//================================================================================================================================================
//
// (c) GIE 04.03.2005
//
//================================================================================================================================================
#ifndef H_GUARD_IDL_TOKEN_H__04_03_2005__6_11_02
#define H_GUARD_IDL_TOKEN_H__04_03_2005__6_11_02
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "idl_countable_string.h"
//#include "antlr/TokenStream.hpp"
#include "antlr/CommonToken.hpp"
//================================================================================================================================================
namespace gie_idl {
    
    struct extended_token_t
        : public antlr::CommonToken
    {

        static antlr::RefToken factory()
        {
            return antlr::RefToken ( new extended_token_t );
        }
        void set_file_name(ref_countable_string_ptr_t& file_name)
        {
            file_name_ = file_name;
        }
        const ref_countable_string_ptr_t& get_file_name()
        {
            return file_name_;
        }
    private:
        ref_countable_string_ptr_t file_name_;
    };

}
//================================================================================================================================================
#endif//H_GUARD_IDL_TOKEN_H__04_03_2005__6_11_02
//================================================================================================================================================
