// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.EMSFireDAC.pas' rev: 34.00 (Windows)

#ifndef Rest_Backend_EmsfiredacHPP
#define Rest_Backend_EmsfiredacHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.JSON.hpp>
#include <REST.Backend.EMSProvider.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <REST.Backend.EndPoint.hpp>
#include <REST.Client.hpp>
#include <REST.Backend.Providers.hpp>
#include <REST.Backend.ServiceComponents.hpp>
#include <REST.Backend.ServiceTypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Emsfiredac
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomEMSFireDACClient;
class DELPHICLASS TEMSFireDACClient;
class DELPHICLASS TEEMSFireDACClientError;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomEMSFireDACClient : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Rest::Backend::Emsprovider::TEMSProvider* FProvider;
	Firedac::Comp::Client::TFDSchemaAdapter* FSchemaAdapter;
	Rest::Backend::Endpoint::TCustomBackendEndpoint* FGetEndpoint;
	Rest::Client::TCustomRESTResponse* FGetResponse;
	Rest::Backend::Endpoint::TCustomBackendEndpoint* FApplyEndpoint;
	Rest::Client::TCustomRESTResponse* FApplyResponse;
	System::UnicodeString FResource;
	Rest::Backend::Providers::_di_IBackendAuthReg FAuth;
	void __fastcall SetProvider(Rest::Backend::Emsprovider::TEMSProvider* const Value);
	void __fastcall SetSchemaAdapter(Firedac::Comp::Client::TFDSchemaAdapter* const Value);
	void __fastcall CheckProvider();
	void __fastcall CheckSchemaAdapter();
	void __fastcall UpdateEndpoints();
	void __fastcall CheckResource();
	bool __fastcall GetCanPostUpdates();
	void __fastcall SetAuth(const Rest::Backend::Providers::_di_IBackendAuthReg Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TCustomEMSFireDACClient(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomEMSFireDACClient();
	void __fastcall GetData();
	void __fastcall PostUpdates();
	__property Rest::Backend::Endpoint::TCustomBackendEndpoint* GetEndpoint = {read=FGetEndpoint};
	__property Rest::Backend::Endpoint::TCustomBackendEndpoint* ApplyEndpoint = {read=FApplyEndpoint};
	__property bool CanPostUpdates = {read=GetCanPostUpdates, nodefault};
	__property Rest::Backend::Emsprovider::TEMSProvider* Provider = {read=FProvider, write=SetProvider};
	__property Firedac::Comp::Client::TFDSchemaAdapter* SchemaAdapter = {read=FSchemaAdapter, write=SetSchemaAdapter};
	__property System::UnicodeString Resource = {read=FResource, write=FResource};
	__property Rest::Backend::Providers::_di_IBackendAuthReg Auth = {read=FAuth, write=SetAuth};
};


class PASCALIMPLEMENTATION TEMSFireDACClient : public TCustomEMSFireDACClient
{
	typedef TCustomEMSFireDACClient inherited;
	
__published:
	__property Provider;
	__property SchemaAdapter;
	__property Resource = {default=0};
	__property Auth;
public:
	/* TCustomEMSFireDACClient.Create */ inline __fastcall virtual TEMSFireDACClient(System::Classes::TComponent* AOwner) : TCustomEMSFireDACClient(AOwner) { }
	/* TCustomEMSFireDACClient.Destroy */ inline __fastcall virtual ~TEMSFireDACClient() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEEMSFireDACClientError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall TEEMSFireDACClientError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall TEEMSFireDACClientError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall TEEMSFireDACClientError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall TEEMSFireDACClientError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall TEEMSFireDACClientError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall TEEMSFireDACClientError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall TEEMSFireDACClientError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall TEEMSFireDACClientError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TEEMSFireDACClientError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TEEMSFireDACClientError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TEEMSFireDACClientError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TEEMSFireDACClientError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~TEEMSFireDACClientError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Emsfiredac */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_EMSFIREDAC)
using namespace Rest::Backend::Emsfiredac;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND)
using namespace Rest::Backend;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_Backend_EmsfiredacHPP
