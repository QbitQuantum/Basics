// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Comp.BatchMove.DataSet.pas' rev: 34.00 (Windows)

#ifndef Firedac_Comp_Batchmove_DatasetHPP
#define Firedac_Comp_Batchmove_DatasetHPP

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
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.BatchMove.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Comp
{
namespace Batchmove
{
namespace Dataset
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDBatchMoveDataSetDriver;
class DELPHICLASS TFDBatchMoveDataSetReader;
class DELPHICLASS TFDBatchMoveDataSetWriter;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDBatchMoveDataSetDriver : public Firedac::Comp::Batchmove::TFDBatchMoveDriver
{
	typedef Firedac::Comp::Batchmove::TFDBatchMoveDriver inherited;
	
private:
	bool FActive;
	Data::Db::TDataSet* FDataSet;
	bool FOptimise;
	Firedac::Stan::Option::_di_IFDStanOptions FPrevOptions;
	void __fastcall SetDataSet(Data::Db::TDataSet* const AValue);
	Data::Db::_di_IProviderSupportNG __fastcall GetProvider();
	Firedac::Comp::Client::TFDAdaptedDataSet* __fastcall GetFDDataSet();
	bool __fastcall IsMemTable();
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall CheckDefined(bool ARaise);
	virtual void __fastcall Open(bool AStartTx);
	virtual void __fastcall Close(bool AStopTxError);
	virtual void __fastcall Refresh();
	void __fastcall AbortJob();
	bool __fastcall AddAutoFields();
	void __fastcall DeleteAutoFields();
	System::UnicodeString __fastcall GetCatalog();
	bool __fastcall GetIsUnicode();
	virtual bool __fastcall GetIsOpen();
	int __fastcall GetFieldCount();
	System::UnicodeString __fastcall GetFieldName(int AIndex);
	int __fastcall GetFieldIndex(const System::UnicodeString AName, bool ACheck);
	System::TObject* __fastcall GetFieldInfo(int AIndex, Firedac::Stan::Intf::TFDDataType &AType, unsigned &ASize, int &APrec, int &AScale, bool &AInKey, bool &AIsIdentity);
	void __fastcall GetTableDefs(Data::Db::TFieldDefs* AFieldDefs, Data::Db::TIndexDefs* AIndexDefs);
	__property Data::Db::TDataSet* DataSet = {read=FDataSet, write=SetDataSet};
	__property bool Optimise = {read=FOptimise, write=FOptimise, default=1};
	
public:
	__fastcall virtual TFDBatchMoveDataSetDriver(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDBatchMoveDataSetDriver();
	__property Data::Db::_di_IProviderSupportNG Provider = {read=GetProvider};
	__property Firedac::Comp::Client::TFDAdaptedDataSet* FDDataSet = {read=GetFDDataSet};
private:
	void *__IFDBatchMoveDriver;	// Firedac::Comp::Batchmove::IFDBatchMoveDriver 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2050}
	operator Firedac::Comp::Batchmove::_di_IFDBatchMoveDriver()
	{
		Firedac::Comp::Batchmove::_di_IFDBatchMoveDriver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Comp::Batchmove::IFDBatchMoveDriver*(void) { return (Firedac::Comp::Batchmove::IFDBatchMoveDriver*)&__IFDBatchMoveDriver; }
	#endif
	
};


class PASCALIMPLEMENTATION TFDBatchMoveDataSetReader : public TFDBatchMoveDataSetDriver
{
	typedef TFDBatchMoveDataSetDriver inherited;
	
private:
	bool FRewind;
	
protected:
	System::UnicodeString __fastcall GetSourceTableName();
	virtual void __fastcall Open(bool AStartTx);
	virtual void __fastcall Close(bool AStopTxError);
	void __fastcall ReadHeader();
	bool __fastcall Eof();
	void __fastcall ReadRecord();
	System::Variant __fastcall GetFieldValue(System::TObject* AField);
	void __fastcall NextRecord();
	void __fastcall GuessFormat(Firedac::Comp::Batchmove::TFDBatchMoveAnalyze AAnalyze = (Firedac::Comp::Batchmove::TFDBatchMoveAnalyze() << Firedac::Comp::Batchmove::Firedac_Comp_Batchmove__1::taDelimSep << Firedac::Comp::Batchmove::Firedac_Comp_Batchmove__1::taHeader << Firedac::Comp::Batchmove::Firedac_Comp_Batchmove__1::taFields ));
	
public:
	__fastcall virtual TFDBatchMoveDataSetReader(System::Classes::TComponent* AOwner);
	
__published:
	__property bool Rewind = {read=FRewind, write=FRewind, default=1};
	__property DataSet;
	__property Optimise = {default=1};
public:
	/* TFDBatchMoveDataSetDriver.Destroy */ inline __fastcall virtual ~TFDBatchMoveDataSetReader() { }
	
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


class PASCALIMPLEMENTATION TFDBatchMoveDataSetWriter : public TFDBatchMoveDataSetDriver
{
	typedef TFDBatchMoveDataSetDriver inherited;
	
private:
	Firedac::Comp::Client::TFDCustomConnection* FConnection;
	bool FDisconnected;
	bool FDirect;
	
protected:
	virtual void __fastcall Open(bool AStartTx);
	virtual void __fastcall Close(bool AStopTxError);
	virtual void __fastcall Refresh();
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
	
__published:
	__property bool Direct = {read=FDirect, write=FDirect, default=0};
	__property DataSet;
	__property Optimise = {default=1};
public:
	/* TFDBatchMoveDataSetDriver.Create */ inline __fastcall virtual TFDBatchMoveDataSetWriter(System::Classes::TComponent* AOwner) : TFDBatchMoveDataSetDriver(AOwner) { }
	/* TFDBatchMoveDataSetDriver.Destroy */ inline __fastcall virtual ~TFDBatchMoveDataSetWriter() { }
	
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


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dataset */
}	/* namespace Batchmove */
}	/* namespace Comp */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_COMP_BATCHMOVE_DATASET)
using namespace Firedac::Comp::Batchmove::Dataset;
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
#endif	// Firedac_Comp_Batchmove_DatasetHPP
