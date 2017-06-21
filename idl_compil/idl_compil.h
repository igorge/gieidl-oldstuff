//================================================================================================================================================
//
// (c) GIE 02.03.2005
//
//================================================================================================================================================
#ifndef H_GUARD_IDL_COMPIL_H__02_03_2005__17_22_23
#define H_GUARD_IDL_COMPIL_H__02_03_2005__17_22_23
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../idl_backend/idl_backend.h"
#include "idl_token.h"

#include "../tree_helpers/line_information.h"

#include "semantic.nodes.late_bound.interfaces.h"
#include "semantic.nodes.semantic_tree_holder.interfaces.h"

#include "gielib/giecom/giecom.server.stackbased.simple.h"
#include "../idl_param/param.core.h"

#include "boost/tuple/tuple.hpp"
//================================================================================================================================================
namespace gie_idl {

    struct compil_t
    {
        //
        // notification interface
        //
        struct notify_i
        {
            typedef ::boost::tuple<const bool, const bool> bool2_t;
            virtual bool before_building_ast() { return true; }
            virtual bool before_building_semantic_tree() { return true; }
            
            virtual const bool2_t before_process_unbound_symbols(const unsigned int iteration) { return bool2_t(true,true); }
            virtual bool after_process_unbound_symbols() { return true; }
            virtual bool process_unbound_symbols(late_bound_i* const late_bound){ return true; }
            
            virtual bool before_rebind(){ return true; }

            virtual bool before_backend(){ return true; }
            virtual bool after_backend(){ return true; }

            virtual void done(){ }
        };

        compil_t( std::istream& char_stream
            , const backend::backend_interface_ptr_t& idl_backend
            , const options_ptr_t& options
            , notify_i* const listener = NULL
            )
            : char_stream_( char_stream )
            , listeners_( &dummy_notifier_ )
            , idl_backend_( idl_backend )
            , options_( options )
        {
            if(listener)
            {
                listeners_ = listener;
            }
        }

        bool compile();

        
    private:
        
        bool process_unbound_symbols_(const semantic_tree_holder_ptr_t& sh, const unsigned int iteration);

        std::istream& char_stream_;
        notify_i* listeners_;

        notify_i dummy_notifier_;
        backend::backend_interface_ptr_t idl_backend_;
        const options_ptr_t& options_;

    };
}
//================================================================================================================================================
#endif//H_GUARD_IDL_COMPIL_H__02_03_2005__17_22_23
//================================================================================================================================================
