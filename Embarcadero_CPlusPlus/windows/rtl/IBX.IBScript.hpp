// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBScript.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbscriptHPP
#define Ibx_IbscriptHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBCustomDataSet.hpp>
#include <IBX.IBSQL.hpp>
#include <IBX.IBDatabaseInfo.hpp>
#include <IBX.IBExternals.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibscript
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBSQLParser;
class DELPHICLASS TIBScriptStats;
class DELPHICLASS TIBScript;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIBParseKind : unsigned char { stmtDDL, stmtDML, stmtSET, stmtCONNECT, stmtDrop, stmtCREATE, stmtINPUT, stmtUNK, stmtEMPTY, stmtTERM, stmtERR, stmtCOMMIT, stmtROLLBACK, stmtReconnect, stmtRollbackSavePoint, stmtReleaseSavePoint, stmtStartSavepoint, stmtCOMMITRetaining, stmtROLLBACKRetaining, stmtBatchStart, stmtBatchExecute, stmtServerSET, stmtSetTransaction, stmtShow };

typedef void __fastcall (__closure *TIBSQLParseError)(System::TObject* Sender, System::UnicodeString Error, System::UnicodeString SQLText, int LineIndex);

typedef void __fastcall (__closure *TIBSQLExecuteError)(System::TObject* Sender, System::UnicodeString Error, System::UnicodeString SQLText, int LineIndex, bool &Ignore);

typedef void __fastcall (__closure *TIBSQLParseStmt)(System::TObject* Sender, TIBParseKind AKind, System::UnicodeString SQLText);

typedef void __fastcall (__closure *TIBScriptParamCheck)(TIBScript* Sender, bool &Pause);

typedef void __fastcall (__closure *TIBScriptOnShow)(TIBScript* Sender, System::UnicodeString SQLText);

typedef void __fastcall (__closure *TIBScriptBeforeSetSubscription)(TIBScript* Sender, System::UnicodeString SubscriptionName, bool Active);

class PASCALIMPLEMENTATION TIBSQLParser : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TIBSQLParseError FOnError;
	TIBSQLParseStmt FOnParse;
	System::Classes::TStrings* FScript;
	System::Classes::TStrings* FInput;
	System::UnicodeString FTerminator;
	bool FPaused;
	bool FFinished;
	void __fastcall SetScript(System::Classes::TStrings* const Value);
	void __fastcall SetPaused(const bool Value);
	System::Classes::TStrings* FTokens;
	System::UnicodeString FWork;
	int ScriptIndex;
	int LineIndex;
	int ImportIndex;
	bool InInput;
	System::UnicodeString __fastcall TokenizeNextLine();
	TIBParseKind __fastcall IsValidStatement();
	void __fastcall RemoveComment();
	bool __fastcall AppendNextLine();
	void __fastcall LoadInput();
	
protected:
	virtual void __fastcall DoOnParse(TIBParseKind AKind, System::UnicodeString SQLText);
	virtual void __fastcall DoOnError(System::UnicodeString Error, System::UnicodeString SQLText);
	void __fastcall DoParser();
	
public:
	__fastcall virtual TIBSQLParser(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBSQLParser();
	void __fastcall Parse();
	__property int CurrentLine = {read=LineIndex, nodefault};
	__property System::Classes::TStrings* CurrentTokens = {read=FTokens};
	
__published:
	__property bool Finished = {read=FFinished, nodefault};
	__property bool Paused = {read=FPaused, write=SetPaused, nodefault};
	__property System::Classes::TStrings* Script = {read=FScript, write=SetScript};
	__property System::UnicodeString Terminator = {read=FTerminator, write=FTerminator};
	__property TIBSQLParseStmt OnParse = {read=FOnParse, write=FOnParse};
	__property TIBSQLParseError OnError = {read=FOnError, write=FOnError};
};


class PASCALIMPLEMENTATION TIBScriptStats : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	__int64 FBuffers;
	__int64 FReadIdx;
	__int64 FWrites;
	__int64 FFetches;
	__int64 FSeqReads;
	__int64 FReads;
	__int64 FDeltaMem;
	bool FStarted;
	__int64 FStartBuffers;
	__int64 FStartReadIdx;
	__int64 FStartWrites;
	__int64 FStartFetches;
	__int64 FStartSeqReads;
	__int64 FStartReads;
	__int64 FStartingMem;
	Ibx::Ibdatabase::TIBDatabase* FDatabase;
	Ibx::Ibdatabaseinfo::TIBDatabaseInfo* FInfoStats;
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* const Value);
	__int64 __fastcall AddStringValues(System::Classes::TStrings* list);
	
public:
	__fastcall TIBScriptStats();
	__fastcall virtual ~TIBScriptStats();
	void __fastcall Start();
	void __fastcall Clear();
	void __fastcall Stop();
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=FDatabase, write=SetDatabase};
	__property __int64 Buffers = {read=FBuffers};
	__property __int64 Reads = {read=FReads};
	__property __int64 Writes = {read=FWrites};
	__property __int64 SeqReads = {read=FSeqReads};
	__property __int64 Fetches = {read=FFetches};
	__property __int64 ReadIdx = {read=FReadIdx};
	__property __int64 DeltaMem = {read=FDeltaMem};
	__property __int64 StartingMem = {read=FStartingMem};
};


class PASCALIMPLEMENTATION TIBScript : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TIBSQLParser* FSQLParser;
	bool FAutoDDL;
	bool FStatsOn;
	Ibx::Ibcustomdataset::TIBDataSet* FDataset;
	Ibx::Ibdatabase::TIBDatabase* FDatabase;
	TIBSQLParseError FOnError;
	TIBSQLParseStmt FOnParse;
	Ibx::Ibdatabase::TIBTransaction* FDDLTransaction;
	Ibx::Ibdatabase::TIBTransaction* FTransaction;
	System::UnicodeString FTerminator;
	Ibx::Ibsql::TIBSQL* FDDLQuery;
	Ibx::Ibsql::TIBSQL* FDMLQuery;
	bool FContinue;
	TIBSQLExecuteError FOnExecuteError;
	TIBScriptParamCheck FOnParamCheck;
	bool FValidate;
	bool FValidating;
	TIBScriptStats* FStats;
	int FSQLDialect;
	System::UnicodeString FCharSet;
	TIBParseKind FCurrentStmt;
	bool FExecuting;
	bool InBatch;
	System::PByte *FBatchBuffer;
	int FBatchCount;
	int FBufferSize;
	TIBScriptBeforeSetSubscription FBeforeSetSubscription;
	TIBScriptOnShow FOnShow;
	bool __fastcall GetPaused();
	void __fastcall SetPaused(const bool Value);
	void __fastcall SetTerminator(const System::UnicodeString Value);
	void __fastcall SetupNewConnection();
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* const Value);
	void __fastcall SetTransaction(Ibx::Ibdatabase::TIBTransaction* const Value);
	System::UnicodeString __fastcall StripQuote(const System::UnicodeString Text);
	System::Classes::TStrings* __fastcall GetScript();
	void __fastcall SetScript(System::Classes::TStrings* const Value);
	Ibx::Ibsql::TIBXSQLDA* __fastcall GetSQLParams();
	void __fastcall SetStatsOn(const bool Value);
	System::Classes::TStrings* __fastcall GetTokens();
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall DoDML(const System::UnicodeString Text);
	virtual void __fastcall DoDDL(const System::UnicodeString Text);
	virtual void __fastcall DoSET(const System::UnicodeString Text);
	virtual void __fastcall DoConnect(const System::UnicodeString SQLText);
	virtual void __fastcall DoCreate(const System::UnicodeString SQLText);
	virtual void __fastcall DoReconnect(const System::UnicodeString SQLText);
	virtual void __fastcall DropDatabase(const System::UnicodeString SQLText);
	virtual void __fastcall DoServerSet(const System::UnicodeString Text);
	virtual void __fastcall DoSetTransaction(const System::UnicodeString Text);
	void __fastcall ParserError(System::TObject* Sender, System::UnicodeString Error, System::UnicodeString SQLText, int LineIndex);
	void __fastcall ParserParse(System::TObject* Sender, TIBParseKind AKind, System::UnicodeString SQLText);
	
public:
	__fastcall virtual TIBScript(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBScript();
	bool __fastcall ValidateScript();
	void __fastcall ExecuteScript();
	Ibx::Ibsql::TIBXSQLVAR* __fastcall ParamByName(System::UnicodeString Idx);
	__property bool Paused = {read=GetPaused, write=SetPaused, nodefault};
	__property Ibx::Ibsql::TIBXSQLDA* Params = {read=GetSQLParams};
	__property TIBScriptStats* Stats = {read=FStats};
	__property System::Classes::TStrings* CurrentTokens = {read=GetTokens};
	__property bool Validating = {read=FValidating, nodefault};
	
__published:
	__property bool AutoDDL = {read=FAutoDDL, write=FAutoDDL, default=1};
	__property Ibx::Ibcustomdataset::TIBDataSet* Dataset = {read=FDataset, write=FDataset};
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=FDatabase, write=SetDatabase};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=FTransaction, write=SetTransaction};
	__property System::UnicodeString Terminator = {read=FTerminator, write=SetTerminator};
	__property System::Classes::TStrings* Script = {read=GetScript, write=SetScript};
	__property bool Statistics = {read=FStatsOn, write=SetStatsOn, default=1};
	__property TIBSQLParseStmt OnParse = {read=FOnParse, write=FOnParse};
	__property TIBSQLParseError OnParseError = {read=FOnError, write=FOnError};
	__property TIBSQLExecuteError OnExecuteError = {read=FOnExecuteError, write=FOnExecuteError};
	__property TIBScriptParamCheck OnParamCheck = {read=FOnParamCheck, write=FOnParamCheck};
	__property TIBScriptBeforeSetSubscription BeforeSetSubscription = {read=FBeforeSetSubscription, write=FBeforeSetSubscription};
	__property TIBScriptOnShow OnShow = {read=FOnShow, write=FOnShow};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibscript */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBSCRIPT)
using namespace Ibx::Ibscript;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbscriptHPP
