//================================================================================================================================================
//
// (c) GIE 26.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_HELPERS_REBIND_H__26_04_2005__21_29_57
#define H_GUARD_SEMANTIC_HELPERS_REBIND_H__26_04_2005__21_29_57
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "symbol_locators/symloc.interfaces.h"
#include "semantic.helpers.get_node_path_as_string.h"
#include "gielib/giecom/giecom.server.stackbased.simple.h"
#include "gielib/giecom/giecom.stdproxy.client.h"
//================================================================================================================================================
namespace gie_idl {

    namespace impl {

        //   
        // try_to_rebind_t
        //
        struct try_to_rebind_t
            : ::gie::ccom::stack_based_simple_unknown_impl_t<::gie_idl::late_boud_enum_callback_i>
        {
            try_to_rebind_t(const semantic_tree_holder_ptr_t& tree_holder, const symbol_locator_ptr_t symbol_locator)
                : tree_holder_( tree_holder )
                , symbol_locator_( symbol_locator )
            {}
            action_t enumerate_this(late_bound_i* const late_bound)
            {
                const node_i_ptr_t& late_bound_as_node = ::gie::ccom::query_interface<node_i>(late_bound);
                const unknown_ptr_t& parent_as_unknown = late_bound_as_node->get_parent();
                
                #ifdef GIE_LIB_DEBUG_W_RTTI
                    const char * const debug__parent_type_name = typeid( * parent_as_unknown.get() ).name();
                #endif


                // parent must be valid, only root ns have no parent
                const node_i_ptr_t& parent = ::gie::ccom::query_interface_via_proxy<node_i>( parent_as_unknown, ::gie::ccom::throw_on_fail(), ::gie::ccom::throw_on_fail() );

                
                #ifdef GIE_LIB_DEBUG_W_RTTI
                    const char * const debug__parent_type_name_resolved = typeid( * parent.get() ).name();
                #endif

                const node_i_ptr_t& bound2node = symbol_locator_->locate_symbol (
                      late_bound->get_lookup_parent().get()
                    , late_bound->get_id()
                    , tree_holder_->get_root_node().get()
                    , late_bound->get_resolver_id()
                    , late_bound->get_resolver_context().get()
                    );

                if( bound2node ) // if bound (that is resolver accepted node) remove from unbound list.
                {
                    #ifdef GIE_LIB_DEBUG
                        const string_t& bound_to_node_name = get_node_path_as_string(bound2node);
                    #endif
                    const late_bound_builder_ptr_t& late_bound_builder = ::gie::ccom::query_interface_<late_bound_builder_i>( late_bound, ::gie::ccom::throw_on_fail() );
                    late_bound_builder->set_target( bound2node );
                    return  delete_this_item_and_continue;
                }

                return continue_enumeration;
            }

        private:
            const semantic_tree_holder_ptr_t tree_holder_;
            const symbol_locator_ptr_t       symbol_locator_;
        };

    } // end of namespace impl
    
    inline
    void rebind_symbols(const semantic_tree_holder_ptr_t& sh, const symbol_locator_ptr_t& symbol_locator)
    {
        impl::try_to_rebind_t try_rebinder(sh, symbol_locator);
        sh->enumerate_late_bound( &try_rebinder );
    }

}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_HELPERS_REBIND_H__26_04_2005__21_29_57
//================================================================================================================================================
