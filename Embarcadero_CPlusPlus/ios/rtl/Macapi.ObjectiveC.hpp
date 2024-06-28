// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.ObjectiveC.pas' rev: 34.00 (iOS)

#ifndef Macapi_ObjectivecHPP
#define Macapi_ObjectivecHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Rtti.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>
#include <System.RTLConsts.hpp>
#include <Macapi.OCMarshal.hpp>
#include <Macapi.ObjCRuntime.hpp>
#include <Macapi.Consts.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Macapi
{
namespace Objectivec
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS MethodNameAttribute;
__interface DELPHIINTERFACE IObjectiveC;
typedef System::DelphiInterface<IObjectiveC> _di_IObjectiveC;
__interface DELPHIINTERFACE IObjectiveCClass;
typedef System::DelphiInterface<IObjectiveCClass> _di_IObjectiveCClass;
__interface DELPHIINTERFACE IObjectiveCInstance;
typedef System::DelphiInterface<IObjectiveCInstance> _di_IObjectiveCInstance;
struct OCMethodInvokeData;
class DELPHICLASS TOCVTable;
class DELPHICLASS EObjectiveC;
class DELPHICLASS EObjectiveCFatal;
__interface DELPHIINTERFACE ILocalObject;
typedef System::DelphiInterface<ILocalObject> _di_ILocalObject;
class DELPHICLASS TOCValidate;
class DELPHICLASS TOCImport;
template<typename C, typename T> class DELPHICLASS TOCGenericImport__2;
class DELPHICLASS TOCInterfacedObject;
class DELPHICLASS TOCLocal;
class DELPHICLASS TVTableCache;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION MethodNameAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	System::UnicodeString FMethodName;
	
public:
	__property System::UnicodeString Name = {read=FMethodName};
	__fastcall MethodNameAttribute(const System::UnicodeString Name);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~MethodNameAttribute() { }
	
};


__interface  INTERFACE_UUID("{3E7B0A40-F6AB-4FF5-9BE0-92DCB2909899}") IObjectiveC  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{ADD1B823-793E-4E51-867B-A01CC83B7739}") IObjectiveCClass  : public IObjectiveC 
{
	virtual void * __cdecl alloc() = 0 ;
};

__interface  INTERFACE_UUID("{B72015CE-B78D-4718-87D2-B639AA153818}") IObjectiveCInstance  : public IObjectiveC 
{
	virtual void * __cdecl init() = 0 ;
};

enum DECLSPEC_DENUM TRetKind : unsigned char { rkNormal, rkFPRET, rkSRET, rkIRET };

struct DECLSPEC_DRECORD OCMethodInvokeData
{
public:
	Macapi::Ocmarshal::TMarshaler* Marshaler;
	TRetKind RetKind;
	int ParamSize;
	System::Typinfo::TTypeInfo *ObjectiveCType;
};


typedef OCMethodInvokeData *POCMethodInvokeData;

class PASCALIMPLEMENTATION TOCVTable : public System::Rtti::TRawVirtualClass::TVTable
{
	typedef System::Rtti::TRawVirtualClass::TVTable inherited;
	
private:
	System::TArray__1<OCMethodInvokeData> FMethodInfoData;
	System::TArray__1<GUID> FGuids;
	
protected:
	__property System::TArray__1<GUID> Guids = {read=FGuids};
	__fastcall TOCVTable(System::Typinfo::PTypeInfo P, bool IsSuperClass);
	
public:
	__fastcall virtual ~TOCVTable();
};


