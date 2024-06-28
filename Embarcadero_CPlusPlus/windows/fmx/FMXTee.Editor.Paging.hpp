// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Paging.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Editor_PagingHPP
#define Fmxtee_Editor_PagingHPP

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
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Dialogs.hpp>
#include <FMXTee.Engine.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Paging
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPagingEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPagingEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TLabel* L17;
	Fmx::Stdctrls::TLabel* LabelPages;
	Fmx::Stdctrls::TCheckBox* CBScaleLast;
	Fmx::Spinbox::TSpinBox* UDPointsPerPage;
	Fmx::Stdctrls::TCheckBox* CBPageLegend;
	Fmx::Stdctrls::TCheckBox* CBPageNum;
	Fmx::Stdctrls::TCheckBox* CBAutoScale;
	Fmx::Stdctrls::TCheckBox* CBNoPages;
	Fmx::Stdctrls::TButton* BEditTool;
	Fmx::Stdctrls::TButton* BPrev;
	Fmx::Stdctrls::TButton* BNext;
	Fmx::Stdctrls::TButton* BLast;
	Fmx::Stdctrls::TButton* BFirst;
	void __fastcall ChartPageNavigator1ButtonClicked();
	void __fastcall BEditToolClick(System::TObject* Sender);
	void __fastcall CBNoPagesChange(System::TObject* Sender);
	void __fastcall CBPageLegendChange(System::TObject* Sender);
	void __fastcall CBScaleLastChange(System::TObject* Sender);
	void __fastcall CBAutoScaleChange(System::TObject* Sender);
	void __fastcall BPrevClick(System::TObject* Sender);
	void __fastcall BNextClick(System::TObject* Sender);
	void __fastcall UDPointsPerPageChangeTracking(System::TObject* Sender);
	void __fastcall BFirstClick(System::TObject* Sender);
	void __fastcall BLastClick(System::TObject* Sender);
	void __fastcall CBPageNumChange(System::TObject* Sender);
	void __fastcall UDPointsPerPageChange(System::TObject* Sender);
	
private:
	Fmxtee::Engine::TChartPage* Paging;
	Fmxtee::Engine::TTeeCustomTool* __fastcall PageNumTool(bool CreateTool);
	void __fastcall RefreshLabelPages();
	void __fastcall RefreshPaging(Fmxtee::Engine::TChartPage* const APaging);
	void __fastcall SetEditTool();
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TChartPage* const APaging);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TPagingEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TPagingEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TPagingEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Paging */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_PAGING)
using namespace Fmxtee::Editor::Paging;
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
#endif	// Fmxtee_Editor_PagingHPP
