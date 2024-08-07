﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseEPLF.pas' rev: 34.00 (Android)

#ifndef IdftplistparseeplfHPP
#define IdftplistparseeplfHPP

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
namespace Idftplistparseeplf
{
  _INIT_UNIT(Idftplistparseeplf);
}	/* namespace Idftplistparseeplf */

namespace Idftplistparseeplf
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdAEPLFFTPListItem;
class DELPHICLASS TIdFTPLPEPLF;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdAEPLFFTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
protected:
	System::UnicodeString FUniqueID;
	System::UnicodeString FEPLFPermissions;
	
public:
	__property ModifiedDateGMT = {default=0};
	__property System::UnicodeString UniqueID = {read=FUniqueID, write=FUniqueID};
	__property System::UnicodeString EPLFPermissions = {read=FEPLFPermissions, write=FEPLFPermissions};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdAEPLFFTPListItem(System::Classes::TCollection* AOwner) : Idftplist::TIdFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdAEPLFFTPListItem() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdFTPLPEPLF : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPEPLF() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPEPLF() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparseeplf */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEEPLF)
using namespace Idftplistparseeplf;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparseeplfHPP
