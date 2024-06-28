// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.InfxDef.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_InfxdefHPP
#define Firedac_Phys_InfxdefHPP

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
namespace Infxdef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysInfxConnectionDefParams;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDInfxStringFormat : unsigned int { sfUnicode, sfANSI };

enum DECLSPEC_DENUM TFDInfxTxSupported : unsigned int { tsYes, tsNo, tsChoose };

class PASCALIMPLEMENTATION TFDPhysInfxConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
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
	System::UnicodeString __fastcall GetCharacterSet();
	void __fastcall SetCharacterSet(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetDBCharacterSet();
	void __fastcall SetDBCharacterSet(const System::UnicodeString AValue);
	TFDInfxStringFormat __fastcall GetStringFormat();
	void __fastcall SetStringFormat(const TFDInfxStringFormat AValue);
	int __fastcall GetReadTimeout();
	void __fastcall SetReadTimeout(const int AValue);
	int __fastcall GetWriteTimeout();
	void __fastcall SetWriteTimeout(const int AValue);
	TFDInfxTxSupported __fastcall GetTxSupported();
	void __fastcall SetTxSupported(const TFDInfxTxSupported AValue);
	bool __fastcall GetTxRetainLocks();
	void __fastcall SetTxRetainLocks(const bool AValue);
	bool __fastcall GetTxLastCommitted();
	void __fastcall SetTxLastCommitted(const bool AValue);
	System::UnicodeString __fastcall GetMetaDefCatalog();
	void __fastcall SetMetaDefCatalog(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaDefSchema();
	void __fastcall SetMetaDefSchema(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurCatalog();
	void __fastcall SetMetaCurCatalog(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetMetaCurSchema();
	void __fastcall SetMetaCurSchema(const System::UnicodeString AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property System::UnicodeString ODBCAdvanced = {read=GetODBCAdvanced, write=SetODBCAdvanced, stored=false};
	__property int LoginTimeout = {read=GetLoginTimeout, write=SetLoginTimeout, stored=false, nodefault};
	__property System::UnicodeString Server = {read=GetServer, write=SetServer, stored=false};
	__property System::UnicodeString CharacterSet = {read=GetCharacterSet, write=SetCharacterSet, stored=false};
	__property System::UnicodeString DBCharacterSet = {read=GetDBCharacterSet, write=SetDBCharacterSet, stored=false};
	__property TFDInfxStringFormat StringFormat = {read=GetStringFormat, write=SetStringFormat, stored=false, default=1};
	__property int ReadTimeout = {read=GetReadTimeout, write=SetReadTimeout, stored=false, nodefault};
	__property int WriteTimeout = {read=GetWriteTimeout, write=SetWriteTimeout, stored=false, nodefault};
	__property TFDInfxTxSupported TxSupported = {read=GetTxSupported, write=SetTxSupported, stored=false, default=0};
	__property bool TxRetainLocks = {read=GetTxRetainLocks, write=SetTxRetainLocks, stored=false, default=1};
	__property bool TxLastCommitted = {read=GetTxLastCommitted, write=SetTxLastCommitted, stored=false, default=1};
	__property System::UnicodeString MetaDefCatalog = {read=GetMetaDefCatalog, write=SetMetaDefCatalog, stored=false};
	__property System::UnicodeString MetaDefSchema = {read=GetMetaDefSchema, write=SetMetaDefSchema, stored=false};
	__property System::UnicodeString MetaCurCatalog = {read=GetMetaCurCatalog, write=SetMetaCurCatalog, stored=false};
	__property System::UnicodeString MetaCurSchema = {read=GetMetaCurSchema, write=SetMetaCurSchema, stored=false};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysInfxConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysInfxConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Infxdef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_INFXDEF)
using namespace Firedac::Phys::Infxdef;
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
#endif	// Firedac_Phys_InfxdefHPP
