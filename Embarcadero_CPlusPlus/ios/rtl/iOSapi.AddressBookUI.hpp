// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.AddressBookUI.pas' rev: 34.00 (iOS)

#ifndef Iosapi_AddressbookuiHPP
#define Iosapi_AddressbookuiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.AddressBook.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.UIKit.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Addressbookui
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE ABNewPersonViewControllerClass;
typedef System::DelphiInterface<ABNewPersonViewControllerClass> _di_ABNewPersonViewControllerClass;
__interface DELPHIINTERFACE ABNewPersonViewController;
typedef System::DelphiInterface<ABNewPersonViewController> _di_ABNewPersonViewController;
class DELPHICLASS TABNewPersonViewController;
__interface DELPHIINTERFACE ABPeoplePickerNavigationControllerClass;
typedef System::DelphiInterface<ABPeoplePickerNavigationControllerClass> _di_ABPeoplePickerNavigationControllerClass;
__interface DELPHIINTERFACE ABPeoplePickerNavigationController;
typedef System::DelphiInterface<ABPeoplePickerNavigationController> _di_ABPeoplePickerNavigationController;
class DELPHICLASS TABPeoplePickerNavigationController;
__interface DELPHIINTERFACE ABPersonViewControllerClass;
typedef System::DelphiInterface<ABPersonViewControllerClass> _di_ABPersonViewControllerClass;
__interface DELPHIINTERFACE ABPersonViewController;
typedef System::DelphiInterface<ABPersonViewController> _di_ABPersonViewController;
class DELPHICLASS TABPersonViewController;
__interface DELPHIINTERFACE ABUnknownPersonViewControllerClass;
typedef System::DelphiInterface<ABUnknownPersonViewControllerClass> _di_ABUnknownPersonViewControllerClass;
__interface DELPHIINTERFACE ABUnknownPersonViewController;
typedef System::DelphiInterface<ABUnknownPersonViewController> _di_ABUnknownPersonViewController;
class DELPHICLASS TABUnknownPersonViewController;
__interface DELPHIINTERFACE ABNewPersonViewControllerDelegate;
typedef System::DelphiInterface<ABNewPersonViewControllerDelegate> _di_ABNewPersonViewControllerDelegate;
__interface DELPHIINTERFACE ABPeoplePickerNavigationControllerDelegate;
typedef System::DelphiInterface<ABPeoplePickerNavigationControllerDelegate> _di_ABPeoplePickerNavigationControllerDelegate;
__interface DELPHIINTERFACE ABPersonViewControllerDelegate;
typedef System::DelphiInterface<ABPersonViewControllerDelegate> _di_ABPersonViewControllerDelegate;
__interface DELPHIINTERFACE ABUnknownPersonViewControllerDelegate;
typedef System::DelphiInterface<ABUnknownPersonViewControllerDelegate> _di_ABUnknownPersonViewControllerDelegate;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{02C71C6E-D0C6-4A74-AF14-9557C13AA2B0}") ABNewPersonViewControllerClass  : public Iosapi::Uikit::UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{CE26CA3D-3E36-4C97-92DF-6552B70C500D}") ABNewPersonViewController  : public Iosapi::Uikit::UIViewController 
{
	virtual void __cdecl setNewPersonViewDelegate(void * newPersonViewDelegate) = 0 ;
	virtual void * __cdecl newPersonViewDelegate() = 0 ;
	virtual void __cdecl setAddressBook(void * AddressBook) = 0 ;
	virtual void * __cdecl AddressBook() = 0 ;
	virtual void __cdecl setDisplayedPerson(void * displayedPerson) = 0 ;
	virtual void * __cdecl displayedPerson() = 0 ;
	virtual void __cdecl setParentGroup(void * parentGroup) = 0 ;
	virtual void * __cdecl parentGroup() = 0 ;
};

class PASCALIMPLEMENTATION TABNewPersonViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_ABNewPersonViewControllerClass,_di_ABNewPersonViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_ABNewPersonViewControllerClass,_di_ABNewPersonViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TABNewPersonViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_ABNewPersonViewControllerClass,_di_ABNewPersonViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TABNewPersonViewController() { }
	
};


typedef void * PABNewPersonViewController;

__interface  INTERFACE_UUID("{A8111585-06C6-48C2-A4DF-0F7B8D250926}") ABPeoplePickerNavigationControllerClass  : public Iosapi::Uikit::UINavigationControllerClass 
{
	
};

__interface  INTERFACE_UUID("{BB49D6AD-74D0-43FE-9D5D-E6049069CBE1}") ABPeoplePickerNavigationController  : public Iosapi::Uikit::UINavigationController 
{
	virtual void __cdecl setPeoplePickerDelegate(void * peoplePickerDelegate) = 0 ;
	virtual void * __cdecl peoplePickerDelegate() = 0 ;
	virtual void __cdecl setDisplayedProperties(Iosapi::Foundation::_di_NSArray displayedProperties) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl displayedProperties() = 0 ;
	virtual void __cdecl setAddressBook(void * AddressBook) = 0 ;
	virtual void * __cdecl AddressBook() = 0 ;
	virtual void __cdecl setPredicateForEnablingPerson(Iosapi::Foundation::_di_NSPredicate predicateForEnablingPerson) = 0 ;
	virtual Iosapi::Foundation::_di_NSPredicate __cdecl predicateForEnablingPerson() = 0 ;
	virtual void __cdecl setPredicateForSelectionOfPerson(Iosapi::Foundation::_di_NSPredicate predicateForSelectionOfPerson) = 0 ;
	virtual Iosapi::Foundation::_di_NSPredicate __cdecl predicateForSelectionOfPerson() = 0 ;
	virtual void __cdecl setPredicateForSelectionOfProperty(Iosapi::Foundation::_di_NSPredicate predicateForSelectionOfProperty) = 0 ;
	virtual Iosapi::Foundation::_di_NSPredicate __cdecl predicateForSelectionOfProperty() = 0 ;
};

class PASCALIMPLEMENTATION TABPeoplePickerNavigationController : public Macapi::Objectivec::TOCGenericImport__2<_di_ABPeoplePickerNavigationControllerClass,_di_ABPeoplePickerNavigationController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_ABPeoplePickerNavigationControllerClass,_di_ABPeoplePickerNavigationController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TABPeoplePickerNavigationController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_ABPeoplePickerNavigationControllerClass,_di_ABPeoplePickerNavigationController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TABPeoplePickerNavigationController() { }
	
};


typedef void * PABPeoplePickerNavigationController;

__interface  INTERFACE_UUID("{5E3F3847-4255-4B49-9915-9800A35AC0AC}") ABPersonViewControllerClass  : public Iosapi::Uikit::UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{F9F2B898-67CC-4064-A041-D78F93A5EA8D}") ABPersonViewController  : public Iosapi::Uikit::UIViewController 
{
	virtual void __cdecl setPersonViewDelegate(void * personViewDelegate) = 0 ;
	virtual void * __cdecl personViewDelegate() = 0 ;
	virtual void __cdecl setAddressBook(void * AddressBook) = 0 ;
	virtual void * __cdecl AddressBook() = 0 ;
	virtual void __cdecl setDisplayedPerson(void * displayedPerson) = 0 ;
	virtual void * __cdecl displayedPerson() = 0 ;
	virtual void __cdecl setDisplayedProperties(Iosapi::Foundation::_di_NSArray displayedProperties) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl displayedProperties() = 0 ;
	virtual void __cdecl setAllowsEditing(bool allowsEditing) = 0 ;
	virtual bool __cdecl allowsEditing() = 0 ;
	virtual void __cdecl setAllowsActions(bool allowsActions) = 0 ;
	virtual bool __cdecl allowsActions() = 0 ;
	virtual void __cdecl setShouldShowLinkedPeople(bool shouldShowLinkedPeople) = 0 ;
	virtual bool __cdecl shouldShowLinkedPeople() = 0 ;
	virtual void __cdecl setHighlightedItemForProperty(int property, int withIdentifier) = 0 ;
};

class PASCALIMPLEMENTATION TABPersonViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_ABPersonViewControllerClass,_di_ABPersonViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_ABPersonViewControllerClass,_di_ABPersonViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TABPersonViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_ABPersonViewControllerClass,_di_ABPersonViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TABPersonViewController() { }
	
};


typedef void * PABPersonViewController;

__interface  INTERFACE_UUID("{433E83A3-2B2D-4314-9773-09DA5C28CC29}") ABUnknownPersonViewControllerClass  : public Iosapi::Uikit::UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{59007037-C81A-4FFC-A664-57D0499DC482}") ABUnknownPersonViewController  : public Iosapi::Uikit::UIViewController 
{
	virtual void __cdecl setUnknownPersonViewDelegate(void * unknownPersonViewDelegate) = 0 ;
	virtual void * __cdecl unknownPersonViewDelegate() = 0 ;
	virtual void __cdecl setAddressBook(void * AddressBook) = 0 ;
	virtual void * __cdecl AddressBook() = 0 ;
	virtual void __cdecl setDisplayedPerson(void * displayedPerson) = 0 ;
	virtual void * __cdecl displayedPerson() = 0 ;
	virtual void __cdecl setAlternateName(Iosapi::Foundation::_di_NSString alternateName) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl alternateName() = 0 ;
	virtual void __cdecl setMessage(Iosapi::Foundation::_di_NSString message) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl message() = 0 ;
	virtual void __cdecl setAllowsActions(bool allowsActions) = 0 ;
	virtual bool __cdecl allowsActions() = 0 ;
	virtual void __cdecl setAllowsAddingToAddressBook(bool allowsAddingToAddressBook) = 0 ;
	virtual bool __cdecl allowsAddingToAddressBook() = 0 ;
};

class PASCALIMPLEMENTATION TABUnknownPersonViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_ABUnknownPersonViewControllerClass,_di_ABUnknownPersonViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_ABUnknownPersonViewControllerClass,_di_ABUnknownPersonViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TABUnknownPersonViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_ABUnknownPersonViewControllerClass,_di_ABUnknownPersonViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TABUnknownPersonViewController() { }
	
};


typedef void * PABUnknownPersonViewController;

__interface  INTERFACE_UUID("{94FAFEC4-530D-4BA3-939D-D93F9A1C5D95}") ABNewPersonViewControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl newPersonViewController(_di_ABNewPersonViewController newPersonView, void * didCompleteWithNewPerson) = 0 ;
};

__interface  INTERFACE_UUID("{2D9E85E3-3477-4E10-86D4-2A6ED47CC84D}") ABPeoplePickerNavigationControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl peoplePickerNavigationControllerDidSelectPerson(_di_ABPeoplePickerNavigationController peoplePicker, void * didSelectPerson) = 0 ;
	virtual void __cdecl peoplePickerNavigationControllerDidSelectPersonPropertyIdentifier(_di_ABPeoplePickerNavigationController peoplePicker, void * didSelectPerson, int property, int identifier) = 0 ;
	virtual void __cdecl peoplePickerNavigationControllerDidCancel(_di_ABPeoplePickerNavigationController peoplePicker) = 0 ;
	virtual bool __cdecl peoplePickerNavigationControllerShouldContinueAfterSelectingPerson(_di_ABPeoplePickerNavigationController peoplePicker, void * shouldContinueAfterSelectingPerson) = 0 ;
	virtual bool __cdecl peoplePickerNavigationControllerShouldContinueAfterSelectingPersonPropertyIdentifier(_di_ABPeoplePickerNavigationController peoplePicker, void * shouldContinueAfterSelectingPerson, int property, int identifier) = 0 ;
};

__interface  INTERFACE_UUID("{DF6DC352-6DB0-4610-8916-34B7AE1FD9BE}") ABPersonViewControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl personViewController(_di_ABPersonViewController personViewController, void * shouldPerformDefaultActionForPerson, int property, int identifier) = 0 ;
};

__interface  INTERFACE_UUID("{53B8F74F-433E-4074-9F0C-F6C786E2D4AD}") ABUnknownPersonViewControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl unknownPersonViewControllerDidResolveToPerson(_di_ABUnknownPersonViewController unknownCardViewController, void * didResolveToPerson) = 0 ;
	virtual bool __cdecl unknownPersonViewControllerShouldPerformDefaultActionForPersonPropertyIdentifier(_di_ABUnknownPersonViewController personViewController, void * shouldPerformDefaultActionForPerson, int property, int identifier) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
#define libAddressBookUI u"/System/Library/Frameworks/AddressBookUI.framework/Address"\
	u"BookUI"
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonNamePrefixProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonGivenNameProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonMiddleNameProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonFamilyNameProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonNameSuffixProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonPreviousFamilyNameProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonNicknameProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonPhoneticGivenNameProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonPhoneticMiddleNameProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonPhoneticFamilyNameProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonOrganizationNameProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonDepartmentNameProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonJobTitleProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonBirthdayProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonNoteProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonPhoneNumbersProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonEmailAddressesProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonUrlAddressesProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonDatesProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonInstantMessageAddressesProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonRelatedNamesProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonSocialProfilesProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall ABPersonPostalAddressesProperty(void);
}	/* namespace Addressbookui */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_ADDRESSBOOKUI)
using namespace Iosapi::Addressbookui;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_AddressbookuiHPP
