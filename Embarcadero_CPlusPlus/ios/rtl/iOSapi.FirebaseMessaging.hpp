// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.FirebaseMessaging.pas' rev: 34.00 (iOS)

#ifndef Iosapi_FirebasemessagingHPP
#define Iosapi_FirebasemessagingHPP

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
namespace Firebasemessaging
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE FIRMessagingMessageInfoClass;
typedef System::DelphiInterface<FIRMessagingMessageInfoClass> _di_FIRMessagingMessageInfoClass;
__interface DELPHIINTERFACE FIRMessagingMessageInfo;
typedef System::DelphiInterface<FIRMessagingMessageInfo> _di_FIRMessagingMessageInfo;
class DELPHICLASS TFIRMessagingMessageInfo;
__interface DELPHIINTERFACE FIRMessagingRemoteMessageClass;
typedef System::DelphiInterface<FIRMessagingRemoteMessageClass> _di_FIRMessagingRemoteMessageClass;
__interface DELPHIINTERFACE FIRMessagingRemoteMessage;
typedef System::DelphiInterface<FIRMessagingRemoteMessage> _di_FIRMessagingRemoteMessage;
class DELPHICLASS TFIRMessagingRemoteMessage;
__interface DELPHIINTERFACE FIRMessagingDelegate;
typedef System::DelphiInterface<FIRMessagingDelegate> _di_FIRMessagingDelegate;
__interface DELPHIINTERFACE FIRMessagingClass;
typedef System::DelphiInterface<FIRMessagingClass> _di_FIRMessagingClass;
__interface DELPHIINTERFACE FIRMessaging;
typedef System::DelphiInterface<FIRMessaging> _di_FIRMessaging;
class DELPHICLASS TFIRMessaging;
//-- type declarations -------------------------------------------------------
typedef long FIRInstanceIDAPNSTokenType;

typedef long FIRMessagingAPNSTokenType;

typedef unsigned long FIRMessagingError;

typedef long FIRMessagingMessageStatus;

typedef void __fastcall (__closure *TFIRMessagingConnectCompletion)(Iosapi::Foundation::_di_NSError error);

__interface  INTERFACE_UUID("{FDAC534F-3D79-4FF6-824E-50DC7423662A}") FIRMessagingMessageInfoClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4D70F5C5-3635-405F-895C-F41C8D1FD76B}") FIRMessagingMessageInfo  : public Iosapi::Foundation::NSObject 
{
	virtual long __cdecl status() = 0 ;
};

class PASCALIMPLEMENTATION TFIRMessagingMessageInfo : public Macapi::Objectivec::TOCGenericImport__2<_di_FIRMessagingMessageInfoClass,_di_FIRMessagingMessageInfo>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_FIRMessagingMessageInfoClass,_di_FIRMessagingMessageInfo> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TFIRMessagingMessageInfo(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_FIRMessagingMessageInfoClass,_di_FIRMessagingMessageInfo>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TFIRMessagingMessageInfo() { }
	
};


__interface  INTERFACE_UUID("{EF45D074-C7A5-4DB2-BCD1-53B8650419F4}") FIRMessagingRemoteMessageClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6E2F8E14-FD8D-4B5D-8026-A607BE0B8F9C}") FIRMessagingRemoteMessage  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl appData() = 0 ;
};

class PASCALIMPLEMENTATION TFIRMessagingRemoteMessage : public Macapi::Objectivec::TOCGenericImport__2<_di_FIRMessagingRemoteMessageClass,_di_FIRMessagingRemoteMessage>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_FIRMessagingRemoteMessageClass,_di_FIRMessagingRemoteMessage> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TFIRMessagingRemoteMessage(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_FIRMessagingRemoteMessageClass,_di_FIRMessagingRemoteMessage>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TFIRMessagingRemoteMessage() { }
	
};


__interface  INTERFACE_UUID("{264C1F0E-3EA9-42AC-9802-EF1BC9A7E321}") FIRMessagingDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl applicationReceivedRemoteMessage(_di_FIRMessagingRemoteMessage remoteMessage) = 0 ;
	virtual void __cdecl didReceiveMessage(_di_FIRMessaging messaging, _di_FIRMessagingRemoteMessage remoteMessage) = 0 ;
	virtual void __cdecl didRefreshRegistrationToken(_di_FIRMessaging messaging, Iosapi::Foundation::_di_NSString fcmToken) = 0 ;
	virtual void __cdecl didReceiveRegistrationToken(_di_FIRMessaging messaging, Iosapi::Foundation::_di_NSString fcmToken) = 0 ;
};

__interface  INTERFACE_UUID("{62AF9A4C-681E-4BCD-9063-6209CAE08296}") FIRMessagingClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl messaging() = 0 ;
};

__interface  INTERFACE_UUID("{A721C3D4-82EB-4A7B-A5E5-42EF9E8F618E}") FIRMessaging  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSData __cdecl APNSToken() = 0 ;
	virtual void __cdecl connectWithCompletion(TFIRMessagingConnectCompletion handler) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl disconnect() = 0 ;
	virtual void __cdecl sendMessage(Iosapi::Foundation::_di_NSDictionary msg, Iosapi::Foundation::_di_NSString receiver, Iosapi::Foundation::_di_NSString messageID, __int64 ttl) = 0 ;
	virtual void __cdecl setAPNSToken(Iosapi::Foundation::_di_NSData apnsToken, long tokenType) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual bool __cdecl shouldEstablishDirectChannel() = 0 ;
	virtual void __cdecl setShouldEstablishDirectChannel(bool value) = 0 ;
	virtual void __cdecl subscribeToTopic(Iosapi::Foundation::_di_NSString topic) = 0 ;
	virtual void __cdecl unsubscribeFromTopic(Iosapi::Foundation::_di_NSString topic) = 0 ;
};

class PASCALIMPLEMENTATION TFIRMessaging : public Macapi::Objectivec::TOCGenericImport__2<_di_FIRMessagingClass,_di_FIRMessaging>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_FIRMessagingClass,_di_FIRMessaging> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TFIRMessaging(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_FIRMessagingClass,_di_FIRMessaging>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TFIRMessaging() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 FIRMessagingErrorUnknown = System::Int8(0x0);
static constexpr System::Int8 FIRMessagingErrorAuthentication = System::Int8(0x1);
static constexpr System::Int8 FIRMessagingErrorNoAccess = System::Int8(0x2);
static constexpr System::Int8 FIRMessagingErrorTimeout = System::Int8(0x3);
static constexpr System::Int8 FIRMessagingErrorNetwork = System::Int8(0x4);
static constexpr System::Int8 FIRMessagingErrorOperationInProgress = System::Int8(0x5);
static constexpr System::Int8 FIRMessagingErrorInvalidRequest = System::Int8(0x7);
static constexpr System::Int8 FIRMessagingMessageStatusUnknown = System::Int8(0x0);
static constexpr System::Int8 FIRMessagingMessageStatusNew = System::Int8(0x1);
static constexpr System::Int8 FIRMessasingAPNSTokenTypeUnknown = System::Int8(0x0);
static constexpr System::Int8 FIRMessasingAPNSTokenTypeSandbox = System::Int8(0x1);
static constexpr System::Int8 FIRMessasingAPNSTokenTypeProd = System::Int8(0x2);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __cdecl kFIRInstanceIDTokenRefreshNotification(void);
}	/* namespace Firebasemessaging */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_FIREBASEMESSAGING)
using namespace Iosapi::Firebasemessaging;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_FirebasemessagingHPP
