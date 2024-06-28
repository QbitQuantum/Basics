// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHMAC.pas' rev: 34.00 (Android)

#ifndef IdhmacHPP
#define IdhmacHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdFIPS.hpp>
#include <IdGlobal.hpp>
#include <IdHash.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idhmac
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHMACKeyBuilder;
class DELPHICLASS TIdHMAC;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHMACKeyBuilder : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod Idglobal::TIdBytes __fastcall Key(const int ASize);
	__classmethod Idglobal::TIdBytes __fastcall IV(const int ASize);
public:
	/* TObject.Create */ inline __fastcall TIdHMACKeyBuilder() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHMACKeyBuilder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHMAC : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	int FHashSize;
	int FBlockSize;
	Idglobal::TIdBytes FKey;
	Idhash::TIdHash* FHash;
	System::UnicodeString FHashName;
	virtual void __fastcall InitHash() = 0 ;
	void __fastcall InitKey();
	virtual void __fastcall SetHashVars() = 0 ;
	Idglobal::TIdBytes __fastcall HashValueNative(const Idglobal::TIdBytes ABuffer, const int ATruncateTo = 0xffffffff);
	Idglobal::TIdBytes __fastcall HashValueIntF(const Idglobal::TIdBytes ABuffer, const int ATruncateTo = 0xffffffff);
	virtual bool __fastcall IsIntFAvail();
	virtual void * __fastcall InitIntFInst(const Idglobal::TIdBytes AKey) = 0 ;
	
public:
	__fastcall virtual TIdHMAC();
	__fastcall virtual ~TIdHMAC();
	Idglobal::TIdBytes __fastcall HashValue(const Idglobal::TIdBytes ABuffer, const int ATruncateTo = 0xffffffff);
	__property int HashSize = {read=FHashSize, nodefault};
	__property int BlockSize = {read=FBlockSize, nodefault};
	__property System::UnicodeString HashName = {read=FHashName};
	__property Idglobal::TIdBytes Key = {read=FKey, write=FKey};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idhmac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHMAC)
using namespace Idhmac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdhmacHPP
