//================================================================================================================================================
//
// (c) GIE 11.04.2005
//
//================================================================================================================================================
// NAME: semantic.tree_holder.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "gielib/giecom/giecom.guid.init.h"                     //START GUID DEF SECTION
#
#   include "semantic.nodes.semantic_tree_holder.interfaces.h"
#
#include "gielib/giecom/giecom.guid.init.end.h"                 //END GUID SECTION

#include "semantic.tree.interfaces.h"
#include "gielib/giecom/giecom.server.h"
#include "gielib/giecom/giecom.client.h"

#include "semantic.nodes.h"

#include <list>
//================================================================================================================================================
namespace gie_idl {

    typedef gie::ccom::list<semantic_tree_holder_i> semantic_tree_holder_interfaces_t;

    struct semantic_tree_holder_impl_t
        : gie::ccom::c_object_root_t
          <
             semantic_tree_holder_impl_t, //self type
             semantic_tree_holder_i ,               //unknown from this interface
             semantic_tree_holder_interfaces_t,   //supported interfaces
             gie::ccom::counter_impl_t<>
          >
    {
        semantic_tree_holder_impl_t()
            : root_node_( create_namespace_node( wxT("") ) )
        {   GIE_IDL_ST_TRACE_FUNC;
        }
        const boost::intrusive_ptr<node_i> get_root_node()
        {   GIE_IDL_ST_TRACE_FUNC;
            GIE_IDL_ST_TRACE_VAL(root_node_);

            return root_node_;
        }
        void push_back_new_late_boud(late_bound_i* const late_bound)
        {
            late_bound_symbols_.push_back( late_bound_ptr_t(late_bound) );
        }
        void enumerate_late_bound(late_boud_enum_callback_i* const enum_callback)
        {
            late_bound_symbols_t::iterator& i = late_bound_symbols_.begin();
            const late_bound_symbols_t::const_iterator& end = late_bound_symbols_.end();
            while( i!=end )
            {
                switch( enum_callback->enumerate_this( (*i).get() ) )
                {
                case late_boud_enum_callback_i::continue_enumeration:
                    break;
                case late_boud_enum_callback_i::abort_enumeration:
                    return;
                case late_boud_enum_callback_i::delete_this_item_and_continue:
                    i = late_bound_symbols_.erase(i);
                    continue;
                default:
                    GIE_LIB_NOT_IMPLEMENTED;
                }

                ++i;
            }
        }

        void ccom_release_resources_()throw()
        {
            late_bound_symbols_.clear();
        }

    private:
        //void free_tree_and_data_()
        //{GIE_IDL_ST_TRACE_FUNC;
        //}

        typedef std::list<late_bound_ptr_t> late_bound_symbols_t;
        late_bound_symbols_t late_bound_symbols_;

        boost::intrusive_ptr<node_i> root_node_;
    };

    typedef gie::ccom::c_object_t<semantic_tree_holder_impl_t> semantic_tree_holder_c;


    boost::intrusive_ptr<semantic_tree_holder_i> create_semantic_tree_holder()
    {
        return boost::intrusive_ptr<semantic_tree_holder_i>( semantic_tree_holder_c::create<semantic_tree_holder_i>(), false );
    }


}

//================================================================================================================================================
