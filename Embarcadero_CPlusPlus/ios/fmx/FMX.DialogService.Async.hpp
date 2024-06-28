// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.DialogService.Async.pas' rev: 34.00 (iOS)

#ifndef Fmx_Dialogservice_AsyncHPP
#define Fmx_Dialogservice_AsyncHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Dialogs.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Dialogservice
{
namespace Async
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDialogServiceAsync;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDialogServiceAsync : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static Fmx::Platform::_di_IFMXDialogServiceAsync FDialogService;
	__classmethod Fmx::Platform::_di_IFMXDialogServiceAsync __fastcall DialogService();
	
public:
	__classmethod void __fastcall ShowMessage(const System::UnicodeString AMessage)/* overload */;
	__classmethod void __fastcall ShowMessage(const System::UnicodeString AMessage, const Fmx::Dialogs::_di_TInputCloseDialogProc ACloseDialogProc)/* overload */;
	__classmethod void __fastcall ShowMessage(const System::UnicodeString AMessage, const Fmx::Dialogs::TInputCloseDialogEvent ACloseDialogEvent, System::TObject* const AContext = (System::TObject*)(0x0))/* overload */;
	__classmethod void __fastcall MessageDialog(const System::UnicodeString AMessage, const System::Uitypes::TMsgDlgType ADialogType, const System::Uitypes::TMsgDlgButtons AButtons, const System::Uitypes::TMsgDlgBtn ADefaultButton, const System::Classes::THelpContext AHelpCtx)/* overload */;
	__classmethod void __fastcall MessageDialog(const System::UnicodeString AMessage, const System::Uitypes::TMsgDlgType ADialogType, const System::Uitypes::TMsgDlgButtons AButtons, const System::Uitypes::TMsgDlgBtn ADefaultButton, const System::Classes::THelpContext AHelpCtx, const Fmx::Dialogs::_di_TInputCloseDialogProc ACloseDialogProc)/* overload */;
	__classmethod void __fastcall MessageDialog(const System::UnicodeString AMessage, const System::Uitypes::TMsgDlgType ADialogType, const System::Uitypes::TMsgDlgButtons AButtons, const System::Uitypes::TMsgDlgBtn ADefaultButton, const System::Classes::THelpContext AHelpCtx, const Fmx::Dialogs::TInputCloseDialogEvent ACloseDialogEvent, System::TObject* const AContext = (System::TObject*)(0x0))/* overload */;
	__classmethod void __fastcall InputQuery(const System::UnicodeString ACaption, const System::UnicodeString *APrompts, const int APrompts_High, const System::UnicodeString *AValues, const int AValues_High, const Fmx::Dialogs::_di_TInputCloseQueryProc ACloseQueryProc)/* overload */;
	__classmethod void __fastcall InputQuery(const System::UnicodeString ACaption, const System::UnicodeString *APrompts, const int APrompts_High, const System::UnicodeString *AValues, const int AValues_High, const Fmx::Dialogs::TInputCloseQueryWithResultEvent ACloseQueryEvent, System::TObject* const AContext = (System::TObject*)(0x0))/* overload */;
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TDialogServiceAsync() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDialogServiceAsync() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Async */
}	/* namespace Dialogservice */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DIALOGSERVICE_ASYNC)
using namespace Fmx::Dialogservice::Async;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DIALOGSERVICE)
using namespace Fmx::Dialogservice;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Dialogservice_AsyncHPP
