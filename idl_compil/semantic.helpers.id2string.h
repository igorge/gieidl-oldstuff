//================================================================================================================================================
//
// (c) GIE 26.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_HELPERS_ID2STRING_H__26_04_2005__23_10_42
#define H_GUARD_SEMANTIC_HELPERS_ID2STRING_H__26_04_2005__23_10_42
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "semantic.nodes.fq_id.h"
#include <algorithm>
//================================================================================================================================================
namespace gie_idl {

    namespace impl {

        struct make_id_str_fq_t
            : std::unary_function<string_t, void>
        {
            explicit make_id_str_fq_t(string_t& str)
                : str_( str )
            {}

            void operator()(const string_t& str)const
            {
                if( str.empty() ) return;

                str_.reserve( str.size()+str_.size()+2 );
                str_.append( wxT("::") );
                str_.append( str );
            }

            string_t& get_str()const throw(){ return str_;}
        
        private:
            string_t& str_;
        };

        struct make_id_str_non_fq_t
            : std::unary_function<string_t, void>
        {
            make_id_str_non_fq_t(string_t& str)
                : str_( str )
                , first_( true )
            {}

            void operator()(const string_t& str)
            {
                GIE_LIB_ASSERTE( !str.empty() );

                str_.reserve( str.size()+str_.size()+2 );
                if( first_ )
                    first_ = false;
                else
                    str_.append( wxT("::") );

                str_.append( str );
            }

            string_t& get_str()const throw(){ return str_;}
        
        private:
            string_t& str_;
            bool first_;
        };
    } // end of namespace impl

    inline
    const string_t map_id2string(const fq_id_ptr_t& id)
    {
        string_t str_accum;
        if( id->is_fq() )
        {
            impl::make_id_str_fq_t str_maker(str_accum);
            return std::for_each(id->begin(), id->end(), str_maker ).get_str();
        }
        else
        {
            impl::make_id_str_non_fq_t str_maker(str_accum);
            return std::for_each(id->begin(), id->end(), str_maker ).get_str();
        }

    }
}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_HELPERS_ID2STRING_H__26_04_2005__23_10_42
//================================================================================================================================================
