﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPServer.pas' rev: 34.00 (Android)

#ifndef IdftpserverHPP
#define IdftpserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdCommandHandlers.hpp>
#include <IdGlobal.hpp>
#include <IdContext.hpp>
#include <IdException.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdFTPBaseFileSystem.hpp>
#include <IdFTPCommon.hpp>
#include <IdBaseComponent.hpp>
#include <IdFTPList.hpp>
#include <IdFTPListOutput.hpp>
#include <IdFTPServerContextBase.hpp>
#include <IdReply.hpp>
#include <IdReplyFTP.hpp>
#include <IdReplyRFC.hpp>
#include <IdScheduler.hpp>
#include <IdServerIOHandler.hpp>
#include <IdTCPConnection.hpp>
#include <IdCmdTCPServer.hpp>
#include <IdTCPServer.hpp>
#include <IdThread.hpp>
#include <IdUserAccounts.hpp>
#include <IdYarn.hpp>
#include <IdZLibCompressorBase.hpp>
#include <System.SysUtils.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTask.hpp>
#include <IdThreadSafe.hpp>
#include <IdComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idftpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdFTPServerException;
class DELPHICLASS EIdFTPServerNoOnListDirectory;
class DELPHICLASS EIdFTPImplicitTLSRequiresSSL;
class DELPHICLASS EIdFTPBoundPortMaxGreater;
class DELPHICLASS EIdFTPBoundPortMinLess;
class DELPHICLASS EIdFTPCannotBeNegative;
class DELPHICLASS TIdFTPSecurityOptions;
class DELPHICLASS TIdDataChannel;
class DELPHICLASS TIdFTPServerContext;
class DELPHICLASS TIdFTPServer;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdFTPDirFormat : unsigned char { ftpdfDOS, ftpdfUnix, ftpdfEPLF, ftpdfCustom, ftpdfOSDependent };

enum DECLSPEC_DENUM TIdFTPPathProcessing : unsigned char { ftppDOS, ftppUnix, ftpOSDependent, ftppCustom };

enum DECLSPEC_DENUM TIdFTPOperation : unsigned char { ftpRetr, ftpStor };

enum DECLSPEC_DENUM TIdMLSDAttr : unsigned char { mlsdUniqueID, mlsdPerms, mlsdUnixModes, mlsdUnixOwner, mlsdUnixGroup, mlsdFileCreationTime, mlsdFileLastAccessTime, mlsdWin32Attributes, mlsdWin32DriveType, mlstWin32DriveLabel };

typedef System::Set<TIdMLSDAttr, TIdMLSDAttr::mlsdUniqueID, TIdMLSDAttr::mlstWin32DriveLabel> TIdMLSDAttrs;

typedef System::StaticArray<System::UnicodeString, 3> Idftpserver__1;

typedef void __fastcall (__closure *TIdOnMLST)(TIdFTPServerContext* ASender, const System::UnicodeString APath, Idftplistoutput::TIdFTPListOutput* ADirectoryListing);

typedef void __fastcall (__closure *TOnDataPortBind)(TIdFTPServerContext* ASender);

typedef void __fastcall (__closure *TOnSetATTRIB)(TIdFTPServerContext* ASender, unsigned &VAttr, const System::UnicodeString AFileName, bool &VAUth);

typedef void __fastcall (__closure *TOnSiteUMASK)(TIdFTPServerContext* ASender, int &VUMASK, bool &VAUth);

typedef void __fastcall (__closure *TOnSiteCHMOD)(TIdFTPServerContext* ASender, int &APermissions, const System::UnicodeString AFileName, bool &VAUth);

typedef void __fastcall (__closure *TOnSiteCHOWN)(TIdFTPServerContext* ASender, System::UnicodeString &AOwner, System::UnicodeString &AGroup, const System::UnicodeString AFileName, bool &VAUth);

typedef void __fastcall (__closure *TOnSiteCHGRP)(TIdFTPServerContext* ASender, System::UnicodeString &AGroup, const System::UnicodeString AFileName, bool &VAUth);

typedef void __fastcall (__closure *TOnCustomPathProcess)(TIdFTPServerContext* ASender, System::UnicodeString &VPath);

typedef void __fastcall (__closure *TOnFTPUserLoginEvent)(TIdFTPServerContext* ASender, const System::UnicodeString AUsername, const System::UnicodeString APassword, bool &AAuthenticated);

typedef void __fastcall (__closure *TOnFTPUserAccountEvent)(TIdFTPServerContext* ASender, const System::UnicodeString AUsername, const System::UnicodeString APassword, const System::UnicodeString AAcount, bool &AAuthenticated);

typedef void __fastcall (__closure *TOnAfterUserLoginEvent)(TIdFTPServerContext* ASender);

typedef void __fastcall (__closure *TOnDirectoryEvent)(TIdFTPServerContext* ASender, System::UnicodeString &VDirectory);

typedef void __fastcall (__closure *TOnGetFileSizeEvent)(TIdFTPServerContext* ASender, const System::UnicodeString AFilename, __int64 &VFileSize);

typedef void __fastcall (__closure *TOnGetFileDateEvent)(TIdFTPServerContext* ASender, const System::UnicodeString AFilename, System::TDateTime &VFileDate);

typedef void __fastcall (__closure *TOnListDirectoryEvent)(TIdFTPServerContext* ASender, const System::UnicodeString APath, Idftplistoutput::TIdFTPListOutput* ADirectoryListing, const System::UnicodeString ACmd, const System::UnicodeString ASwitches);

typedef void __fastcall (__closure *TOnCustomListDirectoryEvent)(TIdFTPServerContext* ASender, const System::UnicodeString APath, System::Classes::TStrings* ADirectoryListing, const System::UnicodeString ACmd, const System::UnicodeString ASwitches);

