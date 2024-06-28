// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Bind.ObjectScope.pas' rev: 34.00 (iOS)

#ifndef Data_Bind_ObjectscopeHPP
#define Data_Bind_ObjectscopeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <Data.Bind.Components.hpp>
#include <System.Bindings.CustomScope.hpp>
#include <System.Rtti.hpp>
#include <System.TypInfo.hpp>
#include <System.Bindings.Expression.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
namespace Data
{
namespace Bind
{
namespace Objectscope
{
  _INIT_UNIT(Data_Bind_Objectscope);
}	/* namespace Objectscope */
}	/* namespace Bind */
}	/* namespace Data */

namespace Data
{
namespace Bind
{
namespace Objectscope
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBaseObjectBindSource;
class DELPHICLASS TBaseObjectBindSourceDelegate;
class DELPHICLASS TCustomAdapterBindSource;
class DELPHICLASS TAdapterBindSource;
class DELPHICLASS TCustomPrototypeBindSource;
class DELPHICLASS TPrototypeBindSource;
class DELPHICLASS TBindFieldDef;
class DELPHICLASS TBindFieldDefs;
class DELPHICLASS TBindFieldDefWithChildren;
class DELPHICLASS TGeneratorFieldDef;
class DELPHICLASS TGeneratorFieldDefs;
class DELPHICLASS TBindSourceAdapterLink;
__interface DELPHIINTERFACE IGetMemberObject;
typedef System::DelphiInterface<IGetMemberObject> _di_IGetMemberObject;
struct TBindSourceAdapterFieldType;
__interface DELPHIINTERFACE IBindSourceAdapter;
typedef System::DelphiInterface<IBindSourceAdapter> _di_IBindSourceAdapter;
class DELPHICLASS TBindSourceAdapter;
class DELPHICLASS TBaseObjectBindSourceAdapter;
class DELPHICLASS TBindSourceAdapterInstanceFactory;
class DELPHICLASS TBaseListBindSourceAdapter;
template<typename T> class DELPHICLASS TListBindSourceAdapter__1;
class DELPHICLASS TListBindSourceAdapter;
template<typename T> class DELPHICLASS TObjectBindSourceAdapter__1;
class DELPHICLASS TObjectBindSourceAdapter;
class DELPHICLASS TBindSourceAdapterField;
class DELPHICLASS TValueAccessor;
template<typename T> class DELPHICLASS TValueReader__1;
template<typename T> class DELPHICLASS TFieldValueReader__1;
template<typename T> class DELPHICLASS TBindFieldDefValueReader__1;
template<typename T> class DELPHICLASS TBindFieldDefObjectValueReader__1;
template<typename T> class DELPHICLASS TPropertyValueReader__1;
template<typename T> class DELPHICLASS TValueWriter__1;
template<typename T> class DELPHICLASS TFieldValueWriter__1;
template<typename T> class DELPHICLASS TBindFieldDefValueWriter__1;
template<typename T> class DELPHICLASS TBindFieldDefObjectValueWriter__1;
template<typename T> class DELPHICLASS TPropertyValueWriter__1;
template<typename T> class DELPHICLASS TBindSourceAdapterReadField__1;
template<typename T> class DELPHICLASS TBindSourceAdapterReadObjectField__1;
template<typename T> class DELPHICLASS TBindSourceAdapterReadWriteField__1;
template<typename T> class DELPHICLASS TBindSourceAdapterReadWriteObjectField__1;
class DELPHICLASS TBindSourceAdapterReadObjectField;
class DELPHICLASS TBindSourceAdapterCustomScope;
class DELPHICLASS TBindSourceAdapterObjectFieldCustomScope;
class DELPHICLASS TBindSourceAdapterGetMemberObject;
class DELPHICLASS TBindSourceAdapteObjectFieldGetMemberObject;
class DELPHICLASS TGeneratorRecord;
class DELPHICLASS TCustomDataGeneratorAdapter;
class DELPHICLASS TDataGeneratorAdapter;
class DELPHICLASS TValueGenerator;
class DELPHICLASS TValueGeneratorDelegate;
__interface DELPHIINTERFACE TValueGeneratorOnGetValue;
typedef System::DelphiInterface<TValueGeneratorOnGetValue> _di_TValueGeneratorOnGetValue;
class DELPHICLASS TValueGeneratorDelegateWithEvents;
class DELPHICLASS TInternalTypedListValueGeneratorDelegate;
template<typename T> class DELPHICLASS TTypedListValueGeneratorDelegate__1;
template<typename T, typename T1> class DELPHICLASS TTypedListValueGeneratorDelegate2__2;
class DELPHICLASS TDelegateValueGenerator;
struct TValueGeneratorDescription;
class DELPHICLASS TCustomFormatObject;
template<typename T> class DELPHICLASS TTypedCustomFormatObject__1;
template<typename T> class DELPHICLASS TValueReaderFunc__1;
template<typename T> class DELPHICLASS TValueWriterProc__1;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TCreateAdapterEvent)(System::TObject* Sender, TBindSourceAdapter* &ABindSourceAdapter);

class PASCALIMPLEMENTATION TBaseObjectBindSource : public Data::Bind::Components::TBaseLinkingBindSource
{
	typedef Data::Bind::Components::TBaseLinkingBindSource inherited;
	
private:
	TBindSourceAdapter* FConnectedAdapter;
	TBindSourceAdapterLink* FDataLink;
	System::Generics::Collections::TDictionary__2<Data::Bind::Components::TBasicBindComponent*,TBindSourceAdapterLink*>* FAdapterLinks;
	Data::Bind::Components::TBindEventList* FActiveChanged;
	Data::Bind::Components::TBindEventList* FDataSetChanged;
	Data::Bind::Components::TBindEventList* FEditingChanged;
	Data::Bind::Components::TBindEventList1__1<int>* FDataSetScrolled;
	bool FAutoActivate;
	bool FDeferActivate;
	TCreateAdapterEvent FOnCreateAdapter;
	TBindSourceAdapter* FRuntimeAdapter;
	bool FCheckRuntimeAdapter;
	bool FAutoEdit;
	void __fastcall SetAutoActivate(const bool Value);
	void __fastcall SetItemIndex(const int Value);
	int __fastcall GetItemIndex();
	void __fastcall GetRowMember(int ARow, const System::UnicodeString AMemberName, System::DelphiInterface<System::Sysutils::TProc__1<System::TObject*> > ACallback);
	System::Rtti::TValue __fastcall AdapterLookup(const System::UnicodeString KeyFields, const System::Rtti::TValue &KeyValues, const System::UnicodeString ResultFields);
	bool __fastcall AdapterLocate(const System::UnicodeString KeyFields, const System::Rtti::TValue &KeyValues);
	bool __fastcall AdapterFindValues(Data::Bind::Components::_di_IScopeRecordEnumerator LEnumerator, const System::UnicodeString KeyFields, const System::Rtti::TValue &KeyValues, System::DelphiInterface<System::Sysutils::TProc__2<int,System::Rtti::TValue> > AProc);
	
protected:
	virtual void __fastcall UpdateAdapterChanged();
	virtual void __fastcall UpdateAdapterChanging();
	void __fastcall SetInternalAdapter(TBindSourceAdapter* const Value, System::DelphiInterface<System::Sysutils::TProc__1<TBindSourceAdapter*> > AAssignProc);
	bool __fastcall CheckRuntimeAdapter();
	TBindSourceAdapter* __fastcall GetRuntimeAdapter();
	void __fastcall ConnectAdapter(TBindSourceAdapter* AAdapter);
	void __fastcall DisconnectAdapter(TBindSourceAdapter* AAdapter);
	void __fastcall DoMemberRenamed(const System::UnicodeString CurName, const System::UnicodeString PrevName);
	void __fastcall DoMemberRenaming(const System::UnicodeString CurName, const System::UnicodeString NewName);
	void __fastcall OnAdapterUpdateState(System::TObject* Sender);
	void __fastcall OnAdapterDataSetChanged(System::TObject* Sender);
	void __fastcall OnAdapterDataSetScrolled(System::TObject* Sender, int ADistance);
	void __fastcall OnAdapterEdit(System::TObject* Sender, bool &Allow);
	void __fastcall OnAdapterEditingChanged(System::TObject* Sender);
	void __fastcall OnAdapterLayoutChanged(System::TObject* Sender);
	void __fastcall OnAdapterUpdateRecord(System::TObject* Sender);
	void __fastcall OnAdapterRecordChanged(System::TObject* Sender, TBindSourceAdapterField* AField);
	virtual void __fastcall SetActive(const bool Value);
	virtual bool __fastcall CheckAdapter();
	virtual TBindSourceAdapter* __fastcall GetInternalAdapter();
	virtual void __fastcall SetRuntimeAdapter(TBindSourceAdapter* AAdapter);
	virtual System::TObject* __fastcall GetValue();
	virtual System::TObject* __fastcall GetMember(const System::UnicodeString AMemberName);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall Loaded();
	virtual void __fastcall AddExpression(Data::Bind::Components::TBasicBindComponent* AExpression);
	virtual void __fastcall RemoveExpression(Data::Bind::Components::TBasicBindComponent* AExpression);
	virtual bool __fastcall Edit(Data::Bind::Components::TBasicBindComponent* ABindComp)/* overload */;
	virtual bool __fastcall GetIsEditing(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual void __fastcall SetModified(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual bool __fastcall GetIsModified(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual bool __fastcall GetCanModify(Data::Bind::Components::TBasicBindComponent* ABindComp)/* overload */;
	virtual void __fastcall UpdateRecord(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual void __fastcall Reset(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual void __fastcall SetField(Data::Bind::Components::TBasicBindComponent* ABindComp, const System::UnicodeString FieldName);
	virtual void __fastcall SetReadOnly(Data::Bind::Components::TBasicBindComponent* ABindComp, const bool Value);
	virtual void __fastcall ClearModified(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual void __fastcall PosChanging(Data::Bind::Components::TBasicBindComponent* ABindComp);
	HIDESBASE Data::Bind::Components::_di_IScopeRecordEnumerator __fastcall GetEnumerator(const System::UnicodeString AMemberName, int ABufferCount = 0xffffffff);
	virtual bool __fastcall GetBOF();
	virtual bool __fastcall GetEOF();
	virtual bool __fastcall GetSelected();
	virtual bool __fastcall GetActive();
	virtual bool __fastcall GetCanModify()/* overload */;
	virtual bool __fastcall GetCanInsert();
	virtual bool __fastcall GetCanDelete();
	virtual bool __fastcall GetEditing();
	virtual bool __fastcall GetCanRefresh();
	virtual void __fastcall AddActiveChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall RemoveActiveChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall AddEditingChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall RemoveEditingChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall AddDataSetScrolled(Data::Bind::Components::TNotifyDistanceEvent LNotify);
	virtual void __fastcall RemoveDataSetScrolled(Data::Bind::Components::TNotifyDistanceEvent LNotify);
	virtual void __fastcall AddDataSetChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall RemoveDataSetChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList);
	System::Bindings::Evalprotocol::_di_IScope __fastcall GetCurrentRecord(const System::UnicodeString AMemberName);
	bool __fastcall GetMemberGetter(const System::UnicodeString AMemberName, System::UnicodeString &AGetter);
	bool __fastcall GetMemberSetter(const System::UnicodeString AMemberName, System::UnicodeString &ASetter);
	bool __fastcall GetMemberType(const System::UnicodeString AMemberName, Data::Bind::Components::TScopeMemberType &AType);
	bool __fastcall GetPositionGetter(System::UnicodeString &AGetter, int &ABase);
	bool __fastcall GetPositionSetter(System::UnicodeString &ASetter, int &ABase);
	void __fastcall GetRecord(int ARow, const System::UnicodeString AMemberName, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IScope> > ACallback);
	virtual void __fastcall DoCreateAdapter(TBindSourceAdapter* &ADataObject);
	virtual void __fastcall GetLookupMemberNames(System::Classes::TStrings* AList);
	virtual bool __fastcall GetCanApplyUpdates();
	virtual bool __fastcall GetCanCancelUpdates();
	
public:
	virtual bool __fastcall Locate(const System::UnicodeString KeyFields, const System::Rtti::TValue &KeyValues);
	virtual System::Rtti::TValue __fastcall Lookup(const System::UnicodeString KeyFields, const System::Rtti::TValue &KeyValues, const System::UnicodeString ResultFields);
	virtual void __fastcall ApplyUpdates();
	virtual void __fastcall CancelUpdates();
	virtual void __fastcall Next();
	virtual void __fastcall Prior();
	virtual void __fastcall First();
	virtual void __fastcall Last();
	HIDESBASE virtual void __fastcall Insert();
	virtual void __fastcall Delete();
	virtual void __fastcall Cancel();
	virtual void __fastcall Post();
	virtual void __fastcall Edit()/* overload */;
	virtual void __fastcall Refresh();
	virtual bool __fastcall IsValidChar(const System::UnicodeString AFieldName, const System::WideChar AChar);
	virtual bool __fastcall IsRequired(const System::UnicodeString AFieldName);
	virtual System::Classes::_di_IEditFormatLink __fastcall GetFormatLink(const System::UnicodeString AFieldName);
	__property bool Eof = {read=GetEOF, nodefault};
	__property bool BOF = {read=GetBOF, nodefault};
	__property bool CanModify = {read=GetCanModify, nodefault};
	__fastcall virtual TBaseObjectBindSource(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBaseObjectBindSource();
	__property bool Active = {read=GetActive, write=SetActive, default=1};
	__property bool AutoActivate = {read=FAutoActivate, write=SetAutoActivate, nodefault};
	__property int ItemIndex = {read=GetItemIndex, write=SetItemIndex, nodefault};
	__property bool Editing = {read=GetEditing, nodefault};
	__property TCreateAdapterEvent OnCreateAdapter = {read=FOnCreateAdapter, write=FOnCreateAdapter};
	__property System::TObject* Members[const System::UnicodeString AName] = {read=GetMember};
	__property TBindSourceAdapter* InternalAdapter = {read=GetInternalAdapter};
private:
	void *__IScopeLocate;	// Data::Bind::Components::IScopeLocate 
	void *__IScopeNavigatorUpdates;	// Data::Bind::Components::IScopeNavigatorUpdates 
	void *__IScopeLookup;	// Data::Bind::Components::IScopeLookup 
	void *__IScopeGetRecord;	// Data::Bind::Components::IScopeGetRecord 
	void *__IScopeMemberScripting;	// Data::Bind::Components::IScopeMemberScripting 
	void *__IScopeCurrentRecord;	// Data::Bind::Components::IScopeCurrentRecord 
	void *__IScopeMemberNames;	// Data::Bind::Components::IScopeMemberNames 
	void *__IScopeEditor;	// Data::Bind::Components::IScopeEditor 
	void *__IScopeState;	// Data::Bind::Components::IScopeState 
	void *__IScopeNavigator;	// Data::Bind::Components::IScopeNavigator 
	void *__IScopeRecordEnumerable;	// Data::Bind::Components::IScopeRecordEnumerable 
	void *__IScopeEditLink;	// Data::Bind::Components::IScopeEditLink 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CBC0B2CC-0011-4569-B17E-1B5B62BE59CF}
	operator Data::Bind::Components::_di_IScopeLocate()
	{
		Data::Bind::Components::_di_IScopeLocate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeLocate*(void) { return (Data::Bind::Components::IScopeLocate*)&__IScopeLocate; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E48BABC-3939-4326-AD02-B1DF377746C6}
	operator Data::Bind::Components::_di_IScopeNavigatorUpdates()
	{
		Data::Bind::Components::_di_IScopeNavigatorUpdates intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeNavigatorUpdates*(void) { return (Data::Bind::Components::IScopeNavigatorUpdates*)&__IScopeNavigatorUpdates; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95C4149E-E1AD-4D21-A8DF-A84A33B6D2D9}
	operator Data::Bind::Components::_di_IScopeLookup()
	{
		Data::Bind::Components::_di_IScopeLookup intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeLookup*(void) { return (Data::Bind::Components::IScopeLookup*)&__IScopeLookup; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D33C242C-310D-4BE7-9908-C3CAC3C856B6}
	operator Data::Bind::Components::_di_IScopeGetRecord()
	{
		Data::Bind::Components::_di_IScopeGetRecord intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeGetRecord*(void) { return (Data::Bind::Components::IScopeGetRecord*)&__IScopeGetRecord; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3B273E26-19DA-4591-99AF-6748B71ABD3A}
	operator Data::Bind::Components::_di_IScopeMemberScripting()
	{
		Data::Bind::Components::_di_IScopeMemberScripting intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeMemberScripting*(void) { return (Data::Bind::Components::IScopeMemberScripting*)&__IScopeMemberScripting; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {56387EF7-0E9C-4049-AD67-37D0CA60F0D9}
	operator Data::Bind::Components::_di_IScopeActive()
	{
		Data::Bind::Components::_di_IScopeActive intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeActive*(void) { return (Data::Bind::Components::IScopeActive*)&__IScopeState; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5ADA44B4-4E81-401B-9784-3B51D29A5149}
	operator Data::Bind::Components::_di_IScopeCurrentRecord()
	{
		Data::Bind::Components::_di_IScopeCurrentRecord intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeCurrentRecord*(void) { return (Data::Bind::Components::IScopeCurrentRecord*)&__IScopeCurrentRecord; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E6D8BFA3-0453-436B-8434-D10623724644}
	operator Data::Bind::Components::_di_IScopeMemberNames()
	{
		Data::Bind::Components::_di_IScopeMemberNames intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeMemberNames*(void) { return (Data::Bind::Components::IScopeMemberNames*)&__IScopeMemberNames; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F2A94E16-2181-4943-8BDC-3D0CA7FDE336}
	operator Data::Bind::Components::_di_IScopeEditor()
	{
		Data::Bind::Components::_di_IScopeEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeEditor*(void) { return (Data::Bind::Components::IScopeEditor*)&__IScopeEditor; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2B1E1B3F-EBD5-46F0-A611-E5512D49BCFD}
	operator Data::Bind::Components::_di_IScopeState()
	{
		Data::Bind::Components::_di_IScopeState intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeState*(void) { return (Data::Bind::Components::IScopeState*)&__IScopeState; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C71852CF-888A-42C6-9A15-B704E11229D8}
	operator Data::Bind::Components::_di_IScopeNavigator()
	{
		Data::Bind::Components::_di_IScopeNavigator intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeNavigator*(void) { return (Data::Bind::Components::IScopeNavigator*)&__IScopeNavigator; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {34A6773D-A71B-4870-9C60-409A798206FA}
	operator Data::Bind::Components::_di_IScopeRecordEnumerable()
	{
		Data::Bind::Components::_di_IScopeRecordEnumerable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeRecordEnumerable*(void) { return (Data::Bind::Components::IScopeRecordEnumerable*)&__IScopeRecordEnumerable; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {86C2783F-082F-4D78-98A3-CC3540D72A0D}
	operator Data::Bind::Components::_di_IScopeEditLink()
	{
		Data::Bind::Components::_di_IScopeEditLink intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeEditLink*(void) { return (Data::Bind::Components::IScopeEditLink*)&__IScopeEditLink; }
	#endif
	
};


class PASCALIMPLEMENTATION TBaseObjectBindSourceDelegate : public Data::Bind::Components::TBaseLinkingBindSource
{
	typedef Data::Bind::Components::TBaseLinkingBindSource inherited;
	
private:
	TBaseObjectBindSource* FBindSource;
	
protected:
	virtual System::TObject* __fastcall GetValue();
	virtual System::TObject* __fastcall GetMember(const System::UnicodeString AMemberName);
	virtual void __fastcall AddExpression(Data::Bind::Components::TBasicBindComponent* AExpression);
	virtual void __fastcall RemoveExpression(Data::Bind::Components::TBasicBindComponent* AExpression);
	bool __fastcall Edit(Data::Bind::Components::TBasicBindComponent* ABindComp)/* overload */;
	bool __fastcall GetIsEditing(Data::Bind::Components::TBasicBindComponent* ABindComp);
	void __fastcall SetModified(Data::Bind::Components::TBasicBindComponent* ABindComp);
	bool __fastcall GetIsModified(Data::Bind::Components::TBasicBindComponent* ABindComp);
	bool __fastcall GetCanModify(Data::Bind::Components::TBasicBindComponent* ABindComp)/* overload */;
	void __fastcall UpdateRecord(Data::Bind::Components::TBasicBindComponent* ABindComp);
	void __fastcall Reset(Data::Bind::Components::TBasicBindComponent* ABindComp);
	void __fastcall SetField(Data::Bind::Components::TBasicBindComponent* ABindComp, const System::UnicodeString FieldName);
	void __fastcall SetReadOnly(Data::Bind::Components::TBasicBindComponent* ABindComp, const bool Value);
	void __fastcall ClearModified(Data::Bind::Components::TBasicBindComponent* ABindComp);
	void __fastcall PosChanging(Data::Bind::Components::TBasicBindComponent* ABindComp);
	HIDESBASE Data::Bind::Components::_di_IScopeRecordEnumerator __fastcall GetEnumerator(const System::UnicodeString AMemberName, int ABufferCount = 0xffffffff);
	bool __fastcall GetBOF();
	bool __fastcall GetEOF();
	bool __fastcall GetSelected();
	bool __fastcall GetActive();
	bool __fastcall GetCanModify()/* overload */;
	bool __fastcall GetCanInsert();
	bool __fastcall GetCanDelete();
	bool __fastcall GetEditing();
	bool __fastcall GetCanRefresh();
	void __fastcall AddActiveChanged(System::Classes::TNotifyEvent LNotify);
	void __fastcall RemoveActiveChanged(System::Classes::TNotifyEvent LNotify);
	void __fastcall AddEditingChanged(System::Classes::TNotifyEvent LNotify);
	void __fastcall RemoveEditingChanged(System::Classes::TNotifyEvent LNotify);
	void __fastcall AddDataSetScrolled(Data::Bind::Components::TNotifyDistanceEvent LNotify);
	void __fastcall RemoveDataSetScrolled(Data::Bind::Components::TNotifyDistanceEvent LNotify);
	void __fastcall AddDataSetChanged(System::Classes::TNotifyEvent LNotify);
	void __fastcall RemoveDataSetChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList);
	System::Bindings::Evalprotocol::_di_IScope __fastcall GetCurrentRecord(const System::UnicodeString AMemberName);
	bool __fastcall GetMemberGetter(const System::UnicodeString AMemberName, System::UnicodeString &AGetter);
	bool __fastcall GetMemberSetter(const System::UnicodeString AMemberName, System::UnicodeString &ASetter);
	bool __fastcall GetMemberType(const System::UnicodeString AMemberName, Data::Bind::Components::TScopeMemberType &AType);
	bool __fastcall GetPositionGetter(System::UnicodeString &AGetter, int &ABase);
	bool __fastcall GetPositionSetter(System::UnicodeString &ASetter, int &ABase);
	void __fastcall GetRecord(int ARow, const System::UnicodeString AMemberName, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IScope> > ACallback);
	bool __fastcall GetCanApplyUpdates();
	bool __fastcall GetCanCancelUpdates();
	bool __fastcall Locate(const System::UnicodeString KeyFields, const System::Rtti::TValue &KeyValues);
	System::Rtti::TValue __fastcall Lookup(const System::UnicodeString KeyFields, const System::Rtti::TValue &KeyValues, const System::UnicodeString ResultFields);
	void __fastcall GetLookupMemberNames(System::Classes::TStrings* AList);
	void __fastcall ApplyUpdates();
	void __fastcall CancelUpdates();
	void __fastcall Next();
	void __fastcall Prior();
	void __fastcall First();
	void __fastcall Last();
	HIDESBASE void __fastcall Insert();
	void __fastcall Delete();
	void __fastcall Cancel();
	void __fastcall Post();
	void __fastcall Edit()/* overload */;
	void __fastcall Refresh();
	bool __fastcall IsValidChar(const System::UnicodeString AFieldName, const System::WideChar AChar);
	bool __fastcall IsRequired(const System::UnicodeString AFieldName);
	System::Classes::_di_IEditFormatLink __fastcall GetFormatLink(const System::UnicodeString AFieldName);
	virtual TBaseObjectBindSource* __fastcall CreateBindSource() = 0 ;
	
public:
	__fastcall virtual TBaseObjectBindSourceDelegate(System::Classes::TComponent* AOwner);
public:
	/* TBaseBindScopeComponent.Destroy */ inline __fastcall virtual ~TBaseObjectBindSourceDelegate() { }
	
private:
	void *__IScopeLocate;	// Data::Bind::Components::IScopeLocate 
	void *__IScopeNavigatorUpdates;	// Data::Bind::Components::IScopeNavigatorUpdates 
	void *__IScopeLookup;	// Data::Bind::Components::IScopeLookup 
	void *__IScopeGetRecord;	// Data::Bind::Components::IScopeGetRecord 
	void *__IScopeMemberScripting;	// Data::Bind::Components::IScopeMemberScripting 
	void *__IScopeCurrentRecord;	// Data::Bind::Components::IScopeCurrentRecord 
	void *__IScopeMemberNames;	// Data::Bind::Components::IScopeMemberNames 
	void *__IScopeEditor;	// Data::Bind::Components::IScopeEditor 
	void *__IScopeState;	// Data::Bind::Components::IScopeState 
	void *__IScopeNavigator;	// Data::Bind::Components::IScopeNavigator 
	void *__IScopeRecordEnumerable;	// Data::Bind::Components::IScopeRecordEnumerable 
	void *__IScopeEditLink;	// Data::Bind::Components::IScopeEditLink 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CBC0B2CC-0011-4569-B17E-1B5B62BE59CF}
	operator Data::Bind::Components::_di_IScopeLocate()
	{
		Data::Bind::Components::_di_IScopeLocate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeLocate*(void) { return (Data::Bind::Components::IScopeLocate*)&__IScopeLocate; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E48BABC-3939-4326-AD02-B1DF377746C6}
	operator Data::Bind::Components::_di_IScopeNavigatorUpdates()
	{
		Data::Bind::Components::_di_IScopeNavigatorUpdates intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeNavigatorUpdates*(void) { return (Data::Bind::Components::IScopeNavigatorUpdates*)&__IScopeNavigatorUpdates; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95C4149E-E1AD-4D21-A8DF-A84A33B6D2D9}
	operator Data::Bind::Components::_di_IScopeLookup()
	{
		Data::Bind::Components::_di_IScopeLookup intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeLookup*(void) { return (Data::Bind::Components::IScopeLookup*)&__IScopeLookup; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D33C242C-310D-4BE7-9908-C3CAC3C856B6}
	operator Data::Bind::Components::_di_IScopeGetRecord()
	{
		Data::Bind::Components::_di_IScopeGetRecord intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeGetRecord*(void) { return (Data::Bind::Components::IScopeGetRecord*)&__IScopeGetRecord; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3B273E26-19DA-4591-99AF-6748B71ABD3A}
	operator Data::Bind::Components::_di_IScopeMemberScripting()
	{
		Data::Bind::Components::_di_IScopeMemberScripting intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeMemberScripting*(void) { return (Data::Bind::Components::IScopeMemberScripting*)&__IScopeMemberScripting; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {56387EF7-0E9C-4049-AD67-37D0CA60F0D9}
	operator Data::Bind::Components::_di_IScopeActive()
	{
		Data::Bind::Components::_di_IScopeActive intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeActive*(void) { return (Data::Bind::Components::IScopeActive*)&__IScopeState; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5ADA44B4-4E81-401B-9784-3B51D29A5149}
	operator Data::Bind::Components::_di_IScopeCurrentRecord()
	{
		Data::Bind::Components::_di_IScopeCurrentRecord intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeCurrentRecord*(void) { return (Data::Bind::Components::IScopeCurrentRecord*)&__IScopeCurrentRecord; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E6D8BFA3-0453-436B-8434-D10623724644}
	operator Data::Bind::Components::_di_IScopeMemberNames()
	{
		Data::Bind::Components::_di_IScopeMemberNames intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeMemberNames*(void) { return (Data::Bind::Components::IScopeMemberNames*)&__IScopeMemberNames; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F2A94E16-2181-4943-8BDC-3D0CA7FDE336}
	operator Data::Bind::Components::_di_IScopeEditor()
	{
		Data::Bind::Components::_di_IScopeEditor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeEditor*(void) { return (Data::Bind::Components::IScopeEditor*)&__IScopeEditor; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2B1E1B3F-EBD5-46F0-A611-E5512D49BCFD}
	operator Data::Bind::Components::_di_IScopeState()
	{
		Data::Bind::Components::_di_IScopeState intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeState*(void) { return (Data::Bind::Components::IScopeState*)&__IScopeState; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C71852CF-888A-42C6-9A15-B704E11229D8}
	operator Data::Bind::Components::_di_IScopeNavigator()
	{
		Data::Bind::Components::_di_IScopeNavigator intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeNavigator*(void) { return (Data::Bind::Components::IScopeNavigator*)&__IScopeNavigator; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {34A6773D-A71B-4870-9C60-409A798206FA}
	operator Data::Bind::Components::_di_IScopeRecordEnumerable()
	{
		Data::Bind::Components::_di_IScopeRecordEnumerable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeRecordEnumerable*(void) { return (Data::Bind::Components::IScopeRecordEnumerable*)&__IScopeRecordEnumerable; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {86C2783F-082F-4D78-98A3-CC3540D72A0D}
	operator Data::Bind::Components::_di_IScopeEditLink()
	{
		Data::Bind::Components::_di_IScopeEditLink intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeEditLink*(void) { return (Data::Bind::Components::IScopeEditLink*)&__IScopeEditLink; }
	#endif
	
};


class PASCALIMPLEMENTATION TCustomAdapterBindSource : public TBaseObjectBindSource
{
	typedef TBaseObjectBindSource inherited;
	
private:
	TBindSourceAdapter* FAdapter;
	void __fastcall SetAdapter(TBindSourceAdapter* Value);
	
protected:
	virtual TBindSourceAdapter* __fastcall GetInternalAdapter();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual ~TCustomAdapterBindSource();
	__property TBindSourceAdapter* Adapter = {read=FAdapter, write=SetAdapter};
public:
	/* TBaseObjectBindSource.Create */ inline __fastcall virtual TCustomAdapterBindSource(System::Classes::TComponent* AOwner) : TBaseObjectBindSource(AOwner) { }
	
};


class PASCALIMPLEMENTATION TAdapterBindSource : public TCustomAdapterBindSource
{
	typedef TCustomAdapterBindSource inherited;
	
__published:
	__property AutoActivate;
	__property OnCreateAdapter;
	__property Adapter;
	__property ScopeMappings;
public:
	/* TCustomAdapterBindSource.Destroy */ inline __fastcall virtual ~TAdapterBindSource() { }
	
public:
	/* TBaseObjectBindSource.Create */ inline __fastcall virtual TAdapterBindSource(System::Classes::TComponent* AOwner) : TCustomAdapterBindSource(AOwner) { }
	
};


class PASCALIMPLEMENTATION TCustomPrototypeBindSource : public TBaseObjectBindSource
{
	typedef TBaseObjectBindSource inherited;
	
private:
	TCustomDataGeneratorAdapter* FDataGenerator;
	TBindSourceAdapter* FAdapter;
	TGeneratorFieldDefs* __fastcall GetFieldDefs();
	int __fastcall GetRecordCount();
	void __fastcall SetFieldDefs(TGeneratorFieldDefs* const Value);
	void __fastcall SetRecordCount(const int Value);
	void __fastcall SetAutoEdit(const bool Value);
	void __fastcall SetAutoPost(const bool Value);
	bool __fastcall GetAutoEdit();
	bool __fastcall GetAutoPost();
	
protected:
	virtual TBindSourceAdapter* __fastcall GetInternalAdapter();
	
public:
	__fastcall virtual TCustomPrototypeBindSource(System::Classes::TComponent* AOwner);
	__property bool AutoEdit = {read=GetAutoEdit, write=SetAutoEdit, default=1};
	__property bool AutoPost = {read=GetAutoPost, write=SetAutoPost, nodefault};
	__property TGeneratorFieldDefs* FieldDefs = {read=GetFieldDefs, write=SetFieldDefs};
	__property int RecordCount = {read=GetRecordCount, write=SetRecordCount, default=-1};
	__property TCustomDataGeneratorAdapter* DataGenerator = {read=FDataGenerator};
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TCustomPrototypeBindSource() { }
	
};


class PASCALIMPLEMENTATION TPrototypeBindSource : public TCustomPrototypeBindSource
{
	typedef TCustomPrototypeBindSource inherited;
	
__published:
	__property AutoActivate;
	__property AutoEdit = {default=1};
	__property AutoPost;
	__property RecordCount = {default=-1};
	__property FieldDefs;
	__property ScopeMappings;
	__property OnCreateAdapter;
public:
	/* TCustomPrototypeBindSource.Create */ inline __fastcall virtual TPrototypeBindSource(System::Classes::TComponent* AOwner) : TCustomPrototypeBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TPrototypeBindSource() { }
	
};


class PASCALIMPLEMENTATION TBindFieldDef : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	HIDESBASE void __fastcall SetDisplayName(const System::UnicodeString Value);
	static System::UnicodeString __fastcall MakeKey(const System::UnicodeString AName);
	__property System::UnicodeString Name = {read=FName, write=SetDisplayName};
	virtual bool __fastcall HasChildDefs();
	
public:
	__fastcall virtual ~TBindFieldDef();
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TBindFieldDef(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TBindFieldDefClass);

typedef void __fastcall (__closure *TDefUpdateMethod)(void);

class PASCALIMPLEMENTATION TBindFieldDefs : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TBindFieldDef*>* FDictionary;
	System::Classes::TComponent* FDataSource;
	bool FUpdated;
	int FInternalUpdateCount;
	TBindFieldDef* FParentDef;
	template<typename T> T __fastcall SafeCast(System::TObject* AValue);
	
protected:
	virtual void __fastcall DoRenamingFieldDef(TBindFieldDef* AFieldDef, const System::UnicodeString CurName, const System::UnicodeString NewName);
	virtual void __fastcall DoRenameFieldDef(TBindFieldDef* AFieldDef, const System::UnicodeString CurName, const System::UnicodeString PrevName);
	virtual void __fastcall DataSourceFieldDefChanged(System::TObject* Sender) = 0 ;
	virtual void __fastcall DataSourceInitFieldDefs() = 0 ;
	virtual TBindFieldDefs* __fastcall GetDataSourceFieldDefs() = 0 ;
	void __fastcall DoUpdate(System::TObject* Sender);
	virtual void __fastcall SetItemName(System::Classes::TCollectionItem* AItem);
	virtual void __fastcall Update(System::Classes::TCollectionItem* AItem)/* overload */;
	void __fastcall UpdateDefs(TDefUpdateMethod AMethod);
	template<typename T> T __fastcall GetParentDef();
	template<typename T> T __fastcall GetFieldDef(int Index);
	void __fastcall SetFieldDef(int Index, TBindFieldDef* Value);
	void __fastcall FieldDefUpdate(System::TObject* Sender);
	void __fastcall ChildDefUpdate(System::TObject* Sender);
	virtual TBindFieldDefClass __fastcall GetFieldDefClass() = 0 ;
	template<typename T> T __fastcall AddFieldDef();
	template<typename T> T __fastcall Find(const System::UnicodeString Name);
	HIDESBASE void __fastcall Update()/* overload */;
	
public:
	__fastcall virtual TBindFieldDefs(System::Classes::TPersistent* AOwner);
	__fastcall virtual ~TBindFieldDefs();
	void __fastcall GetItemNames(System::Classes::TStrings* List)/* overload */;
	int __fastcall IndexOf(const System::UnicodeString AName);
	__property System::Classes::TComponent* DataSource = {read=FDataSource};
	__property bool Updated = {read=FUpdated, write=FUpdated, nodefault};
};


_DECLARE_METACLASS(System::TMetaClass, TBindFieldDefsClass);

class PASCALIMPLEMENTATION TBindFieldDefWithChildren : public TBindFieldDef
{
	typedef TBindFieldDef inherited;
	
private:
	TBindFieldDefs* FChildDefs;
	
protected:
	template<typename T> T __fastcall GetChildDefs();
	template<typename T> T __fastcall GetParentDef();
	void __fastcall SetChildDefs(TBindFieldDefs* Value);
	virtual TBindFieldDefsClass __fastcall GetChildDefsClass() = 0 ;
	template<typename T> T __fastcall AddChild();
	virtual bool __fastcall HasChildDefs();
	
public:
	__fastcall virtual ~TBindFieldDefWithChildren();
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TBindFieldDefWithChildren(System::Classes::TCollection* Collection) : TBindFieldDef(Collection) { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TGeneratorBindFieldDefsClass);

enum DECLSPEC_DENUM TGeneratorFieldType : unsigned char { ftString, ftInteger, ftSingle, ftBoolean, ftBitmap, ftUInteger, ftCurrency, ftDateTime, ftTStrings, ftDate, ftTime, ftChar };

typedef System::Set<TGeneratorFieldType, TGeneratorFieldType::ftString, TGeneratorFieldType::ftChar> TGeneratorFieldTypes;

enum DECLSPEC_DENUM TGeneratorOption : unsigned char { optShuffle, optRepeat };

typedef System::Set<TGeneratorOption, TGeneratorOption::optShuffle, TGeneratorOption::optRepeat> TGeneratorOptions;

class PASCALIMPLEMENTATION TGeneratorFieldDef : public TBindFieldDefWithChildren
{
	typedef TBindFieldDefWithChildren inherited;
	
private:
	int FFieldNo;
	TGeneratorFieldType FFieldType;
	System::UnicodeString FGenerator;
	bool FReadOnly;
	TGeneratorOptions FOptions;
	System::UnicodeString FCustomFormat;
	HIDESBASE TGeneratorFieldDefs* __fastcall GetChildDefs();
	int __fastcall GetFieldNo();
	HIDESBASE TGeneratorFieldDef* __fastcall GetParentDef();
	HIDESBASE void __fastcall SetChildDefs(TGeneratorFieldDefs* Value);
	void __fastcall SetFieldType(TGeneratorFieldType Value);
	void __fastcall SetGenerator(const System::UnicodeString Value);
	System::Typinfo::PTypeInfo __fastcall GetTypeInfo();
	Data::Bind::Components::TScopeMemberType __fastcall GetMemberType();
	void __fastcall SetReadOnly(const bool Value);
	void __fastcall SetOptions(const TGeneratorOptions Value);
	void __fastcall SetCustomFormat(const System::UnicodeString Value);
	
protected:
	virtual TBindFieldDefsClass __fastcall GetChildDefsClass();
	
public:
	__fastcall virtual TGeneratorFieldDef(System::Classes::TCollection* Collection)/* overload */;
	__fastcall virtual TGeneratorFieldDef(TBindFieldDefs* Owner, const System::UnicodeString Name, int FieldNo)/* overload */;
	HIDESBASE TGeneratorFieldDef* __fastcall AddChild();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property int FieldNo = {read=GetFieldNo, write=FFieldNo, stored=false, nodefault};
	__property TGeneratorFieldDef* ParentDef = {read=GetParentDef};
	__property System::Typinfo::PTypeInfo TypeInfo = {read=GetTypeInfo};
	__property Data::Bind::Components::TScopeMemberType MemberType = {read=GetMemberType, nodefault};
	__property TGeneratorFieldDefs* ChildDefs = {read=GetChildDefs, write=SetChildDefs, stored=HasChildDefs};
	
__published:
	__property Name = {default=0};
	__property TGeneratorFieldType FieldType = {read=FFieldType, write=SetFieldType, default=0};
	__property System::UnicodeString Generator = {read=FGenerator, write=SetGenerator};
	__property TGeneratorOptions Options = {read=FOptions, write=SetOptions, default=3};
	__property bool ReadOnly = {read=FReadOnly, write=SetReadOnly, nodefault};
	__property System::UnicodeString CustomFormat = {read=FCustomFormat, write=SetCustomFormat};
public:
	/* TBindFieldDefWithChildren.Destroy */ inline __fastcall virtual ~TGeneratorFieldDef() { }
	
};


class PASCALIMPLEMENTATION TGeneratorFieldDefs : public TBindFieldDefs
{
	typedef TBindFieldDefs inherited;
	
	
__published:
	typedef Data::Bind::Components::TCollectionEnumerator__1<TGeneratorFieldDef*>* TEnumerator;
	
	
public:
	TGeneratorFieldDef* operator[](int Index) { return this->Items[Index]; }
	
protected:
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	virtual void __fastcall DoRenamingFieldDef(TBindFieldDef* AFieldDef, const System::UnicodeString CurName, const System::UnicodeString NewName);
	virtual void __fastcall DoRenameFieldDef(TBindFieldDef* AFieldDef, const System::UnicodeString CurName, const System::UnicodeString PrevName);
	virtual void __fastcall DataSourceFieldDefChanged(System::TObject* Sender);
	virtual void __fastcall DataSourceInitFieldDefs();
	virtual TBindFieldDefs* __fastcall GetDataSourceFieldDefs();
	virtual TBindFieldDefClass __fastcall GetFieldDefClass();
	HIDESBASE TGeneratorFieldDef* __fastcall GetParentDef();
	HIDESBASE TGeneratorFieldDef* __fastcall GetFieldDef(int Index);
	HIDESBASE void __fastcall SetFieldDef(int Index, TGeneratorFieldDef* Value);
	
public:
	HIDESBASE Data::Bind::Components::TCollectionEnumerator__1<TGeneratorFieldDef*>* __fastcall GetEnumerator();
	HIDESBASE TGeneratorFieldDef* __fastcall AddFieldDef();
	HIDESBASE TGeneratorFieldDef* __fastcall Find(const System::UnicodeString Name);
	__property TGeneratorFieldDef* Items[int Index] = {read=GetFieldDef, write=SetFieldDef/*, default*/};
	__property TGeneratorFieldDef* ParentDef = {read=GetParentDef};
public:
	/* TBindFieldDefs.Create */ inline __fastcall virtual TGeneratorFieldDefs(System::Classes::TPersistent* AOwner) : TBindFieldDefs(AOwner) { }
	/* TBindFieldDefs.Destroy */ inline __fastcall virtual ~TGeneratorFieldDefs() { }
	
};


class PASCALIMPLEMENTATION TBindSourceAdapterLink : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TBindSourceAdapter* FAdapter;
	bool FUpdating;
	bool FActive;
	bool FEditing;
	bool FReadOnly;
	void __fastcall SetAdapter(TBindSourceAdapter* const Value);
	void __fastcall UpdateState();
	void __fastcall SetActive(bool Value);
	void __fastcall SetEditing(bool Value);
	
protected:
	void __fastcall UpdateRecord();
	virtual void __fastcall RecordChanged(TBindSourceAdapterField* Field);
	virtual void __fastcall DataSetChanged();
	virtual void __fastcall DataSetScrolled(int ADistance);
	virtual void __fastcall LayoutChanged();
	virtual void __fastcall ActiveChanged();
	virtual void __fastcall EditingChanged();
	virtual void __fastcall UpdateData();
	virtual bool __fastcall Edit();
	__property bool Active = {read=FActive, nodefault};
	__property TBindSourceAdapter* Adapter = {read=FAdapter, write=SetAdapter};
	__property bool Editing = {read=FEditing, nodefault};
	
public:
	__fastcall TBindSourceAdapterLink();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindSourceAdapterLink() { }
	
};


enum DECLSPEC_DENUM TBindSourceAdapterState : unsigned char { seInactive, seBrowse, seEdit, seInsert };

__interface IGetMemberObject  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetMemberObject() = 0 ;
};

struct DECLSPEC_DRECORD TBindSourceAdapterFieldType
{
private:
	System::TTypeKind FTypeKind;
	System::UnicodeString FTypeName;
	
public:
	__fastcall TBindSourceAdapterFieldType(const System::UnicodeString ATypeName, System::TTypeKind ATypeKind);
	__property System::TTypeKind TypeKind = {read=FTypeKind};
	__property System::UnicodeString TypeName = {read=FTypeName};
	TBindSourceAdapterFieldType() {}
};


__interface  INTERFACE_UUID("{6F63422E-B03D-4308-A536-12F3C5A22931}") IBindSourceAdapter  : public System::IInterface 
{
	virtual void __fastcall Next() = 0 ;
	virtual void __fastcall Prior() = 0 ;
	virtual void __fastcall First() = 0 ;
	virtual void __fastcall Last() = 0 ;
	virtual void __fastcall Insert() = 0 ;
	virtual void __fastcall Append() = 0 ;
	virtual void __fastcall Delete() = 0 ;
	virtual void __fastcall Cancel() = 0 ;
	virtual void __fastcall Post() = 0 ;
	virtual void __fastcall Edit(bool AForce = false) = 0 ;
	virtual void __fastcall ApplyUpdates() = 0 ;
	virtual void __fastcall CancelUpdates() = 0 ;
	virtual bool __fastcall GetEmpty() = 0 ;
	virtual System::TObject* __fastcall GetCurrent() = 0 ;
	virtual int __fastcall GetCount() = 0 ;
	virtual int __fastcall GetItemIndex() = 0 ;
	virtual int __fastcall GetCurrentIndex() = 0 ;
	virtual bool __fastcall GetCanDelete() = 0 ;
	virtual bool __fastcall GetCanInsert() = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual bool __fastcall GetCanModify() = 0 ;
	virtual bool __fastcall GetCanApplyUpdates() = 0 ;
	virtual bool __fastcall GetCanCancelUpdates() = 0 ;
	virtual bool __fastcall GetBOF() = 0 ;
	virtual bool __fastcall GetEOF() = 0 ;
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList) = 0 ;
	virtual void __fastcall GetLookupMemberNames(System::Classes::TStrings* AList) = 0 ;
	virtual void __fastcall SetItemIndex(int AValue) = 0 ;
	virtual void __fastcall SetItemIndexOffset(int AValue) = 0 ;
	virtual int __fastcall GetItemIndexOffset() = 0 ;
	virtual void __fastcall SetActive(bool AValue) = 0 ;
	__property System::TObject* Current = {read=GetCurrent};
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall GetCurrentRecord(const System::UnicodeString AMemberName) = 0 ;
	__property int ItemIndex = {read=GetItemIndex, write=SetItemIndex};
	__property int CurrentIndex = {read=GetCurrentIndex};
	__property int ItemCount = {read=GetCount};
	__property int ItemIndexOffset = {read=GetItemIndexOffset, write=SetItemIndexOffset};
	__property bool CanModify = {read=GetCanModify};
	__property bool CanInsert = {read=GetCanInsert};
	__property bool CanDelete = {read=GetCanDelete};
	__property bool Active = {read=GetActive, write=SetActive};
	__property bool BOF = {read=GetBOF};
	__property bool Eof = {read=GetEOF};
	__property bool Empty = {read=GetEmpty};
};

enum DECLSPEC_DENUM TAdapterErrorAction : unsigned char { aaFail, aaAbort, aaRetry };

typedef void __fastcall (__closure *TAdapterNotifyEvent)(TBindSourceAdapter* Adapter);

typedef void __fastcall (__closure *TAdapterHasUpdatesEvent)(TBindSourceAdapter* Adapter, bool &AHasUpdates);

typedef void __fastcall (__closure *TAdapterErrorEvent)(TBindSourceAdapter* Adapter, Data::Bind::Components::EBindCompError* E, TAdapterErrorAction &Action);

class PASCALIMPLEMENTATION TBindSourceAdapter : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
private:
	template<typename T> class DELPHICLASS TDummy__1;
	// Template declaration generated by Delphi parameterized types is
	// used only for accessing Delphi variables and fields.
	// Don't instantiate with new type parameters in user code.
	template<typename T> class PASCALIMPLEMENTATION TDummy__1 : public System::TObject
	{
		typedef System::TObject inherited;
		
	protected:
		T FDummy;
	public:
		/* TObject.Create */ inline __fastcall TDummy__1() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TDummy__1() { }
		
	};
	
	
	
private:
	bool FEnteringEditState;
	int FUpdatingRecords;
	System::Generics::Collections::TList__1<TBaseObjectBindSource*>* FScopes;
	bool FModified;
	System::Generics::Collections::TList__1<TBindSourceAdapterField*>* FFields;
	System::Generics::Collections::TList__1<TBindSourceAdapterLink*>* FLinks;
	int FItemIndex;
	TBindSourceAdapterState FState;
	TAdapterNotifyEvent FBeforeOpen;
	TAdapterNotifyEvent FAfterOpen;
	TAdapterNotifyEvent FBeforeClose;
	TAdapterNotifyEvent FAfterClose;
	TAdapterNotifyEvent FBeforeInsert;
	TAdapterNotifyEvent FAfterInsert;
	TAdapterNotifyEvent FBeforeEdit;
	TAdapterNotifyEvent FAfterEdit;
	TAdapterNotifyEvent FBeforePost;
	TAdapterNotifyEvent FAfterPost;
	TAdapterNotifyEvent FBeforeCancel;
	TAdapterNotifyEvent FAfterCancel;
	TAdapterNotifyEvent FBeforeDelete;
	TAdapterNotifyEvent FAfterDelete;
	TAdapterNotifyEvent FBeforeRefresh;
	TAdapterNotifyEvent FAfterRefresh;
	TAdapterNotifyEvent FBeforeScroll;
	TAdapterNotifyEvent FAfterScroll;
	TAdapterNotifyEvent FBeforeApplyUpdates;
	TAdapterNotifyEvent FAfterApplyUpdates;
	TAdapterNotifyEvent FBeforeCancelUpdates;
	TAdapterNotifyEvent FAfterCancelUpdates;
	TAdapterErrorEvent FOnPostError;
	TAdapterErrorEvent FOnDeleteError;
	TAdapterErrorEvent FOnInsertError;
	int FItemIndexOffset;
	TAdapterNotifyEvent FOnCancelUpdates;
	TAdapterNotifyEvent FOnApplyUpdates;
	TAdapterErrorEvent FOnApplyUpdatesError;
	TAdapterErrorEvent FOnEditError;
	TAdapterErrorEvent FOnCancelUpdatesError;
	TAdapterHasUpdatesEvent FOnHasUpdates;
	bool FAutoEdit;
	bool FResetNeeded;
	bool FAutoPost;
	System::Generics::Collections::TEnumerable__1<TBaseObjectBindSource*>* __fastcall GetScopes();
	void __fastcall CheckBrowseMode();
	void __fastcall CheckActive();
	void __fastcall CheckCanModify();
	void __fastcall CheckOperation(System::Sysutils::_di_TProc AOperation, TAdapterErrorEvent ErrorEvent);
	void __fastcall DoAfterApplyUpdates();
	void __fastcall DoAfterCancelUpdates();
	void __fastcall DoBeforeApplyUpdates();
	void __fastcall DoBeforeCancelUpdates();
	void __fastcall AutoEditField(TBindSourceAdapterField* AField);
	void __fastcall AutoPostField(TBindSourceAdapterField* AField);
	
protected:
	void __fastcall PostFields(System::TArray__1<TBindSourceAdapterField*> AFields);
	void __fastcall DataSetChanged();
	void __fastcall RecordChanged(TBindSourceAdapterField* AField);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	int __fastcall GetItemIndexOffset();
	void __fastcall SetItemIndexOffset(int Value);
	virtual bool __fastcall SupportsNestedFields();
	virtual bool __fastcall GetCanActivate();
	virtual void __fastcall AddScope(TBaseObjectBindSource* Value);
	bool __fastcall HasScope(TBaseObjectBindSource* Value);
	virtual void __fastcall RemoveScope(TBaseObjectBindSource* Value);
	void __fastcall SetItemIndex(int Value);
	void __fastcall ClearFields();
	void __fastcall AddLink(TBindSourceAdapterLink* DataLink);
	void __fastcall RemoveLink(TBindSourceAdapterLink* DataLink);
	void __fastcall SetState(TBindSourceAdapterState Value);
	virtual bool __fastcall GetMemberGetter(const System::UnicodeString AMemberName, System::UnicodeString &AGetter);
	virtual bool __fastcall GetMemberSetter(const System::UnicodeString AMemberName, System::UnicodeString &ASetter);
	virtual bool __fastcall GetMemberType(const System::UnicodeString AMemberName, Data::Bind::Components::TScopeMemberType &AType);
	virtual bool __fastcall IsValidChar(const System::UnicodeString AMemberName, const System::WideChar AChar);
	virtual System::Classes::_di_IEditFormatLink __fastcall GetFormatLink(const System::UnicodeString AMemberName);
	void __fastcall UpdateRecord();
	bool __fastcall GetEmpty();
	virtual System::TObject* __fastcall GetCurrent();
	virtual int __fastcall GetCount();
	int __fastcall GetItemIndex();
	int __fastcall GetCurrentIndex();
	virtual bool __fastcall GetCanDelete();
	virtual bool __fastcall GetCanInsert();
	virtual bool __fastcall GetActive();
	virtual bool __fastcall GetCanModify();
	virtual bool __fastcall GetCanRefresh();
	virtual bool __fastcall GetBOF();
	virtual bool __fastcall GetEOF();
	virtual void __fastcall GetLookupMemberNames(System::Classes::TStrings* AList);
	virtual bool __fastcall DeleteAt(int AIndex);
	virtual void __fastcall SetActive(bool Value);
	virtual int __fastcall AppendAt();
	virtual void __fastcall InternalEdit();
	virtual void __fastcall InternalRefresh();
	virtual void __fastcall InternalCancelUpdates();
	virtual void __fastcall InternalApplyUpdates();
	virtual void __fastcall InternalPost();
	virtual int __fastcall InsertAt(int AIndex);
	virtual bool __fastcall GetCanApplyUpdates();
	virtual bool __fastcall GetCanCancelUpdates();
	__classmethod void __fastcall AddFieldsToList(System::Rtti::TRttiType* AType, TBindSourceAdapter* ABindSourceAdapter, System::Generics::Collections::TList__1<TBindSourceAdapterField*>* AFieldsList, const _di_IGetMemberObject AGetMemberObject);
	template<typename T> __classmethod TBindSourceAdapterField* __fastcall CreateRttiPropertyField(System::Rtti::TRttiProperty* AProperty, TBindSourceAdapter* ABindSourceAdapter, const _di_IGetMemberObject AGetMemberObject, Data::Bind::Components::TScopeMemberType AMemberType, TDummy__1<T>* LDummy = (TDummy__1<T>*)(0x0));
	template<typename T> __classmethod TBindSourceAdapterField* __fastcall CreateRttiObjectPropertyField(System::Rtti::TRttiProperty* AProperty, TBindSourceAdapter* ABindSourceAdapter, const _di_IGetMemberObject AGetMemberObject, Data::Bind::Components::TScopeMemberType AMemberType, TDummy__1<T>* LDummy = (TDummy__1<T>*)(0x0));
	template<typename T> __classmethod TBindSourceAdapterField* __fastcall CreateRttiFieldField(System::Rtti::TRttiField* AProperty, TBindSourceAdapter* ABindSourceAdapter, const _di_IGetMemberObject AGetMemberObject, Data::Bind::Components::TScopeMemberType AMemberType, TDummy__1<T>* LDummy = (TDummy__1<T>*)(0x0));
	template<typename T> __classmethod TBindSourceAdapterField* __fastcall CreateRttiObjectFieldField(System::Rtti::TRttiField* AProperty, TBindSourceAdapter* ABindSourceAdapter, const _di_IGetMemberObject AGetMemberObject, Data::Bind::Components::TScopeMemberType AMemberType, TDummy__1<T>* LDummy = (TDummy__1<T>*)(0x0));
	__classmethod void __fastcall AddPropertiesToList(System::Rtti::TRttiType* AType, TBindSourceAdapter* ABindSourceAdapter, System::Generics::Collections::TList__1<TBindSourceAdapterField*>* AFieldsList, const _di_IGetMemberObject AGetMemberObject);
	virtual void __fastcall DoAfterCancel();
	virtual void __fastcall DoAfterClose();
	virtual void __fastcall DoAfterDelete();
	virtual void __fastcall DoAfterEdit();
	virtual void __fastcall DoAfterInsert();
	virtual void __fastcall DoAfterOpen();
	virtual void __fastcall DoAfterPost();
	virtual void __fastcall DoAfterRefresh();
	virtual void __fastcall DoAfterScroll();
	virtual void __fastcall DoBeforeCancel();
	virtual void __fastcall DoBeforeClose();
	virtual void __fastcall DoBeforeDelete();
	virtual void __fastcall DoBeforeEdit();
	virtual void __fastcall DoBeforeInsert();
	virtual void __fastcall DoBeforeOpen();
	virtual void __fastcall DoBeforePost();
	virtual void __fastcall DoBeforePostFields(System::TArray__1<TBindSourceAdapterField*> AFields);
	virtual void __fastcall DoAfterPostFields(System::TArray__1<TBindSourceAdapterField*> AFields);
	virtual void __fastcall DoBeforeRefresh();
	virtual void __fastcall DoBeforeScroll();
	
public:
	__fastcall virtual TBindSourceAdapter(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBindSourceAdapter();
	TBindSourceAdapterField* __fastcall FindField(const System::UnicodeString AMemberName);
	HIDESBASE Data::Bind::Components::_di_IScopeRecordEnumerator __fastcall GetEnumerator(const System::UnicodeString AMemberName, System::DelphiInterface<System::Sysutils::TFunc__1<System::Bindings::Evalprotocol::_di_IScope> > AGetScope, System::DelphiInterface<System::Sysutils::TFunc__2<System::UnicodeString,System::Bindings::Evalprotocol::_di_IScope> > AGetMemberScope);
	System::TObject* __fastcall GetValue();
	System::TObject* __fastcall GetMember(const System::UnicodeString AMemberName);
	virtual void __fastcall Refresh();
	virtual void __fastcall Next();
	virtual void __fastcall Prior();
	virtual void __fastcall First();
	virtual void __fastcall Last();
	HIDESBASE virtual void __fastcall Insert();
	virtual void __fastcall Append();
	virtual void __fastcall Delete();
	virtual void __fastcall Cancel();
	virtual void __fastcall Post();
	virtual void __fastcall PosChanging();
	virtual void __fastcall Edit(bool AForce = false)/* overload */;
	virtual void __fastcall CancelUpdates();
	virtual void __fastcall ApplyUpdates();
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList);
	void __fastcall ResetNeeded();
	__property System::TObject* Current = {read=GetCurrent};
	System::Bindings::Evalprotocol::_di_IScope __fastcall GetCurrentRecord(const System::UnicodeString AMemberName);
	__property int ItemIndex = {read=GetItemIndex, write=SetItemIndex, nodefault};
	__property int CurrentIndex = {read=GetCurrentIndex, nodefault};
	__property int ItemCount = {read=GetCount, nodefault};
	__property int ItemIndexOffset = {read=GetItemIndexOffset, write=SetItemIndexOffset, nodefault};
	__property bool CanModify = {read=GetCanModify, nodefault};
	__property bool CanInsert = {read=GetCanInsert, nodefault};
	__property bool CanDelete = {read=GetCanDelete, nodefault};
	__property bool CanRefresh = {read=GetCanRefresh, nodefault};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property bool AutoEdit = {read=FAutoEdit, write=FAutoEdit, default=1};
	__property bool AutoPost = {read=FAutoPost, write=FAutoPost, nodefault};
	__property bool BOF = {read=GetBOF, nodefault};
	__property bool Eof = {read=GetEOF, nodefault};
	__property bool Modified = {read=FModified, nodefault};
	__property bool Empty = {read=GetEmpty, nodefault};
	__property TBindSourceAdapterState State = {read=FState, nodefault};
	__property System::Generics::Collections::TList__1<TBindSourceAdapterField*>* Fields = {read=FFields};
	__property bool CanActivate = {read=GetCanActivate, nodefault};
	__property bool CanApplyUpdates = {read=GetCanApplyUpdates, nodefault};
	__property bool CanCancelUpdates = {read=GetCanCancelUpdates, nodefault};
	__property System::Generics::Collections::TEnumerable__1<TBaseObjectBindSource*>* Scopes = {read=GetScopes};
	__property TAdapterNotifyEvent BeforeOpen = {read=FBeforeOpen, write=FBeforeOpen};
	__property TAdapterNotifyEvent AfterOpen = {read=FAfterOpen, write=FAfterOpen};
	__property TAdapterNotifyEvent BeforeClose = {read=FBeforeClose, write=FBeforeClose};
	__property TAdapterNotifyEvent AfterClose = {read=FAfterClose, write=FAfterClose};
	__property TAdapterNotifyEvent BeforeInsert = {read=FBeforeInsert, write=FBeforeInsert};
	__property TAdapterNotifyEvent AfterInsert = {read=FAfterInsert, write=FAfterInsert};
	__property TAdapterNotifyEvent BeforeEdit = {read=FBeforeEdit, write=FBeforeEdit};
	__property TAdapterNotifyEvent AfterEdit = {read=FAfterEdit, write=FAfterEdit};
	__property TAdapterNotifyEvent BeforePost = {read=FBeforePost, write=FBeforePost};
	__property TAdapterNotifyEvent AfterPost = {read=FAfterPost, write=FAfterPost};
	__property TAdapterNotifyEvent BeforeCancel = {read=FBeforeCancel, write=FBeforeCancel};
	__property TAdapterNotifyEvent AfterCancel = {read=FAfterCancel, write=FAfterCancel};
	__property TAdapterNotifyEvent BeforeDelete = {read=FBeforeDelete, write=FBeforeDelete};
	__property TAdapterNotifyEvent AfterDelete = {read=FAfterDelete, write=FAfterDelete};
	__property TAdapterNotifyEvent BeforeScroll = {read=FBeforeScroll, write=FBeforeScroll};
	__property TAdapterNotifyEvent AfterScroll = {read=FAfterScroll, write=FAfterScroll};
	__property TAdapterNotifyEvent BeforeRefresh = {read=FBeforeRefresh, write=FBeforeRefresh};
	__property TAdapterNotifyEvent AfterRefresh = {read=FAfterRefresh, write=FAfterRefresh};
	__property TAdapterNotifyEvent BeforeApplyUpdates = {read=FBeforeApplyUpdates, write=FBeforeApplyUpdates};
	__property TAdapterNotifyEvent AfterApplyUpdates = {read=FAfterApplyUpdates, write=FAfterApplyUpdates};
	__property TAdapterNotifyEvent BeforeCancelUpdates = {read=FBeforeCancelUpdates, write=FBeforeCancelUpdates};
	__property TAdapterNotifyEvent AfterCancelUpdates = {read=FAfterCancelUpdates, write=FAfterCancelUpdates};
	__property TAdapterErrorEvent OnDeleteError = {read=FOnDeleteError, write=FOnDeleteError};
	__property TAdapterErrorEvent OnInsertError = {read=FOnInsertError, write=FOnInsertError};
	__property TAdapterErrorEvent OnEditError = {read=FOnEditError, write=FOnEditError};
	__property TAdapterErrorEvent OnPostError = {read=FOnPostError, write=FOnPostError};
	__property TAdapterErrorEvent OnApplyUpdatesError = {read=FOnApplyUpdatesError, write=FOnApplyUpdatesError};
	__property TAdapterErrorEvent OnCancelUpdatesError = {read=FOnCancelUpdatesError, write=FOnCancelUpdatesError};
	__property TAdapterNotifyEvent OnApplyUpdates = {read=FOnApplyUpdates, write=FOnApplyUpdates};
	__property TAdapterNotifyEvent OnCancelUpdates = {read=FOnCancelUpdates, write=FOnCancelUpdates};
	__property TAdapterHasUpdatesEvent OnHasUpdates = {read=FOnHasUpdates, write=FOnHasUpdates};
private:
	void *__IBindSourceAdapter;	// IBindSourceAdapter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6F63422E-B03D-4308-A536-12F3C5A22931}
	operator _di_IBindSourceAdapter()
	{
		_di_IBindSourceAdapter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindSourceAdapter*(void) { return (IBindSourceAdapter*)&__IBindSourceAdapter; }
	#endif
	
};


enum DECLSPEC_DENUM TObjectAdapterOption : unsigned char { optAllowModify, optAllowApplyUpdates, optAllowCancelUpdates };

typedef System::Set<TObjectAdapterOption, TObjectAdapterOption::optAllowModify, TObjectAdapterOption::optAllowCancelUpdates> TObjectAdapterOptions;

class PASCALIMPLEMENTATION TBaseObjectBindSourceAdapter : public TBindSourceAdapter
{
	typedef TBindSourceAdapter inherited;
	
private:
	TObjectAdapterOptions FOptions;
	
protected:
	virtual System::Rtti::TRttiType* __fastcall GetObjectType();
	
public:
	__fastcall virtual TBaseObjectBindSourceAdapter(System::Classes::TComponent* AOwner);
	__property TObjectAdapterOptions Options = {read=FOptions, write=FOptions, nodefault};
public:
	/* TBindSourceAdapter.Destroy */ inline __fastcall virtual ~TBaseObjectBindSourceAdapter() { }
	
};


class PASCALIMPLEMENTATION TBindSourceAdapterInstanceFactory : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Rtti::TRttiType* FType;
	bool FFindConstructor;
	System::Rtti::TRttiMethod* FConstructor;
	System::Rtti::TRttiMethod* __fastcall FindConstructor();
	
public:
	__fastcall TBindSourceAdapterInstanceFactory(System::Rtti::TRttiType* AType);
	bool __fastcall CheckConstructor(/* out */ System::Rtti::TRttiType* &AType, /* out */ System::Rtti::TRttiMethod* &AMethod)/* overload */;
	bool __fastcall CheckConstructor()/* overload */;
	bool __fastcall CanConstructInstance();
	System::TObject* __fastcall ConstructInstance();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindSourceAdapterInstanceFactory() { }
	
};


enum DECLSPEC_DENUM TListAdapterOption : unsigned char { loptAllowInsert, loptAllowDelete, loptAllowModify, loptAllowApplyUpdates, loptAllowCancelUpdates };

typedef System::Set<TListAdapterOption, TListAdapterOption::loptAllowInsert, TListAdapterOption::loptAllowCancelUpdates> TListAdapterOptions;

typedef void __fastcall (__closure *TListInsertEvent)(TBindSourceAdapter* Sender, int AIndex, bool &AHandled, int &ANewIndex);

typedef void __fastcall (__closure *TListAppendEvent)(TBindSourceAdapter* Sender, bool &AHandled, bool &Appended);

typedef void __fastcall (__closure *TListDeleteEvent)(TBindSourceAdapter* Sender, int AIndex, bool &AHandled, bool &ADeleted);

typedef void __fastcall (__closure *TCreateItemInstanceEvent)(TBindSourceAdapter* Sender, bool &AHandled, System::TObject* &AInstance);

typedef void __fastcall (__closure *TInitItemInstanceEvent)(TBindSourceAdapter* Sender, System::TObject* AInstance);

typedef void __fastcall (__closure *TSetObjectEvent)(TBindSourceAdapter* Sender, System::TObject* AObject);

class PASCALIMPLEMENTATION TBaseListBindSourceAdapter : public TBaseObjectBindSourceAdapter
{
	typedef TBaseObjectBindSourceAdapter inherited;
	
private:
	TListAppendEvent FOnListAppend;
	TListInsertEvent FOnListInsert;
	TListDeleteEvent FOnListDelete;
	TCreateItemInstanceEvent FOnCreateItemInstance;
	TInitItemInstanceEvent FOnInitItemInstance;
	TListAdapterOptions FOptions;
	
protected:
	virtual void __fastcall DoListDelete(int AIndex, /* out */ bool &AHandled, /* out */ bool &ARemoved);
	virtual void __fastcall DoListInsert(int AIndex, /* out */ bool &AHandled, /* out */ int &ANewIndex);
	virtual void __fastcall DoListAppend(/* out */ bool &AHandled, /* out */ bool &AAppended);
	virtual void __fastcall DoCreateInstance(/* out */ bool &AHandled, /* out */ System::TObject* &AInstance);
	virtual void __fastcall DoInitItemInstance(System::TObject* AInstance);
	
public:
	__fastcall virtual TBaseListBindSourceAdapter(System::Classes::TComponent* AOwner);
	__property TListAppendEvent OnListAppend = {read=FOnListAppend, write=FOnListAppend};
	__property TListDeleteEvent OnListDelete = {read=FOnListDelete, write=FOnListDelete};
	__property TListInsertEvent OnListInsert = {read=FOnListInsert, write=FOnListInsert};
	__property TCreateItemInstanceEvent OnCreateItemInstance = {read=FOnCreateItemInstance, write=FOnCreateItemInstance};
	__property TInitItemInstanceEvent OnInitItemInstance = {read=FOnInitItemInstance, write=FOnInitItemInstance};
	__property TListAdapterOptions Options = {read=FOptions, write=FOptions, nodefault};
public:
	/* TBindSourceAdapter.Destroy */ inline __fastcall virtual ~TBaseListBindSourceAdapter() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TListBindSourceAdapter__1 : public TBaseListBindSourceAdapter
{
	typedef TBaseListBindSourceAdapter inherited;
	
private:
	System::Generics::Collections::TList__1<T>* FList;
	TBindSourceAdapterInstanceFactory* FInstanceFactory;
	bool FOwnsList;
	TSetObjectEvent FOnBeforeSetList;
	TAdapterNotifyEvent FOnAfterSetList;
	TBindSourceAdapterInstanceFactory* __fastcall GetItemInstanceFactory();
	
protected:
	void __fastcall CheckList();
	virtual System::Rtti::TRttiType* __fastcall GetObjectType();
	virtual T __fastcall CreateItemInstance();
	virtual void __fastcall InitItemInstance(T AInstance);
	virtual System::TObject* __fastcall GetCurrent();
	virtual int __fastcall GetCount();
	virtual bool __fastcall DeleteAt(int AIndex);
	virtual int __fastcall AppendAt();
	virtual int __fastcall InsertAt(int AIndex);
	virtual bool __fastcall GetCanActivate();
	virtual bool __fastcall SupportsNestedFields();
	virtual bool __fastcall GetCanDelete();
	virtual bool __fastcall GetCanInsert();
	virtual bool __fastcall GetCanModify();
	virtual bool __fastcall GetCanApplyUpdates();
	virtual bool __fastcall GetCanCancelUpdates();
	virtual void __fastcall AddFields();
	virtual void __fastcall InternalCancelUpdates();
	virtual void __fastcall InternalApplyUpdates();
	virtual void __fastcall DoOnBeforeSetList(System::Generics::Collections::TList__1<T>* AList);
	virtual void __fastcall DoOnAfterSetList();
	
public:
	__fastcall virtual TListBindSourceAdapter__1(System::Classes::TComponent* AOwner, System::Generics::Collections::TList__1<T>* AList, bool AOwnsObject)/* overload */;
	__fastcall virtual ~TListBindSourceAdapter__1();
	void __fastcall SetList(System::Generics::Collections::TList__1<T>* AList, bool AOwnsObject = true);
	__property System::Generics::Collections::TList__1<T>* List = {read=FList};
	__property TSetObjectEvent OnBeforeSetList = {read=FOnBeforeSetList, write=FOnBeforeSetList};
	__property TAdapterNotifyEvent OnAfterSetList = {read=FOnAfterSetList, write=FOnAfterSetList};
};


class PASCALIMPLEMENTATION TListBindSourceAdapter : public TListBindSourceAdapter__1<System::TObject*>
{
	typedef TListBindSourceAdapter__1<System::TObject*> inherited;
	
private:
	System::TClass FClass;
	
protected:
	virtual System::Rtti::TRttiType* __fastcall GetObjectType();
	
public:
	__fastcall virtual TListBindSourceAdapter(System::Classes::TComponent* AOwner, System::Generics::Collections::TList__1<System::TObject*>* AList, System::TClass AClass, bool AOwnsObject)/* overload */;
public:
	/* {Data_Bind_ObjectScope}TListBindSourceAdapter<System_TObject>.Create */ inline __fastcall virtual TListBindSourceAdapter(System::Classes::TComponent* AOwner, System::Generics::Collections::TList__1<System::TObject*>* AList, bool AOwnsObject)/* overload */ : TListBindSourceAdapter__1<System::TObject*>(AOwner, AList, AOwnsObject) { }
	/* {Data_Bind_ObjectScope}TListBindSourceAdapter<System_TObject>.Destroy */ inline __fastcall virtual ~TListBindSourceAdapter() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TObjectBindSourceAdapter__1 : public TBaseObjectBindSourceAdapter
{
	typedef TBaseObjectBindSourceAdapter inherited;
	
private:
	T FDataObject;
	bool FOwnsObject;
	TSetObjectEvent FOnBeforeSetDataObject;
	TAdapterNotifyEvent FOnAfterSetDataObject;
	
protected:
	virtual System::Rtti::TRttiType* __fastcall GetObjectType();
	virtual bool __fastcall GetCanActivate();
	virtual System::TObject* __fastcall GetCurrent();
	virtual int __fastcall GetCount();
	virtual bool __fastcall DeleteAt(int AIndex);
	virtual int __fastcall AppendAt();
	virtual int __fastcall InsertAt(int AIndex);
	virtual bool __fastcall SupportsNestedFields();
	virtual bool __fastcall GetCanModify();
	virtual bool __fastcall GetCanApplyUpdates();
	virtual bool __fastcall GetCanCancelUpdates();
	virtual void __fastcall AddFields();
	virtual void __fastcall InternalApplyUpdates();
	virtual void __fastcall InternalCancelUpdates();
	virtual void __fastcall DoOnBeforeSetDataObject(T ADataObject);
	virtual void __fastcall DoOnAfterSetDataObject();
	
public:
	__fastcall virtual TObjectBindSourceAdapter__1(System::Classes::TComponent* AOwner, T AObject, bool AOwnsObject)/* overload */;
	__fastcall virtual ~TObjectBindSourceAdapter__1();
	void __fastcall SetDataObject(T ADataObject, bool AOwnsObject = true);
	__property T DataObject = {read=FDataObject};
	__property TSetObjectEvent OnBeforeSetDataObject = {read=FOnBeforeSetDataObject, write=FOnBeforeSetDataObject};
	__property TAdapterNotifyEvent OnAfterSetDataObject = {read=FOnAfterSetDataObject, write=FOnAfterSetDataObject};
};


class PASCALIMPLEMENTATION TObjectBindSourceAdapter : public TObjectBindSourceAdapter__1<System::TObject*>
{
	typedef TObjectBindSourceAdapter__1<System::TObject*> inherited;
	
private:
	System::TClass FClass;
	
protected:
	virtual System::Rtti::TRttiType* __fastcall GetObjectType();
	
public:
	__fastcall virtual TObjectBindSourceAdapter(System::Classes::TComponent* AOwner, System::TObject* AObject, System::TClass AClass, bool AOwnsObject)/* overload */;
public:
	/* {Data_Bind_ObjectScope}TObjectBindSourceAdapter<System_TObject>.Create */ inline __fastcall virtual TObjectBindSourceAdapter(System::Classes::TComponent* AOwner, System::TObject* AObject, bool AOwnsObject)/* overload */ : TObjectBindSourceAdapter__1<System::TObject*>(AOwner, AObject, AOwnsObject) { }
	/* {Data_Bind_ObjectScope}TObjectBindSourceAdapter<System_TObject>.Destroy */ inline __fastcall virtual ~TObjectBindSourceAdapter() { }
	
};


class PASCALIMPLEMENTATION TBindSourceAdapterField : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	static System::Generics::Collections::TDictionary__2<System::WideChar,Data::Bind::Components::TScopeMemberTypes>* FValidChars;
	System::UnicodeString FMemberName;
	TBindSourceAdapter* FOwner;
	_di_IGetMemberObject FGetMemberObject;
	int FIndex;
	System::TObject* __fastcall GetMemberObject();
	bool __fastcall SupportsStreamPersist(System::TObject* const Persistent, System::Classes::_di_IStreamPersist &StreamPersist);
	void __fastcall SaveToStreamPersist(System::Classes::_di_IStreamPersist StreamPersist);
	void __fastcall SaveToStrings(System::Classes::TStrings* Strings);
	System::Classes::TStream* __fastcall CreateValueBlobStream(System::TObject* AValue);
	virtual bool __fastcall GetAutoPost();
	virtual void __fastcall SetAutoPost(const bool Value);
	
protected:
	void __fastcall AutoPostField();
	void __fastcall AutoEditField();
	virtual System::Classes::TStream* __fastcall CreateBlobStream();
	bool __fastcall AssignValue(System::Classes::TPersistent* Dest);
	virtual void __fastcall Post();
	virtual bool __fastcall IsBuffered();
	virtual void __fastcall Cancel();
	virtual bool __fastcall GetIsObject();
	virtual bool __fastcall GetIsReadable();
	virtual bool __fastcall GetIsWritable();
	virtual bool __fastcall GetGetter(System::UnicodeString &AGetter);
	virtual bool __fastcall GetSetter(System::UnicodeString &AGetter);
	virtual bool __fastcall GetMemberType(Data::Bind::Components::TScopeMemberType &AType);
	bool __fastcall IsValidChar(System::WideChar AChar);
	System::Classes::_di_IEditFormatLink __fastcall GetFormatLink();
	void __fastcall RecordChanged();
	
public:
	__fastcall virtual TBindSourceAdapterField(TBindSourceAdapter* AOwner, const System::UnicodeString AMemberName, const _di_IGetMemberObject AGetMemberObject);
	
private:
	// __classmethod void __fastcall Destroy@();
	
public:
	virtual System::Rtti::TValue __fastcall GetTValue();
	virtual void __fastcall SetTValue(const System::Rtti::TValue &AValue);
	virtual TBindSourceAdapterField* __fastcall FindField(const System::UnicodeString AMemberName);
	__property TBindSourceAdapter* Owner = {read=FOwner};
	__property System::UnicodeString MemberName = {read=FMemberName};
	__property bool IsObject = {read=GetIsObject, nodefault};
	__property bool IsReadable = {read=GetIsReadable, nodefault};
	__property bool IsWritable = {read=GetIsWritable, nodefault};
	__property bool AutoPost = {read=GetAutoPost, write=SetAutoPost, nodefault};
	__property System::TObject* MemberObject = {read=GetMemberObject};
	__property _di_IGetMemberObject GetMemberObjectIntf = {read=FGetMemberObject, write=FGetMemberObject};
	__property int Index = {read=FIndex, nodefault};
	
private:
	// __classmethod void __fastcall Create@();
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TBindSourceAdapterField() { }
	
};


class PASCALIMPLEMENTATION TValueAccessor : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	TBindSourceAdapterField* FField;
public:
	/* TObject.Create */ inline __fastcall TValueAccessor() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TValueAccessor() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TValueReader__1 : public TValueAccessor
{
	typedef TValueAccessor inherited;
	
public:
	virtual T __fastcall GetValue() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TValueReader__1() : TValueAccessor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TValueReader__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TFieldValueReader__1 : public TValueReader__1<T>
{
	typedef TValueReader__1<T> inherited;
	
public:
	virtual T __fastcall GetValue();
public:
	/* TObject.Create */ inline __fastcall TFieldValueReader__1() : TValueReader__1<T>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFieldValueReader__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TBindFieldDefValueReader__1 : public TValueReader__1<T>
{
	typedef TValueReader__1<T> inherited;
	
public:
	virtual T __fastcall GetValue();
public:
	/* TObject.Create */ inline __fastcall TBindFieldDefValueReader__1() : TValueReader__1<T>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindFieldDefValueReader__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TBindFieldDefObjectValueReader__1 : public TBindFieldDefValueReader__1<T>
{
	typedef TBindFieldDefValueReader__1<T> inherited;
	
public:
	virtual T __fastcall GetValue();
public:
	/* TObject.Create */ inline __fastcall TBindFieldDefObjectValueReader__1() : TBindFieldDefValueReader__1<T>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindFieldDefObjectValueReader__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TPropertyValueReader__1 : public TValueReader__1<T>
{
	typedef TValueReader__1<T> inherited;
	
public:
	virtual T __fastcall GetValue();
public:
	/* TObject.Create */ inline __fastcall TPropertyValueReader__1() : TValueReader__1<T>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPropertyValueReader__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TValueWriter__1 : public TValueAccessor
{
	typedef TValueAccessor inherited;
	
public:
	virtual void __fastcall SetValue(const T AValue) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TValueWriter__1() : TValueAccessor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TValueWriter__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TFieldValueWriter__1 : public TValueWriter__1<T>
{
	typedef TValueWriter__1<T> inherited;
	
public:
	virtual void __fastcall SetValue(const T AValue);
public:
	/* TObject.Create */ inline __fastcall TFieldValueWriter__1() : TValueWriter__1<T>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFieldValueWriter__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TBindFieldDefValueWriter__1 : public TValueWriter__1<T>
{
	typedef TValueWriter__1<T> inherited;
	
public:
	virtual void __fastcall SetValue(const T AValue);
public:
	/* TObject.Create */ inline __fastcall TBindFieldDefValueWriter__1() : TValueWriter__1<T>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindFieldDefValueWriter__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TBindFieldDefObjectValueWriter__1 : public TBindFieldDefValueWriter__1<T>
{
	typedef TBindFieldDefValueWriter__1<T> inherited;
	
public:
	virtual void __fastcall SetValue(const T AValue);
public:
	/* TObject.Create */ inline __fastcall TBindFieldDefObjectValueWriter__1() : TBindFieldDefValueWriter__1<T>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindFieldDefObjectValueWriter__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TPropertyValueWriter__1 : public TValueWriter__1<T>
{
	typedef TValueWriter__1<T> inherited;
	
public:
	virtual void __fastcall SetValue(const T AValue);
public:
	/* TObject.Create */ inline __fastcall TPropertyValueWriter__1() : TValueWriter__1<T>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPropertyValueWriter__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TBindSourceAdapterReadField__1 : public TBindSourceAdapterField
{
	typedef TBindSourceAdapterField inherited;
	
protected:
	#define TBindSourceAdapterReadField__1_sMemberName u"Value"
	
	
private:
	TValueReader__1<T>* FValueReader;
	TBindSourceAdapterFieldType FRttiType;
	Data::Bind::Components::TScopeMemberType FMemberType;
	
protected:
	virtual T __fastcall GetValue();
	virtual bool __fastcall GetMemberType(Data::Bind::Components::TScopeMemberType &AType);
	virtual bool __fastcall GetGetter(System::UnicodeString &AGetter);
	
public:
	__fastcall TBindSourceAdapterReadField__1(TBindSourceAdapter* AOwner, const System::UnicodeString AMemberName, const TBindSourceAdapterFieldType &AType, const _di_IGetMemberObject AGetMemberObject, TValueReader__1<T>* const AReader, Data::Bind::Components::TScopeMemberType AMemberType);
	__fastcall virtual ~TBindSourceAdapterReadField__1();
	virtual System::Rtti::TValue __fastcall GetTValue();
	__property T Value = {read=GetValue};
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TBindSourceAdapterReadObjectField__1 : public TBindSourceAdapterReadField__1<T>
{
	typedef TBindSourceAdapterReadField__1<T> inherited;
	
protected:
	virtual System::Classes::TStream* __fastcall CreateBlobStream();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
public:
	/* {Data_Bind_ObjectScope}TBindSourceAdapterReadField<Data_Bind_ObjectScope_TBindSourceAdapterReadObjectField<T>_T>.Create */ inline __fastcall TBindSourceAdapterReadObjectField__1(TBindSourceAdapter* AOwner, const System::UnicodeString AMemberName, const TBindSourceAdapterFieldType &AType, const _di_IGetMemberObject AGetMemberObject, TValueReader__1<T>* const AReader, Data::Bind::Components::TScopeMemberType AMemberType) : TBindSourceAdapterReadField__1<T>(AOwner, AMemberName, AType, AGetMemberObject, AReader, AMemberType) { }
	/* {Data_Bind_ObjectScope}TBindSourceAdapterReadField<Data_Bind_ObjectScope_TBindSourceAdapterReadObjectField<T>_T>.Destroy */ inline __fastcall virtual ~TBindSourceAdapterReadObjectField__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TBindSourceAdapterReadWriteField__1 : public TBindSourceAdapterReadField__1<T>
{
	typedef TBindSourceAdapterReadField__1<T> inherited;
	
private:
	bool FAutoPost;
	bool FBuffered;
	TValueWriter__1<T>* FValueWriter;
	
private:
	T FBuffer;
	
protected:
	virtual bool __fastcall IsBuffered();
	virtual void __fastcall Post();
	virtual void __fastcall Cancel();
	virtual T __fastcall GetValue();
	virtual void __fastcall SetValue(const T Value);
	virtual bool __fastcall GetSetter(System::UnicodeString &AGetter);
	virtual void __fastcall ClearBuffer();
	virtual bool __fastcall GetAutoPost();
	virtual void __fastcall SetAutoPost(const bool Value);
	
public:
	__fastcall TBindSourceAdapterReadWriteField__1(TBindSourceAdapter* AOwner, const System::UnicodeString AMemberName, const TBindSourceAdapterFieldType &AType, const _di_IGetMemberObject AGetMemberObject, TValueReader__1<T>* const AReader, TValueWriter__1<T>* const AWriter, Data::Bind::Components::TScopeMemberType AMemberType);
	virtual void __fastcall SetTValue(const System::Rtti::TValue &AValue);
	__fastcall virtual ~TBindSourceAdapterReadWriteField__1();
	__property T Value = {read=GetValue, write=SetValue};
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TBindSourceAdapterReadWriteObjectField__1 : public TBindSourceAdapterReadWriteField__1<T>
{
	typedef TBindSourceAdapterReadWriteField__1<T> inherited;
	
protected:
	virtual System::Classes::TStream* __fastcall CreateBlobStream();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual void __fastcall ClearBuffer();
public:
	/* {Data_Bind_ObjectScope}TBindSourceAdapterReadWriteField<Data_Bind_ObjectScope_TBindSourceAdapterReadWriteObjectField<T>_T>.Create */ inline __fastcall TBindSourceAdapterReadWriteObjectField__1(TBindSourceAdapter* AOwner, const System::UnicodeString AMemberName, const TBindSourceAdapterFieldType &AType, const _di_IGetMemberObject AGetMemberObject, TValueReader__1<T>* const AReader, TValueWriter__1<T>* const AWriter, Data::Bind::Components::TScopeMemberType AMemberType) : TBindSourceAdapterReadWriteField__1<T>(AOwner, AMemberName, AType, AGetMemberObject, AReader, AWriter, AMemberType) { }
	/* {Data_Bind_ObjectScope}TBindSourceAdapterReadWriteField<Data_Bind_ObjectScope_TBindSourceAdapterReadWriteObjectField<T>_T>.Destroy */ inline __fastcall virtual ~TBindSourceAdapterReadWriteObjectField__1() { }
	
};


class PASCALIMPLEMENTATION TBindSourceAdapterReadObjectField : public TBindSourceAdapterReadObjectField__1<System::TObject*>
{
	typedef TBindSourceAdapterReadObjectField__1<System::TObject*> inherited;
	
private:
	bool FHaveFields;
	System::Generics::Collections::TList__1<TBindSourceAdapterField*>* FFields;
	void __fastcall CheckAddFields();
	
protected:
	virtual bool __fastcall GetIsObject();
	
public:
	__fastcall virtual ~TBindSourceAdapterReadObjectField();
	__fastcall TBindSourceAdapterReadObjectField(TBindSourceAdapter* AOwner, const System::UnicodeString AMemberName, const TBindSourceAdapterFieldType &AType, const _di_IGetMemberObject AGetMemberObject, TValueReader__1<System::TObject*>* const AReader, Data::Bind::Components::TScopeMemberType AMemberType);
	virtual TBindSourceAdapterField* __fastcall FindField(const System::UnicodeString AMemberName);
	__property System::Generics::Collections::TList__1<TBindSourceAdapterField*>* Fields = {read=FFields};
};


class PASCALIMPLEMENTATION TBindSourceAdapterCustomScope : public System::Bindings::Customscope::TCustomScope
{
	typedef System::Bindings::Customscope::TCustomScope inherited;
	
protected:
	virtual System::_di_IInterface __fastcall DoLookup(const System::UnicodeString Name);
public:
	/* TCustomScope.Create */ inline __fastcall virtual TBindSourceAdapterCustomScope(System::TObject* const MappedObject, System::TClass MetaClass) : System::Bindings::Customscope::TCustomScope(MappedObject, MetaClass) { }
	/* TCustomScope.Destroy */ inline __fastcall virtual ~TBindSourceAdapterCustomScope() { }
	
};


class PASCALIMPLEMENTATION TBindSourceAdapterObjectFieldCustomScope : public System::Bindings::Customscope::TCustomScope
{
	typedef System::Bindings::Customscope::TCustomScope inherited;
	
protected:
	virtual System::_di_IInterface __fastcall DoLookup(const System::UnicodeString Name);
public:
	/* TCustomScope.Create */ inline __fastcall virtual TBindSourceAdapterObjectFieldCustomScope(System::TObject* const MappedObject, System::TClass MetaClass) : System::Bindings::Customscope::TCustomScope(MappedObject, MetaClass) { }
	/* TCustomScope.Destroy */ inline __fastcall virtual ~TBindSourceAdapterObjectFieldCustomScope() { }
	
};


class PASCALIMPLEMENTATION TBindSourceAdapterGetMemberObject : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	TBindSourceAdapter* FBindSourceAdapter;
	
public:
	__fastcall TBindSourceAdapterGetMemberObject(TBindSourceAdapter* ACollectionEditor);
	System::TObject* __fastcall GetMemberObject();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindSourceAdapterGetMemberObject() { }
	
private:
	void *__IGetMemberObject;	// IGetMemberObject 
	
public:
	operator IGetMemberObject*(void) { return (IGetMemberObject*)&__IGetMemberObject; }
	
};


class PASCALIMPLEMENTATION TBindSourceAdapteObjectFieldGetMemberObject : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::TObject* FObject;
	
public:
	__fastcall TBindSourceAdapteObjectFieldGetMemberObject(System::TObject* AObject);
	System::TObject* __fastcall GetMemberObject();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindSourceAdapteObjectFieldGetMemberObject() { }
	
private:
	void *__IGetMemberObject;	// IGetMemberObject 
	
public:
	operator IGetMemberObject*(void) { return (IGetMemberObject*)&__IGetMemberObject; }
	
};


class PASCALIMPLEMENTATION TGeneratorRecord : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::TArray__1<System::Rtti::TValue> FValues;
	System::Generics::Collections::TList__1<System::TObject*>* FFreeObjects;
	
public:
	__fastcall virtual ~TGeneratorRecord();
public:
	/* TObject.Create */ inline __fastcall TGeneratorRecord() : System::TObject() { }
	
};


class PASCALIMPLEMENTATION TCustomDataGeneratorAdapter : public TListBindSourceAdapter__1<TGeneratorRecord*>
{
	typedef TListBindSourceAdapter__1<TGeneratorRecord*> inherited;
	
	
private:
	template<typename T> class DELPHICLASS TDummy__1;
	// Template declaration generated by Delphi parameterized types is
	// used only for accessing Delphi variables and fields.
	// Don't instantiate with new type parameters in user code.
	template<typename T> class PASCALIMPLEMENTATION TDummy__1 : public System::TObject
	{
		typedef System::TObject inherited;
		
	protected:
		T FDummy;
	public:
		/* TObject.Create */ inline __fastcall TDummy__1() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TDummy__1() { }
		
	};
	
	
	
private:
	TGeneratorFieldDefs* FFieldDefs;
	int FRecordCount;
	static void __fastcall AddFieldsToList(TGeneratorFieldDefs* AFieldDefs, TBindSourceAdapter* ABindSourceAdapter, System::Generics::Collections::TList__1<TBindSourceAdapterField*>* AFieldsList, const _di_IGetMemberObject AGetMemberObject);
	template<typename T> static TBindSourceAdapterField* __fastcall CreateField(TGeneratorFieldDef* AFieldDef, TBindSourceAdapter* ABindSourceAdapter, const _di_IGetMemberObject AGetMemberObject, TDummy__1<T>* LDummy = (TDummy__1<T>*)(0x0));
	template<typename T> static TBindSourceAdapterField* __fastcall CreateObjectField(TGeneratorFieldDef* AFieldDef, TBindSourceAdapter* ABindSourceAdapter, const _di_IGetMemberObject AGetMemberObject, TDummy__1<T>* LDummy = (TDummy__1<T>*)(0x0));
	void __fastcall GenerateExistingRecords(System::Generics::Collections::TList__1<TGeneratorRecord*>* AList);
	void __fastcall SetFieldDefs(TGeneratorFieldDefs* Value);
	TGeneratorBindFieldDefsClass __fastcall GetFieldDefsClass();
	void __fastcall InitFieldDefs();
	void __fastcall SetRecordCount(const int Value);
	template<typename T> void __fastcall CreateCustomFormatExpression(const System::UnicodeString ACustomFormat, /* out */ System::Bindings::Expression::TBindingExpression* &AExpression, /* out */ TCustomFormatObject* &ACustomFormatObject);
	
protected:
	virtual bool __fastcall SupportsNestedFields();
	virtual void __fastcall SetActive(bool Value);
	virtual TGeneratorRecord* __fastcall CreateItemInstance();
	virtual void __fastcall InitItemInstance(TGeneratorRecord* ARecord);
	virtual void __fastcall FieldDefChanged(System::TObject* Sender);
	virtual bool __fastcall GetCanActivate();
	virtual bool __fastcall GetCanInsert();
	
public:
	__fastcall virtual TCustomDataGeneratorAdapter(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDataGeneratorAdapter();
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList);
	virtual void __fastcall AddFields();
	__property TGeneratorFieldDefs* FieldDefs = {read=FFieldDefs, write=SetFieldDefs};
	__property int RecordCount = {read=FRecordCount, write=SetRecordCount, default=-1};
};


class PASCALIMPLEMENTATION TDataGeneratorAdapter : public TCustomDataGeneratorAdapter
{
	typedef TCustomDataGeneratorAdapter inherited;
	
__published:
	__property FieldDefs;
	__property Active;
	__property AutoEdit = {default=1};
	__property AutoPost;
	__property RecordCount = {default=-1};
	__property BeforeOpen;
	__property AfterOpen;
	__property BeforeClose;
	__property AfterClose;
	__property BeforeInsert;
	__property AfterInsert;
	__property BeforeEdit;
	__property AfterEdit;
	__property BeforePost;
	__property AfterPost;
	__property BeforeCancel;
	__property AfterCancel;
	__property BeforeDelete;
	__property AfterDelete;
	__property BeforeScroll;
	__property AfterScroll;
	__property BeforeRefresh;
	__property AfterRefresh;
	__property OnDeleteError;
	__property OnInsertError;
	__property OnEditError;
	__property OnPostError;
	__property OnApplyUpdates;
	__property OnCancelUpdates;
	__property Options;
public:
	/* TCustomDataGeneratorAdapter.Create */ inline __fastcall virtual TDataGeneratorAdapter(System::Classes::TComponent* AOwner) : TCustomDataGeneratorAdapter(AOwner) { }
	/* TCustomDataGeneratorAdapter.Destroy */ inline __fastcall virtual ~TDataGeneratorAdapter() { }
	
};


class PASCALIMPLEMENTATION TValueGenerator : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FGeneratorName;
	TGeneratorFieldType FFieldType;
	TGeneratorOptions FOptions;
	System::UnicodeString FCustomFormat;
	
protected:
	virtual int __fastcall GetRecordCount();
	
public:
	__fastcall virtual TValueGenerator(TGeneratorFieldDef* AFieldDef);
	virtual void __fastcall FirstRecord();
	virtual void __fastcall NextRecord();
	virtual System::Rtti::TValue __fastcall GetValue(bool &AFree);
	__property TGeneratorFieldType FieldType = {read=FFieldType, nodefault};
	__property TGeneratorOptions Options = {read=FOptions, nodefault};
	__property System::UnicodeString GeneratorName = {read=FGeneratorName};
	__property System::UnicodeString CustomFormat = {read=FCustomFormat};
	__property int RecordCount = {read=GetRecordCount, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TValueGenerator() { }
	
};


class PASCALIMPLEMENTATION TValueGeneratorDelegate : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::Rtti::TValue __fastcall GetValue(bool &AFree) = 0 ;
	virtual void __fastcall NextRecord() = 0 ;
	virtual void __fastcall FirstRecord() = 0 ;
	virtual int __fastcall GetRecordCount();
public:
	/* TObject.Create */ inline __fastcall TValueGeneratorDelegate() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TValueGeneratorDelegate() { }
	
};


__interface TValueGeneratorOnGetValue  : public System::IInterface 
{
	virtual System::Rtti::TValue __fastcall Invoke(const System::Rtti::TValue &AKey, bool &AFreeObject) = 0 ;
};

class PASCALIMPLEMENTATION TValueGeneratorDelegateWithEvents : public TValueGeneratorDelegate
{
	typedef TValueGeneratorDelegate inherited;
	
private:
	_di_TValueGeneratorOnGetValue FGetValue;
	
public:
	__property _di_TValueGeneratorOnGetValue OnGetValue = {read=FGetValue, write=FGetValue};
public:
	/* TObject.Create */ inline __fastcall TValueGeneratorDelegateWithEvents() : TValueGeneratorDelegate() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TValueGeneratorDelegateWithEvents() { }
	
};


class PASCALIMPLEMENTATION TInternalTypedListValueGeneratorDelegate : public TValueGeneratorDelegateWithEvents
{
	typedef TValueGeneratorDelegateWithEvents inherited;
	
protected:
	int __fastcall PRNGenerator(const int ARange, int &Seed);
public:
	/* TObject.Create */ inline __fastcall TInternalTypedListValueGeneratorDelegate() : TValueGeneratorDelegateWithEvents() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInternalTypedListValueGeneratorDelegate() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TTypedListValueGeneratorDelegate__1 : public TInternalTypedListValueGeneratorDelegate
{
	typedef TInternalTypedListValueGeneratorDelegate inherited;
	
private:
	int FValueCounter;
	System::Generics::Collections::TList__1<T>* FValuesList;
	
public:
	__fastcall TTypedListValueGeneratorDelegate__1(const TGeneratorOptions AOptions, const T *AValuesList, const int AValuesList_High)/* overload */;
	__fastcall TTypedListValueGeneratorDelegate__1(const TGeneratorOptions AOptions, const T *AValuesList, const int AValuesList_High, const _di_TValueGeneratorOnGetValue AOnGetValue)/* overload */;
	__fastcall TTypedListValueGeneratorDelegate__1(const TGeneratorOptions AOptions, const System::TArray__1<T> AValuesList)/* overload */;
	__fastcall TTypedListValueGeneratorDelegate__1(const TGeneratorOptions AOptions, const System::TArray__1<T> AValuesList, const _di_TValueGeneratorOnGetValue AOnGetValue)/* overload */;
	__fastcall virtual ~TTypedListValueGeneratorDelegate__1();
	virtual int __fastcall GetRecordCount();
	virtual System::Rtti::TValue __fastcall GetValue(bool &AFree);
	virtual void __fastcall NextRecord();
	virtual void __fastcall FirstRecord();
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T, typename T1> class PASCALIMPLEMENTATION TTypedListValueGeneratorDelegate2__2 : public TTypedListValueGeneratorDelegate__1<T>
{
	typedef TTypedListValueGeneratorDelegate__1<T> inherited;
	
private:
	System::TArray__1<T> __fastcall ConvertArray(System::TArray__1<T1> AArray);
	
public:
	__fastcall TTypedListValueGeneratorDelegate2__2(TGeneratorOptions AOptions, System::TArray__1<T1> AValuesList);
public:
	/* {Data_Bind_ObjectScope}TTypedListValueGeneratorDelegate<Data_Bind_ObjectScope_TTypedListValueGeneratorDelegate2<T,T1>_T>.CreateFromOA */ inline __fastcall TTypedListValueGeneratorDelegate2__2(const TGeneratorOptions AOptions, const T *AValuesList, const int AValuesList_High)/* overload */ : TTypedListValueGeneratorDelegate__1<T>(AOptions, AValuesList, AValuesList_High) { }
	/* {Data_Bind_ObjectScope}TTypedListValueGeneratorDelegate<Data_Bind_ObjectScope_TTypedListValueGeneratorDelegate2<T,T1>_T>.CreateFromOA */ inline __fastcall TTypedListValueGeneratorDelegate2__2(const TGeneratorOptions AOptions, const T *AValuesList, const int AValuesList_High, const _di_TValueGeneratorOnGetValue AOnGetValue)/* overload */ : TTypedListValueGeneratorDelegate__1<T>(AOptions, AValuesList, AValuesList_High, AOnGetValue) { }
	/* {Data_Bind_ObjectScope}TTypedListValueGeneratorDelegate<Data_Bind_ObjectScope_TTypedListValueGeneratorDelegate2<T,T1>_T>.Destroy */ inline __fastcall virtual ~TTypedListValueGeneratorDelegate2__2() { }
	
};


class PASCALIMPLEMENTATION TDelegateValueGenerator : public TValueGenerator
{
	typedef TValueGenerator inherited;
	
private:
	TValueGeneratorDelegate* FDelegate;
	
protected:
	virtual int __fastcall GetRecordCount();
	virtual TValueGeneratorDelegate* __fastcall CreateDelegate() = 0 ;
	
public:
	__fastcall virtual TDelegateValueGenerator(TGeneratorFieldDef* AFieldDef);
	virtual void __fastcall FirstRecord();
	virtual void __fastcall NextRecord();
	virtual System::Rtti::TValue __fastcall GetValue(bool &AFree);
	__fastcall virtual ~TDelegateValueGenerator();
};


_DECLARE_METACLASS(System::TMetaClass, TValueGeneratorClass);

struct DECLSPEC_DRECORD TValueGeneratorDescription
{
private:
	TValueGeneratorClass FClassType;
	System::UnicodeString FFormatFieldName;
	System::UnicodeString FUnitName;
	
public:
	__fastcall TValueGeneratorDescription(TValueGeneratorClass AClassType, const System::UnicodeString AFormatFieldName, const System::UnicodeString AUnitName);
	__property TValueGeneratorClass ClassType = {read=FClassType};
	__property System::UnicodeString FormatFieldName = {read=FFormatFieldName};
	__property System::UnicodeString UnitName = {read=FUnitName};
	TValueGeneratorDescription() {}
};


class PASCALIMPLEMENTATION TCustomFormatObject : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::Rtti::TValue __fastcall GetTValue() = 0 ;
	virtual void __fastcall SetTValue(const System::Rtti::TValue &AValue) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TCustomFormatObject() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomFormatObject() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TTypedCustomFormatObject__1 : public TCustomFormatObject
{
	typedef TCustomFormatObject inherited;
	
private:
	T FValue;
	
protected:
	__fastcall TTypedCustomFormatObject__1()/* overload */;
	
private:
	T __fastcall GetValue();
	void __fastcall SetValue(T AValue);
	
protected:
	virtual System::Rtti::TValue __fastcall GetTValue();
	virtual void __fastcall SetTValue(const System::Rtti::TValue &AValue);
	
public:
	__property T V = {read=GetValue, write=SetValue};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TTypedCustomFormatObject__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TValueReaderFunc__1 : public TValueReader__1<T>
{
	typedef TValueReader__1<T> inherited;
	
private:
	System::DelphiInterface<System::Sysutils::TFunc__2<System::UnicodeString,T> > FGetValue;
	System::UnicodeString FName;
	
public:
	__fastcall TValueReaderFunc__1(const System::UnicodeString AName, System::DelphiInterface<System::Sysutils::TFunc__2<System::UnicodeString,T> > AGetValue);
	virtual T __fastcall GetValue();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TValueReaderFunc__1() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TValueWriterProc__1 : public TValueWriter__1<T>
{
	typedef TValueWriter__1<T> inherited;
	
private:
	System::DelphiInterface<System::Sysutils::TProc__2<System::UnicodeString,T> > FSetValue;
	System::UnicodeString FName;
	
public:
	__fastcall TValueWriterProc__1(const System::UnicodeString AName, System::DelphiInterface<System::Sysutils::TProc__2<System::UnicodeString,T> > ASetValue);
	virtual void __fastcall SetValue(const T AValue);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TValueWriterProc__1() { }
	
};


typedef System::Generics::Collections::TPair__2<System::UnicodeString,TValueGeneratorDescription> TNameValueGeneratorDescriptionPair;

//-- var, const, procedure ---------------------------------------------------
#define seEditModes (System::Set<TBindSourceAdapterState, TBindSourceAdapterState::seInactive, TBindSourceAdapterState::seInsert>() << TBindSourceAdapterState::seEdit << TBindSourceAdapterState::seInsert )
extern DELPHI_PACKAGE void __fastcall RegisterValueGenerator(const System::UnicodeString AName, TGeneratorFieldTypes AFieldTypes, TValueGeneratorClass AClass, const System::UnicodeString AFrameworkExt = System::UnicodeString())/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterValueGenerator(const System::UnicodeString AName, TGeneratorFieldTypes AFieldTypes, const TValueGeneratorDescription &ADescription, const System::UnicodeString AFrameWorkExt = System::UnicodeString())/* overload */;
extern DELPHI_PACKAGE void __fastcall UnRegisterValueGenerator(const System::UnicodeString AName, TGeneratorFieldTypes AFieldTypes, const System::UnicodeString AFrameWorkExt);
extern DELPHI_PACKAGE System::TArray__1<System::UnicodeString> __fastcall GetRegisteredValueGenerators(TGeneratorFieldType AFieldType);
extern DELPHI_PACKAGE bool __fastcall FindRegisteredValueGenerator(const System::UnicodeString AName, TGeneratorFieldType AFieldType, TValueGeneratorDescription &ADescription);
extern DELPHI_PACKAGE System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,TValueGeneratorDescription> > __fastcall FindRegisteredValueGenerators(const System::UnicodeString AName, TGeneratorFieldType AFieldType);
extern DELPHI_PACKAGE void __fastcall BindSourceAdapterError(const System::UnicodeString Message, System::Classes::TComponent* Component = (System::Classes::TComponent*)(0x0));
}	/* namespace Objectscope */
}	/* namespace Bind */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND_OBJECTSCOPE)
using namespace Data::Bind::Objectscope;
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
#endif	// Data_Bind_ObjectscopeHPP
