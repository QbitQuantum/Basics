// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Tether.AppProfile.pas' rev: 34.00 (Windows)

#ifndef System_Tether_AppprofileHPP
#define System_Tether_AppprofileHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <System.Tether.Manager.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Tether
{
namespace Appprofile
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomRemoteItem;
class DELPHICLASS TCustomLocalItem;
class DELPHICLASS TLocalAction;
struct TSimpleValue;
struct TResourceValue;
class DELPHICLASS TLocalResource;
class DELPHICLASS TRemoteAction;
class DELPHICLASS TRemoteResource;
class DELPHICLASS TResourceCollection;
class DELPHICLASS TActionCollection;
class DELPHICLASS TTetheringAppProfile;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TTetheringRemoteItemType : unsigned char { Action, Resource };

enum class DECLSPEC_DENUM TTetheringRemoteKind : unsigned char { Shared, Mirror };

enum class DECLSPEC_DENUM TResourceType : unsigned char { Integer, Single, Double, Int64, Boolean, String };

enum class DECLSPEC_DENUM TRemoteResourceType : unsigned char { Data, Stream };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TCustomRemoteItem : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FName;
	System::UnicodeString FHint;
	TTetheringAppProfile* FProfile;
	System::UnicodeString FRemoteProfileId;
	bool FNotifyUpdates;
	TTetheringRemoteItemType FItemType;
	bool FIsPublic;
	bool FIsTemp;
	TTetheringRemoteKind FKind;
	void __fastcall SetProfile(TTetheringAppProfile* const Value);
	
public:
	__fastcall TCustomRemoteItem();
	__fastcall virtual ~TCustomRemoteItem();
	virtual void __fastcall Broadcast();
	__property System::UnicodeString Hint = {read=FHint, write=FHint};
	__property TTetheringAppProfile* Profile = {read=FProfile, write=SetProfile};
	__property TTetheringRemoteItemType ItemType = {read=FItemType, write=FItemType, nodefault};
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property bool NotifyUpdates = {read=FNotifyUpdates, write=FNotifyUpdates, nodefault};
	__property bool IsPublic = {read=FIsPublic, write=FIsPublic, nodefault};
	__property bool IsTemp = {read=FIsTemp, write=FIsTemp, nodefault};
	__property TTetheringRemoteKind Kind = {read=FKind, write=FKind, default=0};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TCustomLocalItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	System::UnicodeString FHint;
	TTetheringAppProfile* FProfile;
	bool FNotifyUpdates;
	bool FIsPublic;
	TTetheringRemoteKind FKind;
	void __fastcall SetProfile(TTetheringAppProfile* const Value);
	void __fastcall SetName(const System::UnicodeString Value);
	void __fastcall SetIsPublic(const bool Value);
	void __fastcall SetKind(const TTetheringRemoteKind Value);
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall ToBytes();
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall ToBytes();
#endif /* _WIN64 */
	virtual System::Json::TJSONObject* __fastcall MarshalToJSON() = 0 ;
	virtual System::UnicodeString __fastcall ToJsonString();
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__fastcall virtual TCustomLocalItem(System::Classes::TCollection* ACollection);
	virtual void __fastcall Broadcast();
	__property System::UnicodeString Hint = {read=FHint, write=FHint};
	__property TTetheringAppProfile* Profile = {read=FProfile, write=SetProfile};
	__property bool NotifyUpdates = {read=FNotifyUpdates, write=FNotifyUpdates, nodefault};
	
__published:
	__property System::UnicodeString Name = {read=FName, write=SetName};
	__property bool IsPublic = {read=FIsPublic, write=SetIsPublic, nodefault};
	__property TTetheringRemoteKind Kind = {read=FKind, write=SetKind, default=0};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TCustomLocalItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TLocalAction : public TCustomLocalItem
{
	typedef TCustomLocalItem inherited;
	
private:
	System::Classes::TNotifyEvent FOldUpdate;
	System::Classes::TNotifyEvent FOldExecute;
	System::Actions::TContainedAction* FAction;
	bool FActionEnabled;
	System::UnicodeString FActionCaption;
	void __fastcall SetAction(System::Actions::TContainedAction* const Value);
	void __fastcall UpdateActionStatus(System::TObject* Sender);
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	void __fastcall DoExecute(System::TObject* Sender);
	virtual System::Json::TJSONObject* __fastcall MarshalToJSON();
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__fastcall virtual TLocalAction(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TLocalAction();
	
__published:
	__property System::Actions::TContainedAction* Action = {read=FAction, write=SetAction};
	__property NotifyUpdates;
};


struct DECLSPEC_DRECORD TSimpleValue
{
	
public:
	union
	{
		struct 
		{
			bool FBoolean;
		};
		struct 
		{
			__int64 FInt64;
		};
		struct 
		{
			double FDouble;
		};
		struct 
		{
			float FSingle;
		};
		struct 
		{
			int FInteger;
		};
		
	};
};


struct DECLSPEC_DRECORD TResourceValue
{
private:
	TResourceType FDataType;
	System::UnicodeString FString;
	System::Classes::TStream* FStream;
	TSimpleValue FSimpleValue;
	void __fastcall AddToJsonObject(System::Json::TJSONObject* const AJSonObject);
	bool __fastcall GetBoolean();
	double __fastcall GetDouble();
	float __fastcall GetSingle();
	__int64 __fastcall GetInt64();
	int __fastcall GetInteger();
	System::UnicodeString __fastcall GetString();
	
public:
	__fastcall TResourceValue(bool Value)/* overload */;
	__fastcall TResourceValue(__int64 Value)/* overload */;
	__fastcall TResourceValue(int Value)/* overload */;
	__fastcall TResourceValue(double Value)/* overload */;
	__fastcall TResourceValue(float Value)/* overload */;
	__fastcall TResourceValue(const System::UnicodeString Value)/* overload */;
	__fastcall TResourceValue(System::Classes::TStream* const Value)/* overload */;
	static TResourceValue __fastcall _op_Implicit(bool Value);
	static TResourceValue __fastcall _op_Implicit(__int64 Value);
	static TResourceValue __fastcall _op_Implicit(int Value);
	static TResourceValue __fastcall _op_Implicit(double Value);
	static TResourceValue __fastcall _op_Implicit(float Value);
	static TResourceValue __fastcall _op_Implicit(const System::UnicodeString Value);
	static TResourceValue __fastcall _op_Implicit(System::Classes::TStream* const Value);
	__property TResourceType DataType = {read=FDataType, write=FDataType};
	__property System::UnicodeString AsString = {read=GetString};
	__property int AsInteger = {read=GetInteger};
	__property double AsDouble = {read=GetDouble};
	__property __int64 AsInt64 = {read=GetInt64};
	__property float AsSingle = {read=GetSingle};
	__property bool AsBoolean = {read=GetBoolean};
	__property System::Classes::TStream* AsStream = {read=FStream};
	TResourceValue() {}
	
	TResourceValue& operator =(bool Value) { *this = TResourceValue::_op_Implicit(Value); return *this; }
	TResourceValue& operator =(__int64 Value) { *this = TResourceValue::_op_Implicit(Value); return *this; }
	TResourceValue& operator =(int Value) { *this = TResourceValue::_op_Implicit(Value); return *this; }
	TResourceValue& operator =(double Value) { *this = TResourceValue::_op_Implicit(Value); return *this; }
	TResourceValue& operator =(float Value) { *this = TResourceValue::_op_Implicit(Value); return *this; }
	TResourceValue& operator =(const System::UnicodeString Value) { *this = TResourceValue::_op_Implicit(Value); return *this; }
	TResourceValue& operator =(System::Classes::TStream* const Value) { *this = TResourceValue::_op_Implicit(Value); return *this; }
};


typedef void __fastcall (__closure *TResourceUpdatedEvent)(System::TObject* const Sender, TRemoteResource* const AResource);

typedef void __fastcall (__closure *TActionUpdatedEvent)(System::TObject* const Sender, TRemoteAction* const AResource);

typedef void __fastcall (__closure *TAcceptResourceEvent)(System::TObject* const Sender, const System::UnicodeString AProfileId, TCustomRemoteItem* const AResource, bool &AcceptResource);

typedef void __fastcall (__closure *TRemoteProfileUpdateEvent)(System::TObject* const Sender, const System::UnicodeString AProfileId);

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TLocalResource : public TCustomLocalItem
{
	typedef TCustomLocalItem inherited;
	
private:
	TRemoteResourceType FResType;
	TResourceValue FResValue;
	TResourceUpdatedEvent FOnResourceReceived;
	void __fastcall SetValue(const TResourceValue &Value);
	void __fastcall SetResType(const TRemoteResourceType Value);
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual System::Json::TJSONObject* __fastcall MarshalToJSON();
	virtual void __fastcall DoResourceReceived(TRemoteResource* const AResource);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__fastcall virtual TLocalResource(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TLocalResource();
	
__published:
	__property TRemoteResourceType ResType = {read=FResType, write=SetResType, default=0};
	__property TResourceUpdatedEvent OnResourceReceived = {read=FOnResourceReceived, write=FOnResourceReceived};
	
public:
	__property TResourceValue Value = {read=FResValue, write=SetValue};
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TRemoteAction : public TCustomRemoteItem
{
	typedef TCustomRemoteItem inherited;
	
private:
	bool FEnabled;
	System::UnicodeString FCaption;
	System::Classes::TNotifyEvent FOnUpdate;
	
public:
	__fastcall TRemoteAction();
	void __fastcall Execute();
	__property System::UnicodeString Caption = {read=FCaption, write=FCaption};
	
__published:
	__property bool Enabled = {read=FEnabled, write=FEnabled, nodefault};
	__property System::Classes::TNotifyEvent OnUpdate = {read=FOnUpdate, write=FOnUpdate};
public:
	/* TCustomRemoteItem.Destroy */ inline __fastcall virtual ~TRemoteAction() { }
	
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TRemoteResource : public TCustomRemoteItem
{
	typedef TCustomRemoteItem inherited;
	
private:
	TRemoteResourceType FResType;
	TResourceValue FValue;
	System::Json::TJSONObject* __fastcall MarshalToJSON();
	void __fastcall SetValue(const TResourceValue &Value);
	
public:
	__fastcall TRemoteResource();
	__fastcall virtual ~TRemoteResource();
	System::UnicodeString __fastcall ToJsonString();
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall ToBytes();
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall ToBytes();
#endif /* _WIN64 */
	void __fastcall UpdateValue(TResourceType ADataType, System::Json::TJSONValue* const AJSONValue);
	__property TRemoteResourceType ResType = {read=FResType, write=FResType, nodefault};
	__property TResourceValue Value = {read=FValue, write=SetValue};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TResourceCollection : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
protected:
	HIDESBASE TLocalResource* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TLocalResource* Value);
	
public:
	__fastcall TResourceCollection(System::Classes::TComponent* AOwner, System::Classes::TCollectionItemClass ItemClass);
	HIDESBASE TLocalResource* __fastcall Add();
	HIDESBASE TLocalResource* __fastcall Insert(int Index);
	TLocalResource* __fastcall FindByName(const System::UnicodeString AResName);
	__property TLocalResource* Items[int Index] = {read=GetItem, write=SetItem};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TResourceCollection() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TActionCollection : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
protected:
	HIDESBASE TLocalAction* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TLocalAction* Value);
	
public:
	__fastcall TActionCollection(System::Classes::TComponent* AOwner, System::Classes::TCollectionItemClass ItemClass);
	HIDESBASE TLocalAction* __fastcall Add();
	HIDESBASE TLocalAction* __fastcall Insert(int Index);
	TLocalAction* __fastcall FindByName(const System::UnicodeString AnActionName);
	__property TLocalAction* Items[int Index] = {read=GetItem, write=SetItem};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TActionCollection() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> TConnectedProfilePair;

typedef System::Generics::Collections::TPair__2<System::Tether::Manager::TTetheringProfileInfo,TCustomRemoteItem*> TSubscribedResPair;

typedef NativeUInt TRemoteActionHandle;

enum class DECLSPEC_DENUM TRemoteActionState : unsigned char { Running, NotRunning, NotFound };

typedef void __fastcall (__closure *TASyncRemoteActionEvent)(System::TObject* const Sender, const System::UnicodeString ARemoteProfileId, const System::UnicodeString ARemoteActionName, NativeUInt ARemoteActionHandle, bool Success);

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringAppProfile : public System::Tether::Manager::TTetheringProfile
{
	typedef System::Tether::Manager::TTetheringProfile inherited;
	
	
private:
	enum class DECLSPEC_DENUM TTetheringAppCommand : unsigned char { Unknown, Connect, Run, GetActions, GetResources, GetResourceValue, SubscribeResource, UnSubscribeResource, SendStream, SendString, ReverseConnect, RunAsync, GetRemoteActionState, DisconnectProfile };
	
	typedef System::Generics::Collections::TPair__2<System::UnicodeString,TTetheringAppCommand> TTetheringAppCommandPair;
	
	typedef System::Generics::Collections::TPair__2<NativeUInt,System::UnicodeString> TRunningActionsPair;
	
	
public:
	#define TTetheringAppProfile_AppProfileID L"APPLICATION"
	
	
private:
	static const System::WideChar CommandSep = (System::WideChar)(0x24);
	
	static const System::WideChar TokenSep = (System::WideChar)(0x23);
	
	static const System::WideChar InnerSep = (System::WideChar)(0x2a);
	
	static const System::Int8 CommandsLength = System::Int8(0xb);
	
	#define TTetheringAppProfile_ConnectCommand L"CON_PROFIL"
	
	#define TTetheringAppProfile_ReverseConnectCommand L"REV_PROFIL"
	
	#define TTetheringAppProfile_ConnectCommandOKResponse L"RES_OKCON"
	
	#define TTetheringAppProfile_ConnectCommandErrorResponse L"RES_ERCON"
	
	#define TTetheringAppProfile_RunActionCommand L"RUN_ACTION"
	
	#define TTetheringAppProfile_RunActionAsyncCommand L"RUN_ASNACT"
	
	#define TTetheringAppProfile_RunActionResponseErrorCommand L"RES_RUNERR"
	
	#define TTetheringAppProfile_RunActionResponseOKCommand L"RES_RUNOKI"
	
	#define TTetheringAppProfile_GetRemoteActionAsyncStateCommand L"GET_ACTASY"
	
	#define TTetheringAppProfile_GetActionsCommand L"GET_ACTION"
	
	#define TTetheringAppProfile_GetActionsCommandResponse L"RES_GETACT"
	
	#define TTetheringAppProfile_GetResourcesCommand L"GET_RESRCS"
	
	#define TTetheringAppProfile_GetResourcesCommandResponse L"RES_GETRES"
	
	#define TTetheringAppProfile_GetResourceValueCommand L"GET_RESVAL"
	
	#define TTetheringAppProfile_GetResourceValueCommandResponse L"RES_GETVAL"
	
	#define TTetheringAppProfile_GetRemoteActionAsyncStateCommandResponse L"RES_ACTASY"
	
	#define TTetheringAppProfile_GetStreamResourceValueCommandResponse L"RES_GETVST"
	
	#define TTetheringAppProfile_SubscribeResourceCommand L"SUB_RESOUR"
	
	#define TTetheringAppProfile_SubscribeResourceResponseCommand L"RES_SUBSCR"
	
	#define TTetheringAppProfile_UnsubscribeResourceCommand L"UNS_RESOUR"
	
	#define TTetheringAppProfile_UnsubscribeResourceResponseCommand L"RES_UNSUBS"
	
	#define TTetheringAppProfile_NotifyResourceUpdateCommand L"NOT_UPDRES"
	
	#define TTetheringAppProfile_NotifySendResourceCommand L"NOT_SNDRES"
	
	#define TTetheringAppProfile_NotifyRemoteActionEndCommand L"NOT_ACTEND"
	
	#define TTetheringAppProfile_ResponseCommandAlive L"RES_ALIVE"
	
	#define TTetheringAppProfile_ResponseBadCommand L"RES_BADCOM"
	
	#define TTetheringAppProfile_ResponseUnknownResourceCommand L"RES_UNKNOWN"
	
	#define TTetheringAppProfile_DisconnectProfileCommand L"DIS_PROFIL"
	
	#define TTetheringAppProfile_SendStreamCommand L"SND_STREAM"
	
	#define TTetheringAppProfile_SendStreamOkResponse L"SND_STROK"
	
	#define TTetheringAppProfile_SendStreamContentCommand L"SND_STRCNT"
	
	#define TTetheringAppProfile_SendStreamContentOKResponse L"RES_STRCNT"
	
	#define TTetheringAppProfile_SendStreamContentErrorResponse L"RES_ERRSCN"
	
	#define TTetheringAppProfile_SendStringCommand L"SND_STRING"
	
	#define TTetheringAppProfile_SendStringOkResponse L"SND_STRGOK"
	
	#define TTetheringAppProfile_SendStringContentOKResponse L"RES_STRGCNT"
	
	#define TTetheringAppProfile_SendStringContentErrorResponse L"RES_ERRSTCN"
	
	#define TTetheringAppProfile_NotifyProfileUpdateCommand L"NOT_UPDPRO"
	
	TActionCollection* FSharedActions;
	TResourceCollection* FSharedResources;
	System::Generics::Collections::TObjectDictionary__2<System::Tether::Manager::TTetheringProfileInfo,System::Generics::Collections::TObjectList__1<TCustomRemoteItem*>*>* FRemoteItems;
	System::Generics::Collections::TObjectDictionary__2<TCustomLocalItem*,System::Classes::TStringList*>* FSubscribedProfiles;
	System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::Tether::Manager::TTetheringProfileInfo,TCustomRemoteItem*> >* FSubscribedRemoteProfiles;
	System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> >* FConnectedManagerProfileIds;
	TResourceUpdatedEvent FOnResourceUpdated;
	TActionUpdatedEvent FOnActionUpdated;
	TAcceptResourceEvent FOnAcceptResource;
	TResourceUpdatedEvent FOnResourceReceived;
	TRemoteProfileUpdateEvent FOnRemoteProfileUpdate;
	bool FNotifyProfileUpdates;
	TASyncRemoteActionEvent FOnASyncRemoteActionEnd;
	System::Generics::Collections::TThreadList__1<System::Generics::Collections::TPair__2<NativeUInt,System::UnicodeString> >* FRunningActions;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TTetheringAppCommand>* FAppCommandMap;
	bool __fastcall GetRemoteActions(const System::Tether::Manager::TTetheringProfileInfo &AProfile);
	void __fastcall GetRemoteResources(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString AProtocolType, const System::UnicodeString AnAdapterType);
	void __fastcall AutoSubscribeGroup(const System::Tether::Manager::TTetheringProfileInfo &AProfile);
	bool __fastcall FindProfileFromRemoteItem(TCustomRemoteItem* const ARemoteItem, System::Tether::Manager::TTetheringProfileInfo &Profile);
	TLocalResource* __fastcall FindResourceByName(const System::UnicodeString AResName, TResourceCollection* const ResList)/* overload */;
	TLocalAction* __fastcall FindActionByName(const System::UnicodeString AnActionName);
	TCustomRemoteItem* __fastcall FindRemoteItemByName(const System::UnicodeString AItemName, System::Generics::Collections::TList__1<TCustomRemoteItem*>* const ResList);
	TRemoteResource* __fastcall InternalGetRemoteResourceValue(TRemoteResource* const ARemoteRes, const System::Tether::Manager::TTetheringProfileInfo &AProfile);
	bool __fastcall InternalRunRemoteAction(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString AnActionName);
	NativeUInt __fastcall InternalRunRemoteActionAsync(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString AnActionName);
	TRemoteActionState __fastcall InternalGetRemoteActionAsyncState(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString AnAction);
	void __fastcall DeleteRemoteItemsOfType(TTetheringRemoteItemType ARemoteItemType, System::Generics::Collections::TObjectList__1<TCustomRemoteItem*>* const AList);
	void __fastcall UnSubscribeAndDeleteRemoteResources(const System::Tether::Manager::TTetheringProfileInfo &AProfile, System::Generics::Collections::TObjectList__1<TCustomRemoteItem*>* const RemoteItems, System::Classes::TStringList* &UnsubscribedResources);
	System::UnicodeString __fastcall FindProfileManager(System::UnicodeString AProfileId);
	TRemoteResource* __fastcall CreateRemoteTempResource(TRemoteResourceType AResourceType, const System::UnicodeString Description, const System::UnicodeString Data = System::UnicodeString(), System::Classes::TStream* const AStream = (System::Classes::TStream*)(0x0));
	TActionCollection* __fastcall GetSharedActions();
	void __fastcall SetSharedActions(TActionCollection* const Value);
	TResourceCollection* __fastcall GetSharedResources();
	void __fastcall SetSharedResources(TResourceCollection* const Value);
#ifndef _WIN64
	TRemoteAction* __fastcall UpdateActionFromJSON(TRemoteAction* const ARemoteAction, const System::DynamicArray<System::Byte> ResValue, int StartPos);
	TRemoteResource* __fastcall UpdateResourceFromJSON(TRemoteResource* const ARemoteRes, const System::DynamicArray<System::Byte> ResValue, int StartPos);
#else /* _WIN64 */
	TRemoteAction* __fastcall UpdateActionFromJSON(TRemoteAction* const ARemoteAction, const System::TArray__1<System::Byte> ResValue, int StartPos);
	TRemoteResource* __fastcall UpdateResourceFromJSON(TRemoteResource* const ARemoteRes, const System::TArray__1<System::Byte> ResValue, int StartPos);
#endif /* _WIN64 */
	
protected:
#ifndef _WIN64
	virtual void __fastcall DoOnIncomingData(System::Tether::Manager::TTetheringProtocol* const AProtocol, const System::DynamicArray<System::Byte> AData);
#else /* _WIN64 */
	virtual void __fastcall DoOnIncomingData(System::Tether::Manager::TTetheringProtocol* const AProtocol, const System::TArray__1<System::Byte> AData);
#endif /* _WIN64 */
	virtual void __fastcall DoOnDisconnect(const System::Tether::Manager::TTetheringProfileInfo &AProfileInfo);
	virtual void __fastcall OnStreamReceived(System::TObject* const Sender, const System::UnicodeString AProfileId, System::Classes::TStream* const AStream, const System::UnicodeString ADescription);
	virtual void __fastcall OnStringReceived(System::TObject* const Sender, const System::UnicodeString AProfileId, const System::UnicodeString AString, const System::UnicodeString ADescription);
	virtual System::UnicodeString __fastcall GetProfileType();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall DoResourceReceived(TRemoteResource* AResource);
	virtual void __fastcall DoAcceptResource(const System::UnicodeString AProfileId, TCustomRemoteItem* AResource, bool &AcceptResource);
	virtual void __fastcall DoRemoteProfileUpdate(const System::UnicodeString AProfileId);
	virtual void __fastcall DoResourceUpdated(TRemoteResource* LRemoteRes);
	virtual void __fastcall DisconnectFromManager(const System::UnicodeString AManagerId);
	virtual void __fastcall InternalConsistencyCheck();
	
public:
	__fastcall virtual TTetheringAppProfile(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TTetheringAppProfile();
	__classmethod virtual System::Tether::Manager::TTetheringProfile* __fastcall CreateInstance(System::Tether::Manager::TTetheringManager* const AManager);
	bool __fastcall RunRemoteAction(TRemoteAction* const AnAction)/* overload */;
	bool __fastcall RunRemoteAction(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString AnActionName)/* overload */;
	NativeUInt __fastcall RunRemoteActionAsync(TRemoteAction* const AnAction)/* overload */;
	NativeUInt __fastcall RunRemoteActionAsync(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString AnActionName)/* overload */;
	TRemoteActionState __fastcall GetRemoteActionAsyncState(const System::Tether::Manager::TTetheringProfileInfo &AProfile, NativeUInt ARemoteActionHandle)/* overload */;
	TRemoteActionState __fastcall GetRemoteActionAsyncState(TRemoteAction* const AnAction)/* overload */;
	TRemoteActionState __fastcall GetRemoteActionAsyncState(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString AnActionName)/* overload */;
	bool __fastcall SendString(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString Description, const System::UnicodeString AString);
	bool __fastcall SendLongString(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString Description, const System::UnicodeString AString);
	bool __fastcall SendStream(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString Description, System::Classes::TStream* const AStream);
	System::Generics::Collections::TList__1<TRemoteAction*>* __fastcall GetRemoteProfileActions(const System::Tether::Manager::TTetheringProfileInfo &AProfile);
	System::Generics::Collections::TList__1<TRemoteResource*>* __fastcall GetRemoteProfileResources(const System::Tether::Manager::TTetheringProfileInfo &AProfile);
	TRemoteResource* __fastcall GetRemoteResourceValue(TRemoteResource* const ARemoteRes)/* overload */;
	TRemoteResource* __fastcall GetRemoteResourceValue(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString ARemoteResName)/* overload */;
	bool __fastcall SubscribeToRemoteItem(const System::Tether::Manager::TTetheringProfileInfo &AProfile, TCustomRemoteItem* const ARemoteItem)/* overload */;
	bool __fastcall SubscribeToRemoteItem(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString ARemoteItemName)/* overload */;
	bool __fastcall UnSubscribeFromRemoteItem(const System::Tether::Manager::TTetheringProfileInfo &AProfile, TCustomRemoteItem* const ARemoteItem)/* overload */;
	bool __fastcall UnSubscribeFromRemoteItem(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString ARemoteItemName)/* overload */;
	virtual bool __fastcall Connect(const System::Tether::Manager::TTetheringProfileInfo &AProfile, const System::UnicodeString AProtocolType = System::UnicodeString(), const System::UnicodeString AnAdapterType = System::UnicodeString())/* overload */;
	virtual bool __fastcall Connect(const System::Tether::Manager::TTetheringProfileInfo &AProfile, int ATimeout, const System::UnicodeString AProtocolType = System::UnicodeString(), const System::UnicodeString AnAdapterType = System::UnicodeString())/* overload */;
	virtual void __fastcall Disconnect(const System::Tether::Manager::TTetheringProfileInfo &AProfile);
	virtual void __fastcall Notify(const System::UnicodeString ANotification, const System::UnicodeString Data);
	void __fastcall NotifyUpdate(TCustomLocalItem* ALocalItem, const System::UnicodeString Data = System::UnicodeString());
	void __fastcall RegisterAction(System::Actions::TContainedAction* const AnAction, const System::UnicodeString AName = System::UnicodeString());
	TLocalResource* __fastcall CreateResource(const System::UnicodeString AName, TRemoteResourceType AResType, const TResourceValue &AValue);
#ifndef _WIN64
	__classmethod virtual System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetAllowedProtocolsAdapters();
#else /* _WIN64 */
	__classmethod virtual System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetAllowedProtocolsAdapters();
#endif /* _WIN64 */
	void __fastcall NotifyProfileUpdate();
	__property bool NotifyProfileUpdates = {read=FNotifyProfileUpdates, write=FNotifyProfileUpdates, nodefault};
	
__published:
	__property TActionCollection* Actions = {read=GetSharedActions, write=SetSharedActions};
	__property TResourceCollection* Resources = {read=GetSharedResources, write=SetSharedResources};
	__property TAcceptResourceEvent OnAcceptResource = {read=FOnAcceptResource, write=FOnAcceptResource};
	__property TActionUpdatedEvent OnActionUpdated = {read=FOnActionUpdated, write=FOnActionUpdated};
	__property TResourceUpdatedEvent OnResourceReceived = {read=FOnResourceReceived, write=FOnResourceReceived};
	__property TResourceUpdatedEvent OnResourceUpdated = {read=FOnResourceUpdated, write=FOnResourceUpdated};
	__property TRemoteProfileUpdateEvent OnRemoteProfileUpdate = {read=FOnRemoteProfileUpdate, write=FOnRemoteProfileUpdate};
	__property TASyncRemoteActionEvent OnASyncRemoteActionEnd = {read=FOnASyncRemoteActionEnd, write=FOnASyncRemoteActionEnd};
};


//-- var, const, procedure ---------------------------------------------------
#define AppProfileDataType L"DataType"
#define AppProfileResourceType L"ResourceType"
#define AppProfileValue L"Value"
#define AppProfileActionEnabled L"ActionEnabled"
#define AppProfileActionCaption L"ActionCaption"
#define AppProfileActionHint L"ActionHint"
#ifndef _WIN64
static const NativeUInt InvalidRemoteHandle = NativeUInt(0xffffffff);
#else /* _WIN64 */
static const NativeUInt InvalidRemoteHandle = 0xffffffffffffffffULL;
#endif /* _WIN64 */
}	/* namespace Appprofile */
}	/* namespace Tether */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_TETHER_APPPROFILE)
using namespace System::Tether::Appprofile;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_TETHER)
using namespace System::Tether;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Tether_AppprofileHPP
