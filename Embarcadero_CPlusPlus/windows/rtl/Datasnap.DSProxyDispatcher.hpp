// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProxyDispatcher.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsproxydispatcherHPP
#define Datasnap_DsproxydispatcherHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Datasnap.DSClientMetadata.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <Web.HTTPApp.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsproxydispatcher
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSProxyDispatcher;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDSProxyDispatcher : public Web::Httpapp::TCustomWebFileDispatcher
{
	typedef Web::Httpapp::TCustomWebFileDispatcher inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FAvailableProxies;
	Datasnap::Dsclientmetadata::TDSProxyGenerator* FDSProxyGenerator;
	void __fastcall OnBeforeDispatch(System::TObject* Sender, const System::UnicodeString AFileName, Web::Httpapp::TWebRequest* Request, Web::Httpapp::TWebResponse* Response, bool &Handled);
	void __fastcall BuildAvailableProxies();
	void __fastcall SetDSProxyGenerator(Datasnap::Dsclientmetadata::TDSProxyGenerator* const Value);
	System::UnicodeString __fastcall GetLanguage(const System::UnicodeString AFileName);
	
private:
	System::UnicodeString FRequiredProxyFilesPath;
	HIDESBASE Web::Httpapp::TMethodType __fastcall DispatchMethodType();
	bool __fastcall IsRequiredProxyFilesPathStored();
	void __fastcall SetRequiredProxyFilesPath(const System::UnicodeString Value);
	
protected:
	void __fastcall CreateZipFile(System::UnicodeString LanguageRequiredFiles, System::UnicodeString Filename);
	bool __fastcall isSupportedProxy(const System::UnicodeString Language, /* out */ System::UnicodeString &WriterID);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TDSProxyDispatcher(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSProxyDispatcher();
	
__published:
	__property AfterDispatch;
	__property System::UnicodeString RequiredProxyFilesPath = {read=FRequiredProxyFilesPath, write=SetRequiredProxyFilesPath, stored=IsRequiredProxyFilesPathStored};
	__property Datasnap::Dsclientmetadata::TDSProxyGenerator* DSProxyGenerator = {read=FDSProxyGenerator, write=SetDSProxyGenerator};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsproxydispatcher */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROXYDISPATCHER)
using namespace Datasnap::Dsproxydispatcher;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproxydispatcherHPP
