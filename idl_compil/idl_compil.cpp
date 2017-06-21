//================================================================================================================================================
//
// (c) GIE 27.04.2005
//
//================================================================================================================================================
// NAME: idl_compil.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "../grammar/generated/gieidl_lexer.hpp"
#include "../grammar/generated/gieidl_parser.hpp"

#include "symbol_locators/symloc.factory.h"

#include "semantic.helpers.rebind.h"
#include "idl_compil.h"
//================================================================================================================================================
namespace gie_idl {
    namespace impl {
        
        //
        // token_stream_warp_t
        //
        template 
        <
            class parent_token_stream_t_t,
            class input_raw_stream_t_t = std::istream            
        >
        struct token_stream_warp_t
            : public parent_token_stream_t_t
        {
            token_stream_warp_t(input_raw_stream_t_t& raw_stream)
                : parent_token_stream_t_t( raw_stream )
            {
                parent_token_stream_t_t::setTokenObjectFactory( gie_idl::extended_token_t::factory );
            }

            antlr::RefToken nextToken()
            {
                antlr::RefToken tmp_token = parent_token_stream_t_t::nextToken();
                //GIE_LIB_ASSERTE( typeid(extended_token_t)==typeid( *tmp_token.get() ) );
                extended_token_t& extended_token = * static_cast<extended_token_t*>( tmp_token.get() );

                extended_token.set_file_name( string_table_.ref_count_string( this->getFilename() ) );

                return tmp_token;
            }
        
        private:
            using parent_token_stream_t_t::setTokenObjectFactory;

            string_table_t  string_table_;
        };

    
        //   
        // unbound_notifier_t
        //
        struct unbound_notifier_t
            : ::gie::ccom::stack_based_simple_unknown_impl_t<::gie_idl::late_boud_enum_callback_i>
        {
            //simple adapter class
            unbound_notifier_t( compil_t::notify_i* const notifier )
                : ext_notifier_( notifier )
            {}
            action_t enumerate_this(late_bound_i* const late_bound)
            {
                if( !ext_notifier_->process_unbound_symbols( late_bound ) )
                    return abort_enumeration;

                return continue_enumeration;
            }

        private:
            compil_t::notify_i* const ext_notifier_;
        };

    }//end of impl namespace


    bool compil_t::process_unbound_symbols_(const semantic_tree_holder_ptr_t& sh, const unsigned int iteration)
    {
        const notify_i::bool2_t& r = listeners_->before_process_unbound_symbols(iteration);
        if( !r.get<0>() ) return false;

        if( r.get<1>() ) //if invoke call-back for each unbound symbol
        {
            impl::unbound_notifier_t unbound_notifier(listeners_);
            sh->enumerate_late_bound( &unbound_notifier );
        }
        if( !listeners_->after_process_unbound_symbols() )
            return false;

        return true;
    }

    bool compil_t::compile()
    {   GIE_IDL_COMPILER_TRACE_FUNC;

        const symbol_locator_ptr_t& symbol_locator =  create_cpp_like_symbol_locator(); // now suppot (and have) only one locator (cpp-like)

        if( !listeners_->before_building_ast() ) return false;

        gie_idl::impl::token_stream_warp_t<gieidl_lexer> lexer(char_stream_);
        gieidl_parser parser(lexer);
        const boost::intrusive_ptr<semantic_tree_holder_i>& sh = create_semantic_tree_holder();
        parser.set_semantic_tree_holder( sh );
        parser.set_symbol_locator(symbol_locator);

        parser.curr_symbol();

        if( !process_unbound_symbols_(sh, 1) ) return false;
        rebind_symbols( sh, symbol_locator );
        if( !process_unbound_symbols_(sh, 2) ) return false;

        //invoking back end generator
        if( !listeners_->before_backend() ) return false;
        backend::storage_inteface  sif;
        idl_backend_->exec(sh, sif, options_);
        if( !listeners_->after_backend() ) return false;

        //done
        listeners_->done();
        return true;
    }

}
//================================================================================================================================================
