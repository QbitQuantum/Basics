// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseChameleonNewt.pas' rev: 34.00 (Windows)

#ifndef IdftplistparsechameleonnewtHPP
#define IdftplistparsechameleonnewtHPP

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
#pragma link "IdFTPListParseChameleonNewt"

namespace Idftplistparsechameleonnewt
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdChameleonNewtFTPListItem;
class DELPHICLASS TIdFTPLPChameleonNewt;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdChameleonNewtFTPListItem : public Idftplisttypes::TIdDOSBaseFTPListItem
{
	typedef Idftplisttypes::TIdDOSBaseFTPListItem inherited;
	
public:
	/* TIdDOSBaseFTPListItem.Create */ inline __fastcall virtual TIdChameleonNewtFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdDOSBaseFTPListItem(AOwner) { }
	/* TIdDOSBaseFTPListItem.Destroy */ inline __fastcall virtual ~TIdChameleonNewtFTPListItem() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPChameleonNewt : public Idftplistparsebase::TIdFTPLPBaseDOS
{
	typedef Idftplistparsebase::TIdFTPLPBaseDOS inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPChameleonNewt() : Idftplistparsebase::TIdFTPLPBaseDOS() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPChameleonNewt() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsechameleonnewt */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSECHAMELEONNEWT)
using namespace Idftplistparsechameleonnewt;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsechameleonnewtHPP
