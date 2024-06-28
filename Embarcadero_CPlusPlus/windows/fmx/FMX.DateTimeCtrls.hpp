// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.DateTimeCtrls.pas' rev: 34.00 (Windows)

#ifndef Fmx_DatetimectrlsHPP
#define Fmx_DatetimectrlsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Types.hpp>
#include <System.Rtti.hpp>
#include <System.UITypes.hpp>
#include <FMX.Types.hpp>
#include <FMX.TextLayout.hpp>
#include <FMX.Controls.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.VirtualKeyboard.hpp>
#include <FMX.Menus.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Pickers.hpp>
#include <FMX.DateTimeCtrls.Types.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Datetimectrls
{
//-- forward type declarations -----------------------------------------------
struct TDTFormatKindHelper /* Helper for enum 'TDTFormatKind' */;
class DELPHICLASS TCustomDateTimeEdit;
class DELPHICLASS TCustomTimeEdit;
class DELPHICLASS TTimeEdit;
class DELPHICLASS TCustomDateEdit;
class DELPHICLASS TDateEdit;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TDTFormatKind : unsigned char { Short, Long, dfShort _DEPRECATED_ATTRIBUTE3("Use TDTFormatKind.Short")  = 0x0, dfLong _DEPRECATED_ATTRIBUTE3("Use TDTFormatKind.Long")  = 0x1 };

typedef TDTFormatKind TDTTimeFormat _DEPRECATED_ATTRIBUTE1("Use TDTFormatKind instead") ;

class PASCALIMPLEMENTATION TCustomDateTimeEdit : public Fmx::Controls::TTextControl
{
	typedef Fmx::Controls::TTextControl inherited;
	
private:
	static const System::Int8 UnknowFormatPart = System::Int8(-1);
	
	Fmx::Datetimectrls::Types::TDateTimeFormatter* FDTFormatter;
	bool FReadOnly;
	bool FShowCheckBox;
	bool FShowClearButton;
	bool FIsChecked;
	bool FIsPressed;
	bool FIsEmpty;
	bool FSupportKeyboardInput;
	Fmx::Types::TVirtualKeyboardType FKeyboardType;
	Fmx::Types::TReturnKeyType FReturnKeyType;
	Fmx::Virtualkeyboard::_di_IFMXVirtualKeyboardService FKeyboardService;
	System::UnicodeString FCustomFormat;
	TDTFormatKind FFormatKind;
	Fmx::Graphics::TBrush* FSelectionFill;
	Fmx::Textlayout::TTextLayout* FTextLayout;
	Fmx::Stdctrls::TCheckBox* FCheck;
	Fmx::Controls::TControl* FClearButton;
	System::Classes::TNotifyEvent FOnCheckChanged;
	System::Classes::TNotifyEvent FOnOpenPicker;
	System::Classes::TNotifyEvent FOnClosePicker;
	System::Classes::TNotifyEvent FOnDateTimeChanged;
	void __fastcall SetDateTime(const System::TDateTime Value);
	System::TDateTime __fastcall GetDateTime();
	System::TDate __fastcall GetDate();
	System::TTime __fastcall GetTime();
	void __fastcall SetCustomFormat(const System::UnicodeString Value);
	void __fastcall SetIndexFormatPart(const int Value);
	void __fastcall SetShowCheckBox(const bool Value);
	void __fastcall SetShowClearButton(const bool Value);
	void __fastcall SetIsChecked(const bool Value);
	void __fastcall SetIsEmpty(const bool Value);
	Fmx::Types::TVirtualKeyboardType __fastcall GetKeyboardType();
	void __fastcall SetKeyboardType(Fmx::Types::TVirtualKeyboardType Value);
	void __fastcall SetReturnKeyType(Fmx::Types::TReturnKeyType Value);
	Fmx::Types::TReturnKeyType __fastcall GetReturnKeyType();
	bool __fastcall IsPassword();
	void __fastcall DoCopy(System::TObject* Sender);
	void __fastcall DoPaste(System::TObject* Sender);
	void __fastcall NotifyObserverIfObserver(System::Classes::TObservers* const AObserver);
	void __fastcall ObserversCallUpdate(System::Classes::TObservers* const AObserver);
	void __fastcall ObserversCallTrackUpdate(System::Classes::TObservers* const AObserver);
	bool __fastcall GetReadOnly();
	void __fastcall SetReadOnly(const bool Value);
	
protected:
	Fmx::Pickers::TCustomDateTimePicker* FDateTimePicker;
	Fmx::Platform::_di_IFMXClipboardService FClipboardService;
	Fmx::Menus::TPopupMenu* FContextMenu;
	System::Generics::Collections::TList__1<System::Types::TRectF>* FFormatSizeParts;
	int FIndexCurrentFormatPart;
	bool FContinueEnteringValue;
	System::UnicodeString FEnteringValue;
	virtual System::UnicodeString __fastcall GetFormat();
	bool __fastcall HasFormat();
	bool __fastcall FindCurrentFormatPart(Fmx::Datetimectrls::Types::TDTFormatPart &ATimeSection);
	void __fastcall SetFormatKind(const TDTFormatKind Value);
	TDTFormatKind __fastcall GetFormatKind();
	System::UnicodeString __fastcall GetMaskForEmptyDateTime();
	virtual void __fastcall GoToNextFormatPart();
	virtual void __fastcall GoToPreviousFormatPart();
	virtual void __fastcall HandlerPickerClosed(System::TObject* Sender);
	virtual void __fastcall HandlerPickerOpened(System::TObject* Sender);
	virtual void __fastcall HandlerPickerDateTimeChanged(System::TObject* Sender, const System::TDateTime ADate);
	virtual void __fastcall InitPicker();
	virtual void __fastcall DoContentPaint(System::TObject* Sender, Fmx::Graphics::TCanvas* Canvas, const System::Types::TRectF &ARect);
	virtual void __fastcall DrawSelection(Fmx::Graphics::TCanvas* ACanvas);
	virtual void __fastcall CalculateTextSize();
	virtual void __fastcall InitTextLayout();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	__property Fmx::Graphics::TBrush* SelectionFill = {read=FSelectionFill};
	__property Fmx::Textlayout::TTextLayout* TextLayout = {read=FTextLayout};
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall EnterValue(System::WideChar &KeyChar);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	bool __fastcall HasTextObject();
	bool __fastcall HasCheckBox();
	bool __fastcall HasClearButton();
	virtual void __fastcall DoCheckChanged(System::TObject* Sender);
	virtual void __fastcall DoClearButtonClick(System::TObject* Sender);
	virtual void __fastcall DoTextObjectSizeChanged(System::TObject* Sender);
	__property Fmx::Stdctrls::TCheckBox* CheckBox = {read=FCheck};
	__property Fmx::Controls::TControl* ClearButton = {read=FClearButton};
	virtual void __fastcall UpdateTextOpacity();
	virtual void __fastcall DoEnter();
	virtual void __fastcall DoExit();
	virtual void __fastcall DoDateTimeChanged();
	virtual void __fastcall DoDateTimeChangedByUser();
	virtual void __fastcall DoTextChanged();
	virtual void __fastcall FormatterDateTimeChanged(System::TObject* Sender);
	virtual void __fastcall IncrementDateTimePart();
	virtual void __fastcall DecrementDateTimePart();
	virtual int __fastcall FindDateTimeSection(const System::Types::TPointF &APos);
	virtual void __fastcall SetTime(const System::TTime Value);
	virtual void __fastcall SetDate(const System::TDate Value);
	virtual void __fastcall SetTextInternal(const System::UnicodeString Value);
	virtual void __fastcall UpdateText();
	virtual void __fastcall UpdateTextWithoutChanges();
	__property int IndexCurrentFormatPart = {read=FIndexCurrentFormatPart, write=SetIndexFormatPart, nodefault};
	virtual void __fastcall CreateContextMenu();
	void __fastcall CreateContextMenuItem(const System::UnicodeString AActionName, const System::UnicodeString ATitleName, const System::Classes::TNotifyEvent AEventHandler = 0x0);
	virtual bool __fastcall ShowContextMenu(const System::Types::TPointF &ScreenPosition);
	virtual void __fastcall DoChanged();
	virtual System::Types::TSizeF __fastcall GetDefaultSize();
	virtual Fmx::Controls::TTextSettingsInfo::TCustomTextSettingsClass __fastcall GetTextSettingsClass();
	bool __fastcall IsDesktop();
	bool __fastcall IsMobilePreview();
	virtual void __fastcall RefreshPlatformBehaviour();
	__property bool SupportKeyboardInput = {read=FSupportKeyboardInput, write=FSupportKeyboardInput, nodefault};
	
public:
	__fastcall virtual TCustomDateTimeEdit(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TCustomDateTimeEdit();
	virtual void __fastcall OpenPicker();
	virtual void __fastcall ClosePicker();
	virtual bool __fastcall IsPickerOpened();
	bool __fastcall HasPicker();
	virtual bool __fastcall CanUsePicker();
	virtual bool __fastcall CanInput();
	virtual bool __fastcall CanObserve(const int ID);
	virtual void __fastcall ObserverAdded(const int ID, const System::Classes::_di_IObserver Observer);
	void __fastcall ObserverToggle(const System::Classes::_di_IObserver AObserver, const bool Value);
	virtual void __fastcall CopyToClipboard();
	virtual void __fastcall PasteFromClipboard();
	__property System::TDateTime DateTime = {read=GetDateTime, write=SetDateTime};
	__property System::TTime Time = {read=GetTime, write=SetTime};
	__property System::TDate Date = {read=GetDate, write=SetDate};
	__property bool ShowCheckBox = {read=FShowCheckBox, write=SetShowCheckBox, default=0};
	__property bool ShowClearButton = {read=FShowClearButton, write=SetShowClearButton, default=0};
	__property bool IsChecked = {read=FIsChecked, write=SetIsChecked, default=1};
	__property bool IsPressed = {read=FIsPressed, nodefault};
	__property bool IsEmpty = {read=FIsEmpty, write=SetIsEmpty, default=0};
	__property Fmx::Types::TVirtualKeyboardType KeyboardType = {read=GetKeyboardType, write=SetKeyboardType, default=2};
	__property bool ReadOnly = {read=FReadOnly, write=FReadOnly, default=0};
	__property System::UnicodeString Format = {read=FCustomFormat, write=SetCustomFormat};
	__property System::Classes::TNotifyEvent OnCheckChanged = {read=FOnCheckChanged, write=FOnCheckChanged};
	__property System::Classes::TNotifyEvent OnClosePicker = {read=FOnClosePicker, write=FOnClosePicker};
	__property System::Classes::TNotifyEvent OnOpenPicker = {read=FOnOpenPicker, write=FOnOpenPicker};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnDateTimeChanged, write=FOnDateTimeChanged};
private:
	void *__IVirtualKeyboardControl;	// Fmx::Types::IVirtualKeyboardControl 
	void *__IReadOnly;	// Fmx::Types::IReadOnly 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {41127080-97FC-4C30-A880-AB6CD351A6C4}
	operator Fmx::Types::_di_IVirtualKeyboardControl()
	{
		Fmx::Types::_di_IVirtualKeyboardControl intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IVirtualKeyboardControl*(void) { return (Fmx::Types::IVirtualKeyboardControl*)&__IVirtualKeyboardControl; }
	#endif
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


class PASCALIMPLEMENTATION TCustomTimeEdit : public TCustomDateTimeEdit
{
	typedef TCustomDateTimeEdit inherited;
	
private:
	bool FUseNowTime;
	Fmx::Types::_di_IFMXTimerService FTimerService;
	NativeUInt FTimerHandle;
	Fmx::Controls::TControl* FUpButton;
	Fmx::Controls::TControl* FDownButton;
	void __fastcall SetUseNowTime(const bool Value);
	
protected:
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual System::UnicodeString __fastcall GetFormat();
	virtual void __fastcall SetText(const System::UnicodeString AValue);
	virtual void __fastcall DoTimer();
	virtual void __fastcall DoUpButtonClick(System::TObject* Sender);
	virtual void __fastcall DoDownButtonClick(System::TObject* Sender);
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall RefreshPlatformBehaviour();
	
public:
	__fastcall virtual TCustomTimeEdit(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TCustomTimeEdit();
	virtual void __fastcall CopyToClipboard();
	virtual bool __fastcall CanInput();
	__property bool UseNowTime = {read=FUseNowTime, write=SetUseNowTime, default=0};
	__property TDTFormatKind TimeFormatKind = {read=GetFormatKind, write=SetFormatKind, default=0};
};


class PASCALIMPLEMENTATION TTimeEdit : public TCustomTimeEdit
{
	typedef TCustomTimeEdit inherited;
	
public:
	__property Font;
	__property FontColor = {default=-16777216};
	__property TextAlign = {default=1};
	
__published:
	__property ShowClearButton = {default=0};
	__property ShowCheckBox = {default=0};
	__property IsChecked = {default=1};
	__property Format = {default=0};
	__property Time = {default=0};
	__property TimeFormatKind = {default=0};
	__property UseNowTime = {default=0};
	__property IsEmpty = {default=0};
	__property OnChange;
	__property OnCheckChanged;
	__property OnClosePicker;
	__property OnOpenPicker;
	__property Align = {default=0};
	__property Anchors;
	__property CanFocus = {default=1};
	__property CanParentFocus = {default=0};
	__property Cursor = {default=-4};
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property DisableFocusEffect = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Height;
	__property HelpContext = {default=0};
	__property HelpKeyword = {default=0};
	__property HelpType = {default=1};
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property Locked = {default=0};
	__property KeyboardType = {default=2};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property ReadOnly = {default=0};
	__property Scale;
	__property Size;
	__property StyleLookup = {default=0};
	__property StyledSettings;
	__property TextSettings;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TouchTargetExpansion;
	__property Visible = {default=1};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property OnApplyStyleLookup;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
public:
	/* TCustomTimeEdit.Create */ inline __fastcall virtual TTimeEdit(System::Classes::TComponent* AOwner)/* overload */ : TCustomTimeEdit(AOwner) { }
	/* TCustomTimeEdit.Destroy */ inline __fastcall virtual ~TTimeEdit() { }
	
};


class PASCALIMPLEMENTATION TCustomDateEdit : public TCustomDateTimeEdit
{
	typedef TCustomDateTimeEdit inherited;
	
private:
	System::Uitypes::TCalDayOfWeek FFirstDayOfWeek;
	bool FShowWeekNumbers;
	bool FTodayDefault;
	Fmx::Controls::TControl* FArrowButton;
	void __fastcall SetTodayDefault(const bool Value);
	
protected:
	virtual System::Rtti::TValue __fastcall GetData();
	virtual void __fastcall SetData(const System::Rtti::TValue &Value);
	virtual System::UnicodeString __fastcall GetFormat();
	virtual void __fastcall SetText(const System::UnicodeString AValue);
	virtual void __fastcall InitPicker();
	void __fastcall DoArrowButtonClick(System::TObject* Sender);
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	__property Fmx::Controls::TControl* ArrowButton = {read=FArrowButton};
	
public:
	__fastcall virtual TCustomDateEdit(System::Classes::TComponent* AOwner)/* overload */;
	virtual void __fastcall CopyToClipboard();
	__property bool TodayDefault = {read=FTodayDefault, write=SetTodayDefault, default=0};
	__property bool WeekNumbers = {read=FShowWeekNumbers, write=FShowWeekNumbers, default=0};
	__property System::Uitypes::TCalDayOfWeek FirstDayOfWeek = {read=FFirstDayOfWeek, write=FFirstDayOfWeek, default=7};
	__property TDTFormatKind DateFormatKind = {read=GetFormatKind, write=SetFormatKind, default=0};
public:
	/* TCustomDateTimeEdit.Destroy */ inline __fastcall virtual ~TCustomDateEdit() { }
	
};


class PASCALIMPLEMENTATION TDateEdit : public TCustomDateEdit
{
	typedef TCustomDateEdit inherited;
	
public:
	__property Font;
	__property TextAlign = {default=1};
	
__published:
	__property ShowClearButton = {default=0};
	__property ShowCheckBox = {default=0};
	__property IsChecked = {default=1};
	__property Date = {default=0};
	__property WeekNumbers = {default=0};
	__property Format = {default=0};
	__property TodayDefault = {default=0};
	__property DateFormatKind = {default=0};
	__property IsEmpty = {default=0};
	__property OnChange;
	__property OnCheckChanged;
	__property OnClosePicker;
	__property OnOpenPicker;
	__property Align = {default=0};
	__property Anchors;
	__property CanFocus = {default=1};
	__property CanParentFocus = {default=0};
	__property Cursor = {default=-4};
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property DisableFocusEffect = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property FirstDayOfWeek = {default=7};
	__property Height;
	__property HelpContext = {default=0};
	__property HelpKeyword = {default=0};
	__property HelpType = {default=1};
	__property Hint = {default=0};
	__property HitTest = {default=1};
	__property Locked = {default=0};
	__property KeyboardType = {default=2};
	__property Padding;
	__property Opacity;
	__property Margins;
	__property PopupMenu;
	__property Position;
	__property RotationAngle = {default=0};
	__property RotationCenter;
	__property ReadOnly = {default=0};
	__property Scale;
	__property Size;
	__property StyleLookup = {default=0};
	__property StyledSettings;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property TextSettings;
	__property TouchTargetExpansion;
	__property Visible = {default=1};
	__property Width;
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property OnApplyStyleLookup;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
public:
	/* TCustomDateEdit.Create */ inline __fastcall virtual TDateEdit(System::Classes::TComponent* AOwner)/* overload */ : TCustomDateEdit(AOwner) { }
	
public:
	/* TCustomDateTimeEdit.Destroy */ inline __fastcall virtual ~TDateEdit() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Datetimectrls */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DATETIMECTRLS)
using namespace Fmx::Datetimectrls;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_DatetimectrlsHPP
