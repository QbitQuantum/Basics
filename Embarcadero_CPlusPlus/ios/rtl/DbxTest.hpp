// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DbxTest.pas' rev: 34.00 (iOS)

#ifndef DbxtestHPP
#define DbxtestHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <TestFrameworkExtension.hpp>
#include <System.Classes.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXMetaDataProvider.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <TestFramework.hpp>

//-- user supplied -----------------------------------------------------------

namespace Dbxtest
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXTestCase;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXTestCase : public Testframeworkextension::TTestCaseExtension
{
	typedef Testframeworkextension::TTestCaseExtension inherited;
	
private:
	System::UnicodeString FDBXName;
	Data::Dbxmetadataprovider::TDBXMetaDataProvider* FMetaDataProvider;
	System::Generics::Collections::TList__1<System::TObject*>* FTearDownList;
	void __fastcall FreeTearDownList();
	
protected:
	Data::Dbxcommon::TDBXConnection* FConnection;
	bool __fastcall IsExtendedMetaDataBeingUsed(System::UnicodeString ConnectionName);
	virtual Data::Dbxcommon::TDBXConnection* __fastcall GetDbxConnection();
	void __fastcall ExecuteStatement(const System::UnicodeString CommandText);
	void __fastcall ExecuteStatementIgnoreError(const System::UnicodeString CommandText);
	Data::Dbxmetadataprovider::TDBXMetaDataProvider* __fastcall GetMetaDataProvider();
	bool __fastcall IsTypeSupported(int DataType, int SubType);
	bool __fastcall GetIsCreateTableInMultiStatementTransactionSupported();
	System::TObject* __fastcall StartMetaDataTransaction();
	void __fastcall CommitFreeAndNilMetaDataTransaction(System::TObject* &Transaction);
	void __fastcall RollbackMetaDataTransaction(System::TObject* &Transaction);
	virtual void __fastcall TearDown();
	
public:
	__fastcall virtual TDBXTestCase(System::UnicodeString MethodName)/* overload */;
	__fastcall virtual ~TDBXTestCase();
	void __fastcall FreeOnTearDown(System::TObject* Item);
	virtual System::UnicodeString __fastcall GetName();
	void __fastcall SetName(System::UnicodeString AName);
	void __fastcall DropTable(System::UnicodeString TableName);
	System::UnicodeString __fastcall GetHostId();
	__property Data::Dbxcommon::TDBXConnection* DbxConnection = {read=GetDbxConnection};
	virtual void __fastcall CloseDbxConnection();
	__property Data::Dbxmetadataprovider::TDBXMetaDataProvider* MetaDataProvider = {read=GetMetaDataProvider};
	__property bool IsCreateTableInMultiStatementTransactionSupported = {read=GetIsCreateTableInMultiStatementTransactionSupported, nodefault};
public:
	/* TTestCase.Create */ inline __fastcall virtual TDBXTestCase(System::UnicodeString MethodName, __int64 RunCount)/* overload */ : Testframeworkextension::TTestCaseExtension(MethodName, RunCount) { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define sConnectionName u"connection"
#define sAdoDbxClientProvider u"Borland.Data.AdoDbxClient"
}	/* namespace Dbxtest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DBXTEST)
using namespace Dbxtest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DbxtestHPP
