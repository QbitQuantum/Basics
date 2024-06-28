// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdLPR.pas' rev: 34.00 (iOS)

#ifndef IdlprHPP
#define IdlprHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdGlobal.hpp>
#include <IdException.hpp>
#include <IdTCPClient.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <IdTCPConnection.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idlpr
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdLPRControlFile;
class DELPHICLASS TIdLPR;
class DELPHICLASS EIdLPRErrorException;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdLPRFileFormat : unsigned char { ffCIF, ffDVI, ffFormattedText, ffPlot, ffControlCharText, ffDitroff, ffPostScript, ffPR, ffFORTRAM, ffTroff, ffSunRaster };

class PASCALIMPLEMENTATION TIdLPRControlFile : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	System::UnicodeString FBannerClass;
	System::UnicodeString FHostName;
	int FIndentCount;
	System::UnicodeString FJobName;
	bool FBannerPage;
	System::UnicodeString FUserName;
	int FOutputWidth;
	TIdLPRFileFormat FFileFormat;
	System::UnicodeString FTroffRomanFont;
	System::UnicodeString FTroffItalicFont;
	System::UnicodeString FTroffBoldFont;
	System::UnicodeString FTroffSpecialFont;
	bool FMailWhenPrinted;
	
public:
	__fastcall TIdLPRControlFile();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString HostName = {read=FHostName, write=FHostName};
	
__published:
	__property System::UnicodeString BannerClass = {read=FBannerClass, write=FBannerClass};
	__property int IndentCount = {read=FIndentCount, write=FIndentCount, default=0};
	__property System::UnicodeString JobName = {read=FJobName, write=FJobName};
	__property bool BannerPage = {read=FBannerPage, write=FBannerPage, default=0};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property int OutputWidth = {read=FOutputWidth, write=FOutputWidth, default=0};
	__property TIdLPRFileFormat FileFormat = {read=FFileFormat, write=FFileFormat, default=4};
	__property System::UnicodeString TroffRomanFont = {read=FTroffRomanFont, write=FTroffRomanFont};
	__property System::UnicodeString TroffItalicFont = {read=FTroffItalicFont, write=FTroffItalicFont};
	__property System::UnicodeString TroffBoldFont = {read=FTroffBoldFont, write=FTroffBoldFont};
	__property System::UnicodeString TroffSpecialFont = {read=FTroffSpecialFont, write=FTroffSpecialFont};
	__property bool MailWhenPrinted = {read=FMailWhenPrinted, write=FMailWhenPrinted, default=0};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TIdLPRControlFile() { }
	
};


enum DECLSPEC_DENUM TIdLPRStatus : unsigned char { psPrinting, psJobCompleted, psError, psGettingQueueState, psGotQueueState, psDeletingJobs, psJobsDeleted, psPrintingWaitingJobs, psPrintedWaitingJobs };

typedef void __fastcall (__closure *TIdLPRStatusEvent)(System::TObject* ASender, const TIdLPRStatus AStatus, const System::UnicodeString AStatusText);

class PASCALIMPLEMENTATION TIdLPR : public Idtcpclient::TIdTCPClientCustom
{
	typedef Idtcpclient::TIdTCPClientCustom inherited;
	
protected:
	TIdLPRStatusEvent FOnLPRStatus;
	System::UnicodeString FQueue;
	int FJobId;
	TIdLPRControlFile* FControlFile;
	void __fastcall DoOnLPRStatus(const TIdLPRStatus AStatus, const System::UnicodeString AStatusText);
	void __fastcall SeTIdLPRControlFile(TIdLPRControlFile* const Value);
	void __fastcall CheckReply();
	System::UnicodeString __fastcall GetJobId();
	void __fastcall SetJobId(const System::UnicodeString Value);
	void __fastcall InternalPrint(System::Classes::TStream* Data);
	System::UnicodeString __fastcall GetControlData();
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdLPR(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TIdLPR();
	virtual void __fastcall Connect()/* overload */;
	void __fastcall Print(const System::UnicodeString AText)/* overload */;
	void __fastcall Print(const Idglobal::TIdBytes ABuffer)/* overload */;
	void __fastcall PrintFile(const System::UnicodeString AFileName);
	System::UnicodeString __fastcall GetQueueState(const bool AShortFormat = false, const System::UnicodeString AList = System::UnicodeString());
	void __fastcall PrintWaitingJobs();
	void __fastcall RemoveJobList(const System::UnicodeString AList, const bool AAsRoot = false);
	__property System::UnicodeString JobId = {read=GetJobId, write=SetJobId};
	
__published:
	__property System::UnicodeString Queue = {read=FQueue, write=FQueue};
	__property TIdLPRControlFile* ControlFile = {read=FControlFile, write=SeTIdLPRControlFile};
	__property Host = {default=0};
	__property Port = {default=515};
	__property TIdLPRStatusEvent OnLPRStatus = {read=FOnLPRStatus, write=FOnLPRStatus};
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdLPR()/* overload */ : Idtcpclient::TIdTCPClientCustom() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Connect(const System::UnicodeString AHost){ Idtcpclient::TIdTCPClientCustom::Connect(AHost); }
	inline void __fastcall  Connect(const System::UnicodeString AHost, const System::Word APort){ Idtcpclient::TIdTCPClientCustom::Connect(AHost, APort); }
	
};


class PASCALIMPLEMENTATION EIdLPRErrorException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdLPRErrorException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdLPRErrorException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdLPRErrorException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdLPRErrorException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdLPRErrorException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdLPRErrorException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdLPRErrorException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdLPRErrorException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdLPRErrorException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdLPRErrorException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdLPRErrorException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdLPRErrorException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdLPRErrorException() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const TIdLPRFileFormat DEF_FILEFORMAT = (TIdLPRFileFormat)(4);
static constexpr System::Int8 DEF_INDENTCOUNT = System::Int8(0x0);
static constexpr bool DEF_BANNERPAGE = false;
static constexpr System::Int8 DEF_OUTPUTWIDTH = System::Int8(0x0);
static constexpr bool DEF_MAILWHENPRINTED = false;
}	/* namespace Idlpr */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDLPR)
using namespace Idlpr;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdlprHPP
