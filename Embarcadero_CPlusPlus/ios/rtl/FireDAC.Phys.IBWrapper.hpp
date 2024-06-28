// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.IBWrapper.pas' rev: 34.00 (iOS)

#ifndef Firedac_Phys_IbwrapperHPP
#define Firedac_Phys_IbwrapperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
#include <Data.SqlTimSt.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Consts.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.IBCli.hpp>
#include <FireDAC.Phys.IBMeta.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Ibwrapper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBLib;
class DELPHICLASS TIBObject;
class DELPHICLASS TFDIBError;
class DELPHICLASS EIBNativeException;
class DELPHICLASS TIBError;
struct TIBPBInfo;
class DELPHICLASS TIBPBWriter;
class DELPHICLASS TIBPBReader;
class DELPHICLASS TIBEnv;
class DELPHICLASS TIBDatabase;
class DELPHICLASS TIBTransaction;
class DELPHICLASS TIBEventSlice;
class DELPHICLASS TIBEvents;
class DELPHICLASS TIBVariable;
class DELPHICLASS TIBVariables;
class DELPHICLASS TIBBlob;
class DELPHICLASS TIBBlobStream;
class DELPHICLASS TIBArray;
class DELPHICLASS TIBStatement;
class DELPHICLASS TIBService;
class DELPHICLASS TIBBackup;
class DELPHICLASS TFBNBackup;
class DELPHICLASS TIBSDump;
class DELPHICLASS TIBRestore;
class DELPHICLASS TFBNRestore;
class DELPHICLASS TIBOnlineValidate;
class DELPHICLASS TIBRepair;
class DELPHICLASS TIBTrace;
class DELPHICLASS TIBSecurity;
class DELPHICLASS TIBConfig;
class DELPHICLASS TIBInfo;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIBProtocol : unsigned int { ipLocal, ipTCPIP, ipNetBEUI, ipSPX };

enum DECLSPEC_DENUM TIBCharacterSet : unsigned int { csNONE, csASCII, csBIG_5, csCYRL, csDOS437, csDOS850, csDOS852, csDOS857, csDOS860, csDOS861, csDOS863, csDOS865, csEUCJ_0208, csGB_2312, csISO8859_1, csISO8859_2, csKSC_5601, csNEXT, csOCTETS, csSJIS_0208, csUNICODE_FSS, csWIN1250, csWIN1251, csWIN1252, csWIN1253, csWIN1254, csDOS737, csDOS775, csDOS858, csDOS862, csDOS864, csDOS866, csDOS869, csWIN1255, csWIN1256, csWIN1257, csISO8859_3, csISO8859_4, csISO8859_5, csISO8859_6, csISO8859_7, csISO8859_8, csISO8859_9, csISO8859_13, csISO8859_15, csKOI8R, csKOI8U, csUTF8, csUNICODE_LE, csUNICODE_BE };

enum DECLSPEC_DENUM TIBOpenMode : unsigned int { omOpen, omCreate, omOpenOrCreate };

enum DECLSPEC_DENUM TIBPageSize : unsigned int { ps1024, ps2048, ps4096, ps8192, ps16384 };

enum DECLSPEC_DENUM Firedac_Phys_Ibwrapper__1 : unsigned int { iuModified, iuUpdated, iuInserted, iuDeleted, iuTruncated };

typedef System::Set<Firedac_Phys_Ibwrapper__1, Firedac_Phys_Ibwrapper__1::iuModified, Firedac_Phys_Ibwrapper__1::iuTruncated> TIBUpdateStatus;

class PASCALIMPLEMENTATION TIBLib : public Firedac::Stan::Util::TFDLibrary
{
	typedef Firedac::Stan::Util::TFDLibrary inherited;
	
private:
	System::Syncobjs::TCriticalSection* FLock;
	bool FThreadSafe;
	int __fastcall GetIDUTF8();
	void __fastcall LoadBase(const System::UnicodeString AVendorHome, const System::UnicodeString AVendorLib, bool AThreadSafe);
	
protected:
	virtual void __fastcall LoadEntries();
	virtual void __fastcall GetLibraryInfo();
	
public:
	Firedac::Phys::Ibmeta::TFDPhysIBBrand FBrand;
	bool FEmbedded;
	Firedac::Phys::Ibcli::TBLOB_get FBLOB_get;
	Firedac::Phys::Ibcli::TBLOB_put FBLOB_put;
	Firedac::Phys::Ibcli::Tisc_add_user Fisc_add_user;
	Firedac::Phys::Ibcli::Tisc_array_gen_sdl Fisc_array_gen_sdl;
	Firedac::Phys::Ibcli::Tisc_array_get_slice Fisc_array_get_slice;
	Firedac::Phys::Ibcli::Tisc_array_lookup_bounds Fisc_array_lookup_bounds;
	Firedac::Phys::Ibcli::Tisc_array_lookup_desc Fisc_array_lookup_desc;
	Firedac::Phys::Ibcli::Tisc_array_put_slice Fisc_array_put_slice;
	Firedac::Phys::Ibcli::Tisc_array_set_desc Fisc_array_set_desc;
	Firedac::Phys::Ibcli::Tisc_array_gen_sdl2 Fisc_array_gen_sdl2;
	Firedac::Phys::Ibcli::Tisc_array_get_slice2 Fisc_array_get_slice2;
	Firedac::Phys::Ibcli::Tisc_array_lookup_bounds2 Fisc_array_lookup_bounds2;
	Firedac::Phys::Ibcli::Tisc_array_lookup_desc2 Fisc_array_lookup_desc2;
	Firedac::Phys::Ibcli::Tisc_array_put_slice2 Fisc_array_put_slice2;
	Firedac::Phys::Ibcli::Tisc_array_set_desc2 Fisc_array_set_desc2;
	Firedac::Phys::Ibcli::Tisc_attach_database Fisc_attach_database;
	Firedac::Phys::Ibcli::Tisc_blob_default_desc Fisc_blob_default_desc;
	Firedac::Phys::Ibcli::Tisc_blob_gen_bpb Fisc_blob_gen_bpb;
	Firedac::Phys::Ibcli::Tisc_blob_info Fisc_blob_info;
	Firedac::Phys::Ibcli::Tisc_blob_lookup_desc Fisc_blob_lookup_desc;
	Firedac::Phys::Ibcli::Tisc_blob_set_desc Fisc_blob_set_desc;
	Firedac::Phys::Ibcli::Tisc_cancel_blob Fisc_cancel_blob;
	Firedac::Phys::Ibcli::Tisc_cancel_events Fisc_cancel_events;
	Firedac::Phys::Ibcli::Tisc_close Fisc_close;
	Firedac::Phys::Ibcli::Tisc_close_blob Fisc_close_blob;
	Firedac::Phys::Ibcli::Tisc_commit_retaining Fisc_commit_retaining;
	Firedac::Phys::Ibcli::Tisc_commit_transaction Fisc_commit_transaction;
	Firedac::Phys::Ibcli::Tisc_compile_request Fisc_compile_request;
	Firedac::Phys::Ibcli::Tisc_compile_request2 Fisc_compile_request2;
	Firedac::Phys::Ibcli::Tisc_create_blob Fisc_create_blob;
	Firedac::Phys::Ibcli::Tisc_create_blob2 Fisc_create_blob2;
	Firedac::Phys::Ibcli::Tisc_create_database Fisc_create_database;
	Firedac::Phys::Ibcli::Tisc_database_info Fisc_database_info;
	Firedac::Phys::Ibcli::Tisc_ddl Fisc_ddl;
	Firedac::Phys::Ibcli::Tisc_declare Fisc_declare;
	Firedac::Phys::Ibcli::Tisc_decode_date Fisc_decode_date;
	Firedac::Phys::Ibcli::Tisc_decode_sql_date Fisc_decode_sql_date;
	Firedac::Phys::Ibcli::Tisc_decode_sql_time Fisc_decode_sql_time;
	Firedac::Phys::Ibcli::Tisc_decode_timestamp Fisc_decode_timestamp;
	Firedac::Phys::Ibcli::Tisc_delete_user Fisc_delete_user;
	Firedac::Phys::Ibcli::Tisc_describe Fisc_describe;
	Firedac::Phys::Ibcli::Tisc_describe_bind Fisc_describe_bind;
	Firedac::Phys::Ibcli::Tisc_detach_database Fisc_detach_database;
	Firedac::Phys::Ibcli::Tisc_drop_database Fisc_drop_database;
	Firedac::Phys::Ibcli::Tisc_dsql_alloc_statement2 Fisc_dsql_alloc_statement2;
	Firedac::Phys::Ibcli::Tisc_dsql_allocate_statement Fisc_dsql_allocate_statement;
	Firedac::Phys::Ibcli::Tisc_dsql_describe Fisc_dsql_describe;
	Firedac::Phys::Ibcli::Tisc_dsql_describe_bind Fisc_dsql_describe_bind;
	Firedac::Phys::Ibcli::Tisc_dsql_exec_immed2 Fisc_dsql_exec_immed2;
	Firedac::Phys::Ibcli::Tisc_dsql_exec_immed3_m Fisc_dsql_exec_immed3_m;
	Firedac::Phys::Ibcli::Tisc_dsql_execute Fisc_dsql_execute;
	Firedac::Phys::Ibcli::Tisc_dsql_execute_immediate Fisc_dsql_execute_immediate;
	Firedac::Phys::Ibcli::Tisc_dsql_execute_immediate_m Fisc_dsql_execute_immediate_m;
	Firedac::Phys::Ibcli::Tisc_dsql_execute_m Fisc_dsql_execute_m;
	Firedac::Phys::Ibcli::Tisc_dsql_execute2 Fisc_dsql_execute2;
	Firedac::Phys::Ibcli::Tisc_dsql_execute2_m Fisc_dsql_execute2_m;
	Firedac::Phys::Ibcli::Tisc_dsql_fetch Fisc_dsql_fetch;
	Firedac::Phys::Ibcli::Tisc_dsql_fetch_m Fisc_dsql_fetch_m;
	Firedac::Phys::Ibcli::Tisc_dsql_finish Fisc_dsql_finish;
	Firedac::Phys::Ibcli::Tisc_dsql_free_statement Fisc_dsql_free_statement;
	Firedac::Phys::Ibcli::Tisc_dsql_insert Fisc_dsql_insert;
	Firedac::Phys::Ibcli::Tisc_dsql_insert_m Fisc_dsql_insert_m;
	Firedac::Phys::Ibcli::Tisc_dsql_prepare Fisc_dsql_prepare;
	Firedac::Phys::Ibcli::Tisc_dsql_prepare_m Fisc_dsql_prepare_m;
	Firedac::Phys::Ibcli::Tisc_dsql_release Fisc_dsql_release;
	Firedac::Phys::Ibcli::Tisc_dsql_set_cursor_name Fisc_dsql_set_cursor_name;
	Firedac::Phys::Ibcli::Tisc_dsql_sql_info Fisc_dsql_sql_info;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_close Fisc_embed_dsql_close;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_declare Fisc_embed_dsql_declare;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_describe Fisc_embed_dsql_describe;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_describe_bind Fisc_embed_dsql_describe_bind;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_execute Fisc_embed_dsql_execute;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_execute_immed Fisc_embed_dsql_execute_immed;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_execute2 Fisc_embed_dsql_execute2;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_fetch Fisc_embed_dsql_fetch;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_insert Fisc_embed_dsql_insert;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_open Fisc_embed_dsql_open;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_open2 Fisc_embed_dsql_open2;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_prepare Fisc_embed_dsql_prepare;
	Firedac::Phys::Ibcli::Tisc_embed_dsql_release Fisc_embed_dsql_release;
	Firedac::Phys::Ibcli::Tisc_encode_date Fisc_encode_date;
	Firedac::Phys::Ibcli::Tisc_encode_sql_date Fisc_encode_sql_date;
	Firedac::Phys::Ibcli::Tisc_encode_sql_time Fisc_encode_sql_time;
	Firedac::Phys::Ibcli::Tisc_encode_timestamp Fisc_encode_timestamp;
	Firedac::Phys::Ibcli::Tisc_event_block Fisc_event_block;
	Firedac::Phys::Ibcli::Tisc_event_counts Fisc_event_counts;
	Firedac::Phys::Ibcli::Tisc_execute Fisc_execute;
	Firedac::Phys::Ibcli::Tisc_execute_immediate Fisc_execute_immediate;
	Firedac::Phys::Ibcli::Tisc_expand_dpb Fisc_expand_dpb;
	Firedac::Phys::Ibcli::Tisc_fetch Fisc_fetch;
	Firedac::Phys::Ibcli::Tisc_free Fisc_free;
	Firedac::Phys::Ibcli::Tisc_ftof Fisc_ftof;
	Firedac::Phys::Ibcli::Tisc_get_segment Fisc_get_segment;
	Firedac::Phys::Ibcli::Tisc_get_slice Fisc_get_slice;
	Firedac::Phys::Ibcli::Tisc_interprete Fisc_interprete;
	Firedac::Phys::Ibcli::Tisc_modify_dpb Fisc_modify_dpb;
	Firedac::Phys::Ibcli::Tisc_modify_user Fisc_modify_user;
	Firedac::Phys::Ibcli::Tisc_open Fisc_open;
	Firedac::Phys::Ibcli::Tisc_open_blob Fisc_open_blob;
	Firedac::Phys::Ibcli::Tisc_open_blob2 Fisc_open_blob2;
	Firedac::Phys::Ibcli::Tisc_portable_integer Fisc_portable_integer;
	Firedac::Phys::Ibcli::Tisc_prepare Fisc_prepare;
	Firedac::Phys::Ibcli::Tisc_prepare_transaction Fisc_prepare_transaction;
	Firedac::Phys::Ibcli::Tisc_prepare_transaction2 Fisc_prepare_transaction2;
	Firedac::Phys::Ibcli::Tisc_print_blr Fisc_print_blr;
	Firedac::Phys::Ibcli::Tisc_print_sqlerror Fisc_print_sqlerror;
	Firedac::Phys::Ibcli::Tisc_print_status Fisc_print_status;
	Firedac::Phys::Ibcli::Tisc_put_segment Fisc_put_segment;
	Firedac::Phys::Ibcli::Tisc_put_slice Fisc_put_slice;
	Firedac::Phys::Ibcli::Tisc_qtoq Fisc_qtoq;
	Firedac::Phys::Ibcli::Tisc_que_events Fisc_que_events;
	Firedac::Phys::Ibcli::Tisc_receive Fisc_receive;
	Firedac::Phys::Ibcli::Tisc_reconnect_transaction Fisc_reconnect_transaction;
	Firedac::Phys::Ibcli::Tisc_release_request Fisc_release_request;
	Firedac::Phys::Ibcli::Tisc_request_info Fisc_request_info;
	Firedac::Phys::Ibcli::Tisc_rollback_retaining Fisc_rollback_retaining;
	Firedac::Phys::Ibcli::Tisc_rollback_transaction Fisc_rollback_transaction;
	Firedac::Phys::Ibcli::Tisc_seek_blob Fisc_seek_blob;
	Firedac::Phys::Ibcli::Tisc_send Fisc_send;
	Firedac::Phys::Ibcli::Tisc_service_attach Fisc_service_attach;
	Firedac::Phys::Ibcli::Tisc_service_detach Fisc_service_detach;
	Firedac::Phys::Ibcli::Tisc_service_query Fisc_service_query;
	Firedac::Phys::Ibcli::Tisc_service_start Fisc_service_start;
	Firedac::Phys::Ibcli::Tisc_set_debug Fisc_set_debug;
	Firedac::Phys::Ibcli::Tisc_sql_interprete Fisc_sql_interprete;
	Firedac::Phys::Ibcli::Tisc_sqlcode Fisc_sqlcode;
	Firedac::Phys::Ibcli::Tisc_start_and_send Fisc_start_and_send;
	Firedac::Phys::Ibcli::Tisc_start_multiple Fisc_start_multiple;
	Firedac::Phys::Ibcli::Tisc_start_request Fisc_start_request;
	Firedac::Phys::Ibcli::Tisc_start_transaction Fisc_start_transaction;
	Firedac::Phys::Ibcli::Tisc_transact_request Fisc_transact_request;
	Firedac::Phys::Ibcli::Tisc_transaction_info Fisc_transaction_info;
	Firedac::Phys::Ibcli::Tisc_unwind_request Fisc_unwind_request;
	Firedac::Phys::Ibcli::Tisc_vax_integer Fisc_vax_integer;
	Firedac::Phys::Ibcli::Tisc_version Fisc_version;
	Firedac::Phys::Ibcli::Tisc_vtof Fisc_vtof;
	Firedac::Phys::Ibcli::Tisc_vtov Fisc_vtov;
	Firedac::Phys::Ibcli::Tisc_wait_for_event Fisc_wait_for_event;
	Firedac::Phys::Ibcli::Tisc_reset_fpe Fisc_reset_fpe;
	Firedac::Phys::Ibcli::Tisc_get_client_version Fisc_get_client_version;
	Firedac::Phys::Ibcli::Tisc_get_client_major_version Fisc_get_client_major_version;
	Firedac::Phys::Ibcli::Tisc_get_client_minor_version Fisc_get_client_minor_version;
	Firedac::Phys::Ibcli::Tisc_release_savepoint Fisc_release_savepoint;
	Firedac::Phys::Ibcli::Tisc_rollback_savepoint Fisc_rollback_savepoint;
	Firedac::Phys::Ibcli::Tisc_start_savepoint Fisc_start_savepoint;
	Firedac::Phys::Ibcli::Tfb_interpret Ffb_interpret;
	Firedac::Phys::Ibcli::Tisc_dsql_batch_execute Fisc_dsql_batch_execute;
	Firedac::Phys::Ibcli::Tfb_sqlstate Ffb_sqlstate;
	Firedac::Phys::Ibcli::Tfb_cancel_operation Ffb_cancel_operation;
	Firedac::Phys::Ibcli::Tfb_shutdown Ffb_shutdown;
	Firedac::Phys::Ibcli::Tfb_shutdown_callback Ffb_shutdown_callback;
	Firedac::Phys::Ibcli::Tfb_ping Ffb_ping;
	__fastcall TIBLib(const System::UnicodeString ADriverID, System::TObject* AOwningObj);
	__fastcall virtual ~TIBLib();
	void __fastcall LoadFB(const System::UnicodeString AVendorHome, const System::UnicodeString AVendorLib, bool AEmbedded, bool AThreadSafe);
	void __fastcall LoadIB(const System::UnicodeString AVendorHome, const System::UnicodeString AVendorLib, bool AEmbedded, bool AThreadSafe);
	virtual void __fastcall Unload();
	void __fastcall Lock();
	void __fastcall Unlock();
	System::Int8 __fastcall getb(Firedac::Phys::Ibcli::PBSTREAM p);
	int __fastcall putb(System::Int8 x, Firedac::Phys::Ibcli::PBSTREAM p);
	int __fastcall putbx(System::Int8 x, Firedac::Phys::Ibcli::PBSTREAM p);
	bool __fastcall IsUTF8(int ACSID);
	System::UnicodeString __fastcall GetUTF8CSName(int ACSID);
	int __fastcall GetBytesPerChar(int ACSID);
	void __fastcall ISCTmSt2DlpTmSt(const Firedac::Phys::Ibcli::ISC_TIMESTAMP &AISCTmSt, Data::Sqltimst::TSQLTimeStamp &ASQLTmSt);
	void __fastcall DlpTmSt2ISCTmSt(const Data::Sqltimst::TSQLTimeStamp &ASQLTmSt, Firedac::Phys::Ibcli::ISC_TIMESTAMP &AISCTmSt);
	void __fastcall ISCDt2DlpDt(const int AISCDt, int &ADt);
	void __fastcall DlpDt2ISCDt(const int ADt, int &AISCDt);
	void __fastcall ISCTm2DlpTm(const unsigned AISCTm, int &ATm);
	void __fastcall DlpTm2ISCTm(const int ATm, unsigned &AISCTm);
	__property Firedac::Phys::Ibmeta::TFDPhysIBBrand Brand = {read=FBrand, nodefault};
	__property int IDUTF8 = {read=GetIDUTF8, nodefault};
};


class PASCALIMPLEMENTATION TIBObject : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TIBEnv* FEnv;
	System::TObject* FOwningObj;
	TIBError* __fastcall GetError();
	TIBLib* __fastcall GetLib();
	
public:
	__fastcall TIBObject(TIBEnv* AEnv, System::TObject* AOwningObj);
	void __fastcall Check(NativeInt AStatus, System::TObject* AInitiator = (System::TObject*)(0x0));
	__property TIBEnv* Env = {read=FEnv};
	__property TIBLib* Lib = {read=GetLib};
	__property TIBError* Error = {read=GetError};
	__property System::TObject* OwningObj = {read=FOwningObj};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBObject() { }
	
};


class PASCALIMPLEMENTATION TFDIBError : public Firedac::Stan::Error::TFDDBError
{
	typedef Firedac::Stan::Error::TFDDBError inherited;
	
private:
	int FExceptionCode;
	int FSQLCode;
	int FLineNo;
	int FColNo;
	System::UnicodeString FSQLState;
	int __fastcall GetErrClass();
	int __fastcall GetErrCode();
	int __fastcall GetFacility();
	
protected:
	virtual void __fastcall Assign(Firedac::Stan::Error::TFDDBError* ASrc);
	virtual void __fastcall LoadFromStorage(const Firedac::Stan::Intf::_di_IFDStanStorage AStorage);
	virtual void __fastcall SaveToStorage(const Firedac::Stan::Intf::_di_IFDStanStorage AStorage);
	
public:
	__property int ExceptionCode = {read=FExceptionCode, nodefault};
	__property int SQLCode = {read=FSQLCode, nodefault};
	__property int LineNo = {read=FLineNo, nodefault};
	__property int ColNo = {read=FColNo, nodefault};
	__property int Facility = {read=GetFacility, nodefault};
	__property int ErrClass = {read=GetErrClass, nodefault};
	__property int ErrCode = {read=GetErrCode, nodefault};
	__property System::UnicodeString SQLState = {read=FSQLState};
public:
	/* TFDDBError.Create */ inline __fastcall virtual TFDIBError()/* overload */ : Firedac::Stan::Error::TFDDBError() { }
	/* TFDDBError.Create */ inline __fastcall virtual TFDIBError(int ALevel, int AErrorCode, const System::UnicodeString AMessage, const System::UnicodeString AObjName, Firedac::Stan::Error::TFDCommandExceptionKind AKind, int ACmdOffset, int ARowIndex)/* overload */ : Firedac::Stan::Error::TFDDBError(ALevel, AErrorCode, AMessage, AObjName, AKind, ACmdOffset, ARowIndex) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDIBError() { }
	
};


class PASCALIMPLEMENTATION EIBNativeException : public Firedac::Stan::Error::EFDDBEngineException
{
	typedef Firedac::Stan::Error::EFDDBEngineException inherited;
	
public:
	TFDIBError* operator[](int AIndex) { return this->Errors[AIndex]; }
	
private:
	HIDESBASE TFDIBError* __fastcall GetErrors(int AIndex);
	
protected:
	virtual Firedac::Stan::Error::TFDDBErrorClass __fastcall GetErrorClass();
	
public:
	__fastcall EIBNativeException(TIBError* AError)/* overload */;
	__property TFDIBError* Errors[int AIndex] = {read=GetErrors/*, default*/};
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual EIBNativeException()/* overload */ : Firedac::Stan::Error::EFDDBEngineException() { }
	/* EFDDBEngineException.Create */ inline __fastcall EIBNativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~EIBNativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIBNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIBNativeException(NativeUInt Ident)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIBNativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIBNativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIBNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBNativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBNativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High, AHelpContext) { }
	
};


class PASCALIMPLEMENTATION TIBError : public TIBObject
{
	typedef TIBObject inherited;
	
private:
	Firedac::Phys::Ibcli::TISCStatusVector FStatusVector;
	NativeInt FStatus;
	Firedac::Stan::Error::EFDDBEngineException* FInfo;
	
public:
	__fastcall virtual ~TIBError();
	HIDESBASE void __fastcall Check(NativeInt AStatus, System::TObject* AInitiator = (System::TObject*)(0x0));
	void __fastcall ClearInfo();
	void __fastcall CheckAllocateInfo();
	bool __fastcall IsWarning();
	__property Firedac::Stan::Error::EFDDBEngineException* Info = {read=FInfo};
	__property NativeInt Status = {read=FStatus};
public:
	/* TIBObject.Create */ inline __fastcall TIBError(TIBEnv* AEnv, System::TObject* AOwningObj) : TIBObject(AEnv, AOwningObj) { }
	
};


enum DECLSPEC_DENUM TIBPBParamType : unsigned int { prNone, prNoneNoZ, prCard, prByte, prStrg, prIgno };

struct DECLSPEC_DRECORD TIBPBInfo
{
public:
	System::UnicodeString Name;
	TIBPBParamType ParamType;
	System::Byte Code;
};


typedef TIBPBInfo *PIBPBInfo;

typedef System::StaticArray<TIBPBInfo, 255> TIBPBInfoArr;

typedef TIBPBInfoArr *PIBPBInfoArr;

typedef TIBPBParamType __fastcall (__closure *TIBPBInfoFilterFunc)(const TIBPBInfo &AInfo);

class PASCALIMPLEMENTATION TIBPBWriter : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TIBLib* FLib;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	int FFinalSize;
	int FBufferSize;
	System::RawByteString FBuffer;
	System::PByte __fastcall CheckBufferSize(int ABytesToAdd);
	System::RawByteString __fastcall GetAsBlock();
	Firedac::Phys::Ibcli::PISC_SCHAR __fastcall GetAsPByte();
	short __fastcall GetLen();
	
public:
	__fastcall TIBPBWriter(TIBLib* ALib, Firedac::Stan::Util::TFDEncoder* AEncoder);
	void __fastcall Reset();
	void __fastcall AddByte(System::Byte AByte);
	void __fastcall AddCard(unsigned ACard);
	void __fastcall AddDWord(unsigned ADWord);
	void __fastcall AddShortString(const System::UnicodeString AString);
	void __fastcall AddLongString(const System::UnicodeString AString);
	void __fastcall AddWord(System::Word AWord);
	void __fastcall AddParams(System::Classes::TStrings* AParams, PIBPBInfoArr ApInfos, System::Byte AMaxCode, TIBPBInfoFilterFunc AFilter);
	__property System::RawByteString AsBlock = {read=GetAsBlock};
	__property Firedac::Phys::Ibcli::PISC_SCHAR AsPByte = {read=GetAsPByte};
	__property short Len = {read=GetLen, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBPBWriter() { }
	
};


class PASCALIMPLEMENTATION TIBPBReader : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TIBLib* FLib;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	System::RawByteString FBuffer;
	int FPos;
	bool __fastcall GetEof();
	System::RawByteString __fastcall GetAsBlock();
	Firedac::Phys::Ibcli::PISC_SCHAR __fastcall GetAsPByte();
	short __fastcall GetLen();
	
public:
	__fastcall TIBPBReader(TIBLib* ALib, Firedac::Stan::Util::TFDEncoder* AEncoder);
	void __fastcall Reset(const System::RawByteString ABuffer)/* overload */;
	void __fastcall Reset(short ALen)/* overload */;
	System::Byte __fastcall GetByte();
	System::Word __fastcall GetWord();
	int __fastcall GetInteger();
	System::UnicodeString __fastcall GetLongString();
	__property bool Eof = {read=GetEof, nodefault};
	__property System::RawByteString AsBlock = {read=GetAsBlock};
	__property Firedac::Phys::Ibcli::PISC_SCHAR AsPByte = {read=GetAsPByte};
	__property short Len = {read=GetLen, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBPBReader() { }
	
};


class PASCALIMPLEMENTATION TIBEnv : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TIBLib* FLib;
	TIBError* FError;
	System::TObject* FOwningObj;
	Firedac::Stan::Intf::_di_IFDMoniClient FMonitor;
	bool FTracing;
	bool __fastcall GetTracing();
	
public:
	__fastcall TIBEnv(TIBLib* ALib, System::TObject* AOwningObj);
	__fastcall virtual ~TIBEnv();
	System::RawByteString __fastcall BuildPB(Firedac::Stan::Util::TFDEncoder* AEncoder, System::Classes::TStrings* AParams, System::Byte ATypeInfo, System::Byte AVersion, PIBPBInfoArr ApInfos, System::Byte AMaxCode, TIBPBInfoFilterFunc AFilter);
	void __fastcall Trace(const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	void __fastcall Trace(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	__property bool Tracing = {read=GetTracing, write=FTracing, nodefault};
	__property Firedac::Stan::Intf::_di_IFDMoniClient Monitor = {read=FMonitor, write=FMonitor};
	__property TIBLib* Lib = {read=FLib};
	__property TIBError* Error = {read=FError};
	__property System::TObject* OwningObj = {read=FOwningObj};
};


class PASCALIMPLEMENTATION TIBDatabase : public TIBObject
{
	typedef TIBObject inherited;
	
private:
	System::Classes::TStrings* FList;
	bool FOwnHandle;
	Firedac::Stan::Util::TFDBuffer* FBuffer;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	TIBPBParamType __fastcall FilterDBParam(const TIBPBInfo &AInfo);
	
public:
	void *FDBHandle;
	__fastcall TIBDatabase(TIBEnv* AEnv, System::TObject* AOwningObj);
	__fastcall TIBDatabase(TIBEnv* AEnv, void * AHandle, System::TObject* AOwningObj);
	__fastcall virtual ~TIBDatabase();
	bool __fastcall Attach(const System::UnicodeString ADBName, System::Classes::TStrings* AParams, bool ARetExists);
	void __fastcall CreateDatabase(const System::UnicodeString ADBName, System::Classes::TStrings* AParams);
	void __fastcall Detach();
	void __fastcall Cancel();
	void __fastcall Drop();
	void __fastcall Ping();
	void __fastcall GetDatabaseInfo(int AInfo, System::PByte ABuff, int ASize);
	int __fastcall GetDatabaseInfoInt(int AInfo);
	System::UnicodeString __fastcall GetDatabaseInfoStr(int AInfo);
	bool __fastcall GetDatabaseInfoBool(int AInfo);
	System::Classes::TStrings* __fastcall GetDatabaseInfoUserNames(int AInfo);
	System::Classes::TStrings* __fastcall GetDatabaseInfoOpers(int AInfo);
	System::Classes::TStrings* __fastcall GetDatabaseInfoInts(int AInfo);
	System::Classes::TStrings* __fastcall GetDatabaseInfoStrsCnt(int AInfo);
	__property Firedac::Stan::Util::TFDBuffer* Buffer = {read=FBuffer};
	__property Firedac::Stan::Util::TFDEncoder* Encoder = {read=FEncoder};
	__property System::Classes::TStrings* db_id = {read=GetDatabaseInfoStrsCnt, index=4};
	__property int reads = {read=GetDatabaseInfoInt, index=5, nodefault};
	__property int writes = {read=GetDatabaseInfoInt, index=6, nodefault};
	__property int fetches = {read=GetDatabaseInfoInt, index=7, nodefault};
	__property int marks = {read=GetDatabaseInfoInt, index=8, nodefault};
	__property int implementation_ = {read=GetDatabaseInfoInt, index=11, nodefault};
	__property System::Classes::TStrings* isc_version = {read=GetDatabaseInfoStrsCnt, index=12};
	__property int base_level = {read=GetDatabaseInfoInt, index=13, nodefault};
	__property int page_size = {read=GetDatabaseInfoInt, index=14, nodefault};
	__property int num_buffers = {read=GetDatabaseInfoInt, index=15, nodefault};
	__property System::Classes::TStrings* limbo = {read=GetDatabaseInfoInts, index=16};
	__property int current_memory = {read=GetDatabaseInfoInt, index=17, nodefault};
	__property int max_memory = {read=GetDatabaseInfoInt, index=18, nodefault};
	__property int window_turns = {read=GetDatabaseInfoInt, index=19, nodefault};
	__property int license = {read=GetDatabaseInfoInt, index=20, nodefault};
	__property int allocation = {read=GetDatabaseInfoInt, index=21, nodefault};
	__property int attachment_id = {read=GetDatabaseInfoInt, index=22, nodefault};
	__property System::Classes::TStrings* read_seq_count = {read=GetDatabaseInfoOpers, index=23};
	__property System::Classes::TStrings* read_idx_count = {read=GetDatabaseInfoOpers, index=24};
	__property System::Classes::TStrings* insert_count = {read=GetDatabaseInfoOpers, index=25};
	__property System::Classes::TStrings* update_count = {read=GetDatabaseInfoOpers, index=26};
	__property System::Classes::TStrings* delete_count = {read=GetDatabaseInfoOpers, index=27};
	__property System::Classes::TStrings* backout_count = {read=GetDatabaseInfoOpers, index=28};
	__property System::Classes::TStrings* purge_count = {read=GetDatabaseInfoOpers, index=29};
	__property System::Classes::TStrings* expunge_count = {read=GetDatabaseInfoOpers, index=30};
	__property int sweep_interval = {read=GetDatabaseInfoInt, index=31, nodefault};
	__property int ods_version = {read=GetDatabaseInfoInt, index=32, nodefault};
	__property int ods_minor_version = {read=GetDatabaseInfoInt, index=33, nodefault};
	__property bool no_reserve = {read=GetDatabaseInfoBool, index=34, nodefault};
	__property System::UnicodeString logfile = {read=GetDatabaseInfoStr, index=35};
	__property System::UnicodeString cur_logfile_name = {read=GetDatabaseInfoStr, index=36};
	__property int cur_log_part_offset = {read=GetDatabaseInfoInt, index=37, nodefault};
	__property int num_wal_buffers = {read=GetDatabaseInfoInt, index=38, nodefault};
	__property int wal_buffer_size = {read=GetDatabaseInfoInt, index=39, nodefault};
	__property int wal_ckpt_length = {read=GetDatabaseInfoInt, index=40, nodefault};
	__property int wal_cur_ckpt_interval = {read=GetDatabaseInfoInt, index=41, nodefault};
	__property int wal_prv_ckpt_fname = {read=GetDatabaseInfoInt, index=42, nodefault};
	__property int wal_prv_ckpt_poffset = {read=GetDatabaseInfoInt, index=43, nodefault};
	__property System::UnicodeString wal_recv_ckpt_fname = {read=GetDatabaseInfoStr, index=44};
	__property int wal_recv_ckpt_poffset = {read=GetDatabaseInfoInt, index=45, nodefault};
	__property int wal_grpc_wait_usecs = {read=GetDatabaseInfoInt, index=47, nodefault};
	__property int wal_num_io = {read=GetDatabaseInfoInt, index=48, nodefault};
	__property int wal_avg_io_size = {read=GetDatabaseInfoInt, index=49, nodefault};
	__property int wal_num_commits = {read=GetDatabaseInfoInt, index=50, nodefault};
	__property int wal_avg_grpc_size = {read=GetDatabaseInfoInt, index=51, nodefault};
	__property bool forced_writes = {read=GetDatabaseInfoBool, index=52, nodefault};
	__property System::Classes::TStrings* user_names = {read=GetDatabaseInfoUserNames, index=53};
	__property int page_errors = {read=GetDatabaseInfoInt, index=54, nodefault};
	__property int record_errors = {read=GetDatabaseInfoInt, index=55, nodefault};
	__property int bpage_errors = {read=GetDatabaseInfoInt, index=56, nodefault};
	__property int dpage_errors = {read=GetDatabaseInfoInt, index=57, nodefault};
	__property int ipage_errors = {read=GetDatabaseInfoInt, index=58, nodefault};
	__property int ppage_errors = {read=GetDatabaseInfoInt, index=59, nodefault};
	__property int tpage_errors = {read=GetDatabaseInfoInt, index=60, nodefault};
	__property int set_page_buffers = {read=GetDatabaseInfoInt, index=61, nodefault};
	__property int db_sql_dialect = {read=GetDatabaseInfoInt, index=62, nodefault};
	__property bool db_read_only = {read=GetDatabaseInfoBool, index=63, nodefault};
	__property int db_size_in_pages = {read=GetDatabaseInfoInt, index=64, nodefault};
	__property int db_reads = {read=GetDatabaseInfoInt, index=65, nodefault};
	__property int db_writes = {read=GetDatabaseInfoInt, index=66, nodefault};
	__property int db_fetches = {read=GetDatabaseInfoInt, index=67, nodefault};
	__property int db_marks = {read=GetDatabaseInfoInt, index=68, nodefault};
	__property bool db_group_commit = {read=GetDatabaseInfoBool, index=69, nodefault};
	__property int att_charset = {read=GetDatabaseInfoInt, index=70, nodefault};
	__property int svr_min_ver = {read=GetDatabaseInfoInt, index=71, nodefault};
	__property int ib_env_var = {read=GetDatabaseInfoInt, index=72, nodefault};
	__property int server_tcp_port = {read=GetDatabaseInfoInt, index=73, nodefault};
	__property int db_encrypted = {read=GetDatabaseInfoInt, index=75, nodefault};
	__property int db_eua_active = {read=GetDatabaseInfoInt, index=78, nodefault};
	__property int att_charset2 = {read=GetDatabaseInfoInt, index=101, nodefault};
	__property int db_class = {read=GetDatabaseInfoInt, index=102, nodefault};
	__property System::Classes::TStrings* firebird_version = {read=GetDatabaseInfoStrsCnt, index=103};
	__property int oldest_transaction = {read=GetDatabaseInfoInt, index=104, nodefault};
	__property int oldest_active = {read=GetDatabaseInfoInt, index=105, nodefault};
	__property int oldest_snapshot = {read=GetDatabaseInfoInt, index=106, nodefault};
	__property int next_transaction = {read=GetDatabaseInfoInt, index=107, nodefault};
	__property int db_provider = {read=GetDatabaseInfoInt, index=108, nodefault};
	__property System::Classes::TStrings* active_transactions = {read=GetDatabaseInfoInts, index=109};
	__property int pages_used = {read=GetDatabaseInfoInt, index=124, nodefault};
	__property int pages_free = {read=GetDatabaseInfoInt, index=125, nodefault};
	__property int crypt_state = {read=GetDatabaseInfoInt, index=126, nodefault};
};


class PASCALIMPLEMENTATION TIBTransaction : public TIBObject
{
	typedef TIBObject inherited;
	
	
private:
	typedef System::DynamicArray<Firedac::Phys::Ibcli::TISCTEB> _TIBTransaction__1;
	
	
private:
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	System::Classes::TList* FDatabases;
	System::RawByteString FTPB;
	_TIBTransaction__1 FTEBs;
	System::Classes::TStrings* FParams;
	bool FChanged;
	bool FOwnHandle;
	TIBPBParamType __fastcall FilterTRParam(const TIBPBInfo &AInfo);
	void __fastcall Update();
	void __fastcall SetParams(System::Classes::TStrings* const AValue);
	void __fastcall DoParamsChanged(System::TObject* ASender);
	__int64 __fastcall GetTransactionID();
	
public:
	void *FTRHandle;
	__fastcall TIBTransaction(TIBEnv* AEnv, System::TObject* AOwningObj);
	__fastcall TIBTransaction(TIBEnv* AEnv, void * AHandle, System::TObject* AOwningObj);
	__fastcall virtual ~TIBTransaction();
	void __fastcall AddDatabase(TIBDatabase* ADB);
	void __fastcall RemoveDatabase(TIBDatabase* ADB);
	void __fastcall StartTransaction();
	void __fastcall Commit();
	void __fastcall Rollback();
	void __fastcall CommitRetaining();
	void __fastcall RollbackRetaining();
	void __fastcall Prepare(const System::UnicodeString AMsg);
	__property System::Classes::TStrings* Params = {read=FParams, write=SetParams};
	__property __int64 TransactionID = {read=GetTransactionID};
};


class PASCALIMPLEMENTATION TIBEventSlice : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TIBEvents* FEvents;
	System::Byte *FEventBuffer;
	System::Byte *FResultBuffer;
	int FBufferLength;
	int FEventsID;
	bool FSysAlert;
	Firedac::Phys::Ibcli::TISCEventCounts FStatusVector;
	int FBaseIndex;
	System::Syncobjs::TEvent* FEvent;
	System::Classes::TThread* FThread;
public:
	/* TObject.Create */ inline __fastcall TIBEventSlice() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIBEventSlice() { }
	
};


typedef void __fastcall (__closure *TIBEventsOnFired)(TIBEvents* AEvents, int ABaseIndex, const Firedac::Phys::Ibcli::TISCEventCounts &ACounts);

class PASCALIMPLEMENTATION TIBEvents : public TIBObject
{
	typedef TIBObject inherited;
	
private:
	TIBDatabase* FDatabase;
	System::Classes::TStrings* FNames;
	TIBEventsOnFired FOnFired;
	System::Classes::TList* FSlices;
	void __fastcall QueueEvents(TIBEventSlice* ASlice);
	void __fastcall HandleEvents(TIBEventSlice* ASlice);
	
public:
	__fastcall TIBEvents(TIBDatabase* ADatabase, System::TObject* AOwningObj);
	__fastcall virtual ~TIBEvents();
	void __fastcall Start();
	void __fastcall Stop();
	__property System::Classes::TStrings* Names = {read=FNames};
	__property TIBEventsOnFired OnFired = {read=FOnFired, write=FOnFired};
};


class PASCALIMPLEMENTATION TIBVariable : public TIBObject
{
	typedef TIBObject inherited;
	
private:
	TIBVariables* FVars;
	unsigned long FDataSize;
	unsigned long FIndex;
	System::UnicodeString FDumpLabel;
	Firedac::Stan::Intf::TFDDataType FFDDataType;
	bool __fastcall GetIsNulls(unsigned long ARowIndex);
	short __fastcall GetSQLDataType();
	void __fastcall SetSQLDataType(const short AValue);
	System::UnicodeString __fastcall GetAsString();
	System::UnicodeString __fastcall GetDumpLabel();
	System::UnicodeString __fastcall Getaliasname();
	System::UnicodeString __fastcall Getownname();
	System::UnicodeString __fastcall Getrelname();
	short __fastcall Getsqllen();
	System::UnicodeString __fastcall Getsqlname();
	short __fastcall Getsqlscale();
	short __fastcall Getsqlsubtype();
	short __fastcall Getsqltype();
	void __fastcall Setsqllen(const short AValue);
	void __fastcall Setsqlscale(const short AValue);
	void __fastcall Setsqlsubtype(const short AValue);
	void __fastcall Setsqltype(const short AValue);
	short __fastcall Getsqlprecision();
	void __fastcall Setsqlprecision(const short AValue);
	Firedac::Phys::Ibcli::PXSQLVAR_V1 __fastcall GetBaseXSQLVarV1();
	Firedac::Phys::Ibcli::PXSQLVAR_V2 __fastcall GetBaseXSQLVarV2();
	unsigned long __fastcall GetBindSize();
	Firedac::Phys::Ibcli::PXSQLVAR_V1 __fastcall GetDataXSQLVarV1(unsigned long ARowIndex);
	Firedac::Phys::Ibcli::PXSQLVAR_V2 __fastcall GetDataXSQLVarV2(unsigned long ARowIndex);
	bool __fastcall GetIsNullable();
	void __fastcall SetIsNullable(const bool AValue);
	unsigned long __fastcall GetDataSize();
	void __fastcall LayoutChanged();
	bool __fastcall GetNational();
	System::UnicodeString __fastcall Decode(const void * ASrc, int ASrcLen);
	TIBUpdateStatus __fastcall GetUpdates(unsigned long ARowIndex);
	
protected:
	__property Firedac::Phys::Ibcli::PXSQLVAR_V2 BaseXSQLVarV2 = {read=GetBaseXSQLVarV2};
	__property Firedac::Phys::Ibcli::PXSQLVAR_V1 BaseXSQLVarV1 = {read=GetBaseXSQLVarV1};
	__property Firedac::Phys::Ibcli::PXSQLVAR_V2 DataXSQLVarV2[unsigned long ARowIndex] = {read=GetDataXSQLVarV2};
	__property Firedac::Phys::Ibcli::PXSQLVAR_V1 DataXSQLVarV1[unsigned long ARowIndex] = {read=GetDataXSQLVarV1};
	
public:
	__fastcall TIBVariable(TIBVariables* AVars);
	__fastcall virtual ~TIBVariable();
	bool __fastcall GetData(unsigned long ARowIndex, void * &ApData, /* out */ unsigned long &ALen, bool AByRef = false)/* overload */;
	void __fastcall SetData(unsigned long ARowIndex, void * ApData, unsigned long ALen)/* overload */;
	__classmethod unsigned long __fastcall GetDataTypeSize(short AType, unsigned long ASize);
	bool __fastcall GetData(void *AData, /* out */ unsigned long &ALen)/* overload */;
	bool __fastcall GetData(void *AData)/* overload */;
	void __fastcall SetData(const void *AData, unsigned long ALen = (unsigned long)(0ULL))/* overload */;
	System::UnicodeString __fastcall DumpValue(unsigned long ARowIndex);
	System::UnicodeString __fastcall DumpSQLDataType();
	__property bool IsNulls[unsigned long ARowIndex] = {read=GetIsNulls};
	__property TIBUpdateStatus Updates[unsigned long ARowIndex] = {read=GetUpdates};
	__property unsigned long BindSize = {read=GetBindSize};
	__property System::UnicodeString sqlname = {read=Getsqlname};
	__property System::UnicodeString relname = {read=Getrelname};
	__property System::UnicodeString ownname = {read=Getownname};
	__property System::UnicodeString aliasname = {read=Getaliasname};
	__property TIBVariables* Vars = {read=FVars};
	__property unsigned long Index = {read=FIndex};
	__property System::UnicodeString AsString = {read=GetAsString};
	__property bool National = {read=GetNational, nodefault};
	__property System::UnicodeString DumpLabel = {read=GetDumpLabel, write=FDumpLabel};
	__property unsigned long DataSize = {read=GetDataSize, write=FDataSize};
	__property short SQLDataType = {read=GetSQLDataType, write=SetSQLDataType, nodefault};
	__property Firedac::Stan::Intf::TFDDataType FDDataType = {read=FFDDataType, write=FFDDataType, nodefault};
	__property bool IsNullable = {read=GetIsNullable, write=SetIsNullable, nodefault};
	__property short sqltype = {read=Getsqltype, write=Setsqltype, nodefault};
	__property short sqlscale = {read=Getsqlscale, write=Setsqlscale, nodefault};
	__property short sqlsubtype = {read=Getsqlsubtype, write=Setsqlsubtype, nodefault};
	__property short sqllen = {read=Getsqllen, write=Setsqllen, nodefault};
	__property short sqlprecision = {read=Getsqlprecision, write=Setsqlprecision, nodefault};
};


class PASCALIMPLEMENTATION TIBVariables : public TIBObject
{
	typedef TIBObject inherited;
	
	
private:
	typedef System::DynamicArray<unsigned> _TIBVariables__1;
	
	
public:
	TIBVariable* operator[](unsigned AIndex) { return this->Items[AIndex]; }
	
private:
	System::Classes::TList* FList;
	TIBStatement* FStatement;
	System::Byte *FBuff;
	unsigned FBuffSize;
	System::Word FRowCount;
	bool FV2;
	short __fastcall GetVarCount();
	void __fastcall SetVarCount(short ACount);
	TIBVariable* __fastcall GetItems(unsigned AIndex);
	void __fastcall SetRowCount(System::Word AValue);
	unsigned __fastcall GetBuffSize();
	
protected:
	void __fastcall AllocateBuff();
	void __fastcall ReleaseBuff();
	
public:
	Firedac::Phys::Ibcli::XSQLDA_V2 *FXSQLDA;
	Firedac::Phys::Ibcli::XSQLVAR_V2 *FXSQLVAR;
	_TIBVariables__1 FRowsAffected;
	__fastcall TIBVariables(TIBStatement* AStatement);
	__fastcall virtual ~TIBVariables();
	bool __fastcall AdjustCount();
	void __fastcall CheckBuff();
	__property bool V2 = {read=FV2, nodefault};
	__property TIBStatement* Statement = {read=FStatement};
	__property unsigned BuffSize = {read=GetBuffSize, nodefault};
	__property short VarCount = {read=GetVarCount, write=SetVarCount, nodefault};
	__property System::Word RowCount = {read=FRowCount, write=SetRowCount, nodefault};
	__property TIBVariable* Items[unsigned AIndex] = {read=GetItems/*, default*/};
};


class PASCALIMPLEMENTATION TIBBlob : public TIBObject
{
	typedef TIBObject inherited;
	
private:
	TIBDatabase* FDatabase;
	TIBTransaction* FTransaction;
	System::Word F_type;
	unsigned Fnum_segments;
	unsigned Fmax_segment;
	unsigned Ftotal_length;
	short Fsqlsubtype;
	void __fastcall GetInfo();
	bool __fastcall GetNational();
	bool __fastcall GetIsOpen();
	
public:
	void *FBLHandle;
	Firedac::Phys::Ibcli::GDS_QUAD FBlobID;
	__fastcall TIBBlob(TIBDatabase* ADatabase, TIBTransaction* ATransaction, System::TObject* AOwningObj);
	__fastcall virtual ~TIBBlob();
	void __fastcall Open();
	void __fastcall Add();
	void __fastcall Close();
	unsigned long __fastcall Read(System::PByte ABuff, unsigned long ABuffLen);
	void __fastcall Write(System::PByte ABuff, unsigned long ABuffLen);
	__property unsigned num_segments = {read=Fnum_segments, nodefault};
	__property unsigned max_segment = {read=Fmax_segment, nodefault};
	__property unsigned total_length = {read=Ftotal_length, nodefault};
	__property System::Word _type = {read=F_type, nodefault};
	__property short sqlsubtype = {read=Fsqlsubtype, write=Fsqlsubtype, nodefault};
	__property bool IsOpen = {read=GetIsOpen, nodefault};
	__property TIBDatabase* Database = {read=FDatabase};
	__property TIBTransaction* Transaction = {read=FTransaction};
	__property Firedac::Phys::Ibcli::GDS_QUAD BlobID = {read=FBlobID, write=FBlobID};
	__property bool National = {read=GetNational, nodefault};
};


class PASCALIMPLEMENTATION TIBBlobStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	TIBBlob* FBlob;
	__int64 FPosition;
	unsigned long __fastcall Bytes2Chars(unsigned long ABytes);
	unsigned long __fastcall Chars2Bytes(unsigned long AChars);
	void __fastcall CheckOpen();
	
protected:
	virtual __int64 __fastcall GetSize();
	
public:
	__fastcall TIBBlobStream(TIBBlob* ABlob);
	__fastcall virtual ~TIBBlobStream();
	virtual long __fastcall Read(void *Buffer, long Count)/* overload */;
	virtual long __fastcall Write(const void *Buffer, long Count)/* overload */;
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	__property TIBBlob* Blob = {read=FBlob};
	/* Hoisted overloads: */
	
public:
	inline long __fastcall  Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Offset, long Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Count){ return System::Classes::TStream::Write(Buffer, Count); }
	inline long __fastcall  Seek(long Offset, System::Word Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
	
};


class PASCALIMPLEMENTATION TIBArray : public TIBObject
{
	typedef TIBObject inherited;
	
private:
	TIBDatabase* FDatabase;
	TIBTransaction* FTransaction;
	short FVer;
	System::Byte FV1_sqlsubtype;
	void *FpDesc;
	System::UnicodeString FRelationName;
	System::UnicodeString FFieldName;
	void *FData;
	int FDataLen;
	System::Byte __fastcall Getsqldtype();
	short __fastcall Getsqltype();
	short __fastcall Getsqldimensions();
	System::Word __fastcall Getsqllen();
	System::Int8 __fastcall Getsqlscale();
	System::Byte __fastcall Getsqlsubtype();
	Firedac::Phys::Ibcli::PISC_ARRAY_BOUNDs __fastcall Getsqlbounds();
	void __fastcall Setsqldtype(const System::Byte AValue);
	void __fastcall Setsqltype(const short AValue);
	void __fastcall Setsqllen(const System::Word AValue);
	void __fastcall Setsqlscale(const System::Int8 AValue);
	void __fastcall Setsqlsubtype(const System::Byte AValue);
	void __fastcall Alloc();
	void __fastcall Release();
	int __fastcall GetTotalCount();
	
public:
	Firedac::Phys::Ibcli::GDS_QUAD FArrayID;
	__fastcall TIBArray(TIBDatabase* ADatabase, TIBTransaction* ATransaction, System::TObject* AOwningObj);
	__fastcall virtual ~TIBArray();
	void __fastcall Lookup();
	void __fastcall Init(short AType, short ALen, short ADims, short *ABounds, const int ABounds_High);
	void __fastcall Read();
	void __fastcall Write();
	void * __fastcall GetDataPtr(short *AIndexes, const int AIndexes_High, bool AFlat);
	void __fastcall GetData(void * ASrc, void * &ApData, /* out */ unsigned long &ALen);
	void __fastcall SetData(void * ADest, void * ApData, unsigned long ALen);
	__property TIBDatabase* Database = {read=FDatabase};
	__property TIBTransaction* Transaction = {read=FTransaction};
	__property System::UnicodeString RelationName = {read=FRelationName, write=FRelationName};
	__property System::UnicodeString FieldName = {read=FFieldName, write=FFieldName};
	__property Firedac::Phys::Ibcli::GDS_QUAD ArrayID = {read=FArrayID, write=FArrayID};
	__property System::Byte sqldtype = {read=Getsqldtype, write=Setsqldtype, nodefault};
	__property short sqltype = {read=Getsqltype, write=Setsqltype, nodefault};
	__property System::Byte sqlsubtype = {read=Getsqlsubtype, write=Setsqlsubtype, nodefault};
	__property System::Int8 sqlscale = {read=Getsqlscale, write=Setsqlscale, nodefault};
	__property System::Word sqllen = {read=Getsqllen, write=Setsqllen, nodefault};
	__property short sqldimensions = {read=Getsqldimensions, nodefault};
	__property Firedac::Phys::Ibcli::PISC_ARRAY_BOUNDs sqlbounds = {read=Getsqlbounds};
	__property int TotalCount = {read=GetTotalCount, nodefault};
};


class PASCALIMPLEMENTATION TIBStatement : public TIBObject
{
	typedef TIBObject inherited;
	
private:
	bool FStrsTrim;
	bool FStrsEmpty2Null;
	TIBDatabase* FDatabase;
	TIBTransaction* FTransaction;
	TIBVariables* FInVars;
	TIBVariables* FOutVars;
	System::Word FDialect;
	__int64 FRowsDeleted;
	__int64 FRowsUpdated;
	__int64 FRowsSelected;
	__int64 FRowsInserted;
	bool FEOF;
	bool FClosed;
	bool FSingleRecord;
	int Fsql_stmt_type;
	bool FStrsTrim2Len;
	System::Types::TEndian FGUIDEndian;
	void __fastcall GetRowCounts(bool AForceGetCounts);
	void __fastcall Reset(bool ACheckBuff);
	void __fastcall DumpOutVars(bool AEof);
	void __fastcall DumpInVars();
	unsigned long __fastcall GetMaximumBatchSize();
	__int64 __fastcall GetRowsAffected();
	
public:
	void *FSTHandle;
	__fastcall TIBStatement(TIBDatabase* ADatabase, TIBTransaction* ATransaction, System::TObject* AOwningObj);
	__fastcall virtual ~TIBStatement();
	void __fastcall Prepare(const System::UnicodeString ASQL);
	void __fastcall DescribeSelect();
	void __fastcall DescribeBind();
	void __fastcall Execute(bool AForceGetCounts);
	void __fastcall ExecuteImmediate(const System::UnicodeString ASQL);
	void __fastcall ExecuteBatch();
	void __fastcall Open(bool ASingleRecord);
	bool __fastcall Fetch();
	void __fastcall Unprepare();
	void __fastcall Cancel();
	void __fastcall Close();
	void __fastcall GetSQLInfo(int AInfo, System::PByte ABuff, int ASize);
	int __fastcall GetSQLInfoInt(int AInfo);
	System::UnicodeString __fastcall GetSQLInfoStr(int AInfo);
	__property bool StrsTrim = {read=FStrsTrim, write=FStrsTrim, nodefault};
	__property bool StrsEmpty2Null = {read=FStrsEmpty2Null, write=FStrsEmpty2Null, nodefault};
	__property bool StrsTrim2Len = {read=FStrsTrim2Len, write=FStrsTrim2Len, nodefault};
	__property System::Types::TEndian GUIDEndian = {read=FGUIDEndian, write=FGUIDEndian, nodefault};
	__property System::Word Dialect = {read=FDialect, write=FDialect, nodefault};
	__property TIBDatabase* Database = {read=FDatabase};
	__property TIBTransaction* Transaction = {read=FTransaction};
	__property TIBVariables* OutVars = {read=FOutVars};
	__property TIBVariables* InVars = {read=FInVars};
	__property unsigned long MaximumBatchSize = {read=GetMaximumBatchSize};
	__property __int64 RowsInserted = {read=FRowsInserted};
	__property __int64 RowsUpdated = {read=FRowsUpdated};
	__property __int64 RowsDeleted = {read=FRowsDeleted};
	__property __int64 RowsSelected = {read=FRowsSelected};
	__property __int64 RowsAffected = {read=GetRowsAffected};
	__property bool Eof = {read=FEOF, nodefault};
	__property bool Closed = {read=FClosed, nodefault};
	__property int sql_stmt_type = {read=Fsql_stmt_type, nodefault};
	__property System::UnicodeString sql_get_plan = {read=GetSQLInfoStr, index=22};
	__property System::UnicodeString sql_explain_plan = {read=GetSQLInfoStr, index=26};
};


class PASCALIMPLEMENTATION TIBService : public TIBObject
{
	typedef TIBObject inherited;
	
private:
	unsigned FConnectTimeout;
	unsigned FQueryTimeout;
	TIBProtocol FProtocol;
	System::UnicodeString FPassword;
	System::UnicodeString FHost;
	int FPort;
	System::UnicodeString FInstanceName;
	System::UnicodeString FUserName;
	System::UnicodeString FSqlRoleName;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	System::UnicodeString FSEPassword;
	
protected:
	virtual void __fastcall GetAttachParams(TIBPBWriter* ABld);
	virtual void __fastcall GetServiceParams(TIBPBWriter* ABld);
	__property Firedac::Stan::Util::TFDEncoder* Encoder = {read=FEncoder};
	
public:
	void *FSvcHandle;
	__fastcall TIBService(TIBEnv* AEnv, System::TObject* AOwningObj);
	__fastcall virtual ~TIBService();
	void __fastcall Attach();
	void __fastcall Detach();
	virtual void __fastcall Start();
	virtual bool __fastcall QueryString(/* out */ System::UnicodeString &AMessage);
	__property TIBProtocol Protocol = {read=FProtocol, write=FProtocol, default=0};
	__property System::UnicodeString Host = {read=FHost, write=FHost};
	__property int Port = {read=FPort, write=FPort, default=0};
	__property System::UnicodeString InstanceName = {read=FInstanceName, write=FInstanceName};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property System::UnicodeString SEPassword = {read=FSEPassword, write=FSEPassword};
	__property System::UnicodeString SqlRoleName = {read=FSqlRoleName, write=FSqlRoleName};
	__property unsigned ConnectTimeout = {read=FConnectTimeout, write=FConnectTimeout, default=0};
	__property unsigned QueryTimeout = {read=FQueryTimeout, write=FQueryTimeout, default=0};
};


enum DECLSPEC_DENUM Firedac_Phys_Ibwrapper__12 : unsigned int { boIgnoreChecksum, boIgnoreLimbo, boMetadataOnly, boNoGarbageCollect, boOldDescriptions, boNonTransportable, boConvert, boExpand, boNoTriggers, boZip };

typedef System::Set<Firedac_Phys_Ibwrapper__12, Firedac_Phys_Ibwrapper__12::boIgnoreChecksum, Firedac_Phys_Ibwrapper__12::boZip> TIBBackupOptions;

enum DECLSPEC_DENUM TIBBackupMode : unsigned int { bmBackup, bmArchiveDatabase, bmArchiveJournals };

enum DECLSPEC_DENUM Firedac_Phys_Ibwrapper__22 : unsigned int { bsTime, bsDelta, bsReads, bsWrites };

typedef System::Set<Firedac_Phys_Ibwrapper__22, Firedac_Phys_Ibwrapper__22::bsTime, Firedac_Phys_Ibwrapper__22::bsWrites> TIBBackupStatistics;

class PASCALIMPLEMENTATION TIBBackup : public TIBService
{
	typedef TIBService inherited;
	
private:
	TIBBackupMode FMode;
	System::Classes::TStrings* FBackupFiles;
	bool FVerbose;
	System::UnicodeString FDatabaseName;
	TIBBackupOptions FOptions;
	System::UnicodeString FEncryptKeyName;
	TIBBackupStatistics FStatistics;
	System::UnicodeString FSkipData;
	void __fastcall SetBackupFiles(System::Classes::TStrings* const AValue);
	
protected:
	virtual void __fastcall GetServiceParams(TIBPBWriter* ABld);
	
public:
	__fastcall TIBBackup(TIBEnv* AEnv, System::TObject* AOwningObj);
	__fastcall virtual ~TIBBackup();
	__property TIBBackupMode Mode = {read=FMode, write=FMode, default=0};
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=FDatabaseName};
	__property System::Classes::TStrings* BackupFiles = {read=FBackupFiles, write=SetBackupFiles};
	__property bool Verbose = {read=FVerbose, write=FVerbose, default=0};
	__property TIBBackupOptions Options = {read=FOptions, write=FOptions, default=0};
	__property System::UnicodeString EncryptKeyName = {read=FEncryptKeyName, write=FEncryptKeyName};
	__property System::UnicodeString SkipData = {read=FSkipData, write=FSkipData};
	__property TIBBackupStatistics Statistics = {read=FStatistics, write=FStatistics, default=0};
};


enum DECLSPEC_DENUM Firedac_Phys_Ibwrapper__42 : unsigned int { noNoTriggers };

typedef System::Set<Firedac_Phys_Ibwrapper__42, Firedac_Phys_Ibwrapper__42::noNoTriggers, Firedac_Phys_Ibwrapper__42::noNoTriggers> TFBNBackupOptions;

enum DECLSPEC_DENUM TFBNBackupDirect : unsigned int { ndDefault, ndOn, ndOff };

class PASCALIMPLEMENTATION TFBNBackup : public TIBService
{
	typedef TIBService inherited;
	
private:
	System::UnicodeString FBackupFile;
	System::UnicodeString FDatabaseName;
	int FLevel;
	TFBNBackupOptions FOptions;
	TFBNBackupDirect FDirect;
	
protected:
	virtual void __fastcall GetServiceParams(TIBPBWriter* ABld);
	
public:
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=FDatabaseName};
	__property System::UnicodeString BackupFile = {read=FBackupFile, write=FBackupFile};
	__property int Level = {read=FLevel, write=FLevel, default=0};
	__property TFBNBackupOptions Options = {read=FOptions, write=FOptions, default=0};
	__property TFBNBackupDirect Direct = {read=FDirect, write=FDirect, default=0};
public:
	/* TIBService.Create */ inline __fastcall TFBNBackup(TIBEnv* AEnv, System::TObject* AOwningObj) : TIBService(AEnv, AOwningObj) { }
	/* TIBService.Destroy */ inline __fastcall virtual ~TFBNBackup() { }
	
};


enum DECLSPEC_DENUM Firedac_Phys_Ibwrapper__62 : unsigned int { doOnline };

typedef System::Set<Firedac_Phys_Ibwrapper__62, Firedac_Phys_Ibwrapper__62::doOnline, Firedac_Phys_Ibwrapper__62::doOnline> TIBSDumpOptions;

class PASCALIMPLEMENTATION TIBSDump : public TIBService
{
	typedef TIBService inherited;
	
private:
	System::UnicodeString FDatabaseName;
	System::Classes::TStrings* FBackupFiles;
	bool FOverwrite;
	TIBSDumpOptions FOptions;
	void __fastcall SetBackupFiles(System::Classes::TStrings* const AValue);
	
protected:
	virtual void __fastcall GetServiceParams(TIBPBWriter* ABld);
	
public:
	__fastcall TIBSDump(TIBEnv* AEnv, System::TObject* AOwningObj);
	__fastcall virtual ~TIBSDump();
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=FDatabaseName};
	__property System::Classes::TStrings* BackupFiles = {read=FBackupFiles, write=SetBackupFiles};
	__property bool Overwrite = {read=FOverwrite, write=FOverwrite, nodefault};
	__property TIBSDumpOptions Options = {read=FOptions, write=FOptions, nodefault};
};


enum DECLSPEC_DENUM Firedac_Phys_Ibwrapper__82 : unsigned int { roDeactivateIdx, roNoShadow, roNoValidity, roOneAtATime, roReplace, roUseAllSpace, roValidate, roFixFSSData, roFixFSSMetaData, roMetaDataOnly };

typedef System::Set<Firedac_Phys_Ibwrapper__82, Firedac_Phys_Ibwrapper__82::roDeactivateIdx, Firedac_Phys_Ibwrapper__82::roMetaDataOnly> TIBRestoreOptions;

enum DECLSPEC_DENUM TIBRestoreMode : unsigned int { rmRestore, rmArchiveRecover };

class PASCALIMPLEMENTATION TIBRestore : public TIBService
{
	typedef TIBService inherited;
	
private:
	TIBRestoreMode FMode;
	System::Classes::TStrings* FBackupFiles;
	bool FVerbose;
	System::UnicodeString FDatabaseName;
	TIBRestoreOptions FOptions;
	unsigned FPageSize;
	unsigned FPageBuffers;
	System::UnicodeString FEUAPassword;
	System::UnicodeString FEUAUserName;
	System::UnicodeString FFixCharSet;
	System::UnicodeString FDecryptPassword;
	System::TDateTime FUntilTimestamp;
	TIBBackupStatistics FStatistics;
	void __fastcall SetBackupFiles(System::Classes::TStrings* const AValue);
	
protected:
	virtual void __fastcall GetServiceParams(TIBPBWriter* ABld);
	
public:
	__fastcall TIBRestore(TIBEnv* AEnv, System::TObject* AOwningObj);
	__fastcall virtual ~TIBRestore();
	__property TIBRestoreMode Mode = {read=FMode, write=FMode, default=0};
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=FDatabaseName};
	__property System::Classes::TStrings* BackupFiles = {read=FBackupFiles, write=SetBackupFiles};
	__property bool Verbose = {read=FVerbose, write=FVerbose, default=0};
	__property TIBRestoreOptions Options = {read=FOptions, write=FOptions, default=0};
	__property unsigned PageSize = {read=FPageSize, write=FPageSize, default=0};
	__property unsigned PageBuffers = {read=FPageBuffers, write=FPageBuffers, default=0};
	__property System::UnicodeString FixCharSet = {read=FFixCharSet, write=FFixCharSet};
	__property System::UnicodeString EUAUserName = {read=FEUAUserName, write=FEUAUserName};
	__property System::UnicodeString EUAPassword = {read=FEUAPassword, write=FEUAPassword};
	__property System::UnicodeString DecryptPassword = {read=FDecryptPassword, write=FDecryptPassword};
	__property System::TDateTime UntilTimestamp = {read=FUntilTimestamp, write=FUntilTimestamp};
	__property TIBBackupStatistics Statistics = {read=FStatistics, write=FStatistics, default=0};
};


class PASCALIMPLEMENTATION TFBNRestore : public TIBService
{
	typedef TIBService inherited;
	
private:
	System::Classes::TStrings* FBackupFiles;
	System::UnicodeString FDatabaseName;
	TFBNBackupOptions FOptions;
	void __fastcall SetBackupFile(System::Classes::TStrings* const AValue);
	
protected:
	virtual void __fastcall GetServiceParams(TIBPBWriter* ABld);
	
public:
	__fastcall TFBNRestore(TIBEnv* AEnv, System::TObject* AOwningObj);
	__fastcall virtual ~TFBNRestore();
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=FDatabaseName};
	__property System::Classes::TStrings* BackupFiles = {read=FBackupFiles, write=SetBackupFile};
	__property TFBNBackupOptions Options = {read=FOptions, write=FOptions, default=0};
};


class PASCALIMPLEMENTATION TIBOnlineValidate : public TIBService
{
	typedef TIBService inherited;
	
private:
	System::UnicodeString FDatabaseName;
	System::UnicodeString FIndexesExclude;
	System::UnicodeString FIndexesInclude;
	System::UnicodeString FTablesExclude;
	System::UnicodeString FTablesInclude;
	int FLockTimeout;
	
protected:
	virtual void __fastcall GetServiceParams(TIBPBWriter* ABld);
	
public:
	__fastcall TIBOnlineValidate(TIBEnv* AEnv, System::TObject* AOwningObj);
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=FDatabaseName};
	__property System::UnicodeString TablesInclude = {read=FTablesInclude, write=FTablesInclude};
	__property System::UnicodeString TablesExclude = {read=FTablesExclude, write=FTablesExclude};
	__property System::UnicodeString IndexesInclude = {read=FIndexesInclude, write=FIndexesInclude};
	__property System::UnicodeString IndexesExclude = {read=FIndexesExclude, write=FIndexesExclude};
	__property int LockTimeout = {read=FLockTimeout, write=FLockTimeout, default=10};
