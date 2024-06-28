// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Licensing.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_LicensingHPP
#define Androidapi_Jni_LicensingHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Licensing
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JAESObfuscatorClass;
typedef System::DelphiInterface<JAESObfuscatorClass> _di_JAESObfuscatorClass;
__interface DELPHIINTERFACE JAESObfuscator;
typedef System::DelphiInterface<JAESObfuscator> _di_JAESObfuscator;
class DELPHICLASS TJAESObfuscator;
__interface DELPHIINTERFACE JAPKExpansionPolicyClass;
typedef System::DelphiInterface<JAPKExpansionPolicyClass> _di_JAPKExpansionPolicyClass;
__interface DELPHIINTERFACE JAPKExpansionPolicy;
typedef System::DelphiInterface<JAPKExpansionPolicy> _di_JAPKExpansionPolicy;
class DELPHICLASS TJAPKExpansionPolicy;
__interface DELPHIINTERFACE JDeviceLimiterClass;
typedef System::DelphiInterface<JDeviceLimiterClass> _di_JDeviceLimiterClass;
__interface DELPHIINTERFACE JDeviceLimiter;
typedef System::DelphiInterface<JDeviceLimiter> _di_JDeviceLimiter;
class DELPHICLASS TJDeviceLimiter;
__interface DELPHIINTERFACE JILicenseResultListenerClass;
typedef System::DelphiInterface<JILicenseResultListenerClass> _di_JILicenseResultListenerClass;
__interface DELPHIINTERFACE JILicenseResultListener;
typedef System::DelphiInterface<JILicenseResultListener> _di_JILicenseResultListener;
class DELPHICLASS TJILicenseResultListener;
__interface DELPHIINTERFACE JILicenseResultListener_StubClass;
typedef System::DelphiInterface<JILicenseResultListener_StubClass> _di_JILicenseResultListener_StubClass;
__interface DELPHIINTERFACE JILicenseResultListener_Stub;
typedef System::DelphiInterface<JILicenseResultListener_Stub> _di_JILicenseResultListener_Stub;
class DELPHICLASS TJILicenseResultListener_Stub;
__interface DELPHIINTERFACE JILicensingServiceClass;
typedef System::DelphiInterface<JILicensingServiceClass> _di_JILicensingServiceClass;
__interface DELPHIINTERFACE JILicensingService;
typedef System::DelphiInterface<JILicensingService> _di_JILicensingService;
class DELPHICLASS TJILicensingService;
__interface DELPHIINTERFACE JILicensingService_StubClass;
typedef System::DelphiInterface<JILicensingService_StubClass> _di_JILicensingService_StubClass;
__interface DELPHIINTERFACE JILicensingService_Stub;
typedef System::DelphiInterface<JILicensingService_Stub> _di_JILicensingService_Stub;
class DELPHICLASS TJILicensingService_Stub;
__interface DELPHIINTERFACE JLicenseCheckerClass;
typedef System::DelphiInterface<JLicenseCheckerClass> _di_JLicenseCheckerClass;
__interface DELPHIINTERFACE JLicenseChecker;
typedef System::DelphiInterface<JLicenseChecker> _di_JLicenseChecker;
class DELPHICLASS TJLicenseChecker;
__interface DELPHIINTERFACE JLicenseCheckerCallbackClass;
typedef System::DelphiInterface<JLicenseCheckerCallbackClass> _di_JLicenseCheckerCallbackClass;
__interface DELPHIINTERFACE JLicenseCheckerCallback;
typedef System::DelphiInterface<JLicenseCheckerCallback> _di_JLicenseCheckerCallback;
class DELPHICLASS TJLicenseCheckerCallback;
__interface DELPHIINTERFACE JNullDeviceLimiterClass;
typedef System::DelphiInterface<JNullDeviceLimiterClass> _di_JNullDeviceLimiterClass;
__interface DELPHIINTERFACE JNullDeviceLimiter;
typedef System::DelphiInterface<JNullDeviceLimiter> _di_JNullDeviceLimiter;
class DELPHICLASS TJNullDeviceLimiter;
__interface DELPHIINTERFACE JObfuscatorClass;
typedef System::DelphiInterface<JObfuscatorClass> _di_JObfuscatorClass;
__interface DELPHIINTERFACE JObfuscator;
typedef System::DelphiInterface<JObfuscator> _di_JObfuscator;
class DELPHICLASS TJObfuscator;
__interface DELPHIINTERFACE Jlicensing_PolicyClass;
typedef System::DelphiInterface<Jlicensing_PolicyClass> _di_Jlicensing_PolicyClass;
__interface DELPHIINTERFACE Jlicensing_Policy;
typedef System::DelphiInterface<Jlicensing_Policy> _di_Jlicensing_Policy;
class DELPHICLASS TJlicensing_Policy;
__interface DELPHIINTERFACE JPreferenceObfuscatorClass;
typedef System::DelphiInterface<JPreferenceObfuscatorClass> _di_JPreferenceObfuscatorClass;
__interface DELPHIINTERFACE JPreferenceObfuscator;
typedef System::DelphiInterface<JPreferenceObfuscator> _di_JPreferenceObfuscator;
class DELPHICLASS TJPreferenceObfuscator;
__interface DELPHIINTERFACE JResponseDataClass;
typedef System::DelphiInterface<JResponseDataClass> _di_JResponseDataClass;
__interface DELPHIINTERFACE JResponseData;
typedef System::DelphiInterface<JResponseData> _di_JResponseData;
class DELPHICLASS TJResponseData;
__interface DELPHIINTERFACE JServerManagedPolicyClass;
typedef System::DelphiInterface<JServerManagedPolicyClass> _di_JServerManagedPolicyClass;
__interface DELPHIINTERFACE JServerManagedPolicy;
typedef System::DelphiInterface<JServerManagedPolicy> _di_JServerManagedPolicy;
class DELPHICLASS TJServerManagedPolicy;
__interface DELPHIINTERFACE JStrictPolicyClass;
typedef System::DelphiInterface<JStrictPolicyClass> _di_JStrictPolicyClass;
__interface DELPHIINTERFACE JStrictPolicy;
typedef System::DelphiInterface<JStrictPolicy> _di_JStrictPolicy;
class DELPHICLASS TJStrictPolicy;
__interface DELPHIINTERFACE JValidationExceptionClass;
typedef System::DelphiInterface<JValidationExceptionClass> _di_JValidationExceptionClass;
__interface DELPHIINTERFACE JValidationException;
typedef System::DelphiInterface<JValidationException> _di_JValidationException;
class DELPHICLASS TJValidationException;
__interface DELPHIINTERFACE Jutil_Base64Class;
typedef System::DelphiInterface<Jutil_Base64Class> _di_Jutil_Base64Class;
__interface DELPHIINTERFACE Jutil_Base64;
typedef System::DelphiInterface<Jutil_Base64> _di_Jutil_Base64;
class DELPHICLASS TJutil_Base64;
__interface DELPHIINTERFACE JBase64DecoderExceptionClass;
typedef System::DelphiInterface<JBase64DecoderExceptionClass> _di_JBase64DecoderExceptionClass;
__interface DELPHIINTERFACE JBase64DecoderException;
typedef System::DelphiInterface<JBase64DecoderException> _di_JBase64DecoderException;
class DELPHICLASS TJBase64DecoderException;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{55A9ACD3-C1B7-4F85-9580-1B151CE1986B}") JAESObfuscatorClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JAESObfuscator __cdecl init(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* salt, Androidapi::Jni::Javatypes::_di_JString applicationId, Androidapi::Jni::Javatypes::_di_JString deviceId) = 0 ;
};

__interface  INTERFACE_UUID("{F5976BA5-419E-4168-B27F-A345008BFF85}") JAESObfuscator  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl obfuscate(Androidapi::Jni::Javatypes::_di_JString original, Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl unobfuscate(Androidapi::Jni::Javatypes::_di_JString obfuscated, Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAESObfuscator : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAESObfuscatorClass,_di_JAESObfuscator>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAESObfuscatorClass,_di_JAESObfuscator> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAESObfuscator() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAESObfuscatorClass,_di_JAESObfuscator>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAESObfuscator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C28EBC8B-3CE0-494D-8A22-397740B7C8D0}") JAPKExpansionPolicyClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetMAIN_FILE_URL_INDEX() = 0 ;
	virtual int __cdecl _GetPATCH_FILE_URL_INDEX() = 0 ;
	HIDESBASE virtual _di_JAPKExpansionPolicy __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, _di_JObfuscator obfuscator) = 0 ;
	__property int MAIN_FILE_URL_INDEX = {read=_GetMAIN_FILE_URL_INDEX};
	__property int PATCH_FILE_URL_INDEX = {read=_GetPATCH_FILE_URL_INDEX};
};

__interface  INTERFACE_UUID("{CE25C415-6076-496D-A80B-13C5CDB18E54}") JAPKExpansionPolicy  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl allowAccess() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getExpansionFileName(int index) = 0 ;
	virtual __int64 __cdecl getExpansionFileSize(int index) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getExpansionURL(int index) = 0 ;
	virtual int __cdecl getExpansionURLCount() = 0 ;
	virtual __int64 __cdecl getMaxRetries() = 0 ;
	virtual __int64 __cdecl getRetryCount() = 0 ;
	virtual __int64 __cdecl getRetryUntil() = 0 ;
	virtual __int64 __cdecl getValidityTimestamp() = 0 ;
	virtual void __cdecl processServerResponse(int response, _di_JResponseData rawData) = 0 ;
	virtual void __cdecl resetPolicy() = 0 ;
	virtual void __cdecl setExpansionFileName(int index, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual void __cdecl setExpansionFileSize(int index, __int64 size) = 0 ;
	virtual void __cdecl setExpansionURL(int index, Androidapi::Jni::Javatypes::_di_JString URL) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAPKExpansionPolicy : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAPKExpansionPolicyClass,_di_JAPKExpansionPolicy>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAPKExpansionPolicyClass,_di_JAPKExpansionPolicy> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAPKExpansionPolicy() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAPKExpansionPolicyClass,_di_JAPKExpansionPolicy>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAPKExpansionPolicy() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F152865E-AB95-4A30-8169-8ACA1522144D}") JDeviceLimiterClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{EBB6D37F-98E4-4488-A84B-117DEE31E9E4}") JDeviceLimiter  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual int __cdecl isDeviceAllowed(Androidapi::Jni::Javatypes::_di_JString userId) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDeviceLimiter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDeviceLimiterClass,_di_JDeviceLimiter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDeviceLimiterClass,_di_JDeviceLimiter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDeviceLimiter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDeviceLimiterClass,_di_JDeviceLimiter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDeviceLimiter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8735CD6F-44B9-45F4-863D-345922715267}") JILicenseResultListenerClass  : public Androidapi::Jni::Os::JIInterfaceClass 
{
	
};

