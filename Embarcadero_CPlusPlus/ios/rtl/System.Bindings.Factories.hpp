// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.Factories.pas' rev: 34.00 (iOS)

#ifndef System_Bindings_FactoriesHPP
#define System_Bindings_FactoriesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Rtti.hpp>
#include <System.RTLConsts.hpp>
#include <System.Bindings.Consts.hpp>
#include <System.Bindings.NotifierContracts.hpp>
#include <System.Bindings.Expression.hpp>
#include <System.Bindings.Manager.hpp>
#include <System.Bindings.CustomScope.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Factories
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindingExpressionFactory;
class DELPHICLASS TBindingManagerFactory;
class DELPHICLASS EBindingScopeFactoryError;
class DELPHICLASS TBindingScopeFactory;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBindingExpressionFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod System::Bindings::Expression::TBindingExpression* __fastcall CreateExpression(System::Bindings::Manager::TBindingManager* Manager = (System::Bindings::Manager::TBindingManager*)(0x0));
public:
	/* TObject.Create */ inline __fastcall TBindingExpressionFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindingExpressionFactory() { }
	
};


class PASCALIMPLEMENTATION TBindingManagerFactory : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Bindings::Manager::TBindingManager* FAppManager;
	__classmethod System::Bindings::Manager::TBindingManager* __fastcall CreateManagerInstance(System::Bindings::Manager::TBindingManager* Owner);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	__classmethod System::Bindings::Manager::TBindingManager* __fastcall CreateManager(System::Bindings::Manager::TBindingManager* Owner = (System::Bindings::Manager::TBindingManager*)(0x0));
	/* static */ __property System::Bindings::Manager::TBindingManager* AppManager = {read=FAppManager};
public:
	/* TObject.Create */ inline __fastcall TBindingManagerFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindingManagerFactory() { }
	
};


class PASCALIMPLEMENTATION EBindingScopeFactoryError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBindingScopeFactoryError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBindingScopeFactoryError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBindingScopeFactoryError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBindingScopeFactoryError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindingScopeFactoryError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindingScopeFactoryError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBindingScopeFactoryError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBindingScopeFactoryError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindingScopeFactoryError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindingScopeFactoryError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindingScopeFactoryError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindingScopeFactoryError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBindingScopeFactoryError() { }
	
};


class PASCALIMPLEMENTATION TBindingScopeFactory : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef System::Generics::Collections::TPair__2<System::TClass,System::Bindings::Customscope::TScopeClass> TScopeTuple;
	
	
private:
	typedef System::Generics::Collections::TDictionary__2<System::TClass,System::Bindings::Customscope::TScopeClass>* TScopeTuples;
	
	
private:
	static System::Generics::Collections::TDictionary__2<System::TClass,System::Bindings::Customscope::TScopeClass>* FScopeTuples;
	static System::Generics::Collections::TDictionary__2<System::TClass,System::Bindings::Customscope::TScopeClass>* __fastcall GetScopeTuples();
	static int __fastcall GetScopeClassCount();
	static System::Bindings::Customscope::TScopeClass __fastcall GetScopeClasses(const System::TClass ObjectType);
	
private:
	// __classmethod void __fastcall Destroy@();
	
public:
	__classmethod void __fastcall RegisterScope(System::TClass ObjectType, System::Bindings::Customscope::TScopeClass ScopeClass);
	__classmethod void __fastcall UnregisterObjectType(System::TClass ObjectType);
	__classmethod void __fastcall UnregisterScope(System::Bindings::Customscope::TScopeClass ScopeClass);
	__classmethod void __fastcall UnregisterScopes();
	__classmethod bool __fastcall IsObjectTypeRegistered(System::TClass ObjectType, bool InheritOkay = false);
	__classmethod bool __fastcall IsScopeClassRegistered(System::Bindings::Customscope::TScopeClass ScopeClass);
	__classmethod System::Bindings::Customscope::TScopeClass __fastcall GetBestFitScope(System::TClass ObjectType);
	__classmethod System::Generics::Collections::TDictionary__2<System::TClass,System::Bindings::Customscope::TScopeClass>::TPairEnumerator* __fastcall GetEnumerator();
	__classmethod System::Bindings::Customscope::TCustomScope* __fastcall CreateScope(System::TObject* const AObject, System::TClass MetaClass)/* overload */;
	__classmethod bool __fastcall CreateScope(System::TObject* const AObject, System::TClass MetaClass, /* out */ System::Bindings::Customscope::TCustomScope* &CustomScope)/* overload */;
	__classmethod System::Bindings::Customscope::TCustomScope* __fastcall CreateScope(System::TObject* const AObject)/* overload */;
	__classmethod bool __fastcall CreateScope(System::TObject* const AObject, /* out */ System::Bindings::Customscope::TCustomScope* &CustomScope)/* overload */;
	/* static */ __property System::Bindings::Customscope::TScopeClass ScopeClasses[const System::TClass ObjectType] = {read=GetScopeClasses};
	/* static */ __property int ScopeClassCount = {read=GetScopeClassCount, nodefault};
	
private:
	// __classmethod void __fastcall Create@();
public:
	/* TObject.Create */ inline __fastcall TBindingScopeFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindingScopeFactory() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Factories */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_FACTORIES)
using namespace System::Bindings::Factories;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS)
using namespace System::Bindings;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Bindings_FactoriesHPP
