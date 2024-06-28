// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEdiGrad.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeedigradHPP
#define Vcltee_TeeedigradHPP

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
#include <Vcl.Buttons.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <VCLTee.TeeGDIPlus.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>
#include <VCLTee.TeeDraw3D.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeedigrad
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPreviewGradient;
class DELPHICLASS TButtonGradient;
class DELPHICLASS TTeeGradientEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPreviewGradient : public Vcltee::Teeprocs::TCustomTeePanelExtended
{
	typedef Vcltee::Teeprocs::TCustomTeePanelExtended inherited;
	
protected:
	virtual void __fastcall InternalDraw(const System::Types::TRect &UserRectangle);
public:
	/* TCustomTeePanelExtended.Create */ inline __fastcall virtual TPreviewGradient(System::Classes::TComponent* AOwner) : Vcltee::Teeprocs::TCustomTeePanelExtended(AOwner) { }
	/* TCustomTeePanelExtended.Destroy */ inline __fastcall virtual ~TPreviewGradient() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TPreviewGradient(HWND ParentWindow) : Vcltee::Teeprocs::TCustomTeePanelExtended(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TButtonGradient : public Vcltee::Tecanvas::TTeeButton
{
	typedef Vcltee::Tecanvas::TTeeButton inherited;
	
private:
	TTeeGradientEditor* FEditor;
	System::Classes::TNotifyEvent FOldDestroy;
	void __fastcall EditorDestroy(System::TObject* Sender);
	TTeeGradientEditor* __fastcall GetEditor();
	Vcltee::Tecanvas::TCustomTeeGradient* __fastcall GetGradient();
	
protected:
	virtual void __fastcall DrawSymbol(Vcltee::Tecanvas::TTeeCanvas* const ACanvas);
	
public:
	bool OnlyStart;
	DYNAMIC void __fastcall Click();
	void __fastcall LinkGradient(Vcltee::Tecanvas::TCustomTeeGradient* const Value);
	__property TTeeGradientEditor* Editor = {read=GetEditor};
	__property Vcltee::Tecanvas::TCustomTeeGradient* Gradient = {read=GetGradient, write=LinkGradient};
public:
	/* TTeeButton.Create */ inline __fastcall virtual TButtonGradient(System::Classes::TComponent* AOwner) : Vcltee::Tecanvas::TTeeButton(AOwner) { }
	
public:
	/* TCustomButton.Destroy */ inline __fastcall virtual ~TButtonGradient() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TButtonGradient(HWND ParentWindow) : Vcltee::Tecanvas::TTeeButton(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TTeeGradientEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabColors;
	Vcl::Comctrls::TTabSheet* TabSheet2;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TLabel* LabelBalance;
	Vcl::Stdctrls::TGroupBox* GroupBox2;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* LRadialX;
	Vcl::Stdctrls::TLabel* LRadialY;
	Vcl::Comctrls::TTrackBar* TrackBar1;
	Vcl::Comctrls::TTrackBar* TrackBar2;
	Vcl::Extctrls::TPanel* PanelButtons;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TCheckBox* CBVisible;
	Vcl::Stdctrls::TLabel* Label1;
	Vcltee::Tecanvas::TComboFlat* CBDirection;
	Vcl::Comctrls::TTabSheet* TabGallery;
	Vcl::Comctrls::TTabSheet* TabDirections;
	Vcltee::Teegallerypanel::TChartGalleryPanel* Directions;
	Vcl::Comctrls::TTabSheet* TabSheet5;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TScrollBar* SBTransp;
	TButtonGradient* BSubEdit;
	Vcl::Stdctrls::TCheckBox* CBSubVisible;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Stdctrls::TEdit* EAngle;
	Vcl::Comctrls::TUpDown* UDAngle;
	Vcl::Comctrls::TTrackBar* TBAngle;
	Vcltee::Teegallerypanel::TChartGalleryPanel* Gallery;
	Vcltee::Teedraw3d::TDraw3D* Draw3D1;
	Vcltee::Teedraw3d::TDraw3D* Colors;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TButton* BSwap;
	Vcltee::Tecanvas::TButtonColor* BStart;
	Vcltee::Tecanvas::TButtonColor* BEnd;
	Vcltee::Tecanvas::TButtonColor* BMid;
	Vcl::Stdctrls::TCheckBox* CBMid;
	Vcl::Stdctrls::TCheckBox* CBSameAsEnd;
	Vcltee::Tecanvas::TButtonColor* BColor;
	Vcl::Comctrls::TTrackBar* TrackTransp;
	Vcl::Buttons::TSpeedButton* BDeleteColor;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Stdctrls::TButton* BOk;
	Vcl::Stdctrls::TButton* BCancel;
	Vcl::Stdctrls::TLabel* LTransp;
	Vcl::Stdctrls::TLabel* LColorTransp;
	Vcl::Comctrls::TTrackBar* TBBalance;
	void __fastcall CBVisibleClick(System::TObject* Sender);
	void __fastcall CBDirectionChange(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall BCancelClick(System::TObject* Sender);
	void __fastcall BSwapClick(System::TObject* Sender);
	void __fastcall CBMidClick(System::TObject* Sender);
	void __fastcall BMidClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall TrackBar1Change(System::TObject* Sender);
	void __fastcall TrackBar2Change(System::TObject* Sender);
	void __fastcall BStartClick(System::TObject* Sender);
	void __fastcall BEndClick(System::TObject* Sender);
	void __fastcall DirectionsChangeChart(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall SBTranspChange(System::TObject* Sender);
	void __fastcall CBSubVisibleClick(System::TObject* Sender);
	void __fastcall EAngleChange(System::TObject* Sender);
	void __fastcall TBAngleChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall GalleryChangeChart(System::TObject* Sender);
	void __fastcall CBSameAsEndClick(System::TObject* Sender);
	void __fastcall Draw3D1Resize(System::TObject* Sender);
	void __fastcall Draw3D1AfterDraw(System::TObject* Sender);
	void __fastcall Draw3D1MouseMove(System::TObject* Sender, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall Draw3D1MouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall BColorClick(System::TObject* Sender);
	void __fastcall ColorsMouseUp(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall TrackTranspChange(System::TObject* Sender);
	void __fastcall Draw3D1MouseUp(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall BDeleteColorClick(System::TObject* Sender);
	void __fastcall TBBalanceChange(System::TObject* Sender);
	
private:
	Vcltee::Tecanvas::TCustomTeeGradient* Backup;
	int IDragging;
	bool IModified;
	bool IOnlyStart;
	bool SettingProps;
	void __fastcall ApplyChart(Vcltee::Teegallerypanel::TGalleryChart* const Chart);
	void __fastcall CheckButtonColor(int Index);
	void __fastcall CheckDirection();
	void __fastcall CheckVisible();
	System::Types::TRect __fastcall ColorHandler(int Index);
	bool __fastcall IsRectGradient();
	int __fastcall PointInColor(int X, int Y);
	void __fastcall SelectDirection();
	void __fastcall SetDirectionGradients();
	void __fastcall SetLabelBalance();
	void __fastcall SetModified();
	
protected:
	System::Classes::TNotifyEvent FOnChangedGradient;
	virtual void __fastcall RefreshControls();
	virtual void __fastcall SetPreview();
	
public:
	Vcltee::Tecanvas::TCustomTeeGradient* TheGradient;
	__fastcall TTeeGradientEditor(System::Classes::TComponent* const AOwner, Vcltee::Tecanvas::TCustomTeeGradient* const AGradient, bool OnlyStart);
	void __fastcall CheckFull(bool IsOnlyStart);
	__classmethod void __fastcall DefaultGradient(Vcltee::Tecanvas::TCustomTeeGradient* const Gradient, bool IsRectGradient, int Index);
	virtual void __fastcall RefreshGradient(Vcltee::Tecanvas::TCustomTeeGradient* const AGradient);
	__classmethod TTeeGradientEditor* __fastcall InsertForm(Vcltee::Tecanvas::TCustomTeeGradient* const AGradient, Vcl::Controls::TWinControl* const AParent);
	__property System::Classes::TNotifyEvent OnChangedGradient = {read=FOnChangedGradient, write=FOnChangedGradient};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTeeGradientEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTeeGradientEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTeeGradientEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTeeGradientEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 TeeMaxSampleGradient = System::Int8(0x11);
extern DELPHI_PACKAGE bool __fastcall EditTeeGradient(System::Classes::TComponent* const AOwner, Vcltee::Tecanvas::TCustomTeeGradient* const AGradient)/* overload */;
extern DELPHI_PACKAGE bool __fastcall EditTeeGradient(System::Classes::TComponent* const AOwner, Vcltee::Tecanvas::TCustomTeeGradient* const AGradient, bool OnlyStart, bool HideVisible = false)/* overload */;
}	/* namespace Teeedigrad */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDIGRAD)
using namespace Vcltee::Teeedigrad;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeedigradHPP
