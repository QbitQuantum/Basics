// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.DBWeb.pas' rev: 34.00 (Windows)

#ifndef Web_DbwebHPP
#define Web_DbwebHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <Data.DB.hpp>
#include <Web.HTTPProd.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Dbweb
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSTableProducerEditor;
class DELPHICLASS THTTPDataLink;
class DELPHICLASS THTMLTableColumn;
class DELPHICLASS THTMLTableColumns;
class DELPHICLASS TDSTableProducer;
class DELPHICLASS TDataSetTableProducer;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSTableProducerEditor : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDSTableProducer* FDSTableProducer;
	Data::Db::TDataSource* __fastcall GetDataSource();
	void __fastcall SetDataSource(Data::Db::TDataSource* DataSource);
	
public:
	__fastcall TDSTableProducerEditor(TDSTableProducer* DSTableProducer);
	__fastcall virtual ~TDSTableProducerEditor();
	virtual void __fastcall Changed();
	virtual void __fastcall PostChange();
	__property TDSTableProducer* DSTableProducer = {read=FDSTableProducer};
	__property Data::Db::TDataSource* DataSource = {read=GetDataSource, write=SetDataSource};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION THTTPDataLink : public Data::Db::TDataLink
{
	typedef Data::Db::TDataLink inherited;
	
private:
	TDSTableProducer* FDSTableProducer;
	int FFieldCount;
	int FFieldMapSize;
	void *FFieldMap;
	bool FModified;
	bool FSparseMap;
	bool __fastcall GetDefaultFields();
	Data::Db::TField* __fastcall GetFields(int I);
	
protected:
	virtual void __fastcall ActiveChanged();
	virtual void __fastcall DataSetChanged();
	virtual void __fastcall DataSetScrolled(int Distance);
	virtual void __fastcall FocusControl(Data::Db::TFieldRef Field);
	virtual void __fastcall EditingChanged();
	virtual void __fastcall LayoutChanged();
	virtual void __fastcall RecordChanged(Data::Db::TField* Field);
	virtual void __fastcall UpdateData();
	int __fastcall GetMappedIndex(int ColIndex);
	
public:
	__fastcall THTTPDataLink(TDSTableProducer* DSTableProducer);
	__fastcall virtual ~THTTPDataLink();
	bool __fastcall AddMapping(const System::UnicodeString FieldName);
	void __fastcall ClearMapping();
	void __fastcall Modified();
	void __fastcall Reset();
	__property bool DefaultFields = {read=GetDefaultFields, nodefault};
	__property int FieldCount = {read=FFieldCount, nodefault};
	__property Data::Db::TField* Fields[int I] = {read=GetFields};
	__property bool SparseMap = {read=FSparseMap, write=FSparseMap, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION THTMLTableColumn : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	Data::Db::TField* FField;
	System::UnicodeString FFieldName;
	Web::Httpprod::THTMLAlign FAlign;
	Web::Httpprod::THTMLBgColor FBgColor;
	System::UnicodeString FCustom;
	Web::Httpprod::THTMLVAlign FVAlign;
	Web::Httpprod::THTMLTableHeaderAttributes* FTitle;
	Data::Db::TField* __fastcall GetField();
	TDSTableProducer* __fastcall GetTableProducer();
	void __fastcall SetAlign(Web::Httpprod::THTMLAlign Value);
	void __fastcall SetBgColor(const Web::Httpprod::THTMLBgColor Value);
	void __fastcall SetCustom(const System::UnicodeString Value);
	void __fastcall SetField(Data::Db::TField* Value);
	void __fastcall SetFieldName(const System::UnicodeString Value);
	void __fastcall SetTitle(Web::Httpprod::THTMLTableHeaderAttributes* Value);
	void __fastcall SetVAlign(Web::Httpprod::THTMLVAlign Value);
	void __fastcall TitleChanged(System::TObject* Sender);
	
protected:
	TDSTableProducer* __fastcall GeTDSTableProducer();
	virtual System::UnicodeString __fastcall GetDisplayName();
	bool __fastcall IsStored();
	
public:
	__fastcall virtual THTMLTableColumn(System::Classes::TCollection* Collection);
	__fastcall virtual ~THTMLTableColumn();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	void __fastcall RestoreDefaults();
	void __fastcall Update();
	__property Data::Db::TField* Field = {read=GetField, write=SetField};
	__property TDSTableProducer* DSTableProducer = {read=GetTableProducer};
	
__published:
	__property Web::Httpprod::THTMLAlign Align = {read=FAlign, write=SetAlign, default=0};
	__property Web::Httpprod::THTMLBgColor BgColor = {read=FBgColor, write=SetBgColor};
	__property System::UnicodeString Custom = {read=FCustom, write=SetCustom};
	__property System::UnicodeString FieldName = {read=FFieldName, write=SetFieldName};
	__property Web::Httpprod::THTMLTableHeaderAttributes* Title = {read=FTitle, write=SetTitle};
	__property Web::Httpprod::THTMLVAlign VAlign = {read=FVAlign, write=SetVAlign, default=0};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* THTMLTableColumnClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, THTMLTableColumnClass);
#endif /* _WIN64 */

enum DECLSPEC_DENUM THTMLColumnState : unsigned char { csDefault, csCustom };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION THTMLTableColumns : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	THTMLTableColumn* operator[](int Index) { return this->Items[Index]; }
	
private:
	TDSTableProducer* FDSTableProducer;
	THTMLTableColumn* __fastcall GetColumn(int Index);
	THTMLColumnState __fastcall GetState();
	void __fastcall SetColumn(int Index, THTMLTableColumn* Value);
	void __fastcall SetState(THTMLColumnState Value);
	
protected:
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	
public:
	__fastcall THTMLTableColumns(TDSTableProducer* DSTableProducer, THTMLTableColumnClass ColumnClass);
	HIDESBASE THTMLTableColumn* __fastcall Add();
	void __fastcall RestoreDefaults();
	void __fastcall RebuildColumns();
	__property THTMLColumnState State = {read=GetState, write=SetState, nodefault};
	__property TDSTableProducer* DSTableProducer = {read=FDSTableProducer};
	__property THTMLTableColumn* Items[int Index] = {read=GetColumn, write=SetColumn/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~THTMLTableColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM THTMLCaptionAlignment : unsigned char { caDefault, caTop, caBottom };

typedef void __fastcall (__closure *TCreateContentEvent)(System::TObject* Sender, bool &Continue);

typedef void __fastcall (__closure *THTMLGetTableCaptionEvent)(System::TObject* Sender, System::UnicodeString &Caption, THTMLCaptionAlignment &Alignment);

typedef void __fastcall (__closure *THTMLFormatCellEvent)(System::TObject* Sender, int CellRow, int CellColumn, Web::Httpprod::THTMLBgColor &BgColor, Web::Httpprod::THTMLAlign &Align, Web::Httpprod::THTMLVAlign &VAlign, System::UnicodeString &CustomAttrs, System::UnicodeString &CellData);

typedef void __fastcall (__closure *THTMLDataSetEmpty)(System::TObject* Sender, bool &Continue);

class PASCALIMPLEMENTATION TDSTableProducer : public Web::Httpapp::TCustomContentProducer
{
	typedef Web::Httpapp::TCustomContentProducer inherited;
	
private:
	System::UnicodeString FCaption;
	THTMLCaptionAlignment FCaptionAlignment;
	THTTPDataLink* FDataLink;
	Data::Db::TDataSource* FInternalDataSource;
	TDSTableProducerEditor* FEditor;
	THTMLTableColumns* FColumns;
	System::Classes::TStrings* FHeader;
	System::Classes::TStrings* FFooter;
	int FMaxRows;
	bool FModified;
	int FLayoutLock;
	int FUpdateLock;
	Web::Httpprod::THTMLTableRowAttributes* FRowAttributes;
	Web::Httpprod::THTMLTableAttributes* FTableAttributes;
	TCreateContentEvent FOnCreateContent;
	THTMLFormatCellEvent FOnFormatCell;
	THTMLGetTableCaptionEvent FOnGetTableCaption;
	void __fastcall AttributeChanged(System::TObject* Sender);
	void __fastcall Changed();
	void __fastcall InternalLayout();
	void __fastcall SetCaption(const System::UnicodeString Value);
	void __fastcall SetCaptionAlignment(THTMLCaptionAlignment Value);
	void __fastcall SetFooter(System::Classes::TStrings* Value);
	void __fastcall SetHeader(System::Classes::TStrings* Value);
	void __fastcall SetMaxRows(int Value);
	void __fastcall SetRowAttributes(Web::Httpprod::THTMLTableRowAttributes* Value);
	void __fastcall SetTableAttributes(Web::Httpprod::THTMLTableAttributes* Value);
	
protected:
	bool __fastcall AcquireLayoutLock();
	void __fastcall BeginLayout();
	DYNAMIC System::UnicodeString __fastcall ColumnHeader();
	void __fastcall DefineFieldMap();
	bool __fastcall DoCreateContent();
	DYNAMIC void __fastcall DoFormatCell(int CellRow, int CellColumn, Web::Httpprod::THTMLBgColor &BgColor, Web::Httpprod::THTMLAlign &Align, Web::Httpprod::THTMLVAlign &VAlign, System::UnicodeString &CustomAttrs, System::UnicodeString &CellData);
	DYNAMIC void __fastcall DoGetCaption(System::UnicodeString &TableCaption, THTMLCaptionAlignment &CaptionAlign);
	void __fastcall EndLayout();
	DYNAMIC System::UnicodeString __fastcall FormatCell(int CellRow, int CellColumn, System::UnicodeString CellData, const System::UnicodeString Tag, const Web::Httpprod::THTMLBgColor BgColor, Web::Httpprod::THTMLAlign Align, Web::Httpprod::THTMLVAlign VAlign, const System::UnicodeString Custom);
	virtual Data::Db::TDataSet* __fastcall GetDataSet() = 0 ;
	Data::Db::TDataSource* __fastcall GetDataSource();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall LayoutChanged();
	void __fastcall LinkActive(bool Value);
	DYNAMIC System::UnicodeString __fastcall RowHeader();
	void __fastcall SetColumns(THTMLTableColumns* Value);
	virtual void __fastcall SetDataSet(Data::Db::TDataSet* ADataSet) = 0 ;
	void __fastcall SetDataSource(Data::Db::TDataSource* Value);
	bool __fastcall StoreColumns();
	DYNAMIC System::UnicodeString __fastcall TableHeader();
	DYNAMIC System::UnicodeString __fastcall TableCaption();
	__property THTTPDataLink* DataLink = {read=FDataLink};
	__property Data::Db::TDataSource* DataSource = {read=GetDataSource, write=SetDataSource};
	__property Data::Db::TDataSource* InternalDataSource = {read=FInternalDataSource};
	__property TCreateContentEvent OnCreateContent = {read=FOnCreateContent, write=FOnCreateContent};
	__property THTMLFormatCellEvent OnFormatCell = {read=FOnFormatCell, write=FOnFormatCell};
	__property THTMLGetTableCaptionEvent OnGetTableCaption = {read=FOnGetTableCaption, write=FOnGetTableCaption};
	
public:
	__fastcall virtual TDSTableProducer(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSTableProducer();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	__property System::UnicodeString Caption = {read=FCaption, write=SetCaption};
	__property THTMLCaptionAlignment CaptionAlignment = {read=FCaptionAlignment, write=SetCaptionAlignment, default=0};
	__property THTMLTableColumns* Columns = {read=FColumns, write=SetColumns, stored=StoreColumns};
	__property Data::Db::TDataSet* DataSet = {read=GetDataSet, write=SetDataSet};
	__property TDSTableProducerEditor* Editor = {read=FEditor, write=FEditor};
	__property System::Classes::TStrings* Footer = {read=FFooter, write=SetFooter};
	__property System::Classes::TStrings* Header = {read=FHeader, write=SetHeader};
	__property int MaxRows = {read=FMaxRows, write=SetMaxRows, default=20};
	__property Web::Httpprod::THTMLTableRowAttributes* RowAttributes = {read=FRowAttributes, write=SetRowAttributes};
	__property Web::Httpprod::THTMLTableAttributes* TableAttributes = {read=FTableAttributes, write=SetTableAttributes};
};


class PASCALIMPLEMENTATION TDataSetTableProducer : public TDSTableProducer
{
	typedef TDSTableProducer inherited;
	
private:
	Data::Db::TDataSet* FDataSet;
	
protected:
	virtual Data::Db::TDataSet* __fastcall GetDataSet();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall SetDataSet(Data::Db::TDataSet* ADataSet);
	
public:
	virtual System::UnicodeString __fastcall Content();
	
__published:
	__property Caption = {default=0};
	__property CaptionAlignment = {default=0};
	__property Columns;
	__property Footer;
	__property Header;
	__property MaxRows = {default=20};
	__property DataSet;
	__property RowAttributes;
	__property TableAttributes;
	__property OnCreateContent;
	__property OnFormatCell;
	__property OnGetTableCaption;
public:
	/* TDSTableProducer.Create */ inline __fastcall virtual TDataSetTableProducer(System::Classes::TComponent* AOwner) : TDSTableProducer(AOwner) { }
	/* TDSTableProducer.Destroy */ inline __fastcall virtual ~TDataSetTableProducer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall HtmlTable(Data::Db::TDataSet* DataSet, TDSTableProducer* DataSetHandler, int MaxRows);
}	/* namespace Dbweb */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_DBWEB)
using namespace Web::Dbweb;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_DbwebHPP
