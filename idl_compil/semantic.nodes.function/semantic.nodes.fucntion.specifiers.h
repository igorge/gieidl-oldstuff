//================================================================================================================================================
//
// (c) GIE 01.06.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_NODES_FUCNTION_SPECIFIERS_H__01_06_2005__23_08_45
#define H_GUARD_SEMANTIC_NODES_FUCNTION_SPECIFIERS_H__01_06_2005__23_08_45
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "boost/preprocessor/punctuation/comma_if.hpp"
#include "boost/preprocessor/punctuation/comma.hpp"
#include "boost/preprocessor/tuple/elem.hpp"
#include "boost/preprocessor/seq/for_each_i.hpp"
//================================================================================================================================================
namespace gie_idl{

    /*
    *	function_specifier = inline | virtual | explicit
    *  cv_qualifier = const | volatile
    *  cv_qualifier_seq = cv_qualifier cv_qualifier_seq(opt)
    */

    //enum fucntion_specifier {func_spec_invalid = 0, func_spec_inline, func_spec_virtual, func_spec_explicit};

#define GIE_IDL_FUNCTION_SPECIFIER_SEQ_ITEM_SIZE 2
#define GIE_IDL_FUNCTION_SPECIFIER_SEQ                                  \
    (( func_spec_inline       , "inline"))                              \
    (( func_spec_virtual      , "virtual"))                             \
    (( func_spec_explicit     , "explicit"))                            \
    /**/


    //
    // enum fucntion_specifier
    //
    #define GIE_IDL_DEFINE_FUNCTION_SPECIFIER(r, aux/*aux data*/, i/*iter counter*/, def /*data*/) \
        BOOST_PP_COMMA_IF(i) BOOST_PP_TUPLE_ELEM(GIE_IDL_FUNCTION_SPECIFIER_SEQ_ITEM_SIZE, 0, def) \
        /**/
    
    enum fucntion_specifier { 
        BOOST_PP_SEQ_FOR_EACH_I(GIE_IDL_DEFINE_FUNCTION_SPECIFIER, 0, GIE_IDL_FUNCTION_SPECIFIER_SEQ)
    };

    //
    // fucntion_specifier_to_string
    //

    #define GIE_IDL_DEFINE_FUNCTION_SPECIFIER_ITEM_2_STRING(r, aux/*aux data*/, i/*iter counter*/, def /*data*/) \
        if( BOOST_PP_TUPLE_ELEM(GIE_IDL_FUNCTION_SPECIFIER_SEQ_ITEM_SIZE, 0, def) == func_spec ) \
        return wxT(BOOST_PP_TUPLE_ELEM(GIE_IDL_FUNCTION_SPECIFIER_SEQ_ITEM_SIZE, 1, def));       \
        /**/

    inline const string_t fucntion_specifier_to_string(const fucntion_specifier func_spec)
    {
        BOOST_PP_SEQ_FOR_EACH_I(GIE_IDL_DEFINE_FUNCTION_SPECIFIER_ITEM_2_STRING, 0, GIE_IDL_FUNCTION_SPECIFIER_SEQ);
        GIE_LIB_NOT_IMPLEMENTED;
    }


}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_NODES_FUCNTION_SPECIFIERS_H__01_06_2005__23_08_45
//================================================================================================================================================
