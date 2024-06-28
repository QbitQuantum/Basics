// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TestFramework.pas' rev: 34.00 (iOS)

#ifndef TestframeworkHPP
#define TestframeworkHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.IniFiles.hpp>
#include <System.TypInfo.hpp>
#include <DUnitConsts.hpp>

//-- user supplied -----------------------------------------------------------
#ifdef USEPACKAGES
  #pragma link "dunitrtl.bpi"
#else
  #pragma link "dunitrtl.a"
#endif

namespace Testframework
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS RunCountAttribute;
class DELPHICLASS ETestFailure;
class DELPHICLASS EDunitException;
class DELPHICLASS ETestError;
class DELPHICLASS EStopTestsFailure;
class DELPHICLASS EPostTestFailure;
__interface DELPHIINTERFACE IMemLeakMonitor;
typedef System::DelphiInterface<IMemLeakMonitor> _di_IMemLeakMonitor;
__interface DELPHIINTERFACE IDUnitMemLeakMonitor;
typedef System::DelphiInterface<IDUnitMemLeakMonitor> _di_IDUnitMemLeakMonitor;
class DELPHICLASS EBreakingTestFailure;
__interface DELPHIINTERFACE ITest;
typedef System::DelphiInterface<ITest> _di_ITest;
__interface DELPHIINTERFACE ITestDecorator;
typedef System::DelphiInterface<ITestDecorator> _di_ITestDecorator;
__interface DELPHIINTERFACE IStatusListener;
typedef System::DelphiInterface<IStatusListener> _di_IStatusListener;
__interface DELPHIINTERFACE ITestListener;
typedef System::DelphiInterface<ITestListener> _di_ITestListener;
__interface DELPHIINTERFACE ITestListenerX;
typedef System::DelphiInterface<ITestListenerX> _di_ITestListenerX;
__interface DELPHIINTERFACE ITestSuite;
typedef System::DelphiInterface<ITestSuite> _di_ITestSuite;
class DELPHICLASS TStatusToResultAdapter;
class DELPHICLASS TTestResult;
class DELPHICLASS TAbstractTest;
class DELPHICLASS TTestCase;
template<typename T> class DELPHICLASS TConverter__1;
class DELPHICLASS TGenericTestCase;
class DELPHICLASS TTestSuite;
class DELPHICLASS TTestFailure;
class DELPHICLASS TMethodEnumerator;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION RunCountAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
public:
	__int64 FCount;
	__fastcall RunCountAttribute(__int64 count);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~RunCountAttribute() { }
	
};


typedef void __fastcall (__closure *TTestMethod)(void);

typedef void __fastcall (*TTestProc)(void);

_DECLARE_METACLASS(System::TMetaClass, TTestCaseClass);

_DECLARE_METACLASS(System::TMetaClass, ExceptionClass);

class PASCALIMPLEMENTATION ETestFailure : public System::Sysutils::EAbort
{
	typedef System::Sysutils::EAbort inherited;
	
public:
	__fastcall ETestFailure()/* overload */;
	__fastcall ETestFailure(System::UnicodeString msg)/* overload */;
public:
	/* Exception.CreateFmt */ inline __fastcall ETestFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::EAbort(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ETestFailure(NativeUInt Ident)/* overload */ : System::Sysutils::EAbort(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ETestFailure(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::EAbort(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ETestFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EAbort(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ETestFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EAbort(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ETestFailure(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::EAbort(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ETestFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::EAbort(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETestFailure(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::EAbort(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETestFailure(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::EAbort(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETestFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EAbort(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETestFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EAbort(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ETestFailure() { }
	
};


class PASCALIMPLEMENTATION EDunitException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EDunitException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EDunitException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDunitException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDunitException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDunitException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDunitException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDunitException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDunitException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDunitException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDunitException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDunitException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDunitException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDunitException() { }
	
};


class PASCALIMPLEMENTATION ETestError : public EDunitException
{
	typedef EDunitException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ETestError(const System::UnicodeString Msg) : EDunitException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ETestError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDunitException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ETestError(NativeUInt Ident)/* overload */ : EDunitException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ETestError(System::PResStringRec ResStringRec)/* overload */ : EDunitException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ETestError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDunitException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ETestError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDunitException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ETestError(const System::UnicodeString Msg, int AHelpContext) : EDunitException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ETestError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDunitException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETestError(NativeUInt Ident, int AHelpContext)/* overload */ : EDunitException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETestError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDunitException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETestError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDunitException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETestError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDunitException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ETestError() { }
	
};


class PASCALIMPLEMENTATION EStopTestsFailure : public ETestFailure
{
	typedef ETestFailure inherited;
	
public:
	/* ETestFailure.Create */ inline __fastcall EStopTestsFailure()/* overload */ : ETestFailure() { }
	/* ETestFailure.Create */ inline __fastcall EStopTestsFailure(System::UnicodeString msg)/* overload */ : ETestFailure(msg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EStopTestsFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ETestFailure(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EStopTestsFailure(NativeUInt Ident)/* overload */ : ETestFailure(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EStopTestsFailure(System::PResStringRec ResStringRec)/* overload */ : ETestFailure(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EStopTestsFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ETestFailure(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EStopTestsFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ETestFailure(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EStopTestsFailure(const System::UnicodeString Msg, int AHelpContext) : ETestFailure(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EStopTestsFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ETestFailure(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EStopTestsFailure(NativeUInt Ident, int AHelpContext)/* overload */ : ETestFailure(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EStopTestsFailure(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ETestFailure(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EStopTestsFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ETestFailure(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EStopTestsFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ETestFailure(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EStopTestsFailure() { }
	
};


class PASCALIMPLEMENTATION EPostTestFailure : public ETestFailure
{
	typedef ETestFailure inherited;
	
public:
	/* ETestFailure.Create */ inline __fastcall EPostTestFailure()/* overload */ : ETestFailure() { }
	/* ETestFailure.Create */ inline __fastcall EPostTestFailure(System::UnicodeString msg)/* overload */ : ETestFailure(msg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EPostTestFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ETestFailure(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EPostTestFailure(NativeUInt Ident)/* overload */ : ETestFailure(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EPostTestFailure(System::PResStringRec ResStringRec)/* overload */ : ETestFailure(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EPostTestFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ETestFailure(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EPostTestFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ETestFailure(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EPostTestFailure(const System::UnicodeString Msg, int AHelpContext) : ETestFailure(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EPostTestFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ETestFailure(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPostTestFailure(NativeUInt Ident, int AHelpContext)/* overload */ : ETestFailure(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPostTestFailure(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ETestFailure(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPostTestFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ETestFailure(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPostTestFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ETestFailure(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EPostTestFailure() { }
	
};


typedef System::StaticArray<int, 4> TAllowedLeakArray;

typedef int __fastcall (__closure *TListIterator)(void);

__interface  INTERFACE_UUID("{041368CC-5B04-4111-9E2E-05A5908B3A58}") IMemLeakMonitor  : public System::IInterface 
{
	virtual bool __fastcall MemLeakDetected(/* out */ int &LeakSize) = 0 ;
};

__interface  INTERFACE_UUID("{45466FCA-1ADC-4457-A41C-88FA3F8D23F7}") IDUnitMemLeakMonitor  : public IMemLeakMonitor 
{
	HIDESBASE virtual bool __fastcall MemLeakDetected(const int AllowedLeakSize, const bool FailOnMemoryRecovery, /* out */ int &LeakSize) = 0 /* overload */;
	HIDESBASE virtual bool __fastcall MemLeakDetected(const TListIterator AllowedValuesGetter, const bool FailOnMemoryRecovery, /* out */ int &LeakIndex, /* out */ int &LeakSize) = 0 /* overload */;
	virtual bool __fastcall GetMemoryUseMsg(const bool FailOnMemoryRecovery, const int TestProcChangedMem, /* out */ System::UnicodeString &ErrorMsg) = 0 /* overload */;
	virtual bool __fastcall GetMemoryUseMsg(const bool FailOnMemoryRecovery, const int TestSetupChangedMem, const int TestProcChangedMem, const int TestTearDownChangedMem, const int TestCaseChangedMem, /* out */ System::UnicodeString &ErrorMsg) = 0 /* overload */;
	virtual void __fastcall MarkMemInUse() = 0 ;
};

class PASCALIMPLEMENTATION EBreakingTestFailure : public EDunitException
{
	typedef EDunitException inherited;
	
public:
	__fastcall EBreakingTestFailure()/* overload */;
	__fastcall EBreakingTestFailure(System::UnicodeString msg)/* overload */;
public:
	/* Exception.CreateFmt */ inline __fastcall EBreakingTestFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDunitException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBreakingTestFailure(NativeUInt Ident)/* overload */ : EDunitException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBreakingTestFailure(System::PResStringRec ResStringRec)/* overload */ : EDunitException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBreakingTestFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDunitException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBreakingTestFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDunitException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBreakingTestFailure(const System::UnicodeString Msg, int AHelpContext) : EDunitException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBreakingTestFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDunitException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBreakingTestFailure(NativeUInt Ident, int AHelpContext)/* overload */ : EDunitException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBreakingTestFailure(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDunitException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBreakingTestFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDunitException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBreakingTestFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDunitException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBreakingTestFailure() { }
	
};


__interface  INTERFACE_UUID("{89CCD557-7DE1-4814-B033-ABAFE0870EC7}") ITest  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual int __fastcall CountTestCases() = 0 ;
	virtual int __fastcall CountEnabledTestCases() = 0 ;
	virtual System::Classes::_di_IInterfaceList __fastcall Tests() = 0 ;
	virtual void __fastcall SetUp() = 0 ;
	virtual void __fastcall TearDown() = 0 ;
	virtual TTestResult* __fastcall Run() = 0 /* overload */;
	virtual void __fastcall Run(TTestResult* testResult) = 0 /* overload */;
	virtual void __fastcall RunWithFixture(TTestResult* testResult) = 0 ;
	virtual void __fastcall RunTest(TTestResult* testResult) = 0 ;
	virtual bool __fastcall GetTestMethodInvoked() = 0 ;
	virtual void __fastcall SetTestMethodInvoked(const bool Value) = 0 ;
	__property bool TestMethodInvoked = {read=GetTestMethodInvoked, write=SetTestMethodInvoked};
	virtual bool __fastcall GetEnabled() = 0 ;
	virtual void __fastcall SetEnabled(bool Value) = 0 ;
	virtual void __fastcall SetStartTime(__int64 Value) = 0 ;
	virtual __int64 __fastcall GetStartTime() = 0 ;
	virtual void __fastcall SetStopTime(__int64 Value) = 0 ;
	virtual __int64 __fastcall GetStopTime() = 0 ;
	virtual unsigned __fastcall ElapsedTestTime() = 0 ;
	virtual int __fastcall GetRunCount() = 0 ;
	virtual void __fastcall SetRunCount(int Value) = 0 ;
	virtual void __fastcall SetStatusListener(_di_IStatusListener Listener) = 0 ;
	virtual System::UnicodeString __fastcall GetStatus() = 0 ;
	virtual void __fastcall LoadConfiguration(System::Inifiles::TCustomIniFile* const iniFile, const System::UnicodeString section) = 0 /* overload */;
	virtual void __fastcall LoadConfiguration(const System::UnicodeString fileName, const bool useRegistry, const bool useMemIni) = 0 /* overload */;
	virtual void __fastcall SaveConfiguration(System::Inifiles::TCustomIniFile* const iniFile, const System::UnicodeString section) = 0 /* overload */;
	virtual void __fastcall SaveConfiguration(const System::UnicodeString fileName, const bool useRegistry, const bool useMemIni) = 0 /* overload */;
	virtual void __fastcall SetGUIObject(System::TObject* const guiObject) = 0 ;
	virtual System::TObject* __fastcall GetGUIObject() = 0 ;
	__property int RunCount = {read=GetRunCount, write=SetRunCount};
	__property System::UnicodeString Name = {read=GetName};
	__property bool Enabled = {read=GetEnabled, write=SetEnabled};
	__property System::TObject* GUIObject = {read=GetGUIObject, write=SetGUIObject};
	__property System::UnicodeString Status = {read=GetStatus};
	__property __int64 StartTime = {read=GetStartTime, write=SetStartTime};
	__property __int64 StopTime = {read=GetStopTime, write=SetStopTime};
	virtual void __fastcall SetFailsOnNoChecksExecuted(const bool Value) = 0 ;
	virtual bool __fastcall GetFailsOnNoChecksExecuted() = 0 ;
	__property bool FailsOnNoChecksExecuted = {read=GetFailsOnNoChecksExecuted, write=SetFailsOnNoChecksExecuted};
	virtual bool __fastcall GetFailsOnMemoryLeak() = 0 ;
	virtual void __fastcall SetFailsOnMemoryLeak(const bool Value) = 0 ;
	__property bool FailsOnMemoryLeak = {read=GetFailsOnMemoryLeak, write=SetFailsOnMemoryLeak};
	virtual int __fastcall GetAllowedMemoryLeakSize() = 0 ;
	virtual void __fastcall SetAllowedMemoryLeakSize(const int NewSize) = 0 ;
	__property int AllowedMemoryLeakSize = {read=GetAllowedMemoryLeakSize, write=SetAllowedMemoryLeakSize};
	virtual bool __fastcall GetFailsOnMemoryRecovery() = 0 ;
	virtual void __fastcall SetFailsOnMemoryRecovery(const bool Value) = 0 ;
	__property bool FailsOnMemoryRecovery = {read=GetFailsOnMemoryRecovery, write=SetFailsOnMemoryRecovery};
	virtual void __fastcall SetAllowedLeakArray(int *AllowedList, const int AllowedList_High) = 0 ;
	virtual bool __fastcall GetIgnoreSetUpTearDownLeaks() = 0 ;
	virtual void __fastcall SetIgnoreSetUpTearDownLeaks(const bool Value) = 0 ;
	__property bool IgnoreSetUpTearDownLeaks = {read=GetIgnoreSetUpTearDownLeaks, write=SetIgnoreSetUpTearDownLeaks};
	virtual int __fastcall GetAllowedLeak() = 0 ;
	virtual TListIterator __fastcall GetAllowedLeaksIterator() = 0 ;
	__property TListIterator AllowedLeaksIterator = {read=GetAllowedLeaksIterator};
};

__interface  INTERFACE_UUID("{8B3FC229-3033-4590-AD5C-01914C6E2C9F}") ITestDecorator  : public ITest 
{
	virtual _di_ITest __fastcall GetTest() = 0 ;
	__property _di_ITest Test = {read=GetTest};
};

__interface  INTERFACE_UUID("{8681DC88-033C-4A42-84F4-4C52EF9ABAC0}") IStatusListener  : public System::IInterface 
{
	virtual void __fastcall Status(_di_ITest test, const System::UnicodeString Msg) = 0 ;
};

__interface  INTERFACE_UUID("{114185BC-B36B-4C68-BDAB-273DBD450F72}") ITestListener  : public IStatusListener 
{
	virtual void __fastcall TestingStarts() = 0 ;
	virtual void __fastcall StartTest(_di_ITest test) = 0 ;
	virtual void __fastcall AddSuccess(_di_ITest test) = 0 ;
	virtual void __fastcall AddError(TTestFailure* error) = 0 ;
	virtual void __fastcall AddFailure(TTestFailure* Failure) = 0 ;
	virtual void __fastcall EndTest(_di_ITest test) = 0 ;
	virtual void __fastcall TestingEnds(TTestResult* testResult) = 0 ;
	virtual bool __fastcall ShouldRunTest(_di_ITest test) = 0 ;
};

__interface  INTERFACE_UUID("{5C28B1BE-38B5-4D6F-AA96-A04E9302C317}") ITestListenerX  : public ITestListener 
{
	virtual void __fastcall StartSuite(_di_ITest suite) = 0 ;
	virtual void __fastcall EndSuite(_di_ITest suite) = 0 ;
};

__interface  INTERFACE_UUID("{C20E38EF-7369-44D9-9D84-08E84EC1DCF0}") ITestSuite  : public ITest 
{
	virtual void __fastcall AddTest(_di_ITest test) = 0 ;
	virtual void __fastcall AddSuite(_di_ITestSuite suite) = 0 ;
};

class PASCALIMPLEMENTATION TStatusToResultAdapter : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	TTestResult* FTestResult;
	
public:
	__fastcall TStatusToResultAdapter(TTestResult* TestResult);
	void __fastcall Status(_di_ITest Test, const System::UnicodeString Msg);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TStatusToResultAdapter() { }
	
private:
	void *__IStatusListener;	// IStatusListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8681DC88-033C-4A42-84F4-4C52EF9ABAC0}
	operator _di_IStatusListener()
	{
		_di_IStatusListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IStatusListener*(void) { return (IStatusListener*)&__IStatusListener; }
	#endif
	
};


class PASCALIMPLEMENTATION TTestResult : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	__int64 FTotalTime;
	
protected:
	System::Classes::TList* FFailures;
	System::Classes::TList* FErrors;
	int FOverRides;
	System::Classes::_di_IInterfaceList FListeners;
	_di_ITest FRootTest;
	int FRunTests;
	bool FStop;
	bool FBreakOnFailures;
	bool FFailsIfNoChecksExecuted;
	bool FIgnoresMemoryLeakInSetUpTearDown;
	bool FMemoryLeakIgnoredInSetupOrTearDown;
	bool FFailsIfMemoryLeaked;
	void *FMethodPtr;
	_di_IStatusListener FStatusAdapter;
	virtual void __fastcall Run(_di_ITest test);
	virtual bool __fastcall RunTestSetup(_di_ITest test);
	virtual void __fastcall RunTestTearDown(_di_ITest test);
	virtual bool __fastcall RunTestRun(_di_ITest test);
	virtual void __fastcall TestingStarts();
	virtual void __fastcall StartSuite(_di_ITest suite);
	virtual void __fastcall StartTest(_di_ITest test);
	virtual bool __fastcall ShouldRunTest(_di_ITest test);
	virtual void __fastcall Status(_di_ITest test, const System::UnicodeString Msg);
	virtual void __fastcall EndSuite(_di_ITest suite);
	virtual void __fastcall EndTest(_di_ITest test);
	virtual void __fastcall TestingEnds();
	
public:
	__fastcall TTestResult();
	__fastcall virtual ~TTestResult();
	virtual void __fastcall AddListener(_di_ITestListener listener);
	void __fastcall RunSuite(_di_ITest test)/* overload */;
	virtual void __fastcall AddSuccess(_di_ITest test);
	TTestFailure* __fastcall AddFailure(_di_ITest test, System::Sysutils::Exception* e, void * Addrs)/* overload */;
	TTestFailure* __fastcall AddFailure(_di_ITest test, void * Addrs, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual TTestFailure* __fastcall AddError(_di_ITest test, System::Sysutils::Exception* e, void * Addrs, System::UnicodeString msg = System::UnicodeString());
	virtual void __fastcall Stop();
	virtual bool __fastcall ShouldStop();
	virtual int __fastcall RunCount();
	virtual int __fastcall ErrorCount();
	virtual int __fastcall FailureCount();
	TTestFailure* __fastcall GetError(int idx);
	TTestFailure* __fastcall GetFailure(int idx);
	virtual bool __fastcall WasStopped();
	virtual bool __fastcall WasSuccessful();
	__property bool BreakOnFailures = {read=FBreakOnFailures, write=FBreakOnFailures, nodefault};
	__property bool FailsIfNoChecksExecuted = {read=FFailsIfNoChecksExecuted, write=FFailsIfNoChecksExecuted, nodefault};
	__property bool FailsIfMemoryLeaked = {read=FFailsIfMemoryLeaked, write=FFailsIfMemoryLeaked, nodefault};
	__property bool IgnoresMemoryLeakInSetUpTearDown = {read=FIgnoresMemoryLeakInSetUpTearDown, write=FIgnoresMemoryLeakInSetUpTearDown, nodefault};
	__property bool MemoryLeakIgnoredInSetupOrTearDown = {read=FMemoryLeakIgnoredInSetupOrTearDown, write=FMemoryLeakIgnoredInSetupOrTearDown, nodefault};
	__property __int64 TotalTime = {read=FTotalTime};
	__property TTestFailure* Errors[int i] = {read=GetError};
	__property TTestFailure* Failures[int i] = {read=GetFailure};
	__property int OverRides = {read=FOverRides, write=FOverRides, nodefault};
};


class PASCALIMPLEMENTATION TAbstractTest : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	System::UnicodeString FTestName;
	bool FEnabled;
	__int64 FStartTime;
	__int64 FStopTime;
	int FRunCount;
	_di_IStatusListener FStatusListener;
	System::Classes::TStrings* FStatusStrings;
	ExceptionClass FExpectedException;
	bool FCheckCalled;
	bool FFailsOnNoChecksExecuted;
	bool FFailsOnMemoryLeak;
	bool FTestMethodInvoked;
	bool FFailsOnMemoryRecovery;
	bool FIgnoreSetUpTearDownLeaks;
	bool FMemoryLeakIgnoredInSetupTearDown;
	TAllowedLeakArray FAllowedLeakList;
	System::Word FAllowedLeakListIndex;
	System::TObject* FGUIObject;
	virtual void __fastcall Invoke(TTestMethod AMethod);
	virtual void __fastcall RunWithFixture(TTestResult* testResult);
	virtual void __fastcall RunTest(TTestResult* testResult);
	virtual void __fastcall SetUp();
	virtual void __fastcall TearDown();
	virtual void __fastcall SetStartTime(__int64 Value);
	virtual __int64 __fastcall GetStartTime();
	virtual void __fastcall SetStopTime(__int64 Value);
	virtual __int64 __fastcall GetStopTime();
	virtual int __fastcall GetRunCount();
	virtual void __fastcall SetRunCount(int Value);
	void __fastcall SetGUIObject(System::TObject* const guiObject);
	System::TObject* __fastcall GetGUIObject();
	void __fastcall SetFailsOnNoChecksExecuted(const bool Value);
	bool __fastcall GetFailsOnNoChecksExecuted();
	bool __fastcall GetFailsOnMemoryLeak();
	void __fastcall SetFailsOnMemoryLeak(const bool Value);
	System::UnicodeString __fastcall GetMemDiffStr(void * expected, void * actual, unsigned long size, System::UnicodeString msg);
	int __fastcall GetAllowedMemoryLeakSize();
	void __fastcall SetAllowedMemoryLeakSize(const int NewSize);
	bool __fastcall GetFailsOnMemoryRecovery();
	void __fastcall SetFailsOnMemoryRecovery(const bool Value);
	bool __fastcall GetIgnoreSetUpTearDownLeaks();
	void __fastcall SetIgnoreSetUpTearDownLeaks(const bool Value);
	bool __fastcall GetMemoryLeakIgnoredInSetupTearDown();
	void __fastcall SetMemoryLeakIgnoredInSetupTearDown(const bool Value);
	void __fastcall SetAllowedLeakArray(int *AllowedList, const int AllowedList_High);
	int __fastcall GetAllowedLeak();
	TListIterator __fastcall GetAllowedLeaksIterator();
	
public:
	__fastcall TAbstractTest(System::UnicodeString AName);
	__fastcall virtual ~TAbstractTest();
	virtual System::UnicodeString __fastcall GetName();
	virtual bool __fastcall GetEnabled();
	virtual void __fastcall SetEnabled(bool value);
	virtual System::Classes::_di_IInterfaceList __fastcall Tests();
	virtual int __fastcall CountTestCases();
	virtual int __fastcall CountEnabledTestCases();
	TTestResult* __fastcall Run()/* overload */;
	void __fastcall Run(TTestResult* testResult)/* overload */;
	bool __fastcall GetTestMethodInvoked();
	void __fastcall SetTestMethodInvoked(const bool Value);
	virtual unsigned __fastcall ElapsedTestTime();
	void __fastcall SetStatusListener(_di_IStatusListener Listener);
	void __fastcall Status(const System::UnicodeString Msg);
	System::UnicodeString __fastcall GetStatus();
	void __fastcall LoadConfiguration(const System::UnicodeString fileName, const bool useRegistry, const bool useMemIni)/* overload */;
	virtual void __fastcall LoadConfiguration(System::Inifiles::TCustomIniFile* const iniFile, const System::UnicodeString section)/* overload */;
	void __fastcall SaveConfiguration(const System::UnicodeString fileName, const bool useRegistry, const bool useMemIni)/* overload */;
	virtual void __fastcall SaveConfiguration(System::Inifiles::TCustomIniFile* const iniFile, const System::UnicodeString section)/* overload */;
	__property System::UnicodeString Name = {read=GetName};
	__property bool Enabled = {read=GetEnabled, write=SetEnabled, nodefault};
	System::UnicodeString __fastcall BoolToStr(bool ABool);
	virtual void __fastcall Check(bool condition, System::UnicodeString msg = System::UnicodeString());
	virtual void __fastcall CheckTrue(bool condition, System::UnicodeString msg = System::UnicodeString());
	virtual void __fastcall CheckFalse(bool condition, System::UnicodeString msg = System::UnicodeString());
	virtual void __fastcall CheckEquals(System::Extended expected, System::Extended actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckEquals(System::Extended expected, System::Extended actual, System::Extended delta, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckEquals(int expected, int actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckEquals(unsigned expected, unsigned actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckEquals(__int64 expected, __int64 actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckEquals(unsigned __int64 expected, unsigned __int64 actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckEquals(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckEquals(System::ShortString &expected, System::ShortString &actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckEqualsString(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg = System::UnicodeString());
	virtual void __fastcall CheckEquals(System::RawByteString expected, System::RawByteString actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckEqualsWideString(System::WideString expected, System::WideString actual, System::UnicodeString msg = System::UnicodeString());
	virtual void __fastcall CheckEqualsMem(void * expected, void * actual, unsigned long size, System::UnicodeString msg = System::UnicodeString());
	virtual void __fastcall CheckEquals(bool expected, bool actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckEqualsBin(unsigned long expected, unsigned long actual, System::UnicodeString msg = System::UnicodeString(), int digits = 0x20);
	virtual void __fastcall CheckEqualsHex(unsigned long expected, unsigned long actual, System::UnicodeString msg = System::UnicodeString(), int digits = 0x8);
	virtual void __fastcall CheckEquals(System::TArray__1<System::WideChar> expected, System::TArray__1<System::WideChar> actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNotEquals(int expected, int actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNotEquals(unsigned expected, unsigned actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNotEquals(__int64 expected, __int64 actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNotEquals(System::Extended expected, System::Extended actual, System::Extended delta = 0.000000E+00, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNotEquals(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNotEquals(System::ShortString &expected, System::ShortString &actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNotEqualsString(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg = System::UnicodeString());
	virtual void __fastcall CheckNotEquals(System::RawByteString expected, System::RawByteString actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNotEqualsWideString(const System::WideString expected, const System::WideString actual, System::UnicodeString msg = System::UnicodeString());
	virtual void __fastcall CheckNotEqualsMem(void * expected, void * actual, unsigned long size, System::UnicodeString msg = System::UnicodeString());
	virtual void __fastcall CheckNotEquals(bool expected, bool actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNotEqualsBin(unsigned long expected, unsigned long actual, System::UnicodeString msg = System::UnicodeString(), int digits = 0x20);
	virtual void __fastcall CheckNotEqualsHex(unsigned long expected, unsigned long actual, System::UnicodeString msg = System::UnicodeString(), int digits = 0x8);
	virtual void __fastcall CheckNotEquals(System::TArray__1<System::WideChar> expected, System::TArray__1<System::WideChar> actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNotNull(System::_di_IInterface obj, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNull(System::_di_IInterface obj, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckSame(System::_di_IInterface expected, System::_di_IInterface actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckSame(System::TObject* expected, System::TObject* actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNotNull(System::TObject* obj, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckNull(System::TObject* obj, System::UnicodeString msg = System::UnicodeString())/* overload */;
	void __fastcall CheckException(TTestMethod AMethod, System::TClass AExceptionClass, System::UnicodeString msg = System::UnicodeString());
	virtual void __fastcall CheckEquals(System::TClass expected, System::TClass actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckInherits(System::TClass expected, System::TClass actual, System::UnicodeString msg = System::UnicodeString())/* overload */;
	virtual void __fastcall CheckIs(System::TObject* AObject, System::TClass AClass, System::UnicodeString msg = System::UnicodeString())/* overload */;
	bool __fastcall CompareFloatRelative(System::Extended expected, System::Extended actual)/* overload */;
	bool __fastcall CompareFloatRelative(System::Extended expected, System::Extended actual, System::Extended RelativeError)/* overload */;
	virtual void __fastcall Fail(System::UnicodeString msg, void * ErrorAddrs = (void *)(0x0))/* overload */;
	virtual void __fastcall FailEquals(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0))/* overload */;
	virtual void __fastcall FailNotEquals(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0))/* overload */;
	virtual void __fastcall FailNotSame(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0))/* overload */;
	System::UnicodeString __fastcall EqualsErrorMessage(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg)/* overload */;
	System::UnicodeString __fastcall NotEqualsErrorMessage(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg)/* overload */;
	System::UnicodeString __fastcall NotSameErrorMessage(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg)/* overload */;
	virtual void __fastcall FailEquals(System::WideString expected, System::WideString actual, System::UnicodeString msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0))/* overload */;
	virtual void __fastcall FailNotEquals(System::WideString expected, System::WideString actual, System::UnicodeString msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0))/* overload */;
	virtual void __fastcall FailNotSame(System::WideString expected, System::WideString actual, System::UnicodeString msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0))/* overload */;
	System::WideString __fastcall EqualsErrorMessage(System::WideString expected, System::WideString actual, System::UnicodeString msg)/* overload */;
	System::WideString __fastcall NotEqualsErrorMessage(System::WideString expected, System::WideString actual, System::UnicodeString msg)/* overload */;
	System::WideString __fastcall NotSameErrorMessage(System::WideString expected, System::WideString actual, System::UnicodeString msg)/* overload */;
	virtual void __fastcall StopTests(System::UnicodeString msg = System::UnicodeString());
	void __fastcall CheckMethodIsNotEmpty(void * MethodPointer);
	void __fastcall StartExpectingException(ExceptionClass e);
	void __fastcall StopExpectingException(System::UnicodeString msg = System::UnicodeString());
	__property ExceptionClass ExpectedException = {read=FExpectedException, write=StartExpectingException};
	
__published:
	__property bool FailsOnNoChecksExecuted = {read=GetFailsOnNoChecksExecuted, write=SetFailsOnNoChecksExecuted, nodefault};
	__property bool FailsOnMemoryLeak = {read=GetFailsOnMemoryLeak, write=SetFailsOnMemoryLeak, nodefault};
	__property bool TestMethodInvoked = {read=GetTestMethodInvoked, write=SetTestMethodInvoked, nodefault};
	__property int AllowedMemoryLeakSize = {read=GetAllowedMemoryLeakSize, write=SetAllowedMemoryLeakSize, nodefault};
	__property TListIterator AllowedLeaksIterator = {read=GetAllowedLeaksIterator};
	__property bool FailsOnMemoryRecovery = {read=GetFailsOnMemoryRecovery, write=SetFailsOnMemoryRecovery, nodefault};
	__property bool IgnoreSetUpTearDownLeaks = {read=GetIgnoreSetUpTearDownLeaks, write=SetIgnoreSetUpTearDownLeaks, nodefault};
private:
	void *__ITest;	// ITest 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {89CCD557-7DE1-4814-B033-ABAFE0870EC7}
	operator _di_ITest()
	{
		_di_ITest intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ITest*(void) { return (ITest*)&__ITest; }
	#endif
	
};


class PASCALIMPLEMENTATION TTestCase : public TAbstractTest
{
	typedef TAbstractTest inherited;
	
protected:
	TTestMethod fMethod;
	virtual void __fastcall Invoke(TTestMethod AMethod);
	virtual void __fastcall RunWithFixture(TTestResult* testResult);
	virtual void __fastcall RunTest(TTestResult* testResult);
	
public:
	__fastcall virtual TTestCase(System::UnicodeString MethodName)/* overload */;
	__fastcall virtual TTestCase(System::UnicodeString MethodName, __int64 RunCount)/* overload */;
	__classmethod virtual _di_ITestSuite __fastcall Suite();
	HIDESBASE void __fastcall Run(TTestResult* testResult)/* overload */;
public:
	/* TAbstractTest.Destroy */ inline __fastcall virtual ~TTestCase() { }
	
	/* Hoisted overloads: */
	
public:
	inline TTestResult* __fastcall  Run(){ return TAbstractTest::Run(); }
	
private:
	void *__ITest;	// ITest 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {89CCD557-7DE1-4814-B033-ABAFE0870EC7}
	operator _di_ITest()
	{
		_di_ITest intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ITest*(void) { return (ITest*)&__ITest; }
	#endif
	
};


typedef void * TValueData;

typedef System::TObject* *PObject;

// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TConverter__1 : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	__classmethod System::UnicodeString __fastcall ValueToString(System::Typinfo::PTypeInfo Info, unsigned Size, void * Value);
	
public:
	__classmethod System::UnicodeString __fastcall ToString(T Value);
public:
	/* TObject.Create */ inline __fastcall TConverter__1() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TConverter__1() { }
	
};


class PASCALIMPLEMENTATION TGenericTestCase : public TTestCase
{
	typedef TTestCase inherited;
	
private:
	template<typename T> __classmethod int __fastcall Compare(const T Expected, const T Actual);
	
public:
	template<typename T> HIDESBASE void __fastcall CheckEquals(T Expected, T Actual, System::UnicodeString Msg = System::UnicodeString())/* overload */;
	template<typename T> HIDESBASE void __fastcall CheckNotEquals(T Expected, T Actual, System::UnicodeString Msg = System::UnicodeString())/* overload */;
	template<typename T> HIDESBASE void __fastcall FailEquals(T Expected, T Actual, System::UnicodeString Msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0))/* overload */;
	template<typename T> HIDESBASE void __fastcall FailNotEquals(T Expected, T Actual, System::UnicodeString Msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0))/* overload */;
	template<typename T> HIDESBASE System::UnicodeString __fastcall EqualsErrorMessage(T Expected, T Actual, System::UnicodeString Msg)/* overload */;
	template<typename T> HIDESBASE System::UnicodeString __fastcall NotEqualsErrorMessage(T Expected, T Actual, System::UnicodeString Msg)/* overload */;
public:
	/* TTestCase.Create */ inline __fastcall virtual TGenericTestCase(System::UnicodeString MethodName)/* overload */ : TTestCase(MethodName) { }
	/* TTestCase.Create */ inline __fastcall virtual TGenericTestCase(System::UnicodeString MethodName, __int64 RunCount)/* overload */ : TTestCase(MethodName, RunCount) { }
	
public:
	/* TAbstractTest.Destroy */ inline __fastcall virtual ~TGenericTestCase() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  CheckEquals(System::Extended expected, System::Extended actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, msg); }
	inline void __fastcall  CheckEquals(System::Extended expected, System::Extended actual, System::Extended delta, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, delta, msg); }
	inline void __fastcall  CheckEquals(int expected, int actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, msg); }
	inline void __fastcall  CheckEquals(unsigned expected, unsigned actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, msg); }
	inline void __fastcall  CheckEquals(__int64 expected, __int64 actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, msg); }
	inline void __fastcall  CheckEquals(unsigned __int64 expected, unsigned __int64 actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, msg); }
	inline void __fastcall  CheckEquals(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, msg); }
	inline void __fastcall  CheckEquals(System::ShortString &expected, System::ShortString &actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, msg); }
	inline void __fastcall  CheckEquals(System::RawByteString expected, System::RawByteString actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, msg); }
	inline void __fastcall  CheckEquals(bool expected, bool actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, msg); }
	inline void __fastcall  CheckEquals(System::TArray__1<System::WideChar> expected, System::TArray__1<System::WideChar> actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, msg); }
	inline void __fastcall  CheckEquals(System::TClass expected, System::TClass actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckEquals(expected, actual, msg); }
	inline void __fastcall  CheckNotEquals(int expected, int actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckNotEquals(expected, actual, msg); }
	inline void __fastcall  CheckNotEquals(unsigned expected, unsigned actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckNotEquals(expected, actual, msg); }
	inline void __fastcall  CheckNotEquals(__int64 expected, __int64 actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckNotEquals(expected, actual, msg); }
	inline void __fastcall  CheckNotEquals(System::Extended expected, System::Extended actual, System::Extended delta = 0.000000E+00, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckNotEquals(expected, actual, delta, msg); }
	inline void __fastcall  CheckNotEquals(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckNotEquals(expected, actual, msg); }
	inline void __fastcall  CheckNotEquals(System::ShortString &expected, System::ShortString &actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckNotEquals(expected, actual, msg); }
	inline void __fastcall  CheckNotEquals(System::RawByteString expected, System::RawByteString actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckNotEquals(expected, actual, msg); }
	inline void __fastcall  CheckNotEquals(bool expected, bool actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckNotEquals(expected, actual, msg); }
	inline void __fastcall  CheckNotEquals(System::TArray__1<System::WideChar> expected, System::TArray__1<System::WideChar> actual, System::UnicodeString msg = System::UnicodeString()){ TAbstractTest::CheckNotEquals(expected, actual, msg); }
	inline void __fastcall  FailEquals(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0)){ TAbstractTest::FailEquals(expected, actual, msg, ErrorAddrs); }
	inline void __fastcall  FailEquals(System::WideString expected, System::WideString actual, System::UnicodeString msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0)){ TAbstractTest::FailEquals(expected, actual, msg, ErrorAddrs); }
	inline void __fastcall  FailNotEquals(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0)){ TAbstractTest::FailNotEquals(expected, actual, msg, ErrorAddrs); }
	inline void __fastcall  FailNotEquals(System::WideString expected, System::WideString actual, System::UnicodeString msg = System::UnicodeString(), void * ErrorAddrs = (void *)(0x0)){ TAbstractTest::FailNotEquals(expected, actual, msg, ErrorAddrs); }
	inline System::UnicodeString __fastcall  EqualsErrorMessage(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg){ return TAbstractTest::EqualsErrorMessage(expected, actual, msg); }
	inline System::WideString __fastcall  EqualsErrorMessage(System::WideString expected, System::WideString actual, System::UnicodeString msg){ return TAbstractTest::EqualsErrorMessage(expected, actual, msg); }
	inline System::UnicodeString __fastcall  NotEqualsErrorMessage(System::UnicodeString expected, System::UnicodeString actual, System::UnicodeString msg){ return TAbstractTest::NotEqualsErrorMessage(expected, actual, msg); }
	inline System::WideString __fastcall  NotEqualsErrorMessage(System::WideString expected, System::WideString actual, System::UnicodeString msg){ return TAbstractTest::NotEqualsErrorMessage(expected, actual, msg); }
	
private:
	void *__ITest;	// ITest 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {89CCD557-7DE1-4814-B033-ABAFE0870EC7}
	operator _di_ITest()
	{
		_di_ITest intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ITest*(void) { return (ITest*)&__ITest; }
	#endif
	
};


class PASCALIMPLEMENTATION TTestSuite : public TAbstractTest
{
	typedef TAbstractTest inherited;
	
protected:
	System::Classes::_di_IInterfaceList FTests;
	virtual void __fastcall RunTest(TTestResult* testResult);
	
public:
	__fastcall TTestSuite()/* overload */;
	__fastcall TTestSuite(System::UnicodeString AName)/* overload */;
	__fastcall TTestSuite(TTestCaseClass TestClass)/* overload */;
	__fastcall TTestSuite(System::UnicodeString AName, const _di_ITest *Tests, const int Tests_High)/* overload */;
	virtual int __fastcall CountTestCases();
	virtual int __fastcall CountEnabledTestCases();
	virtual System::Classes::_di_IInterfaceList __fastcall Tests();
	virtual void __fastcall AddTest(_di_ITest ATest);
	virtual void __fastcall AddTests(TTestCaseClass testClass);
	virtual void __fastcall AddSuite(_di_ITestSuite suite);
	virtual void __fastcall LoadConfiguration(System::Inifiles::TCustomIniFile* const iniFile, const System::UnicodeString section)/* overload */;
	virtual void __fastcall SaveConfiguration(System::Inifiles::TCustomIniFile* const iniFile, const System::UnicodeString section)/* overload */;
public:
	/* TAbstractTest.Destroy */ inline __fastcall virtual ~TTestSuite() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  LoadConfiguration(const System::UnicodeString fileName, const bool useRegistry, const bool useMemIni){ TAbstractTest::LoadConfiguration(fileName, useRegistry, useMemIni); }
	inline void __fastcall  SaveConfiguration(const System::UnicodeString fileName, const bool useRegistry, const bool useMemIni){ TAbstractTest::SaveConfiguration(fileName, useRegistry, useMemIni); }
	
private:
	void *__ITestSuite;	// ITestSuite 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {89CCD557-7DE1-4814-B033-ABAFE0870EC7}
	operator _di_ITest()
	{
		_di_ITest intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ITest*(void) { return (ITest*)&__ITestSuite; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C20E38EF-7369-44D9-9D84-08E84EC1DCF0}
	operator _di_ITestSuite()
	{
		_di_ITestSuite intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ITestSuite*(void) { return (ITestSuite*)&__ITestSuite; }
	#endif
	
};


class PASCALIMPLEMENTATION TTestFailure : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	_di_ITest FFailedTest;
	System::TClass FThrownExceptionClass;
	System::UnicodeString FThrownExceptionMessage;
	void *FThrownExceptionAddress;
	System::UnicodeString FStackTrace;
	System::UnicodeString __fastcall CaptureStackTrace(System::Sysutils::Exception* ThrownException, void * ThrownExceptionAddress);
	
public:
	__fastcall TTestFailure(_di_ITest FailedTest, System::Sysutils::Exception* ThrownException, void * Addrs, System::UnicodeString msg)/* overload */;
	__fastcall TTestFailure(_di_ITest FailedTest, void * Addrs, System::UnicodeString msg)/* overload */;
	virtual _di_ITest __fastcall FailedTest();
	virtual System::TClass __fastcall ThrownExceptionClass();
	virtual System::UnicodeString __fastcall ThrownExceptionName();
	virtual System::UnicodeString __fastcall ThrownExceptionMessage();
	virtual void * __fastcall ThrownExceptionAddress();
	virtual System::UnicodeString __fastcall LocationInfo();
	virtual System::UnicodeString __fastcall AddressInfo();
	virtual System::UnicodeString __fastcall StackTrace();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TTestFailure() { }
	
};


class PASCALIMPLEMENTATION TMethodEnumerator : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<System::UnicodeString> _TMethodEnumerator__1;
	
	typedef System::DynamicArray<__int64> _TMethodEnumerator__2;
	
	
protected:
	_TMethodEnumerator__1 FMethodNameList;
	_TMethodEnumerator__2 FMethodRunCountList;
	System::UnicodeString __fastcall GetNameOfMethod(int idx);
	__int64 __fastcall GetRunCountOfMethod(int idx);
	int __fastcall GetMethodCount();
	
public:
	__fastcall TMethodEnumerator(System::TClass AClass);
	__property int MethodCount = {read=GetMethodCount, nodefault};
	__property System::UnicodeString NameOfMethod[int idx] = {read=GetNameOfMethod};
	__property __int64 RunCountOfMethod[int idx] = {read=GetRunCountOfMethod};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMethodEnumerator() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString rcs_id;
extern DELPHI_PACKAGE System::UnicodeString rcs_version;
#define sExpButWasFmt u"%sexpected: <%s> but was: <%s>"
#define sExpAndActualFmt u"%sexpected and actual were: <%s>"
extern DELPHI_PACKAGE System::UnicodeString __fastcall TestDataDir(void);
extern DELPHI_PACKAGE _di_IMemLeakMonitor __fastcall MemLeakMonitor(void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall PtrToStr(void * p);
extern DELPHI_PACKAGE void * __fastcall CallerAddr _DEPRECATED_ATTRIBUTE1("Use ReturnAddress") (void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall PointerToLocationInfo(void * Addrs);
extern DELPHI_PACKAGE System::UnicodeString __fastcall PointerToAddressInfo(void * Addrs);
extern DELPHI_PACKAGE bool __fastcall IsTestMethod(_di_ITest aTest);
extern DELPHI_PACKAGE bool __fastcall IsDecorator(_di_ITest aTest);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetDUnitRegistryKey(void);
extern DELPHI_PACKAGE void __fastcall SetDUnitRegistryKey(const System::UnicodeString NewKey);
extern DELPHI_PACKAGE int __fastcall FirstByteDiff(void * p1, void * p2, unsigned long size, /* out */ System::Byte &b1, /* out */ System::Byte &b2);
extern DELPHI_PACKAGE _di_ITestSuite __fastcall TestSuite(System::UnicodeString AName, const _di_ITest *Tests, const int Tests_High);
extern DELPHI_PACKAGE void __fastcall RegisterTest(System::UnicodeString SuitePath, _di_ITest test)/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterTest(_di_ITest test)/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterTests(System::UnicodeString SuitePath, const _di_ITest *Tests, const int Tests_High)/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterTests(const _di_ITest *Tests, const int Tests_High)/* overload */;
extern DELPHI_PACKAGE _di_ITestSuite __fastcall RegisteredTests(void);
extern DELPHI_PACKAGE TTestResult* __fastcall RunTest(_di_ITest suite, const _di_ITestListener *listeners, const int listeners_High)/* overload */;
extern DELPHI_PACKAGE TTestResult* __fastcall RunRegisteredTests(const _di_ITestListener *listeners, const int listeners_High);
extern DELPHI_PACKAGE void __fastcall ClearRegistry(void);
}	/* namespace Testframework */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_TESTFRAMEWORK)
using namespace Testframework;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TestframeworkHPP
