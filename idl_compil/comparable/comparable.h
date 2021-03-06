//================================================================================================================================================
//
// (c) GIE 03.06.2005
//
//================================================================================================================================================
#ifndef H_GUARD_COMPARABLE_H__03_06_2005__20_16_18
#define H_GUARD_COMPARABLE_H__03_06_2005__20_16_18
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "comparable.interfaces.h"
//================================================================================================================================================
namespace gie_idl {
    template <class inteface1_t_t, class inteface2_t_t>
    inline
    bool is_equal(::boost::intrusive_ptr<inteface1_t_t> const & obj1, ::boost::intrusive_ptr<inteface2_t_t> const & obj2)
    {
        GIE_LIB_DEBUG_WARN_ASSERT( !::gie::ccom::is_same(obj1, obj2), "comparing same object");
        const comparable_ptr_t& left = ::gie::ccom::query_interface<comparable_i>( obj1 );
        if( !left )
        {
            GIE_LIB_NOT_IMPLEMENTED_1("'left'-part object does not support comparable_i");
        }
        return left->equals( obj2.get() );
    }
}
//================================================================================================================================================
#endif//H_GUARD_COMPARABLE_H__03_06_2005__20_16_18
//================================================================================================================================================
