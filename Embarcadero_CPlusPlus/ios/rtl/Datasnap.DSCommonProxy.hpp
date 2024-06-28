// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSCommonProxy.pas' rev: 34.00 (iOS)

#ifndef Datasnap_DscommonproxyHPP
#define Datasnap_DscommonproxyHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXCommon.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dscommonproxy
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSMethodParametersEntity;
class DELPHICLASS TDSProxyClass;
class DELPHICLASS TDSProxyMetadata;
__interface DELPHIINTERFACE IDSProxyMetaDataLoader;
typedef System::DelphiInterface<IDSProxyMetaDataLoader> _di_IDSProxyMetaDataLoader;
__interface DELPHIINTERFACE IDSProxyWriter;
typedef System::DelphiInterface<IDSProxyWriter> _di_IDSProxyWriter;
class DELPHICLASS TDSProxyStreamWriter;
class DELPHICLASS TDSProxyMetaDataLoader;
class DELPHICLASS TDSProxyMethod;
class DELPHICLASS TDSProxyParameter;
class DELPHICLASS TDSProxyException;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDSMethodParametersEntity : public Data::Dbxcommontable::TDBXTableEntity
{
	typedef Data::Dbxcommontable::TDBXTableEntity inherited;
	
public:
	__fastcall TDSMethodParametersEntity(Data::Dbxcommontable::TDBXTable* const Table, const bool OwnTable)/* overload */;
	__fastcall TDSMethodParametersEntity(const bool OwnTable)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetMethodAlias();
	void __fastcall SetMethodAlias(const System::UnicodeString ClassName);
	System::UnicodeString __fastcall GetServerClassName();
	void __fastcall SetServerClassName(const System::UnicodeString ClassName);
	System::UnicodeString __fastcall GetServerMethodName();
	void __fastcall SetServerMethodName(const System::UnicodeString ClassName);
	System::UnicodeString __fastcall GetParameterName();
	void __fastcall SetParameterName(const System::UnicodeString ParameterName);
	System::UnicodeString __fastcall GetParameterTypeName();
	void __fastcall SetParameterTypeName(const System::UnicodeString DataTypeName);
	System::UnicodeString __fastcall GetParameterTypeUnit();
	void __fastcall SetParameterTypeUnit(const System::UnicodeString DataTypeUnit);
	int __fastcall GetParameterDirection();
	void __fastcall SetParameterDirection(const int ParameterDirection);
	int __fastcall GetParameterDBXDataType();
	void __fastcall SetParameterDBXDataType(const int DbxDataType);
	int __fastcall GetParameterDBXSubDataType();
	void __fastcall SetParameterDBXSubDataType(const int DbxSubDataType);
	int __fastcall GetDBXParameterDirection();
	void __fastcall SetDBXParameterDirection(const int DbxParameterDirection);
	
private:
	static Data::Dbxcommontable::TDBXTable* __fastcall CreateMethodTable();
	
public:
	__property System::UnicodeString MethodAlias = {read=GetMethodAlias, write=SetMethodAlias};
	__property System::UnicodeString ServerClassName = {read=GetServerClassName, write=SetServerClassName};
	__property System::UnicodeString ServerMethodName = {read=GetServerMethodName, write=SetServerMethodName};
	__property System::UnicodeString ParameterName = {read=GetParameterName, write=SetParameterName};
	__property System::UnicodeString ParameterTypeName = {read=GetParameterTypeName, write=SetParameterTypeName};
	__property System::UnicodeString ParameterTypeUnit = {read=GetParameterTypeUnit, write=SetParameterTypeUnit};
	__property int ParameterDirection = {read=GetParameterDirection, write=SetParameterDirection, nodefault};
	__property int ParameterDBXDataType = {read=GetParameterDBXDataType, write=SetParameterDBXDataType, nodefault};
	__property int ParameterDBXSubDataType = {read=GetParameterDBXSubDataType, write=SetParameterDBXSubDataType, nodefault};
	__property int DBXParameterDirection = {read=GetDBXParameterDirection, write=SetDBXParameterDirection, nodefault};
public:
	/* TDBXTableEntity.Destroy */ inline __fastcall virtual ~TDSMethodParametersEntity() { }
	
};


class PASCALIMPLEMENTATION TDSProxyClass : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual ~TDSProxyClass();
	void __fastcall AddMethod(TDSProxyMethod* const ProxyMethod);
	
private:
	System::UnicodeString FProxyClassName;
	TDSProxyMethod* FFirstMethod;
	TDSProxyMethod* FLastMethod;
	TDSProxyClass* FNext;
	
public:
	__property System::UnicodeString ProxyClassName = {read=FProxyClassName, write=FProxyClassName};
	__property TDSProxyMethod* FirstMethod = {read=FFirstMethod, write=FFirstMethod};
	__property TDSProxyMethod* LastMethod = {read=FLastMethod, write=FLastMethod};
	__property TDSProxyClass* Next = {read=FNext, write=FNext};
public:
	/* TObject.Create */ inline __fastcall TDSProxyClass() : System::TObject() { }
	
};


class PASCALIMPLEMENTATION TDSProxyMetadata : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual ~TDSProxyMetadata();
	void __fastcall LoadMetadata(TDSMethodParametersEntity* MethodParameters);
	
private:
	void __fastcall AddClass(TDSProxyClass* const ProxyClass);
	TDSProxyClass* FFirstClass;
	TDSProxyClass* FLastClass;
	void __fastcall Clear();
	
public:
	__property TDSProxyClass* Classes = {read=FFirstClass};
public:
	/* TObject.Create */ inline __fastcall TDSProxyMetadata() : System::TObject() { }
	
};


__interface  INTERFACE_UUID("{768E0AB8-3FEB-4BBF-8AAB-9ACE5A8D2CBF}") IDSProxyMetaDataLoader  : public System::IInterface 
{
	virtual void __fastcall Load(TDSProxyMetadata* AMetaData) = 0 ;
};

__interface  INTERFACE_UUID("{0840A428-9BD6-4F76-BEF4-969013CDABCC}") IDSProxyWriter  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall Name() = 0 ;
	virtual void __fastcall Write(const System::UnicodeString Line) = 0 ;
	virtual void __fastcall WriteLine() = 0 ;
};

class PASCALIMPLEMENTATION TDSProxyStreamWriter : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::UnicodeString FName;
	System::Classes::TStreamWriter* FStreamWriter;
	void __fastcall Write(const System::UnicodeString Line);
	void __fastcall WriteLine();
	System::UnicodeString __fastcall Name();
	
public:
	__fastcall TDSProxyStreamWriter(System::UnicodeString Name, System::Classes::TStream* Stream, System::Sysutils::TEncoding* Encoding);
	__fastcall virtual ~TDSProxyStreamWriter();
private:
	void *__IDSProxyWriter;	// IDSProxyWriter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0840A428-9BD6-4F76-BEF4-969013CDABCC}
	operator _di_IDSProxyWriter()
	{
		_di_IDSProxyWriter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSProxyWriter*(void) { return (IDSProxyWriter*)&__IDSProxyWriter; }
	#endif
	
};


class PASCALIMPLEMENTATION TDSProxyMetaDataLoader : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Data::Dbxcommon::TDBXConnection* FConnection;
	System::UnicodeString FConnectionString;
	System::DelphiInterface<System::Sysutils::TFunc__1<Data::Dbxcommon::TDBXConnection*> > FOpenConnection;
	System::DelphiInterface<System::Sysutils::TProc__1<Data::Dbxcommon::TDBXConnection*> > FCloseConnection;
	void __fastcall Load(TDSProxyMetadata* MetaData);
	void __fastcall LoadFromConnection(Data::Dbxcommon::TDBXConnection* AConnection, TDSProxyMetadata* AMetaData);
	
public:
	__fastcall TDSProxyMetaDataLoader(Data::Dbxcommon::TDBXConnection* AConnection)/* overload */;
	__fastcall TDSProxyMetaDataLoader(const System::UnicodeString AConnectionString)/* overload */;
	__fastcall TDSProxyMetaDataLoader(System::DelphiInterface<System::Sysutils::TFunc__1<Data::Dbxcommon::TDBXConnection*> > AOpenConnection, System::DelphiInterface<System::Sysutils::TProc__1<Data::Dbxcommon::TDBXConnection*> > ACloseConnection)/* overload */;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSProxyMetaDataLoader() { }
	
private:
	void *__IDSProxyMetaDataLoader;	// IDSProxyMetaDataLoader 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {768E0AB8-3FEB-4BBF-8AAB-9ACE5A8D2CBF}
	operator _di_IDSProxyMetaDataLoader()
	{
		_di_IDSProxyMetaDataLoader intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSProxyMetaDataLoader*(void) { return (IDSProxyMetaDataLoader*)&__IDSProxyMetaDataLoader; }
	#endif
	
};


class PASCALIMPLEMENTATION TDSProxyMethod : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual ~TDSProxyMethod();
	void __fastcall AddParameter(TDSProxyParameter* const ProxyParameter);
	bool __fastcall HasReturnValue();
	void __fastcall InitParameters();
	bool __fastcall HasParametersWithUserType();
	
private:
	TDSProxyParameter* FFirstParameter;
	TDSProxyParameter* FLastParameter;
	System::UnicodeString FProxyMethodName;
	System::UnicodeString FMethodAlias;
	TDSProxyMethod* FNext;
	int FInputCount;
	int FOutputCount;
	TDSProxyParameter* FReturnParameter;
	int FParameterCount;
	bool FHasUserTypeParameter;
	
public:
	__property System::UnicodeString ProxyMethodName = {read=FProxyMethodName, write=FProxyMethodName};
	__property TDSProxyMethod* Next = {read=FNext, write=FNext};
	__property int InputCount = {read=FInputCount, nodefault};
	__property int OutputCount = {read=FOutputCount, nodefault};
	__property System::UnicodeString MethodAlias = {read=FMethodAlias, write=FMethodAlias};
	__property TDSProxyParameter* Parameters = {read=FFirstParameter};
	__property int ParameterCount = {read=FParameterCount, nodefault};
	__property TDSProxyParameter* ReturnParameter = {read=FReturnParameter};
public:
	/* TObject.Create */ inline __fastcall TDSProxyMethod() : System::TObject() { }
	
};


class PASCALIMPLEMENTATION TDSProxyParameter : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual void __fastcall SetTypeUnit(const System::UnicodeString TypeUnit);
	virtual System::UnicodeString __fastcall GetTypeUnit();
	virtual bool __fastcall IsKnownJSONTypeName();
	
private:
	TDSProxyParameter* FNext;
	int FParameterDirection;
	int FDataType;
	int FSubDataType;
	System::UnicodeString FParameterName;
	System::UnicodeString FTypeName;
	System::UnicodeString FTypeUnit;
	
public:
	__property System::UnicodeString TypeName = {read=FTypeName, write=FTypeName};
	__property TDSProxyParameter* Next = {read=FNext, write=FNext};
	__property int ParameterDirection = {read=FParameterDirection, write=FParameterDirection, nodefault};
	__property int DataType = {read=FDataType, write=FDataType, nodefault};
	__property int SubDataType = {read=FSubDataType, write=FSubDataType, nodefault};
	__property System::UnicodeString ParameterName = {read=FParameterName, write=FParameterName};
	__property System::UnicodeString TypeUnit = {read=GetTypeUnit, write=SetTypeUnit};
	__property bool KnownJSONTypeName = {read=IsKnownJSONTypeName, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDSProxyParameter() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSProxyParameter() { }
	
};


class PASCALIMPLEMENTATION TDSProxyException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall TDSProxyException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall TDSProxyException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall TDSProxyException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall TDSProxyException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall TDSProxyException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall TDSProxyException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall TDSProxyException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall TDSProxyException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDSProxyException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDSProxyException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDSProxyException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDSProxyException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~TDSProxyException() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define sImplementation u"implementation"
#define sInterface u"interface"
#define sASMethodsPrefix u"AS_*"
#define sDSAdminClassName u"DSAdmin"
#define sDSMetadataClassName u"DSMetadata"
}	/* namespace Dscommonproxy */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSCOMMONPROXY)
using namespace Datasnap::Dscommonproxy;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DscommonproxyHPP
