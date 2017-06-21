//================================================================================================================================================
//
// (c) GIE 06.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_HELPERS_GET_NODE_ATTR_REPO_H__06_05_2005__20_14_20
#define H_GUARD_SEMANTIC_HELPERS_GET_NODE_ATTR_REPO_H__06_05_2005__20_14_20
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.stdproxy.client.h"
//================================================================================================================================================
namespace gie_idl {
 
    //const attribute_repository_ptr_t get_node_attr_repo(node_i* const node)
    //{
    //    const unknown_ptr_t& parent_as_unknown = node->get_parent();
    //    if( parent_as_unknown )
    //    {
    //        const named_collection_ptr_t& parent_as_named_collection = ::gie::ccom::query_interface_via_proxy<named_collection_i>( parent_as_unknown );
    //        if( !parent_as_named_collection ){ GIE_LIB_NOT_IMPLEMENTED; }
    //        const named_ptr_t& node_as_named = ::gie::ccom::query_interface_<named_i>( node, ::gie::ccom::throw_on_fail() );
    //        const string_t& node_name = node_as_named->get_name();
    //        const named_collection_i::search_result_t& r = (*parent_as_named_collection)[node_name];
    //        if( !r.get<0>() ) //must be found!!!
    //        {
    //            GIE_LIB_NOT_IMPLEMENTED;
    //        }
    //        
    //        GIE_LIB_ASSERTE( ::gie::ccom::is_same( node,r.get<0>().get() ) );
    //        
    //        return r.get<1>();

    //    }
    //    else return NULL;

    //    
    //}
}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_HELPERS_GET_NODE_ATTR_REPO_H__06_05_2005__20_14_20
//================================================================================================================================================
