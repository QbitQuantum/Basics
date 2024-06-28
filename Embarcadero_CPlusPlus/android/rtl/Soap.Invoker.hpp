// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.Invoker.pas' rev: 34.00 (Android)

#ifndef Soap_InvokerHPP
#define Soap_InvokerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Soap.IntfInfo.hpp>
#include <Soap.InvokeRegistry.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Invoker
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TInterfaceInvoker;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TInterfaceInvoker : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	void __fastcall Invoke(System::TObject* const Obj, const Soap::Intfinfo::TIntfMetaData &IntfMD, const int MethNum, Soap::Invokeregistry::TInvContext* const Context);
public:
	/* TObject.Create */ inline __fastcall TInterfaceInvoker() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInterfaceInvoker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Invoker */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_INVOKER)
using namespace Soap::Invoker;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_InvokerHPP
