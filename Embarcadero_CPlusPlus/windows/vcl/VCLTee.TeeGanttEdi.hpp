// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeGanttEdi.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeganttediHPP
#define Vcltee_TeeganttediHPP

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
#include <VCLTee.Chart.hpp>
#include <VCLTee.GanttCh.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeePoEdi.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeganttedi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGanttSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TGanttSeriesEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabGanttOptions;
	Vcl::Comctrls::TTabSheet* TabGanttCallout;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TEdit* SEPointVertSize;
	Vcltee::Teependlg::TButtonPen* BConnLines;
	Vcl::Comctrls::TUpDown* UDPointVertSize;
	Vcl::Stdctrls::TGroupBox* GPLine;
	Vcltee::Tecanvas::TButtonColor* BColor;
	Vcl::Stdctrls::TCheckBox* CBColorEach;
	Vcl::Comctrls::TTrackBar* TBTransp;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall SEPointVertSizeChange(System::TObject* Sender);
	void __fastcall CBColorEachClick(System::TObject* Sender);
	void __fastcall BColorClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	
private:
	Vcltee::Teepoedi::TSeriesPointerEditor* ICallout;
	Vcl::Forms::TCustomForm* PointerForm;
	Vcltee::Ganttch::TGanttSeries* TheSeries;
	void __fastcall RefreshShape();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TGanttSeriesEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TGanttSeriesEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TGanttSeriesEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TGanttSeriesEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeganttedi */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEGANTTEDI)
using namespace Vcltee::Teeganttedi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeganttediHPP
