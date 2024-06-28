// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdZLib.pas' rev: 34.00 (iOS)

#ifndef IdzlibHPP
#define IdzlibHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <IdCTypes.hpp>
#include <IdGlobal.hpp>
#include <IdZLibHeaders.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idzlib
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomZlibStream;
class DELPHICLASS TCompressionStream;
class DELPHICLASS TDecompressionStream;
class DELPHICLASS EZlibError;
class DELPHICLASS ECompressionError;
class DELPHICLASS EDecompressionError;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomZlibStream : public Idglobal::TIdBaseStream
{
	typedef Idglobal::TIdBaseStream inherited;
	
protected:
	System::Classes::TStream* FStrm;
	int FStrmPos;
	System::Classes::TNotifyEvent FOnProgress;
	z_stream FZRec;
	System::StaticArray<char, 65536> FBuffer;
	System::StaticArray<char, 256> FNameBuffer;
	gz_header FGZHeader;
	Idzlibheaders::TZStreamType FStreamType;
	DYNAMIC void __fastcall Progress();
	virtual void __fastcall IdSetSize(__int64 ASize);
	__property System::Classes::TNotifyEvent OnProgress = {read=FOnProgress, write=FOnProgress};
	
public:
	__fastcall TCustomZlibStream(System::Classes::TStream* Strm);
	__fastcall virtual ~TCustomZlibStream();
	__property gz_header GZHeader = {read=FGZHeader};
};


enum DECLSPEC_DENUM TCompressionLevel : unsigned char { clNone, clFastest, clDefault, clMax };

class PASCALIMPLEMENTATION TCompressionStream : public TCustomZlibStream
{
	typedef TCustomZlibStream inherited;
	
protected:
	float __fastcall GetCompressionRate();
	virtual long __fastcall IdRead(Idglobal::TIdBytes &VBuffer, long AOffset, long ACount);
	virtual long __fastcall IdWrite(const Idglobal::TIdBytes ABuffer, long AOffset, long ACount);
	virtual __int64 __fastcall IdSeek(const __int64 AOffset, System::Classes::TSeekOrigin AOrigin);
	
public:
	__fastcall TCompressionStream(TCompressionLevel CompressionLevel, System::Classes::TStream* Dest, const Idzlibheaders::TZStreamType StreamType, const System::UnicodeString AName, int ATime);
	__fastcall TCompressionStream(TCompressionLevel CompressionLevel, System::Classes::TStream* Dest, const bool AIncludeHeaders);
	__fastcall TCompressionStream(TCompressionLevel CompressionLevel, System::Classes::TStream* Dest, const System::UnicodeString AName, int ATime)/* overload */;
	__fastcall virtual ~TCompressionStream();
	__property float CompressionRate = {read=GetCompressionRate};
	__property OnProgress;
};


class PASCALIMPLEMENTATION TDecompressionStream : public TCustomZlibStream
{
	typedef TCustomZlibStream inherited;
	
protected:
	__int64 FInitialPos;
	virtual long __fastcall IdRead(Idglobal::TIdBytes &VBuffer, long AOffset, long ACount);
	virtual long __fastcall IdWrite(const Idglobal::TIdBytes ABuffer, long AOffset, long ACount);
	virtual __int64 __fastcall IdSeek(const __int64 AOffset, System::Classes::TSeekOrigin AOrigin);
	
public:
	__fastcall TDecompressionStream(System::Classes::TStream* Source);
	__fastcall virtual ~TDecompressionStream();
	void __fastcall InitRead();
	bool __fastcall IsGZip();
	__property OnProgress;
};


class PASCALIMPLEMENTATION EZlibError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
protected:
	int FErrorCode;
	
public:
	__classmethod void __fastcall RaiseException(const int AError);
	__property int ErrorCode = {read=FErrorCode, nodefault};
public:
	/* Exception.Create */ inline __fastcall EZlibError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EZlibError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EZlibError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EZlibError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EZlibError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EZlibError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EZlibError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EZlibError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EZlibError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EZlibError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EZlibError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EZlibError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EZlibError() { }
	
};


class PASCALIMPLEMENTATION ECompressionError : public EZlibError
{
	typedef EZlibError inherited;
	
public:
	/* Exception.Create */ inline __fastcall ECompressionError(const System::UnicodeString Msg) : EZlibError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ECompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EZlibError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ECompressionError(NativeUInt Ident)/* overload */ : EZlibError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ECompressionError(System::PResStringRec ResStringRec)/* overload */ : EZlibError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ECompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EZlibError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ECompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EZlibError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ECompressionError(const System::UnicodeString Msg, int AHelpContext) : EZlibError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ECompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EZlibError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECompressionError(NativeUInt Ident, int AHelpContext)/* overload */ : EZlibError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECompressionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EZlibError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EZlibError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EZlibError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ECompressionError() { }
	
};


class PASCALIMPLEMENTATION EDecompressionError : public EZlibError
{
	typedef EZlibError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EDecompressionError(const System::UnicodeString Msg) : EZlibError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EDecompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EZlibError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDecompressionError(NativeUInt Ident)/* overload */ : EZlibError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDecompressionError(System::PResStringRec ResStringRec)/* overload */ : EZlibError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDecompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EZlibError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDecompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EZlibError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDecompressionError(const System::UnicodeString Msg, int AHelpContext) : EZlibError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDecompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EZlibError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDecompressionError(NativeUInt Ident, int AHelpContext)/* overload */ : EZlibError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDecompressionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EZlibError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDecompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EZlibError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDecompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EZlibError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDecompressionError() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int __fastcall CCheck(int code);
extern DELPHI_PACKAGE int __fastcall DCheck(int code);
extern DELPHI_PACKAGE void __fastcall CompressBuf(const void * InBuf, int InBytes, /* out */ void * &OutBuf, /* out */ unsigned &OutBytes);
extern DELPHI_PACKAGE Idzlibheaders::TZStreamType __fastcall GetStreamType(void * InBuffer, unsigned InCount, gz_headerp gzheader, /* out */ unsigned &HeaderSize)/* overload */;
extern DELPHI_PACKAGE Idzlibheaders::TZStreamType __fastcall GetStreamType(System::Classes::TStream* InStream, gz_headerp gzheader, /* out */ unsigned &HeaderSize)/* overload */;
extern DELPHI_PACKAGE void __fastcall DecompressStream(System::Classes::TStream* InStream, System::Classes::TStream* OutStream);
extern DELPHI_PACKAGE void __fastcall IndyDecompressStream(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, const int AWindowBits);
extern DELPHI_PACKAGE void __fastcall IndyCompressStream(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, const int level = 0xffffffff, const int WinBits = 0xf, const int MemLevel = 0x9, const int Stratagy = 0x0);
extern DELPHI_PACKAGE void __fastcall CompressStream(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, TCompressionLevel level, Idzlibheaders::TZStreamType StreamType);
extern DELPHI_PACKAGE void __fastcall CompressStreamEx(System::Classes::TStream* InStream, System::Classes::TStream* OutStream, TCompressionLevel level, Idzlibheaders::TZStreamType StreamType);
extern DELPHI_PACKAGE System::UnicodeString __fastcall CompressString(const System::UnicodeString InString, TCompressionLevel level, Idzlibheaders::TZStreamType StreamType);
extern DELPHI_PACKAGE void __fastcall DecompressBuf(const void * InBuf, int InBytes, int OutEstimate, /* out */ void * &OutBuf, /* out */ int &OutBytes);
extern DELPHI_PACKAGE void __fastcall DecompressToUserBuf(const void * InBuf, int InBytes, const void * OutBuf, int BufSize);
}	/* namespace Idzlib */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDZLIB)
using namespace Idzlib;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdzlibHPP
