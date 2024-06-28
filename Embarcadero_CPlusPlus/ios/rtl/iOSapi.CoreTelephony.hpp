// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.CoreTelephony.pas' rev: 34.00 (iOS)

#ifndef Iosapi_CoretelephonyHPP
#define Iosapi_CoretelephonyHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Coretelephony
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE CTCarrierClass;
typedef System::DelphiInterface<CTCarrierClass> _di_CTCarrierClass;
__interface DELPHIINTERFACE CTCarrier;
typedef System::DelphiInterface<CTCarrier> _di_CTCarrier;
class DELPHICLASS TCTCarrier;
__interface DELPHIINTERFACE CTTelephonyNetworkInfoClass;
typedef System::DelphiInterface<CTTelephonyNetworkInfoClass> _di_CTTelephonyNetworkInfoClass;
__interface DELPHIINTERFACE CTTelephonyNetworkInfo;
typedef System::DelphiInterface<CTTelephonyNetworkInfo> _di_CTTelephonyNetworkInfo;
class DELPHICLASS TCTTelephonyNetworkInfo;
__interface DELPHIINTERFACE CTCallClass;
typedef System::DelphiInterface<CTCallClass> _di_CTCallClass;
__interface DELPHIINTERFACE CTCall;
typedef System::DelphiInterface<CTCall> _di_CTCall;
class DELPHICLASS TCTCall;
__interface DELPHIINTERFACE CTCallCenterClass;
typedef System::DelphiInterface<CTCallCenterClass> _di_CTCallCenterClass;
__interface DELPHIINTERFACE CTCallCenter;
typedef System::DelphiInterface<CTCallCenter> _di_CTCallCenter;
class DELPHICLASS TCTCallCenter;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{FA14F6EF-18EF-4AE0-A115-5D5819B05A32}") CTCarrierClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{7FF111BF-7573-4BD2-881F-0B614DD5C01E}") CTCarrier  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl allowsVOIP() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl carrierName() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl isoCountryCode() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl mobileCountryCode() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl mobileNetworkCode() = 0 ;
};

class PASCALIMPLEMENTATION TCTCarrier : public Macapi::Objectivec::TOCGenericImport__2<_di_CTCarrierClass,_di_CTCarrier>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CTCarrierClass,_di_CTCarrier> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCTCarrier(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CTCarrierClass,_di_CTCarrier>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCTCarrier() { }
	
};


typedef void __fastcall (__closure *TCellularProviderNotifier)(const _di_CTCarrier Data);

__interface  INTERFACE_UUID("{28EB8488-EE8F-4967-B8A8-6BF96AD4382D}") CTTelephonyNetworkInfoClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{F75CE940-A78E-4C64-812E-0576386B582D}") CTTelephonyNetworkInfo  : public Iosapi::Foundation::NSObject 
{
	virtual _di_CTCarrier __cdecl subscriberCellularProvider() = 0 ;
	virtual void __cdecl setSubscriberCellularProviderDidUpdateNotifier(TCellularProviderNotifier Handler) = 0 ;
};

class PASCALIMPLEMENTATION TCTTelephonyNetworkInfo : public Macapi::Objectivec::TOCGenericImport__2<_di_CTTelephonyNetworkInfoClass,_di_CTTelephonyNetworkInfo>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CTTelephonyNetworkInfoClass,_di_CTTelephonyNetworkInfo> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCTTelephonyNetworkInfo(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CTTelephonyNetworkInfoClass,_di_CTTelephonyNetworkInfo>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCTTelephonyNetworkInfo() { }
	
};


__interface  INTERFACE_UUID("{1FA8C69C-57FA-4607-ACBA-547C9636312F}") CTCallClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{31625956-A516-437B-A385-7DF292D6FB5A}") CTCall  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl callID() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl callState() = 0 ;
};

class PASCALIMPLEMENTATION TCTCall : public Macapi::Objectivec::TOCGenericImport__2<_di_CTCallClass,_di_CTCall>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CTCallClass,_di_CTCall> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCTCall(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CTCallClass,_di_CTCall>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCTCall() { }
	
};


typedef void __fastcall (__closure *TCallEventHandler)(const _di_CTCall Data);

__interface  INTERFACE_UUID("{A28B0E07-ED5A-4C05-82DA-E9FE4073E14D}") CTCallCenterClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{0FDB7AC7-B379-4E20-8D72-F1C11EA32EB6}") CTCallCenter  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setCallEventHandler(TCallEventHandler EventHandler) = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl currentCalls() = 0 ;
};

class PASCALIMPLEMENTATION TCTCallCenter : public Macapi::Objectivec::TOCGenericImport__2<_di_CTCallCenterClass,_di_CTCallCenter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CTCallCenterClass,_di_CTCallCenter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCTCallCenter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CTCallCenterClass,_di_CTCallCenter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCTCallCenter() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define libCoreTelephony u"/System/Library/Frameworks/CoreTelephony.framework/CoreTel"\
	u"ephony"
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CTCallStateDialing(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CTCallStateIncoming(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CTCallStateConnected(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall CTCallStateDisconnected(void);
}	/* namespace Coretelephony */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_CORETELEPHONY)
using namespace Iosapi::Coretelephony;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_CoretelephonyHPP
