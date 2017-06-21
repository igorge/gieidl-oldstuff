//================================================================================================================================================
//
// (c) GIE 14.03.2005
//
//================================================================================================================================================
// NAME: test.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "idl_compil/visitors/semantic.nodes.dispatch.h"
#include "idl_compil/semantic.nodes.h"

#include "boost/mpl/inherit.hpp"
#include "boost/mpl/vector.hpp"
#include "boost/mpl/inherit_linearly.hpp"

#include "idl_compil/semantic.nodes.function/semantic.nodes.fucntion.factory.h"
//================================================================================================================================================
void test()
{
    using namespace gie_idl;

    gie_idl::fucntion_specifier_to_string(gie_idl::func_spec_inline);

    function_attribute_ptr_t spec = create_function_specifier();
    function_attribute_builder_ptr_t spec_builder = ::gie::ccom::query_interface_<function_attribute_builder_i>( spec, ::gie::ccom::throw_on_fail() );

    spec_builder->set_enable_specifier(func_spec_inline);

    //using namespace gie_idl;

    //dummy_funct agg_handler;

    //typedef gie_idl::node_dispatcher_t< 
    //        mpl::vector2<aggregate_i, namespace_i> 
    //    > disp_t;

    //disp_t v( agg_handler );

    //node_dispatch_interface_loopback_impl_t rrr;

    //aggregate_ptr_t aggregate = create_aggregate_node("nmae");
    //exec_node_dispatch( aggregate.get() , &v);


}
//================================================================================================================================================
