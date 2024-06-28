// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBFilterDialog.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbfilterdialogHPP
#define Ibx_IbfilterdialogHPP

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
#include <Vcl.Dialogs.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Data.DB.hpp>
#include <IBX.IBCustomDataSet.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibfilterdialog
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBFieldInfo;
class DELPHICLASS TIBVariable;
class DELPHICLASS TfrmIBFilterDialog;
class DELPHICLASS TIBFilterDialog;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIBFilterMatchType : unsigned char { fdMatchExact, fdMatchStart, fdMatchEnd, fdMatchAny, fdMatchRange, fdMatchNone };

enum DECLSPEC_DENUM TIBOption : unsigned char { fdCaseSensitive, fdShowCaseSensitive, fdShowNonMatching };

typedef System::Set<TIBOption, TIBOption::fdCaseSensitive, TIBOption::fdShowNonMatching> TIBOptions;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIBFieldInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::UnicodeString FieldName;
	System::UnicodeString FieldOrigin;
	Data::Db::TFieldType FieldType;
	System::UnicodeString DisplayLabel;
	TIBFilterMatchType MatchType;
	System::UnicodeString FilterValue;
	System::UnicodeString StartingValue;
	System::UnicodeString EndingValue;
	bool CaseSensitive;
	bool NonMatching;
	void __fastcall Assign(TIBFieldInfo* o);
	System::UnicodeString __fastcall CreateSQL();
	void __fastcall SetVariables(Ibx::Ibcustomdataset::TIBCustomDataSet* d);
public:
	/* TObject.Create */ inline __fastcall TIBFieldInfo() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIBFieldInfo() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIBVariable : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::UnicodeString VariableName;
	System::Variant VariableValue;
	__fastcall TIBVariable(System::UnicodeString name, const System::Variant &value);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIBVariable() { }
	
};


class PASCALIMPLEMENTATION TfrmIBFilterDialog : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
public:
	TIBFieldInfo* operator[](int index) { return this->FilterItem[index]; }
	
__published:
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Comctrls::TPageControl* pgeFields;
	Vcl::Comctrls::TTabSheet* tabAll;
	Vcl::Comctrls::TTabSheet* tabSelected;
	Vcl::Stdctrls::TListBox* lstAllFields;
	Vcl::Stdctrls::TListBox* lstSelectedFields;
	Vcl::Comctrls::TPageControl* pgeCriteria;
	Vcl::Comctrls::TTabSheet* tabByValue;
	Vcl::Comctrls::TTabSheet* tabByRange;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* edtFieldValue;
	Vcl::Stdctrls::TButton* btnClearFieldValue;
	Vcl::Extctrls::TRadioGroup* grpSearchType;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TEdit* edtStartingRange;
	Vcl::Stdctrls::TEdit* edtEndingRange;
	Vcl::Stdctrls::TButton* btnClearStartingRange;
	Vcl::Stdctrls::TButton* btnClearEndingRange;
	Vcl::Buttons::TBitBtn* btnOk;
	Vcl::Buttons::TBitBtn* btnCancel;
	Vcl::Stdctrls::TButton* btnViewSummary;
	Vcl::Stdctrls::TButton* btnNewSearch;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TCheckBox* cbxCaseSensitive;
	Vcl::Stdctrls::TCheckBox* cbxNonMatching;
	void __fastcall RefreshClearButtons(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FieldsListBoxClick(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall pgeFieldsChanging(System::TObject* Sender, bool &AllowChange);
	void __fastcall btnNewSearchClick(System::TObject* Sender);
	void __fastcall btnViewSummaryClick(System::TObject* Sender);
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall btnCancelClick(System::TObject* Sender);
	void __fastcall btnOkClick(System::TObject* Sender);
	void __fastcall btnClearFieldValueClick(System::TObject* Sender);
	void __fastcall btnClearStartingRangeClick(System::TObject* Sender);
	void __fastcall btnClearEndingRangeClick(System::TObject* Sender);
	
private:
	System::Classes::TList* FFilterList;
	System::Classes::TList* FPreviousList;
	int LastIndex;
	void __fastcall SetCriteria();
	void __fastcall GetCriteria();
	void __fastcall ClearCriteria();
	TIBFieldInfo* __fastcall GetFilterItem(int index);
	
public:
	void __fastcall NewSQL();
	__property System::Classes::TList* FilterList = {read=FFilterList};
	__property TIBFieldInfo* FilterItem[int index] = {read=GetFilterItem/*, default*/};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TfrmIBFilterDialog(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmIBFilterDialog(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmIBFilterDialog() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmIBFilterDialog(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TIBFilterDialog : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TfrmIBFilterDialog* FDialog;
	System::Classes::TStrings* FOriginalSQL;
	System::Classes::TStrings* FModifiedSQL;
	Ibx::Ibcustomdataset::TIBCustomDataSet* FDataSet;
	TIBFilterMatchType FDefaultMatchType;
	TIBOptions FOptions;
	System::UnicodeString FCaption;
	System::Classes::TStringList* FFields;
	System::Classes::TList* FOriginalVariables;
	System::UnicodeString SQLProp;
	void __fastcall SetDataSet(Ibx::Ibcustomdataset::TIBCustomDataSet* const Value);
	void __fastcall SetOptions(const TIBOptions Value);
	void __fastcall SetCaption(const System::UnicodeString Value);
	void __fastcall SetDefaultMatchType(const TIBFilterMatchType Value);
	void __fastcall SetFields();
	void __fastcall SetFieldsList(System::Classes::TStringList* const Value);
	void __fastcall SetOriginalSQL(System::Classes::TStrings* const Value);
	void __fastcall RestoreSQL();
	void __fastcall SaveParamValues();
	
protected:
	virtual void __fastcall Loaded();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	__property System::Classes::TStrings* OriginalSQL = {read=FOriginalSQL, write=SetOriginalSQL};
	
public:
	__fastcall virtual TIBFilterDialog(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBFilterDialog();
	bool __fastcall Execute();
	void __fastcall ReBuildSQL();
	__property System::Classes::TStrings* ModifiedSQL = {read=FModifiedSQL};
	
__published:
	__property System::UnicodeString Caption = {read=FCaption, write=SetCaption};
	__property Ibx::Ibcustomdataset::TIBCustomDataSet* DataSet = {read=FDataSet, write=SetDataSet};
	__property TIBFilterMatchType DefaultMatchType = {read=FDefaultMatchType, write=SetDefaultMatchType, default=1};
	__property TIBOptions Options = {read=FOptions, write=SetOptions, default=6};
	__property System::Classes::TStringList* Fields = {read=FFields, write=SetFieldsList};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibfilterdialog */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBFILTERDIALOG)
using namespace Ibx::Ibfilterdialog;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbfilterdialogHPP
