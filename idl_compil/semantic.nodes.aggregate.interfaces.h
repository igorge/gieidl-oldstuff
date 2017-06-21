//================================================================================================================================================
//
// (c) GIE 18.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_NODES_AGGREGATE_INTERFACES_H__18_04_2005__1_03_04
#define H_GUARD_SEMANTIC_NODES_AGGREGATE_INTERFACES_H__18_04_2005__1_03_04
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.non_init.begin.h"

#include "semantic.tree.core.interfaces.h"
#include "semantic.attributes.interfaces.h"
#include "boost/intrusive_ptr.hpp"

#include "gielib/giecom/giecom.guid.non_init.end.h"
//================================================================================================================================================
namespace gie_idl {
    //
    // aggregate
    //

    //
    // ancestor_enum_callback_i
    //
    // {56DDAB5C-6B0C-441e-9302-4C44279B5D8E}
    GIE_CCOM_RAW_GUID(ancestor_enum_callback_iid, 0x56ddab5c, 0x6b0c, 0x441e, 0x93, 0x2, 0x4c, 0x44, 0x27, 0x9b, 0x5d, 0x8e);
    struct ancestor_enum_callback_i
        : ::gie::ccom::unknown_i
    {
        enum action_t { continue_enumeration=0, abort_enumeration};

        virtual action_t enumerate_this(node_i* const node, const access_t& access)=0;
    };
    typedef ::boost::intrusive_ptr<ancestor_enum_callback_i> ancestor_enum_callback_ptr_t;

    //
    // aggregate_i
    //
    // {89B182FB-71B7-4356-A3BE-FD4D866B6D3D}
    GIE_CCOM_RAW_GUID(aggregate_iid, 0x89b182fb, 0x71b7, 0x4356, 0xa3, 0xbe, 0xfd, 0x4d, 0x86, 0x6b, 0x6d, 0x3d);
    struct aggregate_i
        : named_collection_i
    {
        virtual void enumerate_encestors(ancestor_enum_callback_i*const enumerator)const=0;
    };
    typedef boost::intrusive_ptr<aggregate_i> aggregate_ptr_t;

    //
    //
    //
    // {9CEECDF2-A1EE-4c0e-A003-AD72A55DD698}
    GIE_CCOM_RAW_GUID(aggregate_build_iid, 0x9ceecdf2, 0xa1ee, 0x4c0e, 0xa0, 0x3, 0xad, 0x72, 0xa5, 0x5d, 0xd6, 0x98);
    struct aggregate_build_i
        : gie::ccom::unknown_i
    {
        virtual void add_inheritance_info(const unknown_ptr_t& inh_parent, const access_t& access)=0;
    };
    typedef boost::intrusive_ptr<aggregate_build_i> aggregate_build_ptr_t;
}

GIE_CCOM_BIND_GUID(gie_idl::aggregate_i, gie_idl::aggregate_iid);
GIE_CCOM_BIND_GUID(gie_idl::aggregate_build_i, gie_idl::aggregate_build_iid);
GIE_CCOM_BIND_GUID(gie_idl::ancestor_enum_callback_i, gie_idl::ancestor_enum_callback_iid);
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_NODES_AGGREGATE_INTERFACES_H__18_04_2005__1_03_04
//================================================================================================================================================
