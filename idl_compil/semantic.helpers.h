//================================================================================================================================================
//
// (c) GIE 14.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_HELPERS_H__14_04_2005__14_00_42
#define H_GUARD_SEMANTIC_HELPERS_H__14_04_2005__14_00_42
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "semantic.helpers.get_node_path_as_string.h"
#include "type_info/semantic.type_info.factory.h"
#include "symbol_locators/symloc.interfaces.h"
#include "semantic.nodes.fq_id.h"
#include "semantic.nodes.h"
#include "semantic.tree.interfaces.h"
#include "semantic.attributes.interfaces.h"
#include "semantic.helpers.get_parent.h"
#include "gielib/giecom/giecom.server.proxy.core.h" //interfaces
#ifdef GIE_LIB_DEBUG
    #include "semantic.helpers.id2string.h"
#endif
//================================================================================================================================================
namespace gie_idl {

    //
    //
    //
    inline
    const gie::ccom::guid_t& map_default_aggregate_access(const gie::ccom::guid_t& aggregate_type)
    {   GIE_IDL_ST_TRACE_FUNC;

        if( aggregate_type==aggregate_class )
            return access_private;
        if( aggregate_type==aggregate_struct )
            return access_public;
        if( aggregate_type==aggregate_interface )
            return access_private;

        GIE_LIB_NOT_IMPLEMENTED;
    }

    //
    // create_base_type
    //
    inline
    const node_i_ptr_t bind_symbol(
          const node_i_ptr_t& from_scope
        , const fq_id_ptr_t& id
        , const semantic_tree_holder_ptr_t& tree
        , const symbol_locator_ptr_t& symbol_locator
        , const resolver_id_t& resolver_id
        , ::gie::ccom::unknown_i* const resolver_context = NULL
    )
    {
        const node_i_ptr_t& bound2node = symbol_locator->locate_symbol( from_scope.get(), id, tree->get_root_node().get(), resolver_id, resolver_context);
        if( bound2node )
            return bound2node;
        else
        {   //bind to proxy
            const late_bound_ptr_t& late_bound_proxy = create_late_bound_node(id, from_scope, resolver_id, resolver_context);
            tree->push_back_new_late_boud( late_bound_proxy );
            return late_bound_proxy;
        }
    }

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
                );

    //
    // create_base_type
    //
    inline
    const type_descriptor_builder_ptr_t create_base_type(
          node_i_ptr_t& ret_node
        , const node_i_ptr_t& from_scope
        , const fq_id_ptr_t& id
        , const semantic_tree_holder_ptr_t& tree
        , const symbol_locator_ptr_t& symbol_locator
        )
    {
        GIE_LIB_IS_VALID_POINTER( from_scope.get() );
        GIE_LIB_IS_VALID_POINTER( id.get() );
        GIE_LIB_IS_VALID_POINTER( tree.get() );
        GIE_LIB_IS_VALID_POINTER( symbol_locator.get() );
        #ifdef GIE_LIB_DEBUG
            const string_t& debug__scope = get_node_path_as_string( from_scope );
            const string_t& debug__id = map_id2string( id );
        #endif

        const node_i_ptr_t& node = bind_symbol(from_scope, id, tree, symbol_locator, ambiguity_resolver_aggregate, NULL);

        const base_type_ptr_t& base_type = create_base_type();
        ret_node = ::gie::ccom::query_interface_<node_i>( base_type, ::gie::ccom::throw_on_fail() );

        const type_descriptor_builder_ptr_t& type_builder = ::gie::ccom::query_interface_<type_descriptor_builder_i>(base_type, ::gie::ccom::throw_on_fail() );
        type_builder->set_next_sub_type( node.get() );

        return type_builder;
    }

    //
    // create_type_descriptor
    //
    inline
    const node_i_ptr_t create_type_descriptor(const node_i_ptr_t& target)
    {
        GIE_LIB_IS_VALID_POINTER( target.get() );

        const type_descriptor_ptr_t& type_descriptor =  create_type_descriptor();

        const type_descriptor_builder_ptr_t& type_builder = ::gie::ccom::query_interface_<type_descriptor_builder_i>(type_descriptor, ::gie::ccom::throw_on_fail() );
        type_builder->set_next_sub_type( target.get() );

        return ::gie::ccom::query_interface_<node_i>( type_descriptor, ::gie::ccom::throw_on_fail() );
    }

}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_HELPERS_H__14_04_2005__14_00_42
//================================================================================================================================================
