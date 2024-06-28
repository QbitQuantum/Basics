// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.PushTypes.pas' rev: 34.00 (iOS)

#ifndef Rest_Backend_PushtypesHPP
#define Rest_Backend_PushtypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <System.PushNotification.hpp>
#include <REST.Backend.Providers.hpp>
#include <REST.Backend.MetaTypes.hpp>
#include <REST.Backend.ServiceTypes.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Pushtypes
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IBackendPushDeviceService;
typedef System::DelphiInterface<IBackendPushDeviceService> _di_IBackendPushDeviceService;
__interface DELPHIINTERFACE IBackendPushDeviceApi;
typedef System::DelphiInterface<IBackendPushDeviceApi> _di_IBackendPushDeviceApi;
__interface DELPHIINTERFACE IBackendPushDeviceApi2;
typedef System::DelphiInterface<IBackendPushDeviceApi2> _di_IBackendPushDeviceApi2;
class DELPHICLASS TBackendPushDeviceApi;
__interface DELPHIINTERFACE IBackendPushService;
typedef System::DelphiInterface<IBackendPushService> _di_IBackendPushService;
__interface DELPHIINTERFACE IBackendPushApi;
typedef System::DelphiInterface<IBackendPushApi> _di_IBackendPushApi;
__interface DELPHIINTERFACE IBackendPushApi2;
typedef System::DelphiInterface<IBackendPushApi2> _di_IBackendPushApi2;
__interface DELPHIINTERFACE IBackendPushApi3;
typedef System::DelphiInterface<IBackendPushApi3> _di_IBackendPushApi3;
class DELPHICLASS TBackendPushApi;
class DELPHICLASS TPushData;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TDeviceRegisteredAtProviderEvent)(System::Pushnotification::TPushService* const AService);

__interface  INTERFACE_UUID("{1810D21D-BF97-4DF0-B39A-DECA2A8A6F07}") IBackendPushDeviceService  : public Rest::Backend::Providers::IBackendService 
{
	virtual _di_IBackendPushDeviceApi __fastcall GetPushDeviceAPI() = 0 ;
	virtual _di_IBackendPushDeviceApi __fastcall CreatePushDeviceApi() = 0 ;
	__property _di_IBackendPushDeviceApi PushDeviceAPI = {read=GetPushDeviceAPI};
};

__interface  INTERFACE_UUID("{2F1A3600-8C92-4C74-9D20-E800FD275482}") IBackendPushDeviceApi  : public System::IInterface 
{
	virtual System::Pushnotification::TPushService* __fastcall GetPushService() = 0 ;
	virtual bool __fastcall HasPushService() = 0 ;
	virtual void __fastcall RegisterDevice(TDeviceRegisteredAtProviderEvent AOnRegistered) = 0 ;
	virtual void __fastcall UnregisterDevice() = 0 ;
};

__interface  INTERFACE_UUID("{3A78B2C1-233B-485D-9616-049A66E374B3}") IBackendPushDeviceApi2  : public System::IInterface 
{
	virtual void __fastcall RegisterDevice(System::Json::TJSONObject* const AProperties, TDeviceRegisteredAtProviderEvent AOnRegistered) = 0 ;
	virtual bool __fastcall TryGetInstallationValue(/* out */ Rest::Backend::Metatypes::TBackendEntityValue &AValue) = 0 ;
};

class PASCALIMPLEMENTATION TBackendPushDeviceApi : public Rest::Backend::Servicetypes::TBackendAuthenticationApi
{
	typedef Rest::Backend::Servicetypes::TBackendAuthenticationApi inherited;
	
private:
	_di_IBackendPushDeviceApi FServiceApi;
	_di_IBackendPushDeviceService FService;
	_di_IBackendPushDeviceApi __fastcall GetServiceAPI();
	
protected:
	virtual Rest::Backend::Servicetypes::_di_IBackendAuthenticationApi __fastcall GetAuthenticationApi();
	
public:
	__fastcall TBackendPushDeviceApi(const _di_IBackendPushDeviceApi AApi)/* overload */;
	__fastcall TBackendPushDeviceApi(const _di_IBackendPushDeviceService AService)/* overload */;
	System::Pushnotification::TPushService* __fastcall GetPushService();
	bool __fastcall HasPushService();
	void __fastcall RegisterDevice(TDeviceRegisteredAtProviderEvent AOnRegistered)/* overload */;
	void __fastcall RegisterDevice(System::Json::TJSONObject* const AProperties, TDeviceRegisteredAtProviderEvent AOnRegistered)/* overload */;
	void __fastcall UnregisterDevice();
	bool __fastcall TryGetInstallationValue(/* out */ Rest::Backend::Metatypes::TBackendEntityValue &AValue);
	__property _di_IBackendPushDeviceApi ProviderAPI = {read=FServiceApi};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBackendPushDeviceApi() { }
	
};


__interface  INTERFACE_UUID("{34547227-6E40-40F7-A59D-4961FDBD499B}") IBackendPushService  : public Rest::Backend::Providers::IBackendService 
{
	virtual _di_IBackendPushApi __fastcall GetPushAPI() = 0 ;
	virtual _di_IBackendPushApi __fastcall CreatePushApi() = 0 ;
	__property _di_IBackendPushApi PushAPI = {read=GetPushAPI};
};

__interface  INTERFACE_UUID("{F7FAC938-CE46-42A9-B4D2-8620365A64B0}") IBackendPushApi  : public Rest::Backend::Providers::IBackendApi 
{
	virtual void __fastcall PushBroadcast(TPushData* const AData) = 0 ;
};

__interface  INTERFACE_UUID("{E9E1859D-1C35-4266-A335-490508A2C6EE}") IBackendPushApi2  : public System::IInterface 
{
	virtual void __fastcall PushBroadcast(System::Json::TJSONObject* const AData) = 0 /* overload */;
	virtual System::Json::TJSONObject* __fastcall PushDataAsJSON(TPushData* const AData) = 0 ;
};

__interface  INTERFACE_UUID("{E0B215B3-8709-4D80-A2DE-8847A69D1773}") IBackendPushApi3  : public System::IInterface 
{
	virtual void __fastcall PushToTarget(TPushData* const AData, System::Json::TJSONObject* const ATarget) = 0 /* overload */;
	virtual void __fastcall PushToTarget(System::Json::TJSONObject* const AData, System::Json::TJSONObject* const ATarget) = 0 /* overload */;
};

class PASCALIMPLEMENTATION TBackendPushApi : public Rest::Backend::Servicetypes::TBackendAuthenticationApi
{
	typedef Rest::Backend::Servicetypes::TBackendAuthenticationApi inherited;
	
private:
	_di_IBackendPushService FService;
	_di_IBackendPushApi FServiceAPI;
	_di_IBackendPushApi __fastcall GetServiceAPI();
	
protected:
	virtual Rest::Backend::Servicetypes::_di_IBackendAuthenticationApi __fastcall GetAuthenticationApi();
	
public:
	__fastcall TBackendPushApi(const _di_IBackendPushService AService)/* overload */;
	__fastcall TBackendPushApi(const _di_IBackendPushApi AServiceAPI)/* overload */;
	void __fastcall PushBroadcast(TPushData* const AData)/* overload */;
	void __fastcall PushToTarget(TPushData* const AData, System::Json::TJSONObject* const ATarget)/* overload */;
	void __fastcall PushToTarget(System::Json::TJSONObject* const AData, System::Json::TJSONObject* const ATarget)/* overload */;
	System::Json::TJSONObject* __fastcall PushDataAsJSON(TPushData* const AData);
	__property _di_IBackendPushApi ProviderAPI = {read=GetServiceAPI};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBackendPushApi() { }
	
};


class PASCALIMPLEMENTATION TPushData : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef System::Sysutils::_di_TProc TChangeMethod;
	
	class DELPHICLASS TDataGroup;
	class PASCALIMPLEMENTATION TDataGroup : public System::Classes::TPersistent
	{
		typedef System::Classes::TPersistent inherited;
		
	private:
		System::Sysutils::_di_TProc FOnChange;
		
	protected:
		void __fastcall DoChange();
		
	public:
		virtual void __fastcall Load(System::Json::TJSONObject* const AJSONObject, const System::UnicodeString ARoot) = 0 ;
		virtual void __fastcall Save(System::Json::TJSONObject* const AJSONObject, const System::UnicodeString ARoot) = 0 ;
		__property System::Sysutils::_di_TProc OnChange = {read=FOnChange, write=FOnChange};
	public:
		/* TPersistent.Destroy */ inline __fastcall virtual ~TDataGroup() { }
		
	public:
		/* TObject.Create */ inline __fastcall TDataGroup() : System::Classes::TPersistent() { }
		
	};
	
	
	class DELPHICLASS TAPS;
	class PASCALIMPLEMENTATION TAPS : public TPushData::TDataGroup
	{
		typedef TPushData::TDataGroup inherited;
		
		
	public:
		struct DECLSPEC_DRECORD TNames
		{
		public:
			#define TPushData_TAPS_TNames_ApsRoot u"aps"
			
			#define TPushData_TAPS_TNames_Alert u"alert"
			
			#define TPushData_TAPS_TNames_Badge u"badge"
			
			#define TPushData_TAPS_TNames_Sound u"sound"
			
		};
		
		
		
	private:
		System::UnicodeString FAlert;
		System::UnicodeString FBadge;
		System::UnicodeString FSound;
		void __fastcall SetAlert(const System::UnicodeString Value);
		void __fastcall SetBadge(const System::UnicodeString Value);
		void __fastcall SetSound(const System::UnicodeString Value);
		
	protected:
		virtual void __fastcall AssignTo(System::Classes::TPersistent* APersistent);
		
	public:
		virtual void __fastcall Load(System::Json::TJSONObject* const AJSONObject, const System::UnicodeString ARoot);
		virtual void __fastcall Save(System::Json::TJSONObject* const AJSONObject, const System::UnicodeString ARoot);
		
	__published:
		__property System::UnicodeString Alert = {read=FAlert, write=SetAlert};
		__property System::UnicodeString Badge = {read=FBadge, write=SetBadge};
		__property System::UnicodeString Sound = {read=FSound, write=SetSound};
	public:
		/* TPersistent.Destroy */ inline __fastcall virtual ~TAPS() { }
		
	public:
		/* TObject.Create */ inline __fastcall TAPS() : TPushData::TDataGroup() { }
		
	};
	
	
	class DELPHICLASS TGCM;
	class PASCALIMPLEMENTATION TGCM : public TPushData::TDataGroup
	{
		typedef TPushData::TDataGroup inherited;
		
		
	public:
		struct DECLSPEC_DRECORD TNames
		{
		public:
			#define TPushData_TGCM_TNames_Action u"action"
			
			#define TPushData_TGCM_TNames_Msg u"msg"
			
			#define TPushData_TGCM_TNames_Message u"message"
			
			#define TPushData_TGCM_TNames_Title u"title"
			
		};
		
		
		
	private:
		System::UnicodeString FAction;
		System::UnicodeString FTitle;
		System::UnicodeString FMessage;
		System::UnicodeString FMsg;
		void __fastcall SetAction(const System::UnicodeString Value);
		void __fastcall SetTitle(const System::UnicodeString Value);
		void __fastcall SetMessage(const System::UnicodeString Value);
		void __fastcall SetMsg(const System::UnicodeString Value);
		
	protected:
		virtual void __fastcall AssignTo(System::Classes::TPersistent* APersistent);
		
	public:
		virtual void __fastcall Load(System::Json::TJSONObject* const AJSONObject, const System::UnicodeString ARoot);
		virtual void __fastcall Save(System::Json::TJSONObject* const AJSONObject, const System::UnicodeString ARoot);
		
	__published:
		__property System::UnicodeString Action = {read=FAction, write=SetAction};
		__property System::UnicodeString Title = {read=FTitle, write=SetTitle};
		__property System::UnicodeString Message = {read=FMessage, write=SetMessage};
		__property System::UnicodeString Msg = {read=FMsg, write=SetMsg};
	public:
		/* TPersistent.Destroy */ inline __fastcall virtual ~TGCM() { }
		
	public:
		/* TObject.Create */ inline __fastcall TGCM() : TPushData::TDataGroup() { }
		
	};
	
	
	class DELPHICLASS TExtras;
	class PASCALIMPLEMENTATION TExtras : public TPushData::TDataGroup
	{
		typedef TPushData::TDataGroup inherited;
		
		
	public:
		typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> TExtrasPair;
		
		typedef System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> >* TExtrasList;
		
		
public:
		System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> operator[](int I) { return this->Items[I]; }
		
	private:
		int __fastcall GetCount();
		System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> __fastcall GetItem(int I);
		
	protected:
		System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> >* FList;
		virtual void __fastcall AssignTo(System::Classes::TPersistent* APersistent);
		
	public:
		__fastcall TExtras();
		__fastcall virtual ~TExtras();
		void __fastcall Add(const System::UnicodeString AName, const System::UnicodeString AValue);
		int __fastcall IndexOf(const System::UnicodeString AName);
		void __fastcall Clear();
		void __fastcall Remove(const System::UnicodeString AName);
		void __fastcall Delete(int AIndex);
		System::Generics::Collections::TEnumerator__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> >* __fastcall GetEnumerator();
		virtual void __fastcall Load(System::Json::TJSONObject* const AJSONObject, const System::UnicodeString ARoot);
		virtual void __fastcall Save(System::Json::TJSONObject* const AJSONObject, const System::UnicodeString ARoot);
		__property int Count = {read=GetCount, nodefault};
		__property System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> Items[int I] = {read=GetItem/*, default*/};
	};
	
	
	
private:
	static System::UnicodeString __fastcall GetString(System::Json::TJSONObject* const AJSON, const System::UnicodeString ARoot, const System::UnicodeString AName)/* overload */;
	static void __fastcall SetString(System::Json::TJSONObject* const AJSON, const System::UnicodeString ARoot, const System::UnicodeString AName, const System::UnicodeString AValue)/* overload */;
	static void __fastcall SetValue(System::Json::TJSONObject* const AJSON, const System::UnicodeString ARoot, const System::UnicodeString AName, System::Json::TJSONValue* const AValue)/* overload */;
	static void __fastcall SetString(System::Json::TJSONObject* const AJSON, const System::UnicodeString AName, const System::UnicodeString AValue)/* overload */;
	TAPS* FAPS;
	TGCM* FGCM;
	TExtras* FExtras;
	System::Sysutils::_di_TProc FOnChange;
	System::UnicodeString FMessage;
	void __fastcall SetMessage(const System::UnicodeString Value);
	void __fastcall SetAPS(TAPS* const Value);
	void __fastcall SetGCM(TGCM* const Value);
	void __fastcall DoChange();
	void __fastcall SetExtras(TExtras* const Value);
	
public:
	__fastcall TPushData()/* overload */;
	__fastcall virtual ~TPushData();
	void __fastcall Load(System::Json::TJSONObject* const AJSON);
	void __fastcall SaveMessage(System::Json::TJSONObject* const AJSON, const System::UnicodeString AName);
	__property System::UnicodeString Message = {read=FMessage, write=SetMessage};
	__property TAPS* APS = {read=FAPS, write=SetAPS};
	__property TGCM* GCM = {read=FGCM, write=SetGCM};
	__property TExtras* Extras = {read=FExtras, write=SetExtras};
	__property System::Sysutils::_di_TProc OnChange = {read=FOnChange, write=FOnChange};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Pushtypes */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_PUSHTYPES)
using namespace Rest::Backend::Pushtypes;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND)
using namespace Rest::Backend;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_Backend_PushtypesHPP
