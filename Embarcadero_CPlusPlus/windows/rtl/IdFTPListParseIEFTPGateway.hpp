// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseIEFTPGateway.pas' rev: 34.00 (Windows)

#ifndef IdftplistparseieftpgatewayHPP
#define IdftplistparseieftpgatewayHPP

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
#pragma link "IdFTPListParseIEFTPGateway"

namespace Idftplistparseieftpgateway
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdIEFTPGatewayLsLongListItem;
class DELPHICLASS TIdIEFTPGatewayLsShortListItem;
class DELPHICLASS TIdIEFTPGatewayLsFileNameListItem;
class DELPHICLASS TIdIEFTPGatewayLSLibraryListItem;
class DELPHICLASS TIdFTPLPIEFTPGatewayLSLong;
class DELPHICLASS TIdFTPLPIEFTPGatewayLSShort;
class DELPHICLASS TIdFTPLPIEFTPGatewayLSFileName;
class DELPHICLASS TIdFTPLPIEFTPGatewayLSLibrary;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdIEFTPGatewayLsLongListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
protected:
	System::UnicodeString FSenderAcct;
	System::UnicodeString FSenderUserID;
	System::UnicodeString FMClass;
	
public:
	__property System::UnicodeString SenderAcct = {read=FSenderAcct, write=FSenderAcct};
	__property System::UnicodeString SenderUserID = {read=FSenderUserID, write=FSenderUserID};
	__property System::UnicodeString MClass = {read=FMClass, write=FMClass};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdIEFTPGatewayLsLongListItem(System::Classes::TCollection* AOwner) : Idftplist::TIdFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdIEFTPGatewayLsLongListItem() { }
	
};


class PASCALIMPLEMENTATION TIdIEFTPGatewayLsShortListItem : public Idftplisttypes::TIdMinimalFTPListItem
{
	typedef Idftplisttypes::TIdMinimalFTPListItem inherited;
	
public:
	/* TIdMinimalFTPListItem.Create */ inline __fastcall virtual TIdIEFTPGatewayLsShortListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdMinimalFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdIEFTPGatewayLsShortListItem() { }
	
};


class PASCALIMPLEMENTATION TIdIEFTPGatewayLsFileNameListItem : public Idftplisttypes::TIdMinimalFTPListItem
{
	typedef Idftplisttypes::TIdMinimalFTPListItem inherited;
	
protected:
	System::UnicodeString FOrigFileName;
	
public:
	__property System::UnicodeString OrigFileName = {read=FOrigFileName, write=FOrigFileName};
public:
	/* TIdMinimalFTPListItem.Create */ inline __fastcall virtual TIdIEFTPGatewayLsFileNameListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdMinimalFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdIEFTPGatewayLsFileNameListItem() { }
	
};


class PASCALIMPLEMENTATION TIdIEFTPGatewayLSLibraryListItem : public Idftplisttypes::TIdUnixPermFTPListItem
{
	typedef Idftplisttypes::TIdUnixPermFTPListItem inherited;
	
protected:
	System::UnicodeString FAccount;
	
public:
	__property System::UnicodeString Account = {read=FAccount, write=FAccount};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdIEFTPGatewayLSLibraryListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdUnixPermFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdIEFTPGatewayLSLibraryListItem() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPIEFTPGatewayLSLong : public Idftplistparsebase::TIdFTPListBaseHeader
{
	typedef Idftplistparsebase::TIdFTPListBaseHeader inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall IsHeader(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPIEFTPGatewayLSLong() : Idftplistparsebase::TIdFTPListBaseHeader() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPIEFTPGatewayLSLong() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPIEFTPGatewayLSShort : public Idftplistparsebase::TIdFTPLPNList
{
	typedef Idftplistparsebase::TIdFTPLPNList inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPIEFTPGatewayLSShort() : Idftplistparsebase::TIdFTPLPNList() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPIEFTPGatewayLSShort() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPIEFTPGatewayLSFileName : public Idftplistparsebase::TIdFTPListBase
{
	typedef Idftplistparsebase::TIdFTPListBase inherited;
	
protected:
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPIEFTPGatewayLSFileName() : Idftplistparsebase::TIdFTPListBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPIEFTPGatewayLSFileName() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPIEFTPGatewayLSLibrary : public Idftplistparsebase::TIdFTPListBaseHeader
{
	typedef Idftplistparsebase::TIdFTPListBaseHeader inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall IsHeader(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPIEFTPGatewayLSLibrary() : Idftplistparsebase::TIdFTPListBaseHeader() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPIEFTPGatewayLSLibrary() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparseieftpgateway */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEIEFTPGATEWAY)
using namespace Idftplistparseieftpgateway;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparseieftpgatewayHPP
