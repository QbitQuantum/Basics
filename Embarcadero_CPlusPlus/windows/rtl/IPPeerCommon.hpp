// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IPPeerCommon.pas' rev: 34.00 (Windows)

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
#pragma link "IPPeerCommon"
#if !defined(_NO_PRAGMA_LINK_INDY)
 #ifndef USEPACKAGES
#ifndef _WIN64
  #pragma link "IndyCore.lib"
  #pragma link "IndyProtocols.lib"
  #pragma link "IndySystem.lib"
#else /* _WIN64 */
  #pragma link "IndyCore.a"
  #pragma link "IndyProtocols.a"
  #pragma link "IndySystem.a"
#endif /* _WIN64 */
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
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
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

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall IPImpId();
}	/* namespace Ippeercommon */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IPPEERCOMMON)
using namespace Ippeercommon;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IppeercommonHPP
