// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdReplySMTP.pas' rev: 34.00 (Android)

#ifndef IdreplysmtpHPP
#define IdreplysmtpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdException.hpp>
#include <IdReply.hpp>
#include <IdReplyRFC.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idreplysmtp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSMTPEnhancedCode;
class DELPHICLASS TIdReplySMTP;
class DELPHICLASS TIdRepliesSMTP;
class DELPHICLASS EIdSMTPReplyError;
class DELPHICLASS EIdSMTPReply;
class DELPHICLASS EIdSMTPReplyInvalidReplyString;
class DELPHICLASS EIdSMTPReplyInvalidClass;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdSMTPEnhancedCode : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	unsigned FStatusClass;
	unsigned FSubject;
	unsigned FDetails;
	bool FAvailable;
	virtual void __fastcall AssignTo(System::Classes::TPersistent* ADest);
	bool __fastcall IsValidReplyCode(const System::UnicodeString AText);
	System::UnicodeString __fastcall GetReplyAsStr();
	void __fastcall SetReplyAsStr(const System::UnicodeString AText);
	void __fastcall SetStatusClass(const unsigned AValue);
	void __fastcall SetAvailable(const bool AValue);
	
public:
	__fastcall TIdSMTPEnhancedCode();
	
__published:
	__property unsigned StatusClass = {read=FStatusClass, write=SetStatusClass, default=2};
	__property unsigned Subject = {read=FSubject, write=FSubject, default=0};
	__property unsigned Details = {read=FDetails, write=FDetails, default=0};
	__property bool Available = {read=FAvailable, write=SetAvailable, default=0};
	__property System::UnicodeString ReplyAsStr = {read=GetReplyAsStr, write=SetReplyAsStr};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TIdSMTPEnhancedCode() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdReplySMTP : public Idreplyrfc::TIdReplyRFC
{
	typedef Idreplyrfc::TIdReplyRFC inherited;
	
protected:
	TIdSMTPEnhancedCode* FEnhancedCode;
	virtual void __fastcall AssignTo(System::Classes::TPersistent* ADest);
	void __fastcall SetEnhancedCode(TIdSMTPEnhancedCode* AValue);
	virtual System::Classes::TStrings* __fastcall GetFormattedReply();
	virtual void __fastcall SetFormattedReply(System::Classes::TStrings* const AValue);
	
public:
	__fastcall virtual TIdReplySMTP(System::Classes::TCollection* ACollection)/* overload */;
	__fastcall virtual TIdReplySMTP(System::Classes::TCollection* ACollection, Idreply::TIdReplies* AReplyTexts)/* overload */;
	__fastcall virtual ~TIdReplySMTP();
	virtual void __fastcall RaiseReplyError();
	void __fastcall SetEnhReply(const int ANumericCode, const System::UnicodeString AEnhReply, const System::UnicodeString AText);
	
__published:
	__property TIdSMTPEnhancedCode* EnhancedCode = {read=FEnhancedCode, write=SetEnhancedCode};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRepliesSMTP : public Idreplyrfc::TIdRepliesRFC
{
	typedef Idreplyrfc::TIdRepliesRFC inherited;
	
public:
	__fastcall virtual TIdRepliesSMTP(System::Classes::TPersistent* AOwner)/* overload */;
public:
	/* TIdRepliesRFC.Create */ inline __fastcall virtual TIdRepliesSMTP(System::Classes::TPersistent* AOwner, const Idreply::TIdReplyClass AReplyClass)/* overload */ : Idreplyrfc::TIdRepliesRFC(AOwner, AReplyClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdRepliesSMTP() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdSMTPReplyError : public Idreplyrfc::EIdReplyRFCError
{
	typedef Idreplyrfc::EIdReplyRFCError inherited;
	
protected:
	TIdSMTPEnhancedCode* FEnhancedCode;
	
public:
	__fastcall EIdSMTPReplyError(const int AErrCode, TIdSMTPEnhancedCode* AEnhanced, const System::UnicodeString AReplyMessage);
	__fastcall virtual ~EIdSMTPReplyError();
	__property TIdSMTPEnhancedCode* EnhancedCode = {read=FEnhancedCode};
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSMTPReplyError(const System::UnicodeString AMsg)/* overload */ : Idreplyrfc::EIdReplyRFCError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSMTPReplyError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idreplyrfc::EIdReplyRFCError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPReplyError(NativeUInt Ident)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPReplyError(System::PResStringRec ResStringRec)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPReplyError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPReplyError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSMTPReplyError(const System::UnicodeString Msg, int AHelpContext) : Idreplyrfc::EIdReplyRFCError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSMTPReplyError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idreplyrfc::EIdReplyRFCError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPReplyError(NativeUInt Ident, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPReplyError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPReplyError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPReplyError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, Args, Args_High, AHelpContext) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdSMTPReply : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSMTPReply(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSMTPReply(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPReply(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPReply(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPReply(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPReply(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSMTPReply(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSMTPReply(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPReply(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPReply(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPReply(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPReply(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSMTPReply() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdSMTPReplyInvalidReplyString : public EIdSMTPReply
{
	typedef EIdSMTPReply inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSMTPReplyInvalidReplyString(const System::UnicodeString AMsg)/* overload */ : EIdSMTPReply(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSMTPReplyInvalidReplyString(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSMTPReply(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPReplyInvalidReplyString(NativeUInt Ident)/* overload */ : EIdSMTPReply(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPReplyInvalidReplyString(System::PResStringRec ResStringRec)/* overload */ : EIdSMTPReply(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPReplyInvalidReplyString(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSMTPReply(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPReplyInvalidReplyString(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSMTPReply(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSMTPReplyInvalidReplyString(const System::UnicodeString Msg, int AHelpContext) : EIdSMTPReply(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSMTPReplyInvalidReplyString(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSMTPReply(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPReplyInvalidReplyString(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSMTPReply(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPReplyInvalidReplyString(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSMTPReply(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPReplyInvalidReplyString(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSMTPReply(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPReplyInvalidReplyString(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSMTPReply(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSMTPReplyInvalidReplyString() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdSMTPReplyInvalidClass : public EIdSMTPReply
{
	typedef EIdSMTPReply inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSMTPReplyInvalidClass(const System::UnicodeString AMsg)/* overload */ : EIdSMTPReply(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSMTPReplyInvalidClass(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSMTPReply(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPReplyInvalidClass(NativeUInt Ident)/* overload */ : EIdSMTPReply(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPReplyInvalidClass(System::PResStringRec ResStringRec)/* overload */ : EIdSMTPReply(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPReplyInvalidClass(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSMTPReply(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPReplyInvalidClass(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSMTPReply(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSMTPReplyInvalidClass(const System::UnicodeString Msg, int AHelpContext) : EIdSMTPReply(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSMTPReplyInvalidClass(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSMTPReply(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPReplyInvalidClass(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSMTPReply(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPReplyInvalidClass(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSMTPReply(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPReplyInvalidClass(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSMTPReply(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPReplyInvalidClass(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSMTPReply(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSMTPReplyInvalidClass() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define ValidClassChars u"245"
#define ValidClassVals (System::Set<System::Byte, 0, 255>() << 0x2 << 0x4 << 0x5 )
static constexpr System::Int8 CLASS_DEF = System::Int8(0x2);
static constexpr bool AVAIL_DEF = false;
static constexpr System::Int8 NODETAILS = System::Int8(0x0);
static constexpr System::WideChar PARTSEP = (System::WideChar)(0x2e);
#define Id_EHR_USE_STARTTLS u"5.7.0"
#define Id_EHR_GENERIC_OK u"2.0.0"
#define Id_EHR_GENERIC_TRANS u"4.0.0"
#define Id_EHR_GENERIC_PERM u"5.0.0"
#define Id_EHR_MSG_OTH_OK u"2.1.0"
#define Id_EHR_MSG_OTH_TRANS u"4.1.0"
#define Id_EHR_MSG_OTH_PERM u"5.1.0"
#define Id_EHR_MSG_BAD_DEST u"5.1.1"
#define Id_EHR_MSG_BAD_DEST_SYST u"5.1.2"
#define Id_EHR_MSG_BAD_DEST_SYNTAX u"5.1.3"
#define Id_EHR_MSG_AMBIG_DEST u"5.1.4"
#define Id_EHR_MSG_VALID_DEST u"2.1.5"
#define Id_EHR_MSG_DEST_MOVED_NOFORWARD u"2.1.6"
#define Id_EHR_MSG_SENDER_BOX_SYNTAX u"5.1.7"
#define Id_EHR_MSG_BAD_SENDER_ADDR u"5.1.8"
#define Id_EHR_MB_OTHER_STATUS_OK u"2.2.0"
#define Id_EHR_MB_OTHER_STATUS_TRANS u"4.2.0"
#define Id_EHR_MB_OTHER_STATUS_PERM u"5.2.0"
#define Id_EHR_MB_DISABLED_TEMP u"4.2.1"
#define Id_EHR_MB_DISABLED_PERM u"5.2.1"
#define Id_EHR_MB_FULL u"4.2.2"
#define Id_EHR_MB_MSG_LEN_LIMIT u"5.2.3"
#define Id_EHR_MB_ML_EXPAN_TEMP u"4.2.4"
#define Id_EHR_MB_ML_EXPAN_PERM u"5.2.4"
#define Id_EHR_MD_OTHER_OK u"2.3.0"
#define Id_EHR_MD_OTHER_TRANS u"4.3.0"
#define Id_EHR_MD_OTHER_PERM u"5.3.0"
#define Id_EHR_MD_MAIL_SYSTEM_FULL u"4.3.1"
#define Id_EHR_MD_NOT_EXCEPTING_TRANS u"4.3.2"
#define Id_EHR_MD_NOT_EXCEPTING_PERM u"5.3.2"
#define Id_EHR_MD_NOT_CAPABLE_FEAT_TRANS u"4.3.3"
#define Id_EHR_MD_NOT_CAPABLE_FEAT_PERM u"5.3.3"
#define Id_EHR_MD_TOO_BIG u"5.3.4"
#define Id_EHR_MD_INCORRECT_CONFIG_TRANS u"4.3.5"
#define Id_EHR_MD_INCORRECT_CONFIG_PERM u"5.3.5"
#define Id_EHR_NR_OTHER_OK u"2.4.0"
#define Id_EHR_NR_OTHER_TRANS u"4.4.0"
#define Id_EHR_NR_OTHER_PERM u"5.4.0"
#define Id_EHR_NR_NO_ANSWER u"4.4.1"
#define Id_EHR_NR_BAD_CONNECTION u"4.4.2"
#define Id_EHR_NR_DIR_SVR_FAILURE u"4.4.3"
#define Id_EHR_NR_UNABLE_TO_ROUTE_TRANS u"4.4.4"
#define Id_EHR_NR_UNABLE_TO_ROUTE_PERM u"5.4.4"
#define Id_EHR_NR_SYSTEM_CONGESTION u"4.4.5"
#define Id_EHR_NR_LOOP_DETECTED u"4.4.6"
#define Id_EHR_NR_DELIVERY_EXPIRED_TEMP u"4.4.7"
#define Id_EHR_NR_DELIVERY_EXPIRED_PERM u"5.4.7"
#define Id_EHR_PR_OTHER_OK u"2.5.0"
#define Id_EHR_PR_OTHER_TEMP u"4.5.0"
#define Id_EHR_PR_OTHER_PERM u"5.5.0"
#define Id_EHR_PR_INVALID_CMD u"5.5.1"
#define Id_EHR_PR_SYNTAX_ERR u"5.5.2"
#define Id_EHR_PR_TOO_MANY_RECIPIENTS_TEMP u"4.5.3"
#define Id_EHR_PR_TOO_MANY_RECIPIENTS_PERM u"5.5.3"
#define Id_EHR_PR_INVALID_CMD_ARGS u"5.5.4"
#define Id_EHR_PR_WRONG_VER_TRANS u"4.5.5"
#define Id_EHR_PR_WRONG_VER_PERM u"5.5.5"
#define Id_EHR_MED_OTHER_OK u"2.6.0"
#define Id_EHR_MED_OTHER_TRANS u"4.6.0"
#define Id_EHR_MED_OTHER_PERM u"5.6.0"
#define Id_EHR_MED_NOT_SUPPORTED u"5.6.1"
#define Id_EHR_MED_CONV_REQUIRED_PROHIB_TRANS u"4.6.2"
#define Id_EHR_MED_CONV_REQUIRED_PROHIB_PERM u"5.6.2"
#define Id_EHR_MED_CONV_REQUIRED_NOT_SUP_TRANS u"4.6.3"
#define Id_EHR_MED_CONV_REQUIRED_NOT_SUP_PERM u"5.6.3"
#define Id_EHR_MED_CONV_LOSS_WARNING u"2.6.4"
#define Id_EHR_MED_CONV_LOSS_ERROR u"5.6.4"
#define Id_EHR_MED_CONV_FAILED_TRANS u"4.6.5"
#define Id_EHR_MED_CONV_FAILED_PERM u"5.6.5"
#define Id_EHR_SEC_OTHER_OK u"2.7.0"
#define Id_EHR_SEC_OTHER_TRANS u"4.7.0"
#define Id_EHR_SEC_OTHER_PERM u"5.7.0"
#define Id_EHR_SEC_DEL_NOT_AUTH u"5.7.1"
#define Id_EHR_SEC_EXP_NOT_AUTH u"5.7.2"
#define Id_EHR_SEC_CONV_REQ_NOT_POSSIBLE u"5.7.3"
#define Id_EHR_SEC_NOT_SUPPORTED u"5.7.4"
#define Id_EHR_SEC_CRYPT_FAILURE_TRANS u"4.7.5"
#define Id_EHR_SEC_CRYPT_FAILURE_PERM u"5.7.5"
#define Id_EHR_SEC_CRYPT_ALG_NOT_SUP_TRANS u"4.7.6"
#define Id_EHR_SEC_CRYPT_ALG_NOT_SUP_PERM u"5.7.6"
#define Id_EHR_SEC_INTEGRETIY_FAILED_WARN u"2.7.7"
#define Id_EHR_SEC_INTEGRETIY_FAILED_TRANS u"4.7.7"
}	/* namespace Idreplysmtp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDREPLYSMTP)
using namespace Idreplysmtp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdreplysmtpHPP
