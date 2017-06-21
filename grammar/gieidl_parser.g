header "pre_include_cpp" 
{
    // gets inserted before the antlr generated includes in the cpp file
    /////////////////////////////////////////////////////////////////////////////
    #include "stdafx.h"
    
    #pragma warning( disable : 4267 )
    /////////////////////////////////////////////////////////////////////////////
    //
}

header
{
    // Header here
    #include "../../grammar.helpers/parser.helper.h"
    #include "../../grammar.helpers/parser.helper.function.h"
    #include "../../idl_compil/semantic.builder.interfaces.h"
    #include "../../trace/gie_idl_trace.h"
    
    
    //DEPRECATED
    //#include "../../ast/nodes/factory.h"
    //#include "../../tree_helpers/line_information.h"
    
    //typedef gie::gie_idl::ast::nodes::node_auto_ptr_t ast_node;
    typedef gie_idl::grammar::context_info_t          context_t;
}

options
{
	language="Cpp";
}


///////////////////////////////////////////////////////////////////////////////
// parser
///////////////////////////////////////////////////////////////////////////////
class gieidl_parser extends Parser;
options 
{
	genHashLines = true;		// include line number information
	defaultErrorHandler=false;
	//k =2;
	//exportVocab=gieidl_grammar;
	importVocab=gieidl_lexer;
	//buildAST = true;			// uses CommonAST by default
}
{
    private:
        //gie::gie_idl::ast::nodes::factory_t   factory_;
        //gie_idl::string_table_t               string_table_;
        
    public:
        void set_semantic_tree_holder(const boost::intrusive_ptr<gie_idl::semantic_tree_holder_i>& holder)
        {
            semantic_tree_holder_ = holder;
        }
        void set_symbol_locator(const gie_idl::symbol_locator_ptr_t& locator)
        {
            symbol_locator_ = locator;            
        }
        
    private:
        boost::intrusive_ptr<gie_idl::semantic_tree_holder_i> semantic_tree_holder_;
        gie_idl::symbol_locator_ptr_t                                  symbol_locator_;
}

curr_symbol
        {   GIE_IDL_GRAMMAR_TRACE_FUNC;
        }
        : global_namespace
        ;

//================================================================================================================================================
// global
//================================================================================================================================================
    global_namespace
        {   GIE_IDL_GRAMMAR_TRACE_FUNC;
            context_t context( semantic_tree_holder_->get_root_node() );
        }
        : ( namespace_item[context] )*
          EOF
        ;

namespace_item [const context_t& this_context]
        {   
            GIE_IDL_GRAMMAR_TRACE_FUNC
        }
        : aggregate_definition[this_context]
        | namespace_def[this_context]
        ;
        
namespace_def [const context_t& this_context]
        {   GIE_IDL_GRAMMAR_TRACE_FUNC;
        
            const gie_idl::namespace_node_ptr_t& parent_node = gie::ccom::query_interface_<gie_idl::namespace_i>( this_context.get_parent(), gie::ccom::throw_on_fail() );
            gie_idl::namespace_node_ptr_t this_node;
        }
        :   KW_NAMESPACE
            id:IDENTIFIER      {this_node = parent_node->create_inner_namespace( id->getText() ).first; }
            LCURLY 
                ( namespace_item[ context_t(this_node) ] )*
            RCURLY
        ;
        
//================================================================================================================================================
// aggregate
//================================================================================================================================================
aggregate_definition [const context_t& this_context]
        {
            GIE_IDL_GRAMMAR_TRACE_FUNC;
            gie_idl::aggregate_ptr_t this_aggregate;
            const gie_idl::named_collection_i_ptr_t& parent_node = gie::ccom::query_interface_<gie_idl::named_collection_i>( this_context.get_parent(), gie::ccom::throw_on_fail() );
            gie::ccom::guid_t default_access_spec;
            gie::ccom::guid_t aggregate_type;
        }
        : ( (attributes)?   //TODO
            (aggregate_type = aggregate_type_info) { default_access_spec = gie_idl::map_default_aggregate_access(aggregate_type); }
            aggregate_id:IDENTIFIER
                    {
                        
                        this_aggregate = gie_idl::create_aggregate_node( aggregate_id->getText() );
                        
                        if(this_context.get_attr_repo())
                            gie_idl::set_attribute_repository(this_aggregate, this_context.get_attr_repo() );
                            
                        const gie_idl::insert_child_result_t& r = parent_node->insert_child(this_aggregate.get() );
                        if( r.get<1>() ) // 0 - node, 1 - inserted or not
                        {
                            //inserted ok
                        }
                        else
                        {
                            //TODO: implement aggregate comparation
                            GIE_LIB_NOT_IMPLEMENTED;
                        }
                    }
            ( aggregate_inheretance_list[ this_context, this_aggregate, default_access_spec ] )?
            LCURLY
                (aggregate_definition_body_item_definition[ context_t(this_aggregate), default_access_spec ])*
                (aggregate_definition_body_item_w_access_definition[ context_t(this_aggregate) ])*
            RCURLY 
            SEMI
           )
        ;
        
aggregate_inheretance_list [const context_t& this_context, gie_idl::aggregate_ptr_t& this_aggregate, const gie::ccom::guid_t& default_access_spec]
        {
            GIE_IDL_GRAMMAR_TRACE_FUNC;
            gie_idl::fq_id_ptr_t id;
            gie::ccom::guid_t access = default_access_spec;
        }
        :   COLON
            ( 
                ( access = aggregate_inheretance_access_sepcifiers )? 
                id = fq_id
                {
                    create_inheretance_info(this_aggregate, id, semantic_tree_holder_, symbol_locator_, this_context.get_parent(), access,  this_context.bind2proxy() ); 
                    access = default_access_spec;
                }
            ) 
            ((  COMMA 
                (
                    ( access = aggregate_inheretance_access_sepcifiers )? 
                    id = fq_id
                    { 
                        create_inheretance_info(this_aggregate, id, semantic_tree_holder_, symbol_locator_, this_context.get_parent(), access, this_context.bind2proxy() ); 
                        access = default_access_spec;
                    }
                )  
            )*)
        ;        

aggregate_inheretance_access_sepcifiers returns [gie::ccom::guid_t access]
        : access = aggregate_access_specifiers
        ;
        
aggregate_access_specifiers returns [gie::ccom::guid_t access_type]
            {GIE_IDL_GRAMMAR_TRACE_FUNC;}
        :   ( 
                 KW_PRIVATE        {access_type = gie_idl::access_private;}
                |KW_PUBLIC         {access_type = gie_idl::access_public;}
                |KW_PROTECTED      {access_type = gie_idl::access_protected;}
            )      
        ;
        
aggregate_type_info  returns [gie::ccom::guid_t aggregate_type]
            {GIE_IDL_GRAMMAR_TRACE_FUNC;}
        :   ( KW_INTERFACE  {aggregate_type = gie_idl::aggregate_interface;} 
             |KW_STRUCT     {aggregate_type = gie_idl::aggregate_struct;}
             |KW_CLASS      {aggregate_type = gie_idl::aggregate_class;}
             )
        ;        
        
//aggregate access block proxy wrappers
aggregate_definition_body_item_w_access_definition [const context_t& this_context]
        {
            GIE_IDL_GRAMMAR_TRACE_FUNC;
            if( this_context.get_attr_repo().get() ) //attr repo should be null
            {
                GIE_LIB_NOT_IMPLEMENTED;
            }
            gie::ccom::guid_t access_spec;
            gie_idl::attribute_repository_ptr_t attr_repo;
        }
        :   (access_spec = aggregate_access_specifiers)
            COLON 
            (
                {   //for each member create new attribute storage
                    attr_repo = gie_idl::create_attribute_repository();
                    gie_idl::set_access_attribute(attr_repo, access_spec);
                }
                aggregate_definition_body_item[ context_t(this_context.get_parent(), attr_repo) ]
            )*
        ;

aggregate_definition_body_item_definition [const context_t& this_context, const gie::ccom::guid_t& access_spec] 
        {
            GIE_IDL_GRAMMAR_TRACE_FUNC;
            
            gie_idl::attribute_repository_ptr_t attr_repo;
        }
        :   {
                attr_repo = gie_idl::create_attribute_repository( this_context.get_attr_repo().get() );
                gie_idl::set_access_attribute(attr_repo, access_spec);
            }
            aggregate_definition_body_item[ context_t(this_context.get_parent(), attr_repo) ]
        ;        

//aggregate items
aggregate_definition_body_item [const context_t& this_context]
        :   (aggregate_member_function_defination[this_context]) => aggregate_member_function_defination[this_context] SEMI
        |   aggregate_member_variable_defination[this_context] SEMI
        |   aggregate_definition[this_context]
        ;    


aggregate_member_variable_defination [const context_t& this_context]
        {
            gie_idl::node_i_ptr_t node;
        }
        :   node = simple_variable_definition[this_context]
            {
                const gie_idl::named_collection_i_ptr_t& parent_node = gie::ccom::query_interface_<gie_idl::named_collection_i>( this_context.get_parent(), gie::ccom::throw_on_fail() );
                if(this_context.get_attr_repo())
                    gie_idl::set_attribute_repository(node, this_context.get_attr_repo() );
                const gie_idl::insert_child_result_t& r = parent_node->insert_child(node.get() );
                if( r.get<1>() ) // 0 - node, 1 - inserted or not
                {
                    //inserted ok
                }
                else
                {
                    GIE_LIB_NOT_IMPLEMENTED_1("Failed to insert variable");
                }
            }
        ;
        
aggregate_member_function_defination[const context_t& this_context]
        {
            gie_idl::node_i_ptr_t node;
        }
        :  node = function_prototype_declaration[this_context]
           {
                gie_idl::grammar::insert_new_function_decl( this_context.get_parent(), node, this_context.get_attr_repo() );
           }
        
        ;        

//================================================================================================================================================
// function/member function
//================================================================================================================================================
function_prototype_declaration[const context_t& this_context] returns [gie_idl::node_i_ptr_t node]
        {
            gie_idl::function_parameters_builder_ptr_t function_parameters_builder;
            gie_idl::function_ptr_t  function_node;
            gie_idl::node_i_ptr_t tmp_node;
            gie_idl::node_i_ptr_t ret_type;
        }
        : ( ret_type = type_defination[this_context]
            id:IDENTIFIER
            {
                const gie_idl::function_parameters_ptr_t& function_parameters = gie_idl::create_function_parameters();
                function_parameters_builder = ::gie::ccom::query_interface_<gie_idl::function_parameters_builder_i>( function_parameters, ::gie::ccom::throw_on_fail() );
                function_parameters_builder->set_return_type( ret_type );
                
                function_node = gie_idl::create_function_node( id->getText() );
                node = function_node;
            }
            LPAREN
            ( ( tmp_node = function_prototype_parameter[this_context]){ function_parameters_builder->push_back(tmp_node); } )? 
            ( (COMMA tmp_node = function_prototype_parameter[this_context]){ function_parameters_builder->push_back(tmp_node); }  )*
            RPAREN
          )
          {
            gie_idl::grammar::add_new_function_parameters(function_node, function_parameters_builder);
          }
        ;  
        
function_prototype_parameter[const context_t& this_context] returns [gie_idl::node_i_ptr_t node]
        : (attributes)? node = simple_variable_definition[this_context]
        ;
            
//================================================================================================================================================
// variable, parameters, etc.
//================================================================================================================================================
simple_variable_definition[const context_t& this_context] returns [gie_idl::node_i_ptr_t node]
        {
            gie_idl::node_i_ptr_t type_descriptor;
        }
        :   ( 
                type_descriptor = type_defination[this_context] 
                id:IDENTIFIER 
                {
                    node = create_var_decl_node( id->getText(), type_descriptor);
                }
            )  
        ;

//================================================================================================================================================
// attributes
//================================================================================================================================================
attributes
    :   LBRACK
            (attribute )?
            (COMMA attribute)*
        RBRACK
    ;
    
attribute
    :   (
            id:IDENTIFIER 
            (LPAREN attribute_value RPAREN)?
        )
    ;    
    
attribute_value
    :   str:STRING
    |   strGuid:attribute_guid
    ;
    
attribute_guid
    : MSGUID
    ;     
        
        
//================================================================================================================================================
// type defination
//================================================================================================================================================
type_defination[const context_t& this_context] returns [gie_idl::node_i_ptr_t node]
        {
            gie_idl::node_i_ptr_t current_sub_type;
            gie_idl::node_i_ptr_t tmp_node;
        }
        :   (
                current_sub_type = type_defination_symbol[this_context]
                (
                    current_sub_type = type_defination_ptr_block[current_sub_type]
                )? 
                (
                    AND
                    {
                        const gie_idl::reference_to_ptr_t& ref_to = gie_idl::create_reference_to();
                        const gie_idl::type_descriptor_builder_ptr_t& type_builder = ::gie::ccom::query_interface_<gie_idl::type_descriptor_builder_i>( ref_to, ::gie::ccom::throw_on_fail() );
                        type_builder->set_next_sub_type( current_sub_type.get() );
                        current_sub_type = ::gie::ccom::query_interface_<gie_idl::node_i>( ref_to, ::gie::ccom::throw_on_fail() );
                    }
                )?
            )
            {
                node = create_type_descriptor( current_sub_type );                
            }
        ;
        
type_defination_symbol[const context_t& this_context] returns [gie_idl::node_i_ptr_t node]
        {
            gie_idl::type_descriptor_builder_ptr_t        base_type;
            gie_idl::fq_id_ptr_t            base_type_symbol;
            bool do_enable_const=false;
        }
        : ( 
            (KW_CONST { do_enable_const=true; } )? 
            base_type_symbol = fq_id 
            {
                base_type = gie_idl::create_base_type(node, this_context.get_parent(), base_type_symbol, semantic_tree_holder_, symbol_locator_);
            }
            (KW_CONST { if(!do_enable_const) do_enable_const=true;} )? 
          )
          {
            if(do_enable_const){ base_type->enable_mod(gie_idl::tim_const); } 
          }
        ;

type_defination_ptr_block[const gie_idl::node_i_ptr_t& target_type] returns [gie_idl::node_i_ptr_t node]
        {
            node = target_type;
        }
        :   (
                (   
                    node = type_defination_ptr[node]
                )+
            )
        ;
        

type_defination_ptr[const gie_idl::node_i_ptr_t& target_type] returns [gie_idl::node_i_ptr_t node]
        {
            gie_idl::type_descriptor_builder_ptr_t type_builder;
        }
        :   STAR
            {
                const gie_idl::pointer_to_ptr_t& pointer_to = gie_idl::create_pointer_to();
                type_builder = ::gie::ccom::query_interface_<gie_idl::type_descriptor_builder_i>( pointer_to, ::gie::ccom::throw_on_fail() );
                type_builder->set_next_sub_type( target_type.get() );
                node = ::gie::ccom::query_interface_<gie_idl::node_i>( pointer_to, ::gie::ccom::throw_on_fail() );
            }
            (KW_CONST{type_builder->enable_mod(gie_idl::tim_const);})?
        ;


fq_id   returns [gie_idl::fq_id_ptr_t fq_id]
        : {fq_id = gie_idl::create_fq_id(); fq_id->push_back(wxT("")); } 
          (DCOLON id1:IDENTIFIER {fq_id->push_back( id1->getText() );} )+
        | { fq_id = gie_idl::create_fq_id();} 
          id2:IDENTIFIER {fq_id->push_back( id2->getText() );}
          (DCOLON id3:IDENTIFIER {fq_id->push_back( id3->getText() );} )*
        ;                
//================================================================================================================================================
// end of type defination
//================================================================================================================================================
                
                          

