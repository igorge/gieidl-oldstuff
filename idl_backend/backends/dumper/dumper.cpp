//================================================================================================================================================
//
// (c) GIE 29.04.2005
//
//================================================================================================================================================
// NAME: dumper.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "../../idl_backend.h"
#include "../../../idl_param/param.core.h"
#include "../../idl_backend.frame.h"
#include "../../../idl_compil/semantic.builder.helper.access2string.h"
#include "../../../idl_compil/semantic.helpers.get_parent.h"
#include "../../../idl_compil/semantic.helpers.get_node_path_as_string.h"
//================================================================================================================================================
namespace gie_idl { namespace backend { namespace  dumper { 

    struct dumper_impl_t
        : backend::visitor_i
    {
        dumper_impl_t( storage_inteface::ostream_ptr_t& out )
            : out_( out )
            , curr_ident_( 0 )
        {}

        typedef std::list<string_t> strings_list_t;
        struct var_decl_context
        {
            std::list<string_t> dump_items;
        };

        // function /member
        virtual void do_visit(frame_i* const frame, function_i* const node, const string_t& name, type_descriptor_i* const ret_type, function_parameters_i* const function_parameters)
        {
            new_line();*do_ident_();
            do_visit( frame, ret_type, NULL ); //new context
            *out_ << wxT(' ') << name <<wxT('(');
            frame->frame_visit( function_parameters, NULL ); // new context
            *out_ << wxT(");");
        }
        virtual void do_visit_function_parameter(frame_i* const frame, var_decl_i * const node,  const string_t& name, const unsigned int pos)
        {
            if( pos ) { *out_<< wxT(", "); }
            frame->frame_visit(node,NULL);
            *out_<<wxT(' ')<<name;
        }
        // member var decl
        void do_visit(frame_i* const frame, var_decl_i * const node,  const string_t& name, type_descriptor_i* const type_descriptor)
        {
            new_line();

            *do_ident_();

            frame->frame_visit(node, NULL);

            *out_<< name << wxT(";\n");

        }

        // type info visitors
        virtual void do_visit(frame_i* const frame, type_descriptor_i* const node, void* const user_context)
        {
            var_decl_context ctx;
            frame->frame_visit(node, &ctx); 

            strings_list_t::const_iterator i = ctx.dump_items.begin();
            const strings_list_t::const_iterator& end = ctx.dump_items.end();

            while( i!=end )
            {
                *out_<<*i<<wxT(' ');
                ++i;
            }
        }

        virtual void do_visit(frame_i* const frame, base_type_i* const node, void* const user_context)
        {
            const type_descriptor_info_ptr_t& type_descriptor_info = ::gie::ccom::query_interface_<type_descriptor_info_i>( node, ::gie::ccom::throw_on_fail() );
            var_decl_context& ctx = *( reinterpret_cast<var_decl_context*const>(user_context) );

            if( type_descriptor_info->is_mod_enabled(tim_const) )
                ctx.dump_items.push_front( wxT("const") );

            ctx.dump_items.push_front( get_node_path_as_string( type_descriptor_info->get_next_sub_type() ) );
        }

        virtual void do_visit(frame_i* const frame, pointer_to_i* const node, void* const user_context)
        {
            GIE_LIB_ASSERTE( user_context );
            const type_descriptor_info_ptr_t& type_descriptor_info = ::gie::ccom::query_interface_<type_descriptor_info_i>( node, ::gie::ccom::throw_on_fail() );
            var_decl_context& ctx = *( reinterpret_cast<var_decl_context*const>(user_context) );

            if( type_descriptor_info->is_mod_enabled(tim_const) )
                ctx.dump_items.push_front( wxT("const") );

            ctx.dump_items.push_front( wxT("*") );

            frame->frame_visit(node, user_context);
        }

        virtual void do_visit(frame_i* const frame, reference_to_i* const node, void* const user_context)
        {
            GIE_LIB_ASSERTE( user_context );
            var_decl_context& ctx = *( reinterpret_cast<var_decl_context*const>(user_context) );

            ctx.dump_items.push_front( wxT("&") );

            frame->frame_visit(node, user_context);
        }

        
        // namespace hooks
        void do_before_visit_traverse(namespace_i * const node,  const string_t& name)
        {
            new_line();
            *do_ident_() << wxT("namespace ") << name << wxT(" { //traverse\n");
            curr_ident_ +=4;
        }
        void do_after_visit_traverse(namespace_i * const node,  const string_t& name)
        {
            //GIE_LIB_IS_VALID_POINTER(node);
            curr_ident_ -=4;
            new_line();
            *do_ident_() << wxT("}\n");// << name << wxT('\n');
        }

        void do_visit(frame_i* const frame, namespace_i * const node, const string_t& name)
        {
            new_line();
            *do_ident_() << wxT("namespace ") << name << wxT(" {\n");
            curr_ident_ +=4;
           
            frame->frame_visit( node );

            curr_ident_ -=4;
            new_line();
            *do_ident_() << wxT("}\n");// << name << wxT('\n');
        }

       
        //
        // aggregate hooks
        //

        void do_ancestor_visit_decoded(aggregate_i * const node,  const string_t& fq_path,  const access_t& inh_access,  const string_t& inh_access_as_string, void* const user_context)
        {
            GIE_LIB_IS_VALID_POINTER( reinterpret_cast<ancestors_visit_context_t*const>(user_context) );

            ancestors_visit_context_t& context = *reinterpret_cast<ancestors_visit_context_t*const>(user_context);

            if( context.is_first_ancestor )
            {
                context.is_first_ancestor=false;
                *do_ident_() << wxT(": ");
            }
            else
            {
                *do_ident_() << wxT(", ");
            }
            *out_ << inh_access_as_string<<wxT(' ');
            *out_ << fq_path << wxT('\n');
        }

        void do_ancestor_visit_decoded(late_bound_i * const node,  const string_t& symbol, const access_t& inh_access,  const string_t& inh_access_as_string, void* const user_context)
        {
            GIE_LIB_IS_VALID_POINTER( reinterpret_cast<ancestors_visit_context_t*const>(user_context) );
            
            ancestors_visit_context_t& context = *reinterpret_cast<ancestors_visit_context_t*const>(user_context);

            if( context.is_first_ancestor )
            {
                context.is_first_ancestor=false;
                *do_ident_() << wxT(": ");
            }
            else
            {
                *do_ident_() << wxT(", ");
            }
            *out_ << inh_access_as_string<<wxT(' ');
            *out_ << symbol << wxT(" /* !!! undefined symbol !!! */\n");
        }

        void do_visit(frame_i* const frame, aggregate_i * const node,  const string_t& name)
        {
            new_line();
            *do_ident_();
            
            //if parent is aggregate then check and dump access spec
            const aggregate_ptr_t& parent = get_parent<aggregate_i>( node );
            if( parent )
            {
                *out_ << map_access2string( get_access( node, access_public ) ) << wxT(":\n");
                *do_ident_();
            }

            *out_ << wxT("struct ") << name << wxT('\n');

            ancestors_visit_context_t ancestors_visit_context;
            frame->frame_ancestors_visit(node, &ancestors_visit_context);

            *do_ident_() << wxT("{\n");
            curr_ident_ +=4;

            frame->frame_visit(node); //recursively ask frame to visit this node, frame will visit childs

            curr_ident_ -=4;
            new_line();
            *do_ident_() << wxT("};\n");// << name << wxT('\n');

        }
    private:
        struct ancestors_visit_context_t
        {
            ancestors_visit_context_t()
                : is_first_ancestor (true)
            {}
            bool is_first_ancestor;
        };

        storage_inteface::ostream_ptr_t& do_ident_()
        {
            unsigned int ident = curr_ident_;
            while( ident )
            {
                *out_ << wxT(' ');
                --ident;
            }
            return out_;
        }
        void new_line()
        {
            *out_ << wxT('\n');
        }
    private:
        storage_inteface::ostream_ptr_t& out_;
        unsigned int curr_ident_;
    };


    const char_t file_root_common_key[]  = wxT("output-file");

    template < template <class> class walker_extender_t_t >
    struct backend_t
        : backend_interface
    {
        void exec( const semantic_tree_holder_ptr_t& tree_holder, storage_inteface& storage, const options_ptr_t& options)
        {
            static char_t const * const file_header = wxT("// Machine generated, do not edit.\n// This is a dump of an INTERAL tree.\n\n");

            if( !options->count(file_root_common_key ) )
            {
                GIE_LIB_NOT_IMPLEMENTED_1("output-file not given");
            }
            const string_t& out_name = (*options)[file_root_common_key].as<std::string>().c_str();

            {
                storage_inteface::ostream_ptr_t out ( storage.create_ostream(out_name) );
                *out << file_header;
                dumper_impl_t this_dumper(out);
                default_walker_t<walker_extender_t_t> walker( &this_dumper );
                walker.visit( tree_holder->get_root_node().get() );
            }

        }
    };


} } }

namespace gie_idl { // meta info support
    void backend_dump_get_desc__(backend_options_description_t& desc)
    {
        namespace po = ::boost::program_options;

        desc.add_options()
            ( backend::dumper::file_root_common_key, po::value<std::string>(), wxT("output file name") )
            ;

    }

    const backend::backend_interface_ptr_t backend_dump_create___()
    {
        return backend::backend_interface_ptr_t( new backend::dumper::backend_t<backend::null_walker_extender_t>() );
    }

    void backend_forward_resolver_dump_get_desc__(backend_options_description_t& desc)
    {
        namespace po = ::boost::program_options;

        desc.add_options()
            ( backend::dumper::file_root_common_key, po::value<std::string>(), wxT("output file name") )
            ;

    }

    const backend::backend_interface_ptr_t backend_forward_resolver_dump_create___()
    {
        return backend::backend_interface_ptr_t( new backend::dumper::backend_t<backend::resolve_forward_walker_extrender_t>() );
    }
}
//================================================================================================================================================
