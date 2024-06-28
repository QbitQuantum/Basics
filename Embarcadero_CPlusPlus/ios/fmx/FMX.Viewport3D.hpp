// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Viewport3D.pas' rev: 34.00 (iOS)

#ifndef Fmx_Viewport3dHPP
#define Fmx_Viewport3dHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Messaging.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Controls3D.hpp>
#include <FMX.Objects3D.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Graphics.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Viewport3d
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TViewport3D;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TViewport3D : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
private:
	Fmx::Graphics::TBitmap* FBitmap;
	Fmx::Types3d::TTexture* FTexture;
	Fmx::Types3d::TContext3D* FContext;
	Fmx::Controls3d::TCamera* FCamera;
	Fmx::Controls3d::TCamera* FDesignCamera;
	Fmx::Objects3d::TDummy* FDesignCameraZ;
	Fmx::Objects3d::TDummy* FDesignCameraX;
	System::Uitypes::TAlphaColor FFill;
	Fmx::Types3d::TMultisample FMultisample;
	bool FUsingDesignCamera;
	bool FDrawing;
	System::Generics::Collections::TList__1<Fmx::Controls3d::TControl3D*>* FRenderingList;
	int FScaleChangedId;
	System::Generics::Collections::TList__1<Fmx::Controls3d::TLight*>* FLights;
	void __fastcall SetFill(const System::Uitypes::TAlphaColor Value);
	void __fastcall SetMultisample(const Fmx::Types3d::TMultisample Value);
	System::Uitypes::TAlphaColor __fastcall GetFill();
	void __fastcall SetUsingDesignCamera(const bool Value);
	void __fastcall RebuildRenderingList();
	void __fastcall ScaleChangedHandler(System::TObject* const Sender, System::Messaging::TMessageBase* const Msg);
	Fmx::Controls3d::TCamera* __fastcall GetCurrentCamera();
	
protected:
	virtual void __fastcall Paint();
	virtual void __fastcall Resize();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual Fmx::Types::_di_IControl __fastcall FindTarget(const System::Types::TPointF &P, const Fmx::Types::TDragObject &Data);
	virtual Fmx::Types::_di_IControl __fastcall ObjectAtPoint(const System::Types::TPointF &P);
	virtual void __fastcall DoAddObject(Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall DoRemoveObject(Fmx::Types::TFmxObject* const AObject);
	HIDESBASE Fmx::Types::TFmxObject* __fastcall GetObject();
	Fmx::Types3d::TContext3D* __fastcall GetContext();
	Fmx::Controls3d::TCamera* __fastcall GetCamera();
	int __fastcall GetLightCount();
	Fmx::Controls3d::TLight* __fastcall GetLight(int Index);
	void __fastcall AddLight(Fmx::Controls3d::TLight* const ALight);
	void __fastcall RemoveLight(Fmx::Controls3d::TLight* const ALight);
	bool __fastcall GetUsingDesignCamera();
	float __fastcall GetViewportScale();
	void __fastcall SetCamera(Fmx::Controls3d::TCamera* const ACamera);
	void __fastcall NeedRender();
	virtual void __fastcall DoScaleChanged();
	
public:
	__fastcall virtual TViewport3D(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TViewport3D();
	__property Fmx::Types3d::TContext3D* Context = {read=FContext, write=FContext};
	
__published:
	__property Align = {default=0};
	__property Anchors;
	__property Fmx::Controls3d::TCamera* Camera = {read=FCamera, write=SetCamera};
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property System::Uitypes::TAlphaColor Color = {read=GetFill, write=SetFill, default=-1};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled;
	__property Height;
	__property HitTest = {default=1};
	__property Locked = {default=0};
	__property Padding;
	__property Fmx::Types3d::TMultisample Multisample = {read=FMultisample, write=SetMultisample, default=2};
	__property Margins;
	__property Opacity;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property Scale;
	__property Size;
	__property bool UsingDesignCamera = {read=FUsingDesignCamera, write=SetUsingDesignCamera, default=1};
	__property Visible = {default=1};
	__property Width;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnClick;
	__property OnDblClick;
	__property OnCanFocus;
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
private:
	void *__IViewport3D;	// Fmx::Controls3d::IViewport3D 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F819CBB6-B3CD-47EA-B4BA-6ED76E668CA9}
	operator Fmx::Controls3d::_di_IViewport3D()
	{
		Fmx::Controls3d::_di_IViewport3D intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Controls3d::IViewport3D*(void) { return (Fmx::Controls3d::IViewport3D*)&__IViewport3D; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Viewport3d */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_VIEWPORT3D)
using namespace Fmx::Viewport3d;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Viewport3dHPP
