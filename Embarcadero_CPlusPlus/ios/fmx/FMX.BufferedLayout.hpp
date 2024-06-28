// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.BufferedLayout.pas' rev: 34.00 (iOS)

#ifndef Fmx_BufferedlayoutHPP
#define Fmx_BufferedlayoutHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Math.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Messaging.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Layouts.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Bufferedlayout
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBufferedScene;
class DELPHICLASS TCustomBufferedLayout;
class DELPHICLASS TBufferedLayout;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBufferedScene : public Fmx::Types::TFmxObject
{
	typedef Fmx::Types::TFmxObject inherited;
	
	
private:
	typedef System::DynamicArray<System::Types::TRectF> _TBufferedScene__1;
	
	
private:
	static Fmx::Platform::_di_IFMXScreenService FScreenService;
	
private:
	// __classmethod void __fastcall Destroy@();
	
private:
	TCustomBufferedLayout* FScene;
	Fmx::Graphics::TBitmap* FBuffer;
	System::Generics::Collections::TList__1<Fmx::Controls::TControl*>* FControls;
	int FWidth;
	int FHeight;
	_TBufferedScene__1 FUpdateRects;
	float FLastWidth;
	float FLastHeight;
	bool FDisableAlign;
	void __fastcall AddUpdateRect(const System::Types::TRectF &R);
	int __fastcall GetUpdateRectsCount();
	System::Types::TRectF __fastcall GetUpdateRect(const int Index);
	Fmx::Types::TFmxObject* __fastcall GetObject();
	Fmx::Graphics::TCanvas* __fastcall GetCanvas();
	float __fastcall GetSceneScale();
	System::Types::TPointF __fastcall LocalToScreen(const System::Types::TPointF &P);
	System::Types::TPointF __fastcall ScreenToLocal(const System::Types::TPointF &P);
	void __fastcall ChangeScrollingState(Fmx::Controls::TControl* const AControl, const bool Active);
	void __fastcall DisableUpdating();
	void __fastcall EnableUpdating();
	Fmx::Controls::TStyleBook* __fastcall GetStyleBook();
	void __fastcall SetStyleBook(Fmx::Controls::TStyleBook* const Value);
	void __fastcall Realign();
	void __fastcall ChildrenAlignChanged();
	Fmx::Types::TFmxObject* __fastcall GetParent();
	HIDESBASE int __fastcall GetChildrenCount();
	void __fastcall Changed();
	void __fastcall Invalidate();
	void __fastcall UpdateBuffer();
	
protected:
	virtual void __fastcall ScaleChangedHandler(System::TObject* const Sender, System::Messaging::TMessageBase* const Msg);
	void __fastcall DrawTo();
	virtual void __fastcall DoAddObject(Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall DoRemoveObject(Fmx::Types::TFmxObject* const AObject);
	Fmx::Types::_di_IControl __fastcall ObjectAtPoint(const System::Types::TPointF &P);
	
public:
	__fastcall TBufferedScene(TCustomBufferedLayout* const AScene);
	__fastcall virtual ~TBufferedScene();
	void __fastcall SetSize(const int AWidth, const int AHeight);
	__property Fmx::Graphics::TBitmap* Buffer = {read=FBuffer};
	__property TCustomBufferedLayout* Scene = {read=FScene};
	
private:
	// __classmethod void __fastcall Create@();
private:
	void *__IContent;	// Fmx::Types::IContent 
	void *__IAlignRoot;	// Fmx::Types::IAlignRoot 
	void *__IScene;	// Fmx::Controls::IScene 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {96E89B94-2AD6-4AD3-A07C-92E66B2E6BC8}
	operator Fmx::Types::_di_IContent()
	{
		Fmx::Types::_di_IContent intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IContent*(void) { return (Fmx::Types::IContent*)&__IContent; }
	#endif
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
	
};


class PASCALIMPLEMENTATION TCustomBufferedLayout : public Fmx::Layouts::TLayout
{
	typedef Fmx::Layouts::TLayout inherited;
	
private:
	TBufferedScene* FScene;
	
protected:
	virtual void __fastcall Paint();
	virtual void __fastcall DoAddObject(Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall DoResized();
	virtual Fmx::Types::_di_IControl __fastcall ObjectAtPoint(const System::Types::TPointF &P);
	
public:
	__fastcall virtual TCustomBufferedLayout(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBufferedLayout();
};


class PASCALIMPLEMENTATION TBufferedLayout : public TCustomBufferedLayout
{
	typedef TCustomBufferedLayout inherited;
	
__published:
	__property Align = {default=0};
	__property Anchors;
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled;
	__property Locked = {default=0};
	__property Height;
	__property HitTest = {default=0};
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
	__property OnApplyStyleLookup;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
public:
	/* TCustomBufferedLayout.Create */ inline __fastcall virtual TBufferedLayout(System::Classes::TComponent* AOwner) : TCustomBufferedLayout(AOwner) { }
	/* TCustomBufferedLayout.Destroy */ inline __fastcall virtual ~TBufferedLayout() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Bufferedlayout */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_BUFFEREDLAYOUT)
using namespace Fmx::Bufferedlayout;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_BufferedlayoutHPP
