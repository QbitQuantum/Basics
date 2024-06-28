// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'XMLTestRunner.pas' rev: 34.00 (Windows)

#ifndef XmltestrunnerHPP
#define XmltestrunnerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <TestFramework.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xmltestrunner
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TXMLTestListener;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TXMLTestListener : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::TextFile FOutputFile;
	System::UnicodeString FFileName;
	
protected:
	System::TDateTime startTime;
	void __fastcall writeReport(System::UnicodeString str);
	
public:
	virtual void __fastcall AddSuccess(Testframework::_di_ITest test);
	virtual void __fastcall AddError(Testframework::TTestFailure* error);
	virtual void __fastcall AddFailure(Testframework::TTestFailure* failure);
	virtual bool __fastcall ShouldRunTest(Testframework::_di_ITest test);
	virtual void __fastcall StartSuite(Testframework::_di_ITest suite);
	virtual void __fastcall EndSuite(Testframework::_di_ITest suite);
	virtual void __fastcall StartTest(Testframework::_di_ITest test);
	virtual void __fastcall EndTest(Testframework::_di_ITest test);
	virtual void __fastcall TestingStarts();
	virtual void __fastcall TestingEnds(Testframework::TTestResult* testResult);
	void __fastcall Status(Testframework::_di_ITest test, const System::UnicodeString Msg);
	void __fastcall Warning(Testframework::_di_ITest test, const System::UnicodeString Msg);
	__fastcall TXMLTestListener()/* overload */;
	__fastcall TXMLTestListener(System::UnicodeString outputFile)/* overload */;
	__classmethod Testframework::TTestResult* __fastcall RunTest(Testframework::_di_ITest suite, System::UnicodeString outputFile)/* overload */;
	__classmethod Testframework::TTestResult* __fastcall RunRegisteredTests(System::UnicodeString outputFile);
	__classmethod System::UnicodeString __fastcall text2sgml(System::UnicodeString text);
	__classmethod System::UnicodeString __fastcall StringReplaceAll(System::UnicodeString text, System::UnicodeString byt, System::UnicodeString mot);
	__property System::UnicodeString FileName = {read=FFileName, write=FFileName};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXMLTestListener() { }
	
private:
	void *__ITestListenerX;	// Testframework::ITestListenerX 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5C28B1BE-38B5-4D6F-AA96-A04E9302C317}
	operator Testframework::_di_ITestListenerX()
	{
		Testframework::_di_ITestListenerX intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Testframework::ITestListenerX*(void) { return (Testframework::ITestListenerX*)&__ITestListenerX; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {114185BC-B36B-4C68-BDAB-273DBD450F72}
	operator Testframework::_di_ITestListener()
	{
		Testframework::_di_ITestListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Testframework::ITestListener*(void) { return (Testframework::ITestListener*)&__ITestListenerX; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
#define DEFAULT_FILENAME L"dunit-report.xml"
extern DELPHI_PACKAGE Testframework::TTestResult* __fastcall RunTest(Testframework::_di_ITest suite, System::UnicodeString outputFile = L"dunit-report.xml")/* overload */;
extern DELPHI_PACKAGE Testframework::TTestResult* __fastcall RunRegisteredTests(System::UnicodeString outputFile = L"dunit-report.xml")/* overload */;
}	/* namespace Xmltestrunner */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XMLTESTRUNNER)
using namespace Xmltestrunner;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// XmltestrunnerHPP
