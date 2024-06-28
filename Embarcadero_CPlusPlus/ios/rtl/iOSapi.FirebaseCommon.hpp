// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.FirebaseCommon.pas' rev: 34.00 (iOS)

#ifndef Iosapi_FirebasecommonHPP
#define Iosapi_FirebasecommonHPP

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
namespace Firebasecommon
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE FIRAppClass;
typedef System::DelphiInterface<FIRAppClass> _di_FIRAppClass;
__interface DELPHIINTERFACE FIRApp;
typedef System::DelphiInterface<FIRApp> _di_FIRApp;
class DELPHICLASS TFIRApp;
__interface DELPHIINTERFACE FIRInstanceIDClass;
typedef System::DelphiInterface<FIRInstanceIDClass> _di_FIRInstanceIDClass;
__interface DELPHIINTERFACE FIRInstanceID;
typedef System::DelphiInterface<FIRInstanceID> _di_FIRInstanceID;
class DELPHICLASS TFIRInstanceID;
//-- type declarations -------------------------------------------------------
typedef unsigned long FIRInstanceIDError;

__interface  INTERFACE_UUID("{B8962096-555F-498E-B102-8EC66E871EF2}") FIRAppClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void __cdecl configure() = 0 ;
};

__interface  INTERFACE_UUID("{FFF4B247-25C6-47B8-BBC5-893D2170EFA5}") FIRApp  : public Iosapi::Foundation::NSObject 
{
	
};

class PASCALIMPLEMENTATION TFIRApp : public Macapi::Objectivec::TOCGenericImport__2<_di_FIRAppClass,_di_FIRApp>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_FIRAppClass,_di_FIRApp> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TFIRApp(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_FIRAppClass,_di_FIRApp>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TFIRApp() { }
	
};


__interface  INTERFACE_UUID("{4A9F1C85-AEDE-4284-A7DC-0EF9111504B1}") FIRInstanceIDClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl instanceID() = 0 ;
};

__interface  INTERFACE_UUID("{2967A1F9-98F5-40E6-8BDA-A25D3C699ED3}") FIRInstanceID  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl token() = 0 ;
};

class PASCALIMPLEMENTATION TFIRInstanceID : public Macapi::Objectivec::TOCGenericImport__2<_di_FIRInstanceIDClass,_di_FIRInstanceID>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_FIRInstanceIDClass,_di_FIRInstanceID> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TFIRInstanceID(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_FIRInstanceIDClass,_di_FIRInstanceID>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TFIRInstanceID() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 FIRInstanceIDErrorUnknown = System::Int8(0x0);
static constexpr System::Int8 FIRInstanceIDErrorAuthentication = System::Int8(0x1);
static constexpr System::Int8 FIRInstanceIDErrorNoAccess = System::Int8(0x2);
static constexpr System::Int8 FIRInstanceIDErrorTimeout = System::Int8(0x3);
static constexpr System::Int8 FIRInstanceIDErrorNetwork = System::Int8(0x4);
static constexpr System::Int8 FIRInstanceIDErrorOperationInProgress = System::Int8(0x5);
static constexpr System::Int8 FIRInstanceIDErrorInvalidRequest = System::Int8(0x7);
static constexpr System::Int8 FIRInstanceIDAPNSTokenTypeUnknown = System::Int8(0x0);
static constexpr System::Int8 FIRInstanceIDAPNSTokenTypeSandbox = System::Int8(0x1);
static constexpr System::Int8 FIRInstanceIDAPNSTokenTypeProd = System::Int8(0x2);
}	/* namespace Firebasecommon */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_FIREBASECOMMON)
using namespace Iosapi::Firebasecommon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_FirebasecommonHPP
