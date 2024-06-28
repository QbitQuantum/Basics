// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.Expression.pas' rev: 34.00 (Windows)

#ifndef System_Bindings_ExpressionHPP
#define System_Bindings_ExpressionHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <System.Bindings.EvalSys.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Expression
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EBindingExpressionError;
struct TBindingAssociation;
struct TBidiAssociation;
class DELPHICLASS TBindingExpression;
class DELPHICLASS TBindExprDict;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBindingExpressionError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBindingExpressionError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBindingExpressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBindingExpressionError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBindingExpressionError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindingExpressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindingExpressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBindingExpressionError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBindingExpressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindingExpressionError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindingExpressionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindingExpressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindingExpressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBindingExpressionError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TBindingAssociation
{
public:
	System::TObject* RealObject;
	System::UnicodeString ScriptObject;
	__fastcall TBindingAssociation(System::TObject* ARealObject, const System::UnicodeString AScriptObject);
	TBindingAssociation() {}
};


struct DECLSPEC_DRECORD TBidiAssociation
{
public:
	System::_di_IInterface BidiInterface;
	System::UnicodeString BidiName;
	__fastcall TBidiAssociation(System::_di_IInterface ABidiInterface, const System::UnicodeString ABidiName);
	TBidiAssociation() {}
};


class PASCALIMPLEMENTATION TBindingExpression : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef System::Generics::Collections::TPair__2<System::TObject*,System::UnicodeString> TAssociationPair;
	
	typedef System::Generics::Collections::TDictionary__2<System::TObject*,System::UnicodeString>* TAssociations;
	
	
private:
	typedef System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> _TBindingExpression__1;
	
	
private:
	System::UnicodeString FSource;
	System::Generics::Collections::TDictionary__2<System::TObject*,System::UnicodeString>* FAssociations;
	System::Bindings::Outputs::TBindingOutput* FBindingOutput;
	System::Rtti::TValue FOutputValue;
	System::Bindings::Outputs::TBindingEvalErrorEvent FEvalErrorEvent;
	
protected:
	_TBindingExpression__1 FScopes;
	virtual bool __fastcall GetCompiled() = 0 ;
	virtual System::UnicodeString __fastcall GetSource();
	virtual void __fastcall SetSource(const System::UnicodeString Value);
	virtual System::Rtti::TValue __fastcall GetOutputValue();
	virtual void __fastcall SetOutputValue(const System::Rtti::TValue &Value);
	virtual void __fastcall SetOutputs(const System::DelphiInterface<System::Sysutils::TFunc__1<System::Bindings::Evalprotocol::_di_IValue> > ValueFunc);
	virtual void __fastcall Compile() = 0 /* overload */;
	virtual bool __fastcall GetIsManaged() = 0 ;
	System::Bindings::Outputs::TBindingAssigningValueEvent __fastcall GetAssigningValueEvent();
	void __fastcall SetAssigningValueEvent(System::Bindings::Outputs::TBindingAssigningValueEvent AssigningValueEvent);
	System::Bindings::Outputs::TBindingAssignedValueEvent __fastcall GetAssignedValueEvent();
	System::Bindings::Outputs::TBindingLocationUpdatedEvent __fastcall GetLocationUpdatedEvent();
	void __fastcall SetAssignedValueEvent(System::Bindings::Outputs::TBindingAssignedValueEvent AssignedValueEvent);
	void __fastcall SetEvalErrorEvent(System::Bindings::Outputs::TBindingEvalErrorEvent EvalErrorEvent);
	void __fastcall SetLocationUpdatedEvent(System::Bindings::Outputs::TBindingLocationUpdatedEvent ALocationUpdatedEvent);
	
public:
	__fastcall TBindingExpression();
	__fastcall virtual ~TBindingExpression();
	void __fastcall Compile(System::Classes::TComponent* const *Objects, const int Objects_High)/* overload */;
	void __fastcall Compile(const TBindingAssociation *Assocs, const int Assocs_High)/* overload */;
	void __fastcall Compile(const System::Bindings::Evalprotocol::_di_IScope AScope)/* overload */;
	void __fastcall Compile(const System::Bindings::Evalprotocol::_di_IScope *AScopes, const int AScopes_High)/* overload */;
	void __fastcall Compile(System::Classes::TComponent* const *Objects, const int Objects_High, const TBindingAssociation *Assocs, const int Assocs_High, const System::Bindings::Evalprotocol::_di_IScope *Scopes, const int Scopes_High)/* overload */;
	void __fastcall Recompile();
	virtual System::Bindings::Evalprotocol::_di_IValue __fastcall Evaluate() = 0 ;
	virtual void __fastcall EvaluateOutputs() = 0 ;
	virtual void __fastcall Clear();
	__property System::UnicodeString Source = {read=GetSource, write=SetSource};
	__property bool Compiled = {read=GetCompiled, nodefault};
	__property System::Bindings::Outputs::TBindingOutput* Outputs = {read=FBindingOutput};
	__property System::Rtti::TValue OutputValue = {read=GetOutputValue, write=SetOutputValue};
	__property System::Generics::Collections::TDictionary__2<System::TObject*,System::UnicodeString>* Associations = {read=FAssociations};
	__property bool IsManaged = {read=GetIsManaged, nodefault};
	__property System::Bindings::Outputs::TBindingAssigningValueEvent OnAssigningValueEvent = {read=GetAssigningValueEvent, write=SetAssigningValueEvent};
	__property System::Bindings::Outputs::TBindingEvalErrorEvent OnEvalErrorEvent = {read=FEvalErrorEvent, write=SetEvalErrorEvent};
	__property System::Bindings::Outputs::TBindingAssignedValueEvent OnAssignedValueEvent = {read=GetAssignedValueEvent, write=SetAssignedValueEvent};
	__property System::Bindings::Outputs::TBindingLocationUpdatedEvent OnLocationUpdatedEvent = {read=GetLocationUpdatedEvent, write=SetLocationUpdatedEvent};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindExprDict : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FName;
	bool FPersistBindings;
	System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBindingExpression*>* FExpressions;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TBindingExpression*>::TValueCollection* __fastcall GetValues();
	
public:
	void __fastcall Add(const System::UnicodeString ExpressionStr, TBindingExpression* BindingExpression);
	__property System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TBindingExpression*>* Expressions = {read=FExpressions};
	__property System::Generics::Collections::TDictionary__2<System::UnicodeString,TBindingExpression*>::TValueCollection* Values = {read=GetValues};
	__property System::UnicodeString Name = {read=FName};
	__property bool PersistBindings = {read=FPersistBindings, write=FPersistBindings, nodefault};
	__fastcall TBindExprDict(const System::UnicodeString GroupName);
	__fastcall virtual ~TBindExprDict();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TBidiAssociation __fastcall BidiAssociate(System::_di_IInterface BidiInterface, const System::UnicodeString BidiName);
extern DELPHI_PACKAGE TBindingAssociation __fastcall Associate(System::TObject* RealObject, const System::UnicodeString ScriptObject);
}	/* namespace Expression */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_EXPRESSION)
using namespace System::Bindings::Expression;
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
#endif	// System_Bindings_ExpressionHPP
