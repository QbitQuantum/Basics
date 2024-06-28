// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeDraw3D.pas' rev: 34.00 (Windows)

#ifndef Vcltee_Teedraw3dHPP
#define Vcltee_Teedraw3dHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.Types.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Menus.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teedraw3d
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDraw3D;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TDraw3DPaintEvent)(System::TObject* Sender, const System::Types::TRect &ARect);

class PASCALIMPLEMENTATION TDraw3D : public Vcltee::Teeprocs::TCustomTeePanelExtended
{
	typedef Vcltee::Teeprocs::TCustomTeePanelExtended inherited;
	
private:
	TDraw3DPaintEvent FOnPaint;
	
protected:
	bool IDontResetCanvas;
	virtual void __fastcall DoCustomPaint(const System::Types::TRect &UserRectangle);
	virtual void __fastcall InternalDraw(const System::Types::TRect &UserRectangle);
	
__published:
	__property BackImage;
	__property BackImageMode = {default=0};
	__property Border;
	__property BorderRound = {default=0};
	__property Emboss;
	__property Gradient;
	__property OnAfterDraw;
	__property BufferedDisplay = {default=1};
	__property MarginLeft = {index=0, default=3};
	__property MarginTop = {index=1, default=4};
	__property MarginRight = {index=2, default=3};
	__property MarginBottom = {index=3, default=4};
	__property MarginUnits = {default=0};
	__property Monochrome = {default=0};
	__property PrintProportional = {default=1};
	__property PrintResolution = {default=0};
	__property Shadow;
	__property View3D = {default=1};
	__property View3DOptions;
	__property TDraw3DPaintEvent OnPaint = {read=FOnPaint, write=FOnPaint};
	__property Align = {default=0};
	__property BevelInner = {default=0};
	__property BevelOuter = {default=2};
	__property BevelWidth = {default=1};
	__property BorderWidth = {default=0};
	__property Color = {default=-16777201};
	__property DragCursor = {default=-12};
	__property DragMode = {default=0};
	__property Enabled = {default=1};
	__property ParentColor = {default=0};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Visible = {default=1};
	__property Anchors = {default=3};
	__property AutoSize = {default=0};
	__property Constraints;
	__property DragKind = {default=0};
	__property Locked = {default=0};
	__property OnClick;
	__property OnContextPopup;
	__property OnDblClick;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnEndDrag;
	__property OnEnter;
	__property OnExit;
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnResize;
	__property OnMouseWheel;
	__property OnMouseWheelDown;
	__property OnMouseWheelUp;
	__property OnStartDrag;
	__property OnCanResize;
	__property OnConstrainedResize;
	__property OnDockDrop;
	__property OnDockOver;
	__property OnEndDock;
	__property OnGetSiteInfo;
	__property OnStartDock;
	__property OnUnDock;
	__property OnMouseEnter;
	__property OnMouseLeave;
public:
	/* TCustomTeePanelExtended.Create */ inline __fastcall virtual TDraw3D(System::Classes::TComponent* AOwner) : Vcltee::Teeprocs::TCustomTeePanelExtended(AOwner) { }
	/* TCustomTeePanelExtended.Destroy */ inline __fastcall virtual ~TDraw3D() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDraw3D(HWND ParentWindow) : Vcltee::Teeprocs::TCustomTeePanelExtended(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teedraw3d */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEDRAW3D)
using namespace Vcltee::Teedraw3d;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_Teedraw3dHPP
