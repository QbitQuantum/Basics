// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseDistinctTCPIP.pas' rev: 34.00 (iOS)

#ifndef IdftplistparsedistincttcpipHPP
#define IdftplistparsedistincttcpipHPP

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
namespace Idftplistparsedistincttcpip
{
  _INIT_UNIT(Idftplistparsedistincttcpip);
}	/* namespace Idftplistparsedistincttcpip */

namespace Idftplistparsedistincttcpip
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdDistinctTCPIPFTPListItem;
class DELPHICLASS TIdFTPLPDistinctTCPIP;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdDistinctTCPIPFTPListItem : public Idftplisttypes::TIdDOSBaseFTPListItem
{
	typedef Idftplisttypes::TIdDOSBaseFTPListItem inherited;
	
protected:
	System::UnicodeString FDist32FileAttributes;
	
public:
	__property ModifiedDateGMT = {default=0};
	__property System::UnicodeString Dist32FileAttributes = {read=FDist32FileAttributes, write=FDist32FileAttributes};
public:
	/* TIdDOSBaseFTPListItem.Create */ inline __fastcall virtual TIdDistinctTCPIPFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdDOSBaseFTPListItem(AOwner) { }
	/* TIdDOSBaseFTPListItem.Destroy */ inline __fastcall virtual ~TIdDistinctTCPIPFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPDistinctTCPIP : public Idftplistparsebase::TIdFTPLPBaseDOS
{
	typedef Idftplistparsebase::TIdFTPLPBaseDOS inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPDistinctTCPIP() : Idftplistparsebase::TIdFTPLPBaseDOS() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPDistinctTCPIP() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsedistincttcpip */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEDISTINCTTCPIP)
using namespace Idftplistparsedistincttcpip;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsedistincttcpipHPP
