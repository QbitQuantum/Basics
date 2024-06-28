// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.FMXUI.Async.pas' rev: 34.00 (Windows)

#ifndef Firedac_Fmxui_AsyncHPP
#define Firedac_Fmxui_AsyncHPP

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
#include <FMX.Forms.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <FMX.Effects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.FMXUI.OptsBase.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.FMXUI.Async"

namespace Firedac
{
namespace Fmxui
{
namespace Async
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFMXAsyncExecute;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFMXAsyncExecute : public Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase
{
	typedef Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase inherited;
	
__published:
	Fmx::Stdctrls::TPanel* pnlBlur;
	Fmx::Stdctrls::TAniIndicator* aniProgress;
	Fmx::Stdctrls::TLabel* lblText;
	Fmx::Stdctrls::TButton* btnCancel2;
	Fmx::Types::TTimer* tmrDelay;
	Fmx::Objects::TRectangle* rectBorder;
	Fmx::Stdctrls::TLabel* lblTitle;
	Fmx::Stdctrls::TPanel* pnlBottom;
	Fmx::Controls::TStyleBook* StyleBook1;
	void __fastcall FormKeyDown(System::TObject* Sender, System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	void __fastcall btnCancelClick(System::TObject* Sender);
	void __fastcall tmrDelayTimer(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	HIDESBASE void __fastcall FormCreate(System::TObject* Sender);
	
private:
	Firedac::Stan::Intf::_di_IFDStanAsyncExecutor FExecutor;
	bool FRequestShow;
	void *FModalData;
	int FShowDelay;
	int FHideDelay;
	
protected:
	HIDESBASE void __fastcall Show(const Firedac::Stan::Intf::_di_IFDStanAsyncExecutor AExecutor);
	HIDESBASE void __fastcall Hide();
	bool __fastcall IsFormMouseMessage(const tagMSG &AMsg);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TfrmFDGUIxFMXAsyncExecute(System::Classes::TComponent* AOwner) : Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFMXAsyncExecute(System::Classes::TComponent* AOwner, NativeInt Dummy) : Firedac::Fmxui::Optsbase::TfrmFDGUIxFMXOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFMXAsyncExecute() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Async */
}	/* namespace Fmxui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_FMXUI_ASYNC)
using namespace Firedac::Fmxui::Async;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_FMXUI)
using namespace Firedac::Fmxui;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Fmxui_AsyncHPP
