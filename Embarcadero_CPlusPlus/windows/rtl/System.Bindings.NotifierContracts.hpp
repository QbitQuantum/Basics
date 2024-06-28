// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.NotifierContracts.pas' rev: 34.00 (Windows)

#ifndef System_Bindings_NotifiercontractsHPP
#define System_Bindings_NotifiercontractsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.Manager.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Notifiercontracts
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EBindingNotifyError;
__interface DELPHIINTERFACE IBindingNotification;
typedef System::DelphiInterface<IBindingNotification> _di_IBindingNotification;
__interface DELPHIINTERFACE IBindingNotifier;
typedef System::DelphiInterface<IBindingNotifier> _di_IBindingNotifier;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBindingNotifyError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBindingNotifyError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBindingNotifyError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBindingNotifyError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBindingNotifyError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindingNotifyError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindingNotifyError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBindingNotifyError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBindingNotifyError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindingNotifyError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindingNotifyError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindingNotifyError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindingNotifyError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBindingNotifyError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TBindingNotifReservedType : unsigned char { bnrtExternal, bnrtInternal };

__interface  INTERFACE_UUID("{83360F64-6260-4029-96B3-070FB253F075}") IBindingNotification  : public System::IInterface 
{
	virtual void __fastcall Notification(_di_IBindingNotifier Notifier, const System::UnicodeString PropertyName) = 0 ;
};

__interface  INTERFACE_UUID("{767FC59A-C8D9-4810-9A9E-B7648706F0B6}") IBindingNotifier  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetOwner() = 0 ;
	virtual System::Bindings::Manager::TBindingManager* __fastcall GetManager() = 0 ;
	virtual TBindingNotifReservedType __fastcall GetReserved() = 0 ;
	virtual void __fastcall SetReserved(TBindingNotifReservedType Value) = 0 ;
	virtual void __fastcall SetOwner(System::TObject* Value) = 0 ;
	virtual void __fastcall Notify(const System::UnicodeString PropertyName) = 0 ;
	__property System::TObject* Owner = {read=GetOwner, write=SetOwner};
	__property System::Bindings::Manager::TBindingManager* Manager = {read=GetManager};
	__property TBindingNotifReservedType Reserved = {read=GetReserved, write=SetReserved};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Notifiercontracts */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_NOTIFIERCONTRACTS)
using namespace System::Bindings::Notifiercontracts;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS)
using namespace System::Bindings;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Bindings_NotifiercontractsHPP
