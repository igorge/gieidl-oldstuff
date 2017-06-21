//================================================================================================================================================
//
// (c) GIE 29.03.2005
//
//================================================================================================================================================
#ifndef H_GUARD_GUID_MAP_INTERFACES_H__29_03_2005__21_44_48
#define H_GUARD_GUID_MAP_INTERFACES_H__29_03_2005__21_44_48
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.core.h"
#include "gielib/giecom/giecom.client.h"

#include "boost/intrusive_ptr.hpp"
#include "boost/tuple/tuple.hpp"
//================================================================================================================================================
namespace gie_idl {

    
    typedef boost::tuple<const boost::intrusive_ptr<gie::ccom::unknown_i>&, const bool> guid_map_i_insert_result_t;
    // {996FEC66-D4A0-4e39-A5AF-52902A3B8FB8}
    GIE_CCOM_RAW_GUID(guid_map_iid, 0x996fec66, 0xd4a0, 0x4e39, 0xa5, 0xaf, 0x52, 0x90, 0x2a, 0x3b, 0x8f, 0xb8);
    struct guid_map_i
        : gie::ccom::unknown_i
    {
        virtual const guid_map_i_insert_result_t insert(const gie::ccom::guid_t& key, const boost::intrusive_ptr<gie::ccom::unknown_i>& unknown)=0;
        virtual const boost::intrusive_ptr<gie::ccom::unknown_i> operator[](const gie::ccom::guid_t& key)const=0;
    };
    typedef ::boost::intrusive_ptr<guid_map_i> guid_map_ptr_t;

}

GIE_CCOM_BIND_GUID(gie_idl::guid_map_i, gie_idl::guid_map_iid);
//================================================================================================================================================
#endif//H_GUARD_GUID_MAP_INTERFACES_H__29_03_2005__21_44_48
//================================================================================================================================================
