// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MSAccDef.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_MsaccdefHPP
#define Firedac_Phys_MsaccdefHPP

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
namespace Msaccdef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysMSAccConnectionDefParams;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDMSAccStringFormat : unsigned int { sfChoose, sfUnicode, sfANSI };

class PASCALIMPLEMENTATION TFDPhysMSAccConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
{
	typedef Firedac::Stan::Intf::TFDConnectionDefParams inherited;
	
private:
	HIDESBASE System::UnicodeString __fastcall GetDriverID();
	HIDESBASE void __fastcall SetDriverID(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetODBCAdvanced();
	void __fastcall SetODBCAdvanced(const System::UnicodeString AValue);
	int __fastcall GetLoginTimeout();
	void __fastcall SetLoginTimeout(const int AValue);
	System::UnicodeString __fastcall GetSystemDB();
	void __fastcall SetSystemDB(const System::UnicodeString AValue);
	bool __fastcall GetReadOnly();
	void __fastcall SetReadOnly(const bool AValue);
	TFDMSAccStringFormat __fastcall GetStringFormat();
	void __fastcall SetStringFormat(const TFDMSAccStringFormat AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property System::UnicodeString ODBCAdvanced = {read=GetODBCAdvanced, write=SetODBCAdvanced, stored=false};
	__property int LoginTimeout = {read=GetLoginTimeout, write=SetLoginTimeout, stored=false, nodefault};
	__property System::UnicodeString SystemDB = {read=GetSystemDB, write=SetSystemDB, stored=false};
	__property bool ReadOnly = {read=GetReadOnly, write=SetReadOnly, stored=false, nodefault};
	__property TFDMSAccStringFormat StringFormat = {read=GetStringFormat, write=SetStringFormat, stored=false, default=0};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysMSAccConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysMSAccConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Msaccdef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MSACCDEF)
using namespace Firedac::Phys::Msaccdef;
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
#endif	// Firedac_Phys_MsaccdefHPP
