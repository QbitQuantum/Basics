// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseNovellNetwarePSU.pas' rev: 34.00 (iOS)

#ifndef IdftplistparsenovellnetwarepsuHPP
#define IdftplistparsenovellnetwarepsuHPP

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
namespace Idftplistparsenovellnetwarepsu
{
  _INIT_UNIT(Idftplistparsenovellnetwarepsu);
}	/* namespace Idftplistparsenovellnetwarepsu */

namespace Idftplistparsenovellnetwarepsu
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdNovellPSU_DOSFTPListItem;
class DELPHICLASS TIdFTPLPNetwarePSUDos;
class DELPHICLASS TIdNovellPSU_NFSFTPListItem;
class DELPHICLASS TIdFTPLPNetwarePSUNFS;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdNovellPSU_DOSFTPListItem : public Idftplisttypes::TIdNovellBaseFTPListItem
{
	typedef Idftplisttypes::TIdNovellBaseFTPListItem inherited;
	
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdNovellPSU_DOSFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdNovellBaseFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdNovellPSU_DOSFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPNetwarePSUDos : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPNetwarePSUDos() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPNetwarePSUDos() { }
	
};


class PASCALIMPLEMENTATION TIdNovellPSU_NFSFTPListItem : public Idftplisttypes::TIdUnixBaseFTPListItem
{
	typedef Idftplisttypes::TIdUnixBaseFTPListItem inherited;
	
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdNovellPSU_NFSFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdUnixBaseFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdNovellPSU_NFSFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPNetwarePSUNFS : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPNetwarePSUNFS() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPNetwarePSUNFS() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define NOVELLNETWAREPSU u"Novell Netware Print Services for Unix:  "
}	/* namespace Idftplistparsenovellnetwarepsu */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSENOVELLNETWAREPSU)
using namespace Idftplistparsenovellnetwarepsu;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsenovellnetwarepsuHPP
