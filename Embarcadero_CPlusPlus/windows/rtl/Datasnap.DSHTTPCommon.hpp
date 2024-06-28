// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSHTTPCommon.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DshttpcommonHPP
#define Datasnap_DshttpcommonHPP

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
#include <Data.DbxDatasnap.hpp>
#include <Data.DBXPlatform.hpp>
#include <Datasnap.DSService.hpp>
#include <Datasnap.DSCommon.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dshttpcommon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSHTTPDispatch;
class DELPHICLASS TDSHTTPContext;
class DELPHICLASS TDSHTTPRequest;
class DELPHICLASS TDSHTTPResponse;
class DELPHICLASS TDSExecutionResponse;
class DELPHICLASS TDSServiceResponseHandler;
class DELPHICLASS TDSJsonResponseHandler;
class DELPHICLASS TDSCommandComplexParams;
class DELPHICLASS TDSCacheResultCommandHandler;
class DELPHICLASS TDSNullResponseHandler;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TDSHTTPCommandType : unsigned char { hcUnknown, hcGET, hcPOST, hcDELETE, hcPUT, hcOther };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPDispatch : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	class DELPHICLASS TOwnedObjects;
	class PASCALIMPLEMENTATION TOwnedObjects : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		System::Generics::Collections::TDictionary__2<System::UnicodeString,System::TObject*>* FDictionary;
		System::TObject* __fastcall GetItem(const System::UnicodeString AName);
		
	public:
		__fastcall TOwnedObjects();
		__fastcall virtual ~TOwnedObjects();
		void __fastcall Add(System::TObject* const AObject)/* overload */;
		void __fastcall Add(const System::UnicodeString AName, System::TObject* const AObject)/* overload */;
		void __fastcall Remove(const System::UnicodeString AName);
		System::Generics::Collections::TPair__2<System::UnicodeString,System::TObject*> __fastcall Extract(const System::UnicodeString AName);
		bool __fastcall TryGetValue(const System::UnicodeString AName, /* out */ System::TObject* &AValue);
		__property System::TObject* Items[const System::UnicodeString I] = {read=GetItem};
	};
	
	
	
private:
	TOwnedObjects* FOwnedObjects;
	TDSHTTPRequest* FRequest;
	TDSHTTPResponse* FResponse;
	TDSHTTPContext* FContext;
	TOwnedObjects* __fastcall GetOwnedObjects();
	
public:
	__fastcall TDSHTTPDispatch(TDSHTTPContext* const AContext, TDSHTTPRequest* const ARequest, TDSHTTPResponse* const AResponse);
	__fastcall virtual ~TDSHTTPDispatch();
	__property TDSHTTPContext* Context = {read=FContext};
	__property TDSHTTPRequest* Request = {read=FRequest};
	__property TDSHTTPResponse* Response = {read=FResponse};
	__property TOwnedObjects* OwnedObjects = {read=GetOwnedObjects};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPContext : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual bool __fastcall Connected() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDSHTTPContext() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSHTTPContext() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPRequest : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetCommand() = 0 ;
	virtual TDSHTTPCommandType __fastcall GetCommandType() = 0 ;
	virtual System::UnicodeString __fastcall GetDocument() = 0 ;
	virtual System::Classes::TStrings* __fastcall GetParams() = 0 ;
	virtual System::Classes::TStream* __fastcall GetPostStream() = 0 ;
	virtual System::UnicodeString __fastcall GetAuthUserName() = 0 ;
	virtual System::UnicodeString __fastcall GetAuthPassword() = 0 ;
	virtual System::UnicodeString __fastcall GetURI() = 0 ;
	virtual System::UnicodeString __fastcall GetPragma() = 0 ;
	virtual System::UnicodeString __fastcall GetAccept() = 0 ;
	virtual System::UnicodeString __fastcall GetRemoteIP() = 0 ;
	virtual System::UnicodeString __fastcall GetUserAgent() = 0 ;
	virtual System::UnicodeString __fastcall GetProtocolVersion() = 0 ;
	
public:
	__property TDSHTTPCommandType CommandType = {read=GetCommandType, nodefault};
	__property System::UnicodeString Document = {read=GetDocument};
	__property System::Classes::TStrings* Params = {read=GetParams};
	__property System::Classes::TStream* PostStream = {read=GetPostStream};
	__property System::UnicodeString AuthUserName = {read=GetAuthUserName};
	__property System::UnicodeString AuthPassword = {read=GetAuthPassword};
	__property System::UnicodeString Command = {read=GetCommand};
	__property System::UnicodeString URI = {read=GetURI};
	__property System::UnicodeString Pragma = {read=GetPragma};
	__property System::UnicodeString Accept = {read=GetAccept};
	__property System::UnicodeString RemoteIP = {read=GetRemoteIP};
	__property System::UnicodeString UserAgent = {read=GetUserAgent};
	__property System::UnicodeString ProtocolVersion = {read=GetProtocolVersion};
public:
	/* TObject.Create */ inline __fastcall TDSHTTPRequest() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSHTTPRequest() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPResponse : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::Classes::TStream* __fastcall GetContentStream() = 0 ;
	virtual int __fastcall GetResponseNo() = 0 ;
	virtual System::UnicodeString __fastcall GetResponseText() = 0 ;
	virtual void __fastcall SetContentStream(System::Classes::TStream* const Value) = 0 ;
	virtual void __fastcall SetResponseNo(const int Value) = 0 ;
	virtual void __fastcall SetResponseText(const System::UnicodeString Value) = 0 ;
	virtual System::UnicodeString __fastcall GetContentText() = 0 ;
	virtual void __fastcall SetContentText(const System::UnicodeString Value) = 0 ;
	virtual __int64 __fastcall GetContentLength() = 0 ;
	virtual void __fastcall SetContentLength(const __int64 Value) = 0 ;
	virtual bool __fastcall GetCloseConnection() = 0 ;
	virtual void __fastcall SetCloseConnection(const bool Value) = 0 ;
	virtual System::UnicodeString __fastcall GetPragma() = 0 ;
	virtual void __fastcall SetPragma(const System::UnicodeString Value) = 0 ;
	virtual System::UnicodeString __fastcall GetContentType() = 0 ;
	virtual void __fastcall SetContentType(const System::UnicodeString Value) = 0 ;
	virtual bool __fastcall GetFreeContentStream() = 0 ;
	virtual void __fastcall SetFreeContentStream(const bool Value) = 0 ;
	
public:
	virtual void __fastcall SetHeaderAuthentication(const System::UnicodeString Value, const System::UnicodeString Realm) = 0 ;
	__property bool FreeContentStream = {read=GetFreeContentStream, write=SetFreeContentStream, nodefault};
	__property int ResponseNo = {read=GetResponseNo, write=SetResponseNo, nodefault};
	__property System::UnicodeString ResponseText = {read=GetResponseText, write=SetResponseText};
	__property System::UnicodeString ContentType = {read=GetContentType, write=SetContentType};
	__property System::Classes::TStream* ContentStream = {read=GetContentStream, write=SetContentStream};
	__property System::UnicodeString ContentText = {read=GetContentText, write=SetContentText};
	__property __int64 ContentLength = {read=GetContentLength, write=SetContentLength};
	__property bool CloseConnection = {read=GetCloseConnection, write=SetCloseConnection, nodefault};
	__property System::UnicodeString Pragma = {read=GetPragma, write=SetPragma};
public:
	/* TObject.Create */ inline __fastcall TDSHTTPResponse() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSHTTPResponse() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TDSHTTPServiceTraceEvent)(System::TObject* Sender, TDSHTTPContext* AContext, TDSHTTPRequest* ARequest, TDSHTTPResponse* AResponse);

typedef void __fastcall (__closure *TDSRESTResultEvent)(System::TObject* Sender, System::Json::TJSONValue* &ResultVal, Data::Dbxcommon::TDBXCommand* const Command, bool &Handled);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSExecutionResponse : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	Data::Dbxcommon::TDBXCommand* FCommand;
	Data::Dbxcommon::TDBXConnection* FDBXConnection;
	System::UnicodeString FErrorMessage;
	bool FLocalConnection;
	
public:
	__fastcall virtual TDSExecutionResponse(Data::Dbxcommon::TDBXCommand* Command, Data::Dbxcommon::TDBXConnection* DBXConnection, bool LocalConnection)/* overload */;
	__fastcall virtual TDSExecutionResponse(System::UnicodeString ErrorMessage)/* overload */;
	__fastcall virtual ~TDSExecutionResponse();
	__property Data::Dbxcommon::TDBXCommand* Command = {read=FCommand};
	__property System::UnicodeString ErrorMessage = {read=FErrorMessage};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSServiceResponseHandler : public Data::Dbxcommon::TRequestCommandHandler
{
	typedef Data::Dbxcommon::TRequestCommandHandler inherited;
	
	
public:
	typedef void __fastcall (__closure *TParsingRequestEvent)(System::TObject* Sender, const System::UnicodeString ARequest, System::Classes::TStrings* const ASegments, System::UnicodeString &ADSMethodName, System::Classes::TStrings* const AParamValues, bool &AHandled);
	
	typedef void __fastcall (__closure *TParseRequestEvent)(System::TObject* Sender, const System::UnicodeString ARequest, System::Classes::TStrings* const ASegments, System::UnicodeString &ADSMethodName, System::Classes::TStrings* const AParamValues);
	
	
protected:
	TDSHTTPCommandType FCommandType;
	System::Generics::Collections::TList__1<TDSExecutionResponse*>* FCommandList;
	bool FLocalConnection;
	bool FForceResultArray;
	TParsingRequestEvent FParsingRequestEvent;
	TParseRequestEvent FParseRequestEvent;
#ifndef _WIN64
	virtual System::DynamicArray<System::Byte> __fastcall ByteContent(System::Json::TJSONValue* JsonValue);
#else /* _WIN64 */
	virtual System::TArray__1<System::Byte> __fastcall ByteContent(System::Json::TJSONValue* JsonValue);
#endif /* _WIN64 */
	virtual int __fastcall GetResultCount();
	virtual int __fastcall GetOKStatus();
	
public:
	__fastcall virtual TDSServiceResponseHandler(TDSHTTPCommandType CommandType, bool LocalConnection)/* overload */;
	__fastcall virtual ~TDSServiceResponseHandler();
	virtual void __fastcall DoParsingRequest(System::TObject* Sender, const System::UnicodeString ARequest, System::Classes::TStrings* const ASegments, System::UnicodeString &ADSMethodName, System::Classes::TStrings* const AParamValues, bool &AHandled);
	virtual void __fastcall DoParseRequest(System::TObject* Sender, System::UnicodeString ARequest, System::Classes::TStrings* const ASegments, System::UnicodeString &ADSMethodName, System::Classes::TStrings* const AParamValues);
	virtual void __fastcall AddCommandError(System::UnicodeString ErrorMessage);
	virtual void __fastcall AddCommand(Data::Dbxcommon::TDBXCommand* Command, Data::Dbxcommon::TDBXConnection* DBXConnection);
	virtual void __fastcall ClearCommands();
	virtual void __fastcall GetResponse(/* out */ System::Json::TJSONValue* &Response, /* out */ System::Classes::TStream* &ResponseStream, /* out */ bool &ContainsErrors) = 0 ;
	virtual void __fastcall PopulateResponse(TDSHTTPResponse* AResponseInfo, Data::Dbxplatform::TDSInvocationMetadata* InvokeMetadata) = 0 ;
	virtual void __fastcall Close() = 0 ;
	__property bool ForceResultArray = {read=FForceResultArray, write=FForceResultArray, nodefault};
	__property TParseRequestEvent OnParseRequest = {read=FParseRequestEvent, write=FParseRequestEvent};
	__property TParsingRequestEvent OnParsingRequest = {read=FParsingRequestEvent, write=FParsingRequestEvent};
};


class PASCALIMPLEMENTATION TDSJsonResponseHandler : public TDSServiceResponseHandler
{
	typedef TDSServiceResponseHandler inherited;
	
protected:
	Datasnap::Dsservice::TDSService* FDSService;
	bool FServiceInstanceOwner;
	bool FAllowStream;
	TDSRESTResultEvent FResultEvent;
	void __fastcall GetCommandResponse(Data::Dbxcommon::TDBXCommand* Command, /* out */ System::Json::TJSONValue* &Response, /* out */ System::Classes::TStream* &ResponseStream);
	virtual bool __fastcall HandleParameter(Data::Dbxcommon::TDBXCommand* const Command, Data::Dbxcommon::TDBXParameter* const Parameter, /* out */ System::Json::TJSONValue* &Response, System::Classes::TStream* &ResponseStream) = 0 ;
	virtual void __fastcall PopulateContent(TDSHTTPResponse* ResponseInfo, System::Json::TJSONValue* Response, System::Classes::TStream* ResponseStream) = 0 ;
	virtual void __fastcall ProcessResultObject(System::Json::TJSONObject* &ResultObj, Data::Dbxcommon::TDBXCommand* Command);
	
public:
	__fastcall virtual TDSJsonResponseHandler(TDSHTTPCommandType CommandType, Datasnap::Dsservice::TDSService* DSService, bool ServiceInstanceOwner)/* overload */;
	__fastcall virtual ~TDSJsonResponseHandler();
	virtual void __fastcall GetResponse(/* out */ System::Json::TJSONValue* &Response, /* out */ System::Classes::TStream* &ResponseStream, /* out */ bool &ContainsErrors);
	virtual void __fastcall PopulateResponse(TDSHTTPResponse* ResponseInfo, Data::Dbxplatform::TDSInvocationMetadata* InvokeMetadata);
	__property TDSRESTResultEvent ResultEvent = {read=FResultEvent, write=FResultEvent};
public:
	/* TDSServiceResponseHandler.Create */ inline __fastcall virtual TDSJsonResponseHandler(TDSHTTPCommandType CommandType, bool LocalConnection)/* overload */ : TDSServiceResponseHandler(CommandType, LocalConnection) { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCommandComplexParams : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Data::Dbxcommon::TDBXCommand* FCommand;
	System::Generics::Collections::TList__1<Data::Dbxcommon::TDBXParameter*>* FParameters;
	
public:
	__fastcall virtual TDSCommandComplexParams(Data::Dbxcommon::TDBXCommand* Command);
	__fastcall virtual ~TDSCommandComplexParams();
	int __fastcall GetParameterCount();
	Data::Dbxcommon::TDBXParameter* __fastcall GetParameter(int Index);
	int __fastcall AddParameter(Data::Dbxcommon::TDBXParameter* Parameter);
	__property Data::Dbxcommon::TDBXCommand* Command = {read=FCommand};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCacheResultCommandHandler : public Data::Dbxcommon::TResultCommandHandler
{
	typedef Data::Dbxcommon::TResultCommandHandler inherited;
	
protected:
	Data::Dbxcommon::TRequestCommandHandler* FCommandWrapper;
	System::Generics::Collections::TList__1<TDSCommandComplexParams*>* FCacheCommands;
	
public:
	__fastcall virtual TDSCacheResultCommandHandler(Data::Dbxcommon::TRequestCommandHandler* CommandWrapper);
	__fastcall virtual ~TDSCacheResultCommandHandler();
	virtual int __fastcall GetCommandCount();
	virtual int __fastcall GetParameterCount(int Index);
	virtual Data::Dbxcommon::TDBXCommand* __fastcall GetCommand(int Index);
	virtual Data::Dbxcommon::TDBXParameter* __fastcall GetCommandParameter(int CommandIndex, int ParameterIndex)/* overload */;
	virtual Data::Dbxcommon::TDBXParameter* __fastcall GetCommandParameter(Data::Dbxcommon::TDBXCommand* Command, int Index)/* overload */;
	__property System::Generics::Collections::TList__1<TDSCommandComplexParams*>* CacheCommands = {read=FCacheCommands, write=FCacheCommands};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSNullResponseHandler : public TDSJsonResponseHandler
{
	typedef TDSJsonResponseHandler inherited;
	
protected:
	virtual bool __fastcall HandleParameter(Data::Dbxcommon::TDBXCommand* const Command, Data::Dbxcommon::TDBXParameter* const Parameter, /* out */ System::Json::TJSONValue* &Response, System::Classes::TStream* &ResponseStream);
	virtual void __fastcall PopulateContent(TDSHTTPResponse* ResponseInfo, System::Json::TJSONValue* Response, System::Classes::TStream* ResponseStream);
	
public:
	__fastcall TDSNullResponseHandler(Datasnap::Dsservice::TDSService* DSService, TDSHTTPCommandType CommandType, bool ServiceInstanceOwner);
	virtual void __fastcall Close();
public:
	/* TDSJsonResponseHandler.Destroy */ inline __fastcall virtual ~TDSNullResponseHandler() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dshttpcommon */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSHTTPCOMMON)
using namespace Datasnap::Dshttpcommon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DshttpcommonHPP
