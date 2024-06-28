// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Fmx.Bind.DBLinks.pas' rev: 34.00 (Windows)

#ifndef Fmx_Bind_DblinksHPP
#define Fmx_Bind_DblinksHPP

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
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Controls.hpp>
#include <System.Bindings.Outputs.hpp>
#include <Data.Bind.DBLinks.hpp>
#include <Data.DB.hpp>
#include <FMX.Grid.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Fmx.Bind.DBLinks"

namespace Fmx
{
namespace Bind
{
namespace Dblinks
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBaseBindDBFieldControlLink;
class DELPHICLASS TCustomBindDBEditLink;
class DELPHICLASS TBindDBEditLink;
class DELPHICLASS TCustomBindDBTextLink;
class DELPHICLASS TBindDBTextLink;
class DELPHICLASS TCustomBindDBListLink;
class DELPHICLASS TBindDBListLink;
class DELPHICLASS TCustomBindDBImageLink;
class DELPHICLASS TBindDBImageLink;
class DELPHICLASS TCustomBindDBMemoLink;
class DELPHICLASS TBindDBMemoLink;
class DELPHICLASS TCustomBindDBCheckLink;
class DELPHICLASS TBindDBCheckLink;
class DELPHICLASS TBaseBindDBGridControlLink;
class DELPHICLASS TDBGridLinkColumnsEnumerator;
class DELPHICLASS TDBGridLinkColumns;
class DELPHICLASS TDBGridLinkColumn;
class DELPHICLASS TCustomBindDBGridLink;
class DELPHICLASS TFMXDBGridLinkColumns;
class DELPHICLASS TBindDBGridLink;
class DELPHICLASS TBindDBStringGridColumnFactory;
struct TCreateColumnDescription;
class DELPHICLASS TBindDBStringGridColumnCreator;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBaseBindDBFieldControlLink : public Data::Bind::Dblinks::TBaseBindDBFieldLink
{
	typedef Data::Bind::Dblinks::TBaseBindDBFieldLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetControlMemberName();
	Fmx::Controls::TStyledControl* __fastcall GetControl();
	void __fastcall SetControl(Fmx::Controls::TStyledControl* const Value);
	
public:
	__property System::UnicodeString ControlMemberName = {read=GetControlMemberName};
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TBaseBindDBFieldControlLink(System::Classes::TComponent* AOwner) : Data::Bind::Dblinks::TBaseBindDBFieldLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TBaseBindDBFieldControlLink() { }
	
};


class PASCALIMPLEMENTATION TCustomBindDBEditLink : public TBaseBindDBFieldControlLink
{
	typedef TBaseBindDBFieldControlLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetControlMemberName();
	
public:
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	__property Fmx::Controls::TStyledControl* EditControl = {read=GetControl, write=SetControl};
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TCustomBindDBEditLink(System::Classes::TComponent* AOwner) : TBaseBindDBFieldControlLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TCustomBindDBEditLink() { }
	
};


class PASCALIMPLEMENTATION TBindDBEditLink : public TCustomBindDBEditLink
{
	typedef TCustomBindDBEditLink inherited;
	
__published:
	__property DataSource;
	__property FieldName = {default=0};
	__property EditControl;
	__property AutoActivate = {default=1};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TBindDBEditLink(System::Classes::TComponent* AOwner) : TCustomBindDBEditLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TBindDBEditLink() { }
	
};


class PASCALIMPLEMENTATION TCustomBindDBTextLink : public TBaseBindDBFieldControlLink
{
	typedef TBaseBindDBFieldControlLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetControlMemberName();
	
public:
	virtual bool __fastcall RequiresControlHandler();
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	__property Fmx::Controls::TStyledControl* TextControl = {read=GetControl, write=SetControl};
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TCustomBindDBTextLink(System::Classes::TComponent* AOwner) : TBaseBindDBFieldControlLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TCustomBindDBTextLink() { }
	
};


class PASCALIMPLEMENTATION TBindDBTextLink : public TCustomBindDBTextLink
{
	typedef TCustomBindDBTextLink inherited;
	
__published:
	__property DataSource;
	__property FieldName = {default=0};
	__property TextControl;
	__property AutoActivate = {default=1};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TBindDBTextLink(System::Classes::TComponent* AOwner) : TCustomBindDBTextLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TBindDBTextLink() { }
	
};


class PASCALIMPLEMENTATION TCustomBindDBListLink : public TBaseBindDBFieldControlLink
{
	typedef TBaseBindDBFieldControlLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetControlMemberName();
	
public:
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	__property Fmx::Controls::TStyledControl* ListControl = {read=GetControl, write=SetControl};
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TCustomBindDBListLink(System::Classes::TComponent* AOwner) : TBaseBindDBFieldControlLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TCustomBindDBListLink() { }
	
};


class PASCALIMPLEMENTATION TBindDBListLink : public TCustomBindDBListLink
{
	typedef TCustomBindDBListLink inherited;
	
__published:
	__property DataSource;
	__property FieldName = {default=0};
	__property ListControl;
	__property AutoActivate = {default=1};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TBindDBListLink(System::Classes::TComponent* AOwner) : TCustomBindDBListLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TBindDBListLink() { }
	
};


class PASCALIMPLEMENTATION TCustomBindDBImageLink : public TBaseBindDBFieldControlLink
{
	typedef TBaseBindDBFieldControlLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetControlMemberName();
	
public:
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	__property Fmx::Controls::TStyledControl* ImageControl = {read=GetControl, write=SetControl};
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TCustomBindDBImageLink(System::Classes::TComponent* AOwner) : TBaseBindDBFieldControlLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TCustomBindDBImageLink() { }
	
};


class PASCALIMPLEMENTATION TBindDBImageLink : public TCustomBindDBImageLink
{
	typedef TCustomBindDBImageLink inherited;
	
__published:
	__property DataSource;
	__property FieldName = {default=0};
	__property ImageControl;
	__property AutoActivate = {default=1};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TBindDBImageLink(System::Classes::TComponent* AOwner) : TCustomBindDBImageLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TBindDBImageLink() { }
	
};


class PASCALIMPLEMENTATION TCustomBindDBMemoLink : public TBaseBindDBFieldControlLink
{
	typedef TBaseBindDBFieldControlLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetControlMemberName();
	
public:
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	__property Fmx::Controls::TStyledControl* MemoControl = {read=GetControl, write=SetControl};
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TCustomBindDBMemoLink(System::Classes::TComponent* AOwner) : TBaseBindDBFieldControlLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TCustomBindDBMemoLink() { }
	
};


class PASCALIMPLEMENTATION TBindDBMemoLink : public TCustomBindDBMemoLink
{
	typedef TCustomBindDBMemoLink inherited;
	
__published:
	__property DataSource;
	__property FieldName = {default=0};
	__property MemoControl;
	__property AutoActivate = {default=1};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TBindDBMemoLink(System::Classes::TComponent* AOwner) : TCustomBindDBMemoLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TBindDBMemoLink() { }
	
};


class PASCALIMPLEMENTATION TCustomBindDBCheckLink : public TBaseBindDBFieldControlLink
{
	typedef TBaseBindDBFieldControlLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetControlMemberName();
	
public:
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	__property Fmx::Controls::TStyledControl* CheckControl = {read=GetControl, write=SetControl};
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TCustomBindDBCheckLink(System::Classes::TComponent* AOwner) : TBaseBindDBFieldControlLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TCustomBindDBCheckLink() { }
	
};


class PASCALIMPLEMENTATION TBindDBCheckLink : public TCustomBindDBCheckLink
{
	typedef TCustomBindDBCheckLink inherited;
	
__published:
	__property DataSource;
	__property FieldName = {default=0};
	__property CheckControl;
	__property AutoActivate = {default=1};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TBaseBindDBFieldLink.Create */ inline __fastcall virtual TBindDBCheckLink(System::Classes::TComponent* AOwner) : TCustomBindDBCheckLink(AOwner) { }
	/* TBaseBindDBFieldLink.Destroy */ inline __fastcall virtual ~TBindDBCheckLink() { }
	
};


class PASCALIMPLEMENTATION TBaseBindDBGridControlLink : public Data::Bind::Dblinks::TBaseBindDBGridLink
{
	typedef Data::Bind::Dblinks::TBaseBindDBGridLink inherited;
	
protected:
	Fmx::Controls::TStyledControl* __fastcall GetControl();
	void __fastcall SetControl(Fmx::Controls::TStyledControl* const Value);
public:
	/* TBaseBindDBGridLink.Create */ inline __fastcall virtual TBaseBindDBGridControlLink(System::Classes::TComponent* AOwner) : Data::Bind::Dblinks::TBaseBindDBGridLink(AOwner) { }
	/* TBaseBindDBGridLink.Destroy */ inline __fastcall virtual ~TBaseBindDBGridControlLink() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBGridLinkColumnsEnumerator : public System::Classes::TCollectionEnumerator
{
	typedef System::Classes::TCollectionEnumerator inherited;
	
public:
	HIDESBASE TDBGridLinkColumn* __fastcall GetCurrent();
	__property TDBGridLinkColumn* Current = {read=GetCurrent};
public:
	/* TCollectionEnumerator.Create */ inline __fastcall TDBGridLinkColumnsEnumerator(System::Classes::TCollection* ACollection) : System::Classes::TCollectionEnumerator(ACollection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBGridLinkColumnsEnumerator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBGridLinkColumns : public Data::Bind::Dblinks::TBaseDBGridLinkColumns
{
	typedef Data::Bind::Dblinks::TBaseDBGridLinkColumns inherited;
	
public:
	TDBGridLinkColumn* operator[](int I) { return this->Items[I]; }
	
private:
	HIDESBASE TDBGridLinkColumn* __fastcall GetItem(int I);
	HIDESBASE void __fastcall SetItem(int I, TDBGridLinkColumn* const Value);
	
public:
	HIDESBASE TDBGridLinkColumnsEnumerator* __fastcall GetEnumerator();
	__property TDBGridLinkColumn* Items[int I] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TBaseDBGridLinkColumns.Create */ inline __fastcall virtual TDBGridLinkColumns(System::Classes::TComponent* Grid, Data::Bind::Dblinks::TBaseDBGridLinkColumnClass ColumnClass) : Data::Bind::Dblinks::TBaseDBGridLinkColumns(Grid, ColumnClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TDBGridLinkColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TDBGridLinkColumnValue : unsigned char { cvWidth, cvReadOnly, cvHeader };

typedef System::Set<TDBGridLinkColumnValue, TDBGridLinkColumnValue::cvWidth, TDBGridLinkColumnValue::cvHeader> TDBGridLinkColumnValues;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBGridLinkColumn : public Data::Bind::Dblinks::TBaseDBGridLinkColumn
{
	typedef Data::Bind::Dblinks::TBaseDBGridLinkColumn inherited;
	
private:
	TDBGridLinkColumnValues FAssignedValues;
	System::UnicodeString FHeader;
	bool FVisible;
	bool FReadOnly;
	int FWidth;
	System::UnicodeString FStyleLookup;
	int __fastcall GetWidth();
	bool __fastcall GetShowing();
	bool __fastcall GetReadOnly();
	bool __fastcall GetVisible();
	bool __fastcall IsHeaderStored();
	bool __fastcall IsReadOnlyStored();
	bool __fastcall IsWidthStored();
	void __fastcall SetHeader(const System::UnicodeString Value);
	void __fastcall SetReadOnly(const bool Value);
	void __fastcall SetVisible(const bool Value);
	void __fastcall SetWidth(const int Value);
	System::UnicodeString __fastcall DefaultHeader();
	int __fastcall DefaultWidth();
	System::UnicodeString __fastcall GetHeader();
	bool __fastcall DefaultReadOnly();
	void __fastcall SetStyleLookup(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall Initialize();
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall RestoreDefaults();
	__property TDBGridLinkColumnValues AssignedValues = {read=FAssignedValues, nodefault};
	__property bool Showing = {read=GetShowing, nodefault};
	
__published:
	__property FieldName = {default=0};
	__property bool ReadOnly = {read=GetReadOnly, write=SetReadOnly, stored=IsReadOnlyStored, nodefault};
	__property System::UnicodeString Header = {read=GetHeader, write=SetHeader, stored=IsHeaderStored};
	__property int Width = {read=GetWidth, write=SetWidth, stored=IsWidthStored, nodefault};
	__property bool Visible = {read=GetVisible, write=SetVisible, nodefault};
	__property System::UnicodeString StyleLookup = {read=FStyleLookup, write=SetStyleLookup};
public:
	/* TBaseDBGridLinkColumn.Create */ inline __fastcall virtual TDBGridLinkColumn(System::Classes::TCollection* Collection) : Data::Bind::Dblinks::TBaseDBGridLinkColumn(Collection) { }
	/* TBaseDBGridLinkColumn.Destroy */ inline __fastcall virtual ~TDBGridLinkColumn() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TCustomBindDBGridLink : public TBaseBindDBGridControlLink
{
	typedef TBaseBindDBGridControlLink inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::TObject*,int>* FColumnDescriptionsLookup;
	System::Generics::Collections::TList__1<Data::Bind::Dblinks::TDBGridLinkColumnDescription>* FColumnDescriptions;
	TDBGridLinkColumns* FColumns;
	bool FDeprecatedAutoBufferCount;
	void __fastcall CreateDefaultGridColumns();
	void __fastcall CreateCollectionGridColumns();
	void __fastcall SetColumns(TDBGridLinkColumns* Value);
	bool __fastcall ColumnsHaveChanged();
#ifndef _WIN64
	System::DynamicArray<Data::Bind::Dblinks::TDBGridLinkColumnDescription> __fastcall CreateDefaultGridColumnDescriptions();
	System::DynamicArray<Data::Bind::Dblinks::TDBGridLinkColumnDescription> __fastcall CreateCollectionGridColumnDescriptions();
	System::DynamicArray<Data::Bind::Dblinks::TDBGridLinkColumnDescription> __fastcall CreateGridColumnDescriptions();
#else /* _WIN64 */
	System::TArray__1<Data::Bind::Dblinks::TDBGridLinkColumnDescription> __fastcall CreateDefaultGridColumnDescriptions();
	System::TArray__1<Data::Bind::Dblinks::TDBGridLinkColumnDescription> __fastcall CreateCollectionGridColumnDescriptions();
	System::TArray__1<Data::Bind::Dblinks::TDBGridLinkColumnDescription> __fastcall CreateGridColumnDescriptions();
#endif /* _WIN64 */
	void __fastcall OnListRefreshing(System::TObject* Sender);
	void __fastcall ReadBoolean(System::Classes::TReader* Reader);
	void __fastcall ReadInteger(System::Classes::TReader* Reader);
	
protected:
	virtual Data::Bind::Dblinks::TBaseDBGridLinkColumns* __fastcall GetColumns();
	virtual void __fastcall InvalidateColumn(Data::Bind::Dblinks::TBaseDBGridLinkColumn* AColumn);
	virtual void __fastcall InvalidateField(Data::Db::TField* AField);
	virtual void __fastcall ClearColumns(Data::Bind::Dblinks::_di_IBindDBGridLinkControlManager AManager);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__fastcall virtual TCustomBindDBGridLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindDBGridLink();
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender);
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	virtual void __fastcall UpdateColumns();
	void __fastcall CreateGridColumns();
	__property Fmx::Controls::TStyledControl* GridControl = {read=GetControl, write=SetControl};
	__property TDBGridLinkColumns* Columns = {read=FColumns, write=SetColumns};
	__property bool AutoBufferCount = {read=FDeprecatedAutoBufferCount, write=FDeprecatedAutoBufferCount, nodefault};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFMXDBGridLinkColumns : public TDBGridLinkColumns
{
	typedef TDBGridLinkColumns inherited;
	
public:
	/* TBaseDBGridLinkColumns.Create */ inline __fastcall virtual TFMXDBGridLinkColumns(System::Classes::TComponent* Grid, Data::Bind::Dblinks::TBaseDBGridLinkColumnClass ColumnClass) : TDBGridLinkColumns(Grid, ColumnClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TFMXDBGridLinkColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TBindDBGridLink : public TCustomBindDBGridLink
{
	typedef TCustomBindDBGridLink inherited;
	
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
public:
	/* TCustomBindDBGridLink.Create */ inline __fastcall virtual TBindDBGridLink(System::Classes::TComponent* AOwner) : TCustomBindDBGridLink(AOwner) { }
	/* TCustomBindDBGridLink.Destroy */ inline __fastcall virtual ~TBindDBGridLink() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindDBStringGridColumnFactory : public Data::Bind::Dblinks::TBindDBColumnFactory
{
	typedef Data::Bind::Dblinks::TBindDBColumnFactory inherited;
	
public:
	__fastcall virtual TBindDBStringGridColumnFactory();
	virtual bool __fastcall Supports(const GUID &AIntf, System::Classes::TComponent* AGrid);
	virtual System::_di_IInterface __fastcall CreateFactory(const GUID &AIntf, System::Classes::TComponent* AGrid);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindDBStringGridColumnFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TCreateColumnDescription
{
private:
	Data::Db::TField* FField;
	System::UnicodeString FHeader;
	bool FReadOnly;
	System::UnicodeString FFieldName;
	bool FVisible;
	int FWidth;
	System::UnicodeString FStyleLookup;
	
public:
	__fastcall TCreateColumnDescription(Data::Db::TField* AField)/* overload */;
	__fastcall TCreateColumnDescription(TDBGridLinkColumn* AColumn)/* overload */;
	__property Data::Db::TField* Field = {read=FField};
	__property System::UnicodeString Header = {read=FHeader};
	__property System::UnicodeString FieldName = {read=FFieldName};
	__property bool Visible = {read=FVisible};
	__property int Width = {read=FWidth};
	__property System::UnicodeString StyleLookup = {read=FStyleLookup};
	__property bool ReadOnly = {read=FReadOnly};
	TCreateColumnDescription() {}
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindDBStringGridColumnCreator : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Fmx::Grid::TStringGrid* FStringGrid;
	Data::Bind::Dblinks::TDBGridLinkColumnDescription __fastcall CreateColumnDescription(int AIndex, const TCreateColumnDescription &ADescription);
	int __fastcall AddColumn(const TCreateColumnDescription &ADescription)/* overload */;
	void __fastcall UpdateColumn(const TCreateColumnDescription &ACreateDescription, const Data::Bind::Dblinks::TDBGridLinkColumnDescription &ADescription)/* overload */;
	Data::Bind::Dblinks::TDBGridLinkColumnDescription __fastcall DescribeColumn(int AIndex, const TCreateColumnDescription &ADescription)/* overload */;
	
public:
	__fastcall TBindDBStringGridColumnCreator(Fmx::Grid::TStringGrid* AGrid);
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	bool __fastcall CanAddColumn(Data::Db::TField* AField)/* overload */;
	bool __fastcall CanAddColumn(Data::Bind::Dblinks::TBaseDBGridLinkColumn* AColumn)/* overload */;
	void __fastcall ClearColumns();
	Data::Bind::Dblinks::TDBGridLinkColumnDescription __fastcall DescribeColumn(int AIndex, Data::Bind::Dblinks::TBaseDBGridLinkColumn* AColumn)/* overload */;
	Data::Bind::Dblinks::TDBGridLinkColumnDescription __fastcall DescribeColumn(int AIndex, Data::Db::TField* AField)/* overload */;
	int __fastcall AddColumn(Data::Bind::Dblinks::TBaseDBGridLinkColumn* AColumn)/* overload */;
	int __fastcall AddColumn(Data::Db::TField* AField)/* overload */;
	void __fastcall UpdateColumn(Data::Bind::Dblinks::TBaseDBGridLinkColumn* AColumn, const Data::Bind::Dblinks::TDBGridLinkColumnDescription &ADescription)/* overload */;
	void __fastcall UpdateColumn(Data::Db::TField* AField, const Data::Bind::Dblinks::TDBGridLinkColumnDescription &ADescription)/* overload */;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindDBStringGridColumnCreator() { }
	
private:
	void *__IBindDBGridLinkControlManager;	// Data::Bind::Dblinks::IBindDBGridLinkControlManager 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F631C178-78F7-4164-A532-6F335760A26A}
	operator Data::Bind::Dblinks::_di_IBindDBGridLinkControlManager()
	{
		Data::Bind::Dblinks::_di_IBindDBGridLinkControlManager intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Dblinks::IBindDBGridLinkControlManager*(void) { return (Data::Bind::Dblinks::IBindDBGridLinkControlManager*)&__IBindDBGridLinkControlManager; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dblinks */
}	/* namespace Bind */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_BIND_DBLINKS)
using namespace Fmx::Bind::Dblinks;
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
#endif	// Fmx_Bind_DblinksHPP
