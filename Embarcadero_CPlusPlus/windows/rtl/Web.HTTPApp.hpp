// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.HTTPApp.pas' rev: 34.00 (Windows)

#ifndef Web_HttpappHPP
#define Web_HttpappHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Masks.hpp>
#include <System.Generics.Collections.hpp>
#include <Web.WebFileDispatcher.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Httpapp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWebRequest;
class DELPHICLASS TAbstractContentParser;
class DELPHICLASS TContentParser;
class DELPHICLASS TAbstractWebRequestFiles;
class DELPHICLASS TAbstractWebRequestFile;
class DELPHICLASS TCookie;
struct TCookieHelper /* Helper for class 'TCookie*' */;
class DELPHICLASS TCookieCollection;
class DELPHICLASS TWebResponse;
__interface DELPHIINTERFACE ISetAppDispatcher;
typedef System::DelphiInterface<ISetAppDispatcher> _di_ISetAppDispatcher;
__interface DELPHIINTERFACE IProduceContent;
typedef System::DelphiInterface<IProduceContent> _di_IProduceContent;
__interface DELPHIINTERFACE IProduceContentFrom;
typedef System::DelphiInterface<IProduceContentFrom> _di_IProduceContentFrom;
__interface DELPHIINTERFACE IWebAppServices180;
typedef System::DelphiInterface<IWebAppServices180> _di_IWebAppServices180;
__interface DELPHIINTERFACE IWebAppServices;
typedef System::DelphiInterface<IWebAppServices> _di_IWebAppServices;
__interface DELPHIINTERFACE IWebExceptionHandler;
typedef System::DelphiInterface<IWebExceptionHandler> _di_IWebExceptionHandler;
__interface DELPHIINTERFACE IGetWebAppServices;
typedef System::DelphiInterface<IGetWebAppServices> _di_IGetWebAppServices;
__interface DELPHIINTERFACE IWebRequestHandler;
typedef System::DelphiInterface<IWebRequestHandler> _di_IWebRequestHandler;
__interface DELPHIINTERFACE IWebDispatchActions;
typedef System::DelphiInterface<IWebDispatchActions> _di_IWebDispatchActions;
__interface DELPHIINTERFACE IGetWebRequestHandler;
typedef System::DelphiInterface<IGetWebRequestHandler> _di_IGetWebRequestHandler;
__interface DELPHIINTERFACE IWebDispatcherAccess;
typedef System::DelphiInterface<IWebDispatcherAccess> _di_IWebDispatcherAccess;
class DELPHICLASS TCustomContentProducer;
class DELPHICLASS TWebActionItem;
class DELPHICLASS TWebActionItems;
__interface DELPHIINTERFACE IWebDispatch;
typedef System::DelphiInterface<IWebDispatch> _di_IWebDispatch;
class DELPHICLASS TCustomWebDispatcher;
class DELPHICLASS TWebDispatcher;
class DELPHICLASS TCustomWebFileDispatcher;
class DELPHICLASS TWebFileDispatcher;
class DELPHICLASS TWebModule;
class DELPHICLASS TDefaultWebAppServices;
class DELPHICLASS EWebBrokerException;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TWebExceptionEvent)(System::TObject* Sender, System::Sysutils::Exception* E, bool &Handled);

enum DECLSPEC_DENUM TMethodType : unsigned char { mtAny, mtGet, mtPut, mtPost, mtHead, mtDelete, mtPatch };

typedef System::Set<char, _DELPHI_SET_CHAR(0), _DELPHI_SET_CHAR(255)> TExtractCharSet;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWebRequest : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TAbstractContentParser* FContentParser;
	TMethodType FMethodType;
	System::Classes::TStrings* FCookieFields;
	System::Classes::TStrings* FQueryFields;
	TAbstractContentParser* __fastcall GetContentParser();
	System::Classes::TStrings* __fastcall GetContentFields();
	System::Classes::TStrings* __fastcall GetCookieFields();
	System::Classes::TStrings* __fastcall GetQueryFields();
	TAbstractWebRequestFiles* __fastcall GetFiles();
	System::UnicodeString __fastcall GetContent();
	
protected:
	virtual System::UnicodeString __fastcall GetRemoteIP();
#ifndef _WIN64
	virtual System::DynamicArray<System::Byte> __fastcall GetRawContent() = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<System::Byte> __fastcall GetRawContent() = 0 ;
#endif /* _WIN64 */
	virtual System::UnicodeString __fastcall GetStringVariable(int Index) = 0 ;
	virtual System::TDateTime __fastcall GetDateVariable(int Index) = 0 ;
	virtual int __fastcall GetIntegerVariable(int Index) = 0 ;
	virtual System::UnicodeString __fastcall GetInternalPathInfo();
	virtual System::UnicodeString __fastcall GetRawPathInfo();
	virtual System::UnicodeString __fastcall GetInternalScriptName();
	void __fastcall UpdateMethodType();
	virtual void __fastcall DoReadTotalContent();
	
public:
	__fastcall TWebRequest();
	__fastcall virtual ~TWebRequest();
	virtual int __fastcall ReadClient(void *Buffer, int Count) = 0 ;
	virtual System::UnicodeString __fastcall ReadString(int Count) = 0 ;
	System::UnicodeString __fastcall ReadUnicodeString(int Count);
	virtual System::UnicodeString __fastcall TranslateURI(const System::UnicodeString URI) = 0 ;
	virtual int __fastcall WriteClient(void *Buffer, int Count) = 0 ;
	virtual bool __fastcall WriteString(const System::UnicodeString AString) = 0 ;
	virtual bool __fastcall WriteHeaders(int StatusCode, const System::UnicodeString ReasonString, const System::UnicodeString Headers) = 0 ;
	void __fastcall ExtractFields(const TExtractCharSet &Separators, const TExtractCharSet &_WhiteSpace, const System::UnicodeString Content, System::Classes::TStrings* Strings)/* overload */;
	void __fastcall ExtractContentFields(System::Classes::TStrings* Strings);
	void __fastcall ExtractCookieFields(System::Classes::TStrings* Strings);
	void __fastcall ExtractQueryFields(System::Classes::TStrings* Strings);
	virtual System::UnicodeString __fastcall GetFieldByName(const System::UnicodeString Name) = 0 ;
	void __fastcall ReadTotalContent();
	__property TMethodType MethodType = {read=FMethodType, nodefault};
	__property TAbstractContentParser* ContentParser = {read=GetContentParser};
	__property System::Classes::TStrings* ContentFields = {read=GetContentFields};
	__property System::Classes::TStrings* CookieFields = {read=GetCookieFields};
	__property System::Classes::TStrings* QueryFields = {read=GetQueryFields};
	__property System::UnicodeString Method = {read=GetStringVariable, index=0};
	__property System::UnicodeString ProtocolVersion = {read=GetStringVariable, index=1};
	__property System::UnicodeString URL = {read=GetStringVariable, index=2};
	__property System::UnicodeString Query = {read=GetStringVariable, index=3};
	__property System::UnicodeString PathInfo = {read=GetStringVariable, index=4};
	__property System::UnicodeString PathTranslated = {read=GetStringVariable, index=5};
	__property System::UnicodeString Authorization = {read=GetStringVariable, index=28};
	__property System::UnicodeString CacheControl = {read=GetStringVariable, index=6};
	__property System::UnicodeString Cookie = {read=GetStringVariable, index=27};
	__property System::TDateTime Date = {read=GetDateVariable, index=7};
	__property System::UnicodeString Accept = {read=GetStringVariable, index=8};
	__property System::UnicodeString From = {read=GetStringVariable, index=9};
	__property System::UnicodeString Host = {read=GetStringVariable, index=10};
	__property System::TDateTime IfModifiedSince = {read=GetDateVariable, index=11};
	__property System::UnicodeString Referer = {read=GetStringVariable, index=12};
	__property System::UnicodeString UserAgent = {read=GetStringVariable, index=13};
	__property System::UnicodeString ContentEncoding = {read=GetStringVariable, index=14};
	__property System::UnicodeString ContentType = {read=GetStringVariable, index=15};
	__property int ContentLength = {read=GetIntegerVariable, index=16, nodefault};
	__property System::UnicodeString ContentVersion = {read=GetStringVariable, index=17};
#ifndef _WIN64
	__property System::DynamicArray<System::Byte> RawContent = {read=GetRawContent};
#else /* _WIN64 */
	__property System::TArray__1<System::Byte> RawContent = {read=GetRawContent};
#endif /* _WIN64 */
	__property System::UnicodeString Content = {read=GetContent};
	__property System::UnicodeString Connection = {read=GetStringVariable, index=26};
	__property System::UnicodeString DerivedFrom = {read=GetStringVariable, index=18};
	__property System::TDateTime Expires = {read=GetDateVariable, index=19};
	__property System::UnicodeString Title = {read=GetStringVariable, index=20};
	__property System::UnicodeString RemoteAddr = {read=GetStringVariable, index=21};
	__property System::UnicodeString RemoteHost = {read=GetStringVariable, index=22};
	__property System::UnicodeString ScriptName = {read=GetStringVariable, index=23};
	__property int ServerPort = {read=GetIntegerVariable, index=24, nodefault};
	__property System::UnicodeString InternalPathInfo = {read=GetInternalPathInfo};
	__property System::UnicodeString RawPathInfo = {read=GetRawPathInfo};
	__property System::UnicodeString InternalScriptName = {read=GetInternalScriptName};
	__property TAbstractWebRequestFiles* Files = {read=GetFiles};
	__property System::UnicodeString RemoteIP = {read=GetRemoteIP};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAbstractContentParser : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TWebRequest* FWebRequest;
	
protected:
	__property TWebRequest* WebRequest = {read=FWebRequest};
	virtual System::Classes::TStrings* __fastcall GetContentFields() = 0 ;
	virtual TAbstractWebRequestFiles* __fastcall GetFiles() = 0 ;
	
public:
	__fastcall virtual TAbstractContentParser(TWebRequest* AWebRequest);
	__classmethod virtual bool __fastcall CanParse(TWebRequest* AWebRequest);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAbstractContentParser() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TContentParser : public TAbstractContentParser
{
	typedef TAbstractContentParser inherited;
	
private:
	System::Classes::TStrings* FContentFields;
	TAbstractWebRequestFiles* FFiles;
	
public:
	__fastcall virtual ~TContentParser();
	virtual System::Classes::TStrings* __fastcall GetContentFields();
	virtual TAbstractWebRequestFiles* __fastcall GetFiles();
	__classmethod virtual bool __fastcall CanParse(TWebRequest* AWebRequest);
public:
	/* TAbstractContentParser.Create */ inline __fastcall virtual TContentParser(TWebRequest* AWebRequest) : TAbstractContentParser(AWebRequest) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TContentParserClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TContentParserClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAbstractWebRequestFiles : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	TAbstractWebRequestFile* operator[](int I) { return this->Items[I]; }
	
protected:
	virtual int __fastcall GetCount() = 0 ;
	virtual TAbstractWebRequestFile* __fastcall GetItem(int I) = 0 ;
	
public:
	__property TAbstractWebRequestFile* Items[int I] = {read=GetItem/*, default*/};
	__property int Count = {read=GetCount, nodefault};
public:
	/* TObject.Create */ inline __fastcall TAbstractWebRequestFiles() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAbstractWebRequestFiles() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAbstractWebRequestFile : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetFieldName() = 0 ;
	virtual System::UnicodeString __fastcall GetFileName() = 0 ;
	virtual System::Classes::TStream* __fastcall GetStream() = 0 ;
	virtual System::UnicodeString __fastcall GetContentType() = 0 ;
	
public:
	__property System::UnicodeString FieldName = {read=GetFieldName};
	__property System::UnicodeString FileName = {read=GetFileName};
	__property System::Classes::TStream* Stream = {read=GetStream};
	__property System::UnicodeString ContentType = {read=GetContentType};
public:
	/* TObject.Create */ inline __fastcall TAbstractWebRequestFile() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAbstractWebRequestFile() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TCookie : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	System::UnicodeString FValue;
	System::UnicodeString FPath;
	System::UnicodeString FDomain;
	System::TDateTime FExpires;
	bool FSecure;
	bool FHttpOnly;
	
protected:
	System::UnicodeString __fastcall GetHeaderValue();
	
public:
	__fastcall virtual TCookie(System::Classes::TCollection* Collection);
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property System::UnicodeString Value = {read=FValue, write=FValue};
	__property System::UnicodeString Domain = {read=FDomain, write=FDomain};
	__property System::UnicodeString Path = {read=FPath, write=FPath};
	__property System::TDateTime Expires = {read=FExpires, write=FExpires};
	__property bool Secure = {read=FSecure, write=FSecure, nodefault};
	__property System::UnicodeString HeaderValue = {read=GetHeaderValue};
	__property bool HttpOnly = {read=FHttpOnly, write=FHttpOnly, nodefault};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TCookie() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCookieCollection : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TCookie* operator[](int Index) { return this->Items[Index]; }
	
private:
	TWebResponse* FWebResponse;
	
protected:
	TCookie* __fastcall GetCookie(int Index);
	void __fastcall SetCookie(int Index, TCookie* Cookie);
	
public:
	__fastcall TCookieCollection(TWebResponse* WebResponse, System::Classes::TCollectionItemClass ItemClass);
	HIDESBASE TCookie* __fastcall Add();
	__property TWebResponse* WebResponse = {read=FWebResponse};
	__property TCookie* Items[int Index] = {read=GetCookie, write=SetCookie/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TCookieCollection() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWebResponse : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	bool FFreeContentStream;
	System::Classes::TStream* FContentStream;
	TCookieCollection* FCookies;
	void __fastcall SetCustomHeaders(System::Classes::TStrings* Value);
	
protected:
	TWebRequest* FHTTPRequest;
	System::Classes::TStrings* FCustomHeaders;
	void __fastcall AddCustomHeaders(System::UnicodeString &Headers);
	virtual System::UnicodeString __fastcall GetStringVariable(int Index) = 0 ;
	virtual void __fastcall SetStringVariable(int Index, const System::UnicodeString Value) = 0 ;
	virtual System::TDateTime __fastcall GetDateVariable(int Index) = 0 ;
	virtual void __fastcall SetDateVariable(int Index, const System::TDateTime Value) = 0 ;
	virtual int __fastcall GetIntegerVariable(int Index) = 0 ;
	virtual void __fastcall SetIntegerVariable(int Index, int Value) = 0 ;
	virtual System::UnicodeString __fastcall GetContent() = 0 ;
	virtual void __fastcall SetContent(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetContentStream(System::Classes::TStream* Value);
	virtual int __fastcall GetStatusCode() = 0 ;
	virtual void __fastcall SetStatusCode(int Value) = 0 ;
	virtual System::UnicodeString __fastcall GetLogMessage() = 0 ;
	virtual void __fastcall SetLogMessage(const System::UnicodeString Value) = 0 ;
	System::UnicodeString __fastcall FormatAuthenticate();
	
public:
	__fastcall TWebResponse(TWebRequest* HTTPRequest);
	__fastcall virtual ~TWebResponse();
	System::UnicodeString __fastcall GetCustomHeader(const System::UnicodeString Name);
	virtual void __fastcall SendResponse() = 0 ;
	virtual void __fastcall SendRedirect(const System::UnicodeString URI) = 0 ;
	virtual void __fastcall SendStream(System::Classes::TStream* AStream) = 0 ;
	virtual bool __fastcall Sent();
	void __fastcall SetCookieField(System::Classes::TStrings* Values, const System::UnicodeString ADomain, const System::UnicodeString APath, System::TDateTime AExpires, bool ASecure, bool AHttpOnly = false);
	void __fastcall SetCustomHeader(const System::UnicodeString Name, const System::UnicodeString Value);
	__property TCookieCollection* Cookies = {read=FCookies};
	__property TWebRequest* HTTPRequest = {read=FHTTPRequest};
	__property System::UnicodeString Version = {read=GetStringVariable, write=SetStringVariable, index=0};
	__property System::UnicodeString ReasonString = {read=GetStringVariable, write=SetStringVariable, index=1};
	__property System::UnicodeString Server = {read=GetStringVariable, write=SetStringVariable, index=2};
	__property System::UnicodeString WWWAuthenticate = {read=GetStringVariable, write=SetStringVariable, index=3};
	__property System::UnicodeString Realm = {read=GetStringVariable, write=SetStringVariable, index=4};
	__property System::UnicodeString Allow = {read=GetStringVariable, write=SetStringVariable, index=5};
	__property System::UnicodeString Location = {read=GetStringVariable, write=SetStringVariable, index=6};
	__property System::UnicodeString ContentEncoding = {read=GetStringVariable, write=SetStringVariable, index=7};
	__property System::UnicodeString ContentType = {read=GetStringVariable, write=SetStringVariable, index=8};
	__property System::UnicodeString ContentVersion = {read=GetStringVariable, write=SetStringVariable, index=9};
	__property System::UnicodeString DerivedFrom = {read=GetStringVariable, write=SetStringVariable, index=10};
	__property System::UnicodeString Title = {read=GetStringVariable, write=SetStringVariable, index=11};
	__property int StatusCode = {read=GetStatusCode, write=SetStatusCode, nodefault};
	__property int ContentLength = {read=GetIntegerVariable, write=SetIntegerVariable, index=0, nodefault};
	__property System::TDateTime Date = {read=GetDateVariable, write=SetDateVariable, index=0};
	__property System::TDateTime Expires = {read=GetDateVariable, write=SetDateVariable, index=1};
	__property System::TDateTime LastModified = {read=GetDateVariable, write=SetDateVariable, index=2};
	__property System::UnicodeString Content = {read=GetContent, write=SetContent};
	__property System::Classes::TStream* ContentStream = {read=FContentStream, write=SetContentStream};
	__property System::UnicodeString LogMessage = {read=GetLogMessage, write=SetLogMessage};
	__property System::Classes::TStrings* CustomHeaders = {read=FCustomHeaders, write=SetCustomHeaders};
	__property bool FreeContentStream = {read=FFreeContentStream, write=FFreeContentStream, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{2F5E959E-DA65-11D3-A411-00C04F6BB853}") ISetAppDispatcher  : public System::IInterface 
{
	virtual void __fastcall SetAppDispatcher(System::Classes::TComponent* const ADispatcher) = 0 ;
};

__interface  INTERFACE_UUID("{AAFA17B7-E814-11D4-A54A-00C04F6BB853}") IProduceContent  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall ProduceContent() = 0 ;
};

__interface  INTERFACE_UUID("{AA0CC875-E81B-11D4-A54A-00C04F6BB853}") IProduceContentFrom  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall ProduceContentFromStream(System::Classes::TStream* Stream) = 0 ;
	virtual System::UnicodeString __fastcall ProduceContentFromString(const System::UnicodeString S) = 0 ;
};

__interface  INTERFACE_UUID("{D62F1586-E307-11D3-A418-00C04F6BB853}") IWebAppServices180  : public System::IInterface 
{
	virtual void __fastcall InitContext(System::Classes::TComponent* WebModule, TWebRequest* Request, TWebResponse* Response) = 0 ;
	virtual bool __fastcall HandleRequest() = 0 ;
	virtual void __fastcall FinishContext() = 0 ;
	virtual System::TObject* __fastcall GetExceptionHandler() = 0 ;
	__property System::TObject* ExceptionHandler = {read=GetExceptionHandler};
};

__interface  INTERFACE_UUID("{8B627D59-897B-452C-9633-05CC3A634196}") IWebAppServices  : public IWebAppServices180 
{
	virtual bool __fastcall GetActive() = 0 ;
	__property bool Active = {read=GetActive};
};

__interface  INTERFACE_UUID("{7664268F-9629-11D4-A4EC-00C04F6BB853}") IWebExceptionHandler  : public System::IInterface 
{
	virtual void __fastcall HandleException(System::Sysutils::Exception* E, bool &Handled) = 0 ;
};

__interface  INTERFACE_UUID("{5CF7B3BD-DAB0-D511-99A8-0050568E0E44}") IGetWebAppServices  : public System::IInterface 
{
	virtual _di_IWebAppServices __fastcall GetWebAppServices() = 0 ;
};

__interface  INTERFACE_UUID("{6FCCB05F-8FE0-11D4-A4E5-00C04F6BB853}") IWebRequestHandler  : public System::IInterface 
{
	virtual bool __fastcall HandleRequest(TWebRequest* Request, TWebResponse* Response) = 0 ;
};

__interface  INTERFACE_UUID("{E4444CD8-9FAE-D511-8D38-0050568E0E44}") IWebDispatchActions  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{6FCCB060-8FE0-11D4-A4E5-00C04F6BB853}") IGetWebRequestHandler  : public System::IInterface 
{
	virtual _di_IWebRequestHandler __fastcall GetWebRequestHandler() = 0 ;
};

__interface  INTERFACE_UUID("{144CD1DF-9FAE-D511-8D38-0050568E0E44}") IWebDispatcherAccess  : public System::IInterface 
{
	virtual TWebRequest* __fastcall Request() = 0 ;
	virtual TWebResponse* __fastcall Response() = 0 ;
};

class PASCALIMPLEMENTATION TCustomContentProducer : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Classes::TComponent* FDispatcher;
	_di_IWebDispatcherAccess __fastcall GetDispatcher();
	void __fastcall SetDispatcher(System::Classes::TComponent* Value);
	
protected:
	System::UnicodeString __fastcall ProduceContent();
	System::UnicodeString __fastcall ProduceContentFromStream(System::Classes::TStream* Stream);
	System::UnicodeString __fastcall ProduceContentFromString(const System::UnicodeString S);
	void __fastcall SetAppDispatcher(System::Classes::TComponent* const ADispatcher);
	System::Classes::TComponent* __fastcall GetAppDispatcher();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	virtual System::UnicodeString __fastcall Content();
	virtual System::UnicodeString __fastcall ContentFromStream(System::Classes::TStream* Stream);
	virtual System::UnicodeString __fastcall ContentFromString(const System::UnicodeString S);
	__property _di_IWebDispatcherAccess Dispatcher = {read=GetDispatcher};
	__property System::Classes::TComponent* DispatcherComponent = {read=FDispatcher};
public:
	/* TComponent.Create */ inline __fastcall virtual TCustomContentProducer(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomContentProducer() { }
	
private:
	void *__IProduceContentFrom;	// IProduceContentFrom 
	void *__IProduceContent;	// IProduceContent 
	void *__ISetAppDispatcher;	// ISetAppDispatcher 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AA0CC875-E81B-11D4-A54A-00C04F6BB853}
	operator _di_IProduceContentFrom()
	{
		_di_IProduceContentFrom intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IProduceContentFrom*(void) { return (IProduceContentFrom*)&__IProduceContentFrom; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AAFA17B7-E814-11D4-A54A-00C04F6BB853}
	operator _di_IProduceContent()
	{
		_di_IProduceContent intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IProduceContent*(void) { return (IProduceContent*)&__IProduceContent; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2F5E959E-DA65-11D3-A411-00C04F6BB853}
	operator _di_ISetAppDispatcher()
	{
		_di_ISetAppDispatcher intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ISetAppDispatcher*(void) { return (ISetAppDispatcher*)&__ISetAppDispatcher; }
	#endif
	
};


typedef void __fastcall (__closure *THTTPMethodEvent)(System::TObject* Sender, TWebRequest* Request, TWebResponse* Response, bool &Handled);

class PASCALIMPLEMENTATION TWebActionItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	THTTPMethodEvent FOnAction;
	System::UnicodeString FPathInfo;
	TMethodType FMethodType;
	bool FDefault;
	bool FEnabled;
	System::UnicodeString FMaskPathInfo;
	System::Masks::TMask* FMask;
	System::UnicodeString FName;
	TCustomContentProducer* FProducer;
	System::Classes::TComponent* FProducerContent;
	bool __fastcall DispatchAction(TWebRequest* Request, TWebResponse* Response, bool DoDefault);
	void __fastcall SetDefault(bool Value);
	void __fastcall SetEnabled(bool Value);
	void __fastcall SetMethodType(TMethodType Value);
	void __fastcall SetOnAction(THTTPMethodEvent Value);
	void __fastcall SetPathInfo(const System::UnicodeString Value);
	void __fastcall SetProducer(TCustomContentProducer* const Value);
	System::Masks::TMask* __fastcall GetMask();
	System::UnicodeString __fastcall ProducerPathInfo();
	void __fastcall SetProducerContent(System::Classes::TComponent* const Value);
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual void __fastcall SetDisplayName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetPathInfo();
	
public:
	__fastcall virtual TWebActionItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TWebActionItem();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
__published:
	__property bool Default = {read=FDefault, write=SetDefault, default=0};
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=1};
	__property TMethodType MethodType = {read=FMethodType, write=SetMethodType, default=0};
	__property System::UnicodeString Name = {read=GetDisplayName, write=SetDisplayName};
	__property System::UnicodeString PathInfo = {read=GetPathInfo, write=SetPathInfo};
	__property TCustomContentProducer* Producer = {read=FProducer, write=SetProducer};
	__property System::Classes::TComponent* ProducerContent = {read=FProducerContent, write=SetProducerContent};
	__property THTTPMethodEvent OnAction = {read=FOnAction, write=SetOnAction};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWebActionItems : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
	
public:
	class DELPHICLASS TEnumerator;
	class PASCALIMPLEMENTATION TEnumerator : public System::Classes::TCollectionEnumerator
	{
		typedef System::Classes::TCollectionEnumerator inherited;
		
	public:
		HIDESBASE TWebActionItem* __fastcall GetCurrent();
		__property TWebActionItem* Current = {read=GetCurrent};
	public:
		/* TCollectionEnumerator.Create */ inline __fastcall TEnumerator(System::Classes::TCollection* ACollection) : System::Classes::TCollectionEnumerator(ACollection) { }
		
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TEnumerator() { }
		
	};
	
	
	
public:
	TWebActionItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	TCustomWebDispatcher* FWebDispatcher;
	TWebActionItem* __fastcall GetActionItem(int Index);
	void __fastcall SetActionItem(int Index, TWebActionItem* Value);
	
protected:
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	virtual void __fastcall SetItemName(System::Classes::TCollectionItem* Item);
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	
public:
	__fastcall TWebActionItems(TCustomWebDispatcher* WebDispatcher, System::Classes::TCollectionItemClass ItemClass);
	HIDESBASE TEnumerator* __fastcall GetEnumerator();
	HIDESBASE TWebActionItem* __fastcall Add();
	__property TCustomWebDispatcher* WebDispatcher = {read=FWebDispatcher};
	__property TWebActionItem* Items[int Index] = {read=GetActionItem, write=SetActionItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TWebActionItems() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{E6D33BE4-9FAE-D511-8D38-0050568E0E44}") IWebDispatch  : public System::IInterface 
{
	virtual bool __fastcall DispatchEnabled() = 0 ;
	virtual TMethodType __fastcall DispatchMethodType() = 0 ;
	virtual bool __fastcall DispatchRequest(System::TObject* Sender, TWebRequest* Request, TWebResponse* Response) = 0 ;
	virtual System::Masks::TMask* __fastcall DispatchMask() = 0 ;
	__property bool Enabled = {read=DispatchEnabled};
	__property TMethodType MethodType = {read=DispatchMethodType};
	__property System::Masks::TMask* Mask = {read=DispatchMask};
};

class PASCALIMPLEMENTATION TCustomWebDispatcher : public System::Classes::TDataModule
{
	typedef System::Classes::TDataModule inherited;
	
private:
	TWebRequest* FRequest;
	TWebResponse* FResponse;
	TWebActionItems* FActions;
	THTTPMethodEvent FBeforeDispatch;
	THTTPMethodEvent FAfterDispatch;
	System::Generics::Collections::TObjectList__1<System::Classes::TComponent*>* FDispatchList;
	TWebExceptionEvent FOnException;
	TWebActionItem* __fastcall GetAction(int Index);
	void __fastcall SetActions(TWebActionItems* Value);
	TWebRequest* __fastcall GetRequest();
	TWebResponse* __fastcall GetResponse();
	
protected:
	bool __fastcall HandleRequest(TWebRequest* Request, TWebResponse* Response);
	TWebRequest* __fastcall Access_Request();
	TWebResponse* __fastcall Access_Response();
	void __fastcall HandleException(System::Sysutils::Exception* E, bool &Handled);
	bool __fastcall DoAfterDispatch(TWebRequest* Request, TWebResponse* Response);
	bool __fastcall DoBeforeDispatch(TWebRequest* Request, TWebResponse* Response);
	bool __fastcall DispatchAction(TWebRequest* Request, TWebResponse* Response);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	__property THTTPMethodEvent BeforeDispatch = {read=FBeforeDispatch, write=FBeforeDispatch};
	__property THTTPMethodEvent AfterDispatch = {read=FAfterDispatch, write=FAfterDispatch};
	
public:
	__fastcall virtual TCustomWebDispatcher(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomWebDispatcher();
	TWebActionItem* __fastcall ActionByName(const System::UnicodeString AName);
	__property TWebActionItems* Actions = {read=FActions, write=SetActions};
	__property TWebActionItem* Action[int Index] = {read=GetAction};
	__property TWebRequest* Request = {read=GetRequest};
	__property TWebResponse* Response = {read=GetResponse};
	__property TWebExceptionEvent OnException = {read=FOnException, write=FOnException};
public:
	/* TDataModule.CreateNew */ inline __fastcall virtual TCustomWebDispatcher(System::Classes::TComponent* AOwner, int Dummy) : System::Classes::TDataModule(AOwner, Dummy) { }
	
private:
	void *__IWebExceptionHandler;	// IWebExceptionHandler 
	void *__IWebDispatcherAccess;	// IWebDispatcherAccess 
	void *__IWebDispatchActions;	// IWebDispatchActions 
	void *__IWebRequestHandler;	// IWebRequestHandler 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7664268F-9629-11D4-A4EC-00C04F6BB853}
	operator _di_IWebExceptionHandler()
	{
		_di_IWebExceptionHandler intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWebExceptionHandler*(void) { return (IWebExceptionHandler*)&__IWebExceptionHandler; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {144CD1DF-9FAE-D511-8D38-0050568E0E44}
	operator _di_IWebDispatcherAccess()
	{
		_di_IWebDispatcherAccess intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWebDispatcherAccess*(void) { return (IWebDispatcherAccess*)&__IWebDispatcherAccess; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E4444CD8-9FAE-D511-8D38-0050568E0E44}
	operator _di_IWebDispatchActions()
	{
		_di_IWebDispatchActions intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWebDispatchActions*(void) { return (IWebDispatchActions*)&__IWebDispatchActions; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6FCCB05F-8FE0-11D4-A4E5-00C04F6BB853}
	operator _di_IWebRequestHandler()
	{
		_di_IWebRequestHandler intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWebRequestHandler*(void) { return (IWebRequestHandler*)&__IWebRequestHandler; }
	#endif
	
};


class PASCALIMPLEMENTATION TWebDispatcher : public TCustomWebDispatcher
{
	typedef TCustomWebDispatcher inherited;
	
__published:
	__property Actions;
	__property BeforeDispatch;
	__property AfterDispatch;
	__property OnException;
public:
	/* TCustomWebDispatcher.Create */ inline __fastcall virtual TWebDispatcher(System::Classes::TComponent* AOwner) : TCustomWebDispatcher(AOwner) { }
	/* TCustomWebDispatcher.Destroy */ inline __fastcall virtual ~TWebDispatcher() { }
	
public:
	/* TDataModule.CreateNew */ inline __fastcall virtual TWebDispatcher(System::Classes::TComponent* AOwner, int Dummy) : TCustomWebDispatcher(AOwner, Dummy) { }
	
};


typedef void __fastcall (__closure *TDispatchFileEvent)(System::TObject* Sender, const System::UnicodeString AFileName, TWebRequest* Request, TWebResponse* Response, bool &Handled);

class PASCALIMPLEMENTATION TCustomWebFileDispatcher : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Web::Webfiledispatcher::TWebFileDispatcherProperties* FFileDispatcherProperties;
	System::Masks::TMask* FMask;
	TDispatchFileEvent FBeforeDispatch;
	TDispatchFileEvent FAfterDispatch;
	void __fastcall SetWebFileExtensions(Web::Webfiledispatcher::TWebFileExtensions* const Value);
	Web::Webfiledispatcher::TWebFileExtensions* __fastcall GetWebFileExtensions();
	void __fastcall SetWebDirectories(Web::Webfiledispatcher::TWebDirectories* const Value);
	Web::Webfiledispatcher::TWebDirectories* __fastcall GetWebDirectories();
	System::UnicodeString __fastcall GetRootDirectory();
	void __fastcall SetRootDirectory(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetVirtualPath();
	void __fastcall SetVirtualPath(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetDefaultFile();
	void __fastcall SetDefaultFile(const System::UnicodeString Value);
	
protected:
	bool __fastcall DispatchEnabled();
	System::Masks::TMask* __fastcall DispatchMask();
	TMethodType __fastcall DispatchMethodType();
	bool __fastcall DispatchRequest(System::TObject* Sender, TWebRequest* Request, TWebResponse* Response);
	__property TDispatchFileEvent BeforeDispatch = {read=FBeforeDispatch, write=FBeforeDispatch};
	__property TDispatchFileEvent AfterDispatch = {read=FAfterDispatch, write=FAfterDispatch};
	
public:
	__fastcall virtual TCustomWebFileDispatcher(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomWebFileDispatcher();
	__property Web::Webfiledispatcher::TWebFileExtensions* WebFileExtensions = {read=GetWebFileExtensions, write=SetWebFileExtensions};
	__property Web::Webfiledispatcher::TWebDirectories* WebDirectories = {read=GetWebDirectories, write=SetWebDirectories};
	__property System::UnicodeString RootDirectory = {read=GetRootDirectory, write=SetRootDirectory};
	__property System::UnicodeString VirtualPath = {read=GetVirtualPath, write=SetVirtualPath};
	__property System::UnicodeString DefaultFile = {read=GetDefaultFile, write=SetDefaultFile};
private:
	void *__IWebDispatch;	// IWebDispatch 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E6D33BE4-9FAE-D511-8D38-0050568E0E44}
	operator _di_IWebDispatch()
	{
		_di_IWebDispatch intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWebDispatch*(void) { return (IWebDispatch*)&__IWebDispatch; }
	#endif
	
};


class PASCALIMPLEMENTATION TWebFileDispatcher : public TCustomWebFileDispatcher
{
	typedef TCustomWebFileDispatcher inherited;
	
__published:
	__property WebFileExtensions;
	__property BeforeDispatch;
	__property AfterDispatch;
	__property WebDirectories;
	__property RootDirectory = {default=0};
	__property VirtualPath = {default=0};
	__property DefaultFile = {default=0};
public:
	/* TCustomWebFileDispatcher.Create */ inline __fastcall virtual TWebFileDispatcher(System::Classes::TComponent* AOwner) : TCustomWebFileDispatcher(AOwner) { }
	/* TCustomWebFileDispatcher.Destroy */ inline __fastcall virtual ~TWebFileDispatcher() { }
	
};


class PASCALIMPLEMENTATION TWebModule : public TCustomWebDispatcher
{
	typedef TCustomWebDispatcher inherited;
	
public:
	__fastcall virtual TWebModule(System::Classes::TComponent* AOwner);
	
__published:
	__property Actions;
	__property BeforeDispatch;
	__property AfterDispatch;
	__property OnException;
public:
	/* TCustomWebDispatcher.Destroy */ inline __fastcall virtual ~TWebModule() { }
	
public:
	/* TDataModule.CreateNew */ inline __fastcall virtual TWebModule(System::Classes::TComponent* AOwner, int Dummy) : TCustomWebDispatcher(AOwner, Dummy) { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDefaultWebAppServices : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	_di_IWebRequestHandler FRequestHandler;
	TWebRequest* FRequest;
	System::Classes::TComponent* FWebModule;
	TWebResponse* FResponse;
	System::Classes::TComponent* __fastcall FindWebDispatcher();
	
protected:
	void __fastcall InitContext(System::Classes::TComponent* WebModule, TWebRequest* Request, TWebResponse* Response);
	void __fastcall FinishContext();
	bool __fastcall HandleRequest();
	System::TObject* __fastcall GetExceptionHandler();
	bool __fastcall GetActive();
	bool __fastcall InvokeDispatcher();
	virtual _di_IWebRequestHandler __fastcall FindRequestHandler();
	_di_IWebRequestHandler __fastcall GetRequestHandler();
	__property TWebRequest* Request = {read=FRequest};
	__property TWebResponse* Response = {read=FResponse};
	__property System::Classes::TComponent* WebModule = {read=FWebModule};
	__property _di_IWebRequestHandler RequestHandler = {read=GetRequestHandler};
public:
	/* TObject.Create */ inline __fastcall TDefaultWebAppServices() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDefaultWebAppServices() { }
	
private:
	void *__IWebAppServices;	// IWebAppServices 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8B627D59-897B-452C-9633-05CC3A634196}
	operator _di_IWebAppServices()
	{
		_di_IWebAppServices intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWebAppServices*(void) { return (IWebAppServices*)&__IWebAppServices; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EWebBrokerException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EWebBrokerException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EWebBrokerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWebBrokerException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWebBrokerException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWebBrokerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWebBrokerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWebBrokerException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWebBrokerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWebBrokerException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWebBrokerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWebBrokerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWebBrokerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWebBrokerException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define sDateFormat L"\"%s\", dd \"%s\" yyyy hh\":\"nn\":\"ss"
static const System::Int8 MAX_STRINGS = System::Int8(0xc);
static const System::Int8 MAX_INTEGERS = System::Int8(0x1);
static const System::Int8 MAX_DATETIMES = System::Int8(0x3);
extern DELPHI_PACKAGE System::UnicodeString __fastcall (*GetModuleFileNameProc)(void);
extern DELPHI_PACKAGE System::Sysutils::TEncoding* GetDefaultCharSetEncoding;
extern DELPHI_PACKAGE System::Sysutils::TEncoding* GetDefaultFieldsCharSetEncoding;
extern DELPHI_PACKAGE System::UnicodeString FWebApplicationFileName;
extern DELPHI_PACKAGE System::UnicodeString __fastcall WebApplicationDirectory(void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall WebApplicationFileName(void);
extern DELPHI_PACKAGE System::Sysutils::TEncoding* __fastcall DefaultCharSetEncoding(void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall DefaultCharSet(void);
extern DELPHI_PACKAGE void __fastcall RegisterContentParser(TContentParserClass AClass);
extern DELPHI_PACKAGE System::Sysutils::TEncoding* __fastcall EncodingFromContentType(const System::UnicodeString AContentType);
#ifndef _WIN64
extern DELPHI_PACKAGE System::UnicodeString __fastcall EncodingGetString(const System::UnicodeString AContentType, const System::DynamicArray<System::Byte> AValue);
extern DELPHI_PACKAGE System::DynamicArray<System::Byte> __fastcall EncodingGetBytes(const System::UnicodeString AContentType, const System::UnicodeString AValue);
#else /* _WIN64 */
extern DELPHI_PACKAGE System::UnicodeString __fastcall EncodingGetString(const System::UnicodeString AContentType, const System::TArray__1<System::Byte> AValue);
extern DELPHI_PACKAGE System::TArray__1<System::Byte> __fastcall EncodingGetBytes(const System::UnicodeString AContentType, const System::UnicodeString AValue);
#endif /* _WIN64 */
extern DELPHI_PACKAGE System::UnicodeString __fastcall HTTPDecode _DEPRECATED_ATTRIBUTE1("Use TNetEncoding.URL.Decode") (const System::UnicodeString AStr);
extern DELPHI_PACKAGE System::UnicodeString __fastcall HTTPEncode _DEPRECATED_ATTRIBUTE1("Use TNetEncoding.URL.Encode") (const System::UnicodeString AStr);
extern DELPHI_PACKAGE System::UnicodeString __fastcall HTMLEncode _DEPRECATED_ATTRIBUTE1("Use TNetEncoding.HTML.Encode") (const System::UnicodeString AStr);
extern DELPHI_PACKAGE System::UnicodeString __fastcall HTMLDecode _DEPRECATED_ATTRIBUTE1("Use TNetEncoding.HTML.Decode") (const System::UnicodeString AStr);
extern DELPHI_PACKAGE System::TDateTime __fastcall ParseDate(const System::UnicodeString DateStr);
extern DELPHI_PACKAGE void __fastcall ExtractHeaderFields(const TExtractCharSet &Separators, const TExtractCharSet &_WhiteSpace, const System::UnicodeString Content, System::Classes::TStrings* Strings, bool Decode, bool StripQuotes = false)/* overload */;
extern DELPHI_PACKAGE void __fastcall ExtractHeaderFields(const TExtractCharSet &Separators, const TExtractCharSet &_WhiteSpace, System::WideChar * Content, System::Classes::TStrings* Strings, bool Decode, bool StripQuotes = false)/* overload */;
extern DELPHI_PACKAGE void __fastcall ExtractHTTPFields(const TExtractCharSet &Separators, const TExtractCharSet &_WhiteSpace, System::WideChar * Content, System::Classes::TStrings* Strings, bool StripQuotes = false)/* overload */;
extern DELPHI_PACKAGE void __fastcall ExtractHTTPFields(const TExtractCharSet &Separators, const TExtractCharSet &_WhiteSpace, const System::UnicodeString Content, System::Classes::TStrings* Strings, bool StripQuotes = false)/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall StatusString(int StatusCode);
extern DELPHI_PACKAGE System::UnicodeString __fastcall UnixPathToDosPath(const System::UnicodeString Path);
extern DELPHI_PACKAGE System::UnicodeString __fastcall DosPathToUnixPath(const System::UnicodeString Path);
extern DELPHI_PACKAGE System::UnicodeString __fastcall MonthStr(System::TDateTime DateTime);
extern DELPHI_PACKAGE System::UnicodeString __fastcall DayOfWeekStr(System::TDateTime DateTime);
}	/* namespace Httpapp */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_HTTPAPP)
using namespace Web::Httpapp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_HttpappHPP
