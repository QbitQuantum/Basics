// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Android.Security.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_Android_SecurityHPP
#define Androidapi_Jni_Android_SecurityHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.Java.Security.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Net.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Android
{
namespace Security
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JKeyChainClass;
typedef System::DelphiInterface<JKeyChainClass> _di_JKeyChainClass;
__interface DELPHIINTERFACE JKeyChain;
typedef System::DelphiInterface<JKeyChain> _di_JKeyChain;
class DELPHICLASS TJKeyChain;
__interface DELPHIINTERFACE JKeyChainAliasCallbackClass;
typedef System::DelphiInterface<JKeyChainAliasCallbackClass> _di_JKeyChainAliasCallbackClass;
__interface DELPHIINTERFACE JKeyChainAliasCallback;
typedef System::DelphiInterface<JKeyChainAliasCallback> _di_JKeyChainAliasCallback;
class DELPHICLASS TJKeyChainAliasCallback;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{318B9BE7-6348-4F80-B891-DC10D7045678}") JKeyChainClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_KEYCHAIN_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_KEY_ACCESS_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_STORAGE_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_TRUST_STORE_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CERTIFICATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_KEY_ACCESSIBLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_KEY_ALIAS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PKCS12() = 0 ;
	HIDESBASE virtual _di_JKeyChain __cdecl init() = 0 ;
	virtual void __cdecl choosePrivateKeyAlias(Androidapi::Jni::App::_di_JActivity activity, _di_JKeyChainAliasCallback response, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* keyTypes, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JPrincipal>* issuers, Androidapi::Jni::Javatypes::_di_JString host, int port, Androidapi::Jni::Javatypes::_di_JString alias) = 0 /* overload */;
	virtual void __cdecl choosePrivateKeyAlias(Androidapi::Jni::App::_di_JActivity activity, _di_JKeyChainAliasCallback response, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* keyTypes, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JPrincipal>* issuers, Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jni::Javatypes::_di_JString alias) = 0 /* overload */;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIntent __cdecl createInstallIntent() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JX509Certificate>* __cdecl getCertificateChain(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString alias) = 0 ;
	virtual Androidapi::Jni::Java::Security::_di_JPrivateKey __cdecl getPrivateKey(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString alias) = 0 ;
	virtual bool __cdecl isBoundKeyAlgorithm(Androidapi::Jni::Javatypes::_di_JString algorithm) = 0 ;
	virtual bool __cdecl isKeyAlgorithmSupported(Androidapi::Jni::Javatypes::_di_JString algorithm) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_KEYCHAIN_CHANGED = {read=_GetACTION_KEYCHAIN_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_KEY_ACCESS_CHANGED = {read=_GetACTION_KEY_ACCESS_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_STORAGE_CHANGED = {read=_GetACTION_STORAGE_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_TRUST_STORE_CHANGED = {read=_GetACTION_TRUST_STORE_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CERTIFICATE = {read=_GetEXTRA_CERTIFICATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_KEY_ACCESSIBLE = {read=_GetEXTRA_KEY_ACCESSIBLE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_KEY_ALIAS = {read=_GetEXTRA_KEY_ALIAS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_NAME = {read=_GetEXTRA_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PKCS12 = {read=_GetEXTRA_PKCS12};
};

__interface  INTERFACE_UUID("{BAB71601-7B0E-49A7-9760-EB868ACFF24A}") JKeyChain  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJKeyChain : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyChainClass,_di_JKeyChain>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyChainClass,_di_JKeyChain> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJKeyChain() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyChainClass,_di_JKeyChain>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJKeyChain() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1DD718B7-A496-4C6A-96AE-5C7D37E5476F}") JKeyChainAliasCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{91594681-1CCA-4081-9A5B-0703B73F380E}") JKeyChainAliasCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl alias(Androidapi::Jni::Javatypes::_di_JString alias) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJKeyChainAliasCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyChainAliasCallbackClass,_di_JKeyChainAliasCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyChainAliasCallbackClass,_di_JKeyChainAliasCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJKeyChainAliasCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyChainAliasCallbackClass,_di_JKeyChainAliasCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJKeyChainAliasCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Security */
}	/* namespace Android */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_ANDROID_SECURITY)
using namespace Androidapi::Jni::Android::Security;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_ANDROID)
using namespace Androidapi::Jni::Android;
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
#endif	// Androidapi_Jni_Android_SecurityHPP