__interface  INTERFACE_UUID("{5068B9E1-9E56-4821-9734-5FB7C6A8DC85}") JILicenseResultListener  : public Androidapi::Jni::Os::JIInterface 
{
	virtual void __cdecl verifyLicense(int responseCode, Androidapi::Jni::Javatypes::_di_JString signedData, Androidapi::Jni::Javatypes::_di_JString signature) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJILicenseResultListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicenseResultListenerClass,_di_JILicenseResultListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicenseResultListenerClass,_di_JILicenseResultListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJILicenseResultListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicenseResultListenerClass,_di_JILicenseResultListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJILicenseResultListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{48180ACB-E93B-43F2-AD3B-A73F7A176B41}") JILicenseResultListener_StubClass  : public Androidapi::Jni::Os::JBinderClass 
{
	HIDESBASE virtual _di_JILicenseResultListener_Stub __cdecl init() = 0 ;
	virtual _di_JILicenseResultListener __cdecl asInterface(Androidapi::Jni::Os::_di_JIBinder obj) = 0 ;
};

__interface  INTERFACE_UUID("{960F10A1-8592-4C50-8506-B589D1EA9A64}") JILicenseResultListener_Stub  : public Androidapi::Jni::Os::JBinder 
{
	virtual Androidapi::Jni::Os::_di_JIBinder __cdecl asBinder() = 0 ;
	virtual bool __cdecl onTransact(int code, Androidapi::Jni::Os::_di_JParcel data, Androidapi::Jni::Os::_di_JParcel reply, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJILicenseResultListener_Stub : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicenseResultListener_StubClass,_di_JILicenseResultListener_Stub>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicenseResultListener_StubClass,_di_JILicenseResultListener_Stub> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJILicenseResultListener_Stub() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicenseResultListener_StubClass,_di_JILicenseResultListener_Stub>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJILicenseResultListener_Stub() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5B7B7AF1-8283-4DCE-BA6B-7DAA989E6C20}") JILicensingServiceClass  : public Androidapi::Jni::Os::JIInterfaceClass 
{
	
};

__interface  INTERFACE_UUID("{624CBEA8-0C84-4AC6-8061-38FAF9A7F6E8}") JILicensingService  : public Androidapi::Jni::Os::JIInterface 
{
	virtual void __cdecl checkLicense(__int64 nonce, Androidapi::Jni::Javatypes::_di_JString packageName, _di_JILicenseResultListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJILicensingService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicensingServiceClass,_di_JILicensingService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicensingServiceClass,_di_JILicensingService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJILicensingService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicensingServiceClass,_di_JILicensingService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJILicensingService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CD2987DA-F1BB-4DDB-ADC6-88C108C2EAFE}") JILicensingService_StubClass  : public Androidapi::Jni::Os::JBinderClass 
{
	HIDESBASE virtual _di_JILicensingService_Stub __cdecl init() = 0 ;
	virtual _di_JILicensingService __cdecl asInterface(Androidapi::Jni::Os::_di_JIBinder obj) = 0 ;
};

__interface  INTERFACE_UUID("{10038698-0D70-479A-8064-FFD14E43F22E}") JILicensingService_Stub  : public Androidapi::Jni::Os::JBinder 
{
	virtual Androidapi::Jni::Os::_di_JIBinder __cdecl asBinder() = 0 ;
	virtual bool __cdecl onTransact(int code, Androidapi::Jni::Os::_di_JParcel data, Androidapi::Jni::Os::_di_JParcel reply, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJILicensingService_Stub : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicensingService_StubClass,_di_JILicensingService_Stub>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicensingService_StubClass,_di_JILicensingService_Stub> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJILicensingService_Stub() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JILicensingService_StubClass,_di_JILicensingService_Stub>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJILicensingService_Stub() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7D5CBCE6-32D5-4DC4-A9A9-83ED7DCB5958}") JLicenseCheckerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JLicenseChecker __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, _di_Jlicensing_Policy policy, Androidapi::Jni::Javatypes::_di_JString encodedPublicKey) = 0 ;
};

__interface  INTERFACE_UUID("{26319EFF-5FE5-4EA8-83E4-5319E4493A23}") JLicenseChecker  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl checkAccess(_di_JLicenseCheckerCallback callback) = 0 ;
	virtual void __cdecl onDestroy() = 0 ;
	virtual void __cdecl onServiceConnected(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName name, Androidapi::Jni::Os::_di_JIBinder service) = 0 ;
	virtual void __cdecl onServiceDisconnected(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName name) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLicenseChecker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLicenseCheckerClass,_di_JLicenseChecker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLicenseCheckerClass,_di_JLicenseChecker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLicenseChecker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLicenseCheckerClass,_di_JLicenseChecker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLicenseChecker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{95961C5E-E8BE-401F-B4AF-799653921CFD}") JLicenseCheckerCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetERROR_CHECK_IN_PROGRESS() = 0 ;
	virtual int __cdecl _GetERROR_INVALID_PACKAGE_NAME() = 0 ;
	virtual int __cdecl _GetERROR_INVALID_PUBLIC_KEY() = 0 ;
	virtual int __cdecl _GetERROR_MISSING_PERMISSION() = 0 ;
	virtual int __cdecl _GetERROR_NON_MATCHING_UID() = 0 ;
	virtual int __cdecl _GetERROR_NOT_MARKET_MANAGED() = 0 ;
	__property int ERROR_CHECK_IN_PROGRESS = {read=_GetERROR_CHECK_IN_PROGRESS};
	__property int ERROR_INVALID_PACKAGE_NAME = {read=_GetERROR_INVALID_PACKAGE_NAME};
	__property int ERROR_INVALID_PUBLIC_KEY = {read=_GetERROR_INVALID_PUBLIC_KEY};
	__property int ERROR_MISSING_PERMISSION = {read=_GetERROR_MISSING_PERMISSION};
	__property int ERROR_NON_MATCHING_UID = {read=_GetERROR_NON_MATCHING_UID};
	__property int ERROR_NOT_MARKET_MANAGED = {read=_GetERROR_NOT_MARKET_MANAGED};
};

__interface  INTERFACE_UUID("{89E61A05-026B-47D3-A198-82364C9B5B53}") JLicenseCheckerCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl allow(int reason) = 0 ;
	virtual void __cdecl applicationError(int errorCode) = 0 ;
	virtual void __cdecl dontAllow(int reason) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLicenseCheckerCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLicenseCheckerCallbackClass,_di_JLicenseCheckerCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLicenseCheckerCallbackClass,_di_JLicenseCheckerCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLicenseCheckerCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLicenseCheckerCallbackClass,_di_JLicenseCheckerCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLicenseCheckerCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FBE817CC-5C88-432C-9BDC-99B7AF895EAD}") JNullDeviceLimiterClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JNullDeviceLimiter __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{126F2762-80F7-4EC6-80AC-3690A7C1198F}") JNullDeviceLimiter  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl isDeviceAllowed(Androidapi::Jni::Javatypes::_di_JString userId) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNullDeviceLimiter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNullDeviceLimiterClass,_di_JNullDeviceLimiter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNullDeviceLimiterClass,_di_JNullDeviceLimiter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNullDeviceLimiter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNullDeviceLimiterClass,_di_JNullDeviceLimiter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNullDeviceLimiter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D7285329-4BFC-4697-B88E-4E12886CE4EC}") JObfuscatorClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C2298636-8597-49FF-AE0A-86C9EC98AA65}") JObfuscator  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl obfuscate(Androidapi::Jni::Javatypes::_di_JString original, Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl unobfuscate(Androidapi::Jni::Javatypes::_di_JString obfuscated, Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJObfuscator : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JObfuscatorClass,_di_JObfuscator>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JObfuscatorClass,_di_JObfuscator> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJObfuscator() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JObfuscatorClass,_di_JObfuscator>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJObfuscator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F30F5194-7323-46CA-A1FA-D375AB185678}") Jlicensing_PolicyClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetLICENSED() = 0 ;
	virtual int __cdecl _GetNOT_LICENSED() = 0 ;
	virtual int __cdecl _GetRETRY() = 0 ;
	__property int LICENSED = {read=_GetLICENSED};
	__property int NOT_LICENSED = {read=_GetNOT_LICENSED};
	__property int RETRY = {read=_GetRETRY};
};

__interface  INTERFACE_UUID("{F8932C2C-7AF9-48E4-B9CA-B48F44904783}") Jlicensing_Policy  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl allowAccess() = 0 ;
	virtual void __cdecl processServerResponse(int response, _di_JResponseData rawData) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJlicensing_Policy : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jlicensing_PolicyClass,_di_Jlicensing_Policy>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jlicensing_PolicyClass,_di_Jlicensing_Policy> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJlicensing_Policy() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jlicensing_PolicyClass,_di_Jlicensing_Policy>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJlicensing_Policy() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3F1D2984-06B0-4DFB-9D0E-93E8F80F1944}") JPreferenceObfuscatorClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JPreferenceObfuscator __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JSharedPreferences sp, _di_JObfuscator o) = 0 ;
};

__interface  INTERFACE_UUID("{9E65AF7D-F6EB-4E6C-8472-A8D3E4362376}") JPreferenceObfuscator  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl commit() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getString(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JString defValue) = 0 ;
	virtual void __cdecl putString(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPreferenceObfuscator : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPreferenceObfuscatorClass,_di_JPreferenceObfuscator>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPreferenceObfuscatorClass,_di_JPreferenceObfuscator> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPreferenceObfuscator() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPreferenceObfuscatorClass,_di_JPreferenceObfuscator>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPreferenceObfuscator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6FB3D196-51DD-44FF-9C24-E7663EBC017F}") JResponseDataClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JResponseData __cdecl init() = 0 ;
	virtual _di_JResponseData __cdecl parse(Androidapi::Jni::Javatypes::_di_JString responseData) = 0 ;
};

__interface  INTERFACE_UUID("{D4CAD4F3-A0F1-45CA-B7AE-E1B14AF600B0}") JResponseData  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getextra() = 0 ;
	virtual void __cdecl _Setextra(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual int __cdecl _Getnonce() = 0 ;
	virtual void __cdecl _Setnonce(int Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetpackageName() = 0 ;
	virtual void __cdecl _SetpackageName(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual int __cdecl _GetresponseCode() = 0 ;
	virtual void __cdecl _SetresponseCode(int Value) = 0 ;
	virtual __int64 __cdecl _Gettimestamp() = 0 ;
	virtual void __cdecl _Settimestamp(__int64 Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetuserId() = 0 ;
	virtual void __cdecl _SetuserId(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetversionCode() = 0 ;
	virtual void __cdecl _SetversionCode(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString extra = {read=_Getextra, write=_Setextra};
	__property int nonce = {read=_Getnonce, write=_Setnonce};
	__property Androidapi::Jni::Javatypes::_di_JString packageName = {read=_GetpackageName, write=_SetpackageName};
	__property int responseCode = {read=_GetresponseCode, write=_SetresponseCode};
	__property __int64 timestamp = {read=_Gettimestamp, write=_Settimestamp};
	__property Androidapi::Jni::Javatypes::_di_JString userId = {read=_GetuserId, write=_SetuserId};
	__property Androidapi::Jni::Javatypes::_di_JString versionCode = {read=_GetversionCode, write=_SetversionCode};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJResponseData : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JResponseDataClass,_di_JResponseData>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JResponseDataClass,_di_JResponseData> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJResponseData() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JResponseDataClass,_di_JResponseData>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJResponseData() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A17DDC78-5806-4E9F-B6DB-93D43B1FEF1F}") JServerManagedPolicyClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JServerManagedPolicy __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, _di_JObfuscator obfuscator) = 0 ;
};

__interface  INTERFACE_UUID("{DE9A9C94-AE7B-42E6-9352-C2F5DA01F458}") JServerManagedPolicy  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl allowAccess() = 0 ;
	virtual __int64 __cdecl getMaxRetries() = 0 ;
	virtual __int64 __cdecl getRetryCount() = 0 ;
	virtual __int64 __cdecl getRetryUntil() = 0 ;
	virtual __int64 __cdecl getValidityTimestamp() = 0 ;
	virtual void __cdecl processServerResponse(int response, _di_JResponseData rawData) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJServerManagedPolicy : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServerManagedPolicyClass,_di_JServerManagedPolicy>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServerManagedPolicyClass,_di_JServerManagedPolicy> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJServerManagedPolicy() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServerManagedPolicyClass,_di_JServerManagedPolicy>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJServerManagedPolicy() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{75D0AA86-C7B0-4904-B502-CB80E1450F8B}") JStrictPolicyClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JStrictPolicy __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{6C413FE6-AC6C-4B00-B658-71AC298B9051}") JStrictPolicy  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl allowAccess() = 0 ;
	virtual void __cdecl processServerResponse(int response, _di_JResponseData rawData) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJStrictPolicy : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStrictPolicyClass,_di_JStrictPolicy>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStrictPolicyClass,_di_JStrictPolicy> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJStrictPolicy() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JStrictPolicyClass,_di_JStrictPolicy>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJStrictPolicy() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4E036DD9-2488-4860-B92E-F9888A45A003}") JValidationExceptionClass  : public Androidapi::Jni::Javatypes::JExceptionClass 
{
	HIDESBASE virtual _di_JValidationException __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JValidationException __cdecl init(Androidapi::Jni::Javatypes::_di_JString s) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{E0A5A0D7-AE87-4C02-830B-8FCB67BF2C9C}") JValidationException  : public Androidapi::Jni::Javatypes::JException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJValidationException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JValidationExceptionClass,_di_JValidationException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JValidationExceptionClass,_di_JValidationException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJValidationException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JValidationExceptionClass,_di_JValidationException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJValidationException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{93BCFD52-79EC-4F15-8C10-49BE6EE35041}") Jutil_Base64Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual bool __cdecl _GetDECODE() = 0 ;
	virtual bool __cdecl _GetENCODE() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl decode(Androidapi::Jni::Javatypes::_di_JString s) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl decode(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* source) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl decode(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* source, int off, int len) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl decode(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* source, int off, int len, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* decodabet) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl decodeWebSafe(Androidapi::Jni::Javatypes::_di_JString s) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl decodeWebSafe(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* source) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl decodeWebSafe(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* source, int off, int len) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl encode(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* source) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl encode(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* source, int off, int len, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* alphabet, bool doPadding) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl encode(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* source, int off, int len, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* alphabet, int maxLineLength) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl encodeWebSafe(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* source, bool doPadding) = 0 ;
	__property bool DECODE = {read=_GetDECODE};
	__property bool ENCODE = {read=_GetENCODE};
};

__interface  INTERFACE_UUID("{FF441DE6-1F42-4C8E-B748-126F00309AB3}") Jutil_Base64  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJutil_Base64 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jutil_Base64Class,_di_Jutil_Base64>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jutil_Base64Class,_di_Jutil_Base64> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJutil_Base64() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jutil_Base64Class,_di_Jutil_Base64>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJutil_Base64() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8E5D4C35-4522-46F4-8B48-1969172871DD}") JBase64DecoderExceptionClass  : public Androidapi::Jni::Javatypes::JExceptionClass 
{
	HIDESBASE virtual _di_JBase64DecoderException __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JBase64DecoderException __cdecl init(Androidapi::Jni::Javatypes::_di_JString s) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{15F9F8C7-65B4-4DDB-B6A6-ADBACF394DFF}") JBase64DecoderException  : public Androidapi::Jni::Javatypes::JException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBase64DecoderException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBase64DecoderExceptionClass,_di_JBase64DecoderException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBase64DecoderExceptionClass,_di_JBase64DecoderException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBase64DecoderException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBase64DecoderExceptionClass,_di_JBase64DecoderException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBase64DecoderException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Licensing */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_LICENSING)
using namespace Androidapi::Jni::Licensing;
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
#endif	// Androidapi_Jni_LicensingHPP
