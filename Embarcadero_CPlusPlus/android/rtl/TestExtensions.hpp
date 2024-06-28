// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TestExtensions.pas' rev: 34.00 (Android)

#ifndef TestextensionsHPP
#define TestextensionsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.IniFiles.hpp>
#include <TestFramework.hpp>
#include <DUnitConsts.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Testextensions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTestDecorator;
class DELPHICLASS TTestSetup;
__interface DELPHIINTERFACE IRepeatedTest;
typedef System::DelphiInterface<IRepeatedTest> _di_IRepeatedTest;
class DELPHICLASS TRepeatedTest;
class DELPHICLASS TActiveTest;
class DELPHICLASS TExceptionTestCase;
class DELPHICLASS EMemoryError;
class DELPHICLASS TMemoryTest;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
typedef int TMemorySize;
#else /* __aarch64__ */
typedef long TMemorySize;
#endif /* __aarch64__ */

class PASCALIMPLEMENTATION TTestDecorator : public Testframework::TAbstractTest
{
	typedef Testframework::TAbstractTest inherited;
	
protected:
	System::UnicodeString FName;
	Testframework::_di_ITest FTest;
	System::Classes::_di_IInterfaceList FTests;
	Testframework::_di_ITest __fastcall GetTest();
	virtual void __fastcall RunTest(Testframework::TTestResult* ATestResult);
	
public:
	__fastcall TTestDecorator(Testframework::_di_ITest ATest, System::UnicodeString AName);
	virtual int __fastcall CountTestCases();
	virtual int __fastcall CountEnabledTestCases();
	virtual System::UnicodeString __fastcall GetName();
	virtual System::Classes::_di_IInterfaceList __fastcall Tests();
	virtual void __fastcall LoadConfiguration(System::Inifiles::TCustomIniFile* const iniFile, const System::UnicodeString section)/* overload */;
	virtual void __fastcall SaveConfiguration(System::Inifiles::TCustomIniFile* const iniFile, const System::UnicodeString section)/* overload */;
	__property Testframework::_di_ITest Test = {read=GetTest};
public:
	/* TAbstractTest.Destroy */ inline __fastcall virtual ~TTestDecorator() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  LoadConfiguration(const System::UnicodeString fileName, const bool useRegistry, const bool useMemIni){ Testframework::TAbstractTest::LoadConfiguration(fileName, useRegistry, useMemIni); }
	inline void __fastcall  SaveConfiguration(const System::UnicodeString fileName, const bool useRegistry, const bool useMemIni){ Testframework::TAbstractTest::SaveConfiguration(fileName, useRegistry, useMemIni); }
	
private:
	void *__ITestDecorator;	// Testframework::ITestDecorator 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {89CCD557-7DE1-4814-B033-ABAFE0870EC7}
	operator Testframework::_di_ITest()
	{
		Testframework::_di_ITest intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Testframework::ITest*(void) { return (Testframework::ITest*)&__ITestDecorator; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8B3FC229-3033-4590-AD5C-01914C6E2C9F}
	operator Testframework::_di_ITestDecorator()
	{
		Testframework::_di_ITestDecorator intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Testframework::ITestDecorator*(void) { return (Testframework::ITestDecorator*)&__ITestDecorator; }
	#endif
	
};


class PASCALIMPLEMENTATION TTestSetup : public TTestDecorator
{
	typedef TTestDecorator inherited;
	
public:
	__fastcall TTestSetup(Testframework::_di_ITest ATest, System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetName();
public:
	/* TAbstractTest.Destroy */ inline __fastcall virtual ~TTestSetup() { }
	
};


__interface  INTERFACE_UUID("{DF3B52FF-2645-42C2-958A-174FF87A19B8}") IRepeatedTest  : public System::IInterface 
{
	virtual bool __fastcall GetHaltOnError() = 0 ;
	virtual void __fastcall SetHaltOnError(const bool Value) = 0 ;
	__property bool HaltOnError = {read=GetHaltOnError, write=SetHaltOnError};
};

class PASCALIMPLEMENTATION TRepeatedTest : public TTestDecorator
{
	typedef TTestDecorator inherited;
	
private:
	int FTimesRepeat;
	bool FHaltOnError;
	bool __fastcall GetHaltOnError();
	void __fastcall SetHaltOnError(const bool Value);
	
protected:
	virtual void __fastcall RunTest(Testframework::TTestResult* ATestResult);
	
public:
	__fastcall TRepeatedTest(Testframework::_di_ITest ATest, int Iterations, System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetName();
	virtual int __fastcall CountTestCases();
	virtual int __fastcall CountEnabledTestCases();
	
__published:
	__property bool HaltOnError = {read=GetHaltOnError, write=SetHaltOnError, nodefault};
public:
	/* TAbstractTest.Destroy */ inline __fastcall virtual ~TRepeatedTest() { }
	
private:
	void *__IRepeatedTest;	// IRepeatedTest 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DF3B52FF-2645-42C2-958A-174FF87A19B8}
	operator _di_IRepeatedTest()
	{
		_di_IRepeatedTest intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IRepeatedTest*(void) { return (IRepeatedTest*)&__IRepeatedTest; }
	#endif
	
};


class PASCALIMPLEMENTATION TActiveTest : public TTestDecorator
{
	typedef TTestDecorator inherited;
	
public:
	/* TTestDecorator.Create */ inline __fastcall TActiveTest(Testframework::_di_ITest ATest, System::UnicodeString AName) : TTestDecorator(ATest, AName) { }
	
public:
	/* TAbstractTest.Destroy */ inline __fastcall virtual ~TActiveTest() { }
	
};


class PASCALIMPLEMENTATION TExceptionTestCase : public TTestDecorator
{
	typedef TTestDecorator inherited;
	
public:
	/* TTestDecorator.Create */ inline __fastcall TExceptionTestCase(Testframework::_di_ITest ATest, System::UnicodeString AName) : TTestDecorator(ATest, AName) { }
	
public:
	/* TAbstractTest.Destroy */ inline __fastcall virtual ~TExceptionTestCase() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EMemoryError : public Testframework::ETestFailure
{
	typedef Testframework::ETestFailure inherited;
	
public:
	/* ETestFailure.Create */ inline __fastcall EMemoryError()/* overload */ : Testframework::ETestFailure() { }
	/* ETestFailure.Create */ inline __fastcall EMemoryError(System::UnicodeString msg)/* overload */ : Testframework::ETestFailure(msg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EMemoryError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Testframework::ETestFailure(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EMemoryError(NativeUInt Ident)/* overload */ : Testframework::ETestFailure(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EMemoryError(System::PResStringRec ResStringRec)/* overload */ : Testframework::ETestFailure(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EMemoryError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Testframework::ETestFailure(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EMemoryError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Testframework::ETestFailure(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EMemoryError(const System::UnicodeString Msg, int AHelpContext) : Testframework::ETestFailure(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMemoryError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Testframework::ETestFailure(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMemoryError(NativeUInt Ident, int AHelpContext)/* overload */ : Testframework::ETestFailure(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMemoryError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Testframework::ETestFailure(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMemoryError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Testframework::ETestFailure(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMemoryError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Testframework::ETestFailure(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EMemoryError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TMemoryTestTypes : unsigned char { mttMemoryTestBeforeNormalTest, mttExecuteNormalTest, mttMemoryTestAfterNormalTest };

typedef System::Set<TMemoryTestTypes, TMemoryTestTypes::mttMemoryTestBeforeNormalTest, TMemoryTestTypes::mttMemoryTestAfterNormalTest> TMemoryTestTypesSet;

class PASCALIMPLEMENTATION TMemoryTest : public TTestDecorator
{
	typedef TTestDecorator inherited;
	
protected:
#ifndef __aarch64__
	int __fastcall MemoryAllocated();
#else /* __aarch64__ */
	long __fastcall MemoryAllocated();
#endif /* __aarch64__ */
	
public:
	virtual System::UnicodeString __fastcall GetName();
	virtual void __fastcall RunTest(Testframework::TTestResult* ATestResult);
public:
	/* TTestDecorator.Create */ inline __fastcall TMemoryTest(Testframework::_di_ITest ATest, System::UnicodeString AName) : TTestDecorator(ATest, AName) { }
	
public:
	/* TAbstractTest.Destroy */ inline __fastcall virtual ~TMemoryTest() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Testextensions */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_TESTEXTENSIONS)
using namespace Testextensions;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// TestextensionsHPP
