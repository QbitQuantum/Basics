// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SyncController.pas' rev: 34.00 (Windows)

#ifndef SynccontrollerHPP
#define SynccontrollerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Rtti.hpp>
#include <System.TypInfo.hpp>
#include <System.Bindings.Expression.hpp>
#include <System.Bindings.Graph.hpp>
#include <System.Bindings.Search.hpp>
#include <GraphView.hpp>
#include <BindingGraphViewNodes.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <System.Bindings.Outputs.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "SyncController"

namespace Synccontroller
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSyncController;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSyncController : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::DelphiInterface<System::Sysutils::TFunc__2<System::Rtti::TValue,System::UnicodeString> > FValueToStringCallback;
	System::DelphiInterface<System::Sysutils::TFunc__3<System::UnicodeString,System::TTypeKind,System::Rtti::TValue> > FStringToValueCallback;
	bool FWaiting;
	System::DelphiInterface<System::Sysutils::TFunc__2<System::UnicodeString,System::TObject*> > FGetObjectByNameProc;
	System::DelphiInterface<System::Sysutils::TFunc__2<System::TObject*,System::UnicodeString> > FGetObjectNameProc;
	System::DelphiInterface<System::Sysutils::TFunc__1<Graphview::TGraphView*> > FGetGraphViewProc;
	bool FWaitBetweenMarked;
	System::UnicodeString __fastcall GetObjectName(System::TObject* AObject);
	System::TObject* __fastcall GetObjectByName(System::UnicodeString AName);
	Graphview::TGraph* __fastcall GetGraph();
	Graphview::TGraphView* __fastcall GetGraphView();
	
protected:
	void __fastcall WaitLoop();
	
public:
	__fastcall TSyncController();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	bool __fastcall MatchGraphNode(Graphview::TGraphNode* Node, System::TObject* Obj, const System::UnicodeString PropertyName)/* overload */;
	bool __fastcall MatchGraphNode(Graphview::TGraphNode* Node, System::Bindings::Expression::TBindingExpression* Expr)/* overload */;
	void __fastcall SetRandGraphNodePos(Graphview::TGraphNode* Node);
	Graphview::TGraphNode* __fastcall PutGraphNode(System::TObject* Obj, const System::UnicodeString PropertyName)/* overload */;
	Graphview::TGraphNode* __fastcall PutGraphNode(System::Bindings::Expression::TBindingExpression* Expr)/* overload */;
	Graphview::TGraphEdge* __fastcall ConnectGraphNodes(Graphview::TGraphNode* FromNode, Graphview::TGraphNode* ToNode);
	Graphview::TGraphNode* __fastcall PutExpr(System::Bindings::Expression::TBindingExpression* Expr);
	void __fastcall NextStep();
	void __fastcall ObjectPropertyMarked(System::TObject* Obj, const System::UnicodeString PropertyName);
	void __fastcall ExpressionMarked(System::Bindings::Expression::TBindingExpression* Expr);
	__property System::DelphiInterface<System::Sysutils::TFunc__2<System::Rtti::TValue,System::UnicodeString> > ValueToStringCallback = {read=FValueToStringCallback};
	__property System::DelphiInterface<System::Sysutils::TFunc__3<System::UnicodeString,System::TTypeKind,System::Rtti::TValue> > StringToValueCallback = {read=FStringToValueCallback};
	__property bool Waiting = {read=FWaiting, nodefault};
	__property System::DelphiInterface<System::Sysutils::TFunc__2<System::TObject*,System::UnicodeString> > GetObjectNameProc = {read=FGetObjectNameProc, write=FGetObjectNameProc};
	__property System::DelphiInterface<System::Sysutils::TFunc__2<System::UnicodeString,System::TObject*> > GetObjectByNameProc = {read=FGetObjectByNameProc, write=FGetObjectByNameProc};
	__property System::DelphiInterface<System::Sysutils::TFunc__1<Graphview::TGraphView*> > GetGraphViewProc = {read=FGetGraphViewProc, write=FGetGraphViewProc};
	__property bool WaitBetweenMarked = {read=FWaitBetweenMarked, write=FWaitBetweenMarked, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSyncController() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#ifndef _WIN64
extern DELPHI_PACKAGE TSyncController* __fastcall Controller();
#else /* _WIN64 */
extern DELPHI_PACKAGE TSyncController* __fastcall Controller(void);
#endif /* _WIN64 */
}	/* namespace Synccontroller */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYNCCONTROLLER)
using namespace Synccontroller;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SynccontrollerHPP
