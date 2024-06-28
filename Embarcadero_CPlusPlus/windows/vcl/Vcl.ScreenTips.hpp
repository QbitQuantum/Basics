// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Vcl.ScreenTips.pas' rev: 34.00 (Windows)

#ifndef Vcl_ScreentipsHPP
#define Vcl_ScreentipsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnList.hpp>
#include <Winapi.Windows.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.Forms.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.Controls.hpp>
#include <System.Contnrs.hpp>
#include <Winapi.Messages.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcl
{
namespace Screentips
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TScreenTipsWindow;
class DELPHICLASS TScreenTipItem;
class DELPHICLASS TScreenTipsCollection;
class DELPHICLASS TScreenTipBorderStyle;
class DELPHICLASS TDisplayOffset;
class DELPHICLASS EAllocatedActionsException;
class DELPHICLASS TAllocatedActions;
class DELPHICLASS TAssociateItem;
class DELPHICLASS TAssociateItemList;
class DELPHICLASS TCustomScreenTipsManager;
class DELPHICLASS TScreenTipsManager;
__interface DELPHIINTERFACE IScreenTipItem;
typedef System::DelphiInterface<IScreenTipItem> _di_IScreenTipItem;
class DELPHICLASS TCustomScreenTipsPopup;
class DELPHICLASS TScreenTipsPopup;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TTipBorderStyle : unsigned char { hbsNormal, hbsRounded };

#ifndef _WIN64
typedef System::TMetaClass* TScreenTipsWindowClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TScreenTipsWindowClass);
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TScreenTipsWindow : public Vcl::Controls::THintWindow
{
	typedef Vcl::Controls::THintWindow inherited;
	
private:
	System::UnicodeString FBody;
	Vcl::Graphics::TPicture* FImage;
	System::Uitypes::TColor FGradientStartColor;
	System::Uitypes::TColor FGradientEndColor;
	Vcl::Graphics::TBitmap* FHelpBitmap;
	Vcl::Extctrls::TTimer* FVisibleTimer;
	Vcl::Extctrls::TTimer* FTimeOutTimer;
	TScreenTipItem* FActiveItem;
	System::UnicodeString FFooter;
	Vcl::Controls::TControl* FHintControl;
	TTipBorderStyle FTipBorderStyle;
	int FCornerSize;
	System::UnicodeString FTitle;
	bool __fastcall HasDisabledText();
	void __fastcall SetHelpBitmap(Vcl::Graphics::TBitmap* const Value);
	void __fastcall SetFooter(const System::UnicodeString Value);
	void __fastcall SetGradientEndColor(const System::Uitypes::TColor Value);
	void __fastcall SetGradientStartColor(const System::Uitypes::TColor Value);
	void __fastcall SetBody(const System::UnicodeString Value);
	void __fastcall SetImage(Vcl::Graphics::TPicture* const Value);
	void __fastcall TimeOutTimerHandler(System::TObject* Sender);
	void __fastcall VisibleTimerHandler(System::TObject* Sender);
	
protected:
	HIDESBASE MESSAGE void __fastcall CMMouseenter(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TMessage &Message);
	virtual void __fastcall CreateParams(Vcl::Controls::TCreateParams &Params);
	virtual void __fastcall CreateRoundedStyle();
	virtual void __fastcall CreateTipBorderStyle();
	virtual void __fastcall CreateWnd();
	virtual void __fastcall DrawBackground(const System::Types::TRect &aRect);
	virtual void __fastcall DrawBorder(const System::Types::TRect &aRect);
	virtual void __fastcall DrawFooter();
	virtual int __fastcall DrawHeader();
	virtual void __fastcall Paint();
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(Winapi::Messages::TWMNCHitTest &Message);
	
public:
	__fastcall virtual TScreenTipsWindow(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TScreenTipsWindow();
	virtual void __fastcall ActivateToolTip(const System::Types::TRect &Rect, TScreenTipItem* Item);
	void __fastcall HideHint();
	__property Vcl::Controls::TControl* HintControl = {read=FHintControl, write=FHintControl};
	__property Vcl::Graphics::TPicture* Image = {read=FImage, write=SetImage};
	__property System::Uitypes::TColor GradientStartColor = {read=FGradientStartColor, write=SetGradientStartColor, nodefault};
	__property System::Uitypes::TColor GradientEndColor = {read=FGradientEndColor, write=SetGradientEndColor, nodefault};
	__property System::UnicodeString Body = {read=FBody, write=SetBody};
	__property System::UnicodeString Footer = {read=FFooter, write=SetFooter};
	__property Vcl::Graphics::TBitmap* FooterImage = {read=FHelpBitmap, write=SetHelpBitmap};
	__property TScreenTipItem* ActiveItem = {read=FActiveItem};
	__property TTipBorderStyle TipBorderStyle = {read=FTipBorderStyle, write=FTipBorderStyle, default=1};
	__property int CornerSize = {read=FCornerSize, write=FCornerSize, default=5};
public:
	/* TWinControl.CreateParented */ inline __fastcall TScreenTipsWindow(HWND ParentWindow) : Vcl::Controls::THintWindow(ParentWindow) { }
	
};


enum DECLSPEC_DENUM TScreenTipOption : unsigned char { soShowHeader, soShowShortCut };

typedef System::Set<TScreenTipOption, TScreenTipOption::soShowHeader, TScreenTipOption::soShowShortCut> TScreenTipOptions;

enum DECLSPEC_DENUM TImageAlign : unsigned char { iaLeft, iaRight };

enum DECLSPEC_DENUM TItemImageAlign : unsigned char { iiaLeft, iiaCenter, iiaRight };

enum DECLSPEC_DENUM TDescriptionType : unsigned char { dtManual, dtHelp, dtResource };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TScreenTipItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FHeader;
	Vcl::Graphics::TPicture* FImage;
	System::Classes::TStrings* FDescription;
	System::Actions::TContainedAction* FAction;
	TScreenTipsCollection* FItemOwner;
	bool FShowImage;
	System::Classes::TStrings* FDisabledDescription;
	int FWidth;
	int FHeight;
	int FCacheDisabledHeight;
	int FCacheDisabledWidth;
	bool FShowFooter;
	TCustomScreenTipsManager* FManager;
	System::UnicodeString FDisabledHeader;
	void __fastcall SetDescription(System::Classes::TStrings* const Value);
	void __fastcall SetDisabledDescription(System::Classes::TStrings* const Value);
	int __fastcall GetHeight();
	TCustomScreenTipsManager* __fastcall GetManager();
	void __fastcall SetImage(Vcl::Graphics::TPicture* const Value);
	void __fastcall SetAction(System::Actions::TContainedAction* const Value);
	void __fastcall DescriptionChange(System::TObject* Sender);
	bool __fastcall IsDisableHeaderStored();
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall virtual TScreenTipItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TScreenTipItem();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall SetManager(TCustomScreenTipsManager* AManager);
	bool __fastcall IsEnabled();
	__property int Height = {read=GetHeight, write=FHeight, nodefault};
	__property int Width = {read=FWidth, write=FWidth, nodefault};
	
__published:
	__property System::Actions::TContainedAction* Action = {read=FAction, write=SetAction};
	__property System::Classes::TStrings* Description = {read=FDescription, write=SetDescription};
	__property System::UnicodeString DisabledHeader = {read=FDisabledHeader, write=FDisabledHeader, stored=IsDisableHeaderStored};
	__property System::Classes::TStrings* DisabledDescription = {read=FDisabledDescription, write=SetDisabledDescription};
	__property System::UnicodeString Header = {read=FHeader, write=FHeader};
	__property Vcl::Graphics::TPicture* Image = {read=FImage, write=SetImage};
	__property TCustomScreenTipsManager* Manager = {read=GetManager};
	__property bool ShowFooter = {read=FShowFooter, write=FShowFooter, default=1};
	__property bool ShowImage = {read=FShowImage, write=FShowImage, default=0};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TScreenTipsCollection : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TScreenTipItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	TCustomScreenTipsManager* FManager;
	HIDESBASE TScreenTipItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TScreenTipItem* const Value);
	
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	
public:
	__fastcall TScreenTipsCollection(TCustomScreenTipsManager* Manager);
	HIDESBASE TScreenTipItem* __fastcall Add();
	HIDESBASE TScreenTipItem* __fastcall Insert(int Index);
	__property TScreenTipItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TScreenTipsCollection() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TScreenTipBorderStyle : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Uitypes::TColor FColor;
	int FCornerSize;
	TTipBorderStyle FStyle;
	
public:
	__fastcall TScreenTipBorderStyle();
	
__published:
	__property TTipBorderStyle Style = {read=FStyle, write=FStyle, default=1};
	__property int CornerSize = {read=FCornerSize, write=FCornerSize, default=5};
	__property System::Uitypes::TColor Color = {read=FColor, write=FColor, default=7763574};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TScreenTipBorderStyle() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TShowScreenTipEvent)(System::TObject* Manager, System::Classes::TBasicAction* Action, bool &ShowScreenTip);

typedef void __fastcall (__closure *TScreenTipWinClass)(System::TObject* Manager, TScreenTipsWindowClass &ScreenTipWinClass);

typedef void __fastcall (__closure *TCreateScreenTipEvent)(System::TObject* Manager, TScreenTipItem* Item);

typedef void __fastcall (__closure *TDuplicateCreateErrorEvent)(System::TObject* Manager, System::Classes::TBasicAction* Action);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDisplayOffset : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	int FX;
	int FY;
	Vcl::Controls::TControl* FControl;
	
public:
	__fastcall TDisplayOffset();
	
__published:
	__property Vcl::Controls::TControl* Control = {read=FControl, write=FControl};
	__property int X = {read=FX, write=FX, default=0};
	__property int Y = {read=FY, write=FY, default=5};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDisplayOffset() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EAllocatedActionsException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EAllocatedActionsException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EAllocatedActionsException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EAllocatedActionsException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EAllocatedActionsException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EAllocatedActionsException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EAllocatedActionsException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EAllocatedActionsException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EAllocatedActionsException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAllocatedActionsException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAllocatedActionsException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAllocatedActionsException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAllocatedActionsException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EAllocatedActionsException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllocatedActions : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStringList* FList;
	int __fastcall GetCount();
	
public:
	__fastcall TAllocatedActions();
	__fastcall virtual ~TAllocatedActions();
	void __fastcall AddAction(const System::UnicodeString aName, System::TObject* aScreenTipItem);
	void __fastcall Clear();
	bool __fastcall Delete(const System::UnicodeString aName, /* out */ int &aIndex);
	bool __fastcall Exists(const System::UnicodeString aName);
	bool __fastcall Find(const System::UnicodeString aName, /* out */ int &aIndex);
	TScreenTipItem* __fastcall GetItem(const System::UnicodeString aName);
	__property int Count = {read=GetCount, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAssociateItem : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Vcl::Controls::TControl* FPopupTip;
	Vcl::Controls::TControl* FAssociate;
	
public:
	__fastcall TAssociateItem(Vcl::Controls::TControl* APopupTip, Vcl::Controls::TControl* AAssociate);
	__fastcall virtual ~TAssociateItem();
	__property Vcl::Controls::TControl* PopupTip = {read=FPopupTip, write=FPopupTip};
	__property Vcl::Controls::TControl* Associate = {read=FAssociate, write=FAssociate};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAssociateItemList : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Contnrs::TObjectList* FList;
	
public:
	__fastcall virtual TAssociateItemList();
	__fastcall virtual ~TAssociateItemList();
	void __fastcall Add(Vcl::Controls::TControl* Popup, Vcl::Controls::TControl* Associate);
	void __fastcall Remove(Vcl::Controls::TControl* Associate);
	int __fastcall Find(Vcl::Controls::TControl* Associate);
	TAssociateItem* __fastcall Get(const int Idx);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TCustomScreenTipsManager : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Vcl::Actnman::TActionListCollection* FLinkedActionLists;
	TScreenTipsCollection* FScreenTips;
	TAllocatedActions* FAllocatedActions;
	System::UnicodeString FFooter;
	Vcl::Graphics::TPicture* FFooterImage;
	TScreenTipOptions FOptions;
	Vcl::Appevnts::TApplicationEvents* FAppEvents;
	TScreenTipsWindow* FWnd;
	System::Uitypes::TColor FGradientStartColor;
	System::Uitypes::TColor FGradientEndColor;
	TScreenTipWinClass FOnGetScreenTipWinClass;
	TShowScreenTipEvent FOnShowScreenTip;
	TCreateScreenTipEvent FOnCreateScreenTip;
	System::Classes::TNotifyEvent FOnScreenTipsLoaded;
	bool FAcceptFocus;
	TDuplicateCreateErrorEvent FOnDuplicateCreateError;
	TScreenTipBorderStyle* FBorderStyle;
	TDisplayOffset* FDisplayOffset;
	bool FCalculatingHeight;
	System::Contnrs::TComponentList* FPopupControlList;
	TAssociateItemList* FAssociateItemList;
	Vcl::Graphics::TFont* FFont;
	void __fastcall ApplicationActivate(System::TObject* Sender);
	void __fastcall ApplicationDeactivate(System::TObject* Sender);
	void __fastcall ApplicationShowHint(System::UnicodeString &HintStr, bool &CanShow, Vcl::Controls::THintInfo &HintInfo);
	int __fastcall CalculateHeight(TScreenTipItem* Item);
	int __fastcall CalculateWidth(TScreenTipItem* Item);
	void __fastcall GenerateScreenTipsForActionList(Vcl::Actnlist::TCustomActionList* aActionList);
	Vcl::Actnman::TActionListCollection* __fastcall GetLinkedActionLists();
	TScreenTipsCollection* __fastcall GetScreenTips();
	bool __fastcall HasLinkedActionLists();
	void __fastcall HideActiveHint();
	bool __fastcall IsDisplayOffsetStored();
	bool __fastcall IsFooterStored();
	bool __fastcall IsFontStored();
	bool __fastcall IsLinkedActionListsStored();
	bool __fastcall IsScreenTipItemsStored();
	void __fastcall SetFont(Vcl::Graphics::TFont* const Value);
	void __fastcall SetFooterImage(Vcl::Graphics::TPicture* const Value);
	void __fastcall SetLinkedActionLists(Vcl::Actnman::TActionListCollection* const Value);
	void __fastcall SetScreenTips(TScreenTipsCollection* const Value);
	void __fastcall ValidateAllocatedActions();
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall DoCreateScreenTip(TScreenTipItem* aItem);
	virtual void __fastcall DoDuplicateCreateError(System::Classes::TBasicAction* aAction);
	virtual void __fastcall DoGetScreenTipClass(TScreenTipsWindowClass &WindowClass);
	virtual void __fastcall DoScreenTipsLoaded();
	virtual void __fastcall DoShow(TScreenTipItem* Item, Vcl::Controls::THintInfo &HintInfo);
	virtual void __fastcall DoShowScreenTip(System::Classes::TBasicAction* Action, TScreenTipItem* Item, Vcl::Controls::THintInfo &HintInfo);
	virtual void __fastcall Loaded();
	void __fastcall UpdateActionInfo(System::Actions::TContainedAction* aAction, TScreenTipItem* aTooltip);
	
public:
	__fastcall virtual TCustomScreenTipsManager(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomScreenTipsManager();
	void __fastcall AddPopup(Vcl::Controls::TCustomControl* AScreenTipPopup);
	void __fastcall ClearScreenTips();
	TScreenTipItem* __fastcall CreateScreenTip(System::Classes::TBasicAction* aAction);
	bool __fastcall GenerateScreenTips();
	TScreenTipItem* __fastcall GetScreenTip(System::Classes::TBasicAction* aAction);
	void __fastcall RemovePopup(Vcl::Controls::TCustomControl* AScreenTipPopup);
	bool __fastcall RemoveScreenTip(TScreenTipItem* aScreenTip);
	void __fastcall UpdateOptions();
	__property TScreenTipBorderStyle* BorderStyle = {read=FBorderStyle, write=FBorderStyle};
	__property TDisplayOffset* DisplayOffset = {read=FDisplayOffset, write=FDisplayOffset, stored=IsDisplayOffsetStored};
	__property Vcl::Graphics::TFont* Font = {read=FFont, write=SetFont, stored=IsFontStored};
	__property System::UnicodeString Footer = {read=FFooter, write=FFooter, stored=IsFooterStored};
	__property Vcl::Graphics::TPicture* FooterImage = {read=FFooterImage, write=SetFooterImage};
	__property System::Uitypes::TColor GradientEndColor = {read=FGradientEndColor, write=FGradientEndColor, default=-16777201};
	__property System::Uitypes::TColor GradientStartColor = {read=FGradientStartColor, write=FGradientStartColor, default=16777215};
	__property Vcl::Actnman::TActionListCollection* LinkedActionLists = {read=GetLinkedActionLists, write=SetLinkedActionLists, stored=IsLinkedActionListsStored};
	__property TScreenTipOptions Options = {read=FOptions, write=FOptions, default=3};
	__property TScreenTipsCollection* ScreenTips = {read=GetScreenTips, write=SetScreenTips, stored=IsScreenTipItemsStored};
	__property TCreateScreenTipEvent OnCreateScreenTip = {read=FOnCreateScreenTip, write=FOnCreateScreenTip};
	__property TShowScreenTipEvent OnShowScreenTip = {read=FOnShowScreenTip, write=FOnShowScreenTip};
	__property TScreenTipWinClass OnGetScreenTipWinClass = {read=FOnGetScreenTipWinClass, write=FOnGetScreenTipWinClass};
	__property System::Classes::TNotifyEvent OnScreenTipsLoaded = {read=FOnScreenTipsLoaded, write=FOnScreenTipsLoaded};
	__property TDuplicateCreateErrorEvent OnDuplicateCreateError = {read=FOnDuplicateCreateError, write=FOnDuplicateCreateError};
};


class PASCALIMPLEMENTATION TScreenTipsManager : public TCustomScreenTipsManager
{
	typedef TCustomScreenTipsManager inherited;
	
__published:
	__property BorderStyle;
	__property DisplayOffset;
	__property Font;
	__property Footer = {default=0};
	__property FooterImage;
	__property GradientEndColor = {default=-16777201};
	__property GradientStartColor = {default=16777215};
	__property LinkedActionLists;
	__property Options = {default=3};
	__property ScreenTips;
	__property OnCreateScreenTip;
	__property OnDuplicateCreateError;
	__property OnShowScreenTip;
	__property OnGetScreenTipWinClass;
	__property OnScreenTipsLoaded;
public:
	/* TCustomScreenTipsManager.Create */ inline __fastcall virtual TScreenTipsManager(System::Classes::TComponent* AOwner) : TCustomScreenTipsManager(AOwner) { }
	/* TCustomScreenTipsManager.Destroy */ inline __fastcall virtual ~TScreenTipsManager() { }
	
};


__interface  INTERFACE_UUID("{FC7D9558-D3EC-4C4D-8E68-ADFEC71451B1}") IScreenTipItem  : public System::IInterface 
{
	virtual TScreenTipItem* __fastcall GetScreenTipItem() = 0 ;
};

enum DECLSPEC_DENUM TScreenTipPopupType : unsigned char { ptCustom, ptHelp, ptInfo };

class PASCALIMPLEMENTATION TCustomScreenTipsPopup : public Vcl::Controls::TCustomControl
{
	typedef Vcl::Controls::TCustomControl inherited;
	
private:
	Vcl::Graphics::TPicture* FGlyph;
	Vcl::Graphics::TPicture* FCustomGlyph;
	Vcl::Graphics::TBitmap* FKnownGlyph;
	TScreenTipPopupType FPopupType;
	TCustomScreenTipsManager* FScreenTipsManager;
	Vcl::Controls::TControl* FAssociate;
	TScreenTipItem* FScreenTip;
	bool FTransparent;
	Vcl::Graphics::TPicture* __fastcall GetPicture();
	void __fastcall InitialisePopupType();
	void __fastcall ResizeControl();
	void __fastcall SetAssociate(Vcl::Controls::TControl* const Value);
	void __fastcall SetPicture(Vcl::Graphics::TPicture* const Value);
	void __fastcall SetPopupType(const TScreenTipPopupType Value);
	void __fastcall SetScreenTip(TScreenTipItem* const Value);
	void __fastcall SetScreenTipsManager(TCustomScreenTipsManager* const Value);
	void __fastcall SetTransparent(const bool Value);
	
protected:
	virtual void __fastcall LinkPopupToManager();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall Paint();
	virtual void __fastcall RemoveLinkToManager();
	virtual void __fastcall UpdateAssociateToManager();
	
public:
	__fastcall virtual TCustomScreenTipsPopup(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomScreenTipsPopup();
	TScreenTipItem* __fastcall GetScreenTipItem();
	__property Vcl::Controls::TControl* Associate = {read=FAssociate, write=SetAssociate};
	__property Vcl::Graphics::TPicture* Glyph = {read=GetPicture, write=SetPicture};
	__property TScreenTipPopupType PopupType = {read=FPopupType, write=SetPopupType, default=2};
	__property TScreenTipItem* ScreenTip = {read=FScreenTip, write=SetScreenTip};
	__property TCustomScreenTipsManager* ScreenTipManager = {read=FScreenTipsManager, write=SetScreenTipsManager};
	__property bool Transparent = {read=FTransparent, write=SetTransparent, default=1};
	
__published:
	__property ShowHint = {default=1};
public:
	/* TWinControl.CreateParented */ inline __fastcall TCustomScreenTipsPopup(HWND ParentWindow) : Vcl::Controls::TCustomControl(ParentWindow) { }
	
private:
	void *__IScreenTipItem;	// IScreenTipItem 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FC7D9558-D3EC-4C4D-8E68-ADFEC71451B1}
	operator _di_IScreenTipItem()
	{
		_di_IScreenTipItem intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IScreenTipItem*(void) { return (IScreenTipItem*)&__IScreenTipItem; }
	#endif
	
};


class PASCALIMPLEMENTATION TScreenTipsPopup : public TCustomScreenTipsPopup
{
	typedef TCustomScreenTipsPopup inherited;
	
__published:
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property Associate;
	__property Glyph;
	__property PopupType = {default=2};
	__property ScreenTip;
	__property ScreenTipManager;
	__property Transparent = {default=1};
	__property Visible = {default=1};
public:
	/* TCustomScreenTipsPopup.Create */ inline __fastcall virtual TScreenTipsPopup(System::Classes::TComponent* AOwner) : TCustomScreenTipsPopup(AOwner) { }
	/* TCustomScreenTipsPopup.Destroy */ inline __fastcall virtual ~TScreenTipsPopup() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TScreenTipsPopup(HWND ParentWindow) : TCustomScreenTipsPopup(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const int cDefaultStartColor = int(16777215);
static const int cDefaultEndColor = int(-16777201);
static const int cDefaultBorderColor = int(0x767676);
static const System::Int8 cScreenTipHeaderSpacing = System::Int8(0xe);
static const System::Byte cScreenTipTextOnlyWidth = System::Byte(0xd2);
static const System::Word cScreenTipTextAndImageWidth = System::Word(0x13e);
static const System::Int8 cScreenTipMinimumHeight = System::Int8(0x32);
}	/* namespace Screentips */
}	/* namespace Vcl */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCL_SCREENTIPS)
using namespace Vcl::Screentips;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCL)
using namespace Vcl;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcl_ScreentipsHPP
