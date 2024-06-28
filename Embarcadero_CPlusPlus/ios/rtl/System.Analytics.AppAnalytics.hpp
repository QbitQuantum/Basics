// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Analytics.AppAnalytics.pas' rev: 34.00 (iOS)

#ifndef System_Analytics_AppanalyticsHPP
#define System_Analytics_AppanalyticsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Math.hpp>
#include <System.Analytics.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Analytics
{
namespace Appanalytics
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAppAnalyticsListener;
class DELPHICLASS TAppAnalyticsCacheManager;
class DELPHICLASS TCustomEventContext;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAppAnalyticsListener : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Analytics::TAppActivityOptions FOptions;
	System::UnicodeString FAppVersion;
	System::Analytics::_di_IApplicationActivityCacheManager FCacheManager;
	System::UnicodeString FPreviousControlClassname;
	System::UnicodeString FPreviousControlName;
	System::UnicodeString FPreviousFormClassname;
	System::UnicodeString FPreviousFormName;
	void __fastcall TrackAppStart(const System::TDateTime TimeStamp);
	void __fastcall TrackAppExit(const System::TDateTime TimeStamp);
	void __fastcall TrackControlFocused(const System::TDateTime TimeStamp, System::TObject* const Sender);
	void __fastcall TrackWindowActivated(const System::TDateTime TimeStamp, System::TObject* const Sender);
	void __fastcall TrackEvent(const System::TDateTime TimeStamp, System::TObject* const Sender, System::TObject* const Context);
	void __fastcall TrackException(const System::TDateTime TimeStamp, System::Sysutils::Exception* const E);
	void __fastcall SetOptions(const System::Analytics::TAppActivityOptions Value);
	System::UnicodeString __fastcall GetTimestamp();
	
public:
	__fastcall TAppAnalyticsListener(const System::Analytics::_di_IApplicationActivityCacheManager CacheManager, const System::UnicodeString AppVersion, const System::Analytics::TAppActivityOptions Options);
	__property System::Analytics::TAppActivityOptions Options = {read=FOptions, write=SetOptions, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAppAnalyticsListener() { }
	
private:
	void *__IApplicationActivityListener;	// System::Analytics::IApplicationActivityListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A67DE237-F274-4028-AAC8-DA0BDA0D5D78}
	operator System::Analytics::_di_IApplicationActivityListener()
	{
		System::Analytics::_di_IApplicationActivityListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Analytics::IApplicationActivityListener*(void) { return (System::Analytics::IApplicationActivityListener*)&__IApplicationActivityListener; }
	#endif
	
};


class PASCALIMPLEMENTATION TAppAnalyticsCacheManager : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Classes::TStringList* FDataCache;
	int FMaxCacheSize;
	System::UnicodeString FUserID;
	System::UnicodeString FSessionID;
	System::UnicodeString FApplicationID;
	unsigned FEventCount;
	System::UnicodeString FServerAddress;
	int FServerPort;
	System::Classes::TNotifyEvent FOnDataCacheFull;
	System::UnicodeString FCPUInfo;
	System::UnicodeString FAppVersion;
	System::UnicodeString FOSVersion;
	int __fastcall GetCacheCount();
	void __fastcall PersistData(const bool Wait);
	void __fastcall ClearData();
	void __fastcall Log(const System::UnicodeString AMessage);
	void __fastcall RemoveEventAtIndex(const int Index);
	System::UnicodeString __fastcall GetEventAtIndex(const int Index);
	void __fastcall SetOnDataCacheFull(const System::Classes::TNotifyEvent AValue);
	System::Classes::TNotifyEvent __fastcall GetOnDataCacheFull();
	void __fastcall SetMaxCacheSize(const int AValue);
	int __fastcall GetMaxCacheSize();
	__classmethod void __fastcall SendData(const System::UnicodeString ContentString, const System::UnicodeString ServerAddress, const int ServerPort);
	void __fastcall AddEnvironmentField(const System::UnicodeString AKey, const System::UnicodeString AValue);
	
public:
	__fastcall TAppAnalyticsCacheManager(const System::UnicodeString AppID, const System::UnicodeString UserID, const System::UnicodeString ServerAddress, const int ServerPort);
	__fastcall virtual ~TAppAnalyticsCacheManager();
	__property int CacheCount = {read=GetCacheCount, nodefault};
	__property int MaxCacheSize = {read=GetMaxCacheSize, write=SetMaxCacheSize, nodefault};
	__property System::UnicodeString Event[const int Index] = {read=GetEventAtIndex};
	__property System::Classes::TNotifyEvent OnDataCacheFull = {read=GetOnDataCacheFull, write=SetOnDataCacheFull};
private:
	void *__IAppAnalyticsStartupDataRecorder;	// System::Analytics::IAppAnalyticsStartupDataRecorder 
	void *__IApplicationActivityCacheManager;	// System::Analytics::IApplicationActivityCacheManager 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {783ED8DB-86BC-41C7-BBD3-443C19468FF1}
	operator System::Analytics::_di_IAppAnalyticsStartupDataRecorder()
	{
		System::Analytics::_di_IAppAnalyticsStartupDataRecorder intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Analytics::IAppAnalyticsStartupDataRecorder*(void) { return (System::Analytics::IAppAnalyticsStartupDataRecorder*)&__IAppAnalyticsStartupDataRecorder; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6145E812-8ECA-4B69-994C-26A81B2A84DC}
	operator System::Analytics::_di_IApplicationActivityCacheManager()
	{
		System::Analytics::_di_IApplicationActivityCacheManager intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Analytics::IApplicationActivityCacheManager*(void) { return (System::Analytics::IApplicationActivityCacheManager*)&__IApplicationActivityCacheManager; }
	#endif
	
};


class PASCALIMPLEMENTATION TCustomEventContext : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FCategory;
	System::UnicodeString FAction;
	System::UnicodeString FText;
	double FValue;
	
public:
	__fastcall TCustomEventContext(const System::UnicodeString ACategory, const System::UnicodeString AAction, const System::UnicodeString AText, const double AValue);
	__property System::UnicodeString Category = {read=FCategory, write=FCategory};
	__property System::UnicodeString Action = {read=FAction, write=FAction};
	__property System::UnicodeString Text = {read=FText, write=FText};
	__property double Value = {read=FValue, write=FValue};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomEventContext() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Appanalytics */
}	/* namespace Analytics */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANALYTICS_APPANALYTICS)
using namespace System::Analytics::Appanalytics;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANALYTICS)
using namespace System::Analytics;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Analytics_AppanalyticsHPP
