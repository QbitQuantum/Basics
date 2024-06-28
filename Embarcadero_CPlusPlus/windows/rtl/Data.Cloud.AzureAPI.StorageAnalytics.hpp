// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Cloud.AzureAPI.StorageAnalytics.pas' rev: 34.00 (Windows)

#ifndef Data_Cloud_Azureapi_StorageanalyticsHPP
#define Data_Cloud_Azureapi_StorageanalyticsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XMLDoc.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Cloud
{
namespace Azureapi
{
namespace Storageanalytics
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCorsRule;
class DELPHICLASS TStorageServiceProperties;
class DELPHICLASS TStorageServiceStats;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCorsRule : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStrings* FAllowedOrigins;
	System::Classes::TStrings* FAllowedMethods;
	int FMaxAgeInSeconds;
	System::Classes::TStrings* FExposedHeaders;
	System::Classes::TStrings* FAllowedHeaders;
	void __fastcall LoadFromXMLNode(const Xml::Xmlintf::_di_IXMLNode AValue);
	System::UnicodeString __fastcall GetXML();
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall GetAllowedOrigins();
	System::DynamicArray<System::UnicodeString> __fastcall GetAllowedHeaders();
	System::DynamicArray<System::UnicodeString> __fastcall GetAllowedMethods();
	System::DynamicArray<System::UnicodeString> __fastcall GetExposedHeaders();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall GetAllowedOrigins();
	System::TArray__1<System::UnicodeString> __fastcall GetAllowedHeaders();
	System::TArray__1<System::UnicodeString> __fastcall GetAllowedMethods();
	System::TArray__1<System::UnicodeString> __fastcall GetExposedHeaders();
#endif /* _WIN64 */
	
public:
	__fastcall TCorsRule();
	__fastcall virtual ~TCorsRule();
	void __fastcall AddAllowedOrigin(const System::UnicodeString AValue);
	void __fastcall AddAllowedHeader(const System::UnicodeString AValue);
	void __fastcall AddExposedHeader(const System::UnicodeString AValue);
	void __fastcall AddAllowedMethod(const System::UnicodeString AValue);
#ifndef _WIN64
	__property System::DynamicArray<System::UnicodeString> AllowedOrigins = {read=GetAllowedOrigins};
	__property System::DynamicArray<System::UnicodeString> AllowedMethods = {read=GetAllowedMethods};
#else /* _WIN64 */
	__property System::TArray__1<System::UnicodeString> AllowedOrigins = {read=GetAllowedOrigins};
	__property System::TArray__1<System::UnicodeString> AllowedMethods = {read=GetAllowedMethods};
#endif /* _WIN64 */
	__property int MaxAgeInSeconds = {read=FMaxAgeInSeconds, write=FMaxAgeInSeconds, nodefault};
#ifndef _WIN64
	__property System::DynamicArray<System::UnicodeString> ExposedHeaders = {read=GetExposedHeaders};
	__property System::DynamicArray<System::UnicodeString> AllowedHeaders = {read=GetAllowedHeaders};
#else /* _WIN64 */
	__property System::TArray__1<System::UnicodeString> ExposedHeaders = {read=GetExposedHeaders};
	__property System::TArray__1<System::UnicodeString> AllowedHeaders = {read=GetAllowedHeaders};
#endif /* _WIN64 */
	__property System::UnicodeString XML = {read=GetXML};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStorageServiceProperties : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	class DELPHICLASS TRetentionPolicy;
	class PASCALIMPLEMENTATION TRetentionPolicy : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		bool FEnabled;
		int FDays;
		void __fastcall LoadFromXMLNode(const Xml::Xmlintf::_di_IXMLNode AValue);
		System::UnicodeString __fastcall GetXML();
		
	public:
		__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
		__property int Days = {read=FDays, write=FDays, nodefault};
		__property System::UnicodeString XML = {read=GetXML};
	public:
		/* TObject.Create */ inline __fastcall TRetentionPolicy() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TRetentionPolicy() { }
		
	};
	
	
	class DELPHICLASS TMetric;
	class PASCALIMPLEMENTATION TMetric : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		bool FEnabled;
		bool FIncludeAPI;
		TStorageServiceProperties::TRetentionPolicy* FRetentionPolicy;
		void __fastcall LoadFromXMLNode(const Xml::Xmlintf::_di_IXMLNode AValue);
		System::UnicodeString __fastcall GetXML();
		virtual System::UnicodeString __fastcall GetNodeName();
		
	public:
		__fastcall TMetric();
		__fastcall virtual ~TMetric();
		__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
		__property bool IncludeAPI = {read=FIncludeAPI, write=FIncludeAPI, nodefault};
		__property TStorageServiceProperties::TRetentionPolicy* RetentionPolicy = {read=FRetentionPolicy};
		__property System::UnicodeString XML = {read=GetXML};
	};
	
	
	class DELPHICLASS THourMetric;
	class PASCALIMPLEMENTATION THourMetric : public TStorageServiceProperties::TMetric
	{
		typedef TStorageServiceProperties::TMetric inherited;
		
	private:
		virtual System::UnicodeString __fastcall GetNodeName();
	public:
		/* TMetric.Create */ inline __fastcall THourMetric() : TStorageServiceProperties::TMetric() { }
		/* TMetric.Destroy */ inline __fastcall virtual ~THourMetric() { }
		
	};
	
	
	class DELPHICLASS TMinuteMetric;
	class PASCALIMPLEMENTATION TMinuteMetric : public TStorageServiceProperties::TMetric
	{
		typedef TStorageServiceProperties::TMetric inherited;
		
	private:
		virtual System::UnicodeString __fastcall GetNodeName();
	public:
		/* TMetric.Create */ inline __fastcall TMinuteMetric() : TStorageServiceProperties::TMetric() { }
		/* TMetric.Destroy */ inline __fastcall virtual ~TMinuteMetric() { }
		
	};
	
	
	class DELPHICLASS TLogging;
	class PASCALIMPLEMENTATION TLogging : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		bool FLogDelete;
		bool FLogRead;
		bool FLogWrite;
		TStorageServiceProperties::TRetentionPolicy* FRetentionPolicy;
		void __fastcall LoadFromXMLNode(Xml::Xmlintf::_di_IXMLNode AValue);
		System::UnicodeString __fastcall GetXML();
		
	public:
		__fastcall TLogging();
		__fastcall virtual ~TLogging();
		__property bool LogDelete = {read=FLogDelete, write=FLogDelete, nodefault};
		__property bool LogRead = {read=FLogRead, write=FLogRead, nodefault};
		__property bool LogWrite = {read=FLogWrite, write=FLogWrite, nodefault};
		__property TStorageServiceProperties::TRetentionPolicy* RetentionPolicy = {read=FRetentionPolicy};
		__property System::UnicodeString XML = {read=GetXML};
	};
	
	
	class DELPHICLASS TCors;
	class PASCALIMPLEMENTATION TCors : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		System::Generics::Collections::TList__1<TCorsRule*>* FRules;
		void __fastcall LoadFromXMLNode(const Xml::Xmlintf::_di_IXMLNode AValue);
		System::UnicodeString __fastcall GetXML();
