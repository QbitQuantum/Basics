// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdHashMessageDigest.pas' rev: 34.00 (Android)

#ifndef IdhashmessagedigestHPP
#define IdhashmessagedigestHPP

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
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idhashmessagedigest
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdHashMessageDigest;
class DELPHICLASS TIdHashMessageDigest2;
class DELPHICLASS TIdHashMessageDigest4;
class DELPHICLASS TIdHashMessageDigest5;
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<unsigned, 4> T4x4LongWordRecord;

typedef System::StaticArray<unsigned, 16> T16x4LongWordRecord;

typedef System::StaticArray<System::StaticArray<unsigned, 4>, 4> T4x4x4LongWordRecord;

typedef System::StaticArray<System::Byte, 64> T512BitRecord;

typedef System::StaticArray<System::Byte, 48> T384BitRecord;

typedef System::StaticArray<System::Byte, 16> T128BitRecord;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHashMessageDigest : public Idhash::TIdHashNativeAndIntF
{
	typedef Idhash::TIdHashNativeAndIntF inherited;
	
protected:
	Idglobal::TIdBytes FCBuffer;
	virtual void __fastcall MDCoder() = 0 ;
	virtual void __fastcall Reset();
public:
	/* TIdHash.Create */ inline __fastcall virtual TIdHashMessageDigest() : Idhash::TIdHashNativeAndIntF() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashMessageDigest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHashMessageDigest2 : public TIdHashMessageDigest
{
	typedef TIdHashMessageDigest inherited;
	
protected:
	T384BitRecord FX;
	T128BitRecord FCheckSum;
	virtual void __fastcall MDCoder();
	virtual void __fastcall Reset();
	virtual void * __fastcall InitHash();
	virtual Idglobal::TIdBytes __fastcall NativeGetHashBytes(System::Classes::TStream* AStream, __int64 ASize);
	virtual System::UnicodeString __fastcall HashToHex(const Idglobal::TIdBytes AHash);
	
public:
	__fastcall virtual TIdHashMessageDigest2();
	__classmethod virtual bool __fastcall IsIntfAvailable();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashMessageDigest2() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHashMessageDigest4 : public TIdHashMessageDigest
{
	typedef TIdHashMessageDigest inherited;
	
protected:
	T4x4LongWordRecord FState;
	virtual Idglobal::TIdBytes __fastcall NativeGetHashBytes(System::Classes::TStream* AStream, __int64 ASize);
	virtual System::UnicodeString __fastcall HashToHex(const Idglobal::TIdBytes AHash);
	virtual void __fastcall MDCoder();
	virtual void * __fastcall InitHash();
	
public:
	__fastcall virtual TIdHashMessageDigest4();
	__classmethod virtual bool __fastcall IsIntfAvailable();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashMessageDigest4() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdHashMessageDigest5 : public TIdHashMessageDigest4
{
	typedef TIdHashMessageDigest4 inherited;
	
protected:
	virtual void __fastcall MDCoder();
	virtual void * __fastcall InitHash();
	
public:
	__classmethod virtual bool __fastcall IsIntfAvailable();
public:
	/* TIdHashMessageDigest4.Create */ inline __fastcall virtual TIdHashMessageDigest5() : TIdHashMessageDigest4() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdHashMessageDigest5() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idhashmessagedigest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDHASHMESSAGEDIGEST)
using namespace Idhashmessagedigest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdhashmessagedigestHPP
