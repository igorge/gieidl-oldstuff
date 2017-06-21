//================================================================================================================================================
//
// (c) GIE 26.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_NODES_SEMANTIC_TREE_HOLDER_INTERFACES_H__26_04_2005__21_31_34
#define H_GUARD_SEMANTIC_NODES_SEMANTIC_TREE_HOLDER_INTERFACES_H__26_04_2005__21_31_34
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.non_init.begin.h"
#
#   include "semantic.tree.core.interfaces.h"
#   include "semantic.nodes.late_bound.interfaces.h"
#
#include "gielib/giecom/giecom.guid.non_init.end.h"
//================================================================================================================================================
namespace gie_idl {
    
    //
    // late_boud_enum_callback_i
    //
    // {86DC31DE-5159-4f59-BD50-6FBEC5FA677E}
    GIE_CCOM_RAW_GUID(late_boud_enum_callback_iid, 0x86dc31de, 0x5159, 0x4f59, 0xbd, 0x50, 0x6f, 0xbe, 0xc5, 0xfa, 0x67, 0x7e);
    struct late_boud_enum_callback_i
        : ::gie::ccom::unknown_i
    {
        enum action_t { continue_enumeration=0, abort_enumeration, delete_this_item_and_continue};

        virtual action_t enumerate_this(late_bound_i* const late_bound)=0;
    };
    //
    // semantic_tree_holder_i
    //
    // {F53F137D-D996-4ba7-A341-7EC42631C0DA}
    GIE_CCOM_RAW_GUID(semantic_tree_holder_iid, 0xf53f137d, 0xd996, 0x4ba7, 0xa3, 0x41, 0x7e, 0xc4, 0x26, 0x31, 0xc0, 0xda);
    struct semantic_tree_holder_i
        : ::gie::ccom::unknown_i
    {
        //virtual void set_root_node(const boost::intrusive_ptr<node_i>& node)=0;
        virtual const boost::intrusive_ptr<node_i> get_root_node()=0;
        virtual void push_back_new_late_boud(late_bound_i* const late_bound)=0;
        virtual void enumerate_late_bound(late_boud_enum_callback_i* const enum_callback)=0;
        
        GIE_LIB_FORCE_INLINE
        void push_back_new_late_boud(const late_bound_ptr_t& late_bound)
        {
            push_back_new_late_boud( late_bound.get() );
        }
    };
    typedef boost::intrusive_ptr<semantic_tree_holder_i> semantic_tree_holder_ptr_t;

}
GIE_CCOM_BIND_GUID(gie_idl::semantic_tree_holder_i, gie_idl::semantic_tree_holder_iid);
GIE_CCOM_BIND_GUID(gie_idl::late_boud_enum_callback_i, gie_idl::late_boud_enum_callback_iid);
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_NODES_SEMANTIC_TREE_HOLDER_INTERFACES_H__26_04_2005__21_31_34
//================================================================================================================================================
