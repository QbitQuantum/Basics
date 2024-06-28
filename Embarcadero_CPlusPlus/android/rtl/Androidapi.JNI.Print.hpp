// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Print.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_PrintHPP
#define Androidapi_Jni_PrintHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Print
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JPageRangeClass;
typedef System::DelphiInterface<JPageRangeClass> _di_JPageRangeClass;
__interface DELPHIINTERFACE JPageRange;
typedef System::DelphiInterface<JPageRange> _di_JPageRange;
class DELPHICLASS TJPageRange;
__interface DELPHIINTERFACE JPrintAttributesClass;
typedef System::DelphiInterface<JPrintAttributesClass> _di_JPrintAttributesClass;
__interface DELPHIINTERFACE JPrintAttributes;
typedef System::DelphiInterface<JPrintAttributes> _di_JPrintAttributes;
class DELPHICLASS TJPrintAttributes;
__interface DELPHIINTERFACE JPrintAttributes_MarginsClass;
typedef System::DelphiInterface<JPrintAttributes_MarginsClass> _di_JPrintAttributes_MarginsClass;
__interface DELPHIINTERFACE JPrintAttributes_Margins;
typedef System::DelphiInterface<JPrintAttributes_Margins> _di_JPrintAttributes_Margins;
class DELPHICLASS TJPrintAttributes_Margins;
__interface DELPHIINTERFACE JPrintAttributes_MediaSizeClass;
typedef System::DelphiInterface<JPrintAttributes_MediaSizeClass> _di_JPrintAttributes_MediaSizeClass;
__interface DELPHIINTERFACE JPrintAttributes_MediaSize;
typedef System::DelphiInterface<JPrintAttributes_MediaSize> _di_JPrintAttributes_MediaSize;
class DELPHICLASS TJPrintAttributes_MediaSize;
__interface DELPHIINTERFACE JPrintAttributes_ResolutionClass;
typedef System::DelphiInterface<JPrintAttributes_ResolutionClass> _di_JPrintAttributes_ResolutionClass;
__interface DELPHIINTERFACE JPrintAttributes_Resolution;
typedef System::DelphiInterface<JPrintAttributes_Resolution> _di_JPrintAttributes_Resolution;
class DELPHICLASS TJPrintAttributes_Resolution;
__interface DELPHIINTERFACE JPrintDocumentAdapterClass;
typedef System::DelphiInterface<JPrintDocumentAdapterClass> _di_JPrintDocumentAdapterClass;
__interface DELPHIINTERFACE JPrintDocumentAdapter;
typedef System::DelphiInterface<JPrintDocumentAdapter> _di_JPrintDocumentAdapter;
class DELPHICLASS TJPrintDocumentAdapter;
__interface DELPHIINTERFACE JPrintDocumentAdapter_LayoutResultCallbackClass;
typedef System::DelphiInterface<JPrintDocumentAdapter_LayoutResultCallbackClass> _di_JPrintDocumentAdapter_LayoutResultCallbackClass;
__interface DELPHIINTERFACE JPrintDocumentAdapter_LayoutResultCallback;
typedef System::DelphiInterface<JPrintDocumentAdapter_LayoutResultCallback> _di_JPrintDocumentAdapter_LayoutResultCallback;
class DELPHICLASS TJPrintDocumentAdapter_LayoutResultCallback;
__interface DELPHIINTERFACE JPrintDocumentAdapter_WriteResultCallbackClass;
typedef System::DelphiInterface<JPrintDocumentAdapter_WriteResultCallbackClass> _di_JPrintDocumentAdapter_WriteResultCallbackClass;
__interface DELPHIINTERFACE JPrintDocumentAdapter_WriteResultCallback;
typedef System::DelphiInterface<JPrintDocumentAdapter_WriteResultCallback> _di_JPrintDocumentAdapter_WriteResultCallback;
class DELPHICLASS TJPrintDocumentAdapter_WriteResultCallback;
__interface DELPHIINTERFACE JPrintDocumentInfoClass;
typedef System::DelphiInterface<JPrintDocumentInfoClass> _di_JPrintDocumentInfoClass;
__interface DELPHIINTERFACE JPrintDocumentInfo;
typedef System::DelphiInterface<JPrintDocumentInfo> _di_JPrintDocumentInfo;
class DELPHICLASS TJPrintDocumentInfo;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{A76D3EDD-96D1-45C5-A5C0-96617C8A2BA0}") JPageRangeClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JPageRange __cdecl _GetALL_PAGES() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JPageRange __cdecl init(int start, int end_) = 0 ;
	__property _di_JPageRange ALL_PAGES = {read=_GetALL_PAGES};
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{993626DC-F39D-4294-8A1D-7A99F074010D}") JPageRange  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual int __cdecl getEnd() = 0 ;
	virtual int __cdecl getStart() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPageRange : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPageRangeClass,_di_JPageRange>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPageRangeClass,_di_JPageRange> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPageRange() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPageRangeClass,_di_JPageRange>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPageRange() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D9B40228-CC37-4573-896E-10D7800670CE}") JPrintAttributesClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetCOLOR_MODE_COLOR() = 0 ;
	virtual int __cdecl _GetCOLOR_MODE_MONOCHROME() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetDUPLEX_MODE_LONG_EDGE() = 0 ;
	virtual int __cdecl _GetDUPLEX_MODE_NONE() = 0 ;
	virtual int __cdecl _GetDUPLEX_MODE_SHORT_EDGE() = 0 ;
	__property int COLOR_MODE_COLOR = {read=_GetCOLOR_MODE_COLOR};
	__property int COLOR_MODE_MONOCHROME = {read=_GetCOLOR_MODE_MONOCHROME};
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int DUPLEX_MODE_LONG_EDGE = {read=_GetDUPLEX_MODE_LONG_EDGE};
	__property int DUPLEX_MODE_NONE = {read=_GetDUPLEX_MODE_NONE};
	__property int DUPLEX_MODE_SHORT_EDGE = {read=_GetDUPLEX_MODE_SHORT_EDGE};
};

__interface  INTERFACE_UUID("{312C7538-43CD-4607-B8E2-04CF431C9B5B}") JPrintAttributes  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual int __cdecl getColorMode() = 0 ;
	virtual int __cdecl getDuplexMode() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl getMediaSize() = 0 ;
	virtual _di_JPrintAttributes_Margins __cdecl getMinMargins() = 0 ;
	virtual _di_JPrintAttributes_Resolution __cdecl getResolution() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPrintAttributes : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributesClass,_di_JPrintAttributes>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributesClass,_di_JPrintAttributes> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPrintAttributes() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributesClass,_di_JPrintAttributes>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPrintAttributes() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{34F23121-C582-4C7E-B04A-A8A5C782EA32}") JPrintAttributes_MarginsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JPrintAttributes_Margins __cdecl _GetNO_MARGINS() = 0 ;
	HIDESBASE virtual _di_JPrintAttributes_Margins __cdecl init(int leftMils, int topMils, int rightMils, int bottomMils) = 0 ;
	__property _di_JPrintAttributes_Margins NO_MARGINS = {read=_GetNO_MARGINS};
};

__interface  INTERFACE_UUID("{BC9FAC43-0090-4CBE-A09E-17A23A093223}") JPrintAttributes_Margins  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual int __cdecl getBottomMils() = 0 ;
	virtual int __cdecl getLeftMils() = 0 ;
	virtual int __cdecl getRightMils() = 0 ;
	virtual int __cdecl getTopMils() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPrintAttributes_Margins : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributes_MarginsClass,_di_JPrintAttributes_Margins>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributes_MarginsClass,_di_JPrintAttributes_Margins> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPrintAttributes_Margins() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributes_MarginsClass,_di_JPrintAttributes_Margins>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPrintAttributes_Margins() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0A2D852F-16AE-49A1-BCFE-E1E3E12A15C4}") JPrintAttributes_MediaSizeClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_A0() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_A1() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_A10() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_A2() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_A3() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_A4() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_A5() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_A6() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_A7() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_A8() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_A9() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_B0() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_B1() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_B10() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_B2() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_B3() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_B4() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_B5() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_B6() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_B7() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_B8() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_B9() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_C0() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_C1() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_C10() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_C2() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_C3() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_C4() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_C5() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_C6() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_C7() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_C8() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetISO_C9() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_B0() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_B1() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_B10() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_B2() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_B3() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_B4() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_B5() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_B6() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_B7() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_B8() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_B9() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJIS_EXEC() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJPN_CHOU2() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJPN_CHOU3() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJPN_CHOU4() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJPN_HAGAKI() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJPN_KAHU() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJPN_KAKU2() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJPN_OUFUKU() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetJPN_YOU4() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_FOOLSCAP() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_GOVT_LETTER() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_INDEX_3X5() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_INDEX_4X6() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_INDEX_5X8() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_JUNIOR_LEGAL() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_LEDGER() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_LEGAL() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_LETTER() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_MONARCH() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_QUARTO() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetNA_TABLOID() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetOM_DAI_PA_KAI() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetOM_JUURO_KU_KAI() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetOM_PA_KAI() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetPRC_1() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetPRC_10() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetPRC_16K() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetPRC_2() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetPRC_3() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetPRC_4() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetPRC_5() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetPRC_6() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetPRC_7() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetPRC_8() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetPRC_9() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetROC_16K() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetROC_8K() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetUNKNOWN_LANDSCAPE() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl _GetUNKNOWN_PORTRAIT() = 0 ;
	HIDESBASE virtual _di_JPrintAttributes_MediaSize __cdecl init(Androidapi::Jni::Javatypes::_di_JString id, Androidapi::Jni::Javatypes::_di_JString label_, int widthMils, int heightMils) = 0 ;
	__property _di_JPrintAttributes_MediaSize ISO_A0 = {read=_GetISO_A0};
	__property _di_JPrintAttributes_MediaSize ISO_A1 = {read=_GetISO_A1};
	__property _di_JPrintAttributes_MediaSize ISO_A10 = {read=_GetISO_A10};
	__property _di_JPrintAttributes_MediaSize ISO_A2 = {read=_GetISO_A2};
	__property _di_JPrintAttributes_MediaSize ISO_A3 = {read=_GetISO_A3};
	__property _di_JPrintAttributes_MediaSize ISO_A4 = {read=_GetISO_A4};
	__property _di_JPrintAttributes_MediaSize ISO_A5 = {read=_GetISO_A5};
	__property _di_JPrintAttributes_MediaSize ISO_A6 = {read=_GetISO_A6};
	__property _di_JPrintAttributes_MediaSize ISO_A7 = {read=_GetISO_A7};
	__property _di_JPrintAttributes_MediaSize ISO_A8 = {read=_GetISO_A8};
	__property _di_JPrintAttributes_MediaSize ISO_A9 = {read=_GetISO_A9};
	__property _di_JPrintAttributes_MediaSize ISO_B0 = {read=_GetISO_B0};
	__property _di_JPrintAttributes_MediaSize ISO_B1 = {read=_GetISO_B1};
	__property _di_JPrintAttributes_MediaSize ISO_B10 = {read=_GetISO_B10};
	__property _di_JPrintAttributes_MediaSize ISO_B2 = {read=_GetISO_B2};
	__property _di_JPrintAttributes_MediaSize ISO_B3 = {read=_GetISO_B3};
	__property _di_JPrintAttributes_MediaSize ISO_B4 = {read=_GetISO_B4};
	__property _di_JPrintAttributes_MediaSize ISO_B5 = {read=_GetISO_B5};
	__property _di_JPrintAttributes_MediaSize ISO_B6 = {read=_GetISO_B6};
	__property _di_JPrintAttributes_MediaSize ISO_B7 = {read=_GetISO_B7};
	__property _di_JPrintAttributes_MediaSize ISO_B8 = {read=_GetISO_B8};
	__property _di_JPrintAttributes_MediaSize ISO_B9 = {read=_GetISO_B9};
	__property _di_JPrintAttributes_MediaSize ISO_C0 = {read=_GetISO_C0};
	__property _di_JPrintAttributes_MediaSize ISO_C1 = {read=_GetISO_C1};
	__property _di_JPrintAttributes_MediaSize ISO_C10 = {read=_GetISO_C10};
	__property _di_JPrintAttributes_MediaSize ISO_C2 = {read=_GetISO_C2};
	__property _di_JPrintAttributes_MediaSize ISO_C3 = {read=_GetISO_C3};
	__property _di_JPrintAttributes_MediaSize ISO_C4 = {read=_GetISO_C4};
	__property _di_JPrintAttributes_MediaSize ISO_C5 = {read=_GetISO_C5};
	__property _di_JPrintAttributes_MediaSize ISO_C6 = {read=_GetISO_C6};
	__property _di_JPrintAttributes_MediaSize ISO_C7 = {read=_GetISO_C7};
	__property _di_JPrintAttributes_MediaSize ISO_C8 = {read=_GetISO_C8};
	__property _di_JPrintAttributes_MediaSize ISO_C9 = {read=_GetISO_C9};
	__property _di_JPrintAttributes_MediaSize JIS_B0 = {read=_GetJIS_B0};
	__property _di_JPrintAttributes_MediaSize JIS_B1 = {read=_GetJIS_B1};
	__property _di_JPrintAttributes_MediaSize JIS_B10 = {read=_GetJIS_B10};
	__property _di_JPrintAttributes_MediaSize JIS_B2 = {read=_GetJIS_B2};
	__property _di_JPrintAttributes_MediaSize JIS_B3 = {read=_GetJIS_B3};
	__property _di_JPrintAttributes_MediaSize JIS_B4 = {read=_GetJIS_B4};
	__property _di_JPrintAttributes_MediaSize JIS_B5 = {read=_GetJIS_B5};
	__property _di_JPrintAttributes_MediaSize JIS_B6 = {read=_GetJIS_B6};
	__property _di_JPrintAttributes_MediaSize JIS_B7 = {read=_GetJIS_B7};
	__property _di_JPrintAttributes_MediaSize JIS_B8 = {read=_GetJIS_B8};
	__property _di_JPrintAttributes_MediaSize JIS_B9 = {read=_GetJIS_B9};
	__property _di_JPrintAttributes_MediaSize JIS_EXEC = {read=_GetJIS_EXEC};
	__property _di_JPrintAttributes_MediaSize JPN_CHOU2 = {read=_GetJPN_CHOU2};
	__property _di_JPrintAttributes_MediaSize JPN_CHOU3 = {read=_GetJPN_CHOU3};
	__property _di_JPrintAttributes_MediaSize JPN_CHOU4 = {read=_GetJPN_CHOU4};
	__property _di_JPrintAttributes_MediaSize JPN_HAGAKI = {read=_GetJPN_HAGAKI};
	__property _di_JPrintAttributes_MediaSize JPN_KAHU = {read=_GetJPN_KAHU};
	__property _di_JPrintAttributes_MediaSize JPN_KAKU2 = {read=_GetJPN_KAKU2};
	__property _di_JPrintAttributes_MediaSize JPN_OUFUKU = {read=_GetJPN_OUFUKU};
	__property _di_JPrintAttributes_MediaSize JPN_YOU4 = {read=_GetJPN_YOU4};
	__property _di_JPrintAttributes_MediaSize NA_FOOLSCAP = {read=_GetNA_FOOLSCAP};
	__property _di_JPrintAttributes_MediaSize NA_GOVT_LETTER = {read=_GetNA_GOVT_LETTER};
	__property _di_JPrintAttributes_MediaSize NA_INDEX_3X5 = {read=_GetNA_INDEX_3X5};
	__property _di_JPrintAttributes_MediaSize NA_INDEX_4X6 = {read=_GetNA_INDEX_4X6};
	__property _di_JPrintAttributes_MediaSize NA_INDEX_5X8 = {read=_GetNA_INDEX_5X8};
	__property _di_JPrintAttributes_MediaSize NA_JUNIOR_LEGAL = {read=_GetNA_JUNIOR_LEGAL};
	__property _di_JPrintAttributes_MediaSize NA_LEDGER = {read=_GetNA_LEDGER};
	__property _di_JPrintAttributes_MediaSize NA_LEGAL = {read=_GetNA_LEGAL};
	__property _di_JPrintAttributes_MediaSize NA_LETTER = {read=_GetNA_LETTER};
	__property _di_JPrintAttributes_MediaSize NA_MONARCH = {read=_GetNA_MONARCH};
	__property _di_JPrintAttributes_MediaSize NA_QUARTO = {read=_GetNA_QUARTO};
	__property _di_JPrintAttributes_MediaSize NA_TABLOID = {read=_GetNA_TABLOID};
	__property _di_JPrintAttributes_MediaSize OM_DAI_PA_KAI = {read=_GetOM_DAI_PA_KAI};
	__property _di_JPrintAttributes_MediaSize OM_JUURO_KU_KAI = {read=_GetOM_JUURO_KU_KAI};
	__property _di_JPrintAttributes_MediaSize OM_PA_KAI = {read=_GetOM_PA_KAI};
	__property _di_JPrintAttributes_MediaSize PRC_1 = {read=_GetPRC_1};
	__property _di_JPrintAttributes_MediaSize PRC_10 = {read=_GetPRC_10};
	__property _di_JPrintAttributes_MediaSize PRC_16K = {read=_GetPRC_16K};
	__property _di_JPrintAttributes_MediaSize PRC_2 = {read=_GetPRC_2};
	__property _di_JPrintAttributes_MediaSize PRC_3 = {read=_GetPRC_3};
	__property _di_JPrintAttributes_MediaSize PRC_4 = {read=_GetPRC_4};
	__property _di_JPrintAttributes_MediaSize PRC_5 = {read=_GetPRC_5};
	__property _di_JPrintAttributes_MediaSize PRC_6 = {read=_GetPRC_6};
	__property _di_JPrintAttributes_MediaSize PRC_7 = {read=_GetPRC_7};
	__property _di_JPrintAttributes_MediaSize PRC_8 = {read=_GetPRC_8};
	__property _di_JPrintAttributes_MediaSize PRC_9 = {read=_GetPRC_9};
	__property _di_JPrintAttributes_MediaSize ROC_16K = {read=_GetROC_16K};
	__property _di_JPrintAttributes_MediaSize ROC_8K = {read=_GetROC_8K};
	__property _di_JPrintAttributes_MediaSize UNKNOWN_LANDSCAPE = {read=_GetUNKNOWN_LANDSCAPE};
	__property _di_JPrintAttributes_MediaSize UNKNOWN_PORTRAIT = {read=_GetUNKNOWN_PORTRAIT};
};

__interface  INTERFACE_UUID("{1F95EC3E-8188-4438-8575-C44CABB52DE5}") JPrintAttributes_MediaSize  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JPrintAttributes_MediaSize __cdecl asLandscape() = 0 ;
	virtual _di_JPrintAttributes_MediaSize __cdecl asPortrait() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual int __cdecl getHeightMils() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getLabel(Androidapi::Jni::Graphicscontentviewtext::_di_JPackageManager packageManager) = 0 ;
	virtual int __cdecl getWidthMils() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isPortrait() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPrintAttributes_MediaSize : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributes_MediaSizeClass,_di_JPrintAttributes_MediaSize>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributes_MediaSizeClass,_di_JPrintAttributes_MediaSize> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPrintAttributes_MediaSize() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributes_MediaSizeClass,_di_JPrintAttributes_MediaSize>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPrintAttributes_MediaSize() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{146C3EA6-7D12-4BAE-9EBE-48DC56B9527A}") JPrintAttributes_ResolutionClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JPrintAttributes_Resolution __cdecl init(Androidapi::Jni::Javatypes::_di_JString id, Androidapi::Jni::Javatypes::_di_JString label_, int horizontalDpi, int verticalDpi) = 0 ;
};

__interface  INTERFACE_UUID("{9794DA8E-7288-47F0-9D7E-EEEBFD6DE459}") JPrintAttributes_Resolution  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual int __cdecl getHorizontalDpi() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getLabel() = 0 ;
	virtual int __cdecl getVerticalDpi() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPrintAttributes_Resolution : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributes_ResolutionClass,_di_JPrintAttributes_Resolution>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributes_ResolutionClass,_di_JPrintAttributes_Resolution> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPrintAttributes_Resolution() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintAttributes_ResolutionClass,_di_JPrintAttributes_Resolution>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPrintAttributes_Resolution() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9E14C8BC-810E-4BEA-9635-AA79DA6D3476}") JPrintDocumentAdapterClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PRINT_PREVIEW() = 0 ;
	HIDESBASE virtual _di_JPrintDocumentAdapter __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PRINT_PREVIEW = {read=_GetEXTRA_PRINT_PREVIEW};
};

__interface  INTERFACE_UUID("{CE4783E1-D54F-46FA-B2DC-DB65A20DC786}") JPrintDocumentAdapter  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onFinish() = 0 ;
	virtual void __cdecl onLayout(_di_JPrintAttributes oldAttributes, _di_JPrintAttributes newAttributes, Androidapi::Jni::Os::_di_JCancellationSignal cancellationSignal, _di_JPrintDocumentAdapter_LayoutResultCallback callback, Androidapi::Jni::Os::_di_JBundle extras) = 0 ;
	virtual void __cdecl onStart() = 0 ;
	virtual void __cdecl onWrite(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JPageRange>* pages, Androidapi::Jni::Os::_di_JParcelFileDescriptor destination, Androidapi::Jni::Os::_di_JCancellationSignal cancellationSignal, _di_JPrintDocumentAdapter_WriteResultCallback callback) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPrintDocumentAdapter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentAdapterClass,_di_JPrintDocumentAdapter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentAdapterClass,_di_JPrintDocumentAdapter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPrintDocumentAdapter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentAdapterClass,_di_JPrintDocumentAdapter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPrintDocumentAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C44B2E02-5437-43D0-9F54-8F506EE5660B}") JPrintDocumentAdapter_LayoutResultCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D9ABC6EE-5D92-4E8A-9CA2-E850A27A3BB4}") JPrintDocumentAdapter_LayoutResultCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onLayoutCancelled() = 0 ;
	virtual void __cdecl onLayoutFailed(Androidapi::Jni::Javatypes::_di_JCharSequence error) = 0 ;
	virtual void __cdecl onLayoutFinished(_di_JPrintDocumentInfo info, bool changed) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPrintDocumentAdapter_LayoutResultCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentAdapter_LayoutResultCallbackClass,_di_JPrintDocumentAdapter_LayoutResultCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentAdapter_LayoutResultCallbackClass,_di_JPrintDocumentAdapter_LayoutResultCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPrintDocumentAdapter_LayoutResultCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentAdapter_LayoutResultCallbackClass,_di_JPrintDocumentAdapter_LayoutResultCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPrintDocumentAdapter_LayoutResultCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8B73ACF7-C9BE-4AE0-B4B4-E2270D42E96D}") JPrintDocumentAdapter_WriteResultCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{03B2AB6A-49E7-4131-AFB7-AB8ABC85075F}") JPrintDocumentAdapter_WriteResultCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onWriteCancelled() = 0 ;
	virtual void __cdecl onWriteFailed(Androidapi::Jni::Javatypes::_di_JCharSequence error) = 0 ;
	virtual void __cdecl onWriteFinished(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JPageRange>* pages) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPrintDocumentAdapter_WriteResultCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentAdapter_WriteResultCallbackClass,_di_JPrintDocumentAdapter_WriteResultCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentAdapter_WriteResultCallbackClass,_di_JPrintDocumentAdapter_WriteResultCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPrintDocumentAdapter_WriteResultCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentAdapter_WriteResultCallbackClass,_di_JPrintDocumentAdapter_WriteResultCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPrintDocumentAdapter_WriteResultCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F28BED16-94C8-421E-B074-52BA163A27FD}") JPrintDocumentInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetCONTENT_TYPE_DOCUMENT() = 0 ;
	virtual int __cdecl _GetCONTENT_TYPE_PHOTO() = 0 ;
	virtual int __cdecl _GetCONTENT_TYPE_UNKNOWN() = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetPAGE_COUNT_UNKNOWN() = 0 ;
	__property int CONTENT_TYPE_DOCUMENT = {read=_GetCONTENT_TYPE_DOCUMENT};
	__property int CONTENT_TYPE_PHOTO = {read=_GetCONTENT_TYPE_PHOTO};
	__property int CONTENT_TYPE_UNKNOWN = {read=_GetCONTENT_TYPE_UNKNOWN};
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int PAGE_COUNT_UNKNOWN = {read=_GetPAGE_COUNT_UNKNOWN};
};

__interface  INTERFACE_UUID("{B4C4BC34-EC66-414B-AA0C-8193C7A5C592}") JPrintDocumentInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual int __cdecl getContentType() = 0 ;
	virtual __int64 __cdecl getDataSize() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual int __cdecl getPageCount() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel parcel, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPrintDocumentInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentInfoClass,_di_JPrintDocumentInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentInfoClass,_di_JPrintDocumentInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPrintDocumentInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPrintDocumentInfoClass,_di_JPrintDocumentInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPrintDocumentInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Print */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_PRINT)
using namespace Androidapi::Jni::Print;
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
#endif	// Androidapi_Jni_PrintHPP
