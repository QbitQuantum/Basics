// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.InAppBilling.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_InappbillingHPP
#define Androidapi_Jni_InappbillingHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Os.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Inappbilling
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JIInAppBillingServiceClass;
typedef System::DelphiInterface<JIInAppBillingServiceClass> _di_JIInAppBillingServiceClass;
__interface DELPHIINTERFACE JIInAppBillingService;
typedef System::DelphiInterface<JIInAppBillingService> _di_JIInAppBillingService;
class DELPHICLASS TJIInAppBillingService;
__interface DELPHIINTERFACE JIInAppBillingService_StubClass;
typedef System::DelphiInterface<JIInAppBillingService_StubClass> _di_JIInAppBillingService_StubClass;
__interface DELPHIINTERFACE JIInAppBillingService_Stub;
typedef System::DelphiInterface<JIInAppBillingService_Stub> _di_JIInAppBillingService_Stub;
class DELPHICLASS TJIInAppBillingService_Stub;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{914929AF-917C-4D7E-842C-656701CACCE7}") JIInAppBillingServiceClass  : public Androidapi::Jni::Os::JIInterfaceClass 
{
	
};

__interface  INTERFACE_UUID("{03D4C897-6265-4854-97C6-415F5C846C0E}") JIInAppBillingService  : public Androidapi::Jni::Os::JIInterface 
{
	virtual int __cdecl consumePurchase(int apiVersion, Androidapi::Jni::Javatypes::_di_JString packageName, Androidapi::Jni::Javatypes::_di_JString purchaseToken) = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getBuyIntent(int apiVersion, Androidapi::Jni::Javatypes::_di_JString packageName, Androidapi::Jni::Javatypes::_di_JString sku, Androidapi::Jni::Javatypes::_di_JString type_, Androidapi::Jni::Javatypes::_di_JString developerPayload) = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getPurchases(int apiVersion, Androidapi::Jni::Javatypes::_di_JString packageName, Androidapi::Jni::Javatypes::_di_JString type_, Androidapi::Jni::Javatypes::_di_JString continuationToken) = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getSkuDetails(int apiVersion, Androidapi::Jni::Javatypes::_di_JString packageName, Androidapi::Jni::Javatypes::_di_JString type_, Androidapi::Jni::Os::_di_JBundle skusBundle) = 0 ;
	virtual int __cdecl isBillingSupported(int apiVersion, Androidapi::Jni::Javatypes::_di_JString packageName, Androidapi::Jni::Javatypes::_di_JString type_) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIInAppBillingService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIInAppBillingServiceClass,_di_JIInAppBillingService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIInAppBillingServiceClass,_di_JIInAppBillingService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIInAppBillingService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIInAppBillingServiceClass,_di_JIInAppBillingService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIInAppBillingService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{77F4F8A3-E103-4CC1-AB9A-D373F71C6D4C}") JIInAppBillingService_StubClass  : public Androidapi::Jni::Os::JBinderClass 
{
	HIDESBASE virtual _di_JIInAppBillingService_Stub __cdecl init() = 0 ;
	virtual _di_JIInAppBillingService __cdecl asInterface(Androidapi::Jni::Os::_di_JIBinder obj) = 0 ;
};

__interface  INTERFACE_UUID("{A5D13E53-F09B-4972-A639-BF7D7B81C242}") JIInAppBillingService_Stub  : public Androidapi::Jni::Os::JBinder 
{
	virtual Androidapi::Jni::Os::_di_JIBinder __cdecl asBinder() = 0 ;
	virtual bool __cdecl onTransact(int code, Androidapi::Jni::Os::_di_JParcel data, Androidapi::Jni::Os::_di_JParcel reply, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIInAppBillingService_Stub : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIInAppBillingService_StubClass,_di_JIInAppBillingService_Stub>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIInAppBillingService_StubClass,_di_JIInAppBillingService_Stub> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIInAppBillingService_Stub() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIInAppBillingService_StubClass,_di_JIInAppBillingService_Stub>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIInAppBillingService_Stub() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Inappbilling */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_INAPPBILLING)
using namespace Androidapi::Jni::Inappbilling;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI)
using namespace Androidapi::Jni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_Jni_InappbillingHPP
