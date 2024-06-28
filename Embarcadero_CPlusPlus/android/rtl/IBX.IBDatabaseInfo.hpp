// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBDatabaseInfo.pas' rev: 34.00 (Android)

#ifndef Ibx_IbdatabaseinfoHPP
#define Ibx_IbdatabaseinfoHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IBX.IBExternals.hpp>
#include <IBX.IB.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibdatabaseinfo
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBDatabaseInfo;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIBWriteMode : unsigned char { wmASync, wmSync, wmDirect, wmNone };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBDatabaseInfo : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* const Value);
	int __fastcall GetNoOfEncryptions();
	TIBWriteMode __fastcall GetWriteMode();
	
protected:
	bool FIBLoaded;
	Ibx::Ibdatabase::TIBDatabase* FDatabase;
	System::Classes::TStringList* FUserNames;
	System::Classes::TStringList* FBackoutCount;
	System::Classes::TStringList* FDeleteCount;
	System::Classes::TStringList* FExpungeCount;
	System::Classes::TStringList* FInsertCount;
	System::Classes::TStringList* FPurgeCount;
	System::Classes::TStringList* FReadIdxCount;
	System::Classes::TStringList* FReadSeqCount;
	System::Classes::TStringList* FUpdateCount;
	int __fastcall GetAllocation();
	int __fastcall GetBaseLevel();
	System::UnicodeString __fastcall GetDBFileName();
	System::UnicodeString __fastcall GetDBSiteName();
	int __fastcall GetDBImplementationNo();
	int __fastcall GetDBImplementationClass();
	int __fastcall GetNoReserve();
	int __fastcall GetODSMinorVersion();
	int __fastcall GetODSMajorVersion();
	System::Extended __fastcall GetFullODS();
	int __fastcall GetPageSize();
	System::UnicodeString __fastcall GetVersion();
	int __fastcall GetCurrentMemory();
	int __fastcall GetForcedWrites();
	int __fastcall GetMaxMemory();
	int __fastcall GetNumBuffers();
	int __fastcall GetSweepInterval();
	System::Classes::TStringList* __fastcall GetUserNames();
	int __fastcall GetFetches();
	int __fastcall GetMarks();
	int __fastcall GetPreAllocated();
	int __fastcall GetReads();
	int __fastcall GetWrites();
	System::Classes::TStringList* __fastcall GetBackoutCount();
	System::Classes::TStringList* __fastcall GetDeleteCount();
	System::Classes::TStringList* __fastcall GetExpungeCount();
	System::Classes::TStringList* __fastcall GetInsertCount();
	System::Classes::TStringList* __fastcall GetPurgeCount();
	System::Classes::TStringList* __fastcall GetReadIdxCount();
	System::Classes::TStringList* __fastcall GetReadSeqCount();
	System::Classes::TStringList* __fastcall GetUpdateCount();
	System::Classes::TStringList* __fastcall GetOperationCounts(int DBInfoCommand, System::Classes::TStringList* FOperation);
	int __fastcall GetReadOnly();
	int __fastcall GetDBSQLDialect();
	Ibx::Ibintf::_di_IGDSLibrary __fastcall GetGDSLibrary();
	bool __fastcall GetEUAActive();
	bool __fastcall GetGroupCommit();
	bool __fastcall GetEncrypted();
	bool __fastcall GetSepEncrypted();
	int __fastcall GetPageBuffers();
	
public:
	__fastcall virtual TIBDatabaseInfo(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBDatabaseInfo();
	NativeInt __fastcall Call(NativeInt ErrCode, bool RaiseError);
	int __fastcall GetLongDatabaseInfo(int DatabaseInfoCommand);
	System::UnicodeString __fastcall GetStringDatabaseInfo(int DatabaseInfoCommand);
	__property int Allocation = {read=GetAllocation, nodefault};
	__property int BaseLevel = {read=GetBaseLevel, nodefault};
	__property System::UnicodeString DBFileName = {read=GetDBFileName};
	__property System::UnicodeString DBSiteName = {read=GetDBSiteName};
	__property int DBImplementationNo = {read=GetDBImplementationNo, nodefault};
	__property int DBImplementationClass = {read=GetDBImplementationClass, nodefault};
	__property int NoReserve = {read=GetNoReserve, nodefault};
	__property int ODSMinorVersion = {read=GetODSMinorVersion, nodefault};
	__property int ODSMajorVersion = {read=GetODSMajorVersion, nodefault};
	__property System::Extended FullODS = {read=GetFullODS};
	__property int PageSize = {read=GetPageSize, nodefault};
	__property System::UnicodeString Version = {read=GetVersion};
	__property int CurrentMemory = {read=GetCurrentMemory, nodefault};
	__property int ForcedWrites = {read=GetForcedWrites, nodefault};
	__property TIBWriteMode WriteMode = {read=GetWriteMode, nodefault};
	__property int MaxMemory = {read=GetMaxMemory, nodefault};
	__property int PageBuffers = {read=GetPageBuffers, nodefault};
	__property int NumBuffers = {read=GetNumBuffers, nodefault};
	__property int SweepInterval = {read=GetSweepInterval, nodefault};
	__property System::Classes::TStringList* UserNames = {read=GetUserNames};
	__property int Fetches = {read=GetFetches, nodefault};
	__property int Marks = {read=GetMarks, nodefault};
	__property int Reads = {read=GetReads, nodefault};
	__property int Writes = {read=GetWrites, nodefault};
	__property System::Classes::TStringList* BackoutCount = {read=GetBackoutCount};
	__property System::Classes::TStringList* DeleteCount = {read=GetDeleteCount};
	__property System::Classes::TStringList* ExpungeCount = {read=GetExpungeCount};
	__property System::Classes::TStringList* InsertCount = {read=GetInsertCount};
	__property System::Classes::TStringList* PurgeCount = {read=GetPurgeCount};
	__property System::Classes::TStringList* ReadIdxCount = {read=GetReadIdxCount};
	__property System::Classes::TStringList* ReadSeqCount = {read=GetReadSeqCount};
	__property System::Classes::TStringList* UpdateCount = {read=GetUpdateCount};
	__property int DBSQLDialect = {read=GetDBSQLDialect, nodefault};
	__property int ReadOnly = {read=GetReadOnly, nodefault};
	__property bool EUAActive = {read=GetEUAActive, nodefault};
	__property bool GroupCommit = {read=GetGroupCommit, nodefault};
	__property bool Encrypted = {read=GetEncrypted, nodefault};
	__property bool SepEncrypted = {read=GetSepEncrypted, nodefault};
	__property int NoOfEncryptions = {read=GetNoOfEncryptions, nodefault};
	__property int PreAllocated = {read=GetPreAllocated, nodefault};
	
__published:
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=FDatabase, write=SetDatabase};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibdatabaseinfo */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBDATABASEINFO)
using namespace Ibx::Ibdatabaseinfo;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbdatabaseinfoHPP
