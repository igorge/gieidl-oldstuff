//================================================================================================================================================
//
// (c) GIE 26.05.2005
//
//================================================================================================================================================
// NAME: semantic.nodes.var_decl.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.init.h"                     //START GUID DEF SECTION
#
#   include "semantic.var_decl.interfaces.h"
#
#include "gielib/giecom/giecom.guid.init.end.h"                 //END GUID SECTION

#include "semantic.nodes.impl/attribute_repository_holder.impl.h"
#include "semantic.nodes.h"
#include "semantic.nodes.impl.h"
#include "semantic.required_symbols.interfaces.h"

#include "gielib/giecom/giecom.server.h"
#include "gielib/giecom/giecom.server.proxy.stdimpl.h"
//================================================================================================================================================
namespace gie_idl {

    //
    // interfaces list
    //
    typedef gie::ccom::list
            < 
                gie::ccom::implemented<named_i>,
                gie::ccom::implemented<gie::ccom::std_proxy_host_i>,
                gie::ccom::implemented<node_i>,
                gie::ccom::implemented<attribute_repository_holder_i>,
                gie::ccom::implemented<var_decl_i>,
                required_symbols_i
            > 
            var_decl_node_interfaces_t;

    //
    // namespace node implementation
    //
    struct var_decl_node_imp_t
        : gie::ccom::c_object_root_t
          <
             var_decl_node_imp_t,   //self type
             node_i ,               //unknown from this interface
             var_decl_node_interfaces_t,   //supported interfaces
             gie::ccom::counter_block_t<var_decl_node_imp_t, 2>   //counter impl
          >
        , gie::ccom::proxy_anchor_t
        , impl::named_i_impl_t
        , impl::proxy_impl_t<var_decl_node_imp_t>
        , impl::node_i_impl_t<type_var_decl, var_decl_i>
        , impl::attribute_repository_holder_impl_t
    {
        var_decl_node_imp_t(const string_t& name, const node_i_ptr_t& type_descriptor)
            : named_i_impl_t ( name )
            , type_descriptor_( ::gie::ccom::query_interface_<type_descriptor_i>(type_descriptor, ::gie::ccom::throw_on_fail()) )
        {}

        void ccom_release_resources_()throw()
        {
            type_descriptor_ = NULL;
        }

        void enumerate_required_symbols(required_symbol_enum_callback_i*const enumerator)
        {
            const required_symbols_ptr_t& child_required_symbols = ::gie::ccom::query_interface<required_symbols_i>(type_descriptor_);
            if( child_required_symbols )
            {
                child_required_symbols->enumerate_required_symbols( enumerator );
            }
        }

        const type_descriptor_ptr_t get_type()
        {
            return type_descriptor_;
        }


    private:
        type_descriptor_ptr_t type_descriptor_;
    };
    typedef gie::ccom::c_object_t<var_decl_node_imp_t> var_decl_node_com;


    //
    // factory function
    //
    var_decl_ptr_t create_var_decl_node(const string_t& name, const node_i_ptr_t& type_descriptor)
    {GIE_IDL_ST_TRACE_FUNC;
        return var_decl_ptr_t
            ( var_decl_node_com::create<var_decl_i>(name, type_descriptor), false );
    }

}

//================================================================================================================================================
