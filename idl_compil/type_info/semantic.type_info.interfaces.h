//================================================================================================================================================
//
// (c) GIE 19.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_TYPE_INFO_INTERFACES_H__19_05_2005__21_29_07
#define H_GUARD_SEMANTIC_TYPE_INFO_INTERFACES_H__19_05_2005__21_29_07
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.non_init.begin.h"
#
#   include "../semantic.tree.core.interfaces.h"
#   include "../semantic.attributes.h"
#
#include "gielib/giecom/giecom.guid.non_init.end.h"
//================================================================================================================================================
namespace gie_idl {

    //
    // node types
    //

    // {300A1150-E7D6-4293-8B41-E64BF49D539E}
    GIE_CCOM_RAW_GUID(type_base_type, 0x300a1150, 0xe7d6, 0x4293, 0x8b, 0x41, 0xe6, 0x4b, 0xf4, 0x9d, 0x53, 0x9e);
    // {2C3875F2-8C55-4cb2-BCF1-991A3C585653}
    GIE_CCOM_RAW_GUID(type_reference_to, 0x2c3875f2, 0x8c55, 0x4cb2, 0xbc, 0xf1, 0x99, 0x1a, 0x3c, 0x58, 0x56, 0x53);
    // {104EE5D0-DF45-4de9-8231-256649A4C3F1}
    GIE_CCOM_RAW_GUID(type_pointer_to, 0x104ee5d0, 0xdf45, 0x4de9, 0x82, 0x31, 0x25, 0x66, 0x49, 0xa4, 0xc3, 0xf1);
    // {23F0C1CE-13E9-49b5-B9A1-A654C6C872F4}
    GIE_CCOM_RAW_GUID(type_type_descriptor, 0x23f0c1ce, 0x13e9, 0x49b5, 0xb9, 0xa1, 0xa6, 0x54, 0xc6, 0xc8, 0x72, 0xf4);

    enum type_info_mods {tim_const};

    //
    // type_descriptor_builder_i
    //
    // {ADBC1358-4FBB-4d4e-BA64-95173C1A8D5C}
    GIE_CCOM_RAW_GUID(type_descriptor_builder_iid,  0xadbc1358, 0x4fbb, 0x4d4e, 0xba, 0x64, 0x95, 0x17, 0x3c, 0x1a, 0x8d, 0x5c);
    struct type_descriptor_builder_i
        : ::gie::ccom::unknown_i
    {
        virtual void enable_mod(const type_info_mods mod2enable)=0;
        virtual void set_next_sub_type(node_i* const type_node)=0;
    };
    typedef ::boost::intrusive_ptr<type_descriptor_builder_i> type_descriptor_builder_ptr_t;

    //
    // type_descriptor_info_i
    //
    // {0454BCE5-F57B-47e6-B3FF-8084B692EA7A}
    GIE_CCOM_RAW_GUID(type_descriptor_info_iid, 0x454bce5, 0xf57b, 0x47e6, 0xb3, 0xff, 0x80, 0x84, 0xb6, 0x92, 0xea, 0x7a);
    struct type_descriptor_info_i
        : ::gie::ccom::unknown_i
    {
        virtual bool is_mod_enabled(const type_info_mods mod2enable)=0;
        virtual const node_i_ptr_t get_next_sub_type()=0;
    };
    typedef ::boost::intrusive_ptr<type_descriptor_info_i> type_descriptor_info_ptr_t;

    //
    // base_type_i
    //
    // {9EADEB23-49DA-4ff2-AE4E-6A542073CFB1}
    GIE_CCOM_RAW_GUID(base_type_iid, 0x9eadeb23, 0x49da, 0x4ff2, 0xae, 0x4e, 0x6a, 0x54, 0x20, 0x73, 0xcf, 0xb1);
    struct base_type_i
        : ::gie::ccom::unknown_i
    {
    };
    typedef ::boost::intrusive_ptr<base_type_i> base_type_ptr_t;

    //
    // pointer_to_i
    //
    // {E268B8DC-EAA1-48a4-88B1-AA5D25FCFB9B}
    GIE_CCOM_RAW_GUID(pointer_to_iid, 0xe268b8dc, 0xeaa1, 0x48a4, 0x88, 0xb1, 0xaa, 0x5d, 0x25, 0xfc, 0xfb, 0x9b);
    struct pointer_to_i
        : ::gie::ccom::unknown_i
    {
    };
    typedef ::boost::intrusive_ptr<pointer_to_i> pointer_to_ptr_t;

    //
    //
    //
    // {43778176-96FA-44ac-A341-74D062B3078C}
    GIE_CCOM_RAW_GUID(reference_to_iid, 0x43778176, 0x96fa, 0x44ac, 0xa3, 0x41, 0x74, 0xd0, 0x62, 0xb3, 0x7, 0x8c);
    struct reference_to_i
        : node_i
    {
    };
    typedef ::boost::intrusive_ptr<reference_to_i> reference_to_ptr_t;

    //
    // type_descriptor_i
    //
    // {2F7BE74B-258E-4f4a-B3F6-4ACBD9E33CC9}
    GIE_CCOM_RAW_GUID(type_descriptor_iid, 0x2f7be74b, 0x258e, 0x4f4a, 0xb3, 0xf6, 0x4a, 0xcb, 0xd9, 0xe3, 0x3c, 0xc9);
    struct type_descriptor_i
        : ::gie::ccom::unknown_i
    {
    };
    typedef ::boost::intrusive_ptr<type_descriptor_i> type_descriptor_ptr_t;

}
GIE_CCOM_BIND_GUID(gie_idl::reference_to_i, gie_idl::reference_to_iid);
GIE_CCOM_BIND_GUID(gie_idl::pointer_to_i, gie_idl::pointer_to_iid);
GIE_CCOM_BIND_GUID(gie_idl::type_descriptor_info_i, gie_idl::type_descriptor_info_iid);
GIE_CCOM_BIND_GUID(gie_idl::type_descriptor_i, gie_idl::type_descriptor_iid);
GIE_CCOM_BIND_GUID(gie_idl::type_descriptor_builder_i, gie_idl::type_descriptor_builder_iid);
GIE_CCOM_BIND_GUID(gie_idl::base_type_i, gie_idl::base_type_iid);
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_TYPE_INFO_INTERFACES_H__19_05_2005__21_29_07
//================================================================================================================================================
