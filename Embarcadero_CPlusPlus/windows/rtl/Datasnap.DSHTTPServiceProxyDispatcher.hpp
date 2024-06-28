// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSHTTPServiceProxyDispatcher.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DshttpserviceproxydispatcherHPP
#define Datasnap_DshttpserviceproxydispatcherHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Datasnap.DSClientMetadata.hpp>
#include <Datasnap.DSHTTP.hpp>
#include <Datasnap.DSHTTPCommon.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dshttpserviceproxydispatcher
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSHTTPServiceProxyDispatcher;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDSHTTPServiceProxyDispatcher : public Datasnap::Dshttp::TDSHTTPServiceFileDispatcher
{
	typedef Datasnap::Dshttp::TDSHTTPServiceFileDispatcher inherited;
	
private:
	System::UnicodeString FRequiredProxyFilesPath;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FAvailableProxies;
	Datasnap::Dsclientmetadata::TDSProxyGenerator* FDSProxyGenerator;
	void __fastcall CreateZipFile(System::UnicodeString LanguageRequiredFiles, System::UnicodeString Filename);
	bool __fastcall isSupportedProxy(const System::UnicodeString Language, /* out */ System::UnicodeString &WriterID);
	System::UnicodeString __fastcall GetLanguage(const System::UnicodeString AFileName);
	void __fastcall SetRequiredProxyFilesPath(const System::UnicodeString Value);
	void __fastcall SetDSProxyGenerator(Datasnap::Dsclientmetadata::TDSProxyGenerator* const Value);
	void __fastcall BuildAvailableProxies();
	bool __fastcall IsRequiredProxyFilesPathStored();
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall DoBeforeDispatch(System::TObject* Sender, const System::UnicodeString AFileName, Datasnap::Dshttpcommon::TDSHTTPContext* AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* Request, Datasnap::Dshttpcommon::TDSHTTPResponse* Response, bool &Handled);
	
public:
	__fastcall virtual TDSHTTPServiceProxyDispatcher(System::Classes::TComponent* AOwner);
	
__published:
	__property Datasnap::Dsclientmetadata::TDSProxyGenerator* DSProxyGenerator = {read=FDSProxyGenerator, write=SetDSProxyGenerator};
	__property System::UnicodeString RequiredProxyFilesPath = {read=FRequiredProxyFilesPath, write=SetRequiredProxyFilesPath, stored=IsRequiredProxyFilesPathStored};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSHTTPServiceProxyDispatcher() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dshttpserviceproxydispatcher */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSHTTPSERVICEPROXYDISPATCHER)
using namespace Datasnap::Dshttpserviceproxydispatcher;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DshttpserviceproxydispatcherHPP
