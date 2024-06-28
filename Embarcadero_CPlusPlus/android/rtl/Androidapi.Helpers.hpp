// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.Helpers.pas' rev: 34.00 (Android)

#ifndef Androidapi_HelpersHPP
#define Androidapi_HelpersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Messaging.hpp>
#include <System.SysUtils.hpp>
#include <System.UITypes.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Net.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Helpers
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidHelper;
class DELPHICLASS TMessageResultNotification;
struct TPermissionsRequestResultData;
class DELPHICLASS TPermissionsRequestResultMessage;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidHelper : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static Androidapi::Jni::Graphicscontentviewtext::_di_JContext FJContext;
	static Androidapi::Jni::App::_di_JActivity FJActivity;
	static Androidapi::Jni::App::_di_JAlarmManager FJAlarmManager;
	static Androidapi::Jni::Graphicscontentviewtext::_di_JDisplay FJDisplay;
	static Androidapi::Jni::Graphicscontentviewtext::_di_JContentResolver FJContentResolver;
	static Androidapi::Jni::Os::_di_JHandler FMainHandler;
	
private:
	// __classmethod void __fastcall Create_();
	
private:
	static Androidapi::Jni::Graphicscontentviewtext::_di_JSharedPreferences __fastcall GetPrivatePreferences();
	static Androidapi::Jni::App::_di_JActivity __fastcall GetJActivity();
	static System::UnicodeString __fastcall GetPackagePath();
	static System::UnicodeString __fastcall GetApplicationTitle();
	static Androidapi::Jni::Os::_di_JHandler __fastcall GetMainHandler();
	static bool __fastcall GetShouldNativeLibrariesBeExtracted();
	
public:
	static bool __fastcall HasSystemService(const Androidapi::Jni::Javatypes::_di_JString AFeatureName);
	static int __fastcall GetResourceID(const System::UnicodeString AResourceName)/* overload */;
	static int __fastcall GetResourceID(const System::UnicodeString AResourceName, const System::UnicodeString AResourceType)/* overload */;
	static System::UnicodeString __fastcall GetResourceString(int AResourceID);
	/* static */ __property Androidapi::Jni::Graphicscontentviewtext::_di_JContext Context = {read=FJContext};
	/* static */ __property Androidapi::Jni::Graphicscontentviewtext::_di_JContentResolver ContentResolver = {read=FJContentResolver};
	/* static */ __property Androidapi::Jni::App::_di_JActivity Activity = {read=GetJActivity};
	/* static */ __property System::UnicodeString ApplicationTitle = {read=GetApplicationTitle};
	/* static */ __property Androidapi::Jni::App::_di_JAlarmManager AlarmManager = {read=FJAlarmManager};
	/* static */ __property Androidapi::Jni::Graphicscontentviewtext::_di_JSharedPreferences PrivatePreferences = {read=GetPrivatePreferences};
	/* static */ __property System::UnicodeString PackagePath = {read=GetPackagePath};
	/* static */ __property Androidapi::Jni::Os::_di_JHandler MainHandler = {read=GetMainHandler};
	/* static */ __property bool ShouldNativeLibrariesBeExtracted = {read=GetShouldNativeLibrariesBeExtracted, nodefault};
	/* static */ __property Androidapi::Jni::Graphicscontentviewtext::_di_JDisplay Display = {read=FJDisplay};
	static Androidapi::Jni::Util::_di_JDisplayMetrics __fastcall DisplayMetrics();
	__classmethod void * __fastcall JObjectToID(const Androidapi::Jni::Javatypes::_di_JObject AObject);
	static Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __fastcall TBytesToTJavaArray(const System::TArray__1<System::Byte> ABytes);
	static System::TArray__1<System::Byte> __fastcall TJavaArrayToTBytes(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* const AJArray);
	static System::UnicodeString __fastcall JStringToString(const Androidapi::Jni::Javatypes::_di_JString JStr);
	static Androidapi::Jni::Javatypes::_di_JString __fastcall StringToJString(const System::UnicodeString Str);
	static Androidapi::Jni::Javatypes::_di_JCharSequence __fastcall StrToJCharSequence(const System::UnicodeString ASource);
	static System::UnicodeString __fastcall JCharSequenceToStr(const Androidapi::Jni::Javatypes::_di_JCharSequence ASource);
	static Androidapi::Jni::Net::_di_Jnet_Uri __fastcall StrToJURI(const System::UnicodeString ASource);
	static System::UnicodeString __fastcall JURIToStr(const Androidapi::Jni::Net::_di_Jnet_Uri ASource);
	static Androidapi::Jni::Net::_di_Jnet_Uri __fastcall JFileToJURI(const Androidapi::Jni::Javatypes::_di_JFile AFile);
	static int __fastcall AlphaColorToJColor(const System::Uitypes::TAlphaColor AColor);
	
private:
	// __classmethod void __fastcall Destroy_();
public:
	/* TObject.Create */ inline __fastcall TAndroidHelper() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAndroidHelper() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMessageResultNotification : public System::Messaging::TMessage__1<Androidapi::Jni::Graphicscontentviewtext::_di_JIntent>
{
	typedef System::Messaging::TMessage__1<Androidapi::Jni::Graphicscontentviewtext::_di_JIntent> inherited;
	
public:
	int RequestCode;
	int ResultCode;
public:
	/* {System_Messaging}TMessage<Androidapi_JNI_GraphicsContentViewText_JIntent>.Create */ inline __fastcall TMessageResultNotification(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AValue) : System::Messaging::TMessage__1<Androidapi::Jni::Graphicscontentviewtext::_di_JIntent>(AValue) { }
	/* {System_Messaging}TMessage<Androidapi_JNI_GraphicsContentViewText_JIntent>.Destroy */ inline __fastcall virtual ~TMessageResultNotification() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TPermissionsRequestResultData
{
public:
	int RequestCode;
	Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* Permissions;
	Androidapi::Jnibridge::TJavaArray__1<int>* GrantResults;
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPermissionsRequestResultMessage : public System::Messaging::TMessage__1<TPermissionsRequestResultData>
{
	typedef System::Messaging::TMessage__1<TPermissionsRequestResultData> inherited;
	
public:
	/* {System_Messaging}TMessage<Androidapi_Helpers_TPermissionsRequestResultData>.Create */ inline __fastcall TPermissionsRequestResultMessage(const TPermissionsRequestResultData &AValue) : System::Messaging::TMessage__1<TPermissionsRequestResultData>(AValue) { }
	/* {System_Messaging}TMessage<Androidapi_Helpers_TPermissionsRequestResultData>.Destroy */ inline __fastcall virtual ~TPermissionsRequestResultMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void * __fastcall JObjectToID _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.JObjectToID") (const Androidapi::Jni::Javatypes::_di_JObject AObject);
extern DELPHI_PACKAGE System::TArray__1<System::Byte> __fastcall TJavaArrayToTBytes(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* const AJArray);
extern DELPHI_PACKAGE Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __fastcall TBytesToTJavaArray(const System::TArray__1<System::Byte> ABytes);
extern DELPHI_PACKAGE Androidapi::Jni::Javatypes::_di_JLong __fastcall Int64ToJLong(const __int64 AValue);
extern DELPHI_PACKAGE System::UnicodeString __fastcall JStringToString(const Androidapi::Jni::Javatypes::_di_JString JStr);
extern DELPHI_PACKAGE Androidapi::Jni::Javatypes::_di_JString __fastcall StringToJString(const System::UnicodeString Str);
extern DELPHI_PACKAGE Androidapi::Jni::Javatypes::_di_JCharSequence __fastcall StrToJCharSequence(const System::UnicodeString ASource);
extern DELPHI_PACKAGE System::UnicodeString __fastcall JCharSequenceToStr(const Androidapi::Jni::Javatypes::_di_JCharSequence ASource);
extern DELPHI_PACKAGE Androidapi::Jni::Net::_di_Jnet_Uri __fastcall StrToJURI(const System::UnicodeString ASource);
extern DELPHI_PACKAGE System::UnicodeString __fastcall JURIToStr(const Androidapi::Jni::Net::_di_Jnet_Uri ASource);
extern DELPHI_PACKAGE Androidapi::Jni::Net::_di_Jnet_Uri __fastcall JFileToJURI(const Androidapi::Jni::Javatypes::_di_JFile AFile);
extern DELPHI_PACKAGE Androidapi::Jni::Graphicscontentviewtext::_di_JContext __fastcall SharedActivityContext _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.Context") (void);
extern DELPHI_PACKAGE Androidapi::Jni::App::_di_JActivity __fastcall SharedActivity _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.Activity") (void);
extern DELPHI_PACKAGE Androidapi::Jni::Graphicscontentviewtext::_di_JApplicationInfo __fastcall SharedApplicationInfo _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.Context.getApplicationInfo") (void);
extern DELPHI_PACKAGE Androidapi::Jni::App::_di_JAlarmManager __fastcall SharedAlarmManager _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.AlarmManager") (void);
extern DELPHI_PACKAGE Androidapi::Jni::Graphicscontentviewtext::_di_JSharedPreferences __fastcall SharedPrivatePreferences _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.PrivatePreferences") (void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetApplicationTitle _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.ApplicationTitle") (void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetPackagePath _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.PackagePath") (void);
extern DELPHI_PACKAGE bool __fastcall HasSystemService _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.HasSystemService") (const Androidapi::Jni::Javatypes::_di_JString AFeatureName);
extern DELPHI_PACKAGE int __fastcall GetResourceID _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.GetResourceID") (const System::UnicodeString ResourceName);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetResourceString _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.GetResourceString") (const int ResourceID);
extern DELPHI_PACKAGE Androidapi::Jni::Graphicscontentviewtext::_di_JDisplay __fastcall GetJDisplay _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.Display") (void);
extern DELPHI_PACKAGE Androidapi::Jni::Util::_di_JDisplayMetrics __fastcall GetJDisplayMetrics _DEPRECATED_ATTRIBUTE1("Use TAndroidHelper.DisplayMetrics") (void);
}	/* namespace Helpers */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_HELPERS)
using namespace Androidapi::Helpers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_HelpersHPP
