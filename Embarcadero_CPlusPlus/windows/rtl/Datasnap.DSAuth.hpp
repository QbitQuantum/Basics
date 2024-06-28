// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSAuth.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsauthHPP
#define Datasnap_DsauthHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DBXCommon.hpp>
#include <Datasnap.DSCommonServer.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsauth
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TRoleAuth;
class DELPHICLASS TDSCustomRoleItem;
class DELPHICLASS TDSRoleItem;
class DELPHICLASS TDSRoleItems;
class DELPHICLASS TDSCustomAuthenticationManager;
class DELPHICLASS TDSAuthenticationManager;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TRoleAuth : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	bool FIsDesignTime;
	System::TDateTime FCreateTime;
	System::Classes::TStringList* FAuthorizedRoles;
	System::Classes::TStringList* FDeniedRoles;
	
public:
	__fastcall virtual TRoleAuth(System::UnicodeString AuthorizedRoles, System::UnicodeString DeniedRoles)/* overload */;
	__fastcall virtual TRoleAuth(System::Classes::TStrings* AllowRoles, System::Classes::TStrings* DenyRoles, bool DesignTime)/* overload */;
	__fastcall virtual ~TRoleAuth();
	__property System::Classes::TStringList* AuthorizedRoles = {read=FAuthorizedRoles};
	__property System::Classes::TStringList* DeniedRoles = {read=FDeniedRoles};
	__property bool IsDesignTime = {read=FIsDesignTime, nodefault};
	__property System::TDateTime CreateTime = {read=FCreateTime};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCustomRoleItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::Classes::TStrings* FDeniedRoles;
	System::Classes::TStrings* FAuthorizedRoles;
	System::Classes::TStrings* FApplyTo;
	System::Classes::TStrings* FExclude;
	void __fastcall SetAuthorizedRoles(System::Classes::TStrings* const Value);
	void __fastcall SetDeniedRoles(System::Classes::TStrings* const Value);
	void __fastcall SetApplyTo(System::Classes::TStrings* const Value);
	void __fastcall SetExclude(System::Classes::TStrings* const Value);
	HIDESBASE void __fastcall Changed();
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	__fastcall virtual TDSCustomRoleItem(System::Classes::TCollection* Collection)/* overload */;
	__fastcall virtual ~TDSCustomRoleItem();
	__property System::Classes::TStrings* AuthorizedRoles = {read=FAuthorizedRoles, write=SetAuthorizedRoles};
	__property System::Classes::TStrings* DeniedRoles = {read=FDeniedRoles, write=SetDeniedRoles};
	__property System::Classes::TStrings* ApplyTo = {read=FApplyTo, write=SetApplyTo};
	__property System::Classes::TStrings* Exclude = {read=FExclude, write=SetExclude};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRoleItem : public TDSCustomRoleItem
{
	typedef TDSCustomRoleItem inherited;
	
__published:
	__property AuthorizedRoles;
	__property DeniedRoles;
	__property ApplyTo;
	__property Exclude;
public:
	/* TDSCustomRoleItem.Create */ inline __fastcall virtual TDSRoleItem(System::Classes::TCollection* Collection)/* overload */ : TDSCustomRoleItem(Collection) { }
	/* TDSCustomRoleItem.Destroy */ inline __fastcall virtual ~TDSRoleItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSRoleItems : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TDSRoleItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	System::Classes::TPersistent* FOwner;
	System::TDateTime FLastUpdated;
	
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	HIDESBASE TDSRoleItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TDSRoleItem* const Value);
	
public:
	__fastcall virtual TDSRoleItems(System::Classes::TPersistent* AOwner);
	void __fastcall MarkUpdated();
	__property System::TDateTime LastUpdated = {read=FLastUpdated};
	__property TDSRoleItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TDSRoleItems() { }
	
};


typedef void __fastcall (__closure *TDSAuthenticationEvent)(System::TObject* Sender, const System::UnicodeString Protocol, const System::UnicodeString Context, const System::UnicodeString User, const System::UnicodeString Password, bool &valid, System::Classes::TStrings* UserRoles);

typedef void __fastcall (__closure *TDSAuthorizationEvent)(System::TObject* Sender, Datasnap::Dscommonserver::TDSAuthorizeEventObject* AuthorizeEventObject, bool &valid);

enum DECLSPEC_DENUM TDSRoleComparison : unsigned char { rcNoUserRoles, rcNoMethodRoles, rcUserRoleAllowed, rcUserRoleDenied, rcNoMatch };

class PASCALIMPLEMENTATION TDSCustomAuthenticationManager : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TDSAuthenticationEvent FOnUserAuthenticate;
	TDSAuthorizationEvent FOnUserAuthorize;
	Data::Dbxcommon::TValidateCertificate FValidateCertificateEvent;
	
private:
	TDSRoleItems* FRoleItems;
	void __fastcall SetRoleItems(TDSRoleItems* const Value);
	
protected:
	TDSAuthenticationEvent __fastcall GetOnUserAuthenticate();
	TDSAuthorizationEvent __fastcall GetOnUserAuthorize();
	virtual Data::Dbxcommon::TValidateCertificate __fastcall GetValidateCertificateEvent();
	virtual void __fastcall SetValidateCertificateEvent(const Data::Dbxcommon::TValidateCertificate Event);
	virtual bool __fastcall HasUserAuthenticateEvent();
	virtual System::Classes::TStrings* __fastcall SessionUserRoles();
	virtual bool __fastcall Authenticate(Datasnap::Dscommonserver::TDSAuthenticateEventObject* const AuthenticateEventObject, const System::UnicodeString Protocol, const System::UnicodeString Context, const System::UnicodeString User, const System::UnicodeString Password, System::Classes::TStrings* UserRoles = (System::Classes::TStrings*)(0x0))/* overload */;
	
public:
	__fastcall virtual TDSCustomAuthenticationManager(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSCustomAuthenticationManager();
	__classmethod TDSRoleComparison __fastcall CompareRoles(System::Classes::TStrings* UserRoles, System::Classes::TStrings* AuthorizedRoles, System::Classes::TStrings* DeniedRoles);
	virtual bool __fastcall Authenticate(const System::UnicodeString Protocol, const System::UnicodeString Context, const System::UnicodeString AuthUserName, const System::UnicodeString AuthPassword, System::TObject* const Request, System::TObject* const Response)/* overload */;
	virtual bool __fastcall Authenticate(Datasnap::Dscommonserver::TDSAuthenticateEventObject* const AuthenticateEventObject, Data::Dbxcommon::TDBXProperties* connectionProps)/* overload */;
	virtual bool __fastcall ValidatePeerCertificate(Data::Dbxcommon::TX509Certificate* Certificate, const int ADepth);
	virtual bool __fastcall Authorize(Datasnap::Dscommonserver::TDSAuthorizeEventObject* const EventObject);
	__property TDSAuthorizationEvent OnUserAuthorize = {read=GetOnUserAuthorize, write=FOnUserAuthorize};
	__property TDSAuthenticationEvent OnUserAuthenticate = {read=GetOnUserAuthenticate, write=FOnUserAuthenticate};
	__property Data::Dbxcommon::TValidateCertificate OnValidatePeerCertificate = {read=GetValidateCertificateEvent, write=SetValidateCertificateEvent};
	virtual TRoleAuth* __fastcall GetAuthRole(const System::UnicodeString ClassName, const System::UnicodeString MethodName);
	__property TDSRoleItems* Roles = {read=FRoleItems, write=SetRoleItems};
};


class PASCALIMPLEMENTATION TDSAuthenticationManager : public TDSCustomAuthenticationManager
{
	typedef TDSCustomAuthenticationManager inherited;
	
__published:
	__property OnUserAuthenticate;
	__property OnUserAuthorize;
	__property Roles;
public:
	/* TDSCustomAuthenticationManager.Create */ inline __fastcall virtual TDSAuthenticationManager(System::Classes::TComponent* AOwner) : TDSCustomAuthenticationManager(AOwner) { }
	/* TDSCustomAuthenticationManager.Destroy */ inline __fastcall virtual ~TDSAuthenticationManager() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsauth */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSAUTH)
using namespace Datasnap::Dsauth;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsauthHPP
