// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeFLineEdi.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeflineediHPP
#define Vcltee_TeeflineediHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.Classes.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeflineedi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFastLineSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFastLineSeriesEditor : public Vcltee::Teependlg::TPenDialog
{
	typedef Vcltee::Teependlg::TPenDialog inherited;
	
__published:
	Vcl::Comctrls::TTabSheet* TabSheet3;
	Vcl::Stdctrls::TGroupBox* GBStair;
	Vcl::Stdctrls::TCheckBox* CBStairs;
	Vcl::Stdctrls::TCheckBox* CBInvStairs;
	Vcltee::Tecanvas::TComboFlat* CBNulls;
	Vcl::Stdctrls::TCheckBox* CBDrawAll;
	Vcltee::Tecanvas::TComboFlat* CBDrawAllStyle;
	Vcl::Stdctrls::TCheckBox* CBFastPen;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* Label4;
	Vcltee::Tecanvas::TComboFlat* CBDrawStyle;
	HIDESBASE void __fastcall FormShow(System::TObject* Sender);
	HIDESBASE void __fastcall BColorClick(System::TObject* Sender);
	void __fastcall CBDrawAllClick(System::TObject* Sender);
	void __fastcall CBStairsClick(System::TObject* Sender);
	void __fastcall CBInvStairsClick(System::TObject* Sender);
	void __fastcall CBNullsChange(System::TObject* Sender);
	void __fastcall CBDrawAllStyleChange(System::TObject* Sender);
	void __fastcall CBFastPenClick(System::TObject* Sender);
	void __fastcall CBDrawStyleChange(System::TObject* Sender);
	
private:
	Vcltee::Series::TFastLineSeries* FastLine;
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFastLineSeriesEditor(System::Classes::TComponent* AOwner) : Vcltee::Teependlg::TPenDialog(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFastLineSeriesEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcltee::Teependlg::TPenDialog(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFastLineSeriesEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFastLineSeriesEditor(HWND ParentWindow) : Vcltee::Teependlg::TPenDialog(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeflineedi */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEFLINEEDI)
using namespace Vcltee::Teeflineedi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeflineediHPP
