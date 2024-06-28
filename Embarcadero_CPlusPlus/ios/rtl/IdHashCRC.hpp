// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHashCRC.pas' rev: 34.00 (iOS)

#ifndef IdhashcrcHPP
#define IdhashcrcHPP

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

namespace Idhashcrc
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHashCRC16;
class DELPHICLASS TIdHashCRC32;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdHashCRC16 : public Idhash::TIdHash16
{
	typedef Idhash::TIdHash16 inherited;
	
public:
	virtual void __fastcall HashStart(System::Word &VRunningHash);
	virtual void __fastcall HashByte(System::Word &VRunningHash, const System::Byte AByte);
public:
	/* TIdHash.Create */ inline __fastcall virtual TIdHashCRC16() : Idhash::TIdHash16() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashCRC16() { }
	
};


class PASCALIMPLEMENTATION TIdHashCRC32 : public Idhash::TIdHash32
{
	typedef Idhash::TIdHash32 inherited;
	
public:
	virtual void __fastcall HashStart(unsigned &VRunningHash);
	virtual void __fastcall HashEnd(unsigned &VRunningHash);
	virtual void __fastcall HashByte(unsigned &VRunningHash, const System::Byte AByte);
public:
	/* TIdHash.Create */ inline __fastcall virtual TIdHashCRC32() : Idhash::TIdHash32() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashCRC32() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idhashcrc */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHASHCRC)
using namespace Idhashcrc;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdhashcrcHPP
