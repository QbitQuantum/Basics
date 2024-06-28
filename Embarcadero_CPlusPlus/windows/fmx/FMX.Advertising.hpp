// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Advertising.pas' rev: 34.00 (Windows)

#ifndef Fmx_AdvertisingHPP
#define Fmx_AdvertisingHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Advertising
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EAdvertisingError;
__interface DELPHIINTERFACE ICommonAd;
typedef System::DelphiInterface<ICommonAd> _di_ICommonAd;
__interface DELPHIINTERFACE IBannerAd;
typedef System::DelphiInterface<IBannerAd> _di_IBannerAd;
__interface DELPHIINTERFACE IFMXAdvertisingService;
typedef System::DelphiInterface<IFMXAdvertisingService> _di_IFMXAdvertisingService;
__interface DELPHIINTERFACE IFMXAdvertisingTestModeService;
typedef System::DelphiInterface<IFMXAdvertisingTestModeService> _di_IFMXAdvertisingTestModeService;
class DELPHICLASS TCustomBannerAd;
class DELPHICLASS TBannerAd;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EAdvertisingError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EAdvertisingError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EAdvertisingError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EAdvertisingError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EAdvertisingError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EAdvertisingError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EAdvertisingError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EAdvertisingError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EAdvertisingError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAdvertisingError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAdvertisingError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAdvertisingError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAdvertisingError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EAdvertisingError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{21350E71-EEBD-4476-9984-8714700D60C1}") ICommonAd  : public System::IInterface 
{
	virtual void __fastcall CancelAction() = 0 ;
	virtual bool __fastcall IsActionInProgress() = 0 ;
	virtual bool __fastcall IsLoaded() = 0 ;
	virtual System::UnicodeString __fastcall GetAdUnitID() = 0 ;
	virtual void __fastcall SetAdUnitID(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall LoadAd() = 0 ;
	__property System::UnicodeString AdUnitID = {read=GetAdUnitID, write=SetAdUnitID};
};

__interface  INTERFACE_UUID("{E2432D16-1FFA-41F8-964A-76F4ADFB0020}") IBannerAd  : public ICommonAd 
{
	virtual void __fastcall SetBannerAdControl(TCustomBannerAd* const AValue) = 0 ;
	virtual Fmx::Types::TFmxObject* __fastcall GetParent() = 0 ;
	virtual bool __fastcall GetVisible() = 0 ;
	virtual void __fastcall Show() = 0 ;
	virtual void __fastcall Hide() = 0 ;
	virtual void __fastcall UpdateContentFromControl() = 0 ;
};

__interface  INTERFACE_UUID("{CFDCA239-A3B8-428D-94A5-4C7E4D50E398}") IFMXAdvertisingService  : public System::IInterface 
{
	virtual _di_IBannerAd __fastcall CreateBannerAd(TCustomBannerAd* const AOwner) = 0 ;
	virtual void __fastcall RemoveAd(const _di_ICommonAd Ad) = 0 ;
};

__interface  INTERFACE_UUID("{6030094F-647F-423F-8D61-A2BCF13BFDB4}") IFMXAdvertisingTestModeService  : public System::IInterface 
{
	virtual void __fastcall SetTestMode(bool AValue) = 0 ;
	virtual bool __fastcall GetTestMode() = 0 ;
	virtual void __fastcall SetTestModeDeviceID(const System::UnicodeString ADeviceID) = 0 ;
};

typedef void __fastcall (__closure *TAdActionCanBeginEvent)(System::TObject* Sender, bool &WillLeaveApplication);

typedef void __fastcall (__closure *TAdDidFailEvent)(System::TObject* Sender, const System::UnicodeString Error);

enum class DECLSPEC_DENUM TBannerAdSize : unsigned char { Auto, Small, Medium, Large };

class PASCALIMPLEMENTATION TCustomBannerAd : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
private:
	_di_IBannerAd FAd;
	_di_IFMXAdvertisingService FAdService;
	TAdActionCanBeginEvent FOnActionCanBegin;
	System::Classes::TNotifyEvent FOnActionDidFinish;
	System::Classes::TNotifyEvent FOnWillLoad;
	System::Classes::TNotifyEvent FOnDidLoad;
	TAdDidFailEvent FOnDidFail;
	bool FTestMode;
	TBannerAdSize FAdSize;
	void __fastcall UpdateContent();
	
protected:
	virtual void __fastcall Move();
	virtual void __fastcall Resize();
	virtual void __fastcall Paint();
	virtual void __fastcall SetParent(Fmx::Types::TFmxObject* const Value);
	virtual void __fastcall AncestorVisibleChanged(const bool Visible);
	virtual void __fastcall ParentChanged();
	virtual void __fastcall DoAbsoluteChanged();
	System::UnicodeString __fastcall GetAdUnitID();
	void __fastcall SetAdUnitID(const System::UnicodeString Value);
	void __fastcall SetTestMode(bool AValue);
	virtual HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	
public:
	__fastcall virtual TCustomBannerAd(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBannerAd();
	virtual void __fastcall Show();
	virtual void __fastcall Hide();
	void __fastcall DoActionCanBegin(bool &WillLeaveApplication);
	void __fastcall DoActionDidFinish();
	void __fastcall DoWillLoad();
	void __fastcall DoDidLoad();
	void __fastcall DoDidFail(const System::UnicodeString Error);
	void __fastcall CancelAction();
	bool __fastcall IsActionInProgress();
	bool __fastcall IsLoaded();
	void __fastcall LoadAd();
	__property System::UnicodeString AdUnitID = {read=GetAdUnitID, write=SetAdUnitID};
	__property TAdActionCanBeginEvent OnActionCanBegin = {read=FOnActionCanBegin, write=FOnActionCanBegin};
	__property System::Classes::TNotifyEvent OnActionDidFinish = {read=FOnActionDidFinish, write=FOnActionDidFinish};
	__property System::Classes::TNotifyEvent OnWillLoad = {read=FOnWillLoad, write=FOnWillLoad};
	__property System::Classes::TNotifyEvent OnDidLoad = {read=FOnDidLoad, write=FOnDidLoad};
	__property TAdDidFailEvent OnDidFail = {read=FOnDidFail, write=FOnDidFail};
	__property bool TestMode = {read=FTestMode, write=SetTestMode, default=0};
	__property TBannerAdSize AdSize = {read=FAdSize, write=FAdSize, default=0};
};


class PASCALIMPLEMENTATION TBannerAd : public TCustomBannerAd
{
	typedef TCustomBannerAd inherited;
	
__published:
	__property AdSize = {default=0};
	__property Align = {default=0};
	__property Anchors;
	__property Width;
	__property Height;
	__property Margins;
	__property Position;
	__property TestMode = {default=0};
	__property Visible = {default=1};
	__property OnActionCanBegin;
	__property OnActionDidFinish;
	__property OnWillLoad;
	__property OnDidLoad;
	__property OnDidFail;
	__property OnResize;
	__property OnResized;
public:
	/* TCustomBannerAd.Create */ inline __fastcall virtual TBannerAd(System::Classes::TComponent* AOwner) : TCustomBannerAd(AOwner) { }
	/* TCustomBannerAd.Destroy */ inline __fastcall virtual ~TBannerAd() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Advertising */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ADVERTISING)
using namespace Fmx::Advertising;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_AdvertisingHPP
