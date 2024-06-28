// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Cloud.AzureAPI.pas' rev: 34.00 (Windows)

#ifndef Data_Cloud_AzureapiHPP
#define Data_Cloud_AzureapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <Data.Cloud.CloudAPI.hpp>
#include <Data.Cloud.AzureAPI.StorageAnalytics.hpp>
#include <Xml.XMLIntf.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Cloud
{
namespace Azureapi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAzureConnectionInfo;
class DELPHICLASS TAzureAuthentication;
class DELPHICLASS TPolicy;
class DELPHICLASS TQueuePolicy;
class DELPHICLASS TTablePolicy;
class DELPHICLASS TBlobPolicy;
struct TAccessPolicy;
__interface DELPHIINTERFACE ISignedIdentifier;
typedef System::DelphiInterface<ISignedIdentifier> _di_ISignedIdentifier;
class DELPHICLASS TSignedIdentifier;
class DELPHICLASS TAzureService;
class DELPHICLASS TAzureTableService;
class DELPHICLASS TAzureQueueService;
struct TAzureContainerItem;
class DELPHICLASS TAzureContainer;
struct TAzureBlobItem;
class DELPHICLASS TAzureBlob;
struct TBlobActionConditional;
struct TAzureBlockListItem;
struct TAzureBlobPageRange;
class DELPHICLASS TAzureBlobService;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAzureConnectionInfo : public Data::Cloud::Cloudapi::TCloudConnectionInfo
{
	typedef Data::Cloud::Cloudapi::TCloudConnectionInfo inherited;
	
private:
	bool FUseDevelopmentStorage;
	System::UnicodeString FBlobEndpoint;
	System::UnicodeString FQueueEndpoint;
	System::UnicodeString FTableEndpoint;
	void __fastcall SetUseDevelopmentStorage(bool use);
	System::UnicodeString __fastcall ServiceURL(const System::UnicodeString ServiceType, const System::UnicodeString ServiceEndpoint, bool AGetSecondary);
	System::UnicodeString __fastcall GetBlobEndpoint();
	System::UnicodeString __fastcall GetQueueEndpoint();
	System::UnicodeString __fastcall GetTableEndpoint();
	
protected:
	virtual System::UnicodeString __fastcall GetAccountName();
	virtual System::UnicodeString __fastcall GetAccountKey();
	
public:
	__fastcall virtual TAzureConnectionInfo(System::Classes::TComponent* AOwner);
	System::UnicodeString __fastcall BlobURL();
	System::UnicodeString __fastcall BlobSecondaryURL();
	System::UnicodeString __fastcall TableURL();
	System::UnicodeString __fastcall TableSecondaryURL();
	System::UnicodeString __fastcall QueueURL();
	System::UnicodeString __fastcall QueueSecondaryURL();
	
__published:
	__property bool UseDevelopmentStorage = {read=FUseDevelopmentStorage, write=SetUseDevelopmentStorage, default=0};
	__property System::UnicodeString BlobEndpoint = {read=GetBlobEndpoint, write=FBlobEndpoint};
	__property System::UnicodeString QueueEndpoint = {read=GetQueueEndpoint, write=FQueueEndpoint};
	__property System::UnicodeString TableEndpoint = {read=GetTableEndpoint, write=FTableEndpoint};
	__property Protocol = {default=0};
	__property AccountName = {default=0};
	__property AccountKey = {default=0};
	__property RequestProxyHost = {default=0};
	__property RequestProxyPort = {default=0};
	__property UseDefaultEndpoints = {default=1};
public:
	/* TCloudConnectionInfo.Destroy */ inline __fastcall virtual ~TAzureConnectionInfo() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAzureAuthentication : public Data::Cloud::Cloudapi::TCloudSHA256Authentication
{
	typedef Data::Cloud::Cloudapi::TCloudSHA256Authentication inherited;
	
protected:
	virtual void __fastcall AssignKey(const System::UnicodeString AccountKey);
	
public:
	__fastcall TAzureAuthentication(TAzureConnectionInfo* ConnectionInfo)/* overload */;
public:
	/* TCloudSHA256Authentication.Create */ inline __fastcall TAzureAuthentication(Data::Cloud::Cloudapi::TCloudConnectionInfo* const ConnectionInfo, System::UnicodeString AuthorizationType)/* overload */ : Data::Cloud::Cloudapi::TCloudSHA256Authentication(ConnectionInfo, AuthorizationType) { }
	
public:
	/* TCloudAuthentication.Destroy */ inline __fastcall virtual ~TAzureAuthentication() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPolicy : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FStartDate;
	System::UnicodeString FExpiryDate;
	virtual TPolicy* __fastcall CreateInstance() = 0 ;
	virtual System::UnicodeString __fastcall GetPermission() = 0 ;
	virtual void __fastcall SetPermission(const System::UnicodeString AValue) = 0 ;
	virtual System::UnicodeString __fastcall GetXML();
	
public:
	__fastcall virtual TPolicy();
	virtual void __fastcall Assign(TPolicy* const ASource) = 0 ;
	__property System::UnicodeString StartDate = {read=FStartDate, write=FStartDate};
	__property System::UnicodeString ExpiryDate = {read=FExpiryDate, write=FExpiryDate};
	__property System::UnicodeString Permission = {read=GetPermission, write=SetPermission};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TPolicy() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TQueuePolicy : public TPolicy
{
	typedef TPolicy inherited;
	
private:
	bool FCanReadMessage;
	bool FCanAddMessage;
	bool FCanUpdateMessage;
	bool FCanProcessMessage;
	virtual TPolicy* __fastcall CreateInstance();
	virtual System::UnicodeString __fastcall GetPermission();
	virtual void __fastcall SetPermission(const System::UnicodeString AValue);
	
public:
	__fastcall virtual TQueuePolicy();
	virtual void __fastcall Assign(TPolicy* const ASource);
	__property bool CanReadMessage = {read=FCanReadMessage, write=FCanReadMessage, nodefault};
	__property bool CanAddMessage = {read=FCanAddMessage, write=FCanAddMessage, nodefault};
	__property bool CanUpdateMessage = {read=FCanUpdateMessage, write=FCanUpdateMessage, nodefault};
	__property bool CanProcessMessage = {read=FCanProcessMessage, write=FCanProcessMessage, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TQueuePolicy() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTablePolicy : public TPolicy
{
	typedef TPolicy inherited;
	
private:
	bool FCanQueryTable;
	bool FCanAddTable;
	bool FCanUpdateTable;
	bool FCanDeleteTable;
	virtual TPolicy* __fastcall CreateInstance();
	virtual System::UnicodeString __fastcall GetPermission();
	virtual void __fastcall SetPermission(const System::UnicodeString AValue);
	
public:
	__fastcall virtual TTablePolicy();
	virtual void __fastcall Assign(TPolicy* const ASource);
	__property bool CanQueryTable = {read=FCanQueryTable, write=FCanQueryTable, nodefault};
	__property bool CanAddTable = {read=FCanAddTable, write=FCanAddTable, nodefault};
	__property bool CanUpdateTable = {read=FCanUpdateTable, write=FCanUpdateTable, nodefault};
	__property bool CanDeleteTable = {read=FCanDeleteTable, write=FCanDeleteTable, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TTablePolicy() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBlobPolicy : public TPolicy
{
	typedef TPolicy inherited;
	
private:
	bool FCanReadBlob;
	bool FCanWriteBlob;
	bool FCanDeleteBlob;
	bool FCanListBlob;
	virtual TPolicy* __fastcall CreateInstance();
	virtual System::UnicodeString __fastcall GetPermission();
	virtual void __fastcall SetPermission(const System::UnicodeString AValue);
	
public:
	__fastcall virtual TBlobPolicy();
	virtual void __fastcall Assign(TPolicy* const ASource);
	__property bool CanReadBlob = {read=FCanReadBlob, write=FCanReadBlob, nodefault};
	__property bool CanWriteBlob = {read=FCanWriteBlob, write=FCanWriteBlob, nodefault};
	__property bool CanDeleteBlob = {read=FCanDeleteBlob, write=FCanDeleteBlob, nodefault};
	__property bool CanListBlob = {read=FCanListBlob, write=FCanListBlob, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBlobPolicy() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TAccessPolicy
{
public:
	System::UnicodeString Start;
	System::UnicodeString Expiry;
	bool PermRead;
	bool PermWrite;
	bool PermDelete;
	bool PermList;
	System::UnicodeString __fastcall GetPermission();
	void __fastcall SetPermission(const System::UnicodeString rwdl);
	System::UnicodeString __fastcall AsXML();
	static TAccessPolicy __fastcall Create();
	__property System::UnicodeString Permission = {read=GetPermission, write=SetPermission};
};


__interface ISignedIdentifier  : public System::IInterface 
{
	
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSignedIdentifier : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::UnicodeString FId;
	System::UnicodeString FResource;
	TPolicy* FPolicy;
	
public:
	TAccessPolicy AccessPolicy;
	__fastcall TSignedIdentifier(const System::UnicodeString Resource)/* overload */;
	__fastcall TSignedIdentifier(const System::UnicodeString Resource, const TAccessPolicy &Policy, System::UnicodeString UniqueId)/* overload */;
	__fastcall TSignedIdentifier(const System::UnicodeString Resource, TPolicy* const Policy, const System::UnicodeString UniqueId)/* overload */;
	__fastcall virtual ~TSignedIdentifier();
	virtual System::UnicodeString __fastcall AsXML();
	__property System::UnicodeString Id = {read=FId, write=FId};
	__property TPolicy* Policy = {read=FPolicy, write=FPolicy};
private:
	void *__ISignedIdentifier;	// ISignedIdentifier 
	
public:
	operator ISignedIdentifier*(void) { return (ISignedIdentifier*)&__ISignedIdentifier; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAzureService : public Data::Cloud::Cloudapi::TCloudService
{
	typedef Data::Cloud::Cloudapi::TCloudService inherited;
	
private:
	void __fastcall SetTimeout(const int AValue);
	
protected:
	System::Classes::TStrings* FRequiredHeaderNames;
	int FTimeout;
	virtual void __fastcall URLEncodeQueryParams(const bool ForURL, System::UnicodeString &ParamName, System::UnicodeString &ParamValue);
	System::UnicodeString __fastcall XMsDate();
	void __fastcall PopulateDateHeader(System::Classes::TStrings* Headers, bool AddRegularDateHeader = true);
	TAzureConnectionInfo* __fastcall GetConnectionInfo();
	virtual System::Classes::TStrings* __fastcall GetRequiredHeaderNames(/* out */ bool &InstanceOwner);
	virtual System::UnicodeString __fastcall GetCanonicalizedHeaderPrefix();
	
public:
	__fastcall TAzureService(TAzureConnectionInfo* ConnectionInfo);
	__fastcall virtual ~TAzureService();
	__property int Timeout = {read=FTimeout, write=SetTimeout, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAzureTableService : public TAzureService
{
	typedef TAzureService inherited;
	
private:
	bool __fastcall ModifyEntityHelper(const System::UnicodeString TableName, Data::Cloud::Cloudapi::TCloudTableRow* const Entity, /* out */ System::UnicodeString &url, /* out */ System::UnicodeString &QueryPrefix, /* out */ System::Classes::TStringList* &Headers);
	void __fastcall AddTableVersionHeaders(System::Classes::TStrings* Headers);
	System::UnicodeString __fastcall UpdatedDate();
	System::Generics::Collections::TList__1<Data::Cloud::Cloudapi::TCloudTableRow*>* __fastcall BuildRowList(const System::UnicodeString XML, const bool FromQuery);
	System::UnicodeString __fastcall GetTablesQueryPrefix(System::Classes::TStrings* Headers, System::UnicodeString TableName = L"Tables");
	System::UnicodeString __fastcall GetInsertEntityXML(Data::Cloud::Cloudapi::TCloudTableRow* Entity);
	
protected:
	virtual System::Classes::TStrings* __fastcall GetRequiredHeaderNames(/* out */ bool &InstanceOwner);
	
public:
	__fastcall TAzureTableService(TAzureConnectionInfo* ConnectionInfo);
	System::UnicodeString __fastcall GetTableServicePropertiesXML(Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	void __fastcall GetTableServiceProperties(Data::Cloud::Azureapi::Storageanalytics::TStorageServiceProperties* const AProperties, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall SetTableServiceProperties(Data::Cloud::Azureapi::Storageanalytics::TStorageServiceProperties* const AProperties, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::UnicodeString __fastcall GetTableServiceStatsXML(Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	void __fastcall GetTableServiceStats(Data::Cloud::Azureapi::Storageanalytics::TStorageServiceStats* const AStats, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::UnicodeString __fastcall QueryTablesXML(const System::UnicodeString ContinuationToken = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::Classes::TStrings* __fastcall QueryTables(const System::UnicodeString ContinuationToken = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::UnicodeString __fastcall QueryEntitiesXML(const System::UnicodeString TableName, const System::UnicodeString FilterExpression = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString NextPartitionKey = System::UnicodeString(), const System::UnicodeString NextRowKey = System::UnicodeString())/* overload */;
	System::Generics::Collections::TList__1<Data::Cloud::Cloudapi::TCloudTableRow*>* __fastcall QueryEntities(const System::UnicodeString TableName, const System::UnicodeString FilterExpression = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString NextPartitionKey = System::UnicodeString(), const System::UnicodeString NextRowKey = System::UnicodeString())/* overload */;
	System::UnicodeString __fastcall QueryEntityXML(const System::UnicodeString TableName, const System::UnicodeString PartitionKey, const System::UnicodeString RowKey, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	Data::Cloud::Cloudapi::TCloudTableRow* __fastcall QueryEntity(const System::UnicodeString TableName, const System::UnicodeString PartitionKey, const System::UnicodeString RowKey, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall CreateTable(const System::UnicodeString TableName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall DeleteTable(const System::UnicodeString TableName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	void __fastcall PreflightTableRequest(const System::UnicodeString ATableName, const System::UnicodeString AOrigin, const System::UnicodeString AAccessControlRequestMethod, const System::UnicodeString AAccessControlRequestHeaders, Data::Cloud::Azureapi::Storageanalytics::TCorsRule* const ARule, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall InsertEntity(const System::UnicodeString TableName, Data::Cloud::Cloudapi::TCloudTableRow* Entity, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall UpdateEntity(const System::UnicodeString TableName, Data::Cloud::Cloudapi::TCloudTableRow* Entity, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall MergeEntity(const System::UnicodeString TableName, Data::Cloud::Cloudapi::TCloudTableRow* Entity, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall DeleteEntity(const System::UnicodeString TableName, Data::Cloud::Cloudapi::TCloudTableRow* const Entity, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::UnicodeString __fastcall GetTableACLXML(const System::UnicodeString ATableName, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#ifndef _WIN64
	System::DynamicArray<TSignedIdentifier*> __fastcall GetTableACL(const System::UnicodeString ATableName, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#else /* _WIN64 */
	System::TArray__1<TSignedIdentifier*> __fastcall GetTableACL(const System::UnicodeString ATableName, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#endif /* _WIN64 */
	bool __fastcall SetTableACL(const System::UnicodeString ATableName, const System::UnicodeString ASignedIdentifierId, TPolicy* const AAccessPolicy, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#ifndef _WIN64
	bool __fastcall SetTableACL(const System::UnicodeString ATableName, System::DynamicArray<TSignedIdentifier*> ASignedIdentifiers, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	bool __fastcall SetTableACL(const System::UnicodeString ATableName, System::TArray__1<TSignedIdentifier*> ASignedIdentifiers, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
public:
	/* TAzureService.Destroy */ inline __fastcall virtual ~TAzureTableService() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAzureQueueService : public TAzureService
{
	typedef TAzureService inherited;
	
private:
	System::UnicodeString __fastcall GetQueuesQueryPrefix(System::Classes::TStrings* Headers, System::UnicodeString QueueName = L"Queues");
	System::Generics::Collections::TList__1<Data::Cloud::Cloudapi::TCloudQueueMessage*>* __fastcall GetMessagesFromXML(const System::UnicodeString xml);
	System::UnicodeString __fastcall GetOrPeekMessagesXML(const System::UnicodeString QueueName, bool PeekOnly, int NumOfMessages = 0x0, int VisibilityTimeout = 0x0, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	
public:
	int __fastcall GetMaxMessageReturnCount();
	System::UnicodeString __fastcall GetQueueServicePropertiesXML(Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	void __fastcall GetQueueServiceProperties(Data::Cloud::Azureapi::Storageanalytics::TStorageServiceProperties* const AProperties, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall SetQueueServiceProperties(Data::Cloud::Azureapi::Storageanalytics::TStorageServiceProperties* const AProperties, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::UnicodeString __fastcall GetQueueServiceStatsXML(Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	void __fastcall GetQueueServiceStats(Data::Cloud::Azureapi::Storageanalytics::TStorageServiceStats* const AStats, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::UnicodeString __fastcall ListQueuesXML(System::Classes::TStrings* OptionalParams = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::Generics::Collections::TList__1<Data::Cloud::Cloudapi::TCloudQueue>* __fastcall ListQueues(System::Classes::TStrings* OptionalParams = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall CreateQueue(const System::UnicodeString QueueName, System::Classes::TStrings* const MetaDataHeaders = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall DeleteQueue(const System::UnicodeString QueueName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall GetQueueMetadata(const System::UnicodeString QueueName, /* out */ System::Classes::TStrings* &MetaData, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall SetQueueMetadata(const System::UnicodeString QueueName, System::Classes::TStrings* const MetaData, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::UnicodeString __fastcall GetQueueACLXML(const System::UnicodeString AQueueName, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#ifndef _WIN64
	System::DynamicArray<TSignedIdentifier*> __fastcall GetQueueACL(const System::UnicodeString AQueueName, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#else /* _WIN64 */
	System::TArray__1<TSignedIdentifier*> __fastcall GetQueueACL(const System::UnicodeString AQueueName, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#endif /* _WIN64 */
	bool __fastcall SetQueueACL(const System::UnicodeString AQueueName, const System::UnicodeString ASignedIdentifierId, TPolicy* const AAccessPolicy, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#ifndef _WIN64
	bool __fastcall SetQueueACL(const System::UnicodeString AQueueName, System::DynamicArray<TSignedIdentifier*> ASignedIdentifiers, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	bool __fastcall SetQueueACL(const System::UnicodeString AQueueName, System::TArray__1<TSignedIdentifier*> ASignedIdentifiers, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	void __fastcall PreflightQueueRequest(const System::UnicodeString AQueueName, const System::UnicodeString AOrigin, const System::UnicodeString AAccessControlRequestMethod, const System::UnicodeString AAccessControlRequestHeaders, Data::Cloud::Azureapi::Storageanalytics::TCorsRule* const ARule, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall AddMessage(const System::UnicodeString QueueName, const System::UnicodeString MessageText, const int TimeToLive = 0x0, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::UnicodeString __fastcall GetMessagesXML(const System::UnicodeString QueueName, int NumOfMessages = 0x0, int VisibilityTimeout = 0x0, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::Generics::Collections::TList__1<Data::Cloud::Cloudapi::TCloudQueueMessage*>* __fastcall GetMessages(const System::UnicodeString QueueName, int NumOfMessages = 0x0, int VisibilityTimeout = 0x0, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::UnicodeString __fastcall PeekMessagesXML(const System::UnicodeString QueueName, int NumOfMessages, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::Generics::Collections::TList__1<Data::Cloud::Cloudapi::TCloudQueueMessage*>* __fastcall PeekMessages(const System::UnicodeString QueueName, int NumOfMessages, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall DeleteMessage(const System::UnicodeString QueueName, const System::UnicodeString MessageId, const System::UnicodeString PopReceipt, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall DeleteMessage(const System::UnicodeString QueueName, Data::Cloud::Cloudapi::TCloudQueueMessage* const QueueMessage, bool GetPopReceiptIfNeeded = true, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall ClearMessages(const System::UnicodeString QueueName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
public:
	/* TAzureService.Create */ inline __fastcall TAzureQueueService(TAzureConnectionInfo* ConnectionInfo) : TAzureService(ConnectionInfo) { }
	/* TAzureService.Destroy */ inline __fastcall virtual ~TAzureQueueService() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TAzureContainerItem
{
public:
	System::UnicodeString Name;
	System::UnicodeString URL;
#ifndef _WIN64
	System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > Properties;
	System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > Metadata;
#else /* _WIN64 */
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > Properties;
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > Metadata;
#endif /* _WIN64 */
	bool __fastcall IsRoot();
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAzureContainer : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FName;
	System::UnicodeString FURL;
	System::Classes::TStrings* FProperties;
	System::Classes::TStrings* FMetadata;
	
public:
	__fastcall TAzureContainer(const System::UnicodeString Name, const System::UnicodeString URL, System::Classes::TStrings* Properties, System::Classes::TStrings* Metadata);
	__classmethod TAzureContainer* __fastcall CreateFromRecord(const TAzureContainerItem &AAzureContainer);
	__fastcall virtual ~TAzureContainer();
	bool __fastcall IsRoot();
	__property System::UnicodeString Name = {read=FName};
	__property System::UnicodeString URL = {read=FURL};
	__property System::Classes::TStrings* Properties = {read=FProperties};
	__property System::Classes::TStrings* Metadata = {read=FMetadata};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TBlobPublicAccess : unsigned char { bpaPrivate, bpaContainer, bpaBlob };

enum DECLSPEC_DENUM TAzureBlobType : unsigned char { abtBlock, abtPage, abtAppend, abtPrefix };

enum DECLSPEC_DENUM TAzureLeaseStatus : unsigned char { alsLocked, alsUnlocked };

struct DECLSPEC_DRECORD TAzureBlobItem
{
	
private:
	typedef System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > _TAzureBlobItem__1;
	
	typedef System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > _TAzureBlobItem__2;
	
	
public:
	System::UnicodeString Name;
	System::UnicodeString Url;
	System::UnicodeString Snapshot;
	TAzureBlobType BlobType;
	TAzureLeaseStatus LeaseStatus;
	_TAzureBlobItem__1 Properties;
	_TAzureBlobItem__2 Metadata;
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAzureBlob : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FName;
	System::UnicodeString FUrl;
	System::UnicodeString FSnapshot;
	TAzureBlobType FBlobType;
	TAzureLeaseStatus FLeaseStatus;
	System::Classes::TStrings* FProperties;
	System::Classes::TStrings* FMetadata;
	
public:
	__fastcall TAzureBlob(const System::UnicodeString Name, TAzureBlobType BlobType, const System::UnicodeString Url, TAzureLeaseStatus LeaseStatus, const System::UnicodeString Snapshot);
	__classmethod TAzureBlob* __fastcall CreateFromRecord(const TAzureBlobItem &AAzureBlobItem);
	__fastcall virtual ~TAzureBlob();
	__property System::UnicodeString Name = {read=FName};
	__property System::UnicodeString Url = {read=FUrl};
	__property TAzureBlobType BlobType = {read=FBlobType, nodefault};
	__property System::UnicodeString Snapshot = {read=FSnapshot};
	__property TAzureLeaseStatus LeaseStatus = {read=FLeaseStatus, write=FLeaseStatus, nodefault};
	__property System::Classes::TStrings* Properties = {read=FProperties};
	__property System::Classes::TStrings* Metadata = {read=FMetadata};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TBlobActionConditional
{
public:
	System::UnicodeString IfSourceModifiedSince;
	System::UnicodeString IfSourceUnmodifiedSince;
	System::UnicodeString IfSourceMatch;
	System::UnicodeString IfSourceNoneMatch;
	System::UnicodeString IfModifiedSince;
	System::UnicodeString IfUnmodifiedSince;
	System::UnicodeString IfMatch;
	System::UnicodeString IfNoneMatch;
	System::UnicodeString IfSequenceNumberLessThanOrEqual;
	System::UnicodeString IfSequenceNumberLessThan;
	System::UnicodeString IfSequenceNumberEquals;
	static TBlobActionConditional __fastcall Create();
	void __fastcall PopulateHeaders(System::Classes::TStrings* Headers);
};


enum DECLSPEC_DENUM TAzureBlockType : unsigned char { abtCommitted, abtUncommitted, abtLatest };

struct DECLSPEC_DRECORD TAzureBlockListItem
{
public:
	System::UnicodeString BlockId;
	System::UnicodeString Size;
	TAzureBlockType BlockType;
	static TAzureBlockListItem __fastcall Create(System::UnicodeString ABlockId, TAzureBlockType ABlockType, System::UnicodeString ASize = L"0");
	System::UnicodeString __fastcall AsXML();
};


enum DECLSPEC_DENUM TAzureQueryIncludeBlockType : unsigned char { aqbtCommitted, aqbtUncommitted, aqbtAll };

struct DECLSPEC_DRECORD TAzureBlobPageRange
{
public:
	__int64 StartByte;
	__int64 EndByte;
	static TAzureBlobPageRange __fastcall Create(__int64 StartByte, __int64 EndByte);
	int __fastcall GetStartPage();
	int __fastcall GetPageCount();
};


enum DECLSPEC_DENUM TAzureContainerLeaseActionMode : unsigned char { clamAcquire, clamRenew, clamChange, clamRelease, clamBreak };

enum DECLSPEC_DENUM TAzureBlobDataset : unsigned char { bdsSnapshots, bdsMetadata, bdsUncommitedBlobs, bdsCopy };

typedef System::Set<TAzureBlobDataset, TAzureBlobDataset::bdsSnapshots, TAzureBlobDataset::bdsCopy> TAzureBlobDatasets;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAzureBlobService : public TAzureService
{
	typedef TAzureService inherited;
	
private:
	System::UnicodeString __fastcall GetBlobContainerQueryPrefix(System::Classes::TStrings* const AHeaders, const System::UnicodeString AContainerName, const System::UnicodeString ABlobName);
#ifndef _WIN64
	System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall ParseContainerPropertiesFromNode(const Xml::Xmlintf::_di_IXMLNode ANode);
#else /* _WIN64 */
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall ParseContainerPropertiesFromNode(const Xml::Xmlintf::_di_IXMLNode ANode);
#endif /* _WIN64 */
	TAzureContainerItem __fastcall ParseContainerFromNode(const Xml::Xmlintf::_di_IXMLNode AContainerNode);
	TAzureBlobItem __fastcall ParseBlobFromNode(const Xml::Xmlintf::_di_IXMLNode ABlobNode);
	System::Classes::TStringList* __fastcall BuildMetadataHeaderList(System::Classes::TStrings* const AMetadata);
	System::UnicodeString __fastcall GetPublicAccessString(TBlobPublicAccess APublicAccess);
	bool __fastcall HandleContainerLease(const System::UnicodeString AContainerName, TAzureContainerLeaseActionMode ALeaseAction, System::UnicodeString &ALeaseId, const System::UnicodeString AProposedLeaseId, int ALeaseDuration, /* out */ int &ALeaseTimeRemaining, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::UnicodeString __fastcall HandleBlobLease(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseAction, const System::UnicodeString ALeaseId, const System::UnicodeString AProposedLeaseId, int ALeaseDuration, int ASuccessCode, /* out */ bool &ASuccess, Data::Cloud::Cloudapi::TCloudResponseInfo* AResponseInfo);
	bool __fastcall DeleteBlobInternal(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ASnapShot, bool AOnlySnapshots, const System::UnicodeString ALeaseId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#ifndef _WIN64
	bool __fastcall GetBlobInternal(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ASnapshot, const System::UnicodeString ALeaseId, __int64 AStartByte, __int64 AEndByte, bool AGetAsHash, /* out */ System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AMetadata, /* out */ System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AProperties, System::Classes::TStream* AResponseContent, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall PutBlobInternal(TAzureBlobType ABlobType, const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, const System::DynamicArray<System::Byte> ABlockContent, __int64 AMaximumSize, __int64 ABlobSequenceNumber, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AOptionalHeaders, const int AOptionalHeaders_High, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#else /* _WIN64 */
	bool __fastcall GetBlobInternal(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ASnapshot, const System::UnicodeString ALeaseId, __int64 AStartByte, __int64 AEndByte, bool AGetAsHash, /* out */ System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AMetadata, /* out */ System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AProperties, System::Classes::TStream* AResponseContent, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall PutBlobInternal(TAzureBlobType ABlobType, const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, const System::TArray__1<System::Byte> ABlockContent, __int64 AMaximumSize, __int64 ABlobSequenceNumber, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AOptionalHeaders, const int AOptionalHeaders_High, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#endif /* _WIN64 */
	bool __fastcall CopyBlobInternal(const System::UnicodeString ATargetContainerName, const System::UnicodeString ATargetBlobName, const System::UnicodeString ASourceContainerName, const System::UnicodeString ASourceBlobName, const System::UnicodeString ASourceSnapshot, const System::UnicodeString ATargetLeaseId, const TBlobActionConditional &ACopyConditionals, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#ifndef _WIN64
	bool __fastcall PutPageInternal(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, bool ADoClear, int AStartPage, int APageCount, const System::DynamicArray<System::Byte> AContent, const System::UnicodeString AContentMD5, const TBlobActionConditional &AActions, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	bool __fastcall PutPageInternal(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, bool ADoClear, int AStartPage, int APageCount, const System::TArray__1<System::Byte> AContent, const System::UnicodeString AContentMD5, const TBlobActionConditional &AActions, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	void __fastcall PopulateBlobPropertyHeaders(System::Classes::TStrings* AHeaders, System::Classes::TStrings* AProperties);
	void __fastcall PopulatePropertyHeaders(System::Classes::TStrings* const AHeaders, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AProperties, const int AProperties_High);
	void __fastcall PopulateMetadataHeaders(System::Classes::TStrings* const AHeaders, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High);
	void __fastcall PopulateOptionalHeaders(System::Classes::TStrings* const AHeaders, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AOptions, const int AOptions_High);
#ifndef _WIN64
	System::DynamicArray<TAzureBlockListItem> __fastcall ParseBlockItemsFromNode(Xml::Xmlintf::_di_IXMLNode ABlocksNode, TAzureBlockType ABlockType);
#else /* _WIN64 */
	System::TArray__1<TAzureBlockListItem> __fastcall ParseBlockItemsFromNode(Xml::Xmlintf::_di_IXMLNode ABlocksNode, TAzureBlockType ABlockType);
#endif /* _WIN64 */
	System::UnicodeString __fastcall ListContainersXML(bool AIncludeMetadata, const System::UnicodeString APrefix, const System::UnicodeString AMarker, int AMaxResult, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	System::UnicodeString __fastcall ListBlobsXML(const System::UnicodeString AContainerName, const System::UnicodeString APrefix, const System::UnicodeString ADelimiter, const System::UnicodeString AMarker, int AMaxResult, TAzureBlobDatasets ADatasets, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	System::UnicodeString __fastcall GetPageRangesXML(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, __int64 AStartByte, __int64 AEndByte, const System::UnicodeString ASnapshot, const System::UnicodeString APrevSnapshot, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::UnicodeString __fastcall GetBlockListXML(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, const System::UnicodeString ASnapShot, TAzureQueryIncludeBlockType ABlockType, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	System::UnicodeString __fastcall GetContainerACLXML(const System::UnicodeString AContainerName, /* out */ TBlobPublicAccess &APublicAccess, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	
public:
	System::UnicodeString __fastcall GetBlobServicePropertiesXML(Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	void __fastcall GetBlobServiceProperties(Data::Cloud::Azureapi::Storageanalytics::TStorageServiceProperties* const AProperties, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall SetBlobServiceProperties(Data::Cloud::Azureapi::Storageanalytics::TStorageServiceProperties* const AProperties, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::UnicodeString __fastcall GetBlobServiceStatsXML(Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	void __fastcall GetBlobServiceStats(Data::Cloud::Azureapi::Storageanalytics::TStorageServiceStats* const AStats, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::UnicodeString __fastcall ListContainersXML _DEPRECATED_ATTRIBUTE1("Use ListContainers method instead") (System::Classes::TStrings* OptionalParams = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::Generics::Collections::TList__1<TAzureContainer*>* __fastcall ListContainers _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (/* out */ System::UnicodeString &NextMarker, System::Classes::TStrings* OptionalParams = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::Generics::Collections::TList__1<TAzureContainer*>* __fastcall ListContainers _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::Classes::TStrings* OptionalParams = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#ifndef _WIN64
	System::DynamicArray<TAzureContainerItem> __fastcall ListContainers(bool AIncludeMetadata, const System::UnicodeString APrefix, const System::UnicodeString AMarker, int AMaxResult, /* out */ System::UnicodeString &ANextMarker, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	System::TArray__1<TAzureContainerItem> __fastcall ListContainers(bool AIncludeMetadata, const System::UnicodeString APrefix, const System::UnicodeString AMarker, int AMaxResult, /* out */ System::UnicodeString &ANextMarker, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	bool __fastcall CreateContainer _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::Classes::TStrings* MetaData = (System::Classes::TStrings*)(0x0), TBlobPublicAccess PublicAccess = (TBlobPublicAccess)(0x1), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall CreateContainer(const System::UnicodeString AContainerName, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetaData, const int AMetaData_High, TBlobPublicAccess APublicAccess, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall CreateRootContainer _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::Classes::TStrings* MetaData = (System::Classes::TStrings*)(0x0), TBlobPublicAccess PublicAccess = (TBlobPublicAccess)(0x1), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall CreateRootContainer(const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetaData, const int AMetaData_High, TBlobPublicAccess APublicAccess, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall DeleteContainer _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName)/* overload */;
	bool __fastcall DeleteContainer(const System::UnicodeString AContainerName, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall DeleteRootContainer(Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall GetContainerProperties _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, /* out */ System::Classes::TStrings* &Properties, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall GetContainerProperties _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, /* out */ System::Classes::TStrings* &Properties, /* out */ System::Classes::TStrings* &Metadata, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#ifndef _WIN64
	System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetContainerProperties(const System::UnicodeString AContainerName, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetContainerProperties(const System::UnicodeString AContainerName, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	bool __fastcall GetContainerMetadata _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, /* out */ System::Classes::TStrings* &Metadata, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#ifndef _WIN64
	System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetContainerMetadata(const System::UnicodeString AContainerName, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetContainerMetadata(const System::UnicodeString AContainerName, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	bool __fastcall SetContainerMetadata _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::Classes::TStrings* const Metadata, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall SetContainerMetadata(const System::UnicodeString AContainerName, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	System::UnicodeString __fastcall GetContainerACLXML _DEPRECATED_ATTRIBUTE1("Use GetContainerACL method instead") (System::UnicodeString ContainerName, /* out */ TBlobPublicAccess &PublicAccess)/* overload */;
	System::Generics::Collections::TList__1<TSignedIdentifier*>* __fastcall GetContainerACL _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, /* out */ TBlobPublicAccess &PublicAccess, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#ifndef _WIN64
	System::DynamicArray<_di_ISignedIdentifier> __fastcall GetContainerACL(const System::UnicodeString AContainerName, /* out */ TBlobPublicAccess &APublicAccess, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	System::TArray__1<_di_ISignedIdentifier> __fastcall GetContainerACL(const System::UnicodeString AContainerName, /* out */ TBlobPublicAccess &APublicAccess, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	bool __fastcall SetContainerACL _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, const System::UnicodeString SignedIdentifierId, const TAccessPolicy &AccessPolicy, TBlobPublicAccess PublicAccess = (TBlobPublicAccess)(0x1), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall SetContainerACL _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (const System::UnicodeString AContainerName, const System::UnicodeString ASignedIdentifierId, TPolicy* const AAccessPolicy, TBlobPublicAccess APublicAccess, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall SetContainerACL _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::Generics::Collections::TList__1<TSignedIdentifier*>* SignedIdentifiers, TBlobPublicAccess PublicAccess = (TBlobPublicAccess)(0x1), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString AClientRequestID = System::UnicodeString())/* overload */;
	bool __fastcall SetContainerACL(const System::UnicodeString AContainerName, _di_ISignedIdentifier *ASignedIdentifiers, const int ASignedIdentifiers_High, const TBlobPublicAccess APublicAccess, const System::UnicodeString AClientRequestID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall AcquireContainerLease(const System::UnicodeString AContainerName, System::UnicodeString &ALeaseId, int ALeaseDuration, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall RenewContainerLease(const System::UnicodeString AContainerName, System::UnicodeString &ALeaseId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall ReleaseContainerLease _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (const System::UnicodeString AContainerName, System::UnicodeString &ALeaseId)/* overload */;
	bool __fastcall ReleaseContainerLease(const System::UnicodeString AContainerName, System::UnicodeString &ALeaseId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall BreakContainerLease(const System::UnicodeString AContainerName, /* out */ int &ALeaseTimeRemaining, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall ChangeContainerLease(const System::UnicodeString AContainerName, System::UnicodeString &ALeaseID, const System::UnicodeString AProposedLeaseID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::UnicodeString __fastcall ListBlobsXML _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::Classes::TStrings* OptionalParams = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::Generics::Collections::TList__1<TAzureBlob*>* __fastcall ListBlobs _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::Classes::TStrings* OptionalParams = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::Generics::Collections::TList__1<TAzureBlob*>* __fastcall ListBlobs _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, /* out */ System::UnicodeString &NextMarker, System::Classes::TStrings* OptionalParams = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#ifndef _WIN64
	System::DynamicArray<TAzureBlobItem> __fastcall ListBlobs(const System::UnicodeString AContainerName, const System::UnicodeString APrefix, const System::UnicodeString ADelimiter, const System::UnicodeString AMarker, int AMaxResult, TAzureBlobDatasets ADatasets, /* out */ System::UnicodeString &ANextMarker, /* out */ System::DynamicArray<System::UnicodeString> &ABlobPrefix, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall PutBlockBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::DynamicArray<System::Byte> Content, System::UnicodeString LeaseId = System::UnicodeString(), System::Classes::TStrings* OptionalHeaders = (System::Classes::TStrings*)(0x0), System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutBlockBlob(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, const System::DynamicArray<System::Byte> AContent, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AOptionalHeaders, const int AOptionalHeaders_High, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall PutPageBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, __int64 MaximumSize, System::Classes::TStrings* OptionalHeaders = (System::Classes::TStrings*)(0x0), System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), __int64 BlobSequenceNumber = 0LL, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#else /* _WIN64 */
	System::TArray__1<TAzureBlobItem> __fastcall ListBlobs(const System::UnicodeString AContainerName, const System::UnicodeString APrefix, const System::UnicodeString ADelimiter, const System::UnicodeString AMarker, int AMaxResult, TAzureBlobDatasets ADatasets, /* out */ System::UnicodeString &ANextMarker, /* out */ System::TArray__1<System::UnicodeString> &ABlobPrefix, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall PutBlockBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::TArray__1<System::Byte> Content, System::UnicodeString LeaseId = System::UnicodeString(), System::Classes::TStrings* OptionalHeaders = (System::Classes::TStrings*)(0x0), System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutBlockBlob(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, const System::TArray__1<System::Byte> AContent, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AOptionalHeaders, const int AOptionalHeaders_High, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall PutPageBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, __int64 MaximumSize, System::Classes::TStrings* OptionalHeaders = (System::Classes::TStrings*)(0x0), System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), __int64 BlobSequenceNumber = (__int64)(0LL), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#endif /* _WIN64 */
	bool __fastcall PutPageBlob(System::UnicodeString AContainerName, System::UnicodeString ABlobName, System::UnicodeString ALeaseID, __int64 AMaximumSize, __int64 ABlobSequenceNumber, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AOptionalHeaders, const int AOptionalHeaders_High, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall PutAppendBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, System::Classes::TStrings* const AOptionalHeaders, System::Classes::TStrings* const AMetadata, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall PutAppendBlob(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AOptionalHeaders, const int AOptionalHeaders_High, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall AcquireBlobLease _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, /* out */ System::UnicodeString &LeaseId, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), int LeaseDuration = 0xffffffff, const System::UnicodeString ProposedLeaseID = System::UnicodeString())/* overload */;
	bool __fastcall AcquireBlobLease(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, /* out */ System::UnicodeString &ALeaseId, const System::UnicodeString AProposedLeaseID, int ALeaseDuration, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall RenewBlobLease _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::UnicodeString LeaseId)/* overload */;
	bool __fastcall RenewBlobLease(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall ReleaseBlobLease _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::UnicodeString LeaseId)/* overload */;
	bool __fastcall ReleaseBlobLease(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall BreakBlobLease _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, /* out */ int &LeaseTimeRemaining)/* overload */;
	bool __fastcall BreakBlobLease(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, /* out */ int &ALeaseTimeRemaining, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall ChangeBlobLease(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, const System::UnicodeString AProposedLeaseID, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall GetBlobMetadata _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, /* out */ System::Classes::TStrings* &Metadata, const System::UnicodeString Snapshot = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#ifndef _WIN64
	System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetBlobMetadata(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ASnapshot, const System::UnicodeString ALeaseId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetBlobMetadata(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ASnapshot, const System::UnicodeString ALeaseId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	bool __fastcall SetBlobMetadata _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::Classes::TStrings* Metadata, System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall SetBlobMetadata(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, const System::UnicodeString ALeaseId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	void __fastcall PreflightBlobRequest(const System::UnicodeString AContainerName, const System::UnicodeString AOrigin, const System::UnicodeString AAccessControlRequestMethod, const System::UnicodeString AAccessControlRequestHeaders, Data::Cloud::Azureapi::Storageanalytics::TCorsRule* const ARule, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	void __fastcall PreflightBlobRequest(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString AOrigin, const System::UnicodeString AAccessControlRequestMethod, const System::UnicodeString AAccessControlRequestHeaders, Data::Cloud::Azureapi::Storageanalytics::TCorsRule* const ARule, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall GetBlobProperties _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, /* out */ System::Classes::TStrings* &Properties, const System::UnicodeString Snapshot = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall GetBlobProperties _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, /* out */ System::Classes::TStrings* &Properties, /* out */ System::Classes::TStrings* &Metadata, const System::UnicodeString Snapshot = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#ifndef _WIN64
	System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetBlobProperties(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, const System::UnicodeString ASnapshot, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetBlobProperties(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, const System::UnicodeString ASnapshot, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	bool __fastcall SetBlobProperties _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::Classes::TStrings* Properties, const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall SetBlobProperties(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, const System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AProperties, const int AProperties_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall DeleteBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName)/* overload */;
	bool __fastcall DeleteBlob(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, bool AOnlySnapshots, const System::UnicodeString ALeaseId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall DeleteBlobSnapshot _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::UnicodeString SnapShot)/* overload */;
	bool __fastcall DeleteBlobSnapshot(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ASnapShot, const System::UnicodeString ALeaseId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall GetBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::Classes::TStream* BlobStream, const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall GetBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::Classes::TStream* BlobStream, /* out */ System::Classes::TStrings* &Properties, /* out */ System::Classes::TStrings* &Metadata, const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall GetBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::Classes::TStream* BlobStream, __int64 StartByte, __int64 EndByte, bool GetAsHash = false, const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall GetBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::Classes::TStream* BlobStream, /* out */ System::Classes::TStrings* &Properties, /* out */ System::Classes::TStrings* &Metadata, __int64 StartByte, __int64 EndByte, bool GetAsHash = false, const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#ifndef _WIN64
	bool __fastcall GetBlob(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, __int64 AStartByte, __int64 AEndByte, bool AGetAsHash, /* out */ System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AProperties, /* out */ System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AMetadata, System::Classes::TStream* ABlobStream, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	bool __fastcall GetBlob(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, __int64 AStartByte, __int64 AEndByte, bool AGetAsHash, /* out */ System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AProperties, /* out */ System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AMetadata, System::Classes::TStream* ABlobStream, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	bool __fastcall GetBlobSnapshot _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::UnicodeString Snapshot, System::Classes::TStream* SnapshotStream, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall GetBlobSnapshot _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::UnicodeString Snapshot, System::Classes::TStream* SnapshotStream, /* out */ System::Classes::TStrings* &Properties, /* out */ System::Classes::TStrings* &Metadata, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#ifndef _WIN64
	bool __fastcall GetBlobSnapshot _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::UnicodeString Snapshot, System::Classes::TStream* SnapshotStream, __int64 StartByte = 0LL, __int64 EndByte = 0LL, bool GetAsHash = false, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall GetBlobSnapshot _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::UnicodeString Snapshot, System::Classes::TStream* SnapshotStream, /* out */ System::Classes::TStrings* &Properties, /* out */ System::Classes::TStrings* &Metadata, __int64 StartByte = 0LL, __int64 EndByte = 0LL, bool GetAsHash = false, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall GetBlobSnapshot(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ASnapshot, const System::UnicodeString ALeaseId, __int64 AStartByte, __int64 AEndByte, bool AGetAsHash, /* out */ System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AProperties, /* out */ System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AMetadata, /* out */ System::Classes::TStream* &ASnapshotStream, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	bool __fastcall GetBlobSnapshot _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::UnicodeString Snapshot, System::Classes::TStream* SnapshotStream, __int64 StartByte = (__int64)(0LL), __int64 EndByte = (__int64)(0LL), bool GetAsHash = false, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall GetBlobSnapshot _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::UnicodeString Snapshot, System::Classes::TStream* SnapshotStream, /* out */ System::Classes::TStrings* &Properties, /* out */ System::Classes::TStrings* &Metadata, __int64 StartByte = (__int64)(0LL), __int64 EndByte = (__int64)(0LL), bool GetAsHash = false, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall GetBlobSnapshot(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ASnapshot, const System::UnicodeString ALeaseId, __int64 AStartByte, __int64 AEndByte, bool AGetAsHash, /* out */ System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AProperties, /* out */ System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > &AMetadata, /* out */ System::Classes::TStream* &ASnapshotStream, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	bool __fastcall CopyBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString TargetContainerName, System::UnicodeString TargetBlobName, System::UnicodeString SourceContainerName, System::UnicodeString SourceBlobName, const System::UnicodeString TargetLeaseId = System::UnicodeString(), System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall CopyBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString TargetContainerName, System::UnicodeString TargetBlobName, System::UnicodeString SourceContainerName, System::UnicodeString SourceBlobName, const TBlobActionConditional &CopyConditionals, const System::UnicodeString TargetLeaseId = System::UnicodeString(), System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall CopyBlob(const System::UnicodeString ATargetContainerName, const System::UnicodeString ATargetBlobName, const System::UnicodeString ASourceContainerName, const System::UnicodeString ASourceBlobName, const System::UnicodeString ATargetLeaseId, const TBlobActionConditional &ACopyConditionals, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall CopySnapshotToBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString TargetContainerName, System::UnicodeString TargetBlobName, System::UnicodeString SourceContainerName, System::UnicodeString SourceBlobName, const System::UnicodeString SourceSnapshot, System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall CopySnapshotToBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString TargetContainerName, System::UnicodeString TargetBlobName, System::UnicodeString SourceContainerName, System::UnicodeString SourceBlobName, const System::UnicodeString SourceSnapshot, const TBlobActionConditional &CopyConditionals, System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall CopySnapshotToBlob(const System::UnicodeString ATargetContainerName, const System::UnicodeString ATargetBlobName, const System::UnicodeString ASourceContainerName, const System::UnicodeString ASourceBlobName, const System::UnicodeString ASourceSnapshot, const TBlobActionConditional &ACopyConditionals, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall SnapshotBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, /* out */ System::UnicodeString &SnapshotId, const System::UnicodeString LeaseId = System::UnicodeString(), System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall SnapshotBlob _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, const TBlobActionConditional &SnapshotConditionals, /* out */ System::UnicodeString &SnapshotId, const System::UnicodeString LeaseId = System::UnicodeString(), System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall SnapshotBlob(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, const TBlobActionConditional &ASnapshotConditionals, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, /* out */ System::UnicodeString &ASnapshotId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#ifndef _WIN64
	bool __fastcall PutBlock _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, const System::UnicodeString BlockId, System::DynamicArray<System::Byte> Content, const System::UnicodeString ContentMD5 = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutBlock(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, const System::UnicodeString ABlockId, System::DynamicArray<System::Byte> AContent, const System::UnicodeString AContentMD5, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall PutPage _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::DynamicArray<System::Byte> Content, int StartPage, int PageCount, const System::UnicodeString LeaseId = System::UnicodeString(), const System::UnicodeString ContentMD5 = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutPage _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::DynamicArray<System::Byte> Content, int StartPage, int PageCount, const TBlobActionConditional &ActionConditional, const System::UnicodeString ContentMD5 = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutPage _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::DynamicArray<System::Byte> Content, int StartPage, const TBlobActionConditional &ActionConditional, const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutPage _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::DynamicArray<System::Byte> Content, int StartPage, const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutPage(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, int AStartPage, System::DynamicArray<System::Byte> AContent, const System::UnicodeString AContentMD5, const TBlobActionConditional &AActionConditional, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	bool __fastcall PutBlock _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, const System::UnicodeString BlockId, System::TArray__1<System::Byte> Content, const System::UnicodeString ContentMD5 = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutBlock(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, const System::UnicodeString ABlockId, System::TArray__1<System::Byte> AContent, const System::UnicodeString AContentMD5, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall PutPage _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::TArray__1<System::Byte> Content, int StartPage, int PageCount, const System::UnicodeString LeaseId = System::UnicodeString(), const System::UnicodeString ContentMD5 = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutPage _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::TArray__1<System::Byte> Content, int StartPage, int PageCount, const TBlobActionConditional &ActionConditional, const System::UnicodeString ContentMD5 = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutPage _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::TArray__1<System::Byte> Content, int StartPage, const TBlobActionConditional &ActionConditional, const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutPage _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, System::TArray__1<System::Byte> Content, int StartPage, const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutPage(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, int AStartPage, System::TArray__1<System::Byte> AContent, const System::UnicodeString AContentMD5, const TBlobActionConditional &AActionConditional, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	bool __fastcall ClearPage _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, int StartPage, int PageCount, const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall ClearPage _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, int StartPage, int PageCount, const TBlobActionConditional &ActionConditional, const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall ClearPage(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseID, int AStartPage, int APageCount, const TBlobActionConditional &AActionConditional, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall PutBlockList(System::UnicodeString ContainerName, System::UnicodeString BlobName, System::Generics::Collections::TList__1<TAzureBlockListItem>* BlockList, System::Classes::TStrings* Properties = (System::Classes::TStrings*)(0x0), System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), const System::UnicodeString LeaseId = System::UnicodeString(), const System::UnicodeString ContentMD5 = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall PutBlockList(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, const System::UnicodeString AContentMD5, TAzureBlockListItem *ABlockList, const int ABlockList_High, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AProperties, const int AProperties_High, System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> *AMetadata, const int AMetadata_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	System::UnicodeString __fastcall GetBlockListXML _DEPRECATED_ATTRIBUTE1("Use GetBlckList method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, TAzureQueryIncludeBlockType BlockType = (TAzureQueryIncludeBlockType)(0x0), const System::UnicodeString SnapShot = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::Generics::Collections::TList__1<TAzureBlockListItem>* __fastcall GetBlockList _DEPRECATED_ATTRIBUTE1("Use overloaded method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, TAzureQueryIncludeBlockType BlockType = (TAzureQueryIncludeBlockType)(0x0), const System::UnicodeString SnapShot = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#ifndef _WIN64
	System::DynamicArray<TAzureBlockListItem> __fastcall GetBlockList(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, const System::UnicodeString ASnapshot, TAzureQueryIncludeBlockType ABlockType, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#else /* _WIN64 */
	System::TArray__1<TAzureBlockListItem> __fastcall GetBlockList(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, const System::UnicodeString ASnapshot, TAzureQueryIncludeBlockType ABlockType, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
#endif /* _WIN64 */
	System::UnicodeString __fastcall GetPageRegionsXML _DEPRECATED_ATTRIBUTE1("Use GetPageRanges method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, __int64 StartByte, __int64 EndByte, const System::UnicodeString Snapshot = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::UnicodeString __fastcall GetPageRegionsXML _DEPRECATED_ATTRIBUTE1("Use GetPageRanges method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, const System::UnicodeString Snapshot = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::Generics::Collections::TList__1<TAzureBlobPageRange>* __fastcall GetPageRegions _DEPRECATED_ATTRIBUTE1("Use GetPageRanges method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, __int64 StartByte, __int64 EndByte, const System::UnicodeString Snapshot = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::Generics::Collections::TList__1<TAzureBlobPageRange>* __fastcall GetPageRegions _DEPRECATED_ATTRIBUTE1("Use GetPageRanges method instead") (System::UnicodeString ContainerName, System::UnicodeString BlobName, const System::UnicodeString Snapshot = System::UnicodeString(), const System::UnicodeString LeaseId = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
#ifndef _WIN64
	System::DynamicArray<TAzureBlobPageRange> __fastcall GetPageRanges(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, __int64 AStartByte, __int64 AEndByte, const System::UnicodeString ASnapshot, const System::UnicodeString APrevSnapshot, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall AppendBlock(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, System::DynamicArray<System::Byte> AContent, const System::UnicodeString AContentMD5, const System::UnicodeString ALeaseId, const System::UnicodeString AClientRequestID, int AMaxSize, int AAppendPos, const TBlobActionConditional &AActionConditional, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#else /* _WIN64 */
	System::TArray__1<TAzureBlobPageRange> __fastcall GetPageRanges(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, const System::UnicodeString ALeaseId, __int64 AStartByte, __int64 AEndByte, const System::UnicodeString ASnapshot, const System::UnicodeString APrevSnapshot, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall AppendBlock(const System::UnicodeString AContainerName, const System::UnicodeString ABlobName, System::TArray__1<System::Byte> AContent, const System::UnicodeString AContentMD5, const System::UnicodeString ALeaseId, const System::UnicodeString AClientRequestID, int AMaxSize, int AAppendPos, const TBlobActionConditional &AActionConditional, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
#endif /* _WIN64 */
public:
	/* TAzureService.Create */ inline __fastcall TAzureBlobService(TAzureConnectionInfo* ConnectionInfo) : TAzureService(ConnectionInfo) { }
	/* TAzureService.Destroy */ inline __fastcall virtual ~TAzureBlobService() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define ROOT_CONTAINER L"$root"
}	/* namespace Azureapi */
}	/* namespace Cloud */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_CLOUD_AZUREAPI)
using namespace Data::Cloud::Azureapi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_CLOUD)
using namespace Data::Cloud;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_Cloud_AzureapiHPP
