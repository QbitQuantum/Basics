// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TextTestRunner.pas' rev: 34.00 (iOS)

#ifndef TexttestrunnerHPP
#define TexttestrunnerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <TestFramework.hpp>
#include <DUnitConsts.hpp>

//-- user supplied -----------------------------------------------------------

namespace Texttestrunner
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTextTestListener;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TRunnerExitBehavior : unsigned char { rxbContinue, rxbPause, rxbHaltOnFailures };

class PASCALIMPLEMENTATION TTextTestListener : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	int FFailureCount;
	int FErrorCount;
	System::TDateTime startTime;
	System::TDateTime endTime;
	System::TDateTime runTime;
	int IndentLevel;
	
public:
	__fastcall TTextTestListener();
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
	System::UnicodeString __fastcall Report(Testframework::TTestResult* r);
	__classmethod Testframework::TTestResult* __fastcall RunTest(Testframework::_di_ITest suite, TRunnerExitBehavior exitBehavior = (TRunnerExitBehavior)(0x0))/* overload */;
	__classmethod Testframework::TTestResult* __fastcall RunRegisteredTests(TRunnerExitBehavior exitBehavior = (TRunnerExitBehavior)(0x0));
	__property int FailureCount = {read=FFailureCount, nodefault};
	__property int ErrorCount = {read=FErrorCount, nodefault};
	
protected:
	System::UnicodeString __fastcall PrefixChars();
	virtual System::UnicodeString __fastcall PrintErrors(Testframework::TTestResult* r);
	virtual System::UnicodeString __fastcall PrintFailures(Testframework::TTestResult* r);
	virtual System::UnicodeString __fastcall PrintHeader(Testframework::TTestResult* r);
	virtual System::UnicodeString __fastcall PrintFailureItems(Testframework::TTestResult* r);
	virtual System::UnicodeString __fastcall PrintErrorItems(Testframework::TTestResult* r);
	virtual System::UnicodeString __fastcall TruncateString(System::UnicodeString s, int len);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TTextTestListener() { }
	
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
extern DELPHI_PACKAGE System::UnicodeString rcs_id;
extern DELPHI_PACKAGE Testframework::TTestResult* __fastcall RunTest(Testframework::_di_ITest suite, TRunnerExitBehavior exitBehavior = (TRunnerExitBehavior)(0x0))/* overload */;
extern DELPHI_PACKAGE Testframework::TTestResult* __fastcall RunRegisteredTests(TRunnerExitBehavior exitBehavior = (TRunnerExitBehavior)(0x0))/* overload */;
}	/* namespace Texttestrunner */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_TEXTTESTRUNNER)
using namespace Texttestrunner;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TexttestrunnerHPP
