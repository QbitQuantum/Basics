// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Cloud.CloudAPI.pas' rev: 34.00 (iOS)

#ifndef Data_Cloud_CloudapiHPP
#define Data_Cloud_CloudapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.URLClient.hpp>
#include <System.Generics.Collections.hpp>
#include <Xml.XMLIntf.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Cloud
{
namespace Cloudapi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCloudConnectionInfo;
class DELPHICLASS TCloudAuthentication;
class DELPHICLASS TCloudSHA256Authentication;
class DELPHICLASS TCloudSHA1Authentication;
class DELPHICLASS TCloudHTTP;
class DELPHICLASS TCloudResponseInfo;
class DELPHICLASS TCloudTableColumn;
class DELPHICLASS TCloudTableRow;
struct TCloudQueue;
struct TCloudQueueMessageItem;
class DELPHICLASS TCloudQueueMessage;
class DELPHICLASS TCloudService;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCloudConnectionInfo : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TCloudAuthentication* FAuthentication;
	bool __fastcall IsProtocolStored();
	void __fastcall SetAccountKey(const System::UnicodeString AValue);
	
protected:
	System::UnicodeString FProtocol;
	System::UnicodeString FAccountName;
	System::UnicodeString FAccountKey;
	System::UnicodeString FRequestProxyHost;
	int FRequestProxyPort;
	bool FUseDefaultEndpoints;
	virtual System::UnicodeString __fastcall GetAccountName();
	virtual System::UnicodeString __fastcall GetAccountKey();
	
public:
	__fastcall virtual TCloudConnectionInfo(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCloudConnectionInfo();
	__property System::UnicodeString Protocol = {read=FProtocol, write=FProtocol, stored=IsProtocolStored};
	__property System::UnicodeString AccountName = {read=GetAccountName, write=FAccountName};
	__property System::UnicodeString AccountKey = {read=GetAccountKey, write=SetAccountKey};
	__property System::UnicodeString RequestProxyHost = {read=FRequestProxyHost, write=FRequestProxyHost};
	__property int RequestProxyPort = {read=FRequestProxyPort, write=FRequestProxyPort, default=0};
	__property bool UseDefaultEndpoints = {read=FUseDefaultEndpoints, write=FUseDefaultEndpoints, default=1};
};


class PASCALIMPLEMENTATION TCloudAuthentication : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	TCloudConnectionInfo* FConnectionInfo;
	System::TArray__1<System::Byte> FSHAKey;
	virtual void __fastcall AssignKey(const System::UnicodeString AccountKey);
	virtual System::UnicodeString __fastcall GetAuthorizationType() = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall SignString(const System::TArray__1<System::Byte> Signkey, const System::UnicodeString StringToSign) = 0 ;
	
public:
	__fastcall TCloudAuthentication(TCloudConnectionInfo* const ConnectionInfo);
	__fastcall virtual ~TCloudAuthentication();
	virtual System::UnicodeString __fastcall BuildAuthorizationString(const System::UnicodeString StringToSign);
};


class PASCALIMPLEMENTATION TCloudSHA256Authentication : public TCloudAuthentication
{
	typedef TCloudAuthentication inherited;
	
private:
	System::UnicodeString FAuthorizationType;
	
protected:
	virtual System::UnicodeString __fastcall GetAuthorizationType();
	virtual System::TArray__1<System::Byte> __fastcall SignString(const System::TArray__1<System::Byte> Signkey, const System::UnicodeString StringToSign);
	
public:
	__classmethod System::UnicodeString __fastcall GetHashSHA256Hex(System::UnicodeString HashString);
	__classmethod System::UnicodeString __fastcall GetStreamToHashSHA256Hex(System::Classes::TStream* const Content);
	__fastcall TCloudSHA256Authentication(TCloudConnectionInfo* const ConnectionInfo, System::UnicodeString AuthorizationType)/* overload */;
public:
	/* TCloudAuthentication.Destroy */ inline __fastcall virtual ~TCloudSHA256Authentication() { }
	
};


class PASCALIMPLEMENTATION TCloudSHA1Authentication : public TCloudAuthentication
{
	typedef TCloudAuthentication inherited;
	
private:
	System::UnicodeString FAuthorizationType;
	
protected:
	virtual System::UnicodeString __fastcall GetAuthorizationType();
	virtual System::TArray__1<System::Byte> __fastcall SignString(const System::TArray__1<System::Byte> Signkey, const System::UnicodeString StringToSign);
	
public:
	__fastcall TCloudSHA1Authentication(TCloudConnectionInfo* ConnectionInfo, System::UnicodeString AuthorizationType)/* overload */;
public:
	/* TCloudAuthentication.Destroy */ inline __fastcall virtual ~TCloudSHA1Authentication() { }
	
};


class PASCALIMPLEMENTATION TCloudHTTP : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Net::Httpclient::THTTPClient* FClient;
	System::Net::Httpclient::_di_IHTTPResponse FResponse;
	System::Net::Urlclient::TCredentialsStorage::TCredentialAuthCallback FOnAuthCallback;
	void __fastcall DoValidateServerCertificate(System::TObject* const Sender, System::Net::Urlclient::TURLRequest* const ARequest, const System::Net::Urlclient::TCertificate &Certificate, bool &Accepted);
	
protected:
	int __fastcall GetResponseCode();
	System::UnicodeString __fastcall GetResponseText();
	System::Net::Httpclient::_di_IHTTPResponse __fastcall GetResponse();
	System::Net::Urlclient::TProxySettings __fastcall GetProxyParams();
	void __fastcall SetProxyParams(const System::Net::Urlclient::TProxySettings &Value);
	
public:
	__fastcall TCloudHTTP()/* overload */;
	__fastcall virtual TCloudHTTP(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TCloudHTTP();
	System::UnicodeString __fastcall Delete(System::UnicodeString AURL)/* overload */;
	System::UnicodeString __fastcall Get(System::UnicodeString AURL)/* overload */;
	void __fastcall Get(System::UnicodeString AURL, System::Classes::TStream* AResponseContent)/* overload */;
	System::UnicodeString __fastcall Post(System::UnicodeString AURL, System::Classes::TStream* Source);
	System::UnicodeString __fastcall Delete(System::UnicodeString AURL, System::Classes::TStream* AResponseStream)/* overload */;
	void __fastcall Merge(System::UnicodeString AURL, System::Classes::TStream* RequestStream);
	System::UnicodeString __fastcall Options(const System::UnicodeString AURL)/* overload */;
	void __fastcall Options(const System::UnicodeString AURL, System::Classes::TStream* AResponseContent)/* overload */;
	void __fastcall Head(System::UnicodeString AURL);
	System::UnicodeString __fastcall Put(System::UnicodeString AURL, System::Classes::TStream* Source)/* overload */;
	System::UnicodeString __fastcall Put(System::UnicodeString AURL)/* overload */;
	void __fastcall SetAuthentication(const System::UnicodeString AUser, const System::UnicodeString APassword);
	__property int ResponseCode = {read=GetResponseCode, nodefault};
	__property System::UnicodeString ResponseText = {read=GetResponseText};
	__property System::Net::Httpclient::_di_IHTTPResponse Response = {read=GetResponse};
	__property System::Net::Urlclient::TProxySettings ProxyParams = {read=GetProxyParams, write=SetProxyParams};
	__property System::Net::Urlclient::TCredentialsStorage::TCredentialAuthCallback OnAuthCallback = {read=FOnAuthCallback, write=FOnAuthCallback};
	__property System::Net::Httpclient::THTTPClient* Client = {read=FClient};
};


class PASCALIMPLEMENTATION TCloudResponseInfo : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	int FStatusCode;
	System::UnicodeString FStatusMessage;
	System::Classes::TStrings* FHeaders;
	void __fastcall SetHeaders(System::Classes::TStrings* NewHeaders);
	
public:
	__fastcall virtual ~TCloudResponseInfo();
	void __fastcall Assign(System::TObject* const ASource);
	__property int StatusCode = {read=FStatusCode, write=FStatusCode, nodefault};
	__property System::UnicodeString StatusMessage = {read=FStatusMessage, write=FStatusMessage};
	__property System::Classes::TStrings* Headers = {read=FHeaders, write=SetHeaders};
public:
	/* TObject.Create */ inline __fastcall TCloudResponseInfo() : System::TObject() { }
	
};


class PASCALIMPLEMENTATION TCloudTableColumn : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	System::UnicodeString FName;
	System::UnicodeString FValue;
	System::UnicodeString FDataType;
	
public:
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property System::UnicodeString Value = {read=FValue, write=FValue};
	__property System::UnicodeString DataType = {read=FDataType, write=FDataType};
public:
	/* TObject.Create */ inline __fastcall TCloudTableColumn() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCloudTableColumn() { }
	
};


class PASCALIMPLEMENTATION TCloudTableRow : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	System::Generics::Collections::TList__1<TCloudTableColumn*>* FColumns;
	bool FSupportsDataType;
	
public:
	__fastcall virtual TCloudTableRow(bool SupportsDataType);
	__fastcall virtual ~TCloudTableRow();
	void __fastcall SetColumn(const System::UnicodeString Name, const System::UnicodeString Value, const System::UnicodeString DataType = System::UnicodeString(), const bool Replace = true);
	bool __fastcall DeleteColumn(const System::UnicodeString Name);
	TCloudTableColumn* __fastcall GetColumn(const System::UnicodeString Name);
	bool __fastcall GetColumnValue(const System::UnicodeString Name, /* out */ System::UnicodeString &Value);
	__property System::Generics::Collections::TList__1<TCloudTableColumn*>* Columns = {read=FColumns};
	__property bool SupportsDataType = {read=FSupportsDataType, nodefault};
};


struct DECLSPEC_DRECORD TCloudQueue
{
public:
	System::UnicodeString Name;
	System::UnicodeString URL;
	static TCloudQueue __fastcall Create(System::UnicodeString Name, System::UnicodeString URL)/* overload */;
	static TCloudQueue __fastcall Create(System::UnicodeString URL)/* overload */;
};


typedef System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TQueuePropertyArray;

struct DECLSPEC_DRECORD TCloudQueueMessageItem
{
public:
	TQueuePropertyArray Properties;
	System::UnicodeString MessageId;
	System::UnicodeString MessageText;
	System::UnicodeString PopReceipt;
};


class PASCALIMPLEMENTATION TCloudQueueMessage : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStrings* FProperties;
	System::UnicodeString FMessageId;
	System::UnicodeString FMessageText;
	System::UnicodeString FPopReceipt;
	
public:
	__fastcall TCloudQueueMessage(const System::UnicodeString MessageId, const System::UnicodeString MessageText)/* overload */;
	__fastcall TCloudQueueMessage(const System::UnicodeString MessageId, const System::UnicodeString MessageText, System::Classes::TStrings* Properties)/* overload */;
	__classmethod TCloudQueueMessage* __fastcall CreateFromRecord(const TCloudQueueMessageItem &ACloudQueueMessage);
	__fastcall virtual ~TCloudQueueMessage();
	__property System::Classes::TStrings* Properties = {read=FProperties};
	__property System::UnicodeString MessageId = {read=FMessageId};
	__property System::UnicodeString MessageText = {read=FMessageText};
	__property System::UnicodeString PopReceipt = {read=FPopReceipt, write=FPopReceipt};
};


class PASCALIMPLEMENTATION TCloudService : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	TCloudAuthentication* FAuthenticator;
	TCloudConnectionInfo* FConnectionInfo;
	System::WideChar FQueryStartChar;
	System::WideChar FQueryParamKeyValueSeparator;
	System::WideChar FQueryParamSeparator;
	bool FUseCanonicalizedHeaders;
	bool FUseCanonicalizedResource;
	bool FUseResourcePath;
	virtual void __fastcall URLEncodeQueryParams(const bool ForURL, System::UnicodeString &ParamName, System::UnicodeString &ParamValue);
	virtual System::Classes::TStrings* __fastcall GetRequiredHeaderNames(/* out */ bool &InstanceOwner) = 0 ;
	virtual System::UnicodeString __fastcall GetCanonicalizedHeaderPrefix() = 0 ;
	virtual void __fastcall SortQueryParameters(System::Classes::TStringList* const QueryParameters, bool ForURL);
	virtual void __fastcall SortHeaders(System::Classes::TStringList* const Headers);
	virtual System::UnicodeString __fastcall BuildQueryParameterString(const System::UnicodeString QueryPrefix, System::Classes::TStringList* QueryParameters, bool DoSort = false, bool ForURL = true);
	virtual System::UnicodeString __fastcall BuildStringToSign(const System::UnicodeString HTTPVerb, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, const System::UnicodeString URL);
	virtual System::UnicodeString __fastcall BuildStringToSignResourcePath(const System::UnicodeString URL);
	virtual System::UnicodeString __fastcall BuildStringToSignResources(System::UnicodeString QueryPrefix, System::Classes::TStringList* QueryParameters);
	virtual System::UnicodeString __fastcall GetHTTPRequestURI(const System::UnicodeString URL);
	virtual System::UnicodeString __fastcall BuildStringToSignPrefix(const System::UnicodeString HTTPVerb);
	virtual System::UnicodeString __fastcall BuildStringToSignHeaders(System::Classes::TStringList* Headers);
	virtual void __fastcall SetDateFromString(System::Net::Httpclient::THTTPClient* Request, const System::UnicodeString DateTimeAsString);
	virtual void __fastcall AddHeaders(System::Net::Httpclient::THTTPClient* Request, System::Classes::TStringList* const headers);
	virtual void __fastcall PrepareRequestSignature(const System::UnicodeString HTTPVerb, System::Classes::TStringList* const Headers, System::Classes::TStringList* const QueryParameters, const System::UnicodeString StringToSign, System::UnicodeString &URL, TCloudHTTP* Request, System::Classes::TStream* &Content);
	virtual TCloudHTTP* __fastcall PrepareRequest(const System::UnicodeString HTTPVerb, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, System::UnicodeString &URL, System::Classes::TStream* &Content)/* overload */;
	virtual TCloudHTTP* __fastcall PrepareRequest(const System::UnicodeString HTTPVerb, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, System::UnicodeString &URL)/* overload */;
	virtual void __fastcall PopulateResponseInfo(TCloudHTTP* ACloudHTTP, TCloudResponseInfo* ResponseInfo);
	virtual TCloudHTTP* __fastcall IssueHeadRequest(System::UnicodeString URL, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, TCloudResponseInfo* ResponseInfo);
	virtual TCloudHTTP* __fastcall IssueGetRequest(System::UnicodeString URL, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, TCloudResponseInfo* ResponseInfo, System::Classes::TStream* ResponseContent)/* overload */;
	virtual TCloudHTTP* __fastcall IssueGetRequest(System::UnicodeString URL, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, TCloudResponseInfo* ResponseInfo, /* out */ System::UnicodeString &ResponseString)/* overload */;
	virtual TCloudHTTP* __fastcall IssueGetRequest(System::UnicodeString URL, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, TCloudResponseInfo* ResponseInfo)/* overload */;
	virtual TCloudHTTP* __fastcall IssuePutRequest(System::UnicodeString URL, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, TCloudResponseInfo* ResponseInfo, System::Classes::TStream* Content = (System::Classes::TStream*)(0x0))/* overload */;
	virtual TCloudHTTP* __fastcall IssuePutRequest(System::UnicodeString URL, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, TCloudResponseInfo* ResponseInfo, System::Classes::TStream* Content, /* out */ System::UnicodeString &ResponseString)/* overload */;
	virtual TCloudHTTP* __fastcall IssueMergeRequest(System::UnicodeString URL, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, TCloudResponseInfo* ResponseInfo, System::Classes::TStream* Content);
	virtual TCloudHTTP* __fastcall IssuePostRequest(System::UnicodeString URL, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, TCloudResponseInfo* ResponseInfo, System::Classes::TStream* Content)/* overload */;
	virtual TCloudHTTP* __fastcall IssuePostRequest(System::UnicodeString URL, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, TCloudResponseInfo* ResponseInfo, System::Classes::TStream* Content, /* out */ System::UnicodeString &ResponseString)/* overload */;
	virtual TCloudHTTP* __fastcall IssueDeleteRequest(System::UnicodeString URL, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, TCloudResponseInfo* ResponseInfo)/* overload */;
	virtual TCloudHTTP* __fastcall IssueDeleteRequest(System::UnicodeString URL, System::Classes::TStringList* Headers, System::Classes::TStringList* QueryParameters, const System::UnicodeString QueryPrefix, TCloudResponseInfo* ResponseInfo, /* out */ System::UnicodeString &ResponseString)/* overload */;
	virtual TCloudHTTP* __fastcall IssueOptionsRequest(System::UnicodeString AURL, System::Classes::TStringList* const AHeaders, System::Classes::TStringList* const AQueryParameters, const System::UnicodeString AQueryPrefix, TCloudResponseInfo* const AResponseInfo)/* overload */;
	virtual TCloudHTTP* __fastcall IssueOptionsRequest(System::UnicodeString AURL, System::Classes::TStringList* const AHeaders, System::Classes::TStringList* const AQueryParameters, const System::UnicodeString AQueryPrefix, TCloudResponseInfo* const AResponseInfo, /* out */ System::UnicodeString &AResponseString)/* overload */;
	virtual System::UnicodeString __fastcall URLEncodeValue(const System::UnicodeString Value);
	
public:
	__fastcall TCloudService(TCloudConnectionInfo* const ConnectionInfo, TCloudAuthentication* const Authenticator);
	__fastcall virtual ~TCloudService();
	__property TCloudConnectionInfo* ConnectionInfo = {read=FConnectionInfo};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall XMLEscape _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString Str);
extern DELPHI_PACKAGE System::UnicodeString __fastcall EncodeBytes64 _DEPRECATED_ATTRIBUTE0 (System::TArray__1<System::Byte> asBytes);
extern DELPHI_PACKAGE System::UnicodeString __fastcall Encode64 _DEPRECATED_ATTRIBUTE0 (System::UnicodeString Str);
extern DELPHI_PACKAGE System::TArray__1<System::Byte> __fastcall DecodeBytes64 _DEPRECATED_ATTRIBUTE0 (System::UnicodeString Str);
extern DELPHI_PACKAGE System::UnicodeString __fastcall Decode64 _DEPRECATED_ATTRIBUTE0 (System::UnicodeString Str);
extern DELPHI_PACKAGE System::UnicodeString __fastcall URLEncode(const System::UnicodeString Str)/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall URLEncode(const System::UnicodeString Str, const System::WideChar *EncodeChars, const int EncodeChars_High)/* overload */;
extern DELPHI_PACKAGE Xml::Xmlintf::_di_IXMLNode __fastcall GetFirstMatchingChildNode(Xml::Xmlintf::_di_IXMLNode Parent, System::UnicodeString ChildName);
extern DELPHI_PACKAGE void __fastcall PopulateKeyValuePairs _DEPRECATED_ATTRIBUTE0 (Xml::Xmlintf::_di_IXMLNode Parent, System::Classes::TStrings* PairList, const System::UnicodeString PairNodeName, const System::UnicodeString KeyNodeName = u"Name", const System::UnicodeString ValueNodeName = u"Value");
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetChildText(const System::UnicodeString NodeName, Xml::Xmlintf::_di_IXMLNode Parent);
}	/* namespace Cloudapi */
}	/* namespace Cloud */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_CLOUD_CLOUDAPI)
using namespace Data::Cloud::Cloudapi;
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
#endif	// Data_Cloud_CloudapiHPP
