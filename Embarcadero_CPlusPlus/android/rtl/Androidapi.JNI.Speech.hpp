// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Speech.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_SpeechHPP
#define Androidapi_Jni_SpeechHPP

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
#include <Androidapi.JNI.Media.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Speech
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JRecognitionListenerClass;
typedef System::DelphiInterface<JRecognitionListenerClass> _di_JRecognitionListenerClass;
__interface DELPHIINTERFACE JRecognitionListener;
typedef System::DelphiInterface<JRecognitionListener> _di_JRecognitionListener;
class DELPHICLASS TJRecognitionListener;
__interface DELPHIINTERFACE JRecognitionServiceClass;
typedef System::DelphiInterface<JRecognitionServiceClass> _di_JRecognitionServiceClass;
__interface DELPHIINTERFACE JRecognitionService;
typedef System::DelphiInterface<JRecognitionService> _di_JRecognitionService;
class DELPHICLASS TJRecognitionService;
__interface DELPHIINTERFACE JRecognitionService_CallbackClass;
typedef System::DelphiInterface<JRecognitionService_CallbackClass> _di_JRecognitionService_CallbackClass;
__interface DELPHIINTERFACE JRecognitionService_Callback;
typedef System::DelphiInterface<JRecognitionService_Callback> _di_JRecognitionService_Callback;
class DELPHICLASS TJRecognitionService_Callback;
__interface DELPHIINTERFACE JRecognizerIntentClass;
typedef System::DelphiInterface<JRecognizerIntentClass> _di_JRecognizerIntentClass;
__interface DELPHIINTERFACE JRecognizerIntent;
typedef System::DelphiInterface<JRecognizerIntent> _di_JRecognizerIntent;
class DELPHICLASS TJRecognizerIntent;
__interface DELPHIINTERFACE JRecognizerResultsIntentClass;
typedef System::DelphiInterface<JRecognizerResultsIntentClass> _di_JRecognizerResultsIntentClass;
__interface DELPHIINTERFACE JRecognizerResultsIntent;
typedef System::DelphiInterface<JRecognizerResultsIntent> _di_JRecognizerResultsIntent;
class DELPHICLASS TJRecognizerResultsIntent;
__interface DELPHIINTERFACE JSpeechRecognizerClass;
typedef System::DelphiInterface<JSpeechRecognizerClass> _di_JSpeechRecognizerClass;
__interface DELPHIINTERFACE JSpeechRecognizer;
typedef System::DelphiInterface<JSpeechRecognizer> _di_JSpeechRecognizer;
class DELPHICLASS TJSpeechRecognizer;
__interface DELPHIINTERFACE JSynthesisCallbackClass;
typedef System::DelphiInterface<JSynthesisCallbackClass> _di_JSynthesisCallbackClass;
__interface DELPHIINTERFACE JSynthesisCallback;
typedef System::DelphiInterface<JSynthesisCallback> _di_JSynthesisCallback;
class DELPHICLASS TJSynthesisCallback;
__interface DELPHIINTERFACE JSynthesisRequestClass;
typedef System::DelphiInterface<JSynthesisRequestClass> _di_JSynthesisRequestClass;
__interface DELPHIINTERFACE JSynthesisRequest;
typedef System::DelphiInterface<JSynthesisRequest> _di_JSynthesisRequest;
class DELPHICLASS TJSynthesisRequest;
__interface DELPHIINTERFACE JTextToSpeechClass;
typedef System::DelphiInterface<JTextToSpeechClass> _di_JTextToSpeechClass;
__interface DELPHIINTERFACE JTextToSpeech;
typedef System::DelphiInterface<JTextToSpeech> _di_JTextToSpeech;
class DELPHICLASS TJTextToSpeech;
__interface DELPHIINTERFACE JTextToSpeech_EngineClass;
typedef System::DelphiInterface<JTextToSpeech_EngineClass> _di_JTextToSpeech_EngineClass;
__interface DELPHIINTERFACE JTextToSpeech_Engine;
typedef System::DelphiInterface<JTextToSpeech_Engine> _di_JTextToSpeech_Engine;
class DELPHICLASS TJTextToSpeech_Engine;
__interface DELPHIINTERFACE JTextToSpeech_EngineInfoClass;
typedef System::DelphiInterface<JTextToSpeech_EngineInfoClass> _di_JTextToSpeech_EngineInfoClass;
__interface DELPHIINTERFACE JTextToSpeech_EngineInfo;
typedef System::DelphiInterface<JTextToSpeech_EngineInfo> _di_JTextToSpeech_EngineInfo;
class DELPHICLASS TJTextToSpeech_EngineInfo;
__interface DELPHIINTERFACE JTextToSpeech_OnInitListenerClass;
typedef System::DelphiInterface<JTextToSpeech_OnInitListenerClass> _di_JTextToSpeech_OnInitListenerClass;
__interface DELPHIINTERFACE JTextToSpeech_OnInitListener;
typedef System::DelphiInterface<JTextToSpeech_OnInitListener> _di_JTextToSpeech_OnInitListener;
class DELPHICLASS TJTextToSpeech_OnInitListener;
__interface DELPHIINTERFACE JTextToSpeech_OnUtteranceCompletedListenerClass;
typedef System::DelphiInterface<JTextToSpeech_OnUtteranceCompletedListenerClass> _di_JTextToSpeech_OnUtteranceCompletedListenerClass;
__interface DELPHIINTERFACE JTextToSpeech_OnUtteranceCompletedListener;
typedef System::DelphiInterface<JTextToSpeech_OnUtteranceCompletedListener> _di_JTextToSpeech_OnUtteranceCompletedListener;
class DELPHICLASS TJTextToSpeech_OnUtteranceCompletedListener;
__interface DELPHIINTERFACE JTextToSpeechServiceClass;
typedef System::DelphiInterface<JTextToSpeechServiceClass> _di_JTextToSpeechServiceClass;
__interface DELPHIINTERFACE JTextToSpeechService;
typedef System::DelphiInterface<JTextToSpeechService> _di_JTextToSpeechService;
class DELPHICLASS TJTextToSpeechService;
__interface DELPHIINTERFACE JUtteranceProgressListenerClass;
typedef System::DelphiInterface<JUtteranceProgressListenerClass> _di_JUtteranceProgressListenerClass;
__interface DELPHIINTERFACE JUtteranceProgressListener;
typedef System::DelphiInterface<JUtteranceProgressListener> _di_JUtteranceProgressListener;
class DELPHICLASS TJUtteranceProgressListener;
__interface DELPHIINTERFACE JVoiceClass;
typedef System::DelphiInterface<JVoiceClass> _di_JVoiceClass;
__interface DELPHIINTERFACE JVoice;
typedef System::DelphiInterface<JVoice> _di_JVoice;
class DELPHICLASS TJVoice;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{57171073-E9C7-49D8-AE11-323FA3855BD3}") JRecognitionListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{24846D38-C77E-4971-B8AC-65D1860CEB44}") JRecognitionListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onBeginningOfSpeech() = 0 ;
	virtual void __cdecl onBufferReceived(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* buffer) = 0 ;
	virtual void __cdecl onEndOfSpeech() = 0 ;
	virtual void __cdecl onError(int error) = 0 ;
	virtual void __cdecl onEvent(int eventType, Androidapi::Jni::Os::_di_JBundle params) = 0 ;
	virtual void __cdecl onPartialResults(Androidapi::Jni::Os::_di_JBundle partialResults) = 0 ;
	virtual void __cdecl onReadyForSpeech(Androidapi::Jni::Os::_di_JBundle params) = 0 ;
	virtual void __cdecl onResults(Androidapi::Jni::Os::_di_JBundle results) = 0 ;
	virtual void __cdecl onRmsChanged(float rmsdB) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRecognitionListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognitionListenerClass,_di_JRecognitionListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognitionListenerClass,_di_JRecognitionListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRecognitionListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognitionListenerClass,_di_JRecognitionListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRecognitionListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{38BB1897-9457-4C99-B64E-6B4CFDDC1CE2}") JRecognitionServiceClass  : public Androidapi::Jni::App::JServiceClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSERVICE_INTERFACE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSERVICE_META_DATA() = 0 ;
	HIDESBASE virtual _di_JRecognitionService __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString SERVICE_INTERFACE = {read=_GetSERVICE_INTERFACE};
	__property Androidapi::Jni::Javatypes::_di_JString SERVICE_META_DATA = {read=_GetSERVICE_META_DATA};
};

__interface  INTERFACE_UUID("{5A5D7D5D-CD74-4498-96B5-496207272EB2}") JRecognitionService  : public Androidapi::Jni::App::JService 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRecognitionService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognitionServiceClass,_di_JRecognitionService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognitionServiceClass,_di_JRecognitionService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRecognitionService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognitionServiceClass,_di_JRecognitionService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRecognitionService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{925781D8-028E-474D-BA6B-77929050BF14}") JRecognitionService_CallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{80A61346-2FB7-4936-8A93-C5A64B38C75C}") JRecognitionService_Callback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl beginningOfSpeech() = 0 ;
	virtual void __cdecl bufferReceived(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* buffer) = 0 ;
	virtual void __cdecl endOfSpeech() = 0 ;
	virtual void __cdecl error(int error) = 0 ;
	virtual int __cdecl getCallingUid() = 0 ;
	virtual void __cdecl partialResults(Androidapi::Jni::Os::_di_JBundle partialResults) = 0 ;
	virtual void __cdecl readyForSpeech(Androidapi::Jni::Os::_di_JBundle params) = 0 ;
	virtual void __cdecl results(Androidapi::Jni::Os::_di_JBundle results) = 0 ;
	virtual void __cdecl rmsChanged(float rmsdB) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRecognitionService_Callback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognitionService_CallbackClass,_di_JRecognitionService_Callback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognitionService_CallbackClass,_di_JRecognitionService_Callback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRecognitionService_Callback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognitionService_CallbackClass,_di_JRecognitionService_Callback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRecognitionService_Callback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A60D33ED-3B87-49A2-8EF9-B0E861A95205}") JRecognizerIntentClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_GET_LANGUAGE_DETAILS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_RECOGNIZE_SPEECH() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_VOICE_SEARCH_HANDS_FREE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_WEB_SEARCH() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDETAILS_META_DATA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CALLING_PACKAGE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CONFIDENCE_SCORES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_LANGUAGE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_LANGUAGE_MODEL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_LANGUAGE_PREFERENCE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_MAX_RESULTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_ONLY_RETURN_LANGUAGE_PREFERENCE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_ORIGIN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PARTIAL_RESULTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PREFER_OFFLINE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PROMPT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_RESULTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_RESULTS_PENDINGINTENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_RESULTS_PENDINGINTENT_BUNDLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SECURE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SPEECH_INPUT_COMPLETE_SILENCE_LENGTH_MILLIS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SPEECH_INPUT_MINIMUM_LENGTH_MILLIS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SPEECH_INPUT_POSSIBLY_COMPLETE_SILENCE_LENGTH_MILLIS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SUPPORTED_LANGUAGES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_WEB_SEARCH_ONLY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetLANGUAGE_MODEL_FREE_FORM() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetLANGUAGE_MODEL_WEB_SEARCH() = 0 ;
	virtual int __cdecl _GetRESULT_AUDIO_ERROR() = 0 ;
	virtual int __cdecl _GetRESULT_CLIENT_ERROR() = 0 ;
	virtual int __cdecl _GetRESULT_NETWORK_ERROR() = 0 ;
	virtual int __cdecl _GetRESULT_NO_MATCH() = 0 ;
	virtual int __cdecl _GetRESULT_SERVER_ERROR() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIntent __cdecl getVoiceDetailsIntent(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_GET_LANGUAGE_DETAILS = {read=_GetACTION_GET_LANGUAGE_DETAILS};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_RECOGNIZE_SPEECH = {read=_GetACTION_RECOGNIZE_SPEECH};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_VOICE_SEARCH_HANDS_FREE = {read=_GetACTION_VOICE_SEARCH_HANDS_FREE};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_WEB_SEARCH = {read=_GetACTION_WEB_SEARCH};
	__property Androidapi::Jni::Javatypes::_di_JString DETAILS_META_DATA = {read=_GetDETAILS_META_DATA};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CALLING_PACKAGE = {read=_GetEXTRA_CALLING_PACKAGE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CONFIDENCE_SCORES = {read=_GetEXTRA_CONFIDENCE_SCORES};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_LANGUAGE = {read=_GetEXTRA_LANGUAGE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_LANGUAGE_MODEL = {read=_GetEXTRA_LANGUAGE_MODEL};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_LANGUAGE_PREFERENCE = {read=_GetEXTRA_LANGUAGE_PREFERENCE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_MAX_RESULTS = {read=_GetEXTRA_MAX_RESULTS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_ONLY_RETURN_LANGUAGE_PREFERENCE = {read=_GetEXTRA_ONLY_RETURN_LANGUAGE_PREFERENCE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_ORIGIN = {read=_GetEXTRA_ORIGIN};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PARTIAL_RESULTS = {read=_GetEXTRA_PARTIAL_RESULTS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PREFER_OFFLINE = {read=_GetEXTRA_PREFER_OFFLINE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PROMPT = {read=_GetEXTRA_PROMPT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_RESULTS = {read=_GetEXTRA_RESULTS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_RESULTS_PENDINGINTENT = {read=_GetEXTRA_RESULTS_PENDINGINTENT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_RESULTS_PENDINGINTENT_BUNDLE = {read=_GetEXTRA_RESULTS_PENDINGINTENT_BUNDLE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SECURE = {read=_GetEXTRA_SECURE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SPEECH_INPUT_COMPLETE_SILENCE_LENGTH_MILLIS = {read=_GetEXTRA_SPEECH_INPUT_COMPLETE_SILENCE_LENGTH_MILLIS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SPEECH_INPUT_MINIMUM_LENGTH_MILLIS = {read=_GetEXTRA_SPEECH_INPUT_MINIMUM_LENGTH_MILLIS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SPEECH_INPUT_POSSIBLY_COMPLETE_SILENCE_LENGTH_MILLIS = {read=_GetEXTRA_SPEECH_INPUT_POSSIBLY_COMPLETE_SILENCE_LENGTH_MILLIS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SUPPORTED_LANGUAGES = {read=_GetEXTRA_SUPPORTED_LANGUAGES};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_WEB_SEARCH_ONLY = {read=_GetEXTRA_WEB_SEARCH_ONLY};
	__property Androidapi::Jni::Javatypes::_di_JString LANGUAGE_MODEL_FREE_FORM = {read=_GetLANGUAGE_MODEL_FREE_FORM};
	__property Androidapi::Jni::Javatypes::_di_JString LANGUAGE_MODEL_WEB_SEARCH = {read=_GetLANGUAGE_MODEL_WEB_SEARCH};
	__property int RESULT_AUDIO_ERROR = {read=_GetRESULT_AUDIO_ERROR};
	__property int RESULT_CLIENT_ERROR = {read=_GetRESULT_CLIENT_ERROR};
	__property int RESULT_NETWORK_ERROR = {read=_GetRESULT_NETWORK_ERROR};
	__property int RESULT_NO_MATCH = {read=_GetRESULT_NO_MATCH};
	__property int RESULT_SERVER_ERROR = {read=_GetRESULT_SERVER_ERROR};
};

__interface  INTERFACE_UUID("{0432BC72-3F99-4EF0-9F02-B5E55BD974CE}") JRecognizerIntent  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRecognizerIntent : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognizerIntentClass,_di_JRecognizerIntent>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognizerIntentClass,_di_JRecognizerIntent> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRecognizerIntent() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognizerIntentClass,_di_JRecognizerIntent>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRecognizerIntent() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5F9C0F34-CE2D-4B4A-B432-49CF198F5AF2}") JRecognizerResultsIntentClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_VOICE_SEARCH_RESULTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VOICE_SEARCH_RESULT_HTML() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VOICE_SEARCH_RESULT_HTML_BASE_URLS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VOICE_SEARCH_RESULT_HTTP_HEADERS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VOICE_SEARCH_RESULT_STRINGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VOICE_SEARCH_RESULT_URLS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetURI_SCHEME_INLINE() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_VOICE_SEARCH_RESULTS = {read=_GetACTION_VOICE_SEARCH_RESULTS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VOICE_SEARCH_RESULT_HTML = {read=_GetEXTRA_VOICE_SEARCH_RESULT_HTML};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VOICE_SEARCH_RESULT_HTML_BASE_URLS = {read=_GetEXTRA_VOICE_SEARCH_RESULT_HTML_BASE_URLS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VOICE_SEARCH_RESULT_HTTP_HEADERS = {read=_GetEXTRA_VOICE_SEARCH_RESULT_HTTP_HEADERS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VOICE_SEARCH_RESULT_STRINGS = {read=_GetEXTRA_VOICE_SEARCH_RESULT_STRINGS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VOICE_SEARCH_RESULT_URLS = {read=_GetEXTRA_VOICE_SEARCH_RESULT_URLS};
	__property Androidapi::Jni::Javatypes::_di_JString URI_SCHEME_INLINE = {read=_GetURI_SCHEME_INLINE};
};

__interface  INTERFACE_UUID("{ECEE440F-2767-455A-A868-81A4F4A72F24}") JRecognizerResultsIntent  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRecognizerResultsIntent : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognizerResultsIntentClass,_di_JRecognizerResultsIntent>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognizerResultsIntentClass,_di_JRecognizerResultsIntent> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRecognizerResultsIntent() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRecognizerResultsIntentClass,_di_JRecognizerResultsIntent>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRecognizerResultsIntent() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{256567F6-C4BF-4744-B1C9-F81311A1F18D}") JSpeechRecognizerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCONFIDENCE_SCORES() = 0 ;
	virtual int __cdecl _GetERROR_AUDIO() = 0 ;
	virtual int __cdecl _GetERROR_CLIENT() = 0 ;
	virtual int __cdecl _GetERROR_INSUFFICIENT_PERMISSIONS() = 0 ;
	virtual int __cdecl _GetERROR_NETWORK() = 0 ;
	virtual int __cdecl _GetERROR_NETWORK_TIMEOUT() = 0 ;
	virtual int __cdecl _GetERROR_NO_MATCH() = 0 ;
	virtual int __cdecl _GetERROR_RECOGNIZER_BUSY() = 0 ;
	virtual int __cdecl _GetERROR_SERVER() = 0 ;
	virtual int __cdecl _GetERROR_SPEECH_TIMEOUT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRESULTS_RECOGNITION() = 0 ;
	virtual _di_JSpeechRecognizer __cdecl createSpeechRecognizer(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	virtual _di_JSpeechRecognizer __cdecl createSpeechRecognizer(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JComponentName serviceComponent) = 0 /* overload */;
	virtual bool __cdecl isRecognitionAvailable(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString CONFIDENCE_SCORES = {read=_GetCONFIDENCE_SCORES};
	__property int ERROR_AUDIO = {read=_GetERROR_AUDIO};
	__property int ERROR_CLIENT = {read=_GetERROR_CLIENT};
	__property int ERROR_INSUFFICIENT_PERMISSIONS = {read=_GetERROR_INSUFFICIENT_PERMISSIONS};
	__property int ERROR_NETWORK = {read=_GetERROR_NETWORK};
	__property int ERROR_NETWORK_TIMEOUT = {read=_GetERROR_NETWORK_TIMEOUT};
	__property int ERROR_NO_MATCH = {read=_GetERROR_NO_MATCH};
	__property int ERROR_RECOGNIZER_BUSY = {read=_GetERROR_RECOGNIZER_BUSY};
	__property int ERROR_SERVER = {read=_GetERROR_SERVER};
	__property int ERROR_SPEECH_TIMEOUT = {read=_GetERROR_SPEECH_TIMEOUT};
	__property Androidapi::Jni::Javatypes::_di_JString RESULTS_RECOGNITION = {read=_GetRESULTS_RECOGNITION};
};

__interface  INTERFACE_UUID("{A67520B9-5BB4-481E-9310-3A673D724235}") JSpeechRecognizer  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual void __cdecl destroy() = 0 ;
	virtual void __cdecl setRecognitionListener(_di_JRecognitionListener listener) = 0 ;
	virtual void __cdecl startListening(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent recognizerIntent) = 0 ;
	virtual void __cdecl stopListening() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSpeechRecognizer : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSpeechRecognizerClass,_di_JSpeechRecognizer>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSpeechRecognizerClass,_di_JSpeechRecognizer> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSpeechRecognizer() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSpeechRecognizerClass,_di_JSpeechRecognizer>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSpeechRecognizer() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{241AE5F6-F249-4B95-8D2D-1C5B068C57D2}") JSynthesisCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{22155271-C2C9-4212-B0C6-01BE152D4F43}") JSynthesisCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual int __cdecl audioAvailable(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* buffer, int offset, int length) = 0 ;
	virtual int __cdecl done() = 0 ;
	virtual void __cdecl error() = 0 /* overload */;
	virtual void __cdecl error(int errorCode) = 0 /* overload */;
	virtual int __cdecl getMaxBufferSize() = 0 ;
	virtual bool __cdecl hasFinished() = 0 ;
	virtual bool __cdecl hasStarted() = 0 ;
	virtual void __cdecl rangeStart(int markerInFrames, int start, int end_) = 0 ;
	virtual int __cdecl start(int sampleRateInHz, int audioFormat, int channelCount) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSynthesisCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSynthesisCallbackClass,_di_JSynthesisCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSynthesisCallbackClass,_di_JSynthesisCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSynthesisCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSynthesisCallbackClass,_di_JSynthesisCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSynthesisCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6E0AE57B-6C0D-4C9D-AFE0-91676BA059C9}") JSynthesisRequestClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSynthesisRequest __cdecl init(Androidapi::Jni::Javatypes::_di_JString text, Androidapi::Jni::Os::_di_JBundle params) = 0 /* overload */;
	HIDESBASE virtual _di_JSynthesisRequest __cdecl init(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Os::_di_JBundle params) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{1E8FE9BA-9A87-40D7-9198-89C56CE2039C}") JSynthesisRequest  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl getCallerUid() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getCharSequenceText() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCountry() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getLanguage() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getParams() = 0 ;
	virtual int __cdecl getPitch() = 0 ;
	virtual int __cdecl getSpeechRate() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getText() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getVariant() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getVoiceName() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSynthesisRequest : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSynthesisRequestClass,_di_JSynthesisRequest>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSynthesisRequestClass,_di_JSynthesisRequest> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSynthesisRequest() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSynthesisRequestClass,_di_JSynthesisRequest>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSynthesisRequest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BE260883-0916-456E-B84C-6B237C8382DA}") JTextToSpeechClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_TTS_QUEUE_PROCESSING_COMPLETED() = 0 ;
	virtual int __cdecl _GetERROR() = 0 ;
	virtual int __cdecl _GetERROR_INVALID_REQUEST() = 0 ;
	virtual int __cdecl _GetERROR_NETWORK() = 0 ;
	virtual int __cdecl _GetERROR_NETWORK_TIMEOUT() = 0 ;
	virtual int __cdecl _GetERROR_NOT_INSTALLED_YET() = 0 ;
	virtual int __cdecl _GetERROR_OUTPUT() = 0 ;
	virtual int __cdecl _GetERROR_SERVICE() = 0 ;
	virtual int __cdecl _GetERROR_SYNTHESIS() = 0 ;
	virtual int __cdecl _GetLANG_AVAILABLE() = 0 ;
	virtual int __cdecl _GetLANG_COUNTRY_AVAILABLE() = 0 ;
	virtual int __cdecl _GetLANG_COUNTRY_VAR_AVAILABLE() = 0 ;
	virtual int __cdecl _GetLANG_MISSING_DATA() = 0 ;
	virtual int __cdecl _GetLANG_NOT_SUPPORTED() = 0 ;
	virtual int __cdecl _GetQUEUE_ADD() = 0 ;
	virtual int __cdecl _GetQUEUE_FLUSH() = 0 ;
	virtual int __cdecl _GetSTOPPED() = 0 ;
	virtual int __cdecl _GetSUCCESS() = 0 ;
	HIDESBASE virtual _di_JTextToSpeech __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, _di_JTextToSpeech_OnInitListener listener) = 0 /* overload */;
	HIDESBASE virtual _di_JTextToSpeech __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, _di_JTextToSpeech_OnInitListener listener, Androidapi::Jni::Javatypes::_di_JString engine) = 0 /* overload */;
	virtual int __cdecl getMaxSpeechInputLength() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_TTS_QUEUE_PROCESSING_COMPLETED = {read=_GetACTION_TTS_QUEUE_PROCESSING_COMPLETED};
	__property int ERROR = {read=_GetERROR};
	__property int ERROR_INVALID_REQUEST = {read=_GetERROR_INVALID_REQUEST};
	__property int ERROR_NETWORK = {read=_GetERROR_NETWORK};
	__property int ERROR_NETWORK_TIMEOUT = {read=_GetERROR_NETWORK_TIMEOUT};
	__property int ERROR_NOT_INSTALLED_YET = {read=_GetERROR_NOT_INSTALLED_YET};
	__property int ERROR_OUTPUT = {read=_GetERROR_OUTPUT};
	__property int ERROR_SERVICE = {read=_GetERROR_SERVICE};
	__property int ERROR_SYNTHESIS = {read=_GetERROR_SYNTHESIS};
	__property int LANG_AVAILABLE = {read=_GetLANG_AVAILABLE};
	__property int LANG_COUNTRY_AVAILABLE = {read=_GetLANG_COUNTRY_AVAILABLE};
	__property int LANG_COUNTRY_VAR_AVAILABLE = {read=_GetLANG_COUNTRY_VAR_AVAILABLE};
	__property int LANG_MISSING_DATA = {read=_GetLANG_MISSING_DATA};
	__property int LANG_NOT_SUPPORTED = {read=_GetLANG_NOT_SUPPORTED};
	__property int QUEUE_ADD = {read=_GetQUEUE_ADD};
	__property int QUEUE_FLUSH = {read=_GetQUEUE_FLUSH};
	__property int STOPPED = {read=_GetSTOPPED};
	__property int SUCCESS = {read=_GetSUCCESS};
};

__interface  INTERFACE_UUID("{38B05C3C-B672-4FEC-849B-0CF4D89AA507}") JTextToSpeech  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl addEarcon(Androidapi::Jni::Javatypes::_di_JString earcon, Androidapi::Jni::Javatypes::_di_JString packagename, int resourceId) = 0 /* overload */;
	virtual int __cdecl addEarcon(Androidapi::Jni::Javatypes::_di_JString earcon, Androidapi::Jni::Javatypes::_di_JString filename) = 0 /* overload */;
	virtual int __cdecl addEarcon(Androidapi::Jni::Javatypes::_di_JString earcon, Androidapi::Jni::Javatypes::_di_JFile file_) = 0 /* overload */;
	virtual int __cdecl addSpeech(Androidapi::Jni::Javatypes::_di_JString text, Androidapi::Jni::Javatypes::_di_JString packagename, int resourceId) = 0 /* overload */;
	virtual int __cdecl addSpeech(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Javatypes::_di_JString packagename, int resourceId) = 0 /* overload */;
	virtual int __cdecl addSpeech(Androidapi::Jni::Javatypes::_di_JString text, Androidapi::Jni::Javatypes::_di_JString filename) = 0 /* overload */;
	virtual int __cdecl addSpeech(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Javatypes::_di_JFile file_) = 0 /* overload */;
	virtual bool __cdecl areDefaultsEnforced() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSet __cdecl getAvailableLanguages() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDefaultEngine() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JLocale __cdecl getDefaultLanguage() = 0 ;
	virtual _di_JVoice __cdecl getDefaultVoice() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getEngines() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSet __cdecl getFeatures(Androidapi::Jni::Javatypes::_di_JLocale locale) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JLocale __cdecl getLanguage() = 0 ;
	virtual _di_JVoice __cdecl getVoice() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSet __cdecl getVoices() = 0 ;
	virtual int __cdecl isLanguageAvailable(Androidapi::Jni::Javatypes::_di_JLocale loc) = 0 ;
	virtual bool __cdecl isSpeaking() = 0 ;
	virtual int __cdecl playEarcon(Androidapi::Jni::Javatypes::_di_JString earcon, int queueMode, Androidapi::Jni::Os::_di_JBundle params, Androidapi::Jni::Javatypes::_di_JString utteranceId) = 0 /* overload */;
	virtual int __cdecl playEarcon(Androidapi::Jni::Javatypes::_di_JString earcon, int queueMode, Androidapi::Jni::Javatypes::_di_JHashMap params) = 0 /* overload */;
	virtual int __cdecl playSilence(__int64 durationInMs, int queueMode, Androidapi::Jni::Javatypes::_di_JHashMap params) = 0 ;
	virtual int __cdecl playSilentUtterance(__int64 durationInMs, int queueMode, Androidapi::Jni::Javatypes::_di_JString utteranceId) = 0 ;
	virtual int __cdecl setAudioAttributes(Androidapi::Jni::Media::_di_JAudioAttributes audioAttributes) = 0 ;
	virtual int __cdecl setEngineByPackageName(Androidapi::Jni::Javatypes::_di_JString enginePackageName) = 0 ;
	virtual int __cdecl setLanguage(Androidapi::Jni::Javatypes::_di_JLocale loc) = 0 ;
	virtual int __cdecl setOnUtteranceCompletedListener(_di_JTextToSpeech_OnUtteranceCompletedListener listener) = 0 ;
	virtual int __cdecl setOnUtteranceProgressListener(_di_JUtteranceProgressListener listener) = 0 ;
	virtual int __cdecl setPitch(float pitch) = 0 ;
	virtual int __cdecl setSpeechRate(float speechRate) = 0 ;
	virtual int __cdecl setVoice(_di_JVoice voice) = 0 ;
	virtual void __cdecl shutdown() = 0 ;
	virtual int __cdecl speak(Androidapi::Jni::Javatypes::_di_JCharSequence text, int queueMode, Androidapi::Jni::Os::_di_JBundle params, Androidapi::Jni::Javatypes::_di_JString utteranceId) = 0 /* overload */;
	virtual int __cdecl speak(Androidapi::Jni::Javatypes::_di_JString text, int queueMode, Androidapi::Jni::Javatypes::_di_JHashMap params) = 0 /* overload */;
	virtual int __cdecl stop() = 0 ;
	virtual int __cdecl synthesizeToFile(Androidapi::Jni::Javatypes::_di_JCharSequence text, Androidapi::Jni::Os::_di_JBundle params, Androidapi::Jni::Javatypes::_di_JFile file_, Androidapi::Jni::Javatypes::_di_JString utteranceId) = 0 /* overload */;
	virtual int __cdecl synthesizeToFile(Androidapi::Jni::Javatypes::_di_JString text, Androidapi::Jni::Javatypes::_di_JHashMap params, Androidapi::Jni::Javatypes::_di_JString filename) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTextToSpeech : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeechClass,_di_JTextToSpeech>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeechClass,_di_JTextToSpeech> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTextToSpeech() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeechClass,_di_JTextToSpeech>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTextToSpeech() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{75457E65-C0B1-4AF3-A166-A553887479C5}") JTextToSpeech_EngineClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_CHECK_TTS_DATA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_GET_SAMPLE_TEXT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_INSTALL_TTS_DATA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_TTS_DATA_INSTALLED() = 0 ;
	virtual int __cdecl _GetCHECK_VOICE_DATA_BAD_DATA() = 0 ;
	virtual int __cdecl _GetCHECK_VOICE_DATA_FAIL() = 0 ;
	virtual int __cdecl _GetCHECK_VOICE_DATA_MISSING_DATA() = 0 ;
	virtual int __cdecl _GetCHECK_VOICE_DATA_MISSING_VOLUME() = 0 ;
	virtual int __cdecl _GetCHECK_VOICE_DATA_PASS() = 0 ;
	virtual int __cdecl _GetDEFAULT_STREAM() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_AVAILABLE_VOICES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CHECK_VOICE_DATA_FOR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SAMPLE_TEXT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_TTS_DATA_INSTALLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_UNAVAILABLE_VOICES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VOICE_DATA_FILES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VOICE_DATA_FILES_INFO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VOICE_DATA_ROOT_DIRECTORY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetINTENT_ACTION_TTS_SERVICE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_FEATURE_EMBEDDED_SYNTHESIS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_FEATURE_NETWORK_RETRIES_COUNT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_FEATURE_NETWORK_SYNTHESIS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_FEATURE_NETWORK_TIMEOUT_MS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_FEATURE_NOT_INSTALLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_PARAM_PAN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_PARAM_SESSION_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_PARAM_STREAM() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_PARAM_UTTERANCE_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_PARAM_VOLUME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSERVICE_META_DATA() = 0 ;
	HIDESBASE virtual _di_JTextToSpeech_Engine __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_CHECK_TTS_DATA = {read=_GetACTION_CHECK_TTS_DATA};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_GET_SAMPLE_TEXT = {read=_GetACTION_GET_SAMPLE_TEXT};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_INSTALL_TTS_DATA = {read=_GetACTION_INSTALL_TTS_DATA};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_TTS_DATA_INSTALLED = {read=_GetACTION_TTS_DATA_INSTALLED};
	__property int CHECK_VOICE_DATA_BAD_DATA = {read=_GetCHECK_VOICE_DATA_BAD_DATA};
	__property int CHECK_VOICE_DATA_FAIL = {read=_GetCHECK_VOICE_DATA_FAIL};
	__property int CHECK_VOICE_DATA_MISSING_DATA = {read=_GetCHECK_VOICE_DATA_MISSING_DATA};
	__property int CHECK_VOICE_DATA_MISSING_VOLUME = {read=_GetCHECK_VOICE_DATA_MISSING_VOLUME};
	__property int CHECK_VOICE_DATA_PASS = {read=_GetCHECK_VOICE_DATA_PASS};
	__property int DEFAULT_STREAM = {read=_GetDEFAULT_STREAM};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_AVAILABLE_VOICES = {read=_GetEXTRA_AVAILABLE_VOICES};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CHECK_VOICE_DATA_FOR = {read=_GetEXTRA_CHECK_VOICE_DATA_FOR};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SAMPLE_TEXT = {read=_GetEXTRA_SAMPLE_TEXT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_TTS_DATA_INSTALLED = {read=_GetEXTRA_TTS_DATA_INSTALLED};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_UNAVAILABLE_VOICES = {read=_GetEXTRA_UNAVAILABLE_VOICES};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VOICE_DATA_FILES = {read=_GetEXTRA_VOICE_DATA_FILES};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VOICE_DATA_FILES_INFO = {read=_GetEXTRA_VOICE_DATA_FILES_INFO};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VOICE_DATA_ROOT_DIRECTORY = {read=_GetEXTRA_VOICE_DATA_ROOT_DIRECTORY};
	__property Androidapi::Jni::Javatypes::_di_JString INTENT_ACTION_TTS_SERVICE = {read=_GetINTENT_ACTION_TTS_SERVICE};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_FEATURE_EMBEDDED_SYNTHESIS = {read=_GetKEY_FEATURE_EMBEDDED_SYNTHESIS};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_FEATURE_NETWORK_RETRIES_COUNT = {read=_GetKEY_FEATURE_NETWORK_RETRIES_COUNT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_FEATURE_NETWORK_SYNTHESIS = {read=_GetKEY_FEATURE_NETWORK_SYNTHESIS};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_FEATURE_NETWORK_TIMEOUT_MS = {read=_GetKEY_FEATURE_NETWORK_TIMEOUT_MS};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_FEATURE_NOT_INSTALLED = {read=_GetKEY_FEATURE_NOT_INSTALLED};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_PARAM_PAN = {read=_GetKEY_PARAM_PAN};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_PARAM_SESSION_ID = {read=_GetKEY_PARAM_SESSION_ID};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_PARAM_STREAM = {read=_GetKEY_PARAM_STREAM};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_PARAM_UTTERANCE_ID = {read=_GetKEY_PARAM_UTTERANCE_ID};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_PARAM_VOLUME = {read=_GetKEY_PARAM_VOLUME};
	__property Androidapi::Jni::Javatypes::_di_JString SERVICE_META_DATA = {read=_GetSERVICE_META_DATA};
};

__interface  INTERFACE_UUID("{A876F830-EEA2-4A8E-B40D-B7AA567205EE}") JTextToSpeech_Engine  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTextToSpeech_Engine : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_EngineClass,_di_JTextToSpeech_Engine>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_EngineClass,_di_JTextToSpeech_Engine> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTextToSpeech_Engine() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_EngineClass,_di_JTextToSpeech_Engine>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTextToSpeech_Engine() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ECA80D2D-D36F-43E4-9820-90A8F2122E29}") JTextToSpeech_EngineInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JTextToSpeech_EngineInfo __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{931C3765-0057-4A59-93EC-93CBEE991ADD}") JTextToSpeech_EngineInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _Geticon() = 0 ;
	virtual void __cdecl _Seticon(int Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getlabel() = 0 ;
	virtual void __cdecl _Setlabel(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getname() = 0 ;
	virtual void __cdecl _Setname(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	__property int icon = {read=_Geticon, write=_Seticon};
	__property Androidapi::Jni::Javatypes::_di_JString label = {read=_Getlabel, write=_Setlabel};
	__property Androidapi::Jni::Javatypes::_di_JString name = {read=_Getname, write=_Setname};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTextToSpeech_EngineInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_EngineInfoClass,_di_JTextToSpeech_EngineInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_EngineInfoClass,_di_JTextToSpeech_EngineInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTextToSpeech_EngineInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_EngineInfoClass,_di_JTextToSpeech_EngineInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTextToSpeech_EngineInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B01450B5-524A-4B99-95DC-9158B7B8CC15}") JTextToSpeech_OnInitListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{94CC537C-E958-4EA5-B613-1465AEF6014B}") JTextToSpeech_OnInitListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onInit(int status) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTextToSpeech_OnInitListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_OnInitListenerClass,_di_JTextToSpeech_OnInitListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_OnInitListenerClass,_di_JTextToSpeech_OnInitListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTextToSpeech_OnInitListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_OnInitListenerClass,_di_JTextToSpeech_OnInitListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTextToSpeech_OnInitListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{83D093B7-6FB6-46FE-A08E-1B0D25BDA841}") JTextToSpeech_OnUtteranceCompletedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{3EA0D21E-74E4-4204-A18F-2F68FE126E18}") JTextToSpeech_OnUtteranceCompletedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onUtteranceCompleted(Androidapi::Jni::Javatypes::_di_JString utteranceId) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTextToSpeech_OnUtteranceCompletedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_OnUtteranceCompletedListenerClass,_di_JTextToSpeech_OnUtteranceCompletedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_OnUtteranceCompletedListenerClass,_di_JTextToSpeech_OnUtteranceCompletedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTextToSpeech_OnUtteranceCompletedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeech_OnUtteranceCompletedListenerClass,_di_JTextToSpeech_OnUtteranceCompletedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTextToSpeech_OnUtteranceCompletedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2A7E4DA5-50FC-43AA-8ACC-98487C02147B}") JTextToSpeechServiceClass  : public Androidapi::Jni::App::JServiceClass 
{
	HIDESBASE virtual _di_JTextToSpeechService __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{52D88001-D8F7-4D5B-8194-CF6AEFD0C918}") JTextToSpeechService  : public Androidapi::Jni::App::JService 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	HIDESBASE virtual void __cdecl onCreate() = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl onGetDefaultVoiceNameFor(Androidapi::Jni::Javatypes::_di_JString lang, Androidapi::Jni::Javatypes::_di_JString country, Androidapi::Jni::Javatypes::_di_JString variant) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl onGetVoices() = 0 ;
	virtual int __cdecl onIsValidVoiceName(Androidapi::Jni::Javatypes::_di_JString voiceName) = 0 ;
	virtual int __cdecl onLoadVoice(Androidapi::Jni::Javatypes::_di_JString voiceName) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTextToSpeechService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeechServiceClass,_di_JTextToSpeechService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeechServiceClass,_di_JTextToSpeechService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTextToSpeechService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextToSpeechServiceClass,_di_JTextToSpeechService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTextToSpeechService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9D335A6E-78BE-4060-B3C1-6028E603073D}") JUtteranceProgressListenerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JUtteranceProgressListener __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{75D1A7E1-86E7-47D6-B9EC-96F0D69DC535}") JUtteranceProgressListener  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onAudioAvailable(Androidapi::Jni::Javatypes::_di_JString utteranceId, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* audio) = 0 ;
	virtual void __cdecl onBeginSynthesis(Androidapi::Jni::Javatypes::_di_JString utteranceId, int sampleRateInHz, int audioFormat, int channelCount) = 0 ;
	virtual void __cdecl onDone(Androidapi::Jni::Javatypes::_di_JString utteranceId) = 0 ;
	virtual void __cdecl onError(Androidapi::Jni::Javatypes::_di_JString utteranceId) = 0 /* overload */;
	virtual void __cdecl onError(Androidapi::Jni::Javatypes::_di_JString utteranceId, int errorCode) = 0 /* overload */;
	virtual void __cdecl onRangeStart(Androidapi::Jni::Javatypes::_di_JString utteranceId, int start, int end_, int frame) = 0 ;
	virtual void __cdecl onStart(Androidapi::Jni::Javatypes::_di_JString utteranceId) = 0 ;
	virtual void __cdecl onStop(Androidapi::Jni::Javatypes::_di_JString utteranceId, bool interrupted) = 0 ;
	virtual void __cdecl onUtteranceRangeStart(Androidapi::Jni::Javatypes::_di_JString utteranceId, int start, int end_) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJUtteranceProgressListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUtteranceProgressListenerClass,_di_JUtteranceProgressListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUtteranceProgressListenerClass,_di_JUtteranceProgressListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJUtteranceProgressListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JUtteranceProgressListenerClass,_di_JUtteranceProgressListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJUtteranceProgressListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DC50F32A-F1DA-40B3-82FC-0C98971CF1E9}") JVoiceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetLATENCY_HIGH() = 0 ;
	virtual int __cdecl _GetLATENCY_LOW() = 0 ;
	virtual int __cdecl _GetLATENCY_NORMAL() = 0 ;
	virtual int __cdecl _GetLATENCY_VERY_HIGH() = 0 ;
	virtual int __cdecl _GetLATENCY_VERY_LOW() = 0 ;
	virtual int __cdecl _GetQUALITY_HIGH() = 0 ;
	virtual int __cdecl _GetQUALITY_LOW() = 0 ;
	virtual int __cdecl _GetQUALITY_NORMAL() = 0 ;
	virtual int __cdecl _GetQUALITY_VERY_HIGH() = 0 ;
	virtual int __cdecl _GetQUALITY_VERY_LOW() = 0 ;
	HIDESBASE virtual _di_JVoice __cdecl init(Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Javatypes::_di_JLocale locale, int quality, int latency, bool requiresNetworkConnection, Androidapi::Jni::Javatypes::_di_JSet features) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int LATENCY_HIGH = {read=_GetLATENCY_HIGH};
	__property int LATENCY_LOW = {read=_GetLATENCY_LOW};
	__property int LATENCY_NORMAL = {read=_GetLATENCY_NORMAL};
	__property int LATENCY_VERY_HIGH = {read=_GetLATENCY_VERY_HIGH};
	__property int LATENCY_VERY_LOW = {read=_GetLATENCY_VERY_LOW};
	__property int QUALITY_HIGH = {read=_GetQUALITY_HIGH};
	__property int QUALITY_LOW = {read=_GetQUALITY_LOW};
	__property int QUALITY_NORMAL = {read=_GetQUALITY_NORMAL};
	__property int QUALITY_VERY_HIGH = {read=_GetQUALITY_VERY_HIGH};
	__property int QUALITY_VERY_LOW = {read=_GetQUALITY_VERY_LOW};
};

__interface  INTERFACE_UUID("{311F01AD-D407-42CD-89A6-20BE035551CC}") JVoice  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JSet __cdecl getFeatures() = 0 ;
	virtual int __cdecl getLatency() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JLocale __cdecl getLocale() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual int __cdecl getQuality() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isNetworkConnectionRequired() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVoice : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVoiceClass,_di_JVoice>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVoiceClass,_di_JVoice> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVoice() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVoiceClass,_di_JVoice>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVoice() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Speech */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_SPEECH)
using namespace Androidapi::Jni::Speech;
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
#endif	// Androidapi_Jni_SpeechHPP
