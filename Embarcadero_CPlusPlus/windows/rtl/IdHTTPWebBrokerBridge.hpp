// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHTTPWebBrokerBridge.pas' rev: 34.00 (Windows)

#ifndef IdhttpwebbrokerbridgeHPP
#define IdhttpwebbrokerbridgeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <System.SysUtils.hpp>
#include <IdContext.hpp>
#include <IdCustomHTTPServer.hpp>
#include <IdException.hpp>
#include <IdTCPServer.hpp>
#include <IdIOHandlerSocket.hpp>
#include <Web.WebBroker.hpp>
#include <Web.WebReq.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idhttpwebbrokerbridge
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EWBBException;
class DELPHICLASS EWBBInvalidIdxGetDateVariable;
class DELPHICLASS EWBBInvalidIdxSetDateVariable;
class DELPHICLASS EWBBInvalidIdxGetIntVariable;
class DELPHICLASS EWBBInvalidIdxSetIntVariable;
class DELPHICLASS EWBBInvalidIdxGetStrVariable;
class DELPHICLASS EWBBInvalidIdxSetStringVar;
class DELPHICLASS EWBBInvalidStringVar;
class DELPHICLASS TIdHTTPAppRequest;
class DELPHICLASS TIdHTTPAppResponse;
class DELPHICLASS TIdHTTPWebBrokerBridge;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EWBBException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EWBBException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EWBBException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWBBException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWBBException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWBBException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWBBException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWBBException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EWBBInvalidIdxGetDateVariable : public EWBBException
{
	typedef EWBBException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EWBBInvalidIdxGetDateVariable(const System::UnicodeString AMsg)/* overload */ : EWBBException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EWBBInvalidIdxGetDateVariable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EWBBException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxGetDateVariable(NativeUInt Ident)/* overload */ : EWBBException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxGetDateVariable(System::PResStringRec ResStringRec)/* overload */ : EWBBException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxGetDateVariable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxGetDateVariable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWBBInvalidIdxGetDateVariable(const System::UnicodeString Msg, int AHelpContext) : EWBBException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWBBInvalidIdxGetDateVariable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EWBBException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxGetDateVariable(NativeUInt Ident, int AHelpContext)/* overload */ : EWBBException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxGetDateVariable(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EWBBException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxGetDateVariable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxGetDateVariable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWBBInvalidIdxGetDateVariable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EWBBInvalidIdxSetDateVariable : public EWBBException
{
	typedef EWBBException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EWBBInvalidIdxSetDateVariable(const System::UnicodeString AMsg)/* overload */ : EWBBException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EWBBInvalidIdxSetDateVariable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EWBBException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxSetDateVariable(NativeUInt Ident)/* overload */ : EWBBException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxSetDateVariable(System::PResStringRec ResStringRec)/* overload */ : EWBBException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxSetDateVariable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxSetDateVariable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWBBInvalidIdxSetDateVariable(const System::UnicodeString Msg, int AHelpContext) : EWBBException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWBBInvalidIdxSetDateVariable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EWBBException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxSetDateVariable(NativeUInt Ident, int AHelpContext)/* overload */ : EWBBException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxSetDateVariable(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EWBBException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxSetDateVariable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxSetDateVariable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWBBInvalidIdxSetDateVariable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EWBBInvalidIdxGetIntVariable : public EWBBException
{
	typedef EWBBException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EWBBInvalidIdxGetIntVariable(const System::UnicodeString AMsg)/* overload */ : EWBBException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EWBBInvalidIdxGetIntVariable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EWBBException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxGetIntVariable(NativeUInt Ident)/* overload */ : EWBBException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxGetIntVariable(System::PResStringRec ResStringRec)/* overload */ : EWBBException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxGetIntVariable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxGetIntVariable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWBBInvalidIdxGetIntVariable(const System::UnicodeString Msg, int AHelpContext) : EWBBException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWBBInvalidIdxGetIntVariable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EWBBException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxGetIntVariable(NativeUInt Ident, int AHelpContext)/* overload */ : EWBBException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxGetIntVariable(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EWBBException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxGetIntVariable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxGetIntVariable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWBBInvalidIdxGetIntVariable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EWBBInvalidIdxSetIntVariable : public EWBBException
{
	typedef EWBBException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EWBBInvalidIdxSetIntVariable(const System::UnicodeString AMsg)/* overload */ : EWBBException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EWBBInvalidIdxSetIntVariable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EWBBException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxSetIntVariable(NativeUInt Ident)/* overload */ : EWBBException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxSetIntVariable(System::PResStringRec ResStringRec)/* overload */ : EWBBException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxSetIntVariable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxSetIntVariable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWBBInvalidIdxSetIntVariable(const System::UnicodeString Msg, int AHelpContext) : EWBBException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWBBInvalidIdxSetIntVariable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EWBBException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxSetIntVariable(NativeUInt Ident, int AHelpContext)/* overload */ : EWBBException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxSetIntVariable(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EWBBException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxSetIntVariable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxSetIntVariable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWBBInvalidIdxSetIntVariable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EWBBInvalidIdxGetStrVariable : public EWBBException
{
	typedef EWBBException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EWBBInvalidIdxGetStrVariable(const System::UnicodeString AMsg)/* overload */ : EWBBException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EWBBInvalidIdxGetStrVariable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EWBBException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxGetStrVariable(NativeUInt Ident)/* overload */ : EWBBException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxGetStrVariable(System::PResStringRec ResStringRec)/* overload */ : EWBBException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxGetStrVariable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxGetStrVariable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWBBInvalidIdxGetStrVariable(const System::UnicodeString Msg, int AHelpContext) : EWBBException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWBBInvalidIdxGetStrVariable(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EWBBException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxGetStrVariable(NativeUInt Ident, int AHelpContext)/* overload */ : EWBBException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxGetStrVariable(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EWBBException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxGetStrVariable(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxGetStrVariable(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWBBInvalidIdxGetStrVariable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EWBBInvalidIdxSetStringVar : public EWBBException
{
	typedef EWBBException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EWBBInvalidIdxSetStringVar(const System::UnicodeString AMsg)/* overload */ : EWBBException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EWBBInvalidIdxSetStringVar(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EWBBException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxSetStringVar(NativeUInt Ident)/* overload */ : EWBBException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidIdxSetStringVar(System::PResStringRec ResStringRec)/* overload */ : EWBBException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxSetStringVar(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidIdxSetStringVar(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWBBInvalidIdxSetStringVar(const System::UnicodeString Msg, int AHelpContext) : EWBBException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWBBInvalidIdxSetStringVar(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EWBBException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxSetStringVar(NativeUInt Ident, int AHelpContext)/* overload */ : EWBBException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidIdxSetStringVar(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EWBBException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxSetStringVar(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidIdxSetStringVar(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWBBInvalidIdxSetStringVar() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EWBBInvalidStringVar : public EWBBException
{
	typedef EWBBException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EWBBInvalidStringVar(const System::UnicodeString AMsg)/* overload */ : EWBBException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EWBBInvalidStringVar(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EWBBException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidStringVar(NativeUInt Ident)/* overload */ : EWBBException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWBBInvalidStringVar(System::PResStringRec ResStringRec)/* overload */ : EWBBException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidStringVar(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWBBInvalidStringVar(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EWBBException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWBBInvalidStringVar(const System::UnicodeString Msg, int AHelpContext) : EWBBException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWBBInvalidStringVar(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EWBBException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidStringVar(NativeUInt Ident, int AHelpContext)/* overload */ : EWBBException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWBBInvalidStringVar(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EWBBException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidStringVar(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWBBInvalidStringVar(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EWBBException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWBBInvalidStringVar() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdHTTPAppRequest : public Web::Httpapp::TWebRequest
{
	typedef Web::Httpapp::TWebRequest inherited;
	
protected:
	Idcustomhttpserver::TIdHTTPRequestInfo* FRequestInfo;
	Idcustomhttpserver::TIdHTTPResponseInfo* FResponseInfo;
	Idcontext::TIdContext* FThread;
	System::Classes::TStream* FContentStream;
	bool FFreeContentStream;
	virtual System::TDateTime __fastcall GetDateVariable(int Index);
	virtual int __fastcall GetIntegerVariable(int Index);
	virtual System::UnicodeString __fastcall GetStringVariable(int Index);
	virtual System::UnicodeString __fastcall GetRemoteIP();
	virtual System::UnicodeString __fastcall GetRawPathInfo();
#ifndef _WIN64
	virtual System::DynamicArray<System::Byte> __fastcall GetRawContent();
#else /* _WIN64 */
	virtual System::TArray__1<System::Byte> __fastcall GetRawContent();
#endif /* _WIN64 */
	
public:
	__fastcall TIdHTTPAppRequest(Idcontext::TIdContext* AThread, Idcustomhttpserver::TIdHTTPRequestInfo* ARequestInfo, Idcustomhttpserver::TIdHTTPResponseInfo* AResponseInfo);
	__fastcall virtual ~TIdHTTPAppRequest();
	virtual System::UnicodeString __fastcall GetFieldByName(const System::UnicodeString Name);
	virtual int __fastcall ReadClient(void *Buffer, int Count);
	virtual System::UnicodeString __fastcall ReadString(int Count);
	virtual System::UnicodeString __fastcall TranslateURI(const System::UnicodeString URI);
	virtual int __fastcall WriteClient(void *ABuffer, int ACount);
	virtual bool __fastcall WriteHeaders(int StatusCode, const System::UnicodeString ReasonString, const System::UnicodeString Headers);
	virtual bool __fastcall WriteString(const System::UnicodeString AString);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdHTTPAppResponse : public Web::Httpapp::TWebResponse
{
	typedef Web::Httpapp::TWebResponse inherited;
	
protected:
	System::UnicodeString FContent;
	Idcustomhttpserver::TIdHTTPRequestInfo* FRequestInfo;
	Idcustomhttpserver::TIdHTTPResponseInfo* FResponseInfo;
	bool FSent;
	Idcontext::TIdContext* FThread;
	System::UnicodeString FContentType;
	virtual System::UnicodeString __fastcall GetContent();
	virtual System::TDateTime __fastcall GetDateVariable(int Index);
	virtual int __fastcall GetStatusCode();
	virtual int __fastcall GetIntegerVariable(int Index);
	virtual System::UnicodeString __fastcall GetLogMessage();
	virtual System::UnicodeString __fastcall GetStringVariable(int Index);
	virtual void __fastcall SetContent(const System::UnicodeString AValue);
	virtual void __fastcall SetContentStream(System::Classes::TStream* AValue);
	virtual void __fastcall SetStatusCode(int AValue);
	virtual void __fastcall SetStringVariable(int Index, const System::UnicodeString Value);
	virtual void __fastcall SetDateVariable(int Index, const System::TDateTime Value);
	virtual void __fastcall SetIntegerVariable(int Index, int Value);
	virtual void __fastcall SetLogMessage(const System::UnicodeString Value);
	void __fastcall MoveCookiesAndCustomHeaders();
	
public:
	__fastcall TIdHTTPAppResponse(Web::Httpapp::TWebRequest* AHTTPRequest, Idcontext::TIdContext* AThread, Idcustomhttpserver::TIdHTTPRequestInfo* ARequestInfo, Idcustomhttpserver::TIdHTTPResponseInfo* AResponseInfo);
	virtual void __fastcall SendRedirect(const System::UnicodeString URI);
	virtual void __fastcall SendResponse();
	virtual void __fastcall SendStream(System::Classes::TStream* AStream);
	virtual bool __fastcall Sent();
public:
	/* TWebResponse.Destroy */ inline __fastcall virtual ~TIdHTTPAppResponse() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIdHTTPWebBrokerBridge : public Idcustomhttpserver::TIdCustomHTTPServer
{
	typedef Idcustomhttpserver::TIdCustomHTTPServer inherited;
	
private:
	void __fastcall RunWebModuleClass(Idcontext::TIdContext* AThread, Idcustomhttpserver::TIdHTTPRequestInfo* ARequestInfo, Idcustomhttpserver::TIdHTTPResponseInfo* AResponseInfo);
	
protected:
	System::Classes::TComponentClass FWebModuleClass;
	virtual void __fastcall DoCommandGet(Idcontext::TIdContext* AThread, Idcustomhttpserver::TIdHTTPRequestInfo* ARequestInfo, Idcustomhttpserver::TIdHTTPResponseInfo* AResponseInfo);
	virtual void __fastcall DoCommandOther(Idcontext::TIdContext* AThread, Idcustomhttpserver::TIdHTTPRequestInfo* ARequestInfo, Idcustomhttpserver::TIdHTTPResponseInfo* AResponseInfo);
	virtual void __fastcall InitComponent();
	
public:
	void __fastcall RegisterWebModuleClass(System::Classes::TComponentClass AClass);
public:
	/* TIdCustomHTTPServer.Create */ inline __fastcall TIdHTTPWebBrokerBridge(System::Classes::TComponent* AOwner)/* overload */ : Idcustomhttpserver::TIdCustomHTTPServer(AOwner) { }
	/* TIdCustomHTTPServer.Destroy */ inline __fastcall virtual ~TIdHTTPWebBrokerBridge() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdHTTPWebBrokerBridge()/* overload */ : Idcustomhttpserver::TIdCustomHTTPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idhttpwebbrokerbridge */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHTTPWEBBROKERBRIDGE)
using namespace Idhttpwebbrokerbridge;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdhttpwebbrokerbridgeHPP
