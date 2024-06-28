// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHashSHA.pas' rev: 34.00 (Android)

#ifndef IdhashshaHPP
#define IdhashshaHPP

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

namespace Idhashsha
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHashSHA1;
class DELPHICLASS TIdHashSHA224;
class DELPHICLASS TIdHashSHA256;
class DELPHICLASS TIdHashSHA384;
class DELPHICLASS TIdHashSHA512;
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<unsigned, 5> T5x4LongWordRecord;

typedef System::StaticArray<System::Byte, 64> T512BitRecord;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHashSHA1 : public Idhash::TIdHashNativeAndIntF
{
	typedef Idhash::TIdHashNativeAndIntF inherited;
	
protected:
	T5x4LongWordRecord FCheckSum;
	Idglobal::TIdBytes FCBuffer;
	void __fastcall Coder();
	virtual Idglobal::TIdBytes __fastcall NativeGetHashBytes(System::Classes::TStream* AStream, __int64 ASize);
	virtual System::UnicodeString __fastcall HashToHex(const Idglobal::TIdBytes AHash);
	virtual void * __fastcall InitHash();
	
public:
	__fastcall virtual TIdHashSHA1();
	__classmethod virtual bool __fastcall IsAvailable();
	__classmethod virtual bool __fastcall IsIntfAvailable();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashSHA1() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHashSHA224 : public Idhash::TIdHashIntF
{
	typedef Idhash::TIdHashIntF inherited;
	
protected:
	virtual void * __fastcall InitHash();
	
public:
	__classmethod virtual bool __fastcall IsAvailable();
public:
	/* TIdHash.Create */ inline __fastcall virtual TIdHashSHA224() : Idhash::TIdHashIntF() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashSHA224() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHashSHA256 : public Idhash::TIdHashIntF
{
	typedef Idhash::TIdHashIntF inherited;
	
protected:
	virtual void * __fastcall InitHash();
	
public:
	__classmethod virtual bool __fastcall IsAvailable();
public:
	/* TIdHash.Create */ inline __fastcall virtual TIdHashSHA256() : Idhash::TIdHashIntF() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashSHA256() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHashSHA384 : public Idhash::TIdHashIntF
{
	typedef Idhash::TIdHashIntF inherited;
	
protected:
	virtual void * __fastcall InitHash();
	
public:
	__classmethod virtual bool __fastcall IsAvailable();
public:
	/* TIdHash.Create */ inline __fastcall virtual TIdHashSHA384() : Idhash::TIdHashIntF() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashSHA384() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHashSHA512 : public Idhash::TIdHashIntF
{
	typedef Idhash::TIdHashIntF inherited;
	
protected:
	virtual void * __fastcall InitHash();
	
public:
	__classmethod virtual bool __fastcall IsAvailable();
public:
	/* TIdHash.Create */ inline __fastcall virtual TIdHashSHA512() : Idhash::TIdHashIntF() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashSHA512() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idhashsha */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHASHSHA)
using namespace Idhashsha;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdhashshaHPP
