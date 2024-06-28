// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEdiGene.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeedigeneHPP
#define Vcltee_TeeedigeneHPP

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
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeNavigator.hpp>
#include <VCLTee.TeeEdiFont.hpp>
#include <VCLTee.TeeMouseCursor.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeePrevi.hpp>
#include <VCLTee.TeeLisB.hpp>
#include <VCLTee.TeeDraw3D.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeedigene
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormTeeGeneral;
class DELPHICLASS TChartPageNavigator;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormTeeGeneral : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabZoom;
	Vcl::Comctrls::TTabSheet* TabScroll;
	Vcl::Extctrls::TRadioGroup* RGPanning;
	Vcl::Stdctrls::TLabel* Label4;
	Vcltee::Tecanvas::TComboFlat* CBScrollMouse;
	Vcl::Comctrls::TTabSheet* TabCursor;
	Vcl::Comctrls::TTabSheet* TabFont;
	Vcl::Stdctrls::TListBox* LBFonts;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Extctrls::TPanel* PanelFont;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TCheckBox* CBAllFonts;
	Vcl::Stdctrls::TCheckBox* CBInsideBounds;
	Vcl::Stdctrls::TLabel* LTextSize;
	Vcl::Stdctrls::TEdit* ETextSize;
	Vcl::Comctrls::TUpDown* UDTextSize;
	Vcltee::Tecanvas::TComboFlat* CBZoomText;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Comctrls::TTabSheet* TabPalette;
	Vcl::Comctrls::TTabSheet* TabMouse;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TLabel* Label6;
	Vcltee::Tecanvas::TComboFlat* CBLeftButton;
	Vcl::Stdctrls::TLabel* Label7;
	Vcltee::Tecanvas::TComboFlat* CBMidButton;
	Vcl::Stdctrls::TLabel* Label8;
	Vcltee::Tecanvas::TComboFlat* CBRightButton;
	Vcl::Stdctrls::TGroupBox* GroupBox2;
	Vcl::Stdctrls::TGroupBox* GroupColors;
	Vcl::Stdctrls::TLabel* Label10;
	Vcl::Stdctrls::TScrollBar* SBLum;
	Vcl::Stdctrls::TLabel* Label11;
	Vcl::Stdctrls::TScrollBar* SBHue;
	Vcl::Stdctrls::TLabel* Label12;
	Vcl::Stdctrls::TScrollBar* SBSat;
	Vcl::Dialogs::TOpenDialog* OpenDialog1;
	Vcl::Dialogs::TSaveDialog* SaveDialog1;
	Vcl::Extctrls::TPanel* PanelColors;
	Vcl::Stdctrls::TLabel* LPalette;
	Vcl::Buttons::TSpeedButton* SBAddColor;
	Vcl::Buttons::TSpeedButton* SBDeleteColor;
	Vcl::Buttons::TSpeedButton* SBEditColor;
	Vcl::Stdctrls::TLabel* LColor;
	Vcl::Stdctrls::TListBox* LBPalette;
	Vcl::Stdctrls::TListBox* LBColors;
	Vcl::Stdctrls::TCheckBox* CBCustom;
	Vcl::Buttons::TSpeedButton* SBLoad;
	Vcl::Buttons::TSpeedButton* SBSave;
	Vcl::Comctrls::TPageControl* PageControl2;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Comctrls::TTabSheet* TabZoomBorder;
	Vcl::Stdctrls::TLabel* LSteps;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TCheckBox* CBAllowZoom;
	Vcl::Stdctrls::TCheckBox* CBAnimatedZoom;
	Vcl::Stdctrls::TEdit* SEAniZoomSteps;
	Vcl::Comctrls::TUpDown* UDAniZoomSteps;
	Vcl::Stdctrls::TEdit* EMinPix;
	Vcl::Comctrls::TUpDown* UDMinPix;
	Vcltee::Tecanvas::TComboFlat* CBDir;
	Vcltee::Tecanvas::TComboFlat* CBZoomMouse;
	Vcl::Stdctrls::TCheckBox* CBUpLeft;
	Vcl::Stdctrls::TCheckBox* CBHistory;
	Vcl::Stdctrls::TCheckBox* CBZoomAspect;
	Vcl::Stdctrls::TRadioButton* RGWheelScroll;
	Vcl::Stdctrls::TRadioButton* RGWheelData;
	Vcl::Stdctrls::TRadioButton* RGWheelChart;
	Vcl::Stdctrls::TCheckBox* CBInvWheel;
	Vcl::Stdctrls::TRadioButton* RBWheelNone;
	Vcl::Comctrls::TTabSheet* TabZoomPattern;
	Vcl::Stdctrls::TCheckBox* CBFullRepaint;
	Vcl::Buttons::TSpeedButton* BMoveUP;
	Vcl::Buttons::TSpeedButton* BMoveDown;
	Vcl::Comctrls::TTabSheet* TabHover;
	Vcl::Stdctrls::TCheckBox* CBHover;
	void __fastcall CBAllowZoomClick(System::TObject* Sender);
	void __fastcall CBAnimatedZoomClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall RGPanningClick(System::TObject* Sender);
	void __fastcall SEAniZoomStepsChange(System::TObject* Sender);
	void __fastcall EMinPixChange(System::TObject* Sender);
	void __fastcall CBDirChange(System::TObject* Sender);
	void __fastcall CBZoomMouseChange(System::TObject* Sender);
	void __fastcall CBScrollMouseChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBUpLeftClick(System::TObject* Sender);
	void __fastcall LBFontsClick(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall FormDeactivate(System::TObject* Sender);
	void __fastcall LBFontsKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBHistoryClick(System::TObject* Sender);
	void __fastcall CBAllFontsClick(System::TObject* Sender);
	void __fastcall CBZoomAspectClick(System::TObject* Sender);
	void __fastcall CBInsideBoundsClick(System::TObject* Sender);
	void __fastcall CBZoomTextChange(System::TObject* Sender);
	void __fastcall ETextSizeChange(System::TObject* Sender);
	void __fastcall CBPaletteChange(System::TObject* Sender);
	void __fastcall CBLeftButtonChange(System::TObject* Sender);
	void __fastcall CBRightButtonChange(System::TObject* Sender);
	void __fastcall CBMidButtonChange(System::TObject* Sender);
	void __fastcall LBColorsDrawItem(Vcl::Controls::TWinControl* Control, int Index, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State);
	void __fastcall SBDeleteColorClick(System::TObject* Sender);
	void __fastcall SBAddColorClick(System::TObject* Sender);
	void __fastcall LBColorsClick(System::TObject* Sender);
	void __fastcall LBColorsDblClick(System::TObject* Sender);
	void __fastcall CBCustomClick(System::TObject* Sender);
	void __fastcall SBEditColorClick(System::TObject* Sender);
	void __fastcall LBColorsDragOver(System::TObject* Sender, System::TObject* Source, int X, int Y, System::Uitypes::TDragState State, bool &Accept);
	void __fastcall LBColorsDragDrop(System::TObject* Sender, System::TObject* Source, int X, int Y);
	void __fastcall SBLumChange(System::TObject* Sender);
	void __fastcall SBSaveClick(System::TObject* Sender);
	void __fastcall SBLoadClick(System::TObject* Sender);
	void __fastcall PanelColorsResize(System::TObject* Sender);
	void __fastcall PageControl2Change(System::TObject* Sender);
	void __fastcall CBInvWheelClick(System::TObject* Sender);
	void __fastcall RGWheelScrollClick(System::TObject* Sender);
	void __fastcall CBFullRepaintClick(System::TObject* Sender);
	void __fastcall BMoveUPClick(System::TObject* Sender);
	void __fastcall BMoveDownClick(System::TObject* Sender);
	void __fastcall CBHoverClick(System::TObject* Sender);
	
private:
	bool Changing;
	Vcltee::Tecanvas::TTeeFont* IBackup;
	Vcltee::Teemousecursor::TMouseCursorEdit* ICursorEdit;
	Vcltee::Tecanvas::TTeeFont* IFont;
	Vcltee::Teeedifont::TTeeFontEditor* IFontEditor;
	System::Classes::TNotifyEvent OldChange;
	Vcltee::Teeprocs::TColorArray ISaved;
	void __fastcall AlterPalette();
	void __fastcall ChangedCustomPalette();
	void __fastcall ChangedFont(System::TObject* Sender);
	void __fastcall CheckCustomPalette();
	void __fastcall CheckMouseButton(Vcl::Stdctrls::TComboBox* const Combo1, Vcl::Stdctrls::TComboBox* const Combo2, const System::Uitypes::TMouseButton Button1, const System::Uitypes::TMouseButton Button2);
	bool __fastcall CurrentColor(/* out */ System::Uitypes::TColor &AColor);
	void __fastcall CursorChange(System::TObject* Sender);
	void __fastcall DoSelectAllFonts();
	void __fastcall EnablePaletteButtons();
	void __fastcall EnableZoomControls();
	void __fastcall FillFonts();
	void __fastcall SelectTitleFont();
	void __fastcall FillPalette();
	Vcltee::Teeprocs::TColorArray __fastcall FindPalette();
	void __fastcall FlagCustomPalette();
	void __fastcall RefreshLabelColor();
	void __fastcall ResetIFont();
	void __fastcall SavePalette();
	Vcltee::Tecanvas::TTeeFont* __fastcall SelectedFont(int Index);
	void __fastcall SwapColor(const int AFrom, const int Delta);
	
protected:
	Vcltee::Teemousecursor::TMouseCursorEdit* __fastcall CheckCursorEdit();
	
public:
	Vcltee::Chart::TCustomChart* TheChart;
	__classmethod void __fastcall GetChartObjects(Vcltee::Chart::TCustomChart* const AChart, System::Classes::TStrings* const AList, bool WithFonts = false);
	__fastcall TFormTeeGeneral(System::Classes::TComponent* const Owner, Vcltee::Chart::TCustomChart* const AChart);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormTeeGeneral(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormTeeGeneral(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormTeeGeneral() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormTeeGeneral(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TChartPageNavigator : public Vcltee::Teenavigator::TCustomTeeNavigator
{
	typedef Vcltee::Teenavigator::TCustomTeeNavigator inherited;
	
private:
	Vcltee::Chart::TCustomChart* __fastcall GetChart();
	void __fastcall SetChart(Vcltee::Chart::TCustomChart* const Value);
	
protected:
	DYNAMIC void __fastcall BtnClick(Vcltee::Teenavigator::TTeeNavigateBtn Index);
	virtual void __fastcall DoTeeEvent(Vcltee::Teeprocs::TTeeEvent* Event);
	virtual void __fastcall SetPanel(Vcltee::Teeprocs::TCustomTeePanel* const Value);
	
public:
	virtual void __fastcall EnableButtons();
	virtual int __fastcall PageCount();
	virtual void __fastcall Print();
	
__published:
	__property Vcltee::Chart::TCustomChart* Chart = {read=GetChart, write=SetChart};
	__property OnButtonClicked;
public:
	/* TCustomTeeNavigator.Create */ inline __fastcall virtual TChartPageNavigator(System::Classes::TComponent* AOwner) : Vcltee::Teenavigator::TCustomTeeNavigator(AOwner) { }
	/* TCustomTeeNavigator.Destroy */ inline __fastcall virtual ~TChartPageNavigator() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TChartPageNavigator(HWND ParentWindow) : Vcltee::Teenavigator::TCustomTeeNavigator(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall (*TeeEditToolProc)(System::Classes::TComponent* AOwner, Vcltee::Teengine::TTeeCustomTool* const ATool);
extern DELPHI_PACKAGE void __fastcall ChartPreview(System::Classes::TComponent* const AOwner, Vcltee::Teeprocs::TCustomTeePanel* const TeePanel);
}	/* namespace Teeedigene */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDIGENE)
using namespace Vcltee::Teeedigene;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeedigeneHPP
