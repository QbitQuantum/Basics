// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Dialogs.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Dialogs_AndroidHPP
#define Fmx_Dialogs_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.UITypes.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.Embarcadero.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <FMX.Dialogs.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Dialogs
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFMXDialogListenerParentList;
class DELPHICLASS TFMXDialogListener;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXDialogListenerParentList : public System::Generics::Collections::TList__1<TFMXDialogListener*>
{
	typedef System::Generics::Collections::TList__1<TFMXDialogListener*> inherited;
	
public:
	/* {System_Generics_Collections}TList<FMX_Dialogs_Android_TFMXDialogListener>.Create */ inline __fastcall TFMXDialogListenerParentList()/* overload */ : System::Generics::Collections::TList__1<TFMXDialogListener*>() { }
	/* {System_Generics_Collections}TList<FMX_Dialogs_Android_TFMXDialogListener>.Create */ inline __fastcall TFMXDialogListenerParentList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TFMXDialogListener*> > AComparer)/* overload */ : System::Generics::Collections::TList__1<TFMXDialogListener*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_Dialogs_Android_TFMXDialogListener>.Create */ inline __fastcall TFMXDialogListenerParentList(System::Generics::Collections::TEnumerable__1<TFMXDialogListener*>* const Collection)/* overload */ : System::Generics::Collections::TList__1<TFMXDialogListener*>(Collection) { }
	/* {System_Generics_Collections}TList<FMX_Dialogs_Android_TFMXDialogListener>.Destroy */ inline __fastcall virtual ~TFMXDialogListenerParentList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXDialogListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
	
private:
	typedef System::DynamicArray<System::UnicodeString> _TFMXDialogListener__1;
	
	typedef System::DynamicArray<System::UnicodeString> _TFMXDialogListener__2;
	
	
private:
	TFMXDialogListenerParentList* FParentList;
	_TFMXDialogListener__1 FValues;
	_TFMXDialogListener__2 FDefaultValues;
	System::Uitypes::TModalResult FModalResult;
	Fmx::Dialogs::_di_TInputCloseQueryProc FInputCloseQueryProc;
	System::Classes::TThread* FCallerThread;
	void __fastcall DoDialogClosed();
	void __fastcall SetParentList(TFMXDialogListenerParentList* const AList);
	
public:
	__fastcall TFMXDialogListener(const Fmx::Dialogs::_di_TInputCloseQueryProc AInputCloseQueryProc);
	void __cdecl onDialogClosed(int modalResult, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* values);
	__property TFMXDialogListenerParentList* ParentList = {read=FParentList, write=SetParentList};
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TFMXDialogListener() { }
	
private:
	void *__JFMXDialogListener;	// Androidapi::Jni::Embarcadero::JFMXDialogListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {008E6099-5C9D-4FF3-9EDD-8AA87B6A52E2}
	operator Androidapi::Jni::Embarcadero::_di_JFMXDialogListener()
	{
		Androidapi::Jni::Embarcadero::_di_JFMXDialogListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Embarcadero::JFMXDialogListener*(void) { return (Androidapi::Jni::Embarcadero::JFMXDialogListener*)&__JFMXDialogListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Dialogs */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DIALOGS_ANDROID)
using namespace Fmx::Dialogs::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DIALOGS)
using namespace Fmx::Dialogs;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Dialogs_AndroidHPP
