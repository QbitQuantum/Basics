// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdMessageCoderUUE.pas' rev: 34.00 (Windows)

#ifndef IdmessagecoderuueHPP
#define IdmessagecoderuueHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdCoder3to4.hpp>
#include <IdMessageCoder.hpp>
#include <IdMessage.hpp>
#include <IdGlobal.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idmessagecoderuue
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdMessageDecoderUUE;
class DELPHICLASS TIdMessageDecoderInfoUUE;
class DELPHICLASS TIdMessageEncoderUUEBase;
class DELPHICLASS TIdMessageEncoderUUE;
class DELPHICLASS TIdMessageEncoderInfoUUE;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdMessageDecoderUUE : public Idmessagecoder::TIdMessageDecoder
{
	typedef Idmessagecoder::TIdMessageDecoder inherited;
	
protected:
	System::UnicodeString FCodingType;
	
public:
	virtual Idmessagecoder::TIdMessageDecoder* __fastcall ReadBody(System::Classes::TStream* ADestStream, bool &AMsgEnd);
	__property System::UnicodeString CodingType = {read=FCodingType};
public:
	/* TIdMessageDecoder.Destroy */ inline __fastcall virtual ~TIdMessageDecoderUUE() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdMessageDecoderUUE(System::Classes::TComponent* AOwner)/* overload */ : Idmessagecoder::TIdMessageDecoder(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMessageDecoderUUE()/* overload */ : Idmessagecoder::TIdMessageDecoder() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdMessageDecoderInfoUUE : public Idmessagecoder::TIdMessageDecoderInfo
{
	typedef Idmessagecoder::TIdMessageDecoderInfo inherited;
	
public:
	virtual Idmessagecoder::TIdMessageDecoder* __fastcall CheckForStart(Idmessage::TIdMessage* ASender, const System::UnicodeString ALine);
public:
	/* TIdMessageDecoderInfo.Create */ inline __fastcall virtual TIdMessageDecoderInfoUUE() : Idmessagecoder::TIdMessageDecoderInfo() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdMessageDecoderInfoUUE() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIdMessageEncoderUUEBase : public Idmessagecoder::TIdMessageEncoder
{
	typedef Idmessagecoder::TIdMessageEncoder inherited;
	
protected:
	Idcoder3to4::TIdEncoder3to4Class FEncoderClass;
	
public:
	virtual void __fastcall Encode(System::Classes::TStream* ASrc, System::Classes::TStream* ADest)/* overload */;
public:
	/* TIdComponent.Destroy */ inline __fastcall virtual ~TIdMessageEncoderUUEBase() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdMessageEncoderUUEBase(System::Classes::TComponent* AOwner)/* overload */ : Idmessagecoder::TIdMessageEncoder(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMessageEncoderUUEBase()/* overload */ : Idmessagecoder::TIdMessageEncoder() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Encode(const System::UnicodeString AFilename, System::Classes::TStream* ADest){ Idmessagecoder::TIdMessageEncoder::Encode(AFilename, ADest); }
	inline void __fastcall  Encode(System::Classes::TStream* ASrc, System::Classes::TStrings* ADest){ Idmessagecoder::TIdMessageEncoder::Encode(ASrc, ADest); }
	
};


class PASCALIMPLEMENTATION TIdMessageEncoderUUE : public TIdMessageEncoderUUEBase
{
	typedef TIdMessageEncoderUUEBase inherited;
	
protected:
	virtual void __fastcall InitComponent();
public:
	/* TIdComponent.Destroy */ inline __fastcall virtual ~TIdMessageEncoderUUE() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdMessageEncoderUUE(System::Classes::TComponent* AOwner)/* overload */ : TIdMessageEncoderUUEBase(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMessageEncoderUUE()/* overload */ : TIdMessageEncoderUUEBase() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdMessageEncoderInfoUUE : public Idmessagecoder::TIdMessageEncoderInfo
{
	typedef Idmessagecoder::TIdMessageEncoderInfo inherited;
	
public:
	__fastcall virtual TIdMessageEncoderInfoUUE();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdMessageEncoderInfoUUE() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idmessagecoderuue */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDMESSAGECODERUUE)
using namespace Idmessagecoderuue;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdmessagecoderuueHPP
