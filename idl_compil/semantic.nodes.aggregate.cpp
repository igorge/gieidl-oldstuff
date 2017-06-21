//================================================================================================================================================
//
// (c) GIE 27.03.2005
//
//================================================================================================================================================
// NAME: semantic.nodes.aggregate.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "semantic.nodes.impl.compound.dep_resolver.h"
#include "semantic.nodes.impl/attribute_repository_holder.impl.h"
#include "semantic.nodes.h"
#include "semantic.nodes.impl.h"
#include "semantic.helpers.get_node_name.h"
#include "semantic.helpers.node_type2string.h"
#include "gielib/giecom/giecom.stdproxy.client.h"

#include "gielib/giecom/giecom.server.h"
#include "gielib/giecom/giecom.server.proxy.stdimpl.h"

#include "semantic.required_symbols.interfaces.h"

#include "gielib/debug/debug.h"
#include <list>
//================================================================================================================================================
namespace gie_idl { 

    //
    // interfaces list
    //
    typedef gie::ccom::list
            < 
                gie::ccom::implemented<aggregate_i>,
                gie::ccom::implemented<named_i>,
                gie::ccom::implemented<gie::ccom::std_proxy_host_i>,
                gie::ccom::implemented<named_collection_i>, 
                gie::ccom::implemented<node_i>,
                gie::ccom::implemented<attribute_repository_holder_i>,
                aggregate_build_i, 
                required_symbols_i
            > 
            aggregate_node_interfaces_t;

    //
    // namespace node implementation
    //
    struct aggregate_node_impl_t
        : gie::ccom::c_object_root_t
          <
             aggregate_node_impl_t, //self type
             node_i ,               //unknown from this interface
             aggregate_node_interfaces_t,   //supported interfaces
             gie::ccom::counter_block_t<aggregate_node_impl_t, 2>   //counter impl
          >
        , gie::ccom::proxy_anchor_t
        , impl::named_i_impl_t
        , impl::proxy_impl_t<aggregate_node_impl_t>
        , impl::named_collection_i_impl_t<aggregate_node_impl_t, impl::node_i_impl_t<type_aggregate, aggregate_i> >
        , impl::attribute_repository_holder_impl_t
        , impl::filter_out_inner_required_symbol_enumerator_impl_t<aggregate_node_impl_t>

    {
        friend impl::filter_out_inner_required_symbol_enumerator_impl_t<aggregate_node_impl_t>;

        aggregate_node_impl_t(const string_t& self_name)
            : impl::named_i_impl_t( self_name )
        {}

        void add_inheritance_info(const unknown_ptr_t& inh_parent, const access_t& access)
        {
            if( !inh_parent ) { GIE_LIB_NOT_IMPLEMENTED; }
            const std_proxy_ptr_t& proxy = ::gie::ccom::query_interface<::gie::ccom::std_proxy_i>(inh_parent);
            if( !proxy ) { GIE_LIB_NOT_IMPLEMENTED; }

            parents_.push_back( parent_info_t( proxy, access) );
        }

        void enumerate_encestors(ancestor_enum_callback_i*const enumerator)const
        {
            parents_t::const_iterator& i = parents_.begin();
            const parents_t::const_iterator& end = parents_.end();
            while( i!=end )
            {
                const node_i_ptr_t node ( i->get<0>()->query_host_interface_ex<node_i>(), false );
                GIE_LIB_ASSERTE( node );
                
                switch( enumerator->enumerate_this( node.get(), i->get<1>() ) )
                {
                case ancestor_enum_callback_i::continue_enumeration:
                    ++i;
                    continue;
                case ancestor_enum_callback_i::abort_enumeration:
                    return;
                default:
                    GIE_LIB_NOT_IMPLEMENTED;
                }//end of switch
            }// end of while
        }

        void enumerate_required_symbols(required_symbol_enum_callback_i*const enumerator)
        {
            if( required_symbols_enum_ancestors_( enumerator ) )
                required_symbols_enum_childrens_( enumerator );

            //TODO: implement inner aggregates lookup for external smbols
        }


        void ccom_release_resources_()throw()
        {
            GIE_LIB_TRACE_FUNC;
            release_childs_();  //named collection impl release
            parents_.clear();   //clear inheritance list
        }
    private:
        bool required_symbols_enum_ancestors_(required_symbol_enum_callback_i*const enumerator)
        {
            parents_t::const_iterator& i = parents_.begin();
            const parents_t::const_iterator& end = parents_.end();
            while( i!=end )
            {
                node_i_ptr_t node ( i->get<0>()->query_host_interface_ex<node_i>(), false );
                GIE_LIB_ASSERTE( node );
                if( node->get_type()==type_late_bound )
                {
                    const late_bound_ptr_t& node_as_late_bound = ::gie::ccom::query_interface_<late_bound_i>(node, ::gie::ccom::throw_on_fail() );

                    node = ::gie::ccom::query_interface_via_proxy<node_i>( node );
                    if( !node )
                    {
                        // if unbound symbol found the we just ignore it
                        // TODO: should we signal somehow for this?
                        ++i;
                        continue;
                    }
                    #ifdef GIE_LIB_DEBUG
                        const string_t& debug__node_name = get_node_name( node );
                        const string_t& debug__node_type_str = map_node_type2string( node->get_type() );
                    #endif
                }
                
                enumerator->enumerate_this_required_symbol( node.get(), false );

                ++i;

            }// end of while

            return true;
        }

        struct required_symbols_enum_context_t
        {
            required_symbols_enum_context_t()
                : abort_enumeration( false )
            {}
            bool abort_enumeration;
        };
    private:
        typedef ::boost::intrusive_ptr<::gie::ccom::std_proxy_i>  std_proxy_ptr_t;
        typedef ::boost::tuple<const std_proxy_ptr_t, const access_t> parent_info_t;
        typedef ::std::list<parent_info_t> parents_t;

        parents_t parents_;
    };
    typedef gie::ccom::c_object_t<aggregate_node_impl_t> aggregate_node_c;


    //
    // factory function
    //
    aggregate_ptr_t create_aggregate_node(const string_t& name)
    {
        return aggregate_ptr_t
            ( aggregate_node_c::create<aggregae_node_default_i>(name), false );
    }

}
//================================================================================================================================================
