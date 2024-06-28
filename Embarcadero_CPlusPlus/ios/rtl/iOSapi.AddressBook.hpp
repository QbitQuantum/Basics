// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.AddressBook.pas' rev: 34.00 (iOS)

#ifndef Iosapi_AddressbookHPP
#define Iosapi_AddressbookHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.Foundation.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Addressbook
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef void * ABRecordRef;

typedef int ABRecordID;

typedef int ABPropertyID;

typedef unsigned long ABRecordType;

typedef unsigned long ABPropertyType;

typedef void * ABAddressBookRef;

typedef long ABAuthorizationStatus;

typedef void __fastcall (__closure *ABAddressBookRequestAccessCompletionHandler)(bool param1, CFErrorRef param2);

typedef void __cdecl (*ABExternalChangeCallback)(void * param1, CFDictionaryRef param2, void * param3);

typedef int ABSourceType;

typedef unsigned long ABPersonSortOrdering;

typedef unsigned long ABPersonCompositeNameFormat;

typedef unsigned ABPersonImageFormat;

typedef void * ABMultiValueRef;

typedef int ABMultiValueIdentifier;

typedef void * ABMutableMultiValueRef;

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 kABPersonType = System::Int8(0x0);
static constexpr System::Int8 kABGroupType = System::Int8(0x1);
static constexpr System::Int8 kABSourceType = System::Int8(0x2);
static constexpr System::Int8 kABInvalidPropertyType = System::Int8(0x0);
static constexpr System::Int8 kABStringPropertyType = System::Int8(0x1);
static constexpr System::Int8 kABIntegerPropertyType = System::Int8(0x2);
static constexpr System::Int8 kABRealPropertyType = System::Int8(0x3);
static constexpr System::Int8 kABDateTimePropertyType = System::Int8(0x4);
static constexpr System::Int8 kABDictionaryPropertyType = System::Int8(0x5);
static constexpr System::Word kABMultiStringPropertyType = System::Word(0x101);
static constexpr System::Word kABMultiIntegerPropertyType = System::Word(0x102);
static constexpr System::Word kABMultiRealPropertyType = System::Word(0x103);
static constexpr System::Word kABMultiDateTimePropertyType = System::Word(0x104);
static constexpr System::Word kABMultiDictionaryPropertyType = System::Word(0x105);
static constexpr System::Int8 kABOperationNotPermittedByStoreError = System::Int8(0x0);
static constexpr System::Int8 kABOperationNotPermittedByUserError = System::Int8(0x1);
static constexpr System::Int8 kABAuthorizationStatusNotDetermined = System::Int8(0x0);
static constexpr System::Int8 kABAuthorizationStatusRestricted = System::Int8(0x1);
static constexpr System::Int8 kABAuthorizationStatusDenied = System::Int8(0x2);
static constexpr System::Int8 kABAuthorizationStatusAuthorized = System::Int8(0x3);
static constexpr System::Int8 kABSourceTypeLocal = System::Int8(0x0);
static constexpr System::Int8 kABSourceTypeExchange = System::Int8(0x1);
static constexpr int kABSourceTypeExchangeGAL = int(0x1000001);
static constexpr System::Int8 kABSourceTypeMobileMe = System::Int8(0x2);
static constexpr int kABSourceTypeLDAP = int(0x1000003);
static constexpr System::Int8 kABSourceTypeCardDAV = System::Int8(0x4);
static constexpr int kABSourceTypeCardDAVSearch = int(0x1000004);
static constexpr System::Int8 kABPersonSortByFirstName = System::Int8(0x0);
static constexpr System::Int8 kABPersonSortByLastName = System::Int8(0x1);
static constexpr System::Int8 kABPersonCompositeNameFormatFirstNameFirst = System::Int8(0x0);
static constexpr System::Int8 kABPersonCompositeNameFormatLastNameFirst = System::Int8(0x1);
static constexpr System::Int8 kABPersonImageFormatThumbnail = System::Int8(0x0);
static constexpr System::Int8 kABPersonImageFormatOriginalSize = System::Int8(0x2);
#define libAddressBook u"/System/Library/Frameworks/AddressBook.framework/AddressBo"\
	u"ok"
extern "C" int __cdecl ABRecordGetRecordID(void * record);
extern "C" unsigned long __cdecl ABRecordGetRecordType(void * record);
extern "C" void * __cdecl ABRecordCopyValue(void * record, int property);
extern "C" bool __cdecl ABRecordSetValue(void * record, int property, void * value, CFErrorRef error);
extern "C" int __cdecl ABRecordRemoveValue(void * record, int property, CFErrorRef error);
extern "C" CFStringRef __cdecl ABRecordCopyCompositeName(void * record);
extern "C" long __cdecl ABAddressBookGetAuthorizationStatus(void);
extern "C" void * __cdecl ABAddressBookCreateWithOptions(CFDictionaryRef options, CFErrorRef error);
extern "C" void * __cdecl ABAddressBookCreate(void);
extern "C" void __cdecl ABAddressBookRequestAccessWithCompletion(void * AddressBook, void * completion);
extern "C" bool __cdecl ABAddressBookSave(void * AddressBook, CFErrorRef error);
extern "C" bool __cdecl ABAddressBookHasUnsavedChanges(void * AddressBook);
extern "C" bool __cdecl ABAddressBookAddRecord(void * AddressBook, void * record, CFErrorRef error);
extern "C" bool __cdecl ABAddressBookRemoveRecord(void * AddressBook, void * record, CFErrorRef error);
extern "C" CFStringRef __cdecl ABAddressBookCopyLocalizedLabel(CFStringRef label);
extern "C" void __cdecl ABAddressBookRegisterExternalChangeCallback(void * AddressBook, ABExternalChangeCallback callback, void * context);
extern "C" void __cdecl ABAddressBookUnregisterExternalChangeCallback(void * AddressBook, ABExternalChangeCallback callback, void * context);
extern "C" void __cdecl ABAddressBookRevert(void * AddressBook);
extern "C" void * __cdecl ABAddressBookCopyDefaultSource(void * AddressBook);
extern "C" void * __cdecl ABAddressBookGetSourceWithRecordID(void * AddressBook, int sourceID);
extern "C" CFArrayRef __cdecl ABAddressBookCopyArrayOfAllSources(void * AddressBook);
extern "C" void * __cdecl ABPersonCreate(void);
extern "C" void * __cdecl ABPersonCreateInSource(void * source);
extern "C" void * __cdecl ABPersonCopySource(void * person);
extern "C" CFArrayRef __cdecl ABPersonCopyArrayOfAllLinkedPeople(void * person);
extern "C" unsigned long __cdecl ABPersonGetTypeOfProperty(int property);
extern "C" CFStringRef __cdecl ABPersonCopyLocalizedPropertyName(int property);
extern "C" unsigned long __cdecl ABPersonGetSortOrdering(void);
extern "C" unsigned long __cdecl ABPersonGetCompositeNameFormat(void);
extern "C" unsigned long __cdecl ABPersonGetCompositeNameFormatForRecord(void * record);
extern "C" CFStringRef __cdecl ABPersonCopyCompositeNameDelimiterForRecord(void * record);
extern "C" bool __cdecl ABPersonSetImageData(void * person, CFDataRef imageData, CFErrorRef error);
extern "C" CFDataRef __cdecl ABPersonCopyImageData(void * person);
extern "C" CFDataRef __cdecl ABPersonCopyImageDataWithFormat(void * person, unsigned format);
extern "C" int __cdecl ABPersonHasImageData(void * person);
extern "C" bool __cdecl ABPersonRemoveImageData(void * person, CFErrorRef error);
extern "C" long __cdecl ABPersonComparePeopleByName(void * person1, void * person2, unsigned long ordering);
extern "C" long __cdecl ABAddressBookGetPersonCount(void * AddressBook);
extern "C" void * __cdecl ABAddressBookGetPersonWithRecordID(void * AddressBook, int recordID);
extern "C" CFArrayRef __cdecl ABAddressBookCopyArrayOfAllPeople(void * AddressBook);
extern "C" CFArrayRef __cdecl ABAddressBookCopyArrayOfAllPeopleInSource(void * AddressBook, void * source);
extern "C" CFArrayRef __cdecl ABAddressBookCopyArrayOfAllPeopleInSourceWithSortOrdering(void * AddressBook, void * source, unsigned long sortOrdering);
extern "C" CFArrayRef __cdecl ABAddressBookCopyPeopleWithName(void * AddressBook, CFStringRef name);
extern "C" CFArrayRef __cdecl ABPersonCreatePeopleInSourceWithVCardRepresentation(void * source, CFDataRef vCardData);
extern "C" CFDataRef __cdecl ABPersonCreateVCardRepresentationWithPeople(CFArrayRef people);
extern "C" void * __cdecl ABGroupCreate(void);
extern "C" void * __cdecl ABGroupCreateInSource(void * source);
extern "C" void * __cdecl ABGroupCopySource(void * group);
extern "C" CFArrayRef __cdecl ABGroupCopyArrayOfAllMembers(void * group);
extern "C" CFArrayRef __cdecl ABGroupCopyArrayOfAllMembersWithSortOrdering(void * group, unsigned long sortOrdering);
extern "C" bool __cdecl ABGroupAddMember(void * group, void * person, CFErrorRef error);
extern "C" bool __cdecl ABGroupRemoveMember(void * group, void * member, CFErrorRef error);
extern "C" void * __cdecl ABAddressBookGetGroupWithRecordID(void * AddressBook, int recordID);
extern "C" long __cdecl ABAddressBookGetGroupCount(void * AddressBook);
extern "C" CFArrayRef __cdecl ABAddressBookCopyArrayOfAllGroups(void * AddressBook);
extern "C" CFArrayRef __cdecl ABAddressBookCopyArrayOfAllGroupsInSource(void * AddressBook, void * source);
extern "C" unsigned long __cdecl ABMultiValueGetPropertyType(void * multiValue);
extern "C" long __cdecl ABMultiValueGetCount(void * multiValue);
extern "C" void * __cdecl ABMultiValueCopyValueAtIndex(void * multiValue, long index);
extern "C" CFArrayRef __cdecl ABMultiValueCopyArrayOfAllValues(void * multiValue);
extern "C" CFStringRef __cdecl ABMultiValueCopyLabelAtIndex(void * multiValue, long index);
extern "C" long __cdecl ABMultiValueGetIndexForIdentifier(void * multiValue, int identifier);
extern "C" int __cdecl ABMultiValueGetIdentifierAtIndex(void * multiValue, long index);
extern "C" long __cdecl ABMultiValueGetFirstIndexOfValue(void * multiValue, void * value);
extern "C" void * __cdecl ABMultiValueCreateMutable(unsigned long type);
extern "C" void * __cdecl ABMultiValueCreateMutableCopy(void * multiValue);
extern "C" bool __cdecl ABMultiValueAddValueAndLabel(void * multiValue, void * value, CFStringRef label, int outIdentifier);
extern "C" int __cdecl ABMultiValueInsertValueAndLabelAtIndex(void * multiValue, void * value, CFStringRef label, long index, int outIdentifier);
extern "C" int __cdecl ABMultiValueRemoveValueAndLabelAtIndex(void * multiValue, long index);
extern "C" int __cdecl ABMultiValueReplaceValueAtIndex(void * multiValue, void * value, long index);
extern "C" int __cdecl ABMultiValueReplaceLabelAtIndex(void * multiValue, CFStringRef label, long index);
extern DELPHI_PACKAGE void * __fastcall ABAddressBookErrorDomain(void);
extern DELPHI_PACKAGE int __fastcall kABSourceNameProperty(void);
extern DELPHI_PACKAGE int __fastcall kABSourceTypeProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABWorkLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABHomeLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABOtherLabel(void);
extern DELPHI_PACKAGE int __fastcall kABPersonFirstNameProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonLastNameProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonMiddleNameProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonPrefixProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonSuffixProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonNicknameProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonFirstNamePhoneticProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonLastNamePhoneticProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonMiddleNamePhoneticProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonOrganizationProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonJobTitleProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonDepartmentProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonEmailProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonBirthdayProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonNoteProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonCreationDateProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonModificationDateProperty(void);
extern DELPHI_PACKAGE int __fastcall kABPersonAddressProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAddressStreetKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAddressCityKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAddressStateKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAddressZIPKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAddressCountryKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAddressCountryCodeKey(void);
extern DELPHI_PACKAGE int __fastcall kABPersonDateProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAnniversaryLabel(void);
extern DELPHI_PACKAGE int __fastcall kABPersonKindProperty(void);
extern DELPHI_PACKAGE void * __fastcall kABPersonKindPerson(void);
extern DELPHI_PACKAGE void * __fastcall kABPersonKindOrganization(void);
extern DELPHI_PACKAGE int __fastcall kABPersonPhoneProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonPhoneMobileLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonPhoneIPhoneLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonPhoneMainLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonPhoneHomeFAXLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonPhoneWorkFAXLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonPhoneOtherFAXLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonPhonePagerLabel(void);
extern DELPHI_PACKAGE int __fastcall kABPersonInstantMessageProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageServiceKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageServiceYahoo(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageServiceJabber(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageServiceMSN(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageServiceICQ(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageServiceAIM(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageServiceQQ(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageServiceGoogleTalk(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageServiceSkype(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageServiceFacebook(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageServiceGaduGadu(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonInstantMessageUsernameKey(void);
extern DELPHI_PACKAGE int __fastcall kABPersonURLProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonHomePageLabel(void);
extern DELPHI_PACKAGE int __fastcall kABPersonRelatedNamesProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonFatherLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonMotherLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonParentLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonBrotherLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSisterLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonChildLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonFriendLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSpouseLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonPartnerLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAssistantLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonManagerLabel(void);
extern DELPHI_PACKAGE int __fastcall kABPersonSocialProfileProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSocialProfileURLKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSocialProfileServiceKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSocialProfileUsernameKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSocialProfileUserIdentifierKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSocialProfileServiceTwitter(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSocialProfileServiceSinaWeibo(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSocialProfileServiceGameCenter(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSocialProfileServiceFacebook(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSocialProfileServiceMyspace(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSocialProfileServiceLinkedIn(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonSocialProfileServiceFlickr(void);
extern DELPHI_PACKAGE int __fastcall kABPersonAlternateBirthdayProperty(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAlternateBirthdayCalendarIdentifierKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAlternateBirthdayEraKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAlternateBirthdayYearKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAlternateBirthdayMonthKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAlternateBirthdayIsLeapMonthKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kABPersonAlternateBirthdayDayKey(void);
extern DELPHI_PACKAGE int __fastcall kABGroupNameProperty(void);
}	/* namespace Addressbook */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_ADDRESSBOOK)
using namespace Iosapi::Addressbook;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_AddressbookHPP
