// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


// Windows Header Files:
#include <windows.h>
#include <crtdbg.h>

#include <string>
#include <iostream>
#include <fstream>
#include <tchar.h>
// TODO: reference additional headers your program requires here

//#define GIE_LIB_DO_TRACE    //turn on tracing facility

#define GIE_IDL_DO_TRACE_ST //turn on tracing of semantic nodes
#define GIE_IDL_DO_TRACE_COMPILER //turn on tracing of compiler facade
#define GIE_IDL_DO_TRACE_GRAMMAR //trace antlr generated grammar

#include "trace/gie_idl_trace.h"

#include "gielib/compil_config.h"
#include "gielib/debug/trace.h"
#include "gielib/debug/debug.h"

typedef ::gie::string_t string_t;
typedef ::gie::char_t   char_t;

#ifdef GIE_LIB_DEBUG 

#include "boost/mpl/list.hpp"
#include "boost/mpl/list_c.hpp"

#include <list>
#include <map>
#include <vector>

#endif
