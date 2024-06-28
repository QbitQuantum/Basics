﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseTOPS20.pas' rev: 34.00 (Android)

#ifndef Idftplistparsetops20HPP
#define Idftplistparsetops20HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdFTPList.hpp>
#include <IdFTPListParseBase.hpp>
#include <IdFTPListTypes.hpp>

//-- user supplied -----------------------------------------------------------
namespace Idftplistparsetops20
{
  _INIT_UNIT(Idftplistparsetops20);
}	/* namespace Idftplistparsetops20 */

namespace Idftplistparsetops20
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdTOPS20FTPListItem;
class DELPHICLASS TIdFTPLPTOPS20;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdTOPS20FTPListItem : public Idftplisttypes::TIdCreationDateFTPListItem
{
	typedef Idftplisttypes::TIdCreationDateFTPListItem inherited;
	
public:
	/* TIdCreationDateFTPListItem.Create */ inline __fastcall virtual TIdTOPS20FTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdCreationDateFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdTOPS20FTPListItem() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdFTPLPTOPS20 : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPTOPS20() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPTOPS20() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define TOPS20_VOLPATH_SEP u":<"
static constexpr System::WideChar TOPS20_DIRFILE_SEP = (System::WideChar)(0x3e);
}	/* namespace Idftplistparsetops20 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSETOPS20)
using namespace Idftplistparsetops20;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idftplistparsetops20HPP
