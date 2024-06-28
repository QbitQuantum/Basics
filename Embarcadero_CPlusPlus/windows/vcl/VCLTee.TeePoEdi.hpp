// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeePoEdi.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeepoediHPP
#define Vcltee_TeepoediHPP

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
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeVisualsEditor.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>
#include <VCLTee.TeeEdiGrad.hpp>
#include <VCLTee.TeeShadowEditor.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teepoedi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSeriesPointerEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSeriesPointerEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* PanelBottom;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TButton* Button1;
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabFormat;
	Vcl::Comctrls::TTabSheet* TabSize;
	Vcl::Stdctrls::TCheckBox* CBInflate;
	Vcl::Stdctrls::TCheckBox* CBDrawPoint;
	Vcl::Stdctrls::TCheckBox* CB3dPoint;
	Vcl::Stdctrls::TCheckBox* CBPoDark;
	Vcl::Stdctrls::TCheckBox* CBColorEach;
	Vcl::Stdctrls::TCheckBox* CBIgnoreNulls;
	Vcl::Stdctrls::TLabel* LTransp;
	Vcl::Comctrls::TTrackBar* TBTransp;
	Vcl::Comctrls::TTabSheet* TabVisual;
	Vcl::Comctrls::TTabSheet* TabStyle;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcltee::Tecanvas::TComboFlat* CBStyle;
	Vcltee::Teegallerypanel::TChartGalleryPanel* StyleGallery;
	Vcl::Comctrls::TTabSheet* TabPattern;
	Vcl::Comctrls::TTabSheet* TabBorder;
	Vcl::Comctrls::TTabSheet* TabShadow;
	Vcl::Comctrls::TTabSheet* TabEmboss;
	Vcl::Stdctrls::TLabel* LColorTransp;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* SEPointHorizSize;
	Vcl::Stdctrls::TEdit* SEPointVertSize;
	Vcl::Comctrls::TUpDown* UDPointHorizSize;
	Vcl::Comctrls::TUpDown* UDPointVertSize;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TEdit* ESize;
	Vcl::Comctrls::TUpDown* UDSize;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Stdctrls::TCheckBox* CBDefBrushColor;
	Vcl::Stdctrls::TCheckBox* CBFullGradient;
	Vcltee::Tecanvas::TComboFlat* CBPointUnits;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TEdit* SEPointDepth;
	Vcl::Comctrls::TUpDown* UDPointDepth;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Comctrls::TTabSheet* TabPicture;
	Vcl::Extctrls::TPanel* Panel4;
	Vcl::Stdctrls::TLabel* Label7;
	Vcl::Comctrls::TTrackBar* TBDarkPen;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBDrawPointClick(System::TObject* Sender);
	void __fastcall CB3dPointClick(System::TObject* Sender);
	void __fastcall SEPointHorizSizeChange(System::TObject* Sender);
	void __fastcall CBStyleChange(System::TObject* Sender);
	void __fastcall SEPointVertSizeChange(System::TObject* Sender);
	void __fastcall CBInflateClick(System::TObject* Sender);
	void __fastcall CBPoDarkClick(System::TObject* Sender);
	void __fastcall CBDefBrushColorClick(System::TObject* Sender);
	void __fastcall CBStyleDrawItem(Vcl::Controls::TWinControl* Control, int Index, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State);
	void __fastcall CBColorEachClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall CBIgnoreNullsClick(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall SEPointDepthChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall StyleGalleryChangeChart(System::TObject* Sender);
	void __fastcall StyleGalleryResize(System::TObject* Sender);
	void __fastcall CBFullGradientClick(System::TObject* Sender);
	void __fastcall ESizeChange(System::TObject* Sender);
	void __fastcall CBPointUnitsChange(System::TObject* Sender);
	void __fastcall PageControl1GetImageIndex(System::TObject* Sender, int TabIndex, int &ImageIndex);
	void __fastcall TBDarkPenChange(System::TObject* Sender);
	
private:
	bool IChanging;
	bool ISelecting;
	void __fastcall ChangedVisual(System::TObject* Sender);
	void __fastcall CheckDefColor();
	Vcltee::Series::TCustomSeries* __fastcall CustomSeries();
	void __fastcall Enable3DPoint();
	void __fastcall SetPointerStyle();
	void __fastcall SetPointerVisible(bool Value);
	
protected:
	Vcltee::Teengine::TSeriesPointer* ThePointer;
	
public:
	__classmethod TSeriesPointerEditor* __fastcall InsertForm(Vcltee::Teengine::TSeriesPointer* const APointer, Vcl::Controls::TWinControl* const AParent);
	void __fastcall HideSizeOptions();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TSeriesPointerEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TSeriesPointerEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TSeriesPointerEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TSeriesPointerEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall EditSeriesPointer(System::Classes::TComponent* AOwner, Vcltee::Teengine::TSeriesPointer* APointer);
extern DELPHI_PACKAGE Vcl::Forms::TCustomForm* __fastcall TeeInsertPointerForm(Vcl::Controls::TControl* AParent, Vcltee::Teengine::TSeriesPointer* APointer, const System::UnicodeString Title);
}	/* namespace Teepoedi */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEPOEDI)
using namespace Vcltee::Teepoedi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeepoediHPP
