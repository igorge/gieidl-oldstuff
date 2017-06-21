//================================================================================================================================================
//
// (c) GIE 08.05.2005
//
//================================================================================================================================================
// NAME: param.core.cpp
//================================================================================================================================================
#include "stdafx.h"
//================================================================================================================================================
#include "param.validator.h"

#include "boost/program_options.hpp"
//================================================================================================================================================
namespace gie_idl {
    const options_ptr_t process_cmd_params(char_t* params[],const unsigned int count, const backends_manager_t& manager, ::std::basic_ostream<char_t>& err_msg)
    {
        using namespace boost::program_options;

        options_description common( wxT("Generic") );
        options_ptr_t       vm_ = new options_t();

        common.add_options()
            ( wxT("help"), wxT("produce help message") )
            ( wxT("backend"),  value<std::string>(), wxT("select backend") )
            ( wxT("input-file"), value<std::string>(), wxT("input file") )
            ( wxT("waitforreturn"), wxT("wait for return before termination") )
            ;

        options_description cmd_line_options;
        cmd_line_options.add(common);
        
        backends_manager_t::const_iterator& current_back_end = manager.begin();
        const backends_manager_t::const_iterator& end = manager.end();

        while( current_back_end!=end )
        {
            options_description this_back_end_desc( current_back_end->second->internal_name );
            current_back_end->second->get_options_description( this_back_end_desc );
            cmd_line_options.add(this_back_end_desc);

            ++current_back_end;
        }

        store(parse_command_line(count, params, cmd_line_options), *vm_);
        notify( *vm_ );  

        if( !(vm_->count( wxT("backend") ) &&  vm_->count( wxT("input-file") )) || vm_->count( wxT("help") ) )
        {
            err_msg << cmd_line_options << wxT('\n');
            return NULL;
        }

        if( !manager.is_valid_backend_name( (*vm_)[ wxT("backend") ].as<std::string>() ))
        {
            GIE_LIB_NOT_IMPLEMENTED_1("unknown back end");
        }

        return vm_;
    }

}
//================================================================================================================================================
