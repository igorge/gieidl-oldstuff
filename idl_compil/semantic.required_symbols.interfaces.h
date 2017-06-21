//================================================================================================================================================
//
// (c) GIE 03.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_REQUIRED_SYMBOLS_INTERFACES_H__03_05_2005__16_53_36
#define H_GUARD_SEMANTIC_REQUIRED_SYMBOLS_INTERFACES_H__03_05_2005__16_53_36
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.non_init.begin.h"

#include "semantic.tree.core.interfaces.h"
#include "boost/intrusive_ptr.hpp"

#include "gielib/giecom/giecom.guid.non_init.end.h"
//================================================================================================================================================
namespace gie_idl {

    // {CF80E9EC-D759-4e1e-AB52-2630674FF490}
    GIE_CCOM_RAW_GUID(required_symbol_enum_callback_iid, 0xcf80e9ec, 0xd759, 0x4e1e, 0xab, 0x52, 0x26, 0x30, 0x67, 0x4f, 0xf4, 0x90);
    struct required_symbol_enum_callback_i
        : ::gie::ccom::unknown_i
    {
        virtual void enumerate_this_required_symbol(node_i* const node, const bool is_forward_only_ok)=0;
    };
    typedef ::boost::intrusive_ptr<required_symbol_enum_callback_i> nrequired_symbol_enum_callback_ptr_t;

    // {A747BE36-365B-46d8-B706-52D0CC2D406E}
    GIE_CCOM_RAW_GUID(required_symbols_iid, 0xa747be36, 0x365b, 0x46d8, 0xb7, 0x6, 0x52, 0xd0, 0xcc, 0x2d, 0x40, 0x6e);
    struct required_symbols_i
        : ::gie::ccom::unknown_i
    {
        virtual void enumerate_required_symbols(required_symbol_enum_callback_i*const enumerator)=0;
    };
    typedef ::boost::intrusive_ptr<required_symbols_i> required_symbols_ptr_t;
}

GIE_CCOM_BIND_GUID(gie_idl::required_symbols_i, gie_idl::access_attribute_iid);
GIE_CCOM_BIND_GUID(gie_idl::required_symbol_enum_callback_i, gie_idl::required_symbol_enum_callback_iid);

//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_REQUIRED_SYMBOLS_INTERFACES_H__03_05_2005__16_53_36
//================================================================================================================================================
