// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeExport.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeexportHPP
#define Vcltee_TeeexportHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeConst.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeexport
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTeeExportFormat;
class DELPHICLASS TTeeExportFormBase;
class DELPHICLASS TTeeExportFormats;
//-- type declarations -------------------------------------------------------
typedef System::WideChar TeeSeparatorChar;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeExportFormat : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Vcltee::Teeprocs::TCustomTeePanel* FPanel;
	float FScale;
	
protected:
	int FFilterIndex;
	void __fastcall CheckSize()/* overload */;
	void __fastcall CheckSize(int Width, int Height)/* overload */;
	Vcl::Forms::TForm* __fastcall CreateProperties(const System::UnicodeString AFormClass);
	virtual void __fastcall DoCopyToClipboard() = 0 ;
	virtual int __fastcall FileFilterIndex();
	Vcl::Graphics::TBitmap* __fastcall GetBitmap(Vcl::Graphics::TPixelFormat APixelFormat = (Vcl::Graphics::TPixelFormat)(0x0), int ADpi = 0x0);
	virtual void __fastcall IncFileFilterIndex(int &FilterIndex);
	System::Types::TRect __fastcall ScaledRect();
	virtual bool __fastcall WantsFilterIndex(int Index);
	
public:
	int Height;
	int Width;
	__fastcall virtual TTeeExportFormat();
	__fastcall virtual ~TTeeExportFormat();
	void __fastcall CopyToClipboard();
	virtual System::UnicodeString __fastcall Description() = 0 ;
	virtual System::UnicodeString __fastcall FileExtension() = 0 ;
	__classmethod virtual System::UnicodeString __fastcall FileFilter();
	virtual Vcl::Graphics::TGraphicClass __fastcall GraphicClass();
	virtual Vcl::Forms::TForm* __fastcall Options(bool Check = true);
	void __fastcall SaveToFile(const System::UnicodeString FileName)/* overload */;
	void __fastcall SaveToFile(const System::UnicodeString FileName, Vcl::Forms::TForm* const AOptions)/* overload */;
	__classmethod void __fastcall SaveToFile(Vcltee::Teeprocs::TCustomTeePanel* APanel, const System::UnicodeString FileName)/* overload */;
	__classmethod void __fastcall SaveToFile(Vcltee::Teeprocs::TCustomTeePanel* APanel, const System::UnicodeString FileName, Vcl::Forms::TForm* const AOptions, int AWidth, int AHeight)/* overload */;
	virtual void __fastcall SaveToStream(System::Classes::TStream* Stream) = 0 /* overload */;
	virtual void __fastcall SaveToStream(System::Classes::TStream* Stream, Vcl::Forms::TForm* const AOptions)/* overload */;
	__property Vcltee::Teeprocs::TCustomTeePanel* Panel = {read=FPanel, write=FPanel};
	__property float Scale = {read=FScale, write=FScale};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TTeeExportFormBase : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Dialogs::TSaveDialog* SaveDialogPicture;
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabPicture;
	Vcl::Comctrls::TTabSheet* TabData;
	Vcl::Stdctrls::TGroupBox* RGFormat;
	Vcl::Dialogs::TSaveDialog* SaveDialogData;
	Vcl::Comctrls::TTabSheet* TabNative;
	Vcl::Stdctrls::TCheckBox* CBNativeData;
	Vcl::Dialogs::TSaveDialog* SaveDialogNative;
	Vcl::Stdctrls::TLabel* LabelSize;
	Vcl::Stdctrls::TCheckBox* CBFileSize;
	Vcl::Comctrls::TPageControl* PageOptions;
	Vcl::Comctrls::TTabSheet* TabOptions;
	Vcl::Comctrls::TTabSheet* TabSize;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TEdit* EWidth;
	Vcl::Comctrls::TUpDown* UDWidth;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* EHeight;
	Vcl::Comctrls::TUpDown* UDHeight;
	Vcl::Stdctrls::TCheckBox* CBAspect;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TButton* BCopy;
	Vcl::Stdctrls::TButton* BSave;
	Vcl::Stdctrls::TButton* BSend;
	Vcl::Stdctrls::TListBox* LBFormat;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Extctrls::TSplitter* SplitPic;
	Vcl::Extctrls::TRadioGroup* CBNativeFormat;
	Vcl::Stdctrls::TButton* BViewNative;
	Vcl::Stdctrls::TCheckBox* CBPicSize;
	Vcl::Stdctrls::TLabel* LabelPicSize;
	Vcl::Extctrls::TPanel* Panel4;
	Vcl::Extctrls::TPanel* Panel5;
	Vcl::Stdctrls::TLabel* Label3;
	Vcltee::Tecanvas::TComboFlat* CBSeries;
	Vcl::Extctrls::TRadioGroup* RGText;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Comctrls::TPageControl* PageDataOptions;
	Vcl::Comctrls::TTabSheet* TabInclude;
	Vcl::Stdctrls::TCheckBox* CBIndex;
	Vcl::Stdctrls::TCheckBox* CBLabels;
	Vcl::Stdctrls::TCheckBox* CBHeader;
	Vcl::Stdctrls::TCheckBox* CBColors;
	Vcl::Comctrls::TTabSheet* TabDataOptions;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Stdctrls::TLabel* LabelEncoding;
	Vcl::Stdctrls::TLabel* LabelXML;
	Vcltee::Tecanvas::TComboFlat* CBDelim;
	Vcl::Stdctrls::TEdit* ECustom;
	Vcl::Stdctrls::TEdit* EQuotes;
	Vcltee::Tecanvas::TComboFlat* CBEncoding;
	Vcltee::Tecanvas::TComboFlat* CBXMLEncoding;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TPanel* PanelPreview;
	Vcl::Stdctrls::TCheckBox* CBDataPreview;
	Vcl::Stdctrls::TMemo* MemoData;
	Vcl::Stdctrls::TButton* BPreview;
	Vcl::Stdctrls::TButton* BClose;
	Vcl::Stdctrls::TLabel* LScale;
	Vcltee::Tecanvas::TComboFlat* CBScale;
	Vcl::Comctrls::TTabSheet* TabJSON;
	Vcl::Extctrls::TRadioGroup* RGJsonDate;
	void __fastcall BCopyClick(System::TObject* Sender);
	void __fastcall BSaveClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall RGFormatClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall EWidthChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall RGTextClick(System::TObject* Sender);
	void __fastcall CBFileSizeClick(System::TObject* Sender);
	void __fastcall CBNativeDataClick(System::TObject* Sender);
	void __fastcall CBDelimChange(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall BSendClick(System::TObject* Sender);
	void __fastcall Panel5Resize(System::TObject* Sender);
	void __fastcall CBNativeFormatClick(System::TObject* Sender);
	void __fastcall BViewNativeClick(System::TObject* Sender);
	void __fastcall CBPicSizeClick(System::TObject* Sender);
	void __fastcall PageOptionsChange(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, System::Uitypes::TCloseAction &Action);
	void __fastcall CBDataPreviewClick(System::TObject* Sender);
	void __fastcall CBSeriesChange(System::TObject* Sender);
	void __fastcall CBIndexClick(System::TObject* Sender);
	void __fastcall ECustomChange(System::TObject* Sender);
	void __fastcall EQuotesChange(System::TObject* Sender);
	void __fastcall CBXMLEncodingChange(System::TObject* Sender);
	void __fastcall SeriesValueFormatChange(System::TObject* Sender);
	void __fastcall BPreviewClick(System::TObject* Sender);
	void __fastcall CBScaleChange(System::TObject* Sender);
	void __fastcall RGJsonDateClick(System::TObject* Sender);
	
private:
	bool ChangingSize;
	System::Classes::TStrings* Formats;
	double IAspect;
	bool __fastcall CanChangeSize();
	void __fastcall CheckFileSize();
	int __fastcall GetDataFilterIndex();
	TTeeExportFormat* __fastcall GuessPictureFormat(const System::UnicodeString FileName);
	void __fastcall FreeExportFormats();
	System::UnicodeString __fastcall NativeAsString();
	TTeeExportFormat* __fastcall PictureFormat();
	void __fastcall SaveNativeToFile(const System::UnicodeString FileName);
	void __fastcall SavePictureToFile(const System::UnicodeString FileName);
	
protected:
	virtual Vcltee::Teeprocs::TTeeExportData* __fastcall CreateData();
	virtual System::Classes::TStream* __fastcall CreateNativeStream();
	System::UnicodeString __fastcall CreateTempFile();
	virtual void __fastcall DoSaveNativeToFile(const System::UnicodeString FileName, bool IncludeData);
	virtual bool __fastcall ExistData();
	System::UnicodeString __fastcall GetNativeExtension();
	System::UnicodeString __fastcall GetNativeFilter();
	System::WideChar __fastcall GetSeparator();
	bool __fastcall NativeAsText();
	virtual void __fastcall PrepareOnShow();
	void __fastcall SaveDataToFile(const System::UnicodeString FileName);
	System::Sysutils::TEncoding* __fastcall SelectedEncoding();
	void __fastcall TryPreviewData();
	
public:
	Vcltee::Teeprocs::TCustomTeePanel* ExportPanel;
	System::UnicodeString EmailName;
	System::UnicodeString NativeFilter;
	System::UnicodeString NativeExtension;
	System::UnicodeString DataFilter;
	System::UnicodeString InitDir;
	void __fastcall EnableButtons();
	__classmethod System::UnicodeString __fastcall GetTempFolder();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTeeExportFormBase(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTeeExportFormBase(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTeeExportFormBase() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTeeExportFormBase(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


#ifndef _WIN64
typedef System::TMetaClass* TTeeExportFormatClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TTeeExportFormatClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTeeExportFormats : public System::Classes::TList
{
	typedef System::Classes::TList inherited;
	
public:
	TTeeExportFormatClass operator[](int Index) { return this->Format[Index]; }
	
private:
	HIDESBASE TTeeExportFormatClass __fastcall Get(int Index);
	
public:
	__property TTeeExportFormatClass Format[int Index] = {read=Get/*, default*/};
public:
	/* TList.Destroy */ inline __fastcall virtual ~TTeeExportFormats() { }
	
public:
	/* TObject.Create */ inline __fastcall TTeeExportFormats() : System::Classes::TList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TTeeExportFormats* TeeExportFormats;
extern DELPHI_PACKAGE Vcl::Graphics::TGraphic* __fastcall WithFileExtension(const System::UnicodeString FileExtension);
extern DELPHI_PACKAGE void __fastcall SaveTeeToStream(Vcltee::Teeprocs::TCustomTeePanel* const APanel, System::Classes::TStream* const AStream);
extern DELPHI_PACKAGE void __fastcall SaveTeeToFile(Vcltee::Teeprocs::TCustomTeePanel* const APanel, const System::UnicodeString AName);
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeToString(Vcltee::Teeprocs::TCustomTeePanel* const APanel);
extern DELPHI_PACKAGE void __fastcall LoadTeeFromStream(Vcltee::Teeprocs::TCustomTeePanel* &APanel, System::Classes::TStream* AStream);
extern DELPHI_PACKAGE void __fastcall LoadTeeFromFile(Vcltee::Teeprocs::TCustomTeePanel* &APanel, const System::UnicodeString AName);
extern DELPHI_PACKAGE void __fastcall TeeFillPictureDialog(Vcl::Dialogs::TSaveDialog* const ADialog, Vcltee::Teeprocs::TCustomTeePanel* const APanel, System::Classes::TStrings* const AItems);
extern DELPHI_PACKAGE void __fastcall RegisterTeeExportFormat(TTeeExportFormatClass AFormat);
extern DELPHI_PACKAGE void __fastcall UnRegisterTeeExportFormat(TTeeExportFormatClass AFormat);
extern DELPHI_PACKAGE void __fastcall TeeExportSavePanel(const TTeeExportFormatClass AFormat, Vcltee::Teeprocs::TCustomTeePanel* const APanel);
extern DELPHI_PACKAGE void __fastcall InternalTeeEmailFile(const System::UnicodeString FileName, const System::UnicodeString Subject = L"TeeChart");
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetRegistryHelpPath(const System::UnicodeString HelpFile);
}	/* namespace Teeexport */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEXPORT)
using namespace Vcltee::Teeexport;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeexportHPP
