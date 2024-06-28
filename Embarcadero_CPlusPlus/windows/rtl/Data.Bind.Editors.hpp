// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Bind.Editors.pas' rev: 34.00 (Windows)

#ifndef Data_Bind_EditorsHPP
#define Data_Bind_EditorsHPP

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
#include <System.Bindings.ObjEval.hpp>
#include <System.Rtti.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Bind
{
namespace Editors
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindListEditorCommon;
class DELPHICLASS TBindListEditor;
class DELPHICLASS TBindListLookupEditor;
class DELPHICLASS TBindCheckBoxEditor;
class DELPHICLASS TBindDateTimeEditEditor;
class DELPHICLASS TBindGridEditor;
class DELPHICLASS TEditors;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListEditorCommon : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	virtual void __fastcall BeginUpdate() = 0 ;
	virtual void __fastcall EndUpdate() = 0 ;
	virtual void __fastcall ClearList() = 0 ;
	virtual System::TObject* __fastcall GetSelectedItem();
	virtual System::Rtti::TValue __fastcall GetSelectedValue();
	virtual System::UnicodeString __fastcall GetSelectedText() = 0 ;
	virtual int __fastcall GetRowCount() = 0 ;
	virtual bool __fastcall GetPositionGetter(System::UnicodeString &AGetter, int &ABase) = 0 ;
	virtual bool __fastcall GetPositionSetter(System::UnicodeString &ASetter, int &ABase) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TBindListEditorCommon() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindListEditorCommon() { }
	
private:
	void *__IBindListEditorCommon;	// Data::Bind::Components::IBindListEditorCommon 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {87465AA0-608E-4CA4-BE36-B808B3895486}
	operator Data::Bind::Components::_di_IBindListEditorCommon()
	{
		Data::Bind::Components::_di_IBindListEditorCommon intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListEditorCommon*(void) { return (Data::Bind::Components::IBindListEditorCommon*)&__IBindListEditorCommon; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListEditor : public TBindListEditorCommon
{
	typedef TBindListEditorCommon inherited;
	
protected:
	virtual void __fastcall FillGroupList(Data::Bind::Components::_di_IScopeRecordEnumerator ARecordEnumerator, Data::Bind::Components::_di_TFormatCallback AFormatProc, Data::Bind::Components::_di_TFormatCallback AFormatHeaderProc, Data::Bind::Components::_di_TQueryBreakCallback AQueryBreakCallback);
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall AddHeader();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall CurrentHeaderItem();
	virtual void __fastcall GetItemMemberNames(System::Classes::TStrings* ANames);
	virtual System::UnicodeString __fastcall GetItemMemberNameExpression(const System::UnicodeString AName);
	virtual void __fastcall GetHeaderMemberNames(System::Classes::TStrings* ANames);
	virtual System::UnicodeString __fastcall GetHeaderMemberNameExpression(const System::UnicodeString AName);
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall AddItem(bool Select = false) = 0 ;
	virtual bool __fastcall CanInsertItem() = 0 ;
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall InsertItem(bool Select = false) = 0 ;
	virtual bool __fastcall MoveNext() = 0 ;
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall CurrentItem() = 0 ;
	virtual void __fastcall DeleteToEnd() = 0 ;
	virtual bool __fastcall UpdateNeeded(Data::Bind::Components::_di_IScopeRecordEnumerator ARecordEnumerator);
	virtual bool __fastcall RefreshNeeded(Data::Bind::Components::_di_IScopeRecordEnumerator ARecordEnumerator);
	virtual void __fastcall UpdateList(Data::Bind::Components::_di_IScopeRecordEnumerator ARecordEnumerator, Data::Bind::Components::_di_TFormatCallback AFormatProc);
	virtual void __fastcall FillList(Data::Bind::Components::_di_IScopeRecordEnumerator ARecordEnumerator, Data::Bind::Components::_di_TFormatCallback AFormatProc);
	virtual void __fastcall SetSelectedText(const System::UnicodeString AValue) = 0 ;
	virtual void __fastcall SetSelectedValue(const System::Rtti::TValue &AValue);
	virtual bool __fastcall GetPositionGetter(System::UnicodeString &AGetter, int &ABase);
	virtual bool __fastcall GetPositionSetter(System::UnicodeString &ASetter, int &ABase);
	virtual void __fastcall SetExpectedRowCount(int ARowCount);
	virtual System::TObject* __fastcall CurrentObject();
	virtual int __fastcall CurrentIndex();
	virtual int __fastcall GetItemIndex();
	virtual void __fastcall SetItemIndex(int AValue);
public:
	/* TObject.Create */ inline __fastcall TBindListEditor() : TBindListEditorCommon() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindListEditor() { }
	
private:
	void *__IBindListItemIndexEditor;	// Data::Bind::Components::IBindListItemIndexEditor 
	void *__IBindListEditorItem;	// Data::Bind::Components::IBindListEditorItem 
	void *__IBindListEditor;	// Data::Bind::Components::IBindListEditor 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A3EBD46C-A2F7-45A2-87FA-8E1CCE9C7601}
	operator Data::Bind::Components::_di_IBindListItemIndexEditor()
	{
		Data::Bind::Components::_di_IBindListItemIndexEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListItemIndexEditor*(void) { return (Data::Bind::Components::IBindListItemIndexEditor*)&__IBindListItemIndexEditor; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6FBB6044-F568-4996-BAA2-CD71F7D1A83E}
	operator Data::Bind::Components::_di_IBindListEditorItem()
	{
		Data::Bind::Components::_di_IBindListEditorItem intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListEditorItem*(void) { return (Data::Bind::Components::IBindListEditorItem*)&__IBindListEditorItem; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C0D3125F-F9E8-4EAE-98CB-AC16D0E7B075}
	operator Data::Bind::Components::_di_IBindListEditor()
	{
		Data::Bind::Components::_di_IBindListEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListEditor*(void) { return (Data::Bind::Components::IBindListEditor*)&__IBindListEditor; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindListLookupEditor : public TBindListEditor
{
	typedef TBindListEditor inherited;
	
private:
	bool FUseLookups;
	
protected:
	bool __fastcall GetUseLookups();
	void __fastcall SetUseLookups(bool AUseLookups);
	virtual System::Rtti::TValue __fastcall GetLookupValue(const System::Bindings::Evalprotocol::_di_IScope AScope) = 0 ;
	virtual void __fastcall SetLookupValue(const System::Bindings::Evalprotocol::_di_IScope AScope, const System::Rtti::TValue &AValue) = 0 ;
	virtual System::Rtti::TValue __fastcall GetSelectedLookupValue() = 0 ;
	virtual void __fastcall SetSelectedLookupValue(const System::Rtti::TValue &AValue) = 0 ;
	virtual void __fastcall SetSelectedValue(const System::Rtti::TValue &AValue);
	virtual System::Rtti::TValue __fastcall GetSelectedValue();
public:
	/* TObject.Create */ inline __fastcall TBindListLookupEditor() : TBindListEditor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindListLookupEditor() { }
	
private:
	void *__IBindListLookupEditor;	// Data::Bind::Components::IBindListLookupEditor 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A70B5726-FF2F-4E6E-A99C-72C73FCF0168}
	operator Data::Bind::Components::_di_IBindListLookupEditor()
	{
		Data::Bind::Components::_di_IBindListLookupEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindListLookupEditor*(void) { return (Data::Bind::Components::IBindListLookupEditor*)&__IBindListLookupEditor; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindCheckBoxEditor : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	virtual Data::Bind::Components::TBindCheckBoxState __fastcall GetState() = 0 ;
	virtual void __fastcall SetState(Data::Bind::Components::TBindCheckBoxState Value) = 0 ;
	virtual bool __fastcall GetAllowGrayed() = 0 ;
	virtual void __fastcall SetAllowGrayed(bool Value) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TBindCheckBoxEditor() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindCheckBoxEditor() { }
	
private:
	void *__IBindCheckBoxEditor;	// Data::Bind::Components::IBindCheckBoxEditor 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {907EB30C-3C04-400C-88FD-3E9FD5EAE761}
	operator Data::Bind::Components::_di_IBindCheckBoxEditor()
	{
		Data::Bind::Components::_di_IBindCheckBoxEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindCheckBoxEditor*(void) { return (Data::Bind::Components::IBindCheckBoxEditor*)&__IBindCheckBoxEditor; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindDateTimeEditEditor : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	virtual bool __fastcall GetIsEmpty() = 0 ;
	virtual void __fastcall SetIsEmpty(bool Value) = 0 ;
	virtual System::TDateTime __fastcall GetDateTime() = 0 ;
	virtual void __fastcall SetDateTime(System::TDateTime ADateTime) = 0 ;
	virtual System::TTime __fastcall GetTime() = 0 ;
	virtual void __fastcall SetTime(System::TTime ADateTime) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TBindDateTimeEditEditor() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindDateTimeEditEditor() { }
	
private:
	void *__IBindTimeEditEditor;	// Data::Bind::Components::IBindTimeEditEditor 
	void *__IBindDateTimeEditEditor;	// Data::Bind::Components::IBindDateTimeEditEditor 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {21F446F9-5C99-47F2-8029-5D7BD0A40563}
	operator Data::Bind::Components::_di_IBindTimeEditEditor()
	{
		Data::Bind::Components::_di_IBindTimeEditEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindTimeEditEditor*(void) { return (Data::Bind::Components::IBindTimeEditEditor*)&__IBindTimeEditEditor; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B94877B1-5DCB-420F-A9E4-D3401C05AF25}
	operator Data::Bind::Components::_di_IBindDateTimeEditEditor()
	{
		Data::Bind::Components::_di_IBindDateTimeEditEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindDateTimeEditEditor*(void) { return (Data::Bind::Components::IBindDateTimeEditEditor*)&__IBindDateTimeEditEditor; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindGridEditor : public TBindListEditor
{
	typedef TBindListEditor inherited;
	
protected:
	virtual void __fastcall GetColumnNames(System::Classes::TStrings* AList) = 0 ;
	virtual void __fastcall GetColumnIndices(System::Classes::TStrings* AList) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TBindGridEditor() : TBindListEditor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindGridEditor() { }
	
private:
	void *__IBindGridEditor;	// Data::Bind::Components::IBindGridEditor 
	
public:
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
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TEditors : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::Classes::TComponent*,System::_di_IInterface>* FDictionary;
	int __fastcall GetCount();
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TEditors(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TEditors();
	void __fastcall Add(System::Classes::TComponent* AComponent, const System::_di_IInterface AEditor);
	HIDESBASE void __fastcall Remove(System::Classes::TComponent* AComponent);
	bool __fastcall TryGetValue(System::Classes::TComponent* AComponent, /* out */ System::_di_IInterface &AEditor);
	bool __fastcall ReleaseEditor(const System::_di_IInterface AEditor);
	__property int Count = {read=GetCount, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall IsLinkFillControl(System::Classes::TComponent* AComponent)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsLinkFillControl(System::Classes::TComponent* AComponent, /* out */ bool &ALookupControl)/* overload */;
}	/* namespace Editors */
}	/* namespace Bind */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND_EDITORS)
using namespace Data::Bind::Editors;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND)
using namespace Data::Bind;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_Bind_EditorsHPP
