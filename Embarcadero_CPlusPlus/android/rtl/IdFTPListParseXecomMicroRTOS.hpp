// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListParseXecomMicroRTOS.pas' rev: 34.00 (Android)

#ifndef IdftplistparsexecommicrortosHPP
#define IdftplistparsexecommicrortosHPP

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

//-- user supplied -----------------------------------------------------------
namespace Idftplistparsexecommicrortos
{
  _INIT_UNIT(Idftplistparsexecommicrortos);
}	/* namespace Idftplistparsexecommicrortos */

namespace Idftplistparsexecommicrortos
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdXecomMicroRTOSTPListItem;
class DELPHICLASS TIdFTPLPXecomMicroRTOS;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdXecomMicroRTOSTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
protected:
	unsigned FMemStart;
	unsigned FMemEnd;
	
public:
	__fastcall virtual TIdXecomMicroRTOSTPListItem(System::Classes::TCollection* AOwner);
	__property unsigned MemStart = {read=FMemStart, write=FMemStart, nodefault};
	__property unsigned MemEnd = {read=FMemEnd, write=FMemEnd, nodefault};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdXecomMicroRTOSTPListItem() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdFTPLPXecomMicroRTOS : public Idftplistparsebase::TIdFTPListBaseHeader
{
	typedef Idftplistparsebase::TIdFTPListBaseHeader inherited;
	
protected:
	__classmethod virtual Idftplist::TIdFTPListItem* __fastcall MakeNewItem(Idftplist::TIdFTPListItems* AOwner);
	__classmethod virtual bool __fastcall IsHeader(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall IsFooter(const System::UnicodeString AData);
	__classmethod virtual bool __fastcall ParseLine(Idftplist::TIdFTPListItem* const AItem, const System::UnicodeString APath = System::UnicodeString());
	
public:
	__classmethod virtual System::UnicodeString __fastcall GetIdent();
public:
	/* TObject.Create */ inline __fastcall TIdFTPLPXecomMicroRTOS() : Idftplistparsebase::TIdFTPListBaseHeader() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdFTPLPXecomMicroRTOS() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplistparsexecommicrortos */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTPARSEXECOMMICRORTOS)
using namespace Idftplistparsexecommicrortos;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistparsexecommicrortosHPP
