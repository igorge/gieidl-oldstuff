//================================================================================================================================================
//
// (c) GIE 29.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_IDL_BACKEND_H__29_04_2005__16_24_36
#define H_GUARD_IDL_BACKEND_H__29_04_2005__16_24_36
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../idl_compil/semantic.nodes.semantic_tree_holder.interfaces.h"

#include "../idl_param/param.core.h"
#include "../idl_compil/utility.countable.h"
#include "../idl_compil/semantic.nodes.semantic_tree_holder.interfaces.h"
#include <ostream>
#include <memory>
#include "boost/noncopyable.hpp"
//================================================================================================================================================
namespace gie_idl { namespace backend {

    struct storage_inteface
    {
        typedef std::auto_ptr<std::ostream> ostream_ptr_t;
        virtual ostream_ptr_t create_ostream(const string_t& name, const bool binary = false) 
        { //this is here temporaliry
            ostream_ptr_t output( new std::ofstream( name.c_str(), binary?std::ios::binary:0 ) );
            if( !(*output) )
            {
                GIE_LIB_NOT_IMPLEMENTED_1("failed to open file");
            }
            return output;
        }
    };

    struct backend_interface
        : ::boost::noncopyable
        , ::gie::ref_countable<backend_interface>
    {
        virtual void exec( const semantic_tree_holder_ptr_t& tree_holder, storage_inteface& storage, const options_ptr_t& options)=0;
        virtual ~backend_interface(){};
    };
    typedef ::boost::intrusive_ptr<backend_interface> backend_interface_ptr_t;

} }
//================================================================================================================================================
#endif//H_GUARD_IDL_BACKEND_H__29_04_2005__16_24_36
//================================================================================================================================================
