// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBFilterSummary.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbfiltersummaryHPP
#define Ibx_IbfiltersummaryHPP

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
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibfiltersummary
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmIBFilterSummary;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmIBFilterSummary : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TListView* lstSummary;
	Vcl::Buttons::TBitBtn* btnOk;
	Vcl::Buttons::TBitBtn* BitBtn1;
public:
	/* TCustomForm.Create */ inline __fastcall virtual TfrmIBFilterSummary(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmIBFilterSummary(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmIBFilterSummary() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmIBFilterSummary(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibfiltersummary */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBFILTERSUMMARY)
using namespace Ibx::Ibfiltersummary;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbfiltersummaryHPP
