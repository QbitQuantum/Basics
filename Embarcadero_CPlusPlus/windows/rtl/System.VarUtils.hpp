// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.VarUtils.pas' rev: 34.00 (Windows)

#ifndef System_VarutilsHPP
#define System_VarutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.SysConst.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Varutils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ESafeArrayError;
class DELPHICLASS ESafeArrayCreateError;
class DELPHICLASS ESafeArrayBoundsError;
class DELPHICLASS ESafeArrayLockedError;
struct TVarTypeToElementInfo;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ESafeArrayError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
private:
	HRESULT FErrorCode;
	
public:
	__fastcall ESafeArrayError(HRESULT AResult, const System::UnicodeString AMessage);
	__property HRESULT ErrorCode = {read=FErrorCode, write=FErrorCode, nodefault};
public:
	/* Exception.Create */ inline __fastcall ESafeArrayError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESafeArrayError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESafeArrayError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESafeArrayError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESafeArrayError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESafeArrayError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESafeArrayError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESafeArrayError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESafeArrayError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESafeArrayError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESafeArrayError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESafeArrayError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESafeArrayError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ESafeArrayCreateError : public ESafeArrayError
{
	typedef ESafeArrayError inherited;
	
public:
	/* ESafeArrayError.CreateHResult */ inline __fastcall ESafeArrayCreateError(HRESULT AResult, const System::UnicodeString AMessage) : ESafeArrayError(AResult, AMessage) { }
	
public:
	/* Exception.Create */ inline __fastcall ESafeArrayCreateError(const System::UnicodeString Msg) : ESafeArrayError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESafeArrayCreateError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ESafeArrayError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESafeArrayCreateError(NativeUInt Ident)/* overload */ : ESafeArrayError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESafeArrayCreateError(System::PResStringRec ResStringRec)/* overload */ : ESafeArrayError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESafeArrayCreateError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ESafeArrayError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESafeArrayCreateError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ESafeArrayError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESafeArrayCreateError(const System::UnicodeString Msg, int AHelpContext) : ESafeArrayError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESafeArrayCreateError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ESafeArrayError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESafeArrayCreateError(NativeUInt Ident, int AHelpContext)/* overload */ : ESafeArrayError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESafeArrayCreateError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ESafeArrayError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESafeArrayCreateError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESafeArrayError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESafeArrayCreateError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESafeArrayError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESafeArrayCreateError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ESafeArrayBoundsError : public ESafeArrayError
{
	typedef ESafeArrayError inherited;
	
public:
	/* ESafeArrayError.CreateHResult */ inline __fastcall ESafeArrayBoundsError(HRESULT AResult, const System::UnicodeString AMessage) : ESafeArrayError(AResult, AMessage) { }
	
public:
	/* Exception.Create */ inline __fastcall ESafeArrayBoundsError(const System::UnicodeString Msg) : ESafeArrayError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESafeArrayBoundsError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ESafeArrayError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESafeArrayBoundsError(NativeUInt Ident)/* overload */ : ESafeArrayError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESafeArrayBoundsError(System::PResStringRec ResStringRec)/* overload */ : ESafeArrayError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESafeArrayBoundsError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ESafeArrayError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESafeArrayBoundsError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ESafeArrayError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESafeArrayBoundsError(const System::UnicodeString Msg, int AHelpContext) : ESafeArrayError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESafeArrayBoundsError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ESafeArrayError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESafeArrayBoundsError(NativeUInt Ident, int AHelpContext)/* overload */ : ESafeArrayError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESafeArrayBoundsError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ESafeArrayError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESafeArrayBoundsError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESafeArrayError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESafeArrayBoundsError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESafeArrayError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESafeArrayBoundsError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ESafeArrayLockedError : public ESafeArrayError
{
	typedef ESafeArrayError inherited;
	
public:
	/* ESafeArrayError.CreateHResult */ inline __fastcall ESafeArrayLockedError(HRESULT AResult, const System::UnicodeString AMessage) : ESafeArrayError(AResult, AMessage) { }
	
public:
	/* Exception.Create */ inline __fastcall ESafeArrayLockedError(const System::UnicodeString Msg) : ESafeArrayError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESafeArrayLockedError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ESafeArrayError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESafeArrayLockedError(NativeUInt Ident)/* overload */ : ESafeArrayError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESafeArrayLockedError(System::PResStringRec ResStringRec)/* overload */ : ESafeArrayError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESafeArrayLockedError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ESafeArrayError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESafeArrayLockedError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ESafeArrayError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESafeArrayLockedError(const System::UnicodeString Msg, int AHelpContext) : ESafeArrayError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESafeArrayLockedError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ESafeArrayError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESafeArrayLockedError(NativeUInt Ident, int AHelpContext)/* overload */ : ESafeArrayError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESafeArrayLockedError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ESafeArrayError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESafeArrayLockedError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESafeArrayError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESafeArrayLockedError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESafeArrayError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESafeArrayLockedError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TVarTypeToElementInfo
{
public:
	bool ValidBase;
	bool ValidElement;
	int Size;
	System::Word Flags;
};


//-- var, const, procedure ---------------------------------------------------
static const bool GenericVarUtils = false;
static const bool GenericVariants = false;
static const bool GenericOperations = false;
static const bool GenericSafeArrays = false;
static const bool GenericSafeArrayUsesLibC = false;
extern DELPHI_PACKAGE HRESULT __stdcall (*VariantChangeTypeEx)(TVarData &Dest, const TVarData &Source, int LCID, System::Word wFlags, System::Word VarType);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarNeg)(const TVarData &Source, TVarData &Dest);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarNot)(const TVarData &Source, TVarData &Dest);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarAdd)(const TVarData &Left, const TVarData &Right, TVarData &AResult);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarSub)(const TVarData &Left, const TVarData &Right, TVarData &AResult);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarMul)(const TVarData &Left, const TVarData &Right, TVarData &AResult);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarDiv)(const TVarData &Left, const TVarData &Right, TVarData &AResult);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarIDiv)(const TVarData &Left, const TVarData &Right, TVarData &AResult);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarMod)(const TVarData &Left, const TVarData &Right, TVarData &AResult);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarAnd)(const TVarData &Left, const TVarData &Right, TVarData &AResult);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarOr)(const TVarData &Left, const TVarData &Right, TVarData &AResult);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarXor)(const TVarData &Left, const TVarData &Right, TVarData &AResult);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarCmp)(const TVarData &Left, const TVarData &Right, int LCID, unsigned Flags);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarI4FromStr)(const System::WideChar * strIn, int LCID, int dwFlags, /* out */ int &iOut);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarR4FromStr)(const System::WideChar * strIn, int LCID, int dwFlags, /* out */ float &fltOut);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarR8FromStr)(const System::WideChar * strIn, int LCID, int dwFlags, /* out */ double &dblOut);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarDateFromStr)(const System::WideChar * strIn, unsigned LCID, int dwFlags, /* out */ System::TDateTime &dateOut);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarCyFromStr)(const System::WideChar * strIn, unsigned LCID, int dwFlags, /* out */ System::Currency &cyOut);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarBoolFromStr)(const System::WideChar * strIn, int LCID, int dwFlags, /* out */ System::WordBool &boolOut);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarBstrFromCy)(System::Currency cyIn, int LCID, int dwFlags, /* out */ System::WideString &bstrOut);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarBstrFromDate)(System::TDateTime dateIn, int LCID, int dwFlags, /* out */ System::WideString &bstrOut);
extern DELPHI_PACKAGE HRESULT __stdcall (*VarBstrFromBool)(System::WordBool boolIn, int LCID, int dwFlags, /* out */ System::WideString &bstrOut);
static const HRESULT VAR_OK = HRESULT(0);
static const HRESULT VAR_PARAMNOTFOUND = HRESULT(-2147352572);
static const HRESULT VAR_TYPEMISMATCH = HRESULT(-2147352571);
static const HRESULT VAR_BADVARTYPE = HRESULT(-2147352568);
static const HRESULT VAR_EXCEPTION = HRESULT(-2147352567);
static const HRESULT VAR_OVERFLOW = HRESULT(-2147352566);
static const HRESULT VAR_BADINDEX = HRESULT(-2147352565);
static const HRESULT VAR_ARRAYISLOCKED = HRESULT(-2147352563);
static const HRESULT VAR_NOTIMPL = HRESULT(-2147467263);
static const HRESULT VAR_OUTOFMEMORY = HRESULT(-2147024882);
static const HRESULT VAR_INVALIDARG = HRESULT(-2147024809);
static const HRESULT VAR_UNEXPECTED = HRESULT(-2147418113);
static const System::Int8 ARR_NONE = System::Int8(0x0);
static const System::Int8 ARR_FIXEDSIZE = System::Int8(0x10);
static const System::Word ARR_OLESTR = System::Word(0x100);
static const System::Word ARR_UNKNOWN = System::Word(0x200);
static const System::Word ARR_DISPATCH = System::Word(0x400);
static const System::Word ARR_VARIANT = System::Word(0x800);
static const System::Int8 VAR_CMP_LT = System::Int8(0x0);
static const System::Int8 VAR_CMP_EQ = System::Int8(0x1);
static const System::Int8 VAR_CMP_GT = System::Int8(0x2);
static const System::Int8 VAR_CMP_NULL = System::Int8(0x3);
static const System::Word VAR_LOCALE_USER_DEFAULT = System::Word(0x400);
static const System::Int8 CMinArrayVarType = System::Int8(0x0);
static const System::Int8 CMaxArrayVarType = System::Int8(0x15);
extern DELPHI_PACKAGE System::StaticArray<TVarTypeToElementInfo, 22> CVarTypeToElementInfo;
extern DELPHI_PACKAGE HRESULT __fastcall VarExceptionToResult(System::Sysutils::Exception* const E);
extern DELPHI_PACKAGE void __fastcall SafeArrayCheck(HRESULT AResult);
extern DELPHI_PACKAGE void __fastcall SafeArrayError(HRESULT AResult);
}	/* namespace Varutils */
}	/* namespace System */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_VarutilsHPP
