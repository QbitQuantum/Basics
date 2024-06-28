// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdAuthenticationManager.pas' rev: 34.00 (iOS)

#ifndef IdauthenticationmanagerHPP
#define IdauthenticationmanagerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAuthentication.hpp>
#include <IdBaseComponent.hpp>
#include <IdURI.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idauthenticationmanager
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdAuthenticationItem;
class DELPHICLASS TIdAuthenticationCollection;
class DELPHICLASS TIdAuthenticationManager;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdAuthenticationItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	Iduri::TIdURI* FURI;
	System::Classes::TStrings* FParams;
	void __fastcall SetParams(System::Classes::TStrings* const Value);
	void __fastcall SetURI(Iduri::TIdURI* const Value);
	
public:
	__fastcall virtual TIdAuthenticationItem(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TIdAuthenticationItem();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property Iduri::TIdURI* URL = {read=FURI, write=SetURI};
	__property System::Classes::TStrings* Params = {read=FParams, write=SetParams};
};


class PASCALIMPLEMENTATION TIdAuthenticationCollection : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
protected:
	TIdAuthenticationItem* __fastcall GetAuthItem(int AIndex);
	void __fastcall SetAuthItem(int AIndex, TIdAuthenticationItem* const Value);
	
public:
	HIDESBASE TIdAuthenticationItem* __fastcall Add();
	__fastcall TIdAuthenticationCollection(System::Classes::TPersistent* AOwner);
	__property TIdAuthenticationItem* Items[int AIndex] = {read=GetAuthItem, write=SetAuthItem};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdAuthenticationCollection() { }
	
};


class PASCALIMPLEMENTATION TIdAuthenticationManager : public Idbasecomponent::TIdBaseComponent
{
	typedef Idbasecomponent::TIdBaseComponent inherited;
	
protected:
	TIdAuthenticationCollection* FAuthentications;
	virtual void __fastcall InitComponent();
	
public:
	__fastcall virtual ~TIdAuthenticationManager();
	void __fastcall AddAuthentication(Idauthentication::TIdAuthentication* AAuthentication, Iduri::TIdURI* AURL);
	__property TIdAuthenticationCollection* Authentications = {read=FAuthentications};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdAuthenticationManager(System::Classes::TComponent* AOwner)/* overload */ : Idbasecomponent::TIdBaseComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdAuthenticationManager()/* overload */ : Idbasecomponent::TIdBaseComponent() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idauthenticationmanager */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDAUTHENTICATIONMANAGER)
using namespace Idauthenticationmanager;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdauthenticationmanagerHPP
