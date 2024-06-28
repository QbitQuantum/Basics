// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.MsCTF.pas' rev: 34.00 (Windows)

#ifndef Winapi_MsctfHPP
#define Winapi_MsctfHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>

//-- user supplied -----------------------------------------------------------

#include <msctf.h>
#include <inputscope.h>


namespace Winapi
{
namespace Msctf
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef System::PGUID *PPGUID;

typedef PWORD *PPWord;

enum DECLSPEC_DENUM InputScope: int { IS_DEFAULT, IS_URL, IS_FILE_FULLFILEPATH, IS_FILE_FILENAME, IS_EMAIL_USERNAME, IS_EMAIL_SMTPEMAILADDRESS, IS_LOGINNAME, IS_PERSONALNAME_FULLNAME, IS_PERSONALNAME_PREFIX, IS_PERSONALNAME_GIVENNAME, IS_PERSONALNAME_MIDDLENAME, IS_PERSONALNAME_SURNAME, IS_PERSONALNAME_SUFFIX, IS_ADDRESS_FULLPOSTALADDRESS, IS_ADDRESS_POSTALCODE, IS_ADDRESS_STREET, IS_ADDRESS_STATEORPROVINCE, IS_ADDRESS_CITY, IS_ADDRESS_COUNTRYNAME, IS_ADDRESS_COUNTRYSHORTNAME, IS_CURRENCY_AMOUNTANDSYMBOL, IS_CURRENCY_AMOUNT, IS_DATE_FULLDATE, IS_DATE_MONTH, IS_DATE_DAY, IS_DATE_YEAR, IS_DATE_MONTHNAME, IS_DATE_DAYNAME, IS_DIGITS, IS_NUMBER, IS_ONECHAR, IS_PASSWORD, IS_TELEPHONE_FULLTELEPHONENUMBER, IS_TELEPHONE_COUNTRYCODE, IS_TELEPHONE_AREACODE, 
	IS_TELEPHONE_LOCALNUMBER, IS_TIME_FULLTIME, IS_TIME_HOUR, IS_TIME_MINORSEC, IS_NUMBER_FULLWIDTH, IS_ALPHANUMERIC_HALFWIDTH, IS_ALPHANUMERIC_FULLWIDTH, IS_CURRENCY_CHINESE, IS_BOPOMOFO, IS_HIRAGANA, IS_KATAKANA_HALFWIDTH, IS_KATAKANA_FULLWIDTH, IS_HANJA, IS_HANJA_HALFWIDTH, IS_HANJA_FULLWIDTH, IS_SEARCH, IS_FORMULA, IS_PHRASELIST = -1, IS_REGULAREXPRESSION = -2, IS_SRGS = -3, IS_XML = -4, IS_ENUMSTRING = -5 };

typedef InputScope TInputScope;

typedef InputScope *PInputScope;

typedef _di_IEnumString *PEnumString;

typedef PInputScope *PPInputScope;

typedef Winapi::Activex::PBStr *PPBSTR;

typedef PEnumString *ppEnumString;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE GUID IID_ITfThreadMgrEventSink;
extern DELPHI_PACKAGE GUID IID_ITfDocumentMgr;
extern DELPHI_PACKAGE GUID IID_ITfContext;
extern DELPHI_PACKAGE GUID IID_ITfEditSession;
extern DELPHI_PACKAGE GUID IID_ITfRange;
extern DELPHI_PACKAGE GUID IID_ISequentialStream;
extern DELPHI_PACKAGE GUID IID_ITfContextView;
extern DELPHI_PACKAGE GUID IID_IEnumTfContextViews;
extern DELPHI_PACKAGE GUID IID_ITfReadOnlyProperty;
extern DELPHI_PACKAGE GUID IID_ITfProperty;
extern DELPHI_PACKAGE GUID IID_IEnumTfRanges;
extern DELPHI_PACKAGE GUID IID_ITfPropertyStore;
extern DELPHI_PACKAGE GUID IID_IEnumTfProperties;
extern DELPHI_PACKAGE GUID IID_ITfRangeBackup;
extern DELPHI_PACKAGE GUID IID_IEnumTfContexts;
extern DELPHI_PACKAGE GUID IID_ITfTextInputProcessor;
extern DELPHI_PACKAGE GUID IID_ITfThreadMgr;
extern DELPHI_PACKAGE GUID IID_IEnumTfDocumentMgrs;
extern DELPHI_PACKAGE GUID IID_ITfFunctionProvider;
extern DELPHI_PACKAGE GUID IID_IEnumTfFunctionProviders;
extern DELPHI_PACKAGE GUID IID_ITfCompartmentMgr;
extern DELPHI_PACKAGE GUID IID_ITfCompartment;
extern DELPHI_PACKAGE GUID IID_ITfRangeACP;
extern DELPHI_PACKAGE GUID IID_ITfPersistentPropertyLoaderACP;
extern DELPHI_PACKAGE GUID IID_ITfKeyEventSink;
extern DELPHI_PACKAGE GUID IID_ITfSource;
extern DELPHI_PACKAGE GUID IID_ITfMouseSink;
extern DELPHI_PACKAGE GUID IID_IEnumTfLanguageProfiles;
extern DELPHI_PACKAGE GUID IID_ITfUIElement;
extern DELPHI_PACKAGE GUID IID_IEnumTfUIElements;
extern DELPHI_PACKAGE GUID IID_IEnumTfInputProcessorProfiles;
extern DELPHI_PACKAGE GUID IID_ITfThreadMgrEx;
extern DELPHI_PACKAGE GUID IID_ITfThreadMgr2;
extern DELPHI_PACKAGE GUID IID_ITfConfigureSystemKeystrokeFeed;
extern DELPHI_PACKAGE GUID IID_ITfCompositionView;
extern DELPHI_PACKAGE GUID IID_IEnumITfCompositionView;
extern DELPHI_PACKAGE GUID IID_ITfComposition;
extern DELPHI_PACKAGE GUID IID_ITfCompositionSink;
extern DELPHI_PACKAGE GUID IID_ITfContextComposition;
extern DELPHI_PACKAGE GUID IID_ITfContextOwnerCompositionServices;
extern DELPHI_PACKAGE GUID IID_ITfContextOwnerCompositionSink;
extern DELPHI_PACKAGE GUID IID_ITfQueryEmbedded;
extern DELPHI_PACKAGE GUID IID_ITfInsertAtSelection;
extern DELPHI_PACKAGE GUID IID_ITfCleanupContextSink;
extern DELPHI_PACKAGE GUID IID_ITfCleanupContextDurationSink;
extern DELPHI_PACKAGE GUID IID_IEnumTfPropertyValue;
extern DELPHI_PACKAGE GUID IID_ITfMouseTracker;
extern DELPHI_PACKAGE GUID IID_ITfMouseTrackerACP;
extern DELPHI_PACKAGE GUID IID_ITfEditRecord;
extern DELPHI_PACKAGE GUID IID_ITfTextEditSink;
extern DELPHI_PACKAGE GUID IID_ITfTextLayoutSink;
extern DELPHI_PACKAGE GUID IID_ITfStatusSink;
extern DELPHI_PACKAGE GUID IID_ITfEditTransactionSink;
extern DELPHI_PACKAGE GUID IID_ITfContextOwner;
extern DELPHI_PACKAGE GUID IID_ITfContextOwnerServices;
extern DELPHI_PACKAGE GUID IID_ITfContextKeyEventSink;
extern DELPHI_PACKAGE GUID IID_ITextStoreACPServices;
extern DELPHI_PACKAGE GUID IID_ITfCreatePropertyStore;
extern DELPHI_PACKAGE GUID IID_ITfCompartmentEventSink;
extern DELPHI_PACKAGE GUID IID_ITfFunction;
extern DELPHI_PACKAGE GUID IID_ITfInputProcessorProfiles;
extern DELPHI_PACKAGE GUID IID_ITfInputProcessorProfilesEx;
extern DELPHI_PACKAGE GUID IID_ITfInputProcessorProfileSubstituteLayout;
extern DELPHI_PACKAGE GUID IID_ITfActiveLanguageProfileNotifySink;
extern DELPHI_PACKAGE GUID IID_ITfLanguageProfileNotifySink;
extern DELPHI_PACKAGE GUID IID_ITfInputProcessorProfileMgr;
extern DELPHI_PACKAGE GUID IID_ITfInputProcessorProfileActivationSink;
extern DELPHI_PACKAGE GUID IID_ITfKeystrokeMgr;
extern DELPHI_PACKAGE GUID IID_ITfKeyTraceEventSink;
extern DELPHI_PACKAGE GUID IID_ITfPreservedKeyNotifySink;
extern DELPHI_PACKAGE GUID IID_ITfMessagePump;
extern DELPHI_PACKAGE GUID IID_ITfThreadFocusSink;
extern DELPHI_PACKAGE GUID IID_ITfTextInputProcessorEx;
extern DELPHI_PACKAGE GUID IID_ITfClientId;
extern DELPHI_PACKAGE GUID IID_ITfDisplayAttributeInfo;
extern DELPHI_PACKAGE GUID IID_IEnumTfDisplayAttributeInfo;
extern DELPHI_PACKAGE GUID IID_ITfDisplayAttributeProvider;
extern DELPHI_PACKAGE GUID IID_ITfDisplayAttributeMgr;
extern DELPHI_PACKAGE GUID IID_ITfDisplayAttributeNotifySink;
extern DELPHI_PACKAGE GUID IID_ITfCategoryMgr;
extern DELPHI_PACKAGE GUID IID_ITfSourceSingle;
extern DELPHI_PACKAGE GUID IID_ITfUIElementMgr;
extern DELPHI_PACKAGE GUID IID_ITfUIElementSink;
extern DELPHI_PACKAGE GUID IID_ITfCandidateListUIElement;
extern DELPHI_PACKAGE GUID IID_ITfCandidateListUIElementBehavior;
extern DELPHI_PACKAGE GUID IID_ITfReadingInformationUIElement;
extern DELPHI_PACKAGE GUID IID_ITfTransitoryExtensionUIElement;
extern DELPHI_PACKAGE GUID IID_ITfTransitoryExtensionSink;
extern DELPHI_PACKAGE GUID IID_ITfToolTipUIElement;
extern DELPHI_PACKAGE GUID IID_ITfReverseConversionList;
extern DELPHI_PACKAGE GUID IID_ITfReverseConversion;
extern DELPHI_PACKAGE GUID IID_ITfReverseConversionMgr;
#define SID_ITfInputScope L"{fde1eaee-6924-4cdf-91e7-da38cff5559d}"
#define SID_ITfInputScope2 L"{5731eaa0-6bc2-4681-a532-92fbb74d7c41}"
extern DELPHI_PACKAGE GUID IID_ITfInputScope;
extern DELPHI_PACKAGE GUID IID_ITfInputScope2;
extern DELPHI_PACKAGE GUID GUID_PROP_INPUTSCOPE;
extern DELPHI_PACKAGE NativeUInt MsCTFHandle;
extern DELPHI_PACKAGE HRESULT __stdcall SetInputScope(HWND hwnd, InputScope inputscope);
extern DELPHI_PACKAGE bool __fastcall IsMSCTFAvailable(void);
}	/* namespace Msctf */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_MSCTF)
using namespace Winapi::Msctf;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_MsctfHPP
