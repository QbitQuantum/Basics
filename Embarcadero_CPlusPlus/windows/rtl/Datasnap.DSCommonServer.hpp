// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSCommonServer.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DscommonserverHPP
#define Datasnap_DscommonserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <System.Classes.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMessageHandlerCommon.hpp>
#include <Data.DBXMessageHandlerServer.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.DBXSqlScanner.hpp>
#include <Data.DBXTransport.hpp>
#include <Datasnap.DSCommonProxy.hpp>
#include <Datasnap.DSCommonTable.hpp>
#include <Datasnap.DSPlatform.hpp>
#include <Datasnap.DSReflect.hpp>
#include <System.SysUtils.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dscommonserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSClassInfo;
class DELPHICLASS TDSConfiguration;
class DELPHICLASS TDSCustomAdmin;
class DELPHICLASS TDSMethodInfo;
class DELPHICLASS DSAdmin;
class DELPHICLASS TDSCustomServer;
class DELPHICLASS TDSDefaultCommandHandler;
class DELPHICLASS TDSDefaultDatabaseConnectionHandler;
class DELPHICLASS TDSEventObject;
class DELPHICLASS TDSErrorEventObject;
class DELPHICLASS TDSDestroyInstanceEventObject;
class DELPHICLASS TDSCreateInstanceEventObject;
class DELPHICLASS TDSConnectEventObject;
class DELPHICLASS TDSInstanceProvider;
class DELPHICLASS TDSHashtableInstanceProvider;
class DELPHICLASS DSMetadata;
class DELPHICLASS TDSServerMethodEventObject;
class DELPHICLASS TDSServerMethodUserEventObject;
class DELPHICLASS TDSPrepareEventObject;
class DELPHICLASS TDSAuthorizeEventObject;
class DELPHICLASS TDSAuthenticateEventObject;
class DELPHICLASS TDSServerCommand;
class DELPHICLASS TDSServerCommandHandler;
class DELPHICLASS TDSServerComponent;
class DELPHICLASS TDSCustomServerClass;
class DELPHICLASS TDSServerConnectionFactory;
class DELPHICLASS TDSServerConnection;
class DELPHICLASS TDSServerConnectionHandler;
class DELPHICLASS TDSServerHelp;
class DELPHICLASS TDSServerMethod;
class DELPHICLASS TDSServerMethodCommandHandler;
class DELPHICLASS TDSServerMethodProvider;
class DELPHICLASS TDSServerTransport;
class DELPHICLASS TDSSystemProperties;
class DELPHICLASS TDSVoidConnectionHandler;
class DELPHICLASS TInstanceProviderItem;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSClassInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual ~TDSClassInfo();
	void __fastcall Close();
	
private:
	System::UnicodeString FPackageName;
	System::UnicodeString FClassName;
	System::UnicodeString FUnitName;
	System::UnicodeString FRoleName;
	System::UnicodeString FLifeCycle;
	Datasnap::Dsreflect::TDSClass* FDsClass;
	bool FAdminClass;
	TDSCustomServerClass* FServerClass;
	
public:
	__property System::UnicodeString DSClassName = {read=FClassName, write=FClassName};
	__property Datasnap::Dsreflect::TDSClass* DSClass = {read=FDsClass, write=FDsClass};
	__property System::UnicodeString LifeCycle = {read=FLifeCycle, write=FLifeCycle};
	__property System::UnicodeString PackageName = {read=FPackageName, write=FPackageName};
	__property System::UnicodeString RoleName = {read=FRoleName, write=FRoleName};
	__property bool CustomAdminClass = {read=FAdminClass, write=FAdminClass, nodefault};
	__property TDSCustomServerClass* ServerClass = {read=FServerClass, write=FServerClass};
	__property System::UnicodeString DSUnitName = {read=FUnitName, write=FUnitName};
public:
	/* TObject.Create */ inline __fastcall TDSClassInfo() : System::TObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSConfiguration : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TDSConfiguration* __fastcall CopyConfiguration();
	
protected:
	Data::Dbxcommontable::TDBXTable* __fastcall GetClassTable();
	void __fastcall SetClassTable(Data::Dbxcommontable::TDBXTable* const Classes);
	Data::Dbxcommontable::TDBXTable* __fastcall GetMethodTable();
	void __fastcall SetMethodTable(Data::Dbxcommontable::TDBXTable* const Methods);
	
private:
	void __fastcall CreateClassTable();
	void __fastcall CreateMethodTable();
	Data::Dbxcommontable::TDBXTable* FClassTable;
	Data::Dbxcommontable::TDBXTable* FMethodTable;
	
public:
	__property Data::Dbxcommontable::TDBXTable* ClassTable = {read=GetClassTable, write=SetClassTable};
	__property Data::Dbxcommontable::TDBXTable* MethodTable = {read=GetMethodTable, write=SetMethodTable};
public:
	/* TObject.Create */ inline __fastcall TDSConfiguration() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSConfiguration() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSCustomAdmin : public Datasnap::Dsplatform::TDBXServerComponent
{
	typedef Datasnap::Dsplatform::TDBXServerComponent inherited;
	
public:
	__fastcall virtual TDSCustomAdmin()/* overload */;
	__fastcall virtual TDSCustomAdmin(System::Classes::TComponent* AOwner)/* overload */;
	virtual System::UnicodeString __fastcall GetDSServerName();
	
protected:
	Data::Dbxcommon::TDBXContext* __fastcall GetDBXContext();
	void __fastcall SetServerConnection(TDSServerConnectionHandler* const Con);
	TDSCustomServer* FServer;
	TDSServerConnectionHandler* FServerCon;
	
public:
	__property Data::Dbxcommon::TDBXContext* DBXContext = {read=GetDBXContext};
	__property TDSServerConnectionHandler* ServerConnection = {write=SetServerConnection};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSCustomAdmin() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSMethodInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual TDSMethodInfo();
	__fastcall virtual ~TDSMethodInfo();
	
protected:
	void __fastcall SetMethodAlias(const System::UnicodeString MethodAlias);
	Datasnap::Dsreflect::TDSMethod* __fastcall GetDSMethod();
	
private:
	System::UnicodeString FMethodAlias;
	TDSClassInfo* FClassInfo;
	Datasnap::Dsreflect::TDSMethod* FDsMethod;
	System::UnicodeString FRoleName;
	System::UnicodeString FMethodName;
	System::UnicodeString FSearchName;
	System::TObject* FAuthRole;
	void __fastcall SetAuthRole(System::TObject* ARoleAuth);
	
public:
	__property TDSClassInfo* DSClassInfo = {read=FClassInfo, write=FClassInfo};
	__property System::UnicodeString MethodAlias = {read=FMethodAlias, write=SetMethodAlias};
	__property System::UnicodeString SearchName = {read=FSearchName};
	__property System::UnicodeString DSMethodName = {read=FMethodName, write=FMethodName};
	__property System::UnicodeString RoleName = {read=FRoleName, write=FRoleName};
	__property Datasnap::Dsreflect::TDSMethod* DSMethod = {read=GetDSMethod, write=FDsMethod};
	__property System::TObject* AuthRole = {read=FAuthRole, write=SetAuthRole};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION DECLSPEC_DRTTI DSAdmin : public TDSCustomAdmin
{
	typedef TDSCustomAdmin inherited;
	
public:
	__fastcall virtual DSAdmin(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~DSAdmin();
	System::UnicodeString __fastcall GetPlatformName();
	bool __fastcall ClearResources();
	Data::Dbxcommon::TDBXReader* __fastcall FindPackages();
	Data::Dbxcommon::TDBXReader* __fastcall FindClasses(const System::UnicodeString PackageName, const System::UnicodeString ClassPattern);
	Data::Dbxcommon::TDBXReader* __fastcall FindMethods(const System::UnicodeString PackageName, const System::UnicodeString ClassPattern, const System::UnicodeString MethodPattern);
	void __fastcall CreateServerClasses(Data::Dbxcommon::TDBXReader* const ClassReader);
	void __fastcall DropServerClasses(Data::Dbxcommon::TDBXReader* const ClassReader);
	void __fastcall CreateServerMethods(Data::Dbxcommon::TDBXReader* const MethodReader);
	void __fastcall DropServerMethods(Data::Dbxcommon::TDBXReader* const MethodReader);
	Data::Dbxcommon::TDBXReader* __fastcall GetServerClasses();
	System::Json::TJSONArray* __fastcall ListClasses();
	System::Json::TJSONObject* __fastcall DescribeClass(const System::UnicodeString ClassName);
	System::Json::TJSONArray* __fastcall ListMethods(const System::UnicodeString ClassName);
	System::Json::TJSONObject* __fastcall DescribeMethod(const System::UnicodeString ServerMethodName);
	Data::Dbxcommon::TDBXReader* __fastcall GetServerMethods();
	Data::Dbxcommon::TDBXReader* __fastcall GetServerMethodParameters();
	Data::Dbxcommon::TDBXConnection* __fastcall GetConnection(const System::UnicodeString NewConName);
	Data::Dbxcommon::TDBXReader* __fastcall GetDatabaseConnectionProperties();
	
private:
	Data::Dbxcommon::TDBXConnection* FCon;
	System::UnicodeString FConName;
public:
	/* TDSCustomAdmin.Create */ inline __fastcall virtual DSAdmin()/* overload */ : TDSCustomAdmin() { }
	
};


class PASCALIMPLEMENTATION TDSCustomServer : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	__fastcall virtual TDSCustomServer(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSCustomServer();
	void __fastcall GetServerClassList(Data::Dbxplatform::TDBXArrayList* const List);
	void __fastcall RemoveServerComponent(TDSServerComponent* const AComponent);
	void __fastcall AddServerComponent(TDSServerComponent* const AComponent);
	virtual void __fastcall Stop();
	virtual void __fastcall Start();
	void __fastcall GetServerClasses(TDSServerConnectionHandler* const ServerCon, Datasnap::Dscommontable::TDSClassEntity* const Classes)/* overload */;
	void __fastcall GetServerClasses(System::Json::TJSONArray* const Container)/* overload */;
	void __fastcall GetServerClass(const System::UnicodeString ClassName, System::Json::TJSONObject* const Container);
	void __fastcall GetServerMethods(const System::UnicodeString ClassName, System::Json::TJSONArray* const Container)/* overload */;
	void __fastcall GetServerMethod(const System::UnicodeString ServerMethodName, System::Json::TJSONObject* const Container);
	void __fastcall CreateServerClasses(Datasnap::Dscommontable::TDSClassEntity* const Classes);
	void __fastcall DropServerClasses(Datasnap::Dscommontable::TDSClassEntity* const Classes);
	void __fastcall GetServerMethods(TDSServerConnectionHandler* const ServerCon, Datasnap::Dscommontable::TDSMethodEntity* const Methods)/* overload */;
	void __fastcall GetServerMethodParameters(TDSServerConnectionHandler* const ServerCon, Datasnap::Dscommonproxy::TDSMethodParametersEntity* const Parameters);
	void __fastcall CreateServerMethods(Datasnap::Dscommontable::TDSMethodEntity* const Methods);
	void __fastcall DropServerMethods(Datasnap::Dscommontable::TDSMethodEntity* const Methods);
	virtual Data::Dbxcommon::TDBXConnection* __fastcall GetServerConnection(Data::Dbxcommon::TDBXProperties* const Properties) = 0 ;
	
protected:
	static TDSCustomServer* __fastcall FindCustomServer(const System::UnicodeString Name);
	Data::Dbxcommontable::TDBXTable* __fastcall GetClassTable();
	void __fastcall SetClassTable(Data::Dbxcommontable::TDBXTable* const Classes);
	Data::Dbxcommontable::TDBXTable* __fastcall GetMethodTable();
	void __fastcall SetMethodTable(Data::Dbxcommontable::TDBXTable* const Methods);
	virtual void __fastcall Connecting(TDSConnectEventObject* const ConnectEventObject) = 0 ;
	virtual void __fastcall Disconnecting(TDSConnectEventObject* const ConnectEventObject) = 0 ;
	virtual void __fastcall Preparing(TDSPrepareEventObject* const PrepareEventObject) = 0 ;
	virtual void __fastcall Error(TDSErrorEventObject* const ErrorEventObject) = 0 ;
	
private:
	void __fastcall StartTransports();
	void __fastcall StopTransports();
	
protected:
	Data::Dbxcommon::TDBXContext* FDbxContext;
	virtual void __fastcall TransportStopping(TDSServerTransport* const Sender);
	
private:
	bool FStarted;
	TDSConfiguration* FConfig;
	TDSServerMethodProvider* FServerMethodProvider;
	Data::Dbxplatform::TDBXArrayList* FComponentList;
	bool FHideDSAdmin;
	
public:
	__property bool Started = {read=FStarted, nodefault};
	__property Data::Dbxcommontable::TDBXTable* ClassTable = {read=GetClassTable, write=SetClassTable};
	__property Data::Dbxcommontable::TDBXTable* MethodTable = {read=GetMethodTable, write=SetMethodTable};
	__property TDSServerMethodProvider* ServerMethodProvider = {read=FServerMethodProvider};
	__property bool HideDSAdmin = {read=FHideDSAdmin, write=FHideDSAdmin, nodefault};
	__property Data::Dbxcommon::TDBXContext* DbxContext = {read=FDbxContext};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSDefaultCommandHandler : public Data::Dbxmessagehandlercommon::TDBXCommandHandler
{
	typedef Data::Dbxmessagehandlercommon::TDBXCommandHandler inherited;
	
public:
	__fastcall TDSDefaultCommandHandler(Data::Dbxcommon::TDBXContext* const ADbxContext, Data::Dbxmessagehandlercommon::TDBXCommandHandler* const ANextHandler);
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const Message);
	__fastcall virtual ~TDSDefaultCommandHandler();
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
	
private:
	TDSServerConnectionHandler* FServerCon;
	TDSServerMethod* FServerMethod;
	Data::Dbxcommontable::TDBXActiveTableReaderList* FActiveStreamerRowList;
	Data::Dbxmessagehandlercommon::TDBXCommandHandler* FNextHandler;
	
public:
	__property TDSServerConnectionHandler* ServerCon = {write=FServerCon};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSDefaultDatabaseConnectionHandler : public Data::Dbxmessagehandlercommon::TDBXConnectionHandler
{
	typedef Data::Dbxmessagehandlercommon::TDBXConnectionHandler inherited;
	
public:
	__fastcall TDSDefaultDatabaseConnectionHandler(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSServerConnectionHandler* const Con, Data::Dbxmessagehandlercommon::TDBXConnectionHandler* const ANextHandler);
	virtual void __fastcall DbxOpen(Data::Dbxmessagehandlercommon::TDBXOpenMessage* const Message);
	virtual bool __fastcall DbxBeforeRequest();
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const ErrorMessage);
	virtual Data::Dbxmessagehandlercommon::TDBXCommandHandler* __fastcall AcquireCommandHandler(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message);
	virtual void __fastcall DbxConnect(Data::Dbxmessagehandlercommon::TDBXConnectMessage* const Message);
	virtual void __fastcall DbxDisconnect(Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* const Message);
	virtual void __fastcall DbxTxBegin(Data::Dbxmessagehandlercommon::TDBXTxBeginMessage* const Message);
	virtual void __fastcall DbxTxEnd(Data::Dbxmessagehandlercommon::TDBXTxEndMessage* const Message);
	virtual void __fastcall DbxVendorProperty(Data::Dbxmessagehandlercommon::TDBXVendorPropertyMessage* const Message);
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
	
protected:
	virtual System::UnicodeString __fastcall GetProductName();
	
private:
	TDSServerConnectionHandler* FServerCon;
	Data::Dbxmessagehandlercommon::TDBXConnectionHandler* FNextHandler;
public:
	/* TDBXCommandHandler.Destroy */ inline __fastcall virtual ~TDSDefaultDatabaseConnectionHandler() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSEventObject : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDSEventObject(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSCustomServer* const AServer, TDSServerTransport* const ATransport, Data::Dbxcommon::TDBXConnection* const ADbxConnection);
	
private:
	Data::Dbxcommon::TDBXContext* FDbxContext;
	TDSServerTransport* FTransport;
	TDSCustomServer* FServer;
	Data::Dbxcommon::TDBXConnection* FDbxConnection;
	TDSServerConnectionHandler* FServerConnectionHandler;
	
public:
	__property Data::Dbxcommon::TDBXContext* DbxContext = {read=FDbxContext};
	__property TDSServerTransport* Transport = {read=FTransport};
	__property TDSCustomServer* Server = {read=FServer};
	__property Data::Dbxcommon::TDBXConnection* DbxConnection = {read=FDbxConnection};
	__property TDSServerConnectionHandler* ServerConnectionHandler = {read=FServerConnectionHandler};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSEventObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSErrorEventObject : public TDSEventObject
{
	typedef TDSEventObject inherited;
	
public:
	__fastcall TDSErrorEventObject(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSCustomServer* const AServer, TDSServerTransport* const ATransport, Data::Dbxcommon::TDBXConnection* const ADbxConnection);
	
private:
	System::Sysutils::Exception* FError;
	
public:
	__property System::Sysutils::Exception* Error = {read=FError, write=FError};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSErrorEventObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSDestroyInstanceEventObject : public TDSEventObject
{
	typedef TDSEventObject inherited;
	
public:
	__fastcall TDSDestroyInstanceEventObject(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSCustomServer* const AServer, TDSServerTransport* const ATransport, Data::Dbxcommon::TDBXConnection* const ADbxConnection);
	
private:
	System::TObject* FServerClassInstance;
	
public:
	__property System::TObject* ServerClassInstance = {read=FServerClassInstance, write=FServerClassInstance};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSDestroyInstanceEventObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCreateInstanceEventObject : public TDSEventObject
{
	typedef TDSEventObject inherited;
	
public:
	__fastcall TDSCreateInstanceEventObject(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSCustomServer* const AServer, TDSServerTransport* const ATransport, Data::Dbxcommon::TDBXConnection* const ADbxConnection);
	
private:
	System::TObject* FServerClassInstance;
	
public:
	__property System::TObject* ServerClassInstance = {read=FServerClassInstance, write=FServerClassInstance};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSCreateInstanceEventObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSConnectEventObject : public TDSEventObject
{
	typedef TDSEventObject inherited;
	
public:
	__fastcall TDSConnectEventObject(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSCustomServer* const AServer, TDSServerTransport* const ATransport, Data::Dbxtransport::TDBXChannelInfo* const AChannelInfo, Data::Dbxcommon::TDBXConnection* const ADbxConnection, Data::Dbxcommon::TDBXProperties* const AConnectProperties);
	
private:
	Data::Dbxcommon::TDBXProperties* FConnectProperties;
	Data::Dbxtransport::TDBXChannelInfo* FChannelInfo;
	
public:
	__property Data::Dbxcommon::TDBXProperties* ConnectProperties = {read=FConnectProperties, write=FConnectProperties};
	__property Data::Dbxtransport::TDBXChannelInfo* ChannelInfo = {read=FChannelInfo};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSConnectEventObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSInstanceProvider : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::TObject* __fastcall GetInstance(TDSServerConnectionHandler* const ServerCon, TDSClassInfo* const ClassInfo) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDSInstanceProvider() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSInstanceProvider() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHashtableInstanceProvider : public TDSInstanceProvider
{
	typedef TDSInstanceProvider inherited;
	
public:
	__fastcall TDSHashtableInstanceProvider(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSCustomServer* const AServer, TDSServerTransport* const ATransport, Data::Dbxcommon::TDBXConnection* const ADbxConnection);
	__fastcall virtual ~TDSHashtableInstanceProvider();
	virtual System::TObject* __fastcall GetInstance(TDSServerConnectionHandler* const ServerCon, TDSClassInfo* const ClassInfo);
	
private:
	Data::Dbxplatform::TDBXObjectStore* FInstanceTable;
	TInstanceProviderItem* FList;
	TDSDestroyInstanceEventObject* FDestroyInstanceEventObject;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION DECLSPEC_DRTTI DSMetadata : public TDSCustomAdmin
{
	typedef TDSCustomAdmin inherited;
	
public:
	__fastcall virtual DSMetadata(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual DSMetadata()/* overload */;
	Data::Dbxcommon::TDBXReader* __fastcall GetProcedures(const System::UnicodeString ProcedureNamePattern, const System::UnicodeString ProcedureType);
	Data::Dbxcommon::TDBXReader* __fastcall GetProcedureParameters(const System::UnicodeString ProcedureNamePattern);
	Data::Dbxcommon::TDBXReader* __fastcall GetDatabase();
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~DSMetadata() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSServerMethodEventObject : public TDSEventObject
{
	typedef TDSEventObject inherited;
	
public:
	__fastcall TDSServerMethodEventObject(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSCustomServer* const AServer, TDSServerTransport* const ATransport, Data::Dbxcommon::TDBXConnection* const ADbxConnection);
	
private:
	System::UnicodeString FMethodAlias;
	TDSCustomServerClass* FServerClass;
	System::TObject* FMethodInstance;
	
public:
	__property TDSCustomServerClass* ServerClass = {read=FServerClass, write=FServerClass};
	__property System::UnicodeString MethodAlias = {read=FMethodAlias};
	__property System::TObject* MethodInstance = {read=FMethodInstance};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSServerMethodEventObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSServerMethodUserEventObject : public TDSServerMethodEventObject
{
	typedef TDSServerMethodEventObject inherited;
	
public:
	__fastcall TDSServerMethodUserEventObject(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSCustomServer* const AServer, TDSServerTransport* const ATransport, Data::Dbxcommon::TDBXConnection* const ADbxConnection);
	__fastcall virtual ~TDSServerMethodUserEventObject();
	
private:
	System::Classes::TStrings* FUserRoles;
	System::Classes::TStrings* FAuthorizedRoles;
	System::Classes::TStrings* FDeniedRoles;
	System::UnicodeString FUserName;
	System::UnicodeString __fastcall GetSessionUserName();
	
public:
	__property System::UnicodeString UserName = {read=GetSessionUserName};
	__property System::Classes::TStrings* UserRoles = {read=FUserRoles};
	__property System::Classes::TStrings* AuthorizedRoles = {read=FAuthorizedRoles};
	__property System::Classes::TStrings* DeniedRoles = {read=FDeniedRoles};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSPrepareEventObject : public TDSServerMethodUserEventObject
{
	typedef TDSServerMethodUserEventObject inherited;
	
public:
	/* TDSServerMethodUserEventObject.Create */ inline __fastcall TDSPrepareEventObject(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSCustomServer* const AServer, TDSServerTransport* const ATransport, Data::Dbxcommon::TDBXConnection* const ADbxConnection) : TDSServerMethodUserEventObject(ADbxContext, AServer, ATransport, ADbxConnection) { }
	/* TDSServerMethodUserEventObject.Destroy */ inline __fastcall virtual ~TDSPrepareEventObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSAuthorizeEventObject : public TDSServerMethodUserEventObject
{
	typedef TDSServerMethodUserEventObject inherited;
	
public:
	/* TDSServerMethodUserEventObject.Create */ inline __fastcall TDSAuthorizeEventObject(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSCustomServer* const AServer, TDSServerTransport* const ATransport, Data::Dbxcommon::TDBXConnection* const ADbxConnection) : TDSServerMethodUserEventObject(ADbxContext, AServer, ATransport, ADbxConnection) { }
	/* TDSServerMethodUserEventObject.Destroy */ inline __fastcall virtual ~TDSAuthorizeEventObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSAuthenticateEventObject : public TDSEventObject
{
	typedef TDSEventObject inherited;
	
public:
	__fastcall TDSAuthenticateEventObject(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSCustomServer* const AServer, TDSServerTransport* const ATransport, Data::Dbxcommon::TDBXConnection* const ADbxConnection);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSAuthenticateEventObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSServerCommand : public Data::Dbxcommon::TDBXCommand
{
	typedef Data::Dbxcommon::TDBXCommand inherited;
	
public:
	__fastcall TDSServerCommand(Data::Dbxcommon::TDBXContext* const Context, TDSServerConnection* const AServerCon, TDSServerConnectionHandler* const AConHandler);
	
protected:
	virtual void __fastcall DerivedOpen();
	virtual Data::Dbxcommon::TDBXRow* __fastcall CreateParameterRow();
	virtual void __fastcall DerivedPrepare();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedExecuteQuery();
	virtual void __fastcall DerivedExecuteUpdate();
	virtual void __fastcall DerivedClose();
	virtual Data::Dbxcommon::TDBXReader* __fastcall DerivedGetNextReader();
	virtual __int64 __fastcall GetRowsAffected();
	virtual void __fastcall SetRowSetSize(const __int64 RowSetSize);
	virtual void __fastcall SetMaxBlobSize(const __int64 MaxBlobSize);
	
private:
	void __fastcall Execute();
	TDSServerConnectionHandler* FConHandler;
	TDSServerConnection* FServerCon;
	__int64 FRowsAffected;
	Data::Dbxcommon::TDBXParameterList* FServerParameterList;
	int FCommandHandle;
public:
	/* TDBXCommand.Destroy */ inline __fastcall virtual ~TDSServerCommand() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSServerCommandHandler : public Data::Dbxmessagehandlercommon::TDBXCommandHandler
{
	typedef Data::Dbxmessagehandlercommon::TDBXCommandHandler inherited;
	
public:
	__fastcall TDSServerCommandHandler(Data::Dbxcommon::TDBXContext* const ADbxContext);
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const Message);
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
public:
	/* TDBXCommandHandler.Destroy */ inline __fastcall virtual ~TDSServerCommandHandler() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSServerComponent : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	__fastcall virtual TDSServerComponent(System::Classes::TComponent* AOwner);
	virtual void __fastcall Start();
	virtual void __fastcall Stop();
	
protected:
	virtual TDSCustomServer* __fastcall GetServer();
	virtual void __fastcall SetServer(TDSCustomServer* const AServer);
	
private:
	TDSCustomServer* FServer;
	
public:
	__property TDSCustomServer* Server = {read=GetServer, write=SetServer};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSServerComponent() { }
	
};


class PASCALIMPLEMENTATION TDSCustomServerClass : public TDSServerComponent
{
	typedef TDSServerComponent inherited;
	
public:
	__fastcall virtual TDSCustomServerClass(System::Classes::TComponent* AOwner);
	
protected:
	virtual Datasnap::Dsreflect::TDSClass* __fastcall GetDSClass() = 0 ;
	virtual void __fastcall CreateInstance(TDSCreateInstanceEventObject* const CreateInstanceEventObject) = 0 ;
	virtual void __fastcall DestroyInstance(TDSDestroyInstanceEventObject* const DestroyInstanceEventObject) = 0 ;
	virtual void __fastcall Preparing(TDSPrepareEventObject* const PrepareEventObject) = 0 ;
	
private:
	System::UnicodeString FLifeCycle;
	System::UnicodeString FRoleName;
	
public:
	__property System::UnicodeString LifeCycle = {read=FLifeCycle, write=FLifeCycle};
	__property System::UnicodeString RoleName = {read=FRoleName, write=FRoleName};
	
protected:
	__property Datasnap::Dsreflect::TDSClass* DSClass = {read=GetDSClass};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSCustomServerClass() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSServerConnectionFactory : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TDSServerConnectionFactory* FInstance;
	Data::Dbxcommon::TDBXContext* FDBXContext;
	Data::Dbxcommon::TDBXProperties* __fastcall CombineDriverProperties(Data::Dbxcommon::TDBXProperties* ConProperties);
	TDSServerConnection* __fastcall GetConnection(Data::Dbxcommon::TDBXContext* const DBXContext, Data::Dbxcommon::TDBXProperties* const ConnectionProperties, TDSCustomServer* const AServer)/* overload */;
	
public:
	TDSServerConnection* __fastcall GetConnection(Data::Dbxcommon::TDBXProperties* const ConnectionProperties, TDSCustomServer* const AServer)/* overload */;
	__fastcall TDSServerConnectionFactory();
	__fastcall virtual ~TDSServerConnectionFactory();
	/* static */ __property TDSServerConnectionFactory* Instance = {read=FInstance};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSServerConnection : public Data::Dbxcommon::TDBXConnection
{
	typedef Data::Dbxcommon::TDBXConnection inherited;
	
public:
	__fastcall TDSServerConnection(Data::Dbxcommon::TDBXConnectionBuilder* const Builder)/* overload */;
	__fastcall TDSServerConnection(Data::Dbxcommon::TDBXProperties* const Properties, TDSCustomServer* const AServer)/* overload */;
	__fastcall virtual ~TDSServerConnection();
	void __fastcall InitSharedConnectionHandler(TDSServerConnectionHandler* const ASharedHandler);
	virtual Data::Dbxcommon::TDBXCommand* __fastcall CreateCommand()/* overload */;
	virtual void __fastcall Commit(Data::Dbxcommon::TDBXTransaction* const Transaction);
	virtual void __fastcall Rollback(Data::Dbxcommon::TDBXTransaction* const Transaction);
	
protected:
	virtual void __fastcall DerivedOpen();
	virtual Data::Dbxcommon::TDBXTransaction* __fastcall CreateAndBeginTransaction(const int IsolationLevel);
	virtual void __fastcall DerivedGetCommandTypes(System::Classes::TStrings* const List);
	virtual void __fastcall DerivedGetCommands(const System::UnicodeString CommandType, System::Classes::TStrings* const List);
	virtual void __fastcall DerivedClose();
	virtual Data::Dbxcommon::TDBXDatabaseMetaData* __fastcall GetDatabaseMetaData();
	
private:
	TDSCustomServer* FDSServer;
	TDSServerConnectionHandler* FConHandler;
	Data::Dbxmessagehandlercommon::TDBXConnectionHandler* FNextHandler;
	Data::Dbxmessagehandlercommon::TDBXPrepareMessage* FPrepareMessage;
	Data::Dbxmessagehandlercommon::TDBXExecuteMessage* FExecuteMessage;
	Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* FCommandCloseMessage;
	Data::Dbxmessagehandlercommon::TDBXConnectMessage* FConnectMessage;
	Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* FDisConnectMessage;
	Data::Dbxmessagehandlercommon::TDBXNextResultMessage* FNextResultMessage;
	Data::Dbxmessagehandlercommon::TDBXTxBeginMessage* FTxBeginMessage;
	Data::Dbxmessagehandlercommon::TDBXTxEndMessage* FTxEndMessage;
	
public:
	__property TDSServerConnectionHandler* ServerConnectionHandler = {read=FConHandler};
	__property Data::Dbxmessagehandlercommon::TDBXPrepareMessage* PrepareMessage = {read=FPrepareMessage};
	__property Data::Dbxmessagehandlercommon::TDBXExecuteMessage* ExecuteMessage = {read=FExecuteMessage};
	__property Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* CommandCloseMessage = {read=FCommandCloseMessage};
	__property Data::Dbxmessagehandlercommon::TDBXNextResultMessage* NextResultMessage = {read=FNextResultMessage};
	__property TDSCustomServer* DSServer = {read=FDSServer};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSServerConnectionHandler : public Data::Dbxmessagehandlercommon::TDBXConnectionHandler
{
	typedef Data::Dbxmessagehandlercommon::TDBXConnectionHandler inherited;
	
public:
	__fastcall TDSServerConnectionHandler(Data::Dbxcommon::TDBXContext* const ADbxContext, Data::Dbxmessagehandlercommon::TDBXConnectionHandler* const ANextHandler, Data::Dbxtransport::TDbxChannel* const AChannel);
	__fastcall virtual ~TDSServerConnectionHandler();
	virtual bool __fastcall ClearResources();
	void __fastcall InitSharedConnectionHandler(TDSServerConnectionHandler* const ASharedHandler);
	System::TObject* __fastcall CreateInstance(TDSCustomServerClass* const ServerClass, Datasnap::Dsreflect::TDSClass* const DsClass);
	void __fastcall DestroyInstance(TDSCustomServerClass* const ServerClass, System::TObject* const Instance);
	void __fastcall PrepareServerMethod(const System::UnicodeString MethodAlias, TDSServerMethod* const ServerMethod, const System::UnicodeString UserName, System::Classes::TStrings* const UserRoles, System::Classes::TStrings* const AuthorizedRoles, System::Classes::TStrings* const DeniedRoles);
	TDSAuthorizeEventObject* __fastcall GetAuthorizeMethodEventObject(TDSServerMethod* const ServerMethod, const System::UnicodeString UserName, System::Classes::TStrings* const UserRoles, System::Classes::TStrings* const AuthorizedRoles, System::Classes::TStrings* const DeniedRoles);
	bool __fastcall UsesDbxParameters();
	virtual void __fastcall DbxOpen(Data::Dbxmessagehandlercommon::TDBXOpenMessage* const Message);
	System::TObject* __fastcall GetInstance(TDSClassInfo* const ClassInfo);
	Data::Dbxmessagehandlercommon::TDBXCommandHandler* __fastcall AcquireNewCommandHandler(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message, Data::Dbxmessagehandlercommon::TDBXCommandHandler* const InNextCommandHandler);
	virtual Data::Dbxmessagehandlercommon::TDBXCommandHandler* __fastcall AcquireCommandHandler(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message);
	virtual bool __fastcall DbxBeforeRequest();
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const Message);
	void __fastcall DbxError(System::Sysutils::Exception* const Ex);
	virtual void __fastcall DbxConnect(Data::Dbxmessagehandlercommon::TDBXConnectMessage* const Message);
	virtual void __fastcall DbxDisconnect(Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* const Message);
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
	virtual void __fastcall DbxTxBegin(Data::Dbxmessagehandlercommon::TDBXTxBeginMessage* const Message);
	virtual void __fastcall DbxTxEnd(Data::Dbxmessagehandlercommon::TDBXTxEndMessage* const Message);
	virtual void __fastcall DbxVendorProperty(Data::Dbxmessagehandlercommon::TDBXVendorPropertyMessage* const Message);
	
protected:
	void __fastcall SetServerConnection(TDSServerConnection* const AServerCon);
	Data::Dbxsqlscanner::TDBXSqlScanner* __fastcall GetSQLScanner();
	virtual System::UnicodeString __fastcall GetProductName();
	void __fastcall SetDbxConnection(Data::Dbxcommon::TDBXConnection* const Con);
	virtual void __fastcall SetTransport(TDSServerTransport* const Transport);
	
private:
	void __fastcall FetchServerConnection();
	int __fastcall AddCommandHandler(Data::Dbxmessagehandlercommon::TDBXCommandHandler* const Handler);
	void __fastcall FreeCommandHandler(Data::Dbxmessagehandlercommon::TDBXCommandHandler* const Handler);
	Data::Dbxmessagehandlercommon::TDBXCommandHandler* __fastcall GetCommandHandler(const int Handle);
	int __fastcall IsCall(const System::UnicodeString CommandText);
	System::UnicodeString __fastcall FirstToken(const System::UnicodeString CommandText);
	System::UnicodeString __fastcall ScanMetaDataParameter(const System::UnicodeString InCommandText);
	bool __fastcall ConvertMetaDataCommandToServerMethodHandler(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message);
	void __fastcall DestroyEventObjects();
	void __fastcall CreateEventObjects();
	void __fastcall InitDatabaseConnectionHandler();
	Data::Dbxcommon::TDBXProperties* FConProperties;
	int FConHandle;
	TDSCustomServer* FServer;
	Data::Dbxmessagehandlercommon::TDBXConnectionHandler* FDatabaseConnectionHandler;
	bool FHasServerConnection;
	TDSHashtableInstanceProvider* FInstanceProvider;
	Data::Dbxmessagehandlercommon::TDBXCommandHandlerArray FCommandHandlers;
	int FLastCommandHandler;
	Data::Dbxmessagehandlercommon::TDBXConnectionHandler* FNextHandler;
	Data::Dbxmessagehandlercommon::TDBXErrorMessage* FErrorMessage;
	Data::Dbxsqlscanner::TDBXSqlScanner* FScanner;
	Data::Dbxcommon::TDBXConnection* FDbxConnection;
	TDSServerTransport* FTransport;
	Data::Dbxtransport::TDbxChannel* FChannel;
	TDSCreateInstanceEventObject* FCreateInstanceEventObject;
	TDSDestroyInstanceEventObject* FDestroyInstanceEventObject;
	TDSPrepareEventObject* FPrepareEventObject;
	TDSAuthenticateEventObject* FAuthenticateEventObject;
	TDSAuthorizeEventObject* FAuthorizeEventObject;
	TDSConnectEventObject* FConnectEventObject;
	TDSErrorEventObject* FErrorEventObject;
	TDSServerConnection* FServerCon;
	TDSServerConnectionHandler* FSharedConHandler;
	void __fastcall InitServerMethodEventObject(TDSServerMethodUserEventObject* EventObject, const System::UnicodeString MethodAlias, TDSServerMethod* const ServerMethod, const System::UnicodeString UserName, System::Classes::TStrings* const UserRoles, System::Classes::TStrings* const AuthorizedRoles, System::Classes::TStrings* const DeniedRoles);
	
public:
	__property Data::Dbxtransport::TDbxChannel* Channel = {read=FChannel};
	__property TDSServerConnection* ServerConnection = {write=SetServerConnection};
	__property Data::Dbxsqlscanner::TDBXSqlScanner* SQLScanner = {read=GetSQLScanner};
	__property Data::Dbxcommon::TDBXProperties* ConProperties = {read=FConProperties};
	__property Data::Dbxcommon::TDBXConnection* DbxConnection = {read=FDbxConnection, write=SetDbxConnection};
	__property TDSServerTransport* Transport = {write=SetTransport};
	__property int ConHandle = {read=FConHandle, write=FConHandle, nodefault};
	__property TDSCustomServer* Server = {read=FServer, write=FServer};
	__property TDSCreateInstanceEventObject* CreateInstanceEventObject = {read=FCreateInstanceEventObject, write=FCreateInstanceEventObject};
	__property TDSAuthenticateEventObject* AuthenticateEventObject = {read=FAuthenticateEventObject, write=FAuthenticateEventObject};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSServerHelp : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static TDSServerConnectionHandler* __fastcall GetServerConnectionHandler(TDSServerConnection* const Con);
public:
	/* TObject.Create */ inline __fastcall TDSServerHelp() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSServerHelp() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSServerMethod : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDSServerMethod();
	__fastcall virtual ~TDSServerMethod();
	void __fastcall Invoke(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual bool __fastcall ClearResources();
	
protected:
	void __fastcall SetServerSideCommand(const bool ServerSide);
	void __fastcall SetParameters(Data::Dbxmessagehandlerserver::TDBXServerParameterList* const Parameters);
	
private:
	TDSServerConnectionHandler* FServerConnection;
	Datasnap::Dsreflect::TDSMethod* FMethod;
	TDSMethodInfo* FMethodInfo;
	Datasnap::Dsreflect::TDSMethodValues* FMethodValues;
	TDSCustomServerClass* FServerClass;
	System::TObject* FMethodInstance;
	System::TObject* FAdapterInstance;
	Data::Dbxmessagehandlerserver::TDBXServerParameterList* FParameters;
	Data::Dbxcommon::TDBXParameterArray FDbxParameters;
	Data::Dbxcommon::TDBXParameter* FReturnParameter;
	bool FHasOutOrReturnParameters;
	Data::Dbxcommontable::TDBXStreamerRow* FRow;
	System::UnicodeString FLifeCycle;
	
public:
	__property Data::Dbxcommon::TDBXParameter* ReturnParameter = {read=FReturnParameter};
	__property Data::Dbxmessagehandlerserver::TDBXServerParameterList* Parameters = {read=FParameters, write=SetParameters};
	__property Datasnap::Dsreflect::TDSMethod* Method = {read=FMethod, write=FMethod};
	__property System::TObject* MethodInstance = {read=FMethodInstance, write=FMethodInstance};
	__property System::TObject* AdapterInstance = {read=FAdapterInstance, write=FAdapterInstance};
	__property Datasnap::Dsreflect::TDSMethodValues* MethodValues = {write=FMethodValues};
	__property bool ServerSideCommand = {write=SetServerSideCommand, nodefault};
	__property Data::Dbxcommon::TDBXParameter* ReturnValue = {write=FReturnParameter};
	__property TDSServerConnectionHandler* ServerConnection = {write=FServerConnection};
	__property bool HasOutOrReturnParameters = {read=FHasOutOrReturnParameters, write=FHasOutOrReturnParameters, nodefault};
	__property Data::Dbxcommontable::TDBXStreamerRow* Row = {write=FRow};
	__property TDSCustomServerClass* ServerClass = {read=FServerClass, write=FServerClass};
	__property TDSMethodInfo* MethodInfo = {read=FMethodInfo, write=FMethodInfo};
	__property System::UnicodeString Lifecycle = {read=FLifeCycle, write=FLifeCycle};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSServerMethodCommandHandler : public Data::Dbxmessagehandlercommon::TDBXCommandHandler
{
	typedef Data::Dbxmessagehandlercommon::TDBXCommandHandler inherited;
	
public:
	__fastcall TDSServerMethodCommandHandler(Data::Dbxcommon::TDBXContext* const ADbxContext, TDSServerConnectionHandler* const AServerCon, Data::Dbxmessagehandlercommon::TDBXCommandHandler* const ANextHandler);
	__fastcall virtual ~TDSServerMethodCommandHandler();
	virtual bool __fastcall ClearResources();
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const Message);
	
private:
	void __fastcall DestroyInstance();
	void __fastcall DestroyServerMethod();
	void __fastcall InitInvocationLifeCycle();
	void __fastcall DestroyInstanceIfNotNeeded();
	TDSServerConnectionHandler* FServerCon;
	TDSServerMethod* FServerMethod;
	Data::Dbxmessagehandlercommon::TDBXCommandHandler* FNextHandler;
	bool FHasInvocationLifeCycle;
	bool FHasExecuted;
	
public:
	__property TDSServerConnectionHandler* ServerConnection = {write=FServerCon};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSServerMethodProvider : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDSServerMethodProvider();
	__fastcall virtual ~TDSServerMethodProvider();
	TDSClassInfo* __fastcall GetClassInfo(const System::UnicodeString ClassName);
	void __fastcall GetServerClasses(TDSServerConnectionHandler* const ServerCon, Datasnap::Dscommontable::TDSClassEntity* const Classes)/* overload */;
	void __fastcall GetServerClasses(System::Json::TJSONArray* const Container)/* overload */;
	void __fastcall GetServerClass(const System::UnicodeString ClassName, System::Json::TJSONObject* const Container);
	void __fastcall AddServerClass(TDSClassInfo* const ClassInfo);
	void __fastcall DropServerClass(const System::UnicodeString ServerClassName);
	void __fastcall CreateServerMethod(TDSClassInfo* const ClassInfo, TDSMethodInfo* const MethodInfo, System::Rtti::TRttiType* const typeCtx, System::TObject* const ClassAuthRole);
	void __fastcall DropSeverMethod(const System::UnicodeString MethodAlias);
	void __fastcall GetServerMethods(TDSServerConnectionHandler* const ServerCon, Datasnap::Dscommontable::TDSMethodEntity* const Methods)/* overload */;
	void __fastcall GetServerMethods(const System::UnicodeString ClassName, System::Json::TJSONArray* const Container)/* overload */;
	void __fastcall GetServerMethod(const System::UnicodeString ServerMethodName, System::Json::TJSONObject* const Container);
	void __fastcall GetServerMethodParameters(TDSServerConnectionHandler* const ServerCon, Datasnap::Dscommonproxy::TDSMethodParametersEntity* const Parameters)/* overload */;
	void __fastcall GetServerMethodParameters(const System::UnicodeString SearchName, System::Json::TJSONObject* const Container)/* overload */;
	void __fastcall GetProcedures(TDSServerConnectionHandler* const ServerCon, const System::UnicodeString ProcedureNamePattern, const System::UnicodeString ProcedureTypePattern, Datasnap::Dscommontable::TDSProcedureEntity* const Procedures);
	void __fastcall GetProcedureParameters(TDSServerConnectionHandler* const ServerCon, const System::UnicodeString SchemaPattern, const System::UnicodeString MethodPattern, Datasnap::Dscommontable::TDSProcedureParametersEntity* const ProcedureParameters);
	void __fastcall UpdateConfiguration(TDSConfiguration* const Config);
	System::TObject* __fastcall GetServerMethodInstance(TDSServerConnectionHandler* const ServerCon, TDSMethodInfo* const MethodInfo);
	bool __fastcall HasServerMethod(const System::UnicodeString MethodName);
	TDSServerMethod* __fastcall PrepareMethod(TDSServerConnectionHandler* const Con, Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message, Data::Dbxcommontable::TDBXActiveTableReaderList* const ActiveStreamerRowList, Data::Dbxcommontable::TDBXStreamerRow* const InRow);
	void __fastcall Open();
	void __fastcall Close();
	
private:
	bool __fastcall IsCallableMethod(Datasnap::Dsreflect::TDSMethod* const Method);
	System::UnicodeString __fastcall CreateMethodAlias(Datasnap::Dsreflect::TDSMethod* const MethodClass);
#ifndef _WIN64
	void __fastcall AddAllMethods(System::Rtti::TRttiContext ARTTICtx, TDSClassInfo* const ClassInfo);
	TDSClassInfo* __fastcall AddBuiltinMethods(System::Rtti::TRttiContext ARTTICtx, const System::UnicodeString PackageName, const System::UnicodeString UnitName, const System::UnicodeString ClassName, const bool AdminClass);
	void __fastcall AddRegisteredServerClasses(System::Rtti::TRttiContext ARttiContext);
#else /* _WIN64 */
	void __fastcall AddAllMethods(const System::Rtti::TRttiContext &ARTTICtx, TDSClassInfo* const ClassInfo);
	TDSClassInfo* __fastcall AddBuiltinMethods(const System::Rtti::TRttiContext &ARTTICtx, const System::UnicodeString PackageName, const System::UnicodeString UnitName, const System::UnicodeString ClassName, const bool AdminClass);
	void __fastcall AddRegisteredServerClasses(const System::Rtti::TRttiContext &ARttiContext);
#endif /* _WIN64 */
	void __fastcall DropServerMethod(TDSMethodInfo* const MethodInfo, const int Index);
	void __fastcall InsertServerMethodParameter(TDSMethodInfo* const MethodInfo, Datasnap::Dscommonproxy::TDSMethodParametersEntity* const Parameters);
	System::UnicodeString __fastcall GetParameterMode(Datasnap::Dsreflect::TDSClass* const ParameterClass);
	void __fastcall AddParameter(TDSServerConnectionHandler* const ServerCon, Datasnap::Dsreflect::TDSClass* const Parameter, const System::UnicodeString ParameterName, const System::UnicodeString SchemaName, const System::UnicodeString ProcedureName, const int ParamIndex, Datasnap::Dscommontable::TDSProcedureParametersEntity* const ProcedureParameters);
	void __fastcall CheckConfiguration(TDSConfiguration* const Config);
	void __fastcall ProcessConfiguration(TDSConfiguration* const Config);
	void __fastcall UnknownLifeCycle(const System::UnicodeString LifeCycle);
	System::TObject* __fastcall GetServerInstance(TDSServerConnectionHandler* const ServerCon, TDSClassInfo* const ClassInfo);
	int __fastcall GetDbxParameterDirection(Datasnap::Dsreflect::TDSClass* const DsClass);
	Data::Dbxcommon::TDBXParameter* __fastcall CreateServerParameter(TDSServerConnectionHandler* const Con, Datasnap::Dsreflect::TDSClass* const DsClass, Data::Dbxcommon::TDBXRow* const DbxRow);
	void __fastcall PrepareParameters(TDSServerConnectionHandler* const Con, TDSMethodInfo* const MethodInfo, TDSServerMethod* const ServerMethod, Data::Dbxcommontable::TDBXActiveTableReaderItem* const Item);
#ifndef _WIN64
	System::TObject* __fastcall GetAuthRole(const System::DynamicArray<System::TCustomAttribute*> attrs, System::TObject* const defValue = (System::TObject*)(0x0));
#else /* _WIN64 */
	System::TObject* __fastcall GetAuthRole(const System::TArray__1<System::TCustomAttribute*> attrs, System::TObject* const defValue = (System::TObject*)(0x0));
#endif /* _WIN64 */
	TDSConfiguration* FConfig;
	bool FOpen;
	Data::Dbxplatform::TDBXObjectStore* FPackageTable;
	Data::Dbxplatform::TDBXObjectStore* FClassTable;
	System::Classes::TStringList* FClassList;
	Data::Dbxplatform::TDBXObjectStore* FMethodTable;
	System::Classes::TStringList* FMethodSearchNameList;
	Data::Dbxplatform::TDBXObjectStore* FStreamerTable;
	TDSHashtableInstanceProvider* FServerInstanceProvider;
	TDSCustomServer* FServer;
	
public:
	__property TDSCustomServer* Server = {write=FServer};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSServerTransport : public TDSServerComponent
{
	typedef TDSServerComponent inherited;
	
public:
	__fastcall virtual TDSServerTransport(System::Classes::TComponent* ATransportOwner);
	__fastcall virtual ~TDSServerTransport();
	void __fastcall AddConnection(Data::Dbxmessagehandlercommon::TDBXConnectionHandler* const Con);
	void __fastcall RemoveConnection(Data::Dbxmessagehandlercommon::TDBXConnectionHandler* const Con);
	void __fastcall CloseConnections();
	void __fastcall WaitForClosedConnections();
	
protected:
	void __fastcall Stopping();
	virtual void __fastcall Disconnecting(Data::Dbxmessagehandlercommon::TDBXConnectionHandler* const Con);
	void __fastcall SetBufferKBSize(const int BufferKBSize);
	virtual Data::Dbxtransport::TTransportFilterCollection* __fastcall GetFilters();
	virtual void __fastcall SetFilters(Data::Dbxtransport::TTransportFilterCollection* const Value);
	virtual System::UnicodeString __fastcall GetIPImplementationID();
	virtual void __fastcall SetIPImplementationID(const System::UnicodeString AIPImplementationID);
	
private:
	Data::Dbxmessagehandlercommon::TDBXConnectionHandlerArray FServerConnections;
	Data::Dbxcommon::TDBXContext* FDbxContext;
	Data::Dbxmessagehandlercommon::TDBXOpenMessage* FOpenMessage;
	Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* FDisconnectMessage;
	int FBufferKBSize;
	System::UnicodeString FIPImplementationID;
	Data::Dbxtransport::TTransportFilterCollection* FFilterList;
	
public:
	__property Data::Dbxcommon::TDBXContext* DbxContext = {read=FDbxContext, write=FDbxContext};
	__property int BufferKBSize = {read=FBufferKBSize, write=SetBufferKBSize, nodefault};
	__property Data::Dbxtransport::TTransportFilterCollection* Filters = {read=GetFilters, write=SetFilters};
	__property System::UnicodeString IPImplementationID = {read=GetIPImplementationID, write=SetIPImplementationID};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSSystemProperties : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSSystemProperties_TempDir L"TempDir"
	
	#define TDSSystemProperties_Port L"Port"
	
	#define TDSSystemProperties_ConfigDir L"ConfigDir"
	
public:
	/* TObject.Create */ inline __fastcall TDSSystemProperties() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSSystemProperties() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSVoidConnectionHandler : public Data::Dbxmessagehandlercommon::TDBXConnectionHandler
{
	typedef Data::Dbxmessagehandlercommon::TDBXConnectionHandler inherited;
	
public:
	__fastcall TDSVoidConnectionHandler(Data::Dbxcommon::TDBXContext* const ADbxContext);
	virtual Data::Dbxmessagehandlercommon::TDBXCommandHandler* __fastcall AcquireCommandHandler(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message);
	virtual bool __fastcall DbxBeforeRequest();
	virtual Data::Dbxcommontable::TDBXStreamerRow* __fastcall CreateDbxRow();
	virtual void __fastcall DbxConnect(Data::Dbxmessagehandlercommon::TDBXConnectMessage* const Message);
	virtual void __fastcall DbxDisconnect(Data::Dbxmessagehandlercommon::TDBXDisconnectMessage* const Message);
	virtual void __fastcall DbxOpen(Data::Dbxmessagehandlercommon::TDBXOpenMessage* const Message);
	virtual void __fastcall DbxTxBegin(Data::Dbxmessagehandlercommon::TDBXTxBeginMessage* const Message);
	virtual void __fastcall DbxTxEnd(Data::Dbxmessagehandlercommon::TDBXTxEndMessage* const Message);
	virtual void __fastcall DbxVendorProperty(Data::Dbxmessagehandlercommon::TDBXVendorPropertyMessage* const Message);
	virtual void __fastcall DbxCommandClose(Data::Dbxmessagehandlercommon::TDBXCommandCloseMessage* const Message);
	virtual void __fastcall DbxErrorMessage(Data::Dbxmessagehandlercommon::TDBXErrorMessage* const Message);
	virtual void __fastcall DbxExecute(Data::Dbxmessagehandlercommon::TDBXExecuteMessage* const Message);
	virtual void __fastcall DbxMoreBlob(Data::Dbxmessagehandlercommon::TDBXMoreBlobMessage* const Message);
	virtual void __fastcall DbxNext(Data::Dbxmessagehandlercommon::TDBXNextMessage* const Message);
	virtual void __fastcall DbxNextResult(Data::Dbxmessagehandlercommon::TDBXNextResultMessage* const Message);
	virtual void __fastcall DbxPrepare(Data::Dbxmessagehandlercommon::TDBXPrepareMessage* const Message);
	virtual void __fastcall DbxReaderClose(Data::Dbxmessagehandlercommon::TDBXReaderCloseMessage* const Message);
	
protected:
	virtual System::UnicodeString __fastcall GetProductName();
public:
	/* TDBXCommandHandler.Destroy */ inline __fastcall virtual ~TDSVoidConnectionHandler() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TInstanceProviderItem : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	class DELPHICLASS TServerClassNotifier;
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TServerClassNotifier : public System::Classes::TComponent
	{
		typedef System::Classes::TComponent inherited;
		
	private:
		TInstanceProviderItem* FParent;
		
	public:
		__fastcall TServerClassNotifier(TInstanceProviderItem* AParent);
		virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	public:
		/* TComponent.Destroy */ inline __fastcall virtual ~TServerClassNotifier() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
public:
	__fastcall TInstanceProviderItem(const System::UnicodeString AClassName, TDSDestroyInstanceEventObject* const ADestroyEventObject, TDSCustomServerClass* const AServerClass, System::TObject* const AInstance);
	void __fastcall DestroyInstance();
	TInstanceProviderItem* FNext;
	
private:
	TServerClassNotifier* FServerClassNotifier;
	System::UnicodeString FInstanceClassName;
	TDSDestroyInstanceEventObject* FDestroyEventObject;
	TDSCustomServerClass* FServerClass;
	System::TObject* FInstance;
	
public:
	__property System::TObject* Instance = {read=FInstance};
	__property System::UnicodeString InstanceClassName = {read=FInstanceClassName};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TInstanceProviderItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dscommonserver */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSCOMMONSERVER)
using namespace Datasnap::Dscommonserver;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DscommonserverHPP
