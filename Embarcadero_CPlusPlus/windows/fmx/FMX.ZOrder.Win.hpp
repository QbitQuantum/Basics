// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.ZOrder.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Zorder_WinHPP
#define Fmx_Zorder_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <Winapi.Windows.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ZOrder.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Zorder
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWinZOrderManager;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWinZOrderManager : public Fmx::Zorder::TCustomZOrderManager__1<HWND>
{
	typedef Fmx::Zorder::TCustomZOrderManager__1<HWND> inherited;
	
private:
	System::Types::TRect __fastcall AbsoluteToParentView(Fmx::Controls::TControl* const AControl, const HWND AParentView);
	
protected:
	virtual HWND __fastcall GetParentView(const HWND AControlHandle);
	virtual void __fastcall RemoveFromParent(const HWND AControlHandle);
	virtual void __fastcall InsertSubview(const HWND AParentHandle, const HWND AChildHandle, const HWND APreviousSiblingView);
	virtual int __fastcall IndexOfView(const HWND AControlHandle);
	virtual void __fastcall UpdateBounds(const HWND AControlHandle, Fmx::Controls::TControl* const AControl, const HWND AParentHandle)/* overload */;
	virtual void __fastcall UpdateVisible(const HWND AControlHandle, const bool AVisible);
	virtual HWND __fastcall GetFormView(Fmx::Forms::TCommonCustomForm* const AForm);
	virtual bool __fastcall SameView(const HWND AControlLeftHwnd, const HWND AControlRightHwnd);
	virtual HWND __fastcall NullView();
public:
	/* {FMX_ZOrder}TCustomZOrderManager<Winapi_Windows_HWND>.Create */ inline __fastcall TWinZOrderManager(Fmx::Types::TWindowHandle* const AOwner) : Fmx::Zorder::TCustomZOrderManager__1<HWND>(AOwner) { }
	/* {FMX_ZOrder}TCustomZOrderManager<Winapi_Windows_HWND>.Destroy */ inline __fastcall virtual ~TWinZOrderManager() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  UpdateBounds(Fmx::Controls::TControl* const AControl){ Fmx::Zorder::TCustomZOrderManager__1<HWND>::UpdateBounds(AControl); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Zorder */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ZORDER_WIN)
using namespace Fmx::Zorder::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ZORDER)
using namespace Fmx::Zorder;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Zorder_WinHPP
