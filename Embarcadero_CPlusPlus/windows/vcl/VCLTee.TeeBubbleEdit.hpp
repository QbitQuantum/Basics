// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeBubbleEdit.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeebubbleeditHPP
#define Vcltee_TeebubbleeditHPP

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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.TeePoEdi.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teebubbleedit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBubbleSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBubbleSeriesEditor : public Vcltee::Teepoedi::TSeriesPointerEditor
{
	typedef Vcltee::Teepoedi::TSeriesPointerEditor inherited;
	
__published:
	HIDESBASE void __fastcall FormShow(System::TObject* Sender);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TBubbleSeriesEditor(System::Classes::TComponent* AOwner) : Vcltee::Teepoedi::TSeriesPointerEditor(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TBubbleSeriesEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcltee::Teepoedi::TSeriesPointerEditor(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TBubbleSeriesEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TBubbleSeriesEditor(HWND ParentWindow) : Vcltee::Teepoedi::TSeriesPointerEditor(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teebubbleedit */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEBUBBLEEDIT)
using namespace Vcltee::Teebubbleedit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeebubbleeditHPP
