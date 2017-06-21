//================================================================================================================================================
//
// (c) GIE 08.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_HELPERS_AGGREGATE_FILTERING_ENUMERATOR_H__08_05_2005__2_04_28
#define H_GUARD_SEMANTIC_HELPERS_AGGREGATE_FILTERING_ENUMERATOR_H__08_05_2005__2_04_28
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "semantic.required_symbols.interfaces.h"
#include "semantic.helpers.get_node_name.h"
#include "semantic.helpers.get_node_path_as_string.h"
#include "gielib/giecom/giecom.server.stackbased.simple.h"
#include "gielib/giecom/giecom.stdproxy.client.h"
//================================================================================================================================================
namespace gie_idl {




    //
    // required_symbols_enum_t
    //
    struct aggregate_filtering_out_enum_t
        : ::gie::ccom::stack_based_simple_unknown_impl_t<required_symbol_enum_callback_i>
    {
        aggregate_filtering_out_enum_t(required_symbol_enum_callback_i* const target_enum, const ::gie::ccom::std_proxy_ptr_t& filter_value)
            : target_enum_( target_enum )
            , filter_value_( filter_value )
        {}
        void enumerate_this_required_symbol(node_i* const node, const bool is_forward_only_ok)
        {
            #ifdef GIE_LIB_DEBUG
                const string_t& debug__node_name = get_node_name( node );
            #endif

            const unknown_ptr_t& nodes_parent = node->get_parent();
            GIE_LIB_IS_VALID_POINTER( nodes_parent.get() );
            GIE_LIB_ASSERTE( !::gie::ccom::query_interface<node_i>(nodes_parent) ); //couse parent must be an a proxy
            if( filter_value(nodes_parent) )
                return;
            
            target_enum_->enumerate_this_required_symbol(node, is_forward_only_ok);
        };
    private:
        //ret true if filtered
        bool filter_value(const unknown_ptr_t& node)
        {
            unknown_ptr_t current_node = node; //actually current proxy of node
            while( current_node )
            {
                if( ::gie::ccom::is_same(filter_value_,  current_node) ) return true;

                const node_i_ptr_t& real_node = ::gie::ccom::query_interface_via_proxy<node_i>(current_node, ::gie::ccom::throw_on_fail(), ::gie::ccom::throw_on_fail() );

                #ifdef GIE_LIB_DEBUG_W_RTTI
                    const char* const node_class_name = typeid( *node ).name();
                    const char* const filter_value_node_class_name = typeid( *filter_value_ ).name();
                #endif
                #ifdef GIE_LIB_DEBUG
                    const string_t& node_name = ::gie::ccom::query_interface_<named_i>(real_node, ::gie::ccom::throw_on_fail() )->get_name();
                    const string_t& filter_value_node_name = ::gie::ccom::query_interface_via_proxy<named_i>(filter_value_, ::gie::ccom::throw_on_fail(), ::gie::ccom::throw_on_fail() )->get_name();
                    const string_t& node_path = get_node_path_as_string( real_node );
                #endif

                current_node = real_node->get_parent();

            }
            //if we have reached root node (that is roo ns that is have no parent) then do not filter node, because it is not in local domain
            return false;
        }
    private:
        required_symbol_enum_callback_i* const target_enum_;
        const ::gie::ccom::std_proxy_ptr_t filter_value_;
    };

}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_HELPERS_AGGREGATE_FILTERING_ENUMERATOR_H__08_05_2005__2_04_28
//================================================================================================================================================
