///////////////////////////////////////////////////////////////////////////////
// Name:        GIEIDL
// Author:      GIE
// Modified by:
// Created:     10.08.2004
// Copyright:   (c) GIE
// Version:     
///////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
#include "stdafx.h"
//---------------------------------------------------------------------------
#include "idl_param/param.validator.h"

#include "idl_backend/idl_backend.manager.h"
#include "idl_compil/idl_compil.h"
#include "gielib/debug/trace.cpp_inline.h"
#include "idl_compil/semantic.helpers.node_type2string.h"
#include "idl_compil/semantic.helpers.id2string.h"
#include "idl_compil/utility.bool2string.h"
#include "idl_compil/semantic.helpers.get_node_path_as_string.h"


#include "antlr/ANTLRException.hpp"
//---------------------------------------------------------------------------
extern void test();
//---------------------------------------------------------------------------
struct progress_t
    : gie_idl::compil_t::notify_i
{
    typedef gie_idl::compil_t::notify_i super_t;

    progress_t(std::ostream& log)
        : log_( log )
    {}

    bool before_building_ast() 
    { 
        log_ << wxT("Building AST...\n");
        return true; 
    };

    bool before_building_semantic_tree()
    {
        log_ << wxT("Building Semantic Tree...\n");
        return true; 
    }

    const bool2_t before_process_unbound_symbols(const unsigned int iteration)
    {
        total_unbound_ = 0;

        log_<<wxT("\nUnbound symbols (iteration ")<<iteration<<wxT(") : \n");
        log_<<wxT("-------------");
        return super_t::before_process_unbound_symbols(iteration);
    }
    bool after_process_unbound_symbols()
    { 
        log_<<wxT("-------------\n");
        log_<<wxT("Total unbound symbols: ")<<total_unbound_<<wxT("\n");
        return true; 
    }

    bool process_unbound_symbols(gie_idl::late_bound_i* const late_bound)
    { 
        ++total_unbound_;

        log_<<wxT("\n");
        log_<<wxT("referring to: ")<<map_id2string( late_bound->get_id() )<<wxT('\n');
        //log_<<wxT("type: ")<<gie_idl::map_node_type2string( late_bound->get_latebound_type() )<<wxT('\n');
        log_<<wxT("is bound?: ")<<gie::bool2string__yes_no( late_bound->is_boud() )<<wxT('\n');
        log_<<wxT("start lookup from: ")<<gie_idl::get_node_path_as_string( late_bound->get_lookup_parent() )<<wxT('\n');

        return true; 
    }

    bool before_backend()
    {
        log_<<wxT("Invoking back end generator...\n");
        return true; 
    }

    void done()
    { 
        log_ << wxT("Done\n");
    }

private:
    std::ostream& log_;
    unsigned int  total_unbound_;
};


//---------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
    bool wait_for_return = false;
    //init leak test
#ifdef GIE_LIB_DEBUG
   _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_DELAY_FREE_MEM_DF);
    //_CrtSetBreakAlloc(96);
#endif

    GIE_LIB_DEBUG_WARN("executing...");

    try 
    {
        gie_idl::backends_manager_t manager;
        const gie_idl::options_ptr_t& params = gie_idl::process_cmd_params(argv, argc, manager, GIE_LIB_CLOG);
        if( params )
        {
            if( params->count(wxT("waitforreturn")) )
                wait_for_return = true;

            test();

            gie_idl::backend::backend_interface_ptr_t back_end = manager.create_back_end( (*params)[wxT("backend")].as<std::string>() );

            progress_t progress_indicator(std::clog);
            std::ifstream ifs( (*params)[wxT("input-file")].as<std::string>().c_str() ); 
            if( !ifs )
            {
                GIE_LIB_NOT_IMPLEMENTED_1("failed to open input-file");
            }
            gie_idl::compil_t idl_compil(ifs, back_end, params, &progress_indicator);
            idl_compil.compile();
        }
        
    }
    catch(const std::exception& e) 
    {
        std::cerr << "exception: " << e.what() << std::endl;
    }
    catch(const antlr::ANTLRException& e)
    {
        std::cerr << "ANTLRException: " << e.toString() << std::endl;
    }

    #ifdef GIE_LIB_DEBUG
        _CrtMemState mem_state;
        _CrtMemCheckpoint( &mem_state );
        GIE_LIB_CLOG << wxT("\n[DEBUG] Max allocated mem: ")<< static_cast<unsigned int>( mem_state.lHighWaterCount )<<wxT('\n');
    #endif

    if( wait_for_return )
    {
        GIE_LIB_CLOG << wxT("\nPress any key\n");
        getchar();
    }

    return 0;
}
//---------------------------------------------------------------------------


