// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdMessageCoderBinHex4.pas' rev: 34.00 (iOS)

#ifndef Idmessagecoderbinhex4HPP
#define Idmessagecoderbinhex4HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdMessageCoder.hpp>
#include <IdMessage.hpp>
#include <IdGlobal.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idmessagecoderbinhex4
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdMessageEncoderBinHex4;
class DELPHICLASS TIdMessageEncoderInfoBinHex4;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdMessageEncoderBinHex4 : public Idmessagecoder::TIdMessageEncoder
{
	typedef Idmessagecoder::TIdMessageEncoder inherited;
	
public:
	virtual void __fastcall Encode(System::Classes::TStream* ASrc, System::Classes::TStream* ADest)/* overload */;
public:
	/* TIdComponent.Destroy */ inline __fastcall virtual ~TIdMessageEncoderBinHex4() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdMessageEncoderBinHex4(System::Classes::TComponent* AOwner)/* overload */ : Idmessagecoder::TIdMessageEncoder(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMessageEncoderBinHex4()/* overload */ : Idmessagecoder::TIdMessageEncoder() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Encode(const System::UnicodeString AFilename, System::Classes::TStream* ADest){ Idmessagecoder::TIdMessageEncoder::Encode(AFilename, ADest); }
	inline void __fastcall  Encode(System::Classes::TStream* ASrc, System::Classes::TStrings* ADest){ Idmessagecoder::TIdMessageEncoder::Encode(ASrc, ADest); }
	
};


class PASCALIMPLEMENTATION TIdMessageEncoderInfoBinHex4 : public Idmessagecoder::TIdMessageEncoderInfo
{
	typedef Idmessagecoder::TIdMessageEncoderInfo inherited;
	
public:
	__fastcall virtual TIdMessageEncoderInfoBinHex4();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdMessageEncoderInfoBinHex4() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idmessagecoderbinhex4 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDMESSAGECODERBINHEX4)
using namespace Idmessagecoderbinhex4;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idmessagecoderbinhex4HPP
