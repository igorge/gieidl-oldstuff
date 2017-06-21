//================================================================================================================================================
//
// (c) GIE 03.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_IDL_BACKEND_FRAME_INTERFACES_H__03_05_2005__0_02_41
#define H_GUARD_IDL_BACKEND_FRAME_INTERFACES_H__03_05_2005__0_02_41
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../idl_compil/semantic.tree.core.interfaces.h"
#include "../idl_compil/semantic.tree.interfaces.h"
#include "../idl_compil/semantic.var_decl.interfaces.h"
#include "../idl_compil/type_info/semantic.type_info.interfaces.h"
#include "../idl_compil/semantic.nodes.function/semantic.nodes.fucntion.interfaces.h"
//================================================================================================================================================
namespace gie_idl { namespace backend {

    // do_visit_decision - decide should we(default back end visitor) bother at all with node

    struct frame_i
    {
        virtual void frame_visit(namespace_i * const node)=0;
        virtual void frame_visit(aggregate_i * const node)=0;
        virtual void frame_ancestors_visit(aggregate_i * const node, void * const user_context)=0;
        
        virtual void frame_visit(var_decl_i * const node, void * const user_context)=0;
        virtual void frame_visit(type_descriptor_i* const node, void* const user_context)=0;
        virtual void frame_visit(pointer_to_i* const node, void* const user_context)=0;
        virtual void frame_visit(reference_to_i* const node, void* const user_context)=0;

        virtual void frame_visit(function_parameters_i* const node, void* const user_context)=0;
    };

    struct visitor_i
    {
        //
        // namespace hooks
        //
        virtual bool do_visit_decision(namespace_i * const node,  const string_t& name)
        {
            return true;
        }
        virtual void do_visit(frame_i* const frame, namespace_i * const node, const string_t& name)
        {
            frame->frame_visit( node );
        }

        virtual void do_before_visit_traverse(namespace_i * const node,  const string_t& name)
        {
            GIE_LIB_NOT_IMPLEMENTED;
        }
        virtual void do_after_visit_traverse(namespace_i * const node,  const string_t& name)
        {
            GIE_LIB_NOT_IMPLEMENTED;
        }

        //
        // aggregate hooks
        //
        virtual bool do_visit_decision(aggregate_i * const node, const string_t& name)
        {
            return true;
        }
        virtual void do_visit(frame_i* const frame, aggregate_i * const node,  const string_t& name)
        {
            frame->frame_visit(node);
        }

        virtual void do_ancestor_visit(aggregate_i * const node,  const access_t& inh_access, void* const user_context);
        virtual void do_ancestor_visit_decoded(aggregate_i * const node,  const string_t& fq_path, const access_t& inh_access,  const string_t& inh_access_as_string, void* const user_context)
        {}

        
        virtual void do_ancestor_visit(late_bound_i * const node,  const access_t& inh_access, void* const user_context); //invoked if no symbols is found
        virtual void do_ancestor_visit_decoded(late_bound_i * const node,  const string_t& symbol, const access_t& inh_access,  const string_t& inh_access_as_string, void* const user_context)
        {}

        //
        // var_decl hooks
        //
        virtual bool do_visit_decision(var_decl_i * const node,  const string_t& name)
        {
            return true;
        }
        virtual void do_visit(frame_i* const frame, var_decl_i * const node,  const string_t& name, type_descriptor_i* const type_descriptor)
        {
            frame->frame_visit(node, NULL);
        }

        // type info visitors
        virtual void do_visit(frame_i* const frame, type_descriptor_i* const node, void* const user_context)
        {
            frame->frame_visit(node, NULL); //null couse new context
        }

        virtual void do_visit(frame_i* const frame, pointer_to_i* const node, void* const user_context)
        {
            frame->frame_visit(node, user_context);
        }

        virtual void do_visit(frame_i* const frame, reference_to_i* const node, void* const user_context)
        {
            frame->frame_visit(node, user_context);
        }

        virtual void do_visit(frame_i* const frame, base_type_i* const node, void* const user_context)
        {
            // do not call frame, because this is a terminal subtype
        }

        // function
        virtual bool do_visit_decision(function_i * const node,  const string_t& name)
        {
            return true;
        }
        virtual void do_visit(frame_i* const frame, function_i* const node, const string_t& name, type_descriptor_i* const ret_type, function_parameters_i* const function_parameters)
        {
            do_visit( frame, ret_type, NULL ); //new context
            frame->frame_visit( function_parameters, NULL ); // new context
        }
        virtual void do_visit_function_parameter(frame_i* const frame, var_decl_i * const node,  const string_t& name, const unsigned int pos)
        {
            frame->frame_visit(node,NULL);
        }

    };

} }
//================================================================================================================================================
#endif//H_GUARD_IDL_BACKEND_FRAME_INTERFACES_H__03_05_2005__0_02_41
//================================================================================================================================================
