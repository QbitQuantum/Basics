// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeePreviewPanel.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeepreviewpanelHPP
#define Vcltee_TeepreviewpanelHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Printers.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.Types.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.Menus.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teepreviewpanel
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPreviewChartPen;
class DELPHICLASS TTeePanelsList;
class DELPHICLASS TTeePreviewPanel;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TTeePreviewPanelOrientation : unsigned char { ppoDefault, ppoPortrait, ppoLandscape };

typedef void __fastcall (__closure *TOnChangeMarginsEvent)(System::TObject* Sender, bool DisableProportional, const System::Types::TRect &NewMargins);

typedef void __fastcall (__closure *TOnGetPaperRect)(System::TObject* Sender, System::Types::TRect &PaperRect);

class PASCALIMPLEMENTATION TPreviewChartPen : public Vcltee::Tecanvas::TTeePen
{
	typedef Vcltee::Tecanvas::TTeePen inherited;
	
__published:
	__property EndStyle = {default=2};
	__property Style = {default=2};
	__property SmallDots = {default=1};
public:
	/* TTeePen.Create */ inline __fastcall TPreviewChartPen(const System::Classes::TNotifyEvent OnChangeEvent) : Vcltee::Tecanvas::TTeePen(OnChangeEvent) { }
	/* TTeePen.Destroy */ inline __fastcall virtual ~TPreviewChartPen() { }
	
};


enum DECLSPEC_DENUM TeePreviewZones : unsigned char { teePrev_None, teePrev_Left, teePrev_Top, teePrev_Right, teePrev_Bottom, teePrev_Image, teePrev_LeftTop, teePrev_RightTop, teePrev_LeftBottom, teePrev_RightBottom };

class PASCALIMPLEMENTATION TTeePanelsList : public System::Generics::Collections::TList__1<Vcltee::Teeprocs::TCustomTeePanel*>
{
	typedef System::Generics::Collections::TList__1<Vcltee::Teeprocs::TCustomTeePanel*> inherited;
	
public:
	/* {System_Generics_Collections}TList<VCLTee_TeeProcs_TCustomTeePanel>.Create */ inline __fastcall TTeePanelsList()/* overload */ : System::Generics::Collections::TList__1<Vcltee::Teeprocs::TCustomTeePanel*>() { }
	/* {System_Generics_Collections}TList<VCLTee_TeeProcs_TCustomTeePanel>.Create */ inline __fastcall TTeePanelsList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<Vcltee::Teeprocs::TCustomTeePanel*> > AComparer)/* overload */ : System::Generics::Collections::TList__1<Vcltee::Teeprocs::TCustomTeePanel*>(AComparer) { }
	/* {System_Generics_Collections}TList<VCLTee_TeeProcs_TCustomTeePanel>.Create */ inline __fastcall TTeePanelsList(System::Generics::Collections::TEnumerable__1<Vcltee::Teeprocs::TCustomTeePanel*>* const Collection)/* overload */ : System::Generics::Collections::TList__1<Vcltee::Teeprocs::TCustomTeePanel*>(Collection) { }
	/* {System_Generics_Collections}TList<VCLTee_TeeProcs_TCustomTeePanel>.Destroy */ inline __fastcall virtual ~TTeePanelsList() { }
	
};


class PASCALIMPLEMENTATION TTeePreviewPanel : public Vcltee::Teeprocs::TCustomTeePanelExtended
{
	typedef Vcltee::Teeprocs::TCustomTeePanelExtended inherited;
	
private:
	bool FAllowResize;
	bool FAllowMove;
	bool FAsBitmap;
	TTeePanelsList* FPanels;
	bool FDragImage;
	TPreviewChartPen* FMargins;
	TTeePreviewPanelOrientation FOrientation;
	TOnChangeMarginsEvent FOnChangeMargins;
	TOnGetPaperRect FOnGetPaperRect;
	System::Uitypes::TColor FPaperColor;
	Vcltee::Tecanvas::TTeeShadow* FPaperShadow;
	bool FShowImage;
	bool FSmoothBitmap;
	System::UnicodeString FTitle;
	TeePreviewZones IDragged;
	int OldX;
	int OldY;
	System::Types::TRect OldRect;
	bool IOldShowImage;
	void __fastcall CheckPrinterOrientation();
	Vcltee::Teeprocs::TCustomTeePanel* __fastcall GetPanel();
	Vcl::Graphics::TBitmap* __fastcall GetPrintingBitmap(Vcltee::Teeprocs::TCustomTeePanel* const APanel);
	System::Uitypes::TColor __fastcall GetShadowColor();
	int __fastcall GetShadowSize();
	int __fastcall PrinterCount();
	void __fastcall SendAsBitmap(Vcltee::Teeprocs::TCustomTeePanel* const APanel, Vcl::Graphics::TCanvas* const ACanvas, const System::Types::TRect &R)/* overload */;
	void __fastcall SendAsBitmap(Vcltee::Teeprocs::TCustomTeePanel* const APanel, const System::Types::TRect &R)/* overload */;
	void __fastcall SetAsBitmap(bool Value);
	HIDESBASE void __fastcall SetMargins(TPreviewChartPen* const Value);
	void __fastcall SetOrientation(const TTeePreviewPanelOrientation Value);
	void __fastcall SetPanel(Vcltee::Teeprocs::TCustomTeePanel* const Value);
	void __fastcall SetPaperColor(System::Uitypes::TColor Value);
	void __fastcall SetPaperShadow(Vcltee::Tecanvas::TTeeShadow* const Value);
	void __fastcall SetShadowColor(System::Uitypes::TColor Value);
	void __fastcall SetShadowSize(int Value);
	void __fastcall SetShowImage(bool Value);
	void __fastcall SetSmoothBitmap(const bool Value);
	
protected:
	System::Types::TRect __fastcall CalcImagePrintMargins(Vcltee::Teeprocs::TCustomTeePanel* const APanel);
	void __fastcall DrawPaper();
	void __fastcall DrawPanelImage(Vcltee::Teeprocs::TCustomTeePanel* const APanel);
	void __fastcall DrawMargins(const System::Types::TRect &R);
	virtual void __fastcall InternalDraw(const System::Types::TRect &UserRectangle);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	TeePreviewZones __fastcall WhereIsCursor(const int x, const int y);
	
public:
	System::Types::TRect ImageRect;
	System::Types::TRect PaperRect;
	__fastcall virtual TTeePreviewPanel(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TTeePreviewPanel();
	HIDESBASE void __fastcall Print();
	__property TTeePanelsList* Panels = {read=FPanels};
	__property System::Uitypes::TColor ShadowColor = {read=GetShadowColor, write=SetShadowColor, nodefault};
	__property int ShadowSize = {read=GetShadowSize, write=SetShadowSize, nodefault};
	
__published:
	__property bool AllowResize = {read=FAllowResize, write=FAllowResize, default=1};
	__property bool AllowMove = {read=FAllowMove, write=FAllowMove, default=1};
	__property bool AsBitmap = {read=FAsBitmap, write=SetAsBitmap, default=0};
	__property bool DragImage = {read=FDragImage, write=FDragImage, default=0};
	__property TPreviewChartPen* Margins = {read=FMargins, write=SetMargins};
	__property TTeePreviewPanelOrientation Orientation = {read=FOrientation, write=SetOrientation, default=0};
	__property Vcltee::Teeprocs::TCustomTeePanel* Panel = {read=GetPanel, write=SetPanel};
	__property System::Uitypes::TColor PaperColor = {read=FPaperColor, write=SetPaperColor, default=16777215};
	__property Vcltee::Tecanvas::TTeeShadow* PaperShadow = {read=FPaperShadow, write=SetPaperShadow};
	__property Shadow;
	__property bool ShowImage = {read=FShowImage, write=SetShowImage, default=1};
	__property bool SmoothBitmap = {read=FSmoothBitmap, write=SetSmoothBitmap, default=1};
	__property System::UnicodeString Title = {read=FTitle, write=FTitle};
	__property TOnChangeMarginsEvent OnChangeMargins = {read=FOnChangeMargins, write=FOnChangeMargins};
	__property TOnGetPaperRect OnGetPaperRect = {read=FOnGetPaperRect, write=FOnGetPaperRect};
	__property BackImage;
	__property BackImageMode = {default=0};
	__property Border;
	__property BorderRound = {default=0};
	__property Gradient;
	__property Align = {default=0};
	__property BevelInner = {default=0};
	__property BevelOuter = {default=2};
	__property BevelWidth = {default=1};
	__property BorderWidth = {default=0};
	__property DragMode = {default=0};
	__property Color = {default=-16777201};
	__property DragCursor = {default=-12};
	__property Enabled = {default=1};
	__property ParentColor = {default=0};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Touch;
	__property Visible = {default=1};
	__property Anchors = {default=3};
	__property AutoSize = {default=0};
	__property Constraints;
	__property DragKind = {default=0};
	__property Locked = {default=0};
	__property OnAfterDraw;
	__property OnClick;
	__property OnContextPopup;
	__property OnDblClick;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnEndDrag;
	__property OnStartDrag;
	__property OnEnter;
	__property OnExit;
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnResize;
	__property OnMouseWheel;
	__property OnMouseWheelDown;
	__property OnMouseWheelUp;
	__property OnCanResize;
	__property OnConstrainedResize;
	__property OnDockDrop;
	__property OnDockOver;
	__property OnEndDock;
	__property OnGetSiteInfo;
	__property OnStartDock;
	__property OnUnDock;
	__property OnGesture;
public:
	/* TWinControl.CreateParented */ inline __fastcall TTeePreviewPanel(HWND ParentWindow) : Vcltee::Teeprocs::TCustomTeePanelExtended(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teepreviewpanel */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEPREVIEWPANEL)
using namespace Vcltee::Teepreviewpanel;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeepreviewpanelHPP
