//================================================================================================================================================
//
// (c) GIE 01.06.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_NODES_FUCNTION_FACTORY_H__01_06_2005__23_45_12
#define H_GUARD_SEMANTIC_NODES_FUCNTION_FACTORY_H__01_06_2005__23_45_12
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "semantic.nodes.fucntion.interfaces.h"
//================================================================================================================================================
namespace gie_idl {

    const function_attribute_ptr_t create_function_specifier();
    const function_parameters_ptr_t create_function_parameters();
    const function_ptr_t create_function_node(const string_t& name);

}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_NODES_FUCNTION_FACTORY_H__01_06_2005__23_45_12
//================================================================================================================================================