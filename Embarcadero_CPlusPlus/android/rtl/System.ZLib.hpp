// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.ZLib.pas' rev: 34.00 (Android)

#ifndef System_ZlibHPP
#define System_ZlibHPP

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

namespace System
{
namespace Zlib
{
//-- forward type declarations -----------------------------------------------
struct DECLSPEC_DRECORD internal_state
{
};


struct z_stream;
struct gz_header;
class DELPHICLASS TCustomZStream;
class DELPHICLASS TZCompressionStream;
class DELPHICLASS TZDecompressionStream;
class DELPHICLASS EZLibError;
class DELPHICLASS EZCompressionError;
class DELPHICLASS EZDecompressionError;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
typedef int z_off_t;
#else /* __aarch64__ */
typedef long z_off_t;
#endif /* __aarch64__ */

typedef __int64 z_off64_t;

typedef internal_state *Pinternal_state;

typedef void * __cdecl (*alloc_func)(void * opaque, unsigned Items, unsigned Size);

typedef void __cdecl (*free_func)(void * opaque, void * address);

struct DECLSPEC_DRECORD z_stream
{
public:
	System::Byte *next_in;
	unsigned avail_in;
#ifndef __aarch64__
	unsigned total_in;
#else /* __aarch64__ */
	unsigned long total_in;
#endif /* __aarch64__ */
	System::Byte *next_out;
	unsigned avail_out;
#ifndef __aarch64__
	unsigned total_out;
#else /* __aarch64__ */
	unsigned long total_out;
#endif /* __aarch64__ */
	char *msg;
	internal_state *state;
	alloc_func zalloc;
	free_func zfree;
	void *opaque;
	int data_type;
#ifndef __aarch64__
	unsigned adler;
	unsigned reserved;
#else /* __aarch64__ */
	unsigned long adler;
	unsigned long reserved;
#endif /* __aarch64__ */
};


typedef z_stream z_stream_s;

typedef z_stream *z_streamp;

struct DECLSPEC_DRECORD gz_header
{
public:
	int text;
#ifndef __aarch64__
	unsigned time;
#else /* __aarch64__ */
	unsigned long time;
#endif /* __aarch64__ */
	int xflags;
	int os;
	System::Byte *extra;
	unsigned extra_len;
	unsigned extra_max;
	char *name;
	unsigned name_max;
	char *comment;
	unsigned comm_max;
	int hcrc;
	int done;
};


typedef gz_header gz_header_s;

typedef gz_header *gz_headerp;

typedef unsigned __fastcall (*in_func)(void * in_desc, System::PByte &buf);

typedef int __fastcall (*out_func)(void * out_desc, System::PByte buf, unsigned length);

typedef void * gzFile;

typedef alloc_func TZAlloc;

typedef free_func TZFree;

enum DECLSPEC_DENUM TZCompressionLevel : unsigned char { zcNone, zcFastest, zcDefault, zcMax };

enum DECLSPEC_DENUM TCompressionLevel : unsigned char { clNone, clFastest, clDefault, clMax };

typedef z_stream TZStreamRec;

class PASCALIMPLEMENTATION TCustomZStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	System::Classes::TStream* FStream;
	__int64 FStreamStartPos;
	__int64 FStreamPos;
	System::Classes::TNotifyEvent FOnProgress;
	z_stream FZStream;
	System::TArray__1<System::Byte> FBuffer;
	
protected:
	__fastcall TCustomZStream(System::Classes::TStream* stream);
	DYNAMIC void __fastcall DoProgress();
	__property System::Classes::TNotifyEvent OnProgress = {read=FOnProgress, write=FOnProgress};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomZStream() { }
	
};


typedef TCustomZStream TCustomZLibStream;

class PASCALIMPLEMENTATION TZCompressionStream : public TCustomZStream
{
	typedef TCustomZStream inherited;
	
private:
	float __fastcall GetCompressionRate();
	
public:
	__fastcall TZCompressionStream(System::Classes::TStream* dest)/* overload */;
	__fastcall TZCompressionStream(System::Classes::TStream* dest, TZCompressionLevel compressionLevel, int windowBits)/* overload */;
	__fastcall TZCompressionStream(TCompressionLevel compressionLevel, System::Classes::TStream* dest)/* overload */;
	__fastcall virtual ~TZCompressionStream();
#ifndef __aarch64__
	virtual int __fastcall Read(void *buffer, int count)/* overload */;
	virtual int __fastcall Write(const void *buffer, int count)/* overload */;
	virtual int __fastcall Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count)/* overload */;
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count)/* overload */;
#else /* __aarch64__ */
	virtual long __fastcall Read(void *buffer, long count)/* overload */;
	virtual long __fastcall Write(const void *buffer, long count)/* overload */;
	virtual long __fastcall Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
	virtual long __fastcall Write(const System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
#endif /* __aarch64__ */
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	__property float CompressionRate = {read=GetCompressionRate};
	__property OnProgress;
	/* Hoisted overloads: */
	
public:
#ifndef __aarch64__
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
	inline int __fastcall  Seek(int Offset, System::Word Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
#else /* __aarch64__ */
	inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Count){ return System::Classes::TStream::Write(Buffer, Count); }
	inline long __fastcall  Seek(long Offset, System::Word Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
#endif /* __aarch64__ */
	
};


typedef TZCompressionStream TCompressionStream;

class PASCALIMPLEMENTATION TZDecompressionStream : public TCustomZStream
{
	typedef TCustomZStream inherited;
	
private:
	bool FOwnsStream;
	
public:
	__fastcall TZDecompressionStream(System::Classes::TStream* source)/* overload */;
	__fastcall TZDecompressionStream(System::Classes::TStream* source, int WindowBits)/* overload */;
	__fastcall TZDecompressionStream(System::Classes::TStream* source, int WindowBits, bool OwnsStream)/* overload */;
	__fastcall virtual ~TZDecompressionStream();
#ifndef __aarch64__
	virtual int __fastcall Read(void *buffer, int count)/* overload */;
	virtual int __fastcall Write(const void *buffer, int count)/* overload */;
	virtual int __fastcall Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count)/* overload */;
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count)/* overload */;
#else /* __aarch64__ */
	virtual long __fastcall Read(void *buffer, long count)/* overload */;
	virtual long __fastcall Write(const void *buffer, long count)/* overload */;
	virtual long __fastcall Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
	virtual long __fastcall Write(const System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
#endif /* __aarch64__ */
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	__property OnProgress;
	/* Hoisted overloads: */
	
public:
#ifndef __aarch64__
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
	inline int __fastcall  Seek(int Offset, System::Word Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
#else /* __aarch64__ */
	inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Count){ return System::Classes::TStream::Write(Buffer, Count); }
	inline long __fastcall  Seek(long Offset, System::Word Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
#endif /* __aarch64__ */
	
};


typedef TZDecompressionStream TDecompressionStream;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EZLibError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EZLibError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EZLibError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EZLibError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EZLibError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EZLibError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EZLibError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EZLibError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EZLibError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EZLibError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EZLibError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EZLibError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EZLibError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EZLibError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EZCompressionError : public EZLibError
{
	typedef EZLibError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EZCompressionError(const System::UnicodeString Msg) : EZLibError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EZCompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EZLibError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EZCompressionError(NativeUInt Ident)/* overload */ : EZLibError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EZCompressionError(System::PResStringRec ResStringRec)/* overload */ : EZLibError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EZCompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EZLibError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EZCompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EZLibError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EZCompressionError(const System::UnicodeString Msg, int AHelpContext) : EZLibError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EZCompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EZLibError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EZCompressionError(NativeUInt Ident, int AHelpContext)/* overload */ : EZLibError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EZCompressionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EZLibError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EZCompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EZLibError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EZCompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EZLibError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EZCompressionError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EZDecompressionError : public EZLibError
{
	typedef EZLibError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EZDecompressionError(const System::UnicodeString Msg) : EZLibError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EZDecompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EZLibError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EZDecompressionError(NativeUInt Ident)/* overload */ : EZLibError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EZDecompressionError(System::PResStringRec ResStringRec)/* overload */ : EZLibError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EZDecompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EZLibError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EZDecompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EZLibError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EZDecompressionError(const System::UnicodeString Msg, int AHelpContext) : EZLibError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EZDecompressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EZLibError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EZDecompressionError(NativeUInt Ident, int AHelpContext)/* overload */ : EZLibError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EZDecompressionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EZLibError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EZDecompressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EZLibError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EZDecompressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EZLibError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EZDecompressionError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE char *ZLIB_VERSION;
static constexpr System::Word ZLIB_VERNUM = System::Word(0x12b0);
static constexpr System::Int8 ZLIB_VER_MAJOR = System::Int8(0x1);
static constexpr System::Int8 ZLIB_VER_MINOR = System::Int8(0x2);
static constexpr System::Int8 ZLIB_VER_REVSION = System::Int8(0xb);
static constexpr System::Int8 ZLIB_VER_SUBREVISION = System::Int8(0x0);
static constexpr System::Int8 Z_NO_FLUSH = System::Int8(0x0);
static constexpr System::Int8 Z_PARTIAL_FLUSH = System::Int8(0x1);
static constexpr System::Int8 Z_SYNC_FLUSH = System::Int8(0x2);
static constexpr System::Int8 Z_FULL_FLUSH = System::Int8(0x3);
static constexpr System::Int8 Z_FINISH = System::Int8(0x4);
static constexpr System::Int8 Z_BLOCK = System::Int8(0x5);
static constexpr System::Int8 Z_TREES = System::Int8(0x6);
static constexpr System::Int8 Z_OK = System::Int8(0x0);
static constexpr System::Int8 Z_STREAM_END = System::Int8(0x1);
static constexpr System::Int8 Z_NEED_DICT = System::Int8(0x2);
static constexpr System::Int8 Z_ERRNO = System::Int8(-1);
static constexpr System::Int8 Z_STREAM_ERROR = System::Int8(-2);
static constexpr System::Int8 Z_DATA_ERROR = System::Int8(-3);
static constexpr System::Int8 Z_MEM_ERROR = System::Int8(-4);
static constexpr System::Int8 Z_BUF_ERROR = System::Int8(-5);
static constexpr System::Int8 Z_VERSION_ERROR = System::Int8(-6);
static constexpr System::Int8 Z_NO_COMPRESSION = System::Int8(0x0);
static constexpr System::Int8 Z_BEST_SPEED = System::Int8(0x1);
static constexpr System::Int8 Z_BEST_COMPRESSION = System::Int8(0x9);
static constexpr System::Int8 Z_DEFAULT_COMPRESSION = System::Int8(-1);
static constexpr System::Int8 Z_FILTERED = System::Int8(0x1);
static constexpr System::Int8 Z_HUFFMAN_ONLY = System::Int8(0x2);
static constexpr System::Int8 Z_RLE = System::Int8(0x3);
static constexpr System::Int8 Z_FIXED = System::Int8(0x4);
static constexpr System::Int8 Z_DEFAULT_STRATEGY = System::Int8(0x0);
static constexpr System::Int8 Z_BINARY = System::Int8(0x0);
static constexpr System::Int8 Z_TEXT = System::Int8(0x1);
static constexpr System::Int8 Z_ASCII = System::Int8(0x1);
static constexpr System::Int8 Z_UNKNOWN = System::Int8(0x2);
static constexpr System::Int8 Z_DEFLATED = System::Int8(0x8);
static constexpr System::Int8 Z_NULL = System::Int8(0x0);
extern "C" char * __cdecl zlibVersion(void);
extern "C" int __cdecl deflate(z_stream &strm, int flush);
extern "C" int __cdecl deflateEnd(z_stream &strm);
extern "C" int __cdecl inflate(z_stream &strm, int flush);
extern "C" int __cdecl inflateEnd(z_stream &strm);
extern "C" int __cdecl deflateSetDictionary(z_stream &strm, System::PByte dictionary, unsigned dictLength);
extern "C" int __cdecl deflateCopy(z_stream &dest, const z_stream source);
extern "C" int __cdecl deflateReset(z_stream &strm);
extern "C" int __cdecl deflateParams(z_stream &strm, int level, int strategy);
extern "C" int __cdecl deflateTune(z_stream &strm, int good_length, int max_lazy, int nice_length, int max_chain);
#ifndef __aarch64__
extern "C" unsigned __cdecl deflateBound(z_stream &strm, unsigned sourceLen);
#else /* __aarch64__ */
extern "C" unsigned long __cdecl deflateBound(z_stream &strm, unsigned sourceLen);
#endif /* __aarch64__ */
extern "C" int __cdecl deflatePrime(z_stream &strm, int bits, int value);
extern "C" int __cdecl deflateSetHeader(z_stream &strm, gz_header &head);
extern "C" int __cdecl inflateSetDictionary(z_stream &strm, System::PByte dictionary, unsigned dictLength);
extern "C" int __cdecl inflateSync(z_stream &strm);
extern "C" int __cdecl inflateCopy(z_stream &dest, z_stream &source);
extern "C" int __cdecl inflateReset(z_stream &strm);
extern "C" int __cdecl inflatePrime(z_stream &strm, int bits, int value);
extern "C" int __cdecl inflateGetHeader(z_stream &strm, gz_header &head);
extern "C" int __cdecl inflateBack(z_stream &strm, in_func in_, void * in_desc, out_func out_, void * out_desc);
extern "C" int __cdecl inflateBackEnd(z_stream &strm);
#ifndef __aarch64__
extern "C" unsigned __cdecl zlibCompileFlags(void);
extern "C" int __cdecl compress(System::PByte dest, unsigned &destLen, System::PByte source, unsigned sourceLen);
extern "C" int __cdecl compress2(System::PByte dest, unsigned &destLen, System::PByte source, unsigned sourceLen, int level);
extern "C" unsigned __cdecl compressBound(unsigned sourceLen);
extern "C" int __cdecl uncompress(System::PByte dest, unsigned &destLen, System::PByte source, unsigned sourceLen);
#else /* __aarch64__ */
extern "C" unsigned long __cdecl zlibCompileFlags(void);
extern "C" int __cdecl compress(System::PByte dest, unsigned long &destLen, System::PByte source, unsigned long sourceLen);
extern "C" int __cdecl compress2(System::PByte dest, unsigned long &destLen, System::PByte source, unsigned long sourceLen, int level);
extern "C" unsigned long __cdecl compressBound(unsigned long sourceLen);
extern "C" int __cdecl uncompress(System::PByte dest, unsigned long &destLen, System::PByte source, unsigned long sourceLen);
#endif /* __aarch64__ */
extern "C" void * __cdecl gzdopen(int fd, char * mode);
extern "C" int __cdecl gzsetparams(void * file_, int level, int strategy);
extern "C" int __cdecl gzread(void * file_, const void *buf, unsigned len);
extern "C" int __cdecl gzwrite(void * file_, const void *buf, unsigned len);
extern "C" int __cdecl gzprintf(void * file_, char * format, ...);
extern "C" int __cdecl gzputs(void * file_, char * s);
extern "C" char * __cdecl gzgets(void * file_, char * buf, int len);
extern "C" int __cdecl gzputc(void * file_, int c);
extern "C" int __cdecl gzgetc(void * file_);
extern "C" int __cdecl gzungetc(int c, void * file_);
extern "C" int __cdecl gzflush(void * file_, int flush);
extern "C" int __cdecl gzrewind(void * file_);
extern "C" int __cdecl gzeof(void * file_);
extern "C" int __cdecl gzdirect(void * file_);
extern "C" int __cdecl gzclose(void * file_);
extern "C" char * __cdecl gzerror(void * file_, int &errnum);
extern "C" void __cdecl gzclearerr(void * file_);
#ifndef __aarch64__
extern "C" unsigned __cdecl adler32(unsigned adler, System::PByte buf, unsigned len);
#else /* __aarch64__ */
extern "C" unsigned long __cdecl adler32(unsigned long adler, System::PByte buf, unsigned len);
#endif /* __aarch64__ */
extern "C" unsigned __cdecl crc32(unsigned crc, System::PByte buf, unsigned len);
extern "C" int __cdecl deflateInit_(z_stream &strm, int level, char * version, int stream_size);
extern "C" int __cdecl inflateInit_(z_stream &strm, char * version, int stream_size);
extern "C" int __cdecl deflateInit2_(z_stream &strm, int level, int method, int windowBits, int memLevel, int strategy, char * version, int stream_size);
extern "C" int __cdecl inflateInit2_(z_stream &strm, int windowBits, char * version, int stream_size);
extern "C" int __cdecl inflateBackInit_(z_stream &strm, int windowBits, System::PByte window, char * version, int stream_size);
extern "C" void * __cdecl gzopen(char * path, char * mode);
#ifndef __aarch64__
extern "C" int __cdecl gzseek(void * file_, int offset, int flush);
extern "C" int __cdecl gztell(void * file_);
extern "C" unsigned __cdecl adler32_combine(unsigned adler1, unsigned adler2, int len2);
extern "C" unsigned __cdecl crc32_combine(unsigned crc1, unsigned crc2, int len2);
#else /* __aarch64__ */
extern "C" long __cdecl gzseek(void * file_, long offset, int flush);
extern "C" long __cdecl gztell(void * file_);
extern "C" unsigned long __cdecl adler32_combine(unsigned long adler1, unsigned long adler2, long len2);
extern "C" unsigned long __cdecl crc32_combine(unsigned long crc1, unsigned long crc2, long len2);
#endif /* __aarch64__ */
extern "C" char * __cdecl zError(int Err);
extern "C" int __cdecl inflateSyncPoint(z_streamp stream);
extern "C" System::PLongWord __cdecl get_crc_table(void);
extern DELPHI_PACKAGE System::StaticArray<char *, 10> _z_errmsg;
extern DELPHI_PACKAGE System::StaticArray<System::Int8, 4> ZLevels;
#define SZInvalid u"Invalid ZStream operation!"
extern DELPHI_PACKAGE int __fastcall deflateInit(z_stream &strm, int level);
extern DELPHI_PACKAGE int __fastcall inflateInit(z_stream &strm);
extern DELPHI_PACKAGE int __fastcall deflateInit2(z_stream &strm, int level, int method, int windowBits, int memLevel, int strategy);
extern DELPHI_PACKAGE int __fastcall inflateInit2(z_stream &strm, int windowBits);
extern DELPHI_PACKAGE int __fastcall inflateBackInit(z_stream &strm, int windowBits, System::PByte window);
extern DELPHI_PACKAGE void __fastcall MoveI32 _DEPRECATED_ATTRIBUTE1("use System.Move") (const void *Source, void *Dest, int Count);
extern DELPHI_PACKAGE void __fastcall ZCompress(const void * inBuffer, int inSize, /* out */ void * &outBuffer, /* out */ int &outSize, TZCompressionLevel level = (TZCompressionLevel)(0x2))/* overload */;
extern DELPHI_PACKAGE void __fastcall ZCompress(const void * inBuffer, int inSize, /* out */ void * &outBuffer, /* out */ int &outSize, TCompressionLevel level)/* overload */;
extern DELPHI_PACKAGE void __fastcall ZCompress(const System::TArray__1<System::Byte> inBuffer, /* out */ System::TArray__1<System::Byte> &outBuffer, TZCompressionLevel level = (TZCompressionLevel)(0x2))/* overload */;
extern DELPHI_PACKAGE void __fastcall ZDecompress(const void * inBuffer, int inSize, /* out */ void * &outBuffer, /* out */ int &outSize, int outEstimate = 0x0)/* overload */;
extern DELPHI_PACKAGE void __fastcall ZDecompress(const System::TArray__1<System::Byte> inBuffer, /* out */ System::TArray__1<System::Byte> &outBuffer, int outEstimate = 0x0)/* overload */;
extern DELPHI_PACKAGE System::TArray__1<System::Byte> __fastcall ZCompressStr(const System::UnicodeString s, TZCompressionLevel level = (TZCompressionLevel)(0x2))/* overload */;
extern DELPHI_PACKAGE System::TArray__1<System::Byte> __fastcall ZCompressStr(const System::UnicodeString s, TCompressionLevel level)/* overload */;
extern DELPHI_PACKAGE void __fastcall ZSendToBrowser(System::UnicodeString &s);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ZDecompressStr(const System::TArray__1<System::Byte> s);
extern DELPHI_PACKAGE void __fastcall ZCompressStream(System::Classes::TStream* inStream, System::Classes::TStream* outStream, TZCompressionLevel level = (TZCompressionLevel)(0x2))/* overload */;
extern DELPHI_PACKAGE void __fastcall ZCompressStream(System::Classes::TStream* inStream, System::Classes::TStream* outStream, TCompressionLevel level)/* overload */;
extern DELPHI_PACKAGE void __fastcall ZDecompressStream(System::Classes::TStream* inStream, System::Classes::TStream* outStream);
extern DELPHI_PACKAGE void * __cdecl zlibAllocMem(void * AppData, unsigned Items, unsigned Size);
extern DELPHI_PACKAGE void __cdecl zlibFreeMem(void * AppData, void * Block);
}	/* namespace Zlib */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ZLIB)
using namespace System::Zlib;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_ZlibHPP
