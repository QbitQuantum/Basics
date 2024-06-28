// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.DBX.Migrate.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Dbx_MigrateHPP
#define Firedac_Dbx_MigrateHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Comp.Client.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Dbx
{
namespace Migrate
{
//-- forward type declarations -----------------------------------------------
struct TFDDBXTransactionDesc;
class DELPHICLASS TFDDBXTransaction;
struct TFDDBXConnectionAdminHelper /* Helper for class 'Firedac::Comp::Client::TFDCustomManager*' */;
struct TFDDBXConnectionHelper /* Helper for class 'Firedac::Comp::Client::TFDCustomConnection*' */;
struct TFDDBXDataSetHelper /* Helper for class 'Firedac::Comp::Client::TFDRdbmsDataSet*' */;
//-- type declarations -------------------------------------------------------
typedef Data::Db::TDataSet TFDDBXProcParamList;

struct DECLSPEC_DRECORD TFDDBXTransactionDesc
{
public:
#ifndef __x86_64__
	unsigned TransactionID;
	unsigned GlobalID;
#else /* __x86_64__ */
	unsigned long TransactionID;
	unsigned long GlobalID;
#endif /* __x86_64__ */
	Firedac::Stan::Option::TFDTxIsolation IsolationLevel;
};


#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDDBXTransaction : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Firedac::Comp::Client::TFDCustomConnection* FConnection;
#ifndef __x86_64__
	unsigned FSerialID;
#else /* __x86_64__ */
	unsigned long FSerialID;
#endif /* __x86_64__ */
	
public:
	__property Firedac::Comp::Client::TFDCustomConnection* Connection = {read=FConnection};
public:
	/* TObject.Create */ inline __fastcall TFDDBXTransaction() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFDDBXTransaction() { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Migrate */
}	/* namespace Dbx */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_DBX_MIGRATE)
using namespace Firedac::Dbx::Migrate;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_DBX)
using namespace Firedac::Dbx;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Dbx_MigrateHPP
