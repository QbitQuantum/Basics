// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Printer.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Printer_WinHPP
#define Fmx_Printer_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.WinSpool.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Canvas.GDIP.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Printer.hpp>
#include <FMX.Graphics.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Printer
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPrinterWin;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPrinterWin : public Fmx::Printer::TPrinter
{
	typedef Fmx::Printer::TPrinter inherited;
	
protected:
	int FPrinterIndex;
	System::Uitypes::TPrinterState FState;
	HDC FDC;
	NativeUInt FPrinterHandle;
	_devicemodeW *FDevMode;
	NativeUInt FDeviceMode;
	System::Uitypes::TPrinterOrientation FOrientation;
	System::Uitypes::TPrinterCapabilities FCapabilities;
	void __fastcall SetCanvasDefaultSettings();
	void __fastcall RefreshActivePrinter();
	virtual void __fastcall ActivePrinterChanged();
	virtual void __fastcall DoAbortDoc();
	virtual void __fastcall DoBeginDoc();
	virtual void __fastcall DoEndDoc();
	virtual void __fastcall DoNewPage();
	void __fastcall SetState(System::Uitypes::TPrinterState Value);
	virtual Fmx::Graphics::TCanvas* __fastcall GetCanvas();
	virtual int __fastcall GetNumCopies();
	HDC __fastcall GetHandle();
	virtual System::Uitypes::TPrinterOrientation __fastcall GetOrientation();
	virtual int __fastcall GetPageHeight();
	virtual int __fastcall GetPageWidth();
	virtual void __fastcall RefreshFonts();
	virtual void __fastcall RefreshPrinterDevices();
	void __fastcall SetPrinterCapabilities(int Value);
	virtual void __fastcall SetOrientation(System::Uitypes::TPrinterOrientation Value);
	virtual void __fastcall SetNumCopies(int Value);
	virtual void __fastcall SetDefaultPrinter();
	
public:
	__fastcall virtual TPrinterWin();
	__fastcall virtual ~TPrinterWin();
	HIDESBASE void __fastcall GetPrinter(System::WideChar * ADevice, System::WideChar * ADriver, System::WideChar * APort, NativeUInt &ADeviceMode);
	void __fastcall SetPrinter(System::WideChar * ADevice, System::WideChar * ADriver, System::WideChar * APort, NativeUInt ADeviceMode);
#ifndef _WIN64
	__property HDC Handle = {read=GetHandle, nodefault};
#else /* _WIN64 */
	__property HDC Handle = {read=GetHandle};
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Fmx::Printer::TPrinterClass __fastcall ActualPrinterClass(void);
}	/* namespace Win */
}	/* namespace Printer */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRINTER_WIN)
using namespace Fmx::Printer::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRINTER)
using namespace Fmx::Printer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Printer_WinHPP
