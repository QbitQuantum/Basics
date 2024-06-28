// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Grid.Style.pas' rev: 34.00 (Windows)

#ifndef Fmx_Grid_StyleHPP
#define Fmx_Grid_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Rtti.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Controls.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Types.hpp>
#include <FMX.ScrollBox.Style.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Header.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Grid.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FMX.Grid.Style"

namespace Fmx
{
namespace Grid
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGridHeaderItem;
class DELPHICLASS TStyledGrid;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TGridPart : unsigned char { Content, Columns, Header, HeaderItemSize, Selection, EditorModeChanging, EditorShowing, EditorKeyDown };

typedef System::Set<TGridPart, _DELPHI_SET_ENUMERATOR(TGridPart::Content), _DELPHI_SET_ENUMERATOR(TGridPart::EditorKeyDown)> TGridParts;

class PASCALIMPLEMENTATION TGridHeaderItem : public Fmx::Header::THeaderItem
{
	typedef Fmx::Header::THeaderItem inherited;
	
private:
	Fmx::Grid::TColumn* FColumn;
	TStyledGrid* FStyledGrid;
	bool FResize;
	Fmx::Grid::TColumn* __fastcall GetColumn();
	void __fastcall SetColumn(Fmx::Grid::TColumn* const Value);
	
protected:
	virtual void __fastcall Click();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	virtual void __fastcall Resize();
	virtual void __fastcall Resizing();
	virtual void __fastcall Resized();
	
public:
	__fastcall virtual TGridHeaderItem(System::Classes::TComponent* AOwner)/* overload */;
	__property Fmx::Grid::TColumn* Column = {read=FColumn, write=SetColumn};
	__property TStyledGrid* Grid = {read=FStyledGrid};
public:
	/* TCustomCornerButton.Destroy */ inline __fastcall virtual ~TGridHeaderItem() { }
	
private:
	void *__ICellControl;	// Fmx::Grid::ICellControl 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {67922698-EEEE-4326-B114-F11145A1D200}
	operator Fmx::Grid::_di_ICellControl()
	{
		Fmx::Grid::_di_ICellControl intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Grid::ICellControl*(void) { return (Fmx::Grid::ICellControl*)&__ICellControl; }
	#endif
	
};


class PASCALIMPLEMENTATION TStyledGrid : public Fmx::Scrollbox::Style::TStyledCustomScrollBox
{
	typedef Fmx::Scrollbox::Style::TStyledCustomScrollBox inherited;
	
	
private:
	struct DECLSPEC_DRECORD TColInfo
	{
	public:
		int Left;
		System::Word Width;
	};
	
	
	enum class DECLSPEC_DENUM TClickIndex : unsigned char { Single, Double };
	
	struct DECLSPEC_DRECORD TCellClickInfo
	{
	public:
		Fmx::Grid::TColumn* Column;
		int Row;
	};
	
	
	typedef System::DynamicArray<TColInfo> _TStyledGrid__1;
	
	
public:
	static const System::Int8 MinSize = System::Int8(0xa);
	
	static System::Uitypes::TAlphaColor AlternatingBackgroundColor;
	static System::Uitypes::TAlphaColor LineColor;
	static const System::Int8 DefaultRowHeight = System::Int8(0x15);
	
	static const System::Int8 DefaultThickness = System::Int8(0x1);
	
	#define TStyledGrid_DefaultFocusOpacity  (4.000000E-01)
	
	#define TStyledGrid_HitTestOptions (System::Set<Fmx::Grid::TGridOption, _DELPHI_SET_ENUMERATOR(Fmx::Grid::TGridOption::AlternatingRowBackground), _DELPHI_SET_ENUMERATOR(Fmx::Grid::TGridOption::AutoDisplacement)>() << Fmx::Grid::TGridOption::ColumnMove << Fmx::Grid::TGridOption::HeaderClick )
	
	
private:
	TGridParts FUpdating;
	bool FEditorMode;
	Fmx::Header::THeader* FHeader;
	Fmx::Controls::TControl* FFocus;
	Fmx::Controls::TControl* FFocusClone;
	Fmx::Controls::TControl* FSelectionClone;
	Fmx::Controls::TControl* FSelection;
	Fmx::Graphics::TBrush* FOddFill;
	Fmx::Graphics::TBrush* FLineFill;
	Fmx::Graphics::TBrush* FEditorLineFill;
	Fmx::Graphics::TBrush* FEditorBackground;
	System::Types::TSize FContentSize;
	bool FOldColLinesVisible;
	bool FOldHeaderVisible;
	int FTopRow;
	int FLeftColumn;
	int FBottomRow;
	int FRightColumn;
	int FDefaultRowHeight;
	System::Types::TRectF FWorkRect;
	System::Types::TRectF FVKRect;
	bool FMouseDown;
	System::Types::TPointF FMouseDownPos;
	bool FHasTouchScreen;
	Fmx::Controls::TStyledControl* FCellControl;
	Fmx::Types::TFmxObject* FInplaceEdit;
	int FOldRowCount;
	_TStyledGrid__1 FColInfo;
	float FBitmapsScale;
	float FBitmapsHeight;
	System::StaticArray<Fmx::Graphics::TBitmap*, 2> FStyledBitmaps;
	System::StaticArray<Fmx::Graphics::TBitmap*, 2> FBitmaps;
	System::StaticArray<TCellClickInfo, 2> FCellClickArray;
	MESSAGE void __fastcall MMContentChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMColumnChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMInvalidateCell(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TCoord> &Message);
	MESSAGE void __fastcall MMColumnMoved(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TColumnIndexes> &Message);
	MESSAGE void __fastcall MMSelChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMCellByPoint(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TPointInfo> &Message);
	MESSAGE void __fastcall PMGetDisplay_Cells(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TRectCoord> &Message);
	MESSAGE void __fastcall PMCreateCellObject(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TCellObjectInfo> &Message);
	MESSAGE void __fastcall MMGetRowHeight(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMInvalidateContentSize(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMCanEdit(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall PMSetTopLeft(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TCoord> &Message);
	MESSAGE void __fastcall PMScrollToSelect(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMCellRect(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TCellInfo> &Message);
	MESSAGE void __fastcall MMShowEditor(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMHideEditor(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMPostEditorValue(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMRefreshEditorValue(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMEditorMode(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMGetEditorValue(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Rtti::TValue> &Message);
	MESSAGE void __fastcall PMVKDisplacement(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Grid::TGridModel::TVKInfo> &Message);
	HIDESBASE MESSAGE void __fastcall PMSetContent(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TScrollContent*> &Message);
	HIDESBASE MESSAGE void __fastcall PMBeginPaintChildren(System::TDispatchMessage &Message);
	HIDESBASE MESSAGE void __fastcall PMEndPaintChildren(System::TDispatchMessage &Message);
	HIDESBASE Fmx::Grid::TGridModel* __fastcall GetModel();
	void __fastcall DoContentResize(System::TObject* Sender);
	void __fastcall DoGetClipRect(System::TObject* Sender, System::Types::TRectF &ContentBounds);
	void __fastcall DoContentPainting(System::TObject* Sender, Fmx::Graphics::TCanvas* Canvas, const System::Types::TRectF &ARect);
	void __fastcall DoRealignItem(System::TObject* Sender, int OldIndex, int NewIndex);
	void __fastcall DoDrawHeader(System::TObject* Sender, Fmx::Graphics::TCanvas* const Canvas, Fmx::Header::THeaderItem* const Item, const System::Types::TRectF &Bounds);
	int __fastcall GetColumnCount();
	int __fastcall GetRowCount();
	int __fastcall GetLeftColumn();
	int __fastcall GetTopRow();
	System::Types::TRectF __fastcall GetWorkRect();
	int __fastcall GetBottomRow();
	int __fastcall GetRightColumn();
	Fmx::Grid::TColumn* __fastcall GetColumns(const int Index);
	System::Types::TRectF __fastcall GetPaintRect();
	void __fastcall InternalDrawCells(Fmx::Graphics::TCanvas* const Canvas, const bool AFrontLayer, bool &NeedEditorBackground);
	void __fastcall ClickTimerProc(System::TObject* Sender);
	int __fastcall GetHeaderItemCount();
	TGridHeaderItem* __fastcall GetHeaderItem(const int Index);
	void __fastcall UpdateHeaderOffset();
	bool __fastcall EditingDone(const bool Accept);
	bool __fastcall PostEditorValue();
	Fmx::Graphics::TBitmap* __fastcall GetBitmaps(const bool Index);
	void __fastcall FreeStyledBitmaps();
	void __fastcall UpdateStyledBitmaps();
	void __fastcall UpdateHeaderOptions();
	void __fastcall PerformClick();
	void __fastcall StartSelectTimer(const int ACol, const int ARow, const System::Types::TPointF &AbsolutePoint, const bool DblTap);
	void __fastcall ClearCellClicks();
	
protected:
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual int __fastcall GetRowHeight();
	virtual int __fastcall GetColumnThickness();
	virtual int __fastcall GetRowThickness();
	System::Types::TRect __fastcall CellRect(const int ACol, const int ARow);
	virtual void __fastcall DoViewportPositionChange(const System::Types::TPointF &OldViewportPosition, const System::Types::TPointF &NewViewportPosition, const bool ContentSizeChanged);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual void __fastcall DialogKey(System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall PerformKeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall DoEnter();
	virtual void __fastcall DoExit();
	virtual void __fastcall CMGesture(Fmx::Types::TGestureEventInfo &EventInfo);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseWheel(System::Classes::TShiftState Shift, int WheelDelta, bool &Handled);
	virtual void __fastcall CellClick(Fmx::Grid::TColumn* const Column, const int Row);
	virtual void __fastcall CellDblClick(Fmx::Grid::TColumn* const Column, const int Row);
	HIDESBASE void __fastcall SetFocus();
	virtual Fmx::Controls::TStyledControl* __fastcall CreateDefaultCell();
	virtual Fmx::Types::TFmxObjectClass __fastcall GetCellClass(Fmx::Grid::TColumn* const Column);
	virtual Fmx::Types::TFmxObjectClass __fastcall GetEditorClass(Fmx::Grid::TColumn* const Column);
	virtual void __fastcall DoCreateCustomEditor(Fmx::Grid::TColumn* const Column, Fmx::Controls::TStyledControl* &Control);
	HIDESBASE void __fastcall InvalidateContentSize();
	void __fastcall UpdateContent();
	void __fastcall UpdateColumns();
	void __fastcall UpdateHeader();
	void __fastcall UpdateItemRect(const int ColumnIndex, const int ItemIndex);
	void __fastcall UpdateSelection();
	virtual bool __fastcall TouchEnabled();
	virtual System::Rtti::TValue __fastcall GetInplaceEditorValue(Fmx::Types::TFmxObject* const AInplaceEdit);
	
public:
	__fastcall virtual TStyledGrid(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TStyledGrid();
	virtual void __fastcall BeforeDestruction();
	virtual bool __fastcall CanEdit();
	virtual System::Types::TRectF __fastcall GetEditorRect();
	virtual bool __fastcall RefreshEditor(Fmx::Types::TFmxObject* const InplaceEdit, const bool RefreshAppearance, const bool RefreshValue);
	void __fastcall ShowEditor();
	void __fastcall HideEditor(const bool Accept);
	void __fastcall CellByPoint(const float X, const float Y, int &ACol, int &ARow);
	void __fastcall SetTopLeft(const int ACol, const int ARow);
	void __fastcall ScrollToSelectedCell();
	__property bool EditorMode = {read=FEditorMode, nodefault};
	__property bool HasTouchScreen = {read=FHasTouchScreen, nodefault};
	__property Fmx::Grid::TGridModel* Model = {read=GetModel};
	__property int RowHeight = {read=GetRowHeight, nodefault};
	__property int ColumnThickness = {read=GetColumnThickness, nodefault};
	__property int RowThickness = {read=GetRowThickness, nodefault};
	__property int ColumnCount = {read=GetColumnCount, nodefault};
	__property Fmx::Grid::TColumn* Columns[const int Index] = {read=GetColumns};
	__property int HeaderItemCount = {read=GetHeaderItemCount, nodefault};
	__property TGridHeaderItem* HeaderItem[const int Index] = {read=GetHeaderItem};
	__property int RowCount = {read=GetRowCount, nodefault};
	__property int TopRow = {read=GetTopRow, nodefault};
	__property int BottomRow = {read=GetBottomRow, nodefault};
	__property int LeftColumn = {read=GetLeftColumn, nodefault};
	__property int RightColumn = {read=GetRightColumn, nodefault};
	__property System::Types::TRectF WorkRect = {read=GetWorkRect};
	__property System::Types::TRectF PaintRect = {read=GetPaintRect};
	__property Fmx::Graphics::TBitmap* Bitmaps[const bool Index] = {read=GetBitmaps};
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledGrid(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Scrollbox::Style::TStyledCustomScrollBox(AOwner, AModel, AControl) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Grid */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GRID_STYLE)
using namespace Fmx::Grid::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GRID)
using namespace Fmx::Grid;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Grid_StyleHPP
