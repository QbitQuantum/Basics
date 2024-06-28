// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Analytics.pas' rev: 34.00 (Windows)

#ifndef Fmx_AnalyticsHPP
#define Fmx_AnalyticsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Analytics.hpp>
#include <FMX.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Analytics
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomAnalytics;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TAnalyticsPrivacyMessageEvent)(System::TObject* Sender, bool &Activate);

class PASCALIMPLEMENTATION TCustomAnalytics : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool FEnabled;
	bool FAllowTracking;
	System::Analytics::TAppActivityOptions FOptions;
	System::UnicodeString FApplicationID;
	System::UnicodeString FUserID;
	System::UnicodeString FSessionID;
	int FMaxCacheSize;
	TAnalyticsPrivacyMessageEvent FOnPrivacyMessage;
	System::Classes::TStrings* FPrivacyMessage;
	int FUpdateInterval;
	Fmx::Types::TTimer* FUpdateTimer;
	void __fastcall DataCacheFull(System::TObject* Sender);
	void __fastcall UpdateTimerFired(System::TObject* Sender);
	int __fastcall GetUpdateInterval();
	void __fastcall SetUpdateInterval(const int Value);
	void __fastcall SetCacheSize(const int Value);
	void __fastcall SetOnPrivacyMessage(const TAnalyticsPrivacyMessageEvent Value);
	void __fastcall SetOptions(const System::Analytics::TAppActivityOptions Value);
	void __fastcall SetPrivacyMessage(System::Classes::TStrings* const Value);
	void __fastcall StartTracking();
	
protected:
	virtual bool __fastcall CheckPrivacy();
	virtual System::Analytics::_di_IApplicationActivityListener __fastcall GetListener() = 0 ;
	virtual System::Analytics::_di_IApplicationActivityCacheManager __fastcall GetCacheManager() = 0 ;
	virtual void __fastcall InstallHooks();
	virtual void __fastcall RemoveHooks();
	virtual void __fastcall SetEnabled(const bool Value);
	virtual void __fastcall Loaded();
	__property System::Analytics::_di_IApplicationActivityListener Listener = {read=GetListener};
	__property System::Analytics::_di_IApplicationActivityCacheManager CacheManager = {read=GetCacheManager};
	
public:
	__fastcall virtual TCustomAnalytics(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomAnalytics();
	__property bool AllowTracking = {read=FAllowTracking, write=FAllowTracking, stored=false, nodefault};
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=0};
	__property TAnalyticsPrivacyMessageEvent OnPrivacyMessage = {read=FOnPrivacyMessage, write=SetOnPrivacyMessage};
	__property System::UnicodeString ApplicationID = {read=FApplicationID, write=FApplicationID};
	__property System::UnicodeString UserID = {read=FUserID, write=FUserID, stored=false};
	__property System::UnicodeString SessionID = {read=FSessionID, stored=false};
	__property int UpdateInterval = {read=GetUpdateInterval, write=SetUpdateInterval, nodefault};
	__property int CacheSize = {read=FMaxCacheSize, write=SetCacheSize, nodefault};
	__property System::Analytics::TAppActivityOptions Options = {read=FOptions, write=SetOptions, nodefault};
	__property System::Classes::TStrings* PrivacyMessage = {read=FPrivacyMessage, write=SetPrivacyMessage};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Analytics */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ANALYTICS)
using namespace Fmx::Analytics;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_AnalyticsHPP
