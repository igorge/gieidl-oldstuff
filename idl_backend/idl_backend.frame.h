//================================================================================================================================================
//
// (c) GIE 29.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_IDL_BACKEND_FRAME_H__29_04_2005__16_22_52
#define H_GUARD_IDL_BACKEND_FRAME_H__29_04_2005__16_22_52
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../idl_compil/visitors/semantic.nodes.dispatch.h"

#include "../idl_compil/semantic.helpers.get_parent.h"
#include "../idl_compil/semantic.required_symbols.interfaces.h"

#include "../idl_compil/semantic.helpers.id2string.h"
#include "../idl_compil/semantic.helpers.get_node_name.h"
#include "idl_backend.frame.helpres.enumerators.h"
#include "idl_backend.frame.interfaces.h"
#include "idl_backend.frame.helpres.h"

#include "gielib/giecom/giecom.server.stackbased.simple.h"
#include "gielib/giecom/giecom.stdproxy.client.h"

#include <set>
//================================================================================================================================================
namespace gie_idl { namespace backend {


    //
    // null_walker_extender_t
    //
    template <class walker_t_t>
    struct null_walker_extender_t
    {
        template<class interface_t_t>
        void ex_about_to_visit(interface_t_t * const node,  const string_t& name){}
        void ex_clear_state(){};
        template<class interface_t_t>
        bool ex_should_be_visited(interface_t_t * const node, const string_t& name)
        {
            return true;
        }
    private:
    };

    //
    // resolve_forward_walker_extrender_t
    //
    template < class walker_t_t>
    struct resolve_forward_walker_extrender_t
    {
        typedef resolve_forward_walker_extrender_t<walker_t_t> this_t;

        friend required_symbols_enum_t<this_t>;


        template<class interface_t_t>
        bool ex_should_be_visited(interface_t_t * const node, const string_t& name)
        {
            const unknown_ptr_t& node_id = ::gie::ccom::get_identity_interface(node);
            const visited_map_t::const_iterator loc = visited_nodes_.find( node_id );

            return( loc==visited_nodes_.end() );
        }

        void ex_clear_state()
        {
            visited_nodes_.clear();                    
        }
        template<class interface_t_t>
        void ex_about_to_visit(interface_t_t * const node,  const string_t& name)
        {
            ex_about_to_visit_compound( node, name );
        }


        template<class interface_t_t>
        void ex_about_to_visit_compound(interface_t_t * const node,  const string_t& name) //TODO: rename, couse this func is general, not only compound
        {
            GIE_LIB_IS_VALID_POINTER(node);

            #ifdef GIE_LIB_DEBUG
                const string_t& debug__node_name_super = get_node_name_no__fail( node );
                //const string_t& debug__node_type_str_super = map_node_type2string( node->get_type() );
            #endif

            const unknown_ptr_t& node_id = ::gie::ccom::get_identity_interface(node);
            const visited_map_t::const_iterator loc = visited_nodes_.find( node_id );

            if( loc==visited_nodes_.end() ) //if we yet have not visited
            {
                if( is_already_in_progress(node) )
                {
                    GIE_LIB_NOT_IMPLEMENTED_1("infinite recursion detected"); //define action for recursion
                }


                //query required_symbols_i and rock'n'roll
                const required_symbols_ptr_t& required_symbols = ::gie::ccom::query_interface_<required_symbols_i>( node, ::gie::ccom::throw_on_fail() );

                mark_as_in_progress(node); //to detect cyclic refs
                required_symbols->enumerate_required_symbols( &required_symbols_enum_t<this_t>( *this, node ) );
                unmark_as_in_progress(node);

                const std::pair<visited_map_t::iterator, bool> r = visited_nodes_.insert(node_id);
                GIE_LIB_ASSERTE( r.second ); //should be inserted
            }
        }


    public:
        template <class interface_t_t> bool is_already_in_progress(interface_t_t* const node)
        {
            return !( in_progress_.find( ::gie::ccom::get_identity_interface(node) ) == in_progress_.end() );
        }
        template <class interface_t_t> void mark_as_in_progress(interface_t_t* const node)
        {
            const ::std::pair<in_progress_map_t::iterator, bool>& r =
                in_progress_.insert( ::gie::ccom::get_identity_interface(node) );
            GIE_LIB_ASSERTE(r.second);
        }
        template <class interface_t_t> void unmark_as_in_progress(interface_t_t* const node)
        {
            if( in_progress_.erase( ::gie::ccom::get_identity_interface(node) )!=1 )
            {
                GIE_LIB_NOT_IMPLEMENTED;
            }
        }
    private:
        typedef std::set<unknown_ptr_t> in_progress_map_t;
        in_progress_map_t in_progress_;


    private:
        typedef std::set<unknown_ptr_t> visited_map_t;
        visited_map_t visited_nodes_;

    private:
        void ask_walker_to_visit(node_i* const node)
        {
            walker_t_t::node_enumerator_adapter_t enumerator( *self_this() );
            enumerator.enumerate_this(node, get_node_name(node) );
        }
        void ask_walker_to_visit_with_traverse(node_i* const from_node, node_i* const node)
        {
            self_this()->visit_with_traverse(from_node, node);
        }

    private:
        walker_t_t* const self_this()
        {
            return static_cast<walker_t_t* const>(this);
        }
        walker_t_t const * const self_this()const
        {
            return static_cast<walker_t_t* const>(this);
        }
    };

    //
    // default_walker_t
    //
    template< template <class> class walker_extender_t_t = null_walker_extender_t>
    struct default_walker_t
        : protected walker_extender_t_t< default_walker_t<walker_extender_t_t> > //extend self and give info about us to extender
        , frame_i
    {
        friend walker_extender_t_t<default_walker_t>; //make it friend of mine

        default_walker_t(visitor_i* const  user_hooks)
            : user_hooks_ ( user_hooks )
        {}

        void visit(node_i* const node)
        {
            if( !node )
            {
                GIE_LIB_NOT_IMPLEMENTED;
            }

            this->ex_clear_state();
            visit_named_collection( node );

        }
    public:
        //
        // frame_i support
        //

        void frame_visit(aggregate_i * const node)
        {
            visit_named_collection( node );
        }
        void frame_visit(namespace_i * const node)
        {
            visit_named_collection( node );
        }

        void frame_ancestors_visit(aggregate_i * const node, void * const user_context)
        {
            ancestor_enumerator_adapter_t ancestor_enumerator( *this, user_context );
            node->enumerate_encestors( &ancestor_enumerator );
        }
        

        void frame_visit(var_decl_i * const node, void * const user_context)
        {
            const type_descriptor_ptr_t& type_descriptor = node->get_type();
            user_hooks_->do_visit( this, type_descriptor.get(), user_context);
        }

        virtual void frame_visit(type_descriptor_i* const node, void* const user_context)
        {
            visit_type_descriptor_info_(node, user_context);
        }
        virtual void frame_visit(pointer_to_i* const node, void* const user_context)
        {
            visit_type_descriptor_info_(node, user_context);
        }
        virtual void frame_visit(reference_to_i* const node, void* const user_context)
        {
            visit_type_descriptor_info_(node, user_context);
        }

        void frame_visit(function_parameters_i* const node, void* const user_context)
        {
            unsigned int no=0;
            node->enumerate_parameters(
                &(function_parameters_enumerator_t( *this, user_context, no ))
            );
        }
    
    private:
        struct function_parameters_enumerator_t
            : ::gie::ccom::stack_based_simple_unknown_impl_t<named_node_enum_callback_i>
        {
            function_parameters_enumerator_t(default_walker_t& walker, void* const user_context, unsigned int& no)
                : walker_( walker )
                , user_context_( user_context )
                , no_( no )
            {}

            action_t enumerate_this(node_i* const node, const string_t& name)
            {
                const var_decl_ptr_t node_as_var = :: gie::ccom::query_interface_<var_decl_i>( node, ::gie::ccom::throw_on_fail() );
                walker_.user_hooks()->do_visit_function_parameter( &walker_, node_as_var.get(), name, no_);
                ++no_;
                return continue_enumeration;
            }
        private:
            default_walker_t& walker_;
            void* const user_context_;
            unsigned int& no_;
        };
  
    private:
        struct type_descriptor_info_node_action_t : node_dispatch_interface_loopback_impl_t
        {
            type_descriptor_info_node_action_t(default_walker_t& context, void* const user_context): context_(context), user_context_(user_context){}
            void dispatch(base_type_i* const node) 
            {
                context_.user_hooks()->do_visit( &context_, node,  user_context_);
            }
            void dispatch(pointer_to_i* const node) 
            {
                context_.user_hooks()->do_visit( &context_, node,  user_context_);
            }
            void dispatch(reference_to_i* const node) 
            {
                context_.user_hooks()->do_visit( &context_, node,  user_context_);
            }
        private: default_walker_t& context_;
                 void* const user_context_;
        };

        void visit_type_descriptor_info_(::gie::ccom::unknown_i* const node, void* const user_context)
        {
            const type_descriptor_info_ptr_t& type_descriptor = ::gie::ccom::query_interface_<type_descriptor_info_i>( node, ::gie::ccom::throw_on_fail() );
            type_descriptor_info_node_action_t(*this, user_context)( type_descriptor->get_next_sub_type() );
        }

    private:
        
        template <class interface_t_t>
        void visit_named_collection(interface_t_t* const node)
        {
            const named_collection_ptr_t& node_collection = ::gie::ccom::query_interface_<named_collection_i>( node, ::gie::ccom::throw_on_fail() );
            visit_named_collection( node_collection.get() );
        }

        template <>
        void visit_named_collection<named_collection_i>(named_collection_i* const node)
        {
            node_enumerator_adapter_t enumerator( *this );
            node->enumerate_nodes( &enumerator );
        }

        // namespace
        void visit(namespace_i * const node, const string_t& name )
        {
            if( this->ex_should_be_visited(node,  name) )
            {
                if( user_hooks()->do_visit_decision(node,  name) )
                {
                    this->ex_about_to_visit( node,  name );

                    user_hooks()->do_visit( this, node,  name );
                }
            }
        }

        // aggregate
        void visit(aggregate_i * const node,  const string_t& name )
        {
            if( this->ex_should_be_visited(node,  name) )
            {
                if( user_hooks()->do_visit_decision(node,  name) )
                {
                    this->ex_about_to_visit( node,  name );
                    user_hooks()->do_visit(this, node,  name );
                }
            }// if reported to be visited by extender
        }

        // var_decl
        void visit(var_decl_i * const node,  const string_t& name )
        {
            if( this->ex_should_be_visited(node,  name) )
            {
                if( user_hooks()->do_visit_decision(node,  name) )
                {
                    const type_descriptor_ptr_t& type_descriptor = node->get_type();
                    this->ex_about_to_visit( node,  name );
                    user_hooks()->do_visit(this, node,  name, type_descriptor.get() );
                }
            }
        }

        // function
        void visit(function_i * const node,  const string_t& name )
        {
            if( this->ex_should_be_visited(node,  name) )
            {
                if( user_hooks()->do_visit_decision(node,  name) )
                {
                    this->ex_about_to_visit( node,  name );
                    user_hooks()->do_visit( this, node,  name, node->get_return_type().get(), node->get_parameters().get()  );
                }
            }
        }
    private:
        bool visit_decision_(node_i* const node, const string_t& name)
        {
            //TODO: call user hook
            return true;
        }

        void visit_with_traverse(node_i* const from_node, node_i* const node)
        {
            GIE_LIB_IS_VALID_POINTER(from_node);
            GIE_LIB_IS_VALID_POINTER(node);

            #ifdef GIE_LIB_DEBUG
                const string_t& debug__from_node_name = get_node_name( from_node );
            #endif
            const named_ptr_t node_as_named = ::gie::ccom::query_interface_<named_i>( node, ::gie::ccom::throw_on_fail() );
            if( !visit_decision_(node,  node_as_named->get_name()) ) return;

            typedef std::list<const node_i_ptr_t> path_t;
            path_t path_;

            node_i_ptr_t current_path_item = get_parent<node_i>(node);
            for(;;)
            {
                #ifdef GIE_LIB_DEBUG
                    const string_t& debug__node_name = get_node_name( current_path_item );
                #endif
                if( !current_path_item ){ GIE_LIB_NOT_IMPLEMENTED_1("root node (or internal inconsistency) detected") };
                path_.push_front( current_path_item );
                if( ::gie::ccom::is_same(current_path_item.get(), from_node) ) break;
                
                current_path_item = get_parent<node_i>(current_path_item);
            }

            path_t::const_iterator& current = path_.begin();
            const path_t::const_iterator& end = path_.end();
            while( current!=end )
            {
                node_traverse_action_t ac( user_hooks(), &visitor_i::do_before_visit_traverse ) ;
                ac( current->get() );
                ++current;
            }

            node_enumerator_adapter_t( *this ).enumerate_this( node, node_as_named->get_name() );

            path_t::reverse_iterator& r_current = path_.rbegin(); //for unknown (for me) reason const_reverse_iterator does not compile under MS C++7.1
            const path_t::reverse_iterator& r_end = path_.rend();
            while( r_current!=r_end )
            {
                node_traverse_action_t ac( user_hooks(), &visitor_i::do_after_visit_traverse ) ;
                ac( r_current->get() );
                ++r_current;
            }
        }

        struct node_traverse_action_t : node_dispatch_interface_loopback_impl_t
        {
            node_traverse_action_t(visitor_i* const user_hooks, void (visitor_i::* const invoke_action)(namespace_i * const node,  const string_t& name) ) 
                : user_hooks_( user_hooks )
                , invoke_action_( invoke_action ){}
            void dispatch(namespace_i* const node) 
            {
                 (user_hooks_->*invoke_action_)( node, get_node_name( node ) );
            }
        private: visitor_i* const user_hooks_;
        void (visitor_i::* const invoke_action_)(namespace_i * const node,  const string_t& name);
        };



        //
        // node enumeration adapter
        //
        struct node_enumerator_adapter_t
            : ::gie::ccom::stack_based_simple_unknown_impl_t<named_node_enum_callback_i>
        {
            //simple adapter class
            node_enumerator_adapter_t( default_walker_t& walker )
                : walker_ ( walker )
            {}
            
            struct node_action_t : node_dispatch_interface_loopback_impl_t
            {
                node_action_t(node_enumerator_adapter_t& context, const string_t& name): context_(context), name_(name){}
                void dispatch(aggregate_i* const node) {context_.walker_.visit( node, name_ );}
                void dispatch(namespace_i* const node) {context_.walker_.visit( node, name_ );}
                void dispatch(var_decl_i* const node)  {context_.walker_.visit( node, name_ );}
                void dispatch(function_i* const node)  {context_.walker_.visit( node, name_ );}
            private: const node_enumerator_adapter_t& context_;
                     const string_t& name_;
            };

            action_t enumerate_this(node_i* const node,  const string_t& name)
            {
                node_action_t(*this, name)(node);
                return continue_enumeration;
            }

        private:
            default_walker_t& walker_;
        };// end of node_enumerator_adapter_t
       

        //
        // ancestor enumeration adapter
        //
        struct ancestor_enumerator_adapter_t
            : ::gie::ccom::stack_based_simple_unknown_impl_t<ancestor_enum_callback_i>
        {
            //simple adapter class
            ancestor_enumerator_adapter_t( default_walker_t& walker, void* const user_context )
                : walker_ ( walker )
                , user_context_( user_context )
            {}
           
            struct ancestor_visit_action_t : node_dispatch_interface_loopback_impl_t
            {
                ancestor_visit_action_t(ancestor_enumerator_adapter_t& context, const access_t& access)
                    : context_(context), access_(access){}
                void dispatch(aggregate_i* const node) 
                {
                    context_.walker_.user_hooks()->do_ancestor_visit( node, access_, context_.user_context_);
                }
                void dispatch(late_bound_i* const node) 
                {
                    const fq_id_ptr_t& undefined_symbol = node->get_id();
                    context_.walker_.user_hooks()->do_ancestor_visit(node, access_, context_.user_context_);
                }
            private: 
                const ancestor_enumerator_adapter_t& context_;
                const access_t& access_;
            };

            action_t enumerate_this(node_i* const node,  const access_t& access)
            {
                ancestor_visit_action_t(*this, access)(node);
                return continue_enumeration;
            }

        private:
            default_walker_t& walker_;
            void* const user_context_;
        };// end of node_enumerator_adapter_t

    private:
        visitor_i* const user_hooks()const throw(){ return user_hooks_; }

        visitor_i* const  user_hooks_;
    };// end of default_walker_t


} }
//================================================================================================================================================
#endif//H_GUARD_IDL_BACKEND_FRAME_H__29_04_2005__16_22_52
//================================================================================================================================================
