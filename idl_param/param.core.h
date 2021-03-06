//================================================================================================================================================
//
// (c) GIE 08.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_PARAM_CORE_H__08_05_2005__20_05_44
#define H_GUARD_PARAM_CORE_H__08_05_2005__20_05_44
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../idl_compil/utility.countable.h"
#include "boost/intrusive_ptr.hpp"
#include "boost/program_options/variables_map.hpp"
#include "boost/program_options/options_description.hpp"
#include "boost/noncopyable.hpp"
//================================================================================================================================================
namespace gie_idl {

    typedef ::boost::program_options::options_description backend_options_description_t;

    struct options_t
        : ::boost::noncopyable
        , ::gie::ref_countable<options_t>
        , ::boost::program_options::variables_map
    {};

    typedef ::boost::intrusive_ptr<options_t> options_ptr_t;

}
//================================================================================================================================================
#endif//H_GUARD_PARAM_CORE_H__08_05_2005__20_05_44
//================================================================================================================================================
