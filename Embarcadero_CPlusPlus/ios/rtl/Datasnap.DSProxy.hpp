// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProxy.pas' rev: 34.00 (iOS)

#ifndef Datasnap_DsproxyHPP
#define Datasnap_DsproxyHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXJSONReflect.hpp>
#include <Data.DbxCompressionFilter.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsproxy
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSAdminClient;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDSAdminClient : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	Data::Dbxcommon::TDBXConnection* FDBXConnection;
	bool FInstanceOwner;
	Data::Dbxjsonreflect::TJSONMarshal* FMarshal;
	Data::Dbxjsonreflect::TJSONUnMarshal* FUnMarshal;
	
private:
	Data::Dbxcommon::TDBXCommand* FGetPlatformNameCommand;
	Data::Dbxcommon::TDBXCommand* FClearResourcesCommand;
	Data::Dbxcommon::TDBXCommand* FFindPackagesCommand;
	Data::Dbxcommon::TDBXCommand* FFindClassesCommand;
	Data::Dbxcommon::TDBXCommand* FFindMethodsCommand;
	Data::Dbxcommon::TDBXCommand* FGetServerMethodsCommand;
	Data::Dbxcommon::TDBXCommand* FGetServerMethodParametersCommand;
	Data::Dbxcommon::TDBXCommand* FGetDatabaseConnectionPropertiesCommand;
	Data::Dbxcommon::TDBXCommand* FBroadcastToChannelCommand;
	Data::Dbxcommon::TDBXCommand* FBroadcastObjectToChannelCommand;
	Data::Dbxcommon::TDBXCommand* FNotifyCallbackCommand;
	Data::Dbxcommon::TDBXCommand* FNotifyObjectCommand;
	Data::Dbxcommon::TDBXCommand* FListClassesCommand;
	Data::Dbxcommon::TDBXCommand* FDescribeClassCommand;
	Data::Dbxcommon::TDBXCommand* FListMethodsCommand;
	Data::Dbxcommon::TDBXCommand* FDescribeMethodCommand;
	
public:
	__fastcall TDSAdminClient(Data::Dbxcommon::TDBXConnection* ADBXConnection)/* overload */;
	__fastcall TDSAdminClient(Data::Dbxcommon::TDBXConnection* ADBXConnection, bool AInstanceOwner)/* overload */;
	__fastcall virtual ~TDSAdminClient();
	System::UnicodeString __fastcall GetPlatformName();
	bool __fastcall ClearResources();
	Data::Dbxcommon::TDBXReader* __fastcall FindPackages();
	Data::Dbxcommon::TDBXReader* __fastcall FindClasses(System::UnicodeString PackageName, System::UnicodeString ClassPattern);
	Data::Dbxcommon::TDBXReader* __fastcall FindMethods(System::UnicodeString PackageName, System::UnicodeString ClassPattern, System::UnicodeString MethodPattern);
	Data::Dbxcommon::TDBXReader* __fastcall GetServerMethods();
	Data::Dbxcommon::TDBXReader* __fastcall GetServerMethodParameters();
	Data::Dbxcommon::TDBXReader* __fastcall GetDatabaseConnectionProperties();
	bool __fastcall BroadcastToChannel(System::UnicodeString ChannelName, System::Json::TJSONValue* Msg);
	bool __fastcall BroadcastObjectToChannel(System::UnicodeString ChannelName, System::TObject* Msg);
	bool __fastcall NotifyCallback(System::UnicodeString ClientId, System::UnicodeString CallbackId, System::Json::TJSONValue* Msg, /* out */ System::Json::TJSONValue* &Response)/* overload */;
	bool __fastcall NotifyObject(System::UnicodeString ClientId, System::UnicodeString CallbackId, System::TObject* Msg, /* out */ System::TObject* &Response)/* overload */;
	System::Json::TJSONArray* __fastcall ListClasses();
	System::Json::TJSONObject* __fastcall DescribeClass(System::UnicodeString ClassName);
	System::Json::TJSONArray* __fastcall ListMethods(System::UnicodeString ClassName);
	System::Json::TJSONObject* __fastcall DescribeMethod(System::UnicodeString ServerMethodName);
	bool __fastcall NotifyCallback _DEPRECATED_ATTRIBUTE1("ChannelName is no longer required") (System::UnicodeString ChannelName, System::UnicodeString ClientId, System::UnicodeString CallbackId, System::Json::TJSONValue* Msg, /* out */ System::Json::TJSONValue* &Response)/* overload */;
	bool __fastcall NotifyObject _DEPRECATED_ATTRIBUTE1("ChannelName is no longer required") (System::UnicodeString ChannelName, System::UnicodeString ClientId, System::UnicodeString CallbackId, System::TObject* Msg, /* out */ System::TObject* &Response)/* overload */;
	__property bool InstanceOwner = {read=FInstanceOwner, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsproxy */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROXY)
using namespace Datasnap::Dsproxy;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproxyHPP
