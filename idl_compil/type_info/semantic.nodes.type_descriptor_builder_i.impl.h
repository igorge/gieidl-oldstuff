//================================================================================================================================================
//
// (c) GIE 19.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_NODES_TYPE_DESCRIPTOR_BUILDER_I_IMPL_H__19_05_2005__22_07_16
#define H_GUARD_SEMANTIC_NODES_TYPE_DESCRIPTOR_BUILDER_I_IMPL_H__19_05_2005__22_07_16
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../semantic.required_symbols.interfaces.h"
#include "../semantic.helpers.node_type2string.h"
#include "semantic.type_info.interfaces.h"
//#include "gielib/giecom/giecom.stdproxy.client.h"

#include <set>
//================================================================================================================================================
namespace gie_idl {

    namespace impl {

        //
        // type_descriptor_builder_non_owner_impl_t
        //
        template <class self_t_t>
        struct type_descriptor_builder_non_owner_impl_t
            : type_descriptor_builder_i
            , type_descriptor_info_i
        {

            type_descriptor_builder_non_owner_impl_t()
                : is_late_bound_(false)
            {}
            void enable_mod(const type_info_mods mod2enable)
            {
                if( !mods_.insert(mod2enable).second )
                {
                    GIE_LIB_DEBUG_WARN("enabling already enabled mod");
                }
            }
            bool is_mod_enabled(const type_info_mods mod2enable)
            {
                return( mods_.find(mod2enable)!=mods_.end() );
            }
            void set_next_sub_type(node_i* const type_node)
            {
                GIE_LIB_DEBUG_WARN_ASSERT(!sub_type_, "resetting sub type");
                if( type_node->get_type()==type_late_bound )
                {
                    sub_type_ = type_node;
                    type_node->set_parent( static_cast<self_t_t*const>(this)->ccom_self_unknown_() );
                    is_late_bound_ = true;
                }
                else
                {
                    sub_type_ = ::gie::ccom::get_std_proxy( type_node, ::gie::ccom::proxy_throw_validator() );
                    is_late_bound_ = false;
                }
            }
            const node_i_ptr_t get_next_sub_type()
            {
                if( is_late_bound_ )
                    return ::gie::ccom::query_interface_<node_i>( sub_type_, ::gie::ccom::throw_on_fail() );
                else
                {
                    return ::gie::ccom::query_interface_via_proxy<node_i>( sub_type_ );
                }

            }
        protected:
            void enumerate_required_symbols_(required_symbol_enum_callback_i*const enumerator)
            {
                // sub_type_ can be proxy or late_boud, both supports query_interface_via_proxy.
                const node_i_ptr_t& child_as_node = ::gie::ccom::query_interface_via_proxy<node_i>( sub_type_ );
                if( child_as_node )
                    enumerator->enumerate_this_required_symbol(child_as_node.get(), false);
            }

            void ccom_release_resources_()throw()
            {
                //GIE_LIB_DEBUG_WARN("releasing sub_type_");
                sub_type_=NULL;  
            }
        private:

            typedef std::set<type_info_mods> mods_ist_t;
            mods_ist_t mods_;

            ::boost::intrusive_ptr<::gie::ccom::unknown_i> sub_type_; //proxy or late_bound
            bool is_late_bound_;
        };

        //
        // type_descriptor_builder_owner_impl_t
        //
        template <class self_t_t>
        struct type_descriptor_builder_owner_impl_t
            : type_descriptor_builder_i
            , type_descriptor_info_i
        {
            void enable_mod(const type_info_mods mod2enable)
            {
                if( !mods_.insert(mod2enable).second )
                {
                    GIE_LIB_DEBUG_WARN("enabling already enabled mod");
                }
            }

            bool is_mod_enabled(const type_info_mods mod2enable)
            {
                return( mods_.find(mod2enable)!=mods_.end() );
            }

            void set_next_sub_type(node_i* const type_node)
            {
                GIE_LIB_IS_VALID_POINTER( type_node );
                sub_type_ = type_node;
                type_node->set_parent( static_cast<self_t_t*const>(this)->ccom_self_unknown_() );
            }

            const node_i_ptr_t get_next_sub_type()
            {
                return sub_type_;
            }

        protected:
            void enumerate_required_symbols_(required_symbol_enum_callback_i*const enumerator)
            {
                #ifdef GIE_LIB_DEBUG
                    const string_t& debug__sub_type = map_node_type2string( sub_type_->get_type() );
                #endif

                const required_symbols_ptr_t& child_required_symbols = ::gie::ccom::query_interface<required_symbols_i>( sub_type_ );
                if( child_required_symbols )
                {
                    child_required_symbols->enumerate_required_symbols( enumerator );
                }
            }

            void ccom_release_resources_()throw()
            {
                //GIE_LIB_DEBUG_WARN("releasing sub_type_");
                sub_type_=NULL;  
            }

        private:

            typedef std::set<type_info_mods> mods_ist_t;
            mods_ist_t mods_;

            node_i_ptr_t sub_type_; //proxy or late_bound
        };

    } // end of impl namespace

}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_NODES_TYPE_DESCRIPTOR_BUILDER_I_IMPL_H__19_05_2005__22_07_16
//================================================================================================================================================
