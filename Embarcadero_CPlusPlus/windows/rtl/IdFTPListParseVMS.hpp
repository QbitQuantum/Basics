// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseVMS.pas' rev: 34.00 (Windows)

#ifndef IdftplistparsevmsHPP
#define IdftplistparsevmsHPP

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
#pragma link "IdFTPListParseVMS"

namespace Idftplistparsevms
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdVMSFTPListItem;
class DELPHICLASS TIdFTPLPVMS;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdVMSFTPListItem : public Idftplisttypes::TIdOwnerFTPListItem
{
	typedef Idftplisttypes::TIdOwnerFTPListItem inherited;
	
protected:
	System::UnicodeString FGroupName;
	System::UnicodeString FVMSOwnerPermissions;
	System::UnicodeString FVMSWorldPermissions;
	System::UnicodeString FVMSSystemPermissions;
	System::UnicodeString FVMSGroupPermissions;
	int FNumberBlocks;
	int FBlockSize;
	int FVersion;
	
public:
	__property System::UnicodeString GroupName = {read=FGroupName, write=FGroupName};
	__property System::UnicodeString VMSSystemPermissions = {read=FVMSSystemPermissions, write=FVMSSystemPermissions};
	__property System::UnicodeString VMSOwnerPermissions = {read=FVMSOwnerPermissions, write=FVMSOwnerPermissions};
	__property System::UnicodeString VMSGroupPermissions = {read=FVMSGroupPermissions, write=FVMSGroupPermissions};
	__property System::UnicodeString VMSWorldPermissions = {read=FVMSWorldPermissions, write=FVMSWorldPermissions};
	__property int Version = {read=FVersion, write=FVersion, nodefault};
	__property int NumberBlocks = {read=FNumberBlocks, write=FNumberBlocks, nodefault};
	__property int BlockSize = {read=FBlockSize, write=FBlockSize, nodefault};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdVMSFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdOwnerFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdVMSFTPListItem() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPVMS : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod bool __fastcall IsVMSHeader(const System::UnicodeString AData);
	__classmethod bool __fastcall IsVMSFooter(const System::UnicodeString AData);
	__classmethod bool __fastcall IsContinuedLine(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
	__classmethod virtual bool __fastcall ParseListing(System::Classes::TStrings* AListing, Idftplist::TIdFTPListItems* ADir);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPVMS() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPVMS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsevms */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEVMS)
using namespace Idftplistparsevms;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsevmsHPP
