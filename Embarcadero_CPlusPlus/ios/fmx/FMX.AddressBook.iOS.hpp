// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.AddressBook.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Addressbook_IosHPP
#define Fmx_Addressbook_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Permissions.hpp>
#include <iOSapi.AddressBook.hpp>
#include <iOSapi.Foundation.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <FMX.AddressBook.hpp>
#include <FMX.AddressBook.Types.hpp>
#include <FMX.Surfaces.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Addressbook
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TiOSAddressBook;
class DELPHICLASS TiOSAddressBookSource;
class DELPHICLASS TiOSAddressBookGroup;
class DELPHICLASS TiOSAddressBookContact;
class DELPHICLASS TiOSAddressBookHelpers;
class DELPHICLASS TiOSAddressBookServices;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TiOSAddressBook : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	void *FAddressBookRef;
	Fmx::Addressbook::Types::TExternalChangeEvent FOnExternalChange;
	Fmx::Addressbook::Types::TPermissionRequestEvent FOnPermissionRequest;
	void __fastcall AddressBookRequestAccessCompletionHandler(bool granted, CFErrorRef error);
	static void __cdecl AddressBookExternalChange(void * addressBook, CFDictionaryRef info, void * context);
	
protected:
	void __fastcall DoPermissionRequest(const System::UnicodeString AMessage, const bool AAccessGranted);
	void __fastcall DoExternalChange();
	void __fastcall RevertCurrentChangesAndUpdate();
	void __fastcall RequestPermission(System::Permissions::TDisplayRationaleEvent ADisplayRationaleEvent = 0x0);
	Fmx::Addressbook::Types::TAuthorizationStatus __fastcall AuthorizationStatus(const Fmx::Addressbook::Types::TAddressBookAccessType AAccessType);
	void __fastcall AllSources(Fmx::Addressbook::TAddressBookSources* &ASources);
	Fmx::Addressbook::TAddressBookSource* __fastcall SourceByID(const System::UnicodeString AID);
	Fmx::Addressbook::TAddressBookSource* __fastcall DefaultSource();
	void __fastcall AllContacts(Fmx::Addressbook::TAddressBookSource* const ASource, Fmx::Addressbook::TAddressBookContacts* &AContacts);
	Fmx::Addressbook::TAddressBookContact* __fastcall ContactByID(const int AID);
	Fmx::Addressbook::TAddressBookContact* __fastcall CreateContact(Fmx::Addressbook::TAddressBookSource* const ASource = (Fmx::Addressbook::TAddressBookSource*)(0x0));
	void __fastcall SaveContact(Fmx::Addressbook::TAddressBookContact* const AContact);
	void __fastcall RemoveContact(Fmx::Addressbook::TAddressBookContact* const AContact)/* overload */;
	void __fastcall RemoveContact(const int AID)/* overload */;
	void __fastcall AllGroups(Fmx::Addressbook::TAddressBookSource* const ASource, Fmx::Addressbook::TAddressBookGroups* &AGroups);
	Fmx::Addressbook::TAddressBookGroup* __fastcall GroupByID(const int AID);
	void __fastcall SaveGroup(Fmx::Addressbook::TAddressBookGroup* const AGroup);
	void __fastcall RemoveGroup(Fmx::Addressbook::TAddressBookGroup* const AGroup)/* overload */;
	void __fastcall RemoveGroup(const int AID)/* overload */;
	Fmx::Addressbook::TAddressBookGroup* __fastcall CreateGroup(Fmx::Addressbook::TAddressBookSource* const ASource = (Fmx::Addressbook::TAddressBookSource*)(0x0));
	void __fastcall AllContactsInGroups(Fmx::Addressbook::TAddressBookGroups* const AGroups, Fmx::Addressbook::TAddressBookContacts* &AContacts);
	void __fastcall AddContactIntoGroup(Fmx::Addressbook::TAddressBookGroup* const AGroup, Fmx::Addressbook::TAddressBookContact* const AContact);
	void __fastcall RemoveContactFromGroup(Fmx::Addressbook::TAddressBookGroup* const AGroup, Fmx::Addressbook::TAddressBookContact* const AContact);
	Fmx::Addressbook::Types::TPermissionRequestEvent __fastcall GetOnPermissionRequest();
	void __fastcall SetOnPermissionRequest(const Fmx::Addressbook::Types::TPermissionRequestEvent AHandler);
	Fmx::Addressbook::Types::TExternalChangeEvent __fastcall GetOnExternalChange();
	void __fastcall SetOnExternalChange(const Fmx::Addressbook::Types::TExternalChangeEvent AHandler);
	
public:
	__fastcall TiOSAddressBook();
	__fastcall virtual ~TiOSAddressBook();
	__property void * AddressBookRef = {read=FAddressBookRef};
private:
	void *__IFMXAddressBookService;	// Fmx::Addressbook::IFMXAddressBookService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C9B83925-6A0E-464D-8CFE-7CD11DB366CA}
	operator Fmx::Addressbook::_di_IFMXAddressBookService()
	{
		Fmx::Addressbook::_di_IFMXAddressBookService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Addressbook::IFMXAddressBookService*(void) { return (Fmx::Addressbook::IFMXAddressBookService*)&__IFMXAddressBookService; }
	#endif
	
};


class PASCALIMPLEMENTATION TiOSAddressBookSource : public Fmx::Addressbook::TAddressBookSource
{
	typedef Fmx::Addressbook::TAddressBookSource inherited;
	
private:
	TiOSAddressBook* FAddressBook;
	void *FSourceRef;
	
protected:
	virtual System::UnicodeString __fastcall GetID();
	virtual System::UnicodeString __fastcall GetSourceName();
	virtual System::UnicodeString __fastcall GetSourceType();
	
public:
	__fastcall TiOSAddressBookSource(TiOSAddressBook* const AAddressBook, const void * ASourceRef);
	__fastcall virtual ~TiOSAddressBookSource();
	__property TiOSAddressBook* AddressBook = {read=FAddressBook};
	__property void * SourceRef = {read=FSourceRef};
};


class PASCALIMPLEMENTATION TiOSAddressBookGroup : public Fmx::Addressbook::TAddressBookGroup
{
	typedef Fmx::Addressbook::TAddressBookGroup inherited;
	
private:
	TiOSAddressBook* FAddressBook;
	void *FGroupRef;
	
protected:
	virtual System::UnicodeString __fastcall GetName();
	virtual void __fastcall SetName(const System::UnicodeString AValue);
	virtual int __fastcall GetID();
	virtual Fmx::Addressbook::TAddressBookSource* __fastcall GetSource();
	
public:
	__fastcall TiOSAddressBookGroup(TiOSAddressBook* const AAddressBook, Fmx::Addressbook::TAddressBookSource* const ASource);
	__fastcall TiOSAddressBookGroup(TiOSAddressBook* const AAddressBook, const void * AGroupRef);
	__fastcall virtual ~TiOSAddressBookGroup();
	__property TiOSAddressBook* AddressBook = {read=FAddressBook};
	__property void * GroupRef = {read=FGroupRef};
public:
	/* TAddressBookGroup.Create */ inline __fastcall TiOSAddressBookGroup() : Fmx::Addressbook::TAddressBookGroup() { }
	
};


class PASCALIMPLEMENTATION TiOSAddressBookContact : public Fmx::Addressbook::TAddressBookContact
{
	typedef Fmx::Addressbook::TAddressBookContact inherited;
	
private:
	TiOSAddressBook* FAddressBook;
	void *FPersonRef;
	void __fastcall SetPropertyValue(const int AProperty, const System::UnicodeString AValue)/* overload */;
	void __fastcall SetPropertyValue(const int AProperty, const System::TDateTime AValue)/* overload */;
	void __fastcall SetPropertyValue(Fmx::Addressbook::Types::TContactDates* const AValue)/* overload */;
	void __fastcall SetPropertyValue(Fmx::Addressbook::Types::TContactAddresses* const AValue)/* overload */;
	void __fastcall SetPropertyValue(Fmx::Addressbook::Types::TContactMessagingServices* const AValue)/* overload */;
	void __fastcall SetPropertyValue(Fmx::Addressbook::Types::TContactSocialProfiles* const AValue)/* overload */;
	void __fastcall SetPropertyValue(Fmx::Addressbook::Types::TContactPhones* const AValue)/* overload */;
	void __fastcall SetPropertyValue(Fmx::Addressbook::Types::TContactEmails* const AValue)/* overload */;
	void __fastcall SetPropertyValue(Fmx::Addressbook::Types::TContactRelatedNames* const AValue)/* overload */;
	void __fastcall SetPropertyValue(Fmx::Addressbook::Types::TContactURLs* const AValue)/* overload */;
	void __fastcall SetPropertyValue(const unsigned AFormat, Fmx::Surfaces::TBitmapSurface* const AValue)/* overload */;
	System::UnicodeString __fastcall GetStringPropertyValue(const int AProperty)/* overload */;
	System::TDateTime __fastcall GetDateTimePropertyValue(const int AProperty)/* overload */;
	System::TDateTime __fastcall GetDatePropertyValue(const int AProperty);
	Fmx::Surfaces::TBitmapSurface* __fastcall GetPhotoPropertyValue(const unsigned AFormat)/* overload */;
	Fmx::Addressbook::Types::TContactAddresses* __fastcall GetAddressesPropertyValue(const int AProperty)/* overload */;
	Fmx::Addressbook::Types::TContactSocialProfiles* __fastcall GetSocialProfilesPropertyValue(const int AProperty)/* overload */;
	
protected:
	virtual System::UnicodeString __fastcall GetStringValue(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetStringValue(const Fmx::Addressbook::Types::TContactField AIndex, const System::UnicodeString AValue);
	virtual Fmx::Surfaces::TBitmapSurface* __fastcall GetBitmapValue(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetBitmapValue(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Surfaces::TBitmapSurface* const AValue);
	virtual System::TDateTime __fastcall GetDateTimeValue(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetDateTimeValue(const Fmx::Addressbook::Types::TContactField AIndex, const System::TDateTime AValue);
	virtual Fmx::Addressbook::Types::TContactDates* __fastcall GetDates(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetDates(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactDates* const AValue);
	virtual Fmx::Addressbook::Types::TContactAddresses* __fastcall GetAddresses(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetAddresses(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactAddresses* const AValue);
	virtual Fmx::Addressbook::Types::TContactMessagingServices* __fastcall GetMessagingServices(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetMessagingServices(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactMessagingServices* const AValue);
	virtual Fmx::Addressbook::Types::TContactSocialProfiles* __fastcall GetSocialProfiles(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetSocialProfiles(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactSocialProfiles* const AValue);
	virtual Fmx::Addressbook::Types::TContactPhones* __fastcall GetPhones(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetPhones(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactPhones* const AValue);
	virtual Fmx::Addressbook::Types::TContactEmails* __fastcall GetEmails(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetEmails(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactEmails* const AValue);
	virtual Fmx::Addressbook::Types::TContactRelatedNames* __fastcall GetRelatedNames(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetRelatedNames(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactRelatedNames* const AValue);
	virtual Fmx::Addressbook::Types::TContactURLs* __fastcall GetURLs(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetURLs(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactURLs* const AValue);
	virtual Fmx::Addressbook::TAddressBookSource* __fastcall GetSource();
	virtual int __fastcall GetID();
	virtual Fmx::Addressbook::Types::TContactKind __fastcall GetContactKind();
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall TiOSAddressBookContact(TiOSAddressBook* const AAddressBook, Fmx::Addressbook::TAddressBookSource* const ASource);
	__fastcall TiOSAddressBookContact(TiOSAddressBook* const AAddressBook, const void * APersonRef);
	__fastcall virtual ~TiOSAddressBookContact();
	virtual void __fastcall AllGroups(Fmx::Addressbook::TAddressBookGroups* &AGroups);
	__property void * PersonRef = {read=FPersonRef};
public:
	/* TAddressBookContact.Create */ inline __fastcall TiOSAddressBookContact() : Fmx::Addressbook::TAddressBookContact() { }
	
};


class PASCALIMPLEMENTATION TiOSAddressBookHelpers : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static Fmx::Addressbook::Types::TContactPhone::TLabelKind __fastcall LabelToPhoneKind(const CFStringRef AKind);
	static CFStringRef __fastcall PhoneKindToLabel(Fmx::Addressbook::Types::TContactPhone* const APhone);
	static Fmx::Addressbook::Types::TContactEmail::TLabelKind __fastcall LabelToEmailKind(const CFStringRef AKind);
	static CFStringRef __fastcall EmailKindToLabel(Fmx::Addressbook::Types::TContactEmail* const AEmail);
	static Fmx::Addressbook::Types::TContactRelatedName::TLabelKind __fastcall LabelToRelationShipKind(const CFStringRef AKind);
	static CFStringRef __fastcall RelationShipKindToLabel(Fmx::Addressbook::Types::TContactRelatedName* const ARelationship);
	static Fmx::Addressbook::Types::TContactURL::TLabelKind __fastcall LabelToURLKind(const CFStringRef AKind);
	static CFStringRef __fastcall URLKindToLabel(Fmx::Addressbook::Types::TContactURL* const AUrl);
	static Fmx::Addressbook::Types::TContactDate::TLabelKind __fastcall LabelToDateKind(const CFStringRef AKind);
	static CFStringRef __fastcall DateKindToLabel(Fmx::Addressbook::Types::TContactDate* const ADate);
	static Fmx::Addressbook::Types::TContactAddress::TLabelKind __fastcall LabelToAddressKind(const CFStringRef AKind);
	static CFStringRef __fastcall AddressKindToLabel(Fmx::Addressbook::Types::TContactAddress* const AAddress);
	static Fmx::Addressbook::Types::TContactMessagingService::TLabelKind __fastcall LabelToMessagingServiceLabelKind(const CFStringRef AKind);
	static CFStringRef __fastcall MessagingServiceLabelKindToLabel(Fmx::Addressbook::Types::TContactMessagingService* const AProfile);
	static Fmx::Addressbook::Types::TContactMessagingService::TServiceKind __fastcall LabelToMessagingServiceKind(const System::UnicodeString AKind);
	static CFStringRef __fastcall MessagingServiceKindToLabel(Fmx::Addressbook::Types::TContactMessagingService* const AProfile);
	static Fmx::Addressbook::Types::TContactSocialProfile::TLabelKind __fastcall LabelToSocialProfileKind(const CFStringRef AKind);
	static CFStringRef __fastcall SocialProfileKindToLabel(Fmx::Addressbook::Types::TContactSocialProfile* const AProfile);
	static Fmx::Addressbook::Types::TContactSocialProfile::TServiceKind __fastcall LabelToSocialProfileServiceKind(const System::UnicodeString AKind);
	static CFStringRef __fastcall SocialProfileServiceKindToLabel(Fmx::Addressbook::Types::TContactSocialProfile* const AProfile);
public:
	/* TObject.Create */ inline __fastcall TiOSAddressBookHelpers() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TiOSAddressBookHelpers() { }
	
};


class PASCALIMPLEMENTATION TiOSAddressBookServices : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	Fmx::Addressbook::_di_IFMXAddressBookService __fastcall CreateAddressBook();
	Fmx::Addressbook::Types::TContactAddress::TLabelKinds __fastcall AddressesLabelKinds();
	Fmx::Addressbook::Types::TContactSocialProfile::TLabelKinds __fastcall SocialProfilesLabelKinds();
	Fmx::Addressbook::Types::TContactSocialProfile::TServiceKinds __fastcall SocialProfilesServiceKinds();
	Fmx::Addressbook::Types::TContactMessagingService::TLabelKinds __fastcall MessagingServicesLabelKinds();
	Fmx::Addressbook::Types::TContactMessagingService::TServiceKinds __fastcall MessagingServicesKinds();
	Fmx::Addressbook::Types::TContactDate::TLabelKinds __fastcall DatesLabelKinds();
	Fmx::Addressbook::Types::TContactPhone::TLabelKinds __fastcall PhonesLabelKinds();
	Fmx::Addressbook::Types::TContactEmail::TLabelKinds __fastcall EmailsLabelKinds();
	Fmx::Addressbook::Types::TContactRelatedName::TLabelKinds __fastcall RelatedNamesLabelKinds();
	Fmx::Addressbook::Types::TContactURL::TLabelKinds __fastcall URLsLabelKinds();
public:
	/* TObject.Create */ inline __fastcall TiOSAddressBookServices() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TiOSAddressBookServices() { }
	
private:
	void *__IFMXAddressBookSupportedLabelKinds;	// Fmx::Addressbook::Types::IFMXAddressBookSupportedLabelKinds 
	void *__IFMXAddressBookFactory;	// Fmx::Addressbook::IFMXAddressBookFactory 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {842B17FF-8059-4904-A8BF-AD520B4FC0A5}
	operator Fmx::Addressbook::Types::_di_IFMXAddressBookSupportedLabelKinds()
	{
		Fmx::Addressbook::Types::_di_IFMXAddressBookSupportedLabelKinds intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Addressbook::Types::IFMXAddressBookSupportedLabelKinds*(void) { return (Fmx::Addressbook::Types::IFMXAddressBookSupportedLabelKinds*)&__IFMXAddressBookSupportedLabelKinds; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1FA4587B-9C13-42FE-B251-CBD9D8AC5D68}
	operator Fmx::Addressbook::_di_IFMXAddressBookFactory()
	{
		Fmx::Addressbook::_di_IFMXAddressBookFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Addressbook::IFMXAddressBookFactory*(void) { return (Fmx::Addressbook::IFMXAddressBookFactory*)&__IFMXAddressBookFactory; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterService(void);
}	/* namespace Ios */
}	/* namespace Addressbook */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ADDRESSBOOK_IOS)
using namespace Fmx::Addressbook::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ADDRESSBOOK)
using namespace Fmx::Addressbook;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Addressbook_IosHPP
