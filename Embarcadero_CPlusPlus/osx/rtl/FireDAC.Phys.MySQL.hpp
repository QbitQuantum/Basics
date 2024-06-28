// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MySQL.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_MysqlHPP
#define Firedac_Phys_MysqlHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Phys.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.Phys.MySQL"

namespace Firedac
{
namespace Phys
{
namespace Mysql
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysMySQLDriverLink;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysMySQLDriverLink : public Firedac::Phys::TFDPhysDriverLink
{
	typedef Firedac::Phys::TFDPhysDriverLink inherited;
	
private:
	System::Classes::TStrings* FEmbeddedArgs;
	System::Classes::TStrings* FEmbeddedGroups;
	void __fastcall SetEmbeddedArgs(System::Classes::TStrings* const AValue);
	void __fastcall SetEmbeddedGroups(System::Classes::TStrings* const AValue);
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
	virtual bool __fastcall IsConfigured();
	virtual void __fastcall ApplyTo(const Firedac::Stan::Intf::_di_IFDStanDefinition AParams);
	
public:
	__fastcall virtual TFDPhysMySQLDriverLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDPhysMySQLDriverLink();
	
__published:
	__property System::Classes::TStrings* EmbeddedArgs = {read=FEmbeddedArgs, write=SetEmbeddedArgs};
	__property System::Classes::TStrings* EmbeddedGroups = {read=FEmbeddedGroups, write=SetEmbeddedGroups};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mysql */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MYSQL)
using namespace Firedac::Phys::Mysql;
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
#endif	// Firedac_Phys_MysqlHPP
