// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHeaderCoderPlain.pas' rev: 34.00 (iOS)

#ifndef IdheadercoderplainHPP
#define IdheadercoderplainHPP

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
namespace Idheadercoderplain
{
  _INIT_UNIT(Idheadercoderplain);
}	/* namespace Idheadercoderplain */

namespace Idheadercoderplain
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHeaderCoderPlain;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdHeaderCoderPlain : public Idheadercoderbase::TIdHeaderCoder
{
	typedef Idheadercoderbase::TIdHeaderCoder inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Decode(const System::UnicodeString ACharSet, const Idglobal::TIdBytes AData);
	__classmethod virtual Idglobal::TIdBytes __fastcall Encode(const System::UnicodeString ACharSet, const System::UnicodeString AData);
	__classmethod virtual bool __fastcall CanHandle(const System::UnicodeString ACharSet);
public:
	/* TObject.Create */ inline __fastcall TIdHeaderCoderPlain() : Idheadercoderbase::TIdHeaderCoder() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHeaderCoderPlain() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idheadercoderplain */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHEADERCODERPLAIN)
using namespace Idheadercoderplain;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdheadercoderplainHPP
