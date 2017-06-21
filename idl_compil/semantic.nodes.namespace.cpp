//================================================================================================================================================
//
// (c) GIE 21.03.2005
//
//================================================================================================================================================
// NAME: semantic.nodes.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "semantic.nodes.impl.compound.dep_resolver.h"
#include "semantic.nodes.h"
#include "semantic.nodes.impl.h"
#include "semantic.required_symbols.interfaces.h"

#include "gielib/giecom/giecom.server.h"
#include "gielib/giecom/giecom.server.proxy.stdimpl.h"
//================================================================================================================================================
namespace gie_idl {

    //
    // interfaces list
    //
    typedef gie::ccom::list
            < 
                gie::ccom::implemented<namespace_i>,
                gie::ccom::implemented<named_i>,
                gie::ccom::implemented<gie::ccom::std_proxy_host_i>,
                gie::ccom::implemented<named_collection_i>, 
                gie::ccom::implemented<node_i>,
                required_symbols_i
            > 
            namespace_node_interfaces_t;

    //
    // namespace node implementation
    //
    struct namespace_node_impl_t
        : gie::ccom::c_object_root_t
          <
             namespace_node_impl_t, //self type
             node_i ,               //unknown from this interface
             namespace_node_interfaces_t,   //supported interfaces
             gie::ccom::counter_block_t<namespace_node_impl_t, 2>   //counter impl
          >
        , gie::ccom::proxy_anchor_t
        , impl::named_i_impl_t
        , impl::proxy_impl_t<namespace_node_impl_t>
        , impl::named_collection_i_impl_t<namespace_node_impl_t, impl::node_i_impl_t<type_namespace, namespace_i> >
        , impl::filter_out_inner_required_symbol_enumerator_impl_t<namespace_node_impl_t>


    {
        friend impl::filter_out_inner_required_symbol_enumerator_impl_t<namespace_node_impl_t>;

        typedef boost::intrusive_ptr<node_i>    node_i_ptr_t;

        namespace_node_impl_t(const string_t& name)
            : named_i_impl_t ( name )
        {}

        const create_namespace_result_t create_inner_namespace(const string_t& name)
        {
            
            // TODO: reimplement using unified insert methods

            const_search_result ns = childs_map_().equal_range(name) ;
            if( ns.first==ns.second ) //if there are no yet such ns - create it
            {
                const namespace_ptr_t& new_ns_obj = create_namespace_node(name);
                childs_map_().insert( childs_map_t::value_type(name, new_ns_obj) );
                new_ns_obj->set_parent( ccom_self_unknown_() );
                return create_namespace_result_t(new_ns_obj, true);
            }
            else //we have such object
            {
                const namespace_ptr_t& located_ns = ::gie::ccom::query_interface_<namespace_i>( ns.first->second, ::gie::ccom::throw_on_fail() );
                if( ++ns.first!=ns.second ){ GIE_LIB_NOT_IMPLEMENTED_1("namespace must have only one entry"); }
                return create_namespace_result_t(located_ns, false);
            }
        }


        void ccom_release_resources_()throw()
        {
            GIE_LIB_TRACE_FUNC;
            release_childs_();
        }

        void enumerate_required_symbols(required_symbol_enum_callback_i*const enumerator)
        {
                required_symbols_enum_childrens_( enumerator );
        }

    private:
    };
    typedef gie::ccom::c_object_t<namespace_node_impl_t> namespace_node_c;


    //
    // factory function
    //
    namespace_node_ptr_t create_namespace_node(const string_t& name)
    {GIE_IDL_ST_TRACE_FUNC;
        return namespace_node_ptr_t
            ( namespace_node_c::create<namespace_node_default_interface_i>(name), false );
    }

}

//================================================================================================================================================
