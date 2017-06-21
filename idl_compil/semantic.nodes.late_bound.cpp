//================================================================================================================================================
//
// (c) GIE 23.04.2005
//
//================================================================================================================================================
// NAME: semantic.nodes.late_bound.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.init.h"                     //START GUID DEF SECTION
#
#   include "semantic.nodes.late_bound.interfaces.h"
#
#include "gielib/giecom/giecom.guid.init.end.h"                 //END GUID SECTION

#include "gielib/giecom/giecom.stdproxy.client.h"
#include "semantic.nodes.h"
#include "semantic.nodes.impl.h"
#include "gielib/giecom/giecom.server.proxy.core.h"
#include "gielib/giecom/giecom.server.h"
//================================================================================================================================================
namespace gie_idl {
    //
    // interfaces list
    //
    typedef gie::ccom::list
            < 
                gie::ccom::implemented<node_i>,
                gie::ccom::implemented<late_bound_i>,
                late_bound_builder_i,
                gie::ccom::std_proxy_i,
                gie::ccom::implemented<gie::ccom::std_proxy_host_i>
            > 
            late_bound_node_interfaces_t;

    //
    // late_boubd node implementation
    //
    struct late_bound_node_impl_t
        : gie::ccom::c_object_root_t
          <
             late_bound_node_impl_t,            //self type
             late_bound_i ,                     //unknown from this interface
             late_bound_node_interfaces_t,      //supported interfaces
             gie::ccom::counter_block_t<late_bound_node_impl_t, 2>
          >
        , gie::ccom::proxy_anchor_t
        , impl::node_i_impl_t<type_late_bound, late_bound_i>
        , impl::proxy_impl_t<late_bound_node_impl_t>
    {
        late_bound_node_impl_t(const fq_id_ptr_t& target_id, const node_i_ptr_t& sym_lookup_parent, const resolver_id_t& resolver_id, ::gie::ccom::unknown_i* const resolver_context)
            : resolver_id_( resolver_id )
            , resolver_context_( resolver_context )
            , target_id_( target_id )
            , sym_lookup_parent_( ::gie::ccom::get_std_proxy( sym_lookup_parent, ::gie::ccom::proxy_throw_validator() )  )
        {
        }
        
        const bool set_target(const node_i_ptr_t& node)
        {
            const ::gie::ccom::std_proxy_ptr_t& new_target = ::gie::ccom::get_std_proxy( node, ::gie::ccom::proxy_throw_validator() );

            const bool was_not_empty = target_ ;
            
            target_ = new_target;

            return was_not_empty;

        }
        bool is_boud()const throw()
        {
            return target_;
        }
        const fq_id_ptr_t& get_id()const
        {
            return target_id_;
        }

        const node_i_ptr_t get_lookup_parent()const
        {
            const node_i_ptr_t sym_lup ( sym_lookup_parent_->query_host_interface_ex<node_i>(), false );
            if( !sym_lup )
            {
                GIE_LIB_NOT_IMPLEMENTED;
            }
            return sym_lup;
        }

        const resolver_id_t& get_resolver_id()const
        {
            return resolver_id_;
        }
        const unknown_ptr_t get_resolver_context()const
        {
            return resolver_context_;
        }

        void* query_host_interface(const gie::ccom::guid_t& iid)
        {
            if( target_ )
                return target_->query_host_interface(iid);
            else 
                return NULL;
        }
    private:
         const resolver_id_t resolver_id_;
         const unknown_ptr_t resolver_context_;
         const fq_id_ptr_t target_id_;
         ::gie::ccom::std_proxy_ptr_t target_;
         const ::gie::ccom::std_proxy_ptr_t sym_lookup_parent_; //we can only refer to proxy, to prevent ref-looping
    };
    typedef gie::ccom::c_object_t<late_bound_node_impl_t> late_bound_node_node_c;
    

    //
    // factory function
    //
    late_bound_ptr_t create_late_bound_node(const fq_id_ptr_t& target_id, const node_i_ptr_t& sym_lookup_parent, const resolver_id_t& resolver_id, ::gie::ccom::unknown_i* const resolver_context)
    {
        return late_bound_ptr_t
            ( late_bound_node_node_c::create<late_bound_i>(target_id, sym_lookup_parent, resolver_id, resolver_context), false );
    }


}
//================================================================================================================================================
