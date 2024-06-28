// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBBatchUpdate.pas' rev: 34.00 (Android)

#ifndef Ibx_IbbatchupdateHPP
#define Ibx_IbbatchupdateHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBSQL.hpp>
#include <IBX.IBExternals.hpp>
#include <System.Generics.Collections.hpp>
#include <IBX.IBHeader.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibbatchupdate
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBBatchError;
class DELPHICLASS TIBBatchErrorsEnumerator;
class DELPHICLASS TIBBatchUpdate;
//-- type declarations -------------------------------------------------------
typedef System::DynamicArray<NativeInt> TIBBatchErrors;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBBatchError : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	int Index;
	NativeInt ErrorCode;
public:
	/* TObject.Create */ inline __fastcall TIBBatchError() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIBBatchError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::Generics::Collections::TList__1<TIBBatchError*>* TIBBatchErrorList;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBBatchErrorsEnumerator : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FIndex;
	System::Generics::Collections::TList__1<TIBBatchError*>* FErrors;
	
public:
	__fastcall TIBBatchErrorsEnumerator(System::Generics::Collections::TList__1<TIBBatchError*>* Errors);
	TIBBatchError* __fastcall GetCurrent();
	bool __fastcall MoveNext();
	__property TIBBatchError* Current = {read=GetCurrent};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBBatchErrorsEnumerator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBBatchUpdate : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	int FBatchSize;
	Ibx::Ibdatabase::TIBBase* FBase;
	Ibx::Ibsql::TIBSQL* FBatchSQL;
	System::Generics::Collections::TList__1<TIBBatchError*>* FIBBatchErrorList;
	bool FPrepared;
	Ibx::Ibsql::TIBXSQLDA* __fastcall GetSQLParams();
	void __fastcall SetBatchSize(const int Value);
	bool __fastcall GetHasErrors();
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* const Value);
	void __fastcall SetTransaction(Ibx::Ibdatabase::TIBTransaction* const Value);
	System::Classes::TStrings* __fastcall GetSQL();
	void __fastcall SetSQL(System::Classes::TStrings* const Value);
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetDatabase();
	Ibx::Ibdatabase::TIBTransaction* __fastcall GetTransaction();
	Ibx::Ibheader::PISC_DB_HANDLE __fastcall GetDBHandle();
	Ibx::Ibheader::PISC_TR_HANDLE __fastcall GetTRHandle();
	
protected:
	System::Classes::TStrings* FSQL;
	System::Classes::TStrings* FProcessedSQL;
	void * *FHandle;
	Ibx::Ibsql::TIBXSQLDA* FSQLParams;
	Ibx::Ibsql::TIBSQLTypes FSQLType;
	void __fastcall PreprocessSQL();
	
public:
	__fastcall virtual TIBBatchUpdate(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBBatchUpdate();
	bool __fastcall Execute();
	void __fastcall Prepare();
	void __fastcall Unprepare();
	void __fastcall First();
	void __fastcall Next();
	void __fastcall Prior();
	HIDESBASE void __fastcall Insert();
	void __fastcall Post();
	void __fastcall Clear();
	NativeInt __fastcall Call(NativeInt ErrCode, bool RaiseError);
	HIDESBASE TIBBatchErrorsEnumerator* __fastcall GetEnumerator();
	__property Ibx::Ibsql::TIBXSQLDA* Params = {read=GetSQLParams};
	__property bool HasErrors = {read=GetHasErrors, nodefault};
	__property bool Prepared = {read=FPrepared, nodefault};
	__property Ibx::Ibheader::PISC_DB_HANDLE DBHandle = {read=GetDBHandle};
	__property Ibx::Ibheader::PISC_TR_HANDLE TRHandle = {read=GetTRHandle};
	
__published:
	__property System::Classes::TStrings* SQL = {read=GetSQL, write=SetSQL};
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=GetDatabase, write=SetDatabase};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=GetTransaction, write=SetTransaction};
	__property int BatchSize = {read=FBatchSize, write=SetBatchSize, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibbatchupdate */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBBATCHUPDATE)
using namespace Ibx::Ibbatchupdate;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbbatchupdateHPP
