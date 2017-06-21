//================================================================================================================================================
//
// (c) GIE 01.06.2005
//
//================================================================================================================================================
// NAME: semantic.nodes.fucntion_params.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "semantic.nodes.fucntion.interfaces.h"

#include "../semantic.required_symbols.interfaces.h"
//#include "../semantic.var_decl.interfaces.h"
#include "../semantic.nodes.impl.h"

#include "gielib/giecom/giecom.server.h"
#include "gielib/giecom/giecom.server.proxy.stdimpl.h"

#include <vector>
#include <algorithm>
//================================================================================================================================================
namespace gie_idl {

    typedef gie::ccom::list
            < 
                gie::ccom::implemented<gie::ccom::std_proxy_host_i>,
                gie::ccom::implemented<node_i>,
                gie::ccom::implemented<function_parameters_builder_i>,
                gie::ccom::implemented<function_parameters_i>,
                required_symbols_i
            > 
            function_parameters_interfaces_t;

    //
    // namespace node implementation
    //
    struct fucntion_parameters_node_impl_t
        : gie::ccom::c_object_root_t
          <
             fucntion_parameters_node_impl_t,             //self type
             node_i ,                           //unknown from this interface
             function_parameters_interfaces_t,       //supported interfaces
             gie::ccom::counter_block_t<fucntion_parameters_node_impl_t, 2>   //counter impl
          >
        , gie::ccom::proxy_anchor_t
        , impl::proxy_impl_t<fucntion_parameters_node_impl_t>
        , impl::node_i_impl_t<type_function_parameters, function_parameters_builder_i>

    {

        void push_back(const node_i_ptr_t& param)
        {
            GIE_LIB_IS_VALID_POINTER( param.get() );
            parameters_.push_back( param );
            param->set_parent( ccom_self_unknown_() );
        }
        
        void set_return_type(const node_i_ptr_t& param)
        {
            GIE_LIB_IS_VALID_POINTER( param.get() );

            GIE_LIB_DEBUG_WARN_ASSERT( !return_type_, "resetting return type" );
            return_type_ = param;
            param->set_parent( ccom_self_unknown_() );
        }

        void enumerate_required_symbols(required_symbol_enum_callback_i*const enumerator)
        {
            (impl::enumerate_required_symbol_t(enumerator))(return_type_);
            std::for_each( parameters_.begin(), parameters_.end(), impl::enumerate_required_symbol_t(enumerator) );
        }

        void ccom_release_resources_()throw()
        {
            return_type_ = NULL;
            parameters_.clear();
        }

        const node_i_ptr_t get_return_type()
        {
            return return_type_;
        }

        void enumerate_parameters(named_node_enum_callback_i* const enumerator)
        {
            std::for_each( parameters_.begin(), parameters_.end(), for_each_enum_t(enumerator) );
        }


    private:
        typedef std::vector<node_i_ptr_t> vector_of_nodes_t;

        node_i_ptr_t return_type_;
        vector_of_nodes_t parameters_;

        struct for_each_enum_t
            : ::std::unary_function<const node_i_ptr_t, void>
        {
            for_each_enum_t(named_node_enum_callback_i* const enumerator)
                : enumerator_( enumerator )
            {}
            result_type operator()(argument_type& node)
            {
                const named_ptr_t& node_as_named = ::gie::ccom::query_interface_<named_i>( node, ::gie::ccom::throw_on_fail() );
                enumerator_->enumerate_this( node.get(), node_as_named->get_name() );
            }
        private:
            named_node_enum_callback_i* const enumerator_;
        };
    };
    typedef gie::ccom::c_object_t<fucntion_parameters_node_impl_t> fucntion_parameters_node_ccom;

    //
    // factory function
    //
    const function_parameters_ptr_t create_function_parameters()
    {
        return function_parameters_ptr_t
            ( fucntion_parameters_node_ccom::create<function_parameters_i>(), false );
    }

}
//================================================================================================================================================
