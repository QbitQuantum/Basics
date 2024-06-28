// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Controls.Ole.pas' rev: 34.00 (Windows)

#ifndef Fmx_Controls_OleHPP
#define Fmx_Controls_OleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Winapi.Windows.hpp>
#include <System.Win.ComObj.hpp>
#include <System.Win.OleControls.hpp>
#include <FMX.Controls.hpp>
#include <Winapi.Messages.hpp>
#include <FMX.Controls.Win.hpp>
#include <FMX.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Controls
{
namespace Ole
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TOLEFrameworkDelegate;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TOLEFrameworkDelegate : public Fmx::Controls::Win::TWinControl
{
	typedef Fmx::Controls::Win::TWinControl inherited;
	
private:
	System::Win::Comobj::_di_TEventDispatchInvoker FDispatcher;
	void __fastcall SetDefWndProc(const void * AWndProc);
	void * __fastcall GetDefWndProc();
	void * __fastcall InitWindowProc();
	void __fastcall SetHandle(const HWND AHandle);
	NativeUInt __fastcall GetParentHandle();
	HIDESBASE System::Types::TRect __fastcall GetBoundsRect();
	void __fastcall SetCreationControl();
	void __fastcall SetDispatcher(const System::Win::Comobj::_di_TEventDispatchInvoker ADisp);
	System::Win::Comobj::TOleVariantArray __fastcall Disp(const int DispId, const System::Win::Comobj::TOleVariantArray AParams);
	HWND __fastcall GetWindowHandle();
	void __fastcall SetWindowHandle(HWND AValue);
	
protected:
	HIDESBASE bool __fastcall GetVisible();
	virtual void __fastcall SetVisible(const bool AVisible);
	virtual void __fastcall CreateWnd();
	virtual void __fastcall DestroyHandle();
	virtual void __fastcall DestroyWindowHandle();
public:
	/* TWinControl.Create */ inline __fastcall virtual TOLEFrameworkDelegate(System::Classes::TComponent* AOwner)/* overload */ : Fmx::Controls::Win::TWinControl(AOwner) { }
	/* TWinControl.CreateParented */ inline __fastcall TOLEFrameworkDelegate(HWND ParentWindow) : Fmx::Controls::Win::TWinControl(ParentWindow) { }
	/* TWinControl.Destroy */ inline __fastcall virtual ~TOLEFrameworkDelegate() { }
	
private:
	void *__IOLEFrameworkDelegate;	// System::Win::Olecontrols::IOLEFrameworkDelegate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5240182A-FED7-41D3-B121-68E983247B1E}
	operator System::Win::Olecontrols::_di_IOLEFrameworkDelegate()
	{
		System::Win::Olecontrols::_di_IOLEFrameworkDelegate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Win::Olecontrols::IOLEFrameworkDelegate*(void) { return (System::Win::Olecontrols::IOLEFrameworkDelegate*)&__IOLEFrameworkDelegate; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ole */
}	/* namespace Controls */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTROLS_OLE)
using namespace Fmx::Controls::Ole;
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
#endif	// Fmx_Controls_OleHPP
