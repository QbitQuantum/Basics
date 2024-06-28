// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.RadioGroup.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_RadiogroupHPP
#define Fmxtee_RadiogroupHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls.Presentation.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Radiogroup
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TRadioGroup;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TRadioGroup : public Fmx::Stdctrls::TGroupBox
{
	typedef Fmx::Stdctrls::TGroupBox inherited;
	
private:
	int FItemIndex;
	System::Classes::TNotifyEvent FOnChange;
	bool FAutoSize;
	void __fastcall CheckSelected();
	int __fastcall GetCount();
	Fmx::Stdctrls::TRadioButton* __fastcall GetItem(int Index);
	void __fastcall ItemChanged(System::TObject* Sender);
	void __fastcall SetAutoSize(const bool Value);
	void __fastcall SetItemIndex(const int Value);
	
protected:
	virtual void __fastcall Changed();
	virtual void __fastcall DoAddObject(Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall DoRealign();
	virtual void __fastcall Loaded();
	
public:
	__fastcall virtual TRadioGroup(System::Classes::TComponent* AOwner)/* overload */;
	Fmx::Stdctrls::TRadioButton* __fastcall Add(const System::UnicodeString AText);
	int __fastcall IndexOfItem(System::TObject* AItem);
	Fmx::Stdctrls::TRadioButton* __fastcall Selected();
	__property int Count = {read=GetCount, nodefault};
	__property Fmx::Stdctrls::TRadioButton* Items[int Index] = {read=GetItem};
	
__published:
	__property bool AutoSize = {read=FAutoSize, write=SetAutoSize, default=0};
	__property CanFocus = {default=1};
	__property int ItemIndex = {read=FItemIndex, write=SetItemIndex, default=-1};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	/* TPresentedTextControl.Destroy */ inline __fastcall virtual ~TRadioGroup() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Radiogroup */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_RADIOGROUP)
using namespace Fmxtee::Radiogroup;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_RadiogroupHPP
