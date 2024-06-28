// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeePenDlg.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeependlgHPP
#define Vcltee_TeependlgHPP

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
#include <Vcl.FileCtrl.hpp>
#include <System.UITypes.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>
#include <VCLTee.TeeEdiGrad.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teependlg
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPenDialog;
class DELPHICLASS TButtonPen;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPenDialog : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* PanelButtons;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Comctrls::TTabSheet* TabSheet2;
	Vcl::Comctrls::TTabSheet* TabGradient;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcltee::Tecanvas::TComboFlat* CBEndStyle;
	Vcltee::Tecanvas::TComboFlat* CBJoinStyle;
	Vcl::Stdctrls::TCheckBox* CBVisible;
	Vcltee::Tecanvas::TButtonColor* BColor;
	Vcl::Stdctrls::TLabel* LWidth;
	Vcl::Comctrls::TTrackBar* TBSize;
	Vcl::Stdctrls::TLabel* LSize;
	Vcl::Comctrls::TTabSheet* TabStyle;
	Vcl::Extctrls::TPanel* Panel1;
	Vcltee::Tecanvas::TComboFlat* CBStyle;
	Vcltee::Teegallerypanel::TChartGalleryPanel* Styles;
	Vcl::Stdctrls::TLabel* LSpace;
	Vcl::Stdctrls::TEdit* ESpace;
	Vcl::Comctrls::TUpDown* UDSpace;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Stdctrls::TButton* BOk;
	Vcl::Stdctrls::TButton* BCancel;
	Vcl::Stdctrls::TLabel* LTransp;
	Vcl::Comctrls::TTrackBar* TBTransp;
	Vcl::Stdctrls::TCheckBox* CBDefColor;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBVisibleClick(System::TObject* Sender);
	void __fastcall BCancelClick(System::TObject* Sender);
	void __fastcall CBStyleChange(System::TObject* Sender);
	void __fastcall CBStyleDrawItem(Vcl::Controls::TWinControl* Control, int Index, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State);
	void __fastcall BColorClick(System::TObject* Sender);
	void __fastcall CBEndStyleChange(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall ESpaceChange(System::TObject* Sender);
	void __fastcall CBJoinStyleChange(System::TObject* Sender);
	void __fastcall TBSizeChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall StylesChangeChart(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall CBDefColorClick(System::TObject* Sender);
	
private:
	Vcltee::Tecanvas::TTeePen* BackupPen;
	System::Classes::TNotifyEvent FOnChangedPen;
	bool ModifiedPen;
	Vcltee::Teeedigrad::TTeeGradientEditor* IGradient;
	bool ISelecting;
	void __fastcall ChangedPen();
	void __fastcall EnablePenStyle();
	void __fastcall PrepareDefColor();
	bool __fastcall SelectedSmallDots();
	void __fastcall SelectStyleGallery();
	void __fastcall StyleChartDraw(System::TObject* Sender);
	
public:
	Vcl::Graphics::TPen* ThePen;
	__classmethod TPenDialog* __fastcall InsertForm(Vcl::Graphics::TPen* const APen, Vcl::Controls::TWinControl* const AParent);
	__classmethod void __fastcall LoadSize(Vcl::Forms::TForm* const AForm, const System::UnicodeString APrefix);
	__classmethod void __fastcall SaveSize(Vcl::Forms::TForm* const AForm, const System::UnicodeString APrefix);
	void __fastcall RefreshPen(Vcl::Graphics::TPen* const APen);
	__property System::Classes::TNotifyEvent OnChangedPen = {read=FOnChangedPen, write=FOnChangedPen};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TPenDialog(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TPenDialog(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TPenDialog() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TPenDialog(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TButtonPen : public Vcltee::Tecanvas::TTeeButton
{
	typedef Vcltee::Tecanvas::TTeeButton inherited;
	
private:
	TPenDialog* FEditor;
	System::Classes::TNotifyEvent FOldDestroy;
	void __fastcall EditorDestroy(System::TObject* Sender);
	Vcltee::Tecanvas::TTeePen* __fastcall GetPen();
	TPenDialog* __fastcall GetEditor();
	
protected:
	virtual void __fastcall DrawSymbol(Vcltee::Tecanvas::TTeeCanvas* const ACanvas);
	
public:
	bool HideColor;
	DYNAMIC void __fastcall Click();
	void __fastcall LinkPen(Vcltee::Tecanvas::TTeePen* const APen);
	__property TPenDialog* Editor = {read=GetEditor};
	__property Vcltee::Tecanvas::TTeePen* Pen = {read=GetPen, write=LinkPen};
public:
	/* TTeeButton.Create */ inline __fastcall virtual TButtonPen(System::Classes::TComponent* AOwner) : Vcltee::Tecanvas::TTeeButton(AOwner) { }
	
public:
	/* TCustomButton.Destroy */ inline __fastcall virtual ~TButtonPen() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TButtonPen(HWND ParentWindow) : Vcltee::Tecanvas::TTeeButton(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const Vcl::Forms::TFormBorderStyle TeeFormBorderStyle = (Vcl::Forms::TFormBorderStyle)(0);
extern DELPHI_PACKAGE void __fastcall PositionToCenter(Vcl::Forms::TForm* const Form);
extern DELPHI_PACKAGE Vcl::Forms::TForm* __fastcall TeeCreateForm(const Vcl::Forms::TFormClass FormClass, System::Classes::TComponent* const AOwner);
extern DELPHI_PACKAGE bool __fastcall EditChartPen(System::Classes::TComponent* const AOwner, Vcltee::Tecanvas::TTeePen* const APen, bool HideColor = false);
extern DELPHI_PACKAGE void __fastcall ShowControls(bool Show, Vcl::Controls::TControl* const *AControls, const int AControls_High);
extern DELPHI_PACKAGE bool __fastcall TeeYesNo(const System::UnicodeString Message, Vcl::Controls::TControl* Owner = (Vcl::Controls::TControl*)(0x0));
extern DELPHI_PACKAGE bool __fastcall TeeYesNoDelete(const System::UnicodeString Message, Vcl::Controls::TControl* Owner = (Vcl::Controls::TControl*)(0x0));
extern DELPHI_PACKAGE bool __fastcall TeeSelectFolder(const System::UnicodeString Caption, const System::UnicodeString Root, System::UnicodeString &Folder);
extern DELPHI_PACKAGE void __fastcall AddFormTo(Vcl::Forms::TForm* const AForm, Vcl::Controls::TWinControl* const AParent)/* overload */;
extern DELPHI_PACKAGE void __fastcall AddFormTo(Vcl::Forms::TForm* const AForm, Vcl::Controls::TWinControl* const AParent, NativeInt ATag)/* overload */;
extern DELPHI_PACKAGE void __fastcall AddFormTo(Vcl::Forms::TForm* const AForm, Vcl::Controls::TWinControl* const AParent, System::TObject* const ATag)/* overload */;
extern DELPHI_PACKAGE void __fastcall TeeLoadArrowBitmaps(Vcl::Graphics::TBitmap* const AUp, Vcl::Graphics::TBitmap* const ADown);
extern DELPHI_PACKAGE void __fastcall MoveList(Vcl::Stdctrls::TCustomListBox* const Source, Vcl::Stdctrls::TCustomListBox* const Dest);
extern DELPHI_PACKAGE void __fastcall MoveListAll(System::Classes::TStrings* const Source, System::Classes::TStrings* const Dest);
extern DELPHI_PACKAGE void __fastcall TeeScaleForm(Vcl::Forms::TForm* const AForm);
extern DELPHI_PACKAGE void __fastcall TeeSavePictureDialog(System::Classes::TComponent* const AOwner, Vcl::Graphics::TGraphic* const AGraphic);
extern DELPHI_PACKAGE System::UnicodeString __fastcall FileSizeToStr(unsigned Size);
}	/* namespace Teependlg */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEPENDLG)
using namespace Vcltee::Teependlg;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeependlgHPP
