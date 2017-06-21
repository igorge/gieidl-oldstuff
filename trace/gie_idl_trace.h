//================================================================================================================================================
//
// (c) GIE 08.04.2005
//
//================================================================================================================================================
#ifndef H_GUARD_GIE_IDL_TRACE_H__08_04_2005__20_56_46
#define H_GUARD_GIE_IDL_TRACE_H__08_04_2005__20_56_46
//================================================================================================================================================
#pragma once
//================================================================================================================================================
#ifdef GIE_IDL_DO_TRACE_ST
    #define GIE_IDL_ST_TRACE_FUNC GIE_LIB_TRACE_FUNC
    #define GIE_IDL_ST_TRACE_VAL(v)  GIE_LIB_TRACE_VALUE(v)
    #define GIE_IDL_ST_TRACE_VAL_EX(v,m)  GIE_LIB_TRACE_VALUE_EX(v,m)
#else
    #define GIE_IDL_ST_TRACE_FUNC
    #define GIE_IDL_ST_TRACE_VAL(v)
    #define GIE_IDL_ST_TRACE_VAL_EX(v,m)
#endif

#ifdef GIE_IDL_DO_TRACE_COMPILER
    #define GIE_IDL_COMPILER_TRACE_FUNC GIE_LIB_TRACE_FUNC
#else
    #define GIE_IDL_COMPILER_TRACE_FUNC
#endif

#ifdef GIE_IDL_DO_TRACE_GRAMMAR
    #define GIE_IDL_GRAMMAR_TRACE_FUNC GIE_LIB_TRACE_FUNC
#else
    #define GIE_IDL_GRAMMAR_TRACE_FUNC
#endif
//================================================================================================================================================
#endif//H_GUARD_GIE_IDL_TRACE_H__08_04_2005__20_56_46
//================================================================================================================================================
