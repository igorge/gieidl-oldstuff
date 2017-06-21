//================================================================================================================================================
//
// (c) GIE 04.03.2005
//
//================================================================================================================================================
#ifndef H_GUARD_IDL_COUNTABLE_STRING_H__04_03_2005__6_14_41
#define H_GUARD_IDL_COUNTABLE_STRING_H__04_03_2005__6_14_41
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "gielib/core/num_capacity.h"
#include "boost/intrusive_ptr.hpp"

#include "utility.countable.h"
//================================================================================================================================================
namespace gie_idl {

    struct ref_countable_string_t
        : public gie::ref_countable<ref_countable_string_t>
        , public string_t
    {
        ref_countable_string_t(const string_t& value)
            : string_t( value )
        {}

        ref_countable_string_t(const string_t::value_type* const value)
            : string_t( value )
        {}

        bool operator<(const ref_countable_string_t& r)const throw()
        {
            //compare string content
            if( this == &r ) return false;
            return ( static_cast<const string_t&>(*this) < static_cast<const string_t&>(r) );
        }

    };
    typedef boost::intrusive_ptr<ref_countable_string_t> ref_countable_string_ptr_t;

    inline
    ref_countable_string_ptr_t new_string(const string_t::value_type* const value )
    {
        return ref_countable_string_ptr_t( new ref_countable_string_t(value) );
    }

    inline
    bool operator<(const ref_countable_string_ptr_t& l, const ref_countable_string_ptr_t& r)
    {
        return (*l < *r);
    }

}
//================================================================================================================================================
#endif//H_GUARD_IDL_COUNTABLE_STRING_H__04_03_2005__6_14_41
//================================================================================================================================================
