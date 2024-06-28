// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeePrevi.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeepreviHPP
#define Vcltee_TeepreviHPP

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
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Printers.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.TeeGDIPlus.hpp>
#include <System.Types.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePreviewPanel.hpp>
#include <VCLTee.TeeNavigator.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeprevi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TChartPreview;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TChartPreview : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* Panel1;
	Vcltee::Tecanvas::TComboFlat* CBPrinters;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Extctrls::TRadioGroup* Orientation;
	Vcl::Stdctrls::TGroupBox* GBMargins;
	Vcl::Stdctrls::TEdit* SETopMa;
	Vcl::Stdctrls::TEdit* SELeftMa;
	Vcl::Stdctrls::TEdit* SEBotMa;
	Vcl::Stdctrls::TEdit* SERightMa;
	Vcl::Stdctrls::TGroupBox* ChangeDetailGroup;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Comctrls::TUpDown* UDLeftMa;
	Vcl::Comctrls::TUpDown* UDTopMa;
	Vcl::Comctrls::TUpDown* UDRightMa;
	Vcl::Comctrls::TUpDown* UDBotMa;
	Vcltee::Teepreviewpanel::TTeePreviewPanel* TeePreviewPanel1;
	Vcl::Comctrls::TTrackBar* Resolution;
	Vcl::Extctrls::TPanel* PanelMargins;
	Vcl::Stdctrls::TButton* BReset;
	Vcl::Stdctrls::TCheckBox* ShowMargins;
	Vcl::Extctrls::TPanel* PanelOptions;
	Vcl::Stdctrls::TCheckBox* CBProp;
	Vcl::Stdctrls::TCheckBox* CBBitmap;
	Vcl::Extctrls::TPanel* PanelClose;
	Vcl::Stdctrls::TButton* BClose;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Stdctrls::TButton* BSetupPrinter;
	Vcl::Stdctrls::TButton* BPrint;
	Vcl::Stdctrls::TCheckBox* CBPrintPanel;
	Vcl::Stdctrls::TButton* Button1;
	Vcl::Extctrls::TPanel* MarginsExpand;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Extctrls::TImage* TriDown;
	Vcl::Extctrls::TImage* TriUp;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall BSetupPrinterClick(System::TObject* Sender);
	void __fastcall CBPrintersChange(System::TObject* Sender);
	void __fastcall OrientationClick(System::TObject* Sender);
	void __fastcall SETopMaChange(System::TObject* Sender);
	void __fastcall SERightMaChange(System::TObject* Sender);
	void __fastcall SEBotMaChange(System::TObject* Sender);
	void __fastcall SELeftMaChange(System::TObject* Sender);
	void __fastcall ShowMarginsClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall BResetClick(System::TObject* Sender);
	void __fastcall BPrintClick(System::TObject* Sender);
	void __fastcall BCloseClick(System::TObject* Sender);
	void __fastcall CBPropClick(System::TObject* Sender);
	void __fastcall TeePreviewPanel1ChangeMargins(System::TObject* Sender, bool DisableProportional, const System::Types::TRect &NewMargins);
	void __fastcall TrackBar1Change(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall CBBitmapClick(System::TObject* Sender);
	void __fastcall Panel1Resize(System::TObject* Sender);
	void __fastcall CBPrintPanelClick(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, System::Uitypes::TCloseAction &Action);
	void __fastcall Label4Click(System::TObject* Sender);
	void __fastcall TriDownClick(System::TObject* Sender);
	
private:
	bool ChangingMargins;
	bool ChangingProp;
	System::Types::TRect OldMargins;
	Vcltee::Teenavigator::TCustomTeeNavigator* PageNavigator1;
	void __fastcall Navigator1ButtonClicked(Vcltee::Teenavigator::TTeeNavigateBtn Index);
	void __fastcall ResetMargins();
	void __fastcall CheckOrientation();
	void __fastcall ChangeMargin(Vcl::Comctrls::TUpDown* UpDown, int &APos, int OtherSide);
	
public:
	Vcltee::Teenavigator::TTeePageNavigatorClass PageNavigatorClass;
	Vcl::Dialogs::TPrinterSetupDialog* PrinterSetupDialog1;
	void __fastcall HideCloseButton();
	Vcltee::Teepreviewpanel::TTeePreviewPanel* __fastcall PreviewPanel();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TChartPreview(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TChartPreview(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TChartPreview() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TChartPreview(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool TeeChangePaperOrientation;
extern DELPHI_PACKAGE void __fastcall TeePreview(System::Classes::TComponent* AOwner, Vcltee::Teeprocs::TCustomTeePanel* APanel);
}	/* namespace Teeprevi */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEPREVI)
using namespace Vcltee::Teeprevi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeepreviHPP
