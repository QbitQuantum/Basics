// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.QEdit.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_QeditHPP
#define Firedac_Vclui_QeditHPP

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
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.DBGrids.hpp>
#include <Data.DB.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ImgList.hpp>
#include <System.IniFiles.hpp>
#include <FireDAC.VCLUI.OptsBase.hpp>
#include <FireDAC.VCLUI.Controls.hpp>
#include <FireDAC.VCLUI.ResourceOptions.hpp>
#include <FireDAC.VCLUI.UpdateOptions.hpp>
#include <FireDAC.VCLUI.FormatOptions.hpp>
#include <FireDAC.VCLUI.FetchOptions.hpp>
#include <FireDAC.VCLUI.Memo.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.DApt.hpp>
#include <System.Actions.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Vclui
{
namespace Qedit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsQEdit;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsQEdit : public Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase
{
	typedef Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase inherited;
	
__published:
	Vcl::Comctrls::TPageControl* pcMain;
	Vcl::Comctrls::TPageControl* pcResult;
	Vcl::Comctrls::TTabSheet* tsSQL;
	Vcl::Comctrls::TTabSheet* tsAdvOptions;
	Firedac::Vclui::Controls::TFDGUIxFormsPanelTree* ptAdvOptions;
	Firedac::Vclui::Fetchoptions::TfrmFDGUIxFormsFetchOptions* frmFetchOptions;
	Firedac::Vclui::Formatoptions::TfrmFDGUIxFormsFormatOptions* frmFormatOptions;
	Firedac::Vclui::Updateoptions::TfrmFDGUIxFormsUpdateOptions* frmUpdateOptions;
	Firedac::Vclui::Resourceoptions::TfrmFDGUIxFormsResourceOptions* frmResourceOptions;
	Data::Db::TDataSource* DataSource1;
	Vcl::Comctrls::TTabSheet* tsRecordSet;
	Vcl::Comctrls::TTabSheet* tsStructure;
	Vcl::Dbgrids::TDBGrid* DBGrid1;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Comctrls::TTabSheet* tsMessages;
	Vcl::Comctrls::TListView* lvStructure;
	Vcl::Stdctrls::TMemo* mmMessages;
	Vcl::Comctrls::TTabSheet* tsParameters;
	Vcl::Stdctrls::TListBox* lbParams;
	Vcl::Extctrls::TPanel* Panel19;
	Vcl::Comctrls::TTabSheet* tsMacros;
	Firedac::Comp::Client::TFDQuery* FQuery;
	Vcl::Actnlist::TActionList* alActions;
	Vcl::Controls::TImageList* ilImages;
	Vcl::Stdctrls::TListBox* lbMacros;
	Vcl::Extctrls::TPanel* pnlRight;
	Vcl::Extctrls::TPanel* Panel16;
	Vcl::Stdctrls::TButton* btnExecute;
	Vcl::Stdctrls::TButton* btnNextRecordSet;
	Vcl::Stdctrls::TButton* btnQBuilder;
	Vcl::Actnlist::TAction* acNextRS;
	Vcl::Actnlist::TAction* acQueryBuilder;
	Vcl::Actnlist::TAction* acExecute;
	Vcl::Stdctrls::TButton* BitBtn1;
	Vcl::Actnlist::TAction* acUpdateSQLEditor;
	Vcl::Actnlist::TAction* acCodeEditor;
	Vcl::Extctrls::TBevel* Bevel5;
	Vcl::Extctrls::TBevel* Bevel7;
	Vcl::Extctrls::TPanel* pnlResult;
	Vcl::Stdctrls::TCheckBox* cbRollback;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TComboBox* cbParamType;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* edtValue;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TComboBox* cbDataType;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TEdit* edtDataSize;
	Vcl::Extctrls::TBevel* Bevel1;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TComboBox* cbArrayType;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Stdctrls::TEdit* edtArraySize;
	Vcl::Stdctrls::TLabel* Label7;
	Vcl::Stdctrls::TEdit* edtPosition;
	Vcl::Extctrls::TBevel* Bevel4;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Extctrls::TBevel* Bevel9;
	Vcl::Stdctrls::TLabel* Label10;
	Vcl::Stdctrls::TLabel* Label11;
	Vcl::Stdctrls::TComboBox* cbMacroType;
	Vcl::Stdctrls::TEdit* edtMacroValue;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall mmSQLKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall lbParamsClick(System::TObject* Sender);
	void __fastcall lbMacrosClick(System::TObject* Sender);
	void __fastcall mmSQLChange(System::TObject* Sender);
	void __fastcall acExecuteExec(System::TObject* Sender);
	void __fastcall acNextRSExecute(System::TObject* Sender);
	void __fastcall acNextRSUpdate(System::TObject* Sender);
	void __fastcall acQueryBuilderExecute(System::TObject* Sender);
	void __fastcall acExecuteUpdate(System::TObject* Sender);
	void __fastcall frmOptionsModified(System::TObject* Sender);
	void __fastcall acUpdateSQLEditorUpdate(System::TObject* Sender);
	void __fastcall acUpdateSQLEditorExecute(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall pcMainChanging(System::TObject* Sender, bool &AllowChange);
	void __fastcall edtParametersExit(System::TObject* Sender);
	void __fastcall edtMacrosExit(System::TObject* Sender);
	
private:
	bool FDefinitionChanged;
	Firedac::Vclui::Memo::TFDGUIxFormsMemo* mmSQL;
	void __fastcall LoadParameters(int AIndex);
	void __fastcall LoadParameter(int AIndex);
	void __fastcall SaveParameter(int AIndex);
	void __fastcall LoadMacros(int AIndex);
	void __fastcall LoadMacro(int AIndex);
	void __fastcall SaveMacros(int AIndex);
	void __fastcall ExecQuery();
	void __fastcall NextRecordSet();
	void __fastcall FillMessages(Firedac::Stan::Error::EFDDBEngineException* AMessages);
	void __fastcall FillStructure(Firedac::Dats::TFDDatSTable* ATable);
	void __fastcall FillInfos();
	void __fastcall UpdateQuery();
	bool __fastcall ExecuteBase(Firedac::Comp::Client::TFDCustomQuery* AQuery, const System::UnicodeString ACaption);
	
protected:
	virtual void __fastcall LoadFormState(System::Inifiles::TCustomIniFile* AIni);
	virtual void __fastcall SaveFormState(System::Inifiles::TCustomIniFile* AIni);
	
public:
	__classmethod bool __fastcall Execute(Firedac::Comp::Client::TFDCustomQuery* AQuery, const System::UnicodeString ACaption);
public:
	/* TfrmFDGUIxFormsOptsBase.Create */ inline __fastcall virtual TfrmFDGUIxFormsQEdit(System::Classes::TComponent* AOwner) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner) { }
	
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFormsQEdit(System::Classes::TComponent* AOwner, int Dummy) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsQEdit() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsQEdit(HWND ParentWindow) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Qedit */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_QEDIT)
using namespace Firedac::Vclui::Qedit;
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
#endif	// Firedac_Vclui_QeditHPP
