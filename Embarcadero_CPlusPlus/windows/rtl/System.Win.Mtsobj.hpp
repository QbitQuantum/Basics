// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.Mtsobj.pas' rev: 34.00 (Windows)

#ifndef System_Win_MtsobjHPP
#define System_Win_MtsobjHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Win.ComObj.hpp>
#include <Winapi.Mtx.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Win
{
namespace Mtsobj
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMtsAutoObject;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMtsAutoObject : public System::Win::Comobj::TAutoObject
{
	typedef System::Win::Comobj::TAutoObject inherited;
	
private:
	_di_IObjectContext FObjectContext;
	bool FCanBePooled;
	
protected:
	HRESULT __safecall Activate();
	void __stdcall Deactivate();
	virtual System::LongBool __stdcall CanBePooled();
	virtual void __fastcall OnActivate();
	virtual void __fastcall OnDeactivate();
	__property _di_IObjectContext ObjectContext = {read=FObjectContext};
	
public:
	void __fastcall SetComplete();
	void __fastcall SetAbort();
	void __fastcall EnableCommit();
	void __fastcall DisableCommit();
	System::LongBool __fastcall IsInTransaction();
	System::LongBool __fastcall IsSecurityEnabled();
	System::LongBool __fastcall IsCallerInRole(const System::WideString Role);
	__property bool Pooled = {read=FCanBePooled, write=FCanBePooled, nodefault};
public:
	/* TAutoObject.Create */ inline __fastcall TMtsAutoObject() : System::Win::Comobj::TAutoObject() { }
	/* TAutoObject.CreateAggregated */ inline __fastcall TMtsAutoObject(const System::_di_IInterface Controller) : System::Win::Comobj::TAutoObject(Controller) { }
	/* TAutoObject.CreateFromFactory */ inline __fastcall TMtsAutoObject(System::Win::Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller) : System::Win::Comobj::TAutoObject(Factory, Controller) { }
	
public:
	/* TComObject.Destroy */ inline __fastcall virtual ~TMtsAutoObject() { }
	
private:
	void *__IObjectControl;	// IObjectControl 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {51372AEC-CAE7-11CF-BE81-00AA00A2FA25}
	operator _di_IObjectControl()
	{
		_di_IObjectControl intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IObjectControl*(void) { return (IObjectControl*)&__IObjectControl; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mtsobj */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_MTSOBJ)
using namespace System::Win::Mtsobj;
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
#endif	// System_Win_MtsobjHPP
