// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdReplyIMAP4.pas' rev: 34.00 (Android)

#ifndef Idreplyimap4HPP
#define Idreplyimap4HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdReply.hpp>
#include <IdReplyRFC.hpp>
#include <IdException.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idreplyimap4
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdReplyIMAP4;
class DELPHICLASS TIdRepliesIMAP4;
class DELPHICLASS EIdReplyIMAP4Error;
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<System::UnicodeString, 6> Idreplyimap4__1;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdReplyIMAP4 : public Idreply::TIdReply
{
	typedef Idreply::TIdReply inherited;
	
protected:
	System::UnicodeString FSequenceNumber;
	System::Classes::TStrings* FExtra;
	System::Classes::TStrings* __fastcall GetExtra();
	virtual System::Classes::TStrings* __fastcall GetFormattedReply();
	virtual void __fastcall SetFormattedReply(System::Classes::TStrings* const AValue);
	virtual bool __fastcall CheckIfCodeIsValid(const System::UnicodeString ACode);
	
public:
	__fastcall virtual TIdReplyIMAP4(System::Classes::TCollection* ACollection, Idreply::TIdReplies* AReplyTexts);
	__fastcall virtual ~TIdReplyIMAP4();
	virtual void __fastcall Clear();
	virtual void __fastcall RaiseReplyError();
	void __fastcall DoReplyError(System::UnicodeString ADescription, System::UnicodeString AnOffendingLine = System::UnicodeString());
	void __fastcall RemoveUnsolicitedResponses(System::UnicodeString *AExpectedResponses, const int AExpectedResponses_High);
	bool __fastcall DoesLineHaveExpectedResponse(System::UnicodeString ALine, System::UnicodeString *AExpectedResponses, const int AExpectedResponses_High);
	bool __fastcall IsItAValidSequenceNumber(const System::UnicodeString AValue);
	bool __fastcall ParseRequest(System::UnicodeString ARequest);
	__property int NumericCode = {read=GetNumericCode, write=SetNumericCode, nodefault};
	__property System::Classes::TStrings* Extra = {read=GetExtra};
	__property System::UnicodeString SequenceNumber = {read=FSequenceNumber};
public:
	/* TIdReply.Create */ inline __fastcall virtual TIdReplyIMAP4(System::Classes::TCollection* ACollection) : Idreply::TIdReply(ACollection) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRepliesIMAP4 : public Idreply::TIdReplies
{
	typedef Idreply::TIdReplies inherited;
	
public:
	__fastcall TIdRepliesIMAP4(System::Classes::TPersistent* AOwner);
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdRepliesIMAP4() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdReplyIMAP4Error : public Idreply::EIdReplyError
{
	typedef Idreply::EIdReplyError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdReplyIMAP4Error(const System::UnicodeString AMsg)/* overload */ : Idreply::EIdReplyError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdReplyIMAP4Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idreply::EIdReplyError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdReplyIMAP4Error(NativeUInt Ident)/* overload */ : Idreply::EIdReplyError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdReplyIMAP4Error(System::PResStringRec ResStringRec)/* overload */ : Idreply::EIdReplyError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdReplyIMAP4Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreply::EIdReplyError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdReplyIMAP4Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreply::EIdReplyError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdReplyIMAP4Error(const System::UnicodeString Msg, int AHelpContext) : Idreply::EIdReplyError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdReplyIMAP4Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idreply::EIdReplyError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdReplyIMAP4Error(NativeUInt Ident, int AHelpContext)/* overload */ : Idreply::EIdReplyError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdReplyIMAP4Error(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idreply::EIdReplyError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdReplyIMAP4Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreply::EIdReplyError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdReplyIMAP4Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreply::EIdReplyError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdReplyIMAP4Error() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define IMAP_OK u"OK"
#define IMAP_NO u"NO"
#define IMAP_BAD u"BAD"
#define IMAP_PREAUTH u"PREAUTH"
#define IMAP_BYE u"BYE"
static constexpr System::WideChar IMAP_CONT = (System::WideChar)(0x2b);
extern DELPHI_PACKAGE Idreplyimap4__1 VALID_TAGGEDREPLIES;
}	/* namespace Idreplyimap4 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDREPLYIMAP4)
using namespace Idreplyimap4;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idreplyimap4HPP
