// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Bind.DBScope.pas' rev: 34.00 (Windows)

#ifndef Data_Bind_DbscopeHPP
#define Data_Bind_DbscopeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Data.DB.hpp>
#include <Data.Bind.Components.hpp>
#include <System.Bindings.Helper.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.CustomScope.hpp>
#include <System.Bindings.CustomWrapper.hpp>
#include <System.Bindings.Factories.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <System.Rtti.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.Bind.DBScope"

namespace Data
{
namespace Bind
{
namespace Dbscope
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindDataSetScope;
class DELPHICLASS TCustomBindSourceDB;
class DELPHICLASS TBindScopeDB;
class DELPHICLASS TBindSourceDB;
class DELPHICLASS TSubDataSource;
class DELPHICLASS TBaseDataLink;
class DELPHICLASS TBindScopeDBEnumerator;
class DELPHICLASS TBaseRemoteAdapter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindDataSetScope : public System::Bindings::Customscope::TCustomScope
{
	typedef System::Bindings::Customscope::TCustomScope inherited;
	
protected:
	virtual System::_di_IInterface __fastcall DoLookup(const System::UnicodeString Name);
public:
	/* TCustomScope.Create */ inline __fastcall virtual TBindDataSetScope(System::TObject* const MappedObject, System::TClass MetaClass) : System::Bindings::Customscope::TCustomScope(MappedObject, MetaClass) { }
	/* TCustomScope.Destroy */ inline __fastcall virtual ~TBindDataSetScope() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TCustomBindSourceDB : public Data::Bind::Components::TBaseLinkingBindSource
{
	typedef Data::Bind::Components::TBaseLinkingBindSource inherited;
	
private:
	bool FCalcBufferCount;
	Data::Db::TDataSource* FUnusedDataSource;
	int FEnumerating;
	bool FMultiRecordChange;
	TBaseDataLink* FDataLink;
	Data::Db::TDataSource* FDataSource;
	System::Generics::Collections::TDictionary__2<Data::Bind::Components::TBasicBindComponent*,TBaseDataLink*>* FDataLinks;
	Data::Bind::Components::TBindEventList* FActiveChanged;
	Data::Bind::Components::TBindEventList* FDataSetChanged;
	Data::Bind::Components::TBindEventList* FEditingChanged;
	Data::Bind::Components::TBindEventList1__1<int>* FDataSetScrolled;
	int FApplyMaxErrors;
	bool FResetNeeded;
	System::Rtti::TRttiContext FRttiContext;
	System::Generics::Collections::TDictionary__2<Data::Db::TField*,System::Classes::_di_IEditFormatLink>* FEditFormatLinks;
	bool __fastcall CheckDataSet();
	void __fastcall OnMasterChanged(System::TObject* Sender);
	void __fastcall OnMasterDisabled(System::TObject* Sender);
	void __fastcall OnActiveChanged(System::TObject* Sender);
	void __fastcall OnDataSetChanged(System::TObject* Sender);
	void __fastcall OnDataSetScrolled(System::TObject* Sender, int ADistance);
	void __fastcall OnEditingChanged(System::TObject* Sender);
	void __fastcall OnIndexFieldChanged(System::TObject* Sender);
	Data::Db::TDataSet* __fastcall GetDataSet();
	void __fastcall SetDataSet(Data::Db::TDataSet* const Value);
	void __fastcall GetRowMember(int ARow, const System::UnicodeString AMemberName, System::DelphiInterface<System::Sysutils::TProc__1<System::TObject*> > ACallback);
	System::Classes::TComponent* __fastcall GetDataComponent();
	void __fastcall SetDataComponent(System::Classes::TComponent* AComponent);
	Data::Db::TDataSource* __fastcall CreateSubDataSource();
	void __fastcall SetLinks(Data::Db::TDataSource* Value);
	bool __fastcall IsDataSetStored();
	bool __fastcall IsCurrencyField(Data::Db::TField* AField);
	
protected:
	virtual void __fastcall Loaded();
	void __fastcall SetDataSource(Data::Db::TDataSource* const Value);
	Data::Db::TDataSource* __fastcall GetDataSource();
	virtual System::TObject* __fastcall GetValue();
	virtual System::TObject* __fastcall GetMember(const System::UnicodeString AMemberName);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall AddExpression(Data::Bind::Components::TBasicBindComponent* AExpression);
	virtual void __fastcall RemoveExpression(Data::Bind::Components::TBasicBindComponent* AExpression);
	bool __fastcall Locate(const System::UnicodeString KeyFields, const System::Rtti::TValue &KeyValues);
	System::Rtti::TValue __fastcall Lookup(const System::UnicodeString KeyFields, const System::Rtti::TValue &KeyValues, const System::UnicodeString ResultFields);
	void __fastcall GetLookupMemberNames(System::Classes::TStrings* AList);
	virtual bool __fastcall Edit(Data::Bind::Components::TBasicBindComponent* ABindComp)/* overload */;
	virtual bool __fastcall GetIsEditing(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual void __fastcall SetModified(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual bool __fastcall GetIsModified(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual bool __fastcall GetCanModify(Data::Bind::Components::TBasicBindComponent* ABindComp)/* overload */;
	virtual void __fastcall UpdateRecord(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual void __fastcall Reset(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual void __fastcall SetReadOnly(Data::Bind::Components::TBasicBindComponent* ABindComp, const bool Value);
	virtual void __fastcall SetField(Data::Bind::Components::TBasicBindComponent* ABindComp, const System::UnicodeString FieldName);
	virtual void __fastcall ClearModified(Data::Bind::Components::TBasicBindComponent* ABindComp);
	virtual void __fastcall PosChanging(Data::Bind::Components::TBasicBindComponent* ABindComp);
	HIDESBASE Data::Bind::Components::_di_IScopeRecordEnumerator __fastcall GetEnumerator(const System::UnicodeString AMemberName, int ABufferCount)/* overload */;
	HIDESBASE Data::Bind::Components::_di_IScopeRecordEnumerator __fastcall GetEnumerator(const System::UnicodeString AMemberName, bool ABuffered)/* overload */;
	virtual bool __fastcall GetBOF();
	virtual bool __fastcall GetEOF();
	virtual bool __fastcall GetSelected();
	virtual void __fastcall Next();
	virtual void __fastcall Prior();
	virtual void __fastcall First();
	virtual void __fastcall Last();
	virtual void __fastcall ApplyUpdates();
	virtual bool __fastcall GetCanApplyUpdates();
	virtual bool __fastcall GetCanCancelUpdates();
	virtual void __fastcall CancelUpdates();
	bool __fastcall GetBufferCount(/* out */ int &ABufferCount);
	virtual bool __fastcall GetActive();
	virtual bool __fastcall GetCanModify()/* overload */;
	virtual bool __fastcall GetCanDelete();
	virtual bool __fastcall GetCanInsert();
	virtual bool __fastcall GetCanRefresh();
	virtual bool __fastcall GetEditing();
	virtual void __fastcall AddActiveChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall RemoveActiveChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall AddEditingChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall RemoveEditingChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall AddDataSetScrolled(Data::Bind::Components::TNotifyDistanceEvent LNotify);
	virtual void __fastcall RemoveDataSetScrolled(Data::Bind::Components::TNotifyDistanceEvent LNotify);
	virtual void __fastcall AddDataSetChanged(System::Classes::TNotifyEvent LNotify);
	virtual void __fastcall RemoveDataSetChanged(System::Classes::TNotifyEvent LNotify);
	HIDESBASE virtual void __fastcall Insert();
	virtual void __fastcall Delete();
	virtual void __fastcall Cancel();
	virtual void __fastcall Post();
	virtual void __fastcall Edit()/* overload */;
	virtual void __fastcall Refresh();
	bool __fastcall IsValidChar(const System::UnicodeString AFieldName, const System::WideChar AChar);
	bool __fastcall IsRequired(const System::UnicodeString AFieldName);
	System::Classes::_di_IEditFormatLink __fastcall GetFormatLink(const System::UnicodeString AFieldName);
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList);
	System::Bindings::Evalprotocol::_di_IScope __fastcall GetCurrentRecord(const System::UnicodeString AMemberName);
	bool __fastcall GetMemberGetter(const System::UnicodeString AMemberName, System::UnicodeString &AGetter);
	bool __fastcall GetMemberSetter(const System::UnicodeString AMemberName, System::UnicodeString &ASetter);
	bool __fastcall GetMemberType(const System::UnicodeString AMemberName, Data::Bind::Components::TScopeMemberType &AType);
	bool __fastcall GetPositionGetter(System::UnicodeString &AGetter, int &ABase);
	bool __fastcall GetPositionSetter(System::UnicodeString &ASetter, int &ABase);
	void __fastcall GetRecord(int ARow, const System::UnicodeString AMemberName, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IScope> > ACallback);
	bool __fastcall GetIsUnidirectional();
	
public:
	__fastcall virtual TCustomBindSourceDB(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindSourceDB();
	static bool __fastcall IsDataComponent(System::Classes::TComponent* AComponent);
	void __fastcall EmptyDataLink();
	void __fastcall ResetNeeded();
	__property Data::Db::TDataSource* DataSource = {read=GetDataSource, write=SetDataSource};
	__property Data::Db::TDataSet* DataSet = {read=GetDataSet, write=SetDataSet, stored=IsDataSetStored};
	__property System::Classes::TComponent* DataComponent = {read=GetDataComponent, write=SetDataComponent};
	__property int ApplyMaxErrors = {read=FApplyMaxErrors, write=FApplyMaxErrors, default=-1};
private:
	void *__IScopeUnidirectional;	// Data::Bind::Components::IScopeUnidirectional 
	void *__IScopeLocate;	// Data::Bind::Components::IScopeLocate 
	void *__IScopeBuffer;	// Data::Bind::Components::IScopeBuffer 
	void *__IScopeNavigatorUpdates;	// Data::Bind::Components::IScopeNavigatorUpdates 
	void *__IScopeLookup;	// Data::Bind::Components::IScopeLookup 
	void *__IScopeGetRecord;	// Data::Bind::Components::IScopeGetRecord 
	void *__IScopeMemberScripting;	// Data::Bind::Components::IScopeMemberScripting 
	void *__IScopeCurrentRecord;	// Data::Bind::Components::IScopeCurrentRecord 
	void *__IScopeMemberNames;	// Data::Bind::Components::IScopeMemberNames 
	void *__IScopeEditor;	// Data::Bind::Components::IScopeEditor 
	void *__IScopeState;	// Data::Bind::Components::IScopeState 
	void *__IScopeNavigator;	// Data::Bind::Components::IScopeNavigator 
	void *__IScopeRecordEnumerableBuffered;	// Data::Bind::Components::IScopeRecordEnumerableBuffered 
	void *__IScopeRecordEnumerable;	// Data::Bind::Components::IScopeRecordEnumerable 
	void *__IScopeEditLink;	// Data::Bind::Components::IScopeEditLink 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4B7BCC08-0278-4CC4-ADF3-7376F2A0A8CC}
	operator Data::Bind::Components::_di_IScopeUnidirectional()
	{
		Data::Bind::Components::_di_IScopeUnidirectional intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeUnidirectional*(void) { return (Data::Bind::Components::IScopeUnidirectional*)&__IScopeUnidirectional; }
	#endif
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
	// {43D47EB0-14F2-47D0-89F5-6CB516F36BF3}
	operator Data::Bind::Components::_di_IScopeBuffer()
	{
		Data::Bind::Components::_di_IScopeBuffer intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeBuffer*(void) { return (Data::Bind::Components::IScopeBuffer*)&__IScopeBuffer; }
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
	// {DC2115E9-F163-43E2-A713-52A8455EF8FD}
	operator Data::Bind::Components::_di_IScopeRecordEnumerableBuffered()
	{
		Data::Bind::Components::_di_IScopeRecordEnumerableBuffered intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeRecordEnumerableBuffered*(void) { return (Data::Bind::Components::IScopeRecordEnumerableBuffered*)&__IScopeRecordEnumerableBuffered; }
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


typedef TCustomBindSourceDB TCustomBindScopeDB;

class PASCALIMPLEMENTATION TBindScopeDB : public TCustomBindSourceDB
{
	typedef TCustomBindSourceDB inherited;
	
private:
	void __fastcall ReadPosition(System::Classes::TReader* Reader);
	
protected:
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
__published:
	__property DataSource;
	__property DataSet;
	__property ScopeMappings;
public:
	/* TCustomBindSourceDB.Create */ inline __fastcall virtual TBindScopeDB(System::Classes::TComponent* AOwner) : TCustomBindSourceDB(AOwner) { }
	/* TCustomBindSourceDB.Destroy */ inline __fastcall virtual ~TBindScopeDB() { }
	
};


class PASCALIMPLEMENTATION TBindSourceDB : public TCustomBindSourceDB
{
	typedef TCustomBindSourceDB inherited;
	
__published:
	__property DataSource;
	__property DataSet;
	__property ScopeMappings;
public:
	/* TCustomBindSourceDB.Create */ inline __fastcall virtual TBindSourceDB(System::Classes::TComponent* AOwner) : TCustomBindSourceDB(AOwner) { }
	/* TCustomBindSourceDB.Destroy */ inline __fastcall virtual ~TBindSourceDB() { }
	
};


class PASCALIMPLEMENTATION TSubDataSource : public Data::Db::TDataSource
{
	typedef Data::Db::TDataSource inherited;
	
private:
	Data::Db::TDataSet* __fastcall GetDataSet();
	
public:
	__fastcall virtual ~TSubDataSource();
	
__published:
	__property Data::Db::TDataSet* DataSet = {read=GetDataSet, stored=false};
public:
	/* TDataSource.Create */ inline __fastcall virtual TSubDataSource(System::Classes::TComponent* AOwner) : Data::Db::TDataSource(AOwner) { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBaseDataLink : public Data::Db::TDataLink
{
	typedef Data::Db::TDataLink inherited;
	
protected:
	HIDESBASE virtual bool __fastcall Edit();
public:
	/* TDataLink.Create */ inline __fastcall TBaseDataLink() : Data::Db::TDataLink() { }
	/* TDataLink.Destroy */ inline __fastcall virtual ~TBaseDataLink() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindScopeDBEnumerator : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	bool FBuffered;
	System::UnicodeString FMemberName;
	bool FCalcBuffer;
	TCustomBindSourceDB* FBindScope;
	int FFetchCount;
	int FSaveFetchRecNo;
	int FSaveActiveRecord;
	int FNextActiveRecord;
	bool FMultiRecordChange;
	int FMaxRecordCount;
	void __fastcall GetMemberValue(const System::UnicodeString AMemberName, const Data::Bind::Components::TScopeMemberType AType, const Data::Bind::Components::_di_TValueCallback ACallback)/* overload */;
	bool __fastcall GetMemberValue(const System::UnicodeString AMemberName, const Data::Bind::Components::TScopeMemberType *ATypes, const int ATypes_High, /* out */ System::Rtti::TValue &AValue)/* overload */;
	bool __fastcall CanGetMemberValue(const System::UnicodeString AMemberName, Data::Bind::Components::TScopeMemberType AType);
	Data::Bind::Components::TScopeMemberTypes __fastcall GetSupportedTypes(Data::Db::TFieldType AFieldType);
	
protected:
	bool __fastcall GetMultiRecordChange();
	void __fastcall First();
	System::Bindings::Evalprotocol::_di_IScope __fastcall GetCurrent();
	int __fastcall GetRecordCount();
	System::Bindings::Evalprotocol::_di_IScope __fastcall GetMemberCurrent(const System::UnicodeString AMemberName);
	bool __fastcall MoveNext();
	__property System::Bindings::Evalprotocol::_di_IScope Current = {read=GetCurrent};
	
public:
	__fastcall TBindScopeDBEnumerator(TCustomBindSourceDB* ABindScope, const System::UnicodeString AMemberName, int ABufferCount)/* overload */;
	__fastcall TBindScopeDBEnumerator(TCustomBindSourceDB* ABindScope, const System::UnicodeString AMemberName, bool ABuffered)/* overload */;
	__fastcall virtual ~TBindScopeDBEnumerator();
private:
	void *__IScopeRecordEnumeratorEvalShortcut;	// Data::Bind::Components::IScopeRecordEnumeratorEvalShortcut 
	void *__IScopeRecordEnumeratorStatus;	// Data::Bind::Components::IScopeRecordEnumeratorStatus 
	void *__IScopeRecordEnumeratorCount;	// Data::Bind::Components::IScopeRecordEnumeratorCount 
	void *__IScopeRecordEnumerator;	// Data::Bind::Components::IScopeRecordEnumerator 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {64768DD1-CD80-434E-A5C1-D5990E0E04F9}
	operator Data::Bind::Components::_di_IScopeRecordEnumeratorEvalShortcut()
	{
		Data::Bind::Components::_di_IScopeRecordEnumeratorEvalShortcut intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeRecordEnumeratorEvalShortcut*(void) { return (Data::Bind::Components::IScopeRecordEnumeratorEvalShortcut*)&__IScopeRecordEnumeratorEvalShortcut; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {755F088B-F673-45BD-A74D-ECBBDB38ACBA}
	operator Data::Bind::Components::_di_IScopeRecordEnumeratorStatus()
	{
		Data::Bind::Components::_di_IScopeRecordEnumeratorStatus intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeRecordEnumeratorStatus*(void) { return (Data::Bind::Components::IScopeRecordEnumeratorStatus*)&__IScopeRecordEnumeratorStatus; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {46FAE534-6F58-4850-AF66-14DF7B8AEC0C}
	operator Data::Bind::Components::_di_IScopeRecordEnumeratorCount()
	{
		Data::Bind::Components::_di_IScopeRecordEnumeratorCount intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeRecordEnumeratorCount*(void) { return (Data::Bind::Components::IScopeRecordEnumeratorCount*)&__IScopeRecordEnumeratorCount; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6C93BB29-D210-43E9-9850-0C22EDD0F9B2}
	operator Data::Bind::Components::_di_IScopeRecordEnumerator()
	{
		Data::Bind::Components::_di_IScopeRecordEnumerator intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IScopeRecordEnumerator*(void) { return (Data::Bind::Components::IScopeRecordEnumerator*)&__IScopeRecordEnumerator; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TBaseRemoteAdapter : public Data::Bind::Objectscope::TBindSourceAdapter
{
	typedef Data::Bind::Objectscope::TBindSourceAdapter inherited;
	
protected:
	virtual bool __fastcall SupportsNestedFields();
	
public:
	__fastcall virtual TBaseRemoteAdapter(System::Classes::TComponent* AOwner);
	void __fastcall AddField(Data::Bind::Objectscope::TBindSourceAdapterField* AField);
public:
	/* TBindSourceAdapter.Destroy */ inline __fastcall virtual ~TBaseRemoteAdapter() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbscope */
}	/* namespace Bind */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND_DBSCOPE)
using namespace Data::Bind::Dbscope;
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
#endif	// Data_Bind_DbscopeHPP
