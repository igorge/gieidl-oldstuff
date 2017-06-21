//================================================================================================================================================
//
// (c) GIE 08.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_ATTRIBUTES_H__08_04_2005__23_11_56
#define H_GUARD_SEMANTIC_ATTRIBUTES_H__08_04_2005__23_11_56
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "semantic.helpers.get_node_name.h"

#include "guid_map.factory.h"

#include "semantic.attributes.interfaces.h"
//================================================================================================================================================
namespace gie_idl {
    
    typedef boost::intrusive_ptr<access_attribute_i> access_attribute_ptr_t;

    access_attribute_ptr_t create_access_attrubute(const gie::ccom::guid_t& access);

    inline
    attribute_repository_ptr_t create_attribute_repository(attribute_repository_i*const existing_repository = NULL)
    {   GIE_IDL_ST_TRACE_FUNC;

        return 
            existing_repository
                ? attribute_repository_ptr_t(existing_repository)
                : create_guid_map();
    }

    inline
    void set_access_attribute(const attribute_repository_ptr_t& attr_repo, const gie::ccom::guid_t& access)
    {   GIE_IDL_ST_TRACE_FUNC;

        if( !attr_repo )
        {
            //fail if attr_repo is null
            GIE_LIB_NOT_IMPLEMENTED;
        }

        const boost::intrusive_ptr<gie::ccom::unknown_i>& access_category_unknown = (*attr_repo)[attr_cat_access];
        
        if( access_category_unknown.get() )
        {
            //fail if access attribute is already set
            GIE_LIB_NOT_IMPLEMENTED;
        }
        else
        {
            access_attribute_ptr_t attr = create_access_attrubute(access);
            if( !attr_repo->insert( attr_cat_access, attr ).get<1>() )
            {
                //fail if not inserted for some unknown reason
                GIE_LIB_NOT_IMPLEMENTED;
            }
        }

    }

    inline
    const access_t get_access( ::gie::ccom::unknown_i* const node, const access_t& default_access /*returrned if no access category present*/)
    {
        GIE_LIB_IS_VALID_POINTER(node);
        #ifdef GIE_LIB_DEBUG
            const string_t&  debug_node_name = get_node_name_no__fail(node);
        #endif

        const attribute_repository_holder_ptr_t& node_as_repo_holder = ::gie::ccom::query_interface<attribute_repository_holder_i>(node);
        if( !node_as_repo_holder ) return default_access;
        
        const attribute_repository_ptr_t& attr_repo = node_as_repo_holder->get_repository();
        if( !attr_repo ) return default_access;

        const boost::intrusive_ptr<gie::ccom::unknown_i>& access_category_unknown = (*attr_repo)[attr_cat_access];
        if( !access_category_unknown ) return default_access;

        const access_attribute_ptr_t& access_category = gie::ccom::query_interface_<access_attribute_i>(access_category_unknown, gie::ccom::throw_on_fail() );
        return access_category->get_access();
    }

    template <class T>
    inline
    const access_t get_access( ::boost::intrusive_ptr<T>const & node, const access_t& default_access)
    {
        return get_access( node.get(), default_access );
    }

    template <class interface_t_t>
        inline void set_attribute_repository(const ::boost::intrusive_ptr<interface_t_t>& unknown, const attribute_repository_ptr_t& new_repo)
    {
        GIE_LIB_IS_VALID_POINTER( new_repo.get() );
        #ifdef GIE_LIB_DEBUG
            const string_t& debug__node_name = get_node_name_no__fail( unknown );
        #endif

        const attribute_repository_holder_ptr_t& unknown_as_repo_holder = ::gie::ccom::query_interface_<attribute_repository_holder_i>( unknown, ::gie::ccom::throw_on_fail() );
        const attribute_repository_ptr_t& old_repo = unknown_as_repo_holder->set_new_repository_ex( new_repo );
        if( old_repo )
        {
            GIE_LIB_NOT_IMPLEMENTED;
        }

    }

}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_ATTRIBUTES_H__08_04_2005__23_11_56
//================================================================================================================================================
