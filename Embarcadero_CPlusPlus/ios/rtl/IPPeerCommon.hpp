// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IPPeerCommon.pas' rev: 34.00 (iOS)

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
#if defined(__APPLE__) && !defined(_NO_PRAGMA_LINK_INDY)
 #ifndef USEPACKAGES
  #pragma link "IndyCore.a"
  #pragma link "IndyProtocols.a"
  #pragma link "IndySystem.a"
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
