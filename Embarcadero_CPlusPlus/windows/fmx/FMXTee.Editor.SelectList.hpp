// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.SelectList.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Editor_SelectlistHPP
#define Fmxtee_Editor_SelectlistHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Variants.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Selectlist
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSelectListForm;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSelectListForm : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Listbox::TListBox* FromList;
	Fmx::Stdctrls::TPanel* Panel2;
	Fmx::Stdctrls::TButton* BRightOne;
	Fmx::Stdctrls::TButton* BRightAll;
	Fmx::Stdctrls::TButton* BLeftOne;
	Fmx::Stdctrls::TButton* BLeftAll;
	Fmx::Stdctrls::TSplitter* Splitter1;
	Fmx::Stdctrls::TPanel* Panel3;
	Fmx::Stdctrls::TButton* BMoveUp;
	Fmx::Stdctrls::TButton* BMoveDown;
	Fmx::Listbox::TListBox* ToList;
	void __fastcall BMoveUpClick(System::TObject* Sender);
	void __fastcall BMoveDownClick(System::TObject* Sender);
	void __fastcall ToListChange(System::TObject* Sender);
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall BRightOneClick(System::TObject* Sender);
	void __fastcall BLeftOneClick(System::TObject* Sender);
	void __fastcall BRightAllClick(System::TObject* Sender);
	void __fastcall BLeftAllClick(System::TObject* Sender);
	void __fastcall FromListDblClick(System::TObject* Sender);
	void __fastcall ToListDblClick(System::TObject* Sender);
	
private:
	void __fastcall Changed();
	
public:
	System::Classes::TNotifyEvent OnChange;
	void __fastcall EnableButtons();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TSelectListForm(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TSelectListForm(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TSelectListForm() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Selectlist */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SELECTLIST)
using namespace Fmxtee::Editor::Selectlist;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR)
using namespace Fmxtee::Editor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_Editor_SelectlistHPP
