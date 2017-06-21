//================================================================================================================================================
//
// (c) GIE 16.03.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_TREE_INTERFACES_H__16_03_2005__19_54_34
#define H_GUARD_SEMANTIC_TREE_INTERFACES_H__16_03_2005__19_54_34
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.non_init.begin.h"

    #include "semantic.tree.core.interfaces.h"
    #include "semantic.nodes.aggregate.interfaces.h"
    #include "semantic.nodes.late_bound.interfaces.h"

    #include "gielib/giecom/giecom.core.h"

    #include "gielib/giecom/iterators/giecom.iterators.interfaces.h"
    #include "gielib/giecom/containers/giecom.list.interfaces.h"

    #include "boost/intrusive_ptr.hpp"
    #include "boost/tuple/tuple.hpp"

#include "gielib/giecom/giecom.guid.non_init.end.h"
//================================================================================================================================================
namespace gie_idl {



    //
    // namespace_i
    //
    struct namespace_i;
    typedef std::pair<boost::intrusive_ptr<namespace_i>,const bool> create_namespace_result_t;
    // {6717ACD0-4BD2-4a0c-BC5A-14C3EEC1E6F0}
    GIE_CCOM_RAW_GUID(namespace_iid, 0x6717acd0, 0x4bd2, 0x4a0c, 0xbc, 0x5a, 0x14, 0xc3, 0xee, 0xc1, 0xe6, 0xf0);
    struct namespace_i
        : named_collection_i
    {
        virtual const create_namespace_result_t create_inner_namespace(const string_t& name)=0;
    };
    typedef ::boost::intrusive_ptr<namespace_i> namespace_ptr_t;


    //
    // multi_symbol
    //
    // {551AD926-C4A7-42da-BAA2-67DE5458B0C5}
    GIE_CCOM_RAW_GUID(multi_symbol_iid, 0x551ad926, 0xc4a7, 0x42da, 0xba, 0xa2, 0x67, 0xde, 0x54, 0x58, 0xb0, 0xc5);
    struct multi_symbol_i
        : node_i
    {
        virtual const gie::ccom::guid_t& contains()const throw()=0;
    };
    //iterator interfaces
    typedef ::gie::ccom::forward_iterator_i< boost::intrusive_ptr<node_i> >  iterator_for_node_i;
    // {C4664CC1-C3A3-42b6-8958-903583678513}
    GIE_CCOM_RAW_GUID(iterator_for_node_iid, 0xc4664cc1, 0xc3a3, 0x42b6, 0x89, 0x58, 0x90, 0x35, 0x83, 0x67, 0x85, 0x13);
    typedef ::gie::ccom::forward_iteratable_i< boost::intrusive_ptr<node_i> > iteratable_over_node_i;
    // {DEBFB031-3A66-41d4-AA01-79015DA1FD7E}
    GIE_CCOM_RAW_GUID(iteratable_over_node_iid, 0xdebfb031, 0x3a66, 0x41d4, 0xaa, 0x1, 0x79, 0x1, 0x5d, 0xa1, 0xfd, 0x7e);

}

GIE_CCOM_BIND_GUID(gie_idl::multi_symbol_i, gie_idl::multi_symbol_iid);
GIE_CCOM_BIND_GUID(gie_idl::iterator_for_node_i, gie_idl::iterator_for_node_iid);
GIE_CCOM_BIND_GUID(gie_idl::iteratable_over_node_i, gie_idl::iteratable_over_node_iid);

GIE_CCOM_BIND_GUID(gie_idl::namespace_i, gie_idl::namespace_iid);
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_TREE_INTERFACES_H__16_03_2005__19_54_34
//================================================================================================================================================
