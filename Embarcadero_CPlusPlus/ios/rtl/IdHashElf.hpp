// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHashElf.pas' rev: 34.00 (iOS)

#ifndef IdhashelfHPP
#define IdhashelfHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdGlobal.hpp>
#include <IdHash.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idhashelf
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHashElf;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdHashElf : public Idhash::TIdHash32
{
	typedef Idhash::TIdHash32 inherited;
	
public:
	virtual void __fastcall HashStart(unsigned &VRunningHash);
	virtual void __fastcall HashByte(unsigned &VRunningHash, const System::Byte AByte);
public:
	/* TIdHash.Create */ inline __fastcall virtual TIdHashElf() : Idhash::TIdHash32() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashElf() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idhashelf */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHASHELF)
using namespace Idhashelf;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdhashelfHPP
