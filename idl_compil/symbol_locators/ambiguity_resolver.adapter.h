//================================================================================================================================================
//
// (c) GIE 05.06.2005
//
//================================================================================================================================================
#ifndef H_GUARD_AMBIGUITY_RESOLVER_ADAPTER_H__05_06_2005__19_39_10
#define H_GUARD_AMBIGUITY_RESOLVER_ADAPTER_H__05_06_2005__19_39_10
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "symloc.interfaces.h"
#include "gielib/giecom/giecom.server.stackbased.simple.h"
//================================================================================================================================================
namespace gie_idl{

    struct enum_to_ambiguity_resolver_adapter_t
        : ::gie::ccom::stack_based_simple_unknown_impl_t<named_node_enum_callback_i>
    {
        enum_to_ambiguity_resolver_adapter_t(const ambiguity_resolver_ptr_t& ambiguity_resolver, ::gie::ccom::unknown_i* const  resolver_context)
            : ambiguity_resolver_( ambiguity_resolver )
  //          , resolver_context_( resolver_context )
        {
            ambiguity_resolver_->begin( resolver_context );
        }

        ~enum_to_ambiguity_resolver_adapter_t()throw()
        {
            ambiguity_resolver_->end();
        }

        virtual action_t enumerate_this(node_i* const node, const string_t& name)
        {
            ambiguity_resolver_->candidate( node );
            return continue_enumeration;
        }
        const node_i_ptr_t GIE_LIB_FASTCALL best_candidate()
        {
            return ambiguity_resolver_-> best_candidate();
        }
    private:
        const ambiguity_resolver_ptr_t ambiguity_resolver_;
//        ::gie::ccom::unknown_i* const  resolver_context_;
    };
}
//================================================================================================================================================
#endif//H_GUARD_AMBIGUITY_RESOLVER_ADAPTER_H__05_06_2005__19_39_10
//================================================================================================================================================
