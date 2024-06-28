// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Hardware.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_HardwareHPP
#define Androidapi_Jni_HardwareHPP

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
namespace Hardware
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JCameraClass;
typedef System::DelphiInterface<JCameraClass> _di_JCameraClass;
__interface DELPHIINTERFACE JCamera;
typedef System::DelphiInterface<JCamera> _di_JCamera;
class DELPHICLASS TJCamera;
__interface DELPHIINTERFACE JCamera_AutoFocusCallbackClass;
typedef System::DelphiInterface<JCamera_AutoFocusCallbackClass> _di_JCamera_AutoFocusCallbackClass;
__interface DELPHIINTERFACE JCamera_AutoFocusCallback;
typedef System::DelphiInterface<JCamera_AutoFocusCallback> _di_JCamera_AutoFocusCallback;
class DELPHICLASS TJCamera_AutoFocusCallback;
__interface DELPHIINTERFACE JCamera_AutoFocusMoveCallbackClass;
typedef System::DelphiInterface<JCamera_AutoFocusMoveCallbackClass> _di_JCamera_AutoFocusMoveCallbackClass;
__interface DELPHIINTERFACE JCamera_AutoFocusMoveCallback;
typedef System::DelphiInterface<JCamera_AutoFocusMoveCallback> _di_JCamera_AutoFocusMoveCallback;
class DELPHICLASS TJCamera_AutoFocusMoveCallback;
__interface DELPHIINTERFACE JCamera_CameraInfoClass;
typedef System::DelphiInterface<JCamera_CameraInfoClass> _di_JCamera_CameraInfoClass;
__interface DELPHIINTERFACE JCamera_CameraInfo;
typedef System::DelphiInterface<JCamera_CameraInfo> _di_JCamera_CameraInfo;
class DELPHICLASS TJCamera_CameraInfo;
__interface DELPHIINTERFACE JCamera_ErrorCallbackClass;
typedef System::DelphiInterface<JCamera_ErrorCallbackClass> _di_JCamera_ErrorCallbackClass;
__interface DELPHIINTERFACE JCamera_ErrorCallback;
typedef System::DelphiInterface<JCamera_ErrorCallback> _di_JCamera_ErrorCallback;
class DELPHICLASS TJCamera_ErrorCallback;
__interface DELPHIINTERFACE JCamera_FaceClass;
typedef System::DelphiInterface<JCamera_FaceClass> _di_JCamera_FaceClass;
__interface DELPHIINTERFACE JCamera_Face;
typedef System::DelphiInterface<JCamera_Face> _di_JCamera_Face;
class DELPHICLASS TJCamera_Face;
__interface DELPHIINTERFACE JCamera_FaceDetectionListenerClass;
typedef System::DelphiInterface<JCamera_FaceDetectionListenerClass> _di_JCamera_FaceDetectionListenerClass;
__interface DELPHIINTERFACE JCamera_FaceDetectionListener;
typedef System::DelphiInterface<JCamera_FaceDetectionListener> _di_JCamera_FaceDetectionListener;
class DELPHICLASS TJCamera_FaceDetectionListener;
__interface DELPHIINTERFACE JCamera_OnZoomChangeListenerClass;
typedef System::DelphiInterface<JCamera_OnZoomChangeListenerClass> _di_JCamera_OnZoomChangeListenerClass;
__interface DELPHIINTERFACE JCamera_OnZoomChangeListener;
typedef System::DelphiInterface<JCamera_OnZoomChangeListener> _di_JCamera_OnZoomChangeListener;
class DELPHICLASS TJCamera_OnZoomChangeListener;
__interface DELPHIINTERFACE JCamera_ParametersClass;
typedef System::DelphiInterface<JCamera_ParametersClass> _di_JCamera_ParametersClass;
__interface DELPHIINTERFACE JCamera_Parameters;
typedef System::DelphiInterface<JCamera_Parameters> _di_JCamera_Parameters;
class DELPHICLASS TJCamera_Parameters;
__interface DELPHIINTERFACE JCamera_PictureCallbackClass;
typedef System::DelphiInterface<JCamera_PictureCallbackClass> _di_JCamera_PictureCallbackClass;
__interface DELPHIINTERFACE JCamera_PictureCallback;
typedef System::DelphiInterface<JCamera_PictureCallback> _di_JCamera_PictureCallback;
class DELPHICLASS TJCamera_PictureCallback;
__interface DELPHIINTERFACE JCamera_PreviewCallbackClass;
typedef System::DelphiInterface<JCamera_PreviewCallbackClass> _di_JCamera_PreviewCallbackClass;
__interface DELPHIINTERFACE JCamera_PreviewCallback;
typedef System::DelphiInterface<JCamera_PreviewCallback> _di_JCamera_PreviewCallback;
class DELPHICLASS TJCamera_PreviewCallback;
__interface DELPHIINTERFACE JCamera_ShutterCallbackClass;
typedef System::DelphiInterface<JCamera_ShutterCallbackClass> _di_JCamera_ShutterCallbackClass;
__interface DELPHIINTERFACE JCamera_ShutterCallback;
typedef System::DelphiInterface<JCamera_ShutterCallback> _di_JCamera_ShutterCallback;
class DELPHICLASS TJCamera_ShutterCallback;
__interface DELPHIINTERFACE JCamera_SizeClass;
typedef System::DelphiInterface<JCamera_SizeClass> _di_JCamera_SizeClass;
__interface DELPHIINTERFACE JCamera_Size;
typedef System::DelphiInterface<JCamera_Size> _di_JCamera_Size;
class DELPHICLASS TJCamera_Size;
__interface DELPHIINTERFACE JDisplayManagerClass;
typedef System::DelphiInterface<JDisplayManagerClass> _di_JDisplayManagerClass;
__interface DELPHIINTERFACE JDisplayManager;
typedef System::DelphiInterface<JDisplayManager> _di_JDisplayManager;
class DELPHICLASS TJDisplayManager;
__interface DELPHIINTERFACE JDisplayManager_DisplayListenerClass;
typedef System::DelphiInterface<JDisplayManager_DisplayListenerClass> _di_JDisplayManager_DisplayListenerClass;
__interface DELPHIINTERFACE JDisplayManager_DisplayListener;
typedef System::DelphiInterface<JDisplayManager_DisplayListener> _di_JDisplayManager_DisplayListener;
class DELPHICLASS TJDisplayManager_DisplayListener;
__interface DELPHIINTERFACE JVirtualDisplayClass;
typedef System::DelphiInterface<JVirtualDisplayClass> _di_JVirtualDisplayClass;
__interface DELPHIINTERFACE JVirtualDisplay;
typedef System::DelphiInterface<JVirtualDisplay> _di_JVirtualDisplay;
class DELPHICLASS TJVirtualDisplay;
__interface DELPHIINTERFACE JVirtualDisplay_CallbackClass;
typedef System::DelphiInterface<JVirtualDisplay_CallbackClass> _di_JVirtualDisplay_CallbackClass;
__interface DELPHIINTERFACE JVirtualDisplay_Callback;
typedef System::DelphiInterface<JVirtualDisplay_Callback> _di_JVirtualDisplay_Callback;
class DELPHICLASS TJVirtualDisplay_Callback;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{EC7FA230-96BA-4ED6-9328-CAC5F459C235}") JCameraClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_NEW_PICTURE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_NEW_VIDEO() = 0 ;
	virtual int __cdecl _GetCAMERA_ERROR_EVICTED() = 0 ;
	virtual int __cdecl _GetCAMERA_ERROR_SERVER_DIED() = 0 ;
	virtual int __cdecl _GetCAMERA_ERROR_UNKNOWN() = 0 ;
	virtual void __cdecl getCameraInfo(int cameraId, _di_JCamera_CameraInfo cameraInfo) = 0 ;
	virtual int __cdecl getNumberOfCameras() = 0 ;
	virtual _di_JCamera __cdecl open(int cameraId) = 0 /* overload */;
	virtual _di_JCamera __cdecl open() = 0 /* overload */;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_NEW_PICTURE = {read=_GetACTION_NEW_PICTURE};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_NEW_VIDEO = {read=_GetACTION_NEW_VIDEO};
	__property int CAMERA_ERROR_EVICTED = {read=_GetCAMERA_ERROR_EVICTED};
	__property int CAMERA_ERROR_SERVER_DIED = {read=_GetCAMERA_ERROR_SERVER_DIED};
	__property int CAMERA_ERROR_UNKNOWN = {read=_GetCAMERA_ERROR_UNKNOWN};
};

__interface  INTERFACE_UUID("{40A86A47-3393-4E33-8884-C33107CD903B}") JCamera  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addCallbackBuffer(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* callbackBuffer) = 0 ;
	virtual void __cdecl autoFocus(_di_JCamera_AutoFocusCallback cb) = 0 ;
	virtual void __cdecl cancelAutoFocus() = 0 ;
	virtual bool __cdecl enableShutterSound(bool enabled) = 0 ;
	virtual _di_JCamera_Parameters __cdecl getParameters() = 0 ;
	virtual void __cdecl lock() = 0 ;
	virtual void __cdecl reconnect() = 0 ;
	virtual void __cdecl release() = 0 ;
	virtual void __cdecl setAutoFocusMoveCallback(_di_JCamera_AutoFocusMoveCallback cb) = 0 ;
	virtual void __cdecl setDisplayOrientation(int degrees) = 0 ;
	virtual void __cdecl setErrorCallback(_di_JCamera_ErrorCallback cb) = 0 ;
	virtual void __cdecl setFaceDetectionListener(_di_JCamera_FaceDetectionListener listener) = 0 ;
	virtual void __cdecl setOneShotPreviewCallback(_di_JCamera_PreviewCallback cb) = 0 ;
	virtual void __cdecl setParameters(_di_JCamera_Parameters params) = 0 ;
	virtual void __cdecl setPreviewCallback(_di_JCamera_PreviewCallback cb) = 0 ;
	virtual void __cdecl setPreviewCallbackWithBuffer(_di_JCamera_PreviewCallback cb) = 0 ;
	virtual void __cdecl setPreviewDisplay(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder) = 0 ;
	virtual void __cdecl setPreviewTexture(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceTexture surfaceTexture) = 0 ;
	virtual void __cdecl setZoomChangeListener(_di_JCamera_OnZoomChangeListener listener) = 0 ;
	virtual void __cdecl startFaceDetection() = 0 ;
	virtual void __cdecl startPreview() = 0 ;
	virtual void __cdecl startSmoothZoom(int value) = 0 ;
	virtual void __cdecl stopFaceDetection() = 0 ;
	virtual void __cdecl stopPreview() = 0 ;
	virtual void __cdecl stopSmoothZoom() = 0 ;
	virtual void __cdecl takePicture(_di_JCamera_ShutterCallback shutter, _di_JCamera_PictureCallback raw, _di_JCamera_PictureCallback jpeg) = 0 /* overload */;
	virtual void __cdecl takePicture(_di_JCamera_ShutterCallback shutter, _di_JCamera_PictureCallback raw, _di_JCamera_PictureCallback postview, _di_JCamera_PictureCallback jpeg) = 0 /* overload */;
	virtual void __cdecl unlock() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraClass,_di_JCamera>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraClass,_di_JCamera> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCameraClass,_di_JCamera>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{624541C8-C3C3-4A09-8367-4C3237E658D0}") JCamera_AutoFocusCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{2E9C9152-C3B7-43EE-98BD-04189FBE43A7}") JCamera_AutoFocusCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onAutoFocus(bool success, _di_JCamera camera) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_AutoFocusCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_AutoFocusCallbackClass,_di_JCamera_AutoFocusCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_AutoFocusCallbackClass,_di_JCamera_AutoFocusCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_AutoFocusCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_AutoFocusCallbackClass,_di_JCamera_AutoFocusCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_AutoFocusCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{901C04AC-438E-4233-A469-A3A53EA3A5E3}") JCamera_AutoFocusMoveCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{3F071E3E-4BE6-4DFF-A5C9-458E91DD4204}") JCamera_AutoFocusMoveCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onAutoFocusMoving(bool start, _di_JCamera camera) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_AutoFocusMoveCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_AutoFocusMoveCallbackClass,_di_JCamera_AutoFocusMoveCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_AutoFocusMoveCallbackClass,_di_JCamera_AutoFocusMoveCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_AutoFocusMoveCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_AutoFocusMoveCallbackClass,_di_JCamera_AutoFocusMoveCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_AutoFocusMoveCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4D9A2405-77B3-4828-B7F5-AF756B98D6B5}") JCamera_CameraInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetCAMERA_FACING_BACK() = 0 ;
	virtual int __cdecl _GetCAMERA_FACING_FRONT() = 0 ;
	HIDESBASE virtual _di_JCamera_CameraInfo __cdecl init() = 0 ;
	__property int CAMERA_FACING_BACK = {read=_GetCAMERA_FACING_BACK};
	__property int CAMERA_FACING_FRONT = {read=_GetCAMERA_FACING_FRONT};
};

__interface  INTERFACE_UUID("{D7A9C455-C629-40F6-BCAE-E20195C6069B}") JCamera_CameraInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl _GetcanDisableShutterSound() = 0 ;
	virtual void __cdecl _SetcanDisableShutterSound(bool Value) = 0 ;
	virtual int __cdecl _Getfacing() = 0 ;
	virtual void __cdecl _Setfacing(int Value) = 0 ;
	virtual int __cdecl _Getorientation() = 0 ;
	virtual void __cdecl _Setorientation(int Value) = 0 ;
	__property bool canDisableShutterSound = {read=_GetcanDisableShutterSound, write=_SetcanDisableShutterSound};
	__property int facing = {read=_Getfacing, write=_Setfacing};
	__property int orientation = {read=_Getorientation, write=_Setorientation};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_CameraInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_CameraInfoClass,_di_JCamera_CameraInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_CameraInfoClass,_di_JCamera_CameraInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_CameraInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_CameraInfoClass,_di_JCamera_CameraInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_CameraInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5AAEF0D6-153A-481B-8A54-527D810352D2}") JCamera_ErrorCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{45CC94C4-4AEC-43B6-861D-A7AC2392CB2D}") JCamera_ErrorCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onError(int error, _di_JCamera camera) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_ErrorCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_ErrorCallbackClass,_di_JCamera_ErrorCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_ErrorCallbackClass,_di_JCamera_ErrorCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_ErrorCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_ErrorCallbackClass,_di_JCamera_ErrorCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_ErrorCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3926BFB1-9866-403B-A24E-7FCB9251F1A5}") JCamera_FaceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCamera_Face __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{4FBCBB16-3A6B-493C-952F-55AC60C75DE9}") JCamera_Face  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _Getid() = 0 ;
	virtual void __cdecl _Setid(int Value) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPoint __cdecl _GetleftEye() = 0 ;
	virtual void __cdecl _SetleftEye(Androidapi::Jni::Graphicscontentviewtext::_di_JPoint Value) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPoint __cdecl _Getmouth() = 0 ;
	virtual void __cdecl _Setmouth(Androidapi::Jni::Graphicscontentviewtext::_di_JPoint Value) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JRect __cdecl _Getrect() = 0 ;
	virtual void __cdecl _Setrect(Androidapi::Jni::Graphicscontentviewtext::_di_JRect Value) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPoint __cdecl _GetrightEye() = 0 ;
	virtual void __cdecl _SetrightEye(Androidapi::Jni::Graphicscontentviewtext::_di_JPoint Value) = 0 ;
	virtual int __cdecl _Getscore() = 0 ;
	virtual void __cdecl _Setscore(int Value) = 0 ;
	__property int id = {read=_Getid, write=_Setid};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JPoint leftEye = {read=_GetleftEye, write=_SetleftEye};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JPoint mouth = {read=_Getmouth, write=_Setmouth};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JRect rect = {read=_Getrect, write=_Setrect};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JPoint rightEye = {read=_GetrightEye, write=_SetrightEye};
	__property int score = {read=_Getscore, write=_Setscore};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_Face : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_FaceClass,_di_JCamera_Face>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_FaceClass,_di_JCamera_Face> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_Face() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_FaceClass,_di_JCamera_Face>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_Face() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2C26C033-6093-440C-8B6F-E0E8632CE495}") JCamera_FaceDetectionListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{F5A3CD35-3B25-41A8-9B69-6EC00C39A0BF}") JCamera_FaceDetectionListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onFaceDetection(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JCamera_Face>* faces, _di_JCamera camera) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_FaceDetectionListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_FaceDetectionListenerClass,_di_JCamera_FaceDetectionListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_FaceDetectionListenerClass,_di_JCamera_FaceDetectionListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_FaceDetectionListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_FaceDetectionListenerClass,_di_JCamera_FaceDetectionListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_FaceDetectionListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7D8BC2A6-9164-48A0-B14F-D65D3642D2BA}") JCamera_OnZoomChangeListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{8083D248-A911-4752-8C17-5F3C9F26CB33}") JCamera_OnZoomChangeListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onZoomChange(int zoomValue, bool stopped, _di_JCamera camera) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_OnZoomChangeListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_OnZoomChangeListenerClass,_di_JCamera_OnZoomChangeListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_OnZoomChangeListenerClass,_di_JCamera_OnZoomChangeListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_OnZoomChangeListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_OnZoomChangeListenerClass,_di_JCamera_OnZoomChangeListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_OnZoomChangeListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{519157BE-F3CB-41ED-90A0-239A67F07E7C}") JCamera_ParametersClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetANTIBANDING_50HZ() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetANTIBANDING_60HZ() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetANTIBANDING_AUTO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetANTIBANDING_OFF() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEFFECT_AQUA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEFFECT_BLACKBOARD() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEFFECT_MONO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEFFECT_NEGATIVE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEFFECT_NONE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEFFECT_POSTERIZE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEFFECT_SEPIA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEFFECT_SOLARIZE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEFFECT_WHITEBOARD() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFLASH_MODE_AUTO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFLASH_MODE_OFF() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFLASH_MODE_ON() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFLASH_MODE_RED_EYE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFLASH_MODE_TORCH() = 0 ;
	virtual int __cdecl _GetFOCUS_DISTANCE_FAR_INDEX() = 0 ;
	virtual int __cdecl _GetFOCUS_DISTANCE_NEAR_INDEX() = 0 ;
	virtual int __cdecl _GetFOCUS_DISTANCE_OPTIMAL_INDEX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFOCUS_MODE_AUTO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFOCUS_MODE_CONTINUOUS_PICTURE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFOCUS_MODE_CONTINUOUS_VIDEO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFOCUS_MODE_EDOF() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFOCUS_MODE_FIXED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFOCUS_MODE_INFINITY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFOCUS_MODE_MACRO() = 0 ;
	virtual int __cdecl _GetPREVIEW_FPS_MAX_INDEX() = 0 ;
	virtual int __cdecl _GetPREVIEW_FPS_MIN_INDEX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_ACTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_AUTO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_BARCODE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_BEACH() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_CANDLELIGHT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_FIREWORKS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_HDR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_LANDSCAPE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_NIGHT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_NIGHT_PORTRAIT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_PARTY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_PORTRAIT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_SNOW() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_SPORTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_STEADYPHOTO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_SUNSET() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSCENE_MODE_THEATRE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWHITE_BALANCE_AUTO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWHITE_BALANCE_CLOUDY_DAYLIGHT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWHITE_BALANCE_DAYLIGHT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWHITE_BALANCE_FLUORESCENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWHITE_BALANCE_INCANDESCENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWHITE_BALANCE_SHADE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWHITE_BALANCE_TWILIGHT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetWHITE_BALANCE_WARM_FLUORESCENT() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ANTIBANDING_50HZ = {read=_GetANTIBANDING_50HZ};
	__property Androidapi::Jni::Javatypes::_di_JString ANTIBANDING_60HZ = {read=_GetANTIBANDING_60HZ};
	__property Androidapi::Jni::Javatypes::_di_JString ANTIBANDING_AUTO = {read=_GetANTIBANDING_AUTO};
	__property Androidapi::Jni::Javatypes::_di_JString ANTIBANDING_OFF = {read=_GetANTIBANDING_OFF};
	__property Androidapi::Jni::Javatypes::_di_JString EFFECT_AQUA = {read=_GetEFFECT_AQUA};
	__property Androidapi::Jni::Javatypes::_di_JString EFFECT_BLACKBOARD = {read=_GetEFFECT_BLACKBOARD};
	__property Androidapi::Jni::Javatypes::_di_JString EFFECT_MONO = {read=_GetEFFECT_MONO};
	__property Androidapi::Jni::Javatypes::_di_JString EFFECT_NEGATIVE = {read=_GetEFFECT_NEGATIVE};
	__property Androidapi::Jni::Javatypes::_di_JString EFFECT_NONE = {read=_GetEFFECT_NONE};
	__property Androidapi::Jni::Javatypes::_di_JString EFFECT_POSTERIZE = {read=_GetEFFECT_POSTERIZE};
	__property Androidapi::Jni::Javatypes::_di_JString EFFECT_SEPIA = {read=_GetEFFECT_SEPIA};
	__property Androidapi::Jni::Javatypes::_di_JString EFFECT_SOLARIZE = {read=_GetEFFECT_SOLARIZE};
	__property Androidapi::Jni::Javatypes::_di_JString EFFECT_WHITEBOARD = {read=_GetEFFECT_WHITEBOARD};
	__property Androidapi::Jni::Javatypes::_di_JString FLASH_MODE_AUTO = {read=_GetFLASH_MODE_AUTO};
	__property Androidapi::Jni::Javatypes::_di_JString FLASH_MODE_OFF = {read=_GetFLASH_MODE_OFF};
	__property Androidapi::Jni::Javatypes::_di_JString FLASH_MODE_ON = {read=_GetFLASH_MODE_ON};
	__property Androidapi::Jni::Javatypes::_di_JString FLASH_MODE_RED_EYE = {read=_GetFLASH_MODE_RED_EYE};
	__property Androidapi::Jni::Javatypes::_di_JString FLASH_MODE_TORCH = {read=_GetFLASH_MODE_TORCH};
	__property int FOCUS_DISTANCE_FAR_INDEX = {read=_GetFOCUS_DISTANCE_FAR_INDEX};
	__property int FOCUS_DISTANCE_NEAR_INDEX = {read=_GetFOCUS_DISTANCE_NEAR_INDEX};
	__property int FOCUS_DISTANCE_OPTIMAL_INDEX = {read=_GetFOCUS_DISTANCE_OPTIMAL_INDEX};
	__property Androidapi::Jni::Javatypes::_di_JString FOCUS_MODE_AUTO = {read=_GetFOCUS_MODE_AUTO};
	__property Androidapi::Jni::Javatypes::_di_JString FOCUS_MODE_CONTINUOUS_PICTURE = {read=_GetFOCUS_MODE_CONTINUOUS_PICTURE};
	__property Androidapi::Jni::Javatypes::_di_JString FOCUS_MODE_CONTINUOUS_VIDEO = {read=_GetFOCUS_MODE_CONTINUOUS_VIDEO};
	__property Androidapi::Jni::Javatypes::_di_JString FOCUS_MODE_EDOF = {read=_GetFOCUS_MODE_EDOF};
	__property Androidapi::Jni::Javatypes::_di_JString FOCUS_MODE_FIXED = {read=_GetFOCUS_MODE_FIXED};
	__property Androidapi::Jni::Javatypes::_di_JString FOCUS_MODE_INFINITY = {read=_GetFOCUS_MODE_INFINITY};
	__property Androidapi::Jni::Javatypes::_di_JString FOCUS_MODE_MACRO = {read=_GetFOCUS_MODE_MACRO};
	__property int PREVIEW_FPS_MAX_INDEX = {read=_GetPREVIEW_FPS_MAX_INDEX};
	__property int PREVIEW_FPS_MIN_INDEX = {read=_GetPREVIEW_FPS_MIN_INDEX};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_ACTION = {read=_GetSCENE_MODE_ACTION};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_AUTO = {read=_GetSCENE_MODE_AUTO};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_BARCODE = {read=_GetSCENE_MODE_BARCODE};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_BEACH = {read=_GetSCENE_MODE_BEACH};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_CANDLELIGHT = {read=_GetSCENE_MODE_CANDLELIGHT};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_FIREWORKS = {read=_GetSCENE_MODE_FIREWORKS};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_HDR = {read=_GetSCENE_MODE_HDR};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_LANDSCAPE = {read=_GetSCENE_MODE_LANDSCAPE};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_NIGHT = {read=_GetSCENE_MODE_NIGHT};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_NIGHT_PORTRAIT = {read=_GetSCENE_MODE_NIGHT_PORTRAIT};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_PARTY = {read=_GetSCENE_MODE_PARTY};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_PORTRAIT = {read=_GetSCENE_MODE_PORTRAIT};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_SNOW = {read=_GetSCENE_MODE_SNOW};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_SPORTS = {read=_GetSCENE_MODE_SPORTS};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_STEADYPHOTO = {read=_GetSCENE_MODE_STEADYPHOTO};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_SUNSET = {read=_GetSCENE_MODE_SUNSET};
	__property Androidapi::Jni::Javatypes::_di_JString SCENE_MODE_THEATRE = {read=_GetSCENE_MODE_THEATRE};
	__property Androidapi::Jni::Javatypes::_di_JString WHITE_BALANCE_AUTO = {read=_GetWHITE_BALANCE_AUTO};
	__property Androidapi::Jni::Javatypes::_di_JString WHITE_BALANCE_CLOUDY_DAYLIGHT = {read=_GetWHITE_BALANCE_CLOUDY_DAYLIGHT};
	__property Androidapi::Jni::Javatypes::_di_JString WHITE_BALANCE_DAYLIGHT = {read=_GetWHITE_BALANCE_DAYLIGHT};
	__property Androidapi::Jni::Javatypes::_di_JString WHITE_BALANCE_FLUORESCENT = {read=_GetWHITE_BALANCE_FLUORESCENT};
	__property Androidapi::Jni::Javatypes::_di_JString WHITE_BALANCE_INCANDESCENT = {read=_GetWHITE_BALANCE_INCANDESCENT};
	__property Androidapi::Jni::Javatypes::_di_JString WHITE_BALANCE_SHADE = {read=_GetWHITE_BALANCE_SHADE};
	__property Androidapi::Jni::Javatypes::_di_JString WHITE_BALANCE_TWILIGHT = {read=_GetWHITE_BALANCE_TWILIGHT};
	__property Androidapi::Jni::Javatypes::_di_JString WHITE_BALANCE_WARM_FLUORESCENT = {read=_GetWHITE_BALANCE_WARM_FLUORESCENT};
};

__interface  INTERFACE_UUID("{EFDE0CD6-C9EB-4DE2-B903-A61589549842}") JCamera_Parameters  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl flatten() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl get(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAntibanding() = 0 ;
	virtual bool __cdecl getAutoExposureLock() = 0 ;
	virtual bool __cdecl getAutoWhiteBalanceLock() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getColorEffect() = 0 ;
	virtual int __cdecl getExposureCompensation() = 0 ;
	virtual float __cdecl getExposureCompensationStep() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFlashMode() = 0 ;
	virtual float __cdecl getFocalLength() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getFocusAreas() = 0 ;
	virtual void __cdecl getFocusDistances(Androidapi::Jnibridge::TJavaArray__1<float>* output) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFocusMode() = 0 ;
	virtual float __cdecl getHorizontalViewAngle() = 0 ;
	virtual int __cdecl getInt(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual int __cdecl getJpegQuality() = 0 ;
	virtual int __cdecl getJpegThumbnailQuality() = 0 ;
	virtual _di_JCamera_Size __cdecl getJpegThumbnailSize() = 0 ;
	virtual int __cdecl getMaxExposureCompensation() = 0 ;
	virtual int __cdecl getMaxNumDetectedFaces() = 0 ;
	virtual int __cdecl getMaxNumFocusAreas() = 0 ;
	virtual int __cdecl getMaxNumMeteringAreas() = 0 ;
	virtual int __cdecl getMaxZoom() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getMeteringAreas() = 0 ;
	virtual int __cdecl getMinExposureCompensation() = 0 ;
	virtual int __cdecl getPictureFormat() = 0 ;
	virtual _di_JCamera_Size __cdecl getPictureSize() = 0 ;
	virtual _di_JCamera_Size __cdecl getPreferredPreviewSizeForVideo() = 0 ;
	virtual int __cdecl getPreviewFormat() = 0 ;
	virtual void __cdecl getPreviewFpsRange(Androidapi::Jnibridge::TJavaArray__1<int>* range) = 0 ;
	virtual int __cdecl getPreviewFrameRate() = 0 ;
	virtual _di_JCamera_Size __cdecl getPreviewSize() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSceneMode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedAntibanding() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedColorEffects() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedFlashModes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedFocusModes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedJpegThumbnailSizes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedPictureFormats() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedPictureSizes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedPreviewFormats() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JList>* __cdecl getSupportedPreviewFpsRange() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedPreviewFrameRates() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedPreviewSizes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedSceneModes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedVideoSizes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getSupportedWhiteBalance() = 0 ;
	virtual float __cdecl getVerticalViewAngle() = 0 ;
	virtual bool __cdecl getVideoStabilization() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getWhiteBalance() = 0 ;
	virtual int __cdecl getZoom() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getZoomRatios() = 0 ;
	virtual bool __cdecl isAutoExposureLockSupported() = 0 ;
	virtual bool __cdecl isAutoWhiteBalanceLockSupported() = 0 ;
	virtual bool __cdecl isSmoothZoomSupported() = 0 ;
	virtual bool __cdecl isVideoSnapshotSupported() = 0 ;
	virtual bool __cdecl isVideoStabilizationSupported() = 0 ;
	virtual bool __cdecl isZoomSupported() = 0 ;
	virtual void __cdecl remove(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual void __cdecl removeGpsData() = 0 ;
	virtual void __cdecl set(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JString value) = 0 /* overload */;
	virtual void __cdecl set(Androidapi::Jni::Javatypes::_di_JString key, int value) = 0 /* overload */;
	virtual void __cdecl setAntibanding(Androidapi::Jni::Javatypes::_di_JString antibanding) = 0 ;
	virtual void __cdecl setAutoExposureLock(bool toggle) = 0 ;
	virtual void __cdecl setAutoWhiteBalanceLock(bool toggle) = 0 ;
	virtual void __cdecl setColorEffect(Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl setExposureCompensation(int value) = 0 ;
	virtual void __cdecl setFlashMode(Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl setFocusAreas(Androidapi::Jni::Javatypes::_di_JList focusAreas) = 0 ;
	virtual void __cdecl setFocusMode(Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl setGpsAltitude(double altitude) = 0 ;
	virtual void __cdecl setGpsLatitude(double latitude) = 0 ;
	virtual void __cdecl setGpsLongitude(double longitude) = 0 ;
	virtual void __cdecl setGpsProcessingMethod(Androidapi::Jni::Javatypes::_di_JString processing_method) = 0 ;
	virtual void __cdecl setGpsTimestamp(__int64 timestamp) = 0 ;
	virtual void __cdecl setJpegQuality(int quality) = 0 ;
	virtual void __cdecl setJpegThumbnailQuality(int quality) = 0 ;
	virtual void __cdecl setJpegThumbnailSize(int width, int height) = 0 ;
	virtual void __cdecl setMeteringAreas(Androidapi::Jni::Javatypes::_di_JList meteringAreas) = 0 ;
	virtual void __cdecl setPictureFormat(int pixel_format) = 0 ;
	virtual void __cdecl setPictureSize(int width, int height) = 0 ;
	virtual void __cdecl setPreviewFormat(int pixel_format) = 0 ;
	virtual void __cdecl setPreviewFpsRange(int min, int max) = 0 ;
	virtual void __cdecl setPreviewFrameRate(int fps) = 0 ;
	virtual void __cdecl setPreviewSize(int width, int height) = 0 ;
	virtual void __cdecl setRecordingHint(bool hint) = 0 ;
	virtual void __cdecl setRotation(int rotation) = 0 ;
	virtual void __cdecl setSceneMode(Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl setVideoStabilization(bool toggle) = 0 ;
	virtual void __cdecl setWhiteBalance(Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl setZoom(int value) = 0 ;
	virtual void __cdecl unflatten(Androidapi::Jni::Javatypes::_di_JString flattened) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_Parameters : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_ParametersClass,_di_JCamera_Parameters>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_ParametersClass,_di_JCamera_Parameters> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_Parameters() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_ParametersClass,_di_JCamera_Parameters>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_Parameters() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{45CCC52F-A446-40A5-BA95-A16D17A11415}") JCamera_PictureCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{307615DE-4EFD-4290-A113-CCE958C0C8C2}") JCamera_PictureCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onPictureTaken(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* data, _di_JCamera camera) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_PictureCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_PictureCallbackClass,_di_JCamera_PictureCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_PictureCallbackClass,_di_JCamera_PictureCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_PictureCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_PictureCallbackClass,_di_JCamera_PictureCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_PictureCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C6836D36-1914-4DB8-8458-D6AEC71A7257}") JCamera_PreviewCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{6F2F0374-DCFF-43EC-B8BF-DB2F72574EBB}") JCamera_PreviewCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onPreviewFrame(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* data, _di_JCamera camera) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_PreviewCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_PreviewCallbackClass,_di_JCamera_PreviewCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_PreviewCallbackClass,_di_JCamera_PreviewCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_PreviewCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_PreviewCallbackClass,_di_JCamera_PreviewCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_PreviewCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D658141F-9627-4E2E-8B23-CDF1814F02FB}") JCamera_ShutterCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{50F23354-86CD-4B59-9CC8-E647BDF98EC2}") JCamera_ShutterCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onShutter() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_ShutterCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_ShutterCallbackClass,_di_JCamera_ShutterCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_ShutterCallbackClass,_di_JCamera_ShutterCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_ShutterCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_ShutterCallbackClass,_di_JCamera_ShutterCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_ShutterCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{23FA6E4F-E2F1-4FDF-9892-A56C71EEA6D4}") JCamera_SizeClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCamera_Size __cdecl init(int w, int h) = 0 ;
};

__interface  INTERFACE_UUID("{2D2A15A6-C3ED-4B61-8276-214F497A766A}") JCamera_Size  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _Getheight() = 0 ;
	virtual void __cdecl _Setheight(int Value) = 0 ;
	virtual int __cdecl _Getwidth() = 0 ;
	virtual void __cdecl _Setwidth(int Value) = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	__property int height = {read=_Getheight, write=_Setheight};
	__property int width = {read=_Getwidth, write=_Setwidth};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCamera_Size : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_SizeClass,_di_JCamera_Size>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_SizeClass,_di_JCamera_Size> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCamera_Size() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCamera_SizeClass,_di_JCamera_Size>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCamera_Size() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EAF20941-0999-4B3C-B333-5DC80A38FB36}") JDisplayManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDISPLAY_CATEGORY_PRESENTATION() = 0 ;
	virtual int __cdecl _GetVIRTUAL_DISPLAY_FLAG_AUTO_MIRROR() = 0 ;
	virtual int __cdecl _GetVIRTUAL_DISPLAY_FLAG_OWN_CONTENT_ONLY() = 0 ;
	virtual int __cdecl _GetVIRTUAL_DISPLAY_FLAG_PRESENTATION() = 0 ;
	virtual int __cdecl _GetVIRTUAL_DISPLAY_FLAG_PUBLIC() = 0 ;
	virtual int __cdecl _GetVIRTUAL_DISPLAY_FLAG_SECURE() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString DISPLAY_CATEGORY_PRESENTATION = {read=_GetDISPLAY_CATEGORY_PRESENTATION};
	__property int VIRTUAL_DISPLAY_FLAG_AUTO_MIRROR = {read=_GetVIRTUAL_DISPLAY_FLAG_AUTO_MIRROR};
	__property int VIRTUAL_DISPLAY_FLAG_OWN_CONTENT_ONLY = {read=_GetVIRTUAL_DISPLAY_FLAG_OWN_CONTENT_ONLY};
	__property int VIRTUAL_DISPLAY_FLAG_PRESENTATION = {read=_GetVIRTUAL_DISPLAY_FLAG_PRESENTATION};
	__property int VIRTUAL_DISPLAY_FLAG_PUBLIC = {read=_GetVIRTUAL_DISPLAY_FLAG_PUBLIC};
	__property int VIRTUAL_DISPLAY_FLAG_SECURE = {read=_GetVIRTUAL_DISPLAY_FLAG_SECURE};
};

__interface  INTERFACE_UUID("{5B4765F5-3933-4CE4-BDA9-DA797F5B913D}") JDisplayManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JVirtualDisplay __cdecl createVirtualDisplay(Androidapi::Jni::Javatypes::_di_JString name, int width, int height, int densityDpi, Androidapi::Jni::Graphicscontentviewtext::_di_JSurface surface, int flags) = 0 /* overload */;
	virtual _di_JVirtualDisplay __cdecl createVirtualDisplay(Androidapi::Jni::Javatypes::_di_JString name, int width, int height, int densityDpi, Androidapi::Jni::Graphicscontentviewtext::_di_JSurface surface, int flags, _di_JVirtualDisplay_Callback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDisplay __cdecl getDisplay(int displayId) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JDisplay>* __cdecl getDisplays() = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JDisplay>* __cdecl getDisplays(Androidapi::Jni::Javatypes::_di_JString category) = 0 /* overload */;
	virtual void __cdecl registerDisplayListener(_di_JDisplayManager_DisplayListener listener, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual void __cdecl unregisterDisplayListener(_di_JDisplayManager_DisplayListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDisplayManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDisplayManagerClass,_di_JDisplayManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDisplayManagerClass,_di_JDisplayManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDisplayManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDisplayManagerClass,_di_JDisplayManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDisplayManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{77B7E5F8-15B2-4463-BF5C-EB037A7C8673}") JDisplayManager_DisplayListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{96449BAC-9FC3-41DF-9784-CFEA8E98341E}") JDisplayManager_DisplayListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onDisplayAdded(int displayId) = 0 ;
	virtual void __cdecl onDisplayChanged(int displayId) = 0 ;
	virtual void __cdecl onDisplayRemoved(int displayId) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDisplayManager_DisplayListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDisplayManager_DisplayListenerClass,_di_JDisplayManager_DisplayListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDisplayManager_DisplayListenerClass,_di_JDisplayManager_DisplayListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDisplayManager_DisplayListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDisplayManager_DisplayListenerClass,_di_JDisplayManager_DisplayListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDisplayManager_DisplayListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{306EA32E-6D20-433A-A8D4-DD0C5489A026}") JVirtualDisplayClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{38AFF33C-3F86-4FF3-B2B7-987CFBA39506}") JVirtualDisplay  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDisplay __cdecl getDisplay() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JSurface __cdecl getSurface() = 0 ;
	virtual void __cdecl release() = 0 ;
	virtual void __cdecl resize(int width, int height, int densityDpi) = 0 ;
	virtual void __cdecl setSurface(Androidapi::Jni::Graphicscontentviewtext::_di_JSurface surface) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVirtualDisplay : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualDisplayClass,_di_JVirtualDisplay>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualDisplayClass,_di_JVirtualDisplay> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVirtualDisplay() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualDisplayClass,_di_JVirtualDisplay>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVirtualDisplay() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9DED19F6-C2C2-4F18-AE4A-4ED00C3F790A}") JVirtualDisplay_CallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JVirtualDisplay_Callback __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{3917E6C4-8330-4CA4-8866-CC55C0F3EA23}") JVirtualDisplay_Callback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onPaused() = 0 ;
	virtual void __cdecl onResumed() = 0 ;
	virtual void __cdecl onStopped() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVirtualDisplay_Callback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualDisplay_CallbackClass,_di_JVirtualDisplay_Callback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualDisplay_CallbackClass,_di_JVirtualDisplay_Callback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVirtualDisplay_Callback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVirtualDisplay_CallbackClass,_di_JVirtualDisplay_Callback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVirtualDisplay_Callback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Hardware */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_HARDWARE)
using namespace Androidapi::Jni::Hardware;
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
#endif	// Androidapi_Jni_HardwareHPP
