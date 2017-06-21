//================================================================================================================================================
//
// (c) GIE 27.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_HELPERS_GET_NODE_NAME_H__27_04_2005__13_14_30
#define H_GUARD_SEMANTIC_HELPERS_GET_NODE_NAME_H__27_04_2005__13_14_30
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "semantic.tree.core.interfaces.h"
//================================================================================================================================================
namespace gie_idl {

    inline
    const string_t get_node_name(node_i* const node)
    {
        const named_ptr_t& named = ::gie::ccom::query_interface_<named_i>(node, ::gie::ccom::throw_on_fail() );
        return named->get_name();
    }

    inline
    const string_t get_node_name(const node_i_ptr_t& node)
    {
        return get_node_name( node.get() );
    }

    template <class interface_t_t>
    inline
    const string_t get_node_name_no__fail(const ::boost::intrusive_ptr<interface_t_t>& node)
    {
        return get_node_name_no__fail( node.get() );
    }

    template <class interface_t_t>
    inline
    const string_t get_node_name_no__fail(interface_t_t* const node)
    {
        const named_ptr_t& named = ::gie::ccom::query_interface<named_i>(node);
        if( named )
            return named->get_name();
        else
            return wxT(" !!!node does not support required interface!!!");
    }

}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_HELPERS_GET_NODE_NAME_H__27_04_2005__13_14_30
//================================================================================================================================================
