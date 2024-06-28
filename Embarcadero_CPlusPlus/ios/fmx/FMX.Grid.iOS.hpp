// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Grid.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Grid_IosHPP
#define Fmx_Grid_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.TypInfo.hpp>
#include <System.UITypes.hpp>
#include <System.SysConst.hpp>
#include <System.SysUtils.hpp>
#include <System.Math.hpp>
#include <System.Messaging.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Generics.Collections.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <Macapi.Helpers.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.CoreImage.hpp>
#include <FMX.Presentation.iOS.hpp>
#include <FMX.ScrollBox.iOS.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Types.hpp>
#include <FMX.ActnList.hpp>
#include <FMX.Pickers.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.MediaLibrary.hpp>
#include <FMX.Grid.hpp>

//-- user supplied -----------------------------------------------------------
namespace Fmx
{
namespace Grid
{
namespace Ios
{
  _INIT_UNIT(Fmx_Grid_Ios);
}	/* namespace Ios */
}	/* namespace Grid */
}	/* namespace Fmx */

namespace Fmx
{
namespace Grid
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IiOSLineView;
typedef System::DelphiInterface<IiOSLineView> _di_IiOSLineView;
class DELPHICLASS TiOSLineView;
class DELPHICLASS TiOSCellControl;
__interface DELPHIINTERFACE IiOSCellLabel;
typedef System::DelphiInterface<IiOSCellLabel> _di_IiOSCellLabel;
class DELPHICLASS TiOSCellLabel;
__interface DELPHIINTERFACE IiOSCellHeader;
typedef System::DelphiInterface<IiOSCellHeader> _di_IiOSCellHeader;
class DELPHICLASS TiOSCellHeader;
__interface DELPHIINTERFACE IiOSCellDefaultEditor;
typedef System::DelphiInterface<IiOSCellDefaultEditor> _di_IiOSCellDefaultEditor;
class DELPHICLASS TiOSCellDefaultEditor;
__interface DELPHIINTERFACE IiOSCurrencyLabel;
typedef System::DelphiInterface<IiOSCurrencyLabel> _di_IiOSCurrencyLabel;
class DELPHICLASS TiOSCurrencyLabel;
__interface DELPHIINTERFACE IiOSCurrencyEditor;
typedef System::DelphiInterface<IiOSCurrencyEditor> _di_IiOSCurrencyEditor;
class DELPHICLASS TiOSCurrencyEditor;
__interface DELPHIINTERFACE IiOSNumberEditor;
typedef System::DelphiInterface<IiOSNumberEditor> _di_IiOSNumberEditor;
class DELPHICLASS TiOSNumberEditor;
__interface DELPHIINTERFACE IiOSCellProgressBar;
typedef System::DelphiInterface<IiOSCellProgressBar> _di_IiOSCellProgressBar;
class DELPHICLASS TiOSCellProgressBar;
__interface DELPHIINTERFACE IiOSCellDatePicker;
typedef System::DelphiInterface<IiOSCellDatePicker> _di_IiOSCellDatePicker;
class DELPHICLASS TiOSCellDatePicker;
__interface DELPHIINTERFACE IiOSCellTimePicker;
typedef System::DelphiInterface<IiOSCellTimePicker> _di_IiOSCellTimePicker;
class DELPHICLASS TiOSCellTimePicker;
__interface DELPHIINTERFACE IiOSCellPopupLabel;
typedef System::DelphiInterface<IiOSCellPopupLabel> _di_IiOSCellPopupLabel;
class DELPHICLASS TiOSCellPopupLabel;
__interface DELPHIINTERFACE IiOSCellPopupPicker;
typedef System::DelphiInterface<IiOSCellPopupPicker> _di_IiOSCellPopupPicker;
class DELPHICLASS TiOSCellPopupPicker;
__interface DELPHIINTERFACE IiOSCellGlyph;
typedef System::DelphiInterface<IiOSCellGlyph> _di_IiOSCellGlyph;
class DELPHICLASS TiOSCellGlyph;
__interface DELPHIINTERFACE IiOSCellImage;
typedef System::DelphiInterface<IiOSCellImage> _di_IiOSCellImage;
class DELPHICLASS TiOSCellImage;
__interface DELPHIINTERFACE IiOSCellImageEditor;
typedef System::DelphiInterface<IiOSCellImageEditor> _di_IiOSCellImageEditor;
class DELPHICLASS TiOSCellImageEditor;
__interface DELPHIINTERFACE IiOSCellCheck;
typedef System::DelphiInterface<IiOSCellCheck> _di_IiOSCellCheck;
class DELPHICLASS TiOSCellCheck;
__interface DELPHIINTERFACE IiOSCellCheckEditor;
typedef System::DelphiInterface<IiOSCellCheckEditor> _di_IiOSCellCheckEditor;
class DELPHICLASS TiOSCellCheckEditor;
__interface DELPHIINTERFACE IFMXColumnItem;
typedef System::DelphiInterface<IFMXColumnItem> _di_IFMXColumnItem;
class DELPHICLASS TColumnItem;
class DELPHICLASS TBaseColumnItemList;
class DELPHICLASS TColumnItemList;
class DELPHICLASS TiOSHeaderItem;
__interface DELPHIINTERFACE IiOSHeader;
typedef System::DelphiInterface<IiOSHeader> _di_IiOSHeader;
class DELPHICLASS TiOSHeader;
__interface DELPHIINTERFACE IiOSInplaceEditor;
typedef System::DelphiInterface<IiOSInplaceEditor> _di_IiOSInplaceEditor;
class DELPHICLASS TiOSInplaceEditor;
__interface DELPHIINTERFACE IiOSCell;
typedef System::DelphiInterface<IiOSCell> _di_IiOSCell;
class DELPHICLASS TiOSCell;
__interface DELPHIINTERFACE IiOSRow;
typedef System::DelphiInterface<IiOSRow> _di_IiOSRow;
class DELPHICLASS TiOSRow;
__interface DELPHIINTERFACE IiOSTable;
typedef System::DelphiInterface<IiOSTable> _di_IiOSTable;
class DELPHICLASS TiOSTable;
class DELPHICLASS TiOSGrid;
//-- type declarations -------------------------------------------------------
_DECLARE_METACLASS(System::TMetaClass, TiOSCellControlClass);

enum class DECLSPEC_DENUM TImageKind : unsigned char { Empty, False, True };

__interface  INTERFACE_UUID("{2DD824DE-1D0E-42A3-9F9F-B6A2A840EB0C}") IiOSLineView  : public Iosapi::Uikit::UIView 
{
	
};

class PASCALIMPLEMENTATION TiOSLineView : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
private:
	Iosapi::Uikit::_di_UIView FParentView;
	Iosapi::Uikit::_di_UIView FFromView;
	double FThickness;
	bool FHorizontal;
	bool FLeading;
	bool FInitialized;
	
private:
	Iosapi::Foundation::NSPoint FOffset;
	void __fastcall SetThickness(const double Value);
	void __fastcall SetHorizontal(const bool Value);
	void __fastcall SetLeading(const bool Value);
	bool __fastcall GetVisible();
	void __fastcall SetVisible(const bool Value);
	Iosapi::Uikit::_di_UIView __fastcall GetView();
	void __fastcall SetOffset(const Iosapi::Foundation::NSPoint &Value);
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	
public:
	__fastcall TiOSLineView(TiOSGrid* const AiOSGrid, const Iosapi::Uikit::_di_UIView AParent, const bool AHorizontal, const bool ALeading, const Iosapi::Uikit::_di_UIView AFromView);
	__fastcall virtual ~TiOSLineView();
	void __fastcall Update();
	__property bool Horizontal = {read=FHorizontal, write=SetHorizontal, nodefault};
	__property bool Leading = {read=FLeading, write=SetLeading, nodefault};
	__property double Thickness = {read=FThickness, write=SetThickness};
	__property bool Visible = {read=GetVisible, write=SetVisible, nodefault};
	__property Iosapi::Foundation::NSPoint Offset = {read=FOffset, write=SetOffset};
	__property Iosapi::Uikit::_di_UIView View = {read=GetView};
};


class PASCALIMPLEMENTATION TiOSCellControl : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
	
public:
	enum class DECLSPEC_DENUM TState : unsigned char { Normal, Touching, Cancel, Done };
	
	
private:
	TColumnItem* FOwner;
	
private:
	Fmx::Grid::TColumn* __fastcall GetColumn();
	Iosapi::Uikit::_di_UIView __fastcall GetView();
	System::Types::TRectF __fastcall GetAbsoluteRect();
	
protected:
	virtual System::Rtti::TValue __fastcall GetData() = 0 ;
	virtual void __fastcall SetData(const System::Rtti::TValue &Value) = 0 ;
	virtual void __fastcall DoUpdate() = 0 ;
	virtual Iosapi::Foundation::NSRect __fastcall GetFrame();
	virtual void __fastcall Activate();
	virtual void __fastcall Deactivate();
	
public:
	__fastcall virtual TiOSCellControl(TColumnItem* const AOwner);
	__fastcall virtual ~TiOSCellControl();
	virtual void __fastcall AfterConstruction();
	void __fastcall Update();
	virtual void __fastcall EditorClick();
	bool __fastcall RestoreFocus(const TState State, const System::Sysutils::_di_TProc Proc = System::Sysutils::_di_TProc());
	__property Fmx::Grid::TColumn* Column = {read=GetColumn};
	__property TColumnItem* Owner = {read=FOwner};
	__property System::Rtti::TValue Data = {read=GetData, write=SetData};
	__property Iosapi::Uikit::_di_UIView View = {read=GetView};
	__property System::Types::TRectF AbsoluteRect = {read=GetAbsoluteRect};
};


__interface  INTERFACE_UUID("{28363B27-5F26-4731-8A1F-D190BBA47F5D}") IiOSCellLabel  : public Iosapi::Uikit::UILabel 
{
	
};

class PASCALIMPLEMENTATION TiOSCellLabel : public TiOSCellControl
{
	typedef TiOSCellControl inherited;
	
private:
	System::UnicodeString FText;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual Iosapi::Foundation::NSRect __fastcall GetFrame();
	virtual void __fastcall DoUpdate();
public:
	/* TiOSCellControl.Create */ inline __fastcall virtual TiOSCellLabel(TColumnItem* const AOwner) : TiOSCellControl(AOwner) { }
	/* TiOSCellControl.Destroy */ inline __fastcall virtual ~TiOSCellLabel() { }
	
};


__interface  INTERFACE_UUID("{2836337A-F1D1-4184-8B64-0E500FF65546}") IiOSCellHeader  : public Iosapi::Uikit::UILabel 
{
	
};

class PASCALIMPLEMENTATION TiOSCellHeader : public TiOSCellControl
{
	typedef TiOSCellControl inherited;
	
private:
	System::UnicodeString FText;
	bool FEnabled;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual void __fastcall DoUpdate();
	
public:
	__fastcall virtual TiOSCellHeader(TColumnItem* const AOwner);
public:
	/* TiOSCellControl.Destroy */ inline __fastcall virtual ~TiOSCellHeader() { }
	
};


__interface  INTERFACE_UUID("{28363F82-B7C8-479C-A1A0-9417B944488A}") IiOSCellDefaultEditor  : public Iosapi::Uikit::UITextField 
{
	virtual void __cdecl ControlEventEditingChanged() = 0 ;
};

class PASCALIMPLEMENTATION TiOSCellDefaultEditor : public TiOSCellControl
{
	typedef TiOSCellControl inherited;
	
private:
	bool FTextUpdating;
	System::UnicodeString FStoredText;
	System::UnicodeString FNewText;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	void __fastcall SetText(const System::UnicodeString Text);
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual Iosapi::Foundation::NSRect __fastcall GetFrame();
	virtual void __fastcall DoUpdate();
	virtual void __fastcall DoUpdateChangedText(System::UnicodeString &Text);
	
public:
	__fastcall virtual TiOSCellDefaultEditor(TColumnItem* const AOwner);
	__fastcall virtual ~TiOSCellDefaultEditor();
	void __cdecl ControlEventEditingChanged();
};


__interface  INTERFACE_UUID("{28363387-55A6-4CC7-88C3-1FD3B102F007}") IiOSCurrencyLabel  : public Iosapi::Uikit::UILabel 
{
	
};

class PASCALIMPLEMENTATION TiOSCurrencyLabel : public TiOSCellLabel
{
	typedef TiOSCellLabel inherited;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
public:
	/* TiOSCellControl.Create */ inline __fastcall virtual TiOSCurrencyLabel(TColumnItem* const AOwner) : TiOSCellLabel(AOwner) { }
	/* TiOSCellControl.Destroy */ inline __fastcall virtual ~TiOSCurrencyLabel() { }
	
};


__interface  INTERFACE_UUID("{2836389D-CE65-446E-AD40-382199969377}") IiOSCurrencyEditor  : public Iosapi::Uikit::UITextField 
{
	virtual void __cdecl ControlEventEditingChanged() = 0 ;
};

class PASCALIMPLEMENTATION TiOSCurrencyEditor : public TiOSCellDefaultEditor
{
	typedef TiOSCellDefaultEditor inherited;
	
private:
	double FValue;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual void __fastcall DoUpdate();
public:
	/* TiOSCellDefaultEditor.Create */ inline __fastcall virtual TiOSCurrencyEditor(TColumnItem* const AOwner) : TiOSCellDefaultEditor(AOwner) { }
	/* TiOSCellDefaultEditor.Destroy */ inline __fastcall virtual ~TiOSCurrencyEditor() { }
	
};


__interface  INTERFACE_UUID("{1DB01CB5-CE65-4AB0-ACAD-DB4EDC7B208C}") IiOSNumberEditor  : public Iosapi::Uikit::UITextField 
{
	virtual void __cdecl ControlEventEditingChanged() = 0 ;
};

class PASCALIMPLEMENTATION TiOSNumberEditor : public TiOSCurrencyEditor
{
	typedef TiOSCurrencyEditor inherited;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
public:
	/* TiOSCellDefaultEditor.Create */ inline __fastcall virtual TiOSNumberEditor(TColumnItem* const AOwner) : TiOSCurrencyEditor(AOwner) { }
	/* TiOSCellDefaultEditor.Destroy */ inline __fastcall virtual ~TiOSNumberEditor() { }
	
};


__interface  INTERFACE_UUID("{2DD82E1E-116D-411F-BD54-DC78612B6012}") IiOSCellProgressBar  : public Iosapi::Uikit::UIView 
{
	
};

class PASCALIMPLEMENTATION TiOSCellProgressBar : public TiOSCellControl
{
	typedef TiOSCellControl inherited;
	
private:
	double FValue;
	Iosapi::Uikit::_di_UIView FForeground;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual void __fastcall DoUpdate();
	virtual Iosapi::Foundation::NSRect __fastcall GetFrame();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TiOSCellControl.Create */ inline __fastcall virtual TiOSCellProgressBar(TColumnItem* const AOwner) : TiOSCellControl(AOwner) { }
	/* TiOSCellControl.Destroy */ inline __fastcall virtual ~TiOSCellProgressBar() { }
	
};


__interface  INTERFACE_UUID("{283634C8-F120-4304-92A1-E0CEBC5DFD00}") IiOSCellDatePicker  : public Iosapi::Uikit::UIView 
{
	
};

class PASCALIMPLEMENTATION TiOSCellDatePicker : public TiOSCellControl
{
	typedef TiOSCellControl inherited;
	
private:
	System::TDateTime FDateTime;
	bool FInitialized;
	bool FTextIsPreferred;
	Fmx::Pickers::TCustomDateTimePicker* FPicker;
	void __fastcall DoPopup(System::TObject* Sender);
	void __fastcall DoClosePopup(System::TObject* Sender);
	void __fastcall DoApply(System::TObject* Sender, const System::TDateTime ADateTime);
	void __fastcall SetDateTime(const System::TDateTime DateTime);
	
private:
	Iosapi::Uikit::_di_UITextField FTextField;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual Iosapi::Foundation::NSRect __fastcall GetFrame();
	virtual void __fastcall DoUpdate();
	virtual void __fastcall DoUpdateField(const Iosapi::Uikit::_di_UITextField AField, const System::TDateTime ADateTime);
	virtual Fmx::Pickers::TDatePickerShowMode __fastcall GetPickerShowMode();
	virtual System::TDateTime __fastcall ValueToDateTime(const System::Rtti::TValue &Value);
	virtual void __fastcall Activate();
	virtual void __fastcall Deactivate();
	
public:
	__fastcall virtual TiOSCellDatePicker(TColumnItem* const AOwner);
	__fastcall virtual ~TiOSCellDatePicker();
	virtual void __fastcall BeforeDestruction();
	void __fastcall UpdateField();
	__property System::TDateTime DateTime = {read=FDateTime, write=SetDateTime};
};


__interface  INTERFACE_UUID("{28363A6E-AFA3-4992-94EB-E2B800F97E3C}") IiOSCellTimePicker  : public Iosapi::Uikit::UIView 
{
	
};

class PASCALIMPLEMENTATION TiOSCellTimePicker : public TiOSCellDatePicker
{
	typedef TiOSCellDatePicker inherited;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual void __fastcall DoUpdateField(const Iosapi::Uikit::_di_UITextField AField, const System::TDateTime ADateTime);
	virtual Fmx::Pickers::TDatePickerShowMode __fastcall GetPickerShowMode();
	virtual System::TDateTime __fastcall ValueToDateTime(const System::Rtti::TValue &Value);
public:
	/* TiOSCellDatePicker.Create */ inline __fastcall virtual TiOSCellTimePicker(TColumnItem* const AOwner) : TiOSCellDatePicker(AOwner) { }
	/* TiOSCellDatePicker.Destroy */ inline __fastcall virtual ~TiOSCellTimePicker() { }
	
};


__interface  INTERFACE_UUID("{28363849-100C-4675-8502-EB36DCA7CBF7}") IiOSCellPopupLabel  : public Iosapi::Uikit::UILabel 
{
	
};

class PASCALIMPLEMENTATION TiOSCellPopupLabel : public TiOSCellLabel
{
	typedef TiOSCellLabel inherited;
	
private:
	System::Rtti::TValue FValue;
	bool FUsingIndex;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	__property bool UsingIndex = {read=FUsingIndex, nodefault};
public:
	/* TiOSCellControl.Create */ inline __fastcall virtual TiOSCellPopupLabel(TColumnItem* const AOwner) : TiOSCellLabel(AOwner) { }
	/* TiOSCellControl.Destroy */ inline __fastcall virtual ~TiOSCellPopupLabel() { }
	
};


__interface  INTERFACE_UUID("{283637AB-6EA6-4515-8C77-98729DBF649B}") IiOSCellPopupPicker  : public Iosapi::Uikit::UILabel 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
};

class PASCALIMPLEMENTATION TiOSCellPopupPicker : public TiOSCellPopupLabel
{
	typedef TiOSCellPopupLabel inherited;
	
private:
	Fmx::Pickers::TCustomListPicker* FPicker;
	
private:
	void __fastcall DoApply(System::TObject* Sender, const int AValueIndex);
	void __fastcall DoClosePopup(System::TObject* Sender);
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual void __fastcall Activate();
	virtual void __fastcall Deactivate();
	
public:
	__fastcall virtual ~TiOSCellPopupPicker();
	void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
public:
	/* TiOSCellControl.Create */ inline __fastcall virtual TiOSCellPopupPicker(TColumnItem* const AOwner) : TiOSCellPopupLabel(AOwner) { }
	
};


__interface  INTERFACE_UUID("{2836336D-9724-4BC7-8F74-1ACCD612AF76}") IiOSCellGlyph  : public Iosapi::Uikit::UIImageView 
{
	
};

class PASCALIMPLEMENTATION TiOSCellGlyph : public TiOSCellControl
{
	typedef TiOSCellControl inherited;
	
private:
	System::Uitypes::TImageIndex FImageIndex;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual void __fastcall DoUpdate();
	
public:
	__fastcall virtual TiOSCellGlyph(TColumnItem* const AOwner);
public:
	/* TiOSCellControl.Destroy */ inline __fastcall virtual ~TiOSCellGlyph() { }
	
};


__interface  INTERFACE_UUID("{28363839-4327-48EC-8E8E-A1CA4FA3CA27}") IiOSCellImage  : public Iosapi::Uikit::UIImageView 
{
	
};

class PASCALIMPLEMENTATION TiOSCellImage : public TiOSCellControl
{
	typedef TiOSCellControl inherited;
	
private:
	Iosapi::Uikit::_di_UIImage FImage;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual Iosapi::Foundation::NSRect __fastcall GetFrame();
	virtual void __fastcall DoUpdate();
public:
	/* TiOSCellControl.Create */ inline __fastcall virtual TiOSCellImage(TColumnItem* const AOwner) : TiOSCellControl(AOwner) { }
	/* TiOSCellControl.Destroy */ inline __fastcall virtual ~TiOSCellImage() { }
	
};


__interface  INTERFACE_UUID("{283635BC-685C-4619-B6B9-2C0F355CB48D}") IiOSCellImageEditor  : public Iosapi::Uikit::UIView 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
};

class PASCALIMPLEMENTATION TiOSCellImageEditor : public TiOSCellControl
{
	typedef TiOSCellControl inherited;
	
private:
	Fmx::Graphics::TBitmap* FBitmap;
	bool FBitmapLoaded;
	TiOSCellImage* FImageControl;
	Fmx::Medialibrary::_di_IFMXTakenImageService FTakenImageService;
	void __fastcall DidReceiveBitmap(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	
protected:
	virtual void __fastcall DoApply(Fmx::Graphics::TBitmap* AImage);
	void __fastcall DoClosePopup();
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual void __fastcall DoUpdate();
	
public:
	__fastcall virtual TiOSCellImageEditor(TColumnItem* const AOwner);
	__fastcall virtual ~TiOSCellImageEditor();
	void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	virtual void __fastcall EditorClick();
};


__interface  INTERFACE_UUID("{2836383A-0872-4626-ABC1-4734E7CEB3A0}") IiOSCellCheck  : public Iosapi::Uikit::UIImageView 
{
	
};

class PASCALIMPLEMENTATION TiOSCellCheck : public TiOSCellControl
{
	typedef TiOSCellControl inherited;
	
private:
	TImageKind FValue;
	bool FInitialized;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual void __fastcall DoUpdate();
	virtual Iosapi::Foundation::NSRect __fastcall GetFrame();
public:
	/* TiOSCellControl.Create */ inline __fastcall virtual TiOSCellCheck(TColumnItem* const AOwner) : TiOSCellControl(AOwner) { }
	/* TiOSCellControl.Destroy */ inline __fastcall virtual ~TiOSCellCheck() { }
	
};


__interface  INTERFACE_UUID("{283634F2-8791-49EB-9EEA-2C3E5B41366C}") IiOSCellCheckEditor  : public Iosapi::Uikit::UIView 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
};

class PASCALIMPLEMENTATION TiOSCellCheckEditor : public TiOSCellControl
{
	typedef TiOSCellControl inherited;
	
private:
	TiOSCellCheck* FCheckControl;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual void __fastcall DoUpdate();
	
public:
	__fastcall virtual TiOSCellCheckEditor(TColumnItem* const AOwner);
	void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	virtual void __fastcall EditorClick();
public:
	/* TiOSCellControl.Destroy */ inline __fastcall virtual ~TiOSCellCheckEditor() { }
	
};


__interface  INTERFACE_UUID("{283638CF-3A80-4238-A5C1-311CFB381D79}") IFMXColumnItem  : public Iosapi::Uikit::UIView 
{
	
};

class PASCALIMPLEMENTATION TColumnItem : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
	
public:
	class DELPHICLASS TColumnLink;
	class PASCALIMPLEMENTATION TColumnLink : public System::TInterfacedObject
	{
		typedef System::TInterfacedObject inherited;
		
	private:
		Fmx::Grid::TColumn* FColumn;
		TColumnItem* FOwner;
		bool FChanged;
		bool FClassChanged;
		void __fastcall FreeNotification(System::TObject* AObject);
		Fmx::Grid::TColumn* __fastcall GetColumn();
		void __fastcall SetColumn(Fmx::Grid::TColumn* const Value);
		
	public:
		__fastcall virtual TColumnLink(TColumnItem* const AOwner);
		__fastcall virtual ~TColumnLink();
		__property Fmx::Grid::TColumn* Column = {read=FColumn, write=SetColumn};
		__property bool Changed = {read=FChanged, write=FChanged, nodefault};
		__property TColumnItem* Owner = {read=FOwner};
		__property bool ClassChanged = {read=FClassChanged, write=FClassChanged, nodefault};
private:
		void *__ICellControl;	// Fmx::Grid::ICellControl 
		void *__IFreeNotification;	// Fmx::Types::IFreeNotification 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {67922698-EEEE-4326-B114-F11145A1D200}
		operator Fmx::Grid::_di_ICellControl()
		{
			Fmx::Grid::_di_ICellControl intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Fmx::Grid::ICellControl*(void) { return (Fmx::Grid::ICellControl*)&__ICellControl; }
		#endif
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {FEB50EAF-A3B9-4B37-8EDB-1EF9EE2F22D4}
		operator Fmx::Types::_di_IFreeNotification()
		{
			Fmx::Types::_di_IFreeNotification intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Fmx::Types::IFreeNotification*(void) { return (Fmx::Types::IFreeNotification*)&__IFreeNotification; }
		#endif
		
	};
	
	
	_DECLARE_METACLASS(System::TMetaClass, TColumnLinkClass);
	
	
private:
	TiOSGrid* FiOSGrid;
	Fmx::Grid::TGridModel* FModel;
	TColumnLink* FColumnLink;
	TiOSCellControl* FInternalCell;
	
private:
	double FDefaultThickness;
	Iosapi::Foundation::NSRect FFrame;
	bool FHiddenFound;
	bool FSizeChanged;
	bool FPosChanged;
	bool FColLines;
	void __fastcall SetFrame(const Iosapi::Foundation::NSRect &Value);
	void __fastcall SetHiddenFound(const bool Value);
	void __fastcall SetColLines(const bool Value);
	Fmx::Grid::TColumn* __fastcall GetColumn();
	void __fastcall SetColumn(Fmx::Grid::TColumn* const Value);
	Iosapi::Uikit::_di_UIView __fastcall GetView();
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual TiOSCellControl* __fastcall CreateInternalCell() = 0 ;
	virtual void __fastcall DoUpdate() = 0 ;
	virtual TColumnLinkClass __fastcall GetColumnLinkClass(Fmx::Grid::TColumn* const AColumn);
	
public:
	__fastcall virtual TColumnItem(TiOSGrid* const AiOSGrid, const Iosapi::Uikit::_di_UIView AParent, Fmx::Grid::TColumn* const AColumn);
	__fastcall virtual ~TColumnItem();
	void __fastcall Update();
	Iosapi::Foundation::NSRect __fastcall ClientRect();
	Iosapi::Foundation::NSRect __fastcall RectPlaceIntoBounds(const Iosapi::Foundation::NSRect &Frame);
	__property TColumnLink* ColumnLink = {read=FColumnLink};
	__property TiOSGrid* iOSGrid = {read=FiOSGrid};
	__property Fmx::Grid::TGridModel* Model = {read=FModel};
	__property Fmx::Grid::TColumn* Column = {read=GetColumn, write=SetColumn};
	__property Iosapi::Uikit::_di_UIView View = {read=GetView};
	__property TiOSCellControl* InternalCell = {read=FInternalCell};
	__property Iosapi::Foundation::NSRect Frame = {read=FFrame, write=SetFrame};
	__property bool ColLines = {read=FColLines, write=SetColLines, nodefault};
	__property bool HiddenFound = {read=FHiddenFound, write=SetHiddenFound, nodefault};
};


class PASCALIMPLEMENTATION TBaseColumnItemList : public System::Generics::Collections::TList__1<TColumnItem*>
{
	typedef System::Generics::Collections::TList__1<TColumnItem*> inherited;
	
public:
	/* {System_Generics_Collections}TList<FMX_Grid_iOS_TColumnItem>.Create */ inline __fastcall TBaseColumnItemList()/* overload */ : System::Generics::Collections::TList__1<TColumnItem*>() { }
	/* {System_Generics_Collections}TList<FMX_Grid_iOS_TColumnItem>.Create */ inline __fastcall TBaseColumnItemList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TColumnItem*> > AComparer)/* overload */ : System::Generics::Collections::TList__1<TColumnItem*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_Grid_iOS_TColumnItem>.Create */ inline __fastcall TBaseColumnItemList(System::Generics::Collections::TEnumerable__1<TColumnItem*>* const Collection)/* overload */ : System::Generics::Collections::TList__1<TColumnItem*>(Collection) { }
	/* {System_Generics_Collections}TList<FMX_Grid_iOS_TColumnItem>.Destroy */ inline __fastcall virtual ~TBaseColumnItemList() { }
	
};


class PASCALIMPLEMENTATION TColumnItemList : public TBaseColumnItemList
{
	typedef TBaseColumnItemList inherited;
	
	
private:
	class DELPHICLASS TComparer;
	class PASCALIMPLEMENTATION TComparer : public System::TInterfacedObject
	{
		typedef System::TInterfacedObject inherited;
		
	public:
		int __fastcall Compare(TColumnItem* const Left, TColumnItem* const Right);
	public:
		/* TObject.Create */ inline __fastcall TComparer() : System::TInterfacedObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TComparer() { }
		
private:
		void *__IComparer__1;	// System::Generics::Defaults::IComparer__1<TColumnItem*> 
		
public:
		operator System::Generics::Defaults::IComparer__1<TColumnItem*>*(void) { return (System::Generics::Defaults::IComparer__1<TColumnItem*>*)&__IComparer__1; }
		
	};
	
	
	
private:
	static TComparer* FComparer;
	
public:
	__fastcall TColumnItemList();
	int __fastcall Find(Fmx::Grid::TColumn* const Column);
	bool __fastcall TryGetValue(Fmx::Grid::TColumn* const Column, TColumnItem* &Item);
	void __fastcall Assign(TColumnItemList* const Source, const double Top, const double Height);
	bool __fastcall RemoveUselessItems(const bool ExceptTiny = true);
public:
	/* {System_Generics_Collections}TList<FMX_Grid_iOS_TColumnItem>.Destroy */ inline __fastcall virtual ~TColumnItemList() { }
	
};


class PASCALIMPLEMENTATION TiOSHeaderItem : public TColumnItem
{
	typedef TColumnItem inherited;
	
private:
	TiOSLineView* FFirstBorder;
	TiOSLineView* FLeftBorder;
	TiOSLineView* FRightBorder;
	TiOSLineView* FLeftColumnLine;
	TiOSLineView* FRightColumnLine;
	
private:
	bool FFirst;
	void __fastcall UpdateVerticalBorders();
	void __fastcall SetFirst(const bool Value);
	
protected:
	virtual TiOSCellControl* __fastcall CreateInternalCell();
	virtual void __fastcall DoUpdate();
	
public:
	__fastcall virtual TiOSHeaderItem(TiOSGrid* const AiOSGrid, const Iosapi::Uikit::_di_UIView AParent, Fmx::Grid::TColumn* const AColumn);
	__fastcall virtual ~TiOSHeaderItem();
	__property bool First = {read=FFirst, write=SetFirst, nodefault};
};


__interface  INTERFACE_UUID("{2DD8288D-F976-4FE2-89B2-F7C469EAC5BF}") IiOSHeader  : public Iosapi::Uikit::UIView 
{
	virtual void __cdecl HandlePan(Iosapi::Uikit::_di_UIPanGestureRecognizer gestureRecognizer) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
};

class PASCALIMPLEMENTATION TiOSHeader : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
private:
	TiOSGrid* FiOSGrid;
	Fmx::Grid::TGridModel* FModel;
	TColumnItemList* FHeaderItems;
	
private:
	TiOSLineView* FLineHeader;
	double FWidth;
	double FHeight;
	int FIndexResizeHeader;
	int FIndexMoveHeader;
	Iosapi::Foundation::NSPoint FCapturePoint;
	Macapi::Objectivec::TOCLocal* FResizeColumnBorder;
	Macapi::Objectivec::TOCLocal* FMoveColumnItem;
	Iosapi::Uikit::_di_UIPanGestureRecognizer FPanRecognizer;
	int FIndexChangedColumn;
	int FFromIndex;
	int FToIndex;
	float FNewColumnWidth;
	Iosapi::Uikit::_di_UIView __fastcall GetView();
	bool __fastcall FindItemIndex(const Iosapi::Foundation::NSPoint &TouchPoint, int &Index)/* overload */;
	bool __fastcall FindItemIndex(const Iosapi::Foundation::_di_NSSet touches, int &Index)/* overload */;
	void __fastcall StartMoveOrResize(const Iosapi::Foundation::NSPoint &P);
	void __fastcall MoveOrResize(const Iosapi::Foundation::NSPoint &P);
	void __fastcall EndMoveOrResize(const Iosapi::Foundation::NSPoint &P);
	void __fastcall DoColumnResize();
	void __fastcall DoColumnIndexChange();
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	
public:
	__fastcall virtual TiOSHeader(TiOSGrid* const AiOSGrid);
	__fastcall virtual ~TiOSHeader();
	void __cdecl HandlePan(Iosapi::Uikit::_di_UIPanGestureRecognizer gestureRecognizer);
	void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	virtual void __fastcall Update();
	__property TiOSGrid* iOSGrid = {read=FiOSGrid};
	__property Fmx::Grid::TGridModel* Model = {read=FModel};
	__property TColumnItemList* HeaderItems = {read=FHeaderItems};
	__property double Width = {read=FWidth};
	__property double Height = {read=FHeight};
	__property Iosapi::Uikit::_di_UIView View = {read=GetView};
};


__interface  INTERFACE_UUID("{2DD823A5-A4FA-490E-A4EA-76DEE3C2F0D3}") IiOSInplaceEditor  : public Iosapi::Uikit::UIView 
{
	
};

class PASCALIMPLEMENTATION TiOSInplaceEditor : public TColumnItem
{
	typedef TColumnItem inherited;
	
	
public:
	class DELPHICLASS TEditorColumnLink;
	class PASCALIMPLEMENTATION TEditorColumnLink : public TColumnItem::TColumnLink
	{
		typedef TColumnItem::TColumnLink inherited;
		
	private:
		bool FReadOnly;
		bool __fastcall GetReadOnly();
		void __fastcall SetReadOnly(const bool Value);
		
	public:
		__property bool ReadOnly = {read=GetReadOnly, write=SetReadOnly, nodefault};
	public:
		/* TColumnLink.Create */ inline __fastcall virtual TEditorColumnLink(TColumnItem* const AOwner) : TColumnItem::TColumnLink(AOwner) { }
		/* TColumnLink.Destroy */ inline __fastcall virtual ~TEditorColumnLink() { }
		
private:
		void *__IReadOnly;	// Fmx::Types::IReadOnly 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {495B8B0C-D7C8-4835-AA5F-580939D21444}
		operator Fmx::Types::_di_IReadOnly()
		{
			Fmx::Types::_di_IReadOnly intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Fmx::Types::IReadOnly*(void) { return (Fmx::Types::IReadOnly*)&__IReadOnly; }
		#endif
		
	};
	
	
	
public:
	static constexpr System::Int8 BorderWidth = System::Int8(0x1);
	
	
private:
	Iosapi::Uikit::_di_UIView FBackground;
	bool FInitialized;
	bool FActive;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual void __fastcall DoUpdate();
	virtual TiOSCellControl* __fastcall CreateInternalCell();
	virtual TColumnItem::TColumnLinkClass __fastcall GetColumnLinkClass(Fmx::Grid::TColumn* const AColumn);
	
public:
	__fastcall virtual TiOSInplaceEditor(TiOSGrid* const AiOSGrid, const Iosapi::Uikit::_di_UIView AParent, Fmx::Grid::TColumn* const AColumn);
	__fastcall virtual ~TiOSInplaceEditor();
	void __fastcall Activate();
	void __fastcall Deactivate();
	void __fastcall EditorClick();
};


__interface  INTERFACE_UUID("{28363863-9876-470C-A415-E4DABD9D1DED}") IiOSCell  : public IFMXColumnItem 
{
	
};

class PASCALIMPLEMENTATION TiOSCell : public TColumnItem
{
	typedef TColumnItem inherited;
	
private:
	int FRow;
	void __fastcall SetRow(const int Value);
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual void __fastcall DoUpdate();
	virtual void __fastcall DoUpdateValue(TiOSCellControl* const ACell);
	virtual TiOSCellControl* __fastcall CreateInternalCell();
	
public:
	__fastcall virtual TiOSCell(TiOSGrid* const AiOSGrid, const Iosapi::Uikit::_di_UIView AParent, Fmx::Grid::TColumn* const AColumn);
	void __fastcall UpdateValue();
	void __fastcall UpdateBackground();
	__property int Row = {read=FRow, write=SetRow, nodefault};
public:
	/* TColumnItem.Destroy */ inline __fastcall virtual ~TiOSCell() { }
	
};


__interface  INTERFACE_UUID("{6DB65D8D-E8B3-4953-8A4F-DA7BFB87BAD8}") IiOSRow  : public Iosapi::Uikit::UIView 
{
	
};

class PASCALIMPLEMENTATION TiOSRow : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
private:
	TiOSGrid* FiOSGrid;
	Fmx::Grid::TGridModel* FModel;
	TiOSLineView* FLineDown;
	TColumnItemList* FCells;
	int __fastcall GetIndex();
	void __fastcall InitView();
	Iosapi::Uikit::_di_UIView __fastcall GetView();
	TiOSCell* __fastcall GetCells(const int Index);
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	void __fastcall PrepareForReuse();
	
public:
	__fastcall TiOSRow(TiOSGrid* const AiOSGrid);
	__fastcall virtual ~TiOSRow();
	void __fastcall Update();
	__property int Index = {read=GetIndex, nodefault};
	__property TiOSCell* Cells[const int Index] = {read=GetCells};
	__property TiOSGrid* iOSGrid = {read=FiOSGrid};
	__property Fmx::Grid::TGridModel* Model = {read=FModel};
	__property Iosapi::Uikit::_di_UIView View = {read=GetView};
};


__interface  INTERFACE_UUID("{0403CF5C-1E87-4F57-ACCA-969E36310372}") IiOSTable  : public Iosapi::Uikit::UIScrollView 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual bool __cdecl becomeFirstResponder() = 0 ;
};

class PASCALIMPLEMENTATION TiOSTable : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
	
private:
	class DELPHICLASS TRowComparer;
	class PASCALIMPLEMENTATION TRowComparer : public System::TInterfacedObject
	{
		typedef System::TInterfacedObject inherited;
		
	public:
		int __fastcall Compare(TiOSRow* const Left, TiOSRow* const Right);
	public:
		/* TObject.Create */ inline __fastcall TRowComparer() : System::TInterfacedObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TRowComparer() { }
		
private:
		void *__IComparer__1;	// System::Generics::Defaults::IComparer__1<TiOSRow*> 
		
public:
		operator System::Generics::Defaults::IComparer__1<TiOSRow*>*(void) { return (System::Generics::Defaults::IComparer__1<TiOSRow*>*)&__IComparer__1; }
		
	};
	
	
	
private:
	TiOSLineView* FLeftLine;
	TiOSLineView* FTopLine;
	TiOSGrid* FiOSGrid;
	Fmx::Grid::TGridModel* FModel;
	double FVKOffset;
	double FTableOffset;
	System::Generics::Collections::TStack__1<TiOSRow*>* FDisappearedRows;
	System::Generics::Collections::TDictionary__2<int,TiOSRow*>* FRows;
	double FRowHeight;
	int FRowCount;
	TiOSCellControl::TState FState;
	
private:
	static TRowComparer* FComparer;
	Iosapi::Uikit::_di_UIScrollView __fastcall GetView();
	bool __fastcall GetTouchCoord(const Iosapi::Foundation::_di_NSSet touches, float &x, float &y, int &TapCount, const Iosapi::Uikit::_di_UIView AView = Iosapi::Uikit::_di_UIView());
	void __fastcall SetVKOffset(const double Value);
	void __fastcall UpdateFrame();
	TiOSRow* __fastcall GetRows(const int Index);
	void __fastcall RowsAppeared(const int MinRow, const int MaxRow);
	void __fastcall RowsDisappeared(const int MinRow, const int MaxRow);
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	__property double VKOffset = {read=FVKOffset, write=SetVKOffset};
	bool __fastcall EnterState(const TiOSCellControl::TState AState);
	void __fastcall ResetState();
	
public:
	__fastcall virtual TiOSTable(TiOSGrid* const AiOSGrid);
	__fastcall virtual ~TiOSTable();
	virtual void __fastcall Update();
	__property TiOSGrid* iOSGrid = {read=FiOSGrid};
	__property Fmx::Grid::TGridModel* Model = {read=FModel};
	__property Iosapi::Uikit::_di_UIScrollView View = {read=GetView};
	__property TiOSCellControl::TState State = {read=FState, nodefault};
	__property TiOSRow* Rows[const int Index] = {read=GetRows};
	virtual void __fastcall DidScroll(const Iosapi::Uikit::_di_UIScrollView ScrollView);
	void __fastcall UpdateFocused();
	void __fastcall UpdateVisibleRows();
	__property double RowHeight = {read=FRowHeight};
	__property int RowCount = {read=FRowCount, nodefault};
	void __fastcall ScrollToSelectedCell(const bool Animated = true);
	void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	bool __cdecl becomeFirstResponder();
};


class PASCALIMPLEMENTATION TiOSGrid : public Fmx::Scrollbox::Ios::TiOSScrollBox
{
	typedef Fmx::Scrollbox::Ios::TiOSScrollBox inherited;
	
	
public:
	enum class DECLSPEC_DENUM TEditorResult : unsigned char { Success, Error, Cancel };
	
	enum class DECLSPEC_DENUM TContentState : unsigned char { Changed, Updating, Updated };
	
	
private:
	typedef System::StaticArray<Iosapi::Uikit::_di_UIImage, 3> _TiOSGrid__1;
	
	
private:
	double FDefaultThickness;
	double FDefaultHeaderHeight;
	double FDefaultRowHeight;
	double FDefaultLabelHeight;
	TiOSHeader* FiOSHeader;
	TiOSTable* FiOSTable;
	Macapi::Objectivec::TOCLocal* FiOSTableDelegate;
	Macapi::Objectivec::TOCLocal* FiOSQueue;
	_TiOSGrid__1 FImages;
	double FVirtualKeayboardOffset;
	
private:
	Macapi::Objectivec::TOCLocal* FiOSEditDelegate;
	TiOSInplaceEditor* FInplaceEditor;
	TContentState FContentState;
	Iosapi::Uikit::_di_UIColor FTintColor;
	Iosapi::Uikit::_di_UIColor FOddColor;
	Iosapi::Uikit::_di_UIColor FBkColor;
	Iosapi::Uikit::_di_UIColor FHighlightColor;
	Iosapi::Uikit::_di_UIColor FFocusColor;
	Iosapi::Uikit::_di_UIColor FUnfocusColor;
	Fmx::Grid::TGridModel::TCoord FOldCoord;
	bool FEditorMode;
	bool FEditorModeChanging;
	bool FForceUpdateRows;
	TEditorResult FEditorResult;
	bool FImagesCreated;
	bool FVKOffsetChanging;
	bool FFocused;
	Fmx::Graphics::TTextSettings* FTextSettings;
	HIDESBASE Fmx::Grid::TGridModel* __fastcall GetModel();
	MESSAGE void __fastcall MMContentChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMColumnChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMInvalidateCell(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TCoord> &Message);
	MESSAGE void __fastcall MMColumnMoved(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TColumnIndexes> &Message);
	MESSAGE void __fastcall MMSelChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMCellByPoint(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TPointInfo> &Message);
	MESSAGE void __fastcall PMGetDisplay_Cells(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TRectCoord> &Message);
	MESSAGE void __fastcall MMGetRowHeight(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMInvalidateContentSize(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMCanEdit(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall PMSetTopLeft(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TCoord> &Message);
	MESSAGE void __fastcall PMScrollToSelect(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMCellRect(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TCellInfo> &Message);
	MESSAGE void __fastcall MMShowEditor(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMHideEditor(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMPostEditorValue(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMRefreshEditorValue(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMEditorMode(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMGetEditorValue(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Rtti::TValue> &Message);
	MESSAGE void __fastcall PMVKDisplacement(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TVKInfo> &Message);
	MESSAGE void __fastcall MMGetViewportPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TPointF> &Message);
	MESSAGE void __fastcall MMSetViewportPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TPointF> &Message);
	MESSAGE void __fastcall MMGetViewportSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &Message);
	double __fastcall GetRowThickness();
	double __fastcall GetColumnThickness();
	bool __fastcall EditingDone(const bool Accept);
	bool __fastcall PostEditorValue();
	bool __fastcall RefreshEditor(const bool RefreshAppearance, const bool RefreshValue);
	Iosapi::Uikit::_di_UIImage __fastcall GetImages(const TImageKind Index);
	void __fastcall CreateImages();
	void __fastcall FreeImages();
	void __fastcall SetVirtualKeayboardOffset(const double Value);
	void __fastcall ForceScroll();
	TiOSHeaderItem* __fastcall HeaderItemByX(const double X, const bool FromLeftToRight);
	void __fastcall ShowEditorIfNeed();
	void __fastcall UpdateDefaultRowHeight();
	
protected:
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual void __fastcall SetSize(const System::Types::TSizeF &ASize);
	void __fastcall UpdateContent();
	void __fastcall UpdateSelection();
	virtual TiOSCellControlClass __fastcall GetCellClass(Fmx::Grid::TColumn* const Column);
	virtual TiOSCellControlClass __fastcall GetEditorClass(Fmx::Grid::TColumn* const Column);
	virtual TiOSHeader* __fastcall CreateHeader();
	TiOSTable* __fastcall CreateTable();
	virtual void __fastcall CellClick(Fmx::Grid::TColumn* const Column, const int Row);
	virtual void __fastcall CellDblClick(Fmx::Grid::TColumn* const Column, const int Row);
	virtual bool __fastcall CanEdit();
	virtual Iosapi::Foundation::NSRect __fastcall GetEditorRect();
	virtual TiOSInplaceEditor* __fastcall CreateInplaceEditor();
	virtual void __fastcall InplaceEditorActivate();
	virtual void __fastcall EditorReturnDown();
	virtual void __fastcall TableScrolled(const Iosapi::Foundation::NSPoint &ViewPortPosition);
	__property Macapi::Objectivec::TOCLocal* iOSQueue = {read=FiOSQueue};
	bool __fastcall PerformSelector(const System::UnicodeString Name, const double Delay = 0.000000E+00);
	__property double VirtualKeayboardOffset = {read=FVirtualKeayboardOffset, write=SetVirtualKeayboardOffset};
	
public:
	__fastcall virtual TiOSGrid(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */;
	__fastcall virtual ~TiOSGrid();
	__property Fmx::Grid::TGridModel* Model = {read=GetModel};
	virtual void __fastcall SetFocus();
	virtual void __fastcall ResetFocus();
	Iosapi::Foundation::NSRect __fastcall CellRect(const int ACol, const int ARow);
	Iosapi::Foundation::NSRect __fastcall PaddingRect(const Iosapi::Foundation::NSRect &ARect, Fmx::Grid::TColumn* const Column);
	__property double DefaultThickness = {read=FDefaultThickness};
	__property double DefaultRowHeight = {read=FDefaultRowHeight};
	__property double DefaultLabelHeight = {read=FDefaultLabelHeight};
	__property double DefaultHeaderHeight = {read=FDefaultHeaderHeight};
	__property double RowThickness = {read=GetRowThickness};
	__property double ColumnThickness = {read=GetColumnThickness};
	__property TiOSHeader* iOSHeader = {read=FiOSHeader};
	__property TiOSTable* iOSTable = {read=FiOSTable};
	__property bool EditorMode = {read=FEditorMode, nodefault};
	void __fastcall ShowEditor();
	__property TEditorResult EditorResult = {read=FEditorResult, nodefault};
	void __fastcall HideEditor(const bool Accept);
	__property Iosapi::Uikit::_di_UIImage Images[const TImageKind Index] = {read=GetImages};
public:
	/* TiOSScrollBox.Create */ inline __fastcall virtual TiOSGrid()/* overload */ : Fmx::Scrollbox::Ios::TiOSScrollBox() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Grid */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GRID_IOS)
using namespace Fmx::Grid::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GRID)
using namespace Fmx::Grid;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Grid_IosHPP
