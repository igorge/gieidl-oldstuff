//================================================================================================================================================
//
// (c) GIE 26.05.2005
//
//================================================================================================================================================
// NAME: semantic.nodes.pointer_to.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "semantic.type_info.interfaces.h"
#include "semantic.nodes.type_descriptor_builder_i.impl.h"

#include "../semantic.required_symbols.interfaces.h"
#include "../semantic.nodes.impl.h"

#include "gielib/giecom/giecom.server.h"
#include "gielib/giecom/giecom.server.proxy.stdimpl.h"
//================================================================================================================================================
namespace gie_idl {

    typedef gie::ccom::list
            < 
                gie::ccom::implemented<gie::ccom::std_proxy_host_i>,
                gie::ccom::implemented<node_i>,
                gie::ccom::implemented<type_descriptor_builder_i>,
                pointer_to_i,
                gie::ccom::implemented<type_descriptor_info_i>,
                required_symbols_i
            > 
            pointer_to_interfaces_t;

    //
    // namespace node implementation
    //
    struct pointer_to_impl_t
        : gie::ccom::c_object_root_t
          <
             pointer_to_impl_t,             //self type
             node_i ,                           //unknown from this interface
             pointer_to_interfaces_t,       //supported interfaces
             gie::ccom::counter_block_t<pointer_to_impl_t, 2>   //counter impl
          >
        , gie::ccom::proxy_anchor_t
        , impl::proxy_impl_t<pointer_to_impl_t>
        , impl::node_i_impl_t<type_pointer_to, node_i>
        , impl::type_descriptor_builder_owner_impl_t<pointer_to_impl_t>

    {
        typedef impl::type_descriptor_builder_owner_impl_t<pointer_to_impl_t> my_type_builder_impl_t;

        void enumerate_required_symbols(required_symbol_enum_callback_i*const enumerator)
        {
            my_type_builder_impl_t::enumerate_required_symbols_(enumerator);
        }

        void ccom_release_resources_()throw()
        {
            my_type_builder_impl_t::ccom_release_resources_();
        }
    };
    typedef gie::ccom::c_object_t<pointer_to_impl_t> pointer_to_node_ccom;

    //
    // factory function
    //
    const pointer_to_ptr_t create_pointer_to()
    {
        return pointer_to_ptr_t
            ( pointer_to_node_ccom::create<pointer_to_i>(), false );
    }



}
//================================================================================================================================================
