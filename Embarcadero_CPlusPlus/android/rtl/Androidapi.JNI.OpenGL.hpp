// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.OpenGL.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_OpenglHPP
#define Androidapi_Jni_OpenglHPP

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
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Opengl
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JEGL14Class;
typedef System::DelphiInterface<JEGL14Class> _di_JEGL14Class;
__interface DELPHIINTERFACE JEGL14;
typedef System::DelphiInterface<JEGL14> _di_JEGL14;
class DELPHICLASS TJEGL14;
__interface DELPHIINTERFACE JEGLObjectHandleClass;
typedef System::DelphiInterface<JEGLObjectHandleClass> _di_JEGLObjectHandleClass;
__interface DELPHIINTERFACE JEGLObjectHandle;
typedef System::DelphiInterface<JEGLObjectHandle> _di_JEGLObjectHandle;
class DELPHICLASS TJEGLObjectHandle;
__interface DELPHIINTERFACE Jopengl_EGLConfigClass;
typedef System::DelphiInterface<Jopengl_EGLConfigClass> _di_Jopengl_EGLConfigClass;
__interface DELPHIINTERFACE Jopengl_EGLConfig;
typedef System::DelphiInterface<Jopengl_EGLConfig> _di_Jopengl_EGLConfig;
class DELPHICLASS TJopengl_EGLConfig;
__interface DELPHIINTERFACE Jopengl_EGLContextClass;
typedef System::DelphiInterface<Jopengl_EGLContextClass> _di_Jopengl_EGLContextClass;
__interface DELPHIINTERFACE Jopengl_EGLContext;
typedef System::DelphiInterface<Jopengl_EGLContext> _di_Jopengl_EGLContext;
class DELPHICLASS TJopengl_EGLContext;
__interface DELPHIINTERFACE Jopengl_EGLDisplayClass;
typedef System::DelphiInterface<Jopengl_EGLDisplayClass> _di_Jopengl_EGLDisplayClass;
__interface DELPHIINTERFACE Jopengl_EGLDisplay;
typedef System::DelphiInterface<Jopengl_EGLDisplay> _di_Jopengl_EGLDisplay;
class DELPHICLASS TJopengl_EGLDisplay;
__interface DELPHIINTERFACE JEGLExtClass;
typedef System::DelphiInterface<JEGLExtClass> _di_JEGLExtClass;
__interface DELPHIINTERFACE JEGLExt;
typedef System::DelphiInterface<JEGLExt> _di_JEGLExt;
class DELPHICLASS TJEGLExt;
__interface DELPHIINTERFACE Jopengl_EGLSurfaceClass;
typedef System::DelphiInterface<Jopengl_EGLSurfaceClass> _di_Jopengl_EGLSurfaceClass;
__interface DELPHIINTERFACE Jopengl_EGLSurface;
typedef System::DelphiInterface<Jopengl_EGLSurface> _di_Jopengl_EGLSurface;
class DELPHICLASS TJopengl_EGLSurface;
__interface DELPHIINTERFACE JETC1Class;
typedef System::DelphiInterface<JETC1Class> _di_JETC1Class;
__interface DELPHIINTERFACE JETC1;
typedef System::DelphiInterface<JETC1> _di_JETC1;
class DELPHICLASS TJETC1;
__interface DELPHIINTERFACE JETC1UtilClass;
typedef System::DelphiInterface<JETC1UtilClass> _di_JETC1UtilClass;
__interface DELPHIINTERFACE JETC1Util;
typedef System::DelphiInterface<JETC1Util> _di_JETC1Util;
class DELPHICLASS TJETC1Util;
__interface DELPHIINTERFACE JETC1Util_ETC1TextureClass;
typedef System::DelphiInterface<JETC1Util_ETC1TextureClass> _di_JETC1Util_ETC1TextureClass;
__interface DELPHIINTERFACE JETC1Util_ETC1Texture;
typedef System::DelphiInterface<JETC1Util_ETC1Texture> _di_JETC1Util_ETC1Texture;
class DELPHICLASS TJETC1Util_ETC1Texture;
__interface DELPHIINTERFACE JGLDebugHelperClass;
typedef System::DelphiInterface<JGLDebugHelperClass> _di_JGLDebugHelperClass;
__interface DELPHIINTERFACE JGLDebugHelper;
typedef System::DelphiInterface<JGLDebugHelper> _di_JGLDebugHelper;
class DELPHICLASS TJGLDebugHelper;
__interface DELPHIINTERFACE JGLES10Class;
typedef System::DelphiInterface<JGLES10Class> _di_JGLES10Class;
__interface DELPHIINTERFACE JGLES10;
typedef System::DelphiInterface<JGLES10> _di_JGLES10;
class DELPHICLASS TJGLES10;
__interface DELPHIINTERFACE JGLES10ExtClass;
typedef System::DelphiInterface<JGLES10ExtClass> _di_JGLES10ExtClass;
__interface DELPHIINTERFACE JGLES10Ext;
typedef System::DelphiInterface<JGLES10Ext> _di_JGLES10Ext;
class DELPHICLASS TJGLES10Ext;
__interface DELPHIINTERFACE JGLES11Class;
typedef System::DelphiInterface<JGLES11Class> _di_JGLES11Class;
__interface DELPHIINTERFACE JGLES11;
typedef System::DelphiInterface<JGLES11> _di_JGLES11;
class DELPHICLASS TJGLES11;
__interface DELPHIINTERFACE JGLES11ExtClass;
typedef System::DelphiInterface<JGLES11ExtClass> _di_JGLES11ExtClass;
__interface DELPHIINTERFACE JGLES11Ext;
typedef System::DelphiInterface<JGLES11Ext> _di_JGLES11Ext;
class DELPHICLASS TJGLES11Ext;
__interface DELPHIINTERFACE JGLES20Class;
typedef System::DelphiInterface<JGLES20Class> _di_JGLES20Class;
__interface DELPHIINTERFACE JGLES20;
typedef System::DelphiInterface<JGLES20> _di_JGLES20;
class DELPHICLASS TJGLES20;
__interface DELPHIINTERFACE JGLES30Class;
typedef System::DelphiInterface<JGLES30Class> _di_JGLES30Class;
__interface DELPHIINTERFACE JGLES30;
typedef System::DelphiInterface<JGLES30> _di_JGLES30;
class DELPHICLASS TJGLES30;
__interface DELPHIINTERFACE JGLES31Class;
typedef System::DelphiInterface<JGLES31Class> _di_JGLES31Class;
__interface DELPHIINTERFACE JGLES31;
typedef System::DelphiInterface<JGLES31> _di_JGLES31;
class DELPHICLASS TJGLES31;
__interface DELPHIINTERFACE JGLES31ExtClass;
typedef System::DelphiInterface<JGLES31ExtClass> _di_JGLES31ExtClass;
__interface DELPHIINTERFACE JGLES31Ext;
typedef System::DelphiInterface<JGLES31Ext> _di_JGLES31Ext;
class DELPHICLASS TJGLES31Ext;
__interface DELPHIINTERFACE JGLES31Ext_DebugProcKHRClass;
typedef System::DelphiInterface<JGLES31Ext_DebugProcKHRClass> _di_JGLES31Ext_DebugProcKHRClass;
__interface DELPHIINTERFACE JGLES31Ext_DebugProcKHR;
typedef System::DelphiInterface<JGLES31Ext_DebugProcKHR> _di_JGLES31Ext_DebugProcKHR;
class DELPHICLASS TJGLES31Ext_DebugProcKHR;
__interface DELPHIINTERFACE JGLES32Class;
typedef System::DelphiInterface<JGLES32Class> _di_JGLES32Class;
__interface DELPHIINTERFACE JGLES32;
typedef System::DelphiInterface<JGLES32> _di_JGLES32;
class DELPHICLASS TJGLES32;
__interface DELPHIINTERFACE JGLES32_DebugProcClass;
typedef System::DelphiInterface<JGLES32_DebugProcClass> _di_JGLES32_DebugProcClass;
__interface DELPHIINTERFACE JGLES32_DebugProc;
typedef System::DelphiInterface<JGLES32_DebugProc> _di_JGLES32_DebugProc;
class DELPHICLASS TJGLES32_DebugProc;
__interface DELPHIINTERFACE JGLExceptionClass;
typedef System::DelphiInterface<JGLExceptionClass> _di_JGLExceptionClass;
__interface DELPHIINTERFACE JGLException;
typedef System::DelphiInterface<JGLException> _di_JGLException;
class DELPHICLASS TJGLException;
__interface DELPHIINTERFACE JGLSurfaceViewClass;
typedef System::DelphiInterface<JGLSurfaceViewClass> _di_JGLSurfaceViewClass;
__interface DELPHIINTERFACE JGLSurfaceView;
typedef System::DelphiInterface<JGLSurfaceView> _di_JGLSurfaceView;
class DELPHICLASS TJGLSurfaceView;
__interface DELPHIINTERFACE JGLSurfaceView_EGLConfigChooserClass;
typedef System::DelphiInterface<JGLSurfaceView_EGLConfigChooserClass> _di_JGLSurfaceView_EGLConfigChooserClass;
__interface DELPHIINTERFACE JGLSurfaceView_EGLConfigChooser;
typedef System::DelphiInterface<JGLSurfaceView_EGLConfigChooser> _di_JGLSurfaceView_EGLConfigChooser;
class DELPHICLASS TJGLSurfaceView_EGLConfigChooser;
__interface DELPHIINTERFACE JGLSurfaceView_EGLContextFactoryClass;
typedef System::DelphiInterface<JGLSurfaceView_EGLContextFactoryClass> _di_JGLSurfaceView_EGLContextFactoryClass;
__interface DELPHIINTERFACE JGLSurfaceView_EGLContextFactory;
typedef System::DelphiInterface<JGLSurfaceView_EGLContextFactory> _di_JGLSurfaceView_EGLContextFactory;
class DELPHICLASS TJGLSurfaceView_EGLContextFactory;
__interface DELPHIINTERFACE JGLSurfaceView_EGLWindowSurfaceFactoryClass;
typedef System::DelphiInterface<JGLSurfaceView_EGLWindowSurfaceFactoryClass> _di_JGLSurfaceView_EGLWindowSurfaceFactoryClass;
__interface DELPHIINTERFACE JGLSurfaceView_EGLWindowSurfaceFactory;
typedef System::DelphiInterface<JGLSurfaceView_EGLWindowSurfaceFactory> _di_JGLSurfaceView_EGLWindowSurfaceFactory;
class DELPHICLASS TJGLSurfaceView_EGLWindowSurfaceFactory;
__interface DELPHIINTERFACE JGLSurfaceView_GLWrapperClass;
typedef System::DelphiInterface<JGLSurfaceView_GLWrapperClass> _di_JGLSurfaceView_GLWrapperClass;
__interface DELPHIINTERFACE JGLSurfaceView_GLWrapper;
typedef System::DelphiInterface<JGLSurfaceView_GLWrapper> _di_JGLSurfaceView_GLWrapper;
class DELPHICLASS TJGLSurfaceView_GLWrapper;
__interface DELPHIINTERFACE JGLSurfaceView_RendererClass;
typedef System::DelphiInterface<JGLSurfaceView_RendererClass> _di_JGLSurfaceView_RendererClass;
__interface DELPHIINTERFACE JGLSurfaceView_Renderer;
typedef System::DelphiInterface<JGLSurfaceView_Renderer> _di_JGLSurfaceView_Renderer;
class DELPHICLASS TJGLSurfaceView_Renderer;
__interface DELPHIINTERFACE JGLUClass;
typedef System::DelphiInterface<JGLUClass> _di_JGLUClass;
__interface DELPHIINTERFACE JGLU;
typedef System::DelphiInterface<JGLU> _di_JGLU;
class DELPHICLASS TJGLU;
__interface DELPHIINTERFACE JGLUtilsClass;
typedef System::DelphiInterface<JGLUtilsClass> _di_JGLUtilsClass;
__interface DELPHIINTERFACE JGLUtils;
typedef System::DelphiInterface<JGLUtils> _di_JGLUtils;
class DELPHICLASS TJGLUtils;
__interface DELPHIINTERFACE Jopengl_MatrixClass;
typedef System::DelphiInterface<Jopengl_MatrixClass> _di_Jopengl_MatrixClass;
__interface DELPHIINTERFACE Jopengl_Matrix;
typedef System::DelphiInterface<Jopengl_Matrix> _di_Jopengl_Matrix;
class DELPHICLASS TJopengl_Matrix;
__interface DELPHIINTERFACE JVisibilityClass;
typedef System::DelphiInterface<JVisibilityClass> _di_JVisibilityClass;
__interface DELPHIINTERFACE JVisibility;
typedef System::DelphiInterface<JVisibility> _di_JVisibility;
class DELPHICLASS TJVisibility;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{9310A9F9-6946-402D-8221-860ED16B719D}") JEGL14Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetEGL_ALPHA_MASK_SIZE() = 0 ;
	virtual int __cdecl _GetEGL_ALPHA_SIZE() = 0 ;
	virtual int __cdecl _GetEGL_BACK_BUFFER() = 0 ;
	virtual int __cdecl _GetEGL_BAD_ACCESS() = 0 ;
	virtual int __cdecl _GetEGL_BAD_ALLOC() = 0 ;
	virtual int __cdecl _GetEGL_BAD_ATTRIBUTE() = 0 ;
	virtual int __cdecl _GetEGL_BAD_CONFIG() = 0 ;
	virtual int __cdecl _GetEGL_BAD_CONTEXT() = 0 ;
	virtual int __cdecl _GetEGL_BAD_CURRENT_SURFACE() = 0 ;
	virtual int __cdecl _GetEGL_BAD_DISPLAY() = 0 ;
	virtual int __cdecl _GetEGL_BAD_MATCH() = 0 ;
	virtual int __cdecl _GetEGL_BAD_NATIVE_PIXMAP() = 0 ;
	virtual int __cdecl _GetEGL_BAD_NATIVE_WINDOW() = 0 ;
	virtual int __cdecl _GetEGL_BAD_PARAMETER() = 0 ;
	virtual int __cdecl _GetEGL_BAD_SURFACE() = 0 ;
	virtual int __cdecl _GetEGL_BIND_TO_TEXTURE_RGB() = 0 ;
	virtual int __cdecl _GetEGL_BIND_TO_TEXTURE_RGBA() = 0 ;
	virtual int __cdecl _GetEGL_BLUE_SIZE() = 0 ;
	virtual int __cdecl _GetEGL_BUFFER_DESTROYED() = 0 ;
	virtual int __cdecl _GetEGL_BUFFER_PRESERVED() = 0 ;
	virtual int __cdecl _GetEGL_BUFFER_SIZE() = 0 ;
	virtual int __cdecl _GetEGL_CLIENT_APIS() = 0 ;
	virtual int __cdecl _GetEGL_COLOR_BUFFER_TYPE() = 0 ;
	virtual int __cdecl _GetEGL_CONFIG_CAVEAT() = 0 ;
	virtual int __cdecl _GetEGL_CONFIG_ID() = 0 ;
	virtual int __cdecl _GetEGL_CONFORMANT() = 0 ;
	virtual int __cdecl _GetEGL_CONTEXT_CLIENT_TYPE() = 0 ;
	virtual int __cdecl _GetEGL_CONTEXT_CLIENT_VERSION() = 0 ;
	virtual int __cdecl _GetEGL_CONTEXT_LOST() = 0 ;
	virtual int __cdecl _GetEGL_CORE_NATIVE_ENGINE() = 0 ;
	virtual int __cdecl _GetEGL_DEFAULT_DISPLAY() = 0 ;
	virtual int __cdecl _GetEGL_DEPTH_SIZE() = 0 ;
	virtual int __cdecl _GetEGL_DISPLAY_SCALING() = 0 ;
	virtual int __cdecl _GetEGL_DRAW() = 0 ;
	virtual int __cdecl _GetEGL_EXTENSIONS() = 0 ;
	virtual int __cdecl _GetEGL_FALSE() = 0 ;
	virtual int __cdecl _GetEGL_GREEN_SIZE() = 0 ;
	virtual int __cdecl _GetEGL_HEIGHT() = 0 ;
	virtual int __cdecl _GetEGL_HORIZONTAL_RESOLUTION() = 0 ;
	virtual int __cdecl _GetEGL_LARGEST_PBUFFER() = 0 ;
	virtual int __cdecl _GetEGL_LEVEL() = 0 ;
	virtual int __cdecl _GetEGL_LUMINANCE_BUFFER() = 0 ;
	virtual int __cdecl _GetEGL_LUMINANCE_SIZE() = 0 ;
	virtual int __cdecl _GetEGL_MATCH_NATIVE_PIXMAP() = 0 ;
	virtual int __cdecl _GetEGL_MAX_PBUFFER_HEIGHT() = 0 ;
	virtual int __cdecl _GetEGL_MAX_PBUFFER_PIXELS() = 0 ;
	virtual int __cdecl _GetEGL_MAX_PBUFFER_WIDTH() = 0 ;
	virtual int __cdecl _GetEGL_MAX_SWAP_INTERVAL() = 0 ;
	virtual int __cdecl _GetEGL_MIN_SWAP_INTERVAL() = 0 ;
	virtual int __cdecl _GetEGL_MIPMAP_LEVEL() = 0 ;
	virtual int __cdecl _GetEGL_MIPMAP_TEXTURE() = 0 ;
	virtual int __cdecl _GetEGL_MULTISAMPLE_RESOLVE() = 0 ;
	virtual int __cdecl _GetEGL_MULTISAMPLE_RESOLVE_BOX() = 0 ;
	virtual int __cdecl _GetEGL_MULTISAMPLE_RESOLVE_BOX_BIT() = 0 ;
	virtual int __cdecl _GetEGL_MULTISAMPLE_RESOLVE_DEFAULT() = 0 ;
	virtual int __cdecl _GetEGL_NATIVE_RENDERABLE() = 0 ;
	virtual int __cdecl _GetEGL_NATIVE_VISUAL_ID() = 0 ;
	virtual int __cdecl _GetEGL_NATIVE_VISUAL_TYPE() = 0 ;
	virtual int __cdecl _GetEGL_NONE() = 0 ;
	virtual int __cdecl _GetEGL_NON_CONFORMANT_CONFIG() = 0 ;
	virtual int __cdecl _GetEGL_NOT_INITIALIZED() = 0 ;
	virtual _di_Jopengl_EGLContext __cdecl _GetEGL_NO_CONTEXT() = 0 ;
	virtual void __cdecl _SetEGL_NO_CONTEXT(_di_Jopengl_EGLContext Value) = 0 ;
	virtual _di_Jopengl_EGLDisplay __cdecl _GetEGL_NO_DISPLAY() = 0 ;
	virtual void __cdecl _SetEGL_NO_DISPLAY(_di_Jopengl_EGLDisplay Value) = 0 ;
	virtual _di_Jopengl_EGLSurface __cdecl _GetEGL_NO_SURFACE() = 0 ;
	virtual void __cdecl _SetEGL_NO_SURFACE(_di_Jopengl_EGLSurface Value) = 0 ;
	virtual int __cdecl _GetEGL_NO_TEXTURE() = 0 ;
	virtual int __cdecl _GetEGL_OPENGL_API() = 0 ;
	virtual int __cdecl _GetEGL_OPENGL_BIT() = 0 ;
	virtual int __cdecl _GetEGL_OPENGL_ES2_BIT() = 0 ;
	virtual int __cdecl _GetEGL_OPENGL_ES_API() = 0 ;
	virtual int __cdecl _GetEGL_OPENGL_ES_BIT() = 0 ;
	virtual int __cdecl _GetEGL_OPENVG_API() = 0 ;
	virtual int __cdecl _GetEGL_OPENVG_BIT() = 0 ;
	virtual int __cdecl _GetEGL_OPENVG_IMAGE() = 0 ;
	virtual int __cdecl _GetEGL_PBUFFER_BIT() = 0 ;
	virtual int __cdecl _GetEGL_PIXEL_ASPECT_RATIO() = 0 ;
	virtual int __cdecl _GetEGL_PIXMAP_BIT() = 0 ;
	virtual int __cdecl _GetEGL_READ() = 0 ;
	virtual int __cdecl _GetEGL_RED_SIZE() = 0 ;
	virtual int __cdecl _GetEGL_RENDERABLE_TYPE() = 0 ;
	virtual int __cdecl _GetEGL_RENDER_BUFFER() = 0 ;
	virtual int __cdecl _GetEGL_RGB_BUFFER() = 0 ;
	virtual int __cdecl _GetEGL_SAMPLES() = 0 ;
	virtual int __cdecl _GetEGL_SAMPLE_BUFFERS() = 0 ;
	virtual int __cdecl _GetEGL_SINGLE_BUFFER() = 0 ;
	virtual int __cdecl _GetEGL_SLOW_CONFIG() = 0 ;
	virtual int __cdecl _GetEGL_STENCIL_SIZE() = 0 ;
	virtual int __cdecl _GetEGL_SUCCESS() = 0 ;
	virtual int __cdecl _GetEGL_SURFACE_TYPE() = 0 ;
	virtual int __cdecl _GetEGL_SWAP_BEHAVIOR() = 0 ;
	virtual int __cdecl _GetEGL_SWAP_BEHAVIOR_PRESERVED_BIT() = 0 ;
	virtual int __cdecl _GetEGL_TEXTURE_2D() = 0 ;
	virtual int __cdecl _GetEGL_TEXTURE_FORMAT() = 0 ;
	virtual int __cdecl _GetEGL_TEXTURE_RGB() = 0 ;
	virtual int __cdecl _GetEGL_TEXTURE_RGBA() = 0 ;
	virtual int __cdecl _GetEGL_TEXTURE_TARGET() = 0 ;
	virtual int __cdecl _GetEGL_TRANSPARENT_BLUE_VALUE() = 0 ;
	virtual int __cdecl _GetEGL_TRANSPARENT_GREEN_VALUE() = 0 ;
	virtual int __cdecl _GetEGL_TRANSPARENT_RED_VALUE() = 0 ;
	virtual int __cdecl _GetEGL_TRANSPARENT_RGB() = 0 ;
	virtual int __cdecl _GetEGL_TRANSPARENT_TYPE() = 0 ;
	virtual int __cdecl _GetEGL_TRUE() = 0 ;
	virtual int __cdecl _GetEGL_VENDOR() = 0 ;
	virtual int __cdecl _GetEGL_VERSION() = 0 ;
	virtual int __cdecl _GetEGL_VERTICAL_RESOLUTION() = 0 ;
	virtual int __cdecl _GetEGL_VG_ALPHA_FORMAT() = 0 ;
	virtual int __cdecl _GetEGL_VG_ALPHA_FORMAT_NONPRE() = 0 ;
	virtual int __cdecl _GetEGL_VG_ALPHA_FORMAT_PRE() = 0 ;
	virtual int __cdecl _GetEGL_VG_ALPHA_FORMAT_PRE_BIT() = 0 ;
	virtual int __cdecl _GetEGL_VG_COLORSPACE() = 0 ;
	virtual int __cdecl _GetEGL_VG_COLORSPACE_LINEAR() = 0 ;
	virtual int __cdecl _GetEGL_VG_COLORSPACE_LINEAR_BIT() = 0 ;
	virtual int __cdecl _GetEGL_VG_COLORSPACE_sRGB() = 0 ;
	virtual int __cdecl _GetEGL_WIDTH() = 0 ;
	virtual int __cdecl _GetEGL_WINDOW_BIT() = 0 ;
	HIDESBASE virtual _di_JEGL14 __cdecl init() = 0 ;
	virtual bool __cdecl eglBindAPI(int api) = 0 ;
	virtual bool __cdecl eglBindTexImage(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLSurface surface, int buffer) = 0 ;
	virtual bool __cdecl eglChooseConfig(_di_Jopengl_EGLDisplay dpy, Androidapi::Jnibridge::TJavaArray__1<int>* attrib_list, int attrib_listOffset, Androidapi::Jnibridge::TJavaObjectArray__1<_di_Jopengl_EGLConfig>* configs, int configsOffset, int config_size, Androidapi::Jnibridge::TJavaArray__1<int>* num_config, int num_configOffset) = 0 ;
	virtual bool __cdecl eglCopyBuffers(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLSurface surface, int target) = 0 ;
	virtual _di_Jopengl_EGLContext __cdecl eglCreateContext(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLConfig config, _di_Jopengl_EGLContext share_context, Androidapi::Jnibridge::TJavaArray__1<int>* attrib_list, int offset) = 0 ;
	virtual _di_Jopengl_EGLSurface __cdecl eglCreatePbufferFromClientBuffer(_di_Jopengl_EGLDisplay dpy, int buftype, int buffer, _di_Jopengl_EGLConfig config, Androidapi::Jnibridge::TJavaArray__1<int>* attrib_list, int offset) = 0 ;
	virtual _di_Jopengl_EGLSurface __cdecl eglCreatePbufferSurface(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLConfig config, Androidapi::Jnibridge::TJavaArray__1<int>* attrib_list, int offset) = 0 ;
	virtual _di_Jopengl_EGLSurface __cdecl eglCreatePixmapSurface(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLConfig config, int pixmap, Androidapi::Jnibridge::TJavaArray__1<int>* attrib_list, int offset) = 0 ;
	virtual _di_Jopengl_EGLSurface __cdecl eglCreateWindowSurface(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLConfig config, Androidapi::Jni::Javatypes::_di_JObject win, Androidapi::Jnibridge::TJavaArray__1<int>* attrib_list, int offset) = 0 ;
	virtual bool __cdecl eglDestroyContext(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLContext ctx) = 0 ;
	virtual bool __cdecl eglDestroySurface(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLSurface surface) = 0 ;
	virtual bool __cdecl eglGetConfigAttrib(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLConfig config, int attribute, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 ;
	virtual bool __cdecl eglGetConfigs(_di_Jopengl_EGLDisplay dpy, Androidapi::Jnibridge::TJavaObjectArray__1<_di_Jopengl_EGLConfig>* configs, int configsOffset, int config_size, Androidapi::Jnibridge::TJavaArray__1<int>* num_config, int num_configOffset) = 0 ;
	virtual _di_Jopengl_EGLContext __cdecl eglGetCurrentContext() = 0 ;
	virtual _di_Jopengl_EGLDisplay __cdecl eglGetCurrentDisplay() = 0 ;
	virtual _di_Jopengl_EGLSurface __cdecl eglGetCurrentSurface(int readdraw) = 0 ;
	virtual _di_Jopengl_EGLDisplay __cdecl eglGetDisplay(int display_id) = 0 ;
	virtual int __cdecl eglGetError() = 0 ;
	virtual bool __cdecl eglInitialize(_di_Jopengl_EGLDisplay dpy, Androidapi::Jnibridge::TJavaArray__1<int>* major, int majorOffset, Androidapi::Jnibridge::TJavaArray__1<int>* minor, int minorOffset) = 0 ;
	virtual bool __cdecl eglMakeCurrent(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLSurface draw, _di_Jopengl_EGLSurface read, _di_Jopengl_EGLContext ctx) = 0 ;
	virtual int __cdecl eglQueryAPI() = 0 ;
	virtual bool __cdecl eglQueryContext(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLContext ctx, int attribute, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl eglQueryString(_di_Jopengl_EGLDisplay dpy, int name) = 0 ;
	virtual bool __cdecl eglQuerySurface(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLSurface surface, int attribute, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 ;
	virtual bool __cdecl eglReleaseTexImage(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLSurface surface, int buffer) = 0 ;
	virtual bool __cdecl eglReleaseThread() = 0 ;
	virtual bool __cdecl eglSurfaceAttrib(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLSurface surface, int attribute, int value) = 0 ;
	virtual bool __cdecl eglSwapBuffers(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLSurface surface) = 0 ;
	virtual bool __cdecl eglSwapInterval(_di_Jopengl_EGLDisplay dpy, int interval) = 0 ;
	virtual bool __cdecl eglTerminate(_di_Jopengl_EGLDisplay dpy) = 0 ;
	virtual bool __cdecl eglWaitClient() = 0 ;
	virtual bool __cdecl eglWaitGL() = 0 ;
	virtual bool __cdecl eglWaitNative(int engine) = 0 ;
	__property int EGL_ALPHA_MASK_SIZE = {read=_GetEGL_ALPHA_MASK_SIZE};
	__property int EGL_ALPHA_SIZE = {read=_GetEGL_ALPHA_SIZE};
	__property int EGL_BACK_BUFFER = {read=_GetEGL_BACK_BUFFER};
	__property int EGL_BAD_ACCESS = {read=_GetEGL_BAD_ACCESS};
	__property int EGL_BAD_ALLOC = {read=_GetEGL_BAD_ALLOC};
	__property int EGL_BAD_ATTRIBUTE = {read=_GetEGL_BAD_ATTRIBUTE};
	__property int EGL_BAD_CONFIG = {read=_GetEGL_BAD_CONFIG};
	__property int EGL_BAD_CONTEXT = {read=_GetEGL_BAD_CONTEXT};
	__property int EGL_BAD_CURRENT_SURFACE = {read=_GetEGL_BAD_CURRENT_SURFACE};
	__property int EGL_BAD_DISPLAY = {read=_GetEGL_BAD_DISPLAY};
	__property int EGL_BAD_MATCH = {read=_GetEGL_BAD_MATCH};
	__property int EGL_BAD_NATIVE_PIXMAP = {read=_GetEGL_BAD_NATIVE_PIXMAP};
	__property int EGL_BAD_NATIVE_WINDOW = {read=_GetEGL_BAD_NATIVE_WINDOW};
	__property int EGL_BAD_PARAMETER = {read=_GetEGL_BAD_PARAMETER};
	__property int EGL_BAD_SURFACE = {read=_GetEGL_BAD_SURFACE};
	__property int EGL_BIND_TO_TEXTURE_RGB = {read=_GetEGL_BIND_TO_TEXTURE_RGB};
	__property int EGL_BIND_TO_TEXTURE_RGBA = {read=_GetEGL_BIND_TO_TEXTURE_RGBA};
	__property int EGL_BLUE_SIZE = {read=_GetEGL_BLUE_SIZE};
	__property int EGL_BUFFER_DESTROYED = {read=_GetEGL_BUFFER_DESTROYED};
	__property int EGL_BUFFER_PRESERVED = {read=_GetEGL_BUFFER_PRESERVED};
	__property int EGL_BUFFER_SIZE = {read=_GetEGL_BUFFER_SIZE};
	__property int EGL_CLIENT_APIS = {read=_GetEGL_CLIENT_APIS};
	__property int EGL_COLOR_BUFFER_TYPE = {read=_GetEGL_COLOR_BUFFER_TYPE};
	__property int EGL_CONFIG_CAVEAT = {read=_GetEGL_CONFIG_CAVEAT};
	__property int EGL_CONFIG_ID = {read=_GetEGL_CONFIG_ID};
	__property int EGL_CONFORMANT = {read=_GetEGL_CONFORMANT};
	__property int EGL_CONTEXT_CLIENT_TYPE = {read=_GetEGL_CONTEXT_CLIENT_TYPE};
	__property int EGL_CONTEXT_CLIENT_VERSION = {read=_GetEGL_CONTEXT_CLIENT_VERSION};
	__property int EGL_CONTEXT_LOST = {read=_GetEGL_CONTEXT_LOST};
	__property int EGL_CORE_NATIVE_ENGINE = {read=_GetEGL_CORE_NATIVE_ENGINE};
	__property int EGL_DEFAULT_DISPLAY = {read=_GetEGL_DEFAULT_DISPLAY};
	__property int EGL_DEPTH_SIZE = {read=_GetEGL_DEPTH_SIZE};
	__property int EGL_DISPLAY_SCALING = {read=_GetEGL_DISPLAY_SCALING};
	__property int EGL_DRAW = {read=_GetEGL_DRAW};
	__property int EGL_EXTENSIONS = {read=_GetEGL_EXTENSIONS};
	__property int EGL_FALSE = {read=_GetEGL_FALSE};
	__property int EGL_GREEN_SIZE = {read=_GetEGL_GREEN_SIZE};
	__property int EGL_HEIGHT = {read=_GetEGL_HEIGHT};
	__property int EGL_HORIZONTAL_RESOLUTION = {read=_GetEGL_HORIZONTAL_RESOLUTION};
	__property int EGL_LARGEST_PBUFFER = {read=_GetEGL_LARGEST_PBUFFER};
	__property int EGL_LEVEL = {read=_GetEGL_LEVEL};
	__property int EGL_LUMINANCE_BUFFER = {read=_GetEGL_LUMINANCE_BUFFER};
	__property int EGL_LUMINANCE_SIZE = {read=_GetEGL_LUMINANCE_SIZE};
	__property int EGL_MATCH_NATIVE_PIXMAP = {read=_GetEGL_MATCH_NATIVE_PIXMAP};
	__property int EGL_MAX_PBUFFER_HEIGHT = {read=_GetEGL_MAX_PBUFFER_HEIGHT};
	__property int EGL_MAX_PBUFFER_PIXELS = {read=_GetEGL_MAX_PBUFFER_PIXELS};
	__property int EGL_MAX_PBUFFER_WIDTH = {read=_GetEGL_MAX_PBUFFER_WIDTH};
	__property int EGL_MAX_SWAP_INTERVAL = {read=_GetEGL_MAX_SWAP_INTERVAL};
	__property int EGL_MIN_SWAP_INTERVAL = {read=_GetEGL_MIN_SWAP_INTERVAL};
	__property int EGL_MIPMAP_LEVEL = {read=_GetEGL_MIPMAP_LEVEL};
	__property int EGL_MIPMAP_TEXTURE = {read=_GetEGL_MIPMAP_TEXTURE};
	__property int EGL_MULTISAMPLE_RESOLVE = {read=_GetEGL_MULTISAMPLE_RESOLVE};
	__property int EGL_MULTISAMPLE_RESOLVE_BOX = {read=_GetEGL_MULTISAMPLE_RESOLVE_BOX};
	__property int EGL_MULTISAMPLE_RESOLVE_BOX_BIT = {read=_GetEGL_MULTISAMPLE_RESOLVE_BOX_BIT};
	__property int EGL_MULTISAMPLE_RESOLVE_DEFAULT = {read=_GetEGL_MULTISAMPLE_RESOLVE_DEFAULT};
	__property int EGL_NATIVE_RENDERABLE = {read=_GetEGL_NATIVE_RENDERABLE};
	__property int EGL_NATIVE_VISUAL_ID = {read=_GetEGL_NATIVE_VISUAL_ID};
	__property int EGL_NATIVE_VISUAL_TYPE = {read=_GetEGL_NATIVE_VISUAL_TYPE};
	__property int EGL_NONE = {read=_GetEGL_NONE};
	__property int EGL_NON_CONFORMANT_CONFIG = {read=_GetEGL_NON_CONFORMANT_CONFIG};
	__property int EGL_NOT_INITIALIZED = {read=_GetEGL_NOT_INITIALIZED};
	__property _di_Jopengl_EGLContext EGL_NO_CONTEXT = {read=_GetEGL_NO_CONTEXT, write=_SetEGL_NO_CONTEXT};
	__property _di_Jopengl_EGLDisplay EGL_NO_DISPLAY = {read=_GetEGL_NO_DISPLAY, write=_SetEGL_NO_DISPLAY};
	__property _di_Jopengl_EGLSurface EGL_NO_SURFACE = {read=_GetEGL_NO_SURFACE, write=_SetEGL_NO_SURFACE};
	__property int EGL_NO_TEXTURE = {read=_GetEGL_NO_TEXTURE};
	__property int EGL_OPENGL_API = {read=_GetEGL_OPENGL_API};
	__property int EGL_OPENGL_BIT = {read=_GetEGL_OPENGL_BIT};
	__property int EGL_OPENGL_ES2_BIT = {read=_GetEGL_OPENGL_ES2_BIT};
	__property int EGL_OPENGL_ES_API = {read=_GetEGL_OPENGL_ES_API};
	__property int EGL_OPENGL_ES_BIT = {read=_GetEGL_OPENGL_ES_BIT};
	__property int EGL_OPENVG_API = {read=_GetEGL_OPENVG_API};
	__property int EGL_OPENVG_BIT = {read=_GetEGL_OPENVG_BIT};
	__property int EGL_OPENVG_IMAGE = {read=_GetEGL_OPENVG_IMAGE};
	__property int EGL_PBUFFER_BIT = {read=_GetEGL_PBUFFER_BIT};
	__property int EGL_PIXEL_ASPECT_RATIO = {read=_GetEGL_PIXEL_ASPECT_RATIO};
	__property int EGL_PIXMAP_BIT = {read=_GetEGL_PIXMAP_BIT};
	__property int EGL_READ = {read=_GetEGL_READ};
	__property int EGL_RED_SIZE = {read=_GetEGL_RED_SIZE};
	__property int EGL_RENDERABLE_TYPE = {read=_GetEGL_RENDERABLE_TYPE};
	__property int EGL_RENDER_BUFFER = {read=_GetEGL_RENDER_BUFFER};
	__property int EGL_RGB_BUFFER = {read=_GetEGL_RGB_BUFFER};
	__property int EGL_SAMPLES = {read=_GetEGL_SAMPLES};
	__property int EGL_SAMPLE_BUFFERS = {read=_GetEGL_SAMPLE_BUFFERS};
	__property int EGL_SINGLE_BUFFER = {read=_GetEGL_SINGLE_BUFFER};
	__property int EGL_SLOW_CONFIG = {read=_GetEGL_SLOW_CONFIG};
	__property int EGL_STENCIL_SIZE = {read=_GetEGL_STENCIL_SIZE};
	__property int EGL_SUCCESS = {read=_GetEGL_SUCCESS};
	__property int EGL_SURFACE_TYPE = {read=_GetEGL_SURFACE_TYPE};
	__property int EGL_SWAP_BEHAVIOR = {read=_GetEGL_SWAP_BEHAVIOR};
	__property int EGL_SWAP_BEHAVIOR_PRESERVED_BIT = {read=_GetEGL_SWAP_BEHAVIOR_PRESERVED_BIT};
	__property int EGL_TEXTURE_2D = {read=_GetEGL_TEXTURE_2D};
	__property int EGL_TEXTURE_FORMAT = {read=_GetEGL_TEXTURE_FORMAT};
	__property int EGL_TEXTURE_RGB = {read=_GetEGL_TEXTURE_RGB};
	__property int EGL_TEXTURE_RGBA = {read=_GetEGL_TEXTURE_RGBA};
	__property int EGL_TEXTURE_TARGET = {read=_GetEGL_TEXTURE_TARGET};
	__property int EGL_TRANSPARENT_BLUE_VALUE = {read=_GetEGL_TRANSPARENT_BLUE_VALUE};
	__property int EGL_TRANSPARENT_GREEN_VALUE = {read=_GetEGL_TRANSPARENT_GREEN_VALUE};
	__property int EGL_TRANSPARENT_RED_VALUE = {read=_GetEGL_TRANSPARENT_RED_VALUE};
	__property int EGL_TRANSPARENT_RGB = {read=_GetEGL_TRANSPARENT_RGB};
	__property int EGL_TRANSPARENT_TYPE = {read=_GetEGL_TRANSPARENT_TYPE};
	__property int EGL_TRUE = {read=_GetEGL_TRUE};
	__property int EGL_VENDOR = {read=_GetEGL_VENDOR};
	__property int EGL_VERSION = {read=_GetEGL_VERSION};
	__property int EGL_VERTICAL_RESOLUTION = {read=_GetEGL_VERTICAL_RESOLUTION};
	__property int EGL_VG_ALPHA_FORMAT = {read=_GetEGL_VG_ALPHA_FORMAT};
	__property int EGL_VG_ALPHA_FORMAT_NONPRE = {read=_GetEGL_VG_ALPHA_FORMAT_NONPRE};
	__property int EGL_VG_ALPHA_FORMAT_PRE = {read=_GetEGL_VG_ALPHA_FORMAT_PRE};
	__property int EGL_VG_ALPHA_FORMAT_PRE_BIT = {read=_GetEGL_VG_ALPHA_FORMAT_PRE_BIT};
	__property int EGL_VG_COLORSPACE = {read=_GetEGL_VG_COLORSPACE};
	__property int EGL_VG_COLORSPACE_LINEAR = {read=_GetEGL_VG_COLORSPACE_LINEAR};
	__property int EGL_VG_COLORSPACE_LINEAR_BIT = {read=_GetEGL_VG_COLORSPACE_LINEAR_BIT};
	__property int EGL_VG_COLORSPACE_sRGB = {read=_GetEGL_VG_COLORSPACE_sRGB};
	__property int EGL_WIDTH = {read=_GetEGL_WIDTH};
	__property int EGL_WINDOW_BIT = {read=_GetEGL_WINDOW_BIT};
};

__interface  INTERFACE_UUID("{3F6CFADC-F857-4996-886D-079C676135C7}") JEGL14  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJEGL14 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEGL14Class,_di_JEGL14>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEGL14Class,_di_JEGL14> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJEGL14() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEGL14Class,_di_JEGL14>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJEGL14() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FF7E34A3-9353-4DF9-9BD6-21DA955FB685}") JEGLObjectHandleClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DDBE4C0D-FAFA-4488-9AF0-A0DA2288D4EE}") JEGLObjectHandle  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl getHandle() = 0 ;
	virtual __int64 __cdecl getNativeHandle() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJEGLObjectHandle : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEGLObjectHandleClass,_di_JEGLObjectHandle>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEGLObjectHandleClass,_di_JEGLObjectHandle> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJEGLObjectHandle() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEGLObjectHandleClass,_di_JEGLObjectHandle>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJEGLObjectHandle() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3822999D-D9EE-4F0F-BBB3-C0B5081A54C3}") Jopengl_EGLConfigClass  : public JEGLObjectHandleClass 
{
	
};

__interface  INTERFACE_UUID("{B821AC66-FC87-4B82-9F10-A1021B85AE65}") Jopengl_EGLConfig  : public JEGLObjectHandle 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJopengl_EGLConfig : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLConfigClass,_di_Jopengl_EGLConfig>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLConfigClass,_di_Jopengl_EGLConfig> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJopengl_EGLConfig() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLConfigClass,_di_Jopengl_EGLConfig>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJopengl_EGLConfig() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E3975386-B545-40C7-A1E4-2C27B7E78418}") Jopengl_EGLContextClass  : public JEGLObjectHandleClass 
{
	
};

__interface  INTERFACE_UUID("{7878A9EA-E332-4F81-A941-38213B756F83}") Jopengl_EGLContext  : public JEGLObjectHandle 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJopengl_EGLContext : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLContextClass,_di_Jopengl_EGLContext>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLContextClass,_di_Jopengl_EGLContext> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJopengl_EGLContext() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLContextClass,_di_Jopengl_EGLContext>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJopengl_EGLContext() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{88F3BA54-B00D-48F7-AF12-A0CB468AC554}") Jopengl_EGLDisplayClass  : public JEGLObjectHandleClass 
{
	
};

__interface  INTERFACE_UUID("{04C41700-CE9C-472E-AD2B-F9BD85ED2F2F}") Jopengl_EGLDisplay  : public JEGLObjectHandle 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJopengl_EGLDisplay : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLDisplayClass,_di_Jopengl_EGLDisplay>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLDisplayClass,_di_Jopengl_EGLDisplay> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJopengl_EGLDisplay() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLDisplayClass,_di_Jopengl_EGLDisplay>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJopengl_EGLDisplay() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{80782380-A265-4609-BDD3-57760E211070}") JEGLExtClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetEGL_CONTEXT_FLAGS_KHR() = 0 ;
	virtual int __cdecl _GetEGL_CONTEXT_MAJOR_VERSION_KHR() = 0 ;
	virtual int __cdecl _GetEGL_CONTEXT_MINOR_VERSION_KHR() = 0 ;
	virtual int __cdecl _GetEGL_OPENGL_ES3_BIT_KHR() = 0 ;
	virtual int __cdecl _GetEGL_RECORDABLE_ANDROID() = 0 ;
	HIDESBASE virtual _di_JEGLExt __cdecl init() = 0 ;
	virtual bool __cdecl eglPresentationTimeANDROID(_di_Jopengl_EGLDisplay dpy, _di_Jopengl_EGLSurface sur, __int64 time) = 0 ;
	__property int EGL_CONTEXT_FLAGS_KHR = {read=_GetEGL_CONTEXT_FLAGS_KHR};
	__property int EGL_CONTEXT_MAJOR_VERSION_KHR = {read=_GetEGL_CONTEXT_MAJOR_VERSION_KHR};
	__property int EGL_CONTEXT_MINOR_VERSION_KHR = {read=_GetEGL_CONTEXT_MINOR_VERSION_KHR};
	__property int EGL_OPENGL_ES3_BIT_KHR = {read=_GetEGL_OPENGL_ES3_BIT_KHR};
	__property int EGL_RECORDABLE_ANDROID = {read=_GetEGL_RECORDABLE_ANDROID};
};

__interface  INTERFACE_UUID("{333656E1-045A-43F1-9025-B76EF3C144F4}") JEGLExt  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJEGLExt : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEGLExtClass,_di_JEGLExt>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEGLExtClass,_di_JEGLExt> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJEGLExt() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEGLExtClass,_di_JEGLExt>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJEGLExt() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{16333FF4-C63D-4F38-B92E-C0C7BAD97E25}") Jopengl_EGLSurfaceClass  : public JEGLObjectHandleClass 
{
	
};

__interface  INTERFACE_UUID("{14FEC125-04A4-4B09-8C09-6B352317AB30}") Jopengl_EGLSurface  : public JEGLObjectHandle 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJopengl_EGLSurface : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLSurfaceClass,_di_Jopengl_EGLSurface>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLSurfaceClass,_di_Jopengl_EGLSurface> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJopengl_EGLSurface() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_EGLSurfaceClass,_di_Jopengl_EGLSurface>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJopengl_EGLSurface() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{54BA31A1-A2A8-448C-96F9-9D95D460D0E9}") JETC1Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetDECODED_BLOCK_SIZE() = 0 ;
	virtual int __cdecl _GetENCODED_BLOCK_SIZE() = 0 ;
	virtual int __cdecl _GetETC1_RGB8_OES() = 0 ;
	virtual int __cdecl _GetETC_PKM_HEADER_SIZE() = 0 ;
	HIDESBASE virtual _di_JETC1 __cdecl init() = 0 ;
	virtual void __cdecl decodeBlock(Androidapi::Jni::Javatypes::_di_JBuffer in_, Androidapi::Jni::Javatypes::_di_JBuffer out_) = 0 ;
	virtual void __cdecl decodeImage(Androidapi::Jni::Javatypes::_di_JBuffer in_, Androidapi::Jni::Javatypes::_di_JBuffer out_, int width, int height, int pixelSize, int stride) = 0 ;
	virtual void __cdecl encodeBlock(Androidapi::Jni::Javatypes::_di_JBuffer in_, int validPixelMask, Androidapi::Jni::Javatypes::_di_JBuffer out_) = 0 ;
	virtual void __cdecl encodeImage(Androidapi::Jni::Javatypes::_di_JBuffer in_, int width, int height, int pixelSize, int stride, Androidapi::Jni::Javatypes::_di_JBuffer out_) = 0 ;
	virtual void __cdecl formatHeader(Androidapi::Jni::Javatypes::_di_JBuffer header, int width, int height) = 0 ;
	virtual int __cdecl getEncodedDataSize(int width, int height) = 0 ;
	virtual int __cdecl getHeight(Androidapi::Jni::Javatypes::_di_JBuffer header) = 0 ;
	virtual int __cdecl getWidth(Androidapi::Jni::Javatypes::_di_JBuffer header) = 0 ;
	virtual bool __cdecl isValid(Androidapi::Jni::Javatypes::_di_JBuffer header) = 0 ;
	__property int DECODED_BLOCK_SIZE = {read=_GetDECODED_BLOCK_SIZE};
	__property int ENCODED_BLOCK_SIZE = {read=_GetENCODED_BLOCK_SIZE};
	__property int ETC1_RGB8_OES = {read=_GetETC1_RGB8_OES};
	__property int ETC_PKM_HEADER_SIZE = {read=_GetETC_PKM_HEADER_SIZE};
};

__interface  INTERFACE_UUID("{412471CE-BF49-40AF-B106-E3DBB54F5811}") JETC1  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJETC1 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JETC1Class,_di_JETC1>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JETC1Class,_di_JETC1> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJETC1() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JETC1Class,_di_JETC1>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJETC1() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0D4A24DC-5C27-4C15-BD0E-1F58E876AFDE}") JETC1UtilClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JETC1Util __cdecl init() = 0 ;
	virtual _di_JETC1Util_ETC1Texture __cdecl compressTexture(Androidapi::Jni::Javatypes::_di_JBuffer input, int width, int height, int pixelSize, int stride) = 0 ;
	virtual _di_JETC1Util_ETC1Texture __cdecl createTexture(Androidapi::Jni::Javatypes::_di_JInputStream input) = 0 ;
	virtual bool __cdecl isETC1Supported() = 0 ;
	virtual void __cdecl loadTexture(int target, int level, int border, int fallbackFormat, int fallbackType, Androidapi::Jni::Javatypes::_di_JInputStream input) = 0 /* overload */;
	virtual void __cdecl loadTexture(int target, int level, int border, int fallbackFormat, int fallbackType, _di_JETC1Util_ETC1Texture texture) = 0 /* overload */;
	virtual void __cdecl writeTexture(_di_JETC1Util_ETC1Texture texture, Androidapi::Jni::Javatypes::_di_JOutputStream output) = 0 ;
};

__interface  INTERFACE_UUID("{EFB4D5C0-69BE-4ACE-949F-32EF40434DCE}") JETC1Util  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJETC1Util : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JETC1UtilClass,_di_JETC1Util>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JETC1UtilClass,_di_JETC1Util> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJETC1Util() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JETC1UtilClass,_di_JETC1Util>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJETC1Util() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4A43895C-EFD2-444A-8048-4F8DFF323CBD}") JETC1Util_ETC1TextureClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JETC1Util_ETC1Texture __cdecl init(int width, int height, Androidapi::Jni::Javatypes::_di_JByteBuffer data) = 0 ;
};

__interface  INTERFACE_UUID("{C53E11F2-9E67-4CC3-8D31-14F55D2E3A6F}") JETC1Util_ETC1Texture  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JByteBuffer __cdecl getData() = 0 ;
	virtual int __cdecl getHeight() = 0 ;
	virtual int __cdecl getWidth() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJETC1Util_ETC1Texture : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JETC1Util_ETC1TextureClass,_di_JETC1Util_ETC1Texture>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JETC1Util_ETC1TextureClass,_di_JETC1Util_ETC1Texture> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJETC1Util_ETC1Texture() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JETC1Util_ETC1TextureClass,_di_JETC1Util_ETC1Texture>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJETC1Util_ETC1Texture() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7E6A0223-471A-40A4-819C-F743E8C79B03}") JGLDebugHelperClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetCONFIG_CHECK_GL_ERROR() = 0 ;
	virtual int __cdecl _GetCONFIG_CHECK_THREAD() = 0 ;
	virtual int __cdecl _GetCONFIG_LOG_ARGUMENT_NAMES() = 0 ;
	virtual int __cdecl _GetERROR_WRONG_THREAD() = 0 ;
	HIDESBASE virtual _di_JGLDebugHelper __cdecl init() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JGL __cdecl wrap(Androidapi::Jni::Javatypes::_di_JGL gl, int configFlags, Androidapi::Jni::Javatypes::_di_JWriter log) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JEGL __cdecl wrap(Androidapi::Jni::Javatypes::_di_JEGL egl, int configFlags, Androidapi::Jni::Javatypes::_di_JWriter log) = 0 /* overload */;
	__property int CONFIG_CHECK_GL_ERROR = {read=_GetCONFIG_CHECK_GL_ERROR};
	__property int CONFIG_CHECK_THREAD = {read=_GetCONFIG_CHECK_THREAD};
	__property int CONFIG_LOG_ARGUMENT_NAMES = {read=_GetCONFIG_LOG_ARGUMENT_NAMES};
	__property int ERROR_WRONG_THREAD = {read=_GetERROR_WRONG_THREAD};
};

__interface  INTERFACE_UUID("{A639D925-310B-4DA9-AA69-984007F9B7CD}") JGLDebugHelper  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLDebugHelper : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLDebugHelperClass,_di_JGLDebugHelper>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLDebugHelperClass,_di_JGLDebugHelper> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLDebugHelper() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLDebugHelperClass,_di_JGLDebugHelper>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLDebugHelper() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{175246E8-7414-4AA7-932F-878CC6D920EE}") JGLES10Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetGL_ADD() = 0 ;
	virtual int __cdecl _GetGL_ALIASED_LINE_WIDTH_RANGE() = 0 ;
	virtual int __cdecl _GetGL_ALIASED_POINT_SIZE_RANGE() = 0 ;
	virtual int __cdecl _GetGL_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_ALPHA_BITS() = 0 ;
	virtual int __cdecl _GetGL_ALPHA_TEST() = 0 ;
	virtual int __cdecl _GetGL_ALWAYS() = 0 ;
	virtual int __cdecl _GetGL_AMBIENT() = 0 ;
	virtual int __cdecl _GetGL_AMBIENT_AND_DIFFUSE() = 0 ;
	virtual int __cdecl _GetGL_AND() = 0 ;
	virtual int __cdecl _GetGL_AND_INVERTED() = 0 ;
	virtual int __cdecl _GetGL_AND_REVERSE() = 0 ;
	virtual int __cdecl _GetGL_BACK() = 0 ;
	virtual int __cdecl _GetGL_BLEND() = 0 ;
	virtual int __cdecl _GetGL_BLUE_BITS() = 0 ;
	virtual int __cdecl _GetGL_BYTE() = 0 ;
	virtual int __cdecl _GetGL_CCW() = 0 ;
	virtual int __cdecl _GetGL_CLAMP_TO_EDGE() = 0 ;
	virtual int __cdecl _GetGL_CLEAR() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_COLOR_BUFFER_BIT() = 0 ;
	virtual int __cdecl _GetGL_COLOR_LOGIC_OP() = 0 ;
	virtual int __cdecl _GetGL_COLOR_MATERIAL() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_TEXTURE_FORMATS() = 0 ;
	virtual int __cdecl _GetGL_CONSTANT_ATTENUATION() = 0 ;
	virtual int __cdecl _GetGL_COPY() = 0 ;
	virtual int __cdecl _GetGL_COPY_INVERTED() = 0 ;
	virtual int __cdecl _GetGL_CULL_FACE() = 0 ;
	virtual int __cdecl _GetGL_CW() = 0 ;
	virtual int __cdecl _GetGL_DECAL() = 0 ;
	virtual int __cdecl _GetGL_DECR() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_BITS() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_BUFFER_BIT() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_TEST() = 0 ;
	virtual int __cdecl _GetGL_DIFFUSE() = 0 ;
	virtual int __cdecl _GetGL_DITHER() = 0 ;
	virtual int __cdecl _GetGL_DONT_CARE() = 0 ;
	virtual int __cdecl _GetGL_DST_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_DST_COLOR() = 0 ;
	virtual int __cdecl _GetGL_EMISSION() = 0 ;
	virtual int __cdecl _GetGL_EQUAL() = 0 ;
	virtual int __cdecl _GetGL_EQUIV() = 0 ;
	virtual int __cdecl _GetGL_EXP() = 0 ;
	virtual int __cdecl _GetGL_EXP2() = 0 ;
	virtual int __cdecl _GetGL_EXTENSIONS() = 0 ;
	virtual int __cdecl _GetGL_FALSE() = 0 ;
	virtual int __cdecl _GetGL_FASTEST() = 0 ;
	virtual int __cdecl _GetGL_FIXED() = 0 ;
	virtual int __cdecl _GetGL_FLAT() = 0 ;
	virtual int __cdecl _GetGL_FLOAT() = 0 ;
	virtual int __cdecl _GetGL_FOG() = 0 ;
	virtual int __cdecl _GetGL_FOG_COLOR() = 0 ;
	virtual int __cdecl _GetGL_FOG_DENSITY() = 0 ;
	virtual int __cdecl _GetGL_FOG_END() = 0 ;
	virtual int __cdecl _GetGL_FOG_HINT() = 0 ;
	virtual int __cdecl _GetGL_FOG_MODE() = 0 ;
	virtual int __cdecl _GetGL_FOG_START() = 0 ;
	virtual int __cdecl _GetGL_FRONT() = 0 ;
	virtual int __cdecl _GetGL_FRONT_AND_BACK() = 0 ;
	virtual int __cdecl _GetGL_GEQUAL() = 0 ;
	virtual int __cdecl _GetGL_GREATER() = 0 ;
	virtual int __cdecl _GetGL_GREEN_BITS() = 0 ;
	virtual int __cdecl _GetGL_IMPLEMENTATION_COLOR_READ_FORMAT_OES() = 0 ;
	virtual int __cdecl _GetGL_IMPLEMENTATION_COLOR_READ_TYPE_OES() = 0 ;
	virtual int __cdecl _GetGL_INCR() = 0 ;
	virtual int __cdecl _GetGL_INVALID_ENUM() = 0 ;
	virtual int __cdecl _GetGL_INVALID_OPERATION() = 0 ;
	virtual int __cdecl _GetGL_INVALID_VALUE() = 0 ;
	virtual int __cdecl _GetGL_INVERT() = 0 ;
	virtual int __cdecl _GetGL_KEEP() = 0 ;
	virtual int __cdecl _GetGL_LEQUAL() = 0 ;
	virtual int __cdecl _GetGL_LESS() = 0 ;
	virtual int __cdecl _GetGL_LIGHT0() = 0 ;
	virtual int __cdecl _GetGL_LIGHT1() = 0 ;
	virtual int __cdecl _GetGL_LIGHT2() = 0 ;
	virtual int __cdecl _GetGL_LIGHT3() = 0 ;
	virtual int __cdecl _GetGL_LIGHT4() = 0 ;
	virtual int __cdecl _GetGL_LIGHT5() = 0 ;
	virtual int __cdecl _GetGL_LIGHT6() = 0 ;
	virtual int __cdecl _GetGL_LIGHT7() = 0 ;
	virtual int __cdecl _GetGL_LIGHTING() = 0 ;
	virtual int __cdecl _GetGL_LIGHT_MODEL_AMBIENT() = 0 ;
	virtual int __cdecl _GetGL_LIGHT_MODEL_TWO_SIDE() = 0 ;
	virtual int __cdecl _GetGL_LINEAR() = 0 ;
	virtual int __cdecl _GetGL_LINEAR_ATTENUATION() = 0 ;
	virtual int __cdecl _GetGL_LINEAR_MIPMAP_LINEAR() = 0 ;
	virtual int __cdecl _GetGL_LINEAR_MIPMAP_NEAREST() = 0 ;
	virtual int __cdecl _GetGL_LINES() = 0 ;
	virtual int __cdecl _GetGL_LINE_LOOP() = 0 ;
	virtual int __cdecl _GetGL_LINE_SMOOTH() = 0 ;
	virtual int __cdecl _GetGL_LINE_SMOOTH_HINT() = 0 ;
	virtual int __cdecl _GetGL_LINE_STRIP() = 0 ;
	virtual int __cdecl _GetGL_LUMINANCE() = 0 ;
	virtual int __cdecl _GetGL_LUMINANCE_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_MAX_ELEMENTS_INDICES() = 0 ;
	virtual int __cdecl _GetGL_MAX_ELEMENTS_VERTICES() = 0 ;
	virtual int __cdecl _GetGL_MAX_LIGHTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_MODELVIEW_STACK_DEPTH() = 0 ;
	virtual int __cdecl _GetGL_MAX_PROJECTION_STACK_DEPTH() = 0 ;
	virtual int __cdecl _GetGL_MAX_TEXTURE_SIZE() = 0 ;
	virtual int __cdecl _GetGL_MAX_TEXTURE_STACK_DEPTH() = 0 ;
	virtual int __cdecl _GetGL_MAX_TEXTURE_UNITS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VIEWPORT_DIMS() = 0 ;
	virtual int __cdecl _GetGL_MODELVIEW() = 0 ;
	virtual int __cdecl _GetGL_MODULATE() = 0 ;
	virtual int __cdecl _GetGL_MULTISAMPLE() = 0 ;
	virtual int __cdecl _GetGL_NAND() = 0 ;
	virtual int __cdecl _GetGL_NEAREST() = 0 ;
	virtual int __cdecl _GetGL_NEAREST_MIPMAP_LINEAR() = 0 ;
	virtual int __cdecl _GetGL_NEAREST_MIPMAP_NEAREST() = 0 ;
	virtual int __cdecl _GetGL_NEVER() = 0 ;
	virtual int __cdecl _GetGL_NICEST() = 0 ;
	virtual int __cdecl _GetGL_NOOP() = 0 ;
	virtual int __cdecl _GetGL_NOR() = 0 ;
	virtual int __cdecl _GetGL_NORMALIZE() = 0 ;
	virtual int __cdecl _GetGL_NORMAL_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_NOTEQUAL() = 0 ;
	virtual int __cdecl _GetGL_NO_ERROR() = 0 ;
	virtual int __cdecl _GetGL_NUM_COMPRESSED_TEXTURE_FORMATS() = 0 ;
	virtual int __cdecl _GetGL_ONE() = 0 ;
	virtual int __cdecl _GetGL_ONE_MINUS_DST_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_ONE_MINUS_DST_COLOR() = 0 ;
	virtual int __cdecl _GetGL_ONE_MINUS_SRC_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_ONE_MINUS_SRC_COLOR() = 0 ;
	virtual int __cdecl _GetGL_OR() = 0 ;
	virtual int __cdecl _GetGL_OR_INVERTED() = 0 ;
	virtual int __cdecl _GetGL_OR_REVERSE() = 0 ;
	virtual int __cdecl _GetGL_OUT_OF_MEMORY() = 0 ;
	virtual int __cdecl _GetGL_PACK_ALIGNMENT() = 0 ;
	virtual int __cdecl _GetGL_PALETTE4_R5_G6_B5_OES() = 0 ;
	virtual int __cdecl _GetGL_PALETTE4_RGB5_A1_OES() = 0 ;
	virtual int __cdecl _GetGL_PALETTE4_RGB8_OES() = 0 ;
	virtual int __cdecl _GetGL_PALETTE4_RGBA4_OES() = 0 ;
	virtual int __cdecl _GetGL_PALETTE4_RGBA8_OES() = 0 ;
	virtual int __cdecl _GetGL_PALETTE8_R5_G6_B5_OES() = 0 ;
	virtual int __cdecl _GetGL_PALETTE8_RGB5_A1_OES() = 0 ;
	virtual int __cdecl _GetGL_PALETTE8_RGB8_OES() = 0 ;
	virtual int __cdecl _GetGL_PALETTE8_RGBA4_OES() = 0 ;
	virtual int __cdecl _GetGL_PALETTE8_RGBA8_OES() = 0 ;
	virtual int __cdecl _GetGL_PERSPECTIVE_CORRECTION_HINT() = 0 ;
	virtual int __cdecl _GetGL_POINTS() = 0 ;
	virtual int __cdecl _GetGL_POINT_FADE_THRESHOLD_SIZE() = 0 ;
	virtual int __cdecl _GetGL_POINT_SIZE() = 0 ;
	virtual int __cdecl _GetGL_POINT_SMOOTH() = 0 ;
	virtual int __cdecl _GetGL_POINT_SMOOTH_HINT() = 0 ;
	virtual int __cdecl _GetGL_POLYGON_OFFSET_FILL() = 0 ;
	virtual int __cdecl _GetGL_POLYGON_SMOOTH_HINT() = 0 ;
	virtual int __cdecl _GetGL_POSITION() = 0 ;
	virtual int __cdecl _GetGL_PROJECTION() = 0 ;
	virtual int __cdecl _GetGL_QUADRATIC_ATTENUATION() = 0 ;
	virtual int __cdecl _GetGL_RED_BITS() = 0 ;
	virtual int __cdecl _GetGL_RENDERER() = 0 ;
	virtual int __cdecl _GetGL_REPEAT() = 0 ;
	virtual int __cdecl _GetGL_REPLACE() = 0 ;
	virtual int __cdecl _GetGL_RESCALE_NORMAL() = 0 ;
	virtual int __cdecl _GetGL_RGB() = 0 ;
	virtual int __cdecl _GetGL_RGBA() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_ALPHA_TO_COVERAGE() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_ALPHA_TO_ONE() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_COVERAGE() = 0 ;
	virtual int __cdecl _GetGL_SCISSOR_TEST() = 0 ;
	virtual int __cdecl _GetGL_SET() = 0 ;
	virtual int __cdecl _GetGL_SHININESS() = 0 ;
	virtual int __cdecl _GetGL_SHORT() = 0 ;
	virtual int __cdecl _GetGL_SMOOTH() = 0 ;
	virtual int __cdecl _GetGL_SMOOTH_LINE_WIDTH_RANGE() = 0 ;
	virtual int __cdecl _GetGL_SMOOTH_POINT_SIZE_RANGE() = 0 ;
	virtual int __cdecl _GetGL_SPECULAR() = 0 ;
	virtual int __cdecl _GetGL_SPOT_CUTOFF() = 0 ;
	virtual int __cdecl _GetGL_SPOT_DIRECTION() = 0 ;
	virtual int __cdecl _GetGL_SPOT_EXPONENT() = 0 ;
	virtual int __cdecl _GetGL_SRC_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_SRC_ALPHA_SATURATE() = 0 ;
	virtual int __cdecl _GetGL_SRC_COLOR() = 0 ;
	virtual int __cdecl _GetGL_STACK_OVERFLOW() = 0 ;
	virtual int __cdecl _GetGL_STACK_UNDERFLOW() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_BITS() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_BUFFER_BIT() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_TEST() = 0 ;
	virtual int __cdecl _GetGL_SUBPIXEL_BITS() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE0() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE1() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE10() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE11() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE12() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE13() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE14() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE15() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE16() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE17() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE18() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE19() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE2() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE20() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE21() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE22() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE23() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE24() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE25() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE26() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE27() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE28() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE29() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE3() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE30() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE31() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE4() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE5() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE6() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE7() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE8() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE9() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_2D() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_COORD_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_ENV() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_ENV_COLOR() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_ENV_MODE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_MAG_FILTER() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_MIN_FILTER() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_WRAP_S() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_WRAP_T() = 0 ;
	virtual int __cdecl _GetGL_TRIANGLES() = 0 ;
	virtual int __cdecl _GetGL_TRIANGLE_FAN() = 0 ;
	virtual int __cdecl _GetGL_TRIANGLE_STRIP() = 0 ;
	virtual int __cdecl _GetGL_TRUE() = 0 ;
	virtual int __cdecl _GetGL_UNPACK_ALIGNMENT() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_BYTE() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_SHORT() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_SHORT_4_4_4_4() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_SHORT_5_5_5_1() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_SHORT_5_6_5() = 0 ;
	virtual int __cdecl _GetGL_VENDOR() = 0 ;
	virtual int __cdecl _GetGL_VERSION() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_XOR() = 0 ;
	virtual int __cdecl _GetGL_ZERO() = 0 ;
	HIDESBASE virtual _di_JGLES10 __cdecl init() = 0 ;
	virtual void __cdecl glActiveTexture(int texture) = 0 ;
	virtual void __cdecl glAlphaFunc(int func, float ref) = 0 ;
	virtual void __cdecl glAlphaFuncx(int func, int ref) = 0 ;
	virtual void __cdecl glBindTexture(int target, int texture) = 0 ;
	virtual void __cdecl glBlendFunc(int sfactor, int dfactor) = 0 ;
	virtual void __cdecl glClear(int mask) = 0 ;
	virtual void __cdecl glClearColor(float red, float green, float blue, float alpha) = 0 ;
	virtual void __cdecl glClearColorx(int red, int green, int blue, int alpha) = 0 ;
	virtual void __cdecl glClearDepthf(float depth) = 0 ;
	virtual void __cdecl glClearDepthx(int depth) = 0 ;
	virtual void __cdecl glClearStencil(int s) = 0 ;
	virtual void __cdecl glClientActiveTexture(int texture) = 0 ;
	virtual void __cdecl glColor4f(float red, float green, float blue, float alpha) = 0 ;
	virtual void __cdecl glColor4x(int red, int green, int blue, int alpha) = 0 ;
	virtual void __cdecl glColorMask(bool red, bool green, bool blue, bool alpha) = 0 ;
	virtual void __cdecl glColorPointer(int size, int type_, int stride, Androidapi::Jni::Javatypes::_di_JBuffer pointer) = 0 ;
	virtual void __cdecl glCompressedTexImage2D(int target, int level, int internalformat, int width, int height, int border, int imageSize, Androidapi::Jni::Javatypes::_di_JBuffer data) = 0 ;
	virtual void __cdecl glCompressedTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, Androidapi::Jni::Javatypes::_di_JBuffer data) = 0 ;
	virtual void __cdecl glCopyTexImage2D(int target, int level, int internalformat, int x, int y, int width, int height, int border) = 0 ;
	virtual void __cdecl glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) = 0 ;
	virtual void __cdecl glCullFace(int mode) = 0 ;
	virtual void __cdecl glDeleteTextures(int n, Androidapi::Jnibridge::TJavaArray__1<int>* textures, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteTextures(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer textures) = 0 /* overload */;
	virtual void __cdecl glDepthFunc(int func) = 0 ;
	virtual void __cdecl glDepthMask(bool flag) = 0 ;
	virtual void __cdecl glDepthRangef(float zNear, float zFar) = 0 ;
	virtual void __cdecl glDepthRangex(int zNear, int zFar) = 0 ;
	virtual void __cdecl glDisable(int cap) = 0 ;
	virtual void __cdecl glDisableClientState(int array_) = 0 ;
	virtual void __cdecl glDrawArrays(int mode, int first, int count) = 0 ;
	virtual void __cdecl glDrawElements(int mode, int count, int type_, Androidapi::Jni::Javatypes::_di_JBuffer indices) = 0 ;
	virtual void __cdecl glEnable(int cap) = 0 ;
	virtual void __cdecl glEnableClientState(int array_) = 0 ;
	virtual void __cdecl glFinish() = 0 ;
	virtual void __cdecl glFlush() = 0 ;
	virtual void __cdecl glFogf(int pname, float param) = 0 ;
	virtual void __cdecl glFogfv(int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glFogfv(int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glFogx(int pname, int param) = 0 ;
	virtual void __cdecl glFogxv(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glFogxv(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glFrontFace(int mode) = 0 ;
	virtual void __cdecl glFrustumf(float left, float right, float bottom, float top, float zNear, float zFar) = 0 ;
	virtual void __cdecl glFrustumx(int left, int right, int bottom, int top, int zNear, int zFar) = 0 ;
	virtual void __cdecl glGenTextures(int n, Androidapi::Jnibridge::TJavaArray__1<int>* textures, int offset) = 0 /* overload */;
	virtual void __cdecl glGenTextures(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer textures) = 0 /* overload */;
	virtual int __cdecl glGetError() = 0 ;
	virtual void __cdecl glGetIntegerv(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetIntegerv(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetString(int name) = 0 ;
	virtual void __cdecl glHint(int target, int mode) = 0 ;
	virtual void __cdecl glLightModelf(int pname, float param) = 0 ;
	virtual void __cdecl glLightModelfv(int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glLightModelfv(int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glLightModelx(int pname, int param) = 0 ;
	virtual void __cdecl glLightModelxv(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glLightModelxv(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glLightf(int light, int pname, float param) = 0 ;
	virtual void __cdecl glLightfv(int light, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glLightfv(int light, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glLightx(int light, int pname, int param) = 0 ;
	virtual void __cdecl glLightxv(int light, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glLightxv(int light, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glLineWidth(float width) = 0 ;
	virtual void __cdecl glLineWidthx(int width) = 0 ;
	virtual void __cdecl glLoadIdentity() = 0 ;
	virtual void __cdecl glLoadMatrixf(Androidapi::Jnibridge::TJavaArray__1<float>* m, int offset) = 0 /* overload */;
	virtual void __cdecl glLoadMatrixf(Androidapi::Jni::Javatypes::_di_JFloatBuffer m) = 0 /* overload */;
	virtual void __cdecl glLoadMatrixx(Androidapi::Jnibridge::TJavaArray__1<int>* m, int offset) = 0 /* overload */;
	virtual void __cdecl glLoadMatrixx(Androidapi::Jni::Javatypes::_di_JIntBuffer m) = 0 /* overload */;
	virtual void __cdecl glLogicOp(int opcode) = 0 ;
	virtual void __cdecl glMaterialf(int face, int pname, float param) = 0 ;
	virtual void __cdecl glMaterialfv(int face, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glMaterialfv(int face, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glMaterialx(int face, int pname, int param) = 0 ;
	virtual void __cdecl glMaterialxv(int face, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glMaterialxv(int face, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glMatrixMode(int mode) = 0 ;
	virtual void __cdecl glMultMatrixf(Androidapi::Jnibridge::TJavaArray__1<float>* m, int offset) = 0 /* overload */;
	virtual void __cdecl glMultMatrixf(Androidapi::Jni::Javatypes::_di_JFloatBuffer m) = 0 /* overload */;
	virtual void __cdecl glMultMatrixx(Androidapi::Jnibridge::TJavaArray__1<int>* m, int offset) = 0 /* overload */;
	virtual void __cdecl glMultMatrixx(Androidapi::Jni::Javatypes::_di_JIntBuffer m) = 0 /* overload */;
	virtual void __cdecl glMultiTexCoord4f(int target, float s, float t, float r, float q) = 0 ;
	virtual void __cdecl glMultiTexCoord4x(int target, int s, int t, int r, int q) = 0 ;
	virtual void __cdecl glNormal3f(float nx, float ny, float nz) = 0 ;
	virtual void __cdecl glNormal3x(int nx, int ny, int nz) = 0 ;
	virtual void __cdecl glNormalPointer(int type_, int stride, Androidapi::Jni::Javatypes::_di_JBuffer pointer) = 0 ;
	virtual void __cdecl glOrthof(float left, float right, float bottom, float top, float zNear, float zFar) = 0 ;
	virtual void __cdecl glOrthox(int left, int right, int bottom, int top, int zNear, int zFar) = 0 ;
	virtual void __cdecl glPixelStorei(int pname, int param) = 0 ;
	virtual void __cdecl glPointSize(float size) = 0 ;
	virtual void __cdecl glPointSizex(int size) = 0 ;
	virtual void __cdecl glPolygonOffset(float factor, float units) = 0 ;
	virtual void __cdecl glPolygonOffsetx(int factor, int units) = 0 ;
	virtual void __cdecl glPopMatrix() = 0 ;
	virtual void __cdecl glPushMatrix() = 0 ;
	virtual void __cdecl glReadPixels(int x, int y, int width, int height, int format, int type_, Androidapi::Jni::Javatypes::_di_JBuffer pixels) = 0 ;
	virtual void __cdecl glRotatef(float angle, float x, float y, float z) = 0 ;
	virtual void __cdecl glRotatex(int angle, int x, int y, int z) = 0 ;
	virtual void __cdecl glSampleCoverage(float value, bool invert) = 0 ;
	virtual void __cdecl glSampleCoveragex(int value, bool invert) = 0 ;
	virtual void __cdecl glScalef(float x, float y, float z) = 0 ;
	virtual void __cdecl glScalex(int x, int y, int z) = 0 ;
	virtual void __cdecl glScissor(int x, int y, int width, int height) = 0 ;
	virtual void __cdecl glShadeModel(int mode) = 0 ;
	virtual void __cdecl glStencilFunc(int func, int ref, int mask) = 0 ;
	virtual void __cdecl glStencilMask(int mask) = 0 ;
	virtual void __cdecl glStencilOp(int fail, int zfail, int zpass) = 0 ;
	virtual void __cdecl glTexCoordPointer(int size, int type_, int stride, Androidapi::Jni::Javatypes::_di_JBuffer pointer) = 0 ;
	virtual void __cdecl glTexEnvf(int target, int pname, float param) = 0 ;
	virtual void __cdecl glTexEnvfv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexEnvfv(int target, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexEnvx(int target, int pname, int param) = 0 ;
	virtual void __cdecl glTexEnvxv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexEnvxv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type_, Androidapi::Jni::Javatypes::_di_JBuffer pixels) = 0 ;
	virtual void __cdecl glTexParameterf(int target, int pname, float param) = 0 ;
	virtual void __cdecl glTexParameterx(int target, int pname, int param) = 0 ;
	virtual void __cdecl glTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int type_, Androidapi::Jni::Javatypes::_di_JBuffer pixels) = 0 ;
	virtual void __cdecl glTranslatef(float x, float y, float z) = 0 ;
	virtual void __cdecl glTranslatex(int x, int y, int z) = 0 ;
	virtual void __cdecl glVertexPointer(int size, int type_, int stride, Androidapi::Jni::Javatypes::_di_JBuffer pointer) = 0 ;
	virtual void __cdecl glViewport(int x, int y, int width, int height) = 0 ;
	__property int GL_ADD = {read=_GetGL_ADD};
	__property int GL_ALIASED_LINE_WIDTH_RANGE = {read=_GetGL_ALIASED_LINE_WIDTH_RANGE};
	__property int GL_ALIASED_POINT_SIZE_RANGE = {read=_GetGL_ALIASED_POINT_SIZE_RANGE};
	__property int GL_ALPHA = {read=_GetGL_ALPHA};
	__property int GL_ALPHA_BITS = {read=_GetGL_ALPHA_BITS};
	__property int GL_ALPHA_TEST = {read=_GetGL_ALPHA_TEST};
	__property int GL_ALWAYS = {read=_GetGL_ALWAYS};
	__property int GL_AMBIENT = {read=_GetGL_AMBIENT};
	__property int GL_AMBIENT_AND_DIFFUSE = {read=_GetGL_AMBIENT_AND_DIFFUSE};
	__property int GL_AND = {read=_GetGL_AND};
	__property int GL_AND_INVERTED = {read=_GetGL_AND_INVERTED};
	__property int GL_AND_REVERSE = {read=_GetGL_AND_REVERSE};
	__property int GL_BACK = {read=_GetGL_BACK};
	__property int GL_BLEND = {read=_GetGL_BLEND};
	__property int GL_BLUE_BITS = {read=_GetGL_BLUE_BITS};
	__property int GL_BYTE = {read=_GetGL_BYTE};
	__property int GL_CCW = {read=_GetGL_CCW};
	__property int GL_CLAMP_TO_EDGE = {read=_GetGL_CLAMP_TO_EDGE};
	__property int GL_CLEAR = {read=_GetGL_CLEAR};
	__property int GL_COLOR_ARRAY = {read=_GetGL_COLOR_ARRAY};
	__property int GL_COLOR_BUFFER_BIT = {read=_GetGL_COLOR_BUFFER_BIT};
	__property int GL_COLOR_LOGIC_OP = {read=_GetGL_COLOR_LOGIC_OP};
	__property int GL_COLOR_MATERIAL = {read=_GetGL_COLOR_MATERIAL};
	__property int GL_COMPRESSED_TEXTURE_FORMATS = {read=_GetGL_COMPRESSED_TEXTURE_FORMATS};
	__property int GL_CONSTANT_ATTENUATION = {read=_GetGL_CONSTANT_ATTENUATION};
	__property int GL_COPY = {read=_GetGL_COPY};
	__property int GL_COPY_INVERTED = {read=_GetGL_COPY_INVERTED};
	__property int GL_CULL_FACE = {read=_GetGL_CULL_FACE};
	__property int GL_CW = {read=_GetGL_CW};
	__property int GL_DECAL = {read=_GetGL_DECAL};
	__property int GL_DECR = {read=_GetGL_DECR};
	__property int GL_DEPTH_BITS = {read=_GetGL_DEPTH_BITS};
	__property int GL_DEPTH_BUFFER_BIT = {read=_GetGL_DEPTH_BUFFER_BIT};
	__property int GL_DEPTH_TEST = {read=_GetGL_DEPTH_TEST};
	__property int GL_DIFFUSE = {read=_GetGL_DIFFUSE};
	__property int GL_DITHER = {read=_GetGL_DITHER};
	__property int GL_DONT_CARE = {read=_GetGL_DONT_CARE};
	__property int GL_DST_ALPHA = {read=_GetGL_DST_ALPHA};
	__property int GL_DST_COLOR = {read=_GetGL_DST_COLOR};
	__property int GL_EMISSION = {read=_GetGL_EMISSION};
	__property int GL_EQUAL = {read=_GetGL_EQUAL};
	__property int GL_EQUIV = {read=_GetGL_EQUIV};
	__property int GL_EXP = {read=_GetGL_EXP};
	__property int GL_EXP2 = {read=_GetGL_EXP2};
	__property int GL_EXTENSIONS = {read=_GetGL_EXTENSIONS};
	__property int GL_FALSE = {read=_GetGL_FALSE};
	__property int GL_FASTEST = {read=_GetGL_FASTEST};
	__property int GL_FIXED = {read=_GetGL_FIXED};
	__property int GL_FLAT = {read=_GetGL_FLAT};
	__property int GL_FLOAT = {read=_GetGL_FLOAT};
	__property int GL_FOG = {read=_GetGL_FOG};
	__property int GL_FOG_COLOR = {read=_GetGL_FOG_COLOR};
	__property int GL_FOG_DENSITY = {read=_GetGL_FOG_DENSITY};
	__property int GL_FOG_END = {read=_GetGL_FOG_END};
	__property int GL_FOG_HINT = {read=_GetGL_FOG_HINT};
	__property int GL_FOG_MODE = {read=_GetGL_FOG_MODE};
	__property int GL_FOG_START = {read=_GetGL_FOG_START};
	__property int GL_FRONT = {read=_GetGL_FRONT};
	__property int GL_FRONT_AND_BACK = {read=_GetGL_FRONT_AND_BACK};
	__property int GL_GEQUAL = {read=_GetGL_GEQUAL};
	__property int GL_GREATER = {read=_GetGL_GREATER};
	__property int GL_GREEN_BITS = {read=_GetGL_GREEN_BITS};
	__property int GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES = {read=_GetGL_IMPLEMENTATION_COLOR_READ_FORMAT_OES};
	__property int GL_IMPLEMENTATION_COLOR_READ_TYPE_OES = {read=_GetGL_IMPLEMENTATION_COLOR_READ_TYPE_OES};
	__property int GL_INCR = {read=_GetGL_INCR};
	__property int GL_INVALID_ENUM = {read=_GetGL_INVALID_ENUM};
	__property int GL_INVALID_OPERATION = {read=_GetGL_INVALID_OPERATION};
	__property int GL_INVALID_VALUE = {read=_GetGL_INVALID_VALUE};
	__property int GL_INVERT = {read=_GetGL_INVERT};
	__property int GL_KEEP = {read=_GetGL_KEEP};
	__property int GL_LEQUAL = {read=_GetGL_LEQUAL};
	__property int GL_LESS = {read=_GetGL_LESS};
	__property int GL_LIGHT0 = {read=_GetGL_LIGHT0};
	__property int GL_LIGHT1 = {read=_GetGL_LIGHT1};
	__property int GL_LIGHT2 = {read=_GetGL_LIGHT2};
	__property int GL_LIGHT3 = {read=_GetGL_LIGHT3};
	__property int GL_LIGHT4 = {read=_GetGL_LIGHT4};
	__property int GL_LIGHT5 = {read=_GetGL_LIGHT5};
	__property int GL_LIGHT6 = {read=_GetGL_LIGHT6};
	__property int GL_LIGHT7 = {read=_GetGL_LIGHT7};
	__property int GL_LIGHTING = {read=_GetGL_LIGHTING};
	__property int GL_LIGHT_MODEL_AMBIENT = {read=_GetGL_LIGHT_MODEL_AMBIENT};
	__property int GL_LIGHT_MODEL_TWO_SIDE = {read=_GetGL_LIGHT_MODEL_TWO_SIDE};
	__property int GL_LINEAR = {read=_GetGL_LINEAR};
	__property int GL_LINEAR_ATTENUATION = {read=_GetGL_LINEAR_ATTENUATION};
	__property int GL_LINEAR_MIPMAP_LINEAR = {read=_GetGL_LINEAR_MIPMAP_LINEAR};
	__property int GL_LINEAR_MIPMAP_NEAREST = {read=_GetGL_LINEAR_MIPMAP_NEAREST};
	__property int GL_LINES = {read=_GetGL_LINES};
	__property int GL_LINE_LOOP = {read=_GetGL_LINE_LOOP};
	__property int GL_LINE_SMOOTH = {read=_GetGL_LINE_SMOOTH};
	__property int GL_LINE_SMOOTH_HINT = {read=_GetGL_LINE_SMOOTH_HINT};
	__property int GL_LINE_STRIP = {read=_GetGL_LINE_STRIP};
	__property int GL_LUMINANCE = {read=_GetGL_LUMINANCE};
	__property int GL_LUMINANCE_ALPHA = {read=_GetGL_LUMINANCE_ALPHA};
	__property int GL_MAX_ELEMENTS_INDICES = {read=_GetGL_MAX_ELEMENTS_INDICES};
	__property int GL_MAX_ELEMENTS_VERTICES = {read=_GetGL_MAX_ELEMENTS_VERTICES};
	__property int GL_MAX_LIGHTS = {read=_GetGL_MAX_LIGHTS};
	__property int GL_MAX_MODELVIEW_STACK_DEPTH = {read=_GetGL_MAX_MODELVIEW_STACK_DEPTH};
	__property int GL_MAX_PROJECTION_STACK_DEPTH = {read=_GetGL_MAX_PROJECTION_STACK_DEPTH};
	__property int GL_MAX_TEXTURE_SIZE = {read=_GetGL_MAX_TEXTURE_SIZE};
	__property int GL_MAX_TEXTURE_STACK_DEPTH = {read=_GetGL_MAX_TEXTURE_STACK_DEPTH};
	__property int GL_MAX_TEXTURE_UNITS = {read=_GetGL_MAX_TEXTURE_UNITS};
	__property int GL_MAX_VIEWPORT_DIMS = {read=_GetGL_MAX_VIEWPORT_DIMS};
	__property int GL_MODELVIEW = {read=_GetGL_MODELVIEW};
	__property int GL_MODULATE = {read=_GetGL_MODULATE};
	__property int GL_MULTISAMPLE = {read=_GetGL_MULTISAMPLE};
	__property int GL_NAND = {read=_GetGL_NAND};
	__property int GL_NEAREST = {read=_GetGL_NEAREST};
	__property int GL_NEAREST_MIPMAP_LINEAR = {read=_GetGL_NEAREST_MIPMAP_LINEAR};
	__property int GL_NEAREST_MIPMAP_NEAREST = {read=_GetGL_NEAREST_MIPMAP_NEAREST};
	__property int GL_NEVER = {read=_GetGL_NEVER};
	__property int GL_NICEST = {read=_GetGL_NICEST};
	__property int GL_NOOP = {read=_GetGL_NOOP};
	__property int GL_NOR = {read=_GetGL_NOR};
	__property int GL_NORMALIZE = {read=_GetGL_NORMALIZE};
	__property int GL_NORMAL_ARRAY = {read=_GetGL_NORMAL_ARRAY};
	__property int GL_NOTEQUAL = {read=_GetGL_NOTEQUAL};
	__property int GL_NO_ERROR = {read=_GetGL_NO_ERROR};
	__property int GL_NUM_COMPRESSED_TEXTURE_FORMATS = {read=_GetGL_NUM_COMPRESSED_TEXTURE_FORMATS};
	__property int GL_ONE = {read=_GetGL_ONE};
	__property int GL_ONE_MINUS_DST_ALPHA = {read=_GetGL_ONE_MINUS_DST_ALPHA};
	__property int GL_ONE_MINUS_DST_COLOR = {read=_GetGL_ONE_MINUS_DST_COLOR};
	__property int GL_ONE_MINUS_SRC_ALPHA = {read=_GetGL_ONE_MINUS_SRC_ALPHA};
	__property int GL_ONE_MINUS_SRC_COLOR = {read=_GetGL_ONE_MINUS_SRC_COLOR};
	__property int GL_OR = {read=_GetGL_OR};
	__property int GL_OR_INVERTED = {read=_GetGL_OR_INVERTED};
	__property int GL_OR_REVERSE = {read=_GetGL_OR_REVERSE};
	__property int GL_OUT_OF_MEMORY = {read=_GetGL_OUT_OF_MEMORY};
	__property int GL_PACK_ALIGNMENT = {read=_GetGL_PACK_ALIGNMENT};
	__property int GL_PALETTE4_R5_G6_B5_OES = {read=_GetGL_PALETTE4_R5_G6_B5_OES};
	__property int GL_PALETTE4_RGB5_A1_OES = {read=_GetGL_PALETTE4_RGB5_A1_OES};
	__property int GL_PALETTE4_RGB8_OES = {read=_GetGL_PALETTE4_RGB8_OES};
	__property int GL_PALETTE4_RGBA4_OES = {read=_GetGL_PALETTE4_RGBA4_OES};
	__property int GL_PALETTE4_RGBA8_OES = {read=_GetGL_PALETTE4_RGBA8_OES};
	__property int GL_PALETTE8_R5_G6_B5_OES = {read=_GetGL_PALETTE8_R5_G6_B5_OES};
	__property int GL_PALETTE8_RGB5_A1_OES = {read=_GetGL_PALETTE8_RGB5_A1_OES};
	__property int GL_PALETTE8_RGB8_OES = {read=_GetGL_PALETTE8_RGB8_OES};
	__property int GL_PALETTE8_RGBA4_OES = {read=_GetGL_PALETTE8_RGBA4_OES};
	__property int GL_PALETTE8_RGBA8_OES = {read=_GetGL_PALETTE8_RGBA8_OES};
	__property int GL_PERSPECTIVE_CORRECTION_HINT = {read=_GetGL_PERSPECTIVE_CORRECTION_HINT};
	__property int GL_POINTS = {read=_GetGL_POINTS};
	__property int GL_POINT_FADE_THRESHOLD_SIZE = {read=_GetGL_POINT_FADE_THRESHOLD_SIZE};
	__property int GL_POINT_SIZE = {read=_GetGL_POINT_SIZE};
	__property int GL_POINT_SMOOTH = {read=_GetGL_POINT_SMOOTH};
	__property int GL_POINT_SMOOTH_HINT = {read=_GetGL_POINT_SMOOTH_HINT};
	__property int GL_POLYGON_OFFSET_FILL = {read=_GetGL_POLYGON_OFFSET_FILL};
	__property int GL_POLYGON_SMOOTH_HINT = {read=_GetGL_POLYGON_SMOOTH_HINT};
	__property int GL_POSITION = {read=_GetGL_POSITION};
	__property int GL_PROJECTION = {read=_GetGL_PROJECTION};
	__property int GL_QUADRATIC_ATTENUATION = {read=_GetGL_QUADRATIC_ATTENUATION};
	__property int GL_RED_BITS = {read=_GetGL_RED_BITS};
	__property int GL_RENDERER = {read=_GetGL_RENDERER};
	__property int GL_REPEAT = {read=_GetGL_REPEAT};
	__property int GL_REPLACE = {read=_GetGL_REPLACE};
	__property int GL_RESCALE_NORMAL = {read=_GetGL_RESCALE_NORMAL};
	__property int GL_RGB = {read=_GetGL_RGB};
	__property int GL_RGBA = {read=_GetGL_RGBA};
	__property int GL_SAMPLE_ALPHA_TO_COVERAGE = {read=_GetGL_SAMPLE_ALPHA_TO_COVERAGE};
	__property int GL_SAMPLE_ALPHA_TO_ONE = {read=_GetGL_SAMPLE_ALPHA_TO_ONE};
	__property int GL_SAMPLE_COVERAGE = {read=_GetGL_SAMPLE_COVERAGE};
	__property int GL_SCISSOR_TEST = {read=_GetGL_SCISSOR_TEST};
	__property int GL_SET = {read=_GetGL_SET};
	__property int GL_SHININESS = {read=_GetGL_SHININESS};
	__property int GL_SHORT = {read=_GetGL_SHORT};
	__property int GL_SMOOTH = {read=_GetGL_SMOOTH};
	__property int GL_SMOOTH_LINE_WIDTH_RANGE = {read=_GetGL_SMOOTH_LINE_WIDTH_RANGE};
	__property int GL_SMOOTH_POINT_SIZE_RANGE = {read=_GetGL_SMOOTH_POINT_SIZE_RANGE};
	__property int GL_SPECULAR = {read=_GetGL_SPECULAR};
	__property int GL_SPOT_CUTOFF = {read=_GetGL_SPOT_CUTOFF};
	__property int GL_SPOT_DIRECTION = {read=_GetGL_SPOT_DIRECTION};
	__property int GL_SPOT_EXPONENT = {read=_GetGL_SPOT_EXPONENT};
	__property int GL_SRC_ALPHA = {read=_GetGL_SRC_ALPHA};
	__property int GL_SRC_ALPHA_SATURATE = {read=_GetGL_SRC_ALPHA_SATURATE};
	__property int GL_SRC_COLOR = {read=_GetGL_SRC_COLOR};
	__property int GL_STACK_OVERFLOW = {read=_GetGL_STACK_OVERFLOW};
	__property int GL_STACK_UNDERFLOW = {read=_GetGL_STACK_UNDERFLOW};
	__property int GL_STENCIL_BITS = {read=_GetGL_STENCIL_BITS};
	__property int GL_STENCIL_BUFFER_BIT = {read=_GetGL_STENCIL_BUFFER_BIT};
	__property int GL_STENCIL_TEST = {read=_GetGL_STENCIL_TEST};
	__property int GL_SUBPIXEL_BITS = {read=_GetGL_SUBPIXEL_BITS};
	__property int GL_TEXTURE = {read=_GetGL_TEXTURE};
	__property int GL_TEXTURE0 = {read=_GetGL_TEXTURE0};
	__property int GL_TEXTURE1 = {read=_GetGL_TEXTURE1};
	__property int GL_TEXTURE10 = {read=_GetGL_TEXTURE10};
	__property int GL_TEXTURE11 = {read=_GetGL_TEXTURE11};
	__property int GL_TEXTURE12 = {read=_GetGL_TEXTURE12};
	__property int GL_TEXTURE13 = {read=_GetGL_TEXTURE13};
	__property int GL_TEXTURE14 = {read=_GetGL_TEXTURE14};
	__property int GL_TEXTURE15 = {read=_GetGL_TEXTURE15};
	__property int GL_TEXTURE16 = {read=_GetGL_TEXTURE16};
	__property int GL_TEXTURE17 = {read=_GetGL_TEXTURE17};
	__property int GL_TEXTURE18 = {read=_GetGL_TEXTURE18};
	__property int GL_TEXTURE19 = {read=_GetGL_TEXTURE19};
	__property int GL_TEXTURE2 = {read=_GetGL_TEXTURE2};
	__property int GL_TEXTURE20 = {read=_GetGL_TEXTURE20};
	__property int GL_TEXTURE21 = {read=_GetGL_TEXTURE21};
	__property int GL_TEXTURE22 = {read=_GetGL_TEXTURE22};
	__property int GL_TEXTURE23 = {read=_GetGL_TEXTURE23};
	__property int GL_TEXTURE24 = {read=_GetGL_TEXTURE24};
	__property int GL_TEXTURE25 = {read=_GetGL_TEXTURE25};
	__property int GL_TEXTURE26 = {read=_GetGL_TEXTURE26};
	__property int GL_TEXTURE27 = {read=_GetGL_TEXTURE27};
	__property int GL_TEXTURE28 = {read=_GetGL_TEXTURE28};
	__property int GL_TEXTURE29 = {read=_GetGL_TEXTURE29};
	__property int GL_TEXTURE3 = {read=_GetGL_TEXTURE3};
	__property int GL_TEXTURE30 = {read=_GetGL_TEXTURE30};
	__property int GL_TEXTURE31 = {read=_GetGL_TEXTURE31};
	__property int GL_TEXTURE4 = {read=_GetGL_TEXTURE4};
	__property int GL_TEXTURE5 = {read=_GetGL_TEXTURE5};
	__property int GL_TEXTURE6 = {read=_GetGL_TEXTURE6};
	__property int GL_TEXTURE7 = {read=_GetGL_TEXTURE7};
	__property int GL_TEXTURE8 = {read=_GetGL_TEXTURE8};
	__property int GL_TEXTURE9 = {read=_GetGL_TEXTURE9};
	__property int GL_TEXTURE_2D = {read=_GetGL_TEXTURE_2D};
	__property int GL_TEXTURE_COORD_ARRAY = {read=_GetGL_TEXTURE_COORD_ARRAY};
	__property int GL_TEXTURE_ENV = {read=_GetGL_TEXTURE_ENV};
	__property int GL_TEXTURE_ENV_COLOR = {read=_GetGL_TEXTURE_ENV_COLOR};
	__property int GL_TEXTURE_ENV_MODE = {read=_GetGL_TEXTURE_ENV_MODE};
	__property int GL_TEXTURE_MAG_FILTER = {read=_GetGL_TEXTURE_MAG_FILTER};
	__property int GL_TEXTURE_MIN_FILTER = {read=_GetGL_TEXTURE_MIN_FILTER};
	__property int GL_TEXTURE_WRAP_S = {read=_GetGL_TEXTURE_WRAP_S};
	__property int GL_TEXTURE_WRAP_T = {read=_GetGL_TEXTURE_WRAP_T};
	__property int GL_TRIANGLES = {read=_GetGL_TRIANGLES};
	__property int GL_TRIANGLE_FAN = {read=_GetGL_TRIANGLE_FAN};
	__property int GL_TRIANGLE_STRIP = {read=_GetGL_TRIANGLE_STRIP};
	__property int GL_TRUE = {read=_GetGL_TRUE};
	__property int GL_UNPACK_ALIGNMENT = {read=_GetGL_UNPACK_ALIGNMENT};
	__property int GL_UNSIGNED_BYTE = {read=_GetGL_UNSIGNED_BYTE};
	__property int GL_UNSIGNED_SHORT = {read=_GetGL_UNSIGNED_SHORT};
	__property int GL_UNSIGNED_SHORT_4_4_4_4 = {read=_GetGL_UNSIGNED_SHORT_4_4_4_4};
	__property int GL_UNSIGNED_SHORT_5_5_5_1 = {read=_GetGL_UNSIGNED_SHORT_5_5_5_1};
	__property int GL_UNSIGNED_SHORT_5_6_5 = {read=_GetGL_UNSIGNED_SHORT_5_6_5};
	__property int GL_VENDOR = {read=_GetGL_VENDOR};
	__property int GL_VERSION = {read=_GetGL_VERSION};
	__property int GL_VERTEX_ARRAY = {read=_GetGL_VERTEX_ARRAY};
	__property int GL_XOR = {read=_GetGL_XOR};
	__property int GL_ZERO = {read=_GetGL_ZERO};
};

__interface  INTERFACE_UUID("{C4CE6341-D0A4-4865-87A2-5251AE952149}") JGLES10  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLES10 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES10Class,_di_JGLES10>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES10Class,_di_JGLES10> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLES10() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES10Class,_di_JGLES10>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLES10() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{15FC6B5A-A329-4CA4-8C7B-96DD6FCA4775}") JGLES10ExtClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JGLES10Ext __cdecl init() = 0 ;
	virtual int __cdecl glQueryMatrixxOES(Androidapi::Jnibridge::TJavaArray__1<int>* mantissa, int mantissaOffset, Androidapi::Jnibridge::TJavaArray__1<int>* exponent, int exponentOffset) = 0 /* overload */;
	virtual int __cdecl glQueryMatrixxOES(Androidapi::Jni::Javatypes::_di_JIntBuffer mantissa, Androidapi::Jni::Javatypes::_di_JIntBuffer exponent) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{2AC60F2B-5ED3-4A6C-ACEC-AFE55D9545E7}") JGLES10Ext  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLES10Ext : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES10ExtClass,_di_JGLES10Ext>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES10ExtClass,_di_JGLES10Ext> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLES10Ext() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES10ExtClass,_di_JGLES10Ext>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLES10Ext() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7E756B17-DA84-4FA1-95BD-A2C395836589}") JGLES11Class  : public JGLES10Class 
{
	virtual int __cdecl _GetGL_ACTIVE_TEXTURE() = 0 ;
	virtual int __cdecl _GetGL_ADD_SIGNED() = 0 ;
	virtual int __cdecl _GetGL_ALPHA_SCALE() = 0 ;
	virtual int __cdecl _GetGL_ALPHA_TEST_FUNC() = 0 ;
	virtual int __cdecl _GetGL_ALPHA_TEST_REF() = 0 ;
	virtual int __cdecl _GetGL_ARRAY_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_ARRAY_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_BLEND_DST() = 0 ;
	virtual int __cdecl _GetGL_BLEND_SRC() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_ACCESS() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_SIZE() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_USAGE() = 0 ;
	virtual int __cdecl _GetGL_CLIENT_ACTIVE_TEXTURE() = 0 ;
	virtual int __cdecl _GetGL_CLIP_PLANE0() = 0 ;
	virtual int __cdecl _GetGL_CLIP_PLANE1() = 0 ;
	virtual int __cdecl _GetGL_CLIP_PLANE2() = 0 ;
	virtual int __cdecl _GetGL_CLIP_PLANE3() = 0 ;
	virtual int __cdecl _GetGL_CLIP_PLANE4() = 0 ;
	virtual int __cdecl _GetGL_CLIP_PLANE5() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ARRAY_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ARRAY_POINTER() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ARRAY_SIZE() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ARRAY_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ARRAY_TYPE() = 0 ;
	virtual int __cdecl _GetGL_COLOR_CLEAR_VALUE() = 0 ;
	virtual int __cdecl _GetGL_COLOR_WRITEMASK() = 0 ;
	virtual int __cdecl _GetGL_COMBINE() = 0 ;
	virtual int __cdecl _GetGL_COMBINE_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_COMBINE_RGB() = 0 ;
	virtual int __cdecl _GetGL_CONSTANT() = 0 ;
	virtual int __cdecl _GetGL_COORD_REPLACE_OES() = 0 ;
	virtual int __cdecl _GetGL_CULL_FACE_MODE() = 0 ;
	virtual int __cdecl _GetGL_CURRENT_COLOR() = 0 ;
	virtual int __cdecl _GetGL_CURRENT_NORMAL() = 0 ;
	virtual int __cdecl _GetGL_CURRENT_TEXTURE_COORDS() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_CLEAR_VALUE() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_FUNC() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_RANGE() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_WRITEMASK() = 0 ;
	virtual int __cdecl _GetGL_DOT3_RGB() = 0 ;
	virtual int __cdecl _GetGL_DOT3_RGBA() = 0 ;
	virtual int __cdecl _GetGL_DYNAMIC_DRAW() = 0 ;
	virtual int __cdecl _GetGL_ELEMENT_ARRAY_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_ELEMENT_ARRAY_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_FRONT_FACE() = 0 ;
	virtual int __cdecl _GetGL_GENERATE_MIPMAP() = 0 ;
	virtual int __cdecl _GetGL_GENERATE_MIPMAP_HINT() = 0 ;
	virtual int __cdecl _GetGL_INTERPOLATE() = 0 ;
	virtual int __cdecl _GetGL_LINE_WIDTH() = 0 ;
	virtual int __cdecl _GetGL_LOGIC_OP_MODE() = 0 ;
	virtual int __cdecl _GetGL_MATRIX_MODE() = 0 ;
	virtual int __cdecl _GetGL_MAX_CLIP_PLANES() = 0 ;
	virtual int __cdecl _GetGL_MODELVIEW_MATRIX() = 0 ;
	virtual int __cdecl _GetGL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES() = 0 ;
	virtual int __cdecl _GetGL_MODELVIEW_STACK_DEPTH() = 0 ;
	virtual int __cdecl _GetGL_NORMAL_ARRAY_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_NORMAL_ARRAY_POINTER() = 0 ;
	virtual int __cdecl _GetGL_NORMAL_ARRAY_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_NORMAL_ARRAY_TYPE() = 0 ;
	virtual int __cdecl _GetGL_OPERAND0_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_OPERAND0_RGB() = 0 ;
	virtual int __cdecl _GetGL_OPERAND1_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_OPERAND1_RGB() = 0 ;
	virtual int __cdecl _GetGL_OPERAND2_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_OPERAND2_RGB() = 0 ;
	virtual int __cdecl _GetGL_POINT_DISTANCE_ATTENUATION() = 0 ;
	HIDESBASE virtual int __cdecl _GetGL_POINT_FADE_THRESHOLD_SIZE() = 0 ;
	HIDESBASE virtual int __cdecl _GetGL_POINT_SIZE() = 0 ;
	virtual int __cdecl _GetGL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES() = 0 ;
	virtual int __cdecl _GetGL_POINT_SIZE_ARRAY_OES() = 0 ;
	virtual int __cdecl _GetGL_POINT_SIZE_ARRAY_POINTER_OES() = 0 ;
	virtual int __cdecl _GetGL_POINT_SIZE_ARRAY_STRIDE_OES() = 0 ;
	virtual int __cdecl _GetGL_POINT_SIZE_ARRAY_TYPE_OES() = 0 ;
	virtual int __cdecl _GetGL_POINT_SIZE_MAX() = 0 ;
	virtual int __cdecl _GetGL_POINT_SIZE_MIN() = 0 ;
	virtual int __cdecl _GetGL_POINT_SPRITE_OES() = 0 ;
	virtual int __cdecl _GetGL_POLYGON_OFFSET_FACTOR() = 0 ;
	virtual int __cdecl _GetGL_POLYGON_OFFSET_UNITS() = 0 ;
	virtual int __cdecl _GetGL_PREVIOUS() = 0 ;
	virtual int __cdecl _GetGL_PRIMARY_COLOR() = 0 ;
	virtual int __cdecl _GetGL_PROJECTION_MATRIX() = 0 ;
	virtual int __cdecl _GetGL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES() = 0 ;
	virtual int __cdecl _GetGL_PROJECTION_STACK_DEPTH() = 0 ;
	virtual int __cdecl _GetGL_RGB_SCALE() = 0 ;
	virtual int __cdecl _GetGL_SAMPLES() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_BUFFERS() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_COVERAGE_INVERT() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_COVERAGE_VALUE() = 0 ;
	virtual int __cdecl _GetGL_SCISSOR_BOX() = 0 ;
	virtual int __cdecl _GetGL_SHADE_MODEL() = 0 ;
	virtual int __cdecl _GetGL_SRC0_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_SRC0_RGB() = 0 ;
	virtual int __cdecl _GetGL_SRC1_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_SRC1_RGB() = 0 ;
	virtual int __cdecl _GetGL_SRC2_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_SRC2_RGB() = 0 ;
	virtual int __cdecl _GetGL_STATIC_DRAW() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_CLEAR_VALUE() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_FAIL() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_FUNC() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_PASS_DEPTH_FAIL() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_PASS_DEPTH_PASS() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_REF() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_VALUE_MASK() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_WRITEMASK() = 0 ;
	virtual int __cdecl _GetGL_SUBTRACT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_2D() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_COORD_ARRAY_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_COORD_ARRAY_POINTER() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_COORD_ARRAY_SIZE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_COORD_ARRAY_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_COORD_ARRAY_TYPE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_MATRIX() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_STACK_DEPTH() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ARRAY_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ARRAY_POINTER() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ARRAY_SIZE() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ARRAY_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ARRAY_TYPE() = 0 ;
	virtual int __cdecl _GetGL_VIEWPORT() = 0 ;
	virtual int __cdecl _GetGL_WRITE_ONLY() = 0 ;
	HIDESBASE virtual _di_JGLES11 __cdecl init() = 0 ;
	virtual void __cdecl glBindBuffer(int target, int buffer) = 0 ;
	virtual void __cdecl glBufferData(int target, int size, Androidapi::Jni::Javatypes::_di_JBuffer data, int usage) = 0 ;
	virtual void __cdecl glBufferSubData(int target, int offset, int size, Androidapi::Jni::Javatypes::_di_JBuffer data) = 0 ;
	virtual void __cdecl glClipPlanef(int plane, Androidapi::Jnibridge::TJavaArray__1<float>* equation, int offset) = 0 /* overload */;
	virtual void __cdecl glClipPlanef(int plane, Androidapi::Jni::Javatypes::_di_JFloatBuffer equation) = 0 /* overload */;
	virtual void __cdecl glClipPlanex(int plane, Androidapi::Jnibridge::TJavaArray__1<int>* equation, int offset) = 0 /* overload */;
	virtual void __cdecl glClipPlanex(int plane, Androidapi::Jni::Javatypes::_di_JIntBuffer equation) = 0 /* overload */;
	virtual void __cdecl glColor4ub(System::Byte red, System::Byte green, System::Byte blue, System::Byte alpha) = 0 ;
	HIDESBASE virtual void __cdecl glColorPointer(int size, int type_, int stride, int offset) = 0 ;
	virtual void __cdecl glDeleteBuffers(int n, Androidapi::Jnibridge::TJavaArray__1<int>* buffers, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteBuffers(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer buffers) = 0 /* overload */;
	HIDESBASE virtual void __cdecl glDrawElements(int mode, int count, int type_, int offset) = 0 ;
	virtual void __cdecl glGenBuffers(int n, Androidapi::Jnibridge::TJavaArray__1<int>* buffers, int offset) = 0 /* overload */;
	virtual void __cdecl glGenBuffers(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer buffers) = 0 /* overload */;
	virtual void __cdecl glGetBooleanv(int pname, Androidapi::Jnibridge::TJavaArray__1<bool>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetBooleanv(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetBufferParameteriv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetBufferParameteriv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetClipPlanef(int pname, Androidapi::Jnibridge::TJavaArray__1<float>* eqn, int offset) = 0 /* overload */;
	virtual void __cdecl glGetClipPlanef(int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer eqn) = 0 /* overload */;
	virtual void __cdecl glGetClipPlanex(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* eqn, int offset) = 0 /* overload */;
	virtual void __cdecl glGetClipPlanex(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer eqn) = 0 /* overload */;
	virtual void __cdecl glGetFixedv(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetFixedv(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetFloatv(int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetFloatv(int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetLightfv(int light, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetLightfv(int light, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetLightxv(int light, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetLightxv(int light, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetMaterialfv(int face, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetMaterialfv(int face, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetMaterialxv(int face, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetMaterialxv(int face, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexEnvfv(int env, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexEnvfv(int env, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexEnviv(int env, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexEnviv(int env, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexEnvxv(int env, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexEnvxv(int env, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterfv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterfv(int target, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexParameteriv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexParameteriv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterxv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterxv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual bool __cdecl glIsBuffer(int buffer) = 0 ;
	virtual bool __cdecl glIsEnabled(int cap) = 0 ;
	virtual bool __cdecl glIsTexture(int texture) = 0 ;
	HIDESBASE virtual void __cdecl glNormalPointer(int type_, int stride, int offset) = 0 ;
	virtual void __cdecl glPointParameterf(int pname, float param) = 0 ;
	virtual void __cdecl glPointParameterfv(int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glPointParameterfv(int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glPointParameterx(int pname, int param) = 0 ;
	virtual void __cdecl glPointParameterxv(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glPointParameterxv(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glPointSizePointerOES(int type_, int stride, Androidapi::Jni::Javatypes::_di_JBuffer pointer) = 0 ;
	HIDESBASE virtual void __cdecl glTexCoordPointer(int size, int type_, int stride, int offset) = 0 ;
	virtual void __cdecl glTexEnvi(int target, int pname, int param) = 0 ;
	virtual void __cdecl glTexEnviv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexEnviv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexParameterfv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexParameterfv(int target, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexParameteri(int target, int pname, int param) = 0 ;
	virtual void __cdecl glTexParameteriv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexParameteriv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexParameterxv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexParameterxv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	HIDESBASE virtual void __cdecl glVertexPointer(int size, int type_, int stride, int offset) = 0 ;
	__property int GL_ACTIVE_TEXTURE = {read=_GetGL_ACTIVE_TEXTURE};
	__property int GL_ADD_SIGNED = {read=_GetGL_ADD_SIGNED};
	__property int GL_ALPHA_SCALE = {read=_GetGL_ALPHA_SCALE};
	__property int GL_ALPHA_TEST_FUNC = {read=_GetGL_ALPHA_TEST_FUNC};
	__property int GL_ALPHA_TEST_REF = {read=_GetGL_ALPHA_TEST_REF};
	__property int GL_ARRAY_BUFFER = {read=_GetGL_ARRAY_BUFFER};
	__property int GL_ARRAY_BUFFER_BINDING = {read=_GetGL_ARRAY_BUFFER_BINDING};
	__property int GL_BLEND_DST = {read=_GetGL_BLEND_DST};
	__property int GL_BLEND_SRC = {read=_GetGL_BLEND_SRC};
	__property int GL_BUFFER_ACCESS = {read=_GetGL_BUFFER_ACCESS};
	__property int GL_BUFFER_SIZE = {read=_GetGL_BUFFER_SIZE};
	__property int GL_BUFFER_USAGE = {read=_GetGL_BUFFER_USAGE};
	__property int GL_CLIENT_ACTIVE_TEXTURE = {read=_GetGL_CLIENT_ACTIVE_TEXTURE};
	__property int GL_CLIP_PLANE0 = {read=_GetGL_CLIP_PLANE0};
	__property int GL_CLIP_PLANE1 = {read=_GetGL_CLIP_PLANE1};
	__property int GL_CLIP_PLANE2 = {read=_GetGL_CLIP_PLANE2};
	__property int GL_CLIP_PLANE3 = {read=_GetGL_CLIP_PLANE3};
	__property int GL_CLIP_PLANE4 = {read=_GetGL_CLIP_PLANE4};
	__property int GL_CLIP_PLANE5 = {read=_GetGL_CLIP_PLANE5};
	__property int GL_COLOR_ARRAY_BUFFER_BINDING = {read=_GetGL_COLOR_ARRAY_BUFFER_BINDING};
	__property int GL_COLOR_ARRAY_POINTER = {read=_GetGL_COLOR_ARRAY_POINTER};
	__property int GL_COLOR_ARRAY_SIZE = {read=_GetGL_COLOR_ARRAY_SIZE};
	__property int GL_COLOR_ARRAY_STRIDE = {read=_GetGL_COLOR_ARRAY_STRIDE};
	__property int GL_COLOR_ARRAY_TYPE = {read=_GetGL_COLOR_ARRAY_TYPE};
	__property int GL_COLOR_CLEAR_VALUE = {read=_GetGL_COLOR_CLEAR_VALUE};
	__property int GL_COLOR_WRITEMASK = {read=_GetGL_COLOR_WRITEMASK};
	__property int GL_COMBINE = {read=_GetGL_COMBINE};
	__property int GL_COMBINE_ALPHA = {read=_GetGL_COMBINE_ALPHA};
	__property int GL_COMBINE_RGB = {read=_GetGL_COMBINE_RGB};
	__property int GL_CONSTANT = {read=_GetGL_CONSTANT};
	__property int GL_COORD_REPLACE_OES = {read=_GetGL_COORD_REPLACE_OES};
	__property int GL_CULL_FACE_MODE = {read=_GetGL_CULL_FACE_MODE};
	__property int GL_CURRENT_COLOR = {read=_GetGL_CURRENT_COLOR};
	__property int GL_CURRENT_NORMAL = {read=_GetGL_CURRENT_NORMAL};
	__property int GL_CURRENT_TEXTURE_COORDS = {read=_GetGL_CURRENT_TEXTURE_COORDS};
	__property int GL_DEPTH_CLEAR_VALUE = {read=_GetGL_DEPTH_CLEAR_VALUE};
	__property int GL_DEPTH_FUNC = {read=_GetGL_DEPTH_FUNC};
	__property int GL_DEPTH_RANGE = {read=_GetGL_DEPTH_RANGE};
	__property int GL_DEPTH_WRITEMASK = {read=_GetGL_DEPTH_WRITEMASK};
	__property int GL_DOT3_RGB = {read=_GetGL_DOT3_RGB};
	__property int GL_DOT3_RGBA = {read=_GetGL_DOT3_RGBA};
	__property int GL_DYNAMIC_DRAW = {read=_GetGL_DYNAMIC_DRAW};
	__property int GL_ELEMENT_ARRAY_BUFFER = {read=_GetGL_ELEMENT_ARRAY_BUFFER};
	__property int GL_ELEMENT_ARRAY_BUFFER_BINDING = {read=_GetGL_ELEMENT_ARRAY_BUFFER_BINDING};
	__property int GL_FRONT_FACE = {read=_GetGL_FRONT_FACE};
	__property int GL_GENERATE_MIPMAP = {read=_GetGL_GENERATE_MIPMAP};
	__property int GL_GENERATE_MIPMAP_HINT = {read=_GetGL_GENERATE_MIPMAP_HINT};
	__property int GL_INTERPOLATE = {read=_GetGL_INTERPOLATE};
	__property int GL_LINE_WIDTH = {read=_GetGL_LINE_WIDTH};
	__property int GL_LOGIC_OP_MODE = {read=_GetGL_LOGIC_OP_MODE};
	__property int GL_MATRIX_MODE = {read=_GetGL_MATRIX_MODE};
	__property int GL_MAX_CLIP_PLANES = {read=_GetGL_MAX_CLIP_PLANES};
	__property int GL_MODELVIEW_MATRIX = {read=_GetGL_MODELVIEW_MATRIX};
	__property int GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES = {read=_GetGL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES};
	__property int GL_MODELVIEW_STACK_DEPTH = {read=_GetGL_MODELVIEW_STACK_DEPTH};
	__property int GL_NORMAL_ARRAY_BUFFER_BINDING = {read=_GetGL_NORMAL_ARRAY_BUFFER_BINDING};
	__property int GL_NORMAL_ARRAY_POINTER = {read=_GetGL_NORMAL_ARRAY_POINTER};
	__property int GL_NORMAL_ARRAY_STRIDE = {read=_GetGL_NORMAL_ARRAY_STRIDE};
	__property int GL_NORMAL_ARRAY_TYPE = {read=_GetGL_NORMAL_ARRAY_TYPE};
	__property int GL_OPERAND0_ALPHA = {read=_GetGL_OPERAND0_ALPHA};
	__property int GL_OPERAND0_RGB = {read=_GetGL_OPERAND0_RGB};
	__property int GL_OPERAND1_ALPHA = {read=_GetGL_OPERAND1_ALPHA};
	__property int GL_OPERAND1_RGB = {read=_GetGL_OPERAND1_RGB};
	__property int GL_OPERAND2_ALPHA = {read=_GetGL_OPERAND2_ALPHA};
	__property int GL_OPERAND2_RGB = {read=_GetGL_OPERAND2_RGB};
	__property int GL_POINT_DISTANCE_ATTENUATION = {read=_GetGL_POINT_DISTANCE_ATTENUATION};
	__property int GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES = {read=_GetGL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES};
	__property int GL_POINT_SIZE_ARRAY_OES = {read=_GetGL_POINT_SIZE_ARRAY_OES};
	__property int GL_POINT_SIZE_ARRAY_POINTER_OES = {read=_GetGL_POINT_SIZE_ARRAY_POINTER_OES};
	__property int GL_POINT_SIZE_ARRAY_STRIDE_OES = {read=_GetGL_POINT_SIZE_ARRAY_STRIDE_OES};
	__property int GL_POINT_SIZE_ARRAY_TYPE_OES = {read=_GetGL_POINT_SIZE_ARRAY_TYPE_OES};
	__property int GL_POINT_SIZE_MAX = {read=_GetGL_POINT_SIZE_MAX};
	__property int GL_POINT_SIZE_MIN = {read=_GetGL_POINT_SIZE_MIN};
	__property int GL_POINT_SPRITE_OES = {read=_GetGL_POINT_SPRITE_OES};
	__property int GL_POLYGON_OFFSET_FACTOR = {read=_GetGL_POLYGON_OFFSET_FACTOR};
	__property int GL_POLYGON_OFFSET_UNITS = {read=_GetGL_POLYGON_OFFSET_UNITS};
	__property int GL_PREVIOUS = {read=_GetGL_PREVIOUS};
	__property int GL_PRIMARY_COLOR = {read=_GetGL_PRIMARY_COLOR};
	__property int GL_PROJECTION_MATRIX = {read=_GetGL_PROJECTION_MATRIX};
	__property int GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES = {read=_GetGL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES};
	__property int GL_PROJECTION_STACK_DEPTH = {read=_GetGL_PROJECTION_STACK_DEPTH};
	__property int GL_RGB_SCALE = {read=_GetGL_RGB_SCALE};
	__property int GL_SAMPLES = {read=_GetGL_SAMPLES};
	__property int GL_SAMPLE_BUFFERS = {read=_GetGL_SAMPLE_BUFFERS};
	__property int GL_SAMPLE_COVERAGE_INVERT = {read=_GetGL_SAMPLE_COVERAGE_INVERT};
	__property int GL_SAMPLE_COVERAGE_VALUE = {read=_GetGL_SAMPLE_COVERAGE_VALUE};
	__property int GL_SCISSOR_BOX = {read=_GetGL_SCISSOR_BOX};
	__property int GL_SHADE_MODEL = {read=_GetGL_SHADE_MODEL};
	__property int GL_SRC0_ALPHA = {read=_GetGL_SRC0_ALPHA};
	__property int GL_SRC0_RGB = {read=_GetGL_SRC0_RGB};
	__property int GL_SRC1_ALPHA = {read=_GetGL_SRC1_ALPHA};
	__property int GL_SRC1_RGB = {read=_GetGL_SRC1_RGB};
	__property int GL_SRC2_ALPHA = {read=_GetGL_SRC2_ALPHA};
	__property int GL_SRC2_RGB = {read=_GetGL_SRC2_RGB};
	__property int GL_STATIC_DRAW = {read=_GetGL_STATIC_DRAW};
	__property int GL_STENCIL_CLEAR_VALUE = {read=_GetGL_STENCIL_CLEAR_VALUE};
	__property int GL_STENCIL_FAIL = {read=_GetGL_STENCIL_FAIL};
	__property int GL_STENCIL_FUNC = {read=_GetGL_STENCIL_FUNC};
	__property int GL_STENCIL_PASS_DEPTH_FAIL = {read=_GetGL_STENCIL_PASS_DEPTH_FAIL};
	__property int GL_STENCIL_PASS_DEPTH_PASS = {read=_GetGL_STENCIL_PASS_DEPTH_PASS};
	__property int GL_STENCIL_REF = {read=_GetGL_STENCIL_REF};
	__property int GL_STENCIL_VALUE_MASK = {read=_GetGL_STENCIL_VALUE_MASK};
	__property int GL_STENCIL_WRITEMASK = {read=_GetGL_STENCIL_WRITEMASK};
	__property int GL_SUBTRACT = {read=_GetGL_SUBTRACT};
	__property int GL_TEXTURE_BINDING_2D = {read=_GetGL_TEXTURE_BINDING_2D};
	__property int GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING = {read=_GetGL_TEXTURE_COORD_ARRAY_BUFFER_BINDING};
	__property int GL_TEXTURE_COORD_ARRAY_POINTER = {read=_GetGL_TEXTURE_COORD_ARRAY_POINTER};
	__property int GL_TEXTURE_COORD_ARRAY_SIZE = {read=_GetGL_TEXTURE_COORD_ARRAY_SIZE};
	__property int GL_TEXTURE_COORD_ARRAY_STRIDE = {read=_GetGL_TEXTURE_COORD_ARRAY_STRIDE};
	__property int GL_TEXTURE_COORD_ARRAY_TYPE = {read=_GetGL_TEXTURE_COORD_ARRAY_TYPE};
	__property int GL_TEXTURE_MATRIX = {read=_GetGL_TEXTURE_MATRIX};
	__property int GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES = {read=_GetGL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES};
	__property int GL_TEXTURE_STACK_DEPTH = {read=_GetGL_TEXTURE_STACK_DEPTH};
	__property int GL_VERTEX_ARRAY_BUFFER_BINDING = {read=_GetGL_VERTEX_ARRAY_BUFFER_BINDING};
	__property int GL_VERTEX_ARRAY_POINTER = {read=_GetGL_VERTEX_ARRAY_POINTER};
	__property int GL_VERTEX_ARRAY_SIZE = {read=_GetGL_VERTEX_ARRAY_SIZE};
	__property int GL_VERTEX_ARRAY_STRIDE = {read=_GetGL_VERTEX_ARRAY_STRIDE};
	__property int GL_VERTEX_ARRAY_TYPE = {read=_GetGL_VERTEX_ARRAY_TYPE};
	__property int GL_VIEWPORT = {read=_GetGL_VIEWPORT};
	__property int GL_WRITE_ONLY = {read=_GetGL_WRITE_ONLY};
};

__interface  INTERFACE_UUID("{07CD2AD1-3814-49AC-AA6E-09475BED866C}") JGLES11  : public JGLES10 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLES11 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES11Class,_di_JGLES11>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES11Class,_di_JGLES11> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLES11() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES11Class,_di_JGLES11>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLES11() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{67F44FDE-35A7-4E7D-A292-13B5A0A63992}") JGLES11ExtClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetGL_3DC_XY_AMD() = 0 ;
	virtual int __cdecl _GetGL_3DC_X_AMD() = 0 ;
	virtual int __cdecl _GetGL_ATC_RGBA_EXPLICIT_ALPHA_AMD() = 0 ;
	virtual int __cdecl _GetGL_ATC_RGBA_INTERPOLATED_ALPHA_AMD() = 0 ;
	virtual int __cdecl _GetGL_ATC_RGB_AMD() = 0 ;
	virtual int __cdecl _GetGL_BGRA() = 0 ;
	virtual int __cdecl _GetGL_BLEND_DST_ALPHA_OES() = 0 ;
	virtual int __cdecl _GetGL_BLEND_DST_RGB_OES() = 0 ;
	virtual int __cdecl _GetGL_BLEND_EQUATION_ALPHA_OES() = 0 ;
	virtual int __cdecl _GetGL_BLEND_EQUATION_OES() = 0 ;
	virtual int __cdecl _GetGL_BLEND_EQUATION_RGB_OES() = 0 ;
	virtual int __cdecl _GetGL_BLEND_SRC_ALPHA_OES() = 0 ;
	virtual int __cdecl _GetGL_BLEND_SRC_RGB_OES() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_ACCESS_OES() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_MAPPED_OES() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_MAP_POINTER_OES() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT0_OES() = 0 ;
	virtual int __cdecl _GetGL_CURRENT_PALETTE_MATRIX_OES() = 0 ;
	virtual int __cdecl _GetGL_DECR_WRAP_OES() = 0 ;
	virtual int __cdecl _GetGL_DEPTH24_STENCIL8_OES() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_ATTACHMENT_OES() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_COMPONENT16_OES() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_COMPONENT24_OES() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_COMPONENT32_OES() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_STENCIL_OES() = 0 ;
	virtual int __cdecl _GetGL_ETC1_RGB8_OES() = 0 ;
	virtual int __cdecl _GetGL_FIXED_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_BINDING_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_COMPLETE_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_UNSUPPORTED_OES() = 0 ;
	virtual int __cdecl _GetGL_FUNC_ADD_OES() = 0 ;
	virtual int __cdecl _GetGL_FUNC_REVERSE_SUBTRACT_OES() = 0 ;
	virtual int __cdecl _GetGL_FUNC_SUBTRACT_OES() = 0 ;
	virtual int __cdecl _GetGL_INCR_WRAP_OES() = 0 ;
	virtual int __cdecl _GetGL_INVALID_FRAMEBUFFER_OPERATION_OES() = 0 ;
	virtual int __cdecl _GetGL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES() = 0 ;
	virtual int __cdecl _GetGL_MATRIX_INDEX_ARRAY_OES() = 0 ;
	virtual int __cdecl _GetGL_MATRIX_INDEX_ARRAY_POINTER_OES() = 0 ;
	virtual int __cdecl _GetGL_MATRIX_INDEX_ARRAY_SIZE_OES() = 0 ;
	virtual int __cdecl _GetGL_MATRIX_INDEX_ARRAY_STRIDE_OES() = 0 ;
	virtual int __cdecl _GetGL_MATRIX_INDEX_ARRAY_TYPE_OES() = 0 ;
	virtual int __cdecl _GetGL_MATRIX_PALETTE_OES() = 0 ;
	virtual int __cdecl _GetGL_MAX_CUBE_MAP_TEXTURE_SIZE_OES() = 0 ;
	virtual int __cdecl _GetGL_MAX_PALETTE_MATRICES_OES() = 0 ;
	virtual int __cdecl _GetGL_MAX_RENDERBUFFER_SIZE_OES() = 0 ;
	virtual int __cdecl _GetGL_MAX_TEXTURE_MAX_ANISOTROPY_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_UNITS_OES() = 0 ;
	virtual int __cdecl _GetGL_MIRRORED_REPEAT_OES() = 0 ;
	virtual int __cdecl _GetGL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES() = 0 ;
	virtual int __cdecl _GetGL_NONE_OES() = 0 ;
	virtual int __cdecl _GetGL_NORMAL_MAP_OES() = 0 ;
	virtual int __cdecl _GetGL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES() = 0 ;
	virtual int __cdecl _GetGL_REFLECTION_MAP_OES() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_ALPHA_SIZE_OES() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_BINDING_OES() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_BLUE_SIZE_OES() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_DEPTH_SIZE_OES() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_GREEN_SIZE_OES() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_HEIGHT_OES() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_INTERNAL_FORMAT_OES() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_OES() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_RED_SIZE_OES() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_STENCIL_SIZE_OES() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_WIDTH_OES() = 0 ;
	virtual int __cdecl _GetGL_REQUIRED_TEXTURE_IMAGE_UNITS_OES() = 0 ;
	virtual int __cdecl _GetGL_RGB565_OES() = 0 ;
	virtual int __cdecl _GetGL_RGB5_A1_OES() = 0 ;
	virtual int __cdecl _GetGL_RGB8_OES() = 0 ;
	virtual int __cdecl _GetGL_RGBA4_OES() = 0 ;
	virtual int __cdecl _GetGL_RGBA8_OES() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_EXTERNAL_OES() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_ATTACHMENT_OES() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_INDEX1_OES() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_INDEX4_OES() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_INDEX8_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_CUBE_MAP_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_EXTERNAL_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CROP_RECT_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_POSITIVE_X_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_POSITIVE_Y_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_POSITIVE_Z_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_EXTERNAL_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_GEN_MODE_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_GEN_STR_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_MAX_ANISOTROPY_EXT() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_24_8_OES() = 0 ;
	virtual int __cdecl _GetGL_WEIGHT_ARRAY_BUFFER_BINDING_OES() = 0 ;
	virtual int __cdecl _GetGL_WEIGHT_ARRAY_OES() = 0 ;
	virtual int __cdecl _GetGL_WEIGHT_ARRAY_POINTER_OES() = 0 ;
	virtual int __cdecl _GetGL_WEIGHT_ARRAY_SIZE_OES() = 0 ;
	virtual int __cdecl _GetGL_WEIGHT_ARRAY_STRIDE_OES() = 0 ;
	virtual int __cdecl _GetGL_WEIGHT_ARRAY_TYPE_OES() = 0 ;
	virtual int __cdecl _GetGL_WRITE_ONLY_OES() = 0 ;
	HIDESBASE virtual _di_JGLES11Ext __cdecl init() = 0 ;
	virtual void __cdecl glAlphaFuncxOES(int func, int ref) = 0 ;
	virtual void __cdecl glBindFramebufferOES(int target, int framebuffer) = 0 ;
	virtual void __cdecl glBindRenderbufferOES(int target, int renderbuffer) = 0 ;
	virtual void __cdecl glBlendEquationOES(int mode) = 0 ;
	virtual void __cdecl glBlendEquationSeparateOES(int modeRGB, int modeAlpha) = 0 ;
	virtual void __cdecl glBlendFuncSeparateOES(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) = 0 ;
	virtual int __cdecl glCheckFramebufferStatusOES(int target) = 0 ;
	virtual void __cdecl glClearColorxOES(int red, int green, int blue, int alpha) = 0 ;
	virtual void __cdecl glClearDepthfOES(float depth) = 0 ;
	virtual void __cdecl glClearDepthxOES(int depth) = 0 ;
	virtual void __cdecl glClipPlanefOES(int plane, Androidapi::Jnibridge::TJavaArray__1<float>* equation, int offset) = 0 /* overload */;
	virtual void __cdecl glClipPlanefOES(int plane, Androidapi::Jni::Javatypes::_di_JFloatBuffer equation) = 0 /* overload */;
	virtual void __cdecl glClipPlanexOES(int plane, Androidapi::Jnibridge::TJavaArray__1<int>* equation, int offset) = 0 /* overload */;
	virtual void __cdecl glClipPlanexOES(int plane, Androidapi::Jni::Javatypes::_di_JIntBuffer equation) = 0 /* overload */;
	virtual void __cdecl glColor4xOES(int red, int green, int blue, int alpha) = 0 ;
	virtual void __cdecl glCurrentPaletteMatrixOES(int matrixpaletteindex) = 0 ;
	virtual void __cdecl glDeleteFramebuffersOES(int n, Androidapi::Jnibridge::TJavaArray__1<int>* framebuffers, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteFramebuffersOES(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer framebuffers) = 0 /* overload */;
	virtual void __cdecl glDeleteRenderbuffersOES(int n, Androidapi::Jnibridge::TJavaArray__1<int>* renderbuffers, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteRenderbuffersOES(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer renderbuffers) = 0 /* overload */;
	virtual void __cdecl glDepthRangefOES(float zNear, float zFar) = 0 ;
	virtual void __cdecl glDepthRangexOES(int zNear, int zFar) = 0 ;
	virtual void __cdecl glDrawTexfOES(float x, float y, float z, float width, float height) = 0 ;
	virtual void __cdecl glDrawTexfvOES(Androidapi::Jnibridge::TJavaArray__1<float>* coords, int offset) = 0 /* overload */;
	virtual void __cdecl glDrawTexfvOES(Androidapi::Jni::Javatypes::_di_JFloatBuffer coords) = 0 /* overload */;
	virtual void __cdecl glDrawTexiOES(int x, int y, int z, int width, int height) = 0 ;
	virtual void __cdecl glDrawTexivOES(Androidapi::Jnibridge::TJavaArray__1<int>* coords, int offset) = 0 /* overload */;
	virtual void __cdecl glDrawTexivOES(Androidapi::Jni::Javatypes::_di_JIntBuffer coords) = 0 /* overload */;
	virtual void __cdecl glDrawTexsOES(short x, short y, short z, short width, short height) = 0 ;
	virtual void __cdecl glDrawTexsvOES(Androidapi::Jnibridge::TJavaArray__1<short>* coords, int offset) = 0 /* overload */;
	virtual void __cdecl glDrawTexsvOES(Androidapi::Jni::Javatypes::_di_JShortBuffer coords) = 0 /* overload */;
	virtual void __cdecl glDrawTexxOES(int x, int y, int z, int width, int height) = 0 ;
	virtual void __cdecl glDrawTexxvOES(Androidapi::Jnibridge::TJavaArray__1<int>* coords, int offset) = 0 /* overload */;
	virtual void __cdecl glDrawTexxvOES(Androidapi::Jni::Javatypes::_di_JIntBuffer coords) = 0 /* overload */;
	virtual void __cdecl glEGLImageTargetRenderbufferStorageOES(int target, Androidapi::Jni::Javatypes::_di_JBuffer image) = 0 ;
	virtual void __cdecl glEGLImageTargetTexture2DOES(int target, Androidapi::Jni::Javatypes::_di_JBuffer image) = 0 ;
	virtual void __cdecl glFogxOES(int pname, int param) = 0 ;
	virtual void __cdecl glFogxvOES(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glFogxvOES(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glFramebufferRenderbufferOES(int target, int attachment, int renderbuffertarget, int renderbuffer) = 0 ;
	virtual void __cdecl glFramebufferTexture2DOES(int target, int attachment, int textarget, int texture, int level) = 0 ;
	virtual void __cdecl glFrustumfOES(float left, float right, float bottom, float top, float zNear, float zFar) = 0 ;
	virtual void __cdecl glFrustumxOES(int left, int right, int bottom, int top, int zNear, int zFar) = 0 ;
	virtual void __cdecl glGenFramebuffersOES(int n, Androidapi::Jnibridge::TJavaArray__1<int>* framebuffers, int offset) = 0 /* overload */;
	virtual void __cdecl glGenFramebuffersOES(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer framebuffers) = 0 /* overload */;
	virtual void __cdecl glGenRenderbuffersOES(int n, Androidapi::Jnibridge::TJavaArray__1<int>* renderbuffers, int offset) = 0 /* overload */;
	virtual void __cdecl glGenRenderbuffersOES(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer renderbuffers) = 0 /* overload */;
	virtual void __cdecl glGenerateMipmapOES(int target) = 0 ;
	virtual void __cdecl glGetClipPlanefOES(int pname, Androidapi::Jnibridge::TJavaArray__1<float>* eqn, int offset) = 0 /* overload */;
	virtual void __cdecl glGetClipPlanefOES(int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer eqn) = 0 /* overload */;
	virtual void __cdecl glGetClipPlanexOES(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* eqn, int offset) = 0 /* overload */;
	virtual void __cdecl glGetClipPlanexOES(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer eqn) = 0 /* overload */;
	virtual void __cdecl glGetFixedvOES(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetFixedvOES(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetFramebufferAttachmentParameterivOES(int target, int attachment, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetFramebufferAttachmentParameterivOES(int target, int attachment, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetLightxvOES(int light, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetLightxvOES(int light, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetMaterialxvOES(int face, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetMaterialxvOES(int face, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetRenderbufferParameterivOES(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetRenderbufferParameterivOES(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexEnvxvOES(int env, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexEnvxvOES(int env, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexGenfvOES(int coord, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexGenfvOES(int coord, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexGenivOES(int coord, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexGenivOES(int coord, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexGenxvOES(int coord, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexGenxvOES(int coord, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterxvOES(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterxvOES(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual bool __cdecl glIsFramebufferOES(int framebuffer) = 0 ;
	virtual bool __cdecl glIsRenderbufferOES(int renderbuffer) = 0 ;
	virtual void __cdecl glLightModelxOES(int pname, int param) = 0 ;
	virtual void __cdecl glLightModelxvOES(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glLightModelxvOES(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glLightxOES(int light, int pname, int param) = 0 ;
	virtual void __cdecl glLightxvOES(int light, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glLightxvOES(int light, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glLineWidthxOES(int width) = 0 ;
	virtual void __cdecl glLoadMatrixxOES(Androidapi::Jnibridge::TJavaArray__1<int>* m, int offset) = 0 /* overload */;
	virtual void __cdecl glLoadMatrixxOES(Androidapi::Jni::Javatypes::_di_JIntBuffer m) = 0 /* overload */;
	virtual void __cdecl glLoadPaletteFromModelViewMatrixOES() = 0 ;
	virtual void __cdecl glMaterialxOES(int face, int pname, int param) = 0 ;
	virtual void __cdecl glMaterialxvOES(int face, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glMaterialxvOES(int face, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glMatrixIndexPointerOES(int size, int type_, int stride, Androidapi::Jni::Javatypes::_di_JBuffer pointer) = 0 ;
	virtual void __cdecl glMultMatrixxOES(Androidapi::Jnibridge::TJavaArray__1<int>* m, int offset) = 0 /* overload */;
	virtual void __cdecl glMultMatrixxOES(Androidapi::Jni::Javatypes::_di_JIntBuffer m) = 0 /* overload */;
	virtual void __cdecl glMultiTexCoord4xOES(int target, int s, int t, int r, int q) = 0 ;
	virtual void __cdecl glNormal3xOES(int nx, int ny, int nz) = 0 ;
	virtual void __cdecl glOrthofOES(float left, float right, float bottom, float top, float zNear, float zFar) = 0 ;
	virtual void __cdecl glOrthoxOES(int left, int right, int bottom, int top, int zNear, int zFar) = 0 ;
	virtual void __cdecl glPointParameterxOES(int pname, int param) = 0 ;
	virtual void __cdecl glPointParameterxvOES(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glPointParameterxvOES(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glPointSizexOES(int size) = 0 ;
	virtual void __cdecl glPolygonOffsetxOES(int factor, int units) = 0 ;
	virtual void __cdecl glRenderbufferStorageOES(int target, int internalformat, int width, int height) = 0 ;
	virtual void __cdecl glRotatexOES(int angle, int x, int y, int z) = 0 ;
	virtual void __cdecl glSampleCoveragexOES(int value, bool invert) = 0 ;
	virtual void __cdecl glScalexOES(int x, int y, int z) = 0 ;
	virtual void __cdecl glTexEnvxOES(int target, int pname, int param) = 0 ;
	virtual void __cdecl glTexEnvxvOES(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexEnvxvOES(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexGenfOES(int coord, int pname, float param) = 0 ;
	virtual void __cdecl glTexGenfvOES(int coord, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexGenfvOES(int coord, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexGeniOES(int coord, int pname, int param) = 0 ;
	virtual void __cdecl glTexGenivOES(int coord, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexGenivOES(int coord, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexGenxOES(int coord, int pname, int param) = 0 ;
	virtual void __cdecl glTexGenxvOES(int coord, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexGenxvOES(int coord, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexParameterxOES(int target, int pname, int param) = 0 ;
	virtual void __cdecl glTexParameterxvOES(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexParameterxvOES(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTranslatexOES(int x, int y, int z) = 0 ;
	virtual void __cdecl glWeightPointerOES(int size, int type_, int stride, Androidapi::Jni::Javatypes::_di_JBuffer pointer) = 0 ;
	__property int GL_3DC_XY_AMD = {read=_GetGL_3DC_XY_AMD};
	__property int GL_3DC_X_AMD = {read=_GetGL_3DC_X_AMD};
	__property int GL_ATC_RGBA_EXPLICIT_ALPHA_AMD = {read=_GetGL_ATC_RGBA_EXPLICIT_ALPHA_AMD};
	__property int GL_ATC_RGBA_INTERPOLATED_ALPHA_AMD = {read=_GetGL_ATC_RGBA_INTERPOLATED_ALPHA_AMD};
	__property int GL_ATC_RGB_AMD = {read=_GetGL_ATC_RGB_AMD};
	__property int GL_BGRA = {read=_GetGL_BGRA};
	__property int GL_BLEND_DST_ALPHA_OES = {read=_GetGL_BLEND_DST_ALPHA_OES};
	__property int GL_BLEND_DST_RGB_OES = {read=_GetGL_BLEND_DST_RGB_OES};
	__property int GL_BLEND_EQUATION_ALPHA_OES = {read=_GetGL_BLEND_EQUATION_ALPHA_OES};
	__property int GL_BLEND_EQUATION_OES = {read=_GetGL_BLEND_EQUATION_OES};
	__property int GL_BLEND_EQUATION_RGB_OES = {read=_GetGL_BLEND_EQUATION_RGB_OES};
	__property int GL_BLEND_SRC_ALPHA_OES = {read=_GetGL_BLEND_SRC_ALPHA_OES};
	__property int GL_BLEND_SRC_RGB_OES = {read=_GetGL_BLEND_SRC_RGB_OES};
	__property int GL_BUFFER_ACCESS_OES = {read=_GetGL_BUFFER_ACCESS_OES};
	__property int GL_BUFFER_MAPPED_OES = {read=_GetGL_BUFFER_MAPPED_OES};
	__property int GL_BUFFER_MAP_POINTER_OES = {read=_GetGL_BUFFER_MAP_POINTER_OES};
	__property int GL_COLOR_ATTACHMENT0_OES = {read=_GetGL_COLOR_ATTACHMENT0_OES};
	__property int GL_CURRENT_PALETTE_MATRIX_OES = {read=_GetGL_CURRENT_PALETTE_MATRIX_OES};
	__property int GL_DECR_WRAP_OES = {read=_GetGL_DECR_WRAP_OES};
	__property int GL_DEPTH24_STENCIL8_OES = {read=_GetGL_DEPTH24_STENCIL8_OES};
	__property int GL_DEPTH_ATTACHMENT_OES = {read=_GetGL_DEPTH_ATTACHMENT_OES};
	__property int GL_DEPTH_COMPONENT16_OES = {read=_GetGL_DEPTH_COMPONENT16_OES};
	__property int GL_DEPTH_COMPONENT24_OES = {read=_GetGL_DEPTH_COMPONENT24_OES};
	__property int GL_DEPTH_COMPONENT32_OES = {read=_GetGL_DEPTH_COMPONENT32_OES};
	__property int GL_DEPTH_STENCIL_OES = {read=_GetGL_DEPTH_STENCIL_OES};
	__property int GL_ETC1_RGB8_OES = {read=_GetGL_ETC1_RGB8_OES};
	__property int GL_FIXED_OES = {read=_GetGL_FIXED_OES};
	__property int GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_OES};
	__property int GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_OES};
	__property int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_OES};
	__property int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_OES};
	__property int GL_FRAMEBUFFER_BINDING_OES = {read=_GetGL_FRAMEBUFFER_BINDING_OES};
	__property int GL_FRAMEBUFFER_COMPLETE_OES = {read=_GetGL_FRAMEBUFFER_COMPLETE_OES};
	__property int GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES = {read=_GetGL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_OES};
	__property int GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES = {read=_GetGL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_OES};
	__property int GL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES = {read=_GetGL_FRAMEBUFFER_INCOMPLETE_FORMATS_OES};
	__property int GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES = {read=_GetGL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_OES};
	__property int GL_FRAMEBUFFER_OES = {read=_GetGL_FRAMEBUFFER_OES};
	__property int GL_FRAMEBUFFER_UNSUPPORTED_OES = {read=_GetGL_FRAMEBUFFER_UNSUPPORTED_OES};
	__property int GL_FUNC_ADD_OES = {read=_GetGL_FUNC_ADD_OES};
	__property int GL_FUNC_REVERSE_SUBTRACT_OES = {read=_GetGL_FUNC_REVERSE_SUBTRACT_OES};
	__property int GL_FUNC_SUBTRACT_OES = {read=_GetGL_FUNC_SUBTRACT_OES};
	__property int GL_INCR_WRAP_OES = {read=_GetGL_INCR_WRAP_OES};
	__property int GL_INVALID_FRAMEBUFFER_OPERATION_OES = {read=_GetGL_INVALID_FRAMEBUFFER_OPERATION_OES};
	__property int GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES = {read=_GetGL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES};
	__property int GL_MATRIX_INDEX_ARRAY_OES = {read=_GetGL_MATRIX_INDEX_ARRAY_OES};
	__property int GL_MATRIX_INDEX_ARRAY_POINTER_OES = {read=_GetGL_MATRIX_INDEX_ARRAY_POINTER_OES};
	__property int GL_MATRIX_INDEX_ARRAY_SIZE_OES = {read=_GetGL_MATRIX_INDEX_ARRAY_SIZE_OES};
	__property int GL_MATRIX_INDEX_ARRAY_STRIDE_OES = {read=_GetGL_MATRIX_INDEX_ARRAY_STRIDE_OES};
	__property int GL_MATRIX_INDEX_ARRAY_TYPE_OES = {read=_GetGL_MATRIX_INDEX_ARRAY_TYPE_OES};
	__property int GL_MATRIX_PALETTE_OES = {read=_GetGL_MATRIX_PALETTE_OES};
	__property int GL_MAX_CUBE_MAP_TEXTURE_SIZE_OES = {read=_GetGL_MAX_CUBE_MAP_TEXTURE_SIZE_OES};
	__property int GL_MAX_PALETTE_MATRICES_OES = {read=_GetGL_MAX_PALETTE_MATRICES_OES};
	__property int GL_MAX_RENDERBUFFER_SIZE_OES = {read=_GetGL_MAX_RENDERBUFFER_SIZE_OES};
	__property int GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT = {read=_GetGL_MAX_TEXTURE_MAX_ANISOTROPY_EXT};
	__property int GL_MAX_VERTEX_UNITS_OES = {read=_GetGL_MAX_VERTEX_UNITS_OES};
	__property int GL_MIRRORED_REPEAT_OES = {read=_GetGL_MIRRORED_REPEAT_OES};
	__property int GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES = {read=_GetGL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES};
	__property int GL_NONE_OES = {read=_GetGL_NONE_OES};
	__property int GL_NORMAL_MAP_OES = {read=_GetGL_NORMAL_MAP_OES};
	__property int GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES = {read=_GetGL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES};
	__property int GL_REFLECTION_MAP_OES = {read=_GetGL_REFLECTION_MAP_OES};
	__property int GL_RENDERBUFFER_ALPHA_SIZE_OES = {read=_GetGL_RENDERBUFFER_ALPHA_SIZE_OES};
	__property int GL_RENDERBUFFER_BINDING_OES = {read=_GetGL_RENDERBUFFER_BINDING_OES};
	__property int GL_RENDERBUFFER_BLUE_SIZE_OES = {read=_GetGL_RENDERBUFFER_BLUE_SIZE_OES};
	__property int GL_RENDERBUFFER_DEPTH_SIZE_OES = {read=_GetGL_RENDERBUFFER_DEPTH_SIZE_OES};
	__property int GL_RENDERBUFFER_GREEN_SIZE_OES = {read=_GetGL_RENDERBUFFER_GREEN_SIZE_OES};
	__property int GL_RENDERBUFFER_HEIGHT_OES = {read=_GetGL_RENDERBUFFER_HEIGHT_OES};
	__property int GL_RENDERBUFFER_INTERNAL_FORMAT_OES = {read=_GetGL_RENDERBUFFER_INTERNAL_FORMAT_OES};
	__property int GL_RENDERBUFFER_OES = {read=_GetGL_RENDERBUFFER_OES};
	__property int GL_RENDERBUFFER_RED_SIZE_OES = {read=_GetGL_RENDERBUFFER_RED_SIZE_OES};
	__property int GL_RENDERBUFFER_STENCIL_SIZE_OES = {read=_GetGL_RENDERBUFFER_STENCIL_SIZE_OES};
	__property int GL_RENDERBUFFER_WIDTH_OES = {read=_GetGL_RENDERBUFFER_WIDTH_OES};
	__property int GL_REQUIRED_TEXTURE_IMAGE_UNITS_OES = {read=_GetGL_REQUIRED_TEXTURE_IMAGE_UNITS_OES};
	__property int GL_RGB565_OES = {read=_GetGL_RGB565_OES};
	__property int GL_RGB5_A1_OES = {read=_GetGL_RGB5_A1_OES};
	__property int GL_RGB8_OES = {read=_GetGL_RGB8_OES};
	__property int GL_RGBA4_OES = {read=_GetGL_RGBA4_OES};
	__property int GL_RGBA8_OES = {read=_GetGL_RGBA8_OES};
	__property int GL_SAMPLER_EXTERNAL_OES = {read=_GetGL_SAMPLER_EXTERNAL_OES};
	__property int GL_STENCIL_ATTACHMENT_OES = {read=_GetGL_STENCIL_ATTACHMENT_OES};
	__property int GL_STENCIL_INDEX1_OES = {read=_GetGL_STENCIL_INDEX1_OES};
	__property int GL_STENCIL_INDEX4_OES = {read=_GetGL_STENCIL_INDEX4_OES};
	__property int GL_STENCIL_INDEX8_OES = {read=_GetGL_STENCIL_INDEX8_OES};
	__property int GL_TEXTURE_BINDING_CUBE_MAP_OES = {read=_GetGL_TEXTURE_BINDING_CUBE_MAP_OES};
	__property int GL_TEXTURE_BINDING_EXTERNAL_OES = {read=_GetGL_TEXTURE_BINDING_EXTERNAL_OES};
	__property int GL_TEXTURE_CROP_RECT_OES = {read=_GetGL_TEXTURE_CROP_RECT_OES};
	__property int GL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES = {read=_GetGL_TEXTURE_CUBE_MAP_NEGATIVE_X_OES};
	__property int GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES = {read=_GetGL_TEXTURE_CUBE_MAP_NEGATIVE_Y_OES};
	__property int GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES = {read=_GetGL_TEXTURE_CUBE_MAP_NEGATIVE_Z_OES};
	__property int GL_TEXTURE_CUBE_MAP_OES = {read=_GetGL_TEXTURE_CUBE_MAP_OES};
	__property int GL_TEXTURE_CUBE_MAP_POSITIVE_X_OES = {read=_GetGL_TEXTURE_CUBE_MAP_POSITIVE_X_OES};
	__property int GL_TEXTURE_CUBE_MAP_POSITIVE_Y_OES = {read=_GetGL_TEXTURE_CUBE_MAP_POSITIVE_Y_OES};
	__property int GL_TEXTURE_CUBE_MAP_POSITIVE_Z_OES = {read=_GetGL_TEXTURE_CUBE_MAP_POSITIVE_Z_OES};
	__property int GL_TEXTURE_EXTERNAL_OES = {read=_GetGL_TEXTURE_EXTERNAL_OES};
	__property int GL_TEXTURE_GEN_MODE_OES = {read=_GetGL_TEXTURE_GEN_MODE_OES};
	__property int GL_TEXTURE_GEN_STR_OES = {read=_GetGL_TEXTURE_GEN_STR_OES};
	__property int GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES = {read=_GetGL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES};
	__property int GL_TEXTURE_MAX_ANISOTROPY_EXT = {read=_GetGL_TEXTURE_MAX_ANISOTROPY_EXT};
	__property int GL_UNSIGNED_INT_24_8_OES = {read=_GetGL_UNSIGNED_INT_24_8_OES};
	__property int GL_WEIGHT_ARRAY_BUFFER_BINDING_OES = {read=_GetGL_WEIGHT_ARRAY_BUFFER_BINDING_OES};
	__property int GL_WEIGHT_ARRAY_OES = {read=_GetGL_WEIGHT_ARRAY_OES};
	__property int GL_WEIGHT_ARRAY_POINTER_OES = {read=_GetGL_WEIGHT_ARRAY_POINTER_OES};
	__property int GL_WEIGHT_ARRAY_SIZE_OES = {read=_GetGL_WEIGHT_ARRAY_SIZE_OES};
	__property int GL_WEIGHT_ARRAY_STRIDE_OES = {read=_GetGL_WEIGHT_ARRAY_STRIDE_OES};
	__property int GL_WEIGHT_ARRAY_TYPE_OES = {read=_GetGL_WEIGHT_ARRAY_TYPE_OES};
	__property int GL_WRITE_ONLY_OES = {read=_GetGL_WRITE_ONLY_OES};
};

__interface  INTERFACE_UUID("{82AC1A8D-82F5-4A70-93C3-A55C1CFA7E95}") JGLES11Ext  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLES11Ext : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES11ExtClass,_di_JGLES11Ext>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES11ExtClass,_di_JGLES11Ext> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLES11Ext() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES11ExtClass,_di_JGLES11Ext>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLES11Ext() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C0AFF4E3-5F31-4377-9F58-C376F76D1CF4}") JGLES20Class  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetGL_ACTIVE_ATTRIBUTES() = 0 ;
	virtual int __cdecl _GetGL_ACTIVE_ATTRIBUTE_MAX_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_ACTIVE_TEXTURE() = 0 ;
	virtual int __cdecl _GetGL_ACTIVE_UNIFORMS() = 0 ;
	virtual int __cdecl _GetGL_ACTIVE_UNIFORM_MAX_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_ALIASED_LINE_WIDTH_RANGE() = 0 ;
	virtual int __cdecl _GetGL_ALIASED_POINT_SIZE_RANGE() = 0 ;
	virtual int __cdecl _GetGL_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_ALPHA_BITS() = 0 ;
	virtual int __cdecl _GetGL_ALWAYS() = 0 ;
	virtual int __cdecl _GetGL_ARRAY_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_ARRAY_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_ATTACHED_SHADERS() = 0 ;
	virtual int __cdecl _GetGL_BACK() = 0 ;
	virtual int __cdecl _GetGL_BLEND() = 0 ;
	virtual int __cdecl _GetGL_BLEND_COLOR() = 0 ;
	virtual int __cdecl _GetGL_BLEND_DST_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_BLEND_DST_RGB() = 0 ;
	virtual int __cdecl _GetGL_BLEND_EQUATION() = 0 ;
	virtual int __cdecl _GetGL_BLEND_EQUATION_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_BLEND_EQUATION_RGB() = 0 ;
	virtual int __cdecl _GetGL_BLEND_SRC_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_BLEND_SRC_RGB() = 0 ;
	virtual int __cdecl _GetGL_BLUE_BITS() = 0 ;
	virtual int __cdecl _GetGL_BOOL() = 0 ;
	virtual int __cdecl _GetGL_BOOL_VEC2() = 0 ;
	virtual int __cdecl _GetGL_BOOL_VEC3() = 0 ;
	virtual int __cdecl _GetGL_BOOL_VEC4() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_SIZE() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_USAGE() = 0 ;
	virtual int __cdecl _GetGL_BYTE() = 0 ;
	virtual int __cdecl _GetGL_CCW() = 0 ;
	virtual int __cdecl _GetGL_CLAMP_TO_EDGE() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT0() = 0 ;
	virtual int __cdecl _GetGL_COLOR_BUFFER_BIT() = 0 ;
	virtual int __cdecl _GetGL_COLOR_CLEAR_VALUE() = 0 ;
	virtual int __cdecl _GetGL_COLOR_WRITEMASK() = 0 ;
	virtual int __cdecl _GetGL_COMPILE_STATUS() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_TEXTURE_FORMATS() = 0 ;
	virtual int __cdecl _GetGL_CONSTANT_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_CONSTANT_COLOR() = 0 ;
	virtual int __cdecl _GetGL_CULL_FACE() = 0 ;
	virtual int __cdecl _GetGL_CULL_FACE_MODE() = 0 ;
	virtual int __cdecl _GetGL_CURRENT_PROGRAM() = 0 ;
	virtual int __cdecl _GetGL_CURRENT_VERTEX_ATTRIB() = 0 ;
	virtual int __cdecl _GetGL_CW() = 0 ;
	virtual int __cdecl _GetGL_DECR() = 0 ;
	virtual int __cdecl _GetGL_DECR_WRAP() = 0 ;
	virtual int __cdecl _GetGL_DELETE_STATUS() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_ATTACHMENT() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_BITS() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_BUFFER_BIT() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_CLEAR_VALUE() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_COMPONENT() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_COMPONENT16() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_FUNC() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_RANGE() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_TEST() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_WRITEMASK() = 0 ;
	virtual int __cdecl _GetGL_DITHER() = 0 ;
	virtual int __cdecl _GetGL_DONT_CARE() = 0 ;
	virtual int __cdecl _GetGL_DST_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_DST_COLOR() = 0 ;
	virtual int __cdecl _GetGL_DYNAMIC_DRAW() = 0 ;
	virtual int __cdecl _GetGL_ELEMENT_ARRAY_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_ELEMENT_ARRAY_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_EQUAL() = 0 ;
	virtual int __cdecl _GetGL_EXTENSIONS() = 0 ;
	virtual int __cdecl _GetGL_FALSE() = 0 ;
	virtual int __cdecl _GetGL_FASTEST() = 0 ;
	virtual int __cdecl _GetGL_FIXED() = 0 ;
	virtual int __cdecl _GetGL_FLOAT() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_MAT2() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_MAT3() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_MAT4() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_VEC2() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_VEC3() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_VEC4() = 0 ;
	virtual int __cdecl _GetGL_FRAGMENT_SHADER() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_COMPLETE() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_UNSUPPORTED() = 0 ;
	virtual int __cdecl _GetGL_FRONT() = 0 ;
	virtual int __cdecl _GetGL_FRONT_AND_BACK() = 0 ;
	virtual int __cdecl _GetGL_FRONT_FACE() = 0 ;
	virtual int __cdecl _GetGL_FUNC_ADD() = 0 ;
	virtual int __cdecl _GetGL_FUNC_REVERSE_SUBTRACT() = 0 ;
	virtual int __cdecl _GetGL_FUNC_SUBTRACT() = 0 ;
	virtual int __cdecl _GetGL_GENERATE_MIPMAP_HINT() = 0 ;
	virtual int __cdecl _GetGL_GEQUAL() = 0 ;
	virtual int __cdecl _GetGL_GREATER() = 0 ;
	virtual int __cdecl _GetGL_GREEN_BITS() = 0 ;
	virtual int __cdecl _GetGL_HIGH_FLOAT() = 0 ;
	virtual int __cdecl _GetGL_HIGH_INT() = 0 ;
	virtual int __cdecl _GetGL_IMPLEMENTATION_COLOR_READ_FORMAT() = 0 ;
	virtual int __cdecl _GetGL_IMPLEMENTATION_COLOR_READ_TYPE() = 0 ;
	virtual int __cdecl _GetGL_INCR() = 0 ;
	virtual int __cdecl _GetGL_INCR_WRAP() = 0 ;
	virtual int __cdecl _GetGL_INFO_LOG_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_INT() = 0 ;
	virtual int __cdecl _GetGL_INT_VEC2() = 0 ;
	virtual int __cdecl _GetGL_INT_VEC3() = 0 ;
	virtual int __cdecl _GetGL_INT_VEC4() = 0 ;
	virtual int __cdecl _GetGL_INVALID_ENUM() = 0 ;
	virtual int __cdecl _GetGL_INVALID_FRAMEBUFFER_OPERATION() = 0 ;
	virtual int __cdecl _GetGL_INVALID_OPERATION() = 0 ;
	virtual int __cdecl _GetGL_INVALID_VALUE() = 0 ;
	virtual int __cdecl _GetGL_INVERT() = 0 ;
	virtual int __cdecl _GetGL_KEEP() = 0 ;
	virtual int __cdecl _GetGL_LEQUAL() = 0 ;
	virtual int __cdecl _GetGL_LESS() = 0 ;
	virtual int __cdecl _GetGL_LINEAR() = 0 ;
	virtual int __cdecl _GetGL_LINEAR_MIPMAP_LINEAR() = 0 ;
	virtual int __cdecl _GetGL_LINEAR_MIPMAP_NEAREST() = 0 ;
	virtual int __cdecl _GetGL_LINES() = 0 ;
	virtual int __cdecl _GetGL_LINE_LOOP() = 0 ;
	virtual int __cdecl _GetGL_LINE_STRIP() = 0 ;
	virtual int __cdecl _GetGL_LINE_WIDTH() = 0 ;
	virtual int __cdecl _GetGL_LINK_STATUS() = 0 ;
	virtual int __cdecl _GetGL_LOW_FLOAT() = 0 ;
	virtual int __cdecl _GetGL_LOW_INT() = 0 ;
	virtual int __cdecl _GetGL_LUMINANCE() = 0 ;
	virtual int __cdecl _GetGL_LUMINANCE_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_TEXTURE_IMAGE_UNITS() = 0 ;
	virtual int __cdecl _GetGL_MAX_CUBE_MAP_TEXTURE_SIZE() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAGMENT_UNIFORM_VECTORS() = 0 ;
	virtual int __cdecl _GetGL_MAX_RENDERBUFFER_SIZE() = 0 ;
	virtual int __cdecl _GetGL_MAX_TEXTURE_IMAGE_UNITS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TEXTURE_SIZE() = 0 ;
	virtual int __cdecl _GetGL_MAX_VARYING_VECTORS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_ATTRIBS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_TEXTURE_IMAGE_UNITS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_UNIFORM_VECTORS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VIEWPORT_DIMS() = 0 ;
	virtual int __cdecl _GetGL_MEDIUM_FLOAT() = 0 ;
	virtual int __cdecl _GetGL_MEDIUM_INT() = 0 ;
	virtual int __cdecl _GetGL_MIRRORED_REPEAT() = 0 ;
	virtual int __cdecl _GetGL_NEAREST() = 0 ;
	virtual int __cdecl _GetGL_NEAREST_MIPMAP_LINEAR() = 0 ;
	virtual int __cdecl _GetGL_NEAREST_MIPMAP_NEAREST() = 0 ;
	virtual int __cdecl _GetGL_NEVER() = 0 ;
	virtual int __cdecl _GetGL_NICEST() = 0 ;
	virtual int __cdecl _GetGL_NONE() = 0 ;
	virtual int __cdecl _GetGL_NOTEQUAL() = 0 ;
	virtual int __cdecl _GetGL_NO_ERROR() = 0 ;
	virtual int __cdecl _GetGL_NUM_COMPRESSED_TEXTURE_FORMATS() = 0 ;
	virtual int __cdecl _GetGL_NUM_SHADER_BINARY_FORMATS() = 0 ;
	virtual int __cdecl _GetGL_ONE() = 0 ;
	virtual int __cdecl _GetGL_ONE_MINUS_CONSTANT_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_ONE_MINUS_CONSTANT_COLOR() = 0 ;
	virtual int __cdecl _GetGL_ONE_MINUS_DST_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_ONE_MINUS_DST_COLOR() = 0 ;
	virtual int __cdecl _GetGL_ONE_MINUS_SRC_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_ONE_MINUS_SRC_COLOR() = 0 ;
	virtual int __cdecl _GetGL_OUT_OF_MEMORY() = 0 ;
	virtual int __cdecl _GetGL_PACK_ALIGNMENT() = 0 ;
	virtual int __cdecl _GetGL_POINTS() = 0 ;
	virtual int __cdecl _GetGL_POLYGON_OFFSET_FACTOR() = 0 ;
	virtual int __cdecl _GetGL_POLYGON_OFFSET_FILL() = 0 ;
	virtual int __cdecl _GetGL_POLYGON_OFFSET_UNITS() = 0 ;
	virtual int __cdecl _GetGL_RED_BITS() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_ALPHA_SIZE() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_BLUE_SIZE() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_DEPTH_SIZE() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_GREEN_SIZE() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_HEIGHT() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_INTERNAL_FORMAT() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_RED_SIZE() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_STENCIL_SIZE() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_WIDTH() = 0 ;
	virtual int __cdecl _GetGL_RENDERER() = 0 ;
	virtual int __cdecl _GetGL_REPEAT() = 0 ;
	virtual int __cdecl _GetGL_REPLACE() = 0 ;
	virtual int __cdecl _GetGL_RGB() = 0 ;
	virtual int __cdecl _GetGL_RGB565() = 0 ;
	virtual int __cdecl _GetGL_RGB5_A1() = 0 ;
	virtual int __cdecl _GetGL_RGBA() = 0 ;
	virtual int __cdecl _GetGL_RGBA4() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_2D() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_CUBE() = 0 ;
	virtual int __cdecl _GetGL_SAMPLES() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_ALPHA_TO_COVERAGE() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_BUFFERS() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_COVERAGE() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_COVERAGE_INVERT() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_COVERAGE_VALUE() = 0 ;
	virtual int __cdecl _GetGL_SCISSOR_BOX() = 0 ;
	virtual int __cdecl _GetGL_SCISSOR_TEST() = 0 ;
	virtual int __cdecl _GetGL_SHADER_BINARY_FORMATS() = 0 ;
	virtual int __cdecl _GetGL_SHADER_COMPILER() = 0 ;
	virtual int __cdecl _GetGL_SHADER_SOURCE_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_SHADER_TYPE() = 0 ;
	virtual int __cdecl _GetGL_SHADING_LANGUAGE_VERSION() = 0 ;
	virtual int __cdecl _GetGL_SHORT() = 0 ;
	virtual int __cdecl _GetGL_SRC_ALPHA() = 0 ;
	virtual int __cdecl _GetGL_SRC_ALPHA_SATURATE() = 0 ;
	virtual int __cdecl _GetGL_SRC_COLOR() = 0 ;
	virtual int __cdecl _GetGL_STATIC_DRAW() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_ATTACHMENT() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_BACK_FAIL() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_BACK_FUNC() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_BACK_PASS_DEPTH_FAIL() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_BACK_PASS_DEPTH_PASS() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_BACK_REF() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_BACK_VALUE_MASK() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_BACK_WRITEMASK() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_BITS() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_BUFFER_BIT() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_CLEAR_VALUE() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_FAIL() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_FUNC() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_INDEX() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_INDEX8() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_PASS_DEPTH_FAIL() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_PASS_DEPTH_PASS() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_REF() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_TEST() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_VALUE_MASK() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_WRITEMASK() = 0 ;
	virtual int __cdecl _GetGL_STREAM_DRAW() = 0 ;
	virtual int __cdecl _GetGL_SUBPIXEL_BITS() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE0() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE1() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE10() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE11() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE12() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE13() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE14() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE15() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE16() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE17() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE18() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE19() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE2() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE20() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE21() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE22() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE23() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE24() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE25() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE26() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE27() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE28() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE29() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE3() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE30() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE31() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE4() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE5() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE6() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE7() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE8() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE9() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_2D() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_2D() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_CUBE_MAP() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_NEGATIVE_X() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_NEGATIVE_Y() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_NEGATIVE_Z() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_POSITIVE_X() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_POSITIVE_Y() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_POSITIVE_Z() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_MAG_FILTER() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_MIN_FILTER() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_WRAP_S() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_WRAP_T() = 0 ;
	virtual int __cdecl _GetGL_TRIANGLES() = 0 ;
	virtual int __cdecl _GetGL_TRIANGLE_FAN() = 0 ;
	virtual int __cdecl _GetGL_TRIANGLE_STRIP() = 0 ;
	virtual int __cdecl _GetGL_TRUE() = 0 ;
	virtual int __cdecl _GetGL_UNPACK_ALIGNMENT() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_BYTE() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_SHORT() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_SHORT_4_4_4_4() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_SHORT_5_5_5_1() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_SHORT_5_6_5() = 0 ;
	virtual int __cdecl _GetGL_VALIDATE_STATUS() = 0 ;
	virtual int __cdecl _GetGL_VENDOR() = 0 ;
	virtual int __cdecl _GetGL_VERSION() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_ARRAY_ENABLED() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_ARRAY_NORMALIZED() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_ARRAY_POINTER() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_ARRAY_SIZE() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_ARRAY_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_ARRAY_TYPE() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_SHADER() = 0 ;
	virtual int __cdecl _GetGL_VIEWPORT() = 0 ;
	virtual int __cdecl _GetGL_ZERO() = 0 ;
	HIDESBASE virtual _di_JGLES20 __cdecl init() = 0 ;
	virtual void __cdecl glActiveTexture(int texture) = 0 ;
	virtual void __cdecl glAttachShader(int program_, int shader) = 0 ;
	virtual void __cdecl glBindAttribLocation(int program_, int index, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual void __cdecl glBindBuffer(int target, int buffer) = 0 ;
	virtual void __cdecl glBindFramebuffer(int target, int framebuffer) = 0 ;
	virtual void __cdecl glBindRenderbuffer(int target, int renderbuffer) = 0 ;
	virtual void __cdecl glBindTexture(int target, int texture) = 0 ;
	virtual void __cdecl glBlendColor(float red, float green, float blue, float alpha) = 0 ;
	virtual void __cdecl glBlendEquation(int mode) = 0 ;
	virtual void __cdecl glBlendEquationSeparate(int modeRGB, int modeAlpha) = 0 ;
	virtual void __cdecl glBlendFunc(int sfactor, int dfactor) = 0 ;
	virtual void __cdecl glBlendFuncSeparate(int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) = 0 ;
	virtual void __cdecl glBufferData(int target, int size, Androidapi::Jni::Javatypes::_di_JBuffer data, int usage) = 0 ;
	virtual void __cdecl glBufferSubData(int target, int offset, int size, Androidapi::Jni::Javatypes::_di_JBuffer data) = 0 ;
	virtual int __cdecl glCheckFramebufferStatus(int target) = 0 ;
	virtual void __cdecl glClear(int mask) = 0 ;
	virtual void __cdecl glClearColor(float red, float green, float blue, float alpha) = 0 ;
	virtual void __cdecl glClearDepthf(float depth) = 0 ;
	virtual void __cdecl glClearStencil(int s) = 0 ;
	virtual void __cdecl glColorMask(bool red, bool green, bool blue, bool alpha) = 0 ;
	virtual void __cdecl glCompileShader(int shader) = 0 ;
	virtual void __cdecl glCompressedTexImage2D(int target, int level, int internalformat, int width, int height, int border, int imageSize, Androidapi::Jni::Javatypes::_di_JBuffer data) = 0 ;
	virtual void __cdecl glCompressedTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, Androidapi::Jni::Javatypes::_di_JBuffer data) = 0 ;
	virtual void __cdecl glCopyTexImage2D(int target, int level, int internalformat, int x, int y, int width, int height, int border) = 0 ;
	virtual void __cdecl glCopyTexSubImage2D(int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) = 0 ;
	virtual int __cdecl glCreateProgram() = 0 ;
	virtual int __cdecl glCreateShader(int type_) = 0 ;
	virtual void __cdecl glCullFace(int mode) = 0 ;
	virtual void __cdecl glDeleteBuffers(int n, Androidapi::Jnibridge::TJavaArray__1<int>* buffers, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteBuffers(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer buffers) = 0 /* overload */;
	virtual void __cdecl glDeleteFramebuffers(int n, Androidapi::Jnibridge::TJavaArray__1<int>* framebuffers, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteFramebuffers(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer framebuffers) = 0 /* overload */;
	virtual void __cdecl glDeleteProgram(int program_) = 0 ;
	virtual void __cdecl glDeleteRenderbuffers(int n, Androidapi::Jnibridge::TJavaArray__1<int>* renderbuffers, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteRenderbuffers(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer renderbuffers) = 0 /* overload */;
	virtual void __cdecl glDeleteShader(int shader) = 0 ;
	virtual void __cdecl glDeleteTextures(int n, Androidapi::Jnibridge::TJavaArray__1<int>* textures, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteTextures(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer textures) = 0 /* overload */;
	virtual void __cdecl glDepthFunc(int func) = 0 ;
	virtual void __cdecl glDepthMask(bool flag) = 0 ;
	virtual void __cdecl glDepthRangef(float zNear, float zFar) = 0 ;
	virtual void __cdecl glDetachShader(int program_, int shader) = 0 ;
	virtual void __cdecl glDisable(int cap) = 0 ;
	virtual void __cdecl glDisableVertexAttribArray(int index) = 0 ;
	virtual void __cdecl glDrawArrays(int mode, int first, int count) = 0 ;
	virtual void __cdecl glDrawElements(int mode, int count, int type_, int offset) = 0 /* overload */;
	virtual void __cdecl glDrawElements(int mode, int count, int type_, Androidapi::Jni::Javatypes::_di_JBuffer indices) = 0 /* overload */;
	virtual void __cdecl glEnable(int cap) = 0 ;
	virtual void __cdecl glEnableVertexAttribArray(int index) = 0 ;
	virtual void __cdecl glFinish() = 0 ;
	virtual void __cdecl glFlush() = 0 ;
	virtual void __cdecl glFramebufferRenderbuffer(int target, int attachment, int renderbuffertarget, int renderbuffer) = 0 ;
	virtual void __cdecl glFramebufferTexture2D(int target, int attachment, int textarget, int texture, int level) = 0 ;
	virtual void __cdecl glFrontFace(int mode) = 0 ;
	virtual void __cdecl glGenBuffers(int n, Androidapi::Jnibridge::TJavaArray__1<int>* buffers, int offset) = 0 /* overload */;
	virtual void __cdecl glGenBuffers(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer buffers) = 0 /* overload */;
	virtual void __cdecl glGenFramebuffers(int n, Androidapi::Jnibridge::TJavaArray__1<int>* framebuffers, int offset) = 0 /* overload */;
	virtual void __cdecl glGenFramebuffers(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer framebuffers) = 0 /* overload */;
	virtual void __cdecl glGenRenderbuffers(int n, Androidapi::Jnibridge::TJavaArray__1<int>* renderbuffers, int offset) = 0 /* overload */;
	virtual void __cdecl glGenRenderbuffers(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer renderbuffers) = 0 /* overload */;
	virtual void __cdecl glGenTextures(int n, Androidapi::Jnibridge::TJavaArray__1<int>* textures, int offset) = 0 /* overload */;
	virtual void __cdecl glGenTextures(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer textures) = 0 /* overload */;
	virtual void __cdecl glGenerateMipmap(int target) = 0 ;
	virtual void __cdecl glGetActiveAttrib(int program_, int index, int bufsize, Androidapi::Jnibridge::TJavaArray__1<int>* length, int lengthOffset, Androidapi::Jnibridge::TJavaArray__1<int>* size, int sizeOffset, Androidapi::Jnibridge::TJavaArray__1<int>* type_, int typeOffset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* name, int nameOffset) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetActiveAttrib(int program_, int index, Androidapi::Jnibridge::TJavaArray__1<int>* size, int sizeOffset, Androidapi::Jnibridge::TJavaArray__1<int>* type_, int typeOffset) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetActiveAttrib(int program_, int index, Androidapi::Jni::Javatypes::_di_JIntBuffer size, Androidapi::Jni::Javatypes::_di_JIntBuffer type_) = 0 /* overload */;
	virtual void __cdecl glGetActiveUniform(int program_, int index, int bufsize, Androidapi::Jnibridge::TJavaArray__1<int>* length, int lengthOffset, Androidapi::Jnibridge::TJavaArray__1<int>* size, int sizeOffset, Androidapi::Jnibridge::TJavaArray__1<int>* type_, int typeOffset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* name, int nameOffset) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetActiveUniform(int program_, int index, Androidapi::Jnibridge::TJavaArray__1<int>* size, int sizeOffset, Androidapi::Jnibridge::TJavaArray__1<int>* type_, int typeOffset) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetActiveUniform(int program_, int index, Androidapi::Jni::Javatypes::_di_JIntBuffer size, Androidapi::Jni::Javatypes::_di_JIntBuffer type_) = 0 /* overload */;
	virtual void __cdecl glGetAttachedShaders(int program_, int maxcount, Androidapi::Jnibridge::TJavaArray__1<int>* count, int countOffset, Androidapi::Jnibridge::TJavaArray__1<int>* shaders, int shadersOffset) = 0 /* overload */;
	virtual void __cdecl glGetAttachedShaders(int program_, int maxcount, Androidapi::Jni::Javatypes::_di_JIntBuffer count, Androidapi::Jni::Javatypes::_di_JIntBuffer shaders) = 0 /* overload */;
	virtual int __cdecl glGetAttribLocation(int program_, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual void __cdecl glGetBooleanv(int pname, Androidapi::Jnibridge::TJavaArray__1<bool>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetBooleanv(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetBufferParameteriv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetBufferParameteriv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual int __cdecl glGetError() = 0 ;
	virtual void __cdecl glGetFloatv(int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetFloatv(int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetFramebufferAttachmentParameteriv(int target, int attachment, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetFramebufferAttachmentParameteriv(int target, int attachment, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetIntegerv(int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetIntegerv(int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetProgramInfoLog(int program_) = 0 ;
	virtual void __cdecl glGetProgramiv(int program_, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetProgramiv(int program_, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetRenderbufferParameteriv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetRenderbufferParameteriv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetShaderInfoLog(int shader) = 0 ;
	virtual void __cdecl glGetShaderPrecisionFormat(int shadertype, int precisiontype, Androidapi::Jnibridge::TJavaArray__1<int>* range, int rangeOffset, Androidapi::Jnibridge::TJavaArray__1<int>* precision, int precisionOffset) = 0 /* overload */;
	virtual void __cdecl glGetShaderPrecisionFormat(int shadertype, int precisiontype, Androidapi::Jni::Javatypes::_di_JIntBuffer range, Androidapi::Jni::Javatypes::_di_JIntBuffer precision) = 0 /* overload */;
	virtual void __cdecl glGetShaderSource(int shader, int bufsize, Androidapi::Jnibridge::TJavaArray__1<int>* length, int lengthOffset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* source, int sourceOffset) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetShaderSource(int shader) = 0 /* overload */;
	virtual void __cdecl glGetShaderiv(int shader, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetShaderiv(int shader, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetString(int name) = 0 ;
	virtual void __cdecl glGetTexParameterfv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterfv(int target, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexParameteriv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexParameteriv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual int __cdecl glGetUniformLocation(int program_, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual void __cdecl glGetUniformfv(int program_, int location, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetUniformfv(int program_, int location, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetUniformiv(int program_, int location, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetUniformiv(int program_, int location, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetVertexAttribfv(int index, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetVertexAttribfv(int index, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetVertexAttribiv(int index, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetVertexAttribiv(int index, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glHint(int target, int mode) = 0 ;
	virtual bool __cdecl glIsBuffer(int buffer) = 0 ;
	virtual bool __cdecl glIsEnabled(int cap) = 0 ;
	virtual bool __cdecl glIsFramebuffer(int framebuffer) = 0 ;
	virtual bool __cdecl glIsProgram(int program_) = 0 ;
	virtual bool __cdecl glIsRenderbuffer(int renderbuffer) = 0 ;
	virtual bool __cdecl glIsShader(int shader) = 0 ;
	virtual bool __cdecl glIsTexture(int texture) = 0 ;
	virtual void __cdecl glLineWidth(float width) = 0 ;
	virtual void __cdecl glLinkProgram(int program_) = 0 ;
	virtual void __cdecl glPixelStorei(int pname, int param) = 0 ;
	virtual void __cdecl glPolygonOffset(float factor, float units) = 0 ;
	virtual void __cdecl glReadPixels(int x, int y, int width, int height, int format, int type_, Androidapi::Jni::Javatypes::_di_JBuffer pixels) = 0 ;
	virtual void __cdecl glReleaseShaderCompiler() = 0 ;
	virtual void __cdecl glRenderbufferStorage(int target, int internalformat, int width, int height) = 0 ;
	virtual void __cdecl glSampleCoverage(float value, bool invert) = 0 ;
	virtual void __cdecl glScissor(int x, int y, int width, int height) = 0 ;
	virtual void __cdecl glShaderBinary(int n, Androidapi::Jnibridge::TJavaArray__1<int>* shaders, int offset, int binaryformat, Androidapi::Jni::Javatypes::_di_JBuffer binary, int length) = 0 /* overload */;
	virtual void __cdecl glShaderBinary(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer shaders, int binaryformat, Androidapi::Jni::Javatypes::_di_JBuffer binary, int length) = 0 /* overload */;
	virtual void __cdecl glShaderSource(int shader, Androidapi::Jni::Javatypes::_di_JString string_) = 0 ;
	virtual void __cdecl glStencilFunc(int func, int ref, int mask) = 0 ;
	virtual void __cdecl glStencilFuncSeparate(int face, int func, int ref, int mask) = 0 ;
	virtual void __cdecl glStencilMask(int mask) = 0 ;
	virtual void __cdecl glStencilMaskSeparate(int face, int mask) = 0 ;
	virtual void __cdecl glStencilOp(int fail, int zfail, int zpass) = 0 ;
	virtual void __cdecl glStencilOpSeparate(int face, int fail, int zfail, int zpass) = 0 ;
	virtual void __cdecl glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type_, Androidapi::Jni::Javatypes::_di_JBuffer pixels) = 0 ;
	virtual void __cdecl glTexParameterf(int target, int pname, float param) = 0 ;
	virtual void __cdecl glTexParameterfv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexParameterfv(int target, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexParameteri(int target, int pname, int param) = 0 ;
	virtual void __cdecl glTexParameteriv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexParameteriv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexSubImage2D(int target, int level, int xoffset, int yoffset, int width, int height, int format, int type_, Androidapi::Jni::Javatypes::_di_JBuffer pixels) = 0 ;
	virtual void __cdecl glUniform1f(int location, float x) = 0 ;
	virtual void __cdecl glUniform1fv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<float>* v, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform1fv(int location, int count, Androidapi::Jni::Javatypes::_di_JFloatBuffer v) = 0 /* overload */;
	virtual void __cdecl glUniform1i(int location, int x) = 0 ;
	virtual void __cdecl glUniform1iv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* v, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform1iv(int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer v) = 0 /* overload */;
	virtual void __cdecl glUniform2f(int location, float x, float y) = 0 ;
	virtual void __cdecl glUniform2fv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<float>* v, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform2fv(int location, int count, Androidapi::Jni::Javatypes::_di_JFloatBuffer v) = 0 /* overload */;
	virtual void __cdecl glUniform2i(int location, int x, int y) = 0 ;
	virtual void __cdecl glUniform2iv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* v, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform2iv(int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer v) = 0 /* overload */;
	virtual void __cdecl glUniform3f(int location, float x, float y, float z) = 0 ;
	virtual void __cdecl glUniform3fv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<float>* v, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform3fv(int location, int count, Androidapi::Jni::Javatypes::_di_JFloatBuffer v) = 0 /* overload */;
	virtual void __cdecl glUniform3i(int location, int x, int y, int z) = 0 ;
	virtual void __cdecl glUniform3iv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* v, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform3iv(int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer v) = 0 /* overload */;
	virtual void __cdecl glUniform4f(int location, float x, float y, float z, float w) = 0 ;
	virtual void __cdecl glUniform4fv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<float>* v, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform4fv(int location, int count, Androidapi::Jni::Javatypes::_di_JFloatBuffer v) = 0 /* overload */;
	virtual void __cdecl glUniform4i(int location, int x, int y, int z, int w) = 0 ;
	virtual void __cdecl glUniform4iv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* v, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform4iv(int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer v) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix2fv(int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix2fv(int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix3fv(int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix3fv(int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix4fv(int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix4fv(int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glUseProgram(int program_) = 0 ;
	virtual void __cdecl glValidateProgram(int program_) = 0 ;
	virtual void __cdecl glVertexAttrib1f(int indx, float x) = 0 ;
	virtual void __cdecl glVertexAttrib1fv(int indx, Androidapi::Jnibridge::TJavaArray__1<float>* values, int offset) = 0 /* overload */;
	virtual void __cdecl glVertexAttrib1fv(int indx, Androidapi::Jni::Javatypes::_di_JFloatBuffer values) = 0 /* overload */;
	virtual void __cdecl glVertexAttrib2f(int indx, float x, float y) = 0 ;
	virtual void __cdecl glVertexAttrib2fv(int indx, Androidapi::Jnibridge::TJavaArray__1<float>* values, int offset) = 0 /* overload */;
	virtual void __cdecl glVertexAttrib2fv(int indx, Androidapi::Jni::Javatypes::_di_JFloatBuffer values) = 0 /* overload */;
	virtual void __cdecl glVertexAttrib3f(int indx, float x, float y, float z) = 0 ;
	virtual void __cdecl glVertexAttrib3fv(int indx, Androidapi::Jnibridge::TJavaArray__1<float>* values, int offset) = 0 /* overload */;
	virtual void __cdecl glVertexAttrib3fv(int indx, Androidapi::Jni::Javatypes::_di_JFloatBuffer values) = 0 /* overload */;
	virtual void __cdecl glVertexAttrib4f(int indx, float x, float y, float z, float w) = 0 ;
	virtual void __cdecl glVertexAttrib4fv(int indx, Androidapi::Jnibridge::TJavaArray__1<float>* values, int offset) = 0 /* overload */;
	virtual void __cdecl glVertexAttrib4fv(int indx, Androidapi::Jni::Javatypes::_di_JFloatBuffer values) = 0 /* overload */;
	virtual void __cdecl glVertexAttribPointer(int indx, int size, int type_, bool normalized, int stride, int offset) = 0 /* overload */;
	virtual void __cdecl glVertexAttribPointer(int indx, int size, int type_, bool normalized, int stride, Androidapi::Jni::Javatypes::_di_JBuffer ptr) = 0 /* overload */;
	virtual void __cdecl glViewport(int x, int y, int width, int height) = 0 ;
	__property int GL_ACTIVE_ATTRIBUTES = {read=_GetGL_ACTIVE_ATTRIBUTES};
	__property int GL_ACTIVE_ATTRIBUTE_MAX_LENGTH = {read=_GetGL_ACTIVE_ATTRIBUTE_MAX_LENGTH};
	__property int GL_ACTIVE_TEXTURE = {read=_GetGL_ACTIVE_TEXTURE};
	__property int GL_ACTIVE_UNIFORMS = {read=_GetGL_ACTIVE_UNIFORMS};
	__property int GL_ACTIVE_UNIFORM_MAX_LENGTH = {read=_GetGL_ACTIVE_UNIFORM_MAX_LENGTH};
	__property int GL_ALIASED_LINE_WIDTH_RANGE = {read=_GetGL_ALIASED_LINE_WIDTH_RANGE};
	__property int GL_ALIASED_POINT_SIZE_RANGE = {read=_GetGL_ALIASED_POINT_SIZE_RANGE};
	__property int GL_ALPHA = {read=_GetGL_ALPHA};
	__property int GL_ALPHA_BITS = {read=_GetGL_ALPHA_BITS};
	__property int GL_ALWAYS = {read=_GetGL_ALWAYS};
	__property int GL_ARRAY_BUFFER = {read=_GetGL_ARRAY_BUFFER};
	__property int GL_ARRAY_BUFFER_BINDING = {read=_GetGL_ARRAY_BUFFER_BINDING};
	__property int GL_ATTACHED_SHADERS = {read=_GetGL_ATTACHED_SHADERS};
	__property int GL_BACK = {read=_GetGL_BACK};
	__property int GL_BLEND = {read=_GetGL_BLEND};
	__property int GL_BLEND_COLOR = {read=_GetGL_BLEND_COLOR};
	__property int GL_BLEND_DST_ALPHA = {read=_GetGL_BLEND_DST_ALPHA};
	__property int GL_BLEND_DST_RGB = {read=_GetGL_BLEND_DST_RGB};
	__property int GL_BLEND_EQUATION = {read=_GetGL_BLEND_EQUATION};
	__property int GL_BLEND_EQUATION_ALPHA = {read=_GetGL_BLEND_EQUATION_ALPHA};
	__property int GL_BLEND_EQUATION_RGB = {read=_GetGL_BLEND_EQUATION_RGB};
	__property int GL_BLEND_SRC_ALPHA = {read=_GetGL_BLEND_SRC_ALPHA};
	__property int GL_BLEND_SRC_RGB = {read=_GetGL_BLEND_SRC_RGB};
	__property int GL_BLUE_BITS = {read=_GetGL_BLUE_BITS};
	__property int GL_BOOL = {read=_GetGL_BOOL};
	__property int GL_BOOL_VEC2 = {read=_GetGL_BOOL_VEC2};
	__property int GL_BOOL_VEC3 = {read=_GetGL_BOOL_VEC3};
	__property int GL_BOOL_VEC4 = {read=_GetGL_BOOL_VEC4};
	__property int GL_BUFFER_SIZE = {read=_GetGL_BUFFER_SIZE};
	__property int GL_BUFFER_USAGE = {read=_GetGL_BUFFER_USAGE};
	__property int GL_BYTE = {read=_GetGL_BYTE};
	__property int GL_CCW = {read=_GetGL_CCW};
	__property int GL_CLAMP_TO_EDGE = {read=_GetGL_CLAMP_TO_EDGE};
	__property int GL_COLOR_ATTACHMENT0 = {read=_GetGL_COLOR_ATTACHMENT0};
	__property int GL_COLOR_BUFFER_BIT = {read=_GetGL_COLOR_BUFFER_BIT};
	__property int GL_COLOR_CLEAR_VALUE = {read=_GetGL_COLOR_CLEAR_VALUE};
	__property int GL_COLOR_WRITEMASK = {read=_GetGL_COLOR_WRITEMASK};
	__property int GL_COMPILE_STATUS = {read=_GetGL_COMPILE_STATUS};
	__property int GL_COMPRESSED_TEXTURE_FORMATS = {read=_GetGL_COMPRESSED_TEXTURE_FORMATS};
	__property int GL_CONSTANT_ALPHA = {read=_GetGL_CONSTANT_ALPHA};
	__property int GL_CONSTANT_COLOR = {read=_GetGL_CONSTANT_COLOR};
	__property int GL_CULL_FACE = {read=_GetGL_CULL_FACE};
	__property int GL_CULL_FACE_MODE = {read=_GetGL_CULL_FACE_MODE};
	__property int GL_CURRENT_PROGRAM = {read=_GetGL_CURRENT_PROGRAM};
	__property int GL_CURRENT_VERTEX_ATTRIB = {read=_GetGL_CURRENT_VERTEX_ATTRIB};
	__property int GL_CW = {read=_GetGL_CW};
	__property int GL_DECR = {read=_GetGL_DECR};
	__property int GL_DECR_WRAP = {read=_GetGL_DECR_WRAP};
	__property int GL_DELETE_STATUS = {read=_GetGL_DELETE_STATUS};
	__property int GL_DEPTH_ATTACHMENT = {read=_GetGL_DEPTH_ATTACHMENT};
	__property int GL_DEPTH_BITS = {read=_GetGL_DEPTH_BITS};
	__property int GL_DEPTH_BUFFER_BIT = {read=_GetGL_DEPTH_BUFFER_BIT};
	__property int GL_DEPTH_CLEAR_VALUE = {read=_GetGL_DEPTH_CLEAR_VALUE};
	__property int GL_DEPTH_COMPONENT = {read=_GetGL_DEPTH_COMPONENT};
	__property int GL_DEPTH_COMPONENT16 = {read=_GetGL_DEPTH_COMPONENT16};
	__property int GL_DEPTH_FUNC = {read=_GetGL_DEPTH_FUNC};
	__property int GL_DEPTH_RANGE = {read=_GetGL_DEPTH_RANGE};
	__property int GL_DEPTH_TEST = {read=_GetGL_DEPTH_TEST};
	__property int GL_DEPTH_WRITEMASK = {read=_GetGL_DEPTH_WRITEMASK};
	__property int GL_DITHER = {read=_GetGL_DITHER};
	__property int GL_DONT_CARE = {read=_GetGL_DONT_CARE};
	__property int GL_DST_ALPHA = {read=_GetGL_DST_ALPHA};
	__property int GL_DST_COLOR = {read=_GetGL_DST_COLOR};
	__property int GL_DYNAMIC_DRAW = {read=_GetGL_DYNAMIC_DRAW};
	__property int GL_ELEMENT_ARRAY_BUFFER = {read=_GetGL_ELEMENT_ARRAY_BUFFER};
	__property int GL_ELEMENT_ARRAY_BUFFER_BINDING = {read=_GetGL_ELEMENT_ARRAY_BUFFER_BINDING};
	__property int GL_EQUAL = {read=_GetGL_EQUAL};
	__property int GL_EXTENSIONS = {read=_GetGL_EXTENSIONS};
	__property int GL_FALSE = {read=_GetGL_FALSE};
	__property int GL_FASTEST = {read=_GetGL_FASTEST};
	__property int GL_FIXED = {read=_GetGL_FIXED};
	__property int GL_FLOAT = {read=_GetGL_FLOAT};
	__property int GL_FLOAT_MAT2 = {read=_GetGL_FLOAT_MAT2};
	__property int GL_FLOAT_MAT3 = {read=_GetGL_FLOAT_MAT3};
	__property int GL_FLOAT_MAT4 = {read=_GetGL_FLOAT_MAT4};
	__property int GL_FLOAT_VEC2 = {read=_GetGL_FLOAT_VEC2};
	__property int GL_FLOAT_VEC3 = {read=_GetGL_FLOAT_VEC3};
	__property int GL_FLOAT_VEC4 = {read=_GetGL_FLOAT_VEC4};
	__property int GL_FRAGMENT_SHADER = {read=_GetGL_FRAGMENT_SHADER};
	__property int GL_FRAMEBUFFER = {read=_GetGL_FRAMEBUFFER};
	__property int GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME};
	__property int GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE};
	__property int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE};
	__property int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL};
	__property int GL_FRAMEBUFFER_BINDING = {read=_GetGL_FRAMEBUFFER_BINDING};
	__property int GL_FRAMEBUFFER_COMPLETE = {read=_GetGL_FRAMEBUFFER_COMPLETE};
	__property int GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT = {read=_GetGL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT};
	__property int GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS = {read=_GetGL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS};
	__property int GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT = {read=_GetGL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT};
	__property int GL_FRAMEBUFFER_UNSUPPORTED = {read=_GetGL_FRAMEBUFFER_UNSUPPORTED};
	__property int GL_FRONT = {read=_GetGL_FRONT};
	__property int GL_FRONT_AND_BACK = {read=_GetGL_FRONT_AND_BACK};
	__property int GL_FRONT_FACE = {read=_GetGL_FRONT_FACE};
	__property int GL_FUNC_ADD = {read=_GetGL_FUNC_ADD};
	__property int GL_FUNC_REVERSE_SUBTRACT = {read=_GetGL_FUNC_REVERSE_SUBTRACT};
	__property int GL_FUNC_SUBTRACT = {read=_GetGL_FUNC_SUBTRACT};
	__property int GL_GENERATE_MIPMAP_HINT = {read=_GetGL_GENERATE_MIPMAP_HINT};
	__property int GL_GEQUAL = {read=_GetGL_GEQUAL};
	__property int GL_GREATER = {read=_GetGL_GREATER};
	__property int GL_GREEN_BITS = {read=_GetGL_GREEN_BITS};
	__property int GL_HIGH_FLOAT = {read=_GetGL_HIGH_FLOAT};
	__property int GL_HIGH_INT = {read=_GetGL_HIGH_INT};
	__property int GL_IMPLEMENTATION_COLOR_READ_FORMAT = {read=_GetGL_IMPLEMENTATION_COLOR_READ_FORMAT};
	__property int GL_IMPLEMENTATION_COLOR_READ_TYPE = {read=_GetGL_IMPLEMENTATION_COLOR_READ_TYPE};
	__property int GL_INCR = {read=_GetGL_INCR};
	__property int GL_INCR_WRAP = {read=_GetGL_INCR_WRAP};
	__property int GL_INFO_LOG_LENGTH = {read=_GetGL_INFO_LOG_LENGTH};
	__property int GL_INT = {read=_GetGL_INT};
	__property int GL_INT_VEC2 = {read=_GetGL_INT_VEC2};
	__property int GL_INT_VEC3 = {read=_GetGL_INT_VEC3};
	__property int GL_INT_VEC4 = {read=_GetGL_INT_VEC4};
	__property int GL_INVALID_ENUM = {read=_GetGL_INVALID_ENUM};
	__property int GL_INVALID_FRAMEBUFFER_OPERATION = {read=_GetGL_INVALID_FRAMEBUFFER_OPERATION};
	__property int GL_INVALID_OPERATION = {read=_GetGL_INVALID_OPERATION};
	__property int GL_INVALID_VALUE = {read=_GetGL_INVALID_VALUE};
	__property int GL_INVERT = {read=_GetGL_INVERT};
	__property int GL_KEEP = {read=_GetGL_KEEP};
	__property int GL_LEQUAL = {read=_GetGL_LEQUAL};
	__property int GL_LESS = {read=_GetGL_LESS};
	__property int GL_LINEAR = {read=_GetGL_LINEAR};
	__property int GL_LINEAR_MIPMAP_LINEAR = {read=_GetGL_LINEAR_MIPMAP_LINEAR};
	__property int GL_LINEAR_MIPMAP_NEAREST = {read=_GetGL_LINEAR_MIPMAP_NEAREST};
	__property int GL_LINES = {read=_GetGL_LINES};
	__property int GL_LINE_LOOP = {read=_GetGL_LINE_LOOP};
	__property int GL_LINE_STRIP = {read=_GetGL_LINE_STRIP};
	__property int GL_LINE_WIDTH = {read=_GetGL_LINE_WIDTH};
	__property int GL_LINK_STATUS = {read=_GetGL_LINK_STATUS};
	__property int GL_LOW_FLOAT = {read=_GetGL_LOW_FLOAT};
	__property int GL_LOW_INT = {read=_GetGL_LOW_INT};
	__property int GL_LUMINANCE = {read=_GetGL_LUMINANCE};
	__property int GL_LUMINANCE_ALPHA = {read=_GetGL_LUMINANCE_ALPHA};
	__property int GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = {read=_GetGL_MAX_COMBINED_TEXTURE_IMAGE_UNITS};
	__property int GL_MAX_CUBE_MAP_TEXTURE_SIZE = {read=_GetGL_MAX_CUBE_MAP_TEXTURE_SIZE};
	__property int GL_MAX_FRAGMENT_UNIFORM_VECTORS = {read=_GetGL_MAX_FRAGMENT_UNIFORM_VECTORS};
	__property int GL_MAX_RENDERBUFFER_SIZE = {read=_GetGL_MAX_RENDERBUFFER_SIZE};
	__property int GL_MAX_TEXTURE_IMAGE_UNITS = {read=_GetGL_MAX_TEXTURE_IMAGE_UNITS};
	__property int GL_MAX_TEXTURE_SIZE = {read=_GetGL_MAX_TEXTURE_SIZE};
	__property int GL_MAX_VARYING_VECTORS = {read=_GetGL_MAX_VARYING_VECTORS};
	__property int GL_MAX_VERTEX_ATTRIBS = {read=_GetGL_MAX_VERTEX_ATTRIBS};
	__property int GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = {read=_GetGL_MAX_VERTEX_TEXTURE_IMAGE_UNITS};
	__property int GL_MAX_VERTEX_UNIFORM_VECTORS = {read=_GetGL_MAX_VERTEX_UNIFORM_VECTORS};
	__property int GL_MAX_VIEWPORT_DIMS = {read=_GetGL_MAX_VIEWPORT_DIMS};
	__property int GL_MEDIUM_FLOAT = {read=_GetGL_MEDIUM_FLOAT};
	__property int GL_MEDIUM_INT = {read=_GetGL_MEDIUM_INT};
	__property int GL_MIRRORED_REPEAT = {read=_GetGL_MIRRORED_REPEAT};
	__property int GL_NEAREST = {read=_GetGL_NEAREST};
	__property int GL_NEAREST_MIPMAP_LINEAR = {read=_GetGL_NEAREST_MIPMAP_LINEAR};
	__property int GL_NEAREST_MIPMAP_NEAREST = {read=_GetGL_NEAREST_MIPMAP_NEAREST};
	__property int GL_NEVER = {read=_GetGL_NEVER};
	__property int GL_NICEST = {read=_GetGL_NICEST};
	__property int GL_NONE = {read=_GetGL_NONE};
	__property int GL_NOTEQUAL = {read=_GetGL_NOTEQUAL};
	__property int GL_NO_ERROR = {read=_GetGL_NO_ERROR};
	__property int GL_NUM_COMPRESSED_TEXTURE_FORMATS = {read=_GetGL_NUM_COMPRESSED_TEXTURE_FORMATS};
	__property int GL_NUM_SHADER_BINARY_FORMATS = {read=_GetGL_NUM_SHADER_BINARY_FORMATS};
	__property int GL_ONE = {read=_GetGL_ONE};
	__property int GL_ONE_MINUS_CONSTANT_ALPHA = {read=_GetGL_ONE_MINUS_CONSTANT_ALPHA};
	__property int GL_ONE_MINUS_CONSTANT_COLOR = {read=_GetGL_ONE_MINUS_CONSTANT_COLOR};
	__property int GL_ONE_MINUS_DST_ALPHA = {read=_GetGL_ONE_MINUS_DST_ALPHA};
	__property int GL_ONE_MINUS_DST_COLOR = {read=_GetGL_ONE_MINUS_DST_COLOR};
	__property int GL_ONE_MINUS_SRC_ALPHA = {read=_GetGL_ONE_MINUS_SRC_ALPHA};
	__property int GL_ONE_MINUS_SRC_COLOR = {read=_GetGL_ONE_MINUS_SRC_COLOR};
	__property int GL_OUT_OF_MEMORY = {read=_GetGL_OUT_OF_MEMORY};
	__property int GL_PACK_ALIGNMENT = {read=_GetGL_PACK_ALIGNMENT};
	__property int GL_POINTS = {read=_GetGL_POINTS};
	__property int GL_POLYGON_OFFSET_FACTOR = {read=_GetGL_POLYGON_OFFSET_FACTOR};
	__property int GL_POLYGON_OFFSET_FILL = {read=_GetGL_POLYGON_OFFSET_FILL};
	__property int GL_POLYGON_OFFSET_UNITS = {read=_GetGL_POLYGON_OFFSET_UNITS};
	__property int GL_RED_BITS = {read=_GetGL_RED_BITS};
	__property int GL_RENDERBUFFER = {read=_GetGL_RENDERBUFFER};
	__property int GL_RENDERBUFFER_ALPHA_SIZE = {read=_GetGL_RENDERBUFFER_ALPHA_SIZE};
	__property int GL_RENDERBUFFER_BINDING = {read=_GetGL_RENDERBUFFER_BINDING};
	__property int GL_RENDERBUFFER_BLUE_SIZE = {read=_GetGL_RENDERBUFFER_BLUE_SIZE};
	__property int GL_RENDERBUFFER_DEPTH_SIZE = {read=_GetGL_RENDERBUFFER_DEPTH_SIZE};
	__property int GL_RENDERBUFFER_GREEN_SIZE = {read=_GetGL_RENDERBUFFER_GREEN_SIZE};
	__property int GL_RENDERBUFFER_HEIGHT = {read=_GetGL_RENDERBUFFER_HEIGHT};
	__property int GL_RENDERBUFFER_INTERNAL_FORMAT = {read=_GetGL_RENDERBUFFER_INTERNAL_FORMAT};
	__property int GL_RENDERBUFFER_RED_SIZE = {read=_GetGL_RENDERBUFFER_RED_SIZE};
	__property int GL_RENDERBUFFER_STENCIL_SIZE = {read=_GetGL_RENDERBUFFER_STENCIL_SIZE};
	__property int GL_RENDERBUFFER_WIDTH = {read=_GetGL_RENDERBUFFER_WIDTH};
	__property int GL_RENDERER = {read=_GetGL_RENDERER};
	__property int GL_REPEAT = {read=_GetGL_REPEAT};
	__property int GL_REPLACE = {read=_GetGL_REPLACE};
	__property int GL_RGB = {read=_GetGL_RGB};
	__property int GL_RGB565 = {read=_GetGL_RGB565};
	__property int GL_RGB5_A1 = {read=_GetGL_RGB5_A1};
	__property int GL_RGBA = {read=_GetGL_RGBA};
	__property int GL_RGBA4 = {read=_GetGL_RGBA4};
	__property int GL_SAMPLER_2D = {read=_GetGL_SAMPLER_2D};
	__property int GL_SAMPLER_CUBE = {read=_GetGL_SAMPLER_CUBE};
	__property int GL_SAMPLES = {read=_GetGL_SAMPLES};
	__property int GL_SAMPLE_ALPHA_TO_COVERAGE = {read=_GetGL_SAMPLE_ALPHA_TO_COVERAGE};
	__property int GL_SAMPLE_BUFFERS = {read=_GetGL_SAMPLE_BUFFERS};
	__property int GL_SAMPLE_COVERAGE = {read=_GetGL_SAMPLE_COVERAGE};
	__property int GL_SAMPLE_COVERAGE_INVERT = {read=_GetGL_SAMPLE_COVERAGE_INVERT};
	__property int GL_SAMPLE_COVERAGE_VALUE = {read=_GetGL_SAMPLE_COVERAGE_VALUE};
	__property int GL_SCISSOR_BOX = {read=_GetGL_SCISSOR_BOX};
	__property int GL_SCISSOR_TEST = {read=_GetGL_SCISSOR_TEST};
	__property int GL_SHADER_BINARY_FORMATS = {read=_GetGL_SHADER_BINARY_FORMATS};
	__property int GL_SHADER_COMPILER = {read=_GetGL_SHADER_COMPILER};
	__property int GL_SHADER_SOURCE_LENGTH = {read=_GetGL_SHADER_SOURCE_LENGTH};
	__property int GL_SHADER_TYPE = {read=_GetGL_SHADER_TYPE};
	__property int GL_SHADING_LANGUAGE_VERSION = {read=_GetGL_SHADING_LANGUAGE_VERSION};
	__property int GL_SHORT = {read=_GetGL_SHORT};
	__property int GL_SRC_ALPHA = {read=_GetGL_SRC_ALPHA};
	__property int GL_SRC_ALPHA_SATURATE = {read=_GetGL_SRC_ALPHA_SATURATE};
	__property int GL_SRC_COLOR = {read=_GetGL_SRC_COLOR};
	__property int GL_STATIC_DRAW = {read=_GetGL_STATIC_DRAW};
	__property int GL_STENCIL_ATTACHMENT = {read=_GetGL_STENCIL_ATTACHMENT};
	__property int GL_STENCIL_BACK_FAIL = {read=_GetGL_STENCIL_BACK_FAIL};
	__property int GL_STENCIL_BACK_FUNC = {read=_GetGL_STENCIL_BACK_FUNC};
	__property int GL_STENCIL_BACK_PASS_DEPTH_FAIL = {read=_GetGL_STENCIL_BACK_PASS_DEPTH_FAIL};
	__property int GL_STENCIL_BACK_PASS_DEPTH_PASS = {read=_GetGL_STENCIL_BACK_PASS_DEPTH_PASS};
	__property int GL_STENCIL_BACK_REF = {read=_GetGL_STENCIL_BACK_REF};
	__property int GL_STENCIL_BACK_VALUE_MASK = {read=_GetGL_STENCIL_BACK_VALUE_MASK};
	__property int GL_STENCIL_BACK_WRITEMASK = {read=_GetGL_STENCIL_BACK_WRITEMASK};
	__property int GL_STENCIL_BITS = {read=_GetGL_STENCIL_BITS};
	__property int GL_STENCIL_BUFFER_BIT = {read=_GetGL_STENCIL_BUFFER_BIT};
	__property int GL_STENCIL_CLEAR_VALUE = {read=_GetGL_STENCIL_CLEAR_VALUE};
	__property int GL_STENCIL_FAIL = {read=_GetGL_STENCIL_FAIL};
	__property int GL_STENCIL_FUNC = {read=_GetGL_STENCIL_FUNC};
	__property int GL_STENCIL_INDEX = {read=_GetGL_STENCIL_INDEX};
	__property int GL_STENCIL_INDEX8 = {read=_GetGL_STENCIL_INDEX8};
	__property int GL_STENCIL_PASS_DEPTH_FAIL = {read=_GetGL_STENCIL_PASS_DEPTH_FAIL};
	__property int GL_STENCIL_PASS_DEPTH_PASS = {read=_GetGL_STENCIL_PASS_DEPTH_PASS};
	__property int GL_STENCIL_REF = {read=_GetGL_STENCIL_REF};
	__property int GL_STENCIL_TEST = {read=_GetGL_STENCIL_TEST};
	__property int GL_STENCIL_VALUE_MASK = {read=_GetGL_STENCIL_VALUE_MASK};
	__property int GL_STENCIL_WRITEMASK = {read=_GetGL_STENCIL_WRITEMASK};
	__property int GL_STREAM_DRAW = {read=_GetGL_STREAM_DRAW};
	__property int GL_SUBPIXEL_BITS = {read=_GetGL_SUBPIXEL_BITS};
	__property int GL_TEXTURE = {read=_GetGL_TEXTURE};
	__property int GL_TEXTURE0 = {read=_GetGL_TEXTURE0};
	__property int GL_TEXTURE1 = {read=_GetGL_TEXTURE1};
	__property int GL_TEXTURE10 = {read=_GetGL_TEXTURE10};
	__property int GL_TEXTURE11 = {read=_GetGL_TEXTURE11};
	__property int GL_TEXTURE12 = {read=_GetGL_TEXTURE12};
	__property int GL_TEXTURE13 = {read=_GetGL_TEXTURE13};
	__property int GL_TEXTURE14 = {read=_GetGL_TEXTURE14};
	__property int GL_TEXTURE15 = {read=_GetGL_TEXTURE15};
	__property int GL_TEXTURE16 = {read=_GetGL_TEXTURE16};
	__property int GL_TEXTURE17 = {read=_GetGL_TEXTURE17};
	__property int GL_TEXTURE18 = {read=_GetGL_TEXTURE18};
	__property int GL_TEXTURE19 = {read=_GetGL_TEXTURE19};
	__property int GL_TEXTURE2 = {read=_GetGL_TEXTURE2};
	__property int GL_TEXTURE20 = {read=_GetGL_TEXTURE20};
	__property int GL_TEXTURE21 = {read=_GetGL_TEXTURE21};
	__property int GL_TEXTURE22 = {read=_GetGL_TEXTURE22};
	__property int GL_TEXTURE23 = {read=_GetGL_TEXTURE23};
	__property int GL_TEXTURE24 = {read=_GetGL_TEXTURE24};
	__property int GL_TEXTURE25 = {read=_GetGL_TEXTURE25};
	__property int GL_TEXTURE26 = {read=_GetGL_TEXTURE26};
	__property int GL_TEXTURE27 = {read=_GetGL_TEXTURE27};
	__property int GL_TEXTURE28 = {read=_GetGL_TEXTURE28};
	__property int GL_TEXTURE29 = {read=_GetGL_TEXTURE29};
	__property int GL_TEXTURE3 = {read=_GetGL_TEXTURE3};
	__property int GL_TEXTURE30 = {read=_GetGL_TEXTURE30};
	__property int GL_TEXTURE31 = {read=_GetGL_TEXTURE31};
	__property int GL_TEXTURE4 = {read=_GetGL_TEXTURE4};
	__property int GL_TEXTURE5 = {read=_GetGL_TEXTURE5};
	__property int GL_TEXTURE6 = {read=_GetGL_TEXTURE6};
	__property int GL_TEXTURE7 = {read=_GetGL_TEXTURE7};
	__property int GL_TEXTURE8 = {read=_GetGL_TEXTURE8};
	__property int GL_TEXTURE9 = {read=_GetGL_TEXTURE9};
	__property int GL_TEXTURE_2D = {read=_GetGL_TEXTURE_2D};
	__property int GL_TEXTURE_BINDING_2D = {read=_GetGL_TEXTURE_BINDING_2D};
	__property int GL_TEXTURE_BINDING_CUBE_MAP = {read=_GetGL_TEXTURE_BINDING_CUBE_MAP};
	__property int GL_TEXTURE_CUBE_MAP = {read=_GetGL_TEXTURE_CUBE_MAP};
	__property int GL_TEXTURE_CUBE_MAP_NEGATIVE_X = {read=_GetGL_TEXTURE_CUBE_MAP_NEGATIVE_X};
	__property int GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = {read=_GetGL_TEXTURE_CUBE_MAP_NEGATIVE_Y};
	__property int GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = {read=_GetGL_TEXTURE_CUBE_MAP_NEGATIVE_Z};
	__property int GL_TEXTURE_CUBE_MAP_POSITIVE_X = {read=_GetGL_TEXTURE_CUBE_MAP_POSITIVE_X};
	__property int GL_TEXTURE_CUBE_MAP_POSITIVE_Y = {read=_GetGL_TEXTURE_CUBE_MAP_POSITIVE_Y};
	__property int GL_TEXTURE_CUBE_MAP_POSITIVE_Z = {read=_GetGL_TEXTURE_CUBE_MAP_POSITIVE_Z};
	__property int GL_TEXTURE_MAG_FILTER = {read=_GetGL_TEXTURE_MAG_FILTER};
	__property int GL_TEXTURE_MIN_FILTER = {read=_GetGL_TEXTURE_MIN_FILTER};
	__property int GL_TEXTURE_WRAP_S = {read=_GetGL_TEXTURE_WRAP_S};
	__property int GL_TEXTURE_WRAP_T = {read=_GetGL_TEXTURE_WRAP_T};
	__property int GL_TRIANGLES = {read=_GetGL_TRIANGLES};
	__property int GL_TRIANGLE_FAN = {read=_GetGL_TRIANGLE_FAN};
	__property int GL_TRIANGLE_STRIP = {read=_GetGL_TRIANGLE_STRIP};
	__property int GL_TRUE = {read=_GetGL_TRUE};
	__property int GL_UNPACK_ALIGNMENT = {read=_GetGL_UNPACK_ALIGNMENT};
	__property int GL_UNSIGNED_BYTE = {read=_GetGL_UNSIGNED_BYTE};
	__property int GL_UNSIGNED_INT = {read=_GetGL_UNSIGNED_INT};
	__property int GL_UNSIGNED_SHORT = {read=_GetGL_UNSIGNED_SHORT};
	__property int GL_UNSIGNED_SHORT_4_4_4_4 = {read=_GetGL_UNSIGNED_SHORT_4_4_4_4};
	__property int GL_UNSIGNED_SHORT_5_5_5_1 = {read=_GetGL_UNSIGNED_SHORT_5_5_5_1};
	__property int GL_UNSIGNED_SHORT_5_6_5 = {read=_GetGL_UNSIGNED_SHORT_5_6_5};
	__property int GL_VALIDATE_STATUS = {read=_GetGL_VALIDATE_STATUS};
	__property int GL_VENDOR = {read=_GetGL_VENDOR};
	__property int GL_VERSION = {read=_GetGL_VERSION};
	__property int GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING = {read=_GetGL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING};
	__property int GL_VERTEX_ATTRIB_ARRAY_ENABLED = {read=_GetGL_VERTEX_ATTRIB_ARRAY_ENABLED};
	__property int GL_VERTEX_ATTRIB_ARRAY_NORMALIZED = {read=_GetGL_VERTEX_ATTRIB_ARRAY_NORMALIZED};
	__property int GL_VERTEX_ATTRIB_ARRAY_POINTER = {read=_GetGL_VERTEX_ATTRIB_ARRAY_POINTER};
	__property int GL_VERTEX_ATTRIB_ARRAY_SIZE = {read=_GetGL_VERTEX_ATTRIB_ARRAY_SIZE};
	__property int GL_VERTEX_ATTRIB_ARRAY_STRIDE = {read=_GetGL_VERTEX_ATTRIB_ARRAY_STRIDE};
	__property int GL_VERTEX_ATTRIB_ARRAY_TYPE = {read=_GetGL_VERTEX_ATTRIB_ARRAY_TYPE};
	__property int GL_VERTEX_SHADER = {read=_GetGL_VERTEX_SHADER};
	__property int GL_VIEWPORT = {read=_GetGL_VIEWPORT};
	__property int GL_ZERO = {read=_GetGL_ZERO};
};

__interface  INTERFACE_UUID("{C9117E42-C2BB-477E-9824-8499EB52648C}") JGLES20  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLES20 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES20Class,_di_JGLES20>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES20Class,_di_JGLES20> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLES20() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES20Class,_di_JGLES20>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLES20() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AB1FCB89-9334-45D0-94EB-1B0BE5D0D311}") JGLES30Class  : public JGLES20Class 
{
	virtual int __cdecl _GetGL_ACTIVE_UNIFORM_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_ALREADY_SIGNALED() = 0 ;
	virtual int __cdecl _GetGL_ANY_SAMPLES_PASSED() = 0 ;
	virtual int __cdecl _GetGL_ANY_SAMPLES_PASSED_CONSERVATIVE() = 0 ;
	virtual int __cdecl _GetGL_BLUE() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_ACCESS_FLAGS() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_MAPPED() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_MAP_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_MAP_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_MAP_POINTER() = 0 ;
	virtual int __cdecl _GetGL_COLOR() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT1() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT10() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT11() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT12() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT13() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT14() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT15() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT2() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT3() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT4() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT5() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT6() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT7() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT8() = 0 ;
	virtual int __cdecl _GetGL_COLOR_ATTACHMENT9() = 0 ;
	virtual int __cdecl _GetGL_COMPARE_REF_TO_TEXTURE() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_R11_EAC() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RG11_EAC() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGB8_ETC2() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA8_ETC2_EAC() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SIGNED_R11_EAC() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SIGNED_RG11_EAC() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ETC2() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2() = 0 ;
	virtual int __cdecl _GetGL_CONDITION_SATISFIED() = 0 ;
	virtual int __cdecl _GetGL_COPY_READ_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_COPY_READ_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_COPY_WRITE_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_COPY_WRITE_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_CURRENT_QUERY() = 0 ;
	virtual int __cdecl _GetGL_DEPTH() = 0 ;
	virtual int __cdecl _GetGL_DEPTH24_STENCIL8() = 0 ;
	virtual int __cdecl _GetGL_DEPTH32F_STENCIL8() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_COMPONENT24() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_COMPONENT32F() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_STENCIL() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_STENCIL_ATTACHMENT() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER0() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER1() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER10() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER11() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER12() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER13() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER14() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER15() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER2() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER3() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER4() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER5() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER6() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER7() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER8() = 0 ;
	virtual int __cdecl _GetGL_DRAW_BUFFER9() = 0 ;
	virtual int __cdecl _GetGL_DRAW_FRAMEBUFFER() = 0 ;
	virtual int __cdecl _GetGL_DRAW_FRAMEBUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_DYNAMIC_COPY() = 0 ;
	virtual int __cdecl _GetGL_DYNAMIC_READ() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_32_UNSIGNED_INT_24_8_REV() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_MAT2x3() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_MAT2x4() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_MAT3x2() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_MAT3x4() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_MAT4x2() = 0 ;
	virtual int __cdecl _GetGL_FLOAT_MAT4x3() = 0 ;
	virtual int __cdecl _GetGL_FRAGMENT_SHADER_DERIVATIVE_HINT() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_RED_SIZE() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_DEFAULT() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_UNDEFINED() = 0 ;
	virtual int __cdecl _GetGL_GREEN() = 0 ;
	virtual int __cdecl _GetGL_HALF_FLOAT() = 0 ;
	virtual int __cdecl _GetGL_INTERLEAVED_ATTRIBS() = 0 ;
	virtual int __cdecl _GetGL_INT_2_10_10_10_REV() = 0 ;
	virtual int __cdecl _GetGL_INT_SAMPLER_2D() = 0 ;
	virtual int __cdecl _GetGL_INT_SAMPLER_2D_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_INT_SAMPLER_3D() = 0 ;
	virtual int __cdecl _GetGL_INT_SAMPLER_CUBE() = 0 ;
	virtual int __cdecl _GetGL_INVALID_INDEX() = 0 ;
	virtual int __cdecl _GetGL_MAJOR_VERSION() = 0 ;
	virtual int __cdecl _GetGL_MAP_FLUSH_EXPLICIT_BIT() = 0 ;
	virtual int __cdecl _GetGL_MAP_INVALIDATE_BUFFER_BIT() = 0 ;
	virtual int __cdecl _GetGL_MAP_INVALIDATE_RANGE_BIT() = 0 ;
	virtual int __cdecl _GetGL_MAP_READ_BIT() = 0 ;
	virtual int __cdecl _GetGL_MAP_UNSYNCHRONIZED_BIT() = 0 ;
	virtual int __cdecl _GetGL_MAP_WRITE_BIT() = 0 ;
	virtual int __cdecl _GetGL_MAX() = 0 ;
	virtual int __cdecl _GetGL_MAX_3D_TEXTURE_SIZE() = 0 ;
	virtual int __cdecl _GetGL_MAX_ARRAY_TEXTURE_LAYERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COLOR_ATTACHMENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_UNIFORM_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_DRAW_BUFFERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_ELEMENTS_INDICES() = 0 ;
	virtual int __cdecl _GetGL_MAX_ELEMENTS_VERTICES() = 0 ;
	virtual int __cdecl _GetGL_MAX_ELEMENT_INDEX() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAGMENT_INPUT_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAGMENT_UNIFORM_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAGMENT_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_PROGRAM_TEXEL_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_MAX_SAMPLES() = 0 ;
	virtual int __cdecl _GetGL_MAX_SERVER_WAIT_TIMEOUT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TEXTURE_LOD_BIAS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_UNIFORM_BLOCK_SIZE() = 0 ;
	virtual int __cdecl _GetGL_MAX_UNIFORM_BUFFER_BINDINGS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VARYING_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_OUTPUT_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_UNIFORM_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MIN() = 0 ;
	virtual int __cdecl _GetGL_MINOR_VERSION() = 0 ;
	virtual int __cdecl _GetGL_MIN_PROGRAM_TEXEL_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_NUM_EXTENSIONS() = 0 ;
	virtual int __cdecl _GetGL_NUM_PROGRAM_BINARY_FORMATS() = 0 ;
	virtual int __cdecl _GetGL_NUM_SAMPLE_COUNTS() = 0 ;
	virtual int __cdecl _GetGL_OBJECT_TYPE() = 0 ;
	virtual int __cdecl _GetGL_PACK_ROW_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_PACK_SKIP_PIXELS() = 0 ;
	virtual int __cdecl _GetGL_PACK_SKIP_ROWS() = 0 ;
	virtual int __cdecl _GetGL_PIXEL_PACK_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_PIXEL_PACK_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_PIXEL_UNPACK_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_PIXEL_UNPACK_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_PRIMITIVE_RESTART_FIXED_INDEX() = 0 ;
	virtual int __cdecl _GetGL_PROGRAM_BINARY_FORMATS() = 0 ;
	virtual int __cdecl _GetGL_PROGRAM_BINARY_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_PROGRAM_BINARY_RETRIEVABLE_HINT() = 0 ;
	virtual int __cdecl _GetGL_QUERY_RESULT() = 0 ;
	virtual int __cdecl _GetGL_QUERY_RESULT_AVAILABLE() = 0 ;
	virtual int __cdecl _GetGL_R11F_G11F_B10F() = 0 ;
	virtual int __cdecl _GetGL_R16F() = 0 ;
	virtual int __cdecl _GetGL_R16I() = 0 ;
	virtual int __cdecl _GetGL_R16UI() = 0 ;
	virtual int __cdecl _GetGL_R32F() = 0 ;
	virtual int __cdecl _GetGL_R32I() = 0 ;
	virtual int __cdecl _GetGL_R32UI() = 0 ;
	virtual int __cdecl _GetGL_R8() = 0 ;
	virtual int __cdecl _GetGL_R8I() = 0 ;
	virtual int __cdecl _GetGL_R8UI() = 0 ;
	virtual int __cdecl _GetGL_R8_SNORM() = 0 ;
	virtual int __cdecl _GetGL_RASTERIZER_DISCARD() = 0 ;
	virtual int __cdecl _GetGL_READ_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_READ_FRAMEBUFFER() = 0 ;
	virtual int __cdecl _GetGL_READ_FRAMEBUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_RED() = 0 ;
	virtual int __cdecl _GetGL_RED_INTEGER() = 0 ;
	virtual int __cdecl _GetGL_RENDERBUFFER_SAMPLES() = 0 ;
	virtual int __cdecl _GetGL_RG() = 0 ;
	virtual int __cdecl _GetGL_RG16F() = 0 ;
	virtual int __cdecl _GetGL_RG16I() = 0 ;
	virtual int __cdecl _GetGL_RG16UI() = 0 ;
	virtual int __cdecl _GetGL_RG32F() = 0 ;
	virtual int __cdecl _GetGL_RG32I() = 0 ;
	virtual int __cdecl _GetGL_RG32UI() = 0 ;
	virtual int __cdecl _GetGL_RG8() = 0 ;
	virtual int __cdecl _GetGL_RG8I() = 0 ;
	virtual int __cdecl _GetGL_RG8UI() = 0 ;
	virtual int __cdecl _GetGL_RG8_SNORM() = 0 ;
	virtual int __cdecl _GetGL_RGB10_A2() = 0 ;
	virtual int __cdecl _GetGL_RGB10_A2UI() = 0 ;
	virtual int __cdecl _GetGL_RGB16F() = 0 ;
	virtual int __cdecl _GetGL_RGB16I() = 0 ;
	virtual int __cdecl _GetGL_RGB16UI() = 0 ;
	virtual int __cdecl _GetGL_RGB32F() = 0 ;
	virtual int __cdecl _GetGL_RGB32I() = 0 ;
	virtual int __cdecl _GetGL_RGB32UI() = 0 ;
	virtual int __cdecl _GetGL_RGB8() = 0 ;
	virtual int __cdecl _GetGL_RGB8I() = 0 ;
	virtual int __cdecl _GetGL_RGB8UI() = 0 ;
	virtual int __cdecl _GetGL_RGB8_SNORM() = 0 ;
	virtual int __cdecl _GetGL_RGB9_E5() = 0 ;
	virtual int __cdecl _GetGL_RGBA16F() = 0 ;
	virtual int __cdecl _GetGL_RGBA16I() = 0 ;
	virtual int __cdecl _GetGL_RGBA16UI() = 0 ;
	virtual int __cdecl _GetGL_RGBA32F() = 0 ;
	virtual int __cdecl _GetGL_RGBA32I() = 0 ;
	virtual int __cdecl _GetGL_RGBA32UI() = 0 ;
	virtual int __cdecl _GetGL_RGBA8() = 0 ;
	virtual int __cdecl _GetGL_RGBA8I() = 0 ;
	virtual int __cdecl _GetGL_RGBA8UI() = 0 ;
	virtual int __cdecl _GetGL_RGBA8_SNORM() = 0 ;
	virtual int __cdecl _GetGL_RGBA_INTEGER() = 0 ;
	virtual int __cdecl _GetGL_RGB_INTEGER() = 0 ;
	virtual int __cdecl _GetGL_RG_INTEGER() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_2D_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_2D_ARRAY_SHADOW() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_2D_SHADOW() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_3D() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_CUBE_SHADOW() = 0 ;
	virtual int __cdecl _GetGL_SEPARATE_ATTRIBS() = 0 ;
	virtual int __cdecl _GetGL_SIGNALED() = 0 ;
	virtual int __cdecl _GetGL_SIGNED_NORMALIZED() = 0 ;
	virtual int __cdecl _GetGL_SRGB() = 0 ;
	virtual int __cdecl _GetGL_SRGB8() = 0 ;
	virtual int __cdecl _GetGL_SRGB8_ALPHA8() = 0 ;
	virtual int __cdecl _GetGL_STATIC_COPY() = 0 ;
	virtual int __cdecl _GetGL_STATIC_READ() = 0 ;
	virtual int __cdecl _GetGL_STENCIL() = 0 ;
	virtual int __cdecl _GetGL_STREAM_COPY() = 0 ;
	virtual int __cdecl _GetGL_STREAM_READ() = 0 ;
	virtual int __cdecl _GetGL_SYNC_CONDITION() = 0 ;
	virtual int __cdecl _GetGL_SYNC_FENCE() = 0 ;
	virtual int __cdecl _GetGL_SYNC_FLAGS() = 0 ;
	virtual int __cdecl _GetGL_SYNC_FLUSH_COMMANDS_BIT() = 0 ;
	virtual int __cdecl _GetGL_SYNC_GPU_COMMANDS_COMPLETE() = 0 ;
	virtual int __cdecl _GetGL_SYNC_STATUS() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_2D_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_3D() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BASE_LEVEL() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_2D_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_3D() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_COMPARE_FUNC() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_COMPARE_MODE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_IMMUTABLE_FORMAT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_IMMUTABLE_LEVELS() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_MAX_LEVEL() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_MAX_LOD() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_MIN_LOD() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_SWIZZLE_A() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_SWIZZLE_B() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_SWIZZLE_G() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_SWIZZLE_R() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_WRAP_R() = 0 ;
	virtual int __cdecl _GetGL_TIMEOUT_EXPIRED() = 0 ;
	virtual __int64 __cdecl _GetGL_TIMEOUT_IGNORED() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_ACTIVE() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_BINDING() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_BUFFER_MODE() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_BUFFER_SIZE() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_BUFFER_START() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_PAUSED() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_VARYINGS() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_ARRAY_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BLOCK_ACTIVE_UNIFORMS() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BLOCK_BINDING() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BLOCK_DATA_SIZE() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BLOCK_INDEX() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BLOCK_NAME_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BUFFER_OFFSET_ALIGNMENT() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BUFFER_SIZE() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BUFFER_START() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_IS_ROW_MAJOR() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_MATRIX_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_NAME_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_SIZE() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_TYPE() = 0 ;
	virtual int __cdecl _GetGL_UNPACK_IMAGE_HEIGHT() = 0 ;
	virtual int __cdecl _GetGL_UNPACK_ROW_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_UNPACK_SKIP_IMAGES() = 0 ;
	virtual int __cdecl _GetGL_UNPACK_SKIP_PIXELS() = 0 ;
	virtual int __cdecl _GetGL_UNPACK_SKIP_ROWS() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNALED() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_10F_11F_11F_REV() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_24_8() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_2_10_10_10_REV() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_5_9_9_9_REV() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_SAMPLER_2D() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_SAMPLER_2D_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_SAMPLER_3D() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_SAMPLER_CUBE() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_VEC2() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_VEC3() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_VEC4() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_NORMALIZED() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ARRAY_BINDING() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_ARRAY_DIVISOR() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_ARRAY_INTEGER() = 0 ;
	virtual int __cdecl _GetGL_WAIT_FAILED() = 0 ;
	HIDESBASE virtual _di_JGLES30 __cdecl init() = 0 ;
	virtual void __cdecl glBeginQuery(int target, int id) = 0 ;
	virtual void __cdecl glBeginTransformFeedback(int primitiveMode) = 0 ;
	virtual void __cdecl glBindBufferBase(int target, int index, int buffer) = 0 ;
	virtual void __cdecl glBindBufferRange(int target, int index, int buffer, int offset, int size) = 0 ;
	virtual void __cdecl glBindSampler(int unit_, int sampler) = 0 ;
	virtual void __cdecl glBindTransformFeedback(int target, int id) = 0 ;
	virtual void __cdecl glBindVertexArray(int array_) = 0 ;
	virtual void __cdecl glBlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, int mask, int filter) = 0 ;
	virtual void __cdecl glClearBufferfi(int buffer, int drawbuffer, float depth, int stencil) = 0 ;
	virtual void __cdecl glClearBufferfv(int buffer, int drawbuffer, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glClearBufferfv(int buffer, int drawbuffer, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glClearBufferiv(int buffer, int drawbuffer, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glClearBufferiv(int buffer, int drawbuffer, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glClearBufferuiv(int buffer, int drawbuffer, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glClearBufferuiv(int buffer, int drawbuffer, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual int __cdecl glClientWaitSync(__int64 sync, int flags, __int64 timeout) = 0 ;
	virtual void __cdecl glCompressedTexImage3D(int target, int level, int internalformat, int width, int height, int depth, int border, int imageSize, Androidapi::Jni::Javatypes::_di_JBuffer data) = 0 /* overload */;
	virtual void __cdecl glCompressedTexImage3D(int target, int level, int internalformat, int width, int height, int depth, int border, int imageSize, int offset) = 0 /* overload */;
	virtual void __cdecl glCompressedTexSubImage3D(int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, int format, int imageSize, Androidapi::Jni::Javatypes::_di_JBuffer data) = 0 /* overload */;
	virtual void __cdecl glCompressedTexSubImage3D(int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, int format, int imageSize, int offset) = 0 /* overload */;
	virtual void __cdecl glCopyBufferSubData(int readTarget, int writeTarget, int readOffset, int writeOffset, int size) = 0 ;
	virtual void __cdecl glCopyTexSubImage3D(int target, int level, int xoffset, int yoffset, int zoffset, int x, int y, int width, int height) = 0 ;
	virtual void __cdecl glDeleteQueries(int n, Androidapi::Jnibridge::TJavaArray__1<int>* ids, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteQueries(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer ids) = 0 /* overload */;
	virtual void __cdecl glDeleteSamplers(int count, Androidapi::Jnibridge::TJavaArray__1<int>* samplers, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteSamplers(int count, Androidapi::Jni::Javatypes::_di_JIntBuffer samplers) = 0 /* overload */;
	virtual void __cdecl glDeleteSync(__int64 sync) = 0 ;
	virtual void __cdecl glDeleteTransformFeedbacks(int n, Androidapi::Jnibridge::TJavaArray__1<int>* ids, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteTransformFeedbacks(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer ids) = 0 /* overload */;
	virtual void __cdecl glDeleteVertexArrays(int n, Androidapi::Jnibridge::TJavaArray__1<int>* arrays, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteVertexArrays(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer arrays) = 0 /* overload */;
	virtual void __cdecl glDrawArraysInstanced(int mode, int first, int count, int instanceCount) = 0 ;
	virtual void __cdecl glDrawBuffers(int n, Androidapi::Jnibridge::TJavaArray__1<int>* bufs, int offset) = 0 /* overload */;
	virtual void __cdecl glDrawBuffers(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer bufs) = 0 /* overload */;
	virtual void __cdecl glDrawElementsInstanced(int mode, int count, int type_, Androidapi::Jni::Javatypes::_di_JBuffer indices, int instanceCount) = 0 /* overload */;
	virtual void __cdecl glDrawElementsInstanced(int mode, int count, int type_, int indicesOffset, int instanceCount) = 0 /* overload */;
	virtual void __cdecl glDrawRangeElements(int mode, int start, int end_, int count, int type_, Androidapi::Jni::Javatypes::_di_JBuffer indices) = 0 /* overload */;
	virtual void __cdecl glDrawRangeElements(int mode, int start, int end_, int count, int type_, int offset) = 0 /* overload */;
	virtual void __cdecl glEndQuery(int target) = 0 ;
	virtual void __cdecl glEndTransformFeedback() = 0 ;
	virtual __int64 __cdecl glFenceSync(int condition, int flags) = 0 ;
	virtual void __cdecl glFlushMappedBufferRange(int target, int offset, int length) = 0 ;
	virtual void __cdecl glFramebufferTextureLayer(int target, int attachment, int texture, int level, int layer) = 0 ;
	virtual void __cdecl glGenQueries(int n, Androidapi::Jnibridge::TJavaArray__1<int>* ids, int offset) = 0 /* overload */;
	virtual void __cdecl glGenQueries(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer ids) = 0 /* overload */;
	virtual void __cdecl glGenSamplers(int count, Androidapi::Jnibridge::TJavaArray__1<int>* samplers, int offset) = 0 /* overload */;
	virtual void __cdecl glGenSamplers(int count, Androidapi::Jni::Javatypes::_di_JIntBuffer samplers) = 0 /* overload */;
	virtual void __cdecl glGenTransformFeedbacks(int n, Androidapi::Jnibridge::TJavaArray__1<int>* ids, int offset) = 0 /* overload */;
	virtual void __cdecl glGenTransformFeedbacks(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer ids) = 0 /* overload */;
	virtual void __cdecl glGenVertexArrays(int n, Androidapi::Jnibridge::TJavaArray__1<int>* arrays, int offset) = 0 /* overload */;
	virtual void __cdecl glGenVertexArrays(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer arrays) = 0 /* overload */;
	virtual void __cdecl glGetActiveUniformBlockName(int program_, int uniformBlockIndex, int bufSize, Androidapi::Jnibridge::TJavaArray__1<int>* length, int lengthOffset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* uniformBlockName, int uniformBlockNameOffset) = 0 /* overload */;
	virtual void __cdecl glGetActiveUniformBlockName(int program_, int uniformBlockIndex, Androidapi::Jni::Javatypes::_di_JBuffer length, Androidapi::Jni::Javatypes::_di_JBuffer uniformBlockName) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetActiveUniformBlockName(int program_, int uniformBlockIndex) = 0 /* overload */;
	virtual void __cdecl glGetActiveUniformBlockiv(int program_, int uniformBlockIndex, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetActiveUniformBlockiv(int program_, int uniformBlockIndex, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetActiveUniformsiv(int program_, int uniformCount, Androidapi::Jnibridge::TJavaArray__1<int>* uniformIndices, int uniformIndicesOffset, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int paramsOffset) = 0 /* overload */;
	virtual void __cdecl glGetActiveUniformsiv(int program_, int uniformCount, Androidapi::Jni::Javatypes::_di_JIntBuffer uniformIndices, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetBufferParameteri64v(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<__int64>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetBufferParameteri64v(int target, int pname, Androidapi::Jni::Javatypes::_di_JLongBuffer params) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JBuffer __cdecl glGetBufferPointerv(int target, int pname) = 0 ;
	virtual int __cdecl glGetFragDataLocation(int program_, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual void __cdecl glGetInteger64i_v(int target, int index, Androidapi::Jnibridge::TJavaArray__1<__int64>* data, int offset) = 0 /* overload */;
	virtual void __cdecl glGetInteger64i_v(int target, int index, Androidapi::Jni::Javatypes::_di_JLongBuffer data) = 0 /* overload */;
	virtual void __cdecl glGetInteger64v(int pname, Androidapi::Jnibridge::TJavaArray__1<__int64>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetInteger64v(int pname, Androidapi::Jni::Javatypes::_di_JLongBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetIntegeri_v(int target, int index, Androidapi::Jnibridge::TJavaArray__1<int>* data, int offset) = 0 /* overload */;
	virtual void __cdecl glGetIntegeri_v(int target, int index, Androidapi::Jni::Javatypes::_di_JIntBuffer data) = 0 /* overload */;
	virtual void __cdecl glGetInternalformativ(int target, int internalformat, int pname, int bufSize, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetInternalformativ(int target, int internalformat, int pname, int bufSize, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetProgramBinary(int program_, int bufSize, Androidapi::Jnibridge::TJavaArray__1<int>* length, int lengthOffset, Androidapi::Jnibridge::TJavaArray__1<int>* binaryFormat, int binaryFormatOffset, Androidapi::Jni::Javatypes::_di_JBuffer binary) = 0 /* overload */;
	virtual void __cdecl glGetProgramBinary(int program_, int bufSize, Androidapi::Jni::Javatypes::_di_JIntBuffer length, Androidapi::Jni::Javatypes::_di_JIntBuffer binaryFormat, Androidapi::Jni::Javatypes::_di_JBuffer binary) = 0 /* overload */;
	virtual void __cdecl glGetQueryObjectuiv(int id, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetQueryObjectuiv(int id, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetQueryiv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetQueryiv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetSamplerParameterfv(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetSamplerParameterfv(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetSamplerParameteriv(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetSamplerParameteriv(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetStringi(int name, int index) = 0 ;
	virtual void __cdecl glGetSynciv(__int64 sync, int pname, int bufSize, Androidapi::Jnibridge::TJavaArray__1<int>* length, int lengthOffset, Androidapi::Jnibridge::TJavaArray__1<int>* values, int valuesOffset) = 0 /* overload */;
	virtual void __cdecl glGetSynciv(__int64 sync, int pname, int bufSize, Androidapi::Jni::Javatypes::_di_JIntBuffer length, Androidapi::Jni::Javatypes::_di_JIntBuffer values) = 0 /* overload */;
	virtual void __cdecl glGetTransformFeedbackVarying(int program_, int index, int bufsize, Androidapi::Jnibridge::TJavaArray__1<int>* length, int lengthOffset, Androidapi::Jnibridge::TJavaArray__1<int>* size, int sizeOffset, Androidapi::Jnibridge::TJavaArray__1<int>* type_, int typeOffset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* name, int nameOffset) = 0 /* overload */;
	virtual void __cdecl glGetTransformFeedbackVarying(int program_, int index, int bufsize, Androidapi::Jni::Javatypes::_di_JIntBuffer length, Androidapi::Jni::Javatypes::_di_JIntBuffer size, Androidapi::Jni::Javatypes::_di_JIntBuffer type_, System::Byte name) = 0 /* overload */;
	virtual void __cdecl glGetTransformFeedbackVarying(int program_, int index, int bufsize, Androidapi::Jni::Javatypes::_di_JIntBuffer length, Androidapi::Jni::Javatypes::_di_JIntBuffer size, Androidapi::Jni::Javatypes::_di_JIntBuffer type_, Androidapi::Jni::Javatypes::_di_JByteBuffer name) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetTransformFeedbackVarying(int program_, int index, Androidapi::Jnibridge::TJavaArray__1<int>* size, int sizeOffset, Androidapi::Jnibridge::TJavaArray__1<int>* type_, int typeOffset) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetTransformFeedbackVarying(int program_, int index, Androidapi::Jni::Javatypes::_di_JIntBuffer size, Androidapi::Jni::Javatypes::_di_JIntBuffer type_) = 0 /* overload */;
	virtual int __cdecl glGetUniformBlockIndex(int program_, Androidapi::Jni::Javatypes::_di_JString uniformBlockName) = 0 ;
	virtual void __cdecl glGetUniformIndices(int program_, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* uniformNames, Androidapi::Jnibridge::TJavaArray__1<int>* uniformIndices, int uniformIndicesOffset) = 0 /* overload */;
	virtual void __cdecl glGetUniformIndices(int program_, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* uniformNames, Androidapi::Jni::Javatypes::_di_JIntBuffer uniformIndices) = 0 /* overload */;
	virtual void __cdecl glGetUniformuiv(int program_, int location, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetUniformuiv(int program_, int location, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetVertexAttribIiv(int index, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetVertexAttribIiv(int index, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetVertexAttribIuiv(int index, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetVertexAttribIuiv(int index, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glInvalidateFramebuffer(int target, int numAttachments, Androidapi::Jnibridge::TJavaArray__1<int>* attachments, int offset) = 0 /* overload */;
	virtual void __cdecl glInvalidateFramebuffer(int target, int numAttachments, Androidapi::Jni::Javatypes::_di_JIntBuffer attachments) = 0 /* overload */;
	virtual void __cdecl glInvalidateSubFramebuffer(int target, int numAttachments, Androidapi::Jnibridge::TJavaArray__1<int>* attachments, int offset, int x, int y, int width, int height) = 0 /* overload */;
	virtual void __cdecl glInvalidateSubFramebuffer(int target, int numAttachments, Androidapi::Jni::Javatypes::_di_JIntBuffer attachments, int x, int y, int width, int height) = 0 /* overload */;
	virtual bool __cdecl glIsQuery(int id) = 0 ;
	virtual bool __cdecl glIsSampler(int sampler) = 0 ;
	virtual bool __cdecl glIsSync(__int64 sync) = 0 ;
	virtual bool __cdecl glIsTransformFeedback(int id) = 0 ;
	virtual bool __cdecl glIsVertexArray(int array_) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JBuffer __cdecl glMapBufferRange(int target, int offset, int length, int access) = 0 ;
	virtual void __cdecl glPauseTransformFeedback() = 0 ;
	virtual void __cdecl glProgramBinary(int program_, int binaryFormat, Androidapi::Jni::Javatypes::_di_JBuffer binary, int length) = 0 ;
	virtual void __cdecl glProgramParameteri(int program_, int pname, int value) = 0 ;
	virtual void __cdecl glReadBuffer(int mode) = 0 ;
	HIDESBASE virtual void __cdecl glReadPixels(int x, int y, int width, int height, int format, int type_, int offset) = 0 ;
	virtual void __cdecl glRenderbufferStorageMultisample(int target, int samples, int internalformat, int width, int height) = 0 ;
	virtual void __cdecl glResumeTransformFeedback() = 0 ;
	virtual void __cdecl glSamplerParameterf(int sampler, int pname, float param) = 0 ;
	virtual void __cdecl glSamplerParameterfv(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* param, int offset) = 0 /* overload */;
	virtual void __cdecl glSamplerParameterfv(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer param) = 0 /* overload */;
	virtual void __cdecl glSamplerParameteri(int sampler, int pname, int param) = 0 ;
	virtual void __cdecl glSamplerParameteriv(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* param, int offset) = 0 /* overload */;
	virtual void __cdecl glSamplerParameteriv(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer param) = 0 /* overload */;
	virtual void __cdecl glTexImage3D(int target, int level, int internalformat, int width, int height, int depth, int border, int format, int type_, Androidapi::Jni::Javatypes::_di_JBuffer pixels) = 0 /* overload */;
	virtual void __cdecl glTexImage3D(int target, int level, int internalformat, int width, int height, int depth, int border, int format, int type_, int offset) = 0 /* overload */;
	virtual void __cdecl glTexStorage2D(int target, int levels, int internalformat, int width, int height) = 0 ;
	virtual void __cdecl glTexStorage3D(int target, int levels, int internalformat, int width, int height, int depth) = 0 ;
	virtual void __cdecl glTexSubImage3D(int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, int format, int type_, Androidapi::Jni::Javatypes::_di_JBuffer pixels) = 0 /* overload */;
	virtual void __cdecl glTexSubImage3D(int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, int format, int type_, int offset) = 0 /* overload */;
	virtual void __cdecl glTransformFeedbackVaryings(int program_, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* varyings, int bufferMode) = 0 ;
	virtual void __cdecl glUniform1ui(int location, int v0) = 0 ;
	virtual void __cdecl glUniform1uiv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform1uiv(int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glUniform2ui(int location, int v0, int v1) = 0 ;
	virtual void __cdecl glUniform2uiv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform2uiv(int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glUniform3ui(int location, int v0, int v1, int v2) = 0 ;
	virtual void __cdecl glUniform3uiv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform3uiv(int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glUniform4ui(int location, int v0, int v1, int v2, int v3) = 0 ;
	virtual void __cdecl glUniform4uiv(int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniform4uiv(int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glUniformBlockBinding(int program_, int uniformBlockIndex, int uniformBlockBinding) = 0 ;
	virtual void __cdecl glUniformMatrix2x3fv(int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix2x3fv(int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix2x4fv(int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix2x4fv(int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix3x2fv(int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix3x2fv(int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix3x4fv(int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix3x4fv(int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix4x2fv(int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix4x2fv(int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix4x3fv(int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glUniformMatrix4x3fv(int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual bool __cdecl glUnmapBuffer(int target) = 0 ;
	virtual void __cdecl glVertexAttribDivisor(int index, int divisor) = 0 ;
	virtual void __cdecl glVertexAttribI4i(int index, int x, int y, int z, int w) = 0 ;
	virtual void __cdecl glVertexAttribI4iv(int index, Androidapi::Jnibridge::TJavaArray__1<int>* v, int offset) = 0 /* overload */;
	virtual void __cdecl glVertexAttribI4iv(int index, Androidapi::Jni::Javatypes::_di_JIntBuffer v) = 0 /* overload */;
	virtual void __cdecl glVertexAttribI4ui(int index, int x, int y, int z, int w) = 0 ;
	virtual void __cdecl glVertexAttribI4uiv(int index, Androidapi::Jnibridge::TJavaArray__1<int>* v, int offset) = 0 /* overload */;
	virtual void __cdecl glVertexAttribI4uiv(int index, Androidapi::Jni::Javatypes::_di_JIntBuffer v) = 0 /* overload */;
	virtual void __cdecl glVertexAttribIPointer(int index, int size, int type_, int stride, Androidapi::Jni::Javatypes::_di_JBuffer pointer) = 0 /* overload */;
	virtual void __cdecl glVertexAttribIPointer(int index, int size, int type_, int stride, int offset) = 0 /* overload */;
	virtual void __cdecl glWaitSync(__int64 sync, int flags, __int64 timeout) = 0 ;
	__property int GL_ACTIVE_UNIFORM_BLOCKS = {read=_GetGL_ACTIVE_UNIFORM_BLOCKS};
	__property int GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH = {read=_GetGL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH};
	__property int GL_ALREADY_SIGNALED = {read=_GetGL_ALREADY_SIGNALED};
	__property int GL_ANY_SAMPLES_PASSED = {read=_GetGL_ANY_SAMPLES_PASSED};
	__property int GL_ANY_SAMPLES_PASSED_CONSERVATIVE = {read=_GetGL_ANY_SAMPLES_PASSED_CONSERVATIVE};
	__property int GL_BLUE = {read=_GetGL_BLUE};
	__property int GL_BUFFER_ACCESS_FLAGS = {read=_GetGL_BUFFER_ACCESS_FLAGS};
	__property int GL_BUFFER_MAPPED = {read=_GetGL_BUFFER_MAPPED};
	__property int GL_BUFFER_MAP_LENGTH = {read=_GetGL_BUFFER_MAP_LENGTH};
	__property int GL_BUFFER_MAP_OFFSET = {read=_GetGL_BUFFER_MAP_OFFSET};
	__property int GL_BUFFER_MAP_POINTER = {read=_GetGL_BUFFER_MAP_POINTER};
	__property int GL_COLOR = {read=_GetGL_COLOR};
	__property int GL_COLOR_ATTACHMENT1 = {read=_GetGL_COLOR_ATTACHMENT1};
	__property int GL_COLOR_ATTACHMENT10 = {read=_GetGL_COLOR_ATTACHMENT10};
	__property int GL_COLOR_ATTACHMENT11 = {read=_GetGL_COLOR_ATTACHMENT11};
	__property int GL_COLOR_ATTACHMENT12 = {read=_GetGL_COLOR_ATTACHMENT12};
	__property int GL_COLOR_ATTACHMENT13 = {read=_GetGL_COLOR_ATTACHMENT13};
	__property int GL_COLOR_ATTACHMENT14 = {read=_GetGL_COLOR_ATTACHMENT14};
	__property int GL_COLOR_ATTACHMENT15 = {read=_GetGL_COLOR_ATTACHMENT15};
	__property int GL_COLOR_ATTACHMENT2 = {read=_GetGL_COLOR_ATTACHMENT2};
	__property int GL_COLOR_ATTACHMENT3 = {read=_GetGL_COLOR_ATTACHMENT3};
	__property int GL_COLOR_ATTACHMENT4 = {read=_GetGL_COLOR_ATTACHMENT4};
	__property int GL_COLOR_ATTACHMENT5 = {read=_GetGL_COLOR_ATTACHMENT5};
	__property int GL_COLOR_ATTACHMENT6 = {read=_GetGL_COLOR_ATTACHMENT6};
	__property int GL_COLOR_ATTACHMENT7 = {read=_GetGL_COLOR_ATTACHMENT7};
	__property int GL_COLOR_ATTACHMENT8 = {read=_GetGL_COLOR_ATTACHMENT8};
	__property int GL_COLOR_ATTACHMENT9 = {read=_GetGL_COLOR_ATTACHMENT9};
	__property int GL_COMPARE_REF_TO_TEXTURE = {read=_GetGL_COMPARE_REF_TO_TEXTURE};
	__property int GL_COMPRESSED_R11_EAC = {read=_GetGL_COMPRESSED_R11_EAC};
	__property int GL_COMPRESSED_RG11_EAC = {read=_GetGL_COMPRESSED_RG11_EAC};
	__property int GL_COMPRESSED_RGB8_ETC2 = {read=_GetGL_COMPRESSED_RGB8_ETC2};
	__property int GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 = {read=_GetGL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2};
	__property int GL_COMPRESSED_RGBA8_ETC2_EAC = {read=_GetGL_COMPRESSED_RGBA8_ETC2_EAC};
	__property int GL_COMPRESSED_SIGNED_R11_EAC = {read=_GetGL_COMPRESSED_SIGNED_R11_EAC};
	__property int GL_COMPRESSED_SIGNED_RG11_EAC = {read=_GetGL_COMPRESSED_SIGNED_RG11_EAC};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC};
	__property int GL_COMPRESSED_SRGB8_ETC2 = {read=_GetGL_COMPRESSED_SRGB8_ETC2};
	__property int GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 = {read=_GetGL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2};
	__property int GL_CONDITION_SATISFIED = {read=_GetGL_CONDITION_SATISFIED};
	__property int GL_COPY_READ_BUFFER = {read=_GetGL_COPY_READ_BUFFER};
	__property int GL_COPY_READ_BUFFER_BINDING = {read=_GetGL_COPY_READ_BUFFER_BINDING};
	__property int GL_COPY_WRITE_BUFFER = {read=_GetGL_COPY_WRITE_BUFFER};
	__property int GL_COPY_WRITE_BUFFER_BINDING = {read=_GetGL_COPY_WRITE_BUFFER_BINDING};
	__property int GL_CURRENT_QUERY = {read=_GetGL_CURRENT_QUERY};
	__property int GL_DEPTH = {read=_GetGL_DEPTH};
	__property int GL_DEPTH24_STENCIL8 = {read=_GetGL_DEPTH24_STENCIL8};
	__property int GL_DEPTH32F_STENCIL8 = {read=_GetGL_DEPTH32F_STENCIL8};
	__property int GL_DEPTH_COMPONENT24 = {read=_GetGL_DEPTH_COMPONENT24};
	__property int GL_DEPTH_COMPONENT32F = {read=_GetGL_DEPTH_COMPONENT32F};
	__property int GL_DEPTH_STENCIL = {read=_GetGL_DEPTH_STENCIL};
	__property int GL_DEPTH_STENCIL_ATTACHMENT = {read=_GetGL_DEPTH_STENCIL_ATTACHMENT};
	__property int GL_DRAW_BUFFER0 = {read=_GetGL_DRAW_BUFFER0};
	__property int GL_DRAW_BUFFER1 = {read=_GetGL_DRAW_BUFFER1};
	__property int GL_DRAW_BUFFER10 = {read=_GetGL_DRAW_BUFFER10};
	__property int GL_DRAW_BUFFER11 = {read=_GetGL_DRAW_BUFFER11};
	__property int GL_DRAW_BUFFER12 = {read=_GetGL_DRAW_BUFFER12};
	__property int GL_DRAW_BUFFER13 = {read=_GetGL_DRAW_BUFFER13};
	__property int GL_DRAW_BUFFER14 = {read=_GetGL_DRAW_BUFFER14};
	__property int GL_DRAW_BUFFER15 = {read=_GetGL_DRAW_BUFFER15};
	__property int GL_DRAW_BUFFER2 = {read=_GetGL_DRAW_BUFFER2};
	__property int GL_DRAW_BUFFER3 = {read=_GetGL_DRAW_BUFFER3};
	__property int GL_DRAW_BUFFER4 = {read=_GetGL_DRAW_BUFFER4};
	__property int GL_DRAW_BUFFER5 = {read=_GetGL_DRAW_BUFFER5};
	__property int GL_DRAW_BUFFER6 = {read=_GetGL_DRAW_BUFFER6};
	__property int GL_DRAW_BUFFER7 = {read=_GetGL_DRAW_BUFFER7};
	__property int GL_DRAW_BUFFER8 = {read=_GetGL_DRAW_BUFFER8};
	__property int GL_DRAW_BUFFER9 = {read=_GetGL_DRAW_BUFFER9};
	__property int GL_DRAW_FRAMEBUFFER = {read=_GetGL_DRAW_FRAMEBUFFER};
	__property int GL_DRAW_FRAMEBUFFER_BINDING = {read=_GetGL_DRAW_FRAMEBUFFER_BINDING};
	__property int GL_DYNAMIC_COPY = {read=_GetGL_DYNAMIC_COPY};
	__property int GL_DYNAMIC_READ = {read=_GetGL_DYNAMIC_READ};
	__property int GL_FLOAT_32_UNSIGNED_INT_24_8_REV = {read=_GetGL_FLOAT_32_UNSIGNED_INT_24_8_REV};
	__property int GL_FLOAT_MAT2x3 = {read=_GetGL_FLOAT_MAT2x3};
	__property int GL_FLOAT_MAT2x4 = {read=_GetGL_FLOAT_MAT2x4};
	__property int GL_FLOAT_MAT3x2 = {read=_GetGL_FLOAT_MAT3x2};
	__property int GL_FLOAT_MAT3x4 = {read=_GetGL_FLOAT_MAT3x4};
	__property int GL_FLOAT_MAT4x2 = {read=_GetGL_FLOAT_MAT4x2};
	__property int GL_FLOAT_MAT4x3 = {read=_GetGL_FLOAT_MAT4x3};
	__property int GL_FRAGMENT_SHADER_DERIVATIVE_HINT = {read=_GetGL_FRAGMENT_SHADER_DERIVATIVE_HINT};
	__property int GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE};
	__property int GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE};
	__property int GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING};
	__property int GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE};
	__property int GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE};
	__property int GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE};
	__property int GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_RED_SIZE};
	__property int GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE};
	__property int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER};
	__property int GL_FRAMEBUFFER_DEFAULT = {read=_GetGL_FRAMEBUFFER_DEFAULT};
	__property int GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE = {read=_GetGL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE};
	__property int GL_FRAMEBUFFER_UNDEFINED = {read=_GetGL_FRAMEBUFFER_UNDEFINED};
	__property int GL_GREEN = {read=_GetGL_GREEN};
	__property int GL_HALF_FLOAT = {read=_GetGL_HALF_FLOAT};
	__property int GL_INTERLEAVED_ATTRIBS = {read=_GetGL_INTERLEAVED_ATTRIBS};
	__property int GL_INT_2_10_10_10_REV = {read=_GetGL_INT_2_10_10_10_REV};
	__property int GL_INT_SAMPLER_2D = {read=_GetGL_INT_SAMPLER_2D};
	__property int GL_INT_SAMPLER_2D_ARRAY = {read=_GetGL_INT_SAMPLER_2D_ARRAY};
	__property int GL_INT_SAMPLER_3D = {read=_GetGL_INT_SAMPLER_3D};
	__property int GL_INT_SAMPLER_CUBE = {read=_GetGL_INT_SAMPLER_CUBE};
	__property int GL_INVALID_INDEX = {read=_GetGL_INVALID_INDEX};
	__property int GL_MAJOR_VERSION = {read=_GetGL_MAJOR_VERSION};
	__property int GL_MAP_FLUSH_EXPLICIT_BIT = {read=_GetGL_MAP_FLUSH_EXPLICIT_BIT};
	__property int GL_MAP_INVALIDATE_BUFFER_BIT = {read=_GetGL_MAP_INVALIDATE_BUFFER_BIT};
	__property int GL_MAP_INVALIDATE_RANGE_BIT = {read=_GetGL_MAP_INVALIDATE_RANGE_BIT};
	__property int GL_MAP_READ_BIT = {read=_GetGL_MAP_READ_BIT};
	__property int GL_MAP_UNSYNCHRONIZED_BIT = {read=_GetGL_MAP_UNSYNCHRONIZED_BIT};
	__property int GL_MAP_WRITE_BIT = {read=_GetGL_MAP_WRITE_BIT};
	__property int GL_MAX = {read=_GetGL_MAX};
	__property int GL_MAX_3D_TEXTURE_SIZE = {read=_GetGL_MAX_3D_TEXTURE_SIZE};
	__property int GL_MAX_ARRAY_TEXTURE_LAYERS = {read=_GetGL_MAX_ARRAY_TEXTURE_LAYERS};
	__property int GL_MAX_COLOR_ATTACHMENTS = {read=_GetGL_MAX_COLOR_ATTACHMENTS};
	__property int GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS = {read=_GetGL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS};
	__property int GL_MAX_COMBINED_UNIFORM_BLOCKS = {read=_GetGL_MAX_COMBINED_UNIFORM_BLOCKS};
	__property int GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS = {read=_GetGL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS};
	__property int GL_MAX_DRAW_BUFFERS = {read=_GetGL_MAX_DRAW_BUFFERS};
	__property int GL_MAX_ELEMENTS_INDICES = {read=_GetGL_MAX_ELEMENTS_INDICES};
	__property int GL_MAX_ELEMENTS_VERTICES = {read=_GetGL_MAX_ELEMENTS_VERTICES};
	__property int GL_MAX_ELEMENT_INDEX = {read=_GetGL_MAX_ELEMENT_INDEX};
	__property int GL_MAX_FRAGMENT_INPUT_COMPONENTS = {read=_GetGL_MAX_FRAGMENT_INPUT_COMPONENTS};
	__property int GL_MAX_FRAGMENT_UNIFORM_BLOCKS = {read=_GetGL_MAX_FRAGMENT_UNIFORM_BLOCKS};
	__property int GL_MAX_FRAGMENT_UNIFORM_COMPONENTS = {read=_GetGL_MAX_FRAGMENT_UNIFORM_COMPONENTS};
	__property int GL_MAX_PROGRAM_TEXEL_OFFSET = {read=_GetGL_MAX_PROGRAM_TEXEL_OFFSET};
	__property int GL_MAX_SAMPLES = {read=_GetGL_MAX_SAMPLES};
	__property int GL_MAX_SERVER_WAIT_TIMEOUT = {read=_GetGL_MAX_SERVER_WAIT_TIMEOUT};
	__property int GL_MAX_TEXTURE_LOD_BIAS = {read=_GetGL_MAX_TEXTURE_LOD_BIAS};
	__property int GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS = {read=_GetGL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS};
	__property int GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS = {read=_GetGL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS};
	__property int GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS = {read=_GetGL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS};
	__property int GL_MAX_UNIFORM_BLOCK_SIZE = {read=_GetGL_MAX_UNIFORM_BLOCK_SIZE};
	__property int GL_MAX_UNIFORM_BUFFER_BINDINGS = {read=_GetGL_MAX_UNIFORM_BUFFER_BINDINGS};
	__property int GL_MAX_VARYING_COMPONENTS = {read=_GetGL_MAX_VARYING_COMPONENTS};
	__property int GL_MAX_VERTEX_OUTPUT_COMPONENTS = {read=_GetGL_MAX_VERTEX_OUTPUT_COMPONENTS};
	__property int GL_MAX_VERTEX_UNIFORM_BLOCKS = {read=_GetGL_MAX_VERTEX_UNIFORM_BLOCKS};
	__property int GL_MAX_VERTEX_UNIFORM_COMPONENTS = {read=_GetGL_MAX_VERTEX_UNIFORM_COMPONENTS};
	__property int GL_MIN = {read=_GetGL_MIN};
	__property int GL_MINOR_VERSION = {read=_GetGL_MINOR_VERSION};
	__property int GL_MIN_PROGRAM_TEXEL_OFFSET = {read=_GetGL_MIN_PROGRAM_TEXEL_OFFSET};
	__property int GL_NUM_EXTENSIONS = {read=_GetGL_NUM_EXTENSIONS};
	__property int GL_NUM_PROGRAM_BINARY_FORMATS = {read=_GetGL_NUM_PROGRAM_BINARY_FORMATS};
	__property int GL_NUM_SAMPLE_COUNTS = {read=_GetGL_NUM_SAMPLE_COUNTS};
	__property int GL_OBJECT_TYPE = {read=_GetGL_OBJECT_TYPE};
	__property int GL_PACK_ROW_LENGTH = {read=_GetGL_PACK_ROW_LENGTH};
	__property int GL_PACK_SKIP_PIXELS = {read=_GetGL_PACK_SKIP_PIXELS};
	__property int GL_PACK_SKIP_ROWS = {read=_GetGL_PACK_SKIP_ROWS};
	__property int GL_PIXEL_PACK_BUFFER = {read=_GetGL_PIXEL_PACK_BUFFER};
	__property int GL_PIXEL_PACK_BUFFER_BINDING = {read=_GetGL_PIXEL_PACK_BUFFER_BINDING};
	__property int GL_PIXEL_UNPACK_BUFFER = {read=_GetGL_PIXEL_UNPACK_BUFFER};
	__property int GL_PIXEL_UNPACK_BUFFER_BINDING = {read=_GetGL_PIXEL_UNPACK_BUFFER_BINDING};
	__property int GL_PRIMITIVE_RESTART_FIXED_INDEX = {read=_GetGL_PRIMITIVE_RESTART_FIXED_INDEX};
	__property int GL_PROGRAM_BINARY_FORMATS = {read=_GetGL_PROGRAM_BINARY_FORMATS};
	__property int GL_PROGRAM_BINARY_LENGTH = {read=_GetGL_PROGRAM_BINARY_LENGTH};
	__property int GL_PROGRAM_BINARY_RETRIEVABLE_HINT = {read=_GetGL_PROGRAM_BINARY_RETRIEVABLE_HINT};
	__property int GL_QUERY_RESULT = {read=_GetGL_QUERY_RESULT};
	__property int GL_QUERY_RESULT_AVAILABLE = {read=_GetGL_QUERY_RESULT_AVAILABLE};
	__property int GL_R11F_G11F_B10F = {read=_GetGL_R11F_G11F_B10F};
	__property int GL_R16F = {read=_GetGL_R16F};
	__property int GL_R16I = {read=_GetGL_R16I};
	__property int GL_R16UI = {read=_GetGL_R16UI};
	__property int GL_R32F = {read=_GetGL_R32F};
	__property int GL_R32I = {read=_GetGL_R32I};
	__property int GL_R32UI = {read=_GetGL_R32UI};
	__property int GL_R8 = {read=_GetGL_R8};
	__property int GL_R8I = {read=_GetGL_R8I};
	__property int GL_R8UI = {read=_GetGL_R8UI};
	__property int GL_R8_SNORM = {read=_GetGL_R8_SNORM};
	__property int GL_RASTERIZER_DISCARD = {read=_GetGL_RASTERIZER_DISCARD};
	__property int GL_READ_BUFFER = {read=_GetGL_READ_BUFFER};
	__property int GL_READ_FRAMEBUFFER = {read=_GetGL_READ_FRAMEBUFFER};
	__property int GL_READ_FRAMEBUFFER_BINDING = {read=_GetGL_READ_FRAMEBUFFER_BINDING};
	__property int GL_RED = {read=_GetGL_RED};
	__property int GL_RED_INTEGER = {read=_GetGL_RED_INTEGER};
	__property int GL_RENDERBUFFER_SAMPLES = {read=_GetGL_RENDERBUFFER_SAMPLES};
	__property int GL_RG = {read=_GetGL_RG};
	__property int GL_RG16F = {read=_GetGL_RG16F};
	__property int GL_RG16I = {read=_GetGL_RG16I};
	__property int GL_RG16UI = {read=_GetGL_RG16UI};
	__property int GL_RG32F = {read=_GetGL_RG32F};
	__property int GL_RG32I = {read=_GetGL_RG32I};
	__property int GL_RG32UI = {read=_GetGL_RG32UI};
	__property int GL_RG8 = {read=_GetGL_RG8};
	__property int GL_RG8I = {read=_GetGL_RG8I};
	__property int GL_RG8UI = {read=_GetGL_RG8UI};
	__property int GL_RG8_SNORM = {read=_GetGL_RG8_SNORM};
	__property int GL_RGB10_A2 = {read=_GetGL_RGB10_A2};
	__property int GL_RGB10_A2UI = {read=_GetGL_RGB10_A2UI};
	__property int GL_RGB16F = {read=_GetGL_RGB16F};
	__property int GL_RGB16I = {read=_GetGL_RGB16I};
	__property int GL_RGB16UI = {read=_GetGL_RGB16UI};
	__property int GL_RGB32F = {read=_GetGL_RGB32F};
	__property int GL_RGB32I = {read=_GetGL_RGB32I};
	__property int GL_RGB32UI = {read=_GetGL_RGB32UI};
	__property int GL_RGB8 = {read=_GetGL_RGB8};
	__property int GL_RGB8I = {read=_GetGL_RGB8I};
	__property int GL_RGB8UI = {read=_GetGL_RGB8UI};
	__property int GL_RGB8_SNORM = {read=_GetGL_RGB8_SNORM};
	__property int GL_RGB9_E5 = {read=_GetGL_RGB9_E5};
	__property int GL_RGBA16F = {read=_GetGL_RGBA16F};
	__property int GL_RGBA16I = {read=_GetGL_RGBA16I};
	__property int GL_RGBA16UI = {read=_GetGL_RGBA16UI};
	__property int GL_RGBA32F = {read=_GetGL_RGBA32F};
	__property int GL_RGBA32I = {read=_GetGL_RGBA32I};
	__property int GL_RGBA32UI = {read=_GetGL_RGBA32UI};
	__property int GL_RGBA8 = {read=_GetGL_RGBA8};
	__property int GL_RGBA8I = {read=_GetGL_RGBA8I};
	__property int GL_RGBA8UI = {read=_GetGL_RGBA8UI};
	__property int GL_RGBA8_SNORM = {read=_GetGL_RGBA8_SNORM};
	__property int GL_RGBA_INTEGER = {read=_GetGL_RGBA_INTEGER};
	__property int GL_RGB_INTEGER = {read=_GetGL_RGB_INTEGER};
	__property int GL_RG_INTEGER = {read=_GetGL_RG_INTEGER};
	__property int GL_SAMPLER_2D_ARRAY = {read=_GetGL_SAMPLER_2D_ARRAY};
	__property int GL_SAMPLER_2D_ARRAY_SHADOW = {read=_GetGL_SAMPLER_2D_ARRAY_SHADOW};
	__property int GL_SAMPLER_2D_SHADOW = {read=_GetGL_SAMPLER_2D_SHADOW};
	__property int GL_SAMPLER_3D = {read=_GetGL_SAMPLER_3D};
	__property int GL_SAMPLER_BINDING = {read=_GetGL_SAMPLER_BINDING};
	__property int GL_SAMPLER_CUBE_SHADOW = {read=_GetGL_SAMPLER_CUBE_SHADOW};
	__property int GL_SEPARATE_ATTRIBS = {read=_GetGL_SEPARATE_ATTRIBS};
	__property int GL_SIGNALED = {read=_GetGL_SIGNALED};
	__property int GL_SIGNED_NORMALIZED = {read=_GetGL_SIGNED_NORMALIZED};
	__property int GL_SRGB = {read=_GetGL_SRGB};
	__property int GL_SRGB8 = {read=_GetGL_SRGB8};
	__property int GL_SRGB8_ALPHA8 = {read=_GetGL_SRGB8_ALPHA8};
	__property int GL_STATIC_COPY = {read=_GetGL_STATIC_COPY};
	__property int GL_STATIC_READ = {read=_GetGL_STATIC_READ};
	__property int GL_STENCIL = {read=_GetGL_STENCIL};
	__property int GL_STREAM_COPY = {read=_GetGL_STREAM_COPY};
	__property int GL_STREAM_READ = {read=_GetGL_STREAM_READ};
	__property int GL_SYNC_CONDITION = {read=_GetGL_SYNC_CONDITION};
	__property int GL_SYNC_FENCE = {read=_GetGL_SYNC_FENCE};
	__property int GL_SYNC_FLAGS = {read=_GetGL_SYNC_FLAGS};
	__property int GL_SYNC_FLUSH_COMMANDS_BIT = {read=_GetGL_SYNC_FLUSH_COMMANDS_BIT};
	__property int GL_SYNC_GPU_COMMANDS_COMPLETE = {read=_GetGL_SYNC_GPU_COMMANDS_COMPLETE};
	__property int GL_SYNC_STATUS = {read=_GetGL_SYNC_STATUS};
	__property int GL_TEXTURE_2D_ARRAY = {read=_GetGL_TEXTURE_2D_ARRAY};
	__property int GL_TEXTURE_3D = {read=_GetGL_TEXTURE_3D};
	__property int GL_TEXTURE_BASE_LEVEL = {read=_GetGL_TEXTURE_BASE_LEVEL};
	__property int GL_TEXTURE_BINDING_2D_ARRAY = {read=_GetGL_TEXTURE_BINDING_2D_ARRAY};
	__property int GL_TEXTURE_BINDING_3D = {read=_GetGL_TEXTURE_BINDING_3D};
	__property int GL_TEXTURE_COMPARE_FUNC = {read=_GetGL_TEXTURE_COMPARE_FUNC};
	__property int GL_TEXTURE_COMPARE_MODE = {read=_GetGL_TEXTURE_COMPARE_MODE};
	__property int GL_TEXTURE_IMMUTABLE_FORMAT = {read=_GetGL_TEXTURE_IMMUTABLE_FORMAT};
	__property int GL_TEXTURE_IMMUTABLE_LEVELS = {read=_GetGL_TEXTURE_IMMUTABLE_LEVELS};
	__property int GL_TEXTURE_MAX_LEVEL = {read=_GetGL_TEXTURE_MAX_LEVEL};
	__property int GL_TEXTURE_MAX_LOD = {read=_GetGL_TEXTURE_MAX_LOD};
	__property int GL_TEXTURE_MIN_LOD = {read=_GetGL_TEXTURE_MIN_LOD};
	__property int GL_TEXTURE_SWIZZLE_A = {read=_GetGL_TEXTURE_SWIZZLE_A};
	__property int GL_TEXTURE_SWIZZLE_B = {read=_GetGL_TEXTURE_SWIZZLE_B};
	__property int GL_TEXTURE_SWIZZLE_G = {read=_GetGL_TEXTURE_SWIZZLE_G};
	__property int GL_TEXTURE_SWIZZLE_R = {read=_GetGL_TEXTURE_SWIZZLE_R};
	__property int GL_TEXTURE_WRAP_R = {read=_GetGL_TEXTURE_WRAP_R};
	__property int GL_TIMEOUT_EXPIRED = {read=_GetGL_TIMEOUT_EXPIRED};
	__property __int64 GL_TIMEOUT_IGNORED = {read=_GetGL_TIMEOUT_IGNORED};
	__property int GL_TRANSFORM_FEEDBACK = {read=_GetGL_TRANSFORM_FEEDBACK};
	__property int GL_TRANSFORM_FEEDBACK_ACTIVE = {read=_GetGL_TRANSFORM_FEEDBACK_ACTIVE};
	__property int GL_TRANSFORM_FEEDBACK_BINDING = {read=_GetGL_TRANSFORM_FEEDBACK_BINDING};
	__property int GL_TRANSFORM_FEEDBACK_BUFFER = {read=_GetGL_TRANSFORM_FEEDBACK_BUFFER};
	__property int GL_TRANSFORM_FEEDBACK_BUFFER_BINDING = {read=_GetGL_TRANSFORM_FEEDBACK_BUFFER_BINDING};
	__property int GL_TRANSFORM_FEEDBACK_BUFFER_MODE = {read=_GetGL_TRANSFORM_FEEDBACK_BUFFER_MODE};
	__property int GL_TRANSFORM_FEEDBACK_BUFFER_SIZE = {read=_GetGL_TRANSFORM_FEEDBACK_BUFFER_SIZE};
	__property int GL_TRANSFORM_FEEDBACK_BUFFER_START = {read=_GetGL_TRANSFORM_FEEDBACK_BUFFER_START};
	__property int GL_TRANSFORM_FEEDBACK_PAUSED = {read=_GetGL_TRANSFORM_FEEDBACK_PAUSED};
	__property int GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN = {read=_GetGL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN};
	__property int GL_TRANSFORM_FEEDBACK_VARYINGS = {read=_GetGL_TRANSFORM_FEEDBACK_VARYINGS};
	__property int GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH = {read=_GetGL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH};
	__property int GL_UNIFORM_ARRAY_STRIDE = {read=_GetGL_UNIFORM_ARRAY_STRIDE};
	__property int GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS = {read=_GetGL_UNIFORM_BLOCK_ACTIVE_UNIFORMS};
	__property int GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES = {read=_GetGL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES};
	__property int GL_UNIFORM_BLOCK_BINDING = {read=_GetGL_UNIFORM_BLOCK_BINDING};
	__property int GL_UNIFORM_BLOCK_DATA_SIZE = {read=_GetGL_UNIFORM_BLOCK_DATA_SIZE};
	__property int GL_UNIFORM_BLOCK_INDEX = {read=_GetGL_UNIFORM_BLOCK_INDEX};
	__property int GL_UNIFORM_BLOCK_NAME_LENGTH = {read=_GetGL_UNIFORM_BLOCK_NAME_LENGTH};
	__property int GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER = {read=_GetGL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER};
	__property int GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER = {read=_GetGL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER};
	__property int GL_UNIFORM_BUFFER = {read=_GetGL_UNIFORM_BUFFER};
	__property int GL_UNIFORM_BUFFER_BINDING = {read=_GetGL_UNIFORM_BUFFER_BINDING};
	__property int GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT = {read=_GetGL_UNIFORM_BUFFER_OFFSET_ALIGNMENT};
	__property int GL_UNIFORM_BUFFER_SIZE = {read=_GetGL_UNIFORM_BUFFER_SIZE};
	__property int GL_UNIFORM_BUFFER_START = {read=_GetGL_UNIFORM_BUFFER_START};
	__property int GL_UNIFORM_IS_ROW_MAJOR = {read=_GetGL_UNIFORM_IS_ROW_MAJOR};
	__property int GL_UNIFORM_MATRIX_STRIDE = {read=_GetGL_UNIFORM_MATRIX_STRIDE};
	__property int GL_UNIFORM_NAME_LENGTH = {read=_GetGL_UNIFORM_NAME_LENGTH};
	__property int GL_UNIFORM_OFFSET = {read=_GetGL_UNIFORM_OFFSET};
	__property int GL_UNIFORM_SIZE = {read=_GetGL_UNIFORM_SIZE};
	__property int GL_UNIFORM_TYPE = {read=_GetGL_UNIFORM_TYPE};
	__property int GL_UNPACK_IMAGE_HEIGHT = {read=_GetGL_UNPACK_IMAGE_HEIGHT};
	__property int GL_UNPACK_ROW_LENGTH = {read=_GetGL_UNPACK_ROW_LENGTH};
	__property int GL_UNPACK_SKIP_IMAGES = {read=_GetGL_UNPACK_SKIP_IMAGES};
	__property int GL_UNPACK_SKIP_PIXELS = {read=_GetGL_UNPACK_SKIP_PIXELS};
	__property int GL_UNPACK_SKIP_ROWS = {read=_GetGL_UNPACK_SKIP_ROWS};
	__property int GL_UNSIGNALED = {read=_GetGL_UNSIGNALED};
	__property int GL_UNSIGNED_INT_10F_11F_11F_REV = {read=_GetGL_UNSIGNED_INT_10F_11F_11F_REV};
	__property int GL_UNSIGNED_INT_24_8 = {read=_GetGL_UNSIGNED_INT_24_8};
	__property int GL_UNSIGNED_INT_2_10_10_10_REV = {read=_GetGL_UNSIGNED_INT_2_10_10_10_REV};
	__property int GL_UNSIGNED_INT_5_9_9_9_REV = {read=_GetGL_UNSIGNED_INT_5_9_9_9_REV};
	__property int GL_UNSIGNED_INT_SAMPLER_2D = {read=_GetGL_UNSIGNED_INT_SAMPLER_2D};
	__property int GL_UNSIGNED_INT_SAMPLER_2D_ARRAY = {read=_GetGL_UNSIGNED_INT_SAMPLER_2D_ARRAY};
	__property int GL_UNSIGNED_INT_SAMPLER_3D = {read=_GetGL_UNSIGNED_INT_SAMPLER_3D};
	__property int GL_UNSIGNED_INT_SAMPLER_CUBE = {read=_GetGL_UNSIGNED_INT_SAMPLER_CUBE};
	__property int GL_UNSIGNED_INT_VEC2 = {read=_GetGL_UNSIGNED_INT_VEC2};
	__property int GL_UNSIGNED_INT_VEC3 = {read=_GetGL_UNSIGNED_INT_VEC3};
	__property int GL_UNSIGNED_INT_VEC4 = {read=_GetGL_UNSIGNED_INT_VEC4};
	__property int GL_UNSIGNED_NORMALIZED = {read=_GetGL_UNSIGNED_NORMALIZED};
	__property int GL_VERTEX_ARRAY_BINDING = {read=_GetGL_VERTEX_ARRAY_BINDING};
	__property int GL_VERTEX_ATTRIB_ARRAY_DIVISOR = {read=_GetGL_VERTEX_ATTRIB_ARRAY_DIVISOR};
	__property int GL_VERTEX_ATTRIB_ARRAY_INTEGER = {read=_GetGL_VERTEX_ATTRIB_ARRAY_INTEGER};
	__property int GL_WAIT_FAILED = {read=_GetGL_WAIT_FAILED};
};

__interface  INTERFACE_UUID("{6254BA09-4979-4CB0-AC26-B0A0D9A01400}") JGLES30  : public JGLES20 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLES30 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES30Class,_di_JGLES30>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES30Class,_di_JGLES30> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLES30() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES30Class,_di_JGLES30>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLES30() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B82E0B3B-6E15-479A-995B-57FFAF6ABDE7}") JGLES31Class  : public JGLES30Class 
{
	virtual int __cdecl _GetGL_ACTIVE_ATOMIC_COUNTER_BUFFERS() = 0 ;
	virtual int __cdecl _GetGL_ACTIVE_PROGRAM() = 0 ;
	virtual int __cdecl _GetGL_ACTIVE_RESOURCES() = 0 ;
	virtual int __cdecl _GetGL_ACTIVE_VARIABLES() = 0 ;
	virtual int __cdecl _GetGL_ALL_BARRIER_BITS() = 0 ;
	virtual int __cdecl _GetGL_ALL_SHADER_BITS() = 0 ;
	virtual int __cdecl _GetGL_ARRAY_SIZE() = 0 ;
	virtual int __cdecl _GetGL_ARRAY_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_ATOMIC_COUNTER_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_ATOMIC_COUNTER_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_ATOMIC_COUNTER_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_ATOMIC_COUNTER_BUFFER_INDEX() = 0 ;
	virtual int __cdecl _GetGL_ATOMIC_COUNTER_BUFFER_SIZE() = 0 ;
	virtual int __cdecl _GetGL_ATOMIC_COUNTER_BUFFER_START() = 0 ;
	virtual int __cdecl _GetGL_BLOCK_INDEX() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_DATA_SIZE() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_UPDATE_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_VARIABLE() = 0 ;
	virtual int __cdecl _GetGL_COMMAND_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_COMPUTE_SHADER() = 0 ;
	virtual int __cdecl _GetGL_COMPUTE_SHADER_BIT() = 0 ;
	virtual int __cdecl _GetGL_COMPUTE_WORK_GROUP_SIZE() = 0 ;
	virtual int __cdecl _GetGL_DEPTH_STENCIL_TEXTURE_MODE() = 0 ;
	virtual int __cdecl _GetGL_DISPATCH_INDIRECT_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_DISPATCH_INDIRECT_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_DRAW_INDIRECT_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_DRAW_INDIRECT_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_ELEMENT_ARRAY_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_FRAGMENT_SHADER_BIT() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_DEFAULT_HEIGHT() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_DEFAULT_SAMPLES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_DEFAULT_WIDTH() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_2D() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_2D_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_3D() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_BINDING_ACCESS() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_BINDING_FORMAT() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_BINDING_LAYER() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_BINDING_LAYERED() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_BINDING_LEVEL() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_BINDING_NAME() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_CUBE() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_FORMAT_COMPATIBILITY_TYPE() = 0 ;
	virtual int __cdecl _GetGL_INT_IMAGE_2D() = 0 ;
	virtual int __cdecl _GetGL_INT_IMAGE_2D_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_INT_IMAGE_3D() = 0 ;
	virtual int __cdecl _GetGL_INT_IMAGE_CUBE() = 0 ;
	virtual int __cdecl _GetGL_INT_SAMPLER_2D_MULTISAMPLE() = 0 ;
	virtual int __cdecl _GetGL_IS_ROW_MAJOR() = 0 ;
	virtual int __cdecl _GetGL_LOCATION() = 0 ;
	virtual int __cdecl _GetGL_MATRIX_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS() = 0 ;
	virtual int __cdecl _GetGL_MAX_ATOMIC_COUNTER_BUFFER_SIZE() = 0 ;
	virtual int __cdecl _GetGL_MAX_COLOR_TEXTURE_SAMPLES() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_ATOMIC_COUNTERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_IMAGE_UNIFORMS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_SHADER_STORAGE_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMPUTE_ATOMIC_COUNTERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMPUTE_IMAGE_UNIFORMS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMPUTE_SHARED_MEMORY_SIZE() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMPUTE_UNIFORM_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMPUTE_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMPUTE_WORK_GROUP_COUNT() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMPUTE_WORK_GROUP_SIZE() = 0 ;
	virtual int __cdecl _GetGL_MAX_DEPTH_TEXTURE_SAMPLES() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAGMENT_ATOMIC_COUNTERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAGMENT_IMAGE_UNIFORMS() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAMEBUFFER_HEIGHT() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAMEBUFFER_SAMPLES() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAMEBUFFER_WIDTH() = 0 ;
	virtual int __cdecl _GetGL_MAX_IMAGE_UNITS() = 0 ;
	virtual int __cdecl _GetGL_MAX_INTEGER_SAMPLES() = 0 ;
	virtual int __cdecl _GetGL_MAX_NAME_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_MAX_NUM_ACTIVE_VARIABLES() = 0 ;
	virtual int __cdecl _GetGL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_MAX_SAMPLE_MASK_WORDS() = 0 ;
	virtual int __cdecl _GetGL_MAX_SHADER_STORAGE_BLOCK_SIZE() = 0 ;
	virtual int __cdecl _GetGL_MAX_SHADER_STORAGE_BUFFER_BINDINGS() = 0 ;
	virtual int __cdecl _GetGL_MAX_UNIFORM_LOCATIONS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_ATOMIC_COUNTERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_ATTRIB_BINDINGS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_ATTRIB_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_IMAGE_UNIFORMS() = 0 ;
	virtual int __cdecl _GetGL_MAX_VERTEX_SHADER_STORAGE_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_NAME_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_NUM_ACTIVE_VARIABLES() = 0 ;
	virtual int __cdecl _GetGL_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_PIXEL_BUFFER_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_PROGRAM_INPUT() = 0 ;
	virtual int __cdecl _GetGL_PROGRAM_OUTPUT() = 0 ;
	virtual int __cdecl _GetGL_PROGRAM_PIPELINE_BINDING() = 0 ;
	virtual int __cdecl _GetGL_PROGRAM_SEPARABLE() = 0 ;
	virtual int __cdecl _GetGL_READ_ONLY() = 0 ;
	virtual int __cdecl _GetGL_READ_WRITE() = 0 ;
	virtual int __cdecl _GetGL_REFERENCED_BY_COMPUTE_SHADER() = 0 ;
	virtual int __cdecl _GetGL_REFERENCED_BY_FRAGMENT_SHADER() = 0 ;
	virtual int __cdecl _GetGL_REFERENCED_BY_VERTEX_SHADER() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_2D_MULTISAMPLE() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_MASK() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_MASK_VALUE() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_POSITION() = 0 ;
	virtual int __cdecl _GetGL_SHADER_IMAGE_ACCESS_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_SHADER_STORAGE_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_SHADER_STORAGE_BLOCK() = 0 ;
	virtual int __cdecl _GetGL_SHADER_STORAGE_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_SHADER_STORAGE_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT() = 0 ;
	virtual int __cdecl _GetGL_SHADER_STORAGE_BUFFER_SIZE() = 0 ;
	virtual int __cdecl _GetGL_SHADER_STORAGE_BUFFER_START() = 0 ;
	HIDESBASE virtual int __cdecl _GetGL_STENCIL_INDEX() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_2D_MULTISAMPLE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_ALPHA_SIZE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_ALPHA_TYPE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_2D_MULTISAMPLE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BLUE_SIZE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BLUE_TYPE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_COMPRESSED() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_DEPTH() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_DEPTH_SIZE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_DEPTH_TYPE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_FETCH_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_FIXED_SAMPLE_LOCATIONS() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_GREEN_SIZE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_GREEN_TYPE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_HEIGHT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_INTERNAL_FORMAT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_RED_SIZE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_RED_TYPE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_SAMPLES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_SHARED_SIZE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_STENCIL_SIZE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_UPDATE_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_WIDTH() = 0 ;
	virtual int __cdecl _GetGL_TOP_LEVEL_ARRAY_SIZE() = 0 ;
	virtual int __cdecl _GetGL_TOP_LEVEL_ARRAY_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_TRANSFORM_FEEDBACK_VARYING() = 0 ;
	virtual int __cdecl _GetGL_TYPE() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_UNIFORM_BLOCK() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_ATOMIC_COUNTER() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_IMAGE_2D() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_IMAGE_2D_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_IMAGE_3D() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_IMAGE_CUBE() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_BINDING() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ATTRIB_RELATIVE_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_BINDING_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_BINDING_DIVISOR() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_BINDING_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_BINDING_STRIDE() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_SHADER_BIT() = 0 ;
	virtual int __cdecl _GetGL_WRITE_ONLY() = 0 ;
	virtual void __cdecl glActiveShaderProgram(int pipeline, int program_) = 0 ;
	virtual void __cdecl glBindImageTexture(int unit_, int texture, int level, bool layered, int layer, int access, int format) = 0 ;
	virtual void __cdecl glBindProgramPipeline(int pipeline) = 0 ;
	virtual void __cdecl glBindVertexBuffer(int bindingindex, int buffer, __int64 offset, int stride) = 0 ;
	virtual int __cdecl glCreateShaderProgramv(int type_, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* strings) = 0 ;
	virtual void __cdecl glDeleteProgramPipelines(int n, Androidapi::Jnibridge::TJavaArray__1<int>* pipelines, int offset) = 0 /* overload */;
	virtual void __cdecl glDeleteProgramPipelines(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer pipelines) = 0 /* overload */;
	virtual void __cdecl glDispatchCompute(int num_groups_x, int num_groups_y, int num_groups_z) = 0 ;
	virtual void __cdecl glDispatchComputeIndirect(__int64 indirect) = 0 ;
	virtual void __cdecl glDrawArraysIndirect(int mode, __int64 indirect) = 0 ;
	virtual void __cdecl glDrawElementsIndirect(int mode, int type_, __int64 indirect) = 0 ;
	virtual void __cdecl glFramebufferParameteri(int target, int pname, int param) = 0 ;
	virtual void __cdecl glGenProgramPipelines(int n, Androidapi::Jnibridge::TJavaArray__1<int>* pipelines, int offset) = 0 /* overload */;
	virtual void __cdecl glGenProgramPipelines(int n, Androidapi::Jni::Javatypes::_di_JIntBuffer pipelines) = 0 /* overload */;
	virtual void __cdecl glGetBooleani_v(int target, int index, Androidapi::Jnibridge::TJavaArray__1<bool>* data, int offset) = 0 /* overload */;
	virtual void __cdecl glGetBooleani_v(int target, int index, Androidapi::Jni::Javatypes::_di_JIntBuffer data) = 0 /* overload */;
	virtual void __cdecl glGetFramebufferParameteriv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetFramebufferParameteriv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetMultisamplefv(int pname, int index, Androidapi::Jnibridge::TJavaArray__1<float>* val, int offset) = 0 /* overload */;
	virtual void __cdecl glGetMultisamplefv(int pname, int index, Androidapi::Jni::Javatypes::_di_JFloatBuffer val) = 0 /* overload */;
	virtual void __cdecl glGetProgramInterfaceiv(int program_, int programInterface, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetProgramInterfaceiv(int program_, int programInterface, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetProgramPipelineInfoLog(int program_) = 0 ;
	virtual void __cdecl glGetProgramPipelineiv(int pipeline, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetProgramPipelineiv(int pipeline, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual int __cdecl glGetProgramResourceIndex(int program_, int programInterface, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual int __cdecl glGetProgramResourceLocation(int program_, int programInterface, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetProgramResourceName(int program_, int programInterface, int index) = 0 ;
	virtual void __cdecl glGetProgramResourceiv(int program_, int programInterface, int index, int propCount, Androidapi::Jnibridge::TJavaArray__1<int>* props, int propsOffset, int bufSize, Androidapi::Jnibridge::TJavaArray__1<int>* length, int lengthOffset, Androidapi::Jnibridge::TJavaArray__1<int>* params, int paramsOffset) = 0 /* overload */;
	virtual void __cdecl glGetProgramResourceiv(int program_, int programInterface, int index, int propCount, Androidapi::Jni::Javatypes::_di_JIntBuffer props, int bufSize, Androidapi::Jni::Javatypes::_di_JIntBuffer length, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexLevelParameterfv(int target, int level, int pname, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexLevelParameterfv(int target, int level, int pname, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexLevelParameteriv(int target, int level, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexLevelParameteriv(int target, int level, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual bool __cdecl glIsProgramPipeline(int pipeline) = 0 ;
	virtual void __cdecl glMemoryBarrier(int barriers) = 0 ;
	virtual void __cdecl glMemoryBarrierByRegion(int barriers) = 0 ;
	virtual void __cdecl glProgramUniform1f(int program_, int location, float v0) = 0 ;
	virtual void __cdecl glProgramUniform1fv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform1fv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniform1i(int program_, int location, int v0) = 0 ;
	virtual void __cdecl glProgramUniform1iv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform1iv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniform1ui(int program_, int location, int v0) = 0 ;
	virtual void __cdecl glProgramUniform1uiv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform1uiv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniform2f(int program_, int location, float v0, float v1) = 0 ;
	virtual void __cdecl glProgramUniform2fv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform2fv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniform2i(int program_, int location, int v0, int v1) = 0 ;
	virtual void __cdecl glProgramUniform2iv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform2iv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniform2ui(int program_, int location, int v0, int v1) = 0 ;
	virtual void __cdecl glProgramUniform2uiv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform2uiv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniform3f(int program_, int location, float v0, float v1, float v2) = 0 ;
	virtual void __cdecl glProgramUniform3fv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform3fv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniform3i(int program_, int location, int v0, int v1, int v2) = 0 ;
	virtual void __cdecl glProgramUniform3iv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform3iv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniform3ui(int program_, int location, int v0, int v1, int v2) = 0 ;
	virtual void __cdecl glProgramUniform3uiv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform3uiv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniform4f(int program_, int location, float v0, float v1, float v2, float v3) = 0 ;
	virtual void __cdecl glProgramUniform4fv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform4fv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniform4i(int program_, int location, int v0, int v1, int v2, int v3) = 0 ;
	virtual void __cdecl glProgramUniform4iv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform4iv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniform4ui(int program_, int location, int v0, int v1, int v2, int v3) = 0 ;
	virtual void __cdecl glProgramUniform4uiv(int program_, int location, int count, Androidapi::Jnibridge::TJavaArray__1<int>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniform4uiv(int program_, int location, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix2fv(int program_, int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix2fv(int program_, int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix2x3fv(int program_, int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix2x3fv(int program_, int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix2x4fv(int program_, int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix2x4fv(int program_, int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix3fv(int program_, int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix3fv(int program_, int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix3x2fv(int program_, int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix3x2fv(int program_, int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix3x4fv(int program_, int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix3x4fv(int program_, int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix4fv(int program_, int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix4fv(int program_, int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix4x2fv(int program_, int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix4x2fv(int program_, int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix4x3fv(int program_, int location, int count, bool transpose, Androidapi::Jnibridge::TJavaArray__1<float>* value, int offset) = 0 /* overload */;
	virtual void __cdecl glProgramUniformMatrix4x3fv(int program_, int location, int count, bool transpose, Androidapi::Jni::Javatypes::_di_JFloatBuffer value) = 0 /* overload */;
	virtual void __cdecl glSampleMaski(int maskNumber, int mask) = 0 ;
	virtual void __cdecl glTexStorage2DMultisample(int target, int samples, int internalformat, int width, int height, bool fixedsamplelocations) = 0 ;
	virtual void __cdecl glUseProgramStages(int pipeline, int stages, int program_) = 0 ;
	virtual void __cdecl glValidateProgramPipeline(int pipeline) = 0 ;
	virtual void __cdecl glVertexAttribBinding(int attribindex, int bindingindex) = 0 ;
	virtual void __cdecl glVertexAttribFormat(int attribindex, int size, int type_, bool normalized, int relativeoffset) = 0 ;
	virtual void __cdecl glVertexAttribIFormat(int attribindex, int size, int type_, int relativeoffset) = 0 ;
	virtual void __cdecl glVertexBindingDivisor(int bindingindex, int divisor) = 0 ;
	__property int GL_ACTIVE_ATOMIC_COUNTER_BUFFERS = {read=_GetGL_ACTIVE_ATOMIC_COUNTER_BUFFERS};
	__property int GL_ACTIVE_PROGRAM = {read=_GetGL_ACTIVE_PROGRAM};
	__property int GL_ACTIVE_RESOURCES = {read=_GetGL_ACTIVE_RESOURCES};
	__property int GL_ACTIVE_VARIABLES = {read=_GetGL_ACTIVE_VARIABLES};
	__property int GL_ALL_BARRIER_BITS = {read=_GetGL_ALL_BARRIER_BITS};
	__property int GL_ALL_SHADER_BITS = {read=_GetGL_ALL_SHADER_BITS};
	__property int GL_ARRAY_SIZE = {read=_GetGL_ARRAY_SIZE};
	__property int GL_ARRAY_STRIDE = {read=_GetGL_ARRAY_STRIDE};
	__property int GL_ATOMIC_COUNTER_BARRIER_BIT = {read=_GetGL_ATOMIC_COUNTER_BARRIER_BIT};
	__property int GL_ATOMIC_COUNTER_BUFFER = {read=_GetGL_ATOMIC_COUNTER_BUFFER};
	__property int GL_ATOMIC_COUNTER_BUFFER_BINDING = {read=_GetGL_ATOMIC_COUNTER_BUFFER_BINDING};
	__property int GL_ATOMIC_COUNTER_BUFFER_INDEX = {read=_GetGL_ATOMIC_COUNTER_BUFFER_INDEX};
	__property int GL_ATOMIC_COUNTER_BUFFER_SIZE = {read=_GetGL_ATOMIC_COUNTER_BUFFER_SIZE};
	__property int GL_ATOMIC_COUNTER_BUFFER_START = {read=_GetGL_ATOMIC_COUNTER_BUFFER_START};
	__property int GL_BLOCK_INDEX = {read=_GetGL_BLOCK_INDEX};
	__property int GL_BUFFER_BINDING = {read=_GetGL_BUFFER_BINDING};
	__property int GL_BUFFER_DATA_SIZE = {read=_GetGL_BUFFER_DATA_SIZE};
	__property int GL_BUFFER_UPDATE_BARRIER_BIT = {read=_GetGL_BUFFER_UPDATE_BARRIER_BIT};
	__property int GL_BUFFER_VARIABLE = {read=_GetGL_BUFFER_VARIABLE};
	__property int GL_COMMAND_BARRIER_BIT = {read=_GetGL_COMMAND_BARRIER_BIT};
	__property int GL_COMPUTE_SHADER = {read=_GetGL_COMPUTE_SHADER};
	__property int GL_COMPUTE_SHADER_BIT = {read=_GetGL_COMPUTE_SHADER_BIT};
	__property int GL_COMPUTE_WORK_GROUP_SIZE = {read=_GetGL_COMPUTE_WORK_GROUP_SIZE};
	__property int GL_DEPTH_STENCIL_TEXTURE_MODE = {read=_GetGL_DEPTH_STENCIL_TEXTURE_MODE};
	__property int GL_DISPATCH_INDIRECT_BUFFER = {read=_GetGL_DISPATCH_INDIRECT_BUFFER};
	__property int GL_DISPATCH_INDIRECT_BUFFER_BINDING = {read=_GetGL_DISPATCH_INDIRECT_BUFFER_BINDING};
	__property int GL_DRAW_INDIRECT_BUFFER = {read=_GetGL_DRAW_INDIRECT_BUFFER};
	__property int GL_DRAW_INDIRECT_BUFFER_BINDING = {read=_GetGL_DRAW_INDIRECT_BUFFER_BINDING};
	__property int GL_ELEMENT_ARRAY_BARRIER_BIT = {read=_GetGL_ELEMENT_ARRAY_BARRIER_BIT};
	__property int GL_FRAGMENT_SHADER_BIT = {read=_GetGL_FRAGMENT_SHADER_BIT};
	__property int GL_FRAMEBUFFER_BARRIER_BIT = {read=_GetGL_FRAMEBUFFER_BARRIER_BIT};
	__property int GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS = {read=_GetGL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS};
	__property int GL_FRAMEBUFFER_DEFAULT_HEIGHT = {read=_GetGL_FRAMEBUFFER_DEFAULT_HEIGHT};
	__property int GL_FRAMEBUFFER_DEFAULT_SAMPLES = {read=_GetGL_FRAMEBUFFER_DEFAULT_SAMPLES};
	__property int GL_FRAMEBUFFER_DEFAULT_WIDTH = {read=_GetGL_FRAMEBUFFER_DEFAULT_WIDTH};
	__property int GL_IMAGE_2D = {read=_GetGL_IMAGE_2D};
	__property int GL_IMAGE_2D_ARRAY = {read=_GetGL_IMAGE_2D_ARRAY};
	__property int GL_IMAGE_3D = {read=_GetGL_IMAGE_3D};
	__property int GL_IMAGE_BINDING_ACCESS = {read=_GetGL_IMAGE_BINDING_ACCESS};
	__property int GL_IMAGE_BINDING_FORMAT = {read=_GetGL_IMAGE_BINDING_FORMAT};
	__property int GL_IMAGE_BINDING_LAYER = {read=_GetGL_IMAGE_BINDING_LAYER};
	__property int GL_IMAGE_BINDING_LAYERED = {read=_GetGL_IMAGE_BINDING_LAYERED};
	__property int GL_IMAGE_BINDING_LEVEL = {read=_GetGL_IMAGE_BINDING_LEVEL};
	__property int GL_IMAGE_BINDING_NAME = {read=_GetGL_IMAGE_BINDING_NAME};
	__property int GL_IMAGE_CUBE = {read=_GetGL_IMAGE_CUBE};
	__property int GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS = {read=_GetGL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS};
	__property int GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE = {read=_GetGL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE};
	__property int GL_IMAGE_FORMAT_COMPATIBILITY_TYPE = {read=_GetGL_IMAGE_FORMAT_COMPATIBILITY_TYPE};
	__property int GL_INT_IMAGE_2D = {read=_GetGL_INT_IMAGE_2D};
	__property int GL_INT_IMAGE_2D_ARRAY = {read=_GetGL_INT_IMAGE_2D_ARRAY};
	__property int GL_INT_IMAGE_3D = {read=_GetGL_INT_IMAGE_3D};
	__property int GL_INT_IMAGE_CUBE = {read=_GetGL_INT_IMAGE_CUBE};
	__property int GL_INT_SAMPLER_2D_MULTISAMPLE = {read=_GetGL_INT_SAMPLER_2D_MULTISAMPLE};
	__property int GL_IS_ROW_MAJOR = {read=_GetGL_IS_ROW_MAJOR};
	__property int GL_LOCATION = {read=_GetGL_LOCATION};
	__property int GL_MATRIX_STRIDE = {read=_GetGL_MATRIX_STRIDE};
	__property int GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS = {read=_GetGL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS};
	__property int GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE = {read=_GetGL_MAX_ATOMIC_COUNTER_BUFFER_SIZE};
	__property int GL_MAX_COLOR_TEXTURE_SAMPLES = {read=_GetGL_MAX_COLOR_TEXTURE_SAMPLES};
	__property int GL_MAX_COMBINED_ATOMIC_COUNTERS = {read=_GetGL_MAX_COMBINED_ATOMIC_COUNTERS};
	__property int GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS = {read=_GetGL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS};
	__property int GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS = {read=_GetGL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS};
	__property int GL_MAX_COMBINED_IMAGE_UNIFORMS = {read=_GetGL_MAX_COMBINED_IMAGE_UNIFORMS};
	__property int GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES = {read=_GetGL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES};
	__property int GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS = {read=_GetGL_MAX_COMBINED_SHADER_STORAGE_BLOCKS};
	__property int GL_MAX_COMPUTE_ATOMIC_COUNTERS = {read=_GetGL_MAX_COMPUTE_ATOMIC_COUNTERS};
	__property int GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS = {read=_GetGL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS};
	__property int GL_MAX_COMPUTE_IMAGE_UNIFORMS = {read=_GetGL_MAX_COMPUTE_IMAGE_UNIFORMS};
	__property int GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS = {read=_GetGL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS};
	__property int GL_MAX_COMPUTE_SHARED_MEMORY_SIZE = {read=_GetGL_MAX_COMPUTE_SHARED_MEMORY_SIZE};
	__property int GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS = {read=_GetGL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS};
	__property int GL_MAX_COMPUTE_UNIFORM_BLOCKS = {read=_GetGL_MAX_COMPUTE_UNIFORM_BLOCKS};
	__property int GL_MAX_COMPUTE_UNIFORM_COMPONENTS = {read=_GetGL_MAX_COMPUTE_UNIFORM_COMPONENTS};
	__property int GL_MAX_COMPUTE_WORK_GROUP_COUNT = {read=_GetGL_MAX_COMPUTE_WORK_GROUP_COUNT};
	__property int GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS = {read=_GetGL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS};
	__property int GL_MAX_COMPUTE_WORK_GROUP_SIZE = {read=_GetGL_MAX_COMPUTE_WORK_GROUP_SIZE};
	__property int GL_MAX_DEPTH_TEXTURE_SAMPLES = {read=_GetGL_MAX_DEPTH_TEXTURE_SAMPLES};
	__property int GL_MAX_FRAGMENT_ATOMIC_COUNTERS = {read=_GetGL_MAX_FRAGMENT_ATOMIC_COUNTERS};
	__property int GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS = {read=_GetGL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS};
	__property int GL_MAX_FRAGMENT_IMAGE_UNIFORMS = {read=_GetGL_MAX_FRAGMENT_IMAGE_UNIFORMS};
	__property int GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS = {read=_GetGL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS};
	__property int GL_MAX_FRAMEBUFFER_HEIGHT = {read=_GetGL_MAX_FRAMEBUFFER_HEIGHT};
	__property int GL_MAX_FRAMEBUFFER_SAMPLES = {read=_GetGL_MAX_FRAMEBUFFER_SAMPLES};
	__property int GL_MAX_FRAMEBUFFER_WIDTH = {read=_GetGL_MAX_FRAMEBUFFER_WIDTH};
	__property int GL_MAX_IMAGE_UNITS = {read=_GetGL_MAX_IMAGE_UNITS};
	__property int GL_MAX_INTEGER_SAMPLES = {read=_GetGL_MAX_INTEGER_SAMPLES};
	__property int GL_MAX_NAME_LENGTH = {read=_GetGL_MAX_NAME_LENGTH};
	__property int GL_MAX_NUM_ACTIVE_VARIABLES = {read=_GetGL_MAX_NUM_ACTIVE_VARIABLES};
	__property int GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET = {read=_GetGL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET};
	__property int GL_MAX_SAMPLE_MASK_WORDS = {read=_GetGL_MAX_SAMPLE_MASK_WORDS};
	__property int GL_MAX_SHADER_STORAGE_BLOCK_SIZE = {read=_GetGL_MAX_SHADER_STORAGE_BLOCK_SIZE};
	__property int GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS = {read=_GetGL_MAX_SHADER_STORAGE_BUFFER_BINDINGS};
	__property int GL_MAX_UNIFORM_LOCATIONS = {read=_GetGL_MAX_UNIFORM_LOCATIONS};
	__property int GL_MAX_VERTEX_ATOMIC_COUNTERS = {read=_GetGL_MAX_VERTEX_ATOMIC_COUNTERS};
	__property int GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS = {read=_GetGL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS};
	__property int GL_MAX_VERTEX_ATTRIB_BINDINGS = {read=_GetGL_MAX_VERTEX_ATTRIB_BINDINGS};
	__property int GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET = {read=_GetGL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET};
	__property int GL_MAX_VERTEX_ATTRIB_STRIDE = {read=_GetGL_MAX_VERTEX_ATTRIB_STRIDE};
	__property int GL_MAX_VERTEX_IMAGE_UNIFORMS = {read=_GetGL_MAX_VERTEX_IMAGE_UNIFORMS};
	__property int GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS = {read=_GetGL_MAX_VERTEX_SHADER_STORAGE_BLOCKS};
	__property int GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET = {read=_GetGL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET};
	__property int GL_NAME_LENGTH = {read=_GetGL_NAME_LENGTH};
	__property int GL_NUM_ACTIVE_VARIABLES = {read=_GetGL_NUM_ACTIVE_VARIABLES};
	__property int GL_OFFSET = {read=_GetGL_OFFSET};
	__property int GL_PIXEL_BUFFER_BARRIER_BIT = {read=_GetGL_PIXEL_BUFFER_BARRIER_BIT};
	__property int GL_PROGRAM_INPUT = {read=_GetGL_PROGRAM_INPUT};
	__property int GL_PROGRAM_OUTPUT = {read=_GetGL_PROGRAM_OUTPUT};
	__property int GL_PROGRAM_PIPELINE_BINDING = {read=_GetGL_PROGRAM_PIPELINE_BINDING};
	__property int GL_PROGRAM_SEPARABLE = {read=_GetGL_PROGRAM_SEPARABLE};
	__property int GL_READ_ONLY = {read=_GetGL_READ_ONLY};
	__property int GL_READ_WRITE = {read=_GetGL_READ_WRITE};
	__property int GL_REFERENCED_BY_COMPUTE_SHADER = {read=_GetGL_REFERENCED_BY_COMPUTE_SHADER};
	__property int GL_REFERENCED_BY_FRAGMENT_SHADER = {read=_GetGL_REFERENCED_BY_FRAGMENT_SHADER};
	__property int GL_REFERENCED_BY_VERTEX_SHADER = {read=_GetGL_REFERENCED_BY_VERTEX_SHADER};
	__property int GL_SAMPLER_2D_MULTISAMPLE = {read=_GetGL_SAMPLER_2D_MULTISAMPLE};
	__property int GL_SAMPLE_MASK = {read=_GetGL_SAMPLE_MASK};
	__property int GL_SAMPLE_MASK_VALUE = {read=_GetGL_SAMPLE_MASK_VALUE};
	__property int GL_SAMPLE_POSITION = {read=_GetGL_SAMPLE_POSITION};
	__property int GL_SHADER_IMAGE_ACCESS_BARRIER_BIT = {read=_GetGL_SHADER_IMAGE_ACCESS_BARRIER_BIT};
	__property int GL_SHADER_STORAGE_BARRIER_BIT = {read=_GetGL_SHADER_STORAGE_BARRIER_BIT};
	__property int GL_SHADER_STORAGE_BLOCK = {read=_GetGL_SHADER_STORAGE_BLOCK};
	__property int GL_SHADER_STORAGE_BUFFER = {read=_GetGL_SHADER_STORAGE_BUFFER};
	__property int GL_SHADER_STORAGE_BUFFER_BINDING = {read=_GetGL_SHADER_STORAGE_BUFFER_BINDING};
	__property int GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT = {read=_GetGL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT};
	__property int GL_SHADER_STORAGE_BUFFER_SIZE = {read=_GetGL_SHADER_STORAGE_BUFFER_SIZE};
	__property int GL_SHADER_STORAGE_BUFFER_START = {read=_GetGL_SHADER_STORAGE_BUFFER_START};
	__property int GL_TEXTURE_2D_MULTISAMPLE = {read=_GetGL_TEXTURE_2D_MULTISAMPLE};
	__property int GL_TEXTURE_ALPHA_SIZE = {read=_GetGL_TEXTURE_ALPHA_SIZE};
	__property int GL_TEXTURE_ALPHA_TYPE = {read=_GetGL_TEXTURE_ALPHA_TYPE};
	__property int GL_TEXTURE_BINDING_2D_MULTISAMPLE = {read=_GetGL_TEXTURE_BINDING_2D_MULTISAMPLE};
	__property int GL_TEXTURE_BLUE_SIZE = {read=_GetGL_TEXTURE_BLUE_SIZE};
	__property int GL_TEXTURE_BLUE_TYPE = {read=_GetGL_TEXTURE_BLUE_TYPE};
	__property int GL_TEXTURE_COMPRESSED = {read=_GetGL_TEXTURE_COMPRESSED};
	__property int GL_TEXTURE_DEPTH = {read=_GetGL_TEXTURE_DEPTH};
	__property int GL_TEXTURE_DEPTH_SIZE = {read=_GetGL_TEXTURE_DEPTH_SIZE};
	__property int GL_TEXTURE_DEPTH_TYPE = {read=_GetGL_TEXTURE_DEPTH_TYPE};
	__property int GL_TEXTURE_FETCH_BARRIER_BIT = {read=_GetGL_TEXTURE_FETCH_BARRIER_BIT};
	__property int GL_TEXTURE_FIXED_SAMPLE_LOCATIONS = {read=_GetGL_TEXTURE_FIXED_SAMPLE_LOCATIONS};
	__property int GL_TEXTURE_GREEN_SIZE = {read=_GetGL_TEXTURE_GREEN_SIZE};
	__property int GL_TEXTURE_GREEN_TYPE = {read=_GetGL_TEXTURE_GREEN_TYPE};
	__property int GL_TEXTURE_HEIGHT = {read=_GetGL_TEXTURE_HEIGHT};
	__property int GL_TEXTURE_INTERNAL_FORMAT = {read=_GetGL_TEXTURE_INTERNAL_FORMAT};
	__property int GL_TEXTURE_RED_SIZE = {read=_GetGL_TEXTURE_RED_SIZE};
	__property int GL_TEXTURE_RED_TYPE = {read=_GetGL_TEXTURE_RED_TYPE};
	__property int GL_TEXTURE_SAMPLES = {read=_GetGL_TEXTURE_SAMPLES};
	__property int GL_TEXTURE_SHARED_SIZE = {read=_GetGL_TEXTURE_SHARED_SIZE};
	__property int GL_TEXTURE_STENCIL_SIZE = {read=_GetGL_TEXTURE_STENCIL_SIZE};
	__property int GL_TEXTURE_UPDATE_BARRIER_BIT = {read=_GetGL_TEXTURE_UPDATE_BARRIER_BIT};
	__property int GL_TEXTURE_WIDTH = {read=_GetGL_TEXTURE_WIDTH};
	__property int GL_TOP_LEVEL_ARRAY_SIZE = {read=_GetGL_TOP_LEVEL_ARRAY_SIZE};
	__property int GL_TOP_LEVEL_ARRAY_STRIDE = {read=_GetGL_TOP_LEVEL_ARRAY_STRIDE};
	__property int GL_TRANSFORM_FEEDBACK_BARRIER_BIT = {read=_GetGL_TRANSFORM_FEEDBACK_BARRIER_BIT};
	__property int GL_TRANSFORM_FEEDBACK_VARYING = {read=_GetGL_TRANSFORM_FEEDBACK_VARYING};
	__property int GL_TYPE = {read=_GetGL_TYPE};
	__property int GL_UNIFORM = {read=_GetGL_UNIFORM};
	__property int GL_UNIFORM_BARRIER_BIT = {read=_GetGL_UNIFORM_BARRIER_BIT};
	__property int GL_UNIFORM_BLOCK = {read=_GetGL_UNIFORM_BLOCK};
	__property int GL_UNSIGNED_INT_ATOMIC_COUNTER = {read=_GetGL_UNSIGNED_INT_ATOMIC_COUNTER};
	__property int GL_UNSIGNED_INT_IMAGE_2D = {read=_GetGL_UNSIGNED_INT_IMAGE_2D};
	__property int GL_UNSIGNED_INT_IMAGE_2D_ARRAY = {read=_GetGL_UNSIGNED_INT_IMAGE_2D_ARRAY};
	__property int GL_UNSIGNED_INT_IMAGE_3D = {read=_GetGL_UNSIGNED_INT_IMAGE_3D};
	__property int GL_UNSIGNED_INT_IMAGE_CUBE = {read=_GetGL_UNSIGNED_INT_IMAGE_CUBE};
	__property int GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = {read=_GetGL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE};
	__property int GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT = {read=_GetGL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT};
	__property int GL_VERTEX_ATTRIB_BINDING = {read=_GetGL_VERTEX_ATTRIB_BINDING};
	__property int GL_VERTEX_ATTRIB_RELATIVE_OFFSET = {read=_GetGL_VERTEX_ATTRIB_RELATIVE_OFFSET};
	__property int GL_VERTEX_BINDING_BUFFER = {read=_GetGL_VERTEX_BINDING_BUFFER};
	__property int GL_VERTEX_BINDING_DIVISOR = {read=_GetGL_VERTEX_BINDING_DIVISOR};
	__property int GL_VERTEX_BINDING_OFFSET = {read=_GetGL_VERTEX_BINDING_OFFSET};
	__property int GL_VERTEX_BINDING_STRIDE = {read=_GetGL_VERTEX_BINDING_STRIDE};
	__property int GL_VERTEX_SHADER_BIT = {read=_GetGL_VERTEX_SHADER_BIT};
	__property int GL_WRITE_ONLY = {read=_GetGL_WRITE_ONLY};
};

__interface  INTERFACE_UUID("{A5839B6F-50F1-46A6-B9CC-748019DFAB87}") JGLES31  : public JGLES30 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLES31 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES31Class,_di_JGLES31>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES31Class,_di_JGLES31> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLES31() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES31Class,_di_JGLES31>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLES31() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6077CD36-8744-4F9A-BCEB-CFC942FB3FED}") JGLES31ExtClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetGL_BLEND_ADVANCED_COHERENT_KHR() = 0 ;
	virtual int __cdecl _GetGL_BUFFER_KHR() = 0 ;
	virtual int __cdecl _GetGL_CLAMP_TO_BORDER_EXT() = 0 ;
	virtual int __cdecl _GetGL_COLORBURN_KHR() = 0 ;
	virtual int __cdecl _GetGL_COLORDODGE_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_10x10_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_10x5_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_10x6_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_10x8_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_12x10_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_12x12_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_4x4_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_5x4_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_5x5_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_6x5_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_6x6_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_8x5_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_8x6_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_8x8_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR() = 0 ;
	virtual int __cdecl _GetGL_CONTEXT_FLAG_DEBUG_BIT_KHR() = 0 ;
	virtual int __cdecl _GetGL_DARKEN_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_CALLBACK_FUNCTION_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_CALLBACK_USER_PARAM_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_GROUP_STACK_DEPTH_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_LOGGED_MESSAGES_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_OUTPUT_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_OUTPUT_SYNCHRONOUS_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SEVERITY_HIGH_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SEVERITY_LOW_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SEVERITY_MEDIUM_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SEVERITY_NOTIFICATION_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_API_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_APPLICATION_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_OTHER_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_SHADER_COMPILER_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_THIRD_PARTY_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_ERROR_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_MARKER_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_OTHER_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_PERFORMANCE_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_POP_GROUP_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_PORTABILITY_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_PUSH_GROUP_KHR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR() = 0 ;
	virtual int __cdecl _GetGL_DECODE_EXT() = 0 ;
	virtual int __cdecl _GetGL_DIFFERENCE_KHR() = 0 ;
	virtual int __cdecl _GetGL_EXCLUSION_KHR() = 0 ;
	virtual int __cdecl _GetGL_FIRST_VERTEX_CONVENTION_EXT() = 0 ;
	virtual int __cdecl _GetGL_FRACTIONAL_EVEN_EXT() = 0 ;
	virtual int __cdecl _GetGL_FRACTIONAL_ODD_EXT() = 0 ;
	virtual int __cdecl _GetGL_FRAGMENT_INTERPOLATION_OFFSET_BITS_OES() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_DEFAULT_LAYERS_EXT() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_LINKED_INPUT_TYPE_EXT() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_LINKED_VERTICES_OUT_EXT() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_SHADER_BIT_EXT() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_SHADER_EXT() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_SHADER_INVOCATIONS_EXT() = 0 ;
	virtual int __cdecl _GetGL_HARDLIGHT_KHR() = 0 ;
	virtual int __cdecl _GetGL_HSL_COLOR_KHR() = 0 ;
	virtual int __cdecl _GetGL_HSL_HUE_KHR() = 0 ;
	virtual int __cdecl _GetGL_HSL_LUMINOSITY_KHR() = 0 ;
	virtual int __cdecl _GetGL_HSL_SATURATION_KHR() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_BUFFER_EXT() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_CUBE_MAP_ARRAY_EXT() = 0 ;
	virtual int __cdecl _GetGL_INT_IMAGE_BUFFER_EXT() = 0 ;
	virtual int __cdecl _GetGL_INT_IMAGE_CUBE_MAP_ARRAY_EXT() = 0 ;
	virtual int __cdecl _GetGL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES() = 0 ;
	virtual int __cdecl _GetGL_INT_SAMPLER_BUFFER_EXT() = 0 ;
	virtual int __cdecl _GetGL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT() = 0 ;
	virtual int __cdecl _GetGL_ISOLINES_EXT() = 0 ;
	virtual int __cdecl _GetGL_IS_PER_PATCH_EXT() = 0 ;
	virtual int __cdecl _GetGL_LAST_VERTEX_CONVENTION_EXT() = 0 ;
	virtual int __cdecl _GetGL_LAYER_PROVOKING_VERTEX_EXT() = 0 ;
	virtual int __cdecl _GetGL_LIGHTEN_KHR() = 0 ;
	virtual int __cdecl _GetGL_LINES_ADJACENCY_EXT() = 0 ;
	virtual int __cdecl _GetGL_LINE_STRIP_ADJACENCY_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_DEBUG_GROUP_STACK_DEPTH_KHR() = 0 ;
	virtual int __cdecl _GetGL_MAX_DEBUG_LOGGED_MESSAGES_KHR() = 0 ;
	virtual int __cdecl _GetGL_MAX_DEBUG_MESSAGE_LENGTH_KHR() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAGMENT_INTERPOLATION_OFFSET_OES() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAMEBUFFER_LAYERS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_INPUT_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_UNIFORM_BLOCKS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_LABEL_LENGTH_KHR() = 0 ;
	virtual int __cdecl _GetGL_MAX_PATCH_VERTICES_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_INPUT_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_UNIFORM_BLOCKS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_INPUT_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_GEN_LEVEL_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_PATCH_COMPONENTS_EXT() = 0 ;
	virtual int __cdecl _GetGL_MAX_TEXTURE_BUFFER_SIZE_EXT() = 0 ;
	virtual int __cdecl _GetGL_MIN_FRAGMENT_INTERPOLATION_OFFSET_OES() = 0 ;
	virtual int __cdecl _GetGL_MIN_SAMPLE_SHADING_VALUE_OES() = 0 ;
	virtual int __cdecl _GetGL_MULTIPLY_KHR() = 0 ;
	virtual int __cdecl _GetGL_OVERLAY_KHR() = 0 ;
	virtual int __cdecl _GetGL_PATCHES_EXT() = 0 ;
	virtual int __cdecl _GetGL_PATCH_VERTICES_EXT() = 0 ;
	virtual int __cdecl _GetGL_PRIMITIVES_GENERATED_EXT() = 0 ;
	virtual int __cdecl _GetGL_PRIMITIVE_BOUNDING_BOX_EXT() = 0 ;
	virtual int __cdecl _GetGL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED() = 0 ;
	virtual int __cdecl _GetGL_PROGRAM_KHR() = 0 ;
	virtual int __cdecl _GetGL_QUADS_EXT() = 0 ;
	virtual int __cdecl _GetGL_QUERY_KHR() = 0 ;
	virtual int __cdecl _GetGL_REFERENCED_BY_GEOMETRY_SHADER_EXT() = 0 ;
	virtual int __cdecl _GetGL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT() = 0 ;
	virtual int __cdecl _GetGL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_BUFFER_EXT() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_CUBE_MAP_ARRAY_EXT() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_KHR() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_SHADING_OES() = 0 ;
	virtual int __cdecl _GetGL_SCREEN_KHR() = 0 ;
	virtual int __cdecl _GetGL_SHADER_KHR() = 0 ;
	virtual int __cdecl _GetGL_SKIP_DECODE_EXT() = 0 ;
	virtual int __cdecl _GetGL_SOFTLIGHT_KHR() = 0 ;
	virtual int __cdecl _GetGL_STACK_OVERFLOW_KHR() = 0 ;
	virtual int __cdecl _GetGL_STACK_UNDERFLOW_KHR() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_INDEX8_OES() = 0 ;
	virtual int __cdecl _GetGL_STENCIL_INDEX_OES() = 0 ;
	virtual int __cdecl _GetGL_TESS_CONTROL_OUTPUT_VERTICES_EXT() = 0 ;
	virtual int __cdecl _GetGL_TESS_CONTROL_SHADER_BIT_EXT() = 0 ;
	virtual int __cdecl _GetGL_TESS_CONTROL_SHADER_EXT() = 0 ;
	virtual int __cdecl _GetGL_TESS_EVALUATION_SHADER_BIT_EXT() = 0 ;
	virtual int __cdecl _GetGL_TESS_EVALUATION_SHADER_EXT() = 0 ;
	virtual int __cdecl _GetGL_TESS_GEN_MODE_EXT() = 0 ;
	virtual int __cdecl _GetGL_TESS_GEN_POINT_MODE_EXT() = 0 ;
	virtual int __cdecl _GetGL_TESS_GEN_SPACING_EXT() = 0 ;
	virtual int __cdecl _GetGL_TESS_GEN_VERTEX_ORDER_EXT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_BUFFER_EXT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BORDER_COLOR_EXT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER_BINDING_EXT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER_DATA_STORE_BINDING_EXT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER_EXT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER_OFFSET_ALIGNMENT_EXT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER_OFFSET_EXT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER_SIZE_EXT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_ARRAY_EXT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_SRGB_DECODE_EXT() = 0 ;
	virtual int __cdecl _GetGL_TRIANGLES_ADJACENCY_EXT() = 0 ;
	virtual int __cdecl _GetGL_TRIANGLE_STRIP_ADJACENCY_EXT() = 0 ;
	virtual int __cdecl _GetGL_UNDEFINED_VERTEX_EXT() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_IMAGE_BUFFER_EXT() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_SAMPLER_BUFFER_EXT() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ARRAY_KHR() = 0 ;
	virtual void __cdecl glBlendBarrierKHR() = 0 ;
	virtual void __cdecl glBlendEquationSeparateiEXT(int buf, int modeRGB, int modeAlpha) = 0 ;
	virtual void __cdecl glBlendEquationiEXT(int buf, int mode) = 0 ;
	virtual void __cdecl glBlendFuncSeparateiEXT(int buf, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) = 0 ;
	virtual void __cdecl glBlendFunciEXT(int buf, int src, int dst) = 0 ;
	virtual void __cdecl glColorMaskiEXT(int index, bool r, bool g, bool b, bool a) = 0 ;
	virtual void __cdecl glCopyImageSubDataEXT(int srcName, int srcTarget, int srcLevel, int srcX, int srcY, int srcZ, int dstName, int dstTarget, int dstLevel, int dstX, int dstY, int dstZ, int srcWidth, int srcHeight, int srcDepth) = 0 ;
	virtual void __cdecl glDebugMessageCallbackKHR(_di_JGLES31Ext_DebugProcKHR callback) = 0 ;
	virtual void __cdecl glDebugMessageControlKHR(int source, int type_, int severity, int count, Androidapi::Jnibridge::TJavaArray__1<int>* ids, int offset, bool enabled) = 0 /* overload */;
	virtual void __cdecl glDebugMessageControlKHR(int source, int type_, int severity, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer ids, bool enabled) = 0 /* overload */;
	virtual void __cdecl glDebugMessageInsertKHR(int source, int type_, int id, int severity, Androidapi::Jni::Javatypes::_di_JString buf) = 0 ;
	virtual void __cdecl glDisableiEXT(int target, int index) = 0 ;
	virtual void __cdecl glEnableiEXT(int target, int index) = 0 ;
	virtual void __cdecl glFramebufferTextureEXT(int target, int attachment, int texture, int level) = 0 ;
	virtual _di_JGLES31Ext_DebugProcKHR __cdecl glGetDebugMessageCallbackKHR() = 0 ;
	virtual int __cdecl glGetDebugMessageLogKHR(int count, int bufSize, Androidapi::Jnibridge::TJavaArray__1<int>* sources, int sourcesOffset, Androidapi::Jnibridge::TJavaArray__1<int>* types, int typesOffset, Androidapi::Jnibridge::TJavaArray__1<int>* ids, int idsOffset, Androidapi::Jnibridge::TJavaArray__1<int>* severities, int severitiesOffset, Androidapi::Jnibridge::TJavaArray__1<int>* lengths, int lengthsOffset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* messageLog, int messageLogOffset) = 0 /* overload */;
	virtual int __cdecl glGetDebugMessageLogKHR(int count, Androidapi::Jni::Javatypes::_di_JIntBuffer sources, Androidapi::Jni::Javatypes::_di_JIntBuffer types, Androidapi::Jni::Javatypes::_di_JIntBuffer ids, Androidapi::Jni::Javatypes::_di_JIntBuffer severities, Androidapi::Jni::Javatypes::_di_JIntBuffer lengths, Androidapi::Jni::Javatypes::_di_JByteBuffer messageLog) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl glGetDebugMessageLogKHR(int count, Androidapi::Jnibridge::TJavaArray__1<int>* sources, int sourcesOffset, Androidapi::Jnibridge::TJavaArray__1<int>* types, int typesOffset, Androidapi::Jnibridge::TJavaArray__1<int>* ids, int idsOffset, Androidapi::Jnibridge::TJavaArray__1<int>* severities, int severitiesOffset) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl glGetDebugMessageLogKHR(int count, Androidapi::Jni::Javatypes::_di_JIntBuffer sources, Androidapi::Jni::Javatypes::_di_JIntBuffer types, Androidapi::Jni::Javatypes::_di_JIntBuffer ids, Androidapi::Jni::Javatypes::_di_JIntBuffer severities) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetObjectLabelKHR(int identifier, int name) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetObjectPtrLabelKHR(__int64 ptr) = 0 ;
	virtual void __cdecl glGetSamplerParameterIivEXT(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetSamplerParameterIivEXT(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetSamplerParameterIuivEXT(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetSamplerParameterIuivEXT(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterIivEXT(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterIivEXT(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterIuivEXT(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterIuivEXT(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual bool __cdecl glIsEnablediEXT(int target, int index) = 0 ;
	virtual void __cdecl glMinSampleShadingOES(float value) = 0 ;
	virtual void __cdecl glObjectLabelKHR(int identifier, int name, int length, Androidapi::Jni::Javatypes::_di_JString label_) = 0 ;
	virtual void __cdecl glObjectPtrLabelKHR(__int64 ptr, Androidapi::Jni::Javatypes::_di_JString label_) = 0 ;
	virtual void __cdecl glPatchParameteriEXT(int pname, int value) = 0 ;
	virtual void __cdecl glPopDebugGroupKHR() = 0 ;
	virtual void __cdecl glPrimitiveBoundingBoxEXT(float minX, float minY, float minZ, float minW, float maxX, float maxY, float maxZ, float maxW) = 0 ;
	virtual void __cdecl glPushDebugGroupKHR(int source, int id, int length, Androidapi::Jni::Javatypes::_di_JString message) = 0 ;
	virtual void __cdecl glSamplerParameterIivEXT(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* param, int offset) = 0 /* overload */;
	virtual void __cdecl glSamplerParameterIivEXT(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer param) = 0 /* overload */;
	virtual void __cdecl glSamplerParameterIuivEXT(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* param, int offset) = 0 /* overload */;
	virtual void __cdecl glSamplerParameterIuivEXT(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer param) = 0 /* overload */;
	virtual void __cdecl glTexBufferEXT(int target, int internalformat, int buffer) = 0 ;
	virtual void __cdecl glTexBufferRangeEXT(int target, int internalformat, int buffer, int offset, int size) = 0 ;
	virtual void __cdecl glTexParameterIivEXT(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexParameterIivEXT(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexParameterIuivEXT(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexParameterIuivEXT(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexStorage3DMultisampleOES(int target, int samples, int internalformat, int width, int height, int depth, bool fixedsamplelocations) = 0 ;
	__property int GL_BLEND_ADVANCED_COHERENT_KHR = {read=_GetGL_BLEND_ADVANCED_COHERENT_KHR};
	__property int GL_BUFFER_KHR = {read=_GetGL_BUFFER_KHR};
	__property int GL_CLAMP_TO_BORDER_EXT = {read=_GetGL_CLAMP_TO_BORDER_EXT};
	__property int GL_COLORBURN_KHR = {read=_GetGL_COLORBURN_KHR};
	__property int GL_COLORDODGE_KHR = {read=_GetGL_COLORDODGE_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_10x10_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_10x10_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_10x5_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_10x5_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_10x6_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_10x6_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_10x8_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_10x8_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_12x10_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_12x10_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_12x12_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_12x12_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_4x4_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_4x4_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_5x4_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_5x4_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_5x5_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_5x5_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_6x5_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_6x5_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_6x6_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_6x6_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_8x5_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_8x5_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_8x6_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_8x6_KHR};
	__property int GL_COMPRESSED_RGBA_ASTC_8x8_KHR = {read=_GetGL_COMPRESSED_RGBA_ASTC_8x8_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR};
	__property int GL_CONTEXT_FLAG_DEBUG_BIT_KHR = {read=_GetGL_CONTEXT_FLAG_DEBUG_BIT_KHR};
	__property int GL_DARKEN_KHR = {read=_GetGL_DARKEN_KHR};
	__property int GL_DEBUG_CALLBACK_FUNCTION_KHR = {read=_GetGL_DEBUG_CALLBACK_FUNCTION_KHR};
	__property int GL_DEBUG_CALLBACK_USER_PARAM_KHR = {read=_GetGL_DEBUG_CALLBACK_USER_PARAM_KHR};
	__property int GL_DEBUG_GROUP_STACK_DEPTH_KHR = {read=_GetGL_DEBUG_GROUP_STACK_DEPTH_KHR};
	__property int GL_DEBUG_LOGGED_MESSAGES_KHR = {read=_GetGL_DEBUG_LOGGED_MESSAGES_KHR};
	__property int GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_KHR = {read=_GetGL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_KHR};
	__property int GL_DEBUG_OUTPUT_KHR = {read=_GetGL_DEBUG_OUTPUT_KHR};
	__property int GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR = {read=_GetGL_DEBUG_OUTPUT_SYNCHRONOUS_KHR};
	__property int GL_DEBUG_SEVERITY_HIGH_KHR = {read=_GetGL_DEBUG_SEVERITY_HIGH_KHR};
	__property int GL_DEBUG_SEVERITY_LOW_KHR = {read=_GetGL_DEBUG_SEVERITY_LOW_KHR};
	__property int GL_DEBUG_SEVERITY_MEDIUM_KHR = {read=_GetGL_DEBUG_SEVERITY_MEDIUM_KHR};
	__property int GL_DEBUG_SEVERITY_NOTIFICATION_KHR = {read=_GetGL_DEBUG_SEVERITY_NOTIFICATION_KHR};
	__property int GL_DEBUG_SOURCE_API_KHR = {read=_GetGL_DEBUG_SOURCE_API_KHR};
	__property int GL_DEBUG_SOURCE_APPLICATION_KHR = {read=_GetGL_DEBUG_SOURCE_APPLICATION_KHR};
	__property int GL_DEBUG_SOURCE_OTHER_KHR = {read=_GetGL_DEBUG_SOURCE_OTHER_KHR};
	__property int GL_DEBUG_SOURCE_SHADER_COMPILER_KHR = {read=_GetGL_DEBUG_SOURCE_SHADER_COMPILER_KHR};
	__property int GL_DEBUG_SOURCE_THIRD_PARTY_KHR = {read=_GetGL_DEBUG_SOURCE_THIRD_PARTY_KHR};
	__property int GL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR = {read=_GetGL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR};
	__property int GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR = {read=_GetGL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR};
	__property int GL_DEBUG_TYPE_ERROR_KHR = {read=_GetGL_DEBUG_TYPE_ERROR_KHR};
	__property int GL_DEBUG_TYPE_MARKER_KHR = {read=_GetGL_DEBUG_TYPE_MARKER_KHR};
	__property int GL_DEBUG_TYPE_OTHER_KHR = {read=_GetGL_DEBUG_TYPE_OTHER_KHR};
	__property int GL_DEBUG_TYPE_PERFORMANCE_KHR = {read=_GetGL_DEBUG_TYPE_PERFORMANCE_KHR};
	__property int GL_DEBUG_TYPE_POP_GROUP_KHR = {read=_GetGL_DEBUG_TYPE_POP_GROUP_KHR};
	__property int GL_DEBUG_TYPE_PORTABILITY_KHR = {read=_GetGL_DEBUG_TYPE_PORTABILITY_KHR};
	__property int GL_DEBUG_TYPE_PUSH_GROUP_KHR = {read=_GetGL_DEBUG_TYPE_PUSH_GROUP_KHR};
	__property int GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR = {read=_GetGL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR};
	__property int GL_DECODE_EXT = {read=_GetGL_DECODE_EXT};
	__property int GL_DIFFERENCE_KHR = {read=_GetGL_DIFFERENCE_KHR};
	__property int GL_EXCLUSION_KHR = {read=_GetGL_EXCLUSION_KHR};
	__property int GL_FIRST_VERTEX_CONVENTION_EXT = {read=_GetGL_FIRST_VERTEX_CONVENTION_EXT};
	__property int GL_FRACTIONAL_EVEN_EXT = {read=_GetGL_FRACTIONAL_EVEN_EXT};
	__property int GL_FRACTIONAL_ODD_EXT = {read=_GetGL_FRACTIONAL_ODD_EXT};
	__property int GL_FRAGMENT_INTERPOLATION_OFFSET_BITS_OES = {read=_GetGL_FRAGMENT_INTERPOLATION_OFFSET_BITS_OES};
	__property int GL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_LAYERED_EXT};
	__property int GL_FRAMEBUFFER_DEFAULT_LAYERS_EXT = {read=_GetGL_FRAMEBUFFER_DEFAULT_LAYERS_EXT};
	__property int GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT = {read=_GetGL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS_EXT};
	__property int GL_GEOMETRY_LINKED_INPUT_TYPE_EXT = {read=_GetGL_GEOMETRY_LINKED_INPUT_TYPE_EXT};
	__property int GL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT = {read=_GetGL_GEOMETRY_LINKED_OUTPUT_TYPE_EXT};
	__property int GL_GEOMETRY_LINKED_VERTICES_OUT_EXT = {read=_GetGL_GEOMETRY_LINKED_VERTICES_OUT_EXT};
	__property int GL_GEOMETRY_SHADER_BIT_EXT = {read=_GetGL_GEOMETRY_SHADER_BIT_EXT};
	__property int GL_GEOMETRY_SHADER_EXT = {read=_GetGL_GEOMETRY_SHADER_EXT};
	__property int GL_GEOMETRY_SHADER_INVOCATIONS_EXT = {read=_GetGL_GEOMETRY_SHADER_INVOCATIONS_EXT};
	__property int GL_HARDLIGHT_KHR = {read=_GetGL_HARDLIGHT_KHR};
	__property int GL_HSL_COLOR_KHR = {read=_GetGL_HSL_COLOR_KHR};
	__property int GL_HSL_HUE_KHR = {read=_GetGL_HSL_HUE_KHR};
	__property int GL_HSL_LUMINOSITY_KHR = {read=_GetGL_HSL_LUMINOSITY_KHR};
	__property int GL_HSL_SATURATION_KHR = {read=_GetGL_HSL_SATURATION_KHR};
	__property int GL_IMAGE_BUFFER_EXT = {read=_GetGL_IMAGE_BUFFER_EXT};
	__property int GL_IMAGE_CUBE_MAP_ARRAY_EXT = {read=_GetGL_IMAGE_CUBE_MAP_ARRAY_EXT};
	__property int GL_INT_IMAGE_BUFFER_EXT = {read=_GetGL_INT_IMAGE_BUFFER_EXT};
	__property int GL_INT_IMAGE_CUBE_MAP_ARRAY_EXT = {read=_GetGL_INT_IMAGE_CUBE_MAP_ARRAY_EXT};
	__property int GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES = {read=_GetGL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES};
	__property int GL_INT_SAMPLER_BUFFER_EXT = {read=_GetGL_INT_SAMPLER_BUFFER_EXT};
	__property int GL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT = {read=_GetGL_INT_SAMPLER_CUBE_MAP_ARRAY_EXT};
	__property int GL_ISOLINES_EXT = {read=_GetGL_ISOLINES_EXT};
	__property int GL_IS_PER_PATCH_EXT = {read=_GetGL_IS_PER_PATCH_EXT};
	__property int GL_LAST_VERTEX_CONVENTION_EXT = {read=_GetGL_LAST_VERTEX_CONVENTION_EXT};
	__property int GL_LAYER_PROVOKING_VERTEX_EXT = {read=_GetGL_LAYER_PROVOKING_VERTEX_EXT};
	__property int GL_LIGHTEN_KHR = {read=_GetGL_LIGHTEN_KHR};
	__property int GL_LINES_ADJACENCY_EXT = {read=_GetGL_LINES_ADJACENCY_EXT};
	__property int GL_LINE_STRIP_ADJACENCY_EXT = {read=_GetGL_LINE_STRIP_ADJACENCY_EXT};
	__property int GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS_EXT = {read=_GetGL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS_EXT};
	__property int GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS_EXT = {read=_GetGL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS_EXT};
	__property int GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT = {read=_GetGL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT};
	__property int GL_MAX_DEBUG_GROUP_STACK_DEPTH_KHR = {read=_GetGL_MAX_DEBUG_GROUP_STACK_DEPTH_KHR};
	__property int GL_MAX_DEBUG_LOGGED_MESSAGES_KHR = {read=_GetGL_MAX_DEBUG_LOGGED_MESSAGES_KHR};
	__property int GL_MAX_DEBUG_MESSAGE_LENGTH_KHR = {read=_GetGL_MAX_DEBUG_MESSAGE_LENGTH_KHR};
	__property int GL_MAX_FRAGMENT_INTERPOLATION_OFFSET_OES = {read=_GetGL_MAX_FRAGMENT_INTERPOLATION_OFFSET_OES};
	__property int GL_MAX_FRAMEBUFFER_LAYERS_EXT = {read=_GetGL_MAX_FRAMEBUFFER_LAYERS_EXT};
	__property int GL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT = {read=_GetGL_MAX_GEOMETRY_ATOMIC_COUNTERS_EXT};
	__property int GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT = {read=_GetGL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS_EXT};
	__property int GL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT = {read=_GetGL_MAX_GEOMETRY_IMAGE_UNIFORMS_EXT};
	__property int GL_MAX_GEOMETRY_INPUT_COMPONENTS_EXT = {read=_GetGL_MAX_GEOMETRY_INPUT_COMPONENTS_EXT};
	__property int GL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT = {read=_GetGL_MAX_GEOMETRY_OUTPUT_COMPONENTS_EXT};
	__property int GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT = {read=_GetGL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT};
	__property int GL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT = {read=_GetGL_MAX_GEOMETRY_SHADER_INVOCATIONS_EXT};
	__property int GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS_EXT = {read=_GetGL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS_EXT};
	__property int GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT = {read=_GetGL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS_EXT};
	__property int GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT = {read=_GetGL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT};
	__property int GL_MAX_GEOMETRY_UNIFORM_BLOCKS_EXT = {read=_GetGL_MAX_GEOMETRY_UNIFORM_BLOCKS_EXT};
	__property int GL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT = {read=_GetGL_MAX_GEOMETRY_UNIFORM_COMPONENTS_EXT};
	__property int GL_MAX_LABEL_LENGTH_KHR = {read=_GetGL_MAX_LABEL_LENGTH_KHR};
	__property int GL_MAX_PATCH_VERTICES_EXT = {read=_GetGL_MAX_PATCH_VERTICES_EXT};
	__property int GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT = {read=_GetGL_MAX_TESS_CONTROL_ATOMIC_COUNTERS_EXT};
	__property int GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_EXT = {read=_GetGL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS_EXT};
	__property int GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT = {read=_GetGL_MAX_TESS_CONTROL_IMAGE_UNIFORMS_EXT};
	__property int GL_MAX_TESS_CONTROL_INPUT_COMPONENTS_EXT = {read=_GetGL_MAX_TESS_CONTROL_INPUT_COMPONENTS_EXT};
	__property int GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT = {read=_GetGL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS_EXT};
	__property int GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS_EXT = {read=_GetGL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS_EXT};
	__property int GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT = {read=_GetGL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS_EXT};
	__property int GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS_EXT = {read=_GetGL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS_EXT};
	__property int GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS_EXT = {read=_GetGL_MAX_TESS_CONTROL_UNIFORM_BLOCKS_EXT};
	__property int GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS_EXT = {read=_GetGL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS_EXT};
	__property int GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT = {read=_GetGL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS_EXT};
	__property int GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_EXT = {read=_GetGL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS_EXT};
	__property int GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT = {read=_GetGL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS_EXT};
	__property int GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS_EXT = {read=_GetGL_MAX_TESS_EVALUATION_INPUT_COMPONENTS_EXT};
	__property int GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT = {read=_GetGL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS_EXT};
	__property int GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS_EXT = {read=_GetGL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS_EXT};
	__property int GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT = {read=_GetGL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS_EXT};
	__property int GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS_EXT = {read=_GetGL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS_EXT};
	__property int GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT = {read=_GetGL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS_EXT};
	__property int GL_MAX_TESS_GEN_LEVEL_EXT = {read=_GetGL_MAX_TESS_GEN_LEVEL_EXT};
	__property int GL_MAX_TESS_PATCH_COMPONENTS_EXT = {read=_GetGL_MAX_TESS_PATCH_COMPONENTS_EXT};
	__property int GL_MAX_TEXTURE_BUFFER_SIZE_EXT = {read=_GetGL_MAX_TEXTURE_BUFFER_SIZE_EXT};
	__property int GL_MIN_FRAGMENT_INTERPOLATION_OFFSET_OES = {read=_GetGL_MIN_FRAGMENT_INTERPOLATION_OFFSET_OES};
	__property int GL_MIN_SAMPLE_SHADING_VALUE_OES = {read=_GetGL_MIN_SAMPLE_SHADING_VALUE_OES};
	__property int GL_MULTIPLY_KHR = {read=_GetGL_MULTIPLY_KHR};
	__property int GL_OVERLAY_KHR = {read=_GetGL_OVERLAY_KHR};
	__property int GL_PATCHES_EXT = {read=_GetGL_PATCHES_EXT};
	__property int GL_PATCH_VERTICES_EXT = {read=_GetGL_PATCH_VERTICES_EXT};
	__property int GL_PRIMITIVES_GENERATED_EXT = {read=_GetGL_PRIMITIVES_GENERATED_EXT};
	__property int GL_PRIMITIVE_BOUNDING_BOX_EXT = {read=_GetGL_PRIMITIVE_BOUNDING_BOX_EXT};
	__property int GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED = {read=_GetGL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED};
	__property int GL_PROGRAM_KHR = {read=_GetGL_PROGRAM_KHR};
	__property int GL_QUADS_EXT = {read=_GetGL_QUADS_EXT};
	__property int GL_QUERY_KHR = {read=_GetGL_QUERY_KHR};
	__property int GL_REFERENCED_BY_GEOMETRY_SHADER_EXT = {read=_GetGL_REFERENCED_BY_GEOMETRY_SHADER_EXT};
	__property int GL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT = {read=_GetGL_REFERENCED_BY_TESS_CONTROL_SHADER_EXT};
	__property int GL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT = {read=_GetGL_REFERENCED_BY_TESS_EVALUATION_SHADER_EXT};
	__property int GL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES = {read=_GetGL_SAMPLER_2D_MULTISAMPLE_ARRAY_OES};
	__property int GL_SAMPLER_BUFFER_EXT = {read=_GetGL_SAMPLER_BUFFER_EXT};
	__property int GL_SAMPLER_CUBE_MAP_ARRAY_EXT = {read=_GetGL_SAMPLER_CUBE_MAP_ARRAY_EXT};
	__property int GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT = {read=_GetGL_SAMPLER_CUBE_MAP_ARRAY_SHADOW_EXT};
	__property int GL_SAMPLER_KHR = {read=_GetGL_SAMPLER_KHR};
	__property int GL_SAMPLE_SHADING_OES = {read=_GetGL_SAMPLE_SHADING_OES};
	__property int GL_SCREEN_KHR = {read=_GetGL_SCREEN_KHR};
	__property int GL_SHADER_KHR = {read=_GetGL_SHADER_KHR};
	__property int GL_SKIP_DECODE_EXT = {read=_GetGL_SKIP_DECODE_EXT};
	__property int GL_SOFTLIGHT_KHR = {read=_GetGL_SOFTLIGHT_KHR};
	__property int GL_STACK_OVERFLOW_KHR = {read=_GetGL_STACK_OVERFLOW_KHR};
	__property int GL_STACK_UNDERFLOW_KHR = {read=_GetGL_STACK_UNDERFLOW_KHR};
	__property int GL_STENCIL_INDEX8_OES = {read=_GetGL_STENCIL_INDEX8_OES};
	__property int GL_STENCIL_INDEX_OES = {read=_GetGL_STENCIL_INDEX_OES};
	__property int GL_TESS_CONTROL_OUTPUT_VERTICES_EXT = {read=_GetGL_TESS_CONTROL_OUTPUT_VERTICES_EXT};
	__property int GL_TESS_CONTROL_SHADER_BIT_EXT = {read=_GetGL_TESS_CONTROL_SHADER_BIT_EXT};
	__property int GL_TESS_CONTROL_SHADER_EXT = {read=_GetGL_TESS_CONTROL_SHADER_EXT};
	__property int GL_TESS_EVALUATION_SHADER_BIT_EXT = {read=_GetGL_TESS_EVALUATION_SHADER_BIT_EXT};
	__property int GL_TESS_EVALUATION_SHADER_EXT = {read=_GetGL_TESS_EVALUATION_SHADER_EXT};
	__property int GL_TESS_GEN_MODE_EXT = {read=_GetGL_TESS_GEN_MODE_EXT};
	__property int GL_TESS_GEN_POINT_MODE_EXT = {read=_GetGL_TESS_GEN_POINT_MODE_EXT};
	__property int GL_TESS_GEN_SPACING_EXT = {read=_GetGL_TESS_GEN_SPACING_EXT};
	__property int GL_TESS_GEN_VERTEX_ORDER_EXT = {read=_GetGL_TESS_GEN_VERTEX_ORDER_EXT};
	__property int GL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES = {read=_GetGL_TEXTURE_2D_MULTISAMPLE_ARRAY_OES};
	__property int GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES = {read=_GetGL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY_OES};
	__property int GL_TEXTURE_BINDING_BUFFER_EXT = {read=_GetGL_TEXTURE_BINDING_BUFFER_EXT};
	__property int GL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT = {read=_GetGL_TEXTURE_BINDING_CUBE_MAP_ARRAY_EXT};
	__property int GL_TEXTURE_BORDER_COLOR_EXT = {read=_GetGL_TEXTURE_BORDER_COLOR_EXT};
	__property int GL_TEXTURE_BUFFER_BINDING_EXT = {read=_GetGL_TEXTURE_BUFFER_BINDING_EXT};
	__property int GL_TEXTURE_BUFFER_DATA_STORE_BINDING_EXT = {read=_GetGL_TEXTURE_BUFFER_DATA_STORE_BINDING_EXT};
	__property int GL_TEXTURE_BUFFER_EXT = {read=_GetGL_TEXTURE_BUFFER_EXT};
	__property int GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT_EXT = {read=_GetGL_TEXTURE_BUFFER_OFFSET_ALIGNMENT_EXT};
	__property int GL_TEXTURE_BUFFER_OFFSET_EXT = {read=_GetGL_TEXTURE_BUFFER_OFFSET_EXT};
	__property int GL_TEXTURE_BUFFER_SIZE_EXT = {read=_GetGL_TEXTURE_BUFFER_SIZE_EXT};
	__property int GL_TEXTURE_CUBE_MAP_ARRAY_EXT = {read=_GetGL_TEXTURE_CUBE_MAP_ARRAY_EXT};
	__property int GL_TEXTURE_SRGB_DECODE_EXT = {read=_GetGL_TEXTURE_SRGB_DECODE_EXT};
	__property int GL_TRIANGLES_ADJACENCY_EXT = {read=_GetGL_TRIANGLES_ADJACENCY_EXT};
	__property int GL_TRIANGLE_STRIP_ADJACENCY_EXT = {read=_GetGL_TRIANGLE_STRIP_ADJACENCY_EXT};
	__property int GL_UNDEFINED_VERTEX_EXT = {read=_GetGL_UNDEFINED_VERTEX_EXT};
	__property int GL_UNSIGNED_INT_IMAGE_BUFFER_EXT = {read=_GetGL_UNSIGNED_INT_IMAGE_BUFFER_EXT};
	__property int GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT = {read=_GetGL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY_EXT};
	__property int GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES = {read=_GetGL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY_OES};
	__property int GL_UNSIGNED_INT_SAMPLER_BUFFER_EXT = {read=_GetGL_UNSIGNED_INT_SAMPLER_BUFFER_EXT};
	__property int GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT = {read=_GetGL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY_EXT};
	__property int GL_VERTEX_ARRAY_KHR = {read=_GetGL_VERTEX_ARRAY_KHR};
};

__interface  INTERFACE_UUID("{0A0B9045-27CE-420A-8B5D-3D92AAD1CF4A}") JGLES31Ext  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLES31Ext : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES31ExtClass,_di_JGLES31Ext>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES31ExtClass,_di_JGLES31Ext> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLES31Ext() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES31ExtClass,_di_JGLES31Ext>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLES31Ext() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FCF53F5F-55C4-4AB9-914A-B9234E78A6E8}") JGLES31Ext_DebugProcKHRClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{E300468C-5411-4010-BEDA-5EC5B748C228}") JGLES31Ext_DebugProcKHR  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMessage(int source, int type_, int id, int severity, Androidapi::Jni::Javatypes::_di_JString message) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLES31Ext_DebugProcKHR : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES31Ext_DebugProcKHRClass,_di_JGLES31Ext_DebugProcKHR>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES31Ext_DebugProcKHRClass,_di_JGLES31Ext_DebugProcKHR> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLES31Ext_DebugProcKHR() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES31Ext_DebugProcKHRClass,_di_JGLES31Ext_DebugProcKHR>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLES31Ext_DebugProcKHR() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C83CC8F0-59E2-43B4-B4E6-99C53E4943D7}") JGLES32Class  : public JGLES31Class 
{
	virtual int __cdecl _GetGL_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_CLAMP_TO_BORDER() = 0 ;
	virtual int __cdecl _GetGL_COLORBURN() = 0 ;
	virtual int __cdecl _GetGL_COLORDODGE() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_10x10() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_10x5() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_10x6() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_10x8() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_12x10() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_12x12() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_4x4() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_5x4() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_5x5() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_6x5() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_6x6() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_8x5() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_8x6() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_RGBA_ASTC_8x8() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6() = 0 ;
	virtual int __cdecl _GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8() = 0 ;
	virtual int __cdecl _GetGL_CONTEXT_FLAGS() = 0 ;
	virtual int __cdecl _GetGL_CONTEXT_FLAG_DEBUG_BIT() = 0 ;
	virtual int __cdecl _GetGL_CONTEXT_FLAG_ROBUST_ACCESS_BIT() = 0 ;
	virtual int __cdecl _GetGL_CONTEXT_LOST() = 0 ;
	virtual int __cdecl _GetGL_DARKEN() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_CALLBACK_FUNCTION() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_CALLBACK_USER_PARAM() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_GROUP_STACK_DEPTH() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_LOGGED_MESSAGES() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_OUTPUT() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_OUTPUT_SYNCHRONOUS() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SEVERITY_HIGH() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SEVERITY_LOW() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SEVERITY_MEDIUM() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SEVERITY_NOTIFICATION() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_API() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_APPLICATION() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_OTHER() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_SHADER_COMPILER() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_THIRD_PARTY() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_SOURCE_WINDOW_SYSTEM() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_DEPRECATED_BEHAVIOR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_ERROR() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_MARKER() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_OTHER() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_PERFORMANCE() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_POP_GROUP() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_PORTABILITY() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_PUSH_GROUP() = 0 ;
	virtual int __cdecl _GetGL_DEBUG_TYPE_UNDEFINED_BEHAVIOR() = 0 ;
	virtual int __cdecl _GetGL_DIFFERENCE() = 0 ;
	virtual int __cdecl _GetGL_EXCLUSION() = 0 ;
	virtual int __cdecl _GetGL_FIRST_VERTEX_CONVENTION() = 0 ;
	virtual int __cdecl _GetGL_FRACTIONAL_EVEN() = 0 ;
	virtual int __cdecl _GetGL_FRACTIONAL_ODD() = 0 ;
	virtual int __cdecl _GetGL_FRAGMENT_INTERPOLATION_OFFSET_BITS() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_ATTACHMENT_LAYERED() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_DEFAULT_LAYERS() = 0 ;
	virtual int __cdecl _GetGL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_INPUT_TYPE() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_OUTPUT_TYPE() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_SHADER() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_SHADER_BIT() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_SHADER_INVOCATIONS() = 0 ;
	virtual int __cdecl _GetGL_GEOMETRY_VERTICES_OUT() = 0 ;
	virtual int __cdecl _GetGL_GUILTY_CONTEXT_RESET() = 0 ;
	virtual int __cdecl _GetGL_HARDLIGHT() = 0 ;
	virtual int __cdecl _GetGL_HSL_COLOR() = 0 ;
	virtual int __cdecl _GetGL_HSL_HUE() = 0 ;
	virtual int __cdecl _GetGL_HSL_LUMINOSITY() = 0 ;
	virtual int __cdecl _GetGL_HSL_SATURATION() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_IMAGE_CUBE_MAP_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_INNOCENT_CONTEXT_RESET() = 0 ;
	virtual int __cdecl _GetGL_INT_IMAGE_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_INT_IMAGE_CUBE_MAP_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_INT_SAMPLER_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_INT_SAMPLER_CUBE_MAP_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_ISOLINES() = 0 ;
	virtual int __cdecl _GetGL_IS_PER_PATCH() = 0 ;
	virtual int __cdecl _GetGL_LAST_VERTEX_CONVENTION() = 0 ;
	virtual int __cdecl _GetGL_LAYER_PROVOKING_VERTEX() = 0 ;
	virtual int __cdecl _GetGL_LIGHTEN() = 0 ;
	virtual int __cdecl _GetGL_LINES_ADJACENCY() = 0 ;
	virtual int __cdecl _GetGL_LINE_STRIP_ADJACENCY() = 0 ;
	virtual int __cdecl _GetGL_LOSE_CONTEXT_ON_RESET() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_DEBUG_GROUP_STACK_DEPTH() = 0 ;
	virtual int __cdecl _GetGL_MAX_DEBUG_LOGGED_MESSAGES() = 0 ;
	virtual int __cdecl _GetGL_MAX_DEBUG_MESSAGE_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAGMENT_INTERPOLATION_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_MAX_FRAMEBUFFER_LAYERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_ATOMIC_COUNTERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_IMAGE_UNIFORMS() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_INPUT_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_OUTPUT_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_OUTPUT_VERTICES() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_SHADER_INVOCATIONS() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_UNIFORM_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_GEOMETRY_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_LABEL_LENGTH() = 0 ;
	virtual int __cdecl _GetGL_MAX_PATCH_VERTICES() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_ATOMIC_COUNTERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_IMAGE_UNIFORMS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_INPUT_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_UNIFORM_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_INPUT_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_GEN_LEVEL() = 0 ;
	virtual int __cdecl _GetGL_MAX_TESS_PATCH_COMPONENTS() = 0 ;
	virtual int __cdecl _GetGL_MAX_TEXTURE_BUFFER_SIZE() = 0 ;
	virtual int __cdecl _GetGL_MIN_FRAGMENT_INTERPOLATION_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_MIN_SAMPLE_SHADING_VALUE() = 0 ;
	virtual int __cdecl _GetGL_MULTIPLY() = 0 ;
	virtual int __cdecl _GetGL_MULTISAMPLE_LINE_WIDTH_GRANULARITY() = 0 ;
	virtual int __cdecl _GetGL_MULTISAMPLE_LINE_WIDTH_RANGE() = 0 ;
	virtual int __cdecl _GetGL_NO_RESET_NOTIFICATION() = 0 ;
	virtual int __cdecl _GetGL_OVERLAY() = 0 ;
	virtual int __cdecl _GetGL_PATCHES() = 0 ;
	virtual int __cdecl _GetGL_PATCH_VERTICES() = 0 ;
	virtual int __cdecl _GetGL_PRIMITIVES_GENERATED() = 0 ;
	virtual int __cdecl _GetGL_PRIMITIVE_BOUNDING_BOX() = 0 ;
	virtual int __cdecl _GetGL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED() = 0 ;
	virtual int __cdecl _GetGL_PROGRAM() = 0 ;
	virtual int __cdecl _GetGL_PROGRAM_PIPELINE() = 0 ;
	virtual int __cdecl _GetGL_QUADS() = 0 ;
	virtual int __cdecl _GetGL_QUERY() = 0 ;
	virtual int __cdecl _GetGL_REFERENCED_BY_GEOMETRY_SHADER() = 0 ;
	virtual int __cdecl _GetGL_REFERENCED_BY_TESS_CONTROL_SHADER() = 0 ;
	virtual int __cdecl _GetGL_REFERENCED_BY_TESS_EVALUATION_SHADER() = 0 ;
	virtual int __cdecl _GetGL_RESET_NOTIFICATION_STRATEGY() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_2D_MULTISAMPLE_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_CUBE_MAP_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_SAMPLER_CUBE_MAP_ARRAY_SHADOW() = 0 ;
	virtual int __cdecl _GetGL_SAMPLE_SHADING() = 0 ;
	virtual int __cdecl _GetGL_SCREEN() = 0 ;
	virtual int __cdecl _GetGL_SHADER() = 0 ;
	virtual int __cdecl _GetGL_SOFTLIGHT() = 0 ;
	virtual int __cdecl _GetGL_STACK_OVERFLOW() = 0 ;
	virtual int __cdecl _GetGL_STACK_UNDERFLOW() = 0 ;
	virtual int __cdecl _GetGL_TESS_CONTROL_OUTPUT_VERTICES() = 0 ;
	virtual int __cdecl _GetGL_TESS_CONTROL_SHADER() = 0 ;
	virtual int __cdecl _GetGL_TESS_CONTROL_SHADER_BIT() = 0 ;
	virtual int __cdecl _GetGL_TESS_EVALUATION_SHADER() = 0 ;
	virtual int __cdecl _GetGL_TESS_EVALUATION_SHADER_BIT() = 0 ;
	virtual int __cdecl _GetGL_TESS_GEN_MODE() = 0 ;
	virtual int __cdecl _GetGL_TESS_GEN_POINT_MODE() = 0 ;
	virtual int __cdecl _GetGL_TESS_GEN_SPACING() = 0 ;
	virtual int __cdecl _GetGL_TESS_GEN_VERTEX_ORDER() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_2D_MULTISAMPLE_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BINDING_CUBE_MAP_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BORDER_COLOR() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER_BINDING() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER_DATA_STORE_BINDING() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER_OFFSET() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER_OFFSET_ALIGNMENT() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_BUFFER_SIZE() = 0 ;
	virtual int __cdecl _GetGL_TEXTURE_CUBE_MAP_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_TRIANGLES_ADJACENCY() = 0 ;
	virtual int __cdecl _GetGL_TRIANGLE_STRIP_ADJACENCY() = 0 ;
	virtual int __cdecl _GetGL_UNDEFINED_VERTEX() = 0 ;
	virtual int __cdecl _GetGL_UNKNOWN_CONTEXT_RESET() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_IMAGE_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_SAMPLER_BUFFER() = 0 ;
	virtual int __cdecl _GetGL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY() = 0 ;
	virtual int __cdecl _GetGL_VERTEX_ARRAY() = 0 ;
	virtual void __cdecl glBlendBarrier() = 0 ;
	virtual void __cdecl glBlendEquationSeparatei(int buf, int modeRGB, int modeAlpha) = 0 ;
	virtual void __cdecl glBlendEquationi(int buf, int mode) = 0 ;
	virtual void __cdecl glBlendFuncSeparatei(int buf, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) = 0 ;
	virtual void __cdecl glBlendFunci(int buf, int src, int dst) = 0 ;
	virtual void __cdecl glColorMaski(int index, bool r, bool g, bool b, bool a) = 0 ;
	virtual void __cdecl glCopyImageSubData(int srcName, int srcTarget, int srcLevel, int srcX, int srcY, int srcZ, int dstName, int dstTarget, int dstLevel, int dstX, int dstY, int dstZ, int srcWidth, int srcHeight, int srcDepth) = 0 ;
	virtual void __cdecl glDebugMessageCallback(_di_JGLES32_DebugProc callback) = 0 ;
	virtual void __cdecl glDebugMessageControl(int source, int type_, int severity, int count, Androidapi::Jnibridge::TJavaArray__1<int>* ids, int offset, bool enabled) = 0 /* overload */;
	virtual void __cdecl glDebugMessageControl(int source, int type_, int severity, int count, Androidapi::Jni::Javatypes::_di_JIntBuffer ids, bool enabled) = 0 /* overload */;
	virtual void __cdecl glDebugMessageInsert(int source, int type_, int id, int severity, int length, Androidapi::Jni::Javatypes::_di_JString buf) = 0 ;
	virtual void __cdecl glDisablei(int target, int index) = 0 ;
	virtual void __cdecl glDrawElementsBaseVertex(int mode, int count, int type_, Androidapi::Jni::Javatypes::_di_JBuffer indices, int basevertex) = 0 ;
	virtual void __cdecl glDrawElementsInstancedBaseVertex(int mode, int count, int type_, Androidapi::Jni::Javatypes::_di_JBuffer indices, int instanceCount, int basevertex) = 0 /* overload */;
	virtual void __cdecl glDrawElementsInstancedBaseVertex(int mode, int count, int type_, int indicesOffset, int instanceCount, int basevertex) = 0 /* overload */;
	virtual void __cdecl glDrawRangeElementsBaseVertex(int mode, int start, int end_, int count, int type_, Androidapi::Jni::Javatypes::_di_JBuffer indices, int basevertex) = 0 ;
	virtual void __cdecl glEnablei(int target, int index) = 0 ;
	virtual void __cdecl glFramebufferTexture(int target, int attachment, int texture, int level) = 0 ;
	virtual int __cdecl glGetDebugMessageLog(int count, int bufSize, Androidapi::Jnibridge::TJavaArray__1<int>* sources, int sourcesOffset, Androidapi::Jnibridge::TJavaArray__1<int>* types, int typesOffset, Androidapi::Jnibridge::TJavaArray__1<int>* ids, int idsOffset, Androidapi::Jnibridge::TJavaArray__1<int>* severities, int severitiesOffset, Androidapi::Jnibridge::TJavaArray__1<int>* lengths, int lengthsOffset, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* messageLog, int messageLogOffset) = 0 /* overload */;
	virtual int __cdecl glGetDebugMessageLog(int count, Androidapi::Jni::Javatypes::_di_JIntBuffer sources, Androidapi::Jni::Javatypes::_di_JIntBuffer types, Androidapi::Jni::Javatypes::_di_JIntBuffer ids, Androidapi::Jni::Javatypes::_di_JIntBuffer severities, Androidapi::Jni::Javatypes::_di_JIntBuffer lengths, Androidapi::Jni::Javatypes::_di_JByteBuffer messageLog) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl glGetDebugMessageLog(int count, Androidapi::Jnibridge::TJavaArray__1<int>* sources, int sourcesOffset, Androidapi::Jnibridge::TJavaArray__1<int>* types, int typesOffset, Androidapi::Jnibridge::TJavaArray__1<int>* ids, int idsOffset, Androidapi::Jnibridge::TJavaArray__1<int>* severities, int severitiesOffset) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl glGetDebugMessageLog(int count, Androidapi::Jni::Javatypes::_di_JIntBuffer sources, Androidapi::Jni::Javatypes::_di_JIntBuffer types, Androidapi::Jni::Javatypes::_di_JIntBuffer ids, Androidapi::Jni::Javatypes::_di_JIntBuffer severities) = 0 /* overload */;
	virtual int __cdecl glGetGraphicsResetStatus() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetObjectLabel(int identifier, int name) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl glGetObjectPtrLabel(__int64 ptr) = 0 ;
	virtual __int64 __cdecl glGetPointerv(int pname) = 0 ;
	virtual void __cdecl glGetSamplerParameterIiv(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetSamplerParameterIiv(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetSamplerParameterIuiv(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetSamplerParameterIuiv(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterIiv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterIiv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterIuiv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetTexParameterIuiv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetnUniformfv(int program_, int location, int bufSize, Androidapi::Jnibridge::TJavaArray__1<float>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetnUniformfv(int program_, int location, int bufSize, Androidapi::Jni::Javatypes::_di_JFloatBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetnUniformiv(int program_, int location, int bufSize, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetnUniformiv(int program_, int location, int bufSize, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glGetnUniformuiv(int program_, int location, int bufSize, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glGetnUniformuiv(int program_, int location, int bufSize, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual bool __cdecl glIsEnabledi(int target, int index) = 0 ;
	virtual void __cdecl glMinSampleShading(float value) = 0 ;
	virtual void __cdecl glObjectLabel(int identifier, int name, int length, Androidapi::Jni::Javatypes::_di_JString label_) = 0 ;
	virtual void __cdecl glObjectPtrLabel(__int64 ptr, Androidapi::Jni::Javatypes::_di_JString label_) = 0 ;
	virtual void __cdecl glPatchParameteri(int pname, int value) = 0 ;
	virtual void __cdecl glPopDebugGroup() = 0 ;
	virtual void __cdecl glPrimitiveBoundingBox(float minX, float minY, float minZ, float minW, float maxX, float maxY, float maxZ, float maxW) = 0 ;
	virtual void __cdecl glPushDebugGroup(int source, int id, int length, Androidapi::Jni::Javatypes::_di_JString message) = 0 ;
	virtual void __cdecl glReadnPixels(int x, int y, int width, int height, int format, int type_, int bufSize, Androidapi::Jni::Javatypes::_di_JBuffer data) = 0 ;
	virtual void __cdecl glSamplerParameterIiv(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* param, int offset) = 0 /* overload */;
	virtual void __cdecl glSamplerParameterIiv(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer param) = 0 /* overload */;
	virtual void __cdecl glSamplerParameterIuiv(int sampler, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* param, int offset) = 0 /* overload */;
	virtual void __cdecl glSamplerParameterIuiv(int sampler, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer param) = 0 /* overload */;
	virtual void __cdecl glTexBuffer(int target, int internalformat, int buffer) = 0 ;
	virtual void __cdecl glTexBufferRange(int target, int internalformat, int buffer, int offset, int size) = 0 ;
	virtual void __cdecl glTexParameterIiv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexParameterIiv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexParameterIuiv(int target, int pname, Androidapi::Jnibridge::TJavaArray__1<int>* params, int offset) = 0 /* overload */;
	virtual void __cdecl glTexParameterIuiv(int target, int pname, Androidapi::Jni::Javatypes::_di_JIntBuffer params) = 0 /* overload */;
	virtual void __cdecl glTexStorage3DMultisample(int target, int samples, int internalformat, int width, int height, int depth, bool fixedsamplelocations) = 0 ;
	__property int GL_BUFFER = {read=_GetGL_BUFFER};
	__property int GL_CLAMP_TO_BORDER = {read=_GetGL_CLAMP_TO_BORDER};
	__property int GL_COLORBURN = {read=_GetGL_COLORBURN};
	__property int GL_COLORDODGE = {read=_GetGL_COLORDODGE};
	__property int GL_COMPRESSED_RGBA_ASTC_10x10 = {read=_GetGL_COMPRESSED_RGBA_ASTC_10x10};
	__property int GL_COMPRESSED_RGBA_ASTC_10x5 = {read=_GetGL_COMPRESSED_RGBA_ASTC_10x5};
	__property int GL_COMPRESSED_RGBA_ASTC_10x6 = {read=_GetGL_COMPRESSED_RGBA_ASTC_10x6};
	__property int GL_COMPRESSED_RGBA_ASTC_10x8 = {read=_GetGL_COMPRESSED_RGBA_ASTC_10x8};
	__property int GL_COMPRESSED_RGBA_ASTC_12x10 = {read=_GetGL_COMPRESSED_RGBA_ASTC_12x10};
	__property int GL_COMPRESSED_RGBA_ASTC_12x12 = {read=_GetGL_COMPRESSED_RGBA_ASTC_12x12};
	__property int GL_COMPRESSED_RGBA_ASTC_4x4 = {read=_GetGL_COMPRESSED_RGBA_ASTC_4x4};
	__property int GL_COMPRESSED_RGBA_ASTC_5x4 = {read=_GetGL_COMPRESSED_RGBA_ASTC_5x4};
	__property int GL_COMPRESSED_RGBA_ASTC_5x5 = {read=_GetGL_COMPRESSED_RGBA_ASTC_5x5};
	__property int GL_COMPRESSED_RGBA_ASTC_6x5 = {read=_GetGL_COMPRESSED_RGBA_ASTC_6x5};
	__property int GL_COMPRESSED_RGBA_ASTC_6x6 = {read=_GetGL_COMPRESSED_RGBA_ASTC_6x6};
	__property int GL_COMPRESSED_RGBA_ASTC_8x5 = {read=_GetGL_COMPRESSED_RGBA_ASTC_8x5};
	__property int GL_COMPRESSED_RGBA_ASTC_8x6 = {read=_GetGL_COMPRESSED_RGBA_ASTC_8x6};
	__property int GL_COMPRESSED_RGBA_ASTC_8x8 = {read=_GetGL_COMPRESSED_RGBA_ASTC_8x8};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6};
	__property int GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8 = {read=_GetGL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8};
	__property int GL_CONTEXT_FLAGS = {read=_GetGL_CONTEXT_FLAGS};
	__property int GL_CONTEXT_FLAG_DEBUG_BIT = {read=_GetGL_CONTEXT_FLAG_DEBUG_BIT};
	__property int GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT = {read=_GetGL_CONTEXT_FLAG_ROBUST_ACCESS_BIT};
	__property int GL_CONTEXT_LOST = {read=_GetGL_CONTEXT_LOST};
	__property int GL_DARKEN = {read=_GetGL_DARKEN};
	__property int GL_DEBUG_CALLBACK_FUNCTION = {read=_GetGL_DEBUG_CALLBACK_FUNCTION};
	__property int GL_DEBUG_CALLBACK_USER_PARAM = {read=_GetGL_DEBUG_CALLBACK_USER_PARAM};
	__property int GL_DEBUG_GROUP_STACK_DEPTH = {read=_GetGL_DEBUG_GROUP_STACK_DEPTH};
	__property int GL_DEBUG_LOGGED_MESSAGES = {read=_GetGL_DEBUG_LOGGED_MESSAGES};
	__property int GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH = {read=_GetGL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH};
	__property int GL_DEBUG_OUTPUT = {read=_GetGL_DEBUG_OUTPUT};
	__property int GL_DEBUG_OUTPUT_SYNCHRONOUS = {read=_GetGL_DEBUG_OUTPUT_SYNCHRONOUS};
	__property int GL_DEBUG_SEVERITY_HIGH = {read=_GetGL_DEBUG_SEVERITY_HIGH};
	__property int GL_DEBUG_SEVERITY_LOW = {read=_GetGL_DEBUG_SEVERITY_LOW};
	__property int GL_DEBUG_SEVERITY_MEDIUM = {read=_GetGL_DEBUG_SEVERITY_MEDIUM};
	__property int GL_DEBUG_SEVERITY_NOTIFICATION = {read=_GetGL_DEBUG_SEVERITY_NOTIFICATION};
	__property int GL_DEBUG_SOURCE_API = {read=_GetGL_DEBUG_SOURCE_API};
	__property int GL_DEBUG_SOURCE_APPLICATION = {read=_GetGL_DEBUG_SOURCE_APPLICATION};
	__property int GL_DEBUG_SOURCE_OTHER = {read=_GetGL_DEBUG_SOURCE_OTHER};
	__property int GL_DEBUG_SOURCE_SHADER_COMPILER = {read=_GetGL_DEBUG_SOURCE_SHADER_COMPILER};
	__property int GL_DEBUG_SOURCE_THIRD_PARTY = {read=_GetGL_DEBUG_SOURCE_THIRD_PARTY};
	__property int GL_DEBUG_SOURCE_WINDOW_SYSTEM = {read=_GetGL_DEBUG_SOURCE_WINDOW_SYSTEM};
	__property int GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR = {read=_GetGL_DEBUG_TYPE_DEPRECATED_BEHAVIOR};
	__property int GL_DEBUG_TYPE_ERROR = {read=_GetGL_DEBUG_TYPE_ERROR};
	__property int GL_DEBUG_TYPE_MARKER = {read=_GetGL_DEBUG_TYPE_MARKER};
	__property int GL_DEBUG_TYPE_OTHER = {read=_GetGL_DEBUG_TYPE_OTHER};
	__property int GL_DEBUG_TYPE_PERFORMANCE = {read=_GetGL_DEBUG_TYPE_PERFORMANCE};
	__property int GL_DEBUG_TYPE_POP_GROUP = {read=_GetGL_DEBUG_TYPE_POP_GROUP};
	__property int GL_DEBUG_TYPE_PORTABILITY = {read=_GetGL_DEBUG_TYPE_PORTABILITY};
	__property int GL_DEBUG_TYPE_PUSH_GROUP = {read=_GetGL_DEBUG_TYPE_PUSH_GROUP};
	__property int GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR = {read=_GetGL_DEBUG_TYPE_UNDEFINED_BEHAVIOR};
	__property int GL_DIFFERENCE = {read=_GetGL_DIFFERENCE};
	__property int GL_EXCLUSION = {read=_GetGL_EXCLUSION};
	__property int GL_FIRST_VERTEX_CONVENTION = {read=_GetGL_FIRST_VERTEX_CONVENTION};
	__property int GL_FRACTIONAL_EVEN = {read=_GetGL_FRACTIONAL_EVEN};
	__property int GL_FRACTIONAL_ODD = {read=_GetGL_FRACTIONAL_ODD};
	__property int GL_FRAGMENT_INTERPOLATION_OFFSET_BITS = {read=_GetGL_FRAGMENT_INTERPOLATION_OFFSET_BITS};
	__property int GL_FRAMEBUFFER_ATTACHMENT_LAYERED = {read=_GetGL_FRAMEBUFFER_ATTACHMENT_LAYERED};
	__property int GL_FRAMEBUFFER_DEFAULT_LAYERS = {read=_GetGL_FRAMEBUFFER_DEFAULT_LAYERS};
	__property int GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS = {read=_GetGL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS};
	__property int GL_GEOMETRY_INPUT_TYPE = {read=_GetGL_GEOMETRY_INPUT_TYPE};
	__property int GL_GEOMETRY_OUTPUT_TYPE = {read=_GetGL_GEOMETRY_OUTPUT_TYPE};
	__property int GL_GEOMETRY_SHADER = {read=_GetGL_GEOMETRY_SHADER};
	__property int GL_GEOMETRY_SHADER_BIT = {read=_GetGL_GEOMETRY_SHADER_BIT};
	__property int GL_GEOMETRY_SHADER_INVOCATIONS = {read=_GetGL_GEOMETRY_SHADER_INVOCATIONS};
	__property int GL_GEOMETRY_VERTICES_OUT = {read=_GetGL_GEOMETRY_VERTICES_OUT};
	__property int GL_GUILTY_CONTEXT_RESET = {read=_GetGL_GUILTY_CONTEXT_RESET};
	__property int GL_HARDLIGHT = {read=_GetGL_HARDLIGHT};
	__property int GL_HSL_COLOR = {read=_GetGL_HSL_COLOR};
	__property int GL_HSL_HUE = {read=_GetGL_HSL_HUE};
	__property int GL_HSL_LUMINOSITY = {read=_GetGL_HSL_LUMINOSITY};
	__property int GL_HSL_SATURATION = {read=_GetGL_HSL_SATURATION};
	__property int GL_IMAGE_BUFFER = {read=_GetGL_IMAGE_BUFFER};
	__property int GL_IMAGE_CUBE_MAP_ARRAY = {read=_GetGL_IMAGE_CUBE_MAP_ARRAY};
	__property int GL_INNOCENT_CONTEXT_RESET = {read=_GetGL_INNOCENT_CONTEXT_RESET};
	__property int GL_INT_IMAGE_BUFFER = {read=_GetGL_INT_IMAGE_BUFFER};
	__property int GL_INT_IMAGE_CUBE_MAP_ARRAY = {read=_GetGL_INT_IMAGE_CUBE_MAP_ARRAY};
	__property int GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = {read=_GetGL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY};
	__property int GL_INT_SAMPLER_BUFFER = {read=_GetGL_INT_SAMPLER_BUFFER};
	__property int GL_INT_SAMPLER_CUBE_MAP_ARRAY = {read=_GetGL_INT_SAMPLER_CUBE_MAP_ARRAY};
	__property int GL_ISOLINES = {read=_GetGL_ISOLINES};
	__property int GL_IS_PER_PATCH = {read=_GetGL_IS_PER_PATCH};
	__property int GL_LAST_VERTEX_CONVENTION = {read=_GetGL_LAST_VERTEX_CONVENTION};
	__property int GL_LAYER_PROVOKING_VERTEX = {read=_GetGL_LAYER_PROVOKING_VERTEX};
	__property int GL_LIGHTEN = {read=_GetGL_LIGHTEN};
	__property int GL_LINES_ADJACENCY = {read=_GetGL_LINES_ADJACENCY};
	__property int GL_LINE_STRIP_ADJACENCY = {read=_GetGL_LINE_STRIP_ADJACENCY};
	__property int GL_LOSE_CONTEXT_ON_RESET = {read=_GetGL_LOSE_CONTEXT_ON_RESET};
	__property int GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS = {read=_GetGL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS};
	__property int GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS = {read=_GetGL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS};
	__property int GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS = {read=_GetGL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS};
	__property int GL_MAX_DEBUG_GROUP_STACK_DEPTH = {read=_GetGL_MAX_DEBUG_GROUP_STACK_DEPTH};
	__property int GL_MAX_DEBUG_LOGGED_MESSAGES = {read=_GetGL_MAX_DEBUG_LOGGED_MESSAGES};
	__property int GL_MAX_DEBUG_MESSAGE_LENGTH = {read=_GetGL_MAX_DEBUG_MESSAGE_LENGTH};
	__property int GL_MAX_FRAGMENT_INTERPOLATION_OFFSET = {read=_GetGL_MAX_FRAGMENT_INTERPOLATION_OFFSET};
	__property int GL_MAX_FRAMEBUFFER_LAYERS = {read=_GetGL_MAX_FRAMEBUFFER_LAYERS};
	__property int GL_MAX_GEOMETRY_ATOMIC_COUNTERS = {read=_GetGL_MAX_GEOMETRY_ATOMIC_COUNTERS};
	__property int GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS = {read=_GetGL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS};
	__property int GL_MAX_GEOMETRY_IMAGE_UNIFORMS = {read=_GetGL_MAX_GEOMETRY_IMAGE_UNIFORMS};
	__property int GL_MAX_GEOMETRY_INPUT_COMPONENTS = {read=_GetGL_MAX_GEOMETRY_INPUT_COMPONENTS};
	__property int GL_MAX_GEOMETRY_OUTPUT_COMPONENTS = {read=_GetGL_MAX_GEOMETRY_OUTPUT_COMPONENTS};
	__property int GL_MAX_GEOMETRY_OUTPUT_VERTICES = {read=_GetGL_MAX_GEOMETRY_OUTPUT_VERTICES};
	__property int GL_MAX_GEOMETRY_SHADER_INVOCATIONS = {read=_GetGL_MAX_GEOMETRY_SHADER_INVOCATIONS};
	__property int GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS = {read=_GetGL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS};
	__property int GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS = {read=_GetGL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS};
	__property int GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS = {read=_GetGL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS};
	__property int GL_MAX_GEOMETRY_UNIFORM_BLOCKS = {read=_GetGL_MAX_GEOMETRY_UNIFORM_BLOCKS};
	__property int GL_MAX_GEOMETRY_UNIFORM_COMPONENTS = {read=_GetGL_MAX_GEOMETRY_UNIFORM_COMPONENTS};
	__property int GL_MAX_LABEL_LENGTH = {read=_GetGL_MAX_LABEL_LENGTH};
	__property int GL_MAX_PATCH_VERTICES = {read=_GetGL_MAX_PATCH_VERTICES};
	__property int GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS = {read=_GetGL_MAX_TESS_CONTROL_ATOMIC_COUNTERS};
	__property int GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS = {read=_GetGL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS};
	__property int GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS = {read=_GetGL_MAX_TESS_CONTROL_IMAGE_UNIFORMS};
	__property int GL_MAX_TESS_CONTROL_INPUT_COMPONENTS = {read=_GetGL_MAX_TESS_CONTROL_INPUT_COMPONENTS};
	__property int GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS = {read=_GetGL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS};
	__property int GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS = {read=_GetGL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS};
	__property int GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS = {read=_GetGL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS};
	__property int GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS = {read=_GetGL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS};
	__property int GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS = {read=_GetGL_MAX_TESS_CONTROL_UNIFORM_BLOCKS};
	__property int GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS = {read=_GetGL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS};
	__property int GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS = {read=_GetGL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS};
	__property int GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS = {read=_GetGL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS};
	__property int GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS = {read=_GetGL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS};
	__property int GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS = {read=_GetGL_MAX_TESS_EVALUATION_INPUT_COMPONENTS};
	__property int GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS = {read=_GetGL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS};
	__property int GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS = {read=_GetGL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS};
	__property int GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS = {read=_GetGL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS};
	__property int GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS = {read=_GetGL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS};
	__property int GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS = {read=_GetGL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS};
	__property int GL_MAX_TESS_GEN_LEVEL = {read=_GetGL_MAX_TESS_GEN_LEVEL};
	__property int GL_MAX_TESS_PATCH_COMPONENTS = {read=_GetGL_MAX_TESS_PATCH_COMPONENTS};
	__property int GL_MAX_TEXTURE_BUFFER_SIZE = {read=_GetGL_MAX_TEXTURE_BUFFER_SIZE};
	__property int GL_MIN_FRAGMENT_INTERPOLATION_OFFSET = {read=_GetGL_MIN_FRAGMENT_INTERPOLATION_OFFSET};
	__property int GL_MIN_SAMPLE_SHADING_VALUE = {read=_GetGL_MIN_SAMPLE_SHADING_VALUE};
	__property int GL_MULTIPLY = {read=_GetGL_MULTIPLY};
	__property int GL_MULTISAMPLE_LINE_WIDTH_GRANULARITY = {read=_GetGL_MULTISAMPLE_LINE_WIDTH_GRANULARITY};
	__property int GL_MULTISAMPLE_LINE_WIDTH_RANGE = {read=_GetGL_MULTISAMPLE_LINE_WIDTH_RANGE};
	__property int GL_NO_RESET_NOTIFICATION = {read=_GetGL_NO_RESET_NOTIFICATION};
	__property int GL_OVERLAY = {read=_GetGL_OVERLAY};
	__property int GL_PATCHES = {read=_GetGL_PATCHES};
	__property int GL_PATCH_VERTICES = {read=_GetGL_PATCH_VERTICES};
	__property int GL_PRIMITIVES_GENERATED = {read=_GetGL_PRIMITIVES_GENERATED};
	__property int GL_PRIMITIVE_BOUNDING_BOX = {read=_GetGL_PRIMITIVE_BOUNDING_BOX};
	__property int GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED = {read=_GetGL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED};
	__property int GL_PROGRAM = {read=_GetGL_PROGRAM};
	__property int GL_PROGRAM_PIPELINE = {read=_GetGL_PROGRAM_PIPELINE};
	__property int GL_QUADS = {read=_GetGL_QUADS};
	__property int GL_QUERY = {read=_GetGL_QUERY};
	__property int GL_REFERENCED_BY_GEOMETRY_SHADER = {read=_GetGL_REFERENCED_BY_GEOMETRY_SHADER};
	__property int GL_REFERENCED_BY_TESS_CONTROL_SHADER = {read=_GetGL_REFERENCED_BY_TESS_CONTROL_SHADER};
	__property int GL_REFERENCED_BY_TESS_EVALUATION_SHADER = {read=_GetGL_REFERENCED_BY_TESS_EVALUATION_SHADER};
	__property int GL_RESET_NOTIFICATION_STRATEGY = {read=_GetGL_RESET_NOTIFICATION_STRATEGY};
	__property int GL_SAMPLER = {read=_GetGL_SAMPLER};
	__property int GL_SAMPLER_2D_MULTISAMPLE_ARRAY = {read=_GetGL_SAMPLER_2D_MULTISAMPLE_ARRAY};
	__property int GL_SAMPLER_BUFFER = {read=_GetGL_SAMPLER_BUFFER};
	__property int GL_SAMPLER_CUBE_MAP_ARRAY = {read=_GetGL_SAMPLER_CUBE_MAP_ARRAY};
	__property int GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW = {read=_GetGL_SAMPLER_CUBE_MAP_ARRAY_SHADOW};
	__property int GL_SAMPLE_SHADING = {read=_GetGL_SAMPLE_SHADING};
	__property int GL_SCREEN = {read=_GetGL_SCREEN};
	__property int GL_SHADER = {read=_GetGL_SHADER};
	__property int GL_SOFTLIGHT = {read=_GetGL_SOFTLIGHT};
	__property int GL_STACK_OVERFLOW = {read=_GetGL_STACK_OVERFLOW};
	__property int GL_STACK_UNDERFLOW = {read=_GetGL_STACK_UNDERFLOW};
	__property int GL_TESS_CONTROL_OUTPUT_VERTICES = {read=_GetGL_TESS_CONTROL_OUTPUT_VERTICES};
	__property int GL_TESS_CONTROL_SHADER = {read=_GetGL_TESS_CONTROL_SHADER};
	__property int GL_TESS_CONTROL_SHADER_BIT = {read=_GetGL_TESS_CONTROL_SHADER_BIT};
	__property int GL_TESS_EVALUATION_SHADER = {read=_GetGL_TESS_EVALUATION_SHADER};
	__property int GL_TESS_EVALUATION_SHADER_BIT = {read=_GetGL_TESS_EVALUATION_SHADER_BIT};
	__property int GL_TESS_GEN_MODE = {read=_GetGL_TESS_GEN_MODE};
	__property int GL_TESS_GEN_POINT_MODE = {read=_GetGL_TESS_GEN_POINT_MODE};
	__property int GL_TESS_GEN_SPACING = {read=_GetGL_TESS_GEN_SPACING};
	__property int GL_TESS_GEN_VERTEX_ORDER = {read=_GetGL_TESS_GEN_VERTEX_ORDER};
	__property int GL_TEXTURE_2D_MULTISAMPLE_ARRAY = {read=_GetGL_TEXTURE_2D_MULTISAMPLE_ARRAY};
	__property int GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY = {read=_GetGL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY};
	__property int GL_TEXTURE_BINDING_BUFFER = {read=_GetGL_TEXTURE_BINDING_BUFFER};
	__property int GL_TEXTURE_BINDING_CUBE_MAP_ARRAY = {read=_GetGL_TEXTURE_BINDING_CUBE_MAP_ARRAY};
	__property int GL_TEXTURE_BORDER_COLOR = {read=_GetGL_TEXTURE_BORDER_COLOR};
	__property int GL_TEXTURE_BUFFER = {read=_GetGL_TEXTURE_BUFFER};
	__property int GL_TEXTURE_BUFFER_BINDING = {read=_GetGL_TEXTURE_BUFFER_BINDING};
	__property int GL_TEXTURE_BUFFER_DATA_STORE_BINDING = {read=_GetGL_TEXTURE_BUFFER_DATA_STORE_BINDING};
	__property int GL_TEXTURE_BUFFER_OFFSET = {read=_GetGL_TEXTURE_BUFFER_OFFSET};
	__property int GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT = {read=_GetGL_TEXTURE_BUFFER_OFFSET_ALIGNMENT};
	__property int GL_TEXTURE_BUFFER_SIZE = {read=_GetGL_TEXTURE_BUFFER_SIZE};
	__property int GL_TEXTURE_CUBE_MAP_ARRAY = {read=_GetGL_TEXTURE_CUBE_MAP_ARRAY};
	__property int GL_TRIANGLES_ADJACENCY = {read=_GetGL_TRIANGLES_ADJACENCY};
	__property int GL_TRIANGLE_STRIP_ADJACENCY = {read=_GetGL_TRIANGLE_STRIP_ADJACENCY};
	__property int GL_UNDEFINED_VERTEX = {read=_GetGL_UNDEFINED_VERTEX};
	__property int GL_UNKNOWN_CONTEXT_RESET = {read=_GetGL_UNKNOWN_CONTEXT_RESET};
	__property int GL_UNSIGNED_INT_IMAGE_BUFFER = {read=_GetGL_UNSIGNED_INT_IMAGE_BUFFER};
	__property int GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY = {read=_GetGL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY};
	__property int GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = {read=_GetGL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY};
	__property int GL_UNSIGNED_INT_SAMPLER_BUFFER = {read=_GetGL_UNSIGNED_INT_SAMPLER_BUFFER};
	__property int GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY = {read=_GetGL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY};
	__property int GL_VERTEX_ARRAY = {read=_GetGL_VERTEX_ARRAY};
};

__interface  INTERFACE_UUID("{70302388-B672-4207-9E51-D665FF0EE4AC}") JGLES32  : public JGLES31 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLES32 : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES32Class,_di_JGLES32>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES32Class,_di_JGLES32> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLES32() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES32Class,_di_JGLES32>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLES32() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3C18DB55-0FBE-4D04-AF8E-E7AA9EF267CE}") JGLES32_DebugProcClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{88B37159-E2F0-48BD-AB4D-4747F75FD63A}") JGLES32_DebugProc  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMessage(int source, int type_, int id, int severity, Androidapi::Jni::Javatypes::_di_JString message) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLES32_DebugProc : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES32_DebugProcClass,_di_JGLES32_DebugProc>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES32_DebugProcClass,_di_JGLES32_DebugProc> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLES32_DebugProc() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLES32_DebugProcClass,_di_JGLES32_DebugProc>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLES32_DebugProc() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3125A88E-3ADF-4D9C-B145-B8AEB89658CD}") JGLExceptionClass  : public Androidapi::Jni::Javatypes::JRuntimeExceptionClass 
{
	HIDESBASE virtual _di_JGLException __cdecl init(int error) = 0 /* overload */;
	HIDESBASE virtual _di_JGLException __cdecl init(int error, Androidapi::Jni::Javatypes::_di_JString string_) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{1779AF1E-76A0-4401-AA06-879864915F19}") JGLException  : public Androidapi::Jni::Javatypes::JRuntimeException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLExceptionClass,_di_JGLException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLExceptionClass,_di_JGLException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLExceptionClass,_di_JGLException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{63463E9C-6F3C-4267-AB08-75F38C2165EC}") JGLSurfaceViewClass  : public Androidapi::Jni::Graphicscontentviewtext::JSurfaceViewClass 
{
	virtual int __cdecl _GetDEBUG_CHECK_GL_ERROR() = 0 ;
	virtual int __cdecl _GetDEBUG_LOG_GL_CALLS() = 0 ;
	virtual int __cdecl _GetRENDERMODE_CONTINUOUSLY() = 0 ;
	virtual int __cdecl _GetRENDERMODE_WHEN_DIRTY() = 0 ;
	HIDESBASE virtual _di_JGLSurfaceView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JGLSurfaceView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	__property int DEBUG_CHECK_GL_ERROR = {read=_GetDEBUG_CHECK_GL_ERROR};
	__property int DEBUG_LOG_GL_CALLS = {read=_GetDEBUG_LOG_GL_CALLS};
	__property int RENDERMODE_CONTINUOUSLY = {read=_GetRENDERMODE_CONTINUOUSLY};
	__property int RENDERMODE_WHEN_DIRTY = {read=_GetRENDERMODE_WHEN_DIRTY};
};

__interface  INTERFACE_UUID("{89634C91-C25A-47F1-9F63-1B86349BD676}") JGLSurfaceView  : public Androidapi::Jni::Graphicscontentviewtext::JSurfaceView 
{
	virtual int __cdecl getDebugFlags() = 0 ;
	virtual bool __cdecl getPreserveEGLContextOnPause() = 0 ;
	virtual int __cdecl getRenderMode() = 0 ;
	virtual void __cdecl onPause() = 0 ;
	virtual void __cdecl onResume() = 0 ;
	virtual void __cdecl queueEvent(Androidapi::Jni::Javatypes::_di_JRunnable r) = 0 ;
	virtual void __cdecl requestRender() = 0 ;
	virtual void __cdecl setDebugFlags(int debugFlags) = 0 ;
	virtual void __cdecl setEGLConfigChooser(_di_JGLSurfaceView_EGLConfigChooser configChooser) = 0 /* overload */;
	virtual void __cdecl setEGLConfigChooser(bool needDepth) = 0 /* overload */;
	virtual void __cdecl setEGLConfigChooser(int redSize, int greenSize, int blueSize, int alphaSize, int depthSize, int stencilSize) = 0 /* overload */;
	virtual void __cdecl setEGLContextClientVersion(int version) = 0 ;
	virtual void __cdecl setEGLContextFactory(_di_JGLSurfaceView_EGLContextFactory factory) = 0 ;
	virtual void __cdecl setEGLWindowSurfaceFactory(_di_JGLSurfaceView_EGLWindowSurfaceFactory factory) = 0 ;
	virtual void __cdecl setGLWrapper(_di_JGLSurfaceView_GLWrapper glWrapper) = 0 ;
	virtual void __cdecl setPreserveEGLContextOnPause(bool preserveOnPause) = 0 ;
	virtual void __cdecl setRenderMode(int renderMode) = 0 ;
	virtual void __cdecl setRenderer(_di_JGLSurfaceView_Renderer renderer) = 0 ;
	virtual void __cdecl surfaceChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder, int format, int w, int h) = 0 ;
	virtual void __cdecl surfaceCreated(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder) = 0 ;
	virtual void __cdecl surfaceDestroyed(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder) = 0 ;
	virtual void __cdecl surfaceRedrawNeeded(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder) = 0 ;
	virtual void __cdecl surfaceRedrawNeededAsync(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder, Androidapi::Jni::Javatypes::_di_JRunnable finishDrawing) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLSurfaceView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceViewClass,_di_JGLSurfaceView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceViewClass,_di_JGLSurfaceView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLSurfaceView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceViewClass,_di_JGLSurfaceView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLSurfaceView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A50E2BAD-797D-4F11-AF7A-2F9B1E9D975B}") JGLSurfaceView_EGLConfigChooserClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{34C89178-6D28-40CE-A5E4-20C433F5D871}") JGLSurfaceView_EGLConfigChooser  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JEGLConfig __cdecl chooseConfig(Androidapi::Jni::Javatypes::_di_JEGL10 egl, Androidapi::Jni::Javatypes::_di_JEGLDisplay display) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLSurfaceView_EGLConfigChooser : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_EGLConfigChooserClass,_di_JGLSurfaceView_EGLConfigChooser>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_EGLConfigChooserClass,_di_JGLSurfaceView_EGLConfigChooser> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLSurfaceView_EGLConfigChooser() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_EGLConfigChooserClass,_di_JGLSurfaceView_EGLConfigChooser>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLSurfaceView_EGLConfigChooser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A2A6C144-BFC6-42FB-A2F9-9ADB73B3FDA4}") JGLSurfaceView_EGLContextFactoryClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{84229F89-FEA5-4E44-B2E0-F0D728C4A307}") JGLSurfaceView_EGLContextFactory  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JEGLContext __cdecl createContext(Androidapi::Jni::Javatypes::_di_JEGL10 egl, Androidapi::Jni::Javatypes::_di_JEGLDisplay display, Androidapi::Jni::Javatypes::_di_JEGLConfig eglConfig) = 0 ;
	virtual void __cdecl destroyContext(Androidapi::Jni::Javatypes::_di_JEGL10 egl, Androidapi::Jni::Javatypes::_di_JEGLDisplay display, Androidapi::Jni::Javatypes::_di_JEGLContext context) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLSurfaceView_EGLContextFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_EGLContextFactoryClass,_di_JGLSurfaceView_EGLContextFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_EGLContextFactoryClass,_di_JGLSurfaceView_EGLContextFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLSurfaceView_EGLContextFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_EGLContextFactoryClass,_di_JGLSurfaceView_EGLContextFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLSurfaceView_EGLContextFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C942EC43-1E26-4355-89C2-2AF11A106E67}") JGLSurfaceView_EGLWindowSurfaceFactoryClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{7DD4EB8B-7244-477A-B1CA-92ACB9679FBE}") JGLSurfaceView_EGLWindowSurfaceFactory  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JEGLSurface __cdecl createWindowSurface(Androidapi::Jni::Javatypes::_di_JEGL10 egl, Androidapi::Jni::Javatypes::_di_JEGLDisplay display, Androidapi::Jni::Javatypes::_di_JEGLConfig config, Androidapi::Jni::Javatypes::_di_JObject nativeWindow) = 0 ;
	virtual void __cdecl destroySurface(Androidapi::Jni::Javatypes::_di_JEGL10 egl, Androidapi::Jni::Javatypes::_di_JEGLDisplay display, Androidapi::Jni::Javatypes::_di_JEGLSurface surface) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLSurfaceView_EGLWindowSurfaceFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_EGLWindowSurfaceFactoryClass,_di_JGLSurfaceView_EGLWindowSurfaceFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_EGLWindowSurfaceFactoryClass,_di_JGLSurfaceView_EGLWindowSurfaceFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLSurfaceView_EGLWindowSurfaceFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_EGLWindowSurfaceFactoryClass,_di_JGLSurfaceView_EGLWindowSurfaceFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLSurfaceView_EGLWindowSurfaceFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C178D1DB-2917-48D8-9F9E-EF01C799E8EB}") JGLSurfaceView_GLWrapperClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{14B3F93A-06F9-44C0-AEA1-8B49C917B0A7}") JGLSurfaceView_GLWrapper  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JGL __cdecl wrap(Androidapi::Jni::Javatypes::_di_JGL gl) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLSurfaceView_GLWrapper : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_GLWrapperClass,_di_JGLSurfaceView_GLWrapper>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_GLWrapperClass,_di_JGLSurfaceView_GLWrapper> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLSurfaceView_GLWrapper() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_GLWrapperClass,_di_JGLSurfaceView_GLWrapper>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLSurfaceView_GLWrapper() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{217726BB-8C84-479F-B023-74178C68EC53}") JGLSurfaceView_RendererClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{B2554C00-E9D5-49B0-9DFC-ED774863B255}") JGLSurfaceView_Renderer  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onDrawFrame(Androidapi::Jni::Javatypes::_di_JGL10 gl) = 0 ;
	virtual void __cdecl onSurfaceChanged(Androidapi::Jni::Javatypes::_di_JGL10 gl, int width, int height) = 0 ;
	virtual void __cdecl onSurfaceCreated(Androidapi::Jni::Javatypes::_di_JGL10 gl, Androidapi::Jni::Javatypes::_di_JEGLConfig config) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLSurfaceView_Renderer : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_RendererClass,_di_JGLSurfaceView_Renderer>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_RendererClass,_di_JGLSurfaceView_Renderer> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLSurfaceView_Renderer() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLSurfaceView_RendererClass,_di_JGLSurfaceView_Renderer>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLSurfaceView_Renderer() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{38DF26FD-6854-4A0B-A390-1247A628F094}") JGLUClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JGLU __cdecl init() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl gluErrorString(int error) = 0 ;
	virtual void __cdecl gluLookAt(Androidapi::Jni::Javatypes::_di_JGL10 gl, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) = 0 ;
	virtual void __cdecl gluOrtho2D(Androidapi::Jni::Javatypes::_di_JGL10 gl, float left, float right, float bottom, float top) = 0 ;
	virtual void __cdecl gluPerspective(Androidapi::Jni::Javatypes::_di_JGL10 gl, float fovy, float aspect, float zNear, float zFar) = 0 ;
	virtual int __cdecl gluProject(float objX, float objY, float objZ, Androidapi::Jnibridge::TJavaArray__1<float>* model, int modelOffset, Androidapi::Jnibridge::TJavaArray__1<float>* project, int projectOffset, Androidapi::Jnibridge::TJavaArray__1<int>* view, int viewOffset, Androidapi::Jnibridge::TJavaArray__1<float>* win, int winOffset) = 0 ;
	virtual int __cdecl gluUnProject(float winX, float winY, float winZ, Androidapi::Jnibridge::TJavaArray__1<float>* model, int modelOffset, Androidapi::Jnibridge::TJavaArray__1<float>* project, int projectOffset, Androidapi::Jnibridge::TJavaArray__1<int>* view, int viewOffset, Androidapi::Jnibridge::TJavaArray__1<float>* obj, int objOffset) = 0 ;
};

__interface  INTERFACE_UUID("{0E20BDE3-3902-49F7-9AD1-D665C1B13FBA}") JGLU  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLU : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLUClass,_di_JGLU>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLUClass,_di_JGLU> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLU() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLUClass,_di_JGLU>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLU() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{81E5073C-57E6-43E4-A9D3-5408E7BD4BED}") JGLUtilsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getEGLErrorString(int error) = 0 ;
	virtual int __cdecl getInternalFormat(Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bitmap) = 0 ;
	virtual int __cdecl getType(Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bitmap) = 0 ;
	virtual void __cdecl texImage2D(int target, int level, int internalformat, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bitmap, int border) = 0 /* overload */;
	virtual void __cdecl texImage2D(int target, int level, int internalformat, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bitmap, int type_, int border) = 0 /* overload */;
	virtual void __cdecl texImage2D(int target, int level, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bitmap, int border) = 0 /* overload */;
	virtual void __cdecl texSubImage2D(int target, int level, int xoffset, int yoffset, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bitmap) = 0 /* overload */;
	virtual void __cdecl texSubImage2D(int target, int level, int xoffset, int yoffset, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bitmap, int format, int type_) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{74547182-0A71-406F-916A-12CA7D3B380F}") JGLUtils  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGLUtils : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLUtilsClass,_di_JGLUtils>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLUtilsClass,_di_JGLUtils> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGLUtils() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGLUtilsClass,_di_JGLUtils>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGLUtils() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4EB67487-D94B-4FC1-95FA-26589B23C44C}") Jopengl_MatrixClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_Jopengl_Matrix __cdecl init() = 0 ;
	virtual void __cdecl frustumM(Androidapi::Jnibridge::TJavaArray__1<float>* m, int offset, float left, float right, float bottom, float top, float near, float far) = 0 ;
	virtual bool __cdecl invertM(Androidapi::Jnibridge::TJavaArray__1<float>* mInv, int mInvOffset, Androidapi::Jnibridge::TJavaArray__1<float>* m, int mOffset) = 0 ;
	virtual float __cdecl length(float x, float y, float z) = 0 ;
	virtual void __cdecl multiplyMM(Androidapi::Jnibridge::TJavaArray__1<float>* result, int resultOffset, Androidapi::Jnibridge::TJavaArray__1<float>* lhs, int lhsOffset, Androidapi::Jnibridge::TJavaArray__1<float>* rhs, int rhsOffset) = 0 ;
	virtual void __cdecl multiplyMV(Androidapi::Jnibridge::TJavaArray__1<float>* resultVec, int resultVecOffset, Androidapi::Jnibridge::TJavaArray__1<float>* lhsMat, int lhsMatOffset, Androidapi::Jnibridge::TJavaArray__1<float>* rhsVec, int rhsVecOffset) = 0 ;
	virtual void __cdecl orthoM(Androidapi::Jnibridge::TJavaArray__1<float>* m, int mOffset, float left, float right, float bottom, float top, float near, float far) = 0 ;
	virtual void __cdecl perspectiveM(Androidapi::Jnibridge::TJavaArray__1<float>* m, int offset, float fovy, float aspect, float zNear, float zFar) = 0 ;
	virtual void __cdecl rotateM(Androidapi::Jnibridge::TJavaArray__1<float>* rm, int rmOffset, Androidapi::Jnibridge::TJavaArray__1<float>* m, int mOffset, float a, float x, float y, float z) = 0 /* overload */;
	virtual void __cdecl rotateM(Androidapi::Jnibridge::TJavaArray__1<float>* m, int mOffset, float a, float x, float y, float z) = 0 /* overload */;
	virtual void __cdecl scaleM(Androidapi::Jnibridge::TJavaArray__1<float>* sm, int smOffset, Androidapi::Jnibridge::TJavaArray__1<float>* m, int mOffset, float x, float y, float z) = 0 /* overload */;
	virtual void __cdecl scaleM(Androidapi::Jnibridge::TJavaArray__1<float>* m, int mOffset, float x, float y, float z) = 0 /* overload */;
	virtual void __cdecl setIdentityM(Androidapi::Jnibridge::TJavaArray__1<float>* sm, int smOffset) = 0 ;
	virtual void __cdecl setLookAtM(Androidapi::Jnibridge::TJavaArray__1<float>* rm, int rmOffset, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ) = 0 ;
	virtual void __cdecl setRotateEulerM(Androidapi::Jnibridge::TJavaArray__1<float>* rm, int rmOffset, float x, float y, float z) = 0 ;
	virtual void __cdecl setRotateM(Androidapi::Jnibridge::TJavaArray__1<float>* rm, int rmOffset, float a, float x, float y, float z) = 0 ;
	virtual void __cdecl translateM(Androidapi::Jnibridge::TJavaArray__1<float>* tm, int tmOffset, Androidapi::Jnibridge::TJavaArray__1<float>* m, int mOffset, float x, float y, float z) = 0 /* overload */;
	virtual void __cdecl translateM(Androidapi::Jnibridge::TJavaArray__1<float>* m, int mOffset, float x, float y, float z) = 0 /* overload */;
	virtual void __cdecl transposeM(Androidapi::Jnibridge::TJavaArray__1<float>* mTrans, int mTransOffset, Androidapi::Jnibridge::TJavaArray__1<float>* m, int mOffset) = 0 ;
};

__interface  INTERFACE_UUID("{CFB1A8B7-3B83-4397-8FFA-5E7E733D6107}") Jopengl_Matrix  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJopengl_Matrix : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_MatrixClass,_di_Jopengl_Matrix>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_MatrixClass,_di_Jopengl_Matrix> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJopengl_Matrix() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jopengl_MatrixClass,_di_Jopengl_Matrix>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJopengl_Matrix() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6B76D3D5-276B-4DCE-8BE7-E8E4569C7FC2}") JVisibilityClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JVisibility __cdecl init() = 0 ;
	virtual void __cdecl computeBoundingSphere(Androidapi::Jnibridge::TJavaArray__1<float>* positions, int positionsOffset, int positionsCount, Androidapi::Jnibridge::TJavaArray__1<float>* sphere, int sphereOffset) = 0 ;
	virtual int __cdecl frustumCullSpheres(Androidapi::Jnibridge::TJavaArray__1<float>* mvp, int mvpOffset, Androidapi::Jnibridge::TJavaArray__1<float>* spheres, int spheresOffset, int spheresCount, Androidapi::Jnibridge::TJavaArray__1<int>* results, int resultsOffset, int resultsCapacity) = 0 ;
	virtual int __cdecl visibilityTest(Androidapi::Jnibridge::TJavaArray__1<float>* ws, int wsOffset, Androidapi::Jnibridge::TJavaArray__1<float>* positions, int positionsOffset, Androidapi::Jnibridge::TJavaArray__1<System::WideChar>* indices, int indicesOffset, int indexCount) = 0 ;
};

__interface  INTERFACE_UUID("{C7FA08CF-B60D-4208-BE44-C1A46B01B75D}") JVisibility  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVisibility : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisibilityClass,_di_JVisibility>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisibilityClass,_di_JVisibility> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVisibility() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisibilityClass,_di_JVisibility>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVisibility() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Opengl */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_OPENGL)
using namespace Androidapi::Jni::Opengl;
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
#endif	// Androidapi_Jni_OpenglHPP
