// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.SQLiteDef.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_SqlitedefHPP
#define Firedac_Phys_SqlitedefHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Sqlitedef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysSQLiteConnectionDefParams;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDSQLiteOpenMode : unsigned int { omCreateUTF8, omCreateUTF16, omReadWrite, omReadOnly };

enum DECLSPEC_DENUM TFDSQLiteEncrypt : unsigned int { enNo, enAes_128, enAes_192, enAes_256, enAes_ctr_128, enAes_ctr_192, enAes_ctr_256, enAes_ecb_128, enAes_ecb_192, enAes_ecb_256 };

enum DECLSPEC_DENUM TFDSQLiteLockingMode : unsigned int { lmNormal, lmExclusive };

enum DECLSPEC_DENUM TFDSQLiteSynchronous : unsigned int { snFull, snNormal, snOff };

enum DECLSPEC_DENUM TFDSQLiteJournalMode : unsigned int { jmDelete, jmTruncate, jmPersist, jmMemory, jmWAL, jmOff };

enum DECLSPEC_DENUM TFDSQLiteForeignKeys : unsigned int { fkOn, fkOff };

enum DECLSPEC_DENUM TFDSQLiteStringFormat : unsigned int { sfChoose, sfUnicode, sfANSI };

enum DECLSPEC_DENUM TFDSQLiteGUIDFormat : unsigned int { guiString, guiBinary };

enum DECLSPEC_DENUM TFDSQLiteDateTimeFormat : unsigned int { dtfString, dtfBinary, dtfDateTime };

typedef System::StaticArray<System::UnicodeString, 10> Firedac_Phys_Sqlitedef__1;

class PASCALIMPLEMENTATION TFDPhysSQLiteConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
{
	typedef Firedac::Stan::Intf::TFDConnectionDefParams inherited;
	
private:
	HIDESBASE System::UnicodeString __fastcall GetDriverID();
	HIDESBASE void __fastcall SetDriverID(const System::UnicodeString AValue);
	TFDSQLiteOpenMode __fastcall GetOpenMode();
	void __fastcall SetOpenMode(const TFDSQLiteOpenMode AValue);
	TFDSQLiteEncrypt __fastcall GetEncrypt();
	void __fastcall SetEncrypt(const TFDSQLiteEncrypt AValue);
	int __fastcall GetBusyTimeout();
	void __fastcall SetBusyTimeout(const int AValue);
	int __fastcall GetCacheSize();
	void __fastcall SetCacheSize(const int AValue);
	bool __fastcall GetSharedCache();
	void __fastcall SetSharedCache(const bool AValue);
	TFDSQLiteLockingMode __fastcall GetLockingMode();
	void __fastcall SetLockingMode(const TFDSQLiteLockingMode AValue);
	TFDSQLiteSynchronous __fastcall GetSynchronous();
	void __fastcall SetSynchronous(const TFDSQLiteSynchronous AValue);
	TFDSQLiteJournalMode __fastcall GetJournalMode();
	void __fastcall SetJournalMode(const TFDSQLiteJournalMode AValue);
	TFDSQLiteForeignKeys __fastcall GetForeignKeys();
	void __fastcall SetForeignKeys(const TFDSQLiteForeignKeys AValue);
	TFDSQLiteStringFormat __fastcall GetStringFormat();
	void __fastcall SetStringFormat(const TFDSQLiteStringFormat AValue);
	TFDSQLiteGUIDFormat __fastcall GetGUIDFormat();
	void __fastcall SetGUIDFormat(const TFDSQLiteGUIDFormat AValue);
	TFDSQLiteDateTimeFormat __fastcall GetDateTimeFormat();
	void __fastcall SetDateTimeFormat(const TFDSQLiteDateTimeFormat AValue);
	System::UnicodeString __fastcall GetExtensions();
	void __fastcall SetExtensions(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetSQLiteAdvanced();
	void __fastcall SetSQLiteAdvanced(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaDefCatalog();
	void __fastcall SetMetaDefCatalog(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurCatalog();
	void __fastcall SetMetaCurCatalog(const System::UnicodeString AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property TFDSQLiteOpenMode OpenMode = {read=GetOpenMode, write=SetOpenMode, stored=false, default=0};
	__property TFDSQLiteEncrypt Encrypt = {read=GetEncrypt, write=SetEncrypt, stored=false, default=0};
	__property int BusyTimeout = {read=GetBusyTimeout, write=SetBusyTimeout, stored=false, default=10000};
	__property int CacheSize = {read=GetCacheSize, write=SetCacheSize, stored=false, default=10000};
	__property bool SharedCache = {read=GetSharedCache, write=SetSharedCache, stored=false, nodefault};
	__property TFDSQLiteLockingMode LockingMode = {read=GetLockingMode, write=SetLockingMode, stored=false, default=1};
	__property TFDSQLiteSynchronous Synchronous = {read=GetSynchronous, write=SetSynchronous, stored=false, default=2};
	__property TFDSQLiteJournalMode JournalMode = {read=GetJournalMode, write=SetJournalMode, stored=false, default=0};
	__property TFDSQLiteForeignKeys ForeignKeys = {read=GetForeignKeys, write=SetForeignKeys, stored=false, default=0};
	__property TFDSQLiteStringFormat StringFormat = {read=GetStringFormat, write=SetStringFormat, stored=false, default=0};
	__property TFDSQLiteGUIDFormat GUIDFormat = {read=GetGUIDFormat, write=SetGUIDFormat, stored=false, default=0};
	__property TFDSQLiteDateTimeFormat DateTimeFormat = {read=GetDateTimeFormat, write=SetDateTimeFormat, stored=false, default=0};
	__property System::UnicodeString Extensions = {read=GetExtensions, write=SetExtensions, stored=false};
	__property System::UnicodeString SQLiteAdvanced = {read=GetSQLiteAdvanced, write=SetSQLiteAdvanced, stored=false};
	__property System::UnicodeString MetaDefCatalog = {read=GetMetaDefCatalog, write=SetMetaDefCatalog, stored=false};
	__property System::UnicodeString MetaCurCatalog = {read=GetMetaCurCatalog, write=SetMetaCurCatalog, stored=false};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysSQLiteConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysSQLiteConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Firedac_Phys_Sqlitedef__1 C_FDSQLiteEncrypt;
}	/* namespace Sqlitedef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_SQLITEDEF)
using namespace Firedac::Phys::Sqlitedef;
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
#endif	// Firedac_Phys_SqlitedefHPP
