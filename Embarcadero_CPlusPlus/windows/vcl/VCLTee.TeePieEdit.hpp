// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeePieEdit.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeepieeditHPP
#define Vcltee_TeepieeditHPP

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
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeCircledEdit.hpp>
#include <VCLTee.TeeEdiGrad.hpp>
#include <VCLTee.TeeFrames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teepieedit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPieSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPieSeriesEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabOptions;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* LTransparency;
	Vcl::Stdctrls::TLabel* LEdgeStyle;
	Vcl::Stdctrls::TCheckBox* CBDark3d;
	Vcl::Stdctrls::TEdit* SEExpBig;
	Vcl::Comctrls::TUpDown* UDExpBig;
	Vcl::Stdctrls::TCheckBox* CBPatterns;
	Vcl::Stdctrls::TEdit* Edit1;
	Vcl::Comctrls::TUpDown* UDAngleSize;
	Vcltee::Tecanvas::TComboFlat* CBMultiple;
	Vcltee::Tecanvas::TComboFlat* CBEdgeStyle;
	Vcl::Comctrls::TTabSheet* TabGroup;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Stdctrls::TLabel* Label9;
	Vcl::Stdctrls::TCheckBox* CBColorEach;
	Vcltee::Tecanvas::TButtonColor* BColor;
	Vcltee::Tecanvas::TComboFlat* CBPalette;
	Vcl::Comctrls::TTabSheet* TabSheet2;
	Vcl::Stdctrls::TLabel* Label8;
	Vcl::Stdctrls::TCheckBox* CBMarksAutoPosition;
	Vcl::Stdctrls::TCheckBox* CBVertCenter;
	Vcl::Comctrls::TTabSheet* TabFrame;
	Vcl::Comctrls::TTabSheet* TabGradient;
	Vcl::Stdctrls::TLabel* Label11;
	Vcl::Stdctrls::TLabel* LLegSize;
	Vcl::Comctrls::TTabSheet* TabBorders;
	Vcl::Stdctrls::TCheckBox* CBMarksInside;
	Vcl::Comctrls::TPageControl* PageControl2;
	Vcl::Comctrls::TTabSheet* TabBevel;
	Vcl::Comctrls::TTabSheet* TabBorder;
	Vcl::Stdctrls::TLabel* LBevelPercent;
	Vcl::Stdctrls::TLabel* Label12;
	Vcl::Stdctrls::TLabel* LBevelBright;
	Vcl::Comctrls::TTrackBar* TBBevelBright;
	Vcl::Stdctrls::TCheckBox* CBBevelBorder;
	Vcl::Comctrls::TTrackBar* TBTransp;
	Vcl::Comctrls::TTrackBar* TBBevel;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Comctrls::TTrackBar* TBDark;
	Vcl::Comctrls::TPageControl* PageControl3;
	Vcl::Comctrls::TTabSheet* TabSheet3;
	Vcl::Comctrls::TTabSheet* TabLegend;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Stdctrls::TLabel* Label7;
	Vcltee::Tecanvas::TComboFlat* CBOther;
	Vcl::Stdctrls::TEdit* EOtherValue;
	Vcl::Stdctrls::TEdit* EOtherLabel;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TLabel* Label10;
	Vcl::Stdctrls::TLabel* LBright;
	Vcl::Comctrls::TTrackBar* TBBright;
	Vcl::Stdctrls::TCheckBox* CBRotated;
	Vcl::Comctrls::TTrackBar* TBLegSize;
	Vcl::Stdctrls::TCheckBox* CBMarksEmpty;
	Vcl::Stdctrls::TLabel* LBevelPerc;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBDark3dClick(System::TObject* Sender);
	void __fastcall CBPatternsClick(System::TObject* Sender);
	void __fastcall CBOtherChange(System::TObject* Sender);
	void __fastcall EOtherValueChange(System::TObject* Sender);
	void __fastcall EOtherLabelChange(System::TObject* Sender);
	void __fastcall SEExpBigChange(System::TObject* Sender);
	void __fastcall Edit1Change(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBMarksAutoPositionClick(System::TObject* Sender);
	void __fastcall CBMultipleChange(System::TObject* Sender);
	void __fastcall CBColorEachClick(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall CBVertCenterClick(System::TObject* Sender);
	void __fastcall CBPaletteChange(System::TObject* Sender);
	void __fastcall TBBrightChange(System::TObject* Sender);
	void __fastcall CBEdgeStyleChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall TBBevelBrightChange(System::TObject* Sender);
	void __fastcall CBBevelBorderClick(System::TObject* Sender);
	void __fastcall CBMarksInsideClick(System::TObject* Sender);
	void __fastcall PageControl2Change(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall TBBevelChange(System::TObject* Sender);
	void __fastcall TBDarkChange(System::TObject* Sender);
	void __fastcall PageControl3Change(System::TObject* Sender);
	void __fastcall CBRotatedClick(System::TObject* Sender);
	void __fastcall TBLegSizeChange(System::TObject* Sender);
	void __fastcall CBMarksEmptyClick(System::TObject* Sender);
	
private:
	Vcltee::Series::TPieSeries* Pie;
	Vcltee::Teecirclededit::TCircledSeriesEditor* tmpCircled;
	
public:
	void __fastcall CheckCircledEditor();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TPieSeriesEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TPieSeriesEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TPieSeriesEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TPieSeriesEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teepieedit */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEPIEEDIT)
using namespace Vcltee::Teepieedit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeepieeditHPP
