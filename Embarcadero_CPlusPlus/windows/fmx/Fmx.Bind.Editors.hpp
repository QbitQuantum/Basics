// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Fmx.Bind.Editors.pas' rev: 34.00 (Windows)

#ifndef Fmx_Bind_EditorsHPP
#define Fmx_Bind_EditorsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.Editors.hpp>
#include <System.Bindings.ObjEval.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.ListView.hpp>
#include <FMX.ListView.Adapters.Base.hpp>
#include <FMX.ListView.Appearances.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Memo.hpp>
#include <FMX.StdCtrls.hpp>
#include <System.Rtti.hpp>
#include <FMX.Graphics.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <System.UITypes.hpp>
#include <FMX.DateTimeCtrls.hpp>
#include <FMX.ComboEdit.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Fmx.Bind.Editors"

namespace Fmx
{
namespace Bind
{
namespace Editors
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindStateCheckBoxEditor;
class DELPHICLASS TBindEmptyDateTimeEditEditor;
class DELPHICLASS TBindListLookupEditorImpl;
class DELPHICLASS TFmxObjectEditorObject;
class DELPHICLASS TControlEditorObject;
class DELPHICLASS TStyledControlEditorObject;
class DELPHICLASS TTextControlEditorObject;
class DELPHICLASS TBindListBoxItemData;
class DELPHICLASS TBindListListItemEditorObject;
class DELPHICLASS TBindListListBoxEditorObject;
class DELPHICLASS TBindListViewLookupEditorImpl;
class DELPHICLASS TBindListViewEditor;
class DELPHICLASS TListViewItemEditorObject;
class DELPHICLASS TBindListMetroListBoxEditorObject;
class DELPHICLASS TBindListComboBoxEditorObject;
class DELPHICLASS TBindListMetroComboBoxEditorObject;
class DELPHICLASS TBindListListBoxEditor;
class DELPHICLASS TBindListMetroListBoxEditor;
class DELPHICLASS TBindListItemDataListBoxEditor;
class DELPHICLASS TBindListComboBoxEditor;
class DELPHICLASS TBindListMetroComboBoxEditor;
class DELPHICLASS TBindListItemDataComboBoxEditor;
class DELPHICLASS TBaseListBoxItemEditorObject;
class DELPHICLASS TStringGridItemEditorObject;
class DELPHICLASS TGridItemEditorObject;
class DELPHICLASS TBindListStringGridEditor;
class DELPHICLASS TValueCache;
class DELPHICLASS TBindListGridEditor;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindStateCheckBoxEditor : public Data::Bind::Editors::TBindCheckBoxEditor
{
	typedef Data::Bind::Editors::TBindCheckBoxEditor inherited;
	
private:
	Fmx::Stdctrls::TCheckBox* FCheckBox;
	
public:
	__fastcall TBindStateCheckBoxEditor(Fmx::Stdctrls::TCheckBox* ACheckBox);
	virtual Data::Bind::Components::TBindCheckBoxState __fastcall GetState();
	virtual void __fastcall SetState(Data::Bind::Components::TBindCheckBoxState Value);
	virtual bool __fastcall GetAllowGrayed();
	virtual void __fastcall SetAllowGrayed(bool Value);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindStateCheckBoxEditor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindEmptyDateTimeEditEditor : public Data::Bind::Editors::TBindDateTimeEditEditor
{
	typedef Data::Bind::Editors::TBindDateTimeEditEditor inherited;
	
private:
	Fmx::Datetimectrls::TCustomDateTimeEdit* FCustomDateTimeEdit;
	
public:
	__fastcall TBindEmptyDateTimeEditEditor(Fmx::Datetimectrls::TCustomDateTimeEdit* ADateTimeEdit);
	virtual bool __fastcall GetIsEmpty();
	virtual void __fastcall SetIsEmpty(bool Value);
	virtual System::TDateTime __fastcall GetDateTime();
	virtual void __fastcall SetDateTime(System::TDateTime ADateTime);
	virtual System::TTime __fastcall GetTime();
	virtual void __fastcall SetTime(System::TTime ATime);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindEmptyDateTimeEditEditor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListLookupEditorImpl : public Data::Bind::Editors::TBindListLookupEditor
{
	typedef Data::Bind::Editors::TBindListLookupEditor inherited;
	
private:
	System::Generics::Collections::TDictionary__2<Fmx::Listbox::TListBoxItem*,System::Rtti::TValue>* FLookupDictionary;
	Fmx::Listbox::TListBoxItem* __fastcall FindLookupValue(const System::Rtti::TValue &AValue);
	bool __fastcall SameValue(const System::Rtti::TValue &AValue1, const System::Rtti::TValue &AValue2);
	
protected:
	void __fastcall ListCleared();
	void __fastcall ItemRemoved(Fmx::Listbox::TListBoxItem* AListItem);
	virtual Fmx::Listbox::TListBoxItem* __fastcall GetSelected() = 0 ;
	virtual int __fastcall ListCount() = 0 ;
	virtual Fmx::Listbox::TListBoxItem* __fastcall GetListItem(int I) = 0 ;
	virtual void __fastcall SetSelected(Fmx::Listbox::TListBoxItem* AListItem) = 0 ;
	virtual System::Rtti::TValue __fastcall GetLookupValue(const System::Bindings::Evalprotocol::_di_IScope AScope);
	virtual void __fastcall SetLookupValue(const System::Bindings::Evalprotocol::_di_IScope AScope, const System::Rtti::TValue &AValue);
	virtual System::Rtti::TValue __fastcall GetSelectedLookupValue();
	virtual void __fastcall SetSelectedLookupValue(const System::Rtti::TValue &AValue);
	
public:
	__fastcall virtual ~TBindListLookupEditorImpl();
public:
	/* TObject.Create */ inline __fastcall TBindListLookupEditorImpl() : Data::Bind::Editors::TBindListLookupEditor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFmxObjectEditorObject : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Rtti::TValue __fastcall GetData();
	int __fastcall GetIndex();
	Fmx::Types::TFmxObject* __fastcall GetParent();
	float __fastcall GetTagFloat();
	System::TObject* __fastcall GetTagObject();
	System::UnicodeString __fastcall GetTagString();
	void __fastcall SetData(const System::Rtti::TValue &Value);
	void __fastcall SetIndex(const int Value);
	void __fastcall SetParent(Fmx::Types::TFmxObject* const Value);
	void __fastcall SetTagFloat(const float Value);
	void __fastcall SetTagObject(System::TObject* const Value);
	void __fastcall SetTagString(const System::UnicodeString Value);
	
protected:
	virtual bool __fastcall CheckRange() = 0 ;
	virtual Fmx::Types::TFmxObject* __fastcall CurrentFmxObject() = 0 ;
	
public:
	Fmx::Types::TFmxObject* __fastcall FindStyleResource(const System::UnicodeString AStyleLookup);
	__property System::TObject* TagObject = {read=GetTagObject, write=SetTagObject};
	__property float TagFloat = {read=GetTagFloat, write=SetTagFloat};
	__property System::UnicodeString TagString = {read=GetTagString, write=SetTagString};
	__property System::Rtti::TValue Data = {read=GetData, write=SetData};
	__property Fmx::Types::TFmxObject* Parent = {read=GetParent, write=SetParent};
	__property int Index = {read=GetIndex, write=SetIndex, nodefault};
public:
	/* TObject.Create */ inline __fastcall TFmxObjectEditorObject() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFmxObjectEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TControlEditorObject : public TFmxObjectEditorObject
{
	typedef TFmxObjectEditorObject inherited;
	
private:
	Fmx::Types::TAlignLayout __fastcall GetAlign();
	bool __fastcall GetClipChildren();
	bool __fastcall GetClipParent();
	System::Uitypes::TDragMode __fastcall GetDragMode();
	bool __fastcall GetEnabled();
	bool __fastcall GetEnableDragHighlight();
	float __fastcall GetHeight();
	bool __fastcall GetHitTest();
	bool __fastcall GetLocked();
	Fmx::Types::TBounds* __fastcall GetMargins();
	float __fastcall GetOpacity();
	Fmx::Types::TBounds* __fastcall GetPadding();
	Fmx::Types::TCustomPopupMenu* __fastcall GetPopupMenu();
	Fmx::Types::TPosition* __fastcall GetPosition();
	float __fastcall GetRotationAngle();
	Fmx::Types::TPosition* __fastcall GetRotationCenter();
	Fmx::Types::TPosition* __fastcall GetScale();
	System::Uitypes::TTabOrder __fastcall GetTabOrder();
	bool __fastcall GetVisible();
	float __fastcall GetWidth();
	void __fastcall SetAlign(const Fmx::Types::TAlignLayout Value);
	void __fastcall SetClipChildren(const bool Value);
	void __fastcall SetClipParent(const bool Value);
	void __fastcall SetDragMode(const System::Uitypes::TDragMode Value);
	void __fastcall SetEnabled(const bool Value);
	void __fastcall SetEnableDragHighlight(const bool Value);
	void __fastcall SetHeight(const float Value);
	void __fastcall SetHitTest(const bool Value);
	void __fastcall SetLocked(const bool Value);
	void __fastcall SetMargins(Fmx::Types::TBounds* const Value);
	void __fastcall SetOpacity(const float Value);
	void __fastcall SetPadding(Fmx::Types::TBounds* const Value);
	void __fastcall SetPopupMenu(Fmx::Types::TCustomPopupMenu* const Value);
	void __fastcall SetPosition(Fmx::Types::TPosition* const Value);
	void __fastcall SetRotationAngle(const float Value);
	void __fastcall SetScale(Fmx::Types::TPosition* const Value);
	void __fastcall SetTabOrder(const System::Uitypes::TTabOrder Value);
	void __fastcall SetVisible(const bool Value);
	void __fastcall SetWidth(const float Value);
	void __fastcall SetRotationCenter(Fmx::Types::TPosition* const Value);
	
protected:
	virtual Fmx::Controls::TControl* __fastcall CurrentControl() = 0 ;
	virtual Fmx::Types::TFmxObject* __fastcall CurrentFmxObject();
	
public:
	__property Fmx::Types::TAlignLayout Align = {read=GetAlign, write=SetAlign, nodefault};
	__property System::Uitypes::TDragMode DragMode = {read=GetDragMode, write=SetDragMode, nodefault};
	__property bool EnableDragHighlight = {read=GetEnableDragHighlight, write=SetEnableDragHighlight, nodefault};
	__property bool Enabled = {read=GetEnabled, write=SetEnabled, nodefault};
	__property Fmx::Types::TPosition* Position = {read=GetPosition, write=SetPosition};
	__property float RotationAngle = {read=GetRotationAngle, write=SetRotationAngle};
	__property Fmx::Types::TPosition* RotationCenter = {read=GetRotationCenter, write=SetRotationCenter};
	__property bool Locked = {read=GetLocked, write=SetLocked, nodefault};
	__property float Width = {read=GetWidth, write=SetWidth};
	__property float Height = {read=GetHeight, write=SetHeight};
	__property Fmx::Types::TBounds* Margins = {read=GetMargins, write=SetMargins};
	__property Fmx::Types::TBounds* Padding = {read=GetPadding, write=SetPadding};
	__property float Opacity = {read=GetOpacity, write=SetOpacity};
	__property bool ClipChildren = {read=GetClipChildren, write=SetClipChildren, nodefault};
	__property bool ClipParent = {read=GetClipParent, write=SetClipParent, nodefault};
	__property bool HitTest = {read=GetHitTest, write=SetHitTest, default=1};
	__property Fmx::Types::TCustomPopupMenu* PopupMenu = {read=GetPopupMenu, write=SetPopupMenu};
	__property Fmx::Types::TPosition* Scale = {read=GetScale, write=SetScale};
	__property System::Uitypes::TTabOrder TabOrder = {read=GetTabOrder, write=SetTabOrder, nodefault};
	__property bool Visible = {read=GetVisible, write=SetVisible, nodefault};
public:
	/* TObject.Create */ inline __fastcall TControlEditorObject() : TFmxObjectEditorObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TControlEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStyledControlEditorObject : public TControlEditorObject
{
	typedef TControlEditorObject inherited;
	
private:
	bool __fastcall GetAutoTranslate();
	System::Classes::THelpContext __fastcall GetHelpContext();
	System::UnicodeString __fastcall GetHelpKeyword();
	System::Classes::THelpType __fastcall GetHelpType();
	System::UnicodeString __fastcall GetStyleLookup();
	System::Rtti::TValue __fastcall GetStyleData(const System::UnicodeString Index);
	void __fastcall SetHelpContext(const System::Classes::THelpContext Value);
	void __fastcall SetHelpKeyword(const System::UnicodeString Value);
	void __fastcall SetHelpType(const System::Classes::THelpType Value);
	void __fastcall SetStyleLookup(const System::UnicodeString Value);
	void __fastcall SetStyleData(const System::UnicodeString Index, const System::Rtti::TValue &Value);
	void __fastcall SetAutoTranslate(const bool Value);
	
protected:
	virtual Fmx::Controls::TStyledControl* __fastcall CurrentStyledControl() = 0 ;
	virtual Fmx::Controls::TControl* __fastcall CurrentControl();
	
public:
	__property bool AutoTranslate = {read=GetAutoTranslate, write=SetAutoTranslate, nodefault};
	__property System::Classes::THelpType HelpType = {read=GetHelpType, write=SetHelpType, nodefault};
	__property System::UnicodeString HelpKeyword = {read=GetHelpKeyword, write=SetHelpKeyword};
	__property System::Classes::THelpContext HelpContext = {read=GetHelpContext, write=SetHelpContext, nodefault};
	__property System::UnicodeString StyleLookup = {read=GetStyleLookup, write=SetStyleLookup};
	__property System::Rtti::TValue StylesData[const System::UnicodeString Index] = {read=GetStyleData, write=SetStyleData};
public:
	/* TObject.Create */ inline __fastcall TStyledControlEditorObject() : TControlEditorObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TStyledControlEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTextControlEditorObject : public TStyledControlEditorObject
{
	typedef TStyledControlEditorObject inherited;
	
private:
	Fmx::Graphics::TFont* __fastcall GetFont();
	System::Uitypes::TAlphaColor __fastcall GetFontColor();
	virtual System::UnicodeString __fastcall GetText();
	Fmx::Types::TTextAlign __fastcall GetTextAlign();
	Fmx::Types::TTextAlign __fastcall GetVertTextAlign();
	bool __fastcall GetWordWrap();
	void __fastcall SetFont(Fmx::Graphics::TFont* const Value);
	void __fastcall SetFontColor(const System::Uitypes::TAlphaColor Value);
	virtual void __fastcall SetText(const System::UnicodeString Value);
	void __fastcall SetTextAlign(const Fmx::Types::TTextAlign Value);
	void __fastcall SetVertTextAlign(const Fmx::Types::TTextAlign Value);
	void __fastcall SetWordWrap(const bool Value);
	
protected:
	virtual Fmx::Controls::TTextControl* __fastcall CurrentTextControl() = 0 ;
	virtual Fmx::Controls::TStyledControl* __fastcall CurrentStyledControl();
	
public:
	__property Fmx::Graphics::TFont* Font = {read=GetFont, write=SetFont};
	__property System::Uitypes::TAlphaColor FontColor = {read=GetFontColor, write=SetFontColor, nodefault};
	__property System::UnicodeString Text = {read=GetText, write=SetText};
	__property Fmx::Types::TTextAlign VertTextAlign = {read=GetVertTextAlign, write=SetVertTextAlign, nodefault};
	__property Fmx::Types::TTextAlign TextAlign = {read=GetTextAlign, write=SetTextAlign, nodefault};
	__property bool WordWrap = {read=GetWordWrap, write=SetWordWrap, nodefault};
public:
	/* TObject.Create */ inline __fastcall TTextControlEditorObject() : TStyledControlEditorObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTextControlEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListBoxItemData : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TBindListListItemEditorObject* FEditorObject;
	System::Rtti::TValue __fastcall GetAccessory();
	Fmx::Graphics::TBitmap* __fastcall GetBitmap();
	System::UnicodeString __fastcall GetDetail();
	System::UnicodeString __fastcall GetText();
	void __fastcall SetAccessory(const System::Rtti::TValue &Value);
	void __fastcall SetBitmap(Fmx::Graphics::TBitmap* const Value);
	void __fastcall SetDetail(const System::UnicodeString Value);
	void __fastcall SetText(const System::UnicodeString Value);
	
public:
	__fastcall TBindListBoxItemData(TBindListListItemEditorObject* AEditorObject);
	__property System::UnicodeString Text = {read=GetText, write=SetText};
	__property System::UnicodeString Detail = {read=GetDetail, write=SetDetail};
	__property System::Rtti::TValue Accessory = {read=GetAccessory, write=SetAccessory};
	__property Fmx::Graphics::TBitmap* Bitmap = {read=GetBitmap, write=SetBitmap};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindListBoxItemData() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListListItemEditorObject : public TTextControlEditorObject
{
	typedef TTextControlEditorObject inherited;
	
private:
	int FItemIndex;
	TBindListBoxItemData* FListBoxItemData;
	bool __fastcall GetIsChecked();
	bool __fastcall GetIsSelected();
	void __fastcall SetIsChecked(const bool Value);
	void __fastcall SetIsSelected(const bool Value);
	HIDESBASE System::TObject* __fastcall GetData();
	HIDESBASE void __fastcall SetData(System::TObject* const Value);
	TBindListBoxItemData* __fastcall GetItemData();
	int __fastcall GetImageIndex();
	void __fastcall SetImageIndex(int Value);
	
protected:
	virtual Fmx::Controls::TTextControl* __fastcall CurrentTextControl();
	virtual Fmx::Listbox::TListBoxItem* __fastcall CurrentItem() = 0 ;
	
public:
	__fastcall virtual ~TBindListListItemEditorObject();
	__property System::TObject* Data = {read=GetData, write=SetData};
	__property bool IsChecked = {read=GetIsChecked, write=SetIsChecked, nodefault};
	__property bool IsSelected = {read=GetIsSelected, write=SetIsSelected, nodefault};
	__property int ImageIndex = {read=GetImageIndex, write=SetImageIndex, nodefault};
	__property TBindListBoxItemData* ItemData = {read=GetItemData};
public:
	/* TObject.Create */ inline __fastcall TBindListListItemEditorObject() : TTextControlEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListListBoxEditorObject : public TBindListListItemEditorObject
{
	typedef TBindListListItemEditorObject inherited;
	
private:
	Fmx::Listbox::TCustomListBox* FListBox;
	
protected:
	virtual Fmx::Listbox::TListBoxItem* __fastcall CurrentItem();
	virtual bool __fastcall CheckRange();
public:
	/* TBindListListItemEditorObject.Destroy */ inline __fastcall virtual ~TBindListListBoxEditorObject() { }
	
public:
	/* TObject.Create */ inline __fastcall TBindListListBoxEditorObject() : TBindListListItemEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListViewLookupEditorImpl : public Data::Bind::Editors::TBindListLookupEditor
{
	typedef Data::Bind::Editors::TBindListLookupEditor inherited;
	
	
protected:
	typedef int TLookupKey;
	
	
private:
	int FCurrentKey;
	System::Generics::Collections::TDictionary__2<int,System::Rtti::TValue>* FLookupDictionary;
	int __fastcall FindLookupValue(const System::Rtti::TValue &AValue);
	bool __fastcall SameValue(const System::Rtti::TValue &AValue1, const System::Rtti::TValue &AValue2);
	
protected:
	int __fastcall NextKey();
	void __fastcall ListCleared();
	void __fastcall ItemRemoved(int AListItem);
	virtual int __fastcall GetLookupKey(System::TObject* AListItemObject) = 0 ;
	virtual int __fastcall GetSelected() = 0 ;
	virtual int __fastcall ListCount() = 0 ;
	virtual int __fastcall GetListItem(int I) = 0 ;
	virtual void __fastcall SetSelected(int ALookupKey) = 0 ;
	virtual System::Rtti::TValue __fastcall GetLookupValue(const System::Bindings::Evalprotocol::_di_IScope AScope);
	virtual void __fastcall SetLookupValue(const System::Bindings::Evalprotocol::_di_IScope AScope, const System::Rtti::TValue &AValue);
	virtual System::Rtti::TValue __fastcall GetSelectedLookupValue();
	virtual void __fastcall SetSelectedLookupValue(const System::Rtti::TValue &AValue);
	
public:
	__fastcall virtual ~TBindListViewLookupEditorImpl();
public:
	/* TObject.Create */ inline __fastcall TBindListViewLookupEditorImpl() : Data::Bind::Editors::TBindListLookupEditor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListViewEditor : public TBindListViewLookupEditorImpl
{
	typedef TBindListViewLookupEditorImpl inherited;
	
	
private:
	typedef int TLookupKey;
	
	
private:
	int FUpdateCounter;
	TListViewItemEditorObject* FEditorObject;
	bool FApplyFilter;
	bool __fastcall IsFiltered();
	bool __fastcall IsGrouped();
	void __fastcall SetCurrentValue(const System::UnicodeString AMemberName, const System::Rtti::TValue &AValue, Data::Bind::Components::TScopeMemberType AType);
	bool __fastcall CanSetCurrentValue(const System::UnicodeString AMemberName, /* out */ Data::Bind::Components::TScopeMemberType &AType);
	
protected:
	virtual bool __fastcall RefreshNeeded(Data::Bind::Components::_di_IScopeRecordEnumerator ARecordEnumerator);
	virtual int __fastcall GetLookupKey(System::TObject* AListItemObject);
	virtual int __fastcall GetSelected();
	virtual int __fastcall ListCount();
	virtual int __fastcall GetListItem(int I);
	virtual void __fastcall SetSelected(int ALookupKey);
	virtual void __fastcall GetItemMemberNames(System::Classes::TStrings* ANames);
	virtual System::UnicodeString __fastcall GetItemMemberNameExpression(const System::UnicodeString AName);
	virtual void __fastcall GetHeaderMemberNames(System::Classes::TStrings* ANames);
	virtual System::UnicodeString __fastcall GetHeaderMemberNameExpression(const System::UnicodeString AName);
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall CurrentHeaderItem();
	virtual int __fastcall CurrentIndex();
	virtual System::TObject* __fastcall CurrentObject();
	int __fastcall GetSynchIndex();
	void __fastcall SetSynchIndex(int AIndex);
	void __fastcall ApplyFilter();
	virtual int __fastcall GetItemIndex();
	virtual void __fastcall SetItemIndex(int AIndex);
	virtual bool __fastcall GetPositionGetter(System::UnicodeString &AGetter, int &ABase);
	virtual bool __fastcall GetPositionSetter(System::UnicodeString &ASetter, int &ABase);
	
public:
	__fastcall TBindListViewEditor(Fmx::Listview::TCustomListView* AListView);
	__fastcall virtual ~TBindListViewEditor();
	virtual void __fastcall BeginUpdate();
	virtual void __fastcall EndUpdate();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall AddItem(bool Select);
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall AddHeader();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall InsertItem(bool Select);
	virtual bool __fastcall CanInsertItem();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall CurrentItem();
	virtual int __fastcall GetRowCount();
	virtual bool __fastcall MoveNext();
	virtual void __fastcall DeleteToEnd();
	virtual void __fastcall ClearList();
	virtual System::UnicodeString __fastcall GetSelectedText();
	virtual void __fastcall SetSelectedText(const System::UnicodeString AValue);
private:
	void *__IBindListEditorEvalShortcut;	// Data::Bind::Components::IBindListEditorEvalShortcut 
	void *__IBindListSynchEditor;	// Data::Bind::Components::IBindListSynchEditor 
	void *__IBindListGroupEditor;	// Data::Bind::Components::IBindListGroupEditor 
	void *__IBindFillControlMembers;	// Data::Bind::Components::IBindFillControlMembers 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B3E7381A-559C-479B-B867-92FDACFDFD34}
	operator Data::Bind::Components::_di_IBindListEditorEvalShortcut()
	{
		Data::Bind::Components::_di_IBindListEditorEvalShortcut intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListEditorEvalShortcut*(void) { return (Data::Bind::Components::IBindListEditorEvalShortcut*)&__IBindListEditorEvalShortcut; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B6F0F4F3-EDF7-44F6-A466-32F439B9E3EA}
	operator Data::Bind::Components::_di_IBindListSynchEditor()
	{
		Data::Bind::Components::_di_IBindListSynchEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListSynchEditor*(void) { return (Data::Bind::Components::IBindListSynchEditor*)&__IBindListSynchEditor; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {788EB4F3-AA8F-42EA-AD73-B5A5B1D90A49}
	operator Data::Bind::Components::_di_IBindListGroupEditor()
	{
		Data::Bind::Components::_di_IBindListGroupEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListGroupEditor*(void) { return (Data::Bind::Components::IBindListGroupEditor*)&__IBindListGroupEditor; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {85AD494A-E7ED-402A-90FF-4F9B485B209C}
	operator Data::Bind::Components::_di_IBindFillControlMembers()
	{
		Data::Bind::Components::_di_IBindFillControlMembers intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindFillControlMembers*(void) { return (Data::Bind::Components::IBindFillControlMembers*)&__IBindFillControlMembers; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TItemIndexType : unsigned char { Active, Unfiltered };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TListViewItemEditorObject : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FItemIndex;
	TItemIndexType FIndexType;
	
private:
	Fmx::Listview::TCustomListView* FListView;
	Fmx::Listview::TCustomListView* __fastcall GetOwner();
	void __fastcall SetText(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetText();
	Fmx::Listview::Appearances::TListViewItem* __fastcall CurrentItem();
	NativeInt __fastcall GetTag();
	void __fastcall SetTag(NativeInt Value);
	bool __fastcall CheckRange();
	Fmx::Graphics::TBitmap* __fastcall GetBitmap();
	System::UnicodeString __fastcall GetDetail();
	void __fastcall SetBitmap(Fmx::Graphics::TBitmap* const Value);
	void __fastcall SetDetail(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetButtonText();
	void __fastcall SetButtonText(const System::UnicodeString Value);
	bool __fastcall GetChecked();
	void __fastcall SetChecked(const bool Value);
	System::Rtti::TValue __fastcall GetData(const System::UnicodeString AIndex);
	void __fastcall SetData(const System::UnicodeString AIndex, const System::Rtti::TValue &Value);
	void __fastcall SetItemIndex(int AIndex, TItemIndexType AIndexType = (TItemIndexType)(0x0));
	int __fastcall GetItemIndex();
	int __fastcall GetImageIndex();
	void __fastcall SetImageIndex(int Value);
	
public:
	__property System::UnicodeString Text = {read=GetText, write=SetText};
	__property System::UnicodeString Detail = {read=GetDetail, write=SetDetail};
	__property System::UnicodeString ButtonText = {read=GetButtonText, write=SetButtonText};
	__property Fmx::Graphics::TBitmap* Bitmap = {read=GetBitmap, write=SetBitmap};
	__property Fmx::Listview::TCustomListView* Owner = {read=GetOwner};
	__property bool Checked = {read=GetChecked, write=SetChecked, nodefault};
	__property Fmx::Listview::Appearances::TListViewItem* Item = {read=CurrentItem};
	__property int ImageIndex = {read=GetImageIndex, write=SetImageIndex, nodefault};
	__property System::Rtti::TValue Data[const System::UnicodeString AIndex] = {read=GetData, write=SetData};
#ifndef _WIN64
	__property NativeInt Tag = {read=GetTag, write=SetTag, nodefault};
#else /* _WIN64 */
	__property NativeInt Tag = {read=GetTag, write=SetTag};
#endif /* _WIN64 */
public:
	/* TObject.Create */ inline __fastcall TListViewItemEditorObject() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TListViewItemEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListMetroListBoxEditorObject : public TBindListListBoxEditorObject
{
	typedef TBindListListBoxEditorObject inherited;
	
private:
	System::UnicodeString __fastcall GetDescription();
	Fmx::Graphics::TBitmap* __fastcall GetIcon();
	int __fastcall GetIconSize();
	System::UnicodeString __fastcall GetSubTitle();
	System::UnicodeString __fastcall GetTitle();
	void __fastcall SetDescription(const System::UnicodeString Value);
	void __fastcall SetIcon(Fmx::Graphics::TBitmap* const Value);
	void __fastcall SetIconSize(const int Value);
	void __fastcall SetSubTitle(const System::UnicodeString Value);
	void __fastcall SetTitle(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetText();
	virtual void __fastcall SetText(const System::UnicodeString Value);
	
protected:
	HIDESBASE Fmx::Listbox::TMetropolisUIListBoxItem* __fastcall CurrentItem();
	
public:
	__property System::UnicodeString Title = {read=GetTitle, write=SetTitle};
	__property System::UnicodeString SubTitle = {read=GetSubTitle, write=SetSubTitle};
	__property System::UnicodeString Description = {read=GetDescription, write=SetDescription};
	__property Fmx::Graphics::TBitmap* Icon = {read=GetIcon, write=SetIcon};
	__property int IconSize = {read=GetIconSize, write=SetIconSize, nodefault};
public:
	/* TBindListListItemEditorObject.Destroy */ inline __fastcall virtual ~TBindListMetroListBoxEditorObject() { }
	
public:
	/* TObject.Create */ inline __fastcall TBindListMetroListBoxEditorObject() : TBindListListBoxEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListComboBoxEditorObject : public TBindListListItemEditorObject
{
	typedef TBindListListItemEditorObject inherited;
	
private:
	Fmx::Listbox::TCustomComboBox* FComboBox;
	
protected:
	virtual Fmx::Listbox::TListBoxItem* __fastcall CurrentItem();
	virtual bool __fastcall CheckRange();
public:
	/* TBindListListItemEditorObject.Destroy */ inline __fastcall virtual ~TBindListComboBoxEditorObject() { }
	
public:
	/* TObject.Create */ inline __fastcall TBindListComboBoxEditorObject() : TBindListListItemEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListMetroComboBoxEditorObject : public TBindListComboBoxEditorObject
{
	typedef TBindListComboBoxEditorObject inherited;
	
private:
	System::UnicodeString __fastcall GetDescription();
	Fmx::Graphics::TBitmap* __fastcall GetIcon();
	int __fastcall GetIconSize();
	System::UnicodeString __fastcall GetSubTitle();
	System::UnicodeString __fastcall GetTitle();
	void __fastcall SetDescription(const System::UnicodeString Value);
	void __fastcall SetIcon(Fmx::Graphics::TBitmap* const Value);
	void __fastcall SetIconSize(const int Value);
	void __fastcall SetSubTitle(const System::UnicodeString Value);
	void __fastcall SetTitle(const System::UnicodeString Value);
	
protected:
	HIDESBASE Fmx::Listbox::TMetropolisUIListBoxItem* __fastcall CurrentItem();
	
public:
	__property System::UnicodeString Title = {read=GetTitle, write=SetTitle};
	__property System::UnicodeString SubTitle = {read=GetSubTitle, write=SetSubTitle};
	__property System::UnicodeString Description = {read=GetDescription, write=SetDescription};
	__property Fmx::Graphics::TBitmap* Icon = {read=GetIcon, write=SetIcon};
	__property int IconSize = {read=GetIconSize, write=SetIconSize, nodefault};
public:
	/* TBindListListItemEditorObject.Destroy */ inline __fastcall virtual ~TBindListMetroComboBoxEditorObject() { }
	
public:
	/* TObject.Create */ inline __fastcall TBindListMetroComboBoxEditorObject() : TBindListComboBoxEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListListBoxEditor : public TBindListLookupEditorImpl
{
	typedef TBindListLookupEditorImpl inherited;
	
private:
	TBindListListBoxEditorObject* FEditorObject;
	int FUpdateCounter;
	void __fastcall SetCurrentValue(const System::UnicodeString AMemberName, const System::Rtti::TValue &AValue, Data::Bind::Components::TScopeMemberType AType);
	bool __fastcall CanSetCurrentValue(const System::UnicodeString AMemberName, /* out */ Data::Bind::Components::TScopeMemberType &AType);
	
protected:
	virtual Fmx::Listbox::TListBoxItem* __fastcall GetSelected();
	virtual int __fastcall ListCount();
	virtual Fmx::Listbox::TListBoxItem* __fastcall GetListItem(int I);
	virtual void __fastcall SetSelected(Fmx::Listbox::TListBoxItem* AListItem);
	virtual Fmx::Listbox::TListBoxItem* __fastcall CreateItem();
	virtual TBindListListBoxEditorObject* __fastcall CreateEditorObject();
	virtual int __fastcall GetItemIndex();
	virtual void __fastcall SetItemIndex(int AIndex);
	virtual void __fastcall GetItemMemberNames(System::Classes::TStrings* ANames);
	virtual System::UnicodeString __fastcall GetItemMemberNameExpression(const System::UnicodeString AName);
	virtual void __fastcall GetHeaderMemberNames(System::Classes::TStrings* ANames);
	virtual System::UnicodeString __fastcall GetHeaderMemberNameExpression(const System::UnicodeString AName);
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall CurrentHeaderItem();
	
public:
	__fastcall TBindListListBoxEditor(Fmx::Listbox::TCustomListBox* AListBox);
	__fastcall virtual ~TBindListListBoxEditor();
	virtual void __fastcall BeginUpdate();
	virtual void __fastcall EndUpdate();
	virtual void __fastcall DeleteToEnd();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall AddItem(bool Select);
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall AddHeader();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall InsertItem(bool Select);
	virtual bool __fastcall CanInsertItem();
	virtual bool __fastcall MoveNext();
	virtual int __fastcall GetRowCount();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall CurrentItem();
	virtual void __fastcall ClearList();
	virtual System::UnicodeString __fastcall GetSelectedText();
	virtual void __fastcall SetSelectedText(const System::UnicodeString AValue);
	virtual System::TObject* __fastcall GetSelectedItem();
	virtual System::TObject* __fastcall CurrentObject();
	virtual int __fastcall CurrentIndex();
private:
	void *__IBindListEditorEvalShortcut;	// Data::Bind::Components::IBindListEditorEvalShortcut 
	void *__IBindListGroupEditor;	// Data::Bind::Components::IBindListGroupEditor 
	void *__IBindFillControlMembers;	// Data::Bind::Components::IBindFillControlMembers 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B3E7381A-559C-479B-B867-92FDACFDFD34}
	operator Data::Bind::Components::_di_IBindListEditorEvalShortcut()
	{
		Data::Bind::Components::_di_IBindListEditorEvalShortcut intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListEditorEvalShortcut*(void) { return (Data::Bind::Components::IBindListEditorEvalShortcut*)&__IBindListEditorEvalShortcut; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {788EB4F3-AA8F-42EA-AD73-B5A5B1D90A49}
	operator Data::Bind::Components::_di_IBindListGroupEditor()
	{
		Data::Bind::Components::_di_IBindListGroupEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListGroupEditor*(void) { return (Data::Bind::Components::IBindListGroupEditor*)&__IBindListGroupEditor; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {85AD494A-E7ED-402A-90FF-4F9B485B209C}
	operator Data::Bind::Components::_di_IBindFillControlMembers()
	{
		Data::Bind::Components::_di_IBindFillControlMembers intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindFillControlMembers*(void) { return (Data::Bind::Components::IBindFillControlMembers*)&__IBindFillControlMembers; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListMetroListBoxEditor : public TBindListListBoxEditor
{
	typedef TBindListListBoxEditor inherited;
	
protected:
	virtual Fmx::Listbox::TListBoxItem* __fastcall CreateItem();
	virtual TBindListListBoxEditorObject* __fastcall CreateEditorObject();
	virtual void __fastcall GetItemMemberNames(System::Classes::TStrings* ANames);
	virtual System::UnicodeString __fastcall GetItemMemberNameExpression(const System::UnicodeString AName);
public:
	/* TBindListListBoxEditor.Create */ inline __fastcall TBindListMetroListBoxEditor(Fmx::Listbox::TCustomListBox* AListBox) : TBindListListBoxEditor(AListBox) { }
	/* TBindListListBoxEditor.Destroy */ inline __fastcall virtual ~TBindListMetroListBoxEditor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListItemDataListBoxEditor : public TBindListListBoxEditor
{
	typedef TBindListListBoxEditor inherited;
	
protected:
	virtual void __fastcall GetItemMemberNames(System::Classes::TStrings* ANames);
public:
	/* TBindListListBoxEditor.Create */ inline __fastcall TBindListItemDataListBoxEditor(Fmx::Listbox::TCustomListBox* AListBox) : TBindListListBoxEditor(AListBox) { }
	/* TBindListListBoxEditor.Destroy */ inline __fastcall virtual ~TBindListItemDataListBoxEditor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListComboBoxEditor : public TBindListLookupEditorImpl
{
	typedef TBindListLookupEditorImpl inherited;
	
private:
	TBindListComboBoxEditorObject* FEditorObject;
	int FUpdateCounter;
	void __fastcall SetCurrentValue(const System::UnicodeString AMemberName, const System::Rtti::TValue &AValue, Data::Bind::Components::TScopeMemberType AType);
	bool __fastcall CanSetCurrentValue(const System::UnicodeString AMemberName, /* out */ Data::Bind::Components::TScopeMemberType &AType);
	
protected:
	virtual Fmx::Listbox::TListBoxItem* __fastcall CreateItem();
	virtual TBindListComboBoxEditorObject* __fastcall CreateEditorObject();
	virtual void __fastcall BeginUpdate();
	virtual void __fastcall EndUpdate();
	virtual void __fastcall DeleteToEnd();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall AddItem(bool Select);
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall InsertItem(bool Select);
	virtual bool __fastcall CanInsertItem();
	virtual bool __fastcall MoveNext();
	virtual int __fastcall GetRowCount();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall CurrentItem();
	virtual void __fastcall ClearList();
	virtual System::UnicodeString __fastcall GetSelectedText();
	virtual System::TObject* __fastcall GetSelectedItem();
	virtual void __fastcall SetSelectedText(const System::UnicodeString AValue);
	virtual void __fastcall GetItemMemberNames(System::Classes::TStrings* ANames);
	virtual System::UnicodeString __fastcall GetItemMemberNameExpression(const System::UnicodeString AName);
	virtual int __fastcall GetItemIndex();
	virtual void __fastcall SetItemIndex(int AIndex);
	virtual System::TObject* __fastcall CurrentObject();
	virtual int __fastcall CurrentIndex();
	virtual Fmx::Listbox::TListBoxItem* __fastcall GetSelected();
	virtual int __fastcall ListCount();
	virtual Fmx::Listbox::TListBoxItem* __fastcall GetListItem(int I);
	virtual void __fastcall SetSelected(Fmx::Listbox::TListBoxItem* AListItem);
	
public:
	__fastcall TBindListComboBoxEditor(Fmx::Listbox::TCustomComboBox* AComboBox);
	__fastcall virtual ~TBindListComboBoxEditor();
private:
	void *__IBindListEditorEvalShortcut;	// Data::Bind::Components::IBindListEditorEvalShortcut 
	void *__IBindFillControlMembers;	// Data::Bind::Components::IBindFillControlMembers 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B3E7381A-559C-479B-B867-92FDACFDFD34}
	operator Data::Bind::Components::_di_IBindListEditorEvalShortcut()
	{
		Data::Bind::Components::_di_IBindListEditorEvalShortcut intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListEditorEvalShortcut*(void) { return (Data::Bind::Components::IBindListEditorEvalShortcut*)&__IBindListEditorEvalShortcut; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {85AD494A-E7ED-402A-90FF-4F9B485B209C}
	operator Data::Bind::Components::_di_IBindFillControlMembers()
	{
		Data::Bind::Components::_di_IBindFillControlMembers intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindFillControlMembers*(void) { return (Data::Bind::Components::IBindFillControlMembers*)&__IBindFillControlMembers; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListMetroComboBoxEditor : public TBindListComboBoxEditor
{
	typedef TBindListComboBoxEditor inherited;
	
protected:
	virtual void __fastcall GetItemMemberNames(System::Classes::TStrings* ANames);
	virtual System::UnicodeString __fastcall GetItemMemberNameExpression(const System::UnicodeString AName);
	virtual Fmx::Listbox::TListBoxItem* __fastcall CreateItem();
	virtual TBindListComboBoxEditorObject* __fastcall CreateEditorObject();
public:
	/* TBindListComboBoxEditor.Create */ inline __fastcall TBindListMetroComboBoxEditor(Fmx::Listbox::TCustomComboBox* AComboBox) : TBindListComboBoxEditor(AComboBox) { }
	/* TBindListComboBoxEditor.Destroy */ inline __fastcall virtual ~TBindListMetroComboBoxEditor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListItemDataComboBoxEditor : public TBindListComboBoxEditor
{
	typedef TBindListComboBoxEditor inherited;
	
protected:
	virtual void __fastcall GetItemMemberNames(System::Classes::TStrings* ANames);
public:
	/* TBindListComboBoxEditor.Create */ inline __fastcall TBindListItemDataComboBoxEditor(Fmx::Listbox::TCustomComboBox* AComboBox) : TBindListComboBoxEditor(AComboBox) { }
	/* TBindListComboBoxEditor.Destroy */ inline __fastcall virtual ~TBindListItemDataComboBoxEditor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBaseListBoxItemEditorObject : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	int FIndex;
	virtual System::Classes::TStrings* __fastcall GetControlItems() = 0 ;
	virtual int __fastcall GetControlItemIndex() = 0 ;
	virtual void __fastcall SetControlItemIndex(int AIndex) = 0 ;
	virtual void __fastcall ControlClear() = 0 ;
	
public:
	__property System::Classes::TStrings* ControlItems = {read=GetControlItems};
	__property int ControlItemIndex = {read=GetControlItemIndex, write=SetControlItemIndex, nodefault};
public:
	/* TObject.Create */ inline __fastcall TBaseListBoxItemEditorObject() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBaseListBoxItemEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStringGridItemEditorObject : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Fmx::Grid::TStringGrid* FStringGrid;
	int FIndex;
	Fmx::Grid::TStringGrid* __fastcall GetOwner();
	System::UnicodeString __fastcall GetCells(int ACol);
	void __fastcall SetCells(int ACol, const System::UnicodeString Value);
	
public:
	__property Fmx::Grid::TStringGrid* Owner = {read=GetOwner};
	__property System::UnicodeString Cells[int ACol] = {read=GetCells, write=SetCells};
public:
	/* TObject.Create */ inline __fastcall TStringGridItemEditorObject() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TStringGridItemEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGridItemEditorObject : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Fmx::Grid::TCustomGrid* FGrid;
	Fmx::Grid::TCustomGrid* __fastcall GetOwner();
	
public:
	__property Fmx::Grid::TCustomGrid* Owner = {read=GetOwner};
public:
	/* TObject.Create */ inline __fastcall TGridItemEditorObject() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGridItemEditorObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListStringGridEditor : public Data::Bind::Editors::TBindGridEditor
{
	typedef Data::Bind::Editors::TBindGridEditor inherited;
	
private:
	int FUpdateCounter;
	TStringGridItemEditorObject* FEditorObject;
	int __fastcall GetRowIndex();
	int __fastcall GetColumnIndex();
	void __fastcall SetCurrentValue(const System::UnicodeString AMemberName, const System::Rtti::TValue &AValue, Data::Bind::Components::TScopeMemberType AType);
	bool __fastcall CanSetCurrentValue(const System::UnicodeString AMemberName, /* out */ Data::Bind::Components::TScopeMemberType &AType);
	
protected:
	virtual void __fastcall BeginUpdate();
	virtual void __fastcall EndUpdate();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall AddItem(bool Select);
	virtual bool __fastcall CanInsertItem();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall InsertItem(bool Select);
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall CurrentItem();
	virtual int __fastcall GetRowCount();
	virtual bool __fastcall MoveNext();
	virtual void __fastcall DeleteToEnd();
	virtual void __fastcall ClearList();
	virtual System::UnicodeString __fastcall GetSelectedText();
	virtual void __fastcall SetSelectedText(const System::UnicodeString AValue);
	virtual void __fastcall GetColumnIndices(System::Classes::TStrings* ANames);
	virtual void __fastcall GetColumnNames(System::Classes::TStrings* ANames);
	virtual bool __fastcall GetPositionGetter(System::UnicodeString &AGetter, int &ABase);
	virtual bool __fastcall GetPositionSetter(System::UnicodeString &ASetter, int &ABase);
	virtual void __fastcall SetExpectedRowCount(int ARowCount);
	virtual int __fastcall GetItemIndex();
	virtual void __fastcall SetItemIndex(int AIndex);
	virtual System::TObject* __fastcall CurrentObject();
	virtual int __fastcall CurrentIndex();
	
public:
	__fastcall TBindListStringGridEditor(Fmx::Grid::TStringGrid* AGrid);
	__fastcall virtual ~TBindListStringGridEditor();
private:
	void *__IBindListEditorEvalShortcut;	// Data::Bind::Components::IBindListEditorEvalShortcut 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B3E7381A-559C-479B-B867-92FDACFDFD34}
	operator Data::Bind::Components::_di_IBindListEditorEvalShortcut()
	{
		Data::Bind::Components::_di_IBindListEditorEvalShortcut intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListEditorEvalShortcut*(void) { return (Data::Bind::Components::IBindListEditorEvalShortcut*)&__IBindListEditorEvalShortcut; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TValueCache : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FRow;
	System::Generics::Collections::TDictionary__2<int,System::Rtti::TValue>* FValues;
	
public:
	__fastcall TValueCache();
	void __fastcall Clear()/* overload */;
	void __fastcall Clear(int AColumn)/* overload */;
	void __fastcall Add(int AColumn, int ARow, const System::Rtti::TValue &AValue);
	bool __fastcall TryGet(int AColumn, int ARow, /* out */ System::Rtti::TValue &AValue);
	System::Rtti::TValue __fastcall Get(int AColumn);
	__fastcall virtual ~TValueCache();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListGridEditor : public Data::Bind::Editors::TBindListEditorCommon
{
	typedef Data::Bind::Editors::TBindListEditorCommon inherited;
	
private:
	TValueCache* FValues;
	TGridItemEditorObject* FEditorObject;
	Data::Bind::Components::_di_TBindGridOnCallbackEvaluateFormat FBindGridCallbackEvaluateFormat;
	System::Generics::Collections::TDictionary__2<int,System::TObject*>* FColumnDataObjects;
	int __fastcall GetRowIndex();
	int __fastcall GetColumnIndex();
	void __fastcall GridOnCallbackGetValue(System::TObject* Sender, const int Col, const int Row, System::DelphiInterface<System::Sysutils::TProc__1<System::Rtti::TValue> > ACallback);
	void __fastcall GridOnSetValue(System::TObject* Sender, const int Col, const int Row, const System::Rtti::TValue &Value);
	
protected:
	virtual bool __fastcall GetPositionGetter(System::UnicodeString &AGetter, int &ABase);
	virtual bool __fastcall GetPositionSetter(System::UnicodeString &ASetter, int &ABase);
	void __fastcall SetRowCount(int AValue);
	void __fastcall SetOnCallbackEvaluateFormat(Data::Bind::Components::_di_TBindGridOnCallbackEvaluateFormat AOnCallbackEvaluateFormat);
	void __fastcall UpdateCell(int Col);
	bool __fastcall CanCache();
	virtual void __fastcall BeginUpdate();
	virtual void __fastcall EndUpdate();
	virtual int __fastcall GetRowCount();
	virtual void __fastcall ClearList();
	virtual System::UnicodeString __fastcall GetSelectedText();
	void __fastcall GetColumnNames(System::Classes::TStrings* ANames);
	void __fastcall GetColumnIndices(System::Classes::TStrings* ANames);
	
public:
	__fastcall TBindListGridEditor(Fmx::Grid::TCustomGrid* AGrid);
	__fastcall virtual ~TBindListGridEditor();
private:
	void *__IBindListVirtualEditorScope;	// Data::Bind::Components::IBindListVirtualEditorScope 
	void *__IBindGridEditor;	// Data::Bind::Components::IBindGridEditor 
	void *__IBindListVirtualEditor;	// Data::Bind::Components::IBindListVirtualEditor 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E4E25A70-9D29-4B46-BB7B-E3A07DC676B0}
	operator Data::Bind::Components::_di_IBindListVirtualEditorScope()
	{
		Data::Bind::Components::_di_IBindListVirtualEditorScope intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListVirtualEditorScope*(void) { return (Data::Bind::Components::IBindListVirtualEditorScope*)&__IBindListVirtualEditorScope; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FDE1D9BA-4277-4549-945F-ABFC5E61A56D}
	operator Data::Bind::Components::_di_IBindGridEditor()
	{
		Data::Bind::Components::_di_IBindGridEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindGridEditor*(void) { return (Data::Bind::Components::IBindGridEditor*)&__IBindGridEditor; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {826B10CB-AD17-4D60-830C-7912B6ED6712}
	operator Data::Bind::Components::_di_IBindListVirtualEditor()
	{
		Data::Bind::Components::_di_IBindListVirtualEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListVirtualEditor*(void) { return (Data::Bind::Components::IBindListVirtualEditor*)&__IBindListVirtualEditor; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Editors */
}	/* namespace Bind */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_BIND_EDITORS)
using namespace Fmx::Bind::Editors;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_BIND)
using namespace Fmx::Bind;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Bind_EditorsHPP
