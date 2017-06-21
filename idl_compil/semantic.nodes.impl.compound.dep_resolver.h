//================================================================================================================================================
//
// (c) GIE 08.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_NODES_IMPL_COMPOUND_DEP_RESOLVER_H__08_05_2005__16_38_45
#define H_GUARD_SEMANTIC_NODES_IMPL_COMPOUND_DEP_RESOLVER_H__08_05_2005__16_38_45
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "semantic.helpers.aggregate_filtering_enumerator.h"
//================================================================================================================================================
namespace gie_idl {

    namespace impl {
        
        template <class self_t_t>
        struct filter_out_inner_required_symbol_enumerator_impl_t
        {
            filter_out_inner_required_symbol_enumerator_impl_t()
            {
                typedef ::boost::is_base_and_derived<filter_out_inner_required_symbol_enumerator_impl_t, self_t_t> is_self_ok;
                BOOST_STATIC_ASSERT( is_self_ok::value );
            }

            bool required_symbols_enum_childrens_(required_symbol_enum_callback_i*const enumerator)
            {
                self_t_t::childs_map_t::const_iterator current_child = self_this()->childs_.begin();
                const self_t_t::childs_map_t::const_iterator end = self_this()->childs_.end();
                while( current_child!=end )
                {
                    #ifdef GIE_LIB_DEBUG
                        const string_t& debug__node_name = get_node_name( current_child->second );
                    #endif
                    #ifdef GIE_LIB_DEBUG_W_RTTI
                        const char * const debug__node_type_name = typeid( * current_child->second ).name();
                    #endif

                    const required_symbols_ptr_t& node_as_required_symbol = ::gie::ccom::query_interface<required_symbols_i>( current_child->second );
                    if( node_as_required_symbol )
                    {                    
                        node_as_required_symbol->enumerate_required_symbols( & aggregate_filtering_out_enum_t( enumerator, self_this()->get_self_proxy_unsafe_() ) );
                    }
                    else
                    {
                        GIE_LIB_DEBUG_WARN("children does not support required_symbols_i");
                        GIE_LIB_NOT_IMPLEMENTED;
                    }
                    
                    ++current_child;

                }//end of while

                return true;
            }
        private:
            self_t_t* const self_this()
            {
                return static_cast<self_t_t* const>(this);
            }
            self_t_t const * const self_this()const
            {
                return static_cast<self_t_t* const>(this);
            }

        };

    }// end of implnamespace
}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_NODES_IMPL_COMPOUND_DEP_RESOLVER_H__08_05_2005__16_38_45
//================================================================================================================================================