#ifndef _WIN64
		System::DynamicArray<TCorsRule*> __fastcall GetRules();
#else /* _WIN64 */
		System::TArray__1<TCorsRule*> __fastcall GetRules();
#endif /* _WIN64 */
		
	public:
		__fastcall TCors();
		__fastcall virtual ~TCors();
		void __fastcall AddRule(TCorsRule* const AValue);
#ifndef _WIN64
		__property System::DynamicArray<TCorsRule*> Rules = {read=GetRules};
#else /* _WIN64 */
		__property System::TArray__1<TCorsRule*> Rules = {read=GetRules};
#endif /* _WIN64 */
		__property System::UnicodeString XML = {read=GetXML};
	};
	
	
	
private:
	TLogging* FLogging;
	THourMetric* FHourMetrics;
	TMinuteMetric* FMinuteMetrics;
	TCors* FCors;
	System::UnicodeString __fastcall GetXML();
	
public:
	__fastcall TStorageServiceProperties();
	__fastcall virtual ~TStorageServiceProperties();
	void __fastcall LoadFromXML(const System::UnicodeString AValue);
	__property TLogging* Logging = {read=FLogging};
	__property THourMetric* HourMetrics = {read=FHourMetrics};
	__property TMinuteMetric* MinuteMetrics = {read=FMinuteMetrics};
	__property TCors* Cors = {read=FCors};
	__property System::UnicodeString XML = {read=GetXML};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStorageServiceStats : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TGRStatus : unsigned char { Live, Bootstrap, Unavailable };
	
	
private:
	class DELPHICLASS TGeoReplication;
	class PASCALIMPLEMENTATION TGeoReplication : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		TStorageServiceStats::TGRStatus FStatus;
		System::UnicodeString FLastSyncTime;
		TStorageServiceStats::TGRStatus __fastcall GetStatus(const System::UnicodeString AValue);
		System::UnicodeString __fastcall GetStatusDef(TStorageServiceStats::TGRStatus AValue);
		void __fastcall LoadFromXMLNode(const Xml::Xmlintf::_di_IXMLNode AValue);
		System::UnicodeString __fastcall GetXML();
		
	public:
		__property TStorageServiceStats::TGRStatus Status = {read=FStatus, write=FStatus, nodefault};
		__property System::UnicodeString LastSyncTime = {read=FLastSyncTime, write=FLastSyncTime};
		__property System::UnicodeString XML = {read=GetXML};
	public:
		/* TObject.Create */ inline __fastcall TGeoReplication() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TGeoReplication() { }
		
	};
	
	
	
private:
	TGeoReplication* FGeoReplication;
	System::UnicodeString __fastcall GetXML();
	
public:
	__fastcall TStorageServiceStats();
	__fastcall virtual ~TStorageServiceStats();
	void __fastcall LoadFromXML(const System::UnicodeString AValue);
	__property TGeoReplication* GeoReplication = {read=FGeoReplication};
	__property System::UnicodeString XML = {read=GetXML};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define cStorageAnalyticsVersion L"1.0"
#define cStorageServiceProperties L"StorageServiceProperties"
#define cLogging L"Logging"
#define cRetentionPolicy L"RetentionPolicy"
#define cMetrics L"Metrics"
#define cHourMetrics L"HourMetrics"
#define cMinuteMetrics L"MinuteMetrics"
#define cCorsRule L"CorsRule"
#define cCors L"Cors"
#define cVersion L"Version"
#define cEnabled L"Enabled"
#define cDelete L"Delete"
#define cRead L"Read"
#define cWrite L"Write"
#define cDays L"Days"
#define cIncludeAPIs L"IncludeAPIs"
#define cAllowedOrigins L"AllowedOrigins"
#define cAllowedMethods L"AllowedMethods"
#define cExposedHeaders L"ExposedHeaders"
#define cAllowedHeaders L"AllowedHeaders"
#define cMaxAgeInSeconds L"MaxAgeInSeconds"
#define cStorageServiceStats L"StorageServiceStats"
#define cGeoReplication L"GeoReplication"
#define cStatus L"Status"
#define cLastSyncTime L"LastSyncTime"
#define cLiveStatus L"live"
#define cBootstrapStatus L"bootstrap"
#define cUnavailableStatus L"unavailable"
}	/* namespace Storageanalytics */
}	/* namespace Azureapi */
}	/* namespace Cloud */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_CLOUD_AZUREAPI_STORAGEANALYTICS)
using namespace Data::Cloud::Azureapi::Storageanalytics;
#endif
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
#endif	// Data_Cloud_Azureapi_StorageanalyticsHPP
