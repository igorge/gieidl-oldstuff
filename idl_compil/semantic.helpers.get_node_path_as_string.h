//================================================================================================================================================
//
// (c) GIE 27.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_HELPERS_GET_NODE_PATH_AS_STRING_H__27_04_2005__13_05_13
#define H_GUARD_SEMANTIC_HELPERS_GET_NODE_PATH_AS_STRING_H__27_04_2005__13_05_13
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "semantic.helpers.get_node_name.h"
#include "semantic.tree.core.interfaces.h"
#include "semantic.helpers.id2string.h"
#include "semantic.nodes.late_bound.interfaces.h"

#include "gielib/giecom/giecom.stdproxy.client.h"

#include <algorithm>
#include <list>
//================================================================================================================================================
namespace gie_idl {

    namespace impl {
        
        struct make_str_path_t
            : ::std::unary_function<named_ptr_t, void>
        {

            make_str_path_t(string_t& str)
                : str_( str )
            {}
            void operator()(const named_ptr_t& named)const
            {

                const string_t& name =  named->get_name();
                if( name.empty() ) return;

                str_.reserve( str_.size()+name.size()+2 );
                
                str_.append( wxT("::") );
                str_.append( name );
            }
            const string_t& get_str()const throw()
            {
                return str_;
            }
        private:
            string_t& str_;
        };
    
    }

    inline
    const string_t get_node_path_as_string(const node_i_ptr_t& node)
    {
        typedef std::list<named_ptr_t> list_of_named_t;

        if( !node )
        {
            GIE_LIB_NOT_IMPLEMENTED;
        }

        list_of_named_t named;
        node_i_ptr_t curr_node;

        if( node->get_type()==type_late_bound )
        {
            const late_bound_ptr_t& node_as_late_bound = ::gie::ccom::query_interface_<late_bound_i>( node, ::gie::ccom::throw_on_fail() );
            if( node_as_late_bound->is_boud() )
            {
                curr_node = ::gie::ccom::query_interface_via_proxy<node_i>(node_as_late_bound);
                if( !curr_node ){ GIE_LIB_NOT_IMPLEMENTED_1("call should success"); }
            }
            else
                return map_id2string( node_as_late_bound->get_id() );
        }
        else
            curr_node = node;


        for(;;)
        {
            named.push_front( ::gie::ccom::query_interface_<named_i>( curr_node, ::gie::ccom::throw_on_fail() ) );

            #ifdef GIE_LIB_DEBUG
                const string_t& str = named.front()->get_name();
            #endif

            //get next
            const boost::intrusive_ptr<gie::ccom::unknown_i>& parent_unknown = curr_node->get_parent();
            if( !parent_unknown ) break;
            const boost::intrusive_ptr<::gie::ccom::std_proxy_i>& parent_proxy = ::gie::ccom::query_interface_<::gie::ccom::std_proxy_i>( parent_unknown, ::gie::ccom::throw_on_fail() );
            curr_node = boost::intrusive_ptr<node_i>( parent_proxy->query_host_interface_ex<node_i>(), false );
        }

        string_t accum_str;
        std::for_each( 
            named.begin(), 
            named.end(),
            impl::make_str_path_t( accum_str )
        );
    
        if( accum_str.empty() )
            accum_str.append( wxT("::") );
        
        return accum_str;
    }

    inline
        const string_t get_node_path_as_string(::gie::ccom::unknown_i* const unknown)
    {
        const node_i_ptr_t& as_node = ::gie::ccom::query_interface_<node_i>( unknown, ::gie::ccom::throw_on_fail() );
        return get_node_path_as_string( as_node );
    }

}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_HELPERS_GET_NODE_PATH_AS_STRING_H__27_04_2005__13_05_13
//================================================================================================================================================
