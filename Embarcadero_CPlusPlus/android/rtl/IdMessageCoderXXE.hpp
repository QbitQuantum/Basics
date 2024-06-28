// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdMessageCoderXXE.pas' rev: 34.00 (Android)

#ifndef IdmessagecoderxxeHPP
#define IdmessagecoderxxeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdMessageCoderUUE.hpp>
#include <IdMessageCoder.hpp>
#include <IdMessage.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idmessagecoderxxe
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdMessageEncoderXXE;
class DELPHICLASS TIdMessageEncoderInfoXXE;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdMessageEncoderXXE : public Idmessagecoderuue::TIdMessageEncoderUUEBase
{
	typedef Idmessagecoderuue::TIdMessageEncoderUUEBase inherited;
	
protected:
	virtual void __fastcall InitComponent();
public:
	/* TIdComponent.Destroy */ inline __fastcall virtual ~TIdMessageEncoderXXE() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdMessageEncoderXXE(System::Classes::TComponent* AOwner)/* overload */ : Idmessagecoderuue::TIdMessageEncoderUUEBase(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMessageEncoderXXE()/* overload */ : Idmessagecoderuue::TIdMessageEncoderUUEBase() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdMessageEncoderInfoXXE : public Idmessagecoder::TIdMessageEncoderInfo
{
	typedef Idmessagecoder::TIdMessageEncoderInfo inherited;
	
public:
	__fastcall virtual TIdMessageEncoderInfoXXE();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdMessageEncoderInfoXXE() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idmessagecoderxxe */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDMESSAGECODERXXE)
using namespace Idmessagecoderxxe;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdmessagecoderxxeHPP
