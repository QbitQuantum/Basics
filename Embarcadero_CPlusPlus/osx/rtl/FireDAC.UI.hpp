// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.UI.pas' rev: 34.00 (MacOS)

#ifndef Firedac_UiHPP
#define Firedac_UiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.IniFiles.hpp>
#include <FireDAC.Stan.Factory.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Consts.hpp>
#include <FireDAC.UI.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Ui
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDGUIxObject;
struct TFDLoginItem;
class DELPHICLASS TFDGUIxLoginDialogImplBase;
class DELPHICLASS TFDGUIxScriptImplBase;
class DELPHICLASS TFDGUIxVisualScriptImplBase;
class DELPHICLASS TFDGUIxWaitCursorImplBase;
class DELPHICLASS TFDGUIxVisualWaitCursorImplBase;
//-- type declarations -------------------------------------------------------
#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDGUIxObject : public Firedac::Stan::Factory::TFDObject
{
	typedef Firedac::Stan::Factory::TFDObject inherited;
	
protected:
	__classmethod virtual bool __fastcall IsFactoryEnabled(const System::UnicodeString AMyProvider, const System::UnicodeString AReqProvider);
public:
	/* TFDObject.Create */ inline __fastcall virtual TFDGUIxObject() : Firedac::Stan::Factory::TFDObject() { }
	/* TFDObject.Destroy */ inline __fastcall virtual ~TFDGUIxObject() { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

typedef TFDLoginItem *PFDLoginItem;

struct DECLSPEC_DRECORD TFDLoginItem
{
public:
	System::UnicodeString FParam;
	System::UnicodeString FType;
	System::UnicodeString FCaption;
	int FOrder;
	System::UnicodeString FValue;
};


class PASCALIMPLEMENTATION TFDGUIxLoginDialogImplBase : public TFDGUIxObject
{
	typedef TFDGUIxObject inherited;
	
	
private:
	typedef System::DynamicArray<TFDLoginItem> _TFDGUIxLoginDialogImplBase__1;
	
	
private:
	System::Classes::TNotifyEvent FOnHide;
	System::Classes::TNotifyEvent FOnShow;
	int FLoginRetries;
	Firedac::Ui::Intf::TFDGUIxLoginDialogEvent FOnChangePassword;
	Firedac::Ui::Intf::TFDGUIxLoginDialogEvent FOnLogin;
	bool FChangeExpiredPassword;
	System::Inifiles::TCustomIniFile* __fastcall CreateHistoryIniFile();
	bool __fastcall InitParamList();
	void __fastcall LoadHistory();
	void __fastcall SaveHistory();
	
protected:
	_TFDGUIxLoginDialogImplBase__1 FParams;
	System::Classes::TStrings* FHistory;
	int FHistoryIndex;
	System::UnicodeString FCaption;
	Firedac::Stan::Intf::_di_IFDStanConnectionDef FConnectionDef;
	bool FHistoryEnabled;
	System::UnicodeString FHistoryKey;
	Firedac::Ui::Intf::TFDGUIxLoginHistoryStorage FHistoryStorage;
	bool FHistoryWithPassword;
	System::Classes::TStrings* FVisibleItems;
	System::UnicodeString __fastcall GetCaption();
	bool __fastcall GetChangeExpiredPassword();
	bool __fastcall GetHistoryEnabled();
	System::UnicodeString __fastcall GetHistoryKey();
	Firedac::Ui::Intf::TFDGUIxLoginHistoryStorage __fastcall GetHistoryStorage();
	bool __fastcall GetHistoryWithPassword();
	int __fastcall GetLoginRetries();
	System::Classes::TStrings* __fastcall GetVisibleItems();
	Firedac::Stan::Intf::_di_IFDStanConnectionDef __fastcall GetConnectionDef();
	System::Classes::TNotifyEvent __fastcall GetOnHide();
	System::Classes::TNotifyEvent __fastcall GetOnShow();
	Firedac::Ui::Intf::TFDGUIxLoginDialogEvent __fastcall GetOnChangePassword();
	Firedac::Ui::Intf::TFDGUIxLoginDialogEvent __fastcall GetOnLogin();
	void __fastcall SetCaption(const System::UnicodeString AValue);
	void __fastcall SetChangeExpiredPassword(const bool AValue);
	void __fastcall SetHistoryEnabled(const bool AValue);
	void __fastcall SetHistoryKey(const System::UnicodeString AValue);
	void __fastcall SetHistoryStorage(const Firedac::Ui::Intf::TFDGUIxLoginHistoryStorage AValue);
	void __fastcall SetHistoryWithPassword(const bool AValue);
	void __fastcall SetLoginRetries(const int AValue);
	void __fastcall SetVisibleItems(System::Classes::TStrings* const AValue);
	void __fastcall SetConnectionDef(const Firedac::Stan::Intf::_di_IFDStanConnectionDef AValue);
	void __fastcall SetOnHide(const System::Classes::TNotifyEvent AValue);
	void __fastcall SetOnShow(const System::Classes::TNotifyEvent AValue);
	void __fastcall SetOnChangePassword(const Firedac::Ui::Intf::TFDGUIxLoginDialogEvent AValue);
	void __fastcall SetOnLogin(const Firedac::Ui::Intf::TFDGUIxLoginDialogEvent AValue);
	bool __fastcall Execute(Firedac::Ui::Intf::TFDGUIxLoginAction ALoginAction);
	void __fastcall GetAllLoginParams();
	virtual bool __fastcall ExecuteLogin() = 0 ;
	virtual bool __fastcall ExecuteChngPwd() = 0 ;
	void __fastcall RemoveHistory(const System::UnicodeString AName);
	void __fastcall ReadHistory(const System::UnicodeString AName, System::Classes::TStrings* AList);
	
public:
	virtual void __fastcall Initialize();
	__fastcall virtual ~TFDGUIxLoginDialogImplBase();
public:
	/* TFDObject.Create */ inline __fastcall virtual TFDGUIxLoginDialogImplBase() : TFDGUIxObject() { }
	
private:
	void *__IFDGUIxLoginDialog;	// Firedac::Ui::Intf::IFDGUIxLoginDialog 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2200}
	operator Firedac::Ui::Intf::_di_IFDGUIxLoginDialog()
	{
		Firedac::Ui::Intf::_di_IFDGUIxLoginDialog intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Ui::Intf::IFDGUIxLoginDialog*(void) { return (Firedac::Ui::Intf::IFDGUIxLoginDialog*)&__IFDGUIxLoginDialog; }
	#endif
	
};


class PASCALIMPLEMENTATION TFDGUIxScriptImplBase : public TFDGUIxObject
{
	typedef TFDGUIxObject inherited;
	
protected:
	System::Classes::TNotifyEvent FOnShow;
	System::Classes::TNotifyEvent FOnHide;
	Firedac::Ui::Intf::TFDGUIxScriptProgressEvent FOnProgress;
	Firedac::Ui::Intf::TFDGUIxScriptOutputEvent FOnOutput;
	Firedac::Ui::Intf::TFDGUIxScriptInputEvent FOnInput;
	Firedac::Ui::Intf::TFDGUIxScriptPauseEvent FOnPause;
	System::UnicodeString FCaption;
	Firedac::Ui::Intf::TFDGUIxScriptOptions FOptions;
	System::Classes::TNotifyEvent __fastcall GetOnShow();
	void __fastcall SetOnShow(const System::Classes::TNotifyEvent AValue);
	System::Classes::TNotifyEvent __fastcall GetOnHide();
	void __fastcall SetOnHide(const System::Classes::TNotifyEvent AValue);
	Firedac::Ui::Intf::TFDGUIxScriptProgressEvent __fastcall GetOnProgress();
	void __fastcall SetOnProgress(const Firedac::Ui::Intf::TFDGUIxScriptProgressEvent AValue);
	Firedac::Ui::Intf::TFDGUIxScriptOutputEvent __fastcall GetOnOutput();
	void __fastcall SetOnOutput(const Firedac::Ui::Intf::TFDGUIxScriptOutputEvent AValue);
	Firedac::Ui::Intf::TFDGUIxScriptInputEvent __fastcall GetOnInput();
	void __fastcall SetOnInput(const Firedac::Ui::Intf::TFDGUIxScriptInputEvent AValue);
	Firedac::Ui::Intf::TFDGUIxScriptPauseEvent __fastcall GetOnPause();
	void __fastcall SetOnPause(const Firedac::Ui::Intf::TFDGUIxScriptPauseEvent AValue);
	System::UnicodeString __fastcall GetCaption();
	void __fastcall SetCaption(const System::UnicodeString AValue);
	Firedac::Ui::Intf::TFDGUIxScriptOptions __fastcall GetOptions();
	void __fastcall SetOptions(Firedac::Ui::Intf::TFDGUIxScriptOptions AValue);
	virtual void __fastcall Show() = 0 ;
	virtual void __fastcall Progress(const Firedac::Ui::Intf::_di_IFDGUIxScriptDialogInfoProvider AInfoProvider) = 0 ;
	virtual void __fastcall Output(const System::UnicodeString AStr, Firedac::Ui::Intf::TFDScriptOutputKind AKind) = 0 ;
	virtual void __fastcall Input(const System::UnicodeString APrompt, System::UnicodeString &AResult) = 0 ;
	virtual void __fastcall Pause(const System::UnicodeString APrompt) = 0 ;
	virtual void __fastcall Hide() = 0 ;
public:
	/* TFDObject.Create */ inline __fastcall virtual TFDGUIxScriptImplBase() : TFDGUIxObject() { }
	/* TFDObject.Destroy */ inline __fastcall virtual ~TFDGUIxScriptImplBase() { }
	
private:
	void *__IFDGUIxScriptDialog;	// Firedac::Ui::Intf::IFDGUIxScriptDialog 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2205}
	operator Firedac::Ui::Intf::_di_IFDGUIxScriptDialog()
	{
		Firedac::Ui::Intf::_di_IFDGUIxScriptDialog intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Ui::Intf::IFDGUIxScriptDialog*(void) { return (Firedac::Ui::Intf::IFDGUIxScriptDialog*)&__IFDGUIxScriptDialog; }
	#endif
	
};


class PASCALIMPLEMENTATION TFDGUIxVisualScriptImplBase : public TFDGUIxScriptImplBase
{
	typedef TFDGUIxScriptImplBase inherited;
	
public:
	virtual void __fastcall Initialize();
public:
	/* TFDObject.Create */ inline __fastcall virtual TFDGUIxVisualScriptImplBase() : TFDGUIxScriptImplBase() { }
	/* TFDObject.Destroy */ inline __fastcall virtual ~TFDGUIxVisualScriptImplBase() { }
	
};


class PASCALIMPLEMENTATION TFDGUIxWaitCursorImplBase : public TFDGUIxObject
{
	typedef TFDGUIxObject inherited;
	
protected:
	Firedac::Ui::Intf::TFDGUIxScreenCursor FWaitCursor;
	System::Classes::TNotifyEvent FOnShow;
	System::Classes::TNotifyEvent FOnHide;
	virtual void __fastcall StartWait() = 0 ;
	virtual void __fastcall StopWait() = 0 ;
	virtual void __fastcall PushWait() = 0 ;
	virtual void __fastcall PopWait() = 0 ;
	virtual void __fastcall ForceStopWait() = 0 ;
	Firedac::Ui::Intf::TFDGUIxScreenCursor __fastcall GetWaitCursor();
	void __fastcall SetWaitCursor(const Firedac::Ui::Intf::TFDGUIxScreenCursor AValue);
	System::Classes::TNotifyEvent __fastcall GetOnShow();
	void __fastcall SetOnShow(const System::Classes::TNotifyEvent AValue);
	System::Classes::TNotifyEvent __fastcall GetOnHide();
	void __fastcall SetOnHide(const System::Classes::TNotifyEvent AValue);
public:
	/* TFDObject.Create */ inline __fastcall virtual TFDGUIxWaitCursorImplBase() : TFDGUIxObject() { }
	/* TFDObject.Destroy */ inline __fastcall virtual ~TFDGUIxWaitCursorImplBase() { }
	
private:
	void *__IFDGUIxWaitCursor;	// Firedac::Ui::Intf::IFDGUIxWaitCursor 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2201}
	operator Firedac::Ui::Intf::_di_IFDGUIxWaitCursor()
	{
		Firedac::Ui::Intf::_di_IFDGUIxWaitCursor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Ui::Intf::IFDGUIxWaitCursor*(void) { return (Firedac::Ui::Intf::IFDGUIxWaitCursor*)&__IFDGUIxWaitCursor; }
	#endif
	
};


class PASCALIMPLEMENTATION TFDGUIxVisualWaitCursorImplBase : public TFDGUIxWaitCursorImplBase
{
	typedef TFDGUIxWaitCursorImplBase inherited;
	
private:
	Firedac::Ui::Intf::_di_IFDGUIxTimer FTimer;
	unsigned FStopRequestTime;
	int FWasActive;
	bool __fastcall IsVisible();
	void __fastcall HideCursor();
	void __fastcall ShowCursor();
	void __fastcall TimerProc(System::TObject* ASender);
	void __fastcall StopTimer();
	void __fastcall StartTimer();
	
protected:
	virtual bool __fastcall CheckCurCursor() = 0 ;
	virtual bool __fastcall InternalHideCursor() = 0 ;
	virtual void __fastcall InternalShowCursor() = 0 ;
	virtual void __fastcall StartWait();
	virtual void __fastcall StopWait();
	virtual void __fastcall PushWait();
	virtual void __fastcall PopWait();
	virtual void __fastcall ForceStopWait();
	
public:
	virtual void __fastcall Initialize();
	__fastcall virtual ~TFDGUIxVisualWaitCursorImplBase();
public:
	/* TFDObject.Create */ inline __fastcall virtual TFDGUIxVisualWaitCursorImplBase() : TFDGUIxWaitCursorImplBase() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_UI)
using namespace Firedac::Ui;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_UiHPP