class PASCALIMPLEMENTATION EObjectiveC : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EObjectiveC(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EObjectiveC(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EObjectiveC(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EObjectiveC(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EObjectiveC(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EObjectiveC(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EObjectiveC(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EObjectiveC(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EObjectiveC(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EObjectiveC(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EObjectiveC(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EObjectiveC(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EObjectiveC() { }
	
};


class PASCALIMPLEMENTATION EObjectiveCFatal : public EObjectiveC
{
	typedef EObjectiveC inherited;
	
public:
	/* Exception.Create */ inline __fastcall EObjectiveCFatal(const System::UnicodeString Msg) : EObjectiveC(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EObjectiveCFatal(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EObjectiveC(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EObjectiveCFatal(NativeUInt Ident)/* overload */ : EObjectiveC(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EObjectiveCFatal(System::PResStringRec ResStringRec)/* overload */ : EObjectiveC(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EObjectiveCFatal(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EObjectiveC(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EObjectiveCFatal(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EObjectiveC(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EObjectiveCFatal(const System::UnicodeString Msg, int AHelpContext) : EObjectiveC(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EObjectiveCFatal(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EObjectiveC(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EObjectiveCFatal(NativeUInt Ident, int AHelpContext)/* overload */ : EObjectiveC(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EObjectiveCFatal(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EObjectiveC(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EObjectiveCFatal(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EObjectiveC(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EObjectiveCFatal(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EObjectiveC(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EObjectiveCFatal() { }
	
};


__interface  INTERFACE_UUID("{55351304-9562-4039-BF44-AA5792DB6C30}") ILocalObject  : public IObjectiveC 
{
	virtual void * __fastcall GetObjectID() = 0 ;
};

class PASCALIMPLEMENTATION TOCValidate : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static void __fastcall ValidateTypeHierarchy(System::Typinfo::PTypeInfo P, System::Typinfo::PTypeInfo RequiredRoot, System::PResStringRec ErrMsg);
	static void __fastcall ValidateMethods(System::Typinfo::PTypeInfo P);
	
protected:
	static void __fastcall ValidateClassHierarchy(System::Typinfo::PTypeInfo P);
	static void __fastcall ValidateInstanceHierarchy(System::Typinfo::PTypeInfo P);
	static void __fastcall ValidateProtocolHierarchy(System::Typinfo::PTypeInfo P);
	
public:
	static void __fastcall ValidateClassType(System::Typinfo::PTypeInfo P);
	static void __fastcall ValidateInstanceType(System::Typinfo::PTypeInfo P);
	static void __fastcall ValidateProtocolType(System::Typinfo::PTypeInfo P);
public:
	/* TObject.Create */ inline __fastcall TOCValidate() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TOCValidate() { }
	
};


class PASCALIMPLEMENTATION TOCImport : public System::Rtti::TRawVirtualClass
{
	typedef System::Rtti::TRawVirtualClass inherited;
	
protected:
	void *FID;
	void *FClsID;
	void * __fastcall GetObjectID();
	
public:
	__fastcall TOCImport(void * ID, void * ClsID, TOCVTable* VTable);
	__fastcall virtual ~TOCImport();
private:
	void *__ILocalObject;	// ILocalObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {55351304-9562-4039-BF44-AA5792DB6C30}
	operator _di_ILocalObject()
	{
		_di_ILocalObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ILocalObject*(void) { return (ILocalObject*)&__ILocalObject; }
	#endif
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename C, typename T> class PASCALIMPLEMENTATION TOCGenericImport__2 : public TOCImport
{
	typedef TOCImport inherited;
	
private:
	static TOCVTable* FInstanceVTable;
	static TOCVTable* FClassVTable;
	static C FOCClass;
	static C __fastcall GetOCClass();
	__classmethod TOCVTable* __fastcall GetInstanceVTable();
	// __classmethod void __fastcall Destroy@();
	
public:
	__classmethod T __fastcall Wrap(void * P);
	/* static */ __property C OCClass = {read=GetOCClass};
	__classmethod T __fastcall Create()/* overload */;
	__classmethod T __fastcall Alloc()/* overload */;
	__classmethod void __fastcall Init(T O, void * P);
	
private:
	// __classmethod void __fastcall Create@();
public:
	/* TOCImport.Create */ inline __fastcall TOCGenericImport__2(void * ID, void * ClsID, TOCVTable* VTable) : TOCImport(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TOCGenericImport__2() { }
	
};


typedef System::DynamicArray<System::Typinfo::PTypeInfo> TProtocols;

class PASCALIMPLEMENTATION TOCInterfacedObject : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	virtual void __fastcall AfterConstruction();
	virtual void __fastcall BeforeDestruction();
public:
	/* TObject.Create */ inline __fastcall TOCInterfacedObject() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TOCInterfacedObject() { }
	
};


class PASCALIMPLEMENTATION TOCLocal : public TOCInterfacedObject
{
	typedef TOCInterfacedObject inherited;
	
private:
	void *FObjectID;
	_di_IObjectiveCInstance FSuper;
	_di_IObjectiveCInstance __fastcall GetSuper();
	
protected:
	void * __fastcall GetObjectID();
	void __fastcall UpdateObjectID(void * Val);
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	__property _di_IObjectiveCInstance Super = {read=GetSuper};
	__fastcall TOCLocal();
	
public:
	__fastcall virtual ~TOCLocal();
private:
	void *__ILocalObject;	// ILocalObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E7B0A40-F6AB-4FF5-9BE0-92DCB2909899}
	operator _di_IObjectiveC()
	{
		_di_IObjectiveC intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IObjectiveC*(void) { return (IObjectiveC*)&__ILocalObject; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {55351304-9562-4039-BF44-AA5792DB6C30}
	operator _di_ILocalObject()
	{
		_di_ILocalObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ILocalObject*(void) { return (ILocalObject*)&__ILocalObject; }
	#endif
	
};


class PASCALIMPLEMENTATION TVTableCache : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Generics::Collections::TDictionary__2<System::Typinfo::PTypeInfo,TOCVTable*>* VTables;
	static System::Generics::Collections::TDictionary__2<System::Typinfo::PTypeInfo,TOCVTable*>* SuperVTables;
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
protected:
	__classmethod TOCVTable* __fastcall GetVTable(System::Typinfo::PTypeInfo P);
	__classmethod TOCVTable* __fastcall GetSuperVTable(System::Typinfo::PTypeInfo P);
public:
	/* TObject.Create */ inline __fastcall TVTableCache() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TVTableCache() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define IID_ILocalObject_Name u"{55351304-9562-4039-BF44-AA5792DB6C30}"
extern DELPHI_PACKAGE GUID IID_ILocalObject;
#define IID_IObjectiveC_Name u"{3E7B0A40-F6AB-4FF5-9BE0-92DCB2909899}"
extern DELPHI_PACKAGE GUID IID_IObjectiveC;
#define IID_IObjectiveCInstance_Name u"{B72015CE-B78D-4718-87D2-B639AA153818}"
extern DELPHI_PACKAGE GUID IID_IObjectiveCInstance;
#define IID_IObjectiveCClass_Name u"{ADD1B823-793E-4E51-867B-A01CC83B7739}"
extern DELPHI_PACKAGE GUID IID_IObjectiveCClass;
extern DELPHI_PACKAGE System::UnicodeString __fastcall MangleMethodType(System::Rtti::TRttiMethod* const Method);
extern DELPHI_PACKAGE System::UnicodeString __fastcall MangleMethodName(System::Rtti::TRttiMethod* const Method);
extern DELPHI_PACKAGE System::UnicodeString __fastcall MangleType(System::Rtti::TRttiType* const RttiType)/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall MangleParameters(System::Rtti::TRttiMethod* const Method);
extern DELPHI_PACKAGE void * __fastcall GetObjectiveCObject(void * P);
extern DELPHI_PACKAGE void __fastcall WrapInterface(void * ObjCId, void * ObjType, /* out */ void *Obj);
extern DELPHI_PACKAGE void __fastcall WrapObjectiveCReturn(void * ObjCId, POCMethodInvokeData InvokeData, /* out */ void *Obj);
extern DELPHI_PACKAGE System::UTF8String __fastcall ShortStrToUTF8String(const char * AString);
extern DELPHI_PACKAGE void __fastcall RegisterObjectiveCClass(System::TClass Cls, System::Typinfo::PTypeInfo Implementing);
}	/* namespace Objectivec */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_OBJECTIVEC)
using namespace Macapi::Objectivec;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_ObjectivecHPP
