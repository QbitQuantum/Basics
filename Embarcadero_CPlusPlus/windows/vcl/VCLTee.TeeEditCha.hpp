// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEditCha.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeeditchaHPP
#define Vcltee_TeeeditchaHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.CheckLst.hpp>
#include <System.Types.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeEdiSeri.hpp>
#include <VCLTee.TeeLisB.hpp>
#include <VCLTee.TeeChartGrid.hpp>
#include <VCLTee.TeePrevi.hpp>
#include <VCLTee.TeeNavigator.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeSourceEdit.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeeditcha
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TChartEditForm;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TChartEditorOption : unsigned char { ceAdd, ceDelete, ceChange, ceClone, ceDataSource, ceTitle, ceHelp, ceGroups, ceGroupAll, ceOrderSeries, ceAskDelete, ceEditData };

typedef void __fastcall (*TTeeOnCreateEditor)(System::Classes::TComponent* AOwner, Vcltee::Teeprocs::TCustomTeePanel* APanel, Vcl::Comctrls::TTabSheet* ATab, Vcl::Comctrls::TPageControl* APageControl);

enum DECLSPEC_DENUM TChartEditorTab : unsigned char { cetMain, cetGeneral, cetAxis, cetTitles, cetLegend, cetPanel, cetPaging, cetWalls, cet3D, cetSeriesGeneral, cetSeriesMarks, cetAllSeries, cetSeriesData, cetExport, cetExportNative, cetTools, cetAnimations, cetPrintPreview };

typedef System::Set<TChartEditorOption, TChartEditorOption::ceAdd, TChartEditorOption::ceEditData> TChartEditorOptions;

typedef System::Set<TChartEditorTab, TChartEditorTab::cetMain, TChartEditorTab::cetPrintPreview> TChartEditorHiddenTabs;

class PASCALIMPLEMENTATION TChartEditForm : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* MainPage;
	Vcl::Comctrls::TTabSheet* TabChart;
	Vcl::Comctrls::TPageControl* SubPage;
	Vcl::Comctrls::TTabSheet* TabSeriesList;
	Vcl::Comctrls::TTabSheet* TabAxis;
	Vcl::Comctrls::TTabSheet* TabGeneral;
	Vcl::Comctrls::TTabSheet* TabTitle;
	Vcl::Comctrls::TTabSheet* TabLegend;
	Vcl::Comctrls::TTabSheet* TabPanel;
	Vcl::Comctrls::TTabSheet* TabPaging;
	Vcl::Comctrls::TTabSheet* TabWalls;
	Vcl::Comctrls::TTabSheet* TabSeries;
	Vcl::Comctrls::TTabSheet* Tab3D;
	Vcl::Comctrls::TTabSheet* TabData;
	Vcl::Comctrls::TTabSheet* TabExport;
	Vcl::Extctrls::TPanel* PanBottom;
	Vcl::Stdctrls::TLabel* LabelWWW;
	Vcl::Comctrls::TTabSheet* TabTools;
	Vcl::Comctrls::TTabSheet* TabAnimations;
	Vcl::Comctrls::TTabSheet* TabPrint;
	Vcl::Extctrls::TPanel* PanRight;
	Vcl::Buttons::TSpeedButton* BMoveUP;
	Vcl::Buttons::TSpeedButton* BMoveDown;
	Vcl::Stdctrls::TButton* BAddSeries;
	Vcl::Stdctrls::TButton* BDeleteSeries;
	Vcl::Stdctrls::TButton* BRenameSeries;
	Vcl::Stdctrls::TButton* BCloneSeries;
	Vcl::Stdctrls::TButton* BChangeTypeSeries;
	Vcl::Extctrls::TPanel* PanTop;
	Vcl::Extctrls::TPanel* PanBot;
	Vcl::Extctrls::TPanel* PanLeft;
	Vcl::Extctrls::TPanel* PanClose;
	Vcl::Stdctrls::TButton* BClose;
	Vcltee::Teechartgrid::TChartGrid* ChartGrid1;
	Vcl::Extctrls::TPanel* Panel1;
	Vcltee::Teechartgrid::TChartGridNavigator* ChartGridNavigator1;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Buttons::TSpeedButton* SBGridText;
	Vcl::Buttons::TSpeedButton* SBGridCol;
	Vcl::Buttons::TSpeedButton* SBGrid3D;
	Vcl::Buttons::TSpeedButton* SBGridX;
	Vcl::Menus::TPopupMenu* PopupData;
	Vcl::Menus::TMenuItem* Deleterow1;
	Vcl::Checklst::TCheckListBox* Groups;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TPanel* PanelGroups;
	Vcl::Buttons::TSpeedButton* BAddGroup;
	Vcl::Buttons::TSpeedButton* BDeleteGroup;
	Vcl::Buttons::TSpeedButton* BRenameGroup;
	Vcl::Comctrls::TTreeView* Tree;
	Vcl::Extctrls::TSplitter* TreeSplitter;
	Vcl::Menus::TMenuItem* Insertrow1;
	Vcltee::Teelisb::TChartListBox* LBSeries;
	Vcl::Menus::TMenuItem* N1;
	Vcl::Menus::TMenuItem* EditColor1;
	Vcl::Menus::TMenuItem* DefaultColor1;
	Vcl::Menus::TMenuItem* Makenullpoint1;
	Vcl::Menus::TMenuItem* N2;
	Vcl::Menus::TMenuItem* extfont1;
	Vcl::Buttons::TSpeedButton* SBCopyData;
	Vcl::Menus::TPopupMenu* PopupSeries;
	Vcl::Menus::TMenuItem* ViewSeriesNames1;
	Vcl::Menus::TMenuItem* ViewSeriesGroups1;
	Vcl::Buttons::TSpeedButton* SpeedSeries;
	Vcl::Buttons::TSpeedButton* SBGridVisuals;
	Vcl::Menus::TPopupMenu* PopupListSeries;
	Vcl::Menus::TMenuItem* ShowAll1;
	Vcl::Menus::TMenuItem* HideAll1;
	Vcl::Menus::TMenuItem* N3;
	Vcl::Menus::TMenuItem* HideOther1;
	Vcl::Menus::TMenuItem* N4;
	Vcl::Menus::TMenuItem* SelectAll1;
	Vcl::Menus::TMenuItem* SelectNone1;
	Vcl::Extctrls::TSplitter* Splitter2;
	Vcl::Extctrls::TPanel* PanelFront;
	Vcl::Menus::TMenuItem* SBMergeSeries;
	Vcl::Menus::TPopupMenu* PopupTree;
	Vcl::Menus::TMenuItem* AddSubAxis1;
	Vcl::Menus::TMenuItem* DeleteSubAxis1;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall SubPageChange(System::TObject* Sender);
	void __fastcall BCloseClick(System::TObject* Sender);
	void __fastcall BMoveUPClick(System::TObject* Sender);
	void __fastcall BMoveDownClick(System::TObject* Sender);
	void __fastcall BAddSeriesClick(System::TObject* Sender);
	void __fastcall BDeleteSeriesClick(System::TObject* Sender);
	void __fastcall BRenameSeriesClick(System::TObject* Sender);
	void __fastcall BCloneSeriesClick(System::TObject* Sender);
	void __fastcall MainPageChange(System::TObject* Sender);
	void __fastcall FormCloseQuery(System::TObject* Sender, bool &CanClose);
	void __fastcall LBSeriesEditSeries(Vcltee::Teelisb::TChartListBox* Sender, int Index);
	void __fastcall LBSeriesOtherItemsChange(System::TObject* Sender);
	void __fastcall LBSeriesRefreshButtons(System::TObject* Sender);
	void __fastcall BChangeTypeSeriesClick(System::TObject* Sender);
	void __fastcall LabelWWWClick(System::TObject* Sender);
	void __fastcall ButtonHelpClick(System::TObject* Sender);
	void __fastcall MainPageChanging(System::TObject* Sender, bool &AllowChange);
	void __fastcall SubPageChanging(System::TObject* Sender, bool &AllowChange);
	void __fastcall SBGridTextClick(System::TObject* Sender);
	void __fastcall SBGridColClick(System::TObject* Sender);
	void __fastcall SBGrid3DClick(System::TObject* Sender);
	void __fastcall SBGridXClick(System::TObject* Sender);
	void __fastcall Deleterow1Click(System::TObject* Sender);
	void __fastcall GroupsClick(System::TObject* Sender);
	void __fastcall GroupsClickCheck(System::TObject* Sender);
	void __fastcall LBSeriesChangeActive(Vcltee::Teelisb::TChartListBox* Sender, Vcltee::Teengine::TCustomChartSeries* Series);
	void __fastcall GroupsDragOver(System::TObject* Sender, System::TObject* Source, int X, int Y, System::Uitypes::TDragState State, bool &Accept);
	void __fastcall GroupsDragDrop(System::TObject* Sender, System::TObject* Source, int X, int Y);
	void __fastcall BAddGroupClick(System::TObject* Sender);
	void __fastcall BRenameGroupClick(System::TObject* Sender);
	void __fastcall BDeleteGroupClick(System::TObject* Sender);
	void __fastcall TreeChange(System::TObject* Sender, Vcl::Comctrls::TTreeNode* Node);
	void __fastcall TreeEditing(System::TObject* Sender, Vcl::Comctrls::TTreeNode* Node, bool &AllowEdit);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall FormResize(System::TObject* Sender);
	void __fastcall Insertrow1Click(System::TObject* Sender);
	void __fastcall PopupDataPopup(System::TObject* Sender);
	void __fastcall EditColor1Click(System::TObject* Sender);
	void __fastcall DefaultColor1Click(System::TObject* Sender);
	void __fastcall Makenullpoint1Click(System::TObject* Sender);
	void __fastcall extfont1Click(System::TObject* Sender);
	void __fastcall SBCopyDataClick(System::TObject* Sender);
	void __fastcall ViewSeriesNames1Click(System::TObject* Sender);
	void __fastcall SpeedSeriesMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall ViewSeriesGroups1Click(System::TObject* Sender);
	void __fastcall LBSeriesRemovedSeries(Vcltee::Teelisb::TChartListBox* Sender, Vcltee::Teengine::TCustomChartSeries* Series);
	void __fastcall SBGridVisualsClick(System::TObject* Sender);
	void __fastcall HideOther1Click(System::TObject* Sender);
	void __fastcall PopupListSeriesPopup(System::TObject* Sender);
	void __fastcall ShowAll1Click(System::TObject* Sender);
	void __fastcall SelectAll1Click(System::TObject* Sender);
	void __fastcall SelectNone1Click(System::TObject* Sender);
	void __fastcall SBMergeSeriesClick(System::TObject* Sender);
	void __fastcall PopupTreePopup(System::TObject* Sender);
	void __fastcall DeleteSubAxis1Click(System::TObject* Sender);
	void __fastcall AddSubAxis1Click(System::TObject* Sender);
	
private:
	int OldWidth;
	Vcltee::Chart::TCustomChart* TheChart;
	Vcltee::Teeprevi::TChartPreview* FPreview;
	Vcltee::Teesourceedit::TBaseSourceEditor* SourceEditor;
	Vcl::Extctrls::TPanel* TreePanel;
	Vcl::Comctrls::TTreeNode* TreeNodeSeries;
	Vcl::Comctrls::TTreeNode* TreeNodeTools;
	Vcl::Comctrls::TTreeNode* TreeNodeAnimations;
	int FGalleryHeight;
	int FGalleryWidth;
	Vcl::Comctrls::TTreeNode* __fastcall AddSubAxis(Vcl::Comctrls::TTreeNode* const ANode, Vcltee::Teengine::TChartAxis* const Axis);
	void __fastcall AxisNotifyCustom(System::TObject* Sender);
	void __fastcall BroadCastShowEditor(Vcl::Comctrls::TTabSheet* const Tab);
	Vcltee::Teechartgrid::TChartGrid* __fastcall ChartGridOf(System::TObject* Sender);
	Vcltee::Teengine::TSeriesGroup* __fastcall CurrentGroup();
	int __fastcall DeltaGroup();
	void __fastcall EnableGroupButtons();
	void __fastcall FillGroups();
	void __fastcall FormSeriesEvent(Vcltee::Teeediseri::TFormTeeSeries* Sender, Vcltee::Teeprocs::TTeeEvent* Event);
	void __fastcall GridMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall InternalSetupFormSeries();
	void __fastcall PrepareTree();
	void __fastcall ReparentAxis();
	void __fastcall ReparentTitle();
	void __fastcall ReparentTools();
	void __fastcall ReparentAnimations();
	void __fastcall ResetParentTab(Vcl::Comctrls::TPageControl* const PageControl);
	void __fastcall SetChart(Vcltee::Chart::TCustomChart* const Value);
	Vcl::Comctrls::TTreeNode* __fastcall TreeNodeCurrentSeries();
	void __fastcall TreeSelectSeries(Vcltee::Teengine::TChartSeries* const Series);
	
protected:
	void __fastcall RefreshSeriesNodes();
	void __fastcall ShowHideGroups();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	HIDESBASE MESSAGE void __fastcall WMHelp(Winapi::Messages::TWMHelp &Message);
	void __fastcall SelectTreeNodeData(System::TObject* const AObject);
	
public:
	Vcltee::Teengine::TChartAxis* TheAxis;
	Vcltee::Chart::TChartTitle* TheTitle;
	Vcltee::Teengine::TTeeCustomTool* TheTool;
	Vcltee::Teengine::TTeeCustomAnimation* TheAnimation;
	Vcltee::Chart::TCustomChartWall* TheWall;
	Vcltee::Teengine::TChartSeries* TheSeries;
	Vcltee::Teengine::TChartSeries* TheEditSeries;
	int TheActivePageIndex;
	TChartEditorHiddenTabs TheHiddenTabs;
	TChartEditorOptions EditorOptions;
	bool IsDssGraph;
	Vcltee::Teeediseri::TFormTeeSeries* TheFormSeries;
	bool HighLightTabs;
	bool RememberPosition;
	bool RememberSize;
	void __fastcall CheckHelpFile();
	__classmethod bool __fastcall ReadDefaultFont(Vcl::Graphics::TFont* const AFont);
	void __fastcall SetTabSeries();
	__property Vcltee::Chart::TCustomChart* Chart = {read=TheChart, write=SetChart};
	__property int GalleryHeight = {read=FGalleryHeight, write=FGalleryHeight, nodefault};
	__property int GalleryWidth = {read=FGalleryWidth, write=FGalleryWidth, nodefault};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TChartEditForm(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TChartEditForm(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TChartEditForm() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TChartEditForm(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 teeEditMainPage = System::Int8(0x0);
static const System::Int8 teeEditGeneralPage = System::Int8(0x1);
static const System::Int8 teeEditAxisPage = System::Int8(0x2);
static const System::Int8 teeEditTitlePage = System::Int8(0x3);
static const System::Int8 teeEditLegendPage = System::Int8(0x4);
static const System::Int8 teeEditPanelPage = System::Int8(0x5);
static const System::Int8 teeEditPagingPage = System::Int8(0x6);
static const System::Int8 teeEditWallsPage = System::Int8(0x7);
static const System::Int8 teeEdit3DPage = System::Int8(0x8);
#define eoAll (System::Set<TChartEditorOption, TChartEditorOption::ceAdd, TChartEditorOption::ceEditData>() << TChartEditorOption::ceAdd << TChartEditorOption::ceDelete << TChartEditorOption::ceChange << TChartEditorOption::ceClone << TChartEditorOption::ceDataSource << TChartEditorOption::ceTitle << TChartEditorOption::ceHelp << TChartEditorOption::ceGroupAll << TChartEditorOption::ceOrderSeries << TChartEditorOption::ceAskDelete << TChartEditorOption::ceEditData )
extern DELPHI_PACKAGE System::Classes::TList* TeeOnShowEditor;
extern DELPHI_PACKAGE bool TeeSeriesNamesRuntime;
#define TeeMsg_RememberPosition L"RememberPosition"
#define TeeMsg_RememberSize L"RememberSize"
#define TeeMsg_TreeMode L"TreeMode"
#define TeeMsg_TreeWidth L"TreeWidth"
#define TeeMsg_DefaultEditorFont L"DefaultEditorFont"
#define TeeMsg_DefaultPalette L"DefaultPalette"
#define TeeMsg_DefaultTheme L"DefaultTheme"
#define TeeMsg_SeriesGroups L"SeriesGroups"
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetTeeChartHelpFile(void);
}	/* namespace Teeeditcha */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDITCHA)
using namespace Vcltee::Teeeditcha;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeeditchaHPP
