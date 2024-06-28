// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXTrace.pas' rev: 34.00 (Android)

#ifndef Data_DbxtraceHPP
#define Data_DbxtraceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXDelegate.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.FmtBcd.hpp>
#include <Data.SqlTimSt.hpp>
#include <Data.DBCommonTypes.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SyncObjs.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------
namespace Data
{
namespace Dbxtrace
{
  _INIT_UNIT(Data_Dbxtrace);
}	/* namespace Dbxtrace */
}	/* namespace Data */

namespace Data
{
namespace Dbxtrace
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXTracePropertyNames;
class DELPHICLASS TDBXTraceFlagNames;
class DELPHICLASS TDBXTraceWriter;
class DELPHICLASS TDBXConsoleTraceWriter;
class DELPHICLASS TDBXTraceFormatter;
class DELPHICLASS TDBXTracePascalFormatter;
class DELPHICLASS TDBXTraceOutput;
class DELPHICLASS TDBXConsoleTraceOutput;
class DELPHICLASS TDBXFileTraceOutput;
class DELPHICLASS TDBXTraceDriver;
class DELPHICLASS TDBXTraceConnection;
class DELPHICLASS TDBXTraceCommand;
class DELPHICLASS TDBXTraceParameterList;
class DELPHICLASS TDBXTraceWritableValue;
class DELPHICLASS TDBXTraceParameter;
class DELPHICLASS TDBXTraceReader;
class DELPHICLASS TDBXTraceProperties;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTracePropertyNames : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXTracePropertyNames_TraceFlags u"TraceFlags"
	
	#define TDBXTracePropertyNames_TraceDriver u"TraceDriver"
	
	#define TDBXTracePropertyNames_TraceFile u"TraceFile"
	
public:
	/* TObject.Create */ inline __fastcall TDBXTracePropertyNames() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTracePropertyNames() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTraceFlagNames : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXTraceFlagNames_NONE u"NONE"
	
	#define TDBXTraceFlagNames_PREPARE u"PREPARE"
	
	#define TDBXTraceFlagNames_EXECUTE u"EXECUTE"
	
	#define TDBXTraceFlagNames_ERROR u"ERROR"
	
	#define TDBXTraceFlagNames_COMMAND u"COMMAND"
	
	#define TDBXTraceFlagNames_CONNECT u"CONNECT"
	
	#define TDBXTraceFlagNames_TRANSACT u"TRANSACT"
	
	#define TDBXTraceFlagNames_BLOB u"BLOB"
	
	#define TDBXTraceFlagNames_MISC u"MISC"
	
	#define TDBXTraceFlagNames_VENDOR u"VENDOR"
	
	#define TDBXTraceFlagNames_PARAMETER u"PARAMETER"
	
	#define TDBXTraceFlagNames_READER u"READER"
	
	#define TDBXTraceFlagNames_DRIVER_LOAD u"DRIVER_LOAD"
	
	#define TDBXTraceFlagNames_METADATA u"METADATA"
	
	#define TDBXTraceFlagNames_DRIVER u"DRIVER"
	
	#define TDBXTraceFlagNames_CUSTOM u"CUSTOM"
	
public:
	/* TObject.Create */ inline __fastcall TDBXTraceFlagNames() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTraceFlagNames() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTraceWriter : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual bool __fastcall IsSingleton() = 0 ;
	virtual Data::Dbcommontypes::CBRType __fastcall WriteTrace(const Data::Dbxcommon::TDBXTraceInfo &TraceInfo) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDBXTraceWriter() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTraceWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXConsoleTraceWriter : public TDBXTraceWriter
{
	typedef TDBXTraceWriter inherited;
	
public:
	virtual bool __fastcall IsSingleton();
	virtual Data::Dbcommontypes::CBRType __fastcall WriteTrace(const Data::Dbxcommon::TDBXTraceInfo &TraceInfo);
public:
	/* TObject.Create */ inline __fastcall TDBXConsoleTraceWriter() : TDBXTraceWriter() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXConsoleTraceWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTraceFormatter : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FCommentStart;
	System::UnicodeString FCommentEnd;
	int FMaxLineWidth;
	
protected:
	__fastcall TDBXTraceFormatter(System::UnicodeString CommentStart, System::UnicodeString CommentEnd, int MaxLineWidth);
	
private:
	virtual System::UnicodeString __fastcall Comment(System::UnicodeString CommentText) = 0 ;
	virtual System::UnicodeString __fastcall CommentValue(System::UnicodeString ResultName, System::UnicodeString Value) = 0 ;
	virtual System::UnicodeString __fastcall OpenComment(System::UnicodeString CommentText) = 0 ;
	virtual System::UnicodeString __fastcall CloseComment() = 0 ;
	virtual System::UnicodeString __fastcall GetProperty(System::UnicodeString ResultName, System::UnicodeString InstanceName, System::UnicodeString PropertyName) = 0 ;
	virtual System::UnicodeString __fastcall SetProperty(System::UnicodeString InstanceName, System::UnicodeString PropertyName, System::UnicodeString Value) = 0 ;
	virtual System::UnicodeString __fastcall CallProcedure(System::UnicodeString InstanceName, System::UnicodeString MethodName) = 0 ;
	virtual System::UnicodeString __fastcall CallFunction(System::UnicodeString ResultName, System::UnicodeString InstanceName, System::UnicodeString MethodName) = 0 ;
	virtual System::UnicodeString __fastcall CallOpenProcedure(System::UnicodeString InstanceName, System::UnicodeString MethodName) = 0 ;
	virtual System::UnicodeString __fastcall CallOpenFunction(System::UnicodeString ResultName, System::UnicodeString InstanceName, System::UnicodeString MethodName) = 0 ;
	virtual System::UnicodeString __fastcall ArrayProperty(System::UnicodeString InstanceName, int Ordinal) = 0 ;
	virtual System::UnicodeString __fastcall ParamString(System::UnicodeString Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamWideString(System::UnicodeString Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamBoolean(bool Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamUInt8(System::Byte Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamInt8(System::Int8 Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamUInt16(System::Word Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamInt16(short Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamInt32(int Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamInt64(__int64 Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamDouble(double Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamBcd(const Data::Fmtbcd::TBcd &Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamDate(Data::Dbxcommon::TDBXDate Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamTime(Data::Dbxcommon::TDBXTime Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamTimeStampOffset(const Data::Sqltimst::TSQLTimeStampOffset &Param, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ParamBytes(System::Byte *Param, const int Param_High, __int64 Offset, __int64 RequestedCount, __int64 Count, System::UnicodeString Separator) = 0 ;
	virtual System::UnicodeString __fastcall ColumnTypeToStr(int ColumnType);
	virtual System::UnicodeString __fastcall CloseProcedure() = 0 ;
	virtual System::UnicodeString __fastcall CloseFunction() = 0 ;
	virtual System::UnicodeString __fastcall QuoteString(System::UnicodeString Value) = 0 ;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTraceFormatter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTracePascalFormatter : public TDBXTraceFormatter
{
	typedef TDBXTraceFormatter inherited;
	
private:
	virtual System::UnicodeString __fastcall Comment(System::UnicodeString CommentText);
	virtual System::UnicodeString __fastcall CommentValue(System::UnicodeString ResultName, System::UnicodeString Value);
	virtual System::UnicodeString __fastcall OpenComment(System::UnicodeString CommentText);
	virtual System::UnicodeString __fastcall CloseComment();
	virtual System::UnicodeString __fastcall GetProperty(System::UnicodeString ResultName, System::UnicodeString InstanceName, System::UnicodeString PropertyName);
	virtual System::UnicodeString __fastcall SetProperty(System::UnicodeString InstanceName, System::UnicodeString PropertyName, System::UnicodeString Value);
	virtual System::UnicodeString __fastcall CallProcedure(System::UnicodeString InstanceName, System::UnicodeString MethodName);
	virtual System::UnicodeString __fastcall CallFunction(System::UnicodeString ResultName, System::UnicodeString InstanceName, System::UnicodeString MethodName);
	virtual System::UnicodeString __fastcall CallOpenProcedure(System::UnicodeString InstanceName, System::UnicodeString MethodName);
	virtual System::UnicodeString __fastcall CallOpenFunction(System::UnicodeString ResultName, System::UnicodeString InstanceName, System::UnicodeString MethodName);
	virtual System::UnicodeString __fastcall ArrayProperty(System::UnicodeString InstanceName, int Ordinal);
	virtual System::UnicodeString __fastcall ParamString(System::UnicodeString Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamWideString(System::UnicodeString Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamBoolean(bool Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamUInt8(System::Byte Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamInt8(System::Int8 Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamUInt16(System::Word Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamInt16(short Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamInt32(int Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamInt64(__int64 Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamDouble(double Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamBcd(const Data::Fmtbcd::TBcd &Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamDate(Data::Dbxcommon::TDBXDate Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamTime(Data::Dbxcommon::TDBXTime Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamTimeStampOffset(const Data::Sqltimst::TSQLTimeStampOffset &Param, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall ParamBytes(System::Byte *Param, const int Param_High, __int64 Offset, __int64 RequestedCount, __int64 Count, System::UnicodeString Separator);
	virtual System::UnicodeString __fastcall CloseProcedure();
	virtual System::UnicodeString __fastcall CloseFunction();
	virtual System::UnicodeString __fastcall QuoteString(System::UnicodeString Value);
protected:
	/* TDBXTraceFormatter.Create */ inline __fastcall TDBXTracePascalFormatter(System::UnicodeString CommentStart, System::UnicodeString CommentEnd, int MaxLineWidth) : TDBXTraceFormatter(CommentStart, CommentEnd, MaxLineWidth) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTracePascalFormatter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTraceOutput : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FName;
	int FReferenceCount;
	System::Syncobjs::TCriticalSection* FCriticalSection;
	TDBXTraceFormatter* FFormatter;
	virtual void __fastcall Open() = 0 ;
	virtual void __fastcall WriteTraceln(System::UnicodeString Line) = 0 ;
	Data::Dbcommontypes::CBRType __fastcall LogTrace(const Data::Dbxcommon::TDBXTraceInfo &TraceInfo);
	Data::Dbcommontypes::CBRType __fastcall LogDriverTrace(const Data::Dbxcommon::TDBXTraceInfo &TraceInfo);
	System::UnicodeString __fastcall TraceFlagToString(int TraceFlag);
	void __fastcall AddReference();
	int __fastcall RemoveReference();
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property TDBXTraceFormatter* Formatter = {read=FFormatter, write=FFormatter};
	
public:
	__fastcall TDBXTraceOutput();
	__fastcall virtual ~TDBXTraceOutput();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXConsoleTraceOutput : public TDBXTraceOutput
{
	typedef TDBXTraceOutput inherited;
	
private:
	virtual void __fastcall Open();
	virtual void __fastcall WriteTraceln(System::UnicodeString Line);
public:
	/* TDBXTraceOutput.Create */ inline __fastcall TDBXConsoleTraceOutput() : TDBXTraceOutput() { }
	/* TDBXTraceOutput.Destroy */ inline __fastcall virtual ~TDBXConsoleTraceOutput() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXFileTraceOutput : public TDBXTraceOutput
{
	typedef TDBXTraceOutput inherited;
	
private:
	System::TextFile FTraceFile;
	virtual void __fastcall Open();
	virtual void __fastcall WriteTraceln(System::UnicodeString Line);
	
public:
	__fastcall virtual ~TDBXFileTraceOutput();
public:
	/* TDBXTraceOutput.Create */ inline __fastcall TDBXFileTraceOutput() : TDBXTraceOutput() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXTraceDriver : public Data::Dbxcommon::TDBXDriver
{
	typedef Data::Dbxcommon::TDBXDriver inherited;
	
private:
	__int64 FConnectionCount;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TDBXTraceOutput*>* FTraceOutputList;
	TDBXTraceOutput* __fastcall GetTraceOutput(System::UnicodeString Name);
	void __fastcall AddTraceOutput(TDBXTraceOutput* TraceOutput);
	void __fastcall ReleaseTraceOutput(TDBXTraceOutput* TraceOutput);
	void __fastcall SetTraceFlags(int TraceFlags);
	int __fastcall GetTraceFlags();
	void __fastcall SetTraceDriver(bool TraceDriver);
	bool __fastcall GetTraceDriver();
	void __fastcall SetTraceFile(System::UnicodeString TraceFile);
	System::UnicodeString __fastcall GetTraceFile();
	
protected:
	virtual System::UnicodeString __fastcall GetDriverName();
	virtual void __fastcall Close();
	
public:
	__fastcall virtual ~TDBXTraceDriver();
	__fastcall virtual TDBXTraceDriver(const Data::Dbxcommon::TDBXDriverDef &DriverDef)/* overload */;
	virtual Data::Dbxcommon::TDBXConnection* __fastcall CreateConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	virtual System::UnicodeString __fastcall GetDriverVersion();
	__property int TraceFlags = {read=GetTraceFlags, write=SetTraceFlags, nodefault};
	__property bool TraceDriver = {read=GetTraceDriver, write=SetTraceDriver, nodefault};
	__property System::UnicodeString TraceFile = {read=GetTraceFile, write=SetTraceFile};
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXTraceDriver()/* overload */ : Data::Dbxcommon::TDBXDriver() { }
	
};


class PASCALIMPLEMENTATION TDBXTraceConnection : public Data::Dbxdelegate::TDBXDelegateConnection
{
	typedef Data::Dbxdelegate::TDBXDelegateConnection inherited;
	
private:
	TDBXTraceFormatter* FFormatter;
	__int64 FConnectionId;
	System::UnicodeString FConnectionName;
	__int64 FCommandCount;
	Data::Dbxcommon::TDBXErrorEvent FOriginalLogError;
	TDBXTraceDriver* FTraceDriver;
	TDBXTraceOutput* FTraceOutput;
	void __fastcall Trace(int TraceFlags, System::UnicodeString Message);
	
protected:
	virtual Data::Dbxcommon::TDBXTransaction* __fastcall CreateAndBeginTransaction(const int Isolation);
	virtual void __fastcall Commit(Data::Dbxcommon::TDBXTransaction* const Transaction);
	virtual void __fastcall Rollback(Data::Dbxcommon::TDBXTransaction* const Transaction);
	virtual Data::Dbxcommon::TDBXDatabaseMetaData* __fastcall GetDatabaseMetaData();
	virtual Data::Dbxcommon::TDBXProperties* __fastcall GetConnectionProperties();
	virtual void __fastcall SetConnectionProperties(Data::Dbxcommon::TDBXProperties* const Value);
	virtual Data::Dbxcommon::TDBXTraceEvent __fastcall GetTraceInfoEvent();
	virtual void __fastcall SetTraceInfoEvent(const Data::Dbxcommon::TDBXTraceEvent TraceInfoEvent);
	virtual int __fastcall GetTraceFlags();
	virtual void __fastcall SetTraceFlags(const int TraceFlags);
	virtual Data::Dbxcommon::TDBXErrorEvent __fastcall GetErrorEvent();
	virtual void __fastcall SetErrorEvent(const Data::Dbxcommon::TDBXErrorEvent ErrorEvent);
	virtual Data::Dbxcommon::TDBXFormatter* __fastcall GetDBXFormatter();
	virtual void __fastcall SetDBXFormatter(Data::Dbxcommon::TDBXFormatter* const DBXFormatter);
	virtual bool __fastcall GetIsOpen();
	virtual Data::Dbxcommon::TDBXCommand* __fastcall DerivedCreateCommand()/* overload */;
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedGetCommandTypes(System::Classes::TStrings* const List);
	virtual void __fastcall DerivedGetCommands(const System::UnicodeString CommandType, System::Classes::TStrings* const List);
	virtual Data::Dbxcommon::TDBXCommand* __fastcall CreateMorphCommand(Data::Dbxcommon::TDBXCommand* MorphicCommand);
	virtual System::UnicodeString __fastcall GetProductVersion();
	virtual System::UnicodeString __fastcall GetProductName();
	virtual System::UnicodeString __fastcall GetConnectionProperty(const System::UnicodeString Name);
	void __fastcall LogError(Data::Dbxcommon::TDBXError* DBXError);
	System::UnicodeString __fastcall GetName();
	
public:
	__fastcall TDBXTraceConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder, TDBXTraceOutput* TraceOutput, TDBXTraceDriver* DRIVER, Data::Dbxcommon::TDBXConnection* Connection, __int64 ConnectionId);
	__fastcall virtual ~TDBXTraceConnection();
	virtual void __fastcall Open();
	virtual void __fastcall Close();
	virtual Data::Dbxcommon::TDBXTransaction* __fastcall BeginTransaction(int Isolation)/* overload */;
	virtual Data::Dbxcommon::TDBXTransaction* __fastcall BeginTransaction()/* overload */;
	virtual void __fastcall CommitFreeAndNil(Data::Dbxcommon::TDBXTransaction* &Transaction);
	virtual void __fastcall RollbackFreeAndNil(Data::Dbxcommon::TDBXTransaction* &Transaction);
	virtual void __fastcall RollbackIncompleteFreeAndNil(Data::Dbxcommon::TDBXTransaction* &Transaction);
	virtual Data::Dbxcommon::TDBXCommand* __fastcall CreateCommand()/* overload */;
	virtual System::UnicodeString __fastcall GetVendorProperty(const System::UnicodeString Name);
};


class PASCALIMPLEMENTATION TDBXTraceCommand : public Data::Dbxdelegate::TDBXDelegateCommand
{
	typedef Data::Dbxdelegate::TDBXDelegateCommand inherited;
	
private:
	TDBXTraceFormatter* FFormatter;
	__int64 FReaderCount;
	__int64 FConnectionId;
	__int64 FCommandId;
	System::UnicodeString FCommandName;
	System::UnicodeString FParametersName;
	void __fastcall Trace(int TraceFlags, System::UnicodeString Message);
	
protected:
	virtual void __fastcall SetCommandType(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetCommandType();
	virtual System::UnicodeString __fastcall GetText();
	virtual void __fastcall SetText(const System::UnicodeString Value);
	virtual void __fastcall SetRowSetSize(const __int64 Value);
	virtual void __fastcall SetMaxBlobSize(const __int64 MaxBlobSize);
	virtual __int64 __fastcall GetRowsAffected();
	virtual void __fastcall SetCommandTimeout(const int Timeout);
	virtual int __fastcall GetCommandTimeout();
	virtual Data::Dbxcommon::TDBXErrorEvent __fastcall GetErrorEvent();
	virtual Data::Dbxcommon::TDBXRow* __fastcall CreateParameterRow();
	virtual void __fastcall CreateParameters(Data::Dbxcommon::TDBXCommand* Command);
	virtual void __fastcall Open();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedGetNextReader();
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedClose();
	virtual void __fastcall DerivedPrepare();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedExecuteQuery();
	virtual void __fastcall DerivedExecuteUpdate();
	virtual void __fastcall DerivedClearParameters();
	System::UnicodeString __fastcall GetName();
	
public:
	__fastcall TDBXTraceCommand(Data::Dbxcommon::TDBXCommand* Command, Data::Dbxcommon::TDBXContext* DBXContext, TDBXTraceFormatter* Formatter, __int64 ConnectionId, __int64 CommandId);
	__fastcall virtual ~TDBXTraceCommand();
	virtual Data::Dbxcommon::TDBXParameter* __fastcall CreateParameter();
	virtual Data::Dbxcommon::TDBXParameterList* __fastcall GetParameters();
	virtual void __fastcall Prepare();
	virtual Data::Dbxcommon::TDBXReader* __fastcall ExecuteQuery();
	virtual void __fastcall ExecuteUpdate();
	virtual Data::Dbxcommon::TDBXReader* __fastcall GetNextReader();
};


class PASCALIMPLEMENTATION TDBXTraceParameterList : public Data::Dbxdelegate::TDBXDelegateParameterList
{
	typedef Data::Dbxdelegate::TDBXDelegateParameterList inherited;
	
protected:
	TDBXTraceFormatter* FFormatter;
	System::UnicodeString FParametersName;
	__int64 FConnectionId;
	__int64 FCommandId;
	System::UnicodeString __fastcall GetName();
	
protected:
	virtual Data::Dbxcommon::TDBXParameter* __fastcall GetParameterByOrdinal(const int Ordinal);
	virtual int __fastcall GetCount();
	
public:
	__fastcall TDBXTraceParameterList(Data::Dbxcommon::TDBXCommand* Command, Data::Dbxcommon::TDBXParameterList* Parameters, Data::Dbxcommon::TDBXContext* DBXContext, TDBXTraceFormatter* Formatter, System::UnicodeString ParametersName, __int64 ConnectionId, __int64 CommandId);
	virtual void __fastcall SetCount(const int Count);
	virtual void __fastcall AddParameter(Data::Dbxcommon::TDBXParameter* Parameter);
	virtual void __fastcall SetParameter(const int Ordinal, Data::Dbxcommon::TDBXParameter* const Parameter);
	virtual void __fastcall InsertParameter(int Ordinal, Data::Dbxcommon::TDBXParameter* Parameter);
	virtual void __fastcall RemoveParameter(int Ordinal)/* overload */;
	virtual void __fastcall RemoveParameter(Data::Dbxcommon::TDBXParameter* Parameter)/* overload */;
	virtual void __fastcall ClearParameters()/* overload */;
	virtual void __fastcall RemoveParameters();
	virtual int __fastcall GetOrdinal(const System::UnicodeString Name);
public:
	/* TDBXDelegateParameterList.Destroy */ inline __fastcall virtual ~TDBXTraceParameterList() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTraceWritableValue : public Data::Dbxdelegate::TDBXDelegateWritableValue
{
	typedef Data::Dbxdelegate::TDBXDelegateWritableValue inherited;
	
private:
	TDBXTraceFormatter* FFormatter;
	System::UnicodeString FValueName;
	System::UnicodeString FValueDisplayName;
	int FLastOrdinal;
	System::UnicodeString __fastcall GetValueDisplayName();
	
protected:
	__fastcall TDBXTraceWritableValue(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXValueType* ValueType, Data::Dbxcommon::TDBXWritableValue* Value, TDBXTraceFormatter* Formatter, System::UnicodeString ValueName)/* overload */;
	virtual Data::Dbxcommon::TDBXValue* __fastcall GetNonDelegate();
	virtual bool __fastcall GetAsBoolean();
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual __int64 __fastcall GetAsInt64();
	virtual System::UnicodeString __fastcall GetAsString();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual Data::Dbxcommon::TDBXDate __fastcall GetAsDate();
	virtual Data::Dbxcommon::TDBXTime __fastcall GetAsTime();
	virtual Data::Sqltimst::TSQLTimeStamp __fastcall GetAsTimeStamp();
	virtual void __fastcall SetPendingValue();
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetAsDate(const Data::Dbxcommon::TDBXDate Value);
	virtual void __fastcall SetAsTime(const Data::Dbxcommon::TDBXTime Value);
	virtual void __fastcall SetAsTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	
public:
	virtual bool __fastcall IsNull();
	virtual __int64 __fastcall GetValueSize();
	virtual System::AnsiString __fastcall GetAnsiString();
	virtual Data::Dbxcommon::TDBXDate __fastcall GetDate();
	virtual bool __fastcall GetBoolean()/* overload */;
	virtual Data::Dbxcommon::TDBXTime __fastcall GetTime();
	virtual System::UnicodeString __fastcall GetWideString()/* overload */;
	virtual System::UnicodeString __fastcall GetString()/* overload */;
	virtual System::Byte __fastcall GetUInt8()/* overload */;
	virtual System::Int8 __fastcall GetInt8()/* overload */;
	virtual System::Word __fastcall GetUInt16()/* overload */;
	virtual short __fastcall GetInt16()/* overload */;
	virtual int __fastcall GetInt32()/* overload */;
	virtual __int64 __fastcall GetInt64()/* overload */;
	virtual float __fastcall GetSingle();
	virtual double __fastcall GetDouble();
	virtual __int64 __fastcall GetBytes(__int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length)/* overload */;
	virtual Data::Sqltimst::TSQLTimeStamp __fastcall GetTimeStamp();
	virtual Data::Sqltimst::TSQLTimeStampOffset __fastcall GetTimeStampOffset();
	virtual Data::Fmtbcd::TBcd __fastcall GetBcd();
	virtual Data::Dbxcommon::TDBXReader* __fastcall GetDBXReader(bool AInstanceOwner)/* overload */;
	virtual Data::Dbxcommon::TDBXConnection* __fastcall GetDBXConnection();
	virtual System::Classes::TStream* __fastcall GetStream(bool AInstanceOwner)/* overload */;
	virtual System::UnicodeString __fastcall GetWideString(System::UnicodeString defaultValue)/* overload */;
	virtual bool __fastcall GetBoolean(bool defaultValue)/* overload */;
	virtual System::Byte __fastcall GetUInt8(System::Byte defaultValue)/* overload */;
	virtual System::Int8 __fastcall GetInt8(System::Int8 defaultValue)/* overload */;
	virtual System::Word __fastcall GetUInt16(System::Word defaultValue)/* overload */;
	virtual short __fastcall GetInt16(short defaultValue)/* overload */;
	virtual int __fastcall GetInt32(int defaultValue)/* overload */;
	virtual __int64 __fastcall GetInt64(__int64 defaultValue)/* overload */;
	virtual bool __fastcall EqualsValue(Data::Dbxcommon::TDBXValue* Other);
	virtual void __fastcall SetNull();
	virtual void __fastcall SetTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetTimeStampOffset(const Data::Sqltimst::TSQLTimeStampOffset &Value);
	virtual void __fastcall SetBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetAnsiString(const System::AnsiString Value);
	virtual void __fastcall SetBoolean(const bool Value);
	virtual void __fastcall SetDate(const Data::Dbxcommon::TDBXDate Value);
	virtual void __fastcall SetTime(const Data::Dbxcommon::TDBXTime Value);
	virtual void __fastcall SetWideString(const System::UnicodeString Value);
	virtual void __fastcall SetString(const System::UnicodeString Value);
	virtual void __fastcall SetUInt8(const System::Byte Value);
	virtual void __fastcall SetInt8(const System::Int8 Value);
	virtual void __fastcall SetUInt16(const System::Word Value);
	virtual void __fastcall SetInt16(const short Value);
	virtual void __fastcall SetInt32(const int Value);
	virtual void __fastcall SetInt64(const __int64 Value);
	virtual void __fastcall SetSingle(const float Value);
	virtual void __fastcall SetDouble(const double Value);
	virtual void __fastcall SetStaticBytes(__int64 Offset, const System::Byte *Buffer, const int Buffer_High, __int64 BufferOffset, __int64 Length);
	virtual void __fastcall SetDynamicBytes(__int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
	virtual void __fastcall SetDBXReader(Data::Dbxcommon::TDBXReader* const Value, const bool AInstanceOwner)/* overload */;
	virtual void __fastcall SetStream(System::Classes::TStream* const Stream, const bool AInstanceOwner);
	virtual void __fastcall SetDBXConnection(Data::Dbxcommon::TDBXConnection* const Value);
	virtual void __fastcall SetValue(Data::Dbxcommon::TDBXValue* const Value);
protected:
	/* TDBXDelegateWritableValue.Create */ inline __fastcall TDBXTraceWritableValue(Data::Dbxcommon::TDBXValueType* ValueType, Data::Dbxcommon::TDBXWritableValue* Value)/* overload */ : Data::Dbxdelegate::TDBXDelegateWritableValue(ValueType, Value) { }
	
public:
	/* TDBXDelegateWritableValue.Destroy */ inline __fastcall virtual ~TDBXTraceWritableValue() { }
	
	/* Hoisted overloads: */
	
public:
	inline Data::Dbxcommon::TDBXReader* __fastcall  GetDBXReader(){ return Data::Dbxcommon::TDBXValue::GetDBXReader(); }
	inline System::Classes::TStream* __fastcall  GetStream(){ return Data::Dbxcommon::TDBXValue::GetStream(); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXTraceParameter : public Data::Dbxdelegate::TDBXDelegateParameter
{
	typedef Data::Dbxdelegate::TDBXDelegateParameter inherited;
	
private:
	TDBXTraceWritableValue* FTraceValue;
	TDBXTraceFormatter* FFormatter;
	System::UnicodeString FParameterName;
	
protected:
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetValue();
	
public:
	__fastcall TDBXTraceParameter(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXParameter* Parameter, TDBXTraceFormatter* Formatter, System::UnicodeString ValueName);
	__fastcall virtual ~TDBXTraceParameter();
	virtual System::TObject* __fastcall Clone();
};


class PASCALIMPLEMENTATION TDBXTraceReader : public Data::Dbxdelegate::TDBXDelegateReader
{
	typedef Data::Dbxdelegate::TDBXDelegateReader inherited;
	
private:
	TDBXTraceFormatter* FFormatter;
	__int64 FNextCount;
	__int64 FConnectionId;
	__int64 FCommandId;
	__int64 FReaderId;
	System::UnicodeString FReaderName;
	bool FClosed;
	void __fastcall PrintColumns();
	
public:
	__fastcall TDBXTraceReader(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXReader* Reader, TDBXTraceFormatter* Formatter, __int64 ConnectionId, __int64 CommandId, __int64 ReaderId);
	__fastcall virtual ~TDBXTraceReader();
	virtual bool __fastcall Next();
};


enum DECLSPEC_DENUM TTraceFlag : unsigned char { PARAMETER, ERROR_, EXECUTE, COMMAND, CONNECT, TRANSACT, BLOB, MISC, VENDOR, READER, DRIVER_LOAD, METADATA };

typedef System::Set<TTraceFlag, TTraceFlag::PARAMETER, TTraceFlag::METADATA> TTraceFlags;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTraceProperties : public Data::Dbxcommon::TDBXProperties
{
	typedef Data::Dbxcommon::TDBXProperties inherited;
	
private:
	#define TDBXTraceProperties_StrTraceFile u"TraceFile"
	
	#define TDBXTraceProperties_StrTraceFlags u"TraceFlags"
	
	#define TDBXTraceProperties_StrTraceDriver u"TraceDriver"
	
	System::UnicodeString __fastcall TraceFlagsToStr(TTraceFlags Flags);
	TTraceFlags __fastcall StrtoTraceFlags(System::UnicodeString Value);
	System::UnicodeString __fastcall GetTraceFile();
	TTraceFlags __fastcall GetTraceFlags();
	bool __fastcall GetTraceDriver();
	void __fastcall SetTraceFile(const System::UnicodeString Value);
	void __fastcall SetTraceFlags(const TTraceFlags Value);
	void __fastcall SetTraceDriver(const bool Value);
	
public:
	__fastcall virtual TDBXTraceProperties(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */;
	
__published:
	__property System::UnicodeString TraceFile = {read=GetTraceFile, write=SetTraceFile};
	__property TTraceFlags TraceFlags = {read=GetTraceFlags, write=SetTraceFlags, nodefault};
	__property bool TraceDriver = {read=GetTraceDriver, write=SetTraceDriver, nodefault};
public:
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXTraceProperties()/* overload */ : Data::Dbxcommon::TDBXProperties() { }
	/* TDBXProperties.Destroy */ inline __fastcall virtual ~TDBXTraceProperties() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define sDriverName u"DBXTrace"
#define sConsoleOutput u":con"
}	/* namespace Dbxtrace */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXTRACE)
using namespace Data::Dbxtrace;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxtraceHPP
