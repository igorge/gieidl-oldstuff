//================================================================================================================================================
//
// (c) GIE 03.06.2005
//
//================================================================================================================================================
#ifndef H_GUARD_PARSER_HELPER_FUNCTION_H__03_06_2005__21_28_45
#define H_GUARD_PARSER_HELPER_FUNCTION_H__03_06_2005__21_28_45
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../idl_compil/semantic.nodes.function/semantic.nodes.fucntion.interfaces.h"
//================================================================================================================================================
namespace gie_idl { namespace grammar {

    inline
    void add_new_function_parameters(gie_idl::function_ptr_t&  function_node, function_parameters_builder_ptr_t& parameters_builder)
    {
        GIE_LIB_IS_VALID_POINTER( function_node.get() );
        GIE_LIB_IS_VALID_POINTER( parameters_builder.get() );

        const function_builder_ptr_t& function_builder = ::gie::ccom::query_interface_<function_builder_i>( function_node, ::gie::ccom::throw_on_fail() );
        function_builder->add( parameters_builder );
    }

    inline
    void insert_new_function_decl(const gie_idl::node_i_ptr_t& parent, const node_i_ptr_t& node, const attribute_repository_ptr_t& attr_repo)
    {
        using namespace gie_idl;

        GIE_LIB_IS_VALID_POINTER( parent.get() );
        GIE_LIB_IS_VALID_POINTER( node.get() );

        const gie_idl::named_collection_i_ptr_t& parent_node = gie::ccom::query_interface_<gie_idl::named_collection_i>( parent, gie::ccom::throw_on_fail() );
        if( attr_repo )
            set_attribute_repository(node, attr_repo );

        const gie_idl::insert_child_result_t& r = parent_node->insert_child( node.get() );
        if( r.get<1>() ) // 0 - node, 1 - inserted or not
        {
            //inserted ok
        }
        else
        {
            GIE_LIB_NOT_IMPLEMENTED_1("Failed to insert function/member");
        }


    }

} }
//================================================================================================================================================
#endif//H_GUARD_PARSER_HELPER_FUNCTION_H__03_06_2005__21_28_45
//================================================================================================================================================
