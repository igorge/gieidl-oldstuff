//================================================================================================================================================
//
// (c) GIE 24.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_UTILITY_COUNTABLE_H__24_04_2005__23_43_14
#define H_GUARD_UTILITY_COUNTABLE_H__24_04_2005__23_43_14
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "boost/static_assert.hpp"
#include "boost/type_traits.hpp"
//================================================================================================================================================
namespace gie {
    //
    // ref counting support
    //


    //TODO: add static checks of correct inheritance
    template<
        class ancestor_t_t,
        class counter_t_t = unsigned int,
            counter_t_t initial_value_t_v = 0
    >
    struct ref_countable 
    {
        typedef ref_countable<ancestor_t_t, counter_t_t, initial_value_t_v> self_type;

        ref_countable()
            : counter_( initial_value_t_v )
        {
            typedef ::boost::is_base_and_derived<self_type, ancestor_t_t> is_self_ok;
            BOOST_STATIC_ASSERT( is_self_ok::value );
        }

        void add_ref()
        {
            ++counter_;
        }

        void release() throw()
        {
            --counter_;
            if( counter_==0 )
                delete static_cast<ancestor_t_t*>(this);
        }

    private:
        counter_t_t counter_;
    };

    template<class ancestor_t_t, class counter_t_t, counter_t_t initial_value_t_v>
        inline
        void intrusive_ptr_add_ref(ref_countable<ancestor_t_t, counter_t_t, initial_value_t_v>* const value)
    {
        value->add_ref();
    }

    template<class ancestor_t_t, class counter_t_t, counter_t_t initial_value_t_v>
        inline
        void intrusive_ptr_release(ref_countable<ancestor_t_t, counter_t_t, initial_value_t_v>* const value)
    {
        value->release();
    }

}
//================================================================================================================================================
#endif//H_GUARD_UTILITY_COUNTABLE_H__24_04_2005__23_43_14
//================================================================================================================================================
