// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.VCLCom.pas' rev: 34.00 (Windows)

#ifndef System_Win_VclcomHPP
#define System_Win_VclcomHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.Win.ComObj.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Win
{
namespace Vclcom
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TComponentFactory;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TComponentFactory : public System::Win::Comobj::TAutoObjectFactory
{
	typedef System::Win::Comobj::TAutoObjectFactory inherited;
	
protected:
	HIDESBASE HRESULT __stdcall CreateInstance(const System::_di_IInterface UnkOuter, const GUID &IID, /* out */ void *Obj);
	
public:
	__fastcall TComponentFactory(System::Win::Comobj::TComServerObject* ComServer, System::Classes::TComponentClass ComponentClass, const GUID &ClassID, System::Win::Comobj::TClassInstancing Instancing, System::Win::Comobj::TThreadingModel ThreadingModel);
	virtual System::Win::Comobj::TComObject* __fastcall CreateComObject(const System::_di_IInterface Controller);
	virtual void __fastcall UpdateRegistry(bool Register);
public:
	/* TComObjectFactory.Destroy */ inline __fastcall virtual ~TComponentFactory() { }
	
private:
	void *__IClassFactory;	// IClassFactory 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000001-0000-0000-C000-000000000046}
	operator _di_IClassFactory()
	{
		_di_IClassFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IClassFactory*(void) { return (IClassFactory*)&__IClassFactory; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Vclcom */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_VCLCOM)
using namespace System::Win::Vclcom;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN)
using namespace System::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Win_VclcomHPP
