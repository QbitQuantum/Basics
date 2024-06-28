// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEdiWall.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeediwallHPP
#define Vcltee_TeeediwallHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
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
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeCustomShapeEditor.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeediwall
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormTeeWall;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormTeeWall : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TTabControl* TabSubWalls;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TCheckBox* CBView3dWalls;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* EAllSize;
	Vcl::Comctrls::TUpDown* UDAllSize;
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Stdctrls::TLabel* L33;
	Vcl::Stdctrls::TEdit* SEWallSize;
	Vcl::Comctrls::TUpDown* UDWallSize;
	Vcl::Stdctrls::TCheckBox* CBDark3D;
	Vcl::Stdctrls::TCheckBox* CBVisible;
	Vcl::Stdctrls::TCheckBox* CBAutoHide;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TEdit* Edit2;
	Vcl::Comctrls::TUpDown* UDStart;
	Vcl::Stdctrls::TEdit* Edit3;
	Vcl::Comctrls::TUpDown* UDEnd;
	Vcl::Stdctrls::TButton* BVisual;
	void __fastcall TabSubWallsChange(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBView3dWallsClick(System::TObject* Sender);
	void __fastcall SEWallSizeChange(System::TObject* Sender);
	void __fastcall CBDark3DClick(System::TObject* Sender);
	void __fastcall CBVisibleClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBAutoHideClick(System::TObject* Sender);
	void __fastcall EAllSizeChange(System::TObject* Sender);
	void __fastcall Edit2Change(System::TObject* Sender);
	void __fastcall Edit3Change(System::TObject* Sender);
	void __fastcall BVisualClick(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	
private:
	bool SettingAllSize;
	Vcltee::Chart::TCustomChartWall* TheWall;
	Vcltee::Teecustomshapeeditor::TFormTeeShape* ShapeForm;
	void __fastcall SetWallControls();
	Vcltee::Chart::TCustomChart* __fastcall TheChart();
	
public:
	__fastcall TFormTeeWall(System::Classes::TComponent* AOwner, Vcltee::Chart::TCustomChartWall* AWall);
	void __fastcall RefreshControls(Vcltee::Chart::TCustomChartWall* Wall);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormTeeWall(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormTeeWall(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormTeeWall() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormTeeWall(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeediwall */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDIWALL)
using namespace Vcltee::Teeediwall;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeediwallHPP
