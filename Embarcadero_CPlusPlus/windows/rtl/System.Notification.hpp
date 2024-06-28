// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Notification.pas' rev: 34.00 (Windows)

#ifndef System_NotificationHPP
#define System_NotificationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Messaging.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Notification
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TNotification;
class DELPHICLASS TChannel;
class DELPHICLASS ELocalNotification;
class DELPHICLASS ELocalNotificationAccess;
class DELPHICLASS TPermissionRequestResultMessage;
class DELPHICLASS TBaseNotificationCenter;
class DELPHICLASS TCustomNotificationCenter;
class DELPHICLASS TNotificationCenter;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TRepeatInterval : unsigned char { None, Second, Minute, Hour, Day, Week, Weekday, Month, Quarter, Year, Era };

class PASCALIMPLEMENTATION TNotification : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	System::UnicodeString Name;
	System::UnicodeString Title;
	System::UnicodeString AlertBody;
	System::UnicodeString AlertAction;
	int Number;
	System::TDateTime FireDate;
	bool EnableSound;
	System::UnicodeString SoundName;
	bool HasAction;
	TRepeatInterval RepeatInterval;
	System::UnicodeString ChannelId;
	__fastcall TNotification();
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TNotification() { }
	
};


enum class DECLSPEC_DENUM TLockscreenVisibility : unsigned char { Public, Private, Secret };

enum class DECLSPEC_DENUM TImportance : unsigned char { None, Default, Min, Low, High };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TChannel : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	System::UnicodeString Id;
	System::UnicodeString Title;
	System::UnicodeString Description;
	TLockscreenVisibility LockscreenVisibility;
	TImportance Importance;
	bool ShouldShowLights;
	bool ShouldVibrate;
	bool ShouldShowBadge;
	__fastcall TChannel();
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TChannel() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ELocalNotification : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ELocalNotification(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ELocalNotification(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ELocalNotification(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ELocalNotification(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ELocalNotification(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ELocalNotification(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ELocalNotification(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ELocalNotification(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELocalNotification(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELocalNotification(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELocalNotification(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELocalNotification(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ELocalNotification() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ELocalNotificationAccess : public ELocalNotification
{
	typedef ELocalNotification inherited;
	
public:
	/* Exception.Create */ inline __fastcall ELocalNotificationAccess(const System::UnicodeString Msg) : ELocalNotification(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ELocalNotificationAccess(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ELocalNotification(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ELocalNotificationAccess(NativeUInt Ident)/* overload */ : ELocalNotification(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ELocalNotificationAccess(System::PResStringRec ResStringRec)/* overload */ : ELocalNotification(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ELocalNotificationAccess(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ELocalNotification(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ELocalNotificationAccess(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ELocalNotification(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ELocalNotificationAccess(const System::UnicodeString Msg, int AHelpContext) : ELocalNotification(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ELocalNotificationAccess(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ELocalNotification(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELocalNotificationAccess(NativeUInt Ident, int AHelpContext)/* overload */ : ELocalNotification(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELocalNotificationAccess(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ELocalNotification(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELocalNotificationAccess(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ELocalNotification(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELocalNotificationAccess(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ELocalNotification(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ELocalNotificationAccess() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<TNotification*> TNotifications;

enum class DECLSPEC_DENUM TAuthorizationStatus : unsigned char { NotDetermined, Restricted, Denied, Authorized };

typedef void __fastcall (__closure *TOnReceiveLocalNotification)(System::TObject* Sender, TNotification* ANotification);

typedef void __fastcall (__closure *TOnPermissionRequestResult)(System::TObject* Sender, const bool AIsGranted);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPermissionRequestResultMessage : public System::Messaging::TMessage__1<bool>
{
	typedef System::Messaging::TMessage__1<bool> inherited;
	
public:
	/* {System_Messaging}TMessage<System_Boolean>.Create */ inline __fastcall TPermissionRequestResultMessage(const bool AValue) : System::Messaging::TMessage__1<bool>(AValue) { }
	/* {System_Messaging}TMessage<System_Boolean>.Destroy */ inline __fastcall virtual ~TPermissionRequestResultMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::Generics::Collections::TList__1<TChannel*>* TChannels;

class PASCALIMPLEMENTATION TBaseNotificationCenter : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TOnReceiveLocalNotification FOnReceiveLocalNotification;
	TOnPermissionRequestResult FOnPermissionRequestResult;
	static TBaseNotificationCenter* __fastcall InternalGetInstance();
	
protected:
	virtual __classmethod TBaseNotificationCenter* __fastcall GetInstance() = 0 ;
	virtual void __fastcall DoRequestPermission() = 0 ;
	virtual TAuthorizationStatus __fastcall DoAuthorizationStatus() = 0 ;
	virtual void __fastcall DoScheduleNotification(TNotification* const ANotification) = 0 ;
	virtual void __fastcall DoPresentNotification(TNotification* const ANotification) = 0 ;
	virtual void __fastcall DoCancelNotification(const System::UnicodeString AName) = 0 /* overload */;
	virtual void __fastcall DoCancelNotification(TNotification* const ANotification) = 0 /* overload */;
	virtual void __fastcall DoCancelAllNotifications() = 0 ;
	virtual void __fastcall DoCreateOrUpdateChannel(TChannel* const AChannel) = 0 ;
	virtual void __fastcall DoDeleteChannel(const System::UnicodeString AChannelId) = 0 ;
	virtual void __fastcall DoGetAllChannels(System::Generics::Collections::TList__1<TChannel*>* const AChannels) = 0 ;
	virtual void __fastcall DoSetIconBadgeNumber(const int ACount) = 0 ;
	virtual int __fastcall DoGetIconBadgeNumber() = 0 ;
	virtual void __fastcall DoResetIconBadgeNumber() = 0 ;
	virtual void __fastcall DoReceiveLocalNotification(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	virtual void __fastcall DoReceivePermissionRequestResult(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	virtual void __fastcall DoLoaded();
	void __fastcall NotifyPermissionRequestResult(const bool AIsGranted);
	
public:
	__fastcall TBaseNotificationCenter();
	__fastcall virtual ~TBaseNotificationCenter();
	void __fastcall RequestPermission();
	TAuthorizationStatus __fastcall AuthorizationStatus();
	TNotification* __fastcall CreateNotification()/* overload */;
	TNotification* __fastcall CreateNotification(const System::UnicodeString AName, const System::UnicodeString AAlertBody, const System::TDateTime AFireDate)/* overload */;
	void __fastcall PresentNotification(TNotification* const ANotification);
	void __fastcall ScheduleNotification(TNotification* const ANotification);
	void __fastcall CancelAll();
	void __fastcall CancelNotification(const System::UnicodeString AName);
	void __fastcall CreateOrUpdateChannel(TChannel* const AChannel);
	void __fastcall DeleteChannel(const System::UnicodeString AChannelId);
	void __fastcall GetAllChannels(System::Generics::Collections::TList__1<TChannel*>* const AChannels);
	__property int ApplicationIconBadgeNumber = {read=DoGetIconBadgeNumber, write=DoSetIconBadgeNumber, nodefault};
	__property TOnReceiveLocalNotification OnReceiveLocalNotification = {read=FOnReceiveLocalNotification, write=FOnReceiveLocalNotification};
	__property TOnPermissionRequestResult OnPermissionRequestResult = {read=FOnPermissionRequestResult, write=FOnPermissionRequestResult};
};


class PASCALIMPLEMENTATION TCustomNotificationCenter : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TBaseNotificationCenter* FPlatformNotificationCenter;
	TOnReceiveLocalNotification FOnReceiveLocalNotification;
	TOnPermissionRequestResult FOnPermissionRequestResult;
	
private:
	// __classmethod void __fastcall Create@();
	
protected:
	virtual void __fastcall DoRequestPermission();
	virtual TAuthorizationStatus __fastcall DoAuthorizationStatus();
	virtual void __fastcall DoScheduleNotification(TNotification* const ANotification);
	virtual void __fastcall DoPresentNotification(TNotification* const ANotification);
	virtual void __fastcall DoCancelNotification(const System::UnicodeString AName)/* overload */;
	virtual void __fastcall DoCancelNotification(TNotification* const ANotification)/* overload */;
	virtual void __fastcall DoCancelAllNotifications();
	virtual void __fastcall DoCreateOrUpdateChannel(TChannel* const AChannel);
	virtual void __fastcall DoDeleteChannel(const System::UnicodeString AChannelId);
	virtual void __fastcall DoGetAllChannels(System::Generics::Collections::TList__1<TChannel*>* const AChannels);
	virtual void __fastcall DoSetIconBadgeNumber(const int ACount);
	virtual int __fastcall DoGetIconBadgeNumber();
	virtual void __fastcall DoResetIconBadgeNumber();
	virtual void __fastcall DoReceiveLocalNotification(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	virtual void __fastcall DoReceivePermissionRequestResult(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	virtual void __fastcall DoLoaded();
	
public:
	__fastcall virtual TCustomNotificationCenter(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomNotificationCenter();
	virtual void __fastcall Loaded();
	bool __fastcall Supported();
	void __fastcall RequestPermission();
	TAuthorizationStatus __fastcall AuthorizationStatus();
	TNotification* __fastcall CreateNotification()/* overload */;
	TNotification* __fastcall CreateNotification(const System::UnicodeString AName, const System::UnicodeString AAlertBody, const System::TDateTime AFireDate)/* overload */;
	TChannel* __fastcall CreateChannel()/* overload */;
	TChannel* __fastcall CreateChannel(const System::UnicodeString AId, const System::UnicodeString ATitle, const System::UnicodeString ADescription = System::UnicodeString())/* overload */;
	void __fastcall PresentNotification(TNotification* const ANotification);
	void __fastcall ScheduleNotification(TNotification* const ANotification);
	void __fastcall CancelAll();
	void __fastcall CancelNotification(const System::UnicodeString AName);
	void __fastcall CreateOrUpdateChannel(TChannel* const AChannel);
	void __fastcall DeleteChannel(const System::UnicodeString AChannelId);
	void __fastcall GetAllChannels(System::Generics::Collections::TList__1<TChannel*>* const AChannels);
	__property int ApplicationIconBadgeNumber = {read=DoGetIconBadgeNumber, write=DoSetIconBadgeNumber, default=0};
	__property TOnReceiveLocalNotification OnReceiveLocalNotification = {read=FOnReceiveLocalNotification, write=FOnReceiveLocalNotification};
	__property TOnPermissionRequestResult OnPermissionRequestResult = {read=FOnPermissionRequestResult, write=FOnPermissionRequestResult};
	
private:
	// __classmethod void __fastcall Destroy@();
};


class PASCALIMPLEMENTATION TNotificationCenter : public TCustomNotificationCenter
{
	typedef TCustomNotificationCenter inherited;
	
__published:
	__property ApplicationIconBadgeNumber = {default=0};
	__property OnReceiveLocalNotification;
	__property OnPermissionRequestResult;
public:
	/* TCustomNotificationCenter.Create */ inline __fastcall virtual TNotificationCenter(System::Classes::TComponent* AOwner) : TCustomNotificationCenter(AOwner) { }
	/* TCustomNotificationCenter.Destroy */ inline __fastcall virtual ~TNotificationCenter() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Notification */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_NOTIFICATION)
using namespace System::Notification;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_NotificationHPP
