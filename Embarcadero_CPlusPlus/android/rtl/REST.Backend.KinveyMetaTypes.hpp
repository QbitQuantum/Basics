﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.KinveyMetaTypes.pas' rev: 34.00 (Android)

#ifndef Rest_Backend_KinveymetatypesHPP
#define Rest_Backend_KinveymetatypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.JSON.hpp>
#include <REST.Backend.MetaTypes.hpp>
#include <REST.Backend.KinveyApi.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Kinveymetatypes
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMetaFactory;
class DELPHICLASS TMetaClass;
class DELPHICLASS TMetaClassName;
class DELPHICLASS TMetaDataType;
class DELPHICLASS TMetaObject;
class DELPHICLASS TMetaUser;
class DELPHICLASS TMetaLogin;
class DELPHICLASS TMetaFile;
class DELPHICLASS TMetaUploadedFile;
class DELPHICLASS TMetaFileObject;
class DELPHICLASS TMetaCreatedObject;
class DELPHICLASS TMetaClassObject;
class DELPHICLASS TMetaUpdatedObjectAt;
class DELPHICLASS TMetaFoundObject;
class DELPHICLASS TMetaUserObject;
class DELPHICLASS TMetaUpdatedUser;
class DELPHICLASS TMetaFoundUser;
class DELPHICLASS TMetaLoginUser;
class DELPHICLASS TMetaSignupUser;
class DELPHICLASS TMetaUpdatedUserAt;
class DELPHICLASS TKinveyMetaFactory;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMetaFactory : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	Rest::Backend::Metatypes::TBackendClassValue __fastcall CreateMetaClass(const System::UnicodeString AClassName);
	Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaClassObject(const System::UnicodeString AClassName, const System::UnicodeString AObjectID);
	Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUserObject(const System::UnicodeString AObjectID);
	Rest::Backend::Metatypes::TBackendClassValue __fastcall CreateMetaDataType(const System::UnicodeString ADataType, const System::UnicodeString ABackendClassName);
	Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaFileObject(const System::UnicodeString AFileID);
public:
	/* TObject.Create */ inline __fastcall TMetaFactory() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaFactory() { }
	
private:
	void *__IBackendMetaFileFactory;	// Rest::Backend::Metatypes::IBackendMetaFileFactory 
	void *__IBackendMetaDataTypeFactory;	// Rest::Backend::Metatypes::IBackendMetaDataTypeFactory 
	void *__IBackendMetaUserFactory;	// Rest::Backend::Metatypes::IBackendMetaUserFactory 
	void *__IBackendMetaClassObjectFactory;	// Rest::Backend::Metatypes::IBackendMetaClassObjectFactory 
	void *__IBackendMetaClassFactory;	// Rest::Backend::Metatypes::IBackendMetaClassFactory 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {96C22B76-C711-4D7C-90C8-AEA565F622D5}
	operator Rest::Backend::Metatypes::_di_IBackendMetaFileFactory()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaFileFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaFileFactory*(void) { return (Rest::Backend::Metatypes::IBackendMetaFileFactory*)&__IBackendMetaFileFactory; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7FDED929-4F6D-4C41-8AF9-8AE20BFB2EF9}
	operator Rest::Backend::Metatypes::_di_IBackendMetaDataTypeFactory()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaDataTypeFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaDataTypeFactory*(void) { return (Rest::Backend::Metatypes::IBackendMetaDataTypeFactory*)&__IBackendMetaDataTypeFactory; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5C1A367B-F06E-492F-BD64-D68CA268671F}
	operator Rest::Backend::Metatypes::_di_IBackendMetaUserFactory()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaUserFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaUserFactory*(void) { return (Rest::Backend::Metatypes::IBackendMetaUserFactory*)&__IBackendMetaUserFactory; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {80E7B794-6088-4A85-A5A2-49ADA2112629}
	operator Rest::Backend::Metatypes::_di_IBackendMetaClassObjectFactory()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaClassObjectFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaClassObjectFactory*(void) { return (Rest::Backend::Metatypes::IBackendMetaClassObjectFactory*)&__IBackendMetaClassObjectFactory; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B27A40E6-5084-4093-BED3-A329DCC65E92}
	operator Rest::Backend::Metatypes::_di_IBackendMetaClassFactory()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaClassFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaClassFactory*(void) { return (Rest::Backend::Metatypes::IBackendMetaClassFactory*)&__IBackendMetaClassFactory; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B58EC9B1-060C-4B44-82E9-82F576AB3793}
	operator Rest::Backend::Metatypes::_di_IBackendMetaFactory()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaFactory*(void) { return (Rest::Backend::Metatypes::IBackendMetaFactory*)&__IBackendMetaFileFactory; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMetaClass : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::UnicodeString FClassName;
	System::UnicodeString FDataType;
	
protected:
	System::UnicodeString __fastcall GetClassName();
	System::UnicodeString __fastcall GetDataType();
	
public:
	__fastcall TMetaClass(const System::UnicodeString AClassName)/* overload */;
	__fastcall TMetaClass(const System::UnicodeString ADataType, const System::UnicodeString AClassName)/* overload */;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaClass() { }
	
private:
	void *__IBackendMetaObject;	// Rest::Backend::Metatypes::IBackendMetaObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendMetaObject; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMetaClassName : public TMetaClass
{
	typedef TMetaClass inherited;
	
public:
	/* TMetaClass.Create */ inline __fastcall TMetaClassName(const System::UnicodeString AClassName)/* overload */ : TMetaClass(AClassName) { }
	/* TMetaClass.Create */ inline __fastcall TMetaClassName(const System::UnicodeString ADataType, const System::UnicodeString AClassName)/* overload */ : TMetaClass(ADataType, AClassName) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaClassName() { }
	
private:
	void *__IBackendClassName;	// Rest::Backend::Metatypes::IBackendClassName 
	void *__IBackendMetaClass;	// Rest::Backend::Metatypes::IBackendMetaClass 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A73AB14F-12C8-4121-AFB1-2E0C55F37BB6}
	operator Rest::Backend::Metatypes::_di_IBackendClassName()
	{
		Rest::Backend::Metatypes::_di_IBackendClassName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendClassName*(void) { return (Rest::Backend::Metatypes::IBackendClassName*)&__IBackendClassName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F80536B3-4F7F-4C52-9F53-A81CF608299C}
	operator Rest::Backend::Metatypes::_di_IBackendMetaClass()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaClass intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaClass*(void) { return (Rest::Backend::Metatypes::IBackendMetaClass*)&__IBackendMetaClass; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMetaDataType : public TMetaClass
{
	typedef TMetaClass inherited;
	
public:
	/* TMetaClass.Create */ inline __fastcall TMetaDataType(const System::UnicodeString AClassName)/* overload */ : TMetaClass(AClassName) { }
	/* TMetaClass.Create */ inline __fastcall TMetaDataType(const System::UnicodeString ADataType, const System::UnicodeString AClassName)/* overload */ : TMetaClass(ADataType, AClassName) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaDataType() { }
	
private:
	void *__IBackendDataType;	// Rest::Backend::Metatypes::IBackendDataType 
	void *__IBackendClassName;	// Rest::Backend::Metatypes::IBackendClassName 
	void *__IBackendMetaClass;	// Rest::Backend::Metatypes::IBackendMetaClass 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8E75565A-3A1B-44E0-B150-B74927F50F97}
	operator Rest::Backend::Metatypes::_di_IBackendDataType()
	{
		Rest::Backend::Metatypes::_di_IBackendDataType intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendDataType*(void) { return (Rest::Backend::Metatypes::IBackendDataType*)&__IBackendDataType; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A73AB14F-12C8-4121-AFB1-2E0C55F37BB6}
	operator Rest::Backend::Metatypes::_di_IBackendClassName()
	{
		Rest::Backend::Metatypes::_di_IBackendClassName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendClassName*(void) { return (Rest::Backend::Metatypes::IBackendClassName*)&__IBackendClassName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F80536B3-4F7F-4C52-9F53-A81CF608299C}
	operator Rest::Backend::Metatypes::_di_IBackendMetaClass()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaClass intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaClass*(void) { return (Rest::Backend::Metatypes::IBackendMetaClass*)&__IBackendMetaClass; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TMetaObject : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Kinveyapi::TKinveyApi::TObjectID FObjectID;
	
protected:
	System::UnicodeString __fastcall GetObjectID();
	System::TDateTime __fastcall GetCreatedAt();
	System::TDateTime __fastcall GetUpdatedAt();
	System::UnicodeString __fastcall GetClassName();
	
public:
	__fastcall TMetaObject(const Rest::Backend::Kinveyapi::TKinveyApi::TObjectID &AObjectID);
	__property Rest::Backend::Kinveyapi::TKinveyApi::TObjectID ObjectID = {read=FObjectID};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaObject() { }
	
private:
	void *__IBackendMetaObject;	// Rest::Backend::Metatypes::IBackendMetaObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendMetaObject; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaUser : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Kinveyapi::TKinveyApi::TUser FUser;
	
protected:
	System::UnicodeString __fastcall GetObjectID();
	System::TDateTime __fastcall GetCreatedAt();
	System::TDateTime __fastcall GetUpdatedAt();
	System::UnicodeString __fastcall GetUserName();
	
public:
	__fastcall TMetaUser(const Rest::Backend::Kinveyapi::TKinveyApi::TUser &AUser);
	__property Rest::Backend::Kinveyapi::TKinveyApi::TUser User = {read=FUser};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaUser() { }
	
private:
	void *__IBackendMetaObject;	// Rest::Backend::Metatypes::IBackendMetaObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendMetaObject; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaLogin : public TMetaUser
{
	typedef TMetaUser inherited;
	
private:
	Rest::Backend::Kinveyapi::TKinveyApi::TLogin FLogin;
	
protected:
	System::UnicodeString __fastcall GetAuthTOken();
	
public:
	__fastcall TMetaLogin(const Rest::Backend::Kinveyapi::TKinveyApi::TLogin &ALogin);
	__property Rest::Backend::Kinveyapi::TKinveyApi::TLogin Login = {read=FLogin};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaLogin() { }
	
};


class PASCALIMPLEMENTATION TMetaFile : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Kinveyapi::TKinveyApi::TFile FFile;
	
protected:
	System::UnicodeString __fastcall GetDownloadURL();
	System::UnicodeString __fastcall GetFileName();
	System::TDateTime __fastcall GetExpiresAt();
	System::UnicodeString __fastcall GetFileID();
	
public:
	__fastcall TMetaFile(const Rest::Backend::Kinveyapi::TKinveyApi::TFile &AFile);
	__property Rest::Backend::Kinveyapi::TKinveyApi::TFile FileValue = {read=FFile};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaFile() { }
	
private:
	void *__IBackendMetaObject;	// Rest::Backend::Metatypes::IBackendMetaObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendMetaObject; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaUploadedFile : public TMetaFile
{
	typedef TMetaFile inherited;
	
public:
	/* TMetaFile.Create */ inline __fastcall TMetaUploadedFile(const Rest::Backend::Kinveyapi::TKinveyApi::TFile &AFile) : TMetaFile(AFile) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaUploadedFile() { }
	
private:
	void *__IBackendExpiresAt;	// Rest::Backend::Metatypes::IBackendExpiresAt 
	void *__IBackendFileName;	// Rest::Backend::Metatypes::IBackendFileName 
	void *__IBackendDownloadURL;	// Rest::Backend::Metatypes::IBackendDownloadURL 
	void *__IBackendFileID;	// Rest::Backend::Metatypes::IBackendFileID 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CAD0E4F8-AB04-4EB5-B13C-CD9B0188036C}
	operator Rest::Backend::Metatypes::_di_IBackendExpiresAt()
	{
		Rest::Backend::Metatypes::_di_IBackendExpiresAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendExpiresAt*(void) { return (Rest::Backend::Metatypes::IBackendExpiresAt*)&__IBackendExpiresAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {59E96B63-92B9-4A1D-991E-1487FF26B0A3}
	operator Rest::Backend::Metatypes::_di_IBackendFileName()
	{
		Rest::Backend::Metatypes::_di_IBackendFileName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendFileName*(void) { return (Rest::Backend::Metatypes::IBackendFileName*)&__IBackendFileName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0403AF5D-AF5D-4463-97DD-2903DE03EBFD}
	operator Rest::Backend::Metatypes::_di_IBackendDownloadURL()
	{
		Rest::Backend::Metatypes::_di_IBackendDownloadURL intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendDownloadURL*(void) { return (Rest::Backend::Metatypes::IBackendDownloadURL*)&__IBackendDownloadURL; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B58DA141-82E8-4BD6-920D-9C9E680BEC03}
	operator Rest::Backend::Metatypes::_di_IBackendFileID()
	{
		Rest::Backend::Metatypes::_di_IBackendFileID intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendFileID*(void) { return (Rest::Backend::Metatypes::IBackendFileID*)&__IBackendFileID; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendExpiresAt; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaFileObject : public TMetaFile
{
	typedef TMetaFile inherited;
	
public:
	/* TMetaFile.Create */ inline __fastcall TMetaFileObject(const Rest::Backend::Kinveyapi::TKinveyApi::TFile &AFile) : TMetaFile(AFile) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaFileObject() { }
	
private:
	void *__IBackendExpiresAt;	// Rest::Backend::Metatypes::IBackendExpiresAt 
	void *__IBackendFileName;	// Rest::Backend::Metatypes::IBackendFileName 
	void *__IBackendDownloadURL;	// Rest::Backend::Metatypes::IBackendDownloadURL 
	void *__IBackendFileID;	// Rest::Backend::Metatypes::IBackendFileID 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CAD0E4F8-AB04-4EB5-B13C-CD9B0188036C}
	operator Rest::Backend::Metatypes::_di_IBackendExpiresAt()
	{
		Rest::Backend::Metatypes::_di_IBackendExpiresAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendExpiresAt*(void) { return (Rest::Backend::Metatypes::IBackendExpiresAt*)&__IBackendExpiresAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {59E96B63-92B9-4A1D-991E-1487FF26B0A3}
	operator Rest::Backend::Metatypes::_di_IBackendFileName()
	{
		Rest::Backend::Metatypes::_di_IBackendFileName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendFileName*(void) { return (Rest::Backend::Metatypes::IBackendFileName*)&__IBackendFileName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0403AF5D-AF5D-4463-97DD-2903DE03EBFD}
	operator Rest::Backend::Metatypes::_di_IBackendDownloadURL()
	{
		Rest::Backend::Metatypes::_di_IBackendDownloadURL intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendDownloadURL*(void) { return (Rest::Backend::Metatypes::IBackendDownloadURL*)&__IBackendDownloadURL; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B58DA141-82E8-4BD6-920D-9C9E680BEC03}
	operator Rest::Backend::Metatypes::_di_IBackendFileID()
	{
		Rest::Backend::Metatypes::_di_IBackendFileID intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendFileID*(void) { return (Rest::Backend::Metatypes::IBackendFileID*)&__IBackendFileID; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendExpiresAt; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaCreatedObject : public TMetaObject
{
	typedef TMetaObject inherited;
	
public:
	/* TMetaObject.Create */ inline __fastcall TMetaCreatedObject(const Rest::Backend::Kinveyapi::TKinveyApi::TObjectID &AObjectID) : TMetaObject(AObjectID) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaCreatedObject() { }
	
private:
	void *__IBackendCreatedAt;	// Rest::Backend::Metatypes::IBackendCreatedAt 
	void *__IBackendClassName;	// Rest::Backend::Metatypes::IBackendClassName 
	void *__IBackendObjectID;	// Rest::Backend::Metatypes::IBackendObjectID 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C3204A92-434F-4008-B356-E41896BC22CA}
	operator Rest::Backend::Metatypes::_di_IBackendCreatedAt()
	{
		Rest::Backend::Metatypes::_di_IBackendCreatedAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendCreatedAt*(void) { return (Rest::Backend::Metatypes::IBackendCreatedAt*)&__IBackendCreatedAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A73AB14F-12C8-4121-AFB1-2E0C55F37BB6}
	operator Rest::Backend::Metatypes::_di_IBackendClassName()
	{
		Rest::Backend::Metatypes::_di_IBackendClassName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendClassName*(void) { return (Rest::Backend::Metatypes::IBackendClassName*)&__IBackendClassName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CD893599-279D-4000-B7E2-F94B944D6C63}
	operator Rest::Backend::Metatypes::_di_IBackendObjectID()
	{
		Rest::Backend::Metatypes::_di_IBackendObjectID intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendObjectID*(void) { return (Rest::Backend::Metatypes::IBackendObjectID*)&__IBackendObjectID; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendCreatedAt; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaClassObject : public TMetaObject
{
	typedef TMetaObject inherited;
	
public:
	/* TMetaObject.Create */ inline __fastcall TMetaClassObject(const Rest::Backend::Kinveyapi::TKinveyApi::TObjectID &AObjectID) : TMetaObject(AObjectID) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaClassObject() { }
	
private:
	void *__IBackendObjectID;	// Rest::Backend::Metatypes::IBackendObjectID 
	void *__IBackendClassName;	// Rest::Backend::Metatypes::IBackendClassName 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CD893599-279D-4000-B7E2-F94B944D6C63}
	operator Rest::Backend::Metatypes::_di_IBackendObjectID()
	{
		Rest::Backend::Metatypes::_di_IBackendObjectID intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendObjectID*(void) { return (Rest::Backend::Metatypes::IBackendObjectID*)&__IBackendObjectID; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A73AB14F-12C8-4121-AFB1-2E0C55F37BB6}
	operator Rest::Backend::Metatypes::_di_IBackendClassName()
	{
		Rest::Backend::Metatypes::_di_IBackendClassName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendClassName*(void) { return (Rest::Backend::Metatypes::IBackendClassName*)&__IBackendClassName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendObjectID; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaUpdatedObjectAt : public TMetaObject
{
	typedef TMetaObject inherited;
	
public:
	/* TMetaObject.Create */ inline __fastcall TMetaUpdatedObjectAt(const Rest::Backend::Kinveyapi::TKinveyApi::TObjectID &AObjectID) : TMetaObject(AObjectID) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaUpdatedObjectAt() { }
	
private:
	void *__IBackendUpdatedAt;	// Rest::Backend::Metatypes::IBackendUpdatedAt 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16630E95-EE80-4328-8323-6F7FF67C0141}
	operator Rest::Backend::Metatypes::_di_IBackendUpdatedAt()
	{
		Rest::Backend::Metatypes::_di_IBackendUpdatedAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendUpdatedAt*(void) { return (Rest::Backend::Metatypes::IBackendUpdatedAt*)&__IBackendUpdatedAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendUpdatedAt; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaFoundObject : public TMetaObject
{
	typedef TMetaObject inherited;
	
public:
	/* TMetaObject.Create */ inline __fastcall TMetaFoundObject(const Rest::Backend::Kinveyapi::TKinveyApi::TObjectID &AObjectID) : TMetaObject(AObjectID) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaFoundObject() { }
	
private:
	void *__IBackendUpdatedAt;	// Rest::Backend::Metatypes::IBackendUpdatedAt 
	void *__IBackendCreatedAt;	// Rest::Backend::Metatypes::IBackendCreatedAt 
	void *__IBackendObjectID;	// Rest::Backend::Metatypes::IBackendObjectID 
	void *__IBackendClassName;	// Rest::Backend::Metatypes::IBackendClassName 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16630E95-EE80-4328-8323-6F7FF67C0141}
	operator Rest::Backend::Metatypes::_di_IBackendUpdatedAt()
	{
		Rest::Backend::Metatypes::_di_IBackendUpdatedAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendUpdatedAt*(void) { return (Rest::Backend::Metatypes::IBackendUpdatedAt*)&__IBackendUpdatedAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C3204A92-434F-4008-B356-E41896BC22CA}
	operator Rest::Backend::Metatypes::_di_IBackendCreatedAt()
	{
		Rest::Backend::Metatypes::_di_IBackendCreatedAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendCreatedAt*(void) { return (Rest::Backend::Metatypes::IBackendCreatedAt*)&__IBackendCreatedAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CD893599-279D-4000-B7E2-F94B944D6C63}
	operator Rest::Backend::Metatypes::_di_IBackendObjectID()
	{
		Rest::Backend::Metatypes::_di_IBackendObjectID intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendObjectID*(void) { return (Rest::Backend::Metatypes::IBackendObjectID*)&__IBackendObjectID; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A73AB14F-12C8-4121-AFB1-2E0C55F37BB6}
	operator Rest::Backend::Metatypes::_di_IBackendClassName()
	{
		Rest::Backend::Metatypes::_di_IBackendClassName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendClassName*(void) { return (Rest::Backend::Metatypes::IBackendClassName*)&__IBackendClassName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendUpdatedAt; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaUserObject : public TMetaObject
{
	typedef TMetaObject inherited;
	
public:
	/* TMetaObject.Create */ inline __fastcall TMetaUserObject(const Rest::Backend::Kinveyapi::TKinveyApi::TObjectID &AObjectID) : TMetaObject(AObjectID) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaUserObject() { }
	
private:
	void *__IBackendObjectID;	// Rest::Backend::Metatypes::IBackendObjectID 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CD893599-279D-4000-B7E2-F94B944D6C63}
	operator Rest::Backend::Metatypes::_di_IBackendObjectID()
	{
		Rest::Backend::Metatypes::_di_IBackendObjectID intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendObjectID*(void) { return (Rest::Backend::Metatypes::IBackendObjectID*)&__IBackendObjectID; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaUpdatedUser : public TMetaUser
{
	typedef TMetaUser inherited;
	
public:
	/* TMetaUser.Create */ inline __fastcall TMetaUpdatedUser(const Rest::Backend::Kinveyapi::TKinveyApi::TUser &AUser) : TMetaUser(AUser) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaUpdatedUser() { }
	
private:
	void *__IBackendUserName;	// Rest::Backend::Metatypes::IBackendUserName 
	void *__IBackendUpdatedAt;	// Rest::Backend::Metatypes::IBackendUpdatedAt 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B7022538-2C7D-4F93-A1C8-A7A96545E4BF}
	operator Rest::Backend::Metatypes::_di_IBackendUserName()
	{
		Rest::Backend::Metatypes::_di_IBackendUserName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendUserName*(void) { return (Rest::Backend::Metatypes::IBackendUserName*)&__IBackendUserName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16630E95-EE80-4328-8323-6F7FF67C0141}
	operator Rest::Backend::Metatypes::_di_IBackendUpdatedAt()
	{
		Rest::Backend::Metatypes::_di_IBackendUpdatedAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendUpdatedAt*(void) { return (Rest::Backend::Metatypes::IBackendUpdatedAt*)&__IBackendUpdatedAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendUserName; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaFoundUser : public TMetaUser
{
	typedef TMetaUser inherited;
	
public:
	/* TMetaUser.Create */ inline __fastcall TMetaFoundUser(const Rest::Backend::Kinveyapi::TKinveyApi::TUser &AUser) : TMetaUser(AUser) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaFoundUser() { }
	
private:
	void *__IBackendUserName;	// Rest::Backend::Metatypes::IBackendUserName 
	void *__IBackendUpdatedAt;	// Rest::Backend::Metatypes::IBackendUpdatedAt 
	void *__IBackendCreatedAt;	// Rest::Backend::Metatypes::IBackendCreatedAt 
	void *__IBackendObjectID;	// Rest::Backend::Metatypes::IBackendObjectID 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B7022538-2C7D-4F93-A1C8-A7A96545E4BF}
	operator Rest::Backend::Metatypes::_di_IBackendUserName()
	{
		Rest::Backend::Metatypes::_di_IBackendUserName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendUserName*(void) { return (Rest::Backend::Metatypes::IBackendUserName*)&__IBackendUserName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16630E95-EE80-4328-8323-6F7FF67C0141}
	operator Rest::Backend::Metatypes::_di_IBackendUpdatedAt()
	{
		Rest::Backend::Metatypes::_di_IBackendUpdatedAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendUpdatedAt*(void) { return (Rest::Backend::Metatypes::IBackendUpdatedAt*)&__IBackendUpdatedAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C3204A92-434F-4008-B356-E41896BC22CA}
	operator Rest::Backend::Metatypes::_di_IBackendCreatedAt()
	{
		Rest::Backend::Metatypes::_di_IBackendCreatedAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendCreatedAt*(void) { return (Rest::Backend::Metatypes::IBackendCreatedAt*)&__IBackendCreatedAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CD893599-279D-4000-B7E2-F94B944D6C63}
	operator Rest::Backend::Metatypes::_di_IBackendObjectID()
	{
		Rest::Backend::Metatypes::_di_IBackendObjectID intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendObjectID*(void) { return (Rest::Backend::Metatypes::IBackendObjectID*)&__IBackendObjectID; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendUserName; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaLoginUser : public TMetaLogin
{
	typedef TMetaLogin inherited;
	
public:
	/* TMetaLogin.Create */ inline __fastcall TMetaLoginUser(const Rest::Backend::Kinveyapi::TKinveyApi::TLogin &ALogin) : TMetaLogin(ALogin) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaLoginUser() { }
	
private:
	void *__IBackendAuthToken;	// Rest::Backend::Metatypes::IBackendAuthToken 
	void *__IBackendUserName;	// Rest::Backend::Metatypes::IBackendUserName 
	void *__IBackendUpdatedAt;	// Rest::Backend::Metatypes::IBackendUpdatedAt 
	void *__IBackendCreatedAt;	// Rest::Backend::Metatypes::IBackendCreatedAt 
	void *__IBackendObjectID;	// Rest::Backend::Metatypes::IBackendObjectID 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3C4FF6D8-11CA-48D8-8967-B3F1FC06C3EA}
	operator Rest::Backend::Metatypes::_di_IBackendAuthToken()
	{
		Rest::Backend::Metatypes::_di_IBackendAuthToken intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendAuthToken*(void) { return (Rest::Backend::Metatypes::IBackendAuthToken*)&__IBackendAuthToken; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B7022538-2C7D-4F93-A1C8-A7A96545E4BF}
	operator Rest::Backend::Metatypes::_di_IBackendUserName()
	{
		Rest::Backend::Metatypes::_di_IBackendUserName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendUserName*(void) { return (Rest::Backend::Metatypes::IBackendUserName*)&__IBackendUserName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16630E95-EE80-4328-8323-6F7FF67C0141}
	operator Rest::Backend::Metatypes::_di_IBackendUpdatedAt()
	{
		Rest::Backend::Metatypes::_di_IBackendUpdatedAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendUpdatedAt*(void) { return (Rest::Backend::Metatypes::IBackendUpdatedAt*)&__IBackendUpdatedAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C3204A92-434F-4008-B356-E41896BC22CA}
	operator Rest::Backend::Metatypes::_di_IBackendCreatedAt()
	{
		Rest::Backend::Metatypes::_di_IBackendCreatedAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendCreatedAt*(void) { return (Rest::Backend::Metatypes::IBackendCreatedAt*)&__IBackendCreatedAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CD893599-279D-4000-B7E2-F94B944D6C63}
	operator Rest::Backend::Metatypes::_di_IBackendObjectID()
	{
		Rest::Backend::Metatypes::_di_IBackendObjectID intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendObjectID*(void) { return (Rest::Backend::Metatypes::IBackendObjectID*)&__IBackendObjectID; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendAuthToken; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaSignupUser : public TMetaLogin
{
	typedef TMetaLogin inherited;
	
public:
	/* TMetaLogin.Create */ inline __fastcall TMetaSignupUser(const Rest::Backend::Kinveyapi::TKinveyApi::TLogin &ALogin) : TMetaLogin(ALogin) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaSignupUser() { }
	
private:
	void *__IBackendAuthToken;	// Rest::Backend::Metatypes::IBackendAuthToken 
	void *__IBackendUserName;	// Rest::Backend::Metatypes::IBackendUserName 
	void *__IBackendCreatedAt;	// Rest::Backend::Metatypes::IBackendCreatedAt 
	void *__IBackendObjectID;	// Rest::Backend::Metatypes::IBackendObjectID 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3C4FF6D8-11CA-48D8-8967-B3F1FC06C3EA}
	operator Rest::Backend::Metatypes::_di_IBackendAuthToken()
	{
		Rest::Backend::Metatypes::_di_IBackendAuthToken intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendAuthToken*(void) { return (Rest::Backend::Metatypes::IBackendAuthToken*)&__IBackendAuthToken; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B7022538-2C7D-4F93-A1C8-A7A96545E4BF}
	operator Rest::Backend::Metatypes::_di_IBackendUserName()
	{
		Rest::Backend::Metatypes::_di_IBackendUserName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendUserName*(void) { return (Rest::Backend::Metatypes::IBackendUserName*)&__IBackendUserName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C3204A92-434F-4008-B356-E41896BC22CA}
	operator Rest::Backend::Metatypes::_di_IBackendCreatedAt()
	{
		Rest::Backend::Metatypes::_di_IBackendCreatedAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendCreatedAt*(void) { return (Rest::Backend::Metatypes::IBackendCreatedAt*)&__IBackendCreatedAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CD893599-279D-4000-B7E2-F94B944D6C63}
	operator Rest::Backend::Metatypes::_di_IBackendObjectID()
	{
		Rest::Backend::Metatypes::_di_IBackendObjectID intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendObjectID*(void) { return (Rest::Backend::Metatypes::IBackendObjectID*)&__IBackendObjectID; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendAuthToken; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaUpdatedUserAt : public TMetaObject
{
	typedef TMetaObject inherited;
	
private:
	Rest::Backend::Kinveyapi::TKinveyApi::TUpdatedAt FUpdatedAt;
	
protected:
	HIDESBASE System::TDateTime __fastcall GetUpdatedAt();
	
public:
	__fastcall TMetaUpdatedUserAt(const Rest::Backend::Kinveyapi::TKinveyApi::TUpdatedAt &AUpdatedAt);
	__property Rest::Backend::Kinveyapi::TKinveyApi::TUpdatedAt UpdatedAt = {read=FUpdatedAt};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaUpdatedUserAt() { }
	
private:
	void *__IBackendUpdatedAt;	// Rest::Backend::Metatypes::IBackendUpdatedAt 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16630E95-EE80-4328-8323-6F7FF67C0141}
	operator Rest::Backend::Metatypes::_di_IBackendUpdatedAt()
	{
		Rest::Backend::Metatypes::_di_IBackendUpdatedAt intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendUpdatedAt*(void) { return (Rest::Backend::Metatypes::IBackendUpdatedAt*)&__IBackendUpdatedAt; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendUpdatedAt; }
	#endif
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TKinveyMetaFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static Rest::Backend::Metatypes::TBackendClassValue __fastcall CreateMetaClass(const System::UnicodeString AClassName);
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaClassObject(const System::UnicodeString AClassName, const System::UnicodeString AObjectID)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaClassObject(const Rest::Backend::Kinveyapi::TKinveyApi::TObjectID &AObjectID)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaCreatedObject(const Rest::Backend::Kinveyapi::TKinveyApi::TObjectID &AObjectID);
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaFoundObject(const Rest::Backend::Kinveyapi::TKinveyApi::TObjectID &AObjectID);
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUpdatedObject(const Rest::Backend::Kinveyapi::TKinveyApi::TObjectID &AObjectID)/* overload */;
	static Rest::Backend::Metatypes::TBackendClassValue __fastcall CreateMetaDataType(const System::UnicodeString ADataType, const System::UnicodeString AClassName);
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUserObject(const System::UnicodeString AObjectID)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUserObject(const Rest::Backend::Kinveyapi::TKinveyApi::TUser &AUser)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaFoundUser(const Rest::Backend::Kinveyapi::TKinveyApi::TUser &AUser);
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUpdatedUser(const Rest::Backend::Kinveyapi::TKinveyApi::TUpdatedAt &AUpdatedAt)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaSignupUser(const Rest::Backend::Kinveyapi::TKinveyApi::TLogin &ALogin)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaLoginUser(const Rest::Backend::Kinveyapi::TKinveyApi::TLogin &ALogin)/* overload */;
	__classmethod Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUploadedFile(const Rest::Backend::Kinveyapi::TKinveyApi::TFile &AFile);
	__classmethod Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaFileObject(const System::UnicodeString AFileID);
public:
	/* TObject.Create */ inline __fastcall TKinveyMetaFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TKinveyMetaFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Kinveymetatypes */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_KINVEYMETATYPES)
using namespace Rest::Backend::Kinveymetatypes;
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
#endif	// Rest_Backend_KinveymetatypesHPP
