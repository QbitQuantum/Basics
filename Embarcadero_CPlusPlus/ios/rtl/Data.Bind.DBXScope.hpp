// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Bind.DBXScope.pas' rev: 34.00 (iOS)

#ifndef Data_Bind_DbxscopeHPP
#define Data_Bind_DbxscopeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>
#include <Data.DB.hpp>
#include <Data.Bind.Components.hpp>
#include <System.Bindings.Helper.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.CustomScope.hpp>
#include <System.Bindings.CustomWrapper.hpp>
#include <System.Bindings.Factories.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <Data.SqlExpr.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Bind
{
namespace Dbxscope
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomParamsAdapter;
class DELPHICLASS TParamsAdapter;
class DELPHICLASS TSubDataSetProvider;
class DELPHICLASS TSubSQLDataSet;
class DELPHICLASS TSubClientDataSet;
class DELPHICLASS TCustomBindSourceDBX;
class DELPHICLASS TBindSourceDBX;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomParamsAdapter : public Data::Bind::Dbscope::TBaseRemoteAdapter
{
	typedef Data::Bind::Dbscope::TBaseRemoteAdapter inherited;
	
private:
	Data::Sqlexpr::TCustomSQLDataSet* FCustomSQLDataSet;
	bool FDeferActivate;
	Data::Bind::Objectscope::TAdapterNotifyEvent FBeforeExecute;
	Data::Bind::Objectscope::TAdapterNotifyEvent FAfterExecute;
	void __fastcall SetCustomSQLDataSet(Data::Sqlexpr::TCustomSQLDataSet* const Value);
	void __fastcall SetSQLDataSet(Data::Sqlexpr::TSQLDataSet* const Value);
	Data::Sqlexpr::TSQLDataSet* __fastcall GetSQLDataSet();
	void __fastcall SetSQLQuery(Data::Sqlexpr::TSQLQuery* const Value);
	Data::Sqlexpr::TSQLQuery* __fastcall GetSQLQuery();
	template<typename T> void __fastcall MakeParamField(Data::Db::TParam* AParam);
	void __fastcall AddFields();
	virtual Data::Db::TParams* __fastcall GetParams();
	Data::Sqlexpr::TSqlServerMethod* __fastcall GetSQLServerMethod();
	Data::Sqlexpr::TSQLStoredProc* __fastcall GetSQLStoredProc();
	void __fastcall SetSQLServerMethod(Data::Sqlexpr::TSqlServerMethod* const Value);
	void __fastcall SetSQLStoredProc(Data::Sqlexpr::TSQLStoredProc* const Value);
	
protected:
	virtual void __fastcall SetActive(bool AValue);
	virtual void __fastcall Loaded();
	virtual bool __fastcall GetCanModify();
	void __fastcall OnActiveChanged(System::TObject* Sender);
	virtual void __fastcall DoBeforeOpen();
	virtual void __fastcall DoAfterOpen();
	virtual void __fastcall DoAfterClose();
	virtual bool __fastcall GetCanActivate();
	virtual int __fastcall GetCount();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall DoAfterExecute();
	virtual void __fastcall DoExecute();
	virtual void __fastcall DoBeforeExecute();
	
public:
	__fastcall virtual TCustomParamsAdapter(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomParamsAdapter();
	virtual void __fastcall Execute();
	__property Data::Sqlexpr::TSQLDataSet* SQLDataSet = {read=GetSQLDataSet, write=SetSQLDataSet};
	__property Data::Sqlexpr::TSQLQuery* SQLQuery = {read=GetSQLQuery, write=SetSQLQuery};
	__property Data::Sqlexpr::TSqlServerMethod* SQLServerMethod = {read=GetSQLServerMethod, write=SetSQLServerMethod};
	__property Data::Sqlexpr::TSQLStoredProc* SQLStoredProc = {read=GetSQLStoredProc, write=SetSQLStoredProc};
	__property Data::Bind::Objectscope::TAdapterNotifyEvent BeforeExecute = {read=FBeforeExecute, write=FBeforeExecute};
	__property Data::Bind::Objectscope::TAdapterNotifyEvent AfterExecute = {read=FAfterExecute, write=FAfterExecute};
};


class PASCALIMPLEMENTATION TParamsAdapter : public TCustomParamsAdapter
{
	typedef TCustomParamsAdapter inherited;
	
__published:
	__property SQLQuery;
	__property SQLDataSet;
	__property SQLStoredProc;
	__property SQLServerMethod;
	__property Active;
	__property AutoPost;
	__property BeforeExecute;
	__property AfterExecute;
public:
	/* TCustomParamsAdapter.Create */ inline __fastcall virtual TParamsAdapter(System::Classes::TComponent* AOwner) : TCustomParamsAdapter(AOwner) { }
	/* TCustomParamsAdapter.Destroy */ inline __fastcall virtual ~TParamsAdapter() { }
	
};


class PASCALIMPLEMENTATION TSubDataSetProvider : public Datasnap::Provider::TDataSetProvider
{
	typedef Datasnap::Provider::TDataSetProvider inherited;
	
private:
	HIDESBASE void __fastcall SetDataSet(Data::Db::TDataSet* ADataSet);
	
public:
	__fastcall virtual ~TSubDataSetProvider();
	
private:
	Data::Db::TDataSet* __fastcall GetDataSet();
	
__published:
	__property Data::Db::TDataSet* DataSet = {read=GetDataSet, stored=false};
public:
	/* TDataSetProvider.Create */ inline __fastcall virtual TSubDataSetProvider(System::Classes::TComponent* AOwner) : Datasnap::Provider::TDataSetProvider(AOwner) { }
	
};


class PASCALIMPLEMENTATION TSubSQLDataSet : public Data::Sqlexpr::TSQLDataSet
{
	typedef Data::Sqlexpr::TSQLDataSet inherited;
	
private:
	void __fastcall SetSQLConnection(Data::Sqlexpr::TSQLConnection* AConnection);
	Data::Sqlexpr::TSQLConnection* __fastcall GetSQLConnection();
	
public:
	__fastcall virtual ~TSubSQLDataSet();
	
__published:
	__property Data::Sqlexpr::TSQLConnection* SQLConnection = {read=GetSQLConnection};
public:
	/* TSQLDataSet.Create */ inline __fastcall virtual TSubSQLDataSet(System::Classes::TComponent* AOwner)/* overload */ : Data::Sqlexpr::TSQLDataSet(AOwner) { }
	
public:
	/* TCustomSQLDataSet.Create */ inline __fastcall TSubSQLDataSet(System::Classes::TComponent* AOwner, Data::Dbxcommon::TDBXReader* DBXReader, bool AOwnsInstance)/* overload */ : Data::Sqlexpr::TSQLDataSet(AOwner, DBXReader, AOwnsInstance) { }
	
};


class PASCALIMPLEMENTATION TSubClientDataSet : public Datasnap::Dbclient::TClientDataSet
{
	typedef Datasnap::Dbclient::TClientDataSet inherited;
	
private:
	System::UnicodeString FReconcileError;
	HIDESBASE void __fastcall SetProviderName(const System::UnicodeString AName);
	TCustomBindSourceDBX* __fastcall GetBindScope();
	System::UnicodeString __fastcall GetProviderName();
	void __fastcall DefaultOnReconcileError(Datasnap::Dbclient::TCustomClientDataSet* DataSet, Datasnap::Dbclient::EReconcileError* E, Data::Db::TUpdateKind UpdateKind, Datasnap::Dbclient::TReconcileAction &Action);
	void __fastcall AutoApplyUpdates();
	
protected:
	virtual void __fastcall DoAfterPost();
	virtual void __fastcall DoAfterDelete();
	
__published:
	__property System::UnicodeString ProviderName = {read=GetProviderName, stored=false};
public:
	/* TCustomClientDataSet.Create */ inline __fastcall virtual TSubClientDataSet(System::Classes::TComponent* AOwner) : Datasnap::Dbclient::TClientDataSet(AOwner) { }
	/* TCustomClientDataSet.Destroy */ inline __fastcall virtual ~TSubClientDataSet() { }
	
};


class PASCALIMPLEMENTATION TCustomBindSourceDBX : public Data::Bind::Dbscope::TCustomBindSourceDB
{
	typedef Data::Bind::Dbscope::TCustomBindSourceDB inherited;
	
private:
	TSubClientDataSet* FClientDataSet;
	TSubDataSetProvider* FProvider;
	TSubSQLDataSet* FSQLDataSet;
	bool FAutoApply;
	void __fastcall AllocSQLDataSet();
	void __fastcall AllocClientDataSet();
	void __fastcall AllocProvider();
	void __fastcall SetActive(const bool Value);
	System::UnicodeString __fastcall GetCommandText();
	Data::Db::TSQLCommandType __fastcall GetCommandType();
	System::UnicodeString __fastcall GetDbxCommandType();
	int __fastcall GetMaxBlobSize();
	bool __fastcall GetParamCheck();
	Data::Db::TParams* __fastcall GetParams();
	System::UnicodeString __fastcall GetSortFieldNames();
	Data::Sqlexpr::TSQLConnection* __fastcall GetSqlConnection();
	void __fastcall SetCommandText(const System::UnicodeString Value);
	void __fastcall SetCommandType(const Data::Db::TSQLCommandType Value);
	void __fastcall SetDbxCommandType(const System::UnicodeString Value);
	void __fastcall SetMaxBlobSize(const int Value);
	void __fastcall SetParamCheck(const bool Value);
	void __fastcall SetParams(Data::Db::TParams* const Value);
	void __fastcall SetSortFieldNames(const System::UnicodeString Value);
	void __fastcall SetSqlConnection(Data::Sqlexpr::TSQLConnection* const Value);
	Data::Bind::Dbscope::TSubDataSource* __fastcall GetSubDataSource();
	System::UnicodeString __fastcall GetMasterFields();
	TCustomBindSourceDBX* __fastcall GetMasterSource();
	void __fastcall SetMasterDataSource(TCustomBindSourceDBX* const Value);
	void __fastcall SetMasterFields(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetIndexFieldNames();
	void __fastcall SetIndexFieldNames(const System::UnicodeString Value);
	void __fastcall Reactivate();
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	
protected:
	virtual bool __fastcall GetActive();
	DYNAMIC void __fastcall GetChildren(System::Classes::TGetChildProc Proc, System::Classes::TComponent* Root);
	Data::Db::TDataSet* __fastcall GetSubDataSet();
	
public:
	__fastcall virtual TCustomBindSourceDBX(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindSourceDBX();
	__property TSubSQLDataSet* SubSQLDataSet = {read=FSQLDataSet};
	__property Data::Bind::Dbscope::TSubDataSource* SubDataSource = {read=GetSubDataSource};
	__property TSubClientDataSet* SubClientDataSet = {read=FClientDataSet};
	__property TSubDataSetProvider* SubProvider = {read=FProvider};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property System::UnicodeString CommandText = {read=GetCommandText, write=SetCommandText};
	__property Data::Db::TSQLCommandType CommandType = {read=GetCommandType, write=SetCommandType, nodefault};
	__property System::UnicodeString DbxCommandType = {read=GetDbxCommandType, write=SetDbxCommandType};
	__property int MaxBlobSize = {read=GetMaxBlobSize, write=SetMaxBlobSize, nodefault};
	__property bool ParamCheck = {read=GetParamCheck, write=SetParamCheck, nodefault};
	__property Data::Db::TParams* Params = {read=GetParams, write=SetParams};
	__property System::UnicodeString SortFieldNames = {read=GetSortFieldNames, write=SetSortFieldNames};
	__property Data::Sqlexpr::TSQLConnection* SQLConnection = {read=GetSqlConnection, write=SetSqlConnection};
	__property bool AutoApply = {read=FAutoApply, write=FAutoApply, default=1};
	__property TCustomBindSourceDBX* MasterSource = {read=GetMasterSource, write=SetMasterDataSource};
	__property System::UnicodeString MasterFields = {read=GetMasterFields, write=SetMasterFields};
	__property System::UnicodeString IndexFieldNames = {read=GetIndexFieldNames, write=SetIndexFieldNames};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
private:
	void *__ISubDataSet;	// Data::Db::ISubDataSet 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D5608EB1-DE94-4B00-9E62-9F3FE0937D98}
	operator Data::Db::_di_ISubDataSet()
	{
		Data::Db::_di_ISubDataSet intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Db::ISubDataSet*(void) { return (Data::Db::ISubDataSet*)&__ISubDataSet; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindSourceDBX : public TCustomBindSourceDBX
{
	typedef TCustomBindSourceDBX inherited;
	
__published:
	__property SubSQLDataSet;
	__property SubDataSource;
	__property SubClientDataSet;
	__property SubProvider;
	__property Active = {stored=false};
	__property CommandText = {stored=false, default=0};
	__property CommandType = {stored=false};
	__property DbxCommandType = {stored=false, default=0};
	__property MaxBlobSize = {stored=false};
	__property ParamCheck = {stored=false};
	__property Params = {stored=false};
	__property SortFieldNames = {stored=false, default=0};
	__property SQLConnection;
	__property AutoApply = {default=1};
	__property ApplyMaxErrors = {default=-1};
	__property ScopeMappings;
	__property MasterFields = {default=0};
	__property MasterSource;
	__property IndexFieldNames = {default=0};
	__property SchemaName = {default=0};
public:
	/* TCustomBindSourceDBX.Create */ inline __fastcall virtual TBindSourceDBX(System::Classes::TComponent* AOwner) : TCustomBindSourceDBX(AOwner) { }
	/* TCustomBindSourceDBX.Destroy */ inline __fastcall virtual ~TBindSourceDBX() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxscope */
}	/* namespace Bind */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND_DBXSCOPE)
using namespace Data::Bind::Dbxscope;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND)
using namespace Data::Bind;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_Bind_DbxscopeHPP
