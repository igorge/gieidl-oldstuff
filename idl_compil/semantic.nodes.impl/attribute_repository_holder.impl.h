//================================================================================================================================================
//
// (c) GIE 07.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_ATTRIBUTE_REPOSITORY_HOLDER_IMPL_H__07_05_2005__16_59_28
#define H_GUARD_ATTRIBUTE_REPOSITORY_HOLDER_IMPL_H__07_05_2005__16_59_28
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../semantic.attributes.interfaces.h"
//================================================================================================================================================
namespace gie_idl { namespace impl {

    struct attribute_repository_holder_impl_t
        : attribute_repository_holder_i
    {
        const attribute_repository_ptr_t set_new_repository(attribute_repository_i* const new_repository)
        {
            attribute_repository_ptr_t new_repo (new_repository) ;
            new_repo.swap( repo_ );
            return new_repo; //return old repo
        }

        const attribute_repository_ptr_t get_repository()
        {
            return repo_;
        }

    private:
        attribute_repository_ptr_t repo_;
    };
} }
//================================================================================================================================================
#endif//H_GUARD_ATTRIBUTE_REPOSITORY_HOLDER_IMPL_H__07_05_2005__16_59_28
//================================================================================================================================================
