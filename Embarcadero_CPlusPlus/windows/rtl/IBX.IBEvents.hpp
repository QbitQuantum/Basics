// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBEvents.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbeventsHPP
#define Ibx_IbeventsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IBExternals.hpp>
#include <IBX.IB.hpp>
#include <IBX.IBDatabase.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibevents
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBEvents;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TEventAlert)(System::TObject* Sender, System::UnicodeString EventName, int EventCount, bool &CancelAlerts);

typedef void __fastcall (__closure *TErrorEvent)(System::TObject* Sender, int ErrorCode);

#ifndef _WIN64
typedef System::Generics::Collections::TList__1<System::DynamicArray<System::Byte> >* TEventStrings;
#else /* _WIN64 */
typedef System::Generics::Collections::TList__1<System::TArray__1<System::Byte> >* TEventStrings;
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TIBEvents : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
#ifndef _WIN64
	System::Generics::Collections::TList__1<System::DynamicArray<System::Byte> >* FEvents;
#else /* _WIN64 */
	System::Generics::Collections::TList__1<System::TArray__1<System::Byte> >* FEvents;
#endif /* _WIN64 */
	System::Classes::TStrings* FUniEvents;
	TEventAlert FOnEventAlert;
	System::Generics::Collections::TList__1<System::Classes::TThread*>* FThreads;
	void * *FNativeHandle;
	bool ThreadException;
	Ibx::Ibdatabase::TIBDatabase* FDatabase;
	TErrorEvent FOnError;
	bool FAutoRegister;
	bool FRegistered;
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* value);
	void __fastcall SetEvents(System::Classes::TStrings* Value);
	bool __fastcall GetRegistered();
	void __fastcall SetRegistered(const bool Value);
	
protected:
	virtual Ibx::Ibexternals::PVoid __fastcall GetNativeHandle();
	virtual void __fastcall EventChange(System::TObject* Sender);
	virtual void __fastcall ThreadEnded(System::TObject* Sender);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall ValidateDatabase(Ibx::Ibdatabase::TIBDatabase* DataBase);
	
public:
	__fastcall virtual TIBEvents(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBEvents();
	virtual void __fastcall RegisterEvents();
	virtual void __fastcall UnRegisterEvents();
	__property Ibx::Ibexternals::PVoid NativeHandle = {read=GetNativeHandle};
	void __fastcall SetAutoRegister(const bool Value);
	bool __fastcall GetAutoRegister();
	
__published:
	__property bool AutoRegister = {read=GetAutoRegister, write=SetAutoRegister, nodefault};
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=FDatabase, write=SetDatabase};
	__property System::Classes::TStrings* Events = {read=FUniEvents, write=SetEvents};
	__property bool Registered = {read=GetRegistered, write=SetRegistered, nodefault};
	__property TEventAlert OnEventAlert = {read=FOnEventAlert, write=FOnEventAlert};
	__property TErrorEvent OnError = {read=FOnError, write=FOnError};
private:
	void *__IIBEventNotifier;	// Ibx::Ibdatabase::IIBEventNotifier 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9427DE09-46F7-4E1D-8B92-C1F88B47BF6D}
	operator Ibx::Ibdatabase::_di_IIBEventNotifier()
	{
		Ibx::Ibdatabase::_di_IIBEventNotifier intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Ibx::Ibdatabase::IIBEventNotifier*(void) { return (Ibx::Ibdatabase::IIBEventNotifier*)&__IIBEventNotifier; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibevents */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBEVENTS)
using namespace Ibx::Ibevents;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbeventsHPP
