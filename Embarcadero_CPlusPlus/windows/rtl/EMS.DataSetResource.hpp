// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMS.DataSetResource.pas' rev: 34.00 (Windows)

#ifndef Ems_DatasetresourceHPP
#define Ems_DatasetresourceHPP

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
#include <System.Net.Mime.hpp>
#include <System.JSON.hpp>
#include <System.JSON.Readers.hpp>
#include <System.JSON.Writers.hpp>
#include <EMS.ResourceAPI.hpp>
#include <EMS.ResourceTypes.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.BatchMove.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ems
{
namespace Datasetresource
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMSDataSetAdaptor;
class DELPHICLASS TEMSFDDataSetAdaptor;
class DELPHICLASS TEMSDataSetResource;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
typedef System::TMetaClass* TEMSDataSetAdaptorClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TEMSDataSetAdaptorClass);
#endif /* _WIN64 */

enum DECLSPEC_DENUM TEMSDataSetResouceOption : unsigned char { roEnableParams, roEnablePaging, roEnableSorting, roReturnNewEntityKey, roReturnNewEntityValue, roAppendOnPut };

typedef System::Set<TEMSDataSetResouceOption, TEMSDataSetResouceOption::roEnableParams, TEMSDataSetResouceOption::roAppendOnPut> TEMSDataSetResouceOptions;

enum DECLSPEC_DENUM TEMSDataSetResouceMappingMode : unsigned char { rmGuess, rmEntityToFields, rmEntityToRecord, rmEntityToParams };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSDataSetAdaptor : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	class DELPHICLASS TRegInfo;
	class PASCALIMPLEMENTATION TRegInfo : public System::TObject
	{
		typedef System::TObject inherited;
		
	public:
		System::UnicodeString FMimeType;
		Data::Db::TDataSetClass FDataSetClass;
		TEMSDataSetAdaptorClass FAdaptorClass;
	public:
		/* TObject.Create */ inline __fastcall TRegInfo() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TRegInfo() { }
		
	};
	
	
	
public:
	typedef System::UnicodeString __fastcall (__closure *TGetParamEvent)(const System::UnicodeString AName);
	
	
private:
	static System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TRegInfo*>* FRegistry;
	TEMSDataSetResource* FResource;
	Ems::Resourceapi::TEndpointContext* FContext;
	Data::Db::TDataSet* FDataSet;
	Data::Db::_di_IProviderSupportNG FProvider;
	Data::Db::TParams* FParams;
	int FRecordCount;
	System::UnicodeString FReqMimeType;
	System::UnicodeString FReqCharset;
	System::UnicodeString FRespMimeType;
	System::UnicodeString FRespCharset;
	bool FRespVirtualStore;
	Firedac::Comp::Batchmove::TFDBatchMove* FBatchMove;
	Firedac::Comp::Batchmove::TFDBatchMoveDriver* FReader;
	Firedac::Comp::Batchmove::TFDBatchMoveDriver* FWriter;
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
private:
	template<typename T> T __fastcall CheckReaderClass();
	template<typename T> T __fastcall CheckWriterClass();
	
protected:
	virtual void __fastcall ProcessList();
	virtual void __fastcall ProcessGet();
	virtual void __fastcall ProcessDelete();
	virtual void __fastcall ProcessPost();
	virtual void __fastcall ProcessPut();
	virtual void __fastcall ProcessPutOtPost(Ems::Resourceapi::TEMSBaseResource::TAction AAction);
	virtual bool __fastcall DelegateOpening(Ems::Resourceapi::TEMSBaseResource::TAction AAction);
	virtual void __fastcall GetRecordCount();
	virtual void __fastcall SetPaging(int ARecsSkip, int ARecsMax)/* overload */;
	virtual void __fastcall SetSorting(const System::UnicodeString ASortingFields)/* overload */;
	virtual void __fastcall ExceptionToHTTPError(System::Sysutils::Exception* AException);
	virtual bool __fastcall RequireMetadataSetup(Ems::Resourceapi::TEMSBaseResource::TAction AAction);
	void __fastcall SetPaging()/* overload */;
	void __fastcall SetSorting()/* overload */;
	void __fastcall SetParamValues();
	void __fastcall GetParamValues();
	void __fastcall SetFieldValues();
	void __fastcall GetFieldValues(System::Classes::TStrings* const AFieldList);
	bool __fastcall LocateEntity();
	void __fastcall DeleteEntity();
	bool __fastcall IsEntityNotNull();
	
public:
	__fastcall TEMSDataSetAdaptor();
	__fastcall virtual ~TEMSDataSetAdaptor();
	__classmethod void __fastcall Register(const System::UnicodeString AMimeType, Data::Db::TDataSetClass ADataSetClass, TEMSDataSetAdaptorClass AAdaptorClass);
	static void __fastcall RegisterParent(Data::Db::TDataSetClass ADataSetClass, TEMSDataSetAdaptorClass AAdaptorClass);
	__classmethod TEMSDataSetAdaptorClass __fastcall Lookup(const System::UnicodeString AMimeType, Data::Db::TDataSetClass ADataSetClass, bool ARequired, bool AAllowDefault);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSFDDataSetAdaptor : public TEMSDataSetAdaptor
{
	typedef TEMSDataSetAdaptor inherited;
	
public:
	#define TEMSFDDataSetAdaptor_CSortMacro L"SORT"
	
	#define TEMSFDDataSetAdaptor_CPageSkipMacro L"SKIP"
	
	#define TEMSFDDataSetAdaptor_CPageMaxMacro L"MAX"
	
	
private:
	// __classmethod void __fastcall Create@();
	
private:
	Firedac::Stan::Intf::TFDStorageFormat __fastcall GetFormat(const System::UnicodeString AMimeType, /* out */ System::UnicodeString &ACharset);
	Firedac::Comp::Dataset::TFDDataSet* __fastcall GetFDDataSet();
	Firedac::Comp::Client::TFDCustomSchemaAdapter* __fastcall GetFDSchema();
	
protected:
	virtual void __fastcall ProcessList();
	virtual void __fastcall ProcessPost();
	virtual bool __fastcall DelegateOpening(Ems::Resourceapi::TEMSBaseResource::TAction AAction);
	virtual void __fastcall GetRecordCount();
	virtual void __fastcall SetPaging(int ARecsSkip, int ARecsMax)/* overload */;
	virtual void __fastcall SetSorting(const System::UnicodeString ASortingFields)/* overload */;
	virtual void __fastcall ExceptionToHTTPError(System::Sysutils::Exception* AException);
	virtual bool __fastcall RequireMetadataSetup(Ems::Resourceapi::TEMSBaseResource::TAction AAction);
	
private:
	// __classmethod void __fastcall Destroy@();
public:
	/* TEMSDataSetAdaptor.Create */ inline __fastcall TEMSFDDataSetAdaptor() : TEMSDataSetAdaptor() { }
	/* TEMSDataSetAdaptor.Destroy */ inline __fastcall virtual ~TEMSFDDataSetAdaptor() { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  SetPaging(){ TEMSDataSetAdaptor::SetPaging(); }
	inline void __fastcall  SetSorting(){ TEMSDataSetAdaptor::SetSorting(); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TEMSDataSetResource : public Ems::Resourceapi::TEMSBaseResource
{
	typedef Ems::Resourceapi::TEMSBaseResource inherited;
	
public:
	#define TEMSDataSetResource_CDefaultPageParamName L"page"
	
	static const System::Int8 CDefaultPageSize = System::Int8(0x32);
	
	#define TEMSDataSetResource_CDefaultSortingParamPrefix L"sf"
	
	#define TEMSDataSetResource_CCallbackName L"callback"
	
	
private:
	Data::Db::TDataSet* FDataSet;
	System::UnicodeString FKeyFields;
	System::Classes::TStrings* FKeyFieldList;
	System::UnicodeString FValueFields;
	System::Classes::TStrings* FValueFieldList;
	bool FDefaultValueFields;
	TEMSDataSetResouceMappingMode FMappingMode;
	TEMSDataSetResouceOptions FOptions;
	System::UnicodeString FPageParamName;
	int FPageSize;
	System::UnicodeString FSortingParamPrefix;
	TEMSDataSetAdaptor* FAdaptor;
	void __fastcall SetValueFields(const System::UnicodeString AValue);
	void __fastcall SetKeyFields(const System::UnicodeString AValue);
	bool __fastcall IsPPNS();
	bool __fastcall IsSPPS();
	void __fastcall SetDataSet(Data::Db::TDataSet* AValue);
	System::UnicodeString __fastcall GetRequestHeader(Ems::Resourceapi::TEndpointRequest* ARequest, const System::UnicodeString AName);
	void __fastcall SetResponse(Ems::Resourceapi::TEndpointResponse* AResponse, System::Classes::TStream* &AStream);
	void __fastcall PrepareAdapter(Ems::Resourceapi::TEndpointContext* AContext, Ems::Resourceapi::TEndpointRequest* ARequest, Ems::Resourceapi::TEndpointResponse* AResponse, Ems::Resourceapi::TEMSBaseResource::TAction AAction);
	void __fastcall GetResponseMime(Ems::Resourceapi::TEndpointContext* const AContext, System::UnicodeString &AMimeType, System::UnicodeString &ACharset);
	void __fastcall GetRequestMime(Ems::Resourceapi::TEndpointContext* const AContext, System::UnicodeString &AMimeType, System::UnicodeString &ACharset);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall CheckAction(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEMSBaseResource::TAction AAction);
	virtual bool __fastcall DoExcludeParam(const System::UnicodeString AName);
	__property System::Classes::TStrings* KeyFieldList = {read=FKeyFieldList};
	__property System::Classes::TStrings* ValueFieldList = {read=FValueFieldList};
	
public:
	__fastcall virtual TEMSDataSetResource(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TEMSDataSetResource();
	virtual void __fastcall List(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	virtual void __fastcall Get(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	virtual void __fastcall Put(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	virtual void __fastcall Post(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	virtual void __fastcall Delete(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEndpointRequest* const ARequest, Ems::Resourceapi::TEndpointResponse* const AResponse);
	
__published:
	__property Data::Db::TDataSet* DataSet = {read=FDataSet, write=SetDataSet};
	__property System::UnicodeString KeyFields = {read=FKeyFields, write=SetKeyFields};
	__property System::UnicodeString ValueFields = {read=FValueFields, write=SetValueFields};
	__property TEMSDataSetResouceMappingMode MappingMode = {read=FMappingMode, write=FMappingMode, default=0};
	__property TEMSDataSetResouceOptions Options = {read=FOptions, write=FOptions, default=47};
	__property System::UnicodeString PageParamName = {read=FPageParamName, write=FPageParamName, stored=IsPPNS};
	__property int PageSize = {read=FPageSize, write=FPageSize, default=50};
	__property System::UnicodeString SortingParamPrefix = {read=FSortingParamPrefix, write=FSortingParamPrefix, stored=IsSPPS};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Datasetresource */
}	/* namespace Ems */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMS_DATASETRESOURCE)
using namespace Ems::Datasetresource;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMS)
using namespace Ems;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ems_DatasetresourceHPP
