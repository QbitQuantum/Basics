// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseVSE.pas' rev: 34.00 (iOS)

#ifndef IdftplistparsevseHPP
#define IdftplistparsevseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdFTPCommon.hpp>
#include <IdFTPList.hpp>
#include <IdFTPListParseBase.hpp>
#include <IdFTPListTypes.hpp>

//-- user supplied -----------------------------------------------------------
namespace Idftplistparsevse
{
  _INIT_UNIT(Idftplistparsevse);
}	/* namespace Idftplistparsevse */

namespace Idftplistparsevse
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdVSERootDirFTPListItem;
class DELPHICLASS TIdVSELibraryFTPListItem;
class DELPHICLASS TIdVSEPowerQueueFTPListItem;
class DELPHICLASS TIdVSESubLibraryFTPListItem;
class DELPHICLASS TIdFTPLPVSESubLibrary;
class DELPHICLASS TIdVSEVSAMCatalogFTPListItem;
class DELPHICLASS TIdFTPLPVSERootDir;
class DELPHICLASS TIdFTPLPVSELibrary;
class DELPHICLASS TIdFTPLPVSEVSAMCatalog;
class DELPHICLASS TIdVSEVTOCFTPListItem;
class DELPHICLASS TIdFTPLPVSEVTOC;
class DELPHICLASS TIdFTPLPVSEPowerQueue;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdVSERootDirFTPListItem : public Idftplisttypes::TIdMinimalFTPListItem
{
	typedef Idftplisttypes::TIdMinimalFTPListItem inherited;
	
public:
	/* TIdMinimalFTPListItem.Create */ inline __fastcall virtual TIdVSERootDirFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdMinimalFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdVSERootDirFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdVSELibraryFTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
protected:
	int FNumberBlocks;
	
public:
	__property int NumberBlocks = {read=FNumberBlocks, write=FNumberBlocks, nodefault};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdVSELibraryFTPListItem(System::Classes::TCollection* AOwner) : Idftplist::TIdFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdVSELibraryFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdVSEPowerQueueFTPListItem : public Idftplisttypes::TIdOwnerFTPListItem
{
	typedef Idftplisttypes::TIdOwnerFTPListItem inherited;
	
protected:
	Idftpcommon::TIdVSEPQDisposition FVSEPQDisposition;
	int FVSEPQPriority;
	int FNumberRecs;
	
public:
	__property int NumberRecs = {read=FNumberRecs, write=FNumberRecs, nodefault};
	__property Idftpcommon::TIdVSEPQDisposition VSEPQDisposition = {read=FVSEPQDisposition, write=FVSEPQDisposition, nodefault};
	__property int VSEPQPriority = {read=FVSEPQPriority, write=FVSEPQPriority, nodefault};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdVSEPowerQueueFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdOwnerFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdVSEPowerQueueFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdVSESubLibraryFTPListItem : public TIdVSELibraryFTPListItem
{
	typedef TIdVSELibraryFTPListItem inherited;
	
protected:
	int FNumberRecs;
	System::TDateTime FCreationDate;
	
public:
	__property System::TDateTime CreationDate = {read=FCreationDate, write=FCreationDate};
	__property int NumberRecs = {read=FNumberRecs, write=FNumberRecs, nodefault};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdVSESubLibraryFTPListItem(System::Classes::TCollection* AOwner) : TIdVSELibraryFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdVSESubLibraryFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPVSESubLibrary : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPVSESubLibrary() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPVSESubLibrary() { }
	
};


class PASCALIMPLEMENTATION TIdVSEVSAMCatalogFTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdVSEVSAMCatalogFTPListItem(System::Classes::TCollection* AOwner) : Idftplist::TIdFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdVSEVSAMCatalogFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPVSERootDir : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPVSERootDir() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPVSERootDir() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPVSELibrary : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPVSELibrary() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPVSELibrary() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPVSEVSAMCatalog : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPVSEVSAMCatalog() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPVSEVSAMCatalog() { }
	
};


class PASCALIMPLEMENTATION TIdVSEVTOCFTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
public:
	__fastcall virtual TIdVSEVTOCFTPListItem(System::Classes::TCollection* AOwner);
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdVSEVTOCFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPVSEVTOC : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPVSEVTOC() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPVSEVTOC() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPVSEPowerQueue : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPVSEPowerQueue() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPVSEPowerQueue() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsevse */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEVSE)
using namespace Idftplistparsevse;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsevseHPP
