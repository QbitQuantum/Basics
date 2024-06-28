// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseTSXPlus.pas' rev: 34.00 (Windows)

#ifndef IdftplistparsetsxplusHPP
#define IdftplistparsetsxplusHPP

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
#pragma link "IdFTPListParseTSXPlus"

namespace Idftplistparsetsxplus
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdTSXPlusFTPListItem;
class DELPHICLASS TIdFTPLPTSXPlus;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdTSXPlusFTPListItem : public Idftplisttypes::TIdMinimalFTPListItem
{
	typedef Idftplisttypes::TIdMinimalFTPListItem inherited;
	
protected:
	int FNumberBlocks;
	
public:
	__property int NumberBlocks = {read=FNumberBlocks, write=FNumberBlocks, nodefault};
public:
	/* TIdMinimalFTPListItem.Create */ inline __fastcall virtual TIdTSXPlusFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdMinimalFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdTSXPlusFTPListItem() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPTSXPlus : public Idftplistparsebase::TIdFTPListBaseHeader
{
	typedef Idftplistparsebase::TIdFTPListBaseHeader inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall IsHeader(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall IsFooter(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPTSXPlus() : Idftplistparsebase::TIdFTPListBaseHeader() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPTSXPlus() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsetsxplus */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSETSXPLUS)
using namespace Idftplistparsetsxplus;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsetsxplusHPP
