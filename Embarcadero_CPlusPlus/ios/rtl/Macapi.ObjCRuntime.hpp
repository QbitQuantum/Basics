// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.ObjCRuntime.pas' rev: 34.00 (iOS)

#ifndef Macapi_ObjcruntimeHPP
#define Macapi_ObjcruntimeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.StdDef.hpp>

//-- user supplied -----------------------------------------------------------

namespace Macapi
{
namespace Objcruntime
{
//-- forward type declarations -----------------------------------------------
struct obj_super;
//-- type declarations -------------------------------------------------------
typedef void * SEL;

#pragma pack(push,1)
struct DECLSPEC_DRECORD obj_super
{
public:
	void *receiver;
	void *cls;
};
#pragma pack(pop)


typedef obj_super *Pobj_super;

typedef void * id;

//-- var, const, procedure ---------------------------------------------------
#define libobjc u"/usr/lib/libobjc.dylib"
extern DELPHI_PACKAGE int YES;
extern DELPHI_PACKAGE int NO;
extern "C" void * __cdecl objc_getClass(const char * name);
extern "C" int __cdecl objc_getClassList(void * buffer, int bufferLen);
extern "C" void * __cdecl objc_allocateClassPair(void * superclass, char * name, unsigned long ExtraBytes);
extern "C" void __cdecl objc_registerClassPair(void * Cls);
extern "C" void __cdecl objc_disposeClassPair(void * cls);
extern "C" int __cdecl objc_addClass(void * Cls);
extern "C" void * __cdecl objc_msgSend(void * theReceiver, void * theSelector)/* overload */;
extern "C" void * __cdecl objc_msgSendP(void * theReceiver, void * theSelector, void * P1)/* overload */;
extern "C" void * __cdecl objc_msgSendP2(void * theReceiver, void * theSelector, void * P1, void * P2)/* overload */;
extern "C" void * __cdecl imp_implementationWithBlock(void * block);
extern "C" int __cdecl imp_removeBlock(void * anImp);
extern "C" void * __cdecl objc_msgSendSuper(Pobj_super theReceiver, void * theSelector)/* overload */;
extern "C" void * __cdecl objc_msgSendSuperP(Pobj_super theReceiver, void * theSelector, void * P1)/* overload */;
extern "C" void * __cdecl objc_msgSendSuperP2(Pobj_super theReceiver, void * theSelector, void * P1, void * P2)/* overload */;
extern "C" void * __cdecl objc_getProtocol(const char * name);
extern "C" void * __cdecl sel_getUid(const char * str);
extern "C" void * __cdecl sel_registerName(const char * str);
extern "C" char * __cdecl sel_getName(void * Selector);
extern "C" void * __cdecl class_copyMethodList(void * Cls, int &OutCount);
extern "C" int __cdecl class_addMethod(void * Cls, void * theSelector, void * Impl, char * types);
extern "C" int __cdecl class_addIvar(void * Cls, char * name, int Size, System::Byte alignment, char * types);
extern "C" int __cdecl class_addProtocol(void * Cls, void * protocol);
extern "C" void * __cdecl class_getInstanceMethod(void * Cls, void * Selector);
extern "C" void * __cdecl class_getClassMethod(void * Cls, void * Selector);
extern "C" char * __cdecl class_getName(void * Cls);
extern "C" void * __cdecl object_getInstanceVariable(void * obj, char * name, /* out */ void * &value);
extern "C" void * __cdecl object_getClass(void * obj);
extern "C" void * __cdecl object_setInstanceVariable(void * obj, char * name, void * value);
extern "C" char * __cdecl method_getTypeEncoding(void * Method);
extern "C" void * __cdecl method_getImplementation(void * Method);
extern "C" void * __cdecl method_setImplementation(void * Method, void * Imp);
extern "C" void __cdecl method_exchangeImplementations(void * Method1, void * Method2);
}	/* namespace Objcruntime */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_OBJCRUNTIME)
using namespace Macapi::Objcruntime;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_ObjcruntimeHPP
