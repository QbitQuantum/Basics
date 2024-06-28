// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMS.ResourceTypes.pas' rev: 34.00 (Windows)

#ifndef Ems_ResourcetypesHPP
#define Ems_ResourcetypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include <System.TypInfo.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <EMS.ResourceAPI.hpp>
#include <System.JSON.hpp>
#include <System.JSON.Writers.hpp>
#include <System.JSON.Builders.hpp>
#include <System.Net.Mime.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ems
{
namespace Resourcetypes
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TResourceCustomAttribute;
class DELPHICLASS TEndpointCustomAttribute;
class DELPHICLASS TEMSCommonResource;
class DELPHICLASS TEMSResourceEndPoint;
class DELPHICLASS TEMSEndpointSegmentList;
class DELPHICLASS TEMSEndpointSegment;
class DELPHICLASS TEMSEndPointSegmentParameter;
class DELPHICLASS TEMSResourceEndPointSuffix;
class DELPHICLASS TEMSEndPointSegmentSlash;
class DELPHICLASS TEMSEndPointSegmentWildCard;
class DELPHICLASS TEMSEndPointSegmentConstant;
class DELPHICLASS TEMSEndPointSegmentService;
class DELPHICLASS TEMSBasicResource;
class DELPHICLASS ResourceSuffixAttribute;
class DELPHICLASS ResourceNameAttribute;
class DELPHICLASS EndpointNameAttribute;
class DELPHICLASS TResourceStringsTable;
class DELPHICLASS TAPIDoc;
class DELPHICLASS TAPIDocPath;
class DELPHICLASS TAPIDocPathItem;
class DELPHICLASS TAPIDocParameter;
class DELPHICLASS TAPIDocResponse;
class DELPHICLASS EndPointRequestSummaryAttribute;
class DELPHICLASS EndPointRequestParameterAttribute;
class DELPHICLASS EndPointResponseDetailsAttribute;
class DELPHICLASS EndPointObjectsYAMLDefinitionsAttribute;
class DELPHICLASS EndPointObjectsJSONDefinitionsAttribute;
class DELPHICLASS AllowAnonymousTenantAttribute;
class DELPHICLASS EndPointProduceAttribute;
class DELPHICLASS EndPointConsumeAttribute;
class DELPHICLASS EndPointMethodAttribute;
class DELPHICLASS TEMSTypeInfoResource;
class DELPHICLASS TEMSResourceAttributes;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TResourceCustomAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
public:
	/* TObject.Create */ inline __fastcall TResourceCustomAttribute() : System::TCustomAttribute() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TResourceCustomAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEndpointCustomAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	System::UnicodeString FMethod;
	
protected:
	__fastcall TEndpointCustomAttribute(const System::UnicodeString AMethod)/* overload */;
	
public:
	__property System::UnicodeString Method = {read=FMethod};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TEndpointCustomAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSCommonResource : public Ems::Resourceapi::TEMSResource
{
	typedef Ems::Resourceapi::TEMSResource inherited;
	
	
private:
	__interface DELPHIINTERFACE TFindCallback;
	typedef System::DelphiInterface<TFindCallback> _di_TFindCallback;
	__interface TFindCallback  : public System::IInterface 
	{
		virtual void __fastcall Invoke(TEMSResourceEndPoint* const AEndPoint, bool &ADone) = 0 ;
	};
	
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TLeafEndpoint
	{
	public:
		System::UnicodeString EndpointName;
		int Score;
		__fastcall TLeafEndpoint(const System::UnicodeString AEndpointName, int AScore);
		TLeafEndpoint() {}
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	class DELPHICLASS TTreeNode;
	class PASCALIMPLEMENTATION TTreeNode : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		Ems::Resourceapi::TEndpointRequest::TMethod FMethod;
		TEMSEndpointSegment* FSegment;
		System::Generics::Collections::TList__1<TEMSCommonResource::TTreeNode*>* FChildNodes;
		System::Generics::Collections::TList__1<TEMSCommonResource::TLeafEndpoint>* FLeafEndpoints;
#ifndef _WIN64
		System::DynamicArray<TEMSCommonResource::TTreeNode*> __fastcall GetChildNodes();
		System::DynamicArray<TEMSCommonResource::TLeafEndpoint> __fastcall GetLeafEndpoints();
#else /* _WIN64 */
		System::TArray__1<TEMSCommonResource::TTreeNode*> __fastcall GetChildNodes();
		System::TArray__1<TEMSCommonResource::TLeafEndpoint> __fastcall GetLeafEndpoints();
#endif /* _WIN64 */
		
	public:
		__fastcall TTreeNode(Ems::Resourceapi::TEndpointRequest::TMethod AMethod, TEMSEndpointSegment* const ASegment);
		__fastcall virtual ~TTreeNode();
		void __fastcall AddChildNode(TEMSCommonResource::TTreeNode* const ANode);
		void __fastcall AddTerminalEndpoint(const System::UnicodeString AEndpointName, int AScore);
		__property Ems::Resourceapi::TEndpointRequest::TMethod Method = {read=FMethod, nodefault};
		__property TEMSEndpointSegment* Segment = {read=FSegment};
#ifndef _WIN64
		__property System::DynamicArray<TEMSCommonResource::TTreeNode*> ChildNodes = {read=GetChildNodes};
		__property System::DynamicArray<TEMSCommonResource::TLeafEndpoint> LeafEndpoints = {read=GetLeafEndpoints};
#else /* _WIN64 */
		__property System::TArray__1<TEMSCommonResource::TTreeNode*> ChildNodes = {read=GetChildNodes};
		__property System::TArray__1<TEMSCommonResource::TLeafEndpoint> LeafEndpoints = {read=GetLeafEndpoints};
#endif /* _WIN64 */
	};
	
	
	class DELPHICLASS TNegotiator;
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TNegotiator : public System::TObject
	{
		typedef System::TObject inherited;
		
		
	public:
		enum class DECLSPEC_DENUM TStatus : unsigned char { Nothing, Failed, Duplicates, OK };
		
		
	private:
		Ems::Resourceapi::TEndpointContext* FContext;
		System::Generics::Collections::TList__1<TEMSResourceEndPoint*>* FBestEndpoints;
		double FBestWeight;
		int FChooseCount;
		TStatus __fastcall GetStatus();
		TEMSResourceEndPoint* __fastcall GetBestEndpoint();
		System::UnicodeString __fastcall GetDuplicateNames();
		
	public:
		__fastcall TNegotiator(Ems::Resourceapi::TEndpointContext* AContext);
		__fastcall virtual ~TNegotiator();
		void __fastcall Reset();
		void __fastcall Choose(TEMSResourceEndPoint* AEndpoint, int AScore);
		__property TStatus Status = {read=GetStatus, nodefault};
		__property TEMSResourceEndPoint* BestEndpoint = {read=GetBestEndpoint};
		__property double BestWeight = {read=FBestWeight};
		__property System::UnicodeString DuplicateNames = {read=GetDuplicateNames};
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	System::Generics::Collections::TList__1<TEMSResourceEndPoint*>* FEndpoints;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TEMSResourceEndPoint*>* FEndpointsDict;
	System::UnicodeString FBaseURL;
	System::UnicodeString FResourceName;
	int FBaseURLSegmentCount;
	TTreeNode* FRootNode;
	bool __fastcall EnumEndPoints(const _di_TFindCallback ACallback);
	TEMSResourceEndPoint* __fastcall FindEndPoint(const System::UnicodeString AName);
	void __fastcall BuildTree();
	void __fastcall SearchTree(Ems::Resourceapi::TEndpointContext* const AContext, int ARequestSegmentIndex, TTreeNode* const ATreeNode, System::Generics::Collections::TList__1<TTreeNode*>* const ATerminalNodes, Ems::Resourceapi::TEndpointRequest::TMethod AMethod)/* overload */;
#ifndef _WIN64
	void __fastcall SearchTree(Ems::Resourceapi::TEndpointContext* const AContext, /* out */ System::DynamicArray<TTreeNode*> &ATerminalNodes, Ems::Resourceapi::TEndpointRequest::TMethod AMethod)/* overload */;
#else /* _WIN64 */
	void __fastcall SearchTree(Ems::Resourceapi::TEndpointContext* const AContext, /* out */ System::TArray__1<TTreeNode*> &ATerminalNodes, Ems::Resourceapi::TEndpointRequest::TMethod AMethod)/* overload */;
#endif /* _WIN64 */
	
protected:
	virtual void __fastcall DoHandleRequest(Ems::Resourceapi::TEndpointContext* const AContext);
	virtual bool __fastcall DoCanHandleRequest(Ems::Resourceapi::TEndpointContext* const AContext, /* out */ System::UnicodeString &AEndpointName);
	virtual System::UnicodeString __fastcall GetName();
#ifndef _WIN64
	virtual System::DynamicArray<System::UnicodeString> __fastcall GetEndpointNames();
#else /* _WIN64 */
	virtual System::TArray__1<System::UnicodeString> __fastcall GetEndpointNames();
#endif /* _WIN64 */
	
public:
	__fastcall TEMSCommonResource(const System::UnicodeString AResourceName);
	__fastcall virtual ~TEMSCommonResource();
	__property int BaseURLSegmentCount = {read=FBaseURLSegmentCount, nodefault};
	virtual bool __fastcall IsBaseURL(const System::UnicodeString ABaseURL);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSResourceEndPoint : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TEMSCommonResource* FRoot;
	System::UnicodeString __fastcall GetFullName();
	
protected:
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual void __fastcall SetName(const System::UnicodeString AName) = 0 ;
	virtual void __fastcall DoAuthorizeRequest(Ems::Resourceapi::TEndpointContext* const AContext);
	virtual void __fastcall DoHandleRequest(Ems::Resourceapi::TEndpointContext* const AContext) = 0 ;
	virtual TEMSEndpointSegmentList* __fastcall GetSegmentParameters() = 0 ;
	virtual Ems::Resourceapi::TEndpointRequest::TMethod __fastcall GetMethod() = 0 ;
	virtual System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* __fastcall GetProduceList() = 0 ;
	virtual System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* __fastcall GetConsumeList() = 0 ;
	
public:
	__fastcall TEMSResourceEndPoint(TEMSCommonResource* const AOwner);
	__fastcall virtual ~TEMSResourceEndPoint();
	__property System::UnicodeString Name = {read=GetName};
	__property System::UnicodeString FullName = {read=GetFullName};
	__property TEMSEndpointSegmentList* SegmentParameters = {read=GetSegmentParameters};
	__property Ems::Resourceapi::TEndpointRequest::TMethod Method = {read=GetMethod, nodefault};
	__property System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* ProduceList = {read=GetProduceList};
	__property System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* ConsumeList = {read=GetConsumeList};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndpointSegmentList : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TList__1<TEMSEndpointSegment*>* FList;
	int __fastcall GetCount();
	TEMSEndpointSegment* __fastcall GetItem(int I);
	
public:
	__fastcall TEMSEndpointSegmentList();
	__fastcall virtual ~TEMSEndpointSegmentList();
	System::Generics::Collections::TEnumerator__1<TEMSEndpointSegment*>* __fastcall GetEnumerator();
	__property TEMSEndpointSegment* Items[int I] = {read=GetItem};
	__property int Count = {read=GetCount, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndpointSegment : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TEMSEndpointSegmentList* FOwner;
	
public:
	__fastcall TEMSEndpointSegment(TEMSEndpointSegmentList* const AOwner);
	__fastcall virtual ~TEMSEndpointSegment();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndPointSegmentParameter : public TEMSEndpointSegment
{
	typedef TEMSEndpointSegment inherited;
	
private:
	System::UnicodeString FName;
	
public:
	__fastcall TEMSEndPointSegmentParameter(TEMSEndpointSegmentList* const AOwner, const System::UnicodeString AName);
	__property System::UnicodeString Name = {read=FName};
public:
	/* TEMSEndpointSegment.Destroy */ inline __fastcall virtual ~TEMSEndPointSegmentParameter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSResourceEndPointSuffix : public TEMSResourceEndPoint
{
	typedef TEMSResourceEndPoint inherited;
	
	
private:
	typedef System::DelphiInterface<System::Sysutils::TProc__2<TEMSEndPointSegmentParameter*,System::UnicodeString> > TSegmentParamCallback;
	
	
public:
	__interface DELPHIINTERFACE THandlerProc;
	typedef System::DelphiInterface<THandlerProc> _di_THandlerProc;
	__interface THandlerProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(System::TObject* const Sender, Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse) = 0 ;
	};
	
	
private:
	System::UnicodeString FURLSuffix;
	System::UnicodeString FName;
	Ems::Resourceapi::TEndpointRequest::TMethod FMethod;
	_di_THandlerProc FHandlerProc;
	TEMSEndpointSegmentList* FSegmentParameters;
	System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* FProduceList;
	System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* FConsumeList;
	bool __fastcall ScanSegmentParameters(Ems::Resourceapi::TEndpointContext* const AContext, const System::DelphiInterface<System::Sysutils::TProc__2<TEMSEndPointSegmentParameter*,System::UnicodeString> > ACallback);
	
protected:
	virtual TEMSEndpointSegmentList* __fastcall GetSegmentParameters();
	virtual Ems::Resourceapi::TEndpointRequest::TMethod __fastcall GetMethod();
	virtual System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* __fastcall GetProduceList();
	virtual System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* __fastcall GetConsumeList();
	virtual System::UnicodeString __fastcall GetName();
	virtual void __fastcall SetName(const System::UnicodeString AName);
	virtual void __fastcall DoAuthorizeRequest(Ems::Resourceapi::TEndpointContext* const AContext);
	virtual void __fastcall DoHandleRequest(Ems::Resourceapi::TEndpointContext* const AContext);
	
public:
	__fastcall TEMSResourceEndPointSuffix(TEMSCommonResource* const AOwner, const System::UnicodeString AName, const System::UnicodeString AURLSuffix, const Ems::Resourceapi::TEndpointRequest::TMethod AMethod, const System::UnicodeString AProduce, const System::UnicodeString AConsume, const _di_THandlerProc AHandlerProc);
	__fastcall virtual ~TEMSResourceEndPointSuffix();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndPointSegmentSlash : public TEMSEndpointSegment
{
	typedef TEMSEndpointSegment inherited;
	
public:
	/* TEMSEndpointSegment.Create */ inline __fastcall TEMSEndPointSegmentSlash(TEMSEndpointSegmentList* const AOwner) : TEMSEndpointSegment(AOwner) { }
	/* TEMSEndpointSegment.Destroy */ inline __fastcall virtual ~TEMSEndPointSegmentSlash() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndPointSegmentWildCard : public TEMSEndpointSegment
{
	typedef TEMSEndpointSegment inherited;
	
public:
	/* TEMSEndpointSegment.Create */ inline __fastcall TEMSEndPointSegmentWildCard(TEMSEndpointSegmentList* const AOwner) : TEMSEndpointSegment(AOwner) { }
	/* TEMSEndpointSegment.Destroy */ inline __fastcall virtual ~TEMSEndPointSegmentWildCard() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndPointSegmentConstant : public TEMSEndpointSegment
{
	typedef TEMSEndpointSegment inherited;
	
private:
	System::UnicodeString FValue;
	
public:
	__fastcall TEMSEndPointSegmentConstant(TEMSEndpointSegmentList* const AOwner, const System::UnicodeString AValue);
	__property System::UnicodeString Value = {read=FValue};
public:
	/* TEMSEndpointSegment.Destroy */ inline __fastcall virtual ~TEMSEndPointSegmentConstant() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndPointSegmentService : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static void __fastcall ExtractSegments(const System::UnicodeString AString, TEMSEndpointSegmentList* const AList);
	static int __fastcall CountSegments(const System::UnicodeString AString);
public:
	/* TObject.Create */ inline __fastcall TEMSEndPointSegmentService() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSEndPointSegmentService() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSBasicResource : public TEMSCommonResource
{
	typedef TEMSCommonResource inherited;
	
public:
	/* TEMSCommonResource.Create */ inline __fastcall TEMSBasicResource(const System::UnicodeString AResourceName) : TEMSCommonResource(AResourceName) { }
	/* TEMSCommonResource.Destroy */ inline __fastcall virtual ~TEMSBasicResource() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ResourceSuffixAttribute : public TEndpointCustomAttribute
{
	typedef TEndpointCustomAttribute inherited;
	
private:
	System::UnicodeString FSuffix;
	
public:
	__fastcall ResourceSuffixAttribute(const System::UnicodeString AMethod, const System::UnicodeString ASuffix)/* overload */;
	__fastcall ResourceSuffixAttribute(const System::UnicodeString ASuffix)/* overload */;
	__property System::UnicodeString Suffix = {read=FSuffix};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~ResourceSuffixAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ResourceNameAttribute : public TResourceCustomAttribute
{
	typedef TResourceCustomAttribute inherited;
	
private:
	System::UnicodeString FName;
	
public:
	__fastcall ResourceNameAttribute(System::UnicodeString AName);
	__property System::UnicodeString Name = {read=FName};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~ResourceNameAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EndpointNameAttribute : public TEndpointCustomAttribute
{
	typedef TEndpointCustomAttribute inherited;
	
private:
	System::UnicodeString FName;
	
public:
	__fastcall EndpointNameAttribute(const System::UnicodeString AMethod, const System::UnicodeString AName)/* overload */;
	__fastcall EndpointNameAttribute(const System::UnicodeString AName)/* overload */;
	__property System::UnicodeString Name = {read=FName};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~EndpointNameAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TResourceStringsTable : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FResourcesTable;
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	static void __fastcall Add(const System::UnicodeString Akey, const System::UnicodeString AResource);
	static System::UnicodeString __fastcall Get(const System::UnicodeString Akey);
public:
	/* TObject.Create */ inline __fastcall TResourceStringsTable() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TResourceStringsTable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAPIDoc : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TAPIDocContactInfo
	{
	private:
		System::UnicodeString FName;
		System::UnicodeString FURL;
		System::UnicodeString FEmail;
		
	public:
		__fastcall TAPIDocContactInfo(const System::UnicodeString AName, const System::UnicodeString AURL, const System::UnicodeString AEmail);
		__property System::UnicodeString Name = {read=FName};
		__property System::UnicodeString URL = {read=FURL};
		__property System::UnicodeString Email = {read=FEmail};
		TAPIDocContactInfo() {}
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TAPIDocLicenseInfo
	{
	private:
		System::UnicodeString FName;
		System::UnicodeString FURL;
		
	public:
		__fastcall TAPIDocLicenseInfo(const System::UnicodeString AName, const System::UnicodeString AURL);
		__property System::UnicodeString Name = {read=FName};
		__property System::UnicodeString URL = {read=FURL};
		TAPIDocLicenseInfo() {}
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TAPIDocInfo
	{
	private:
		System::UnicodeString FVersion;
		System::UnicodeString FTitle;
		System::UnicodeString FDescription;
		System::UnicodeString FTermsOfUse;
		TAPIDoc::TAPIDocContactInfo FContact;
		TAPIDoc::TAPIDocLicenseInfo FLicense;
		
	public:
		__fastcall TAPIDocInfo(const System::UnicodeString AVersion, const System::UnicodeString ATitle, const System::UnicodeString ADescription);
		__property System::UnicodeString Version = {read=FVersion};
		__property System::UnicodeString Title = {read=FTitle};
		__property System::UnicodeString Description = {read=FDescription};
		__property System::UnicodeString TermsOfUse = {read=FTermsOfUse, write=FTermsOfUse};
		__property TAPIDoc::TAPIDocContactInfo Contact = {read=FContact, write=FContact};
		__property TAPIDoc::TAPIDocLicenseInfo License = {read=FLicense, write=FLicense};
		TAPIDocInfo() {}
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	enum class DECLSPEC_DENUM TPrimitiveType : unsigned char { spArray, spBoolean, spInteger, spNumber, spNull, spObject, spString, spFile };
	
	enum class DECLSPEC_DENUM TPrimitiveFormat : unsigned char { None, Int32, Int64, Float, Double, Byte, Date, DateTime, Password };
	
	enum class DECLSPEC_DENUM TTransferProtocol : unsigned char { Http, Https, Ws, Wss };
	
	
public:
	static const System::WideChar cBlank = (System::WideChar)(0x20);
	
	#define TAPIDoc_cEmptySchema L"{}"
	
	static const System::WideChar cStar = (System::WideChar)(0x2a);
	
	#define TAPIDoc_cWildCard L"wildcard"
	
	
private:
	System::UnicodeString FSwaggerVersion;
	TAPIDocInfo FInfo;
	System::Generics::Collections::TList__1<TAPIDocPath*>* FPaths;
	System::UnicodeString FHost;
	System::UnicodeString FBasePath;
	System::UnicodeString FDefinitions;
#ifndef _WIN64
	System::DynamicArray<TAPIDocPath*> __fastcall GetPaths();
#else /* _WIN64 */
	System::TArray__1<TAPIDocPath*> __fastcall GetPaths();
#endif /* _WIN64 */
	void __fastcall WriteJsonDefinitions(const System::UnicodeString ADefinitions, System::Json::Writers::TJsonWriter* const AJSONWriter);
	
public:
	__fastcall TAPIDoc(const System::UnicodeString AHost, const System::UnicodeString ABasePath);
	__fastcall virtual ~TAPIDoc();
	System::UnicodeString __fastcall GetAPIDocYaml();
	void __fastcall WriteAPIDocJson(System::Json::Writers::TJsonTextWriter* const AWriter);
	bool __fastcall AddPath(TAPIDocPath* const AAPIDocPath);
	void __fastcall SortPaths();
#ifndef _WIN64
	__property System::DynamicArray<TAPIDocPath*> Paths = {read=GetPaths};
#else /* _WIN64 */
	__property System::TArray__1<TAPIDocPath*> Paths = {read=GetPaths};
#endif /* _WIN64 */
	__property System::UnicodeString Definitions = {read=FDefinitions, write=FDefinitions};
	__classmethod System::UnicodeString __fastcall GetDataTypeAsString(TPrimitiveFormat AType)/* overload */;
	__classmethod System::UnicodeString __fastcall GetDataTypeAsString(TPrimitiveType AType)/* overload */;
	__classmethod System::UnicodeString __fastcall ReplaceStar(System::UnicodeString AItem, bool IsPath = false);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAPIDocPath : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FPath;
	System::UnicodeString FResourceName;
	System::Generics::Collections::TObjectList__1<TAPIDocPathItem*>* FPathItems;
#ifndef _WIN64
	System::DynamicArray<TAPIDocPathItem*> __fastcall GetPathItems();
	System::DynamicArray<System::UnicodeString> __fastcall GetPathInfo();
#else /* _WIN64 */
	System::TArray__1<TAPIDocPathItem*> __fastcall GetPathItems();
	System::TArray__1<System::UnicodeString> __fastcall GetPathInfo();
#endif /* _WIN64 */
	void __fastcall WritePathInfo(System::Json::Builders::TJSONObjectBuilder* const ABuilder);
	System::UnicodeString __fastcall GetPath();
	
public:
	__fastcall TAPIDocPath(const System::UnicodeString APath, const System::UnicodeString AResourceName);
	__fastcall virtual ~TAPIDocPath();
	bool __fastcall AddPathItem(TAPIDocPathItem* const AAPIDocPathItem);
#ifndef _WIN64
	__property System::DynamicArray<TAPIDocPathItem*> PathItems = {read=GetPathItems};
#else /* _WIN64 */
	__property System::TArray__1<TAPIDocPathItem*> PathItems = {read=GetPathItems};
#endif /* _WIN64 */
	__property System::UnicodeString Path = {read=GetPath};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAPIDocPathItem : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TAPIDocPathItem_ApplicationId L"X-Embarcadero-Application-Id"
	
	#define TAPIDocPathItem_AppSecret L"X-Embarcadero-App-Secret"
	
	#define TAPIDocPathItem_MasterSecret L"X-Embarcadero-Master-Secret"
	
	#define TAPIDocPathItem_TenantId L"X-Embarcadero-Tenant-Id"
	
	#define TAPIDocPathItem_TenantSecret L"X-Embarcadero-Tenant-Secret"
	
	
private:
	Ems::Resourceapi::TEndpointRequest::TMethod FVerb;
	System::UnicodeString FTags;
	System::UnicodeString FSummary;
	System::UnicodeString FDescription;
	System::UnicodeString FOperationId;
	System::UnicodeString FProduces;
	System::UnicodeString FConsumes;
#ifndef _WIN64
	System::DynamicArray<TAPIDocParameter*> FParameters;
	System::DynamicArray<TAPIDocResponse*> FResponses;
	System::DynamicArray<System::UnicodeString> __fastcall GetAuthoritationHeaderParams();
#else /* _WIN64 */
	System::TArray__1<TAPIDocParameter*> FParameters;
	System::TArray__1<TAPIDocResponse*> FResponses;
	System::TArray__1<System::UnicodeString> __fastcall GetAuthoritationHeaderParams();
#endif /* _WIN64 */
	void __fastcall WriteAuthoritationHeaderParams(System::Json::Builders::TJSONObjectBuilder* const ABuilder);
	
public:
#ifndef _WIN64
	__fastcall TAPIDocPathItem(Ems::Resourceapi::TEndpointRequest::TMethod AHTTPMethod, const System::UnicodeString AOperationID, EndPointRequestSummaryAttribute* const AAttribute, const System::DynamicArray<TAPIDocResponse*> AAPIDocResponses, const System::DynamicArray<TAPIDocParameter*> AAPIDocParameters, const System::UnicodeString AConsume, const System::UnicodeString AProduce);
#else /* _WIN64 */
	__fastcall TAPIDocPathItem(Ems::Resourceapi::TEndpointRequest::TMethod AHTTPMethod, const System::UnicodeString AOperationID, EndPointRequestSummaryAttribute* const AAttribute, const System::TArray__1<TAPIDocResponse*> AAPIDocResponses, const System::TArray__1<TAPIDocParameter*> AAPIDocParameters, const System::UnicodeString AConsume, const System::UnicodeString AProduce);
#endif /* _WIN64 */
	__fastcall virtual ~TAPIDocPathItem();
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall GetMethodInfo();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall GetMethodInfo();
#endif /* _WIN64 */
	void __fastcall WriteMethodInfo(System::Json::Builders::TJSONObjectBuilder* const ABuilder);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAPIDocParameter : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TParameterIn : unsigned char { Path, Query, Header, Body, formData };
	
	
private:
	System::UnicodeString FName;
	TParameterIn FIn;
	System::UnicodeString FDescription;
	bool FRequired;
	bool FIsReference;
	TAPIDoc::TPrimitiveType FType;
	TAPIDoc::TPrimitiveType FItemType;
	TAPIDoc::TPrimitiveFormat FFormat;
	System::UnicodeString FSchema;
	System::UnicodeString FReference;
	System::UnicodeString __fastcall GetParamAsString();
	System::UnicodeString __fastcall GetName();
	
public:
	__fastcall TAPIDocParameter(EndPointRequestParameterAttribute* const AAttribute);
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall GetParamInfo();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall GetParamInfo();
#endif /* _WIN64 */
	void __fastcall WriteParamInfo(System::Json::Builders::TJSONObjectBuilder* const ABuilder);
	void __fastcall Assign(TAPIDocParameter* ASource);
	__property System::UnicodeString Name = {read=GetName};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAPIDocParameter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAPIDocResponse : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	int FCode;
	System::UnicodeString FDescription;
	System::UnicodeString FSchema;
	bool FIsReference;
	System::UnicodeString FReference;
	TAPIDoc::TPrimitiveType FType;
	TAPIDoc::TPrimitiveFormat FFormat;
	System::UnicodeString FExamples;
	System::UnicodeString FRef;
	__fastcall TAPIDocResponse(EndPointResponseDetailsAttribute* const AAttribute);
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall GetResponseInfo();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall GetResponseInfo();
#endif /* _WIN64 */
	void __fastcall WriteResponseInfo(System::Json::Builders::TJSONObjectBuilder* const ABuilder);
	void __fastcall Assign(TAPIDocResponse* ASource);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAPIDocResponse() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EndPointRequestSummaryAttribute : public TEndpointCustomAttribute
{
	typedef TEndpointCustomAttribute inherited;
	
private:
	System::UnicodeString FTags;
	System::UnicodeString FSummary;
	System::UnicodeString FDescription;
	System::UnicodeString FProduces;
	System::UnicodeString FConsume;
	
public:
	__fastcall EndPointRequestSummaryAttribute(const System::UnicodeString AMethod, const System::UnicodeString ATags, const System::UnicodeString ASummary, const System::UnicodeString ADescription, const System::UnicodeString AProduces, const System::UnicodeString AConsume)/* overload */;
	__fastcall EndPointRequestSummaryAttribute(const System::UnicodeString ATags, const System::UnicodeString ASummary, const System::UnicodeString ADescription, const System::UnicodeString AProduces, const System::UnicodeString AConsume)/* overload */;
	__fastcall EndPointRequestSummaryAttribute(const System::UnicodeString AMethod, const System::UnicodeString ATags, const System::UnicodeString ASummary, const System::UnicodeString ADescription)/* overload */;
	__fastcall EndPointRequestSummaryAttribute(const System::UnicodeString ATags, const System::UnicodeString ASummary, const System::UnicodeString ADescription)/* overload */;
	__property System::UnicodeString Tags = {read=FTags};
	__property System::UnicodeString Summary = {read=FSummary};
	__property System::UnicodeString Description = {read=FDescription};
	__property System::UnicodeString Produces = {read=FProduces};
	__property System::UnicodeString Consume = {read=FConsume};
protected:
	/* TEndpointCustomAttribute.Create */ inline __fastcall EndPointRequestSummaryAttribute(const System::UnicodeString AMethod)/* overload */ : TEndpointCustomAttribute(AMethod) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~EndPointRequestSummaryAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EndPointRequestParameterAttribute : public TEndpointCustomAttribute
{
	typedef TEndpointCustomAttribute inherited;
	
private:
	System::UnicodeString FName;
	TAPIDocParameter::TParameterIn FIn;
	System::UnicodeString FDescription;
	bool FRequired;
	System::UnicodeString FJSONSchema;
	System::UnicodeString FReference;
	TAPIDoc::TPrimitiveType FType;
	TAPIDoc::TPrimitiveType FItemType;
	TAPIDoc::TPrimitiveFormat FFormat;
	
public:
	__fastcall EndPointRequestParameterAttribute(const System::UnicodeString AMethod, TAPIDocParameter::TParameterIn AIn, const System::UnicodeString AName, const System::UnicodeString ADescription, const bool ARequired, TAPIDoc::TPrimitiveType AType, TAPIDoc::TPrimitiveFormat AFormat, TAPIDoc::TPrimitiveType AItemType, const System::UnicodeString AJSONScheme, const System::UnicodeString AReference)/* overload */;
	__fastcall EndPointRequestParameterAttribute(TAPIDocParameter::TParameterIn AIn, const System::UnicodeString AName, const System::UnicodeString ADescription, const bool ARequired, TAPIDoc::TPrimitiveType AType, TAPIDoc::TPrimitiveFormat AFormat, TAPIDoc::TPrimitiveType AItemType, const System::UnicodeString AJSONScheme, const System::UnicodeString AReference)/* overload */;
	__property System::UnicodeString Name = {read=FName};
	__property TAPIDocParameter::TParameterIn ParamIn = {read=FIn, nodefault};
	__property System::UnicodeString Description = {read=FDescription};
	__property bool Required = {read=FRequired, nodefault};
	__property TAPIDoc::TPrimitiveType ParamType = {read=FType, nodefault};
	__property TAPIDoc::TPrimitiveType ItemType = {read=FItemType, nodefault};
	__property TAPIDoc::TPrimitiveFormat ItemFormat = {read=FFormat, nodefault};
	__property System::UnicodeString JSONSchema = {read=FJSONSchema};
	__property System::UnicodeString Reference = {read=FReference};
protected:
	/* TEndpointCustomAttribute.Create */ inline __fastcall EndPointRequestParameterAttribute(const System::UnicodeString AMethod)/* overload */ : TEndpointCustomAttribute(AMethod) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~EndPointRequestParameterAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EndPointResponseDetailsAttribute : public TEndpointCustomAttribute
{
	typedef TEndpointCustomAttribute inherited;
	
private:
	int FCode;
	System::UnicodeString FDescription;
	System::UnicodeString FSchema;
	TAPIDoc::TPrimitiveType FType;
	TAPIDoc::TPrimitiveFormat FFormat;
	System::UnicodeString FReference;
	
public:
	__fastcall EndPointResponseDetailsAttribute(const System::UnicodeString AMethod, int ACode, const System::UnicodeString ADescription, TAPIDoc::TPrimitiveType AType, TAPIDoc::TPrimitiveFormat AFormat, const System::UnicodeString ASchema, const System::UnicodeString AReference)/* overload */;
	__fastcall EndPointResponseDetailsAttribute(int ACode, const System::UnicodeString ADescription, TAPIDoc::TPrimitiveType AType, TAPIDoc::TPrimitiveFormat AFormat, const System::UnicodeString ASchema, const System::UnicodeString AReference)/* overload */;
	__property int Code = {read=FCode, nodefault};
	__property System::UnicodeString Description = {read=FDescription};
	__property System::UnicodeString Schema = {read=FSchema};
	__property System::UnicodeString Reference = {read=FReference};
	__property TAPIDoc::TPrimitiveType PrimitiveType = {read=FType, nodefault};
	__property TAPIDoc::TPrimitiveFormat PrimitiveFormat = {read=FFormat, nodefault};
protected:
	/* TEndpointCustomAttribute.Create */ inline __fastcall EndPointResponseDetailsAttribute(const System::UnicodeString AMethod)/* overload */ : TEndpointCustomAttribute(AMethod) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~EndPointResponseDetailsAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EndPointObjectsYAMLDefinitionsAttribute : public TResourceCustomAttribute
{
	typedef TResourceCustomAttribute inherited;
	
private:
	System::UnicodeString FObjects;
	
public:
	__fastcall EndPointObjectsYAMLDefinitionsAttribute(const System::UnicodeString Objects);
	__property System::UnicodeString Objects = {read=FObjects};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~EndPointObjectsYAMLDefinitionsAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EndPointObjectsJSONDefinitionsAttribute : public TResourceCustomAttribute
{
	typedef TResourceCustomAttribute inherited;
	
private:
	System::UnicodeString FObjects;
	
public:
	__fastcall EndPointObjectsJSONDefinitionsAttribute(const System::UnicodeString Objects);
	__property System::UnicodeString Objects = {read=FObjects};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~EndPointObjectsJSONDefinitionsAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION AllowAnonymousTenantAttribute : public TEndpointCustomAttribute
{
	typedef TEndpointCustomAttribute inherited;
	
public:
	__fastcall AllowAnonymousTenantAttribute(const System::UnicodeString AMethod)/* overload */;
	__fastcall AllowAnonymousTenantAttribute()/* overload */;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~AllowAnonymousTenantAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EndPointProduceAttribute : public TEndpointCustomAttribute
{
	typedef TEndpointCustomAttribute inherited;
	
private:
	System::UnicodeString FTypes;
	
public:
	__fastcall EndPointProduceAttribute(const System::UnicodeString AMethod, const System::UnicodeString ATypes)/* overload */;
	__fastcall EndPointProduceAttribute(const System::UnicodeString ATypes)/* overload */;
	__property System::UnicodeString Types = {read=FTypes};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~EndPointProduceAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EndPointConsumeAttribute : public EndPointProduceAttribute
{
	typedef EndPointProduceAttribute inherited;
	
public:
	/* EndPointProduceAttribute.Create */ inline __fastcall EndPointConsumeAttribute(const System::UnicodeString AMethod, const System::UnicodeString ATypes)/* overload */ : EndPointProduceAttribute(AMethod, ATypes) { }
	/* EndPointProduceAttribute.Create */ inline __fastcall EndPointConsumeAttribute(const System::UnicodeString ATypes)/* overload */ : EndPointProduceAttribute(ATypes) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~EndPointConsumeAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EndPointMethodAttribute : public TEndpointCustomAttribute
{
	typedef TEndpointCustomAttribute inherited;
	
private:
	Ems::Resourceapi::TEndpointRequest::TMethod FHTTPMethod;
	
public:
	__fastcall EndPointMethodAttribute(const System::UnicodeString AMethod, const Ems::Resourceapi::TEndpointRequest::TMethod AHTTPMethod)/* overload */;
	__fastcall EndPointMethodAttribute(const Ems::Resourceapi::TEndpointRequest::TMethod AHTTPMethod)/* overload */;
	__property Ems::Resourceapi::TEndpointRequest::TMethod HTTPMethod = {read=FHTTPMethod, nodefault};
protected:
	/* TEndpointCustomAttribute.Create */ inline __fastcall EndPointMethodAttribute(const System::UnicodeString AMethod)/* overload */ : TEndpointCustomAttribute(AMethod) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~EndPointMethodAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum class DECLSPEC_DENUM TTenantAuthorization : unsigned char { Default, Full, SkipAll };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSTypeInfoResource : public TEMSCommonResource
{
	typedef TEMSCommonResource inherited;
	
	
private:
	enum class DECLSPEC_DENUM TConstructorKind : unsigned char { Simple, Component };
	
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TResourceMethod
	{
		
	public:
		enum class DECLSPEC_DENUM TSignatureKind : unsigned char { Unknown, Standard };
		
		
	private:
		System::Rtti::TRttiField* FRttiField;
		System::Rtti::TRttiMethod* FRttiMethod;
		Ems::Resourceapi::TEndpointRequest::TMethod FHTTPMethod;
		System::UnicodeString FName;
		System::UnicodeString FURLSuffix;
#ifndef _WIN64
		System::DynamicArray<System::Rtti::TRttiParameter*> FRttiParameters;
#else /* _WIN64 */
		System::TArray__1<System::Rtti::TRttiParameter*> FRttiParameters;
#endif /* _WIN64 */
		System::Rtti::TRttiType* FRttiReturnType;
		TSignatureKind FSignatureKind;
		TAPIDocPathItem* FPathItem;
		TTenantAuthorization FTenantAuthorization;
		System::UnicodeString FProduce;
		System::UnicodeString FConsume;
		
	public:
		__property System::UnicodeString Name = {read=FName};
		__property TTenantAuthorization TenantAuthorization = {read=FTenantAuthorization};
		__fastcall TResourceMethod(const System::UnicodeString AName, System::Rtti::TRttiField* const ARttiField, System::Rtti::TRttiMethod* const ARttiMethod, Ems::Resourceapi::TEndpointRequest::TMethod AHTTPMethod, const System::UnicodeString ABaseURLSuffix, TAPIDocPathItem* const APathItem, TTenantAuthorization ATenantAuthorization, const System::UnicodeString AProduce, const System::UnicodeString AConsume);
		TResourceMethod() {}
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	
private:
	System::Rtti::TRttiContext FRttiContext;
	System::Rtti::TRttiMethod* FRttiConstructor;
	TConstructorKind FConstructorKind;
	System::Rtti::TRttiType* FRttiType;
	System::Generics::Collections::TList__1<TResourceMethod>* FMethodList;
	TEMSResourceAttributes* FAttributes;
	System::Generics::Collections::TObjectList__1<TAPIDocPath*>* FAPIDocPaths;
	System::UnicodeString FYAMLDefinitions;
	System::UnicodeString FJSONDefinitions;
	TTenantAuthorization FTenantAuthorization;
	void __fastcall InternalScanResource(System::Rtti::TRttiNamedObject* ARttiObj, /* out */ System::UnicodeString &AResourceName, /* out */ TTenantAuthorization &ATenantAuthorization);
	void __fastcall ScanResource(/* out */ System::UnicodeString &AResourceName);
	void __fastcall ScanConstructor();
#ifndef _WIN64
	void __fastcall InternalScanMethods(System::Rtti::TRttiField* const ARTTIField, TEMSResourceAttributes* const AFieldAttributes, const System::DynamicArray<System::Rtti::TRttiMethod*> ARTTIMethods);
#else /* _WIN64 */
	void __fastcall InternalScanMethods(System::Rtti::TRttiField* const ARTTIField, TEMSResourceAttributes* const AFieldAttributes, const System::TArray__1<System::Rtti::TRttiMethod*> ARTTIMethods);
#endif /* _WIN64 */
	void __fastcall ScanMethods();
	void __fastcall ScanFields();
	void __fastcall ScanObjectsDefinitions(const System::UnicodeString AResourceName);
	System::TObject* __fastcall CreateInstance();
	void __fastcall CreateEndPoints();
#ifndef _WIN64
	System::DynamicArray<TAPIDocPath*> __fastcall GetAPIDocPaths();
#else /* _WIN64 */
	System::TArray__1<TAPIDocPath*> __fastcall GetAPIDocPaths();
#endif /* _WIN64 */
	TTenantAuthorization __fastcall GetMethodTenantAuthorization(const System::UnicodeString AMethod);
	
public:
	__fastcall TEMSTypeInfoResource(const System::Typinfo::PTypeInfo ATypeInfo)/* overload */;
	__fastcall TEMSTypeInfoResource(const System::Typinfo::PTypeInfo ATypeInfo, TEMSResourceAttributes* const AAttributes)/* overload */;
	__fastcall virtual ~TEMSTypeInfoResource();
	virtual void __fastcall Log(System::Json::TJSONObject* AJSON);
	__property System::UnicodeString YAMLDefinitions = {read=FYAMLDefinitions};
	__property System::UnicodeString JSONDefinitions = {read=FJSONDefinitions};
#ifndef _WIN64
	__property System::DynamicArray<TAPIDocPath*> APIDocPaths = {read=GetAPIDocPaths};
#else /* _WIN64 */
	__property System::TArray__1<TAPIDocPath*> APIDocPaths = {read=GetAPIDocPaths};
#endif /* _WIN64 */
	__property TTenantAuthorization TenantAuthorization = {read=FTenantAuthorization, nodefault};
	__property TTenantAuthorization MethodTenantAuthorization[const System::UnicodeString AMethod] = {read=GetMethodTenantAuthorization};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSResourceAttributes : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FResourceName;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FEndpointName;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FResourceSuffix;
	System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,System::Generics::Collections::TList__1<TAPIDocResponse*>*>* FResponseDetails;
	System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,EndPointRequestSummaryAttribute*>* FRequestSummary;
	System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,System::Generics::Collections::TList__1<TAPIDocParameter*>*>* FRequestParameters;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FYAMLDefinitions;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FJSONDefinitions;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TTenantAuthorization>* FResourceTenantAuthorizations;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TTenantAuthorization>* FEndPointTenantAuthorizations;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FEndPointProduce;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FEndPointConsume;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,Ems::Resourceapi::TEndpointRequest::TMethod>* FEndPointHTTPMethod;
	System::UnicodeString __fastcall GetEndPointName(const System::UnicodeString AMethod)/* overload */;
	System::UnicodeString __fastcall GetResourceSuffix(const System::UnicodeString AMethod)/* overload */;
#ifndef _WIN64
	System::DynamicArray<TAPIDocResponse*> __fastcall GetResponseDetails(const System::UnicodeString AMethod);
#else /* _WIN64 */
	System::TArray__1<TAPIDocResponse*> __fastcall GetResponseDetails(const System::UnicodeString AMethod);
#endif /* _WIN64 */
	EndPointRequestSummaryAttribute* __fastcall GetRequestSummary(const System::UnicodeString AMethod);
#ifndef _WIN64
	System::DynamicArray<TAPIDocParameter*> __fastcall GetRequestParameters(const System::UnicodeString AMethod);
#else /* _WIN64 */
	System::TArray__1<TAPIDocParameter*> __fastcall GetRequestParameters(const System::UnicodeString AMethod);
#endif /* _WIN64 */
	System::UnicodeString __fastcall GetYAMLDefinitions(const System::UnicodeString AResourceName);
	System::UnicodeString __fastcall GetJSONDefinitions(const System::UnicodeString AResourceName);
	void __fastcall SetEndPointName(const System::UnicodeString AMethod, const System::UnicodeString Value);
	void __fastcall SetResourceSuffix(const System::UnicodeString AMethod, const System::UnicodeString Value);
	void __fastcall SetRequestSummary(const System::UnicodeString AMethod, EndPointRequestSummaryAttribute* ARequestSummaryAttribute);
	void __fastcall SetYAMLDefinitions(const System::UnicodeString AResourceName, const System::UnicodeString Value);
	void __fastcall SetJSONDefinitions(const System::UnicodeString AResourceName, const System::UnicodeString Value);
	TTenantAuthorization __fastcall GetEndPointTenantAuthorization(const System::UnicodeString AMethod);
	TTenantAuthorization __fastcall GetResourceTenantAuthorization(const System::UnicodeString AResourceName);
	void __fastcall SetEndPointTenantAuthorization(const System::UnicodeString AMethod, const TTenantAuthorization Value);
	void __fastcall SetResourceTenantAuthorization(const System::UnicodeString AResourceName, const TTenantAuthorization Value);
	System::UnicodeString __fastcall GetEndPointProduce(const System::UnicodeString AMethod);
	void __fastcall SetEndPointProduce(const System::UnicodeString AMethod, const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetEndPointConsume(const System::UnicodeString AMethod);
	void __fastcall SetEndPointConsume(const System::UnicodeString AMethod, const System::UnicodeString AValue);
	Ems::Resourceapi::TEndpointRequest::TMethod __fastcall GetEndPointHTTPMethod(const System::UnicodeString AMethod);
	void __fastcall SetEndPointHTTPMethod(const System::UnicodeString AMethod, const Ems::Resourceapi::TEndpointRequest::TMethod AValue);
	
public:
	__fastcall TEMSResourceAttributes();
	__fastcall virtual ~TEMSResourceAttributes();
	void __fastcall LoadFromRtti(System::Rtti::TRttiMember* AMember);
	void __fastcall Clear();
	void __fastcall AddResponseDetail(const System::UnicodeString AMethod, EndPointResponseDetailsAttribute* const AResponseDetailAttribute);
	void __fastcall AddRequestParameter(const System::UnicodeString AMethod, EndPointRequestParameterAttribute* const ARequestParameterAttribute);
	__property System::UnicodeString ResourceName = {read=FResourceName, write=FResourceName};
	__property TTenantAuthorization ResourceTenantAuthorization[const System::UnicodeString AResourceName] = {read=GetResourceTenantAuthorization, write=SetResourceTenantAuthorization};
	__property System::UnicodeString YAMLDefinitions[const System::UnicodeString AResourceName] = {read=GetYAMLDefinitions, write=SetYAMLDefinitions};
	__property System::UnicodeString JSONDefinitions[const System::UnicodeString AResourceName] = {read=GetJSONDefinitions, write=SetJSONDefinitions};
	__property System::UnicodeString EndPointName[const System::UnicodeString AMethod] = {read=GetEndPointName, write=SetEndPointName};
	__property System::UnicodeString ResourceSuffix[const System::UnicodeString AMethod] = {read=GetResourceSuffix, write=SetResourceSuffix};
	__property System::UnicodeString EndPointProduce[const System::UnicodeString AMethod] = {read=GetEndPointProduce, write=SetEndPointProduce};
	__property System::UnicodeString EndPointConsume[const System::UnicodeString AMethod] = {read=GetEndPointConsume, write=SetEndPointConsume};
	__property Ems::Resourceapi::TEndpointRequest::TMethod EndPointHTTPMethod[const System::UnicodeString AMethod] = {read=GetEndPointHTTPMethod, write=SetEndPointHTTPMethod};
	__property TTenantAuthorization EndPointTenantAuthorization[const System::UnicodeString AMethod] = {read=GetEndPointTenantAuthorization, write=SetEndPointTenantAuthorization};
#ifndef _WIN64
	__property System::DynamicArray<TAPIDocResponse*> ResponseDetails[const System::UnicodeString AMethod] = {read=GetResponseDetails};
#else /* _WIN64 */
	__property System::TArray__1<TAPIDocResponse*> ResponseDetails[const System::UnicodeString AMethod] = {read=GetResponseDetails};
#endif /* _WIN64 */
	__property EndPointRequestSummaryAttribute* RequestSummary[const System::UnicodeString AMethod] = {read=GetRequestSummary, write=SetRequestSummary};
#ifndef _WIN64
	__property System::DynamicArray<TAPIDocParameter*> RequestParameters[const System::UnicodeString AMethod] = {read=GetRequestParameters};
#else /* _WIN64 */
	__property System::TArray__1<TAPIDocParameter*> RequestParameters[const System::UnicodeString AMethod] = {read=GetRequestParameters};
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterResource(const System::Typinfo::PTypeInfo TypeInfo)/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterResource(const System::Typinfo::PTypeInfo TypeInfo, TEMSResourceAttributes* const AAttributes)/* overload */;
}	/* namespace Resourcetypes */
}	/* namespace Ems */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMS_RESOURCETYPES)
using namespace Ems::Resourcetypes;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMS)
using namespace Ems;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ems_ResourcetypesHPP
