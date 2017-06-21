//================================================================================================================================================
//
// (c) GIE 29.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_HELPERS_NODE_TYPE2STRING_H__29_04_2005__21_45_11
#define H_GUARD_SEMANTIC_HELPERS_NODE_TYPE2STRING_H__29_04_2005__21_45_11
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "semantic.tree.core.interfaces.h"
#include "semantic.var_decl.interfaces.h"
#include "semantic.nodes.function/semantic.nodes.fucntion.interfaces.h"
//================================================================================================================================================
namespace gie_idl {
    
    //
    // node type string mapper
    //
    inline
    const string_t map_node_type2string(const type_of_node_t& type_of_node)
    {
        if( type_of_node==type_aggregate )return wxT("aggregate");
        if( type_of_node==type_late_bound )return wxT("late bound");
        if( type_of_node==type_namespace)return wxT("namespace");
        if( type_of_node==type_var_decl)return wxT("var_decl");
        if( type_of_node==type_base_type)return wxT("base_type");
        if( type_of_node==type_reference_to)return wxT("reference_to");
        if( type_of_node==type_pointer_to)return wxT("pointer_to");
        if( type_of_node==type_type_descriptor)return wxT("type_descriptor");
        if( type_of_node==type_function_parameters)return wxT("function_parameters");
        if( type_of_node==type_function)return wxT("function");
        GIE_LIB_NOT_IMPLEMENTED;
    }

}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_HELPERS_NODE_TYPE2STRING_H__29_04_2005__21_45_11
//================================================================================================================================================
