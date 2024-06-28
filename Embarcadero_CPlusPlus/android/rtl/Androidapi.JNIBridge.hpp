// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNIBridge.pas' rev: 34.00 (Android)

#ifndef Androidapi_JnibridgeHPP
#define Androidapi_JnibridgeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Rtti.hpp>
#include <System.TypInfo.hpp>
#include <System.Generics.Collections.hpp>
#include <Androidapi.Jni.hpp>
#include <Androidapi.JNIMarshal.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jnibridge
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IJava;
typedef System::DelphiInterface<IJava> _di_IJava;
__interface DELPHIINTERFACE IJavaClass;
typedef System::DelphiInterface<IJavaClass> _di_IJavaClass;
__interface DELPHIINTERFACE IJavaInstance;
typedef System::DelphiInterface<IJavaInstance> _di_IJavaInstance;
class DELPHICLASS TJavaVTable;
class DELPHICLASS EJNI;
class DELPHICLASS EJNIFatal;
__interface DELPHIINTERFACE ILocalObject;
typedef System::DelphiInterface<ILocalObject> _di_ILocalObject;
class DELPHICLASS TJavaImport;
template<typename C, typename T> class DELPHICLASS TJavaGenericImport__2;
class DELPHICLASS TJInterfacedObject;
class DELPHICLASS TJavaLocal;
class DELPHICLASS TVTableCache;
class DELPHICLASS TClassLoader;
class DELPHICLASS TJavaValidate;
class DELPHICLASS TJNIResolver;
class DELPHICLASS JavaSignatureAttribute;
class DELPHICLASS TJavaBasicArray;
template<typename T> class DELPHICLASS TJavaArray__1;
template<typename T> class DELPHICLASS TJavaObjectArray__1;
template<typename T> class DELPHICLASS TJavaBiArray__1;
template<typename T> class DELPHICLASS TJavaObjectBiArray__1;
class DELPHICLASS TRegTypes;
class DELPHICLASS TBridgeHelper;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{2866B78E-2258-4DE6-A075-C37264E2C837}") IJava  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{ABFF4754-6EC8-4B84-B541-4FC471500856}") IJavaClass  : public IJava 
{
	
};

