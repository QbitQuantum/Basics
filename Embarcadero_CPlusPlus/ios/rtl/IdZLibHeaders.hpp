// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdZLibHeaders.pas' rev: 34.00 (iOS)

#ifndef IdzlibheadersHPP
#define IdzlibheadersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.SysTypes.hpp>
#include <IdGlobal.hpp>
#include <IdCTypes.hpp>
#include <IdException.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
#define ZEXPORT __cdecl
#define ZEXPORTVA __cdecl
#if !defined(__MACTYPES__)
  // We are defining __MACTYPES__ in order to skip the declaration of "Byte" as it causes
  // ambiguity with System::Byte
  #define __MACTYPES__
  #define __REMOVE_MACTYPES__
#endif
#if defined(__USE_ZLIBH__)
  #include "ZLib\zlib.h"
#else
typedef void * __cdecl (*alloc_func)(void * opaque, unsigned items, unsigned size);

typedef void __cdecl (*free_func)(void * opaque, void * address);

struct DECLSPEC_DRECORD z_stream
{
	
public:
	char *next_in;
	unsigned avail_in;
	unsigned long total_in;
	char *next_out;
	unsigned avail_out;
	unsigned long total_out;
	char *msg;
	void *state;
	alloc_func zalloc;
	free_func zfree;
	void *opaque;
	int data_type;
	unsigned long adler;
	unsigned long reserved;
};

#if !defined(__clang__) && !defined(__CPP__)
#if sizeof(z_stream) < 56
#pragma message "Pascal/C++ size mismatch: (C++) sizeof(z_stream) < (Pascal) [size: 56, align: 1] (WARNING)"
#pragma sizeof(z_stream)
#endif

#if sizeof(z_stream) > 56
#pragma message "Pascal/C++ size mismatch: (C++) sizeof(z_stream) > (Pascal) [size: 56, align: 1] (WARNING)"
#pragma sizeof(z_stream)
#endif

#if alignof(z_stream) < 1
#pragma message "Pascal/C++ alignment mismatch: (C++) alignof(z_stream) < (Pascal) [size: 56, align: 1] (WARNING)"
#endif

#if alignof(z_stream) > 1
#pragma message "Pascal/C++ alignment mismatch: (C++) alignof(z_stream) > (Pascal) [size: 56, align: 1] (WARNING)"
#endif
#endif


struct gz_header;
typedef gz_header *gz_headerp;

struct DECLSPEC_DRECORD gz_header
{
	
public:
	int text;
	unsigned long time;
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

#if !defined(__clang__) && !defined(__CPP__)
#if sizeof(gz_header) < 52
#pragma message "Pascal/C++ size mismatch: (C++) sizeof(gz_header) < (Pascal) [size: 52, align: 1] (WARNING)"
#pragma sizeof(gz_header)
#endif

#if sizeof(gz_header) > 52
#pragma message "Pascal/C++ size mismatch: (C++) sizeof(gz_header) > (Pascal) [size: 52, align: 1] (WARNING)"
#pragma sizeof(gz_header)
#endif

#if alignof(gz_header) < 1
#pragma message "Pascal/C++ alignment mismatch: (C++) alignof(gz_header) < (Pascal) [size: 52, align: 1] (WARNING)"
#endif

#if alignof(gz_header) > 1
#pragma message "Pascal/C++ alignment mismatch: (C++) alignof(gz_header) > (Pascal) [size: 52, align: 1] (WARNING)"
#endif
#endif
#endif
#if defined(__REMOVE_MACTYPES__)
  // Cleanup workaround for "Byte" ambiguity
  #if defined(__MACTYPES__)
    #undef __MACTYPES__
  #endif
  #undef __REMOVE_MACTYPES__
#endif

namespace Idzlibheaders
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdZLibStubError;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TZStreamType : unsigned char { zsZLib, zsGZip, zsRaw };

class PASCALIMPLEMENTATION EIdZLibStubError : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
protected:
	unsigned FError;
	System::UnicodeString FErrorMessage;
	System::UnicodeString FTitle;
	
public:
	__fastcall EIdZLibStubError(const System::UnicodeString ATitle, unsigned AError);
	__property unsigned Error = {read=FError, nodefault};
	__property System::UnicodeString ErrorMessage = {read=FErrorMessage};
	__property System::UnicodeString Title = {read=FTitle};
public:
	/* EIdException.Create */ inline __fastcall virtual EIdZLibStubError(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdZLibStubError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdZLibStubError(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdZLibStubError(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdZLibStubError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdZLibStubError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdZLibStubError(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdZLibStubError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdZLibStubError(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdZLibStubError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdZLibStubError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdZLibStubError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdZLibStubError() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall IdZLibSetLibPath(const System::UnicodeString APath);
}	/* namespace Idzlibheaders */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDZLIBHEADERS)
using namespace Idzlibheaders;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdzlibheadersHPP
