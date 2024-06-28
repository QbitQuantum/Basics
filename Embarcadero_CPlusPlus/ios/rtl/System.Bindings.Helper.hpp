// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.Helper.pas' rev: 34.00 (iOS)

#ifndef System_Bindings_HelperHPP
#define System_Bindings_HelperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.TypInfo.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <System.Bindings.EvalSys.hpp>
#include <System.Bindings.NotifierContracts.hpp>
#include <System.Bindings.NotifierDefaults.hpp>
#include <System.Bindings.Factories.hpp>
#include <System.Bindings.Expression.hpp>
#include <System.Bindings.ExpressionDefaults.hpp>
#include <System.Bindings.Manager.hpp>
#include <System.Bindings.Outputs.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Helper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EBindHelperException;
struct TBindingEventRec;
class DELPHICLASS TBindings;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EBindHelperException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBindHelperException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBindHelperException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBindHelperException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBindHelperException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindHelperException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindHelperException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBindHelperException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBindHelperException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindHelperException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindHelperException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindHelperException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindHelperException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBindHelperException() { }
	
};


struct DECLSPEC_DRECORD TBindingEventRec
{
public:
	System::Bindings::Outputs::TBindingEvalErrorEvent EvalErrorEvent;
	System::Bindings::Outputs::TBindingAssigningValueEvent AssigningValueEvent;
	System::Bindings::Outputs::TBindingAssignedValueEvent AssignedValueEvent;
	System::Bindings::Outputs::TBindingLocationUpdatedEvent LocationUpdatedEvent;
	static TBindingEventRec __fastcall Create()/* overload */;
	__fastcall TBindingEventRec(System::Bindings::Outputs::TBindingEvalErrorEvent AEvalErrorEvent)/* overload */;
	__fastcall TBindingEventRec(System::Bindings::Outputs::TBindingAssigningValueEvent AAssigningValueEvent)/* overload */;
	__fastcall TBindingEventRec(System::Bindings::Outputs::TBindingEvalErrorEvent AEvalErrorEvent, System::Bindings::Outputs::TBindingAssigningValueEvent AAssigningValueEvent)/* overload */;
	__fastcall TBindingEventRec(System::Bindings::Outputs::TBindingEvalErrorEvent AEvalErrorEvent, System::Bindings::Outputs::TBindingAssigningValueEvent AAssigningValueEvent, System::Bindings::Outputs::TBindingAssignedValueEvent AAssignedValueEvent)/* overload */;
	__fastcall TBindingEventRec(System::Bindings::Outputs::TBindingEvalErrorEvent AEvalErrorEvent, System::Bindings::Outputs::TBindingAssigningValueEvent AAssigningValueEvent, System::Bindings::Outputs::TBindingAssignedValueEvent AAssignedValueEvent, System::Bindings::Outputs::TBindingLocationUpdatedEvent ALocationUpdatedEvent)/* overload */;
	TBindingEventRec() {}
};


class PASCALIMPLEMENTATION TBindings : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum DECLSPEC_DENUM TCreateOption : unsigned char { coNotifyOutput, coEvaluate };
	
	typedef System::Set<TCreateOption, TCreateOption::coNotifyOutput, TCreateOption::coEvaluate> TCreateOptions;
	
	
public:
	__classmethod System::Bindings::Notifiercontracts::_di_IBindingNotifier __fastcall CreateNotifier(System::TObject* const AObject, System::Bindings::Manager::TBindingManager* Manager = (System::Bindings::Manager::TBindingManager*)(0x0));
	__classmethod void __fastcall Notify(System::TObject* Sender, System::UnicodeString PropName = System::UnicodeString(), System::Bindings::Manager::TBindingManager* Manager = (System::Bindings::Manager::TBindingManager*)(0x0));
	__classmethod System::Bindings::Evalprotocol::_di_IScope __fastcall CreateMethodScope(const System::UnicodeString MethodName, System::Bindings::Evalprotocol::_di_IInvokable InvokableMethod)/* overload */;
	__classmethod System::Bindings::Evalprotocol::_di_IScope __fastcall CreateMethodScope(System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::Bindings::Evalprotocol::_di_IInvokable> > AMethod)/* overload */;
	__classmethod System::Bindings::Evalprotocol::_di_IScope __fastcall CreateAssociationScope(System::Bindings::Expression::TBindingAssociation *Assocs, const int Assocs_High);
	__classmethod System::Bindings::Expression::TBindingExpression* __fastcall CreateManagedBinding(const System::Bindings::Evalprotocol::_di_IScope *InputScopes, const int InputScopes_High, const System::UnicodeString BindExprStr, const System::Bindings::Evalprotocol::_di_IScope *OutputScopes, const int OutputScopes_High, const System::UnicodeString OutputExpr, const System::Bindings::Outputs::_di_IValueRefConverter OutputConverter, const TBindingEventRec &BindingEventRec, System::Bindings::Manager::TBindingManager* Manager = (System::Bindings::Manager::TBindingManager*)(0x0), TCreateOptions Options = (TCreateOptions() << TCreateOption::coNotifyOutput ))/* overload */;
	__classmethod System::Bindings::Expression::TBindingExpression* __fastcall CreateManagedBinding(const System::Bindings::Evalprotocol::_di_IScope *InputScopes, const int InputScopes_High, const System::UnicodeString BindExprStr, const System::Bindings::Evalprotocol::_di_IScope *OutputScopes, const int OutputScopes_High, const System::UnicodeString OutputExpr, const System::Bindings::Outputs::_di_IValueRefConverter OutputConverter, System::Bindings::Manager::TBindingManager* Manager = (System::Bindings::Manager::TBindingManager*)(0x0), TCreateOptions Options = (TCreateOptions() << TCreateOption::coNotifyOutput ))/* overload */;
	__classmethod System::Bindings::Expression::TBindingExpression* __fastcall CreateUnmanagedBinding(const System::Bindings::Evalprotocol::_di_IScope *InputScopes, const int InputScopes_High, const System::UnicodeString BindExprStr, const System::Bindings::Evalprotocol::_di_IScope *OutputScopes, const int OutputScopes_High, const System::UnicodeString OutputExpr, const System::Bindings::Outputs::_di_IValueRefConverter OutputConverter, const TBindingEventRec &BindingEventRec, TCreateOptions Options = (TCreateOptions() << TCreateOption::coNotifyOutput ))/* overload */;
	__classmethod System::Bindings::Expression::TBindingExpression* __fastcall CreateUnmanagedBinding(const System::Bindings::Evalprotocol::_di_IScope *InputScopes, const int InputScopes_High, const System::UnicodeString BindExprStr, const System::Bindings::Evalprotocol::_di_IScope *OutputScopes, const int OutputScopes_High, const System::UnicodeString OutputExpr, const System::Bindings::Outputs::_di_IValueRefConverter OutputConverter, TCreateOptions Options = TCreateOptions() )/* overload */;
	__classmethod System::Bindings::Expression::TBindingExpression* __fastcall CreateExpression(const System::Bindings::Evalprotocol::_di_IScope *InputScopes, const int InputScopes_High, const System::UnicodeString BindExprStr, const TBindingEventRec &BindingEventRec)/* overload */;
	__classmethod System::Bindings::Expression::TBindingExpression* __fastcall CreateExpression(const System::Bindings::Evalprotocol::_di_IScope *InputScopes, const int InputScopes_High, const System::UnicodeString BindExprStr)/* overload */;
	__classmethod void __fastcall RemoveBinding(System::Bindings::Expression::TBindingExpression* const Expression, System::Bindings::Manager::TBindingManager* Manager = (System::Bindings::Manager::TBindingManager*)(0x0))/* overload */;
public:
	/* TObject.Create */ inline __fastcall TBindings() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindings() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Helper */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_HELPER)
using namespace System::Bindings::Helper;
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
#endif	// System_Bindings_HelperHPP