public:
	/* TIBService.Destroy */ inline __fastcall virtual ~TIBOnlineValidate() { }
	
};


enum DECLSPEC_DENUM Firedac_Phys_Ibwrapper__23 : unsigned int { roValidateFull, roValidatePages, roMendRecords, roIgnoreChecksum, roKillShadows };

typedef System::Set<Firedac_Phys_Ibwrapper__23, Firedac_Phys_Ibwrapper__23::roValidateFull, Firedac_Phys_Ibwrapper__23::roKillShadows> TIBRepairOptions;

enum DECLSPEC_DENUM TIBRepairMode : unsigned int { rmCheckOnly, rmRepair, rmSweep };

class PASCALIMPLEMENTATION TIBRepair : public TIBService
{
	typedef TIBService inherited;
	
private:
	System::UnicodeString FDatabaseName;
	TIBRepairOptions FOptions;
	TIBRepairMode FMode;
	
protected:
	virtual void __fastcall GetServiceParams(TIBPBWriter* ABld);
	
public:
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=FDatabaseName};
	__property TIBRepairMode Mode = {read=FMode, write=FMode, default=0};
	__property TIBRepairOptions Options = {read=FOptions, write=FOptions, default=0};
public:
	/* TIBService.Create */ inline __fastcall TIBRepair(TIBEnv* AEnv, System::TObject* AOwningObj) : TIBService(AEnv, AOwningObj) { }
	/* TIBService.Destroy */ inline __fastcall virtual ~TIBRepair() { }
	
};


enum DECLSPEC_DENUM TIBTraceAction : unsigned int { taStart, taStop, taSuspend, taResume, taList };

class PASCALIMPLEMENTATION TIBTrace : public TIBService
{
	typedef TIBService inherited;
	
private:
	System::UnicodeString FSessionName;
	System::Classes::TStrings* FConfig;
	int FSessionID;
	TIBTraceAction FAction;
	void __fastcall SetConfig(System::Classes::TStrings* const AValue);
	
protected:
	virtual void __fastcall GetServiceParams(TIBPBWriter* ABld);
	
public:
	__fastcall TIBTrace(TIBEnv* AEnv, System::TObject* AOwningObj);
	__fastcall virtual ~TIBTrace();
	virtual bool __fastcall QueryString(/* out */ System::UnicodeString &AMessage);
	__property TIBTraceAction Action = {read=FAction, write=FAction, default=0};
	__property System::UnicodeString SessionName = {read=FSessionName, write=FSessionName};
	__property int SessionID = {read=FSessionID, write=FSessionID, default=0};
	__property System::Classes::TStrings* Config = {read=FConfig, write=SetConfig};
};


enum DECLSPEC_DENUM TIBSecurityValue : unsigned int { svUserName, svPassword, svFirstName, svMiddleName, svLastName, svUserID, svGroupID, svGroupName, svRoleName };

typedef System::Set<TIBSecurityValue, TIBSecurityValue::svUserName, TIBSecurityValue::svRoleName> TIBSecurityValues;

enum DECLSPEC_DENUM TIBSecurityAction : unsigned int { saAddUser, saDeleteUser, saModifyUser, saDisplayUser, saDisplayUsers };

class PASCALIMPLEMENTATION TIBSecurity : public TIBService
{
	typedef TIBService inherited;
	
	
private:
	typedef System::StaticArray<System::UnicodeString, 9> _TIBSecurity__1;
	
	
private:
	_TIBSecurity__1 FValues;
	TIBSecurityValues FModified;
	TIBSecurityAction FAction;
	Firedac::Dats::TFDDatSTable* FUsers;
	System::UnicodeString FEUADatabase;
	
protected:
	virtual void __fastcall GetAttachParams(TIBPBWriter* ABld);
	virtual void __fastcall GetServiceParams(TIBPBWriter* ABld);
	
public:
	__fastcall virtual ~TIBSecurity();
	int __fastcall GetInt(const int AIndex);
	System::UnicodeString __fastcall GetStr(const int AIndex);
	void __fastcall SetInt(const int AIndex, const int AValue);
	void __fastcall SetStr(const int AIndex, const System::UnicodeString AValue);
	void __fastcall QuerySecurity();
	__property Firedac::Dats::TFDDatSTable* Users = {read=FUsers};
	__property TIBSecurityAction Action = {read=FAction, write=FAction, nodefault};
	__property TIBSecurityValues Modified = {read=FModified, write=FModified, default=0};
	__property System::UnicodeString AUserName = {read=GetStr, write=SetStr, index=0};
	__property System::UnicodeString APassword = {read=GetStr, write=SetStr, index=1};
	__property System::UnicodeString AFirstName = {read=GetStr, write=SetStr, index=2};
	__property System::UnicodeString AMiddleName = {read=GetStr, write=SetStr, index=3};
	__property System::UnicodeString ALastName = {read=GetStr, write=SetStr, index=4};
	__property int AUserID = {read=GetInt, write=SetInt, index=5, nodefault};
	__property int AGroupID = {read=GetInt, write=SetInt, index=6, nodefault};
	__property System::UnicodeString AGroupName = {read=GetStr, write=SetStr, index=7};
	__property System::UnicodeString ARoleName = {read=GetStr, write=SetStr, index=8};
	__property System::UnicodeString EUADatabase = {read=FEUADatabase, write=FEUADatabase};
public:
	/* TIBService.Create */ inline __fastcall TIBSecurity(TIBEnv* AEnv, System::TObject* AOwningObj) : TIBService(AEnv, AOwningObj) { }
	
};


enum DECLSPEC_DENUM TIBReserveSpace : unsigned int { rsUseFull, rsReserve };

enum DECLSPEC_DENUM TIBWriteMode : unsigned int { wmAsync, wmSync, wmDirect };

enum DECLSPEC_DENUM TIBAccessMode : unsigned int { amReadOnly, amReadWrite };

enum DECLSPEC_DENUM TIBShutdownMode : unsigned int { smForce, smDenyTransactions, smDenyAttachements };

class PASCALIMPLEMENTATION TIBConfig : public TIBService
{
	typedef TIBService inherited;
	
private:
	System::UnicodeString FDatabaseName;
	int FProperty;
	unsigned FValue;
	
protected:
	virtual void __fastcall GetServiceParams(TIBPBWriter* ABld);
	
public:
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=FDatabaseName};
	void __fastcall SetPageBuffers(const unsigned AValue);
	void __fastcall SetSQLDialect(const unsigned AValue);
	void __fastcall SetSweepInterval(const unsigned AValue);
	void __fastcall SetReserveSpace(const TIBReserveSpace AValue);
	void __fastcall SetWriteMode(const TIBWriteMode AValue);
	void __fastcall SetAccessMode(const TIBAccessMode AValue);
	void __fastcall SetArchiveDumps(const unsigned AValue);
	void __fastcall SetArchiveSweep(const unsigned AValue);
	void __fastcall ShutdownDB(TIBShutdownMode AMode, unsigned ATimeout);
	void __fastcall OnlineDB();
	void __fastcall ActivateShadow();
public:
	/* TIBService.Create */ inline __fastcall TIBConfig(TIBEnv* AEnv, System::TObject* AOwningObj) : TIBService(AEnv, AOwningObj) { }
	/* TIBService.Destroy */ inline __fastcall virtual ~TIBConfig() { }
	
};


class PASCALIMPLEMENTATION TIBInfo : public TIBService
{
	typedef TIBService inherited;
	
	
public:
	struct DECLSPEC_DRECORD TVersion
	{
	public:
		int FService;
		System::UnicodeString FServerStr;
		unsigned __int64 FServer;
		System::UnicodeString FImplementation;
	};
	
	
	struct DECLSPEC_DRECORD TLicense
	{
		
	public:
		struct DECLSPEC_DRECORD TCertificate
		{
		public:
			System::UnicodeString FID;
			System::UnicodeString FKey;
			System::UnicodeString FDesc;
		};
		
		
		
	public:
		System::TArray__1<TCertificate> FCertificates;
		int FLicenseMask;
		int FCapabilities;
		int FUsers;
		System::UnicodeString FProduct;
	};
	
	
	struct DECLSPEC_DRECORD TConfig
	{
		
	public:
		struct DECLSPEC_DRECORD TEntry
		{
		public:
			int FID;
			int FValue;
		};
		
		
		
	public:
		System::TArray__1<TEntry> FConfig;
		System::UnicodeString FServerPath;
		System::UnicodeString FLockPath;
		System::UnicodeString FMessagePath;
		System::UnicodeString FSecurityDBFile;
	};
	
	
	struct DECLSPEC_DRECORD TUsage
	{
	public:
		int FAttachments;
		int FDatabases;
		System::TArray__1<System::UnicodeString> FDBNames;
	};
	
	
	
protected:
	__interface DELPHIINTERFACE TRequestProc;
	typedef System::DelphiInterface<TRequestProc> _di_TRequestProc;
	__interface TRequestProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(TIBPBWriter* AReqWrt) = 0 ;
	};
	
	__interface DELPHIINTERFACE TParseFunc;
	typedef System::DelphiInterface<TParseFunc> _di_TParseFunc;
	__interface TParseFunc  : public System::IInterface 
	{
		virtual bool __fastcall Invoke(TIBPBReader* AOutRdr) = 0 ;
	};
	
	
protected:
	void __fastcall QueryInfo(_di_TRequestProc ARequest, _di_TParseFunc AParse);
	
public:
	virtual void __fastcall Start();
	void __fastcall GetVersion(/* out */ TVersion &AVersion);
	void __fastcall GetLicense(/* out */ TLicense &ALicense);
	void __fastcall GetConfig(/* out */ TConfig &AConfig);
	void __fastcall GetUsage(/* out */ TUsage &AUsage);
public:
	/* TIBService.Create */ inline __fastcall TIBInfo(TIBEnv* AEnv, System::TObject* AOwningObj) : TIBService(AEnv, AOwningObj) { }
	/* TIBService.Destroy */ inline __fastcall virtual ~TIBInfo() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibwrapper */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_IBWRAPPER)
using namespace Firedac::Phys::Ibwrapper;
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
#endif	// Firedac_Phys_IbwrapperHPP
