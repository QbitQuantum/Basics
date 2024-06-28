// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseAS400.pas' rev: 34.00 (Windows)

#ifndef Idftplistparseas400HPP
#define Idftplistparseas400HPP

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
#pragma link "IdFTPListParseAS400"

namespace Idftplistparseas400
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdAS400FTPListItem;
class DELPHICLASS TIdFTPLPAS400;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdAS400FTPListItem : public Idftplisttypes::TIdOwnerFTPListItem
{
	typedef Idftplisttypes::TIdOwnerFTPListItem inherited;
	
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdAS400FTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdOwnerFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdAS400FTPListItem() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPAS400 : public Idftplistparsebase::TIdFTPLineOwnedList
{
	typedef Idftplistparsebase::TIdFTPLineOwnedList inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPAS400() : Idftplistparsebase::TIdFTPLineOwnedList() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPAS400() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparseas400 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEAS400)
using namespace Idftplistparseas400;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idftplistparseas400HPP
