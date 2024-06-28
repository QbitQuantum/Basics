// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.OBufferedStreams.pas' rev: 34.00 (iOS)

#ifndef Xml_Internal_ObufferedstreamsHPP
#define Xml_Internal_ObufferedstreamsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Obufferedstreams
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TOBufferedWriteStream;
class DELPHICLASS TOBufferedReadStream;
class DELPHICLASS EOBufferedWriteStream;
class DELPHICLASS EOBufferedReadStream;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TOBufferedWriteStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	System::Classes::TStream* fStream;
	NativeInt fStreamPosition;
	NativeInt fStreamSize;
	System::TArray__1<System::Byte> fTempBuffer;
	NativeInt fTempBufferUsedLength;
	NativeInt fBufferSize;
	
protected:
	virtual __int64 __fastcall GetSize();
	
public:
	__fastcall TOBufferedWriteStream(System::Classes::TStream* const aStream, const NativeInt aBufferSize);
	__fastcall virtual ~TOBufferedWriteStream();
	virtual long __fastcall Write(const void *Buffer, long Count)/* overload */;
	virtual long __fastcall Write(const System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
	virtual long __fastcall Read(void *Buffer, long Count)/* overload */;
	virtual long __fastcall Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	void __fastcall EnsureTempBufferWritten();
	/* Hoisted overloads: */
	
public:
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Count){ return System::Classes::TStream::Write(Buffer, Count); }
	inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline long __fastcall  Seek(long Offset, System::Word Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
	
};


class PASCALIMPLEMENTATION TOBufferedReadStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	System::Classes::TStream* fStream;
	NativeInt fStreamPosition;
	NativeInt fStreamSize;
	System::TArray__1<System::Byte> fTempBuffer;
	NativeInt fTempBufferPosition;
	NativeInt fTempBufferUsedLength;
	int fBlockFlushTempBuffer;
	NativeInt fBufferSize;
	void __fastcall CheckTempBuffer();
	
protected:
	virtual __int64 __fastcall GetSize();
	
public:
	__fastcall TOBufferedReadStream(System::Classes::TStream* const aStream, const NativeInt aBufferSize);
	virtual long __fastcall Write(const void *Buffer, long Count)/* overload */;
	virtual long __fastcall Write(const System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
	virtual long __fastcall Read(void *Buffer, long Count)/* overload */;
	virtual long __fastcall Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	void __fastcall BlockFlushTempBuffer();
	void __fastcall UnblockFlushTempBuffer();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TOBufferedReadStream() { }
	
	/* Hoisted overloads: */
	
public:
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Count){ return System::Classes::TStream::Write(Buffer, Count); }
	inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline long __fastcall  Seek(long Offset, System::Word Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
	
};


class PASCALIMPLEMENTATION EOBufferedWriteStream : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EOBufferedWriteStream(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EOBufferedWriteStream(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EOBufferedWriteStream(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EOBufferedWriteStream(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EOBufferedWriteStream(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EOBufferedWriteStream(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EOBufferedWriteStream(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EOBufferedWriteStream(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EOBufferedWriteStream(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EOBufferedWriteStream(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EOBufferedWriteStream(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EOBufferedWriteStream(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EOBufferedWriteStream() { }
	
};


class PASCALIMPLEMENTATION EOBufferedReadStream : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EOBufferedReadStream(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EOBufferedReadStream(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EOBufferedReadStream(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EOBufferedReadStream(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EOBufferedReadStream(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EOBufferedReadStream(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EOBufferedReadStream(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EOBufferedReadStream(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EOBufferedReadStream(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EOBufferedReadStream(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EOBufferedReadStream(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EOBufferedReadStream(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EOBufferedReadStream() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word OBUFFEREDSTREAMS_DEFBUFFERSIZE = System::Word(0x4000);
static constexpr System::Word OBUFFEREDSTREAMS_DEFCHARBUFFERSIZE = System::Word(0x2000);
}	/* namespace Obufferedstreams */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_OBUFFEREDSTREAMS)
using namespace Xml::Internal::Obufferedstreams;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL)
using namespace Xml::Internal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Internal_ObufferedstreamsHPP
