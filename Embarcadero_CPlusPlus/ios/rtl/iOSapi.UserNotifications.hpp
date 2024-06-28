// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.UserNotifications.pas' rev: 34.00 (iOS)

#ifndef Iosapi_UsernotificationsHPP
#define Iosapi_UsernotificationsHPP

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
#include <iOSapi.CoreLocation.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Usernotifications
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE UNNotificationClass;
typedef System::DelphiInterface<UNNotificationClass> _di_UNNotificationClass;
__interface DELPHIINTERFACE UNNotification;
typedef System::DelphiInterface<UNNotification> _di_UNNotification;
class DELPHICLASS TUNNotification;
__interface DELPHIINTERFACE UNNotificationActionClass;
typedef System::DelphiInterface<UNNotificationActionClass> _di_UNNotificationActionClass;
__interface DELPHIINTERFACE UNNotificationAction;
typedef System::DelphiInterface<UNNotificationAction> _di_UNNotificationAction;
class DELPHICLASS TUNNotificationAction;
__interface DELPHIINTERFACE UNTextInputNotificationActionClass;
typedef System::DelphiInterface<UNTextInputNotificationActionClass> _di_UNTextInputNotificationActionClass;
__interface DELPHIINTERFACE UNTextInputNotificationAction;
typedef System::DelphiInterface<UNTextInputNotificationAction> _di_UNTextInputNotificationAction;
class DELPHICLASS TUNTextInputNotificationAction;
__interface DELPHIINTERFACE UNNotificationAttachmentClass;
typedef System::DelphiInterface<UNNotificationAttachmentClass> _di_UNNotificationAttachmentClass;
__interface DELPHIINTERFACE UNNotificationAttachment;
typedef System::DelphiInterface<UNNotificationAttachment> _di_UNNotificationAttachment;
class DELPHICLASS TUNNotificationAttachment;
__interface DELPHIINTERFACE UNNotificationCategoryClass;
typedef System::DelphiInterface<UNNotificationCategoryClass> _di_UNNotificationCategoryClass;
__interface DELPHIINTERFACE UNNotificationCategory;
typedef System::DelphiInterface<UNNotificationCategory> _di_UNNotificationCategory;
class DELPHICLASS TUNNotificationCategory;
__interface DELPHIINTERFACE UNNotificationContentClass;
typedef System::DelphiInterface<UNNotificationContentClass> _di_UNNotificationContentClass;
__interface DELPHIINTERFACE UNNotificationContent;
typedef System::DelphiInterface<UNNotificationContent> _di_UNNotificationContent;
class DELPHICLASS TUNNotificationContent;
__interface DELPHIINTERFACE UNMutableNotificationContentClass;
typedef System::DelphiInterface<UNMutableNotificationContentClass> _di_UNMutableNotificationContentClass;
__interface DELPHIINTERFACE UNMutableNotificationContent;
typedef System::DelphiInterface<UNMutableNotificationContent> _di_UNMutableNotificationContent;
class DELPHICLASS TUNMutableNotificationContent;
__interface DELPHIINTERFACE UNNotificationRequestClass;
typedef System::DelphiInterface<UNNotificationRequestClass> _di_UNNotificationRequestClass;
__interface DELPHIINTERFACE UNNotificationRequest;
typedef System::DelphiInterface<UNNotificationRequest> _di_UNNotificationRequest;
class DELPHICLASS TUNNotificationRequest;
__interface DELPHIINTERFACE UNNotificationResponseClass;
typedef System::DelphiInterface<UNNotificationResponseClass> _di_UNNotificationResponseClass;
__interface DELPHIINTERFACE UNNotificationResponse;
typedef System::DelphiInterface<UNNotificationResponse> _di_UNNotificationResponse;
class DELPHICLASS TUNNotificationResponse;
__interface DELPHIINTERFACE UNTextInputNotificationResponseClass;
typedef System::DelphiInterface<UNTextInputNotificationResponseClass> _di_UNTextInputNotificationResponseClass;
__interface DELPHIINTERFACE UNTextInputNotificationResponse;
typedef System::DelphiInterface<UNTextInputNotificationResponse> _di_UNTextInputNotificationResponse;
class DELPHICLASS TUNTextInputNotificationResponse;
__interface DELPHIINTERFACE UNNotificationServiceExtensionClass;
typedef System::DelphiInterface<UNNotificationServiceExtensionClass> _di_UNNotificationServiceExtensionClass;
__interface DELPHIINTERFACE UNNotificationServiceExtension;
typedef System::DelphiInterface<UNNotificationServiceExtension> _di_UNNotificationServiceExtension;
class DELPHICLASS TUNNotificationServiceExtension;
__interface DELPHIINTERFACE UNNotificationSettingsClass;
typedef System::DelphiInterface<UNNotificationSettingsClass> _di_UNNotificationSettingsClass;
__interface DELPHIINTERFACE UNNotificationSettings;
typedef System::DelphiInterface<UNNotificationSettings> _di_UNNotificationSettings;
class DELPHICLASS TUNNotificationSettings;
__interface DELPHIINTERFACE UNNotificationSoundClass;
typedef System::DelphiInterface<UNNotificationSoundClass> _di_UNNotificationSoundClass;
__interface DELPHIINTERFACE UNNotificationSound;
typedef System::DelphiInterface<UNNotificationSound> _di_UNNotificationSound;
class DELPHICLASS TUNNotificationSound;
__interface DELPHIINTERFACE UNNotificationTriggerClass;
typedef System::DelphiInterface<UNNotificationTriggerClass> _di_UNNotificationTriggerClass;
__interface DELPHIINTERFACE UNNotificationTrigger;
typedef System::DelphiInterface<UNNotificationTrigger> _di_UNNotificationTrigger;
class DELPHICLASS TUNNotificationTrigger;
__interface DELPHIINTERFACE UNPushNotificationTriggerClass;
typedef System::DelphiInterface<UNPushNotificationTriggerClass> _di_UNPushNotificationTriggerClass;
__interface DELPHIINTERFACE UNPushNotificationTrigger;
typedef System::DelphiInterface<UNPushNotificationTrigger> _di_UNPushNotificationTrigger;
class DELPHICLASS TUNPushNotificationTrigger;
__interface DELPHIINTERFACE UNTimeIntervalNotificationTriggerClass;
typedef System::DelphiInterface<UNTimeIntervalNotificationTriggerClass> _di_UNTimeIntervalNotificationTriggerClass;
__interface DELPHIINTERFACE UNTimeIntervalNotificationTrigger;
typedef System::DelphiInterface<UNTimeIntervalNotificationTrigger> _di_UNTimeIntervalNotificationTrigger;
class DELPHICLASS TUNTimeIntervalNotificationTrigger;
__interface DELPHIINTERFACE UNCalendarNotificationTriggerClass;
typedef System::DelphiInterface<UNCalendarNotificationTriggerClass> _di_UNCalendarNotificationTriggerClass;
__interface DELPHIINTERFACE UNCalendarNotificationTrigger;
typedef System::DelphiInterface<UNCalendarNotificationTrigger> _di_UNCalendarNotificationTrigger;
class DELPHICLASS TUNCalendarNotificationTrigger;
__interface DELPHIINTERFACE UNLocationNotificationTriggerClass;
typedef System::DelphiInterface<UNLocationNotificationTriggerClass> _di_UNLocationNotificationTriggerClass;
__interface DELPHIINTERFACE UNLocationNotificationTrigger;
typedef System::DelphiInterface<UNLocationNotificationTrigger> _di_UNLocationNotificationTrigger;
class DELPHICLASS TUNLocationNotificationTrigger;
__interface DELPHIINTERFACE UNUserNotificationCenterClass;
typedef System::DelphiInterface<UNUserNotificationCenterClass> _di_UNUserNotificationCenterClass;
__interface DELPHIINTERFACE UNUserNotificationCenter;
typedef System::DelphiInterface<UNUserNotificationCenter> _di_UNUserNotificationCenter;
class DELPHICLASS TUNUserNotificationCenter;
__interface DELPHIINTERFACE UNUserNotificationCenterDelegate;
typedef System::DelphiInterface<UNUserNotificationCenterDelegate> _di_UNUserNotificationCenterDelegate;
//-- type declarations -------------------------------------------------------
typedef Iosapi::Foundation::_di_NSError *PNSError;

typedef long UNErrorCode;

typedef long UNNotificationActionOptions;

typedef long UNNotificationCategoryOptions;

typedef long UNAuthorizationStatus;

typedef long UNShowPreviewsSetting;

typedef long UNNotificationSetting;

typedef long UNAlertStyle;

typedef Iosapi::Foundation::_di_NSString UNNotificationSoundName;

typedef long UNAuthorizationOptions;

typedef long UNNotificationPresentationOptions;

typedef void __fastcall (__closure *TUNNotificationServiceExtensionBlockMethod1)(_di_UNNotificationContent contentToDeliver);

typedef void __fastcall (__closure *TUNUserNotificationCenterBlockMethod1)(bool granted, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *TUNUserNotificationCenterBlockMethod2)(Iosapi::Foundation::_di_NSSet categories);

typedef void __fastcall (__closure *TUNUserNotificationCenterBlockMethod3)(_di_UNNotificationSettings settings);

typedef void __fastcall (__closure *TUNUserNotificationCenterBlockMethod4)(Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *TUNUserNotificationCenterBlockMethod5)(Iosapi::Foundation::_di_NSArray requests);

typedef void __fastcall (__closure *TUNUserNotificationCenterBlockMethod6)(Iosapi::Foundation::_di_NSArray notifications);

typedef void __fastcall (__closure *TUNUserNotificationCenterDelegateBlockMethod1)(long options);

typedef void __fastcall (__closure *TUNUserNotificationCenterDelegateBlockMethod2)(void);

__interface  INTERFACE_UUID("{6D4428D5-18A3-4913-AD3D-99398B6A89CB}") UNNotificationClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{AFEE6151-57D2-4811-B5E8-3CDF1DDFBE57}") UNNotification  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDate __cdecl date() = 0 ;
	virtual _di_UNNotificationRequest __cdecl request() = 0 ;
};

class PASCALIMPLEMENTATION TUNNotification : public Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationClass,_di_UNNotification>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationClass,_di_UNNotification> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNNotification(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationClass,_di_UNNotification>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNNotification() { }
	
};


__interface  INTERFACE_UUID("{3A506339-56AB-4579-A1B2-F08E7A2D6C9A}") UNNotificationActionClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_UNNotificationAction __cdecl actionWithIdentifier(Iosapi::Foundation::_di_NSString identifier, Iosapi::Foundation::_di_NSString title, long options) = 0 ;
};

__interface  INTERFACE_UUID("{5B3E600A-3DB8-4257-9397-A2590D0B134D}") UNNotificationAction  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl identifier() = 0 ;
	virtual long __cdecl options() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
};

class PASCALIMPLEMENTATION TUNNotificationAction : public Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationActionClass,_di_UNNotificationAction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationActionClass,_di_UNNotificationAction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNNotificationAction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationActionClass,_di_UNNotificationAction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNNotificationAction() { }
	
};


__interface  INTERFACE_UUID("{41186088-9940-4F9B-A0AB-7F9C64417876}") UNTextInputNotificationActionClass  : public UNNotificationActionClass 
{
	HIDESBASE virtual _di_UNTextInputNotificationAction __cdecl actionWithIdentifier(Iosapi::Foundation::_di_NSString identifier, Iosapi::Foundation::_di_NSString title, long options, Iosapi::Foundation::_di_NSString textInputButtonTitle, Iosapi::Foundation::_di_NSString textInputPlaceholder) = 0 ;
};

__interface  INTERFACE_UUID("{CEF16097-1AA7-4853-9BDB-644840CF0003}") UNTextInputNotificationAction  : public UNNotificationAction 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl textInputButtonTitle() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl textInputPlaceholder() = 0 ;
};

class PASCALIMPLEMENTATION TUNTextInputNotificationAction : public Macapi::Objectivec::TOCGenericImport__2<_di_UNTextInputNotificationActionClass,_di_UNTextInputNotificationAction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNTextInputNotificationActionClass,_di_UNTextInputNotificationAction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNTextInputNotificationAction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNTextInputNotificationActionClass,_di_UNTextInputNotificationAction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNTextInputNotificationAction() { }
	
};


__interface  INTERFACE_UUID("{F4099CB1-FB60-46EA-BB24-AF96292EEA45}") UNNotificationAttachmentClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_UNNotificationAttachment __cdecl attachmentWithIdentifier(Iosapi::Foundation::_di_NSString identifier, Iosapi::Foundation::_di_NSURL URL, Iosapi::Foundation::_di_NSDictionary options, PNSError error) = 0 ;
};

__interface  INTERFACE_UUID("{89AABA8D-7E0C-4FA0-806E-0CC1341166D3}") UNNotificationAttachment  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl type() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl identifier() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl URL() = 0 ;
};

class PASCALIMPLEMENTATION TUNNotificationAttachment : public Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationAttachmentClass,_di_UNNotificationAttachment>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationAttachmentClass,_di_UNNotificationAttachment> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNNotificationAttachment(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationAttachmentClass,_di_UNNotificationAttachment>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNNotificationAttachment() { }
	
};


__interface  INTERFACE_UUID("{34B7ADD9-3404-436E-82C5-47E368E6DC17}") UNNotificationCategoryClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_UNNotificationCategory __cdecl categoryWithIdentifier(Iosapi::Foundation::_di_NSString identifier, Iosapi::Foundation::_di_NSArray actions, Iosapi::Foundation::_di_NSArray intentIdentifiers, Iosapi::Foundation::_di_NSString hiddenPreviewsBodyPlaceholder, Iosapi::Foundation::_di_NSString categorySummaryFormat, long options) = 0 /* overload */;
	virtual _di_UNNotificationCategory __cdecl categoryWithIdentifier(Iosapi::Foundation::_di_NSString identifier, Iosapi::Foundation::_di_NSArray actions, Iosapi::Foundation::_di_NSArray intentIdentifiers, Iosapi::Foundation::_di_NSString hiddenPreviewsBodyPlaceholder, long options) = 0 /* overload */;
	virtual _di_UNNotificationCategory __cdecl categoryWithIdentifier(Iosapi::Foundation::_di_NSString identifier, Iosapi::Foundation::_di_NSArray actions, Iosapi::Foundation::_di_NSArray intentIdentifiers, long options) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{26B3E2D1-4E43-42CF-8AB3-344E2455D75F}") UNNotificationCategory  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl actions() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl categorySummaryFormat() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl hiddenPreviewsBodyPlaceholder() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl identifier() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl intentIdentifiers() = 0 ;
	virtual long __cdecl options() = 0 ;
};

class PASCALIMPLEMENTATION TUNNotificationCategory : public Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationCategoryClass,_di_UNNotificationCategory>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationCategoryClass,_di_UNNotificationCategory> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNNotificationCategory(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationCategoryClass,_di_UNNotificationCategory>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNNotificationCategory() { }
	
};


__interface  INTERFACE_UUID("{51114586-06DF-4F81-89EE-A596F73F170A}") UNNotificationContentClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{BDF46729-F7A4-4780-8699-424E5A342426}") UNNotificationContent  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl attachments() = 0 ;
	virtual Iosapi::Foundation::_di_NSNumber __cdecl badge() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl body() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl categoryIdentifier() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl launchImageName() = 0 ;
	virtual _di_UNNotificationSound __cdecl sound() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl subtitle() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl summaryArgument() = 0 ;
	virtual unsigned long __cdecl summaryArgumentCount() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl threadIdentifier() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl userInfo() = 0 ;
};

class PASCALIMPLEMENTATION TUNNotificationContent : public Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationContentClass,_di_UNNotificationContent>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationContentClass,_di_UNNotificationContent> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNNotificationContent(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationContentClass,_di_UNNotificationContent>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNNotificationContent() { }
	
};


__interface  INTERFACE_UUID("{D9F80BFC-AE7B-4186-9FC7-63FF96694C99}") UNMutableNotificationContentClass  : public UNNotificationContentClass 
{
	
};

__interface  INTERFACE_UUID("{C97A9AB7-D2BE-479C-A737-B12B05B35496}") UNMutableNotificationContent  : public UNNotificationContent 
{
	HIDESBASE virtual Iosapi::Foundation::_di_NSArray __cdecl attachments() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSNumber __cdecl badge() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl body() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl categoryIdentifier() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl launchImageName() = 0 ;
	virtual void __cdecl setAttachments(Iosapi::Foundation::_di_NSArray attachments) = 0 ;
	virtual void __cdecl setBadge(Iosapi::Foundation::_di_NSNumber badge) = 0 ;
	virtual void __cdecl setBody(Iosapi::Foundation::_di_NSString body) = 0 ;
	virtual void __cdecl setCategoryIdentifier(Iosapi::Foundation::_di_NSString categoryIdentifier) = 0 ;
	virtual void __cdecl setLaunchImageName(Iosapi::Foundation::_di_NSString launchImageName) = 0 ;
	virtual void __cdecl setSound(_di_UNNotificationSound sound) = 0 ;
	virtual void __cdecl setSubtitle(Iosapi::Foundation::_di_NSString subtitle) = 0 ;
	virtual void __cdecl setSummaryArgument(Iosapi::Foundation::_di_NSString summaryArgument) = 0 ;
	virtual void __cdecl setSummaryArgumentCount(unsigned long summaryArgumentCount) = 0 ;
	virtual void __cdecl setThreadIdentifier(Iosapi::Foundation::_di_NSString threadIdentifier) = 0 ;
	virtual void __cdecl setTitle(Iosapi::Foundation::_di_NSString title) = 0 ;
	virtual void __cdecl setUserInfo(Iosapi::Foundation::_di_NSDictionary userInfo) = 0 ;
	HIDESBASE virtual _di_UNNotificationSound __cdecl sound() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl subtitle() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl summaryArgument() = 0 ;
	HIDESBASE virtual unsigned long __cdecl summaryArgumentCount() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl threadIdentifier() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl title() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSDictionary __cdecl userInfo() = 0 ;
};

class PASCALIMPLEMENTATION TUNMutableNotificationContent : public Macapi::Objectivec::TOCGenericImport__2<_di_UNMutableNotificationContentClass,_di_UNMutableNotificationContent>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNMutableNotificationContentClass,_di_UNMutableNotificationContent> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNMutableNotificationContent(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNMutableNotificationContentClass,_di_UNMutableNotificationContent>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNMutableNotificationContent() { }
	
};


__interface  INTERFACE_UUID("{85DD088D-EECD-4F62-B4D4-A77297CB8C68}") UNNotificationRequestClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_UNNotificationRequest __cdecl requestWithIdentifier(Iosapi::Foundation::_di_NSString identifier, _di_UNNotificationContent content, _di_UNNotificationTrigger trigger) = 0 ;
};

__interface  INTERFACE_UUID("{77D79B65-2B67-4255-B40E-7E98F2C91D8C}") UNNotificationRequest  : public Iosapi::Foundation::NSObject 
{
	virtual _di_UNNotificationContent __cdecl content() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl identifier() = 0 ;
	virtual _di_UNNotificationTrigger __cdecl trigger() = 0 ;
};

class PASCALIMPLEMENTATION TUNNotificationRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationRequestClass,_di_UNNotificationRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationRequestClass,_di_UNNotificationRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNNotificationRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationRequestClass,_di_UNNotificationRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNNotificationRequest() { }
	
};


__interface  INTERFACE_UUID("{822F3160-ED9B-401A-B770-ED0E745C67A9}") UNNotificationResponseClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{12B346C3-E55B-4A93-81D3-01699EBAEA43}") UNNotificationResponse  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl actionIdentifier() = 0 ;
	virtual _di_UNNotification __cdecl notification() = 0 ;
};

class PASCALIMPLEMENTATION TUNNotificationResponse : public Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationResponseClass,_di_UNNotificationResponse>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationResponseClass,_di_UNNotificationResponse> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNNotificationResponse(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationResponseClass,_di_UNNotificationResponse>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNNotificationResponse() { }
	
};


__interface  INTERFACE_UUID("{860727E8-2CB8-4A3F-83AD-27D5D4F1F8F7}") UNTextInputNotificationResponseClass  : public UNNotificationResponseClass 
{
	
};

__interface  INTERFACE_UUID("{C2869DC8-9C1D-4D23-93D0-8D869827AB5D}") UNTextInputNotificationResponse  : public UNNotificationResponse 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl userText() = 0 ;
};

class PASCALIMPLEMENTATION TUNTextInputNotificationResponse : public Macapi::Objectivec::TOCGenericImport__2<_di_UNTextInputNotificationResponseClass,_di_UNTextInputNotificationResponse>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNTextInputNotificationResponseClass,_di_UNTextInputNotificationResponse> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNTextInputNotificationResponse(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNTextInputNotificationResponseClass,_di_UNTextInputNotificationResponse>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNTextInputNotificationResponse() { }
	
};


__interface  INTERFACE_UUID("{6554C320-B0B0-4927-A011-1BA871C24140}") UNNotificationServiceExtensionClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{16B231C8-D680-4943-95C3-8941E7E01A78}") UNNotificationServiceExtension  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl didReceiveNotificationRequest(_di_UNNotificationRequest request, TUNNotificationServiceExtensionBlockMethod1 contentHandler) = 0 ;
	virtual void __cdecl serviceExtensionTimeWillExpire() = 0 ;
};

class PASCALIMPLEMENTATION TUNNotificationServiceExtension : public Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationServiceExtensionClass,_di_UNNotificationServiceExtension>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationServiceExtensionClass,_di_UNNotificationServiceExtension> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNNotificationServiceExtension(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationServiceExtensionClass,_di_UNNotificationServiceExtension>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNNotificationServiceExtension() { }
	
};


__interface  INTERFACE_UUID("{F6CC36AB-6F7D-4F0D-AA01-F604086FD698}") UNNotificationSettingsClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{98352662-F2B4-443A-83C3-F839AD9FFADC}") UNNotificationSettings  : public Iosapi::Foundation::NSObject 
{
	virtual long __cdecl alertSetting() = 0 ;
	virtual long __cdecl alertStyle() = 0 ;
	virtual long __cdecl authorizationStatus() = 0 ;
	virtual long __cdecl badgeSetting() = 0 ;
	virtual long __cdecl carPlaySetting() = 0 ;
	virtual long __cdecl criticalAlertSetting() = 0 ;
	virtual long __cdecl lockScreenSetting() = 0 ;
	virtual long __cdecl notificationCenterSetting() = 0 ;
	virtual bool __cdecl providesAppNotificationSettings() = 0 ;
	virtual long __cdecl showPreviewsSetting() = 0 ;
	virtual long __cdecl soundSetting() = 0 ;
};

class PASCALIMPLEMENTATION TUNNotificationSettings : public Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationSettingsClass,_di_UNNotificationSettings>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationSettingsClass,_di_UNNotificationSettings> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNNotificationSettings(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationSettingsClass,_di_UNNotificationSettings>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNNotificationSettings() { }
	
};


__interface  INTERFACE_UUID("{DE409993-FA94-4455-B5E1-E19B9999BD00}") UNNotificationSoundClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_UNNotificationSound __cdecl criticalSoundNamed(Iosapi::Foundation::_di_NSString name, float volume) = 0 /* overload */;
	virtual _di_UNNotificationSound __cdecl criticalSoundNamed(Iosapi::Foundation::_di_NSString name) = 0 /* overload */;
	virtual _di_UNNotificationSound __cdecl defaultCriticalSound() = 0 ;
	virtual _di_UNNotificationSound __cdecl defaultCriticalSoundWithAudioVolume(float volume) = 0 ;
	virtual _di_UNNotificationSound __cdecl defaultSound() = 0 ;
	virtual _di_UNNotificationSound __cdecl soundNamed(Iosapi::Foundation::_di_NSString name) = 0 ;
};

__interface  INTERFACE_UUID("{8C29C92A-EE23-423F-8F97-38735D4E2544}") UNNotificationSound  : public Iosapi::Foundation::NSObject 
{
	
};

class PASCALIMPLEMENTATION TUNNotificationSound : public Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationSoundClass,_di_UNNotificationSound>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationSoundClass,_di_UNNotificationSound> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNNotificationSound(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationSoundClass,_di_UNNotificationSound>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNNotificationSound() { }
	
};


__interface  INTERFACE_UUID("{209BB768-F422-478F-AC5F-F2EB4856F30C}") UNNotificationTriggerClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{274B049C-A4B1-4BB2-BD89-57DB452C626A}") UNNotificationTrigger  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl repeats() = 0 ;
};

class PASCALIMPLEMENTATION TUNNotificationTrigger : public Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationTriggerClass,_di_UNNotificationTrigger>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationTriggerClass,_di_UNNotificationTrigger> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNNotificationTrigger(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNNotificationTriggerClass,_di_UNNotificationTrigger>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNNotificationTrigger() { }
	
};


__interface  INTERFACE_UUID("{73252166-B928-4E81-A6DE-C0F7E22B93FF}") UNPushNotificationTriggerClass  : public UNNotificationTriggerClass 
{
	
};

__interface  INTERFACE_UUID("{D5E464F5-4FEC-4A26-BE0B-1643B92408BA}") UNPushNotificationTrigger  : public UNNotificationTrigger 
{
	
};

class PASCALIMPLEMENTATION TUNPushNotificationTrigger : public Macapi::Objectivec::TOCGenericImport__2<_di_UNPushNotificationTriggerClass,_di_UNPushNotificationTrigger>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNPushNotificationTriggerClass,_di_UNPushNotificationTrigger> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNPushNotificationTrigger(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNPushNotificationTriggerClass,_di_UNPushNotificationTrigger>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNPushNotificationTrigger() { }
	
};


__interface  INTERFACE_UUID("{65B02DB4-95F6-436E-9DE1-DDE82B8B4E9B}") UNTimeIntervalNotificationTriggerClass  : public UNNotificationTriggerClass 
{
	virtual _di_UNTimeIntervalNotificationTrigger __cdecl triggerWithTimeInterval(double timeInterval, bool repeats) = 0 ;
};

__interface  INTERFACE_UUID("{52D4250D-9E69-468B-B73C-840099D60361}") UNTimeIntervalNotificationTrigger  : public UNNotificationTrigger 
{
	virtual Iosapi::Foundation::_di_NSDate __cdecl nextTriggerDate() = 0 ;
	virtual double __cdecl timeInterval() = 0 ;
};

class PASCALIMPLEMENTATION TUNTimeIntervalNotificationTrigger : public Macapi::Objectivec::TOCGenericImport__2<_di_UNTimeIntervalNotificationTriggerClass,_di_UNTimeIntervalNotificationTrigger>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNTimeIntervalNotificationTriggerClass,_di_UNTimeIntervalNotificationTrigger> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNTimeIntervalNotificationTrigger(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNTimeIntervalNotificationTriggerClass,_di_UNTimeIntervalNotificationTrigger>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNTimeIntervalNotificationTrigger() { }
	
};


__interface  INTERFACE_UUID("{0D70BDA0-5C5C-412D-98A2-80CBBC21AABB}") UNCalendarNotificationTriggerClass  : public UNNotificationTriggerClass 
{
	virtual _di_UNCalendarNotificationTrigger __cdecl triggerWithDateMatchingComponents(Iosapi::Foundation::_di_NSDateComponents dateComponents, bool repeats) = 0 ;
};

__interface  INTERFACE_UUID("{59EDD126-D15F-40D9-B632-A249AE77E127}") UNCalendarNotificationTrigger  : public UNNotificationTrigger 
{
	virtual Iosapi::Foundation::_di_NSDateComponents __cdecl dateComponents() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl nextTriggerDate() = 0 ;
};

class PASCALIMPLEMENTATION TUNCalendarNotificationTrigger : public Macapi::Objectivec::TOCGenericImport__2<_di_UNCalendarNotificationTriggerClass,_di_UNCalendarNotificationTrigger>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNCalendarNotificationTriggerClass,_di_UNCalendarNotificationTrigger> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNCalendarNotificationTrigger(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNCalendarNotificationTriggerClass,_di_UNCalendarNotificationTrigger>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNCalendarNotificationTrigger() { }
	
};


__interface  INTERFACE_UUID("{E90E4004-1202-45BF-B20C-3BEDA4AA43F8}") UNLocationNotificationTriggerClass  : public UNNotificationTriggerClass 
{
	virtual _di_UNLocationNotificationTrigger __cdecl triggerWithRegion(Iosapi::Corelocation::_di_CLRegion region, bool repeats) = 0 ;
};

__interface  INTERFACE_UUID("{DDDAB13D-5499-41A6-BCFC-5A90D65FB4DF}") UNLocationNotificationTrigger  : public UNNotificationTrigger 
{
	virtual Iosapi::Corelocation::_di_CLRegion __cdecl region() = 0 ;
};

class PASCALIMPLEMENTATION TUNLocationNotificationTrigger : public Macapi::Objectivec::TOCGenericImport__2<_di_UNLocationNotificationTriggerClass,_di_UNLocationNotificationTrigger>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNLocationNotificationTriggerClass,_di_UNLocationNotificationTrigger> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNLocationNotificationTrigger(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNLocationNotificationTriggerClass,_di_UNLocationNotificationTrigger>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNLocationNotificationTrigger() { }
	
};


__interface  INTERFACE_UUID("{499732CA-F14F-4A91-82F9-903E1B0C125C}") UNUserNotificationCenterClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_UNUserNotificationCenter __cdecl currentNotificationCenter() = 0 ;
};

__interface  INTERFACE_UUID("{23C1DA35-7D1A-483F-ACE5-872CA4068EFF}") UNUserNotificationCenter  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl addNotificationRequest(_di_UNNotificationRequest request, TUNUserNotificationCenterBlockMethod4 completionHandler) = 0 ;
	virtual _di_UNUserNotificationCenterDelegate __cdecl delegate() = 0 ;
	virtual void __cdecl getDeliveredNotificationsWithCompletionHandler(TUNUserNotificationCenterBlockMethod6 completionHandler) = 0 ;
	virtual void __cdecl getNotificationCategoriesWithCompletionHandler(TUNUserNotificationCenterBlockMethod2 completionHandler) = 0 ;
	virtual void __cdecl getNotificationSettingsWithCompletionHandler(TUNUserNotificationCenterBlockMethod3 completionHandler) = 0 ;
	virtual void __cdecl getPendingNotificationRequestsWithCompletionHandler(TUNUserNotificationCenterBlockMethod5 completionHandler) = 0 ;
	virtual void __cdecl removeAllDeliveredNotifications() = 0 ;
	virtual void __cdecl removeAllPendingNotificationRequests() = 0 ;
	virtual void __cdecl removeDeliveredNotificationsWithIdentifiers(Iosapi::Foundation::_di_NSArray identifiers) = 0 ;
	virtual void __cdecl removePendingNotificationRequestsWithIdentifiers(Iosapi::Foundation::_di_NSArray identifiers) = 0 ;
	virtual void __cdecl requestAuthorizationWithOptions(long options, TUNUserNotificationCenterBlockMethod1 completionHandler) = 0 ;
	virtual void __cdecl setDelegate(_di_UNUserNotificationCenterDelegate delegate) = 0 ;
	virtual void __cdecl setNotificationCategories(Iosapi::Foundation::_di_NSSet categories) = 0 ;
	virtual bool __cdecl supportsContentExtensions() = 0 ;
};

class PASCALIMPLEMENTATION TUNUserNotificationCenter : public Macapi::Objectivec::TOCGenericImport__2<_di_UNUserNotificationCenterClass,_di_UNUserNotificationCenter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_UNUserNotificationCenterClass,_di_UNUserNotificationCenter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TUNUserNotificationCenter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_UNUserNotificationCenterClass,_di_UNUserNotificationCenter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TUNUserNotificationCenter() { }
	
};


__interface  INTERFACE_UUID("{07BBABF7-BB08-44A7-A654-37D3EEE16DA9}") UNUserNotificationCenterDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl userNotificationCenter(_di_UNUserNotificationCenter center, _di_UNNotification notification) = 0 /* overload */;
	virtual void __cdecl userNotificationCenter(_di_UNUserNotificationCenter center, _di_UNNotificationResponse response, void * completionHandler) = 0 /* overload */;
	virtual void __cdecl userNotificationCenter(_di_UNUserNotificationCenter center, _di_UNNotification notification, void * completionHandler) = 0 /* overload */;
};

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 UNErrorCodeNotificationsNotAllowed = System::Int8(0x1);
static constexpr System::Int8 UNErrorCodeAttachmentInvalidURL = System::Int8(0x64);
static constexpr System::Int8 UNErrorCodeAttachmentUnrecognizedType = System::Int8(0x65);
static constexpr System::Int8 UNErrorCodeAttachmentInvalidFileSize = System::Int8(0x66);
static constexpr System::Int8 UNErrorCodeAttachmentNotInDataStore = System::Int8(0x67);
static constexpr System::Int8 UNErrorCodeAttachmentMoveIntoDataStoreFailed = System::Int8(0x68);
static constexpr System::Int8 UNErrorCodeAttachmentCorrupt = System::Int8(0x69);
static constexpr System::Word UNErrorCodeNotificationInvalidNoDate = System::Word(0x578);
static constexpr System::Word UNErrorCodeNotificationInvalidNoContent = System::Word(0x579);
static constexpr System::Int8 UNNotificationActionOptionAuthenticationRequired = System::Int8(0x1);
static constexpr System::Int8 UNNotificationActionOptionDestructive = System::Int8(0x2);
static constexpr System::Int8 UNNotificationActionOptionForeground = System::Int8(0x4);
static constexpr System::Int8 UNNotificationCategoryOptionCustomDismissAction = System::Int8(0x1);
static constexpr System::Int8 UNNotificationCategoryOptionAllowInCarPlay = System::Int8(0x2);
static constexpr System::Int8 UNNotificationCategoryOptionHiddenPreviewsShowTitle = System::Int8(0x4);
static constexpr System::Int8 UNNotificationCategoryOptionHiddenPreviewsShowSubtitle = System::Int8(0x8);
static constexpr System::Int8 UNAuthorizationStatusNotDetermined = System::Int8(0x0);
static constexpr System::Int8 UNAuthorizationStatusDenied = System::Int8(0x1);
static constexpr System::Int8 UNAuthorizationStatusAuthorized = System::Int8(0x2);
static constexpr System::Int8 UNAuthorizationStatusProvisional = System::Int8(0x3);
static constexpr System::Int8 UNShowPreviewsSettingAlways = System::Int8(0x0);
static constexpr System::Int8 UNShowPreviewsSettingWhenAuthenticated = System::Int8(0x1);
static constexpr System::Int8 UNShowPreviewsSettingNever = System::Int8(0x2);
static constexpr System::Int8 UNNotificationSettingNotSupported = System::Int8(0x0);
static constexpr System::Int8 UNNotificationSettingDisabled = System::Int8(0x1);
static constexpr System::Int8 UNNotificationSettingEnabled = System::Int8(0x2);
static constexpr System::Int8 UNAlertStyleNone = System::Int8(0x0);
static constexpr System::Int8 UNAlertStyleBanner = System::Int8(0x1);
static constexpr System::Int8 UNAlertStyleAlert = System::Int8(0x2);
static constexpr System::Int8 UNAuthorizationOptionBadge = System::Int8(0x1);
static constexpr System::Int8 UNAuthorizationOptionSound = System::Int8(0x2);
static constexpr System::Int8 UNAuthorizationOptionAlert = System::Int8(0x4);
static constexpr System::Int8 UNAuthorizationOptionCarPlay = System::Int8(0x8);
static constexpr System::Int8 UNAuthorizationOptionCriticalAlert = System::Int8(0x10);
static constexpr System::Int8 UNAuthorizationOptionProvidesAppNotificationSettings = System::Int8(0x20);
static constexpr System::Int8 UNAuthorizationOptionProvisional = System::Int8(0x40);
static constexpr System::Int8 UNNotificationPresentationOptionBadge = System::Int8(0x1);
static constexpr System::Int8 UNNotificationPresentationOptionSound = System::Int8(0x2);
static constexpr System::Int8 UNNotificationPresentationOptionAlert = System::Int8(0x4);
#define libUserNotifications u"/System/Library/Frameworks/UserNotifications.framework/Use"\
	u"rNotifications"
}	/* namespace Usernotifications */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_USERNOTIFICATIONS)
using namespace Iosapi::Usernotifications;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_UsernotificationsHPP
