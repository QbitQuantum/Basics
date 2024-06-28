// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdCompressionIntercept.pas' rev: 34.00 (Windows)

#ifndef IdcompressioninterceptHPP
#define IdcompressioninterceptHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdException.hpp>
#include <IdGlobal.hpp>
#include <IdGlobalProtocols.hpp>
#include <IdIntercept.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdZLibHeaders.hpp>
#include <IdZLib.hpp>
#include <System.SysUtils.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idcompressionintercept
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdCompressionException;
class DELPHICLASS EIdCompressorInitFailure;
class DELPHICLASS EIdDecompressorInitFailure;
class DELPHICLASS EIdCompressionError;
class DELPHICLASS EIdDecompressionError;
class DELPHICLASS TIdCompressionIntercept;
class DELPHICLASS TIdServerCompressionIntercept;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdCompressionException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdCompressionException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdCompressionException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdCompressionException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdCompressionException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCompressionException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCompressionException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdCompressionException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdCompressionException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCompressionException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCompressionException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCompressionException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCompressionException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdCompressionException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdCompressorInitFailure : public EIdCompressionException
{
	typedef EIdCompressionException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdCompressorInitFailure(const System::UnicodeString AMsg)/* overload */ : EIdCompressionException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdCompressorInitFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdCompressionException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdCompressorInitFailure(NativeUInt Ident)/* overload */ : EIdCompressionException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdCompressorInitFailure(System::PResStringRec ResStringRec)/* overload */ : EIdCompressionException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCompressorInitFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdCompressionException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCompressorInitFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdCompressionException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdCompressorInitFailure(const System::UnicodeString Msg, int AHelpContext) : EIdCompressionException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdCompressorInitFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdCompressionException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCompressorInitFailure(NativeUInt Ident, int AHelpContext)/* overload */ : EIdCompressionException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCompressorInitFailure(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdCompressionException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCompressorInitFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdCompressionException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCompressorInitFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdCompressionException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdCompressorInitFailure() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdDecompressorInitFailure : public EIdCompressionException
{
	typedef EIdCompressionException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdDecompressorInitFailure(const System::UnicodeString AMsg)/* overload */ : EIdCompressionException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdDecompressorInitFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdCompressionException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdDecompressorInitFailure(NativeUInt Ident)/* overload */ : EIdCompressionException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdDecompressorInitFailure(System::PResStringRec ResStringRec)/* overload */ : EIdCompressionException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDecompressorInitFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdCompressionException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDecompressorInitFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdCompressionException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdDecompressorInitFailure(const System::UnicodeString Msg, int AHelpContext) : EIdCompressionException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdDecompressorInitFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdCompressionException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDecompressorInitFailure(NativeUInt Ident, int AHelpContext)/* overload */ : EIdCompressionException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDecompressorInitFailure(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdCompressionException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDecompressorInitFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdCompressionException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDecompressorInitFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdCompressionException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdDecompressorInitFailure() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdCompressionError : public EIdCompressionException
{
	typedef EIdCompressionException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdCompressionError(const System::UnicodeString AMsg)/* overload */ : EIdCompressionException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdCompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdCompressionException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdCompressionError(NativeUInt Ident)/* overload */ : EIdCompressionException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdCompressionError(System::PResStringRec ResStringRec)/* overload */ : EIdCompressionException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdCompressionException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdCompressionException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdCompressionError(const System::UnicodeString Msg, int AHelpContext) : EIdCompressionException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdCompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdCompressionException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCompressionError(NativeUInt Ident, int AHelpContext)/* overload */ : EIdCompressionException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCompressionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdCompressionException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdCompressionException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdCompressionException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdCompressionError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdDecompressionError : public EIdCompressionException
{
	typedef EIdCompressionException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdDecompressionError(const System::UnicodeString AMsg)/* overload */ : EIdCompressionException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdDecompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdCompressionException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdDecompressionError(NativeUInt Ident)/* overload */ : EIdCompressionException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdDecompressionError(System::PResStringRec ResStringRec)/* overload */ : EIdCompressionException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDecompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdCompressionException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDecompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdCompressionException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdDecompressionError(const System::UnicodeString Msg, int AHelpContext) : EIdCompressionException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdDecompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdCompressionException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDecompressionError(NativeUInt Ident, int AHelpContext)/* overload */ : EIdCompressionException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDecompressionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdCompressionException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDecompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdCompressionException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDecompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdCompressionException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdDecompressionError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::Int8 TIdCompressionLevel;

class PASCALIMPLEMENTATION TIdCompressionIntercept : public Idintercept::TIdConnectionIntercept
{
	typedef Idintercept::TIdConnectionIntercept inherited;
	
protected:
	TIdCompressionLevel FCompressionLevel;
	z_stream FCompressRec;
	z_stream FDecompressRec;
	Idglobal::TIdBytes FRecvBuf;
	unsigned FRecvCount;
	unsigned FRecvSize;
	Idglobal::TIdBytes FSendBuf;
	unsigned FSendCount;
	unsigned FSendSize;
	void __fastcall SetCompressionLevel(TIdCompressionLevel Value);
	void __fastcall InitCompressors();
	void __fastcall DeinitCompressors();
	
public:
	__fastcall virtual ~TIdCompressionIntercept();
	virtual void __fastcall Disconnect();
	virtual void __fastcall Receive(Idglobal::TIdBytes &VBuffer);
	virtual void __fastcall Send(Idglobal::TIdBytes &VBuffer);
	
__published:
	__property TIdCompressionLevel CompressionLevel = {read=FCompressionLevel, write=SetCompressionLevel, nodefault};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdCompressionIntercept(System::Classes::TComponent* AOwner)/* overload */ : Idintercept::TIdConnectionIntercept(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdCompressionIntercept()/* overload */ : Idintercept::TIdConnectionIntercept() { }
	
};


class PASCALIMPLEMENTATION TIdServerCompressionIntercept : public Idintercept::TIdServerIntercept
{
	typedef Idintercept::TIdServerIntercept inherited;
	
protected:
	TIdCompressionLevel FCompressionLevel;
	
public:
	virtual void __fastcall Init();
	virtual Idintercept::TIdConnectionIntercept* __fastcall Accept(System::Classes::TComponent* AConnection);
	
__published:
	__property TIdCompressionLevel CompressionLevel = {read=FCompressionLevel, write=FCompressionLevel, nodefault};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdServerCompressionIntercept(System::Classes::TComponent* AOwner)/* overload */ : Idintercept::TIdServerIntercept(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdServerCompressionIntercept()/* overload */ : Idintercept::TIdServerIntercept() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdServerCompressionIntercept() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idcompressionintercept */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDCOMPRESSIONINTERCEPT)
using namespace Idcompressionintercept;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdcompressioninterceptHPP
