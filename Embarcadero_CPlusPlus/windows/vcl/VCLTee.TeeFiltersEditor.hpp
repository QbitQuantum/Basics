// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeFiltersEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeefilterseditorHPP
#define Vcltee_TeefilterseditorHPP

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
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.CheckLst.hpp>
#include <VCLTee.TeeGDIPlus.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeDraw3D.hpp>
#include <VCLTee.TeeFilters.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.Chart.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teefilterseditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormItem;
class DELPHICLASS TFormItems;
class DELPHICLASS TFormCreator;
class DELPHICLASS TFiltersEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormItem : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::UnicodeString PropName;
	System::Classes::TNotifyEvent OnChange;
public:
	/* TObject.Create */ inline __fastcall TFormItem() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFormItem() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFormItems : public System::Classes::TList
{
	typedef System::Classes::TList inherited;
	
public:
	TFormItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	HIDESBASE TFormItem* __fastcall Get(int Index);
	
public:
	virtual void __fastcall Clear();
	__property TFormItem* Items[int Index] = {read=Get/*, default*/};
public:
	/* TList.Destroy */ inline __fastcall virtual ~TFormItems() { }
	
public:
	/* TObject.Create */ inline __fastcall TFormItems() : System::Classes::TList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TFormCreator : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Vcl::Controls::TWinControl* FParent;
	System::Classes::TNotifyEvent FOnChange;
	bool IChanging;
	int IPosY;
	TFormItem* __fastcall AddItem(const System::UnicodeString PropName, System::Classes::TNotifyEvent AOnChange = 0x0);
	void __fastcall ChangeProp(System::TObject* Sender, const System::Variant &Value);
	void __fastcall CheckBoxChanged(System::TObject* Sender);
	void __fastcall ColorChanged(System::TObject* Sender);
	void __fastcall ComboChanged(System::TObject* Sender);
	void __fastcall EditChanged(System::TObject* Sender);
	void __fastcall ScrollChanged(System::TObject* Sender);
	
public:
	System::TObject* Instance;
	TFormItems* Items;
	__fastcall virtual TFormCreator(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFormCreator();
	Vcl::Stdctrls::TCheckBox* __fastcall AddCheckBox(const System::UnicodeString PropName, const System::UnicodeString ACaption, System::Classes::TNotifyEvent OnChange = 0x0);
	Vcl::Stdctrls::TButton* __fastcall AddColor(const System::UnicodeString PropName, const System::UnicodeString ACaption);
	Vcl::Stdctrls::TComboBox* __fastcall AddCombo(const System::UnicodeString PropName);
	Vcl::Stdctrls::TEdit* __fastcall AddInteger(const System::UnicodeString PropName, const System::UnicodeString ACaption, int AMin, int AMax);
	Vcl::Stdctrls::TScrollBar* __fastcall AddScroll(const System::UnicodeString PropName, int AMin, int AMax);
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
private:
	void *__IFormCreator;	// Vcltee::Tecanvas::IFormCreator 
	
public:
	operator Vcltee::Tecanvas::IFormCreator*(void) { return (Vcltee::Tecanvas::IFormCreator*)&__IFormCreator; }
	
};


class PASCALIMPLEMENTATION TFiltersEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Buttons::TSpeedButton* BAdd;
	Vcl::Buttons::TSpeedButton* BDelete;
	Vcl::Buttons::TSpeedButton* BMoveUp;
	Vcl::Buttons::TSpeedButton* BMoveDown;
	Vcl::Checklst::TCheckListBox* Filters;
	Vcltee::Teedraw3d::TDraw3D* Image;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Extctrls::TPanel* Panel4;
	Vcl::Stdctrls::TButton* BOK;
	Vcl::Comctrls::TPageControl* PageProps;
	Vcl::Comctrls::TTabSheet* Properties;
	Vcl::Comctrls::TTabSheet* TabRegion;
	Vcl::Extctrls::TSplitter* Splitter2;
	Vcl::Extctrls::TTimer* Timer1;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TEdit* ELeft;
	Vcl::Comctrls::TUpDown* UDLeft;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* ETop;
	Vcl::Comctrls::TUpDown* UDTop;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TEdit* EWidth;
	Vcl::Comctrls::TUpDown* UDWidth;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TEdit* EHeight;
	Vcl::Comctrls::TUpDown* UDHeight;
	Vcltee::Tecanvas::TComboFlat* CBPreview;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Comctrls::TTabSheet* TabHistogram;
	Vcltee::Chart::TChart* Chart1;
	Vcltee::Series::TFastLineSeries* Series1;
	Vcltee::Series::TFastLineSeries* Series2;
	Vcltee::Series::TFastLineSeries* Series3;
	Vcltee::Series::TFastLineSeries* Series4;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FiltersClick(System::TObject* Sender);
	void __fastcall BAddClick(System::TObject* Sender);
	void __fastcall FiltersClickCheck(System::TObject* Sender);
	void __fastcall BDeleteClick(System::TObject* Sender);
	void __fastcall BMoveUpClick(System::TObject* Sender);
	void __fastcall BMoveDownClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall ImageResize(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall CBScaledClick(System::TObject* Sender);
	void __fastcall Timer1Timer(System::TObject* Sender);
	void __fastcall ELeftChange(System::TObject* Sender);
	void __fastcall ETopChange(System::TObject* Sender);
	void __fastcall EWidthChange(System::TObject* Sender);
	void __fastcall EHeightChange(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, System::Uitypes::TCloseAction &Action);
	void __fastcall CBPreviewChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	
private:
	Vcltee::Tecanvas::TFilterItems* Backup;
	TFormCreator* Creator;
	Vcl::Graphics::TBitmap* IBitmap;
	bool IChanging;
	bool HistogramReady;
	void __fastcall ClearProperties();
	void __fastcall ChangedProperties(System::TObject* Sender);
	Vcltee::Tecanvas::TTeeFilter* __fastcall CurrentFilter();
	void __fastcall EnableButtons();
	void __fastcall Preview();
	void __fastcall RepaintPreview();
	void __fastcall Swap(int A, int B);
	
public:
	System::Classes::TNotifyEvent Changed;
	Vcltee::Tecanvas::TFilterItems* FilterItems;
	Vcl::Graphics::TGraphic* Picture;
	void __fastcall SetPicture(Vcl::Graphics::TGraphic* const APicture);
	__classmethod TFiltersEditor* __fastcall InsertForm(Vcltee::Tecanvas::TTeePicture* const APicture, Vcl::Controls::TWinControl* const AParent);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFiltersEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFiltersEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFiltersEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFiltersEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall ShowFiltersEditor(System::Classes::TComponent* const AOwner, Vcl::Graphics::TGraphic* const APicture, Vcltee::Tecanvas::TFilterItems* const AFilters)/* overload */;
extern DELPHI_PACKAGE bool __fastcall ShowFiltersEditor(System::Classes::TComponent* const AOwner, Vcltee::Tecanvas::TTeePicture* const APicture)/* overload */;
}	/* namespace Teefilterseditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEFILTERSEDITOR)
using namespace Vcltee::Teefilterseditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeefilterseditorHPP
