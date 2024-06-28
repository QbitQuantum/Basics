// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Bind.DBLinks.pas' rev: 34.00 (Android)

#ifndef Data_Bind_DblinksHPP
#define Data_Bind_DblinksHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <System.Bindings.Outputs.hpp>
#include <Data.DB.hpp>
#include <System.Bindings.EvalProtocol.hpp>

//-- user supplied -----------------------------------------------------------
namespace Data
{
namespace Bind
{
namespace Dblinks
{
  _INIT_UNIT(Data_Bind_Dblinks);
}	/* namespace Dblinks */
}	/* namespace Bind */
}	/* namespace Data */

namespace Data
{
namespace Bind
{
namespace Dblinks
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBaseBindDBControlLink;
class DELPHICLASS TBaseBindDBFieldLink;
__interface DELPHIINTERFACE ICustomDBGrid;
typedef System::DelphiInterface<ICustomDBGrid> _di_ICustomDBGrid;
class DELPHICLASS TBaseBindDBGridLink;
class DELPHICLASS TBaseDBGridLinkColumn;
class DELPHICLASS TBaseDBGridLinkColumns;
struct TDBGridLinkColumnExpressionPair;
struct TDBGridLinkColumnDescription;
__interface DELPHIINTERFACE IBindDBGridLinkControlManager;
typedef System::DelphiInterface<IBindDBGridLinkControlManager> _di_IBindDBGridLinkControlManager;
class DELPHICLASS TBindDBColumnFactory;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBaseBindDBControlLink : public Data::Bind::Components::TBindComponentDelegate
{
	typedef Data::Bind::Components::TBindComponentDelegate inherited;
	
protected:
	virtual void __fastcall SetActive(bool AValue);
	void __fastcall SetSourceControl(Data::Bind::Dbscope::TCustomBindSourceDB* const Value);
	Data::Bind::Dbscope::TCustomBindSourceDB* __fastcall GetSourceControl();
	void __fastcall SetSourceMember(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSourceMember();
	virtual System::Classes::TComponent* __fastcall GetControlComponent();
	virtual void __fastcall SetControlComponent(System::Classes::TComponent* const Value);
	
public:
	virtual void __fastcall UpdateColumns() = 0 ;
	__property Data::Bind::Dbscope::TCustomBindSourceDB* DataSource = {read=GetSourceControl, write=SetSourceControl};
public:
	/* TContainedBindComponent.Create */ inline __fastcall virtual TBaseBindDBControlLink(System::Classes::TComponent* AOwner) : Data::Bind::Components::TBindComponentDelegate(AOwner) { }
	/* TContainedBindComponent.Destroy */ inline __fastcall virtual ~TBaseBindDBControlLink() { }
	
private:
	void *__IBindActivate;	// Data::Bind::Components::IBindActivate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79856F26-5E66-4A24-B4DE-A7DBBE6356AD}
	operator Data::Bind::Components::_di_IBindActivate()
	{
		Data::Bind::Components::_di_IBindActivate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindActivate*(void) { return (Data::Bind::Components::IBindActivate*)&__IBindActivate; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBaseBindDBFieldLink : public TBaseBindDBControlLink
{
	typedef TBaseBindDBControlLink inherited;
	
private:
	Data::Bind::Components::TCustomBindLink* FBindLink;
	bool __fastcall GetAutoActivate();
	void __fastcall SetAutoActivate(const bool Value);
	
protected:
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(bool Value);
	
public:
	virtual System::TArray__1<Data::Bind::Components::TCommonBindComponent*> __fastcall GetDelegates();
	virtual bool __fastcall CanActivate(System::Classes::TComponent* Sender);
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender);
	virtual bool __fastcall RequiresControlHandler();
	virtual void __fastcall Loaded();
	__fastcall virtual TBaseBindDBFieldLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBaseBindDBFieldLink();
	__property Data::Bind::Components::TCustomBindLink* BindLink = {read=FBindLink};
	__property System::UnicodeString FieldName = {read=GetSourceMember, write=SetSourceMember};
	__property bool AutoActivate = {read=GetAutoActivate, write=SetAutoActivate, default=1};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E14CC39A-D660-4801-9FFB-7CA7F2B6A99F}") ICustomDBGrid  : public System::IInterface 
{
	virtual bool __fastcall GetReadOnly() = 0 ;
	virtual Data::Db::TDataSet* __fastcall GetDataSet() = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual bool __fastcall GetDefaultFields() = 0 ;
	virtual System::Classes::TComponentState __fastcall GetComponentState() = 0 ;
	virtual TBaseDBGridLinkColumns* __fastcall CreateColumns() = 0 ;
	virtual void __fastcall BeginUpdate() = 0 ;
	virtual void __fastcall CancelLayout() = 0 ;
	virtual void __fastcall EndUpdate() = 0 ;
	virtual void __fastcall BeginLayout() = 0 ;
	virtual void __fastcall EndLayout() = 0 ;
	virtual void __fastcall LayoutChanged() = 0 ;
	virtual void __fastcall InvalidateColumn(TBaseDBGridLinkColumn* AColumn) = 0 ;
	virtual void __fastcall InvalidateField(Data::Db::TField* AField) = 0 ;
	virtual bool __fastcall AcquireLayoutLock() = 0 ;
	__property bool ReadOnly = {read=GetReadOnly};
	__property Data::Db::TDataSet* DataSet = {read=GetDataSet};
	__property bool Active = {read=GetActive};
	__property bool DefaultFields = {read=GetDefaultFields};
	__property System::Classes::TComponentState ComponentState = {read=GetComponentState};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBaseBindDBGridLink : public TBaseBindDBControlLink
{
	typedef TBaseBindDBControlLink inherited;
	
private:
	Data::Bind::Components::TCustomBindGridLink* FBindGridLink;
	System::Byte FUpdateLock;
	System::Byte FLayoutLock;
	bool __fastcall GetAutoActivate();
	void __fastcall SetAutoActivate(const bool Value);
	void __fastcall InternalLayout();
	int __fastcall GetBufferCount();
	void __fastcall SetBufferCount(const int Value);
	
protected:
	virtual void __fastcall SetActive(bool Value);
	virtual TBaseDBGridLinkColumns* __fastcall GetColumns() = 0 ;
	virtual System::_di_IInterface __fastcall GetBindDBColumnFactory(const GUID &AGuid);
	virtual _di_IBindDBGridLinkControlManager __fastcall GetBindDBColumnManager();
	virtual void __fastcall Loaded();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall ClearColumns(_di_IBindDBGridLinkControlManager AManager);
	void __fastcall BeginUpdate();
	void __fastcall CancelLayout();
	void __fastcall EndUpdate();
	bool __fastcall GetReadOnly();
	Data::Db::TDataSet* __fastcall GetDataSet();
	virtual bool __fastcall GetActive();
	bool __fastcall GetDefaultFields();
	System::Classes::TComponentState __fastcall GetComponentState();
	TBaseDBGridLinkColumns* __fastcall CreateColumns();
	void __fastcall BeginLayout();
	void __fastcall EndLayout();
	bool __fastcall AcquireLayoutLock();
	void __fastcall LayoutChanged();
	virtual void __fastcall InvalidateColumn(TBaseDBGridLinkColumn* AColumn);
	virtual void __fastcall InvalidateField(Data::Db::TField* AField);
	
public:
	__fastcall virtual TBaseBindDBGridLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBaseBindDBGridLink();
	virtual bool __fastcall CanActivate(System::Classes::TComponent* Sender);
	virtual System::TArray__1<Data::Bind::Components::TCommonBindComponent*> __fastcall GetDelegates();
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender);
	__property Data::Bind::Components::TCustomBindGridLink* BindGridLink = {read=FBindGridLink};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property int BufferCount = {read=GetBufferCount, write=SetBufferCount, default=-1};
	__property bool AutoActivate = {read=GetAutoActivate, write=SetAutoActivate, default=1};
private:
	void *__ICustomDBGrid;	// ICustomDBGrid 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E14CC39A-D660-4801-9FFB-7CA7F2B6A99F}
	operator _di_ICustomDBGrid()
	{
		_di_ICustomDBGrid intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ICustomDBGrid*(void) { return (ICustomDBGrid*)&__ICustomDBGrid; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBaseDBGridLinkColumn : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	Data::Db::TField* FField;
	System::UnicodeString FFieldName;
	bool FStored;
	Data::Db::TField* __fastcall GetField();
	TBaseDBGridLinkColumn* __fastcall GetParentColumn();
	virtual void __fastcall SetField(Data::Db::TField* Value);
	void __fastcall SetFieldName(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall Initialize();
	_di_ICustomDBGrid __fastcall GetGridIntf();
	System::Classes::TComponent* __fastcall GetGrid();
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual void __fastcall SetIndex(int Value);
	__property bool IsStored = {read=FStored, write=FStored, default=1};
	
public:
	__fastcall virtual TBaseDBGridLinkColumn(System::Classes::TCollection* Collection);
	__fastcall virtual ~TBaseDBGridLinkColumn();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	System::Classes::TAlignment __fastcall DefaultAlignment();
	virtual void __fastcall RestoreDefaults();
	__property Data::Db::TField* Field = {read=GetField, write=SetField};
	__property TBaseDBGridLinkColumn* ParentColumn = {read=GetParentColumn};
	__property System::UnicodeString FieldName = {read=FFieldName, write=SetFieldName};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TDBGridLinkColumnsState : unsigned char { csDefault, csCustomized };

_DECLARE_METACLASS(System::TMetaClass, TBaseDBGridLinkColumnClass);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBaseDBGridLinkColumns : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
private:
	System::Classes::TComponent* FGrid;
	TBaseDBGridLinkColumn* __fastcall GetColumn(int Index);
	void __fastcall SetColumn(int Index, TBaseDBGridLinkColumn* Value);
	void __fastcall SetState(TDBGridLinkColumnsState NewState);
	TDBGridLinkColumnsState __fastcall GetState();
	Data::Db::TDataSet* __fastcall GetDataSet();
	
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	_di_ICustomDBGrid __fastcall GetGridIntf();
	
public:
	__fastcall virtual TBaseDBGridLinkColumns(System::Classes::TComponent* Grid, TBaseDBGridLinkColumnClass ColumnClass);
	HIDESBASE TBaseDBGridLinkColumn* __fastcall Add();
	bool __fastcall Updating();
	void __fastcall LoadFromFile(const System::UnicodeString Filename);
	void __fastcall LoadFromStream(System::Classes::TStream* S);
	void __fastcall RestoreDefaults();
	void __fastcall RebuildColumns();
	void __fastcall SaveToFile(const System::UnicodeString Filename);
	void __fastcall SaveToStream(System::Classes::TStream* S);
	__property TDBGridLinkColumnsState State = {read=GetState, write=SetState, nodefault};
	__property System::Classes::TComponent* Grid = {read=FGrid};
	__property TBaseDBGridLinkColumn* BaseItems[int Index] = {read=GetColumn, write=SetColumn};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TBaseDBGridLinkColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TDBGridLinkColumnExpressionPair
{
private:
	System::UnicodeString FControlExpression;
	System::UnicodeString FSourceExpression;
	
public:
	__fastcall TDBGridLinkColumnExpressionPair(const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression);
	__property System::UnicodeString ControlExpression = {read=FControlExpression};
	__property System::UnicodeString SourceExpression = {read=FSourceExpression};
	TDBGridLinkColumnExpressionPair() {}
};


struct DECLSPEC_DRECORD TDBGridLinkColumnDescription
{
private:
	System::Classes::TComponent* FColumnControl;
	System::UnicodeString FColumnName;
	int FColumnIndex;
	System::UnicodeString FSourceMemberName;
	System::UnicodeString FControlMemberName;
	System::TArray__1<TDBGridLinkColumnExpressionPair> FFormatCellExpressions;
	System::TArray__1<TDBGridLinkColumnExpressionPair> FFormatColumnExpressions;
	System::TArray__1<TDBGridLinkColumnExpressionPair> FParseCellExpressions;
	
public:
	__fastcall TDBGridLinkColumnDescription(System::Classes::TComponent* AColumnControl, const System::UnicodeString AColumnName, int AColumnIndex, const System::UnicodeString AControlMemberName, const System::UnicodeString ASourceMemberName, System::TArray__1<TDBGridLinkColumnExpressionPair> AFormatColumnExpressions, System::TArray__1<TDBGridLinkColumnExpressionPair> AFormatCellExpressions, System::TArray__1<TDBGridLinkColumnExpressionPair> AParseCellExpression);
	__property System::Classes::TComponent* ColumnControl = {read=FColumnControl};
	__property System::UnicodeString ColumnName = {read=FColumnName};
	__property int ColumnIndex = {read=FColumnIndex};
	__property System::UnicodeString SourceMemberName = {read=FSourceMemberName};
	__property System::UnicodeString ControlMemberName = {read=FControlMemberName};
	__property System::TArray__1<TDBGridLinkColumnExpressionPair> ParseCellExpression = {read=FParseCellExpressions};
	__property System::TArray__1<TDBGridLinkColumnExpressionPair> FormatCellExpressions = {read=FFormatCellExpressions};
	__property System::TArray__1<TDBGridLinkColumnExpressionPair> FormatColumnExpressions = {read=FFormatColumnExpressions};
	bool __fastcall IsEqual(const TDBGridLinkColumnDescription &ADescription);
	TDBGridLinkColumnDescription() {}
};


__interface  INTERFACE_UUID("{F631C178-78F7-4164-A532-6F335760A26A}") IBindDBGridLinkControlManager  : public System::IInterface 
{
	virtual void __fastcall BeginUpdate() = 0 ;
	virtual void __fastcall EndUpdate() = 0 ;
	virtual void __fastcall ClearColumns() = 0 ;
	virtual bool __fastcall CanAddColumn(TBaseDBGridLinkColumn* AColumn) = 0 /* overload */;
	virtual bool __fastcall CanAddColumn(Data::Db::TField* AField) = 0 /* overload */;
	virtual int __fastcall AddColumn(TBaseDBGridLinkColumn* AColumn) = 0 /* overload */;
	virtual int __fastcall AddColumn(Data::Db::TField* AField) = 0 /* overload */;
	virtual void __fastcall UpdateColumn(TBaseDBGridLinkColumn* AColumn, const TDBGridLinkColumnDescription &ADescription) = 0 /* overload */;
	virtual void __fastcall UpdateColumn(Data::Db::TField* AField, const TDBGridLinkColumnDescription &ADescription) = 0 /* overload */;
	virtual TDBGridLinkColumnDescription __fastcall DescribeColumn(int AIndex, TBaseDBGridLinkColumn* AColumn) = 0 /* overload */;
	virtual TDBGridLinkColumnDescription __fastcall DescribeColumn(int AIndex, Data::Db::TField* AField) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBindDBColumnFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual TBindDBColumnFactory();
	virtual bool __fastcall Supports(const GUID &AIntf, System::Classes::TComponent* AGrid) = 0 ;
	virtual System::_di_IInterface __fastcall CreateFactory(const GUID &AIntf, System::Classes::TComponent* AGrid) = 0 ;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindDBColumnFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TBindDBColumnFactoryClass);

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterBindDBColumnFactory(TBindDBColumnFactoryClass *AFactories, const int AFactories_High);
extern DELPHI_PACKAGE void __fastcall UnregisterBindDBColumnFactory(TBindDBColumnFactoryClass *AFactories, const int AFactories_High);
}	/* namespace Dblinks */
}	/* namespace Bind */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND_DBLINKS)
using namespace Data::Bind::Dblinks;
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
#endif	// Data_Bind_DblinksHPP
