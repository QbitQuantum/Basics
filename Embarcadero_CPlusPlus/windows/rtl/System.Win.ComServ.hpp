// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.ComServ.pas' rev: 34.00 (Windows)

#ifndef System_Win_ComservHPP
#define System_Win_ComservHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.SysUtils.hpp>
#include <System.Win.ComObj.hpp>

//-- user supplied -----------------------------------------------------------
#include <cstdlib>

namespace System
{
namespace Win
{
namespace Comserv
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TComServer;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TStartMode : unsigned char { smStandalone, smAutomation, smRegServer, smUnregServer };

typedef void __fastcall (__closure *TLastReleaseEvent)(bool &Shutdown);

class PASCALIMPLEMENTATION TComServer : public System::Win::Comobj::TComServerObject
{
	typedef System::Win::Comobj::TComServerObject inherited;
	
private:
	int FObjectCount;
	int FFactoryCount;
	_di_ITypeLib FTypeLib;
	System::UnicodeString FServerName;
	System::UnicodeString FHelpFileName;
	bool FIsInprocServer;
	TStartMode FStartMode;
	bool FStartSuspended;
	bool FRegister;
	bool FUIInteractive;
	TLastReleaseEvent FOnLastRelease;
	System::Sysutils::TProcedure FTermProc;
	void __fastcall FactoryFree(System::Win::Comobj::TComObjectFactory* Factory);
	void __fastcall FactoryRegisterClassObject(System::Win::Comobj::TComObjectFactory* Factory);
	void __fastcall FactoryUpdateRegistry(System::Win::Comobj::TComObjectFactory* Factory);
	void __fastcall LastReleased();
	
protected:
	virtual int __fastcall CountObject(bool Created);
	virtual int __fastcall CountFactory(bool Created);
	virtual System::UnicodeString __fastcall GetHelpFileName();
	virtual System::UnicodeString __fastcall GetServerFileName();
	virtual System::UnicodeString __fastcall GetServerKey();
	virtual System::UnicodeString __fastcall GetServerName();
	virtual bool __fastcall GetStartSuspended();
	virtual _di_ITypeLib __fastcall GetTypeLib();
	virtual void __fastcall SetHelpFileName(const System::UnicodeString Value);
	
public:
	__fastcall TComServer();
	__fastcall virtual ~TComServer();
	void __fastcall Initialize();
	void __fastcall LoadTypeLib();
	void __fastcall SetServerName(const System::UnicodeString Name);
	void __fastcall UpdateRegistry(bool Register);
	__property bool IsInprocServer = {read=FIsInprocServer, write=FIsInprocServer, nodefault};
	__property int ObjectCount = {read=FObjectCount, nodefault};
	__property int FactoryCount = {read=FFactoryCount, nodefault};
	__property TStartMode StartMode = {read=FStartMode, nodefault};
	__property bool UIInteractive = {read=FUIInteractive, write=FUIInteractive, nodefault};
	__property TLastReleaseEvent OnLastRelease = {read=FOnLastRelease, write=FOnLastRelease};
	__property System::Sysutils::TProcedure TermProc = {read=FTermProc, write=FTermProc};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TComServer* ComServer;
extern DELPHI_PACKAGE _di_ITypeLib __fastcall LoadTypeLibrary(const System::UnicodeString ModuleName);
extern DELPHI_PACKAGE TComServer* __fastcall GetComServer();
}	/* namespace Comserv */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_COMSERV)
using namespace System::Win::Comserv;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN)
using namespace System::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif

//-- user supplied -----------------------------------------------------------
namespace System {
namespace Win {
namespace Comserv {
    // ------------------------------------------------------------------------- 
    // TCppActiveXModule 
    // ------------------------------------------------------------------------- 
     
    template <typename T> 
    void __fastcall Comserv_TermProc() 
    { 
      std::exit(EXIT_SUCCESS); 
    } 
     
    class TCppActiveXModule  
    { 
    public: 
      TCppActiveXModule(bool isLocal) 
      { 
        if (isLocal) 
          Comserv::GetComServer()->TermProc = Comserv_TermProc<TCppActiveXModule>; 
      } 
     ~TCppActiveXModule() 
      { 
      } 
    }; 
} /* namespace Comserv */ ; 
} /* namespace Win */ ; 
} /* namespace System */ ; 

#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Win_ComservHPP
