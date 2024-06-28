// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Response.Adapter.pas' rev: 34.00 (Windows)

#ifndef Rest_Response_AdapterHPP
#define Rest_Response_AdapterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.DateUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Rtti.hpp>
#include <System.JSON.hpp>
#include <System.JSON.Builders.hpp>
#include <Data.DB.hpp>
#include <Data.DBJson.hpp>
#include <Data.Bind.Components.hpp>
#include <REST.Client.hpp>
#include <REST.Types.hpp>
#include <REST.BindSource.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Response
{
namespace Adapter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomJSONDataSetAdapter;
class DELPHICLASS TCustomRESTResponseDataSetAdapter;
class DELPHICLASS TRESTResponseDataSetAdapter;
class DELPHICLASS TRESTResponseJSON;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TOnBeforeOpenDataSetEvent)(System::TObject* Sender);

typedef void __fastcall (__closure *TJSONParserObjectCallback)(System::Json::TJSONObject* const AJSONObject);

class PASCALIMPLEMENTATION TCustomJSONDataSetAdapter : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Data::Dbjson::TJSONToDataSetBridge* FBridge;
	Data::Db::TFieldDefs* FFieldDefs;
	void __fastcall SetFieldDefs(Data::Db::TFieldDefs* AValue);
	Data::Db::TDataSet* __fastcall GetDataSet();
	void __fastcall SetDataSet(Data::Db::TDataSet* const AValue);
	void __fastcall TransferJSONData(System::Json::TJSONValue* const AJSON);
	
private:
	Data::Dbjson::TJSONMetaMergeMode __fastcall GetMetaMergeMode();
	bool __fastcall GetObjectView();
	int __fastcall GetSampleObjects();
	Data::Dbjson::TJSONTypesMode __fastcall GetTypesMode();
	int __fastcall GetStringFieldSize();
	void __fastcall SetMetaMergeMode(const Data::Dbjson::TJSONMetaMergeMode Value);
	void __fastcall SetObjectView(const bool Value);
	void __fastcall SetSampleObjects(const int Value);
	void __fastcall SetTypesMode(const Data::Dbjson::TJSONTypesMode Value);
	void __fastcall SetStringFieldSize(const int Value);
	
protected:
	virtual void __fastcall DoBeforeOpenDataSet();
	virtual Data::Db::TFieldDefsClass __fastcall GetFieldDefsClass();
	virtual System::UnicodeString __fastcall GetDefaultFieldName(System::Json::TJSONValue* const AJSON);
	virtual int __fastcall GetScanDepth();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TCustomJSONDataSetAdapter(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomJSONDataSetAdapter();
	void __fastcall ResetToDefaults();
	void __fastcall UpdateDataSet(System::Json::TJSONValue* const AJSON);
	void __fastcall ClearDataSet();
	__property Data::Db::TDataSet* Dataset = {read=GetDataSet, write=SetDataSet};
	__property Data::Db::TFieldDefs* FieldDefs = {read=FFieldDefs, write=SetFieldDefs};
	__property bool ObjectView = {read=GetObjectView, write=SetObjectView, default=0};
	__property Data::Dbjson::TJSONMetaMergeMode MetaMergeMode = {read=GetMetaMergeMode, write=SetMetaMergeMode, default=1};
	__property int SampleObjects = {read=GetSampleObjects, write=SetSampleObjects, default=1};
	__property Data::Dbjson::TJSONTypesMode TypesMode = {read=GetTypesMode, write=SetTypesMode, default=2};
	__property int StringFieldSize = {read=GetStringFieldSize, write=SetStringFieldSize, default=255};
private:
	void *__TJSONToDataSetBridge_IAdaptor;	// Data::Dbjson::TJSONToDataSetBridge::IAdaptor 
	
public:
	operator Data::Dbjson::TJSONToDataSetBridge::IAdaptor*(void) { return (Data::Dbjson::TJSONToDataSetBridge::IAdaptor*)&__TJSONToDataSetBridge_IAdaptor; }
	
};


class PASCALIMPLEMENTATION TCustomRESTResponseDataSetAdapter : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
private:
	class DELPHICLASS TAdapter;
	class PASCALIMPLEMENTATION TAdapter : public TCustomJSONDataSetAdapter
	{
		typedef TCustomJSONDataSetAdapter inherited;
		
	private:
		TCustomRESTResponseDataSetAdapter* FOwner;
		
	protected:
		virtual void __fastcall DoBeforeOpenDataSet();
		virtual System::UnicodeString __fastcall GetDefaultFieldName(System::Json::TJSONValue* const AJSON);
		virtual int __fastcall GetScanDepth();
	public:
		/* TCustomJSONDataSetAdapter.Create */ inline __fastcall virtual TAdapter(System::Classes::TComponent* AOwner) : TCustomJSONDataSetAdapter(AOwner) { }
		/* TCustomJSONDataSetAdapter.Destroy */ inline __fastcall virtual ~TAdapter() { }
		
	};
	
	
	class DELPHICLASS TNotify;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TNotify : public Rest::Bindsource::TRESTJSONComponentNotify
	{
		typedef Rest::Bindsource::TRESTJSONComponentNotify inherited;
		
	private:
		TCustomRESTResponseDataSetAdapter* FOwner;
		
	protected:
		__fastcall TNotify(TCustomRESTResponseDataSetAdapter* const AOwner);
		
	public:
		virtual void __fastcall JSONValueChanged(System::TObject* ASender);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TNotify() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
public:
	enum class DECLSPEC_DENUM TJSONValueError : unsigned char { NoContent, NoJSON, NoResponseComponent, InvalidRootElement };
	
	typedef void __fastcall (__closure *TJSONValueErrorEvent)(System::TObject* Sender, TJSONValueError AUpdateError, const System::UnicodeString AMessage);
	
	class DELPHICLASS EJSONValueError;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION EJSONValueError : public Rest::Types::ERESTException
	{
		typedef Rest::Types::ERESTException inherited;
		
	private:
		TCustomRESTResponseDataSetAdapter::TJSONValueError FError;
		
	public:
		__fastcall EJSONValueError(TCustomRESTResponseDataSetAdapter::TJSONValueError AError, const System::UnicodeString AMessage);
		__property TCustomRESTResponseDataSetAdapter::TJSONValueError Error = {read=FError, nodefault};
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
	
	
private:
	TOnBeforeOpenDataSetEvent FOnBeforeOpenDataSet;
	TAdapter* FBridge;
	Rest::Client::TCustomRESTResponse* FResponse;
	bool FAutoUpdate;
	TNotify* FNotify;
	Rest::Client::_di_IRESTResponseJSON FResponseJSONIntf;
	int FNestedElementsDepth;
	bool FNestedElements;
	bool FDeferActivate;
	void __fastcall SetResponse(Rest::Client::TCustomRESTResponse* const AValue);
	Data::Db::TDataSet* __fastcall GetDataSet();
	Data::Db::TFieldDefs* __fastcall GetFieldDefs();
	void __fastcall SetDataSet(Data::Db::TDataSet* const Value);
	void __fastcall SetFieldDefs(Data::Db::TFieldDefs* const Value);
	void __fastcall SetActive(const bool Value);
	bool __fastcall GetActive();
	void __fastcall SetAutoUpdate(const bool Value);
	void __fastcall SetResponseJSONIntf(const Rest::Client::_di_IRESTResponseJSON Value);
	void __fastcall ResponseJSONChanged(System::TObject* Sender);
	void __fastcall SetNestedElementsDepth(const int Value);
	void __fastcall InvalidateJSONValue();
	void __fastcall DoJSONValueChanged();
	
private:
	System::UnicodeString FRootElement;
	System::Json::TJSONValue* FJSONValue;
	TJSONValueErrorEvent FOnUpdateError;
	void __fastcall SetNestedElements(const bool Value);
	System::Json::TJSONValue* __fastcall CreateJSONValue();
	System::Json::TJSONValue* __fastcall GetJSONValue();
	Rest::Client::_di_IRESTResponseJSON __fastcall GetResponseComponent();
	System::UnicodeString __fastcall GetRootFieldName();
	int __fastcall GetStringFieldSize();
	void __fastcall SetStringFieldSize(const int Value);
	Data::Dbjson::TJSONMetaMergeMode __fastcall GetMetaMergeMode();
	bool __fastcall GetObjectView();
	int __fastcall GetSampleObjects();
	Data::Dbjson::TJSONTypesMode __fastcall GetTypesMode();
	void __fastcall SetMetaMergeMode(const Data::Dbjson::TJSONMetaMergeMode Value);
	void __fastcall SetObjectView(const bool Value);
	void __fastcall SetSampleObjects(const int Value);
	void __fastcall SetTypesMode(const Data::Dbjson::TJSONTypesMode Value);
	
protected:
	virtual void __fastcall DoBeforeOpenDataSet();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall SetRootElement(const System::UnicodeString AValue);
	virtual void __fastcall Loaded();
	virtual void __fastcall DoUpdateError(TJSONValueError AError, const System::UnicodeString AMessage);
	
public:
	__fastcall virtual TCustomRESTResponseDataSetAdapter(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomRESTResponseDataSetAdapter();
	System::UnicodeString __fastcall GetDefaultFieldName _DEPRECATED_ATTRIBUTE0 (System::Json::TJSONValue* const AJSON);
	__property bool Active = {read=GetActive, write=SetActive, default=0};
	__property bool AutoUpdate = {read=FAutoUpdate, write=SetAutoUpdate, default=1};
	__property Rest::Client::TCustomRESTResponse* Response = {read=FResponse, write=SetResponse};
	__property Rest::Client::_di_IRESTResponseJSON ResponseJSON = {read=FResponseJSONIntf, write=SetResponseJSONIntf};
	void __fastcall ResetToDefaults();
	void __fastcall UpdateDataSet(System::Json::TJSONValue* AJSONValue = (System::Json::TJSONValue*)(0x0));
	void __fastcall ClearDataSet();
	__property Data::Db::TDataSet* Dataset = {read=GetDataSet, write=SetDataSet};
	__property Data::Db::TFieldDefs* FieldDefs = {read=GetFieldDefs, write=SetFieldDefs};
	__property System::UnicodeString RootElement = {read=FRootElement, write=SetRootElement};
	__property bool ObjectView = {read=GetObjectView, write=SetObjectView, default=0};
	__property Data::Dbjson::TJSONMetaMergeMode MetaMergeMode = {read=GetMetaMergeMode, write=SetMetaMergeMode, default=1};
	__property int SampleObjects = {read=GetSampleObjects, write=SetSampleObjects, default=1};
	__property Data::Dbjson::TJSONTypesMode TypesMode = {read=GetTypesMode, write=SetTypesMode, default=2};
	__property int StringFieldSize = {read=GetStringFieldSize, write=SetStringFieldSize, default=255};
	__property bool NestedElements = {read=FNestedElements, write=SetNestedElements, default=0};
	__property int NestedElementsDepth = {read=FNestedElementsDepth, write=SetNestedElementsDepth, default=0};
	__property TOnBeforeOpenDataSetEvent OnBeforeOpenDataSet = {read=FOnBeforeOpenDataSet, write=FOnBeforeOpenDataSet};
	__property TJSONValueErrorEvent OnUpdateError = {read=FOnUpdateError, write=FOnUpdateError};
};


class PASCALIMPLEMENTATION TRESTResponseDataSetAdapter : public TCustomRESTResponseDataSetAdapter
{
	typedef TCustomRESTResponseDataSetAdapter inherited;
	
__published:
	__property Active = {default=0};
	__property AutoUpdate = {default=1};
	__property Dataset;
	__property FieldDefs;
	__property Response;
	__property ResponseJSON;
	__property RootElement = {default=0};
	__property ObjectView = {default=0};
	__property MetaMergeMode = {default=1};
	__property SampleObjects = {default=1};
	__property TypesMode = {default=2};
	__property NestedElementsDepth = {default=0};
	__property NestedElements = {default=0};
	__property StringFieldSize = {default=255};
	__property OnBeforeOpenDataSet;
	__property OnUpdateError;
public:
	/* TCustomRESTResponseDataSetAdapter.Create */ inline __fastcall virtual TRESTResponseDataSetAdapter(System::Classes::TComponent* AOwner) : TCustomRESTResponseDataSetAdapter(AOwner) { }
	/* TCustomRESTResponseDataSetAdapter.Destroy */ inline __fastcall virtual ~TRESTResponseDataSetAdapter() { }
	
};


class PASCALIMPLEMENTATION TRESTResponseJSON : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Json::TJSONValue* FValue;
	System::Generics::Collections::TList__1<System::Classes::TNotifyEvent>* FJSONNotifyList;
	bool FOwnsValue;
	
protected:
	void __fastcall ValueChanged(System::TObject* Sender);
	void __fastcall AddJSONChangedEvent(const System::Classes::TNotifyEvent ANotify);
	void __fastcall RemoveJSONChangedEvent(const System::Classes::TNotifyEvent ANotify);
	void __fastcall GetJSONResponse(/* out */ System::Json::TJSONValue* &AValue, /* out */ bool &AHasOwner);
	bool __fastcall HasJSONResponse();
	bool __fastcall HasResponseContent();
	
public:
	__fastcall virtual TRESTResponseJSON(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall TRESTResponseJSON(System::Classes::TComponent* AOwner, System::Json::TJSONValue* const AValue, bool AOwnsValue)/* overload */;
	__fastcall virtual ~TRESTResponseJSON();
	void __fastcall SetJSONValue(System::Json::TJSONValue* const AValue, bool AOwnsValue);
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


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Adapter */
}	/* namespace Response */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_RESPONSE_ADAPTER)
using namespace Rest::Response::Adapter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_RESPONSE)
using namespace Rest::Response;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_Response_AdapterHPP
