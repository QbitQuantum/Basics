// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GraphView.pas' rev: 34.00 (Windows)

#ifndef GraphviewHPP
#define GraphviewHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Math.hpp>
#include <System.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <BindingGraphResStrs.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Graphview
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGraphEntity;
class DELPHICLASS TGraphNode;
class DELPHICLASS TGraphEdge;
class DELPHICLASS EGraphError;
class DELPHICLASS TGraph;
class DELPHICLASS TGraphViewGraph;
class DELPHICLASS TGraphView;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
typedef System::TMetaClass* TGraphNodeClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TGraphNodeClass);
#endif /* _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TGraphEdgeClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TGraphEdgeClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGraphEntity : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TGraph* FOwner;
	System::Uitypes::TColor FColor;
	System::UnicodeString FCaption;
	System::Types::TRect FRect;
	System::Uitypes::TColor FTextColor;
	void __fastcall SetRectField(int &Field, int Value);
	
protected:
	virtual System::UnicodeString __fastcall GetCaption();
	virtual int __fastcall GetRect(const Vcl::Controls::TAlign Index);
	virtual System::Types::TRect __fastcall GetWholeRect();
	virtual void __fastcall SetCaption(const System::UnicodeString Value);
	virtual void __fastcall SetColor(const System::Uitypes::TColor Value);
	virtual void __fastcall SetRect(const Vcl::Controls::TAlign Index, int Value);
	virtual void __fastcall SetTextColor(const System::Uitypes::TColor Value);
	virtual void __fastcall SetWholeRect(const System::Types::TRect &Value);
	virtual void __fastcall Update();
	
public:
	__fastcall virtual TGraphEntity(TGraph* Owner);
	__property TGraph* Owner = {read=FOwner};
	__property System::Uitypes::TColor Color = {read=FColor, write=SetColor, nodefault};
	__property System::Uitypes::TColor TextColor = {read=FTextColor, write=SetTextColor, nodefault};
	__property System::UnicodeString Caption = {read=GetCaption, write=SetCaption};
	__property System::Types::TRect Rect = {read=GetWholeRect, write=SetWholeRect};
	__property int Left = {read=GetRect, write=SetRect, index=3, nodefault};
	__property int Top = {read=GetRect, write=SetRect, index=1, nodefault};
	__property int Right = {read=GetRect, write=SetRect, index=4, nodefault};
	__property int Bottom = {read=GetRect, write=SetRect, index=2, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TGraphEntity() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGraphNode : public TGraphEntity
{
	typedef TGraphEntity inherited;
	
private:
	int FIndex;
	System::UnicodeString FContent;
	bool FFitText;
	bool FKeepHeight;
	bool FKeepWidth;
	
protected:
	virtual System::UnicodeString __fastcall GetContent();
	virtual int __fastcall GetHeight();
	virtual int __fastcall GetWidth();
	virtual void __fastcall SetContent(const System::UnicodeString Value);
	virtual void __fastcall SetHeight(const int Value);
	virtual void __fastcall SetWidth(const int Value);
	virtual void __fastcall SetFitText(const bool Value);
	virtual void __fastcall SetCaption(const System::UnicodeString Value);
	virtual void __fastcall SetRect(const Vcl::Controls::TAlign Index, int Value);
	virtual void __fastcall UpdateFitText();
	
public:
	__property int Index = {read=FIndex, nodefault};
	__property int Width = {read=GetWidth, write=SetWidth, nodefault};
	__property int Height = {read=GetHeight, write=SetHeight, nodefault};
	__property System::UnicodeString Content = {read=GetContent, write=SetContent};
	__property bool KeepWidth = {read=FKeepWidth, write=FKeepWidth, nodefault};
	__property bool KeepHeight = {read=FKeepHeight, write=FKeepHeight, nodefault};
	__property bool FitText = {read=FFitText, write=SetFitText, nodefault};
public:
	/* TGraphEntity.Create */ inline __fastcall virtual TGraphNode(TGraph* Owner) : TGraphEntity(Owner) { }
	
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TGraphNode() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGraphEdge : public TGraphEntity
{
	typedef TGraphEntity inherited;
	
private:
	TGraphNode* FEndNode;
	TGraphNode* FStartNode;
	
public:
	__property TGraphNode* StartNode = {read=FStartNode};
	__property TGraphNode* EndNode = {read=FEndNode};
public:
	/* TGraphEntity.Create */ inline __fastcall virtual TGraphEdge(TGraph* Owner) : TGraphEntity(Owner) { }
	
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TGraphEdge() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EGraphError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EGraphError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EGraphError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EGraphError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EGraphError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EGraphError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EGraphError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EGraphError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EGraphError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EGraphError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EGraphError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EGraphError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EGraphError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EGraphError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGraph : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
	
public:
	__interface DELPHIINTERFACE TFindGraphNodeCallback;
	typedef System::DelphiInterface<TFindGraphNodeCallback> _di_TFindGraphNodeCallback;
	__interface TFindGraphNodeCallback  : public System::IInterface 
	{
		virtual bool __fastcall Invoke(TGraphNode* Node) = 0 ;
	};
	
	typedef System::Generics::Collections::TObjectList__1<TGraphEdge*>* TOutgoingEdges;
	
	
protected:
	typedef System::Generics::Collections::TObjectList__1<System::Generics::Collections::TObjectList__1<TGraphEdge*>*>* TEdgeData;
	
	typedef System::Generics::Collections::TObjectList__1<TGraphNode*>* TNodeData;
	
	
private:
	System::Generics::Collections::TObjectList__1<TGraphNode*>* FNodeData;
	System::Generics::Collections::TObjectList__1<System::Generics::Collections::TObjectList__1<TGraphEdge*>*>* FEdgeData;
	int FEdgeCount;
	TGraphNodeClass FNodeClass;
	TGraphEdgeClass FEdgeClass;
	int FUpdateCount;
	
protected:
	void __fastcall CheckIndex(int Index);
	void __fastcall CheckOwner(TGraphEntity* Entity);
	int __fastcall GetNodeCount();
	TGraphNode* __fastcall GetNodes(int Index);
	System::Generics::Collections::TObjectList__1<TGraphEdge*>* __fastcall GetEdges(int NodeIndex);
	virtual int __fastcall GetTextWidth(const System::UnicodeString Text);
	virtual int __fastcall GetTextHeight(const System::UnicodeString Text);
	virtual void __fastcall Update();
	__property int UpdateCount = {read=FUpdateCount, nodefault};
	__property System::Generics::Collections::TObjectList__1<TGraphNode*>* NodeData = {read=FNodeData};
	__property System::Generics::Collections::TObjectList__1<System::Generics::Collections::TObjectList__1<TGraphEdge*>*>* EdgeData = {read=FEdgeData};
	
public:
	__fastcall TGraph();
	__fastcall virtual ~TGraph();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	TGraphNode* __fastcall AddNode();
	void __fastcall DeleteNode(int Index);
	int __fastcall RemoveNode(TGraphNode* Node);
	TGraphEdge* __fastcall AddEdge(int StartIndex, int EndIndex);
	void __fastcall DeleteEdge(int StartIndex, int EndIndex);
	int __fastcall RemoveEdge(TGraphEdge* Edge);
	int __fastcall FindEdge(int StartIndex, int EndIndex, /* out */ TGraphEdge* &Edge);
	bool __fastcall FindNode(/* out */ TGraphNode* &Node, _di_TFindGraphNodeCallback Callback);
	void __fastcall Clear();
	void __fastcall ClearEdges();
	__property TGraphNode* Nodes[int Index] = {read=GetNodes};
	__property int NodeCount = {read=GetNodeCount, nodefault};
	__property System::Generics::Collections::TObjectList__1<TGraphEdge*>* Edges[int NodeIndex] = {read=GetEdges};
	__property int EdgeCount = {read=FEdgeCount, nodefault};
	__property TGraphNodeClass NodeClass = {read=FNodeClass, write=FNodeClass};
	__property TGraphEdgeClass EdgeClass = {read=FEdgeClass, write=FEdgeClass};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGraphViewGraph : public TGraph
{
	typedef TGraph inherited;
	
private:
	TGraphView* FGraphView;
	
protected:
	virtual int __fastcall GetTextWidth(const System::UnicodeString Text);
	virtual int __fastcall GetTextHeight(const System::UnicodeString Text);
	virtual void __fastcall Update();
	__property TGraphView* GraphView = {read=FGraphView};
	
public:
	__fastcall TGraphViewGraph(TGraphView* GraphView);
public:
	/* TGraph.Destroy */ inline __fastcall virtual ~TGraphViewGraph() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TGraphView : public Vcl::Controls::TCustomControl
{
	typedef Vcl::Controls::TCustomControl inherited;
	
public:
	static System::Types::TPoint CBulletSize;
	
private:
	TGraph* FGraph;
	System::Types::TPoint FBulletSize;
	TGraphNode* FDraggedNode;
	System::Uitypes::TColor FBulletColor;
	bool FNodeDragging;
	bool FDblClicked;
	void __fastcall SetBulletSize(const System::Types::TPoint &Value);
	void __fastcall SetBulletColor(const System::Uitypes::TColor Value);
	System::Types::TPoint __fastcall GetLineToNodeCross(const System::Types::TPoint &LineStart, const System::Types::TRect &ARect);
	
protected:
	System::Types::TRect __fastcall AddRects(const System::Types::TRect &R1, const System::Types::TRect &R2);
	int __fastcall PtXOnLine(const System::Types::TPoint &StartPt, const System::Types::TPoint &EndPt, int PtY);
	int __fastcall PtYOnLine(const System::Types::TPoint &StartPt, const System::Types::TPoint &EndPt, int PtX);
	int __fastcall LineLength(const System::Types::TPoint &StartPt, const System::Types::TPoint &EndPt);
	void __fastcall PaintNode(TGraphNode* Node);
	void __fastcall PaintNodes();
	void __fastcall PaintEdge(TGraphEdge* Edge);
	void __fastcall PaintEdges();
	virtual void __fastcall Paint();
	DYNAMIC void __fastcall DblClick();
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	
public:
	__fastcall virtual TGraphView(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TGraphView();
	TGraphNode* __fastcall GetNodeFromPoint(const System::Types::TPoint &Point);
	void __fastcall MoveNode(TGraphNode* Node, int X, int Y);
	__property TGraph* Graph = {read=FGraph};
	__property System::Types::TPoint BulletSize = {read=FBulletSize, write=SetBulletSize};
	__property System::Uitypes::TColor BulletColor = {read=FBulletColor, write=SetBulletColor, nodefault};
	__property TGraphNode* DraggedNode = {read=FDraggedNode};
	__property bool NodeDragging = {read=FNodeDragging, write=FNodeDragging, default=1};
	
__published:
	__property DoubleBuffered = {default=1};
	__property Color = {default=16777215};
	__property BevelKind = {default=3};
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
public:
	/* TWinControl.CreateParented */ inline __fastcall TGraphView(HWND ParentWindow) : Vcl::Controls::TCustomControl(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Graphview */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GRAPHVIEW)
using namespace Graphview;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// GraphviewHPP
