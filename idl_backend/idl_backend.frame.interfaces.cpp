//================================================================================================================================================
//
// (c) GIE 03.05.2005
//
//================================================================================================================================================
// NAME: idl_backend.frame.interfaces.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "idl_backend.frame.interfaces.h"
//================================================================================================================================================
#include "../idl_compil/semantic.helpers.get_node_name.h"
#include "../idl_compil/semantic.helpers.get_node_path_as_string.h"
#include "../idl_compil/semantic.builder.helper.access2string.h"
#include "../idl_compil/semantic.helpers.id2string.h"
//================================================================================================================================================
namespace gie_idl { namespace backend {

    void visitor_i::do_ancestor_visit(aggregate_i * const node, const access_t& inh_access, void* const user_context)
    {
        const string_t& node_path = get_node_path_as_string( node );

        do_ancestor_visit_decoded(node, node_path, inh_access, map_access2string(inh_access), user_context );
    }

    void visitor_i::do_ancestor_visit(late_bound_i * const node,  const access_t& inh_access, void* const user_context)
    {
        do_ancestor_visit_decoded( node, map_id2string(node->get_id()), inh_access, map_access2string(inh_access), user_context );
    }

} }
//================================================================================================================================================
