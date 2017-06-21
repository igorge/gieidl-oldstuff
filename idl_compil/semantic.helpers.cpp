//================================================================================================================================================
//
// (c) GIE 19.04.2005
//
//================================================================================================================================================
// NAME: semantic.helpers.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "semantic.helpers.h"
#include "semantic.attributes.h"

#include "gielib/giecom/giecom.stdproxy.client.h"
//================================================================================================================================================
namespace gie_idl {
   
    //
    // create_inheretance_info
    //
    void create_inheretance_info(
                  const aggregate_ptr_t& this_aggregate
                , const fq_id_ptr_t& id
                , const semantic_tree_holder_ptr_t& tree
                , const symbol_locator_ptr_t& symbol_locator
                , const node_i_ptr_t& sym_lookup_parent
                , const gie::ccom::guid_t& access
                , const bool bind2proxy
                )
    {
        GIE_LIB_IS_VALID_POINTER( symbol_locator.get() );

        if( bind2proxy )
        {
            GIE_LIB_NOT_IMPLEMENTED;
        }
        else
        {
            const aggregate_build_ptr_t& aggregate_builder = gie::ccom::query_interface_<aggregate_build_i>(this_aggregate, gie::ccom::throw_on_fail() );

            const node_i_ptr_t& bound2node = symbol_locator->locate_symbol( sym_lookup_parent.get(), id, tree->get_root_node().get(), ambiguity_resolver_aggregate);
            if( bound2node )
            {   //symbol found
                const boost::intrusive_ptr<gie::ccom::std_proxy_i>& node_proxy = gie::ccom::get_std_proxy( bound2node, gie::ccom::proxy_throw_validator() );
                aggregate_builder->add_inheritance_info(node_proxy,  access);
            }
            else
            {   //bind to proxy
                const late_bound_ptr_t& late_bound_proxy = create_late_bound_node(id, sym_lookup_parent,  ambiguity_resolver_aggregate);
                late_bound_proxy->set_parent( this_aggregate.get() );
                aggregate_builder->add_inheritance_info(  ::gie::ccom::get_std_proxy( late_bound_proxy, ::gie::ccom::proxy_throw_validator() ), access);

                tree->push_back_new_late_boud( late_bound_proxy );
            }
        }
    }

}
//================================================================================================================================================
