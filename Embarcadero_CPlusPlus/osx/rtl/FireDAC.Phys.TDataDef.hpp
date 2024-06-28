// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.TDataDef.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_TdatadefHPP
#define Firedac_Phys_TdatadefHPP

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
#include <FireDAC.Phys.TDataMeta.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Tdatadef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysTDataConnectionDefParams;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDTDataCharacterSet : unsigned int { csASCII, csUTF8, csUTF16, csLATIN1252_0A, csLATIN9_0A, csLATIN1_0A, csKANJISJIS_0S, csKANJIEUC_0U, csTCHBIG5_1R0, csSCHGB2312_1T0, csHANGULKSC5601_2R4 };

class PASCALIMPLEMENTATION TFDPhysTDataConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
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
	bool __fastcall GetOSAuthent();
	void __fastcall SetOSAuthent(const bool AValue);
	TFDTDataCharacterSet __fastcall GetCharacterSet();
	void __fastcall SetCharacterSet(const TFDTDataCharacterSet AValue);
	Firedac::Phys::Tdatameta::TFDTDataSessionMode __fastcall GetSessionMode();
	void __fastcall SetSessionMode(const Firedac::Phys::Tdatameta::TFDTDataSessionMode AValue);
	bool __fastcall GetEncrypt();
	void __fastcall SetEncrypt(const bool AValue);
	bool __fastcall GetExtendedMetadata();
	void __fastcall SetExtendedMetadata(const bool AValue);
	System::UnicodeString __fastcall GetMetaDefSchema();
	void __fastcall SetMetaDefSchema(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurSchema();
	void __fastcall SetMetaCurSchema(const System::UnicodeString AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property System::UnicodeString ODBCAdvanced = {read=GetODBCAdvanced, write=SetODBCAdvanced, stored=false};
	__property int LoginTimeout = {read=GetLoginTimeout, write=SetLoginTimeout, stored=false, nodefault};
	__property System::UnicodeString Server = {read=GetServer, write=SetServer, stored=false};
	__property bool OSAuthent = {read=GetOSAuthent, write=SetOSAuthent, stored=false, nodefault};
	__property TFDTDataCharacterSet CharacterSet = {read=GetCharacterSet, write=SetCharacterSet, stored=false, default=0};
	__property Firedac::Phys::Tdatameta::TFDTDataSessionMode SessionMode = {read=GetSessionMode, write=SetSessionMode, stored=false, default=0};
	__property bool Encrypt = {read=GetEncrypt, write=SetEncrypt, stored=false, nodefault};
	__property bool ExtendedMetadata = {read=GetExtendedMetadata, write=SetExtendedMetadata, stored=false, nodefault};
	__property System::UnicodeString MetaDefSchema = {read=GetMetaDefSchema, write=SetMetaDefSchema, stored=false};
	__property System::UnicodeString MetaCurSchema = {read=GetMetaCurSchema, write=SetMetaCurSchema, stored=false};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysTDataConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysTDataConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Tdatadef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_TDATADEF)
using namespace Firedac::Phys::Tdatadef;
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
#endif	// Firedac_Phys_TdatadefHPP
