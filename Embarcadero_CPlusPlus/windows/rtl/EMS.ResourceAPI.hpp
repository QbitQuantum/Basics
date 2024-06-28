// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMS.ResourceAPI.pas' rev: 34.00 (Windows)

#ifndef Ems_ResourceapiHPP
#define Ems_ResourceapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <System.JSON.Writers.hpp>
#include <System.JSON.Readers.hpp>
#include <System.Net.Mime.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "EMS.ResourceAPI"

namespace Ems
{
namespace Resourceapi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMSResource;
class DELPHICLASS TEMSEndpointEnvironment;
class DELPHICLASS TEMSEndpointManager;
class DELPHICLASS TEMSEndpointAuthorization;
class DELPHICLASS TEndpointParams;
class DELPHICLASS TEndpointSegments;
class DELPHICLASS TEndpointHeaders;
class DELPHICLASS TEndpointRequestBody;
class DELPHICLASS TEndpointResponseBody;
class DELPHICLASS TEndpointNegotiation;
class DELPHICLASS TEndpointContext;
class DELPHICLASS TEndpointRequest;
class DELPHICLASS TEndpointResponse;
__interface DELPHIINTERFACE IEMSEndpointPublisher;
typedef System::DelphiInterface<IEMSEndpointPublisher> _di_IEMSEndpointPublisher;
class DELPHICLASS TEMSBaseResource;
class DELPHICLASS EEMSError;
class DELPHICLASS EEMSHTTPError;
class DELPHICLASS EEMSHTTPBadRequestError;
class DELPHICLASS EEMSHTTPResourceNotFoundError;
class DELPHICLASS EEMSHTTPDuplicateError;
class DELPHICLASS EEMSHTTPUnauthorizedError;
class DELPHICLASS EEMSHTTPForbiddenError;
class DELPHICLASS EEMSHTTPNotAcceptableError;
class DELPHICLASS EEMSHTTPUnsupportedMediaError;
class DELPHICLASS EEMSEndpointError;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSResource : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetName() = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<System::UnicodeString> __fastcall GetEndpointNames() = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<System::UnicodeString> __fastcall GetEndpointNames() = 0 ;
#endif /* _WIN64 */
	virtual void __fastcall DoHandleRequest(TEndpointContext* const AContext) = 0 ;
	virtual bool __fastcall DoCanHandleRequest(TEndpointContext* const AContext, /* out */ System::UnicodeString &AEndpointName) = 0 ;
	
public:
	__property System::UnicodeString Name = {read=GetName};
#ifndef _WIN64
	__property System::DynamicArray<System::UnicodeString> EndpointNames = {read=GetEndpointNames};
#else /* _WIN64 */
	__property System::TArray__1<System::UnicodeString> EndpointNames = {read=GetEndpointNames};
#endif /* _WIN64 */
	virtual bool __fastcall IsBaseURL(const System::UnicodeString ABaseURL);
	void __fastcall HandleRequest(TEndpointContext* const AContext);
	bool __fastcall CanHandleRequest(TEndpointContext* const AContext, /* out */ System::UnicodeString &AEndpointName);
	virtual void __fastcall Log(System::Json::TJSONObject* AJSON);
public:
	/* TObject.Create */ inline __fastcall TEMSResource() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSResource() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndpointEnvironment : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TEMSEndpointEnvironment* FInstance;
	static TEMSEndpointEnvironment* __fastcall GetInstance();
	
protected:
	static System::DelphiInterface<System::Sysutils::TFunc__1<TEMSEndpointEnvironment*> > FEnvironmentFactory;
	virtual bool __fastcall GetMultiTenantMode();
	
public:
	__fastcall virtual ~TEMSEndpointEnvironment();
	virtual void __fastcall LogMessage(const System::UnicodeString AMessage)/* overload */;
	__property bool MultiTenantMode = {read=GetMultiTenantMode, nodefault};
	/* static */ __property TEMSEndpointEnvironment* Instance = {read=GetInstance};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TEMSEndpointEnvironment() : System::TObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndpointManager : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TEMSEndpointManager* FInstance;
	static TEMSEndpointManager* __fastcall GetInstance();
	
protected:
	static System::DelphiInterface<System::Sysutils::TFunc__1<TEMSEndpointManager*> > FEndpointManagerFactory;
#ifndef _WIN64
	virtual System::DynamicArray<TEMSResource*> __fastcall GetResources() = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<TEMSResource*> __fastcall GetResources() = 0 ;
#endif /* _WIN64 */
	
public:
	__fastcall virtual ~TEMSEndpointManager();
	virtual void __fastcall RegisterResource(TEMSResource* const AResource) = 0 ;
#ifndef _WIN64
	__property System::DynamicArray<TEMSResource*> Resources = {read=GetResources};
#else /* _WIN64 */
	__property System::TArray__1<TEMSResource*> Resources = {read=GetResources};
#endif /* _WIN64 */
	/* static */ __property TEMSEndpointManager* Instance = {read=GetInstance};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TEMSEndpointManager() : System::TObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndpointAuthorization : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	class DELPHICLASS TACL;
	class PASCALIMPLEMENTATION TACL : public System::TObject
	{
		typedef System::TObject inherited;
		
