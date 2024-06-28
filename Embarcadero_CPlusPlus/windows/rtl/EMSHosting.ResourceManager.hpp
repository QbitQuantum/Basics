// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.ResourceManager.pas' rev: 34.00 (Windows)

#ifndef Emshosting_ResourcemanagerHPP
#define Emshosting_ResourcemanagerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <EMS.ResourceAPI.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "EMSHosting.ResourceManager"

namespace Emshosting
{
namespace Resourcemanager
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMSEndpointManagerImpl;
class DELPHICLASS TEMSEndpointAuthorizationImpl;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndpointManagerImpl : public Ems::Resourceapi::TEMSEndpointManager
{
	typedef Ems::Resourceapi::TEMSEndpointManager inherited;
	
private:
	System::Generics::Collections::TList__1<Ems::Resourceapi::TEMSResource*>* FResources;
	__classmethod void __fastcall Init();
	static TEMSEndpointManagerImpl* __fastcall GetInstance();
	
protected:
#ifndef _WIN64
	virtual System::DynamicArray<Ems::Resourceapi::TEMSResource*> __fastcall GetResources();
#else /* _WIN64 */
	virtual System::TArray__1<Ems::Resourceapi::TEMSResource*> __fastcall GetResources();
#endif /* _WIN64 */
	
public:
	__fastcall TEMSEndpointManagerImpl();
	__fastcall virtual ~TEMSEndpointManagerImpl();
#ifndef _WIN64
	System::DynamicArray<Ems::Resourceapi::TEMSResource*> __fastcall FindByBaseURL(const System::UnicodeString ABaseURL);
#else /* _WIN64 */
	System::TArray__1<Ems::Resourceapi::TEMSResource*> __fastcall FindByBaseURL(const System::UnicodeString ABaseURL);
#endif /* _WIN64 */
	Ems::Resourceapi::TEMSResource* __fastcall FindByName(const System::UnicodeString AName);
	virtual void __fastcall RegisterResource(Ems::Resourceapi::TEMSResource* const AResource);
	/* static */ __property TEMSEndpointManagerImpl* Instance = {read=GetInstance};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEndpointAuthorizationImpl : public Ems::Resourceapi::TEMSEndpointAuthorization
{
	typedef Ems::Resourceapi::TEMSEndpointAuthorization inherited;
	
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,Ems::Resourceapi::TEMSEndpointAuthorization::TACL*>* FACL;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,bool>* FAllowCreator;
	static TEMSEndpointAuthorizationImpl* __fastcall GetInstance();
	__classmethod void __fastcall Init();
	
public:
	__fastcall TEMSEndpointAuthorizationImpl();
	__fastcall virtual ~TEMSEndpointAuthorizationImpl();
	void __fastcall RegisterACL(const System::UnicodeString AName, Ems::Resourceapi::TEMSEndpointAuthorization::TACL* const AACL);
#ifndef _WIN64
	void __fastcall RegisterAllowCreator(const System::UnicodeString AResourceName, const System::DynamicArray<System::UnicodeString> AEndpointNames);
#else /* _WIN64 */
	void __fastcall RegisterAllowCreator(const System::UnicodeString AResourceName, const System::TArray__1<System::UnicodeString> AEndpointNames);
#endif /* _WIN64 */
	bool __fastcall AllowCreator(const System::UnicodeString AName);
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall AllowCreatorEndpoints(const System::UnicodeString AResource);
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall AllowCreatorEndpoints(const System::UnicodeString AResource);
#endif /* _WIN64 */
	virtual void __fastcall Authorize(Ems::Resourceapi::TEndpointContext* const AContext, Ems::Resourceapi::TEMSEndpointAuthorization::TACL* const AACL);
	virtual bool __fastcall FindACL(const System::UnicodeString AName, /* out */ Ems::Resourceapi::TEMSEndpointAuthorization::TACL* &AACL);
	/* static */ __property TEMSEndpointAuthorizationImpl* Instance = {read=GetInstance};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Resourcemanager */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_RESOURCEMANAGER)
using namespace Emshosting::Resourcemanager;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_ResourcemanagerHPP
