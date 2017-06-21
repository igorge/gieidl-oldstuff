//================================================================================================================================================
//
// (c) GIE 06.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_IDL_BACKEND_FRAME_HELPRES_ENUMERATORS_H__06_05_2005__22_49_36
#define H_GUARD_IDL_BACKEND_FRAME_HELPRES_ENUMERATORS_H__06_05_2005__22_49_36
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../idl_compil/semantic.helpers.get_node_attr_repo.h"

#include "gielib/giecom/giecom.server.stackbased.simple.h"

#include "boost/type.hpp"
#include "gielib/giecom/giecom.stdproxy.client.h"
//================================================================================================================================================
namespace gie_idl {

    typedef node_i_ptr_t get_super_result_t;
    const get_super_result_t get_super_root_for_inner_if_any_or_self(node_i* const node, node_i* const referrer)
    {
        GIE_LIB_IS_VALID_POINTER(node);
        GIE_LIB_IS_VALID_POINTER(referrer);

        #ifdef GIE_LIB_DEBUG
            const string_t& debug__node_name = get_node_name( node );
            const string_t& debug__referrer_name = get_node_name( referrer );
        #endif

        node_i_ptr_t current (node);
        const unknown_ptr_t& referrers_parent = referrer->get_parent();
        GIE_LIB_ASSERTE(referrers_parent);
        const node_i_ptr_t& real_referrers_parent = ::gie::ccom::query_interface_via_proxy<node_i>(referrers_parent, ::gie::ccom::throw_on_fail(), ::gie::ccom::throw_on_fail() );

        #ifdef GIE_LIB_DEBUG
            const string_t& debug__ref_node_name = get_node_name( real_referrers_parent );
        #endif
                
        //
        // we have 2 type of compound objects (by structural identity)
        //  aggregates - treated as one - cannot be separated
        //  namespaces - can be additively combined, so we can walk them by parts
        //
        if( node->get_type() == type_aggregate )
        {
            for(;;)
            {
                #ifdef GIE_LIB_DEBUG
                    const string_t& debug__node_name = get_node_name( current );
                    const string_t& debug__node_type_str = map_node_type2string( current->get_type() );
                #endif

                const unknown_ptr_t& new_current_unknown = current->get_parent();
                //GIE_LIB_IS_VALID_POINTER( new_current_unknown.get() ); //only root ns have no parent
                const node_i_ptr_t& new_current_as_node = ::gie::ccom::query_interface_via_proxy<node_i>(new_current_unknown,  ::gie::ccom::throw_on_fail(), ::gie::ccom::throw_on_fail() );
                if( !new_current_as_node->get_parent() ) break; //we reached root ns
                if( ::gie::ccom::is_same(real_referrers_parent, new_current_as_node ) ) break; //narrow down dependency scope
                current = new_current_as_node;
            }
            return get_super_result_t(current);

        }
        else
            if( node->get_type() == type_namespace )
            {
                GIE_LIB_NOT_IMPLEMENTED; //cuurently no symbol can depend on namespace
                //return get_super_result_t( node );
            }
            else
                return get_super_result_t( node );

    }

    //
    // required_symbols_enum_t
    //
    template <class extern_info_t_t>
    struct required_symbols_enum_t
        : ::gie::ccom::stack_based_simple_unknown_impl_t<required_symbol_enum_callback_i>
    {
        required_symbols_enum_t(extern_info_t_t& extern_info, const node_i_ptr_t& referrer)
            : extern_info_( extern_info )
            , referrer_( referrer )
        {}
        void enumerate_this_required_symbol(node_i* const node, const bool is_forward_only_ok)
        {
            #ifdef GIE_LIB_DEBUG
                const string_t& debug__node_name = get_node_name( node );
                const string_t& debug__referrer_name = get_node_name( referrer_ );
            #endif

            const unknown_ptr_t& node_id = ::gie::ccom::get_identity_interface( node );
            const extern_info_t_t::visited_map_t::const_iterator loc = extern_info_.visited_nodes_.find( node_id );

            if( loc==extern_info_.visited_nodes_.end() ) //if node not visited
            {
                const get_super_result_t& super_r = get_super_root_for_inner_if_any_or_self( node, referrer_.get() );

                #ifdef GIE_LIB_DEBUG
                    const string_t& debug__node_name_super = get_node_name( super_r );
                    const string_t& debug__node_type_str_super = map_node_type2string( super_r->get_type() );
                #endif

                if( is_forward_only_ok )
                {
                    GIE_LIB_NOT_IMPLEMENTED;
                }
                else
                {
                    if( super_r->get_type() == type_namespace )
                        extern_info_.ask_walker_to_visit_with_traverse(super_r.get(), node);
                    else
                        extern_info_.ask_walker_to_visit( super_r.get() );
                }
            }
        };
    private:
        extern_info_t_t& extern_info_;
        const node_i_ptr_t referrer_;
    };

}
//================================================================================================================================================
#endif//H_GUARD_IDL_BACKEND_FRAME_HELPRES_ENUMERATORS_H__06_05_2005__22_49_36
//================================================================================================================================================
