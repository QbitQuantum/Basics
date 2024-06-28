// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TestFrameworkExtension.pas' rev: 34.00 (Windows)

#ifndef TestframeworkextensionHPP
#define TestframeworkextensionHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <TestFramework.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Testframeworkextension
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE ITestExtension;
typedef System::DelphiInterface<ITestExtension> _di_ITestExtension;
class DELPHICLASS TTestSuiteExtension;
class DELPHICLASS TTestCaseExtension;
class DELPHICLASS TTestCaseThread;
class DELPHICLASS TInterval;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{8FADE3D2-D3E6-4141-A3DE-6C348069EF96}") ITestExtension  : public Testframework::ITest 
{
	virtual void __fastcall SetProperties(System::Classes::TStrings* props) = 0 ;
	virtual System::Classes::TStrings* __fastcall GetProperties() = 0 ;
	virtual void __fastcall ApplyFilter(System::UnicodeString FilterString) = 0 ;
};

class PASCALIMPLEMENTATION TTestSuiteExtension : public Testframework::TTestSuite
{
	typedef Testframework::TTestSuite inherited;
	
public:
	System::UnicodeString __fastcall GetRunPattern(System::UnicodeString CMD);
	virtual void __fastcall FilterTests();
	virtual void __fastcall AddTests(Testframework::TTestCaseClass testClass);
public:
	/* TTestSuite.Create */ inline __fastcall TTestSuiteExtension()/* overload */ : Testframework::TTestSuite() { }
	/* TTestSuite.Create */ inline __fastcall TTestSuiteExtension(System::UnicodeString AName)/* overload */ : Testframework::TTestSuite(AName) { }
	/* TTestSuite.Create */ inline __fastcall TTestSuiteExtension(Testframework::TTestCaseClass TestClass)/* overload */ : Testframework::TTestSuite(TestClass) { }
	/* TTestSuite.Create */ inline __fastcall TTestSuiteExtension(System::UnicodeString AName, const Testframework::_di_ITest *Tests, const int Tests_High)/* overload */ : Testframework::TTestSuite(AName, Tests, Tests_High) { }
	
public:
	/* TAbstractTest.Destroy */ inline __fastcall virtual ~TTestSuiteExtension() { }
	
};


class PASCALIMPLEMENTATION TTestCaseExtension : public Testframework::TTestCase
{
	typedef Testframework::TTestCase inherited;
	
protected:
	System::Classes::TStrings* FProperties;
	System::UnicodeString FContext;
	System::UnicodeString FLogFileName;
	int FTimeoutValue;
	virtual System::UnicodeString __fastcall GetUserToken();
	virtual System::UnicodeString __fastcall GetHostName();
	virtual void __fastcall Invoke(Testframework::TTestMethod AMethod);
	
public:
	__fastcall virtual TTestCaseExtension(System::UnicodeString MethodName)/* overload */;
	__fastcall virtual ~TTestCaseExtension();
	void __fastcall SetProperties(System::Classes::TStrings* props);
	System::Classes::TStrings* __fastcall GetProperties();
	virtual System::UnicodeString __fastcall GetMethodName();
	void __fastcall ApplyFilter(System::UnicodeString FilterString);
	__property System::Classes::TStrings* Properties = {read=GetProperties};
	__property int TimeOutValue = {read=FTimeoutValue, write=FTimeoutValue, nodefault};
	__classmethod virtual Testframework::_di_ITestSuite __fastcall Suite();
public:
	/* TTestCase.Create */ inline __fastcall virtual TTestCaseExtension(System::UnicodeString MethodName, __int64 RunCount)/* overload */ : Testframework::TTestCase(MethodName, RunCount) { }
	
private:
	void *__ITestExtension;	// ITestExtension 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8FADE3D2-D3E6-4141-A3DE-6C348069EF96}
	operator _di_ITestExtension()
	{
		_di_ITestExtension intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ITestExtension*(void) { return (ITestExtension*)&__ITestExtension; }
	#endif
	
};


class PASCALIMPLEMENTATION TTestCaseThread : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	Testframework::TTestMethod FTestMethod;
	System::TObject* FExceptionObj;
	
protected:
	virtual void __fastcall Execute();
public:
	/* TThread.Create */ inline __fastcall TTestCaseThread()/* overload */ : System::Classes::TThread() { }
	/* TThread.Create */ inline __fastcall TTestCaseThread(bool CreateSuspended)/* overload */ : System::Classes::TThread(CreateSuspended) { }
	/* TThread.Create */ inline __fastcall TTestCaseThread(bool CreateSuspended, NativeUInt ReservedStackSize)/* overload */ : System::Classes::TThread(CreateSuspended, ReservedStackSize) { }
	/* TThread.Destroy */ inline __fastcall virtual ~TTestCaseThread() { }
	
};


class PASCALIMPLEMENTATION TInterval : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::TDateTime FStart;
	System::TDateTime FStop;
	__int64 __fastcall GetTotalSeconds();
	__int64 __fastcall GetTotalMinuets();
	__int64 __fastcall GetTotalHours();
	System::TDateTime __fastcall GetTimeSpan();
	
public:
	__fastcall TInterval();
	void __fastcall Start();
	void __fastcall Stop();
	void __fastcall Clear();
	__property System::TDateTime TimeSpan = {read=GetTimeSpan};
	__property __int64 TotalSeconds = {read=GetTotalSeconds};
	__property __int64 TotalMinuets = {read=GetTotalMinuets};
	__property __int64 TotalHours = {read=GetTotalHours};
	HIDESBASE System::UnicodeString __fastcall ToString()/* overload */;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TInterval() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define SelectSwitch L"-S:"
#define DisableTimeoutSwitch L"-DisableTimeout"
extern DELPHI_PACKAGE bool __fastcall UseTestTimeout(void);
extern DELPHI_PACKAGE System::Classes::TStrings* __fastcall GetAppProperties(void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetPropertyValue(System::UnicodeString Key);
extern DELPHI_PACKAGE void __fastcall SetPropertyValue(System::UnicodeString Key, System::UnicodeString Value);
extern DELPHI_PACKAGE void __fastcall CopyAppProperties(System::Classes::TStrings* Destination);
}	/* namespace Testframeworkextension */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_TESTFRAMEWORKEXTENSION)
using namespace Testframeworkextension;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TestframeworkextensionHPP
