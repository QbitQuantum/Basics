// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Printer.pas' rev: 34.00 (Windows)

#ifndef Fmx_PrinterHPP
#define Fmx_PrinterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.UITypes.hpp>
#include <System.UIConsts.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Graphics.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Printer
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EPrinter;
class DELPHICLASS EPrinterSettingsError;
class DELPHICLASS TPrinterDevice;
class DELPHICLASS TPrinter;
class DELPHICLASS TPrintDialog;
class DELPHICLASS TPrinterSetupDialog;
class DELPHICLASS TPageSetupDialog;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EPrinter : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EPrinter(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EPrinter(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EPrinter(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EPrinter(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EPrinter(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EPrinter(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EPrinter(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EPrinter(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPrinter(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPrinter(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPrinter(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPrinter(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EPrinter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EPrinterSettingsError : public EPrinter
{
	typedef EPrinter inherited;
	
public:
	/* Exception.Create */ inline __fastcall EPrinterSettingsError(const System::UnicodeString Msg) : EPrinter(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EPrinterSettingsError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EPrinter(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EPrinterSettingsError(NativeUInt Ident)/* overload */ : EPrinter(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EPrinterSettingsError(System::PResStringRec ResStringRec)/* overload */ : EPrinter(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EPrinterSettingsError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EPrinter(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EPrinterSettingsError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EPrinter(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EPrinterSettingsError(const System::UnicodeString Msg, int AHelpContext) : EPrinter(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EPrinterSettingsError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EPrinter(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPrinterSettingsError(NativeUInt Ident, int AHelpContext)/* overload */ : EPrinter(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPrinterSettingsError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EPrinter(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPrinterSettingsError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EPrinter(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPrinterSettingsError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EPrinter(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EPrinterSettingsError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPrinterDevice : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FDevice;
	System::UnicodeString FDriver;
	System::UnicodeString FPort;
	System::Types::TPoint __fastcall GetActiveDPI();
	System::Types::TPoint __fastcall GetDPI(int Index);
	int __fastcall GetDPICount();
	void __fastcall SetActiveDPIIndex(const int Value);
	
protected:
	System::Generics::Collections::TList__1<System::Types::TPoint>* FDPIList;
	int FActiveDPIIndex;
	void __fastcall DPIChangeError();
	virtual System::UnicodeString __fastcall GetTitle();
	virtual void __fastcall RefreshDPIList() = 0 ;
	virtual void __fastcall ActiveDPIChanged() = 0 ;
	
public:
	__fastcall TPrinterDevice(const System::UnicodeString ADriver, const System::UnicodeString ADevice, const System::UnicodeString APort);
	__fastcall virtual ~TPrinterDevice();
	virtual bool __fastcall Equals(System::TObject* Obj)/* overload */;
	HIDESBASE bool __fastcall Equals(const System::UnicodeString ADriver, const System::UnicodeString ADevice, const System::UnicodeString APort)/* overload */;
	virtual void __fastcall ShowDeviceOptions();
	int __fastcall SelectDPI(int X, int Y)/* overload */;
	int __fastcall SelectDPI(const System::Types::TPoint &DPI)/* overload */;
	__property System::UnicodeString Device = {read=FDevice};
	__property System::UnicodeString Driver = {read=FDriver};
	__property System::UnicodeString Port = {read=FPort, write=FPort};
	__property System::UnicodeString Title = {read=GetTitle};
	__property System::Types::TPoint ActiveDPI = {read=GetActiveDPI};
	__property int ActiveDPIIndex = {read=FActiveDPIIndex, write=SetActiveDPIIndex, nodefault};
	__property System::Types::TPoint DPI[int Index] = {read=GetDPI};
	__property int DPICount = {read=GetDPICount, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPrinter : public Fmx::Graphics::TAbstractPrinter
{
	typedef Fmx::Graphics::TAbstractPrinter inherited;
	
	
private:
	typedef System::Generics::Collections::TObjectList__1<TPrinterDevice*>* TPrinterDeviceList;
	
	
protected:
	Fmx::Graphics::TCanvas* FCanvas;
	bool FAborted;
	System::Classes::TStrings* FFonts;
	System::Generics::Collections::TObjectList__1<TPrinterDevice*>* FPrinters;
	int FActivePrinter;
	System::UnicodeString FTitle;
	bool FPrinting;
	int FPageNumber;
	virtual void __fastcall ActivePrinterChanged() = 0 ;
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual void __fastcall DoAbortDoc() = 0 ;
	virtual void __fastcall DoBeginDoc() = 0 ;
	virtual void __fastcall DoEndDoc() = 0 ;
	virtual void __fastcall DoNewPage() = 0 ;
	void __fastcall FreeFonts();
	TPrinterDevice* __fastcall GetActivePrinter();
	virtual Fmx::Graphics::TCanvas* __fastcall GetCanvas() = 0 ;
	virtual System::Uitypes::TPrinterCapabilities __fastcall GetCapabilities() = 0 ;
	int __fastcall GetCount();
	System::Classes::TStrings* __fastcall GetFonts();
	virtual int __fastcall GetNumCopies() = 0 ;
	virtual System::Uitypes::TPrinterOrientation __fastcall GetOrientation() = 0 ;
	virtual int __fastcall GetPageHeight() = 0 ;
	virtual int __fastcall GetPageWidth() = 0 ;
	TPrinterDevice* __fastcall GetPrinter(int Index);
	void __fastcall RaiseError(const System::UnicodeString Msg);
	virtual void __fastcall RefreshFonts() = 0 ;
	virtual void __fastcall RefreshPrinterDevices() = 0 ;
	void __fastcall SetActivePrinter(TPrinterDevice* APrinter);
	virtual void __fastcall SetDefaultPrinter() = 0 ;
	virtual void __fastcall SetNumCopies(int Value);
	virtual void __fastcall SetOrientation(System::Uitypes::TPrinterOrientation Value);
	void __fastcall CheckPrinting(bool Printing);
	
public:
	__fastcall virtual TPrinter();
	__fastcall virtual ~TPrinter();
	void __fastcall Abort();
	void __fastcall BeginDoc();
	void __fastcall EndDoc();
	void __fastcall NewPage();
	void __fastcall Refresh();
	__property bool Aborted = {read=FAborted, nodefault};
	__property TPrinterDevice* ActivePrinter = {read=GetActivePrinter, write=SetActivePrinter};
	__property Fmx::Graphics::TCanvas* Canvas = {read=GetCanvas};
	__property System::Uitypes::TPrinterCapabilities Capabilities = {read=GetCapabilities, nodefault};
	__property int Copies = {read=GetNumCopies, write=SetNumCopies, nodefault};
	__property int Count = {read=GetCount, nodefault};
	__property System::Classes::TStrings* Fonts = {read=GetFonts};
	__property System::Uitypes::TPrinterOrientation Orientation = {read=GetOrientation, write=SetOrientation, nodefault};
	__property int PageHeight = {read=GetPageHeight, nodefault};
	__property int PageNumber = {read=FPageNumber, nodefault};
	__property int PageWidth = {read=GetPageWidth, nodefault};
	__property bool Printing = {read=FPrinting, nodefault};
	__property TPrinterDevice* Printers[int Index] = {read=GetPrinter};
	__property System::UnicodeString Title = {read=FTitle, write=FTitle};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TPrinterClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TPrinterClass);
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TPrintDialog : public Fmx::Dialogs::TCommonDialog
{
	typedef Fmx::Dialogs::TCommonDialog inherited;
	
private:
	bool FCollate;
	int FCopies;
	int FMinPage;
	int FMaxPage;
	System::Uitypes::TPrintDialogOptions FOptions;
	int FFromPage;
	int FToPage;
	System::Uitypes::TPrintRange FPrintRange;
	bool FPrintToFile;
	void __fastcall SetNumCopies(int Value);
	
protected:
	virtual bool __fastcall DoExecute();
	
__published:
	__property bool Collate = {read=FCollate, write=FCollate, default=0};
	__property int Copies = {read=FCopies, write=SetNumCopies, default=0};
	__property int FromPage = {read=FFromPage, write=FFromPage, default=0};
	__property int MinPage = {read=FMinPage, write=FMinPage, default=0};
	__property int MaxPage = {read=FMaxPage, write=FMaxPage, default=0};
	__property System::Uitypes::TPrintDialogOptions Options = {read=FOptions, write=FOptions, default=0};
	__property bool PrintToFile = {read=FPrintToFile, write=FPrintToFile, default=0};
	__property System::Uitypes::TPrintRange PrintRange = {read=FPrintRange, write=FPrintRange, default=0};
	__property int ToPage = {read=FToPage, write=FToPage, default=0};
public:
	/* TCommonDialog.Create */ inline __fastcall virtual TPrintDialog(System::Classes::TComponent* AOwner) : Fmx::Dialogs::TCommonDialog(AOwner) { }
	/* TCommonDialog.Destroy */ inline __fastcall virtual ~TPrintDialog() { }
	
};


class PASCALIMPLEMENTATION TPrinterSetupDialog : public Fmx::Dialogs::TCommonDialog
{
	typedef Fmx::Dialogs::TCommonDialog inherited;
	
protected:
	virtual bool __fastcall DoExecute();
public:
	/* TCommonDialog.Create */ inline __fastcall virtual TPrinterSetupDialog(System::Classes::TComponent* AOwner) : Fmx::Dialogs::TCommonDialog(AOwner) { }
	/* TCommonDialog.Destroy */ inline __fastcall virtual ~TPrinterSetupDialog() { }
	
};


typedef void __fastcall (__closure *TPageSetupPaintingEvent)(System::TObject* Sender, const short PaperSize, const System::Uitypes::TPrinterOrientation Orientation, const System::Uitypes::TPageType PageType, bool &DoneDrawing);

typedef void __fastcall (__closure *TPaintPageEvent)(System::TObject* Sender, Fmx::Graphics::TCanvas* Canvas, const System::Types::TRect &PageRect, bool &DoneDrawing);

class PASCALIMPLEMENTATION TPageSetupDialog : public Fmx::Dialogs::TCommonDialog
{
	typedef Fmx::Dialogs::TCommonDialog inherited;
	
private:
	System::Uitypes::TPageSetupDialogOptions FOptions;
	System::Types::TRect FMargin;
	System::Types::TRect FMinMargin;
	System::Types::TPointF FPaperSize;
	TPageSetupPaintingEvent FPainting;
	System::Uitypes::TPageMeasureUnits FUnits;
	TPaintPageEvent FOnDrawRetAddress;
	TPaintPageEvent FOnDrawMinMargin;
	TPaintPageEvent FOnDrawEnvStamp;
	TPaintPageEvent FOnDrawFullPage;
	TPaintPageEvent FOnDrawGreekText;
	TPaintPageEvent FOnDrawMargin;
	int __fastcall getMinMarginLeft();
	int __fastcall getMinMarginTop();
	int __fastcall getMinMarginRight();
	int __fastcall getMinMarginBottom();
	int __fastcall getMarginLeft();
	int __fastcall getMarginTop();
	int __fastcall getMarginRight();
	int __fastcall getMarginBottom();
	float __fastcall getPageWidth();
	float __fastcall getPageHeight();
	void __fastcall setMinMarginLeft(int Value);
	void __fastcall setMinMarginTop(int Value);
	void __fastcall setMinMarginRight(int Value);
	void __fastcall setMinMarginBottom(int Value);
	void __fastcall setMarginLeft(int Value);
	void __fastcall setMarginTop(int Value);
	void __fastcall setMarginRight(int Value);
	void __fastcall setMarginBottom(int Value);
	void __fastcall setPageWidth(float Value);
	void __fastcall setPageHeight(float Value);
	
protected:
	virtual bool __fastcall DoExecute();
	
public:
	__fastcall virtual TPageSetupDialog(System::Classes::TComponent* AOwner);
	
__published:
	__property int MinMarginLeft = {read=getMinMarginLeft, write=setMinMarginLeft, nodefault};
	__property int MinMarginTop = {read=getMinMarginTop, write=setMinMarginTop, nodefault};
	__property int MinMarginRight = {read=getMinMarginRight, write=setMinMarginRight, nodefault};
	__property int MinMarginBottom = {read=getMinMarginBottom, write=setMinMarginBottom, nodefault};
	__property int MarginLeft = {read=getMarginLeft, write=setMarginLeft, nodefault};
	__property int MarginTop = {read=getMarginTop, write=setMarginTop, nodefault};
	__property int MarginRight = {read=getMarginRight, write=setMarginRight, nodefault};
	__property int MarginBottom = {read=getMarginBottom, write=setMarginBottom, nodefault};
	__property System::Uitypes::TPageSetupDialogOptions Options = {read=FOptions, write=FOptions, default=1};
	__property float PageWidth = {read=getPageWidth, write=setPageWidth};
	__property float PageHeight = {read=getPageHeight, write=setPageHeight};
	__property System::Uitypes::TPageMeasureUnits Units = {read=FUnits, write=FUnits, default=0};
	__property TPageSetupPaintingEvent Painting = {read=FPainting, write=FPainting};
	__property TPaintPageEvent OnDrawFullPage = {read=FOnDrawFullPage, write=FOnDrawFullPage};
	__property TPaintPageEvent OnDrawMinMargin = {read=FOnDrawMinMargin, write=FOnDrawMinMargin};
	__property TPaintPageEvent OnDrawMargin = {read=FOnDrawMargin, write=FOnDrawMargin};
	__property TPaintPageEvent OnDrawGreekText = {read=FOnDrawGreekText, write=FOnDrawGreekText};
	__property TPaintPageEvent OnDrawEnvStamp = {read=FOnDrawEnvStamp, write=FOnDrawEnvStamp};
	__property TPaintPageEvent OnDrawRetAddress = {read=FOnDrawRetAddress, write=FOnDrawRetAddress};
public:
	/* TCommonDialog.Destroy */ inline __fastcall virtual ~TPageSetupDialog() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TPrinterClass __fastcall PrinterClass(void);
extern DELPHI_PACKAGE TPrinter* __fastcall Printer(void);
extern DELPHI_PACKAGE TPrinter* __fastcall SetPrinter(TPrinter* const NewPrinter);
extern DELPHI_PACKAGE bool __fastcall PrinterAssigned(void);
extern DELPHI_PACKAGE void __fastcall AssignPrn(System::TextFile &F);
}	/* namespace Printer */
}	/* namespace Fmx */
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
#endif	// Fmx_PrinterHPP
