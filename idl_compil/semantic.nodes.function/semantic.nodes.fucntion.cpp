//================================================================================================================================================
//
// (c) GIE 03.06.2005
//
//================================================================================================================================================
// NAME: semantic.nodes.fucntion.cpp
//================================================================================================================================================
#include "stdafx.h"

#include "semantic.nodes.fucntion.interfaces.h"

#include "../semantic.nodes.impl.h"
#include "../semantic.required_symbols.interfaces.h"
#include "../semantic.nodes.impl/attribute_repository_holder.impl.h"

#include "gielib/giecom/giecom.server.h"
#include "gielib/giecom/giecom.server.proxy.stdimpl.h"

#include <algorithm>
//================================================================================================================================================
namespace gie_idl {


    //
    // interfaces list
    //
    typedef gie::ccom::list
            < 
                gie::ccom::implemented<named_i>,
                gie::ccom::implemented<gie::ccom::std_proxy_host_i>,
                gie::ccom::implemented<node_i>,
                gie::ccom::implemented<attribute_repository_holder_i>,
                gie::ccom::implemented<function_builder_i>,
                gie::ccom::implemented<function_i>,
                required_symbols_i
            > 
            function_node_interfaces_t;

    //
    // namespace node implementation
    //
    struct function_impl_t
        : gie::ccom::c_object_root_t
          <
             function_impl_t,   //self type
             node_i ,               //unknown from this interface
             function_node_interfaces_t,   //supported interfaces
             gie::ccom::counter_block_t<function_impl_t, 2>   //counter impl
          >
        , gie::ccom::proxy_anchor_t
        , impl::named_i_impl_t
        , impl::proxy_impl_t<function_impl_t>
        , impl::node_i_impl_t<type_function, function_builder_i>
        , impl::attribute_repository_holder_impl_t
    {
        function_impl_t(const string_t& name)
            : named_i_impl_t ( name )
        {}

        void ccom_release_resources_()throw()
        {
            //functions_.clear();
            parameters_ = NULL;
        }
            

        void enumerate_required_symbols(required_symbol_enum_callback_i*const enumerator)
        {
            //std::for_each( functions_.begin(), functions_.end(), impl::enumerate_required_symbol_t(enumerator) );
            (impl::enumerate_required_symbol_t(enumerator))(parameters_);
        }

        void GIE_LIB_FASTCALL add(const node_i_ptr_t& function_info) // naming BUG here
        {
            GIE_LIB_DEBUG_WARN_ASSERT(!parameters_, "resetting function parameters");
            parameters_ = ::gie::ccom::query_interface_<function_parameters_i>( function_info, ::gie::ccom::throw_on_fail() );
            //functions_.push_back( function_info );
        }

        const type_descriptor_ptr_t get_return_type()
        {
            GIE_LIB_IS_VALID_POINTER( parameters_.get() );
            const node_i_ptr_t& ret_as_node = parameters_->get_return_type();
            if( ret_as_node )
            {
                const type_descriptor_ptr_t& ret_as_type = ::gie::ccom::query_interface_<type_descriptor_i>( ret_as_node, ::gie::ccom::throw_on_fail() );
                return ret_as_type;
            }

            return NULL;
        }

        const function_parameters_ptr_t get_parameters()
        {
            GIE_LIB_IS_VALID_POINTER( parameters_.get() );
            return parameters_;
        }


    private:
        function_parameters_ptr_t parameters_;
    };
    typedef gie::ccom::c_object_t<function_impl_t> functiom_node_ccom;


    //
    // factory function
    //
    const function_ptr_t create_function_node(const string_t& name)
    {GIE_IDL_ST_TRACE_FUNC;
        return function_ptr_t
            ( functiom_node_ccom::create<function_i>( name ), false );
    }

}
//================================================================================================================================================
