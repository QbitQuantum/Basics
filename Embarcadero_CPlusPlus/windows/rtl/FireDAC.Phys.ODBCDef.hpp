// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ODBCDef.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_OdbcdefHPP
#define Firedac_Phys_OdbcdefHPP

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
#include <FireDAC.Phys.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Odbcdef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysODBCConnectionDefParams;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDODBCNumericFormat : unsigned int { nfBinary, nfString };

enum DECLSPEC_DENUM TFDODBCVersion : unsigned int { ov3_8, ov3_0 };

class PASCALIMPLEMENTATION TFDPhysODBCConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
{
	typedef Firedac::Stan::Intf::TFDConnectionDefParams inherited;
	
private:
	HIDESBASE System::UnicodeString __fastcall GetDriverID();
	HIDESBASE void __fastcall SetDriverID(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetODBCAdvanced();
	void __fastcall SetODBCAdvanced(const System::UnicodeString AValue);
	int __fastcall GetLoginTimeout();
	void __fastcall SetLoginTimeout(const int AValue);
	System::UnicodeString __fastcall GetODBCDriver();
	void __fastcall SetODBCDriver(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetDataSource();
	void __fastcall SetDataSource(const System::UnicodeString AValue);
	TFDODBCNumericFormat __fastcall GetNumericFormat();
	void __fastcall SetNumericFormat(const TFDODBCNumericFormat AValue);
	TFDODBCVersion __fastcall GetODBCVersion();
	void __fastcall SetODBCVersion(const TFDODBCVersion AValue);
	System::UnicodeString __fastcall GetMetaDefCatalog();
	void __fastcall SetMetaDefCatalog(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaDefSchema();
	void __fastcall SetMetaDefSchema(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurCatalog();
	void __fastcall SetMetaCurCatalog(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurSchema();
	void __fastcall SetMetaCurSchema(const System::UnicodeString AValue);
	Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetRDBMS();
	void __fastcall SetRDBMS(const Firedac::Stan::Intf::TFDRDBMSKind AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property System::UnicodeString ODBCAdvanced = {read=GetODBCAdvanced, write=SetODBCAdvanced, stored=false};
	__property int LoginTimeout = {read=GetLoginTimeout, write=SetLoginTimeout, stored=false, nodefault};
	__property System::UnicodeString ODBCDriver = {read=GetODBCDriver, write=SetODBCDriver, stored=false};
	__property System::UnicodeString DataSource = {read=GetDataSource, write=SetDataSource, stored=false};
	__property TFDODBCNumericFormat NumericFormat = {read=GetNumericFormat, write=SetNumericFormat, stored=false, default=1};
	__property TFDODBCVersion ODBCVersion = {read=GetODBCVersion, write=SetODBCVersion, stored=false, default=1};
	__property System::UnicodeString MetaDefCatalog = {read=GetMetaDefCatalog, write=SetMetaDefCatalog, stored=false};
	__property System::UnicodeString MetaDefSchema = {read=GetMetaDefSchema, write=SetMetaDefSchema, stored=false};
	__property System::UnicodeString MetaCurCatalog = {read=GetMetaCurCatalog, write=SetMetaCurCatalog, stored=false};
	__property System::UnicodeString MetaCurSchema = {read=GetMetaCurSchema, write=SetMetaCurSchema, stored=false};
	__property Firedac::Stan::Intf::TFDRDBMSKind RDBMS = {read=GetRDBMS, write=SetRDBMS, stored=false, nodefault};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysODBCConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysODBCConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Odbcdef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ODBCDEF)
using namespace Firedac::Phys::Odbcdef;
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
#endif	// Firedac_Phys_OdbcdefHPP
