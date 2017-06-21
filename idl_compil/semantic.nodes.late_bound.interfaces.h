//================================================================================================================================================
//
// (c) GIE 23.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_NODES_LATE_BOUND_INTERFACES_H__23_04_2005__19_31_06
#define H_GUARD_SEMANTIC_NODES_LATE_BOUND_INTERFACES_H__23_04_2005__19_31_06
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.non_init.begin.h"
#
#   include "semantic.tree.core.interfaces.h"
#   include "semantic.nodes.fq_id.h"
#   include "semantic.attributes.h"
#   include "symbol_locators/symloc.interfaces.h"
#
#include "gielib/giecom/giecom.guid.non_init.end.h"
//================================================================================================================================================
namespace gie_idl {
    
    //
    // late_bound_i
    //
    // {1221409A-1E75-47bc-9E84-0F14FDD61DA0}
    GIE_CCOM_RAW_GUID(late_bound_iid, 0x1221409a, 0x1e75, 0x47bc, 0x9e, 0x84, 0xf, 0x14, 0xfd, 0xd6, 0x1d, 0xa0);
    struct late_bound_i
        : node_i
    {
        virtual bool is_boud()const throw()=0;
        virtual const fq_id_ptr_t& get_id()const =0;
        virtual const node_i_ptr_t get_lookup_parent()const=0;
        virtual const resolver_id_t& get_resolver_id()const=0;
        virtual const unknown_ptr_t get_resolver_context()const=0;
    };
    typedef boost::intrusive_ptr<late_bound_i> late_bound_ptr_t;

    //
    // late_bound_builder_i
    //
    // {291081C7-5693-44b8-9911-2916672517EE}
    GIE_CCOM_RAW_GUID(late_bound_builder_iid, 0x291081c7, 0x5693, 0x44b8, 0x99, 0x11, 0x29, 0x16, 0x67, 0x25, 0x17, 0xee);
    struct late_bound_builder_i
        : gie::ccom::unknown_i
    {
        virtual const bool set_target(const node_i_ptr_t& node)=0;
    };
    typedef boost::intrusive_ptr<late_bound_builder_i> late_bound_builder_ptr_t;

}
GIE_CCOM_BIND_GUID(gie_idl::late_bound_i, gie_idl::late_bound_iid);
GIE_CCOM_BIND_GUID(gie_idl::late_bound_builder_i, gie_idl::late_bound_builder_iid);
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_NODES_LATE_BOUND_INTERFACES_H__23_04_2005__19_31_06
//================================================================================================================================================
