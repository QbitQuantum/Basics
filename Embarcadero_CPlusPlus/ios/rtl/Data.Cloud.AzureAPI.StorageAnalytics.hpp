// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Cloud.AzureAPI.StorageAnalytics.pas' rev: 34.00 (iOS)

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
	System::TArray__1<System::UnicodeString> __fastcall GetAllowedOrigins();
	System::TArray__1<System::UnicodeString> __fastcall GetAllowedHeaders();
	System::TArray__1<System::UnicodeString> __fastcall GetAllowedMethods();
	System::TArray__1<System::UnicodeString> __fastcall GetExposedHeaders();
	
public:
	__fastcall TCorsRule();
	__fastcall virtual ~TCorsRule();
	void __fastcall AddAllowedOrigin(const System::UnicodeString AValue);
	void __fastcall AddAllowedHeader(const System::UnicodeString AValue);
	void __fastcall AddExposedHeader(const System::UnicodeString AValue);
	void __fastcall AddAllowedMethod(const System::UnicodeString AValue);
	__property System::TArray__1<System::UnicodeString> AllowedOrigins = {read=GetAllowedOrigins};
	__property System::TArray__1<System::UnicodeString> AllowedMethods = {read=GetAllowedMethods};
	__property int MaxAgeInSeconds = {read=FMaxAgeInSeconds, write=FMaxAgeInSeconds, nodefault};
	__property System::TArray__1<System::UnicodeString> ExposedHeaders = {read=GetExposedHeaders};
	__property System::TArray__1<System::UnicodeString> AllowedHeaders = {read=GetAllowedHeaders};
	__property System::UnicodeString XML = {read=GetXML};
};


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
		System::TArray__1<TCorsRule*> __fastcall GetRules();
		
	public:
		__fastcall TCors();
		__fastcall virtual ~TCors();
		void __fastcall AddRule(TCorsRule* const AValue);
		__property System::TArray__1<TCorsRule*> Rules = {read=GetRules};
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


//-- var, const, procedure ---------------------------------------------------
#define cStorageAnalyticsVersion u"1.0"
#define cStorageServiceProperties u"StorageServiceProperties"
#define cLogging u"Logging"
#define cRetentionPolicy u"RetentionPolicy"
#define cMetrics u"Metrics"
#define cHourMetrics u"HourMetrics"
#define cMinuteMetrics u"MinuteMetrics"
#define cCorsRule u"CorsRule"
#define cCors u"Cors"
#define cVersion u"Version"
#define cEnabled u"Enabled"
#define cDelete u"Delete"
#define cRead u"Read"
#define cWrite u"Write"
#define cDays u"Days"
#define cIncludeAPIs u"IncludeAPIs"
#define cAllowedOrigins u"AllowedOrigins"
#define cAllowedMethods u"AllowedMethods"
#define cExposedHeaders u"ExposedHeaders"
#define cAllowedHeaders u"AllowedHeaders"
#define cMaxAgeInSeconds u"MaxAgeInSeconds"
#define cStorageServiceStats u"StorageServiceStats"
#define cGeoReplication u"GeoReplication"
#define cStatus u"Status"
#define cLastSyncTime u"LastSyncTime"
#define cLiveStatus u"live"
#define cBootstrapStatus u"bootstrap"
#define cUnavailableStatus u"unavailable"
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
