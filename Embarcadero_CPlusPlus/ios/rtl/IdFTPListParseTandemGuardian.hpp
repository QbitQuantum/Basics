// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseTandemGuardian.pas' rev: 34.00 (iOS)

#ifndef IdftplistparsetandemguardianHPP
#define IdftplistparsetandemguardianHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdFTPList.hpp>
#include <IdFTPListParseBase.hpp>
#include <IdFTPListTypes.hpp>

//-- user supplied -----------------------------------------------------------
namespace Idftplistparsetandemguardian
{
  _INIT_UNIT(Idftplistparsetandemguardian);
}	/* namespace Idftplistparsetandemguardian */

namespace Idftplistparsetandemguardian
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdTandemGuardianFTPListItem;
class DELPHICLASS TIdFTPLPTandemGuardian;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdTandemGuardianFTPListItem : public Idftplisttypes::TIdOwnerFTPListItem
{
	typedef Idftplisttypes::TIdOwnerFTPListItem inherited;
	
protected:
	System::UnicodeString FGroupName;
	unsigned FCode;
	System::UnicodeString FPermissions;
	
public:
	__property System::UnicodeString GroupName = {read=FGroupName, write=FGroupName};
	__property unsigned Code = {read=FCode, write=FCode, nodefault};
	__property System::UnicodeString Permissions = {read=FPermissions, write=FPermissions};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdTandemGuardianFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdOwnerFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdTandemGuardianFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPTandemGuardian : public Idftplistparsebase::TIdFTPListBaseHeader
{
	typedef Idftplistparsebase::TIdFTPListBaseHeader inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall IsHeader(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPTandemGuardian() : Idftplistparsebase::TIdFTPListBaseHeader() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPTandemGuardian() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define TANDEM_GUARDIAN_ID u"Tandem NonStop Guardian"
}	/* namespace Idftplistparsetandemguardian */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSETANDEMGUARDIAN)
using namespace Idftplistparsetandemguardian;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsetandemguardianHPP
