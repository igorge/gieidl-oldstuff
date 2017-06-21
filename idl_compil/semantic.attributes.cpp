//================================================================================================================================================
//
// (c) GIE 08.04.2005
//
//================================================================================================================================================
// NAME: semantic.attributes.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.init.h"

#include "semantic.attributes.interfaces.h"

#include "gielib/giecom/giecom.guid.init.end.h"

#include "gielib/giecom/giecom.guid.core.h"
#include "gielib/giecom/giecom.server.h"
#include "gielib/giecom/giecom.client.h"

#include "semantic.attributes.h"
//================================================================================================================================================
namespace gie_idl {

    typedef gie::ccom::list<access_attribute_i> access_attribute_interfaces_t;
    
    struct access_attribute_impl_t
        : gie::ccom::c_object_root_t
          <
             access_attribute_impl_t, //self type
             access_attribute_i ,               //unknown from this interface
             access_attribute_interfaces_t,   //supported interfaces
             gie::ccom::counter_impl_t<>
          >
    {
        access_attribute_impl_t(const gie::ccom::guid_t& access)
            : access_( access )
        {
            if ( access_!=access_public && access_!=access_protected && access_!=access_private ) // i know, this is stupid
            {
                GIE_LIB_NOT_IMPLEMENTED;
            }
        }

        const gie::ccom::guid_t& get_access()const
        {
            return access_;
        }

    private:
        const gie::ccom::guid_t access_;
    };


    typedef gie::ccom::c_object_t<access_attribute_impl_t> access_attribute_c;


    access_attribute_ptr_t create_access_attrubute(const gie::ccom::guid_t& access)
    {
        return access_attribute_ptr_t( access_attribute_c::create<access_attribute_i>(access), false );
    }

}
//================================================================================================================================================
