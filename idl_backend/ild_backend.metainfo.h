//================================================================================================================================================
//
// (c) GIE 09.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_ILD_BACKEND_METAINFO_H__09_05_2005__19_49_59
#define H_GUARD_ILD_BACKEND_METAINFO_H__09_05_2005__19_49_59
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "idl_backend.h"
#include "../idl_param/param.core.h"
//================================================================================================================================================
namespace gie_idl {

    struct backend_meta_info_t
    {
        typedef void (*get_options_description_func_t)(backend_options_description_t& desc);
        typedef const backend::backend_interface_ptr_t (*create_t)();

        backend_meta_info_t(const string_t& internal_name_p, const string_t&  description_p, get_options_description_func_t get_options_description_p, const create_t create_p)
            : internal_name ( internal_name_p )
            , description( description_p )
            , get_options_description( get_options_description_p )
            , create ( create_p )
        {};

        const string_t  internal_name;
        const string_t  description;
        const get_options_description_func_t get_options_description;
        const create_t create;
    };

}
//================================================================================================================================================
#endif//H_GUARD_ILD_BACKEND_METAINFO_H__09_05_2005__19_49_59
//================================================================================================================================================
