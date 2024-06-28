// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBStoredProc.pas' rev: 34.00 (Android)

#ifndef Ibx_IbstoredprocHPP
#define Ibx_IbstoredprocHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <IBX.IB.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBCustomDataSet.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IBExternals.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibstoredproc
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBStoredProc;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIBStoredProc : public Ibx::Ibcustomdataset::TIBCustomDataSet
{
	typedef Ibx::Ibcustomdataset::TIBCustomDataSet inherited;
	
private:
	void * *FStmtHandle;
	System::UnicodeString FProcName;
	Data::Db::TParams* FParams;
	bool FPrepared;
	System::Classes::TStrings* FNameList;
	void __fastcall SetParamsList(Data::Db::TParams* Value);
	void __fastcall FreeStatement();
	System::Classes::TStrings* __fastcall GetStoredProcedureNames();
	void __fastcall GetStoredProcedureNamesFromServer();
	void __fastcall CreateParamDesc();
	void __fastcall SetParams();
	void __fastcall SetParamsFromCursor();
	void __fastcall GenerateSQL();
	void __fastcall FetchDataIntoOutputParams();
	void __fastcall ReadParamData(System::Classes::TReader* Reader);
	void __fastcall WriteParamData(System::Classes::TWriter* Writer);
	Data::Db::TParams* __fastcall GetParams();
	
protected:
	virtual void __fastcall PSExecute();
	virtual System::UnicodeString __fastcall PSGetTableName();
	virtual Data::Db::TParams* __fastcall PSGetParams();
	virtual void __fastcall PSSetCommandText(const System::UnicodeString CommandText);
	virtual void __fastcall PSSetParams(Data::Db::TParams* AParams);
	virtual System::UnicodeString __fastcall PSGetCommandText();
	virtual Data::Db::TPSCommandType __fastcall PSGetCommandType();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall SetFiltered(bool Value);
	System::Word __fastcall GetParamsCount();
	void __fastcall SetPrepared(bool Value);
	void __fastcall SetPrepare(bool Value);
	void __fastcall SetProcName(System::UnicodeString Value);
	virtual void __fastcall Disconnect();
	virtual void __fastcall InternalOpen();
	virtual Data::Db::TParamsClass __fastcall GetParamsClass();
	
public:
	__fastcall virtual TIBStoredProc(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBStoredProc();
	void __fastcall CopyParams(Data::Db::TParams* Value);
	void __fastcall ExecProc();
	Data::Db::TParam* __fastcall ParamByName(const System::UnicodeString Value);
	void __fastcall Prepare();
	void __fastcall UnPrepare();
	__property System::Word ParamCount = {read=GetParamsCount, nodefault};
	__property Ibx::Ibexternals::PVoid StmtHandle = {read=FStmtHandle};
	__property bool Prepared = {read=FPrepared, write=SetPrepare, nodefault};
	__property System::Classes::TStrings* StoredProcedureNames = {read=GetStoredProcedureNames};
	
__published:
	__property System::UnicodeString StoredProcName = {read=FProcName, write=SetProcName};
	__property Data::Db::TParams* Params = {read=GetParams, write=SetParamsList, stored=false};
	__property Filtered = {default=0};
	__property BeforeDatabaseDisconnect;
	__property AfterDatabaseDisconnect;
	__property DatabaseFree;
	__property BeforeTransactionEnd;
	__property AfterTransactionEnd;
	__property TransactionFree;
	__property OnFilterRecord;
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibstoredproc */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBSTOREDPROC)
using namespace Ibx::Ibstoredproc;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbstoredprocHPP
