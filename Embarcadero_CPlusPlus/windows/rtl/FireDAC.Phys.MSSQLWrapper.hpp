// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MSSQLWrapper.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_MssqlwrapperHPP
#define Firedac_Phys_MssqlwrapperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Phys.MSSQLCli.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Mssqlwrapper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMSSQLToolLib;
class DELPHICLASS TMSSQLFileStream;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TMSSQLToolLib : public Firedac::Stan::Util::TFDLibrary
{
	typedef Firedac::Stan::Util::TFDLibrary inherited;
	
protected:
	virtual void __fastcall LoadEntries();
	
public:
	Firedac::Phys::Mssqlcli::TMSSQLOpenSqlFilestream OpenSqlFilestream;
	__fastcall TMSSQLToolLib(System::TObject* AOwningObj);
	HIDESBASE void __fastcall Load(const System::UnicodeString AODBCDrvLib);
public:
	/* TFDLibrary.Destroy */ inline __fastcall virtual ~TMSSQLToolLib() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMSSQLFileStream : public System::Classes::THandleStream
{
	typedef System::Classes::THandleStream inherited;
	
private:
	System::TObject* FOwningObj;
	
public:
	__fastcall TMSSQLFileStream(TMSSQLToolLib* ALib, const System::UnicodeString ABlobPath, const System::RawByteString AToken, Firedac::Stan::Intf::TFDStreamMode AMode, unsigned AOptions, System::TObject* AOwningObj)/* overload */;
	__fastcall virtual ~TMSSQLFileStream();
	__property System::TObject* OwningObj = {read=FOwningObj};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mssqlwrapper */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MSSQLWRAPPER)
using namespace Firedac::Phys::Mssqlwrapper;
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
#endif	// Firedac_Phys_MssqlwrapperHPP
