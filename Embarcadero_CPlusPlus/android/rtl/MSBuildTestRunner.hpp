// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'MSBuildTestRunner.pas' rev: 34.00 (Android)

#ifndef MsbuildtestrunnerHPP
#define MsbuildtestrunnerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <XMLTestRunner.hpp>
#include <TestFramework.hpp>

//-- user supplied -----------------------------------------------------------

namespace Msbuildtestrunner
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMSBuildTestListener;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TMSBuildTestListener : public Xmltestrunner::TXMLTestListener
{
	typedef Xmltestrunner::TXMLTestListener inherited;
	
public:
	virtual void __fastcall TestingEnds(Testframework::TTestResult* TestResult);
public:
	/* TXMLTestListener.Create */ inline __fastcall TMSBuildTestListener()/* overload */ : Xmltestrunner::TXMLTestListener() { }
	/* TXMLTestListener.Create */ inline __fastcall TMSBuildTestListener(System::UnicodeString outputFile)/* overload */ : Xmltestrunner::TXMLTestListener(outputFile) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMSBuildTestListener() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define DEFAULT_FILENAME u"dunit-report.xml"
extern DELPHI_PACKAGE Testframework::TTestResult* __fastcall RunTest(Testframework::_di_ITest Suite, System::UnicodeString OutputFile = u"dunit-report.xml")/* overload */;
extern DELPHI_PACKAGE Testframework::TTestResult* __fastcall RunRegisteredTests(System::UnicodeString OutputFile = u"dunit-report.xml")/* overload */;
}	/* namespace Msbuildtestrunner */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MSBUILDTESTRUNNER)
using namespace Msbuildtestrunner;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// MsbuildtestrunnerHPP
