// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseNovellNetware.pas' rev: 34.00 (iOS)

#ifndef IdftplistparsenovellnetwareHPP
#define IdftplistparsenovellnetwareHPP

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
namespace Idftplistparsenovellnetware
{
  _INIT_UNIT(Idftplistparsenovellnetware);
}	/* namespace Idftplistparsenovellnetware */

namespace Idftplistparsenovellnetware
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdNovellNetwareFTPListItem;
class DELPHICLASS TIdFTPLPNovellNetware;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdNovellNetwareFTPListItem : public Idftplisttypes::TIdNovellBaseFTPListItem
{
	typedef Idftplisttypes::TIdNovellBaseFTPListItem inherited;
	
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdNovellNetwareFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdNovellBaseFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdNovellNetwareFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPNovellNetware : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
	__classmethod virtual bool __fastcall ParseListing(System::Classes::TStrings* AListing, Idftplist::TIdFTPListItems* ADir);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPNovellNetware() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPNovellNetware() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsenovellnetware */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSENOVELLNETWARE)
using namespace Idftplistparsenovellnetware;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsenovellnetwareHPP
