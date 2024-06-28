// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Platform_WinHPP
#define Fmx_Platform_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.CommCtrl.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <System.UIConsts.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Types.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.ZOrder.Win.hpp>

//-- user supplied -----------------------------------------------------------
#if defined(WIN32) && defined(CreateWindow)
  #define __SAVE_CREATEWINDOW CreateWindow
  #undef  CreateWindow
#endif

namespace Fmx
{
namespace Platform
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWinWindowHandle;
class DELPHICLASS TWinDropTarget;
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<System::Types::TRect, 134217727> TRgnRects;

typedef TRgnRects *PRgnRects;

typedef System::DynamicArray<System::Types::TRectF> TUpdateRects;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWinWindowHandle : public Fmx::Types::TWindowHandle
{
	typedef Fmx::Types::TWindowHandle inherited;
	
private:
	static float FForcedScale;
	HWND FWnd;
	Fmx::Zorder::Win::TWinZOrderManager* FZOrderManager;
	NativeUInt FBufferBitmap;
	tagBITMAPINFO FBitmapInfo;
	void *FBufferBits;
	NativeUInt FBufferHandle;
	System::Types::TSize FBufferSize;
	Fmx::Forms::TCommonCustomForm* FForm;
	bool FDisableDeactivate;
	TWinDropTarget* FWinDropTarget;
	float FCurrentScale;
	System::Types::TSizeF FClientSize;
	System::Types::TSize FWndClientSize;
	System::Types::TRectF FBounds;
	System::Types::TRect FWndBounds;
	int FNearestIntegerMultiple;
	void __fastcall UpdateLayer();
	Fmx::Zorder::Win::TWinZOrderManager* __fastcall GetZOrderManager();
	void __fastcall SetBounds(const System::Types::TRect &Value);
	void __fastcall SetWndBounds(const System::Types::TRect &Value);
	void __fastcall SetClientSize(const System::Types::TSize &Value);
	void __fastcall UpdateClientSize();
	void __fastcall SetWindowSizeByClientSize();
	void __fastcall CalcNearestIntegerMultiple();
	int __fastcall GetNearestIntegerMultiple();
	
protected:
	virtual System::Types::TRect __fastcall GetBounds();
	virtual System::Types::TSize __fastcall GetClientSize();
	virtual System::Types::TRect __fastcall GetWndBounds();
	virtual System::Types::TSize __fastcall GetWndClientSize();
	virtual bool __fastcall GetTransparency();
	virtual float __fastcall GetScale();
	
public:
	__fastcall TWinWindowHandle(Fmx::Forms::TCommonCustomForm* const AForm, const HWND AWnd);
	__fastcall virtual ~TWinWindowHandle();
	__classmethod void __fastcall SetForcedScale(float NewScale);
	void __fastcall CreateBuffer(const int Width, const int Height);
	void __fastcall ResizeBuffer(const int Width, const int Height);
	void __fastcall FreeBuffer();
	void __fastcall CorrectWindowSize(const Winapi::Windows::PWindowPos WindowPos);
	void __fastcall ScaleChanged();
	void __fastcall DpiChanged(const int NewDpi);
	System::Types::TRectF __fastcall WndToForm(const System::Types::TRect &Rect)/* overload */;
	System::Types::TRectF __fastcall WndToForm(const System::Types::TRectF &Rect)/* overload */;
	System::Types::TRectF __fastcall FormToWnd(const System::Types::TRectF &Rect);
#ifndef _WIN64
	__property HWND Wnd = {read=FWnd, nodefault};
#else /* _WIN64 */
	__property HWND Wnd = {read=FWnd};
#endif /* _WIN64 */
	__property Fmx::Forms::TCommonCustomForm* Form = {read=FForm};
	__property void * BufferBits = {read=FBufferBits};
#ifndef _WIN64
	__property NativeUInt BufferHandle = {read=FBufferHandle, nodefault};
#else /* _WIN64 */
	__property NativeUInt BufferHandle = {read=FBufferHandle};
#endif /* _WIN64 */
	__property System::Types::TSize BufferSize = {read=FBufferSize};
	__property Fmx::Zorder::Win::TWinZOrderManager* ZOrderManager = {read=GetZOrderManager};
	__property bool Transparency = {read=GetTransparency, nodefault};
	__property System::Types::TSize ClientSize = {read=GetClientSize, write=SetClientSize};
	__property int NearestIntegerMultiple = {read=GetNearestIntegerMultiple, nodefault};
	__property System::Types::TRect Bounds = {read=GetBounds, write=SetBounds};
	__property System::Types::TRectF BoundsF = {read=FBounds};
	__property System::Types::TSize WndClientSize = {read=GetWndClientSize};
	__property System::Types::TRect WndBounds = {read=GetWndBounds, write=SetWndBounds};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TWinDropTarget : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Fmx::Forms::TCommonCustomForm* Form;
	Fmx::Types::TDragObject __fastcall GetDataObject();
	HRESULT __stdcall DragEnter(const _di_IDataObject dataObj, int grfKeyState, System::Types::TPoint pt, int &dwEffect);
	HRESULT __stdcall DragOver(int grfKeyState, System::Types::TPoint pt, int &dwEffect);
	HRESULT __stdcall DragLeave();
	HRESULT __stdcall Drop(const _di_IDataObject dataObj, int grfKeyState, System::Types::TPoint pt, int &dwEffect);
public:
	/* TComponent.Create */ inline __fastcall virtual TWinDropTarget(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TWinDropTarget() { }
	
private:
	void *__IDropTarget;	// IDropTarget 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000122-0000-0000-C000-000000000046}
	operator _di_IDropTarget()
	{
		_di_IDropTarget intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDropTarget*(void) { return (IDropTarget*)&__IDropTarget; }
	#endif
	
};


typedef HWND __fastcall (*TApplicationHWNDProc)(void);

//-- var, const, procedure ---------------------------------------------------
#ifndef _WIN64
#define IDC_NODROP (System::WideChar *)(0x7fff)
#define IDC_DRAG (System::WideChar *)(0x7ffe)
#define IDC_MULTIDRAG (System::WideChar *)(0x7ffb)
#define IDC_SQLWAIT (System::WideChar *)(0x7ffa)
#else /* _WIN64 */
#define IDC_NODROP (System::WideChar *)(0x0000000000007fffULL)
#define IDC_DRAG (System::WideChar *)(0x0000000000007ffeULL)
#define IDC_MULTIDRAG (System::WideChar *)(0x0000000000007ffbULL)
#define IDC_SQLWAIT (System::WideChar *)(0x0000000000007ffaULL)
#endif /* _WIN64 */
extern DELPHI_PACKAGE void __fastcall RegisterCorePlatformServices(void);
extern DELPHI_PACKAGE void __fastcall UnregisterCorePlatformServices(void);
extern DELPHI_PACKAGE Fmx::Forms::TCommonCustomForm* __fastcall FindWindow(HWND Handle);
extern DELPHI_PACKAGE HWND __fastcall FmxHandleToHWND(Fmx::Types::TWindowHandle* const FmxHandle);
extern DELPHI_PACKAGE TWinWindowHandle* __fastcall WindowHandleToPlatform(Fmx::Types::TWindowHandle* const AHandle);
extern DELPHI_PACKAGE HWND __fastcall FormToHWND(Fmx::Forms::TCommonCustomForm* Form);
extern DELPHI_PACKAGE HWND __fastcall ApplicationHWND(void);
extern DELPHI_PACKAGE void __fastcall RegisterApplicationHWNDProc(const TApplicationHWNDProc Proc);
extern DELPHI_PACKAGE void __cdecl ShutDown(void);
}	/* namespace Win */
}	/* namespace Platform */
}	/* namespace Fmx */

//-- user supplied -----------------------------------------------------------
#if defined(__SAVE_CREATEWINDOW)
  #define CreateWindow __SAVE_CREATEWINDOW
  #undef  __SAVE_CREATEWINDOW
#endif

#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Platform_WinHPP
