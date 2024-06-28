// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Analytics.AppAnalytics.pas' rev: 34.00 (Android)

#ifndef Fmx_Analytics_AppanalyticsHPP
#define Fmx_Analytics_AppanalyticsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Analytics.hpp>
#include <FMX.Analytics.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Analytics
{
namespace Appanalytics
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAppAnalytics;
class DELPHICLASS EAppAnalyticsCategoryMissingException;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAppAnalytics : public Fmx::Analytics::TCustomAnalytics
{
	typedef Fmx::Analytics::TCustomAnalytics inherited;
	
private:
	System::UnicodeString FServerAddress;
	int FServerPort;
	System::Analytics::_di_IApplicationActivityListener FListener;
	System::Analytics::_di_IApplicationActivityCacheManager FCacheManager;
	
protected:
	virtual System::Analytics::_di_IApplicationActivityListener __fastcall GetListener();
	virtual System::Analytics::_di_IApplicationActivityCacheManager __fastcall GetCacheManager();
	virtual void __fastcall InstallHooks();
	virtual void __fastcall RemoveHooks();
	virtual void __fastcall SetEnabled(const bool Value);
	
public:
	__fastcall virtual TAppAnalytics(System::Classes::TComponent* AOwner);
	void __fastcall TrackEvent(const System::UnicodeString ACategory, const System::UnicodeString AAction = System::UnicodeString(), const System::UnicodeString ALabel = System::UnicodeString(), const double AValue = 0.000000E+00);
	__property System::UnicodeString AppAnalyticsServer = {read=FServerAddress, write=FServerAddress};
	__property int ServerPort = {read=FServerPort, write=FServerPort, default=80};
	
__published:
	__property Enabled = {default=0};
	__property OnPrivacyMessage;
	__property ApplicationID = {default=0};
	__property UpdateInterval;
	__property CacheSize;
	__property Options;
	__property PrivacyMessage;
public:
	/* TCustomAnalytics.Destroy */ inline __fastcall virtual ~TAppAnalytics() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EAppAnalyticsCategoryMissingException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EAppAnalyticsCategoryMissingException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EAppAnalyticsCategoryMissingException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EAppAnalyticsCategoryMissingException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EAppAnalyticsCategoryMissingException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EAppAnalyticsCategoryMissingException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EAppAnalyticsCategoryMissingException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EAppAnalyticsCategoryMissingException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EAppAnalyticsCategoryMissingException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAppAnalyticsCategoryMissingException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAppAnalyticsCategoryMissingException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAppAnalyticsCategoryMissingException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAppAnalyticsCategoryMissingException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EAppAnalyticsCategoryMissingException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Appanalytics */
}	/* namespace Analytics */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ANALYTICS_APPANALYTICS)
using namespace Fmx::Analytics::Appanalytics;
#endif
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
#endif	// Fmx_Analytics_AppanalyticsHPP
