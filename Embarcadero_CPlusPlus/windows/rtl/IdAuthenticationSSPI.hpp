// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdAuthenticationSSPI.pas' rev: 34.00 (Windows)

#ifndef IdauthenticationsspiHPP
#define IdauthenticationsspiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdGlobal.hpp>
#include <IdAuthentication.hpp>
#include <IdCoder.hpp>
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <IdSSPI.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "IdAuthenticationSSPI"

namespace Idauthenticationsspi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ESSPIException;
class DELPHICLASS ESSPIInterfaceInitFailed;
class DELPHICLASS TSSPIInterface;
class DELPHICLASS TSSPIPackage;
class DELPHICLASS TCustomSSPIPackage;
class DELPHICLASS TSSPINTLMPackage;
class DELPHICLASS TSSPICredentials;
class DELPHICLASS TSSPIWinNTCredentials;
class DELPHICLASS TSSPIContext;
class DELPHICLASS TCustomSSPIConnectionContext;
class DELPHICLASS TSSPIClientConnectionContext;
class DELPHICLASS TIndySSPINTLMClient;
class DELPHICLASS TIdSSPINTLMAuthentication;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ESSPIException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	__fastcall ESSPIException(const int AErrorNo, const System::UnicodeString AFailedFuncName);
	__classmethod System::UnicodeString __fastcall GetErrorMessageByNo(unsigned AErrorNo);
public:
	/* Exception.Create */ inline __fastcall ESSPIException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESSPIException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESSPIException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESSPIException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESSPIException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESSPIException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESSPIException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESSPIException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESSPIException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESSPIException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESSPIException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESSPIException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESSPIException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ESSPIInterfaceInitFailed : public ESSPIException
{
	typedef ESSPIException inherited;
	
public:
	/* ESSPIException.CreateError */ inline __fastcall ESSPIInterfaceInitFailed(const int AErrorNo, const System::UnicodeString AFailedFuncName) : ESSPIException(AErrorNo, AFailedFuncName) { }
	
public:
	/* Exception.Create */ inline __fastcall ESSPIInterfaceInitFailed(const System::UnicodeString Msg) : ESSPIException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESSPIInterfaceInitFailed(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ESSPIException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESSPIInterfaceInitFailed(NativeUInt Ident)/* overload */ : ESSPIException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESSPIInterfaceInitFailed(System::PResStringRec ResStringRec)/* overload */ : ESSPIException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESSPIInterfaceInitFailed(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ESSPIException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESSPIInterfaceInitFailed(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ESSPIException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESSPIInterfaceInitFailed(const System::UnicodeString Msg, int AHelpContext) : ESSPIException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESSPIInterfaceInitFailed(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ESSPIException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESSPIInterfaceInitFailed(NativeUInt Ident, int AHelpContext)/* overload */ : ESSPIException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESSPIInterfaceInitFailed(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ESSPIException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESSPIInterfaceInitFailed(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESSPIException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESSPIInterfaceInitFailed(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESSPIException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESSPIInterfaceInitFailed() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSSPIInterface : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	bool fLoadPending;
	bool fIsAvailable;
	SecurityFunctionTableW *fPFunctionTable;
	NativeUInt fDLLHandle;
	void __fastcall ReleaseFunctionTable();
	void __fastcall CheckAvailable();
	SecurityFunctionTableW __fastcall GetFunctionTable();
	
public:
	__classmethod void __fastcall RaiseIfError(int aStatus, const System::UnicodeString aFunctionName);
	bool __fastcall IsAvailable();
	__property SecurityFunctionTableW FunctionTable = {read=GetFunctionTable};
	__fastcall TSSPIInterface();
	__fastcall virtual ~TSSPIInterface();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSSPIPackage : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	SecPkgInfoW *fPSecPkginfo;
	PSecPkgInfoW __fastcall GetPSecPkgInfo();
	unsigned __fastcall GetMaxToken();
	System::UnicodeString __fastcall GetName();
	
public:
	__property unsigned MaxToken = {read=GetMaxToken, nodefault};
	__property System::UnicodeString Name = {read=GetName};
	__fastcall TSSPIPackage(PSecPkgInfoW aPSecPkginfo);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSSPIPackage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCustomSSPIPackage : public TSSPIPackage
{
	typedef TSSPIPackage inherited;
	
private:
	SecPkgInfoW *fInfo;
	
public:
	__fastcall TCustomSSPIPackage(const System::UnicodeString aPkgName);
	__fastcall virtual ~TCustomSSPIPackage();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSSPINTLMPackage : public TCustomSSPIPackage
{
	typedef TCustomSSPIPackage inherited;
	
public:
	__fastcall TSSPINTLMPackage();
public:
	/* TCustomSSPIPackage.Destroy */ inline __fastcall virtual ~TSSPINTLMPackage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TSSPICredentialsUse : unsigned char { scuInBound, scuOutBound, scuBoth };

class PASCALIMPLEMENTATION TSSPICredentials : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSSPIPackage* fPackage;
	SecHandle fHandle;
	TSSPICredentialsUse fUse;
	bool fAcquired;
	_LARGE_INTEGER fExpiry;
	PSecHandle __fastcall GetHandle();
	void __fastcall SetUse(TSSPICredentialsUse aValue);
	
protected:
	void __fastcall CheckAcquired();
	void __fastcall CheckNotAcquired();
	void __fastcall DoAcquire(System::WideChar * pszPrincipal, void * pvLogonId, void * pAuthData);
	virtual void __fastcall DoRelease();
	
public:
	void __fastcall Release();
	__property TSSPIPackage* Package = {read=fPackage};
	__property PSecHandle Handle = {read=GetHandle};
	__property TSSPICredentialsUse Use = {read=fUse, write=SetUse, nodefault};
	__property bool Acquired = {read=fAcquired, nodefault};
	__fastcall TSSPICredentials(TSSPIPackage* aPackage);
	__fastcall virtual ~TSSPICredentials();
};


class PASCALIMPLEMENTATION TSSPIWinNTCredentials : public TSSPICredentials
{
	typedef TSSPICredentials inherited;
	
public:
	void __fastcall Acquire(TSSPICredentialsUse aUse)/* overload */;
	void __fastcall Acquire(TSSPICredentialsUse aUse, const System::UnicodeString aDomain, const System::UnicodeString aUserName, const System::UnicodeString aPassword)/* overload */;
public:
	/* TSSPICredentials.Create */ inline __fastcall TSSPIWinNTCredentials(TSSPIPackage* aPackage) : TSSPICredentials(aPackage) { }
	/* TSSPICredentials.Destroy */ inline __fastcall virtual ~TSSPIWinNTCredentials() { }
	
};


class PASCALIMPLEMENTATION TSSPIContext : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TSSPICredentials* fCredentials;
	SecHandle fHandle;
	bool fHasHandle;
	_LARGE_INTEGER fExpiry;
	PSecHandle __fastcall GetHandle();
	_LARGE_INTEGER __fastcall GetExpiry();
	void __fastcall UpdateHasContextAndCheckForError(const int aFuncResult, const System::UnicodeString aFuncName, const int *aErrorsToIgnore, const int aErrorsToIgnore_High);
	
protected:
	void __fastcall CheckHasHandle();
	void __fastcall CheckCredentials();
	int __fastcall DoInitialize(const System::UnicodeString aTokenSourceName, SecBufferDesc &aIn, SecBufferDesc &aOut, const int *errorsToIgnore, const int errorsToIgnore_High);
	virtual void __fastcall DoRelease();
	virtual unsigned __fastcall GetRequestedFlags() = 0 ;
	virtual void __fastcall SetEstablishedFlags(unsigned aFlags) = 0 ;
	virtual bool __fastcall GetAuthenticated() = 0 ;
	__property bool HasHandle = {read=fHasHandle, nodefault};
	
public:
	void __fastcall Release();
	__property TSSPICredentials* Credentials = {read=fCredentials};
	__property PSecHandle Handle = {read=GetHandle};
	__property bool Authenticated = {read=GetAuthenticated, nodefault};
	__property _LARGE_INTEGER Expiry = {read=GetExpiry};
	__fastcall TSSPIContext(TSSPICredentials* aCredentials);
	__fastcall virtual ~TSSPIContext();
};


class PASCALIMPLEMENTATION TCustomSSPIConnectionContext : public TSSPIContext
{
	typedef TSSPIContext inherited;
	
private:
	int fStatus;
	SecBufferDesc fOutBuffDesc;
	SecBufferDesc fInBuffDesc;
	SecBuffer fInBuff;
	
protected:
	virtual void __fastcall DoRelease();
	virtual bool __fastcall GetAuthenticated();
	virtual int __fastcall DoUpdateAndGenerateReply(SecBufferDesc &aIn, SecBufferDesc &aOut, const int *aErrorsToIgnore, const int aErrorsToIgnore_High) = 0 ;
	
public:
	__fastcall TCustomSSPIConnectionContext(TSSPICredentials* ACredentials);
	bool __fastcall UpdateAndGenerateReply(const Idglobal::TIdBytes aFromPeerToken, Idglobal::TIdBytes &aToPeerToken);
public:
	/* TSSPIContext.Destroy */ inline __fastcall virtual ~TCustomSSPIConnectionContext() { }
	
};


class PASCALIMPLEMENTATION TSSPIClientConnectionContext : public TCustomSSPIConnectionContext
{
	typedef TCustomSSPIConnectionContext inherited;
	
private:
	System::UnicodeString fTargetName;
	unsigned fReqReguested;
	unsigned fReqEstablished;
	
protected:
	virtual unsigned __fastcall GetRequestedFlags();
	virtual void __fastcall SetEstablishedFlags(unsigned aFlags);
	virtual int __fastcall DoUpdateAndGenerateReply(SecBufferDesc &aIn, SecBufferDesc &aOut, const int *aErrorsToIgnore, const int aErrorsToIgnore_High);
	
public:
	bool __fastcall GenerateInitialChallenge(const System::UnicodeString aTargetName, Idglobal::TIdBytes &aToPeerToken);
	__fastcall TSSPIClientConnectionContext(TSSPICredentials* aCredentials);
public:
	/* TSSPIContext.Destroy */ inline __fastcall virtual ~TSSPIClientConnectionContext() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIndySSPINTLMClient : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	TSSPINTLMPackage* fNTLMPackage;
	TSSPIWinNTCredentials* fCredentials;
	TSSPIClientConnectionContext* fContext;
	
public:
	void __fastcall SetCredentials(const System::UnicodeString aDomain, const System::UnicodeString aUserName, const System::UnicodeString aPassword);
	void __fastcall SetCredentialsAsCurrentUser();
	Idglobal::TIdBytes __fastcall InitAndBuildType1Message();
	Idglobal::TIdBytes __fastcall UpdateAndBuildType3Message(const Idglobal::TIdBytes aServerType2Message);
	__fastcall TIndySSPINTLMClient();
	__fastcall virtual ~TIndySSPINTLMClient();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdSSPINTLMAuthentication : public Idauthentication::TIdAuthentication
{
	typedef Idauthentication::TIdAuthentication inherited;
	
protected:
	System::UnicodeString FNTLMInfo;
	TIndySSPINTLMClient* FSSPIClient;
	void __fastcall SetDomain(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetDomain();
	virtual void __fastcall SetUserName(const System::UnicodeString Value);
	virtual int __fastcall GetSteps();
	virtual Idauthentication::TIdAuthWhatsNext __fastcall DoNext();
	
public:
	__fastcall virtual TIdSSPINTLMAuthentication();
	__fastcall virtual ~TIdSSPINTLMAuthentication();
	virtual System::UnicodeString __fastcall Authentication();
	virtual bool __fastcall KeepAlive();
	__property System::UnicodeString Domain = {read=GetDomain, write=SetDomain};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idauthenticationsspi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDAUTHENTICATIONSSPI)
using namespace Idauthenticationsspi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdauthenticationsspiHPP
