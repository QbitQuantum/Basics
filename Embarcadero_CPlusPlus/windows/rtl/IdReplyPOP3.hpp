// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdReplyPOP3.pas' rev: 34.00 (Windows)

#ifndef Idreplypop3HPP
#define Idreplypop3HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdException.hpp>
#include <IdReply.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idreplypop3
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdReplyPOP3;
class DELPHICLASS TIdRepliesPOP3;
class DELPHICLASS EIdReplyPOP3Error;
class DELPHICLASS EIdPOP3ReplyException;
class DELPHICLASS EIdPOP3ReplyInvalidEnhancedCode;
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<System::UnicodeString, 5> Idreplypop3__1;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdReplyPOP3 : public Idreply::TIdReply
{
	typedef Idreply::TIdReply inherited;
	
protected:
	System::UnicodeString FEnhancedCode;
	__classmethod int __fastcall FindCodeTextDelim(const System::UnicodeString AText);
	__classmethod bool __fastcall IsValidEnhancedCode(const System::UnicodeString AText, const bool AStrict = false);
	__classmethod int __fastcall ExtractTextPosArray(const System::UnicodeString AStr);
	virtual System::Classes::TStrings* __fastcall GetFormattedReply();
	virtual void __fastcall SetFormattedReply(System::Classes::TStrings* const AValue);
	virtual bool __fastcall CheckIfCodeIsValid(const System::UnicodeString ACode);
	void __fastcall SetEnhancedCode(const System::UnicodeString AValue);
	
public:
	__fastcall virtual TIdReplyPOP3(System::Classes::TCollection* ACollection, Idreply::TIdReplies* AReplyTexts);
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
	virtual void __fastcall RaiseReplyError();
	__classmethod virtual bool __fastcall IsEndMarker(const System::UnicodeString ALine);
	
__published:
	__property System::UnicodeString EnhancedCode = {read=FEnhancedCode, write=SetEnhancedCode};
public:
	/* TIdReply.Create */ inline __fastcall virtual TIdReplyPOP3(System::Classes::TCollection* ACollection) : Idreply::TIdReply(ACollection) { }
	/* TIdReply.Destroy */ inline __fastcall virtual ~TIdReplyPOP3() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdRepliesPOP3 : public Idreply::TIdReplies
{
	typedef Idreply::TIdReplies inherited;
	
public:
	__fastcall TIdRepliesPOP3(System::Classes::TPersistent* AOwner);
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdRepliesPOP3() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdReplyPOP3Error : public Idreply::EIdReplyError
{
	typedef Idreply::EIdReplyError inherited;
	
protected:
	System::UnicodeString FErrorCode;
	System::UnicodeString FEnhancedCode;
	
public:
	__fastcall virtual EIdReplyPOP3Error(const System::UnicodeString AErrorCode, const System::UnicodeString AReplyMessage, const System::UnicodeString AEnhancedCode);
	__property System::UnicodeString ErrorCode = {read=FErrorCode};
	__property System::UnicodeString EnhancedCode = {read=FEnhancedCode};
public:
	/* EIdException.Create */ inline __fastcall virtual EIdReplyPOP3Error(const System::UnicodeString AMsg)/* overload */ : Idreply::EIdReplyError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdReplyPOP3Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idreply::EIdReplyError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdReplyPOP3Error(NativeUInt Ident)/* overload */ : Idreply::EIdReplyError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdReplyPOP3Error(System::PResStringRec ResStringRec)/* overload */ : Idreply::EIdReplyError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdReplyPOP3Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreply::EIdReplyError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdReplyPOP3Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreply::EIdReplyError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdReplyPOP3Error(const System::UnicodeString Msg, int AHelpContext) : Idreply::EIdReplyError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdReplyPOP3Error(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idreply::EIdReplyError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdReplyPOP3Error(NativeUInt Ident, int AHelpContext)/* overload */ : Idreply::EIdReplyError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdReplyPOP3Error(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idreply::EIdReplyError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdReplyPOP3Error(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreply::EIdReplyError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdReplyPOP3Error(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreply::EIdReplyError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdReplyPOP3Error() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::StaticArray<System::UnicodeString, 3> Idreplypop3__5;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdPOP3ReplyException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdPOP3ReplyException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdPOP3ReplyException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdPOP3ReplyException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdPOP3ReplyException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdPOP3ReplyException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdPOP3ReplyException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdPOP3ReplyException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdPOP3ReplyException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdPOP3ReplyException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdPOP3ReplyException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdPOP3ReplyException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdPOP3ReplyException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdPOP3ReplyException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdPOP3ReplyInvalidEnhancedCode : public EIdPOP3ReplyException
{
	typedef EIdPOP3ReplyException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdPOP3ReplyInvalidEnhancedCode(const System::UnicodeString AMsg)/* overload */ : EIdPOP3ReplyException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdPOP3ReplyInvalidEnhancedCode(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdPOP3ReplyException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdPOP3ReplyInvalidEnhancedCode(NativeUInt Ident)/* overload */ : EIdPOP3ReplyException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdPOP3ReplyInvalidEnhancedCode(System::PResStringRec ResStringRec)/* overload */ : EIdPOP3ReplyException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdPOP3ReplyInvalidEnhancedCode(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdPOP3ReplyException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdPOP3ReplyInvalidEnhancedCode(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdPOP3ReplyException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdPOP3ReplyInvalidEnhancedCode(const System::UnicodeString Msg, int AHelpContext) : EIdPOP3ReplyException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdPOP3ReplyInvalidEnhancedCode(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdPOP3ReplyException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdPOP3ReplyInvalidEnhancedCode(NativeUInt Ident, int AHelpContext)/* overload */ : EIdPOP3ReplyException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdPOP3ReplyInvalidEnhancedCode(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdPOP3ReplyException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdPOP3ReplyInvalidEnhancedCode(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdPOP3ReplyException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdPOP3ReplyInvalidEnhancedCode(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdPOP3ReplyException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdPOP3ReplyInvalidEnhancedCode() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define ST_OK L"+OK"
#define ST_ERR L"-ERR"
static const System::WideChar ST_SASLCONTINUE = (System::WideChar)(0x2b);
#define ST_ERR_IN_USE L"IN-USE"
#define ST_ERR_LOGIN_DELAY L"LOGIN-DELAY"
#define ST_ERR_SYS_TEMP L"SYS/PERM"
#define ST_ERR_SYS_PERM L"SYS/TEMP"
#define ST_ERR_AUTH L"AUTH"
extern DELPHI_PACKAGE Idreplypop3__1 VALID_ENH_CODES;
extern DELPHI_PACKAGE Idreplypop3__5 VALID_POP3_STR;
}	/* namespace Idreplypop3 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDREPLYPOP3)
using namespace Idreplypop3;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idreplypop3HPP
