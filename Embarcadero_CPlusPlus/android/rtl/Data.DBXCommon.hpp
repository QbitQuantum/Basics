// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXCommon.pas' rev: 34.00 (Android)

#ifndef Data_DbxcommonHPP
#define Data_DbxcommonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.Classes.hpp>
#include <System.IniFiles.hpp>
#include <System.SysUtils.hpp>
#include <System.JSON.hpp>
#include <System.JSON.Readers.hpp>
#include <System.JSON.Writers.hpp>
#include <Data.DBCommonTypes.hpp>
#include <Data.FmtBcd.hpp>
#include <Data.SqlTimSt.hpp>
#include <Data.DBXClassRegistry.hpp>
#include <Data.DBXJSON.hpp>
#include <System.SyncObjs.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxcommon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSubDataTypes;
class DELPHICLASS TDBXDataTypes;
class DELPHICLASS TDBXErrorCodes;
class DELPHICLASS TDBXIsolations;
class DELPHICLASS TDBXParameterDirections;
class DELPHICLASS TDBXValueTypeFlags;
class DELPHICLASS TDBXTraceFlags;
class DELPHICLASS TDBXTraceLevels;
class DELPHICLASS TDBXPropertyNames;
class DELPHICLASS TDBXCommandTypes;
class DELPHICLASS TDBXMetaDataCommands;
class DELPHICLASS TDBXMetaDataKeyword;
class DELPHICLASS TDBXMetaDatabaseColumnNames;
class DELPHICLASS TDBXMetaDataTableTypes;
class DELPHICLASS TDBXMetaDataProcedureTypes;
struct TDBXX509_Filetypes;
class DELPHICLASS TDBXError;
struct TDBXTraceInfo;
class DELPHICLASS TEventsCollection;
class DELPHICLASS TNameValuesStringList;
class DELPHICLASS TDictionaryStringList;
class DELPHICLASS TDBXProperties;
class DELPHICLASS TDBXConnectionFactory;
class DELPHICLASS TDBXIniFileConnectionFactory;
class DELPHICLASS TDBXMemoryConnectionFactory;
class DELPHICLASS TDBXCreateCommand;
struct TDBXDriverDef;
class DELPHICLASS TDBXDriver;
class DELPHICLASS TDBXStateItem;
class DELPHICLASS TDBXStateItemList;
class DELPHICLASS TDBXConnection;
class DELPHICLASS TDBXTransaction;
class DELPHICLASS TDBXDatabaseMetaData;
class DELPHICLASS TDBXCommand;
class DELPHICLASS TDBXMorphicCommand;
class DELPHICLASS TDBXValueList;
class DELPHICLASS TDBXWritableValueList;
class DELPHICLASS TDBXReader;
class DELPHICLASS TDBXValueType;
class DELPHICLASS TDBXParameter;
class DELPHICLASS TDBXParameterList;
class DELPHICLASS TDBXJSONStream;
class DELPHICLASS TDBXValue;
class DELPHICLASS TDBXWritableValue;
class DELPHICLASS TDBXNullValue;
class DELPHICLASS TDBXAnsiStringValue;
class DELPHICLASS TDBXDateValue;
class DELPHICLASS TDBXCursorValue;
class DELPHICLASS TDBXBooleanValue;
class DELPHICLASS TDBXTimeValue;
class DELPHICLASS TDBXWideStringValue;
class DELPHICLASS TDBXInt8Value;
class DELPHICLASS TDBXUInt8Value;
class DELPHICLASS TDBXInt16Value;
class DELPHICLASS TDBXUInt16Value;
class DELPHICLASS TDBXInt32Value;
class DELPHICLASS TDBXInt64Value;
class DELPHICLASS TDBXDoubleValue;
class DELPHICLASS TDBXSingleValue;
class DELPHICLASS TDBXBcdValue;
class DELPHICLASS TDBXByteArrayValue;
class DELPHICLASS TDBXStreamReader;
class DELPHICLASS TDBXLookAheadStreamReader;
class DELPHICLASS TDBXByteStreamReader;
class DELPHICLASS TDBXStreamValue;
class DELPHICLASS TDBXWideCharsValue;
class DELPHICLASS TDBXStringValue;
class DELPHICLASS TDBXAnsiCharsValue;
class DELPHICLASS TDBXTimeStampValue;
class DELPHICLASS TDBXTimeStampOffsetValue;
class DELPHICLASS TDBXReaderValue;
class DELPHICLASS TDBXConnectionValue;
class DELPHICLASS TDBXContext;
class DELPHICLASS TDBXByteReader;
class DELPHICLASS TDBXReaderByteReader;
class DELPHICLASS TDBXValueTypeList;
class DELPHICLASS TDBXDriverHelp;
class DELPHICLASS TDBXDriverLoader;
class DELPHICLASS TDBXDriverRegistry;
class DELPHICLASS TDBXDelegateDriver;
class DELPHICLASS TDBXDelegateItem;
class DELPHICLASS TDBXPropertiesItem;
class DELPHICLASS TDBXConnectionBuilder;
class DELPHICLASS TDBXAnsiMemoValue;
class DELPHICLASS TDBXWideMemoValue;
class DELPHICLASS TDBXRow;
class DELPHICLASS TDBXCommandFactory;
class DELPHICLASS TDBXFormatter;
class DELPHICLASS TDBXStream;
class DELPHICLASS TDBXStreamReaderStream;
class DELPHICLASS TDBXBytesStream;
class DELPHICLASS TDBXJSONValue;
class DELPHICLASS TDBXCallbackValue;
class DELPHICLASS TDBXCommunicationLayer;
__interface DELPHIINTERFACE TDBXScheduleEvent;
typedef System::DelphiInterface<TDBXScheduleEvent> _di_TDBXScheduleEvent;
class DELPHICLASS TDBXScheduler;
class DELPHICLASS TPrincipal;
class DELPHICLASS TX500Principal;
class DELPHICLASS ECertificateExpiredException;
class DELPHICLASS ECertificateNotYetValidException;
class DELPHICLASS ECertificateParsingException;
class DELPHICLASS TKey;
class DELPHICLASS TPublicKey;
class DELPHICLASS TCertificate;
class DELPHICLASS TX509Certificate;
class DELPHICLASS TRequestCommandHandler;
class DELPHICLASS TResultCommandHandler;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TValidateCertificate)(System::TObject* Owner, TX509Certificate* Certificate, const int ADepth, bool &Ok);

typedef void __fastcall (__closure *TValidateCertificateErr)(System::TObject* Owner, TX509Certificate* Certificate, const int ADepth, const int AError, bool &Ok);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXSubDataTypes : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 MoneySubType = System::Int8(0x15);
	
	static constexpr System::Int8 MemoSubType = System::Int8(0x16);
	
	static constexpr System::Int8 BinarySubType = System::Int8(0x17);
	
	static constexpr System::Int8 WideMemoSubType = System::Int8(0x20);
	
	static constexpr System::Int8 HMemoSubType = System::Int8(0x21);
	
	static constexpr System::Int8 HBinarySubType = System::Int8(0x22);
	
	static constexpr System::Int8 BFileSubType = System::Int8(0x24);
	
	static constexpr System::Int8 FixedSubType = System::Int8(0x1f);
	
	static constexpr System::Int8 AutoIncSubType = System::Int8(0x1d);
	
	static constexpr System::Int8 AdtNestedTableSubType = System::Int8(0x23);
	
	static constexpr System::Int8 AdtDateSubType = System::Int8(0x25);
	
	static constexpr System::Int8 OracleTimeStampSubType = System::Int8(0x26);
	
	static constexpr System::Int8 OracleIntervalSubType = System::Int8(0x27);
	
	static constexpr System::Int8 UserSubType = System::Int8(0x28);
	
	static constexpr System::Int8 JSONStreamSubType = System::Int8(0x29);
	
public:
	/* TObject.Create */ inline __fastcall TDBXSubDataTypes() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSubDataTypes() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDataTypes : public TDBXSubDataTypes
{
	typedef TDBXSubDataTypes inherited;
	
public:
	static constexpr System::Int8 UnknownType = System::Int8(0x0);
	
	static constexpr System::Int8 AnsiStringType = System::Int8(0x1);
	
	static constexpr System::Int8 DateType = System::Int8(0x2);
	
	static constexpr System::Int8 BlobType = System::Int8(0x3);
	
	static constexpr System::Int8 BooleanType = System::Int8(0x4);
	
	static constexpr System::Int8 Int16Type = System::Int8(0x5);
	
	static constexpr System::Int8 Int32Type = System::Int8(0x6);
	
	static constexpr System::Int8 DoubleType = System::Int8(0x7);
	
	static constexpr System::Int8 BcdType = System::Int8(0x8);
	
	static constexpr System::Int8 BytesType = System::Int8(0x9);
	
	static constexpr System::Int8 TimeType = System::Int8(0xa);
	
	static constexpr System::Int8 DateTimeType = System::Int8(0xb);
	
	static constexpr System::Int8 UInt16Type = System::Int8(0xc);
	
	static constexpr System::Int8 UInt32Type = System::Int8(0xd);
	
	static constexpr System::Int8 VarBytesType = System::Int8(0xf);
	
	static constexpr System::Int8 CursorType = System::Int8(0x11);
	
	static constexpr System::Int8 Int64Type = System::Int8(0x12);
	
	static constexpr System::Int8 UInt64Type = System::Int8(0x13);
	
	static constexpr System::Int8 AdtType = System::Int8(0x14);
	
	static constexpr System::Int8 ArrayType = System::Int8(0x15);
	
	static constexpr System::Int8 RefType = System::Int8(0x16);
	
	static constexpr System::Int8 TableType = System::Int8(0x17);
	
	static constexpr System::Int8 TimeStampType = System::Int8(0x18);
	
	static constexpr System::Int8 CurrencyType = System::Int8(0x19);
	
	static constexpr System::Int8 WideStringType = System::Int8(0x1a);
	
	static constexpr System::Int8 SingleType = System::Int8(0x1b);
	
	static constexpr System::Int8 Int8Type = System::Int8(0x1c);
	
	static constexpr System::Int8 UInt8Type = System::Int8(0x1d);
	
	static constexpr System::Int8 ObjectType = System::Int8(0x1e);
	
	static constexpr System::Int8 CharArrayType = System::Int8(0x1f);
	
	static constexpr System::Int8 IntervalType = System::Int8(0x20);
	
	static constexpr System::Int8 BinaryBlobType = System::Int8(0x21);
	
	static constexpr System::Int8 DBXConnectionType = System::Int8(0x22);
	
	static constexpr System::Int8 VariantType = System::Int8(0x23);
	
	static constexpr System::Int8 TimeStampOffsetType = System::Int8(0x24);
	
	static constexpr System::Int8 JsonValueType = System::Int8(0x25);
	
	static constexpr System::Int8 CallbackType = System::Int8(0x26);
	
	static constexpr System::Int8 MaxBaseTypes = System::Int8(0x27);
	
public:
	/* TObject.Create */ inline __fastcall TDBXDataTypes() : TDBXSubDataTypes() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDataTypes() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef int TDBXType;

_DECLARE_ARITH_TYPE_ALIAS(int, TDBXDate);

_DECLARE_ARITH_TYPE_ALIAS(int, TDBXTime);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXErrorCodes : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 None = System::Int8(0x0);
	
	static constexpr System::Int8 Warning = System::Int8(0x1);
	
	static constexpr System::Int8 NoMemory = System::Int8(0x2);
	
	static constexpr System::Int8 UnsupportedFieldType = System::Int8(0x3);
	
	static constexpr System::Int8 InvalidHandle = System::Int8(0x4);
	
	static constexpr System::Int8 NotSupported = System::Int8(0x5);
	
	static constexpr System::Int8 InvalidTime = System::Int8(0x6);
	
	static constexpr System::Int8 InvalidType = System::Int8(0x7);
	
	static constexpr System::Int8 InvalidOrdinal = System::Int8(0x8);
	
	static constexpr System::Int8 InvalidParameter = System::Int8(0x9);
	
	static constexpr System::Int8 EoF = System::Int8(0xa);
	
	static constexpr System::Int8 ParameterNotSet = System::Int8(0xb);
	
	static constexpr System::Int8 InvalidUserOrPassword = System::Int8(0xc);
	
	static constexpr System::Int8 InvalidPrecision = System::Int8(0xd);
	
	static constexpr System::Int8 InvalidLength = System::Int8(0xe);
	
	static constexpr System::Int8 InvalidIsolationLevel = System::Int8(0xf);
	
	static constexpr System::Int8 InvalidTransactionId = System::Int8(0x10);
	
	static constexpr System::Int8 DuplicateTransactionId = System::Int8(0x11);
	
	static constexpr System::Int8 DriverRestricted = System::Int8(0x12);
	
	static constexpr System::Int8 TransactionActive = System::Int8(0x13);
	
	static constexpr System::Int8 MultipleTransactionNotEnabled = System::Int8(0x14);
	
	static constexpr System::Int8 ConnectionFailed = System::Int8(0x15);
	
	static constexpr System::Int8 DriverInitFailed = System::Int8(0x16);
	
	static constexpr System::Int8 OptimisticLockFailed = System::Int8(0x17);
	
	static constexpr System::Int8 InvalidReference = System::Int8(0x18);
	
	static constexpr System::Int8 NoTable = System::Int8(0x19);
	
	static constexpr System::Int8 MissingParameterMarker = System::Int8(0x1a);
	
	static constexpr System::Int8 NotImplemented = System::Int8(0x1b);
	
	static constexpr System::Int8 DriverIncompatible = System::Int8(0x1c);
	
	static constexpr System::Int8 InvalidArgument = System::Int8(0x1d);
	
	static constexpr System::Int8 InvalidOperation = System::Int8(0x1e);
	
	static constexpr System::Int8 UnrecognizedCommandType = System::Int8(0x1f);
	
	static constexpr System::Int8 CallbackError = System::Int8(0x20);
	
	static constexpr System::Int8 SchemaNameUnspecified = System::Int8(0x21);
	
	static constexpr System::Int8 DatabaseUnspecified = System::Int8(0x22);
	
	static constexpr System::Int8 LibraryNameUnspecified = System::Int8(0x23);
	
	static constexpr System::Int8 GetDriverFuncUnspecified = System::Int8(0x24);
	
	static constexpr System::Int8 VendorLibUnspecified = System::Int8(0x25);
	
	static constexpr System::Int8 NoData = System::Int8(0x64);
	
	static constexpr System::Int8 MaxCommonErrors = System::Int8(0x64);
	
	static constexpr System::Int8 VendorError = System::Int8(0x65);
	
	static constexpr System::Int8 ServerClassExists = System::Int8(0x66);
	
	static constexpr System::Int8 ServerMethodExists = System::Int8(0x67);
	
	static constexpr System::Int8 ServerClassMissing = System::Int8(0x68);
	
	static constexpr System::Int8 ServerMethodMissing = System::Int8(0x69);
	
	static constexpr System::Int8 ServerMethodFailed = System::Int8(0x70);
	
	static constexpr System::Int8 AuthorizationFailed = System::Int8(0x71);
	
public:
	/* TObject.Create */ inline __fastcall TDBXErrorCodes() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXErrorCodes() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
typedef int TDBXErrorCode;
#else /* __aarch64__ */
typedef long TDBXErrorCode;
#endif /* __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXIsolations : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 ReadCommitted = System::Int8(0x0);
	
	static constexpr System::Int8 RepeatableRead = System::Int8(0x1);
	
	static constexpr System::Int8 DirtyRead = System::Int8(0x2);
	
	static constexpr System::Int8 Serializable = System::Int8(0x3);
	
	static constexpr System::Int8 SnapShot = System::Int8(0x4);
	
public:
	/* TObject.Create */ inline __fastcall TDBXIsolations() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXIsolations() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef int TDBXIsolation;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXParameterDirections : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 Unknown = System::Int8(0x0);
	
	static constexpr System::Int8 InParameter = System::Int8(0x1);
	
	static constexpr System::Int8 OutParameter = System::Int8(0x2);
	
	static constexpr System::Int8 InOutParameter = System::Int8(0x3);
	
	static constexpr System::Int8 ReturnParameter = System::Int8(0x4);
	
public:
	/* TObject.Create */ inline __fastcall TDBXParameterDirections() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXParameterDirections() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef int TDBXParameterDirection;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXValueTypeFlags : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 Nullable = System::Int8(0x1);
	
	static constexpr System::Int8 ReadOnly = System::Int8(0x2);
	
	static constexpr System::Int8 Searchable = System::Int8(0x4);
	
	static constexpr System::Int8 AutoIncrement = System::Int8(0x8);
	
	static constexpr System::Int8 ReadOnlyType = System::Int8(0x20);
	
	static constexpr System::Int8 Hidden = System::Int8(0x40);
	
	static constexpr System::Byte ExtendedType = System::Byte(0x80);
	
	static constexpr System::Word ValueParameter = System::Word(0x100);
	
	static constexpr System::Word Literal = System::Word(0x200);
	
public:
	/* TObject.Create */ inline __fastcall TDBXValueTypeFlags() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXValueTypeFlags() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTraceFlags : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 None = System::Int8(0x0);
	
	static constexpr System::Int8 Prepare = System::Int8(0x1);
	
	static constexpr System::Int8 Execute = System::Int8(0x2);
	
	static constexpr System::Int8 Error = System::Int8(0x4);
	
	static constexpr System::Int8 Command = System::Int8(0x8);
	
	static constexpr System::Int8 Connect = System::Int8(0x10);
	
	static constexpr System::Int8 Transact = System::Int8(0x20);
	
	static constexpr System::Int8 Blob = System::Int8(0x40);
	
	static constexpr System::Byte Misc = System::Byte(0x80);
	
	static constexpr System::Word Vendor = System::Word(0x100);
	
	static constexpr System::Word Parameter = System::Word(0x200);
	
	static constexpr System::Word Reader = System::Word(0x400);
	
	static constexpr System::Word DriverLoad = System::Word(0x800);
	
	static constexpr System::Word MetaData = System::Word(0x1000);
	
	static constexpr System::Word Driver = System::Word(0x2000);
	
	static constexpr System::Word Custom = System::Word(0x4000);
	
public:
	/* TObject.Create */ inline __fastcall TDBXTraceFlags() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTraceFlags() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef int TDBXTraceFlag;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTraceLevels : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 None = System::Int8(0x0);
	
	static constexpr System::Int8 Debug = System::Int8(0x1);
	
	static constexpr System::Int8 Info = System::Int8(0x2);
	
	static constexpr System::Int8 Warn = System::Int8(0x3);
	
	static constexpr System::Int8 Error = System::Int8(0x4);
	
	static constexpr System::Int8 Fatal = System::Int8(0x5);
	
	static constexpr System::Int8 Highest = System::Int8(0x5);
	
public:
	/* TObject.Create */ inline __fastcall TDBXTraceLevels() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTraceLevels() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef int TDBXTracelevel;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXPropertyNames : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPropertyNames_ConnectionName u"ConnectionName"
	
	#define TDBXPropertyNames_InstalledDrivers u"Installed Drivers"
	
	#define TDBXPropertyNames_GetDriverFunc u"GetDriverFunc"
	
	#define TDBXPropertyNames_VendorLib u"VendorLib"
	
	#define TDBXPropertyNames_VendorLibWin64 u"VendorLibWin64"
	
	#define TDBXPropertyNames_VendorLibOsx u"VendorLibOsx"
	
	#define TDBXPropertyNames_ErrorResourceFile u"ErrorResourceFile"
	
	#define TDBXPropertyNames_LibraryName u"LibraryName"
	
	#define TDBXPropertyNames_LibraryNameOsx u"LibraryNameOsx"
	
	#define TDBXPropertyNames_DriverName u"DriverName"
	
	#define TDBXPropertyNames_HostName u"HostName"
	
	#define TDBXPropertyNames_DBHostName u"DBHostName"
	
	#define TDBXPropertyNames_Port u"Port"
	
	#define TDBXPropertyNames_Database u"Database"
	
	#define TDBXPropertyNames_UserName u"User_Name"
	
	#define TDBXPropertyNames_Password u"Password"
	
	#define TDBXPropertyNames_ConnectionString u"ConnectionString"
	
	#define TDBXPropertyNames_Role u"Role"
	
	#define TDBXPropertyNames_IsolationLevel u"IsolationLevel"
	
	#define TDBXPropertyNames_MaxBlobSize u"MaxBlobSize"
	
	#define TDBXPropertyNames_RowSetSize u"RowSetSize"
	
	#define TDBXPropertyNames_DelegateConnection u"DelegateConnection"
	
	#define TDBXPropertyNames_DriverUnit u"DriverUnit"
	
	#define TDBXPropertyNames_DriverPackage u"DriverPackage"
	
	#define TDBXPropertyNames_DriverAssembly u"DriverAssembly"
	
	#define TDBXPropertyNames_DriverPackageLoader u"DriverPackageLoader"
	
	#define TDBXPropertyNames_DriverAssemblyLoader u"DriverAssemblyLoader"
	
	#define TDBXPropertyNames_DelegateDriver u"DelegateDriver"
	
	#define TDBXPropertyNames_SchemaOverride u"SchemaOverride"
	
	#define TDBXPropertyNames_MetaDataPackageLoader u"MetaDataPackageLoader"
	
	#define TDBXPropertyNames_MetaDataAssemblyLoader u"MetaDataAssemblyLoader"
	
	#define TDBXPropertyNames_ProductVersion u"ProductVersion"
	
	#define TDBXPropertyNames_ProductName u"ProductName"
	
	#define TDBXPropertyNames_ServerConnection u"ServerConnection"
	
	#define TDBXPropertyNames_IPImplementationID u"IPImplementationID"
	
	#define TDBXPropertyNames_SupportsParameterMetadata u"SupportsParameterMetaData"
	
	#define TDBXPropertyNames_ConnectTimeout u"ConnectTimeout"
	
	#define TDBXPropertyNames_BufferKBSize u"BufferKBSize"
	
	#define TDBXPropertyNames_AutoUnloadDriver u"AutoUnloadDriver"
	
	#define TDBXPropertyNames_CommunicationProtocol u"CommunicationProtocol"
	
	#define TDBXPropertyNames_CommunicationIPVersion u"CommunicationIPVersion"
	
	#define TDBXPropertyNames_URLPath u"URLPath"
	
	#define TDBXPropertyNames_DSAuthenticationUser u"DSAuthenticationUser"
	
	#define TDBXPropertyNames_DSAuthenticationPassword u"DSAuthenticationPassword"
	
	#define TDBXPropertyNames_DSAuthenticationScheme u"DSAuthenticationScheme"
	
	#define TDBXPropertyNames_CommunicationTimeout u"CommunicationTimeout"
	
	#define TDBXPropertyNames_Filters u"Filters"
	
	#define TDBXPropertyNames_DatasnapContext u"DatasnapContext"
	
	#define TDBXPropertyNames_DSProxyHost u"DSProxyHost"
	
	#define TDBXPropertyNames_DSProxyPort u"DSProxyPort"
	
	#define TDBXPropertyNames_DSProxyUsername u"DSProxyUsername"
	
	#define TDBXPropertyNames_DSProxyPassword u"DSProxyPassword"
	
	#define TDBXPropertyNames_DisplayDriverName u"DisplayDriverName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPropertyNames() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPropertyNames() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXCommandTypes : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXCommandTypes_DbxSQL u"Dbx.SQL"
	
	#define TDBXCommandTypes_DbxStoredProcedure u"Dbx.StoredProcedure"
	
	#define TDBXCommandTypes_DbxTable u"Dbx.Table"
	
	#define TDBXCommandTypes_DbxMetaData u"Dbx.MetaData"
	
	#define TDBXCommandTypes_DbxCommand u"Dbx.Command"
	
	#define TDBXCommandTypes_DbxPool u"Dbx.Pool"
	
	#define TDBXCommandTypes_DSServerMethod u"DataSnap.ServerMethod"
	
public:
	/* TObject.Create */ inline __fastcall TDBXCommandTypes() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXCommandTypes() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDataCommands : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXMetaDataCommands_GetDatabase u"GetDatabase"
	
	#define TDBXMetaDataCommands_GetDataTypes u"GetDataTypes"
	
	#define TDBXMetaDataCommands_GetTables u"GetTables"
	
	#define TDBXMetaDataCommands_GetColumns u"GetColumns"
	
	#define TDBXMetaDataCommands_GetForeignKeys u"GetForeignKeys"
	
	#define TDBXMetaDataCommands_GetForeignKeyColumns u"GetForeignKeyColumns"
	
	#define TDBXMetaDataCommands_GetIndexes u"GetIndexes"
	
	#define TDBXMetaDataCommands_GetIndexColumns u"GetIndexColumns"
	
	#define TDBXMetaDataCommands_GetPackages u"GetPackages"
	
	#define TDBXMetaDataCommands_GetProcedures u"GetProcedures"
	
	#define TDBXMetaDataCommands_GetProcedureParameters u"GetProcedureParameters"
	
	#define TDBXMetaDataCommands_GetUsers u"GetUsers"
	
	#define TDBXMetaDataCommands_GetViews u"GetViews"
	
	#define TDBXMetaDataCommands_GetSynonyms u"GetSynonyms"
	
	#define TDBXMetaDataCommands_GetCatalogs u"GetCatalogs"
	
	#define TDBXMetaDataCommands_GetSchemas u"GetSchemas"
	
	#define TDBXMetaDataCommands_GetProcedureSources u"GetProcedureSources"
	
	#define TDBXMetaDataCommands_GetPackageProcedures u"GetPackageProcedures"
	
	#define TDBXMetaDataCommands_GetPackageProcedureParameters u"GetPackageProcedureParameters"
	
	#define TDBXMetaDataCommands_GetPackageSources u"GetPackageSources"
	
	#define TDBXMetaDataCommands_GetRoles u"GetRoles"
	
	#define TDBXMetaDataCommands_GetReservedWords u"GetReservedWords"
	
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataCommands() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataCommands() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDataKeyword : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXMetaDataKeyword_PrimaryKey u"PrimaryKey"
	
	#define TDBXMetaDataKeyword_ForeignKey u"ForeignKey"
	
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataKeyword() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataKeyword() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDatabaseColumnNames : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXMetaDatabaseColumnNames_QuoteChar u"QuoteChar"
	
	#define TDBXMetaDatabaseColumnNames_ProcedureQuoteChar u"ProcedureQuoteChar"
	
	#define TDBXMetaDatabaseColumnNames_MaxCommands u"MaxCommands"
	
	#define TDBXMetaDatabaseColumnNames_SupportsTransactions u"SupportsTransactions"
	
	#define TDBXMetaDatabaseColumnNames_SupportsNestedTransactions u"SupportsNestedTransactions"
	
	#define TDBXMetaDatabaseColumnNames_SupportsRowSetSize u"SupportsRowSetSize"
	
	#define TDBXMetaDatabaseColumnNames_ProductVersion u"ProductVersion"
	
	#define TDBXMetaDatabaseColumnNames_ProductName u"ProductName"
	
	#define TDBXMetaDatabaseColumnNames_QuotePrefix u"QuotePrefix"
	
	#define TDBXMetaDatabaseColumnNames_QuoteSuffix u"QuoteSuffix"
	
	#define TDBXMetaDatabaseColumnNames_SupportsLowerCaseIdentifiers u"SupportsLowerCaseIdentifiers"
	
	#define TDBXMetaDatabaseColumnNames_SupportsUpperCaseIdentifiers u"SupportsUpperCaseIdentifiers"
	
	#define TDBXMetaDatabaseColumnNames_SupportsSPReturnCode u"SupportsSPReturnCode"
	
	#define TDBXMetaDatabaseColumnNames_SupportsParameterMetadata u"SupportsParameterMetadata"
	
	#define TDBXMetaDatabaseColumnNames_SupportsCatalogFunctions u"SupportsCatalogFunctions"
	
	#define TDBXMetaDatabaseColumnNames_SupportsCatalogs u"SupportsCatalogs"
	
	#define TDBXMetaDatabaseColumnNames_SupportsSchemas u"SupportsSchemas"
	
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDatabaseColumnNames() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDatabaseColumnNames() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDataTableTypes : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXMetaDataTableTypes_Table u"Table"
	
	#define TDBXMetaDataTableTypes_View u"View"
	
	#define TDBXMetaDataTableTypes_SystemTable u"SystemTable"
	
	#define TDBXMetaDataTableTypes_Synonym u"Synonym"
	
	#define TDBXMetaDataTableTypes_SystemView u"SystemView"
	
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataTableTypes() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataTableTypes() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDataProcedureTypes : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXMetaDataProcedureTypes_ProcedureType u"Procedure"
	
	#define TDBXMetaDataProcedureTypes_FunctionType u"Function"
	
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataProcedureTypes() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataProcedureTypes() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TDBXX509_Filetypes
{
public:
	static constexpr System::Int8 SSL_FILETYPE_DER = System::Int8(0x1);
	
	static constexpr System::Int8 SSL_FILETYPE_PEM = System::Int8(0x2);
	
	static constexpr System::Int8 SSL_FILETYPE_P12 = System::Int8(0x3);
	
};


typedef System::DynamicArray<System::WideChar> TDBXChars;

typedef System::DynamicArray<System::UnicodeString> TWideStringArray;

typedef System::DynamicArray<TDBXValue*> TDBXValueArray;

typedef System::DynamicArray<TDBXWritableValue*> TDBXWritableValueArray;

typedef System::DynamicArray<TDBXParameter*> TDBXParameterArray;

typedef System::DynamicArray<TDBXReader*> TDBXReaderArray;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
private:
#ifndef __aarch64__
	int FErrorCode;
#else /* __aarch64__ */
	long FErrorCode;
#endif /* __aarch64__ */
	System::UnicodeString FErrorMessage;
	
public:
#ifndef __aarch64__
	__fastcall TDBXError(int ErrorCode, const System::UnicodeString ErrorMessage)/* overload */;
	__fastcall TDBXError(int ErrorCode, const System::UnicodeString ErrorMessage, System::Sysutils::Exception* const InnerException)/* overload */;
	static System::UnicodeString __fastcall ErrorCodeToString(int ErrorCode);
	__property int ErrorCode = {read=FErrorCode, nodefault};
#else /* __aarch64__ */
	__fastcall TDBXError(long ErrorCode, const System::UnicodeString ErrorMessage)/* overload */;
	__fastcall TDBXError(long ErrorCode, const System::UnicodeString ErrorMessage, System::Sysutils::Exception* const InnerException)/* overload */;
	static System::UnicodeString __fastcall ErrorCodeToString(long ErrorCode);
	__property long ErrorCode = {read=FErrorCode};
#endif /* __aarch64__ */
	__property System::UnicodeString Message = {read=FErrorMessage};
public:
	/* Exception.CreateFmt */ inline __fastcall TDBXError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall TDBXError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall TDBXError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall TDBXError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall TDBXError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall TDBXError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall TDBXError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDBXError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDBXError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDBXError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDBXError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~TDBXError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TDBXErrorEvent)(TDBXError* DBXError);

#pragma pack(push,1)
struct DECLSPEC_DRECORD TDBXTraceInfo
{
private:
	System::UnicodeString FTraceMessage;
	int FTraceFlag;
	int FTraceLevel;
	System::UnicodeString FCustomCategory;
	
public:
	__property System::UnicodeString Message = {read=FTraceMessage, write=FTraceMessage};
	__property int TraceFlag = {read=FTraceFlag, write=FTraceFlag};
	__property int TraceLevel = {read=FTraceLevel, write=FTraceLevel};
	__property System::UnicodeString CustomCategory = {read=FCustomCategory, write=FCustomCategory};
};
#pragma pack(pop)


typedef Data::Dbcommontypes::CBRType __fastcall (__closure *TDBXTraceEvent)(const TDBXTraceInfo &TraceInfo);

typedef void __fastcall (__closure *TEventPointer)(void);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TEventsCollection : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TEventPointer>* FEvents;
	TEventPointer __fastcall GetEvent(const System::UnicodeString AName);
	void __fastcall SetEvent(const System::UnicodeString AName, TEventPointer AValue);
	
public:
	__fastcall TEventsCollection();
	__fastcall virtual ~TEventsCollection();
	void __fastcall SetValues(System::Generics::Collections::TDictionary__2<System::UnicodeString,TEventPointer>* Collection);
	__property TEventPointer Events[const System::UnicodeString AName] = {read=GetEvent, write=SetEvent};
	__property System::Generics::Collections::TDictionary__2<System::UnicodeString,TEventPointer>* AllEvents = {read=FEvents};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TNameValuesStringList : public System::Classes::TStringList
{
	typedef System::Classes::TStringList inherited;
	
public:
	virtual void __fastcall AddNameValues(System::Classes::TStrings* const AStrings);
	virtual void __fastcall MergeNameValues(System::Classes::TStrings* const AStrings);
public:
	/* TStringList.Create */ inline __fastcall TNameValuesStringList()/* overload */ : System::Classes::TStringList() { }
	/* TStringList.Create */ inline __fastcall TNameValuesStringList(bool OwnsObjects)/* overload */ : System::Classes::TStringList(OwnsObjects) { }
	/* TStringList.Create */ inline __fastcall TNameValuesStringList(System::WideChar QuoteChar, System::WideChar Delimiter)/* overload */ : System::Classes::TStringList(QuoteChar, Delimiter) { }
	/* TStringList.Create */ inline __fastcall TNameValuesStringList(System::WideChar QuoteChar, System::WideChar Delimiter, System::Classes::TStringsOptions Options)/* overload */ : System::Classes::TStringList(QuoteChar, Delimiter, Options) { }
	/* TStringList.Create */ inline __fastcall TNameValuesStringList(System::Types::TDuplicates Duplicates, bool Sorted, bool CaseSensitive)/* overload */ : System::Classes::TStringList(Duplicates, Sorted, CaseSensitive) { }
	/* TStringList.Destroy */ inline __fastcall virtual ~TNameValuesStringList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDictionaryStringList : public TNameValuesStringList
{
	typedef TNameValuesStringList inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,int>* FDictionary;
	bool FAssigning;
	HIDESBASE System::UnicodeString __fastcall GetValue(const System::UnicodeString Name);
	HIDESBASE void __fastcall SetValue(const System::UnicodeString Name, const System::UnicodeString Value);
	
protected:
	virtual void __fastcall InsertItem(int Index, const System::UnicodeString S, System::TObject* AObject);
	
public:
	__fastcall TDictionaryStringList()/* overload */;
	__fastcall virtual ~TDictionaryStringList();
	virtual int __fastcall AddObject(const System::UnicodeString S, System::TObject* AObject);
	virtual void __fastcall Assign(System::Classes::TPersistent* APersistent);
	virtual int __fastcall IndexOfName(const System::UnicodeString Name);
	virtual void __fastcall Clear();
	virtual void __fastcall Delete(int Index);
	virtual void __fastcall AddNameValues(System::Classes::TStrings* const AStrings);
	virtual void __fastcall Exchange(int Index1, int Index2);
	virtual void __fastcall Insert(int Index, const System::UnicodeString S);
	__property System::UnicodeString Values[const System::UnicodeString Name] = {read=GetValue, write=SetValue};
public:
	/* TStringList.Create */ inline __fastcall TDictionaryStringList(bool OwnsObjects)/* overload */ : TNameValuesStringList(OwnsObjects) { }
	/* TStringList.Create */ inline __fastcall TDictionaryStringList(System::WideChar QuoteChar, System::WideChar Delimiter)/* overload */ : TNameValuesStringList(QuoteChar, Delimiter) { }
	/* TStringList.Create */ inline __fastcall TDictionaryStringList(System::WideChar QuoteChar, System::WideChar Delimiter, System::Classes::TStringsOptions Options)/* overload */ : TNameValuesStringList(QuoteChar, Delimiter, Options) { }
	/* TStringList.Create */ inline __fastcall TDictionaryStringList(System::Types::TDuplicates Duplicates, bool Sorted, bool CaseSensitive)/* overload */ : TNameValuesStringList(Duplicates, Sorted, CaseSensitive) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXProperties : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
	
private:
	typedef TNameValuesStringList TStringListClass;
	
	
public:
	System::UnicodeString operator[](const System::UnicodeString Name) { return this->Values[Name]; }
	
private:
	TDBXContext* FDBXContext;
	TNameValuesStringList* FProperties;
	System::TObject* FOwner;
	System::Classes::TComponent* FComponentOwner;
	System::Classes::TNotifyEvent FOnChange;
	TEventsCollection* FEvents;
	System::UnicodeString __fastcall GetValue(const System::UnicodeString Name);
	void __fastcall SetValue(const System::UnicodeString Name, const System::UnicodeString Value);
	int __fastcall GetCount();
	System::Classes::TStrings* __fastcall GetProperties();
	
protected:
	virtual void __fastcall DoOnChange(System::TObject* Sender);
	
public:
	__fastcall virtual TDBXProperties(TDBXContext* DBXContext)/* overload */;
	__fastcall virtual TDBXProperties()/* overload */;
	bool __fastcall GetBoolean(const System::UnicodeString Name);
	int __fastcall GetInteger(const System::UnicodeString Name);
	System::UnicodeString __fastcall GetRequiredValue(const System::UnicodeString Name);
	__fastcall virtual ~TDBXProperties();
	TDBXProperties* __fastcall Clone();
	void __fastcall SetComponentOwner(System::Classes::TComponent* AOwner);
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	void __fastcall AddProperties(System::Classes::TStrings* List);
	void __fastcall AddUniqueProperties(System::Classes::TStrings* List)/* overload */;
	void __fastcall MergeProperties(System::Classes::TStrings* List);
	void __fastcall SetProperties(const System::UnicodeString ConnectionString)/* overload */;
	void __fastcall Add(const System::UnicodeString Name, const System::UnicodeString Value);
	void __fastcall GetLists(TWideStringArray &Names, TWideStringArray &Values);
	void __fastcall Clear();
	__property System::UnicodeString Values[const System::UnicodeString Name] = {read=GetValue, write=SetValue/*, default*/};
	__property System::Classes::TStrings* Properties = {read=GetProperties};
	__property int Count = {read=GetCount, nodefault};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property TEventsCollection* Events = {read=FEvents, write=FEvents};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TDBXPropertiesClass);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXConnectionFactory : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDBXFormatter* FDBXDefaultFormatter;
	__classmethod TDBXConnectionFactory* __fastcall OpenConnectionFactory(const System::UnicodeString DriverFileName, const System::UnicodeString ConnectionFileName);
	TDBXDelegateItem* __fastcall CreateDelegatePath(const System::UnicodeString ConnectionName, TDBXProperties* DBXProperties)/* overload */;
	TDBXDelegateItem* __fastcall CreateDelegatePath(const System::UnicodeString Prefix, int Depth, TDBXDelegateItem* DelegateItem, TDBXProperties* DBXProperties)/* overload */;
	TDBXPropertiesItem* __fastcall HasConnectionPropertiesItem(const System::UnicodeString ConnectionName);
	TDBXPropertiesItem* __fastcall GetConnectionPropertiesItem(const System::UnicodeString ConnectionName);
	TDBXProperties* __fastcall CombineDriverProperties(TDBXProperties* ConProperties);
	static TDBXConnectionFactory* ConnectionFactorySingleton;
	static System::TObject* FLock;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TDBXProperties*>* FDrivers;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TDBXPropertiesItem*>* FConnectionProperties;
	TDBXDelegateDriver* __fastcall GetDriver(const System::UnicodeString DriverName, TDBXProperties* DriverProperties)/* overload */;
	System::UnicodeString __fastcall getDriverName(TDBXProperties* ConnectionProperties);
	TDBXConnection* __fastcall GetConnection(TDBXContext* const DBXContext, TDBXProperties* const ConnectionProperties)/* overload */;
	TDBXConnection* __fastcall GetConnection(TDBXContext* const DBXContext, const System::UnicodeString ConnectionName, const System::UnicodeString UserName, const System::UnicodeString Password)/* overload */;
	
protected:
	TDBXContext* FDBXContext;
	
protected:
	virtual TDBXTraceEvent __fastcall GetTraceInfoEvent();
	virtual void __fastcall SetTraceInfoEvent(const TDBXTraceEvent TraceInfoEvent);
	virtual TDBXErrorEvent __fastcall GetErrorEvent();
	virtual void __fastcall SetErrorEvent(const TDBXErrorEvent ErrorEvent);
	virtual int __fastcall GetTraceFlags();
	virtual void __fastcall SetTraceFlags(const int TraceFlags);
	virtual void __fastcall LoadDrivers();
	virtual void __fastcall UnloadDriver(System::UnicodeString DriverName);
	virtual void __fastcall LoadConnections();
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedClose();
	
public:
	__fastcall TDBXConnectionFactory();
	__fastcall virtual ~TDBXConnectionFactory();
	
private:
	// __classmethod void __fastcall Create_();
	// __classmethod void __fastcall Destroy_();
	
public:
	virtual void __fastcall Open();
	virtual void __fastcall Close();
	void __fastcall GetConnectionItems(System::Classes::TStrings* Items);
	void __fastcall GetRegisteredDriverNames(System::Classes::TStringList* DriverNames);
	void __fastcall GetDriverNames(System::Classes::TStrings* Items);
	TDBXProperties* __fastcall HasConnectionProperties(const System::UnicodeString ConnectionName);
	TDBXProperties* __fastcall GetConnectionProperties(const System::UnicodeString ConnectionName);
	TDBXProperties* __fastcall GetDriverProperties(const System::UnicodeString DriverName);
	TDBXProperties* __fastcall HasDriverProperties(const System::UnicodeString DriverName);
	TDBXDriver* __fastcall GetDriver(const System::UnicodeString DriverName)/* overload */;
	TDBXDelegateDriver* __fastcall GetConnectionDriver(const System::UnicodeString ConnectionName)/* overload */;
	TDBXConnection* __fastcall GetConnection(const System::UnicodeString ConnectionName, const System::UnicodeString UserName, const System::UnicodeString Password)/* overload */;
	TDBXConnection* __fastcall GetConnection(TDBXProperties* ConnectionProperties)/* overload */;
	static void __fastcall SetConnectionFactory(TDBXConnectionFactory* const ConnectionFactory);
	static TDBXConnectionFactory* __fastcall GetConnectionFactory();
	__classmethod void __fastcall Lock();
	__classmethod void __fastcall Unlock();
	__property TDBXErrorEvent OnError = {read=GetErrorEvent, write=SetErrorEvent};
	__property TDBXTraceEvent OnTrace = {read=GetTraceInfoEvent, write=SetTraceInfoEvent};
	__property int TraceFlags = {read=GetTraceFlags, write=SetTraceFlags, nodefault};
	__property TDBXFormatter* DBXFormatter = {read=FDBXDefaultFormatter, write=FDBXDefaultFormatter};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXIniFileConnectionFactory : public TDBXConnectionFactory
{
	typedef TDBXConnectionFactory inherited;
	
private:
	System::UnicodeString FConnectionsFile;
	System::UnicodeString FDriversFile;
	TDBXProperties* __fastcall LoadSectionProperties(System::Inifiles::TMemIniFile* IniFile, System::UnicodeString Section, bool LoadConnection);
	TDBXProperties* __fastcall LoadDriver(System::Inifiles::TMemIniFile* DriverIni, const System::UnicodeString DriverName);
	
protected:
	virtual void __fastcall LoadDrivers();
	virtual void __fastcall LoadConnections();
	
public:
	__fastcall TDBXIniFileConnectionFactory();
	__fastcall virtual ~TDBXIniFileConnectionFactory();
	void __fastcall GetDriverItems(System::Classes::TStrings* Items);
	__property System::UnicodeString DriversFile = {read=FDriversFile, write=FDriversFile};
	__property System::UnicodeString ConnectionsFile = {read=FConnectionsFile, write=FConnectionsFile};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMemoryConnectionFactory : public TDBXConnectionFactory
{
	typedef TDBXConnectionFactory inherited;
	
public:
	__fastcall TDBXMemoryConnectionFactory();
	__fastcall virtual ~TDBXMemoryConnectionFactory();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef TDBXCommand* __fastcall (__closure *TDBXCreateCommandEvent)(TDBXContext* DbxContext, TDBXConnection* Connection, TDBXCommand* MorphicCommand);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXCreateCommand : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDBXCreateCommandEvent FOnCreateCommand;
public:
	/* TObject.Create */ inline __fastcall TDBXCreateCommand() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXCreateCommand() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TDBXDriverClass);

#pragma pack(push,1)
struct DECLSPEC_DRECORD TDBXDriverDef
{
public:
	System::UnicodeString FDriverName;
	TDBXProperties* FDriverProperties;
	TDBXContext* FDBXContext;
};
#pragma pack(pop)


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDriver : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FDriverName;
	int FReferenceCount;
	TDBXProperties* FDriverProperties;
	TDBXCommandFactory* FMetaDataCommandFactory;
	bool FCachedUntilFinalization;
	void __fastcall AddReference();
	void __fastcall RemoveReference();
	void __fastcall UncacheAtFinalization();
	
protected:
	void __fastcall CacheUntilFinalization();
	
protected:
	TDBXContext* FDBXContext;
	TDBXDriverLoader* FDriverLoader;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TDBXCreateCommand*>* FCommandFactories;
	virtual TDBXProperties* __fastcall GetDriverProperties();
	virtual void __fastcall InitDriverProperties(TDBXProperties* const DriverProperties);
	virtual System::UnicodeString __fastcall GetDriverName();
	virtual void __fastcall SetDriverName(const System::UnicodeString DriverName);
	virtual TDBXConnection* __fastcall CreateConnection(TDBXConnectionBuilder* ConnectionBuilder) = 0 ;
	virtual void __fastcall Close() = 0 ;
	virtual TDBXCommand* __fastcall CreateMorphCommand(TDBXContext* DbxContext, TDBXConnection* Connection, TDBXCommand* MorphicCommand);
	void __fastcall LoadMetaDataCommandFactory(const System::UnicodeString MetaDataCommandFactoryClassName, const System::UnicodeString MetaDataCommandFactoryPackageName);
	void __fastcall AddCommandFactory(const System::UnicodeString Name, TDBXCreateCommandEvent OnCreateCommand)/* overload */;
	void __fastcall AddCommandFactory(const System::UnicodeString Name, TDBXCommandFactory* CommandFactory)/* overload */;
	
public:
	__fastcall virtual TDBXDriver(const TDBXDriverDef &DriverDef)/* overload */;
	__fastcall TDBXDriver()/* overload */;
	virtual void __fastcall GetDriverPropertyNames(System::Classes::TStrings* List);
	virtual System::TClass __fastcall GetDriverClass();
	__fastcall virtual ~TDBXDriver();
	virtual System::UnicodeString __fastcall GetDriverVersion() = 0 ;
	__property System::UnicodeString DriverName = {read=GetDriverName, write=SetDriverName};
	__property TDBXProperties* DriverProperties = {read=GetDriverProperties};
	__property System::UnicodeString DriverVersion = {read=GetDriverVersion};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXStateItem : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall Close() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDBXStateItem() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXStateItem() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXStateItemList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual ~TDBXStateItemList();
	TDBXStateItem* __fastcall GetStateItem(System::UnicodeString Name);
	void __fastcall AddStateItem(System::UnicodeString Name, TDBXStateItem* Item);
	void __fastcall RemoveAndFreeStateItem(System::UnicodeString Name);
public:
	/* TObject.Create */ inline __fastcall TDBXStateItemList() : System::TObject() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXConnection : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDBXTransaction* FTransactionStack;
	bool FOpen;
	System::UnicodeString FProductVersion;
	bool FProductVersionInitialized;
	System::TObject* FMetaDataReader;
	System::Generics::Collections::TList__1<TDBXCommand*>* FCommands;
	void __fastcall CheckTransaction(TDBXTransaction* Transaction);
	void __fastcall FreeTransactions(TDBXTransaction* StartTransaction);
	void __fastcall AddCommand(TDBXCommand* Command);
	void __fastcall RemoveCommand(TDBXCommand* Command);
	
protected:
	int FIsolationLevel;
	TDBXDriver* FDriverDelegate;
	TDBXDatabaseMetaData* FDatabaseMetaData;
	
protected:
	TDBXContext* FDBXContext;
	TDBXProperties* FConnectionProperties;
	void __fastcall CloseAllCommands();
	void __fastcall RollbackAllTransactions();
	virtual TDBXTransaction* __fastcall CreateAndBeginTransaction(const int Isolation) = 0 ;
	virtual void __fastcall Commit(TDBXTransaction* const Transaction) = 0 ;
	virtual void __fastcall Rollback(TDBXTransaction* const Transaction) = 0 ;
	virtual TDBXDatabaseMetaData* __fastcall GetDatabaseMetaData();
	virtual TDBXProperties* __fastcall GetConnectionProperties();
	virtual void __fastcall SetConnectionProperties(TDBXProperties* const Value);
	virtual TDBXTraceEvent __fastcall GetTraceInfoEvent();
	virtual void __fastcall SetTraceInfoEvent(const TDBXTraceEvent TraceInfoEvent);
	virtual int __fastcall GetTraceFlags();
	virtual void __fastcall SetTraceFlags(const int TraceFlags);
	virtual TDBXErrorEvent __fastcall GetErrorEvent();
	virtual void __fastcall SetErrorEvent(const TDBXErrorEvent ErrorEvent);
	virtual TDBXFormatter* __fastcall GetDBXFormatter();
	virtual void __fastcall SetDBXFormatter(TDBXFormatter* const DBXFormatter);
	virtual bool __fastcall GetIsOpen();
	virtual void __fastcall Open();
	virtual TDBXCommand* __fastcall DerivedCreateCommand();
	virtual void __fastcall DerivedOpen() = 0 ;
	virtual void __fastcall DerivedGetCommandTypes(System::Classes::TStrings* const List) = 0 ;
	virtual void __fastcall DerivedGetCommands(const System::UnicodeString CommandType, System::Classes::TStrings* const List) = 0 ;
	virtual void __fastcall DerivedClose() = 0 ;
	virtual TDBXCommand* __fastcall CreateMorphCommand(TDBXCommand* MorphicCommand);
	virtual System::UnicodeString __fastcall GetProductVersion();
	virtual System::UnicodeString __fastcall GetProductName();
	virtual System::UnicodeString __fastcall GetConnectionProperty(const System::UnicodeString Name);
	__fastcall TDBXConnection(TDBXConnectionBuilder* ConnectionBuilder);
	
public:
	__fastcall virtual ~TDBXConnection();
	virtual void __fastcall Close();
	virtual TDBXTransaction* __fastcall BeginTransaction(int Isolation)/* overload */;
	virtual TDBXTransaction* __fastcall BeginTransaction()/* overload */;
	virtual void __fastcall CommitFreeAndNil(TDBXTransaction* &Transaction);
	virtual void __fastcall CommitTransaction();
	virtual void __fastcall RollbackFreeAndNil(TDBXTransaction* &Transaction);
	virtual void __fastcall RollbackIncompleteFreeAndNil(TDBXTransaction* &Transaction);
	virtual void __fastcall RollbackTransaction();
	virtual TDBXCommand* __fastcall CreateCommand()/* overload */;
	void __fastcall GetCommandTypes(System::Classes::TStrings* List);
	void __fastcall GetCommands(const System::UnicodeString CommandType, System::Classes::TStrings* List);
	virtual System::UnicodeString __fastcall GetVendorProperty(const System::UnicodeString Name);
	bool __fastcall HasTransaction(TDBXTransaction* Transaction);
	__property TDBXProperties* ConnectionProperties = {read=GetConnectionProperties, write=SetConnectionProperties};
	__property TDBXDatabaseMetaData* DatabaseMetaData = {read=GetDatabaseMetaData};
	__property TDBXTraceEvent OnTrace = {read=GetTraceInfoEvent, write=SetTraceInfoEvent};
	__property int TraceFlags = {read=GetTraceFlags, write=SetTraceFlags, nodefault};
	__property TDBXErrorEvent OnErrorEvent = {read=GetErrorEvent, write=SetErrorEvent};
	__property bool IsOpen = {read=GetIsOpen, nodefault};
	__property TDBXFormatter* DBXFormatter = {read=GetDBXFormatter, write=SetDBXFormatter};
	__property System::UnicodeString ProductVersion = {read=GetProductVersion};
	__property System::UnicodeString ProductName = {read=GetProductName};
	__property System::UnicodeString ConnectionProperty[const System::UnicodeString Name] = {read=GetConnectionProperty};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTransaction : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDBXTransaction* FNext;
	TDBXConnection* FConnection;
	
protected:
	int FIsolationLevel;
	
protected:
	__fastcall TDBXTransaction(TDBXConnection* Connection);
	
public:
	__property TDBXConnection* Connection = {read=FConnection};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTransaction() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDatabaseMetaData : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FQuoteChar;
	System::UnicodeString FProcedureQuoteChar;
	bool FSupportsTransactions;
	bool FSupportsNestedTransactions;
	int FMaxCommands;
	bool FSupportsRowSetSize;
	System::UnicodeString FQuotePrefix;
	System::UnicodeString FQuoteSuffix;
	bool FSupportsLowerCaseIdentifiers;
	bool FSupportsUpperCaseIdentifiers;
	bool FSupportsSPReturnCode;
	System::UnicodeString FMetaDataVersion;
	bool FSupportsParameterMetadata;
	bool FSupportsCatalogFunctions;
	bool FSupportsCatalogs;
	bool FSupportsSchemas;
	void __fastcall Init(TDBXConnection* Connection);
	
protected:
	TDBXContext* FDBXContext;
	
public:
	__fastcall TDBXDatabaseMetaData(TDBXContext* DBXContext);
	__property System::UnicodeString QuoteChar = {read=FQuoteChar};
	__property System::UnicodeString ProcedureQuoteChar = {read=FProcedureQuoteChar};
	__property bool SupportsTransactions = {read=FSupportsTransactions, nodefault};
	__property bool SupportsNestedTransactions = {read=FSupportsNestedTransactions, nodefault};
	__property int MaxCommands = {read=FMaxCommands, nodefault};
	__property bool SupportsRowSetSize = {read=FSupportsRowSetSize, nodefault};
	__property System::UnicodeString QuotePrefix = {read=FQuotePrefix};
	__property System::UnicodeString QuoteSuffix = {read=FQuoteSuffix};
	__property bool SupportsLowerCaseIdentifiers = {read=FSupportsLowerCaseIdentifiers, nodefault};
	__property bool SupportsUpperCaseIdentifiers = {read=FSupportsUpperCaseIdentifiers, nodefault};
	__property System::UnicodeString MetaDataVersion = {read=FMetaDataVersion};
	__property bool SupportsSPReturnCode = {read=FSupportsSPReturnCode, nodefault};
	__property bool SupportsParameterMetadata = {read=FSupportsParameterMetadata, nodefault};
	__property bool SupportsCatalogFunctions = {read=FSupportsCatalogFunctions, nodefault};
	__property bool SupportsCatalogs = {read=FSupportsCatalogs, nodefault};
	__property bool SupportsSchemas = {read=FSupportsSchemas, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDatabaseMetaData() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXCommand : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FCommandType;
	System::UnicodeString FText;
	TDBXReader* FLastReader;
	bool FOpen;
	bool FPrepared;
	int FCommandTimeout;
	TDBXConnection* FConnection;
	bool FConnectionClosed;
	System::Generics::Collections::TList__1<System::TObject*>* FFreeOnCloseList;
	void __fastcall CommandExecuting();
	void __fastcall CommandExecuted();
	void __fastcall SetParameters();
	void __fastcall ConnectionClosing();
	void __fastcall FreeOnExecuteObjects();
	
protected:
	TDBXParameterList* FParameters;
	void __fastcall NotImplemented();
	
protected:
	TDBXContext* FDBXContext;
	__fastcall TDBXCommand(TDBXContext* DBXContext);
	virtual void __fastcall CloseReader();
	virtual void __fastcall SetCommandType(const System::UnicodeString CommandType);
	virtual System::UnicodeString __fastcall GetCommandType();
	virtual System::UnicodeString __fastcall GetText();
	virtual void __fastcall SetText(const System::UnicodeString Value);
	virtual void __fastcall SetRowSetSize(const __int64 RowSetSize) = 0 ;
	virtual void __fastcall SetMaxBlobSize(const __int64 MaxBlobSize) = 0 ;
	virtual __int64 __fastcall GetRowsAffected() = 0 ;
	virtual void __fastcall SetCommandTimeout(const int Timeout);
	virtual int __fastcall GetCommandTimeout();
	virtual TDBXErrorEvent __fastcall GetErrorEvent();
	virtual TDBXRow* __fastcall CreateParameterRow();
	virtual void __fastcall CreateParameters(TDBXCommand* Command);
	virtual TDBXParameterList* __fastcall GetParameters();
	virtual void __fastcall Open();
	virtual TDBXReader* __fastcall DerivedGetNextReader() = 0 ;
	virtual void __fastcall DerivedOpen() = 0 ;
	virtual void __fastcall DerivedClose() = 0 ;
	virtual void __fastcall DerivedPrepare() = 0 ;
	virtual TDBXReader* __fastcall DerivedExecuteQuery() = 0 ;
	virtual void __fastcall DerivedExecuteUpdate() = 0 ;
	virtual void __fastcall DerivedClearParameters();
	
public:
	__fastcall virtual ~TDBXCommand();
	virtual void __fastcall FreeOnExecute(System::TObject* Value);
	virtual void __fastcall Close();
	virtual void __fastcall Prepare();
	virtual TDBXReader* __fastcall ExecuteQuery();
	virtual void __fastcall ExecuteUpdate();
	virtual TDBXReader* __fastcall GetNextReader();
	virtual TDBXParameter* __fastcall CreateParameter();
	__property __int64 RowsAffected = {read=GetRowsAffected};
	__property System::UnicodeString Text = {read=GetText, write=SetText};
	__property __int64 RowSetSize = {write=SetRowSetSize};
	__property __int64 MaxBlobSize = {write=SetMaxBlobSize};
	__property System::UnicodeString CommandType = {read=GetCommandType, write=SetCommandType};
	__property TDBXParameterList* Parameters = {read=GetParameters};
	__property TDBXErrorEvent OnErrorEvent = {read=GetErrorEvent};
	__property bool IsPrepared = {read=FPrepared, nodefault};
	__property int CommandTimeout = {read=GetCommandTimeout, write=SetCommandTimeout, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXMorphicCommand : public TDBXCommand
{
	typedef TDBXCommand inherited;
	
protected:
	TDBXConnection* FConnection;
	TDBXCommand* FCommand;
	__int64 FRowSetSize;
	__int64 FMaxBlobSize;
	void __fastcall CopyProperties(TDBXCommand* Command);
	
protected:
	virtual __int64 __fastcall GetRowsAffected();
	virtual void __fastcall SetCommandType(const System::UnicodeString Value);
	virtual void __fastcall SetText(const System::UnicodeString Value);
	virtual TDBXRow* __fastcall CreateParameterRow();
	virtual TDBXParameterList* __fastcall GetParameters();
	virtual void __fastcall CreateParameters(TDBXCommand* Command);
	virtual void __fastcall SetMaxBlobSize(const __int64 MaxBlobSize);
	virtual void __fastcall SetRowSetSize(const __int64 Value);
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedClose();
	virtual TDBXReader* __fastcall DerivedGetNextReader();
	virtual TDBXReader* __fastcall DerivedExecuteQuery();
	virtual void __fastcall DerivedExecuteUpdate();
	virtual void __fastcall DerivedPrepare();
	virtual void __fastcall CloseReader();
	
public:
	__fastcall TDBXMorphicCommand(TDBXContext* DBXContext, TDBXConnection* Connection);
	__fastcall virtual ~TDBXMorphicCommand();
	virtual void __fastcall FreeOnExecute(System::TObject* Value);
	virtual void __fastcall Prepare();
	virtual TDBXReader* __fastcall ExecuteQuery();
	virtual void __fastcall ExecuteUpdate();
	virtual TDBXReader* __fastcall GetNextReader();
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXValueList : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDBXWritableValueArray FValues;
	int FValueCount;
	int FLastOrdinal;
	bool FClosed;
	virtual int __fastcall FindOrdinal(const System::UnicodeString Name, const int StartOrdinal, const int EndOrdinal)/* overload */;
	void __fastcall InvalidOrdinal(const int Ordinal);
	void __fastcall InvalidName(const System::UnicodeString Name, const int Ordinal);
	
protected:
	TDBXContext* FDBXContext;
	void __fastcall FailIfClosed();
	__property TDBXContext* DBXContext = {read=FDBXContext};
	
protected:
	void __fastcall ClearValues();
	virtual void __fastcall SetValues(const TDBXValueArray Values)/* overload */;
	virtual void __fastcall SetValues(const TDBXWritableValueArray Values)/* overload */;
	virtual void __fastcall SetValues(const TDBXWritableValueArray Values, const int Count)/* overload */;
	virtual TDBXValue* __fastcall GetValue(const int Ordinal);
	virtual TDBXValue* __fastcall GetValueByName(const System::UnicodeString Name);
	virtual TDBXValueType* __fastcall GetValueType(const int Ordinal);
	virtual int __fastcall GetColumnCount();
	
public:
	__fastcall TDBXValueList(TDBXContext* DBXContext);
	__fastcall virtual ~TDBXValueList();
	__property bool Closed = {read=FClosed, nodefault};
	virtual int __fastcall GetOrdinal(const System::UnicodeString Name)/* overload */;
	__property int ColumnCount = {read=GetColumnCount, nodefault};
	__property TDBXValueType* ValueType[const int Ordinal] = {read=GetValueType};
	__property TDBXWritableValueArray Values = {read=FValues};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXWritableValueList : public TDBXValueList
{
	typedef TDBXValueList inherited;
	
public:
	TDBXWritableValue* operator[](const int Ordinal) { return this->Value[Ordinal]; }
	
protected:
	virtual TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	
public:
	__fastcall TDBXWritableValueList(TDBXContext* DBXContext);
	__property TDBXWritableValue* Value[const int Ordinal] = {read=GetWritableValue/*, default*/};
public:
	/* TDBXValueList.Destroy */ inline __fastcall virtual ~TDBXWritableValueList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXReader : public TDBXValueList
{
	typedef TDBXValueList inherited;
	
public:
	TDBXValue* operator[](const int Ordinal) { return this->Value[Ordinal]; }
	
private:
	TDBXByteReader* FByteReader;
	TDBXCommand* FCommand;
	void __fastcall CommandCloseReader();
	void __fastcall CloseReader();
	
protected:
	TDBXRow* FDbxRow;
	TDBXErrorEvent __fastcall GetErrorEvent();
	
protected:
	__fastcall TDBXReader(TDBXContext* DBXContext, TDBXRow* DbxRow, TDBXByteReader* ByteReader);
	virtual bool __fastcall DerivedNext() = 0 ;
	virtual void __fastcall DerivedClose() = 0 ;
	virtual TDBXByteReader* __fastcall GetByteReader();
	virtual int __fastcall GetReaderHandle();
	virtual bool __fastcall IsUpdateable();
	virtual int __fastcall GetRowHandle();
	TDBXRow* __fastcall GetRow();
	
public:
	__fastcall virtual ~TDBXReader();
	void __fastcall Close();
	virtual bool __fastcall Next();
	virtual bool __fastcall Reset();
	virtual System::UnicodeString __fastcall GetObjectTypeName(int Ordinal);
	__property TDBXByteReader* ByteReader = {read=GetByteReader};
	__property TDBXErrorEvent OnErrorEvent = {read=GetErrorEvent};
	__property int RowHandle = {read=GetRowHandle, nodefault};
	__property bool Updateable = {read=IsUpdateable, nodefault};
	__property TDBXValue* Value[const int Ordinal] = {read=GetValue/*, default*/};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXValueType : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FName;
	System::UnicodeString FCaption;
	int FOrdinal;
	int FDataType;
	int FSubType;
	__int64 FSize;
	__int64 FPrecision;
	int FScale;
	int FChildPosition;
	int FFlags;
	int FParameterDirection;
	TDBXRow* FDbxRow;
	bool __fastcall IsNullable();
	bool __fastcall IsReadOnly();
	bool __fastcall IsSearchable();
	bool __fastcall IsAutoIncrement();
	bool __fastcall IsReadOnlyType();
	
protected:
	TDBXContext* FDBXContext;
	
protected:
	virtual void __fastcall SetDbxRow(TDBXRow* const DbxRow);
	virtual void __fastcall SetParameterDirection(const int ParameterDirection);
	virtual void __fastcall SetName(const System::UnicodeString Name);
	virtual void __fastcall SetDisplayName(const System::UnicodeString Caption);
	virtual void __fastcall SetOrdinal(const int Ordinal);
	virtual void __fastcall SetDataType(const int DataType);
	virtual void __fastcall SetSubType(const int SubType);
	virtual void __fastcall SetPrecision(const __int64 Precision);
	virtual void __fastcall SetScale(const int Scale);
	virtual void __fastcall SetChildPosition(const int ChildPosition);
	virtual void __fastcall SetFlags(const int Flags);
	virtual void __fastcall SetNullable(const bool NullableValue);
	virtual void __fastcall SetSize(const __int64 Size);
	virtual void __fastcall SetHidden(const System::LongBool Hidden);
	virtual void __fastcall SetValueParameter(const bool ValueParameter);
	virtual void __fastcall SetLiteral(const bool Literal);
	virtual int __fastcall GetParameterDirection();
	virtual System::UnicodeString __fastcall GetName();
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual int __fastcall GetOrdinal();
	virtual int __fastcall GetDataType();
	virtual int __fastcall GetSubType();
	virtual __int64 __fastcall GetPrecision();
	virtual int __fastcall GetScale();
	virtual int __fastcall GetChildPosition();
	virtual int __fastcall GetFlags();
	virtual __int64 __fastcall GetSize();
	virtual System::LongBool __fastcall GetHidden();
	virtual bool __fastcall GetValueParameter();
	virtual bool __fastcall GetLiteral();
	
private:
	bool FModified;
	void __fastcall FailIfReadOnlyType();
	void __fastcall SetReadOnlyType();
	__property TDBXContext* DBXContext = {read=FDBXContext};
	
public:
	__fastcall TDBXValueType(TDBXContext* DBXContext)/* overload */;
	__fastcall TDBXValueType()/* overload */;
	__fastcall virtual ~TDBXValueType();
	TDBXValueType* __fastcall Clone();
	TDBXValueType* __fastcall WritableClone();
	static System::UnicodeString __fastcall DataTypeName(int DataType);
	static void __fastcall InvalidTypeAccess(int ExpectedDataType, int DataType);
	__property System::UnicodeString Name = {read=FName, write=SetName};
	__property System::UnicodeString DisplayName = {read=FCaption, write=SetDisplayName};
	__property int DataType = {read=GetDataType, write=SetDataType, nodefault};
	__property int Ordinal = {read=GetOrdinal, write=SetOrdinal, nodefault};
	__property int SubType = {read=GetSubType, write=SetSubType, nodefault};
	__property __int64 Precision = {read=GetPrecision, write=SetPrecision};
	__property int Scale = {read=GetScale, write=SetScale, nodefault};
	__property int ChildPosition = {read=GetChildPosition, write=SetChildPosition, nodefault};
	__property int ValueTypeFlags = {read=GetFlags, write=SetFlags, nodefault};
	__property __int64 Size = {read=GetSize, write=SetSize};
	__property bool Nullable = {read=IsNullable, write=SetNullable, nodefault};
	__property bool ReadOnly = {read=IsReadOnly, nodefault};
	__property bool Searchable = {read=IsSearchable, nodefault};
	__property bool AutoIncrement = {read=IsAutoIncrement, nodefault};
	__property System::LongBool Hidden = {read=GetHidden, write=SetHidden, nodefault};
	__property int ParameterDirection = {read=GetParameterDirection, write=SetParameterDirection, nodefault};
	__property bool ValueParameter = {read=GetValueParameter, write=SetValueParameter, nodefault};
	__property bool Literal = {read=GetLiteral, write=SetLiteral, nodefault};
};


class PASCALIMPLEMENTATION TDBXParameter : public TDBXValueType
{
	typedef TDBXValueType inherited;
	
private:
	TDBXWritableValue* FValue;
	System::TObject* FConnectionHandler;
	System::UnicodeString FTypeName;
	void __fastcall UpdateParameterType(int SetDataType);
	void __fastcall CopyByteValue(TDBXValue* Source, TDBXWritableValue* Dest);
	void __fastcall AssignValue(TDBXValue* Source);
	virtual void __fastcall AssignType(TDBXParameter* Source);
	
protected:
	virtual TDBXWritableValue* __fastcall GetValue();
	virtual void __fastcall SetParameter();
	
public:
	__fastcall TDBXParameter(TDBXContext* DbxContext)/* overload */;
	__fastcall TDBXParameter(TDBXContext* DbxContext, TDBXRow* Row)/* overload */;
	__fastcall TDBXParameter(TDBXContext* DbxContext, TDBXRow* Row, TDBXParameter* Source)/* overload */;
	__fastcall virtual ~TDBXParameter();
	virtual void __fastcall Assign(TDBXParameter* Source);
	HIDESBASE virtual System::TObject* __fastcall Clone();
	__property TDBXWritableValue* Value = {read=GetValue};
	__property System::UnicodeString TypeName = {read=FTypeName, write=FTypeName};
	__property System::TObject* ConnectionHandler = {read=FConnectionHandler, write=FConnectionHandler};
public:
	/* TDBXValueType.Create */ inline __fastcall TDBXParameter()/* overload */ : TDBXValueType() { }
	
};


typedef System::DynamicArray<TDBXValueType*> TDBXValueTypeArray;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXParameterList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TDBXParameter* operator[](const int Ordinal) { return this->Parameter[Ordinal]; }
	
private:
	TDBXValueTypeList* FValueTypes;
	TDBXCommand* FCommand;
	TDBXRow* FParameterRow;
	TDBXParameter* __fastcall GetParameterByName(const System::UnicodeString Name);
	void __fastcall InvalidOrdinal(int Ordinal);
	
protected:
	void __fastcall SetPendingOutParameter(const int Ordinal);
	virtual TDBXRow* __fastcall GetRow();
	
protected:
	TDBXContext* FDBXContext;
	__fastcall TDBXParameterList(TDBXContext* DBXContext, TDBXCommand* Command)/* overload */;
	virtual TDBXParameter* __fastcall GetParameterByOrdinal(const int Ordinal);
	virtual int __fastcall GetCount();
	
public:
	__fastcall TDBXParameterList(TDBXContext* DBXContext, TDBXRow* DBXRow)/* overload */;
	__fastcall virtual ~TDBXParameterList();
	virtual void __fastcall SetCount(const int Count);
	virtual void __fastcall AddParameter(TDBXParameter* Parameter);
	virtual void __fastcall SetParameter(const int Ordinal, TDBXParameter* const Parameter);
	virtual void __fastcall InsertParameter(int Ordinal, TDBXParameter* Parameter);
	virtual void __fastcall RemoveParameter(int Ordinal)/* overload */;
	virtual void __fastcall RemoveParameter(TDBXParameter* Parameter)/* overload */;
	virtual void __fastcall ClearParameters()/* overload */;
	virtual void __fastcall RemoveParameters();
	virtual int __fastcall GetOrdinal(const System::UnicodeString Name);
	__property int Count = {read=GetCount, write=SetCount, nodefault};
	__property TDBXParameter* Parameter[const int Ordinal] = {read=GetParameterByOrdinal/*, default*/};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXJSONStream : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Json::Writers::TJsonWriter* FJSONWriter;
	System::Json::Readers::TJsonReader* FJSONReader;
	System::Classes::TStream* FBaseStream;
	bool FOwnsStream;
	
protected:
	System::Json::Readers::TJsonReader* __fastcall GetJSONReader();
	System::Json::Writers::TJsonWriter* __fastcall GetJSONWriter();
	
public:
	__fastcall TDBXJSONStream()/* overload */;
	__fastcall TDBXJSONStream(System::Classes::TStream* const AStream, bool AOwnsStream)/* overload */;
	__fastcall virtual ~TDBXJSONStream();
	void __fastcall Close();
	System::Classes::TStream* __fastcall ExtractStream();
	__property System::Json::Readers::TJsonReader* Reader = {read=GetJSONReader};
	__property System::Json::Writers::TJsonWriter* Writer = {read=GetJSONWriter};
	__property System::Classes::TStream* BaseStream = {read=FBaseStream};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXValue : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDBXValueType* FValueType;
	int FGeneration;
	System::LongBool FIsNull;
	virtual void __fastcall InvalidOperation();
	static void __fastcall UnsupportedFieldType(TDBXContext* DBXContext, TDBXValueType* ValueType);
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	__fastcall TDBXValue(TDBXValueType* ValueType);
	
protected:
	TDBXRow* FDbxRow;
	TDBXContext* __fastcall GetDbxContext();
	__property TDBXContext* DbxContext = {read=GetDbxContext};
	virtual TDBXValue* __fastcall GetNonDelegate();
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
	virtual TDBXDate __fastcall GetAsDate();
	virtual TDBXTime __fastcall GetAsTime();
	virtual Data::Sqltimst::TSQLTimeStamp __fastcall GetAsTimeStamp();
	virtual Data::Sqltimst::TSQLTimeStampOffset __fastcall GetAsTimeStampOffset();
	virtual System::TDateTime __fastcall GetAsDateTime();
	virtual System::Currency __fastcall GetAsCurrency();
	virtual System::OleVariant __fastcall GetAsVariant();
	virtual System::Classes::TStream* __fastcall GetAsStream();
	virtual TDBXReader* __fastcall GetAsDBXReader();
	
public:
	__fastcall virtual ~TDBXValue();
	static TDBXWritableValue* __fastcall CreateValue(TDBXContext* DBXContext, TDBXValueType* ValueType, TDBXRow* DbxRow, bool ReadOnlyType)/* overload */;
	static TDBXWritableValue* __fastcall CreateValue(TDBXValueType* ValueType)/* overload */;
	virtual bool __fastcall IsNull() = 0 ;
	virtual __int64 __fastcall GetValueSize();
	virtual System::AnsiString __fastcall GetAnsiString();
	virtual TDBXDate __fastcall GetDate();
	virtual bool __fastcall GetBoolean()/* overload */;
	virtual TDBXTime __fastcall GetTime();
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
	virtual TDBXReader* __fastcall GetDBXReader(bool AInstanceOwner)/* overload */;
	virtual TDBXReader* __fastcall GetDBXReader()/* overload */;
	virtual TDBXConnection* __fastcall GetDBXConnection();
	virtual System::Classes::TStream* __fastcall GetStream(bool AInstanceOwner)/* overload */;
	virtual TDBXJSONStream* __fastcall GetJSONStream(bool AInstanceOwner)/* overload */;
	virtual System::Classes::TStream* __fastcall GetStream()/* overload */;
	virtual System::Json::TJSONValue* __fastcall GetJSONValue()/* overload */;
	virtual System::Json::TJSONValue* __fastcall GetJSONValue(bool AInstanceOwner)/* overload */;
	virtual Data::Dbxjson::TDBXCallback* __fastcall GetCallbackValue();
	virtual System::TObject* __fastcall GetObjectValue()/* overload */;
	virtual System::TObject* __fastcall GetObjectValue(bool AInstanceOwner)/* overload */;
	virtual System::UnicodeString __fastcall GetWideString(System::UnicodeString defaultValue)/* overload */;
	virtual bool __fastcall GetBoolean(bool defaultValue)/* overload */;
	virtual System::Byte __fastcall GetUInt8(System::Byte defaultValue)/* overload */;
	virtual System::Int8 __fastcall GetInt8(System::Int8 defaultValue)/* overload */;
	virtual System::Word __fastcall GetUInt16(System::Word defaultValue)/* overload */;
	virtual short __fastcall GetInt16(short defaultValue)/* overload */;
	virtual int __fastcall GetInt32(int defaultValue)/* overload */;
	virtual __int64 __fastcall GetInt64(__int64 defaultValue)/* overload */;
	virtual bool __fastcall EqualsValue(TDBXValue* Other);
	virtual short __fastcall Compare(TDBXValue* Other);
	__property TDBXValueType* ValueType = {read=FValueType};
	__property System::UnicodeString AsString = {read=GetAsString};
	__property bool AsBoolean = {read=GetAsBoolean, nodefault};
	__property System::Byte AsUInt8 = {read=GetAsUInt8, nodefault};
	__property System::Int8 AsInt8 = {read=GetAsInt8, nodefault};
	__property System::Word AsUInt16 = {read=GetAsUInt16, nodefault};
	__property short AsInt16 = {read=GetAsInt16, nodefault};
	__property int AsInt32 = {read=GetAsInt32, nodefault};
	__property __int64 AsInt64 = {read=GetAsInt64};
	__property float AsSingle = {read=GetAsSingle};
	__property double AsDouble = {read=GetAsDouble};
	__property Data::Fmtbcd::TBcd AsBcd = {read=GetAsBcd};
	__property TDBXDate AsDate = {read=GetAsDate, nodefault};
	__property TDBXTime AsTime = {read=GetAsTime, nodefault};
	__property Data::Sqltimst::TSQLTimeStamp AsTimeStamp = {read=GetAsTimeStamp};
	__property System::TDateTime AsDateTime = {read=GetAsDateTime};
	__property System::OleVariant AsVariant = {read=GetAsVariant};
	__property System::Classes::TStream* AsStream = {read=GetAsStream};
	__property TDBXReader* AsDBXReader = {read=GetAsDBXReader};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXWritableValue : public TDBXValue
{
	typedef TDBXValue inherited;
	
private:
	bool FSetPending;
	virtual void __fastcall UpdateType();
	virtual void __fastcall SetRowValue()/* overload */;
	virtual TDBXStreamReader* __fastcall GetStreamReader();
	
protected:
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
	virtual void __fastcall SetAsDate(const TDBXDate Value);
	virtual void __fastcall SetAsTime(const TDBXTime Value);
	virtual void __fastcall SetAsTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetAsTimeStampOffset(const Data::Sqltimst::TSQLTimeStampOffset &Value);
	virtual void __fastcall SetAsDateTime(const System::TDateTime Value);
	virtual void __fastcall SetAsCurrency(const System::Currency Value);
	virtual void __fastcall SetAsCurrencyValue(const System::Currency Value, int Precision, int Decimals);
	virtual void __fastcall SetAsVariant(const System::OleVariant &Value);
	virtual void __fastcall SetAsStream(System::Classes::TStream* const Value);
	virtual void __fastcall SetAsDBXReader(TDBXReader* const Value);
	
public:
	__fastcall TDBXWritableValue(TDBXValueType* ValueType);
	__fastcall virtual ~TDBXWritableValue();
	void __fastcall MarkAsPending();
	virtual void __fastcall SetNull();
	virtual void __fastcall SetTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetTimeStampOffset(const Data::Sqltimst::TSQLTimeStampOffset &Value);
	virtual void __fastcall SetBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetAnsiString(const System::AnsiString Value);
	virtual void __fastcall SetBoolean(const bool Value);
	virtual void __fastcall SetDate(const TDBXDate Value);
	virtual void __fastcall SetTime(const TDBXTime Value);
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
	virtual void __fastcall SetDBXReader(TDBXReader* const Value, const bool AInstanceOwner)/* overload */;
	virtual void __fastcall SetJSONStream(TDBXJSONStream* const Value, bool AInstanceOwner);
	virtual void __fastcall SetStream(System::Classes::TStream* const Stream, const bool AInstanceOwner);
	virtual void __fastcall SetDBXConnection(TDBXConnection* const Value);
	virtual void __fastcall SetJSONValue(System::Json::TJSONValue* const Value, const bool AInstanceOwner);
	virtual void __fastcall SetObjectValue(System::TObject* const Value, const bool AInstanceOwner);
	virtual void __fastcall SetCallbackValue(Data::Dbxjson::TDBXCallback* const Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	__property System::UnicodeString AsString = {read=GetAsString, write=SetAsString};
	__property bool AsBoolean = {read=GetAsBoolean, write=SetAsBoolean, nodefault};
	__property System::Byte AsUInt8 = {read=GetAsUInt8, write=SetAsUInt8, nodefault};
	__property System::Int8 AsInt8 = {read=GetAsInt8, write=SetAsInt8, nodefault};
	__property System::Word AsUInt16 = {read=GetAsUInt16, write=SetAsUInt16, nodefault};
	__property short AsInt16 = {read=GetAsInt16, write=SetAsInt16, nodefault};
	__property int AsInt32 = {read=GetAsInt32, write=SetAsInt32, nodefault};
	__property __int64 AsInt64 = {read=GetAsInt64, write=SetAsInt64};
	__property float AsSingle = {read=GetAsSingle, write=SetAsSingle};
	__property double AsDouble = {read=GetAsDouble, write=SetAsDouble};
	__property Data::Fmtbcd::TBcd AsBcd = {read=GetAsBcd, write=SetAsBcd};
	__property TDBXDate AsDate = {read=GetAsDate, write=SetAsDate, nodefault};
	__property TDBXTime AsTime = {read=GetAsTime, write=SetAsTime, nodefault};
	__property Data::Sqltimst::TSQLTimeStamp AsTimeStamp = {read=GetAsTimeStamp, write=SetAsTimeStamp};
	__property Data::Sqltimst::TSQLTimeStampOffset AsTimeStampOffset = {read=GetAsTimeStampOffset, write=SetAsTimeStampOffset};
	__property System::TDateTime AsDateTime = {read=GetAsDateTime, write=SetAsDateTime};
	__property System::Currency AsCurrency = {read=GetAsCurrency, write=SetAsCurrency};
	__property System::OleVariant AsVariant = {read=GetAsVariant, write=SetAsVariant};
	__property System::Classes::TStream* AsStream = {read=GetAsStream, write=SetAsStream};
	__property TDBXReader* AsDBXReader = {read=GetAsDBXReader, write=SetAsDBXReader};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXNullValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
public:
	__fastcall TDBXNullValue(TDBXValueType* ValueType);
	__fastcall virtual ~TDBXNullValue();
	virtual bool __fastcall IsNull();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXAnsiStringValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	System::TArray__1<System::Byte> FValue;
	TDBXByteStreamReader* FOverFlowBytes;
	void __fastcall SetOverflowBytes(TDBXByteStreamReader* const OverFlowBytes);
	virtual TDBXStreamReader* __fastcall GetStreamReader();
	virtual void __fastcall UpdateType();
	
public:
	__fastcall TDBXAnsiStringValue(TDBXValueType* ValueType);
	__fastcall virtual ~TDBXAnsiStringValue();
	virtual bool __fastcall IsNull();
	virtual System::AnsiString __fastcall GetAnsiString();
	virtual void __fastcall SetAnsiString(const System::AnsiString Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual bool __fastcall GetAsBoolean();
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual __int64 __fastcall GetAsInt64();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual TDBXDate __fastcall GetAsDate();
	virtual TDBXTime __fastcall GetAsTime();
	virtual Data::Sqltimst::TSQLTimeStamp __fastcall GetAsTimeStamp();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetAsDate(const TDBXDate Value);
	virtual void __fastcall SetAsTime(const TDBXTime Value);
	virtual void __fastcall SetAsTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDateValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	TDBXDate FDate;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual System::TDateTime __fastcall GetAsDateTime();
	virtual void __fastcall SetAsDateTime(const System::TDateTime Value);
	virtual bool __fastcall IsNull();
	virtual TDBXDate __fastcall GetDate();
	virtual void __fastcall SetDate(const TDBXDate Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual TDBXDate __fastcall GetAsDate();
	virtual Data::Sqltimst::TSQLTimeStamp __fastcall GetAsTimeStamp();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsDate(const TDBXDate Value);
	virtual void __fastcall SetAsTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXDateValue(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXDateValue() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXCursorValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
public:
	virtual bool __fastcall IsNull();
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXCursorValue(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXCursorValue() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXBooleanValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	System::LongBool FBoolean;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual bool __fastcall IsNull();
	virtual bool __fastcall GetBoolean()/* overload */;
	virtual void __fastcall SetBoolean(const bool Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual bool __fastcall GetAsBoolean();
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual __int64 __fastcall GetAsInt64();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual bool __fastcall EqualsValue(TDBXValue* Other);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXBooleanValue(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXBooleanValue() { }
	
	/* Hoisted overloads: */
	
public:
	inline bool __fastcall  GetBoolean(bool defaultValue){ return TDBXValue::GetBoolean(defaultValue); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTimeValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	TDBXTime FTime;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual bool __fastcall IsNull();
	virtual TDBXTime __fastcall GetTime();
	virtual void __fastcall SetTime(const TDBXTime Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual TDBXTime __fastcall GetAsTime();
	virtual Data::Sqltimst::TSQLTimeStamp __fastcall GetAsTimeStamp();
	virtual System::TDateTime __fastcall GetAsDateTime();
	virtual void __fastcall SetAsDateTime(const System::TDateTime Value);
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsTime(const TDBXTime Value);
	virtual void __fastcall SetAsTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXTimeValue(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXTimeValue() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXWideStringValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	System::UnicodeString FWideString;
	TDBXByteStreamReader* FOverFlowBytes;
	virtual void __fastcall UpdateType();
	void __fastcall SetOverflowBytes(TDBXByteStreamReader* const OverFlowBytes);
	virtual TDBXStreamReader* __fastcall GetStreamReader();
	
public:
	__fastcall TDBXWideStringValue(TDBXValueType* ValueType);
	__fastcall virtual ~TDBXWideStringValue();
	virtual bool __fastcall IsNull();
	virtual System::UnicodeString __fastcall GetWideString()/* overload */;
	virtual System::UnicodeString __fastcall GetAsString();
	virtual bool __fastcall GetAsBoolean();
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual __int64 __fastcall GetAsInt64();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual TDBXDate __fastcall GetAsDate();
	virtual TDBXTime __fastcall GetAsTime();
	virtual Data::Sqltimst::TSQLTimeStamp __fastcall GetAsTimeStamp();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetAsDate(const TDBXDate Value);
	virtual void __fastcall SetAsTime(const TDBXTime Value);
	virtual void __fastcall SetAsTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual bool __fastcall EqualsValue(TDBXValue* Other);
	virtual short __fastcall Compare(TDBXValue* Other);
	/* Hoisted overloads: */
	
public:
	inline System::UnicodeString __fastcall  GetWideString(System::UnicodeString defaultValue){ return TDBXValue::GetWideString(defaultValue); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXInt8Value : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	System::Int8 FInt8;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual System::Int8 __fastcall GetInt8()/* overload */;
	virtual bool __fastcall IsNull();
	virtual void __fastcall SetInt8(const System::Int8 Value);
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual bool __fastcall GetAsBoolean();
	virtual __int64 __fastcall GetAsInt64();
	virtual System::UnicodeString __fastcall GetAsString();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXInt8Value(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXInt8Value() { }
	
	/* Hoisted overloads: */
	
public:
	inline System::Int8 __fastcall  GetInt8(System::Int8 defaultValue){ return TDBXValue::GetInt8(defaultValue); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXUInt8Value : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	System::Byte FUInt8;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual System::Byte __fastcall GetUInt8()/* overload */;
	virtual bool __fastcall IsNull();
	virtual void __fastcall SetUInt8(const System::Byte Value);
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual bool __fastcall GetAsBoolean();
	virtual __int64 __fastcall GetAsInt64();
	virtual System::UnicodeString __fastcall GetAsString();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXUInt8Value(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXUInt8Value() { }
	
	/* Hoisted overloads: */
	
public:
	inline System::Byte __fastcall  GetUInt8(System::Byte defaultValue){ return TDBXValue::GetUInt8(defaultValue); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXInt16Value : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	short FInt16;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual short __fastcall GetInt16()/* overload */;
	virtual bool __fastcall IsNull();
	virtual void __fastcall SetInt16(const short Value);
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual bool __fastcall GetAsBoolean();
	virtual __int64 __fastcall GetAsInt64();
	virtual System::UnicodeString __fastcall GetAsString();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXInt16Value(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXInt16Value() { }
	
	/* Hoisted overloads: */
	
public:
	inline short __fastcall  GetInt16(short defaultValue){ return TDBXValue::GetInt16(defaultValue); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXUInt16Value : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	System::Word FUInt16;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual System::Word __fastcall GetUInt16()/* overload */;
	virtual bool __fastcall IsNull();
	virtual void __fastcall SetUInt16(const System::Word Value);
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual bool __fastcall GetAsBoolean();
	virtual __int64 __fastcall GetAsInt64();
	virtual System::UnicodeString __fastcall GetAsString();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXUInt16Value(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXUInt16Value() { }
	
	/* Hoisted overloads: */
	
public:
	inline System::Word __fastcall  GetUInt16(System::Word defaultValue){ return TDBXValue::GetUInt16(defaultValue); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXInt32Value : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	int FInt32;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual bool __fastcall IsNull();
	virtual int __fastcall GetInt32()/* overload */;
	virtual void __fastcall SetInt32(const int Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual bool __fastcall GetAsBoolean();
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual __int64 __fastcall GetAsInt64();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual TDBXTime __fastcall GetAsTime();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetAsTime(const TDBXTime Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual bool __fastcall EqualsValue(TDBXValue* Other);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXInt32Value(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXInt32Value() { }
	
	/* Hoisted overloads: */
	
public:
	inline int __fastcall  GetInt32(int defaultValue){ return TDBXValue::GetInt32(defaultValue); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXInt64Value : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	__int64 FInt64;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual bool __fastcall IsNull();
	virtual __int64 __fastcall GetInt64()/* overload */;
	virtual void __fastcall SetInt64(const __int64 Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual bool __fastcall GetAsBoolean();
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual __int64 __fastcall GetAsInt64();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
	virtual bool __fastcall EqualsValue(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXInt64Value(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXInt64Value() { }
	
	/* Hoisted overloads: */
	
public:
	inline __int64 __fastcall  GetInt64(__int64 defaultValue){ return TDBXValue::GetInt64(defaultValue); }
	
};


class PASCALIMPLEMENTATION TDBXDoubleValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	double FDouble;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual bool __fastcall IsNull();
	virtual double __fastcall GetDouble();
	virtual void __fastcall SetDouble(const double Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual bool __fastcall GetAsBoolean();
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual __int64 __fastcall GetAsInt64();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXDoubleValue(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXDoubleValue() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXSingleValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	float FSingle;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual bool __fastcall IsNull();
	virtual float __fastcall GetSingle();
	virtual void __fastcall SetSingle(const float Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual bool __fastcall GetAsBoolean();
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual __int64 __fastcall GetAsInt64();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXSingleValue(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXSingleValue() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXBcdValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	Data::Fmtbcd::TBcd FBcd;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual bool __fastcall IsNull();
	virtual Data::Fmtbcd::TBcd __fastcall GetBcd();
	virtual void __fastcall SetBcd(const Data::Fmtbcd::TBcd &Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual bool __fastcall GetAsBoolean();
	virtual System::Byte __fastcall GetAsUInt8();
	virtual System::Int8 __fastcall GetAsInt8();
	virtual System::Word __fastcall GetAsUInt16();
	virtual short __fastcall GetAsInt16();
	virtual int __fastcall GetAsInt32();
	virtual __int64 __fastcall GetAsInt64();
	virtual float __fastcall GetAsSingle();
	virtual double __fastcall GetAsDouble();
	virtual Data::Fmtbcd::TBcd __fastcall GetAsBcd();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsBoolean(const bool Value);
	virtual void __fastcall SetAsUInt8(const System::Byte Value);
	virtual void __fastcall SetAsInt8(const System::Int8 Value);
	virtual void __fastcall SetAsUInt16(const System::Word Value);
	virtual void __fastcall SetAsInt16(const short Value);
	virtual void __fastcall SetAsInt32(const int Value);
	virtual void __fastcall SetAsInt64(const __int64 Value);
	virtual void __fastcall SetAsSingle(const float Value);
	virtual void __fastcall SetAsDouble(const double Value);
	virtual void __fastcall SetAsBcd(const Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXBcdValue(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXBcdValue() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXByteArrayValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	int FNullGeneration;
	System::TArray__1<System::Byte> FBytes;
	__int64 FByteLength;
	__int64 FOffset;
	__int64 FBufferOffset;
	TDBXStreamReader* FOverFlowBytes;
	virtual void __fastcall SetRowValue()/* overload */;
	void __fastcall SetOverflowBytes(TDBXStreamReader* const OverFlowBytes);
	virtual TDBXStreamReader* __fastcall GetStreamReader();
	
public:
	__fastcall TDBXByteArrayValue(TDBXValueType* ValueType);
	__fastcall virtual ~TDBXByteArrayValue();
	virtual bool __fastcall IsNull();
	virtual __int64 __fastcall GetBytes(__int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length)/* overload */;
	virtual __int64 __fastcall GetValueSize();
	virtual void __fastcall SetStaticBytes(__int64 Offset, const System::Byte *Buffer, const int Buffer_High, __int64 BufferOffset, __int64 Length);
	virtual void __fastcall SetDynamicBytes(__int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXStreamReader : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Size) = 0 ;
	virtual bool __fastcall Eos() = 0 ;
	virtual __int64 __fastcall Size() = 0 ;
	virtual void __fastcall Close() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDBXStreamReader() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXStreamReader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXLookAheadStreamReader : public TDBXStreamReader
{
	typedef TDBXStreamReader inherited;
	
private:
	System::Classes::TStream* FStream;
	bool FEOS;
	bool FHasLookAheadByte;
	System::Byte FLookAheadByte;
	bool FInstanceOwner;
	System::Classes::TStream* FConvertedStream;
	bool FConvertedStreamOwner;
	
protected:
	System::TArray__1<System::Classes::TStream*> __fastcall ExtractOwnedStreams();
	
public:
	__fastcall virtual ~TDBXLookAheadStreamReader();
	void __fastcall SetStream(System::Classes::TStream* const Stream, const bool AInstanceOwner);
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual bool __fastcall Eos();
	virtual __int64 __fastcall Size();
	virtual void __fastcall Close();
	System::Classes::TStream* __fastcall ConvertToMemoryStream();
	__property bool InstanceOwner = {read=FInstanceOwner, write=FInstanceOwner, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXLookAheadStreamReader() : TDBXStreamReader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXByteStreamReader : public TDBXStreamReader
{
	typedef TDBXStreamReader inherited;
	
private:
	System::TArray__1<System::Byte> FBytes;
	int FOffset;
	int FCount;
	int FPosition;
	bool FEOS;
	
public:
	__fastcall TDBXByteStreamReader(System::TArray__1<System::Byte> Bytes, int Offset, int Count);
	__fastcall virtual ~TDBXByteStreamReader();
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual bool __fastcall Eos();
	virtual __int64 __fastcall Size();
	virtual void __fastcall Close();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXStreamValue : public TDBXByteArrayValue
{
	typedef TDBXByteArrayValue inherited;
	
private:
	TDBXLookAheadStreamReader* FStreamStreamReader;
	TDBXByteStreamReader* FByteStreamReader;
	bool FExtendedType;
	int FLastSize;
	bool FInstanceOwner;
	System::Classes::TStream* FLastReadStream;
	System::Generics::Collections::TObjectList__1<System::TObject*>* FFreeList;
	System::Generics::Collections::TList__1<System::Classes::TStream*>* FOwnedStreams;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	virtual TDBXStreamReader* __fastcall GetStreamReader();
	void __fastcall FreeLastReadStream();
	
protected:
	virtual void __fastcall SetAsVariant(const System::OleVariant &Value);
	
public:
	__fastcall TDBXStreamValue(TDBXValueType* ValueType);
	virtual void __fastcall UpdateType();
	virtual void __fastcall SetNull();
	__fastcall virtual ~TDBXStreamValue();
	virtual System::Classes::TStream* __fastcall GetStream(bool AInstanceOwner)/* overload */;
	virtual TDBXJSONStream* __fastcall GetJSONStream(bool AInstanceOwner)/* overload */;
	virtual System::Classes::TStream* __fastcall GetStream()/* overload */;
	virtual __int64 __fastcall GetValueSize();
	virtual void __fastcall SetDynamicBytes(__int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Count);
	virtual void __fastcall SetStream(System::Classes::TStream* const Stream, const bool AInstanceOwner);
	virtual void __fastcall SetJSONStream(TDBXJSONStream* const Value, bool AInstanceOwner);
	virtual void __fastcall SetValue(TDBXValue* const Value);
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXWideCharsValue : public TDBXWideStringValue
{
	typedef TDBXWideStringValue inherited;
	
private:
	int FCount;
	Data::Dbxplatform::TDBXWideChars FWideChars;
	System::UnicodeString FRefValue;
	virtual void __fastcall UpdateType();
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
protected:
	__property int WideCharsCount = {read=FCount, nodefault};
	__property Data::Dbxplatform::TDBXWideChars WideChars = {read=FWideChars};
	
public:
	__fastcall TDBXWideCharsValue(TDBXValueType* ValueType);
	__fastcall virtual ~TDBXWideCharsValue();
	virtual bool __fastcall IsNull();
	virtual void __fastcall SetWideString(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetWideString()/* overload */;
	virtual System::Classes::TStream* __fastcall GetStream(bool AInstanceOwner)/* overload */;
	virtual __int64 __fastcall GetValueSize();
	virtual __int64 __fastcall GetBytes(__int64 Offset, const System::TArray__1<System::Byte> Value, __int64 BufferOffset, __int64 Length)/* overload */;
	virtual void __fastcall SetDynamicBytes(__int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
	virtual short __fastcall Compare(TDBXValue* Other);
	/* Hoisted overloads: */
	
public:
	inline System::UnicodeString __fastcall  GetWideString(System::UnicodeString defaultValue){ return TDBXValue::GetWideString(defaultValue); }
	inline System::Classes::TStream* __fastcall  GetStream(){ return TDBXValue::GetStream(); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXStringValue : public TDBXWideStringValue
{
	typedef TDBXWideStringValue inherited;
	
private:
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	__fastcall TDBXStringValue(TDBXValueType* ValueType);
	__fastcall virtual ~TDBXStringValue();
	virtual bool __fastcall IsNull();
	virtual System::UnicodeString __fastcall GetWideString()/* overload */;
	virtual void __fastcall SetWideString(const System::UnicodeString Value);
	/* Hoisted overloads: */
	
public:
	inline System::UnicodeString __fastcall  GetWideString(System::UnicodeString defaultValue){ return TDBXValue::GetWideString(defaultValue); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXAnsiCharsValue : public TDBXAnsiStringValue
{
	typedef TDBXAnsiStringValue inherited;
	
private:
	int FCount;
	System::TArray__1<System::Byte> FBytes;
	System::TArray__1<System::Byte> FRefValue;
	virtual void __fastcall UpdateType();
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	__fastcall TDBXAnsiCharsValue(TDBXValueType* ValueType);
	virtual bool __fastcall IsNull();
	virtual void __fastcall SetAnsiString(const System::AnsiString Value);
	virtual System::AnsiString __fastcall GetAnsiString();
	virtual System::Classes::TStream* __fastcall GetStream(bool AInstanceOwner)/* overload */;
	virtual __int64 __fastcall GetValueSize();
	virtual __int64 __fastcall GetBytes(__int64 Offset, const System::TArray__1<System::Byte> Value, __int64 BufferOffset, __int64 Length)/* overload */;
	virtual void __fastcall SetStaticBytes(__int64 Offset, const System::Byte *Buffer, const int Buffer_High, __int64 BufferOffset, __int64 Length);
	virtual void __fastcall SetDynamicBytes(__int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
public:
	/* TDBXAnsiStringValue.Destroy */ inline __fastcall virtual ~TDBXAnsiCharsValue() { }
	
	/* Hoisted overloads: */
	
public:
	inline System::Classes::TStream* __fastcall  GetStream(){ return TDBXValue::GetStream(); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTimeStampValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	Data::Sqltimst::TSQLTimeStamp FTimeStamp;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual bool __fastcall IsNull();
	virtual Data::Sqltimst::TSQLTimeStamp __fastcall GetTimeStamp();
	virtual void __fastcall SetTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual TDBXDate __fastcall GetAsDate();
	virtual TDBXTime __fastcall GetAsTime();
	virtual Data::Sqltimst::TSQLTimeStamp __fastcall GetAsTimeStamp();
	virtual System::TDateTime __fastcall GetAsDateTime();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetAsDate(const TDBXDate Value);
	virtual void __fastcall SetAsTime(const TDBXTime Value);
	virtual void __fastcall SetAsTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetAsDateTime(const System::TDateTime Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual short __fastcall Compare(TDBXValue* Other);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXTimeStampValue(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXTimeStampValue() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTimeStampOffsetValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	Data::Sqltimst::TSQLTimeStampOffset FTimeStampOffset;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	virtual bool __fastcall IsNull();
	virtual Data::Sqltimst::TSQLTimeStampOffset __fastcall GetTimeStampOffset();
	virtual void __fastcall SetTimeStampOffset(const Data::Sqltimst::TSQLTimeStampOffset &Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXTimeStampOffsetValue(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	/* TDBXWritableValue.Destroy */ inline __fastcall virtual ~TDBXTimeStampOffsetValue() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXReaderValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	TDBXReader* FDBXReader;
	bool FRowReader;
	int FHandle;
	bool FInstanceOwner;
	int FMaxRows;
	virtual void __fastcall SetRowValue()/* overload */;
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
protected:
	virtual int __fastcall GetHandle();
	virtual void __fastcall SetHandle(const int Handle);
	
public:
	__fastcall virtual ~TDBXReaderValue();
	virtual bool __fastcall IsNull();
	virtual TDBXReader* __fastcall GetDBXReader()/* overload */;
	virtual TDBXReader* __fastcall GetDBXReader(bool AInstanceOwner)/* overload */;
	virtual void __fastcall SetDBXReader(TDBXReader* const Value, const bool AInstanceOwner)/* overload */;
	virtual int __fastcall GetMaxRows();
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual void __fastcall SetNull();
	__property int Handle = {read=GetHandle, write=SetHandle, nodefault};
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXReaderValue(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXConnectionValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	TDBXConnection* FDBXConnection;
	virtual void __fastcall SetRowValue()/* overload */;
	
public:
	__fastcall virtual ~TDBXConnectionValue();
	virtual bool __fastcall IsNull();
	virtual TDBXConnection* __fastcall GetDBXConnection();
	virtual void __fastcall SetDBXConnection(TDBXConnection* const Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
public:
	/* TDBXWritableValue.Create */ inline __fastcall TDBXConnectionValue(TDBXValueType* ValueType) : TDBXWritableValue(ValueType) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXContext : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDBXErrorEvent FOnError;
	TDBXTraceEvent FOnTrace;
	int FTraceFlags;
	int FTraceLevel;
	TDBXByteReader* FClosedByteReader;
	TDBXFormatter* FDBXFormatter;
	void __fastcall SetOnError(const TDBXErrorEvent Value);
	void __fastcall SetOnTrace(const TDBXTraceEvent Value);
	void __fastcall SetTraceFlags(const int Value);
	void __fastcall SetTraceLevel(const int Value);
	void __fastcall SetDBXFormatter(TDBXFormatter* const DBXFormatter);
	
protected:
	TDBXContext* FOnErrorDBXContext;
	TDBXContext* FOnTraceDBXContext;
	Data::Dbcommontypes::CBRType __fastcall Trace(int TraceLevel, int TraceFlag, System::UnicodeString CustomCategory, System::UnicodeString TraceMessage)/* overload */;
	__fastcall TDBXContext(TDBXContext* DBXContext)/* overload */;
	
public:
	__fastcall TDBXContext()/* overload */;
	__fastcall virtual ~TDBXContext();
	bool __fastcall IsTracingLevel(int TraceLevel);
	bool __fastcall IsTracing(int TraceFlags);
	bool __fastcall IsTracingCategory(System::UnicodeString Category);
	Data::Dbcommontypes::CBRType __fastcall Trace(int TraceFlag, System::UnicodeString TraceMessage)/* overload */;
	Data::Dbcommontypes::CBRType __fastcall Trace(int TraceLevel, int TraceFlag, System::UnicodeString TraceMessage)/* overload */;
	Data::Dbcommontypes::CBRType __fastcall Trace(int TraceLevel, System::UnicodeString CustomCategory, System::UnicodeString TraceMessage)/* overload */;
#ifndef __aarch64__
	void __fastcall Error(int ErrorCode, System::UnicodeString ErrorMessage)/* overload */;
	void __fastcall Error(int ErrorCode, System::UnicodeString ErrorMessage, System::Sysutils::Exception* InnerException)/* overload */;
#else /* __aarch64__ */
	void __fastcall Error(long ErrorCode, System::UnicodeString ErrorMessage)/* overload */;
	void __fastcall Error(long ErrorCode, System::UnicodeString ErrorMessage, System::Sysutils::Exception* InnerException)/* overload */;
#endif /* __aarch64__ */
	__property TDBXErrorEvent OnError = {read=FOnError, write=SetOnError};
	__property TDBXTraceEvent OnTrace = {read=FOnTrace, write=SetOnTrace};
	__property int TraceFlags = {read=FTraceFlags, write=SetTraceFlags, nodefault};
	__property int TraceLevel = {read=FTraceLevel, write=SetTraceLevel, nodefault};
	__property TDBXByteReader* ClosedByteReader = {read=FClosedByteReader};
	__property TDBXFormatter* DBXFormatter = {read=FDBXFormatter, write=SetDBXFormatter};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXByteReader : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	TDBXContext* FDBXContext;
	
protected:
	__fastcall TDBXByteReader(TDBXContext* DBXContext);
	
public:
	virtual void __fastcall GetAnsiString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetWideString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetUInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetUInt16(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetInt16(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetInt32(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetInt64(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetSingle(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetDouble(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetBcd(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetTimeStamp(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetTimeStampOffset(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetTime(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetDate(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetByteLength(int Ordinal, __int64 &Length, System::LongBool &IsNull) = 0 ;
	virtual __int64 __fastcall GetBytes(int Ordinal, __int64 Offset, const System::TArray__1<System::Byte> Value, __int64 ValueOffset, __int64 Length, System::LongBool &IsNull) = 0 ;
	virtual void __fastcall GetBoolean(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXByteReader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXReaderByteReader : public TDBXByteReader
{
	typedef TDBXByteReader inherited;
	
private:
	TDBXReader* FDbxReader;
	
public:
	__fastcall TDBXReaderByteReader(TDBXContext* DBXContext, TDBXReader* DbxReader);
	virtual void __fastcall GetAnsiString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetWideString(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetUInt16(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt16(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt32(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetInt64(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetSingle(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetDouble(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetBcd(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStamp(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStampOffset(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetTime(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetDate(int Ordinal, const System::TArray__1<System::Byte> Value, int Offset, System::LongBool &IsNull);
	virtual void __fastcall GetByteLength(int Ordinal, __int64 &Length, System::LongBool &IsNull);
	virtual __int64 __fastcall GetBytes(int Ordinal, __int64 Offset, const System::TArray__1<System::Byte> Value, __int64 ValueOffset, __int64 Length, System::LongBool &IsNull);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXReaderByteReader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXValueTypeList : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<TDBXValueType*> _TDBXValueTypeList__1;
	
	
public:
	TDBXValueType* operator[](const int Ordinal) { return this->Values[Ordinal]; }
	
private:
	_TDBXValueTypeList__1 FValueTypeArray;
	int FLastOrdinal;
	virtual int __fastcall FindOrdinal(const System::UnicodeString Name, int StartOrdinal, int EndOrdinal);
	
private:
	TDBXValueType* __fastcall GetValueType(const int Ordinal);
	virtual int __fastcall GetOrdinal(const System::UnicodeString Name);
	void __fastcall SetCount(const int Count);
	int __fastcall GetCount();
	void __fastcall Add(TDBXValueType* ValueType);
	void __fastcall Insert(int Ordinal, TDBXValueType* ValueType);
	void __fastcall Remove(TDBXValueType* ValueType)/* overload */;
	void __fastcall Remove(int Ordinal)/* overload */;
	void __fastcall SetValueType(const int Ordinal, TDBXValueType* ValueType);
	void __fastcall Clear();
	void __fastcall RemoveAll();
	__property int Count = {read=GetCount, nodefault};
	__property TDBXValueType* Values[const int Ordinal] = {read=GetValueType/*, default*/};
	
public:
	__fastcall virtual ~TDBXValueTypeList();
public:
	/* TObject.Create */ inline __fastcall TDBXValueTypeList() : System::TObject() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDriverHelp : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static TDBXParameter* __fastcall CreateTDBXParameter(TDBXContext* DBXContext);
	static TDBXValueType* __fastcall CreateTDBXValueType(TDBXContext* DBXContext)/* overload */;
	static TDBXValueType* __fastcall CreateTDBXValueType(TDBXContext* DBXContext, TDBXRow* DBXRow)/* overload */;
	static TDBXProperties* __fastcall CreateTDBXProperties(TDBXContext* DBXContext);
	static TDBXContext* __fastcall CreateTDBXContext();
	static TDBXStreamReader* __fastcall GetStreamReader(TDBXValue* Value)/* overload */;
	__classmethod void __fastcall UpdateParameterType(TDBXParameter* Parameter);
	static bool __fastcall IsReadOnlyValueType(TDBXValueType* ValueType);
	__classmethod void __fastcall SetPendingValue(TDBXWritableValue* Value);
	static TDBXValue* __fastcall GetNonDelegate(TDBXValue* Value);
	static void __fastcall SetOverflowBytes(TDBXByteArrayValue* Value, TDBXByteStreamReader* streamReader)/* overload */;
	static void __fastcall SetOverflowBytes(TDBXWideStringValue* Value, TDBXByteStreamReader* streamReader)/* overload */;
	static void __fastcall SetOverflowBytes(TDBXAnsiStringValue* Value, TDBXByteStreamReader* streamReader)/* overload */;
	static bool __fastcall HasOverflowBytes(TDBXWritableValue* Value);
	static void __fastcall CopyRowValue(TDBXValue* Value, TDBXRow* DBXRow);
	static TDBXConnection* __fastcall GetConnection(TDBXConnectionFactory* ConnectionFactory, TDBXContext* DBXContext, System::UnicodeString ConnectionName);
	static void __fastcall SetMetaDataReader(TDBXConnection* Connection, System::TObject* MetaDataReader);
	static System::TObject* __fastcall GetMetaDataReader(TDBXConnection* Connection);
public:
	/* TObject.Create */ inline __fastcall TDBXDriverHelp() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDriverHelp() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDriverLoader : public Data::Dbxclassregistry::TClassRegistryObject
{
	typedef Data::Dbxclassregistry::TClassRegistryObject inherited;
	
protected:
	System::UnicodeString FLoaderName;
	
public:
	virtual TDBXDriver* __fastcall Load(const TDBXDriverDef &DriverDef) = 0 ;
public:
	/* TClassRegistryObject.Create */ inline __fastcall virtual TDBXDriverLoader() : Data::Dbxclassregistry::TClassRegistryObject() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDriverLoader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TDBXDriverLoaderClass);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDriverRegistry : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TDBXDriverLoader*>* FDriverLoaders;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TDBXDriverClass>* FDriverClasses;
	int FCounter;
	System::Generics::Collections::TThreadList__1<TDBXDriver*>* FDrivers;
	static TDBXDriverRegistry* DBXDriverRegistry;
	int __fastcall FindDriver(System::Generics::Collections::TList__1<TDBXDriver*>* List, const System::UnicodeString DriverName);
	void __fastcall FreeAllDrivers(TDBXDriverLoader* Loader);
	void __fastcall FreeAllLoaders();
	void __fastcall InternalRegisterLoader(const System::UnicodeString LoaderClassName, TDBXDriverLoader* Loader);
	void __fastcall LoadMetaDataCommandFactory(TDBXDriver* Driver);
	TDBXDriver* __fastcall LoadDriver(const TDBXDriverDef &DriverDef, System::Generics::Collections::TList__1<TDBXDriver*>* List);
	TDBXDriver* __fastcall GetDriver(const TDBXDriverDef &DriverDef);
	void __fastcall DriverLoadError(const TDBXDriverDef &DriverDef, System::UnicodeString PackageName);
	void __fastcall FreeDriver(TDBXDriver* Driver);
	void __fastcall CloseAllDrivers();
	void __fastcall GetRegisteredDriverNames(System::Classes::TStringList* DriverNameList);
	void __fastcall GetRegisteredDriverLoaderNames(System::Classes::TStringList* DriverLoaderNameList);
	void __fastcall GetRegisteredDriverClassNames(System::Classes::TStringList* DriverClassNameList);
	
public:
	__fastcall TDBXDriverRegistry();
	__fastcall virtual ~TDBXDriverRegistry();
	static void __fastcall RegisterDriverClass(System::UnicodeString DriverName, TDBXDriverClass DriverClass);
	static void __fastcall UnregisterDriverClass(System::UnicodeString DriverName);
	static void __fastcall UnloadDriver(System::UnicodeString DriverName);
	static void __fastcall RegisterDriver(System::UnicodeString DriverName, TDBXDriver* Driver);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDelegateDriver : public TDBXDriver
{
	typedef TDBXDriver inherited;
	
private:
	TDBXDriver* FDriver;
	
protected:
	virtual TDBXProperties* __fastcall GetDriverProperties();
	virtual void __fastcall InitDriverProperties(TDBXProperties* const DriverProperties);
	virtual System::UnicodeString __fastcall GetDriverName();
	virtual void __fastcall SetDriverName(const System::UnicodeString DriverName);
	virtual TDBXConnection* __fastcall CreateConnection(TDBXConnectionBuilder* ConnectionBuilder);
	virtual void __fastcall Close();
	virtual TDBXCommand* __fastcall CreateMorphCommand(TDBXContext* DbxContext, TDBXConnection* Connection, TDBXCommand* MorphicCommand);
	
public:
	__fastcall TDBXDelegateDriver(TDBXDriver* Driver);
	__fastcall virtual ~TDBXDelegateDriver();
	virtual System::TClass __fastcall GetDriverClass();
	virtual System::UnicodeString __fastcall GetDriverVersion();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDelegateItem : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	void __fastcall FreeProperties();
	
public:
	System::UnicodeString FName;
	TDBXProperties* FProperties;
	TDBXDelegateItem* FNext;
	__fastcall virtual ~TDBXDelegateItem();
public:
	/* TObject.Create */ inline __fastcall TDBXDelegateItem() : System::TObject() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXPropertiesItem : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TDBXProperties* FProperties;
	TDBXDelegateItem* FDeletgatePath;
	__fastcall TDBXPropertiesItem(TDBXProperties* Properties);
	__fastcall virtual ~TDBXPropertiesItem();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXConnectionBuilder : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDBXProperties* FInputConnectionProperties;
	System::UnicodeString FInputConnectionName;
	System::UnicodeString FInputUserName;
	System::UnicodeString FInputPassword;
	TDBXConnectionFactory* FConnectionFactory;
	TDBXDelegateItem* FDelegatePath;
	TDBXContext* FDBXContext;
	TDBXDelegateDriver* FDelegateDriver;
	TDBXProperties* __fastcall GetConnectionProperties();
	System::UnicodeString __fastcall GetDelegationSignature();
	void __fastcall Assign(TDBXConnectionBuilder* Source);
	TDBXConnection* __fastcall CreateConnection();
	
protected:
	__fastcall TDBXConnectionBuilder()/* overload */;
	__fastcall TDBXConnectionBuilder(TDBXConnectionBuilder* Source)/* overload */;
	
public:
	__fastcall virtual ~TDBXConnectionBuilder();
	TDBXConnection* __fastcall CreateDelegateeConnection();
	__property TDBXProperties* ConnectionProperties = {read=GetConnectionProperties};
	__property System::UnicodeString DelegationSignature = {read=GetDelegationSignature};
	__property TDBXProperties* InputConnectionProperties = {read=FInputConnectionProperties};
	__property System::UnicodeString InputConnectionName = {read=FInputConnectionName};
	__property System::UnicodeString InputUserName = {read=FInputUserName};
	__property System::UnicodeString InputPassword = {read=FInputPassword};
	__property TDBXContext* DbxContext = {read=FDBXContext};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXAnsiMemoValue : public TDBXByteArrayValue
{
	typedef TDBXByteArrayValue inherited;
	
private:
	void __fastcall GetFBytes();
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	__fastcall TDBXAnsiMemoValue(TDBXValueType* ValueType);
	__fastcall virtual ~TDBXAnsiMemoValue();
	virtual bool __fastcall IsNull();
	virtual System::AnsiString __fastcall GetAnsiString();
	virtual void __fastcall SetAnsiString(const System::AnsiString Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
};


class PASCALIMPLEMENTATION TDBXWideMemoValue : public TDBXByteArrayValue
{
	typedef TDBXByteArrayValue inherited;
	
private:
	void __fastcall GetFBytes();
	virtual void __fastcall CopyRowValue(TDBXRow* Row)/* overload */;
	
public:
	__fastcall TDBXWideMemoValue(TDBXValueType* ValueType);
	__fastcall virtual ~TDBXWideMemoValue();
	virtual bool __fastcall IsNull();
	virtual System::UnicodeString __fastcall GetWideString()/* overload */;
	virtual void __fastcall SetWideString(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetAsString();
	virtual void __fastcall SetAsString(const System::UnicodeString Value);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	/* Hoisted overloads: */
	
public:
	inline System::UnicodeString __fastcall  GetWideString(System::UnicodeString defaultValue){ return TDBXValue::GetWideString(defaultValue); }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXRow : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	TDBXContext* FDBXContext;
	__property TDBXContext* DBXContext = {read=FDBXContext};
	
protected:
	int FGeneration;
	virtual void __fastcall NotImplemented();
	virtual void __fastcall GetAnsiString(TDBXAnsiStringValue* DbxValue, char * &AnsiStringBuilder, System::LongBool &IsNull);
	virtual void __fastcall GetWideString(TDBXWideStringValue* DbxValue, System::WideChar * &WideStringBuilder, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetWideString(TDBXWideStringValue* DbxValue, System::UnicodeString &Value, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetBoolean(TDBXBooleanValue* DbxValue, System::LongBool &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt8(TDBXUInt8Value* DbxValue, System::Byte &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt8(TDBXInt8Value* DbxValue, System::Int8 &Value, System::LongBool &IsNull);
	virtual void __fastcall GetUInt16(TDBXUInt16Value* DbxValue, System::Word &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt16(TDBXInt16Value* DbxValue, short &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt32(TDBXInt32Value* DbxValue, int &Value, System::LongBool &IsNull);
	virtual void __fastcall GetInt64(TDBXInt64Value* DbxValue, __int64 &Value, System::LongBool &IsNull);
	virtual void __fastcall GetSingle(TDBXSingleValue* DbxValue, float &Value, System::LongBool &IsNull);
	virtual void __fastcall GetDouble(TDBXDoubleValue* DbxValue, double &Value, System::LongBool &IsNull);
	virtual void __fastcall GetBcd(TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value, System::LongBool &IsNull);
	virtual void __fastcall GetDate(TDBXDateValue* DbxValue, TDBXDate &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTime(TDBXTimeValue* DbxValue, TDBXTime &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStamp(TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value, System::LongBool &IsNull);
	virtual void __fastcall GetTimeStampOffset(TDBXTimeStampOffsetValue* DbxValue, Data::Sqltimst::TSQLTimeStampOffset &Value, System::LongBool &IsNull);
	virtual void __fastcall GetBytes(TDBXByteArrayValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length, __int64 &ReturnLength, System::LongBool &IsNull);
	virtual void __fastcall GetByteLength(TDBXByteArrayValue* DbxValue, __int64 &ByteLength, System::LongBool &IsNull);
	virtual void __fastcall GetDBXReader(TDBXReaderValue* DbxValue, TDBXReader* &Value, System::LongBool &IsNull);
	virtual void __fastcall GetDBXConnection(TDBXConnectionValue* DbxValue, TDBXConnection* &Value, System::LongBool &IsNull);
	virtual void __fastcall GetJSONValue(TDBXJSONValue* DbxValue, System::Json::TJSONValue* &Value, System::LongBool &IsNull);
	virtual void __fastcall SetJSONValue(TDBXJSONValue* DbxValue, System::Json::TJSONValue* Value);
	virtual void __fastcall GetCallbackValue(TDBXCallbackValue* DbxValue, Data::Dbxjson::TDBXCallback* &Value, System::LongBool &IsNull);
	virtual void __fastcall SetCallbackValue(TDBXCallbackValue* DbxValue, Data::Dbxjson::TDBXCallback* Value);
	virtual bool __fastcall IsStoredNull(TDBXValue* DbxValue);
	virtual void __fastcall SetNull(TDBXValue* DbxValue);
	virtual void __fastcall SetString(TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetAnsiString(TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetWideString(TDBXWideStringValue* DbxValue, const System::UnicodeString Value);
	virtual void __fastcall SetBoolean(TDBXBooleanValue* DbxValue, bool Value);
	virtual void __fastcall SetUInt8(TDBXUInt8Value* DbxValue, System::Byte Value);
	virtual void __fastcall SetInt8(TDBXInt8Value* DbxValue, System::Int8 Value);
	virtual void __fastcall SetUInt16(TDBXUInt16Value* DbxValue, System::Word Value);
	virtual void __fastcall SetInt16(TDBXInt16Value* DbxValue, short Value);
	virtual void __fastcall SetInt32(TDBXInt32Value* DbxValue, int Value);
	virtual void __fastcall SetInt64(TDBXInt64Value* DbxValue, __int64 Value);
	virtual void __fastcall SetSingle(TDBXSingleValue* DbxValue, float Value);
	virtual void __fastcall SetDouble(TDBXDoubleValue* DbxValue, double Value);
	virtual void __fastcall SetBCD(TDBXBcdValue* DbxValue, Data::Fmtbcd::TBcd &Value);
	virtual void __fastcall SetDate(TDBXDateValue* DbxValue, TDBXDate Value);
	virtual void __fastcall SetTime(TDBXTimeValue* DbxValue, TDBXTime Value);
	virtual void __fastcall SetTimestamp(TDBXTimeStampValue* DbxValue, Data::Sqltimst::TSQLTimeStamp &Value);
	virtual void __fastcall SetTimestampOffset(TDBXTimeStampOffsetValue* DbxValue, Data::Sqltimst::TSQLTimeStampOffset &Value);
	virtual void __fastcall SetDynamicBytes(TDBXValue* DbxValue, __int64 Offset, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length);
	virtual System::UnicodeString __fastcall GetObjectTypeName(int Ordinal);
	virtual void __fastcall SetValueType(TDBXValueType* ValueType);
	virtual int __fastcall GetGeneration();
	__property int Generation = {read=GetGeneration, nodefault};
	virtual bool __fastcall UseExtendedTypes();
	virtual void __fastcall GetWideChars(TDBXWideStringValue* DbxValue, Data::Dbxplatform::TDBXWideChars &WideChars, int &Count, System::LongBool &IsNull);
	virtual void __fastcall GetAnsiChars(TDBXAnsiStringValue* DbxValue, Data::Dbxplatform::TDBXAnsiChars &AnsiChars, int &Count, System::LongBool &IsNull);
	virtual void __fastcall GetStream(TDBXStreamValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetStream(TDBXWideStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetStream(TDBXAnsiStringValue* DbxValue, System::Classes::TStream* &Stream, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetStreamBytes(TDBXStreamValue* DbxValue, const System::TArray__1<System::Byte> Buffer, __int64 BufferOffset, __int64 Length, __int64 ReturnLength, System::LongBool &IsNull);
	virtual void __fastcall GetStreamLength(TDBXStreamValue* DbxValue, __int64 StreamLength, System::LongBool &IsNull);
	virtual void __fastcall SetWideChars(TDBXWideStringValue* DbxValue, const System::UnicodeString Value);
	virtual void __fastcall SetAnsiChars(TDBXAnsiStringValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetAnsiMemo(TDBXAnsiMemoValue* DbxValue, const System::AnsiString Value);
	virtual void __fastcall SetWideMemo(TDBXWideMemoValue* DbxValue, const System::UnicodeString Value);
	virtual void __fastcall SetStream(TDBXStreamValue* DbxValue, TDBXStreamReader* StreamReader)/* overload */;
	virtual void __fastcall SetDBXReader(TDBXReaderValue* DbxValue, TDBXReader* Value);
	virtual void __fastcall SetDBXConnection(TDBXConnectionValue* DbxValue, TDBXConnection* Value);
	virtual void __fastcall GetLength(TDBXValue* DbxValue, __int64 &ByteLength, System::LongBool &IsNull);
	virtual TDBXValue* __fastcall CreateCustomValue(TDBXValueType* const ValueType);
	virtual void __fastcall ValueSet(TDBXWritableValue* Value);
	virtual void __fastcall ValueNotSet(TDBXWritableValue* const Value);
	__fastcall TDBXRow(TDBXContext* DBXContext);
	
public:
	virtual void __fastcall ClearParameters();
	void __fastcall NewRowGeneration();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXRow() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXCommandFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual TDBXCommand* __fastcall CreateCommand(TDBXContext* DbxContext, TDBXConnection* Connection, TDBXCommand* MorphicCommand) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDBXCommandFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXCommandFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXFormatter : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::UnicodeString __fastcall DateToString(TDBXDateValue* DBXDateValue) = 0 ;
	virtual void __fastcall StringToDate(System::UnicodeString StringValue, TDBXDateValue* DBXDateValue) = 0 ;
	virtual System::UnicodeString __fastcall TimeToString(TDBXTimeValue* DBXTimeValue) = 0 ;
	virtual void __fastcall StringToTime(System::UnicodeString StringValue, TDBXTimeValue* DBXTimeValue) = 0 ;
	virtual System::UnicodeString __fastcall TimestampToString(TDBXTimeStampValue* DBXTimestampValue) = 0 ;
	virtual void __fastcall StringToTimestamp(System::UnicodeString StringValue, TDBXTimeStampValue* DBXTimestampValue) = 0 ;
	virtual System::UnicodeString __fastcall TimestampOffsetToString(TDBXTimeStampOffsetValue* DBXTimestampOffsetValue) = 0 ;
	virtual void __fastcall StringToTimestampOffset(System::UnicodeString StringValue, TDBXTimeStampOffsetValue* DBXTimestampOffsetValue) = 0 ;
	virtual System::UnicodeString __fastcall BcdToString(TDBXBcdValue* DBXBcdValue) = 0 ;
	virtual void __fastcall StringToBcd(System::UnicodeString StringValue, TDBXBcdValue* DBXBcdValue) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDBXFormatter() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXFormatter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
public:
#ifndef __aarch64__
	virtual int __fastcall ReadBytes(const System::TArray__1<System::Byte> Buffer, int Offset, int Count) = 0 ;
	virtual int __fastcall Seek(int Offset, System::Word Origin)/* overload */;
#else /* __aarch64__ */
	virtual long __fastcall ReadBytes(const System::TArray__1<System::Byte> Buffer, long Offset, long Count) = 0 ;
	virtual long __fastcall Seek(long Offset, System::Word Origin)/* overload */;
#endif /* __aarch64__ */
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TDBXStream() : System::Classes::TStream() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXStream() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXStreamReaderStream : public TDBXStream
{
	typedef TDBXStream inherited;
	
private:
	bool FStartedRead;
	System::TArray__1<System::Byte> FBuffer;
	int FOffset;
	TDBXStreamReader* FReader;
	
protected:
	virtual __int64 __fastcall GetSize();
	
public:
#ifndef __aarch64__
	virtual int __fastcall Read(void *Buffer, int Count)/* overload */;
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
	virtual int __fastcall ReadBytes(const System::TArray__1<System::Byte> Buffer, int Offset, int Count);
	virtual int __fastcall Seek(int Offset, System::Word Origin)/* overload */;
#else /* __aarch64__ */
	virtual long __fastcall Read(void *Buffer, long Count)/* overload */;
	virtual long __fastcall Write(const void *Buffer, long Count)/* overload */;
	virtual long __fastcall ReadBytes(const System::TArray__1<System::Byte> Buffer, long Offset, long Count);
	virtual long __fastcall Seek(long Offset, System::Word Origin)/* overload */;
#endif /* __aarch64__ */
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	__fastcall TDBXStreamReaderStream(TDBXStreamReader* Reader, __int64 Size);
	__fastcall virtual ~TDBXStreamReaderStream();
	/* Hoisted overloads: */
	
public:
#ifndef __aarch64__
	inline int __fastcall  Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#else /* __aarch64__ */
	inline long __fastcall  Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Offset, long Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Count){ return System::Classes::TStream::Write(Buffer, Count); }
#endif /* __aarch64__ */
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXBytesStream : public TDBXStream
{
	typedef TDBXStream inherited;
	
private:
	System::TArray__1<System::Byte> FBuffer;
	int FOffset;
	int FSize;
	
protected:
	virtual __int64 __fastcall GetSize();
	
public:
#ifndef __aarch64__
	virtual int __fastcall Read(void *Buffer, int Count)/* overload */;
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
	virtual int __fastcall ReadBytes(const System::TArray__1<System::Byte> Buffer, int Offset, int Count);
#else /* __aarch64__ */
	virtual long __fastcall Read(void *Buffer, long Count)/* overload */;
	virtual long __fastcall Write(const void *Buffer, long Count)/* overload */;
	virtual long __fastcall ReadBytes(const System::TArray__1<System::Byte> Buffer, long Offset, long Count);
#endif /* __aarch64__ */
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	__fastcall TDBXBytesStream(System::TArray__1<System::Byte> Bytes, __int64 Size);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXBytesStream() { }
	
	/* Hoisted overloads: */
	
public:
#ifndef __aarch64__
	inline int __fastcall  Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
	inline int __fastcall  Seek(int Offset, System::Word Origin){ return TDBXStream::Seek(Offset, Origin); }
#else /* __aarch64__ */
	inline long __fastcall  Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Offset, long Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Count){ return System::Classes::TStream::Write(Buffer, Count); }
	inline long __fastcall  Seek(long Offset, System::Word Origin){ return TDBXStream::Seek(Offset, Origin); }
#endif /* __aarch64__ */
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXJSONValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	System::Json::TJSONValue* FJsonValue;
	bool FInstanceOwner;
	
public:
	__fastcall TDBXJSONValue(TDBXValueType* const ValueType);
	__fastcall virtual ~TDBXJSONValue();
	virtual void __fastcall SetRowValue()/* overload */;
	virtual int __fastcall EstimatedByteSize();
	virtual int __fastcall ToBytes(const System::TArray__1<System::Byte> Data, const int Offset);
	virtual System::Json::TJSONValue* __fastcall CreateJSONValue(const System::TArray__1<System::Byte> Data, const int Off, const int Count);
	virtual bool __fastcall IsNull();
	virtual System::Json::TJSONValue* __fastcall GetJSONValue()/* overload */;
	virtual System::Json::TJSONValue* __fastcall GetJSONValue(bool AInstanceOwner)/* overload */;
	virtual System::TObject* __fastcall GetObjectValue()/* overload */;
	virtual System::TObject* __fastcall GetObjectValue(bool AInstanceOwner)/* overload */;
	virtual System::UnicodeString __fastcall GetWideString()/* overload */;
	virtual void __fastcall SetJSONValue(System::Json::TJSONValue* const Value, const bool AInstanceOwner);
	virtual void __fastcall SetObjectValue(System::TObject* const Value, const bool AInstanceOwner);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	virtual void __fastcall SetNull();
	/* Hoisted overloads: */
	
public:
	inline System::UnicodeString __fastcall  GetWideString(System::UnicodeString defaultValue){ return TDBXValue::GetWideString(defaultValue); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXCallbackValue : public TDBXWritableValue
{
	typedef TDBXWritableValue inherited;
	
private:
	Data::Dbxjson::TDBXCallback* FDbxCallback;
	
protected:
	virtual void __fastcall SetRowValue()/* overload */;
	
public:
	__fastcall TDBXCallbackValue(TDBXValueType* const ValueType);
	__fastcall virtual ~TDBXCallbackValue();
	virtual bool __fastcall IsNull();
	virtual void __fastcall SetCallbackValue(Data::Dbxjson::TDBXCallback* const Value);
	virtual Data::Dbxjson::TDBXCallback* __fastcall GetCallbackValue();
	virtual void __fastcall SetOrdinal(const int Ordinal);
	virtual void __fastcall SetConnectionHandler(System::TObject* const ConnectionHandler);
	virtual void __fastcall SetObjectValue(System::TObject* const Value, const bool AInstanceOwner);
	virtual Data::Dbxjson::TDBXCallback* __fastcall CreateCallbackDelegate(int ordinal);
	virtual void __fastcall SetValue(TDBXValue* const Value);
	__property int Ordinal = {write=SetOrdinal, nodefault};
	__property System::TObject* ConnectionHandler = {write=SetConnectionHandler};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDBXCommunicationLayer : public Data::Dbxplatform::TFactoryObject
{
	typedef Data::Dbxplatform::TFactoryObject inherited;
	
private:
	bool FTerminated;
	int FConnectTimeout;
	int FCommunicationTimeout;
	
protected:
	virtual void __fastcall SetConnectTimeout(int Duration);
	virtual int __fastcall GetConnectTimeout();
	
public:
	virtual void __fastcall Open(TDBXProperties* const DbxProperties) = 0 ;
	virtual void __fastcall Close() = 0 ;
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count) = 0 ;
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count) = 0 ;
	virtual System::UnicodeString __fastcall Info() = 0 ;
	virtual void __fastcall Terminate();
	__property bool Terminated = {read=FTerminated, nodefault};
	__property int ConnectTimeout = {read=GetConnectTimeout, write=SetConnectTimeout, nodefault};
	__property int CommunicationTimeout = {read=FCommunicationTimeout, write=FCommunicationTimeout, nodefault};
public:
	/* TFactoryObject.Create */ inline __fastcall virtual TDBXCommunicationLayer() : Data::Dbxplatform::TFactoryObject() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXCommunicationLayer() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface TDBXScheduleEvent  : public System::IInterface 
{
	virtual void __fastcall Invoke() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXScheduler : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	class DELPHICLASS TDBXSchedulerRec;
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	class PASCALIMPLEMENTATION TDBXSchedulerRec : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		_di_TDBXScheduleEvent FEvent;
		System::TDateTime FTime;
		NativeInt FID;
	public:
		/* TObject.Create */ inline __fastcall TDBXSchedulerRec() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TDBXSchedulerRec() { }
		
	};
	
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	class DELPHICLASS TDBXSchedulerThread;
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	class PASCALIMPLEMENTATION TDBXSchedulerThread : public System::Classes::TThread
	{
		typedef System::Classes::TThread inherited;
		
	private:
		System::TObject* FEventSemaphore;
		System::TDateTime FLastFailure;
		
	protected:
		virtual void __fastcall Execute();
		
	public:
		__fastcall TDBXSchedulerThread(System::TObject* EventSem);
	public:
		/* TThread.Destroy */ inline __fastcall virtual ~TDBXSchedulerThread() { }
		
	};
	
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
private:
	System::Generics::Collections::TList__1<TDBXSchedulerRec*>* FEvents;
	TDBXSchedulerThread* FThread;
	System::Syncobjs::TCriticalSection* FSync;
	System::TObject* FThreadLock;
	System::TObject* FEventSemaphore;
	
private:
	static TDBXScheduler* FInstance;
	
protected:
	void __fastcall StartSchedulerThread();
	void __fastcall StopSchedulerThread();
	System::TDateTime __fastcall PeekTime();
	_di_TDBXScheduleEvent __fastcall PeekEvent();
	void __fastcall Pop();
	int __fastcall EventCount();
	
public:
	__fastcall virtual TDBXScheduler();
	__fastcall virtual ~TDBXScheduler();
	void __fastcall AddEvent(NativeInt Id, _di_TDBXScheduleEvent Proc, int Delta);
	bool __fastcall CancelEvent(NativeInt Id);
	void __fastcall CloseScheduler();
	/* static */ __property TDBXScheduler* Instance = {read=FInstance};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPrincipal : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::UnicodeString __fastcall GetName() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TPrincipal() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPrincipal() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TX500Principal : public TPrincipal
{
	typedef TPrincipal inherited;
	
public:
#ifndef __aarch64__
	virtual int __fastcall GetEncoded() = 0 ;
#else /* __aarch64__ */
	virtual long __fastcall GetEncoded() = 0 ;
#endif /* __aarch64__ */
public:
	/* TObject.Create */ inline __fastcall TX500Principal() : TPrincipal() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TX500Principal() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ECertificateExpiredException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ECertificateExpiredException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ECertificateExpiredException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ECertificateExpiredException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ECertificateExpiredException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ECertificateExpiredException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ECertificateExpiredException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ECertificateExpiredException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ECertificateExpiredException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECertificateExpiredException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECertificateExpiredException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECertificateExpiredException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECertificateExpiredException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ECertificateExpiredException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ECertificateNotYetValidException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ECertificateNotYetValidException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ECertificateNotYetValidException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ECertificateNotYetValidException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ECertificateNotYetValidException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ECertificateNotYetValidException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ECertificateNotYetValidException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ECertificateNotYetValidException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ECertificateNotYetValidException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECertificateNotYetValidException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECertificateNotYetValidException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECertificateNotYetValidException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECertificateNotYetValidException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ECertificateNotYetValidException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ECertificateParsingException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ECertificateParsingException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ECertificateParsingException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ECertificateParsingException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ECertificateParsingException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ECertificateParsingException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ECertificateParsingException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ECertificateParsingException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ECertificateParsingException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECertificateParsingException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECertificateParsingException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECertificateParsingException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECertificateParsingException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ECertificateParsingException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TKey : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::UnicodeString __fastcall GetAlgorithm() = 0 ;
	virtual System::UnicodeString __fastcall GetFormat() = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall GetEncoded() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TKey() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TKey() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPublicKey : public TKey
{
	typedef TKey inherited;
	
public:
	/* TObject.Create */ inline __fastcall TPublicKey() : TKey() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPublicKey() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCertificate : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::TArray__1<System::Byte> __fastcall GetEncoded() = 0 /* overload */;
	virtual TPublicKey* __fastcall GetPublicKey() = 0 /* overload */;
	virtual System::UnicodeString __fastcall GetType() = 0 /* overload */;
	virtual bool __fastcall Verify(TPublicKey* key) = 0 /* overload */;
public:
	/* TObject.Create */ inline __fastcall TCertificate() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCertificate() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TX509Certificate : public TCertificate
{
	typedef TCertificate inherited;
	
public:
	virtual System::UnicodeString __fastcall GetType()/* overload */;
	virtual void __fastcall CheckValidity() = 0 /* overload */;
	virtual void __fastcall CheckValidity(System::TDateTime ADate) = 0 /* overload */;
	virtual int __fastcall GetBasicConstraints() = 0 ;
	virtual TX500Principal* __fastcall GetIssuerX500Principal() = 0 ;
	virtual System::TDateTime __fastcall GetNotAfter() = 0 ;
	virtual System::TDateTime __fastcall GetNotBefore() = 0 ;
	virtual System::UnicodeString __fastcall GetSerialNumber() = 0 ;
	virtual System::UnicodeString __fastcall GetSigAlgName() = 0 ;
	virtual System::UnicodeString __fastcall GetSignature() = 0 ;
	virtual TX500Principal* __fastcall GetSubjectX500Principal() = 0 ;
#ifndef __aarch64__
	virtual int __fastcall GetVersion() = 0 ;
#else /* __aarch64__ */
	virtual long __fastcall GetVersion() = 0 ;
#endif /* __aarch64__ */
public:
	/* TObject.Create */ inline __fastcall TX509Certificate() : TCertificate() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TX509Certificate() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TRequestCommandHandler : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall AddCommandError(System::UnicodeString ErrorMessage) = 0 ;
	virtual void __fastcall AddCommand(TDBXCommand* Command, TDBXConnection* DBXConnection) = 0 ;
	virtual void __fastcall ClearCommands() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TRequestCommandHandler() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRequestCommandHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TResultCommandHandler : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual int __fastcall GetCommandCount() = 0 ;
	virtual int __fastcall GetParameterCount(int Index) = 0 ;
	virtual TDBXCommand* __fastcall GetCommand(int Index) = 0 ;
	virtual TDBXParameter* __fastcall GetCommandParameter(int CommandIndex, int ParameterIndex) = 0 /* overload */;
	virtual TDBXParameter* __fastcall GetCommandParameter(TDBXCommand* Command, int Index) = 0 /* overload */;
public:
	/* TObject.Create */ inline __fastcall TResultCommandHandler() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TResultCommandHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define DBXVersion25 u"2.5"
#define DBXVersion30 u"3.0"
#define DBXVersion40 u"4.0"
static constexpr System::Int8 DBXDefaultRowSetSize = System::Int8(0x14);
static constexpr System::WideChar LibraryPreferences = (System::WideChar)(0x2f);
#define TDBXRegistryKey u"\\Software\\Embarcadero\\BDS\\20.0\\dbExpress"
#define TDBXRegistryKey21 u"\\Software\\Embarcadero\\BDS\\21.0\\dbExpress"
#define TDBXRegistryDriverValue u"Driver Registry File"
#define TDBXRegistryConnectionValue u"Connection Registry File"
#define TDBXDriverFile u"dbxdrivers.ini"
#define TDBXConnectionFile u"dbxconnections.ini"
extern DELPHI_PACKAGE void __fastcall InitializeConnectionFactorySingletonFromINIFile(const System::UnicodeString DriverFileName, const System::UnicodeString ConnectionFileName);
}	/* namespace Dbxcommon */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXCOMMON)
using namespace Data::Dbxcommon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxcommonHPP
