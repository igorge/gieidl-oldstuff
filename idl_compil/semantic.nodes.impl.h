//================================================================================================================================================
//
// (c) GIE 26.03.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_NODES_IMPL_H__26_03_2005__19_36_49
#define H_GUARD_SEMANTIC_NODES_IMPL_H__26_03_2005__19_36_49
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "semantic.tree.interfaces.h"
#include "semantic.required_symbols.interfaces.h"
#include "gielib/giecom/giecom.server.proxy.stdimpl.h"
#include "gielib/giecom/giecom.stdproxy.client.h"

#include "boost/type_traits.hpp"
#include "boost/static_assert.hpp"
#include <map>
//================================================================================================================================================
namespace gie_idl {

    template <class outer_t_t>
    struct this_resolver_t
    {
        outer_t_t* get_this()throw()
        {
            typedef ::boost::is_base_and_derived<this_resolver_t, outer_t_t> is_outer_ok;
            BOOST_STATIC_ASSERT( is_outer_ok::value );

            return static_cast<outer_t_t*const>(this);
        }
    };

    namespace impl {

        //
        // enumerate_required_symbol_t
        // 
        struct enumerate_required_symbol_t
            : ::std::unary_function<node_i_ptr_t,void>
        {
            enumerate_required_symbol_t(required_symbol_enum_callback_i*const enumerator)
                : enumerator_ ( enumerator )
            {}
            result_type operator()(const argument_type& node)
            {
                const required_symbols_ptr_t& childrens_required_symbols = ::gie::ccom::query_interface<required_symbols_i>( node );
                if( childrens_required_symbols ) childrens_required_symbols->enumerate_required_symbols( enumerator_ );
            }
        private:
            required_symbol_enum_callback_i*const enumerator_;
        };


        //
        // named_i_impl_t
        //
        struct named_i_impl_t
            : public named_i
        {
            named_i_impl_t(const string_t&  self_name)
                : self_name_( self_name )
            {}

            const string_t& get_name()const throw()
            {
                return get_name_();
            }
        protected:
            const string_t& get_name_()const throw()
            {
                return self_name_;
            }
        private:
            const string_t  self_name_;
        };

        //
        // proxy_impl_t
        //
        template
        <
            class outer_t_t,
            const unsigned int counter_id_t_v=1
        >
        struct proxy_impl_t
            : gie::ccom::std_proxy_host_i
            , this_resolver_t<outer_t_t>
        {

            gie::ccom::std_proxy_i* get_proxy()
            {
                return get_proxy_();
            }

        protected:
            proxy_impl_t()
                : this_proxy_( get_this() )
            {
                typedef ::boost::is_base_and_derived<proxy_impl_t, outer_t_t> is_outer_ok;
                BOOST_STATIC_ASSERT( is_outer_ok::value );
            }

            gie::ccom::std_proxy_i* get_proxy_()
            {
                return static_cast<gie::ccom::std_proxy_i*const>( this_proxy_.query_interface( gie::ccom::iid_of<gie::ccom::std_proxy_i>::value ) );
            }

            gie::ccom::std_proxy_i*const get_self_proxy_unsafe_()
            {
                return &this_proxy_;
            }

            typedef gie::ccom::c_proxy_object_t<
                gie::ccom::std_proxy_t<counter_id_t_v, outer_t_t>
            > node_proxy_c;

            node_proxy_c this_proxy_;
        };

        //
        // named_collection_i_impl_t
        //
        template
        <
            class outer_t_t,
            class inherit_chain_t_t = gie::null_t
        >
        struct named_collection_i_impl_t
            : public inherit_chain_t_t
        {
            const insert_child_result_t insert_child(node_i * const child)
            {
                //#ifdef GIE_LIB_DEBUG
                //    const string_t* const node_name = get_name(child);
                //#endif
                return insert_child_(child);
            }

            void enumerate_nodes( named_node_enum_callback_i* const enumerator)
            {
                childs_map_t::const_iterator& i = childs_.begin();
                const childs_map_t::const_iterator& end = childs_.end();

                while( i!=end )
                {
                    switch ( enumerator->enumerate_this( i->second.get(), i->first) )
                    {
                    case named_node_enum_callback_i::continue_enumeration:
                        ++i;
                        continue;
                    case named_node_enum_callback_i::abort_enumeration:
                        return;
                    default:
                        GIE_LIB_NOT_IMPLEMENTED;
                    }//end of switch
                }//end of while

            }

            //const named_collection_i::search_result_t operator[](const string_t& name)
            //{
            //    const childs_map_t::const_iterator i = childs_.find(name);
            //    if( i==childs_.end() )
            //    {
            //        return NULL;
            //    }
            //    else
            //    {
            //        return named_collection_i::search_result_t( i->second );
            //    }
            //}

            virtual bool locate_node(const string_t& name, named_node_enum_callback_i* const enumerator)
            {
                const const_search_result& nodes = childs_map_().equal_range(name) ;
                if( nodes.first==nodes.second ) return false;

                const_search_result::first_type i = nodes.first;
                while( i!= nodes.second )
                {
                    if( enumerator->enumerate_this( i->second.get(), name  )!=named_node_enum_callback_i::continue_enumeration )
                    {
                        GIE_LIB_NOT_IMPLEMENTED;
                    }
                    ++i;
                }

                return true;
            }


        protected:
            const insert_child_result_t insert_child_(node_i * const child )
            {
                typedef ::boost::is_base_and_derived<named_collection_i_impl_t, outer_t_t> is_outer_ok;
                BOOST_STATIC_ASSERT( is_outer_ok::value );

                GIE_LIB_ASSERTE( !is_same( static_cast<outer_t_t*const>(this)->ccom_self_unknown_(), child) );

                const string_t& childs_name = gie::ccom::query_interface_<named_i>( child, gie::ccom::throw_on_fail() )->get_name();
                childs_.insert( std::make_pair(childs_name, child ) );

                child->set_parent( static_cast<outer_t_t*const>(this)->ccom_self_unknown_() );
                
                return insert_child_result_t ( child, true ); //always insert
            }

        protected:
            typedef node_i_ptr_t                                    value_t;
            typedef std::multimap<string_t const, value_t>          childs_map_t;
            typedef ::std::pair<childs_map_t::const_iterator, childs_map_t::const_iterator> const_search_result;
            typedef std::pair<childs_map_t::iterator, bool>         childs_map_insert_result_t;

            childs_map_t& childs_map_()throw()
            {
                return childs_;
            }

            void release_childs_()
            {
                childs_.clear();
            }

            childs_map_t    childs_;
        };

        //
        // node_i_impl_t
        //
        template
        <
            const gie::ccom::guid_t& this_type,
            class inherit_chain_t_t = gie::null_t
        >
        struct node_i_impl_t
            : public inherit_chain_t_t
        {
            void set_parent(gie::ccom::unknown_i*const parent_proxy)
            {
                GIE_LIB_DEBUG_WARN_ASSERT(!parent_, "resetting parent_");
                parent_ = ::gie::ccom::get_std_proxy( parent_proxy, ::gie::ccom::proxy_throw_validator() );
            }

            const boost::intrusive_ptr<gie::ccom::unknown_i> get_parent()
            {
                return parent_;
            }


            const gie::ccom::guid_t& get_type()const throw()
            {
                return this_type;
            }
        protected:
            const boost::intrusive_ptr<gie::ccom::std_proxy_i>& get_parent_()const
            {
                return parent_;
            }


        private:
            boost::intrusive_ptr<gie::ccom::std_proxy_i> parent_;
        };

    }//end of impl namespace

}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_NODES_IMPL_H__26_03_2005__19_36_49
//================================================================================================================================================
