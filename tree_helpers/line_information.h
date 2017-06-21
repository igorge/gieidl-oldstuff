//================================================================================================================================================
//
// (c) GIE 27.02.2005
//
//================================================================================================================================================
#ifndef H_GUARD_LINE_INFORMATION_H__27_02_2005__15_49_10
#define H_GUARD_LINE_INFORMATION_H__27_02_2005__15_49_10
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../idl_compil/idl_countable_string.h"

#include <map>
//================================================================================================================================================
namespace gie_idl {

    struct line_information_t
    {
        line_information_t(const ref_countable_string_ptr_t& file_name, const unsigned int line_no, const unsigned int column_no)
            : file_name_( file_name )
            , line_no_( line_no )
            , column_no_( column_no )
        {}
    private:
        ref_countable_string_ptr_t  file_name_;
        unsigned int                line_no_;
        unsigned int                column_no_;
    };
    typedef std::auto_ptr<line_information_t> line_information_auto_ptr_t;


    struct string_table_t
    {
        ref_countable_string_ptr_t& ref_count_string(const string_t& str)
        {
            insert_result_t_& r = string_table_.insert( std::make_pair(str,ref_countable_string_ptr_t() ) );
            if( r.second ) //if inserted new element
            {
                r.first->second =  new ref_countable_string_t(str) ;
            }

            return r.first->second;
        }

    private:
        typedef std::map<string_t, ref_countable_string_ptr_t>      string_table_t_;
        typedef std::pair<typedef string_table_t_::iterator, bool>  insert_result_t_;

        string_table_t_ string_table_;
    };

}
//================================================================================================================================================
#endif//H_GUARD_LINE_INFORMATION_H__27_02_2005__15_49_10
//================================================================================================================================================
