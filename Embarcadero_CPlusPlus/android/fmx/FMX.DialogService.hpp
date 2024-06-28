// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.DialogService.pas' rev: 34.00 (Android)

#ifndef Fmx_DialogserviceHPP
#define Fmx_DialogserviceHPP

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
namespace Dialogservice
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDialogService;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDialogService : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TPreferredMode : unsigned char { Platform, Async, Sync };
	
	
private:
	static TPreferredMode FPreferredMode;
	static bool FInSyncMode;
	static void __fastcall SetPreferredMode(const TPreferredMode PreferredMode);
	// __classmethod void __fastcall ClassCreate_();
	
public:
	__classmethod void __fastcall ShowMessage(const System::UnicodeString AMessage)/* overload */;
	__classmethod void __fastcall ShowMessage(const System::UnicodeString AMessage, const Fmx::Dialogs::_di_TInputCloseDialogProc ACloseDialogProc)/* overload */;
	__classmethod void __fastcall ShowMessage(const System::UnicodeString AMessage, const Fmx::Dialogs::TInputCloseDialogEvent ACloseDialogEvent, System::TObject* const AContext = (System::TObject*)(0x0))/* overload */;
	__classmethod void __fastcall MessageDialog(const System::UnicodeString AMessage, const System::Uitypes::TMsgDlgType ADialogType, const System::Uitypes::TMsgDlgButtons AButtons, const System::Uitypes::TMsgDlgBtn ADefaultButton, const System::Classes::THelpContext AHelpCtx, const Fmx::Dialogs::_di_TInputCloseDialogProc ACloseDialogProc)/* overload */;
	__classmethod void __fastcall MessageDialog(const System::UnicodeString AMessage, const System::Uitypes::TMsgDlgType ADialogType, const System::Uitypes::TMsgDlgButtons AButtons, const System::Uitypes::TMsgDlgBtn ADefaultButton, const System::Classes::THelpContext AHelpCtx, const Fmx::Dialogs::TInputCloseDialogEvent ACloseDialogEvent, System::TObject* const AContext = (System::TObject*)(0x0))/* overload */;
	__classmethod void __fastcall InputQuery(const System::UnicodeString ACaption, const System::UnicodeString *APrompts, const int APrompts_High, const System::UnicodeString *AValues, const int AValues_High, const Fmx::Dialogs::_di_TInputCloseQueryProc ACloseQueryProc)/* overload */;
	__classmethod void __fastcall InputQuery(const System::UnicodeString ACaption, const System::UnicodeString *APrompts, const int APrompts_High, const System::UnicodeString *AValues, const int AValues_High, const Fmx::Dialogs::TInputCloseQueryWithResultEvent ACloseQueryEvent, System::TObject* const AContext = (System::TObject*)(0x0))/* overload */;
	/* static */ __property TPreferredMode PreferredMode = {read=FPreferredMode, write=SetPreferredMode, nodefault};
	
private:
	// __classmethod void __fastcall Destroy_();
public:
	/* TObject.Create */ inline __fastcall TDialogService() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDialogService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dialogservice */
}	/* namespace Fmx */
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
#endif	// Fmx_DialogserviceHPP
