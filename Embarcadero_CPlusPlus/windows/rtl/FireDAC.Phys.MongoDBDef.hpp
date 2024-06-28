// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MongoDBDef.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_MongodbdefHPP
#define Firedac_Phys_MongodbdefHPP

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
#include <System.JSON.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Mongodbdef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysMongoConnectionDefParams;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysMongoConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
{
	typedef Firedac::Stan::Intf::TFDConnectionDefParams inherited;
	
private:
	HIDESBASE System::UnicodeString __fastcall GetDriverID();
	HIDESBASE void __fastcall SetDriverID(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetServer();
	void __fastcall SetServer(const System::UnicodeString AValue);
	int __fastcall GetPort();
	void __fastcall SetPort(const int AValue);
	System::UnicodeString __fastcall GetMoreHosts();
	void __fastcall SetMoreHosts(const System::UnicodeString AValue);
	bool __fastcall GetUseSSL();
	void __fastcall SetUseSSL(const bool AValue);
	int __fastcall GetLoginTimeout();
	void __fastcall SetLoginTimeout(const int AValue);
	int __fastcall GetReadTimeout();
	void __fastcall SetReadTimeout(const int AValue);
	System::Json::Types::TJsonDateTimeZoneHandling __fastcall GetTimeZone();
	void __fastcall SetTimeZone(const System::Json::Types::TJsonDateTimeZoneHandling AValue);
	System::UnicodeString __fastcall GetMongoAdvanced();
	void __fastcall SetMongoAdvanced(const System::UnicodeString AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property System::UnicodeString Server = {read=GetServer, write=SetServer, stored=false};
	__property int Port = {read=GetPort, write=SetPort, stored=false, default=27017};
	__property System::UnicodeString MoreHosts = {read=GetMoreHosts, write=SetMoreHosts, stored=false};
	__property bool UseSSL = {read=GetUseSSL, write=SetUseSSL, stored=false, nodefault};
	__property int LoginTimeout = {read=GetLoginTimeout, write=SetLoginTimeout, stored=false, default=0};
	__property int ReadTimeout = {read=GetReadTimeout, write=SetReadTimeout, stored=false, default=300};
	__property System::Json::Types::TJsonDateTimeZoneHandling TimeZone = {read=GetTimeZone, write=SetTimeZone, stored=false, default=0};
	__property System::UnicodeString MongoAdvanced = {read=GetMongoAdvanced, write=SetMongoAdvanced, stored=false};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysMongoConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysMongoConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mongodbdef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MONGODBDEF)
using namespace Firedac::Phys::Mongodbdef;
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
#endif	// Firedac_Phys_MongodbdefHPP
