//================================================================================================================================================
//
// (c) GIE 01.06.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_NODES_FUCNTION_INTERFACES_H__01_06_2005__21_36_32
#define H_GUARD_SEMANTIC_NODES_FUCNTION_INTERFACES_H__01_06_2005__21_36_32
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.non_init.begin.h"
#
#   include "../semantic.tree.core.interfaces.h"
#   include "../semantic.attributes.interfaces.h"
#   include "../type_info/semantic.type_info.interfaces.h"
#
#include "gielib/giecom/giecom.guid.non_init.end.h"

#include "semantic.nodes.fucntion.specifiers.h"
//================================================================================================================================================
namespace gie_idl {

    // function/member function attribute category & attributes
    // {9C456B64-7EF8-4215-87AE-A0B1270BBBDC}
    GIE_CCOM_RAW_GUID(attr_cat_function, 0x9c456b64, 0x7ef8, 0x4215, 0x87, 0xae, 0xa0, 0xb1, 0x27, 0xb, 0xbb, 0xdc);

    //
    // function_attribute_i
    //
    // {562B7FF6-309E-4fa9-A0D0-1B5DEB78A279}
    GIE_CCOM_RAW_GUID(function_attribute_iid, 0x562b7ff6, 0x309e, 0x4fa9, 0xa0, 0xd0, 0x1b, 0x5d, 0xeb, 0x78, 0xa2, 0x79);
    struct function_attribute_i
        : ::gie::ccom::unknown_i
    {
    };
    typedef ::boost::intrusive_ptr<function_attribute_i> function_attribute_ptr_t;

    //
    // function_attribute_builder_i
    //
    // {A946483A-20BC-432d-BC12-766B986CED88}
    GIE_CCOM_RAW_GUID(function_attribute_builder_iid, 0xa946483a, 0x20bc, 0x432d, 0xbc, 0x12, 0x76, 0x6b, 0x98, 0x6c, 0xed, 0x88);
    struct function_attribute_builder_i
        : function_attribute_i
    {
        virtual void set_enable_specifier(const fucntion_specifier specifier)=0;
    };
    typedef ::boost::intrusive_ptr<function_attribute_builder_i> function_attribute_builder_ptr_t;
    
    //
    // function node types
    //

    // {D3288657-745F-48f3-A379-28F480F5C009}
    GIE_CCOM_RAW_GUID(type_function_parameters, 0xd3288657, 0x745f, 0x48f3, 0xa3, 0x79, 0x28, 0xf4, 0x80, 0xf5, 0xc0, 0x9);
    // {B949F074-8AE8-436f-9FB8-1E22084F96C2}
    GIE_CCOM_RAW_GUID(type_function, 0xb949f074, 0x8ae8, 0x436f, 0x9f, 0xb8, 0x1e, 0x22, 0x8, 0x4f, 0x96, 0xc2);


    //
    // function_parameters_i
    //
    // {467656FB-8541-4a1f-9688-D38FCA74AD51}
    GIE_CCOM_RAW_GUID(function_parameters_iid, 0x467656fb, 0x8541, 0x4a1f, 0x96, 0x88, 0xd3, 0x8f, 0xca, 0x74, 0xad, 0x51);
    struct function_parameters_i
        : node_i
    {
        virtual const node_i_ptr_t get_return_type() = 0;
        virtual void enumerate_parameters(named_node_enum_callback_i* const enumerator)=0;

    };
    typedef ::boost::intrusive_ptr<function_parameters_i> function_parameters_ptr_t;
    
    //
    // function_parameters_builder_i
    //
    // {813545D9-40CB-4bdf-9FD7-C5201D8407C4}
    GIE_CCOM_RAW_GUID(function_parameters_builder_iid, 0x813545d9, 0x40cb, 0x4bdf, 0x9f, 0xd7, 0xc5, 0x20, 0x1d, 0x84, 0x7, 0xc4);
    struct function_parameters_builder_i
        : function_parameters_i
    {
        virtual void push_back(const node_i_ptr_t& param) = 0;
        virtual void set_return_type(const node_i_ptr_t& param) = 0;
    };
    typedef ::boost::intrusive_ptr<function_parameters_builder_i> function_parameters_builder_ptr_t;

    //
    // function_i
    //
    // {AB2F88A0-5777-48d2-9C39-F1FA25CC9829}
    GIE_CCOM_RAW_GUID(function_iid, 0xab2f88a0, 0x5777, 0x48d2, 0x9c, 0x39, 0xf1, 0xfa, 0x25, 0xcc, 0x98, 0x29);
    struct function_i
        : node_i
    {
        //virtual const function_parameters_ptr_t get_parameters()=0;
        virtual const type_descriptor_ptr_t get_return_type() = 0;
        virtual const function_parameters_ptr_t get_parameters()=0;
    };
    typedef ::boost::intrusive_ptr<function_i> function_ptr_t;

    //
    // function_builder_i
    //
    // {AD5D2B68-7F5B-4751-9F3D-D27B4F1F2D31}
    GIE_CCOM_RAW_GUID(function_builder_iid,  0xad5d2b68, 0x7f5b, 0x4751, 0x9f, 0x3d, 0xd2, 0x7b, 0x4f, 0x1f, 0x2d, 0x31);
    struct function_builder_i
        : function_i
    {
        virtual void GIE_LIB_FASTCALL add(const node_i_ptr_t& function_info)=0;
    };
    typedef ::boost::intrusive_ptr<function_builder_i> function_builder_ptr_t;

}
GIE_CCOM_BIND_GUID(gie_idl::function_i, gie_idl::function_iid);
GIE_CCOM_BIND_GUID(gie_idl::function_builder_i, gie_idl::function_builder_iid);
GIE_CCOM_BIND_GUID(gie_idl::function_attribute_i, gie_idl::function_attribute_iid);
GIE_CCOM_BIND_GUID(gie_idl::function_attribute_builder_i, gie_idl::function_attribute_builder_iid);
GIE_CCOM_BIND_GUID(gie_idl::function_parameters_i, gie_idl::function_parameters_iid);
GIE_CCOM_BIND_GUID(gie_idl::function_parameters_builder_i, gie_idl::function_parameters_builder_iid);
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_NODES_FUCNTION_INTERFACES_H__01_06_2005__21_36_32
//================================================================================================================================================
