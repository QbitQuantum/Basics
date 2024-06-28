// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdServerInterceptLogBase.pas' rev: 34.00 (Android)

#ifndef IdserverinterceptlogbaseHPP
#define IdserverinterceptlogbaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdIntercept.hpp>
#include <IdGlobal.hpp>
#include <IdLogBase.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idserverinterceptlogbase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdServerInterceptLogBase;
class DELPHICLASS TIdServerInterceptLogFileConnection;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdServerInterceptLogBase : public Idintercept::TIdServerIntercept
{
	typedef Idintercept::TIdServerIntercept inherited;
	
protected:
	Idglobal::TIdCriticalSection* FLock;
	bool FLogTime;
	bool FReplaceCRLF;
	bool FHasInit;
	virtual void __fastcall InitComponent();
	
public:
	virtual void __fastcall Init();
	virtual Idintercept::TIdConnectionIntercept* __fastcall Accept(System::Classes::TComponent* AConnection);
	__fastcall virtual ~TIdServerInterceptLogBase();
	virtual void __fastcall DoLogWriteString(const System::UnicodeString AText) = 0 ;
	virtual void __fastcall LogWriteString(const System::UnicodeString AText);
	
__published:
	__property bool LogTime = {read=FLogTime, write=FLogTime, default=1};
	__property bool ReplaceCRLF = {read=FReplaceCRLF, write=FReplaceCRLF, default=1};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdServerInterceptLogBase(System::Classes::TComponent* AOwner)/* overload */ : Idintercept::TIdServerIntercept(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdServerInterceptLogBase()/* overload */ : Idintercept::TIdServerIntercept() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdServerInterceptLogFileConnection : public Idlogbase::TIdLogBase
{
	typedef Idlogbase::TIdLogBase inherited;
	
protected:
	TIdServerInterceptLogBase* FServerInterceptLog;
	virtual void __fastcall LogReceivedData(const System::UnicodeString AText, const System::UnicodeString AData);
	virtual void __fastcall LogSentData(const System::UnicodeString AText, const System::UnicodeString AData);
	virtual void __fastcall LogStatus(const System::UnicodeString AText);
	virtual System::UnicodeString __fastcall GetConnectionID();
public:
	/* TIdLogBase.Destroy */ inline __fastcall virtual ~TIdServerInterceptLogFileConnection() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdServerInterceptLogFileConnection(System::Classes::TComponent* AOwner)/* overload */ : Idlogbase::TIdLogBase(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdServerInterceptLogFileConnection()/* overload */ : Idlogbase::TIdLogBase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idserverinterceptlogbase */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSERVERINTERCEPTLOGBASE)
using namespace Idserverinterceptlogbase;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdserverinterceptlogbaseHPP
