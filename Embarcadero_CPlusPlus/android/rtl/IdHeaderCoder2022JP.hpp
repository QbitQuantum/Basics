﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHeaderCoder2022JP.pas' rev: 34.00 (Android)

#ifndef Idheadercoder2022jpHPP
#define Idheadercoder2022jpHPP

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
namespace Idheadercoder2022jp
{
  _INIT_UNIT(Idheadercoder2022jp);
}	/* namespace Idheadercoder2022jp */

namespace Idheadercoder2022jp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHeaderCoder2022JP;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHeaderCoder2022JP : public Idheadercoderbase::TIdHeaderCoder
{
	typedef Idheadercoderbase::TIdHeaderCoder inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Decode(const System::UnicodeString ACharSet, const Idglobal::TIdBytes AData);
	__classmethod virtual Idglobal::TIdBytes __fastcall Encode(const System::UnicodeString ACharSet, const System::UnicodeString AData);
	__classmethod virtual bool __fastcall CanHandle(const System::UnicodeString ACharSet);
public:
	/* TObject.Create */ inline __fastcall TIdHeaderCoder2022JP() : Idheadercoderbase::TIdHeaderCoder() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHeaderCoder2022JP() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idheadercoder2022jp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHEADERCODER2022JP)
using namespace Idheadercoder2022jp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idheadercoder2022jpHPP
