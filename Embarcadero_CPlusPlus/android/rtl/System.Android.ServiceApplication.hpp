// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Android.ServiceApplication.pas' rev: 34.00 (Android)

#ifndef System_Android_ServiceapplicationHPP
#define System_Android_ServiceapplicationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Android
{
namespace Serviceapplication
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TServiceApplication;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TServiceApplication : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	// __classmethod void __fastcall Create_();
	
private:
	void __fastcall OnExceptionHandler(System::TObject* Sender);
	
protected:
	DYNAMIC void __fastcall DoHandleException(System::Sysutils::Exception* E);
	
public:
	__fastcall virtual TServiceApplication(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TServiceApplication();
	virtual void __fastcall CreateForm(System::Classes::TComponentClass InstanceClass, void *Reference);
	virtual void __fastcall Initialize();
	virtual void __fastcall Run();
	
private:
	// __classmethod void __fastcall Destroy_();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TServiceApplication* Application;
}	/* namespace Serviceapplication */
}	/* namespace Android */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANDROID_SERVICEAPPLICATION)
using namespace System::Android::Serviceapplication;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANDROID)
using namespace System::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Android_ServiceapplicationHPP