	protected:
		virtual bool __fastcall GetPublic() = 0 ;
#ifndef _WIN64
		virtual System::DynamicArray<System::UnicodeString> __fastcall GetGroups() = 0 ;
		virtual System::DynamicArray<System::UnicodeString> __fastcall GetUsers() = 0 ;
#else /* _WIN64 */
		virtual System::TArray__1<System::UnicodeString> __fastcall GetGroups() = 0 ;
		virtual System::TArray__1<System::UnicodeString> __fastcall GetUsers() = 0 ;
#endif /* _WIN64 */
		virtual bool __fastcall GetAllowCreator() = 0 ;
		
	public:
		__property bool IsPublic = {read=GetPublic, nodefault};
#ifndef _WIN64
		__property System::DynamicArray<System::UnicodeString> Users = {read=GetUsers};
		__property System::DynamicArray<System::UnicodeString> Groups = {read=GetGroups};
#else /* _WIN64 */
		__property System::TArray__1<System::UnicodeString> Users = {read=GetUsers};
		__property System::TArray__1<System::UnicodeString> Groups = {read=GetGroups};
#endif /* _WIN64 */
		__property bool AllowCreator = {read=GetAllowCreator, nodefault};
	public:
		/* TObject.Create */ inline __fastcall TACL() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TACL() { }
		
	};
	
	
	
private:
	static TEMSEndpointAuthorization* FInstance;
	static TEMSEndpointAuthorization* __fastcall GetInstance();
	
protected:
	static System::DelphiInterface<System::Sysutils::TFunc__1<TEMSEndpointAuthorization*> > FEndpointAuthorizationFactory;
	
public:
	__fastcall virtual ~TEMSEndpointAuthorization();
	virtual void __fastcall Authorize(TEndpointContext* const AContext, TACL* const AACL) = 0 ;
	virtual bool __fastcall FindACL(const System::UnicodeString AName, /* out */ TACL* &AACL) = 0 ;
	/* static */ __property TEMSEndpointAuthorization* Instance = {read=GetInstance};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TEMSEndpointAuthorization() : System::TObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointParams : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> TPairItem;
	
	class DELPHICLASS TEnumerator;
	class PASCALIMPLEMENTATION TEnumerator : public System::Generics::Collections::TEnumerator__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> >
	{
		typedef System::Generics::Collections::TEnumerator__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > inherited;
		
	private:
		TEndpointParams* FParams;
		int FIndex;
		
	protected:
		virtual System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> __fastcall DoGetCurrent();
		virtual bool __fastcall DoMoveNext();
		
	public:
		__fastcall TEnumerator(TEndpointParams* const AParams);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TEnumerator() { }
		
	};
	
	
	
protected:
	virtual int __fastcall GetCount() = 0 ;
	virtual System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> __fastcall GetPair(const int Index) = 0 ;
	System::UnicodeString __fastcall GetValue(const System::UnicodeString AName);
	virtual void __fastcall DoAdd(const System::UnicodeString AName, const System::UnicodeString AValue);
	
public:
	System::Generics::Collections::TEnumerator__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> >* __fastcall GetEnumerator();
	virtual bool __fastcall TryGetValue(const System::UnicodeString AName, /* out */ System::UnicodeString &AValue) = 0 ;
	virtual bool __fastcall Contains(const System::UnicodeString AName) = 0 ;
	__property int Count = {read=GetCount, nodefault};
	__property System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> Pairs[const int Index] = {read=GetPair};
	__property System::UnicodeString Values[const System::UnicodeString Name] = {read=GetValue};
	void __fastcall Add(const System::UnicodeString AName, const System::UnicodeString AValue);
#ifndef _WIN64
	System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall ToArray();
#else /* _WIN64 */
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall ToArray();
#endif /* _WIN64 */
public:
	/* TObject.Create */ inline __fastcall TEndpointParams() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointParams() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointSegments : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	class DELPHICLASS TEnumerator;
	class PASCALIMPLEMENTATION TEnumerator : public System::Generics::Collections::TEnumerator__1<System::UnicodeString>
	{
		typedef System::Generics::Collections::TEnumerator__1<System::UnicodeString> inherited;
		
	private:
		TEndpointSegments* FSegments;
		int FIndex;
		
	protected:
		virtual System::UnicodeString __fastcall DoGetCurrent();
		virtual bool __fastcall DoMoveNext();
		
	public:
		__fastcall TEnumerator(TEndpointSegments* const ASegments);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TEnumerator() { }
		
	};
	
	
	
public:
	System::UnicodeString operator[](const int AIndex) { return this->Items[AIndex]; }
	
protected:
	virtual int __fastcall GetCount() = 0 ;
	virtual System::UnicodeString __fastcall GetItem(const int AIndex) = 0 ;
	virtual void __fastcall DoAdd(const System::UnicodeString AName);
	
public:
	System::Generics::Collections::TEnumerator__1<System::UnicodeString>* __fastcall GetEnumerator();
	__property int Count = {read=GetCount, nodefault};
	__property System::UnicodeString Items[const int AIndex] = {read=GetItem/*, default*/};
	void __fastcall Add(const System::UnicodeString AName);
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall ToArray();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall ToArray();
#endif /* _WIN64 */
public:
	/* TObject.Create */ inline __fastcall TEndpointSegments() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointSegments() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointHeaders : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual void __fastcall DoSetValue(const System::UnicodeString AName, const System::UnicodeString AValue);
	
public:
	virtual bool __fastcall TryGetValue(const System::UnicodeString AName, /* out */ System::UnicodeString &AValue) = 0 ;
	System::UnicodeString __fastcall GetValue(const System::UnicodeString AName);
	void __fastcall SetValue(const System::UnicodeString AName, const System::UnicodeString AValue);
public:
	/* TObject.Create */ inline __fastcall TEndpointHeaders() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointHeaders() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointRequestBody : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetContentType() = 0 ;
	virtual System::Json::Readers::TJsonTextReader* __fastcall GetJSONReader() = 0 ;
	
public:
	virtual bool __fastcall TryGetStream(/* out */ System::Classes::TStream* &AStream) = 0 /* overload */;
	virtual bool __fastcall TryGetStream(/* out */ System::Classes::TStream* &AStream, /* out */ System::UnicodeString &AContentType) = 0 /* overload */;
	virtual bool __fastcall TryGetObject(/* out */ System::Json::TJSONObject* &AJSONObject) = 0 ;
	virtual bool __fastcall TryGetArray(/* out */ System::Json::TJSONArray* &AJSONArray) = 0 ;
	virtual bool __fastcall TryGetValue(/* out */ System::Json::TJSONValue* &AJSONValue) = 0 ;
#ifndef _WIN64
	virtual bool __fastcall TryGetBytes(/* out */ System::DynamicArray<System::Byte> &ABytes) = 0 ;
#else /* _WIN64 */
	virtual bool __fastcall TryGetBytes(/* out */ System::TArray__1<System::Byte> &ABytes) = 0 ;
#endif /* _WIN64 */
	System::Classes::TStream* __fastcall GetStream();
	System::Json::TJSONObject* __fastcall GetObject();
	System::Json::TJSONArray* __fastcall GetArray();
	System::Json::TJSONValue* __fastcall GetValue();
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall GetBytes();
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall GetBytes();
#endif /* _WIN64 */
	__property System::UnicodeString ContentType = {read=GetContentType};
	__property System::Json::Readers::TJsonTextReader* JSONReader = {read=GetJSONReader};
public:
	/* TObject.Create */ inline __fastcall TEndpointRequestBody() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointRequestBody() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointResponseBody : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::Json::Writers::TJsonTextWriter* __fastcall GetJSONWriter() = 0 ;
	
public:
	virtual void __fastcall SetValue(System::Json::TJSONValue* const AJSONValue, bool AOwnsValue) = 0 ;
#ifndef _WIN64
	virtual void __fastcall SetBytes(const System::DynamicArray<System::Byte> ABytes, const System::UnicodeString AContentType) = 0 ;
#else /* _WIN64 */
	virtual void __fastcall SetBytes(const System::TArray__1<System::Byte> ABytes, const System::UnicodeString AContentType) = 0 ;
#endif /* _WIN64 */
	virtual void __fastcall SetStream(System::Classes::TStream* const AStream, const System::UnicodeString AContentType, bool AOwnsValue) = 0 ;
	__property System::Json::Writers::TJsonTextWriter* JSONWriter = {read=GetJSONWriter};
public:
	/* TObject.Create */ inline __fastcall TEndpointResponseBody() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointResponseBody() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointNegotiation : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* __fastcall GetConsumeList() = 0 ;
	virtual System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* __fastcall GetProduceList() = 0 ;
	
public:
	__property System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* ConsumeList = {read=GetConsumeList};
	__property System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* ProduceList = {read=GetProduceList};
public:
	/* TObject.Create */ inline __fastcall TEndpointNegotiation() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointNegotiation() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointContext : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	class DELPHICLASS TGroups;
	class PASCALIMPLEMENTATION TGroups : public System::TObject
	{
		typedef System::TObject inherited;
		
	protected:
		virtual int __fastcall GetCount() = 0 ;
		
	public:
		virtual bool __fastcall Contains(const System::UnicodeString AGroup) = 0 ;
		__property int Count = {read=GetCount, nodefault};
	public:
		/* TObject.Create */ inline __fastcall TGroups() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TGroups() { }
		
	};
	
	
	class DELPHICLASS TUser;
	class PASCALIMPLEMENTATION TUser : public System::TObject
	{
		typedef System::TObject inherited;
		
	protected:
		virtual System::UnicodeString __fastcall GetUserName() = 0 ;
		virtual System::UnicodeString __fastcall GetUserID() = 0 ;
		virtual System::UnicodeString __fastcall GetSessionToken() = 0 ;
		virtual TEndpointContext::TGroups* __fastcall GetGroups() = 0 ;
		
	public:
		__property System::UnicodeString UserName = {read=GetUserName};
		__property System::UnicodeString UserID = {read=GetUserID};
		__property System::UnicodeString SessionToken = {read=GetSessionToken};
		__property TEndpointContext::TGroups* Groups = {read=GetGroups};
	public:
		/* TObject.Create */ inline __fastcall TUser() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TUser() { }
		
	};
	
	
	class DELPHICLASS TEdgemodule;
	class PASCALIMPLEMENTATION TEdgemodule : public System::TObject
	{
		typedef System::TObject inherited;
		
	protected:
		virtual System::UnicodeString __fastcall GetModuleName() = 0 ;
		virtual System::UnicodeString __fastcall GetModuleVersion() = 0 ;
		
	public:
		__property System::UnicodeString ModuleName = {read=GetModuleName};
		__property System::UnicodeString ModuleVersion = {read=GetModuleVersion};
	public:
		/* TObject.Create */ inline __fastcall TEdgemodule() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TEdgemodule() { }
		
	};
	
	
	class DELPHICLASS TTenant;
	class PASCALIMPLEMENTATION TTenant : public System::TObject
	{
		typedef System::TObject inherited;
		
	protected:
		virtual System::UnicodeString __fastcall GetTenantId() = 0 ;
		virtual System::UnicodeString __fastcall GetTenantName() = 0 ;
		
	public:
		__property System::UnicodeString Id = {read=GetTenantId};
		__property System::UnicodeString TenantName = {read=GetTenantName};
	public:
		/* TObject.Create */ inline __fastcall TTenant() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TTenant() { }
		
	};
	
	
	enum class DECLSPEC_DENUM TAuthenticate : unsigned char { MasterSecret, AppSecret, User, Tenant };
	
	typedef System::Set<TAuthenticate, _DELPHI_SET_ENUMERATOR(TAuthenticate::MasterSecret), _DELPHI_SET_ENUMERATOR(TAuthenticate::Tenant)> TAuthenticated;
	
	
protected:
	virtual TUser* __fastcall GetUser() = 0 ;
	virtual TEdgemodule* __fastcall GetEdgemodule() = 0 ;
	virtual TAuthenticated __fastcall GetAuthenticated() = 0 ;
	virtual TEndpointRequest* __fastcall GetRequest() = 0 ;
	virtual TEndpointResponse* __fastcall GetResponse() = 0 ;
	virtual System::UnicodeString __fastcall GetEndpointName() = 0 ;
	virtual TTenant* __fastcall GetTenant() = 0 ;
	virtual TEndpointNegotiation* __fastcall GetNegotiation() = 0 ;
	
public:
	__property TUser* User = {read=GetUser};
	__property System::UnicodeString EndpointName = {read=GetEndpointName};
	__property TEdgemodule* Edgemodule = {read=GetEdgemodule};
	__property TAuthenticated Authenticated = {read=GetAuthenticated, nodefault};
	__property TEndpointRequest* Request = {read=GetRequest};
	__property TEndpointResponse* Response = {read=GetResponse};
	__property TTenant* Tenant = {read=GetTenant};
	__property TEndpointNegotiation* Negotiation = {read=GetNegotiation};
public:
	/* TObject.Create */ inline __fastcall TEndpointContext() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointContext() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointRequest : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TMethod : unsigned char { Get, Put, Post, Head, Delete, Patch, Other };
	
	typedef TEndpointHeaders THeaders;
	
	typedef TEndpointParams TParams;
	
	typedef TEndpointSegments TSegments;
	
	typedef TEndpointRequestBody TBody;
	
	
protected:
	virtual TEndpointHeaders* __fastcall GetHeaders() = 0 ;
	virtual TEndpointParams* __fastcall GetParams() = 0 ;
	virtual TEndpointSegments* __fastcall GetSegments() = 0 ;
	virtual TEndpointRequestBody* __fastcall GetBody() = 0 ;
	virtual TMethod __fastcall GetMethod() = 0 ;
	virtual System::UnicodeString __fastcall GetMethodString() = 0 ;
	virtual System::UnicodeString __fastcall GetResource() = 0 ;
	virtual System::UnicodeString __fastcall GetBasePath() = 0 ;
	virtual System::UnicodeString __fastcall GetServerHost() = 0 ;
	
public:
	__property TEndpointRequestBody* Body = {read=GetBody};
	__property TEndpointHeaders* Headers = {read=GetHeaders};
	__property TMethod Method = {read=GetMethod, nodefault};
	__property System::UnicodeString MethodString = {read=GetMethodString};
	__property TEndpointParams* Params = {read=GetParams};
	__property TEndpointSegments* Segments = {read=GetSegments};
	__property System::UnicodeString Resource = {read=GetResource};
	__property System::UnicodeString BasePath = {read=GetBasePath};
	__property System::UnicodeString ServerHost = {read=GetServerHost};
public:
	/* TObject.Create */ inline __fastcall TEndpointRequest() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointRequest() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointResponse : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef TEndpointHeaders THeaders;
	
	typedef TEndpointResponseBody TBody;
	
	
protected:
	virtual TEndpointHeaders* __fastcall GetHeaders() = 0 ;
	virtual TEndpointResponseBody* __fastcall GetBody() = 0 ;
	virtual void __fastcall SetStatusCode(int ACode) = 0 ;
	
public:
	virtual void __fastcall SetCreated(const System::UnicodeString ALocation, int AStatusCode = 0xc9) = 0 ;
	void __fastcall RaiseError(int ACode, const System::UnicodeString AError, const System::UnicodeString ADescription);
	void __fastcall RaiseNotFound(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	void __fastcall RaiseBadRequest(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	void __fastcall RaiseDuplicate(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	void __fastcall RaiseForbidden(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	void __fastcall RaiseUnauthorized(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	void __fastcall RaiseNotAcceptable(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	void __fastcall RaiseUnsupportedMedia(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	__property TEndpointResponseBody* Body = {read=GetBody};
	__property TEndpointHeaders* Headers = {read=GetHeaders};
	__property int StatusCode = {write=SetStatusCode, nodefault};
public:
	/* TObject.Create */ inline __fastcall TEndpointResponse() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointResponse() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{3CECB155-07D2-42CB-918E-27695972F1E3}") IEMSEndpointPublisher  : public System::IInterface 
{
	
};

class PASCALIMPLEMENTATION TEMSBaseResource : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
public:
	enum class DECLSPEC_DENUM TAction : unsigned char { List, Get, Post, Put, Delete };
	
	typedef System::Set<TAction, _DELPHI_SET_ENUMERATOR(TAction::List), _DELPHI_SET_ENUMERATOR(TAction::Delete)> TActions;
	
	typedef void __fastcall (__closure *TGetParam)(System::TObject* ASender, const System::UnicodeString AName, System::UnicodeString &AValue, bool &AHasValue);
	
	enum class DECLSPEC_DENUM TParamMode : unsigned char { Mixed, ByName, ByNumber };
	
	
private:
	TActions FAllowedActions;
	TGetParam FOnGetParam;
	TParamMode FParamBindMode;
	
protected:
	virtual void __fastcall CheckAction(TEndpointContext* const AContext, TAction AAction);
	virtual void __fastcall DoGetParam(const System::UnicodeString AName, System::UnicodeString &AValue, bool &AHasValue);
	virtual bool __fastcall DoExcludeParam(const System::UnicodeString AName);
	System::UnicodeString __fastcall GetParamValue(TEndpointContext* AContext, const System::UnicodeString AName, int AIndex);
	virtual void __fastcall List(TEndpointContext* const AContext, TEndpointRequest* const ARequest, TEndpointResponse* const AResponse);
	virtual void __fastcall Get(TEndpointContext* const AContext, TEndpointRequest* const ARequest, TEndpointResponse* const AResponse);
	virtual void __fastcall Put(TEndpointContext* const AContext, TEndpointRequest* const ARequest, TEndpointResponse* const AResponse);
	virtual void __fastcall Post(TEndpointContext* const AContext, TEndpointRequest* const ARequest, TEndpointResponse* const AResponse);
	virtual void __fastcall Delete(TEndpointContext* const AContext, TEndpointRequest* const ARequest, TEndpointResponse* const AResponse);
	
public:
	__fastcall virtual TEMSBaseResource(System::Classes::TComponent* AOwner);
	
__published:
	__property TActions AllowedActions = {read=FAllowedActions, write=FAllowedActions, default=2};
	__property TParamMode ParamBindMode = {read=FParamBindMode, write=FParamBindMode, default=0};
	__property TGetParam OnGetParam = {read=FOnGetParam, write=FOnGetParam};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TEMSBaseResource() { }
	
private:
	void *__IEMSEndpointPublisher;	// IEMSEndpointPublisher 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3CECB155-07D2-42CB-918E-27695972F1E3}
	operator _di_IEMSEndpointPublisher()
	{
		_di_IEMSEndpointPublisher intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IEMSEndpointPublisher*(void) { return (IEMSEndpointPublisher*)&__IEMSEndpointPublisher; }
	#endif
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EEMSError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EEMSError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSHTTPError : public EEMSError
{
	typedef EEMSError inherited;
	
	
public:
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TCodes
	{
	public:
		static const System::Word BadRequest = System::Word(0x190);
		
		static const System::Word NotFound = System::Word(0x194);
		
		static const System::Word Duplicate = System::Word(0x199);
		
		static const System::Word Unauthorized = System::Word(0x191);
		
		static const System::Word Forbidden = System::Word(0x193);
		
		static const System::Word NotAcceptable = System::Word(0x196);
		
		static const System::Word UnsupportedMedia = System::Word(0x19f);
		
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	
private:
	int FCode;
	System::UnicodeString FDescription;
	int __fastcall GetCode();
	System::UnicodeString __fastcall GetError();
	
public:
	static void __fastcall RaiseError(int ACode, const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	static void __fastcall RaiseDuplicate(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	static void __fastcall RaiseNotFound(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	static void __fastcall RaiseBadRequest(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	static void __fastcall RaiseUnauthorized(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	static void __fastcall RaiseForbidden(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	static void __fastcall RaiseNotAcceptable(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	static void __fastcall RaiseUnsupportedMedia(const System::UnicodeString AError = System::UnicodeString(), const System::UnicodeString ADescription = System::UnicodeString());
	__fastcall EEMSHTTPError(int ACode, const System::UnicodeString AError, const System::UnicodeString ADescription);
	__property int Code = {read=GetCode, nodefault};
	__property System::UnicodeString Description = {read=FDescription};
	__property System::UnicodeString Error = {read=GetError};
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSHTTPError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPError(NativeUInt Ident)/* overload */ : EEMSError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPError(System::PResStringRec ResStringRec)/* overload */ : EEMSError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSHTTPError(const System::UnicodeString Msg, int AHelpContext) : EEMSError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSHTTPError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPError(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSHTTPError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSHTTPBadRequestError : public EEMSHTTPError
{
	typedef EEMSHTTPError inherited;
	
public:
	__fastcall EEMSHTTPBadRequestError(const System::UnicodeString AError, const System::UnicodeString ADescription);
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSHTTPBadRequestError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPBadRequestError(NativeUInt Ident)/* overload */ : EEMSHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPBadRequestError(System::PResStringRec ResStringRec)/* overload */ : EEMSHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPBadRequestError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPBadRequestError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSHTTPBadRequestError(const System::UnicodeString Msg, int AHelpContext) : EEMSHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSHTTPBadRequestError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPBadRequestError(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPBadRequestError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPBadRequestError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPBadRequestError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSHTTPBadRequestError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSHTTPResourceNotFoundError : public EEMSHTTPError
{
	typedef EEMSHTTPError inherited;
	
public:
	__fastcall EEMSHTTPResourceNotFoundError(const System::UnicodeString AError, const System::UnicodeString ADescription);
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSHTTPResourceNotFoundError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPResourceNotFoundError(NativeUInt Ident)/* overload */ : EEMSHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPResourceNotFoundError(System::PResStringRec ResStringRec)/* overload */ : EEMSHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPResourceNotFoundError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPResourceNotFoundError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSHTTPResourceNotFoundError(const System::UnicodeString Msg, int AHelpContext) : EEMSHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSHTTPResourceNotFoundError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPResourceNotFoundError(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPResourceNotFoundError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPResourceNotFoundError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPResourceNotFoundError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSHTTPResourceNotFoundError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSHTTPDuplicateError : public EEMSHTTPError
{
	typedef EEMSHTTPError inherited;
	
public:
	__fastcall EEMSHTTPDuplicateError(const System::UnicodeString AError, const System::UnicodeString ADescription);
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSHTTPDuplicateError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPDuplicateError(NativeUInt Ident)/* overload */ : EEMSHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPDuplicateError(System::PResStringRec ResStringRec)/* overload */ : EEMSHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPDuplicateError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPDuplicateError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSHTTPDuplicateError(const System::UnicodeString Msg, int AHelpContext) : EEMSHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSHTTPDuplicateError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPDuplicateError(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPDuplicateError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPDuplicateError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPDuplicateError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSHTTPDuplicateError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSHTTPUnauthorizedError : public EEMSHTTPError
{
	typedef EEMSHTTPError inherited;
	
public:
	__fastcall EEMSHTTPUnauthorizedError(const System::UnicodeString AError, const System::UnicodeString ADescription);
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSHTTPUnauthorizedError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPUnauthorizedError(NativeUInt Ident)/* overload */ : EEMSHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPUnauthorizedError(System::PResStringRec ResStringRec)/* overload */ : EEMSHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPUnauthorizedError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPUnauthorizedError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSHTTPUnauthorizedError(const System::UnicodeString Msg, int AHelpContext) : EEMSHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSHTTPUnauthorizedError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPUnauthorizedError(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPUnauthorizedError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPUnauthorizedError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPUnauthorizedError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSHTTPUnauthorizedError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSHTTPForbiddenError : public EEMSHTTPError
{
	typedef EEMSHTTPError inherited;
	
public:
	__fastcall EEMSHTTPForbiddenError(const System::UnicodeString AError, const System::UnicodeString ADescription);
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSHTTPForbiddenError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPForbiddenError(NativeUInt Ident)/* overload */ : EEMSHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPForbiddenError(System::PResStringRec ResStringRec)/* overload */ : EEMSHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPForbiddenError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPForbiddenError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSHTTPForbiddenError(const System::UnicodeString Msg, int AHelpContext) : EEMSHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSHTTPForbiddenError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPForbiddenError(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPForbiddenError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPForbiddenError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPForbiddenError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSHTTPForbiddenError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSHTTPNotAcceptableError : public EEMSHTTPError
{
	typedef EEMSHTTPError inherited;
	
public:
	__fastcall EEMSHTTPNotAcceptableError(const System::UnicodeString AError, const System::UnicodeString ADescription);
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSHTTPNotAcceptableError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPNotAcceptableError(NativeUInt Ident)/* overload */ : EEMSHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPNotAcceptableError(System::PResStringRec ResStringRec)/* overload */ : EEMSHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPNotAcceptableError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPNotAcceptableError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSHTTPNotAcceptableError(const System::UnicodeString Msg, int AHelpContext) : EEMSHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSHTTPNotAcceptableError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPNotAcceptableError(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPNotAcceptableError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPNotAcceptableError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPNotAcceptableError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSHTTPNotAcceptableError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSHTTPUnsupportedMediaError : public EEMSHTTPError
{
	typedef EEMSHTTPError inherited;
	
public:
	__fastcall EEMSHTTPUnsupportedMediaError(const System::UnicodeString AError, const System::UnicodeString ADescription);
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSHTTPUnsupportedMediaError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPUnsupportedMediaError(NativeUInt Ident)/* overload */ : EEMSHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSHTTPUnsupportedMediaError(System::PResStringRec ResStringRec)/* overload */ : EEMSHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPUnsupportedMediaError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSHTTPUnsupportedMediaError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSHTTPUnsupportedMediaError(const System::UnicodeString Msg, int AHelpContext) : EEMSHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSHTTPUnsupportedMediaError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPUnsupportedMediaError(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSHTTPUnsupportedMediaError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPUnsupportedMediaError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSHTTPUnsupportedMediaError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSHTTPUnsupportedMediaError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSEndpointError : public EEMSError
{
	typedef EEMSError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EEMSEndpointError(const System::UnicodeString Msg) : EEMSError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EEMSEndpointError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSEndpointError(NativeUInt Ident)/* overload */ : EEMSError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSEndpointError(System::PResStringRec ResStringRec)/* overload */ : EEMSError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSEndpointError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSEndpointError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSEndpointError(const System::UnicodeString Msg, int AHelpContext) : EEMSError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSEndpointError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSEndpointError(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSEndpointError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSEndpointError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSEndpointError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSEndpointError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterResource(TEMSResource* const AResource)/* overload */;
}	/* namespace Resourceapi */
}	/* namespace Ems */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMS_RESOURCEAPI)
using namespace Ems::Resourceapi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMS)
using namespace Ems;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ems_ResourceapiHPP