__interface  INTERFACE_UUID("{E9063409-906F-4C8D-ABF2-E10318F8E72C}") IJavaInstance  : public IJava 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJavaVTable : public System::Rtti::TRawVirtualClass::TVTable
{
	typedef System::Rtti::TRawVirtualClass::TVTable inherited;
	
private:
	System::TArray__1<Androidapi::Jnimarshal::JNIMethodInvokeData> FMethodInfoData;
	System::TArray__1<GUID> FGuids;
	
protected:
	__property System::TArray__1<GUID> Guids = {read=FGuids};
	__fastcall TJavaVTable(System::Typinfo::PTypeInfo P, void * ClsID, bool IsClassTable);
public:
	/* TVTable.Destroy */ inline __fastcall virtual ~TJavaVTable() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EJNI : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EJNI(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EJNI(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EJNI(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EJNI(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EJNI(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EJNI(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EJNI(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EJNI(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJNI(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJNI(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJNI(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJNI(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EJNI() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EJNIFatal : public EJNI
{
	typedef EJNI inherited;
	
public:
	/* Exception.Create */ inline __fastcall EJNIFatal(const System::UnicodeString Msg) : EJNI(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EJNIFatal(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EJNI(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EJNIFatal(NativeUInt Ident)/* overload */ : EJNI(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EJNIFatal(System::PResStringRec ResStringRec)/* overload */ : EJNI(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EJNIFatal(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EJNI(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EJNIFatal(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EJNI(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EJNIFatal(const System::UnicodeString Msg, int AHelpContext) : EJNI(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EJNIFatal(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EJNI(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJNIFatal(NativeUInt Ident, int AHelpContext)/* overload */ : EJNI(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJNIFatal(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EJNI(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJNIFatal(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EJNI(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJNIFatal(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EJNI(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EJNIFatal() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{81DD0F8E-7E6C-4D63-BE42-EB691CAAE686}") ILocalObject  : public IJava 
{
	virtual void * __fastcall GetObjectID() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJavaImport : public System::Rtti::TRawVirtualClass
{
	typedef System::Rtti::TRawVirtualClass inherited;
	
private:
	void *FJNIObjectID;
	
public:
	__fastcall TJavaImport(void * ID, TJavaVTable* const VTable);
	__fastcall virtual ~TJavaImport();
	void * __fastcall GetObjectID();
private:
	void *__ILocalObject;	// ILocalObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {81DD0F8E-7E6C-4D63-BE42-EB691CAAE686}
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename C, typename T> class PASCALIMPLEMENTATION TJavaGenericImport__2 : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TJavaVTable* FInstanceVTable;
	static TJavaVTable* FClassVTable;
	static C FJavaClass;
	static void *FJNIClassID;
	static C __fastcall GetJavaClass();
	static T __fastcall Alloc()/* overload */;
	// __classmethod void __fastcall Destroy_();
	
public:
	static T __fastcall Wrap(void * AJNIObjectID)/* overload */;
	static T __fastcall Wrap(const _di_IJavaInstance AInstance)/* overload */;
	/* static */ __property C JavaClass = {read=GetJavaClass};
	static T __fastcall Create();
	static void * __fastcall GetClsID();
	
private:
	// __classmethod void __fastcall Create_();
public:
	/* TObject.Create */ inline __fastcall TJavaGenericImport__2() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJavaGenericImport__2() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInterfacedObject : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	virtual void __fastcall AfterConstruction();
	virtual void __fastcall BeforeDestruction();
public:
	/* TObject.Create */ inline __fastcall TJInterfacedObject() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInterfacedObject() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJavaLocal : public TJInterfacedObject
{
	typedef TJInterfacedObject inherited;
	
public:
	#define TJavaLocal_DefaultProxyInterfaceName u"com/embarcadero/rtl/ProxyInterface"
	
	
private:
	static System::UnicodeString FProxyInterfaceName;
	void *FObjectID;
	void *FLocalRefObjectID;
	
private:
	// __classmethod void __fastcall Create_();
	
private:
	static System::UnicodeString __fastcall GetProxyInterfaceNameFromContext(Androidapi::Jni::JNIObject AContext);
	
protected:
	void * __fastcall GetObjectID();
	
public:
	__fastcall TJavaLocal();
	__fastcall virtual ~TJavaLocal();
	int __cdecl hashCode();
	HIDESBASE bool __cdecl equals(void * Obj)/* overload */;
	HIDESBASE Androidapi::Jni::JNIObject __cdecl toString()/* overload */;
	Androidapi::Jni::JNIObject __fastcall getName();
	
private:
	// __classmethod void __fastcall Destroy_();
private:
	void *__ILocalObject;	// ILocalObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2866B78E-2258-4DE6-A075-C37264E2C837}
	operator _di_IJava()
	{
		_di_IJava intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IJava*(void) { return (IJava*)&__ILocalObject; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {81DD0F8E-7E6C-4D63-BE42-EB691CAAE686}
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TVTableCache : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Generics::Collections::TObjectDictionary__2<System::Typinfo::PTypeInfo,TJavaVTable*>* VTables;
	// __classmethod void __fastcall Create_();
	// __classmethod void __fastcall Destroy_();
	
protected:
	__classmethod TJavaVTable* __fastcall GetVTable(System::Typinfo::PTypeInfo P, void * ClsID, bool IsClassTable);
	__classmethod void __fastcall DeleteVTable(System::Typinfo::PTypeInfo P, TJavaVTable* const J);
public:
	/* TObject.Create */ inline __fastcall TVTableCache() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TVTableCache() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TClassLoader : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Androidapi::Jni::_JNIMethodID *LoadClassID;
	Androidapi::Jni::_JNIObject *Instance;
	bool __fastcall CreateDefaultClassLoader();
	Androidapi::Jni::JNIObject __fastcall GetContextClassLoader(Androidapi::Jni::JNIObject AJavaContext);
	
public:
	__fastcall TClassLoader();
	__fastcall virtual ~TClassLoader();
	Androidapi::Jni::JNIObject __fastcall LoadClass(const System::UnicodeString AClass);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJavaValidate : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static void __fastcall ValidateTypeHierarchy(System::Typinfo::PTypeInfo P, System::Typinfo::PTypeInfo RequiredRoot, System::PResStringRec ErrMsg);
	
protected:
	static void __fastcall ValidateClassHierarchy(System::Typinfo::PTypeInfo P);
	static void __fastcall ValidateInstanceHierarchy(System::Typinfo::PTypeInfo P);
public:
	/* TObject.Create */ inline __fastcall TJavaValidate() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJavaValidate() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNIResolver : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,Androidapi::Jni::JNIObject>* ClassRefCache;
	static System::Generics::Collections::TDictionary__2<void *,System::Rtti::TValue>* ReturnValues;
	static System::Generics::Collections::TDictionary__2<void *,Androidapi::Jni::JNIObject>* ReturnValuesJNIObject;
	static Androidapi::Jni::_JNIMethodID *FIntMethodID;
	static Androidapi::Jni::_JNIMethodID *FCharMethodID;
	static Androidapi::Jni::_JNIMethodID *FBooleanMethodID;
	static Androidapi::Jni::_JNIMethodID *FLongMethodID;
	static Androidapi::Jni::_JNIMethodID *FShortMethodID;
	static Androidapi::Jni::_JNIMethodID *FByteMethodID;
	static Androidapi::Jni::_JNIMethodID *FFloatMethodID;
	static Androidapi::Jni::_JNIMethodID *FDoubleMethodID;
	static Androidapi::Jni::JNIMethodID __fastcall GetBasicTypeMethodID(const System::UnicodeString ClassSig, const System::UnicodeString ClassGetMethod, const System::UnicodeString ClassGetMethodSig);
	static Androidapi::Jni::JNIObject __fastcall InternalGetJavaClassID(const System::UnicodeString AClass);
	static void __fastcall AddReturnValue(void * Obj, const System::Rtti::TValue &AValue)/* overload */;
	static void __fastcall RemoveReturnValue(void * Obj);
	
public:
	static DELPHITHREAD JNIEnv *JNIEnvRes;
	static TClassLoader* ClassLoader;
	static Androidapi::Jni::PJNIEnv __fastcall GetJNIEnv();
	static Androidapi::Jni::JNIObject __fastcall GetJavaClassID(const System::UnicodeString AClass);
	static Androidapi::Jni::JNIMethodID __fastcall GetJavaMethodID(Androidapi::Jni::JNIObject AClass, const System::UnicodeString AMethod, const System::UnicodeString AMethodSig, bool IsClassTable = true);
	static Androidapi::Jni::JNIMethodID __fastcall GetJavaStaticMethodID(Androidapi::Jni::JNIObject AClass, const System::UnicodeString AMethod, const System::UnicodeString AMethodSig);
	static Androidapi::Jni::JNIFieldID __fastcall GetJavaStaticFieldID(Androidapi::Jni::JNIObject AClass, const System::UnicodeString AField, const System::UnicodeString AFieldSig);
	static Androidapi::Jni::JNIFieldID __fastcall GetJavaFieldID(Androidapi::Jni::JNIObject AClass, const System::UnicodeString AField, const System::UnicodeString AFieldSig);
	static void __fastcall DeleteLocalRef(Androidapi::Jni::JNIObject AObject);
	static void __fastcall DeleteGlobalRef(Androidapi::Jni::JNIObject AObject);
	static void __fastcall ExceptionCheck();
	static Androidapi::Jni::JNIObjectRefType __fastcall GetObjectRefType(Androidapi::Jni::JNIObject AObject);
	static Androidapi::Jni::JNIObject __fastcall NewObject(Androidapi::Jni::JNIObject AClass);
	static Androidapi::Jni::JNIObject __fastcall NewGlobalRef(Androidapi::Jni::JNIObject AJNIObject);
	static Androidapi::Jni::JNIObject __fastcall GetObjectArrayElement(Androidapi::Jni::JNIObject AArray, int Index);
	static void __fastcall SetObjectArrayElement(Androidapi::Jni::JNIObject AArray, int Index, const void *Val);
	static void __fastcall SetRawObjectArrayElement(Androidapi::Jni::JNIObject AArray, int Index, const void *Val);
	static int __fastcall GetRawValueFromJInteger(Androidapi::Jni::JNIObject AJInteger);
	static bool __fastcall GetRawValueFromJBoolean(Androidapi::Jni::JNIObject AJBoolean);
	static System::WideChar __fastcall GetRawValueFromJCharacter(Androidapi::Jni::JNIObject AJCharacter);
	static __int64 __fastcall GetRawValueFromJLong(Androidapi::Jni::JNIObject AJLong);
	static short __fastcall GetRawValueFromJShort(Androidapi::Jni::JNIObject AJShort);
	static System::Int8 __fastcall GetRawValueFromJByte(Androidapi::Jni::JNIObject AJByte);
	static double __fastcall GetRawValueFromJDouble(Androidapi::Jni::JNIObject AJDouble);
	static float __fastcall GetRawValueFromJFloat(Androidapi::Jni::JNIObject AJFloat);
	static int __fastcall GetArrayLength(Androidapi::Jni::JNIObject AJNIArray);
	static void * __fastcall JavaInstanceToID(const _di_IJavaInstance AJavaInstance);
	static bool __fastcall IsInstanceOf(const _di_IJavaInstance AJavaInstance, const Androidapi::Jni::JNIObject AClass);
	static bool __fastcall IsSameObject(const _di_IJavaInstance AObject1, const _di_IJavaInstance AObject2);
	
private:
	// __classmethod void __fastcall Create_();
	// __classmethod void __fastcall Destroy_();
public:
	/* TObject.Create */ inline __fastcall TJNIResolver() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNIResolver() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION JavaSignatureAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	System::UnicodeString FSignature;
	
public:
	__fastcall JavaSignatureAttribute(const System::UnicodeString S);
	__property System::UnicodeString Signature = {read=FSignature};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~JavaSignatureAttribute() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJavaBasicArray : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Androidapi::Jni::_JNIObject *Handle;
	virtual void __fastcall ProcessArray(bool CreateArray, int Len, void * AHandle) = 0 ;
	int __fastcall GetArrayLength();
	
protected:
	bool FIsCopy;
	bool FElementsAccessed;
	Androidapi::Jni::_JNIObject *FClassID;
	
public:
	static System::Rtti::TRttiContext Context;
	
private:
	// __classmethod void __fastcall Create_();
	// __classmethod void __fastcall Destroy_();
	
public:
	Androidapi::Jni::JNIObject __fastcall ToPointer();
	virtual void __fastcall RefreshValues() = 0 ;
	virtual void __fastcall Sync() = 0 ;
	__property int Length = {read=GetArrayLength, nodefault};
	__property bool IsCopy = {read=FIsCopy, nodefault};
	__property bool ElementsAccessed = {read=FElementsAccessed, nodefault};
public:
	/* TObject.Create */ inline __fastcall TJavaBasicArray() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJavaBasicArray() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef TJavaBasicArray* *PJavaBasicArray;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TJavaArray__1 : public TJavaBasicArray
{
	typedef TJavaBasicArray inherited;
	
	
public:
	typedef T *PJavaArrayBaseType;
	
	/* [Template Alias] */
	#if defined(__clang__)
	using TJavaArrayReleaser = void __cdecl (*)(Androidapi::Jni::PJNIEnv Env, Androidapi::Jni::JNIObject AArray, PJavaArrayBaseType Elems, int Mode);
	#endif
	
	/* [Template Alias] */
	#if defined(__clang__)
	using TJavaArrayElementsGetter = void * __cdecl (*)(Androidapi::Jni::PJNIEnv Env, Androidapi::Jni::JNIObject AArray, Androidapi::Jni::PJNIBoolean IsCopy);
	#endif
	
	
public:
	T operator[](int AIndex) { return this->Items[AIndex]; }
	
private:
	TJavaArrayReleaser FArrayReleaser;
	TJavaArrayElementsGetter FArrayGetter;
	PJavaArrayBaseType FArrayElem;
	System::Rtti::TRttiType* FBaseType;
	virtual T __fastcall GetItem(int AIndex);
	virtual void __fastcall SetItem(int AIndex, T AValue);
	PJavaArrayBaseType __fastcall GetArrayElem();
	virtual void __fastcall ProcessArray(bool CreateArray, int Len, void * AHandle);
	
public:
	__fastcall TJavaArray__1(int Len)/* overload */;
	__fastcall TJavaArray__1()/* overload */;
	__fastcall virtual ~TJavaArray__1();
	virtual void __fastcall RefreshValues();
	virtual void __fastcall Sync();
	static TJavaArray__1<T>* __fastcall Wrap(TJavaBasicArray* const AnArray);
	__property T Items[int AIndex] = {read=GetItem, write=SetItem/*, default*/};
	__property PJavaArrayBaseType Data = {read=GetArrayElem};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TJavaObjectArray__1 : public TJavaArray__1<T>
{
	typedef TJavaArray__1<T> inherited;
	
private:
	virtual T __fastcall GetItem(int AIndex);
	virtual void __fastcall SetItem(int AIndex, T AValue);
	
public:
	Androidapi::Jni::JNIObject __fastcall GetRawItem(int AIndex);
	void __fastcall SetRawItem(int AIndex, Androidapi::Jni::JNIObject AValue);
	static TJavaObjectArray__1<T>* __fastcall Wrap(TJavaBasicArray* const AnArray);
public:
	/* {Androidapi_JNIBridge}TJavaArray<Androidapi_JNIBridge_TJavaObjectArray<T>_T>.Create */ inline __fastcall TJavaObjectArray__1(int Len)/* overload */ : TJavaArray__1<T>(Len) { }
	/* {Androidapi_JNIBridge}TJavaArray<Androidapi_JNIBridge_TJavaObjectArray<T>_T>.Create */ inline __fastcall TJavaObjectArray__1()/* overload */ : TJavaArray__1<T>() { }
	/* {Androidapi_JNIBridge}TJavaArray<Androidapi_JNIBridge_TJavaObjectArray<T>_T>.Destroy */ inline __fastcall virtual ~TJavaObjectArray__1() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TJavaBiArray__1 : public TJavaArray__1<T>
{
	typedef TJavaArray__1<T> inherited;
	
public:
	/* {Androidapi_JNIBridge}TJavaArray<Androidapi_JNIBridge_TJavaBiArray<T>_T>.Create */ inline __fastcall TJavaBiArray__1(int Len)/* overload */ : TJavaArray__1<T>(Len) { }
	/* {Androidapi_JNIBridge}TJavaArray<Androidapi_JNIBridge_TJavaBiArray<T>_T>.Create */ inline __fastcall TJavaBiArray__1()/* overload */ : TJavaArray__1<T>() { }
	/* {Androidapi_JNIBridge}TJavaArray<Androidapi_JNIBridge_TJavaBiArray<T>_T>.Destroy */ inline __fastcall virtual ~TJavaBiArray__1() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TJavaObjectBiArray__1 : public TJavaArray__1<T>
{
	typedef TJavaArray__1<T> inherited;
	
public:
	/* {Androidapi_JNIBridge}TJavaArray<Androidapi_JNIBridge_TJavaObjectBiArray<T>_T>.Create */ inline __fastcall TJavaObjectBiArray__1(int Len)/* overload */ : TJavaArray__1<T>(Len) { }
	/* {Androidapi_JNIBridge}TJavaArray<Androidapi_JNIBridge_TJavaObjectBiArray<T>_T>.Create */ inline __fastcall TJavaObjectBiArray__1()/* overload */ : TJavaArray__1<T>() { }
	/* {Androidapi_JNIBridge}TJavaArray<Androidapi_JNIBridge_TJavaObjectBiArray<T>_T>.Destroy */ inline __fastcall virtual ~TJavaObjectBiArray__1() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TRegTypes : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,System::Typinfo::PTypeInfo>* RegTypes;
	
private:
	// __classmethod void __fastcall Create_();
	// __classmethod void __fastcall Destroy_();
	
public:
	__classmethod void __fastcall RegisterType(const System::UnicodeString AQName, System::Typinfo::PTypeInfo TI);
	__classmethod System::Typinfo::PTypeInfo __fastcall GetType(const System::UnicodeString ATypeName);
public:
	/* TObject.Create */ inline __fastcall TRegTypes() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRegTypes() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBridgeHelper : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::TObject* FGetClassLock;
	
private:
	// __classmethod void __fastcall Create_();
	// __classmethod void __fastcall Destroy_();
	
private:
	static TJavaVTable* __fastcall GetInstanceVTable(TJavaVTable* &AVTable, System::Typinfo::PTypeInfo ATypeInfo, void * ClsID);
	static void __fastcall GetJavaClass(System::Typinfo::PTypeInfo CTypeInfo, System::Typinfo::PTypeInfo ITypeInfo, _di_IJavaClass &AJavaClass, void * &AClsID, TJavaVTable* &AClassVTable);
	__classmethod void __fastcall Wrap(void * P, System::Typinfo::PTypeInfo ITypeInfo, void * &JNIClassID, TJavaVTable* &ATable, System::_di_IInterface &Resp);
	__classmethod void __fastcall WrapInstance(const _di_IJavaInstance I, System::Typinfo::PTypeInfo ITypeInfo, void * &JNIClassID, TJavaVTable* &ATable, System::_di_IInterface &Resp);
	static void __fastcall Alloc(void * &ClsID, System::Typinfo::PTypeInfo ITypeInfo, TJavaVTable* &AVTable, void *Resp);
	static void * __fastcall GetClsID(void * &AClsID, System::Typinfo::PTypeInfo ATypeInfo);
#ifndef __aarch64__
	static void __fastcall ProcessArray(System::Typinfo::PTypeInfo LInfo, const System::Rtti::TRttiContext Context, void * &FArrayReleaser, void * &FArrayGetter, System::Rtti::TRttiType* &FBaseType, Androidapi::Jni::JNIObject &Handle, Androidapi::Jni::JNIObject &FClassID, bool CreateArray, int Len, void * AHandle);
#else /* __aarch64__ */
	static void __fastcall ProcessArray(System::Typinfo::PTypeInfo LInfo, const System::Rtti::TRttiContext &Context, void * &FArrayReleaser, void * &FArrayGetter, System::Rtti::TRttiType* &FBaseType, Androidapi::Jni::JNIObject &Handle, Androidapi::Jni::JNIObject &FClassID, bool CreateArray, int Len, void * AHandle);
#endif /* __aarch64__ */
public:
	/* TObject.Create */ inline __fastcall TBridgeHelper() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBridgeHelper() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define IID_ILocalObject_Name u"{81DD0F8E-7E6C-4D63-BE42-EB691CAAE686}"
extern DELPHI_PACKAGE GUID IID_ILocalObject;
#define IID_IJava_Name u"{2866B78E-2258-4DE6-A075-C37264E2C837}"
extern DELPHI_PACKAGE GUID IID_IJava;
#define IID_IJavaInstance_Name u"{E9063409-906F-4C8D-ABF2-E10318F8E72C}"
extern DELPHI_PACKAGE GUID IID_IJavaInstance;
#define IID_IJavaClass_Name u"{ABFF4754-6EC8-4B84-B541-4FC471500856}"
extern DELPHI_PACKAGE GUID IID_IJavaClass;
#define DefaultJConstructor u"<init>"
#define DefaultJConstructorName u"init"
#define DefaultJConstructorSig u"()V"
#define DefaultJGetter u"_Get"
#define DefaultJSetter u"_Set"
static constexpr System::Int8 DefaultJSetterLength = System::Int8(0x4);
static constexpr System::Int8 DefaultJGetterLength = System::Int8(0x4);
#define DexClassConstructorSig u"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Lja"\
	u"va/lang/ClassLoader;)V"
#define DexLoadClassMethod u"loadClass"
#define DexLoadClassSig u"(Ljava/lang/String;)Ljava/lang/Class;"
#define ActClassLoader u"loadClass"
#define ActClassLoaderSig u"(Ljava/lang/String;)Ljava/lang/Class;"
#define DexOutputDir u"outdex"
#define CreateProxyClassMethod u"CreateProxyClass"
#define CreateProxyClassSig u"(Ljava/lang/Class;J)Ljava/lang/Object;"
#define GetClassLoaderMethod u"getClassLoader"
#define GetClassLoaderSig u"()Ljava/lang/ClassLoader;"
#define JIntegerSig u"java/lang/Integer"
#define JIntegerGetMethod u"intValue"
#define JIntegerGetMethodSig u"()I"
#define JCharSig u"java/lang/Character"
#define JCharGetMethod u"charValue"
#define JCharGetMethodSig u"()C"
#define JBooleanSig u"java/lang/Boolean"
#define JBooleanGetMethod u"booleanValue"
#define JBooleanGetMethodSig u"()Z"
#define JLongSig u"java/lang/Long"
#define JLongGetMethod u"longValue"
#define JLongGetMethodSig u"()J"
#define JShortSig u"java/lang/Short"
#define JShortGetMethod u"shortValue"
#define JShortGetMethodSig u"()S"
#define JByteSig u"java/lang/Byte"
#define JByteGetMethod u"byteValue"
#define JByteGetMethodSig u"()B"
#define JFloatSig u"java/lang/Float"
#define JFloatGetMethod u"floatValue"
#define JFloatGetMethodSig u"()F"
#define JDoubleSig u"java/lang/Double"
#define JDoubleGetMethod u"doubleValue"
#define JDoubleGetMethodSig u"()D"
extern DELPHI_PACKAGE void __cdecl cleanNative(Androidapi::Jni::PJNIEnv Env, Androidapi::Jni::JNIObject This, __int64 DelphiObject);
extern DELPHI_PACKAGE Androidapi::Jni::JNIObject __cdecl dispatchToNative(Androidapi::Jni::PJNIEnv Env, Androidapi::Jni::JNIObject This, Androidapi::Jni::JNIObject Method, Androidapi::Jni::JNIObject Args, __int64 DelphiObject);
extern DELPHI_PACKAGE void __fastcall XFormInterface(void * Src, void * Dest);
extern DELPHI_PACKAGE void __fastcall XFormClass(void * Src, void * Dest);
extern DELPHI_PACKAGE void __fastcall WrapJNIReturn(void * ObjID, void * ClsID, void * ObjType, /* out */ void *Obj);
extern DELPHI_PACKAGE TJavaBasicArray* __fastcall WrapJNIArray(void * ObjID, void * ObjType);
extern DELPHI_PACKAGE void __fastcall ReleaseAndNil(void *Obj);
}	/* namespace Jnibridge */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNIBRIDGE)
using namespace Androidapi::Jnibridge;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_JnibridgeHPP
