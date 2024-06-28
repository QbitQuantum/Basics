// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Bind.Grid.pas' rev: 34.00 (Android)

#ifndef Data_Bind_GridHPP
#define Data_Bind_GridHPP

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
#include <System.Bindings.Outputs.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.Bindings.EvalProtocol.hpp>

//-- user supplied -----------------------------------------------------------
namespace Data
{
namespace Bind
{
namespace Grid
{
  _INIT_UNIT(Data_Bind_Grid);
}	/* namespace Grid */
}	/* namespace Bind */
}	/* namespace Data */

namespace Data
{
namespace Bind
{
namespace Grid
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBaseLinkToDataSource;
__interface DELPHIINTERFACE ILinkGridToDataSource;
typedef System::DelphiInterface<ILinkGridToDataSource> _di_ILinkGridToDataSource;
class DELPHICLASS TBaseLinkGridToDataSource;
class DELPHICLASS TCustomLinkGridToDataSource;
class DELPHICLASS TLinkGridToDataSource;
class DELPHICLASS TBaseLinkGridToDataSourceColumn;
class DELPHICLASS TBaseLinkGridToDataSourceColumns;
struct TLinkGridColumnExpressionPair;
class DELPHICLASS TLinkGridColumnDescriptions;
class DELPHICLASS TLinkGridColumnDescription;
struct TCreateColumnDescription;
__interface DELPHIINTERFACE ILinkGridToDataSourceControlManager;
typedef System::DelphiInterface<ILinkGridToDataSourceControlManager> _di_ILinkGridToDataSourceControlManager;
class DELPHICLASS TLinkGridToDataSourceColumnFactory;
class DELPHICLASS TLinkGridToDataSourceColumnsEnumerator;
class DELPHICLASS TLinkGridToDataSourceColumns;
class DELPHICLASS TLinkGridToDataSourceColumn;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBaseLinkToDataSource : public Data::Bind::Components::TBindComponentDelegate
{
	typedef Data::Bind::Components::TBindComponentDelegate inherited;
	
protected:
	void __fastcall SetSourceControl(Data::Bind::Components::TBaseLinkingBindSource* const Value);
	Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetSourceControl();
	void __fastcall SetSourceMember(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSourceMember();
	virtual System::Classes::TComponent* __fastcall GetControlComponent();
	virtual void __fastcall SetControlComponent(System::Classes::TComponent* const Value);
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* Sender, System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	
public:
	virtual void __fastcall UpdateColumns() = 0 ;
	virtual bool __fastcall ColumnsHaveChanged() = 0 ;
	__property Data::Bind::Components::TBaseLinkingBindSource* DataSource = {read=GetSourceControl, write=SetSourceControl};
public:
	/* TContainedBindComponent.Create */ inline __fastcall virtual TBaseLinkToDataSource(System::Classes::TComponent* AOwner) : Data::Bind::Components::TBindComponentDelegate(AOwner) { }
	/* TContainedBindComponent.Destroy */ inline __fastcall virtual ~TBaseLinkToDataSource() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E14CC39A-D660-4801-9FFB-7CA7F2B6A99F}") ILinkGridToDataSource  : public System::IInterface 
{
	virtual bool __fastcall GetReadOnly() = 0 ;
	virtual Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetDataSource() = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual bool __fastcall GetDefaultMembers() = 0 ;
	virtual System::Classes::TComponentState __fastcall GetComponentState() = 0 ;
	virtual TBaseLinkGridToDataSourceColumns* __fastcall CreateColumns() = 0 ;
	virtual void __fastcall BeginUpdate() = 0 ;
	virtual void __fastcall CancelLayout() = 0 ;
	virtual void __fastcall EndUpdate() = 0 ;
	virtual void __fastcall BeginLayout() = 0 ;
	virtual void __fastcall EndLayout() = 0 ;
	virtual void __fastcall LayoutChanged() = 0 ;
	virtual void __fastcall InvalidateColumn(TBaseLinkGridToDataSourceColumn* AColumn) = 0 ;
	virtual bool __fastcall AcquireLayoutLock() = 0 ;
	__property bool ReadOnly = {read=GetReadOnly};
	__property Data::Bind::Components::TBaseLinkingBindSource* DataSource = {read=GetDataSource};
	__property bool Active = {read=GetActive};
	__property bool DefaultMembers = {read=GetDefaultMembers};
	__property System::Classes::TComponentState ComponentState = {read=GetComponentState};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBaseLinkGridToDataSource : public TBaseLinkToDataSource
{
	typedef TBaseLinkToDataSource inherited;
	
private:
	Data::Bind::Components::TCustomBindGridLink* FBindGridLink;
	System::Byte FUpdateLock;
	System::Byte FLayoutLock;
	int FDefaultColumnWidth;
	bool __fastcall GetAutoActivate();
	void __fastcall SetAutoActivate(const bool Value);
	void __fastcall SetActive(const bool Value);
	void __fastcall InternalLayout();
	int __fastcall GetBufferCount();
	void __fastcall SetBufferCount(const int Value);
	void __fastcall SetDefaultColumnWidth(const int Value);
	
protected:
	virtual TBaseLinkGridToDataSourceColumns* __fastcall GetColumns() = 0 ;
	virtual System::_di_IInterface __fastcall GetGridColumnManagerFactory(const GUID &AGuid);
	virtual _di_ILinkGridToDataSourceControlManager __fastcall GetGridColumnManager();
	virtual void __fastcall Loaded();
	virtual void __fastcall ClearColumns(_di_ILinkGridToDataSourceControlManager AManager);
	virtual System::Classes::_di_IEditFormatLink __fastcall GetFormatLink(const System::UnicodeString AMemberName);
	void __fastcall BeginUpdate();
	void __fastcall CancelLayout();
	void __fastcall EndUpdate();
	bool __fastcall GetReadOnly();
	Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetDataSource();
	virtual bool __fastcall GetActive();
	bool __fastcall GetDefaultMembers();
	System::Classes::TComponentState __fastcall GetComponentState();
	TBaseLinkGridToDataSourceColumns* __fastcall CreateColumns();
	bool __fastcall AcquireLayoutLock();
	void __fastcall LayoutChanged();
	virtual void __fastcall InvalidateColumn(TBaseLinkGridToDataSourceColumn* AColumn);
	
public:
	__fastcall virtual TBaseLinkGridToDataSource(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBaseLinkGridToDataSource();
	void __fastcall BeginLayout();
	void __fastcall EndLayout();
	virtual bool __fastcall CanActivate(System::Classes::TComponent* Sender);
	virtual System::TArray__1<Data::Bind::Components::TCommonBindComponent*> __fastcall GetDelegates();
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender);
	__property Data::Bind::Components::TCustomBindGridLink* BindGridLink = {read=FBindGridLink};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property int BufferCount = {read=GetBufferCount, write=SetBufferCount, default=-1};
	__property bool AutoActivate = {read=GetAutoActivate, write=SetAutoActivate, default=1};
	__property int DefaultColumnWidth = {read=FDefaultColumnWidth, write=SetDefaultColumnWidth, default=64};
private:
	void *__ILinkGridToDataSource;	// ILinkGridToDataSource 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E14CC39A-D660-4801-9FFB-7CA7F2B6A99F}
	operator _di_ILinkGridToDataSource()
	{
		_di_ILinkGridToDataSource intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ILinkGridToDataSource*(void) { return (ILinkGridToDataSource*)&__ILinkGridToDataSource; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomLinkGridToDataSource : public TBaseLinkGridToDataSource
{
	typedef TBaseLinkGridToDataSource inherited;
	
	
public:
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TMemberKey
	{
	private:
		System::UnicodeString FMemberName;
		TBaseLinkGridToDataSourceColumn* FColumn;
		
	public:
		__fastcall TMemberKey(const System::UnicodeString AMemberName);
		__fastcall TMemberKey(TBaseLinkGridToDataSourceColumn* AColumn);
		TMemberKey() {}
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	
protected:
	System::Classes::TComponent* __fastcall GetControl();
	void __fastcall SetControl(System::Classes::TComponent* const Value);
	
private:
	System::Generics::Collections::TDictionary__2<TMemberKey,int>* FLinkGridColumnDescriptionsLookup;
	TLinkGridColumnDescriptions* FLinkGridColumnDescriptions;
	TLinkGridToDataSourceColumns* FLinkGridToDataSourceColumns;
	bool FDeprecatedAutoBufferCount;
	bool FUseEvalShortcuts;
	void __fastcall CreateDefaultGridColumns();
	void __fastcall CreateCollectionGridColumns();
	void __fastcall SetColumns(TLinkGridToDataSourceColumns* Value);
	TLinkGridColumnDescriptions* __fastcall CreateDefaultGridColumnDescriptions();
	TLinkGridColumnDescriptions* __fastcall CreateCollectionGridColumnDescriptions();
	TLinkGridColumnDescriptions* __fastcall CreateGridColumnDescriptions();
	void __fastcall OnListRefreshing(System::TObject* Sender);
	System::TArray__1<System::UnicodeString> __fastcall GetDataSetFields();
	void __fastcall ReadBoolean(System::Classes::TReader* Reader);
	void __fastcall ReadInteger(System::Classes::TReader* Reader);
	
protected:
	virtual System::Classes::_di_IEditFormatLink __fastcall GetFormatLink(const System::UnicodeString AMemberName);
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* Sender, System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	virtual TBaseLinkGridToDataSourceColumns* __fastcall GetColumns();
	virtual void __fastcall InvalidateColumn(TBaseLinkGridToDataSourceColumn* AColumn);
	virtual void __fastcall ClearColumns(_di_ILinkGridToDataSourceControlManager AManager);
	virtual bool __fastcall GetUseEvalShortcuts();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__fastcall virtual TCustomLinkGridToDataSource(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomLinkGridToDataSource();
	virtual bool __fastcall CanSetControlComponent(System::Classes::TComponent* Value);
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender);
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	virtual void __fastcall UpdateColumns();
	virtual bool __fastcall ColumnsHaveChanged();
	void __fastcall CreateGridColumns();
	__property System::Classes::TComponent* GridControl = {read=GetControl, write=SetControl};
	__property TLinkGridToDataSourceColumns* Columns = {read=FLinkGridToDataSourceColumns, write=SetColumns};
	__property bool AutoBufferCount = {read=FDeprecatedAutoBufferCount, write=FDeprecatedAutoBufferCount, nodefault};
	__property bool UseEvalShortcuts = {read=GetUseEvalShortcuts, write=FUseEvalShortcuts, default=1};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLinkGridToDataSource : public TCustomLinkGridToDataSource
{
	typedef TCustomLinkGridToDataSource inherited;
	
__published:
	__property DataSource;
	__property GridControl;
	__property AutoActivate = {default=1};
	__property Columns;
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
	__property DefaultColumnWidth = {default=64};
	__property UseEvalShortcuts = {default=1};
public:
	/* TCustomLinkGridToDataSource.Create */ inline __fastcall virtual TLinkGridToDataSource(System::Classes::TComponent* AOwner) : TCustomLinkGridToDataSource(AOwner) { }
	/* TCustomLinkGridToDataSource.Destroy */ inline __fastcall virtual ~TLinkGridToDataSource() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBaseLinkGridToDataSourceColumn : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FMemberName;
	Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetDataSource();
	TBaseLinkGridToDataSourceColumn* __fastcall GetParentColumn();
	void __fastcall SetFieldName(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall Initialize();
	_di_ILinkGridToDataSource __fastcall GetGridIntf();
	System::Classes::TComponent* __fastcall GetGrid();
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual void __fastcall SetIndex(int Value);
	
public:
	__fastcall virtual TBaseLinkGridToDataSourceColumn(System::Classes::TCollection* Collection);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall RestoreDefaults();
	__property Data::Bind::Components::TBaseLinkingBindSource* DataSource = {read=GetDataSource};
	__property TBaseLinkGridToDataSourceColumn* ParentColumn = {read=GetParentColumn};
	__property System::UnicodeString MemberName = {read=FMemberName, write=SetFieldName};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TBaseLinkGridToDataSourceColumn() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TBaseLinkGridToDataSourceColumnClass);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBaseLinkGridToDataSourceColumns : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
private:
	System::Classes::TComponent* FGrid;
	TBaseLinkGridToDataSourceColumn* __fastcall GetColumn(int Index);
	void __fastcall SetColumn(int Index, TBaseLinkGridToDataSourceColumn* Value);
	Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetDataSource();
	System::TArray__1<System::UnicodeString> __fastcall GetDataSourceMemberNames();
	
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	_di_ILinkGridToDataSource __fastcall GetGridIntf();
	
public:
	__fastcall virtual TBaseLinkGridToDataSourceColumns(System::Classes::TComponent* Grid, TBaseLinkGridToDataSourceColumnClass ColumnClass);
	HIDESBASE TBaseLinkGridToDataSourceColumn* __fastcall Add();
	bool __fastcall Updating();
	void __fastcall LoadFromFile(const System::UnicodeString Filename);
	void __fastcall LoadFromStream(System::Classes::TStream* S);
	void __fastcall RestoreDefaults();
	void __fastcall RebuildColumns();
	void __fastcall SaveToFile(const System::UnicodeString Filename);
	void __fastcall SaveToStream(System::Classes::TStream* S);
	__property System::Classes::TComponent* Grid = {read=FGrid};
	__property TBaseLinkGridToDataSourceColumn* BaseItems[int Index] = {read=GetColumn, write=SetColumn};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TBaseLinkGridToDataSourceColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TLinkGridColumnExpressionPair
{
private:
	System::UnicodeString FControlExpression;
	System::UnicodeString FSourceExpression;
	bool FCustom;
	
public:
	__fastcall TLinkGridColumnExpressionPair(const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, bool ACustom);
	__property System::UnicodeString ControlExpression = {read=FControlExpression};
	__property System::UnicodeString SourceExpression = {read=FSourceExpression};
	__property bool Custom = {read=FCustom};
	TLinkGridColumnExpressionPair() {}
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLinkGridColumnDescriptions : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TList__1<TLinkGridColumnDescription*>* FList;
	System::TArray__1<TLinkGridColumnDescription*> __fastcall GetList();
	int __fastcall GetCount();
	
public:
	__fastcall TLinkGridColumnDescriptions();
	__fastcall virtual ~TLinkGridColumnDescriptions();
	void __fastcall Add(TLinkGridColumnDescription* AItem);
	__property System::TArray__1<TLinkGridColumnDescription*> List = {read=GetList};
	__property int Count = {read=GetCount, nodefault};
	void __fastcall Clear();
	TLinkGridColumnDescription* __fastcall Extract(int AIndex);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLinkGridColumnDescription : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TComponent* FColumnControl;
	System::UnicodeString FColumnName;
	int FColumnIndex;
	System::UnicodeString FSourceMemberName;
	System::UnicodeString FControlMemberName;
	System::UnicodeString FColumnStyle;
	System::TArray__1<TLinkGridColumnExpressionPair> FFormatCellExpressions;
	System::TArray__1<TLinkGridColumnExpressionPair> FFormatColumnExpressions;
	System::TArray__1<TLinkGridColumnExpressionPair> FParseCellExpressions;
	
public:
	__fastcall TLinkGridColumnDescription(System::Classes::TComponent* AColumnControl, const System::UnicodeString AColumnName, int AColumnIndex, const System::UnicodeString AControlMemberName, const System::UnicodeString ASourceMemberName, const System::UnicodeString AColumnStyle, System::TArray__1<TLinkGridColumnExpressionPair> AFormatColumnExpressions, System::TArray__1<TLinkGridColumnExpressionPair> AFormatCellExpressions, System::TArray__1<TLinkGridColumnExpressionPair> AParseCellExpression);
	__property System::Classes::TComponent* ColumnControl = {read=FColumnControl};
	__property System::UnicodeString ColumnName = {read=FColumnName};
	__property int ColumnIndex = {read=FColumnIndex, nodefault};
	__property System::UnicodeString SourceMemberName = {read=FSourceMemberName};
	__property System::UnicodeString ControlMemberName = {read=FControlMemberName};
	__property System::UnicodeString ColumnStyle = {read=FColumnStyle};
	__property System::TArray__1<TLinkGridColumnExpressionPair> ParseCellExpression = {read=FParseCellExpressions};
	__property System::TArray__1<TLinkGridColumnExpressionPair> FormatCellExpressions = {read=FFormatCellExpressions};
	__property System::TArray__1<TLinkGridColumnExpressionPair> FormatColumnExpressions = {read=FFormatColumnExpressions};
	virtual bool __fastcall IsEqual(TLinkGridColumnDescription* const ADescription);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TLinkGridColumnDescription() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TCreateColumnDescription
{
private:
	Data::Bind::Components::TBaseLinkingBindSource* FDataSource;
	System::UnicodeString FHeader;
	bool FReadOnly;
	System::UnicodeString FMemberName;
	bool FVisible;
	int FWidth;
	int FTextWidth;
	Data::Bind::Components::TScopeMemberType FMemberType;
	System::UnicodeString FMemberGetter;
	System::UnicodeString FMemberSetter;
	System::UnicodeString FCustomFormat;
	System::UnicodeString FCustomParse;
	System::UnicodeString FColumnStyle;
	int FDecimalDigits;
	bool FShowThousandSeparator;
	System::Classes::TAlignment FAlignment;
	bool FDefaultAlignment;
	
public:
	__fastcall TCreateColumnDescription(TLinkGridToDataSourceColumn* AColumn)/* overload */;
	__fastcall TCreateColumnDescription(Data::Bind::Components::TBaseLinkingBindSource* ADataSource, const System::UnicodeString AMemberName)/* overload */;
	__property Data::Bind::Components::TBaseLinkingBindSource* DataSource = {read=FDataSource};
	__property System::UnicodeString Header = {read=FHeader, write=FHeader};
	__property System::UnicodeString MemberName = {read=FMemberName};
	__property bool Visible = {read=FVisible, write=FVisible};
	__property int Width = {read=FWidth, write=FWidth};
	__property int TextWidth = {read=FTextWidth, write=FTextWidth};
	__property bool ReadOnly = {read=FReadOnly, write=FReadOnly};
	__property Data::Bind::Components::TScopeMemberType MemberType = {read=FMemberType, write=FMemberType};
	__property System::UnicodeString MemberSetter = {read=FMemberSetter, write=FMemberSetter};
	__property System::UnicodeString MemberGetter = {read=FMemberGetter, write=FMemberGetter};
	__property System::UnicodeString CustomParse = {read=FCustomParse, write=FCustomParse};
	__property System::UnicodeString CustomFormat = {read=FCustomFormat, write=FCustomFormat};
	__property System::UnicodeString ColumnStyle = {read=FColumnStyle, write=FColumnStyle};
	__property int DecimalDigits = {read=FDecimalDigits, write=FDecimalDigits};
	__property bool ShowThousandSeparator = {read=FShowThousandSeparator, write=FShowThousandSeparator};
	__property System::Classes::TAlignment Alignment = {read=FAlignment, write=FAlignment};
	__property bool DefaultAlignment = {read=FDefaultAlignment, write=FDefaultAlignment};
	TCreateColumnDescription() {}
};


__interface  INTERFACE_UUID("{F631C178-78F7-4164-A532-6F335760A26A}") ILinkGridToDataSourceControlManager  : public System::IInterface 
{
	virtual int __fastcall GetDefaultColumnWidth() = 0 ;
	virtual void __fastcall SetDefaultColumnWidth(int AWidth) = 0 ;
	virtual void __fastcall BeginUpdate() = 0 ;
	virtual void __fastcall EndUpdate() = 0 ;
	virtual void __fastcall ClearColumns() = 0 ;
	virtual bool __fastcall CanAddColumn(TBaseLinkGridToDataSourceColumn* AColumn) = 0 /* overload */;
	virtual bool __fastcall CanAddColumn(Data::Bind::Components::TBaseLinkingBindSource* ADataSource, const System::UnicodeString AMemberName) = 0 /* overload */;
	virtual int __fastcall AddColumn(TBaseLinkGridToDataSourceColumn* AColumn) = 0 /* overload */;
	virtual int __fastcall AddColumn(Data::Bind::Components::TBaseLinkingBindSource* ADataSource, const System::UnicodeString AMemberName) = 0 /* overload */;
	virtual void __fastcall UpdateColumn(int AIndex, TBaseLinkGridToDataSourceColumn* AColumn) = 0 /* overload */;
	virtual void __fastcall UpdateColumn(int AIndex, Data::Bind::Components::TBaseLinkingBindSource* ADataSource, const System::UnicodeString AMemberName) = 0 /* overload */;
	virtual TLinkGridColumnDescription* __fastcall DescribeColumn(int AIndex, TBaseLinkGridToDataSourceColumn* AColumn) = 0 /* overload */;
	virtual TLinkGridColumnDescription* __fastcall DescribeColumn(int AIndex, Data::Bind::Components::TBaseLinkingBindSource* ADataSource, const System::UnicodeString AMemberName) = 0 /* overload */;
	__property int DefaultColumnWidth = {read=GetDefaultColumnWidth, write=SetDefaultColumnWidth};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLinkGridToDataSourceColumnFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual TLinkGridToDataSourceColumnFactory();
	virtual System::UnicodeString __fastcall FrameworkExt();
	virtual System::TArray__1<System::Classes::TComponentClass> __fastcall GridClasses();
	virtual bool __fastcall Supports(const GUID &AIntf, System::Classes::TComponent* AGrid) = 0 ;
	virtual System::TArray__1<System::UnicodeString> __fastcall UsesUnits() = 0 ;
	virtual System::_di_IInterface __fastcall CreateFactory(const GUID &AIntf, System::Classes::TComponent* AGrid) = 0 ;
	virtual System::TArray__1<System::UnicodeString> __fastcall GetColumnStyles();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TLinkGridToDataSourceColumnFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLinkGridToDataSourceColumnsEnumerator : public System::Classes::TCollectionEnumerator
{
	typedef System::Classes::TCollectionEnumerator inherited;
	
public:
	HIDESBASE TLinkGridToDataSourceColumn* __fastcall GetCurrent();
	__property TLinkGridToDataSourceColumn* Current = {read=GetCurrent};
public:
	/* TCollectionEnumerator.Create */ inline __fastcall TLinkGridToDataSourceColumnsEnumerator(System::Classes::TCollection* ACollection) : System::Classes::TCollectionEnumerator(ACollection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TLinkGridToDataSourceColumnsEnumerator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLinkGridToDataSourceColumns : public TBaseLinkGridToDataSourceColumns
{
	typedef TBaseLinkGridToDataSourceColumns inherited;
	
public:
	TLinkGridToDataSourceColumn* operator[](int I) { return this->Items[I]; }
	
private:
	HIDESBASE TLinkGridToDataSourceColumn* __fastcall GetItem(int I);
	HIDESBASE void __fastcall SetItem(int I, TLinkGridToDataSourceColumn* const Value);
	
public:
	HIDESBASE TLinkGridToDataSourceColumnsEnumerator* __fastcall GetEnumerator();
	HIDESBASE TLinkGridToDataSourceColumn* __fastcall Add();
	__property TLinkGridToDataSourceColumn* Items[int I] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TBaseLinkGridToDataSourceColumns.Create */ inline __fastcall virtual TLinkGridToDataSourceColumns(System::Classes::TComponent* Grid, TBaseLinkGridToDataSourceColumnClass ColumnClass) : TBaseLinkGridToDataSourceColumns(Grid, ColumnClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TLinkGridToDataSourceColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TLinkGridToDataSourceColumnValue : unsigned char { cvWidth, cvTextWidth, cvHeader, cvVisible, cvReadOnly, cvDecimalDigits, cvShowThousandSeparator, cvAlignment };

typedef System::Set<TLinkGridToDataSourceColumnValue, TLinkGridToDataSourceColumnValue::cvWidth, TLinkGridToDataSourceColumnValue::cvAlignment> TLinkGridToDataSourceColumnValues;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLinkGridToDataSourceColumn : public TBaseLinkGridToDataSourceColumn
{
	typedef TBaseLinkGridToDataSourceColumn inherited;
	
private:
	TLinkGridToDataSourceColumnValues FAssignedValues;
	System::UnicodeString FHeader;
	bool FVisible;
	bool FReadOnly;
	int FWidth;
	int FTextWidth;
	System::UnicodeString FCustomFormat;
	System::UnicodeString FCustomParse;
	System::UnicodeString FColumnStyle;
	int FDecimalDigits;
	bool FShowThousandSeparator;
	System::Classes::_di_IEditFormatLink FFormatLink;
	bool FFormatLinkInit;
	System::Classes::TAlignment FAlignment;
	int __fastcall GetWidth();
	bool __fastcall GetShowing();
	bool __fastcall GetReadOnly();
	bool __fastcall GetVisible();
	bool __fastcall IsHeaderStored();
	bool __fastcall IsWidthStored();
	void __fastcall SetHeader(const System::UnicodeString AValue);
	void __fastcall SetReadOnly(const bool AValue);
	void __fastcall SetVisible(const bool AValue);
	void __fastcall SetWidth(const int AValue);
	System::UnicodeString __fastcall GetHeader();
	void __fastcall SetCustomFormat(const System::UnicodeString AValue);
	void __fastcall SetCustomParse(const System::UnicodeString AValue);
	void __fastcall SetColumnStyle(const System::UnicodeString AValue);
	void __fastcall SetDecimalDigits(const int AValue);
	void __fastcall SetShowThousandSeparator(const bool AValue);
	bool __fastcall TryGetDefaultInfo();
	bool __fastcall IsVisibleStored();
	bool __fastcall IsReadonlyStored();
	int __fastcall GetTextWidth();
	bool __fastcall IsTextWidthStored();
	void __fastcall SetTextWidth(const int AValue);
	int __fastcall GetDecimalDigits();
	bool __fastcall IsDecimalDigitsStored();
	bool __fastcall GetShowThousandSeparator();
	bool __fastcall IsShowThousandSeparatorStored();
	System::Classes::TAlignment __fastcall GetAlignment();
	bool __fastcall IsAlignmentStored();
	void __fastcall SetAlignment(const System::Classes::TAlignment AValue);
	
protected:
	virtual void __fastcall Initialize();
	void __fastcall ResetDefaultInfo();
	
public:
	virtual void __fastcall RestoreDefaults();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property TLinkGridToDataSourceColumnValues AssignedValues = {read=FAssignedValues, nodefault};
	__property bool Showing = {read=GetShowing, nodefault};
	
__published:
	__property MemberName = {default=0};
	__property bool ReadOnly = {read=GetReadOnly, write=SetReadOnly, stored=IsReadonlyStored, nodefault};
	__property System::UnicodeString Header = {read=GetHeader, write=SetHeader, stored=IsHeaderStored};
	__property int Width = {read=GetWidth, write=SetWidth, stored=IsWidthStored, nodefault};
	__property int TextWidth = {read=GetTextWidth, write=SetTextWidth, stored=IsTextWidthStored, nodefault};
	__property bool Visible = {read=GetVisible, write=SetVisible, stored=IsVisibleStored, nodefault};
	__property System::UnicodeString CustomFormat = {read=FCustomFormat, write=SetCustomFormat};
	__property System::UnicodeString CustomParse = {read=FCustomParse, write=SetCustomParse};
	__property System::UnicodeString ColumnStyle = {read=FColumnStyle, write=SetColumnStyle};
	__property int DecimalDigits = {read=GetDecimalDigits, write=SetDecimalDigits, stored=IsDecimalDigitsStored, nodefault};
	__property bool ShowThousandSeparator = {read=GetShowThousandSeparator, write=SetShowThousandSeparator, stored=IsShowThousandSeparatorStored, nodefault};
	__property System::Classes::TAlignment Alignment = {read=GetAlignment, write=SetAlignment, stored=IsAlignmentStored, nodefault};
public:
	/* TBaseLinkGridToDataSourceColumn.Create */ inline __fastcall virtual TLinkGridToDataSourceColumn(System::Classes::TCollection* Collection) : TBaseLinkGridToDataSourceColumn(Collection) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TLinkGridToDataSourceColumn() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TLinkGridToDataSourceColumnFactoryClass);

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterLinkGridToDataSourceColumnFactory(TLinkGridToDataSourceColumnFactoryClass *AFactories, const int AFactories_High);
extern DELPHI_PACKAGE void __fastcall UnregisterLinkGridToDataSourceColumnFactory(TLinkGridToDataSourceColumnFactoryClass *AFactories, const int AFactories_High);
extern DELPHI_PACKAGE bool __fastcall GetIsLinkGridToDataSourceControl(System::Classes::TComponent* AGrid);
extern DELPHI_PACKAGE System::TArray__1<System::UnicodeString> __fastcall GetLinkGridToDataSourceControlUsesUnits(System::Classes::TComponent* AGrid);
extern DELPHI_PACKAGE System::TArray__1<System::UnicodeString> __fastcall GetLinkGridToDataSourceControlColumnStyles(System::Classes::TComponent* AGrid);
extern DELPHI_PACKAGE System::TArray__1<System::Classes::TComponentClass> __fastcall GetGridClasses(const System::UnicodeString AFrameworkExt);
}	/* namespace Grid */
}	/* namespace Bind */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND_GRID)
using namespace Data::Bind::Grid;
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
#endif	// Data_Bind_GridHPP
