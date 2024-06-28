// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'CtlPanel.pas' rev: 34.00 (Windows)

#ifndef CtlpanelHPP
#define CtlpanelHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Winapi.Cpl.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ctlpanel
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EAppletException;
class DELPHICLASS TAppletModule;
class DELPHICLASS TAppletApplication;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EAppletException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EAppletException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EAppletException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EAppletException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EAppletException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EAppletException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EAppletException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EAppletException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EAppletException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAppletException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAppletException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAppletException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAppletException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EAppletException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TInitEvent)(System::TObject* Sender, bool &AppInitOK);

typedef void __fastcall (__closure *TCountEvent)(System::TObject* Sender, int &AppCount);

typedef System::Classes::TNotifyEvent TExitEvent;

typedef System::Classes::TNotifyEvent TSetupEvent;

typedef void __fastcall (__closure *TActivateEvent)(System::TObject* Sender, int Data);

typedef void __fastcall (__closure *TStopEvent)(System::TObject* Sender, int Data);

typedef void __fastcall (__closure *TInquireEvent)(System::TObject* Sender, int &idIcon, int &idName, int &idInfo, NativeInt &lData);

typedef void __fastcall (__closure *TNewInquireEvent)(System::TObject* Sender, NativeInt &lData, HICON &hIcon, System::UnicodeString &AppletName, System::UnicodeString &AppletInfo);

typedef void __fastcall (__closure *TStartWParmsEvent)(System::TObject* Sender, System::UnicodeString Params);

class PASCALIMPLEMENTATION TAppletModule : public System::Classes::TDataModule
{
	typedef System::Classes::TDataModule inherited;
	
private:
	TActivateEvent FOnActivate;
	TStopEvent FOnStop;
	TInquireEvent FOnInquire;
	TNewInquireEvent FOnNewInquire;
	TStartWParmsEvent FOnStartWParms;
	int FData;
	int FResidIcon;
	int FResidName;
	int FResidInfo;
	Vcl::Graphics::TIcon* FAppletIcon;
	System::UnicodeString FCaption;
	System::UnicodeString FHelp;
	void __fastcall SetData(const int Value);
	void __fastcall SetResidIcon(const int Value);
	void __fastcall SetResidInfo(const int Value);
	void __fastcall SetResidName(const int Value);
	void __fastcall SetAppletIcon(Vcl::Graphics::TIcon* const Value);
	void __fastcall SetCaption(const System::UnicodeString Value);
	void __fastcall SetHelp(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetCaption();
	
protected:
	DYNAMIC void __fastcall DoStop(int Data);
	DYNAMIC void __fastcall DoActivate(int Data);
	DYNAMIC void __fastcall DoInquire(tagCPLINFO &ACPLInfo);
	DYNAMIC void __fastcall DoNewInquire(tagNEWCPLINFOW &ANewCPLInfo);
	DYNAMIC void __fastcall DoStartWParms(System::UnicodeString Params);
	
public:
	__fastcall virtual TAppletModule(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TAppletModule();
	__property int Data = {read=FData, write=SetData, nodefault};
	
__published:
	__property TStopEvent OnStop = {read=FOnStop, write=FOnStop};
	__property TActivateEvent OnActivate = {read=FOnActivate, write=FOnActivate};
	__property TInquireEvent OnInquire = {read=FOnInquire, write=FOnInquire};
	__property TNewInquireEvent OnNewInquire = {read=FOnNewInquire, write=FOnNewInquire};
	__property TStartWParmsEvent OnStartWParms = {read=FOnStartWParms, write=FOnStartWParms};
	__property System::UnicodeString Caption = {read=GetCaption, write=SetCaption};
	__property Vcl::Graphics::TIcon* AppletIcon = {read=FAppletIcon, write=SetAppletIcon};
	__property System::UnicodeString Help = {read=FHelp, write=SetHelp};
	__property int ResidIcon = {read=FResidIcon, write=SetResidIcon, nodefault};
	__property int ResidName = {read=FResidName, write=SetResidName, nodefault};
	__property int ResidInfo = {read=FResidInfo, write=SetResidInfo, nodefault};
public:
	/* TDataModule.CreateNew */ inline __fastcall virtual TAppletModule(System::Classes::TComponent* AOwner, int Dummy) : System::Classes::TDataModule(AOwner, Dummy) { }
	
};


#ifndef _WIN64
typedef System::TMetaClass* TAppletModuleClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TAppletModuleClass);
#endif /* _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TCPLAppletClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TCPLAppletClass);
#endif /* _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TDataModuleClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TDataModuleClass);
#endif /* _WIN64 */

typedef void __fastcall (__closure *TOnAppletExceptionEvent)(System::TObject* Sender, System::Sysutils::Exception* E);

class PASCALIMPLEMENTATION TAppletApplication : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	NativeUInt FControlPanelHandle;
	System::Classes::TList* FModules;
	TInitEvent FOnInit;
	TCountEvent FOnCount;
	System::Classes::TNotifyEvent FOnExit;
	System::Classes::TNotifyEvent FOnSetup;
	int FModuleCount;
	TOnAppletExceptionEvent FOnException;
	TAppletModule* __fastcall GetModules(int Index);
	void __fastcall SetModules(int Index, TAppletModule* const Value);
	void __fastcall SetModuleCount(const int Value);
	int __fastcall GetModuleCount();
	
protected:
	DYNAMIC void __fastcall DoHandleException(System::TObject* Sender, System::Sysutils::Exception* E);
	DYNAMIC void __fastcall DoInit(bool &AppInitOK);
	DYNAMIC void __fastcall DoCount(int &AppCount);
	DYNAMIC void __fastcall DoExit();
	DYNAMIC void __fastcall DoSetup();
	
public:
	__fastcall virtual TAppletApplication(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TAppletApplication();
	virtual void __fastcall CreateForm(System::Classes::TComponentClass InstanceClass, void *Reference);
	void __fastcall HandleException(System::TObject* Sender);
	virtual void __fastcall Initialize();
	virtual void __fastcall Run();
	__property TAppletModule* Modules[int Index] = {read=GetModules, write=SetModules};
	__property int ModuleCount = {read=GetModuleCount, write=SetModuleCount, nodefault};
#ifndef _WIN64
	__property NativeUInt ControlPanelHandle = {read=FControlPanelHandle, nodefault};
#else /* _WIN64 */
	__property NativeUInt ControlPanelHandle = {read=FControlPanelHandle};
#endif /* _WIN64 */
	__property TInitEvent OnInit = {read=FOnInit, write=FOnInit};
	__property TCountEvent OnCount = {read=FOnCount, write=FOnCount};
	__property TOnAppletExceptionEvent OnException = {read=FOnException, write=FOnException};
	__property System::Classes::TNotifyEvent OnExit = {read=FOnExit, write=FOnExit};
	__property System::Classes::TNotifyEvent OnSetup = {read=FOnSetup, write=FOnSetup};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TAppletApplication* Application;
extern DELPHI_PACKAGE int __stdcall CPlApplet(NativeUInt hwndCPl, unsigned uMsg, int lParam1, int lParam2);
}	/* namespace Ctlpanel */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_CTLPANEL)
using namespace Ctlpanel;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// CtlpanelHPP
