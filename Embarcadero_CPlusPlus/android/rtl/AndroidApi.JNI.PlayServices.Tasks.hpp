// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.PlayServices.Tasks.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_Playservices_TasksHPP
#define Androidapi_Jni_Playservices_TasksHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.PlayServices.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Playservices
{
namespace Tasks
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JCancellationTokenClass;
typedef System::DelphiInterface<JCancellationTokenClass> _di_JCancellationTokenClass;
__interface DELPHIINTERFACE JCancellationToken;
typedef System::DelphiInterface<JCancellationToken> _di_JCancellationToken;
class DELPHICLASS TJCancellationToken;
__interface DELPHIINTERFACE JCancellationTokenSourceClass;
typedef System::DelphiInterface<JCancellationTokenSourceClass> _di_JCancellationTokenSourceClass;
__interface DELPHIINTERFACE JCancellationTokenSource;
typedef System::DelphiInterface<JCancellationTokenSource> _di_JCancellationTokenSource;
class DELPHICLASS TJCancellationTokenSource;
__interface DELPHIINTERFACE JContinuationClass;
typedef System::DelphiInterface<JContinuationClass> _di_JContinuationClass;
__interface DELPHIINTERFACE JContinuation;
typedef System::DelphiInterface<JContinuation> _di_JContinuation;
class DELPHICLASS TJContinuation;
__interface DELPHIINTERFACE JOnCanceledListenerClass;
typedef System::DelphiInterface<JOnCanceledListenerClass> _di_JOnCanceledListenerClass;
__interface DELPHIINTERFACE JOnCanceledListener;
typedef System::DelphiInterface<JOnCanceledListener> _di_JOnCanceledListener;
class DELPHICLASS TJOnCanceledListener;
__interface DELPHIINTERFACE JOnCompleteListenerClass;
typedef System::DelphiInterface<JOnCompleteListenerClass> _di_JOnCompleteListenerClass;
__interface DELPHIINTERFACE JOnCompleteListener;
typedef System::DelphiInterface<JOnCompleteListener> _di_JOnCompleteListener;
class DELPHICLASS TJOnCompleteListener;
__interface DELPHIINTERFACE JOnFailureListenerClass;
typedef System::DelphiInterface<JOnFailureListenerClass> _di_JOnFailureListenerClass;
__interface DELPHIINTERFACE JOnFailureListener;
typedef System::DelphiInterface<JOnFailureListener> _di_JOnFailureListener;
class DELPHICLASS TJOnFailureListener;
__interface DELPHIINTERFACE JOnSuccessListenerClass;
typedef System::DelphiInterface<JOnSuccessListenerClass> _di_JOnSuccessListenerClass;
__interface DELPHIINTERFACE JOnSuccessListener;
typedef System::DelphiInterface<JOnSuccessListener> _di_JOnSuccessListener;
class DELPHICLASS TJOnSuccessListener;
__interface DELPHIINTERFACE JOnTokenCanceledListenerClass;
typedef System::DelphiInterface<JOnTokenCanceledListenerClass> _di_JOnTokenCanceledListenerClass;
__interface DELPHIINTERFACE JOnTokenCanceledListener;
typedef System::DelphiInterface<JOnTokenCanceledListener> _di_JOnTokenCanceledListener;
class DELPHICLASS TJOnTokenCanceledListener;
__interface DELPHIINTERFACE JRuntimeExecutionExceptionClass;
typedef System::DelphiInterface<JRuntimeExecutionExceptionClass> _di_JRuntimeExecutionExceptionClass;
__interface DELPHIINTERFACE JRuntimeExecutionException;
typedef System::DelphiInterface<JRuntimeExecutionException> _di_JRuntimeExecutionException;
class DELPHICLASS TJRuntimeExecutionException;
__interface DELPHIINTERFACE JSuccessContinuationClass;
typedef System::DelphiInterface<JSuccessContinuationClass> _di_JSuccessContinuationClass;
__interface DELPHIINTERFACE JSuccessContinuation;
typedef System::DelphiInterface<JSuccessContinuation> _di_JSuccessContinuation;
class DELPHICLASS TJSuccessContinuation;
__interface DELPHIINTERFACE JTaskClass;
typedef System::DelphiInterface<JTaskClass> _di_JTaskClass;
__interface DELPHIINTERFACE JTask;
typedef System::DelphiInterface<JTask> _di_JTask;
class DELPHICLASS TJTask;
__interface DELPHIINTERFACE JTaskCompletionSourceClass;
typedef System::DelphiInterface<JTaskCompletionSourceClass> _di_JTaskCompletionSourceClass;
__interface DELPHIINTERFACE JTaskCompletionSource;
typedef System::DelphiInterface<JTaskCompletionSource> _di_JTaskCompletionSource;
class DELPHICLASS TJTaskCompletionSource;
__interface DELPHIINTERFACE JTaskExecutorsClass;
typedef System::DelphiInterface<JTaskExecutorsClass> _di_JTaskExecutorsClass;
__interface DELPHIINTERFACE JTaskExecutors;
typedef System::DelphiInterface<JTaskExecutors> _di_JTaskExecutors;
class DELPHICLASS TJTaskExecutors;
__interface DELPHIINTERFACE JTasksClass;
typedef System::DelphiInterface<JTasksClass> _di_JTasksClass;
__interface DELPHIINTERFACE JTasks;
typedef System::DelphiInterface<JTasks> _di_JTasks;
class DELPHICLASS TJTasks;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{54992047-8D32-483B-9F0E-014DA5856366}") JCancellationTokenClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCancellationToken __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{07EB8B2D-D35A-4EE8-95CE-DE6ABF6F25F1}") JCancellationToken  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl isCancellationRequested() = 0 ;
	virtual _di_JCancellationToken __cdecl onCanceledRequested(_di_JOnTokenCanceledListener onTokenCanceledListener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCancellationToken : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationTokenClass,_di_JCancellationToken>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationTokenClass,_di_JCancellationToken> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCancellationToken() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationTokenClass,_di_JCancellationToken>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCancellationToken() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9766E52C-D42C-4A6B-A267-FE1FC09CFA24}") JCancellationTokenSourceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCancellationTokenSource __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{778D0256-1758-487C-BC4E-0A5707F4C964}") JCancellationTokenSource  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual _di_JCancellationToken __cdecl getToken() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCancellationTokenSource : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationTokenSourceClass,_di_JCancellationTokenSource>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationTokenSourceClass,_di_JCancellationTokenSource> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCancellationTokenSource() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCancellationTokenSourceClass,_di_JCancellationTokenSource>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCancellationTokenSource() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FCE10375-D6B8-4A1B-88E3-C3A56193AF87}") JContinuationClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{969CD9CE-2481-4E01-B998-B5E37D1B34A4}") JContinuation  : public Androidapi::Jnibridge::IJavaInstance 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJContinuation : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JContinuationClass,_di_JContinuation>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JContinuationClass,_di_JContinuation> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJContinuation() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JContinuationClass,_di_JContinuation>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJContinuation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{004542B2-41C0-4976-89EB-71272CB46F76}") JOnCanceledListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{A43992EC-6A69-4DC7-A222-0E812661C382}") JOnCanceledListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCanceled() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnCanceledListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnCanceledListenerClass,_di_JOnCanceledListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnCanceledListenerClass,_di_JOnCanceledListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnCanceledListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnCanceledListenerClass,_di_JOnCanceledListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnCanceledListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{70B28546-8DC5-44A9-9348-D016D9CFC152}") JOnCompleteListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{6EA0E0AA-3D47-4DCF-AE5C-6D861C4AA42F}") JOnCompleteListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onComplete(_di_JTask task) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnCompleteListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnCompleteListenerClass,_di_JOnCompleteListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnCompleteListenerClass,_di_JOnCompleteListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnCompleteListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnCompleteListenerClass,_di_JOnCompleteListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnCompleteListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1BC53B31-7582-4515-9159-1BFDEA41F529}") JOnFailureListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{37C18E4E-53EE-4A61-B6CD-C6D57D6FA134}") JOnFailureListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onFailure(Androidapi::Jni::Javatypes::_di_JException exception) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnFailureListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnFailureListenerClass,_di_JOnFailureListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnFailureListenerClass,_di_JOnFailureListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnFailureListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnFailureListenerClass,_di_JOnFailureListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnFailureListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FC00DCC1-A036-4F01-856A-6153512B1E8B}") JOnSuccessListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{DD9283EA-F418-4BAA-A8A8-34309E4245F8}") JOnSuccessListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onSuccess(Androidapi::Jni::Javatypes::_di_JObject tResult) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnSuccessListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnSuccessListenerClass,_di_JOnSuccessListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnSuccessListenerClass,_di_JOnSuccessListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnSuccessListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnSuccessListenerClass,_di_JOnSuccessListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnSuccessListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E47F998C-DEDB-4A13-82FF-F8294E5706AA}") JOnTokenCanceledListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{E48D9AF3-F505-4411-8D28-0BEB7F49F0F2}") JOnTokenCanceledListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCanceled() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnTokenCanceledListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnTokenCanceledListenerClass,_di_JOnTokenCanceledListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnTokenCanceledListenerClass,_di_JOnTokenCanceledListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnTokenCanceledListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnTokenCanceledListenerClass,_di_JOnTokenCanceledListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnTokenCanceledListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{494546B8-2948-4530-8CEE-E68CDD528442}") JRuntimeExecutionExceptionClass  : public Androidapi::Jni::Javatypes::JRuntimeExceptionClass 
{
	HIDESBASE virtual _di_JRuntimeExecutionException __cdecl init(Androidapi::Jni::Javatypes::_di_JThrowable throwable) = 0 ;
};

__interface  INTERFACE_UUID("{118E2731-9CFA-436D-A263-E84BB7D93C96}") JRuntimeExecutionException  : public Androidapi::Jni::Javatypes::JRuntimeException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRuntimeExecutionException : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRuntimeExecutionExceptionClass,_di_JRuntimeExecutionException>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRuntimeExecutionExceptionClass,_di_JRuntimeExecutionException> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRuntimeExecutionException() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRuntimeExecutionExceptionClass,_di_JRuntimeExecutionException>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRuntimeExecutionException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{170D3825-22A9-4642-A79B-D9C56D188896}") JSuccessContinuationClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{7595D13B-191F-426D-8C07-D0CC669AB156}") JSuccessContinuation  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual _di_JTask __cdecl then(Androidapi::Jni::Javatypes::_di_JObject tResult) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSuccessContinuation : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSuccessContinuationClass,_di_JSuccessContinuation>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSuccessContinuationClass,_di_JSuccessContinuation> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSuccessContinuation() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSuccessContinuationClass,_di_JSuccessContinuation>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSuccessContinuation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E9F05104-CB8A-4155-B89D-DF06F7CAA0C2}") JTaskClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JTask __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{9C0C585F-1DD9-4437-A5EF-A55673956D11}") JTask  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JTask __cdecl addOnCanceledListener(_di_JOnCanceledListener onCanceledListener) = 0 /* overload */;
	virtual _di_JTask __cdecl addOnCanceledListener(Androidapi::Jni::Javatypes::_di_JExecutor executor, _di_JOnCanceledListener onCanceledListener) = 0 /* overload */;
	virtual _di_JTask __cdecl addOnCanceledListener(Androidapi::Jni::App::_di_JActivity activity, _di_JOnCanceledListener onCanceledListener) = 0 /* overload */;
	virtual _di_JTask __cdecl addOnCompleteListener(_di_JOnCompleteListener onCompleteListener) = 0 /* overload */;
	virtual _di_JTask __cdecl addOnCompleteListener(Androidapi::Jni::Javatypes::_di_JExecutor executor, _di_JOnCompleteListener onCompleteListener) = 0 /* overload */;
	virtual _di_JTask __cdecl addOnCompleteListener(Androidapi::Jni::App::_di_JActivity activity, _di_JOnCompleteListener onCompleteListener) = 0 /* overload */;
	virtual _di_JTask __cdecl addOnFailureListener(_di_JOnFailureListener onFailureListener) = 0 /* overload */;
	virtual _di_JTask __cdecl addOnFailureListener(Androidapi::Jni::Javatypes::_di_JExecutor executor, _di_JOnFailureListener onFailureListener) = 0 /* overload */;
	virtual _di_JTask __cdecl addOnFailureListener(Androidapi::Jni::App::_di_JActivity activity, _di_JOnFailureListener onFailureListener) = 0 /* overload */;
	virtual _di_JTask __cdecl addOnSuccessListener(_di_JOnSuccessListener onSuccessListener) = 0 /* overload */;
	virtual _di_JTask __cdecl addOnSuccessListener(Androidapi::Jni::App::_di_JActivity activity, _di_JOnSuccessListener onSuccessListener) = 0 /* overload */;
	virtual _di_JTask __cdecl addOnSuccessListener(Androidapi::Jni::Javatypes::_di_JExecutor executor, _di_JOnSuccessListener onSuccessListener) = 0 /* overload */;
	virtual _di_JTask __cdecl continueWith(_di_JContinuation continuation) = 0 /* overload */;
	virtual _di_JTask __cdecl continueWith(Androidapi::Jni::Javatypes::_di_JExecutor executor, _di_JContinuation continuation) = 0 /* overload */;
	virtual _di_JTask __cdecl continueWithTask(_di_JContinuation continuation) = 0 /* overload */;
	virtual _di_JTask __cdecl continueWithTask(Androidapi::Jni::Javatypes::_di_JExecutor executor, _di_JContinuation continuation) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JException __cdecl getException() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getResult() = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getResult(Androidapi::Jni::Javatypes::_di_Jlang_Class class_) = 0 /* overload */;
	virtual bool __cdecl isCanceled() = 0 ;
	virtual bool __cdecl isComplete() = 0 ;
	virtual bool __cdecl isSuccessful() = 0 ;
	virtual _di_JTask __cdecl onSuccessTask(_di_JSuccessContinuation successContinuation) = 0 /* overload */;
	virtual _di_JTask __cdecl onSuccessTask(Androidapi::Jni::Javatypes::_di_JExecutor executor, _di_JSuccessContinuation successContinuation) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTask : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskClass,_di_JTask>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskClass,_di_JTask> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTask() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskClass,_di_JTask>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTask() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0830DA0D-0EFD-4C15-B32C-7F104132BF87}") JTaskCompletionSourceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JTaskCompletionSource __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JTaskCompletionSource __cdecl init(_di_JCancellationToken cancellationToken) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{3124BB2B-37AA-4A27-89C8-2F66CC1791E4}") JTaskCompletionSource  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JTask __cdecl getTask() = 0 ;
	virtual void __cdecl setException(Androidapi::Jni::Javatypes::_di_JException exception) = 0 ;
	virtual void __cdecl setResult(Androidapi::Jni::Javatypes::_di_JObject tResult) = 0 ;
	virtual bool __cdecl trySetException(Androidapi::Jni::Javatypes::_di_JException exception) = 0 ;
	virtual bool __cdecl trySetResult(Androidapi::Jni::Javatypes::_di_JObject tResult) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTaskCompletionSource : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskCompletionSourceClass,_di_JTaskCompletionSource>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskCompletionSourceClass,_di_JTaskCompletionSource> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTaskCompletionSource() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskCompletionSourceClass,_di_JTaskCompletionSource>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTaskCompletionSource() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1AB0DFE3-D64B-4217-8A2B-8A3547C87EC0}") JTaskExecutorsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JExecutor __cdecl _GetMAIN_THREAD() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JExecutor MAIN_THREAD = {read=_GetMAIN_THREAD};
};

__interface  INTERFACE_UUID("{F0DCBEA3-9101-4A0E-BB47-8FF8D41A5319}") JTaskExecutors  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTaskExecutors : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskExecutorsClass,_di_JTaskExecutors>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskExecutorsClass,_di_JTaskExecutors> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTaskExecutors() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTaskExecutorsClass,_di_JTaskExecutors>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTaskExecutors() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BC74FDB7-14AF-4A19-B9DE-0B6F594A166F}") JTasksClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JTask __cdecl call(Androidapi::Jni::Javatypes::_di_JCallable callable) = 0 /* overload */;
	virtual _di_JTask __cdecl call(Androidapi::Jni::Javatypes::_di_JExecutor executor, Androidapi::Jni::Javatypes::_di_JCallable callable) = 0 /* overload */;
	virtual _di_JTask __cdecl forCanceled() = 0 ;
	virtual _di_JTask __cdecl forException(Androidapi::Jni::Javatypes::_di_JException exception) = 0 ;
	virtual _di_JTask __cdecl whenAll(Androidapi::Jni::Javatypes::_di_JCollection collection) = 0 /* overload */;
	virtual _di_JTask __cdecl whenAllComplete(Androidapi::Jni::Javatypes::_di_JCollection collection) = 0 /* overload */;
	virtual _di_JTask __cdecl whenAllSuccess(Androidapi::Jni::Javatypes::_di_JCollection collection) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{14AAFE98-2354-4252-A90D-A0D31A7366BB}") JTasks  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTasks : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTasksClass,_di_JTasks>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTasksClass,_di_JTasks> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTasks() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTasksClass,_di_JTasks>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTasks() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Tasks */
}	/* namespace Playservices */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_PLAYSERVICES_TASKS)
using namespace Androidapi::Jni::Playservices::Tasks;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_PLAYSERVICES)
using namespace Androidapi::Jni::Playservices;
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
#endif	// Androidapi_Jni_Playservices_TasksHPP
