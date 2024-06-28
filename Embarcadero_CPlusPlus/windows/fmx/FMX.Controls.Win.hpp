// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Controls.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Controls_WinHPP
#define Fmx_Controls_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Controls
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
struct TCreateParams;
class DELPHICLASS TWinControl;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TCreateParams
{
public:
	System::WideChar *Caption;
	unsigned Style;
	unsigned ExStyle;
	int X;
	int Y;
	int Width;
	int Height;
	HWND WndParent;
	void *Param;
	tagWNDCLASSW WindowClass;
	System::StaticArray<System::WideChar, 64> WinClassName;
};


class PASCALIMPLEMENTATION TWinControl : public Fmx::Controls::TControl
{
	typedef Fmx::Controls::TControl inherited;
	
private:
	System::Classes::TWndMethod FWindowProc;
	HWND FParentWindow;
	System::Classes::TList* FWinControls;
	void *FDefWndProc;
	HWND FHandle;
	void *FObjectInstance;
	HWND __fastcall PrecedingWindow(TWinControl* const Control);
	void __fastcall SetParentWindow(const HWND Value);
	void __fastcall UpdateShowing();
	
protected:
	virtual HWND __fastcall GetHandle();
	HIDESBASE virtual void __fastcall SetParent(Fmx::Types::TFmxObject* const AParent);
	HIDESBASE virtual Fmx::Types::TFmxObject* __fastcall GetParent();
	virtual void __fastcall WndProc(Winapi::Messages::TMessage &Message);
	virtual void __fastcall CreateHandle();
	virtual void __fastcall CreateParams(TCreateParams &Params);
	virtual void __fastcall CreateWnd() = 0 ;
	virtual void __fastcall DestroyHandle();
	virtual void __fastcall DestroyWindowHandle();
	HWND __fastcall GetTopParentHandle();
	void __fastcall MainWndProc(Winapi::Messages::TMessage &Message);
	__property void * DefWndProc = {read=FDefWndProc, write=FDefWndProc};
#ifndef _WIN64
	__property HWND WindowHandle = {read=FHandle, write=FHandle, nodefault};
#else /* _WIN64 */
	__property HWND WindowHandle = {read=FHandle, write=FHandle};
#endif /* _WIN64 */
	virtual void __fastcall DoMatrixChanged(System::TObject* Sender);
	virtual void __fastcall DoMouseActivate();
	virtual void __fastcall DoSetFocus();
	
public:
	__fastcall virtual TWinControl(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall TWinControl(HWND ParentWindow);
	__classmethod TWinControl* __fastcall CreateParentedControl(HWND ParentWindow);
	__fastcall virtual ~TWinControl();
	bool __fastcall HandleAllocated();
	HIDESBASE virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	void __fastcall UpdateControlState();
#ifndef _WIN64
	__property HWND Handle = {read=GetHandle, nodefault};
	__property HWND ParentWindow = {read=FParentWindow, write=SetParentWindow, nodefault};
#else /* _WIN64 */
	__property HWND Handle = {read=GetHandle};
	__property HWND ParentWindow = {read=FParentWindow, write=SetParentWindow};
#endif /* _WIN64 */
	virtual void __fastcall Update();
	__property System::Classes::TWndMethod WindowProc = {read=FWindowProc, write=FWindowProc};
	__property Fmx::Types::TFmxObject* Parent = {read=GetParent, write=SetParent};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TWinControl* CreationControl;
extern DELPHI_PACKAGE NativeInt __stdcall InitWndProc(HWND HWindow, unsigned Msg, NativeUInt WParam, NativeInt LParam);
}	/* namespace Win */
}	/* namespace Controls */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTROLS_WIN)
using namespace Fmx::Controls::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTROLS)
using namespace Fmx::Controls;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Controls_WinHPP
