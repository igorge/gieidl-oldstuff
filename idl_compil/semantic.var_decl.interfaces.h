//================================================================================================================================================
//
// (c) GIE 26.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_VAR_DECL_INTERFACES_H__26_05_2005__21_46_47
#define H_GUARD_SEMANTIC_VAR_DECL_INTERFACES_H__26_05_2005__21_46_47
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.non_init.begin.h"
#
#   include "semantic.tree.core.interfaces.h"
#   include "type_info/semantic.type_info.interfaces.h"
#
#include "gielib/giecom/giecom.guid.non_init.end.h"
//================================================================================================================================================
namespace gie_idl {

    // {CAD34802-0BD3-4f4b-9D97-8DD9F71FCFF8}
    GIE_CCOM_RAW_GUID(type_var_decl, 0xcad34802, 0xbd3, 0x4f4b, 0x9d, 0x97, 0x8d, 0xd9, 0xf7, 0x1f, 0xcf, 0xf8);

    //
    // var_decl_i
    //
    // {D34AA683-8B97-4c23-915C-4C59C3BF17B1}
    GIE_CCOM_RAW_GUID(var_decl_iid, 0xd34aa683, 0x8b97, 0x4c23, 0x91, 0x5c, 0x4c, 0x59, 0xc3, 0xbf, 0x17, 0xb1);
    struct var_decl_i
        : node_i
    {
        virtual const type_descriptor_ptr_t get_type()=0;
    };
    typedef ::boost::intrusive_ptr<var_decl_i> var_decl_ptr_t;

    struct var_decl_builder_i
        : ::gie::ccom::unknown_i
    {
    };

}
GIE_CCOM_BIND_GUID(gie_idl::var_decl_i, gie_idl::var_decl_iid);
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_VAR_DECL_INTERFACES_H__26_05_2005__21_46_47
//================================================================================================================================================
