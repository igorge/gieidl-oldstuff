//================================================================================================================================================
//
// (c) GIE 08.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_ATTRIBUTES_INTERFACES_H__08_04_2005__23_15_42
#define H_GUARD_SEMANTIC_ATTRIBUTES_INTERFACES_H__08_04_2005__23_15_42
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.non_init.begin.h"
        #include "gielib/giecom/giecom.core.h"
        #include "guid_map.interfaces.h"
#include "gielib/giecom/giecom.guid.non_init.end.h"
//================================================================================================================================================
namespace gie_idl {

    typedef guid_map_i     attribute_repository_i;
    typedef guid_map_ptr_t attribute_repository_ptr_t;

    // {F09EF753-C029-49ce-B3F2-8C09E651C741}
    GIE_CCOM_RAW_GUID(attr_cat_access, 0xf09ef753, 0xc029, 0x49ce, 0xb3, 0xf2, 0x8c, 0x9, 0xe6, 0x51, 0xc7, 0x41);


    // {662F136D-7762-4d79-B8C7-FEB41F54C3D6}
    GIE_CCOM_RAW_GUID(access_attribute_iid, 0x662f136d, 0x7762, 0x4d79, 0xb8, 0xc7, 0xfe, 0xb4, 0x1f, 0x54, 0xc3, 0xd6);
    struct access_attribute_i
        : gie::ccom::unknown_i
    {
        virtual const gie::ccom::guid_t& get_access()const = 0;
    };

    //
    // attribute_repository_holder_i
    //
    // {FE2C07D7-212A-44ff-9512-4DCBEE02C467}
    GIE_CCOM_RAW_GUID(attribute_repository_holder_iid, 0xfe2c07d7, 0x212a, 0x44ff, 0x95, 0x12, 0x4d, 0xcb, 0xee, 0x2, 0xc4, 0x67);
    struct attribute_repository_holder_i
        : ::gie::ccom::unknown_i
    {
        virtual const attribute_repository_ptr_t set_new_repository(attribute_repository_i* const new_repository)=0;
        virtual const attribute_repository_ptr_t get_repository()=0;
        
        GIE_LIB_FORCE_INLINE
        const attribute_repository_ptr_t set_new_repository_ex(const attribute_repository_ptr_t& new_repository)
        {
            return set_new_repository( new_repository.get() );
        }
    };
    typedef ::boost::intrusive_ptr<attribute_repository_holder_i> attribute_repository_holder_ptr_t;

}

GIE_CCOM_BIND_GUID(gie_idl::access_attribute_i, gie_idl::access_attribute_iid);
GIE_CCOM_BIND_GUID(gie_idl::attribute_repository_holder_i, gie_idl::attribute_repository_holder_iid);

//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_ATTRIBUTES_INTERFACES_H__08_04_2005__23_15_42
//================================================================================================================================================
