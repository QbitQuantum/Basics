// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.WSILIntf.pas' rev: 34.00 (Windows)

#ifndef Soap_WsilintfHPP
#define Soap_WsilintfHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Wsilintf
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IXMLItemWithAbstracts;
typedef System::DelphiInterface<IXMLItemWithAbstracts> _di_IXMLItemWithAbstracts;
__interface DELPHIINTERFACE IXMLServiceType;
typedef System::DelphiInterface<IXMLServiceType> _di_IXMLServiceType;
__interface DELPHIINTERFACE IXMLServiceTypeList;
typedef System::DelphiInterface<IXMLServiceTypeList> _di_IXMLServiceTypeList;
__interface DELPHIINTERFACE IXMLNameType;
typedef System::DelphiInterface<IXMLNameType> _di_IXMLNameType;
__interface DELPHIINTERFACE IXMLNameTypeList;
typedef System::DelphiInterface<IXMLNameTypeList> _di_IXMLNameTypeList;
__interface DELPHIINTERFACE IXMLReferenceType;
typedef System::DelphiInterface<IXMLReferenceType> _di_IXMLReferenceType;
__interface DELPHIINTERFACE IXMLLinkType;
typedef System::DelphiInterface<IXMLLinkType> _di_IXMLLinkType;
__interface DELPHIINTERFACE IXMLLinkTypeList;
typedef System::DelphiInterface<IXMLLinkTypeList> _di_IXMLLinkTypeList;
__interface DELPHIINTERFACE IXMLTypeOfAbstract;
typedef System::DelphiInterface<IXMLTypeOfAbstract> _di_IXMLTypeOfAbstract;
__interface DELPHIINTERFACE IXMLInspection;
typedef System::DelphiInterface<IXMLInspection> _di_IXMLInspection;
__interface DELPHIINTERFACE IXMLDescriptionType;
typedef System::DelphiInterface<IXMLDescriptionType> _di_IXMLDescriptionType;
__interface DELPHIINTERFACE IXMLDescriptionTypeList;
typedef System::DelphiInterface<IXMLDescriptionTypeList> _di_IXMLDescriptionTypeList;
class DELPHICLASS TXMLItemWithAbstracts;
class DELPHICLASS TXMLServiceType;
class DELPHICLASS TXMLServiceTypeList;
class DELPHICLASS TXMLNameType;
class DELPHICLASS TXMLNameTypeList;
class DELPHICLASS TXMLReferenceType;
class DELPHICLASS TXMLLinkType;
class DELPHICLASS TXMLLinkTypeList;
class DELPHICLASS TXMLTypeOfAbstract;
class DELPHICLASS TXMLInspection;
class DELPHICLASS TXMLDescriptionType;
class DELPHICLASS TXMLDescriptionTypeList;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{33E53FE0-14E5-4D18-A0AE-19FEE8CF6403}") IXMLItemWithAbstracts  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IXMLTypeOfAbstract operator[](int Index) { return this->Abstract[Index]; }
	virtual _di_IXMLTypeOfAbstract __fastcall Get_Abstract(int Index) = 0 ;
	virtual _di_IXMLTypeOfAbstract __fastcall Add() = 0 ;
	virtual _di_IXMLTypeOfAbstract __fastcall Insert(const int Index) = 0 ;
	__property _di_IXMLTypeOfAbstract Abstract[int Index] = {read=Get_Abstract/*, default*/};
};

__interface  INTERFACE_UUID("{EC832C01-CF74-4207-9884-4027134D80F2}") IXMLServiceType  : public IXMLItemWithAbstracts 
{
	virtual _di_IXMLNameTypeList __fastcall Get_Name() = 0 ;
	virtual _di_IXMLDescriptionTypeList __fastcall Get_Description() = 0 ;
	__property _di_IXMLNameTypeList Name = {read=Get_Name};
	__property _di_IXMLDescriptionTypeList Description = {read=Get_Description};
};

__interface  INTERFACE_UUID("{3E5EC7EF-3355-4D9A-8987-7067A9CAFBC7}") IXMLServiceTypeList  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IXMLServiceType operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLServiceType __fastcall Add() = 0 ;
	virtual _di_IXMLServiceType __fastcall Insert(const int Index) = 0 ;
	virtual _di_IXMLServiceType __fastcall Get_Item(int Index) = 0 ;
	__property _di_IXMLServiceType Items[int Index] = {read=Get_Item/*, default*/};
};

__interface  INTERFACE_UUID("{60F42F94-6754-40EB-8889-00D7BD607240}") IXMLNameType  : public Xml::Xmlintf::IXMLNode 
{
	virtual System::WideString __fastcall Get_Lang() = 0 ;
	virtual void __fastcall Set_Lang(System::WideString Value) = 0 ;
	__property System::WideString Lang = {read=Get_Lang, write=Set_Lang};
};

__interface  INTERFACE_UUID("{5DAA8A82-A27D-49DF-A154-52351CBB8A7F}") IXMLNameTypeList  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IXMLNameType operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLNameType __fastcall Add() = 0 ;
	virtual _di_IXMLNameType __fastcall Insert(const int Index) = 0 ;
	virtual _di_IXMLNameType __fastcall Get_Item(int Index) = 0 ;
	__property _di_IXMLNameType Items[int Index] = {read=Get_Item/*, default*/};
};

__interface  INTERFACE_UUID("{94130F0C-0F07-4FDE-9A59-C5079D7952A0}") IXMLReferenceType  : public IXMLItemWithAbstracts 
{
	virtual System::WideString __fastcall Get_ReferencedNamespace() = 0 ;
	virtual System::WideString __fastcall Get_Location() = 0 ;
	virtual void __fastcall Set_ReferencedNamespace(System::WideString Value) = 0 ;
	virtual void __fastcall Set_Location(System::WideString Value) = 0 ;
	__property System::WideString ReferencedNamespace = {read=Get_ReferencedNamespace, write=Set_ReferencedNamespace};
	__property System::WideString Location = {read=Get_Location, write=Set_Location};
};

__interface  INTERFACE_UUID("{84A1F2BC-E4CA-4187-8B62-DEBB01F8BE8F}") IXMLLinkType  : public IXMLReferenceType 
{
	
};

__interface  INTERFACE_UUID("{64415871-3494-4B46-A34C-A47BF53AABEE}") IXMLLinkTypeList  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IXMLLinkType operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLLinkType __fastcall Add() = 0 ;
	virtual _di_IXMLLinkType __fastcall Insert(const int Index) = 0 ;
	virtual _di_IXMLLinkType __fastcall Get_Item(int Index) = 0 ;
	__property _di_IXMLLinkType Items[int Index] = {read=Get_Item/*, default*/};
};

__interface  INTERFACE_UUID("{49BD4FF9-04D5-41C4-B08C-66A17F7DCB18}") IXMLTypeOfAbstract  : public Xml::Xmlintf::IXMLNode 
{
	virtual System::WideString __fastcall Get_Lang() = 0 ;
	virtual void __fastcall Set_Lang(System::WideString Value) = 0 ;
	__property System::WideString Lang = {read=Get_Lang, write=Set_Lang};
};

__interface  INTERFACE_UUID("{9188C201-D00D-44B9-80A6-6C55D820879F}") IXMLInspection  : public IXMLItemWithAbstracts 
{
	virtual _di_IXMLServiceTypeList __fastcall Get_Service() = 0 ;
	virtual _di_IXMLLinkTypeList __fastcall Get_Link() = 0 ;
	__property _di_IXMLServiceTypeList Service = {read=Get_Service};
	__property _di_IXMLLinkTypeList Link = {read=Get_Link};
};

__interface  INTERFACE_UUID("{620E7125-E033-4B8B-B5AE-A18F26864411}") IXMLDescriptionType  : public IXMLReferenceType 
{
	
};

__interface  INTERFACE_UUID("{9A62AF8B-F404-4655-8175-1E899C78F668}") IXMLDescriptionTypeList  : public Xml::Xmlintf::IXMLNodeCollection 
{
	
public:
	_di_IXMLDescriptionType operator[](int Index) { return this->Items[Index]; }
	virtual _di_IXMLDescriptionType __fastcall Add() = 0 ;
	virtual _di_IXMLDescriptionType __fastcall Insert(const int Index) = 0 ;
	virtual _di_IXMLDescriptionType __fastcall Get_Item(int Index) = 0 ;
	__property _di_IXMLDescriptionType Items[int Index] = {read=Get_Item/*, default*/};
};

class PASCALIMPLEMENTATION TXMLItemWithAbstracts : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IXMLTypeOfAbstract __fastcall Get_Abstract(int Index);
	_di_IXMLTypeOfAbstract __fastcall Add();
	_di_IXMLTypeOfAbstract __fastcall Insert(const int Index);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLItemWithAbstracts(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLItemWithAbstracts(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLItemWithAbstracts() { }
	
private:
	void *__IXMLItemWithAbstracts;	// IXMLItemWithAbstracts 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {33E53FE0-14E5-4D18-A0AE-19FEE8CF6403}
	operator _di_IXMLItemWithAbstracts()
	{
		_di_IXMLItemWithAbstracts intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLItemWithAbstracts*(void) { return (IXMLItemWithAbstracts*)&__IXMLItemWithAbstracts; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLServiceType : public TXMLItemWithAbstracts
{
	typedef TXMLItemWithAbstracts inherited;
	
private:
	_di_IXMLNameTypeList FName;
	_di_IXMLDescriptionTypeList FDescription;
	
protected:
	_di_IXMLNameTypeList __fastcall Get_Name();
	_di_IXMLDescriptionTypeList __fastcall Get_Description();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLServiceType(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLItemWithAbstracts(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLServiceType(Xml::Xmldoc::TXMLNode* HostNode) : TXMLItemWithAbstracts(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLServiceType() { }
	
private:
	void *__IXMLServiceType;	// IXMLServiceType 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EC832C01-CF74-4207-9884-4027134D80F2}
	operator _di_IXMLServiceType()
	{
		_di_IXMLServiceType intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLServiceType*(void) { return (IXMLServiceType*)&__IXMLServiceType; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLServiceTypeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IXMLServiceType __fastcall Add();
	_di_IXMLServiceType __fastcall Insert(const int Index);
	_di_IXMLServiceType __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLServiceTypeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLServiceTypeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLServiceTypeList() { }
	
private:
	void *__IXMLServiceTypeList;	// IXMLServiceTypeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E5EC7EF-3355-4D9A-8987-7067A9CAFBC7}
	operator _di_IXMLServiceTypeList()
	{
		_di_IXMLServiceTypeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLServiceTypeList*(void) { return (IXMLServiceTypeList*)&__IXMLServiceTypeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLNameType : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::WideString __fastcall Get_Lang();
	void __fastcall Set_Lang(System::WideString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLNameType(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLNameType(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLNameType() { }
	
private:
	void *__IXMLNameType;	// IXMLNameType 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {60F42F94-6754-40EB-8889-00D7BD607240}
	operator _di_IXMLNameType()
	{
		_di_IXMLNameType intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLNameType*(void) { return (IXMLNameType*)&__IXMLNameType; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLNameTypeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IXMLNameType __fastcall Add();
	_di_IXMLNameType __fastcall Insert(const int Index);
	_di_IXMLNameType __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLNameTypeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLNameTypeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLNameTypeList() { }
	
private:
	void *__IXMLNameTypeList;	// IXMLNameTypeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5DAA8A82-A27D-49DF-A154-52351CBB8A7F}
	operator _di_IXMLNameTypeList()
	{
		_di_IXMLNameTypeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLNameTypeList*(void) { return (IXMLNameTypeList*)&__IXMLNameTypeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLReferenceType : public TXMLItemWithAbstracts
{
	typedef TXMLItemWithAbstracts inherited;
	
protected:
	System::WideString __fastcall Get_ReferencedNamespace();
	System::WideString __fastcall Get_Location();
	void __fastcall Set_ReferencedNamespace(System::WideString Value);
	void __fastcall Set_Location(System::WideString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLReferenceType(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLItemWithAbstracts(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLReferenceType(Xml::Xmldoc::TXMLNode* HostNode) : TXMLItemWithAbstracts(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLReferenceType() { }
	
private:
	void *__IXMLReferenceType;	// IXMLReferenceType 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {94130F0C-0F07-4FDE-9A59-C5079D7952A0}
	operator _di_IXMLReferenceType()
	{
		_di_IXMLReferenceType intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLReferenceType*(void) { return (IXMLReferenceType*)&__IXMLReferenceType; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLinkType : public TXMLReferenceType
{
	typedef TXMLReferenceType inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLinkType(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLReferenceType(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLinkType(Xml::Xmldoc::TXMLNode* HostNode) : TXMLReferenceType(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLinkType() { }
	
private:
	void *__IXMLLinkType;	// IXMLLinkType 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {84A1F2BC-E4CA-4187-8B62-DEBB01F8BE8F}
	operator _di_IXMLLinkType()
	{
		_di_IXMLLinkType intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLLinkType*(void) { return (IXMLLinkType*)&__IXMLLinkType; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLinkTypeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	_di_IXMLLinkType __fastcall Add();
	_di_IXMLLinkType __fastcall Insert(const int Index);
	_di_IXMLLinkType __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLinkTypeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLinkTypeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLinkTypeList() { }
	
private:
	void *__IXMLLinkTypeList;	// IXMLLinkTypeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {64415871-3494-4B46-A34C-A47BF53AABEE}
	operator _di_IXMLLinkTypeList()
	{
		_di_IXMLLinkTypeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLLinkTypeList*(void) { return (IXMLLinkTypeList*)&__IXMLLinkTypeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTypeOfAbstract : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::WideString __fastcall Get_Lang();
	void __fastcall Set_Lang(System::WideString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTypeOfAbstract(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTypeOfAbstract(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTypeOfAbstract() { }
	
private:
	void *__IXMLTypeOfAbstract;	// IXMLTypeOfAbstract 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {49BD4FF9-04D5-41C4-B08C-66A17F7DCB18}
	operator _di_IXMLTypeOfAbstract()
	{
		_di_IXMLTypeOfAbstract intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLTypeOfAbstract*(void) { return (IXMLTypeOfAbstract*)&__IXMLTypeOfAbstract; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLInspection : public TXMLItemWithAbstracts
{
	typedef TXMLItemWithAbstracts inherited;
	
private:
	_di_IXMLServiceTypeList FService;
	_di_IXMLLinkTypeList FLink;
	
protected:
	_di_IXMLServiceTypeList __fastcall Get_Service();
	_di_IXMLLinkTypeList __fastcall Get_Link();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLInspection(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLItemWithAbstracts(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLInspection(Xml::Xmldoc::TXMLNode* HostNode) : TXMLItemWithAbstracts(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLInspection() { }
	
private:
	void *__IXMLInspection;	// IXMLInspection 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9188C201-D00D-44B9-80A6-6C55D820879F}
	operator _di_IXMLInspection()
	{
		_di_IXMLInspection intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLInspection*(void) { return (IXMLInspection*)&__IXMLInspection; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLDescriptionType : public TXMLReferenceType
{
	typedef TXMLReferenceType inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLDescriptionType(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLReferenceType(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLDescriptionType(Xml::Xmldoc::TXMLNode* HostNode) : TXMLReferenceType(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLDescriptionType() { }
	
private:
	void *__IXMLDescriptionType;	// IXMLDescriptionType 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {620E7125-E033-4B8B-B5AE-A18F26864411}
	operator _di_IXMLDescriptionType()
	{
		_di_IXMLDescriptionType intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLDescriptionType*(void) { return (IXMLDescriptionType*)&__IXMLDescriptionType; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLDescriptionTypeList : public TXMLReferenceType
{
	typedef TXMLReferenceType inherited;
	
protected:
	HIDESBASE _di_IXMLDescriptionType __fastcall Add();
	HIDESBASE _di_IXMLDescriptionType __fastcall Insert(const int Index);
	_di_IXMLDescriptionType __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLDescriptionTypeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLReferenceType(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLDescriptionTypeList(Xml::Xmldoc::TXMLNode* HostNode) : TXMLReferenceType(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLDescriptionTypeList() { }
	
private:
	void *__IXMLDescriptionTypeList;	// IXMLDescriptionTypeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9A62AF8B-F404-4655-8175-1E899C78F668}
	operator _di_IXMLDescriptionTypeList()
	{
		_di_IXMLDescriptionTypeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IXMLDescriptionTypeList*(void) { return (IXMLDescriptionTypeList*)&__IXMLDescriptionTypeList; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
#define SInspectionNS L"http://schemas.xmlsoap.org/ws/2001/10/inspection/"
extern DELPHI_PACKAGE _di_IXMLInspection __fastcall Getinspection(Xml::Xmlintf::_di_IXMLDocument Doc);
extern DELPHI_PACKAGE _di_IXMLInspection __fastcall Loadinspection(const System::WideString FileName);
extern DELPHI_PACKAGE _di_IXMLInspection __fastcall Newinspection(void);
}	/* namespace Wsilintf */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_WSILINTF)
using namespace Soap::Wsilintf;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_WsilintfHPP