typedef void __fastcall (__closure *TOnFileEvent)(TIdFTPServerContext* ASender, const System::UnicodeString APathName);

typedef void __fastcall (__closure *TOnCheckFileEvent)(TIdFTPServerContext* ASender, const System::UnicodeString APathName, bool &VExist);

typedef void __fastcall (__closure *TOnRenameFileEvent)(TIdFTPServerContext* ASender, const System::UnicodeString ARenameFromFile, const System::UnicodeString ARenameToFile);

typedef void __fastcall (__closure *TOnRetrieveFileEvent)(TIdFTPServerContext* ASender, const System::UnicodeString AFileName, System::Classes::TStream* &VStream);

typedef void __fastcall (__closure *TOnStoreFileEvent)(TIdFTPServerContext* ASender, const System::UnicodeString AFileName, bool AAppend, System::Classes::TStream* &VStream);

typedef void __fastcall (__closure *TOnCombineFiles)(TIdFTPServerContext* ASender, const System::UnicodeString ATargetFileName, System::Classes::TStrings* AParts);

typedef void __fastcall (__closure *TOnCheckSumFile)(TIdFTPServerContext* ASender, const System::UnicodeString AFileName, System::Classes::TStream* &VStream);

typedef void __fastcall (__closure *TOnCacheChecksum)(TIdFTPServerContext* ASender, const System::UnicodeString AFileName, System::UnicodeString &VCheckSum);

typedef void __fastcall (__closure *TOnVerifyChecksum)(TIdFTPServerContext* ASender, const System::UnicodeString AFileName, const System::UnicodeString ACheckSum);

typedef void __fastcall (__closure *TOnSetFileDateEvent)(TIdFTPServerContext* ASender, const System::UnicodeString AFileName, System::TDateTime &AFileTime);

typedef void __fastcall (__closure *TOnHostCheck)(TIdFTPServerContext* ASender, const System::UnicodeString AHost, bool &VAccepted);

typedef void __fastcall (__closure *TOnSiteUTIME)(TIdFTPServerContext* ASender, const System::UnicodeString AFileName, System::TDateTime &VLastAccessTime, System::TDateTime &VLastModTime, System::TDateTime &VCreateDate, bool &VAUth);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdFTPServerException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPServerException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPServerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPServerException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPServerException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPServerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPServerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPServerException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPServerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPServerException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPServerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPServerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPServerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPServerException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdFTPServerNoOnListDirectory : public EIdFTPServerException
{
	typedef EIdFTPServerException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPServerNoOnListDirectory(const System::UnicodeString AMsg)/* overload */ : EIdFTPServerException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPServerNoOnListDirectory(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPServerException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPServerNoOnListDirectory(NativeUInt Ident)/* overload */ : EIdFTPServerException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPServerNoOnListDirectory(System::PResStringRec ResStringRec)/* overload */ : EIdFTPServerException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPServerNoOnListDirectory(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPServerException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPServerNoOnListDirectory(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPServerException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPServerNoOnListDirectory(const System::UnicodeString Msg, int AHelpContext) : EIdFTPServerException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPServerNoOnListDirectory(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPServerException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPServerNoOnListDirectory(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPServerException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPServerNoOnListDirectory(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPServerException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPServerNoOnListDirectory(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPServerException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPServerNoOnListDirectory(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPServerException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPServerNoOnListDirectory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdFTPImplicitTLSRequiresSSL : public EIdFTPServerException
{
	typedef EIdFTPServerException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPImplicitTLSRequiresSSL(const System::UnicodeString AMsg)/* overload */ : EIdFTPServerException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPImplicitTLSRequiresSSL(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPServerException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPImplicitTLSRequiresSSL(NativeUInt Ident)/* overload */ : EIdFTPServerException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPImplicitTLSRequiresSSL(System::PResStringRec ResStringRec)/* overload */ : EIdFTPServerException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPImplicitTLSRequiresSSL(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPServerException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPImplicitTLSRequiresSSL(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPServerException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPImplicitTLSRequiresSSL(const System::UnicodeString Msg, int AHelpContext) : EIdFTPServerException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPImplicitTLSRequiresSSL(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPServerException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPImplicitTLSRequiresSSL(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPServerException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPImplicitTLSRequiresSSL(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPServerException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPImplicitTLSRequiresSSL(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPServerException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPImplicitTLSRequiresSSL(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPServerException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPImplicitTLSRequiresSSL() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdFTPBoundPortMaxGreater : public EIdFTPServerException
{
	typedef EIdFTPServerException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPBoundPortMaxGreater(const System::UnicodeString AMsg)/* overload */ : EIdFTPServerException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPBoundPortMaxGreater(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPServerException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPBoundPortMaxGreater(NativeUInt Ident)/* overload */ : EIdFTPServerException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPBoundPortMaxGreater(System::PResStringRec ResStringRec)/* overload */ : EIdFTPServerException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPBoundPortMaxGreater(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPServerException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPBoundPortMaxGreater(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPServerException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPBoundPortMaxGreater(const System::UnicodeString Msg, int AHelpContext) : EIdFTPServerException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPBoundPortMaxGreater(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPServerException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPBoundPortMaxGreater(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPServerException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPBoundPortMaxGreater(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPServerException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPBoundPortMaxGreater(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPServerException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPBoundPortMaxGreater(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPServerException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPBoundPortMaxGreater() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdFTPBoundPortMinLess : public EIdFTPServerException
{
	typedef EIdFTPServerException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPBoundPortMinLess(const System::UnicodeString AMsg)/* overload */ : EIdFTPServerException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPBoundPortMinLess(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPServerException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPBoundPortMinLess(NativeUInt Ident)/* overload */ : EIdFTPServerException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPBoundPortMinLess(System::PResStringRec ResStringRec)/* overload */ : EIdFTPServerException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPBoundPortMinLess(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPServerException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPBoundPortMinLess(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPServerException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPBoundPortMinLess(const System::UnicodeString Msg, int AHelpContext) : EIdFTPServerException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPBoundPortMinLess(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPServerException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPBoundPortMinLess(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPServerException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPBoundPortMinLess(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPServerException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPBoundPortMinLess(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPServerException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPBoundPortMinLess(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPServerException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPBoundPortMinLess() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdFTPCannotBeNegative : public EIdFTPServerException
{
	typedef EIdFTPServerException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPCannotBeNegative(const System::UnicodeString AMsg)/* overload */ : EIdFTPServerException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPCannotBeNegative(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPServerException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPCannotBeNegative(NativeUInt Ident)/* overload */ : EIdFTPServerException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPCannotBeNegative(System::PResStringRec ResStringRec)/* overload */ : EIdFTPServerException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPCannotBeNegative(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPServerException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPCannotBeNegative(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPServerException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPCannotBeNegative(const System::UnicodeString Msg, int AHelpContext) : EIdFTPServerException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPCannotBeNegative(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPServerException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPCannotBeNegative(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPServerException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPCannotBeNegative(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPServerException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPCannotBeNegative(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPServerException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPCannotBeNegative(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPServerException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPCannotBeNegative() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TIdOnClientID)(TIdFTPServerContext* ASender, const System::UnicodeString AID);

typedef void __fastcall (__closure *TIdOnFTPStatEvent)(TIdFTPServerContext* ASender, System::Classes::TStrings* AStatusInfo);

typedef void __fastcall (__closure *TIdOnBanner)(TIdFTPServerContext* ASender, Idreply::TIdReply* AGreeting);

typedef void __fastcall (__closure *TIdOnPASV)(TIdFTPServerContext* ASender, System::UnicodeString &VIP, System::Word &VPort, const Idglobal::TIdIPVersion AIPVer);

typedef void __fastcall (__closure *TIdOnPASVRange)(TIdFTPServerContext* ASender, System::UnicodeString &VIP, System::Word &VPortMin, System::Word &VPortMax, const Idglobal::TIdIPVersion AIPVer);

typedef void __fastcall (__closure *TIdOnDirSizeInfo)(TIdFTPServerContext* ASender, const System::UnicodeString APathName, bool &VIsAFile, __int64 &VSpace);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdFTPSecurityOptions : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	unsigned FPasswordAttempts;
	unsigned FInvalidPassDelay;
	bool FRequirePASVFromSameIP;
	bool FRequirePORTFromSameIP;
	bool FNoReservedRangePORT;
	bool FBlockAllPORTTransfers;
	bool FDisableSYSTCommand;
	bool FDisableSTATCommand;
	bool FPermitCCC;
	
public:
	__fastcall virtual TIdFTPSecurityOptions();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property unsigned PasswordAttempts = {read=FPasswordAttempts, write=FPasswordAttempts, default=3};
	__property unsigned InvalidPassDelay = {read=FInvalidPassDelay, write=FInvalidPassDelay, default=3000};
	__property bool RequirePASVFromSameIP = {read=FRequirePASVFromSameIP, write=FRequirePASVFromSameIP, default=1};
	__property bool RequirePORTFromSameIP = {read=FRequirePORTFromSameIP, write=FRequirePORTFromSameIP, default=1};
	__property bool NoReservedRangePORT = {read=FNoReservedRangePORT, write=FNoReservedRangePORT, default=1};
	__property bool BlockAllPORTTransfers = {read=FBlockAllPORTTransfers, write=FBlockAllPORTTransfers, default=0};
	__property bool DisableSYSTCommand = {read=FDisableSYSTCommand, write=FDisableSYSTCommand, default=0};
	__property bool DisableSTATCommand = {read=FDisableSTATCommand, write=FDisableSTATCommand, default=0};
	__property bool PermitCCC = {read=FPermitCCC, write=FPermitCCC, default=0};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TIdFTPSecurityOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdDataChannel : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	bool FNegotiateTLS;
	TIdFTPServerContext* FControlContext;
	Idtcpconnection::TIdTCPConnection* FDataChannel;
	Idreplyrfc::TIdReplyRFC* FErrorReply;
	TIdFTPOperation FFtpOperation;
	Idreplyrfc::TIdReplyRFC* FOKReply;
	Idreplyrfc::TIdReplyRFC* FReply;
	TIdFTPServer* FServer;
	bool FRequirePASVFromSameIP;
	bool FStopped;
	System::TObject* FData;
	void __fastcall SetErrorReply(Idreplyrfc::TIdReplyRFC* const AValue);
	void __fastcall SetOKReply(Idreplyrfc::TIdReplyRFC* const AValue);
	System::UnicodeString __fastcall GetPeerIP();
	System::Word __fastcall GetPeerPort();
	System::UnicodeString __fastcall GetLocalIP();
	System::Word __fastcall GetLocalPort();
	
public:
	__fastcall TIdDataChannel(bool APASV, TIdFTPServerContext* AControlContext, const bool ARequirePASVFromSameIP, TIdFTPServer* AServer);
	__fastcall virtual ~TIdDataChannel();
	void __fastcall InitOperation(const bool AConnectMode = false);
	__property System::UnicodeString PeerIP = {read=GetPeerIP};
	__property System::Word PeerPort = {read=GetPeerPort, nodefault};
	__property System::UnicodeString LocalIP = {read=GetLocalIP};
	__property System::Word LocalPort = {read=GetLocalPort, nodefault};
	__property bool Stopped = {read=FStopped, write=FStopped, nodefault};
	__property System::TObject* Data = {read=FData, write=FData};
	__property TIdFTPServer* Server = {read=FServer};
	__property Idreplyrfc::TIdReplyRFC* OKReply = {read=FOKReply, write=SetOKReply};
	__property Idreplyrfc::TIdReplyRFC* ErrorReply = {read=FErrorReply, write=SetErrorReply};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdFTPServerContext : public Idftpservercontextbase::TIdFTPServerContextBase
{
	typedef Idftpservercontextbase::TIdFTPServerContextBase inherited;
	
protected:
	unsigned FXAUTKey;
	int FRESTPos;
	TIdDataChannel* FDataChannel;
	System::UnicodeString FAuthMechanism;
	bool FCCC;
	Idftpcommon::TIdFTPTransferType FDataType;
	Idftpcommon::TIdFTPTransferMode FDataMode;
	System::Word FDataPort;
	unsigned FDataProtBufSize;
	Idftpcommon::TIdFTPDataStructure FDataStruct;
	unsigned FPasswordAttempts;
	bool FPASV;
	bool FEPSVAll;
	bool FDataPortDenied;
	Idftpcommon::TIdFTPDataPortSecurity FDataProtection;
	bool FDataPBSZCalled;
	Idftplistoutput::TIdFTPFactOutputs FMLSOpts;
	bool FSSCNOn;
	TIdFTPServer* FServer;
	TIdFTPSecurityOptions* FUserSecurity;
	int FUMask;
	bool FMSDOSMode;
	System::UnicodeString FQuitReply;
	int FZLibCompressionLevel;
	int FZLibWindowBits;
	int FZLibMemLevel;
	int FZLibStratagy;
	void __fastcall ResetZLibSettings();
	void __fastcall PortOnAfterBind(System::TObject* ASender);
	void __fastcall PortOnBeforeBind(System::TObject* ASender);
	void __fastcall SetUserSecurity(TIdFTPSecurityOptions* const Value);
	void __fastcall CreateDataChannel(bool APASV = false);
	bool __fastcall IsAuthenticated(Idcommandhandlers::TIdCommand* ASender);
	virtual void __fastcall ReInitialize();
	
public:
	__fastcall virtual TIdFTPServerContext(Idtcpconnection::TIdTCPConnection* AConnection, Idyarn::TIdYarn* AYarn, Idthreadsafe::TIdThreadSafeObjectList* AList);
	__fastcall virtual ~TIdFTPServerContext();
	void __fastcall KillDataChannel();
	__property TIdDataChannel* DataChannel = {read=FDataChannel};
	__property TIdFTPServer* Server = {read=FServer, write=FServer};
	__property TIdFTPSecurityOptions* UserSecurity = {read=FUserSecurity, write=SetUserSecurity};
	__property System::UnicodeString AuthMechanism = {read=FAuthMechanism, write=FAuthMechanism};
	__property Idftpcommon::TIdFTPTransferType DataType = {read=FDataType, write=FDataType, nodefault};
	__property Idftpcommon::TIdFTPTransferMode DataMode = {read=FDataMode, write=FDataMode, nodefault};
	__property System::Word DataPort = {read=FDataPort, nodefault};
	__property unsigned DataProtBufSize = {read=FDataProtBufSize, write=FDataProtBufSize, nodefault};
	__property bool DataPBSZCalled = {read=FDataPBSZCalled, write=FDataPBSZCalled, nodefault};
	__property Idftpcommon::TIdFTPDataStructure DataStruct = {read=FDataStruct, write=FDataStruct, nodefault};
	__property Idftpcommon::TIdFTPDataPortSecurity DataProtection = {read=FDataProtection, write=FDataProtection, nodefault};
	__property unsigned PasswordAttempts = {read=FPasswordAttempts, write=FPasswordAttempts, nodefault};
	__property bool PASV = {read=FPASV, write=FPASV, nodefault};
	__property int RESTPos = {read=FRESTPos, write=FRESTPos, nodefault};
	__property Idftplistoutput::TIdFTPFactOutputs MLSOpts = {read=FMLSOpts, write=FMLSOpts, nodefault};
	__property bool SSCNOn = {read=FSSCNOn, write=FSSCNOn, nodefault};
	__property bool MSDOSMode = {read=FMSDOSMode, write=FMSDOSMode, nodefault};
	__property int UMask = {read=FUMask, write=FUMask, nodefault};
	__property int ZLibCompressionLevel = {read=FZLibCompressionLevel, write=FZLibCompressionLevel, nodefault};
	__property int ZLibWindowBits = {read=FZLibWindowBits, write=FZLibWindowBits, nodefault};
	__property int ZLibMemLevel = {read=FZLibMemLevel, write=FZLibMemLevel, nodefault};
	__property int ZLibStratagy = {read=FZLibStratagy, write=FZLibStratagy, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TIdOnGetCustomListFormat)(TIdFTPServer* ASender, Idftplist::TIdFTPListItem* AItem, System::UnicodeString &VText);

class PASCALIMPLEMENTATION TIdFTPServer : public Idexplicittlsclientserverbase::TIdExplicitTLSServer
{
	typedef Idexplicittlsclientserverbase::TIdExplicitTLSServer inherited;
	
protected:
	bool FSupportXAUTH;
	TIdFTPDirFormat FDirFormat;
	TIdFTPPathProcessing FPathProcessing;
	TIdOnClientID FOnClientID;
	Idcommandhandlers::TIdCommandHandlers* FDataChannelCommands;
	Idcommandhandlers::TIdCommandHandlers* FSITECommands;
	Idcommandhandlers::TIdCommandHandlers* FOPTSCommands;
	TIdMLSDAttrs FMLSDFacts;
	System::Classes::TStrings* FAnonymousAccounts;
	bool FAllowAnonymousLogin;
	bool FAnonymousPassStrictCheck;
	System::Word FPASVBoundPortMin;
	System::Word FPASVBoundPortMax;
	System::UnicodeString FSystemType;
	System::Word FDefaultDataPort;
	Iduseraccounts::TIdCustomUserManager* FUserAccounts;
	TOnFTPUserAccountEvent FOnUserAccount;
	TOnAfterUserLoginEvent FOnAfterUserLogin;
	TOnFTPUserLoginEvent FOnUserLogin;
	TOnDirectoryEvent FOnChangeDirectory;
	TOnGetFileSizeEvent FOnGetFileSize;
	TOnGetFileDateEvent FOnGetFileDate;
	TOnListDirectoryEvent FOnListDirectory;
	TOnCustomListDirectoryEvent FOnCustomListDirectory;
	TOnRenameFileEvent FOnRenameFile;
	TOnFileEvent FOnDeleteFile;
	TOnRetrieveFileEvent FOnRetrieveFile;
	TOnStoreFileEvent FOnStoreFile;
	TOnDirectoryEvent FOnMakeDirectory;
	TOnDirectoryEvent FOnRemoveDirectory;
	TIdOnFTPStatEvent FOnStat;
	TIdFTPSecurityOptions* FFTPSecurityOptions;
	TOnCheckSumFile FOnCRCFile;
	TOnCombineFiles FOnCombineFiles;
	TOnSetFileDateEvent FOnSetModifiedTime;
	TOnCheckFileEvent FOnFileExistCheck;
	TOnSetFileDateEvent FOnSetCreationTime;
	TOnCacheChecksum FOnMD5Cache;
	TOnVerifyChecksum FOnMD5Verify;
	TIdOnBanner FOnGreeting;
	TIdOnBanner FOnLoginSuccessBanner;
	TIdOnBanner FOnLoginFailureBanner;
	TIdOnBanner FOnQuitBanner;
	TOnSetATTRIB FOnSetATTRIB;
	TOnSiteUMASK FOnSiteUMASK;
	TOnSiteCHMOD FOnSiteCHMOD;
	TOnSiteCHOWN FOnSiteCHOWN;
	TOnSiteCHGRP FOnSiteCHGRP;
	TIdOnDirSizeInfo FOnAvailDiskSpace;
	TIdOnDirSizeInfo FOnCompleteDirSize;
	TOnDirectoryEvent FOnRemoveDirectoryAll;
	TOnCustomPathProcess FOnCustomPathProcess;
	TOnDataPortBind FOnDataPortBeforeBind;
	TOnDataPortBind FOnDataPortAfterBind;
	TIdOnPASVRange FOnPASVBeforeBind;
	TIdOnPASV FOnPASVReply;
	Idftpbasefilesystem::TIdFTPBaseFileSystem* FFTPFileSystem;
	System::UnicodeString FEndOfHelpLine;
	System::UnicodeString FCustomSystID;
	Idreply::TIdReply* FReplyUnknownSITECommand;
	Idzlibcompressorbase::TIdZLibCompressorBase* FCompressor;
	TIdOnMLST FOnMLST;
	TOnSiteUTIME FOnSiteUTIME;
	TOnHostCheck FOnHostCheck;
	void __fastcall SetOnUserAccount(TOnFTPUserAccountEvent AValue);
	void __fastcall AuthenticateUser(Idcommandhandlers::TIdCommand* ASender);
	bool __fastcall SupportTaDirSwitches(TIdFTPServerContext* AContext);
	System::UnicodeString __fastcall IgnoreLastPathDelim(const System::UnicodeString APath);
	void __fastcall DoOnPASVBeforeBind(TIdFTPServerContext* ASender, System::UnicodeString &VIP, System::Word &VPortMin, System::Word &VPortMax, const Idglobal::TIdIPVersion AIPVersion);
	void __fastcall DoOnPASVReply(TIdFTPServerContext* ASender, System::UnicodeString &VIP, System::Word &VPort, const Idglobal::TIdIPVersion AIPVersion);
	bool __fastcall InternalPASV(Idcommandhandlers::TIdCommand* ASender, System::UnicodeString &VIP, System::Word &VPort, Idglobal::TIdIPVersion &VIPVersion);
	System::UnicodeString __fastcall DoSysType(TIdFTPServerContext* ASender);
	System::UnicodeString __fastcall DoProcessPath(TIdFTPServerContext* ASender, const System::UnicodeString APath);
	System::UnicodeString __fastcall FTPNormalizePath(const System::UnicodeString APath);
	System::UnicodeString __fastcall MLSFEATLine(const TIdMLSDAttrs AFactMask, const Idftplistoutput::TIdFTPFactOutputs AFacts);
	System::UnicodeString __fastcall HelpText(System::Classes::TStrings* Cmds);
	bool __fastcall IsValidPermNumbers(const System::UnicodeString APermNos);
	void __fastcall SetRFCReplyFormat(Idreply::TIdReply* AReply);
	System::UnicodeString __fastcall CDUPDir(TIdFTPServerContext* AContext);
	void __fastcall DisconUser(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CmdNotImplemented(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CmdFileActionAborted(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CmdSyntaxError(Idcontext::TIdContext* AContext, System::UnicodeString ALine, Idreply::TIdReply* const AReply = (Idreply::TIdReply*)(0x0))/* overload */;
	void __fastcall CmdSyntaxError(Idcommandhandlers::TIdCommand* ASender)/* overload */;
	void __fastcall CmdInvalidParams(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CmdInvalidParamNum(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CmdTwineFileActionAborted(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CmdCommandSuccessful(Idcommandhandlers::TIdCommand* ASender, const int AReplyCode = 0xfa);
	void __fastcall CommandQUIT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandUSER(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandPASS(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandACCT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandXAUT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandCWD(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandCDUP(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandREIN(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandPORT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandPASV(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandTYPE(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSTRU(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandMODE(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandRETR(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSSAP(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandALLO(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandREST(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandRNFR(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandRNTO(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandABOR(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandAVBL(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandDELE(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandDSIZ(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandRMDA(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandRMD(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandMKD(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandPWD(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandLIST(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSYST(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSTAT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSIZE(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandFEAT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandOPTS(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandAUTH(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandCCC(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandEPSV(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandEPRT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandMDTM(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandMFF(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandMD5(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandMMD5(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandPROT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandPBSZ(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandMFMT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandMFCT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandMLSD(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandMLST(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandCheckSum(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandCOMB(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandCLNT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSSCN(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandCPSV(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSPSV(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandHOST(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSecRFC(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSITE(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSiteHELP(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSiteUMASK(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSiteCHMOD(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSiteCHOWN(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSiteCHGRP(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSiteDIRSTYLE(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSiteZONE(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSiteATTRIB(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSiteUTIME(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandOptsMLST(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandOptsMODEZ(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandOptsUTF8(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandHELP(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall DoOnRenameFile(TIdFTPServerContext* ASender, const System::UnicodeString ARenameFromFile, const System::UnicodeString ARenameToFile);
	void __fastcall DoOnDeleteFile(TIdFTPServerContext* ASender, const System::UnicodeString APathName);
	void __fastcall DoOnChangeDirectory(TIdFTPServerContext* AContext, System::UnicodeString &VDirectory);
	void __fastcall DoOnMakeDirectory(TIdFTPServerContext* AContext, System::UnicodeString &VDirectory);
	void __fastcall DoOnRemoveDirectory(TIdFTPServerContext* AContext, System::UnicodeString &VDirectory);
	void __fastcall DoOnGetFileSize(TIdFTPServerContext* ASender, const System::UnicodeString AFilename, __int64 &VFileSize);
	void __fastcall DoOnGetFileDate(TIdFTPServerContext* ASender, const System::UnicodeString AFilename, System::TDateTime &VFileDate);
	void __fastcall DoOnSetModifiedTime(TIdFTPServerContext* AContext, const System::UnicodeString AFileName, System::TDateTime &VDateTime)/* overload */;
	void __fastcall DoOnSetModifiedTime(TIdFTPServerContext* AContext, const System::UnicodeString AFileName, System::UnicodeString &VDateTimeStr)/* overload */;
	void __fastcall DoOnFileExistCheck(TIdFTPServerContext* AContext, const System::UnicodeString AFileName, bool &VExist);
	void __fastcall DoOnSetModifiedTimeGMT(TIdFTPServerContext* AContext, const System::UnicodeString AFileName, System::TDateTime &VDateTime);
	void __fastcall DoOnSetCreationTime(TIdFTPServerContext* AContext, const System::UnicodeString AFileName, System::TDateTime &VDateTime)/* overload */;
	void __fastcall DoOnSetCreationTime(TIdFTPServerContext* AContext, const System::UnicodeString AFileName, System::UnicodeString &VDateTimeStr)/* overload */;
	void __fastcall DoOnSetCreationTimeGMT(TIdFTPServerContext* AContext, const System::UnicodeString AFileName, System::TDateTime &VDateTime);
	void __fastcall DoOnCRCFile(TIdFTPServerContext* ASender, const System::UnicodeString AFileName, System::Classes::TStream* &VStream);
	void __fastcall DoOnMD5Verify(TIdFTPServerContext* ASender, const System::UnicodeString AFileName, const System::UnicodeString ACheckSum);
	void __fastcall DoOnMD5Cache(TIdFTPServerContext* ASender, const System::UnicodeString AFileName, System::UnicodeString &VCheckSum);
	void __fastcall DoOnCombineFiles(TIdFTPServerContext* ASender, const System::UnicodeString ATargetFileName, System::Classes::TStrings* AParts);
	void __fastcall DoOnSetATTRIB(TIdFTPServerContext* ASender, unsigned &VAttr, const System::UnicodeString AFileName, bool &VAUth);
	void __fastcall DoOnSiteUMASK(TIdFTPServerContext* ASender, int &VUMASK, bool &VAUth);
	void __fastcall DoOnSiteCHMOD(TIdFTPServerContext* ASender, int &APermissions, const System::UnicodeString AFileName, bool &VAUth);
	void __fastcall DoOnSiteCHOWN(TIdFTPServerContext* ASender, System::UnicodeString &AOwner, System::UnicodeString &AGroup, const System::UnicodeString AFileName, bool &VAUth);
	void __fastcall DoOnSiteCHGRP(TIdFTPServerContext* ASender, System::UnicodeString &AGroup, const System::UnicodeString AFileName, bool &VAUth);
	virtual void __fastcall SetUseTLS(Idexplicittlsclientserverbase::TIdUseTLS AValue);
	void __fastcall SetSupportXAUTH(bool AValue);
	virtual void __fastcall InitializeCommandHandlers();
	void __fastcall ListDirectory(TIdFTPServerContext* ASender, System::UnicodeString ADirectory, System::Classes::TStrings* ADirContents, bool ADetails, const System::UnicodeString ACmd = u"LIST", const System::UnicodeString ASwitches = System::UnicodeString());
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall SetAnonymousAccounts(System::Classes::TStrings* const AValue);
	void __fastcall SetUserAccounts(Iduseraccounts::TIdCustomUserManager* const AValue);
	void __fastcall SetFTPSecurityOptions(TIdFTPSecurityOptions* const AValue);
	void __fastcall SetPASVBoundPortMax(const System::Word AValue);
	void __fastcall SetPASVBoundPortMin(const System::Word AValue);
	void __fastcall SetReplyUnknownSITECommand(Idreply::TIdReply* AValue);
	void __fastcall SetSITECommands(Idcommandhandlers::TIdCommandHandlers* AValue);
	void __fastcall ThreadException(Idthread::TIdThread* AThread, System::Sysutils::Exception* AException);
	void __fastcall SetFTPFileSystem(Idftpbasefilesystem::TIdFTPBaseFileSystem* const AValue);
	System::UnicodeString __fastcall GetMD5Checksum(TIdFTPServerContext* ASender, const System::UnicodeString AFileName);
	virtual void __fastcall DoConnect(Idcontext::TIdContext* AContext);
	virtual void __fastcall DoDisconnect(Idcontext::TIdContext* AContext);
	virtual void __fastcall ContextCreated(Idcontext::TIdContext* AContext);
	virtual void __fastcall DoOnDataPortBeforeBind(TIdFTPServerContext* ASender);
	virtual void __fastcall DoDataChannelOperation(Idcommandhandlers::TIdCommand* ASender, const bool AConnectMode = false);
	virtual void __fastcall DoOnDataPortAfterBind(TIdFTPServerContext* ASender);
	void __fastcall DoOnCustomListDirectory(TIdFTPServerContext* ASender, const System::UnicodeString APath, System::Classes::TStrings* ADirectoryListing, const System::UnicodeString ACmd, const System::UnicodeString ASwitches);
	virtual Idreply::TIdReplyClass __fastcall GetReplyClass();
	virtual Idreply::TIdRepliesClass __fastcall GetRepliesClass();
	virtual void __fastcall InitComponent();
	virtual void __fastcall DoReplyUnknownCommand(Idcontext::TIdContext* AContext, System::UnicodeString ALine);
	virtual void __fastcall DoTerminateContext(Idcontext::TIdContext* AContext);
	virtual System::UnicodeString __fastcall ReadCommandLine(Idcontext::TIdContext* AContext);
	
public:
	__fastcall virtual ~TIdFTPServer();
	__property bool SupportXAUTH = {read=FSupportXAUTH, write=SetSupportXAUTH, nodefault};
	
__published:
	__property Idzlibcompressorbase::TIdZLibCompressorBase* Compressor = {read=FCompressor, write=FCompressor};
	__property System::UnicodeString CustomSystID = {read=FCustomSystID, write=FCustomSystID};
	__property TIdFTPDirFormat DirFormat = {read=FDirFormat, write=FDirFormat, default=1};
	__property TIdFTPPathProcessing PathProcessing = {read=FPathProcessing, write=FPathProcessing, default=2};
	__property UseTLS = {default=0};
	__property DefaultPort = {default=21};
	__property bool AllowAnonymousLogin = {read=FAllowAnonymousLogin, write=FAllowAnonymousLogin, default=0};
	__property System::Classes::TStrings* AnonymousAccounts = {read=FAnonymousAccounts, write=SetAnonymousAccounts};
	__property bool AnonymousPassStrictCheck = {read=FAnonymousPassStrictCheck, write=FAnonymousPassStrictCheck, default=1};
	__property System::Word DefaultDataPort = {read=FDefaultDataPort, write=FDefaultDataPort, default=20};
	__property Idftpbasefilesystem::TIdFTPBaseFileSystem* FTPFileSystem = {read=FFTPFileSystem, write=SetFTPFileSystem};
	__property TIdFTPSecurityOptions* FTPSecurityOptions = {read=FFTPSecurityOptions, write=SetFTPSecurityOptions};
	__property System::UnicodeString EndOfHelpLine = {read=FEndOfHelpLine, write=FEndOfHelpLine};
	__property System::Word PASVBoundPortMin = {read=FPASVBoundPortMin, write=SetPASVBoundPortMin, default=0};
	__property System::Word PASVBoundPortMax = {read=FPASVBoundPortMax, write=SetPASVBoundPortMax, default=0};
	__property Iduseraccounts::TIdCustomUserManager* UserAccounts = {read=FUserAccounts, write=SetUserAccounts};
	__property System::UnicodeString SystemType = {read=FSystemType, write=FSystemType};
	__property TIdOnBanner OnGreeting = {read=FOnGreeting, write=FOnGreeting};
	__property TIdOnBanner OnLoginSuccessBanner = {read=FOnLoginSuccessBanner, write=FOnLoginSuccessBanner};
	__property TIdOnBanner OnLoginFailureBanner = {read=FOnLoginFailureBanner, write=FOnLoginFailureBanner};
	__property TOnCacheChecksum OnMD5Cache = {read=FOnMD5Cache, write=FOnMD5Cache};
	__property TOnVerifyChecksum OnMD5Verify = {read=FOnMD5Verify, write=FOnMD5Verify};
	__property TIdOnBanner OnQuitBanner = {read=FOnQuitBanner, write=FOnQuitBanner};
	__property TOnCustomListDirectoryEvent OnCustomListDirectory = {read=FOnCustomListDirectory, write=FOnCustomListDirectory};
	__property TOnCustomPathProcess OnCustomPathProcess = {read=FOnCustomPathProcess, write=FOnCustomPathProcess};
	__property TOnAfterUserLoginEvent OnAfterUserLogin = {read=FOnAfterUserLogin, write=FOnAfterUserLogin};
	__property TOnDirectoryEvent OnChangeDirectory = {read=FOnChangeDirectory, write=FOnChangeDirectory};
	__property TOnGetFileSizeEvent OnGetFileSize = {read=FOnGetFileSize, write=FOnGetFileSize};
	__property TOnGetFileDateEvent OnGetFileDate = {read=FOnGetFileDate, write=FOnGetFileDate};
	__property TOnFTPUserLoginEvent OnUserLogin = {read=FOnUserLogin, write=FOnUserLogin};
	__property TOnFTPUserAccountEvent OnUserAccount = {read=FOnUserAccount, write=SetOnUserAccount};
	__property TOnListDirectoryEvent OnListDirectory = {read=FOnListDirectory, write=FOnListDirectory};
	__property TOnDataPortBind OnDataPortBeforeBind = {read=FOnDataPortBeforeBind, write=FOnDataPortBeforeBind};
	__property TOnDataPortBind OnDataPortAfterBind = {read=FOnDataPortAfterBind, write=FOnDataPortAfterBind};
	__property TOnRenameFileEvent OnRenameFile = {read=FOnRenameFile, write=FOnRenameFile};
	__property TOnFileEvent OnDeleteFile = {read=FOnDeleteFile, write=FOnDeleteFile};
	__property TOnRetrieveFileEvent OnRetrieveFile = {read=FOnRetrieveFile, write=FOnRetrieveFile};
	__property TOnStoreFileEvent OnStoreFile = {read=FOnStoreFile, write=FOnStoreFile};
	__property TOnDirectoryEvent OnMakeDirectory = {read=FOnMakeDirectory, write=FOnMakeDirectory};
	__property TOnDirectoryEvent OnRemoveDirectory = {read=FOnRemoveDirectory, write=FOnRemoveDirectory};
	__property TIdOnFTPStatEvent OnStat = {read=FOnStat, write=FOnStat};
	__property TOnCombineFiles OnCombineFiles = {read=FOnCombineFiles, write=FOnCombineFiles};
	__property TOnCheckSumFile OnCRCFile = {read=FOnCRCFile, write=FOnCRCFile};
	__property TOnSetFileDateEvent OnSetCreationTime = {read=FOnSetCreationTime, write=FOnSetCreationTime};
	__property TOnSetFileDateEvent OnSetModifiedTime = {read=FOnSetModifiedTime, write=FOnSetModifiedTime};
	__property TOnCheckFileEvent OnFileExistCheck = {read=FOnFileExistCheck, write=FOnFileExistCheck};
	__property TOnHostCheck OnHostCheck = {read=FOnHostCheck, write=FOnHostCheck};
	__property TOnSetATTRIB OnSetATTRIB = {read=FOnSetATTRIB, write=FOnSetATTRIB};
	__property TOnSiteUMASK OnSiteUMASK = {read=FOnSiteUMASK, write=FOnSiteUMASK};
	__property TOnSiteCHMOD OnSiteCHMOD = {read=FOnSiteCHMOD, write=FOnSiteCHMOD};
	__property TOnSiteCHOWN OnSiteCHOWN = {read=FOnSiteCHOWN, write=FOnSiteCHOWN};
	__property TOnSiteCHGRP OnSiteCHGRP = {read=FOnSiteCHGRP, write=FOnSiteCHGRP};
	__property TIdOnPASVRange OnPASVBeforeBind = {read=FOnPASVBeforeBind, write=FOnPASVBeforeBind};
	__property TIdOnPASV OnPASVReply = {read=FOnPASVReply, write=FOnPASVReply};
	__property TIdOnMLST OnMLST = {read=FOnMLST, write=FOnMLST};
	__property TOnSiteUTIME OnSiteUTIME = {read=FOnSiteUTIME, write=FOnSiteUTIME};
	__property TIdOnDirSizeInfo OnAvailDiskSpace = {read=FOnAvailDiskSpace, write=FOnAvailDiskSpace};
	__property TIdOnDirSizeInfo OnCompleteDirSize = {read=FOnCompleteDirSize, write=FOnCompleteDirSize};
	__property Idcommandhandlers::TIdCommandHandlers* SITECommands = {read=FSITECommands, write=SetSITECommands};
	__property TIdMLSDAttrs MLSDFacts = {read=FMLSDFacts, write=FMLSDFacts, nodefault};
	__property TIdOnClientID OnClientID = {read=FOnClientID, write=FOnClientID};
	__property Idreply::TIdReply* ReplyUnknownSITCommand = {read=FReplyUnknownSITECommand, write=SetReplyUnknownSITECommand};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdFTPServer(System::Classes::TComponent* AOwner)/* overload */ : Idexplicittlsclientserverbase::TIdExplicitTLSServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdFTPServer()/* overload */ : Idexplicittlsclientserverbase::TIdExplicitTLSServer() { }
	
};


enum DECLSPEC_DENUM TIdFTPTelnetState : unsigned char { tsData, tsCheckCR, tsIAC, tsWill, tsDo, tsWont, tsDont, tsNegotiate, tsNegotiateData, tsNegotiateIAC, tsInterrupt, tsInterruptIAC };

//-- var, const, procedure ---------------------------------------------------
static const TIdFTPDirFormat DEF_DIRFORMAT = (TIdFTPDirFormat)(1);
static constexpr bool Id_DEF_AllowAnon = false;
static constexpr bool Id_DEF_PassStrictCheck = true;
static constexpr bool DEF_FTP_IMPLICIT_FTP = false;
static constexpr bool DEF_FTP_HIDE_INVALID_USER = true;
static constexpr System::Int8 DEF_FTP_PASSWORDATTEMPTS = System::Int8(0x3);
static constexpr System::Word DEF_FTP_INVALIDPASS_DELAY = System::Word(0xbb8);
static constexpr bool DEF_FTP_PASV_SAME_IP = true;
static constexpr bool DEF_FTP_PORT_SAME_IP = true;
static constexpr bool DEF_FTP_NO_RESERVED_PORTS = true;
static constexpr bool DEF_FTP_BLOCK_ALL_PORTS = false;
static constexpr bool DEF_FTP_DISABLE_SYST = false;
static constexpr bool DEF_FTP_DISABLE_STAT = false;
static constexpr bool DEF_FTP_PERMIT_CCC = false;
static constexpr bool DEF_FTP_REPORT_EX_MSG = false;
static constexpr System::Int8 DEF_PASV_BOUND_MIN = System::Int8(0x0);
static constexpr System::Int8 DEF_PASV_BOUND_MAX = System::Int8(0x0);
static const TIdFTPPathProcessing DEF_PATHPROCESSING = (TIdFTPPathProcessing)(2);
#define SYST_ID_UNIX u"UNIX Type: L8"
#define SYST_ID_NT u"Windows_NT"
extern DELPHI_PACKAGE Idftpserver__1 AAlwaysValidOpts;
}	/* namespace Idftpserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPSERVER)
using namespace Idftpserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftpserverHPP
