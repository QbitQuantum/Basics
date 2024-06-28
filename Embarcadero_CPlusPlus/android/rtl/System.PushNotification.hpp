// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.PushNotification.pas' rev: 34.00 (Android)

#ifndef System_PushnotificationHPP
#define System_PushnotificationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.JSON.hpp>
#include <System.Messaging.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Pushnotification
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPushService;
class DELPHICLASS TPushServiceConnection;
class DELPHICLASS TPushServiceManager;
class DELPHICLASS TPushServiceNotification;
class DELPHICLASS EPushServiceError;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPushService : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> TPropPair;
	
	typedef System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TPropArray;
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TServiceNames
	{
	public:
		#define TPushService_TServiceNames_GCM u"gcm"
		
		#define TPushService_TServiceNames_FCM u"fcm"
		
		#define TPushService_TServiceNames_APS u"aps"
		
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TAppPropNames
	{
	public:
		#define TPushService_TAppPropNames_GCMAppID u"gcmappid"
		
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TDeviceTokenNames
	{
	public:
		#define TPushService_TDeviceTokenNames_DeviceToken u"devicetoken"
		
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TDeviceIDNames
	{
	public:
		#define TPushService_TDeviceIDNames_DeviceID u"deviceid"
		
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	enum class DECLSPEC_DENUM TStatus : unsigned char { Stopped, Starting, Started, StartupError };
	
	enum class DECLSPEC_DENUM TChange : unsigned char { Status, DeviceToken, StartupNotifications };
	
	typedef System::Set<TChange, _DELPHI_SET_ENUMERATOR(TChange::Status), _DELPHI_SET_ENUMERATOR(TChange::StartupNotifications)> TChanges;
	
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FAppProps;
	System::Generics::Collections::TList__1<TPushServiceConnection*>* FConnections;
	System::UnicodeString FServiceName;
	TPushServiceManager* FManager;
	TPushServiceConnection* __fastcall GetConnection(int I);
	int __fastcall GetConnectionCount();
	void __fastcall AddConnection(TPushServiceConnection* const AConnection);
	void __fastcall RemoveConnection(TPushServiceConnection* const AConnection);
	void __fastcall ForConnections(System::DelphiInterface<System::Sysutils::TProc__1<TPushServiceConnection*> > AProc);
	System::UnicodeString __fastcall GetAppProp(const System::UnicodeString AName);
	void __fastcall SetAppProp(const System::UnicodeString AName, const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetDeviceIDValue(const System::UnicodeString AName);
	System::UnicodeString __fastcall GetDeviceTokenValue(const System::UnicodeString AName);
	System::UnicodeString __fastcall GetPropValue(const System::UnicodeString AName, System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > APairs);
	
protected:
	void __fastcall DoChange(TChanges AChanges);
	void __fastcall DoReceiveNotification(TPushServiceNotification* const ANotification);
	virtual TStatus __fastcall GetStatus() = 0 ;
	virtual void __fastcall StartService() = 0 ;
	virtual void __fastcall StopService() = 0 ;
	virtual System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetDeviceToken() = 0 ;
	virtual System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetDeviceID() = 0 ;
	virtual System::TArray__1<TPushServiceNotification*> __fastcall GetStartupNotifications() = 0 ;
	virtual System::UnicodeString __fastcall GetStartupError() = 0 ;
	
public:
	__fastcall virtual TPushService(TPushServiceManager* const AOwner, const System::UnicodeString AServiceName);
	virtual void __fastcall AfterConstruction();
	__fastcall virtual ~TPushService();
	TPushServiceConnection* __fastcall CreateConnection();
	int __fastcall IndexOfConnection(TPushServiceConnection* const AConnection);
	__property System::UnicodeString ServiceName = {read=FServiceName};
	__property TPushServiceManager* Manager = {read=FManager};
	__property int ConnectionCount = {read=GetConnectionCount, nodefault};
	__property TPushServiceConnection* Connections[int I] = {read=GetConnection};
	__property TStatus Status = {read=GetStatus, nodefault};
	__property System::UnicodeString AppProps[const System::UnicodeString AName] = {read=GetAppProp, write=SetAppProp};
	__property System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > DeviceToken = {read=GetDeviceToken};
	__property System::UnicodeString DeviceTokenValue[const System::UnicodeString AName] = {read=GetDeviceTokenValue};
	__property System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > DeviceID = {read=GetDeviceID};
	__property System::UnicodeString DeviceIDValue[const System::UnicodeString AName] = {read=GetDeviceIDValue};
	__property System::TArray__1<TPushServiceNotification*> StartupNotifications = {read=GetStartupNotifications};
	__property System::UnicodeString StartupError = {read=GetStartupError};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPushServiceConnection : /*[[sealed]]*/ public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef void __fastcall (__closure *TReceiveNotificationEvent)(System::TObject* Sender, TPushServiceNotification* const ANotification);
	
	typedef void __fastcall (__closure *TChangeEvent)(System::TObject* Sender, TPushService::TChanges AChange);
	
	
private:
	TPushService* FService;
	bool FActive;
	TReceiveNotificationEvent FOnReceiveNotification;
	TChangeEvent FOnChange;
	void __fastcall SetActive(const bool Value);
	
protected:
	void __fastcall DoChange(TPushService::TChanges AChanges);
	void __fastcall DoReceiveNotification(TPushServiceNotification* const ANotification);
	
public:
	__fastcall virtual TPushServiceConnection(TPushService* const AService);
	__fastcall virtual ~TPushServiceConnection();
	virtual void __fastcall AfterConstruction();
	__property bool Active = {read=FActive, write=SetActive, nodefault};
	__property TPushService* Service = {read=FService};
	__property TReceiveNotificationEvent OnReceiveNotification = {read=FOnReceiveNotification, write=FOnReceiveNotification};
	__property TChangeEvent OnChange = {read=FOnChange, write=FOnChange};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPushServiceManager : /*[[sealed]]*/ public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::Generics::Collections::TPair__2<TPushService*,bool> TServicePair;
	
	
public:
	TPushService* operator[](int Index) { return this->Services[Index]; }
	
private:
	static TPushServiceManager* FInstance;
	System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<TPushService*,bool> >* FServices;
	int __fastcall GetCount();
	TPushService* __fastcall GetService(int Index)/* overload */;
	
protected:
	__fastcall TPushServiceManager();
	
private:
	static TPushServiceManager* __fastcall GetInstance();
	
public:
	__fastcall virtual ~TPushServiceManager();
	void __fastcall AddService(TPushService* AService, bool AOwnService = true);
	void __fastcall RemoveService(TPushService* AService);
	TPushService* __fastcall GetServiceByName(const System::UnicodeString AServiceName);
	int __fastcall IndexOfService(TPushService* const AService);
	__property int Count = {read=GetCount, nodefault};
	__property TPushService* Services[int Index] = {read=GetService/*, default*/};
	/* static */ __property TPushServiceManager* Instance = {read=GetInstance};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPushServiceNotification : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetDataKey() = 0 ;
	virtual System::Json::TJSONObject* __fastcall GetJson() = 0 ;
	virtual System::Json::TJSONObject* __fastcall GetDataObject() = 0 ;
	
public:
	__property System::UnicodeString DataKey = {read=GetDataKey};
	__property System::Json::TJSONObject* Json = {read=GetJson};
	__property System::Json::TJSONObject* DataObject = {read=GetDataObject};
public:
	/* TObject.Create */ inline __fastcall TPushServiceNotification() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPushServiceNotification() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EPushServiceError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EPushServiceError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EPushServiceError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EPushServiceError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EPushServiceError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EPushServiceError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EPushServiceError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EPushServiceError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EPushServiceError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPushServiceError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPushServiceError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPushServiceError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPushServiceError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EPushServiceError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Pushnotification */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_PUSHNOTIFICATION)
using namespace System::Pushnotification;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_PushnotificationHPP
