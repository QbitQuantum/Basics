// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MySQLDef.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_MysqldefHPP
#define Firedac_Phys_MysqldefHPP

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
namespace Mysqldef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysMySQLConnectionDefParams;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDMySQLResultMode : unsigned int { rmStore, rmUse, rmChoose };

enum DECLSPEC_DENUM TFDMySQLCharacterSet : unsigned int { csNone, csBig5, csDec8, csCp850, csHp8, csKoi8r, csLatin1, csLatin2, csSwe7, csAscii, csUjis, csSjis, csCp1251, csHebrew, csTis620, csEuckr, csKoi8u, csGb2312, csGreek, csCp1250, csGbk, csLatin5, csArmscii8, csCp866, csKeybcs2, csMacce, csMacroman, csCp852, csLatin7, csCp1256, csCp1257, csBinary, csUtf8, csUtf8mb4 };

enum DECLSPEC_DENUM TFDMySQLTinyIntFormat : unsigned int { tifBoolean, tifInteger };

class PASCALIMPLEMENTATION TFDPhysMySQLConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
{
	typedef Firedac::Stan::Intf::TFDConnectionDefParams inherited;
	
private:
	HIDESBASE System::UnicodeString __fastcall GetDriverID();
	HIDESBASE void __fastcall SetDriverID(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetServer();
	void __fastcall SetServer(const System::UnicodeString AValue);
	int __fastcall GetPort();
	void __fastcall SetPort(const int AValue);
	bool __fastcall GetCompress();
	void __fastcall SetCompress(const bool AValue);
	bool __fastcall GetUseSSL();
	void __fastcall SetUseSSL(const bool AValue);
	int __fastcall GetLoginTimeout();
	void __fastcall SetLoginTimeout(const int AValue);
	int __fastcall GetReadTimeout();
	void __fastcall SetReadTimeout(const int AValue);
	int __fastcall GetWriteTimeout();
	void __fastcall SetWriteTimeout(const int AValue);
	TFDMySQLResultMode __fastcall GetResultMode();
	void __fastcall SetResultMode(const TFDMySQLResultMode AValue);
	TFDMySQLCharacterSet __fastcall GetCharacterSet();
	void __fastcall SetCharacterSet(const TFDMySQLCharacterSet AValue);
	TFDMySQLTinyIntFormat __fastcall GetTinyIntFormat();
	void __fastcall SetTinyIntFormat(const TFDMySQLTinyIntFormat AValue);
	System::UnicodeString __fastcall GetMetaDefCatalog();
	void __fastcall SetMetaDefCatalog(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurCatalog();
	void __fastcall SetMetaCurCatalog(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetSSL_key();
	void __fastcall SetSSL_key(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetSSL_cert();
	void __fastcall SetSSL_cert(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetSSL_ca();
	void __fastcall SetSSL_ca(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetSSL_capath();
	void __fastcall SetSSL_capath(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetSSL_cipher();
	void __fastcall SetSSL_cipher(const System::UnicodeString AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property System::UnicodeString Server = {read=GetServer, write=SetServer, stored=false};
	__property int Port = {read=GetPort, write=SetPort, stored=false, default=3306};
	__property bool Compress = {read=GetCompress, write=SetCompress, stored=false, nodefault};
	__property bool UseSSL = {read=GetUseSSL, write=SetUseSSL, stored=false, nodefault};
	__property int LoginTimeout = {read=GetLoginTimeout, write=SetLoginTimeout, stored=false, nodefault};
	__property int ReadTimeout = {read=GetReadTimeout, write=SetReadTimeout, stored=false, nodefault};
	__property int WriteTimeout = {read=GetWriteTimeout, write=SetWriteTimeout, stored=false, nodefault};
	__property TFDMySQLResultMode ResultMode = {read=GetResultMode, write=SetResultMode, stored=false, default=0};
	__property TFDMySQLCharacterSet CharacterSet = {read=GetCharacterSet, write=SetCharacterSet, stored=false, nodefault};
	__property TFDMySQLTinyIntFormat TinyIntFormat = {read=GetTinyIntFormat, write=SetTinyIntFormat, stored=false, default=0};
	__property System::UnicodeString MetaDefCatalog = {read=GetMetaDefCatalog, write=SetMetaDefCatalog, stored=false};
	__property System::UnicodeString MetaCurCatalog = {read=GetMetaCurCatalog, write=SetMetaCurCatalog, stored=false};
	__property System::UnicodeString SSL_key = {read=GetSSL_key, write=SetSSL_key, stored=false};
	__property System::UnicodeString SSL_cert = {read=GetSSL_cert, write=SetSSL_cert, stored=false};
	__property System::UnicodeString SSL_ca = {read=GetSSL_ca, write=SetSSL_ca, stored=false};
	__property System::UnicodeString SSL_capath = {read=GetSSL_capath, write=SetSSL_capath, stored=false};
	__property System::UnicodeString SSL_cipher = {read=GetSSL_cipher, write=SetSSL_cipher, stored=false};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysMySQLConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysMySQLConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mysqldef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MYSQLDEF)
using namespace Firedac::Phys::Mysqldef;
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
#endif	// Firedac_Phys_MysqldefHPP
