// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeCustomShapeEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeecustomshapeeditorHPP
#define Vcltee_TeecustomshapeeditorHPP

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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeEdiGrad.hpp>
#include <VCLTee.TeeEdiFont.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeShadowEditor.hpp>
#include <VCLTee.TeeBackImage.hpp>
#include <VCLTee.TeeBrushDlg.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teecustomshapeeditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormTeeShape;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormTeeShape : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PC1;
	Vcl::Comctrls::TTabSheet* TabFormat;
	Vcltee::Tecanvas::TButtonColor* BBackColor;
	Vcl::Stdctrls::TCheckBox* CBTransparent;
	Vcl::Comctrls::TTabSheet* TabPattern;
	Vcl::Comctrls::TTabSheet* TabText;
	Vcl::Comctrls::TTabSheet* TabShadow;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Comctrls::TTabSheet* TabImage;
	Vcl::Comctrls::TTabSheet* TabBorder;
	Vcl::Comctrls::TTabSheet* TabEmboss;
	Vcl::Comctrls::TTrackBar* TBTransp;
	Vcl::Stdctrls::TLabel* LTransp;
	Vcl::Comctrls::TPageControl* PageBorder;
	Vcl::Comctrls::TTabSheet* TabSheet2;
	Vcl::Comctrls::TTabSheet* TabBorderPen;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TEdit* EBevWidth;
	Vcl::Comctrls::TUpDown* UDBevW;
	Vcl::Comctrls::TTabSheet* TabSheet3;
	Vcl::Stdctrls::TLabel* Label5;
	Vcltee::Tecanvas::TComboFlat* CBSide;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Comctrls::TTrackBar* TBSize;
	Vcl::Stdctrls::TLabel* LSize;
	Vcl::Stdctrls::TLabel* Label7;
	Vcl::Comctrls::TTrackBar* TBPosition;
	Vcl::Stdctrls::TLabel* LPosition;
	Vcl::Stdctrls::TLabel* Label8;
	Vcl::Comctrls::TTrackBar* TBWidth;
	Vcl::Stdctrls::TLabel* LWidth;
	Vcl::Comctrls::TTabSheet* TabSheet4;
	Vcl::Extctrls::TRadioGroup* RGBevel;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TCheckBox* CBRound;
	Vcl::Stdctrls::TEdit* ERoundSize;
	Vcl::Comctrls::TUpDown* UDRoundSize;
	Vcl::Stdctrls::TGroupBox* GroupCorners;
	Vcl::Comctrls::TTabSheet* TabChildren;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Extctrls::TPanel* Panel2;
	Vcltee::Tecanvas::TComboFlat* CBLayout;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Stdctrls::TListBox* LBChildren;
	Vcl::Buttons::TSpeedButton* BAdd;
	Vcl::Buttons::TSpeedButton* BDelete;
	Vcl::Stdctrls::TCheckBox* CBVisible;
	Vcltee::Tecanvas::TComboFlat* CBLeftTop;
	Vcltee::Tecanvas::TComboFlat* CBLeftBottom;
	Vcltee::Tecanvas::TComboFlat* CBRightTop;
	Vcltee::Tecanvas::TComboFlat* CBRightBottom;
	void __fastcall BColorClick(System::TObject* Sender);
	void __fastcall CBRoundClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBTransparentClick(System::TObject* Sender);
	void __fastcall EBevWidthChange(System::TObject* Sender);
	void __fastcall CBVisibleChecked(System::TObject* Sender);
	void __fastcall ERoundSizeChange(System::TObject* Sender);
	void __fastcall PC1Change(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall PageBorderChange(System::TObject* Sender);
	void __fastcall CBSideChange(System::TObject* Sender);
	void __fastcall TBSizeChange(System::TObject* Sender);
	void __fastcall TBPositionChange(System::TObject* Sender);
	void __fastcall TBWidthChange(System::TObject* Sender);
	void __fastcall RGBevelClick(System::TObject* Sender);
	void __fastcall LBChildrenClick(System::TObject* Sender);
	void __fastcall BAddClick(System::TObject* Sender);
	void __fastcall BDeleteClick(System::TObject* Sender);
	void __fastcall CBLayoutChange(System::TObject* Sender);
	void __fastcall CBVisibleClick(System::TObject* Sender);
	void __fastcall PC1GetImageIndex(System::TObject* Sender, int TabIndex, int &ImageIndex);
	void __fastcall CBLeftTopChange(System::TObject* Sender);
	void __fastcall CBLeftBottomChange(System::TObject* Sender);
	void __fastcall CBRightTopChange(System::TObject* Sender);
	void __fastcall CBRightBottomChange(System::TObject* Sender);
	
private:
	bool CreatingForm;
	Vcltee::Teependlg::TPenDialog* FBorderEditor;
	Vcltee::Teeshadoweditor::TTeeShadowEditor* FEmbossEditor;
	Vcltee::Teeedifont::TTeeFontEditor* FFontEditor;
	Vcltee::Teebrushdlg::TBrushDialog* FBrushEditor;
	Vcltee::Teebackimage::TBackImageEditor* FImageEditor;
	Vcltee::Teeshadoweditor::TTeeShadowEditor* FShadowEditor;
	Vcl::Forms::TForm* IChildEditor;
	void __fastcall AddChildItem(int Index);
	void __fastcall EnableBevel();
	
public:
	Vcltee::Teeprocs::TTeeCustomShape* TheShape;
	__fastcall virtual TFormTeeShape(System::Classes::TComponent* AOwner);
	__classmethod TFormTeeShape* __fastcall CreateForm(System::Classes::TComponent* const AOwner, Vcltee::Teeprocs::TTeeCustomShape* const AShape, Vcl::Controls::TWinControl* const AParent = (Vcl::Controls::TWinControl*)(0x0));
	void __fastcall RefreshControls(Vcltee::Teeprocs::TTeeCustomShape* const AShape);
	__classmethod void __fastcall InsertTeeForm(Vcl::Comctrls::TPageControl* const Source, Vcl::Comctrls::TPageControl* const Dest);
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormTeeShape(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormTeeShape() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormTeeShape(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TFormTeeShape* __fastcall InsertTeeObjectForm(Vcl::Comctrls::TPageControl* const APageControl, Vcltee::Teeprocs::TTeeCustomShape* const AShape);
extern DELPHI_PACKAGE bool __fastcall EditTeeCustomShape(System::Classes::TComponent* const AOwner, Vcltee::Teeprocs::TTeeCustomShape* const AShape, bool HideText = false, const System::UnicodeString ACaption = System::UnicodeString());
}	/* namespace Teecustomshapeeditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEECUSTOMSHAPEEDITOR)
using namespace Vcltee::Teecustomshapeeditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeecustomshapeeditorHPP
