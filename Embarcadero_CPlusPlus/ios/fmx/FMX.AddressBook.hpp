// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.AddressBook.pas' rev: 34.00 (iOS)

#ifndef Fmx_AddressbookHPP
#define Fmx_AddressbookHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Classes.hpp>
#include <System.Permissions.hpp>
#include <FMX.AddressBook.Types.hpp>
#include <FMX.Surfaces.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Addressbook
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomAddressBook;
class DELPHICLASS TAddressBook;
class DELPHICLASS TAddressBookSource;
class DELPHICLASS TAddressBookSources;
class DELPHICLASS TAddressBookGroup;
class DELPHICLASS TAddressBookGroups;
class DELPHICLASS TAddressBookContact;
class DELPHICLASS TAddressBookContacts;
__interface DELPHIINTERFACE IFMXAddressBookService;
typedef System::DelphiInterface<IFMXAddressBookService> _di_IFMXAddressBookService;
__interface DELPHIINTERFACE IFMXAddressBookFactory;
typedef System::DelphiInterface<IFMXAddressBookFactory> _di_IFMXAddressBookFactory;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomAddressBook : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	_di_IFMXAddressBookService FService;
	System::StaticArray<Fmx::Addressbook::Types::TAuthorizationStatus, 2> FAuthorizationStatus;
	Fmx::Addressbook::Types::TExternalChangeEvent FOnExternalChange;
	Fmx::Addressbook::Types::TPermissionRequestEvent FOnPermissionRequest;
	void __fastcall CheckAuthorization(const Fmx::Addressbook::Types::TAddressBookAccessType AAccessType);
	Fmx::Addressbook::Types::TExternalChangeEvent __fastcall GetOnExternalChange();
	Fmx::Addressbook::Types::TPermissionRequestEvent __fastcall GetOnPermissionRequest();
	void __fastcall SetOnExternalChange(const Fmx::Addressbook::Types::TExternalChangeEvent AValue);
	void __fastcall SetOnPermissionRequest(const Fmx::Addressbook::Types::TPermissionRequestEvent AValue);
	
protected:
	__property _di_IFMXAddressBookService Service = {read=FService};
	
public:
	__fastcall virtual TCustomAddressBook(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomAddressBook();
	bool __fastcall Supported();
	void __fastcall RevertCurrentChangesAndUpdate();
	void __fastcall AllSources(TAddressBookSources* &ASources);
	TAddressBookSource* __fastcall SourceByID(const System::UnicodeString AID);
	TAddressBookSource* __fastcall DefaultSource();
	void __fastcall RequestPermission(System::Permissions::TDisplayRationaleEvent ADisplayRationaleEvent = 0x0)/* overload */;
	Fmx::Addressbook::Types::TAuthorizationStatus __fastcall AuthorizationStatus(const Fmx::Addressbook::Types::TAddressBookAccessType AAccessType);
	void __fastcall AllGroups(TAddressBookGroups* &AGroups)/* overload */;
	void __fastcall AllGroups(TAddressBookSource* const ASource, TAddressBookGroups* &AGroups)/* overload */;
	TAddressBookGroup* __fastcall GroupByID(const int AID);
	TAddressBookGroup* __fastcall CreateGroup(TAddressBookSource* const ASource = (TAddressBookSource*)(0x0));
	void __fastcall SaveGroup(TAddressBookGroup* const AGroup);
	void __fastcall RemoveGroup(TAddressBookGroup* const AGroup)/* overload */;
	void __fastcall RemoveGroup(const int AID)/* overload */;
	void __fastcall AddContactIntoGroup(TAddressBookGroup* const AGroup, TAddressBookContact* const AContact);
	void __fastcall RemoveContactFromGroup(TAddressBookGroup* const AGroup, TAddressBookContact* const AContact);
	void __fastcall AllContacts(TAddressBookContacts* &AContacts)/* overload */;
	void __fastcall AllContacts(TAddressBookSource* const ASource, TAddressBookContacts* &AContacts)/* overload */;
	void __fastcall AllContactsInGroups(TAddressBookGroups* const AGroups, TAddressBookContacts* &AContacts);
	void __fastcall AllContactsInGroup(TAddressBookGroup* const AGroup, TAddressBookContacts* &AContacts);
	TAddressBookContact* __fastcall ContactByID(const int AID);
	TAddressBookContact* __fastcall CreateContact(TAddressBookSource* const ASource = (TAddressBookSource*)(0x0));
	void __fastcall SaveContact(TAddressBookContact* const AContact);
	void __fastcall RemoveContact(TAddressBookContact* const AContact)/* overload */;
	void __fastcall RemoveContact(const int AID)/* overload */;
	__property Fmx::Addressbook::Types::TPermissionRequestEvent OnPermissionRequest = {read=GetOnPermissionRequest, write=SetOnPermissionRequest};
	__property Fmx::Addressbook::Types::TExternalChangeEvent OnExternalChange = {read=GetOnExternalChange, write=SetOnExternalChange};
};


class PASCALIMPLEMENTATION TAddressBook : public TCustomAddressBook
{
	typedef TCustomAddressBook inherited;
	
__published:
	__property OnPermissionRequest;
	__property OnExternalChange;
public:
	/* TCustomAddressBook.Create */ inline __fastcall virtual TAddressBook(System::Classes::TComponent* AOwner) : TCustomAddressBook(AOwner) { }
	/* TCustomAddressBook.Destroy */ inline __fastcall virtual ~TAddressBook() { }
	
};


class PASCALIMPLEMENTATION TAddressBookSource : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetID() = 0 ;
	virtual System::UnicodeString __fastcall GetSourceName() = 0 ;
	virtual System::UnicodeString __fastcall GetSourceType() = 0 ;
	
public:
	__fastcall TAddressBookSource();
	__property System::UnicodeString ID = {read=GetID};
	__property System::UnicodeString SourceName = {read=GetSourceName};
	__property System::UnicodeString SourceType = {read=GetSourceType};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAddressBookSource() { }
	
};


class PASCALIMPLEMENTATION TAddressBookSources : public System::Generics::Collections::TList__1<TAddressBookSource*>
{
	typedef System::Generics::Collections::TList__1<TAddressBookSource*> inherited;
	
public:
	/* {System_Generics_Collections}TList<FMX_AddressBook_TAddressBookSource>.Create */ inline __fastcall TAddressBookSources()/* overload */ : System::Generics::Collections::TList__1<TAddressBookSource*>() { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_TAddressBookSource>.Create */ inline __fastcall TAddressBookSources(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TAddressBookSource*> > AComparer)/* overload */ : System::Generics::Collections::TList__1<TAddressBookSource*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_TAddressBookSource>.Create */ inline __fastcall TAddressBookSources(System::Generics::Collections::TEnumerable__1<TAddressBookSource*>* const Collection)/* overload */ : System::Generics::Collections::TList__1<TAddressBookSource*>(Collection) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_TAddressBookSource>.Destroy */ inline __fastcall virtual ~TAddressBookSources() { }
	
};


class PASCALIMPLEMENTATION TAddressBookGroup : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetName() = 0 ;
	virtual void __fastcall SetName(const System::UnicodeString Value) = 0 ;
	virtual int __fastcall GetID() = 0 ;
	virtual TAddressBookSource* __fastcall GetSource() = 0 ;
	
public:
	__fastcall TAddressBookGroup();
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property int ID = {read=GetID, nodefault};
	__property TAddressBookSource* Source = {read=GetSource};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAddressBookGroup() { }
	
};


class PASCALIMPLEMENTATION TAddressBookGroups : public System::Generics::Collections::TList__1<TAddressBookGroup*>
{
	typedef System::Generics::Collections::TList__1<TAddressBookGroup*> inherited;
	
public:
	/* {System_Generics_Collections}TList<FMX_AddressBook_TAddressBookGroup>.Create */ inline __fastcall TAddressBookGroups()/* overload */ : System::Generics::Collections::TList__1<TAddressBookGroup*>() { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_TAddressBookGroup>.Create */ inline __fastcall TAddressBookGroups(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TAddressBookGroup*> > AComparer)/* overload */ : System::Generics::Collections::TList__1<TAddressBookGroup*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_TAddressBookGroup>.Create */ inline __fastcall TAddressBookGroups(System::Generics::Collections::TEnumerable__1<TAddressBookGroup*>* const Collection)/* overload */ : System::Generics::Collections::TList__1<TAddressBookGroup*>(Collection) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_TAddressBookGroup>.Destroy */ inline __fastcall virtual ~TAddressBookGroups() { }
	
};


class PASCALIMPLEMENTATION TAddressBookContact : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetStringValue(const Fmx::Addressbook::Types::TContactField AIndex) = 0 ;
	virtual void __fastcall SetStringValue(const Fmx::Addressbook::Types::TContactField AIndex, const System::UnicodeString AValue) = 0 ;
	virtual Fmx::Surfaces::TBitmapSurface* __fastcall GetBitmapValue(const Fmx::Addressbook::Types::TContactField AIndex) = 0 ;
	virtual void __fastcall SetBitmapValue(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Surfaces::TBitmapSurface* const AValue) = 0 ;
	virtual System::TDateTime __fastcall GetDateTimeValue(const Fmx::Addressbook::Types::TContactField AIndex) = 0 ;
	virtual void __fastcall SetDateTimeValue(const Fmx::Addressbook::Types::TContactField AIndex, const System::TDateTime AValue) = 0 ;
	virtual Fmx::Addressbook::Types::TContactDates* __fastcall GetDates(const Fmx::Addressbook::Types::TContactField AIndex) = 0 ;
	virtual void __fastcall SetDates(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactDates* const AValue) = 0 ;
	virtual Fmx::Addressbook::Types::TContactAddresses* __fastcall GetAddresses(const Fmx::Addressbook::Types::TContactField AIndex) = 0 ;
	virtual void __fastcall SetAddresses(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactAddresses* const AValue) = 0 ;
	virtual Fmx::Addressbook::Types::TContactMessagingServices* __fastcall GetMessagingServices(const Fmx::Addressbook::Types::TContactField AIndex) = 0 ;
	virtual void __fastcall SetMessagingServices(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactMessagingServices* const AValue) = 0 ;
	virtual Fmx::Addressbook::Types::TContactSocialProfiles* __fastcall GetSocialProfiles(const Fmx::Addressbook::Types::TContactField AIndex) = 0 ;
	virtual void __fastcall SetSocialProfiles(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactSocialProfiles* const AValue) = 0 ;
	virtual Fmx::Addressbook::Types::TContactPhones* __fastcall GetPhones(const Fmx::Addressbook::Types::TContactField Index) = 0 ;
	virtual void __fastcall SetPhones(const Fmx::Addressbook::Types::TContactField Index, Fmx::Addressbook::Types::TContactPhones* const Value) = 0 ;
	virtual Fmx::Addressbook::Types::TContactEmails* __fastcall GetEmails(const Fmx::Addressbook::Types::TContactField AIndex) = 0 ;
	virtual void __fastcall SetEmails(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactEmails* const AValue) = 0 ;
	virtual Fmx::Addressbook::Types::TContactRelatedNames* __fastcall GetRelatedNames(const Fmx::Addressbook::Types::TContactField AIndex) = 0 ;
	virtual void __fastcall SetRelatedNames(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactRelatedNames* const AValue) = 0 ;
	virtual Fmx::Addressbook::Types::TContactURLs* __fastcall GetURLs(const Fmx::Addressbook::Types::TContactField AIndex) = 0 ;
	virtual void __fastcall SetURLs(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactURLs* const AValue) = 0 ;
	virtual TAddressBookSource* __fastcall GetSource() = 0 ;
	virtual Fmx::Addressbook::Types::TContactKind __fastcall GetContactKind() = 0 ;
	virtual System::UnicodeString __fastcall GetDisplayName() = 0 ;
	virtual int __fastcall GetID() = 0 ;
	
public:
	__fastcall TAddressBookContact();
	__property int ID = {read=GetID, nodefault};
	__property Fmx::Addressbook::Types::TContactKind Kind = {read=GetContactKind, nodefault};
	__property TAddressBookSource* Source = {read=GetSource};
	virtual void __fastcall AllGroups(TAddressBookGroups* &AGroups) = 0 ;
	__property System::UnicodeString DisplayName = {read=GetDisplayName};
	__property System::UnicodeString FirstName = {read=GetStringValue, write=SetStringValue, index=0};
	__property System::UnicodeString LastName = {read=GetStringValue, write=SetStringValue, index=1};
	__property System::UnicodeString MiddleName = {read=GetStringValue, write=SetStringValue, index=2};
	__property System::UnicodeString Prefix = {read=GetStringValue, write=SetStringValue, index=3};
	__property System::UnicodeString Suffix = {read=GetStringValue, write=SetStringValue, index=4};
	__property System::UnicodeString NickName = {read=GetStringValue, write=SetStringValue, index=5};
	__property System::UnicodeString FirstNamePhonetic = {read=GetStringValue, write=SetStringValue, index=6};
	__property System::UnicodeString LastNamePhonetic = {read=GetStringValue, write=SetStringValue, index=7};
	__property System::UnicodeString MiddleNamePhonetic = {read=GetStringValue, write=SetStringValue, index=8};
	__property System::UnicodeString Organization = {read=GetStringValue, write=SetStringValue, index=9};
	__property System::UnicodeString JobTitle = {read=GetStringValue, write=SetStringValue, index=10};
	__property System::UnicodeString Department = {read=GetStringValue, write=SetStringValue, index=11};
	__property Fmx::Surfaces::TBitmapSurface* Photo = {read=GetBitmapValue, write=SetBitmapValue, index=12};
	__property Fmx::Surfaces::TBitmapSurface* PhotoThumbnail = {read=GetBitmapValue, index=13};
	__property Fmx::Addressbook::Types::TContactEmails* EMails = {read=GetEmails, write=SetEmails, index=16};
	__property System::TDateTime Birthday = {read=GetDateTimeValue, write=SetDateTimeValue, index=22};
	__property System::UnicodeString Note = {read=GetStringValue, write=SetStringValue, index=14};
	__property Fmx::Addressbook::Types::TContactDates* Dates = {read=GetDates, write=SetDates, index=19};
	__property System::TDateTime CreationDate = {read=GetDateTimeValue, index=24};
	__property System::TDateTime ModificationDate = {read=GetDateTimeValue, index=25};
	__property Fmx::Addressbook::Types::TContactAddresses* Addresses = {read=GetAddresses, write=SetAddresses, index=17};
	__property Fmx::Addressbook::Types::TContactPhones* Phones = {read=GetPhones, write=SetPhones, index=18};
	__property Fmx::Addressbook::Types::TContactMessagingServices* MessagingServices = {read=GetMessagingServices, write=SetMessagingServices, index=21};
	__property Fmx::Addressbook::Types::TContactSocialProfiles* SocialProfiles = {read=GetSocialProfiles, write=SetSocialProfiles, index=23};
	__property Fmx::Addressbook::Types::TContactRelatedNames* RelatedNames = {read=GetRelatedNames, write=SetRelatedNames, index=20};
	__property Fmx::Addressbook::Types::TContactURLs* URLs = {read=GetURLs, write=SetURLs, index=15};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAddressBookContact() { }
	
};


class PASCALIMPLEMENTATION TAddressBookContacts : public System::Generics::Collections::TObjectList__1<TAddressBookContact*>
{
	typedef System::Generics::Collections::TObjectList__1<TAddressBookContact*> inherited;
	
public:
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_TAddressBookContact>.Create */ inline __fastcall TAddressBookContacts()/* overload */ : System::Generics::Collections::TObjectList__1<TAddressBookContact*>() { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_TAddressBookContact>.Create */ inline __fastcall TAddressBookContacts(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TAddressBookContact*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_TAddressBookContact>.Create */ inline __fastcall TAddressBookContacts(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TAddressBookContact*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TAddressBookContact*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_TAddressBookContact>.Create */ inline __fastcall TAddressBookContacts(System::Generics::Collections::TEnumerable__1<TAddressBookContact*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TAddressBookContact*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_TAddressBookContact>.Destroy */ inline __fastcall virtual ~TAddressBookContacts() { }
	
public:
	/* {System_Generics_Collections}TList<FMX_AddressBook_TAddressBookContact>.Create */ inline __fastcall TAddressBookContacts(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TAddressBookContact*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TAddressBookContact*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_TAddressBookContact>.Create */ inline __fastcall TAddressBookContacts(System::Generics::Collections::TEnumerable__1<TAddressBookContact*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TAddressBookContact*>(Collection) { }
	
};


__interface  INTERFACE_UUID("{C9B83925-6A0E-464D-8CFE-7CD11DB366CA}") IFMXAddressBookService  : public System::IInterface 
{
	virtual void __fastcall RequestPermission(System::Permissions::TDisplayRationaleEvent ADisplayRationaleEvent = 0x0) = 0 ;
	virtual Fmx::Addressbook::Types::TAuthorizationStatus __fastcall AuthorizationStatus(const Fmx::Addressbook::Types::TAddressBookAccessType AAccessType) = 0 ;
	virtual void __fastcall AllSources(TAddressBookSources* &ASources) = 0 ;
	virtual TAddressBookSource* __fastcall SourceByID(const System::UnicodeString AID) = 0 ;
	virtual TAddressBookSource* __fastcall DefaultSource() = 0 ;
	virtual void __fastcall RevertCurrentChangesAndUpdate() = 0 ;
	virtual void __fastcall AllGroups(TAddressBookSource* const ASource, TAddressBookGroups* &AGroups) = 0 ;
	virtual TAddressBookGroup* __fastcall GroupByID(const int AID) = 0 ;
	virtual TAddressBookGroup* __fastcall CreateGroup(TAddressBookSource* const ASource = (TAddressBookSource*)(0x0)) = 0 ;
	virtual void __fastcall SaveGroup(TAddressBookGroup* const AGroup) = 0 ;
	virtual void __fastcall RemoveGroup(TAddressBookGroup* const AGroup) = 0 /* overload */;
	virtual void __fastcall RemoveGroup(const int AID) = 0 /* overload */;
	virtual void __fastcall AddContactIntoGroup(TAddressBookGroup* const AGroup, TAddressBookContact* const AContact) = 0 ;
	virtual void __fastcall RemoveContactFromGroup(TAddressBookGroup* const AGroup, TAddressBookContact* const AContact) = 0 ;
	virtual void __fastcall AllContacts(TAddressBookSource* const ASource, TAddressBookContacts* &AContacts) = 0 ;
	virtual void __fastcall AllContactsInGroups(TAddressBookGroups* const AGroups, TAddressBookContacts* &AContacts) = 0 ;
	virtual TAddressBookContact* __fastcall ContactByID(const int AID) = 0 ;
	virtual TAddressBookContact* __fastcall CreateContact(TAddressBookSource* const ASource = (TAddressBookSource*)(0x0)) = 0 ;
	virtual void __fastcall SaveContact(TAddressBookContact* const AContact) = 0 ;
	virtual void __fastcall RemoveContact(TAddressBookContact* const AContact) = 0 /* overload */;
	virtual void __fastcall RemoveContact(const int AID) = 0 /* overload */;
	virtual Fmx::Addressbook::Types::TPermissionRequestEvent __fastcall GetOnPermissionRequest() = 0 ;
	virtual void __fastcall SetOnPermissionRequest(const Fmx::Addressbook::Types::TPermissionRequestEvent AHandler) = 0 ;
	virtual Fmx::Addressbook::Types::TExternalChangeEvent __fastcall GetOnExternalChange() = 0 ;
	virtual void __fastcall SetOnExternalChange(const Fmx::Addressbook::Types::TExternalChangeEvent AHandler) = 0 ;
	__property Fmx::Addressbook::Types::TPermissionRequestEvent OnPermissionRequest = {read=GetOnPermissionRequest, write=SetOnPermissionRequest};
	__property Fmx::Addressbook::Types::TExternalChangeEvent OnExternalChange = {read=GetOnExternalChange, write=SetOnExternalChange};
};

__interface  INTERFACE_UUID("{1FA4587B-9C13-42FE-B251-CBD9D8AC5D68}") IFMXAddressBookFactory  : public System::IInterface 
{
	virtual _di_IFMXAddressBookService __fastcall CreateAddressBook() = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Addressbook */
}	/* namespace Fmx */
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
#endif	// Fmx_AddressbookHPP
