// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Printer.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Printer_IosHPP
#define Fmx_Printer_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.UITypes.hpp>
#include <System.Types.hpp>
#include <Macapi.CoreServices.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.UIKit.hpp>
#include <FMX.Printer.hpp>
#include <FMX.Types.hpp>
#include <FMX.Consts.hpp>
#include <FMX.Graphics.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Printer
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPrinteriOS;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPrinteriOS : public Fmx::Printer::TPrinter
{
	typedef Fmx::Printer::TPrinter inherited;
	
protected:
	virtual void __fastcall ActivePrinterChanged();
	virtual void __fastcall DoAbortDoc();
	virtual void __fastcall DoBeginDoc();
	virtual void __fastcall DoEndDoc();
	virtual void __fastcall DoNewPage();
	virtual Fmx::Graphics::TCanvas* __fastcall GetCanvas();
	virtual System::Uitypes::TPrinterCapabilities __fastcall GetCapabilities();
	virtual int __fastcall GetNumCopies();
	virtual System::Uitypes::TPrinterOrientation __fastcall GetOrientation();
	virtual int __fastcall GetPageHeight();
	virtual int __fastcall GetPageWidth();
	virtual void __fastcall RefreshFonts();
	virtual void __fastcall RefreshPrinterDevices();
	virtual void __fastcall SetDefaultPrinter();
	virtual void __fastcall SetNumCopies(int Value);
	virtual void __fastcall SetOrientation(System::Uitypes::TPrinterOrientation Value);
	
public:
	__fastcall virtual TPrinteriOS();
	__fastcall virtual ~TPrinteriOS();
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Fmx::Printer::TPrinterClass __fastcall ActualPrinterClass(void);
}	/* namespace Ios */
}	/* namespace Printer */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRINTER_IOS)
using namespace Fmx::Printer::Ios;
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
#endif	// Fmx_Printer_IosHPP
