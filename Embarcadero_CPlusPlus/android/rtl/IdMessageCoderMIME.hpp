// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdMessageCoderMIME.pas' rev: 34.00 (Android)

#ifndef IdmessagecodermimeHPP
#define IdmessagecodermimeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdBaseComponent.hpp>
#include <IdMessageCoder.hpp>
#include <IdMessage.hpp>
#include <IdGlobal.hpp>
#include <IdComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idmessagecodermime
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdMessageDecoderMIME;
class DELPHICLASS TIdMessageDecoderInfoMIME;
class DELPHICLASS TIdMessageEncoderMIME;
class DELPHICLASS TIdMessageEncoderInfoMIME;
class DELPHICLASS TIdMIMEBoundaryStrings;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdMessageDecoderMIME : public Idmessagecoder::TIdMessageDecoder
{
	typedef Idmessagecoder::TIdMessageDecoder inherited;
	
protected:
	System::UnicodeString FFirstLine;
	bool FProcessFirstLine;
	bool FBodyEncoded;
	System::UnicodeString FMIMEBoundary;
	System::UnicodeString __fastcall GetProperHeaderItem(const System::UnicodeString Line);
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdMessageDecoderMIME(System::Classes::TComponent* AOwner, const System::UnicodeString ALine)/* overload */;
	virtual Idmessagecoder::TIdMessageDecoder* __fastcall ReadBody(System::Classes::TStream* ADestStream, bool &VMsgEnd);
	void __fastcall CheckAndSetType(const System::UnicodeString AContentType, const System::UnicodeString AContentDisposition);
	virtual void __fastcall ReadHeader();
	System::UnicodeString __fastcall GetAttachmentFilename(const System::UnicodeString AContentType, const System::UnicodeString AContentDisposition);
	System::UnicodeString __fastcall RemoveInvalidCharsFromFilename(const System::UnicodeString AFilename);
	__property System::UnicodeString MIMEBoundary = {read=FMIMEBoundary, write=FMIMEBoundary};
	__property bool BodyEncoded = {read=FBodyEncoded, write=FBodyEncoded, nodefault};
public:
	/* TIdMessageDecoder.Destroy */ inline __fastcall virtual ~TIdMessageDecoderMIME() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdMessageDecoderMIME(System::Classes::TComponent* AOwner)/* overload */ : Idmessagecoder::TIdMessageDecoder(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMessageDecoderMIME()/* overload */ : Idmessagecoder::TIdMessageDecoder() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdMessageDecoderInfoMIME : public Idmessagecoder::TIdMessageDecoderInfo
{
	typedef Idmessagecoder::TIdMessageDecoderInfo inherited;
	
public:
	virtual Idmessagecoder::TIdMessageDecoder* __fastcall CheckForStart(Idmessage::TIdMessage* ASender, const System::UnicodeString ALine);
public:
	/* TIdMessageDecoderInfo.Create */ inline __fastcall virtual TIdMessageDecoderInfoMIME() : Idmessagecoder::TIdMessageDecoderInfo() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdMessageDecoderInfoMIME() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TIdMessageEncoderMIME : public Idmessagecoder::TIdMessageEncoder
{
	typedef Idmessagecoder::TIdMessageEncoder inherited;
	
public:
	virtual void __fastcall Encode(System::Classes::TStream* ASrc, System::Classes::TStream* ADest)/* overload */;
public:
	/* TIdComponent.Destroy */ inline __fastcall virtual ~TIdMessageEncoderMIME() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdMessageEncoderMIME(System::Classes::TComponent* AOwner)/* overload */ : Idmessagecoder::TIdMessageEncoder(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMessageEncoderMIME()/* overload */ : Idmessagecoder::TIdMessageEncoder() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Encode(const System::UnicodeString AFilename, System::Classes::TStream* ADest){ Idmessagecoder::TIdMessageEncoder::Encode(AFilename, ADest); }
	inline void __fastcall  Encode(System::Classes::TStream* ASrc, System::Classes::TStrings* ADest){ Idmessagecoder::TIdMessageEncoder::Encode(ASrc, ADest); }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdMessageEncoderInfoMIME : public Idmessagecoder::TIdMessageEncoderInfo
{
	typedef Idmessagecoder::TIdMessageEncoderInfo inherited;
	
public:
	__fastcall virtual TIdMessageEncoderInfoMIME();
	virtual void __fastcall InitializeHeaders(Idmessage::TIdMessage* AMsg);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdMessageEncoderInfoMIME() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdMIMEBoundaryStrings : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod System::WideChar __fastcall GenerateRandomChar();
	__classmethod System::UnicodeString __fastcall GenerateBoundary();
public:
	/* TObject.Create */ inline __fastcall TIdMIMEBoundaryStrings() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdMIMEBoundaryStrings() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idmessagecodermime */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDMESSAGECODERMIME)
using namespace Idmessagecodermime;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdmessagecodermimeHPP
