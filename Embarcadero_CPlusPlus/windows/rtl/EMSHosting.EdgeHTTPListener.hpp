// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.EdgeHTTPListener.pas' rev: 34.00 (Windows)

#ifndef Emshosting_EdgehttplistenerHPP
#define Emshosting_EdgehttplistenerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <EMSHosting.EdgeService.hpp>
#include <EMSHosting.EdgeHTTPServer.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "EMSHosting.EdgeHTTPListener"

namespace Emshosting
{
namespace Edgehttplistener
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomEMSEdgeHTTPListener;
class DELPHICLASS TEMSEdgeHTTPListener;
class DELPHICLASS TCustomEMSEdgeHTTPSListener;
class DELPHICLASS TEMSEdgeHTTPSListener;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomEMSEdgeHTTPListener : public Emshosting::Edgeservice::TEMSEdgeListener
{
	typedef Emshosting::Edgeservice::TEMSEdgeListener inherited;
	
	
public:
	__interface DELPHIINTERFACE TCreateModuleEvent;
	typedef System::DelphiInterface<TCreateModuleEvent> _di_TCreateModuleEvent;
	__interface TCreateModuleEvent  : public System::IInterface 
	{
		virtual Emshosting::Edgeservice::TEMSEdgeListener::TModule* __fastcall Invoke() = 0 ;
	};
	
	
private:
	Emshosting::Edgehttpserver::TEMSEdgeHTTPServer* FServer;
	System::UnicodeString FHost;
	Emshosting::Edgeservice::TEMSEdgeListener::TModule* FModule;
	unsigned __fastcall Getport();
	void __fastcall Setport(const unsigned Value);
	
protected:
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(const bool Value);
	virtual Emshosting::Edgeservice::TEMSEdgeListener::TModule* __fastcall GetModule();
	virtual void __fastcall AddProtocolProps(System::Json::TJSONObject* const AProtocolProps);
	__property Emshosting::Edgehttpserver::TEMSEdgeHTTPServer* Server = {read=FServer};
	
public:
	__fastcall virtual TCustomEMSEdgeHTTPListener(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomEMSEdgeHTTPListener();
	__property System::UnicodeString Host = {read=FHost, write=FHost};
	__property unsigned Port = {read=Getport, write=Setport, nodefault};
};


class PASCALIMPLEMENTATION TEMSEdgeHTTPListener : public TCustomEMSEdgeHTTPListener
{
	typedef TCustomEMSEdgeHTTPListener inherited;
	
__published:
	__property Port;
	__property Host = {default=0};
public:
	/* TCustomEMSEdgeHTTPListener.Create */ inline __fastcall virtual TEMSEdgeHTTPListener(System::Classes::TComponent* AOwner) : TCustomEMSEdgeHTTPListener(AOwner) { }
	/* TCustomEMSEdgeHTTPListener.Destroy */ inline __fastcall virtual ~TEMSEdgeHTTPListener() { }
	
};


class PASCALIMPLEMENTATION TCustomEMSEdgeHTTPSListener : public TCustomEMSEdgeHTTPListener
{
	typedef TCustomEMSEdgeHTTPListener inherited;
	
	
public:
	typedef void __fastcall (__closure *TGetPasswordEvent)(System::TObject* Sender, System::UnicodeString &APassword);
	
	
private:
	TGetPasswordEvent FOnGetKeyPassword;
	System::UnicodeString __fastcall GetCertFile();
	System::UnicodeString __fastcall GetKeyFile();
	System::UnicodeString __fastcall GetRootCertFile();
	void __fastcall SetCertFile(const System::UnicodeString Value);
	void __fastcall SetKeyFile(const System::UnicodeString Value);
	void __fastcall SetRootCertFile(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall DoGetKeyPassword(System::UnicodeString &APassword);
	
public:
	__fastcall virtual TCustomEMSEdgeHTTPSListener(System::Classes::TComponent* AOwner);
	__property System::UnicodeString CertFile = {read=GetCertFile, write=SetCertFile};
	__property System::UnicodeString KeyFile = {read=GetKeyFile, write=SetKeyFile};
	__property System::UnicodeString RootCertFile = {read=GetRootCertFile, write=SetRootCertFile};
	__property TGetPasswordEvent OnGetKeyPassword = {read=FOnGetKeyPassword, write=FOnGetKeyPassword};
public:
	/* TCustomEMSEdgeHTTPListener.Destroy */ inline __fastcall virtual ~TCustomEMSEdgeHTTPSListener() { }
	
};


class PASCALIMPLEMENTATION TEMSEdgeHTTPSListener : public TCustomEMSEdgeHTTPSListener
{
	typedef TCustomEMSEdgeHTTPSListener inherited;
	
__published:
	__property Port;
	__property Host = {default=0};
	__property CertFile = {default=0};
	__property KeyFile = {default=0};
	__property OnGetKeyPassword;
	__property RootCertFile = {default=0};
public:
	/* TCustomEMSEdgeHTTPSListener.Create */ inline __fastcall virtual TEMSEdgeHTTPSListener(System::Classes::TComponent* AOwner) : TCustomEMSEdgeHTTPSListener(AOwner) { }
	
public:
	/* TCustomEMSEdgeHTTPListener.Destroy */ inline __fastcall virtual ~TEMSEdgeHTTPSListener() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Edgehttplistener */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_EDGEHTTPLISTENER)
using namespace Emshosting::Edgehttplistener;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_EdgehttplistenerHPP
