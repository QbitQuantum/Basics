// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.DialogHelper.pas' rev: 34.00 (iOS)

#ifndef Fmx_DialoghelperHPP
#define Fmx_DialoghelperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <FMX.Dialogs.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Dialoghelper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDialogHelper;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDialogHelper : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod void __fastcall ShowMessage(const System::UnicodeString AMessage, const Fmx::Dialogs::_di_TInputCloseDialogProc ACloseDialogProc, bool AModalAndSync)/* overload */;
	__classmethod void __fastcall ShowMessage(const System::UnicodeString AMessage, const Fmx::Dialogs::TInputCloseDialogEvent ACloseDialogEvent, System::TObject* const AContext, bool AModalAndSync)/* overload */;
	__classmethod void __fastcall MessageDialog(const System::UnicodeString AMessage, const System::Uitypes::TMsgDlgType ADialogType, const System::Uitypes::TMsgDlgButtons AButtons, const System::Uitypes::TMsgDlgBtn DefaultButton, const System::Classes::THelpContext AHelpCtx, const Fmx::Dialogs::_di_TInputCloseDialogProc ACloseDialogProc, bool AModalAndSync)/* overload */;
	__classmethod void __fastcall MessageDialog(const System::UnicodeString AMessage, const System::Uitypes::TMsgDlgType ADialogType, const System::Uitypes::TMsgDlgButtons AButtons, const System::Uitypes::TMsgDlgBtn DefaultButton, const System::Classes::THelpContext AHelpCtx, const Fmx::Dialogs::TInputCloseDialogEvent ACloseDialogEvent, System::TObject* const AContext, bool AModalAndSync)/* overload */;
	__classmethod void __fastcall InputQuery(const System::UnicodeString ACaption, const System::UnicodeString *APrompts, const int APrompts_High, const System::UnicodeString *ADefaultValues, const int ADefaultValues_High, Fmx::Dialogs::_di_TInputCloseQueryProc ACloseQueryProc, bool AModalAndSync)/* overload */;
	__classmethod void __fastcall InputQuery(const System::UnicodeString ACaption, const System::UnicodeString *APrompts, const int APrompts_High, const System::UnicodeString *ADefaultValues, const int ADefaultValues_High, const Fmx::Dialogs::TInputCloseQueryWithResultEvent ACloseDialogEvent, System::TObject* const AContext, bool AModalAndSync)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TDialogHelper() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDialogHelper() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dialoghelper */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DIALOGHELPER)
using namespace Fmx::Dialoghelper;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_DialoghelperHPP
