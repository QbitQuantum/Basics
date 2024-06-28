// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Cloud.AmazonAPI.pas' rev: 34.00 (Android)

#ifndef Data_Cloud_AmazonapiHPP
#define Data_Cloud_AmazonapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <Data.Cloud.CloudAPI.hpp>
#include <Data.Cloud.AmazonAPI.LifeCycle.hpp>
#include <Xml.XMLIntf.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Cloud
{
namespace Amazonapi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAmazonAuthentication;
class DELPHICLASS TAmazonAWS4Authentication;
class DELPHICLASS TAmazonSHA1Authentication;
class DELPHICLASS TAmazonConnectionInfo;
class DELPHICLASS TAmazonService;
struct TAmazonQueuePermission;
class DELPHICLASS TAmazonBasicService;
struct TAmazonBatchRow;
struct TAmazonRowConditional;
class DELPHICLASS TAmazonTableService;
class DELPHICLASS TAmazonQueueService;
struct TAmazonObjectResult;
class DELPHICLASS TAmazonBucketResult;
struct TAmazonGrant;
class DELPHICLASS TAmazonBucketLoggingInfo;
struct TAmazonNotificationEvent;
struct TAmazonMultipartUploadItem;
class DELPHICLASS TAmazonMultipartUploadsResult;
class DELPHICLASS TAmazonAccessControlPolicy;
struct TAmazonActionConditional;
struct TAmazonGetObjectOptionals;
class DELPHICLASS TAmazonCopyObjectOptionals;
class DELPHICLASS TAmazonCopyObjectOptionalsExt;
struct TAmazonMultipartPart;
class DELPHICLASS TAmazonListPartsResult;
class DELPHICLASS TAmazonStorageService;
struct TAmazonStorageServiceHelper /* Helper for class 'TAmazonStorageService*' */;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TAmazonACLType : unsigned char { amzbaNotSpecified, amzbaPrivate, amzbaPublicRead, amzbaPublicReadWrite, amzbaAuthenticatedRead, amzbaBucketOwnerRead, amzbaBucketOwnerFullControl, amzbaAWSExecRead, amzbaLogDeliveryWrite };

typedef System::UnicodeString TAmazonRegion;

enum DECLSPEC_DENUM TAmazonGrantPermission : unsigned char { amgpFullControl, amgpWrite, amgpWriteACP, amgpRead, amgpReadACP, amgpUnknown };

enum DECLSPEC_DENUM TAmazonGranteeType : unsigned char { agtCanonicalUser, agtCustomerByEmail, agtGroup, agtUnknown };

enum DECLSPEC_DENUM TAmazonPayer : unsigned char { ampRequester, ampBucketOwner, ampUnknown };

enum DECLSPEC_DENUM TAmazonQueueAttribute : unsigned char { aqaAll, aqaApproximateNumberOfMessages, aqaApproximateNumberOfMessagesNotVisible, aqaVisibilityTimeout, aqaCreatedTimestamp, aqaLastModifiedTimestamp, aqaPolicy, aqaMaximumMessageSize, aqaMessageRetentionPeriod, aqaQueueArn, aqaApproximateNumberOfMessagesDelayed, aqaDelaySeconds, aqaReceiveMessageWaitTimeSeconds, aqaRedrivePolicy };

enum DECLSPEC_DENUM TAmazonQueueActions : unsigned char { aqacAll, aqacSendMessage, aqacReceiveMessage, aqacDeleteMessage, aqacChangeMessageVisibility, aqacGetQueueAttributes };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonAuthentication : public Data::Cloud::Cloudapi::TCloudSHA256Authentication
{
	typedef Data::Cloud::Cloudapi::TCloudSHA256Authentication inherited;
	
public:
	#define TAmazonAuthentication_AuthorizationType u"AWS"
	
	
protected:
	bool FAuthInHeader;
	
public:
	__fastcall TAmazonAuthentication(Data::Cloud::Cloudapi::TCloudConnectionInfo* const ConnectionInfo, bool AuthInHeader)/* overload */;
	virtual System::UnicodeString __fastcall BuildAuthorizationString(const System::UnicodeString StringToSign);
public:
	/* TCloudSHA256Authentication.Create */ inline __fastcall TAmazonAuthentication(Data::Cloud::Cloudapi::TCloudConnectionInfo* const ConnectionInfo, System::UnicodeString AuthorizationType)/* overload */ : Data::Cloud::Cloudapi::TCloudSHA256Authentication(ConnectionInfo, AuthorizationType) { }
	
public:
	/* TCloudAuthentication.Destroy */ inline __fastcall virtual ~TAmazonAuthentication() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonAWS4Authentication : public Data::Cloud::Cloudapi::TCloudSHA256Authentication
{
	typedef Data::Cloud::Cloudapi::TCloudSHA256Authentication inherited;
	
public:
	#define TAmazonAWS4Authentication_AuthorizationType u"AWS4-HMAC-SHA256"
	
	
protected:
	bool FAuthInHeader;
	virtual void __fastcall AssignKey(const System::UnicodeString AccountKey);
	
public:
	__fastcall TAmazonAWS4Authentication(Data::Cloud::Cloudapi::TCloudConnectionInfo* const ConnectionInfo, bool AuthInHeader)/* overload */;
	HIDESBASE System::UnicodeString __fastcall BuildAuthorizationString(const System::UnicodeString StringToSign, const System::UnicodeString DateISO, const System::UnicodeString Region, const System::UnicodeString SignedStrHeaders)/* overload */;
	HIDESBASE System::UnicodeString __fastcall BuildAuthorizationString(const System::UnicodeString StringToSign, const System::UnicodeString DateISO, const System::UnicodeString Region, const System::UnicodeString ServiceName, const System::UnicodeString SignedStrHeaders)/* overload */;
public:
	/* TCloudSHA256Authentication.Create */ inline __fastcall TAmazonAWS4Authentication(Data::Cloud::Cloudapi::TCloudConnectionInfo* const ConnectionInfo, System::UnicodeString AuthorizationType)/* overload */ : Data::Cloud::Cloudapi::TCloudSHA256Authentication(ConnectionInfo, AuthorizationType) { }
	
public:
	/* TCloudAuthentication.Destroy */ inline __fastcall virtual ~TAmazonAWS4Authentication() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonSHA1Authentication : public Data::Cloud::Cloudapi::TCloudSHA1Authentication
{
	typedef Data::Cloud::Cloudapi::TCloudSHA1Authentication inherited;
	
public:
	#define TAmazonSHA1Authentication_AuthorizationType u"AWS"
	
	__fastcall TAmazonSHA1Authentication(Data::Cloud::Cloudapi::TCloudConnectionInfo* const ConnectionInfo)/* overload */;
public:
	/* TCloudSHA1Authentication.Create */ inline __fastcall TAmazonSHA1Authentication(Data::Cloud::Cloudapi::TCloudConnectionInfo* ConnectionInfo, System::UnicodeString AuthorizationType)/* overload */ : Data::Cloud::Cloudapi::TCloudSHA1Authentication(ConnectionInfo, AuthorizationType) { }
	
public:
	/* TCloudAuthentication.Destroy */ inline __fastcall virtual ~TAmazonSHA1Authentication() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonConnectionInfo : public Data::Cloud::Cloudapi::TCloudConnectionInfo
{
	typedef Data::Cloud::Cloudapi::TCloudConnectionInfo inherited;
	
	
private:
	__interface DELPHIINTERFACE TGetRegion;
	typedef System::DelphiInterface<TGetRegion> _di_TGetRegion;
	__interface TGetRegion  : public System::IInterface 
	{
		virtual System::UnicodeString __fastcall Invoke(const System::UnicodeString ABucket) = 0 ;
	};
	
	
public:
	#define TAmazonConnectionInfo_DefaultStorageEndpoint u"s3.amazonaws.com"
	
	#define TAmazonConnectionInfo_DefaultTableEndpoint u"sdb.amazonaws.com"
	
	#define TAmazonConnectionInfo_DefaultQueueEndpoint u"sqs.amazonaws.com"
	
	#define TAmazonConnectionInfo_RegionStorageEndpoint u"s3.%s.amazonaws.com"
	
	#define TAmazonConnectionInfo_RegionTableEndpoint u"sdb.%s.amazonaws.com"
	
	#define TAmazonConnectionInfo_RegionQueueEndpoint u"sqs.%s.amazonaws.com"
	
	#define TAmazonConnectionInfo_DefaultRegion u"us-east-1"
	
	
private:
	bool FConsistentRead;
	System::UnicodeString FMFASerialNumber;
	System::UnicodeString FMFAAuthCode;
	System::UnicodeString FStorageEndpoint;
	System::UnicodeString FTableEndpoint;
	System::UnicodeString FQueueEndpoint;
	System::UnicodeString FRegion;
	bool FAutoDetectBucketRegion;
	_di_TGetRegion FGetRegion;
	System::UnicodeString __fastcall ResolveRegion(const System::UnicodeString ARegion, bool AUseDefault);
	System::UnicodeString __fastcall GetServiceURL(const System::UnicodeString AHost)/* overload */;
	System::UnicodeString __fastcall GetServiceURL(const System::UnicodeString AHost, const System::UnicodeString ARegionHost, const System::UnicodeString ARegion)/* overload */;
	System::UnicodeString __fastcall GetQueueURL();
	System::UnicodeString __fastcall GetTableURL();
	System::UnicodeString __fastcall GetQueueEndpoint();
	System::UnicodeString __fastcall GetTableEndpoint();
	System::UnicodeString __fastcall GetStorageEndpoint();
	void __fastcall SetStorageEndpoint(const System::UnicodeString AValue);
	void __fastcall SetQueueEndpoint(const System::UnicodeString AValue);
	void __fastcall SetTableEndpoint(const System::UnicodeString AValue);
	void __fastcall SetRegion(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetRegion();
	System::UnicodeString __fastcall GetVirtualHost(const System::UnicodeString AHost, const System::UnicodeString ARegionHost, const System::UnicodeString ARegion);
	bool __fastcall IsRegionStored();
	
public:
	__fastcall virtual TAmazonConnectionInfo(System::Classes::TComponent* AOwner);
	__property System::UnicodeString QueueURL = {read=GetQueueURL};
	__property System::UnicodeString TableURL = {read=GetTableURL};
	System::UnicodeString __fastcall StorageURL(const System::UnicodeString ABucketName = System::UnicodeString(), const System::UnicodeString ARegion = System::UnicodeString());
	System::UnicodeString __fastcall StorageVirtualHost(const System::UnicodeString ABucketName = System::UnicodeString(), const System::UnicodeString ARegion = System::UnicodeString());
	static System::UnicodeString __fastcall GetRegionString _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString Region);
	static System::UnicodeString __fastcall GetRegionFromString _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString Region);
	
__published:
	__property AccountName = {default=0};
	__property AccountKey = {default=0};
	__property Protocol = {default=0};
	__property RequestProxyHost = {default=0};
	__property RequestProxyPort = {default=0};
	__property bool ConsistentRead = {read=FConsistentRead, write=FConsistentRead, default=1};
	__property System::UnicodeString MFASerialNumber = {read=FMFASerialNumber, write=FMFASerialNumber};
	__property System::UnicodeString MFAAuthCode = {read=FMFAAuthCode, write=FMFAAuthCode};
	__property System::UnicodeString TableEndpoint = {read=GetTableEndpoint, write=SetTableEndpoint};
	__property System::UnicodeString QueueEndpoint = {read=GetQueueEndpoint, write=SetQueueEndpoint};
	__property System::UnicodeString StorageEndpoint = {read=GetStorageEndpoint, write=SetStorageEndpoint};
	__property System::UnicodeString Region = {read=GetRegion, write=SetRegion, stored=IsRegionStored};
	__property bool AutoDetectBucketRegion = {read=FAutoDetectBucketRegion, write=FAutoDetectBucketRegion, default=0};
	__property UseDefaultEndpoints = {default=1};
public:
	/* TCloudConnectionInfo.Destroy */ inline __fastcall virtual ~TAmazonConnectionInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonService : public Data::Cloud::Cloudapi::TCloudService
{
	typedef Data::Cloud::Cloudapi::TCloudService inherited;
	
protected:
	virtual System::UnicodeString __fastcall URLEncodeValue(const System::UnicodeString Value);
	TAmazonConnectionInfo* __fastcall GetConnectionInfo();
	virtual System::Classes::TStrings* __fastcall GetRequiredHeaderNames(/* out */ bool &InstanceOwner);
	virtual System::UnicodeString __fastcall GetCanonicalizedHeaderPrefix();
	virtual System::UnicodeString __fastcall CurrentTime();
	virtual Data::Cloud::Cloudapi::TCloudAuthentication* __fastcall CreateAuthInstance(TAmazonConnectionInfo* const ConnectionInfo) = 0 ;
	virtual void __fastcall SortHeaders(System::Classes::TStringList* const Headers);
	System::UnicodeString __fastcall ISODateTime_noSeparators();
	virtual void __fastcall ParseResponseError(Data::Cloud::Cloudapi::TCloudResponseInfo* const ResponseInfo, const System::UnicodeString ResultString) = 0 ;
	
public:
	__fastcall TAmazonService(TAmazonConnectionInfo* const ConnectionInfo);
	__fastcall virtual ~TAmazonService();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TAmazonQueuePermission
{
public:
	System::UnicodeString AccountId;
	TAmazonQueueActions Action;
	static TAmazonQueuePermission __fastcall Create(const System::UnicodeString AccountId, TAmazonQueueActions Action = (TAmazonQueueActions)(0x0));
	System::UnicodeString __fastcall GetAction();
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonBasicService : public TAmazonService
{
	typedef TAmazonService inherited;
	
protected:
	virtual Data::Cloud::Cloudapi::TCloudAuthentication* __fastcall CreateAuthInstance(TAmazonConnectionInfo* const ConnectionInfo);
	virtual void __fastcall PrepareRequestSignature(const System::UnicodeString HTTPVerb, System::Classes::TStringList* const Headers, System::Classes::TStringList* const QueryParameters, const System::UnicodeString StringToSign, System::UnicodeString &URL, Data::Cloud::Cloudapi::TCloudHTTP* Request, System::Classes::TStream* &Content);
	virtual System::UnicodeString __fastcall BuildStringToSignResourcePath(const System::UnicodeString URL);
	System::Classes::TStringList* __fastcall BuildQueryParameters(const System::UnicodeString Action);
	virtual void __fastcall SortQueryParameters(System::Classes::TStringList* const QueryParameters, bool ForURL);
	Data::Cloud::Cloudapi::TCloudHTTP* __fastcall IssueRequest(const System::UnicodeString URL, System::Classes::TStringList* QueryParams, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo, /* out */ System::UnicodeString &ResultString, System::Classes::TStream* RequestStream = (System::Classes::TStream*)(0x0))/* overload */;
	Data::Cloud::Cloudapi::TCloudHTTP* __fastcall IssueRequest(System::UnicodeString URL, System::Classes::TStringList* QueryParams, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo, System::Classes::TStream* RequestStream = (System::Classes::TStream*)(0x0))/* overload */;
	virtual void __fastcall ParseResponseError(Data::Cloud::Cloudapi::TCloudResponseInfo* const ResponseInfo, const System::UnicodeString ResultString);
	virtual System::UnicodeString __fastcall GetServiceVersion() = 0 ;
	virtual System::UnicodeString __fastcall GetServiceHost() = 0 ;
public:
	/* TAmazonService.Create */ inline __fastcall TAmazonBasicService(TAmazonConnectionInfo* const ConnectionInfo) : TAmazonService(ConnectionInfo) { }
	/* TAmazonService.Destroy */ inline __fastcall virtual ~TAmazonBasicService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TAmazonBatchRow
{
public:
	System::UnicodeString RowId;
	Data::Cloud::Cloudapi::TCloudTableRow* Row;
	bool ReplaceAll;
	static TAmazonBatchRow __fastcall Create(const System::UnicodeString RowId, Data::Cloud::Cloudapi::TCloudTableRow* Row, bool ReplaceAll = true);
};


struct DECLSPEC_DRECORD TAmazonRowConditional
{
public:
	System::UnicodeString ColumnName;
	System::UnicodeString ColumnValue;
	bool ColumnExists;
	static TAmazonRowConditional __fastcall Create(const System::UnicodeString ColumnName, const System::UnicodeString ColumnValue, const bool ColumnExists = true);
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonTableService : public TAmazonBasicService
{
	typedef TAmazonBasicService inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetServiceVersion();
	virtual System::UnicodeString __fastcall GetServiceHost();
	
public:
	bool __fastcall CreateTable(const System::UnicodeString TableName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall DeleteTable(const System::UnicodeString TableName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::UnicodeString __fastcall QueryTablesXML(const System::UnicodeString ContinuationToken = System::UnicodeString(), const int MaxNumberOfTables = 0x0, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::Classes::TStrings* __fastcall QueryTables(const System::UnicodeString ContinuationToken = System::UnicodeString(), const int MaxNumberOfTables = 0x0, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::UnicodeString __fastcall GetTableMetadataXML(const System::UnicodeString TableName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::Classes::TStrings* __fastcall GetTableMetadata(const System::UnicodeString TableName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall InsertRow(const System::UnicodeString TableName, const System::UnicodeString RowId, Data::Cloud::Cloudapi::TCloudTableRow* Row, System::Generics::Collections::TList__1<TAmazonRowConditional>* Conditionals, bool ReplaceAll = true, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall InsertRows(const System::UnicodeString TableName, System::Generics::Collections::TList__1<TAmazonBatchRow>* Rows, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::UnicodeString __fastcall SelectRowsXML(const System::UnicodeString SelectStatement, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString NextToken = System::UnicodeString());
	System::UnicodeString __fastcall GetRowsXML(const System::UnicodeString TableName, int MaxNumberOfItems = 0x0, bool ItemIdOnly = false, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString NextToken = System::UnicodeString());
	System::Generics::Collections::TList__1<Data::Cloud::Cloudapi::TCloudTableRow*>* __fastcall GetRows(const System::UnicodeString TableName, int MaxNumberOfItems = 0x0, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString NextToken = System::UnicodeString());
	System::Classes::TStrings* __fastcall GetRowIDs(const System::UnicodeString TableName, int MaxNumberOfItems = 0x0, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString NextToken = System::UnicodeString());
	bool __fastcall DeleteColumns(const System::UnicodeString TableName, const System::UnicodeString RowId, System::Classes::TStrings* const Columns, System::Generics::Collections::TList__1<TAmazonRowConditional>* Conditionals, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall DeleteColumns(const System::UnicodeString TableName, const System::UnicodeString RowId, System::Classes::TStrings* const Columns, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall DeleteRow(const System::UnicodeString TableName, const System::UnicodeString RowId, System::Generics::Collections::TList__1<TAmazonRowConditional>* Conditionals, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall DeleteRow(const System::UnicodeString TableName, const System::UnicodeString RowId, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall BatchDeleteColumns(const System::UnicodeString TableName, System::Generics::Collections::TList__1<Data::Cloud::Cloudapi::TCloudTableRow*>* BatchColumns, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
public:
	/* TAmazonService.Create */ inline __fastcall TAmazonTableService(TAmazonConnectionInfo* const ConnectionInfo) : TAmazonBasicService(ConnectionInfo) { }
	/* TAmazonService.Destroy */ inline __fastcall virtual ~TAmazonTableService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonQueueService : public TAmazonBasicService
{
	typedef TAmazonBasicService inherited;
	
	
public:
	typedef System::Generics::Collections::TPair__2<TAmazonQueueAttribute,System::UnicodeString> TQueueAttributePair;
	
	typedef System::TArray__1<System::Generics::Collections::TPair__2<TAmazonQueueAttribute,System::UnicodeString> > TQueueAttributePairs;
	
	
private:
	bool __fastcall IsUniqueMessageId(const System::UnicodeString AMessageId, const Data::Cloud::Cloudapi::TCloudQueueMessageItem *AMessageList, const int AMessageList_High);
	System::UnicodeString __fastcall ReceiveMessageXML(const System::UnicodeString AQueueURL, int ANumOfMessages, int AVisibilityTimeout, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::UnicodeString __fastcall GetQueueAttributesXML(const System::UnicodeString AQueueURL, TAmazonQueueAttribute *AAttributes, const int AAttributes_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	
protected:
	virtual System::UnicodeString __fastcall GetServiceVersion();
	System::UnicodeString __fastcall GetQueueAttributeName(const TAmazonQueueAttribute Attribute);
	TAmazonQueueAttribute __fastcall GetQueueAttributeFromName(const System::UnicodeString AAttributeName);
	virtual System::UnicodeString __fastcall GetServiceHost();
	
public:
	int __fastcall GetMaxMessageReturnCount();
	System::UnicodeString __fastcall ListQueuesXML(System::Classes::TStrings* OptionalParams = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::Generics::Collections::TList__1<Data::Cloud::Cloudapi::TCloudQueue>* __fastcall ListQueues(System::Classes::TStrings* OptionalParams = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall CreateQueue(const System::UnicodeString QueueName, const int DefaultVisibilityTimeout = 0xffffffff, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall CreateQueue(const System::UnicodeString QueueName, /* out */ System::UnicodeString &QueueURL, const int DefaultVisibilityTimeout = 0xffffffff, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall CreateQueue(const System::UnicodeString QueueName, /* out */ System::UnicodeString &QueueURL, System::Generics::Collections::TPair__2<TAmazonQueueAttribute,System::UnicodeString> *Attributes, const int Attributes_High, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall DeleteQueue(const System::UnicodeString QueueURL, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::UnicodeString __fastcall GetQueuePropertiesXML _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, TAmazonQueueAttribute Attribute = (TAmazonQueueAttribute)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::UnicodeString __fastcall GetQueuePropertiesXML _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, TAmazonQueueAttribute *Attributes, const int Attributes_High, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::Classes::TStrings* __fastcall GetQueueProperties _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, TAmazonQueueAttribute Attribute = (TAmazonQueueAttribute)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::Classes::TStrings* __fastcall GetQueueProperties _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, TAmazonQueueAttribute *Attributes, const int Attributes_High, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	System::TArray__1<System::Generics::Collections::TPair__2<TAmazonQueueAttribute,System::UnicodeString> > __fastcall GetQueueAttributes(const System::UnicodeString AQueueURL, TAmazonQueueAttribute *AAttributes, const int AAttributes_High, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall SetQueueProperty _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, const System::UnicodeString Key, const System::UnicodeString Value, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall SetQueueAttributes(const System::UnicodeString AQueueURL, System::Generics::Collections::TPair__2<TAmazonQueueAttribute,System::UnicodeString> *AAttributes, const int AAttributes_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall AddQueuePermissions _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, const System::UnicodeString PermissionsLabel, TAmazonQueuePermission *Permissions, const int Permissions_High, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall AddPermission(const System::UnicodeString AQueueURL, const System::UnicodeString APermissionsLabel, TAmazonQueuePermission *APermissions, const int APermissions_High, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall RemoveQueuePermissions _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, const System::UnicodeString PermissionsLabel, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall RemovePermission(const System::UnicodeString AQueueURL, const System::UnicodeString APermissionsLabel, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall PurgeQueue(const System::UnicodeString AQueueURL, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall AddMessage _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, const System::UnicodeString MessageText, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall AddMessage _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, const System::UnicodeString MessageText, /* out */ System::UnicodeString &MessageId, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0))/* overload */;
	bool __fastcall SendMessage(const System::UnicodeString AQueueURL, const System::UnicodeString AMessageText, /* out */ System::UnicodeString &AMessageId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	bool __fastcall SendMessage(const System::UnicodeString AQueueURL, const System::UnicodeString AMessageText, const System::UnicodeString AMessageGroupId, /* out */ System::UnicodeString &AMessageId, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo)/* overload */;
	System::TArray__1<System::UnicodeString> __fastcall SendMessageBatch(const System::UnicodeString AQueueURL, System::TArray__1<System::UnicodeString> AMessageList, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::UnicodeString __fastcall GetMessagesXML _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, int NumOfMessages = 0x0, int VisibilityTimeout = 0xffffffff, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::Generics::Collections::TList__1<Data::Cloud::Cloudapi::TCloudQueueMessage*>* __fastcall GetMessages _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, int NumOfMessages = 0x0, int VisibilityTimeout = 0xffffffff, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::TArray__1<Data::Cloud::Cloudapi::TCloudQueueMessageItem> __fastcall ReceiveMessage(const System::UnicodeString AQueueURL, int ANumOfMessages, int AVisibilityTimeout, /* out */ System::UnicodeString &AResponseXML, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::Generics::Collections::TList__1<Data::Cloud::Cloudapi::TCloudQueueMessage*>* __fastcall PeekMessages _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString QueueURL, int NumOfMessages, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall DeleteMessage(const System::UnicodeString QueueURL, const System::UnicodeString PopReceipt, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall DeleteMessageBatch(const System::UnicodeString AQueueURL, const System::TArray__1<System::UnicodeString> APopReceiptList, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	bool __fastcall ChangeMessageVisibility(const System::UnicodeString QueueURL, const System::UnicodeString PopReceipt, const int VisibilityTimeout = 0x0, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall ChangeMessageVisibilityBatch(const System::UnicodeString AQueueURL, System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,int> > AMessageInfoList, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
	System::TArray__1<System::UnicodeString> __fastcall ListDeadLetterSourceQueues(const System::UnicodeString AQueueURL, Data::Cloud::Cloudapi::TCloudResponseInfo* const AResponseInfo);
public:
	/* TAmazonService.Create */ inline __fastcall TAmazonQueueService(TAmazonConnectionInfo* const ConnectionInfo) : TAmazonBasicService(ConnectionInfo) { }
	/* TAmazonService.Destroy */ inline __fastcall virtual ~TAmazonQueueService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TAmazonObjectResult
{
public:
	System::UnicodeString Name;
	System::UnicodeString LastModified;
	System::UnicodeString ETag;
	__int64 Size;
	System::UnicodeString OwnerID;
	System::UnicodeString OwnerDisplayName;
	System::UnicodeString VersionId;
	bool IsLatest;
	bool IsDeleted;
	System::UnicodeString StorageClass;
	static TAmazonObjectResult __fastcall Create(const System::UnicodeString Name);
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonBucketResult : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FName;
	bool FIsTruncated;
	System::Generics::Collections::TList__1<TAmazonObjectResult>* FObjects;
	System::Classes::TStrings* FPrefixes;
	System::UnicodeString FMarker;
	System::UnicodeString FVersionIdMarker;
	System::UnicodeString FRequestPrefix;
	System::UnicodeString FRequestDelimiter;
	int FRequestMaxKeys;
	
public:
	__fastcall virtual TAmazonBucketResult(const System::UnicodeString AName);
	__fastcall virtual ~TAmazonBucketResult();
	__property System::UnicodeString Name = {read=FName};
	__property bool IsTruncated = {read=FIsTruncated, write=FIsTruncated, nodefault};
	__property System::Generics::Collections::TList__1<TAmazonObjectResult>* Objects = {read=FObjects};
	__property System::Classes::TStrings* Prefixes = {read=FPrefixes};
	__property System::UnicodeString Marker = {read=FMarker, write=FMarker};
	__property System::UnicodeString VersionIdMarker = {read=FVersionIdMarker, write=FVersionIdMarker};
	__property System::UnicodeString RequestPrefix = {read=FRequestPrefix, write=FRequestPrefix};
	__property System::UnicodeString RequestDelimiter = {read=FRequestDelimiter, write=FRequestDelimiter};
	__property int RequestMaxKeys = {read=FRequestMaxKeys, write=FRequestMaxKeys, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TAmazonGrant
{
public:
	System::UnicodeString GranteeURI;
	System::UnicodeString GranteeID;
	System::UnicodeString GranteeDisplayName;
	System::UnicodeString GranteeEmailAddress;
	TAmazonGrantPermission Permission;
	static TAmazonGrantPermission __fastcall GetPermission(const System::UnicodeString PermissionString);
	static TAmazonGrant __fastcall Create(const System::UnicodeString Permission)/* overload */;
	static TAmazonGrant __fastcall Create(TAmazonGrantPermission Permission)/* overload */;
	System::UnicodeString __fastcall PermissionString();
	bool __fastcall IsAllUsers();
	bool __fastcall IsAllAuthenticatedUsers();
	bool __fastcall IsLogDelivery();
	TAmazonGranteeType __fastcall GranteeType();
	System::UnicodeString __fastcall GranteeTypeString();
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonBucketLoggingInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TAmazonBucketLoggingInfo_LogXMLPrefix u"<?xml version=\"1.0\"?><BucketLoggingStatus xmlns=\"http:/"\
		u"/doc.s3.amazonaws.com/2006-03-01\">"
	
	#define TAmazonBucketLoggingInfo_LogXMLSuffix u"</BucketLoggingStatus>"
	
	
private:
	System::UnicodeString FTargetBucket;
	System::UnicodeString FTargetPrefix;
	bool FLoggingEnabled;
	System::Generics::Collections::TList__1<TAmazonGrant>* FGrants;
	
public:
	__fastcall virtual TAmazonBucketLoggingInfo(const System::UnicodeString TargetBucket, const System::UnicodeString TargetPrefix)/* overload */;
	__fastcall virtual TAmazonBucketLoggingInfo()/* overload */;
	__fastcall virtual ~TAmazonBucketLoggingInfo();
	System::UnicodeString __fastcall AsXML();
	__classmethod System::UnicodeString __fastcall GetDisableXML();
	__property System::UnicodeString Targetbucket = {read=FTargetBucket};
	__property System::UnicodeString TargetPrefix = {read=FTargetPrefix};
	__property System::Generics::Collections::TList__1<TAmazonGrant>* Grants = {read=FGrants};
	__property bool IsLoggingEnabled = {read=FLoggingEnabled, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TAmazonNotificationEvent
{
public:
	System::UnicodeString Topic;
	System::UnicodeString Event;
	static TAmazonNotificationEvent __fastcall Create(const System::UnicodeString Topic, const System::UnicodeString Event);
};


struct DECLSPEC_DRECORD TAmazonMultipartUploadItem
{
public:
	System::UnicodeString Key;
	System::UnicodeString UploadId;
	System::UnicodeString InitiatorId;
	System::UnicodeString InitiatorDisplayName;
	System::UnicodeString OwnerId;
	System::UnicodeString OwnerDisplayName;
	bool IsReducedRedundancyStorage;
	System::UnicodeString DateInitiated;
	__fastcall TAmazonMultipartUploadItem(const System::UnicodeString AKey);
	TAmazonMultipartUploadItem() {}
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonMultipartUploadsResult : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FBucket;
	System::UnicodeString FKeyMarker;
	System::UnicodeString FUploadIdMarker;
	System::UnicodeString FNextKeyMarker;
	System::UnicodeString FNextUploadIdMarker;
	int FMaxUploads;
	bool FIsTruncated;
	System::Generics::Collections::TList__1<TAmazonMultipartUploadItem>* FUploadItems;
	
public:
	__fastcall virtual TAmazonMultipartUploadsResult(const System::UnicodeString BucketName);
	__fastcall virtual ~TAmazonMultipartUploadsResult();
	__property System::UnicodeString Bucket = {read=FBucket};
	__property System::UnicodeString KeyMarker = {read=FKeyMarker, write=FKeyMarker};
	__property System::UnicodeString UploadIdMarker = {read=FUploadIdMarker, write=FUploadIdMarker};
	__property System::UnicodeString NextKeyMarker = {read=FNextKeyMarker, write=FNextKeyMarker};
	__property System::UnicodeString NextUploadIdMarker = {read=FNextUploadIdMarker, write=FNextUploadIdMarker};
	__property int MaxUploads = {read=FMaxUploads, write=FMaxUploads, nodefault};
	__property bool IsTruncated = {read=FIsTruncated, write=FIsTruncated, nodefault};
	__property System::Generics::Collections::TList__1<TAmazonMultipartUploadItem>* UploadItems = {read=FUploadItems};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonAccessControlPolicy : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FOwnerId;
	System::UnicodeString FOwnerDisplayName;
	System::Generics::Collections::TList__1<TAmazonGrant>* FGrants;
	
public:
	__fastcall virtual TAmazonAccessControlPolicy(const System::UnicodeString OwnerId, const System::UnicodeString OwnerDisplayName, System::Generics::Collections::TList__1<TAmazonGrant>* Grants);
	__fastcall virtual ~TAmazonAccessControlPolicy();
	System::UnicodeString __fastcall AsXML();
	__property System::UnicodeString OwnerId = {read=FOwnerId};
	__property System::UnicodeString OwnerDisplayName = {read=FOwnerDisplayName};
	__property System::Generics::Collections::TList__1<TAmazonGrant>* Grants = {read=FGrants};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TAmazonActionConditional
{
public:
	System::UnicodeString IfModifiedSince;
	System::UnicodeString IfUnmodifiedSince;
	System::UnicodeString IfMatch;
	System::UnicodeString IfNoneMatch;
	static TAmazonActionConditional __fastcall Create();
	void __fastcall PopulateHeaders(System::Classes::TStrings* Headers, bool ForCopy = false);
};


struct DECLSPEC_DRECORD TAmazonGetObjectOptionals
{
public:
	System::UnicodeString ResponseContentType;
	System::UnicodeString ResponseContentLanguage;
	System::UnicodeString ResponseExpires;
	System::UnicodeString ResponseCacheControl;
	System::UnicodeString ResponseContentDisposition;
	System::UnicodeString ResponseContentEncoding;
	TAmazonActionConditional Condition;
	__int64 RangeStartByte;
	__int64 RangeEndByte;
	static TAmazonGetObjectOptionals __fastcall Create();
	void __fastcall PopulateHeaders(System::Classes::TStrings* Headers);
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonCopyObjectOptionals : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	bool FCopyMetadata;
	System::Classes::TStrings* FMetadata;
	TAmazonACLType FACL;
	bool FUseReducedRedundancy;
	
public:
	TAmazonActionConditional Condition;
	__fastcall virtual TAmazonCopyObjectOptionals();
	__fastcall virtual ~TAmazonCopyObjectOptionals();
	void __fastcall PopulateHeaders(System::Classes::TStrings* Headers);
	__property bool CopyMetadata = {read=FCopyMetadata, write=FCopyMetadata, nodefault};
	__property bool UseReducedRedundancy = {read=FUseReducedRedundancy, write=FUseReducedRedundancy, nodefault};
	__property TAmazonACLType ACL = {read=FACL, write=FACL, nodefault};
	__property System::Classes::TStrings* Metadata = {read=FMetadata};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonCopyObjectOptionalsExt : public TAmazonCopyObjectOptionals
{
	typedef TAmazonCopyObjectOptionals inherited;
	
private:
	System::Classes::TStrings* FProperties;
	
public:
	__fastcall virtual TAmazonCopyObjectOptionalsExt();
	__fastcall virtual ~TAmazonCopyObjectOptionalsExt();
	__property System::Classes::TStrings* Properties = {read=FProperties};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TAmazonMultipartPart
{
public:
	int PartNumber;
	System::UnicodeString ETag;
	System::UnicodeString LastModified;
	__int64 Size;
	__fastcall TAmazonMultipartPart(int APartNumber, System::UnicodeString AETag);
	System::UnicodeString __fastcall AsXML();
	TAmazonMultipartPart() {}
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonListPartsResult : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FBucket;
	System::UnicodeString FObjectName;
	System::UnicodeString FUploadId;
	System::UnicodeString FInitiatorId;
	System::UnicodeString FInitiatorDisplayName;
	System::UnicodeString FOwnerId;
	System::UnicodeString FOwnerDisplayName;
	bool FIsReducedRedundancyStorage;
	int FPartNumberMarker;
	int FNextPartNumberMarker;
	int FMaxParts;
	bool FIsTruncated;
	System::Generics::Collections::TList__1<TAmazonMultipartPart>* FParts;
	
public:
	__fastcall virtual TAmazonListPartsResult(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString UploadId);
	__fastcall virtual ~TAmazonListPartsResult();
	__property System::UnicodeString Bucket = {read=FBucket};
	__property System::UnicodeString ObjectName = {read=FObjectName};
	__property System::UnicodeString UploadId = {read=FUploadId, write=FUploadId};
	__property System::UnicodeString InitiatorId = {read=FInitiatorId, write=FInitiatorId};
	__property System::UnicodeString InitiatorDisplayName = {read=FInitiatorDisplayName, write=FInitiatorDisplayName};
	__property System::UnicodeString OwnerId = {read=FOwnerId, write=FOwnerId};
	__property System::UnicodeString OwnerDisplayName = {read=FOwnerDisplayName, write=FOwnerDisplayName};
	__property bool IsReducedRedundancyStorage = {read=FIsReducedRedundancyStorage, write=FIsReducedRedundancyStorage, nodefault};
	__property int PartNumberMarker = {read=FPartNumberMarker, write=FPartNumberMarker, nodefault};
	__property int NextPartNumberMarker = {read=FNextPartNumberMarker, write=FNextPartNumberMarker, nodefault};
	__property int MaxParts = {read=FMaxParts, write=FMaxParts, nodefault};
	__property bool IsTruncated = {read=FIsTruncated, write=FIsTruncated, nodefault};
	__property System::Generics::Collections::TList__1<TAmazonMultipartPart>* Parts = {read=FParts};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAmazonStorageService : public TAmazonService
{
	typedef TAmazonService inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FBucketRegionDict;
	System::Classes::TStringList* __fastcall InitHeaders(const System::UnicodeString BucketName, const System::UnicodeString BucketRegion);
	void __fastcall AddAndValidateHeaders(System::Classes::TStrings* const defaultHeaders, System::Classes::TStrings* const customHeaders);
	bool __fastcall PopulateResultItem(Xml::Xmlintf::_di_IXMLNode ObjectNode, /* out */ TAmazonObjectResult &ResultItem);
	void __fastcall PopulateGrants(Xml::Xmlintf::_di_IXMLNode GrantsNode, System::Generics::Collections::TList__1<TAmazonGrant>* Grants);
	TAmazonBucketResult* __fastcall GetBucketInternal(const System::UnicodeString XML, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo);
	System::UnicodeString __fastcall GetBucketXMLInternal(const System::UnicodeString BucketName, System::Classes::TStrings* OptionalParams, bool VersionInfo, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo, const System::UnicodeString BucketRegion);
	System::UnicodeString __fastcall GetNotificationXML(System::Generics::Collections::TList__1<TAmazonNotificationEvent>* Events);
	bool __fastcall DeleteObjectInternal(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString VersionId, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo, const System::UnicodeString BucketRegion);
	bool __fastcall GetObjectInternal(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString VersionId, const TAmazonGetObjectOptionals &OptionalParams, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo, System::Classes::TStream* ObjectStream, const System::UnicodeString BucketRegion);
	System::UnicodeString __fastcall GetRegionFromEndpoint(const System::UnicodeString Endpoint);
	System::UnicodeString __fastcall BuildObjectURL(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString ARegion);
	
protected:
	System::Classes::TStrings* FRequiredHeaderNames;
	virtual void __fastcall URLEncodeQueryParams(const bool ForURL, System::UnicodeString &ParamName, System::UnicodeString &ParamValue);
	virtual Data::Cloud::Cloudapi::TCloudAuthentication* __fastcall CreateAuthInstance(TAmazonConnectionInfo* const ConnectionInfo);
	virtual System::UnicodeString __fastcall BuildStringToSign(const System::UnicodeString HTTPVerb, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, const System::UnicodeString URL);
	virtual void __fastcall PrepareRequestSignature(const System::UnicodeString HTTPVerb, System::Classes::TStringList* const Headers, System::Classes::TStringList* const QueryParameters, const System::UnicodeString StringToSign, System::UnicodeString &URL, Data::Cloud::Cloudapi::TCloudHTTP* Request, System::Classes::TStream* &Content);
	virtual System::UnicodeString __fastcall BuildStringToSignHeaders(System::Classes::TStringList* Headers);
	virtual System::Classes::TStrings* __fastcall GetRequiredHeaderNames(/* out */ bool &InstanceOwner);
	virtual System::UnicodeString __fastcall GetCanonicalizedHeaderPrefix();
	virtual System::UnicodeString __fastcall CurrentTime();
	virtual void __fastcall ParseResponseError(Data::Cloud::Cloudapi::TCloudResponseInfo* const ResponseInfo, const System::UnicodeString ResultString);
	virtual void __fastcall SortHeaders(System::Classes::TStringList* const Headers);
	virtual System::UnicodeString __fastcall BuildQueryParameterString(const System::UnicodeString QueryPrefix, System::Classes::TStringList* QueryParameters, bool DoSort = false, bool ForURL = true);
	
public:
	__fastcall TAmazonStorageService(TAmazonConnectionInfo* const ConnectionInfo);
	__fastcall virtual ~TAmazonStorageService();
	static System::UnicodeString __fastcall GetRegionString _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString Region);
	static System::UnicodeString __fastcall GetRegionFromString _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString Region);
	System::UnicodeString __fastcall ListBucketsXML(Data::Cloud::Cloudapi::TCloudResponseInfo* const ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::Classes::TStrings* __fastcall ListBuckets(Data::Cloud::Cloudapi::TCloudResponseInfo* const ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall CreateBucket(const System::UnicodeString BucketName, TAmazonACLType BucketACL = (TAmazonACLType)(0x1), const System::UnicodeString BucketRegion = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	bool __fastcall DeleteBucket(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall DeleteBucketPolicy(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall GetBucketXML(const System::UnicodeString BucketName, System::Classes::TStrings* OptionalParams, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	TAmazonBucketResult* __fastcall GetBucket(const System::UnicodeString BucketName, System::Classes::TStrings* OptionalParams, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall GetBucketACLXML(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::Generics::Collections::TList__1<TAmazonGrant>* __fastcall GetBucketACL(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall GetBucketPolicyJSON(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::Json::TJSONObject* __fastcall GetBucketPolicy(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall GetBucketLocationXML(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::UnicodeString __fastcall GetBucketLocation(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0));
	System::UnicodeString __fastcall GetBucketLoggingXML(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	TAmazonBucketLoggingInfo* __fastcall GetBucketLogging(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall GetBucketNotificationXML(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::Generics::Collections::TList__1<TAmazonNotificationEvent>* __fastcall GetBucketNotification(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall GetBucketObjectVersionsXML(const System::UnicodeString BucketName, System::Classes::TStrings* OptionalParams, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	TAmazonBucketResult* __fastcall GetBucketObjectVersions(const System::UnicodeString BucketName, System::Classes::TStrings* OptionalParams, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall GetRequestPaymentXML(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	TAmazonPayer __fastcall GetRequestPayment(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall GetBucketVersioningXML(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall GetBucketVersioning(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall GetBucketMFADelete(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall GetBucketLifecycleXML(const System::UnicodeString ABucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* AResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall ListMultipartUploadsXML(const System::UnicodeString BucketName, System::Classes::TStrings* const OptionalParams, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	TAmazonMultipartUploadsResult* __fastcall ListMultipartUploads(const System::UnicodeString BucketName, System::Classes::TStrings* const OptionalParams, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall SetBucketACL(const System::UnicodeString BucketName, TAmazonAccessControlPolicy* ACP, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall SetBucketPolicy(const System::UnicodeString BucketName, System::Json::TJSONObject* Policy, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall SetBucketLogging(const System::UnicodeString BucketName, TAmazonBucketLoggingInfo* LoggingInfo, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall SetBucketNotification(const System::UnicodeString BucketName, System::Generics::Collections::TList__1<TAmazonNotificationEvent>* Events, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall SetBucketRequestPayment(const System::UnicodeString BucketName, TAmazonPayer Payer, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall SetBucketVersioning(const System::UnicodeString BucketName, bool Enabled, bool MFADelete = false, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
#ifndef __aarch64__
	bool __fastcall SetBucketLifecycle(const System::UnicodeString BucketName, const Data::Cloud::Amazonapi::Lifecycle::TAmazonLifeCycleConfiguration LifeCycle, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
#else /* __aarch64__ */
	bool __fastcall SetBucketLifecycle(const System::UnicodeString BucketName, const Data::Cloud::Amazonapi::Lifecycle::TAmazonLifeCycleConfiguration &LifeCycle, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
#endif /* __aarch64__ */
	bool __fastcall DeleteObject(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall DeleteObjectVersion(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString VersionId, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall DeleteBucketLifecycle(const System::UnicodeString BucketName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall GetObject(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const TAmazonGetObjectOptionals &OptionalParams, System::Classes::TStream* ObjectStream, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString())/* overload */;
	bool __fastcall GetObject(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, System::Classes::TStream* ObjectStream, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString())/* overload */;
	bool __fastcall GetObjectVersion(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString VersionId, const TAmazonGetObjectOptionals &OptionalParams, System::Classes::TStream* ObjectStream, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString())/* overload */;
	bool __fastcall GetObjectVersion(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString VersionId, System::Classes::TStream* ObjectStream, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString())/* overload */;
	System::UnicodeString __fastcall GetObjectACLXML(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::Generics::Collections::TList__1<TAmazonGrant>* __fastcall GetObjectACL(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall GetObjectTorrent(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, System::Classes::TStream* ObjectStream, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString())/* overload */;
	System::Classes::TStrings* __fastcall GetObjectMetadata(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const TAmazonGetObjectOptionals &OptionalParams, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString())/* overload */;
	System::Classes::TStrings* __fastcall GetObjectMetadata(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString())/* overload */;
	bool __fastcall GetObjectProperties(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const TAmazonGetObjectOptionals &OptionalParams, /* out */ System::Classes::TStrings* &Properties, /* out */ System::Classes::TStrings* &Metadata, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString())/* overload */;
	bool __fastcall GetObjectProperties(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, /* out */ System::Classes::TStrings* &Properties, /* out */ System::Classes::TStrings* &Metadata, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString())/* overload */;
	bool __fastcall UploadObject(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, System::TArray__1<System::Byte> Content, bool ReducedRedundancy = false, System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), System::Classes::TStrings* Headers = (System::Classes::TStrings*)(0x0), TAmazonACLType ACL = (TAmazonACLType)(0x1), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall SetObjectACL(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, TAmazonAccessControlPolicy* ACP, System::Classes::TStrings* Headers = (System::Classes::TStrings*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString())/* overload */;
	bool __fastcall SetObjectACL(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, TAmazonACLType ACL, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString())/* overload */;
	bool __fastcall CopyObject(const System::UnicodeString DestinationBucket, const System::UnicodeString DestinationObjectName, const System::UnicodeString SourceBucket, const System::UnicodeString SourceObjectName, TAmazonCopyObjectOptionals* OptionalParams = (TAmazonCopyObjectOptionals*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall SetObjectMetadata(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, System::Classes::TStrings* Metadata, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall CopyObjectVersion(const System::UnicodeString DestinationBucket, const System::UnicodeString DestinationObjectName, const System::UnicodeString SourceBucket, const System::UnicodeString SourceObjectName, const System::UnicodeString SourceVersionId, TAmazonCopyObjectOptionals* OptionalParams = (TAmazonCopyObjectOptionals*)(0x0), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall InitiateMultipartUploadXML(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), System::Classes::TStrings* Headers = (System::Classes::TStrings*)(0x0), TAmazonACLType ACL = (TAmazonACLType)(0x1), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall InitiateMultipartUpload(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, System::Classes::TStrings* Metadata = (System::Classes::TStrings*)(0x0), System::Classes::TStrings* Headers = (System::Classes::TStrings*)(0x0), TAmazonACLType ACL = (TAmazonACLType)(0x1), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall AbortMultipartUpload(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString UploadId, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall UploadPart(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString UploadId, int PartNumber, System::TArray__1<System::Byte> Content, /* out */ TAmazonMultipartPart &Part, const System::UnicodeString ContentMD5 = System::UnicodeString(), Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	bool __fastcall CompleteMultipartUpload(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString UploadId, System::Generics::Collections::TList__1<TAmazonMultipartPart>* Parts, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall ListMultipartUploadPartsXML(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString UploadId, int MaxParts = 0x0, int PartNumberMarker = 0x0, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	TAmazonListPartsResult* __fastcall ListMultipartUploadParts(const System::UnicodeString BucketName, const System::UnicodeString ObjectName, const System::UnicodeString UploadId, int MaxParts = 0x0, int PartNumberMarker = 0x0, Data::Cloud::Cloudapi::TCloudResponseInfo* ResponseInfo = (Data::Cloud::Cloudapi::TCloudResponseInfo*)(0x0), const System::UnicodeString BucketRegion = System::UnicodeString());
	System::UnicodeString __fastcall GetEndpointFromRegion(System::UnicodeString ARegion);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define amzrNotSpecified u""
#define amzrEUWest1 u"eu-west-1"
#define amzrEUWest2 u"eu-west-2"
#define amzrEUWest3 u"eu-west-3"
#define amzrEUCentral1 u"eu-central-1"
#define amzrUSEast1 u"us-east-1"
#define amzrUSEast2 u"us-east-2"
#define amzrUSWest1 u"us-west-1"
#define amzrUSWest2 u"us-west-2"
#define amzrAPEast1 u"ap-east-1"
#define amzrAPSouth1 u"ap-south-1"
#define amzrAPSoutheast1 u"ap-southeast-1"
#define amzrAPSoutheast2 u"ap-southeast-2"
#define amzrAPNortheast1 u"ap-northeast-1"
#define amzrAPNortheast2 u"ap-northeast-2"
#define amzrAPNortheast3 u"ap-northeast-3"
#define amzrCACentral1 u"ca-central-1"
#define amzrSAEast1 u"sa-east-1"
#define amzrUSClassic u"us-east-1"
#define amzrEU u"eu-west-1"
#define amzrCNNorth1 u"cn-north-1"
#define amzrCNNorthwest1 u"cn-northwest-1"
#define azmrEUNorth1 u"eu-north-1"
#define azmrMESouth1 u"me-south-1"
#define TABLE_ROW_DATATYPE_REPLACE u"replace"
#define TABLE_ROW_DATATYPE_DO_NOT_REPLACE u"noreplace"
#define ALL_USERS_GROUP u"http://acs.amazonaws.com/groups/global/AllUsers"
#define ALL_AUTHENTICATED_USERS_GROUP u"http://acs.amazonaws.com/groups/global/AuthenticatedUsers"
#define LOG_DELIVERY_GROUP u"http://acs.amazonaws.com/groups/s3/LogDelivery"
}	/* namespace Amazonapi */
}	/* namespace Cloud */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_CLOUD_AMAZONAPI)
using namespace Data::Cloud::Amazonapi;
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
#endif	// Data_Cloud_AmazonapiHPP
