//================================================================================================================================================
//
// (c) GIE 01.06.2005
//
//================================================================================================================================================
// NAME: semantic.nodes.fucntion.attributes.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "semantic.nodes.fucntion.interfaces.h"

#include "gielib/giecom/giecom.server.h"
//================================================================================================================================================
namespace gie_idl {

    typedef
        gie::ccom::list
        <
            ::gie::ccom::implemented<function_attribute_i>, 
            function_attribute_builder_i
        >
        function_specifiers_interfaces_t;

// define
#define GIE_IDL_DEFINE_FUNCTION_SPECIFIER_VAR(r, aux/*aux data*/, i/*iter counter*/, def /*data*/) \
    bool BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM(GIE_IDL_FUNCTION_SPECIFIER_SEQ_ITEM_SIZE, 0, def), _);        \
    /**/
// init
#define GIE_IDL_DEFINE_FUNCTION_SPECIFIER_VAR_INIT(r, aux/*aux data*/, i/*iter counter*/, def /*data*/) \
    BOOST_PP_COMMA_IF(i) BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM(GIE_IDL_FUNCTION_SPECIFIER_SEQ_ITEM_SIZE, 0, def), _)(false)        \
    /**/
// set
#define GIE_IDL_DEFINE_FUNCTION_SPECIFIER_ITEM_SET(r, aux/*aux data*/, i/*iter counter*/, def /*data*/) \
    if( BOOST_PP_TUPLE_ELEM(GIE_IDL_FUNCTION_SPECIFIER_SEQ_ITEM_SIZE, 0, def) == specifier )       \
    {   \
    if( BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM(GIE_IDL_FUNCTION_SPECIFIER_SEQ_ITEM_SIZE, 0, def), _) ) {GIE_LIB_DEBUG_WARN("resetting specifier");} \
        else BOOST_PP_CAT( BOOST_PP_TUPLE_ELEM(GIE_IDL_FUNCTION_SPECIFIER_SEQ_ITEM_SIZE, 0, def), _) = true; \
        return; \
    }   \
    /**/


    struct function_specifiers_impl_t
        : gie::ccom::c_object_root_t
        <
            function_specifiers_impl_t, //self type
            function_attribute_i ,               //unknown from this interface
            function_specifiers_interfaces_t,   //supported interfaces
            gie::ccom::counter_impl_t<>
        >
    {
        function_specifiers_impl_t()
            : BOOST_PP_SEQ_FOR_EACH_I(GIE_IDL_DEFINE_FUNCTION_SPECIFIER_VAR_INIT, 0, GIE_IDL_FUNCTION_SPECIFIER_SEQ)
        {}
        void set_enable_specifier(const fucntion_specifier specifier)
        {
            BOOST_PP_SEQ_FOR_EACH_I(GIE_IDL_DEFINE_FUNCTION_SPECIFIER_ITEM_SET, 0, GIE_IDL_FUNCTION_SPECIFIER_SEQ);
            GIE_LIB_NOT_IMPLEMENTED_2("unknown function specifier", specifier );
        }
    private:
        BOOST_PP_SEQ_FOR_EACH_I(GIE_IDL_DEFINE_FUNCTION_SPECIFIER_VAR, 0, GIE_IDL_FUNCTION_SPECIFIER_SEQ);
    };

    typedef gie::ccom::c_object_t<function_specifiers_impl_t> function_specifiers_com;


    const function_attribute_ptr_t create_function_specifier()
    {
        return function_attribute_ptr_t( function_specifiers_com::create<function_attribute_i>(), false );
    }

}
//================================================================================================================================================
