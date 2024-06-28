// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Forms.Border.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Forms_Border_WinHPP
#define Fmx_Forms_Border_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.Windows.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <System.UIConsts.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Types.hpp>
#include <FMX.Forms.Border.hpp>
#include <FMX.Menus.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Graphics.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Forms
{
namespace Border
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWindowBorderWin;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TWindowBorderWin : public Fmx::Forms::Border::TStyledWindowBorder
{
	typedef Fmx::Forms::Border::TStyledWindowBorder inherited;
	
private:
	Fmx::Graphics::TBitmap* FCaptionBuffer;
	NativeUInt FCaptionBufferHandle;
	NativeUInt FCaptionBufferBitmap;
	void *FCaptionBufferBits;
	Fmx::Controls::TControl* FBottomBorder;
	Fmx::Graphics::TBitmap* FBottomBuffer;
	NativeUInt FBottomBufferHandle;
	NativeUInt FBottomBufferBitmap;
	void *FBottomBufferBits;
	Fmx::Controls::TControl* FLeftBorder;
	Fmx::Graphics::TBitmap* FLeftBuffer;
	NativeUInt FLeftBufferHandle;
	NativeUInt FLeftBufferBitmap;
	void *FLeftBufferBits;
	Fmx::Controls::TControl* FRightBorder;
	Fmx::Graphics::TBitmap* FRightBuffer;
	NativeUInt FRightBufferHandle;
	NativeUInt FRightBufferBitmap;
	void *FRightBufferBits;
	Fmx::Graphics::TCanvas* FCurrentCanvas;
	NativeUInt FIcon;
	System::Types::TPointF FSaveIconPos;
	System::Types::TPointF FSaveTitlePadding;
	bool FNCClick;
	Fmx::Menus::TMenuBar* FMenuBar;
	int FUpdating;
	System::Generics::Collections::TDictionary__2<NativeUInt,Fmx::Menus::TMenuItem*>* FMenuMap;
	int __fastcall GetTopOffset();
	void __fastcall InvalidateRegion();
	void __fastcall RecreateRegion();
	void __fastcall Paint();
	void __fastcall UpdateWnd();
	void __fastcall DoPaint();
	void __fastcall ResizeCaptionBuffer(const System::Types::TRectF &R);
	void __fastcall ResizeBottomBuffer(const System::Types::TRectF &R);
	void __fastcall ResizeLeftBuffer(const System::Types::TRectF &R);
	void __fastcall ResizeRightBuffer(const System::Types::TRectF &R);
	void __fastcall FillBitmapInfo(tagBITMAPINFO &BitmapInfo, const int Width, const int Height);
	void __fastcall PaintCaption(const HDC DC);
	void __fastcall PaintBottom(const HDC DC);
	void __fastcall PaintLeft(const HDC DC);
	void __fastcall PaintRight(const HDC DC);
	void __fastcall UpdateButtonsState();
	System::Types::TSize __fastcall GetWndSize();
	HWND __fastcall GetWnd();
	void __fastcall ResizeMenuBar();
	
protected:
	virtual System::Types::TSizeF __fastcall GetFormSize();
	virtual void __fastcall Resize();
	virtual void __fastcall Invalidate();
	virtual void __fastcall DoAddUpdateRect(const System::Types::TRectF &R);
	virtual Fmx::Graphics::TCanvas* __fastcall GetCanvas();
	virtual System::Types::TRectF __fastcall GetClientMargins();
	virtual void __fastcall DoApplyStyle();
	virtual void __fastcall StyleChanged();
	virtual System::UnicodeString __fastcall GetStyleLookup();
	__property System::Types::TSize WndSize = {read=GetWndSize};
#ifndef _WIN64
	__property HWND Wnd = {read=GetWnd, nodefault};
#else /* _WIN64 */
	__property HWND Wnd = {read=GetWnd};
#endif /* _WIN64 */
	
public:
	__fastcall virtual TWindowBorderWin(Fmx::Forms::TCommonCustomForm* const AForm);
	__fastcall virtual ~TWindowBorderWin();
	void __fastcall CreateOSMenu(const Fmx::Types::_di_IItemsContainer AMenu);
	bool __fastcall HandleExists(const NativeUInt Handle);
	void __fastcall RemoveHandle(const NativeUInt Handle);
	__property bool NCClick = {read=FNCClick, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE NativeInt __fastcall WMNCMessages(Fmx::Forms::TCommonCustomForm* AForm, unsigned uMsg, NativeUInt wParam, NativeInt lParam);
extern DELPHI_PACKAGE Fmx::Forms::TWindowBorder* __fastcall CreateWindowBorder(Fmx::Forms::TCommonCustomForm* const AForm);
}	/* namespace Win */
}	/* namespace Border */
}	/* namespace Forms */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_FORMS_BORDER_WIN)
using namespace Fmx::Forms::Border::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_FORMS_BORDER)
using namespace Fmx::Forms::Border;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_FORMS)
using namespace Fmx::Forms;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Forms_Border_WinHPP
