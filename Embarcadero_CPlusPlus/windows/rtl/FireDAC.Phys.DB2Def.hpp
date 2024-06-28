// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.DB2Def.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_Db2defHPP
#define Firedac_Phys_Db2defHPP

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
namespace Db2def
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysDB2ConnectionDefParams;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDDB2StringFormat : unsigned int { sfChoose, sfUnicode };

enum DECLSPEC_DENUM TFDDB2TxSupported : unsigned int { tsYes, tsNo };

class PASCALIMPLEMENTATION TFDPhysDB2ConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
{
	typedef Firedac::Stan::Intf::TFDConnectionDefParams inherited;
	
private:
	HIDESBASE System::UnicodeString __fastcall GetDriverID();
	HIDESBASE void __fastcall SetDriverID(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetODBCAdvanced();
	void __fastcall SetODBCAdvanced(const System::UnicodeString AValue);
	int __fastcall GetLoginTimeout();
	void __fastcall SetLoginTimeout(const int AValue);
	System::UnicodeString __fastcall GetAlias();
	void __fastcall SetAlias(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetServer();
	void __fastcall SetServer(const System::UnicodeString AValue);
	int __fastcall GetPort();
	void __fastcall SetPort(const int AValue);
	System::UnicodeString __fastcall GetProtocol();
	void __fastcall SetProtocol(const System::UnicodeString AValue);
	bool __fastcall GetOSAuthent();
	void __fastcall SetOSAuthent(const bool AValue);
	TFDDB2StringFormat __fastcall GetStringFormat();
	void __fastcall SetStringFormat(const TFDDB2StringFormat AValue);
	bool __fastcall GetExtendedMetadata();
	void __fastcall SetExtendedMetadata(const bool AValue);
	TFDDB2TxSupported __fastcall GetTxSupported();
	void __fastcall SetTxSupported(const TFDDB2TxSupported AValue);
	System::UnicodeString __fastcall GetMetaDefSchema();
	void __fastcall SetMetaDefSchema(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurSchema();
	void __fastcall SetMetaCurSchema(const System::UnicodeString AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property System::UnicodeString ODBCAdvanced = {read=GetODBCAdvanced, write=SetODBCAdvanced, stored=false};
	__property int LoginTimeout = {read=GetLoginTimeout, write=SetLoginTimeout, stored=false, nodefault};
	__property System::UnicodeString Alias = {read=GetAlias, write=SetAlias, stored=false};
	__property System::UnicodeString Server = {read=GetServer, write=SetServer, stored=false};
	__property int Port = {read=GetPort, write=SetPort, stored=false, nodefault};
	__property System::UnicodeString Protocol = {read=GetProtocol, write=SetProtocol, stored=false};
	__property bool OSAuthent = {read=GetOSAuthent, write=SetOSAuthent, stored=false, nodefault};
	__property TFDDB2StringFormat StringFormat = {read=GetStringFormat, write=SetStringFormat, stored=false, default=0};
	__property bool ExtendedMetadata = {read=GetExtendedMetadata, write=SetExtendedMetadata, stored=false, nodefault};
	__property TFDDB2TxSupported TxSupported = {read=GetTxSupported, write=SetTxSupported, stored=false, default=0};
	__property System::UnicodeString MetaDefSchema = {read=GetMetaDefSchema, write=SetMetaDefSchema, stored=false};
	__property System::UnicodeString MetaCurSchema = {read=GetMetaCurSchema, write=SetMetaCurSchema, stored=false};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysDB2ConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysDB2ConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Db2def */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_DB2DEF)
using namespace Firedac::Phys::Db2def;
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
#endif	// Firedac_Phys_Db2defHPP
