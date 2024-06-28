// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Support.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_SupportHPP
#define Androidapi_Jni_SupportHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Net.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.JNI.Widget.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Support
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JContextCompatClass;
typedef System::DelphiInterface<JContextCompatClass> _di_JContextCompatClass;
__interface DELPHIINTERFACE JContextCompat;
typedef System::DelphiInterface<JContextCompat> _di_JContextCompat;
class DELPHICLASS TJContextCompat;
__interface DELPHIINTERFACE JActivityCompatClass;
typedef System::DelphiInterface<JActivityCompatClass> _di_JActivityCompatClass;
__interface DELPHIINTERFACE JActivityCompat;
typedef System::DelphiInterface<JActivityCompat> _di_JActivityCompat;
class DELPHICLASS TJActivityCompat;
__interface DELPHIINTERFACE Japp_FragmentClass;
typedef System::DelphiInterface<Japp_FragmentClass> _di_Japp_FragmentClass;
__interface DELPHIINTERFACE Japp_Fragment;
typedef System::DelphiInterface<Japp_Fragment> _di_Japp_Fragment;
class DELPHICLASS TJapp_Fragment;
__interface DELPHIINTERFACE Japp_Fragment_SavedStateClass;
typedef System::DelphiInterface<Japp_Fragment_SavedStateClass> _di_Japp_Fragment_SavedStateClass;
__interface DELPHIINTERFACE Japp_Fragment_SavedState;
typedef System::DelphiInterface<Japp_Fragment_SavedState> _di_Japp_Fragment_SavedState;
class DELPHICLASS TJapp_Fragment_SavedState;
__interface DELPHIINTERFACE Japp_FragmentActivityClass;
typedef System::DelphiInterface<Japp_FragmentActivityClass> _di_Japp_FragmentActivityClass;
__interface DELPHIINTERFACE Japp_FragmentActivity;
typedef System::DelphiInterface<Japp_FragmentActivity> _di_Japp_FragmentActivity;
class DELPHICLASS TJapp_FragmentActivity;
__interface DELPHIINTERFACE Japp_FragmentManagerClass;
typedef System::DelphiInterface<Japp_FragmentManagerClass> _di_Japp_FragmentManagerClass;
__interface DELPHIINTERFACE Japp_FragmentManager;
typedef System::DelphiInterface<Japp_FragmentManager> _di_Japp_FragmentManager;
class DELPHICLASS TJapp_FragmentManager;
__interface DELPHIINTERFACE Japp_FragmentManager_BackStackEntryClass;
typedef System::DelphiInterface<Japp_FragmentManager_BackStackEntryClass> _di_Japp_FragmentManager_BackStackEntryClass;
__interface DELPHIINTERFACE Japp_FragmentManager_BackStackEntry;
typedef System::DelphiInterface<Japp_FragmentManager_BackStackEntry> _di_Japp_FragmentManager_BackStackEntry;
class DELPHICLASS TJapp_FragmentManager_BackStackEntry;
__interface DELPHIINTERFACE Japp_FragmentManager_FragmentLifecycleCallbacksClass;
typedef System::DelphiInterface<Japp_FragmentManager_FragmentLifecycleCallbacksClass> _di_Japp_FragmentManager_FragmentLifecycleCallbacksClass;
__interface DELPHIINTERFACE Japp_FragmentManager_FragmentLifecycleCallbacks;
typedef System::DelphiInterface<Japp_FragmentManager_FragmentLifecycleCallbacks> _di_Japp_FragmentManager_FragmentLifecycleCallbacks;
class DELPHICLASS TJapp_FragmentManager_FragmentLifecycleCallbacks;
__interface DELPHIINTERFACE Japp_FragmentManager_OnBackStackChangedListenerClass;
typedef System::DelphiInterface<Japp_FragmentManager_OnBackStackChangedListenerClass> _di_Japp_FragmentManager_OnBackStackChangedListenerClass;
__interface DELPHIINTERFACE Japp_FragmentManager_OnBackStackChangedListener;
typedef System::DelphiInterface<Japp_FragmentManager_OnBackStackChangedListener> _di_Japp_FragmentManager_OnBackStackChangedListener;
class DELPHICLASS TJapp_FragmentManager_OnBackStackChangedListener;
__interface DELPHIINTERFACE Japp_FragmentTransactionClass;
typedef System::DelphiInterface<Japp_FragmentTransactionClass> _di_Japp_FragmentTransactionClass;
__interface DELPHIINTERFACE Japp_FragmentTransaction;
typedef System::DelphiInterface<Japp_FragmentTransaction> _di_Japp_FragmentTransaction;
class DELPHICLASS TJapp_FragmentTransaction;
__interface DELPHIINTERFACE JJobIntentServiceClass;
typedef System::DelphiInterface<JJobIntentServiceClass> _di_JJobIntentServiceClass;
__interface DELPHIINTERFACE JJobIntentService;
typedef System::DelphiInterface<JJobIntentService> _di_JJobIntentService;
class DELPHICLASS TJJobIntentService;
__interface DELPHIINTERFACE Japp_LoaderManagerClass;
typedef System::DelphiInterface<Japp_LoaderManagerClass> _di_Japp_LoaderManagerClass;
__interface DELPHIINTERFACE Japp_LoaderManager;
typedef System::DelphiInterface<Japp_LoaderManager> _di_Japp_LoaderManager;
class DELPHICLASS TJapp_LoaderManager;
__interface DELPHIINTERFACE Japp_LoaderManager_LoaderCallbacksClass;
typedef System::DelphiInterface<Japp_LoaderManager_LoaderCallbacksClass> _di_Japp_LoaderManager_LoaderCallbacksClass;
__interface DELPHIINTERFACE Japp_LoaderManager_LoaderCallbacks;
typedef System::DelphiInterface<Japp_LoaderManager_LoaderCallbacks> _di_Japp_LoaderManager_LoaderCallbacks;
class DELPHICLASS TJapp_LoaderManager_LoaderCallbacks;
__interface DELPHIINTERFACE JNotificationCompat_ActionClass;
typedef System::DelphiInterface<JNotificationCompat_ActionClass> _di_JNotificationCompat_ActionClass;
__interface DELPHIINTERFACE JNotificationCompat_Action;
typedef System::DelphiInterface<JNotificationCompat_Action> _di_JNotificationCompat_Action;
class DELPHICLASS TJNotificationCompat_Action;
__interface DELPHIINTERFACE JNotificationCompat_BuilderClass;
typedef System::DelphiInterface<JNotificationCompat_BuilderClass> _di_JNotificationCompat_BuilderClass;
__interface DELPHIINTERFACE JNotificationCompat_Builder;
typedef System::DelphiInterface<JNotificationCompat_Builder> _di_JNotificationCompat_Builder;
class DELPHICLASS TJNotificationCompat_Builder;
__interface DELPHIINTERFACE JNotificationCompat_ExtenderClass;
typedef System::DelphiInterface<JNotificationCompat_ExtenderClass> _di_JNotificationCompat_ExtenderClass;
__interface DELPHIINTERFACE JNotificationCompat_Extender;
typedef System::DelphiInterface<JNotificationCompat_Extender> _di_JNotificationCompat_Extender;
class DELPHICLASS TJNotificationCompat_Extender;
__interface DELPHIINTERFACE JNotificationCompat_StyleClass;
typedef System::DelphiInterface<JNotificationCompat_StyleClass> _di_JNotificationCompat_StyleClass;
__interface DELPHIINTERFACE JNotificationCompat_Style;
typedef System::DelphiInterface<JNotificationCompat_Style> _di_JNotificationCompat_Style;
class DELPHICLASS TJNotificationCompat_Style;
__interface DELPHIINTERFACE Japp_RemoteInputClass;
typedef System::DelphiInterface<Japp_RemoteInputClass> _di_Japp_RemoteInputClass;
__interface DELPHIINTERFACE Japp_RemoteInput;
typedef System::DelphiInterface<Japp_RemoteInput> _di_Japp_RemoteInput;
class DELPHICLASS TJapp_RemoteInput;
__interface DELPHIINTERFACE Japp_SharedElementCallbackClass;
typedef System::DelphiInterface<Japp_SharedElementCallbackClass> _di_Japp_SharedElementCallbackClass;
__interface DELPHIINTERFACE Japp_SharedElementCallback;
typedef System::DelphiInterface<Japp_SharedElementCallback> _di_Japp_SharedElementCallback;
class DELPHICLASS TJapp_SharedElementCallback;
__interface DELPHIINTERFACE Japp_SharedElementCallback_OnSharedElementsReadyListenerClass;
typedef System::DelphiInterface<Japp_SharedElementCallback_OnSharedElementsReadyListenerClass> _di_Japp_SharedElementCallback_OnSharedElementsReadyListenerClass;
__interface DELPHIINTERFACE Japp_SharedElementCallback_OnSharedElementsReadyListener;
typedef System::DelphiInterface<Japp_SharedElementCallback_OnSharedElementsReadyListener> _di_Japp_SharedElementCallback_OnSharedElementsReadyListener;
class DELPHICLASS TJapp_SharedElementCallback_OnSharedElementsReadyListener;
__interface DELPHIINTERFACE JFileProviderClass;
typedef System::DelphiInterface<JFileProviderClass> _di_JFileProviderClass;
__interface DELPHIINTERFACE JFileProvider;
typedef System::DelphiInterface<JFileProvider> _di_JFileProvider;
class DELPHICLASS TJFileProvider;
__interface DELPHIINTERFACE Jcontent_LoaderClass;
typedef System::DelphiInterface<Jcontent_LoaderClass> _di_Jcontent_LoaderClass;
__interface DELPHIINTERFACE Jcontent_Loader;
typedef System::DelphiInterface<Jcontent_Loader> _di_Jcontent_Loader;
class DELPHICLASS TJcontent_Loader;
__interface DELPHIINTERFACE Jcontent_Loader_OnLoadCanceledListenerClass;
typedef System::DelphiInterface<Jcontent_Loader_OnLoadCanceledListenerClass> _di_Jcontent_Loader_OnLoadCanceledListenerClass;
__interface DELPHIINTERFACE Jcontent_Loader_OnLoadCanceledListener;
typedef System::DelphiInterface<Jcontent_Loader_OnLoadCanceledListener> _di_Jcontent_Loader_OnLoadCanceledListener;
class DELPHICLASS TJcontent_Loader_OnLoadCanceledListener;
__interface DELPHIINTERFACE Jcontent_Loader_OnLoadCompleteListenerClass;
typedef System::DelphiInterface<Jcontent_Loader_OnLoadCompleteListenerClass> _di_Jcontent_Loader_OnLoadCompleteListenerClass;
__interface DELPHIINTERFACE Jcontent_Loader_OnLoadCompleteListener;
typedef System::DelphiInterface<Jcontent_Loader_OnLoadCompleteListener> _di_Jcontent_Loader_OnLoadCompleteListener;
class DELPHICLASS TJcontent_Loader_OnLoadCompleteListener;
__interface DELPHIINTERFACE JPermissionCheckerClass;
typedef System::DelphiInterface<JPermissionCheckerClass> _di_JPermissionCheckerClass;
__interface DELPHIINTERFACE JPermissionChecker;
typedef System::DelphiInterface<JPermissionChecker> _di_JPermissionChecker;
class DELPHICLASS TJPermissionChecker;
__interface DELPHIINTERFACE JWakefulBroadcastReceiverClass;
typedef System::DelphiInterface<JWakefulBroadcastReceiverClass> _di_JWakefulBroadcastReceiverClass;
__interface DELPHIINTERFACE JWakefulBroadcastReceiver;
typedef System::DelphiInterface<JWakefulBroadcastReceiver> _di_JWakefulBroadcastReceiver;
class DELPHICLASS TJWakefulBroadcastReceiver;
__interface DELPHIINTERFACE JWindowInsetsCompatClass;
typedef System::DelphiInterface<JWindowInsetsCompatClass> _di_JWindowInsetsCompatClass;
__interface DELPHIINTERFACE JWindowInsetsCompat;
typedef System::DelphiInterface<JWindowInsetsCompat> _di_JWindowInsetsCompat;
class DELPHICLASS TJWindowInsetsCompat;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{17CBF90F-B907-448F-9BFE-07ABAD5919D0}") JContextCompatClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl checkSelfPermission(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString permission) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JContext __cdecl createDeviceProtectedStorageContext(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFile __cdecl getCodeCacheDir(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual int __cdecl getColor(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int id) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList __cdecl getColorStateList(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int id) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFile __cdecl getDataDir(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int id) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JFile>* __cdecl getExternalCacheDirs(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JFile>* __cdecl getExternalFilesDirs(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString type_) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFile __cdecl getNoBackupFilesDir(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JFile>* __cdecl getObbDirs(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual bool __cdecl isDeviceProtectedStorage(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual bool __cdecl startActivities(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JIntent>* intents) = 0 /* overload */;
	virtual bool __cdecl startActivities(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JIntent>* intents, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startActivity(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Os::_di_JBundle options) = 0 ;
	virtual void __cdecl startForegroundService(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
};

__interface  INTERFACE_UUID("{DA319CC4-B7F8-4702-B969-3137BE6260C9}") JContextCompat  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJContextCompat : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JContextCompatClass,_di_JContextCompat>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JContextCompatClass,_di_JContextCompat> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJContextCompat() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JContextCompatClass,_di_JContextCompat>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJContextCompat() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AF83EB83-0A07-45E4-A615-3E9F50EEC123}") JActivityCompatClass  : public JContextCompatClass 
{
	virtual void __cdecl finishAffinity(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	virtual void __cdecl finishAfterTransition(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	virtual Androidapi::Jni::Net::_di_Jnet_Uri __cdecl getReferrer(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	virtual bool __cdecl invalidateOptionsMenu(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	virtual void __cdecl postponeEnterTransition(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
	virtual void __cdecl requestPermissions(Androidapi::Jni::App::_di_JActivity activity, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* permissions, int requestCode) = 0 ;
	virtual void __cdecl setEnterSharedElementCallback(Androidapi::Jni::App::_di_JActivity activity, _di_Japp_SharedElementCallback callback) = 0 ;
	virtual void __cdecl setExitSharedElementCallback(Androidapi::Jni::App::_di_JActivity activity, _di_Japp_SharedElementCallback callback) = 0 ;
	virtual bool __cdecl shouldShowRequestPermissionRationale(Androidapi::Jni::App::_di_JActivity activity, Androidapi::Jni::Javatypes::_di_JString permission) = 0 ;
	virtual void __cdecl startActivityForResult(Androidapi::Jni::App::_di_JActivity activity, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode, Androidapi::Jni::Os::_di_JBundle options) = 0 ;
	virtual void __cdecl startIntentSenderForResult(Androidapi::Jni::App::_di_JActivity activity, Androidapi::Jni::Graphicscontentviewtext::_di_JIntentSender intent, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent fillInIntent, int flagsMask, int flagsValues, int extraFlags, Androidapi::Jni::Os::_di_JBundle options) = 0 ;
	virtual void __cdecl startPostponedEnterTransition(Androidapi::Jni::App::_di_JActivity activity) = 0 ;
};

__interface  INTERFACE_UUID("{7108F0BF-5819-4668-9D20-7165FCB5A871}") JActivityCompat  : public JContextCompat 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJActivityCompat : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityCompatClass,_di_JActivityCompat>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityCompatClass,_di_JActivityCompat> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJActivityCompat() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JActivityCompatClass,_di_JActivityCompat>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJActivityCompat() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E3089B9B-FD4C-463E-A7C9-BD9DE5C6D3F7}") Japp_FragmentClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_Japp_Fragment __cdecl init() = 0 ;
	virtual _di_Japp_Fragment __cdecl instantiate(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString fname) = 0 /* overload */;
	virtual _di_Japp_Fragment __cdecl instantiate(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString fname, Androidapi::Jni::Os::_di_JBundle args) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{7C819B68-2FEC-4843-B2FB-B0CCFDA11642}") Japp_Fragment  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JString prefix, Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jni::Javatypes::_di_JPrintWriter writer, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual _di_Japp_FragmentActivity __cdecl getActivity() = 0 ;
	virtual bool __cdecl getAllowEnterTransitionOverlap() = 0 ;
	virtual bool __cdecl getAllowReturnTransitionOverlap() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getArguments() = 0 ;
	virtual _di_Japp_FragmentManager __cdecl getChildFragmentManager() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JContext __cdecl getContext() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getEnterTransition() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getExitTransition() = 0 ;
	virtual _di_Japp_FragmentManager __cdecl getFragmentManager() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getHost() = 0 ;
	virtual int __cdecl getId() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater __cdecl getLayoutInflater() = 0 ;
	virtual _di_Japp_LoaderManager __cdecl getLoaderManager() = 0 ;
	virtual _di_Japp_Fragment __cdecl getParentFragment() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getReenterTransition() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JResources __cdecl getResources() = 0 ;
	virtual bool __cdecl getRetainInstance() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getReturnTransition() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getSharedElementEnterTransition() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getSharedElementReturnTransition() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getString(int resId) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTag() = 0 ;
	virtual _di_Japp_Fragment __cdecl getTargetFragment() = 0 ;
	virtual int __cdecl getTargetRequestCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getText(int resId) = 0 ;
	virtual bool __cdecl getUserVisibleHint() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getView() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isAdded() = 0 ;
	virtual bool __cdecl isDetached() = 0 ;
	virtual bool __cdecl isHidden() = 0 ;
	virtual bool __cdecl isInLayout() = 0 ;
	virtual bool __cdecl isRemoving() = 0 ;
	virtual bool __cdecl isResumed() = 0 ;
	virtual bool __cdecl isStateSaved() = 0 ;
	virtual bool __cdecl isVisible() = 0 ;
	virtual void __cdecl onActivityCreated(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onActivityResult(int requestCode, int resultCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent data) = 0 ;
	virtual void __cdecl onAttach(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	virtual void __cdecl onAttach(Androidapi::Jni::App::_di_JActivity activity) = 0 /* overload */;
	virtual void __cdecl onAttachFragment(_di_Japp_Fragment childFragment) = 0 ;
	virtual void __cdecl onConfigurationChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 ;
	virtual bool __cdecl onContextItemSelected(Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JAnimation __cdecl onCreateAnimation(int transit, bool enter, int nextAnim) = 0 ;
	virtual void __cdecl onCreateContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JContextMenu menu, Androidapi::Jni::Graphicscontentviewtext::_di_JView v, Androidapi::Jni::Graphicscontentviewtext::_di_JContextMenu_ContextMenuInfo menuInfo) = 0 ;
	virtual void __cdecl onCreateOptionsMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu, Androidapi::Jni::Graphicscontentviewtext::_di_JMenuInflater inflater) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateView(Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater inflater, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup container, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onDestroy() = 0 ;
	virtual void __cdecl onDestroyOptionsMenu() = 0 ;
	virtual void __cdecl onDestroyView() = 0 ;
	virtual void __cdecl onDetach() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLayoutInflater __cdecl onGetLayoutInflater(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onHiddenChanged(bool hidden) = 0 ;
	virtual void __cdecl onInflate(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 /* overload */;
	virtual void __cdecl onInflate(Androidapi::Jni::App::_di_JActivity activity, Androidapi::Jni::Util::_di_JAttributeSet attrs, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 /* overload */;
	virtual void __cdecl onLowMemory() = 0 ;
	virtual void __cdecl onMultiWindowModeChanged(bool isInMultiWindowMode) = 0 ;
	virtual bool __cdecl onOptionsItemSelected(Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual void __cdecl onOptionsMenuClosed(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onPause() = 0 ;
	virtual void __cdecl onPictureInPictureModeChanged(bool isInPictureInPictureMode) = 0 ;
	virtual void __cdecl onPrepareOptionsMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onRequestPermissionsResult(int requestCode, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* permissions, Androidapi::Jnibridge::TJavaArray__1<int>* grantResults) = 0 ;
	virtual void __cdecl onResume() = 0 ;
	virtual void __cdecl onSaveInstanceState(Androidapi::Jni::Os::_di_JBundle outState) = 0 ;
	virtual void __cdecl onStart() = 0 ;
	virtual void __cdecl onStop() = 0 ;
	virtual void __cdecl onViewCreated(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onViewStateRestored(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl postponeEnterTransition() = 0 ;
	virtual void __cdecl registerForContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual void __cdecl requestPermissions(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* permissions, int requestCode) = 0 ;
	virtual void __cdecl setAllowEnterTransitionOverlap(bool allow) = 0 ;
	virtual void __cdecl setAllowReturnTransitionOverlap(bool allow) = 0 ;
	virtual void __cdecl setArguments(Androidapi::Jni::Os::_di_JBundle args) = 0 ;
	virtual void __cdecl setEnterSharedElementCallback(_di_Japp_SharedElementCallback callback) = 0 ;
	virtual void __cdecl setEnterTransition(Androidapi::Jni::Javatypes::_di_JObject transition) = 0 ;
	virtual void __cdecl setExitSharedElementCallback(_di_Japp_SharedElementCallback callback) = 0 ;
	virtual void __cdecl setExitTransition(Androidapi::Jni::Javatypes::_di_JObject transition) = 0 ;
	virtual void __cdecl setHasOptionsMenu(bool hasMenu) = 0 ;
	virtual void __cdecl setInitialSavedState(_di_Japp_Fragment_SavedState state) = 0 ;
	virtual void __cdecl setMenuVisibility(bool menuVisible) = 0 ;
	virtual void __cdecl setReenterTransition(Androidapi::Jni::Javatypes::_di_JObject transition) = 0 ;
	virtual void __cdecl setRetainInstance(bool retain) = 0 ;
	virtual void __cdecl setReturnTransition(Androidapi::Jni::Javatypes::_di_JObject transition) = 0 ;
	virtual void __cdecl setSharedElementEnterTransition(Androidapi::Jni::Javatypes::_di_JObject transition) = 0 ;
	virtual void __cdecl setSharedElementReturnTransition(Androidapi::Jni::Javatypes::_di_JObject transition) = 0 ;
	virtual void __cdecl setTargetFragment(_di_Japp_Fragment fragment, int requestCode) = 0 ;
	virtual void __cdecl setUserVisibleHint(bool isVisibleToUser) = 0 ;
	virtual bool __cdecl shouldShowRequestPermissionRationale(Androidapi::Jni::Javatypes::_di_JString permission) = 0 ;
	virtual void __cdecl startActivity(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 /* overload */;
	virtual void __cdecl startActivity(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startActivityForResult(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode) = 0 /* overload */;
	virtual void __cdecl startActivityForResult(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startIntentSenderForResult(Androidapi::Jni::Graphicscontentviewtext::_di_JIntentSender intent, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent fillInIntent, int flagsMask, int flagsValues, int extraFlags, Androidapi::Jni::Os::_di_JBundle options) = 0 ;
	virtual void __cdecl startPostponedEnterTransition() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl unregisterForContextMenu(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_Fragment : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentClass,_di_Japp_Fragment>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentClass,_di_Japp_Fragment> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_Fragment() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentClass,_di_Japp_Fragment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_Fragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6AF46B16-0976-4759-AB40-599B705C4239}") Japp_Fragment_SavedStateClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{21C3F0C5-A8C9-444E-B4DF-8DBA6E797052}") Japp_Fragment_SavedState  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_Fragment_SavedState : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_Fragment_SavedStateClass,_di_Japp_Fragment_SavedState>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_Fragment_SavedStateClass,_di_Japp_Fragment_SavedState> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_Fragment_SavedState() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_Fragment_SavedStateClass,_di_Japp_Fragment_SavedState>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_Fragment_SavedState() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{750FF7AB-0643-439B-A6C3-DB0EA3D1AFD7}") Japp_FragmentActivityClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_Japp_FragmentActivity __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{150D107F-E0C3-49B0-BFC7-5A551379615C}") Japp_FragmentActivity  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JString prefix, Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jni::Javatypes::_di_JPrintWriter writer, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getLastCustomNonConfigurationInstance() = 0 ;
	virtual _di_Japp_FragmentManager __cdecl getSupportFragmentManager() = 0 ;
	virtual _di_Japp_LoaderManager __cdecl getSupportLoaderManager() = 0 ;
	virtual void __cdecl onAttachFragment(_di_Japp_Fragment fragment) = 0 ;
	virtual void __cdecl onBackPressed() = 0 ;
	virtual void __cdecl onConfigurationChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration newConfig) = 0 ;
	virtual bool __cdecl onCreatePanelMenu(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onLowMemory() = 0 ;
	virtual bool __cdecl onMenuItemSelected(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
	virtual void __cdecl onMultiWindowModeChanged(bool isInMultiWindowMode) = 0 ;
	virtual void __cdecl onPanelClosed(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onPictureInPictureModeChanged(bool isInPictureInPictureMode) = 0 ;
	virtual bool __cdecl onPreparePanel(int featureId, Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu) = 0 ;
	virtual void __cdecl onRequestPermissionsResult(int requestCode, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* permissions, Androidapi::Jnibridge::TJavaArray__1<int>* grantResults) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl onRetainCustomNonConfigurationInstance() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl onRetainNonConfigurationInstance() = 0 ;
	virtual void __cdecl onStateNotSaved() = 0 ;
	virtual void __cdecl setEnterSharedElementCallback(_di_Japp_SharedElementCallback callback) = 0 ;
	virtual void __cdecl setExitSharedElementCallback(_di_Japp_SharedElementCallback listener) = 0 ;
	virtual void __cdecl startActivityForResult(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode) = 0 ;
	virtual void __cdecl startActivityFromFragment(_di_Japp_Fragment fragment, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode) = 0 /* overload */;
	virtual void __cdecl startActivityFromFragment(_di_Japp_Fragment fragment, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int requestCode, Androidapi::Jni::Os::_di_JBundle options) = 0 /* overload */;
	virtual void __cdecl startIntentSenderFromFragment(_di_Japp_Fragment fragment, Androidapi::Jni::Graphicscontentviewtext::_di_JIntentSender intent, int requestCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent fillInIntent, int flagsMask, int flagsValues, int extraFlags, Androidapi::Jni::Os::_di_JBundle options) = 0 ;
	virtual void __cdecl supportFinishAfterTransition() = 0 ;
	virtual void __cdecl supportInvalidateOptionsMenu() = 0 ;
	virtual void __cdecl supportPostponeEnterTransition() = 0 ;
	virtual void __cdecl supportStartPostponedEnterTransition() = 0 ;
	virtual void __cdecl validateRequestPermissionsRequestCode(int requestCode) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_FragmentActivity : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentActivityClass,_di_Japp_FragmentActivity>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentActivityClass,_di_Japp_FragmentActivity> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_FragmentActivity() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentActivityClass,_di_Japp_FragmentActivity>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_FragmentActivity() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B337A371-DC72-4A07-940A-4CA4F5FFB078}") Japp_FragmentManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetPOP_BACK_STACK_INCLUSIVE() = 0 ;
	HIDESBASE virtual _di_Japp_FragmentManager __cdecl init() = 0 ;
	virtual void __cdecl enableDebugLogging(bool enabled) = 0 ;
	__property int POP_BACK_STACK_INCLUSIVE = {read=_GetPOP_BACK_STACK_INCLUSIVE};
};

__interface  INTERFACE_UUID("{19B65C80-D723-4014-9185-44BEBAD0947A}") Japp_FragmentManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addOnBackStackChangedListener(_di_Japp_FragmentManager_OnBackStackChangedListener listener) = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl beginTransaction() = 0 ;
	virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JString prefix, Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jni::Javatypes::_di_JPrintWriter writer, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual bool __cdecl executePendingTransactions() = 0 ;
	virtual _di_Japp_Fragment __cdecl findFragmentById(int id) = 0 ;
	virtual _di_Japp_Fragment __cdecl findFragmentByTag(Androidapi::Jni::Javatypes::_di_JString tag) = 0 ;
	virtual _di_Japp_FragmentManager_BackStackEntry __cdecl getBackStackEntryAt(int index) = 0 ;
	virtual int __cdecl getBackStackEntryCount() = 0 ;
	virtual _di_Japp_Fragment __cdecl getFragment(Androidapi::Jni::Os::_di_JBundle bundle, Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getFragments() = 0 ;
	virtual _di_Japp_Fragment __cdecl getPrimaryNavigationFragment() = 0 ;
	virtual bool __cdecl isDestroyed() = 0 ;
	virtual bool __cdecl isStateSaved() = 0 ;
	virtual void __cdecl popBackStack() = 0 /* overload */;
	virtual void __cdecl popBackStack(Androidapi::Jni::Javatypes::_di_JString name, int flags) = 0 /* overload */;
	virtual void __cdecl popBackStack(int id, int flags) = 0 /* overload */;
	virtual bool __cdecl popBackStackImmediate() = 0 /* overload */;
	virtual bool __cdecl popBackStackImmediate(Androidapi::Jni::Javatypes::_di_JString name, int flags) = 0 /* overload */;
	virtual bool __cdecl popBackStackImmediate(int id, int flags) = 0 /* overload */;
	virtual void __cdecl putFragment(Androidapi::Jni::Os::_di_JBundle bundle, Androidapi::Jni::Javatypes::_di_JString key, _di_Japp_Fragment fragment) = 0 ;
	virtual void __cdecl registerFragmentLifecycleCallbacks(_di_Japp_FragmentManager_FragmentLifecycleCallbacks cb, bool recursive) = 0 ;
	virtual void __cdecl removeOnBackStackChangedListener(_di_Japp_FragmentManager_OnBackStackChangedListener listener) = 0 ;
	virtual _di_Japp_Fragment_SavedState __cdecl saveFragmentInstanceState(_di_Japp_Fragment f) = 0 ;
	virtual void __cdecl unregisterFragmentLifecycleCallbacks(_di_Japp_FragmentManager_FragmentLifecycleCallbacks cb) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_FragmentManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManagerClass,_di_Japp_FragmentManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManagerClass,_di_Japp_FragmentManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_FragmentManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManagerClass,_di_Japp_FragmentManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_FragmentManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DEF82AEE-4F42-417B-81E1-14471A8BA6AE}") Japp_FragmentManager_BackStackEntryClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{9DCCFF9D-2628-433C-A071-212F3C1DE5FA}") Japp_FragmentManager_BackStackEntry  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getBreadCrumbShortTitle() = 0 ;
	virtual int __cdecl getBreadCrumbShortTitleRes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getBreadCrumbTitle() = 0 ;
	virtual int __cdecl getBreadCrumbTitleRes() = 0 ;
	virtual int __cdecl getId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_FragmentManager_BackStackEntry : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManager_BackStackEntryClass,_di_Japp_FragmentManager_BackStackEntry>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManager_BackStackEntryClass,_di_Japp_FragmentManager_BackStackEntry> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_FragmentManager_BackStackEntry() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManager_BackStackEntryClass,_di_Japp_FragmentManager_BackStackEntry>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_FragmentManager_BackStackEntry() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8DF03887-3AE5-47C0-A97B-2EF9B7869B20}") Japp_FragmentManager_FragmentLifecycleCallbacksClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_Japp_FragmentManager_FragmentLifecycleCallbacks __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{735F708B-427C-4C89-B5AD-536DDC38ED1A}") Japp_FragmentManager_FragmentLifecycleCallbacks  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onFragmentActivityCreated(_di_Japp_FragmentManager fm, _di_Japp_Fragment f, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onFragmentAttached(_di_Japp_FragmentManager fm, _di_Japp_Fragment f, Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual void __cdecl onFragmentCreated(_di_Japp_FragmentManager fm, _di_Japp_Fragment f, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onFragmentDestroyed(_di_Japp_FragmentManager fm, _di_Japp_Fragment f) = 0 ;
	virtual void __cdecl onFragmentDetached(_di_Japp_FragmentManager fm, _di_Japp_Fragment f) = 0 ;
	virtual void __cdecl onFragmentPaused(_di_Japp_FragmentManager fm, _di_Japp_Fragment f) = 0 ;
	virtual void __cdecl onFragmentPreAttached(_di_Japp_FragmentManager fm, _di_Japp_Fragment f, Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual void __cdecl onFragmentPreCreated(_di_Japp_FragmentManager fm, _di_Japp_Fragment f, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onFragmentResumed(_di_Japp_FragmentManager fm, _di_Japp_Fragment f) = 0 ;
	virtual void __cdecl onFragmentSaveInstanceState(_di_Japp_FragmentManager fm, _di_Japp_Fragment f, Androidapi::Jni::Os::_di_JBundle outState) = 0 ;
	virtual void __cdecl onFragmentStarted(_di_Japp_FragmentManager fm, _di_Japp_Fragment f) = 0 ;
	virtual void __cdecl onFragmentStopped(_di_Japp_FragmentManager fm, _di_Japp_Fragment f) = 0 ;
	virtual void __cdecl onFragmentViewCreated(_di_Japp_FragmentManager fm, _di_Japp_Fragment f, Androidapi::Jni::Graphicscontentviewtext::_di_JView v, Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onFragmentViewDestroyed(_di_Japp_FragmentManager fm, _di_Japp_Fragment f) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_FragmentManager_FragmentLifecycleCallbacks : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManager_FragmentLifecycleCallbacksClass,_di_Japp_FragmentManager_FragmentLifecycleCallbacks>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManager_FragmentLifecycleCallbacksClass,_di_Japp_FragmentManager_FragmentLifecycleCallbacks> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_FragmentManager_FragmentLifecycleCallbacks() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManager_FragmentLifecycleCallbacksClass,_di_Japp_FragmentManager_FragmentLifecycleCallbacks>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_FragmentManager_FragmentLifecycleCallbacks() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F60DD80B-2570-4ED5-A16C-E7EAC6B63F30}") Japp_FragmentManager_OnBackStackChangedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{63207AFF-576A-40BA-A51B-4A7C17CC1D45}") Japp_FragmentManager_OnBackStackChangedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onBackStackChanged() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_FragmentManager_OnBackStackChangedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManager_OnBackStackChangedListenerClass,_di_Japp_FragmentManager_OnBackStackChangedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManager_OnBackStackChangedListenerClass,_di_Japp_FragmentManager_OnBackStackChangedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_FragmentManager_OnBackStackChangedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentManager_OnBackStackChangedListenerClass,_di_Japp_FragmentManager_OnBackStackChangedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_FragmentManager_OnBackStackChangedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ACA4981E-8459-4155-BF06-5D19957B6BE7}") Japp_FragmentTransactionClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetTRANSIT_ENTER_MASK() = 0 ;
	virtual int __cdecl _GetTRANSIT_EXIT_MASK() = 0 ;
	virtual int __cdecl _GetTRANSIT_FRAGMENT_CLOSE() = 0 ;
	virtual int __cdecl _GetTRANSIT_FRAGMENT_FADE() = 0 ;
	virtual int __cdecl _GetTRANSIT_FRAGMENT_OPEN() = 0 ;
	virtual int __cdecl _GetTRANSIT_NONE() = 0 ;
	virtual int __cdecl _GetTRANSIT_UNSET() = 0 ;
	HIDESBASE virtual _di_Japp_FragmentTransaction __cdecl init() = 0 ;
	__property int TRANSIT_ENTER_MASK = {read=_GetTRANSIT_ENTER_MASK};
	__property int TRANSIT_EXIT_MASK = {read=_GetTRANSIT_EXIT_MASK};
	__property int TRANSIT_FRAGMENT_CLOSE = {read=_GetTRANSIT_FRAGMENT_CLOSE};
	__property int TRANSIT_FRAGMENT_FADE = {read=_GetTRANSIT_FRAGMENT_FADE};
	__property int TRANSIT_FRAGMENT_OPEN = {read=_GetTRANSIT_FRAGMENT_OPEN};
	__property int TRANSIT_NONE = {read=_GetTRANSIT_NONE};
	__property int TRANSIT_UNSET = {read=_GetTRANSIT_UNSET};
};

__interface  INTERFACE_UUID("{9B1E0684-DC82-4C71-BC05-56C51FF65DD3}") Japp_FragmentTransaction  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_Japp_FragmentTransaction __cdecl add(_di_Japp_Fragment fragment, Androidapi::Jni::Javatypes::_di_JString tag) = 0 /* overload */;
	virtual _di_Japp_FragmentTransaction __cdecl add(int containerViewId, _di_Japp_Fragment fragment) = 0 /* overload */;
	virtual _di_Japp_FragmentTransaction __cdecl add(int containerViewId, _di_Japp_Fragment fragment, Androidapi::Jni::Javatypes::_di_JString tag) = 0 /* overload */;
	virtual _di_Japp_FragmentTransaction __cdecl addSharedElement(Androidapi::Jni::Graphicscontentviewtext::_di_JView sharedElement, Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl addToBackStack(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl attach(_di_Japp_Fragment fragment) = 0 ;
	virtual int __cdecl commit() = 0 ;
	virtual int __cdecl commitAllowingStateLoss() = 0 ;
	virtual void __cdecl commitNow() = 0 ;
	virtual void __cdecl commitNowAllowingStateLoss() = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl detach(_di_Japp_Fragment fragment) = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl disallowAddToBackStack() = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl hide(_di_Japp_Fragment fragment) = 0 ;
	virtual bool __cdecl isAddToBackStackAllowed() = 0 ;
	virtual bool __cdecl isEmpty() = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl remove(_di_Japp_Fragment fragment) = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl replace(int containerViewId, _di_Japp_Fragment fragment) = 0 /* overload */;
	virtual _di_Japp_FragmentTransaction __cdecl replace(int containerViewId, _di_Japp_Fragment fragment, Androidapi::Jni::Javatypes::_di_JString tag) = 0 /* overload */;
	virtual _di_Japp_FragmentTransaction __cdecl runOnCommit(Androidapi::Jni::Javatypes::_di_JRunnable runnable) = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl setAllowOptimization(bool allowOptimization) = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl setBreadCrumbShortTitle(int res) = 0 /* overload */;
	virtual _di_Japp_FragmentTransaction __cdecl setBreadCrumbShortTitle(Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 /* overload */;
	virtual _di_Japp_FragmentTransaction __cdecl setBreadCrumbTitle(int res) = 0 /* overload */;
	virtual _di_Japp_FragmentTransaction __cdecl setBreadCrumbTitle(Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 /* overload */;
	virtual _di_Japp_FragmentTransaction __cdecl setCustomAnimations(int enter, int exit) = 0 /* overload */;
	virtual _di_Japp_FragmentTransaction __cdecl setCustomAnimations(int enter, int exit, int popEnter, int popExit) = 0 /* overload */;
	virtual _di_Japp_FragmentTransaction __cdecl setPrimaryNavigationFragment(_di_Japp_Fragment fragment) = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl setReorderingAllowed(bool reorderingAllowed) = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl setTransition(int transit) = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl setTransitionStyle(int styleRes) = 0 ;
	virtual _di_Japp_FragmentTransaction __cdecl show(_di_Japp_Fragment fragment) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_FragmentTransaction : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentTransactionClass,_di_Japp_FragmentTransaction>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentTransactionClass,_di_Japp_FragmentTransaction> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_FragmentTransaction() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_FragmentTransactionClass,_di_Japp_FragmentTransaction>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_FragmentTransaction() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FE42203A-1313-4AED-98A7-973CD56FB4A9}") JJobIntentServiceClass  : public Androidapi::Jni::App::JServiceClass 
{
	HIDESBASE virtual _di_JJobIntentService __cdecl init() = 0 ;
	virtual void __cdecl enqueueWork(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_Jlang_Class cls, int jobId, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent work) = 0 ;
};

__interface  INTERFACE_UUID("{5DA74544-B80C-4832-8171-25E7FC726C4E}") JJobIntentService  : public Androidapi::Jni::App::JService 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	HIDESBASE virtual void __cdecl onCreate() = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
	HIDESBASE virtual int __cdecl onStartCommand(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, int flags, int startId) = 0 ;
	virtual bool __cdecl onStopCurrentWork() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJJobIntentService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJobIntentServiceClass,_di_JJobIntentService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJobIntentServiceClass,_di_JJobIntentService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJJobIntentService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JJobIntentServiceClass,_di_JJobIntentService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJJobIntentService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{479A03D5-D5F3-4084-A8EC-241CEA0F0AFB}") Japp_LoaderManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_Japp_LoaderManager __cdecl init() = 0 ;
	virtual void __cdecl enableDebugLogging(bool enabled) = 0 ;
};

__interface  INTERFACE_UUID("{E13F6C45-41F3-4A16-9B2D-6C3BFF45FDE5}") Japp_LoaderManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl destroyLoader(int id) = 0 ;
	virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JString prefix, Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jni::Javatypes::_di_JPrintWriter writer, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual _di_Jcontent_Loader __cdecl getLoader(int id) = 0 ;
	virtual bool __cdecl hasRunningLoaders() = 0 ;
	virtual _di_Jcontent_Loader __cdecl initLoader(int id, Androidapi::Jni::Os::_di_JBundle args, _di_Japp_LoaderManager_LoaderCallbacks callback) = 0 ;
	virtual _di_Jcontent_Loader __cdecl restartLoader(int id, Androidapi::Jni::Os::_di_JBundle args, _di_Japp_LoaderManager_LoaderCallbacks callback) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_LoaderManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_LoaderManagerClass,_di_Japp_LoaderManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_LoaderManagerClass,_di_Japp_LoaderManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_LoaderManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_LoaderManagerClass,_di_Japp_LoaderManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_LoaderManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{49F864F7-F0C4-4990-AE14-1B20E356F92C}") Japp_LoaderManager_LoaderCallbacksClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{FD34E913-C4A1-4D1D-B6B8-421D9C3D9770}") Japp_LoaderManager_LoaderCallbacks  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual _di_Jcontent_Loader __cdecl onCreateLoader(int id, Androidapi::Jni::Os::_di_JBundle args) = 0 ;
	virtual void __cdecl onLoadFinished(_di_Jcontent_Loader loader, Androidapi::Jni::Javatypes::_di_JObject data) = 0 ;
	virtual void __cdecl onLoaderReset(_di_Jcontent_Loader loader) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_LoaderManager_LoaderCallbacks : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_LoaderManager_LoaderCallbacksClass,_di_Japp_LoaderManager_LoaderCallbacks>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_LoaderManager_LoaderCallbacksClass,_di_Japp_LoaderManager_LoaderCallbacks> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_LoaderManager_LoaderCallbacks() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_LoaderManager_LoaderCallbacksClass,_di_Japp_LoaderManager_LoaderCallbacks>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_LoaderManager_LoaderCallbacks() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9A2975B1-7BCA-4120-BAE9-A99F23F48159}") JNotificationCompat_ActionClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JNotificationCompat_Action __cdecl init(int icon, Androidapi::Jni::Javatypes::_di_JCharSequence title, Androidapi::Jni::App::_di_JPendingIntent intent) = 0 ;
};

__interface  INTERFACE_UUID("{2C05FC19-2838-47F8-97B0-44836566B08D}") JNotificationCompat_Action  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::App::_di_JPendingIntent __cdecl _GetactionIntent() = 0 ;
	virtual void __cdecl _SetactionIntent(Androidapi::Jni::App::_di_JPendingIntent Value) = 0 ;
	virtual int __cdecl _Geticon() = 0 ;
	virtual void __cdecl _Seticon(int Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl _Gettitle() = 0 ;
	virtual void __cdecl _Settitle(Androidapi::Jni::Javatypes::_di_JCharSequence Value) = 0 ;
	virtual Androidapi::Jni::App::_di_JPendingIntent __cdecl getActionIntent() = 0 ;
	virtual bool __cdecl getAllowGeneratedReplies() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_Japp_RemoteInput>* __cdecl getDataOnlyRemoteInputs() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getExtras() = 0 ;
	virtual int __cdecl getIcon() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_Japp_RemoteInput>* __cdecl getRemoteInputs() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getTitle() = 0 ;
	__property Androidapi::Jni::App::_di_JPendingIntent actionIntent = {read=_GetactionIntent, write=_SetactionIntent};
	__property int icon = {read=_Geticon, write=_Seticon};
	__property Androidapi::Jni::Javatypes::_di_JCharSequence title = {read=_Gettitle, write=_Settitle};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotificationCompat_Action : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_ActionClass,_di_JNotificationCompat_Action>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_ActionClass,_di_JNotificationCompat_Action> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotificationCompat_Action() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_ActionClass,_di_JNotificationCompat_Action>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotificationCompat_Action() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6EC74C2C-EBCC-4A55-98B6-6DD36DE3BA8C}") JNotificationCompat_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JNotificationCompat_Builder __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString channelId) = 0 /* overload */;
	HIDESBASE virtual _di_JNotificationCompat_Builder __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{7DE9C385-1C34-413C-9E85-D8FA90028065}") JNotificationCompat_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JArrayList __cdecl _GetmPeople() = 0 ;
	virtual void __cdecl _SetmPeople(Androidapi::Jni::Javatypes::_di_JArrayList Value) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl addAction(int icon, Androidapi::Jni::Javatypes::_di_JCharSequence title, Androidapi::Jni::App::_di_JPendingIntent intent) = 0 /* overload */;
	virtual _di_JNotificationCompat_Builder __cdecl addAction(_di_JNotificationCompat_Action action) = 0 /* overload */;
	virtual _di_JNotificationCompat_Builder __cdecl addExtras(Androidapi::Jni::Os::_di_JBundle extras) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl addPerson(Androidapi::Jni::Javatypes::_di_JString uri) = 0 ;
	virtual Androidapi::Jni::App::_di_JNotification __cdecl build() = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl extend(_di_JNotificationCompat_Extender extender) = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getExtras() = 0 ;
	virtual Androidapi::Jni::App::_di_JNotification __cdecl getNotification() = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setAutoCancel(bool autoCancel) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setBadgeIconType(int icon) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setCategory(Androidapi::Jni::Javatypes::_di_JString category) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setChannel(Androidapi::Jni::Javatypes::_di_JString channelId) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setChannelId(Androidapi::Jni::Javatypes::_di_JString channelId) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setColor(int argb) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setColorized(bool colorize) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setContent(Androidapi::Jni::Widget::_di_JRemoteViews views) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setContentInfo(Androidapi::Jni::Javatypes::_di_JCharSequence info) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setContentIntent(Androidapi::Jni::App::_di_JPendingIntent intent) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setContentText(Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setContentTitle(Androidapi::Jni::Javatypes::_di_JCharSequence title) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setCustomBigContentView(Androidapi::Jni::Widget::_di_JRemoteViews contentView) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setCustomContentView(Androidapi::Jni::Widget::_di_JRemoteViews contentView) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setCustomHeadsUpContentView(Androidapi::Jni::Widget::_di_JRemoteViews contentView) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setDefaults(int defaults) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setDeleteIntent(Androidapi::Jni::App::_di_JPendingIntent intent) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setExtras(Androidapi::Jni::Os::_di_JBundle extras) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setFullScreenIntent(Androidapi::Jni::App::_di_JPendingIntent intent, bool highPriority) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setGroup(Androidapi::Jni::Javatypes::_di_JString groupKey) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setGroupAlertBehavior(int groupAlertBehavior) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setGroupSummary(bool isGroupSummary) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setLargeIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap icon) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setLights(int argb, int onMs, int offMs) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setLocalOnly(bool b) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setNumber(int number) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setOngoing(bool ongoing) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setOnlyAlertOnce(bool onlyAlertOnce) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setPriority(int pri) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setProgress(int max, int progress, bool indeterminate) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setPublicVersion(Androidapi::Jni::App::_di_JNotification n) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setRemoteInputHistory(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JCharSequence>* text) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setShortcutId(Androidapi::Jni::Javatypes::_di_JString shortcutId) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setShowWhen(bool show) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setSmallIcon(int icon) = 0 /* overload */;
	virtual _di_JNotificationCompat_Builder __cdecl setSmallIcon(int icon, int level) = 0 /* overload */;
	virtual _di_JNotificationCompat_Builder __cdecl setSortKey(Androidapi::Jni::Javatypes::_di_JString sortKey) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setSound(Androidapi::Jni::Net::_di_Jnet_Uri sound) = 0 /* overload */;
	virtual _di_JNotificationCompat_Builder __cdecl setSound(Androidapi::Jni::Net::_di_Jnet_Uri sound, int streamType) = 0 /* overload */;
	virtual _di_JNotificationCompat_Builder __cdecl setStyle(_di_JNotificationCompat_Style style) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setSubText(Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setTicker(Androidapi::Jni::Javatypes::_di_JCharSequence tickerText) = 0 /* overload */;
	virtual _di_JNotificationCompat_Builder __cdecl setTicker(Androidapi::Jni::Javatypes::_di_JCharSequence tickerText, Androidapi::Jni::Widget::_di_JRemoteViews views) = 0 /* overload */;
	virtual _di_JNotificationCompat_Builder __cdecl setTimeout(__int64 durationMs) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setTimeoutAfter(__int64 durationMs) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setUsesChronometer(bool b) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setVibrate(Androidapi::Jnibridge::TJavaArray__1<__int64>* pattern) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setVisibility(int visibility) = 0 ;
	virtual _di_JNotificationCompat_Builder __cdecl setWhen(__int64 when) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JArrayList mPeople = {read=_GetmPeople, write=_SetmPeople};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotificationCompat_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_BuilderClass,_di_JNotificationCompat_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_BuilderClass,_di_JNotificationCompat_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotificationCompat_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_BuilderClass,_di_JNotificationCompat_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotificationCompat_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FE44EF36-1DB6-47B7-AA66-5F91FE5134C5}") JNotificationCompat_ExtenderClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C96F5828-B7E4-48EC-9A8C-8B8518A347BB}") JNotificationCompat_Extender  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual _di_JNotificationCompat_Builder __cdecl extend(_di_JNotificationCompat_Builder builder) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotificationCompat_Extender : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_ExtenderClass,_di_JNotificationCompat_Extender>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_ExtenderClass,_di_JNotificationCompat_Extender> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotificationCompat_Extender() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_ExtenderClass,_di_JNotificationCompat_Extender>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotificationCompat_Extender() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A76478B0-8BCB-4AFA-AFCD-CB0460219CDA}") JNotificationCompat_StyleClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JNotificationCompat_Style __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{5C782C73-8C4B-4ADA-994D-4293E0D2D282}") JNotificationCompat_Style  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::App::_di_JNotification __cdecl build() = 0 ;
	virtual void __cdecl setBuilder(_di_JNotificationCompat_Builder builder) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotificationCompat_Style : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_StyleClass,_di_JNotificationCompat_Style>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_StyleClass,_di_JNotificationCompat_Style> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotificationCompat_Style() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationCompat_StyleClass,_di_JNotificationCompat_Style>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotificationCompat_Style() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2D5C5EF8-294E-4B0F-A648-9D1EA5BED891}") Japp_RemoteInputClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_RESULTS_DATA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRESULTS_CLIP_LABEL() = 0 ;
	virtual void __cdecl addDataResultToIntent(_di_Japp_RemoteInput remoteInput, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Javatypes::_di_JMap results) = 0 ;
	virtual void __cdecl addResultsToIntent(Androidapi::Jnibridge::TJavaObjectArray__1<_di_Japp_RemoteInput>* remoteInputs, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Os::_di_JBundle results) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl getDataResultsFromIntent(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Javatypes::_di_JString remoteInputResultKey) = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getResultsFromIntent(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_RESULTS_DATA = {read=_GetEXTRA_RESULTS_DATA};
	__property Androidapi::Jni::Javatypes::_di_JString RESULTS_CLIP_LABEL = {read=_GetRESULTS_CLIP_LABEL};
};

__interface  INTERFACE_UUID("{728FBA2D-C0B9-45AC-A5DD-24B89188687E}") Japp_RemoteInput  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl getAllowFreeFormInput() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSet __cdecl getAllowedDataTypes() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JCharSequence>* __cdecl getChoices() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getExtras() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getLabel() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getResultKey() = 0 ;
	virtual bool __cdecl isDataOnly() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_RemoteInput : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_RemoteInputClass,_di_Japp_RemoteInput>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_RemoteInputClass,_di_Japp_RemoteInput> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_RemoteInput() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_RemoteInputClass,_di_Japp_RemoteInput>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_RemoteInput() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4E37BD6A-6494-425B-9528-DD56C6E4EB12}") Japp_SharedElementCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_Japp_SharedElementCallback __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{BA8B8350-C929-499D-8B13-5E7FDBD6AF92}") Japp_SharedElementCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Os::_di_JParcelable __cdecl onCaptureSharedElementSnapshot(Androidapi::Jni::Graphicscontentviewtext::_di_JView sharedElement, Androidapi::Jni::Graphicscontentviewtext::_di_JMatrix viewToGlobalMatrix, Androidapi::Jni::Graphicscontentviewtext::_di_JRectF screenBounds) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl onCreateSnapshotView(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Os::_di_JParcelable snapshot) = 0 ;
	virtual void __cdecl onMapSharedElements(Androidapi::Jni::Javatypes::_di_JList names, Androidapi::Jni::Javatypes::_di_JMap sharedElements) = 0 ;
	virtual void __cdecl onRejectSharedElements(Androidapi::Jni::Javatypes::_di_JList rejectedSharedElements) = 0 ;
	virtual void __cdecl onSharedElementEnd(Androidapi::Jni::Javatypes::_di_JList sharedElementNames, Androidapi::Jni::Javatypes::_di_JList sharedElements, Androidapi::Jni::Javatypes::_di_JList sharedElementSnapshots) = 0 ;
	virtual void __cdecl onSharedElementStart(Androidapi::Jni::Javatypes::_di_JList sharedElementNames, Androidapi::Jni::Javatypes::_di_JList sharedElements, Androidapi::Jni::Javatypes::_di_JList sharedElementSnapshots) = 0 ;
	virtual void __cdecl onSharedElementsArrived(Androidapi::Jni::Javatypes::_di_JList sharedElementNames, Androidapi::Jni::Javatypes::_di_JList sharedElements, _di_Japp_SharedElementCallback_OnSharedElementsReadyListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_SharedElementCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_SharedElementCallbackClass,_di_Japp_SharedElementCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_SharedElementCallbackClass,_di_Japp_SharedElementCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_SharedElementCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_SharedElementCallbackClass,_di_Japp_SharedElementCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_SharedElementCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5AB9395E-A8B1-4932-A92B-4BD7AEF39E11}") Japp_SharedElementCallback_OnSharedElementsReadyListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{89CD4036-B7EA-43B6-97E9-259FE977C0C4}") Japp_SharedElementCallback_OnSharedElementsReadyListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onSharedElementsReady() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJapp_SharedElementCallback_OnSharedElementsReadyListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_SharedElementCallback_OnSharedElementsReadyListenerClass,_di_Japp_SharedElementCallback_OnSharedElementsReadyListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_SharedElementCallback_OnSharedElementsReadyListenerClass,_di_Japp_SharedElementCallback_OnSharedElementsReadyListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJapp_SharedElementCallback_OnSharedElementsReadyListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Japp_SharedElementCallback_OnSharedElementsReadyListenerClass,_di_Japp_SharedElementCallback_OnSharedElementsReadyListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJapp_SharedElementCallback_OnSharedElementsReadyListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{33A87969-5731-4791-90F6-3AD22F2BB822}") JFileProviderClass  : public Androidapi::Jni::Graphicscontentviewtext::JContentProviderClass 
{
	HIDESBASE virtual _di_JFileProvider __cdecl init() = 0 ;
	virtual Androidapi::Jni::Net::_di_Jnet_Uri __cdecl getUriForFile(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString authority, Androidapi::Jni::Javatypes::_di_JFile file_) = 0 ;
};

__interface  INTERFACE_UUID("{12F5DD38-A3CE-4D2E-9F68-24933C9D221B}") JFileProvider  : public Androidapi::Jni::Graphicscontentviewtext::JContentProvider 
{
	HIDESBASE virtual void __cdecl attachInfo(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JProviderInfo info) = 0 ;
	HIDESBASE virtual int __cdecl Delete(Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jni::Javatypes::_di_JString selection, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* selectionArgs) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getType(Androidapi::Jni::Net::_di_Jnet_Uri uri) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Net::_di_Jnet_Uri __cdecl insert(Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jni::Graphicscontentviewtext::_di_JContentValues values) = 0 ;
	HIDESBASE virtual bool __cdecl onCreate() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Os::_di_JParcelFileDescriptor __cdecl openFile(Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jni::Javatypes::_di_JString mode) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JCursor __cdecl query(Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* projection, Androidapi::Jni::Javatypes::_di_JString selection, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* selectionArgs, Androidapi::Jni::Javatypes::_di_JString sortOrder) = 0 ;
	HIDESBASE virtual int __cdecl update(Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jni::Graphicscontentviewtext::_di_JContentValues values, Androidapi::Jni::Javatypes::_di_JString selection, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* selectionArgs) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFileProvider : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFileProviderClass,_di_JFileProvider>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFileProviderClass,_di_JFileProvider> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFileProvider() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFileProviderClass,_di_JFileProvider>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFileProvider() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{75230956-00B9-43CD-8C60-ADA295F7E7F3}") Jcontent_LoaderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_Jcontent_Loader __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

__interface  INTERFACE_UUID("{B43C247C-8BDF-497A-BAC1-1E900F51A47D}") Jcontent_Loader  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl abandon() = 0 ;
	virtual bool __cdecl cancelLoad() = 0 ;
	virtual void __cdecl commitContentChanged() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl dataToString(Androidapi::Jni::Javatypes::_di_JObject data) = 0 ;
	virtual void __cdecl deliverCancellation() = 0 ;
	virtual void __cdecl deliverResult(Androidapi::Jni::Javatypes::_di_JObject data) = 0 ;
	virtual void __cdecl dump(Androidapi::Jni::Javatypes::_di_JString prefix, Androidapi::Jni::Javatypes::_di_JFileDescriptor fd, Androidapi::Jni::Javatypes::_di_JPrintWriter writer, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* args) = 0 ;
	virtual void __cdecl forceLoad() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JContext __cdecl getContext() = 0 ;
	virtual int __cdecl getId() = 0 ;
	virtual bool __cdecl isAbandoned() = 0 ;
	virtual bool __cdecl isReset() = 0 ;
	virtual bool __cdecl isStarted() = 0 ;
	virtual void __cdecl onContentChanged() = 0 ;
	virtual void __cdecl registerListener(int id, _di_Jcontent_Loader_OnLoadCompleteListener listener) = 0 ;
	virtual void __cdecl registerOnLoadCanceledListener(_di_Jcontent_Loader_OnLoadCanceledListener listener) = 0 ;
	virtual void __cdecl reset() = 0 ;
	virtual void __cdecl rollbackContentChanged() = 0 ;
	virtual void __cdecl startLoading() = 0 ;
	virtual void __cdecl stopLoading() = 0 ;
	virtual bool __cdecl takeContentChanged() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl unregisterListener(_di_Jcontent_Loader_OnLoadCompleteListener listener) = 0 ;
	virtual void __cdecl unregisterOnLoadCanceledListener(_di_Jcontent_Loader_OnLoadCanceledListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJcontent_Loader : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jcontent_LoaderClass,_di_Jcontent_Loader>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jcontent_LoaderClass,_di_Jcontent_Loader> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJcontent_Loader() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jcontent_LoaderClass,_di_Jcontent_Loader>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJcontent_Loader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A92A64DD-99A8-4582-9291-38BB8CDF7500}") Jcontent_Loader_OnLoadCanceledListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{6B2BDFD1-1384-46BF-B895-0B8EF000D0ED}") Jcontent_Loader_OnLoadCanceledListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onLoadCanceled(_di_Jcontent_Loader loader) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJcontent_Loader_OnLoadCanceledListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jcontent_Loader_OnLoadCanceledListenerClass,_di_Jcontent_Loader_OnLoadCanceledListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jcontent_Loader_OnLoadCanceledListenerClass,_di_Jcontent_Loader_OnLoadCanceledListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJcontent_Loader_OnLoadCanceledListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jcontent_Loader_OnLoadCanceledListenerClass,_di_Jcontent_Loader_OnLoadCanceledListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJcontent_Loader_OnLoadCanceledListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AD54E07C-4FD0-4274-9A2D-A17F9D57FF5C}") Jcontent_Loader_OnLoadCompleteListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C9E1065D-CEC5-4C51-BBFB-CEE633EADB45}") Jcontent_Loader_OnLoadCompleteListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onLoadComplete(_di_Jcontent_Loader loader, Androidapi::Jni::Javatypes::_di_JObject data) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJcontent_Loader_OnLoadCompleteListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jcontent_Loader_OnLoadCompleteListenerClass,_di_Jcontent_Loader_OnLoadCompleteListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jcontent_Loader_OnLoadCompleteListenerClass,_di_Jcontent_Loader_OnLoadCompleteListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJcontent_Loader_OnLoadCompleteListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jcontent_Loader_OnLoadCompleteListenerClass,_di_Jcontent_Loader_OnLoadCompleteListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJcontent_Loader_OnLoadCompleteListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A1030BEA-760D-43D3-B303-1107F333DE59}") JPermissionCheckerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetPERMISSION_DENIED() = 0 ;
	virtual int __cdecl _GetPERMISSION_DENIED_APP_OP() = 0 ;
	virtual int __cdecl _GetPERMISSION_GRANTED() = 0 ;
	virtual int __cdecl checkCallingOrSelfPermission(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString permission) = 0 ;
	virtual int __cdecl checkCallingPermission(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString permission, Androidapi::Jni::Javatypes::_di_JString packageName) = 0 ;
	virtual int __cdecl checkPermission(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString permission, int pid, int uid, Androidapi::Jni::Javatypes::_di_JString packageName) = 0 ;
	virtual int __cdecl checkSelfPermission(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString permission) = 0 ;
	__property int PERMISSION_DENIED = {read=_GetPERMISSION_DENIED};
	__property int PERMISSION_DENIED_APP_OP = {read=_GetPERMISSION_DENIED_APP_OP};
	__property int PERMISSION_GRANTED = {read=_GetPERMISSION_GRANTED};
};

__interface  INTERFACE_UUID("{153463C8-6544-4775-8641-B5E90044A3D9}") JPermissionChecker  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPermissionChecker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPermissionCheckerClass,_di_JPermissionChecker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPermissionCheckerClass,_di_JPermissionChecker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPermissionChecker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPermissionCheckerClass,_di_JPermissionChecker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPermissionChecker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DECFDD83-E88E-449A-8198-F539F905B2A8}") JWakefulBroadcastReceiverClass  : public Androidapi::Jni::Graphicscontentviewtext::JBroadcastReceiverClass 
{
	HIDESBASE virtual _di_JWakefulBroadcastReceiver __cdecl init() = 0 ;
	virtual bool __cdecl completeWakefulIntent(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName __cdecl startWakefulService(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
};

__interface  INTERFACE_UUID("{2B7CD6F2-EB86-4F3C-9BB7-804797C60B05}") JWakefulBroadcastReceiver  : public Androidapi::Jni::Graphicscontentviewtext::JBroadcastReceiver 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWakefulBroadcastReceiver : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWakefulBroadcastReceiverClass,_di_JWakefulBroadcastReceiver>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWakefulBroadcastReceiverClass,_di_JWakefulBroadcastReceiver> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWakefulBroadcastReceiver() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWakefulBroadcastReceiverClass,_di_JWakefulBroadcastReceiver>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWakefulBroadcastReceiver() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4B7521B6-AD61-46FE-9921-4DF794FD5913}") JWindowInsetsCompatClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JWindowInsetsCompat __cdecl init(_di_JWindowInsetsCompat src) = 0 ;
};

__interface  INTERFACE_UUID("{E7655533-41AA-41E5-A2EF-3BA60A800EB7}") JWindowInsetsCompat  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JWindowInsetsCompat __cdecl consumeStableInsets() = 0 ;
	virtual _di_JWindowInsetsCompat __cdecl consumeSystemWindowInsets() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual int __cdecl getStableInsetBottom() = 0 ;
	virtual int __cdecl getStableInsetLeft() = 0 ;
	virtual int __cdecl getStableInsetRight() = 0 ;
	virtual int __cdecl getStableInsetTop() = 0 ;
	virtual int __cdecl getSystemWindowInsetBottom() = 0 ;
	virtual int __cdecl getSystemWindowInsetLeft() = 0 ;
	virtual int __cdecl getSystemWindowInsetRight() = 0 ;
	virtual int __cdecl getSystemWindowInsetTop() = 0 ;
	virtual bool __cdecl hasInsets() = 0 ;
	virtual bool __cdecl hasStableInsets() = 0 ;
	virtual bool __cdecl hasSystemWindowInsets() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isConsumed() = 0 ;
	virtual bool __cdecl isRound() = 0 ;
	virtual _di_JWindowInsetsCompat __cdecl replaceSystemWindowInsets(int left, int top, int right, int bottom) = 0 /* overload */;
	virtual _di_JWindowInsetsCompat __cdecl replaceSystemWindowInsets(Androidapi::Jni::Graphicscontentviewtext::_di_JRect systemWindowInsets) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJWindowInsetsCompat : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWindowInsetsCompatClass,_di_JWindowInsetsCompat>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWindowInsetsCompatClass,_di_JWindowInsetsCompat> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJWindowInsetsCompat() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JWindowInsetsCompatClass,_di_JWindowInsetsCompat>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJWindowInsetsCompat() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Support */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_SUPPORT)
using namespace Androidapi::Jni::Support;
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
#endif	// Androidapi_Jni_SupportHPP
