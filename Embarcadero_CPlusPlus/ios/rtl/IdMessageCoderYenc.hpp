// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdMessageCoderYenc.pas' rev: 34.00 (iOS)

#ifndef IdmessagecoderyencHPP
#define IdmessagecoderyencHPP

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
#include <IdExceptionCore.hpp>
#include <IdGlobal.hpp>
#include <IdException.hpp>
#include <System.SysUtils.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idmessagecoderyenc
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdMessageYencException;
class DELPHICLASS EIdMessageYencInvalidSizeException;
class DELPHICLASS EIdMessageYencInvalidCRCException;
class DELPHICLASS EIdMessageYencCorruptionException;
class DELPHICLASS TIdMessageDecoderYenc;
class DELPHICLASS TIdMessageDecoderInfoYenc;
class DELPHICLASS TIdMessageEncoderYenc;
class DELPHICLASS TIdMessageEncoderInfoYenc;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EIdMessageYencException : public Idexceptioncore::EIdMessageException
{
	typedef Idexceptioncore::EIdMessageException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdMessageYencException(const System::UnicodeString AMsg)/* overload */ : Idexceptioncore::EIdMessageException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdMessageYencException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexceptioncore::EIdMessageException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdMessageYencException(NativeUInt Ident)/* overload */ : Idexceptioncore::EIdMessageException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdMessageYencException(System::PResStringRec ResStringRec)/* overload */ : Idexceptioncore::EIdMessageException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdMessageYencException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexceptioncore::EIdMessageException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdMessageYencException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexceptioncore::EIdMessageException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdMessageYencException(const System::UnicodeString Msg, int AHelpContext) : Idexceptioncore::EIdMessageException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdMessageYencException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexceptioncore::EIdMessageException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdMessageYencException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexceptioncore::EIdMessageException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdMessageYencException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexceptioncore::EIdMessageException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdMessageYencException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexceptioncore::EIdMessageException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdMessageYencException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexceptioncore::EIdMessageException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdMessageYencException() { }
	
};


class PASCALIMPLEMENTATION EIdMessageYencInvalidSizeException : public EIdMessageYencException
{
	typedef EIdMessageYencException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdMessageYencInvalidSizeException(const System::UnicodeString AMsg)/* overload */ : EIdMessageYencException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdMessageYencInvalidSizeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdMessageYencException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdMessageYencInvalidSizeException(NativeUInt Ident)/* overload */ : EIdMessageYencException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdMessageYencInvalidSizeException(System::PResStringRec ResStringRec)/* overload */ : EIdMessageYencException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdMessageYencInvalidSizeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdMessageYencException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdMessageYencInvalidSizeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdMessageYencException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdMessageYencInvalidSizeException(const System::UnicodeString Msg, int AHelpContext) : EIdMessageYencException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdMessageYencInvalidSizeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdMessageYencException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdMessageYencInvalidSizeException(NativeUInt Ident, int AHelpContext)/* overload */ : EIdMessageYencException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdMessageYencInvalidSizeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdMessageYencException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdMessageYencInvalidSizeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdMessageYencException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdMessageYencInvalidSizeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdMessageYencException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdMessageYencInvalidSizeException() { }
	
};


class PASCALIMPLEMENTATION EIdMessageYencInvalidCRCException : public EIdMessageYencException
{
	typedef EIdMessageYencException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdMessageYencInvalidCRCException(const System::UnicodeString AMsg)/* overload */ : EIdMessageYencException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdMessageYencInvalidCRCException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdMessageYencException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdMessageYencInvalidCRCException(NativeUInt Ident)/* overload */ : EIdMessageYencException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdMessageYencInvalidCRCException(System::PResStringRec ResStringRec)/* overload */ : EIdMessageYencException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdMessageYencInvalidCRCException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdMessageYencException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdMessageYencInvalidCRCException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdMessageYencException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdMessageYencInvalidCRCException(const System::UnicodeString Msg, int AHelpContext) : EIdMessageYencException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdMessageYencInvalidCRCException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdMessageYencException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdMessageYencInvalidCRCException(NativeUInt Ident, int AHelpContext)/* overload */ : EIdMessageYencException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdMessageYencInvalidCRCException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdMessageYencException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdMessageYencInvalidCRCException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdMessageYencException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdMessageYencInvalidCRCException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdMessageYencException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdMessageYencInvalidCRCException() { }
	
};


class PASCALIMPLEMENTATION EIdMessageYencCorruptionException : public EIdMessageYencException
{
	typedef EIdMessageYencException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdMessageYencCorruptionException(const System::UnicodeString AMsg)/* overload */ : EIdMessageYencException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdMessageYencCorruptionException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdMessageYencException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdMessageYencCorruptionException(NativeUInt Ident)/* overload */ : EIdMessageYencException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdMessageYencCorruptionException(System::PResStringRec ResStringRec)/* overload */ : EIdMessageYencException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdMessageYencCorruptionException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdMessageYencException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdMessageYencCorruptionException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdMessageYencException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdMessageYencCorruptionException(const System::UnicodeString Msg, int AHelpContext) : EIdMessageYencException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdMessageYencCorruptionException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdMessageYencException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdMessageYencCorruptionException(NativeUInt Ident, int AHelpContext)/* overload */ : EIdMessageYencException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdMessageYencCorruptionException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdMessageYencException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdMessageYencCorruptionException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdMessageYencException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdMessageYencCorruptionException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdMessageYencException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdMessageYencCorruptionException() { }
	
};


class PASCALIMPLEMENTATION TIdMessageDecoderYenc : public Idmessagecoder::TIdMessageDecoder
{
	typedef Idmessagecoder::TIdMessageDecoder inherited;
	
protected:
	int FPart;
	int FLine;
	int FSize;
	
public:
	virtual Idmessagecoder::TIdMessageDecoder* __fastcall ReadBody(System::Classes::TStream* ADestStream, bool &AMsgEnd);
public:
	/* TIdMessageDecoder.Destroy */ inline __fastcall virtual ~TIdMessageDecoderYenc() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdMessageDecoderYenc(System::Classes::TComponent* AOwner)/* overload */ : Idmessagecoder::TIdMessageDecoder(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMessageDecoderYenc()/* overload */ : Idmessagecoder::TIdMessageDecoder() { }
	
};


class PASCALIMPLEMENTATION TIdMessageDecoderInfoYenc : public Idmessagecoder::TIdMessageDecoderInfo
{
	typedef Idmessagecoder::TIdMessageDecoderInfo inherited;
	
public:
	virtual Idmessagecoder::TIdMessageDecoder* __fastcall CheckForStart(Idmessage::TIdMessage* ASender, const System::UnicodeString ALine);
public:
	/* TIdMessageDecoderInfo.Create */ inline __fastcall virtual TIdMessageDecoderInfoYenc() : Idmessagecoder::TIdMessageDecoderInfo() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdMessageDecoderInfoYenc() { }
	
};


class PASCALIMPLEMENTATION TIdMessageEncoderYenc : public Idmessagecoder::TIdMessageEncoder
{
	typedef Idmessagecoder::TIdMessageEncoder inherited;
	
public:
	virtual void __fastcall Encode(System::Classes::TStream* ASrc, System::Classes::TStream* ADest)/* overload */;
public:
	/* TIdComponent.Destroy */ inline __fastcall virtual ~TIdMessageEncoderYenc() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdMessageEncoderYenc(System::Classes::TComponent* AOwner)/* overload */ : Idmessagecoder::TIdMessageEncoder(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMessageEncoderYenc()/* overload */ : Idmessagecoder::TIdMessageEncoder() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Encode(const System::UnicodeString AFilename, System::Classes::TStream* ADest){ Idmessagecoder::TIdMessageEncoder::Encode(AFilename, ADest); }
	inline void __fastcall  Encode(System::Classes::TStream* ASrc, System::Classes::TStrings* ADest){ Idmessagecoder::TIdMessageEncoder::Encode(ASrc, ADest); }
	
};


class PASCALIMPLEMENTATION TIdMessageEncoderInfoYenc : public Idmessagecoder::TIdMessageEncoderInfo
{
	typedef Idmessagecoder::TIdMessageEncoderInfo inherited;
	
public:
	__fastcall virtual TIdMessageEncoderInfoYenc();
	virtual void __fastcall InitializeHeaders(Idmessage::TIdMessage* AMsg);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdMessageEncoderInfoYenc() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word BUFLEN = System::Word(0x1000);
static constexpr System::Int8 B_PERIOD = System::Int8(0x2e);
static constexpr System::Int8 B_EQUALS = System::Int8(0x3d);
static constexpr System::Int8 B_TAB = System::Int8(0x9);
static constexpr System::Int8 B_LF = System::Int8(0xa);
static constexpr System::Int8 B_CR = System::Int8(0xd);
static constexpr System::Int8 B_NUL = System::Int8(0x0);
}	/* namespace Idmessagecoderyenc */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDMESSAGECODERYENC)
using namespace Idmessagecoderyenc;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdmessagecoderyencHPP
