// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MagnifierGlass.pas' rev: 34.00 (Android)

#ifndef Fmx_MagnifierglassHPP
#define Fmx_MagnifierglassHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Magnifierglass
{
//-- forward type declarations -----------------------------------------------
struct TLoupeModeHelper /* Helper for enum 'TLoupeMode' */;
struct TZoomModeHelper /* Helper for enum 'TZoomMode' */;
class DELPHICLASS TCustomMagnifierGlass;
class DELPHICLASS TMagnifierGlass;
__interface DELPHIINTERFACE ILoupeService;
typedef System::DelphiInterface<ILoupeService> _di_ILoupeService;
class DELPHICLASS TLoupeFactoryService;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TLoupeMode : unsigned char { Circle, Rectangle, lmCircle _DEPRECATED_ATTRIBUTE3("Use TLoupeMode.Circle")  = 0x0, lmRectangle _DEPRECATED_ATTRIBUTE3("Use TLoupeMode.Rectangle")  = 0x1 };

enum class DECLSPEC_DENUM TZoomMode : unsigned char { Absolute, Relative, zmAbsolute _DEPRECATED_ATTRIBUTE3("Use TZoomMode.Absolute")  = 0x0, zmRelative _DEPRECATED_ATTRIBUTE3("Use TZoomMode.Relative")  = 0x1 };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomMagnifierGlass : public Fmx::Controls::Presentation::TPresentedControl
{
	typedef Fmx::Controls::Presentation::TPresentedControl inherited;
	
public:
	#define TCustomMagnifierGlass_DefaultLoupeScale  (1.400000E+00)
	
	
private:
	TLoupeMode FLoupeMode;
	float FLoupeScale;
	Fmx::Types::TPosition* FZoomRegionCenter;
	TZoomMode FZoomMode;
	System::Uitypes::TAlphaColor FBackgroundColor;
	Fmx::Graphics::TBitmap* FScreenshot;
	Fmx::Graphics::TBitmap* FScaledScreenshot;
	Fmx::Objects::TShape* FContent;
	void __fastcall SetLoupeMode(const TLoupeMode Value);
	void __fastcall SetLoupeScale(const float Value);
	void __fastcall SetZoomMode(const TZoomMode Value);
	void __fastcall SetBackgroundColor(const System::Uitypes::TAlphaColor Value);
	bool __fastcall IsLoupeScaleStored();
	float __fastcall GetScreenScale();
	System::Types::TPointF __fastcall GetCenter();
	HIDESBASE void __fastcall MakeScreenshot();
	void __fastcall DoZoomRegionChanged(System::TObject* Sender);
	void __fastcall DoContentPaint(System::TObject* Sender, Fmx::Graphics::TCanvas* Canvas, const System::Types::TRectF &ARect);
	
protected:
	virtual void __fastcall SetZoomRegionCenter(Fmx::Types::TPosition* const Value);
	virtual System::Types::TRectF __fastcall GetZoomRect();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	bool __fastcall HasContent();
	virtual System::Types::TSizeF __fastcall GetDefaultSize();
	virtual void __fastcall Paint();
	__property float ScreenScale = {read=GetScreenScale};
	__property System::Types::TPointF Center = {read=GetCenter};
	
public:
	__fastcall virtual TCustomMagnifierGlass(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TCustomMagnifierGlass();
	__property Fmx::Types::TPosition* ZoomRegionCenter = {read=FZoomRegionCenter, write=SetZoomRegionCenter};
	__property TZoomMode ZoomMode = {read=FZoomMode, write=SetZoomMode, default=1};
	__property System::Uitypes::TAlphaColor BackgroundColor = {read=FBackgroundColor, write=SetBackgroundColor, default=-1};
	__property TLoupeMode LoupeMode = {read=FLoupeMode, write=SetLoupeMode, default=0};
	__property float LoupeScale = {read=FLoupeScale, write=SetLoupeScale, stored=IsLoupeScaleStored};
	__property Fmx::Graphics::TBitmap* ScaledScreenshot = {read=FScaledScreenshot};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMagnifierGlass : public TCustomMagnifierGlass
{
	typedef TCustomMagnifierGlass inherited;
	
__published:
	__property BackgroundColor = {default=-1};
	__property LoupeMode = {default=0};
	__property LoupeScale;
	__property Align = {default=0};
	__property Anchors;
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property ControlType = {default=0};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
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
	__property StyleLookup = {default=0};
	__property Visible = {default=1};
	__property Width;
	__property ZoomMode = {default=1};
	__property ZoomRegionCenter;
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
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
public:
	/* TCustomMagnifierGlass.Create */ inline __fastcall virtual TMagnifierGlass(System::Classes::TComponent* AOwner)/* overload */ : TCustomMagnifierGlass(AOwner) { }
	/* TCustomMagnifierGlass.Destroy */ inline __fastcall virtual ~TMagnifierGlass() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EAFDFBA9-F24A-4DF0-920E-F0D2BC6E8B33}") ILoupeService  : public System::IInterface 
{
	virtual void __fastcall SetLoupeMode(const TLoupeMode AMode) = 0 ;
	virtual void __fastcall SetLoupeScale(const float AScale) = 0 ;
	virtual float __fastcall GetWidth() = 0 ;
	virtual float __fastcall GetHeight() = 0 ;
	virtual void __fastcall SetZoomRegionCenter(const System::Types::TPointF &AZoomPoint) = 0 ;
	virtual void __fastcall SetPosition(const System::Types::TPointF &AAbsolutePosition) = 0 ;
	virtual void __fastcall ShowFor(Fmx::Controls::TControl* AControl) = 0 ;
	virtual void __fastcall Hide() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLoupeFactoryService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Fmx::Controls::TControl* FForControl;
	TMagnifierGlass* FLoupe;
	
public:
	__fastcall TLoupeFactoryService();
	__fastcall virtual ~TLoupeFactoryService();
	void __fastcall SetLoupeMode(const TLoupeMode AMode);
	void __fastcall SetLoupeScale(const float AScale);
	float __fastcall GetWidth();
	float __fastcall GetHeight();
	void __fastcall SetZoomRegionCenter(const System::Types::TPointF &AZoomPoint);
	void __fastcall SetPosition(const System::Types::TPointF &AAbsolutePosition);
	void __fastcall ShowFor(Fmx::Controls::TControl* AControl);
	void __fastcall Hide();
private:
	void *__ILoupeService;	// ILoupeService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EAFDFBA9-F24A-4DF0-920E-F0D2BC6E8B33}
	operator _di_ILoupeService()
	{
		_di_ILoupeService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ILoupeService*(void) { return (ILoupeService*)&__ILoupeService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define DEFAULT_LOUPE_SCALE  (1.400000E+00)
}	/* namespace Magnifierglass */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MAGNIFIERGLASS)
using namespace Fmx::Magnifierglass;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_MagnifierglassHPP
