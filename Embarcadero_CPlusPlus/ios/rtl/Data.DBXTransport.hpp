// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXTransport.pas' rev: 34.00 (iOS)

#ifndef Data_DbxtransportHPP
#define Data_DbxtransportHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXEncryption.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxtransport
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDbxChannel;
struct TDBXClientInfo;
class DELPHICLASS TDBXChannelInfo;
class DELPHICLASS TDBXCommunicationLayerFactory;
class DELPHICLASS TDBXLocalChannel;
class DELPHICLASS TDBXSocketChannelInfo;
class DELPHICLASS TFilterProperties;
class DELPHICLASS TTransportFilter;
class DELPHICLASS TTransportCypherFilter;
class DELPHICLASS TTransportFilterCollection;
class DELPHICLASS TTransportFilterFactory;
class DELPHICLASS TTransportFilterItem;
class DELPHICLASS TTransportFilterTools;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDbxChannel : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall Open() = 0 ;
	virtual void __fastcall Close() = 0 ;
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count) = 0 ;
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count) = 0 ;
	__fastcall virtual ~TDbxChannel();
	
protected:
	virtual bool __fastcall IsConnectionLost();
	virtual TDBXChannelInfo* __fastcall GetChannelInfo() = 0 ;
	virtual Data::Dbxcommon::TDBXProperties* __fastcall GetDBXProperties();
	virtual void __fastcall SetDBXProperties(Data::Dbxcommon::TDBXProperties* const Properties);
	TDBXChannelInfo* FChannelInfo;
	
private:
	Data::Dbxcommon::TDBXProperties* FDbxProperties;
	
public:
	__property TDBXChannelInfo* ChannelInfo = {read=GetChannelInfo};
	__property Data::Dbxcommon::TDBXProperties* DBXProperties = {read=GetDBXProperties, write=SetDBXProperties};
	__property bool ConnectionLost = {read=IsConnectionLost, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDbxChannel() : System::TObject() { }
	
};


struct DECLSPEC_DRECORD TDBXClientInfo
{
public:
	System::UnicodeString IpAddress;
	System::UnicodeString ClientPort;
	System::UnicodeString Protocol;
	System::UnicodeString AppName;
};


class PASCALIMPLEMENTATION TDBXChannelInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDBXChannelInfo(const int AId);
	
protected:
	virtual System::UnicodeString __fastcall GetInfo();
	
private:
	int FId;
	TDBXClientInfo FClientInfo;
	
public:
	__property int Id = {read=FId, nodefault};
	__property System::UnicodeString Info = {read=GetInfo};
	__property TDBXClientInfo ClientInfo = {read=FClientInfo, write=FClientInfo};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXChannelInfo() { }
	
};


class PASCALIMPLEMENTATION TDBXCommunicationLayerFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static TDBXCommunicationLayerFactory* __fastcall Instance();
	static void __fastcall RegisterLayer(const System::UnicodeString CommLayerId, const Data::Dbxplatform::TObjectClass CommLayerClass);
	static void __fastcall UnregisterLayer(const System::UnicodeString CommLayerId);
	static Data::Dbxcommon::TDBXCommunicationLayer* __fastcall CommunicationLayer(const System::UnicodeString Id);
	static Data::Dbxplatform::TDBXStringArray __fastcall RegisteredLayerList();
	__fastcall TDBXCommunicationLayerFactory();
	__fastcall virtual ~TDBXCommunicationLayerFactory();
	
private:
	static TDBXCommunicationLayerFactory* FSingleton;
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,Data::Dbxplatform::TObjectClass>* FRegisteredLayers;
};


class PASCALIMPLEMENTATION TDBXLocalChannel : public TDbxChannel
{
	typedef TDbxChannel inherited;
	
public:
	__fastcall TDBXLocalChannel(const System::UnicodeString ServerName);
	__fastcall virtual ~TDBXLocalChannel();
	virtual void __fastcall Close();
	virtual void __fastcall Open();
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall WriteLocalData(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall ReadLocalData(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual bool __fastcall HasReadData();
	virtual bool __fastcall HasWriteData();
	
protected:
	virtual TDBXChannelInfo* __fastcall GetChannelInfo();
	
private:
	System::TArray__1<System::Byte> FReadBuffer;
	int FReadCount;
	int FReadOffset;
	bool FHasReadData;
	System::TArray__1<System::Byte> FWriteBuffer;
	int FWriteCount;
	int FWriteOffset;
	bool FHasWriteData;
};


class PASCALIMPLEMENTATION TDBXSocketChannelInfo : public TDBXChannelInfo
{
	typedef TDBXChannelInfo inherited;
	
public:
	__fastcall TDBXSocketChannelInfo(const NativeInt AId, const System::UnicodeString AInfo);
	
protected:
	virtual System::UnicodeString __fastcall GetInfo();
	
private:
	System::UnicodeString FInfo;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSocketChannelInfo() { }
	
};


class PASCALIMPLEMENTATION TFilterProperties : public Data::Dbxplatform::TBaseFilterProperties
{
	typedef Data::Dbxplatform::TBaseFilterProperties inherited;
	
public:
	/* TStringList.Create */ inline __fastcall TFilterProperties()/* overload */ : Data::Dbxplatform::TBaseFilterProperties() { }
	/* TStringList.Create */ inline __fastcall TFilterProperties(bool OwnsObjects)/* overload */ : Data::Dbxplatform::TBaseFilterProperties(OwnsObjects) { }
	/* TStringList.Create */ inline __fastcall TFilterProperties(System::WideChar QuoteChar, System::WideChar Delimiter)/* overload */ : Data::Dbxplatform::TBaseFilterProperties(QuoteChar, Delimiter) { }
	/* TStringList.Create */ inline __fastcall TFilterProperties(System::WideChar QuoteChar, System::WideChar Delimiter, System::Classes::TStringsOptions Options)/* overload */ : Data::Dbxplatform::TBaseFilterProperties(QuoteChar, Delimiter, Options) { }
	/* TStringList.Create */ inline __fastcall TFilterProperties(System::Types::TDuplicates Duplicates, bool Sorted, bool CaseSensitive)/* overload */ : Data::Dbxplatform::TBaseFilterProperties(Duplicates, Sorted, CaseSensitive) { }
	/* TStringList.Destroy */ inline __fastcall virtual ~TFilterProperties() { }
	
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTransportFilter : public Data::Dbxplatform::TFactoryObject
{
	typedef Data::Dbxplatform::TFactoryObject inherited;
	
public:
	static System::UnicodeString __fastcall Encode(const System::TArray__1<System::Byte> Data, const int Pos, const int DataLength);
	static System::TArray__1<System::Byte> __fastcall Decode(const System::UnicodeString StrData);
	__fastcall virtual TTransportFilter();
	virtual System::UnicodeString __fastcall Id() = 0 ;
	virtual System::UnicodeString __fastcall GetParameterValue(const System::UnicodeString ParamName);
	virtual bool __fastcall SetParameterValue(const System::UnicodeString ParamName, const System::UnicodeString ParamValue);
	virtual bool __fastcall SetConfederateParameter(const System::UnicodeString ParamName, const System::UnicodeString ParamValue);
	virtual System::TArray__1<System::Byte> __fastcall ProcessInput(const System::TArray__1<System::Byte> Data) = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall ProcessOutput(const System::TArray__1<System::Byte> Data) = 0 ;
	virtual void __fastcall StartHandshake();
	virtual bool __fastcall HandshakeComplete();
	virtual TTransportFilter* __fastcall GetCollectionFilter(const System::UnicodeString FilterId);
	
protected:
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetParameters();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetUserParameters();
	virtual void __fastcall SetServerInstance(const bool IsServerSide);
	virtual bool __fastcall IsPublicKeyCryptograph();
	virtual bool __fastcall IsServerInstance();
	virtual bool __fastcall IsClientInstance();
	virtual TTransportFilterCollection* __fastcall GetFilterCollection();
	virtual void __fastcall SetFilterCollection(TTransportFilterCollection* const FilterCollection);
	virtual bool __fastcall IsHandshakeStarted();
	
private:
	bool FServerInstance;
	TTransportFilterCollection* FFilterCollection;
	bool FHandshakeStarted;
	
public:
	__property Data::Dbxplatform::TDBXStringArray Parameters = {read=GetParameters};
	__property Data::Dbxplatform::TDBXStringArray UserParameters = {read=GetUserParameters};
	__property bool PublicKeyCryptograph = {read=IsPublicKeyCryptograph, nodefault};
	__property bool ServerInstance = {read=IsServerInstance, write=SetServerInstance, nodefault};
	__property bool ClientInstance = {read=IsClientInstance, nodefault};
	__property TTransportFilterCollection* FilterCollection = {read=GetFilterCollection, write=SetFilterCollection};
	__property bool HandshakeStarted = {read=IsHandshakeStarted, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TTransportFilter() { }
	
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTransportCypherFilter : /*[[sealed]]*/ public TTransportFilter
{
	typedef TTransportFilter inherited;
	
public:
	virtual System::UnicodeString __fastcall GetParameterValue(const System::UnicodeString ParamName);
	virtual System::TArray__1<System::Byte> __fastcall ProcessInput(const System::TArray__1<System::Byte> Data);
	virtual System::TArray__1<System::Byte> __fastcall ProcessOutput(const System::TArray__1<System::Byte> Data);
	virtual bool __fastcall SetParameterValue(const System::UnicodeString ParamName, const System::UnicodeString ParamValue);
	virtual bool __fastcall SetConfederateParameter(const System::UnicodeString ParamName, const System::UnicodeString ParamValue);
	virtual System::UnicodeString __fastcall Id();
	
protected:
	System::UnicodeString __fastcall GetClearKey();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetUserParameters();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetParameters();
	
private:
	Data::Dbxencryption::TPC1Cypher* __fastcall SetUp(const System::UnicodeString Key);
	void __fastcall TearDown(Data::Dbxencryption::TPC1Cypher* &Cypher);
	System::UnicodeString FCypherKey;
	System::UnicodeString FConfederateKey;
	__property System::UnicodeString ClearKey = {read=GetClearKey};
	#define TTransportCypherFilter_Key u"Key"
	
	#define TTransportCypherFilter_Code u"CODE"
	
	#define TTransportCypherFilter_Filterunit u"FilterUnit"
	
public:
	/* TTransportFilter.Create */ inline __fastcall virtual TTransportCypherFilter() : TTransportFilter() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TTransportCypherFilter() { }
	
};


class PASCALIMPLEMENTATION TTransportFilterCollection : public Data::Dbxplatform::TBaseTransportFilterCollection
{
	typedef Data::Dbxplatform::TBaseTransportFilterCollection inherited;
	
public:
	__fastcall TTransportFilterCollection();
	virtual int __fastcall AddFilter(const System::UnicodeString FilterId)/* overload */;
	virtual int __fastcall AddFilter(TTransportFilter* const Filter)/* overload */;
	virtual bool __fastcall RemoveFilter(const int Index);
	virtual TTransportFilter* __fastcall GetFilter(const int Pos)/* overload */;
	virtual TTransportFilter* __fastcall GetFilter(const System::UnicodeString Id)/* overload */;
	virtual bool __fastcall HandshakeComplete();
	virtual void __fastcall StartHandshake();
	virtual System::UnicodeString __fastcall ToJSON();
	static TTransportFilterCollection* __fastcall FromJSON(const System::UnicodeString Json);
	
protected:
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetFilterIdList();
	
public:
	__property Data::Dbxplatform::TDBXStringArray FilterIdList = {read=GetFilterIdList};
public:
	/* TBaseTransportFilterCollection.Destroy */ inline __fastcall virtual ~TTransportFilterCollection() { }
	
};


class PASCALIMPLEMENTATION TTransportFilterFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static TTransportFilterFactory* __fastcall Instance();
	static TTransportFilter* __fastcall CreateFilter(const System::UnicodeString FilterId);
	static void __fastcall RegisterFilter(const System::UnicodeString FilterId, const Data::Dbxplatform::TObjectClass FilterClass)/* overload */;
	static void __fastcall RegisterFilter(const Data::Dbxplatform::TObjectClass FilterClass)/* overload */;
	static void __fastcall UnregisterFilter(const System::UnicodeString FilterId)/* overload */;
	static void __fastcall UnregisterFilter(const Data::Dbxplatform::TObjectClass FilterClass)/* overload */;
	static Data::Dbxplatform::TDBXStringArray __fastcall RegisteredFiltersId();
	__fastcall TTransportFilterFactory();
	__fastcall virtual ~TTransportFilterFactory();
	
private:
	static TTransportFilterFactory* FSingleton;
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,Data::Dbxplatform::TObjectClass>* FRegisteredFilters;
};


class PASCALIMPLEMENTATION TTransportFilterItem : public Data::Dbxplatform::TBaseTransportFilterItem
{
	typedef Data::Dbxplatform::TBaseTransportFilterItem inherited;
	
public:
	__fastcall virtual TTransportFilterItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TTransportFilterItem();
	
protected:
	virtual void __fastcall SetFilterId(const System::UnicodeString FilterId);
	virtual System::UnicodeString __fastcall GetFilterId();
	virtual TTransportFilter* __fastcall GetFilter();
	virtual void __fastcall SetFilter(TTransportFilter* const Filter);
	virtual void __fastcall SetProperties(TFilterProperties* const Value);
	virtual TFilterProperties* __fastcall GetProperties();
	
private:
	System::UnicodeString FFilterId;
	TTransportFilter* FFilter;
	TFilterProperties* FFilterProperties;
	bool FFilterPropertiesChanged;
	void __fastcall UpdateFilterProperties();
	void __fastcall UpdateFilter();
	void __fastcall OnFilterPropertiesChange(System::TObject* Sender);
	
public:
	__property TTransportFilter* Filter = {read=GetFilter, write=SetFilter};
	
__published:
	__property System::UnicodeString FilterId = {read=GetFilterId, write=SetFilterId};
	__property TFilterProperties* Properties = {read=GetProperties, write=SetProperties};
};


class PASCALIMPLEMENTATION TTransportFilterTools : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static System::TArray__1<System::Byte> __fastcall FilterQuery(const System::TArray__1<System::Byte> Buffer);
	static bool __fastcall IsFilterQuery(const System::TArray__1<System::Byte> Buffer);
	static System::TArray__1<System::Byte> __fastcall NoFilter(const System::TArray__1<System::Byte> Buffer);
	static bool __fastcall HasNoFilter(const System::TArray__1<System::Byte> Buffer);
	static bool __fastcall HasPublicKey(const System::TArray__1<System::Byte> Buffer);
	static bool __fastcall HasPublicKeyCryptography(TTransportFilterCollection* const FilterList);
	static void __fastcall EncodeDataLength(const System::TArray__1<System::Byte> Data, const int Len);
	static void __fastcall EncodePublicKeyLength(const System::TArray__1<System::Byte> Data, const int Len);
	static int __fastcall DecodeDataLen(const System::TArray__1<System::Byte> Data);
	static constexpr System::Int8 HeaderLen = System::Int8(0x5);
	
	
private:
	static constexpr System::Int8 HeaderFilter = System::Int8(0xd);
	
	static constexpr System::Int8 HeaderQuery = System::Int8(0x5);
	
	static constexpr System::Int8 HeaderNoFilter = System::Int8(0x6);
	
	static constexpr System::Int8 HeaderPublicKey = System::Int8(0x7);
	
public:
	/* TObject.Create */ inline __fastcall TTransportFilterTools() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTransportFilterTools() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxtransport */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXTRANSPORT)
using namespace Data::Dbxtransport;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxtransportHPP
