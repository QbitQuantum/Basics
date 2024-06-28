// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Client.pas' rev: 34.00 (Windows)

#ifndef Rest_ClientHPP
#define Rest_ClientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.JSON.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Net.URLClient.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.JSON.Writers.hpp>
#include <System.JSON.Readers.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <Data.Bind.Components.hpp>
#include <REST.HttpClient.hpp>
#include <REST.Types.hpp>
#include <REST.BindSource.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Client
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IRESTResponseJSON;
typedef System::DelphiInterface<IRESTResponseJSON> _di_IRESTResponseJSON;
class DELPHICLASS TRESTRequestParameter;
__interface DELPHIINTERFACE IRESTRequestParameterListOwnerNotify;
typedef System::DelphiInterface<IRESTRequestParameterListOwnerNotify> _di_IRESTRequestParameterListOwnerNotify;
class DELPHICLASS TRESTRequestParameterList;
class DELPHICLASS TRESTExecutionThread;
class DELPHICLASS TCustomRESTRequest;
class DELPHICLASS TRESTRequestAdapter;
class DELPHICLASS TCustomRESTRequestBindSource;
class DELPHICLASS TSubRESTRequestBindSource;
class DELPHICLASS TRESTRequest;
class DELPHICLASS TCustomRESTResponse;
class DELPHICLASS TRESTResponseAdapter;
class DELPHICLASS TCustomRESTResponseBindSource;
class DELPHICLASS TSubRESTResponseBindSource;
class DELPHICLASS TRESTResponse;
class DELPHICLASS TCustomRESTClient;
class DELPHICLASS TRESTClientAdapter;
class DELPHICLASS TCustomRESTClientBindSource;
class DELPHICLASS TSubRESTClientBindSource;
class DELPHICLASS TRESTClient;
class DELPHICLASS TCustomAuthenticator;
template<typename T> class DELPHICLASS TRESTAuthenticatorAdapter__1;
template<typename T> class DELPHICLASS TRESTAuthenticatorBindSource__1;
class DELPHICLASS TDownloadURL;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{71F5FA19-69CC-4384-AC0A-D6E30AD5CC95}") IRESTResponseJSON  : public System::IInterface 
{
	virtual void __fastcall AddJSONChangedEvent(const System::Classes::TNotifyEvent ANotify) = 0 ;
	virtual void __fastcall RemoveJSONChangedEvent(const System::Classes::TNotifyEvent ANotify) = 0 ;
	virtual void __fastcall GetJSONResponse(/* out */ System::Json::TJSONValue* &AJSONValue, /* out */ bool &AHasOwner) = 0 ;
	virtual bool __fastcall HasJSONResponse() = 0 ;
	virtual bool __fastcall HasResponseContent() = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TRESTRequestParameter : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	System::UnicodeString FValue;
	System::Classes::TStream* FStream;
	bool FStreamOwner;
	Rest::Types::TRESTRequestParameterKind FKind;
	Rest::Types::TRESTContentType FContentType;
	Rest::Types::TRESTRequestParameterOptions FOptions;
	bool __fastcall KindIsStored();
	void __fastcall SetKind(const Rest::Types::TRESTRequestParameterKind AValue);
	void __fastcall SetName(const System::UnicodeString AValue);
	void __fastcall SetOptions(const Rest::Types::TRESTRequestParameterOptions AValue);
	void __fastcall SetValue(const System::UnicodeString AValue);
	void __fastcall SetContentType(const Rest::Types::TRESTContentType AValue);
	void __fastcall ReleaseStream();
	void __fastcall NotifyParameterChanged(bool AValueChanged);
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall GetBytes();
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall GetBytes();
#endif /* _WIN64 */
	
public:
	__fastcall virtual TRESTRequestParameter(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TRESTRequestParameter();
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
	void __fastcall SetStream(System::Classes::TStream* const AValue, Rest::Types::TRESTObjectOwnership AOwnership = (Rest::Types::TRESTObjectOwnership)(0x0));
	TRESTRequestParameter* __fastcall AddValue(const System::UnicodeString AValue);
	virtual System::UnicodeString __fastcall ToString();
	virtual System::UnicodeString __fastcall GetDisplayName();
	__property System::Classes::TStream* Stream = {read=FStream};
	__property bool StreamOwner = {read=FStreamOwner, nodefault};
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> Bytes = {read=GetBytes};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> Bytes = {read=GetBytes};
#endif /* _WIN64 */
	
__published:
	__property Rest::Types::TRESTRequestParameterKind Kind = {read=FKind, write=SetKind, stored=KindIsStored, nodefault};
	__property System::UnicodeString Name = {read=FName, write=SetName};
	__property Rest::Types::TRESTRequestParameterOptions Options = {read=FOptions, write=SetOptions, default=0};
	__property System::UnicodeString Value = {read=FValue, write=SetValue};
	__property Rest::Types::TRESTContentType ContentType = {read=FContentType, write=SetContentType, default=0};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,TRESTRequestParameter*>* TRESTRequestParameterDict;

#ifndef _WIN64
typedef System::DynamicArray<TRESTRequestParameter*> TRESTRequestParameterArray;
#else /* _WIN64 */
typedef System::TArray__1<TRESTRequestParameter*> TRESTRequestParameterArray;
#endif /* _WIN64 */

__interface  INTERFACE_UUID("{48713C06-9469-4648-BCF9-FF83C6A58F5D}") IRESTRequestParameterListOwnerNotify  : public System::IInterface 
{
	virtual void __fastcall ParameterListChanged() = 0 ;
	virtual void __fastcall ParameterValueChanged() = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TRESTRequestParameterList : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
	
private:
	class DELPHICLASS TEnumerator;
	class PASCALIMPLEMENTATION TEnumerator : public System::Classes::TCollectionEnumerator
	{
		typedef System::Classes::TCollectionEnumerator inherited;
		
	public:
		HIDESBASE TRESTRequestParameter* __fastcall GetCurrent();
		__property TRESTRequestParameter* Current = {read=GetCurrent};
	public:
		/* TCollectionEnumerator.Create */ inline __fastcall TEnumerator(System::Classes::TCollection* ACollection) : System::Classes::TCollectionEnumerator(ACollection) { }
		
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TEnumerator() { }
		
	};
	
	
	
public:
	TRESTRequestParameter* operator[](int index) { return this->Items[index]; }
	
protected:
	HIDESBASE TRESTRequestParameter* __fastcall GetItem(int AIndex);
	HIDESBASE void __fastcall SetItem(int AIndex, TRESTRequestParameter* const AValue);
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int AIndex);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int AIndex, int AItemIndex);
	virtual void __fastcall Update(System::Classes::TCollectionItem* AItem);
	
public:
	__fastcall TRESTRequestParameterList(System::Classes::TComponent* const AOwner);
	HIDESBASE TEnumerator* __fastcall GetEnumerator();
	TRESTRequestParameter* __fastcall AddCookie(const System::UnicodeString AName, const System::UnicodeString AValue);
	TRESTRequestParameter* __fastcall AddHeader(const System::UnicodeString AName, const System::UnicodeString AValue);
	void __fastcall AddObject(System::TObject* AObject)/* overload */;
	void __fastcall AddObject(System::TObject* AObject, System::Classes::TStrings* WhiteList)/* overload */;
	TRESTRequestParameter* __fastcall AddItem()/* overload */;
	TRESTRequestParameter* __fastcall AddItem(const System::UnicodeString AName, const System::UnicodeString AValue, Rest::Types::TRESTRequestParameterKind AKind, Rest::Types::TRESTRequestParameterOptions AOptions = Rest::Types::TRESTRequestParameterOptions() )/* overload */;
	__property TRESTRequestParameter* Items[int index] = {read=GetItem, write=SetItem/*, default*/};
	HIDESBASE void __fastcall Delete(TRESTRequestParameter* const AParam)/* overload */;
	HIDESBASE void __fastcall Delete(const System::UnicodeString AName)/* overload */;
	int __fastcall IndexOf(TRESTRequestParameter* const AParam)/* overload */;
	int __fastcall IndexOf(const System::UnicodeString AName)/* overload */;
	TRESTRequestParameter* __fastcall AddItem(const System::UnicodeString AName, const System::UnicodeString AValue)/* overload */;
	TRESTRequestParameter* __fastcall AddItem(const System::UnicodeString AName, const System::UnicodeString AValue, const Rest::Types::TRESTRequestParameterKind AKind, const Rest::Types::TRESTRequestParameterOptions AOptions, Rest::Types::TRESTContentType AContentType)/* overload */;
#ifndef _WIN64
	TRESTRequestParameter* __fastcall AddItem(const System::UnicodeString AName, const System::DynamicArray<System::Byte> AValue, const Rest::Types::TRESTRequestParameterKind AKind, const Rest::Types::TRESTRequestParameterOptions AOptions, Rest::Types::TRESTContentType AContentType)/* overload */;
#else /* _WIN64 */
	TRESTRequestParameter* __fastcall AddItem(const System::UnicodeString AName, const System::TArray__1<System::Byte> AValue, const Rest::Types::TRESTRequestParameterKind AKind, const Rest::Types::TRESTRequestParameterOptions AOptions, Rest::Types::TRESTContentType AContentType)/* overload */;
#endif /* _WIN64 */
	TRESTRequestParameter* __fastcall AddItem(const System::UnicodeString AName, System::Classes::TStream* const AValue, const Rest::Types::TRESTRequestParameterKind AKind, const Rest::Types::TRESTRequestParameterOptions AOptions, Rest::Types::TRESTContentType AContentType, Rest::Types::TRESTObjectOwnership AOwnsStream = (Rest::Types::TRESTObjectOwnership)(0x0))/* overload */;
	void __fastcall AddUrlSegment(const System::UnicodeString AName, const System::UnicodeString AValue);
	TRESTRequestParameter* __fastcall ParameterByName(const System::UnicodeString AName);
	TRESTRequestParameter* __fastcall ParameterByIndex(int AIndex);
	bool __fastcall ContainsParameter(const System::UnicodeString AName);
	bool __fastcall CreateURLSegmentsFromString(const System::UnicodeString AUrlPath);
	void __fastcall CreateGetParamsFromUrl(const System::UnicodeString AUrlPath);
	void __fastcall AddBody(const System::UnicodeString ABodyContent, Rest::Types::TRESTContentType AContentType = (Rest::Types::TRESTContentType)(0x0))/* overload */;
	template<typename T> void __fastcall AddBody(const T AObject, Rest::Types::TRESTObjectOwnership AOwnsObject = (Rest::Types::TRESTObjectOwnership)(0x2))/* overload */;
	void __fastcall AddBody(System::Json::TJSONObject* const AObject, Rest::Types::TRESTObjectOwnership AOwnsObject = (Rest::Types::TRESTObjectOwnership)(0x2))/* overload */;
	void __fastcall AddBody(System::Classes::TStream* const ABodyContent, Rest::Types::TRESTContentType AContentType = (Rest::Types::TRESTContentType)(0x0), Rest::Types::TRESTObjectOwnership AOwnsStream = (Rest::Types::TRESTObjectOwnership)(0x0))/* overload */;
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TRESTRequestParameterList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TExecuteMethod)(void);

class PASCALIMPLEMENTATION TRESTExecutionThread : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	System::Sysutils::_di_TProc FCompletionHandler;
	System::DelphiInterface<System::Sysutils::TProc__1<System::TObject*> > FCompletionHandlerWithError;
	TExecuteMethod FExecuteMethod;
	bool FSynchronized;
	TCustomRESTRequest* FRequest;
	System::TObject* FExceptObject;
	
protected:
	void __fastcall HandleCompletion();
	void __fastcall HandleCompletionWithError();
	virtual void __fastcall Execute();
	
public:
	__fastcall TRESTExecutionThread(TExecuteMethod AExecuteMethod, TCustomRESTRequest* ARequest, System::Sysutils::_di_TProc ACompletionHandler, bool ASynchronized, bool AFreeThread, System::DelphiInterface<System::Sysutils::TProc__1<System::TObject*> > ACompletionHandlerWithError);
	void __fastcall Cancel();
public:
	/* TThread.Destroy */ inline __fastcall virtual ~TRESTExecutionThread() { }
	
};


typedef void __fastcall (__closure *TCustomRESTRequestNotifyEvent)(TCustomRESTRequest* Sender);

class PASCALIMPLEMENTATION TCustomRESTRequest : public Data::Bind::Objectscope::TBaseObjectBindSourceDelegate
{
	typedef Data::Bind::Objectscope::TBaseObjectBindSourceDelegate inherited;
	
	
public:
	enum class DECLSPEC_DENUM TAssignedValue : unsigned char { rvAccept, rvHandleRedirects, rvAcceptCharset, rvAcceptEncoding, rvAllowCookies, rvConnectTimeout, rvReadTimeout };
	
	typedef System::Set<TAssignedValue, _DELPHI_SET_ENUMERATOR(TAssignedValue::rvAccept), _DELPHI_SET_ENUMERATOR(TAssignedValue::rvReadTimeout)> TAssignedValues;
	
	class DELPHICLASS TNotify;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TNotify : public Rest::Bindsource::TRESTComponentNotify
	{
		typedef Rest::Bindsource::TRESTComponentNotify inherited;
		
	public:
		virtual void __fastcall ParameterListChanged(System::TObject* Sender);
	public:
		/* TObject.Create */ inline __fastcall TNotify() : Rest::Bindsource::TRESTComponentNotify() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	typedef Rest::Bindsource::TRESTComponentNotifyList__1<TNotify*>* TNotifyList;
	
	class DELPHICLASS TBody;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TBody : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		TRESTRequestParameterList* FParams;
		System::Json::Writers::TJsonTextWriter* FJSONTextWriter;
		System::Classes::TStream* FJSONStream;
		void __fastcall ClearWriter();
		System::Json::Writers::TJsonTextWriter* __fastcall GetJSONWriter();
		
	public:
		__fastcall TBody();
		__fastcall virtual ~TBody();
		void __fastcall Add(const System::UnicodeString ABodyContent, Rest::Types::TRESTContentType AContentType = (Rest::Types::TRESTContentType)(0x0))/* overload */;
		template<typename T> void __fastcall Add(T AObject, Rest::Types::TRESTObjectOwnership AOwnsObject = (Rest::Types::TRESTObjectOwnership)(0x2))/* overload */;
		void __fastcall Add(System::Json::TJSONObject* AObject, Rest::Types::TRESTObjectOwnership AOwnsObject = (Rest::Types::TRESTObjectOwnership)(0x2))/* overload */;
		void __fastcall Add(System::Classes::TStream* ABodyContent, Rest::Types::TRESTContentType AContentType = (Rest::Types::TRESTContentType)(0x0), Rest::Types::TRESTObjectOwnership AOwnsStream = (Rest::Types::TRESTObjectOwnership)(0x0))/* overload */;
		void __fastcall ClearBody();
		__property System::Json::Writers::TJsonTextWriter* JSONWriter = {read=GetJSONWriter};
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	System::UnicodeString FAccept;
	System::UnicodeString FAcceptCharset;
	System::UnicodeString FAcceptEncoding;
	bool FHandleRedirects;
	Rest::Types::TRESTRequestMethod FMethod;
	bool FPosting;
	bool FAutoCreateParams;
	TRESTRequestParameterList* FParams;
	TRESTRequestParameterList* FTransientParams;
	System::UnicodeString FResource;
	int FReadTimeout;
	int FConnectTimeout;
	TCustomRESTClient* FClient;
	TCustomRESTResponse* FResponse;
	TSubRESTRequestBindSource* FBindSource;
	Rest::Bindsource::TRESTComponentNotifyList__1<TNotify*>* FNotifyList;
	bool FURLAlreadyEncoded;
	TBody* FBody;
	System::UnicodeString FRequestContentType;
	TCustomRESTRequestNotifyEvent FOnAfterExecute;
	Rest::Types::TExecutionPerformance FExecutionPerformance;
	TCustomRESTRequestNotifyEvent FOnHTTPProtocolError;
	bool FSynchronizedEvents;
	System::UnicodeString FResourceSuffix;
	bool FAllowCookies;
	TAssignedValues FAssignedValues;
	bool __fastcall AcceptIsStored();
	bool __fastcall AcceptCharSetIsStored();
	bool __fastcall AcceptEncodingIsStored();
	bool __fastcall AllowCookiesIsStored();
	bool __fastcall HandleRedirectsIsStored();
	bool __fastcall MethodIsStored();
	void __fastcall SetAccept(const System::UnicodeString AValue);
	void __fastcall SetAcceptCharset(const System::UnicodeString AValue);
	void __fastcall SetHandleRedirects(const bool AValue);
	void __fastcall SetClient(TCustomRESTClient* const AValue);
	void __fastcall SetParams(TRESTRequestParameterList* const AValue);
	void __fastcall SetAutoCreateParams(const bool AValue);
	void __fastcall ProcessResponse(const System::UnicodeString AURL, System::Classes::TMemoryStream* AResponseStream, const System::UnicodeString AContent);
	void __fastcall SetAcceptEncoding(const System::UnicodeString AValue);
	void __fastcall SetMethod(const Rest::Types::TRESTRequestMethod AValue);
	void __fastcall SetResource(const System::UnicodeString AValue);
	void __fastcall SetTimeout(const int AValue);
	void __fastcall SetResponse(TCustomRESTResponse* const AResponse);
	void __fastcall SetSynchronizedEvents(const bool AValue);
	System::UnicodeString __fastcall GetFullResource();
	void __fastcall SetResourceSuffix(const System::UnicodeString AValue);
	bool __fastcall IsQueryParam(TRESTRequestParameter* const AParam, Rest::Types::TRESTContentType AContentType);
	System::UnicodeString __fastcall GetFullURL();
	bool __fastcall GetIsCancelled();
	int __fastcall GetTimeout();
	void __fastcall SetConnectTimeout(const int AValue);
	void __fastcall SetReadTimeout(const int AValue);
	void __fastcall DoReadTimeout(System::Classes::TReader* Reader);
	void __fastcall SetAllowCookies(const bool AValue);
	System::UnicodeString __fastcall GetAccept();
	System::UnicodeString __fastcall GetAcceptCharset();
	System::UnicodeString __fastcall GetAcceptEncoding();
	bool __fastcall GetAllowCookies();
	bool __fastcall GetHandleRedirects();
	int __fastcall GetConnectTimeout();
	int __fastcall GetReadTimeout();
	bool __fastcall ConnectTimeoutIsStored();
	bool __fastcall ReadTimeoutIsStored();
	
protected:
	virtual void __fastcall Loaded();
	virtual TCustomRESTClient* __fastcall GetClient();
	virtual Data::Bind::Objectscope::TBaseObjectBindSource* __fastcall CreateBindSource();
	virtual TSubRESTRequestBindSource* __fastcall CreateRequestBindSource();
	virtual void __fastcall ParameterListChanged();
	virtual void __fastcall ParameterValueChanged();
	virtual void __fastcall PropertyValueChanged();
	virtual void __fastcall DoResponseChanged();
	virtual void __fastcall DoResponseChanging();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* AFiler);
	virtual void __fastcall DoAfterExecute();
	virtual void __fastcall DoBeforeExecute();
	virtual void __fastcall DoHTTPProtocolError();
#ifndef _WIN64
	virtual void __fastcall DoApplyCookieParams(const System::DynamicArray<TRESTRequestParameter*> AParamList, const System::UnicodeString CookieURL);
	virtual void __fastcall DoApplyHeaderParams(const System::DynamicArray<TRESTRequestParameter*> AParamList);
	virtual void __fastcall DoApplyURLSegments(const System::DynamicArray<TRESTRequestParameter*> AParamList, System::UnicodeString &AURL);
	virtual void __fastcall DoPrepareQueryString(const System::DynamicArray<TRESTRequestParameter*> AParamList, Rest::Types::TRESTContentType AContentType, System::UnicodeString &AURL);
	virtual void __fastcall DoPrepareRequestBody(System::DynamicArray<TRESTRequestParameter*> AParamList, Rest::Types::TRESTContentType AContentType, System::Classes::TStream* &ABodyStream, bool &ABodyStreamOwner);
#else /* _WIN64 */
	virtual void __fastcall DoApplyCookieParams(const System::TArray__1<TRESTRequestParameter*> AParamList, const System::UnicodeString CookieURL);
	virtual void __fastcall DoApplyHeaderParams(const System::TArray__1<TRESTRequestParameter*> AParamList);
	virtual void __fastcall DoApplyURLSegments(const System::TArray__1<TRESTRequestParameter*> AParamList, System::UnicodeString &AURL);
	virtual void __fastcall DoPrepareQueryString(const System::TArray__1<TRESTRequestParameter*> AParamList, Rest::Types::TRESTContentType AContentType, System::UnicodeString &AURL);
	virtual void __fastcall DoPrepareRequestBody(System::TArray__1<TRESTRequestParameter*> AParamList, Rest::Types::TRESTContentType AContentType, System::Classes::TStream* &ABodyStream, bool &ABodyStreamOwner);
#endif /* _WIN64 */
	void __fastcall HandleEvent(Rest::Types::TMethod AEventHandler);
	__property Rest::Bindsource::TRESTComponentNotifyList__1<TNotify*>* NotifyList = {read=FNotifyList};
	
public:
	__fastcall virtual TCustomRESTRequest(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomRESTRequest();
	Rest::Types::TRESTContentType __fastcall ContentType()/* overload */;
#ifndef _WIN64
	Rest::Types::TRESTContentType __fastcall ContentType(const System::DynamicArray<TRESTRequestParameter*> AParamsArray)/* overload */;
#else /* _WIN64 */
	Rest::Types::TRESTContentType __fastcall ContentType(const System::TArray__1<TRESTRequestParameter*> AParamsArray)/* overload */;
#endif /* _WIN64 */
	void __fastcall AddParameter(const System::UnicodeString AName, const System::UnicodeString AValue)/* overload */;
	void __fastcall AddParameter(const System::UnicodeString AName, System::Json::TJSONObject* AJsonObject, bool AFreeJson = true)/* overload */;
	void __fastcall AddParameter(const System::UnicodeString AName, System::Json::TJSONObject* AJsonObject, Rest::Types::TRESTObjectOwnership AOwnsObject)/* overload */;
	void __fastcall AddParameter(const System::UnicodeString AName, const System::UnicodeString AValue, const Rest::Types::TRESTRequestParameterKind AKind)/* overload */;
	void __fastcall AddParameter(const System::UnicodeString AName, const System::UnicodeString AValue, const Rest::Types::TRESTRequestParameterKind AKind, const Rest::Types::TRESTRequestParameterOptions AOptions)/* overload */;
	void __fastcall AddAuthParameter(const System::UnicodeString AName, const System::UnicodeString AValue, const Rest::Types::TRESTRequestParameterKind AKind, const Rest::Types::TRESTRequestParameterOptions AOptions = Rest::Types::TRESTRequestParameterOptions() )/* overload */;
#ifndef _WIN64
	System::DynamicArray<TRESTRequestParameter*> __fastcall CreateUnionParameterList();
#else /* _WIN64 */
	System::TArray__1<TRESTRequestParameter*> __fastcall CreateUnionParameterList();
#endif /* _WIN64 */
	void __fastcall AddBody(const System::UnicodeString ABodyContent, Rest::Types::TRESTContentType AContentType = (Rest::Types::TRESTContentType)(0x0))/* overload */;
	template<typename T> void __fastcall AddBody(T AObject)/* overload */;
	void __fastcall AddBody(System::Json::TJSONObject* AObject, Rest::Types::TRESTObjectOwnership AOwnsObject = (Rest::Types::TRESTObjectOwnership)(0x2))/* overload */;
	void __fastcall AddBody(System::Classes::TStream* ABodyContent, Rest::Types::TRESTContentType AContentType = (Rest::Types::TRESTContentType)(0x0), Rest::Types::TRESTObjectOwnership AOwnsStream = (Rest::Types::TRESTObjectOwnership)(0x0))/* overload */;
	void __fastcall ClearBody();
	void __fastcall AddFile(const System::UnicodeString AName, const System::UnicodeString AFileName, Rest::Types::TRESTContentType AContentType = (Rest::Types::TRESTContentType)(0x0))/* overload */;
	void __fastcall AddFile(const System::UnicodeString AFileName, Rest::Types::TRESTContentType AContentType = (Rest::Types::TRESTContentType)(0x0))/* overload */;
	void __fastcall ResetToDefaults();
	void __fastcall Execute();
	HIDESBASE void __fastcall Cancel();
	__property bool IsCancelled = {read=GetIsCancelled, nodefault};
	TRESTExecutionThread* __fastcall ExecuteAsync(System::Sysutils::_di_TProc ACompletionHandler = System::Sysutils::_di_TProc(), bool ASynchronized = true, bool AFreeThread = true, System::DelphiInterface<System::Sysutils::TProc__1<System::TObject*> > ACompletionHandlerWithError = System::DelphiInterface<System::Sysutils::TProc__1<System::TObject*> >());
	System::UnicodeString __fastcall GetFullRequestURL(bool AIncludeParams = true);
	__property TAssignedValues AssignedValues = {read=FAssignedValues, write=FAssignedValues, default=0};
	__property TRESTRequestParameterList* TransientParams = {read=FTransientParams};
	__property bool AutoCreateParams = {read=FAutoCreateParams, write=SetAutoCreateParams, default=1};
	__property System::UnicodeString Accept = {read=GetAccept, write=SetAccept, stored=AcceptIsStored};
	__property System::UnicodeString AcceptCharset = {read=GetAcceptCharset, write=SetAcceptCharset, stored=AcceptCharSetIsStored};
	__property System::UnicodeString AcceptEncoding = {read=GetAcceptEncoding, write=SetAcceptEncoding, stored=AcceptEncodingIsStored};
	__property bool AllowCookies = {read=GetAllowCookies, write=SetAllowCookies, stored=AllowCookiesIsStored, default=1};
	__property bool HandleRedirects = {read=GetHandleRedirects, write=SetHandleRedirects, stored=HandleRedirectsIsStored, default=1};
	__property TCustomRESTClient* Client = {read=GetClient, write=SetClient};
	__property Rest::Types::TRESTRequestMethod Method = {read=FMethod, write=SetMethod, stored=MethodIsStored, nodefault};
	__property TRESTRequestParameterList* Params = {read=FParams, write=SetParams};
	__property TBody* Body = {read=FBody};
	__property System::UnicodeString Resource = {read=FResource, write=SetResource};
	__property System::UnicodeString ResourceSuffix = {read=FResourceSuffix, write=SetResourceSuffix};
	__property System::UnicodeString FullResource = {read=GetFullResource};
	__property TCustomRESTResponse* Response = {read=FResponse, write=SetResponse};
	__property int Timeout = {read=GetTimeout, write=SetTimeout, stored=false, default=30000};
	__property int ConnectTimeout = {read=GetConnectTimeout, write=SetConnectTimeout, stored=ConnectTimeoutIsStored, default=30000};
	__property int ReadTimeout = {read=GetReadTimeout, write=SetReadTimeout, stored=ReadTimeoutIsStored, default=30000};
	__property TCustomRESTRequestNotifyEvent OnAfterExecute = {read=FOnAfterExecute, write=FOnAfterExecute};
	__property Rest::Types::TExecutionPerformance ExecutionPerformance = {read=FExecutionPerformance};
	__property bool SynchronizedEvents = {read=FSynchronizedEvents, write=SetSynchronizedEvents, default=1};
	__property TCustomRESTRequestNotifyEvent OnHTTPProtocolError = {read=FOnHTTPProtocolError, write=FOnHTTPProtocolError};
	__property TSubRESTRequestBindSource* BindSource = {read=FBindSource};
	__property bool URLAlreadyEncoded = {read=FURLAlreadyEncoded, write=FURLAlreadyEncoded, nodefault};
private:
	void *__IRESTRequestParameterListOwnerNotify;	// IRESTRequestParameterListOwnerNotify 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {48713C06-9469-4648-BCF9-FF83C6A58F5D}
	operator _di_IRESTRequestParameterListOwnerNotify()
	{
		_di_IRESTRequestParameterListOwnerNotify intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IRESTRequestParameterListOwnerNotify*(void) { return (IRESTRequestParameterListOwnerNotify*)&__IRESTRequestParameterListOwnerNotify; }
	#endif
	
};


class PASCALIMPLEMENTATION TRESTRequestAdapter : public Rest::Bindsource::TRESTComponentAdapter
{
	typedef Rest::Bindsource::TRESTComponentAdapter inherited;
	
	
public:
	class DELPHICLASS TNotify;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TNotify : public TCustomRESTRequest::TNotify
	{
		typedef TCustomRESTRequest::TNotify inherited;
		
	private:
		TRESTRequestAdapter* FAdapter;
		
	protected:
		__fastcall TNotify(TRESTRequestAdapter* const AAdapter);
		
	public:
		virtual void __fastcall ParameterListChanged(System::TObject* Sender);
		virtual void __fastcall PropertyValueChanged(System::TObject* Sender);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	TCustomRESTRequest* FRequest;
	TNotify* FNotify;
	void __fastcall SetRequest(TCustomRESTRequest* const ARequest);
	void __fastcall AddParameterFields();
	void __fastcall ParameterListChanged();
	void __fastcall AddPropertyFields();
	
protected:
	virtual void __fastcall CreatePropertyFields();
	virtual void __fastcall DoChangePosting();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall GetCanActivate();
	virtual void __fastcall AddFields();
	virtual Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetSource();
	
public:
	__fastcall virtual TRESTRequestAdapter(System::Classes::TComponent* AComponent);
	__fastcall virtual ~TRESTRequestAdapter();
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList);
	__property TCustomRESTRequest* Request = {read=FRequest, write=SetRequest};
};


class PASCALIMPLEMENTATION TCustomRESTRequestBindSource : public Rest::Bindsource::TRESTComponentBindSource
{
	typedef Rest::Bindsource::TRESTComponentBindSource inherited;
	
private:
	TRESTRequestAdapter* FAdapter;
	TCustomRESTRequest* __fastcall GetRequest();
	void __fastcall SetRequest(TCustomRESTRequest* const Value);
	
protected:
	virtual TRESTRequestAdapter* __fastcall CreateRequestAdapter();
	virtual Rest::Bindsource::TRESTComponentAdapter* __fastcall CreateAdapter();
	
public:
	__property TCustomRESTRequest* Request = {read=GetRequest, write=SetRequest};
	__property TRESTRequestAdapter* Adapter = {read=FAdapter};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TCustomRESTRequestBindSource(System::Classes::TComponent* AOwner) : Rest::Bindsource::TRESTComponentBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TCustomRESTRequestBindSource() { }
	
};


class PASCALIMPLEMENTATION TSubRESTRequestBindSource : public TCustomRESTRequestBindSource
{
	typedef TCustomRESTRequestBindSource inherited;
	
__published:
	__property AutoActivate = {default=1};
	__property AutoEdit = {default=1};
	__property AutoPost = {default=1};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TSubRESTRequestBindSource(System::Classes::TComponent* AOwner) : TCustomRESTRequestBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TSubRESTRequestBindSource() { }
	
};


class PASCALIMPLEMENTATION TRESTRequest : public TCustomRESTRequest
{
	typedef TCustomRESTRequest inherited;
	
__published:
	__property AssignedValues = {default=0};
	__property Accept;
	__property AcceptCharset;
	__property AcceptEncoding;
	__property AutoCreateParams = {default=1};
	__property HandleRedirects = {default=1};
	__property Client;
	__property Method;
	__property Params;
	__property Resource = {default=0};
	__property ResourceSuffix = {default=0};
	__property Response;
	__property ConnectTimeout = {default=30000};
	__property ReadTimeout = {default=30000};
	__property OnAfterExecute;
	
public:
	__property ExecutionPerformance;
	
__published:
	__property SynchronizedEvents = {default=1};
	__property OnHTTPProtocolError;
	__property BindSource;
public:
	/* TCustomRESTRequest.Create */ inline __fastcall virtual TRESTRequest(System::Classes::TComponent* AOwner) : TCustomRESTRequest(AOwner) { }
	/* TCustomRESTRequest.Destroy */ inline __fastcall virtual ~TRESTRequest() { }
	
};


class PASCALIMPLEMENTATION TCustomRESTResponse : public Data::Bind::Objectscope::TBaseObjectBindSourceDelegate
{
	typedef Data::Bind::Objectscope::TBaseObjectBindSourceDelegate inherited;
	
	
public:
	typedef Rest::Bindsource::TRESTJSONComponentNotify TNotify;
	
	typedef Rest::Bindsource::TRESTComponentNotifyList__1<Rest::Bindsource::TRESTJSONComponentNotify*>* TNotifyList;
	
	enum class DECLSPEC_DENUM TUpdateOption : unsigned char { PropertyValueChanged, JSONValueChanged };
	
	typedef System::Set<TUpdateOption, _DELPHI_SET_ENUMERATOR(TUpdateOption::PropertyValueChanged), _DELPHI_SET_ENUMERATOR(TUpdateOption::JSONValueChanged)> TUpdateOptions;
	
	enum class DECLSPEC_DENUM TJSONValueError : unsigned char { NoContent, NoJSON, InvalidRootElement };
	
	typedef void __fastcall (__closure *TJSONValueErrorEvent)(System::TObject* Sender, TJSONValueError AUpdateError, const System::UnicodeString AMessage);
	
	class DELPHICLASS EJSONValueError;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION EJSONValueError : public Rest::Types::ERESTException
	{
		typedef Rest::Types::ERESTException inherited;
		
	private:
		TCustomRESTResponse::TJSONValueError FError;
		
	public:
		__fastcall EJSONValueError(TCustomRESTResponse::TJSONValueError AError, const System::UnicodeString AMessage);
		__property TCustomRESTResponse::TJSONValueError Error = {read=FError, nodefault};
	public:
		/* Exception.CreateFmt */ inline __fastcall EJSONValueError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Rest::Types::ERESTException(Msg, Args, Args_High) { }
		/* Exception.CreateRes */ inline __fastcall EJSONValueError(NativeUInt Ident)/* overload */ : Rest::Types::ERESTException(Ident) { }
		/* Exception.CreateRes */ inline __fastcall EJSONValueError(System::PResStringRec ResStringRec)/* overload */ : Rest::Types::ERESTException(ResStringRec) { }
		/* Exception.CreateResFmt */ inline __fastcall EJSONValueError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Types::ERESTException(Ident, Args, Args_High) { }
		/* Exception.CreateResFmt */ inline __fastcall EJSONValueError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Types::ERESTException(ResStringRec, Args, Args_High) { }
		/* Exception.CreateHelp */ inline __fastcall EJSONValueError(const System::UnicodeString Msg, int AHelpContext) : Rest::Types::ERESTException(Msg, AHelpContext) { }
		/* Exception.CreateFmtHelp */ inline __fastcall EJSONValueError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Rest::Types::ERESTException(Msg, Args, Args_High, AHelpContext) { }
		/* Exception.CreateResHelp */ inline __fastcall EJSONValueError(NativeUInt Ident, int AHelpContext)/* overload */ : Rest::Types::ERESTException(Ident, AHelpContext) { }
		/* Exception.CreateResHelp */ inline __fastcall EJSONValueError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Rest::Types::ERESTException(ResStringRec, AHelpContext) { }
		/* Exception.CreateResFmtHelp */ inline __fastcall EJSONValueError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Types::ERESTException(ResStringRec, Args, Args_High, AHelpContext) { }
		/* Exception.CreateResFmtHelp */ inline __fastcall EJSONValueError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Types::ERESTException(Ident, Args, Args_High, AHelpContext) { }
		/* Exception.Destroy */ inline __fastcall virtual ~EJSONValueError() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	struct DECLSPEC_DRECORD TStatus
	{
	private:
		TCustomRESTResponse* FResponse;
		
	public:
		bool __fastcall Success();
		bool __fastcall ClientError();
		bool __fastcall SuccessOK_200();
		bool __fastcall SucessCreated_201();
		bool __fastcall ClientErrorBadRequest_400();
		bool __fastcall ClientErrorUnauthorized_401();
		bool __fastcall ClientErrorForbidden_403();
		bool __fastcall ClientErrorNotFound_404();
		bool __fastcall ClientErrorNotAcceptable_406();
		bool __fastcall ClientErrorDuplicate_409();
	};
	
	
	
private:
	TStatus FStatus;
	int FUpdating;
	TUpdateOptions FUpdateOptions;
	System::UnicodeString FContent;
	System::UnicodeString FContentEncoding;
	System::UnicodeString FContentType;
	System::UnicodeString FErrorMessage;
	System::Classes::TStrings* FHeaders;
	System::Net::Httpclient::TCookies* FCookies;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FRawBytes;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FRawBytes;
#endif /* _WIN64 */
	System::UnicodeString FFullRequestURI;
	System::Json::TJSONValue* FJSONValue;
	System::Classes::TStreamReader* FJSONStreamReader;
	System::Json::Readers::TJsonTextReader* FJSONTextReader;
	System::Classes::TStream* FJSONStream;
	System::UnicodeString FRootElement;
	System::UnicodeString FServer;
	int FStatusCode;
	System::UnicodeString FStatusText;
	TSubRESTResponseBindSource* FBindSource;
	Rest::Bindsource::TRESTComponentNotifyList__1<Rest::Bindsource::TRESTJSONComponentNotify*>* FNotifyList;
	System::Generics::Collections::TList__1<System::Classes::TNotifyEvent>* FJSONNotifyList;
	System::Json::TJSONValue* __fastcall GetJSONValue();
	void __fastcall SetRootElement(const System::UnicodeString AValue);
	int __fastcall GetStatusCode();
	void __fastcall SetStatusCode(const int AValue);
	System::UnicodeString __fastcall GetStatusText();
	void __fastcall SetStatusText(const System::UnicodeString AValue);
	unsigned __fastcall GetContentLength();
	void __fastcall SetContentEncoding(const System::UnicodeString AValue);
	void __fastcall SetContentType(const System::UnicodeString AValue);
	void __fastcall SetErrorMessage(const System::UnicodeString AValue);
	void __fastcall SetFullRequestURI(const System::UnicodeString AValue);
	void __fastcall SetServer(const System::UnicodeString AValue);
	TStatus __fastcall GetStatus();
	System::UnicodeString __fastcall GetJSONText();
	System::Json::Readers::TJsonTextReader* __fastcall GetJSONReader();
	
protected:
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	bool __fastcall IsUpdating();
	virtual Data::Bind::Objectscope::TBaseObjectBindSource* __fastcall CreateBindSource();
	virtual void __fastcall PropertyValueChanged();
	virtual void __fastcall JSONValueChanged();
	void __fastcall SetContent(const System::UnicodeString AContent);
	void __fastcall SetRawBytes(System::Classes::TStream* const AStream);
	void __fastcall AddJSONChangedEvent(const System::Classes::TNotifyEvent ANotify);
	void __fastcall RemoveJSONChangedEvent(const System::Classes::TNotifyEvent ANotify);
	void __fastcall GetJSONResponse(/* out */ System::Json::TJSONValue* &AJSONValue, /* out */ bool &AHasOwner);
	bool __fastcall HasJSONResponse();
	bool __fastcall HasResponseContent();
	
public:
	__fastcall virtual TCustomRESTResponse(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomRESTResponse();
	bool __fastcall GetSimpleValue(const System::UnicodeString AName, System::UnicodeString &AValue);
	void __fastcall ResetToDefaults();
	__property System::UnicodeString ContentEncoding = {read=FContentEncoding, write=SetContentEncoding};
	__property unsigned ContentLength = {read=GetContentLength, nodefault};
	__property System::UnicodeString ContentType = {read=FContentType, write=SetContentType};
	__property System::UnicodeString ErrorMessage = {read=FErrorMessage, write=SetErrorMessage};
	__property System::Classes::TStrings* Headers = {read=FHeaders};
	__property System::Net::Httpclient::TCookies* Cookies = {read=FCookies};
	__property System::Json::TJSONValue* JSONValue = {read=GetJSONValue};
	__property System::UnicodeString JSONText = {read=GetJSONText};
	__property System::Json::Readers::TJsonTextReader* JSONReader = {read=GetJSONReader};
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> RawBytes = {read=FRawBytes};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> RawBytes = {read=FRawBytes};
#endif /* _WIN64 */
	__property System::UnicodeString FullRequestURI = {read=FFullRequestURI, write=SetFullRequestURI};
	__property System::UnicodeString Server = {read=FServer, write=SetServer};
	__property int StatusCode = {read=GetStatusCode, write=SetStatusCode, nodefault};
	__property System::UnicodeString StatusText = {read=GetStatusText, write=SetStatusText};
	__property System::UnicodeString Content = {read=FContent};
	__property System::UnicodeString RootElement = {read=FRootElement, write=SetRootElement};
	__property TSubRESTResponseBindSource* BindSource = {read=FBindSource};
	__property Rest::Bindsource::TRESTComponentNotifyList__1<Rest::Bindsource::TRESTJSONComponentNotify*>* NotifyList = {read=FNotifyList};
	__property TStatus Status = {read=GetStatus};
private:
	void *__IRESTResponseJSON;	// IRESTResponseJSON 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {71F5FA19-69CC-4384-AC0A-D6E30AD5CC95}
	operator _di_IRESTResponseJSON()
	{
		_di_IRESTResponseJSON intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IRESTResponseJSON*(void) { return (IRESTResponseJSON*)&__IRESTResponseJSON; }
	#endif
	
};


class PASCALIMPLEMENTATION TRESTResponseAdapter : public Rest::Bindsource::TRESTComponentAdapter
{
	typedef Rest::Bindsource::TRESTComponentAdapter inherited;
	
	
public:
	class DELPHICLASS TNotify;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TNotify : public Rest::Bindsource::TRESTJSONComponentNotify
	{
		typedef Rest::Bindsource::TRESTJSONComponentNotify inherited;
		
	private:
		TRESTResponseAdapter* FAdapter;
		
	protected:
		__fastcall TNotify(TRESTResponseAdapter* const AAdapter);
		
	public:
		virtual void __fastcall PropertyValueChanged(System::TObject* Sender);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	TCustomRESTResponse* FResponse;
	TNotify* FNotify;
	void __fastcall SetResponse(TCustomRESTResponse* const AResponse);
	void __fastcall AddPropertyFields();
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall GetCanActivate();
	virtual void __fastcall AddFields();
	virtual Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetSource();
	
public:
	__fastcall virtual TRESTResponseAdapter(System::Classes::TComponent* AComponent);
	__fastcall virtual ~TRESTResponseAdapter();
	__property TCustomRESTResponse* Response = {read=FResponse, write=SetResponse};
};


class PASCALIMPLEMENTATION TCustomRESTResponseBindSource : public Rest::Bindsource::TRESTComponentBindSource
{
	typedef Rest::Bindsource::TRESTComponentBindSource inherited;
	
private:
	TRESTResponseAdapter* FAdapter;
	TCustomRESTResponse* __fastcall GetResponse();
	void __fastcall SetResponse(TCustomRESTResponse* const Value);
	
protected:
	virtual Rest::Bindsource::TRESTComponentAdapter* __fastcall CreateAdapter();
	
public:
	__property TCustomRESTResponse* Response = {read=GetResponse, write=SetResponse};
	__property TRESTResponseAdapter* Adapter = {read=FAdapter};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TCustomRESTResponseBindSource(System::Classes::TComponent* AOwner) : Rest::Bindsource::TRESTComponentBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TCustomRESTResponseBindSource() { }
	
};


class PASCALIMPLEMENTATION TSubRESTResponseBindSource : public TCustomRESTResponseBindSource
{
	typedef TCustomRESTResponseBindSource inherited;
	
__published:
	__property AutoActivate = {default=1};
	__property AutoEdit = {default=1};
	__property AutoPost = {default=1};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TSubRESTResponseBindSource(System::Classes::TComponent* AOwner) : TCustomRESTResponseBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TSubRESTResponseBindSource() { }
	
};


class PASCALIMPLEMENTATION TRESTResponse : public TCustomRESTResponse
{
	typedef TCustomRESTResponse inherited;
	
__published:
	__property Content = {default=0};
	__property ContentLength;
	__property ContentType = {default=0};
	__property ContentEncoding = {default=0};
	__property RootElement = {default=0};
	__property BindSource;
public:
	/* TCustomRESTResponse.Create */ inline __fastcall virtual TRESTResponse(System::Classes::TComponent* AOwner) : TCustomRESTResponse(AOwner) { }
	/* TCustomRESTResponse.Destroy */ inline __fastcall virtual ~TRESTResponse() { }
	
};


typedef void __fastcall (__closure *TCustomRESTClientNotifyEvent)(TCustomRESTClient* Sender);

class PASCALIMPLEMENTATION TCustomRESTClient : public Data::Bind::Objectscope::TBaseObjectBindSourceDelegate
{
	typedef Data::Bind::Objectscope::TBaseObjectBindSourceDelegate inherited;
	
	
public:
	class DELPHICLASS TNotify;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TNotify : public Rest::Bindsource::TRESTComponentNotify
	{
		typedef Rest::Bindsource::TRESTComponentNotify inherited;
		
	public:
		virtual void __fastcall ParameterListChanged(System::TObject* Sender);
	public:
		/* TObject.Create */ inline __fastcall TNotify() : Rest::Bindsource::TRESTComponentNotify() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	typedef Rest::Bindsource::TRESTComponentNotifyList__1<TNotify*>* TNotifyList;
	
	
private:
	TSubRESTClientBindSource* FBindSource;
	Rest::Bindsource::TRESTComponentNotifyList__1<TNotify*>* FNotifyList;
	TCustomRESTClientNotifyEvent FOnHTTPProtocolError;
	bool FAutoCreateParams;
	TRESTRequestParameterList* FParams;
	TRESTRequestParameterList* FTransientParams;
	TCustomAuthenticator* FAuthenticator;
	System::UnicodeString FBaseURL;
	System::UnicodeString FFallbackCharsetEncoding;
	bool FSynchronizedEvents;
	bool FRaiseExceptionOn500;
	Rest::Httpclient::TRESTHTTP* FHttpClient;
	bool FPosting;
	bool __fastcall FallbackCharsetEncodingIsStored();
	bool __fastcall UserAgentIsStored();
	void __fastcall SetParams(TRESTRequestParameterList* const AValue);
	void __fastcall SetAutoCreateParams(const bool AValue);
	System::UnicodeString __fastcall GetProxyPassword();
	int __fastcall GetProxyPort();
	System::UnicodeString __fastcall GetProxyServer();
	System::UnicodeString __fastcall GetProxyUsername();
	void __fastcall SetBaseURL(const System::UnicodeString AValue);
	void __fastcall SetProxyPassword(const System::UnicodeString AValue);
	void __fastcall SetProxyPort(const int AValue);
	void __fastcall SetProxyServer(const System::UnicodeString AValue);
	void __fastcall SetProxyUsername(const System::UnicodeString AValue);
	void __fastcall SetUserAgent(const System::UnicodeString AValue);
	void __fastcall SetFallbackCharsetEncoding(const System::UnicodeString AValue);
	void __fastcall SetAuthenticator(TCustomAuthenticator* const AValue);
	System::UnicodeString __fastcall GetAccept();
	void __fastcall SetAccept(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetUserAgent();
	bool __fastcall GetAllowCookies();
	void __fastcall SetAllowCookies(const bool AValue);
	bool __fastcall GetHandleRedirects();
	void __fastcall SetHandleRedirects(const bool AValue);
	System::UnicodeString __fastcall GetAcceptCharset();
	void __fastcall SetAcceptCharset(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetAcceptEncoding();
	void __fastcall SetAcceptEncoding(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetContentType();
	void __fastcall SetContentType(const System::UnicodeString AValue);
	void __fastcall SetSynchronizedEvents(const bool AValue);
	System::Net::Urlclient::TValidateCertificateEvent __fastcall GetOnValidateCertificate();
	void __fastcall SetOnValidateCertificate(const System::Net::Urlclient::TValidateCertificateEvent Value);
	System::Net::Httpclient::THTTPRedirectsWithGET __fastcall GetRedirectsWithGET();
	System::Net::Httpclient::THTTPSecureProtocols __fastcall GetSecureProtocols();
	System::Net::Urlclient::TNeedClientCertificateEvent __fastcall GetNeedClientCertificateEvent();
	System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent __fastcall GetAuthEvent();
	void __fastcall SetRedirectsWithGET(const System::Net::Httpclient::THTTPRedirectsWithGET AValue);
	void __fastcall SetSecureProtocols(const System::Net::Httpclient::THTTPSecureProtocols AValue);
	void __fastcall SetNeedClientCertificateEvent(const System::Net::Urlclient::TNeedClientCertificateEvent AValue);
	void __fastcall SetAuthEvent(const System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent AValue);
	void __fastcall SetConnectTimeout(const int AValue);
	void __fastcall SetReadTimeout(const int AValue);
	int __fastcall GetConnectTimeout();
	int __fastcall GetReadTimeout();
	__property Rest::Httpclient::TRESTHTTP* HTTPClient = {read=FHttpClient};
	
protected:
	__property Rest::Bindsource::TRESTComponentNotifyList__1<TNotify*>* NotifyList = {read=FNotifyList};
	virtual void __fastcall ParameterListChanged();
	virtual void __fastcall ParameterValueChanged();
	virtual void __fastcall PropertyValueChanged();
	virtual Data::Bind::Objectscope::TBaseObjectBindSource* __fastcall CreateBindSource();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall CreateHttpClient();
	virtual void __fastcall DoHTTPProtocolError();
	virtual void __fastcall HandleEvent(Rest::Types::TMethod AEventHandler);
	
public:
	__fastcall TCustomRESTClient(const System::UnicodeString ABaseApiURL)/* overload */;
	__fastcall virtual TCustomRESTClient(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TCustomRESTClient();
	void __fastcall AddParameter(const System::UnicodeString AName, const System::UnicodeString AValue)/* overload */;
	void __fastcall AddParameter(const System::UnicodeString AName, const System::UnicodeString AValue, const Rest::Types::TRESTRequestParameterKind AKind)/* overload */;
	void __fastcall AddParameter(const System::UnicodeString AName, const System::UnicodeString AValue, const Rest::Types::TRESTRequestParameterKind AKind, const Rest::Types::TRESTRequestParameterOptions AOptions)/* overload */;
	void __fastcall AddAuthParameter(const System::UnicodeString AName, const System::UnicodeString AValue, const Rest::Types::TRESTRequestParameterKind AKind, const Rest::Types::TRESTRequestParameterOptions AOptions = Rest::Types::TRESTRequestParameterOptions() )/* overload */;
	void __fastcall SetCookie(const System::UnicodeString ACookie, const System::UnicodeString AURL);
	void __fastcall SetHTTPHeader(const System::UnicodeString AName, const System::UnicodeString AValue);
	template<typename T> T __fastcall GetEntity(const System::UnicodeString AResource);
	template<typename T> System::Generics::Collections::TObjectList__1<T>* __fastcall GetEntityList(const System::UnicodeString AResource);
#ifndef _WIN64
	template<typename T> System::DynamicArray<T> __fastcall GetEntityArray(const System::UnicodeString AQuery);
#else /* _WIN64 */
	template<typename T> System::TArray__1<T> __fastcall GetEntityArray(const System::UnicodeString AQuery);
#endif /* _WIN64 */
	template<typename T> System::Json::TJSONObject* __fastcall PostEntity(const System::UnicodeString AResource, T AEntity);
	void __fastcall ResetToDefaults();
	void __fastcall Disconnect();
	__property TRESTRequestParameterList* TransientParams = {read=FTransientParams};
	__property bool AutoCreateParams = {read=FAutoCreateParams, write=SetAutoCreateParams, default=1};
	__property TCustomAuthenticator* Authenticator = {read=FAuthenticator, write=SetAuthenticator};
	__property System::UnicodeString Accept = {read=GetAccept, write=SetAccept};
	__property System::UnicodeString AcceptCharset = {read=GetAcceptCharset, write=SetAcceptCharset};
	__property System::UnicodeString AcceptEncoding = {read=GetAcceptEncoding, write=SetAcceptEncoding};
	__property bool AllowCookies = {read=GetAllowCookies, write=SetAllowCookies, default=1};
	__property System::UnicodeString BaseURL = {read=FBaseURL, write=SetBaseURL};
	__property System::UnicodeString ContentType = {read=GetContentType, write=SetContentType};
	__property System::UnicodeString FallbackCharsetEncoding = {read=FFallbackCharsetEncoding, write=SetFallbackCharsetEncoding, stored=FallbackCharsetEncodingIsStored};
	__property TRESTRequestParameterList* Params = {read=FParams, write=SetParams};
	__property bool HandleRedirects = {read=GetHandleRedirects, write=SetHandleRedirects, default=1};
	__property System::Net::Httpclient::THTTPRedirectsWithGET RedirectsWithGET = {read=GetRedirectsWithGET, write=SetRedirectsWithGET, default=4231};
	__property System::Net::Httpclient::THTTPSecureProtocols SecureProtocols = {read=GetSecureProtocols, write=SetSecureProtocols, default=0};
	__property System::UnicodeString ProxyPassword = {read=GetProxyPassword, write=SetProxyPassword};
	__property int ProxyPort = {read=GetProxyPort, write=SetProxyPort, default=0};
	__property System::UnicodeString ProxyServer = {read=GetProxyServer, write=SetProxyServer};
	__property System::UnicodeString ProxyUsername = {read=GetProxyUsername, write=SetProxyUsername};
	__property int ConnectTimeout = {read=GetConnectTimeout, write=SetConnectTimeout, default=30000};
	__property int ReadTimeout = {read=GetReadTimeout, write=SetReadTimeout, default=30000};
	__property bool RaiseExceptionOn500 = {read=FRaiseExceptionOn500, write=FRaiseExceptionOn500, default=1};
	__property bool SynchronizedEvents = {read=FSynchronizedEvents, write=SetSynchronizedEvents, default=1};
	__property System::UnicodeString UserAgent = {read=GetUserAgent, write=SetUserAgent, stored=UserAgentIsStored};
	__property TCustomRESTClientNotifyEvent OnHTTPProtocolError = {read=FOnHTTPProtocolError, write=FOnHTTPProtocolError};
	__property TSubRESTClientBindSource* BindSource = {read=FBindSource};
	__property System::Net::Urlclient::TValidateCertificateEvent OnValidateCertificate = {read=GetOnValidateCertificate, write=SetOnValidateCertificate};
	__property System::Net::Urlclient::TNeedClientCertificateEvent OnNeedClientCertificate = {read=GetNeedClientCertificateEvent, write=SetNeedClientCertificateEvent};
	__property System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent OnAuthEvent = {read=GetAuthEvent, write=SetAuthEvent};
private:
	void *__IRESTRequestParameterListOwnerNotify;	// IRESTRequestParameterListOwnerNotify 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {48713C06-9469-4648-BCF9-FF83C6A58F5D}
	operator _di_IRESTRequestParameterListOwnerNotify()
	{
		_di_IRESTRequestParameterListOwnerNotify intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IRESTRequestParameterListOwnerNotify*(void) { return (IRESTRequestParameterListOwnerNotify*)&__IRESTRequestParameterListOwnerNotify; }
	#endif
	
};


class PASCALIMPLEMENTATION TRESTClientAdapter : public Rest::Bindsource::TRESTComponentAdapter
{
	typedef Rest::Bindsource::TRESTComponentAdapter inherited;
	
	
public:
	class DELPHICLASS TNotify;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TNotify : public TCustomRESTClient::TNotify
	{
		typedef TCustomRESTClient::TNotify inherited;
		
	private:
		TRESTClientAdapter* FAdapter;
		
	protected:
		__fastcall TNotify(TRESTClientAdapter* const AAdapter);
		
	public:
		virtual void __fastcall ParameterListChanged(System::TObject* Sender);
		virtual void __fastcall PropertyValueChanged(System::TObject* Sender);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	TCustomRESTClient* FClient;
	TNotify* FNotify;
	void __fastcall SetClient(TCustomRESTClient* const AClient);
	void __fastcall AddParameterFields();
	void __fastcall ParameterListChanged();
	void __fastcall AddPropertyFields();
	
protected:
	virtual void __fastcall DoChangePosting();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall GetCanActivate();
	virtual void __fastcall AddFields();
	virtual Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetSource();
	
public:
	__fastcall virtual TRESTClientAdapter(System::Classes::TComponent* AComponent);
	__fastcall virtual ~TRESTClientAdapter();
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList);
	__property TCustomRESTClient* Client = {read=FClient, write=SetClient};
};


class PASCALIMPLEMENTATION TCustomRESTClientBindSource : public Rest::Bindsource::TRESTComponentBindSource
{
	typedef Rest::Bindsource::TRESTComponentBindSource inherited;
	
private:
	TRESTClientAdapter* FAdapter;
	TCustomRESTClient* __fastcall GetClient();
	void __fastcall SetClient(TCustomRESTClient* const AValue);
	
protected:
	virtual Rest::Bindsource::TRESTComponentAdapter* __fastcall CreateAdapter();
	
public:
	__property TCustomRESTClient* Client = {read=GetClient, write=SetClient};
	__property TRESTClientAdapter* Adapter = {read=FAdapter};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TCustomRESTClientBindSource(System::Classes::TComponent* AOwner) : Rest::Bindsource::TRESTComponentBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TCustomRESTClientBindSource() { }
	
};


class PASCALIMPLEMENTATION TSubRESTClientBindSource : public TCustomRESTClientBindSource
{
	typedef TCustomRESTClientBindSource inherited;
	
__published:
	__property AutoActivate = {default=1};
	__property AutoEdit = {default=1};
	__property AutoPost = {default=1};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TSubRESTClientBindSource(System::Classes::TComponent* AOwner) : TCustomRESTClientBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TSubRESTClientBindSource() { }
	
};


class PASCALIMPLEMENTATION TRESTClient : public TCustomRESTClient
{
	typedef TCustomRESTClient inherited;
	
__published:
	__property Authenticator;
	__property Accept = {default=0};
	__property AcceptCharset = {default=0};
	__property AcceptEncoding = {default=0};
	__property AllowCookies = {default=1};
	__property AutoCreateParams = {default=1};
	__property BaseURL = {default=0};
	__property ContentType = {default=0};
	__property FallbackCharsetEncoding = {default=0};
	__property Params;
	__property HandleRedirects = {default=1};
	__property RedirectsWithGET = {default=4231};
	__property SecureProtocols = {default=0};
	__property ProxyPassword = {default=0};
	__property ProxyPort = {default=0};
	__property ProxyServer = {default=0};
	__property ProxyUsername = {default=0};
	__property RaiseExceptionOn500 = {default=1};
	__property ConnectTimeout = {default=30000};
	__property ReadTimeout = {default=30000};
	__property SynchronizedEvents = {default=1};
	__property UserAgent = {default=0};
	__property OnHTTPProtocolError;
	__property BindSource;
	__property OnValidateCertificate;
	__property OnNeedClientCertificate;
	__property OnAuthEvent;
public:
	/* TCustomRESTClient.Create */ inline __fastcall TRESTClient(const System::UnicodeString ABaseApiURL)/* overload */ : TCustomRESTClient(ABaseApiURL) { }
	/* TCustomRESTClient.Create */ inline __fastcall virtual TRESTClient(System::Classes::TComponent* AOwner)/* overload */ : TCustomRESTClient(AOwner) { }
	/* TCustomRESTClient.Destroy */ inline __fastcall virtual ~TRESTClient() { }
	
};


typedef void __fastcall (__closure *TAuthenticateEvent)(TCustomRESTRequest* ARequest, bool &ADone);

class PASCALIMPLEMENTATION TCustomAuthenticator : public Data::Bind::Objectscope::TBaseObjectBindSourceDelegate
{
	typedef Data::Bind::Objectscope::TBaseObjectBindSourceDelegate inherited;
	
	
protected:
	typedef Rest::Bindsource::TRESTComponentNotify TNotify;
	
	typedef Rest::Bindsource::TRESTComponentNotifyList__1<Rest::Bindsource::TRESTComponentNotify*>* TNotifyList;
	
	
private:
	Rest::Bindsource::TRESTComponentNotifyList__1<Rest::Bindsource::TRESTComponentNotify*>* FNotifyList;
	TAuthenticateEvent FOnAuthenticate;
	
protected:
	virtual void __fastcall PropertyValueChanged();
	__property Rest::Bindsource::TRESTComponentNotifyList__1<Rest::Bindsource::TRESTComponentNotify*>* NotifyList = {read=FNotifyList};
	virtual void __fastcall DoAuthenticate(TCustomRESTRequest* ARequest) = 0 ;
	
public:
	__fastcall virtual TCustomAuthenticator(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomAuthenticator();
	void __fastcall Authenticate(TCustomRESTRequest* ARequest);
	virtual void __fastcall ResetToDefaults();
	
__published:
	__property TAuthenticateEvent OnAuthenticate = {read=FOnAuthenticate, write=FOnAuthenticate};
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TRESTAuthenticatorAdapter__1 : public Rest::Bindsource::TRESTComponentAdapter
{
	typedef Rest::Bindsource::TRESTComponentAdapter inherited;
	
	
private:
	T FAuthenticator;
	void __fastcall SetAuthenticator(const T AAuthenticator);
	Rest::Bindsource::TRESTComponentAdapter::TNotify* FNotify;
	
protected:
	virtual Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetSource();
	virtual void __fastcall DoAuthenticatorChanging();
	virtual void __fastcall DoAuthenticatorChanged();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall GetCanActivate();
	
public:
	__fastcall virtual TRESTAuthenticatorAdapter__1(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TRESTAuthenticatorAdapter__1();
	__property T Authenticator = {read=FAuthenticator, write=SetAuthenticator};
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TRESTAuthenticatorBindSource__1 : public Rest::Bindsource::TRESTComponentBindSource
{
	typedef Rest::Bindsource::TRESTComponentBindSource inherited;
	
private:
	TRESTAuthenticatorAdapter__1<T>* FAdapter;
	TCustomAuthenticator* __fastcall GetAuthenticator();
	void __fastcall SetAuthenticator(TCustomAuthenticator* const Value);
	
protected:
	virtual Rest::Bindsource::TRESTComponentAdapter* __fastcall CreateAdapter();
	virtual TRESTAuthenticatorAdapter__1<T>* __fastcall CreateAdapterT();
	
public:
	__property TCustomAuthenticator* Authenticator = {read=GetAuthenticator, write=SetAuthenticator};
	__property TRESTAuthenticatorAdapter__1<T>* Adapter = {read=FAdapter};
	
__published:
	__property AutoActivate = {default=1};
	__property AutoEdit = {default=1};
	__property AutoPost = {default=1};
public:
	/* TRESTComponentBindSource.Create */ inline __fastcall virtual TRESTAuthenticatorBindSource__1(System::Classes::TComponent* AOwner) : Rest::Bindsource::TRESTComponentBindSource(AOwner) { }
	
public:
	/* TBaseObjectBindSource.Destroy */ inline __fastcall virtual ~TRESTAuthenticatorBindSource__1() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDownloadURL : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static void __fastcall CheckForError(TCustomRESTResponse* const AResponse);
	
public:
	static void __fastcall DownloadRawBytes(const System::UnicodeString AURL, System::Classes::TStream* const AStream);
public:
	/* TObject.Create */ inline __fastcall TDownloadURL() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDownloadURL() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define RESTCLIENT_VERSION L"1.0"
}	/* namespace Client */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_CLIENT)
using namespace Rest::Client;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_ClientHPP
