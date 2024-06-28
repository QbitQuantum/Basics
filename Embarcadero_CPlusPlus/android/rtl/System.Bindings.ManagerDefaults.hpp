// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.ManagerDefaults.pas' rev: 34.00 (Android)

#ifndef System_Bindings_ManagerdefaultsHPP
#define System_Bindings_ManagerdefaultsHPP

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
#include <System.Bindings.EvalProtocol.hpp>
#include <System.Bindings.NotifierContracts.hpp>
#include <System.Bindings.Manager.hpp>
#include <System.Bindings.Factories.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Managerdefaults
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindingManagerDefault;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBindingManagerDefault : public System::Bindings::Manager::TBindingManager
{
	typedef System::Bindings::Manager::TBindingManager inherited;
	
private:
	System::Bindings::Notifiercontracts::_di_IBindingNotification FNotifHandler;
	
protected:
	__property System::Bindings::Notifiercontracts::_di_IBindingNotification NotifHandler = {read=FNotifHandler};
	
public:
	__fastcall TBindingManagerDefault(System::Bindings::Manager::TBindingManager* Owner);
	__fastcall virtual ~TBindingManagerDefault();
private:
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {83360F64-6260-4029-96B3-070FB253F075}
	operator System::Bindings::Notifiercontracts::_di_IBindingNotification() { return NotifHandler; }
	#else
	operator System::Bindings::Notifiercontracts::IBindingNotification*(void) { return (System::Bindings::Notifiercontracts::IBindingNotification*)NotifHandler; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Managerdefaults */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_MANAGERDEFAULTS)
using namespace System::Bindings::Managerdefaults;
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
#endif	// System_Bindings_ManagerdefaultsHPP
