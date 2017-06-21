//================================================================================================================================================
//
// (c) GIE 16.05.2005
//
//================================================================================================================================================
#ifndef H_GUARD_SEMANTIC_NODES_DISPATCH_H__16_05_2005__10_21_23
#define H_GUARD_SEMANTIC_NODES_DISPATCH_H__16_05_2005__10_21_23
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../semantic.tree.interfaces.h"
#include "../semantic.nodes.aggregate.interfaces.h"
#include "../semantic.nodes.late_bound.interfaces.h"
#include "../semantic.nodes.function/semantic.nodes.fucntion.interfaces.h"
#include "../semantic.helpers.node_type2string.h"

#include "gielib/giecom/giecom.stdproxy.client.h"
//================================================================================================================================================
namespace gie_idl {

    #define GIE_IDL_NODE_DISPATCH_SEQ_ITEM_SIZE 2
    #define GIE_IDL_NODE_DISPATCH_IDX_TYPE      0
    #define GIE_IDL_NODE_DISPATCH_IDX_INTERFACE 1
    #define GIE_IDL_NODE_DISPATCH_SEQ                                      \
        (( type_namespace           , namespace_i))                        \
        (( type_aggregate           , aggregate_i))                        \
        (( type_var_decl            , var_decl_i))                         \
        (( type_type_descriptor     , type_descriptor_i))                  \
        (( type_base_type           , base_type_i))                        \
        (( type_pointer_to          , pointer_to_i))                       \
        (( type_reference_to        , reference_to_i))                     \
        (( type_function            , function_i))                         \
        (( type_function_parameters , function_parameters_i))              \
        (( type_late_bound          , late_bound_i))                       \
        /**/

    struct node_dispatch_interface
    {
        #define GIE_IDL_NODE_DISPATCH_DEF(r, aux/*aux data*/, i/*iter counter*/, def /*data*/)  \
            virtual void dispatch(  \
                BOOST_PP_TUPLE_ELEM(GIE_IDL_NODE_DISPATCH_SEQ_ITEM_SIZE, GIE_IDL_NODE_DISPATCH_IDX_INTERFACE, def)  \
                * const node)=0;    \
            /**/
        BOOST_PP_SEQ_FOR_EACH_I(GIE_IDL_NODE_DISPATCH_DEF, 0, GIE_IDL_NODE_DISPATCH_SEQ) // generate code
        #undef GIE_IDL_NODE_DISPATCH_DEF
    };

    inline void exec_node_dispatch(node_i* const node, node_dispatch_interface* const target); //forward
    namespace impl {

        template<class interface_t_t>
        struct type_to_interface_t
        {
            template<class unknown_t_t>
            static
            void do_dispatch(unknown_t_t const& node, node_dispatch_interface * const target)
            {
                const ::boost::intrusive_ptr<interface_t_t> node_as_target =
                    ::gie::ccom::query_interface_<interface_t_t>( node, ::gie::ccom::throw_on_fail() );
                target->dispatch( node_as_target.get() );
            }
        };

        template<>
        struct type_to_interface_t<late_bound_i>
        {
            template<class unknown_t_t>
            static
            void do_dispatch(unknown_t_t const& node, node_dispatch_interface * const target)
            {
                const late_bound_ptr_t& node_as_late_bound = ::gie::ccom::query_interface_<late_bound_i>( node, ::gie::ccom::throw_on_fail() );
                if( node_as_late_bound->is_boud() )
                {
                    //if( node_as_late_bound->get_latebound_type()!=type_aggregate ){GIE_LIB_NOT_IMPLEMENTED;}
                    const ::gie::ccom::std_proxy_ptr_t& node_as_std_proxy = ::gie::ccom::query_interface_<::gie::ccom::std_proxy_i>( node, ::gie::ccom::throw_on_fail() );
                    const node_i_ptr_t target_node ( node_as_std_proxy->query_host_interface_ex<node_i>(), false );
                    if( !target_node ) { GIE_LIB_NOT_IMPLEMENTED_1("late bound target should support node_i interface"); }
                    exec_node_dispatch( target_node.get(), target); //call self on an a dispatched node
                }
                else
                {
                    target->dispatch( node_as_late_bound.get() );
                }
            }
        };

    } //end of impl

    inline
    void exec_node_dispatch(node_i* const node, node_dispatch_interface* const target)
    { // TODO: redesign this function, because it is too ugly now
        GIE_LIB_IS_VALID_POINTER(node);
        GIE_LIB_IS_VALID_POINTER(target);

        #ifdef GIE_LIB_DEBUG
            const string_t& debug__node_name = get_node_name_no__fail( node );
            const string_t& debug__node_type_str = map_node_type2string( node->get_type() );
        #endif


        const type_of_node_t& current_node_type = node->get_type();
        #define GIE_IDL_NODE_SELECTOR(r, aux/*aux data*/, i/*iter counter*/, def /*data*/)  \
            if( current_node_type==BOOST_PP_TUPLE_ELEM(GIE_IDL_NODE_DISPATCH_SEQ_ITEM_SIZE, 0, def) ) \
                impl::type_to_interface_t<BOOST_PP_TUPLE_ELEM(GIE_IDL_NODE_DISPATCH_SEQ_ITEM_SIZE, 1, def)>::do_dispatch(node, target); \
                else \
            /**/

        BOOST_PP_SEQ_FOR_EACH_I(GIE_IDL_NODE_SELECTOR, 0, GIE_IDL_NODE_DISPATCH_SEQ) // generate code
        {
            GIE_LIB_NOT_IMPLEMENTED;
        }
        #undef GIE_IDL_NODE_SELECTOR
    }// end of exec_node_dispatch

    struct node_dispatch_interface_loopback_impl_t
        : node_dispatch_interface
    {
        #define GIE_IDL_NODE_DISPATCH_IMPL_DEF(r, aux/*aux data*/, i/*iter counter*/, def /*data*/)  \
            void dispatch(  \
                BOOST_PP_TUPLE_ELEM(GIE_IDL_NODE_DISPATCH_SEQ_ITEM_SIZE, GIE_IDL_NODE_DISPATCH_IDX_INTERFACE, def)  \
                * const node) {GIE_LIB_NOT_IMPLEMENTED_1("no acceptor defined for node");} \
            /**/
        BOOST_PP_SEQ_FOR_EACH_I(GIE_IDL_NODE_DISPATCH_IMPL_DEF, 0, GIE_IDL_NODE_DISPATCH_SEQ) // generate code
        #undef GIE_IDL_NODE_DISPATCH_IMPL_DEF


        void operator()(node_i* const node)
        {
            exec_node_dispatch(node, this);
        }

        template <class T>
        void operator()(const ::boost::intrusive_ptr<T>& node)
        {
            const node_i_ptr_t as_node = ::gie::ccom::query_interface_<node_i>( node, ::gie::ccom::throw_on_fail() );
            (*this)( as_node );
        }

        template <class T>
        void operator()(T* const node)
        {
            const node_i_ptr_t as_node = ::gie::ccom::query_interface_<node_i>( node, ::gie::ccom::throw_on_fail() );
            (*this)( as_node );
        }

        void operator()(const node_i_ptr_t& node)
        {
            (*this)( node.get() );
        }
    };



}
//================================================================================================================================================
#endif//H_GUARD_SEMANTIC_NODES_DISPATCH_H__16_05_2005__10_21_23
//================================================================================================================================================
