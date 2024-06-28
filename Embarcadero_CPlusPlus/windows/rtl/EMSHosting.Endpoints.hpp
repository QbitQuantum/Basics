// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.Endpoints.pas' rev: 34.00 (Windows)

#ifndef Emshosting_EndpointsHPP
#define Emshosting_EndpointsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.JSON.hpp>
#include <EMS.ResourceAPI.hpp>
#include <EMSHosting.RequestTypes.hpp>
#include <System.JSON.Writers.hpp>
#include <System.JSON.Readers.hpp>
#include <System.Net.Mime.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Emshosting
{
namespace Endpoints
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEndpointParamsImpl;
class DELPHICLASS TEndpointSegmentsImpl;
class DELPHICLASS TEndpointRequestHeadersImpl;
class DELPHICLASS TEndpointResponseHeadersRWImpl;
class DELPHICLASS TEndpointParamsImplW;
class DELPHICLASS TEndpointSegmentsImplW;
class DELPHICLASS TBodyReader;
class DELPHICLASS TEndpointRequestBodyImpl;
class DELPHICLASS TEndpointResponseBodyImpl;
class DELPHICLASS TEndpointNegotiationImpl;
class DELPHICLASS TEndpointContextImpl;
class DELPHICLASS TEndpointRequestImpl;
class DELPHICLASS TEndpointResponseImpl;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointParamsImpl : public Ems::Resourceapi::TEndpointParams
{
	typedef Ems::Resourceapi::TEndpointParams inherited;
	
	
private:
	typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> TPairItem;
	
#ifndef _WIN64
	typedef System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TPairs;
#else /* _WIN64 */
	typedef System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TPairs;
#endif /* _WIN64 */
	
	
private:
	System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> >* FList;
	int FSegmentParamLength;
	
protected:
	virtual int __fastcall GetCount();
	virtual System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> __fastcall GetPair(const int Index);
	virtual void __fastcall DoAdd(const System::UnicodeString AName, const System::UnicodeString AValue);
	
public:
	__fastcall TEndpointParamsImpl()/* overload */;
#ifndef _WIN64
	__fastcall TEndpointParamsImpl(const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryPairs)/* overload */;
#else /* _WIN64 */
	__fastcall TEndpointParamsImpl(const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryPairs)/* overload */;
#endif /* _WIN64 */
	__fastcall virtual ~TEndpointParamsImpl();
	virtual bool __fastcall TryGetValue(const System::UnicodeString AName, /* out */ System::UnicodeString &AValue);
	virtual bool __fastcall Contains(const System::UnicodeString AName);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointSegmentsImpl : public Ems::Resourceapi::TEndpointSegments
{
	typedef Ems::Resourceapi::TEndpointSegments inherited;
	
private:
	System::Generics::Collections::TList__1<System::UnicodeString>* FList;
	
protected:
	virtual int __fastcall GetCount();
	virtual System::UnicodeString __fastcall GetItem(const int AIndex);
	
public:
	__fastcall TEndpointSegmentsImpl()/* overload */;
#ifndef _WIN64
	__fastcall TEndpointSegmentsImpl(const System::DynamicArray<System::UnicodeString> ASegments)/* overload */;
#else /* _WIN64 */
	__fastcall TEndpointSegmentsImpl(const System::TArray__1<System::UnicodeString> ASegments)/* overload */;
#endif /* _WIN64 */
	__fastcall virtual ~TEndpointSegmentsImpl();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointRequestHeadersImpl : public Ems::Resourceapi::TEndpointHeaders
{
	typedef Ems::Resourceapi::TEndpointHeaders inherited;
	
private:
	Emshosting::Requesttypes::_di_IEMSHostRequest FRequest;
	
public:
	__fastcall TEndpointRequestHeadersImpl(const Emshosting::Requesttypes::_di_IEMSHostRequest ARequest);
	virtual bool __fastcall TryGetValue(const System::UnicodeString AName, /* out */ System::UnicodeString &AValue);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointRequestHeadersImpl() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointResponseHeadersRWImpl : public Ems::Resourceapi::TEndpointHeaders
{
	typedef Ems::Resourceapi::TEndpointHeaders inherited;
	
private:
	Emshosting::Requesttypes::_di_IEMSHostResponse FResponse;
	
protected:
	virtual void __fastcall DoSetValue(const System::UnicodeString AName, const System::UnicodeString AValue);
	
public:
	__fastcall TEndpointResponseHeadersRWImpl(const Emshosting::Requesttypes::_di_IEMSHostResponse AResponse);
	virtual bool __fastcall TryGetValue(const System::UnicodeString AName, /* out */ System::UnicodeString &AValue);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointResponseHeadersRWImpl() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointParamsImplW : public TEndpointParamsImpl
{
	typedef TEndpointParamsImpl inherited;
	
	
protected:
	virtual void __fastcall DoAdd(const System::UnicodeString AName, const System::UnicodeString AValue);
public:
	/* TEndpointParamsImpl.Create */ inline __fastcall TEndpointParamsImplW()/* overload */ : TEndpointParamsImpl() { }
#ifndef _WIN64
	/* TEndpointParamsImpl.Create */ inline __fastcall TEndpointParamsImplW(const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryPairs)/* overload */ : TEndpointParamsImpl(AQueryPairs) { }
#else /* _WIN64 */
	/* TEndpointParamsImpl.Create */ inline __fastcall TEndpointParamsImplW(const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQueryPairs)/* overload */ : TEndpointParamsImpl(AQueryPairs) { }
#endif /* _WIN64 */
	/* TEndpointParamsImpl.Destroy */ inline __fastcall virtual ~TEndpointParamsImplW() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointSegmentsImplW : public TEndpointSegmentsImpl
{
	typedef TEndpointSegmentsImpl inherited;
	
protected:
	virtual void __fastcall DoAdd(const System::UnicodeString AValue);
public:
	/* TEndpointSegmentsImpl.Create */ inline __fastcall TEndpointSegmentsImplW()/* overload */ : TEndpointSegmentsImpl() { }
#ifndef _WIN64
	/* TEndpointSegmentsImpl.Create */ inline __fastcall TEndpointSegmentsImplW(const System::DynamicArray<System::UnicodeString> ASegments)/* overload */ : TEndpointSegmentsImpl(ASegments) { }
#else /* _WIN64 */
	/* TEndpointSegmentsImpl.Create */ inline __fastcall TEndpointSegmentsImplW(const System::TArray__1<System::UnicodeString> ASegments)/* overload */ : TEndpointSegmentsImpl(ASegments) { }
#endif /* _WIN64 */
	/* TEndpointSegmentsImpl.Destroy */ inline __fastcall virtual ~TEndpointSegmentsImplW() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef TEndpointParamsImpl TEndpointRequestParams;

typedef TEndpointParamsImplW TEndpontResponseParams;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBodyReader : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FContentType;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FRawContent;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FRawContent;
#endif /* _WIN64 */
	int FContentLength;
	System::Classes::TStream* FStream;
	System::Json::TJSONValue* FValue;
	System::Json::Readers::TJsonTextReader* FJSONReader;
	System::Classes::TTextReader* FStreamReader;
	System::Json::Readers::TJsonTextReader* __fastcall GetJSONReader();
	
public:
#ifndef _WIN64
	__fastcall TBodyReader(const System::UnicodeString AContentType, int AContentLength, const System::DynamicArray<System::Byte> ARawContent)/* overload */;
#else /* _WIN64 */
	__fastcall TBodyReader(const System::UnicodeString AContentType, int AContentLength, const System::TArray__1<System::Byte> ARawContent)/* overload */;
#endif /* _WIN64 */
	__fastcall TBodyReader(const System::UnicodeString AContentType, System::Classes::TStream* const AContentStream)/* overload */;
	__fastcall virtual ~TBodyReader();
	System::UnicodeString __fastcall GetContentType();
	bool __fastcall TryGetArray(/* out */ System::Json::TJSONArray* &AJSONArray);
#ifndef _WIN64
	bool __fastcall TryGetBytes(/* out */ System::DynamicArray<System::Byte> &ABytes);
#else /* _WIN64 */
	bool __fastcall TryGetBytes(/* out */ System::TArray__1<System::Byte> &ABytes);
#endif /* _WIN64 */
	bool __fastcall TryGetObject(/* out */ System::Json::TJSONObject* &AJSONObject);
	bool __fastcall TryGetStream(/* out */ System::Classes::TStream* &AStream)/* overload */;
	bool __fastcall TryGetStream(/* out */ System::Classes::TStream* &AStream, /* out */ System::UnicodeString &AContentType)/* overload */;
	bool __fastcall TryGetValue(/* out */ System::Json::TJSONValue* &AJSONValue);
	__property System::Json::Readers::TJsonTextReader* JSONReader = {read=GetJSONReader};
	__property System::UnicodeString ContentType = {read=GetContentType};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointRequestBodyImpl : public Ems::Resourceapi::TEndpointRequestBody
{
	typedef Ems::Resourceapi::TEndpointRequestBody inherited;
	
private:
	TBodyReader* FBodyReader;
	
protected:
	virtual System::UnicodeString __fastcall GetContentType();
	virtual System::Json::Readers::TJsonTextReader* __fastcall GetJSONReader();
	
public:
	__fastcall TEndpointRequestBodyImpl(const Emshosting::Requesttypes::_di_IEMSHostRequest ARequest);
	__fastcall virtual ~TEndpointRequestBodyImpl();
	virtual bool __fastcall TryGetStream(/* out */ System::Classes::TStream* &AStream)/* overload */;
	virtual bool __fastcall TryGetStream(/* out */ System::Classes::TStream* &AStream, /* out */ System::UnicodeString &AContentType)/* overload */;
	virtual bool __fastcall TryGetObject(/* out */ System::Json::TJSONObject* &AJSONObject);
	virtual bool __fastcall TryGetArray(/* out */ System::Json::TJSONArray* &AJSONArray);
	virtual bool __fastcall TryGetValue(/* out */ System::Json::TJSONValue* &AJSONValue);
#ifndef _WIN64
	virtual bool __fastcall TryGetBytes(/* out */ System::DynamicArray<System::Byte> &ABytes);
#else /* _WIN64 */
	virtual bool __fastcall TryGetBytes(/* out */ System::TArray__1<System::Byte> &ABytes);
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointResponseBodyImpl : public Ems::Resourceapi::TEndpointResponseBody
{
	typedef Ems::Resourceapi::TEndpointResponseBody inherited;
	
private:
	Emshosting::Requesttypes::_di_IEMSHostResponse FHostResponse;
	System::Json::Writers::TJsonTextWriter* FJSONWriter;
	System::Classes::TStream* FWriterStream;
	
protected:
	virtual System::Json::Writers::TJsonTextWriter* __fastcall GetJSONWriter();
	
public:
	virtual void __fastcall SetValue(System::Json::TJSONValue* const AJSONValue, bool AOwnsValue);
#ifndef _WIN64
	virtual void __fastcall SetBytes(const System::DynamicArray<System::Byte> ABytes, const System::UnicodeString AContentType);
#else /* _WIN64 */
	virtual void __fastcall SetBytes(const System::TArray__1<System::Byte> ABytes, const System::UnicodeString AContentType);
#endif /* _WIN64 */
	virtual void __fastcall SetStream(System::Classes::TStream* const AStream, const System::UnicodeString AContentType, bool AOwnsValue);
	__fastcall TEndpointResponseBodyImpl(const Emshosting::Requesttypes::_di_IEMSHostResponse AHostResponse);
	__fastcall virtual ~TEndpointResponseBodyImpl();
	void __fastcall Write();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointNegotiationImpl : public Ems::Resourceapi::TEndpointNegotiation
{
	typedef Ems::Resourceapi::TEndpointNegotiation inherited;
	
private:
	System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* FConsumeList;
	System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* FProduceList;
	
protected:
	virtual System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* __fastcall GetConsumeList();
	virtual System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* __fastcall GetProduceList();
	
public:
	__fastcall TEndpointNegotiationImpl(Ems::Resourceapi::TEndpointHeaders* const AHeaders);
	__fastcall virtual ~TEndpointNegotiationImpl();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointContextImpl : public Ems::Resourceapi::TEndpointContext
{
	typedef Ems::Resourceapi::TEndpointContext inherited;
	
	
public:
	__interface DELPHIINTERFACE TGetEndpointNameCallback;
	typedef System::DelphiInterface<TGetEndpointNameCallback> _di_TGetEndpointNameCallback;
	__interface TGetEndpointNameCallback  : public System::IInterface 
	{
		virtual System::UnicodeString __fastcall Invoke() = 0 ;
	};
	
	__interface DELPHIINTERFACE TCreateUserCallback;
	typedef System::DelphiInterface<TCreateUserCallback> _di_TCreateUserCallback;
	__interface TCreateUserCallback  : public System::IInterface 
	{
		virtual void __fastcall Invoke(TEndpointContextImpl* const AContext, /* out */ Ems::Resourceapi::TEndpointContext::TUser* &AUser) = 0 ;
	};
	
	__interface DELPHIINTERFACE TCreateEdgemoduleCallback;
	typedef System::DelphiInterface<TCreateEdgemoduleCallback> _di_TCreateEdgemoduleCallback;
	__interface TCreateEdgemoduleCallback  : public System::IInterface 
	{
		virtual void __fastcall Invoke(TEndpointContextImpl* const AContext, /* out */ Ems::Resourceapi::TEndpointContext::TEdgemodule* &AEdgemodule) = 0 ;
	};
	
	__interface DELPHIINTERFACE TGetRequestCallback;
	typedef System::DelphiInterface<TGetRequestCallback> _di_TGetRequestCallback;
	__interface TGetRequestCallback  : public System::IInterface 
	{
		virtual Ems::Resourceapi::TEndpointRequest* __fastcall Invoke() = 0 ;
	};
	
	__interface DELPHIINTERFACE TGetResponseCallback;
	typedef System::DelphiInterface<TGetResponseCallback> _di_TGetResponseCallback;
	__interface TGetResponseCallback  : public System::IInterface 
	{
		virtual Ems::Resourceapi::TEndpointResponse* __fastcall Invoke() = 0 ;
	};
	
	__interface DELPHIINTERFACE TGetAuthenticatedCallback;
	typedef System::DelphiInterface<TGetAuthenticatedCallback> _di_TGetAuthenticatedCallback;
	__interface TGetAuthenticatedCallback  : public System::IInterface 
	{
		virtual Ems::Resourceapi::TEndpointContext::TAuthenticated __fastcall Invoke() = 0 ;
	};
	
	__interface DELPHIINTERFACE TGetTenantCallback;
	typedef System::DelphiInterface<TGetTenantCallback> _di_TGetTenantCallback;
	__interface TGetTenantCallback  : public System::IInterface 
	{
		virtual Ems::Resourceapi::TEndpointContext::TTenant* __fastcall Invoke() = 0 ;
	};
	
	enum class DECLSPEC_DENUM TEndpointDataType : unsigned char { None, AddUser, DeletedUser, LoginUser };
	
	
private:
	System::UnicodeString FEndpontDataValue;
	TEndpointDataType FEndpointDataType;
	Ems::Resourceapi::TEndpointContext::TUser* FUser;
	Ems::Resourceapi::TEndpointContext::TEdgemodule* FEdgemodule;
	Ems::Resourceapi::TEndpointContext::TTenant* FTenant;
	Ems::Resourceapi::TEndpointNegotiation* FNegotiation;
	_di_TCreateUserCallback FOnCreateUser;
	_di_TCreateEdgemoduleCallback FOnCreateEdgemodule;
	_di_TGetResponseCallback FOnGetResponse;
	_di_TGetRequestCallback FOnGetRequest;
	_di_TGetAuthenticatedCallback FOnGetAuthenticated;
	_di_TGetEndpointNameCallback FOnGetEndpointName;
	_di_TGetTenantCallback FOnGetTenant;
	bool FCreatorRequired;
	
protected:
	virtual Ems::Resourceapi::TEndpointContext::TUser* __fastcall GetUser();
	virtual Ems::Resourceapi::TEndpointContext::TEdgemodule* __fastcall GetEdgemodule();
	virtual Ems::Resourceapi::TEndpointContext::TAuthenticated __fastcall GetAuthenticated();
	virtual Ems::Resourceapi::TEndpointRequest* __fastcall GetRequest();
	virtual Ems::Resourceapi::TEndpointResponse* __fastcall GetResponse();
	virtual System::UnicodeString __fastcall GetEndpointName();
	virtual Ems::Resourceapi::TEndpointContext::TTenant* __fastcall GetTenant();
	virtual Ems::Resourceapi::TEndpointNegotiation* __fastcall GetNegotiation();
	
public:
	__fastcall virtual ~TEndpointContextImpl();
	__property _di_TCreateUserCallback OnCreateUser = {read=FOnCreateUser, write=FOnCreateUser};
	__property _di_TCreateEdgemoduleCallback OnCreateEdgemodule = {read=FOnCreateEdgemodule, write=FOnCreateEdgemodule};
	__property _di_TGetRequestCallback OnGetRequest = {read=FOnGetRequest, write=FOnGetRequest};
	__property _di_TGetResponseCallback OnGetResponse = {read=FOnGetResponse, write=FOnGetResponse};
	__property _di_TGetAuthenticatedCallback OnGetAuthenticated = {read=FOnGetAuthenticated, write=FOnGetAuthenticated};
	__property _di_TGetEndpointNameCallback OnGetEndpointName = {read=FOnGetEndpointName, write=FOnGetEndpointName};
	__property _di_TGetTenantCallback OnGetTenant = {read=FOnGetTenant, write=FOnGetTenant};
	void __fastcall SetEndpointData(TEndpointDataType AStatus, const System::UnicodeString AValue);
	void __fastcall SetCreatorRequired();
	__property TEndpointDataType EndpointDataType = {read=FEndpointDataType, nodefault};
	__property System::UnicodeString EndpointDataValue = {read=FEndpontDataValue};
	__property bool CreatorRequired = {read=FCreatorRequired, nodefault};
public:
	/* TObject.Create */ inline __fastcall TEndpointContextImpl() : Ems::Resourceapi::TEndpointContext() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointRequestImpl : public Ems::Resourceapi::TEndpointRequest
{
	typedef Ems::Resourceapi::TEndpointRequest inherited;
	
	
private:
	typedef Ems::Resourceapi::TEndpointHeaders THeaders;
	
	typedef Ems::Resourceapi::TEndpointParams TParams;
	
	typedef Ems::Resourceapi::TEndpointRequestBody TBody;
	
	typedef Ems::Resourceapi::TEndpointSegments TSegments;
	
	
private:
	Emshosting::Requesttypes::_di_IEMSHostRequest FHostRequest;
	Ems::Resourceapi::TEndpointParams* FParams;
	Ems::Resourceapi::TEndpointHeaders* FHeaders;
	Ems::Resourceapi::TEndpointRequestBody* FBody;
	Ems::Resourceapi::TEndpointSegments* FSegments;
	
protected:
	virtual Ems::Resourceapi::TEndpointHeaders* __fastcall GetHeaders();
	virtual Ems::Resourceapi::TEndpointParams* __fastcall GetParams();
	virtual Ems::Resourceapi::TEndpointSegments* __fastcall GetSegments();
	virtual Ems::Resourceapi::TEndpointRequestBody* __fastcall GetBody();
	virtual Ems::Resourceapi::TEndpointRequest::TMethod __fastcall GetMethod();
	virtual System::UnicodeString __fastcall GetMethodString();
	virtual System::UnicodeString __fastcall GetResource();
	virtual System::UnicodeString __fastcall GetBasePath();
	virtual System::UnicodeString __fastcall GetServerHost();
	
public:
	__fastcall TEndpointRequestImpl(const Emshosting::Requesttypes::_di_IEMSHostRequest AHostRequest);
	__fastcall virtual ~TEndpointRequestImpl();
	__property Emshosting::Requesttypes::_di_IEMSHostRequest HostRequest = {read=FHostRequest};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointResponseImpl : public Ems::Resourceapi::TEndpointResponse
{
	typedef Ems::Resourceapi::TEndpointResponse inherited;
	
	
public:
	typedef Ems::Resourceapi::TEndpointHeaders THeaders;
	
	typedef Ems::Resourceapi::TEndpointResponseBody TBody;
	
	
private:
	Emshosting::Requesttypes::_di_IEMSHostResponse FHostResponse;
	Ems::Resourceapi::TEndpointHeaders* FHeaders;
	Ems::Resourceapi::TEndpointResponseBody* FBody;
	
protected:
	virtual Ems::Resourceapi::TEndpointHeaders* __fastcall GetHeaders();
	virtual Ems::Resourceapi::TEndpointResponseBody* __fastcall GetBody();
	virtual void __fastcall SetStatusCode(int ACode);
	
public:
	__fastcall TEndpointResponseImpl(const Emshosting::Requesttypes::_di_IEMSHostResponse AHostResponse);
	__fastcall virtual ~TEndpointResponseImpl();
	virtual void __fastcall SetCreated(const System::UnicodeString ALocation, int AStatusCode);
	void __fastcall Write();
	__property Emshosting::Requesttypes::_di_IEMSHostResponse HostResponse = {read=FHostResponse};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Endpoints */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_ENDPOINTS)
using namespace Emshosting::Endpoints;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_EndpointsHPP
