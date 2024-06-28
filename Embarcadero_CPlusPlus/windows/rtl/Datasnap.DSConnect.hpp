// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSConnect.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsconnectHPP
#define Datasnap_DsconnectHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <Datasnap.DBClient.hpp>
#include <Data.DBXCommon.hpp>
#include <Datasnap.Midas.hpp>
#include <Data.SqlExpr.hpp>
#include <Data.DB.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsconnect
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSProviderConnection;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDSProviderConnection : public Datasnap::Dbclient::TCustomRemoteServer
{
	typedef Datasnap::Dbclient::TCustomRemoteServer inherited;
	
private:
	Datasnap::Midas::_di_IAppServer FAppServer;
	System::UnicodeString FServerClassName;
	Data::Sqlexpr::TSQLConnection* FSQLConnection;
	Data::Dbxcommon::TDBXCommand* FApplyUpdatesCommand;
	Data::Dbxcommon::TDBXCommand* FGetRecordsCommand;
	Data::Dbxcommon::TDBXCommand* FDataRequestCommand;
	Data::Dbxcommon::TDBXCommand* FGetProviderNamesCommand;
	Data::Dbxcommon::TDBXCommand* FGetParamsCommand;
	Data::Dbxcommon::TDBXCommand* FRowRequestCommand;
	Data::Dbxcommon::TDBXCommand* FExecuteCommand;
	Data::Dbxcommon::TDBXCommand* FRowRequest;
	void __fastcall SetSQLConnection(Data::Sqlexpr::TSQLConnection* const Value);
	void __fastcall SetServerClassName(const System::UnicodeString Value);
	Data::Dbxcommon::TDBXConnection* __fastcall GetDBXConnection();
	void __fastcall FreeCommands();
	void __fastcall ConnectChange(System::TObject* Sender, bool Connecting);
	
protected:
	virtual void __fastcall DoConnect();
	virtual void __fastcall DoDisconnect();
	virtual bool __fastcall GetConnected();
	virtual void __fastcall SetConnected(bool Value);
	Data::Dbxcommon::TDBXCommand* __fastcall GetCommandObject(const System::UnicodeString ProcedureName);
	__property Data::Dbxcommon::TDBXConnection* Connection = {read=GetDBXConnection};
	HRESULT __safecall AS_ApplyUpdates(const System::WideString ProviderName, System::OleVariant Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData, System::OleVariant &__AS_ApplyUpdates_result);
	HRESULT __safecall AS_GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData, System::OleVariant &__AS_GetRecords_result);
	HRESULT __safecall AS_DataRequest(const System::WideString ProviderName, System::OleVariant Data, System::OleVariant &__AS_DataRequest_result);
	HRESULT __safecall AS_GetProviderNames(System::OleVariant &__AS_GetProviderNames_result);
	HRESULT __safecall AS_GetParams(const System::WideString ProviderName, System::OleVariant &OwnerData, System::OleVariant &__AS_GetParams_result);
	HRESULT __safecall AS_RowRequest(const System::WideString ProviderName, System::OleVariant Row, int RequestType, System::OleVariant &OwnerData, System::OleVariant &__AS_RowRequest_result);
	HRESULT __safecall AS_Execute(const System::WideString ProviderName, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	HRESULT __stdcall InterfaceSupportsErrorInfo(const GUID &iid);
	
public:
	__fastcall virtual TDSProviderConnection(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSProviderConnection();
	__property Datasnap::Midas::_di_IAppServer AppServer = {read=FAppServer};
	virtual Datasnap::Midas::_di_IAppServer __fastcall GetServer();
	virtual HRESULT __fastcall SafeCallException(System::TObject* ExceptObject, void * ExceptAddr);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
__published:
	__property System::UnicodeString ServerClassName = {read=FServerClassName, write=SetServerClassName};
	__property Connected = {default=0};
	__property Data::Sqlexpr::TSQLConnection* SQLConnection = {read=FSQLConnection, write=SetSQLConnection};
private:
	void *__ISupportErrorInfo;	// ISupportErrorInfo 
	void *__IAppServer;	// Datasnap::Midas::IAppServer 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DF0B3D60-548F-101B-8E65-08002B2BD119}
	operator _di_ISupportErrorInfo()
	{
		_di_ISupportErrorInfo intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ISupportErrorInfo*(void) { return (ISupportErrorInfo*)&__ISupportErrorInfo; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1AEFCC20-7A24-11D2-98B0-C69BEB4B5B6D}
	operator Datasnap::Midas::_di_IAppServer()
	{
		Datasnap::Midas::_di_IAppServer intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Datasnap::Midas::IAppServer*(void) { return (Datasnap::Midas::IAppServer*)&__IAppServer; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsconnect */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSCONNECT)
using namespace Datasnap::Dsconnect;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsconnectHPP
