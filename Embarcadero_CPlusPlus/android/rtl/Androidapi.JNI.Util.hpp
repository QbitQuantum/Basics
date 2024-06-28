// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Util.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_UtilHPP
#define Androidapi_Jni_UtilHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Util
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JAndroidExceptionClass;
typedef System::DelphiInterface<JAndroidExceptionClass> _di_JAndroidExceptionClass;
__interface DELPHIINTERFACE JAndroidException;
typedef System::DelphiInterface<JAndroidException> _di_JAndroidException;
class DELPHICLASS TJAndroidException;
__interface DELPHIINTERFACE JAndroidRuntimeExceptionClass;
typedef System::DelphiInterface<JAndroidRuntimeExceptionClass> _di_JAndroidRuntimeExceptionClass;
__interface DELPHIINTERFACE JAndroidRuntimeException;
typedef System::DelphiInterface<JAndroidRuntimeException> _di_JAndroidRuntimeException;
class DELPHICLASS TJAndroidRuntimeException;
__interface DELPHIINTERFACE JAttributeSetClass;
typedef System::DelphiInterface<JAttributeSetClass> _di_JAttributeSetClass;
__interface DELPHIINTERFACE JAttributeSet;
typedef System::DelphiInterface<JAttributeSet> _di_JAttributeSet;
class DELPHICLASS TJAttributeSet;
__interface DELPHIINTERFACE JDisplayMetricsClass;
typedef System::DelphiInterface<JDisplayMetricsClass> _di_JDisplayMetricsClass;
__interface DELPHIINTERFACE JDisplayMetrics;
typedef System::DelphiInterface<JDisplayMetrics> _di_JDisplayMetrics;
class DELPHICLASS TJDisplayMetrics;
__interface DELPHIINTERFACE JPairClass;
typedef System::DelphiInterface<JPairClass> _di_JPairClass;
__interface DELPHIINTERFACE JPair;
typedef System::DelphiInterface<JPair> _di_JPair;
class DELPHICLASS TJPair;
__interface DELPHIINTERFACE JPrinterClass;
typedef System::DelphiInterface<JPrinterClass> _di_JPrinterClass;
__interface DELPHIINTERFACE JPrinter;
typedef System::DelphiInterface<JPrinter> _di_JPrinter;
class DELPHICLASS TJPrinter;
__interface DELPHIINTERFACE JPropertyClass;
typedef System::DelphiInterface<JPropertyClass> _di_JPropertyClass;
__interface DELPHIINTERFACE JProperty;
typedef System::DelphiInterface<JProperty> _di_JProperty;
class DELPHICLASS TJProperty;
__interface DELPHIINTERFACE JRangeClass;
typedef System::DelphiInterface<JRangeClass> _di_JRangeClass;
__interface DELPHIINTERFACE JRange;
typedef System::DelphiInterface<JRange> _di_JRange;
class DELPHICLASS TJRange;
__interface DELPHIINTERFACE Jutil_SizeClass;
typedef System::DelphiInterface<Jutil_SizeClass> _di_Jutil_SizeClass;
__interface DELPHIINTERFACE Jutil_Size;
typedef System::DelphiInterface<Jutil_Size> _di_Jutil_Size;
class DELPHICLASS TJutil_Size;
__interface DELPHIINTERFACE JSizeFClass;
typedef System::DelphiInterface<JSizeFClass> _di_JSizeFClass;
__interface DELPHIINTERFACE JSizeF;
typedef System::DelphiInterface<JSizeF> _di_JSizeF;
class DELPHICLASS TJSizeF;
__interface DELPHIINTERFACE JSparseArrayClass;
typedef System::DelphiInterface<JSparseArrayClass> _di_JSparseArrayClass;
__interface DELPHIINTERFACE JSparseArray;
typedef System::DelphiInterface<JSparseArray> _di_JSparseArray;
class DELPHICLASS TJSparseArray;
__interface DELPHIINTERFACE JSparseBooleanArrayClass;
typedef System::DelphiInterface<JSparseBooleanArrayClass> _di_JSparseBooleanArrayClass;
__interface DELPHIINTERFACE JSparseBooleanArray;
typedef System::DelphiInterface<JSparseBooleanArray> _di_JSparseBooleanArray;
class DELPHICLASS TJSparseBooleanArray;
__interface DELPHIINTERFACE JTypedValueClass;
typedef System::DelphiInterface<JTypedValueClass> _di_JTypedValueClass;
__interface DELPHIINTERFACE JTypedValue;
typedef System::DelphiInterface<JTypedValue> _di_JTypedValue;
class DELPHICLASS TJTypedValue;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{316A42C1-5EB3-4252-BD9B-DF12B2FDF470}") JAndroidExceptionClass  : public Androidapi::Jni::Javatypes::JExceptionClass 
{
	HIDESBASE virtual _di_JAndroidException __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JAndroidException __cdecl init(Androidapi::Jni::Javatypes::_di_JString name) = 0 /* overload */;
	HIDESBASE virtual _di_JAndroidException __cdecl init(Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Javatypes::_di_JThrowable cause) = 0 /* overload */;
	HIDESBASE virtual _di_JAndroidException __cdecl init(Androidapi::Jni::Javatypes::_di_JException cause) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{9DD82875-9F43-483A-83BC-980F36CBCA5A}") JAndroidException  : public Androidapi::Jni::Javatypes::JException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAndroidException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAndroidExceptionClass,_di_JAndroidException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAndroidExceptionClass,_di_JAndroidException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAndroidException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAndroidExceptionClass,_di_JAndroidException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAndroidException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0858B0B4-AAB9-4F0B-850F-33B575ACFE7B}") JAndroidRuntimeExceptionClass  : public Androidapi::Jni::Javatypes::JRuntimeExceptionClass 
{
	HIDESBASE virtual _di_JAndroidRuntimeException __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JAndroidRuntimeException __cdecl init(Androidapi::Jni::Javatypes::_di_JString name) = 0 /* overload */;
	HIDESBASE virtual _di_JAndroidRuntimeException __cdecl init(Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Javatypes::_di_JThrowable cause) = 0 /* overload */;
	HIDESBASE virtual _di_JAndroidRuntimeException __cdecl init(Androidapi::Jni::Javatypes::_di_JException cause) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{83257DE1-7FFC-4373-B4B3-ED0330D090ED}") JAndroidRuntimeException  : public Androidapi::Jni::Javatypes::JRuntimeException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAndroidRuntimeException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAndroidRuntimeExceptionClass,_di_JAndroidRuntimeException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAndroidRuntimeExceptionClass,_di_JAndroidRuntimeException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAndroidRuntimeException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAndroidRuntimeExceptionClass,_di_JAndroidRuntimeException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAndroidRuntimeException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{38053FDE-577B-41AB-9D3F-0572B876D9A1}") JAttributeSetClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{A68EE3B4-0C0D-4B03-A0A0-163C13A234CC}") JAttributeSet  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl getAttributeBooleanValue(Androidapi::Jni::Javatypes::_di_JString Namespace, Androidapi::Jni::Javatypes::_di_JString attribute, bool defaultValue) = 0 /* overload */;
	virtual bool __cdecl getAttributeBooleanValue(int index, bool defaultValue) = 0 /* overload */;
	virtual int __cdecl getAttributeCount() = 0 ;
	virtual float __cdecl getAttributeFloatValue(Androidapi::Jni::Javatypes::_di_JString Namespace, Androidapi::Jni::Javatypes::_di_JString attribute, float defaultValue) = 0 /* overload */;
	virtual float __cdecl getAttributeFloatValue(int index, float defaultValue) = 0 /* overload */;
	virtual int __cdecl getAttributeIntValue(Androidapi::Jni::Javatypes::_di_JString Namespace, Androidapi::Jni::Javatypes::_di_JString attribute, int defaultValue) = 0 /* overload */;
	virtual int __cdecl getAttributeIntValue(int index, int defaultValue) = 0 /* overload */;
	virtual int __cdecl getAttributeListValue(Androidapi::Jni::Javatypes::_di_JString Namespace, Androidapi::Jni::Javatypes::_di_JString attribute, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* options, int defaultValue) = 0 /* overload */;
	virtual int __cdecl getAttributeListValue(int index, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* options, int defaultValue) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAttributeName(int index) = 0 ;
	virtual int __cdecl getAttributeNameResource(int index) = 0 ;
	virtual int __cdecl getAttributeResourceValue(Androidapi::Jni::Javatypes::_di_JString Namespace, Androidapi::Jni::Javatypes::_di_JString attribute, int defaultValue) = 0 /* overload */;
	virtual int __cdecl getAttributeResourceValue(int index, int defaultValue) = 0 /* overload */;
	virtual int __cdecl getAttributeUnsignedIntValue(Androidapi::Jni::Javatypes::_di_JString Namespace, Androidapi::Jni::Javatypes::_di_JString attribute, int defaultValue) = 0 /* overload */;
	virtual int __cdecl getAttributeUnsignedIntValue(int index, int defaultValue) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAttributeValue(int index) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAttributeValue(Androidapi::Jni::Javatypes::_di_JString Namespace, Androidapi::Jni::Javatypes::_di_JString name) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getClassAttribute() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getIdAttribute() = 0 ;
	virtual int __cdecl getIdAttributeResourceValue(int defaultValue) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPositionDescription() = 0 ;
	virtual int __cdecl getStyleAttribute() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAttributeSet : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAttributeSetClass,_di_JAttributeSet>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAttributeSetClass,_di_JAttributeSet> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAttributeSet() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAttributeSetClass,_di_JAttributeSet>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAttributeSet() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5B98B374-49AD-4739-873F-C979B3F824CD}") JDisplayMetricsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetDENSITY_260() = 0 ;
	virtual int __cdecl _GetDENSITY_280() = 0 ;
	virtual int __cdecl _GetDENSITY_300() = 0 ;
	virtual int __cdecl _GetDENSITY_340() = 0 ;
	virtual int __cdecl _GetDENSITY_360() = 0 ;
	virtual int __cdecl _GetDENSITY_400() = 0 ;
	virtual int __cdecl _GetDENSITY_420() = 0 ;
	virtual int __cdecl _GetDENSITY_560() = 0 ;
	virtual int __cdecl _GetDENSITY_DEFAULT() = 0 ;
	virtual int __cdecl _GetDENSITY_DEVICE_STABLE() = 0 ;
	virtual int __cdecl _GetDENSITY_HIGH() = 0 ;
	virtual int __cdecl _GetDENSITY_LOW() = 0 ;
	virtual int __cdecl _GetDENSITY_MEDIUM() = 0 ;
	virtual int __cdecl _GetDENSITY_TV() = 0 ;
	virtual int __cdecl _GetDENSITY_XHIGH() = 0 ;
	virtual int __cdecl _GetDENSITY_XXHIGH() = 0 ;
	virtual int __cdecl _GetDENSITY_XXXHIGH() = 0 ;
	HIDESBASE virtual _di_JDisplayMetrics __cdecl init() = 0 ;
	__property int DENSITY_260 = {read=_GetDENSITY_260};
	__property int DENSITY_280 = {read=_GetDENSITY_280};
	__property int DENSITY_300 = {read=_GetDENSITY_300};
	__property int DENSITY_340 = {read=_GetDENSITY_340};
	__property int DENSITY_360 = {read=_GetDENSITY_360};
	__property int DENSITY_400 = {read=_GetDENSITY_400};
	__property int DENSITY_420 = {read=_GetDENSITY_420};
	__property int DENSITY_560 = {read=_GetDENSITY_560};
	__property int DENSITY_DEFAULT = {read=_GetDENSITY_DEFAULT};
	__property int DENSITY_DEVICE_STABLE = {read=_GetDENSITY_DEVICE_STABLE};
	__property int DENSITY_HIGH = {read=_GetDENSITY_HIGH};
	__property int DENSITY_LOW = {read=_GetDENSITY_LOW};
	__property int DENSITY_MEDIUM = {read=_GetDENSITY_MEDIUM};
	__property int DENSITY_TV = {read=_GetDENSITY_TV};
	__property int DENSITY_XHIGH = {read=_GetDENSITY_XHIGH};
	__property int DENSITY_XXHIGH = {read=_GetDENSITY_XXHIGH};
	__property int DENSITY_XXXHIGH = {read=_GetDENSITY_XXXHIGH};
};

__interface  INTERFACE_UUID("{D3EC59F1-BB9A-4820-BBB6-47A518711902}") JDisplayMetrics  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl _Getdensity() = 0 ;
	virtual void __cdecl _Setdensity(float Value) = 0 ;
	virtual int __cdecl _GetdensityDpi() = 0 ;
	virtual void __cdecl _SetdensityDpi(int Value) = 0 ;
	virtual int __cdecl _GetheightPixels() = 0 ;
	virtual void __cdecl _SetheightPixels(int Value) = 0 ;
	virtual float __cdecl _GetscaledDensity() = 0 ;
	virtual void __cdecl _SetscaledDensity(float Value) = 0 ;
	virtual int __cdecl _GetwidthPixels() = 0 ;
	virtual void __cdecl _SetwidthPixels(int Value) = 0 ;
	virtual float __cdecl _Getxdpi() = 0 ;
	virtual void __cdecl _Setxdpi(float Value) = 0 ;
	virtual float __cdecl _Getydpi() = 0 ;
	virtual void __cdecl _Setydpi(float Value) = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 /* overload */;
	HIDESBASE virtual bool __cdecl equals(_di_JDisplayMetrics other) = 0 /* overload */;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual void __cdecl setTo(_di_JDisplayMetrics o) = 0 ;
	virtual void __cdecl setToDefaults() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	__property float density = {read=_Getdensity, write=_Setdensity};
	__property int densityDpi = {read=_GetdensityDpi, write=_SetdensityDpi};
	__property int heightPixels = {read=_GetheightPixels, write=_SetheightPixels};
	__property float scaledDensity = {read=_GetscaledDensity, write=_SetscaledDensity};
	__property int widthPixels = {read=_GetwidthPixels, write=_SetwidthPixels};
	__property float xdpi = {read=_Getxdpi, write=_Setxdpi};
	__property float ydpi = {read=_Getydpi, write=_Setydpi};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDisplayMetrics : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDisplayMetricsClass,_di_JDisplayMetrics>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDisplayMetricsClass,_di_JDisplayMetrics> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDisplayMetrics() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDisplayMetricsClass,_di_JDisplayMetrics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDisplayMetrics() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FC74853D-BE83-4F13-8068-CA5D73548F17}") JPairClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JPair __cdecl init(Androidapi::Jni::Javatypes::_di_JObject first, Androidapi::Jni::Javatypes::_di_JObject second) = 0 ;
	virtual _di_JPair __cdecl create(Androidapi::Jni::Javatypes::_di_JObject a, Androidapi::Jni::Javatypes::_di_JObject b) = 0 ;
};

__interface  INTERFACE_UUID("{F5066B7F-AF96-45FD-AF9F-7F42F8EE8A5D}") JPair  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl _Getfirst() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl _Getsecond() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JObject first = {read=_Getfirst};
	__property Androidapi::Jni::Javatypes::_di_JObject second = {read=_Getsecond};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPair : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPairClass,_di_JPair>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPairClass,_di_JPair> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPair() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPairClass,_di_JPair>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPair() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7D16885A-30FC-4B75-A5B5-78A36D20B8CC}") JPrinterClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{118D609E-31BE-43D6-91A8-119D5B6BBE3C}") JPrinter  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl println(Androidapi::Jni::Javatypes::_di_JString x) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPrinter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrinterClass,_di_JPrinter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrinterClass,_di_JPrinter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPrinter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrinterClass,_di_JPrinter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPrinter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9189FC50-84D8-4091-95ED-15B3B8FACC15}") JPropertyClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JProperty __cdecl init(Androidapi::Jni::Javatypes::_di_Jlang_Class type_, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual _di_JProperty __cdecl of(Androidapi::Jni::Javatypes::_di_Jlang_Class hostType, Androidapi::Jni::Javatypes::_di_Jlang_Class valueType, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
};

__interface  INTERFACE_UUID("{2803C5A6-4347-4D46-AEAA-28C87BB457B5}") JProperty  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl get(Androidapi::Jni::Javatypes::_di_JObject object_) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_Jlang_Class __cdecl getType() = 0 ;
	virtual bool __cdecl isReadOnly() = 0 ;
	virtual void __cdecl set(Androidapi::Jni::Javatypes::_di_JObject object_, Androidapi::Jni::Javatypes::_di_JObject value) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJProperty : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPropertyClass,_di_JProperty>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPropertyClass,_di_JProperty> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJProperty() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPropertyClass,_di_JProperty>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJProperty() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F33DC57E-796A-44C1-81F6-0DE129721343}") JRangeClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JRange __cdecl init(Androidapi::Jni::Javatypes::_di_JComparable lower, Androidapi::Jni::Javatypes::_di_JComparable upper) = 0 ;
	virtual _di_JRange __cdecl create(Androidapi::Jni::Javatypes::_di_JComparable lower, Androidapi::Jni::Javatypes::_di_JComparable upper) = 0 ;
};

__interface  INTERFACE_UUID("{CCDFBCEC-E08B-4B45-9953-F04EDBCE1AC7}") JRange  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JComparable __cdecl clamp(Androidapi::Jni::Javatypes::_di_JComparable value) = 0 ;
	virtual bool __cdecl contains(Androidapi::Jni::Javatypes::_di_JComparable value) = 0 /* overload */;
	virtual bool __cdecl contains(_di_JRange range) = 0 /* overload */;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual _di_JRange __cdecl extend(_di_JRange range) = 0 /* overload */;
	virtual _di_JRange __cdecl extend(Androidapi::Jni::Javatypes::_di_JComparable lower, Androidapi::Jni::Javatypes::_di_JComparable upper) = 0 /* overload */;
	virtual _di_JRange __cdecl extend(Androidapi::Jni::Javatypes::_di_JComparable value) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JComparable __cdecl getLower() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JComparable __cdecl getUpper() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual _di_JRange __cdecl intersect(_di_JRange range) = 0 /* overload */;
	virtual _di_JRange __cdecl intersect(Androidapi::Jni::Javatypes::_di_JComparable lower, Androidapi::Jni::Javatypes::_di_JComparable upper) = 0 /* overload */;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRange : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRangeClass,_di_JRange>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRangeClass,_di_JRange> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRange() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRangeClass,_di_JRange>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRange() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{214877DC-3C23-41FC-A5E5-AD122E30E787}") Jutil_SizeClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_Jutil_Size __cdecl init(int width, int height) = 0 ;
	virtual _di_Jutil_Size __cdecl parseSize(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
};

__interface  INTERFACE_UUID("{E57F5407-74DB-4B6C-A0D0-3AE4B7A33C28}") Jutil_Size  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual int __cdecl getHeight() = 0 ;
	virtual int __cdecl getWidth() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJutil_Size : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jutil_SizeClass,_di_Jutil_Size>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jutil_SizeClass,_di_Jutil_Size> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJutil_Size() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jutil_SizeClass,_di_Jutil_Size>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJutil_Size() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{25EA8EC9-E533-4443-AE91-AD7A5F818865}") JSizeFClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSizeF __cdecl init(float width, float height) = 0 ;
	virtual _di_JSizeF __cdecl parseSizeF(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
};

__interface  INTERFACE_UUID("{4EEB0336-42B1-4281-880C-D43693201935}") JSizeF  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual float __cdecl getHeight() = 0 ;
	virtual float __cdecl getWidth() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSizeF : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSizeFClass,_di_JSizeF>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSizeFClass,_di_JSizeF> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSizeF() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSizeFClass,_di_JSizeF>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSizeF() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4E51484A-CD9E-4170-8CCF-B3C8A8CA3F26}") JSparseArrayClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSparseArray __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JSparseArray __cdecl init(int initialCapacity) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{AFB1BC39-0C23-4B91-A7E9-C03FD965EA44}") JSparseArray  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl append(int key, Androidapi::Jni::Javatypes::_di_JObject value) = 0 ;
	virtual void __cdecl clear() = 0 ;
	virtual _di_JSparseArray __cdecl clone() = 0 ;
	virtual void __cdecl Delete(int key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl get(int key) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl get(int key, Androidapi::Jni::Javatypes::_di_JObject valueIfKeyNotFound) = 0 /* overload */;
	virtual int __cdecl indexOfKey(int key) = 0 ;
	virtual int __cdecl indexOfValue(Androidapi::Jni::Javatypes::_di_JObject value) = 0 ;
	virtual int __cdecl keyAt(int index) = 0 ;
	virtual void __cdecl put(int key, Androidapi::Jni::Javatypes::_di_JObject value) = 0 ;
	virtual void __cdecl remove(int key) = 0 ;
	virtual void __cdecl removeAt(int index) = 0 ;
	virtual void __cdecl removeAtRange(int index, int size) = 0 ;
	virtual void __cdecl setValueAt(int index, Androidapi::Jni::Javatypes::_di_JObject value) = 0 ;
	virtual int __cdecl size() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl valueAt(int index) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSparseArray : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSparseArrayClass,_di_JSparseArray>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSparseArrayClass,_di_JSparseArray> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSparseArray() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSparseArrayClass,_di_JSparseArray>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSparseArray() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D23BD7F9-76E0-4E9D-AAF4-AFE4660DEE0F}") JSparseBooleanArrayClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSparseBooleanArray __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JSparseBooleanArray __cdecl init(int initialCapacity) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{5DD9C005-5426-4BEB-A03E-CA66DE454B01}") JSparseBooleanArray  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl append(int key, bool value) = 0 ;
	virtual void __cdecl clear() = 0 ;
	virtual _di_JSparseBooleanArray __cdecl clone() = 0 ;
	virtual void __cdecl Delete(int key) = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject that) = 0 ;
	virtual bool __cdecl get(int key) = 0 /* overload */;
	virtual bool __cdecl get(int key, bool valueIfKeyNotFound) = 0 /* overload */;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual int __cdecl indexOfKey(int key) = 0 ;
	virtual int __cdecl indexOfValue(bool value) = 0 ;
	virtual int __cdecl keyAt(int index) = 0 ;
	virtual void __cdecl put(int key, bool value) = 0 ;
	virtual int __cdecl size() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual bool __cdecl valueAt(int index) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSparseBooleanArray : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSparseBooleanArrayClass,_di_JSparseBooleanArray>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSparseBooleanArrayClass,_di_JSparseBooleanArray> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSparseBooleanArray() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSparseBooleanArrayClass,_di_JSparseBooleanArray>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSparseBooleanArray() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{772C1CBF-A712-432D-9AAE-54E62D0DC745}") JTypedValueClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetCOMPLEX_MANTISSA_MASK() = 0 ;
	virtual int __cdecl _GetCOMPLEX_MANTISSA_SHIFT() = 0 ;
	virtual int __cdecl _GetCOMPLEX_RADIX_0p23() = 0 ;
	virtual int __cdecl _GetCOMPLEX_RADIX_16p7() = 0 ;
	virtual int __cdecl _GetCOMPLEX_RADIX_23p0() = 0 ;
	virtual int __cdecl _GetCOMPLEX_RADIX_8p15() = 0 ;
	virtual int __cdecl _GetCOMPLEX_RADIX_MASK() = 0 ;
	virtual int __cdecl _GetCOMPLEX_RADIX_SHIFT() = 0 ;
	virtual int __cdecl _GetCOMPLEX_UNIT_DIP() = 0 ;
	virtual int __cdecl _GetCOMPLEX_UNIT_FRACTION() = 0 ;
	virtual int __cdecl _GetCOMPLEX_UNIT_FRACTION_PARENT() = 0 ;
	virtual int __cdecl _GetCOMPLEX_UNIT_IN() = 0 ;
	virtual int __cdecl _GetCOMPLEX_UNIT_MASK() = 0 ;
	virtual int __cdecl _GetCOMPLEX_UNIT_MM() = 0 ;
	virtual int __cdecl _GetCOMPLEX_UNIT_PT() = 0 ;
	virtual int __cdecl _GetCOMPLEX_UNIT_PX() = 0 ;
	virtual int __cdecl _GetCOMPLEX_UNIT_SHIFT() = 0 ;
	virtual int __cdecl _GetCOMPLEX_UNIT_SP() = 0 ;
	virtual int __cdecl _GetDATA_NULL_EMPTY() = 0 ;
	virtual int __cdecl _GetDATA_NULL_UNDEFINED() = 0 ;
	virtual int __cdecl _GetDENSITY_DEFAULT() = 0 ;
	virtual int __cdecl _GetDENSITY_NONE() = 0 ;
	virtual int __cdecl _GetTYPE_ATTRIBUTE() = 0 ;
	virtual int __cdecl _GetTYPE_DIMENSION() = 0 ;
	virtual int __cdecl _GetTYPE_FIRST_COLOR_INT() = 0 ;
	virtual int __cdecl _GetTYPE_FIRST_INT() = 0 ;
	virtual int __cdecl _GetTYPE_FLOAT() = 0 ;
	virtual int __cdecl _GetTYPE_FRACTION() = 0 ;
	virtual int __cdecl _GetTYPE_INT_BOOLEAN() = 0 ;
	virtual int __cdecl _GetTYPE_INT_COLOR_ARGB4() = 0 ;
	virtual int __cdecl _GetTYPE_INT_COLOR_ARGB8() = 0 ;
	virtual int __cdecl _GetTYPE_INT_COLOR_RGB4() = 0 ;
	virtual int __cdecl _GetTYPE_INT_COLOR_RGB8() = 0 ;
	virtual int __cdecl _GetTYPE_INT_DEC() = 0 ;
	virtual int __cdecl _GetTYPE_INT_HEX() = 0 ;
	virtual int __cdecl _GetTYPE_LAST_COLOR_INT() = 0 ;
	virtual int __cdecl _GetTYPE_LAST_INT() = 0 ;
	virtual int __cdecl _GetTYPE_NULL() = 0 ;
	virtual int __cdecl _GetTYPE_REFERENCE() = 0 ;
	virtual int __cdecl _GetTYPE_STRING() = 0 ;
	HIDESBASE virtual _di_JTypedValue __cdecl init() = 0 ;
	virtual float __cdecl applyDimension(int unit_, float value, _di_JDisplayMetrics metrics) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl coerceToString(int type_, int data) = 0 /* overload */;
	virtual float __cdecl complexToDimension(int data, _di_JDisplayMetrics metrics) = 0 ;
	virtual int __cdecl complexToDimensionPixelOffset(int data, _di_JDisplayMetrics metrics) = 0 ;
	virtual int __cdecl complexToDimensionPixelSize(int data, _di_JDisplayMetrics metrics) = 0 ;
	virtual float __cdecl complexToFloat(int complex) = 0 ;
	virtual float __cdecl complexToFraction(int data, float base, float pbase) = 0 ;
	__property int COMPLEX_MANTISSA_MASK = {read=_GetCOMPLEX_MANTISSA_MASK};
	__property int COMPLEX_MANTISSA_SHIFT = {read=_GetCOMPLEX_MANTISSA_SHIFT};
	__property int COMPLEX_RADIX_0p23 = {read=_GetCOMPLEX_RADIX_0p23};
	__property int COMPLEX_RADIX_16p7 = {read=_GetCOMPLEX_RADIX_16p7};
	__property int COMPLEX_RADIX_23p0 = {read=_GetCOMPLEX_RADIX_23p0};
	__property int COMPLEX_RADIX_8p15 = {read=_GetCOMPLEX_RADIX_8p15};
	__property int COMPLEX_RADIX_MASK = {read=_GetCOMPLEX_RADIX_MASK};
	__property int COMPLEX_RADIX_SHIFT = {read=_GetCOMPLEX_RADIX_SHIFT};
	__property int COMPLEX_UNIT_DIP = {read=_GetCOMPLEX_UNIT_DIP};
	__property int COMPLEX_UNIT_FRACTION = {read=_GetCOMPLEX_UNIT_FRACTION};
	__property int COMPLEX_UNIT_FRACTION_PARENT = {read=_GetCOMPLEX_UNIT_FRACTION_PARENT};
	__property int COMPLEX_UNIT_IN = {read=_GetCOMPLEX_UNIT_IN};
	__property int COMPLEX_UNIT_MASK = {read=_GetCOMPLEX_UNIT_MASK};
	__property int COMPLEX_UNIT_MM = {read=_GetCOMPLEX_UNIT_MM};
	__property int COMPLEX_UNIT_PT = {read=_GetCOMPLEX_UNIT_PT};
	__property int COMPLEX_UNIT_PX = {read=_GetCOMPLEX_UNIT_PX};
	__property int COMPLEX_UNIT_SHIFT = {read=_GetCOMPLEX_UNIT_SHIFT};
	__property int COMPLEX_UNIT_SP = {read=_GetCOMPLEX_UNIT_SP};
	__property int DATA_NULL_EMPTY = {read=_GetDATA_NULL_EMPTY};
	__property int DATA_NULL_UNDEFINED = {read=_GetDATA_NULL_UNDEFINED};
	__property int DENSITY_DEFAULT = {read=_GetDENSITY_DEFAULT};
	__property int DENSITY_NONE = {read=_GetDENSITY_NONE};
	__property int TYPE_ATTRIBUTE = {read=_GetTYPE_ATTRIBUTE};
	__property int TYPE_DIMENSION = {read=_GetTYPE_DIMENSION};
	__property int TYPE_FIRST_COLOR_INT = {read=_GetTYPE_FIRST_COLOR_INT};
	__property int TYPE_FIRST_INT = {read=_GetTYPE_FIRST_INT};
	__property int TYPE_FLOAT = {read=_GetTYPE_FLOAT};
	__property int TYPE_FRACTION = {read=_GetTYPE_FRACTION};
	__property int TYPE_INT_BOOLEAN = {read=_GetTYPE_INT_BOOLEAN};
	__property int TYPE_INT_COLOR_ARGB4 = {read=_GetTYPE_INT_COLOR_ARGB4};
	__property int TYPE_INT_COLOR_ARGB8 = {read=_GetTYPE_INT_COLOR_ARGB8};
	__property int TYPE_INT_COLOR_RGB4 = {read=_GetTYPE_INT_COLOR_RGB4};
	__property int TYPE_INT_COLOR_RGB8 = {read=_GetTYPE_INT_COLOR_RGB8};
	__property int TYPE_INT_DEC = {read=_GetTYPE_INT_DEC};
	__property int TYPE_INT_HEX = {read=_GetTYPE_INT_HEX};
	__property int TYPE_LAST_COLOR_INT = {read=_GetTYPE_LAST_COLOR_INT};
	__property int TYPE_LAST_INT = {read=_GetTYPE_LAST_INT};
	__property int TYPE_NULL = {read=_GetTYPE_NULL};
	__property int TYPE_REFERENCE = {read=_GetTYPE_REFERENCE};
	__property int TYPE_STRING = {read=_GetTYPE_STRING};
};

__interface  INTERFACE_UUID("{776A314F-EFF7-401A-A02D-7FF0AA43F435}") JTypedValue  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _GetassetCookie() = 0 ;
	virtual void __cdecl _SetassetCookie(int Value) = 0 ;
	virtual int __cdecl _GetchangingConfigurations() = 0 ;
	virtual void __cdecl _SetchangingConfigurations(int Value) = 0 ;
	virtual int __cdecl _Getdata() = 0 ;
	virtual void __cdecl _Setdata(int Value) = 0 ;
	virtual int __cdecl _Getdensity() = 0 ;
	virtual void __cdecl _Setdensity(int Value) = 0 ;
	virtual int __cdecl _GetresourceId() = 0 ;
	virtual void __cdecl _SetresourceId(int Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl _Getstring() = 0 ;
	virtual void __cdecl _Setstring(Androidapi::Jni::Javatypes::_di_JCharSequence Value) = 0 ;
	virtual int __cdecl _Gettype() = 0 ;
	virtual void __cdecl _Settype(int Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl coerceToString() = 0 /* overload */;
	virtual int __cdecl getComplexUnit() = 0 ;
	virtual float __cdecl getDimension(_di_JDisplayMetrics metrics) = 0 ;
	virtual float __cdecl getFloat() = 0 ;
	virtual float __cdecl getFraction(float base, float pbase) = 0 ;
	virtual void __cdecl setTo(_di_JTypedValue other) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	__property int assetCookie = {read=_GetassetCookie, write=_SetassetCookie};
	__property int changingConfigurations = {read=_GetchangingConfigurations, write=_SetchangingConfigurations};
	__property int data = {read=_Getdata, write=_Setdata};
	__property int density = {read=_Getdensity, write=_Setdensity};
	__property int resourceId = {read=_GetresourceId, write=_SetresourceId};
	__property Androidapi::Jni::Javatypes::_di_JCharSequence string = {read=_Getstring, write=_Setstring};
	__property int type = {read=_Gettype, write=_Settype};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTypedValue : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTypedValueClass,_di_JTypedValue>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTypedValueClass,_di_JTypedValue> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTypedValue() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTypedValueClass,_di_JTypedValue>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTypedValue() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Util */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_UTIL)
using namespace Androidapi::Jni::Util;
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
#endif	// Androidapi_Jni_UtilHPP
