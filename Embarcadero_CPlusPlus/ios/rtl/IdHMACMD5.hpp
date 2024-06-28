// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHMACMD5.pas' rev: 34.00 (iOS)

#ifndef Idhmacmd5HPP
#define Idhmacmd5HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdFIPS.hpp>
#include <IdGlobal.hpp>
#include <IdHash.hpp>
#include <IdHashMessageDigest.hpp>
#include <IdHMAC.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idhmacmd5
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHMACMD5;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdHMACMD5 : public Idhmac::TIdHMAC
{
	typedef Idhmac::TIdHMAC inherited;
	
protected:
	virtual void __fastcall SetHashVars();
	virtual bool __fastcall IsIntFAvail();
	virtual void * __fastcall InitIntFInst(const Idglobal::TIdBytes AKey);
	virtual void __fastcall InitHash();
public:
	/* TIdHMAC.Create */ inline __fastcall virtual TIdHMACMD5() : Idhmac::TIdHMAC() { }
	/* TIdHMAC.Destroy */ inline __fastcall virtual ~TIdHMACMD5() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idhmacmd5 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHMACMD5)
using namespace Idhmacmd5;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idhmacmd5HPP
