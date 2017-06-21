//================================================================================================================================================
//
// (c) GIE 09.05.2005
//
//================================================================================================================================================
// NAME: idl_backend.manager.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "idl_backend.manager.h"
//================================================================================================================================================
namespace gie_idl {


    void backend_dump_get_desc__(backend_options_description_t& desc);
    const backend::backend_interface_ptr_t backend_dump_create___();
    const backend_meta_info_t backend_dump_meta_info(wxT("dump"), wxT("Internal dumper"), backend_dump_get_desc__, backend_dump_create___);

    void backend_forward_resolver_dump_get_desc__(backend_options_description_t& desc);
    const backend::backend_interface_ptr_t backend_forward_resolver_dump_create___();
    const backend_meta_info_t backend_forward_resolver_dump_meta_info(wxT("fwddump"), wxT("Internal dumper with forward resolver"), backend_forward_resolver_dump_get_desc__, backend_forward_resolver_dump_create___);

    backends_manager_t::backends_manager_t()
    {
        typedef ::std::pair<iterator, bool> insert_result_t;

        { const insert_result_t& insert_result = insert( std::make_pair( backend_dump_meta_info.internal_name, &backend_dump_meta_info ) ); GIE_LIB_ASSERTE( insert_result.second ); }
        { const insert_result_t& insert_result = insert( std::make_pair( backend_forward_resolver_dump_meta_info.internal_name, &backend_forward_resolver_dump_meta_info ) ); GIE_LIB_ASSERTE( insert_result.second ); }
    }

    const backend::backend_interface_ptr_t backends_manager_t::create_back_end(const string_t& name)
    {
        backend_meta_info_t const* const meta_info = get_back_end_meta_info(name);
        if( !meta_info )
        {
            GIE_LIB_NOT_IMPLEMENTED_1("cannot create unknown back end");
        }
        return meta_info->create();
    }

}
//================================================================================================================================================
