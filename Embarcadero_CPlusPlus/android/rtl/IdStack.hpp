﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdStack.pas' rev: 34.00 (Android)

#ifndef IdstackHPP
#define IdstackHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdException.hpp>
#include <IdStackConsts.hpp>
#include <IdGlobal.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idstack
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdSocketError;
class DELPHICLASS EIdStackError;
class DELPHICLASS EIdIPVersionUnsupported;
class DELPHICLASS EIdResolveError;
class DELPHICLASS EIdReverseResolveError;
class DELPHICLASS EIdMaliciousPtrRecord;
class DELPHICLASS EIdNotASocket;
class DELPHICLASS EIdAndroidPermissionNeeded;
class DELPHICLASS EIdInternetPermissionNeeded;
class DELPHICLASS TIdPacketInfo;
class DELPHICLASS TIdSocketList;
class DELPHICLASS TIdStackLocalAddress;
class DELPHICLASS TIdStackLocalAddressIPv4;
class DELPHICLASS TIdStackLocalAddressIPv6;
class DELPHICLASS TIdStackLocalAddressList;
class DELPHICLASS TIdStack;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdSocketError : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
protected:
	int FLastError;
	
public:
	__fastcall virtual EIdSocketError(const int AErr, const System::UnicodeString AMsg);
	__property int LastError = {read=FLastError, nodefault};
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSocketError(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSocketError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSocketError(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSocketError(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSocketError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSocketError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSocketError(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSocketError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSocketError(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSocketError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSocketError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSocketError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSocketError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdStackError : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdStackError(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdStackError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdStackError(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdStackError(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdStackError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdStackError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdStackError(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdStackError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdStackError(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdStackError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdStackError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdStackError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdStackError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdIPVersionUnsupported : public EIdStackError
{
	typedef EIdStackError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdIPVersionUnsupported(const System::UnicodeString AMsg)/* overload */ : EIdStackError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdIPVersionUnsupported(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdStackError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdIPVersionUnsupported(NativeUInt Ident)/* overload */ : EIdStackError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdIPVersionUnsupported(System::PResStringRec ResStringRec)/* overload */ : EIdStackError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIPVersionUnsupported(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdStackError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdIPVersionUnsupported(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdStackError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdIPVersionUnsupported(const System::UnicodeString Msg, int AHelpContext) : EIdStackError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdIPVersionUnsupported(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdStackError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIPVersionUnsupported(NativeUInt Ident, int AHelpContext)/* overload */ : EIdStackError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdIPVersionUnsupported(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdStackError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIPVersionUnsupported(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdStackError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdIPVersionUnsupported(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdStackError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdIPVersionUnsupported() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdResolveError : public EIdSocketError
{
	typedef EIdSocketError inherited;
	
public:
	/* EIdSocketError.CreateError */ inline __fastcall virtual EIdResolveError(const int AErr, const System::UnicodeString AMsg) : EIdSocketError(AErr, AMsg) { }
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdResolveError(const System::UnicodeString AMsg)/* overload */ : EIdSocketError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdResolveError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSocketError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdResolveError(NativeUInt Ident)/* overload */ : EIdSocketError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdResolveError(System::PResStringRec ResStringRec)/* overload */ : EIdSocketError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdResolveError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSocketError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdResolveError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSocketError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdResolveError(const System::UnicodeString Msg, int AHelpContext) : EIdSocketError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdResolveError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSocketError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdResolveError(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSocketError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdResolveError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSocketError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdResolveError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSocketError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdResolveError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSocketError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdResolveError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdReverseResolveError : public EIdSocketError
{
	typedef EIdSocketError inherited;
	
public:
	/* EIdSocketError.CreateError */ inline __fastcall virtual EIdReverseResolveError(const int AErr, const System::UnicodeString AMsg) : EIdSocketError(AErr, AMsg) { }
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdReverseResolveError(const System::UnicodeString AMsg)/* overload */ : EIdSocketError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdReverseResolveError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSocketError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdReverseResolveError(NativeUInt Ident)/* overload */ : EIdSocketError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdReverseResolveError(System::PResStringRec ResStringRec)/* overload */ : EIdSocketError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdReverseResolveError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSocketError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdReverseResolveError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSocketError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdReverseResolveError(const System::UnicodeString Msg, int AHelpContext) : EIdSocketError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdReverseResolveError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSocketError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdReverseResolveError(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSocketError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdReverseResolveError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSocketError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdReverseResolveError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSocketError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdReverseResolveError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSocketError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdReverseResolveError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdMaliciousPtrRecord : public EIdReverseResolveError
{
	typedef EIdReverseResolveError inherited;
	
public:
	/* EIdSocketError.CreateError */ inline __fastcall virtual EIdMaliciousPtrRecord(const int AErr, const System::UnicodeString AMsg) : EIdReverseResolveError(AErr, AMsg) { }
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdMaliciousPtrRecord(const System::UnicodeString AMsg)/* overload */ : EIdReverseResolveError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdMaliciousPtrRecord(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdReverseResolveError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdMaliciousPtrRecord(NativeUInt Ident)/* overload */ : EIdReverseResolveError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdMaliciousPtrRecord(System::PResStringRec ResStringRec)/* overload */ : EIdReverseResolveError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdMaliciousPtrRecord(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdReverseResolveError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdMaliciousPtrRecord(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdReverseResolveError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdMaliciousPtrRecord(const System::UnicodeString Msg, int AHelpContext) : EIdReverseResolveError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdMaliciousPtrRecord(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdReverseResolveError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdMaliciousPtrRecord(NativeUInt Ident, int AHelpContext)/* overload */ : EIdReverseResolveError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdMaliciousPtrRecord(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdReverseResolveError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdMaliciousPtrRecord(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdReverseResolveError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdMaliciousPtrRecord(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdReverseResolveError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdMaliciousPtrRecord() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdNotASocket : public EIdSocketError
{
	typedef EIdSocketError inherited;
	
public:
	/* EIdSocketError.CreateError */ inline __fastcall virtual EIdNotASocket(const int AErr, const System::UnicodeString AMsg) : EIdSocketError(AErr, AMsg) { }
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdNotASocket(const System::UnicodeString AMsg)/* overload */ : EIdSocketError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdNotASocket(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSocketError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdNotASocket(NativeUInt Ident)/* overload */ : EIdSocketError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdNotASocket(System::PResStringRec ResStringRec)/* overload */ : EIdSocketError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNotASocket(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSocketError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNotASocket(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSocketError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdNotASocket(const System::UnicodeString Msg, int AHelpContext) : EIdSocketError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdNotASocket(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSocketError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNotASocket(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSocketError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNotASocket(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSocketError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNotASocket(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSocketError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNotASocket(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSocketError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdNotASocket() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdAndroidPermissionNeeded : public EIdSocketError
{
	typedef EIdSocketError inherited;
	
public:
	/* EIdSocketError.CreateError */ inline __fastcall virtual EIdAndroidPermissionNeeded(const int AErr, const System::UnicodeString AMsg) : EIdSocketError(AErr, AMsg) { }
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdAndroidPermissionNeeded(const System::UnicodeString AMsg)/* overload */ : EIdSocketError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdAndroidPermissionNeeded(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSocketError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdAndroidPermissionNeeded(NativeUInt Ident)/* overload */ : EIdSocketError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdAndroidPermissionNeeded(System::PResStringRec ResStringRec)/* overload */ : EIdSocketError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdAndroidPermissionNeeded(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSocketError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdAndroidPermissionNeeded(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSocketError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdAndroidPermissionNeeded(const System::UnicodeString Msg, int AHelpContext) : EIdSocketError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdAndroidPermissionNeeded(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSocketError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdAndroidPermissionNeeded(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSocketError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdAndroidPermissionNeeded(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSocketError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdAndroidPermissionNeeded(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSocketError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdAndroidPermissionNeeded(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSocketError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdAndroidPermissionNeeded() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdInternetPermissionNeeded : public EIdAndroidPermissionNeeded
{
	typedef EIdAndroidPermissionNeeded inherited;
	
public:
	/* EIdSocketError.CreateError */ inline __fastcall virtual EIdInternetPermissionNeeded(const int AErr, const System::UnicodeString AMsg) : EIdAndroidPermissionNeeded(AErr, AMsg) { }
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdInternetPermissionNeeded(const System::UnicodeString AMsg)/* overload */ : EIdAndroidPermissionNeeded(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdInternetPermissionNeeded(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdAndroidPermissionNeeded(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdInternetPermissionNeeded(NativeUInt Ident)/* overload */ : EIdAndroidPermissionNeeded(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdInternetPermissionNeeded(System::PResStringRec ResStringRec)/* overload */ : EIdAndroidPermissionNeeded(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdInternetPermissionNeeded(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdAndroidPermissionNeeded(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdInternetPermissionNeeded(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdAndroidPermissionNeeded(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdInternetPermissionNeeded(const System::UnicodeString Msg, int AHelpContext) : EIdAndroidPermissionNeeded(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdInternetPermissionNeeded(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdAndroidPermissionNeeded(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdInternetPermissionNeeded(NativeUInt Ident, int AHelpContext)/* overload */ : EIdAndroidPermissionNeeded(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdInternetPermissionNeeded(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdAndroidPermissionNeeded(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdInternetPermissionNeeded(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdAndroidPermissionNeeded(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdInternetPermissionNeeded(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdAndroidPermissionNeeded(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdInternetPermissionNeeded() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef __int64 __fastcall (*TIdServeFile)(int ASocket, const System::UnicodeString AFileName);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdPacketInfo : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	System::UnicodeString FSourceIP;
	System::Word FSourcePort;
	unsigned FSourceIF;
	Idglobal::TIdIPVersion FSourceIPVersion;
	System::UnicodeString FDestIP;
	System::Word FDestPort;
	unsigned FDestIF;
	Idglobal::TIdIPVersion FDestIPVersion;
	System::Byte FTTL;
	
public:
	void __fastcall Reset();
	__property System::Byte TTL = {read=FTTL, write=FTTL, nodefault};
	__property System::UnicodeString SourceIP = {read=FSourceIP, write=FSourceIP};
	__property System::Word SourcePort = {read=FSourcePort, write=FSourcePort, nodefault};
	__property unsigned SourceIF = {read=FSourceIF, write=FSourceIF, nodefault};
	__property Idglobal::TIdIPVersion SourceIPVersion = {read=FSourceIPVersion, write=FSourceIPVersion, nodefault};
	__property System::UnicodeString DestIP = {read=FDestIP, write=FDestIP};
	__property System::Word DestPort = {read=FDestPort, write=FDestPort, nodefault};
	__property unsigned DestIF = {read=FDestIF, write=FDestIF, nodefault};
	__property Idglobal::TIdIPVersion DestIPVersion = {read=FDestIPVersion, write=FDestIPVersion, nodefault};
public:
	/* TObject.Create */ inline __fastcall TIdPacketInfo() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdPacketInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TIdSocketListClass);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdSocketList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	int operator[](int AIndex) { return this->Items[AIndex]; }
	
protected:
	Idglobal::TIdCriticalSection* FLock;
	virtual int __fastcall GetItem(int AIndex) = 0 ;
	
public:
	__fastcall virtual TIdSocketList();
	__fastcall virtual ~TIdSocketList();
	virtual void __fastcall Add(int AHandle) = 0 ;
	virtual TIdSocketList* __fastcall Clone() = 0 ;
	virtual int __fastcall Count() = 0 ;
	__classmethod TIdSocketList* __fastcall CreateSocketList();
	__property int Items[int AIndex] = {read=GetItem/*, default*/};
	virtual void __fastcall Remove(int AHandle) = 0 ;
	virtual void __fastcall Clear() = 0 ;
	virtual bool __fastcall ContainsSocket(int AHandle) = 0 ;
	void __fastcall Lock();
	__classmethod virtual bool __fastcall Select(TIdSocketList* AReadList, TIdSocketList* AWriteList, TIdSocketList* AExceptList, const int ATimeout = 0xfffffffe);
	virtual bool __fastcall SelectRead(const int ATimeout = 0xfffffffe) = 0 ;
	virtual bool __fastcall SelectReadList(TIdSocketList* &VSocketList, const int ATimeout = 0xfffffffe) = 0 ;
	void __fastcall Unlock();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdStackLocalAddress : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	Idglobal::TIdIPVersion FIPVersion;
	System::UnicodeString FIPAddress;
	System::UnicodeString FInterfaceName;
	unsigned FInterfaceIndex;
	
public:
	__fastcall TIdStackLocalAddress(System::Classes::TCollection* ACollection, const Idglobal::TIdIPVersion AIPVersion, const System::UnicodeString AIPAddress);
	__property Idglobal::TIdIPVersion IPVersion = {read=FIPVersion, nodefault};
	__property System::UnicodeString IPAddress = {read=FIPAddress};
	__property System::UnicodeString InterfaceName = {read=FInterfaceName};
	__property unsigned InterfaceIndex = {read=FInterfaceIndex, nodefault};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdStackLocalAddress() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdStackLocalAddressIPv4 : public TIdStackLocalAddress
{
	typedef TIdStackLocalAddress inherited;
	
protected:
	System::UnicodeString FSubNetMask;
	
public:
	__fastcall TIdStackLocalAddressIPv4(System::Classes::TCollection* ACollection, const System::UnicodeString AIPAddress, const System::UnicodeString ASubNetMask);
	__property System::UnicodeString SubNetMask = {read=FSubNetMask};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdStackLocalAddressIPv4() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdStackLocalAddressIPv6 : public TIdStackLocalAddress
{
	typedef TIdStackLocalAddress inherited;
	
public:
	__fastcall TIdStackLocalAddressIPv6(System::Classes::TCollection* ACollection, const System::UnicodeString AIPAddress);
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdStackLocalAddressIPv6() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdStackLocalAddressList : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TIdStackLocalAddress* operator[](int AIndex) { return this->Addresses[AIndex]; }
	
protected:
	TIdStackLocalAddress* __fastcall GetAddress(int AIndex);
	
public:
	__fastcall TIdStackLocalAddressList();
	int __fastcall IndexOfIP(const System::UnicodeString AIP)/* overload */;
	int __fastcall IndexOfIP(const System::UnicodeString AIP, Idglobal::TIdIPVersion AIPVersion)/* overload */;
	__property TIdStackLocalAddress* Addresses[int AIndex] = {read=GetAddress/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdStackLocalAddressList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdStack : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	System::Classes::TStrings* FLocalAddresses;
	void __fastcall IPVersionUnsupported();
	virtual System::UnicodeString __fastcall HostByName(const System::UnicodeString AHostName, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0)) = 0 ;
	System::UnicodeString __fastcall MakeCanonicalIPv6Address _DEPRECATED_ATTRIBUTE1("Use IdGlobal.MakeCanonicalIPv6Address()") (const System::UnicodeString AAddr);
	virtual System::UnicodeString __fastcall ReadHostName() = 0 ;
	System::UnicodeString __fastcall GetLocalAddress();
	System::Classes::TStrings* __fastcall GetLocalAddresses();
	
public:
	int __fastcall Accept(int ASocket, System::UnicodeString &VIP, System::Word &VPort)/* overload */;
	virtual int __fastcall Accept(int ASocket, System::UnicodeString &VIP, System::Word &VPort, Idglobal::TIdIPVersion &VIPVersion) = 0 /* overload */;
	virtual void __fastcall Bind(int ASocket, const System::UnicodeString AIP, const System::Word APort, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0)) = 0 ;
	virtual void __fastcall Connect(const int ASocket, const System::UnicodeString AIP, const System::Word APort, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0)) = 0 ;
	__fastcall virtual TIdStack();
	__fastcall virtual ~TIdStack();
	virtual void __fastcall Disconnect(int ASocket) = 0 ;
	virtual int __fastcall IOControl(const int s, const unsigned cmd, unsigned &arg) = 0 ;
	__classmethod void __fastcall IncUsage();
	__classmethod void __fastcall DecUsage();
	void __fastcall GetPeerName(int ASocket, System::UnicodeString &VIP, System::Word &VPort)/* overload */;
	virtual void __fastcall GetPeerName(int ASocket, System::UnicodeString &VIP, System::Word &VPort, Idglobal::TIdIPVersion &VIPVersion) = 0 /* overload */;
	void __fastcall GetSocketName(int ASocket, System::UnicodeString &VIP, System::Word &VPort)/* overload */;
	virtual void __fastcall GetSocketName(int ASocket, System::UnicodeString &VIP, System::Word &VPort, Idglobal::TIdIPVersion &VIPVersion) = 0 /* overload */;
	virtual System::UnicodeString __fastcall HostByAddress(const System::UnicodeString AAddress, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0)) = 0 ;
	virtual System::Word __fastcall HostToNetwork(System::Word AValue) = 0 /* overload */;
	virtual unsigned __fastcall HostToNetwork(unsigned AValue) = 0 /* overload */;
	virtual unsigned __int64 __fastcall HostToNetwork(unsigned __int64 AValue) = 0 /* overload */;
	virtual Idglobal::TIdIPv6Address __fastcall HostToNetwork(const Idglobal::TIdIPv6Address &AValue)/* overload */;
	bool __fastcall IsIP(System::UnicodeString AIP);
	virtual void __fastcall Listen(int ASocket, int ABackLog) = 0 ;
	virtual int __fastcall WSGetLastError() = 0 ;
	virtual void __fastcall WSSetLastError(const int AErr) = 0 ;
	virtual System::UnicodeString __fastcall WSTranslateSocketErrorMsg(const int AErr);
	int __fastcall CheckForSocketError(const int AResult)/* overload */;
	int __fastcall CheckForSocketError(const int AResult, const int *AIgnore, const int AIgnore_High)/* overload */;
	void __fastcall RaiseLastSocketError();
	virtual void __fastcall RaiseSocketError(int AErr);
	virtual int __fastcall NewSocketHandle(const int ASocketType, const int AProtocol, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0), const bool ANonBlocking = false) = 0 ;
	virtual System::Word __fastcall NetworkToHost(System::Word AValue) = 0 /* overload */;
	virtual unsigned __fastcall NetworkToHost(unsigned AValue) = 0 /* overload */;
	virtual unsigned __int64 __fastcall NetworkToHost(unsigned __int64 AValue) = 0 /* overload */;
	virtual Idglobal::TIdIPv6Address __fastcall NetworkToHost(const Idglobal::TIdIPv6Address &AValue)/* overload */;
	virtual void __fastcall GetSocketOption(int ASocket, int ALevel, int AOptName, /* out */ int &AOptVal) = 0 /* overload */;
	virtual void __fastcall SetSocketOption(int ASocket, int ALevel, int AOptName, int AOptVal) = 0 /* overload */;
	System::UnicodeString __fastcall ResolveHost(const System::UnicodeString AHost, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0));
	virtual int __fastcall Receive(int ASocket, Idglobal::TIdBytes &VBuffer) = 0 ;
	virtual int __fastcall Send(int ASocket, const Idglobal::TIdBytes ABuffer, const int AOffset = 0x0, const int ASize = 0xffffffff) = 0 ;
	virtual int __fastcall ReceiveFrom(int ASocket, Idglobal::TIdBytes &VBuffer, System::UnicodeString &VIP, System::Word &VPort, Idglobal::TIdIPVersion &VIPVersion) = 0 ;
	int __fastcall SendTo(int ASocket, const Idglobal::TIdBytes ABuffer, const int AOffset, const System::UnicodeString AIP, const System::Word APort, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0))/* overload */;
	virtual int __fastcall SendTo(int ASocket, const Idglobal::TIdBytes ABuffer, const int AOffset, const int ASize, const System::UnicodeString AIP, const System::Word APort, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0)) = 0 /* overload */;
	virtual unsigned __fastcall ReceiveMsg(int ASocket, Idglobal::TIdBytes &VBuffer, TIdPacketInfo* APkt) = 0 ;
	virtual bool __fastcall SupportsIPv4() = 0 ;
	virtual bool __fastcall SupportsIPv6() = 0 ;
	bool __fastcall IsValidIPv4MulticastGroup(const System::UnicodeString Value);
	bool __fastcall IsValidIPv6MulticastGroup(const System::UnicodeString Value);
	virtual void __fastcall SetKeepAliveValues(int ASocket, const bool AEnabled, const int ATimeMS, const int AInterval);
	virtual void __fastcall SetMulticastTTL(int AHandle, const System::Byte AValue, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0)) = 0 ;
	virtual void __fastcall SetLoopBack(int AHandle, const bool AValue, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0)) = 0 ;
	virtual void __fastcall DropMulticastMembership(int AHandle, const System::UnicodeString AGroupIP, const System::UnicodeString ALocalIP, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0)) = 0 ;
	virtual void __fastcall AddMulticastMembership(int AHandle, const System::UnicodeString AGroupIP, const System::UnicodeString ALocalIP, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0)) = 0 ;
	virtual System::Word __fastcall CalcCheckSum(const Idglobal::TIdBytes AData);
	virtual void __fastcall WriteChecksum(int s, Idglobal::TIdBytes &VBuffer, const int AOffset, const System::UnicodeString AIP, const System::Word APort, const Idglobal::TIdIPVersion AIPVersion = (Idglobal::TIdIPVersion)(0x0)) = 0 ;
	void __fastcall AddLocalAddressesToList _DEPRECATED_ATTRIBUTE1("use GetLocalAddressList()") (System::Classes::TStrings* AAddresses);
	virtual void __fastcall GetLocalAddressList(TIdStackLocalAddressList* AAddresses) = 0 ;
	__property System::UnicodeString HostName = {read=ReadHostName};
	__property System::UnicodeString LocalAddress = {read=GetLocalAddress};
	__property System::Classes::TStrings* LocalAddresses = {read=GetLocalAddresses};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TIdStackClass);

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TIdStack* GStack;
extern DELPHI_PACKAGE TIdServeFile GServeFileProc;
extern DELPHI_PACKAGE TIdSocketListClass GSocketListClass;
extern DELPHI_PACKAGE void __fastcall SetStackClass(TIdStackClass AStackClass);
extern DELPHI_PACKAGE bool __fastcall HasAndroidPermission(const System::UnicodeString Permission);
}	/* namespace Idstack */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSTACK)
using namespace Idstack;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdstackHPP
