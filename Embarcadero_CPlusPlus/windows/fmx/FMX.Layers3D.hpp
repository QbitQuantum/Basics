// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Layers3D.pas' rev: 34.00 (Windows)

#ifndef Fmx_Layers3dHPP
#define Fmx_Layers3dHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Messaging.hpp>
#include <System.Math.Vectors.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls3D.hpp>
#include <FMX.Graphics.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Layers3d
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAbstractLayer3D;
class DELPHICLASS TLayout3D;
class DELPHICLASS TSplitter3D;
class DELPHICLASS TSolidLayer3D;
class DELPHICLASS TImage3D;
class DELPHICLASS TCustomBufferLayer3D;
class DELPHICLASS TBufferLayer3D;
class DELPHICLASS TCustomLayer3D;
class DELPHICLASS TLayer3D;
class DELPHICLASS TTextLayer3D;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAbstractLayer3D : public Fmx::Controls3d::TControl3D
{
	typedef Fmx::Controls3d::TControl3D inherited;
	
private:
	Fmx::Types::TMouseMoveEvent FOnLayerMouseMove;
	Fmx::Types::TMouseEvent FOnLayerMouseDown;
	Fmx::Types::TMouseEvent FOnLayerMouseUp;
	bool FDisableLayerEvent;
	Fmx::Types::TAlignLayout FAlign;
	System::Uitypes::TAnchors FAnchors;
	Fmx::Types::TBounds* FMargins;
	Fmx::Types::TBounds* FPadding;
	System::Uitypes::TAlphaColor FModulationColor;
	int FResolution;
	int FLayerWidth;
	int FLayerHeight;
	float FLastWidth;
	float FLastHeight;
	bool FNeedAlign;
	bool FDisableAlign;
	int FScaleChangedId;
	bool FAnchorMove;
	System::Types::TPointF FAnchorRules;
	System::Types::TPointF FAnchorOrigin;
	System::Types::TPointF FOriginalParentSize;
	float FExplicitLeft;
	float FExplicitTop;
	float FExplicitWidth;
	float FExplicitHeight;
	virtual void __fastcall PaddingChanged(System::TObject* Sender);
	virtual void __fastcall MarginsChanged(System::TObject* Sender);
	void __fastcall SetResolution(const int Value);
	void __fastcall SetModulationColor(const System::Uitypes::TAlphaColor Value);
	bool __fastcall IsAnchorsStored();
	void __fastcall UpdateExplicitBounds();
	void __fastcall UpdateAnchorRules();
	void __fastcall ScaleChangedHandler(System::TObject* const Sender, System::Messaging::TMessageBase* const Msg);
	void __fastcall SetPadding(Fmx::Types::TBounds* const Value);
	void __fastcall SetMargins(Fmx::Types::TBounds* const Value);
	
protected:
	virtual void __fastcall DoAddObject(Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall MatrixChanged(System::TObject* Sender);
	virtual void __fastcall MouseMove3D(System::Classes::TShiftState Shift, float X, float Y, const System::Math::Vectors::TVector3D &RayPos, const System::Math::Vectors::TVector3D &RayDir);
	virtual void __fastcall MouseDown3D(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y, const System::Math::Vectors::TVector3D &RayPos, const System::Math::Vectors::TVector3D &RayDir);
	virtual void __fastcall MouseUp3D(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y, const System::Math::Vectors::TVector3D &RayPos, const System::Math::Vectors::TVector3D &RayDir);
	virtual void __fastcall Resize3D();
	virtual void __fastcall SetDepth(const float Value);
	virtual void __fastcall SetProjection(const Fmx::Types3d::TProjection Value);
	virtual Fmx::Types::_di_IControl __fastcall ObjectAtPoint(const System::Types::TPointF &P);
	virtual bool __fastcall DoRayCastIntersect(const System::Math::Vectors::TPoint3D &RayPos, const System::Math::Vectors::TPoint3D &RayDir, System::Math::Vectors::TPoint3D &Intersection);
	virtual void __fastcall ApplyEffect();
	virtual void __fastcall LayerMouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall LayerMouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall LayerMouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall LayerResized();
	virtual void __fastcall DoScaleChanged();
	virtual void __fastcall Realign();
	void __fastcall ChildrenAlignChanged();
	Fmx::Types::TAlignLayout __fastcall GetAlign();
	virtual void __fastcall SetAlign(const Fmx::Types::TAlignLayout Value);
	System::Uitypes::TAnchors __fastcall GetAnchors();
	virtual void __fastcall SetAnchors(const System::Uitypes::TAnchors Value);
	Fmx::Types::TBounds* __fastcall GetMargins();
	Fmx::Types::TBounds* __fastcall GetPadding();
	void __fastcall SetBounds(float X, float Y, float AWidth, float AHeight);
	bool __fastcall GetAllowAlign();
	System::Types::TPointF __fastcall GetAnchorRules();
	System::Types::TPointF __fastcall GetAnchorOrigin();
	System::Types::TPointF __fastcall GetOriginalParentSize();
	bool __fastcall GetAnchorMove();
	void __fastcall SetAnchorMove(bool Value);
	float __fastcall GetAlignableWidth();
	float __fastcall GetAlignableHeight();
	float __fastcall GetAlignableLeft();
	float __fastcall GetAlignableTop();
	virtual System::Types::TSizeF __fastcall GetAdjustSizeValue();
	virtual Fmx::Types::TAdjustType __fastcall GetAdjustType();
	virtual void __fastcall Loaded();
	__property int LayerWidth = {read=FLayerWidth, nodefault};
	__property int LayerHeight = {read=FLayerHeight, nodefault};
	__property int Resolution = {read=FResolution, write=SetResolution, nodefault};
	virtual void __fastcall SetParent(Fmx::Types::TFmxObject* const Value);
	
public:
	__fastcall virtual TAbstractLayer3D(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TAbstractLayer3D();
	__property Fmx::Types::TAlignLayout Align = {read=FAlign, write=SetAlign, default=0};
	__property System::Uitypes::TAnchors Anchors = {read=FAnchors, write=SetAnchors, stored=IsAnchorsStored, default=3};
	__property Fmx::Types::TBounds* Padding = {read=GetPadding, write=SetPadding};
	__property System::Uitypes::TAlphaColor ModulationColor = {read=FModulationColor, write=SetModulationColor, default=-1};
	__property Fmx::Types::TBounds* Margins = {read=GetMargins, write=SetMargins};
	__property Fmx::Types::TMouseMoveEvent OnLayerMouseMove = {read=FOnLayerMouseMove, write=FOnLayerMouseMove};
	__property Fmx::Types::TMouseEvent OnLayerMouseDown = {read=FOnLayerMouseDown, write=FOnLayerMouseDown};
	__property Fmx::Types::TMouseEvent OnLayerMouseUp = {read=FOnLayerMouseUp, write=FOnLayerMouseUp};
private:
	void *__IAlignRoot;	// Fmx::Types::IAlignRoot 
	void *__IAlignableObject;	// Fmx::Types::IAlignableObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {86DF30A6-0394-4A0E-8722-1F2CDB242CE8}
	operator Fmx::Types::_di_IAlignRoot()
	{
		Fmx::Types::_di_IAlignRoot intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IAlignRoot*(void) { return (Fmx::Types::IAlignRoot*)&__IAlignRoot; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {420D3E98-4433-4CBE-9767-0B494DF08354}
	operator Fmx::Types::_di_IAlignableObject()
	{
		Fmx::Types::_di_IAlignableObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IAlignableObject*(void) { return (Fmx::Types::IAlignableObject*)&__IAlignableObject; }
	#endif
	
};


class PASCALIMPLEMENTATION TLayout3D : public TAbstractLayer3D
{
	typedef TAbstractLayer3D inherited;
	
protected:
	virtual void __fastcall Render();
	
public:
	__fastcall virtual TLayout3D(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TLayout3D();
	
__published:
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property Height = {default=0};
	__property HitTest = {default=1};
	__property Locked = {default=0};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property Position;
	__property Projection = {default=0};
	__property RotationAngle;
	__property Scale;
	__property VisibleContextMenu = {default=1};
	__property TwoSide = {default=1};
	__property Visible = {default=1};
	__property Width = {default=0};
	__property ZWrite = {default=1};
	__property OnDragEnd;
	__property OnDragEnter;
	__property OnDragDrop;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnLayerMouseDown;
	__property OnLayerMouseMove;
	__property OnLayerMouseUp;
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnRender;
};


class PASCALIMPLEMENTATION TSplitter3D : public TAbstractLayer3D
{
	typedef TAbstractLayer3D inherited;
	
private:
	bool FPressed;
	TAbstractLayer3D* FControl;
	System::Types::TPointF FDownPos;
	float FMinSize;
	float FMaxSize;
	float FNewSize;
	float FOldSize;
	float FSplit;
	
protected:
	virtual void __fastcall Render();
	virtual void __fastcall SetAlign(const Fmx::Types::TAlignLayout Value);
	TAbstractLayer3D* __fastcall FindObject();
	void __fastcall CalcSplitSize(float X, float Y, float &NewSize, float &Split);
	void __fastcall UpdateSize(float X, float Y);
	bool __fastcall DoCanResize(float &NewSize);
	void __fastcall UpdateControlSize();
	virtual void __fastcall LayerMouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall LayerMouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall LayerMouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	
public:
	__fastcall virtual TSplitter3D(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSplitter3D();
	
__published:
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property Height = {default=0};
	__property HitTest = {default=1};
	__property Locked = {default=0};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property Position;
	__property Projection = {default=0};
	__property RotationAngle;
	__property Scale;
	__property VisibleContextMenu = {default=1};
	__property TwoSide = {default=1};
	__property Visible = {default=1};
	__property Width = {default=0};
	__property ZWrite = {default=1};
	__property OnDragEnd;
	__property OnDragEnter;
	__property OnDragDrop;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnLayerMouseDown;
	__property OnLayerMouseMove;
	__property OnLayerMouseUp;
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnRender;
};


class PASCALIMPLEMENTATION TSolidLayer3D : public TAbstractLayer3D
{
	typedef TAbstractLayer3D inherited;
	
protected:
	virtual void __fastcall Render();
	
public:
	__fastcall virtual TSolidLayer3D(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSolidLayer3D();
	
__published:
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property Height = {default=0};
	__property HitTest = {default=1};
	__property Locked = {default=0};
	__property Padding;
	__property ModulationColor = {default=-1};
	__property Opacity;
	__property Margins;
	__property Position;
	__property Projection = {default=0};
	__property RotationAngle;
	__property Scale;
	__property VisibleContextMenu = {default=1};
	__property TwoSide = {default=1};
	__property Visible = {default=1};
	__property Width = {default=0};
	__property ZWrite = {default=1};
	__property OnDragEnd;
	__property OnDragEnter;
	__property OnDragDrop;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnLayerMouseDown;
	__property OnLayerMouseMove;
	__property OnLayerMouseUp;
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnRender;
};


class PASCALIMPLEMENTATION TImage3D : public TAbstractLayer3D
{
	typedef TAbstractLayer3D inherited;
	
private:
	Fmx::Graphics::TBitmap* FBitmap;
	Fmx::Objects::TImageWrapMode FWrapMode;
	void __fastcall SetBitmap(Fmx::Graphics::TBitmap* const Value);
	void __fastcall SetWrapMode(const Fmx::Objects::TImageWrapMode Value);
	Fmx::Graphics::TBitmap* __fastcall GetBitmap();
	
protected:
	void __fastcall DoBitmapChanged(System::TObject* Sender);
	virtual void __fastcall Render();
	
public:
	__fastcall virtual TImage3D(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TImage3D();
	
__published:
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property Fmx::Graphics::TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property Height = {default=0};
	__property HitTest = {default=1};
	__property Locked = {default=0};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property Position;
	__property Projection = {default=0};
	__property RotationAngle;
	__property Scale;
	__property VisibleContextMenu = {default=1};
	__property TwoSide = {default=1};
	__property Visible = {default=1};
	__property Width = {default=0};
	__property Fmx::Objects::TImageWrapMode WrapMode = {read=FWrapMode, write=SetWrapMode, default=2};
	__property ZWrite = {default=1};
	__property OnDragEnd;
	__property OnDragEnter;
	__property OnDragDrop;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnLayerMouseDown;
	__property OnLayerMouseMove;
	__property OnLayerMouseUp;
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnRender;
private:
	void *__IBitmapObject;	// Fmx::Graphics::IBitmapObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5C17D001-47C1-462F-856D-8358B7B2C842}
	operator Fmx::Graphics::_di_IBitmapObject()
	{
		Fmx::Graphics::_di_IBitmapObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Graphics::IBitmapObject*(void) { return (Fmx::Graphics::IBitmapObject*)&__IBitmapObject; }
	#endif
	
};


class PASCALIMPLEMENTATION TCustomBufferLayer3D : public TAbstractLayer3D
{
	typedef TAbstractLayer3D inherited;
	
private:
	System::Classes::TNotifyEvent FOnUpdateBuffer;
	
protected:
	Fmx::Graphics::TBitmap* FBuffer;
	virtual void __fastcall BeforeRender();
	virtual void __fastcall Render();
	virtual Fmx::Graphics::TBitmap* __fastcall GetBitmap();
	virtual void __fastcall LayerResized();
	virtual void __fastcall DoScaleChanged();
	virtual void __fastcall DoUpdateBuffer();
	__property System::Classes::TNotifyEvent OnUpdateBuffer = {read=FOnUpdateBuffer, write=FOnUpdateBuffer};
	
public:
	__fastcall virtual TCustomBufferLayer3D(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBufferLayer3D();
	__property Fmx::Graphics::TBitmap* Buffer = {read=FBuffer};
};


class PASCALIMPLEMENTATION TBufferLayer3D : public TCustomBufferLayer3D
{
	typedef TCustomBufferLayer3D inherited;
	
__published:
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property Height = {default=0};
	__property HitTest = {default=1};
	__property Locked = {default=0};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property Position;
	__property Projection = {default=0};
	__property Resolution;
	__property RotationAngle;
	__property Scale;
	__property VisibleContextMenu = {default=1};
	__property TwoSide = {default=1};
	__property Visible = {default=1};
	__property Width = {default=0};
	__property ZWrite = {default=1};
	__property OnDragEnd;
	__property OnDragEnter;
	__property OnDragDrop;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnLayerMouseDown;
	__property OnLayerMouseMove;
	__property OnLayerMouseUp;
	__property OnUpdateBuffer;
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnRender;
public:
	/* TCustomBufferLayer3D.Create */ inline __fastcall virtual TBufferLayer3D(System::Classes::TComponent* AOwner) : TCustomBufferLayer3D(AOwner) { }
	/* TCustomBufferLayer3D.Destroy */ inline __fastcall virtual ~TBufferLayer3D() { }
	
};


class PASCALIMPLEMENTATION TCustomLayer3D : public TCustomBufferLayer3D
{
	typedef TCustomBufferLayer3D inherited;
	
	
private:
	typedef System::DynamicArray<System::Types::TRectF> _TCustomLayer3D__1;
	
	
private:
	static const System::Int8 InitialControlsCapacity = System::Int8(0xa);
	
	Fmx::Graphics::TBrush* FFill;
	bool FTransparency;
	bool FDrawing;
	Fmx::Controls::TStyleBook* FStyleBook;
	Fmx::Controls::TStyledControl* FActiveControl;
	bool FAnimatedCaret;
	System::UnicodeString FStyleLookup;
	bool FNeedStyleLookup;
	Fmx::Controls::TControl* FResourceLink;
	Fmx::Controls::TOnPaintEvent FOnPaint;
	int FStyleChangedId;
	System::Generics::Collections::TList__1<Fmx::Controls::TControl*>* FControls;
	int FDisableUpdating;
	void __fastcall SetActiveControl(Fmx::Controls::TStyledControl* AControl);
	void __fastcall SetFill(Fmx::Graphics::TBrush* const Value);
	void __fastcall FillChanged(System::TObject* Sender);
	void __fastcall StyleChangedHandler(System::TObject* const Sender, System::Messaging::TMessageBase* const Msg);
	Fmx::Graphics::TCanvas* __fastcall GetCanvas();
	int __fastcall GetUpdateRectsCount();
	System::Types::TRectF __fastcall GetUpdateRect(const int Index);
	Fmx::Controls::TStyleBook* __fastcall GetStyleBook();
	HIDESBASE System::Types::TPointF __fastcall LocalToScreen(const System::Types::TPointF &P);
	HIDESBASE System::Types::TPointF __fastcall ScreenToLocal(const System::Types::TPointF &P);
	void __fastcall SetStyleBook(Fmx::Controls::TStyleBook* const Value);
	float __fastcall GetSceneScale();
	void __fastcall ChangeScrollingState(Fmx::Controls::TControl* const AControl, const bool Active);
	void __fastcall DisableUpdating();
	void __fastcall EnableUpdating();
	float __fastcall GetContainerWidth();
	float __fastcall GetContainerHeight();
	void __fastcall SetStyleLookup(const System::UnicodeString Value);
	
protected:
	_TCustomLayer3D__1 FUpdateRects;
	virtual void __fastcall DoUpdateBuffer();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual Fmx::Types::_di_IControl __fastcall FindTarget(const System::Types::TPointF &P, const Fmx::Types::TDragObject &Data);
	virtual void __fastcall SetVisible(const bool Value);
	virtual void __fastcall DoScaleChanged();
	virtual void __fastcall DoStyleChanged();
	virtual void __fastcall DoAddObject(Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall DoRemoveObject(Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall DoDeleteChildren();
	virtual void __fastcall ChangeChildren();
	virtual void __fastcall ApplyStyleLookup();
	Fmx::Controls::TControl* __fastcall GetStyleObject();
	virtual void __fastcall DoPaint(Fmx::Graphics::TCanvas* const Canvas, const System::Types::TRectF &ARect);
	
public:
	__fastcall virtual TCustomLayer3D(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomLayer3D();
	void __fastcall Invalidate();
	void __fastcall AddUpdateRect(const System::Types::TRectF &R);
	__property Fmx::Graphics::TCanvas* Canvas = {read=GetCanvas};
	__property Fmx::Controls::TStyledControl* ActiveControl = {read=FActiveControl, write=SetActiveControl};
	__property bool AnimatedCaret = {read=FAnimatedCaret, write=FAnimatedCaret, default=1};
	__property Fmx::Graphics::TBrush* Fill = {read=FFill, write=SetFill};
	__property Fmx::Controls::TStyleBook* StyleBook = {read=FStyleBook, write=SetStyleBook};
	__property System::UnicodeString StyleLookup = {read=FStyleLookup, write=SetStyleLookup};
	__property bool Transparency = {read=FTransparency, write=FTransparency, nodefault};
	__property Fmx::Controls::TOnPaintEvent OnPaint = {read=FOnPaint, write=FOnPaint};
private:
	void *__IContainerObject;	// Fmx::Types::IContainerObject 
	void *__IScene;	// Fmx::Controls::IScene 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DE635E60-CB00-4741-92BB-3B8F1F29A67C}
	operator Fmx::Types::_di_IContainerObject()
	{
		Fmx::Types::_di_IContainerObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IContainerObject*(void) { return (Fmx::Types::IContainerObject*)&__IContainerObject; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16DB110E-DA7D-4E75-BC2D-999FA12E45F5}
	operator Fmx::Controls::_di_IScene()
	{
		Fmx::Controls::_di_IScene intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Controls::IScene*(void) { return (Fmx::Controls::IScene*)&__IScene; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BA1AE6C6-FCF7-43E2-92AA-2869FF203309}
	operator Fmx::Controls::_di_IStyleBookOwner()
	{
		Fmx::Controls::_di_IStyleBookOwner intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Controls::IStyleBookOwner*(void) { return (Fmx::Controls::IStyleBookOwner*)&__IScene; }
	#endif
	
};


class PASCALIMPLEMENTATION TLayer3D : public TCustomLayer3D
{
	typedef TCustomLayer3D inherited;
	
__published:
	__property ActiveControl;
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property AnimatedCaret = {default=1};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property Fill;
	__property Height = {default=0};
	__property HitTest = {default=1};
	__property Locked = {default=0};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property Position;
	__property Projection = {default=0};
	__property Resolution;
	__property RotationAngle;
	__property Scale;
	__property VisibleContextMenu = {default=1};
	__property StyleBook;
	__property StyleLookup = {default=0};
	__property Transparency = {default=0};
	__property TwoSide = {default=1};
	__property Visible = {default=1};
	__property Width = {default=0};
	__property ZWrite = {default=1};
	__property OnDragEnd;
	__property OnDragEnter;
	__property OnDragDrop;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnLayerMouseMove;
	__property OnLayerMouseDown;
	__property OnLayerMouseUp;
	__property OnPaint;
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnRender;
public:
	/* TCustomLayer3D.Create */ inline __fastcall virtual TLayer3D(System::Classes::TComponent* AOwner) : TCustomLayer3D(AOwner) { }
	/* TCustomLayer3D.Destroy */ inline __fastcall virtual ~TLayer3D() { }
	
};


class PASCALIMPLEMENTATION TTextLayer3D : public TCustomLayer3D
{
	typedef TCustomLayer3D inherited;
	
private:
	Fmx::Objects::TText* FText;
	System::UnicodeString __fastcall GetText();
	void __fastcall SetText(const System::UnicodeString Value);
	Fmx::Graphics::TFont* __fastcall GetFont();
	void __fastcall SetFont(Fmx::Graphics::TFont* const Value);
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	
protected:
	virtual void __fastcall ApplyStyleLookup();
	
public:
	__fastcall virtual TTextLayer3D(System::Classes::TComponent* AOwner);
	
__published:
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, nodefault};
	__property Fmx::Graphics::TFont* Font = {read=GetFont, write=SetFont};
	__property Height = {default=0};
	__property HitTest = {default=1};
	__property Locked = {default=0};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property Position;
	__property Projection = {default=0};
	__property Resolution;
	__property RotationAngle;
	__property Scale;
	__property VisibleContextMenu = {default=1};
	__property System::UnicodeString Text = {read=GetText, write=SetText};
	__property TwoSide = {default=1};
	__property Visible = {default=1};
	__property Width = {default=0};
	__property ZWrite = {default=1};
	__property OnDragEnd;
	__property OnDragEnter;
	__property OnDragDrop;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnLayerMouseMove;
	__property OnLayerMouseDown;
	__property OnLayerMouseUp;
	__property OnPaint;
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnRender;
public:
	/* TCustomLayer3D.Destroy */ inline __fastcall virtual ~TTextLayer3D() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Layers3d */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_LAYERS3D)
using namespace Fmx::Layers3d;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Layers3dHPP
