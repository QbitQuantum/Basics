// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.Xmlxform.pas' rev: 34.00 (Windows)

#ifndef Datasnap_XmlxformHPP
#define Datasnap_XmlxformHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Datasnap.DBClient.hpp>
#include <Datasnap.Provider.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <Xml.XmlTransform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Xmlxform
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TXMLTransformProvider;
class DELPHICLASS TXMLTransformClient;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TXMLTransformProvider : public Datasnap::Provider::TCustomProvider
{
	typedef Datasnap::Provider::TCustomProvider inherited;
	
private:
	Datasnap::Dbclient::TClientDataSet* FDataCache;
	Datasnap::Provider::TDataSetProvider* FResolver;
	Xml::Xmltransform::TXMLTransform* FTransformRead;
	Xml::Xmltransform::TXMLTransform* FTransformWrite;
	bool FCacheData;
	System::UnicodeString __fastcall GetXMLDataFile();
	void __fastcall SetXMLDataFile(const System::UnicodeString Value);
	
protected:
	virtual System::OleVariant __fastcall InternalApplyUpdates(const System::OleVariant &Delta, int MaxErrors, /* out */ int &ErrorCount);
	virtual System::OleVariant __fastcall InternalGetRecords(int Count, /* out */ int &RecsOut, Datasnap::Provider::TGetRecordOptions Options, const System::WideString CommandText, System::OleVariant &Params);
	
public:
	__fastcall virtual TXMLTransformProvider(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TXMLTransformProvider();
	
__published:
	__property Xml::Xmltransform::TXMLTransform* TransformRead = {read=FTransformRead};
	__property Xml::Xmltransform::TXMLTransform* TransformWrite = {read=FTransformWrite};
	__property System::UnicodeString XMLDataFile = {read=GetXMLDataFile, write=SetXMLDataFile};
	__property bool CacheData = {read=FCacheData, write=FCacheData, default=0};
	__property BeforeApplyUpdates;
	__property AfterApplyUpdates;
	__property BeforeGetRecords;
	__property AfterGetRecords;
	__property BeforeRowRequest;
	__property AfterRowRequest;
	__property OnDataRequest;
};


class PASCALIMPLEMENTATION TXMLTransformClient : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Datasnap::Dbclient::TClientDataSet* FDataCache;
	Datasnap::Dbclient::TClientDataSet* FSetParamsDataCache;
	Datasnap::Provider::TLocalAppServer* FLocalAppServer;
	Xml::Xmltransform::TXMLTransform* FTransformGetData;
	Xml::Xmltransform::TXMLTransform* FTransformApplyUpdates;
	Xml::Xmltransform::TXMLTransform* FTransformSetParams;
	System::UnicodeString __fastcall GetProviderName();
	Datasnap::Dbclient::TCustomRemoteServer* __fastcall GetRemoteServer();
	void __fastcall SetProviderName(const System::UnicodeString Value);
	void __fastcall SetRemoteServer(Datasnap::Dbclient::TCustomRemoteServer* const Value);
	
protected:
	void __fastcall SetupAppServer();
	
public:
	__fastcall virtual TXMLTransformClient(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TXMLTransformClient();
	virtual System::UnicodeString __fastcall GetDataAsXml(const System::UnicodeString PublishTransformFile);
	virtual int __fastcall ApplyUpdates(const System::UnicodeString UpdateXML, const System::UnicodeString UpdateTransformFile, int MaxErrors);
	void __fastcall SetParams(const System::UnicodeString ParamsXml, const System::UnicodeString ParamsTransformFile);
	
__published:
	__property Datasnap::Dbclient::TCustomRemoteServer* RemoteServer = {read=GetRemoteServer, write=SetRemoteServer};
	__property System::UnicodeString ProviderName = {read=GetProviderName, write=SetProviderName};
	__property Xml::Xmltransform::TXMLTransform* TransformGetData = {read=FTransformGetData};
	__property Xml::Xmltransform::TXMLTransform* TransformApplyUpdates = {read=FTransformApplyUpdates};
	__property Xml::Xmltransform::TXMLTransform* TransformSetParams = {read=FTransformSetParams};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Xmlxform */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_XMLXFORM)
using namespace Datasnap::Xmlxform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_XmlxformHPP
