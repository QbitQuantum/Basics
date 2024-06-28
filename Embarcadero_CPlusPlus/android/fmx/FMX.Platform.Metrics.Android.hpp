// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.Metrics.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Platform_Metrics_AndroidHPP
#define Fmx_Platform_Metrics_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Rtti.hpp>
#include <FMX.Pickers.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Graphics.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Metrics
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidMetricsServices;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidMetricsServices : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	static constexpr System::Int8 DefaultAndroidFontSize = System::Int8(0xe);
	
	#define TAndroidMetricsServices_DefaultAndroidFontName u"Roboto"
	
	
protected:
	virtual void __fastcall RegisterServices();
	virtual void __fastcall UnregisterServices();
	
public:
	__fastcall TAndroidMetricsServices();
	__fastcall virtual ~TAndroidMetricsServices();
	bool __fastcall SupportsDefaultSize(const Fmx::Platform::TComponentKind AComponent);
	System::Types::TSize __fastcall GetDefaultSize(const Fmx::Platform::TComponentKind AComponent);
	System::Rtti::TValue __fastcall GetDefaultPropertyValue(const System::UnicodeString AClassName, const System::UnicodeString APropertyName);
	Fmx::Platform::TScrollingBehaviours __fastcall GetScrollingBehaviour();
	float __fastcall GetMinScrollThumbSize();
	int __fastcall GetCaretWidth();
	int __fastcall GetMenuShowDelay();
	System::UnicodeString __fastcall GetDefaultFontFamilyName();
	float __fastcall GetDefaultFontSize();
	System::UnicodeString __fastcall GetCurrentLangID();
	System::UnicodeString __fastcall GetLocaleFirstDayOfWeek();
	System::Byte __fastcall GetFirstWeekday();
	Fmx::Platform::TListingHeaderBehaviors __fastcall GetListingHeaderBehaviors();
	Fmx::Platform::TListingSearchFeatures __fastcall GetListingSearchFeatures();
	Fmx::Platform::TListingTransitionFeatures __fastcall GetListingTransitionFeatures();
	Fmx::Platform::TListingEditModeFeatures __fastcall GetListingEditModeFeatures();
private:
	void *__IFMXListingService;	// Fmx::Platform::IFMXListingService 
	void *__IFMXLocaleService;	// Fmx::Platform::IFMXLocaleService 
	void *__IFMXSystemFontService;	// Fmx::Graphics::IFMXSystemFontService 
	void *__IFMXSystemInformationService;	// Fmx::Platform::IFMXSystemInformationService 
	void *__IFMXDefaultPropertyValueService;	// Fmx::Platform::IFMXDefaultPropertyValueService 
	void *__IFMXDefaultMetricsService;	// Fmx::Platform::IFMXDefaultMetricsService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {942C2800-D66E-4094-9B77-BA88A1FBC788}
	operator Fmx::Platform::_di_IFMXListingService()
	{
		Fmx::Platform::_di_IFMXListingService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXListingService*(void) { return (Fmx::Platform::IFMXListingService*)&__IFMXListingService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {311A40D4-3D5B-40CC-A201-78465760B25E}
	operator Fmx::Platform::_di_IFMXLocaleService()
	{
		Fmx::Platform::_di_IFMXLocaleService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXLocaleService*(void) { return (Fmx::Platform::IFMXLocaleService*)&__IFMXLocaleService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {62017F22-ADF1-44D9-A21D-796D8C7F3CF0}
	operator Fmx::Graphics::_di_IFMXSystemFontService()
	{
		Fmx::Graphics::_di_IFMXSystemFontService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Graphics::IFMXSystemFontService*(void) { return (Fmx::Graphics::IFMXSystemFontService*)&__IFMXSystemFontService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2E01A60B-E297-4AC0-AA24-C5F52289EC1E}
	operator Fmx::Platform::_di_IFMXSystemInformationService()
	{
		Fmx::Platform::_di_IFMXSystemInformationService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXSystemInformationService*(void) { return (Fmx::Platform::IFMXSystemInformationService*)&__IFMXSystemInformationService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7E8A25A0-5FCF-49FA-990C-CEDE6ABEAE50}
	operator Fmx::Platform::_di_IFMXDefaultPropertyValueService()
	{
		Fmx::Platform::_di_IFMXDefaultPropertyValueService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXDefaultPropertyValueService*(void) { return (Fmx::Platform::IFMXDefaultPropertyValueService*)&__IFMXDefaultPropertyValueService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {216841F5-C089-45F1-B350-E9B018B73441}
	operator Fmx::Platform::_di_IFMXDefaultMetricsService()
	{
		Fmx::Platform::_di_IFMXDefaultMetricsService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXDefaultMetricsService*(void) { return (Fmx::Platform::IFMXDefaultMetricsService*)&__IFMXDefaultMetricsService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Metrics */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_METRICS_ANDROID)
using namespace Fmx::Platform::Metrics::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_METRICS)
using namespace Fmx::Platform::Metrics;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM)
using namespace Fmx::Platform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Platform_Metrics_AndroidHPP
