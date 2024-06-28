// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdCompressorZLib.pas' rev: 34.00 (Windows)

#ifndef IdcompressorzlibHPP
#define IdcompressorzlibHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdException.hpp>
#include <IdIOHandler.hpp>
#include <IdZLibCompressorBase.hpp>
#include <IdZLibHeaders.hpp>
#include <IdBaseComponent.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idcompressorzlib
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdCompressorZLib;
class DELPHICLASS EIdCompressionException;
class DELPHICLASS EIdCompressorInitFailure;
class DELPHICLASS EIdDecompressorInitFailure;
class DELPHICLASS EIdCompressionError;
class DELPHICLASS EIdDecompressionError;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdCompressorZLib : public Idzlibcompressorbase::TIdZLibCompressorBase
{
	typedef Idzlibcompressorbase::TIdZLibCompressorBase inherited;
	
protected:
	virtual bool __fastcall GetIsReady();
	void __fastcall InternalDecompressStream(const z_stream &LZstream, Idiohandler::TIdIOHandler* AIOHandler, System::Classes::TStream* AOutStream);
	
public:
	virtual void __fastcall DeflateStream(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream, const Idzlibcompressorbase::TIdCompressionLevel ALevel = (Idzlibcompressorbase::TIdCompressionLevel)(0x0));
	virtual void __fastcall InflateStream(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream);
	virtual void __fastcall CompressStream(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream, const Idzlibcompressorbase::TIdCompressionLevel ALevel, const int AWindowBits, const int AMemLevel, const int AStrategy);
	virtual void __fastcall DecompressStream(System::Classes::TStream* AInStream, System::Classes::TStream* AOutStream, const int AWindowBits);
	virtual void __fastcall CompressFTPToIO(System::Classes::TStream* AInStream, Idiohandler::TIdIOHandler* AIOHandler, const int ALevel, const int AWindowBits, const int AMemLevel, const int AStrategy);
	virtual void __fastcall DecompressFTPFromIO(Idiohandler::TIdIOHandler* AIOHandler, System::Classes::TStream* AOutputStream, const int AWindowBits);
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdCompressorZLib(System::Classes::TComponent* AOwner)/* overload */ : Idzlibcompressorbase::TIdZLibCompressorBase(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdCompressorZLib()/* overload */ : Idzlibcompressorbase::TIdZLibCompressorBase() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdCompressorZLib() { }
	
};


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

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idcompressorzlib */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDCOMPRESSORZLIB)
using namespace Idcompressorzlib;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdcompressorzlibHPP
