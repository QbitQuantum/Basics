// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBInstall.pas' rev: 34.00 (Android)

#ifndef Ibx_IbinstallHPP
#define Ibx_IbinstallHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <IBX.IB.hpp>
#include <IBX.IBInstallHeader.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibinstall
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIBInstall;
class DELPHICLASS EIBInstallError;
class DELPHICLASS EIBInstallerError;
class DELPHICLASS TInstallOptions;
class DELPHICLASS TIBSetup;
class DELPHICLASS TIBInstall;
class DELPHICLASS TIBUnInstall;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
typedef int TIscError;
#else /* __aarch64__ */
typedef long TIscError;
#endif /* __aarch64__ */

enum DECLSPEC_DENUM TIBInstallerError : unsigned char { ieSuccess, ieDelphiException, ieNoOptionsSet, ieNoDestinationDirectory, ieNosourceDirectory, ieNoUninstallFile, ieOptionNeedsClient, ieOptionNeedsServer, ieInvalidOption, ieInvalidOnErrorResult, ieInvalidOnStatusResult };

enum DECLSPEC_DENUM TMainOption : unsigned char { moServer, moClient, moConServer, moGuiTools, moDocumentation, moDevelopment };

enum DECLSPEC_DENUM TExamplesOption : unsigned char { exDB, exAPI };

enum DECLSPEC_DENUM TCmdOption : unsigned char { cmDBMgmt, cmDBQuery, cmUsrMgmt };

enum DECLSPEC_DENUM TConnectivityOption : unsigned char { cnODBC, cnOLEDB, cnJDBC };

typedef System::Set<TMainOption, TMainOption::moServer, TMainOption::moDevelopment> TMainOptions;

typedef System::Set<TExamplesOption, TExamplesOption::exDB, TExamplesOption::exAPI> TExamplesOptions;

typedef System::Set<TCmdOption, TCmdOption::cmDBMgmt, TCmdOption::cmUsrMgmt> TCmdOptions;

typedef System::Set<TConnectivityOption, TConnectivityOption::cnODBC, TConnectivityOption::cnJDBC> TConnectivityOptions;

enum DECLSPEC_DENUM TErrorResult : unsigned char { erAbort, erContinue, erRetry };

enum DECLSPEC_DENUM TStatusResult : unsigned char { srAbort, srContinue };

enum DECLSPEC_DENUM TWarningResult : unsigned char { wrAbort, wrContinue };

typedef TStatusResult __fastcall (__closure *TIBSetupOnStatus)(System::TObject* Sender, System::UnicodeString StatusComment);

#ifndef __aarch64__
typedef TWarningResult __fastcall (__closure *TIBSetupOnWarning)(System::TObject* Sender, int WarningCode, System::UnicodeString WarningMessage);
#else /* __aarch64__ */
typedef TWarningResult __fastcall (__closure *TIBSetupOnWarning)(System::TObject* Sender, long WarningCode, System::UnicodeString WarningMessage);
#endif /* __aarch64__ */

#ifndef __aarch64__
typedef TErrorResult __fastcall (__closure *TIBSetupOnError)(System::TObject* Sender, int IscCode, System::UnicodeString ErrorMessage, System::UnicodeString ErrorComment);
#else /* __aarch64__ */
typedef TErrorResult __fastcall (__closure *TIBSetupOnError)(System::TObject* Sender, long IscCode, System::UnicodeString ErrorMessage, System::UnicodeString ErrorComment);
#endif /* __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIBInstall : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
private:
#ifndef __aarch64__
	int FIscError;
#else /* __aarch64__ */
	long FIscError;
#endif /* __aarch64__ */
	TIBInstallerError FInstallerError;
	
public:
#ifndef __aarch64__
	__fastcall virtual EIBInstall(int IscCode, System::UnicodeString IscMessage)/* overload */;
#else /* __aarch64__ */
	__fastcall virtual EIBInstall(long IscCode, System::UnicodeString IscMessage)/* overload */;
#endif /* __aarch64__ */
	__fastcall virtual EIBInstall(TIBInstallerError ECode, System::UnicodeString EMessage)/* overload */;
#ifndef __aarch64__
	__property int InstallError = {read=FIscError, nodefault};
#else /* __aarch64__ */
	__property long InstallError = {read=FIscError};
#endif /* __aarch64__ */
	__property TIBInstallerError InstallerError = {read=FInstallerError, nodefault};
public:
	/* Exception.CreateFmt */ inline __fastcall EIBInstall(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIBInstall(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIBInstall(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBInstall(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBInstall(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIBInstall(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIBInstall(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBInstall(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBInstall(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBInstall(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBInstall(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIBInstall() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIBInstallError : public EIBInstall
{
	typedef EIBInstall inherited;
	
public:
#ifndef __aarch64__
	/* EIBInstall.Create */ inline __fastcall virtual EIBInstallError(int IscCode, System::UnicodeString IscMessage)/* overload */ : EIBInstall(IscCode, IscMessage) { }
#else /* __aarch64__ */
	/* EIBInstall.Create */ inline __fastcall virtual EIBInstallError(long IscCode, System::UnicodeString IscMessage)/* overload */ : EIBInstall(IscCode, IscMessage) { }
#endif /* __aarch64__ */
	/* EIBInstall.Create */ inline __fastcall virtual EIBInstallError(TIBInstallerError ECode, System::UnicodeString EMessage)/* overload */ : EIBInstall(ECode, EMessage) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIBInstallError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIBInstall(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIBInstallError(NativeUInt Ident)/* overload */ : EIBInstall(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIBInstallError(System::PResStringRec ResStringRec)/* overload */ : EIBInstall(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBInstallError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBInstall(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBInstallError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBInstall(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIBInstallError(const System::UnicodeString Msg, int AHelpContext) : EIBInstall(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIBInstallError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIBInstall(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBInstallError(NativeUInt Ident, int AHelpContext)/* overload */ : EIBInstall(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBInstallError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIBInstall(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBInstallError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBInstall(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBInstallError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBInstall(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIBInstallError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIBInstallerError : public EIBInstall
{
	typedef EIBInstall inherited;
	
public:
#ifndef __aarch64__
	/* EIBInstall.Create */ inline __fastcall virtual EIBInstallerError(int IscCode, System::UnicodeString IscMessage)/* overload */ : EIBInstall(IscCode, IscMessage) { }
#else /* __aarch64__ */
	/* EIBInstall.Create */ inline __fastcall virtual EIBInstallerError(long IscCode, System::UnicodeString IscMessage)/* overload */ : EIBInstall(IscCode, IscMessage) { }
#endif /* __aarch64__ */
	/* EIBInstall.Create */ inline __fastcall virtual EIBInstallerError(TIBInstallerError ECode, System::UnicodeString EMessage)/* overload */ : EIBInstall(ECode, EMessage) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIBInstallerError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIBInstall(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIBInstallerError(NativeUInt Ident)/* overload */ : EIBInstall(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIBInstallerError(System::PResStringRec ResStringRec)/* overload */ : EIBInstall(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBInstallerError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBInstall(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBInstallerError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBInstall(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIBInstallerError(const System::UnicodeString Msg, int AHelpContext) : EIBInstall(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIBInstallerError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIBInstall(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBInstallerError(NativeUInt Ident, int AHelpContext)/* overload */ : EIBInstall(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBInstallerError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIBInstall(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBInstallerError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBInstall(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBInstallerError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBInstall(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIBInstallerError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TInstallOptions : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TMainOptions FMainComponents;
	TExamplesOptions FExamples;
	TCmdOptions FCmdLineTools;
	TConnectivityOptions FConnectivityClients;
	
__published:
	__property TMainOptions MainComponents = {read=FMainComponents, write=FMainComponents, nodefault};
	__property TCmdOptions CmdLineTools = {read=FCmdLineTools, write=FCmdLineTools, nodefault};
	__property TConnectivityOptions ConnectivityClients = {read=FConnectivityClients, write=FConnectivityClients, nodefault};
	__property TExamplesOptions Examples = {read=FExamples, write=FExamples, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TInstallOptions() { }
	
public:
	/* TObject.Create */ inline __fastcall TInstallOptions() : System::Classes::TPersistent() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBSetup : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool FIBInstallLoaded;
	bool FRebootToComplete;
	int FProgress;
	System::UnicodeString FMsgFilePath;
	TIBSetupOnStatus FOnStatusChange;
	void *FStatusContext;
	TIBSetupOnError FOnError;
	void *FErrorContext;
	TIBSetupOnWarning FOnWarning;
	void __fastcall SetMsgFilePath(const System::UnicodeString Value);
	
protected:
	int __fastcall StatusInternal(int Status, const System::PByte ActionDescription);
#ifndef __aarch64__
	int __fastcall ErrorInternal(int IscCode, const System::PByte ActionDescription);
	void __fastcall Call(int IscCode);
	void __fastcall IBInstallError(int IscCode);
	System::UnicodeString __fastcall GetInstallMessage(int IscCode);
#else /* __aarch64__ */
	int __fastcall ErrorInternal(long IscCode, const System::PByte ActionDescription);
	void __fastcall Call(long IscCode);
	void __fastcall IBInstallError(long IscCode);
	System::UnicodeString __fastcall GetInstallMessage(long IscCode);
#endif /* __aarch64__ */
	
public:
	__fastcall virtual TIBSetup(System::Classes::TComponent* AOwner);
	__property bool RebootToComplete = {read=FRebootToComplete, nodefault};
	__property int Progress = {read=FProgress, nodefault};
	__property void * StatusContext = {read=FStatusContext, write=FStatusContext};
	__property void * ErrorContext = {read=FErrorContext, write=FErrorContext};
	__property System::UnicodeString MsgFilePath = {read=FMsgFilePath, write=SetMsgFilePath};
	
__published:
	__property TIBSetupOnWarning OnWarning = {read=FOnWarning, write=FOnWarning};
	__property TIBSetupOnError OnError = {read=FOnError, write=FOnError};
	__property TIBSetupOnStatus OnStatusChange = {read=FOnStatusChange, write=FOnStatusChange};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIBSetup() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBInstall : public TIBSetup
{
	typedef TIBSetup inherited;
	
private:
	System::UnicodeString FUnInstallFile;
	System::UnicodeString FSourceDir;
	System::UnicodeString FDestinationDir;
	System::UnicodeString FSuggestedDestination;
	TInstallOptions* FInstallOptions;
	void __fastcall GetOptionProperty(int InfoType, TExamplesOption Option, void * Buffer, unsigned BufferLen)/* overload */;
	void __fastcall GetOptionProperty(int InfoType, TMainOption Option, void * Buffer, unsigned BufferLen)/* overload */;
	void __fastcall GetOptionProperty(int InfoType, TConnectivityOption Option, void * Buffer, unsigned BufferLen)/* overload */;
	void __fastcall GetOptionProperty(int InfoType, TCmdOption Option, void * Buffer, unsigned BufferLen)/* overload */;
	void __fastcall InternalSetOptions(Ibx::Ibinstallheader::POPTIONS_HANDLE pHandle);
	void __fastcall SetDestination(const System::UnicodeString Value);
	void __fastcall SetSource(const System::UnicodeString Value);
	void __fastcall SetInstallOptions(TInstallOptions* const Value);
	void __fastcall SuggestDestination();
	
public:
	__fastcall virtual TIBInstall(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBInstall();
	void __fastcall InstallCheck();
	void __fastcall InstallExecute();
	System::UnicodeString __fastcall GetOptionDescription(TExamplesOption Option)/* overload */;
	System::UnicodeString __fastcall GetOptionDescription(TMainOption Option)/* overload */;
	System::UnicodeString __fastcall GetOptionDescription(TConnectivityOption Option)/* overload */;
	System::UnicodeString __fastcall GetOptionDescription(TCmdOption Option)/* overload */;
	System::UnicodeString __fastcall GetOptionName(TExamplesOption Option)/* overload */;
	System::UnicodeString __fastcall GetOptionName(TMainOption Option)/* overload */;
	System::UnicodeString __fastcall GetOptionName(TConnectivityOption Option)/* overload */;
	System::UnicodeString __fastcall GetOptionName(TCmdOption Option)/* overload */;
#ifndef __aarch64__
	unsigned __fastcall GetOptionSpaceRequired(TExamplesOption Option)/* overload */;
	unsigned __fastcall GetOptionSpaceRequired(TMainOption Option)/* overload */;
	unsigned __fastcall GetOptionSpaceRequired(TConnectivityOption Option)/* overload */;
	unsigned __fastcall GetOptionSpaceRequired(TCmdOption Option)/* overload */;
#else /* __aarch64__ */
	unsigned long __fastcall GetOptionSpaceRequired(TExamplesOption Option)/* overload */;
	unsigned long __fastcall GetOptionSpaceRequired(TMainOption Option)/* overload */;
	unsigned long __fastcall GetOptionSpaceRequired(TConnectivityOption Option)/* overload */;
	unsigned long __fastcall GetOptionSpaceRequired(TCmdOption Option)/* overload */;
#endif /* __aarch64__ */
	__property System::UnicodeString UnInstallFile = {read=FUnInstallFile};
	__property System::UnicodeString SuggestedDestination = {read=FSuggestedDestination};
	
__published:
	__property System::UnicodeString SourceDirectory = {read=FSourceDir, write=SetSource};
	__property System::UnicodeString DestinationDirectory = {read=FDestinationDir, write=SetDestination};
	__property TInstallOptions* InstallOptions = {read=FInstallOptions, write=SetInstallOptions};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBUnInstall : public TIBSetup
{
	typedef TIBSetup inherited;
	
private:
	System::UnicodeString FUnInstallFile;
	
public:
	void __fastcall UnInstallCheck();
	void __fastcall UnInstallExecute();
	__property System::UnicodeString UnInstallFile = {read=FUnInstallFile, write=FUnInstallFile};
public:
	/* TIBSetup.Create */ inline __fastcall virtual TIBUnInstall(System::Classes::TComponent* AOwner) : TIBSetup(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIBUnInstall() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibinstall */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBINSTALL)
using namespace Ibx::Ibinstall;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbinstallHPP
