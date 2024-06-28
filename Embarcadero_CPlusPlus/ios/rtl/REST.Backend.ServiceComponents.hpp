// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.ServiceComponents.pas' rev: 34.00 (iOS)

#ifndef Rest_Backend_ServicecomponentsHPP
#define Rest_Backend_ServicecomponentsHPP

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
#include <System.Generics.Collections.hpp>
#include <REST.Client.hpp>
#include <REST.BindSource.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Backend.Providers.hpp>
#include <REST.Backend.ServiceTypes.hpp>
#include <REST.Backend.BindSource.hpp>
#include <REST.Backend.PushTypes.hpp>
#include <REST.Backend.Consts.hpp>
#include <REST.Backend.MetaTypes.hpp>
#include <System.SyncObjs.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Servicecomponents
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomBackendUsers;
class DELPHICLASS TBackendUsers;
class DELPHICLASS TCustomBackendGroups;
class DELPHICLASS TBackendGroups;
class DELPHICLASS TCustomBackendStorage;
class DELPHICLASS TBackendStorage;
class DELPHICLASS TCustomBackendFiles;
class DELPHICLASS TBackendFiles;
class DELPHICLASS TCustomBackendQuery;
class DELPHICLASS TBackendQuery;
class DELPHICLASS TBackendQueryAdapter;
class DELPHICLASS TCustomBackendQueryBindSource;
class DELPHICLASS TSubBackendQueryBindSource;
class DELPHICLASS TCustomBackendPush;
class DELPHICLASS TBackendPush;
class DELPHICLASS TPushSenderAdapter;
class DELPHICLASS TCustomPushSenderBindSource;
class DELPHICLASS TSubPushSenderBindSource;
class DELPHICLASS TCustomBackendAuth;
class DELPHICLASS TBackendAuth;
class DELPHICLASS TBackendAuthAdapter;
class DELPHICLASS TCustomLoginBindSource;
class DELPHICLASS TSubLoginBindSource;
class DELPHICLASS TAuthAccess;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomBackendUsers : public Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendUsersService,Rest::Backend::Servicetypes::TBackendUsersApi*>
{
	typedef Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendUsersService,Rest::Backend::Servicetypes::TBackendUsersApi*> inherited;
	
private:
	Rest::Backend::Servicetypes::TBackendUsersApi* __fastcall GetUsers();
	Rest::Backend::Servicetypes::_di_IBackendUsersService __fastcall GetProviderService();
	
protected:
	virtual Rest::Backend::Servicetypes::TBackendUsersApi* __fastcall InternalCreateBackendServiceAPI();
	virtual Rest::Backend::Servicetypes::TBackendUsersApi* __fastcall InternalCreateIndependentBackendServiceAPI();
	virtual Rest::Backend::Providers::_di_IAuthAccess __fastcall CreateAuthAccess();
	
public:
	__property Rest::Backend::Servicetypes::TBackendUsersApi* Users = {read=GetUsers};
	__property Rest::Backend::Servicetypes::_di_IBackendUsersService ProviderService = {read=GetProviderService};
	Rest::Backend::Servicetypes::TBackendUsersApi* __fastcall CreateUserAPI();
public:
	/* {REST_Backend_Providers}TBackendServiceComponentAuth<REST_Backend_ServiceTypes_IBackendUsersService,REST_Backend_ServiceTypes_TBackendUsersApi>.Destroy */ inline __fastcall virtual ~TCustomBackendUsers() { }
	
public:
	/* {REST_Backend_Providers}TBackendServiceComponent<REST_Backend_ServiceTypes_IBackendUsersService,REST_Backend_ServiceTypes_TBackendUsersApi>.Create */ inline __fastcall virtual TCustomBackendUsers(System::Classes::TComponent* AOwner) : Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendUsersService,Rest::Backend::Servicetypes::TBackendUsersApi*>(AOwner) { }
	
};


class PASCALIMPLEMENTATION TBackendUsers : public TCustomBackendUsers
{
	typedef TCustomBackendUsers inherited;
	
__published:
	__property Provider;
	__property Auth;
public:
	/* {REST_Backend_Providers}TBackendServiceComponentAuth<REST_Backend_ServiceTypes_IBackendUsersService,REST_Backend_ServiceTypes_TBackendUsersApi>.Destroy */ inline __fastcall virtual ~TBackendUsers() { }
	
public:
	/* {REST_Backend_Providers}TBackendServiceComponent<REST_Backend_ServiceTypes_IBackendUsersService,REST_Backend_ServiceTypes_TBackendUsersApi>.Create */ inline __fastcall virtual TBackendUsers(System::Classes::TComponent* AOwner) : TCustomBackendUsers(AOwner) { }
	
};


class PASCALIMPLEMENTATION TCustomBackendGroups : public Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendGroupsService,Rest::Backend::Servicetypes::TBackendGroupsApi*>
{
	typedef Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendGroupsService,Rest::Backend::Servicetypes::TBackendGroupsApi*> inherited;
	
private:
	Rest::Backend::Servicetypes::TBackendGroupsApi* __fastcall GetGroups();
	Rest::Backend::Servicetypes::_di_IBackendGroupsService __fastcall GetProviderService();
	
protected:
	virtual Rest::Backend::Servicetypes::TBackendGroupsApi* __fastcall InternalCreateBackendServiceAPI();
	virtual Rest::Backend::Servicetypes::TBackendGroupsApi* __fastcall InternalCreateIndependentBackendServiceAPI();
	virtual Rest::Backend::Providers::_di_IAuthAccess __fastcall CreateAuthAccess();
	
public:
	__property Rest::Backend::Servicetypes::TBackendGroupsApi* Groups = {read=GetGroups};
	__property Rest::Backend::Servicetypes::_di_IBackendGroupsService ProviderService = {read=GetProviderService};
	Rest::Backend::Servicetypes::TBackendGroupsApi* __fastcall CreateGroupsAPI();
public:
	/* {REST_Backend_Providers}TBackendServiceComponentAuth<REST_Backend_ServiceTypes_IBackendGroupsService,REST_Backend_ServiceTypes_TBackendGroupsApi>.Destroy */ inline __fastcall virtual ~TCustomBackendGroups() { }
	
public:
	/* {REST_Backend_Providers}TBackendServiceComponent<REST_Backend_ServiceTypes_IBackendGroupsService,REST_Backend_ServiceTypes_TBackendGroupsApi>.Create */ inline __fastcall virtual TCustomBackendGroups(System::Classes::TComponent* AOwner) : Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendGroupsService,Rest::Backend::Servicetypes::TBackendGroupsApi*>(AOwner) { }
	
};


class PASCALIMPLEMENTATION TBackendGroups : public TCustomBackendGroups
{
	typedef TCustomBackendGroups inherited;
	
__published:
	__property Provider;
	__property Auth;
public:
	/* {REST_Backend_Providers}TBackendServiceComponentAuth<REST_Backend_ServiceTypes_IBackendGroupsService,REST_Backend_ServiceTypes_TBackendGroupsApi>.Destroy */ inline __fastcall virtual ~TBackendGroups() { }
	
public:
	/* {REST_Backend_Providers}TBackendServiceComponent<REST_Backend_ServiceTypes_IBackendGroupsService,REST_Backend_ServiceTypes_TBackendGroupsApi>.Create */ inline __fastcall virtual TBackendGroups(System::Classes::TComponent* AOwner) : TCustomBackendGroups(AOwner) { }
	
};


class PASCALIMPLEMENTATION TCustomBackendStorage : public Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendStorageService,Rest::Backend::Servicetypes::TBackendStorageApi*>
{
	typedef Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendStorageService,Rest::Backend::Servicetypes::TBackendStorageApi*> inherited;
	
private:
	Rest::Backend::Servicetypes::TBackendStorageApi* __fastcall GetStorage();
	Rest::Backend::Servicetypes::_di_IBackendStorageService __fastcall GetProviderService();
	
protected:
	virtual Rest::Backend::Servicetypes::TBackendStorageApi* __fastcall InternalCreateBackendServiceAPI();
	virtual Rest::Backend::Servicetypes::TBackendStorageApi* __fastcall InternalCreateIndependentBackendServiceAPI();
	virtual Rest::Backend::Providers::_di_IAuthAccess __fastcall CreateAuthAccess();
	
public:
	__property Rest::Backend::Servicetypes::TBackendStorageApi* Storage = {read=GetStorage};
	__property Rest::Backend::Servicetypes::_di_IBackendStorageService ProviderService = {read=GetProviderService};
	Rest::Backend::Servicetypes::TBackendStorageApi* __fastcall CreateStorageAPI();
public:
	/* {REST_Backend_Providers}TBackendServiceComponentAuth<REST_Backend_ServiceTypes_IBackendStorageService,REST_Backend_ServiceTypes_TBackendStorageApi>.Destroy */ inline __fastcall virtual ~TCustomBackendStorage() { }
	
public:
	/* {REST_Backend_Providers}TBackendServiceComponent<REST_Backend_ServiceTypes_IBackendStorageService,REST_Backend_ServiceTypes_TBackendStorageApi>.Create */ inline __fastcall virtual TCustomBackendStorage(System::Classes::TComponent* AOwner) : Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendStorageService,Rest::Backend::Servicetypes::TBackendStorageApi*>(AOwner) { }
	
};


class PASCALIMPLEMENTATION TBackendStorage : public TCustomBackendStorage
{
	typedef TCustomBackendStorage inherited;
	
__published:
	__property Provider;
	__property Auth;
public:
	/* {REST_Backend_Providers}TBackendServiceComponentAuth<REST_Backend_ServiceTypes_IBackendStorageService,REST_Backend_ServiceTypes_TBackendStorageApi>.Destroy */ inline __fastcall virtual ~TBackendStorage() { }
	
public:
	/* {REST_Backend_Providers}TBackendServiceComponent<REST_Backend_ServiceTypes_IBackendStorageService,REST_Backend_ServiceTypes_TBackendStorageApi>.Create */ inline __fastcall virtual TBackendStorage(System::Classes::TComponent* AOwner) : TCustomBackendStorage(AOwner) { }
	
};


class PASCALIMPLEMENTATION TCustomBackendFiles : public Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendFilesService,Rest::Backend::Servicetypes::TBackendFilesApi*>
{
	typedef Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendFilesService,Rest::Backend::Servicetypes::TBackendFilesApi*> inherited;
	
private:
	Rest::Backend::Servicetypes::TBackendFilesApi* __fastcall GetFiles();
	Rest::Backend::Servicetypes::_di_IBackendFilesService __fastcall GetProviderService();
	
protected:
	virtual Rest::Backend::Servicetypes::TBackendFilesApi* __fastcall InternalCreateBackendServiceAPI();
	virtual Rest::Backend::Servicetypes::TBackendFilesApi* __fastcall InternalCreateIndependentBackendServiceAPI();
	virtual Rest::Backend::Providers::_di_IAuthAccess __fastcall CreateAuthAccess();
	
public:
	__property Rest::Backend::Servicetypes::TBackendFilesApi* Files = {read=GetFiles};
	__property Rest::Backend::Servicetypes::_di_IBackendFilesService ProviderService = {read=GetProviderService};
	Rest::Backend::Servicetypes::TBackendFilesApi* __fastcall CreateFilesAPI();
public:
	/* {REST_Backend_Providers}TBackendServiceComponentAuth<REST_Backend_ServiceTypes_IBackendFilesService,REST_Backend_ServiceTypes_TBackendFilesApi>.Destroy */ inline __fastcall virtual ~TCustomBackendFiles() { }
	
public:
	/* {REST_Backend_Providers}TBackendServiceComponent<REST_Backend_ServiceTypes_IBackendFilesService,REST_Backend_ServiceTypes_TBackendFilesApi>.Create */ inline __fastcall virtual TCustomBackendFiles(System::Classes::TComponent* AOwner) : Rest::Backend::Providers::TBackendServiceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendFilesService,Rest::Backend::Servicetypes::TBackendFilesApi*>(AOwner) { }
	
};


class PASCALIMPLEMENTATION TBackendFiles : public TCustomBackendFiles
{
	typedef TCustomBackendFiles inherited;
	
__published:
	__property Provider;
	__property Auth;
public:
	/* {REST_Backend_Providers}TBackendServiceComponentAuth<REST_Backend_ServiceTypes_IBackendFilesService,REST_Backend_ServiceTypes_TBackendFilesApi>.Destroy */ inline __fastcall virtual ~TBackendFiles() { }
	
public:
	/* {REST_Backend_Providers}TBackendServiceComponent<REST_Backend_ServiceTypes_IBackendFilesService,REST_Backend_ServiceTypes_TBackendFilesApi>.Create */ inline __fastcall virtual TBackendFiles(System::Classes::TComponent* AOwner) : TCustomBackendFiles(AOwner) { }
	
};


class PASCALIMPLEMENTATION TCustomBackendQuery : public Rest::Backend::Bindsource::TBackendBindSourceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendQueryService,Rest::Backend::Servicetypes::TBackendQueryApi*>
{
	typedef Rest::Backend::Bindsource::TBackendBindSourceComponentAuth__2<Rest::Backend::Servicetypes::_di_IBackendQueryService,Rest::Backend::Servicetypes::TBackendQueryApi*> inherited;
	
	
private:
	typedef Rest::Bindsource::TRESTComponentNotify TNotify;
	
	typedef Rest::Bindsource::TRESTComponentNotifyList__1<Rest::Bindsource::TRESTComponentNotify*>* TNotifyList;
	
	
private:
	Rest::Bindsource::TRESTComponentNotifyList__1<Rest::Bindsource::TRESTComponentNotify*>* FNotifyList;
	System::Generics::Collections::TList__1<System::Classes::TNotifyEvent>* FJSONNotifyList;
	System::UnicodeString FBackendClassName;
	System::Classes::TStrings* FQueryLines;
	System::Json::TJSONArray* FJSONResult;
	TSubBackendQueryBindSource* FBindSource;
	System::UnicodeString FBackendService;
	Rest::Backend::Servicetypes::TBackendQueryApi* __fastcall GetQueryApi();
	void __fastcall SetQueryLines(System::Classes::TStrings* const Value);
	void __fastcall SetBackendClassName(const System::UnicodeString Value);
	void __fastcall PropertyValueChanged();
	void __fastcall JSONValueChanged();
	Rest::Backend::Servicetypes::_di_IBackendQueryService __fastcall GetProviderService();
	void __fastcall SetBackendService(const System::UnicodeString Value);
	
protected:
	virtual Rest::Backend::Providers::_di_IAuthAccess __fastcall CreateAuthAccess();
	virtual Data::Bind::Objectscope::TBaseObjectBindSource* __fastcall CreateBindSource();
	virtual Rest::Backend::Servicetypes::TBackendQueryApi* __fastcall InternalCreateBackendServiceAPI();
	virtual Rest::Backend::Servicetypes::TBackendQueryApi* __fastcall InternalCreateIndependentBackendServiceAPI();
	void __fastcall AddJSONChangedEvent(const System::Classes::TNotifyEvent ANotify);
	void __fastcall RemoveJSONChangedEvent(const System::Classes::TNotifyEvent ANotify);
	void __fastcall GetJSONResponse(/* out */ System::Json::TJSONValue* &AJSONValue, /* out */ bool &AHasOwner);
	bool __fastcall HasJSONResponse();
	bool __fastcall HasResponseContent();
	
public:
	__fastcall virtual TCustomBackendQuery(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBackendQuery();
	void __fastcall Execute();
	void __fastcall ClearResult();
	void __fastcall SetJSONResult(System::Json::TJSONArray* const AJSONResult);
	Rest::Backend::Servicetypes::TBackendQueryApi* __fastcall CreateQueryAPI();
	__property System::Classes::TStrings* QueryLines = {read=FQueryLines, write=SetQueryLines};
	__property System::UnicodeString BackendClassName = {read=FBackendClassName, write=SetBackendClassName};
	__property System::UnicodeString BackendService = {read=FBackendService, write=SetBackendService};
	__property System::Json::TJSONArray* JSONResult = {read=FJSONResult};
	__property TSubBackendQueryBindSource* BindSource = {read=FBindSource};
	__property Rest::Backend::Servicetypes::TBackendQueryApi* QueryApi = {read=GetQueryApi};
	__property Rest::Backend::Servicetypes::_di_IBackendQueryService ProviderService = {read=GetProviderService};
private:
	void *__IRESTResponseJSON;	// Rest::Client::IRESTResponseJSON 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {71F5FA19-69CC-4384-AC0A-D6E30AD5CC95}
	operator Rest::Client::_di_IRESTResponseJSON()
	{
		Rest::Client::_di_IRESTResponseJSON intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Client::IRESTResponseJSON*(void) { return (Rest::Client::IRESTResponseJSON*)&__IRESTResponseJSON; }
	#endif
	
};


class PASCALIMPLEMENTATION TBackendQuery : public TCustomBackendQuery
{
	typedef TCustomBackendQuery inherited;
	
__published:
	__property Provider;
	__property Auth;
	__property BackendClassName = {default=0};
	__property BackendService = {default=0};
	__property QueryLines;
	__property BindSource;
public:
	/* TCustomBackendQuery.Create */ inline __fastcall virtual TBackendQuery(System::Classes::TComponent* AOwner) : TCustomBackendQuery(AOwner) { }
	/* TCustomBackendQuery.Destroy */ inline __fastcall virtual ~TBackendQuery() { }
	
};


class PASCALIMPLEMENTATION TBackendQueryAdapter : public Rest::Bindsource::TRESTComponentAdapter
{
	typedef Rest::Bindsource::TRESTComponentAdapter inherited;
	
	
public:
	class DELPHICLASS TNotify;
	class PASCALIMPLEMENTATION TNotify : public Rest::Bindsource::TRESTComponentNotify
	{
		typedef Rest::Bindsource::TRESTComponentNotify inherited;
		
	private:
		TBackendQueryAdapter* FAdapter;
		
	protected:
		__fastcall TNotify(TBackendQueryAdapter* const AAdapter);
		
	public:
		virtual void __fastcall PropertyValueChanged(System::TObject* Sender);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
	
	
private:
	TCustomBackendQuery* FQuery;
	TNotify* FNotify;
	void __fastcall SetQuery(TCustomBackendQuery* const AQuery);
	void __fastcall AddPropertyFields();
	
protected:
	virtual void __fastcall DoChangePosting();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall GetCanActivate();
	virtual void __fastcall AddFields();
	virtual Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetSource();
	
public:
	__fastcall virtual TBackendQueryAdapter(System::Classes::TComponent* AComponent);
	__fastcall virtual ~TBackendQueryAdapter();
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList);
	__property TCustomBackendQuery* Query = {read=FQuery, write=SetQuery};
};


class PASCALIMPLEMENTATION TCustomBackendQueryBindSource : public Rest::Bindsource::TRESTComponentBindSource
{
	typedef Rest::Bindsource::TRESTComponentBindSource inherited;
	
private:
	TBackendQueryAdapter* FAdapter;
	TCustomBackendQuery* __fastcall GetQuery();
	void __fastcall SetQuery(TCustomBackendQuery* const AValue);
	
protected:
	virtual Rest::Bindsource::TRESTComponentAdapter* __fastcall CreateAdapter();
	
public:
	__property TCustomBackendQuery* Query = {read=GetQuery, write=SetQuery};
	__property TBackendQueryAdapter* Adapter = {read=FAdapter};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TCustomBackendQueryBindSource(System::Classes::TComponent* AOwner) : Rest::Bindsource::TRESTComponentBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TCustomBackendQueryBindSource() { }
	
};


class PASCALIMPLEMENTATION TSubBackendQueryBindSource : public TCustomBackendQueryBindSource
{
	typedef TCustomBackendQueryBindSource inherited;
	
__published:
	__property AutoActivate = {default=1};
	__property AutoEdit = {default=1};
	__property AutoPost = {default=1};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TSubBackendQueryBindSource(System::Classes::TComponent* AOwner) : TCustomBackendQueryBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TSubBackendQueryBindSource() { }
	
};


class PASCALIMPLEMENTATION TCustomBackendPush : public Rest::Backend::Bindsource::TBackendBindSourceComponentAuth__2<Rest::Backend::Pushtypes::_di_IBackendPushService,Rest::Backend::Pushtypes::TBackendPushApi*>
{
	typedef Rest::Backend::Bindsource::TBackendBindSourceComponentAuth__2<Rest::Backend::Pushtypes::_di_IBackendPushService,Rest::Backend::Pushtypes::TBackendPushApi*> inherited;
	friend class TPushSenderAdapter;
	
	
public:
	typedef System::Classes::TNotifyEvent TSendEvent;
	
	typedef System::Classes::TNotifyEvent TSendingEvent;
	
	class DELPHICLASS TExtrasItem;
	class PASCALIMPLEMENTATION TExtrasItem : public System::Classes::TCollectionItem
	{
		typedef System::Classes::TCollectionItem inherited;
		
	private:
		System::UnicodeString FName;
		System::UnicodeString FValue;
		
	protected:
		void __fastcall SetName(const System::UnicodeString AValue);
		void __fastcall SetValue(const System::UnicodeString AValue);
		
	public:
		virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
		virtual System::UnicodeString __fastcall ToString();
		virtual System::UnicodeString __fastcall GetDisplayName();
		
	__published:
		__property System::UnicodeString Name = {read=FName, write=SetName};
		__property System::UnicodeString Value = {read=FValue, write=SetValue};
	public:
		/* TCollectionItem.Create */ inline __fastcall virtual TExtrasItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
		/* TCollectionItem.Destroy */ inline __fastcall virtual ~TExtrasItem() { }
		
	};
	
	
	class DELPHICLASS TExtrasCollection;
	class PASCALIMPLEMENTATION TExtrasCollection : public System::Classes::TOwnedCollection
	{
		typedef System::Classes::TOwnedCollection inherited;
		
		
	private:
		class DELPHICLASS TEnumerator;
		class PASCALIMPLEMENTATION TEnumerator : public System::Classes::TCollectionEnumerator
		{
			typedef System::Classes::TCollectionEnumerator inherited;
			
		public:
			HIDESBASE TCustomBackendPush::TExtrasItem* __fastcall GetCurrent();
			__property TCustomBackendPush::TExtrasItem* Current = {read=GetCurrent};
		public:
			/* TCollectionEnumerator.Create */ inline __fastcall TEnumerator(System::Classes::TCollection* ACollection) : System::Classes::TCollectionEnumerator(ACollection) { }
			
		public:
			/* TObject.Destroy */ inline __fastcall virtual ~TEnumerator() { }
			
		};
		
		
		
public:
		TCustomBackendPush::TExtrasItem* operator[](int AIndex) { return this->Items[AIndex]; }
		
	protected:
		HIDESBASE TCustomBackendPush::TExtrasItem* __fastcall GetItem(int AIndex);
		HIDESBASE void __fastcall SetItem(int AIndex, TCustomBackendPush::TExtrasItem* const AValue);
		DYNAMIC int __fastcall GetAttrCount();
		DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
		DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
		virtual void __fastcall Update(System::Classes::TCollectionItem* AItem);
		
	public:
		__fastcall TExtrasCollection(System::Classes::TComponent* const AOwner);
		void __fastcall UpdateExtras(Rest::Backend::Pushtypes::TPushData::TExtras* const AExtras);
		HIDESBASE TEnumerator* __fastcall GetEnumerator();
		__property TCustomBackendPush::TExtrasItem* Items[int AIndex] = {read=GetItem, write=SetItem/*, default*/};
	public:
		/* TCollection.Destroy */ inline __fastcall virtual ~TExtrasCollection() { }
		
	};
	
	
	
private:
	class DELPHICLASS TNotify;
	class PASCALIMPLEMENTATION TNotify : public Rest::Bindsource::TRESTComponentNotify
	{
		typedef Rest::Bindsource::TRESTComponentNotify inherited;
		
	public:
		virtual void __fastcall ExtrasListChanged(System::TObject* Sender);
	public:
		/* TObject.Create */ inline __fastcall TNotify() : Rest::Bindsource::TRESTComponentNotify() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
	
	typedef Rest::Bindsource::TRESTComponentNotifyList__1<TNotify*>* TNotifyList;
	
	
private:
	Rest::Bindsource::TRESTComponentNotifyList__1<TNotify*>* FNotifyList;
	Rest::Backend::Pushtypes::TPushData* FPushData;
	TExtrasCollection* FExtras;
	TSubPushSenderBindSource* FBindSource;
	System::Classes::TNotifyEvent FOnSending;
	System::Classes::TNotifyEvent FOnSend;
	System::Classes::TStrings* FTarget;
	Rest::Backend::Pushtypes::_di_IBackendPushService __fastcall GetProviderService();
	void __fastcall PropertyValueChanged();
	void __fastcall ExtrasListChanged();
	Rest::Backend::Pushtypes::TBackendPushApi* __fastcall GetPushAPI();
	void __fastcall SetAPS(Rest::Backend::Pushtypes::TPushData::TAPS* const Value);
	void __fastcall SetMessage(const System::UnicodeString Value);
	Rest::Backend::Pushtypes::TPushData::TAPS* __fastcall GetAPS();
	System::UnicodeString __fastcall GetMessage();
	Rest::Backend::Pushtypes::TPushData::TGCM* __fastcall GetGCM();
	void __fastcall SetGCM(Rest::Backend::Pushtypes::TPushData::TGCM* const Value);
	void __fastcall SetExtras(TExtrasCollection* const Value);
	void __fastcall SetTarget(System::Classes::TStrings* const Value);
	
protected:
	virtual Rest::Backend::Pushtypes::TBackendPushApi* __fastcall InternalCreateBackendServiceAPI();
	virtual Rest::Backend::Pushtypes::TBackendPushApi* __fastcall InternalCreateIndependentBackendServiceAPI();
	virtual Data::Bind::Objectscope::TBaseObjectBindSource* __fastcall CreateBindSource();
	virtual void __fastcall DoSend();
	virtual void __fastcall DoSending();
	virtual Rest::Backend::Providers::_di_IAuthAccess __fastcall CreateAuthAccess();
	
public:
	__fastcall virtual TCustomBackendPush(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBackendPush();
	void __fastcall PushData(Rest::Backend::Pushtypes::TPushData* const AData)/* overload */;
	void __fastcall PushData(Rest::Backend::Pushtypes::TPushData* const AData, System::Json::TJSONObject* const ATarget)/* overload */;
	void __fastcall Push()/* overload */;
	__property Rest::Backend::Pushtypes::TPushData::TAPS* APS = {read=GetAPS, write=SetAPS};
	__property Rest::Backend::Pushtypes::TPushData::TGCM* GCM = {read=GetGCM, write=SetGCM};
	__property TExtrasCollection* Extras = {read=FExtras, write=SetExtras};
	__property System::UnicodeString Message = {read=GetMessage, write=SetMessage};
	__property TSubPushSenderBindSource* BindSource = {read=FBindSource};
	__property System::Classes::TNotifyEvent OnSending = {read=FOnSending, write=FOnSending};
	__property System::Classes::TNotifyEvent OnSend = {read=FOnSend, write=FOnSend};
	__property Rest::Backend::Pushtypes::TBackendPushApi* PushAPI = {read=GetPushAPI};
	__property System::Classes::TStrings* Target = {read=FTarget, write=SetTarget};
	__property Rest::Backend::Pushtypes::_di_IBackendPushService ProviderService = {read=GetProviderService};
};


class PASCALIMPLEMENTATION TBackendPush : public TCustomBackendPush
{
	typedef TCustomBackendPush inherited;
	
__published:
	__property Provider;
	__property Auth;
	__property Message = {default=0};
	__property APS;
	__property GCM;
	__property Extras;
	__property BindSource;
	__property Target;
public:
	/* TCustomBackendPush.Create */ inline __fastcall virtual TBackendPush(System::Classes::TComponent* AOwner) : TCustomBackendPush(AOwner) { }
	/* TCustomBackendPush.Destroy */ inline __fastcall virtual ~TBackendPush() { }
	
};


class PASCALIMPLEMENTATION TPushSenderAdapter : public Rest::Bindsource::TRESTComponentAdapter
{
	typedef Rest::Bindsource::TRESTComponentAdapter inherited;
	
	
public:
	class DELPHICLASS TNotify;
	class PASCALIMPLEMENTATION TNotify : public TCustomBackendPush::TNotify
	{
		typedef TCustomBackendPush::TNotify inherited;
		
	private:
		TPushSenderAdapter* FAdapter;
		
	protected:
		__fastcall TNotify(TPushSenderAdapter* const AAdapter);
		
	public:
		virtual void __fastcall PropertyValueChanged(System::TObject* Sender);
		virtual void __fastcall ExtrasListChanged(System::TObject* Sender);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
	
	
private:
	TCustomBackendPush* FComponent;
	TNotify* FNotify;
	void __fastcall SetPushSender(TCustomBackendPush* const APushSender);
	void __fastcall AddPropertyFields();
	void __fastcall AddParameterFields();
	void __fastcall ExtrasListChanged();
	
protected:
	virtual void __fastcall DoChangePosting();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall GetCanActivate();
	virtual void __fastcall AddFields();
	virtual Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetSource();
	
public:
	__fastcall virtual TPushSenderAdapter(System::Classes::TComponent* AComponent);
	__fastcall virtual ~TPushSenderAdapter();
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList);
	__property TCustomBackendPush* PushSender = {read=FComponent, write=SetPushSender};
};


class PASCALIMPLEMENTATION TCustomPushSenderBindSource : public Rest::Bindsource::TRESTComponentBindSource
{
	typedef Rest::Bindsource::TRESTComponentBindSource inherited;
	
private:
	TPushSenderAdapter* FAdapter;
	HIDESBASE TCustomBackendPush* __fastcall GetComponent();
	void __fastcall SetComponent(TCustomBackendPush* const AValue);
	
protected:
	virtual Rest::Bindsource::TRESTComponentAdapter* __fastcall CreateAdapter();
	
public:
	__property TCustomBackendPush* Component = {read=GetComponent, write=SetComponent};
	__property TPushSenderAdapter* Adapter = {read=FAdapter};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TCustomPushSenderBindSource(System::Classes::TComponent* AOwner) : Rest::Bindsource::TRESTComponentBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TCustomPushSenderBindSource() { }
	
};


class PASCALIMPLEMENTATION TSubPushSenderBindSource : public TCustomPushSenderBindSource
{
	typedef TCustomPushSenderBindSource inherited;
	
__published:
	__property AutoActivate = {default=1};
	__property AutoEdit = {default=1};
	__property AutoPost = {default=1};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TSubPushSenderBindSource(System::Classes::TComponent* AOwner) : TCustomPushSenderBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TSubPushSenderBindSource() { }
	
};


class PASCALIMPLEMENTATION TCustomBackendAuth : public Rest::Backend::Bindsource::TBackendBindSourceComponent__2<Rest::Backend::Servicetypes::_di_IBackendAuthService,Rest::Backend::Servicetypes::TBackendAuthApi*>
{
	typedef Rest::Backend::Bindsource::TBackendBindSourceComponent__2<Rest::Backend::Servicetypes::_di_IBackendAuthService,Rest::Backend::Servicetypes::TBackendAuthApi*> inherited;
	
	
public:
	typedef System::Classes::TNotifyEvent TSendEvent;
	
	typedef System::Classes::TNotifyEvent TSendingEvent;
	
	class DELPHICLASS TUserDetailsItem;
	class PASCALIMPLEMENTATION TUserDetailsItem : public System::Classes::TCollectionItem
	{
		typedef System::Classes::TCollectionItem inherited;
		
	private:
		System::UnicodeString FName;
		System::UnicodeString FValue;
		
	protected:
		void __fastcall SetName(const System::UnicodeString AValue);
		void __fastcall SetValue(const System::UnicodeString AValue);
		
	public:
		virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
		virtual System::UnicodeString __fastcall ToString();
		virtual System::UnicodeString __fastcall GetDisplayName();
		
	__published:
		__property System::UnicodeString Name = {read=FName, write=SetName};
		__property System::UnicodeString Value = {read=FValue, write=SetValue};
	public:
		/* TCollectionItem.Create */ inline __fastcall virtual TUserDetailsItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
		/* TCollectionItem.Destroy */ inline __fastcall virtual ~TUserDetailsItem() { }
		
	};
	
	
	class DELPHICLASS TUserDetailsCollection;
	class PASCALIMPLEMENTATION TUserDetailsCollection : public System::Classes::TOwnedCollection
	{
		typedef System::Classes::TOwnedCollection inherited;
		
		
	private:
		class DELPHICLASS TEnumerator;
		class PASCALIMPLEMENTATION TEnumerator : public System::Classes::TCollectionEnumerator
		{
			typedef System::Classes::TCollectionEnumerator inherited;
			
		public:
			HIDESBASE TCustomBackendAuth::TUserDetailsItem* __fastcall GetCurrent();
			__property TCustomBackendAuth::TUserDetailsItem* Current = {read=GetCurrent};
		public:
			/* TCollectionEnumerator.Create */ inline __fastcall TEnumerator(System::Classes::TCollection* ACollection) : System::Classes::TCollectionEnumerator(ACollection) { }
			
		public:
			/* TObject.Destroy */ inline __fastcall virtual ~TEnumerator() { }
			
		};
		
		
		
public:
		TCustomBackendAuth::TUserDetailsItem* operator[](int AIndex) { return this->Items[AIndex]; }
		
	protected:
		HIDESBASE TCustomBackendAuth::TUserDetailsItem* __fastcall GetItem(int AIndex);
		HIDESBASE void __fastcall SetItem(int AIndex, TCustomBackendAuth::TUserDetailsItem* const AValue);
		DYNAMIC int __fastcall GetAttrCount();
		DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
		DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
		virtual void __fastcall Update(System::Classes::TCollectionItem* AItem);
		
	public:
		__fastcall TUserDetailsCollection(System::Classes::TComponent* const AOwner);
		void __fastcall ClearValues();
		HIDESBASE TEnumerator* __fastcall GetEnumerator();
		__property TCustomBackendAuth::TUserDetailsItem* Items[int AIndex] = {read=GetItem, write=SetItem/*, default*/};
	public:
		/* TCollection.Destroy */ inline __fastcall virtual ~TUserDetailsCollection() { }
		
	};
	
	
	class DELPHICLASS TNotify;
	class PASCALIMPLEMENTATION TNotify : public Rest::Bindsource::TRESTComponentNotify
	{
		typedef Rest::Bindsource::TRESTComponentNotify inherited;
		
	public:
		virtual void __fastcall UserDetailsChanged(System::TObject* Sender);
	public:
		/* TObject.Create */ inline __fastcall TNotify() : Rest::Bindsource::TRESTComponentNotify() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
	
	typedef Rest::Bindsource::TRESTComponentNotifyList__1<TNotify*>* TNotifyList;
	
	typedef void __fastcall (__closure *TLoginPromptEvent)(System::TObject* Sender, System::UnicodeString &AUserName, System::UnicodeString &APassword);
	
	
private:
	Rest::Backend::Metatypes::TBackendEntityValue FLoggedInValue;
	Rest::Bindsource::TRESTComponentNotifyList__1<TNotify*>* FNotifyList;
	TUserDetailsCollection* FUserDetails;
	TSubLoginBindSource* FBindSource;
	System::UnicodeString FPassword;
	System::UnicodeString FUserName;
	bool FLoginPrompt;
	System::Generics::Collections::TList__1<Rest::Backend::Providers::_di_IAuthAccess>* FAuthAccess;
	Rest::Backend::Providers::TBackendAuthentication FAuthentication;
	Rest::Backend::Providers::TBackendDefaultAuthentication FDefaultAuthentication;
	System::Classes::TNotifyEvent FOnLoggedIn;
	System::Classes::TNotifyEvent FOnLoggingIn;
	System::Classes::TNotifyEvent FOnSigningUp;
	System::Classes::TNotifyEvent FOnSignedUp;
	System::Classes::TNotifyEvent FOnLoggedOut;
	TLoginPromptEvent FOnLoginPrompt;
	Rest::Backend::Servicetypes::_di_IBackendAuthService __fastcall GetProviderService();
	void __fastcall PropertyValueChanged();
	void __fastcall UserDetailsChanged();
	Rest::Backend::Servicetypes::TBackendAuthApi* __fastcall GetAuthApi();
	void __fastcall SetUserDetails(TUserDetailsCollection* const Value);
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	void __fastcall DoAuthAccess(const System::DelphiInterface<System::Sysutils::TProc__1<Rest::Backend::Providers::_di_IAuthAccess> > AProc);
	void __fastcall ValidateAuthAccess();
	bool __fastcall GetLoggedIn();
	System::UnicodeString __fastcall GetLoggedInToken();
	System::UnicodeString __fastcall GetLoggedInUserName();
	void __fastcall CheckLoggedIn();
	
protected:
	void __fastcall RegisterForAuth(const Rest::Backend::Providers::_di_IAuthAccess AAuthAccess);
	void __fastcall UnregisterForAuth(const Rest::Backend::Providers::_di_IAuthAccess AAuthAccess);
	virtual Rest::Backend::Servicetypes::TBackendAuthApi* __fastcall InternalCreateBackendServiceAPI();
	virtual Rest::Backend::Servicetypes::TBackendAuthApi* __fastcall InternalCreateIndependentBackendServiceAPI();
	virtual Data::Bind::Objectscope::TBaseObjectBindSource* __fastcall CreateBindSource();
	void __fastcall SetAuthentication(const Rest::Backend::Providers::TBackendAuthentication Value);
	void __fastcall SetDefaultAuthentication(const Rest::Backend::Providers::TBackendDefaultAuthentication Value);
	virtual bool __fastcall LoginDialog(/* out */ System::UnicodeString &AUserName, /* out */ System::UnicodeString &APassword);
	virtual void __fastcall DoLoggedIn();
	virtual void __fastcall DoLoggingIn();
	virtual void __fastcall DoLoggedOut();
	virtual bool __fastcall DoLogInPrompt(/* out */ System::UnicodeString &AUserName, /* out */ System::UnicodeString &APassword);
	virtual void __fastcall DoSignedUp();
	virtual void __fastcall DoSigningUp();
	virtual void __fastcall ProviderChanged();
	virtual void __fastcall Loaded();
	
public:
	__fastcall virtual TCustomBackendAuth(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBackendAuth();
	void __fastcall Login()/* overload */;
	void __fastcall Login(const Rest::Backend::Metatypes::TBackendEntityValue &ALogin, System::Json::TJSONObject* const AJSON)/* overload */;
	void __fastcall Signup();
	void __fastcall Logout();
	void __fastcall UpdateUserDetails();
	void __fastcall UserDetailsToJSON(System::Json::TJSONObject* const AJSON);
	void __fastcall JSONToUserDetails(System::Json::TJSONObject* const AJSON);
	void __fastcall ClearFieldValues();
	__property TUserDetailsCollection* UserDetails = {read=FUserDetails, write=SetUserDetails};
	__property System::UnicodeString UserName = {read=FUserName, write=SetUserName};
	__property System::UnicodeString Password = {read=FPassword, write=SetPassword};
	__property bool LoginPrompt = {read=FLoginPrompt, write=FLoginPrompt, nodefault};
	__property TSubLoginBindSource* BindSource = {read=FBindSource};
	__property Rest::Backend::Servicetypes::TBackendAuthApi* AuthAPI = {read=GetAuthApi};
	__property Rest::Backend::Servicetypes::_di_IBackendAuthService ProviderService = {read=GetProviderService};
	__property Rest::Backend::Providers::TBackendAuthentication Authentication = {read=FAuthentication, write=SetAuthentication, default=0};
	__property Rest::Backend::Providers::TBackendDefaultAuthentication DefaultAuthentication = {read=FDefaultAuthentication, write=SetDefaultAuthentication, default=4};
	__property bool LoggedIn = {read=GetLoggedIn, nodefault};
	__property System::UnicodeString LoggedInToken = {read=GetLoggedInToken};
	__property System::UnicodeString LoggedInUserName = {read=GetLoggedInUserName};
	__property TLoginPromptEvent OnLoginPrompt = {read=FOnLoginPrompt, write=FOnLoginPrompt};
	__property System::Classes::TNotifyEvent OnLoggingIn = {read=FOnLoggingIn, write=FOnLoggingIn};
	__property System::Classes::TNotifyEvent OnLoggedIn = {read=FOnLoggedIn, write=FOnLoggedIn};
	__property System::Classes::TNotifyEvent OnSigningUp = {read=FOnSigningUp, write=FOnSigningUp};
	__property System::Classes::TNotifyEvent OnSignedUp = {read=FOnSignedUp, write=FOnSignedUp};
	__property System::Classes::TNotifyEvent OnLoggedOut = {read=FOnLoggedOut, write=FOnLoggedOut};
	__property Rest::Backend::Metatypes::TBackendEntityValue LoggedInValue = {read=FLoggedInValue};
private:
	void *__IBackendAuthReg;	// Rest::Backend::Providers::IBackendAuthReg 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6EB1DC55-C0C7-434D-8CE7-CD6F215A1B6F}
	operator Rest::Backend::Providers::_di_IBackendAuthReg()
	{
		Rest::Backend::Providers::_di_IBackendAuthReg intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Providers::IBackendAuthReg*(void) { return (Rest::Backend::Providers::IBackendAuthReg*)&__IBackendAuthReg; }
	#endif
	
};


class PASCALIMPLEMENTATION TBackendAuth : public TCustomBackendAuth
{
	typedef TCustomBackendAuth inherited;
	
__published:
	__property Provider;
	__property UserName = {default=0};
	__property Password = {default=0};
	__property LoginPrompt;
	__property UserDetails;
	__property BindSource;
	__property Authentication = {default=0};
	__property DefaultAuthentication = {default=4};
	__property OnLoginPrompt;
	__property OnLoggingIn;
	__property OnLoggedIn;
	__property OnSigningUp;
	__property OnSignedUp;
	__property OnLoggedOut;
public:
	/* TCustomBackendAuth.Create */ inline __fastcall virtual TBackendAuth(System::Classes::TComponent* AOwner) : TCustomBackendAuth(AOwner) { }
	/* TCustomBackendAuth.Destroy */ inline __fastcall virtual ~TBackendAuth() { }
	
};


class PASCALIMPLEMENTATION TBackendAuthAdapter : public Rest::Bindsource::TRESTComponentAdapter
{
	typedef Rest::Bindsource::TRESTComponentAdapter inherited;
	
	
public:
	class DELPHICLASS TNotify;
	class PASCALIMPLEMENTATION TNotify : public TCustomBackendAuth::TNotify
	{
		typedef TCustomBackendAuth::TNotify inherited;
		
	private:
		TBackendAuthAdapter* FAdapter;
		
	protected:
		__fastcall TNotify(TBackendAuthAdapter* const AAdapter);
		
	public:
		virtual void __fastcall PropertyValueChanged(System::TObject* Sender);
		virtual void __fastcall UserDetailsChanged(System::TObject* Sender);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
	
	
private:
	TCustomBackendAuth* FComponent;
	TNotify* FNotify;
	void __fastcall SetBackendAuth(TCustomBackendAuth* const ALogin);
	void __fastcall AddPropertyFields();
	void __fastcall AddParameterFields();
	void __fastcall UserDetailsChanged();
	
protected:
	virtual void __fastcall DoChangePosting();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall GetCanActivate();
	virtual void __fastcall AddFields();
	virtual Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetSource();
	
public:
	__fastcall virtual TBackendAuthAdapter(System::Classes::TComponent* AComponent);
	__fastcall virtual ~TBackendAuthAdapter();
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList);
	__property TCustomBackendAuth* BackendAuth = {read=FComponent, write=SetBackendAuth};
};


class PASCALIMPLEMENTATION TCustomLoginBindSource : public Rest::Bindsource::TRESTComponentBindSource
{
	typedef Rest::Bindsource::TRESTComponentBindSource inherited;
	
private:
	TBackendAuthAdapter* FAdapter;
	HIDESBASE TCustomBackendAuth* __fastcall GetComponent();
	void __fastcall SetComponent(TCustomBackendAuth* const AValue);
	
protected:
	virtual Rest::Bindsource::TRESTComponentAdapter* __fastcall CreateAdapter();
	
public:
	__property TCustomBackendAuth* Component = {read=GetComponent, write=SetComponent};
	__property TBackendAuthAdapter* Adapter = {read=FAdapter};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TCustomLoginBindSource(System::Classes::TComponent* AOwner) : Rest::Bindsource::TRESTComponentBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TCustomLoginBindSource() { }
	
};


class PASCALIMPLEMENTATION TSubLoginBindSource : public TCustomLoginBindSource
{
	typedef TCustomLoginBindSource inherited;
	
__published:
	__property AutoActivate = {default=1};
	__property AutoEdit = {default=1};
	__property AutoPost = {default=1};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TSubLoginBindSource(System::Classes::TComponent* AOwner) : TCustomLoginBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TSubLoginBindSource() { }
	
};


class PASCALIMPLEMENTATION TAuthAccess : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::DelphiInterface<System::Sysutils::TFunc__1<Rest::Backend::Servicetypes::_di_IBackendAuthenticationApi> > FAuthentication;
	Rest::Backend::Providers::_di_IBackendServiceComponent FComponent;
	void __fastcall Login(const Rest::Backend::Metatypes::TBackendEntityValue &ALogin);
	void __fastcall Logout();
	void __fastcall SetAuthentication(const Rest::Backend::Providers::TBackendAuthentication Value);
	void __fastcall SetDefaultAuthentication(const Rest::Backend::Providers::TBackendDefaultAuthentication Value);
	Rest::Backend::Providers::_di_IBackendProvider __fastcall GetProvider();
	
public:
	__fastcall TAuthAccess(const Rest::Backend::Providers::_di_IBackendServiceComponent AComponent, const System::DelphiInterface<System::Sysutils::TFunc__1<Rest::Backend::Servicetypes::_di_IBackendAuthenticationApi> > AAuthentication);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAuthAccess() { }
	
private:
	void *__IAuthAccess;	// Rest::Backend::Providers::IAuthAccess 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E4F2AAC7-A81B-40E5-AF79-F60505B3C0A9}
	operator Rest::Backend::Providers::_di_IAuthAccess()
	{
		Rest::Backend::Providers::_di_IAuthAccess intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Providers::IAuthAccess*(void) { return (Rest::Backend::Providers::IAuthAccess*)&__IAuthAccess; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Servicecomponents */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_SERVICECOMPONENTS)
using namespace Rest::Backend::Servicecomponents;
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
#endif	// Rest_Backend_ServicecomponentsHPP
