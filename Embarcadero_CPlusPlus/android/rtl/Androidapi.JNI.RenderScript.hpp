// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.RenderScript.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_RenderscriptHPP
#define Androidapi_Jni_RenderscriptHPP

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
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Renderscript
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JBaseObjClass;
typedef System::DelphiInterface<JBaseObjClass> _di_JBaseObjClass;
__interface DELPHIINTERFACE JBaseObj;
typedef System::DelphiInterface<JBaseObj> _di_JBaseObj;
class DELPHICLASS TJBaseObj;
__interface DELPHIINTERFACE JAllocationClass;
typedef System::DelphiInterface<JAllocationClass> _di_JAllocationClass;
__interface DELPHIINTERFACE JAllocation;
typedef System::DelphiInterface<JAllocation> _di_JAllocation;
class DELPHICLASS TJAllocation;
__interface DELPHIINTERFACE JAllocation_MipmapControlClass;
typedef System::DelphiInterface<JAllocation_MipmapControlClass> _di_JAllocation_MipmapControlClass;
__interface DELPHIINTERFACE JAllocation_MipmapControl;
typedef System::DelphiInterface<JAllocation_MipmapControl> _di_JAllocation_MipmapControl;
class DELPHICLASS TJAllocation_MipmapControl;
__interface DELPHIINTERFACE JAllocation_OnBufferAvailableListenerClass;
typedef System::DelphiInterface<JAllocation_OnBufferAvailableListenerClass> _di_JAllocation_OnBufferAvailableListenerClass;
__interface DELPHIINTERFACE JAllocation_OnBufferAvailableListener;
typedef System::DelphiInterface<JAllocation_OnBufferAvailableListener> _di_JAllocation_OnBufferAvailableListener;
class DELPHICLASS TJAllocation_OnBufferAvailableListener;
__interface DELPHIINTERFACE JAllocationAdapterClass;
typedef System::DelphiInterface<JAllocationAdapterClass> _di_JAllocationAdapterClass;
__interface DELPHIINTERFACE JAllocationAdapter;
typedef System::DelphiInterface<JAllocationAdapter> _di_JAllocationAdapter;
class DELPHICLASS TJAllocationAdapter;
__interface DELPHIINTERFACE JByte2Class;
typedef System::DelphiInterface<JByte2Class> _di_JByte2Class;
__interface DELPHIINTERFACE JByte2;
typedef System::DelphiInterface<JByte2> _di_JByte2;
class DELPHICLASS TJByte2;
__interface DELPHIINTERFACE JByte3Class;
typedef System::DelphiInterface<JByte3Class> _di_JByte3Class;
__interface DELPHIINTERFACE JByte3;
typedef System::DelphiInterface<JByte3> _di_JByte3;
class DELPHICLASS TJByte3;
__interface DELPHIINTERFACE JByte4Class;
typedef System::DelphiInterface<JByte4Class> _di_JByte4Class;
__interface DELPHIINTERFACE JByte4;
typedef System::DelphiInterface<JByte4> _di_JByte4;
class DELPHICLASS TJByte4;
__interface DELPHIINTERFACE JDouble2Class;
typedef System::DelphiInterface<JDouble2Class> _di_JDouble2Class;
__interface DELPHIINTERFACE JDouble2;
typedef System::DelphiInterface<JDouble2> _di_JDouble2;
class DELPHICLASS TJDouble2;
__interface DELPHIINTERFACE JDouble3Class;
typedef System::DelphiInterface<JDouble3Class> _di_JDouble3Class;
__interface DELPHIINTERFACE JDouble3;
typedef System::DelphiInterface<JDouble3> _di_JDouble3;
class DELPHICLASS TJDouble3;
__interface DELPHIINTERFACE JDouble4Class;
typedef System::DelphiInterface<JDouble4Class> _di_JDouble4Class;
__interface DELPHIINTERFACE JDouble4;
typedef System::DelphiInterface<JDouble4> _di_JDouble4;
class DELPHICLASS TJDouble4;
__interface DELPHIINTERFACE Jrenderscript_ElementClass;
typedef System::DelphiInterface<Jrenderscript_ElementClass> _di_Jrenderscript_ElementClass;
__interface DELPHIINTERFACE Jrenderscript_Element;
typedef System::DelphiInterface<Jrenderscript_Element> _di_Jrenderscript_Element;
class DELPHICLASS TJrenderscript_Element;
__interface DELPHIINTERFACE JElement_BuilderClass;
typedef System::DelphiInterface<JElement_BuilderClass> _di_JElement_BuilderClass;
__interface DELPHIINTERFACE JElement_Builder;
typedef System::DelphiInterface<JElement_Builder> _di_JElement_Builder;
class DELPHICLASS TJElement_Builder;
__interface DELPHIINTERFACE JElement_DataKindClass;
typedef System::DelphiInterface<JElement_DataKindClass> _di_JElement_DataKindClass;
__interface DELPHIINTERFACE JElement_DataKind;
typedef System::DelphiInterface<JElement_DataKind> _di_JElement_DataKind;
class DELPHICLASS TJElement_DataKind;
__interface DELPHIINTERFACE JElement_DataTypeClass;
typedef System::DelphiInterface<JElement_DataTypeClass> _di_JElement_DataTypeClass;
__interface DELPHIINTERFACE JElement_DataType;
typedef System::DelphiInterface<JElement_DataType> _di_JElement_DataType;
class DELPHICLASS TJElement_DataType;
__interface DELPHIINTERFACE JFieldPackerClass;
typedef System::DelphiInterface<JFieldPackerClass> _di_JFieldPackerClass;
__interface DELPHIINTERFACE JFieldPacker;
typedef System::DelphiInterface<JFieldPacker> _di_JFieldPacker;
class DELPHICLASS TJFieldPacker;
__interface DELPHIINTERFACE JFloat2Class;
typedef System::DelphiInterface<JFloat2Class> _di_JFloat2Class;
__interface DELPHIINTERFACE JFloat2;
typedef System::DelphiInterface<JFloat2> _di_JFloat2;
class DELPHICLASS TJFloat2;
__interface DELPHIINTERFACE JFloat3Class;
typedef System::DelphiInterface<JFloat3Class> _di_JFloat3Class;
__interface DELPHIINTERFACE JFloat3;
typedef System::DelphiInterface<JFloat3> _di_JFloat3;
class DELPHICLASS TJFloat3;
__interface DELPHIINTERFACE JFloat4Class;
typedef System::DelphiInterface<JFloat4Class> _di_JFloat4Class;
__interface DELPHIINTERFACE JFloat4;
typedef System::DelphiInterface<JFloat4> _di_JFloat4;
class DELPHICLASS TJFloat4;
__interface DELPHIINTERFACE JInt2Class;
typedef System::DelphiInterface<JInt2Class> _di_JInt2Class;
__interface DELPHIINTERFACE JInt2;
typedef System::DelphiInterface<JInt2> _di_JInt2;
class DELPHICLASS TJInt2;
__interface DELPHIINTERFACE JInt3Class;
typedef System::DelphiInterface<JInt3Class> _di_JInt3Class;
__interface DELPHIINTERFACE JInt3;
typedef System::DelphiInterface<JInt3> _di_JInt3;
class DELPHICLASS TJInt3;
__interface DELPHIINTERFACE JInt4Class;
typedef System::DelphiInterface<JInt4Class> _di_JInt4Class;
__interface DELPHIINTERFACE JInt4;
typedef System::DelphiInterface<JInt4> _di_JInt4;
class DELPHICLASS TJInt4;
__interface DELPHIINTERFACE JLong2Class;
typedef System::DelphiInterface<JLong2Class> _di_JLong2Class;
__interface DELPHIINTERFACE JLong2;
typedef System::DelphiInterface<JLong2> _di_JLong2;
class DELPHICLASS TJLong2;
__interface DELPHIINTERFACE JLong3Class;
typedef System::DelphiInterface<JLong3Class> _di_JLong3Class;
__interface DELPHIINTERFACE JLong3;
typedef System::DelphiInterface<JLong3> _di_JLong3;
class DELPHICLASS TJLong3;
__interface DELPHIINTERFACE JLong4Class;
typedef System::DelphiInterface<JLong4Class> _di_JLong4Class;
__interface DELPHIINTERFACE JLong4;
typedef System::DelphiInterface<JLong4> _di_JLong4;
class DELPHICLASS TJLong4;
__interface DELPHIINTERFACE JMatrix2fClass;
typedef System::DelphiInterface<JMatrix2fClass> _di_JMatrix2fClass;
__interface DELPHIINTERFACE JMatrix2f;
typedef System::DelphiInterface<JMatrix2f> _di_JMatrix2f;
class DELPHICLASS TJMatrix2f;
__interface DELPHIINTERFACE JMatrix3fClass;
typedef System::DelphiInterface<JMatrix3fClass> _di_JMatrix3fClass;
__interface DELPHIINTERFACE JMatrix3f;
typedef System::DelphiInterface<JMatrix3f> _di_JMatrix3f;
class DELPHICLASS TJMatrix3f;
__interface DELPHIINTERFACE JMatrix4fClass;
typedef System::DelphiInterface<JMatrix4fClass> _di_JMatrix4fClass;
__interface DELPHIINTERFACE JMatrix4f;
typedef System::DelphiInterface<JMatrix4f> _di_JMatrix4f;
class DELPHICLASS TJMatrix4f;
__interface DELPHIINTERFACE JRSRuntimeExceptionClass;
typedef System::DelphiInterface<JRSRuntimeExceptionClass> _di_JRSRuntimeExceptionClass;
__interface DELPHIINTERFACE JRSRuntimeException;
typedef System::DelphiInterface<JRSRuntimeException> _di_JRSRuntimeException;
class DELPHICLASS TJRSRuntimeException;
__interface DELPHIINTERFACE JRSDriverExceptionClass;
typedef System::DelphiInterface<JRSDriverExceptionClass> _di_JRSDriverExceptionClass;
__interface DELPHIINTERFACE JRSDriverException;
typedef System::DelphiInterface<JRSDriverException> _di_JRSDriverException;
class DELPHICLASS TJRSDriverException;
__interface DELPHIINTERFACE JRSIllegalArgumentExceptionClass;
typedef System::DelphiInterface<JRSIllegalArgumentExceptionClass> _di_JRSIllegalArgumentExceptionClass;
__interface DELPHIINTERFACE JRSIllegalArgumentException;
typedef System::DelphiInterface<JRSIllegalArgumentException> _di_JRSIllegalArgumentException;
class DELPHICLASS TJRSIllegalArgumentException;
__interface DELPHIINTERFACE JRSInvalidStateExceptionClass;
typedef System::DelphiInterface<JRSInvalidStateExceptionClass> _di_JRSInvalidStateExceptionClass;
__interface DELPHIINTERFACE JRSInvalidStateException;
typedef System::DelphiInterface<JRSInvalidStateException> _di_JRSInvalidStateException;
class DELPHICLASS TJRSInvalidStateException;
__interface DELPHIINTERFACE JRenderScriptClass;
typedef System::DelphiInterface<JRenderScriptClass> _di_JRenderScriptClass;
__interface DELPHIINTERFACE JRenderScript;
typedef System::DelphiInterface<JRenderScript> _di_JRenderScript;
class DELPHICLASS TJRenderScript;
__interface DELPHIINTERFACE JRenderScript_ContextTypeClass;
typedef System::DelphiInterface<JRenderScript_ContextTypeClass> _di_JRenderScript_ContextTypeClass;
__interface DELPHIINTERFACE JRenderScript_ContextType;
typedef System::DelphiInterface<JRenderScript_ContextType> _di_JRenderScript_ContextType;
class DELPHICLASS TJRenderScript_ContextType;
__interface DELPHIINTERFACE JRenderScript_PriorityClass;
typedef System::DelphiInterface<JRenderScript_PriorityClass> _di_JRenderScript_PriorityClass;
__interface DELPHIINTERFACE JRenderScript_Priority;
typedef System::DelphiInterface<JRenderScript_Priority> _di_JRenderScript_Priority;
class DELPHICLASS TJRenderScript_Priority;
__interface DELPHIINTERFACE JRenderScript_RSErrorHandlerClass;
typedef System::DelphiInterface<JRenderScript_RSErrorHandlerClass> _di_JRenderScript_RSErrorHandlerClass;
__interface DELPHIINTERFACE JRenderScript_RSErrorHandler;
typedef System::DelphiInterface<JRenderScript_RSErrorHandler> _di_JRenderScript_RSErrorHandler;
class DELPHICLASS TJRenderScript_RSErrorHandler;
__interface DELPHIINTERFACE JRenderScript_RSMessageHandlerClass;
typedef System::DelphiInterface<JRenderScript_RSMessageHandlerClass> _di_JRenderScript_RSMessageHandlerClass;
__interface DELPHIINTERFACE JRenderScript_RSMessageHandler;
typedef System::DelphiInterface<JRenderScript_RSMessageHandler> _di_JRenderScript_RSMessageHandler;
class DELPHICLASS TJRenderScript_RSMessageHandler;
__interface DELPHIINTERFACE JSamplerClass;
typedef System::DelphiInterface<JSamplerClass> _di_JSamplerClass;
__interface DELPHIINTERFACE JSampler;
typedef System::DelphiInterface<JSampler> _di_JSampler;
class DELPHICLASS TJSampler;
__interface DELPHIINTERFACE JSampler_BuilderClass;
typedef System::DelphiInterface<JSampler_BuilderClass> _di_JSampler_BuilderClass;
__interface DELPHIINTERFACE JSampler_Builder;
typedef System::DelphiInterface<JSampler_Builder> _di_JSampler_Builder;
class DELPHICLASS TJSampler_Builder;
__interface DELPHIINTERFACE JSampler_ValueClass;
typedef System::DelphiInterface<JSampler_ValueClass> _di_JSampler_ValueClass;
__interface DELPHIINTERFACE JSampler_Value;
typedef System::DelphiInterface<JSampler_Value> _di_JSampler_Value;
class DELPHICLASS TJSampler_Value;
__interface DELPHIINTERFACE JScriptClass;
typedef System::DelphiInterface<JScriptClass> _di_JScriptClass;
__interface DELPHIINTERFACE JScript;
typedef System::DelphiInterface<JScript> _di_JScript;
class DELPHICLASS TJScript;
__interface DELPHIINTERFACE JScript_BuilderClass;
typedef System::DelphiInterface<JScript_BuilderClass> _di_JScript_BuilderClass;
__interface DELPHIINTERFACE JScript_Builder;
typedef System::DelphiInterface<JScript_Builder> _di_JScript_Builder;
class DELPHICLASS TJScript_Builder;
__interface DELPHIINTERFACE JScript_FieldBaseClass;
typedef System::DelphiInterface<JScript_FieldBaseClass> _di_JScript_FieldBaseClass;
__interface DELPHIINTERFACE JScript_FieldBase;
typedef System::DelphiInterface<JScript_FieldBase> _di_JScript_FieldBase;
class DELPHICLASS TJScript_FieldBase;
__interface DELPHIINTERFACE JScript_FieldIDClass;
typedef System::DelphiInterface<JScript_FieldIDClass> _di_JScript_FieldIDClass;
__interface DELPHIINTERFACE JScript_FieldID;
typedef System::DelphiInterface<JScript_FieldID> _di_JScript_FieldID;
class DELPHICLASS TJScript_FieldID;
__interface DELPHIINTERFACE JScript_InvokeIDClass;
typedef System::DelphiInterface<JScript_InvokeIDClass> _di_JScript_InvokeIDClass;
__interface DELPHIINTERFACE JScript_InvokeID;
typedef System::DelphiInterface<JScript_InvokeID> _di_JScript_InvokeID;
class DELPHICLASS TJScript_InvokeID;
__interface DELPHIINTERFACE JScript_KernelIDClass;
typedef System::DelphiInterface<JScript_KernelIDClass> _di_JScript_KernelIDClass;
__interface DELPHIINTERFACE JScript_KernelID;
typedef System::DelphiInterface<JScript_KernelID> _di_JScript_KernelID;
class DELPHICLASS TJScript_KernelID;
__interface DELPHIINTERFACE JScript_LaunchOptionsClass;
typedef System::DelphiInterface<JScript_LaunchOptionsClass> _di_JScript_LaunchOptionsClass;
__interface DELPHIINTERFACE JScript_LaunchOptions;
typedef System::DelphiInterface<JScript_LaunchOptions> _di_JScript_LaunchOptions;
class DELPHICLASS TJScript_LaunchOptions;
__interface DELPHIINTERFACE JScriptCClass;
typedef System::DelphiInterface<JScriptCClass> _di_JScriptCClass;
__interface DELPHIINTERFACE JScriptC;
typedef System::DelphiInterface<JScriptC> _di_JScriptC;
class DELPHICLASS TJScriptC;
__interface DELPHIINTERFACE JScriptGroupClass;
typedef System::DelphiInterface<JScriptGroupClass> _di_JScriptGroupClass;
__interface DELPHIINTERFACE JScriptGroup;
typedef System::DelphiInterface<JScriptGroup> _di_JScriptGroup;
class DELPHICLASS TJScriptGroup;
__interface DELPHIINTERFACE JScriptGroup_BindingClass;
typedef System::DelphiInterface<JScriptGroup_BindingClass> _di_JScriptGroup_BindingClass;
__interface DELPHIINTERFACE JScriptGroup_Binding;
typedef System::DelphiInterface<JScriptGroup_Binding> _di_JScriptGroup_Binding;
class DELPHICLASS TJScriptGroup_Binding;
__interface DELPHIINTERFACE JScriptGroup_BuilderClass;
typedef System::DelphiInterface<JScriptGroup_BuilderClass> _di_JScriptGroup_BuilderClass;
__interface DELPHIINTERFACE JScriptGroup_Builder;
typedef System::DelphiInterface<JScriptGroup_Builder> _di_JScriptGroup_Builder;
class DELPHICLASS TJScriptGroup_Builder;
__interface DELPHIINTERFACE JScriptGroup_Builder2Class;
typedef System::DelphiInterface<JScriptGroup_Builder2Class> _di_JScriptGroup_Builder2Class;
__interface DELPHIINTERFACE JScriptGroup_Builder2;
typedef System::DelphiInterface<JScriptGroup_Builder2> _di_JScriptGroup_Builder2;
class DELPHICLASS TJScriptGroup_Builder2;
__interface DELPHIINTERFACE JScriptGroup_ClosureClass;
typedef System::DelphiInterface<JScriptGroup_ClosureClass> _di_JScriptGroup_ClosureClass;
__interface DELPHIINTERFACE JScriptGroup_Closure;
typedef System::DelphiInterface<JScriptGroup_Closure> _di_JScriptGroup_Closure;
class DELPHICLASS TJScriptGroup_Closure;
__interface DELPHIINTERFACE JScriptGroup_FutureClass;
typedef System::DelphiInterface<JScriptGroup_FutureClass> _di_JScriptGroup_FutureClass;
__interface DELPHIINTERFACE JScriptGroup_Future;
typedef System::DelphiInterface<JScriptGroup_Future> _di_JScriptGroup_Future;
class DELPHICLASS TJScriptGroup_Future;
__interface DELPHIINTERFACE JScriptGroup_InputClass;
typedef System::DelphiInterface<JScriptGroup_InputClass> _di_JScriptGroup_InputClass;
__interface DELPHIINTERFACE JScriptGroup_Input;
typedef System::DelphiInterface<JScriptGroup_Input> _di_JScriptGroup_Input;
class DELPHICLASS TJScriptGroup_Input;
__interface DELPHIINTERFACE JScriptIntrinsicClass;
typedef System::DelphiInterface<JScriptIntrinsicClass> _di_JScriptIntrinsicClass;
__interface DELPHIINTERFACE JScriptIntrinsic;
typedef System::DelphiInterface<JScriptIntrinsic> _di_JScriptIntrinsic;
class DELPHICLASS TJScriptIntrinsic;
__interface DELPHIINTERFACE JScriptIntrinsic3DLUTClass;
typedef System::DelphiInterface<JScriptIntrinsic3DLUTClass> _di_JScriptIntrinsic3DLUTClass;
__interface DELPHIINTERFACE JScriptIntrinsic3DLUT;
typedef System::DelphiInterface<JScriptIntrinsic3DLUT> _di_JScriptIntrinsic3DLUT;
class DELPHICLASS TJScriptIntrinsic3DLUT;
__interface DELPHIINTERFACE JScriptIntrinsicBLASClass;
typedef System::DelphiInterface<JScriptIntrinsicBLASClass> _di_JScriptIntrinsicBLASClass;
__interface DELPHIINTERFACE JScriptIntrinsicBLAS;
typedef System::DelphiInterface<JScriptIntrinsicBLAS> _di_JScriptIntrinsicBLAS;
class DELPHICLASS TJScriptIntrinsicBLAS;
__interface DELPHIINTERFACE JScriptIntrinsicBlendClass;
typedef System::DelphiInterface<JScriptIntrinsicBlendClass> _di_JScriptIntrinsicBlendClass;
__interface DELPHIINTERFACE JScriptIntrinsicBlend;
typedef System::DelphiInterface<JScriptIntrinsicBlend> _di_JScriptIntrinsicBlend;
class DELPHICLASS TJScriptIntrinsicBlend;
__interface DELPHIINTERFACE JScriptIntrinsicBlurClass;
typedef System::DelphiInterface<JScriptIntrinsicBlurClass> _di_JScriptIntrinsicBlurClass;
__interface DELPHIINTERFACE JScriptIntrinsicBlur;
typedef System::DelphiInterface<JScriptIntrinsicBlur> _di_JScriptIntrinsicBlur;
class DELPHICLASS TJScriptIntrinsicBlur;
__interface DELPHIINTERFACE JScriptIntrinsicColorMatrixClass;
typedef System::DelphiInterface<JScriptIntrinsicColorMatrixClass> _di_JScriptIntrinsicColorMatrixClass;
__interface DELPHIINTERFACE JScriptIntrinsicColorMatrix;
typedef System::DelphiInterface<JScriptIntrinsicColorMatrix> _di_JScriptIntrinsicColorMatrix;
class DELPHICLASS TJScriptIntrinsicColorMatrix;
__interface DELPHIINTERFACE JScriptIntrinsicConvolve3x3Class;
typedef System::DelphiInterface<JScriptIntrinsicConvolve3x3Class> _di_JScriptIntrinsicConvolve3x3Class;
__interface DELPHIINTERFACE JScriptIntrinsicConvolve3x3;
typedef System::DelphiInterface<JScriptIntrinsicConvolve3x3> _di_JScriptIntrinsicConvolve3x3;
class DELPHICLASS TJScriptIntrinsicConvolve3x3;
__interface DELPHIINTERFACE JScriptIntrinsicConvolve5x5Class;
typedef System::DelphiInterface<JScriptIntrinsicConvolve5x5Class> _di_JScriptIntrinsicConvolve5x5Class;
__interface DELPHIINTERFACE JScriptIntrinsicConvolve5x5;
typedef System::DelphiInterface<JScriptIntrinsicConvolve5x5> _di_JScriptIntrinsicConvolve5x5;
class DELPHICLASS TJScriptIntrinsicConvolve5x5;
__interface DELPHIINTERFACE JScriptIntrinsicHistogramClass;
typedef System::DelphiInterface<JScriptIntrinsicHistogramClass> _di_JScriptIntrinsicHistogramClass;
__interface DELPHIINTERFACE JScriptIntrinsicHistogram;
typedef System::DelphiInterface<JScriptIntrinsicHistogram> _di_JScriptIntrinsicHistogram;
class DELPHICLASS TJScriptIntrinsicHistogram;
__interface DELPHIINTERFACE JScriptIntrinsicLUTClass;
typedef System::DelphiInterface<JScriptIntrinsicLUTClass> _di_JScriptIntrinsicLUTClass;
__interface DELPHIINTERFACE JScriptIntrinsicLUT;
typedef System::DelphiInterface<JScriptIntrinsicLUT> _di_JScriptIntrinsicLUT;
class DELPHICLASS TJScriptIntrinsicLUT;
__interface DELPHIINTERFACE JScriptIntrinsicResizeClass;
typedef System::DelphiInterface<JScriptIntrinsicResizeClass> _di_JScriptIntrinsicResizeClass;
__interface DELPHIINTERFACE JScriptIntrinsicResize;
typedef System::DelphiInterface<JScriptIntrinsicResize> _di_JScriptIntrinsicResize;
class DELPHICLASS TJScriptIntrinsicResize;
__interface DELPHIINTERFACE JScriptIntrinsicYuvToRGBClass;
typedef System::DelphiInterface<JScriptIntrinsicYuvToRGBClass> _di_JScriptIntrinsicYuvToRGBClass;
__interface DELPHIINTERFACE JScriptIntrinsicYuvToRGB;
typedef System::DelphiInterface<JScriptIntrinsicYuvToRGB> _di_JScriptIntrinsicYuvToRGB;
class DELPHICLASS TJScriptIntrinsicYuvToRGB;
__interface DELPHIINTERFACE JShort2Class;
typedef System::DelphiInterface<JShort2Class> _di_JShort2Class;
__interface DELPHIINTERFACE JShort2;
typedef System::DelphiInterface<JShort2> _di_JShort2;
class DELPHICLASS TJShort2;
__interface DELPHIINTERFACE JShort3Class;
typedef System::DelphiInterface<JShort3Class> _di_JShort3Class;
__interface DELPHIINTERFACE JShort3;
typedef System::DelphiInterface<JShort3> _di_JShort3;
class DELPHICLASS TJShort3;
__interface DELPHIINTERFACE JShort4Class;
typedef System::DelphiInterface<JShort4Class> _di_JShort4Class;
__interface DELPHIINTERFACE JShort4;
typedef System::DelphiInterface<JShort4> _di_JShort4;
class DELPHICLASS TJShort4;
__interface DELPHIINTERFACE JTypeClass;
typedef System::DelphiInterface<JTypeClass> _di_JTypeClass;
__interface DELPHIINTERFACE JType;
typedef System::DelphiInterface<JType> _di_JType;
class DELPHICLASS TJType;
__interface DELPHIINTERFACE JType_BuilderClass;
typedef System::DelphiInterface<JType_BuilderClass> _di_JType_BuilderClass;
__interface DELPHIINTERFACE JType_Builder;
typedef System::DelphiInterface<JType_Builder> _di_JType_Builder;
class DELPHICLASS TJType_Builder;
__interface DELPHIINTERFACE JType_CubemapFaceClass;
typedef System::DelphiInterface<JType_CubemapFaceClass> _di_JType_CubemapFaceClass;
__interface DELPHIINTERFACE JType_CubemapFace;
typedef System::DelphiInterface<JType_CubemapFace> _di_JType_CubemapFace;
class DELPHICLASS TJType_CubemapFace;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{F1A3D5D0-1151-47D2-A690-B3B562F350CC}") JBaseObjClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{20615312-245C-4906-B481-80FDCA85B4B7}") JBaseObj  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl destroy() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual void __cdecl setName(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBaseObj : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseObjClass,_di_JBaseObj>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseObjClass,_di_JBaseObj> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBaseObj() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseObjClass,_di_JBaseObj>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBaseObj() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B01FABA3-B1B6-4F4F-AAB7-FCDDCEECB161}") JAllocationClass  : public JBaseObjClass 
{
	virtual int __cdecl _GetUSAGE_GRAPHICS_CONSTANTS() = 0 ;
	virtual int __cdecl _GetUSAGE_GRAPHICS_RENDER_TARGET() = 0 ;
	virtual int __cdecl _GetUSAGE_GRAPHICS_TEXTURE() = 0 ;
	virtual int __cdecl _GetUSAGE_GRAPHICS_VERTEX() = 0 ;
	virtual int __cdecl _GetUSAGE_IO_INPUT() = 0 ;
	virtual int __cdecl _GetUSAGE_IO_OUTPUT() = 0 ;
	virtual int __cdecl _GetUSAGE_SCRIPT() = 0 ;
	virtual int __cdecl _GetUSAGE_SHARED() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JAllocation>* __cdecl createAllocations(_di_JRenderScript rs, _di_JType t, int usage, int numAlloc) = 0 ;
	virtual _di_JAllocation __cdecl createCubemapFromBitmap(_di_JRenderScript rs, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap b, _di_JAllocation_MipmapControl mips, int usage) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createCubemapFromBitmap(_di_JRenderScript rs, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap b) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createCubemapFromCubeFaces(_di_JRenderScript rs, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap xpos, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap xneg, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap ypos, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap yneg, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap zpos, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap zneg, _di_JAllocation_MipmapControl mips, int usage) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createCubemapFromCubeFaces(_di_JRenderScript rs, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap xpos, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap xneg, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap ypos, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap yneg, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap zpos, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap zneg) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createFromBitmap(_di_JRenderScript rs, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap b, _di_JAllocation_MipmapControl mips, int usage) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createFromBitmap(_di_JRenderScript rs, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap b) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createFromBitmapResource(_di_JRenderScript rs, Androidapi::Jni::Graphicscontentviewtext::_di_JResources res, int id, _di_JAllocation_MipmapControl mips, int usage) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createFromBitmapResource(_di_JRenderScript rs, Androidapi::Jni::Graphicscontentviewtext::_di_JResources res, int id) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createFromString(_di_JRenderScript rs, Androidapi::Jni::Javatypes::_di_JString str, int usage) = 0 ;
	virtual _di_JAllocation __cdecl createSized(_di_JRenderScript rs, _di_Jrenderscript_Element e, int count, int usage) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createSized(_di_JRenderScript rs, _di_Jrenderscript_Element e, int count) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createTyped(_di_JRenderScript rs, _di_JType type_, _di_JAllocation_MipmapControl mips, int usage) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createTyped(_di_JRenderScript rs, _di_JType type_, int usage) = 0 /* overload */;
	virtual _di_JAllocation __cdecl createTyped(_di_JRenderScript rs, _di_JType type_) = 0 /* overload */;
	__property int USAGE_GRAPHICS_CONSTANTS = {read=_GetUSAGE_GRAPHICS_CONSTANTS};
	__property int USAGE_GRAPHICS_RENDER_TARGET = {read=_GetUSAGE_GRAPHICS_RENDER_TARGET};
	__property int USAGE_GRAPHICS_TEXTURE = {read=_GetUSAGE_GRAPHICS_TEXTURE};
	__property int USAGE_GRAPHICS_VERTEX = {read=_GetUSAGE_GRAPHICS_VERTEX};
	__property int USAGE_IO_INPUT = {read=_GetUSAGE_IO_INPUT};
	__property int USAGE_IO_OUTPUT = {read=_GetUSAGE_IO_OUTPUT};
	__property int USAGE_SCRIPT = {read=_GetUSAGE_SCRIPT};
	__property int USAGE_SHARED = {read=_GetUSAGE_SHARED};
};

__interface  INTERFACE_UUID("{1A259581-F9C8-4808-99C1-63859107FE15}") JAllocation  : public JBaseObj 
{
	virtual void __cdecl copy1DRangeFrom(int off, int count, Androidapi::Jni::Javatypes::_di_JObject array_) = 0 /* overload */;
	virtual void __cdecl copy1DRangeFrom(int off, int count, Androidapi::Jnibridge::TJavaArray__1<int>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeFrom(int off, int count, Androidapi::Jnibridge::TJavaArray__1<short>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeFrom(int off, int count, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeFrom(int off, int count, Androidapi::Jnibridge::TJavaArray__1<float>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeFrom(int off, int count, _di_JAllocation data, int dataOff) = 0 /* overload */;
	virtual void __cdecl copy1DRangeFromUnchecked(int off, int count, Androidapi::Jni::Javatypes::_di_JObject array_) = 0 /* overload */;
	virtual void __cdecl copy1DRangeFromUnchecked(int off, int count, Androidapi::Jnibridge::TJavaArray__1<int>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeFromUnchecked(int off, int count, Androidapi::Jnibridge::TJavaArray__1<short>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeFromUnchecked(int off, int count, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeFromUnchecked(int off, int count, Androidapi::Jnibridge::TJavaArray__1<float>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeTo(int off, int count, Androidapi::Jni::Javatypes::_di_JObject array_) = 0 /* overload */;
	virtual void __cdecl copy1DRangeTo(int off, int count, Androidapi::Jnibridge::TJavaArray__1<int>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeTo(int off, int count, Androidapi::Jnibridge::TJavaArray__1<short>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeTo(int off, int count, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeTo(int off, int count, Androidapi::Jnibridge::TJavaArray__1<float>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeToUnchecked(int off, int count, Androidapi::Jni::Javatypes::_di_JObject array_) = 0 /* overload */;
	virtual void __cdecl copy1DRangeToUnchecked(int off, int count, Androidapi::Jnibridge::TJavaArray__1<int>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeToUnchecked(int off, int count, Androidapi::Jnibridge::TJavaArray__1<short>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeToUnchecked(int off, int count, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* d) = 0 /* overload */;
	virtual void __cdecl copy1DRangeToUnchecked(int off, int count, Androidapi::Jnibridge::TJavaArray__1<float>* d) = 0 /* overload */;
	virtual void __cdecl copy2DRangeFrom(int xoff, int yoff, int w, int h, Androidapi::Jni::Javatypes::_di_JObject array_) = 0 /* overload */;
	virtual void __cdecl copy2DRangeFrom(int xoff, int yoff, int w, int h, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* data) = 0 /* overload */;
	virtual void __cdecl copy2DRangeFrom(int xoff, int yoff, int w, int h, Androidapi::Jnibridge::TJavaArray__1<short>* data) = 0 /* overload */;
	virtual void __cdecl copy2DRangeFrom(int xoff, int yoff, int w, int h, Androidapi::Jnibridge::TJavaArray__1<int>* data) = 0 /* overload */;
	virtual void __cdecl copy2DRangeFrom(int xoff, int yoff, int w, int h, Androidapi::Jnibridge::TJavaArray__1<float>* data) = 0 /* overload */;
	virtual void __cdecl copy2DRangeFrom(int xoff, int yoff, int w, int h, _di_JAllocation data, int dataXoff, int dataYoff) = 0 /* overload */;
	virtual void __cdecl copy2DRangeFrom(int xoff, int yoff, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap data) = 0 /* overload */;
	virtual void __cdecl copy2DRangeTo(int xoff, int yoff, int w, int h, Androidapi::Jni::Javatypes::_di_JObject array_) = 0 /* overload */;
	virtual void __cdecl copy2DRangeTo(int xoff, int yoff, int w, int h, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* data) = 0 /* overload */;
	virtual void __cdecl copy2DRangeTo(int xoff, int yoff, int w, int h, Androidapi::Jnibridge::TJavaArray__1<short>* data) = 0 /* overload */;
	virtual void __cdecl copy2DRangeTo(int xoff, int yoff, int w, int h, Androidapi::Jnibridge::TJavaArray__1<int>* data) = 0 /* overload */;
	virtual void __cdecl copy2DRangeTo(int xoff, int yoff, int w, int h, Androidapi::Jnibridge::TJavaArray__1<float>* data) = 0 /* overload */;
	virtual void __cdecl copy3DRangeFrom(int xoff, int yoff, int zoff, int w, int h, int d, Androidapi::Jni::Javatypes::_di_JObject array_) = 0 /* overload */;
	virtual void __cdecl copy3DRangeFrom(int xoff, int yoff, int zoff, int w, int h, int d, _di_JAllocation data, int dataXoff, int dataYoff, int dataZoff) = 0 /* overload */;
	virtual void __cdecl copy3DRangeTo(int xoff, int yoff, int zoff, int w, int h, int d, Androidapi::Jni::Javatypes::_di_JObject array_) = 0 ;
	virtual void __cdecl copyFrom(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JBaseObj>* d) = 0 /* overload */;
	virtual void __cdecl copyFrom(Androidapi::Jni::Javatypes::_di_JObject array_) = 0 /* overload */;
	virtual void __cdecl copyFrom(Androidapi::Jnibridge::TJavaArray__1<int>* d) = 0 /* overload */;
	virtual void __cdecl copyFrom(Androidapi::Jnibridge::TJavaArray__1<short>* d) = 0 /* overload */;
	virtual void __cdecl copyFrom(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* d) = 0 /* overload */;
	virtual void __cdecl copyFrom(Androidapi::Jnibridge::TJavaArray__1<float>* d) = 0 /* overload */;
	virtual void __cdecl copyFrom(Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap b) = 0 /* overload */;
	virtual void __cdecl copyFrom(_di_JAllocation a) = 0 /* overload */;
	virtual void __cdecl copyFromUnchecked(Androidapi::Jni::Javatypes::_di_JObject array_) = 0 /* overload */;
	virtual void __cdecl copyFromUnchecked(Androidapi::Jnibridge::TJavaArray__1<int>* d) = 0 /* overload */;
	virtual void __cdecl copyFromUnchecked(Androidapi::Jnibridge::TJavaArray__1<short>* d) = 0 /* overload */;
	virtual void __cdecl copyFromUnchecked(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* d) = 0 /* overload */;
	virtual void __cdecl copyFromUnchecked(Androidapi::Jnibridge::TJavaArray__1<float>* d) = 0 /* overload */;
	virtual void __cdecl copyTo(Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap b) = 0 /* overload */;
	virtual void __cdecl copyTo(Androidapi::Jni::Javatypes::_di_JObject array_) = 0 /* overload */;
	virtual void __cdecl copyTo(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* d) = 0 /* overload */;
	virtual void __cdecl copyTo(Androidapi::Jnibridge::TJavaArray__1<short>* d) = 0 /* overload */;
	virtual void __cdecl copyTo(Androidapi::Jnibridge::TJavaArray__1<int>* d) = 0 /* overload */;
	virtual void __cdecl copyTo(Androidapi::Jnibridge::TJavaArray__1<float>* d) = 0 /* overload */;
	HIDESBASE virtual void __cdecl destroy() = 0 ;
	virtual void __cdecl generateMipmaps() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JByteBuffer __cdecl getByteBuffer() = 0 ;
	virtual int __cdecl getBytesSize() = 0 ;
	virtual _di_Jrenderscript_Element __cdecl getElement() = 0 ;
	virtual __int64 __cdecl getStride() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JSurface __cdecl getSurface() = 0 ;
	virtual __int64 __cdecl getTimeStamp() = 0 ;
	virtual _di_JType __cdecl getType() = 0 ;
	virtual int __cdecl getUsage() = 0 ;
	virtual void __cdecl ioReceive() = 0 ;
	virtual void __cdecl ioSend() = 0 ;
	virtual void __cdecl resize(int dimX) = 0 ;
	virtual void __cdecl setAutoPadding(bool useAutoPadding) = 0 ;
	virtual void __cdecl setFromFieldPacker(int xoff, _di_JFieldPacker fp) = 0 /* overload */;
	virtual void __cdecl setFromFieldPacker(int xoff, int component_number, _di_JFieldPacker fp) = 0 /* overload */;
	virtual void __cdecl setFromFieldPacker(int xoff, int yoff, int zoff, int component_number, _di_JFieldPacker fp) = 0 /* overload */;
	virtual void __cdecl setOnBufferAvailableListener(_di_JAllocation_OnBufferAvailableListener callback) = 0 ;
	virtual void __cdecl setSurface(Androidapi::Jni::Graphicscontentviewtext::_di_JSurface sur) = 0 ;
	virtual void __cdecl syncAll(int srcLocation) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAllocation : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocationClass,_di_JAllocation>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocationClass,_di_JAllocation> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAllocation() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocationClass,_di_JAllocation>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAllocation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{87E40B07-4700-4177-9E49-3FED1F0886F7}") JAllocation_MipmapControlClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JAllocation_MipmapControl __cdecl _GetMIPMAP_FULL() = 0 ;
	virtual _di_JAllocation_MipmapControl __cdecl _GetMIPMAP_NONE() = 0 ;
	virtual _di_JAllocation_MipmapControl __cdecl _GetMIPMAP_ON_SYNC_TO_TEXTURE() = 0 ;
	HIDESBASE virtual _di_JAllocation_MipmapControl __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JAllocation_MipmapControl>* __cdecl values() = 0 ;
	__property _di_JAllocation_MipmapControl MIPMAP_FULL = {read=_GetMIPMAP_FULL};
	__property _di_JAllocation_MipmapControl MIPMAP_NONE = {read=_GetMIPMAP_NONE};
	__property _di_JAllocation_MipmapControl MIPMAP_ON_SYNC_TO_TEXTURE = {read=_GetMIPMAP_ON_SYNC_TO_TEXTURE};
};

__interface  INTERFACE_UUID("{2381D33F-176C-4B5F-A896-F00D69E2B8A5}") JAllocation_MipmapControl  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAllocation_MipmapControl : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocation_MipmapControlClass,_di_JAllocation_MipmapControl>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocation_MipmapControlClass,_di_JAllocation_MipmapControl> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAllocation_MipmapControl() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocation_MipmapControlClass,_di_JAllocation_MipmapControl>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAllocation_MipmapControl() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{11AC4ED8-AF4B-410C-B541-A295CC4C949B}") JAllocation_OnBufferAvailableListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{A8F407F2-6004-4A74-82C2-434973C349F6}") JAllocation_OnBufferAvailableListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onBufferAvailable(_di_JAllocation a) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAllocation_OnBufferAvailableListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocation_OnBufferAvailableListenerClass,_di_JAllocation_OnBufferAvailableListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocation_OnBufferAvailableListenerClass,_di_JAllocation_OnBufferAvailableListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAllocation_OnBufferAvailableListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocation_OnBufferAvailableListenerClass,_di_JAllocation_OnBufferAvailableListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAllocation_OnBufferAvailableListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3F11D804-4C00-4F5A-96DD-D37AE05B5262}") JAllocationAdapterClass  : public JAllocationClass 
{
	virtual _di_JAllocationAdapter __cdecl create1D(_di_JRenderScript rs, _di_JAllocation a) = 0 ;
	virtual _di_JAllocationAdapter __cdecl create2D(_di_JRenderScript rs, _di_JAllocation a) = 0 ;
	HIDESBASE virtual _di_JAllocationAdapter __cdecl createTyped(_di_JRenderScript rs, _di_JAllocation a, _di_JType t) = 0 ;
};

__interface  INTERFACE_UUID("{42D2A32F-1F42-4C98-AFDB-F99BE0453A30}") JAllocationAdapter  : public JAllocation 
{
	HIDESBASE virtual void __cdecl resize(int dimX) = 0 ;
	virtual void __cdecl setFace(_di_JType_CubemapFace cf) = 0 ;
	virtual void __cdecl setLOD(int lod) = 0 ;
	virtual void __cdecl setX(int x) = 0 ;
	virtual void __cdecl setY(int y) = 0 ;
	virtual void __cdecl setZ(int z) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAllocationAdapter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocationAdapterClass,_di_JAllocationAdapter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocationAdapterClass,_di_JAllocationAdapter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAllocationAdapter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAllocationAdapterClass,_di_JAllocationAdapter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAllocationAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FD826C34-18C0-4A2D-A25D-C2DE2157CBA4}") JByte2Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JByte2 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JByte2 __cdecl init(System::Byte initX, System::Byte initY) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{D204CF71-A2E9-4378-BACC-F17A59CC5A2A}") JByte2  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual System::Byte __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(System::Byte Value) = 0 ;
	virtual System::Byte __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(System::Byte Value) = 0 ;
	__property System::Byte x = {read=_Getx, write=_Setx};
	__property System::Byte y = {read=_Gety, write=_Sety};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJByte2 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JByte2Class,_di_JByte2>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JByte2Class,_di_JByte2> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJByte2() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JByte2Class,_di_JByte2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJByte2() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B16A7374-C542-4692-B43C-EC47C9B25103}") JByte3Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JByte3 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JByte3 __cdecl init(System::Byte initX, System::Byte initY, System::Byte initZ) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{B4299E7D-4F20-4B2A-A51A-ECA6FE05CEF1}") JByte3  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual System::Byte __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(System::Byte Value) = 0 ;
	virtual System::Byte __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(System::Byte Value) = 0 ;
	virtual System::Byte __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(System::Byte Value) = 0 ;
	__property System::Byte x = {read=_Getx, write=_Setx};
	__property System::Byte y = {read=_Gety, write=_Sety};
	__property System::Byte z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJByte3 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JByte3Class,_di_JByte3>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JByte3Class,_di_JByte3> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJByte3() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JByte3Class,_di_JByte3>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJByte3() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7CECAA7D-78B8-4A82-ABEA-CA1A960B5F7D}") JByte4Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JByte4 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JByte4 __cdecl init(System::Byte initX, System::Byte initY, System::Byte initZ, System::Byte initW) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{25793C6B-3BD8-4F36-A7CB-6B249A84BA00}") JByte4  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual System::Byte __cdecl _Getw() = 0 ;
	virtual void __cdecl _Setw(System::Byte Value) = 0 ;
	virtual System::Byte __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(System::Byte Value) = 0 ;
	virtual System::Byte __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(System::Byte Value) = 0 ;
	virtual System::Byte __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(System::Byte Value) = 0 ;
	__property System::Byte w = {read=_Getw, write=_Setw};
	__property System::Byte x = {read=_Getx, write=_Setx};
	__property System::Byte y = {read=_Gety, write=_Sety};
	__property System::Byte z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJByte4 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JByte4Class,_di_JByte4>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JByte4Class,_di_JByte4> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJByte4() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JByte4Class,_di_JByte4>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJByte4() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3296D13A-9497-4E70-B04F-6A6FB0B94CA2}") JDouble2Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDouble2 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JDouble2 __cdecl init(double x, double y) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{960329E8-5599-48F5-8A3C-EDB4F77860C7}") JDouble2  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual double __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(double Value) = 0 ;
	virtual double __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(double Value) = 0 ;
	__property double x = {read=_Getx, write=_Setx};
	__property double y = {read=_Gety, write=_Sety};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDouble2 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDouble2Class,_di_JDouble2>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDouble2Class,_di_JDouble2> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDouble2() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDouble2Class,_di_JDouble2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDouble2() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D09E8456-E324-4365-8C24-F7BE9076CC92}") JDouble3Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDouble3 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JDouble3 __cdecl init(double x, double y, double z) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{CDDE7EEA-0EAA-4A3C-9E38-B5CE628AB935}") JDouble3  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual double __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(double Value) = 0 ;
	virtual double __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(double Value) = 0 ;
	virtual double __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(double Value) = 0 ;
	__property double x = {read=_Getx, write=_Setx};
	__property double y = {read=_Gety, write=_Sety};
	__property double z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDouble3 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDouble3Class,_di_JDouble3>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDouble3Class,_di_JDouble3> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDouble3() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDouble3Class,_di_JDouble3>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDouble3() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9FB171A5-D63F-4E2D-B6B4-7AD0A82DCA54}") JDouble4Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDouble4 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JDouble4 __cdecl init(double x, double y, double z, double w) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{CC62BE0A-7716-4C85-998B-67FCF7A9C846}") JDouble4  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual double __cdecl _Getw() = 0 ;
	virtual void __cdecl _Setw(double Value) = 0 ;
	virtual double __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(double Value) = 0 ;
	virtual double __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(double Value) = 0 ;
	virtual double __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(double Value) = 0 ;
	__property double w = {read=_Getw, write=_Setw};
	__property double x = {read=_Getx, write=_Setx};
	__property double y = {read=_Gety, write=_Sety};
	__property double z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDouble4 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDouble4Class,_di_JDouble4>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDouble4Class,_di_JDouble4> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDouble4() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDouble4Class,_di_JDouble4>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDouble4() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{19D75D2F-CF5B-4EFE-9A01-A69F51A1685D}") Jrenderscript_ElementClass  : public JBaseObjClass 
{
	virtual _di_Jrenderscript_Element __cdecl ALLOCATION(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl A_8(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl BOOLEAN(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl ELEMENT(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F16(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F16_2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F16_3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F16_4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F32(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F32_2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F32_3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F32_4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F64(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F64_2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F64_3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl F64_4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl FONT(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I16(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I16_2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I16_3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I16_4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I32(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I32_2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I32_3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I32_4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I64(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I64_2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I64_3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I64_4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I8(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I8_2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I8_3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl I8_4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl MATRIX4X4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl MATRIX_2X2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl MATRIX_3X3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl MATRIX_4X4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl MESH(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl PROGRAM_FRAGMENT(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl PROGRAM_RASTER(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl PROGRAM_STORE(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl PROGRAM_VERTEX(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl RGBA_4444(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl RGBA_5551(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl RGBA_8888(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl RGB_565(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl RGB_888(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl SAMPLER(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl SCRIPT(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl TYPE(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U16(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U16_2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U16_3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U16_4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U32(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U32_2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U32_3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U32_4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U64(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U64_2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U64_3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U64_4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U8(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U8_2(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U8_3(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl U8_4(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl YUV(_di_JRenderScript rs) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl createPixel(_di_JRenderScript rs, _di_JElement_DataType dt, _di_JElement_DataKind dk) = 0 ;
	virtual _di_Jrenderscript_Element __cdecl createVector(_di_JRenderScript rs, _di_JElement_DataType dt, int size) = 0 ;
};

__interface  INTERFACE_UUID("{47E2A1DE-1101-43E3-BF42-9F8128EDD03E}") Jrenderscript_Element  : public JBaseObj 
{
	virtual int __cdecl getBytesSize() = 0 ;
	virtual _di_JElement_DataKind __cdecl getDataKind() = 0 ;
	virtual _di_JElement_DataType __cdecl getDataType() = 0 ;
	virtual _di_Jrenderscript_Element __cdecl getSubElement(int index) = 0 ;
	virtual int __cdecl getSubElementArraySize(int index) = 0 ;
	virtual int __cdecl getSubElementCount() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSubElementName(int index) = 0 ;
	virtual int __cdecl getSubElementOffsetBytes(int index) = 0 ;
	virtual int __cdecl getVectorSize() = 0 ;
	virtual bool __cdecl isCompatible(_di_Jrenderscript_Element e) = 0 ;
	virtual bool __cdecl isComplex() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJrenderscript_Element : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jrenderscript_ElementClass,_di_Jrenderscript_Element>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jrenderscript_ElementClass,_di_Jrenderscript_Element> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJrenderscript_Element() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jrenderscript_ElementClass,_di_Jrenderscript_Element>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJrenderscript_Element() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9A906C07-DE8B-436A-A045-08079CCBF48F}") JElement_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JElement_Builder __cdecl init(_di_JRenderScript rs) = 0 ;
};

__interface  INTERFACE_UUID("{A4906DDF-7DD6-4433-B4F9-A3CDE394B6CA}") JElement_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JElement_Builder __cdecl add(_di_Jrenderscript_Element element, Androidapi::Jni::Javatypes::_di_JString name, int arraySize) = 0 /* overload */;
	virtual _di_JElement_Builder __cdecl add(_di_Jrenderscript_Element element, Androidapi::Jni::Javatypes::_di_JString name) = 0 /* overload */;
	virtual _di_Jrenderscript_Element __cdecl create() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJElement_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JElement_BuilderClass,_di_JElement_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JElement_BuilderClass,_di_JElement_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJElement_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JElement_BuilderClass,_di_JElement_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJElement_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{994F8F53-C8C0-45BE-8AB4-0194F2E93C42}") JElement_DataKindClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JElement_DataKind __cdecl _GetPIXEL_A() = 0 ;
	virtual _di_JElement_DataKind __cdecl _GetPIXEL_DEPTH() = 0 ;
	virtual _di_JElement_DataKind __cdecl _GetPIXEL_L() = 0 ;
	virtual _di_JElement_DataKind __cdecl _GetPIXEL_LA() = 0 ;
	virtual _di_JElement_DataKind __cdecl _GetPIXEL_RGB() = 0 ;
	virtual _di_JElement_DataKind __cdecl _GetPIXEL_RGBA() = 0 ;
	virtual _di_JElement_DataKind __cdecl _GetPIXEL_YUV() = 0 ;
	virtual _di_JElement_DataKind __cdecl _GetUSER() = 0 ;
	HIDESBASE virtual _di_JElement_DataKind __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JElement_DataKind>* __cdecl values() = 0 ;
	__property _di_JElement_DataKind PIXEL_A = {read=_GetPIXEL_A};
	__property _di_JElement_DataKind PIXEL_DEPTH = {read=_GetPIXEL_DEPTH};
	__property _di_JElement_DataKind PIXEL_L = {read=_GetPIXEL_L};
	__property _di_JElement_DataKind PIXEL_LA = {read=_GetPIXEL_LA};
	__property _di_JElement_DataKind PIXEL_RGB = {read=_GetPIXEL_RGB};
	__property _di_JElement_DataKind PIXEL_RGBA = {read=_GetPIXEL_RGBA};
	__property _di_JElement_DataKind PIXEL_YUV = {read=_GetPIXEL_YUV};
	__property _di_JElement_DataKind USER = {read=_GetUSER};
};

__interface  INTERFACE_UUID("{4623979D-33C7-4948-A859-E6275BCC84CD}") JElement_DataKind  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJElement_DataKind : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JElement_DataKindClass,_di_JElement_DataKind>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JElement_DataKindClass,_di_JElement_DataKind> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJElement_DataKind() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JElement_DataKindClass,_di_JElement_DataKind>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJElement_DataKind() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{196C4F4D-D545-43A4-8E4C-302BFCEB06E6}") JElement_DataTypeClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JElement_DataType __cdecl _GetBOOLEAN() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetFLOAT_16() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetFLOAT_32() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetFLOAT_64() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetMATRIX_2X2() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetMATRIX_3X3() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetMATRIX_4X4() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetNONE() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetRS_ALLOCATION() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetRS_ELEMENT() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetRS_FONT() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetRS_MESH() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetRS_PROGRAM_FRAGMENT() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetRS_PROGRAM_RASTER() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetRS_PROGRAM_STORE() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetRS_PROGRAM_VERTEX() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetRS_SAMPLER() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetRS_SCRIPT() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetRS_TYPE() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetSIGNED_16() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetSIGNED_32() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetSIGNED_64() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetSIGNED_8() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetUNSIGNED_16() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetUNSIGNED_32() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetUNSIGNED_4_4_4_4() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetUNSIGNED_5_5_5_1() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetUNSIGNED_5_6_5() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetUNSIGNED_64() = 0 ;
	virtual _di_JElement_DataType __cdecl _GetUNSIGNED_8() = 0 ;
	HIDESBASE virtual _di_JElement_DataType __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JElement_DataType>* __cdecl values() = 0 ;
	__property _di_JElement_DataType BOOLEAN = {read=_GetBOOLEAN};
	__property _di_JElement_DataType FLOAT_16 = {read=_GetFLOAT_16};
	__property _di_JElement_DataType FLOAT_32 = {read=_GetFLOAT_32};
	__property _di_JElement_DataType FLOAT_64 = {read=_GetFLOAT_64};
	__property _di_JElement_DataType MATRIX_2X2 = {read=_GetMATRIX_2X2};
	__property _di_JElement_DataType MATRIX_3X3 = {read=_GetMATRIX_3X3};
	__property _di_JElement_DataType MATRIX_4X4 = {read=_GetMATRIX_4X4};
	__property _di_JElement_DataType NONE = {read=_GetNONE};
	__property _di_JElement_DataType RS_ALLOCATION = {read=_GetRS_ALLOCATION};
	__property _di_JElement_DataType RS_ELEMENT = {read=_GetRS_ELEMENT};
	__property _di_JElement_DataType RS_FONT = {read=_GetRS_FONT};
	__property _di_JElement_DataType RS_MESH = {read=_GetRS_MESH};
	__property _di_JElement_DataType RS_PROGRAM_FRAGMENT = {read=_GetRS_PROGRAM_FRAGMENT};
	__property _di_JElement_DataType RS_PROGRAM_RASTER = {read=_GetRS_PROGRAM_RASTER};
	__property _di_JElement_DataType RS_PROGRAM_STORE = {read=_GetRS_PROGRAM_STORE};
	__property _di_JElement_DataType RS_PROGRAM_VERTEX = {read=_GetRS_PROGRAM_VERTEX};
	__property _di_JElement_DataType RS_SAMPLER = {read=_GetRS_SAMPLER};
	__property _di_JElement_DataType RS_SCRIPT = {read=_GetRS_SCRIPT};
	__property _di_JElement_DataType RS_TYPE = {read=_GetRS_TYPE};
	__property _di_JElement_DataType SIGNED_16 = {read=_GetSIGNED_16};
	__property _di_JElement_DataType SIGNED_32 = {read=_GetSIGNED_32};
	__property _di_JElement_DataType SIGNED_64 = {read=_GetSIGNED_64};
	__property _di_JElement_DataType SIGNED_8 = {read=_GetSIGNED_8};
	__property _di_JElement_DataType UNSIGNED_16 = {read=_GetUNSIGNED_16};
	__property _di_JElement_DataType UNSIGNED_32 = {read=_GetUNSIGNED_32};
	__property _di_JElement_DataType UNSIGNED_4_4_4_4 = {read=_GetUNSIGNED_4_4_4_4};
	__property _di_JElement_DataType UNSIGNED_5_5_5_1 = {read=_GetUNSIGNED_5_5_5_1};
	__property _di_JElement_DataType UNSIGNED_5_6_5 = {read=_GetUNSIGNED_5_6_5};
	__property _di_JElement_DataType UNSIGNED_64 = {read=_GetUNSIGNED_64};
	__property _di_JElement_DataType UNSIGNED_8 = {read=_GetUNSIGNED_8};
};

__interface  INTERFACE_UUID("{CD73A622-83C1-4E6A-AAA3-FDDD26FE6D70}") JElement_DataType  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJElement_DataType : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JElement_DataTypeClass,_di_JElement_DataType>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JElement_DataTypeClass,_di_JElement_DataType> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJElement_DataType() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JElement_DataTypeClass,_di_JElement_DataType>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJElement_DataType() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A81ECEEF-416F-4EF9-B267-A620F21CA310}") JFieldPackerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JFieldPacker __cdecl init(int len) = 0 /* overload */;
	HIDESBASE virtual _di_JFieldPacker __cdecl init(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* data) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{B633F233-E449-47BC-8DB1-E8E82116D429}") JFieldPacker  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addBoolean(bool v) = 0 ;
	virtual void __cdecl addF32(float v) = 0 /* overload */;
	virtual void __cdecl addF32(_di_JFloat2 v) = 0 /* overload */;
	virtual void __cdecl addF32(_di_JFloat3 v) = 0 /* overload */;
	virtual void __cdecl addF32(_di_JFloat4 v) = 0 /* overload */;
	virtual void __cdecl addF64(double v) = 0 /* overload */;
	virtual void __cdecl addF64(_di_JDouble2 v) = 0 /* overload */;
	virtual void __cdecl addF64(_di_JDouble3 v) = 0 /* overload */;
	virtual void __cdecl addF64(_di_JDouble4 v) = 0 /* overload */;
	virtual void __cdecl addI16(short v) = 0 /* overload */;
	virtual void __cdecl addI16(_di_JShort2 v) = 0 /* overload */;
	virtual void __cdecl addI16(_di_JShort3 v) = 0 /* overload */;
	virtual void __cdecl addI16(_di_JShort4 v) = 0 /* overload */;
	virtual void __cdecl addI32(int v) = 0 /* overload */;
	virtual void __cdecl addI32(_di_JInt2 v) = 0 /* overload */;
	virtual void __cdecl addI32(_di_JInt3 v) = 0 /* overload */;
	virtual void __cdecl addI32(_di_JInt4 v) = 0 /* overload */;
	virtual void __cdecl addI64(__int64 v) = 0 /* overload */;
	virtual void __cdecl addI64(_di_JLong2 v) = 0 /* overload */;
	virtual void __cdecl addI64(_di_JLong3 v) = 0 /* overload */;
	virtual void __cdecl addI64(_di_JLong4 v) = 0 /* overload */;
	virtual void __cdecl addI8(System::Byte v) = 0 /* overload */;
	virtual void __cdecl addI8(_di_JByte2 v) = 0 /* overload */;
	virtual void __cdecl addI8(_di_JByte3 v) = 0 /* overload */;
	virtual void __cdecl addI8(_di_JByte4 v) = 0 /* overload */;
	virtual void __cdecl addMatrix(_di_JMatrix4f v) = 0 /* overload */;
	virtual void __cdecl addMatrix(_di_JMatrix3f v) = 0 /* overload */;
	virtual void __cdecl addMatrix(_di_JMatrix2f v) = 0 /* overload */;
	virtual void __cdecl addObj(_di_JBaseObj obj) = 0 ;
	virtual void __cdecl addU16(int v) = 0 /* overload */;
	virtual void __cdecl addU16(_di_JInt2 v) = 0 /* overload */;
	virtual void __cdecl addU16(_di_JInt3 v) = 0 /* overload */;
	virtual void __cdecl addU16(_di_JInt4 v) = 0 /* overload */;
	virtual void __cdecl addU32(__int64 v) = 0 /* overload */;
	virtual void __cdecl addU32(_di_JLong2 v) = 0 /* overload */;
	virtual void __cdecl addU32(_di_JLong3 v) = 0 /* overload */;
	virtual void __cdecl addU32(_di_JLong4 v) = 0 /* overload */;
	virtual void __cdecl addU64(__int64 v) = 0 /* overload */;
	virtual void __cdecl addU64(_di_JLong2 v) = 0 /* overload */;
	virtual void __cdecl addU64(_di_JLong3 v) = 0 /* overload */;
	virtual void __cdecl addU64(_di_JLong4 v) = 0 /* overload */;
	virtual void __cdecl addU8(short v) = 0 /* overload */;
	virtual void __cdecl addU8(_di_JShort2 v) = 0 /* overload */;
	virtual void __cdecl addU8(_di_JShort3 v) = 0 /* overload */;
	virtual void __cdecl addU8(_di_JShort4 v) = 0 /* overload */;
	virtual void __cdecl align(int v) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getData() = 0 ;
	virtual void __cdecl reset() = 0 /* overload */;
	virtual void __cdecl reset(int i) = 0 /* overload */;
	virtual void __cdecl skip(int i) = 0 ;
	virtual bool __cdecl subBoolean() = 0 ;
	virtual _di_JByte2 __cdecl subByte2() = 0 ;
	virtual _di_JByte3 __cdecl subByte3() = 0 ;
	virtual _di_JByte4 __cdecl subByte4() = 0 ;
	virtual _di_JDouble2 __cdecl subDouble2() = 0 ;
	virtual _di_JDouble3 __cdecl subDouble3() = 0 ;
	virtual _di_JDouble4 __cdecl subDouble4() = 0 ;
	virtual float __cdecl subF32() = 0 ;
	virtual double __cdecl subF64() = 0 ;
	virtual _di_JFloat2 __cdecl subFloat2() = 0 ;
	virtual _di_JFloat3 __cdecl subFloat3() = 0 ;
	virtual _di_JFloat4 __cdecl subFloat4() = 0 ;
	virtual short __cdecl subI16() = 0 ;
	virtual int __cdecl subI32() = 0 ;
	virtual __int64 __cdecl subI64() = 0 ;
	virtual System::Byte __cdecl subI8() = 0 ;
	virtual _di_JInt2 __cdecl subInt2() = 0 ;
	virtual _di_JInt3 __cdecl subInt3() = 0 ;
	virtual _di_JInt4 __cdecl subInt4() = 0 ;
	virtual _di_JLong2 __cdecl subLong2() = 0 ;
	virtual _di_JLong3 __cdecl subLong3() = 0 ;
	virtual _di_JLong4 __cdecl subLong4() = 0 ;
	virtual _di_JMatrix2f __cdecl subMatrix2f() = 0 ;
	virtual _di_JMatrix3f __cdecl subMatrix3f() = 0 ;
	virtual _di_JMatrix4f __cdecl subMatrix4f() = 0 ;
	virtual _di_JShort2 __cdecl subShort2() = 0 ;
	virtual _di_JShort3 __cdecl subShort3() = 0 ;
	virtual _di_JShort4 __cdecl subShort4() = 0 ;
	virtual void __cdecl subalign(int v) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFieldPacker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFieldPackerClass,_di_JFieldPacker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFieldPackerClass,_di_JFieldPacker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFieldPacker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFieldPackerClass,_di_JFieldPacker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFieldPacker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6050BD90-1EA8-449A-8786-E4E8602ECF91}") JFloat2Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JFloat2 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JFloat2 __cdecl init(float x, float y) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{6EBAAAB6-A69D-4FC8-8F42-79F855A90837}") JFloat2  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(float Value) = 0 ;
	virtual float __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(float Value) = 0 ;
	__property float x = {read=_Getx, write=_Setx};
	__property float y = {read=_Gety, write=_Sety};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFloat2 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFloat2Class,_di_JFloat2>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFloat2Class,_di_JFloat2> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFloat2() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFloat2Class,_di_JFloat2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFloat2() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2E7D5B03-0B13-45A1-8A8B-44404B54AD9D}") JFloat3Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JFloat3 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JFloat3 __cdecl init(float x, float y, float z) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{92201ACB-EBD1-4596-A190-7CC34D9383F4}") JFloat3  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(float Value) = 0 ;
	virtual float __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(float Value) = 0 ;
	virtual float __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(float Value) = 0 ;
	__property float x = {read=_Getx, write=_Setx};
	__property float y = {read=_Gety, write=_Sety};
	__property float z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFloat3 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFloat3Class,_di_JFloat3>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFloat3Class,_di_JFloat3> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFloat3() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFloat3Class,_di_JFloat3>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFloat3() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D2E339DE-2B56-4A91-B229-CB583171E2B6}") JFloat4Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JFloat4 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JFloat4 __cdecl init(float x, float y, float z, float w) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{5B33BB30-A5CA-4165-93A4-5F1EF8A07219}") JFloat4  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl _Getw() = 0 ;
	virtual void __cdecl _Setw(float Value) = 0 ;
	virtual float __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(float Value) = 0 ;
	virtual float __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(float Value) = 0 ;
	virtual float __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(float Value) = 0 ;
	__property float w = {read=_Getw, write=_Setw};
	__property float x = {read=_Getx, write=_Setx};
	__property float y = {read=_Gety, write=_Sety};
	__property float z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFloat4 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFloat4Class,_di_JFloat4>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFloat4Class,_di_JFloat4> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFloat4() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFloat4Class,_di_JFloat4>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFloat4() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F2EC55B3-B3AE-4D65-931B-9CA64CA68996}") JInt2Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JInt2 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JInt2 __cdecl init(int x, int y) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{66BB1064-9C8A-4ABB-A0BC-9E68D358DC7B}") JInt2  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(int Value) = 0 ;
	virtual int __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(int Value) = 0 ;
	__property int x = {read=_Getx, write=_Setx};
	__property int y = {read=_Gety, write=_Sety};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInt2 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInt2Class,_di_JInt2>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInt2Class,_di_JInt2> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInt2() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInt2Class,_di_JInt2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInt2() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{341DC972-08DD-4C54-BE97-240BBD8A7437}") JInt3Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JInt3 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JInt3 __cdecl init(int x, int y, int z) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{7A5CA488-046A-4195-8FF7-54B3A93C7854}") JInt3  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(int Value) = 0 ;
	virtual int __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(int Value) = 0 ;
	virtual int __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(int Value) = 0 ;
	__property int x = {read=_Getx, write=_Setx};
	__property int y = {read=_Gety, write=_Sety};
	__property int z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInt3 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInt3Class,_di_JInt3>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInt3Class,_di_JInt3> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInt3() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInt3Class,_di_JInt3>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInt3() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2AF2D02D-02D7-4584-B031-D68072843E83}") JInt4Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JInt4 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JInt4 __cdecl init(int x, int y, int z, int w) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{42D7C7D1-30B7-45C3-94D6-8059A07F964D}") JInt4  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _Getw() = 0 ;
	virtual void __cdecl _Setw(int Value) = 0 ;
	virtual int __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(int Value) = 0 ;
	virtual int __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(int Value) = 0 ;
	virtual int __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(int Value) = 0 ;
	__property int w = {read=_Getw, write=_Setw};
	__property int x = {read=_Getx, write=_Setx};
	__property int y = {read=_Gety, write=_Sety};
	__property int z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInt4 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInt4Class,_di_JInt4>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInt4Class,_di_JInt4> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInt4() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInt4Class,_di_JInt4>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInt4() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5CBD4D1F-1429-40E6-A678-7E387C2F7351}") JLong2Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JLong2 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JLong2 __cdecl init(__int64 x, __int64 y) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{90A3A963-CA89-4D9C-84E0-0EB14F2BA4CB}") JLong2  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual __int64 __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(__int64 Value) = 0 ;
	virtual __int64 __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(__int64 Value) = 0 ;
	__property __int64 x = {read=_Getx, write=_Setx};
	__property __int64 y = {read=_Gety, write=_Sety};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLong2 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLong2Class,_di_JLong2>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLong2Class,_di_JLong2> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLong2() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLong2Class,_di_JLong2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLong2() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{08A2088D-461C-4FE0-97E4-385DABAD1FA1}") JLong3Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JLong3 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JLong3 __cdecl init(__int64 x, __int64 y, __int64 z) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{95FD593E-F7C6-4A93-B523-16F2191CE900}") JLong3  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual __int64 __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(__int64 Value) = 0 ;
	virtual __int64 __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(__int64 Value) = 0 ;
	virtual __int64 __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(__int64 Value) = 0 ;
	__property __int64 x = {read=_Getx, write=_Setx};
	__property __int64 y = {read=_Gety, write=_Sety};
	__property __int64 z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLong3 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLong3Class,_di_JLong3>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLong3Class,_di_JLong3> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLong3() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLong3Class,_di_JLong3>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLong3() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7A4DCA11-1342-4361-9C80-A33F6EFD795B}") JLong4Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JLong4 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JLong4 __cdecl init(__int64 x, __int64 y, __int64 z, __int64 w) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{CE624C29-BF0C-409E-BD05-4E122BF5DB0B}") JLong4  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual __int64 __cdecl _Getw() = 0 ;
	virtual void __cdecl _Setw(__int64 Value) = 0 ;
	virtual __int64 __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(__int64 Value) = 0 ;
	virtual __int64 __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(__int64 Value) = 0 ;
	virtual __int64 __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(__int64 Value) = 0 ;
	__property __int64 w = {read=_Getw, write=_Setw};
	__property __int64 x = {read=_Getx, write=_Setx};
	__property __int64 y = {read=_Gety, write=_Sety};
	__property __int64 z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLong4 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLong4Class,_di_JLong4>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLong4Class,_di_JLong4> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLong4() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLong4Class,_di_JLong4>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLong4() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{62C79CAE-98F8-4A49-AEA5-16898C7545D5}") JMatrix2fClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JMatrix2f __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JMatrix2f __cdecl init(Androidapi::Jnibridge::TJavaArray__1<float>* dataArray) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{1E766A89-5F56-4818-9864-06837EAF0E0C}") JMatrix2f  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl get(int x, int y) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<float>* __cdecl getArray() = 0 ;
	virtual void __cdecl load(_di_JMatrix2f src) = 0 ;
	virtual void __cdecl loadIdentity() = 0 ;
	virtual void __cdecl loadMultiply(_di_JMatrix2f lhs, _di_JMatrix2f rhs) = 0 ;
	virtual void __cdecl loadRotate(float rot) = 0 ;
	virtual void __cdecl loadScale(float x, float y) = 0 ;
	virtual void __cdecl multiply(_di_JMatrix2f rhs) = 0 ;
	virtual void __cdecl rotate(float rot) = 0 ;
	virtual void __cdecl scale(float x, float y) = 0 ;
	virtual void __cdecl set(int x, int y, float v) = 0 ;
	virtual void __cdecl transpose() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMatrix2f : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMatrix2fClass,_di_JMatrix2f>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMatrix2fClass,_di_JMatrix2f> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMatrix2f() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMatrix2fClass,_di_JMatrix2f>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMatrix2f() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2F3F915F-90FE-477A-AC7E-CCCF53E5F631}") JMatrix3fClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JMatrix3f __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JMatrix3f __cdecl init(Androidapi::Jnibridge::TJavaArray__1<float>* dataArray) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{4AF7E3DE-7AC0-4677-91AB-8DF4ECF227A1}") JMatrix3f  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl get(int x, int y) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<float>* __cdecl getArray() = 0 ;
	virtual void __cdecl load(_di_JMatrix3f src) = 0 ;
	virtual void __cdecl loadIdentity() = 0 ;
	virtual void __cdecl loadMultiply(_di_JMatrix3f lhs, _di_JMatrix3f rhs) = 0 ;
	virtual void __cdecl loadRotate(float rot, float x, float y, float z) = 0 /* overload */;
	virtual void __cdecl loadRotate(float rot) = 0 /* overload */;
	virtual void __cdecl loadScale(float x, float y) = 0 /* overload */;
	virtual void __cdecl loadScale(float x, float y, float z) = 0 /* overload */;
	virtual void __cdecl loadTranslate(float x, float y) = 0 ;
	virtual void __cdecl multiply(_di_JMatrix3f rhs) = 0 ;
	virtual void __cdecl rotate(float rot, float x, float y, float z) = 0 /* overload */;
	virtual void __cdecl rotate(float rot) = 0 /* overload */;
	virtual void __cdecl scale(float x, float y) = 0 /* overload */;
	virtual void __cdecl scale(float x, float y, float z) = 0 /* overload */;
	virtual void __cdecl set(int x, int y, float v) = 0 ;
	virtual void __cdecl translate(float x, float y) = 0 ;
	virtual void __cdecl transpose() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMatrix3f : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMatrix3fClass,_di_JMatrix3f>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMatrix3fClass,_di_JMatrix3f> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMatrix3f() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMatrix3fClass,_di_JMatrix3f>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMatrix3f() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6483A6CB-C4F7-4E4E-B40E-F887A68403BD}") JMatrix4fClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JMatrix4f __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JMatrix4f __cdecl init(Androidapi::Jnibridge::TJavaArray__1<float>* dataArray) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{3E2D34F5-4AB7-4CBC-B0B9-255312A3ACFD}") JMatrix4f  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl get(int x, int y) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<float>* __cdecl getArray() = 0 ;
	virtual bool __cdecl inverse() = 0 ;
	virtual bool __cdecl inverseTranspose() = 0 ;
	virtual void __cdecl load(_di_JMatrix4f src) = 0 ;
	virtual void __cdecl loadFrustum(float l, float r, float b, float t, float n, float f) = 0 ;
	virtual void __cdecl loadIdentity() = 0 ;
	virtual void __cdecl loadMultiply(_di_JMatrix4f lhs, _di_JMatrix4f rhs) = 0 ;
	virtual void __cdecl loadOrtho(float l, float r, float b, float t, float n, float f) = 0 ;
	virtual void __cdecl loadOrthoWindow(int w, int h) = 0 ;
	virtual void __cdecl loadPerspective(float fovy, float aspect, float near, float far) = 0 ;
	virtual void __cdecl loadProjectionNormalized(int w, int h) = 0 ;
	virtual void __cdecl loadRotate(float rot, float x, float y, float z) = 0 ;
	virtual void __cdecl loadScale(float x, float y, float z) = 0 ;
	virtual void __cdecl loadTranslate(float x, float y, float z) = 0 ;
	virtual void __cdecl multiply(_di_JMatrix4f rhs) = 0 ;
	virtual void __cdecl rotate(float rot, float x, float y, float z) = 0 ;
	virtual void __cdecl scale(float x, float y, float z) = 0 ;
	virtual void __cdecl set(int x, int y, float v) = 0 ;
	virtual void __cdecl translate(float x, float y, float z) = 0 ;
	virtual void __cdecl transpose() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJMatrix4f : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMatrix4fClass,_di_JMatrix4f>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMatrix4fClass,_di_JMatrix4f> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJMatrix4f() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JMatrix4fClass,_di_JMatrix4f>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJMatrix4f() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{03D61660-F32B-4021-8229-25BF94795756}") JRSRuntimeExceptionClass  : public Androidapi::Jni::Javatypes::JRuntimeExceptionClass 
{
	HIDESBASE virtual _di_JRSRuntimeException __cdecl init(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
};

__interface  INTERFACE_UUID("{DD1FAE5C-1626-48AA-8C1F-1309C133CD47}") JRSRuntimeException  : public Androidapi::Jni::Javatypes::JRuntimeException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRSRuntimeException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSRuntimeExceptionClass,_di_JRSRuntimeException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSRuntimeExceptionClass,_di_JRSRuntimeException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRSRuntimeException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSRuntimeExceptionClass,_di_JRSRuntimeException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRSRuntimeException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8C8445E5-1F76-441B-9747-D4DB57DCCC3C}") JRSDriverExceptionClass  : public JRSRuntimeExceptionClass 
{
	HIDESBASE virtual _di_JRSDriverException __cdecl init(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
};

__interface  INTERFACE_UUID("{7F2014E4-DD11-498A-94C2-B2E13A43ADA5}") JRSDriverException  : public JRSRuntimeException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRSDriverException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSDriverExceptionClass,_di_JRSDriverException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSDriverExceptionClass,_di_JRSDriverException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRSDriverException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSDriverExceptionClass,_di_JRSDriverException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRSDriverException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EE678B06-E8C2-47B5-89DA-A2BEFC96DC51}") JRSIllegalArgumentExceptionClass  : public JRSRuntimeExceptionClass 
{
	HIDESBASE virtual _di_JRSIllegalArgumentException __cdecl init(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
};

__interface  INTERFACE_UUID("{166BD74D-2CD8-492F-82CF-4DD4A49A9A53}") JRSIllegalArgumentException  : public JRSRuntimeException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRSIllegalArgumentException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSIllegalArgumentExceptionClass,_di_JRSIllegalArgumentException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSIllegalArgumentExceptionClass,_di_JRSIllegalArgumentException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRSIllegalArgumentException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSIllegalArgumentExceptionClass,_di_JRSIllegalArgumentException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRSIllegalArgumentException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7AA83170-1921-4DC8-85C3-59434692FF5C}") JRSInvalidStateExceptionClass  : public JRSRuntimeExceptionClass 
{
	HIDESBASE virtual _di_JRSInvalidStateException __cdecl init(Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
};

__interface  INTERFACE_UUID("{6DF1A237-27E3-4C24-B258-FB956C279B1E}") JRSInvalidStateException  : public JRSRuntimeException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRSInvalidStateException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSInvalidStateExceptionClass,_di_JRSInvalidStateException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSInvalidStateExceptionClass,_di_JRSInvalidStateException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRSInvalidStateException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRSInvalidStateExceptionClass,_di_JRSInvalidStateException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRSInvalidStateException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ACD2A56F-451D-4D2C-9EF0-339EE08C663F}") JRenderScriptClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetCREATE_FLAG_LOW_LATENCY() = 0 ;
	virtual int __cdecl _GetCREATE_FLAG_LOW_POWER() = 0 ;
	virtual int __cdecl _GetCREATE_FLAG_NONE() = 0 ;
	virtual _di_JRenderScript __cdecl create(Androidapi::Jni::Graphicscontentviewtext::_di_JContext ctx) = 0 /* overload */;
	virtual _di_JRenderScript __cdecl create(Androidapi::Jni::Graphicscontentviewtext::_di_JContext ctx, _di_JRenderScript_ContextType ct) = 0 /* overload */;
	virtual _di_JRenderScript __cdecl create(Androidapi::Jni::Graphicscontentviewtext::_di_JContext ctx, _di_JRenderScript_ContextType ct, int flags) = 0 /* overload */;
	virtual _di_JRenderScript __cdecl createMultiContext(Androidapi::Jni::Graphicscontentviewtext::_di_JContext ctx, _di_JRenderScript_ContextType ct, int flags, int API_number) = 0 ;
	virtual __int64 __cdecl getMinorVersion() = 0 ;
	virtual void __cdecl releaseAllContexts() = 0 ;
	__property int CREATE_FLAG_LOW_LATENCY = {read=_GetCREATE_FLAG_LOW_LATENCY};
	__property int CREATE_FLAG_LOW_POWER = {read=_GetCREATE_FLAG_LOW_POWER};
	__property int CREATE_FLAG_NONE = {read=_GetCREATE_FLAG_NONE};
};

__interface  INTERFACE_UUID("{1375A3CE-12EA-4DB9-B20F-128B944A172B}") JRenderScript  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl contextDump() = 0 ;
	virtual void __cdecl destroy() = 0 ;
	virtual void __cdecl finish() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JContext __cdecl getApplicationContext() = 0 ;
	virtual _di_JRenderScript_RSErrorHandler __cdecl getErrorHandler() = 0 ;
	virtual _di_JRenderScript_RSMessageHandler __cdecl getMessageHandler() = 0 ;
	virtual void __cdecl sendMessage(int id, Androidapi::Jnibridge::TJavaArray__1<int>* data) = 0 ;
	virtual void __cdecl setErrorHandler(_di_JRenderScript_RSErrorHandler msg) = 0 ;
	virtual void __cdecl setMessageHandler(_di_JRenderScript_RSMessageHandler msg) = 0 ;
	virtual void __cdecl setPriority(_di_JRenderScript_Priority p) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRenderScript : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScriptClass,_di_JRenderScript>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScriptClass,_di_JRenderScript> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRenderScript() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScriptClass,_di_JRenderScript>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRenderScript() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9AC82907-B608-45DE-9C01-32619316E00B}") JRenderScript_ContextTypeClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JRenderScript_ContextType __cdecl _GetDEBUG() = 0 ;
	virtual _di_JRenderScript_ContextType __cdecl _GetNORMAL() = 0 ;
	virtual _di_JRenderScript_ContextType __cdecl _GetPROFILE() = 0 ;
	HIDESBASE virtual _di_JRenderScript_ContextType __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JRenderScript_ContextType>* __cdecl values() = 0 ;
	__property _di_JRenderScript_ContextType DEBUG = {read=_GetDEBUG};
	__property _di_JRenderScript_ContextType NORMAL = {read=_GetNORMAL};
	__property _di_JRenderScript_ContextType PROFILE = {read=_GetPROFILE};
};

__interface  INTERFACE_UUID("{A7DD5E86-28E9-46D5-86F3-42B3AC09F992}") JRenderScript_ContextType  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRenderScript_ContextType : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_ContextTypeClass,_di_JRenderScript_ContextType>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_ContextTypeClass,_di_JRenderScript_ContextType> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRenderScript_ContextType() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_ContextTypeClass,_di_JRenderScript_ContextType>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRenderScript_ContextType() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F4D97121-C8FA-4318-AFF2-EA810216B789}") JRenderScript_PriorityClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JRenderScript_Priority __cdecl _GetLOW() = 0 ;
	virtual _di_JRenderScript_Priority __cdecl _GetNORMAL() = 0 ;
	HIDESBASE virtual _di_JRenderScript_Priority __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JRenderScript_Priority>* __cdecl values() = 0 ;
	__property _di_JRenderScript_Priority LOW = {read=_GetLOW};
	__property _di_JRenderScript_Priority NORMAL = {read=_GetNORMAL};
};

__interface  INTERFACE_UUID("{A53C6A12-652B-4272-AEBC-DC5E71376BA6}") JRenderScript_Priority  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRenderScript_Priority : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_PriorityClass,_di_JRenderScript_Priority>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_PriorityClass,_di_JRenderScript_Priority> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRenderScript_Priority() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_PriorityClass,_di_JRenderScript_Priority>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRenderScript_Priority() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C53AAF16-0541-4A5E-85D5-62A3D50EFA2B}") JRenderScript_RSErrorHandlerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JRenderScript_RSErrorHandler __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{50BCE00A-0A52-4159-A030-D5EDEBABD142}") JRenderScript_RSErrorHandler  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl run() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRenderScript_RSErrorHandler : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_RSErrorHandlerClass,_di_JRenderScript_RSErrorHandler>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_RSErrorHandlerClass,_di_JRenderScript_RSErrorHandler> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRenderScript_RSErrorHandler() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_RSErrorHandlerClass,_di_JRenderScript_RSErrorHandler>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRenderScript_RSErrorHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{46CB4337-A752-4A50-BE4D-1F8BE837700C}") JRenderScript_RSMessageHandlerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JRenderScript_RSMessageHandler __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{7B2E311E-5144-4366-A315-1689480B541D}") JRenderScript_RSMessageHandler  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl run() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRenderScript_RSMessageHandler : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_RSMessageHandlerClass,_di_JRenderScript_RSMessageHandler>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_RSMessageHandlerClass,_di_JRenderScript_RSMessageHandler> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRenderScript_RSMessageHandler() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRenderScript_RSMessageHandlerClass,_di_JRenderScript_RSMessageHandler>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRenderScript_RSMessageHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{070535D1-2A17-4382-9BB1-77F0D4164FA2}") JSamplerClass  : public JBaseObjClass 
{
	virtual _di_JSampler __cdecl CLAMP_LINEAR(_di_JRenderScript rs) = 0 ;
	virtual _di_JSampler __cdecl CLAMP_LINEAR_MIP_LINEAR(_di_JRenderScript rs) = 0 ;
	virtual _di_JSampler __cdecl CLAMP_NEAREST(_di_JRenderScript rs) = 0 ;
	virtual _di_JSampler __cdecl MIRRORED_REPEAT_LINEAR(_di_JRenderScript rs) = 0 ;
	virtual _di_JSampler __cdecl MIRRORED_REPEAT_LINEAR_MIP_LINEAR(_di_JRenderScript rs) = 0 ;
	virtual _di_JSampler __cdecl MIRRORED_REPEAT_NEAREST(_di_JRenderScript rs) = 0 ;
	virtual _di_JSampler __cdecl WRAP_LINEAR(_di_JRenderScript rs) = 0 ;
	virtual _di_JSampler __cdecl WRAP_LINEAR_MIP_LINEAR(_di_JRenderScript rs) = 0 ;
	virtual _di_JSampler __cdecl WRAP_NEAREST(_di_JRenderScript rs) = 0 ;
};

__interface  INTERFACE_UUID("{0FA0CED8-A2D6-44F9-9473-1F9CBCB613BA}") JSampler  : public JBaseObj 
{
	virtual float __cdecl getAnisotropy() = 0 ;
	virtual _di_JSampler_Value __cdecl getMagnification() = 0 ;
	virtual _di_JSampler_Value __cdecl getMinification() = 0 ;
	virtual _di_JSampler_Value __cdecl getWrapS() = 0 ;
	virtual _di_JSampler_Value __cdecl getWrapT() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSampler : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSamplerClass,_di_JSampler>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSamplerClass,_di_JSampler> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSampler() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSamplerClass,_di_JSampler>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSampler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{37390FE7-A7CC-4990-9B18-0F1FF3F310E2}") JSampler_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSampler_Builder __cdecl init(_di_JRenderScript rs) = 0 ;
};

__interface  INTERFACE_UUID("{D56000B6-2005-4FEE-B0C4-01581A09D489}") JSampler_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JSampler __cdecl create() = 0 ;
	virtual void __cdecl setAnisotropy(float v) = 0 ;
	virtual void __cdecl setMagnification(_di_JSampler_Value v) = 0 ;
	virtual void __cdecl setMinification(_di_JSampler_Value v) = 0 ;
	virtual void __cdecl setWrapS(_di_JSampler_Value v) = 0 ;
	virtual void __cdecl setWrapT(_di_JSampler_Value v) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSampler_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSampler_BuilderClass,_di_JSampler_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSampler_BuilderClass,_di_JSampler_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSampler_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSampler_BuilderClass,_di_JSampler_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSampler_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8077E896-05A5-444B-B3E7-344DDDB57BC0}") JSampler_ValueClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JSampler_Value __cdecl _GetCLAMP() = 0 ;
	virtual _di_JSampler_Value __cdecl _GetLINEAR() = 0 ;
	virtual _di_JSampler_Value __cdecl _GetLINEAR_MIP_LINEAR() = 0 ;
	virtual _di_JSampler_Value __cdecl _GetLINEAR_MIP_NEAREST() = 0 ;
	virtual _di_JSampler_Value __cdecl _GetMIRRORED_REPEAT() = 0 ;
	virtual _di_JSampler_Value __cdecl _GetNEAREST() = 0 ;
	virtual _di_JSampler_Value __cdecl _GetWRAP() = 0 ;
	HIDESBASE virtual _di_JSampler_Value __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JSampler_Value>* __cdecl values() = 0 ;
	__property _di_JSampler_Value CLAMP = {read=_GetCLAMP};
	__property _di_JSampler_Value LINEAR = {read=_GetLINEAR};
	__property _di_JSampler_Value LINEAR_MIP_LINEAR = {read=_GetLINEAR_MIP_LINEAR};
	__property _di_JSampler_Value LINEAR_MIP_NEAREST = {read=_GetLINEAR_MIP_NEAREST};
	__property _di_JSampler_Value MIRRORED_REPEAT = {read=_GetMIRRORED_REPEAT};
	__property _di_JSampler_Value NEAREST = {read=_GetNEAREST};
	__property _di_JSampler_Value WRAP = {read=_GetWRAP};
};

__interface  INTERFACE_UUID("{AE9FA332-D600-46B2-B4C7-6AA8BD8C88B1}") JSampler_Value  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSampler_Value : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSampler_ValueClass,_di_JSampler_Value>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSampler_ValueClass,_di_JSampler_Value> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSampler_Value() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSampler_ValueClass,_di_JSampler_Value>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSampler_Value() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3C4B94DB-AA9D-4EAE-BE4C-22FB4E0E6EAE}") JScriptClass  : public JBaseObjClass 
{
	
};

__interface  INTERFACE_UUID("{25CE110C-9510-469A-A5C5-957A802D881A}") JScript  : public JBaseObj 
{
	virtual void __cdecl bindAllocation(_di_JAllocation va, int slot) = 0 ;
	virtual bool __cdecl getVarB(int index) = 0 ;
	virtual double __cdecl getVarD(int index) = 0 ;
	virtual float __cdecl getVarF(int index) = 0 ;
	virtual int __cdecl getVarI(int index) = 0 ;
	virtual __int64 __cdecl getVarJ(int index) = 0 ;
	virtual void __cdecl getVarV(int index, _di_JFieldPacker v) = 0 ;
	virtual void __cdecl setTimeZone(Androidapi::Jni::Javatypes::_di_JString timeZone) = 0 ;
	virtual void __cdecl setVar(int index, float v) = 0 /* overload */;
	virtual void __cdecl setVar(int index, double v) = 0 /* overload */;
	virtual void __cdecl setVar(int index, int v) = 0 /* overload */;
	virtual void __cdecl setVar(int index, __int64 v) = 0 /* overload */;
	virtual void __cdecl setVar(int index, bool v) = 0 /* overload */;
	virtual void __cdecl setVar(int index, _di_JBaseObj o) = 0 /* overload */;
	virtual void __cdecl setVar(int index, _di_JFieldPacker v) = 0 /* overload */;
	virtual void __cdecl setVar(int index, _di_JFieldPacker v, _di_Jrenderscript_Element e, Androidapi::Jnibridge::TJavaArray__1<int>* dims) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScript : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptClass,_di_JScript>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptClass,_di_JScript> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScript() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptClass,_di_JScript>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScript() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C053D63B-E1EA-4DDF-93C0-B7FFACD38922}") JScript_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{FF9991B7-C7CD-4652-A3D6-9A02EC654457}") JScript_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScript_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_BuilderClass,_di_JScript_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_BuilderClass,_di_JScript_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScript_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_BuilderClass,_di_JScript_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScript_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{55F38A69-0626-4BDD-BB0C-786E6044EC93}") JScript_FieldBaseClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{8921B206-F389-439E-8DCB-C51630F72EB4}") JScript_FieldBase  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JAllocation __cdecl getAllocation() = 0 ;
	virtual _di_Jrenderscript_Element __cdecl getElement() = 0 ;
	virtual _di_JType __cdecl getType() = 0 ;
	virtual void __cdecl updateAllocation() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScript_FieldBase : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_FieldBaseClass,_di_JScript_FieldBase>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_FieldBaseClass,_di_JScript_FieldBase> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScript_FieldBase() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_FieldBaseClass,_di_JScript_FieldBase>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScript_FieldBase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A0544DC8-4ECA-445F-B266-6B2F138E6D92}") JScript_FieldIDClass  : public JBaseObjClass 
{
	
};

__interface  INTERFACE_UUID("{B05644E2-FEB8-4DD7-819F-1D5F85648761}") JScript_FieldID  : public JBaseObj 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScript_FieldID : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_FieldIDClass,_di_JScript_FieldID>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_FieldIDClass,_di_JScript_FieldID> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScript_FieldID() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_FieldIDClass,_di_JScript_FieldID>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScript_FieldID() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AC750D8A-FFDF-4A29-90EC-5EDCC99A2D62}") JScript_InvokeIDClass  : public JBaseObjClass 
{
	
};

__interface  INTERFACE_UUID("{19995BD8-07C5-4CA4-A4BE-3F29F4BC5C01}") JScript_InvokeID  : public JBaseObj 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScript_InvokeID : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_InvokeIDClass,_di_JScript_InvokeID>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_InvokeIDClass,_di_JScript_InvokeID> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScript_InvokeID() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_InvokeIDClass,_di_JScript_InvokeID>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScript_InvokeID() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1D8D5235-9976-469E-AC1D-7FA0B10C5AAB}") JScript_KernelIDClass  : public JBaseObjClass 
{
	
};

__interface  INTERFACE_UUID("{0F171B16-CC18-41DE-A121-79023D34C764}") JScript_KernelID  : public JBaseObj 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScript_KernelID : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_KernelIDClass,_di_JScript_KernelID>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_KernelIDClass,_di_JScript_KernelID> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScript_KernelID() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_KernelIDClass,_di_JScript_KernelID>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScript_KernelID() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1BDBA116-91A8-4614-B453-E851D81CC968}") JScript_LaunchOptionsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JScript_LaunchOptions __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{6AF9C535-E4CE-4FE0-AD57-42EC87BA046A}") JScript_LaunchOptions  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl getXEnd() = 0 ;
	virtual int __cdecl getXStart() = 0 ;
	virtual int __cdecl getYEnd() = 0 ;
	virtual int __cdecl getYStart() = 0 ;
	virtual int __cdecl getZEnd() = 0 ;
	virtual int __cdecl getZStart() = 0 ;
	virtual _di_JScript_LaunchOptions __cdecl setX(int xstartArg, int xendArg) = 0 ;
	virtual _di_JScript_LaunchOptions __cdecl setY(int ystartArg, int yendArg) = 0 ;
	virtual _di_JScript_LaunchOptions __cdecl setZ(int zstartArg, int zendArg) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScript_LaunchOptions : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_LaunchOptionsClass,_di_JScript_LaunchOptions>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_LaunchOptionsClass,_di_JScript_LaunchOptions> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScript_LaunchOptions() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScript_LaunchOptionsClass,_di_JScript_LaunchOptions>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScript_LaunchOptions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E8C599CD-8577-488C-BB2E-6E258B28F9ED}") JScriptCClass  : public JScriptClass 
{
	
};

__interface  INTERFACE_UUID("{EE227749-F51D-48C8-9BBC-2400ACD7C317}") JScriptC  : public JScript 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptC : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptCClass,_di_JScriptC>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptCClass,_di_JScriptC> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptC() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptCClass,_di_JScriptC>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptC() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1045A21B-0421-41C3-9F70-00ADCA568DCC}") JScriptGroupClass  : public JBaseObjClass 
{
	
};

__interface  INTERFACE_UUID("{47963EEE-BB3D-48A5-AE1C-6EFFB53886CC}") JScriptGroup  : public JBaseObj 
{
	HIDESBASE virtual void __cdecl destroy() = 0 ;
	virtual void __cdecl execute() = 0 /* overload */;
	virtual void __cdecl setInput(_di_JScript_KernelID s, _di_JAllocation a) = 0 ;
	virtual void __cdecl setOutput(_di_JScript_KernelID s, _di_JAllocation a) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptGroup : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroupClass,_di_JScriptGroup>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroupClass,_di_JScriptGroup> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptGroup() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroupClass,_di_JScriptGroup>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptGroup() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{92F1F6B6-E6C8-4C3F-8D44-746D24F98D9F}") JScriptGroup_BindingClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JScriptGroup_Binding __cdecl init(_di_JScript_FieldID field, Androidapi::Jni::Javatypes::_di_JObject value) = 0 ;
};

__interface  INTERFACE_UUID("{2B4A8CA8-01CB-4649-86EC-4EA257DFC73C}") JScriptGroup_Binding  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptGroup_Binding : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_BindingClass,_di_JScriptGroup_Binding>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_BindingClass,_di_JScriptGroup_Binding> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptGroup_Binding() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_BindingClass,_di_JScriptGroup_Binding>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptGroup_Binding() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{601170DB-3547-48AD-8C65-51592BFF2ED6}") JScriptGroup_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JScriptGroup_Builder __cdecl init(_di_JRenderScript rs) = 0 ;
};

__interface  INTERFACE_UUID("{1BFC76E1-C11E-46D7-925E-E6F8BB5A04E2}") JScriptGroup_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JScriptGroup_Builder __cdecl addConnection(_di_JType t, _di_JScript_KernelID from, _di_JScript_FieldID to_) = 0 /* overload */;
	virtual _di_JScriptGroup_Builder __cdecl addConnection(_di_JType t, _di_JScript_KernelID from, _di_JScript_KernelID to_) = 0 /* overload */;
	virtual _di_JScriptGroup_Builder __cdecl addKernel(_di_JScript_KernelID k) = 0 ;
	virtual _di_JScriptGroup __cdecl create() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptGroup_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_BuilderClass,_di_JScriptGroup_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_BuilderClass,_di_JScriptGroup_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptGroup_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_BuilderClass,_di_JScriptGroup_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptGroup_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E02ABA26-A570-4325-9FE9-7948CB98189E}") JScriptGroup_Builder2Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JScriptGroup_Builder2 __cdecl init(_di_JRenderScript rs) = 0 ;
};

__interface  INTERFACE_UUID("{A6D8A0F0-57AE-489E-ACC6-680F07F8EA3C}") JScriptGroup_Builder2  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JScriptGroup_Input __cdecl addInput() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptGroup_Builder2 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_Builder2Class,_di_JScriptGroup_Builder2>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_Builder2Class,_di_JScriptGroup_Builder2> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptGroup_Builder2() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_Builder2Class,_di_JScriptGroup_Builder2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptGroup_Builder2() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0F69F36B-8782-4C0D-AA23-A67B4BBB8E08}") JScriptGroup_ClosureClass  : public JBaseObjClass 
{
	
};

__interface  INTERFACE_UUID("{6773E7A7-F3AF-482C-96EE-3837809B8045}") JScriptGroup_Closure  : public JBaseObj 
{
	HIDESBASE virtual void __cdecl destroy() = 0 ;
	virtual _di_JScriptGroup_Future __cdecl getGlobal(_di_JScript_FieldID field) = 0 ;
	virtual _di_JScriptGroup_Future __cdecl getReturn() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptGroup_Closure : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_ClosureClass,_di_JScriptGroup_Closure>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_ClosureClass,_di_JScriptGroup_Closure> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptGroup_Closure() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_ClosureClass,_di_JScriptGroup_Closure>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptGroup_Closure() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5FA43287-34F4-4CBC-91C0-E92718AE31F0}") JScriptGroup_FutureClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{0129A47F-30BE-4B1D-A632-C9B36486DC4C}") JScriptGroup_Future  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptGroup_Future : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_FutureClass,_di_JScriptGroup_Future>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_FutureClass,_di_JScriptGroup_Future> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptGroup_Future() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_FutureClass,_di_JScriptGroup_Future>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptGroup_Future() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{26F8BA5F-62A3-4316-A282-EA0CBFAA5C4C}") JScriptGroup_InputClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{EC9FDE93-BD29-4BBB-9009-AE8E4DC3B918}") JScriptGroup_Input  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptGroup_Input : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_InputClass,_di_JScriptGroup_Input>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_InputClass,_di_JScriptGroup_Input> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptGroup_Input() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptGroup_InputClass,_di_JScriptGroup_Input>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptGroup_Input() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EFFAD6DF-A3D4-461C-B594-851D221474ED}") JScriptIntrinsicClass  : public JScriptClass 
{
	
};

__interface  INTERFACE_UUID("{584A2682-B1D5-4DD4-A5DD-CBCF599E52E8}") JScriptIntrinsic  : public JScript 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsic : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicClass,_di_JScriptIntrinsic>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicClass,_di_JScriptIntrinsic> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsic() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicClass,_di_JScriptIntrinsic>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsic() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C3C054BB-29E9-42EC-825E-B399F5D382FE}") JScriptIntrinsic3DLUTClass  : public JScriptIntrinsicClass 
{
	virtual _di_JScriptIntrinsic3DLUT __cdecl create(_di_JRenderScript rs, _di_Jrenderscript_Element e) = 0 ;
};

__interface  INTERFACE_UUID("{BAB26680-9347-44A2-AC20-3020D3596C69}") JScriptIntrinsic3DLUT  : public JScriptIntrinsic 
{
	virtual void __cdecl forEach(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEach(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual _di_JScript_KernelID __cdecl getKernelID() = 0 ;
	virtual void __cdecl setLUT(_di_JAllocation lut) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsic3DLUT : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsic3DLUTClass,_di_JScriptIntrinsic3DLUT>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsic3DLUTClass,_di_JScriptIntrinsic3DLUT> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsic3DLUT() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsic3DLUTClass,_di_JScriptIntrinsic3DLUT>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsic3DLUT() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{40581C44-819D-4AF0-B944-F34A6948AEBE}") JScriptIntrinsicBLASClass  : public JScriptIntrinsicClass 
{
	virtual int __cdecl _GetCONJ_TRANSPOSE() = 0 ;
	virtual int __cdecl _GetLEFT() = 0 ;
	virtual int __cdecl _GetLOWER() = 0 ;
	virtual int __cdecl _GetNON_UNIT() = 0 ;
	virtual int __cdecl _GetNO_TRANSPOSE() = 0 ;
	virtual int __cdecl _GetRIGHT() = 0 ;
	virtual int __cdecl _GetTRANSPOSE() = 0 ;
	virtual int __cdecl _GetUNIT() = 0 ;
	virtual int __cdecl _GetUPPER() = 0 ;
	virtual _di_JScriptIntrinsicBLAS __cdecl create(_di_JRenderScript rs) = 0 ;
	__property int CONJ_TRANSPOSE = {read=_GetCONJ_TRANSPOSE};
	__property int LEFT = {read=_GetLEFT};
	__property int LOWER = {read=_GetLOWER};
	__property int NON_UNIT = {read=_GetNON_UNIT};
	__property int NO_TRANSPOSE = {read=_GetNO_TRANSPOSE};
	__property int RIGHT = {read=_GetRIGHT};
	__property int TRANSPOSE = {read=_GetTRANSPOSE};
	__property int UNIT = {read=_GetUNIT};
	__property int UPPER = {read=_GetUPPER};
};

__interface  INTERFACE_UUID("{5612542C-48B4-47DE-90BC-A98935B00215}") JScriptIntrinsicBLAS  : public JScriptIntrinsic 
{
	virtual void __cdecl BNNM(_di_JAllocation A, int a_offset, _di_JAllocation B, int b_offset, _di_JAllocation C, int c_offset, int c_mult) = 0 ;
	virtual void __cdecl CGBMV(int TransA, int KL, int KU, _di_JFloat2 alpha, _di_JAllocation A, _di_JAllocation X, int incX, _di_JFloat2 beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl CGEMM(int TransA, int TransB, _di_JFloat2 alpha, _di_JAllocation A, _di_JAllocation B, _di_JFloat2 beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl CGEMV(int TransA, _di_JFloat2 alpha, _di_JAllocation A, _di_JAllocation X, int incX, _di_JFloat2 beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl CGERC(_di_JFloat2 alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation A) = 0 ;
	virtual void __cdecl CGERU(_di_JFloat2 alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation A) = 0 ;
	virtual void __cdecl CHBMV(int Uplo, int K, _di_JFloat2 alpha, _di_JAllocation A, _di_JAllocation X, int incX, _di_JFloat2 beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl CHEMM(int Side, int Uplo, _di_JFloat2 alpha, _di_JAllocation A, _di_JAllocation B, _di_JFloat2 beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl CHEMV(int Uplo, _di_JFloat2 alpha, _di_JAllocation A, _di_JAllocation X, int incX, _di_JFloat2 beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl CHER(int Uplo, float alpha, _di_JAllocation X, int incX, _di_JAllocation A) = 0 ;
	virtual void __cdecl CHER2(int Uplo, _di_JFloat2 alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation A) = 0 ;
	virtual void __cdecl CHER2K(int Uplo, int Trans, _di_JFloat2 alpha, _di_JAllocation A, _di_JAllocation B, float beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl CHERK(int Uplo, int Trans, float alpha, _di_JAllocation A, float beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl CHPMV(int Uplo, _di_JFloat2 alpha, _di_JAllocation Ap, _di_JAllocation X, int incX, _di_JFloat2 beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl CHPR(int Uplo, float alpha, _di_JAllocation X, int incX, _di_JAllocation Ap) = 0 ;
	virtual void __cdecl CHPR2(int Uplo, _di_JFloat2 alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation Ap) = 0 ;
	virtual void __cdecl CSYMM(int Side, int Uplo, _di_JFloat2 alpha, _di_JAllocation A, _di_JAllocation B, _di_JFloat2 beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl CSYR2K(int Uplo, int Trans, _di_JFloat2 alpha, _di_JAllocation A, _di_JAllocation B, _di_JFloat2 beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl CSYRK(int Uplo, int Trans, _di_JFloat2 alpha, _di_JAllocation A, _di_JFloat2 beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl CTBMV(int Uplo, int TransA, int Diag, int K, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl CTBSV(int Uplo, int TransA, int Diag, int K, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl CTPMV(int Uplo, int TransA, int Diag, _di_JAllocation Ap, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl CTPSV(int Uplo, int TransA, int Diag, _di_JAllocation Ap, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl CTRMM(int Side, int Uplo, int TransA, int Diag, _di_JFloat2 alpha, _di_JAllocation A, _di_JAllocation B) = 0 ;
	virtual void __cdecl CTRMV(int Uplo, int TransA, int Diag, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl CTRSM(int Side, int Uplo, int TransA, int Diag, _di_JFloat2 alpha, _di_JAllocation A, _di_JAllocation B) = 0 ;
	virtual void __cdecl CTRSV(int Uplo, int TransA, int Diag, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl DGBMV(int TransA, int KL, int KU, double alpha, _di_JAllocation A, _di_JAllocation X, int incX, double beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl DGEMM(int TransA, int TransB, double alpha, _di_JAllocation A, _di_JAllocation B, double beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl DGEMV(int TransA, double alpha, _di_JAllocation A, _di_JAllocation X, int incX, double beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl DGER(double alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation A) = 0 ;
	virtual void __cdecl DSBMV(int Uplo, int K, double alpha, _di_JAllocation A, _di_JAllocation X, int incX, double beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl DSPMV(int Uplo, double alpha, _di_JAllocation Ap, _di_JAllocation X, int incX, double beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl DSPR(int Uplo, double alpha, _di_JAllocation X, int incX, _di_JAllocation Ap) = 0 ;
	virtual void __cdecl DSPR2(int Uplo, double alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation Ap) = 0 ;
	virtual void __cdecl DSYMM(int Side, int Uplo, double alpha, _di_JAllocation A, _di_JAllocation B, double beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl DSYMV(int Uplo, double alpha, _di_JAllocation A, _di_JAllocation X, int incX, double beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl DSYR(int Uplo, double alpha, _di_JAllocation X, int incX, _di_JAllocation A) = 0 ;
	virtual void __cdecl DSYR2(int Uplo, double alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation A) = 0 ;
	virtual void __cdecl DSYR2K(int Uplo, int Trans, double alpha, _di_JAllocation A, _di_JAllocation B, double beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl DSYRK(int Uplo, int Trans, double alpha, _di_JAllocation A, double beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl DTBMV(int Uplo, int TransA, int Diag, int K, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl DTBSV(int Uplo, int TransA, int Diag, int K, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl DTPMV(int Uplo, int TransA, int Diag, _di_JAllocation Ap, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl DTPSV(int Uplo, int TransA, int Diag, _di_JAllocation Ap, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl DTRMM(int Side, int Uplo, int TransA, int Diag, double alpha, _di_JAllocation A, _di_JAllocation B) = 0 ;
	virtual void __cdecl DTRMV(int Uplo, int TransA, int Diag, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl DTRSM(int Side, int Uplo, int TransA, int Diag, double alpha, _di_JAllocation A, _di_JAllocation B) = 0 ;
	virtual void __cdecl DTRSV(int Uplo, int TransA, int Diag, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl SGBMV(int TransA, int KL, int KU, float alpha, _di_JAllocation A, _di_JAllocation X, int incX, float beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl SGEMM(int TransA, int TransB, float alpha, _di_JAllocation A, _di_JAllocation B, float beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl SGEMV(int TransA, float alpha, _di_JAllocation A, _di_JAllocation X, int incX, float beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl SGER(float alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation A) = 0 ;
	virtual void __cdecl SSBMV(int Uplo, int K, float alpha, _di_JAllocation A, _di_JAllocation X, int incX, float beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl SSPMV(int Uplo, float alpha, _di_JAllocation Ap, _di_JAllocation X, int incX, float beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl SSPR(int Uplo, float alpha, _di_JAllocation X, int incX, _di_JAllocation Ap) = 0 ;
	virtual void __cdecl SSPR2(int Uplo, float alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation Ap) = 0 ;
	virtual void __cdecl SSYMM(int Side, int Uplo, float alpha, _di_JAllocation A, _di_JAllocation B, float beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl SSYMV(int Uplo, float alpha, _di_JAllocation A, _di_JAllocation X, int incX, float beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl SSYR(int Uplo, float alpha, _di_JAllocation X, int incX, _di_JAllocation A) = 0 ;
	virtual void __cdecl SSYR2(int Uplo, float alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation A) = 0 ;
	virtual void __cdecl SSYR2K(int Uplo, int Trans, float alpha, _di_JAllocation A, _di_JAllocation B, float beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl SSYRK(int Uplo, int Trans, float alpha, _di_JAllocation A, float beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl STBMV(int Uplo, int TransA, int Diag, int K, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl STBSV(int Uplo, int TransA, int Diag, int K, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl STPMV(int Uplo, int TransA, int Diag, _di_JAllocation Ap, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl STPSV(int Uplo, int TransA, int Diag, _di_JAllocation Ap, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl STRMM(int Side, int Uplo, int TransA, int Diag, float alpha, _di_JAllocation A, _di_JAllocation B) = 0 ;
	virtual void __cdecl STRMV(int Uplo, int TransA, int Diag, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl STRSM(int Side, int Uplo, int TransA, int Diag, float alpha, _di_JAllocation A, _di_JAllocation B) = 0 ;
	virtual void __cdecl STRSV(int Uplo, int TransA, int Diag, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl ZGBMV(int TransA, int KL, int KU, _di_JDouble2 alpha, _di_JAllocation A, _di_JAllocation X, int incX, _di_JDouble2 beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl ZGEMM(int TransA, int TransB, _di_JDouble2 alpha, _di_JAllocation A, _di_JAllocation B, _di_JDouble2 beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl ZGEMV(int TransA, _di_JDouble2 alpha, _di_JAllocation A, _di_JAllocation X, int incX, _di_JDouble2 beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl ZGERC(_di_JDouble2 alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation A) = 0 ;
	virtual void __cdecl ZGERU(_di_JDouble2 alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation A) = 0 ;
	virtual void __cdecl ZHBMV(int Uplo, int K, _di_JDouble2 alpha, _di_JAllocation A, _di_JAllocation X, int incX, _di_JDouble2 beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl ZHEMM(int Side, int Uplo, _di_JDouble2 alpha, _di_JAllocation A, _di_JAllocation B, _di_JDouble2 beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl ZHEMV(int Uplo, _di_JDouble2 alpha, _di_JAllocation A, _di_JAllocation X, int incX, _di_JDouble2 beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl ZHER(int Uplo, double alpha, _di_JAllocation X, int incX, _di_JAllocation A) = 0 ;
	virtual void __cdecl ZHER2(int Uplo, _di_JDouble2 alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation A) = 0 ;
	virtual void __cdecl ZHER2K(int Uplo, int Trans, _di_JDouble2 alpha, _di_JAllocation A, _di_JAllocation B, double beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl ZHERK(int Uplo, int Trans, double alpha, _di_JAllocation A, double beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl ZHPMV(int Uplo, _di_JDouble2 alpha, _di_JAllocation Ap, _di_JAllocation X, int incX, _di_JDouble2 beta, _di_JAllocation Y, int incY) = 0 ;
	virtual void __cdecl ZHPR(int Uplo, double alpha, _di_JAllocation X, int incX, _di_JAllocation Ap) = 0 ;
	virtual void __cdecl ZHPR2(int Uplo, _di_JDouble2 alpha, _di_JAllocation X, int incX, _di_JAllocation Y, int incY, _di_JAllocation Ap) = 0 ;
	virtual void __cdecl ZSYMM(int Side, int Uplo, _di_JDouble2 alpha, _di_JAllocation A, _di_JAllocation B, _di_JDouble2 beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl ZSYR2K(int Uplo, int Trans, _di_JDouble2 alpha, _di_JAllocation A, _di_JAllocation B, _di_JDouble2 beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl ZSYRK(int Uplo, int Trans, _di_JDouble2 alpha, _di_JAllocation A, _di_JDouble2 beta, _di_JAllocation C) = 0 ;
	virtual void __cdecl ZTBMV(int Uplo, int TransA, int Diag, int K, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl ZTBSV(int Uplo, int TransA, int Diag, int K, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl ZTPMV(int Uplo, int TransA, int Diag, _di_JAllocation Ap, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl ZTPSV(int Uplo, int TransA, int Diag, _di_JAllocation Ap, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl ZTRMM(int Side, int Uplo, int TransA, int Diag, _di_JDouble2 alpha, _di_JAllocation A, _di_JAllocation B) = 0 ;
	virtual void __cdecl ZTRMV(int Uplo, int TransA, int Diag, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
	virtual void __cdecl ZTRSM(int Side, int Uplo, int TransA, int Diag, _di_JDouble2 alpha, _di_JAllocation A, _di_JAllocation B) = 0 ;
	virtual void __cdecl ZTRSV(int Uplo, int TransA, int Diag, _di_JAllocation A, _di_JAllocation X, int incX) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsicBLAS : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicBLASClass,_di_JScriptIntrinsicBLAS>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicBLASClass,_di_JScriptIntrinsicBLAS> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsicBLAS() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicBLASClass,_di_JScriptIntrinsicBLAS>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsicBLAS() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7CA741B4-F235-4661-8EBD-39A36ABF073D}") JScriptIntrinsicBlendClass  : public JScriptIntrinsicClass 
{
	virtual _di_JScriptIntrinsicBlend __cdecl create(_di_JRenderScript rs, _di_Jrenderscript_Element e) = 0 ;
};

__interface  INTERFACE_UUID("{8F609357-C61C-4D34-8B24-08FD277E70F4}") JScriptIntrinsicBlend  : public JScriptIntrinsic 
{
	virtual void __cdecl forEachAdd(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachAdd(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachClear(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachClear(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachDst(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachDst(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachDstAtop(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachDstAtop(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachDstIn(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachDstIn(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachDstOut(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachDstOut(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachDstOver(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachDstOver(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachMultiply(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachMultiply(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachSrc(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachSrc(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachSrcAtop(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachSrcAtop(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachSrcIn(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachSrcIn(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachSrcOut(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachSrcOut(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachSrcOver(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachSrcOver(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachSubtract(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachSubtract(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEachXor(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEachXor(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual _di_JScript_KernelID __cdecl getKernelIDAdd() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDClear() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDDst() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDDstAtop() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDDstIn() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDDstOut() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDDstOver() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDMultiply() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDSrc() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDSrcAtop() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDSrcIn() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDSrcOut() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDSrcOver() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDSubtract() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelIDXor() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsicBlend : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicBlendClass,_di_JScriptIntrinsicBlend>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicBlendClass,_di_JScriptIntrinsicBlend> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsicBlend() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicBlendClass,_di_JScriptIntrinsicBlend>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsicBlend() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{38491E8D-407C-4BA3-86D4-FE5A6419C4CB}") JScriptIntrinsicBlurClass  : public JScriptIntrinsicClass 
{
	virtual _di_JScriptIntrinsicBlur __cdecl create(_di_JRenderScript rs, _di_Jrenderscript_Element e) = 0 ;
};

__interface  INTERFACE_UUID("{63EE931E-7DE6-468A-B5A8-6ACC301BCAF7}") JScriptIntrinsicBlur  : public JScriptIntrinsic 
{
	virtual void __cdecl forEach(_di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEach(_di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual _di_JScript_FieldID __cdecl getFieldID_Input() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelID() = 0 ;
	virtual void __cdecl setInput(_di_JAllocation ain) = 0 ;
	virtual void __cdecl setRadius(float radius) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsicBlur : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicBlurClass,_di_JScriptIntrinsicBlur>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicBlurClass,_di_JScriptIntrinsicBlur> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsicBlur() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicBlurClass,_di_JScriptIntrinsicBlur>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsicBlur() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F662D945-89C0-4E5E-9653-3C0A934F298C}") JScriptIntrinsicColorMatrixClass  : public JScriptIntrinsicClass 
{
	virtual _di_JScriptIntrinsicColorMatrix __cdecl create(_di_JRenderScript rs, _di_Jrenderscript_Element e) = 0 /* overload */;
	virtual _di_JScriptIntrinsicColorMatrix __cdecl create(_di_JRenderScript rs) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{4A785F7C-1096-4C91-BE13-9CC5CE6F560F}") JScriptIntrinsicColorMatrix  : public JScriptIntrinsic 
{
	virtual void __cdecl forEach(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEach(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual _di_JScript_KernelID __cdecl getKernelID() = 0 ;
	virtual void __cdecl setAdd(_di_JFloat4 f) = 0 /* overload */;
	virtual void __cdecl setAdd(float r, float g, float b, float a) = 0 /* overload */;
	virtual void __cdecl setColorMatrix(_di_JMatrix4f m) = 0 /* overload */;
	virtual void __cdecl setColorMatrix(_di_JMatrix3f m) = 0 /* overload */;
	virtual void __cdecl setGreyscale() = 0 ;
	virtual void __cdecl setRGBtoYUV() = 0 ;
	virtual void __cdecl setYUVtoRGB() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsicColorMatrix : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicColorMatrixClass,_di_JScriptIntrinsicColorMatrix>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicColorMatrixClass,_di_JScriptIntrinsicColorMatrix> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsicColorMatrix() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicColorMatrixClass,_di_JScriptIntrinsicColorMatrix>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsicColorMatrix() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{97FF9326-FF80-4D24-B546-3A053102D03F}") JScriptIntrinsicConvolve3x3Class  : public JScriptIntrinsicClass 
{
	virtual _di_JScriptIntrinsicConvolve3x3 __cdecl create(_di_JRenderScript rs, _di_Jrenderscript_Element e) = 0 ;
};

__interface  INTERFACE_UUID("{223BE7FC-0B99-42BD-A984-B96A3746E9B6}") JScriptIntrinsicConvolve3x3  : public JScriptIntrinsic 
{
	virtual void __cdecl forEach(_di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEach(_di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual _di_JScript_FieldID __cdecl getFieldID_Input() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelID() = 0 ;
	virtual void __cdecl setCoefficients(Androidapi::Jnibridge::TJavaArray__1<float>* v) = 0 ;
	virtual void __cdecl setInput(_di_JAllocation ain) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsicConvolve3x3 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicConvolve3x3Class,_di_JScriptIntrinsicConvolve3x3>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicConvolve3x3Class,_di_JScriptIntrinsicConvolve3x3> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsicConvolve3x3() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicConvolve3x3Class,_di_JScriptIntrinsicConvolve3x3>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsicConvolve3x3() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5A6A9A23-2FFC-430E-BA36-80AD7C05D067}") JScriptIntrinsicConvolve5x5Class  : public JScriptIntrinsicClass 
{
	virtual _di_JScriptIntrinsicConvolve5x5 __cdecl create(_di_JRenderScript rs, _di_Jrenderscript_Element e) = 0 ;
};

__interface  INTERFACE_UUID("{31407942-C83C-4341-BA48-73D0AD667C3C}") JScriptIntrinsicConvolve5x5  : public JScriptIntrinsic 
{
	virtual void __cdecl forEach(_di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEach(_di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual _di_JScript_FieldID __cdecl getFieldID_Input() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelID() = 0 ;
	virtual void __cdecl setCoefficients(Androidapi::Jnibridge::TJavaArray__1<float>* v) = 0 ;
	virtual void __cdecl setInput(_di_JAllocation ain) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsicConvolve5x5 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicConvolve5x5Class,_di_JScriptIntrinsicConvolve5x5>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicConvolve5x5Class,_di_JScriptIntrinsicConvolve5x5> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsicConvolve5x5() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicConvolve5x5Class,_di_JScriptIntrinsicConvolve5x5>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsicConvolve5x5() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{870E7DC1-4E6C-426D-BF19-45B400408680}") JScriptIntrinsicHistogramClass  : public JScriptIntrinsicClass 
{
	virtual _di_JScriptIntrinsicHistogram __cdecl create(_di_JRenderScript rs, _di_Jrenderscript_Element e) = 0 ;
};

__interface  INTERFACE_UUID("{4D59E7CE-58C5-4CD6-ADA6-1F183D9C0D9B}") JScriptIntrinsicHistogram  : public JScriptIntrinsic 
{
	virtual void __cdecl forEach(_di_JAllocation ain) = 0 /* overload */;
	virtual void __cdecl forEach(_di_JAllocation ain, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual void __cdecl forEach_Dot(_di_JAllocation ain) = 0 /* overload */;
	virtual void __cdecl forEach_Dot(_di_JAllocation ain, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual _di_JScript_FieldID __cdecl getFieldID_Input() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelID_Separate() = 0 ;
	virtual void __cdecl setDotCoefficients(float r, float g, float b, float a) = 0 ;
	virtual void __cdecl setOutput(_di_JAllocation aout) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsicHistogram : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicHistogramClass,_di_JScriptIntrinsicHistogram>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicHistogramClass,_di_JScriptIntrinsicHistogram> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsicHistogram() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicHistogramClass,_di_JScriptIntrinsicHistogram>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsicHistogram() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AF117583-280C-467D-A777-FAD4C723E932}") JScriptIntrinsicLUTClass  : public JScriptIntrinsicClass 
{
	virtual _di_JScriptIntrinsicLUT __cdecl create(_di_JRenderScript rs, _di_Jrenderscript_Element e) = 0 ;
};

__interface  INTERFACE_UUID("{AB6CA036-20C9-4AC9-9D66-0E4735CBDE6E}") JScriptIntrinsicLUT  : public JScriptIntrinsic 
{
	HIDESBASE virtual void __cdecl destroy() = 0 ;
	virtual void __cdecl forEach(_di_JAllocation ain, _di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEach(_di_JAllocation ain, _di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual _di_JScript_KernelID __cdecl getKernelID() = 0 ;
	virtual void __cdecl setAlpha(int index, int value) = 0 ;
	virtual void __cdecl setBlue(int index, int value) = 0 ;
	virtual void __cdecl setGreen(int index, int value) = 0 ;
	virtual void __cdecl setRed(int index, int value) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsicLUT : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicLUTClass,_di_JScriptIntrinsicLUT>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicLUTClass,_di_JScriptIntrinsicLUT> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsicLUT() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicLUTClass,_di_JScriptIntrinsicLUT>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsicLUT() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{09C122BE-D6AA-45B4-BE38-EE4DA5529B12}") JScriptIntrinsicResizeClass  : public JScriptIntrinsicClass 
{
	virtual _di_JScriptIntrinsicResize __cdecl create(_di_JRenderScript rs) = 0 ;
};

__interface  INTERFACE_UUID("{23934D18-3078-4D91-B96C-9DDFE28B9756}") JScriptIntrinsicResize  : public JScriptIntrinsic 
{
	virtual void __cdecl forEach_bicubic(_di_JAllocation aout) = 0 /* overload */;
	virtual void __cdecl forEach_bicubic(_di_JAllocation aout, _di_JScript_LaunchOptions opt) = 0 /* overload */;
	virtual _di_JScript_FieldID __cdecl getFieldID_Input() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelID_bicubic() = 0 ;
	virtual void __cdecl setInput(_di_JAllocation ain) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsicResize : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicResizeClass,_di_JScriptIntrinsicResize>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicResizeClass,_di_JScriptIntrinsicResize> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsicResize() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicResizeClass,_di_JScriptIntrinsicResize>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsicResize() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A4F423A2-7CE4-4DB5-8E2D-CFE990CAB744}") JScriptIntrinsicYuvToRGBClass  : public JScriptIntrinsicClass 
{
	virtual _di_JScriptIntrinsicYuvToRGB __cdecl create(_di_JRenderScript rs, _di_Jrenderscript_Element e) = 0 ;
};

__interface  INTERFACE_UUID("{9883EE76-C5FF-4D2C-9A5D-AF574136F5E3}") JScriptIntrinsicYuvToRGB  : public JScriptIntrinsic 
{
	virtual void __cdecl forEach(_di_JAllocation aout) = 0 ;
	virtual _di_JScript_FieldID __cdecl getFieldID_Input() = 0 ;
	virtual _di_JScript_KernelID __cdecl getKernelID() = 0 ;
	virtual void __cdecl setInput(_di_JAllocation ain) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScriptIntrinsicYuvToRGB : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicYuvToRGBClass,_di_JScriptIntrinsicYuvToRGB>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicYuvToRGBClass,_di_JScriptIntrinsicYuvToRGB> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScriptIntrinsicYuvToRGB() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScriptIntrinsicYuvToRGBClass,_di_JScriptIntrinsicYuvToRGB>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScriptIntrinsicYuvToRGB() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{671EDDB5-33BC-4E9A-9E8C-03E19430D456}") JShort2Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JShort2 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JShort2 __cdecl init(short x, short y) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{3B138DD0-8A11-4342-A376-EB24993F932D}") JShort2  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual short __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(short Value) = 0 ;
	virtual short __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(short Value) = 0 ;
	__property short x = {read=_Getx, write=_Setx};
	__property short y = {read=_Gety, write=_Sety};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJShort2 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JShort2Class,_di_JShort2>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JShort2Class,_di_JShort2> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJShort2() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JShort2Class,_di_JShort2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJShort2() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0D00C53F-10D9-4531-ACEC-975204178548}") JShort3Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JShort3 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JShort3 __cdecl init(short x, short y, short z) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{2F5E58BB-0DA1-42D1-8854-5D5540789D54}") JShort3  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual short __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(short Value) = 0 ;
	virtual short __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(short Value) = 0 ;
	virtual short __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(short Value) = 0 ;
	__property short x = {read=_Getx, write=_Setx};
	__property short y = {read=_Gety, write=_Sety};
	__property short z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJShort3 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JShort3Class,_di_JShort3>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JShort3Class,_di_JShort3> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJShort3() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JShort3Class,_di_JShort3>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJShort3() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{80A95F44-C8C5-4D74-8619-DD1F8E877891}") JShort4Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JShort4 __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JShort4 __cdecl init(short x, short y, short z, short w) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{C33683EC-B50F-412D-9540-BE5D1188B931}") JShort4  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual short __cdecl _Getw() = 0 ;
	virtual void __cdecl _Setw(short Value) = 0 ;
	virtual short __cdecl _Getx() = 0 ;
	virtual void __cdecl _Setx(short Value) = 0 ;
	virtual short __cdecl _Gety() = 0 ;
	virtual void __cdecl _Sety(short Value) = 0 ;
	virtual short __cdecl _Getz() = 0 ;
	virtual void __cdecl _Setz(short Value) = 0 ;
	__property short w = {read=_Getw, write=_Setw};
	__property short x = {read=_Getx, write=_Setx};
	__property short y = {read=_Gety, write=_Sety};
	__property short z = {read=_Getz, write=_Setz};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJShort4 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JShort4Class,_di_JShort4>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JShort4Class,_di_JShort4> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJShort4() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JShort4Class,_di_JShort4>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJShort4() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EA772550-90A2-4831-A62F-063EC75F6402}") JTypeClass  : public JBaseObjClass 
{
	virtual _di_JType __cdecl createX(_di_JRenderScript rs, _di_Jrenderscript_Element e, int dimX) = 0 ;
	virtual _di_JType __cdecl createXY(_di_JRenderScript rs, _di_Jrenderscript_Element e, int dimX, int dimY) = 0 ;
	virtual _di_JType __cdecl createXYZ(_di_JRenderScript rs, _di_Jrenderscript_Element e, int dimX, int dimY, int dimZ) = 0 ;
};

__interface  INTERFACE_UUID("{1EC7E148-3497-4D42-AF8C-67FF257EECFD}") JType  : public JBaseObj 
{
	virtual int __cdecl getCount() = 0 ;
	virtual _di_Jrenderscript_Element __cdecl getElement() = 0 ;
	virtual int __cdecl getX() = 0 ;
	virtual int __cdecl getY() = 0 ;
	virtual int __cdecl getYuv() = 0 ;
	virtual int __cdecl getZ() = 0 ;
	virtual bool __cdecl hasFaces() = 0 ;
	virtual bool __cdecl hasMipmaps() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJType : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTypeClass,_di_JType>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTypeClass,_di_JType> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJType() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTypeClass,_di_JType>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJType() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{76A458CF-E09E-427D-8FFA-F0F601C7FEA7}") JType_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JType_Builder __cdecl init(_di_JRenderScript rs, _di_Jrenderscript_Element e) = 0 ;
};

__interface  INTERFACE_UUID("{18D670D4-F7E5-4808-948F-A446D3ABE4E3}") JType_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JType __cdecl create() = 0 ;
	virtual _di_JType_Builder __cdecl setFaces(bool value) = 0 ;
	virtual _di_JType_Builder __cdecl setMipmaps(bool value) = 0 ;
	virtual _di_JType_Builder __cdecl setX(int value) = 0 ;
	virtual _di_JType_Builder __cdecl setY(int value) = 0 ;
	virtual _di_JType_Builder __cdecl setYuvFormat(int yuvFormat) = 0 ;
	virtual _di_JType_Builder __cdecl setZ(int value) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJType_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JType_BuilderClass,_di_JType_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JType_BuilderClass,_di_JType_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJType_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JType_BuilderClass,_di_JType_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJType_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AB16FAD5-6539-42A1-B2CF-2E59843FFA3F}") JType_CubemapFaceClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JType_CubemapFace __cdecl _GetNEGATIVE_X() = 0 ;
	virtual _di_JType_CubemapFace __cdecl _GetNEGATIVE_Y() = 0 ;
	virtual _di_JType_CubemapFace __cdecl _GetNEGATIVE_Z() = 0 ;
	virtual _di_JType_CubemapFace __cdecl _GetPOSITIVE_X() = 0 ;
	virtual _di_JType_CubemapFace __cdecl _GetPOSITIVE_Y() = 0 ;
	virtual _di_JType_CubemapFace __cdecl _GetPOSITIVE_Z() = 0 ;
	virtual _di_JType_CubemapFace __cdecl _GetPOSITVE_X() = 0 ;
	virtual _di_JType_CubemapFace __cdecl _GetPOSITVE_Y() = 0 ;
	virtual _di_JType_CubemapFace __cdecl _GetPOSITVE_Z() = 0 ;
	HIDESBASE virtual _di_JType_CubemapFace __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JType_CubemapFace>* __cdecl values() = 0 ;
	__property _di_JType_CubemapFace NEGATIVE_X = {read=_GetNEGATIVE_X};
	__property _di_JType_CubemapFace NEGATIVE_Y = {read=_GetNEGATIVE_Y};
	__property _di_JType_CubemapFace NEGATIVE_Z = {read=_GetNEGATIVE_Z};
	__property _di_JType_CubemapFace POSITIVE_X = {read=_GetPOSITIVE_X};
	__property _di_JType_CubemapFace POSITIVE_Y = {read=_GetPOSITIVE_Y};
	__property _di_JType_CubemapFace POSITIVE_Z = {read=_GetPOSITIVE_Z};
	__property _di_JType_CubemapFace POSITVE_X = {read=_GetPOSITVE_X};
	__property _di_JType_CubemapFace POSITVE_Y = {read=_GetPOSITVE_Y};
	__property _di_JType_CubemapFace POSITVE_Z = {read=_GetPOSITVE_Z};
};

__interface  INTERFACE_UUID("{7E789A7C-6CDD-4989-8631-B587F9DB3A20}") JType_CubemapFace  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJType_CubemapFace : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JType_CubemapFaceClass,_di_JType_CubemapFace>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JType_CubemapFaceClass,_di_JType_CubemapFace> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJType_CubemapFace() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JType_CubemapFaceClass,_di_JType_CubemapFace>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJType_CubemapFace() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Renderscript */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_RENDERSCRIPT)
using namespace Androidapi::Jni::Renderscript;
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
#endif	// Androidapi_Jni_RenderscriptHPP
