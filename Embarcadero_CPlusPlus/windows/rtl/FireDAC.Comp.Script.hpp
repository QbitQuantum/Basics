// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Comp.Script.pas' rev: 34.00 (Windows)

#ifndef Firedac_Comp_ScriptHPP
#define Firedac_Comp_ScriptHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.SQLPreprocessor.hpp>
#include <FireDAC.Comp.UI.hpp>
#include <FireDAC.Comp.Client.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Comp
{
namespace Script
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFDScriptEngineIntf;
typedef System::DelphiInterface<IFDScriptEngineIntf> _di_IFDScriptEngineIntf;
class DELPHICLASS TFDScriptCommand;
class DELPHICLASS TFDScriptCommandRegistry;
class DELPHICLASS TFDScriptParser;
class DELPHICLASS TFDScriptOptions;
class DELPHICLASS TFDSQLScript;
class DELPHICLASS TFDSQLScripts;
class DELPHICLASS TFDScript;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
typedef System::TMetaClass* TFDScriptCommandClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TFDScriptCommandClass);
#endif /* _WIN64 */

enum DECLSPEC_DENUM TFDScriptEchoCommands : unsigned int { ecNone, ecSQL, ecAll };

enum DECLSPEC_DENUM TFDScriptSpoolOutputMode : unsigned int { smNone, smOnReset, smOnAppend };

enum DECLSPEC_DENUM TFDScriptStatus : unsigned int { ssInactive, ssValidating, ssRunning, ssFinishWithErrors, ssFinishSuccess, ssAborted };

enum DECLSPEC_DENUM TFDScriptTextMode : unsigned int { smRead, smWriteReset, smWriteAppend };

typedef void __fastcall (__closure *TFDHostCommandEvent)(TFDScript* AEngine, const System::UnicodeString ACommand, bool &ADoDefault);

typedef void __fastcall (__closure *TFDConsolePutEvent)(TFDScript* AEngine, const System::UnicodeString AMessage, Firedac::Ui::Intf::TFDScriptOutputKind AKind);

typedef void __fastcall (__closure *TFDConsoleLockUpdate)(TFDScript* AEngine, bool ALock);

typedef void __fastcall (__closure *TFDConsoleGetEvent)(TFDScript* AEngine, const System::UnicodeString APrompt, System::UnicodeString &AResult);

typedef void __fastcall (__closure *TFDGetTextEvent)(TFDScript* AEngine, const System::UnicodeString AFileName, TFDScriptTextMode AMode, /* out */ Firedac::Stan::Util::TFDTextFile* &AText);

typedef void __fastcall (__closure *TFDPauseEvent)(TFDScript* AEngine, const System::UnicodeString AText);

__interface  INTERFACE_UUID("{FFD3BABC-CFAB-4A6E-9B1B-882E76791DF6}") IFDScriptEngineIntf  : public System::IInterface 
{
	virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetRDBMSKind() = 0 ;
	virtual Firedac::Phys::Intf::_di_IFDPhysConnection __fastcall GetConnectionIntf() = 0 ;
	virtual Firedac::Phys::Intf::_di_IFDPhysCommand __fastcall GetCommandIntf() = 0 ;
	virtual Firedac::Dats::TFDDatSTable* __fastcall GetTable() = 0 ;
	virtual void __fastcall CheckCommand() = 0 ;
	virtual void __fastcall CheckCommit(bool AForce) = 0 ;
	virtual void __fastcall CheckStartTransaction() = 0 ;
	virtual void __fastcall UpdateCommandSeparator() = 0 ;
	virtual System::UnicodeString __fastcall ExpandString(const System::UnicodeString AValue) = 0 ;
	virtual void __fastcall CloseSpool() = 0 ;
	virtual void __fastcall UpdateSpool() = 0 ;
	virtual void __fastcall OpenConnection(const System::UnicodeString AConnectionString) = 0 ;
	virtual void __fastcall CloseConnection() = 0 ;
	virtual void __fastcall Disconnect(bool AAbortJob = false) = 0 ;
	virtual bool __fastcall ExecuteAll(TFDScriptParser* AParser) = 0 /* overload */;
	virtual bool __fastcall ExecuteStep(TFDScriptParser* AParser) = 0 /* overload */;
	virtual bool __fastcall ValidateAll(TFDScriptParser* AParser) = 0 /* overload */;
	virtual bool __fastcall ValidateStep(TFDScriptParser* AParser) = 0 /* overload */;
	virtual void __fastcall Progress() = 0 ;
	virtual void __fastcall ConPut(const System::UnicodeString AMsg, Firedac::Ui::Intf::TFDScriptOutputKind AKind) = 0 ;
	virtual void __fastcall ConLockUpdate() = 0 ;
	virtual void __fastcall ConUnlockUpdate() = 0 ;
	virtual void __fastcall ConGet(const System::UnicodeString APrompt, System::UnicodeString &AResult) = 0 ;
	virtual void __fastcall ConPause(const System::UnicodeString APrompt) = 0 ;
	virtual void __fastcall GetText(const System::UnicodeString AFileName, TFDScriptTextMode AMode, /* out */ Firedac::Stan::Util::TFDTextFile* &AText) = 0 ;
	virtual void __fastcall ReleaseText(const System::UnicodeString AFileName, TFDScriptTextMode AMode, Firedac::Stan::Util::TFDTextFile* &AText) = 0 ;
	virtual void __fastcall ExecuteHostCommand(const System::UnicodeString ACommand) = 0 ;
	__property Firedac::Phys::Intf::_di_IFDPhysConnection ConnectionIntf = {read=GetConnectionIntf};
	__property Firedac::Phys::Intf::_di_IFDPhysCommand CommandIntf = {read=GetCommandIntf};
	__property Firedac::Stan::Intf::TFDRDBMSKind RDBMSKind = {read=GetRDBMSKind};
	__property Firedac::Dats::TFDDatSTable* Table = {read=GetTable};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDScriptCommand : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TFDScriptParser* FParser;
	TFDScript* FEngine;
	_di_IFDScriptEngineIntf FEngineIntf;
	System::Types::TPoint FPosition;
	
public:
	__fastcall virtual TFDScriptCommand(TFDScriptParser* AParser, TFDScript* AEngine);
	__fastcall virtual ~TFDScriptCommand();
	virtual System::UnicodeString __fastcall Dump();
	__classmethod virtual System::UnicodeString __fastcall Help();
	__classmethod virtual void __fastcall Keywords(System::Classes::TStrings* AKwds);
	virtual bool __fastcall Parse(const System::UnicodeString AKwd);
	virtual void __fastcall Execute();
	virtual void __fastcall Validate();
	virtual void __fastcall AbortJob(const bool AWait = false);
	__property TFDScriptParser* Parser = {read=FParser};
	__property TFDScript* Engine = {read=FEngine};
	__property _di_IFDScriptEngineIntf EngineIntf = {read=FEngineIntf};
	__property System::Types::TPoint Position = {read=FPosition};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TFDScriptCommandLookupRes : unsigned int { ucNone, ucPartial, ucShort, ucExact };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDScriptCommandRegistry : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TFDScriptCommandClass operator[](int AIndex) { return this->Commands[AIndex]; }
	
private:
	Firedac::Stan::Intf::TFDStringList* FKeywords;
	System::Classes::TList* FCommands;
	TFDScriptCommandClass FDefaultSQLCommandClass;
	TFDScriptCommandClass FDefaultPLSQLCommandClass;
	TFDScriptCommandClass __fastcall GetCommand(int AIndex);
	int __fastcall GetCount();
	
public:
	__fastcall TFDScriptCommandRegistry();
	__fastcall virtual ~TFDScriptCommandRegistry();
	void __fastcall AddCommand(TFDScriptCommandClass ACommand);
	TFDScriptCommandLookupRes __fastcall LookupCommand(const System::UnicodeString AStr, /* out */ TFDScriptCommandClass &ACommand);
	__property TFDScriptCommandClass DefaultSQLCommandClass = {read=FDefaultSQLCommandClass, write=FDefaultSQLCommandClass};
	__property TFDScriptCommandClass DefaultPLSQLCommandClass = {read=FDefaultPLSQLCommandClass, write=FDefaultPLSQLCommandClass};
	__property int Count = {read=GetCount, nodefault};
	__property TFDScriptCommandClass Commands[int AIndex] = {read=GetCommand/*, default*/};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TFDScriptParser : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::WideChar FCh;
	bool FBeginningOfLine;
	bool FWasBeginningOfLine;
	System::UnicodeString FFileName;
	TFDScriptCommand* FParentCommand;
	int FLineNumber;
	__int64 FLineNumberPos;
	int FTotalSize;
	TFDScriptOptions* FScriptOptions;
	Firedac::Stan::Util::TFDTextFile* FText;
	System::UnicodeString FLastKwd;
	Firedac::Phys::Sqlpreprocessor::TFDPhysPreprocessor* FPrep;
	TFDScriptCommand* __fastcall CreateScriptCommand(TFDScriptCommandClass ACmdClass, TFDScript* AEngine, const System::UnicodeString AKwd);
	bool __fastcall CreateSQLCommand(int &ABeginBmk, int &ALastBmk, int &AEndBmk, TFDScript* AEngine, TFDScriptCommand* &ACommand);
	System::Types::TPoint __fastcall GetPosition();
	void __fastcall SetPosition(const System::Types::TPoint &AValue);
	System::UnicodeString __fastcall InternalGetString(bool AAllowQuote, bool AAllowDoubleQuote, bool ARequired, bool AIgnoreSep, const Firedac::Stan::Intf::TFDCharSet &ASet);
	bool __fastcall GetEOL(System::WideChar AFirstCh);
	
protected:
	System::WideChar __fastcall InternalGetChar();
	int __fastcall InternalGetBookmark();
	void __fastcall InternalSetBookmark(int ABmk);
	System::UnicodeString __fastcall InternalExtractString(int ABmk1, int ABmk2);
	
public:
	__fastcall TFDScriptParser(System::UnicodeString AFileName, TFDScriptCommand* AParentCommand, Firedac::Stan::Util::TFDTextFile* AText, TFDScriptOptions* AOptions);
	void __fastcall GetChar();
	void __fastcall UnGetChar();
	int __fastcall GetBookmark();
	void __fastcall SetBookmark(int ABmk);
	System::UnicodeString __fastcall ExtractString(int ABmk1, int ABmk2);
	void __fastcall SkipWS();
	void __fastcall SkipWSLF();
	System::UnicodeString __fastcall GetUCWord();
	System::UnicodeString __fastcall GetString(bool ARequired = false);
	System::UnicodeString __fastcall GetStringInFull();
	System::UnicodeString __fastcall GetIdentifier();
	System::UnicodeString __fastcall GetLine();
	int __fastcall GetOnOfChar(System::WideChar ADef);
	int __fastcall GetOnOff();
	int __fastcall GetNumber(int ADef = 0x0);
	void __fastcall InvalidSyntax();
	TFDScriptCommand* __fastcall ExtractCommand(TFDScript* AEngine);
	__property System::WideChar Ch = {read=FCh, nodefault};
	__property System::UnicodeString FileName = {read=FFileName};
	__property int LineNumber = {read=FLineNumber, nodefault};
	__property TFDScriptCommand* ParentCommand = {read=FParentCommand};
	__property bool WasBeginningOfLine = {read=FWasBeginningOfLine, nodefault};
	__property int TotalSize = {read=FTotalSize, write=FTotalSize, nodefault};
	__property TFDScriptOptions* ScriptOptions = {read=FScriptOptions, write=FScriptOptions};
	__property System::Types::TPoint Position = {read=GetPosition, write=SetPosition};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDScriptParser() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDScriptOptions : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Classes::TPersistent* FOwner;
	int FCommitEachNCommands;
	bool FAutoPrintParams;
	TFDScriptEchoCommands FEchoCommands;
	bool FFeedbackCommands;
	bool FColumnHeadings;
	int FMaxBytesToPrintLongs;
	bool FConsoleOutput;
	TFDScriptSpoolOutputMode FSpoolOutput;
	System::UnicodeString FSpoolFileName;
	bool FTiming;
	bool FBreakOnError;
	bool FDropNonexistObj;
	System::UnicodeString FCommandSeparator;
	int FParamArraySize;
	int FEchoCommandTrim;
	bool FFeedbackScript;
	System::UnicodeString FActualCommandSeparator;
	System::UnicodeString FDefaultScriptPath;
	bool FMacroExpand;
	bool FTrimConsole;
	bool FTrimSpool;
	bool FVerify;
	System::UnicodeString FDefaultDataPath;
	int FPageSize;
	int FLineSize;
	Firedac::Stan::Intf::TFDTextEndOfLine FFileEndOfLine;
	Firedac::Stan::Intf::TFDEncoding FFileEncoding;
	bool FIgnoreError;
	System::UnicodeString FCharacterSet;
	int FSQLDialect;
	System::UnicodeString FClientLib;
	System::UnicodeString FDriverID;
	bool FRaisePLSQLErrors;
	System::UnicodeString FBlobFile;
	void __fastcall SetCommandSeparator(const System::UnicodeString AValue);
	void __fastcall SetDriverID(const System::UnicodeString AValue);
	
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	
public:
	__property System::UnicodeString ActualCommandSeparator = {read=FActualCommandSeparator};
	
__published:
	__fastcall TFDScriptOptions(System::Classes::TPersistent* AOwner);
	void __fastcall Reset();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property int CommitEachNCommands = {read=FCommitEachNCommands, write=FCommitEachNCommands, default=0};
	__property bool AutoPrintParams = {read=FAutoPrintParams, write=FAutoPrintParams, default=0};
	__property TFDScriptEchoCommands EchoCommands = {read=FEchoCommands, write=FEchoCommands, default=1};
	__property int EchoCommandTrim = {read=FEchoCommandTrim, write=FEchoCommandTrim, default=50};
	__property bool FeedbackCommands = {read=FFeedbackCommands, write=FFeedbackCommands, default=1};
	__property bool FeedbackScript = {read=FFeedbackScript, write=FFeedbackScript, default=1};
	__property bool ColumnHeadings = {read=FColumnHeadings, write=FColumnHeadings, default=1};
	__property int MaxStringWidth = {read=FMaxBytesToPrintLongs, write=FMaxBytesToPrintLongs, default=80};
	__property bool ConsoleOutput = {read=FConsoleOutput, write=FConsoleOutput, default=1};
	__property TFDScriptSpoolOutputMode SpoolOutput = {read=FSpoolOutput, write=FSpoolOutput, default=0};
	__property System::UnicodeString SpoolFileName = {read=FSpoolFileName, write=FSpoolFileName};
	__property bool Timing = {read=FTiming, write=FTiming, default=1};
	__property bool BreakOnError = {read=FBreakOnError, write=FBreakOnError, default=0};
	__property bool IgnoreError = {read=FIgnoreError, write=FIgnoreError, default=0};
	__property bool DropNonexistObj = {read=FDropNonexistObj, write=FDropNonexistObj, default=1};
	__property System::UnicodeString CommandSeparator = {read=FCommandSeparator, write=SetCommandSeparator};
	__property int ParamArraySize = {read=FParamArraySize, write=FParamArraySize, default=1};
	__property int PageSize = {read=FPageSize, write=FPageSize, default=24};
	__property int LineSize = {read=FLineSize, write=FLineSize, default=0};
	__property System::UnicodeString DefaultScriptPath = {read=FDefaultScriptPath, write=FDefaultScriptPath};
	__property bool MacroExpand = {read=FMacroExpand, write=FMacroExpand, default=1};
	__property bool TrimConsole = {read=FTrimConsole, write=FTrimConsole, default=0};
	__property bool TrimSpool = {read=FTrimSpool, write=FTrimSpool, default=1};
	__property bool Verify = {read=FVerify, write=FVerify, default=0};
	__property System::UnicodeString DefaultDataPath = {read=FDefaultDataPath, write=FDefaultDataPath};
	__property Firedac::Stan::Intf::TFDEncoding FileEncoding = {read=FFileEncoding, write=FFileEncoding, default=0};
	__property Firedac::Stan::Intf::TFDTextEndOfLine FileEndOfLine = {read=FFileEndOfLine, write=FFileEndOfLine, default=0};
	__property System::UnicodeString DriverID = {read=FDriverID, write=SetDriverID};
	__property System::UnicodeString ClientLib = {read=FClientLib, write=FClientLib};
	__property System::UnicodeString CharacterSet = {read=FCharacterSet, write=FCharacterSet};
	__property int SQLDialect = {read=FSQLDialect, write=FSQLDialect, default=0};
	__property bool RaisePLSQLErrors = {read=FRaisePLSQLErrors, write=FRaisePLSQLErrors, default=0};
	__property System::UnicodeString BlobFile = {read=FBlobFile, write=FBlobFile};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TFDScriptOptions() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDSQLScript : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	System::Classes::TStrings* FSQL;
	void __fastcall SetSQL(System::Classes::TStrings* const AValue);
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall virtual TFDSQLScript(System::Classes::TCollection* Collection);
	__fastcall virtual ~TFDSQLScript();
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
	
__published:
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property System::Classes::TStrings* SQL = {read=FSQL, write=SetSQL};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDSQLScripts : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TFDSQLScript* operator[](int AIndex) { return this->Items[AIndex]; }
	
private:
	TFDSQLScript* __fastcall GetItems(int AIndex);
	void __fastcall SetItems(int AIndex, TFDSQLScript* const AValue);
	
public:
	__fastcall TFDSQLScripts(TFDScript* AScript);
	HIDESBASE TFDSQLScript* __fastcall Add();
	TFDSQLScript* __fastcall FindScript(const System::UnicodeString AName);
	__property TFDSQLScript* Items[int AIndex] = {read=GetItems, write=SetItems/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TFDSQLScripts() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TFDScript : public Firedac::Stan::Intf::TFDComponent
{
	typedef Firedac::Stan::Intf::TFDComponent inherited;
	
private:
	bool FFinished;
	Firedac::Phys::Intf::_di_IFDPhysConnection FConnectionIntf;
	Firedac::Phys::Intf::_di_IFDPhysCommand FCommandIntf;
	Firedac::Dats::TFDDatSTable* FTable;
	Firedac::Stan::Param::TFDMacros* FMacros;
	Firedac::Stan::Param::TFDParams* FParams;
	System::Classes::TStrings* FArguments;
	int FProcessedAfterCommit;
	Firedac::Stan::Util::TFDTextFile* FSpool;
	System::UnicodeString FLastSpoolFileName;
	System::Syncobjs::TCriticalSection* FLock;
	Firedac::Phys::Sqlpreprocessor::TFDPhysPreprocessor* FPrep;
	Firedac::Stan::Intf::TFDRDBMSKind FRDBMSKind;
	TFDScriptCommand* FCurrentCommand;
	System::Classes::TStrings* FCallStack;
	System::Classes::TStrings* FAllSpools;
	int FTotalJobSize;
	int FTotalJobDone;
	int FTotalPct10Done;
	int FTotalErrors;
	TFDScriptStatus FStatus;
	TFDHostCommandEvent FOnHostCommand;
	TFDConsolePutEvent FOnConsolePut;
	TFDConsoleLockUpdate FOnConsoleLockUpdate;
	TFDConsoleGetEvent FOnConsoleGet;
	TFDConsolePutEvent FOnSpoolPut;
	TFDGetTextEvent FOnGetText;
	TFDGetTextEvent FOnReleaseText;
	TFDPauseEvent FOnPause;
	System::Classes::TNotifyEvent FOnProgress;
	System::Classes::TNotifyEvent FBeforeScript;
	System::Classes::TNotifyEvent FAfterScript;
	System::Classes::TNotifyEvent FAfterExecute;
	System::Classes::TNotifyEvent FBeforeExecute;
	Firedac::Stan::Error::TFDErrorEvent FOnError;
	TFDScriptOptions* FScriptOptions;
	Firedac::Comp::Ui::TFDGUIxScriptDialog* FScriptDialog;
	bool FScriptDialogVisible;
	System::UnicodeString FSQLScriptFileName;
	TFDSQLScripts* FSQLScripts;
	Firedac::Comp::Client::TFDCustomConnection* FConnection;
	Firedac::Comp::Client::TFDCustomTransaction* FTransaction;
	Firedac::Stan::Option::_di_IFDStanOptions FOptionsIntf;
	System::Types::TPoint FPosition;
	bool __fastcall GetScriptDialogIntf(/* out */ Firedac::Ui::Intf::_di_IFDGUIxScriptDialog &AIntf);
	void __fastcall SetCurrentCommand(TFDScriptCommand* const ACommand);
	void __fastcall SetScriptOptions(TFDScriptOptions* const AValue);
	void __fastcall SetScriptDialog(Firedac::Comp::Ui::TFDGUIxScriptDialog* const AValue);
	void __fastcall RestoreArguments(System::Classes::TStrings* AArgs);
	System::Classes::TStrings* __fastcall SetupArguments();
	void __fastcall SetArguments(System::Classes::TStrings* const AValue);
	void __fastcall SetConnection(Firedac::Comp::Client::TFDCustomConnection* const AValue);
	void __fastcall SetTransaction(Firedac::Comp::Client::TFDCustomTransaction* const AValue);
	void __fastcall DoConnectChanged(System::TObject* Sender, bool Connecting);
	void __fastcall SetSQLScripts(TFDSQLScripts* const AValue);
	Firedac::Stan::Option::TFDFetchOptions* __fastcall GetFetchOptions();
	Firedac::Stan::Option::TFDFormatOptions* __fastcall GetFormatOptions();
	Firedac::Stan::Option::TFDResourceOptions* __fastcall GetResourceOptions();
	void __fastcall SetFetchOptions(Firedac::Stan::Option::TFDFetchOptions* const Value);
	void __fastcall SetFormatOptions(Firedac::Stan::Option::TFDFormatOptions* const Value);
	void __fastcall SetResourceOptions(Firedac::Stan::Option::TFDResourceOptions* const Value);
	bool __fastcall GetEof();
	void __fastcall SetMacros(Firedac::Stan::Param::TFDMacros* const AValue);
	void __fastcall SetParams(Firedac::Stan::Param::TFDParams* const AValue);
	System::Classes::TPersistent* __fastcall GetParamsOwner();
	bool __fastcall GetIsEmpty();
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation AOperation);
	bool __fastcall InternalExecute(TFDScriptParser* AParser, bool ARealExecute, bool AAll)/* overload */;
	bool __fastcall InternalExecute(bool ARealExecute, bool AAll)/* overload */;
	void __fastcall InternalOpenConnection(const System::UnicodeString AConnectionString);
	void __fastcall InternalReleaseConnection();
	System::Classes::TComponentName __fastcall GetName();
	Firedac::Stan::Intf::_di_IFDStanObject __fastcall GetParent();
	void __fastcall BeforeReuse();
	void __fastcall AfterReuse();
	void __fastcall SetOwner(System::TObject* const AOwner, const System::Classes::TComponentName ARole);
	__property Firedac::Stan::Option::_di_IFDStanOptions OptionsIntf = {read=FOptionsIntf};
	void __fastcall GetParentOptions(Firedac::Stan::Option::_di_IFDStanOptions &AOpts);
	virtual void __fastcall HandleException(const Firedac::Stan::Intf::_di_IFDStanObject AInitiator, System::Sysutils::Exception* &AException);
	void __fastcall RequestStop();
	System::Classes::TStrings* __fastcall GetCallStack();
	int __fastcall GetTotalJobSize();
	int __fastcall GetTotalJobDone();
	int __fastcall GetTotalPct10Done();
	int __fastcall GetTotalErrors();
	bool __fastcall GetIsRunning();
	Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetRDBMSKind();
	Firedac::Phys::Intf::_di_IFDPhysConnection __fastcall GetConnectionIntf();
	Firedac::Phys::Intf::_di_IFDPhysCommand __fastcall GetCommandIntf();
	Firedac::Dats::TFDDatSTable* __fastcall GetTable();
	void __fastcall CheckCommand();
	void __fastcall CheckCommit(bool AForce);
	void __fastcall CheckStartTransaction();
	void __fastcall UpdateCommandSeparator();
	System::UnicodeString __fastcall ExpandString(const System::UnicodeString AValue);
	void __fastcall CloseSpool();
	void __fastcall UpdateSpool();
	void __fastcall OpenConnection(const System::UnicodeString AConnectionString);
	void __fastcall CloseConnection();
	void __fastcall Disconnect(bool AAbortJob = false);
	bool __fastcall ExecuteAll(TFDScriptParser* AParser)/* overload */;
	bool __fastcall ExecuteStep(TFDScriptParser* AParser)/* overload */;
	bool __fastcall ValidateAll(TFDScriptParser* AParser)/* overload */;
	bool __fastcall ValidateStep(TFDScriptParser* AParser)/* overload */;
	void __fastcall Progress();
	virtual void __fastcall ConPut(const System::UnicodeString AMsg, Firedac::Ui::Intf::TFDScriptOutputKind AKind);
	virtual void __fastcall ConLockUpdate();
	virtual void __fastcall ConUnlockUpdate();
	virtual void __fastcall ConGet(const System::UnicodeString APrompt, System::UnicodeString &AResult);
	virtual void __fastcall ConPause(const System::UnicodeString APrompt);
	virtual void __fastcall GetText(const System::UnicodeString AFileName, TFDScriptTextMode AMode, /* out */ Firedac::Stan::Util::TFDTextFile* &AText);
	virtual void __fastcall ReleaseText(const System::UnicodeString AFileName, TFDScriptTextMode AMode, Firedac::Stan::Util::TFDTextFile* &AText);
	virtual void __fastcall ExecuteHostCommand(const System::UnicodeString ACommand);
	
public:
	__fastcall virtual TFDScript(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDScript();
	bool __fastcall ExecuteAll()/* overload */;
	bool __fastcall ExecuteStep()/* overload */;
	bool __fastcall ValidateAll()/* overload */;
	bool __fastcall ValidateStep()/* overload */;
	void __fastcall ExecuteFile(const System::UnicodeString AFileName)/* overload */;
	void __fastcall ExecuteFile(const System::UnicodeString AFileName, const System::UnicodeString *AArguments, const int AArguments_High)/* overload */;
	void __fastcall ExecuteScript(System::Classes::TStrings* const AScript)/* overload */;
	void __fastcall ExecuteScript(System::Classes::TStrings* const AScript, const System::UnicodeString *AArguments, const int AArguments_High)/* overload */;
	void __fastcall AbortJob(const bool AWait = false);
	__property System::Classes::TStrings* CallStack = {read=GetCallStack};
	__property int TotalJobSize = {read=GetTotalJobSize, nodefault};
	__property int TotalJobDone = {read=GetTotalJobDone, nodefault};
	__property int TotalPct10Done = {read=GetTotalPct10Done, nodefault};
	__property int TotalErrors = {read=GetTotalErrors, nodefault};
	__property TFDScriptCommand* CurrentCommand = {read=FCurrentCommand};
	__property System::Classes::TStrings* AllSpools = {read=FAllSpools};
	__property System::UnicodeString LastSpoolFileName = {read=FLastSpoolFileName};
	__property TFDScriptStatus Status = {read=FStatus, nodefault};
	__property bool Eof = {read=GetEof, nodefault};
	__property bool IsEmpty = {read=GetIsEmpty, nodefault};
	__property System::Types::TPoint Position = {read=FPosition, write=FPosition};
	__property bool Finished = {read=FFinished, write=FFinished, nodefault};
	__property int ProcessedAfterCommit = {read=FProcessedAfterCommit, write=FProcessedAfterCommit, nodefault};
	
__published:
	__property System::UnicodeString SQLScriptFileName = {read=FSQLScriptFileName, write=FSQLScriptFileName};
	__property TFDSQLScripts* SQLScripts = {read=FSQLScripts, write=SetSQLScripts};
	__property Firedac::Comp::Client::TFDCustomConnection* Connection = {read=FConnection, write=SetConnection};
	__property Firedac::Comp::Client::TFDCustomTransaction* Transaction = {read=FTransaction, write=SetTransaction};
	__property TFDScriptOptions* ScriptOptions = {read=FScriptOptions, write=SetScriptOptions};
	__property Firedac::Comp::Ui::TFDGUIxScriptDialog* ScriptDialog = {read=FScriptDialog, write=SetScriptDialog};
	__property Firedac::Stan::Param::TFDParams* Params = {read=FParams, write=SetParams};
	__property Firedac::Stan::Param::TFDMacros* Macros = {read=FMacros, write=SetMacros};
	__property System::Classes::TStrings* Arguments = {read=FArguments, write=SetArguments};
	__property Firedac::Stan::Option::TFDFormatOptions* FormatOptions = {read=GetFormatOptions, write=SetFormatOptions};
	__property Firedac::Stan::Option::TFDFetchOptions* FetchOptions = {read=GetFetchOptions, write=SetFetchOptions};
	__property Firedac::Stan::Option::TFDResourceOptions* ResourceOptions = {read=GetResourceOptions, write=SetResourceOptions};
	__property TFDHostCommandEvent OnHostCommand = {read=FOnHostCommand, write=FOnHostCommand};
	__property TFDConsolePutEvent OnConsolePut = {read=FOnConsolePut, write=FOnConsolePut};
	__property TFDConsoleLockUpdate OnConsoleLockUpdate = {read=FOnConsoleLockUpdate, write=FOnConsoleLockUpdate};
	__property TFDConsoleGetEvent OnConsoleGet = {read=FOnConsoleGet, write=FOnConsoleGet};
	__property TFDConsolePutEvent OnSpoolPut = {read=FOnSpoolPut, write=FOnSpoolPut};
	__property TFDGetTextEvent OnGetText = {read=FOnGetText, write=FOnGetText};
	__property TFDGetTextEvent OnReleaseText = {read=FOnReleaseText, write=FOnReleaseText};
	__property TFDPauseEvent OnPause = {read=FOnPause, write=FOnPause};
	__property System::Classes::TNotifyEvent OnProgress = {read=FOnProgress, write=FOnProgress};
	__property System::Classes::TNotifyEvent BeforeScript = {read=FBeforeScript, write=FBeforeScript};
	__property System::Classes::TNotifyEvent AfterScript = {read=FAfterScript, write=FAfterScript};
	__property Firedac::Stan::Error::TFDErrorEvent OnError = {read=FOnError, write=FOnError};
	__property System::Classes::TNotifyEvent BeforeExecute = {read=FBeforeExecute, write=FBeforeExecute};
	__property System::Classes::TNotifyEvent AfterExecute = {read=FAfterExecute, write=FAfterExecute};
private:
	void *__IFDScriptEngineIntf;	// IFDScriptEngineIntf 
	void *__IFDGUIxScriptDialogInfoProvider;	// Firedac::Ui::Intf::IFDGUIxScriptDialogInfoProvider 
	void *__IFDStanObject;	// Firedac::Stan::Intf::IFDStanObject 
	void *__IFDStanErrorHandler;	// Firedac::Stan::Intf::IFDStanErrorHandler 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FFD3BABC-CFAB-4A6E-9B1B-882E76791DF6}
	operator _di_IFDScriptEngineIntf()
	{
		_di_IFDScriptEngineIntf intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFDScriptEngineIntf*(void) { return (IFDScriptEngineIntf*)&__IFDScriptEngineIntf; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2206}
	operator Firedac::Ui::Intf::_di_IFDGUIxScriptDialogInfoProvider()
	{
		Firedac::Ui::Intf::_di_IFDGUIxScriptDialogInfoProvider intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Ui::Intf::IFDGUIxScriptDialogInfoProvider*(void) { return (Firedac::Ui::Intf::IFDGUIxScriptDialogInfoProvider*)&__IFDGUIxScriptDialogInfoProvider; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2001}
	operator Firedac::Stan::Intf::_di_IFDStanObject()
	{
		Firedac::Stan::Intf::_di_IFDStanObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanObject*(void) { return (Firedac::Stan::Intf::IFDStanObject*)&__IFDStanObject; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2007}
	operator Firedac::Stan::Intf::_di_IFDStanErrorHandler()
	{
		Firedac::Stan::Intf::_di_IFDStanErrorHandler intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanErrorHandler*(void) { return (Firedac::Stan::Intf::IFDStanErrorHandler*)&__IFDStanErrorHandler; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2018}
	operator Firedac::Stan::Option::_di_IFDStanOptions() { return OptionsIntf; }
	#else
	operator Firedac::Stan::Option::IFDStanOptions*(void) { return (Firedac::Stan::Option::IFDStanOptions*)OptionsIntf; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall FDKeywordMatch(const System::UnicodeString AStr, const System::UnicodeString AMatch, int AOptLength);
extern DELPHI_PACKAGE TFDScriptCommandRegistry* __fastcall FDScriptCommandRegistry(void);
}	/* namespace Script */
}	/* namespace Comp */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_COMP_SCRIPT)
using namespace Firedac::Comp::Script;
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
#endif	// Firedac_Comp_ScriptHPP
