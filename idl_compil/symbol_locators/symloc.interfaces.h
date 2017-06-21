//================================================================================================================================================
//
// (c) GIE 22.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SYMLOC_INTERFACES_H__22_05_2005__16_21_21
#define H_GUARD_SYMLOC_INTERFACES_H__22_05_2005__16_21_21
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.non_init.begin.h"

    #include "../semantic.tree.core.interfaces.h"
    #include "../semantic.nodes.fq_id.h"

#include "gielib/giecom/giecom.guid.non_init.end.h"
//================================================================================================================================================
namespace gie_idl {

    typedef ::gie::ccom::guid_t resolver_id_t;
    //
    // predefined resolvers
    //
    // {89D6E527-34E7-4d96-947C-E8B4CDA6E3B0}
    GIE_CCOM_RAW_GUID(ambiguity_resolver_aggregate, 0x89d6e527, 0x34e7, 0x4d96, 0x94, 0x7c, 0xe8, 0xb4, 0xcd, 0xa6, 0xe3, 0xb0);

    // {40AE327B-1AFC-4a74-8DA0-B7EA7BAB2C9E}
    GIE_CCOM_RAW_GUID(ambiguity_resolver_symbol_locator, 0x40ae327b, 0x1afc, 0x4a74, 0x8d, 0xa0, 0xb7, 0xea, 0x7b, 0xab, 0x2c, 0x9e);

    //
    // ambiguity_resolver_i
    //
    // {B274FF2C-2E07-4cc7-922E-E01C9F22D94A}
    GIE_CCOM_RAW_GUID(ambiguity_resolver_iid, 0xb274ff2c, 0x2e07, 0x4cc7, 0x92, 0x2e, 0xe0, 0x1c, 0x9f, 0x22, 0xd9, 0x4a);
    struct ambiguity_resolver_i
        : ::gie::ccom::unknown_i
    {
        virtual void GIE_LIB_FASTCALL begin(::gie::ccom::unknown_i* const context = NULL)=0;
        virtual void GIE_LIB_FASTCALL end()throw()=0;
        virtual void GIE_LIB_FASTCALL candidate(node_i* const node)=0;
        virtual const node_i_ptr_t GIE_LIB_FASTCALL best_candidate()=0;
    };
    typedef ::boost::intrusive_ptr<ambiguity_resolver_i> ambiguity_resolver_ptr_t;

    //
    // symbol_locator_i
    //
    // {0425F197-EB5A-4e9d-B68A-2B5C4B5E970D}
    GIE_CCOM_RAW_GUID(symbol_locator_iid, 0x425f197, 0xeb5a, 0x4e9d, 0xb6, 0x8a, 0x2b, 0x5c, 0x4b, 0x5e, 0x97, 0xd);
    struct symbol_locator_i
        : ::gie::ccom::unknown_i
    {
        virtual const node_i_ptr_t locate_symbol(node_i* const referrers_scope, const fq_id_ptr_t& id, node_i* const root, const resolver_id_t& resolver_id, ::gie::ccom::unknown_i* const resolver_context = 0)=0;
    };
    typedef ::boost::intrusive_ptr<symbol_locator_i> symbol_locator_ptr_t;

}
GIE_CCOM_BIND_GUID(gie_idl::ambiguity_resolver_i, gie_idl::ambiguity_resolver_iid);
GIE_CCOM_BIND_GUID(gie_idl::symbol_locator_i, gie_idl::symbol_locator_iid);
//================================================================================================================================================
#endif//H_GUARD_SYMLOC_INTERFACES_H__22_05_2005__16_21_21
//================================================================================================================================================
