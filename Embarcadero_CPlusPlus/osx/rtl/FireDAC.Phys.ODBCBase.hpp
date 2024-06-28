// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ODBCBase.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_OdbcbaseHPP
#define Firedac_Phys_OdbcbaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.ODBCCli.hpp>
#include <FireDAC.Phys.ODBCWrapper.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Odbcbase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysODBCBaseDriverLink;
class DELPHICLASS TFDPhysODBCBaseService;
__interface DELPHIINTERFACE IFDPhysODBCDriver;
typedef System::DelphiInterface<IFDPhysODBCDriver> _di_IFDPhysODBCDriver;
class DELPHICLASS TFDPhysODBCDriverBase;
class DELPHICLASS TFDPhysODBCConnectionBase;
class DELPHICLASS TFDPhysODBCTransaction;
struct TFDODBCVarInfoRec;
class DELPHICLASS TFDPhysODBCCommand;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysODBCBaseDriverLink : public Firedac::Phys::TFDPhysDriverLink
{
	typedef Firedac::Phys::TFDPhysDriverLink inherited;
	
private:
	System::UnicodeString FODBCAdvanced;
	System::UnicodeString FODBCDriver;
	
protected:
	virtual bool __fastcall IsConfigured();
	virtual void __fastcall ApplyTo(const Firedac::Stan::Intf::_di_IFDStanDefinition AParams);
	
public:
	void __fastcall GetDrivers(System::Classes::TStrings* AList);
	void __fastcall GetDSNs(System::Classes::TStrings* AList, bool AWithDescription = false);
	
__published:
	__property System::UnicodeString ODBCDriver = {read=FODBCDriver, write=FODBCDriver};
	__property System::UnicodeString ODBCAdvanced = {read=FODBCAdvanced, write=FODBCAdvanced};
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysODBCBaseDriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::TFDPhysDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysODBCBaseDriverLink() { }
	
};


class PASCALIMPLEMENTATION TFDPhysODBCBaseService : public Firedac::Phys::TFDPhysDriverService
{
	typedef Firedac::Phys::TFDPhysDriverService inherited;
	
private:
	Firedac::Phys::Odbcwrapper::TODBCLib* __fastcall GetLib();
	
protected:
	virtual Firedac::Phys::Odbcwrapper::TODBCEnvironment* __fastcall GetEnv();
	
public:
	void __fastcall ExecuteBase(System::Word ARequest, System::UnicodeString ADriver, System::UnicodeString AAttributes);
	__property Firedac::Phys::Odbcwrapper::TODBCEnvironment* Env = {read=GetEnv};
	__property Firedac::Phys::Odbcwrapper::TODBCLib* Lib = {read=GetLib};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDPhysODBCBaseService() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDPhysODBCBaseService(System::Classes::TComponent* AOwner) : Firedac::Phys::TFDPhysDriverService(AOwner) { }
	
};


typedef System::StaticArray<void *, 2> TFDPhysODBCCliHandles;

typedef TFDPhysODBCCliHandles *PFDPhysODBCCliHandles;

__interface  INTERFACE_UUID("{A52C2247-E07C-4BEB-821B-6DF097828ED0}") IFDPhysODBCDriver  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetODBCDriver() = 0 ;
	virtual System::UnicodeString __fastcall GetODBCAdvanced() = 0 ;
	__property System::UnicodeString ODBCDriver = {read=GetODBCDriver};
	__property System::UnicodeString ODBCAdvanced = {read=GetODBCAdvanced};
};

#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDPhysODBCDriverBase : public Firedac::Phys::TFDPhysDriver
{
	typedef Firedac::Phys::TFDPhysDriver inherited;
	
private:
	Firedac::Phys::Odbcwrapper::TODBCLib* FODBCLib;
	Firedac::Phys::Odbcwrapper::TODBCEnvironment* FODBCEnvironment;
	System::UnicodeString FODBCDriver;
	System::UnicodeString FODBCAdvanced;
	Firedac::Stan::Intf::TFDStringList* FKeywords;
	
protected:
	virtual void __fastcall InternalLoad();
	virtual void __fastcall InternalUnload();
	virtual void * __fastcall GetCliObj();
	virtual Firedac::Dats::TFDDatSTable* __fastcall GetConnParams(System::Classes::TStrings* AKeys, Firedac::Dats::TFDDatSTable* AParams);
	bool __fastcall RunConnectionWizard(const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef, NativeUInt AParentWnd);
	System::UnicodeString __fastcall GetODBCDriver();
	System::UnicodeString __fastcall GetODBCAdvanced();
	virtual void __fastcall GetODBCConnectStringKeywords(System::Classes::TStrings* AKeywords);
	
public:
	__fastcall virtual TFDPhysODBCDriverBase(Firedac::Phys::TFDPhysManager* AManager, const Firedac::Stan::Intf::_di_IFDStanDefinition ADriverDef);
	__fastcall virtual ~TFDPhysODBCDriverBase();
	virtual System::UnicodeString __fastcall BuildODBCConnectString(const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef);
	System::UnicodeString __fastcall FindBestDriver(const System::UnicodeString *ADrivers, const int ADrivers_High, const System::UnicodeString ADefaultDriver = System::UnicodeString());
	__property System::UnicodeString ODBCDriver = {read=FODBCDriver, write=FODBCDriver};
	__property System::UnicodeString ODBCAdvanced = {read=FODBCAdvanced, write=FODBCAdvanced};
	__property Firedac::Phys::Odbcwrapper::TODBCLib* ODBCLib = {read=FODBCLib};
	__property Firedac::Phys::Odbcwrapper::TODBCEnvironment* ODBCEnvironment = {read=FODBCEnvironment};
private:
	void *__IFDPhysODBCDriver;	// IFDPhysODBCDriver 
	void *__IFDPhysDriverConnectionWizard;	// Firedac::Phys::Intf::IFDPhysDriverConnectionWizard 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A52C2247-E07C-4BEB-821B-6DF097828ED0}
	operator _di_IFDPhysODBCDriver()
	{
		_di_IFDPhysODBCDriver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFDPhysODBCDriver*(void) { return (IFDPhysODBCDriver*)&__IFDPhysODBCDriver; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2111}
	operator Firedac::Phys::Intf::_di_IFDPhysDriverConnectionWizard()
	{
		Firedac::Phys::Intf::_di_IFDPhysDriverConnectionWizard intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysDriverConnectionWizard*(void) { return (Firedac::Phys::Intf::IFDPhysDriverConnectionWizard*)&__IFDPhysDriverConnectionWizard; }
	#endif
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

enum DECLSPEC_DENUM Firedac_Phys_Odbcbase__4 : unsigned int { soPKFunction, soFKFunction, soParamSet, soRowSet, soMoney, soArrayBatch };

typedef System::Set<Firedac_Phys_Odbcbase__4, Firedac_Phys_Odbcbase__4::soPKFunction, Firedac_Phys_Odbcbase__4::soArrayBatch> TFDPhysODBCSupportedOptions;

class PASCALIMPLEMENTATION TFDPhysODBCConnectionBase : public Firedac::Phys::TFDPhysConnection
{
	typedef Firedac::Phys::TFDPhysConnection inherited;
	
private:
	Firedac::Phys::Odbcwrapper::TODBCEnvironment* FODBCEnvironment;
	Firedac::Phys::Odbcwrapper::TODBCConnection* FODBCConnection;
	TFDPhysODBCCliHandles FCliHandles;
	TFDPhysODBCSupportedOptions FSupportedOptions;
	System::StaticArray<int, 6> FTxnIsolations;
	void __fastcall MapTxIsolations();
	Firedac::Phys::Odbcwrapper::TODBCDriverKind __fastcall GetDriverKind();
	
protected:
	virtual void __fastcall InternalConnect();
	virtual void __fastcall InternalSetMeta();
	virtual Firedac::Phys::TFDPhysCommand* __fastcall InternalCreateCommand();
	virtual Firedac::Phys::TFDPhysTransaction* __fastcall InternalCreateTransaction();
	virtual void __fastcall InternalDisconnect();
	virtual void __fastcall InternalTracingChanged();
	virtual void __fastcall InternalExecuteDirect(const System::UnicodeString ASQL, Firedac::Phys::TFDPhysTransaction* ATransaction);
	virtual void __fastcall GetItem(int AIndex, /* out */ System::UnicodeString &AName, /* out */ System::Variant &AValue, /* out */ Firedac::Stan::Intf::TFDMoniAdapterItemKind &AKind);
	virtual int __fastcall GetItemCount();
	virtual Firedac::Stan::Error::EFDDBEngineException* __fastcall GetMessages();
	virtual void * __fastcall GetCliObj();
	virtual void * __fastcall InternalGetCliHandle();
	virtual System::UnicodeString __fastcall InternalGetCurrentCatalog();
	virtual System::UnicodeString __fastcall InternalGetCurrentSchema();
	virtual void __fastcall GetStrsMaxSizes(short AStrDataType, bool AFixedLen, /* out */ int &ACharSize, /* out */ int &AByteSize);
	virtual Firedac::Stan::Intf::TFDDataType __fastcall GetStrsType();
	virtual Firedac::Stan::Intf::TFDDataType __fastcall GetNumType();
	virtual void __fastcall UpdateDecimalSep();
	virtual Firedac::Phys::Odbcwrapper::EODBCNativeExceptionClass __fastcall GetExceptionClass();
	virtual void __fastcall SetupConnection();
	virtual int __fastcall GetODBCVersion();
	System::UnicodeString __fastcall GetKeywords();
	void __fastcall GetVersions(/* out */ unsigned __int64 &AServer, /* out */ unsigned __int64 &AClient);
	
public:
	__fastcall virtual TFDPhysODBCConnectionBase(Firedac::Phys::TFDPhysDriver* ADriverObj, Firedac::Phys::TFDPhysConnectionHost* AConnHost);
	__fastcall virtual ~TFDPhysODBCConnectionBase();
	__property Firedac::Phys::Odbcwrapper::TODBCEnvironment* ODBCEnvironment = {read=FODBCEnvironment};
	__property Firedac::Phys::Odbcwrapper::TODBCConnection* ODBCConnection = {read=FODBCConnection};
	__property Firedac::Phys::Odbcwrapper::TODBCDriverKind DriverKind = {read=GetDriverKind, nodefault};
};


#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDPhysODBCTransaction : public Firedac::Phys::TFDPhysTransaction
{
	typedef Firedac::Phys::TFDPhysTransaction inherited;
	
private:
	Firedac::Phys::Odbcwrapper::TODBCConnection* __fastcall GetODBCConnection();
	void __fastcall DisconnectCommandsBeforeCommit();
	void __fastcall DisconnectCommandsBeforeRollback();
	
protected:
#ifndef __x86_64__
	virtual void __fastcall InternalStartTransaction(unsigned ATxID);
#else /* __x86_64__ */
	virtual void __fastcall InternalStartTransaction(unsigned long ATxID);
#endif /* __x86_64__ */
	virtual void __fastcall InternalChanged();
#ifndef __x86_64__
	virtual void __fastcall InternalCommit(unsigned ATxID);
	virtual void __fastcall InternalRollback(unsigned ATxID);
#else /* __x86_64__ */
	virtual void __fastcall InternalCommit(unsigned long ATxID);
	virtual void __fastcall InternalRollback(unsigned long ATxID);
#endif /* __x86_64__ */
	virtual void __fastcall InternalReleaseHandle();
	virtual void __fastcall InternalNotify(Firedac::Phys::TFDPhysTxNotification ANotification, Firedac::Phys::TFDPhysCommand* ACommandObj);
	
public:
	__property Firedac::Phys::Odbcwrapper::TODBCConnection* ODBCConnection = {read=GetODBCConnection};
public:
	/* TFDPhysTransaction.Create */ inline __fastcall virtual TFDPhysODBCTransaction(Firedac::Phys::TFDPhysConnection* AConnection) : Firedac::Phys::TFDPhysTransaction(AConnection) { }
	/* TFDPhysTransaction.Destroy */ inline __fastcall virtual ~TFDPhysODBCTransaction() { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

typedef TFDODBCVarInfoRec *PFDODBCColInfoRec;

typedef TFDODBCVarInfoRec *PFDODBCParInfoRec;

struct DECLSPEC_DRECORD TFDODBCVarInfoRec
{
	
private:
	typedef System::DynamicArray<TFDODBCVarInfoRec> _TFDODBCVarInfoRec__1;
	
	
public:
	System::UnicodeString FName;
	System::UnicodeString FExtName;
	System::UnicodeString FOriginCatalogName;
	System::UnicodeString FOriginSchemaName;
	System::UnicodeString FOriginTabName;
	System::UnicodeString FOriginColName;
	short FPos;
	short FParamIndex;
	int FColSize;
	int FScale;
	short FSrcSQLDataType;
	short FOutSQLDataType;
	Firedac::Stan::Intf::TFDDataType FSrcDataType;
	Firedac::Stan::Intf::TFDDataType FOutDataType;
	Firedac::Stan::Intf::TFDDataType FDestDataType;
	Firedac::Phys::Odbcwrapper::TODBCVariable* FVar;
	_TFDODBCVarInfoRec__1 FSubInfos;
	Firedac::Stan::Intf::TFDDataAttributes FAttrs;
	
public:
	union
	{
		struct 
		{
			bool FIsNull;
			Data::Db::TParamType FParamType;
			Data::Db::TFieldType FDataType;
		};
		struct 
		{
			bool FInKey;
#ifndef __x86_64__
			unsigned FFDLen;
#else /* __x86_64__ */
			unsigned long FFDLen;
#endif /* __x86_64__ */
			int FFDScale;
		};
		
	};
};


enum DECLSPEC_DENUM TFDPhysODBCStatementProp : unsigned int { cpParamSet, cpRowSet, cpLateBindedData, cpOutResParams, cpOutParams, cpDefaultCrs, cpOnNextResult, cpOnNextResultValue, cpNotFirstCursor, cpResetOnArrayOffset, cpUnifyParams };

typedef System::Set<TFDPhysODBCStatementProp, TFDPhysODBCStatementProp::cpParamSet, TFDPhysODBCStatementProp::cpUnifyParams> TFDPhysODBCStatementProps;

#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDPhysODBCCommand : public Firedac::Phys::TFDPhysCommand
{
	typedef Firedac::Phys::TFDPhysCommand inherited;
	
	
private:
	typedef System::DynamicArray<TFDODBCVarInfoRec> _TFDPhysODBCCommand__1;
	
	typedef System::DynamicArray<TFDODBCVarInfoRec> _TFDPhysODBCCommand__2;
	
	
private:
	int FColumnIndex;
	Firedac::Phys::Odbcwrapper::TODBCStatementBase* FStatement;
	Firedac::Phys::Odbcwrapper::TODBCCommandStatement* FCommandStatement;
	Firedac::Phys::Odbcwrapper::TODBCMetaInfoStatement* FMetainfoStatement;
	Firedac::Dats::TFDDatSView* FMetainfoAddonView;
	TFDPhysODBCStatementProps FStatementProps;
	HIDESBASE TFDPhysODBCConnectionBase* __fastcall GetConnection();
	void __fastcall DestroyDescribeInfos();
	void __fastcall DestroyParamInfos();
	bool __fastcall FetchMetaRow(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow, int ARowIndex, int ARowNo);
	void __fastcall FetchRow(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow, int ARowIndex);
	void __fastcall GetParamValues(int ATimes, int AOffset, int AFromParIndex);
	bool __fastcall OpenMetaInfo();
	void __fastcall SetParamValues(int ATimes, int AOffset, int AFromParIndex);
	void __fastcall SetupStatementBeforePrepare(Firedac::Phys::Odbcwrapper::TODBCStatementBase* AStmt);
	void __fastcall SetupStatementAfterDescribe(Firedac::Phys::Odbcwrapper::TODBCStatementBase* AStmt);
	void __fastcall SetupStatementBeforeExecute(Firedac::Phys::Odbcwrapper::TODBCStatementBase* AStmt);
	int __fastcall GetRowsetSize(int ARowsetSize);
	int __fastcall GetParamsetSize(int AParamsetSize);
	bool __fastcall MatchParamsetSize(int AParamsetSize1, int AParamsetSize2);
	bool __fastcall UseExecDirect();
	bool __fastcall UseInformationSchema();
	bool __fastcall UseStatement();
	void __fastcall CloseStatement(int AIndex, bool AForceClose, bool AGetOutParams, bool AIgnoreErrors);
#ifndef __x86_64__
	bool __fastcall GetCursor(int &ARows);
#else /* __x86_64__ */
	bool __fastcall GetCursor(__int64 &ARows);
#endif /* __x86_64__ */
	
protected:
	_TFDPhysODBCCommand__1 FColInfos;
	_TFDPhysODBCCommand__2 FParInfos;
	HIDESBASE bool __fastcall CheckFetchColumn(Firedac::Stan::Intf::TFDDataType ADataType, Firedac::Stan::Intf::TFDDataAttributes AAttributes, short ASQLDataType)/* overload */;
	short __fastcall FD2SQLDataType(Firedac::Stan::Intf::TFDDataType AFDType, bool AFixedLen, int &AColSize, int &AScale);
	short __fastcall FD2CDataType(Firedac::Stan::Intf::TFDDataType AFDType, bool ANestedColumn);
#ifndef __x86_64__
	void __fastcall SQL2FDColInfo(short ASQLDataType, bool AUnsigned, const System::UnicodeString ASQLTypeName, int &ASQLSize, int ASQLDecimals, Firedac::Stan::Intf::TFDDataType &AType, Firedac::Stan::Intf::TFDDataAttributes &AAttrs, unsigned &ALen, int &APrec, int &AScale);
#else /* __x86_64__ */
	void __fastcall SQL2FDColInfo(short ASQLDataType, bool AUnsigned, const System::UnicodeString ASQLTypeName, int &ASQLSize, int ASQLDecimals, Firedac::Stan::Intf::TFDDataType &AType, Firedac::Stan::Intf::TFDDataAttributes &AAttrs, unsigned long &ALen, int &APrec, int &AScale);
#endif /* __x86_64__ */
	short __fastcall FD2SQLParamType(Data::Db::TParamType AParamType);
	virtual void __fastcall InternalAbort();
	virtual void __fastcall InternalClose();
	virtual bool __fastcall InternalColInfoGet(Firedac::Phys::TFDPhysDataColumnInfo &AColInfo);
	virtual bool __fastcall InternalColInfoStart(Firedac::Phys::TFDPhysDataTableInfo &ATabInfo);
#ifndef __x86_64__
	virtual void __fastcall InternalExecute(int ATimes, int AOffset, int &ACount);
#else /* __x86_64__ */
	virtual void __fastcall InternalExecute(int ATimes, int AOffset, __int64 &ACount);
#endif /* __x86_64__ */
	virtual void __fastcall InternalCloseStreams();
#ifndef __x86_64__
	virtual unsigned __fastcall InternalFetchRowSet(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow, unsigned ARowsetSize);
#else /* __x86_64__ */
	virtual unsigned long __fastcall InternalFetchRowSet(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow, unsigned long ARowsetSize);
#endif /* __x86_64__ */
	virtual bool __fastcall InternalNextRecordSet();
#ifndef __x86_64__
	virtual bool __fastcall InternalOpen(int &ACount);
#else /* __x86_64__ */
	virtual bool __fastcall InternalOpen(__int64 &ACount);
#endif /* __x86_64__ */
	virtual void __fastcall InternalPrepare();
	virtual void __fastcall InternalUnprepare();
	virtual void * __fastcall GetCliObj();
	virtual void __fastcall CreateDescribeInfos();
	virtual void __fastcall CreateParamInfos();
	virtual void __fastcall CreateParamColumns(Firedac::Stan::Param::TFDParam* AParam);
	virtual void __fastcall CreateParamColumnInfos(PFDODBCParInfoRec ApInfo, Firedac::Stan::Param::TFDParam* AParam);
	virtual bool __fastcall GetIsCustomParam(Firedac::Stan::Intf::TFDDataType ADataType);
	virtual void __fastcall SetCustomParamValue(Firedac::Stan::Intf::TFDDataType ADataType, Firedac::Phys::Odbcwrapper::TODBCVariable* AVar, Firedac::Stan::Param::TFDParam* AParam, int AVarIndex, int AParIndex);
	virtual void __fastcall GetCustomParamValue(Firedac::Stan::Intf::TFDDataType ADataType, Firedac::Phys::Odbcwrapper::TODBCVariable* AVar, Firedac::Stan::Param::TFDParam* AParam, int AVarIndex, int AParIndex);
	
public:
	__property Firedac::Phys::Odbcwrapper::TODBCStatementBase* ODBCStatement = {read=FStatement};
	__property TFDPhysODBCConnectionBase* ODBCConnection = {read=GetConnection};
public:
	/* TFDPhysCommand.Create */ inline __fastcall TFDPhysODBCCommand(Firedac::Phys::TFDPhysConnection* AConnection) : Firedac::Phys::TFDPhysCommand(AConnection) { }
	/* TFDPhysCommand.Destroy */ inline __fastcall virtual ~TFDPhysODBCCommand() { }
	
	/* Hoisted overloads: */
	
protected:
	inline bool __fastcall  CheckFetchColumn(Firedac::Stan::Intf::TFDDataType ADataType, Firedac::Stan::Intf::TFDDataAttributes AAttributes){ return Firedac::Phys::TFDPhysCommand::CheckFetchColumn(ADataType, AAttributes); }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Odbcbase */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ODBCBASE)
using namespace Firedac::Phys::Odbcbase;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS)
using namespace Firedac::Phys;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Phys_OdbcbaseHPP
