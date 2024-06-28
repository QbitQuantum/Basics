// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.ConnEdit.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_ConneditHPP
#define Firedac_Vclui_ConneditHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.IniFiles.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Dialogs.hpp>
#include <System.ImageList.hpp>
#include <System.Actions.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.Script.hpp>
#include <FireDAC.Comp.UI.hpp>
#include <FireDAC.Comp.ScriptCommands.hpp>
#include <FireDAC.VCLUI.OptsBase.hpp>
#include <FireDAC.VCLUI.Controls.hpp>
#include <FireDAC.VCLUI.Login.hpp>
#include <FireDAC.VCLUI.UpdateOptions.hpp>
#include <FireDAC.VCLUI.FormatOptions.hpp>
#include <FireDAC.VCLUI.FetchOptions.hpp>
#include <FireDAC.VCLUI.ResourceOptions.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Memo.hpp>
#include <FireDAC.VCLUI.Script.hpp>
#include <System.UITypes.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Vclui
{
namespace Connedit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsConnEdit;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsConnEdit : public Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase
{
	typedef Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase inherited;
	
__published:
	Vcl::Comctrls::TPageControl* pcMain;
	Vcl::Comctrls::TTabSheet* tsConnection;
	Vcl::Grids::TStringGrid* sgParams;
	Vcl::Stdctrls::TComboBox* cbParams;
	Vcl::Stdctrls::TEdit* edtParams;
	Vcl::Extctrls::TPanel* pnlTitle;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TComboBox* cbServerID;
	Vcl::Stdctrls::TComboBox* cbConnectionDefName;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Comctrls::TTabSheet* tsOptions;
	Firedac::Vclui::Controls::TFDGUIxFormsPanelTree* ptreeOptions;
	Firedac::Vclui::Formatoptions::TfrmFDGUIxFormsFormatOptions* frmFormatOptions;
	Firedac::Vclui::Fetchoptions::TfrmFDGUIxFormsFetchOptions* frmFetchOptions;
	Firedac::Vclui::Updateoptions::TfrmFDGUIxFormsUpdateOptions* frmUpdateOptions;
	Firedac::Vclui::Resourceoptions::TfrmFDGUIxFormsResourceOptions* frmResourceOptions;
	Vcl::Extctrls::TPanel* pnlConnection;
	Vcl::Extctrls::TPanel* pnlOptions;
	Vcl::Comctrls::TTabSheet* tsSQL;
	Vcl::Comctrls::TTabSheet* tsInfo;
	Vcl::Extctrls::TPanel* pnlInfo;
	Vcl::Stdctrls::TMemo* mmInfo;
	Vcl::Extctrls::TPanel* pnlSQL;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Stdctrls::TMemo* mmLog;
	Firedac::Comp::Script::TFDScript* scrEngine;
	Firedac::Comp::Ui::TFDGUIxScriptDialog* sdMain;
	Vcl::Actnlist::TActionList* ActionList1;
	Vcl::Actnlist::TAction* acNewScript;
	Vcl::Actnlist::TAction* acOpenScript;
	Vcl::Actnlist::TAction* acSaveScript;
	Vcl::Actnlist::TAction* acSaveScriptAs;
	Vcl::Actnlist::TAction* acSaveLog;
	Vcl::Actnlist::TAction* acExit;
	Vcl::Actnlist::TAction* acRun;
	Vcl::Actnlist::TAction* acRunByStep;
	Vcl::Actnlist::TAction* acSkipStep;
	Vcl::Actnlist::TAction* acContinueOnError;
	Vcl::Actnlist::TAction* acDropNonexistObj;
	Vcl::Actnlist::TAction* acShowMessages;
	Vcl::Actnlist::TAction* acHelp;
	Vcl::Actnlist::TAction* acAbout;
	Vcl::Controls::TImageList* ilMain;
	Vcl::Comctrls::TToolBar* ToolBar1;
	Vcl::Comctrls::TToolButton* tbtRun;
	Vcl::Comctrls::TToolButton* ToolButton1;
	Vcl::Comctrls::TToolButton* ToolButton3;
	Vcl::Stdctrls::TButton* btnDefaults;
	Vcl::Stdctrls::TButton* btnTest;
	Vcl::Stdctrls::TButton* btnWizard;
	Vcl::Stdctrls::TButton* btnWiki;
	Vcl::Dialogs::TOpenDialog* OpenDialog1;
	void __fastcall btnWizardClick(System::TObject* Sender);
	void __fastcall sgParamsSelectCell(System::TObject* Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall cbServerIDClick(System::TObject* Sender);
	void __fastcall EditorExit(System::TObject* Sender);
	void __fastcall sgParamsTopLeftChanged(System::TObject* Sender);
	void __fastcall EditorKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall sgParamsKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall sgParamsMouseUp(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall cbConnectionDefNameClick(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall sgParamsDrawCell(System::TObject* Sender, int ACol, int ARow, const System::Types::TRect &Rect, Vcl::Grids::TGridDrawState State);
	void __fastcall btnDefaultsClick(System::TObject* Sender);
	void __fastcall frmOptionsModified(System::TObject* Sender);
	void __fastcall cbParamsDblClick(System::TObject* Sender);
	void __fastcall FormResize(System::TObject* Sender);
	void __fastcall btnTestClick(System::TObject* Sender);
	void __fastcall pcMainChange(System::TObject* Sender);
	void __fastcall mmScriptKeyUp(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall mmScriptMouseUp(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall scrEngineBeforeExecute(System::TObject* Sender);
	void __fastcall scrEngineAfterExecute(System::TObject* Sender);
	void __fastcall scrEngineConsoleGet(Firedac::Comp::Script::TFDScript* AEngine, const System::UnicodeString APrompt, System::UnicodeString &AResult);
	void __fastcall scrEngineConsoleLockUpdate(Firedac::Comp::Script::TFDScript* AEngine, bool ALock);
	void __fastcall scrEngineConsolePut(Firedac::Comp::Script::TFDScript* AEngine, const System::UnicodeString AMessage, Firedac::Ui::Intf::TFDScriptOutputKind AKind);
	void __fastcall scrEnginePause(Firedac::Comp::Script::TFDScript* AEngine, const System::UnicodeString AText);
	void __fastcall mmLogDblClick(System::TObject* Sender);
	void __fastcall acRunUpdate(System::TObject* Sender);
	void __fastcall acRunExecute(System::TObject* Sender);
	void __fastcall acRunByStepUpdate(System::TObject* Sender);
	void __fastcall acRunByStepExecute(System::TObject* Sender);
	void __fastcall acSkipStepUpdate(System::TObject* Sender);
	void __fastcall acSkipStepExecute(System::TObject* Sender);
	void __fastcall btnWikiClick(System::TObject* Sender);
	void __fastcall bedtParamsRightButtonClick(System::TObject* Sender);
	
private:
	Firedac::Comp::Client::TFDCustomConnection* FConnection;
	Firedac::Comp::Client::TFDCustomConnection* FTempConnection;
	bool FModified;
	System::UnicodeString FDriverID;
	System::UnicodeString FConnectionDefName;
	Firedac::Stan::Intf::_di_IFDStanConnectionDef FConnectionDef;
	System::Classes::TStrings* FDefaults;
	System::Classes::TStrings* FResults;
	System::Classes::TStrings* FEdited;
	Firedac::Stan::Option::_di_IFDStanOptions FOptions;
	System::Classes::TNotifyEvent FOnModified;
	bool FLockResize;
	int FLastGridWidth;
	int FEditor;
	Vcl::Comctrls::TPageControl* __fastcall GetPageControl();
	void __fastcall GetDriverParams(const System::UnicodeString ADrvID, System::Classes::TStrings* AStrs);
	void __fastcall GetConnectionDefParams(const System::UnicodeString AConnectionDefName, System::Classes::TStrings* AStrs);
	void __fastcall OverrideBy(System::Classes::TStrings* AThis, System::Classes::TStrings* AByThat);
	void __fastcall FillParamValues(bool AAsIs);
	void __fastcall FillParamGrids(bool AResetPosition);
	void __fastcall AdjustEditor(Vcl::Controls::TWinControl* ACtrl, int ACol, int ARow);
	void __fastcall FillConnParams(System::Classes::TStrings* AParams);
	void __fastcall Modified();
	bool __fastcall IsDriverKnown(const System::UnicodeString ADrvID, /* out */ Firedac::Phys::Intf::_di_IFDPhysDriverMetadata &ADrvMeta);
	void __fastcall ResetConnectionDef();
	void __fastcall ResetOpts();
	int __fastcall GetGridWidth();
	Vcl::Controls::TWinControl* __fastcall GetEditor();
	Firedac::Comp::Client::TFDCustomConnection* __fastcall GetTempConnection();
	Firedac::Comp::Client::TFDCustomConnection* __fastcall GetTestConnection();
	void __fastcall ReleaseTempConnection();
	void __fastcall SetConnectionParams(Firedac::Comp::Client::TFDCustomConnection* AConnection);
	
protected:
	virtual void __fastcall LoadFormState(System::Inifiles::TCustomIniFile* AIni);
	virtual void __fastcall SaveFormState(System::Inifiles::TCustomIniFile* AIni);
	
public:
	Firedac::Vclui::Memo::TFDGUIxFormsMemo* mmScript;
	Vcl::Extctrls::TButtonedEdit* bedtParams;
	__classmethod bool __fastcall Execute(Firedac::Comp::Client::TFDCustomConnection* AConn, const System::UnicodeString ACaption, TfrmFDGUIxFormsConnEdit* const ACustomFrm = (TfrmFDGUIxFormsConnEdit*)(0x0))/* overload */;
	__classmethod bool __fastcall Execute(System::UnicodeString &AConnStr, const System::UnicodeString ACaption, TfrmFDGUIxFormsConnEdit* const ACustomFrm = (TfrmFDGUIxFormsConnEdit*)(0x0))/* overload */;
	__classmethod bool __fastcall Execute(Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnDef, const System::UnicodeString ACaption, TfrmFDGUIxFormsConnEdit* const ACustomFrm = (TfrmFDGUIxFormsConnEdit*)(0x0))/* overload */;
	__fastcall TfrmFDGUIxFormsConnEdit();
	void __fastcall LoadData(Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef);
	void __fastcall PostChanges();
	void __fastcall SaveData();
	void __fastcall ResetState(bool AClear);
	void __fastcall ResetData();
	void __fastcall ResetPage();
	void __fastcall TestConnection();
	void __fastcall FillConnectionInfo(Firedac::Comp::Client::TFDCustomConnection* AConnection, bool ATryToConnect);
	void __fastcall SetReadOnly(bool AValue);
	__property bool LockResize = {read=FLockResize, write=FLockResize, nodefault};
	__property Vcl::Comctrls::TPageControl* PageControl = {read=GetPageControl};
	__property System::Classes::TNotifyEvent OnModified = {read=FOnModified, write=FOnModified};
public:
	/* TfrmFDGUIxFormsOptsBase.Create */ inline __fastcall virtual TfrmFDGUIxFormsConnEdit(System::Classes::TComponent* AOwner) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner) { }
	
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFormsConnEdit(System::Classes::TComponent* AOwner, int Dummy) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsConnEdit() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsConnEdit(HWND ParentWindow) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TfrmFDGUIxFormsConnEdit* frmFDGUIxFormsConnEdit;
}	/* namespace Connedit */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_CONNEDIT)
using namespace Firedac::Vclui::Connedit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI)
using namespace Firedac::Vclui;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Vclui_ConneditHPP
