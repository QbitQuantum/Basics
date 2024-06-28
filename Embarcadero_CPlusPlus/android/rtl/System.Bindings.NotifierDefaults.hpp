// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.NotifierDefaults.pas' rev: 34.00 (Android)

#ifndef System_Bindings_NotifierdefaultsHPP
#define System_Bindings_NotifierdefaultsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.Consts.hpp>
#include <System.Bindings.NotifierContracts.hpp>
#include <System.Bindings.Manager.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Notifierdefaults
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindingNotifier;
class DELPHICLASS TBindingNotification;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBindingNotifier : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::TObject* FOwner;
	System::Bindings::Manager::TBindingManager* FManager;
	System::Bindings::Notifiercontracts::TBindingNotifReservedType FReserved;
	
protected:
	System::TObject* __fastcall GetOwner();
	System::Bindings::Manager::TBindingManager* __fastcall GetManager();
	System::Bindings::Notifiercontracts::TBindingNotifReservedType __fastcall GetReserved();
	void __fastcall SetReserved(System::Bindings::Notifiercontracts::TBindingNotifReservedType Value);
	void __fastcall SetOwner(System::TObject* Value);
	virtual void __fastcall Notify(const System::UnicodeString PropertyName);
	
public:
	__fastcall TBindingNotifier(System::TObject* Owner, System::Bindings::Manager::TBindingManager* Manager);
	__property System::TObject* Owner = {read=GetOwner, write=SetOwner};
	__property System::Bindings::Manager::TBindingManager* Manager = {read=GetManager};
	__property System::Bindings::Notifiercontracts::TBindingNotifReservedType Reserved = {read=GetReserved, write=SetReserved, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindingNotifier() { }
	
private:
	void *__IBindingNotifier;	// System::Bindings::Notifiercontracts::IBindingNotifier 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {767FC59A-C8D9-4810-9A9E-B7648706F0B6}
	operator System::Bindings::Notifiercontracts::_di_IBindingNotifier()
	{
		System::Bindings::Notifiercontracts::_di_IBindingNotifier intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Notifiercontracts::IBindingNotifier*(void) { return (System::Bindings::Notifiercontracts::IBindingNotifier*)&__IBindingNotifier; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBindingNotification : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::TObject* FOwner;
	
protected:
	virtual void __fastcall Notification(System::Bindings::Notifiercontracts::_di_IBindingNotifier Notifier, const System::UnicodeString PropertyName) = 0 ;
	__property System::TObject* Owner = {read=FOwner};
	
public:
	__fastcall TBindingNotification(System::TObject* Owner);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindingNotification() { }
	
private:
	void *__IBindingNotification;	// System::Bindings::Notifiercontracts::IBindingNotification 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {83360F64-6260-4029-96B3-070FB253F075}
	operator System::Bindings::Notifiercontracts::_di_IBindingNotification()
	{
		System::Bindings::Notifiercontracts::_di_IBindingNotification intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Notifiercontracts::IBindingNotification*(void) { return (System::Bindings::Notifiercontracts::IBindingNotification*)&__IBindingNotification; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Notifierdefaults */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_NOTIFIERDEFAULTS)
using namespace System::Bindings::Notifierdefaults;
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
#endif	// System_Bindings_NotifierdefaultsHPP
