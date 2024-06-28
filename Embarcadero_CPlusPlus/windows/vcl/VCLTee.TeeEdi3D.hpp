// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEdi3D.pas' rev: 34.00 (Windows)

#ifndef Vcltee_Teeedi3dHPP
#define Vcltee_Teeedi3dHPP

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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeedi3d
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormTee3D;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormTee3D : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* Tab3D;
	Vcl::Comctrls::TTabSheet* TabViews;
	Vcl::Stdctrls::TLabel* L4;
	Vcl::Stdctrls::TLabel* LRot;
	Vcl::Stdctrls::TLabel* LElev;
	Vcl::Stdctrls::TLabel* LZoom;
	Vcl::Stdctrls::TLabel* LRotation;
	Vcl::Stdctrls::TLabel* LElevation;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* LHOffset;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* LVOffset;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* LPerspec;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TLabel* LTextSize;
	Vcl::Stdctrls::TCheckBox* CBView3d;
	Vcl::Stdctrls::TCheckBox* CBOrthogonal;
	Vcl::Comctrls::TTrackBar* SBZoom;
	Vcl::Comctrls::TTrackBar* SBRotation;
	Vcl::Comctrls::TTrackBar* SBElevation;
	Vcl::Comctrls::TTrackBar* SBHOffset;
	Vcl::Comctrls::TTrackBar* SBVOffset;
	Vcl::Comctrls::TTrackBar* SBPerspec;
	Vcl::Stdctrls::TEdit* EOrthoAngle;
	Vcl::Comctrls::TUpDown* UDOrthoAngle;
	Vcl::Stdctrls::TCheckBox* CBClipPoints;
	Vcl::Stdctrls::TEdit* ETextSize;
	Vcl::Comctrls::TUpDown* UDTextSize;
	Vcltee::Teegallerypanel::TChartGalleryPanel* Views;
	Vcl::Comctrls::TTabSheet* TabRender;
	Vcl::Stdctrls::TListBox* LBRender;
	Vcl::Extctrls::TPanel* PanelRender;
	Vcl::Extctrls::TPanel* PanelGDI;
	Vcl::Stdctrls::TCheckBox* CBBuffered;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcltee::Tecanvas::TComboFlat* CBZoomText;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TLabel* Label6;
	Vcltee::Tecanvas::TComboFlat* CBTextQuality;
	Vcl::Comctrls::TTrackBar* TB3D;
	void __fastcall CBOrthogonalClick(System::TObject* Sender);
	void __fastcall SBZoomChange(System::TObject* Sender);
	void __fastcall SBRotationChange(System::TObject* Sender);
	void __fastcall SBElevationChange(System::TObject* Sender);
	void __fastcall CBView3dClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall SBHOffsetChange(System::TObject* Sender);
	void __fastcall SBVOffsetChange(System::TObject* Sender);
	void __fastcall SBPerspecChange(System::TObject* Sender);
	void __fastcall EOrthoAngleChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBClipPointsClick(System::TObject* Sender);
	void __fastcall ETextSizeChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall LBRenderClick(System::TObject* Sender);
	void __fastcall CBBufferedClick(System::TObject* Sender);
	void __fastcall CBZoomTextChange(System::TObject* Sender);
	void __fastcall ViewsChangeChart(System::TObject* Sender);
	void __fastcall CBTextQualityChange(System::TObject* Sender);
	void __fastcall TB3DChange(System::TObject* Sender);
	
private:
	bool AllowRotation;
	bool Changing;
	bool CreatingViews;
	void __fastcall AddRenderClasses();
	void __fastcall CreateViewsGallery();
	int __fastcall GetRotation();
	void __fastcall RefreshOptions();
	void __fastcall Select3DPanel(Vcltee::Teeprocs::TCustomTeePanel* APanel);
	void __fastcall SetGallery3DPanel(Vcltee::Teeprocs::TCustomTeePanel* APanel);
	void __fastcall ShowCanvasEditor();
	
public:
	bool ResetTab3D;
	Vcltee::Teeprocs::TCustomTeePanel* ThePanel;
	void __fastcall CheckControls();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormTee3D(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormTee3D(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormTee3D() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormTee3D(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeedi3d */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDI3D)
using namespace Vcltee::Teeedi3d;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_Teeedi3dHPP
