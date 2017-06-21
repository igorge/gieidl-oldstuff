//================================================================================================================================================
//
// (c) GIE 09.03.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_NODES_H__09_03_2005__14_09_21
#define H_GUARD_SEMANTIC_NODES_H__09_03_2005__14_09_21
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "semantic.tree.interfaces.h"
#include "semantic.nodes.late_bound.interfaces.h"
#include "semantic.nodes.semantic_tree_holder.interfaces.h"
#include "semantic.var_decl.interfaces.h"
#include "gielib/giecom/giecom.client.h"
#include "symbol_locators/symloc.interfaces.h"
#include <memory>
//================================================================================================================================================
namespace gie_idl {

    typedef ::boost::intrusive_ptr<named_collection_i> named_collection_i_ptr_t;
    
    //
    // semantic tree holder
    //
    typedef ::boost::intrusive_ptr<semantic_tree_holder_i> semantic_tree_holder_ptr_t;
    semantic_tree_holder_ptr_t create_semantic_tree_holder();


    //
    // namespace node
    //
    typedef namespace_i namespace_node_default_interface_i;
    typedef ::boost::intrusive_ptr<namespace_node_default_interface_i> namespace_node_ptr_t;
    namespace_node_ptr_t create_namespace_node(const string_t& name);

    //
    // aggregate node
    //
    typedef aggregate_i aggregae_node_default_i;
    aggregate_ptr_t create_aggregate_node(const string_t& name);

    //
    // multi_symbol node
    //
    typedef multi_symbol_i multi_symbol_node_default_interface_i;
    typedef ::boost::intrusive_ptr<multi_symbol_node_default_interface_i> multi_symbol_node_ptr_t;
    multi_symbol_node_ptr_t create_multi_symbol_node(const string_t& name, const gie::ccom::guid_t& contains);

    //
    // late_bound node
    //
    typedef ::boost::intrusive_ptr<late_bound_i> late_bound_ptr_t;
    late_bound_ptr_t create_late_bound_node(const fq_id_ptr_t& target_id, const node_i_ptr_t& sym_lookup_parent, const resolver_id_t& resolver_id, ::gie::ccom::unknown_i* const resolver_context = NULL);

    //
    // var_decl node
    //
    var_decl_ptr_t create_var_decl_node(const string_t& name, const node_i_ptr_t& type_descriptor);


}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_NODES_H__09_03_2005__14_09_21
//================================================================================================================================================
