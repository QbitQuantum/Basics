// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MSSQLDef.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_MssqldefHPP
#define Firedac_Phys_MssqldefHPP

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
namespace Mssqldef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysMSSQLConnectionDefParams;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDMSSQLVariantFormat : unsigned int { vfString, vfBinary };

enum DECLSPEC_DENUM TFDMSSQLMetaCaseInsCat : unsigned int { mciChoose, mciFalse, mciTrue };

class PASCALIMPLEMENTATION TFDPhysMSSQLConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
{
	typedef Firedac::Stan::Intf::TFDConnectionDefParams inherited;
	
private:
	HIDESBASE System::UnicodeString __fastcall GetDriverID();
	HIDESBASE void __fastcall SetDriverID(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetODBCAdvanced();
	void __fastcall SetODBCAdvanced(const System::UnicodeString AValue);
	int __fastcall GetLoginTimeout();
	void __fastcall SetLoginTimeout(const int AValue);
	System::UnicodeString __fastcall GetServer();
	void __fastcall SetServer(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetNetwork();
	void __fastcall SetNetwork(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetAddress();
	void __fastcall SetAddress(const System::UnicodeString AValue);
	bool __fastcall GetOSAuthent();
	void __fastcall SetOSAuthent(const bool AValue);
	bool __fastcall GetMARS();
	void __fastcall SetMARS(const bool AValue);
	System::UnicodeString __fastcall GetWorkstation();
	void __fastcall SetWorkstation(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetLanguage();
	void __fastcall SetLanguage(const System::UnicodeString AValue);
	bool __fastcall GetEncrypt();
	void __fastcall SetEncrypt(const bool AValue);
	TFDMSSQLVariantFormat __fastcall GetVariantFormat();
	void __fastcall SetVariantFormat(const TFDMSSQLVariantFormat AValue);
	bool __fastcall GetExtendedMetadata();
	void __fastcall SetExtendedMetadata(const bool AValue);
	System::UnicodeString __fastcall GetApplicationName();
	void __fastcall SetApplicationName(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaDefCatalog();
	void __fastcall SetMetaDefCatalog(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaDefSchema();
	void __fastcall SetMetaDefSchema(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurCatalog();
	void __fastcall SetMetaCurCatalog(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurSchema();
	void __fastcall SetMetaCurSchema(const System::UnicodeString AValue);
	bool __fastcall GetMetaCaseIns();
	void __fastcall SetMetaCaseIns(const bool AValue);
	TFDMSSQLMetaCaseInsCat __fastcall GetMetaCaseInsCat();
	void __fastcall SetMetaCaseInsCat(const TFDMSSQLMetaCaseInsCat AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property System::UnicodeString ODBCAdvanced = {read=GetODBCAdvanced, write=SetODBCAdvanced, stored=false};
	__property int LoginTimeout = {read=GetLoginTimeout, write=SetLoginTimeout, stored=false, nodefault};
	__property System::UnicodeString Server = {read=GetServer, write=SetServer, stored=false};
	__property System::UnicodeString Network = {read=GetNetwork, write=SetNetwork, stored=false};
	__property System::UnicodeString Address = {read=GetAddress, write=SetAddress, stored=false};
	__property bool OSAuthent = {read=GetOSAuthent, write=SetOSAuthent, stored=false, nodefault};
	__property bool MARS = {read=GetMARS, write=SetMARS, stored=false, default=1};
	__property System::UnicodeString Workstation = {read=GetWorkstation, write=SetWorkstation, stored=false};
	__property System::UnicodeString Language = {read=GetLanguage, write=SetLanguage, stored=false};
	__property bool Encrypt = {read=GetEncrypt, write=SetEncrypt, stored=false, nodefault};
	__property TFDMSSQLVariantFormat VariantFormat = {read=GetVariantFormat, write=SetVariantFormat, stored=false, default=0};
	__property bool ExtendedMetadata = {read=GetExtendedMetadata, write=SetExtendedMetadata, stored=false, nodefault};
	__property System::UnicodeString ApplicationName = {read=GetApplicationName, write=SetApplicationName, stored=false};
	__property System::UnicodeString MetaDefCatalog = {read=GetMetaDefCatalog, write=SetMetaDefCatalog, stored=false};
	__property System::UnicodeString MetaDefSchema = {read=GetMetaDefSchema, write=SetMetaDefSchema, stored=false};
	__property System::UnicodeString MetaCurCatalog = {read=GetMetaCurCatalog, write=SetMetaCurCatalog, stored=false};
	__property System::UnicodeString MetaCurSchema = {read=GetMetaCurSchema, write=SetMetaCurSchema, stored=false};
	__property bool MetaCaseIns = {read=GetMetaCaseIns, write=SetMetaCaseIns, stored=false, nodefault};
	__property TFDMSSQLMetaCaseInsCat MetaCaseInsCat = {read=GetMetaCaseInsCat, write=SetMetaCaseInsCat, stored=false, default=0};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysMSSQLConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysMSSQLConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mssqldef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MSSQLDEF)
using namespace Firedac::Phys::Mssqldef;
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
#endif	// Firedac_Phys_MssqldefHPP
