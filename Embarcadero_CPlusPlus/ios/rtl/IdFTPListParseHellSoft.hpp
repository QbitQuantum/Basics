// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseHellSoft.pas' rev: 34.00 (iOS)

#ifndef IdftplistparsehellsoftHPP
#define IdftplistparsehellsoftHPP

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
#include <IdFTPListParseNovellNetware.hpp>

//-- user supplied -----------------------------------------------------------
namespace Idftplistparsehellsoft
{
  _INIT_UNIT(Idftplistparsehellsoft);
}	/* namespace Idftplistparsehellsoft */

namespace Idftplistparsehellsoft
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHellSoftFTPListItem;
class DELPHICLASS TIdFTPLPHellSoft;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdHellSoftFTPListItem : public Idftplistparsenovellnetware::TIdNovellNetwareFTPListItem
{
	typedef Idftplistparsenovellnetware::TIdNovellNetwareFTPListItem inherited;
	
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdHellSoftFTPListItem(System::Classes::TCollection* AOwner) : Idftplistparsenovellnetware::TIdNovellNetwareFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdHellSoftFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPHellSoft : public Idftplistparsenovellnetware::TIdFTPLPNovellNetware
{
	typedef Idftplistparsenovellnetware::TIdFTPLPNovellNetware inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPHellSoft() : Idftplistparsenovellnetware::TIdFTPLPNovellNetware() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPHellSoft() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsehellsoft */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEHELLSOFT)
using namespace Idftplistparsehellsoft;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsehellsoftHPP
