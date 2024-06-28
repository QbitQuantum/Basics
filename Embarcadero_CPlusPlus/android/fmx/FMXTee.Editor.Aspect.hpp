// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Aspect.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_AspectHPP
#define Fmxtee_Editor_AspectHPP

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
#include <System.Generics.Collections.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Controls3D.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.ComboTrackBar.hpp>
#include <FMX.SpinBox.hpp>
#include <FMXTee.Procs.hpp>
#include <FMXTee.Canvas.hpp>
#include <FMXTee.Chart.GalleryPanel.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Aspect
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormTee3D;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormTee3D : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* PageControl1;
	Fmx::Tabcontrol::TTabItem* Tab3D;
	Fmx::Stdctrls::TLabel* L13;
	Fmx::Stdctrls::TLabel* L4;
	Fmx::Stdctrls::TLabel* L35;
	Fmx::Stdctrls::TLabel* L36;
	Fmx::Stdctrls::TLabel* LZoom;
	Fmx::Stdctrls::TLabel* LRotation;
	Fmx::Stdctrls::TLabel* LElevation;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TLabel* LHOffset;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TLabel* LVOffset;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TLabel* LPerspec;
	Fmx::Stdctrls::TLabel* LabelOrtho;
	Fmx::Stdctrls::TLabel* LTextSize;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Stdctrls::TCheckBox* CBView3d;
	Fmx::Stdctrls::TCheckBox* CBOrthogonal;
	Fmx::Stdctrls::TTrackBar* SBZoom;
	Fmx::Spinbox::TSpinBox* UDTextSize;
	Fmx::Listbox::TComboBox* CBZoomText;
	Fmx::Tabcontrol::TTabItem* TabViews;
	Fmx::Tabcontrol::TTabItem* TabRender;
	Fmx::Stdctrls::TSplitter* Splitter1;
	Fmx::Listbox::TListBox* LBRender;
	Fmx::Stdctrls::TPanel* PanelRender;
	Fmx::Stdctrls::TPanel* PanelGDI;
	Fmx::Stdctrls::TCheckBox* CBBuffered;
	Fmx::Stdctrls::TTrackBar* SBRotation;
	Fmx::Stdctrls::TTrackBar* SBElevation;
	Fmx::Stdctrls::TTrackBar* SBHorizOffset;
	Fmx::Stdctrls::TTrackBar* SBVertOffset;
	Fmx::Stdctrls::TTrackBar* SBPerspec;
	Fmx::Stdctrls::TCheckBox* CBClipPoints;
	Fmx::Spinbox::TSpinBox* UDOrthoAngle;
	Fmx::Stdctrls::TCheckBox* CBGPUSurface;
	Fmx::Stdctrls::TCheckBox* CBClipRect;
	Fmx::Listbox::TComboBox* CBQuality;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Listbox::TListBoxItem* ListBoxItem4;
	Fmx::Listbox::TListBoxItem* ListBoxItem5;
	Fmx::Listbox::TListBoxItem* ListBoxItem6;
	Fmx::Stdctrls::TLabel* Label6;
	Fmx::Edit::TEdit* EScale;
	Fmx::Stdctrls::TCheckBox* CBBlending;
	Fmx::Combotrackbar::TComboTrackBar* Percent3D;
	Fmxtee::Chart::Gallerypanel::TChartGalleryPanel* Views;
	Fmx::Stdctrls::TLabel* LDensity;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall SBZoomChange(System::TObject* Sender);
	void __fastcall SBRotationChange(System::TObject* Sender);
	void __fastcall SBElevationChange(System::TObject* Sender);
	void __fastcall SBPerspecChange(System::TObject* Sender);
	void __fastcall CBZoomTextChange(System::TObject* Sender);
	void __fastcall CBView3dChange(System::TObject* Sender);
	void __fastcall CBOrthogonalChange(System::TObject* Sender);
	void __fastcall CBClipPointsChange(System::TObject* Sender);
	void __fastcall UDOrthoAngleChange(System::TObject* Sender);
	void __fastcall SBHorizOffsetChange(System::TObject* Sender);
	void __fastcall SBVertOffsetChange(System::TObject* Sender);
	void __fastcall CBBufferedChange(System::TObject* Sender);
	void __fastcall UDTextSizeChange(System::TObject* Sender);
	void __fastcall LBRenderChange(System::TObject* Sender);
	void __fastcall CBBlendingChange(System::TObject* Sender);
	void __fastcall Percent3DChangeTracking(System::TObject* Sender);
	void __fastcall ViewsChangeChart(System::TObject* Sender);
	
private:
	Fmxtee::Procs::TCustomTeePanel* Panel;
	float IDepth;
	bool CreatingViews;
	void __fastcall AddRenders();
	System::UnicodeString __fastcall AspectFloat(const float Value);
	void __fastcall CreateViewsGallery();
	void __fastcall EnableControls();
	void __fastcall RefreshPanel();
	void __fastcall Select3DPanel(Fmxtee::Procs::TCustomTeePanel* const APanel);
	void __fastcall SetGallery3DPanel(Fmxtee::Procs::TCustomTeePanel* const APanel);
	void __fastcall SetSpinRepeat(Fmx::Spinbox::TSpinBox* const Spin);
	void __fastcall SetView3D(Fmxtee::Canvas::TView3DOptions* const AView);
	void __fastcall UDOrthoAngleApplyStyleLookup(System::TObject* Sender);
	
public:
	__classmethod Fmx::Forms::TForm* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Procs::TCustomTeePanel* const APanel);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormTee3D(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormTee3D(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormTee3D() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Aspect */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_ASPECT)
using namespace Fmxtee::Editor::Aspect;
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
#endif	// Fmxtee_Editor_AspectHPP
