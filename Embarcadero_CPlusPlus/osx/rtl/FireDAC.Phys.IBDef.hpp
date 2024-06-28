// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.IBDef.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_IbdefHPP
#define Firedac_Phys_IbdefHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Phys.IBWrapper.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Ibdef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysIBConnectionDefParams;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysIBConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
{
	typedef Firedac::Stan::Intf::TFDConnectionDefParams inherited;
	
private:
	HIDESBASE System::UnicodeString __fastcall GetDriverID();
	HIDESBASE void __fastcall SetDriverID(const System::UnicodeString AValue);
	bool __fastcall GetOSAuthent();
	void __fastcall SetOSAuthent(const bool AValue);
	Firedac::Phys::Ibwrapper::TIBProtocol __fastcall GetProtocol();
	void __fastcall SetProtocol(const Firedac::Phys::Ibwrapper::TIBProtocol AValue);
	System::UnicodeString __fastcall GetServer();
	void __fastcall SetServer(const System::UnicodeString AValue);
	int __fastcall GetPort();
	void __fastcall SetPort(const int AValue);
	int __fastcall GetSQLDialect();
	void __fastcall SetSQLDialect(const int AValue);
	System::UnicodeString __fastcall GetRoleName();
	void __fastcall SetRoleName(const System::UnicodeString AValue);
	Firedac::Phys::Ibwrapper::TIBCharacterSet __fastcall GetCharacterSet();
	void __fastcall SetCharacterSet(const Firedac::Phys::Ibwrapper::TIBCharacterSet AValue);
	bool __fastcall GetExtendedMetadata();
	void __fastcall SetExtendedMetadata(const bool AValue);
	Firedac::Phys::Ibwrapper::TIBOpenMode __fastcall GetOpenMode();
	void __fastcall SetOpenMode(const Firedac::Phys::Ibwrapper::TIBOpenMode AValue);
	Firedac::Phys::Ibwrapper::TIBPageSize __fastcall GetPageSize();
	void __fastcall SetPageSize(const Firedac::Phys::Ibwrapper::TIBPageSize AValue);
	bool __fastcall GetDropDatabase();
	void __fastcall SetDropDatabase(const bool AValue);
	System::UnicodeString __fastcall GetIBAdvanced();
	void __fastcall SetIBAdvanced(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetInstanceName();
	void __fastcall SetInstanceName(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetSEPassword();
	void __fastcall SetSEPassword(const System::UnicodeString AValue);
	System::Types::TEndian __fastcall GetGUIDEndian();
	void __fastcall SetGUIDEndian(const System::Types::TEndian AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property bool OSAuthent = {read=GetOSAuthent, write=SetOSAuthent, stored=false, nodefault};
	__property Firedac::Phys::Ibwrapper::TIBProtocol Protocol = {read=GetProtocol, write=SetProtocol, stored=false, default=0};
	__property System::UnicodeString Server = {read=GetServer, write=SetServer, stored=false};
	__property int Port = {read=GetPort, write=SetPort, stored=false, nodefault};
	__property int SQLDialect = {read=GetSQLDialect, write=SetSQLDialect, stored=false, default=3};
	__property System::UnicodeString RoleName = {read=GetRoleName, write=SetRoleName, stored=false};
	__property Firedac::Phys::Ibwrapper::TIBCharacterSet CharacterSet = {read=GetCharacterSet, write=SetCharacterSet, stored=false, default=0};
	__property bool ExtendedMetadata = {read=GetExtendedMetadata, write=SetExtendedMetadata, stored=false, nodefault};
	__property Firedac::Phys::Ibwrapper::TIBOpenMode OpenMode = {read=GetOpenMode, write=SetOpenMode, stored=false, default=0};
	__property Firedac::Phys::Ibwrapper::TIBPageSize PageSize = {read=GetPageSize, write=SetPageSize, stored=false, default=2};
	__property bool DropDatabase = {read=GetDropDatabase, write=SetDropDatabase, stored=false, nodefault};
	__property System::UnicodeString IBAdvanced = {read=GetIBAdvanced, write=SetIBAdvanced, stored=false};
	__property System::UnicodeString InstanceName = {read=GetInstanceName, write=SetInstanceName, stored=false};
	__property System::UnicodeString SEPassword = {read=GetSEPassword, write=SetSEPassword, stored=false};
	__property System::Types::TEndian GUIDEndian = {read=GetGUIDEndian, write=SetGUIDEndian, stored=false, nodefault};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysIBConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysIBConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibdef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_IBDEF)
using namespace Firedac::Phys::Ibdef;
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
#endif	// Firedac_Phys_IbdefHPP
