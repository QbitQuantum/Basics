// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.EMSMetaTypes.pas' rev: 34.00 (iOS)

#ifndef Rest_Backend_EmsmetatypesHPP
#define Rest_Backend_EmsmetatypesHPP

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
#include <REST.Backend.EMSApi.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Emsmetatypes
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMetaFactory;
class DELPHICLASS TMetaClass;
class DELPHICLASS TMetaClassName;
class DELPHICLASS TMetaDataType;
class DELPHICLASS TMetaUser;
class DELPHICLASS TMetaGroup;
class DELPHICLASS TMetaInstallation;
class DELPHICLASS TMetaLogin;
class DELPHICLASS TMetaModule;
class DELPHICLASS TMetaModuleResource;
class DELPHICLASS TMetaUpdatedUser;
class DELPHICLASS TMetaFoundUser;
class DELPHICLASS TMetaFoundGroup;
class DELPHICLASS TMetaFoundInstallation;
class DELPHICLASS TMetaInstallationID;
class DELPHICLASS TMetaLoginUser;
class DELPHICLASS TMetaSignupUser;
class DELPHICLASS TMetaFoundModule;
class DELPHICLASS TMetaFoundModuleResource;
class DELPHICLASS TMetaUpdatedAt;
class DELPHICLASS TEMSMetaFactory;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TMetaFactory : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUserObject(const System::UnicodeString AObjectID);
	Rest::Backend::Metatypes::TBackendClassValue __fastcall CreateMetaDataType(const System::UnicodeString ADataType, const System::UnicodeString ABackendClassName);
	Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaGroupObject(const System::UnicodeString AGroupID);
public:
	/* TObject.Create */ inline __fastcall TMetaFactory() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaFactory() { }
	
private:
	void *__IBackendMetaDataTypeFactory;	// Rest::Backend::Metatypes::IBackendMetaDataTypeFactory 
	void *__IBackendMetaGroupFactory;	// Rest::Backend::Metatypes::IBackendMetaGroupFactory 
	void *__IBackendMetaUserFactory;	// Rest::Backend::Metatypes::IBackendMetaUserFactory 
	
public:
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
	// {3CB88315-4399-4307-A5E5-CF60C919FF2D}
	operator Rest::Backend::Metatypes::_di_IBackendMetaGroupFactory()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaGroupFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaGroupFactory*(void) { return (Rest::Backend::Metatypes::IBackendMetaGroupFactory*)&__IBackendMetaGroupFactory; }
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
	// {B58EC9B1-060C-4B44-82E9-82F576AB3793}
	operator Rest::Backend::Metatypes::_di_IBackendMetaFactory()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaFactory*(void) { return (Rest::Backend::Metatypes::IBackendMetaFactory*)&__IBackendMetaDataTypeFactory; }
	#endif
	
};


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


class PASCALIMPLEMENTATION TMetaUser : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Emsapi::TEMSClientAPI::TUser FUser;
	
protected:
	System::UnicodeString __fastcall GetObjectID();
	System::TDateTime __fastcall GetCreatedAt();
	System::TDateTime __fastcall GetUpdatedAt();
	System::UnicodeString __fastcall GetUserName();
	
public:
	__fastcall TMetaUser(const Rest::Backend::Emsapi::TEMSClientAPI::TUser &AUser);
	__property Rest::Backend::Emsapi::TEMSClientAPI::TUser User = {read=FUser};
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


class PASCALIMPLEMENTATION TMetaGroup : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Emsapi::TEMSClientAPI::TGroup FGroup;
	
protected:
	System::UnicodeString __fastcall GetGroupName();
	System::TDateTime __fastcall GetCreatedAt();
	System::TDateTime __fastcall GetUpdatedAt();
	
public:
	__fastcall TMetaGroup(const Rest::Backend::Emsapi::TEMSClientAPI::TGroup &AGroup);
	__property Rest::Backend::Emsapi::TEMSClientAPI::TGroup Group = {read=FGroup};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaGroup() { }
	
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


class PASCALIMPLEMENTATION TMetaInstallation : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Emsapi::TEMSClientAPI::TInstallation FInstallation;
	
protected:
	System::UnicodeString __fastcall GetObjectID();
	System::TDateTime __fastcall GetCreatedAt();
	System::TDateTime __fastcall GetUpdatedAt();
	
public:
	__fastcall TMetaInstallation(const Rest::Backend::Emsapi::TEMSClientAPI::TInstallation &AInstallation);
	__property Rest::Backend::Emsapi::TEMSClientAPI::TInstallation Installation = {read=FInstallation};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaInstallation() { }
	
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
	Rest::Backend::Emsapi::TEMSClientAPI::TLogin FLogin;
	
protected:
	System::UnicodeString __fastcall GetAuthTOken();
	
public:
	__fastcall TMetaLogin(const Rest::Backend::Emsapi::TEMSClientAPI::TLogin &ALogin);
	__property Rest::Backend::Emsapi::TEMSClientAPI::TLogin Login = {read=FLogin};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaLogin() { }
	
};


class PASCALIMPLEMENTATION TMetaModule : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Emsapi::TEMSClientAPI::TModule FModule;
	
protected:
	System::UnicodeString __fastcall GetObjectID();
	System::UnicodeString __fastcall GetModuleName();
	System::TDateTime __fastcall GetCreatedAt();
	System::TDateTime __fastcall GetUpdatedAt();
	
public:
	__fastcall TMetaModule(const Rest::Backend::Emsapi::TEMSClientAPI::TModule &AModule);
	__property Rest::Backend::Emsapi::TEMSClientAPI::TModule Module = {read=FModule};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaModule() { }
	
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


class PASCALIMPLEMENTATION TMetaModuleResource : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Emsapi::TEMSClientAPI::TModuleResource FModuleResource;
	
protected:
	System::UnicodeString __fastcall GetObjectID();
	System::UnicodeString __fastcall GetModuleName();
	System::UnicodeString __fastcall GetResourceName();
	System::TDateTime __fastcall GetCreatedAt();
	System::TDateTime __fastcall GetUpdatedAt();
	
public:
	__fastcall TMetaModuleResource(const Rest::Backend::Emsapi::TEMSClientAPI::TModuleResource &AModuleResource);
	__property Rest::Backend::Emsapi::TEMSClientAPI::TModuleResource ModuleResource = {read=FModuleResource};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaModuleResource() { }
	
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


class PASCALIMPLEMENTATION TMetaUpdatedUser : public TMetaUser
{
	typedef TMetaUser inherited;
	
public:
	/* TMetaUser.Create */ inline __fastcall TMetaUpdatedUser(const Rest::Backend::Emsapi::TEMSClientAPI::TUser &AUser) : TMetaUser(AUser) { }
	
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
	/* TMetaUser.Create */ inline __fastcall TMetaFoundUser(const Rest::Backend::Emsapi::TEMSClientAPI::TUser &AUser) : TMetaUser(AUser) { }
	
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


class PASCALIMPLEMENTATION TMetaFoundGroup : public TMetaGroup
{
	typedef TMetaGroup inherited;
	
public:
	/* TMetaGroup.Create */ inline __fastcall TMetaFoundGroup(const Rest::Backend::Emsapi::TEMSClientAPI::TGroup &AGroup) : TMetaGroup(AGroup) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaFoundGroup() { }
	
private:
	void *__IBackendGroupName;	// Rest::Backend::Metatypes::IBackendGroupName 
	void *__IBackendUpdatedAt;	// Rest::Backend::Metatypes::IBackendUpdatedAt 
	void *__IBackendCreatedAt;	// Rest::Backend::Metatypes::IBackendCreatedAt 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BEA0754A-0D59-4D62-96A4-3175A3E8E1EB}
	operator Rest::Backend::Metatypes::_di_IBackendGroupName()
	{
		Rest::Backend::Metatypes::_di_IBackendGroupName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendGroupName*(void) { return (Rest::Backend::Metatypes::IBackendGroupName*)&__IBackendGroupName; }
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
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendGroupName; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaFoundInstallation : public TMetaInstallation
{
	typedef TMetaInstallation inherited;
	
public:
	/* TMetaInstallation.Create */ inline __fastcall TMetaFoundInstallation(const Rest::Backend::Emsapi::TEMSClientAPI::TInstallation &AInstallation) : TMetaInstallation(AInstallation) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaFoundInstallation() { }
	
private:
	void *__IBackendObjectID;	// Rest::Backend::Metatypes::IBackendObjectID 
	void *__IBackendUpdatedAt;	// Rest::Backend::Metatypes::IBackendUpdatedAt 
	void *__IBackendCreatedAt;	// Rest::Backend::Metatypes::IBackendCreatedAt 
	
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


class PASCALIMPLEMENTATION TMetaInstallationID : public TMetaInstallation
{
	typedef TMetaInstallation inherited;
	
public:
	/* TMetaInstallation.Create */ inline __fastcall TMetaInstallationID(const Rest::Backend::Emsapi::TEMSClientAPI::TInstallation &AInstallation) : TMetaInstallation(AInstallation) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaInstallationID() { }
	
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


class PASCALIMPLEMENTATION TMetaLoginUser : public TMetaLogin
{
	typedef TMetaLogin inherited;
	
public:
	/* TMetaLogin.Create */ inline __fastcall TMetaLoginUser(const Rest::Backend::Emsapi::TEMSClientAPI::TLogin &ALogin) : TMetaLogin(ALogin) { }
	
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
	/* TMetaLogin.Create */ inline __fastcall TMetaSignupUser(const Rest::Backend::Emsapi::TEMSClientAPI::TLogin &ALogin) : TMetaLogin(ALogin) { }
	
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


class PASCALIMPLEMENTATION TMetaFoundModule : public TMetaModule
{
	typedef TMetaModule inherited;
	
public:
	/* TMetaModule.Create */ inline __fastcall TMetaFoundModule(const Rest::Backend::Emsapi::TEMSClientAPI::TModule &AModule) : TMetaModule(AModule) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaFoundModule() { }
	
private:
	void *__IBackendModuleName;	// Rest::Backend::Metatypes::IBackendModuleName 
	void *__IBackendObjectID;	// Rest::Backend::Metatypes::IBackendObjectID 
	void *__IBackendUpdatedAt;	// Rest::Backend::Metatypes::IBackendUpdatedAt 
	void *__IBackendCreatedAt;	// Rest::Backend::Metatypes::IBackendCreatedAt 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BEA0754A-0D59-4D62-96A4-3175A3E8E1EB}
	operator Rest::Backend::Metatypes::_di_IBackendModuleName()
	{
		Rest::Backend::Metatypes::_di_IBackendModuleName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendModuleName*(void) { return (Rest::Backend::Metatypes::IBackendModuleName*)&__IBackendModuleName; }
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
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendModuleName; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaFoundModuleResource : public TMetaModuleResource
{
	typedef TMetaModuleResource inherited;
	
public:
	/* TMetaModuleResource.Create */ inline __fastcall TMetaFoundModuleResource(const Rest::Backend::Emsapi::TEMSClientAPI::TModuleResource &AModuleResource) : TMetaModuleResource(AModuleResource) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaFoundModuleResource() { }
	
private:
	void *__IBackendModuleResourceName;	// Rest::Backend::Metatypes::IBackendModuleResourceName 
	void *__IBackendModuleName;	// Rest::Backend::Metatypes::IBackendModuleName 
	void *__IBackendObjectID;	// Rest::Backend::Metatypes::IBackendObjectID 
	void *__IBackendUpdatedAt;	// Rest::Backend::Metatypes::IBackendUpdatedAt 
	void *__IBackendCreatedAt;	// Rest::Backend::Metatypes::IBackendCreatedAt 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BEA0754A-0D59-4D62-96A4-3175A3E8E1EB}
	operator Rest::Backend::Metatypes::_di_IBackendModuleResourceName()
	{
		Rest::Backend::Metatypes::_di_IBackendModuleResourceName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendModuleResourceName*(void) { return (Rest::Backend::Metatypes::IBackendModuleResourceName*)&__IBackendModuleResourceName; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BEA0754A-0D59-4D62-96A4-3175A3E8E1EB}
	operator Rest::Backend::Metatypes::_di_IBackendModuleName()
	{
		Rest::Backend::Metatypes::_di_IBackendModuleName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendModuleName*(void) { return (Rest::Backend::Metatypes::IBackendModuleName*)&__IBackendModuleName; }
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
	// {95F29709-C995-4E69-A16E-3E9FA6D81ED6}
	operator Rest::Backend::Metatypes::_di_IBackendMetaObject()
	{
		Rest::Backend::Metatypes::_di_IBackendMetaObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Metatypes::IBackendMetaObject*(void) { return (Rest::Backend::Metatypes::IBackendMetaObject*)&__IBackendModuleResourceName; }
	#endif
	
};


class PASCALIMPLEMENTATION TMetaUpdatedAt : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Rest::Backend::Emsapi::TEMSClientAPI::TUpdatedAt FUpdatedAt;
	
protected:
	System::TDateTime __fastcall GetUpdatedAt();
	
public:
	__fastcall TMetaUpdatedAt(const Rest::Backend::Emsapi::TEMSClientAPI::TUpdatedAt &AUpdatedAt);
	__property Rest::Backend::Emsapi::TEMSClientAPI::TUpdatedAt UpdatedAt = {read=FUpdatedAt};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMetaUpdatedAt() { }
	
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


typedef TMetaUpdatedAt TMetaUpdatedUserAt;

typedef TMetaUpdatedAt TMetaUpdatedGroupAt;

class PASCALIMPLEMENTATION TEMSMetaFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static Rest::Backend::Metatypes::TBackendClassValue __fastcall CreateMetaClass(const System::UnicodeString AClassName);
	static Rest::Backend::Metatypes::TBackendClassValue __fastcall CreateMetaDataType(const System::UnicodeString ADataType, const System::UnicodeString AClassName);
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUserObject(const System::UnicodeString AObjectID)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaGroupObject(const System::UnicodeString AGroupName)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUserObject(const Rest::Backend::Emsapi::TEMSClientAPI::TUser &AUser)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaGroupObject(const Rest::Backend::Emsapi::TEMSClientAPI::TGroup &AGroup)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaFoundUser(const Rest::Backend::Emsapi::TEMSClientAPI::TUser &AUser);
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaFoundGroup(const Rest::Backend::Emsapi::TEMSClientAPI::TGroup &AGroup);
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaFoundInstallation(const Rest::Backend::Emsapi::TEMSClientAPI::TInstallation &AInstallation);
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUpdatedUser(const Rest::Backend::Emsapi::TEMSClientAPI::TUpdatedAt &AUpdatedAt)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaUpdatedGroup(const Rest::Backend::Emsapi::TEMSClientAPI::TUpdatedAt &AUpdatedAt)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaSignupUser(const Rest::Backend::Emsapi::TEMSClientAPI::TLogin &ALogin)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaLoginUser(const Rest::Backend::Emsapi::TEMSClientAPI::TLogin &ALogin)/* overload */;
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaFoundModule(const Rest::Backend::Emsapi::TEMSClientAPI::TModule &AModule);
	static Rest::Backend::Metatypes::TBackendEntityValue __fastcall CreateMetaFoundModuleResource(const Rest::Backend::Emsapi::TEMSClientAPI::TModuleResource &AModuleResource);
public:
	/* TObject.Create */ inline __fastcall TEMSMetaFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSMetaFactory() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Emsmetatypes */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_EMSMETATYPES)
using namespace Rest::Backend::Emsmetatypes;
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
#endif	// Rest_Backend_EmsmetatypesHPP
