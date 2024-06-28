// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdIPAddrMon.pas' rev: 34.00 (Android)

#ifndef IdipaddrmonHPP
#define IdipaddrmonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdComponent.hpp>
#include <IdThread.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idipaddrmon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdIPAddrMonThread;
class DELPHICLASS TIdIPAddrMon;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdIPAddrMonEvent)(System::TObject* ASender, int AAdapter, System::UnicodeString AOldIP, System::UnicodeString ANewIP);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdIPAddrMonThread : public Idthread::TIdThread
{
	typedef Idthread::TIdThread inherited;
	
protected:
	unsigned FInterval;
	System::Classes::TNotifyEvent FOnTimerEvent;
	virtual void __fastcall Run();
	void __fastcall DoTimerEvent();
public:
	/* TIdThread.Create */ inline __fastcall virtual TIdIPAddrMonThread(bool ACreateSuspended, bool ALoop, const System::UnicodeString AName) : Idthread::TIdThread(ACreateSuspended, ALoop, AName) { }
	/* TIdThread.Destroy */ inline __fastcall virtual ~TIdIPAddrMonThread() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TIdIPAddrMon : public Idcomponent::TIdComponent
{
	typedef Idcomponent::TIdComponent inherited;
	
private:
	bool FActive;
	bool FBusy;
	unsigned FInterval;
	int FAdapterCount;
	TIdIPAddrMonThread* FThread;
	System::Classes::TStrings* FIPAddresses;
	System::Classes::TStrings* FPreviousIPAddresses;
	TIdIPAddrMonEvent FOnStatusChanged;
	void __fastcall SetActive(bool Value);
	void __fastcall SetInterval(unsigned Value);
	void __fastcall GetAdapterAddresses();
	void __fastcall DoStatusChanged();
	
protected:
	virtual void __fastcall InitComponent();
	virtual void __fastcall Loaded();
	
public:
	__fastcall virtual ~TIdIPAddrMon();
	void __fastcall CheckAdapters(System::TObject* Sender);
	void __fastcall ForceCheck();
	__property int AdapterCount = {read=FAdapterCount, nodefault};
	__property bool Busy = {read=FBusy, nodefault};
	__property System::Classes::TStrings* IPAddresses = {read=FIPAddresses};
	__property TIdIPAddrMonThread* Thread = {read=FThread};
	
__published:
	__property bool Active = {read=FActive, write=SetActive, nodefault};
	__property unsigned Interval = {read=FInterval, write=SetInterval, default=500};
	__property TIdIPAddrMonEvent OnStatusChanged = {read=FOnStatusChanged, write=FOnStatusChanged};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdIPAddrMon(System::Classes::TComponent* AOwner)/* overload */ : Idcomponent::TIdComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdIPAddrMon()/* overload */ : Idcomponent::TIdComponent() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word IdIPAddrMonInterval = System::Word(0x1f4);
}	/* namespace Idipaddrmon */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDIPADDRMON)
using namespace Idipaddrmon;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdipaddrmonHPP
