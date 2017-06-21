//================================================================================================================================================
//
// (c) GIE 06.04.2005
//
//================================================================================================================================================
// NAME: semantic.nodes.multi_symbol.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "semantic.nodes.h"
#include "semantic.nodes.impl.h"

#include "gielib/giecom/giecom.server.h"
#include "gielib/giecom/giecom.server.proxy.stdimpl.h"
#include "gielib/giecom/containers/giecom.list.impl.h"
//================================================================================================================================================
namespace gie_idl { 

    //
    // interfaces list
    //
    typedef gie::ccom::list
            < 
                gie::ccom::implemented<multi_symbol_i>,
                gie::ccom::implemented<named_i>,
                gie::ccom::implemented<gie::ccom::std_proxy_host_i>,
                gie::ccom::implemented<node_i>,
                //iterator interfaces
                gie::ccom::implemented< iteratable_over_node_i >
            > 
            multi_symbol_node_interfaces_t;
    
    //
    // multi_symbol node implementation
    //
    struct multi_symbol_node_impl_t
        : gie::ccom::c_object_root_t
          <
             multi_symbol_node_impl_t, //self type
             node_i ,               //unknown from this interface
             multi_symbol_node_interfaces_t,   //supported interfaces
             gie::ccom::counter_block_t<multi_symbol_node_impl_t, 2>   //counter impl
          >
        , gie::ccom::proxy_anchor_t
        , impl::named_i_impl_t
        , impl::proxy_impl_t<multi_symbol_node_impl_t>
        , impl::node_i_impl_t<type_multi_symbol, multi_symbol_i>
        , ::gie::ccom::list_i_impl_t< node_i_ptr_t >

    {
        multi_symbol_node_impl_t(const string_t& name, const gie::ccom::guid_t& contains)
            : named_i_impl_t ( name )
            , contains_( contains )
        {}

        void ccom_release_resources_()throw()
        {
            ::gie::ccom::list_i_impl_t< node_i_ptr_t >::ccom_release_resources_();
        }

        const gie::ccom::guid_t& contains()const throw()
        {
            return contains_;
        }
    private:
        const gie::ccom::guid_t contains_;
    };


    typedef gie::ccom::c_object_t<multi_symbol_node_impl_t> multi_symbol_node_c;


    //
    // factory function
    //
    multi_symbol_node_ptr_t create_multi_symbol_node(const string_t& name, const gie::ccom::guid_t& contains)
    {
        return multi_symbol_node_ptr_t
            ( multi_symbol_node_c::create<multi_symbol_node_default_interface_i>(name, contains), false );
    }


}
//================================================================================================================================================
