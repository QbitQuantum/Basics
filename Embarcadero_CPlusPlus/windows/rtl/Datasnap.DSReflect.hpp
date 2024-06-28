// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSReflect.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsreflectHPP
#define Datasnap_DsreflectHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <System.JSON.Writers.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXJSON.hpp>
#include <Data.DBXJSONReflect.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.TypInfo.hpp>
#include <System.ObjAuto.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Rtti.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsreflect
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSAdapterClass;
class DELPHICLASS TDSDataModuleAdapterClass;
class DELPHICLASS TDSClass;
class DELPHICLASS TDSPackage;
class DELPHICLASS TDSMethodValues;
class DELPHICLASS TDSMethod;
//-- type declarations -------------------------------------------------------
typedef System::DynamicArray<System::Rtti::TValue> TArrayOfTValue;

typedef System::DynamicArray<System::TObject*> TArrayOfObject;

typedef System::DynamicArray<TDSMethod*> TDSMethodArray;

typedef System::DynamicArray<TDSClass*> TDSClassArray;

#ifndef _WIN64
typedef System::TMetaClass* TDSAdapterClassType;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TDSAdapterClassType);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSAdapterClass : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::TObject* FAdapteeInstance;
	
public:
	__fastcall virtual TDSAdapterClass(System::TObject* AdapteeInstance);
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDSAdapterClass() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSDataModuleAdapterClass : public TDSAdapterClass
{
	typedef TDSAdapterClass inherited;
	
protected:
	virtual System::Classes::TDataModule* __fastcall ExtractDataModule() = 0 ;
public:
	/* TDSAdapterClass.Create */ inline __fastcall virtual TDSDataModuleAdapterClass(System::TObject* AdapteeInstance) : TDSAdapterClass(AdapteeInstance) { }
	
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDSDataModuleAdapterClass() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSClass : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TPersistentClass FClassRef;
	TDSClass* FAdapteeClass;
	System::UnicodeString FClassName;
	bool FIsArrayParameter;
	bool FIsVarParameter;
	bool FIsOutParameter;
	System::Typinfo::TTypeData *FOriginalTypeData;
	System::Typinfo::TTypeData *FTypeData;
	bool FValueParameter;
	bool FIsAdapted;
	bool FInvalidTypeData;
	TDSMethodArray __fastcall GetMethods();
	int __fastcall GetDBXDataType(bool AllowUnknown, Data::Dbxcommon::TDBXParameter* Parameter);
	int __fastcall GetDBXSubDataType();
	System::UnicodeString __fastcall GetDSClassName();
	bool __fastcall IsVoidReturn();
	bool __fastcall IsArrayParameter();
	bool __fastcall IsInOutParameter();
	bool __fastcall IsOutParameter();
	System::UnicodeString __fastcall GetClassLoadError();
	System::UnicodeString __fastcall GetTypeUnit();
	
public:
	__fastcall TDSClass(System::Classes::TPersistentClass AClassRef, bool AIsAdapted)/* overload */;
	__fastcall TDSClass(System::Classes::TPersistentClass AClassRef, TDSClass* AAdapteeClass)/* overload */;
	__fastcall TDSClass(System::UnicodeString ClassName, System::Typinfo::PTypeData TypeData, bool AIsArrayParameter, bool AIsVarParameter, bool AIsOutParameter)/* overload */;
	__fastcall virtual ~TDSClass();
	System::TObject* __fastcall CreateInstance();
	void __fastcall GetDbxType(Data::Dbxcommon::TDBXParameter* Parameter);
	TDSMethod* __fastcall CreateMethod(System::UnicodeString MethodName);
	__property TDSMethodArray Methods = {read=GetMethods};
	__property System::UnicodeString DSClassName = {read=GetDSClassName};
	__property bool VoidReturn = {read=IsVoidReturn, nodefault};
	__property bool ArrayParameter = {read=IsArrayParameter, nodefault};
	__property bool OutParameter = {read=IsOutParameter, nodefault};
	__property bool InOutParameter = {read=IsInOutParameter, nodefault};
	__property System::UnicodeString ClassLoadError = {read=GetClassLoadError};
	__property bool ValueParameter = {read=FValueParameter, nodefault};
	__property TDSClass* AdapteeDSClass = {read=FAdapteeClass};
	__property System::UnicodeString TypeUnit = {read=GetTypeUnit};
	__property System::Classes::TPersistentClass ClassRef = {read=FClassRef};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSPackage : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FPackagename;
	System::Classes::TStringList* FClassList;
	void __fastcall GetClassesProc(System::Classes::TPersistentClass AClass);
	
public:
	__fastcall TDSPackage();
	__fastcall virtual ~TDSPackage();
	Data::Dbxplatform::TDBXStringArray __fastcall GetDSPackages();
	Data::Dbxplatform::TDBXStringArray __fastcall GetDSClasses(System::UnicodeString classNamePattern);
	TDSClass* __fastcall CreateDSClass(System::UnicodeString ClassName);
	__property System::UnicodeString PackageName = {read=FPackagename, write=FPackagename};
	__property Data::Dbxplatform::TDBXStringArray DSPackages = {read=GetDSPackages};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSMethodValues : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<System::Generics::Collections::TPair__2<System::TObject*,bool> > TArrayOfPair;
	
	
private:
	TArrayOfPair FAllocatedObjects;
	System::TObject* FAllocatedReturn;
	TArrayOfTValue FMethodValues;
	System::Rtti::TValue FReturnValue;
	bool FServerSideCommand;
	Data::Dbxjsonreflect::TJSONMarshal* FJSONMarshal;
	Data::Dbxjsonreflect::TJSONUnMarshal* FJSONUnMarshal;
	System::Generics::Collections::TObjectList__1<System::TObject*>* FUserObjects;
	void __fastcall SetDBXJSONValueParameter(Data::Dbxcommon::TDBXParameter* const DBXParameter, const System::Rtti::TValue &Value);
	void __fastcall SetDBXParameter(Data::Dbxcommon::TDBXParameter* const DBXParameter, const System::Rtti::TValue &Value);
	void __fastcall SetDBXReaderParameter(Data::Dbxcommon::TDBXParameter* const DBXParameter, const System::Rtti::TValue &Value);
	void __fastcall SetDBXStreamParameter(Data::Dbxcommon::TDBXParameter* const DBXParameter, const System::Rtti::TValue &Value);
	void __fastcall PopulateMarshal(Data::Dbxcommon::TDBXParameter* const Parameter);
	System::TObject* __fastcall JSONToUserObject(System::Json::TJSONValue* Json);
	System::Json::TJSONValue* __fastcall UserObjectToJSON(System::TObject* Data);
	void __fastcall SetAllocatedObject(int Ordinal, System::TObject* AllocatedObject, bool AlwaysFree = false);
	void __fastcall SetServerSideCommand(bool AServerSide);
	template<typename T> T __fastcall GetValObject(const System::Rtti::TValue &Value);
	
public:
	__fastcall TDSMethodValues();
	__fastcall virtual ~TDSMethodValues();
	bool __fastcall ClearReferenceParameters();
	void __fastcall AssignParameterValues(Data::Dbxcommon::TDBXParameterArray Parameters);
	void __fastcall GetReturnValue(Data::Dbxcommon::TDBXParameter* ReturnValue);
	void __fastcall GetOutValue(Data::Dbxcommon::TDBXParameter* OutValue);
	TArrayOfTValue __fastcall GetValues();
	__property System::Rtti::TValue ReturnValue = {read=FReturnValue, write=FReturnValue};
	__property bool ServerSidecommand = {read=FServerSideCommand, write=SetServerSideCommand, nodefault};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSMethod : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Objauto::TMethodInfoHeader *FMethodInfoHeader;
	TDSClassArray FParameterTypes;
	Data::Dbxplatform::TDBXStringArray FParameterNames;
	System::UnicodeString FMethodName;
	TDSClass* FMethodClass;
	TDSClass* FDSReturnType;
	bool FIsPublicMethod;
	bool FIsStaticMethod;
	bool FIsConstructor;
	bool FIsDestructor;
	bool __fastcall IsPublicMethod();
	bool __fastcall IsStaticMethod();
	TDSClassArray __fastcall GetParameterTypes();
	TDSClass* __fastcall GetReturnType();
	System::UnicodeString __fastcall GetDSMethodName();
	TDSClass* __fastcall GetMethodClass();
	Data::Dbxplatform::TDBXStringArray __fastcall GetParameterNames();
	
public:
	__classmethod System::UnicodeString __fastcall InvokeStringFunction(Data::Dbxplatform::TObjectClass objClass, System::UnicodeString methodName);
	__fastcall TDSMethod(System::Objauto::PMethodInfoHeader AMethodInfo, TDSClass* const AMethodClass);
	__fastcall virtual ~TDSMethod();
	System::TObject* __fastcall GetClassInstance(System::TObject* AObject);
	void __fastcall Invoke(System::TObject* MethodInstance, TDSMethodValues* MethodValues);
	__property bool PublicMethod = {read=IsPublicMethod, nodefault};
	__property bool StaticMethod = {read=IsStaticMethod, nodefault};
	__property TDSClassArray ParameterTypes = {read=GetParameterTypes};
	__property Data::Dbxplatform::TDBXStringArray ParameterNames = {read=GetParameterNames};
	__property TDSClass* ReturnType = {read=GetReturnType};
	__property System::UnicodeString DSMethodName = {read=GetDSMethodName};
	__property TDSClass* MethodClass = {read=GetMethodClass};
	__property bool IsConstructor = {read=FIsConstructor, nodefault};
	__property bool IsDestructor = {read=FIsDestructor, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define STDataSet L"TDataSet"
#define STParams L"TParams"
#define STDBXReaderValue L"TDBXReaderValue"
#define SOleVariant L"OleVariant"
}	/* namespace Dsreflect */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSREFLECT)
using namespace Datasnap::Dsreflect;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsreflectHPP
