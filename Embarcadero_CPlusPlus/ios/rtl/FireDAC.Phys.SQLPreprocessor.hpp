// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.SQLPreprocessor.pas' rev: 34.00 (iOS)

#ifndef Firedac_Phys_SqlpreprocessorHPP
#define Firedac_Phys_SqlpreprocessorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Phys.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Sqlpreprocessor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysPreprocessor;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDPhysPreprocessorInstr : unsigned int { piCreateParams, piCreateMacros, piExpandParams, piExpandMacros, piExpandEscapes, piParseSQL, piTransformQuestions, piTransformEOLs };

typedef System::Set<TFDPhysPreprocessorInstr, TFDPhysPreprocessorInstr::piCreateParams, TFDPhysPreprocessorInstr::piTransformEOLs> TFDPhysPreprocessorInstrs;

class PASCALIMPLEMENTATION TFDPhysPreprocessor : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Firedac::Phys::Intf::_di_IFDPhysConnectionMetadata FConnMetadata;
	Firedac::Stan::Param::TFDParams* FParams;
	Firedac::Stan::Param::TFDMacros* FMacrosUpd;
	Firedac::Stan::Param::TFDMacros* FMacrosRead;
	TFDPhysPreprocessorInstrs FInstrs;
	bool FDesignMode;
	Firedac::Stan::Intf::TFDByteSet FNameDelims1;
	Firedac::Stan::Intf::TFDByteSet FNameDelims2;
	Firedac::Phys::Intf::TFDPhysParamMark FParamMark;
	bool FNested;
	System::WideChar FPrevCh;
	System::WideChar FCh;
	System::UnicodeString FSource;
	System::UnicodeString FDestination;
	int FSourceLen;
	int FSrcIndex;
	int FCommitedIndex;
	int FDestinationIndex;
	bool FInComment1;
	bool FInComment2;
	bool FInStr1;
	bool FInStr2;
	bool FInStr3;
	bool FInMySQLConditional;
	bool FInProgramBlock;
	Firedac::Phys::Intf::TFDPhysNameQuoteLevels FInNames;
	int FEscapeLevel;
	int FBraceLevel;
	int FParamCount;
	int FSkipEscapes;
	Firedac::Stan::Intf::TFDStringList* FParamCache;
	Firedac::Stan::Intf::TFDStringList* FDestStack;
	Firedac::Stan::Intf::TFDStringList* FTokens;
	Firedac::Stan::Intf::TFDStringList* FQuoteTags;
	Firedac::Phys::Intf::TFDPhysCommandKind FSQLCommandKind;
	System::UnicodeString FSQLFromValue;
	int FSQLOrderByPos;
	int FSQLValuesPos;
	int FSQLValuesPosEnd;
	int FSQLLimitSkip;
	int FSQLLimitRows;
	bool FInIntoEscape;
	bool FWasIntoEscape;
	void __fastcall Commit(int ASkip = 0x0);
	void __fastcall Uncommit(int AChars);
	void __fastcall WriteStr(const System::UnicodeString AStr);
	void __fastcall PushWriter();
	System::UnicodeString __fastcall PopWriter();
	System::WideChar __fastcall GetChar();
	void __fastcall PutBack();
	void __fastcall SkipWS();
	System::UnicodeString __fastcall ProcessIdentifier(bool ADotAllowed, bool &AIsQuoted);
	void __fastcall ProcessParam();
	void __fastcall ProcessQuestion();
	void __fastcall ProcessMacro(System::WideChar AFirstCh);
	Firedac::Phys::Intf::TFDPhysEscapeKind __fastcall ProcessEscape();
	System::UnicodeString __fastcall TranslateEscape(Firedac::Phys::Intf::TFDPhysEscapeData &AEscape);
	System::UnicodeString __fastcall ProcessCommand();
	void __fastcall ParseDestination();
	void __fastcall Missed(const System::UnicodeString AStr);
	void __fastcall ProcessQuoteTag();
	
public:
	__fastcall TFDPhysPreprocessor();
	__fastcall virtual ~TFDPhysPreprocessor();
	void __fastcall Init();
	void __fastcall Execute();
	__property Firedac::Phys::Intf::_di_IFDPhysConnectionMetadata ConnMetadata = {read=FConnMetadata, write=FConnMetadata};
	__property System::UnicodeString Source = {read=FSource, write=FSource};
	__property System::UnicodeString Destination = {read=FDestination};
	__property Firedac::Stan::Param::TFDParams* Params = {read=FParams, write=FParams};
	__property Firedac::Stan::Param::TFDMacros* MacrosUpd = {read=FMacrosUpd, write=FMacrosUpd};
	__property Firedac::Stan::Param::TFDMacros* MacrosRead = {read=FMacrosRead, write=FMacrosRead};
	__property TFDPhysPreprocessorInstrs Instrs = {read=FInstrs, write=FInstrs, nodefault};
	__property bool DesignMode = {read=FDesignMode, write=FDesignMode, nodefault};
	__property Firedac::Phys::Intf::TFDPhysCommandKind SQLCommandKind = {read=FSQLCommandKind, nodefault};
	__property System::UnicodeString SQLFromValue = {read=FSQLFromValue};
	__property int SQLOrderByPos = {read=FSQLOrderByPos, nodefault};
	__property int SQLValuesPos = {read=FSQLValuesPos, nodefault};
	__property int SQLValuesPosEnd = {read=FSQLValuesPosEnd, nodefault};
	__property int SQLLimitSkip = {read=FSQLLimitSkip, nodefault};
	__property int SQLLimitRows = {read=FSQLLimitRows, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sqlpreprocessor */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_SQLPREPROCESSOR)
using namespace Firedac::Phys::Sqlpreprocessor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS)
using namespace Firedac::Phys;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Phys_SqlpreprocessorHPP
