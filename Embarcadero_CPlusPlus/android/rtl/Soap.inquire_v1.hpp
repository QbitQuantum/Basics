// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.inquire_v1.pas' rev: 34.00 (Android)

#ifndef Soap_Inquire_v1HPP
#define Soap_Inquire_v1HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Soap.InvokeRegistry.hpp>

//-- user supplied -----------------------------------------------------------
#ifndef __clang__
namespace Soap { namespace Inquire_v1 { enum Truncated { False, True }; } }

namespace Soap
{
namespace Inquire_v1
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS AccessPoint;
class DELPHICLASS HostingRedirector;
class DELPHICLASS OverviewDoc;
class DELPHICLASS InstanceDetails;
class DELPHICLASS TModelInstanceInfo;
class DELPHICLASS TModelInstanceDetails;
class DELPHICLASS BindingTemplate;
class DELPHICLASS BindingDetail;
class DELPHICLASS DiscoveryUrl;
class DELPHICLASS DiscoveryURLs;
class DELPHICLASS Phone2;
class DELPHICLASS Email;
class DELPHICLASS Address;
class DELPHICLASS Contact;
class DELPHICLASS Contacts;
class DELPHICLASS BindingTemplates;
class DELPHICLASS KeyedReference;
class DELPHICLASS CategoryBag;
class DELPHICLASS BusinessService;
class DELPHICLASS ServiceDetail;
class DELPHICLASS BusinessServices;
class DELPHICLASS IdentifierBag;
class DELPHICLASS BusinessEntity;
class DELPHICLASS BusinessDetail;
class DELPHICLASS BusinessEntityExt;
class DELPHICLASS BusinessDetailExt;
class DELPHICLASS ServiceInfo;
class DELPHICLASS ServiceInfos;
class DELPHICLASS ServiceList;
class DELPHICLASS BusinessInfo;
class DELPHICLASS BusinessInfos;
class DELPHICLASS BusinessList;
class DELPHICLASS FindQualifiers;
class DELPHICLASS FindTModel;
class DELPHICLASS TModelBag;
class DELPHICLASS FindBinding;
class DELPHICLASS FindBusiness;
class DELPHICLASS FindService;
class DELPHICLASS GetTModelDetail;
class DELPHICLASS GetBindingDetail;
class DELPHICLASS GetBusinessDetailExt;
class DELPHICLASS GetBusinessDetail;
class DELPHICLASS GetServiceDetail;
class DELPHICLASS TModelInfo;
class DELPHICLASS TModelInfos;
class DELPHICLASS TModelList;
class DELPHICLASS TModel;
class DELPHICLASS TModelDetail;
__interface DELPHIINTERFACE InquireSoap;
typedef System::DelphiInterface<InquireSoap> _di_InquireSoap;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM URLType : unsigned char { mailto, http, https, ftp, fax, phone, other };

typedef System::WideString Description;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION AccessPoint : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::UnicodeString FAccessPoint;
	URLType FURLType;
	
public:
	__fastcall virtual AccessPoint();
	
__published:
	__property System::UnicodeString AccessPoint = {read=FAccessPoint, write=FAccessPoint};
	__property URLType URLType = {read=FURLType, write=FURLType, stored=false, nodefault};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~AccessPoint() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION HostingRedirector : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::UnicodeString FbindingKey;
	
__published:
	__property System::UnicodeString bindingKey = {read=FbindingKey, write=FbindingKey, stored=false};
public:
	/* TRemotable.Create */ inline __fastcall virtual HostingRedirector() : Soap::Invokeregistry::TRemotable() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~HostingRedirector() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION OverviewDoc : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	Description Fdescription;
	System::UnicodeString FoverviewURL;
	
__published:
	__property Description description = {read=Fdescription, write=Fdescription};
	__property System::UnicodeString overviewURL = {read=FoverviewURL, write=FoverviewURL};
public:
	/* TRemotable.Create */ inline __fastcall virtual OverviewDoc() : Soap::Invokeregistry::TRemotable() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~OverviewDoc() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION InstanceDetails : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	Description Fdescription;
	OverviewDoc* FoverviewDoc;
	System::UnicodeString FinstanceParms;
	
public:
	__fastcall virtual ~InstanceDetails();
	
__published:
	__property Description description = {read=Fdescription, write=Fdescription};
	__property OverviewDoc* overviewDoc = {read=FoverviewDoc, write=FoverviewDoc};
	__property System::UnicodeString instanceParms = {read=FinstanceParms, write=FinstanceParms};
public:
	/* TRemotable.Create */ inline __fastcall virtual InstanceDetails() : Soap::Invokeregistry::TRemotable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TModelInstanceInfo : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	Description Fdescription;
	InstanceDetails* FinstanceDetails;
	System::UnicodeString FtModelKey;
	
public:
	__fastcall virtual ~TModelInstanceInfo();
	
__published:
	__property Description description = {read=Fdescription, write=Fdescription};
	__property InstanceDetails* instanceDetails = {read=FinstanceDetails, write=FinstanceDetails};
	__property System::UnicodeString tModelKey = {read=FtModelKey, write=FtModelKey, stored=false};
public:
	/* TRemotable.Create */ inline __fastcall virtual TModelInstanceInfo() : Soap::Invokeregistry::TRemotable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<TModelInstanceInfo*> tModelInstanceInfo2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TModelInstanceDetails : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	TModelInstanceInfo* operator[](int Index) { return this->TModelInstanceInfoArray[Index]; }
	
private:
	tModelInstanceInfo2 FtModelInstanceInfo;
	
public:
	__fastcall virtual TModelInstanceDetails();
	__fastcall virtual ~TModelInstanceDetails();
	TModelInstanceInfo* __fastcall GetTModelInstanceInfoArray(int Index);
	int __fastcall GetTModelInstanceInfoArrayLength();
	__property TModelInstanceInfo* TModelInstanceInfoArray[int Index] = {read=GetTModelInstanceInfoArray/*, default*/};
	__property int Len = {read=GetTModelInstanceInfoArrayLength, nodefault};
	
__published:
	__property tModelInstanceInfo2 tModelInstanceInfo = {read=FtModelInstanceInfo, write=FtModelInstanceInfo};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BindingTemplate : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	Description Fdescription;
	AccessPoint* FaccessPoint;
	HostingRedirector* FhostingRedirector;
	TModelInstanceDetails* FtModelInstanceDetails;
	System::UnicodeString FserviceKey;
	System::UnicodeString FbindingKey;
	
public:
	__fastcall virtual ~BindingTemplate();
	
__published:
	__property Description description = {read=Fdescription, write=Fdescription};
	__property AccessPoint* accessPoint = {read=FaccessPoint, write=FaccessPoint};
	__property HostingRedirector* hostingRedirector = {read=FhostingRedirector, write=FhostingRedirector};
	__property TModelInstanceDetails* tModelInstanceDetails = {read=FtModelInstanceDetails, write=FtModelInstanceDetails};
	__property System::UnicodeString serviceKey = {read=FserviceKey, write=FserviceKey, stored=false};
	__property System::UnicodeString bindingKey = {read=FbindingKey, write=FbindingKey, stored=false};
public:
	/* TRemotable.Create */ inline __fastcall virtual BindingTemplate() : Soap::Invokeregistry::TRemotable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<BindingTemplate*> bindingTemplate2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BindingDetail : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	BindingTemplate* operator[](int Index) { return this->BindingTemplateArray[Index]; }
	
private:
	System::UnicodeString Fgeneric;
	System::UnicodeString Foperator;
	Truncated Ftruncated;
	bindingTemplate2 FbindingTemplate;
	
public:
	__fastcall virtual BindingDetail();
	__fastcall virtual ~BindingDetail();
	BindingTemplate* __fastcall GetBindingTemplateArray(int Index);
	int __fastcall GetBindingTemplateArrayLength();
	__property BindingTemplate* BindingTemplateArray[int Index] = {read=GetBindingTemplateArray/*, default*/};
	__property int Len = {read=GetBindingTemplateArrayLength, nodefault};
	
__published:
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property System::UnicodeString Operator = {read=Foperator, write=Foperator, stored=false};
	__property Truncated truncated = {read=Ftruncated, write=Ftruncated, stored=false, nodefault};
	__property bindingTemplate2 bindingTemplate = {read=FbindingTemplate, write=FbindingTemplate};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef BindingDetail bindingDetail2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION DiscoveryUrl : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::UnicodeString FDiscoveryUrl;
	System::UnicodeString FuseType;
	
public:
	__fastcall virtual DiscoveryUrl();
	
__published:
	__property System::UnicodeString DiscoveryUrl = {read=FDiscoveryUrl, write=FDiscoveryUrl};
	__property System::UnicodeString useType = {read=FuseType, write=FuseType, stored=false};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~DiscoveryUrl() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<DiscoveryUrl*> discoveryUrl2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION DiscoveryURLs : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	DiscoveryUrl* operator[](int Index) { return this->DiscoveryUrlArray[Index]; }
	
private:
	discoveryUrl2 FdiscoveryUrl;
	
public:
	__fastcall virtual DiscoveryURLs();
	__fastcall virtual ~DiscoveryURLs();
	DiscoveryUrl* __fastcall GetDiscoveryUrlArray(int Index);
	int __fastcall GetDiscoveryUrlArrayLength();
	__property DiscoveryUrl* DiscoveryUrlArray[int Index] = {read=GetDiscoveryUrlArray/*, default*/};
	__property int Len = {read=GetDiscoveryUrlArrayLength, nodefault};
	
__published:
	__property discoveryUrl2 discoveryUrl = {read=FdiscoveryUrl, write=FdiscoveryUrl};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION Phone2 : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::UnicodeString FPhone;
	System::UnicodeString FuseType;
	
public:
	__fastcall virtual Phone2();
	
__published:
	__property System::UnicodeString Phone = {read=FPhone, write=FPhone};
	__property System::UnicodeString useType = {read=FuseType, write=FuseType, stored=false};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~Phone2() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION Email : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::UnicodeString FEmail;
	System::UnicodeString FuseType;
	
public:
	__fastcall virtual Email();
	
__published:
	__property System::UnicodeString Email = {read=FEmail, write=FEmail};
	__property System::UnicodeString useType = {read=FuseType, write=FuseType, stored=false};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~Email() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<System::UnicodeString> addressLine;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION Address : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	System::UnicodeString operator[](int Index) { return this->WideStringArray[Index]; }
	
private:
	System::UnicodeString FsortCode;
	System::UnicodeString FuseType;
	addressLine FaddressLine;
	
public:
	__fastcall virtual Address();
	System::UnicodeString __fastcall GetWideStringArray(int Index);
	int __fastcall GetWideStringArrayLength();
	__property System::UnicodeString WideStringArray[int Index] = {read=GetWideStringArray/*, default*/};
	__property int Len = {read=GetWideStringArrayLength, nodefault};
	
__published:
	__property System::UnicodeString sortCode = {read=FsortCode, write=FsortCode, stored=false};
	__property System::UnicodeString useType = {read=FuseType, write=FuseType, stored=false};
	__property addressLine addressLine = {read=FaddressLine, write=FaddressLine};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~Address() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION Contact : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	Description Fdescription;
	System::UnicodeString FpersonName;
	Phone2* Fphone;
	Email* Femail;
	Address* Faddress;
	System::UnicodeString FuseType;
	
public:
	__fastcall virtual ~Contact();
	
__published:
	__property Description description = {read=Fdescription, write=Fdescription};
	__property System::UnicodeString personName = {read=FpersonName, write=FpersonName};
	__property Phone2* phone = {read=Fphone, write=Fphone};
	__property Email* email = {read=Femail, write=Femail};
	__property Address* address = {read=Faddress, write=Faddress};
	__property System::UnicodeString useType = {read=FuseType, write=FuseType, stored=false};
public:
	/* TRemotable.Create */ inline __fastcall virtual Contact() : Soap::Invokeregistry::TRemotable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<Contact*> contact2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION Contacts : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	Contact* operator[](int Index) { return this->ContactArray[Index]; }
	
private:
	contact2 Fcontact;
	
public:
	__fastcall virtual Contacts();
	__fastcall virtual ~Contacts();
	Contact* __fastcall GetContactArray(int Index);
	int __fastcall GetContactArrayLength();
	__property Contact* ContactArray[int Index] = {read=GetContactArray/*, default*/};
	__property int Len = {read=GetContactArrayLength, nodefault};
	
__published:
	__property contact2 contact = {read=Fcontact, write=Fcontact};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BindingTemplates : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	BindingTemplate* operator[](int Index) { return this->BindingTemplateArray[Index]; }
	
private:
	bindingTemplate2 FbindingTemplate;
	
public:
	__fastcall virtual BindingTemplates();
	__fastcall virtual ~BindingTemplates();
	BindingTemplate* __fastcall GetBindingTemplateArray(int Index);
	int __fastcall GetBindingTemplateArrayLength();
	__property BindingTemplate* BindingTemplateArray[int Index] = {read=GetBindingTemplateArray/*, default*/};
	__property int Len = {read=GetBindingTemplateArrayLength, nodefault};
	
__published:
	__property bindingTemplate2 bindingTemplate = {read=FbindingTemplate, write=FbindingTemplate};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION KeyedReference : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::UnicodeString FtModelKey;
	System::UnicodeString FkeyName;
	System::UnicodeString FkeyValue;
	
__published:
	__property System::UnicodeString tModelKey = {read=FtModelKey, write=FtModelKey, stored=false};
	__property System::UnicodeString keyName = {read=FkeyName, write=FkeyName, stored=false};
	__property System::UnicodeString keyValue = {read=FkeyValue, write=FkeyValue, stored=false};
public:
	/* TRemotable.Create */ inline __fastcall virtual KeyedReference() : Soap::Invokeregistry::TRemotable() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~KeyedReference() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<KeyedReference*> keyedReference2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION CategoryBag : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	KeyedReference* operator[](int Index) { return this->KeyedReferenceArray[Index]; }
	
private:
	keyedReference2 FkeyedReference;
	
public:
	__fastcall virtual CategoryBag();
	__fastcall virtual ~CategoryBag();
	KeyedReference* __fastcall GetKeyedReferenceArray(int Index);
	int __fastcall GetKeyedReferenceArrayLength();
	__property KeyedReference* KeyedReferenceArray[int Index] = {read=GetKeyedReferenceArray/*, default*/};
	__property int Len = {read=GetKeyedReferenceArrayLength, nodefault};
	
__published:
	__property keyedReference2 keyedReference = {read=FkeyedReference, write=FkeyedReference};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BusinessService : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::UnicodeString Fname;
	Description Fdescription;
	BindingTemplates* FbindingTemplates;
	CategoryBag* FcategoryBag;
	System::UnicodeString FserviceKey;
	System::UnicodeString FbusinessKey;
	
public:
	__fastcall virtual ~BusinessService();
	
__published:
	__property System::UnicodeString name = {read=Fname, write=Fname};
	__property Description description = {read=Fdescription, write=Fdescription};
	__property BindingTemplates* bindingTemplates = {read=FbindingTemplates, write=FbindingTemplates};
	__property CategoryBag* categoryBag = {read=FcategoryBag, write=FcategoryBag};
	__property System::UnicodeString serviceKey = {read=FserviceKey, write=FserviceKey, stored=false};
	__property System::UnicodeString businessKey = {read=FbusinessKey, write=FbusinessKey, stored=false};
public:
	/* TRemotable.Create */ inline __fastcall virtual BusinessService() : Soap::Invokeregistry::TRemotable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<BusinessService*> businessService2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ServiceDetail : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	BusinessService* operator[](int Index) { return this->BusinessServiceArray[Index]; }
	
private:
	System::UnicodeString Fgeneric;
	System::UnicodeString Foperator;
	Truncated Ftruncated;
	businessService2 FbusinessService;
	
public:
	__fastcall virtual ServiceDetail();
	__fastcall virtual ~ServiceDetail();
	BusinessService* __fastcall GetBusinessServiceArray(int Index);
	int __fastcall GetBusinessServiceArrayLength();
	__property BusinessService* BusinessServiceArray[int Index] = {read=GetBusinessServiceArray/*, default*/};
	__property int Len = {read=GetBusinessServiceArrayLength, nodefault};
	
__published:
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property System::UnicodeString Operator = {read=Foperator, write=Foperator, stored=false};
	__property Truncated truncated = {read=Ftruncated, write=Ftruncated, stored=false, nodefault};
	__property businessService2 businessService = {read=FbusinessService, write=FbusinessService};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef ServiceDetail serviceDetail2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BusinessServices : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	BusinessService* operator[](int Index) { return this->BusinessServiceArray[Index]; }
	
private:
	businessService2 FbusinessService;
	
public:
	__fastcall virtual BusinessServices();
	__fastcall virtual ~BusinessServices();
	BusinessService* __fastcall GetBusinessServiceArray(int Index);
	int __fastcall GetBusinessServiceArrayLength();
	__property BusinessService* BusinessServiceArray[int Index] = {read=GetBusinessServiceArray/*, default*/};
	__property int Len = {read=GetBusinessServiceArrayLength, nodefault};
	
__published:
	__property businessService2 businessService = {read=FbusinessService, write=FbusinessService};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION IdentifierBag : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	KeyedReference* operator[](int Index) { return this->KeyedReferenceArray[Index]; }
	
private:
	keyedReference2 FkeyedReference;
	
public:
	__fastcall virtual IdentifierBag();
	__fastcall virtual ~IdentifierBag();
	KeyedReference* __fastcall GetKeyedReferenceArray(int Index);
	int __fastcall GetKeyedReferenceArrayLength();
	__property KeyedReference* KeyedReferenceArray[int Index] = {read=GetKeyedReferenceArray/*, default*/};
	__property int Len = {read=GetKeyedReferenceArrayLength, nodefault};
	
__published:
	__property keyedReference2 keyedReference = {read=FkeyedReference, write=FkeyedReference};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BusinessEntity : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	DiscoveryURLs* FdiscoveryURLs;
	System::UnicodeString Fname;
	Description Fdescription;
	Contacts* Fcontacts;
	BusinessServices* FbusinessServices;
	IdentifierBag* FidentifierBag;
	CategoryBag* FcategoryBag;
	System::UnicodeString FbusinessKey;
	System::UnicodeString Foperator;
	System::UnicodeString FauthorizedName;
	
public:
	__fastcall virtual ~BusinessEntity();
	
__published:
	__property DiscoveryURLs* discoveryURLs = {read=FdiscoveryURLs, write=FdiscoveryURLs};
	__property System::UnicodeString name = {read=Fname, write=Fname};
	__property Description description = {read=Fdescription, write=Fdescription};
	__property Contacts* contacts = {read=Fcontacts, write=Fcontacts};
	__property BusinessServices* businessServices = {read=FbusinessServices, write=FbusinessServices};
	__property IdentifierBag* identifierBag = {read=FidentifierBag, write=FidentifierBag};
	__property CategoryBag* categoryBag = {read=FcategoryBag, write=FcategoryBag};
	__property System::UnicodeString businessKey = {read=FbusinessKey, write=FbusinessKey, stored=false};
	__property System::UnicodeString Operator = {read=Foperator, write=Foperator, stored=false};
	__property System::UnicodeString authorizedName = {read=FauthorizedName, write=FauthorizedName, stored=false};
public:
	/* TRemotable.Create */ inline __fastcall virtual BusinessEntity() : Soap::Invokeregistry::TRemotable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<BusinessEntity*> businessEntity2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BusinessDetail : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	BusinessEntity* operator[](int Index) { return this->BusinessEntityArray[Index]; }
	
private:
	System::UnicodeString Fgeneric;
	System::UnicodeString Foperator;
	Truncated Ftruncated;
	businessEntity2 FbusinessEntity;
	
public:
	__fastcall virtual BusinessDetail();
	__fastcall virtual ~BusinessDetail();
	BusinessEntity* __fastcall GetBusinessEntityArray(int Index);
	int __fastcall GetBusinessEntityArrayLength();
	__property BusinessEntity* BusinessEntityArray[int Index] = {read=GetBusinessEntityArray/*, default*/};
	__property int Len = {read=GetBusinessEntityArrayLength, nodefault};
	
__published:
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property System::UnicodeString Operator = {read=Foperator, write=Foperator, stored=false};
	__property Truncated truncated = {read=Ftruncated, write=Ftruncated, stored=false, nodefault};
	__property businessEntity2 businessEntity = {read=FbusinessEntity, write=FbusinessEntity};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef BusinessDetail businessDetail2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BusinessEntityExt : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	BusinessEntity* FbusinessEntity;
	
public:
	__fastcall virtual ~BusinessEntityExt();
	
__published:
	__property BusinessEntity* businessEntity = {read=FbusinessEntity, write=FbusinessEntity};
public:
	/* TRemotable.Create */ inline __fastcall virtual BusinessEntityExt() : Soap::Invokeregistry::TRemotable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<BusinessEntityExt*> businessEntityExt2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BusinessDetailExt : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	BusinessEntityExt* operator[](int Index) { return this->BusinessEntityExtArray[Index]; }
	
private:
	System::UnicodeString Fgeneric;
	System::UnicodeString Foperator;
	Truncated Ftruncated;
	businessEntityExt2 FbusinessEntityExt;
	
public:
	__fastcall virtual BusinessDetailExt();
	__fastcall virtual ~BusinessDetailExt();
	BusinessEntityExt* __fastcall GetBusinessEntityExtArray(int Index);
	int __fastcall GetBusinessEntityExtArrayLength();
	__property BusinessEntityExt* BusinessEntityExtArray[int Index] = {read=GetBusinessEntityExtArray/*, default*/};
	__property int Len = {read=GetBusinessEntityExtArrayLength, nodefault};
	
__published:
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property System::UnicodeString Operator = {read=Foperator, write=Foperator, stored=false};
	__property Truncated truncated = {read=Ftruncated, write=Ftruncated, stored=false, nodefault};
	__property businessEntityExt2 businessEntityExt = {read=FbusinessEntityExt, write=FbusinessEntityExt};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef BusinessDetailExt businessDetailExt2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ServiceInfo : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::UnicodeString Fname;
	System::UnicodeString FserviceKey;
	System::UnicodeString FbusinessKey;
	
__published:
	__property System::UnicodeString name = {read=Fname, write=Fname};
	__property System::UnicodeString serviceKey = {read=FserviceKey, write=FserviceKey, stored=false};
	__property System::UnicodeString businessKey = {read=FbusinessKey, write=FbusinessKey, stored=false};
public:
	/* TRemotable.Create */ inline __fastcall virtual ServiceInfo() : Soap::Invokeregistry::TRemotable() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~ServiceInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<ServiceInfo*> serviceInfo2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ServiceInfos : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	ServiceInfo* operator[](int Index) { return this->ServiceInfoArray[Index]; }
	
private:
	serviceInfo2 FserviceInfo;
	
public:
	__fastcall virtual ServiceInfos();
	__fastcall virtual ~ServiceInfos();
	ServiceInfo* __fastcall GetServiceInfoArray(int Index);
	int __fastcall GetServiceInfoArrayLength();
	__property ServiceInfo* ServiceInfoArray[int Index] = {read=GetServiceInfoArray/*, default*/};
	__property int Len = {read=GetServiceInfoArrayLength, nodefault};
	
__published:
	__property serviceInfo2 serviceInfo = {read=FserviceInfo, write=FserviceInfo};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ServiceList : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	ServiceInfos* FserviceInfos;
	System::UnicodeString Fgeneric;
	System::UnicodeString Foperator;
	Truncated Ftruncated;
	
public:
	__fastcall virtual ServiceList();
	__fastcall virtual ~ServiceList();
	
__published:
	__property ServiceInfos* serviceInfos = {read=FserviceInfos, write=FserviceInfos};
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property System::UnicodeString Operator = {read=Foperator, write=Foperator, stored=false};
	__property Truncated truncated = {read=Ftruncated, write=Ftruncated, stored=false, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef ServiceList serviceList2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BusinessInfo : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::UnicodeString Fname;
	Description Fdescription;
	ServiceInfos* FserviceInfos;
	System::UnicodeString FbusinessKey;
	
public:
	__fastcall virtual ~BusinessInfo();
	
__published:
	__property System::UnicodeString name = {read=Fname, write=Fname};
	__property Description description = {read=Fdescription, write=Fdescription};
	__property ServiceInfos* serviceInfos = {read=FserviceInfos, write=FserviceInfos};
	__property System::UnicodeString businessKey = {read=FbusinessKey, write=FbusinessKey, stored=false};
public:
	/* TRemotable.Create */ inline __fastcall virtual BusinessInfo() : Soap::Invokeregistry::TRemotable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<BusinessInfo*> businessInfo2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BusinessInfos : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	BusinessInfo* operator[](int Index) { return this->BusinessInfoArray[Index]; }
	
private:
	businessInfo2 FbusinessInfo;
	
public:
	__fastcall virtual BusinessInfos();
	__fastcall virtual ~BusinessInfos();
	BusinessInfo* __fastcall GetBusinessInfoArray(int Index);
	int __fastcall GetBusinessInfoArrayLength();
	__property BusinessInfo* BusinessInfoArray[int Index] = {read=GetBusinessInfoArray/*, default*/};
	__property int Len = {read=GetBusinessInfoArrayLength, nodefault};
	
__published:
	__property businessInfo2 businessInfo = {read=FbusinessInfo, write=FbusinessInfo};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION BusinessList : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	BusinessInfos* FbusinessInfos;
	System::UnicodeString Fgeneric;
	System::UnicodeString Foperator;
	Truncated Ftruncated;
	
public:
	__fastcall virtual BusinessList();
	__fastcall virtual ~BusinessList();
	
__published:
	__property BusinessInfos* businessInfos = {read=FbusinessInfos, write=FbusinessInfos};
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property System::UnicodeString Operator = {read=Foperator, write=Foperator, stored=false};
	__property Truncated truncated = {read=Ftruncated, write=Ftruncated, stored=false, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef BusinessList businessList2;

typedef System::DynamicArray<System::UnicodeString> findQualifier;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION FindQualifiers : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	System::UnicodeString operator[](int Index) { return this->WideStringArray[Index]; }
	
private:
	findQualifier FfindQualifier;
	
public:
	__fastcall virtual FindQualifiers();
	System::UnicodeString __fastcall GetWideStringArray(int Index);
	int __fastcall GetWideStringArrayLength();
	__property System::UnicodeString WideStringArray[int Index] = {read=GetWideStringArray/*, default*/};
	__property int Len = {read=GetWideStringArrayLength, nodefault};
	
__published:
	__property findQualifier findQualifier = {read=FfindQualifier, write=FfindQualifier};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~FindQualifiers() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION FindTModel : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	FindQualifiers* FfindQualifiers;
	System::UnicodeString Fname;
	IdentifierBag* FidentifierBag;
	CategoryBag* FcategoryBag;
	System::UnicodeString Fgeneric;
	int FmaxRows;
	
public:
	__fastcall virtual FindTModel();
	__fastcall virtual ~FindTModel();
	
__published:
	__property FindQualifiers* findQualifiers = {read=FfindQualifiers, write=FfindQualifiers};
	__property System::UnicodeString name = {read=Fname, write=Fname};
	__property IdentifierBag* identifierBag = {read=FidentifierBag, write=FidentifierBag};
	__property CategoryBag* categoryBag = {read=FcategoryBag, write=FcategoryBag};
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property int maxRows = {read=FmaxRows, write=FmaxRows, stored=false, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef FindTModel find_tModel;

typedef System::DynamicArray<System::UnicodeString> tModelKey;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TModelBag : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	System::UnicodeString operator[](int Index) { return this->WideStringArray[Index]; }
	
private:
	tModelKey FtModelKey;
	
public:
	__fastcall virtual TModelBag();
	System::UnicodeString __fastcall GetWideStringArray(int Index);
	int __fastcall GetWideStringArrayLength();
	__property System::UnicodeString WideStringArray[int Index] = {read=GetWideStringArray/*, default*/};
	__property int Len = {read=GetWideStringArrayLength, nodefault};
	
__published:
	__property tModelKey tModelKey = {read=FtModelKey, write=FtModelKey};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~TModelBag() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION FindBinding : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	FindQualifiers* FfindQualifiers;
	TModelBag* FtModelBag;
	System::UnicodeString Fgeneric;
	int FmaxRows;
	System::UnicodeString FserviceKey;
	
public:
	__fastcall virtual FindBinding();
	__fastcall virtual ~FindBinding();
	
__published:
	__property FindQualifiers* findQualifiers = {read=FfindQualifiers, write=FfindQualifiers};
	__property TModelBag* tModelBag = {read=FtModelBag, write=FtModelBag};
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property int maxRows = {read=FmaxRows, write=FmaxRows, stored=false, nodefault};
	__property System::UnicodeString serviceKey = {read=FserviceKey, write=FserviceKey, stored=false};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef FindBinding find_binding;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION FindBusiness : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	FindQualifiers* FfindQualifiers;
	System::UnicodeString Fname;
	IdentifierBag* FidentifierBag;
	CategoryBag* FcategoryBag;
	TModelBag* FtModelBag;
	DiscoveryURLs* FdiscoveryURLs;
	System::UnicodeString Fgeneric;
	int FmaxRows;
	
public:
	__fastcall virtual FindBusiness();
	__fastcall virtual ~FindBusiness();
	
__published:
	__property FindQualifiers* findQualifiers = {read=FfindQualifiers, write=FfindQualifiers};
	__property System::UnicodeString name = {read=Fname, write=Fname};
	__property IdentifierBag* identifierBag = {read=FidentifierBag, write=FidentifierBag};
	__property CategoryBag* categoryBag = {read=FcategoryBag, write=FcategoryBag};
	__property TModelBag* tModelBag = {read=FtModelBag, write=FtModelBag};
	__property DiscoveryURLs* discoveryURLs = {read=FdiscoveryURLs, write=FdiscoveryURLs};
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property int maxRows = {read=FmaxRows, write=FmaxRows, stored=false, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef FindBusiness find_business;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION FindService : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	FindQualifiers* FfindQualifiers;
	System::UnicodeString Fname;
	CategoryBag* FcategoryBag;
	TModelBag* FtModelBag;
	System::UnicodeString Fgeneric;
	int FmaxRows;
	System::UnicodeString FbusinessKey;
	
public:
	__fastcall virtual FindService();
	__fastcall virtual ~FindService();
	
__published:
	__property FindQualifiers* findQualifiers = {read=FfindQualifiers, write=FfindQualifiers};
	__property System::UnicodeString name = {read=Fname, write=Fname};
	__property CategoryBag* categoryBag = {read=FcategoryBag, write=FcategoryBag};
	__property TModelBag* tModelBag = {read=FtModelBag, write=FtModelBag};
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property int maxRows = {read=FmaxRows, write=FmaxRows, stored=false, nodefault};
	__property System::UnicodeString businessKey = {read=FbusinessKey, write=FbusinessKey, stored=false};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef FindService find_service;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION GetTModelDetail : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	System::UnicodeString operator[](int Index) { return this->WideStringArray[Index]; }
	
private:
	System::UnicodeString Fgeneric;
	tModelKey FtModelKey;
	
public:
	__fastcall virtual GetTModelDetail();
	System::UnicodeString __fastcall GetWideStringArray(int Index);
	int __fastcall GetWideStringArrayLength();
	__property System::UnicodeString WideStringArray[int Index] = {read=GetWideStringArray/*, default*/};
	__property int Len = {read=GetWideStringArrayLength, nodefault};
	
__published:
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property tModelKey tModelKey = {read=FtModelKey, write=FtModelKey};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~GetTModelDetail() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef GetTModelDetail get_tModelDetail;

typedef System::DynamicArray<System::UnicodeString> bindingKey;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION GetBindingDetail : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	System::UnicodeString operator[](int Index) { return this->WideStringArray[Index]; }
	
private:
	System::UnicodeString Fgeneric;
	bindingKey FbindingKey;
	
public:
	__fastcall virtual GetBindingDetail();
	System::UnicodeString __fastcall GetWideStringArray(int Index);
	int __fastcall GetWideStringArrayLength();
	__property System::UnicodeString WideStringArray[int Index] = {read=GetWideStringArray/*, default*/};
	__property int Len = {read=GetWideStringArrayLength, nodefault};
	
__published:
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property bindingKey bindingKey = {read=FbindingKey, write=FbindingKey};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~GetBindingDetail() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef GetBindingDetail get_bindingDetail;

typedef System::DynamicArray<System::UnicodeString> businessKey;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION GetBusinessDetailExt : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	System::UnicodeString operator[](int Index) { return this->WideStringArray[Index]; }
	
private:
	System::UnicodeString Fgeneric;
	businessKey FbusinessKey;
	
public:
	__fastcall virtual GetBusinessDetailExt();
	System::UnicodeString __fastcall GetWideStringArray(int Index);
	int __fastcall GetWideStringArrayLength();
	__property System::UnicodeString WideStringArray[int Index] = {read=GetWideStringArray/*, default*/};
	__property int Len = {read=GetWideStringArrayLength, nodefault};
	
__published:
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property businessKey businessKey = {read=FbusinessKey, write=FbusinessKey};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~GetBusinessDetailExt() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef GetBusinessDetailExt get_businessDetailExt;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION GetBusinessDetail : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	System::UnicodeString operator[](int Index) { return this->WideStringArray[Index]; }
	
private:
	System::UnicodeString Fgeneric;
	businessKey FbusinessKey;
	
public:
	__fastcall virtual GetBusinessDetail();
	System::UnicodeString __fastcall GetWideStringArray(int Index);
	int __fastcall GetWideStringArrayLength();
	__property System::UnicodeString WideStringArray[int Index] = {read=GetWideStringArray/*, default*/};
	__property int Len = {read=GetWideStringArrayLength, nodefault};
	
__published:
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property businessKey businessKey = {read=FbusinessKey, write=FbusinessKey};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~GetBusinessDetail() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef GetBusinessDetail get_businessDetail;

typedef System::DynamicArray<System::UnicodeString> serviceKey;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION GetServiceDetail : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	System::UnicodeString operator[](int Index) { return this->WideStringArray[Index]; }
	
private:
	System::UnicodeString Fgeneric;
	serviceKey FserviceKey;
	
public:
	__fastcall virtual GetServiceDetail();
	System::UnicodeString __fastcall GetWideStringArray(int Index);
	int __fastcall GetWideStringArrayLength();
	__property System::UnicodeString WideStringArray[int Index] = {read=GetWideStringArray/*, default*/};
	__property int Len = {read=GetWideStringArrayLength, nodefault};
	
__published:
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property serviceKey serviceKey = {read=FserviceKey, write=FserviceKey};
public:
	/* TRemotable.Destroy */ inline __fastcall virtual ~GetServiceDetail() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef GetServiceDetail get_serviceDetail;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TModelInfo : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::UnicodeString Fname;
	System::UnicodeString FtModelKey;
	
__published:
	__property System::UnicodeString name = {read=Fname, write=Fname};
	__property System::UnicodeString tModelKey = {read=FtModelKey, write=FtModelKey, stored=false};
public:
	/* TRemotable.Create */ inline __fastcall virtual TModelInfo() : Soap::Invokeregistry::TRemotable() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~TModelInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<TModelInfo*> tModelInfo2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TModelInfos : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	TModelInfo* operator[](int Index) { return this->TModelInfoArray[Index]; }
	
private:
	tModelInfo2 FtModelInfo;
	
public:
	__fastcall virtual TModelInfos();
	__fastcall virtual ~TModelInfos();
	TModelInfo* __fastcall GetTModelInfoArray(int Index);
	int __fastcall GetTModelInfoArrayLength();
	__property TModelInfo* TModelInfoArray[int Index] = {read=GetTModelInfoArray/*, default*/};
	__property int Len = {read=GetTModelInfoArrayLength, nodefault};
	
__published:
	__property tModelInfo2 tModelInfo = {read=FtModelInfo, write=FtModelInfo};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TModelList : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	TModelInfos* FtModelInfos;
	System::UnicodeString Fgeneric;
	System::UnicodeString Foperator;
	Truncated Ftruncated;
	
public:
	__fastcall virtual TModelList();
	__fastcall virtual ~TModelList();
	
__published:
	__property TModelInfos* tModelInfos = {read=FtModelInfos, write=FtModelInfos};
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property System::UnicodeString Operator = {read=Foperator, write=Foperator, stored=false};
	__property Truncated truncated = {read=Ftruncated, write=Ftruncated, stored=false, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef TModelList tModelList2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TModel : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::UnicodeString Fname;
	Description Fdescription;
	OverviewDoc* FoverviewDoc;
	IdentifierBag* FidentifierBag;
	CategoryBag* FcategoryBag;
	System::UnicodeString FtModelKey;
	System::UnicodeString Foperator;
	System::UnicodeString FauthorizedName;
	
public:
	__fastcall virtual ~TModel();
	
__published:
	__property System::UnicodeString name = {read=Fname, write=Fname};
	__property Description description = {read=Fdescription, write=Fdescription};
	__property OverviewDoc* overviewDoc = {read=FoverviewDoc, write=FoverviewDoc};
	__property IdentifierBag* identifierBag = {read=FidentifierBag, write=FidentifierBag};
	__property CategoryBag* categoryBag = {read=FcategoryBag, write=FcategoryBag};
	__property System::UnicodeString tModelKey = {read=FtModelKey, write=FtModelKey, stored=false};
	__property System::UnicodeString Operator = {read=Foperator, write=Foperator, stored=false};
	__property System::UnicodeString authorizedName = {read=FauthorizedName, write=FauthorizedName, stored=false};
public:
	/* TRemotable.Create */ inline __fastcall virtual TModel() : Soap::Invokeregistry::TRemotable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<TModel*> tModel2;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TModelDetail : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
public:
	TModel* operator[](int Index) { return this->TModelArray[Index]; }
	
private:
	System::UnicodeString Fgeneric;
	System::UnicodeString Foperator;
	Truncated Ftruncated;
	tModel2 FtModel;
	
public:
	__fastcall virtual TModelDetail();
	__fastcall virtual ~TModelDetail();
	TModel* __fastcall GetTModelArray(int Index);
	int __fastcall GetTModelArrayLength();
	__property TModel* TModelArray[int Index] = {read=GetTModelArray/*, default*/};
	__property int Len = {read=GetTModelArrayLength, nodefault};
	
__published:
	__property System::UnicodeString generic = {read=Fgeneric, write=Fgeneric, stored=false};
	__property System::UnicodeString Operator = {read=Foperator, write=Foperator, stored=false};
	__property Truncated truncated = {read=Ftruncated, write=Ftruncated, stored=false, nodefault};
	__property tModel2 tModel = {read=FtModel, write=FtModel};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef TModelDetail tModelDetail2;

__interface  INTERFACE_UUID("{C2AD6D0F-0875-EF31-4035-8D59DF59CBFA}") InquireSoap  : public System::IInvokable 
{
	virtual BindingDetail* __stdcall find_binding(FindBinding* const body) = 0 ;
	virtual BusinessList* __stdcall find_business(FindBusiness* const body) = 0 ;
	virtual ServiceList* __stdcall find_service(FindService* const body) = 0 ;
	virtual TModelList* __stdcall find_tModel(FindTModel* const body) = 0 ;
	virtual BindingDetail* __stdcall get_bindingDetail(GetBindingDetail* const body) = 0 ;
	virtual BusinessDetail* __stdcall get_businessDetail(GetBusinessDetail* const body) = 0 ;
	virtual BusinessDetailExt* __stdcall get_businessDetailExt(GetBusinessDetailExt* const body) = 0 ;
	virtual ServiceDetail* __stdcall get_serviceDetail(GetServiceDetail* const body) = 0 ;
	virtual TModelDetail* __stdcall get_tModelDetail(GetTModelDetail* const body) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall InitInquireV1Types(void);
}	/* namespace Inquire_v1 */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_INQUIRE_V1)
using namespace Soap::Inquire_v1;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif

//-- user supplied -----------------------------------------------------------
#endif // __clang__

#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_Inquire_v1HPP
