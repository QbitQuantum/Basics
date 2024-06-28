// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Dalvik.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_DalvikHPP
#define Androidapi_Jni_DalvikHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Dalvik
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JBaseDexClassLoaderClass;
typedef System::DelphiInterface<JBaseDexClassLoaderClass> _di_JBaseDexClassLoaderClass;
__interface DELPHIINTERFACE JBaseDexClassLoader;
typedef System::DelphiInterface<JBaseDexClassLoader> _di_JBaseDexClassLoader;
class DELPHICLASS TJBaseDexClassLoader;
__interface DELPHIINTERFACE JDexClassLoaderClass;
typedef System::DelphiInterface<JDexClassLoaderClass> _di_JDexClassLoaderClass;
__interface DELPHIINTERFACE JDexClassLoader;
typedef System::DelphiInterface<JDexClassLoader> _di_JDexClassLoader;
class DELPHICLASS TJDexClassLoader;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{C907AADB-131B-49CC-A2F6-03B88756C7AD}") JBaseDexClassLoaderClass  : public Androidapi::Jni::Javatypes::JClassLoaderClass 
{
	HIDESBASE virtual _di_JBaseDexClassLoader __cdecl init(Androidapi::Jni::Javatypes::_di_JString dexPath, Androidapi::Jni::Javatypes::_di_JFile optimizedDirectory, Androidapi::Jni::Javatypes::_di_JString librarySearchPath, Androidapi::Jni::Javatypes::_di_JClassLoader parent) = 0 ;
};

__interface  INTERFACE_UUID("{8E8B3944-DF8D-4BBD-AA80-588357BF7565}") JBaseDexClassLoader  : public Androidapi::Jni::Javatypes::JClassLoader 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl findLibrary(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBaseDexClassLoader : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseDexClassLoaderClass,_di_JBaseDexClassLoader>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseDexClassLoaderClass,_di_JBaseDexClassLoader> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBaseDexClassLoader() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseDexClassLoaderClass,_di_JBaseDexClassLoader>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBaseDexClassLoader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9350A960-93CE-4D6C-BD80-650CCC1AFC4C}") JDexClassLoaderClass  : public JBaseDexClassLoaderClass 
{
	HIDESBASE virtual _di_JDexClassLoader __cdecl init(Androidapi::Jni::Javatypes::_di_JString dexPath, Androidapi::Jni::Javatypes::_di_JString optimizedDirectory, Androidapi::Jni::Javatypes::_di_JString librarySearchPath, Androidapi::Jni::Javatypes::_di_JClassLoader parent) = 0 ;
};

__interface  INTERFACE_UUID("{990A5C23-67CB-4521-A9FA-37C6E9BA05A7}") JDexClassLoader  : public JBaseDexClassLoader 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDexClassLoader : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDexClassLoaderClass,_di_JDexClassLoader>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDexClassLoaderClass,_di_JDexClassLoader> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDexClassLoader() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDexClassLoaderClass,_di_JDexClassLoader>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDexClassLoader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dalvik */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_DALVIK)
using namespace Androidapi::Jni::Dalvik;
#endif
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
#endif	// Androidapi_Jni_DalvikHPP
