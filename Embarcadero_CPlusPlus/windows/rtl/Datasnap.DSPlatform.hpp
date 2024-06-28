// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSPlatform.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsplatformHPP
#define Datasnap_DsplatformHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Datasnap.DSCommonTable.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXJSON.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsplatform
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXServerComponent;
class DELPHICLASS TDSPlatform;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDBXServerComponent : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	bool HasTunnelSessionEvent;
	bool __fastcall ConsumeAllClientChannel(const System::UnicodeString ChannelName, const System::UnicodeString ChannelId, const System::UnicodeString CallbackId, const System::UnicodeString SecurityToken, System::Classes::TStringList* ChannelNames, Data::Dbxjson::TDBXCallback* ChannelCallback, unsigned Timeout);
	System::Json::TJSONValue* __fastcall ConsumeOneClientChannel(const System::UnicodeString ChannelName, const System::UnicodeString ClientManagerId, const System::UnicodeString CallbackId, const System::UnicodeString SecurityToken, System::Classes::TStringList* ChannelNames, System::Json::TJSONValue* ResponseData, unsigned Timeout);
	
protected:
	virtual System::UnicodeString __fastcall GetDSServerName() = 0 ;
	
public:
	__fastcall virtual TDBXServerComponent(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual TDBXServerComponent()/* overload */;
	System::Json::TJSONValue* __fastcall ConsumeClientChannel(const System::UnicodeString ChannelName, const System::UnicodeString ClientManagerId, const System::UnicodeString CallbackId, const System::UnicodeString ChannelNames, const System::UnicodeString SecurityToken, System::Json::TJSONValue* ResponseData);
	System::Json::TJSONValue* __fastcall ConsumeClientChannelTimeout(const System::UnicodeString ChannelName, const System::UnicodeString ClientManagerId, const System::UnicodeString CallbackId, const System::UnicodeString ChannelNames, const System::UnicodeString SecurityToken, int Timeout, System::Json::TJSONValue* ResponseData);
	bool __fastcall ConnectClientChannel(const System::UnicodeString ChannelName, const System::UnicodeString ChannelId, const System::UnicodeString CallbackId, const System::UnicodeString ChannelNames, const System::UnicodeString SecurityToken, Data::Dbxjson::TDBXCallback* ChannelCallback);
	bool __fastcall ConnectClientChannelTimeout(const System::UnicodeString ChannelName, const System::UnicodeString ChannelId, const System::UnicodeString CallbackId, const System::UnicodeString ChannelNames, const System::UnicodeString SecurityToken, Data::Dbxjson::TDBXCallback* ChannelCallback, int Timeout);
	bool __fastcall CloseClientChannel(const System::UnicodeString ChannelId, const System::UnicodeString SecurityToken);
	bool __fastcall RegisterClientCallback(const System::UnicodeString ChannelId, const System::UnicodeString CallbackId, const System::UnicodeString ChannelNames, const System::UnicodeString SecurityToken, Data::Dbxjson::TDBXCallback* ChannelCallback);
	bool __fastcall RegisterClientCallbackServer(const System::UnicodeString ChannelId, const System::UnicodeString CallbackId, const System::UnicodeString ChannelNames, const System::UnicodeString SecurityToken);
	bool __fastcall UnregisterClientCallback(const System::UnicodeString ChannelId, const System::UnicodeString CallbackId, const System::UnicodeString SecurityToken);
	bool __fastcall BroadcastToChannel(const System::UnicodeString ChannelName, System::Json::TJSONValue* const Msg);
	bool __fastcall BroadcastObjectToChannel(const System::UnicodeString ChannelName, System::TObject* const Msg);
	bool __fastcall NotifyCallback(const System::UnicodeString ClientId, const System::UnicodeString CallbackId, System::Json::TJSONValue* const Msg, /* out */ System::Json::TJSONValue* &Response);
	bool __fastcall NotifyObject(const System::UnicodeString ClientId, const System::UnicodeString CallbackId, System::TObject* const Msg, /* out */ System::TObject* &Response);
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDBXServerComponent() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSPlatform : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static System::UnicodeString __fastcall DefaultPackageName();
	static System::UnicodeString __fastcall DataSnapAdminClassName();
	static System::UnicodeString __fastcall DataSnapAdminUnitName();
	static System::UnicodeString __fastcall MetadataClassName();
	static System::UnicodeString __fastcall MetadataUnitName();
	static System::UnicodeString __fastcall PlatformName();
	static Data::Dbxcommon::TDBXConnection* __fastcall GetDatabaseConnection(Data::Dbxcommon::TDBXContext* DBXContext, System::UnicodeString ServerConnectionName, Data::Dbxcommon::TDBXProperties* ConProperties);
	static void __fastcall GetConnectionProperties(Datasnap::Dscommontable::TDSConnectionEntity* Connections);
public:
	/* TObject.Create */ inline __fastcall TDSPlatform() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSPlatform() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsplatform */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPLATFORM)
using namespace Datasnap::Dsplatform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsplatformHPP
