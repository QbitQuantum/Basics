// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'BindingGraphViewNodes.pas' rev: 34.00 (Windows)

#ifndef BindinggraphviewnodesHPP
#define BindinggraphviewnodesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Rtti.hpp>
#include <System.Bindings.Expression.hpp>
#include <GraphView.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Bindinggraphviewnodes
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGraphNodeValue;
class DELPHICLASS TGraphNodeExpr;
class DELPHICLASS TGraphNodeProp;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGraphNodeValue : public Graphview::TGraphNode
{
	typedef Graphview::TGraphNode inherited;
	
private:
	System::DelphiInterface<System::Sysutils::TFunc__2<System::Rtti::TValue,System::UnicodeString> > FValueToStringCallback;
	bool FValueAsContent;
	void __fastcall SetValueAsContent(const bool Value);
	
protected:
	virtual System::UnicodeString __fastcall GetContent();
	virtual System::UnicodeString __fastcall GetValueString();
	
public:
	__property bool ValueAsContent = {read=FValueAsContent, write=SetValueAsContent, nodefault};
	__property System::DelphiInterface<System::Sysutils::TFunc__2<System::Rtti::TValue,System::UnicodeString> > ValueToStringCallback = {read=FValueToStringCallback, write=FValueToStringCallback};
public:
	/* TGraphEntity.Create */ inline __fastcall virtual TGraphNodeValue(Graphview::TGraph* Owner) : Graphview::TGraphNode(Owner) { }
	
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TGraphNodeValue() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGraphNodeExpr : public TGraphNodeValue
{
	typedef TGraphNodeValue inherited;
	
private:
	System::Bindings::Expression::TBindingExpression* FExpression;
	void __fastcall SetExpression(System::Bindings::Expression::TBindingExpression* const Value);
	
protected:
	virtual System::UnicodeString __fastcall GetValueString();
	
public:
	__fastcall virtual TGraphNodeExpr(Graphview::TGraph* Owner);
	__property System::Bindings::Expression::TBindingExpression* Expression = {read=FExpression, write=SetExpression};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TGraphNodeExpr() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGraphNodeProp : public TGraphNodeValue
{
	typedef TGraphNodeValue inherited;
	
private:
	System::Rtti::TRttiContext FRttiCtx;
	System::Rtti::TRttiProperty* FPropertyInfo;
	System::TObject* FObj;
	System::UnicodeString FPropertyName;
	void __fastcall SetObj(System::TObject* const Value);
	void __fastcall SetPropertyName(const System::UnicodeString Value);
	
protected:
	virtual System::UnicodeString __fastcall GetValueString();
	void __fastcall UpdateData();
	
public:
	__fastcall virtual TGraphNodeProp(Graphview::TGraph* AOwner);
	__property System::TObject* Obj = {read=FObj, write=SetObj};
	__property System::UnicodeString PropertyName = {read=FPropertyName, write=SetPropertyName};
	__property System::Rtti::TRttiProperty* PropertyInfo = {read=FPropertyInfo};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TGraphNodeProp() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Bindinggraphviewnodes */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_BINDINGGRAPHVIEWNODES)
using namespace Bindinggraphviewnodes;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// BindinggraphviewnodesHPP
