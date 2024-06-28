// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Embarcadero.Firebase.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_Embarcadero_FirebaseHPP
#define Androidapi_Jni_Embarcadero_FirebaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.Firebase.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Os.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Embarcadero
{
namespace Firebase
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE Jmessaging_ProxyFirebaseMessagingServiceClass;
typedef System::DelphiInterface<Jmessaging_ProxyFirebaseMessagingServiceClass> _di_Jmessaging_ProxyFirebaseMessagingServiceClass;
__interface DELPHIINTERFACE Jmessaging_ProxyFirebaseMessagingService;
typedef System::DelphiInterface<Jmessaging_ProxyFirebaseMessagingService> _di_Jmessaging_ProxyFirebaseMessagingService;
class DELPHICLASS TJmessaging_ProxyFirebaseMessagingService;
__interface DELPHIINTERFACE Jmessaging_PushNotificationListenerClass;
typedef System::DelphiInterface<Jmessaging_PushNotificationListenerClass> _di_Jmessaging_PushNotificationListenerClass;
__interface DELPHIINTERFACE Jmessaging_PushNotificationListener;
typedef System::DelphiInterface<Jmessaging_PushNotificationListener> _di_Jmessaging_PushNotificationListener;
class DELPHICLASS TJmessaging_PushNotificationListener;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{5D4B23EE-7D2D-4D21-BAED-38CC4795E00F}") Jmessaging_ProxyFirebaseMessagingServiceClass  : public Androidapi::Jni::Firebase::JFirebaseMessagingServiceClass 
{
	virtual bool __cdecl _GetDEBUG() = 0 ;
	virtual void __cdecl _SetDEBUG(bool Value) = 0 ;
	HIDESBASE virtual _di_Jmessaging_ProxyFirebaseMessagingService __cdecl init() = 0 ;
	virtual void __cdecl setListener(_di_Jmessaging_PushNotificationListener listener) = 0 ;
	__property bool DEBUG = {read=_GetDEBUG, write=_SetDEBUG};
};

__interface  INTERFACE_UUID("{CF35DA04-7A99-45CD-91FD-BB9A333043F3}") Jmessaging_ProxyFirebaseMessagingService  : public Androidapi::Jni::Firebase::JFirebaseMessagingService 
{
	HIDESBASE virtual void __cdecl onNewToken(Androidapi::Jni::Javatypes::_di_JString token) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJmessaging_ProxyFirebaseMessagingService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jmessaging_ProxyFirebaseMessagingServiceClass,_di_Jmessaging_ProxyFirebaseMessagingService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jmessaging_ProxyFirebaseMessagingServiceClass,_di_Jmessaging_ProxyFirebaseMessagingService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJmessaging_ProxyFirebaseMessagingService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jmessaging_ProxyFirebaseMessagingServiceClass,_di_Jmessaging_ProxyFirebaseMessagingService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJmessaging_ProxyFirebaseMessagingService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9DFD082F-580D-419B-8F42-3A26B0B34A21}") Jmessaging_PushNotificationListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{62F3E3DD-3DA9-4E88-81E6-FBAA8D909FB9}") Jmessaging_PushNotificationListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onNewTokenReceived(Androidapi::Jni::Javatypes::_di_JString token) = 0 ;
	virtual void __cdecl onNotificationReceived(Androidapi::Jni::Os::_di_JBundle notification) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJmessaging_PushNotificationListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jmessaging_PushNotificationListenerClass,_di_Jmessaging_PushNotificationListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jmessaging_PushNotificationListenerClass,_di_Jmessaging_PushNotificationListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJmessaging_PushNotificationListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jmessaging_PushNotificationListenerClass,_di_Jmessaging_PushNotificationListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJmessaging_PushNotificationListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Firebase */
}	/* namespace Embarcadero */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_EMBARCADERO_FIREBASE)
using namespace Androidapi::Jni::Embarcadero::Firebase;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_EMBARCADERO)
using namespace Androidapi::Jni::Embarcadero;
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
#endif	// Androidapi_Jni_Embarcadero_FirebaseHPP
