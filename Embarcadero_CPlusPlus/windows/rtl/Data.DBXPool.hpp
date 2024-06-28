// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXPool.pas' rev: 34.00 (Windows)

#ifndef Data_DbxpoolHPP
#define Data_DbxpoolHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.Classes.hpp>
#include <Data.DBXDelegate.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SyncObjs.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.DBXPool"

namespace Data
{
namespace Dbxpool
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXPoolPropertyNames;
class DELPHICLASS TDBXPoolCommands;
class DELPHICLASS TDBXPoolsTable;
class DELPHICLASS TDBXPoolConnection;
class DELPHICLASS TDBXPoolCommand;
class DELPHICLASS TDBXPoolReader;
class DELPHICLASS TDBXPoolRow;
class DELPHICLASS TDBXPool;
class DELPHICLASS TDBXPoolDriver;
class DELPHICLASS TDBXPoolProperties;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPoolPropertyNames : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPoolPropertyNames_MaxConnections L"MaxConnections"
	
	#define TDBXPoolPropertyNames_MinConnections L"MinConnections"
	
	#define TDBXPoolPropertyNames_ConnectTimeout L"ConnectTimeout"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPoolPropertyNames() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPoolPropertyNames() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPoolCommands : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPoolCommands_GetPools L"GetPools"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPoolCommands() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPoolCommands() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPoolsTable : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPoolsTable_ConnectionName L"ConnectionName"
	
	#define TDBXPoolsTable_DriverName L"DriverName"
	
	#define TDBXPoolsTable_DatabaseName L"DatabaseName"
	
	#define TDBXPoolsTable_UserName L"UserName"
	
	#define TDBXPoolsTable_DelegateSignature L"DelegateSignature"
	
	#define TDBXPoolsTable_ConnectTimeout L"ConnectTimeout"
	
	#define TDBXPoolsTable_AvailableConnections L"AvailableConnections"
	
	#define TDBXPoolsTable_TotalConnections L"TotalConnections"
	
	#define TDBXPoolsTable_MaxConnections L"MaxConnections"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPoolsTable() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPoolsTable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPoolConnection : public Data::Dbxdelegate::TDBXDelegateConnection
{
	typedef Data::Dbxdelegate::TDBXDelegateConnection inherited;
	
private:
	TDBXPoolDriver* FPoolDriver;
	TDBXPool* FPool;
	
protected:
	virtual void __fastcall DerivedGetCommandTypes(System::Classes::TStrings* const List);
	virtual void __fastcall DerivedGetCommands(const System::UnicodeString CommandType, System::Classes::TStrings* const List);
	virtual void __fastcall Open();
	
public:
	__fastcall TDBXPoolConnection(TDBXPool* Pool, Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder, TDBXPoolDriver* PoolDriver, Data::Dbxcommon::TDBXConnection* Connection);
	__fastcall virtual ~TDBXPoolConnection();
	virtual Data::Dbxcommon::TDBXCommand* __fastcall CreateCommand()/* overload */;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPoolCommand : public Data::Dbxcommon::TDBXCommand
{
	typedef Data::Dbxcommon::TDBXCommand inherited;
	
private:
	TDBXPool* FPool;
	Data::Dbxcommon::TDBXReader* __fastcall ExecuteGetPools();
	
protected:
	virtual void __fastcall SetMaxBlobSize(const __int64 MaxBlobSize);
	virtual void __fastcall SetRowSetSize(const __int64 Value);
	virtual void __fastcall DerivedOpen();
	virtual void __fastcall DerivedClose();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedGetNextReader();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedExecuteQuery();
	virtual void __fastcall DerivedExecuteUpdate();
	virtual void __fastcall DerivedPrepare();
	virtual __int64 __fastcall GetRowsAffected();
	__fastcall TDBXPoolCommand(Data::Dbxcommon::TDBXContext* DBXContext, TDBXPool* Pool);
	
public:
	__fastcall virtual ~TDBXPoolCommand();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPoolReader : public Data::Dbxcommon::TDBXReader
{
	typedef Data::Dbxcommon::TDBXReader inherited;
	
private:
	Data::Dbxcommon::TDBXReaderByteReader* FByteReader;
	
protected:
	virtual bool __fastcall DerivedNext();
	virtual void __fastcall DerivedClose();
	virtual Data::Dbxcommon::TDBXByteReader* __fastcall GetByteReader();
	
public:
	__fastcall TDBXPoolReader(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXRow* DbxRow, Data::Dbxcommon::TDBXByteReader* ByteReader);
	__fastcall virtual ~TDBXPoolReader();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPoolRow : public Data::Dbxcommon::TDBXRow
{
	typedef Data::Dbxcommon::TDBXRow inherited;
	
private:
	System::Generics::Collections::TList__1<TDBXPool*>* FPoolList;
	int FRow;
	bool __fastcall Next();
	
protected:
	virtual void __fastcall GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::WideChar * &WideStringBuilder, System::LongBool &IsNull)/* overload */;
	virtual void __fastcall GetInt32(Data::Dbxcommon::TDBXInt32Value* DbxValue, int &Value, System::LongBool &IsNull);
	
public:
	__fastcall TDBXPoolRow(System::Generics::Collections::TList__1<TDBXPool*>* PoolList, Data::Dbxcommon::TDBXContext* DBXContext);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPoolRow() { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GetWideString(Data::Dbxcommon::TDBXWideStringValue* DbxValue, System::UnicodeString &Value, System::LongBool &IsNull){ Data::Dbxcommon::TDBXRow::GetWideString(DbxValue, Value, IsNull); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPool : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<Data::Dbxcommon::TDBXConnection*> _TDBXPool__1;
	
	typedef System::DynamicArray<Data::Dbxcommon::TDBXConnection*> _TDBXPool__2;
	
	
private:
	Data::Dbxplatform::TDBXSemaphore* FSemaphore;
	System::Syncobjs::TCriticalSection* FCriticalSection;
	_TDBXPool__1 FAllConnectionArray;
	_TDBXPool__2 FAvailableConnectionArray;
	TDBXPoolDriver* FPoolDriver;
	System::UnicodeString FConnectionName;
	System::UnicodeString FDriverName;
	System::UnicodeString FDatabaseName;
	System::UnicodeString FUserName;
	System::UnicodeString FDelegateSignature;
	int FConnectTimeout;
	int FTotalConnections;
	int FAvailableConnections;
	int FMaxConnections;
	
protected:
	__fastcall TDBXPool(TDBXPoolDriver* Driver, Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	
private:
	bool __fastcall IsEqual(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder, const System::UnicodeString ConnectionName, const System::UnicodeString DelegateSignature, const System::UnicodeString DriverName, const System::UnicodeString DatabaseName, const System::UnicodeString UserName);
	Data::Dbxcommon::TDBXConnection* __fastcall GetConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	void __fastcall ReleaseConnection(Data::Dbxcommon::TDBXConnection* Connection);
	void __fastcall ClearPool();
	
public:
	__fastcall virtual ~TDBXPool();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPoolDriver : public Data::Dbxcommon::TDBXDriver
{
	typedef Data::Dbxcommon::TDBXDriver inherited;
	
private:
	System::Generics::Collections::TList__1<TDBXPool*>* FPoolList;
	TDBXPool* __fastcall FindPool(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	void __fastcall ClearPools();
	Data::Dbxcommon::TDBXCommand* __fastcall CreatePoolCommand(Data::Dbxcommon::TDBXContext* DBXContext, Data::Dbxcommon::TDBXConnection* Connection, Data::Dbxcommon::TDBXCommand* MorphicCommand);
	
protected:
	virtual void __fastcall Close();
	
public:
	__fastcall virtual ~TDBXPoolDriver();
	__fastcall virtual TDBXPoolDriver(const Data::Dbxcommon::TDBXDriverDef &DriverDef)/* overload */;
	virtual Data::Dbxcommon::TDBXConnection* __fastcall CreateConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	virtual System::UnicodeString __fastcall GetDriverVersion();
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXPoolDriver()/* overload */ : Data::Dbxcommon::TDBXDriver() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDBXPoolProperties : public Data::Dbxcommon::TDBXProperties
{
	typedef Data::Dbxcommon::TDBXProperties inherited;
	
private:
	#define TDBXPoolProperties_StrMaxConnections L"MaxConnections"
	
	#define TDBXPoolProperties_StrMinConnections L"MinConnections"
	
	#define TDBXPoolProperties_StrConnectTimeout L"ConnectTimeout"
	
	int __fastcall GetConnectTimeout();
	int __fastcall GetMaxConnections();
	int __fastcall GetMinConnections();
	void __fastcall SetConnectTimeout(const int Value);
	void __fastcall SetMaxConnections(const int Value);
	void __fastcall SetMinConnections(const int Value);
	
public:
	__fastcall virtual TDBXPoolProperties(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */;
	
__published:
	__property int MaxConnections = {read=GetMaxConnections, write=SetMaxConnections, nodefault};
	__property int MinConnections = {read=GetMinConnections, write=SetMinConnections, nodefault};
	__property int ConnectTimeout = {read=GetConnectTimeout, write=SetConnectTimeout, nodefault};
public:
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXPoolProperties()/* overload */ : Data::Dbxcommon::TDBXProperties() { }
	/* TDBXProperties.Destroy */ inline __fastcall virtual ~TDBXPoolProperties() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define sDriverName L"DBXPool"
}	/* namespace Dbxpool */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXPOOL)
using namespace Data::Dbxpool;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxpoolHPP
