﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseBullGCOS8.pas' rev: 34.00 (Windows)

#ifndef Idftplistparsebullgcos8HPP
#define Idftplistparsebullgcos8HPP

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
#pragma link "IdFTPListParseBullGCOS8"

namespace Idftplistparsebullgcos8
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdFTPLPGOS8ListItem;
class DELPHICLASS TIdFTPLPGOS8;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdFTPLPGOS8ListItem : public Idftplisttypes::TIdUnixPermFTPListItem
{
	typedef Idftplisttypes::TIdUnixPermFTPListItem inherited;
	
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdFTPLPGOS8ListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdUnixPermFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdFTPLPGOS8ListItem() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPGOS8 : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPGOS8() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPGOS8() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsebullgcos8 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEBULLGCOS8)
using namespace Idftplistparsebullgcos8;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idftplistparsebullgcos8HPP
