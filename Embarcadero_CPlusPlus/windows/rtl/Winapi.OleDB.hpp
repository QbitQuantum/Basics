// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.OleDB.pas' rev: 34.00 (Windows)

#ifndef Winapi_OledbHPP
#define Winapi_OledbHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>

//-- user supplied -----------------------------------------------------------
#include <transact.h>
#include <oledb.h>

namespace Winapi
{
namespace Oledb
{
//-- forward type declarations -----------------------------------------------
struct DBIDNAME;
struct DBIDGUID;
struct DBFILETIME;
__interface DELPHIINTERFACE ITransaction;
typedef System::DelphiInterface<ITransaction> _di_ITransaction;
__interface DELPHIINTERFACE ITransactionSC;
typedef System::DelphiInterface<ITransactionSC> _di_ITransactionSC;
__interface DELPHIINTERFACE ITransactionOptions;
typedef System::DelphiInterface<ITransactionOptions> _di_ITransactionOptions;
__interface DELPHIINTERFACE ITransactionOptionsSC;
typedef System::DelphiInterface<ITransactionOptionsSC> _di_ITransactionOptionsSC;
__interface DELPHIINTERFACE ITransactionDispenser;
typedef System::DelphiInterface<ITransactionDispenser> _di_ITransactionDispenser;
__interface DELPHIINTERFACE ITransactionDispenserSC;
typedef System::DelphiInterface<ITransactionDispenserSC> _di_ITransactionDispenserSC;
__interface DELPHIINTERFACE ITransactionOutcomeEvents;
typedef System::DelphiInterface<ITransactionOutcomeEvents> _di_ITransactionOutcomeEvents;
__interface DELPHIINTERFACE ITransactionOutcomeEventsSC;
typedef System::DelphiInterface<ITransactionOutcomeEventsSC> _di_ITransactionOutcomeEventsSC;
__interface DELPHIINTERFACE IAccessor;
typedef System::DelphiInterface<IAccessor> _di_IAccessor;
__interface DELPHIINTERFACE IAccessorSC;
typedef System::DelphiInterface<IAccessorSC> _di_IAccessorSC;
__interface DELPHIINTERFACE IRowset;
typedef System::DelphiInterface<IRowset> _di_IRowset;
__interface DELPHIINTERFACE IRowsetSC;
typedef System::DelphiInterface<IRowsetSC> _di_IRowsetSC;
__interface DELPHIINTERFACE IRowsetInfo;
typedef System::DelphiInterface<IRowsetInfo> _di_IRowsetInfo;
__interface DELPHIINTERFACE IRowsetInfoSC;
typedef System::DelphiInterface<IRowsetInfoSC> _di_IRowsetInfoSC;
__interface DELPHIINTERFACE IRowsetLocate;
typedef System::DelphiInterface<IRowsetLocate> _di_IRowsetLocate;
__interface DELPHIINTERFACE IRowsetLocateSC;
typedef System::DelphiInterface<IRowsetLocateSC> _di_IRowsetLocateSC;
__interface DELPHIINTERFACE IRowsetResynch;
typedef System::DelphiInterface<IRowsetResynch> _di_IRowsetResynch;
__interface DELPHIINTERFACE IRowsetResynchSC;
typedef System::DelphiInterface<IRowsetResynchSC> _di_IRowsetResynchSC;
__interface DELPHIINTERFACE IRowsetScroll;
typedef System::DelphiInterface<IRowsetScroll> _di_IRowsetScroll;
__interface DELPHIINTERFACE IRowsetScrollSC;
typedef System::DelphiInterface<IRowsetScrollSC> _di_IRowsetScrollSC;
__interface DELPHIINTERFACE IRowsetChange;
typedef System::DelphiInterface<IRowsetChange> _di_IRowsetChange;
__interface DELPHIINTERFACE IRowsetChangeSC;
typedef System::DelphiInterface<IRowsetChangeSC> _di_IRowsetChangeSC;
__interface DELPHIINTERFACE IRowsetUpdate;
typedef System::DelphiInterface<IRowsetUpdate> _di_IRowsetUpdate;
__interface DELPHIINTERFACE IRowsetUpdateSC;
typedef System::DelphiInterface<IRowsetUpdateSC> _di_IRowsetUpdateSC;
__interface DELPHIINTERFACE IRowsetIndex;
typedef System::DelphiInterface<IRowsetIndex> _di_IRowsetIndex;
__interface DELPHIINTERFACE IRowsetIndexSC;
typedef System::DelphiInterface<IRowsetIndexSC> _di_IRowsetIndexSC;
__interface DELPHIINTERFACE IMultipleResults;
typedef System::DelphiInterface<IMultipleResults> _di_IMultipleResults;
__interface DELPHIINTERFACE IMultipleResultsSC;
typedef System::DelphiInterface<IMultipleResultsSC> _di_IMultipleResultsSC;
__interface DELPHIINTERFACE IConvertType;
typedef System::DelphiInterface<IConvertType> _di_IConvertType;
__interface DELPHIINTERFACE IConvertTypeSC;
typedef System::DelphiInterface<IConvertTypeSC> _di_IConvertTypeSC;
__interface DELPHIINTERFACE ICommandPrepare;
typedef System::DelphiInterface<ICommandPrepare> _di_ICommandPrepare;
__interface DELPHIINTERFACE ICommandPrepareSC;
typedef System::DelphiInterface<ICommandPrepareSC> _di_ICommandPrepareSC;
__interface DELPHIINTERFACE ICommandProperties;
typedef System::DelphiInterface<ICommandProperties> _di_ICommandProperties;
__interface DELPHIINTERFACE ICommandPropertiesSC;
typedef System::DelphiInterface<ICommandPropertiesSC> _di_ICommandPropertiesSC;
__interface DELPHIINTERFACE ICommand;
typedef System::DelphiInterface<ICommand> _di_ICommand;
__interface DELPHIINTERFACE ICommandSC;
typedef System::DelphiInterface<ICommandSC> _di_ICommandSC;
__interface DELPHIINTERFACE ICommandWithParameters;
typedef System::DelphiInterface<ICommandWithParameters> _di_ICommandWithParameters;
__interface DELPHIINTERFACE ICommandWithParametersSC;
typedef System::DelphiInterface<ICommandWithParametersSC> _di_ICommandWithParametersSC;
__interface DELPHIINTERFACE ICommandText;
typedef System::DelphiInterface<ICommandText> _di_ICommandText;
__interface DELPHIINTERFACE ICommandTextP;
typedef System::DelphiInterface<ICommandTextP> _di_ICommandTextP;
__interface DELPHIINTERFACE ICommandTextSC;
typedef System::DelphiInterface<ICommandTextSC> _di_ICommandTextSC;
__interface DELPHIINTERFACE ICommandTextSCP;
typedef System::DelphiInterface<ICommandTextSCP> _di_ICommandTextSCP;
__interface DELPHIINTERFACE IColumnsRowset;
typedef System::DelphiInterface<IColumnsRowset> _di_IColumnsRowset;
__interface DELPHIINTERFACE IColumnsRowsetSC;
typedef System::DelphiInterface<IColumnsRowsetSC> _di_IColumnsRowsetSC;
__interface DELPHIINTERFACE IColumnsInfo;
typedef System::DelphiInterface<IColumnsInfo> _di_IColumnsInfo;
__interface DELPHIINTERFACE IColumnsInfoSC;
typedef System::DelphiInterface<IColumnsInfoSC> _di_IColumnsInfoSC;
__interface DELPHIINTERFACE IDBCreateCommand;
typedef System::DelphiInterface<IDBCreateCommand> _di_IDBCreateCommand;
__interface DELPHIINTERFACE IDBCreateCommandSC;
typedef System::DelphiInterface<IDBCreateCommandSC> _di_IDBCreateCommandSC;
__interface DELPHIINTERFACE IDBCreateSession;
typedef System::DelphiInterface<IDBCreateSession> _di_IDBCreateSession;
__interface DELPHIINTERFACE IDBCreateSessionSC;
typedef System::DelphiInterface<IDBCreateSessionSC> _di_IDBCreateSessionSC;
__interface DELPHIINTERFACE ISourcesRowset;
typedef System::DelphiInterface<ISourcesRowset> _di_ISourcesRowset;
__interface DELPHIINTERFACE ISourcesRowsetSC;
typedef System::DelphiInterface<ISourcesRowsetSC> _di_ISourcesRowsetSC;
__interface DELPHIINTERFACE IDBProperties;
typedef System::DelphiInterface<IDBProperties> _di_IDBProperties;
__interface DELPHIINTERFACE IDBPropertiesSC;
typedef System::DelphiInterface<IDBPropertiesSC> _di_IDBPropertiesSC;
__interface DELPHIINTERFACE IDBInitialize;
typedef System::DelphiInterface<IDBInitialize> _di_IDBInitialize;
__interface DELPHIINTERFACE IDBInitializeSC;
typedef System::DelphiInterface<IDBInitializeSC> _di_IDBInitializeSC;
__interface DELPHIINTERFACE IDBInfo;
typedef System::DelphiInterface<IDBInfo> _di_IDBInfo;
__interface DELPHIINTERFACE IDBInfoSC;
typedef System::DelphiInterface<IDBInfoSC> _di_IDBInfoSC;
__interface DELPHIINTERFACE IDBDataSourceAdmin;
typedef System::DelphiInterface<IDBDataSourceAdmin> _di_IDBDataSourceAdmin;
__interface DELPHIINTERFACE IDBDataSourceAdminSC;
typedef System::DelphiInterface<IDBDataSourceAdminSC> _di_IDBDataSourceAdminSC;
__interface DELPHIINTERFACE ISessionProperties;
typedef System::DelphiInterface<ISessionProperties> _di_ISessionProperties;
__interface DELPHIINTERFACE ISessionPropertiesSC;
typedef System::DelphiInterface<ISessionPropertiesSC> _di_ISessionPropertiesSC;
__interface DELPHIINTERFACE IIndexDefinition;
typedef System::DelphiInterface<IIndexDefinition> _di_IIndexDefinition;
__interface DELPHIINTERFACE IIndexDefinitionSC;
typedef System::DelphiInterface<IIndexDefinitionSC> _di_IIndexDefinitionSC;
__interface DELPHIINTERFACE ITableDefinition;
typedef System::DelphiInterface<ITableDefinition> _di_ITableDefinition;
__interface DELPHIINTERFACE ITableDefinitionSC;
typedef System::DelphiInterface<ITableDefinitionSC> _di_ITableDefinitionSC;
__interface DELPHIINTERFACE IOpenRowset;
typedef System::DelphiInterface<IOpenRowset> _di_IOpenRowset;
__interface DELPHIINTERFACE IOpenRowsetSC;
typedef System::DelphiInterface<IOpenRowsetSC> _di_IOpenRowsetSC;
__interface DELPHIINTERFACE IErrorLookup;
typedef System::DelphiInterface<IErrorLookup> _di_IErrorLookup;
__interface DELPHIINTERFACE IErrorLookupSC;
typedef System::DelphiInterface<IErrorLookupSC> _di_IErrorLookupSC;
__interface DELPHIINTERFACE ISQLErrorInfo;
typedef System::DelphiInterface<ISQLErrorInfo> _di_ISQLErrorInfo;
__interface DELPHIINTERFACE ISQLErrorInfoSC;
typedef System::DelphiInterface<ISQLErrorInfoSC> _di_ISQLErrorInfoSC;
__interface DELPHIINTERFACE IGetDataSource;
typedef System::DelphiInterface<IGetDataSource> _di_IGetDataSource;
__interface DELPHIINTERFACE IGetDataSourceSC;
typedef System::DelphiInterface<IGetDataSourceSC> _di_IGetDataSourceSC;
__interface DELPHIINTERFACE ITransactionLocal;
typedef System::DelphiInterface<ITransactionLocal> _di_ITransactionLocal;
__interface DELPHIINTERFACE ITransactionLocalSC;
typedef System::DelphiInterface<ITransactionLocalSC> _di_ITransactionLocalSC;
__interface DELPHIINTERFACE ITransactionJoin;
typedef System::DelphiInterface<ITransactionJoin> _di_ITransactionJoin;
__interface DELPHIINTERFACE ITransactionJoinSC;
typedef System::DelphiInterface<ITransactionJoinSC> _di_ITransactionJoinSC;
__interface DELPHIINTERFACE ITransactionObject;
typedef System::DelphiInterface<ITransactionObject> _di_ITransactionObject;
__interface DELPHIINTERFACE ITransactionObjectSC;
typedef System::DelphiInterface<ITransactionObjectSC> _di_ITransactionObjectSC;
__interface DELPHIINTERFACE IDBAsynchStatus;
typedef System::DelphiInterface<IDBAsynchStatus> _di_IDBAsynchStatus;
__interface DELPHIINTERFACE IDBAsynchStatusSC;
typedef System::DelphiInterface<IDBAsynchStatusSC> _di_IDBAsynchStatusSC;
__interface DELPHIINTERFACE IRowsetFind;
typedef System::DelphiInterface<IRowsetFind> _di_IRowsetFind;
__interface DELPHIINTERFACE IRowsetFindSC;
typedef System::DelphiInterface<IRowsetFindSC> _di_IRowsetFindSC;
__interface DELPHIINTERFACE IRowPosition;
typedef System::DelphiInterface<IRowPosition> _di_IRowPosition;
__interface DELPHIINTERFACE IRowPositionSC;
typedef System::DelphiInterface<IRowPositionSC> _di_IRowPositionSC;
__interface DELPHIINTERFACE IRowPositionChange;
typedef System::DelphiInterface<IRowPositionChange> _di_IRowPositionChange;
__interface DELPHIINTERFACE IRowPositionChangeSC;
typedef System::DelphiInterface<IRowPositionChangeSC> _di_IRowPositionChangeSC;
__interface DELPHIINTERFACE IViewRowset;
typedef System::DelphiInterface<IViewRowset> _di_IViewRowset;
__interface DELPHIINTERFACE IViewRowsetSC;
typedef System::DelphiInterface<IViewRowsetSC> _di_IViewRowsetSC;
__interface DELPHIINTERFACE IViewChapter;
typedef System::DelphiInterface<IViewChapter> _di_IViewChapter;
__interface DELPHIINTERFACE IViewChapterSC;
typedef System::DelphiInterface<IViewChapterSC> _di_IViewChapterSC;
__interface DELPHIINTERFACE IViewSort;
typedef System::DelphiInterface<IViewSort> _di_IViewSort;
__interface DELPHIINTERFACE IViewSortSC;
typedef System::DelphiInterface<IViewSortSC> _di_IViewSortSC;
__interface DELPHIINTERFACE IViewFilter;
typedef System::DelphiInterface<IViewFilter> _di_IViewFilter;
__interface DELPHIINTERFACE IViewFilterSC;
typedef System::DelphiInterface<IViewFilterSC> _di_IViewFilterSC;
__interface DELPHIINTERFACE IRowsetView;
typedef System::DelphiInterface<IRowsetView> _di_IRowsetView;
__interface DELPHIINTERFACE IRowsetViewSC;
typedef System::DelphiInterface<IRowsetViewSC> _di_IRowsetViewSC;
__interface DELPHIINTERFACE IMDFind;
typedef System::DelphiInterface<IMDFind> _di_IMDFind;
__interface DELPHIINTERFACE IMDFindSC;
typedef System::DelphiInterface<IMDFindSC> _di_IMDFindSC;
__interface DELPHIINTERFACE IMDRangeRowset;
typedef System::DelphiInterface<IMDRangeRowset> _di_IMDRangeRowset;
__interface DELPHIINTERFACE IMDRangeRowsetSC;
typedef System::DelphiInterface<IMDRangeRowsetSC> _di_IMDRangeRowsetSC;
__interface DELPHIINTERFACE IAlterTable;
typedef System::DelphiInterface<IAlterTable> _di_IAlterTable;
__interface DELPHIINTERFACE IAlterTableSC;
typedef System::DelphiInterface<IAlterTableSC> _di_IAlterTableSC;
__interface DELPHIINTERFACE IAlterIndex;
typedef System::DelphiInterface<IAlterIndex> _di_IAlterIndex;
__interface DELPHIINTERFACE IAlterIndexSC;
typedef System::DelphiInterface<IAlterIndexSC> _di_IAlterIndexSC;
__interface DELPHIINTERFACE ICommandPersist;
typedef System::DelphiInterface<ICommandPersist> _di_ICommandPersist;
__interface DELPHIINTERFACE ICommandPersistSC;
typedef System::DelphiInterface<ICommandPersistSC> _di_ICommandPersistSC;
__interface DELPHIINTERFACE IRowsetChapterMember;
typedef System::DelphiInterface<IRowsetChapterMember> _di_IRowsetChapterMember;
__interface DELPHIINTERFACE IRowsetChapterMemberSC;
typedef System::DelphiInterface<IRowsetChapterMemberSC> _di_IRowsetChapterMemberSC;
__interface DELPHIINTERFACE IRowsetRefresh;
typedef System::DelphiInterface<IRowsetRefresh> _di_IRowsetRefresh;
__interface DELPHIINTERFACE IRowsetRefreshSC;
typedef System::DelphiInterface<IRowsetRefreshSC> _di_IRowsetRefreshSC;
__interface DELPHIINTERFACE IParentRowset;
typedef System::DelphiInterface<IParentRowset> _di_IParentRowset;
__interface DELPHIINTERFACE IParentRowsetSC;
typedef System::DelphiInterface<IParentRowsetSC> _di_IParentRowsetSC;
__interface DELPHIINTERFACE ITrusteeGroupAdmin;
typedef System::DelphiInterface<ITrusteeGroupAdmin> _di_ITrusteeGroupAdmin;
__interface DELPHIINTERFACE ITrusteeGroupAdminSC;
typedef System::DelphiInterface<ITrusteeGroupAdminSC> _di_ITrusteeGroupAdminSC;
__interface DELPHIINTERFACE IObjectAccessControl;
typedef System::DelphiInterface<IObjectAccessControl> _di_IObjectAccessControl;
__interface DELPHIINTERFACE IObjectAccessControlSC;
typedef System::DelphiInterface<IObjectAccessControlSC> _di_IObjectAccessControlSC;
__interface DELPHIINTERFACE ISecurityInfo;
typedef System::DelphiInterface<ISecurityInfo> _di_ISecurityInfo;
__interface DELPHIINTERFACE ISecurityInfoSC;
typedef System::DelphiInterface<ISecurityInfoSC> _di_ISecurityInfoSC;
__interface DELPHIINTERFACE IDBPromptInitialize;
typedef System::DelphiInterface<IDBPromptInitialize> _di_IDBPromptInitialize;
__interface DELPHIINTERFACE IDBPromptInitializeSC;
typedef System::DelphiInterface<IDBPromptInitializeSC> _di_IDBPromptInitializeSC;
__interface DELPHIINTERFACE IDataInitialize;
typedef System::DelphiInterface<IDataInitialize> _di_IDataInitialize;
__interface DELPHIINTERFACE IDataInitializeSC;
typedef System::DelphiInterface<IDataInitializeSC> _di_IDataInitializeSC;
//-- type declarations -------------------------------------------------------
typedef int TOldOleEnum;

typedef unsigned TOleEnum;

typedef System::_di_IInterface *PIUnknown;

typedef System::Int8 SBYTE;

typedef System::StaticArray<unsigned, 65536> TUintArray;

typedef TUintArray *PUintArray;

typedef System::StaticArray<NativeUInt, 65536> TULONG_PTRArray;

typedef TULONG_PTRArray *PULONG_PTRArray;

typedef System::PByte *PPByte;

typedef System::StaticArray<System::PByte, 65536> TPByteArray;

typedef TPByteArray *PPByteArray;

typedef unsigned *PDBASYNCHPHASE;

typedef unsigned *PDBSORT;

typedef unsigned *PDBCOMPAREOP;

typedef NativeUInt *PHACCESSOR;

typedef System::Word *PHSOURCE;

typedef NativeUInt PHCHAPTER;

typedef NativeUInt *PHROW;

typedef PHROW *PPHROW;

typedef unsigned *PDBROWSTATUS;

typedef PDBROWSTATUS *PPDBROWSTATUS;

typedef unsigned *PDBPENDINGSTATUS;

typedef PDBPENDINGSTATUS *PPDBPENDINGSTATUS;

typedef unsigned *PDBROWOPTIONS;

typedef unsigned *PDBSOURCETYPE;

typedef BOID *PBoid;

typedef BOID TBoid;

typedef XACTTRANSINFO *PXactTransInfo;

typedef XACTTRANSINFO TXactTransInfo;

typedef XACTOPT *PXactOpt;

typedef XACTOPT TXActOpt;

typedef XACTSTATS *PXactStats;

typedef XACTSTATS TXactStats;

typedef DBBINDEXT *PDBBindExt;

typedef DBBINDEXT TDBBindExt;

typedef DBOBJECT *PDBObject;

typedef DBOBJECT TDBObject;

typedef DBBINDING *PDBBinding;

typedef DBBINDING TDBBinding;

typedef System::StaticArray<DBBINDING, 65536> TDBBindingArray;

typedef TDBBindingArray *PDBBindingArray;

typedef DBIDNAME *PDBIDName;

#ifndef _WIN64
#pragma pack(push,2)
#endif /* not _WIN64 */
struct DECLSPEC_DRECORD DBIDNAME
{
	
public:
	union
	{
		struct 
		{
			unsigned ulPropid;
		};
		struct 
		{
			System::WideChar *pwszName;
		};
		
	};
};
#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */


typedef DBIDNAME TDBIDName;

typedef DBIDGUID *PDBIDGuid;

#ifndef _WIN64
#pragma pack(push,2)
#endif /* not _WIN64 */
struct DECLSPEC_DRECORD DBIDGUID
{
	
public:
	union
	{
		struct 
		{
			GUID *pguid;
		};
		struct 
		{
			GUID guid;
		};
		
	};
};
#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */


typedef DBIDGUID TDBIDGuid;

typedef unsigned *PDBPROPID;

typedef System::StaticArray<unsigned, 65536> TDBPropIDArray;

typedef TDBPropIDArray *PDBPropIDArray;

typedef DBID *PDBID;

typedef PDBID *PPDBID;

typedef DBID TDBID;

typedef System::StaticArray<DBID, 65536> TDBIDArray;

typedef TDBIDArray *PDBIDArray;

typedef DBPROPIDSET *PDBPropIDSet;

typedef DBPROPIDSET TDBPropIDSet;

typedef System::StaticArray<DBPROPIDSET, 65536> TDBPropIDSetArray;

typedef TDBPropIDSetArray *PDBPropIDSetArray;

typedef DBPROP *PDBProp;

typedef DBPROP TDBProp;

typedef System::StaticArray<DBPROP, 65536> TDBPropArray;

typedef TDBPropArray *PDBPropArray;

typedef DBPROPSET *PDBPropSet;

typedef PDBPropSet *PPDBPropSet;

typedef DBPROPSET TDBPropSet;

typedef System::StaticArray<DBPROPSET, 65536> TDBPropSetArray;

typedef TDBPropSetArray *PDBPropSetArray;

typedef DBPROPINFO *PDBPropInfo;

typedef DBPROPINFO TDBPropInfo;

typedef System::StaticArray<DBPROPINFO, 65536> TDBPropInfoArray;

typedef TDBPropInfoArray *PDBPropInfoArray;

typedef DBPROPINFOSET *PDBPropInfoSet;

typedef DBPROPINFOSET TDBPropInfoSet;

typedef System::StaticArray<DBPROPINFOSET, 65536> TDBPropInfoSetArray;

typedef TDBPropInfoSetArray *PDBPropInfoSetArray;

typedef DBINDEXCOLUMNDESC *PDBIndexColumnDesc;

typedef DBINDEXCOLUMNDESC TDBIndexColumnDesc;

typedef System::StaticArray<DBINDEXCOLUMNDESC, 65536> TDBIndexColumnDescArray;

typedef TDBIndexColumnDescArray *PDBIndexColumnDescArray;

typedef DBPARAMS *PDBParams;

typedef DBPARAMS TDBParams;

typedef DBCOLUMNINFO *PDBColumnInfo;

typedef DBCOLUMNINFO TDBColumnInfo;

typedef System::StaticArray<DBCOLUMNINFO, 4097> TDBColumnInfoArray;

typedef TDBColumnInfoArray *PDBColumnInfoArray;

typedef DBLITERALINFO *PDBLiteralInfo;

typedef DBLITERALINFO TDBLiteralInfo;

typedef System::StaticArray<DBLITERALINFO, 65536> TDBLiteralInfoArray;

typedef TDBLiteralInfoArray *PDBLiteralInfoArray;

typedef DBCOLUMNDESC *PDBColumnDesc;

typedef DBCOLUMNDESC TDBColumnDesc;

typedef System::StaticArray<DBCOLUMNDESC, 65536> TDBColumnDescArray;

typedef TDBColumnDescArray *PDBColumnDescArray;

typedef SEC_OBJECT_ELEMENT *PSecObjectElement;

typedef SEC_OBJECT_ELEMENT TSecObjectElement;

typedef System::StaticArray<SEC_OBJECT_ELEMENT, 65536> TSecObjectElementArray;

typedef TSecObjectElementArray *PSecObjectElementArray;

typedef SEC_OBJECT *PSecObject;

typedef SEC_OBJECT TSecObject;

typedef TRUSTEE_W *TTrusteeW;

typedef TTrusteeW *PTrusteeW;

typedef PTrusteeW *PPTrusteeW;

typedef DBPARAMINFO *PDBParamInfo;

typedef DBPARAMINFO TDBParamInfo;

typedef System::StaticArray<DBPARAMINFO, 65536> TDBParamInfoArray;

typedef TDBParamInfoArray *PDBParamInfoArray;

typedef DB_NUMERIC *PDBNumeric;

typedef DB_NUMERIC TDBNumeric;

typedef DBVECTOR *PDBVector;

typedef DBVECTOR TDBVector;

typedef DBDATE *PDBDate;

typedef DBDATE TDBDate;

typedef DBTIME *PDBTime;

typedef DBTIME TDBTime;

typedef DBTIMESTAMP *PDBTimeStamp;

typedef DBTIMESTAMP TDBTimeStamp;

typedef DBFILETIME *PDBFileTime;

#ifndef _WIN64
#pragma pack(push,2)
#endif /* not _WIN64 */
struct DECLSPEC_DRECORD DBFILETIME
{
public:
	unsigned dwLowDateTime;
	unsigned dwHighDateTime;
};
#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */


typedef DBFILETIME TDBFileTime;

typedef DB_VARNUMERIC *PDBVarNumeric;

typedef DB_VARNUMERIC TDBVarNumeric;

typedef DBFAILUREINFO *PDBFailureInfo;

typedef DBFAILUREINFO TDBFailureInfo;

typedef MDAXISINFO *PMDAxisInfo;

typedef MDAXISINFO TMDAxisInfo;

typedef DBPARAMBINDINFO *PDBParamBindInfo;

typedef DBPARAMBINDINFO TDBParamBindInfo;

typedef System::StaticArray<DBPARAMBINDINFO, 65536> TDBParamBindInfoArray;

typedef TDBParamBindInfoArray *PDBParamBindInfoArray;

typedef ERRORINFO *PErrorInfo;

typedef ERRORINFO TErrorInfo;

typedef EXPLICIT_ACCESS_W *PExplicitAccessW;

typedef PExplicitAccessW *PPExplicitAccessW;

typedef EXPLICIT_ACCESS_W TExplicitAccessW;

__interface  INTERFACE_UUID("{0FB15084-AF41-11CE-BD2B-204C4F4F5020}") ITransaction  : public System::IInterface 
{
	virtual HRESULT __stdcall Commit(System::LongBool fRetaining, unsigned grfTC, unsigned grfRM) = 0 ;
	virtual HRESULT __stdcall Abort(PBoid pboidReason, System::LongBool fRetaining, System::LongBool fAsync) = 0 ;
	virtual HRESULT __stdcall GetTransactionInfo(/* out */ XACTTRANSINFO &pinfo) = 0 ;
};

__interface  INTERFACE_UUID("{0FB15084-AF41-11CE-BD2B-204C4F4F5020}") ITransactionSC  : public System::IInterface 
{
	virtual HRESULT __safecall Commit(System::LongBool fRetaining, unsigned grfTC, unsigned grfRM) = 0 ;
	virtual HRESULT __safecall Abort(PBoid pboidReason, System::LongBool fRetaining, System::LongBool fAsync) = 0 ;
	virtual HRESULT __safecall GetTransactionInfo(/* out */ XACTTRANSINFO &pinfo) = 0 ;
};

__interface  INTERFACE_UUID("{3A6AD9E0-23B9-11CF-AD60-00AA00A74CCD}") ITransactionOptions  : public System::IInterface 
{
	virtual HRESULT __stdcall SetOptions(XACTOPT &pOptions) = 0 ;
	virtual HRESULT __stdcall GetOptions(XACTOPT &pOptions) = 0 ;
};

__interface  INTERFACE_UUID("{3A6AD9E0-23B9-11CF-AD60-00AA00A74CCD}") ITransactionOptionsSC  : public System::IInterface 
{
	virtual HRESULT __safecall SetOptions(XACTOPT &pOptions) = 0 ;
	virtual HRESULT __safecall GetOptions(XACTOPT &pOptions) = 0 ;
};

__interface  INTERFACE_UUID("{3A6AD9E1-23B9-11CF-AD60-00AA00A74CCD}") ITransactionDispenser  : public System::IInterface 
{
	virtual HRESULT __stdcall GetOptionsObject(/* out */ _di_ITransactionOptions &ppOptions) = 0 ;
	virtual HRESULT __stdcall BeginTransaction(const System::_di_IInterface punkOuter, int isoLevel, unsigned isoFlags, const _di_ITransactionOptions pOptions, /* out */ _di_ITransaction &ppTransaction) = 0 ;
};

__interface  INTERFACE_UUID("{3A6AD9E1-23B9-11CF-AD60-00AA00A74CCD}") ITransactionDispenserSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetOptionsObject(/* out */ _di_ITransactionOptions &ppOptions) = 0 ;
	virtual HRESULT __safecall BeginTransaction(const System::_di_IInterface punkOuter, int isoLevel, unsigned isoFlags, const _di_ITransactionOptions pOptions, /* out */ _di_ITransaction &ppTransaction) = 0 ;
};

__interface  INTERFACE_UUID("{3A6AD9E2-23B9-11CF-AD60-00AA00A74CCD}") ITransactionOutcomeEvents  : public System::IInterface 
{
	virtual HRESULT __stdcall Committed(System::LongBool fRetaining, PBoid pNewUOW, HRESULT hr) = 0 ;
	virtual HRESULT __stdcall Aborted(PBoid pboidReason, System::LongBool fRetaining, PBoid pNewUOW, HRESULT hr) = 0 ;
	virtual HRESULT __stdcall HeuristicDecision(unsigned dwDecision, PBoid pboidReason, HRESULT hr) = 0 ;
	virtual HRESULT __stdcall Indoubt() = 0 ;
};

__interface  INTERFACE_UUID("{3A6AD9E2-23B9-11CF-AD60-00AA00A74CCD}") ITransactionOutcomeEventsSC  : public System::IInterface 
{
	virtual HRESULT __safecall Committed(System::LongBool fRetaining, PBoid pNewUOW, HRESULT hr) = 0 ;
	virtual HRESULT __safecall Aborted(PBoid pboidReason, System::LongBool fRetaining, PBoid pNewUOW, HRESULT hr) = 0 ;
	virtual HRESULT __safecall HeuristicDecision(unsigned dwDecision, PBoid pboidReason, HRESULT hr) = 0 ;
	virtual HRESULT __stdcall Indoubt() = 0 ;
};

__interface  INTERFACE_UUID("{0C733A8C-2A1C-11CE-ADE5-00AA0044773D}") IAccessor  : public System::IInterface 
{
	virtual HRESULT __stdcall AddRefAccessor(NativeUInt HACCESSOR, PUINT pcRefCount) = 0 ;
	virtual HRESULT __stdcall CreateAccessor(unsigned dwAccessorFlags, NativeUInt cBindings, PDBBindingArray rgBindings, NativeUInt cbRowSize, NativeUInt &phAccessor, PUintArray rgStatus) = 0 ;
	virtual HRESULT __stdcall GetBindings(NativeUInt HACCESSOR, PUINT pdwAccessorFlags, NativeUInt &pcBindings, /* out */ PDBBinding &prgBindings) = 0 ;
	virtual HRESULT __stdcall ReleaseAccessor(NativeUInt HACCESSOR, PUINT pcRefCount) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A8C-2A1C-11CE-ADE5-00AA0044773D}") IAccessorSC  : public System::IInterface 
{
	virtual HRESULT __safecall AddRefAccessor(NativeUInt HACCESSOR, PUINT pcRefCount) = 0 ;
	virtual HRESULT __safecall CreateAccessor(unsigned dwAccessorFlags, NativeUInt cBindings, PDBBindingArray rgBindings, NativeUInt cbRowSize, NativeUInt &phAccessor, PUintArray rgStatus) = 0 ;
	virtual HRESULT __safecall GetBindings(NativeUInt HACCESSOR, PUINT pdwAccessorFlags, NativeUInt &pcBindings, /* out */ PDBBinding &prgBindings) = 0 ;
	virtual HRESULT __safecall ReleaseAccessor(NativeUInt HACCESSOR, PUINT pcRefCount) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A7C-2A1C-11CE-ADE5-00AA0044773D}") IRowset  : public System::IInterface 
{
	virtual HRESULT __stdcall AddRefRows(NativeUInt cRows, PUintArray rghRows, PUintArray rgRefCounts, PUintArray rgRowStatus) = 0 ;
	virtual HRESULT __stdcall GetData(NativeUInt HROW, NativeUInt HACCESSOR, void * pData) = 0 ;
	virtual HRESULT __stdcall GetNextRows(NativeUInt hReserved, NativeInt lRowsOffset, NativeInt cRows, /* out */ NativeUInt &pcRowsObtained, PUintArray &prghRows) = 0 ;
	virtual HRESULT __stdcall ReleaseRows(NativeUInt cRows, PUintArray rghRows, PUintArray rgRowOptions, PUintArray rgRefCounts, PUintArray rgRowStatus) = 0 ;
	virtual HRESULT __stdcall RestartPosition(NativeUInt hReserved) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A7C-2A1C-11CE-ADE5-00AA0044773D}") IRowsetSC  : public System::IInterface 
{
	virtual HRESULT __safecall AddRefRows(NativeUInt cRows, PUintArray rghRows, PUintArray rgRefCounts, PUintArray rgRowStatus) = 0 ;
	virtual HRESULT __safecall GetData(NativeUInt HROW, NativeUInt HACCESSOR, void * pData) = 0 ;
	virtual HRESULT __safecall GetNextRows(NativeUInt hReserved, NativeInt lRowsOffset, NativeInt cRows, /* out */ NativeUInt &pcRowsObtained, PUintArray &prghRows) = 0 ;
	virtual HRESULT __safecall ReleaseRows(NativeUInt cRows, PUintArray rghRows, PUintArray rgRowOptions, PUintArray rgRefCounts, PUintArray rgRowStatus) = 0 ;
	virtual HRESULT __safecall RestartPosition(NativeUInt hReserved) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A55-2A1C-11CE-ADE5-00AA0044773D}") IRowsetInfo  : public System::IInterface 
{
	virtual HRESULT __stdcall GetProperties(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, /* out */ unsigned &pcPropertySets, /* out */ PDBPropSet &prgPropertySets) = 0 ;
	virtual HRESULT __stdcall GetReferencedRowset(NativeUInt iOrdinal, const GUID &riid, /* out */ System::_di_IInterface &ppReferencedRowset) = 0 ;
	virtual HRESULT __stdcall GetSpecification(const GUID &riid, /* out */ System::_di_IInterface &ppSpecification) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A55-2A1C-11CE-ADE5-00AA0044773D}") IRowsetInfoSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetProperties(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, /* out */ unsigned &pcPropertySets, /* out */ PDBPropSet &prgPropertySets) = 0 ;
	virtual HRESULT __safecall GetReferencedRowset(NativeUInt iOrdinal, const GUID &riid, /* out */ System::_di_IInterface &ppReferencedRowset) = 0 ;
	virtual HRESULT __safecall GetSpecification(const GUID &riid, /* out */ System::_di_IInterface &ppSpecification) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A7D-2A1C-11CE-ADE5-00AA0044773D}") IRowsetLocate  : public IRowset 
{
	virtual HRESULT __stdcall Compare(NativeUInt hReserved, NativeUInt cbBookmark1, System::PByte pBookmark1, NativeUInt cbBookmark2, System::PByte pBookmark2, /* out */ unsigned &pComparison) = 0 ;
	virtual HRESULT __stdcall GetRowsAt(NativeUInt hReserved1, NativeUInt hReserved2, NativeUInt cbBookmark, System::PByte pBookmark, NativeInt lRowsOffset, NativeInt cRows, /* out */ NativeUInt &pcRowsObtained, /* out */ PHROW &prghRows) = 0 ;
	virtual HRESULT __stdcall GetRowsByBookmark(NativeUInt hReserved, NativeUInt cRows, PULONG_PTRArray rgcbBookmarks, PPByteArray rgpBookmarks, PUintArray rghRows, PUintArray rgRowStatus) = 0 ;
	virtual HRESULT __stdcall Hash(NativeUInt hReserved, NativeUInt cBookmarks, PULONG_PTRArray rgcbBookmarks, PPByteArray rgpBookmarks, PULONG_PTRArray rgHashedValues, PUintArray rgBookmarkStatus) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A7D-2A1C-11CE-ADE5-00AA0044773D}") IRowsetLocateSC  : public IRowsetSC 
{
	virtual HRESULT __safecall Compare(NativeUInt hReserved, NativeUInt cbBookmark1, System::PByte pBookmark1, NativeUInt cbBookmark2, System::PByte pBookmark2, /* out */ unsigned &pComparison) = 0 ;
	virtual HRESULT __safecall GetRowsAt(NativeUInt hReserved1, NativeUInt hReserved2, NativeUInt cbBookmark, System::PByte pBookmark, NativeInt lRowsOffset, NativeInt cRows, /* out */ NativeUInt &pcRowsObtained, /* out */ PHROW &prghRows) = 0 ;
	virtual HRESULT __safecall GetRowsByBookmark(NativeUInt hReserved, NativeUInt cRows, PULONG_PTRArray rgcbBookmarks, PPByteArray rgpBookmarks, PUintArray rghRows, PUintArray rgRowStatus) = 0 ;
	virtual HRESULT __safecall Hash(NativeUInt hReserved, NativeUInt cBookmarks, PULONG_PTRArray rgcbBookmarks, PPByteArray rgpBookmarks, PULONG_PTRArray rgHashedValues, PUintArray rgBookmarkStatus) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A84-2A1C-11CE-ADE5-00AA0044773D}") IRowsetResynch  : public System::IInterface 
{
	virtual HRESULT __stdcall GetVisibleData(NativeUInt HROW, NativeUInt HACCESSOR, /* out */ void * &pData) = 0 ;
	virtual HRESULT __stdcall ResynchRows(NativeUInt cRows, PUintArray rghRows, PULONG_PTR pcRowsResynched, /* out */ PHROW &prghRowsResynched, PPDBROWSTATUS prgRowStatus) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A84-2A1C-11CE-ADE5-00AA0044773D}") IRowsetResynchSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetVisibleData(NativeUInt HROW, NativeUInt HACCESSOR, /* out */ void * &pData) = 0 ;
	virtual HRESULT __safecall ResynchRows(NativeUInt cRows, PUintArray rghRows, PULONG_PTR pcRowsResynched, /* out */ PHROW &prghRowsResynched, PPDBROWSTATUS prgRowStatus) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A7E-2A1C-11CE-ADE5-00AA0044773D}") IRowsetScroll  : public IRowsetLocate 
{
	virtual HRESULT __stdcall GetApproximatePosition(NativeUInt hReserved, NativeUInt cbBookmark, System::PByte pBookmark, PULONG_PTR pulPosition, PULONG_PTR pcRows) = 0 ;
	virtual HRESULT __stdcall GetRowsAtRatio(NativeUInt hReserved1, NativeUInt hReserved2, NativeUInt ulNumerator, NativeUInt ulDenominator, NativeInt cRows, /* out */ NativeUInt &pcRowsObtained, PHROW &prghRows) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A7E-2A1C-11CE-ADE5-00AA0044773D}") IRowsetScrollSC  : public IRowsetLocateSC 
{
	virtual HRESULT __safecall GetApproximatePosition(NativeUInt hReserved, NativeUInt cbBookmark, System::PByte pBookmark, PULONG_PTR pulPosition, PULONG_PTR pcRows) = 0 ;
	virtual HRESULT __safecall GetRowsAtRatio(NativeUInt hReserved1, NativeUInt hReserved2, NativeUInt ulNumerator, NativeUInt ulDenominator, NativeInt cRows, /* out */ NativeUInt &pcRowsObtained, PHROW &prghRows) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A05-2A1C-11CE-ADE5-00AA0044773D}") IRowsetChange  : public System::IInterface 
{
	virtual HRESULT __stdcall DeleteRows(NativeUInt hReserved, NativeUInt cRows, PUintArray rghRows, PUintArray rgRowStatus) = 0 ;
	virtual HRESULT __stdcall SetData(NativeUInt HROW, NativeUInt HACCESSOR, void * pData) = 0 ;
	virtual HRESULT __stdcall InsertRow(NativeUInt hReserved, NativeUInt HACCESSOR, void * pData, PHROW phRow) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A05-2A1C-11CE-ADE5-00AA0044773D}") IRowsetChangeSC  : public System::IInterface 
{
	virtual HRESULT __safecall DeleteRows(NativeUInt hReserved, NativeUInt cRows, PUintArray rghRows, PUintArray rgRowStatus) = 0 ;
	virtual HRESULT __safecall SetData(NativeUInt HROW, NativeUInt HACCESSOR, void * pData) = 0 ;
	virtual HRESULT __safecall InsertRow(NativeUInt hReserved, NativeUInt HACCESSOR, void * pData, PHROW phRow) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A6D-2A1C-11CE-ADE5-00AA0044773D}") IRowsetUpdate  : public IRowsetChange 
{
	virtual HRESULT __stdcall GetOriginalData(NativeUInt HROW, NativeUInt HACCESSOR, void * pData) = 0 ;
	virtual HRESULT __stdcall GetPendingRows(NativeUInt hReserved, unsigned dwRowStatus, PULONG_PTR pcPendingRows, PPHROW prgPendingRows, PPDBPENDINGSTATUS prgPendingStatus) = 0 ;
	virtual HRESULT __stdcall GetRowStatus(NativeUInt hReserved, NativeUInt cRows, PUintArray rghRows, PUintArray rgPendingStatus) = 0 ;
	virtual HRESULT __stdcall Undo(NativeUInt hReserved, NativeUInt cRows, PUintArray rghRows, PULONG_PTR pcRowsUndone, PPHROW prgRowsUndone, PPDBROWSTATUS prgRowStatus) = 0 ;
	virtual HRESULT __stdcall Update(NativeUInt hReserved, NativeUInt cRows, PUintArray rghRows, PULONG_PTR pcRows, PPHROW prgRows, PPDBROWSTATUS prgRowStatus) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A6D-2A1C-11CE-ADE5-00AA0044773D}") IRowsetUpdateSC  : public IRowsetChangeSC 
{
	virtual HRESULT __safecall GetOriginalData(NativeUInt HROW, NativeUInt HACCESSOR, void * pData) = 0 ;
	virtual HRESULT __safecall GetPendingRows(NativeUInt hReserved, unsigned dwRowStatus, PULONG_PTR pcPendingRows, PPHROW prgPendingRows, PPDBPENDINGSTATUS prgPendingStatus) = 0 ;
	virtual HRESULT __safecall GetRowStatus(NativeUInt hReserved, NativeUInt cRows, PUintArray rghRows, PUintArray rgPendingStatus) = 0 ;
	virtual HRESULT __safecall Undo(NativeUInt hReserved, NativeUInt cRows, PUintArray rghRows, PULONG_PTR pcRowsUndone, PPHROW prgRowsUndone, PPDBROWSTATUS prgRowStatus) = 0 ;
	virtual HRESULT __safecall Update(NativeUInt hReserved, NativeUInt cRows, PUintArray rghRows, PULONG_PTR pcRows, PPHROW prgRows, PPDBROWSTATUS prgRowStatus) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A82-2A1C-11CE-ADE5-00AA0044773D}") IRowsetIndex  : public System::IInterface 
{
	virtual HRESULT __stdcall GetIndexInfo(NativeUInt &pcKeyColumns, /* out */ PDBIndexColumnDesc &prgIndexColumnDesc, unsigned &pcIndexProperties, /* out */ PDBPropSet &prgIndexProperties) = 0 ;
	virtual HRESULT __stdcall Seek(NativeUInt HACCESSOR, NativeUInt cKeyValues, void * pData, unsigned dwSeekOptions) = 0 ;
	virtual HRESULT __stdcall SetRange(NativeUInt HACCESSOR, NativeUInt cStartKeyColumns, void * pStartData, NativeUInt cEndKeyColumns, void * pEndData, unsigned dwRangeOptions) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A82-2A1C-11CE-ADE5-00AA0044773D}") IRowsetIndexSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetIndexInfo(NativeUInt &pcKeyColumns, /* out */ PDBIndexColumnDesc &prgIndexColumnDesc, unsigned &pcIndexProperties, /* out */ PDBPropSet &prgIndexProperties) = 0 ;
	virtual HRESULT __safecall Seek(NativeUInt HACCESSOR, NativeUInt cKeyValues, void * pData, unsigned dwSeekOptions) = 0 ;
	virtual HRESULT __safecall SetRange(NativeUInt HACCESSOR, NativeUInt cStartKeyColumns, void * pStartData, NativeUInt cEndKeyColumns, void * pEndData, unsigned dwRangeOptions) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A90-2A1C-11CE-ADE5-00AA0044773D}") IMultipleResults  : public System::IInterface 
{
	virtual HRESULT __stdcall GetResult(const System::_di_IInterface punkOuter, NativeInt reserved, const GUID &riid, PLONG_PTR pcRowsAffected, PIUnknown ppRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A90-2A1C-11CE-ADE5-00AA0044773D}") IMultipleResultsSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetResult(const System::_di_IInterface punkOuter, int reserved, const GUID &riid, PLONG_PTR pcRowsAffected, PIUnknown ppRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A88-2A1C-11CE-ADE5-00AA0044773D}") IConvertType  : public System::IInterface 
{
	virtual HRESULT __stdcall CanConvert(System::Word wFromType, System::Word wToType, unsigned dwConvertFlags) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A88-2A1C-11CE-ADE5-00AA0044773D}") IConvertTypeSC  : public System::IInterface 
{
	virtual HRESULT __safecall CanConvert(System::Word wFromType, System::Word wToType, unsigned dwConvertFlags) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A26-2A1C-11CE-ADE5-00AA0044773D}") ICommandPrepare  : public System::IInterface 
{
	virtual HRESULT __stdcall Prepare(unsigned cExpectedRuns) = 0 ;
	virtual HRESULT __stdcall Unprepare() = 0 ;
};

__interface  INTERFACE_UUID("{0C733A26-2A1C-11CE-ADE5-00AA0044773D}") ICommandPrepareSC  : public System::IInterface 
{
	virtual HRESULT __safecall Prepare(unsigned cExpectedRuns) = 0 ;
	virtual HRESULT __safecall Unprepare() = 0 ;
};

__interface  INTERFACE_UUID("{0C733A79-2A1C-11CE-ADE5-00AA0044773D}") ICommandProperties  : public System::IInterface 
{
	virtual HRESULT __stdcall GetProperties(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, unsigned &pcPropertySets, /* out */ PDBPropSet &prgPropertySets) = 0 ;
	virtual HRESULT __stdcall SetProperties(unsigned cPropertySets, PDBPropSetArray rgPropertySets) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A79-2A1C-11CE-ADE5-00AA0044773D}") ICommandPropertiesSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetProperties(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, unsigned &pcPropertySets, /* out */ PDBPropSet &prgPropertySets) = 0 ;
	virtual HRESULT __safecall SetProperties(unsigned cPropertySets, PDBPropSetArray rgPropertySets) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A63-2A1C-11CE-ADE5-00AA0044773D}") ICommand  : public System::IInterface 
{
	virtual HRESULT __stdcall Cancel() = 0 ;
	virtual HRESULT __stdcall Execute(const System::_di_IInterface punkOuter, const GUID &riid, DBPARAMS &pParams, PLONG_PTR pcRowsAffected, PIUnknown ppRowset) = 0 ;
	virtual HRESULT __stdcall GetDBSession(const GUID &riid, /* out */ System::_di_IInterface &ppSession) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A63-2A1C-11CE-ADE5-00AA0044773D}") ICommandSC  : public System::IInterface 
{
	virtual HRESULT __safecall Cancel() = 0 ;
	virtual HRESULT __safecall Execute(const System::_di_IInterface punkOuter, const GUID &riid, DBPARAMS &pParams, PLONG_PTR pcRowsAffected, PIUnknown ppRowset) = 0 ;
	virtual HRESULT __safecall GetDBSession(const GUID &riid, /* out */ System::_di_IInterface &ppSession) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A64-2A1C-11CE-ADE5-00AA0044773D}") ICommandWithParameters  : public System::IInterface 
{
	virtual HRESULT __stdcall GetParameterInfo(NativeUInt &pcParams, /* out */ PDBParamInfo &prgParamInfo, Winapi::Activex::PPOleStr ppNamesBuffer) = 0 ;
	virtual HRESULT __stdcall MapParameterNames(NativeUInt cParamNames, Winapi::Activex::POleStrList rgParamNames, PULONG_PTRArray rgParamOrdinals) = 0 ;
	virtual HRESULT __stdcall SetParameterInfo(NativeUInt cParams, PULONG_PTRArray rgParamOrdinals, PDBParamBindInfoArray rgParamBindInfo) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A64-2A1C-11CE-ADE5-00AA0044773D}") ICommandWithParametersSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetParameterInfo(NativeUInt &pcParams, /* out */ PDBParamInfo &prgParamInfo, Winapi::Activex::PPOleStr ppNamesBuffer) = 0 ;
	virtual HRESULT __safecall MapParameterNames(NativeUInt cParamNames, Winapi::Activex::POleStrList rgParamNames, PULONG_PTRArray rgParamOrdinals) = 0 ;
	virtual HRESULT __safecall SetParameterInfo(NativeUInt cParams, PULONG_PTRArray rgParamOrdinals, PDBParamBindInfoArray rgParamBindInfo) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A27-2A1C-11CE-ADE5-00AA0044773D}") ICommandText  : public ICommand 
{
	virtual HRESULT __stdcall GetCommandText(GUID &pguidDialect, /* out */ System::WideChar * &ppwszCommand) = 0 ;
	virtual HRESULT __stdcall SetCommandText(const GUID &guidDialect, System::WideChar * pwszCommand) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A27-2A1C-11CE-ADE5-00AA0044773D}") ICommandTextP  : public ICommand 
{
	virtual HRESULT __stdcall GetCommandText(System::PGUID pguidDialect, /* out */ System::WideChar * &ppwszCommand) = 0 ;
	virtual HRESULT __stdcall SetCommandText(const GUID &guidDialect, System::WideChar * pwszCommand) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A27-2A1C-11CE-ADE5-00AA0044773D}") ICommandTextSC  : public ICommandSC 
{
	virtual HRESULT __safecall GetCommandText(GUID &pguidDialect, /* out */ System::WideChar * &ppwszCommand) = 0 ;
	virtual HRESULT __safecall SetCommandText(const GUID &guidDialect, System::WideChar * pwszCommand) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A27-2A1C-11CE-ADE5-00AA0044773D}") ICommandTextSCP  : public ICommandSC 
{
	virtual HRESULT __safecall GetCommandText(System::PGUID pguidDialect, /* out */ System::WideChar * &ppwszCommand) = 0 ;
	virtual HRESULT __safecall SetCommandText(const GUID &guidDialect, System::WideChar * pwszCommand) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A10-2A1C-11CE-ADE5-00AA0044773D}") IColumnsRowset  : public System::IInterface 
{
	virtual HRESULT __stdcall GetAvailableColumns(NativeUInt &pcOptColumns, PDBID &prgOptColumns) = 0 ;
	virtual HRESULT __stdcall GetColumnsRowset(const System::_di_IInterface punkOuter, NativeUInt cOptColumns, PDBIDArray rgOptColumns, const GUID &riid, unsigned cPropertySets, PDBPropSetArray rgPropertySets, /* out */ System::_di_IInterface &pColRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A10-2A1C-11CE-ADE5-00AA0044773D}") IColumnsRowsetSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetAvailableColumns(NativeUInt &pcOptColumns, PDBID &prgOptColumns) = 0 ;
	virtual HRESULT __safecall GetColumnsRowset(const System::_di_IInterface punkOuter, NativeUInt cOptColumns, PDBIDArray rgOptColumns, const GUID &riid, unsigned cPropertySets, PDBPropSetArray rgPropertySets, /* out */ System::_di_IInterface &pColRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A11-2A1C-11CE-ADE5-00AA0044773D}") IColumnsInfo  : public System::IInterface 
{
	virtual HRESULT __stdcall GetColumnInfo(NativeUInt &pcColumns, /* out */ PDBColumnInfo &prgInfo, /* out */ System::WideChar * &ppStringsBuffer) = 0 ;
	virtual HRESULT __stdcall MapColumnIDs(NativeUInt cColumnIDs, PDBIDArray rgColumnIDs, PULONG_PTRArray rgColumns) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A11-2A1C-11CE-ADE5-00AA0044773D}") IColumnsInfoSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetColumnInfo(NativeUInt &pcColumns, /* out */ PDBColumnInfo &prgInfo, /* out */ System::WideChar * &ppStringsBuffer) = 0 ;
	virtual HRESULT __safecall MapColumnIDs(NativeUInt cColumnIDs, PDBIDArray rgColumnIDs, PULONG_PTRArray rgColumns) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A1D-2A1C-11CE-ADE5-00AA0044773D}") IDBCreateCommand  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateCommand(const System::_di_IInterface punkOuter, const GUID &riid, /* out */ System::_di_IInterface &ppCommand) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A1D-2A1C-11CE-ADE5-00AA0044773D}") IDBCreateCommandSC  : public System::IInterface 
{
	virtual HRESULT __safecall CreateCommand(const System::_di_IInterface punkOuter, const GUID &riid, /* out */ System::_di_IInterface &ppCommand) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A5D-2A1C-11CE-ADE5-00AA0044773D}") IDBCreateSession  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateSession(const System::_di_IInterface punkOuter, const GUID &riid, /* out */ System::_di_IInterface &ppDBSession) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A5D-2A1C-11CE-ADE5-00AA0044773D}") IDBCreateSessionSC  : public System::IInterface 
{
	virtual HRESULT __safecall CreateSession(const System::_di_IInterface punkOuter, const GUID &riid, /* out */ System::_di_IInterface &ppDBSession) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A1E-2A1C-11CE-ADE5-00AA0044773D}") ISourcesRowset  : public System::IInterface 
{
	virtual HRESULT __stdcall GetSourcesRowset(const System::_di_IInterface punkOuter, const GUID &riid, unsigned cPropertySets, PDBPropSetArray rgProperties, /* out */ System::_di_IInterface &ppSourcesRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A1E-2A1C-11CE-ADE5-00AA0044773D}") ISourcesRowsetSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetSourcesRowset(const System::_di_IInterface punkOuter, const GUID &riid, unsigned cPropertySets, PDBPropSetArray rgProperties, /* out */ System::_di_IInterface &ppSourcesRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A8A-2A1C-11CE-ADE5-00AA0044773D}") IDBProperties  : public System::IInterface 
{
	virtual HRESULT __stdcall GetProperties(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, unsigned &pcPropertySets, /* out */ PDBPropSet &prgPropertySets) = 0 ;
	virtual HRESULT __stdcall GetPropertyInfo(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, unsigned &pcPropertyInfoSets, /* out */ PDBPropInfoSet &prgPropertyInfoSets, Winapi::Activex::PPOleStr ppDescBuffer) = 0 ;
	virtual HRESULT __stdcall SetProperties(unsigned cPropertySets, PDBPropSetArray rgPropertySets) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A8A-2A1C-11CE-ADE5-00AA0044773D}") IDBPropertiesSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetProperties(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, unsigned &pcPropertySets, /* out */ PDBPropSet &prgPropertySets) = 0 ;
	virtual HRESULT __safecall GetPropertyInfo(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, unsigned &pcPropertyInfoSets, /* out */ PDBPropInfoSet &prgPropertyInfoSets, Winapi::Activex::PPOleStr ppDescBuffer) = 0 ;
	virtual HRESULT __safecall SetProperties(unsigned cPropertySets, PDBPropSet rgPropertySets) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A8B-2A1C-11CE-ADE5-00AA0044773D}") IDBInitialize  : public System::IInterface 
{
	virtual HRESULT __stdcall Initialize() = 0 ;
	virtual HRESULT __stdcall Uninitialize() = 0 ;
};

__interface  INTERFACE_UUID("{0C733A8B-2A1C-11CE-ADE5-00AA0044773D}") IDBInitializeSC  : public System::IInterface 
{
	virtual HRESULT __safecall Initialize() = 0 ;
	virtual HRESULT __safecall Uninitialize() = 0 ;
};

__interface  INTERFACE_UUID("{0C733A89-2A1C-11CE-ADE5-00AA0044773D}") IDBInfo  : public System::IInterface 
{
	virtual HRESULT __stdcall GetKeywords(/* out */ System::WideChar * &ppwszKeywords) = 0 ;
	virtual HRESULT __stdcall GetLiteralInfo(unsigned cLiterals, PUintArray rgLiterals, unsigned &pcLiteralInfo, /* out */ PDBLiteralInfo &prgLiteralInfo, /* out */ System::WideChar * &ppCharBuffer) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A89-2A1C-11CE-ADE5-00AA0044773D}") IDBInfoSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetKeywords(/* out */ System::WideChar * &ppwszKeywords) = 0 ;
	virtual HRESULT __safecall GetLiteralInfo(unsigned cLiterals, PUintArray rgLiterals, unsigned &pcLiteralInfo, /* out */ PDBLiteralInfo &prgLiteralInfo, /* out */ System::WideChar * &ppCharBuffer) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A7A-2A1C-11CE-ADE5-00AA0044773D}") IDBDataSourceAdmin  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateDataSource(unsigned cPropertySets, PDBPropSetArray rgPropertySets, const System::_di_IInterface punkOuter, const GUID &riid, /* out */ System::_di_IInterface &ppDBSession) = 0 ;
	virtual HRESULT __stdcall DestroyDataSource() = 0 ;
	virtual HRESULT __stdcall GetCreationProperties(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, PUINT pcPropertyInfoSets, /* out */ PDBPropInfoSet &prgPropertyInfoSets, Winapi::Activex::PPOleStr ppDescBuffer) = 0 ;
	virtual HRESULT __stdcall ModifyDataSource(unsigned cPropertySets, PDBPropSetArray rgPropertySets) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A7A-2A1C-11CE-ADE5-00AA0044773D}") IDBDataSourceAdminSC  : public System::IInterface 
{
	virtual HRESULT __safecall CreateDataSource(unsigned cPropertySets, PDBPropSetArray rgPropertySets, const System::_di_IInterface punkOuter, const GUID &riid, /* out */ System::_di_IInterface &ppDBSession) = 0 ;
	virtual HRESULT __safecall DestroyDataSource() = 0 ;
	virtual HRESULT __safecall GetCreationProperties(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, PUINT pcPropertyInfoSets, /* out */ PDBPropInfoSet &prgPropertyInfoSets, Winapi::Activex::PPOleStr ppDescBuffer) = 0 ;
	virtual HRESULT __safecall ModifyDataSource(unsigned cPropertySets, PDBPropSetArray rgPropertySets) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A85-2A1C-11CE-ADE5-00AA0044773D}") ISessionProperties  : public System::IInterface 
{
	virtual HRESULT __stdcall GetProperties(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, unsigned &pcPropertySets, /* out */ PDBPropSet &prgPropertySets) = 0 ;
	virtual HRESULT __stdcall SetProperties(unsigned cPropertySets, PDBPropSetArray rgPropertySets) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A85-2A1C-11CE-ADE5-00AA0044773D}") ISessionPropertiesSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetProperties(unsigned cPropertyIDSets, PDBPropIDSetArray rgPropertyIDSets, unsigned &pcPropertySets, /* out */ PDBPropSet &prgPropertySets) = 0 ;
	virtual HRESULT __safecall SetProperties(unsigned cPropertySets, PDBPropSetArray rgPropertySets) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A68-2A1C-11CE-ADE5-00AA0044773D}") IIndexDefinition  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateIndex(DBID &pTableID, PDBID pIndexID, NativeUInt cIndexColumnDescs, PDBIndexColumnDescArray rgIndexColumnDescs, unsigned cPropertySets, PDBPropSetArray rgPropertySets, PPDBID ppIndexID) = 0 ;
	virtual HRESULT __stdcall DropIndex(DBID &TableID, PDBID pIndexID) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A68-2A1C-11CE-ADE5-00AA0044773D}") IIndexDefinitionSC  : public System::IInterface 
{
	virtual HRESULT __safecall CreateIndex(DBID &pTableID, PDBID pIndexID, NativeUInt cIndexColumnDescs, PDBIndexColumnDescArray rgIndexColumnDescs, unsigned cPropertySets, PDBPropSetArray rgPropertySets, PPDBID ppIndexID) = 0 ;
	virtual HRESULT __safecall DropIndex(DBID &TableID, PDBID pIndexID) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A86-2A1C-11CE-ADE5-00AA0044773D}") ITableDefinition  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateTable(const System::_di_IInterface punkOuter, PDBID pTableID, NativeUInt cColumnDescs, PDBColumnDescArray rgColumnDescs, const GUID &riid, unsigned cPropertySets, PDBPropSetArray rgPropertySets, PPDBID ppTableID, PIUnknown ppRowset) = 0 ;
	virtual HRESULT __stdcall DropTable(DBID &pTableID) = 0 ;
	virtual HRESULT __stdcall AddColumn(DBID &pTableID, DBCOLUMNDESC &pColumnDesc, PPDBID ppColumnID) = 0 ;
	virtual HRESULT __stdcall DropColumn(DBID &pTableID, DBID &pColumnID) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A86-2A1C-11CE-ADE5-00AA0044773D}") ITableDefinitionSC  : public System::IInterface 
{
	virtual HRESULT __safecall CreateTable(const System::_di_IInterface punkOuter, PDBID pTableID, NativeUInt cColumnDescs, PDBColumnDescArray rgColumnDescs, const GUID &riid, unsigned cPropertySets, PDBPropSetArray rgPropertySets, PPDBID ppTableID, PIUnknown ppRowset) = 0 ;
	virtual HRESULT __safecall DropTable(DBID &pTableID) = 0 ;
	virtual HRESULT __safecall AddColumn(DBID &pTableID, DBCOLUMNDESC &pColumnDesc, PPDBID ppColumnID) = 0 ;
	virtual HRESULT __safecall DropColumn(DBID &pTableID, DBID &pColumnID) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A69-2A1C-11CE-ADE5-00AA0044773D}") IOpenRowset  : public System::IInterface 
{
	virtual HRESULT __stdcall OpenRowset(const System::_di_IInterface punkOuter, PDBID pTableID, PDBID pIndexID, const GUID &riid, unsigned cPropertySets, PDBPropSetArray rgPropertySets, PIUnknown ppRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A69-2A1C-11CE-ADE5-00AA0044773D}") IOpenRowsetSC  : public System::IInterface 
{
	virtual HRESULT __safecall OpenRowset(const System::_di_IInterface punkOuter, PDBID pTableID, PDBID pIndexID, const GUID &riid, unsigned cPropertySets, PDBPropSetArray rgPropertySets, PIUnknown ppRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A66-2A1C-11CE-ADE5-00AA0044773D}") IErrorLookup  : public System::IInterface 
{
	virtual HRESULT __stdcall GetErrorDescription(HRESULT hrError, unsigned dwLookupID, Winapi::Activex::PDispParams pdispparams, unsigned lcid, /* out */ System::WideString &pbstrSource, /* out */ System::WideString &pbstrDescription) = 0 ;
	virtual HRESULT __stdcall GetHelpInfo(HRESULT hrError, unsigned dwLookupID, unsigned lcid, /* out */ System::WideString &pbstrHelpFile, /* out */ unsigned &pdwHelpContext) = 0 ;
	virtual HRESULT __stdcall ReleaseErrors(unsigned dwDynamicErrorID) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A66-2A1C-11CE-ADE5-00AA0044773D}") IErrorLookupSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetErrorDescription(HRESULT hrError, unsigned dwLookupID, Winapi::Activex::PDispParams pdispparams, unsigned lcid, /* out */ System::WideString &pbstrSource, /* out */ System::WideString &pbstrDescription) = 0 ;
	virtual HRESULT __safecall GetHelpInfo(HRESULT hrError, unsigned dwLookupID, unsigned lcid, /* out */ System::WideString &pbstrHelpFile, /* out */ unsigned &pdwHelpContext) = 0 ;
	virtual HRESULT __safecall ReleaseErrors(unsigned dwDynamicErrorID) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A74-2A1C-11CE-ADE5-00AA0044773D}") ISQLErrorInfo  : public System::IInterface 
{
	virtual HRESULT __stdcall GetSQLInfo(/* out */ System::WideString &pbstrSQLState, /* out */ int &plNativeError) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A74-2A1C-11CE-ADE5-00AA0044773D}") ISQLErrorInfoSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetSQLInfo(/* out */ System::WideString &pbstrSQLState, /* out */ int &plNativeError) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A75-2A1C-11CE-ADE5-00AA0044773D}") IGetDataSource  : public System::IInterface 
{
	virtual HRESULT __stdcall GetDataSource(const GUID &riid, /* out */ System::_di_IInterface &ppDataSource) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A75-2A1C-11CE-ADE5-00AA0044773D}") IGetDataSourceSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetDataSource(const GUID &riid, /* out */ System::_di_IInterface &ppDataSource) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A5F-2A1C-11CE-ADE5-00AA0044773D}") ITransactionLocal  : public ITransaction 
{
	virtual HRESULT __stdcall GetOptionsObject(/* out */ _di_ITransactionOptions &ppOptions) = 0 ;
	virtual HRESULT __stdcall StartTransaction(int isoLevel, unsigned isoFlags, const _di_ITransactionOptions pOtherOptions, PUINT pulTransactionLevel) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A5F-2A1C-11CE-ADE5-00AA0044773D}") ITransactionLocalSC  : public ITransactionSC 
{
	virtual HRESULT __safecall GetOptionsObject(/* out */ _di_ITransactionOptions &ppOptions) = 0 ;
	virtual HRESULT __safecall StartTransaction(int isoLevel, unsigned isoFlags, const _di_ITransactionOptions pOtherOptions, PUINT pulTransactionLevel) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A5E-2A1C-11CE-ADE5-00AA0044773D}") ITransactionJoin  : public System::IInterface 
{
	virtual HRESULT __stdcall GetOptionsObject(/* out */ _di_ITransactionOptions &ppOptions) = 0 ;
	virtual HRESULT __stdcall JoinTransaction(const System::_di_IInterface punkTransactionCoord, int isoLevel, unsigned isoFlags, const _di_ITransactionOptions pOtherOptions) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A5E-2A1C-11CE-ADE5-00AA0044773D}") ITransactionJoinSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetOptionsObject(/* out */ _di_ITransactionOptions &ppOptions) = 0 ;
	virtual HRESULT __safecall JoinTransaction(const System::_di_IInterface punkTransactionCoord, int isoLevel, unsigned isoFlags, const _di_ITransactionOptions pOtherOptions) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A60-2A1C-11CE-ADE5-00AA0044773D}") ITransactionObject  : public System::IInterface 
{
	virtual HRESULT __stdcall GetTransactionObject(unsigned ulTransactionLevel, /* out */ _di_ITransaction &ppTransactionObject) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A60-2A1C-11CE-ADE5-00AA0044773D}") ITransactionObjectSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetTransactionObject(unsigned ulTransactionLevel, /* out */ _di_ITransaction &ppTransactionObject) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A95-2A1C-11CE-ADE5-00AA0044773D}") IDBAsynchStatus  : public System::IInterface 
{
	virtual HRESULT __stdcall Abort(NativeUInt HCHAPTER, unsigned eOperation) = 0 ;
	virtual HRESULT __stdcall GetStatus(NativeUInt HCHAPTER, unsigned eOperation, PULONG_PTR pulProgress, PULONG_PTR pulProgressMax, PDBASYNCHPHASE peAsynchPhase, Winapi::Activex::PPOleStr ppwszStatusText) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A95-2A1C-11CE-ADE5-00AA0044773D}") IDBAsynchStatusSC  : public System::IInterface 
{
	virtual HRESULT __safecall Abort(NativeUInt HCHAPTER, unsigned eOperation) = 0 ;
	virtual HRESULT __safecall GetStatus(NativeUInt HCHAPTER, unsigned eOperation, PULONG_PTR pulProgress, PULONG_PTR pulProgressMax, PDBASYNCHPHASE peAsynchPhase, Winapi::Activex::PPOleStr ppwszStatusText) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A9D-2A1C-11CE-ADE5-00AA0044773D}") IRowsetFind  : public System::IInterface 
{
	virtual HRESULT __stdcall FindNextRow(NativeUInt HCHAPTER, NativeUInt HACCESSOR, void * pFindValue, unsigned CompareOp, NativeUInt cbBookmark, System::PByte pBookmark, NativeInt lRowsOffset, NativeInt cRows, NativeUInt &pcRowsObtained, /* out */ PHROW &prghRows) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A9D-2A1C-11CE-ADE5-00AA0044773D}") IRowsetFindSC  : public System::IInterface 
{
	virtual HRESULT __safecall FindNextRow(NativeUInt HCHAPTER, NativeUInt HACCESSOR, void * pFindValue, unsigned CompareOp, NativeUInt cbBookmark, System::PByte pBookmark, NativeInt lRowsOffset, NativeInt cRows, NativeUInt &pcRowsObtained, /* out */ PHROW &prghRows) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A94-2A1C-11CE-ADE5-00AA0044773D}") IRowPosition  : public System::IInterface 
{
	virtual HRESULT __stdcall ClearRowPosition() = 0 ;
	virtual HRESULT __stdcall GetRowPosition(/* out */ NativeUInt &phChapter, /* out */ NativeUInt &phRow, /* out */ unsigned &pdwPositionFlags) = 0 ;
	virtual HRESULT __stdcall GetRowset(const GUID &riid, /* out */ System::_di_IInterface &ppRowset) = 0 ;
	virtual HRESULT __stdcall Initialize(const System::_di_IInterface pRowset) = 0 ;
	virtual HRESULT __stdcall SetRowPosition(NativeUInt HCHAPTER, NativeUInt HROW, unsigned dwPositionFlags) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A94-2A1C-11CE-ADE5-00AA0044773D}") IRowPositionSC  : public System::IInterface 
{
	virtual HRESULT __safecall ClearRowPosition() = 0 ;
	virtual HRESULT __safecall GetRowPosition(/* out */ NativeUInt &phChapter, /* out */ NativeUInt &phRow, /* out */ unsigned &pdwPositionFlags) = 0 ;
	virtual HRESULT __safecall GetRowset(const GUID &riid, /* out */ System::_di_IInterface &ppRowset) = 0 ;
	virtual HRESULT __safecall Initialize(const System::_di_IInterface pRowset) = 0 ;
	virtual HRESULT __safecall SetRowPosition(NativeUInt HCHAPTER, NativeUInt HROW, unsigned dwPositionFlags) = 0 ;
};

__interface  INTERFACE_UUID("{0997A571-126E-11D0-9F8A-00A0C9A0631E}") IRowPositionChange  : public System::IInterface 
{
	virtual HRESULT __stdcall OnRowPositionChange(unsigned eReason, unsigned ePhase, System::LongBool fCantDeny) = 0 ;
};

__interface  INTERFACE_UUID("{0997A571-126E-11D0-9F8A-00A0C9A0631E}") IRowPositionChangeSC  : public System::IInterface 
{
	virtual HRESULT __safecall OnRowPositionChange(unsigned eReason, unsigned ePhase, System::LongBool fCantDeny) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A97-2A1C-11CE-ADE5-00AA0044773D}") IViewRowset  : public System::IInterface 
{
	virtual HRESULT __stdcall GetSpecification(const GUID &riid, /* out */ System::_di_IInterface &ppObject) = 0 ;
	virtual HRESULT __stdcall OpenViewRowset(const System::_di_IInterface punkOuter, const GUID &riid, /* out */ System::_di_IInterface &ppRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A97-2A1C-11CE-ADE5-00AA0044773D}") IViewRowsetSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetSpecification(const GUID &riid, /* out */ System::_di_IInterface &ppObject) = 0 ;
	virtual HRESULT __safecall OpenViewRowset(const System::_di_IInterface punkOuter, const GUID &riid, /* out */ System::_di_IInterface &ppRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A98-2A1C-11CE-ADE5-00AA0044773D}") IViewChapter  : public System::IInterface 
{
	virtual HRESULT __stdcall GetSpecification(const GUID &riid, /* out */ System::_di_IInterface &ppRowset) = 0 ;
	virtual HRESULT __stdcall OpenViewChapter(NativeUInt hSource, /* out */ NativeUInt &phViewChapter) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A98-2A1C-11CE-ADE5-00AA0044773D}") IViewChapterSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetSpecification(const GUID &riid, /* out */ System::_di_IInterface &ppRowset) = 0 ;
	virtual HRESULT __safecall OpenViewChapter(NativeUInt hSource, /* out */ NativeUInt &phViewChapter) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A9A-2A1C-11CE-ADE5-00AA0044773D}") IViewSort  : public System::IInterface 
{
	virtual HRESULT __stdcall GetSortOrder(/* out */ NativeUInt &pcValues, /* out */ PULONG_PTRArray &prgColumns, /* out */ PUintArray &prgOrders) = 0 ;
	virtual HRESULT __stdcall SetSortOrder(NativeUInt cValues, PULONG_PTRArray rgColumns, PUintArray rgOrders) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A9A-2A1C-11CE-ADE5-00AA0044773D}") IViewSortSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetSortOrder(/* out */ NativeUInt &pcValues, /* out */ PULONG_PTRArray &prgColumns, /* out */ PUintArray &prgOrders) = 0 ;
	virtual HRESULT __safecall SetSortOrder(NativeUInt cValues, PULONG_PTRArray rgColumns, PUintArray rgOrders) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A9B-2A1C-11CE-ADE5-00AA0044773D}") IViewFilter  : public System::IInterface 
{
	virtual HRESULT __stdcall GetFilter(NativeUInt HACCESSOR, /* out */ NativeUInt &pcRows, /* out */ PDBCOMPAREOP &pCompareOps, void * pCriteriaData) = 0 ;
	virtual HRESULT __stdcall GetFilterBindings(/* out */ NativeUInt &pcBindings, /* out */ PDBBinding &prgBindings) = 0 ;
	virtual HRESULT __stdcall SetFilter(NativeUInt HACCESSOR, NativeUInt cRows, unsigned &CompareOps, void * pCriteriaData) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A9B-2A1C-11CE-ADE5-00AA0044773D}") IViewFilterSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetFilter(NativeUInt HACCESSOR, /* out */ NativeUInt &pcRows, /* out */ PDBCOMPAREOP &pCompareOps, void * pCriteriaData) = 0 ;
	virtual HRESULT __safecall GetFilterBindings(/* out */ NativeUInt &pcBindings, /* out */ PDBBinding &prgBindings) = 0 ;
	virtual HRESULT __safecall SetFilter(NativeUInt HACCESSOR, NativeUInt cRows, unsigned &CompareOps, void * pCriteriaData) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A99-2A1C-11CE-ADE5-00AA0044773D}") IRowsetView  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateView(const System::_di_IInterface punkOuter, const GUID &riid, /* out */ System::_di_IInterface &ppView) = 0 ;
	virtual HRESULT __stdcall GetView(NativeUInt HCHAPTER, const GUID &riid, /* out */ NativeUInt &phChapterSource, /* out */ System::_di_IInterface &ppView) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A99-2A1C-11CE-ADE5-00AA0044773D}") IRowsetViewSC  : public System::IInterface 
{
	virtual HRESULT __safecall CreateView(const System::_di_IInterface punkOuter, const GUID &riid, /* out */ System::_di_IInterface &ppView) = 0 ;
	virtual HRESULT __safecall GetView(NativeUInt HCHAPTER, const GUID &riid, /* out */ NativeUInt &phChapterSource, /* out */ System::_di_IInterface &ppView) = 0 ;
};

__interface  INTERFACE_UUID("{A07CCCD2-8148-11D0-87BB-00C04FC33942}") IMDFind  : public System::IInterface 
{
	virtual HRESULT __stdcall FindCell(NativeUInt ulStartingOrdinal, NativeUInt cMembers, Winapi::Activex::PPOleStr rgpwszMember, /* out */ NativeUInt &pulCellOrdinal) = 0 ;
	virtual HRESULT __stdcall FindTuple(unsigned ulAxisIdentifier, NativeUInt ulStartingOrdinal, NativeUInt cMembers, Winapi::Activex::PPOleStr rgpwszMember, /* out */ unsigned &pulTupleOrdinal) = 0 ;
};

__interface  INTERFACE_UUID("{A07CCCD2-8148-11D0-87BB-00C04FC33942}") IMDFindSC  : public System::IInterface 
{
	virtual HRESULT __safecall FindCell(NativeUInt ulStartingOrdinal, NativeUInt cMembers, Winapi::Activex::PPOleStr rgpwszMember, /* out */ NativeUInt &pulCellOrdinal) = 0 ;
	virtual HRESULT __safecall FindTuple(unsigned ulAxisIdentifier, NativeUInt ulStartingOrdinal, NativeUInt cMembers, Winapi::Activex::PPOleStr rgpwszMember, /* out */ unsigned &pulTupleOrdinal) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA0-2A1C-11CE-ADE5-00AA0044773D}") IMDRangeRowset  : public System::IInterface 
{
	virtual HRESULT __stdcall GetRangeRowset(const System::_di_IInterface punkOuter, NativeUInt ulStartCell, NativeUInt ulEndCell, const GUID &riid, unsigned cPropertySets, PDBPropSetArray rgPropertySets, /* out */ System::_di_IInterface &ppRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA0-2A1C-11CE-ADE5-00AA0044773D}") IMDRangeRowsetSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetRangeRowset(const System::_di_IInterface punkOuter, NativeUInt ulStartCell, NativeUInt ulEndCell, const GUID &riid, unsigned cPropertySets, PDBPropSetArray rgPropertySets, /* out */ System::_di_IInterface &ppRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA5-2A1C-11CE-ADE5-00AA0044773D}") IAlterTable  : public System::IInterface 
{
	virtual HRESULT __stdcall AlterColumn(DBID &pTableID, DBID &pColumnID, unsigned ColumnDescFlags, DBCOLUMNDESC &pColumnDesc) = 0 ;
	virtual HRESULT __stdcall AlterTable(DBID &pTableID, PDBID pNewTableId, unsigned cPropertySets, PDBPropSetArray rgPropertySets) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA5-2A1C-11CE-ADE5-00AA0044773D}") IAlterTableSC  : public System::IInterface 
{
	virtual HRESULT __safecall AlterColumn(DBID &pTableID, DBID &pColumnID, unsigned ColumnDescFlags, DBCOLUMNDESC &pColumnDesc) = 0 ;
	virtual HRESULT __safecall AlterTable(DBID &pTableID, PDBID pNewTableId, unsigned cPropertySets, PDBPropSetArray rgPropertySets) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA6-2A1C-11CE-ADE5-00AA0044773D}") IAlterIndex  : public System::IInterface 
{
	virtual HRESULT __stdcall AlterIndex(DBID &pTableID, DBID &pIndexID, PDBID pNewIndexId, unsigned cPropertySets, PDBPropSetArray rgPropertySet) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA6-2A1C-11CE-ADE5-00AA0044773D}") IAlterIndexSC  : public System::IInterface 
{
	virtual HRESULT __safecall AlterIndex(DBID &pTableID, DBID &pIndexID, PDBID pNewIndexId, unsigned cPropertySets, PDBPropSetArray rgPropertySet) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA7-2A1C-11CE-ADE5-00AA0044773D}") ICommandPersist  : public System::IInterface 
{
	virtual HRESULT __stdcall DeleteCommand(DBID &pCommandID) = 0 ;
	virtual HRESULT __stdcall GetCurrentCommand(/* out */ PDBID &ppCommandID) = 0 ;
	virtual HRESULT __stdcall LoadCommand(DBID &pCommandID, unsigned dwFlags) = 0 ;
	virtual HRESULT __stdcall SaveCommand(DBID &pCommandID, unsigned dwFlags) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA7-2A1C-11CE-ADE5-00AA0044773D}") ICommandPersistSC  : public System::IInterface 
{
	virtual HRESULT __safecall DeleteCommand(DBID &pCommandID) = 0 ;
	virtual HRESULT __safecall GetCurrentCommand(/* out */ PDBID &ppCommandID) = 0 ;
	virtual HRESULT __safecall LoadCommand(DBID &pCommandID, unsigned dwFlags) = 0 ;
	virtual HRESULT __safecall SaveCommand(DBID &pCommandID, unsigned dwFlags) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA8-2A1C-11CE-ADE5-00AA0044773D}") IRowsetChapterMember  : public System::IInterface 
{
	virtual HRESULT __stdcall IsRowInChapter(NativeUInt HCHAPTER, NativeUInt HROW) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA8-2A1C-11CE-ADE5-00AA0044773D}") IRowsetChapterMemberSC  : public System::IInterface 
{
	virtual HRESULT __safecall IsRowInChapter(NativeUInt HCHAPTER, NativeUInt HROW) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA9-2A1C-11CE-ADE5-00AA0044773D}") IRowsetRefresh  : public System::IInterface 
{
	virtual HRESULT __stdcall RefreshVisibleData(NativeUInt HCHAPTER, NativeUInt cRows, PUintArray rghRows, System::LongBool fOverWrite, PULONG_PTR pcRowsRefreshed, /* out */ PHROW &prghRowsRefreshed, PPDBROWSTATUS prgRowStatus) = 0 ;
	virtual HRESULT __stdcall GetLastVisibleData(NativeUInt HROW, NativeUInt HACCESSOR, void * pData) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA9-2A1C-11CE-ADE5-00AA0044773D}") IRowsetRefreshSC  : public System::IInterface 
{
	virtual HRESULT __safecall RefreshVisibleData(NativeUInt HCHAPTER, NativeUInt cRows, PUintArray rghRows, System::LongBool fOverWrite, PULONG_PTR pcRowsRefreshed, /* out */ PHROW &prghRowsRefreshed, PPDBROWSTATUS prgRowStatus) = 0 ;
	virtual HRESULT __safecall GetLastVisibleData(NativeUInt HROW, NativeUInt HACCESSOR, void * pData) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AAA-2A1C-11CE-ADE5-00AA0044773D}") IParentRowset  : public System::IInterface 
{
	virtual HRESULT __stdcall GetChildRowset(const System::_di_IInterface punkOuter, NativeUInt iOrdinal, const GUID &riid, /* out */ System::_di_IInterface &ppRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AAA-2A1C-11CE-ADE5-00AA0044773D}") IParentRowsetSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetChildRowset(const System::_di_IInterface punkOuter, NativeUInt iOrdinal, const GUID &riid, /* out */ System::_di_IInterface &ppRowset) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA2-2A1C-11CE-ADE5-00AA0044773D}") ITrusteeGroupAdmin  : public System::IInterface 
{
	virtual HRESULT __stdcall AddMember(PTrusteeW pMembershipTrustee, PTrusteeW pMemberTrustee) = 0 ;
	virtual HRESULT __stdcall DeleteMember(PTrusteeW pMembershipTrustee, PTrusteeW pMemberTrustee) = 0 ;
	virtual HRESULT __stdcall IsMember(PTrusteeW pMembershipTrustee, PTrusteeW pMemberTrustee, /* out */ System::LongBool &pfStatus) = 0 ;
	virtual HRESULT __stdcall GetMembers(PTrusteeW pMembershipTrustee, PUINT pcMembers, /* out */ PTrusteeW &prgMembers) = 0 ;
	virtual HRESULT __stdcall GetMemberships(PTrusteeW pTrustee, PUINT pcMemberships, /* out */ PTrusteeW &prgMemberships) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA2-2A1C-11CE-ADE5-00AA0044773D}") ITrusteeGroupAdminSC  : public System::IInterface 
{
	virtual HRESULT __safecall AddMember(PTrusteeW pMembershipTrustee, PTrusteeW pMemberTrustee) = 0 ;
	virtual HRESULT __safecall DeleteMember(PTrusteeW pMembershipTrustee, PTrusteeW pMemberTrustee) = 0 ;
	virtual HRESULT __safecall IsMember(PTrusteeW pMembershipTrustee, PTrusteeW pMemberTrustee, /* out */ System::LongBool &pfStatus) = 0 ;
	virtual HRESULT __safecall GetMembers(PTrusteeW pMembershipTrustee, PUINT pcMembers, /* out */ PTrusteeW &prgMembers) = 0 ;
	virtual HRESULT __safecall GetMemberships(PTrusteeW pTrustee, PUINT pcMemberships, /* out */ PTrusteeW &prgMemberships) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA3-2A1C-11CE-ADE5-00AA0044773D}") IObjectAccessControl  : public System::IInterface 
{
	virtual HRESULT __stdcall GetObjectAccessRights(PSecObject pObject, PUINT pcAccessEntries, PExplicitAccessW prgAccessEntries) = 0 ;
	virtual HRESULT __stdcall GetObjectOwner(PSecObject pObject, PPTrusteeW ppOwner) = 0 ;
	virtual HRESULT __stdcall IsObjectAccessAllowed(PSecObject pObject, PExplicitAccessW pAccessEntry, PBOOL pfResult) = 0 ;
	virtual HRESULT __stdcall SetObjectAccessRights(PSecObject pObject, unsigned cAccessEntries, PExplicitAccessW prgAccessEntries) = 0 ;
	virtual HRESULT __stdcall SetObjectOwner(PSecObject pObject, PTrusteeW pOwner) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA3-2A1C-11CE-ADE5-00AA0044773D}") IObjectAccessControlSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetObjectAccessRights(PSecObject pObject, PUINT pcAccessEntries, PExplicitAccessW prgAccessEntries) = 0 ;
	virtual HRESULT __safecall GetObjectOwner(PSecObject pObject, PPTrusteeW ppOwner) = 0 ;
	virtual HRESULT __safecall IsObjectAccessAllowed(PSecObject pObject, PExplicitAccessW pAccessEntry, PBOOL pfResult) = 0 ;
	virtual HRESULT __safecall SetObjectAccessRights(PSecObject pObject, unsigned cAccessEntries, PExplicitAccessW prgAccessEntries) = 0 ;
	virtual HRESULT __safecall SetObjectOwner(PSecObject pObject, PTrusteeW pOwner) = 0 ;
};

__interface  INTERFACE_UUID("{0C733AA4-2A1C-11CE-ADE5-00AA0044773D}") ISecurityInfo  : public System::IInterface 
{
	virtual HRESULT __stdcall GetCurrentTrustee(PPTrusteeW ppTrustee) = 0 ;
	virtual HRESULT __stdcall GetObjectTypes(/* out */ unsigned &cObjectTypes, /* out */ System::PGUID &rgObjectTypes) = 0 ;
#ifndef _WIN64
	virtual HRESULT __stdcall GetPermissions(GUID ObjectType, /* out */ unsigned &pPermissions) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __stdcall GetPermissions(const GUID &ObjectType, /* out */ unsigned &pPermissions) = 0 ;
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{0C733AA4-2A1C-11CE-ADE5-00AA0044773D}") ISecurityInfoSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetCurrentTrustee(PPTrusteeW ppTrustee) = 0 ;
	virtual HRESULT __safecall GetObjectTypes(/* out */ unsigned &cObjectTypes, /* out */ System::PGUID &rgObjectTypes) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall GetPermissions(GUID ObjectType, /* out */ unsigned &pPermissions) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall GetPermissions(const GUID &ObjectType, /* out */ unsigned &pPermissions) = 0 ;
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{2206CCB0-19C1-11D1-89E0-00C04FD7A829}") IDBPromptInitialize  : public System::IInterface 
{
	virtual HRESULT __stdcall PromptDataSource(const System::_di_IInterface pUnkOuter, HWND hWndParent, unsigned dwPromptOptions, unsigned cSourceTypeFilter, PDBSOURCETYPE rgSourceTypeFilter, System::WideChar * pszProviderFilter, const GUID &riid, System::_di_IInterface &DataSource) = 0 ;
	virtual HRESULT __stdcall PromptFileName(HWND hWndParent, unsigned dwPromptOptions, System::WideChar * pwszInitialDirectory, System::WideChar * pwszInitialFile, System::WideChar * &ppwszSelectedFile) = 0 ;
};

__interface  INTERFACE_UUID("{2206CCB0-19C1-11D1-89E0-00C04FD7A829}") IDBPromptInitializeSC  : public System::IInterface 
{
	virtual HRESULT __safecall PromptDataSource(const System::_di_IInterface pUnkOuter, HWND hWndParent, unsigned dwPromptOptions, unsigned cSourceTypeFilter, PDBSOURCETYPE rgSourceTypeFilter, System::WideChar * pszProviderFilter, const GUID &riid, System::_di_IInterface &DataSource) = 0 ;
	virtual HRESULT __safecall PromptFileName(HWND hWndParent, unsigned dwPromptOptions, System::WideChar * pwszInitialDirectory, System::WideChar * pwszInitialFile, System::WideChar * &ppwszSelectedFile) = 0 ;
};

__interface  INTERFACE_UUID("{2206CCB1-19C1-11D1-89E0-00C04FD7A829}") IDataInitialize  : public System::IInterface 
{
	virtual HRESULT __stdcall GetDataSource(const System::_di_IInterface pUnkOuter, unsigned dwClsCtx, System::WideChar * pwszInitializationString, const GUID &riid, System::_di_IInterface &DataSource) = 0 ;
	virtual HRESULT __stdcall GetInitializationString(const System::_di_IInterface DataSource, bool fIncludePassword, /* out */ System::WideChar * &pwszInitString) = 0 ;
	virtual HRESULT __stdcall CreateDBInstance(const GUID &clsidProvider, const System::_di_IInterface pUnkOuter, unsigned dwClsCtx, System::WideChar * pwszReserved, const GUID &riid, System::_di_IInterface &DataSource) = 0 ;
	virtual HRESULT __stdcall CreateDBInstanceEx(const GUID &clsidProvider, const System::_di_IInterface pUnkOuter, unsigned dwClsCtx, System::WideChar * pwszReserved, Winapi::Activex::PCoServerInfo pServerInfo, unsigned cmq, Winapi::Activex::PMultiQI rgmqResults) = 0 ;
	virtual HRESULT __stdcall LoadStringFromStorage(System::WideChar * pwszFileName, /* out */ System::WideChar * &pwszInitializationString) = 0 ;
	virtual HRESULT __stdcall WriteStringToStorage(System::WideChar * pwszFileName, System::WideChar * pwszInitializationString, unsigned dwCreationDisposition) = 0 ;
};

__interface  INTERFACE_UUID("{2206CCB1-19C1-11D1-89E0-00C04FD7A829}") IDataInitializeSC  : public System::IInterface 
{
	virtual HRESULT __safecall GetDataSource(const System::_di_IInterface pUnkOuter, unsigned dwClsCtx, System::WideChar * pwszInitializationString, const GUID &riid, System::_di_IInterface &DataSource) = 0 ;
	virtual HRESULT __safecall GetInitializationString(const System::_di_IInterface DataSource, bool fIncludePassword, /* out */ System::WideChar * &pwszInitString) = 0 ;
	virtual HRESULT __safecall CreateDBInstance(const GUID &clsidProvider, const System::_di_IInterface pUnkOuter, unsigned dwClsCtx, System::WideChar * pwszReserved, const GUID &riid, System::_di_IInterface &DataSource) = 0 ;
	virtual HRESULT __safecall CreateDBInstanceEx(const GUID &clsidProvider, const System::_di_IInterface pUnkOuter, unsigned dwClsCtx, System::WideChar * pwszReserved, Winapi::Activex::PCoServerInfo pServerInfo, unsigned cmq, Winapi::Activex::PMultiQI rgmqResults) = 0 ;
	virtual HRESULT __safecall LoadStringFromStorage(System::WideChar * pwszFileName, /* out */ System::WideChar * &pwszInitializationString) = 0 ;
	virtual HRESULT __safecall WriteStringToStorage(System::WideChar * pwszFileName, System::WideChar * pwszInitializationString, unsigned dwCreationDisposition) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE GUID CLSID_OLEDB_ENUMERATOR;
extern DELPHI_PACKAGE GUID CLSID_EXTENDEDERRORINFO;
extern DELPHI_PACKAGE GUID CLSID_MSDAVTM;
extern DELPHI_PACKAGE GUID CLSID_OLEDB_CONVERSIONLIBRARY;
extern DELPHI_PACKAGE GUID CLSID_OLEDB_ROWPOSITIONLIBRARY;
extern DELPHI_PACKAGE GUID CLSID_DATALINKS;
extern DELPHI_PACKAGE GUID IID_ITransaction;
extern DELPHI_PACKAGE GUID IID_ITransactionOptions;
extern DELPHI_PACKAGE GUID IID_ITransactionDispenser;
extern DELPHI_PACKAGE GUID IID_ITransactionOutcomeEvents;
extern DELPHI_PACKAGE GUID IID_IAccessor;
extern DELPHI_PACKAGE GUID IID_IRowset;
extern DELPHI_PACKAGE GUID IID_IRowsetInfo;
extern DELPHI_PACKAGE GUID IID_IRowsetLocate;
extern DELPHI_PACKAGE GUID IID_IRowsetResynch;
extern DELPHI_PACKAGE GUID IID_IRowsetScroll;
extern DELPHI_PACKAGE GUID IID_IRowsetChange;
extern DELPHI_PACKAGE GUID IID_IRowsetUpdate;
extern DELPHI_PACKAGE GUID IID_IRowsetIndex;
extern DELPHI_PACKAGE GUID IID_IMultipleResults;
extern DELPHI_PACKAGE GUID IID_IConvertType;
extern DELPHI_PACKAGE GUID IID_ICommandPrepare;
extern DELPHI_PACKAGE GUID IID_ICommandProperties;
extern DELPHI_PACKAGE GUID IID_ICommand;
extern DELPHI_PACKAGE GUID IID_ICommandWithParameters;
extern DELPHI_PACKAGE GUID IID_ICommandText;
extern DELPHI_PACKAGE GUID IID_IColumnsRowset;
extern DELPHI_PACKAGE GUID IID_IColumnsInfo;
extern DELPHI_PACKAGE GUID IID_IDBCreateCommand;
extern DELPHI_PACKAGE GUID IID_IDBCreateSession;
extern DELPHI_PACKAGE GUID IID_ISourcesRowset;
extern DELPHI_PACKAGE GUID IID_IDBProperties;
extern DELPHI_PACKAGE GUID IID_IDBInitialize;
extern DELPHI_PACKAGE GUID IID_IDBInfo;
extern DELPHI_PACKAGE GUID IID_IDBDataSourceAdmin;
extern DELPHI_PACKAGE GUID IID_ISessionProperties;
extern DELPHI_PACKAGE GUID IID_IIndexDefinition;
extern DELPHI_PACKAGE GUID IID_ITableDefinition;
extern DELPHI_PACKAGE GUID IID_IOpenRowset;
extern DELPHI_PACKAGE GUID IID_IErrorLookup;
extern DELPHI_PACKAGE GUID IID_ISQLErrorInfo;
extern DELPHI_PACKAGE GUID IID_IGetDataSource;
extern DELPHI_PACKAGE GUID IID_ITransactionLocal;
extern DELPHI_PACKAGE GUID IID_ITransactionJoin;
extern DELPHI_PACKAGE GUID IID_ITransactionObject;
extern DELPHI_PACKAGE GUID IID_IDBAsynchStatus;
extern DELPHI_PACKAGE GUID IID_IRowsetFind;
extern DELPHI_PACKAGE GUID IID_IRowPosition;
extern DELPHI_PACKAGE GUID IID_IRowPositionChange;
extern DELPHI_PACKAGE GUID IID_IViewRowset;
extern DELPHI_PACKAGE GUID IID_IViewChapter;
extern DELPHI_PACKAGE GUID IID_IViewSort;
extern DELPHI_PACKAGE GUID IID_IViewFilter;
extern DELPHI_PACKAGE GUID IID_IRowsetView;
extern DELPHI_PACKAGE GUID IID_IMDFind;
extern DELPHI_PACKAGE GUID IID_IMDRangeRowset;
extern DELPHI_PACKAGE GUID IID_IAlterTable;
extern DELPHI_PACKAGE GUID IID_IAlterIndex;
extern DELPHI_PACKAGE GUID IID_ICommandPersist;
extern DELPHI_PACKAGE GUID IID_IRowsetChapterMember;
extern DELPHI_PACKAGE GUID IID_IRowsetRefresh;
extern DELPHI_PACKAGE GUID IID_IParentRowset;
extern DELPHI_PACKAGE GUID IID_ITrusteeGroupAdmin;
extern DELPHI_PACKAGE GUID IID_IObjectAccessControl;
extern DELPHI_PACKAGE GUID IID_ISecurityInfo;
extern DELPHI_PACKAGE GUID IID_IDBPromptInitialize;
extern DELPHI_PACKAGE GUID IID_IDataInitialize;
extern DELPHI_PACKAGE GUID DBSCHEMA_TABLES_INFO;
extern DELPHI_PACKAGE GUID MDGUID_MDX;
extern DELPHI_PACKAGE GUID DBGUID_MDX;
extern DELPHI_PACKAGE GUID MDSCHEMA_CUBES;
extern DELPHI_PACKAGE GUID MDSCHEMA_DIMENSIONS;
extern DELPHI_PACKAGE GUID MDSCHEMA_HIERARCHIES;
extern DELPHI_PACKAGE GUID MDSCHEMA_LEVELS;
extern DELPHI_PACKAGE GUID MDSCHEMA_MEASURES;
extern DELPHI_PACKAGE GUID MDSCHEMA_PROPERTIES;
extern DELPHI_PACKAGE GUID MDSCHEMA_MEMBERS;
extern DELPHI_PACKAGE GUID DBPROPSET_TRUSTEE;
extern DELPHI_PACKAGE GUID DBOBJECT_TABLE;
extern DELPHI_PACKAGE GUID DBOBJECT_COLUMN;
extern DELPHI_PACKAGE GUID DBOBJECT_DATABASE;
extern DELPHI_PACKAGE GUID DBOBJECT_PROCEDURE;
extern DELPHI_PACKAGE GUID DBOBJECT_VIEW;
extern DELPHI_PACKAGE GUID DBOBJECT_SCHEMA;
extern DELPHI_PACKAGE GUID DBOBJECT_DOMAIN;
extern DELPHI_PACKAGE GUID DBOBJECT_COLLATION;
extern DELPHI_PACKAGE GUID DBOBJECT_TRUSTEE;
extern DELPHI_PACKAGE GUID DBOBJECT_SCHEMAROWSET;
extern DELPHI_PACKAGE GUID DBOBJECT_CHARACTERSET;
extern DELPHI_PACKAGE GUID DBOBJECT_TRANSLATION;
extern DELPHI_PACKAGE GUID DB_PROPERTY_CHECK_OPTION;
extern DELPHI_PACKAGE GUID DB_PROPERTY_CONSTRAINT_CHECK_DEFERRED;
extern DELPHI_PACKAGE GUID DB_PROPERTY_DROP_CASCADE;
extern DELPHI_PACKAGE GUID DB_PROPERTY_UNIQUE;
extern DELPHI_PACKAGE GUID DB_PROPERTY_ON_COMMIT_PRESERVE_ROWS;
extern DELPHI_PACKAGE GUID DB_PROPERTY_PRIMARY;
extern DELPHI_PACKAGE GUID DB_PROPERTY_CLUSTERED;
extern DELPHI_PACKAGE GUID DB_PROPERTY_NONCLUSTERED;
extern DELPHI_PACKAGE GUID DB_PROPERTY_BTREE;
extern DELPHI_PACKAGE GUID DB_PROPERTY_HASH;
extern DELPHI_PACKAGE GUID DB_PROPERTY_FILLFACTOR;
extern DELPHI_PACKAGE GUID DB_PROPERTY_INITIALSIZE;
extern DELPHI_PACKAGE GUID DB_PROPERTY_DISALLOWNULL;
extern DELPHI_PACKAGE GUID DB_PROPERTY_IGNORENULL;
extern DELPHI_PACKAGE GUID DB_PROPERTY_IGNOREANYNULL;
extern DELPHI_PACKAGE GUID DB_PROPERTY_SORTBOOKMARKS;
extern DELPHI_PACKAGE GUID DB_PROPERTY_AUTOMATICUPDATE;
extern DELPHI_PACKAGE GUID DB_PROPERTY_EXPLICITUPDATE;
extern DELPHI_PACKAGE GUID DBGUID_LIKE_SQL;
extern DELPHI_PACKAGE GUID DBGUID_LIKE_DOS;
extern DELPHI_PACKAGE GUID DBGUID_LIKE_OFS;
extern DELPHI_PACKAGE GUID DBGUID_LIKE_MAPI;
extern DELPHI_PACKAGE GUID DBSCHEMA_ASSERTIONS;
extern DELPHI_PACKAGE GUID DBSCHEMA_CATALOGS;
extern DELPHI_PACKAGE GUID DBSCHEMA_CHARACTER_SETS;
extern DELPHI_PACKAGE GUID DBSCHEMA_COLLATIONS;
extern DELPHI_PACKAGE GUID DBSCHEMA_COLUMNS;
extern DELPHI_PACKAGE GUID DBSCHEMA_CHECK_CONSTRAINTS;
extern DELPHI_PACKAGE GUID DBSCHEMA_CONSTRAINT_COLUMN_USAGE;
extern DELPHI_PACKAGE GUID DBSCHEMA_CONSTRAINT_TABLE_USAGE;
extern DELPHI_PACKAGE GUID DBSCHEMA_KEY_COLUMN_USAGE;
extern DELPHI_PACKAGE GUID DBSCHEMA_REFERENTIAL_CONSTRAINTS;
extern DELPHI_PACKAGE GUID DBSCHEMA_TABLE_CONSTRAINTS;
extern DELPHI_PACKAGE GUID DBSCHEMA_COLUMN_DOMAIN_USAGE;
extern DELPHI_PACKAGE GUID DBSCHEMA_INDEXES;
extern DELPHI_PACKAGE GUID DBSCHEMA_COLUMN_PRIVILEGES;
extern DELPHI_PACKAGE GUID DBSCHEMA_TABLE_PRIVILEGES;
extern DELPHI_PACKAGE GUID DBSCHEMA_USAGE_PRIVILEGES;
extern DELPHI_PACKAGE GUID DBSCHEMA_PROCEDURES;
extern DELPHI_PACKAGE GUID DBSCHEMA_SCHEMATA;
extern DELPHI_PACKAGE GUID DBSCHEMA_SQL_LANGUAGES;
extern DELPHI_PACKAGE GUID DBSCHEMA_STATISTICS;
extern DELPHI_PACKAGE GUID DBSCHEMA_TABLES;
extern DELPHI_PACKAGE GUID DBSCHEMA_TRANSLATIONS;
extern DELPHI_PACKAGE GUID DBSCHEMA_PROVIDER_TYPES;
extern DELPHI_PACKAGE GUID DBSCHEMA_VIEWS;
extern DELPHI_PACKAGE GUID DBSCHEMA_VIEW_COLUMN_USAGE;
extern DELPHI_PACKAGE GUID DBSCHEMA_VIEW_TABLE_USAGE;
extern DELPHI_PACKAGE GUID DBSCHEMA_PROCEDURE_PARAMETERS;
extern DELPHI_PACKAGE GUID DBSCHEMA_FOREIGN_KEYS;
extern DELPHI_PACKAGE GUID DBSCHEMA_PRIMARY_KEYS;
extern DELPHI_PACKAGE GUID DBSCHEMA_PROCEDURE_COLUMNS;
extern DELPHI_PACKAGE GUID DBCOL_SELFCOLUMNS;
extern DELPHI_PACKAGE GUID DBCOL_SPECIALCOL;
extern DELPHI_PACKAGE GUID PSGUID_QUERY;
extern DELPHI_PACKAGE GUID DBPROPSET_COLUMN;
extern DELPHI_PACKAGE GUID DBPROPSET_DATASOURCE;
extern DELPHI_PACKAGE GUID DBPROPSET_DATASOURCEINFO;
extern DELPHI_PACKAGE GUID DBPROPSET_INDEX;
extern DELPHI_PACKAGE GUID DBPROPSET_DBINIT;
extern DELPHI_PACKAGE GUID DBPROPSET_ROWSET;
extern DELPHI_PACKAGE GUID DBPROPSET_SESSION;
extern DELPHI_PACKAGE GUID DBPROPSET_TABLE;
extern DELPHI_PACKAGE GUID DBPROPSET_PROPERTIESINERROR;
extern DELPHI_PACKAGE GUID DBPROPSET_VIEW;
#define DBPROPSET_COLUMNALL L"{C8B522F0-5CF3-11CE-ADE5-00AA0044773D}"
#define DBPROPSET_CONSTRAINTALL L"{C8B522FA-5CF3-11CE-ADE5-00AA0044773D}"
extern DELPHI_PACKAGE GUID DBPROPSET_DATASOURCEALL;
extern DELPHI_PACKAGE GUID DBPROPSET_DATASOURCEINFOALL;
extern DELPHI_PACKAGE GUID DBPROPSET_DBINITALL;
#define DBPROPSET_INDEXALL L"{C8B522F1-5CF3-11CE-ADE5-00AA0044773D}"
extern DELPHI_PACKAGE GUID DBPROPSET_ROWSETALL;
extern DELPHI_PACKAGE GUID DBPROPSET_SESSIONALL;
#define DBPROPSET_TABLEALL L"{C8B522F2-5CF3-11CE-ADE5-00AA0044773D}"
#define DBPROPSET_TRUSTEEALL L"{C8B522F3-5CF3-11CE-ADE5-00AA0044773D}"
extern DELPHI_PACKAGE GUID DBGUID_DEFAULT;
extern DELPHI_PACKAGE GUID DBGUID_SQL;
static const System::Word MAXCOLS = System::Word(0x1000);
static const System::Word MAXBOUND = System::Word(0xffff);
static const System::Int8 ISOFLAG_RETAIN_DONTCARE = System::Int8(0x5);
}	/* namespace Oledb */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_OLEDB)
using namespace Winapi::Oledb;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_OledbHPP
