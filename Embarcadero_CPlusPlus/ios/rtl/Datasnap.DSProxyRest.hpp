// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProxyRest.pas' rev: 34.00 (iOS)

#ifndef Datasnap_DsproxyrestHPP
#define Datasnap_DsproxyrestHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <System.JSON.hpp>
#include <Data.DBXJSONReflect.hpp>
#include <Datasnap.DSClientRest.hpp>
#include <Datasnap.DSCommonProxy.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsproxyrest
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSRestClient;
class DELPHICLASS TDSRestProxyMetaDataLoader;
class DELPHICLASS TDSAdminRestClient;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDSRestClient : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	bool FInstanceOwner;
	Datasnap::Dsclientrest::TDSCustomRestConnection* FConnection;
	
public:
	__fastcall TDSRestClient(Datasnap::Dsclientrest::TDSCustomRestConnection* AConnection)/* overload */;
	__fastcall TDSRestClient(Datasnap::Dsclientrest::TDSCustomRestConnection* AConnection, bool AInstanceOwner)/* overload */;
	__property bool InstanceOwner = {read=FInstanceOwner, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSRestClient() { }
	
};


class PASCALIMPLEMENTATION TDSRestProxyMetaDataLoader : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Datasnap::Dsclientrest::TDSCustomRestConnection* FConnection;
	void __fastcall Load(Datasnap::Dscommonproxy::TDSProxyMetadata* MetaData);
	void __fastcall LoadFromConnection(Datasnap::Dsclientrest::TDSCustomRestConnection* AConnection, Datasnap::Dscommonproxy::TDSProxyMetadata* AMetaData);
	
public:
	__fastcall TDSRestProxyMetaDataLoader(Datasnap::Dsclientrest::TDSCustomRestConnection* AConnection);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSRestProxyMetaDataLoader() { }
	
private:
	void *__IDSProxyMetaDataLoader;	// Datasnap::Dscommonproxy::IDSProxyMetaDataLoader 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {768E0AB8-3FEB-4BBF-8AAB-9ACE5A8D2CBF}
	operator Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader()
	{
		Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Datasnap::Dscommonproxy::IDSProxyMetaDataLoader*(void) { return (Datasnap::Dscommonproxy::IDSProxyMetaDataLoader*)&__IDSProxyMetaDataLoader; }
	#endif
	
};


class PASCALIMPLEMENTATION TDSAdminRestClient : public TDSRestClient
{
	typedef TDSRestClient inherited;
	
protected:
	Datasnap::Dsclientrest::TDSRestCommand* FDConnection;
	Data::Dbxjsonreflect::TJSONMarshal* FMarshal;
	Data::Dbxjsonreflect::TJSONUnMarshal* FUnMarshal;
	
private:
	Datasnap::Dsclientrest::TDSRestCommand* FGetPlatformNameCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FClearResourcesCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FFindPackagesCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FFindClassesCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FFindMethodsCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FListClassesCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FDescribeClassCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FListMethodsCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FDescribeMethodCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FGetServerMethodsCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FGetServerMethodParametersCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FGetDatabaseConnectionPropertiesCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FConsumeClientChannelCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FConsumeClientChannelTimeoutCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FCloseClientChannelCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FRegisterClientCallbackServerCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FUnregisterClientCallbackCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FBroadcastToChannelCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FBroadcastObjectToChannelCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FNotifyCallbackCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FNotifyObjectCommand;
	Datasnap::Dsclientrest::TDSRestCommand* FClearSessionCommand;
	
public:
	__fastcall TDSAdminRestClient(Datasnap::Dsclientrest::TDSCustomRestConnection* AConnection)/* overload */;
	__fastcall TDSAdminRestClient(Datasnap::Dsclientrest::TDSCustomRestConnection* AConnection, bool AInstanceOwner)/* overload */;
	__fastcall virtual ~TDSAdminRestClient();
	System::UnicodeString __fastcall GetPlatformName();
	bool __fastcall ClearResources();
	Data::Dbxcommon::TDBXReader* __fastcall FindPackages();
	Data::Dbxcommon::TDBXReader* __fastcall FindClasses(System::UnicodeString PackageName, System::UnicodeString ClassPattern);
	Data::Dbxcommon::TDBXReader* __fastcall FindMethods(System::UnicodeString PackageName, System::UnicodeString ClassPattern, System::UnicodeString MethodPattern);
	System::Json::TJSONArray* __fastcall ListClasses();
	System::Json::TJSONObject* __fastcall DescribeClass(System::UnicodeString ClassName);
	System::Json::TJSONArray* __fastcall ListMethods(System::UnicodeString ClassName);
	System::Json::TJSONObject* __fastcall DescribeMethod(System::UnicodeString ServerMethodName);
	Data::Dbxcommon::TDBXReader* __fastcall GetServerMethods();
	Data::Dbxcommon::TDBXReader* __fastcall GetServerMethodParameters();
	Data::Dbxcommon::TDBXReader* __fastcall GetDatabaseConnectionProperties();
	System::Json::TJSONValue* __fastcall ConsumeClientChannel(System::UnicodeString ChannelName, System::UnicodeString ClientManagerId, System::UnicodeString CallbackId, System::UnicodeString ChannelNames, System::Json::TJSONValue* ResponseData);
	System::Json::TJSONValue* __fastcall ConsumeClientChannelTimeout(System::UnicodeString ChannelName, System::UnicodeString ClientManagerId, System::UnicodeString CallbackId, System::UnicodeString ChannelNames, int Timeout, System::Json::TJSONValue* ResponseData);
	bool __fastcall CloseClientChannel(System::UnicodeString ChannelId);
	bool __fastcall RegisterClientCallbackServer(System::UnicodeString ChannelId, System::UnicodeString CallbackId, System::UnicodeString ChannelNames);
	bool __fastcall UnregisterClientCallback(System::UnicodeString ChannelId, System::UnicodeString CallbackId);
	bool __fastcall BroadcastToChannel(System::UnicodeString ChannelName, System::Json::TJSONValue* Msg);
	bool __fastcall BroadcastObjectToChannel(System::UnicodeString ChannelName, System::TObject* Msg);
	bool __fastcall NotifyCallback(System::UnicodeString ClientId, System::UnicodeString CallbackId, System::Json::TJSONValue* Msg, /* out */ System::Json::TJSONValue* &Response);
	bool __fastcall NotifyObject(System::UnicodeString ClientId, System::UnicodeString CallbackId, System::TObject* Msg, /* out */ System::TObject* &Response);
	void __fastcall ClearSession();
};


typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 1> Datasnap_Dsproxyrest__4;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 1> Datasnap_Dsproxyrest__5;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 1> Datasnap_Dsproxyrest__6;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 3> Datasnap_Dsproxyrest__7;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 4> Datasnap_Dsproxyrest__8;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 1> Datasnap_Dsproxyrest__9;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 2> Datasnap_Dsproxyrest__01;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 2> Datasnap_Dsproxyrest__11;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 2> Datasnap_Dsproxyrest__21;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 1> Datasnap_Dsproxyrest__31;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 1> Datasnap_Dsproxyrest__41;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 1> Datasnap_Dsproxyrest__51;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 1> Datasnap_Dsproxyrest__61;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 2> Datasnap_Dsproxyrest__71;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 3> Datasnap_Dsproxyrest__81;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 3> Datasnap_Dsproxyrest__91;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 3> Datasnap_Dsproxyrest__02;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 5> Datasnap_Dsproxyrest__12;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 5> Datasnap_Dsproxyrest__22;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 7> Datasnap_Dsproxyrest__32;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 8> Datasnap_Dsproxyrest__42;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 3> Datasnap_Dsproxyrest__52;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 5> Datasnap_Dsproxyrest__62;

typedef System::StaticArray<Datasnap::Dsclientrest::TDSRestParameterMetaData, 4> Datasnap_Dsproxyrest__72;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString GDSProxyRestSecurityToken;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__4 DSAdmin_GetPlatformName;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__5 DSAdmin_ClearResources;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__6 DSAdmin_FindPackages;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__7 DSAdmin_FindClasses;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__8 DSAdmin_FindMethods;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__9 DSAdmin_ListClasses;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__01 DSAdmin_DescribeClass;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__11 DSAdmin_ListMethods;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__21 DSAdmin_DescribeMethod;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__31 DSAdmin_GetServerMethods;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__41 DSAdmin_GetServerMethodParameters;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__51 DSAdmin_GetDatabaseConnectionProperties;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__61 DSAdmin_GetDSServerName;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__71 DSAdmin_CloseClientChannel;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__81 DSAdmin_UnregisterClientCallback;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__91 DSAdmin_BroadcastToChannel;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__02 DSAdmin_BroadcastObjectToChannel;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__12 DSAdmin_NotifyCallback;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__22 DSAdmin_NotifyObject;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__32 DSAdmin_ConsumeClientChannelSecure;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__42 DSAdmin_ConsumeClientChannelTimeoutSecure;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__52 DSAdmin_CloseClientChannelSecure;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__62 DSAdmin_RegisterClientCallbackServerSecure;
extern DELPHI_PACKAGE Datasnap_Dsproxyrest__72 DSAdmin_UnregisterClientCallbackSecure;
}	/* namespace Dsproxyrest */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROXYREST)
using namespace Datasnap::Dsproxyrest;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproxyrestHPP
