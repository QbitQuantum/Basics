// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GUITestRunner.pas' rev: 34.00 (Windows)

#ifndef GuitestrunnerHPP
#define GuitestrunnerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <TestFramework.hpp>
#include <Winapi.Windows.hpp>
#include <System.Math.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ActnList.hpp>
#include <System.Classes.hpp>
#include <System.IniFiles.hpp>
#include <Vcl.ToolWin.hpp>
#include <DUnitConsts.hpp>
#include <System.Actions.hpp>
#include <System.UITypes.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Guitestrunner
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGUITestRunner;
//-- type declarations -------------------------------------------------------
typedef bool __fastcall (__closure *TTestFunc)(Testframework::_di_ITest item);

class PASCALIMPLEMENTATION TGUITestRunner : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Controls::TImageList* StateImages;
	Vcl::Controls::TImageList* RunImages;
	Vcl::Actnlist::TActionList* DialogActions;
	Vcl::Actnlist::TAction* SelectAllAction;
	Vcl::Actnlist::TAction* DeselectAllAction;
	Vcl::Actnlist::TAction* SelectFailedAction;
	Vcl::Menus::TMainMenu* MainMenu;
	Vcl::Menus::TMenuItem* TestTreeMenu;
	Vcl::Menus::TMenuItem* SelectAllItem;
	Vcl::Menus::TMenuItem* DeselectAllItem;
	Vcl::Menus::TMenuItem* SelectFailedItem;
	Vcl::Menus::TMenuItem* FileMenu;
	Vcl::Actnlist::TAction* SaveConfigurationAction;
	Vcl::Actnlist::TAction* AutoSaveAction;
	Vcl::Menus::TMenuItem* SaveConfigurationItem;
	Vcl::Menus::TMenuItem* AutoSaveItem;
	Vcl::Actnlist::TAction* RestoreSavedAction;
	Vcl::Menus::TMenuItem* RestoreSavedConfigurationItem;
	Vcl::Menus::TMenuItem* ViewMenu;
	Vcl::Menus::TMenuItem* HideErrorBoxItem;
	Vcl::Extctrls::TPanel* BodyPanel;
	Vcl::Actnlist::TAction* ErrorBoxVisibleAction;
	Vcl::Extctrls::TPanel* TopPanel;
	Vcl::Extctrls::TPanel* TreePanel;
	Vcl::Comctrls::TTreeView* TestTree;
	Vcl::Extctrls::TPanel* ResultsPanel;
	Vcl::Extctrls::TPanel* ProgressPanel;
	Vcl::Comctrls::TListView* ResultsView;
	Vcl::Comctrls::TListView* FailureListView;
	Vcl::Extctrls::TPanel* ErrorBoxPanel;
	Vcl::Extctrls::TSplitter* ErrorBoxSplitter;
	Vcl::Extctrls::TSplitter* ResultsSplitter;
	Vcl::Menus::TMenuItem* AutoChangeFocusItem;
	Vcl::Extctrls::TPanel* TopProgressPanel;
	Vcl::Comctrls::TProgressBar* ProgressBar;
	Vcl::Extctrls::TPanel* pnlProgresslabel;
	Vcl::Extctrls::TPanel* ScorePanel;
	Vcl::Extctrls::TPanel* ScoreLabel;
	Vcl::Comctrls::TProgressBar* ScoreBar;
	Vcl::Menus::TPopupMenu* pmTestTree;
	Vcl::Menus::TMenuItem* pmiSelectAll;
	Vcl::Menus::TMenuItem* pmiDeselectAll;
	Vcl::Menus::TMenuItem* pmiSelectFailed;
	Vcl::Actnlist::TAction* HideTestNodesAction;
	Vcl::Menus::TMenuItem* CollapseLowestSuiteNodesItem;
	Vcl::Menus::TMenuItem* CollapseLowestSuiteNodes1;
	Vcl::Actnlist::TAction* HideTestNodesOnOpenAction;
	Vcl::Menus::TMenuItem* HideTestNodesItem;
	Vcl::Actnlist::TAction* ExpandAllNodesAction;
	Vcl::Menus::TMenuItem* TestTreeMenuSeparator;
	Vcl::Menus::TMenuItem* ExpandAllItem;
	Vcl::Menus::TMenuItem* TestTreeLocalMenuSeparator;
	Vcl::Menus::TMenuItem* ExpandAll2;
	Vcl::Stdctrls::TLabel* lblTestTree;
	Vcl::Actnlist::TAction* RunAction;
	Vcl::Actnlist::TAction* ExitAction;
	Vcl::Actnlist::TAction* BreakOnFailuresAction;
	Vcl::Menus::TMenuItem* BreakonFailuresItem;
	Vcl::Actnlist::TAction* ShowTestedNodeAction;
	Vcl::Menus::TMenuItem* SelectTestedNodeItem;
	Vcl::Menus::TPopupMenu* ErrorMessagePopup;
	Vcl::Menus::TMenuItem* CopyFailureMessage;
	Vcl::Actnlist::TAction* CopyMessageToClipboardAction;
	Vcl::Menus::TMenuItem* ActionsMenu;
	Vcl::Menus::TMenuItem* CopyMessagetoCllipboardItem;
	Vcl::Stdctrls::TLabel* LbProgress;
	Vcl::Actnlist::TAction* UseRegistryAction;
	Vcl::Menus::TMenuItem* UseRegistryItem;
	Vcl::Comctrls::TRichEdit* ErrorMessageRTF;
	Vcl::Actnlist::TAction* SelectCurrentAction;
	Vcl::Actnlist::TAction* DeselectCurrentAction;
	Vcl::Menus::TMenuItem* SelectCurrent1;
	Vcl::Menus::TMenuItem* DeselectCurrent1;
	Vcl::Controls::TImageList* ActionsImages;
	Vcl::Menus::TMenuItem* CloseItem;
	Vcl::Menus::TMenuItem* RunItem;
	Vcl::Actnlist::TAction* StopAction;
	Vcl::Menus::TMenuItem* StopActionItem;
	Vcl::Comctrls::TToolBar* ToolBar1;
	Vcl::Comctrls::TToolButton* SelectAllButton;
	Vcl::Comctrls::TToolButton* DeselectAllButton;
	Vcl::Comctrls::TToolButton* ToolButton1;
	Vcl::Comctrls::TToolButton* SelectFailedButton;
	Vcl::Comctrls::TToolButton* ToolButton2;
	Vcl::Comctrls::TToolButton* SelectCurrentButton;
	Vcl::Comctrls::TToolButton* DeselectCurrentButton;
	Vcl::Comctrls::TToolButton* ToolButton3;
	Vcl::Comctrls::TToolButton* ToolButton4;
	Vcl::Comctrls::TToolButton* ToolButton5;
	Vcl::Actnlist::TAction* Alt_R_RunAction;
	Vcl::Actnlist::TAction* Alt_S_StopAction;
	Vcl::Menus::TMenuItem* N1;
	Vcl::Menus::TMenuItem* DeselectCurrent2;
	Vcl::Menus::TMenuItem* SelectCurrent2;
	Vcl::Menus::TMenuItem* N2;
	Vcl::Actnlist::TAction* CopyProcnameToClipboardAction;
	Vcl::Menus::TMenuItem* N3;
	Vcl::Menus::TMenuItem* Copytestnametoclipboard1;
	Vcl::Menus::TMenuItem* N4;
	Vcl::Menus::TMenuItem* Copytestnametoclipboard2;
	Vcl::Actnlist::TAction* RunSelectedTestAction;
	Vcl::Menus::TMenuItem* N5;
	Vcl::Menus::TMenuItem* Runcurrenttest1;
	Vcl::Menus::TMenuItem* N6;
	Vcl::Menus::TMenuItem* Runcurrenttest2;
	Vcl::Menus::TMenuItem* RunSelectedTestItem;
	Vcl::Comctrls::TToolButton* RunSelectedTestButton;
	Vcl::Actnlist::TAction* GoToNextSelectedTestAction;
	Vcl::Actnlist::TAction* GoToPrevSelectedTestAction;
	Vcl::Menus::TMenuItem* N7;
	Vcl::Menus::TMenuItem* GoToNextSelectedNode1;
	Vcl::Menus::TMenuItem* GoToPreviousSelectedNode1;
	Vcl::Menus::TMenuItem* N8;
	Vcl::Menus::TMenuItem* GoToNextSelectedNode2;
	Vcl::Menus::TMenuItem* GoToPreviousSelectedNode2;
	Vcl::Menus::TMenuItem* FailIfNoChecksExecuted;
	Vcl::Actnlist::TAction* FailIfNoChecksExecutedAction;
	Vcl::Menus::TMenuItem* FailTestCaseIfMemoryLeaked;
	Vcl::Actnlist::TAction* FailTestCaseIfMemoryLeakedAction;
	Vcl::Menus::TPopupMenu* TestCaseProperty;
	Vcl::Menus::TMenuItem* TestCaseProperties;
	Vcl::Menus::TMenuItem* N10;
	Vcl::Menus::TMenuItem* FailNoCheckExecutedMenuItem;
	Vcl::Menus::TMenuItem* FailsOnMemoryLeakMenuItem;
	Vcl::Menus::TMenuItem* N11;
	Vcl::Menus::TMenuItem* TestCasePopup;
	Vcl::Menus::TMenuItem* FailsOnMemoryRecoveryMenuItem;
	Vcl::Menus::TMenuItem* AllowedLeakSizeMemuItem;
	Vcl::Menus::TMenuItem* ShowTestCaseswithRunTimeProperties;
	Vcl::Actnlist::TAction* ShowTestCasesWithRunTimePropertiesAction;
	Vcl::Menus::TMenuItem* N9;
	Vcl::Menus::TMenuItem* WarnOnFailTestOverride;
	Vcl::Actnlist::TAction* WarnOnFailTestOverrideAction;
	Vcl::Menus::TMenuItem* N12;
	Vcl::Actnlist::TAction* TestCasePropertiesAction;
	Vcl::Actnlist::TAction* PropertyPopUpAction;
	Vcl::Menus::TMenuItem* N13;
	Vcl::Menus::TMenuItem* Previous1;
	Vcl::Menus::TMenuItem* Next1;
	Vcl::Menus::TMenuItem* RunSelectedTest1;
	Vcl::Actnlist::TAction* RunSelectedTestAltAction;
	Vcl::Menus::TMenuItem* N14;
	Vcl::Menus::TMenuItem* ReportMemoryLeakTypeOnShutdown;
	Vcl::Menus::TMenuItem* IgnoreMemoryLeakInSetUpTearDown;
	Vcl::Actnlist::TAction* IgnoreMemoryLeakInSetUpTearDownAction;
	Vcl::Actnlist::TAction* ReportMemoryLeakTypeOnShutdownAction;
	Vcl::Menus::TMenuItem* TestCaseIgnoreSetUpTearDownLeaksMenuItem;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall TestTreeClick(System::TObject* Sender);
	void __fastcall FailureListViewSelectItem(System::TObject* Sender, Vcl::Comctrls::TListItem* Item, bool Selected);
	void __fastcall FailureListViewClick(System::TObject* Sender);
	void __fastcall TestTreeKeyPress(System::TObject* Sender, System::WideChar &Key);
	void __fastcall SelectAllActionExecute(System::TObject* Sender);
	void __fastcall DeselectAllActionExecute(System::TObject* Sender);
	void __fastcall SelectFailedActionExecute(System::TObject* Sender);
	void __fastcall SaveConfigurationActionExecute(System::TObject* Sender);
	void __fastcall RestoreSavedActionExecute(System::TObject* Sender);
	void __fastcall AutoSaveActionExecute(System::TObject* Sender);
	void __fastcall ErrorBoxVisibleActionExecute(System::TObject* Sender);
	void __fastcall ErrorBoxSplitterMoved(System::TObject* Sender);
	void __fastcall ErrorBoxPanelResize(System::TObject* Sender);
	void __fastcall HideTestNodesActionExecute(System::TObject* Sender);
	void __fastcall HideTestNodesOnOpenActionExecute(System::TObject* Sender);
	void __fastcall ExpandAllNodesActionExecute(System::TObject* Sender);
	void __fastcall RunActionExecute(System::TObject* Sender);
	void __fastcall ExitActionExecute(System::TObject* Sender);
	void __fastcall BreakOnFailuresActionExecute(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall ShowTestedNodeActionExecute(System::TObject* Sender);
	void __fastcall CopyMessageToClipboardActionExecute(System::TObject* Sender);
	void __fastcall UseRegistryActionExecute(System::TObject* Sender);
	void __fastcall RunActionUpdate(System::TObject* Sender);
	void __fastcall CopyMessageToClipboardActionUpdate(System::TObject* Sender);
	void __fastcall SelectCurrentActionExecute(System::TObject* Sender);
	void __fastcall DeselectCurrentActionExecute(System::TObject* Sender);
	void __fastcall StopActionExecute(System::TObject* Sender);
	void __fastcall StopActionUpdate(System::TObject* Sender);
	void __fastcall TestTreeChange(System::TObject* Sender, Vcl::Comctrls::TTreeNode* Node);
	void __fastcall CopyProcnameToClipboardActionExecute(System::TObject* Sender);
	void __fastcall CopyProcnameToClipboardActionUpdate(System::TObject* Sender);
	void __fastcall RunSelectedTestActionExecute(System::TObject* Sender);
	void __fastcall RunSelectedTestActionUpdate(System::TObject* Sender);
	void __fastcall TestTreeMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall GoToNextSelectedTestActionExecute(System::TObject* Sender);
	void __fastcall GoToPrevSelectedTestActionExecute(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FailIfNoChecksExecutedActionExecute(System::TObject* Sender);
	void __fastcall FailTestCaseIfMemoryLeakedActionExecute(System::TObject* Sender);
	void __fastcall ShowTestCasesWithRunTimePropertiesActionExecute(System::TObject* Sender);
	void __fastcall WarnOnFailTestOverrideActionExecute(System::TObject* Sender);
	void __fastcall TestCasePropertiesActionExecute(System::TObject* Sender);
	void __fastcall Previous1Click(System::TObject* Sender);
	void __fastcall Next1Click(System::TObject* Sender);
	void __fastcall TestCasePropertiesMeasureItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, int &Width, int &Height);
	void __fastcall TestCasePropertiesDrawItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected);
	void __fastcall FailNoCheckExecutedMenuItemDrawItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected);
	void __fastcall AllowedLeakSizeMemuItemDrawItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected);
	void __fastcall FailsOnMemoryRecoveryMenuItemDrawItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected);
	void __fastcall FailsOnMemoryLeakMenuItemDrawItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected);
	void __fastcall pmTestTreePopup(System::TObject* Sender);
	void __fastcall FailNoCheckExecutedMenuItemClick(System::TObject* Sender);
	void __fastcall AllowedLeakSizeMemuItemClick(System::TObject* Sender);
	void __fastcall FailsOnMemoryLeakMenuItemClick(System::TObject* Sender);
	void __fastcall FailsOnMemoryRecoveryMenuItemClick(System::TObject* Sender);
	void __fastcall RunSelectedTestAltActionExecute(System::TObject* Sender);
	void __fastcall Previous1DrawItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected);
	void __fastcall RunSelectedTest1DrawItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected);
	void __fastcall Next1DrawItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected);
	void __fastcall ReportMemoryLeakTypeOnShutdownActionExecute(System::TObject* Sender);
	void __fastcall IgnoreMemoryLeakInSetUpTearDownActionExecute(System::TObject* Sender);
	void __fastcall TestCaseIgnoreSetUpTearDownLeaksMenuItemClick(System::TObject* Sender);
	void __fastcall TestCaseIgnoreSetUpTearDownLeaksMenuItemDrawItem(System::TObject* Sender, Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected);
	
private:
	bool FNoCheckExecutedPtyOverridden;
	bool FMemLeakDetectedPtyOverridden;
	bool FIgnoreSetUpTearDownLeakPtyOverridden;
	int FPopupY;
	int FPopupX;
	void __fastcall ResetProgress();
	void __fastcall MenuLooksInactive(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected, System::UnicodeString ATitle, unsigned TitlePosn, bool PtyOveridesGUI);
	void __fastcall MenuLooksActive(Vcl::Graphics::TCanvas* ACanvas, const System::Types::TRect &ARect, bool Selected, System::UnicodeString ATitle, unsigned TitlePosn);
	System::UnicodeString __fastcall GetPropertyName(const System::UnicodeString Caption);
	
protected:
	Testframework::_di_ITest FSuite;
	Testframework::TTestResult* FTestResult;
	bool FRunning;
	System::Classes::TInterfaceList* FTests;
	System::Classes::TInterfaceList* FSelectedTests;
	__int64 FTotalTime;
	System::UnicodeString FRunTimeStr;
	System::UnicodeString FNoChecksStr;
	System::UnicodeString FMemLeakStr;
	System::UnicodeString FMemGainStr;
	System::UnicodeString FMemBytesStr;
	System::UnicodeString FIgnoreLeakStr;
	System::UnicodeString FBytes;
	int FErrorCount;
	int FFailureCount;
	int FStrMaxLen;
	int FValMaxLen;
	Vcl::Extctrls::TTimer* FUpdateTimer;
	bool FTimerExpired;
	int FTotalTestsCount;
	void __fastcall Setup();
	void __fastcall SetUpStateImages();
	void __fastcall SetSuite(Testframework::_di_ITest value);
	void __fastcall ClearResult();
	void __fastcall DisplayFailureMessage(Vcl::Comctrls::TListItem* Item);
	void __fastcall ClearFailureMessage();
	Vcl::Comctrls::TListItem* __fastcall AddFailureItem(Testframework::TTestFailure* failure);
	void __fastcall UpdateStatus(const bool fullUpdate);
	void __fastcall FillTestTree(Vcl::Comctrls::TTreeNode* RootNode, Testframework::_di_ITest ATest)/* overload */;
	void __fastcall FillTestTree(Testframework::_di_ITest ATest)/* overload */;
	void __fastcall UpdateNodeImage(Vcl::Comctrls::TTreeNode* node);
	void __fastcall UpdateNodeState(Vcl::Comctrls::TTreeNode* node);
	void __fastcall SetNodeState(Vcl::Comctrls::TTreeNode* node, bool enabled);
	void __fastcall SwitchNodeState(Vcl::Comctrls::TTreeNode* node);
	void __fastcall UpdateTestTreeState();
	void __fastcall MakeNodeVisible(Vcl::Comctrls::TTreeNode* node);
	void __fastcall SetTreeNodeImage(Vcl::Comctrls::TTreeNode* Node, int imgIndex);
	void __fastcall SelectNode(Vcl::Comctrls::TTreeNode* node);
	Testframework::_di_ITest __fastcall NodeToTest(Vcl::Comctrls::TTreeNode* node);
	Vcl::Comctrls::TTreeNode* __fastcall TestToNode(Testframework::_di_ITest test);
	Testframework::_di_ITest __fastcall SelectedTest();
	void __fastcall ListSelectedTests();
	bool __fastcall EnableTest(Testframework::_di_ITest test);
	bool __fastcall DisableTest(Testframework::_di_ITest test);
	void __fastcall ApplyToTests(Vcl::Comctrls::TTreeNode* root, const TTestFunc func);
	void __fastcall EnableUI(bool enable);
	void __fastcall RunTheTest(Testframework::_di_ITest aTest);
	virtual void __fastcall InitTree();
	System::UnicodeString __fastcall IniFileName();
	System::Inifiles::TCustomIniFile* __fastcall GetIniFile(const System::UnicodeString FileName);
	void __fastcall LoadRegistryAction();
	void __fastcall SaveRegistryAction();
	void __fastcall LoadFormPlacement();
	void __fastcall SaveFormPlacement();
	void __fastcall SaveConfiguration();
	void __fastcall LoadConfiguration();
	void __fastcall LoadSuiteConfiguration();
	void __fastcall AutoSaveConfiguration();
	bool __fastcall NodeIsGrandparent(Vcl::Comctrls::TTreeNode* ANode);
	void __fastcall CollapseNonGrandparentNodes(Vcl::Comctrls::TTreeNode* RootNode);
	void __fastcall ProcessClickOnStateIcon();
	void __fastcall ClearStatusMessage();
	void __fastcall CopyTestNametoClipboard(Vcl::Comctrls::TTreeNode* ANode);
	void __fastcall SetupCustomShortcuts();
	void __fastcall SetupGUINodes();
	bool __fastcall SelectNodeIfTestEnabled(Vcl::Comctrls::TTreeNode* ANode);
	void __fastcall OnUpdateTimer(System::TObject* Sender);
	
public:
	void __fastcall AddSuccess(Testframework::_di_ITest test);
	void __fastcall AddError(Testframework::TTestFailure* failure);
	void __fastcall AddFailure(Testframework::TTestFailure* failure);
	bool __fastcall ShouldRunTest(Testframework::_di_ITest test);
	virtual void __fastcall StartSuite(Testframework::_di_ITest suite);
	virtual void __fastcall EndSuite(Testframework::_di_ITest suite);
	virtual void __fastcall StartTest(Testframework::_di_ITest test);
	virtual void __fastcall EndTest(Testframework::_di_ITest test);
	void __fastcall TestingStarts();
	void __fastcall TestingEnds(Testframework::TTestResult* TestResult);
	void __fastcall Status(Testframework::_di_ITest test, const System::UnicodeString Msg);
	void __fastcall Warning(Testframework::_di_ITest test, const System::UnicodeString Msg);
	__property int ErrorCount = {read=FErrorCount, nodefault};
	__property int FailureCount = {read=FFailureCount, nodefault};
	__property Testframework::_di_ITest Suite = {read=FSuite, write=SetSuite};
	__property Testframework::TTestResult* TestResult = {read=FTestResult, write=FTestResult};
	__classmethod void __fastcall RunTest(Testframework::_di_ITest test);
	__classmethod void __fastcall RunRegisteredTests();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TGUITestRunner(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TGUITestRunner(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TGUITestRunner() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TGUITestRunner(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
private:
	void *__ITestListenerX;	// Testframework::ITestListenerX 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5C28B1BE-38B5-4D6F-AA96-A04E9302C317}
	operator Testframework::_di_ITestListenerX()
	{
		Testframework::_di_ITestListenerX intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Testframework::ITestListenerX*(void) { return (Testframework::ITestListenerX*)&__ITestListenerX; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {114185BC-B36B-4C68-BDAB-273DBD450F72}
	operator Testframework::_di_ITestListener()
	{
		Testframework::_di_ITestListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Testframework::ITestListener*(void) { return (Testframework::ITestListener*)&__ITestListenerX; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
#define cnConfigIniSection L"GUITestRunner Config"
static const int clOK = int(32768);
static const int clFAILURE = int(16711935);
static const int clERROR = int(255);
static const System::Int8 imgNONE = System::Int8(0x0);
static const System::Int8 imgRUNNING = System::Int8(0x1);
static const System::Int8 imgRUN = System::Int8(0x2);
static const System::Int8 imgHASPROPS = System::Int8(0x3);
static const System::Int8 imgFAILED = System::Int8(0x4);
static const System::Int8 imgERROR = System::Int8(0x5);
static const System::Int8 imgDISABLED = System::Int8(0x1);
static const System::Int8 imgPARENT_DISABLED = System::Int8(0x2);
static const System::Int8 imgENABLED = System::Int8(0x3);
extern DELPHI_PACKAGE void __fastcall RunTest(Testframework::_di_ITest test);
extern DELPHI_PACKAGE void __fastcall RunTestModeless(Testframework::_di_ITest test);
extern DELPHI_PACKAGE void __fastcall RunRegisteredTests(void);
extern DELPHI_PACKAGE void __fastcall RunRegisteredTestsModeless(void);
extern DELPHI_PACKAGE int __fastcall RunRegisteredTestsModelessUnattended(void);
}	/* namespace Guitestrunner */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GUITESTRUNNER)
using namespace Guitestrunner;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// GuitestrunnerHPP
