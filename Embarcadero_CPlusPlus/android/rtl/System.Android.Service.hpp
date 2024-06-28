// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Android.Service.pas' rev: 34.00 (Android)

#ifndef System_Android_ServiceHPP
#define System_Android_ServiceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.JNI.Support.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Embarcadero.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Android
{
namespace Service
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidBaseService;
class DELPHICLASS TAndroidService;
class DELPHICLASS TAndroidIntentService;
class DELPHICLASS TServiceCallbacks;
class DELPHICLASS TLocalServiceConnection;
class DELPHICLASS TRemoteServiceConnection;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TOnCreateEvent)(System::TObject* const Sender);

typedef void __fastcall (__closure *TOnDestroyEvent)(System::TObject* const Sender);

typedef int __fastcall (__closure *TOnStartCommandEvent)(System::TObject* const Sender, const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent Intent, int Flags, int StartId);

typedef Androidapi::Jni::Os::_di_JIBinder __fastcall (__closure *TOnBindEvent)(System::TObject* const Sender, const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);

typedef bool __fastcall (__closure *TOnUnBindEvent)(System::TObject* const Sender, const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);

typedef void __fastcall (__closure *TOnRebindEvent)(System::TObject* const Sender, const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);

typedef void __fastcall (__closure *TOnTaskRemovedEvent)(System::TObject* const Sender, const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent ARootIntent);

typedef void __fastcall (__closure *TOnConfigurationChangedEvent)(System::TObject* const Sender, const Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration NewConfig);

typedef void __fastcall (__closure *TOnLowMemoryEvent)(System::TObject* const Sender);

typedef void __fastcall (__closure *TOnTrimMemoryEvent)(System::TObject* const Sender, int Level);

typedef void __fastcall (__closure *TOnHandleIntent)(System::TObject* const Sender, const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);

typedef bool __fastcall (__closure *TOnHandleMessage)(System::TObject* const Sender, const Androidapi::Jni::Os::_di_JMessage AMessage);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidBaseService : public System::Classes::TDataModule
{
	typedef System::Classes::TDataModule inherited;
	
private:
	Androidapi::Jni::App::_di_JService FJavaService;
	Androidapi::Jni::Support::_di_JJobIntentService FJavaJobIntentService;
	TOnBindEvent FOnBind;
	TOnUnBindEvent FOnUnBind;
	TOnTrimMemoryEvent FOnTrimMemory;
	TOnTaskRemovedEvent FOnTaskRemoved;
	TOnConfigurationChangedEvent FOnConfigurationChanged;
	TOnLowMemoryEvent FOnLowMemory;
	TOnRebindEvent FOnRebind;
	TOnHandleMessage FOnHandleMessage;
	
protected:
	virtual void __fastcall DoCreate();
	virtual Androidapi::Jni::Os::_di_JIBinder __fastcall DoBind(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);
	virtual bool __fastcall DoUnBind(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);
	virtual void __fastcall DoRebind(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);
	virtual void __fastcall DoTaskRemoved(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent ARootIntent);
	virtual void __fastcall DoConfigurationChanged(const Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration NewConfig);
	virtual void __fastcall DoLowMemory();
	virtual void __fastcall DoTrimMemory(int Level);
	virtual bool __fastcall DoHandleMessage(const Androidapi::Jni::Os::_di_JMessage AMessage);
	
public:
	__property Androidapi::Jni::App::_di_JService JavaService = {read=FJavaService};
	__property Androidapi::Jni::Support::_di_JJobIntentService JavaIntentService = {read=FJavaJobIntentService};
	Androidapi::Jni::Os::_di_JIBinder __fastcall GetBinder();
	
__published:
	__property OnCreate;
	__property OnDestroy;
	__property TOnBindEvent OnBind = {read=FOnBind, write=FOnBind};
	__property TOnUnBindEvent OnUnBind = {read=FOnUnBind, write=FOnUnBind};
	__property TOnRebindEvent OnRebind = {read=FOnRebind, write=FOnRebind};
	__property TOnTaskRemovedEvent OnTaskRemoved = {read=FOnTaskRemoved, write=FOnTaskRemoved};
	__property TOnConfigurationChangedEvent OnConfigurationChanged = {read=FOnConfigurationChanged, write=FOnConfigurationChanged};
	__property TOnLowMemoryEvent OnLowMemory = {read=FOnLowMemory, write=FOnLowMemory};
	__property TOnTrimMemoryEvent OnTrimMemory = {read=FOnTrimMemory, write=FOnTrimMemory};
	__property TOnHandleMessage OnHandleMessage = {read=FOnHandleMessage, write=FOnHandleMessage};
public:
	/* TDataModule.Create */ inline __fastcall virtual TAndroidBaseService(System::Classes::TComponent* AOwner) : System::Classes::TDataModule(AOwner) { }
	/* TDataModule.CreateNew */ inline __fastcall virtual TAndroidBaseService(System::Classes::TComponent* AOwner, int Dummy) : System::Classes::TDataModule(AOwner, Dummy) { }
	/* TDataModule.Destroy */ inline __fastcall virtual ~TAndroidBaseService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidService : public TAndroidBaseService
{
	typedef TAndroidBaseService inherited;
	
private:
	TOnStartCommandEvent FOnStartCommand;
	
protected:
	virtual int __fastcall DoStartCommand(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AStartIntent, int AFlags, int AStartID);
	
__published:
	__property OnCreate;
	__property OnDestroy;
	__property TOnStartCommandEvent OnStartCommand = {read=FOnStartCommand, write=FOnStartCommand};
	__property OnBind;
	__property OnUnBind;
	__property OnRebind;
	__property OnTaskRemoved;
	__property OnConfigurationChanged;
	__property OnLowMemory;
	__property OnTrimMemory;
	__property OnHandleMessage;
public:
	/* TDataModule.Create */ inline __fastcall virtual TAndroidService(System::Classes::TComponent* AOwner) : TAndroidBaseService(AOwner) { }
	/* TDataModule.CreateNew */ inline __fastcall virtual TAndroidService(System::Classes::TComponent* AOwner, int Dummy) : TAndroidBaseService(AOwner, Dummy) { }
	/* TDataModule.Destroy */ inline __fastcall virtual ~TAndroidService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidIntentService : public TAndroidBaseService
{
	typedef TAndroidBaseService inherited;
	
private:
	TOnHandleIntent FOnHandleIntent;
	
protected:
	virtual void __fastcall DoHandleIntent(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);
	
__published:
	__property OnCreate;
	__property OnDestroy;
	__property OnBind;
	__property OnUnBind;
	__property OnRebind;
	__property OnTaskRemoved;
	__property OnConfigurationChanged;
	__property OnLowMemory;
	__property OnTrimMemory;
	__property TOnHandleIntent OnHandleIntent = {read=FOnHandleIntent, write=FOnHandleIntent};
	__property OnHandleMessage;
public:
	/* TDataModule.Create */ inline __fastcall virtual TAndroidIntentService(System::Classes::TComponent* AOwner) : TAndroidBaseService(AOwner) { }
	/* TDataModule.CreateNew */ inline __fastcall virtual TAndroidIntentService(System::Classes::TComponent* AOwner, int Dummy) : TAndroidBaseService(AOwner, Dummy) { }
	/* TDataModule.Destroy */ inline __fastcall virtual ~TAndroidIntentService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TServiceCallbacks : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static Androidapi::Jni::Os::_di_JIBinder FBinder;
	
protected:
	static TAndroidService* FService;
	static TAndroidIntentService* FIntentService;
	static void __fastcall OnCreateCallback(const Androidapi::Jni::App::_di_JService AJavaService);
	static void __fastcall OnDestroyCallback();
	static int __fastcall OnStartCommandCallback(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AStartIntent, int AFlags, int AStartID);
	static Androidapi::Jni::Os::_di_JIBinder __fastcall OnBindCallback(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);
	static bool __fastcall onUnbindCallback(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);
	static void __fastcall onRebindCallback(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);
	static void __fastcall onTaskRemovedCallback(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent ARootIntent);
	static void __fastcall onConfigurationChangedCallback(const Androidapi::Jni::Graphicscontentviewtext::_di_JConfiguration NewConfig);
	static void __fastcall onLowMemoryCallback();
	static void __fastcall onTrimMemoryCallback(int Level);
	static void __fastcall onHandleIntentCallback(const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AnIntent);
	static __int64 __fastcall GetDelphiService();
	__classmethod bool __fastcall onHandleMessageCallback(const Androidapi::Jni::Os::_di_JMessage AMessage);
	
private:
	// __classmethod void __fastcall Create_();
	// __classmethod void __fastcall Destroy_();
public:
	/* TObject.Create */ inline __fastcall TServiceCallbacks() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TServiceCallbacks() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TOnLocalServiceConnected)(TAndroidBaseService* const ALocalService);

typedef void __fastcall (__closure *TOnLocalServiceDisconnected)(void);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TLocalServiceConnection : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	class DELPHICLASS TJavaServiceConnection;
	class PASCALIMPLEMENTATION TJavaServiceConnection : public Androidapi::Jnibridge::TJavaLocal
	{
		typedef Androidapi::Jnibridge::TJavaLocal inherited;
		
	private:
		TLocalServiceConnection* FLocalConnection;
		
	public:
		__fastcall TJavaServiceConnection(TLocalServiceConnection* const ALocalConnection);
		void __cdecl onBindingDied(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName name);
		void __cdecl onServiceConnected(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName name, Androidapi::Jni::Os::_di_JIBinder service);
		void __cdecl onServiceDisconnected(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName name);
	public:
		/* TJavaLocal.Destroy */ inline __fastcall virtual ~TJavaServiceConnection() { }
		
private:
		void *__JServiceConnection;	// Androidapi::Jni::Graphicscontentviewtext::JServiceConnection 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {B1F97308-817B-4AC2-91CA-3C5FF72D4707}
		operator Androidapi::Jni::Graphicscontentviewtext::_di_JServiceConnection()
		{
			Androidapi::Jni::Graphicscontentviewtext::_di_JServiceConnection intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Androidapi::Jni::Graphicscontentviewtext::JServiceConnection*(void) { return (Androidapi::Jni::Graphicscontentviewtext::JServiceConnection*)&__JServiceConnection; }
		#endif
		
	};
	
	
	
private:
	TJavaServiceConnection* FConnection;
	TAndroidBaseService* FLocalService;
	TOnLocalServiceConnected FOnConnected;
	TOnLocalServiceDisconnected FOnDisconnected;
	void __fastcall DoOnConnected(TAndroidBaseService* const ALocalService);
	void __fastcall DoOnDisconnected();
	
public:
	__fastcall TLocalServiceConnection();
	__fastcall virtual ~TLocalServiceConnection();
	static void __fastcall StartService(const System::UnicodeString AServiceName);
	static void __fastcall StartJobIntentService(const System::UnicodeString AServiceName, int AJobID = 0x1, const Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AIntent = Androidapi::Jni::Graphicscontentviewtext::_di_JIntent());
	void __fastcall BindService(const System::UnicodeString AServiceName, int AFlags = 0x1);
	void __fastcall UnbindService();
	__property TOnLocalServiceConnected OnConnected = {read=FOnConnected, write=FOnConnected};
	__property TOnLocalServiceDisconnected OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
	__property TAndroidBaseService* LocalService = {read=FLocalService};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TOnRemoteServiceConnected)(const Androidapi::Jni::Os::_di_JMessenger ServiceMessenger);

typedef void __fastcall (__closure *TOnRemoteServiceDisconnected)(void);

typedef void __fastcall (__closure *TOnRemoteServiceHandleMessage)(const Androidapi::Jni::Os::_di_JMessage AMessage);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TRemoteServiceConnection : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	class DELPHICLASS TJavaServiceConnection;
	class PASCALIMPLEMENTATION TJavaServiceConnection : public Androidapi::Jnibridge::TJavaLocal
	{
		typedef Androidapi::Jnibridge::TJavaLocal inherited;
		
	private:
		TRemoteServiceConnection* FLocalConnection;
		
	public:
		__fastcall TJavaServiceConnection(TRemoteServiceConnection* const ALocalConnection);
		void __cdecl onBindingDied(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName name);
		void __cdecl onServiceConnected(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName name, Androidapi::Jni::Os::_di_JIBinder service);
		void __cdecl onServiceDisconnected(Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName name);
	public:
		/* TJavaLocal.Destroy */ inline __fastcall virtual ~TJavaServiceConnection() { }
		
private:
		void *__JServiceConnection;	// Androidapi::Jni::Graphicscontentviewtext::JServiceConnection 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {B1F97308-817B-4AC2-91CA-3C5FF72D4707}
		operator Androidapi::Jni::Graphicscontentviewtext::_di_JServiceConnection()
		{
			Androidapi::Jni::Graphicscontentviewtext::_di_JServiceConnection intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Androidapi::Jni::Graphicscontentviewtext::JServiceConnection*(void) { return (Androidapi::Jni::Graphicscontentviewtext::JServiceConnection*)&__JServiceConnection; }
		#endif
		
	};
	
	
	class DELPHICLASS TRTLHandlerListener;
	class PASCALIMPLEMENTATION TRTLHandlerListener : public Androidapi::Jnibridge::TJavaLocal
	{
		typedef Androidapi::Jnibridge::TJavaLocal inherited;
		
	private:
		Androidapi::Jni::Embarcadero::_di_JRTLHandler FHandler;
		TRemoteServiceConnection* FConnection;
		
	public:
		__fastcall TRTLHandlerListener(TRemoteServiceConnection* const AConnection);
		void __cdecl handleMessage(Androidapi::Jni::Os::_di_JMessage msg);
		__property Androidapi::Jni::Embarcadero::_di_JRTLHandler Handler = {read=FHandler};
	public:
		/* TJavaLocal.Destroy */ inline __fastcall virtual ~TRTLHandlerListener() { }
		
private:
		void *__JRTLHandler_Listener;	// Androidapi::Jni::Embarcadero::JRTLHandler_Listener 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {D5EEE739-658B-4973-B431-F74CA8681B6E}
		operator Androidapi::Jni::Embarcadero::_di_JRTLHandler_Listener()
		{
			Androidapi::Jni::Embarcadero::_di_JRTLHandler_Listener intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Androidapi::Jni::Embarcadero::JRTLHandler_Listener*(void) { return (Androidapi::Jni::Embarcadero::JRTLHandler_Listener*)&__JRTLHandler_Listener; }
		#endif
		
	};
	
	
	
private:
	TJavaServiceConnection* FConnection;
	TOnRemoteServiceConnected FOnConnected;
	TOnRemoteServiceDisconnected FOnDisconnected;
	TOnRemoteServiceHandleMessage FOnHandleMessage;
	Androidapi::Jni::Os::_di_JMessenger FJServiceMessenger;
	TRTLHandlerListener* FHandlerListener;
	Androidapi::Jni::Os::_di_JMessenger FJLocalMessenger;
	Androidapi::Jni::Embarcadero::_di_JRTLHandler __fastcall GetHandler();
	void __fastcall DoOnConnected(const Androidapi::Jni::Os::_di_JIBinder service);
	void __fastcall DoOnDisconnected();
	void __fastcall DoOnHandleMessage(const Androidapi::Jni::Os::_di_JMessage AMessage);
	
public:
	__fastcall TRemoteServiceConnection();
	__fastcall virtual ~TRemoteServiceConnection();
	void __fastcall BindService(const System::UnicodeString APackageName, const System::UnicodeString AServiceName, int AFlags = 0x1);
	void __fastcall UnbindService();
	__property TOnRemoteServiceConnected OnConnected = {read=FOnConnected, write=FOnConnected};
	__property TOnRemoteServiceDisconnected OnDisconnected = {read=FOnDisconnected, write=FOnDisconnected};
	__property TOnRemoteServiceHandleMessage OnHandleMessage = {read=FOnHandleMessage, write=FOnHandleMessage};
	__property Androidapi::Jni::Os::_di_JMessenger ServiceMessenger = {read=FJServiceMessenger};
	__property Androidapi::Jni::Os::_di_JMessenger LocalMessenger = {read=FJLocalMessenger};
	__property Androidapi::Jni::Embarcadero::_di_JRTLHandler Handler = {read=GetHandler};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Service */
}	/* namespace Android */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANDROID_SERVICE)
using namespace System::Android::Service;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANDROID)
using namespace System::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Android_ServiceHPP
