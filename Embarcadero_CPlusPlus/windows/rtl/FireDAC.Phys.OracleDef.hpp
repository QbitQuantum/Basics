// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.OracleDef.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_OracledefHPP
#define Firedac_Phys_OracledefHPP

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
namespace Oracledef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysOracleConnectionDefParams;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDOracleAuthMode : unsigned int { amNormal, amSysDBA, amSysOper, amSysASM, amSysBackup, amSysDG, amSysKM };

enum DECLSPEC_DENUM TFDOracleCharacterSet : unsigned int { cs_NLS_LANG_, csUTF8 };

enum DECLSPEC_DENUM TFDOracleBooleanFormat : unsigned int { bfChoose, bfInteger, bfString };

class PASCALIMPLEMENTATION TFDPhysOracleConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
{
	typedef Firedac::Stan::Intf::TFDConnectionDefParams inherited;
	
private:
	HIDESBASE System::UnicodeString __fastcall GetDriverID();
	HIDESBASE void __fastcall SetDriverID(const System::UnicodeString AValue);
	bool __fastcall GetOSAuthent();
	void __fastcall SetOSAuthent(const bool AValue);
	TFDOracleAuthMode __fastcall GetAuthMode();
	void __fastcall SetAuthMode(const TFDOracleAuthMode AValue);
	int __fastcall GetReadTimeout();
	void __fastcall SetReadTimeout(const int AValue);
	int __fastcall GetWriteTimeout();
	void __fastcall SetWriteTimeout(const int AValue);
	TFDOracleCharacterSet __fastcall GetCharacterSet();
	void __fastcall SetCharacterSet(const TFDOracleCharacterSet AValue);
	TFDOracleBooleanFormat __fastcall GetBooleanFormat();
	void __fastcall SetBooleanFormat(const TFDOracleBooleanFormat AValue);
	System::UnicodeString __fastcall GetApplicationName();
	void __fastcall SetApplicationName(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetOracleAdvanced();
	void __fastcall SetOracleAdvanced(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaDefSchema();
	void __fastcall SetMetaDefSchema(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurSchema();
	void __fastcall SetMetaCurSchema(const System::UnicodeString AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property bool OSAuthent = {read=GetOSAuthent, write=SetOSAuthent, stored=false, nodefault};
	__property TFDOracleAuthMode AuthMode = {read=GetAuthMode, write=SetAuthMode, stored=false, default=0};
	__property int ReadTimeout = {read=GetReadTimeout, write=SetReadTimeout, stored=false, nodefault};
	__property int WriteTimeout = {read=GetWriteTimeout, write=SetWriteTimeout, stored=false, nodefault};
	__property TFDOracleCharacterSet CharacterSet = {read=GetCharacterSet, write=SetCharacterSet, stored=false, default=0};
	__property TFDOracleBooleanFormat BooleanFormat = {read=GetBooleanFormat, write=SetBooleanFormat, stored=false, default=0};
	__property System::UnicodeString ApplicationName = {read=GetApplicationName, write=SetApplicationName, stored=false};
	__property System::UnicodeString OracleAdvanced = {read=GetOracleAdvanced, write=SetOracleAdvanced, stored=false};
	__property System::UnicodeString MetaDefSchema = {read=GetMetaDefSchema, write=SetMetaDefSchema, stored=false};
	__property System::UnicodeString MetaCurSchema = {read=GetMetaCurSchema, write=SetMetaCurSchema, stored=false};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysOracleConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysOracleConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Oracledef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ORACLEDEF)
using namespace Firedac::Phys::Oracledef;
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
#endif	// Firedac_Phys_OracledefHPP
