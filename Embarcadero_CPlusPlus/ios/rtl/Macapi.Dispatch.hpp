// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.Dispatch.pas' rev: 34.00 (iOS)

#ifndef Macapi_DispatchHPP
#define Macapi_DispatchHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Macapi
{
namespace Dispatch
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef NativeInt dispatch_object_t;

typedef NativeInt dispatch_queue_t;

typedef void * dispatch_block_t;

typedef void __cdecl (*dispatch_function_t)(void * context);

//-- var, const, procedure ---------------------------------------------------
#define libSystem u"/usr/lib/libSystem.dylib"
#define libdispatch u"/usr/lib/system/libdispatch.dylib"
#define DISPATCH_QUEUE_SERIAL (void*)(0)
extern "C" NativeInt __cdecl dispatch_queue_create(char * QueueLabel, NativeInt attr);
extern "C" void __cdecl dispatch_release(NativeInt obj);
extern "C" void __cdecl dispatch_async_f(NativeInt queue, void * context, dispatch_function_t work);
}	/* namespace Dispatch */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_DISPATCH)
using namespace Macapi::Dispatch;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_DispatchHPP
