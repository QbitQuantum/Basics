// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Chart.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_ChartHPP
#define Fmxtee_Editor_ChartHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Classes.hpp>
#include <System.Variants.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.TabControl.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.TreeView.hpp>
#include <FMX.ListBox.hpp>
#include <FMXTee.Chart.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Procs.hpp>
#include <FMXTee.Editor.Gallery.hpp>
#include <FMX.Objects.hpp>
#include <FMXTee.Chart.ListBox.hpp>
#include <FMX.Menus.hpp>
#include <FMX.ExtCtrls.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Chart
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TChartEditForm;
//-- type declarations -------------------------------------------------------
_DECLARE_METACLASS(System::TMetaClass, TFormClass);

class PASCALIMPLEMENTATION TChartEditForm : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Treeview::TTreeView* Tree;
	Fmx::Stdctrls::TPanel* PanBottom;
	Fmx::Stdctrls::TButton* Button1;
	Fmx::Stdctrls::TPanel* Panel2;
	Fmx::Stdctrls::TPanel* PanelTabs;
	Fmx::Layouts::TLayout* TopLayout;
	Fmx::Stdctrls::TButton* BAdd;
	Fmx::Stdctrls::TButton* BDelete;
	Fmx::Stdctrls::TButton* BTitle;
	Fmx::Stdctrls::TButton* BClone;
	Fmx::Stdctrls::TButton* BChange;
	Fmx::Stdctrls::TSplitter* SplitterTree;
	Fmx::Stdctrls::TButton* SBUp;
	Fmx::Stdctrls::TButton* SBDown;
	Fmx::Treeview::TTreeViewItem* SeriesNode;
	Fmx::Treeview::TTreeViewItem* LegendNode;
	Fmx::Treeview::TTreeViewItem* PagingNode;
	Fmx::Treeview::TTreeViewItem* PanelNode;
	Fmx::Treeview::TTreeViewItem* GeneralNode;
	Fmx::Treeview::TTreeViewItem* TitlesNode;
	Fmx::Treeview::TTreeViewItem* WallsNode;
	Fmx::Treeview::TTreeViewItem* AxesNode;
	Fmx::Treeview::TTreeViewItem* ChartNode;
	Fmx::Treeview::TTreeViewItem* Node3D;
	Fmx::Treeview::TTreeViewItem* ExportNode;
	Fmx::Treeview::TTreeViewItem* PrintNode;
	Fmx::Treeview::TTreeViewItem* TitleNode;
	Fmx::Treeview::TTreeViewItem* SubTitleNode;
	Fmx::Treeview::TTreeViewItem* FooterNode;
	Fmx::Treeview::TTreeViewItem* SubFooterNode;
	Fmx::Treeview::TTreeViewItem* DataNode;
	Fmx::Menus::TPopupMenu* PopupData;
	Fmx::Menus::TMenuItem* MenuItem2;
	Fmx::Menus::TMenuItem* MenuItem3;
	Fmx::Menus::TMenuItem* MenuItem4;
	Fmx::Menus::TMenuItem* MenuItem5;
	Fmx::Stdctrls::TPanel* PanelGroups;
	Fmx::Listbox::TListBox* Groups;
	Fmx::Stdctrls::TSplitter* SplitterGroups;
	Fmx::Stdctrls::TPanel* PanelGroupButtons;
	Fmx::Stdctrls::TButton* BAddGroup;
	Fmx::Stdctrls::TButton* BRenameGroup;
	Fmx::Stdctrls::TButton* BDeleteGroup;
	Fmx::Stdctrls::TPanel* PanelList;
	Fmx::Menus::TPopupMenu* PopupListSeries;
	Fmx::Menus::TMenuItem* MenuItem6;
	Fmx::Menus::TMenuItem* MenuItem7;
	Fmx::Menus::TMenuItem* MenuItem8;
	Fmx::Menus::TMenuItem* MenuItem9;
	Fmx::Menus::TMenuItem* MenuItem10;
	Fmx::Menus::TMenuItem* MenuItem11;
	Fmx::Menus::TMenuItem* MenuItem12;
	Fmx::Objects::TText* Text1;
	Fmxtee::Chart::Listbox::TChartListBox* ListSeries;
	Fmx::Stdctrls::TButton* BEditSeries;
	Fmx::Layouts::TLayout* Layout1;
	Fmx::Stdctrls::TSpeedButton* SBView;
	Fmx::Objects::TText* Label1;
	Fmx::Stdctrls::TCheckBox* ViewGroups;
	Fmx::Stdctrls::TCheckBox* ViewNames;
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall BAddClick(System::TObject* Sender);
	void __fastcall ListSeriesChange(System::TObject* Sender);
	void __fastcall BDeleteClick(System::TObject* Sender);
	void __fastcall BCloneClick(System::TObject* Sender);
	void __fastcall TreeChange(System::TObject* Sender);
	void __fastcall ListSeriesDblClick(System::TObject* Sender);
	void __fastcall ListSeriesChangeCheck(System::TObject* Sender);
	void __fastcall SBUpClick(System::TObject* Sender);
	void __fastcall SBDownClick(System::TObject* Sender);
	void __fastcall BTitleClick(System::TObject* Sender);
	void __fastcall BChangeClick(System::TObject* Sender);
	void __fastcall MenuItem5Click(System::TObject* Sender);
	void __fastcall MenuItem2Click(System::TObject* Sender);
	void __fastcall MenuItem3Click(System::TObject* Sender);
	void __fastcall GroupsChangeCheck(System::TObject* Sender);
	void __fastcall GroupsChange(System::TObject* Sender);
	void __fastcall BAddGroupClick(System::TObject* Sender);
	void __fastcall BRenameGroupClick(System::TObject* Sender);
	void __fastcall BDeleteGroupClick(System::TObject* Sender);
	void __fastcall MenuItem6Click(System::TObject* Sender);
	void __fastcall MenuItem8Click(System::TObject* Sender);
	void __fastcall MenuItem9Click(System::TObject* Sender);
	void __fastcall MenuItem11Click(System::TObject* Sender);
	void __fastcall MenuItem12Click(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall Text1Click(System::TObject* Sender);
	void __fastcall FormCloseQuery(System::TObject* Sender, bool &CanClose);
	void __fastcall BEditSeriesClick(System::TObject* Sender);
	void __fastcall ViewGroupsChange(System::TObject* Sender);
	void __fastcall ViewNamesChange(System::TObject* Sender);
	void __fastcall SBViewClick(System::TObject* Sender);
	void __fastcall Label1Click(System::TObject* Sender);
	void __fastcall PanBottomResize(System::TObject* Sender);
	
private:
	Fmx::Forms::TForm* FLastForm;
	void __fastcall AddSeries(Fmxtee::Engine::TChartSeries* const ASeries);
	Fmxtee::Engine::TSeriesGroup* __fastcall CurrentGroup();
	void __fastcall EnableGroupButtons();
	void __fastcall ExchangeSeries(int Index1, int Index2);
	void __fastcall FillAxes();
	void __fastcall FillGroups();
	void __fastcall GroupsDragOver(System::TObject* Sender, const Fmx::Types::TDragObject &Data, const System::Types::TPointF &Point, Fmx::Types::TDragOperation &Operation);
	void __fastcall GroupsDragDrop(System::TObject* Sender, const Fmx::Types::TDragObject &Data, const System::Types::TPointF &Point);
	Fmxtee::Engine::TChartSeries* __fastcall SelectedSeries();
	Fmx::Treeview::TTreeViewItem* __fastcall TreeItemSeries(Fmxtee::Engine::TChartSeries* const ASeries);
	
protected:
	Fmxtee::Chart::TCustomChart* FChart;
	void __fastcall FillSeries();
	void __fastcall SetupChart(Fmxtee::Chart::TCustomChart* const AChart);
	void __fastcall ShowHideGroups();
	
public:
	bool RememberPosition;
	bool RememberSize;
	static TFormClass ImportEditor;
	static TFormClass ThemesEditor;
	__classmethod void __fastcall Edit(System::Classes::TComponent* const AOwner, Fmxtee::Chart::TCustomChart* const AChart)/* overload */;
	__classmethod void __fastcall Edit(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TChartSeries* const ASeries)/* overload */;
	__property Fmxtee::Chart::TCustomChart* Chart = {read=FChart, write=SetupChart};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TChartEditForm(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TChartEditForm(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TChartEditForm() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Chart */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_CHART)
using namespace Fmxtee::Editor::Chart;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR)
using namespace Fmxtee::Editor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_Editor_ChartHPP
