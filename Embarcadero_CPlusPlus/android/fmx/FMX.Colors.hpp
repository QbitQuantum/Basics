// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Colors.pas' rev: 34.00 (Android)

#ifndef Fmx_ColorsHPP
#define Fmx_ColorsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.Rtti.hpp>
#include <System.UITypes.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Pickers.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Layouts.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Colors
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS THueTrackBar;
class DELPHICLASS TAlphaTrackBar;
class DELPHICLASS TBWTrackBar;
class DELPHICLASS TColorBox;
class DELPHICLASS TColorQuad;
class DELPHICLASS TColorPicker;
class DELPHICLASS TGradientEdit;
class DELPHICLASS TColorPanel;
class DELPHICLASS TComboColorBox;
class DELPHICLASS TColorButton;
class DELPHICLASS TColorListBox;
class DELPHICLASS TCustomColorComboBox;
class DELPHICLASS TColorComboBox;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION THueTrackBar : public Fmx::Stdctrls::TBitmapTrackBar
{
	typedef Fmx::Stdctrls::TBitmapTrackBar inherited;
	
private:
	bool __fastcall IsValueStored();
	
protected:
	virtual void __fastcall FillBitmap();
	
public:
	__fastcall virtual THueTrackBar(System::Classes::TComponent* AOwner)/* overload */;
	
__published:
	__property Value = {stored=IsValueStored};
public:
	/* TBitmapTrackBar.Destroy */ inline __fastcall virtual ~THueTrackBar() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAlphaTrackBar : public Fmx::Stdctrls::TBitmapTrackBar
{
	typedef Fmx::Stdctrls::TBitmapTrackBar inherited;
	
private:
	bool __fastcall IsValueStored();
	
protected:
	virtual void __fastcall FillBitmap();
	
public:
	__fastcall virtual TAlphaTrackBar(System::Classes::TComponent* AOwner)/* overload */;
	
__published:
	__property Value = {stored=IsValueStored};
public:
	/* TBitmapTrackBar.Destroy */ inline __fastcall virtual ~TAlphaTrackBar() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBWTrackBar : public Fmx::Stdctrls::TBitmapTrackBar
{
	typedef Fmx::Stdctrls::TBitmapTrackBar inherited;
	
private:
	bool __fastcall IsValueStored();
	
protected:
	virtual void __fastcall FillBitmap();
	
public:
	__fastcall virtual TBWTrackBar(System::Classes::TComponent* AOwner)/* overload */;
	
__published:
	__property Value = {stored=IsValueStored};
public:
	/* TBitmapTrackBar.Destroy */ inline __fastcall virtual ~TBWTrackBar() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TColorBox : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
private:
	System::Uitypes::TAlphaColor FColor;
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	
protected:
	virtual void __fastcall Paint();
	
public:
	__fastcall virtual TColorBox(System::Classes::TComponent* AOwner);
	
__published:
	__property Align = {default=0};
	__property Anchors;
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=SetColor, nodefault};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Locked = {default=0};
	__property Height;
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TouchTargetExpansion;
	__property Visible = {default=1};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnClick;
	__property OnDblClick;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
public:
	/* TControl.Destroy */ inline __fastcall virtual ~TColorBox() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TColorQuad : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
private:
	TColorBox* FColorBox;
	Fmx::Graphics::TBitmap* FColorBitmap;
	float FHue;
	float FSat;
	float FLum;
	System::Classes::TNotifyEvent FOnChange;
	float FAlpha;
	bool FPendingChanges;
	void __fastcall SetHue(const float Value);
	void __fastcall SetLum(const float Value);
	void __fastcall SetSat(const float Value);
	void __fastcall SetAlpha(const float Value);
	void __fastcall SetColorBox(TColorBox* const Value);
	void __fastcall PreviewColor(const float ValHue, const float ValLum, const float ValSat, const float ValAlpha);
	void __fastcall SetColor(const float ValHue, const float ValLum, const float ValSat, const float ValAlpha);
	bool __fastcall GetIsTracking();
	
protected:
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual System::Types::TRectF __fastcall DoGetUpdateRect();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall Paint();
	
public:
	virtual bool __fastcall PointInObjectLocal(float X, float Y);
	__fastcall virtual TColorQuad(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TColorQuad();
	
__published:
	__property float Alpha = {read=FAlpha, write=SetAlpha};
	__property Align = {default=0};
	__property Anchors;
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property TColorBox* ColorBox = {read=FColorBox, write=SetColorBox};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Locked = {default=0};
	__property Height;
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property float Hue = {read=FHue, write=SetHue};
	__property float Lum = {read=FLum, write=SetLum};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property float Sat = {read=FSat, write=SetSat};
	__property Scale;
	__property Size;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TouchTargetExpansion;
	__property Visible = {default=1};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnClick;
	__property OnDblClick;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TColorPicker : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
private:
	Fmx::Graphics::TBitmap* FHueBitmap;
	float FHue;
	TColorQuad* FColorQuad;
	void __fastcall SetHue(const float Value);
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	
protected:
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual System::Types::TRectF __fastcall GetAbsoluteRect();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall Paint();
	
public:
	virtual bool __fastcall PointInObjectLocal(float X, float Y);
	__fastcall virtual TColorPicker(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TColorPicker();
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, nodefault};
	
__published:
	__property Align = {default=0};
	__property Anchors;
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property TColorQuad* ColorQuad = {read=FColorQuad, write=FColorQuad};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Locked = {default=0};
	__property Height;
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property float Hue = {read=FHue, write=SetHue};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TouchTargetExpansion;
	__property Visible = {default=1};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnClick;
	__property OnDblClick;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TGradientEdit : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
private:
	Fmx::Graphics::TBitmap* FBitmap;
	Fmx::Graphics::TGradient* FGradient;
	int FCurrentPoint;
	bool FCurrentPointInvisible;
	bool FMoving;
	System::Classes::TNotifyEvent FOnChange;
	System::Classes::TNotifyEvent FOnSelectPoint;
	TColorPicker* FColorPicker;
	void __fastcall SetGradient(Fmx::Graphics::TGradient* const Value);
	System::Types::TRectF __fastcall GetPointRect(const int Point);
	void __fastcall DoChanged(System::TObject* Sender);
	void __fastcall SetCurrentPoint(const int Value);
	void __fastcall SetColorPicker(TColorPicker* const Value);
	
protected:
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall Paint();
	
public:
	__fastcall virtual TGradientEdit(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TGradientEdit();
	void __fastcall UpdateGradient();
	__property Fmx::Graphics::TGradient* Gradient = {read=FGradient, write=SetGradient};
	__property int CurrentPoint = {read=FCurrentPoint, write=SetCurrentPoint, nodefault};
	
__published:
	__property Align = {default=0};
	__property Anchors;
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property TColorPicker* ColorPicker = {read=FColorPicker, write=SetColorPicker};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Locked = {default=0};
	__property Height;
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TouchTargetExpansion;
	__property Visible = {default=1};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnClick;
	__property OnDblClick;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
	__property System::Classes::TNotifyEvent OnSelectPoint = {read=FOnSelectPoint, write=FOnSelectPoint};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TColorPanel : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
private:
	System::Classes::TNotifyEvent FOnChange;
	TColorQuad* FColorQuad;
	TAlphaTrackBar* FAlphaTrack;
	THueTrackBar* FHueTrack;
	TColorBox* FColorBox;
	bool FUseAlpha;
	bool FOwnerObserves;
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	void __fastcall SetColorBox(TColorBox* const Value);
	void __fastcall SetUseAlpha(const bool Value);
	
protected:
	virtual System::Classes::TObservers* __fastcall GetObservers();
	virtual bool __fastcall CanObserve(const int ID);
	virtual System::Rtti::TValue __fastcall GetData();
	void __fastcall DoAlphaChange(System::TObject* Sender);
	void __fastcall DoHueChange(System::TObject* Sender);
	void __fastcall DoQuadChange(System::TObject* Sender);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TColorPanel(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TColorPanel();
	void __fastcall OwnerObserves();
	
__published:
	__property Align = {default=0};
	__property Anchors;
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, nodefault};
	__property TColorBox* ColorBox = {read=FColorBox, write=SetColorBox};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Locked = {default=0};
	__property Height;
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TouchTargetExpansion;
	__property bool UseAlpha = {read=FUseAlpha, write=SetUseAlpha, default=1};
	__property Visible = {default=1};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnClick;
	__property OnDblClick;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TComboColorBox : public Fmx::Controls::TStyledControl
{
	typedef Fmx::Controls::TStyledControl inherited;
	
private:
	Fmx::Controls::TPopup* FPopup;
	TColorPanel* FColorPanel;
	TColorBox* FColorBox;
	Fmx::Edit::TEdit* FColorText;
	Fmx::Controls::TPlacement FPlacement;
	System::Classes::TNotifyEvent FOnChange;
	System::Uitypes::TAlphaColor __fastcall GetValue();
	void __fastcall SetValue(const System::Uitypes::TAlphaColor Value);
	bool __fastcall GetUseAlpha();
	void __fastcall SetUseAlpha(const bool Value);
	void __fastcall CalcSize();
	
protected:
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual void __fastcall ApplyStyle();
	virtual bool __fastcall CanObserve(const int ID);
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	void __fastcall DoContentPaint(System::TObject* Sender, Fmx::Graphics::TCanvas* Canvas, const System::Types::TRectF &ARect);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall ParentChanged();
	virtual void __fastcall DoColorChange(System::TObject* Sender);
	virtual void __fastcall DoTextChange(System::TObject* Sender);
	virtual void __fastcall DoValidating(System::TObject* Sender, System::UnicodeString &Text);
	
public:
	__fastcall virtual TComboColorBox(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TComboColorBox();
	void __fastcall DropDown();
	
__published:
	__property Align = {default=0};
	__property Anchors;
	__property CanFocus = {default=1};
	__property CanParentFocus = {default=0};
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property System::Uitypes::TAlphaColor Color = {read=GetValue, write=SetValue, nodefault};
	__property Cursor = {default=0};
	__property DisableFocusEffect = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Locked = {default=0};
	__property Height;
	__property HelpContext = {default=0};
	__property HelpKeyword = {default=0};
	__property HelpType = {default=1};
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property StyleLookup = {default=0};
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TouchTargetExpansion;
	__property bool UseAlpha = {read=GetUseAlpha, write=SetUseAlpha, default=1};
	__property Visible = {default=1};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property OnApplyStyleLookup;
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnClick;
	__property OnDblClick;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TColorButton : public Fmx::Stdctrls::TCustomButton
{
	typedef Fmx::Stdctrls::TCustomButton inherited;
	
private:
	Fmx::Objects::TShape* FFill;
	System::Uitypes::TAlphaColor FColor;
	System::Classes::TNotifyEvent FOnChange;
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	
protected:
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	
public:
	__fastcall virtual TColorButton(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TColorButton();
	
__published:
	__property Align = {default=0};
	__property AutoTranslate = {default=0};
	__property CanFocus = {default=1};
	__property CanParentFocus = {default=0};
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=SetColor, nodefault};
	__property ControlType = {default=0};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property DisableFocusEffect = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Locked = {default=0};
	__property Height;
	__property HelpContext = {default=0};
	__property HelpKeyword = {default=0};
	__property HelpType = {default=1};
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property StaysPressed = {default=0};
	__property IsPressed = {default=0};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property StyleLookup = {default=0};
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TouchTargetExpansion;
	__property Visible = {default=1};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property OnApplyStyleLookup;
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnClick;
	__property OnDblClick;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TColorListBox : public Fmx::Listbox::TCustomListBox
{
	typedef Fmx::Listbox::TCustomListBox inherited;
	
private:
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall DoItemApplyStyleLookup(System::TObject* Sender);
	
protected:
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	void __fastcall RebuildList();
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	
public:
	__fastcall virtual TColorListBox(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TColorListBox();
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, default=0};
	__property Align = {default=0};
	__property AllowDrag = {default=0};
	__property AlternatingRowBackground = {default=0};
	__property Anchors;
	__property CanFocus = {default=1};
	__property CanParentFocus = {default=0};
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property Cursor = {default=0};
	__property DisableFocusEffect = {default=1};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Locked = {default=0};
	__property Height;
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property ItemIndex = {default=-1};
	__property ItemHeight = {default=0};
	__property ItemWidth = {default=0};
	__property DefaultItemStyles;
	__property GroupingKind = {default=0};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property StyleLookup = {default=0};
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Visible = {default=1};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property OnApplyStyleLookup;
	__property OnChange;
	__property OnDragChange;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnItemClick;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomColorComboBox : public Fmx::Listbox::TCustomComboBox
{
	typedef Fmx::Listbox::TCustomComboBox inherited;
	
private:
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall DoItemApplyStyleLookup(System::TObject* Sender);
	void __fastcall ReadItemsStrings(System::Classes::TReader* Reader);
	
protected:
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	void __fastcall RebuildList();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	
public:
	__fastcall virtual TCustomColorComboBox(System::Classes::TComponent* AOwner)/* overload */;
	
__published:
	__property DropDownKind;
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, nodefault};
public:
	/* TCustomComboBox.Destroy */ inline __fastcall virtual ~TCustomColorComboBox() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TColorComboBox : public TCustomColorComboBox
{
	typedef TCustomColorComboBox inherited;
	
public:
	__property PlacementRectangle;
	
__published:
	__property Color;
	__property Align = {default=0};
	__property Anchors;
	__property CanFocus = {default=1};
	__property CanParentFocus = {default=0};
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property Cursor = {default=0};
	__property DisableFocusEffect = {default=1};
	__property DragMode = {default=0};
	__property DropDownCount = {default=8};
	__property DropDownKind;
	__property EnableDragHighlight = {default=1};
	__property Enabled;
	__property Locked = {default=0};
	__property Height;
	__property HelpContext = {default=0};
	__property HelpKeyword = {default=0};
	__property HelpType = {default=1};
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property ItemIndex = {default=-1};
	__property ItemWidth = {default=0};
	__property ItemHeight = {default=0};
	__property ListBoxResource = {default=0};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property Placement = {default=0};
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property StyleLookup = {default=0};
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TouchTargetExpansion;
	__property Visible = {default=1};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property OnApplyStyleLookup;
	__property OnChange;
	__property OnClosePopup;
	__property OnPopup;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnClick;
	__property OnDblClick;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
public:
	/* TCustomColorComboBox.Create */ inline __fastcall virtual TColorComboBox(System::Classes::TComponent* AOwner)/* overload */ : TCustomColorComboBox(AOwner) { }
	
public:
	/* TCustomComboBox.Destroy */ inline __fastcall virtual ~TColorComboBox() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 ColorPickSize = System::Int8(0xa);
extern DELPHI_PACKAGE void __fastcall MakeChessBoardBrush(Fmx::Graphics::TBrushBitmap* ABrushBitmap, const float AChessStep);
}	/* namespace Colors */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_COLORS)
using namespace Fmx::Colors;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_ColorsHPP
