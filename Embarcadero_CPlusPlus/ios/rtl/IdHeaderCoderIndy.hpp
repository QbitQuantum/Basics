﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHeaderCoderIndy.pas' rev: 34.00 (iOS)

#ifndef IdheadercoderindyHPP
#define IdheadercoderindyHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdGlobal.hpp>
#include <IdHeaderCoderBase.hpp>

//-- user supplied -----------------------------------------------------------
namespace Idheadercoderindy
{
  _INIT_UNIT(Idheadercoderindy);
}	/* namespace Idheadercoderindy */

namespace Idheadercoderindy
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHeaderCoderIndy;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdHeaderCoderIndy : public Idheadercoderbase::TIdHeaderCoder
{
	typedef Idheadercoderbase::TIdHeaderCoder inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Decode(const System::UnicodeString ACharSet, const Idglobal::TIdBytes AData);
	__classmethod virtual Idglobal::TIdBytes __fastcall Encode(const System::UnicodeString ACharSet, const System::UnicodeString AData);
	__classmethod virtual bool __fastcall CanHandle(const System::UnicodeString ACharSet);
public:
	/* TObject.Create */ inline __fastcall TIdHeaderCoderIndy() : Idheadercoderbase::TIdHeaderCoder() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHeaderCoderIndy() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idheadercoderindy */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHEADERCODERINDY)
using namespace Idheadercoderindy;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdheadercoderindyHPP
