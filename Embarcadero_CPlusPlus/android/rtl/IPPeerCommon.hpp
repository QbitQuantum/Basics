// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IPPeerCommon.pas' rev: 34.00 (Android)

#ifndef IppeercommonHPP
#define IppeercommonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------
namespace Ippeercommon
{
  _INIT_UNIT(Ippeercommon);
}	/* namespace Ippeercommon */
#if !defined(_NO_PRAGMA_LINK_INDY)
 #ifndef USEPACKAGES
  #pragma link "IndyCore.lib"
  #pragma link "IndyProtocols.lib"
  #pragma link "IndySystem.lib"
 #else
  #pragma link "IndyCore.bpi"
  #pragma link "IndyProtocols.bpi"
  #pragma link "IndySystem.bpi"
 #endif
#endif

namespace Ippeercommon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdClassIP;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdClassIP : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	bool FIsFreed;
	
protected:
	void __fastcall SetDestroyed();
	bool __fastcall NeedToFree();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TObject.Create */ inline __fastcall TIdClassIP() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdClassIP() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall IPImpId(void);
}	/* namespace Ippeercommon */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IPPEERCOMMON)
using namespace Ippeercommon;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IppeercommonHPP
