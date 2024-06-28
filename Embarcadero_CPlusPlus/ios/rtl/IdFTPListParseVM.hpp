// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseVM.pas' rev: 34.00 (iOS)

#ifndef IdftplistparsevmHPP
#define IdftplistparsevmHPP

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
namespace Idftplistparsevm
{
  _INIT_UNIT(Idftplistparsevm);
}	/* namespace Idftplistparsevm */

namespace Idftplistparsevm
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdVMCMSFTPListItem;
class DELPHICLASS TIdVMVirtualReaderFTPListItem;
class DELPHICLASS TIdVMBFSFTPListItem;
class DELPHICLASS TIdFTPLPVMCMS;
class DELPHICLASS TIdFTPLPVMBFS;
class DELPHICLASS TIdFTPLVirtualReader;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdVMCMSFTPListItem : public Idftplisttypes::TIdRecFTPListItem
{
	typedef Idftplisttypes::TIdRecFTPListItem inherited;
	
protected:
	System::UnicodeString FOwnerName;
	int FNumberBlocks;
	
public:
	__property int RecLength = {read=FRecLength, write=FRecLength, nodefault};
	__property System::UnicodeString RecFormat = {read=FRecFormat, write=FRecFormat};
	__property int NumberRecs = {read=FNumberRecs, write=FNumberRecs, nodefault};
	__property System::UnicodeString OwnerName = {read=FOwnerName, write=FOwnerName};
	__property int NumberBlocks = {read=FNumberBlocks, write=FNumberBlocks, nodefault};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdVMCMSFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdRecFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdVMCMSFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdVMVirtualReaderFTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
protected:
	int FNumberRecs;
	
public:
	__fastcall virtual TIdVMVirtualReaderFTPListItem(System::Classes::TCollection* AOwner);
	__property int NumberRecs = {read=FNumberRecs, write=FNumberRecs, nodefault};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdVMVirtualReaderFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdVMBFSFTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdVMBFSFTPListItem(System::Classes::TCollection* AOwner) : Idftplist::TIdFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdVMBFSFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPVMCMS : public Idftplistparsebase::TIdFTPListBaseHeaderOpt
{
	typedef Idftplistparsebase::TIdFTPListBaseHeaderOpt inherited;
	
protected:
	__classmethod virtual bool __fastcall IsHeader(const System::UnicodeString AData);
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	__classmethod virtual bool __fastcall CheckListingAlt(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPVMCMS() : Idftplistparsebase::TIdFTPListBaseHeaderOpt() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPVMCMS() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPVMBFS : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPVMBFS() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPVMBFS() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLVirtualReader : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLVirtualReader() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLVirtualReader() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsevm */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEVM)
using namespace Idftplistparsevm;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsevmHPP
