// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.DialogService.Sync.pas' rev: 34.00 (Windows)

#ifndef Fmx_Dialogservice_SyncHPP
#define Fmx_Dialogservice_SyncHPP

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
namespace Sync
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDialogServiceSync;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDialogServiceSync : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static Fmx::Platform::_di_IFMXDialogServiceSync FDialogService;
	__classmethod Fmx::Platform::_di_IFMXDialogServiceSync __fastcall DialogService();
	
public:
	__classmethod void __fastcall ShowMessage(const System::UnicodeString AMessage);
	__classmethod int __fastcall MessageDialog(const System::UnicodeString AMessage, const System::Uitypes::TMsgDlgType ADialogType, const System::Uitypes::TMsgDlgButtons AButtons, const System::Uitypes::TMsgDlgBtn ADefaultButton, const System::Classes::THelpContext AHelpCtx);
	__classmethod bool __fastcall InputQuery(const System::UnicodeString ACaption, const System::UnicodeString *APrompts, const int APrompts_High, System::UnicodeString *AValues, const int AValues_High);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TDialogServiceSync() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDialogServiceSync() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sync */
}	/* namespace Dialogservice */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DIALOGSERVICE_SYNC)
using namespace Fmx::Dialogservice::Sync;
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
#endif	// Fmx_Dialogservice_SyncHPP
