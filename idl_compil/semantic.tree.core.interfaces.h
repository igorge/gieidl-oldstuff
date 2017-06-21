//================================================================================================================================================
//
// (c) GIE 18.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_TREE_CORE_INTERFACES_H__18_04_2005__1_00_13
#define H_GUARD_SEMANTIC_TREE_CORE_INTERFACES_H__18_04_2005__1_00_13
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.non_init.begin.h"

#include "gielib/giecom/giecom.guid.core.h"
#include "gielib/giecom/giecom.core.h"

#include "guid_map.interfaces.h"
#include "semantic.access.h"

#include "boost/intrusive_ptr.hpp"
#include "boost/tuple/tuple.hpp"

#include "gielib/giecom/giecom.guid.non_init.end.h"
//================================================================================================================================================
namespace gie_idl {


    //
    // node types
    //
    typedef gie::ccom::guid_t type_of_node_t;

    // {943C6466-8D5E-4b12-B201-CD98360BB73E}
    GIE_CCOM_RAW_GUID(type_namespace, 0x943c6466, 0x8d5e, 0x4b12, 0xb2, 0x1, 0xcd, 0x98, 0x36, 0xb, 0xb7, 0x3e);
    // {152275D3-E832-47b2-991E-10DA544DD820}
    GIE_CCOM_RAW_GUID(type_aggregate, 0x152275d3, 0xe832, 0x47b2, 0x99, 0x1e, 0x10, 0xda, 0x54, 0x4d, 0xd8, 0x20);
    // {A7F19169-7B51-49a6-9FCE-ECBF64BB5F02}
    GIE_CCOM_RAW_GUID(type_multi_symbol, 0xa7f19169, 0x7b51, 0x49a6, 0x9f, 0xce, 0xec, 0xbf, 0x64, 0xbb, 0x5f, 0x2);
    // {5DA3B42C-588D-4d3d-971C-E08A82FA4B61}
    GIE_CCOM_RAW_GUID(type_late_bound, 0x5da3b42c, 0x588d, 0x4d3d, 0x97, 0x1c, 0xe0, 0x8a, 0x82, 0xfa, 0x4b, 0x61);

    // {67FA83BD-F074-4dc0-9F68-C745A8BFA9CB}
    GIE_CCOM_RAW_GUID(aggregate_class, 0x67fa83bd, 0xf074, 0x4dc0, 0x9f, 0x68, 0xc7, 0x45, 0xa8, 0xbf, 0xa9, 0xcb);
    // {CF011D4E-9AC7-4351-B0C2-2125A1E2AF8A}
    GIE_CCOM_RAW_GUID(aggregate_struct, 0xcf011d4e, 0x9ac7, 0x4351, 0xb0, 0xc2, 0x21, 0x25, 0xa1, 0xe2, 0xaf, 0x8a);
    // {31EBA0CB-8FE6-41bd-A019-EAD43A4F7433}
    GIE_CCOM_RAW_GUID(aggregate_interface, 0x31eba0cb, 0x8fe6, 0x41bd, 0xa0, 0x19, 0xea, 0xd4, 0x3a, 0x4f, 0x74, 0x33);


    typedef boost::intrusive_ptr<gie::ccom::unknown_i> unknown_ptr_t;

    //
    // node_i
    //
    // {62F4622B-E09D-4acd-AF51-EDB4228764D1}
    GIE_CCOM_RAW_GUID(node_iid, 0x62f4622b, 0xe09d, 0x4acd, 0xaf, 0x51, 0xed, 0xb4, 0x22, 0x87, 0x64, 0xd1);
    struct node_i
        : gie::ccom::unknown_i
    {
        virtual void set_parent(gie::ccom::unknown_i*const parent_proxy)=0;
        virtual const boost::intrusive_ptr<gie::ccom::unknown_i> get_parent()=0;
        virtual const gie::ccom::guid_t& get_type()const throw()=0;
    };
    typedef boost::intrusive_ptr<node_i> node_i_ptr_t;

    //
    // named_i
    //
    // {EE99B34F-F09E-4e38-B4BB-0BAA8CE7BD82}
    GIE_CCOM_RAW_GUID(named_iid, 0xee99b34f, 0xf09e, 0x4e38, 0xb4, 0xbb, 0xb, 0xaa, 0x8c, 0xe7, 0xbd, 0x82);
    struct named_i
        : gie::ccom::unknown_i
    {
        virtual const string_t& get_name()const throw()=0;
    };
    typedef boost::intrusive_ptr<named_i> named_ptr_t;

    //
    //
    //
    // {BA8C7081-DDF9-4d80-A3BF-5CDB02C9F130}
    GIE_CCOM_RAW_GUID(named_node_enum_callback_iid, 0xba8c7081, 0xddf9, 0x4d80, 0xa3, 0xbf, 0x5c, 0xdb, 0x2, 0xc9, 0xf1, 0x30);
    struct named_node_enum_callback_i
        : ::gie::ccom::unknown_i
    {
        enum action_t { continue_enumeration=0, abort_enumeration};

        virtual action_t enumerate_this(node_i* const node, const string_t& name)=0;
    };
    typedef ::boost::intrusive_ptr<named_node_enum_callback_i> node_enum_callback_ptr_t;

    //
    // named collection
    //
    typedef boost::tuple<
        const boost::intrusive_ptr<node_i>&, 
        const bool 
    > insert_child_result_t;
    // {6704FE01-4103-4ecd-86BF-DFA415B993F2}
    GIE_CCOM_RAW_GUID(named_collection_iid, 0x6704fe01, 0x4103, 0x4ecd, 0x86, 0xbf, 0xdf, 0xa4, 0x15, 0xb9, 0x93, 0xf2);
    struct named_collection_i
        : node_i
    {
        typedef node_i_ptr_t search_result_t;

        virtual const insert_child_result_t insert_child(node_i * const child)=0;
        //virtual const search_result_t operator[](const string_t& name)=0;
        virtual bool locate_node(const string_t& name, named_node_enum_callback_i* const enumerator)=0;
        virtual void enumerate_nodes( named_node_enum_callback_i* const enumerator)=0;
        
        GIE_LIB_FORCE_INLINE
        void enumerate_nodes( node_enum_callback_ptr_t& enumerator)
        {
            enumerate_nodes( enumerator.get() );
        }
    };
    typedef boost::intrusive_ptr<named_collection_i> named_collection_ptr_t;

    //
    // symbol_resolution_i
    //
    // {C9AFC6AD-C9D1-423e-B855-A3833B1A910E}
    GIE_CCOM_RAW_GUID(symbol_resolution_iid, 0xc9afc6ad, 0xc9d1, 0x423e, 0xb8, 0x55, 0xa3, 0x83, 0x3b, 0x1a, 0x91, 0xe);
    struct symbol_resolution_i
        : ::gie::ccom::unknown_i
    {
        typedef ::boost::tuple<const node_i_ptr_t, const access_t> symbol_ret_t;

        virtual const symbol_ret_t resolve_symbol(const string_t& name)=0;
    };
    typedef ::boost::intrusive_ptr<symbol_resolution_i> symbol_resolution_ptr_t;

}

GIE_CCOM_BIND_GUID(gie_idl::symbol_resolution_i, gie_idl::symbol_resolution_iid);
GIE_CCOM_BIND_GUID(gie_idl::named_node_enum_callback_i, gie_idl::named_node_enum_callback_iid);
GIE_CCOM_BIND_GUID(gie_idl::named_collection_i, gie_idl::named_collection_iid);
GIE_CCOM_BIND_GUID(gie_idl::node_i, gie_idl::node_iid);
GIE_CCOM_BIND_GUID(gie_idl::named_i, gie_idl::named_iid);
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_TREE_CORE_INTERFACES_H__18_04_2005__1_00_13
//================================================================================================================================================
