// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNIMarshal.pas' rev: 34.00 (Android)

#ifndef Androidapi_JnimarshalHPP
#define Androidapi_JnimarshalHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.TypInfo.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jnimarshal
{
//-- forward type declarations -----------------------------------------------
struct TMarshalOp;
struct JNIMethodInvokeData;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TRetKind : unsigned char { rkBoolean, rkByte, rkChar, rkShort, rkInt, rkLong, rkFloat, rkDouble, rkVoid, rkObject, rkConstructor, rkInstance };

enum DECLSPEC_DENUM TMethodKind : unsigned char { mkObjectMethod, mkClassMethod, mkPropertySetMethod, mkPropertyGetMethod, mkClassPropertySetMethod, mkClassPropertyGetMethod };

#ifndef __aarch64__
enum DECLSPEC_DENUM TMarshalOpKind : unsigned char { moCopy, moJNIObject, moJNIArray };
#else /* __aarch64__ */
enum DECLSPEC_DENUM TMarshalOpKind : unsigned char { moCopy, moCopyFloat, moJNIObject, moJNIArray };
#endif /* __aarch64__ */

struct DECLSPEC_DRECORD TMarshalOp
{
public:
	System::Int8 Size;
	TMarshalOpKind Kind;
};


struct DECLSPEC_DRECORD JNIMethodInvokeData
{
public:
	NativeInt Size;
	System::TArray__1<TMarshalOp> Params;
	void *Instance;
	System::Typinfo::TTypeInfo *JavaType;
	void *MethodID;
	void *RetClsID;
	TMethodKind MethodType;
	TRetKind RetKind;
};


typedef JNIMethodInvokeData *PJNIMethodInvokeData;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Jnimarshal */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNIMARSHAL)
using namespace Androidapi::Jnimarshal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_JnimarshalHPP
