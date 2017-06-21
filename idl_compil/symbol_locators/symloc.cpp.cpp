//================================================================================================================================================
//
// (c) GIE 22.05.2005
//
//================================================================================================================================================
// NAME: symloc.cpp.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "../semantic.attributes.h"
#include "../semantic.helpers.get_parent.h"
#include "../semantic.helpers.get_node_name.h"
#include "../semantic.helpers.id2string.h"
#include "../semantic.helpers.node_type2string.h"

#include "symloc.factory.h"
#include "ambiguity_resolver.adapter.h"
#include "gielib/giecom/giecom.server.h"

#include <map>
//================================================================================================================================================
namespace gie_idl {

    typedef gie::ccom::list<symbol_locator_i> cpp_like_symol_locator_interfaces_t;

    struct cpp_like_symol_locator_t
        : gie::ccom::c_object_root_t
          <
             cpp_like_symol_locator_t,           //self type
             symbol_locator_i ,               //unknown from this interface
             cpp_like_symol_locator_interfaces_t     //supported interfaces
          >
    {
        const node_i_ptr_t locate_symbol(node_i* const referrers_scope, const fq_id_ptr_t& id, node_i* const root, const resolver_id_t& resolver_id, ::gie::ccom::unknown_i* const resolver_context)
        {
            GIE_LIB_IS_VALID_POINTER( referrers_scope );
            GIE_LIB_IS_VALID_POINTER( id.get() );
            GIE_LIB_ASSERTE( root->get_parent()==NULL );
            
            const symloc_context_t symloc_context(referrers_scope, id, root, resolver_id, resolver_context);

            #ifdef GIE_LIB_DEBUG
                const string_t& debug__node_type = map_node_type2string( referrers_scope->get_type() );
                const string_t& debug__id = map_id2string( id );
                const string_t& debug__refs_scoped_name = get_node_name_no__fail( referrers_scope );
            #endif

            fq_id_t::const_iterator& i = id->begin();
            const fq_id_t::const_iterator& end   = id->end();
            node_i_ptr_t curr_search_from;
            if( id->is_fq() )
            {
                curr_search_from = root;
                ++i;
            }
            else
            {
                curr_search_from = referrers_scope;
            }

            // search loop (move from inner to upper scope in order to locate first macth symbol)

            while( curr_search_from ) // while we have to search from
            {
                #ifdef GIE_LIB_DEBUG
                    const string_t& debug__curr_search_from_type = map_node_type2string( curr_search_from->get_type() );
                    const string_t& debug__curr_search_from_name = get_node_name_no__fail( curr_search_from );
                #endif

                const node_i_ptr_t located_node = locate_node_(curr_search_from, i, end, symloc_context);
                if( located_node ) return located_node;

                //get upper scope (if we failed to found in inner)
                curr_search_from = get_parent<node_i>( curr_search_from );
                i = id->begin();

            }

            return NULL;
        }

        cpp_like_symol_locator_t()
        {
            //TODO: NOW ALL AMBIGUITY RESOLVERS ARE HARDCODED !!! // FIX THIS
            if( !ambiguity_resolvers_.insert( std::make_pair(ambiguity_resolver_aggregate, create_ambiguity_resolver_aggregate()) ).second ) {GIE_LIB_NOT_IMPLEMENTED_1("only one ambiguity resolver for each type allowed");}
            if( !ambiguity_resolvers_.insert( std::make_pair(ambiguity_resolver_symbol_locator, create_ambiguity_resolver_symbol_locator()) ).second) {GIE_LIB_NOT_IMPLEMENTED_1("only one ambiguity resolver for each type allowed");}
        }
    private:
        typedef ::std::map<::gie::ccom::guid_t, ambiguity_resolver_ptr_t> ambiguity_resolvers_map_t;
        ambiguity_resolvers_map_t ambiguity_resolvers_;
        
        const ambiguity_resolver_ptr_t& get_resolver_(const resolver_id_t& resolver_id)const
        {
            const ambiguity_resolvers_map_t::const_iterator& iter = ambiguity_resolvers_.find( resolver_id );
            if( iter == ambiguity_resolvers_.end() ) { GIE_LIB_NOT_IMPLEMENTED_1("ambiguity resolver not found"); }
            return iter->second;
        }

        struct symloc_context_t
        {
            symloc_context_t(node_i* const& referrers_scope, const fq_id_ptr_t& id, node_i* const& root, const resolver_id_t& resolver_id, ::gie::ccom::unknown_i* const& resolver_context)
                : referrers_scope_( referrers_scope )
                , root_( root )
                , resolver_id_( resolver_id )
                , resolver_contex_( resolver_context )
            {}
            node_i* const& referrers_scope_;
            node_i* const& root_;
            const resolver_id_t& resolver_id_;
            ::gie::ccom::unknown_i* const& resolver_contex_;
        };

    private:
        typedef ::boost::tuple<const node_i_ptr_t, const access_t> openned_scope_t;
        
        //
        //
        //
        
        openned_scope_t open_scope(const node_i_ptr_t& current_scope, const string_t& scope_name, const symloc_context_t& symloc_context)
        {
            const symbol_resolution_ptr_t& symbol_resolution = ::gie::ccom::query_interface<symbol_resolution_i>( current_scope );
            if( symbol_resolution )
            {
                GIE_LIB_NOT_IMPLEMENTED;
            }
            else
            {   
                named_collection_ptr_t curr_collection = ::gie::ccom::query_interface<named_collection_i>( current_scope );
                if( !curr_collection ) return openned_scope_t(NULL); // given scope does not supports symbol resolution at all
                //const node_i_ptr_t& located_symbol = (*curr_collection)[ scope_name ];
                enum_to_ambiguity_resolver_adapter_t node_selector( get_resolver_( ambiguity_resolver_symbol_locator ), symloc_context.resolver_contex_ );
                curr_collection->locate_node( scope_name, &node_selector );
                const node_i_ptr_t& located_symbol = node_selector.best_candidate();
                if( !located_symbol ) return openned_scope_t(NULL); 
                return openned_scope_t( located_symbol, get_access(located_symbol, access_public) );
            }
        }
        //
        // when walking from referrers scope to root and we have walked onto target_scope then we have full access to that scope
        //
        
        bool do_we_have_full_access_(const node_i_ptr_t& target_scope, const symloc_context_t& symloc_context)
        {
            #ifdef GIE_LIB_DEBUG
                const string_t& debug__target_scope_name = get_node_name_no__fail( target_scope );
            #endif
            node_i_ptr_t current_node = symloc_context.referrers_scope_;
            while( current_node )
            {
                #ifdef GIE_LIB_DEBUG
                    const string_t& debug__refs_scoped_name = get_node_name_no__fail( current_node );
                #endif

                if( ::gie::ccom::is_same(current_node, target_scope) ) return true;
                current_node = get_parent<node_i>(current_node);
            }
            return false;
        }
        //
        //
        //
        inline 
        const node_i_ptr_t locate_node_(const node_i_ptr_t& search_from, const fq_id_t::const_iterator& begin, const fq_id_t::const_iterator& end, const symloc_context_t& symloc_context)
        {   GIE_IDL_ST_TRACE_FUNC;

            fq_id_t::const_iterator i = begin;
            if( i==end ){GIE_LIB_NOT_IMPLEMENTED;}

            node_i_ptr_t current_scope = search_from;

            for(;;)
            {
                const openned_scope_t& located_symbol = open_scope( current_scope, *i, symloc_context);
                if( !located_symbol.get<0>() ) return NULL; // not found
                //check for access
                if( located_symbol.get<1>()!=access_public )
                    if( !do_we_have_full_access_( current_scope, symloc_context ) )  return NULL;

                //go to next path symbol
                if( ++i==end )
                    return located_symbol.get<0>(); //found requested terminal symbol
                else
                    current_scope = located_symbol.get<0>();

            }

            return NULL;
        } // end of locate_node_

    }; // end of struct
    typedef gie::ccom::c_object_t<cpp_like_symol_locator_t> cpp_like_symol_locator_com;


    const symbol_locator_ptr_t create_cpp_like_symbol_locator()
    {
        return symbol_locator_ptr_t( cpp_like_symol_locator_com::create<symbol_locator_i>(), false );
    }


}
//================================================================================================================================================
