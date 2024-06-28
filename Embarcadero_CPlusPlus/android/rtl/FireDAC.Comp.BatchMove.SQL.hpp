// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Comp.BatchMove.SQL.pas' rev: 34.00 (Android)

#ifndef Firedac_Comp_Batchmove_SqlHPP
#define Firedac_Comp_Batchmove_SqlHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.BatchMove.hpp>
#include <FireDAC.Comp.BatchMove.DataSet.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Comp
{
namespace Batchmove
{
namespace Sql
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDBatchMoveSQLDriver;
class DELPHICLASS TFDBatchMoveSQLReader;
class DELPHICLASS TFDBatchMoveSQLWriter;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDBatchMoveSQLDriver : public Firedac::Comp::Batchmove::Dataset::TFDBatchMoveDataSetDriver
{
	typedef Firedac::Comp::Batchmove::Dataset::TFDBatchMoveDataSetDriver inherited;
	
private:
	Firedac::Comp::Client::TFDCustomConnection* FConnection;
	System::UnicodeString FConnectionName;
	Firedac::Comp::Client::TFDCustomTransaction* FTransaction;
	System::UnicodeString FTableName;
	System::UnicodeString FReadSQL;
	Firedac::Comp::Client::TFDQuery* FReadQuery;
	Firedac::Comp::Client::TFDCustomConnection* FActualConnection;
	void __fastcall SetConnection(Firedac::Comp::Client::TFDCustomConnection* const AValue);
	void __fastcall SetConnectionName(const System::UnicodeString AValue);
	void __fastcall SetTransaction(Firedac::Comp::Client::TFDCustomTransaction* const AValue);
	void __fastcall SetReadSQL(const System::UnicodeString AValue);
	void __fastcall SetTableName(const System::UnicodeString AValue);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall CheckDefined(bool ARaise);
	virtual void __fastcall Open(bool AStartTx);
	virtual void __fastcall Close(bool AStopTxError);
	virtual System::UnicodeString __fastcall GetActualTableName();
	
public:
	__fastcall virtual TFDBatchMoveSQLDriver(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDBatchMoveSQLDriver();
	__property System::UnicodeString ActualTableName = {read=GetActualTableName};
	
__published:
	__property Firedac::Comp::Client::TFDCustomConnection* Connection = {read=FConnection, write=SetConnection};
	__property System::UnicodeString ConnectionName = {read=FConnectionName, write=SetConnectionName};
	__property Firedac::Comp::Client::TFDCustomTransaction* Transaction = {read=FTransaction, write=SetTransaction};
	__property System::UnicodeString TableName = {read=FTableName, write=SetTableName};
	__property System::UnicodeString ReadSQL = {read=FReadSQL, write=SetReadSQL};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDBatchMoveSQLReader : public TFDBatchMoveSQLDriver
{
	typedef TFDBatchMoveSQLDriver inherited;
	
protected:
	System::UnicodeString __fastcall GetSourceTableName();
	virtual void __fastcall Open(bool AStartTx);
	virtual void __fastcall Refresh();
	void __fastcall ReadHeader();
	System::Variant __fastcall GetFieldValue(System::TObject* AField);
	bool __fastcall Eof();
	void __fastcall ReadRecord();
	void __fastcall NextRecord();
	void __fastcall GuessFormat(Firedac::Comp::Batchmove::TFDBatchMoveAnalyze AAnalyze = (Firedac::Comp::Batchmove::TFDBatchMoveAnalyze() << Firedac::Comp::Batchmove::Firedac_Comp_Batchmove__1::taDelimSep << Firedac::Comp::Batchmove::Firedac_Comp_Batchmove__1::taHeader << Firedac::Comp::Batchmove::Firedac_Comp_Batchmove__1::taFields ));
public:
	/* TFDBatchMoveSQLDriver.Create */ inline __fastcall virtual TFDBatchMoveSQLReader(System::Classes::TComponent* AOwner) : TFDBatchMoveSQLDriver(AOwner) { }
	/* TFDBatchMoveSQLDriver.Destroy */ inline __fastcall virtual ~TFDBatchMoveSQLReader() { }
	
private:
	void *__IFDBatchMoveReader;	// Firedac::Comp::Batchmove::IFDBatchMoveReader 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2051}
	operator Firedac::Comp::Batchmove::_di_IFDBatchMoveReader()
	{
		Firedac::Comp::Batchmove::_di_IFDBatchMoveReader intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Comp::Batchmove::IFDBatchMoveReader*(void) { return (Firedac::Comp::Batchmove::IFDBatchMoveReader*)&__IFDBatchMoveReader; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDBatchMoveSQLWriter : public TFDBatchMoveSQLDriver
{
	typedef TFDBatchMoveSQLDriver inherited;
	
private:
	System::UnicodeString FWriteSQL;
	System::UnicodeString FGeneratorName;
	int FRecIndex;
	Firedac::Comp::Client::TFDQuery* FWriteQuery;
	Firedac::Phys::Intf::TFDPhysCreateTableParts FCreateTableParts;
	int __fastcall MoveRecord();
	
protected:
	virtual bool __fastcall GetIsBatch();
	virtual void __fastcall Open(bool AStartTx);
	virtual void __fastcall Close(bool AStopTxError);
	void __fastcall CreateTable();
	void __fastcall StartTransaction();
	void __fastcall CommitTransaction();
	void __fastcall RollbackTransaction();
	void __fastcall Erase(bool ANoUndo);
	void __fastcall WriteHeader();
	void __fastcall SetFieldValue(System::TObject* AField, const System::Variant &AValue);
	bool __fastcall FindRecord();
	int __fastcall InsertRecord();
	int __fastcall UpdateRecord();
	int __fastcall DeleteRecord();
	int __fastcall FlushRecords();
	HIDESBASE int __fastcall GetFieldCount();
	HIDESBASE System::UnicodeString __fastcall GetFieldName(int AIndex);
	HIDESBASE int __fastcall GetFieldIndex(const System::UnicodeString AName, bool ACheck);
#ifndef __aarch64__
	HIDESBASE System::TObject* __fastcall GetFieldInfo(int AIndex, Firedac::Stan::Intf::TFDDataType &AType, unsigned &ASize, int &APrec, int &AScale, bool &AInKey, bool &AIsIdentity);
#else /* __aarch64__ */
	HIDESBASE System::TObject* __fastcall GetFieldInfo(int AIndex, Firedac::Stan::Intf::TFDDataType &AType, unsigned long &ASize, int &APrec, int &AScale, bool &AInKey, bool &AIsIdentity);
#endif /* __aarch64__ */
	virtual System::UnicodeString __fastcall GetActualTableName();
	
public:
	__fastcall virtual TFDBatchMoveSQLWriter(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDBatchMoveSQLWriter();
	
__published:
	__property System::UnicodeString WriteSQL = {read=FWriteSQL, write=FWriteSQL};
	__property System::UnicodeString GeneratorName = {read=FGeneratorName, write=FGeneratorName};
	__property Firedac::Phys::Intf::TFDPhysCreateTableParts CreateTableParts = {read=FCreateTableParts, write=FCreateTableParts, default=31};
private:
	void *__IFDBatchMoveWriter;	// Firedac::Comp::Batchmove::IFDBatchMoveWriter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2052}
	operator Firedac::Comp::Batchmove::_di_IFDBatchMoveWriter()
	{
		Firedac::Comp::Batchmove::_di_IFDBatchMoveWriter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Comp::Batchmove::IFDBatchMoveWriter*(void) { return (Firedac::Comp::Batchmove::IFDBatchMoveWriter*)&__IFDBatchMoveWriter; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sql */
}	/* namespace Batchmove */
}	/* namespace Comp */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_COMP_BATCHMOVE_SQL)
using namespace Firedac::Comp::Batchmove::Sql;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_COMP_BATCHMOVE)
using namespace Firedac::Comp::Batchmove;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_COMP)
using namespace Firedac::Comp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Comp_Batchmove_SqlHPP
