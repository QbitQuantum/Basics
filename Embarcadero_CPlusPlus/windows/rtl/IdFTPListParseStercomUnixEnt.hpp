﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseStercomUnixEnt.pas' rev: 34.00 (Windows)

#ifndef IdftplistparsestercomunixentHPP
#define IdftplistparsestercomunixentHPP

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
#pragma link "IdFTPListParseStercomUnixEnt"

namespace Idftplistparsestercomunixent
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSterCommEntUxFTPListItem;
class DELPHICLASS TIdFTPLPSterComEntBase;
class DELPHICLASS TIdFTPLPSterCommEntUx;
class DELPHICLASS TIdSterCommEntUxNSFTPListItem;
class DELPHICLASS TIdFTPLPSterCommEntUxNS;
class DELPHICLASS TIdSterCommEntUxRootFTPListItem;
class DELPHICLASS TIdFTPLPSterCommEntUxRoot;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSterCommEntUxFTPListItem : public Idftplisttypes::TIdOwnerFTPListItem
{
	typedef Idftplisttypes::TIdOwnerFTPListItem inherited;
	
protected:
	System::UnicodeString FFlagsProt;
	System::UnicodeString FProtIndicator;
	
public:
	__property System::UnicodeString FlagsProt = {read=FFlagsProt, write=FFlagsProt};
	__property System::UnicodeString ProtIndicator = {read=FProtIndicator, write=FProtIndicator};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdSterCommEntUxFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdOwnerFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdSterCommEntUxFTPListItem() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPSterComEntBase : public Idftplistparsebase::TIdFTPListBaseHeader
{
	typedef Idftplistparsebase::TIdFTPListBaseHeader inherited;
	
protected:
	__classmethod virtual bool __fastcall IsFooter(const System::UnicodeString AData);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPSterComEntBase() : Idftplistparsebase::TIdFTPListBaseHeader() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPSterComEntBase() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPSterCommEntUx : public TIdFTPLPSterComEntBase
{
	typedef TIdFTPLPSterComEntBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPSterCommEntUx() : TIdFTPLPSterComEntBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPSterCommEntUx() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIdSterCommEntUxNSFTPListItem : public Idftplisttypes::TIdOwnerFTPListItem
{
	typedef Idftplisttypes::TIdOwnerFTPListItem inherited;
	
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdSterCommEntUxNSFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdOwnerFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdSterCommEntUxNSFTPListItem() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPSterCommEntUxNS : public TIdFTPLPSterComEntBase
{
	typedef TIdFTPLPSterComEntBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod void __fastcall StripPlus(System::UnicodeString &VString);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPSterCommEntUxNS() : TIdFTPLPSterComEntBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPSterCommEntUxNS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIdSterCommEntUxRootFTPListItem : public Idftplisttypes::TIdMinimalFTPListItem
{
	typedef Idftplisttypes::TIdMinimalFTPListItem inherited;
	
public:
	/* TIdMinimalFTPListItem.Create */ inline __fastcall virtual TIdSterCommEntUxRootFTPListItem(System::Classes::TCollection* AOwner) : Idftplisttypes::TIdMinimalFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdSterCommEntUxRootFTPListItem() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPLPSterCommEntUxRoot : public TIdFTPLPSterComEntBase
{
	typedef TIdFTPLPSterComEntBase inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall IsFooter(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
	__classmethod virtual bool __fastcall CheckListing(System::Classes::TStrings* AListing, const System::UnicodeString ASysDescript = System::UnicodeString(), const bool ADetails = true);
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPSterCommEntUxRoot() : TIdFTPLPSterComEntBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPSterCommEntUxRoot() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define STIRCOMUNIX L"CONNECT:Enterprise for UNIX"
#define STIRCOMUNIXNS L"CONNECT:Enterprise for UNIX$$"
#define STIRCOMUNIXROOT L"CONNECT:Enterprise for UNIX ROOT"
}	/* namespace Idftplistparsestercomunixent */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSESTERCOMUNIXENT)
using namespace Idftplistparsestercomunixent;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsestercomunixentHPP
