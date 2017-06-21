//================================================================================================================================================
//
// (c) GIE 03.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_HELPERS_GET_PARENT_H__03_05_2005__11_35_21
#define H_GUARD_SEMANTIC_HELPERS_GET_PARENT_H__03_05_2005__11_35_21
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.server.proxy.stdimpl.h"
#include "boost/intrusive_ptr.hpp"
//================================================================================================================================================
namespace gie_idl {

    //
    //
    //
    template <class parent_interface_t_t, class child_t_t>
    inline
    const boost::intrusive_ptr<parent_interface_t_t> get_parent(const child_t_t& child)
    {
        const boost::intrusive_ptr<gie::ccom::unknown_i>& parent_proxy_unknown = child->get_parent();
        if( !parent_proxy_unknown ) //if child have no parent (child is a root)
            return NULL;

        const boost::intrusive_ptr<gie::ccom::std_proxy_i>& std_proxy = gie::ccom::query_interface_<gie::ccom::std_proxy_i>( parent_proxy_unknown, gie::ccom::throw_on_fail() );

        boost::intrusive_ptr<parent_interface_t_t> parent_iface ( 
              static_cast<parent_interface_t_t*const>( std_proxy->query_host_interface(gie::ccom::iid_of<parent_interface_t_t>::value) )
            , false );

        return parent_iface;
    }

}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_HELPERS_GET_PARENT_H__03_05_2005__11_35_21
//================================================================================================================================================
