// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.ASE.Lexer.pas' rev: 34.00 (iOS)

#ifndef Fmx_Ase_LexerHPP
#define Fmx_Ase_LexerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Ase
{
namespace Lexer
{
//-- forward type declarations -----------------------------------------------
struct TASETokenHelper /* Helper for enum 'TASEToken' */;
struct TKeyWordRec;
class DELPHICLASS TAseLexer;
class DELPHICLASS EAseLexerError;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TASEToken : unsigned char { Unknown, EndOfFile, KeyWord, Ident, String, Integer, Float, Colon, OpenBracket, CloseBracket, Comma, atUnknown _DEPRECATED_ATTRIBUTE3("Use TASEToken.Unknown")  = 0, atEOF _DEPRECATED_ATTRIBUTE3("Use TASEToken.EndOfFile")  = 1, atKeyWord _DEPRECATED_ATTRIBUTE3("Use TASEToken.KeyWord")  = 2, atIdent _DEPRECATED_ATTRIBUTE3("Use TASEToken.Ident")  = 3, atString _DEPRECATED_ATTRIBUTE3("Use TASEToken.String")  = 4, atInteger _DEPRECATED_ATTRIBUTE3("Use TASEToken.Integer")  = 5, atFloat _DEPRECATED_ATTRIBUTE3("Use TASEToken.Float")  = 6, atColon _DEPRECATED_ATTRIBUTE3("Use TASEToken.Colon")  = 7, atOpenBracket _DEPRECATED_ATTRIBUTE3("Use TASEToken.OpenBracket")  = 8, atCloseBracket _DEPRECATED_ATTRIBUTE3("Use TASEToken.CloseBracket")  = 9, 
	atComma _DEPRECATED_ATTRIBUTE3("Use TASEToken.Comma")  = 10 };

enum class DECLSPEC_DENUM TKeyWord : unsigned char { kw_UNKNOWN, kw_3DSMAX_ASCIIEXPORT, kw_COMMENT, kw_SCENE, kw_SCENE_FILENAME, kw_SCENE_FIRSTFRAME, kw_SCENE_LASTFRAME, kw_SCENE_FRAMESPEED, kw_SCENE_TICKSPERFRAME, kw_SCENE_BACKGROUND_STATIC, kw_SCENE_AMBIENT_STATIC, kw_MATERIAL_LIST, kw_MATERIAL_COUNT, kw_MATERIAL, kw_MATERIAL_NAME, kw_MATERIAL_CLASS, kw_MATERIAL_AMBIENT, kw_MATERIAL_DIFFUSE, kw_MATERIAL_SPECULAR, kw_MATERIAL_SHINE, kw_MATERIAL_SHINESTRENGTH, kw_MATERIAL_TRANSPARENCY, kw_MATERIAL_WIRESIZE, kw_MATERIAL_SHADING, kw_MATERIAL_XP_FALLOFF, kw_MATERIAL_SELFILLUM, kw_MATERIAL_FALLOFF, kw_MATERIAL_XP_TYPE, kw_NUMSUBMTLS, kw_SUBMATERIAL, kw_MAP_DIFFUSE, kw_MAP_NAME, kw_MAP_CLASS, kw_MAP_SUBNO, kw_MAP_AMOUNT, kw_BITMAP, kw_MAP_TYPE, kw_UVW_U_OFFSET, 
	kw_UVW_V_OFFSET, kw_UVW_U_TILING, kw_UVW_V_TILING, kw_UVW_ANGLE, kw_UVW_BLUR, kw_UVW_BLUR_OFFSET, kw_UVW_NOUSE_AMT, kw_UVW_NOISE_SIZE, kw_UVW_NOISE_LEVEL, kw_UVW_NOISE_PHASE, kw_BITMAP_FILTER, kw_GEOMOBJECT, kw_NODE_NAME, kw_NODE_TM, kw_INHERIT_POS, kw_INHERIT_ROT, kw_INHERIT_SCL, kw_TM_ROW0, kw_TM_ROW1, kw_TM_ROW2, kw_TM_ROW3, kw_TM_POS, kw_TM_ROTAXIS, kw_TM_ROTANGLE, kw_TM_SCALE, kw_TM_SCALEAXIS, kw_TM_SCALEAXISANG, kw_MESH, kw_TIMEVALUE, kw_MESH_NUMVERTEX, kw_MESH_NUMFACES, kw_MESH_VERTEX_LIST, kw_MESH_VERTEX, kw_MESH_FACE_LIST, kw_MESH_FACE, kw_MESH_SMOOTHING, kw_MESH_MTLID, kw_MESH_NUMTVERTEX, kw_MESH_TVERTLIST, kw_MESH_TVERT, kw_MESH_NUMTVFACES, kw_MESH_TFACELIST, kw_MESH_TFACE, kw_MESH_NORMALS, kw_MESH_FACENORMAL, kw_MESH_VERTEXNORMAL, 
	kw_PROP_MOTIONBLUR, kw_PROP_CASTSHADOW, kw_PROP_RECVSHADOW, kw_MATERIAL_REF };

struct DECLSPEC_DRECORD TKeyWordRec
{
public:
	System::UnicodeString Str;
	int Hash;
};


typedef System::StaticArray<TKeyWordRec, 88> Fmx_Ase_Lexer__1;

class PASCALIMPLEMENTATION TAseLexer : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	void __fastcall StringToKeyWord();
	void __fastcall SkipBlanks();
	
private:
	bool FAhead;
	System::TextFile FASE;
	TASEToken FToken;
	bool FUseCommaToken;
	int FIdxCurChar;
	System::UnicodeString FLine;
	int FLineId;
	System::UnicodeString FString;
	TKeyWord FKeyWord;
	System::Sysutils::TFormatSettings FFormatSettings;
	float __fastcall GetTokenFloat();
	int __fastcall GetTokenInteger();
	System::WideChar __fastcall GetChar();
	
public:
	__fastcall TAseLexer(const System::UnicodeString AFileName);
	__fastcall virtual ~TAseLexer();
	TASEToken __fastcall NextToken();
	void __fastcall NextTokenExpected(TASEToken AToken);
	bool __fastcall IsExpectedToken(TASEToken AToken);
	__property TASEToken Token = {read=FToken, nodefault};
	void __fastcall SkipKeyWordBlock();
	bool __fastcall IsDigit();
	bool __fastcall IsChar();
	bool __fastcall IsCharUpper();
	__property TKeyWord TokenKeyWord = {read=FKeyWord, nodefault};
	__property System::UnicodeString TokenString = {read=FString};
	__property System::UnicodeString TokenIdent = {read=FString};
	__property float TokenFloat = {read=GetTokenFloat};
	__property int TokenInteger = {read=GetTokenInteger, nodefault};
	__property System::WideChar CurrentChar = {read=GetChar, nodefault};
	__property bool Ahead = {read=FAhead, write=FAhead, nodefault};
	__property bool UseCommaToken = {read=FUseCommaToken, write=FUseCommaToken, nodefault};
};


class PASCALIMPLEMENTATION EAseLexerError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EAseLexerError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EAseLexerError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EAseLexerError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EAseLexerError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EAseLexerError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EAseLexerError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EAseLexerError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EAseLexerError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAseLexerError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAseLexerError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAseLexerError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAseLexerError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EAseLexerError() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Fmx_Ase_Lexer__1 KEY_WORDS;
}	/* namespace Lexer */
}	/* namespace Ase */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ASE_LEXER)
using namespace Fmx::Ase::Lexer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ASE)
using namespace Fmx::Ase;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Ase_LexerHPP
