// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.AddressBook.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Addressbook_AndroidHPP
#define Fmx_Addressbook_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Permissions.hpp>
#include <System.Rtti.hpp>
#include <System.Types.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Provider.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.Embarcadero.hpp>
#include <Androidapi.JNI.Net.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.AddressBook.hpp>
#include <FMX.AddressBook.Types.hpp>
#include <FMX.Surfaces.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>
#include <Androidapi.Jni.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Addressbook
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidAddressBook;
class DELPHICLASS TAndroidAddressBookSource;
class DELPHICLASS TAddressBookChangesListener;
class DELPHICLASS TAndroidAddressBookGroup;
class DELPHICLASS TAndroidAddressBookContact;
class DELPHICLASS TOperationBuilderAdapter;
class DELPHICLASS TQueryAdapter;
class DELPHICLASS TAndroidAddressBookHelper;
class DELPHICLASS TAndroidAddressBookServices;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAndroidAddressBook : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Androidapi::Jni::Embarcadero::_di_JAddressBookObserver FObserver;
	TAddressBookChangesListener* FListener;
	bool FProcessing;
	System::TDateTime FRevertTimeStamp;
	Fmx::Addressbook::Types::TExternalChangeEvent FOnExternalChange;
	Fmx::Addressbook::Types::TPermissionRequestEvent FOnPermissionRequest;
	bool __fastcall RecordExists(const Androidapi::Jni::Javatypes::_di_JString AContentType, TAndroidAddressBookContact* const AContact);
	void __fastcall SaveStructureName(Androidapi::Jni::Javatypes::_di_JArrayList &AOperations, TAndroidAddressBookContact* const AContact);
	void __fastcall SaveOrganization(Androidapi::Jni::Javatypes::_di_JArrayList &AOperations, TAndroidAddressBookContact* const AContact);
	void __fastcall SaveNickName(Androidapi::Jni::Javatypes::_di_JArrayList &AOperations, TAndroidAddressBookContact* const AContact);
	void __fastcall SavePhones(Androidapi::Jni::Javatypes::_di_JArrayList &AOperations, TAndroidAddressBookContact* const AContact);
	void __fastcall SaveAddresses(Androidapi::Jni::Javatypes::_di_JArrayList &AOperations, TAndroidAddressBookContact* const AContact);
	void __fastcall SaveDates(Androidapi::Jni::Javatypes::_di_JArrayList &AOperations, TAndroidAddressBookContact* const AContact);
	void __fastcall SaveMessagingServices(Androidapi::Jni::Javatypes::_di_JArrayList &AOperations, TAndroidAddressBookContact* const AContact);
	void __fastcall SavePhoto(Androidapi::Jni::Javatypes::_di_JArrayList &AOperations, TAndroidAddressBookContact* const AContact);
	void __fastcall SaveURLs(Androidapi::Jni::Javatypes::_di_JArrayList &AOperations, TAndroidAddressBookContact* const AContact);
	void __fastcall SaveEmails(Androidapi::Jni::Javatypes::_di_JArrayList &AOperations, TAndroidAddressBookContact* const AContact);
	void __fastcall SaveRelatedNames(Androidapi::Jni::Javatypes::_di_JArrayList &AOperations, TAndroidAddressBookContact* const AContact);
	void __fastcall FetchContacts(Fmx::Addressbook::TAddressBookContacts* &AContacts, const System::UnicodeString AFilter = System::UnicodeString());
	void __fastcall FetchGroups(Fmx::Addressbook::TAddressBookGroups* const AGroups, const System::UnicodeString AFilter = System::UnicodeString());
	void __fastcall OnRequestPermissionsResult(System::TObject* Sender, const System::TArray__1<System::UnicodeString> APermissions, const System::TArray__1<System::Permissions::TPermissionStatus> AGrantResults);
	
protected:
	void __fastcall DoPermissionRequest(const System::UnicodeString AMessage, const bool AAccessGranted);
	void __fastcall InitializeAddressBook();
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
	Fmx::Addressbook::TAddressBookGroup* __fastcall CreateGroup(Fmx::Addressbook::TAddressBookSource* const ASource = (Fmx::Addressbook::TAddressBookSource*)(0x0));
	void __fastcall SaveGroup(Fmx::Addressbook::TAddressBookGroup* const AGroup);
	void __fastcall RemoveGroup(Fmx::Addressbook::TAddressBookGroup* const AGroup)/* overload */;
	void __fastcall RemoveGroup(const int AID)/* overload */;
	void __fastcall AllContactsInGroups(Fmx::Addressbook::TAddressBookGroups* const AGroups, Fmx::Addressbook::TAddressBookContacts* &AContacts);
	void __fastcall AddContactIntoGroup(Fmx::Addressbook::TAddressBookGroup* const AGroup, Fmx::Addressbook::TAddressBookContact* const AContact);
	void __fastcall RemoveContactFromGroup(Fmx::Addressbook::TAddressBookGroup* const AGroup, Fmx::Addressbook::TAddressBookContact* const AContact);
	Fmx::Addressbook::Types::TPermissionRequestEvent __fastcall GetOnPermissionRequest();
	void __fastcall SetOnPermissionRequest(const Fmx::Addressbook::Types::TPermissionRequestEvent AHandler);
	Fmx::Addressbook::Types::TExternalChangeEvent __fastcall GetOnExternalChange();
	void __fastcall SetOnExternalChange(const Fmx::Addressbook::Types::TExternalChangeEvent AHandler);
	
public:
	__fastcall virtual ~TAndroidAddressBook();
	void __fastcall BeginProcessing();
	void __fastcall EndProcessing();
	__property bool Processing = {read=FProcessing, nodefault};
	__property System::TDateTime RevertTimeStamp = {read=FRevertTimeStamp};
public:
	/* TObject.Create */ inline __fastcall TAndroidAddressBook() : System::TInterfacedObject() { }
	
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


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidAddressBookSource : public Fmx::Addressbook::TAddressBookSource
{
	typedef Fmx::Addressbook::TAddressBookSource inherited;
	
private:
	System::UnicodeString FAccountType;
	System::UnicodeString FAccountName;
	
protected:
	virtual System::UnicodeString __fastcall GetID();
	virtual System::UnicodeString __fastcall GetSourceName();
	virtual System::UnicodeString __fastcall GetSourceType();
	
public:
	__fastcall TAndroidAddressBookSource(const System::UnicodeString AAccountName, const System::UnicodeString AAccountType);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAndroidAddressBookSource() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAddressBookChangesListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TAndroidAddressBook* FAddressBook;
	
public:
	__fastcall TAddressBookChangesListener(TAndroidAddressBook* const AAddressBook);
	void __cdecl onChanged(bool selfChange);
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAddressBookChangesListener() { }
	
private:
	void *__JOnAddressBookChangesListener;	// Androidapi::Jni::Embarcadero::JOnAddressBookChangesListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {07FE15E5-7885-430E-B161-2E339965B549}
	operator Androidapi::Jni::Embarcadero::_di_JOnAddressBookChangesListener()
	{
		Androidapi::Jni::Embarcadero::_di_JOnAddressBookChangesListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Embarcadero::JOnAddressBookChangesListener*(void) { return (Androidapi::Jni::Embarcadero::JOnAddressBookChangesListener*)&__JOnAddressBookChangesListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum class DECLSPEC_DENUM TRecordState : unsigned char { Adding, Viewing, Modification };

class PASCALIMPLEMENTATION TAndroidAddressBookGroup : public Fmx::Addressbook::TAddressBookGroup
{
	typedef Fmx::Addressbook::TAddressBookGroup inherited;
	
public:
	static constexpr System::Int8 UndefinedID = System::Int8(-1);
	
	
private:
	TAndroidAddressBook* FAddressBook;
	TRecordState FState;
	__int64 FID;
	System::UnicodeString FName;
	System::TDateTime FNameChangeTimestamp;
	System::UnicodeString FAccountType;
	System::UnicodeString FAccountName;
	void __fastcall SetID(const __int64 AValue);
	
protected:
	virtual void __fastcall SetName(const System::UnicodeString AValue);
	virtual System::UnicodeString __fastcall GetName();
	virtual int __fastcall GetID();
	virtual Fmx::Addressbook::TAddressBookSource* __fastcall GetSource();
	
public:
	__fastcall TAndroidAddressBookGroup(TAndroidAddressBook* const AAddressBook, Fmx::Addressbook::TAddressBookSource* const ASource);
	__fastcall TAndroidAddressBookGroup(TAndroidAddressBook* const AAddressBook, const __int64 AID);
	__property System::UnicodeString AccountType = {read=FAccountType, write=FAccountType};
	__property System::UnicodeString AccountName = {read=FAccountName, write=FAccountName};
	__property __int64 ID = {read=FID, write=SetID};
	__property TRecordState State = {read=FState, nodefault};
public:
	/* TAddressBookGroup.Create */ inline __fastcall TAndroidAddressBookGroup() : Fmx::Addressbook::TAddressBookGroup() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAndroidAddressBookGroup() { }
	
};


typedef System::UnicodeString __fastcall (*TTranslateCallback)(const int AType);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidAddressBookContact : public Fmx::Addressbook::TAddressBookContact
{
	typedef Fmx::Addressbook::TAddressBookContact inherited;
	
	
public:
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TFieldValue
	{
	public:
		System::Rtti::TValue Value;
		System::TDateTime TimeStamp;
		__fastcall TFieldValue(const System::Rtti::TValue &AValue, const System::TDateTime ATimeStamp);
		TFieldValue() {}
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	typedef System::Generics::Collections::TDictionary__2<Fmx::Addressbook::Types::TContactField,TFieldValue>* TContactChanges;
	
	
public:
	static constexpr System::Int8 UndefinedID = System::Int8(-1);
	
	
private:
	TAndroidAddressBook* FAddressBook;
	TRecordState FState;
	int FContactID;
	int FRawContactID;
	System::UnicodeString FAccountType;
	System::UnicodeString FAccountName;
	System::Generics::Collections::TDictionary__2<Fmx::Addressbook::Types::TContactField,TFieldValue>* FListChanges;
	void __fastcall SetContactID(const int Value);
	int __fastcall GetContactID();
	System::UnicodeString __fastcall GetAccountName();
	System::UnicodeString __fastcall GetStringFieldValue(const Androidapi::Jni::Javatypes::_di_JString AFieldName, const Androidapi::Jni::Javatypes::_di_JString AContentType);
	
protected:
	virtual System::UnicodeString __fastcall GetStringValue(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetStringValue(const Fmx::Addressbook::Types::TContactField AIndex, const System::UnicodeString AValue);
	virtual Fmx::Surfaces::TBitmapSurface* __fastcall GetBitmapValue(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetBitmapValue(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Surfaces::TBitmapSurface* const AValue);
	virtual System::TDateTime __fastcall GetDateTimeValue(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetDateTimeValue(const Fmx::Addressbook::Types::TContactField AIndex, const System::TDateTime AValue);
	virtual Fmx::Addressbook::Types::TContactDates* __fastcall GetDates(const Fmx::Addressbook::Types::TContactField AIndex)/* overload */;
	virtual void __fastcall SetDates(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactDates* const AValue);
	virtual Fmx::Addressbook::Types::TContactAddresses* __fastcall GetAddresses(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetAddresses(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactAddresses* const AValue);
	virtual Fmx::Addressbook::Types::TContactSocialProfiles* __fastcall GetSocialProfiles(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetSocialProfiles(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactSocialProfiles* const AValue);
	virtual Fmx::Addressbook::Types::TContactMessagingServices* __fastcall GetMessagingServices(const Fmx::Addressbook::Types::TContactField AIndex);
	virtual void __fastcall SetMessagingServices(const Fmx::Addressbook::Types::TContactField AIndex, Fmx::Addressbook::Types::TContactMessagingServices* const AValue);
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
	HIDESBASE Fmx::Addressbook::Types::TContactDates* __fastcall GetDates()/* overload */;
	
public:
	__fastcall TAndroidAddressBookContact(TAndroidAddressBook* const AAddressBook, Fmx::Addressbook::TAddressBookSource* const ASource)/* overload */;
	__fastcall TAndroidAddressBookContact(TAndroidAddressBook* const AAddressBook, const int AContactID)/* overload */;
	__fastcall virtual ~TAndroidAddressBookContact();
	bool __fastcall HasChanges(const Fmx::Addressbook::Types::TContactField AFieldType);
	bool __fastcall HasAtLeastOneChange(const Fmx::Addressbook::Types::TContactFields AFieldTypes);
	void __fastcall Modified();
	virtual void __fastcall AllGroups(Fmx::Addressbook::TAddressBookGroups* &AGroups);
	__property int ContactID = {read=GetContactID, write=SetContactID, nodefault};
	__property int RawContactID = {read=FRawContactID, write=FRawContactID, nodefault};
	__property System::UnicodeString AccountType = {read=FAccountType, write=FAccountType};
	__property System::UnicodeString AccountName = {read=GetAccountName, write=FAccountName};
	__property TRecordState State = {read=FState, nodefault};
	__property System::Generics::Collections::TDictionary__2<Fmx::Addressbook::Types::TContactField,TFieldValue>* Changes = {read=FListChanges};
public:
	/* TAddressBookContact.Create */ inline __fastcall TAndroidAddressBookContact() : Fmx::Addressbook::TAddressBookContact() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TOperationBuilderAdapter : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Androidapi::Jni::Graphicscontentviewtext::_di_JContentProviderOperation_Builder FBuilder;
	
protected:
	__fastcall TOperationBuilderAdapter();
	
public:
	__classmethod TOperationBuilderAdapter* __fastcall CreateInsert(const Androidapi::Jni::Javatypes::_di_JString AContentItemType)/* overload */;
	__classmethod TOperationBuilderAdapter* __fastcall CreateInsert(const Androidapi::Jni::Javatypes::_di_JString AContentItemType, const int ARawContactID)/* overload */;
	__classmethod TOperationBuilderAdapter* __fastcall CreateUpdate(const Androidapi::Jni::Javatypes::_di_JString AContentItemType, const int ARawContactID)/* overload */;
	__classmethod TOperationBuilderAdapter* __fastcall CreateDelete(const Androidapi::Jni::Javatypes::_di_JString AContentItemType, const int ARawContactID)/* overload */;
	void __fastcall AddValue(const System::UnicodeString AFieldName, const System::UnicodeString AValue)/* overload */;
	void __fastcall AddValue(const Androidapi::Jni::Javatypes::_di_JString AFieldName, const System::UnicodeString AValue)/* overload */;
	void __fastcall AddValue(const System::UnicodeString AFieldName, const Androidapi::Jni::Javatypes::_di_JString AValue)/* overload */;
	void __fastcall AddValue(const System::UnicodeString AFieldName, const __int64 AValue)/* overload */;
	void __fastcall AddValue(const System::UnicodeString AFieldName, Fmx::Surfaces::TBitmapSurface* const ABitmapSurface)/* overload */;
	void __fastcall AddValue(const Androidapi::Jni::Javatypes::_di_JString AFieldName, const System::TDateTime AValue)/* overload */;
	Androidapi::Jni::Graphicscontentviewtext::_di_JContentProviderOperation __fastcall Build();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TOperationBuilderAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TQueryAdapter : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	__interface DELPHIINTERFACE TQueryCallback;
	typedef System::DelphiInterface<TQueryCallback> _di_TQueryCallback;
	__interface TQueryCallback  : public System::IInterface 
	{
		virtual void __fastcall Invoke(Androidapi::Jni::Graphicscontentviewtext::_di_JCursor ACursor) = 0 ;
	};
	
	
private:
	Androidapi::Jni::Net::_di_Jnet_Uri FContentURI;
	Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* FFields;
	Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* FParams;
	System::UnicodeString FFilter;
	
public:
	__fastcall TQueryAdapter(const Androidapi::Jni::Net::_di_Jnet_Uri AContentURI);
	__fastcall virtual ~TQueryAdapter();
	void __fastcall SetFields(const System::TVarRec *ASource, const int ASource_High);
	void __fastcall SetFilter(const System::UnicodeString AFilter, const System::TVarRec *AParams, const int AParams_High);
	bool __fastcall Execute(const _di_TQueryCallback ACallback, const bool AOnlyFirst = false);
	__property System::UnicodeString Filter = {read=FFilter, write=FFilter};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidAddressBookHelper : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static Fmx::Addressbook::Types::TContactPhone::TLabelKind __fastcall IntegerToPhoneKind(const int AType);
	static int __fastcall PhoneKindToInteger(const Fmx::Addressbook::Types::TContactPhone::TLabelKind AKind);
	static Fmx::Addressbook::Types::TContactURL::TLabelKind __fastcall IntegerToURLKind(const int AType);
	static int __fastcall URLKindToInteger(const Fmx::Addressbook::Types::TContactURL::TLabelKind AKind);
	static Fmx::Addressbook::Types::TContactEmail::TLabelKind __fastcall IntegerToEmailKind(const int AType);
	static int __fastcall EmailKindToInteger(const Fmx::Addressbook::Types::TContactEmail::TLabelKind AKind);
	static Fmx::Addressbook::Types::TContactRelatedName::TLabelKind __fastcall IntegerToRelatedNamesKind(const int AType);
	static int __fastcall RelatedNameKindToInteger(const Fmx::Addressbook::Types::TContactRelatedName::TLabelKind AKind);
	static Fmx::Addressbook::Types::TContactDate::TLabelKind __fastcall IntegerToDateKind(const int AType);
	static int __fastcall DateKindToInteger(const Fmx::Addressbook::Types::TContactDate::TLabelKind AType);
	static Fmx::Addressbook::Types::TContactMessagingService::TServiceKind __fastcall IntegerToMessagingServiceKind(const int AType);
	static int __fastcall MessagingServiceKindToInteger(const Fmx::Addressbook::Types::TContactMessagingService::TServiceKind AKind);
	static Fmx::Addressbook::Types::TContactMessagingService::TLabelKind __fastcall IntegerToMessagingServiceLabelKind(const int AType);
	static int __fastcall MessagingServiceLabelKindToInteger(const Fmx::Addressbook::Types::TContactMessagingService::TLabelKind AKind);
	static Fmx::Addressbook::Types::TContactAddress::TLabelKind __fastcall IntegerToAddressLabelKind(const int AType);
	static int __fastcall AddressKindToInteger(const Fmx::Addressbook::Types::TContactAddress::TLabelKind AKind);
public:
	/* TObject.Create */ inline __fastcall TAndroidAddressBookHelper() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAndroidAddressBookHelper() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidAddressBookServices : public System::TInterfacedObject
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
	/* TObject.Create */ inline __fastcall TAndroidAddressBookServices() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAndroidAddressBookServices() { }
	
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterService(void);
}	/* namespace Android */
}	/* namespace Addressbook */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ADDRESSBOOK_ANDROID)
using namespace Fmx::Addressbook::Android;
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
#endif	// Fmx_Addressbook_AndroidHPP
