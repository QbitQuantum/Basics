// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdText.pas' rev: 34.00 (iOS)

#ifndef IdtextHPP
#define IdtextHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdMessageParts.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idtext
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdText;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdText : public Idmessageparts::TIdMessagePart
{
	typedef Idmessageparts::TIdMessagePart inherited;
	
protected:
	System::Classes::TStrings* FBody;
	virtual void __fastcall SetBody(System::Classes::TStrings* const AStrs);
	
public:
	__fastcall TIdText(Idmessageparts::TIdMessageParts* Collection, System::Classes::TStrings* ABody);
	__fastcall virtual ~TIdText();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	bool __fastcall IsBodyEncodingRequired();
	__classmethod virtual Idmessageparts::TIdMessagePartType __fastcall PartType();
	__property System::Classes::TStrings* Body = {read=FBody, write=SetBody};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idtext */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDTEXT)
using namespace Idtext;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdtextHPP
