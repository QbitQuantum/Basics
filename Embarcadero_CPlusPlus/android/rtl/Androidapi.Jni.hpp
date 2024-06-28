// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.Jni.pas' rev: 34.00 (Android)

#ifndef Androidapi_JniHPP
#define Androidapi_JniHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------
#include <jni.h>

namespace Androidapi
{
namespace Jni
{
//-- forward type declarations -----------------------------------------------
struct DECLSPEC_DRECORD _JNIObject
{
};


struct JNIValue;
struct DECLSPEC_DRECORD _JNIFieldID
{
};


struct DECLSPEC_DRECORD _JNIMethodID
{
};


//-- type declarations -------------------------------------------------------
typedef int JNIInt;

typedef __int64 JNILong;

typedef System::Int8 JNIByte;

typedef System::DynamicArray<System::Byte> TByteArray;

typedef System::DynamicArray<int> TIntegerArray;

typedef System::Byte JNIBoolean;

typedef System::WideChar JNIChar;

typedef short JNIShort;

typedef float JNIFloat;

typedef double JNIDouble;

typedef int JNISize;

typedef _JNIObject *JNIObject;

typedef JNIObject JNIClass;

typedef JNIObject JNIThrowable;

typedef JNIObject JNIString;

typedef JNIObject JNIArray;

typedef JNIObject JNIBooleanArray;

typedef JNIObject JNIByteArray;

typedef JNIObject JNICharArray;

typedef JNIObject JNIShortArray;

typedef JNIObject JNIIntArray;

typedef JNIObject JNILongArray;

typedef JNIObject JNIFloatArray;

typedef JNIObject JNIDoubleArray;

typedef JNIObject JNIObjectArray;

typedef JNIObject JNIWeak;

typedef JNIObject JNIRef;

#pragma pack(push,1)
struct DECLSPEC_DRECORD JNIValue
{
	
public:
	union
	{
		struct 
		{
			_JNIObject *l;
		};
		struct 
		{
			double d;
		};
		struct 
		{
			float f;
		};
		struct 
		{
			__int64 j;
		};
		struct 
		{
			int i;
		};
		struct 
		{
			short s;
		};
		struct 
		{
			System::WideChar c;
		};
		struct 
		{
			System::Int8 b;
		};
		struct 
		{
			System::Byte z;
		};
		
	};
};
#pragma pack(pop)


typedef System::DynamicArray<JNIValue> TJNIValueArray;

typedef _JNIFieldID *JNIFieldID;

typedef _JNIMethodID *JNIMethodID;

typedef System::Int8 *PJNIByte;

typedef System::Byte *PJNIBoolean;

typedef System::WideChar *PJNIChar;

typedef short *PJNIShort;

typedef int *PJNIInt;

typedef __int64 *PJNILong;

typedef float *PJNIFloat;

typedef double *PJNIDouble;

typedef JNIObject *PJNIString;

typedef int *PJNISize;

typedef JNIObject *PJNIClass;

typedef JNIObject *PJNIObject;

typedef JNIObject *PJNIThrowable;

typedef JNIObject *PJNIArray;

typedef JNIObject *PJNIByteArray;

typedef JNIObject *PJNIBooleanArray;

typedef JNIObject *PJNICharArray;

typedef JNIObject *PJNIShortArray;

typedef JNIObject *PJNIIntArray;

typedef JNIObject *PJNILongArray;

typedef JNIObject *PJNIFloatArray;

typedef JNIObject *PJNIDoubleArray;

typedef JNIObject *PJNIObjectArray;

typedef JNIFieldID *PJNIFieldID;

typedef JNIMethodID *PJNIMethodID;

typedef JNIValue *PJNIValue;

typedef JNIObject *PJNIWeak;

typedef JNIObject *PJNIRef;

enum DECLSPEC_DENUM JNIObjectRefType : unsigned char { JNIInvalidRefType, JNILocalRefType, JNIGlobalRefType, JNIWeakGlobalRefType };

typedef JNINativeMethod *PJNINativeMethod;

typedef JavaVMAttachArgs *PJavaVMAttachArgs;

typedef JNIEnv *PJNIEnv;

typedef PJNIEnv *PPJNIEnv;

typedef JNINativeInterface *PJNINativeInterface;

typedef JavaVM *PJavaVM;

typedef PJavaVM *PPJavaVM;

typedef JNIInvokeInterface *PJNIInvokeInterface;

typedef int __cdecl (*TJNI_OnLoad)(PJavaVM PVM, void * Reserved);

typedef void __cdecl (*TJNI_OnUnload)(PJavaVM PVM, void * Reserved);

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall (*DoRaiseJNIException)(const System::UnicodeString JNIExceptionClassName, const System::UnicodeString Msg);
extern DELPHI_PACKAGE System::UnicodeString __fastcall JNIStringToString(PJNIEnv Env, JNIObject JStr);
extern DELPHI_PACKAGE JNIObject __fastcall StringToJNIString(PJNIEnv Env, const System::UnicodeString Str);
extern DELPHI_PACKAGE TJNIValueArray __fastcall ArgsToJNIValues(const System::TVarRec *Args, const int Args_High);
extern DELPHI_PACKAGE void __fastcall HandleJNIException(PJNIEnv Env);
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI)
using namespace Androidapi::Jni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_JniHPP
