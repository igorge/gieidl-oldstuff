//================================================================================================================================================
//
// (c) GIE 04.03.2005
//
//================================================================================================================================================
#ifndef H_GUARD_PARSER_HELPER_H__04_03_2005__6_07_54
#define H_GUARD_PARSER_HELPER_H__04_03_2005__6_07_54
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#include "../idl_compil/semantic.nodes.fq_id.h"
#include "../idl_compil/semantic.nodes.h"
#include "../idl_compil/semantic.attributes.h"
#include "../idl_compil/semantic.helpers.h"

#include "../idl_compil/type_info/semantic.type_info.factory.h"
#include "../idl_compil/semantic.nodes.function/semantic.nodes.fucntion.factory.h"
#include "../idl_compil/symbol_locators/symloc.interfaces.h"
//================================================================================================================================================
namespace gie_idl { namespace grammar {

    struct context_info_t
    {
        context_info_t(const node_i_ptr_t& parent)
            : parent_( parent )
            , bind_to_proxies_( false )
        {}
        
        context_info_t(const node_i_ptr_t& parent, const attribute_repository_ptr_t& attr_repo)
            : parent_( parent )
            , attr_repo_( attr_repo )
            , bind_to_proxies_( false )
        {}

        const node_i_ptr_t& get_parent()const throw(){ return parent_; }
        const attribute_repository_ptr_t& get_attr_repo()const throw(){ return attr_repo_; }
        const bool bind2proxy()const throw(){ return bind_to_proxies_;}
    private:

        node_i_ptr_t parent_;
        attribute_repository_ptr_t attr_repo_;
        bool         bind_to_proxies_;
    };

} }
//================================================================================================================================================
//inline
//gie_idl::line_information_auto_ptr_t li_from_node(antlr::RefToken& token)
//{
//    
//
//    GIE_LIB_ASSERTE( typeid(gie_idl::extended_token_t)==typeid( *token.get() ) );
//    gie_idl::extended_token_t& extended_token = * static_cast<gie_idl::extended_token_t*>( token.get() );
//
//    return gie_idl::line_information_auto_ptr_t ( new gie_idl::line_information_t(extended_token.get_file_name(), extended_token.getLine(), extended_token.getColumn() ) );
//}
//
//inline 
//void set_li(gie::gie_idl::ast::nodes::node_t& node, antlr::RefToken& token)
//{
//    node.set_line_information( li_from_node(token) );
//}

//================================================================================================================================================
#endif//H_GUARD_PARSER_HELPER_H__04_03_2005__6_07_54
//================================================================================================================================================
