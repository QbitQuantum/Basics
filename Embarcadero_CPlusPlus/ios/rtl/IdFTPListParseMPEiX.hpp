// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseMPEiX.pas' rev: 34.00 (iOS)

#ifndef IdftplistparsempeixHPP
#define IdftplistparsempeixHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdFTPList.hpp>
#include <IdFTPListParseBase.hpp>
#include <IdFTPListTypes.hpp>

//-- user supplied -----------------------------------------------------------
namespace Idftplistparsempeix
{
  _INIT_UNIT(Idftplistparsempeix);
}	/* namespace Idftplistparsempeix */

namespace Idftplistparsempeix
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdMPiXFTPListItem;
class DELPHICLASS TIdFTPLPMPiXBase;
class DELPHICLASS TIdFTPLPMPiX;
class DELPHICLASS TIdFTPLPMPiXWithPOSIX;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdMPiXFTPListItem : public Idftplisttypes::TIdRecFTPListItem
{
	typedef Idftplisttypes::TIdRecFTPListItem inherited;
	
protected:
	unsigned FLimit;
	
public:
	__fastcall virtual TIdMPiXFTPListItem(System::Classes::TCollection* AOwner);
	__property RecLength;
	__property RecFormat = {default=0};
	__property NumberRecs;
	__property unsigned Limit = {read=FLimit, write=FLimit, nodefault};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdMPiXFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPMPiXBase : public Idftplistparsebase::TIdFTPListBaseHeader
{
	typedef Idftplistparsebase::TIdFTPListBaseHeader inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall IsSecondHeader(System::Classes::TStrings* ACols);
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPMPiXBase() : Idftplistparsebase::TIdFTPListBaseHeader() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPMPiXBase() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPMPiX : public TIdFTPLPMPiXBase
{
	typedef TIdFTPLPMPiXBase inherited;
	
protected:
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	__classmethod virtual bool __fastcall IsHeader(const System::UnicodeString AData);
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPMPiX() : TIdFTPLPMPiXBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPMPiX() { }
	
};


class PASCALIMPLEMENTATION TIdFTPLPMPiXWithPOSIX : public TIdFTPLPMPiXBase
{
	typedef TIdFTPLPMPiXBase inherited;
	
protected:
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	__classmethod virtual bool __fastcall IsHeader(const System::UnicodeString AData);
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPMPiXWithPOSIX() : TIdFTPLPMPiXBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPMPiXWithPOSIX() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsempeix */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEMPEIX)
using namespace Idftplistparsempeix;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsempeixHPP
