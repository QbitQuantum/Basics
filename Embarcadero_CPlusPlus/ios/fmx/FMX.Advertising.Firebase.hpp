// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Advertising.Firebase.pas' rev: 34.00 (iOS)

#ifndef Fmx_Advertising_FirebaseHPP
#define Fmx_Advertising_FirebaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Advertising
{
namespace Firebase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomFirebaseBannerAdModel;
class DELPHICLASS TCustomFirebaseBannerAd;
class DELPHICLASS TFirebaseBannerAd;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFirebaseBannerAdSize : unsigned char { Banner, LargeBanner, MediumRectangle, FullBanner, Leaderboard };

typedef void __fastcall (__closure *TDidFailToReceiveAdEvent)(System::TObject* Sender, const System::UnicodeString Error);

class PASCALIMPLEMENTATION TCustomFirebaseBannerAdModel : public Fmx::Controls::Model::TDataModel
{
	typedef Fmx::Controls::Model::TDataModel inherited;
	
private:
	TFirebaseBannerAdSize FAdSize;
	System::UnicodeString FAdUnitID;
	bool FTestMode;
	void __fastcall SetAdSize(const TFirebaseBannerAdSize Value);
	void __fastcall SetAdUnitID(const System::UnicodeString Value);
	void __fastcall SetTestMode(const bool Value);
	
public:
	void __fastcall LoadAd();
	__property TFirebaseBannerAdSize AdSize = {read=FAdSize, write=SetAdSize, nodefault};
	__property System::UnicodeString AdUnitID = {read=FAdUnitID, write=SetAdUnitID};
	__property bool TestMode = {read=FTestMode, write=SetTestMode, nodefault};
public:
	/* TDataModel.Create */ inline __fastcall virtual TCustomFirebaseBannerAdModel(System::Classes::TComponent* const AOwner)/* overload */ : Fmx::Controls::Model::TDataModel(AOwner) { }
	/* TDataModel.Destroy */ inline __fastcall virtual ~TCustomFirebaseBannerAdModel() { }
	
public:
	/* TMessageSender.Create */ inline __fastcall virtual TCustomFirebaseBannerAdModel()/* overload */ : Fmx::Controls::Model::TDataModel() { }
	
};


class PASCALIMPLEMENTATION TCustomFirebaseBannerAd : public Fmx::Controls::Presentation::TPresentedControl
{
	typedef Fmx::Controls::Presentation::TPresentedControl inherited;
	
private:
	System::Classes::TNotifyEvent FOnDidDismissScreen;
	TDidFailToReceiveAdEvent FOnDidFailToReceiveAd;
	System::Classes::TNotifyEvent FOnDidReceiveAd;
	System::Classes::TNotifyEvent FOnWillDismissScreen;
	System::Classes::TNotifyEvent FOnWillLeaveApplication;
	System::Classes::TNotifyEvent FOnWillPresentScreen;
	TFirebaseBannerAdSize __fastcall GetAdSize();
	System::UnicodeString __fastcall GetAdUnitID();
	HIDESBASE TCustomFirebaseBannerAdModel* __fastcall GetModel()/* overload */;
	bool __fastcall GetTestMode();
	void __fastcall SetAdSize(const TFirebaseBannerAdSize Value);
	void __fastcall SetAdUnitID(const System::UnicodeString Value);
	void __fastcall SetTestMode(const bool Value);
	
protected:
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual void __fastcall Paint();
	
public:
	void __fastcall DoDidDismissScreen();
	void __fastcall DoDidFailToReceiveAd(const System::UnicodeString AError);
	void __fastcall DoDidReceiveAd();
	void __fastcall DoWillDismissScreen();
	void __fastcall DoWillLeaveApplication();
	void __fastcall DoWillPresentScreen();
	__fastcall virtual TCustomFirebaseBannerAd(System::Classes::TComponent* AOwner)/* overload */;
	void __fastcall LoadAd();
	__property TFirebaseBannerAdSize AdSize = {read=GetAdSize, write=SetAdSize, nodefault};
	__property System::UnicodeString AdUnitID = {read=GetAdUnitID, write=SetAdUnitID};
	__property TCustomFirebaseBannerAdModel* Model = {read=GetModel};
	__property bool TestMode = {read=GetTestMode, write=SetTestMode, default=0};
	__property System::Classes::TNotifyEvent OnDidDismissScreen = {read=FOnDidDismissScreen, write=FOnDidDismissScreen};
	__property TDidFailToReceiveAdEvent OnDidFailToReceiveAd = {read=FOnDidFailToReceiveAd, write=FOnDidFailToReceiveAd};
	__property System::Classes::TNotifyEvent OnDidReceiveAd = {read=FOnDidReceiveAd, write=FOnDidReceiveAd};
	__property System::Classes::TNotifyEvent OnWillDismissScreen = {read=FOnWillDismissScreen, write=FOnWillDismissScreen};
	__property System::Classes::TNotifyEvent OnWillLeaveApplication = {read=FOnWillLeaveApplication, write=FOnWillLeaveApplication};
	__property System::Classes::TNotifyEvent OnWillPresentScreen = {read=FOnWillPresentScreen, write=FOnWillPresentScreen};
public:
	/* TPresentedControl.Destroy */ inline __fastcall virtual ~TCustomFirebaseBannerAd() { }
	
};


class PASCALIMPLEMENTATION TFirebaseBannerAd : public TCustomFirebaseBannerAd
{
	typedef TCustomFirebaseBannerAd inherited;
	
__published:
	__property Align = {default=0};
	__property Anchors;
	__property Height;
	__property Margins;
	__property Position;
	__property TestMode = {default=0};
	__property Visible = {default=1};
	__property Width;
	__property OnDidDismissScreen;
	__property OnDidFailToReceiveAd;
	__property OnDidReceiveAd;
	__property OnResize;
	__property OnResized;
	__property OnWillDismissScreen;
	__property OnWillLeaveApplication;
	__property OnWillPresentScreen;
public:
	/* TCustomFirebaseBannerAd.Create */ inline __fastcall virtual TFirebaseBannerAd(System::Classes::TComponent* AOwner)/* overload */ : TCustomFirebaseBannerAd(AOwner) { }
	
public:
	/* TPresentedControl.Destroy */ inline __fastcall virtual ~TFirebaseBannerAd() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word MM_FIREBASE_ADUNITID_CHANGED = System::Word(0x1701);
static constexpr System::Word MM_FIREBASE_LOADAD = System::Word(0x1702);
static constexpr System::Word MM_FIREBASE_TESTMODE_CHANGED = System::Word(0x1703);
static constexpr System::Word MM_FIREBASE_ADSIZE_CHANGED = System::Word(0x1704);
}	/* namespace Firebase */
}	/* namespace Advertising */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ADVERTISING_FIREBASE)
using namespace Fmx::Advertising::Firebase;
#endif
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
#endif	// Fmx_Advertising_FirebaseHPP
