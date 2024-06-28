// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MySQLWrapper.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_MysqlwrapperHPP
#define Firedac_Phys_MysqlwrapperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SyncObjs.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Phys.MySQLCli.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Mysqlwrapper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMySQLLib;
class DELPHICLASS TFDMySQLError;
class DELPHICLASS EMySQLNativeException;
class DELPHICLASS TMySQLSession;
class DELPHICLASS TMySQLReader;
class DELPHICLASS TMySQLField;
class DELPHICLASS TMySQLResult;
class DELPHICLASS TMySQLVariable;
class DELPHICLASS TMySQLBlobStream;
class DELPHICLASS TMySQLVariables;
class DELPHICLASS TMySQLStatement;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TMySQLBrand : unsigned int { mbMySQL, mbMariaDB };

class PASCALIMPLEMENTATION TMySQLLib : public Firedac::Stan::Util::TFDLibrary
{
	typedef Firedac::Stan::Util::TFDLibrary inherited;
	
private:
	System::Syncobjs::TCriticalSection* FLock;
	TMySQLBrand FBrand;
	unsigned __int64 FCompatVersion;
	void __fastcall InitEmbedded(const System::UnicodeString AEmbArgs, const System::UnicodeString AEmbGrps);
	void __fastcall EndEmbedded();
	
protected:
	virtual void __fastcall GetLibraryInfo();
	virtual void __fastcall LoadEntries();
	
public:
	bool FMySQLEmbedded;
	bool FMySQLEmbeddedInit;
	Firedac::Phys::Mysqlcli::TPrcmysql_num_fields mysql_num_fields;
	Firedac::Phys::Mysqlcli::TPrcmysql_fetch_field_direct mysql_fetch_field_direct;
	Firedac::Phys::Mysqlcli::TPrcmysql_affected_rows mysql_affected_rows;
	Firedac::Phys::Mysqlcli::TPrcmysql_insert_id mysql_insert_id;
	Firedac::Phys::Mysqlcli::TPrcmysql_errno mysql_errno;
	Firedac::Phys::Mysqlcli::TPrcmysql_error mysql_error;
	Firedac::Phys::Mysqlcli::TPrcmysql_sqlstate mysql_sqlstate;
	Firedac::Phys::Mysqlcli::TPrcmysql_warning_count mysql_warning_count;
	Firedac::Phys::Mysqlcli::TPrcmysql_info mysql_info;
	Firedac::Phys::Mysqlcli::TPrcmysql_character_set_name mysql_character_set_name;
	Firedac::Phys::Mysqlcli::TPrcmysql_get_character_set_info mysql_get_character_set_info;
	Firedac::Phys::Mysqlcli::TPrcmysql_set_character_set mysql_set_character_set;
	Firedac::Phys::Mysqlcli::TPrcmysql_init mysql_init;
	Firedac::Phys::Mysqlcli::TPrcmysql_ssl_set mysql_ssl_set;
	Firedac::Phys::Mysqlcli::TPrcmysql_get_ssl_cipher mysql_get_ssl_cipher;
	Firedac::Phys::Mysqlcli::TPrcmysql_connect mysql_connect;
	Firedac::Phys::Mysqlcli::TPrcmysql_real_connect mysql_real_connect;
	Firedac::Phys::Mysqlcli::TPrcmysql_close mysql_close;
	Firedac::Phys::Mysqlcli::TPrcmysql_select_db mysql_select_db;
	Firedac::Phys::Mysqlcli::TPrcmysql_real_query mysql_real_query;
	Firedac::Phys::Mysqlcli::TPrcmysql_kill mysql_kill;
	Firedac::Phys::Mysqlcli::TPrcmysql_ping mysql_ping;
	Firedac::Phys::Mysqlcli::TPrcmysql_stat mysql_stat;
	Firedac::Phys::Mysqlcli::TPrcmysql_get_server_info mysql_get_server_info;
	Firedac::Phys::Mysqlcli::TPrcmysql_get_client_info mysql_get_client_info;
	Firedac::Phys::Mysqlcli::TPrcmysql_get_host_info mysql_get_host_info;
	Firedac::Phys::Mysqlcli::TPrcmysql_get_proto_info mysql_get_proto_info;
	Firedac::Phys::Mysqlcli::TPrcmysql_list_processes mysql_list_processes;
	Firedac::Phys::Mysqlcli::TPrcmysql_store_result mysql_store_result;
	Firedac::Phys::Mysqlcli::TPrcmysql_use_result mysql_use_result;
	Firedac::Phys::Mysqlcli::TPrcmysql_options mysql_options_;
	Firedac::Phys::Mysqlcli::TPrcmysql_free_result mysql_free_result;
	Firedac::Phys::Mysqlcli::TPrcmysql_fetch_row mysql_fetch_row;
	Firedac::Phys::Mysqlcli::TPrcmysql_fetch_lengths mysql_fetch_lengths;
	Firedac::Phys::Mysqlcli::TPrcmysql_escape_string mysql_escape_string;
	Firedac::Phys::Mysqlcli::TPrcmysql_real_escape_string mysql_real_escape_string;
	Firedac::Phys::Mysqlcli::TPrcmysql_thread_safe mysql_thread_safe;
	Firedac::Phys::Mysqlcli::TPrcmysql_more_results mysql_more_results;
	Firedac::Phys::Mysqlcli::TPrcmysql_next_result mysql_next_result;
	Firedac::Phys::Mysqlcli::TPrcmysql_server_init mysql_server_init;
	Firedac::Phys::Mysqlcli::TPrcmysql_server_end mysql_server_end;
	Firedac::Phys::Mysqlcli::TPrcmysql_thread_init mysql_thread_init;
	Firedac::Phys::Mysqlcli::TPrcmysql_thread_end mysql_thread_end;
	Firedac::Phys::Mysqlcli::TPrcmysql_thread_id mysql_thread_id;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_init mysql_stmt_init;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_prepare mysql_stmt_prepare;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_execute mysql_stmt_execute;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_fetch mysql_stmt_fetch;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_fetch_column mysql_stmt_fetch_column;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_store_result mysql_stmt_store_result;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_param_count mysql_stmt_param_count;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_attr_set mysql_stmt_attr_set;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_attr_get mysql_stmt_attr_get;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_bind_param mysql_stmt_bind_param;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_bind_result mysql_stmt_bind_result;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_close mysql_stmt_close;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_reset mysql_stmt_reset;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_free_result mysql_stmt_free_result;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_send_long_data mysql_stmt_send_long_data;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_result_metadata mysql_stmt_result_metadata;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_errno mysql_stmt_errno;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_error mysql_stmt_error;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_sqlstate mysql_stmt_sqlstate;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_row_seek mysql_stmt_row_seek;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_row_tell mysql_stmt_row_tell;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_data_seek mysql_stmt_data_seek;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_num_rows mysql_stmt_num_rows;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_affected_rows mysql_stmt_affected_rows;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_insert_id mysql_stmt_insert_id;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_field_count mysql_stmt_field_count;
	Firedac::Phys::Mysqlcli::TPrcmysql_stmt_next_result mysql_stmt_next_result;
	__fastcall TMySQLLib(System::TObject* AOwningObj);
	__fastcall virtual ~TMySQLLib();
	HIDESBASE void __fastcall Load(const System::UnicodeString AVendorHome, const System::UnicodeString AVendorLib, const System::UnicodeString AEmbArgs, const System::UnicodeString AEmbGrps);
	virtual void __fastcall Unload();
	__property TMySQLBrand Brand = {read=FBrand, nodefault};
	__property unsigned __int64 CompatVersion = {read=FCompatVersion};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDMySQLError : public Firedac::Stan::Error::TFDDBError
{
	typedef Firedac::Stan::Error::TFDDBError inherited;
	
private:
	System::UnicodeString FSQLState;
	
protected:
	virtual void __fastcall Assign(Firedac::Stan::Error::TFDDBError* ASrc);
	virtual void __fastcall LoadFromStorage(const Firedac::Stan::Intf::_di_IFDStanStorage AStorage);
	virtual void __fastcall SaveToStorage(const Firedac::Stan::Intf::_di_IFDStanStorage AStorage);
	
public:
	__property System::UnicodeString SQLState = {read=FSQLState};
public:
	/* TFDDBError.Create */ inline __fastcall virtual TFDMySQLError()/* overload */ : Firedac::Stan::Error::TFDDBError() { }
	/* TFDDBError.Create */ inline __fastcall virtual TFDMySQLError(int ALevel, int AErrorCode, const System::UnicodeString AMessage, const System::UnicodeString AObjName, Firedac::Stan::Error::TFDCommandExceptionKind AKind, int ACmdOffset, int ARowIndex)/* overload */ : Firedac::Stan::Error::TFDDBError(ALevel, AErrorCode, AMessage, AObjName, AKind, ACmdOffset, ARowIndex) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDMySQLError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EMySQLNativeException : public Firedac::Stan::Error::EFDDBEngineException
{
	typedef Firedac::Stan::Error::EFDDBEngineException inherited;
	
protected:
	virtual Firedac::Stan::Error::TFDDBErrorClass __fastcall GetErrorClass();
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual EMySQLNativeException()/* overload */ : Firedac::Stan::Error::EFDDBEngineException() { }
	/* EFDDBEngineException.Create */ inline __fastcall EMySQLNativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~EMySQLNativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EMySQLNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EMySQLNativeException(NativeUInt Ident)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EMySQLNativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EMySQLNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EMySQLNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EMySQLNativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMySQLNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMySQLNativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMySQLNativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMySQLNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMySQLNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High, AHelpContext) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TMySQLSession : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TMySQLLib* FLib;
	bool FTracing;
	Firedac::Stan::Intf::_di_IFDMoniClient FMonitor;
	void *FPMySQL;
	bool FOwnPMySQL;
	System::TObject* FOwningObj;
	Firedac::Stan::Util::TFDBuffer* FBuffer;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	System::UnicodeString FCurrDB;
	EMySQLNativeException* FInfo;
	System::UnicodeString FCharsetName;
	unsigned __int64 FServerVersion;
	unsigned __int64 FClientVersion;
	System::UnicodeString FPwd;
	unsigned FPort;
	System::UnicodeString FHost;
	System::UnicodeString FUser;
	unsigned FFlags;
	bool FUtf8mb4;
	unsigned __int64 __fastcall GetAffectedRows();
	unsigned __fastcall GetWarningCount();
	System::UnicodeString __fastcall GetClientInfo();
	System::UnicodeString __fastcall GetServerInfo();
	void __fastcall SetOptions(int AOption, const System::PByte AValue);
	System::UnicodeString __fastcall GetDB();
	void __fastcall SetDB(const System::UnicodeString AValue);
	void __fastcall ProcessError(unsigned AErrNo, const System::UnicodeString AMsg, const System::UnicodeString ASQLState, System::TObject* AInitiator);
	void __fastcall Check(int ACode = 0xffffffff, System::TObject* AInitiator = (System::TObject*)(0x0));
	void __fastcall ClearInfo();
	void __fastcall SetInfo(char * ApInfo, char * ApLevel, int ACode);
	void __fastcall GetInfo();
	System::UnicodeString __fastcall GetCharacterSetName();
	System::UnicodeString __fastcall GetHostInfo();
	unsigned __int64 __fastcall GetInsert_ID();
	void __fastcall SetCharacterSetName(const System::UnicodeString AValue);
	bool __fastcall GetHasMoreResults();
	System::UnicodeString __fastcall GetSSLCipher();
	unsigned __int64 __fastcall GetClientVersion();
	unsigned __int64 __fastcall GetServerVersion();
	unsigned __fastcall GetServerStatus();
	
public:
	__fastcall TMySQLSession(TMySQLLib* ALib, System::TObject* AOwningObj);
	__fastcall TMySQLSession(TMySQLLib* ALib, void * ApMySQL, System::TObject* AOwningObj);
	__fastcall virtual ~TMySQLSession();
	void __fastcall Trace(const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	void __fastcall Trace(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	void __fastcall Init();
	void __fastcall SSLInit(const System::UnicodeString Akey, const System::UnicodeString Acert, const System::UnicodeString Aca, const System::UnicodeString Acapath, const System::UnicodeString Acipher);
	void __fastcall Connect(const System::UnicodeString host, const System::UnicodeString user, const System::UnicodeString passwd, const System::UnicodeString db, unsigned port, unsigned clientflag);
	void __fastcall Disconnect();
	void __fastcall KillQuery();
	void __fastcall Ping();
	unsigned __fastcall EscapeString(char * szTo, const char * szFrom, unsigned length)/* overload */;
	void __fastcall Query(const System::UnicodeString ACmd, System::TObject* AInitiator = (System::TObject*)(0x0));
	void __fastcall QuerySB(const System::RawByteString ACmd, System::TObject* AInitiator = (System::TObject*)(0x0));
	void __fastcall GetServerOutput();
	TMySQLResult* __fastcall StoreResult();
	TMySQLResult* __fastcall UseResult();
	bool __fastcall MoreResults();
	bool __fastcall NextResult();
	void __fastcall GetCharacterSetInfo(Firedac::Phys::Mysqlcli::MY_CHARSET_INFO &ACharset);
	__property System::PByte Options[int AOption] = {write=SetOptions};
	__property System::UnicodeString ServerInfo = {read=GetServerInfo};
	__property unsigned __int64 ServerVersion = {read=GetServerVersion};
	__property System::UnicodeString ClientInfo = {read=GetClientInfo};
	__property unsigned __int64 ClientVersion = {read=GetClientVersion};
	__property unsigned __int64 AffectedRows = {read=GetAffectedRows};
	__property unsigned WarningCount = {read=GetWarningCount, nodefault};
	__property unsigned ServerStatus = {read=GetServerStatus, nodefault};
	__property bool Tracing = {read=FTracing, write=FTracing, nodefault};
	__property Firedac::Stan::Intf::_di_IFDMoniClient Monitor = {read=FMonitor, write=FMonitor};
	__property System::UnicodeString DB = {read=GetDB, write=SetDB};
	__property TMySQLLib* Lib = {read=FLib};
	__property System::TObject* OwningObj = {read=FOwningObj};
	__property EMySQLNativeException* Info = {read=FInfo};
	__property Firedac::Stan::Util::TFDBuffer* Buffer = {read=FBuffer};
	__property Firedac::Stan::Util::TFDEncoder* Encoder = {read=FEncoder};
	__property System::UnicodeString CharacterSetName = {read=GetCharacterSetName, write=SetCharacterSetName};
	__property System::UnicodeString HostInfo = {read=GetHostInfo};
	__property unsigned __int64 Insert_ID = {read=GetInsert_ID};
	__property void * MySQL = {read=FPMySQL};
	__property System::UnicodeString Host = {read=FHost};
	__property System::UnicodeString User = {read=FUser};
	__property System::UnicodeString Pwd = {read=FPwd};
	__property unsigned Port = {read=FPort, nodefault};
	__property unsigned Flags = {read=FFlags, nodefault};
	__property bool HasMoreResults = {read=GetHasMoreResults, nodefault};
	__property System::UnicodeString SSLCipher = {read=GetSSLCipher};
	__property bool UTf8mb4 = {read=FUtf8mb4, nodefault};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMySQLReader : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	bool FStrsTrim;
	bool FStrsEmpty2Null;
	bool FStrsTrim2Len;
	unsigned FMaxStringSize;
	
public:
	__property bool StrsTrim = {read=FStrsTrim, write=FStrsTrim, nodefault};
	__property bool StrsEmpty2Null = {read=FStrsEmpty2Null, write=FStrsEmpty2Null, nodefault};
	__property bool StrsTrim2Len = {read=FStrsTrim2Len, write=FStrsTrim2Len, nodefault};
	__property unsigned MaxStringSize = {read=FMaxStringSize, write=FMaxStringSize, nodefault};
public:
	/* TObject.Create */ inline __fastcall TMySQLReader() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMySQLReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMySQLField : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TMySQLResult* FResult;
	void *FpFld;
	
public:
	void __fastcall GetInfo(char * &name, char * &srcname, char * &table, char * &db, System::Byte &type_, unsigned &length, unsigned &flags, unsigned &decimals, unsigned &charsetnr, bool AMaxLenValid);
	__fastcall TMySQLField(TMySQLResult* AResult);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMySQLField() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMySQLResult : public TMySQLReader
{
	typedef TMySQLReader inherited;
	
private:
	TMySQLSession* FSession;
	void *FCursor;
	System::PByte *FpRow;
	unsigned *FpLengths;
	TMySQLField* FField;
	unsigned __fastcall GetFieldCount();
	TMySQLField* __fastcall GetFields(int AIndex);
	void __fastcall DumpColumns(int ARowIndex);
	
public:
	__fastcall TMySQLResult(TMySQLSession* ASession, void * AResult);
	__fastcall virtual ~TMySQLResult();
	bool __fastcall Fetch(int ARowIndex);
	bool __fastcall GetFieldData(int AIndex, /* out */ void * &ApData, /* out */ unsigned &ALen);
	bool __fastcall GetData(int AIndex, void * &ApData, /* out */ unsigned &ALen, Firedac::Stan::Intf::TFDDataType AType, Firedac::Stan::Intf::TFDDataAttributes AAttrs);
	__property unsigned FieldCount = {read=GetFieldCount, nodefault};
	__property TMySQLField* Fields[int AIndex] = {read=GetFields};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TMySQLVariable : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TMySQLVariables* FVars;
	unsigned __int64 FVer;
	unsigned FIndex;
	Firedac::Stan::Intf::TFDDataType FFDDataType;
	System::UnicodeString FDumpLabel;
	bool FFixedLen;
	void * __fastcall GetBind();
	unsigned __fastcall GetBindSize();
	int __fastcall GetDataType();
	void __fastcall SetDataType(const int AValue);
	unsigned __fastcall GetDataSize();
	void __fastcall SetDataSize(const unsigned AValue);
	bool __fastcall GetUnsigned();
	void __fastcall SetUnsigned(const bool AValue);
	void __fastcall GetInfo(void * &ApData, Firedac::Phys::Mysqlcli::Pmy_ulong &ApLen, Firedac::Phys::Mysqlcli::Pmy_bool &ApNull, Firedac::Phys::Mysqlcli::Pmy_bool &ApError);
	System::UnicodeString __fastcall GetDumpLabel();
	bool __fastcall GetLongData();
	void __fastcall SetBuffer(System::PByte ABuff, unsigned ALength);
	
protected:
	void __fastcall ResetBlob();
	
public:
	__fastcall TMySQLVariable(TMySQLVariables* AVars);
	__fastcall virtual ~TMySQLVariable();
	void __fastcall Assign(TMySQLVariable* AVar);
	bool __fastcall GetData(void * &ApData, /* out */ unsigned &ALen, bool AByRef = false)/* overload */;
	void __fastcall SetData(void * ApData, unsigned ALen)/* overload */;
	unsigned __fastcall GetDataTypeSize(int AType, unsigned ASize);
	System::UnicodeString __fastcall DumpValue();
	System::UnicodeString __fastcall DumpSQLDataType();
	__property void * Bind = {read=GetBind};
	__property unsigned BindSize = {read=GetBindSize, nodefault};
	__property bool LongData = {read=GetLongData, nodefault};
	__property unsigned Index = {read=FIndex, nodefault};
	__property TMySQLVariables* Vars = {read=FVars};
	__property System::UnicodeString DumpLabel = {read=GetDumpLabel, write=FDumpLabel};
	__property int DataType = {read=GetDataType, write=SetDataType, nodefault};
	__property unsigned DataSize = {read=GetDataSize, write=SetDataSize, nodefault};
	__property bool Unsigned = {read=GetUnsigned, write=SetUnsigned, nodefault};
	__property Firedac::Stan::Intf::TFDDataType FDDataType = {read=FFDDataType, write=FFDDataType, nodefault};
	__property bool FixedLen = {read=FFixedLen, write=FFixedLen, nodefault};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMySQLBlobStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	TMySQLVariable* FVar;
	TMySQLStatement* FStmt;
	Firedac::Stan::Intf::TFDStreamMode FMode;
	unsigned FDataOff;
	unsigned FDataLen;
	unsigned FBlobOff;
	System::Byte *FBuff;
	unsigned FBuffSize;
	unsigned FLength;
	void __fastcall CheckMode(Firedac::Stan::Intf::TFDStreamMode AMode, const System::UnicodeString AMsg);
	System::TObject* __fastcall GetOwningObj();
	Firedac::Stan::Intf::TFDEncoding __fastcall GetEncoding(Firedac::Stan::Intf::TFDDataType AType);
	
protected:
	virtual __int64 __fastcall GetSize();
	
public:
	__fastcall TMySQLBlobStream(TMySQLVariable* AVar, Firedac::Stan::Intf::TFDStreamMode AMode);
	__fastcall virtual ~TMySQLBlobStream();
	virtual int __fastcall Read(void *Buffer, int Count)/* overload */;
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
	int __fastcall ReadStr(void * ABuff, int ALen, Firedac::Stan::Intf::TFDDataType AType);
	int __fastcall WriteStr(void * ABuff, int ALen, Firedac::Stan::Intf::TFDDataType AType);
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	__property TMySQLVariable* Vari = {read=FVar};
	__property System::TObject* OwningObj = {read=GetOwningObj};
	/* Hoisted overloads: */
	
public:
#ifndef _WIN64
	inline int __fastcall  Read(System::DynamicArray<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::DynamicArray<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#else /* _WIN64 */
	inline int __fastcall  Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#endif /* _WIN64 */
	inline int __fastcall  Seek(int Offset, System::Word Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMySQLVariables : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TMySQLVariable* operator[](unsigned AIndex) { return this->Items[AIndex]; }
	
private:
	System::Classes::TList* FList;
	TMySQLStatement* FStatement;
	void *FBinds;
	unsigned FBindSize;
	System::Byte *FBuff;
	unsigned FBuffSize;
	TMySQLVariable* __fastcall GetItems(unsigned AIndex);
	int __fastcall GetCount();
	void __fastcall SetCount(const int ACount);
	
protected:
	void __fastcall AllocateBuff();
	void __fastcall ReleaseBuff();
	void __fastcall ResetBlobs();
	
public:
	__fastcall TMySQLVariables(TMySQLStatement* AStatement);
	__fastcall virtual ~TMySQLVariables();
	void __fastcall CheckBuff();
	__property TMySQLStatement* Statement = {read=FStatement};
	__property void * Binds = {read=FBinds};
	__property int Count = {read=GetCount, write=SetCount, nodefault};
	__property TMySQLVariable* Items[unsigned AIndex] = {read=GetItems/*, default*/};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TMySQLStatementState : unsigned int { msInactive, msPrepared, msExecuted, msOpenFirst, msOpenNext, msEOF };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMySQLStatement : public TMySQLReader
{
	typedef TMySQLReader inherited;
	
private:
	System::TObject* FOwningObj;
	TMySQLSession* FSession;
	void *FStmt;
	TMySQLVariables* FParams;
	TMySQLVariables* FFields;
	TMySQLStatementState FState;
	void __fastcall Check(int ACode);
	unsigned __int64 __fastcall GetAffectedRows();
	unsigned __int64 __fastcall GetInsert_ID();
	unsigned __fastcall GetFieldCount();
	unsigned __fastcall GetParamCount();
	System::Byte __fastcall GetBoolAttr(const int AIndex);
	void __fastcall SetBoolAttr(const int AIndex, const System::Byte AValue);
	unsigned __fastcall GetLongAttr(const int AIndex);
	void __fastcall SetLongAttr(const int AIndex, const unsigned AValue);
	
public:
	__fastcall TMySQLStatement(TMySQLSession* ASession, System::TObject* AOwningObj);
	__fastcall virtual ~TMySQLStatement();
	void __fastcall Prepare(const System::UnicodeString ASQL);
	TMySQLResult* __fastcall Describe();
	void __fastcall BindParams();
	void __fastcall BindColumns();
	void __fastcall Execute();
	bool __fastcall Fetch();
	bool __fastcall MoreResults();
	bool __fastcall NextResult();
	void __fastcall StoreResult();
	void __fastcall Close();
	void __fastcall Reset();
	void __fastcall Unprepare();
	__property TMySQLStatementState State = {read=FState, nodefault};
	__property unsigned __int64 AffectedRows = {read=GetAffectedRows};
	__property unsigned __int64 Insert_ID = {read=GetInsert_ID};
	__property unsigned ParamCount = {read=GetParamCount, nodefault};
	__property unsigned FieldCount = {read=GetFieldCount, nodefault};
	__property TMySQLVariables* Params = {read=FParams};
	__property TMySQLVariables* Fields = {read=FFields};
	__property TMySQLSession* Session = {read=FSession};
	__property System::TObject* OwningObj = {read=FOwningObj};
	__property System::Byte UPDATE_MAX_LENGTH = {read=GetBoolAttr, write=SetBoolAttr, index=0, nodefault};
	__property unsigned CURSOR_TYPE = {read=GetLongAttr, write=SetLongAttr, index=1, nodefault};
	__property unsigned PREFETCH_ROWS = {read=GetLongAttr, write=SetLongAttr, index=2, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mysqlwrapper */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MYSQLWRAPPER)
using namespace Firedac::Phys::Mysqlwrapper;
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
#endif	// Firedac_Phys_MysqlwrapperHPP
