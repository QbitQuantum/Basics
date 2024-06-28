// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseMicrowareOS9.pas' rev: 34.00 (Android)

#ifndef Idftplistparsemicrowareos9HPP
#define Idftplistparsemicrowareos9HPP

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
namespace Idftplistparsemicrowareos9
{
  _INIT_UNIT(Idftplistparsemicrowareos9);
}	/* namespace Idftplistparsemicrowareos9 */

namespace Idftplistparsemicrowareos9
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdMicrowareOS9FTPListItem;
class DELPHICLASS TIdFTPLPMicrowareOS9;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdMicrowareOS9FTPListItem : public Idftplisttypes::TIdOwnerFTPListItem
{
	typedef Idftplisttypes::TIdOwnerFTPListItem inherited;
	
protected:
	System::UnicodeString FOS9OwnerPermissions;
	System::UnicodeString FOS9PublicPermissions;
	System::UnicodeString FOS9MiscPermissions;
	unsigned FOS9Sector;
	
public:
	__property System::UnicodeString OS9OwnerPermissions = {read=FOS9OwnerPermissions, write=FOS9OwnerPermissions};
	__property System::UnicodeString OS9PublicPermissions = {read=FOS9PublicPermissions, write=FOS9PublicPermissions};
	__property System::UnicodeString OS9MiscPermissions = {read=FOS9MiscPermissions, write=FOS9MiscPermissions};
	__property unsigned OS9Sector = {read=FOS9Sector, write=FOS9Sector, nodefault};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdMicrowareOS9FTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdOwnerFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdMicrowareOS9FTPListItem() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdFTPLPMicrowareOS9 : public Idftplistparsebase::TIdFTPListBaseHeader
{
	typedef Idftplistparsebase::TIdFTPListBaseHeader inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall IsHeader(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPMicrowareOS9() : Idftplistparsebase::TIdFTPListBaseHeader() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPMicrowareOS9() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsemicrowareos9 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEMICROWAREOS9)
using namespace Idftplistparsemicrowareos9;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idftplistparsemicrowareos9HPP
