// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.AddressBook.Types.pas' rev: 34.00 (Android)

#ifndef Fmx_Addressbook_TypesHPP
#define Fmx_Addressbook_TypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Addressbook
{
namespace Types
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EAddressBookException;
class DELPHICLASS EAddressBookWrongArgs;
class DELPHICLASS EAddressBookExecute;
class DELPHICLASS EAddressBookAccess;
struct TContactFieldHelper /* Helper for enum 'TContactField' */;
class DELPHICLASS TContactAddress;
class DELPHICLASS TContactAddresses;
class DELPHICLASS TContactSocialProfile;
class DELPHICLASS TContactSocialProfiles;
class DELPHICLASS TContactMessagingService;
class DELPHICLASS TContactMessagingServices;
class DELPHICLASS TContactDate;
class DELPHICLASS TContactDates;
class DELPHICLASS TContactPhone;
class DELPHICLASS TContactPhones;
class DELPHICLASS TContactEmail;
class DELPHICLASS TContactEmails;
class DELPHICLASS TContactRelatedName;
class DELPHICLASS TContactRelatedNames;
class DELPHICLASS TContactURL;
class DELPHICLASS TContactURLs;
__interface DELPHIINTERFACE IFMXAddressBookSupportedLabelKinds;
typedef System::DelphiInterface<IFMXAddressBookSupportedLabelKinds> _di_IFMXAddressBookSupportedLabelKinds;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EAddressBookException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EAddressBookException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EAddressBookException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EAddressBookException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EAddressBookException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EAddressBookException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EAddressBookException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EAddressBookException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EAddressBookException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAddressBookException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAddressBookException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAddressBookException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAddressBookException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EAddressBookException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EAddressBookWrongArgs : public EAddressBookException
{
	typedef EAddressBookException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EAddressBookWrongArgs(const System::UnicodeString Msg) : EAddressBookException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EAddressBookWrongArgs(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EAddressBookException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EAddressBookWrongArgs(NativeUInt Ident)/* overload */ : EAddressBookException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EAddressBookWrongArgs(System::PResStringRec ResStringRec)/* overload */ : EAddressBookException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EAddressBookWrongArgs(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EAddressBookException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EAddressBookWrongArgs(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EAddressBookException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EAddressBookWrongArgs(const System::UnicodeString Msg, int AHelpContext) : EAddressBookException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EAddressBookWrongArgs(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EAddressBookException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAddressBookWrongArgs(NativeUInt Ident, int AHelpContext)/* overload */ : EAddressBookException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAddressBookWrongArgs(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EAddressBookException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAddressBookWrongArgs(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EAddressBookException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAddressBookWrongArgs(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EAddressBookException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EAddressBookWrongArgs() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EAddressBookExecute : public EAddressBookException
{
	typedef EAddressBookException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EAddressBookExecute(const System::UnicodeString Msg) : EAddressBookException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EAddressBookExecute(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EAddressBookException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EAddressBookExecute(NativeUInt Ident)/* overload */ : EAddressBookException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EAddressBookExecute(System::PResStringRec ResStringRec)/* overload */ : EAddressBookException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EAddressBookExecute(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EAddressBookException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EAddressBookExecute(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EAddressBookException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EAddressBookExecute(const System::UnicodeString Msg, int AHelpContext) : EAddressBookException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EAddressBookExecute(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EAddressBookException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAddressBookExecute(NativeUInt Ident, int AHelpContext)/* overload */ : EAddressBookException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAddressBookExecute(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EAddressBookException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAddressBookExecute(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EAddressBookException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAddressBookExecute(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EAddressBookException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EAddressBookExecute() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EAddressBookAccess : public EAddressBookException
{
	typedef EAddressBookException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EAddressBookAccess(const System::UnicodeString Msg) : EAddressBookException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EAddressBookAccess(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EAddressBookException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EAddressBookAccess(NativeUInt Ident)/* overload */ : EAddressBookException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EAddressBookAccess(System::PResStringRec ResStringRec)/* overload */ : EAddressBookException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EAddressBookAccess(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EAddressBookException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EAddressBookAccess(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EAddressBookException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EAddressBookAccess(const System::UnicodeString Msg, int AHelpContext) : EAddressBookException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EAddressBookAccess(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EAddressBookException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAddressBookAccess(NativeUInt Ident, int AHelpContext)/* overload */ : EAddressBookException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAddressBookAccess(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EAddressBookException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAddressBookAccess(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EAddressBookException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAddressBookAccess(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EAddressBookException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EAddressBookAccess() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TPermissionRequestEvent)(System::TObject* ASender, const System::UnicodeString AMessage, const bool AAccessGranted);

typedef void __fastcall (__closure *TExternalChangeEvent)(System::TObject* ASender);

enum class DECLSPEC_DENUM TAddressBookAccessType : unsigned char { Read, Write };

enum class DECLSPEC_DENUM TAuthorizationStatus : unsigned char { NotDetermined, Restricted, Denied, Authorized };

enum class DECLSPEC_DENUM TContactField : unsigned char { FirstName, LastName, MiddleName, Prefix, Suffix, NickName, FirstNamePhonetic, LastNamePhonetic, MiddleNamePhonetic, Organization, JobTitle, Department, Photo, PhotoThumbnail, Note, URLs, EMails, Addresses, Phones, Dates, RelatedNames, MessagingServices, Birthday, SocialProfiles, CreationDate, ModificationDate };

typedef System::Set<TContactField, _DELPHI_SET_ENUMERATOR(TContactField::FirstName), _DELPHI_SET_ENUMERATOR(TContactField::ModificationDate)> TContactFields;

enum class DECLSPEC_DENUM TContactKind : unsigned char { Person, Organization };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactAddress : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TLabelKind : unsigned char { Custom, Home, Work, Other };
	
	typedef System::Set<TLabelKind, _DELPHI_SET_ENUMERATOR(TLabelKind::Custom), _DELPHI_SET_ENUMERATOR(TLabelKind::Other)> TLabelKinds;
	
	
private:
	TLabelKind FLabelKind;
	System::UnicodeString FLabelText;
	System::UnicodeString FCountry;
	System::UnicodeString FState;
	System::UnicodeString FCity;
	System::UnicodeString FZIP;
	System::UnicodeString FStreet;
	void __fastcall SetLabelKind(const TLabelKind AValue);
	void __fastcall SetLabelText(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetLabelText();
	
public:
	__fastcall TContactAddress()/* overload */;
	__fastcall TContactAddress(const TLabelKind AKind, const System::UnicodeString ACountry, const System::UnicodeString AState, const System::UnicodeString ACity, const System::UnicodeString AZIP, const System::UnicodeString AStreet)/* overload */;
	__fastcall TContactAddress(const System::UnicodeString ALabel, const System::UnicodeString ACountry, const System::UnicodeString AState, const System::UnicodeString ACity, const System::UnicodeString AZIP, const System::UnicodeString AStreet)/* overload */;
	__classmethod TLabelKinds __fastcall SupportedLabelKinds();
	bool __fastcall IsLabelKindSupported();
	virtual System::UnicodeString __fastcall ToString();
	__property TLabelKind LabelKind = {read=FLabelKind, write=SetLabelKind, nodefault};
	__property System::UnicodeString LabelText = {read=GetLabelText, write=SetLabelText};
	__property System::UnicodeString Country = {read=FCountry, write=FCountry};
	__property System::UnicodeString State = {read=FState, write=FState};
	__property System::UnicodeString City = {read=FCity, write=FCity};
	__property System::UnicodeString ZIP = {read=FZIP, write=FZIP};
	__property System::UnicodeString Street = {read=FStreet, write=FStreet};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TContactAddress() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactAddresses : public System::Generics::Collections::TObjectList__1<TContactAddress*>
{
	typedef System::Generics::Collections::TObjectList__1<TContactAddress*> inherited;
	
public:
	TContactAddress* __fastcall AddAddress(const System::UnicodeString ALabel, const System::UnicodeString ACountry, const System::UnicodeString AState, const System::UnicodeString ACity, const System::UnicodeString AZIP, const System::UnicodeString AStreet)/* overload */;
	TContactAddress* __fastcall AddAddress(const TContactAddress::TLabelKind AKind, const System::UnicodeString ACountry, const System::UnicodeString AState, const System::UnicodeString ACity, const System::UnicodeString AZIP, const System::UnicodeString AStreet)/* overload */;
public:
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactAddress>.Create */ inline __fastcall TContactAddresses()/* overload */ : System::Generics::Collections::TObjectList__1<TContactAddress*>() { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactAddress>.Create */ inline __fastcall TContactAddresses(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactAddress*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactAddress>.Create */ inline __fastcall TContactAddresses(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactAddress*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactAddress*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactAddress>.Create */ inline __fastcall TContactAddresses(System::Generics::Collections::TEnumerable__1<TContactAddress*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactAddress*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactAddress>.Destroy */ inline __fastcall virtual ~TContactAddresses() { }
	
public:
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactAddress>.Create */ inline __fastcall TContactAddresses(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactAddress*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TContactAddress*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactAddress>.Create */ inline __fastcall TContactAddresses(System::Generics::Collections::TEnumerable__1<TContactAddress*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TContactAddress*>(Collection) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactSocialProfile : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TLabelKind : unsigned char { Custom, Home, Work, Other };
	
	typedef System::Set<TLabelKind, _DELPHI_SET_ENUMERATOR(TLabelKind::Custom), _DELPHI_SET_ENUMERATOR(TLabelKind::Other)> TLabelKinds;
	
	enum class DECLSPEC_DENUM TServiceKind : unsigned char { Custom, Twitter, GameCenter, SinaWeibo, Facebook, Myspace, LinkedIn, Flickr };
	
	typedef System::Set<TServiceKind, _DELPHI_SET_ENUMERATOR(TServiceKind::Custom), _DELPHI_SET_ENUMERATOR(TServiceKind::Flickr)> TServiceKinds;
	
	
private:
	TLabelKind FLabelKind;
	System::UnicodeString FLabelText;
	TServiceKind FServiceKind;
	System::UnicodeString FServiceName;
	System::UnicodeString FURL;
	System::UnicodeString FUserName;
	System::UnicodeString FUserIdentifier;
	void __fastcall SetLabelKind(const TLabelKind AValue);
	void __fastcall SetLabelText(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetLabelText();
	void __fastcall SetServiceKind(const TServiceKind AValue);
	void __fastcall SetServiceName(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetServiceName();
	
public:
	__fastcall TContactSocialProfile()/* overload */;
	__fastcall TContactSocialProfile(const System::UnicodeString ALabel, const System::UnicodeString AServiceName, const System::UnicodeString AUrl, const System::UnicodeString AUserName, const System::UnicodeString AUserIdentifier)/* overload */;
	__fastcall TContactSocialProfile(const TLabelKind ALabelKind, const System::UnicodeString AServiceName, const System::UnicodeString AUrl, const System::UnicodeString AUserName, const System::UnicodeString AUserIdentifier)/* overload */;
	__fastcall TContactSocialProfile(const System::UnicodeString ALabel, const TServiceKind AServiceKind, const System::UnicodeString AUrl, const System::UnicodeString AUserName, const System::UnicodeString AUserIdentifier)/* overload */;
	__fastcall TContactSocialProfile(const TLabelKind ALabelKind, const TServiceKind AServiceKind, const System::UnicodeString AUrl, const System::UnicodeString AUserName, const System::UnicodeString AUserIdentifier)/* overload */;
	__classmethod TLabelKinds __fastcall SupportedLabelKinds();
	__classmethod TServiceKinds __fastcall SupportedServiceKinds();
	bool __fastcall IsLabelKindSupported();
	bool __fastcall IsServiceKindSupported();
	virtual System::UnicodeString __fastcall ToString();
	__property System::UnicodeString ServiceName = {read=GetServiceName, write=SetServiceName};
	__property TServiceKind ServiceKind = {read=FServiceKind, write=SetServiceKind, nodefault};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property System::UnicodeString UserIdentifier = {read=FUserIdentifier, write=FUserIdentifier};
	__property System::UnicodeString URL = {read=FURL, write=FURL};
	__property TLabelKind LabelKind = {read=FLabelKind, write=SetLabelKind, nodefault};
	__property System::UnicodeString LabelText = {read=GetLabelText, write=SetLabelText};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TContactSocialProfile() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactSocialProfiles : public System::Generics::Collections::TObjectList__1<TContactSocialProfile*>
{
	typedef System::Generics::Collections::TObjectList__1<TContactSocialProfile*> inherited;
	
public:
	TContactSocialProfile* __fastcall AddProfile(const System::UnicodeString ALabel, const System::UnicodeString AServiceName, const System::UnicodeString AUrl, const System::UnicodeString AUserName, const System::UnicodeString AUserIdentifier)/* overload */;
	TContactSocialProfile* __fastcall AddProfile(const TContactSocialProfile::TLabelKind ALabelKind, const System::UnicodeString AServiceName, const System::UnicodeString AUrl, const System::UnicodeString AUserName, const System::UnicodeString AUserIdentifier)/* overload */;
	TContactSocialProfile* __fastcall AddProfile(const System::UnicodeString ALabel, const TContactSocialProfile::TServiceKind AServiceKind, const System::UnicodeString AUrl, const System::UnicodeString AUserName, const System::UnicodeString AUserIdentifier)/* overload */;
	TContactSocialProfile* __fastcall AddProfile(const TContactSocialProfile::TLabelKind ALabelKind, const TContactSocialProfile::TServiceKind AServiceKind, const System::UnicodeString AUrl, const System::UnicodeString AUserName, const System::UnicodeString AUserIdentifier)/* overload */;
public:
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactSocialProfile>.Create */ inline __fastcall TContactSocialProfiles()/* overload */ : System::Generics::Collections::TObjectList__1<TContactSocialProfile*>() { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactSocialProfile>.Create */ inline __fastcall TContactSocialProfiles(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactSocialProfile*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactSocialProfile>.Create */ inline __fastcall TContactSocialProfiles(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactSocialProfile*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactSocialProfile*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactSocialProfile>.Create */ inline __fastcall TContactSocialProfiles(System::Generics::Collections::TEnumerable__1<TContactSocialProfile*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactSocialProfile*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactSocialProfile>.Destroy */ inline __fastcall virtual ~TContactSocialProfiles() { }
	
public:
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactSocialProfile>.Create */ inline __fastcall TContactSocialProfiles(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactSocialProfile*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TContactSocialProfile*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactSocialProfile>.Create */ inline __fastcall TContactSocialProfiles(System::Generics::Collections::TEnumerable__1<TContactSocialProfile*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TContactSocialProfile*>(Collection) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactMessagingService : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TLabelKind : unsigned char { Custom, Home, Work, Other };
	
	typedef System::Set<TLabelKind, _DELPHI_SET_ENUMERATOR(TLabelKind::Custom), _DELPHI_SET_ENUMERATOR(TLabelKind::Other)> TLabelKinds;
	
	enum class DECLSPEC_DENUM TServiceKind : unsigned char { Custom, Yahoo, Jabber, MSN, ICQ, AIM, QQ, GoogleTalk, Skype, Facebook, GaduGadu, NetMeeting };
	
	typedef System::Set<TServiceKind, _DELPHI_SET_ENUMERATOR(TServiceKind::Custom), _DELPHI_SET_ENUMERATOR(TServiceKind::NetMeeting)> TServiceKinds;
	
	
private:
	TLabelKind FLabelKind;
	System::UnicodeString FLabel;
	TServiceKind FServiceKind;
	System::UnicodeString FServiceName;
	System::UnicodeString FUserName;
	void __fastcall SetLabelKind(const TLabelKind AValue);
	void __fastcall SetLabelText(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetLabelText();
	void __fastcall SetServiceKind(const TServiceKind AValue);
	void __fastcall SetServiceName(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetServiceName();
	
public:
	__fastcall TContactMessagingService()/* overload */;
	__fastcall TContactMessagingService(const System::UnicodeString ALabel, const System::UnicodeString AServiceName, const System::UnicodeString AUserName)/* overload */;
	__fastcall TContactMessagingService(const TLabelKind ALabelKind, const System::UnicodeString AServiceName, const System::UnicodeString AUserName)/* overload */;
	__fastcall TContactMessagingService(const System::UnicodeString ALabel, const TServiceKind AServiceKind, const System::UnicodeString AUserName)/* overload */;
	__fastcall TContactMessagingService(const TLabelKind ALabelKind, const TServiceKind AServiceKind, const System::UnicodeString AUserName)/* overload */;
	__classmethod TLabelKinds __fastcall SupportedLabelKinds();
	__classmethod TServiceKinds __fastcall SupportedServiceKinds();
	bool __fastcall IsLabelKindSupported();
	bool __fastcall IsServiceKindSupported();
	virtual System::UnicodeString __fastcall ToString();
	__property System::UnicodeString ServiceName = {read=GetServiceName, write=SetServiceName};
	__property TServiceKind ServiceKind = {read=FServiceKind, write=SetServiceKind, nodefault};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property TLabelKind LabelKind = {read=FLabelKind, write=SetLabelKind, nodefault};
	__property System::UnicodeString LabelText = {read=GetLabelText, write=SetLabelText};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TContactMessagingService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactMessagingServices : public System::Generics::Collections::TObjectList__1<TContactMessagingService*>
{
	typedef System::Generics::Collections::TObjectList__1<TContactMessagingService*> inherited;
	
public:
	TContactMessagingService* __fastcall AddProfile(const System::UnicodeString ALabel, const System::UnicodeString AServiceName, const System::UnicodeString AUserName)/* overload */;
	TContactMessagingService* __fastcall AddProfile(const TContactMessagingService::TLabelKind ALabelKind, const System::UnicodeString AServiceName, const System::UnicodeString AUserName)/* overload */;
	TContactMessagingService* __fastcall AddProfile(const System::UnicodeString ALabel, const TContactMessagingService::TServiceKind AServiceKind, const System::UnicodeString AUserName)/* overload */;
	TContactMessagingService* __fastcall AddProfile(const TContactMessagingService::TLabelKind ALabelKind, const TContactMessagingService::TServiceKind AServiceKind, const System::UnicodeString AUserName)/* overload */;
public:
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactMessagingService>.Create */ inline __fastcall TContactMessagingServices()/* overload */ : System::Generics::Collections::TObjectList__1<TContactMessagingService*>() { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactMessagingService>.Create */ inline __fastcall TContactMessagingServices(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactMessagingService*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactMessagingService>.Create */ inline __fastcall TContactMessagingServices(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactMessagingService*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactMessagingService*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactMessagingService>.Create */ inline __fastcall TContactMessagingServices(System::Generics::Collections::TEnumerable__1<TContactMessagingService*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactMessagingService*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactMessagingService>.Destroy */ inline __fastcall virtual ~TContactMessagingServices() { }
	
public:
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactMessagingService>.Create */ inline __fastcall TContactMessagingServices(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactMessagingService*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TContactMessagingService*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactMessagingService>.Create */ inline __fastcall TContactMessagingServices(System::Generics::Collections::TEnumerable__1<TContactMessagingService*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TContactMessagingService*>(Collection) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TContactDate : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TLabelKind : unsigned char { Custom, Birthday, Anniversary, Other };
	
	typedef System::Set<TLabelKind, _DELPHI_SET_ENUMERATOR(TLabelKind::Custom), _DELPHI_SET_ENUMERATOR(TLabelKind::Other)> TLabelKinds;
	
	
private:
	TLabelKind FLabelKind;
	System::UnicodeString FLabelText;
	System::TDate FDate;
	void __fastcall SetLabelKind(const TLabelKind AValue);
	void __fastcall SetLabelText(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetLabelText();
	
public:
	__fastcall TContactDate()/* overload */;
	__fastcall TContactDate(const System::TDate ADate)/* overload */;
	__fastcall TContactDate(const TLabelKind AKind, const System::TDate ADate)/* overload */;
	__fastcall TContactDate(const System::UnicodeString ALabel, const System::TDate ADate)/* overload */;
	__classmethod TLabelKinds __fastcall SupportedLabelKinds();
	bool __fastcall IsLabelKindSupported();
	__property System::TDate Date = {read=FDate, write=FDate};
	__property TLabelKind LabelKind = {read=FLabelKind, write=SetLabelKind, nodefault};
	__property System::UnicodeString LabelText = {read=GetLabelText, write=SetLabelText};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TContactDate() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactDates : public System::Generics::Collections::TObjectList__1<TContactDate*>
{
	typedef System::Generics::Collections::TObjectList__1<TContactDate*> inherited;
	
public:
	TContactDate* __fastcall AddDate(const TContactDate::TLabelKind AKind, const System::TDate ADate)/* overload */;
	TContactDate* __fastcall AddDate(const System::UnicodeString ALabel, const System::TDate ADate)/* overload */;
public:
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactDate>.Create */ inline __fastcall TContactDates()/* overload */ : System::Generics::Collections::TObjectList__1<TContactDate*>() { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactDate>.Create */ inline __fastcall TContactDates(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactDate*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactDate>.Create */ inline __fastcall TContactDates(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactDate*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactDate*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactDate>.Create */ inline __fastcall TContactDates(System::Generics::Collections::TEnumerable__1<TContactDate*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactDate*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactDate>.Destroy */ inline __fastcall virtual ~TContactDates() { }
	
public:
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactDate>.Create */ inline __fastcall TContactDates(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactDate*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TContactDate*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactDate>.Create */ inline __fastcall TContactDates(System::Generics::Collections::TEnumerable__1<TContactDate*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TContactDate*>(Collection) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactPhone : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TLabelKind : unsigned char { Custom, Home, Mobile, Work, iPhone, FaxWork, FaxHome, FaxOther, Pager, Other, Callback, Car, CompanyMain, ISDN, Main, Radio, Telex, TTYTDD, WorkMobile, WorkPager, Assistant };
	
	typedef System::Set<TLabelKind, _DELPHI_SET_ENUMERATOR(TLabelKind::Custom), _DELPHI_SET_ENUMERATOR(TLabelKind::Assistant)> TLabelKinds;
	
	
private:
	TLabelKind FLabelKind;
	System::UnicodeString FLabel;
	System::UnicodeString FNumber;
	void __fastcall SetLabelKind(const TLabelKind AValue);
	void __fastcall SetLabelText(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetLabelText();
	
public:
	__fastcall TContactPhone()/* overload */;
	__fastcall TContactPhone(const TLabelKind AKind, const System::UnicodeString ANumber)/* overload */;
	__fastcall TContactPhone(const System::UnicodeString ALabel, const System::UnicodeString ANumber)/* overload */;
	__classmethod TLabelKinds __fastcall SupportedLabelKinds();
	bool __fastcall IsLabelKindSupported();
	__property System::UnicodeString Number = {read=FNumber, write=FNumber};
	__property TLabelKind LabelKind = {read=FLabelKind, write=SetLabelKind, nodefault};
	__property System::UnicodeString LabelText = {read=GetLabelText, write=SetLabelText};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TContactPhone() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactPhones : public System::Generics::Collections::TObjectList__1<TContactPhone*>
{
	typedef System::Generics::Collections::TObjectList__1<TContactPhone*> inherited;
	
public:
	TContactPhone* __fastcall AddPhone(const TContactPhone::TLabelKind AKind, const System::UnicodeString ANumber)/* overload */;
	TContactPhone* __fastcall AddPhone(const System::UnicodeString ALabel, const System::UnicodeString ANumber)/* overload */;
public:
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactPhone>.Create */ inline __fastcall TContactPhones()/* overload */ : System::Generics::Collections::TObjectList__1<TContactPhone*>() { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactPhone>.Create */ inline __fastcall TContactPhones(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactPhone*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactPhone>.Create */ inline __fastcall TContactPhones(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactPhone*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactPhone*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactPhone>.Create */ inline __fastcall TContactPhones(System::Generics::Collections::TEnumerable__1<TContactPhone*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactPhone*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactPhone>.Destroy */ inline __fastcall virtual ~TContactPhones() { }
	
public:
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactPhone>.Create */ inline __fastcall TContactPhones(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactPhone*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TContactPhone*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactPhone>.Create */ inline __fastcall TContactPhones(System::Generics::Collections::TEnumerable__1<TContactPhone*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TContactPhone*>(Collection) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactEmail : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TLabelKind : unsigned char { Custom, Home, Mobile, Work, Other };
	
	typedef System::Set<TLabelKind, _DELPHI_SET_ENUMERATOR(TLabelKind::Custom), _DELPHI_SET_ENUMERATOR(TLabelKind::Other)> TLabelKinds;
	
	
private:
	TLabelKind FLabelKind;
	System::UnicodeString FLabelText;
	System::UnicodeString FEmail;
	void __fastcall SetLabelKind(const TLabelKind AValue);
	void __fastcall SetLabelText(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetLabelText();
	
public:
	__fastcall TContactEmail()/* overload */;
	__fastcall TContactEmail(const TLabelKind AKind, const System::UnicodeString AEmail)/* overload */;
	__fastcall TContactEmail(const System::UnicodeString ALabel, const System::UnicodeString AEmail)/* overload */;
	__classmethod TLabelKinds __fastcall SupportedLabelKinds();
	bool __fastcall IsLabelKindSupported();
	__property System::UnicodeString Email = {read=FEmail, write=FEmail};
	__property TLabelKind LabelKind = {read=FLabelKind, write=SetLabelKind, nodefault};
	__property System::UnicodeString LabelText = {read=GetLabelText, write=SetLabelText};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TContactEmail() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactEmails : public System::Generics::Collections::TObjectList__1<TContactEmail*>
{
	typedef System::Generics::Collections::TObjectList__1<TContactEmail*> inherited;
	
public:
	TContactEmail* __fastcall AddEmail(const TContactEmail::TLabelKind AKind, const System::UnicodeString AEmail)/* overload */;
	TContactEmail* __fastcall AddEmail(const System::UnicodeString ALabel, const System::UnicodeString AEmail)/* overload */;
public:
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactEmail>.Create */ inline __fastcall TContactEmails()/* overload */ : System::Generics::Collections::TObjectList__1<TContactEmail*>() { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactEmail>.Create */ inline __fastcall TContactEmails(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactEmail*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactEmail>.Create */ inline __fastcall TContactEmails(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactEmail*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactEmail*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactEmail>.Create */ inline __fastcall TContactEmails(System::Generics::Collections::TEnumerable__1<TContactEmail*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactEmail*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactEmail>.Destroy */ inline __fastcall virtual ~TContactEmails() { }
	
public:
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactEmail>.Create */ inline __fastcall TContactEmails(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactEmail*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TContactEmail*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactEmail>.Create */ inline __fastcall TContactEmails(System::Generics::Collections::TEnumerable__1<TContactEmail*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TContactEmail*>(Collection) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactRelatedName : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TLabelKind : unsigned char { Custom, Mother, Father, Parent, Sister, Brother, Child, Friend, Spouse, Partner, Manager, Assistant, DomesticPartner, ReferredBy, Relative };
	
	typedef System::Set<TLabelKind, _DELPHI_SET_ENUMERATOR(TLabelKind::Custom), _DELPHI_SET_ENUMERATOR(TLabelKind::Relative)> TLabelKinds;
	
	
private:
	TLabelKind FLabelKind;
	System::UnicodeString FLabelText;
	System::UnicodeString FName;
	void __fastcall SetLabelKind(const TLabelKind AValue);
	void __fastcall SetLabelText(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetLabelText();
	
public:
	__fastcall TContactRelatedName()/* overload */;
	__fastcall TContactRelatedName(const TLabelKind AKind, const System::UnicodeString AName)/* overload */;
	__fastcall TContactRelatedName(const System::UnicodeString ALabel, const System::UnicodeString AName)/* overload */;
	__classmethod TLabelKinds __fastcall SupportedLabelKinds();
	bool __fastcall IsLabelKindSupported();
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property TLabelKind LabelKind = {read=FLabelKind, write=SetLabelKind, nodefault};
	__property System::UnicodeString LabelText = {read=GetLabelText, write=SetLabelText};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TContactRelatedName() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactRelatedNames : public System::Generics::Collections::TObjectList__1<TContactRelatedName*>
{
	typedef System::Generics::Collections::TObjectList__1<TContactRelatedName*> inherited;
	
public:
	TContactRelatedName* __fastcall AddRelatedName(const TContactRelatedName::TLabelKind AKind, const System::UnicodeString AName)/* overload */;
	TContactRelatedName* __fastcall AddRelatedName(const System::UnicodeString ALabel, const System::UnicodeString AName)/* overload */;
public:
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactRelatedName>.Create */ inline __fastcall TContactRelatedNames()/* overload */ : System::Generics::Collections::TObjectList__1<TContactRelatedName*>() { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactRelatedName>.Create */ inline __fastcall TContactRelatedNames(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactRelatedName*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactRelatedName>.Create */ inline __fastcall TContactRelatedNames(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactRelatedName*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactRelatedName*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactRelatedName>.Create */ inline __fastcall TContactRelatedNames(System::Generics::Collections::TEnumerable__1<TContactRelatedName*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactRelatedName*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactRelatedName>.Destroy */ inline __fastcall virtual ~TContactRelatedNames() { }
	
public:
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactRelatedName>.Create */ inline __fastcall TContactRelatedNames(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactRelatedName*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TContactRelatedName*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactRelatedName>.Create */ inline __fastcall TContactRelatedNames(System::Generics::Collections::TEnumerable__1<TContactRelatedName*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TContactRelatedName*>(Collection) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactURL : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TLabelKind : unsigned char { Custom, HomePage, Blog, Profile, Home, Work, FTP, Other };
	
	typedef System::Set<TLabelKind, _DELPHI_SET_ENUMERATOR(TLabelKind::Custom), _DELPHI_SET_ENUMERATOR(TLabelKind::Other)> TLabelKinds;
	
	
private:
	TLabelKind FLabelKind;
	System::UnicodeString FLabelText;
	System::UnicodeString FURL;
	void __fastcall SetLabelKind(const TLabelKind AValue);
	void __fastcall SetLabelText(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetLabelText();
	
public:
	__fastcall TContactURL()/* overload */;
	__fastcall TContactURL(const TLabelKind AKind, const System::UnicodeString AURL)/* overload */;
	__fastcall TContactURL(const System::UnicodeString ALabel, const System::UnicodeString AURL)/* overload */;
	__classmethod TLabelKinds __fastcall SupportedLabelKinds();
	bool __fastcall IsLabelKindSupported();
	__property System::UnicodeString URL = {read=FURL, write=FURL};
	__property TLabelKind LabelKind = {read=FLabelKind, write=SetLabelKind, nodefault};
	__property System::UnicodeString LabelText = {read=GetLabelText, write=SetLabelText};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TContactURL() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TContactURLs : public System::Generics::Collections::TObjectList__1<TContactURL*>
{
	typedef System::Generics::Collections::TObjectList__1<TContactURL*> inherited;
	
public:
	TContactURL* __fastcall AddURL(const TContactURL::TLabelKind AKind, const System::UnicodeString AURL)/* overload */;
	TContactURL* __fastcall AddURL(const System::UnicodeString ALabel, const System::UnicodeString AURL)/* overload */;
public:
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactURL>.Create */ inline __fastcall TContactURLs()/* overload */ : System::Generics::Collections::TObjectList__1<TContactURL*>() { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactURL>.Create */ inline __fastcall TContactURLs(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactURL*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactURL>.Create */ inline __fastcall TContactURLs(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactURL*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactURL*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactURL>.Create */ inline __fastcall TContactURLs(System::Generics::Collections::TEnumerable__1<TContactURL*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TContactURL*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMX_AddressBook_Types_TContactURL>.Destroy */ inline __fastcall virtual ~TContactURLs() { }
	
public:
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactURL>.Create */ inline __fastcall TContactURLs(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TContactURL*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TContactURL*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_AddressBook_Types_TContactURL>.Create */ inline __fastcall TContactURLs(System::Generics::Collections::TEnumerable__1<TContactURL*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TContactURL*>(Collection) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{842B17FF-8059-4904-A8BF-AD520B4FC0A5}") IFMXAddressBookSupportedLabelKinds  : public System::IInterface 
{
	virtual TContactAddress::TLabelKinds __fastcall AddressesLabelKinds() = 0 ;
	virtual TContactSocialProfile::TLabelKinds __fastcall SocialProfilesLabelKinds() = 0 ;
	virtual TContactSocialProfile::TServiceKinds __fastcall SocialProfilesServiceKinds() = 0 ;
	virtual TContactMessagingService::TLabelKinds __fastcall MessagingServicesLabelKinds() = 0 ;
	virtual TContactMessagingService::TServiceKinds __fastcall MessagingServicesKinds() = 0 ;
	virtual TContactDate::TLabelKinds __fastcall DatesLabelKinds() = 0 ;
	virtual TContactPhone::TLabelKinds __fastcall PhonesLabelKinds() = 0 ;
	virtual TContactEmail::TLabelKinds __fastcall EmailsLabelKinds() = 0 ;
	virtual TContactRelatedName::TLabelKinds __fastcall RelatedNamesLabelKinds() = 0 ;
	virtual TContactURL::TLabelKinds __fastcall URLsLabelKinds() = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TContactFields StructuredNameFields;
extern DELPHI_PACKAGE TContactFields CompanyFields;
}	/* namespace Types */
}	/* namespace Addressbook */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ADDRESSBOOK_TYPES)
using namespace Fmx::Addressbook::Types;
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
#endif	// Fmx_Addressbook_TypesHPP
