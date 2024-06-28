// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeAreaEdit.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeareaeditHPP
#define Vcltee_TeeareaeditHPP

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
#include <System.UITypes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeareaedit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAreaSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAreaSeriesEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Comctrls::TTabSheet* TabSheet2;
	Vcl::Extctrls::TRadioGroup* RGMultiArea;
	Vcl::Stdctrls::TGroupBox* GroupBox3;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TCheckBox* CBUseOrigin;
	Vcl::Stdctrls::TEdit* EOrigin;
	Vcl::Comctrls::TUpDown* UDOrigin;
	Vcl::Stdctrls::TGroupBox* GroupBox2;
	Vcl::Stdctrls::TCheckBox* CBStairs;
	Vcl::Stdctrls::TCheckBox* CBInvStairs;
	Vcl::Stdctrls::TCheckBox* CBDark3D;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TCheckBox* CBColorEach;
	Vcltee::Tecanvas::TButtonColor* BAreaColor;
	Vcltee::Tecanvas::TComboFlat* CBNulls;
	Vcl::Stdctrls::TGroupBox* GroupBox6;
	Vcl::Stdctrls::TEdit* EGroup;
	Vcl::Comctrls::TUpDown* UDGroup;
	Vcl::Stdctrls::TCheckBox* CBSmoothed;
	Vcl::Stdctrls::TCheckBox* CBDefColor;
	Vcl::Comctrls::TTabSheet* TabBorder;
	Vcl::Comctrls::TTabSheet* TabPattern;
	Vcl::Comctrls::TTabSheet* TabAreaLines;
	Vcl::Comctrls::TTabSheet* TabTop;
	Vcl::Comctrls::TTrackBar* TBTransp;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* LTransp;
	Vcltee::Tecanvas::TComboFlat* CBDrawStyle;
	Vcl::Stdctrls::TLabel* LDrawStyle;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall RGMultiAreaClick(System::TObject* Sender);
	void __fastcall CBColorEachClick(System::TObject* Sender);
	void __fastcall CBStairsClick(System::TObject* Sender);
	void __fastcall CBInvStairsClick(System::TObject* Sender);
	void __fastcall CBUseOriginClick(System::TObject* Sender);
	void __fastcall EOriginChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall CBNullsChange(System::TObject* Sender);
	void __fastcall CBDark3DClick(System::TObject* Sender);
	void __fastcall EGroupChange(System::TObject* Sender);
	void __fastcall CBSmoothedClick(System::TObject* Sender);
	void __fastcall CBDefColorClick(System::TObject* Sender);
	void __fastcall BAreaColorClick(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall CBDrawStyleChange(System::TObject* Sender);
	
private:
	Vcltee::Series::TAreaSeries* Area;
	Vcl::Forms::TCustomForm* PointerForm;
	bool CreatingForm;
	void __fastcall EnableOrigin();
	System::Uitypes::TColor __fastcall GetAreaColor();
	void __fastcall RefreshShape();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TAreaSeriesEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TAreaSeriesEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TAreaSeriesEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TAreaSeriesEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeareaedit */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEAREAEDIT)
using namespace Vcltee::Teeareaedit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeareaeditHPP
