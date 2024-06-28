// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseUnix.pas' rev: 34.00 (iOS)

#ifndef IdftplistparseunixHPP
#define IdftplistparseunixHPP

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
namespace Idftplistparseunix
{
  _INIT_UNIT(Idftplistparseunix);
}	/* namespace Idftplistparseunix */

namespace Idftplistparseunix
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdUnixFTPListItem;
class DELPHICLASS TIdUnitreeFTPListItem;
class DELPHICLASS TIdFTPLPUnix;
class DELPHICLASS TIdFTPLPUnitree;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdUnixFTPListItem : public Idftplisttypes::TIdUnixBaseFTPListItem
{
	typedef Idftplisttypes::TIdUnixBaseFTPListItem inherited;
	
protected:
	int FNumberBlocks;
	int FInode;
	
public:
	__property int NumberBlocks = {read=FNumberBlocks, write=FNumberBlocks, nodefault};
	__property int Inode = {read=FInode, write=FInode, nodefault};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdUnixFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdUnixBaseFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdUnixFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdUnitreeFTPListItem : public TIdUnixFTPListItem
{
	typedef TIdUnixFTPListItem inherited;
	
protected:
	bool FMigrated;
	System::UnicodeString FFileFamily;
	
public:
	__property bool Migrated = {read=FMigrated, write=FMigrated, nodefault};
	__property System::UnicodeString FileFamily = {read=FFileFamily, write=FFileFamily};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdUnitreeFTPListItem(System::Classes::TCollection* AOwner) : TIdUnixFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdUnitreeFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPUnix : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall InternelChkUnix(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall IsUnitree(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall IsUnitreeBanner(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
	__classmethod virtual bool __fastcall ParseListing(System::Classes::TStrings* AListing, Idftplist::TIdFTPListItems* ADir);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPUnix() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPUnix() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPUnitree : public TIdFTPLPUnix
{
	typedef TIdFTPLPUnix inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPUnitree() : TIdFTPLPUnix() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPUnitree() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define UNIX u"Unix"
#define UNITREE u"Unitree"
}	/* namespace Idftplistparseunix */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEUNIX)
using namespace Idftplistparseunix;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparseunixHPP
