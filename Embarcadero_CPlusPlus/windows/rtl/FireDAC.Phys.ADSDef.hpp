// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ADSDef.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_AdsdefHPP
#define Firedac_Phys_AdsdefHPP

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
#include <FireDAC.Phys.ADSWrapper.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Adsdef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysADSConnectionDefParams;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDADSServerTypes : unsigned int { stNone, stRemote, stLocal, stInternet };

enum DECLSPEC_DENUM TFDADSProtocol : unsigned int { prNone, prUDP, prIPX, prTCPIP, prTLS };

enum DECLSPEC_DENUM TFDADSCharacterSet : unsigned int { csANSI, csOEM };

enum DECLSPEC_DENUM TFDADSCompress : unsigned int { cmNone, cmInternet, cmAlways, cmNever };

enum DECLSPEC_DENUM TFDADSLocking : unsigned int { lcNone, lcProprietary, lcCompatible };

class PASCALIMPLEMENTATION TFDPhysADSConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
{
	typedef Firedac::Stan::Intf::TFDConnectionDefParams inherited;
	
private:
	HIDESBASE System::UnicodeString __fastcall GetDriverID();
	HIDESBASE void __fastcall SetDriverID(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetAlias();
	void __fastcall SetAlias(const System::UnicodeString AValue);
	TFDADSServerTypes __fastcall GetServerTypes();
	void __fastcall SetServerTypes(const TFDADSServerTypes AValue);
	TFDADSProtocol __fastcall GetProtocol();
	void __fastcall SetProtocol(const TFDADSProtocol AValue);
	System::UnicodeString __fastcall GetServer();
	void __fastcall SetServer(const System::UnicodeString AValue);
	int __fastcall GetPort();
	void __fastcall SetPort(const int AValue);
	TFDADSCharacterSet __fastcall GetCharacterSet();
	void __fastcall SetCharacterSet(const TFDADSCharacterSet AValue);
	TFDADSCompress __fastcall GetCompress();
	void __fastcall SetCompress(const TFDADSCompress AValue);
	Firedac::Phys::Adswrapper::TADSTableType __fastcall GetTableType();
	void __fastcall SetTableType(const Firedac::Phys::Adswrapper::TADSTableType AValue);
	System::UnicodeString __fastcall GetTablePassword();
	void __fastcall SetTablePassword(const System::UnicodeString AValue);
	TFDADSLocking __fastcall GetLocking();
	void __fastcall SetLocking(const TFDADSLocking AValue);
	System::UnicodeString __fastcall GetADSAdvanced();
	void __fastcall SetADSAdvanced(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaDefCatalog();
	void __fastcall SetMetaDefCatalog(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurCatalog();
	void __fastcall SetMetaCurCatalog(const System::UnicodeString AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property System::UnicodeString Alias = {read=GetAlias, write=SetAlias, stored=false};
	__property TFDADSServerTypes ServerTypes = {read=GetServerTypes, write=SetServerTypes, stored=false, nodefault};
	__property TFDADSProtocol Protocol = {read=GetProtocol, write=SetProtocol, stored=false, nodefault};
	__property System::UnicodeString Server = {read=GetServer, write=SetServer, stored=false};
	__property int Port = {read=GetPort, write=SetPort, stored=false, nodefault};
	__property TFDADSCharacterSet CharacterSet = {read=GetCharacterSet, write=SetCharacterSet, stored=false, default=0};
	__property TFDADSCompress Compress = {read=GetCompress, write=SetCompress, stored=false, nodefault};
	__property Firedac::Phys::Adswrapper::TADSTableType TableType = {read=GetTableType, write=SetTableType, stored=false, default=0};
	__property System::UnicodeString TablePassword = {read=GetTablePassword, write=SetTablePassword, stored=false};
	__property TFDADSLocking Locking = {read=GetLocking, write=SetLocking, stored=false, nodefault};
	__property System::UnicodeString ADSAdvanced = {read=GetADSAdvanced, write=SetADSAdvanced, stored=false};
	__property System::UnicodeString MetaDefCatalog = {read=GetMetaDefCatalog, write=SetMetaDefCatalog, stored=false};
	__property System::UnicodeString MetaCurCatalog = {read=GetMetaCurCatalog, write=SetMetaCurCatalog, stored=false};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysADSConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysADSConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Adsdef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ADSDEF)
using namespace Firedac::Phys::Adsdef;
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
#endif	// Firedac_Phys_AdsdefHPP
