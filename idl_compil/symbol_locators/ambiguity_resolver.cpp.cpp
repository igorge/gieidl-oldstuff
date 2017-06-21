//================================================================================================================================================
//
// (c) GIE 04.06.2005
//
//================================================================================================================================================
// NAME: ambiguity_resolver.cpp.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "symloc.interfaces.h"

#include "gielib/giecom/giecom.server.h"
//================================================================================================================================================
namespace gie_idl {

    typedef gie::ccom::list<ambiguity_resolver_i> ambiguity_resolver_aggregate_interfaces_t;

    struct ambiguity_resolver_aggregate_impl_t
        : gie::ccom::c_object_root_t
        <
            ambiguity_resolver_aggregate_impl_t,           //self type
            ambiguity_resolver_i ,               //unknown from this interface
            ambiguity_resolver_aggregate_interfaces_t     //supported interfaces
        >
    {
        void GIE_LIB_FASTCALL begin(::gie::ccom::unknown_i* const context)
        {
            GIE_LIB_ASSERTE( !context );
            if( current_ ) current_=NULL;
        }
        void GIE_LIB_FASTCALL end()throw()
        {
            if( current_ ) current_=NULL;
        }
        void GIE_LIB_FASTCALL candidate(node_i* const node)
        {
            if( current_ )
            {
                GIE_LIB_NOT_IMPLEMENTED_1("aggregate can't have multiple defs");
            }

            current_ = node;
        }
        const node_i_ptr_t GIE_LIB_FASTCALL best_candidate()
        {
            return current_;
        }
    private:
        node_i_ptr_t current_;
    };

    typedef gie::ccom::c_object_t<ambiguity_resolver_aggregate_impl_t> ambiguity_resolver_aggregate_ccom;


    const ambiguity_resolver_ptr_t create_ambiguity_resolver_aggregate()
    {
        return ambiguity_resolver_ptr_t( ambiguity_resolver_aggregate_ccom::create<ambiguity_resolver_i>(), false );
    }

    //
    //
    //
    //
    //
    //

    typedef gie::ccom::list<ambiguity_resolver_i> ambiguity_resolver_symbol_locator_interfaces_t;

    struct ambiguity_resolver_symbol_locator_impl_t
        : gie::ccom::c_object_root_t
        <
            ambiguity_resolver_symbol_locator_impl_t,           //self type
            ambiguity_resolver_i ,               //unknown from this interface
            ambiguity_resolver_symbol_locator_interfaces_t     //supported interfaces
        >
    {
        ambiguity_resolver_symbol_locator_impl_t()
            : locked_( false )
        {}

        void GIE_LIB_FASTCALL begin(::gie::ccom::unknown_i* const context)
        {
            GIE_LIB_ASSERTE( !locked_ );
            locked_ = true;
            GIE_LIB_ASSERTE( !context );
            if( current_ ) current_=NULL;
        }
        void GIE_LIB_FASTCALL end()throw()
        {
            GIE_LIB_ASSERTE( locked_ );
            if( current_ ) current_=NULL;
            locked_ = false;
        }
        void GIE_LIB_FASTCALL candidate(node_i* const node)
        {
            GIE_LIB_ASSERTE( locked_ );
            if( current_ )
            {
                GIE_LIB_NOT_IMPLEMENTED_1("aggregate or namespace can't have multiple defs");
            }

            current_ = node;
        }
        const node_i_ptr_t GIE_LIB_FASTCALL best_candidate()
        {
            GIE_LIB_ASSERTE( locked_ );
            return current_;
        }
    private:
        node_i_ptr_t current_;

        bool locked_;
    };

    typedef gie::ccom::c_object_t<ambiguity_resolver_symbol_locator_impl_t> ambiguity_resolver_symbol_locator_ccom;


    const ambiguity_resolver_ptr_t create_ambiguity_resolver_symbol_locator()
    {
        return ambiguity_resolver_ptr_t( ambiguity_resolver_symbol_locator_ccom::create<ambiguity_resolver_i>(), false );
    }




}
//================================================================================================================================================
