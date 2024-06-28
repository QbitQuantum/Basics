// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Wall.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Editor_WallHPP
#define Fmxtee_Editor_WallHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Variants.hpp>
#include <FMX.Types.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.ListBox.hpp>
#include <FMXTee.Chart.hpp>
#include <FMX.Colors.hpp>
#include <FMX.SpinBox.hpp>
#include <FMXTee.Editor.CustomShape.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Wall
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWallEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TWallEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TCheckBox* CBView3dWalls;
	Fmx::Spinbox::TSpinBox* UDAllSize;
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabItem1;
	Fmx::Tabcontrol::TTabItem* TabItem2;
	Fmx::Tabcontrol::TTabItem* TabItem3;
	Fmx::Tabcontrol::TTabItem* TabItem4;
	Fmx::Stdctrls::TPanel* TabSubWalls;
	Fmx::Tabcontrol::TTabControl* TabControl2;
	Fmx::Tabcontrol::TTabItem* TabOptions;
	Fmx::Stdctrls::TCheckBox* CBVisible;
	Fmx::Stdctrls::TCheckBox* CBDark3D;
	Fmx::Stdctrls::TCheckBox* CBAutoHide;
	Fmx::Stdctrls::TGroupBox* GroupBox1;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Spinbox::TSpinBox* UDStart;
	Fmx::Spinbox::TSpinBox* UDEnd;
	Fmx::Stdctrls::TLabel* L33;
	Fmx::Spinbox::TSpinBox* UDWallSize;
	void __fastcall BImageClick(System::TObject* Sender);
	void __fastcall CBView3dWallsChange(System::TObject* Sender);
	void __fastcall UDAllSizeChange(System::TObject* Sender);
	void __fastcall CBVisibleChange(System::TObject* Sender);
	void __fastcall CBDark3DChange(System::TObject* Sender);
	void __fastcall CBAutoHideChange(System::TObject* Sender);
	void __fastcall UDWallSizeChange(System::TObject* Sender);
	void __fastcall UDStartChange(System::TObject* Sender);
	void __fastcall UDEndChange(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	void __fastcall TabControl2Change(System::TObject* Sender);
	
private:
	Fmxtee::Chart::TChartWalls* Walls;
	Fmxtee::Editor::Customshape::TTeeShapeEditor* IShapeForm;
	Fmxtee::Chart::TChartWall* __fastcall Wall();
	void __fastcall RefreshWall(Fmxtee::Chart::TChartWall* const AWall);
	void __fastcall RefreshWalls(Fmxtee::Chart::TChartWalls* const AWalls, Fmxtee::Chart::TChartWall* const AWall = (Fmxtee::Chart::TChartWall*)(0x0));
	
public:
	__classmethod TWallEditor* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Chart::TChartWalls* const AWalls)/* overload */;
	__classmethod TWallEditor* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Chart::TChartWall* const AWall)/* overload */;
public:
	/* TCustomForm.Create */ inline __fastcall virtual TWallEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TWallEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TWallEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Wall */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_WALL)
using namespace Fmxtee::Editor::Wall;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR)
using namespace Fmxtee::Editor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_Editor_WallHPP
