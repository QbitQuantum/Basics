// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.MetaTypes.pas' rev: 34.00 (Windows)

#ifndef Rest_Backend_MetatypesHPP
#define Rest_Backend_MetatypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Metatypes
{
//-- forward type declarations -----------------------------------------------
struct TBackendEntityValue;
struct TBackendClassValue;
__interface DELPHIINTERFACE IBackendMetaObject;
typedef System::DelphiInterface<IBackendMetaObject> _di_IBackendMetaObject;
__interface DELPHIINTERFACE IBackendClassName;
typedef System::DelphiInterface<IBackendClassName> _di_IBackendClassName;
__interface DELPHIINTERFACE IBackendDataType;
typedef System::DelphiInterface<IBackendDataType> _di_IBackendDataType;
__interface DELPHIINTERFACE IBackendObjectID;
typedef System::DelphiInterface<IBackendObjectID> _di_IBackendObjectID;
__interface DELPHIINTERFACE IBackendUpdatedAt;
typedef System::DelphiInterface<IBackendUpdatedAt> _di_IBackendUpdatedAt;
__interface DELPHIINTERFACE IBackendCreatedAt;
typedef System::DelphiInterface<IBackendCreatedAt> _di_IBackendCreatedAt;
__interface DELPHIINTERFACE IBackendAuthToken;
typedef System::DelphiInterface<IBackendAuthToken> _di_IBackendAuthToken;
__interface DELPHIINTERFACE IBackendUserName;
typedef System::DelphiInterface<IBackendUserName> _di_IBackendUserName;
__interface DELPHIINTERFACE IBackendGroupName;
typedef System::DelphiInterface<IBackendGroupName> _di_IBackendGroupName;
__interface DELPHIINTERFACE IBackendModuleName;
typedef System::DelphiInterface<IBackendModuleName> _di_IBackendModuleName;
__interface DELPHIINTERFACE IBackendModuleResourceName;
typedef System::DelphiInterface<IBackendModuleResourceName> _di_IBackendModuleResourceName;
__interface DELPHIINTERFACE IBackendDownloadURL;
typedef System::DelphiInterface<IBackendDownloadURL> _di_IBackendDownloadURL;
__interface DELPHIINTERFACE IBackendFileName;
typedef System::DelphiInterface<IBackendFileName> _di_IBackendFileName;
__interface DELPHIINTERFACE IBackendFileID;
typedef System::DelphiInterface<IBackendFileID> _di_IBackendFileID;
__interface DELPHIINTERFACE IBackendExpiresAt;
typedef System::DelphiInterface<IBackendExpiresAt> _di_IBackendExpiresAt;
__interface DELPHIINTERFACE IBackendMetaClass;
typedef System::DelphiInterface<IBackendMetaClass> _di_IBackendMetaClass;
__interface DELPHIINTERFACE IBackendMetaDataType;
typedef System::DelphiInterface<IBackendMetaDataType> _di_IBackendMetaDataType;
__interface DELPHIINTERFACE IBackendMetaFactory;
typedef System::DelphiInterface<IBackendMetaFactory> _di_IBackendMetaFactory;
__interface DELPHIINTERFACE IBackendMetaClassFactory;
typedef System::DelphiInterface<IBackendMetaClassFactory> _di_IBackendMetaClassFactory;
__interface DELPHIINTERFACE IBackendMetaClassObjectFactory;
typedef System::DelphiInterface<IBackendMetaClassObjectFactory> _di_IBackendMetaClassObjectFactory;
__interface DELPHIINTERFACE IBackendMetaUserFactory;
typedef System::DelphiInterface<IBackendMetaUserFactory> _di_IBackendMetaUserFactory;
__interface DELPHIINTERFACE IBackendMetaGroupFactory;
typedef System::DelphiInterface<IBackendMetaGroupFactory> _di_IBackendMetaGroupFactory;
__interface DELPHIINTERFACE IBackendMetaFileFactory;
typedef System::DelphiInterface<IBackendMetaFileFactory> _di_IBackendMetaFileFactory;
__interface DELPHIINTERFACE IBackendMetaDataTypeFactory;
typedef System::DelphiInterface<IBackendMetaDataTypeFactory> _di_IBackendMetaDataTypeFactory;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TBackendEntityValue
{
public:
	static TBackendEntityValue FEmpty;
	
private:
	_di_IBackendMetaObject FData;
	int FFiller;
	System::UnicodeString __fastcall GetBackendClassName();
	System::TDateTime __fastcall GetCreatedAt();
	System::UnicodeString __fastcall GetObjectID();
	System::TDateTime __fastcall GetUpdatedAt();
	System::UnicodeString __fastcall GetAuthToken();
	System::UnicodeString __fastcall GetUserName();
	System::UnicodeString __fastcall GetGroupName();
	System::UnicodeString __fastcall GetDownloadURL();
	System::TDateTime __fastcall GetExpiresAt();
	System::UnicodeString __fastcall GetFileName();
	System::UnicodeString __fastcall GetFileID();
	bool __fastcall GetIsEmpty();
	
public:
	__fastcall TBackendEntityValue(const _di_IBackendMetaObject Intf);
	bool __fastcall TryGetBackendClassName(/* out */ System::UnicodeString &AValue);
	bool __fastcall TryGetObjectID(/* out */ System::UnicodeString &AValue);
	bool __fastcall TryGetUpdatedAt(/* out */ System::TDateTime &AValue);
	bool __fastcall TryGetCreatedAt(/* out */ System::TDateTime &AValue);
	bool __fastcall TryGetExpiresAt(/* out */ System::TDateTime &AValue);
	bool __fastcall TryGetUserName(/* out */ System::UnicodeString &AValue);
	bool __fastcall TryGetGroupName(/* out */ System::UnicodeString &AValue);
	bool __fastcall TryGetFileName(/* out */ System::UnicodeString &AValue);
	bool __fastcall TryGetDownloadURL(/* out */ System::UnicodeString &AValue);
	bool __fastcall TryGetAuthToken(/* out */ System::UnicodeString &AValue);
	bool __fastcall TryGetFileID(/* out */ System::UnicodeString &AValue);
	__property System::UnicodeString BackendClassName = {read=GetBackendClassName};
	__property System::UnicodeString ObjectID = {read=GetObjectID};
	__property System::TDateTime UpdatedAt = {read=GetUpdatedAt};
	__property System::TDateTime CreatedAt = {read=GetCreatedAt};
	__property System::UnicodeString UserName = {read=GetUserName};
	__property System::UnicodeString GroupName = {read=GetGroupName};
	__property System::UnicodeString AuthToken = {read=GetAuthToken};
	__property System::UnicodeString DownloadURL = {read=GetDownloadURL};
	__property System::TDateTime ExpiresAt = {read=GetExpiresAt};
	__property System::UnicodeString FileName = {read=GetFileName};
	__property System::UnicodeString FileID = {read=GetFileID};
	__property _di_IBackendMetaObject Data = {read=FData};
	__property bool IsEmpty = {read=GetIsEmpty};
	/* static */ __property TBackendEntityValue Empty = {read=FEmpty};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	TBackendEntityValue() {}
};


typedef TBackendEntityValue TBackendMetaObject;

struct DECLSPEC_DRECORD TBackendClassValue
{
private:
	_di_IBackendMetaClass FData;
	System::UnicodeString __fastcall GetBackendClassName();
	System::UnicodeString __fastcall GetDataType();
	
public:
	__fastcall TBackendClassValue(const _di_IBackendMetaClass Intf);
	bool __fastcall TryGetBackendClassName(/* out */ System::UnicodeString &AValue);
	bool __fastcall TryGetDataType(/* out */ System::UnicodeString &AValue);
	__property System::UnicodeString BackendClassName = {read=GetBackendClassName};
	__property System::UnicodeString BackendDataType = {read=GetDataType};
	TBackendClassValue() {}
};


typedef TBackendClassValue TBackendMetaClass;

__interface  INTERFACE_UUID("{95F29709-C995-4E69-A16E-3E9FA6D81ED6}") IBackendMetaObject  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{A73AB14F-12C8-4121-AFB1-2E0C55F37BB6}") IBackendClassName  : public IBackendMetaObject 
{
	virtual System::UnicodeString __fastcall GetClassName() = 0 ;
};

__interface  INTERFACE_UUID("{8E75565A-3A1B-44E0-B150-B74927F50F97}") IBackendDataType  : public IBackendMetaObject 
{
	virtual System::UnicodeString __fastcall GetDataType() = 0 ;
};

__interface  INTERFACE_UUID("{CD893599-279D-4000-B7E2-F94B944D6C63}") IBackendObjectID  : public IBackendMetaObject 
{
	virtual System::UnicodeString __fastcall GetObjectID() = 0 ;
};

__interface  INTERFACE_UUID("{16630E95-EE80-4328-8323-6F7FF67C0141}") IBackendUpdatedAt  : public IBackendMetaObject 
{
	virtual System::TDateTime __fastcall GetUpdatedAt() = 0 ;
};

__interface  INTERFACE_UUID("{C3204A92-434F-4008-B356-E41896BC22CA}") IBackendCreatedAt  : public IBackendMetaObject 
{
	virtual System::TDateTime __fastcall GetCreatedAt() = 0 ;
};

__interface  INTERFACE_UUID("{3C4FF6D8-11CA-48D8-8967-B3F1FC06C3EA}") IBackendAuthToken  : public IBackendMetaObject 
{
	virtual System::UnicodeString __fastcall GetAuthToken() = 0 ;
};

__interface  INTERFACE_UUID("{B7022538-2C7D-4F93-A1C8-A7A96545E4BF}") IBackendUserName  : public IBackendMetaObject 
{
	virtual System::UnicodeString __fastcall GetUserName() = 0 ;
};

__interface  INTERFACE_UUID("{BEA0754A-0D59-4D62-96A4-3175A3E8E1EB}") IBackendGroupName  : public IBackendMetaObject 
{
	virtual System::UnicodeString __fastcall GetGroupName() = 0 ;
};

__interface  INTERFACE_UUID("{BEA0754A-0D59-4D62-96A4-3175A3E8E1EB}") IBackendModuleName  : public IBackendMetaObject 
{
	virtual System::UnicodeString __fastcall GetModuleName() = 0 ;
};

__interface  INTERFACE_UUID("{BEA0754A-0D59-4D62-96A4-3175A3E8E1EB}") IBackendModuleResourceName  : public IBackendMetaObject 
{
	virtual System::UnicodeString __fastcall GetResourceName() = 0 ;
};

__interface  INTERFACE_UUID("{0403AF5D-AF5D-4463-97DD-2903DE03EBFD}") IBackendDownloadURL  : public IBackendMetaObject 
{
	virtual System::UnicodeString __fastcall GetDownloadURL() = 0 ;
};

__interface  INTERFACE_UUID("{59E96B63-92B9-4A1D-991E-1487FF26B0A3}") IBackendFileName  : public IBackendMetaObject 
{
	virtual System::UnicodeString __fastcall GetFileName() = 0 ;
};

__interface  INTERFACE_UUID("{B58DA141-82E8-4BD6-920D-9C9E680BEC03}") IBackendFileID  : public IBackendMetaObject 
{
	virtual System::UnicodeString __fastcall GetFileID() = 0 ;
};

__interface  INTERFACE_UUID("{CAD0E4F8-AB04-4EB5-B13C-CD9B0188036C}") IBackendExpiresAt  : public IBackendMetaObject 
{
	virtual System::TDateTime __fastcall GetExpiresAt() = 0 ;
};

__interface  INTERFACE_UUID("{F80536B3-4F7F-4C52-9F53-A81CF608299C}") IBackendMetaClass  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{64064A4C-09AC-4FDC-8A12-31C40AC9E2FC}") IBackendMetaDataType  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{B58EC9B1-060C-4B44-82E9-82F576AB3793}") IBackendMetaFactory  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{B27A40E6-5084-4093-BED3-A329DCC65E92}") IBackendMetaClassFactory  : public IBackendMetaFactory 
{
	virtual TBackendClassValue __fastcall CreateMetaClass(const System::UnicodeString AClassName) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{80E7B794-6088-4A85-A5A2-49ADA2112629}") IBackendMetaClassObjectFactory  : public IBackendMetaFactory 
{
	virtual TBackendEntityValue __fastcall CreateMetaClassObject(const System::UnicodeString AClassName, const System::UnicodeString AObjectID) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{5C1A367B-F06E-492F-BD64-D68CA268671F}") IBackendMetaUserFactory  : public IBackendMetaFactory 
{
	virtual TBackendEntityValue __fastcall CreateMetaUserObject(const System::UnicodeString AObjectID) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{3CB88315-4399-4307-A5E5-CF60C919FF2D}") IBackendMetaGroupFactory  : public IBackendMetaFactory 
{
	virtual TBackendEntityValue __fastcall CreateMetaGroupObject(const System::UnicodeString AGroupName) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{96C22B76-C711-4D7C-90C8-AEA565F622D5}") IBackendMetaFileFactory  : public IBackendMetaFactory 
{
	virtual TBackendEntityValue __fastcall CreateMetaFileObject(const System::UnicodeString AObjectID) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{7FDED929-4F6D-4C41-8AF9-8AE20BFB2EF9}") IBackendMetaDataTypeFactory  : public IBackendMetaFactory 
{
	virtual TBackendClassValue __fastcall CreateMetaDataType(const System::UnicodeString ADataType, const System::UnicodeString ABackendClassName) = 0 /* overload */;
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Metatypes */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_METATYPES)
using namespace Rest::Backend::Metatypes;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND)
using namespace Rest::Backend;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_Backend_MetatypesHPP
