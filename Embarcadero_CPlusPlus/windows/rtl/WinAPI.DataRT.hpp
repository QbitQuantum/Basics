// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DataRT.pas' rev: 34.00 (Windows)

#ifndef Winapi_DatartHPP
#define Winapi_DatartHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Types.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.ApplicationModel.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Datart
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IIterator_1__Text_TextSegment_Base;
typedef System::DelphiInterface<IIterator_1__Text_TextSegment_Base> _di_IIterator_1__Text_TextSegment_Base;
__interface DELPHIINTERFACE IIterator_1__Text_TextSegment;
typedef System::DelphiInterface<IIterator_1__Text_TextSegment> _di_IIterator_1__Text_TextSegment;
__interface DELPHIINTERFACE IIterable_1__Text_TextSegment_Base;
typedef System::DelphiInterface<IIterable_1__Text_TextSegment_Base> _di_IIterable_1__Text_TextSegment_Base;
__interface DELPHIINTERFACE IIterable_1__Text_TextSegment;
typedef System::DelphiInterface<IIterable_1__Text_TextSegment> _di_IIterable_1__Text_TextSegment;
__interface DELPHIINTERFACE IVectorView_1__Text_TextSegment;
typedef System::DelphiInterface<IVectorView_1__Text_TextSegment> _di_IVectorView_1__Text_TextSegment;
__interface DELPHIINTERFACE Json_IJsonObject;
typedef System::DelphiInterface<Json_IJsonObject> _di_Json_IJsonObject;
__interface DELPHIINTERFACE Json_IJsonArray;
typedef System::DelphiInterface<Json_IJsonArray> _di_Json_IJsonArray;
__interface DELPHIINTERFACE Json_IJsonValue;
typedef System::DelphiInterface<Json_IJsonValue> _di_Json_IJsonValue;
__interface DELPHIINTERFACE Json_IJsonValueStatics;
typedef System::DelphiInterface<Json_IJsonValueStatics> _di_Json_IJsonValueStatics;
__interface DELPHIINTERFACE Json_IJsonValueStatics2;
typedef System::DelphiInterface<Json_IJsonValueStatics2> _di_Json_IJsonValueStatics2;
__interface DELPHIINTERFACE Json_IJsonObjectWithDefaultValues;
typedef System::DelphiInterface<Json_IJsonObjectWithDefaultValues> _di_Json_IJsonObjectWithDefaultValues;
__interface DELPHIINTERFACE Json_IJsonObjectStatics;
typedef System::DelphiInterface<Json_IJsonObjectStatics> _di_Json_IJsonObjectStatics;
__interface DELPHIINTERFACE Json_IJsonArrayStatics;
typedef System::DelphiInterface<Json_IJsonArrayStatics> _di_Json_IJsonArrayStatics;
__interface DELPHIINTERFACE Json_IJsonErrorStatics2;
typedef System::DelphiInterface<Json_IJsonErrorStatics2> _di_Json_IJsonErrorStatics2;
__interface DELPHIINTERFACE IIterator_1__Xml_Dom_IXmlNode_Base;
typedef System::DelphiInterface<IIterator_1__Xml_Dom_IXmlNode_Base> _di_IIterator_1__Xml_Dom_IXmlNode_Base;
__interface DELPHIINTERFACE IIterator_1__Xml_Dom_IXmlNode;
typedef System::DelphiInterface<IIterator_1__Xml_Dom_IXmlNode> _di_IIterator_1__Xml_Dom_IXmlNode;
__interface DELPHIINTERFACE Xml_Dom_IXmlNodeSelector;
typedef System::DelphiInterface<Xml_Dom_IXmlNodeSelector> _di_Xml_Dom_IXmlNodeSelector;
__interface DELPHIINTERFACE Xml_Dom_IXmlNodeSerializer;
typedef System::DelphiInterface<Xml_Dom_IXmlNodeSerializer> _di_Xml_Dom_IXmlNodeSerializer;
__interface DELPHIINTERFACE Xml_Dom_IXmlLoadSettings;
typedef System::DelphiInterface<Xml_Dom_IXmlLoadSettings> _di_Xml_Dom_IXmlLoadSettings;
__interface DELPHIINTERFACE AsyncOperationProgressHandler_2__IBuffer__Cardinal;
typedef System::DelphiInterface<AsyncOperationProgressHandler_2__IBuffer__Cardinal> _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal;
__interface DELPHIINTERFACE AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal;
typedef System::DelphiInterface<AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal> _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal;
__interface DELPHIINTERFACE IAsyncOperationWithProgress_2__IBuffer__Cardinal;
typedef System::DelphiInterface<IAsyncOperationWithProgress_2__IBuffer__Cardinal> _di_IAsyncOperationWithProgress_2__IBuffer__Cardinal;
__interface DELPHIINTERFACE AsyncOperationProgressHandler_2__Cardinal__Cardinal;
typedef System::DelphiInterface<AsyncOperationProgressHandler_2__Cardinal__Cardinal> _di_AsyncOperationProgressHandler_2__Cardinal__Cardinal;
__interface DELPHIINTERFACE AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal;
typedef System::DelphiInterface<AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal> _di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal;
__interface DELPHIINTERFACE IAsyncOperationWithProgress_2__Cardinal__Cardinal;
typedef System::DelphiInterface<IAsyncOperationWithProgress_2__Cardinal__Cardinal> _di_IAsyncOperationWithProgress_2__Cardinal__Cardinal;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Boolean;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Boolean> _di_AsyncOperationCompletedHandler_1__Boolean;
__interface DELPHIINTERFACE IAsyncOperation_1__Boolean;
typedef System::DelphiInterface<IAsyncOperation_1__Boolean> _di_IAsyncOperation_1__Boolean;
__interface DELPHIINTERFACE Xml_Dom_IXmlDocumentIO;
typedef System::DelphiInterface<Xml_Dom_IXmlDocumentIO> _di_Xml_Dom_IXmlDocumentIO;
__interface DELPHIINTERFACE Xml_Dom_IXmlDocumentIO2;
typedef System::DelphiInterface<Xml_Dom_IXmlDocumentIO2> _di_Xml_Dom_IXmlDocumentIO2;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument_Delegate_Base> _di_AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument> _di_AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument;
__interface DELPHIINTERFACE IAsyncOperation_1__Xml_Dom_IXmlDocument_Base;
typedef System::DelphiInterface<IAsyncOperation_1__Xml_Dom_IXmlDocument_Base> _di_IAsyncOperation_1__Xml_Dom_IXmlDocument_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__Xml_Dom_IXmlDocument;
typedef System::DelphiInterface<IAsyncOperation_1__Xml_Dom_IXmlDocument> _di_IAsyncOperation_1__Xml_Dom_IXmlDocument;
__interface DELPHIINTERFACE Xml_Dom_IXmlDocumentStatics;
typedef System::DelphiInterface<Xml_Dom_IXmlDocumentStatics> _di_Xml_Dom_IXmlDocumentStatics;
__interface DELPHIINTERFACE Text_IUnicodeCharactersStatics;
typedef System::DelphiInterface<Text_IUnicodeCharactersStatics> _di_Text_IUnicodeCharactersStatics;
__interface DELPHIINTERFACE Text_IAlternateWordForm;
typedef System::DelphiInterface<Text_IAlternateWordForm> _di_Text_IAlternateWordForm;
__interface DELPHIINTERFACE Text_ISelectableWordSegment;
typedef System::DelphiInterface<Text_ISelectableWordSegment> _di_Text_ISelectableWordSegment;
__interface DELPHIINTERFACE IIterator_1__Text_IAlternateWordForm_Base;
typedef System::DelphiInterface<IIterator_1__Text_IAlternateWordForm_Base> _di_IIterator_1__Text_IAlternateWordForm_Base;
__interface DELPHIINTERFACE IIterator_1__Text_IAlternateWordForm;
typedef System::DelphiInterface<IIterator_1__Text_IAlternateWordForm> _di_IIterator_1__Text_IAlternateWordForm;
__interface DELPHIINTERFACE IIterable_1__Text_IAlternateWordForm_Base;
typedef System::DelphiInterface<IIterable_1__Text_IAlternateWordForm_Base> _di_IIterable_1__Text_IAlternateWordForm_Base;
__interface DELPHIINTERFACE IIterable_1__Text_IAlternateWordForm;
typedef System::DelphiInterface<IIterable_1__Text_IAlternateWordForm> _di_IIterable_1__Text_IAlternateWordForm;
__interface DELPHIINTERFACE IVectorView_1__Text_IAlternateWordForm;
typedef System::DelphiInterface<IVectorView_1__Text_IAlternateWordForm> _di_IVectorView_1__Text_IAlternateWordForm;
__interface DELPHIINTERFACE Text_IWordSegment;
typedef System::DelphiInterface<Text_IWordSegment> _di_Text_IWordSegment;
__interface DELPHIINTERFACE IIterator_1__Text_IWordSegment_Base;
typedef System::DelphiInterface<IIterator_1__Text_IWordSegment_Base> _di_IIterator_1__Text_IWordSegment_Base;
__interface DELPHIINTERFACE IIterator_1__Text_IWordSegment;
typedef System::DelphiInterface<IIterator_1__Text_IWordSegment> _di_IIterator_1__Text_IWordSegment;
__interface DELPHIINTERFACE IIterable_1__Text_IWordSegment_Base;
typedef System::DelphiInterface<IIterable_1__Text_IWordSegment_Base> _di_IIterable_1__Text_IWordSegment_Base;
__interface DELPHIINTERFACE IIterable_1__Text_IWordSegment;
typedef System::DelphiInterface<IIterable_1__Text_IWordSegment> _di_IIterable_1__Text_IWordSegment;
__interface DELPHIINTERFACE Text_WordSegmentsTokenizingHandler;
typedef System::DelphiInterface<Text_WordSegmentsTokenizingHandler> _di_Text_WordSegmentsTokenizingHandler;
__interface DELPHIINTERFACE IVectorView_1__Text_IWordSegment;
typedef System::DelphiInterface<IVectorView_1__Text_IWordSegment> _di_IVectorView_1__Text_IWordSegment;
__interface DELPHIINTERFACE Text_IWordsSegmenter;
typedef System::DelphiInterface<Text_IWordsSegmenter> _di_Text_IWordsSegmenter;
__interface DELPHIINTERFACE Text_IWordsSegmenterFactory;
typedef System::DelphiInterface<Text_IWordsSegmenterFactory> _di_Text_IWordsSegmenterFactory;
__interface DELPHIINTERFACE IIterator_1__Text_ISelectableWordSegment_Base;
typedef System::DelphiInterface<IIterator_1__Text_ISelectableWordSegment_Base> _di_IIterator_1__Text_ISelectableWordSegment_Base;
__interface DELPHIINTERFACE IIterator_1__Text_ISelectableWordSegment;
typedef System::DelphiInterface<IIterator_1__Text_ISelectableWordSegment> _di_IIterator_1__Text_ISelectableWordSegment;
__interface DELPHIINTERFACE IIterable_1__Text_ISelectableWordSegment_Base;
typedef System::DelphiInterface<IIterable_1__Text_ISelectableWordSegment_Base> _di_IIterable_1__Text_ISelectableWordSegment_Base;
__interface DELPHIINTERFACE IIterable_1__Text_ISelectableWordSegment;
typedef System::DelphiInterface<IIterable_1__Text_ISelectableWordSegment> _di_IIterable_1__Text_ISelectableWordSegment;
__interface DELPHIINTERFACE Text_SelectableWordSegmentsTokenizingHandler;
typedef System::DelphiInterface<Text_SelectableWordSegmentsTokenizingHandler> _di_Text_SelectableWordSegmentsTokenizingHandler;
__interface DELPHIINTERFACE IVectorView_1__Text_ISelectableWordSegment;
typedef System::DelphiInterface<IVectorView_1__Text_ISelectableWordSegment> _di_IVectorView_1__Text_ISelectableWordSegment;
__interface DELPHIINTERFACE Text_ISelectableWordsSegmenter;
typedef System::DelphiInterface<Text_ISelectableWordsSegmenter> _di_Text_ISelectableWordsSegmenter;
__interface DELPHIINTERFACE Text_ISelectableWordsSegmenterFactory;
typedef System::DelphiInterface<Text_ISelectableWordsSegmenterFactory> _di_Text_ISelectableWordsSegmenterFactory;
__interface DELPHIINTERFACE IIterator_1__HSTRING;
typedef System::DelphiInterface<IIterator_1__HSTRING> _di_IIterator_1__HSTRING;
__interface DELPHIINTERFACE IIterable_1__HSTRING;
typedef System::DelphiInterface<IIterable_1__HSTRING> _di_IIterable_1__HSTRING;
__interface DELPHIINTERFACE IVectorView_1__HSTRING;
typedef System::DelphiInterface<IVectorView_1__HSTRING> _di_IVectorView_1__HSTRING;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__HSTRING;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__HSTRING> _di_AsyncOperationCompletedHandler_1__IVectorView_1__HSTRING;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__HSTRING;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__HSTRING> _di_IAsyncOperation_1__IVectorView_1__HSTRING;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__HSTRING;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__HSTRING> _di_AsyncOperationCompletedHandler_1__HSTRING;
__interface DELPHIINTERFACE IAsyncOperation_1__HSTRING;
typedef System::DelphiInterface<IAsyncOperation_1__HSTRING> _di_IAsyncOperation_1__HSTRING;
__interface DELPHIINTERFACE Text_ITextPhoneme;
typedef System::DelphiInterface<Text_ITextPhoneme> _di_Text_ITextPhoneme;
__interface DELPHIINTERFACE IIterator_1__Text_ITextPhoneme_Base;
typedef System::DelphiInterface<IIterator_1__Text_ITextPhoneme_Base> _di_IIterator_1__Text_ITextPhoneme_Base;
__interface DELPHIINTERFACE IIterator_1__Text_ITextPhoneme;
typedef System::DelphiInterface<IIterator_1__Text_ITextPhoneme> _di_IIterator_1__Text_ITextPhoneme;
__interface DELPHIINTERFACE IIterable_1__Text_ITextPhoneme_Base;
typedef System::DelphiInterface<IIterable_1__Text_ITextPhoneme_Base> _di_IIterable_1__Text_ITextPhoneme_Base;
__interface DELPHIINTERFACE IIterable_1__Text_ITextPhoneme;
typedef System::DelphiInterface<IIterable_1__Text_ITextPhoneme> _di_IIterable_1__Text_ITextPhoneme;
__interface DELPHIINTERFACE IVectorView_1__Text_ITextPhoneme;
typedef System::DelphiInterface<IVectorView_1__Text_ITextPhoneme> _di_IVectorView_1__Text_ITextPhoneme;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme> _di_AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__Text_ITextPhoneme_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__Text_ITextPhoneme_Base> _di_IAsyncOperation_1__IVectorView_1__Text_ITextPhoneme_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__Text_ITextPhoneme;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__Text_ITextPhoneme> _di_IAsyncOperation_1__IVectorView_1__Text_ITextPhoneme;
__interface DELPHIINTERFACE IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment;
typedef System::DelphiInterface<IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment> _di_IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment_Base;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment_Base> _di_IIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment_Base;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment> _di_IIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment_Base;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment_Base> _di_IIterable_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment_Base;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment> _di_IIterable_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment;
__interface DELPHIINTERFACE IMapView_2__HSTRING__IVectorView_1__Text_TextSegment_Base;
typedef System::DelphiInterface<IMapView_2__HSTRING__IVectorView_1__Text_TextSegment_Base> _di_IMapView_2__HSTRING__IVectorView_1__Text_TextSegment_Base;
__interface DELPHIINTERFACE IMapView_2__HSTRING__IVectorView_1__Text_TextSegment;
typedef System::DelphiInterface<IMapView_2__HSTRING__IVectorView_1__Text_TextSegment> _di_IMapView_2__HSTRING__IVectorView_1__Text_TextSegment;
__interface DELPHIINTERFACE IMap_2__HSTRING__IVectorView_1__Text_TextSegment;
typedef System::DelphiInterface<IMap_2__HSTRING__IVectorView_1__Text_TextSegment> _di_IMap_2__HSTRING__IVectorView_1__Text_TextSegment;
class DELPHICLASS TJson_JsonArray;
class DELPHICLASS TJson_JsonObject;
class DELPHICLASS TJson_JsonValue;
class DELPHICLASS TJson_JsonError;
class DELPHICLASS TXml_Dom_XmlDocument;
class DELPHICLASS TText_UnicodeCharacters;
class DELPHICLASS TText_WordsSegmenter;
class DELPHICLASS TText_SelectableWordsSegmenter;
//-- type declarations -------------------------------------------------------
typedef _di_IIterator_1__Text_TextSegment *PIIterator_1__Text_TextSegment;

typedef _di_IIterable_1__Text_TextSegment *PIIterable_1__Text_TextSegment;

typedef _di_IVectorView_1__Text_TextSegment *PIVectorView_1__Text_TextSegment;

typedef _di_Json_IJsonObject *PJson_IJsonObject;

typedef _di_Json_IJsonArray *PJson_IJsonArray;

typedef _di_Json_IJsonValue *PJson_IJsonValue;

typedef _di_Json_IJsonValueStatics *PJson_IJsonValueStatics;

typedef _di_Json_IJsonValueStatics2 *PJson_IJsonValueStatics2;

typedef _di_Json_IJsonObjectWithDefaultValues *PJson_IJsonObjectWithDefaultValues;

typedef _di_Json_IJsonObjectStatics *PJson_IJsonObjectStatics;

typedef _di_Json_IJsonArrayStatics *PJson_IJsonArrayStatics;

typedef _di_Json_IJsonErrorStatics2 *PJson_IJsonErrorStatics2;

typedef _di_IIterator_1__Xml_Dom_IXmlNode *PIIterator_1__Xml_Dom_IXmlNode;

typedef _di_Xml_Dom_IXmlNodeSelector *PXml_Dom_IXmlNodeSelector;

typedef _di_Xml_Dom_IXmlNodeSerializer *PXml_Dom_IXmlNodeSerializer;

typedef _di_Xml_Dom_IXmlLoadSettings *PXml_Dom_IXmlLoadSettings;

typedef _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal *PAsyncOperationProgressHandler_2__IBuffer__Cardinal;

typedef _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal *PAsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal;

typedef _di_IAsyncOperationWithProgress_2__IBuffer__Cardinal *PIAsyncOperationWithProgress_2__IBuffer__Cardinal;

typedef _di_AsyncOperationProgressHandler_2__Cardinal__Cardinal *PAsyncOperationProgressHandler_2__Cardinal__Cardinal;

typedef _di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal *PAsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal;

typedef _di_IAsyncOperationWithProgress_2__Cardinal__Cardinal *PIAsyncOperationWithProgress_2__Cardinal__Cardinal;

typedef _di_AsyncOperationCompletedHandler_1__Boolean *PAsyncOperationCompletedHandler_1__Boolean;

typedef _di_IAsyncOperation_1__Boolean *PIAsyncOperation_1__Boolean;

typedef _di_Xml_Dom_IXmlDocumentIO *PXml_Dom_IXmlDocumentIO;

typedef _di_Xml_Dom_IXmlDocumentIO2 *PXml_Dom_IXmlDocumentIO2;

typedef _di_AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument *PAsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument;

typedef _di_IAsyncOperation_1__Xml_Dom_IXmlDocument *PIAsyncOperation_1__Xml_Dom_IXmlDocument;

typedef _di_Xml_Dom_IXmlDocumentStatics *PXml_Dom_IXmlDocumentStatics;

typedef _di_Text_IUnicodeCharactersStatics *PText_IUnicodeCharactersStatics;

typedef _di_Text_IAlternateWordForm *PText_IAlternateWordForm;

typedef _di_Text_ISelectableWordSegment *PText_ISelectableWordSegment;

typedef _di_IIterator_1__Text_IAlternateWordForm *PIIterator_1__Text_IAlternateWordForm;

typedef _di_IIterable_1__Text_IAlternateWordForm *PIIterable_1__Text_IAlternateWordForm;

typedef _di_IVectorView_1__Text_IAlternateWordForm *PIVectorView_1__Text_IAlternateWordForm;

typedef _di_Text_IWordSegment *PText_IWordSegment;

typedef _di_IIterator_1__Text_IWordSegment *PIIterator_1__Text_IWordSegment;

typedef _di_IIterable_1__Text_IWordSegment *PIIterable_1__Text_IWordSegment;

typedef _di_Text_WordSegmentsTokenizingHandler *PText_WordSegmentsTokenizingHandler;

typedef _di_IVectorView_1__Text_IWordSegment *PIVectorView_1__Text_IWordSegment;

typedef _di_Text_IWordsSegmenter *PText_IWordsSegmenter;

typedef _di_Text_IWordsSegmenterFactory *PText_IWordsSegmenterFactory;

typedef _di_IIterator_1__Text_ISelectableWordSegment *PIIterator_1__Text_ISelectableWordSegment;

typedef _di_IIterable_1__Text_ISelectableWordSegment *PIIterable_1__Text_ISelectableWordSegment;

typedef _di_Text_SelectableWordSegmentsTokenizingHandler *PText_SelectableWordSegmentsTokenizingHandler;

typedef _di_IVectorView_1__Text_ISelectableWordSegment *PIVectorView_1__Text_ISelectableWordSegment;

typedef _di_Text_ISelectableWordsSegmenter *PText_ISelectableWordsSegmenter;

typedef _di_Text_ISelectableWordsSegmenterFactory *PText_ISelectableWordsSegmenterFactory;

typedef _di_IIterator_1__HSTRING *PIIterator_1__HSTRING;

typedef _di_IIterable_1__HSTRING *PIIterable_1__HSTRING;

typedef _di_IVectorView_1__HSTRING *PIVectorView_1__HSTRING;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__HSTRING *PAsyncOperationCompletedHandler_1__IVectorView_1__HSTRING;

typedef _di_IAsyncOperation_1__IVectorView_1__HSTRING *PIAsyncOperation_1__IVectorView_1__HSTRING;

typedef _di_AsyncOperationCompletedHandler_1__HSTRING *PAsyncOperationCompletedHandler_1__HSTRING;

typedef _di_IAsyncOperation_1__HSTRING *PIAsyncOperation_1__HSTRING;

typedef _di_Text_ITextPhoneme *PText_ITextPhoneme;

typedef _di_IIterator_1__Text_ITextPhoneme *PIIterator_1__Text_ITextPhoneme;

typedef _di_IIterable_1__Text_ITextPhoneme *PIIterable_1__Text_ITextPhoneme;

typedef _di_IVectorView_1__Text_ITextPhoneme *PIVectorView_1__Text_ITextPhoneme;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme *PAsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme;

typedef _di_IAsyncOperation_1__IVectorView_1__Text_ITextPhoneme *PIAsyncOperation_1__IVectorView_1__Text_ITextPhoneme;

typedef _di_IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment *PIKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment;

typedef _di_IIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment *PIIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment;

typedef _di_IIterable_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment *PIIterable_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment;

typedef _di_IMapView_2__HSTRING__IVectorView_1__Text_TextSegment *PIMapView_2__HSTRING__IVectorView_1__Text_TextSegment;

typedef _di_IMap_2__HSTRING__IVectorView_1__Text_TextSegment *PIMap_2__HSTRING__IVectorView_1__Text_TextSegment;

__interface  INTERFACE_UUID("{645A39B4-F001-5272-9015-FB4A327179AE}") IIterator_1__Text_TextSegment_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__Text_TextSegment  : public IIterator_1__Text_TextSegment_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::Text_TextSegment &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PText_TextSegment items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Text_TextSegment _scw_get_Current() { Winapi::Commontypes::Text_TextSegment __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Text_TextSegment Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{5498F4F3-CEE4-5B72-9729-815C4AD7B9DC}") IIterable_1__Text_TextSegment_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__Text_TextSegment  : public IIterable_1__Text_TextSegment_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Text_TextSegment &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__Text_TextSegment  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::Text_TextSegment &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::Text_TextSegment value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PText_TextSegment items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{064E24DD-29C2-4F83-9AC1-9EE11578BEB3}") Json_IJsonObject  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetNamedValue(HSTRING name, _di_Json_IJsonValue &__GetNamedValue_result) = 0 ;
	virtual HRESULT __safecall SetNamedValue(HSTRING name, _di_Json_IJsonValue value) = 0 ;
	virtual HRESULT __safecall GetNamedObject(HSTRING name, _di_Json_IJsonObject &__GetNamedObject_result) = 0 ;
	virtual HRESULT __safecall GetNamedArray(HSTRING name, _di_Json_IJsonArray &__GetNamedArray_result) = 0 ;
	virtual HRESULT __safecall GetNamedString(HSTRING name, HSTRING &__GetNamedString_result) = 0 ;
	virtual HRESULT __safecall GetNamedNumber(HSTRING name, double &__GetNamedNumber_result) = 0 ;
	virtual HRESULT __safecall GetNamedBoolean(HSTRING name, bool &__GetNamedBoolean_result) = 0 ;
};

__interface  INTERFACE_UUID("{08C1DDB6-0CBD-4A9A-B5D3-2F852DC37E81}") Json_IJsonArray  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetObjectAt(unsigned index, _di_Json_IJsonObject &__GetObjectAt_result) = 0 ;
	virtual HRESULT __safecall GetArrayAt(unsigned index, _di_Json_IJsonArray &__GetArrayAt_result) = 0 ;
	virtual HRESULT __safecall GetStringAt(unsigned index, HSTRING &__GetStringAt_result) = 0 ;
	virtual HRESULT __safecall GetNumberAt(unsigned index, double &__GetNumberAt_result) = 0 ;
	virtual HRESULT __safecall GetBooleanAt(unsigned index, bool &__GetBooleanAt_result) = 0 ;
};

__interface  INTERFACE_UUID("{A3219ECB-F0B3-4DCD-BEEE-19D48CD3ED1E}") Json_IJsonValue  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ValueType(Winapi::Commontypes::Json_JsonValueType &__get_ValueType_result) = 0 ;
	virtual HRESULT __safecall Stringify(HSTRING &__Stringify_result) = 0 ;
	virtual HRESULT __safecall GetString(HSTRING &__GetString_result) = 0 ;
	virtual HRESULT __safecall GetNumber(double &__GetNumber_result) = 0 ;
	virtual HRESULT __safecall GetBoolean(bool &__GetBoolean_result) = 0 ;
	virtual HRESULT __safecall GetArray(_di_Json_IJsonArray &__GetArray_result) = 0 ;
	virtual HRESULT __safecall GetObject(_di_Json_IJsonObject &__GetObject_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Json_JsonValueType _scw_get_ValueType() { Winapi::Commontypes::Json_JsonValueType __r; HRESULT __hr = get_ValueType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Json_JsonValueType ValueType = {read=_scw_get_ValueType};
};

__interface  INTERFACE_UUID("{5F6B544A-2F53-48E1-91A3-F78B50A6345C}") Json_IJsonValueStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Parse(HSTRING input, _di_Json_IJsonValue &__Parse_result) = 0 ;
	virtual HRESULT __safecall TryParse(HSTRING input, /* out */ _di_Json_IJsonValue &a_result, bool &__TryParse_result) = 0 ;
	virtual HRESULT __safecall CreateBooleanValue(bool input, _di_Json_IJsonValue &__CreateBooleanValue_result) = 0 ;
	virtual HRESULT __safecall CreateNumberValue(double input, _di_Json_IJsonValue &__CreateNumberValue_result) = 0 ;
	virtual HRESULT __safecall CreateStringValue(HSTRING input, _di_Json_IJsonValue &__CreateStringValue_result) = 0 ;
};

__interface  INTERFACE_UUID("{1D9ECBE4-3FE8-4335-8392-93D8E36865F0}") Json_IJsonValueStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateNullValue(_di_Json_IJsonValue &__CreateNullValue_result) = 0 ;
};

__interface  INTERFACE_UUID("{D960D2A2-B7F0-4F00-8E44-D82CF415EA13}") Json_IJsonObjectWithDefaultValues  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetNamedValue(HSTRING name, _di_Json_IJsonValue defaultValue, _di_Json_IJsonValue &__GetNamedValue_result) = 0 ;
	virtual HRESULT __safecall GetNamedObject(HSTRING name, _di_Json_IJsonObject defaultValue, _di_Json_IJsonObject &__GetNamedObject_result) = 0 ;
	virtual HRESULT __safecall GetNamedString(HSTRING name, HSTRING defaultValue, HSTRING &__GetNamedString_result) = 0 ;
	virtual HRESULT __safecall GetNamedArray(HSTRING name, _di_Json_IJsonArray defaultValue, _di_Json_IJsonArray &__GetNamedArray_result) = 0 ;
	virtual HRESULT __safecall GetNamedNumber(HSTRING name, double defaultValue, double &__GetNamedNumber_result) = 0 ;
	virtual HRESULT __safecall GetNamedBoolean(HSTRING name, bool defaultValue, bool &__GetNamedBoolean_result) = 0 ;
};

__interface  INTERFACE_UUID("{2289F159-54DE-45D8-ABCC-22603FA066A0}") Json_IJsonObjectStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Parse(HSTRING input, _di_Json_IJsonObject &__Parse_result) = 0 ;
	virtual HRESULT __safecall TryParse(HSTRING input, /* out */ _di_Json_IJsonObject &a_result, bool &__TryParse_result) = 0 ;
};

__interface  INTERFACE_UUID("{DB1434A9-E164-499F-93E2-8A8F49BB90BA}") Json_IJsonArrayStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Parse(HSTRING input, _di_Json_IJsonArray &__Parse_result) = 0 ;
	virtual HRESULT __safecall TryParse(HSTRING input, /* out */ _di_Json_IJsonArray &a_result, bool &__TryParse_result) = 0 ;
};

__interface  INTERFACE_UUID("{404030DA-87D0-436C-83AB-FC7B12C0CC26}") Json_IJsonErrorStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetJsonStatus(int hresult, Winapi::Commontypes::Json_JsonErrorStatus &__GetJsonStatus_result) = 0 ;
};

__interface  INTERFACE_UUID("{3833A35E-2C61-56BD-B093-3694165F8898}") IIterator_1__Xml_Dom_IXmlNode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{3833A35E-2C61-56BD-B093-3694165F8898}") IIterator_1__Xml_Dom_IXmlNode  : public IIterator_1__Xml_Dom_IXmlNode_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_Xml_Dom_IXmlNode &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PXml_Dom_IXmlNode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_Xml_Dom_IXmlNode _scw_get_Current() { Winapi::Commontypes::_di_Xml_Dom_IXmlNode __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_Xml_Dom_IXmlNode Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{63DBBA8B-D0DB-4FE1-B745-F9433AFDC25B}") Xml_Dom_IXmlNodeSelector  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SelectSingleNode(HSTRING xpath, Winapi::Commontypes::_di_Xml_Dom_IXmlNode &__SelectSingleNode_result) = 0 ;
	virtual HRESULT __safecall SelectNodes(HSTRING xpath, Winapi::Commontypes::_di_Xml_Dom_IXmlNodeList &__SelectNodes_result) = 0 ;
	virtual HRESULT __safecall SelectSingleNodeNS(HSTRING xpath, Winapi::Winrt::_di_IInspectable namespaces, Winapi::Commontypes::_di_Xml_Dom_IXmlNode &__SelectSingleNodeNS_result) = 0 ;
	virtual HRESULT __safecall SelectNodesNS(HSTRING xpath, Winapi::Winrt::_di_IInspectable namespaces, Winapi::Commontypes::_di_Xml_Dom_IXmlNodeList &__SelectNodesNS_result) = 0 ;
};

__interface  INTERFACE_UUID("{5CC5B382-E6DD-4991-ABEF-06D8D2E7BD0C}") Xml_Dom_IXmlNodeSerializer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetXml(HSTRING &__GetXml_result) = 0 ;
	virtual HRESULT __safecall get_InnerText(HSTRING &__get_InnerText_result) = 0 ;
	virtual HRESULT __safecall put_InnerText(HSTRING value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_InnerText() { HSTRING __r; HRESULT __hr = get_InnerText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING InnerText = {read=_scw_get_InnerText, write=put_InnerText};
};

__interface  INTERFACE_UUID("{58AA07A8-FED6-46F7-B4C5-FB1BA72108D6}") Xml_Dom_IXmlLoadSettings  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_MaxElementDepth(unsigned &__get_MaxElementDepth_result) = 0 ;
	virtual HRESULT __safecall put_MaxElementDepth(unsigned value) = 0 ;
	virtual HRESULT __safecall get_ProhibitDtd(bool &__get_ProhibitDtd_result) = 0 ;
	virtual HRESULT __safecall put_ProhibitDtd(bool value) = 0 ;
	virtual HRESULT __safecall get_ResolveExternals(bool &__get_ResolveExternals_result) = 0 ;
	virtual HRESULT __safecall put_ResolveExternals(bool value) = 0 ;
	virtual HRESULT __safecall get_ValidateOnParse(bool &__get_ValidateOnParse_result) = 0 ;
	virtual HRESULT __safecall put_ValidateOnParse(bool value) = 0 ;
	virtual HRESULT __safecall get_ElementContentWhiteSpace(bool &__get_ElementContentWhiteSpace_result) = 0 ;
	virtual HRESULT __safecall put_ElementContentWhiteSpace(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_ElementContentWhiteSpace() { bool __r; HRESULT __hr = get_ElementContentWhiteSpace(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool ElementContentWhiteSpace = {read=_scw_get_ElementContentWhiteSpace, write=put_ElementContentWhiteSpace};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_MaxElementDepth() { unsigned __r; HRESULT __hr = get_MaxElementDepth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned MaxElementDepth = {read=_scw_get_MaxElementDepth, write=put_MaxElementDepth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_ProhibitDtd() { bool __r; HRESULT __hr = get_ProhibitDtd(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool ProhibitDtd = {read=_scw_get_ProhibitDtd, write=put_ProhibitDtd};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_ResolveExternals() { bool __r; HRESULT __hr = get_ResolveExternals(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool ResolveExternals = {read=_scw_get_ResolveExternals, write=put_ResolveExternals};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_ValidateOnParse() { bool __r; HRESULT __hr = get_ValidateOnParse(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool ValidateOnParse = {read=_scw_get_ValidateOnParse, write=put_ValidateOnParse};
};

__interface  INTERFACE_UUID("{BF666554-7605-5D9A-B14E-18D8C8472AFE}") AsyncOperationProgressHandler_2__IBuffer__Cardinal  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__IBuffer__Cardinal asyncInfo, unsigned progressInfo) = 0 ;
};

__interface  INTERFACE_UUID("{06386A7A-E009-5B0B-AB68-A8E48B516647}") AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__IBuffer__Cardinal asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{D26B2819-897F-5C7D-84D6-56D796561431}") IAsyncOperationWithProgress_2__IBuffer__Cardinal  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Progress(_di_AsyncOperationProgressHandler_2__IBuffer__Cardinal handler) = 0 ;
	virtual HRESULT __safecall get_Progress(_di_AsyncOperationProgressHandler_2__IBuffer__Cardinal &__get_Progress_result) = 0 ;
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IBuffer &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal _scw_get_Progress() { _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal __r; HRESULT __hr = get_Progress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal Progress = {read=_scw_get_Progress, write=put_Progress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal _scw_get_Completed() { _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{EA0FE405-D432-5AC7-9EF8-5A65E1F97D7E}") AsyncOperationProgressHandler_2__Cardinal__Cardinal  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__Cardinal__Cardinal asyncInfo, unsigned progressInfo) = 0 ;
};

__interface  INTERFACE_UUID("{1E466DC5-840F-54F9-B877-5E3A9F4B6C74}") AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__Cardinal__Cardinal asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{ECCB574A-C684-5572-A679-6B0842CFB57F}") IAsyncOperationWithProgress_2__Cardinal__Cardinal  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Progress(_di_AsyncOperationProgressHandler_2__Cardinal__Cardinal handler) = 0 ;
	virtual HRESULT __safecall get_Progress(_di_AsyncOperationProgressHandler_2__Cardinal__Cardinal &__get_Progress_result) = 0 ;
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(unsigned &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationProgressHandler_2__Cardinal__Cardinal _scw_get_Progress() { _di_AsyncOperationProgressHandler_2__Cardinal__Cardinal __r; HRESULT __hr = get_Progress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationProgressHandler_2__Cardinal__Cardinal Progress = {read=_scw_get_Progress, write=put_Progress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal _scw_get_Completed() { _di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{C1D3D1A2-AE17-5A5F-B5A2-BDCC8844889A}") AsyncOperationCompletedHandler_1__Boolean  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__Boolean asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{CDB5EFB3-5788-509D-9BE1-71CCB8A3362A}") IAsyncOperation_1__Boolean  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__Boolean handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__Boolean &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(bool &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__Boolean _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__Boolean __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__Boolean Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{6CD0E74E-EE65-4489-9EBF-CA43E87BA637}") Xml_Dom_IXmlDocumentIO  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall LoadXml(HSTRING xml) = 0 /* overload */;
	virtual HRESULT __safecall LoadXml(HSTRING xml, _di_Xml_Dom_IXmlLoadSettings loadSettings) = 0 /* overload */;
	virtual HRESULT __safecall SaveToFileAsync(Winapi::Commontypes::_di_IStorageFile file, Winapi::Commontypes::_di_IAsyncAction &__SaveToFileAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{5D034661-7BD8-4AD5-9EBF-81E6347263B1}") Xml_Dom_IXmlDocumentIO2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall LoadXmlFromBuffer(Winapi::Commontypes::_di_IBuffer buffer) = 0 /* overload */;
	virtual HRESULT __safecall LoadXmlFromBuffer(Winapi::Commontypes::_di_IBuffer buffer, _di_Xml_Dom_IXmlLoadSettings loadSettings) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{5EEF7817-93DD-5C0B-9E5A-EB490408F3A9}") AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{4D733BCA-331A-59A6-8361-D703C963C6D1}") AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument  : public AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__Xml_Dom_IXmlDocument asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{F858E239-1896-5982-8495-143168478EB8}") IAsyncOperation_1__Xml_Dom_IXmlDocument_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA3E8F7C-BBE4-5C32-B42F-CBA0C469E42C}") IAsyncOperation_1__Xml_Dom_IXmlDocument  : public IAsyncOperation_1__Xml_Dom_IXmlDocument_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_Xml_Dom_IXmlDocument &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__Xml_Dom_IXmlDocument Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{5543D254-D757-4B79-9539-232B18F50BF1}") Xml_Dom_IXmlDocumentStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall LoadFromUriAsync(Winapi::Commontypes::_di_IUriRuntimeClass uri, _di_IAsyncOperation_1__Xml_Dom_IXmlDocument &__LoadFromUriAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall LoadFromUriAsync(Winapi::Commontypes::_di_IUriRuntimeClass uri, _di_Xml_Dom_IXmlLoadSettings loadSettings, _di_IAsyncOperation_1__Xml_Dom_IXmlDocument &__LoadFromUriAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall LoadFromFileAsync(Winapi::Commontypes::_di_IStorageFile file, _di_IAsyncOperation_1__Xml_Dom_IXmlDocument &__LoadFromFileAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall LoadFromFileAsync(Winapi::Commontypes::_di_IStorageFile file, _di_Xml_Dom_IXmlLoadSettings loadSettings, _di_IAsyncOperation_1__Xml_Dom_IXmlDocument &__LoadFromFileAsync_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{97909E87-9291-4F91-B6C8-B6E359D7A7FB}") Text_IUnicodeCharactersStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetCodepointFromSurrogatePair(unsigned highSurrogate, unsigned lowSurrogate, unsigned &__GetCodepointFromSurrogatePair_result) = 0 ;
	virtual HRESULT __safecall GetSurrogatePairFromCodepoint(unsigned codepoint, /* out */ System::WideChar &highSurrogate, /* out */ System::WideChar &lowSurrogate) = 0 ;
	virtual HRESULT __safecall IsHighSurrogate(unsigned codepoint, bool &__IsHighSurrogate_result) = 0 ;
	virtual HRESULT __safecall IsLowSurrogate(unsigned codepoint, bool &__IsLowSurrogate_result) = 0 ;
	virtual HRESULT __safecall IsSupplementary(unsigned codepoint, bool &__IsSupplementary_result) = 0 ;
	virtual HRESULT __safecall IsNoncharacter(unsigned codepoint, bool &__IsNoncharacter_result) = 0 ;
	virtual HRESULT __safecall IsWhitespace(unsigned codepoint, bool &__IsWhitespace_result) = 0 ;
	virtual HRESULT __safecall IsAlphabetic(unsigned codepoint, bool &__IsAlphabetic_result) = 0 ;
	virtual HRESULT __safecall IsCased(unsigned codepoint, bool &__IsCased_result) = 0 ;
	virtual HRESULT __safecall IsUppercase(unsigned codepoint, bool &__IsUppercase_result) = 0 ;
	virtual HRESULT __safecall IsLowercase(unsigned codepoint, bool &__IsLowercase_result) = 0 ;
	virtual HRESULT __safecall IsIdStart(unsigned codepoint, bool &__IsIdStart_result) = 0 ;
	virtual HRESULT __safecall IsIdContinue(unsigned codepoint, bool &__IsIdContinue_result) = 0 ;
	virtual HRESULT __safecall IsGraphemeBase(unsigned codepoint, bool &__IsGraphemeBase_result) = 0 ;
	virtual HRESULT __safecall IsGraphemeExtend(unsigned codepoint, bool &__IsGraphemeExtend_result) = 0 ;
	virtual HRESULT __safecall GetNumericType(unsigned codepoint, Winapi::Commontypes::Text_UnicodeNumericType &__GetNumericType_result) = 0 ;
	virtual HRESULT __safecall GetGeneralCategory(unsigned codepoint, Winapi::Commontypes::Text_UnicodeGeneralCategory &__GetGeneralCategory_result) = 0 ;
};

__interface  INTERFACE_UUID("{47396C1E-51B9-4207-9146-248E636A1D1D}") Text_IAlternateWordForm  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_SourceTextSegment(Winapi::Commontypes::Text_TextSegment &__get_SourceTextSegment_result) = 0 ;
	virtual HRESULT __safecall get_AlternateText(HSTRING &__get_AlternateText_result) = 0 ;
	virtual HRESULT __safecall get_NormalizationFormat(Winapi::Commontypes::Text_AlternateNormalizationFormat &__get_NormalizationFormat_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AlternateText() { HSTRING __r; HRESULT __hr = get_AlternateText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AlternateText = {read=_scw_get_AlternateText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Text_AlternateNormalizationFormat _scw_get_NormalizationFormat() { Winapi::Commontypes::Text_AlternateNormalizationFormat __r; HRESULT __hr = get_NormalizationFormat(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Text_AlternateNormalizationFormat NormalizationFormat = {read=_scw_get_NormalizationFormat};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Text_TextSegment _scw_get_SourceTextSegment() { Winapi::Commontypes::Text_TextSegment __r; HRESULT __hr = get_SourceTextSegment(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Text_TextSegment SourceTextSegment = {read=_scw_get_SourceTextSegment};
};

__interface  INTERFACE_UUID("{916A4CB7-8AA7-4C78-B374-5DEDB752E60B}") Text_ISelectableWordSegment  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Text(HSTRING &__get_Text_result) = 0 ;
	virtual HRESULT __safecall get_SourceTextSegment(Winapi::Commontypes::Text_TextSegment &__get_SourceTextSegment_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Text_TextSegment _scw_get_SourceTextSegment() { Winapi::Commontypes::Text_TextSegment __r; HRESULT __hr = get_SourceTextSegment(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Text_TextSegment SourceTextSegment = {read=_scw_get_SourceTextSegment};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Text() { HSTRING __r; HRESULT __hr = get_Text(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Text = {read=_scw_get_Text};
};

__interface  INTERFACE_UUID("{7F463F8A-E08F-516E-B4B8-81B5417BFB58}") IIterator_1__Text_IAlternateWordForm_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{0D806514-0F6A-5579-BC4C-BF0B91C511E2}") IIterator_1__Text_IAlternateWordForm  : public IIterator_1__Text_IAlternateWordForm_Base 
{
	virtual HRESULT __safecall get_Current(_di_Text_IAlternateWordForm &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PText_IAlternateWordForm items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Text_IAlternateWordForm _scw_get_Current() { _di_Text_IAlternateWordForm __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Text_IAlternateWordForm Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{AE838C29-60C1-5093-AE61-0ED22857DB05}") IIterable_1__Text_IAlternateWordForm_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{3A8C90F6-6AAC-5697-8EF8-ECDB54D25DDF}") IIterable_1__Text_IAlternateWordForm  : public IIterable_1__Text_IAlternateWordForm_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Text_IAlternateWordForm &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{118A250E-A55C-5CF2-ABF9-0FAE89D20E85}") IVectorView_1__Text_IAlternateWordForm  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_Text_IAlternateWordForm &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_Text_IAlternateWordForm value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PText_IAlternateWordForm items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{D2D4BA6D-987C-4CC0-B6BD-D49A11B38F9A}") Text_IWordSegment  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Text(HSTRING &__get_Text_result) = 0 ;
	virtual HRESULT __safecall get_SourceTextSegment(Winapi::Commontypes::Text_TextSegment &__get_SourceTextSegment_result) = 0 ;
	virtual HRESULT __safecall get_AlternateForms(_di_IVectorView_1__Text_IAlternateWordForm &__get_AlternateForms_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__Text_IAlternateWordForm _scw_get_AlternateForms() { _di_IVectorView_1__Text_IAlternateWordForm __r; HRESULT __hr = get_AlternateForms(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__Text_IAlternateWordForm AlternateForms = {read=_scw_get_AlternateForms};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Text_TextSegment _scw_get_SourceTextSegment() { Winapi::Commontypes::Text_TextSegment __r; HRESULT __hr = get_SourceTextSegment(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Text_TextSegment SourceTextSegment = {read=_scw_get_SourceTextSegment};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Text() { HSTRING __r; HRESULT __hr = get_Text(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Text = {read=_scw_get_Text};
};

__interface  INTERFACE_UUID("{AEB846B3-664B-545E-AB93-F5FC66D24E32}") IIterator_1__Text_IWordSegment_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{5AE16A4D-93C9-57B6-8811-249A7E7C07A0}") IIterator_1__Text_IWordSegment  : public IIterator_1__Text_IWordSegment_Base 
{
	virtual HRESULT __safecall get_Current(_di_Text_IWordSegment &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PText_IWordSegment items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Text_IWordSegment _scw_get_Current() { _di_Text_IWordSegment __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Text_IWordSegment Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{D14DC94A-A311-5DDC-BF8B-D58795D87D6D}") IIterable_1__Text_IWordSegment_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{DE2D0496-8160-501B-825B-933D35601BA4}") IIterable_1__Text_IWordSegment  : public IIterable_1__Text_IWordSegment_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Text_IWordSegment &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{A5DD6357-BF2A-4C4F-A31F-29E71C6F8B35}") Text_WordSegmentsTokenizingHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IIterable_1__Text_IWordSegment precedingWords, _di_IIterable_1__Text_IWordSegment words) = 0 ;
};

__interface  INTERFACE_UUID("{F931F534-BDA4-593C-97C1-072B3CDB05E9}") IVectorView_1__Text_IWordSegment  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_Text_IWordSegment &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_Text_IWordSegment value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PText_IWordSegment items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{86B4D4D1-B2FE-4E34-A81D-66640300454F}") Text_IWordsSegmenter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ResolvedLanguage(HSTRING &__get_ResolvedLanguage_result) = 0 ;
	virtual HRESULT __safecall GetTokenAt(HSTRING text, unsigned startIndex, _di_Text_IWordSegment &__GetTokenAt_result) = 0 ;
	virtual HRESULT __safecall GetTokens(HSTRING text, _di_IVectorView_1__Text_IWordSegment &__GetTokens_result) = 0 ;
	virtual HRESULT __safecall Tokenize(HSTRING text, unsigned startIndex, _di_Text_WordSegmentsTokenizingHandler handler) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ResolvedLanguage() { HSTRING __r; HRESULT __hr = get_ResolvedLanguage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ResolvedLanguage = {read=_scw_get_ResolvedLanguage};
};

__interface  INTERFACE_UUID("{E6977274-FC35-455C-8BFB-6D7F4653CA97}") Text_IWordsSegmenterFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateWithLanguage(HSTRING language, _di_Text_IWordsSegmenter &__CreateWithLanguage_result) = 0 ;
};

__interface  INTERFACE_UUID("{A5842459-147D-5A88-8F23-A3398AFD8A85}") IIterator_1__Text_ISelectableWordSegment_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{C0E508BB-A33E-5D60-B630-6F92DF91252C}") IIterator_1__Text_ISelectableWordSegment  : public IIterator_1__Text_ISelectableWordSegment_Base 
{
	virtual HRESULT __safecall get_Current(_di_Text_ISelectableWordSegment &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PText_ISelectableWordSegment items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Text_ISelectableWordSegment _scw_get_Current() { _di_Text_ISelectableWordSegment __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Text_ISelectableWordSegment Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{784B0CEC-1348-5334-91E5-2E013294E211}") IIterable_1__Text_ISelectableWordSegment_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{01806953-9F16-574D-B498-A026DCA5D767}") IIterable_1__Text_ISelectableWordSegment  : public IIterable_1__Text_ISelectableWordSegment_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Text_ISelectableWordSegment &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{3A3DFC9C-AEDE-4DC7-9E6C-41C044BD3592}") Text_SelectableWordSegmentsTokenizingHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IIterable_1__Text_ISelectableWordSegment precedingWords, _di_IIterable_1__Text_ISelectableWordSegment words) = 0 ;
};

__interface  INTERFACE_UUID("{08BCD90D-CDB2-5FE6-B17D-8675BDF1482A}") IVectorView_1__Text_ISelectableWordSegment  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_Text_ISelectableWordSegment &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_Text_ISelectableWordSegment value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PText_ISelectableWordSegment items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{F6DC31E7-4B13-45C5-8897-7D71269E085D}") Text_ISelectableWordsSegmenter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ResolvedLanguage(HSTRING &__get_ResolvedLanguage_result) = 0 ;
	virtual HRESULT __safecall GetTokenAt(HSTRING text, unsigned startIndex, _di_Text_ISelectableWordSegment &__GetTokenAt_result) = 0 ;
	virtual HRESULT __safecall GetTokens(HSTRING text, _di_IVectorView_1__Text_ISelectableWordSegment &__GetTokens_result) = 0 ;
	virtual HRESULT __safecall Tokenize(HSTRING text, unsigned startIndex, _di_Text_SelectableWordSegmentsTokenizingHandler handler) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ResolvedLanguage() { HSTRING __r; HRESULT __hr = get_ResolvedLanguage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ResolvedLanguage = {read=_scw_get_ResolvedLanguage};
};

__interface  INTERFACE_UUID("{8C7A7648-6057-4339-BC70-F210010A4150}") Text_ISelectableWordsSegmenterFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateWithLanguage(HSTRING language, _di_Text_ISelectableWordsSegmenter &__CreateWithLanguage_result) = 0 ;
};

__interface  INTERFACE_UUID("{8C304EBB-6615-50A4-8829-879ECD443236}") IIterator_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Current(HSTRING &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Winrt::PHSTRING items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Current() { HSTRING __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{E2FCC7C1-3BFC-5A0B-B2B0-72E769D1CB7E}") IIterable_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall First(_di_IIterator_1__HSTRING &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{2F13C006-A03A-5F69-B090-75A43E33423E}") IVectorView_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, HSTRING &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(HSTRING value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Winrt::PHSTRING items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{7C7899BE-5F2E-5BF3-ADE5-AD98B772C7CD}") AsyncOperationCompletedHandler_1__IVectorView_1__HSTRING  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__HSTRING asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{2F92B529-119B-575A-A419-3904B4E41AF2}") IAsyncOperation_1__IVectorView_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__HSTRING handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__HSTRING &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__HSTRING &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__HSTRING _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__HSTRING __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__HSTRING Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{B79A741F-7FB5-50AE-9E99-911201EC3D41}") AsyncOperationCompletedHandler_1__HSTRING  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__HSTRING asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{3E1FE603-F897-5263-B328-0806426B8A79}") IAsyncOperation_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__HSTRING handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__HSTRING &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(HSTRING &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__HSTRING _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__HSTRING __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__HSTRING Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{9362A40A-9B7A-4569-94CF-D84F2F38CF9B}") Text_ITextPhoneme  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DisplayText(HSTRING &__get_DisplayText_result) = 0 ;
	virtual HRESULT __safecall get_ReadingText(HSTRING &__get_ReadingText_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DisplayText() { HSTRING __r; HRESULT __hr = get_DisplayText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DisplayText = {read=_scw_get_DisplayText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ReadingText() { HSTRING __r; HRESULT __hr = get_ReadingText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ReadingText = {read=_scw_get_ReadingText};
};

__interface  INTERFACE_UUID("{36426C36-B5C4-5D1B-A468-AFF3B48B7C3A}") IIterator_1__Text_ITextPhoneme_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{4E72A6A6-1069-50AB-AD0F-DEB9E7EBDC16}") IIterator_1__Text_ITextPhoneme  : public IIterator_1__Text_ITextPhoneme_Base 
{
	virtual HRESULT __safecall get_Current(_di_Text_ITextPhoneme &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PText_ITextPhoneme items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Text_ITextPhoneme _scw_get_Current() { _di_Text_ITextPhoneme __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Text_ITextPhoneme Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{2017F561-8162-55F8-B056-656636935815}") IIterable_1__Text_ITextPhoneme_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{D7DA1415-771F-5C33-A51C-AB3E83E49D5F}") IIterable_1__Text_ITextPhoneme  : public IIterable_1__Text_ITextPhoneme_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Text_ITextPhoneme &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{999FAB8C-F583-571B-A856-DAC177FC85F9}") IVectorView_1__Text_ITextPhoneme  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_Text_ITextPhoneme &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_Text_ITextPhoneme value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PText_ITextPhoneme items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{83E14307-0BE1-5560-8BFC-291095CF6D30}") AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{B7D8CB4A-CFD5-568B-ACF3-EC639BE99911}") AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme  : public AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__Text_ITextPhoneme asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{6BC3019D-DD10-5510-B164-808C232B7D64}") IAsyncOperation_1__IVectorView_1__Text_ITextPhoneme_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{C4BE9346-FA66-564C-98C0-725092640F4F}") IAsyncOperation_1__IVectorView_1__Text_ITextPhoneme  : public IAsyncOperation_1__IVectorView_1__Text_ITextPhoneme_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__Text_ITextPhoneme &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__Text_ITextPhoneme Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{55F778D6-F408-5E83-84AA-7E359540639A}") IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Key(HSTRING &__get_Key_result) = 0 ;
	virtual HRESULT __safecall get_Value(_di_IVectorView_1__Text_TextSegment &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Key() { HSTRING __r; HRESULT __hr = get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Key = {read=_scw_get_Key};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__Text_TextSegment _scw_get_Value() { _di_IVectorView_1__Text_TextSegment __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__Text_TextSegment Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{00078AA3-8676-5F06-ADF5-FFE5D661D670}") IIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{87CF56D8-0231-5FC8-8E9D-E06E7237F991}") IIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment  : public IIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment_Base 
{
	virtual HRESULT __safecall get_Current(_di_IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment _scw_get_Current() { _di_IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{F819A276-B3F5-54D4-B8FD-C9ADB7F700E3}") IIterable_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{09FC0D28-9CF3-5562-8129-3EE9B34BB332}") IIterable_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment  : public IIterable_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IKeyValuePair_2__HSTRING__IVectorView_1__Text_TextSegment &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{91D443D6-3777-5102-B0BC-3D4183A26FF9}") IMapView_2__HSTRING__IVectorView_1__Text_TextSegment_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{61C67A85-7658-508B-A585-D9DEFFED6302}") IMapView_2__HSTRING__IVectorView_1__Text_TextSegment  : public IMapView_2__HSTRING__IVectorView_1__Text_TextSegment_Base 
{
	virtual HRESULT __safecall Lookup(HSTRING key, _di_IVectorView_1__Text_TextSegment &__Lookup_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall HasKey(HSTRING key, bool &__HasKey_result) = 0 ;
	virtual HRESULT __safecall Split(/* out */ _di_IMapView_2__HSTRING__IVectorView_1__Text_TextSegment &first, /* out */ _di_IMapView_2__HSTRING__IVectorView_1__Text_TextSegment &second) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{DD54B51A-FF01-544B-9FA7-A6213845628C}") IMap_2__HSTRING__IVectorView_1__Text_TextSegment  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Lookup(HSTRING key, _di_IVectorView_1__Text_TextSegment &__Lookup_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall HasKey(HSTRING key, bool &__HasKey_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IMapView_2__HSTRING__IVectorView_1__Text_TextSegment &__GetView_result) = 0 ;
	virtual HRESULT __safecall Insert(HSTRING key, _di_IVectorView_1__Text_TextSegment value, bool &__Insert_result) = 0 ;
	virtual HRESULT __safecall Remove(HSTRING key) = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJson_JsonArray : public System::Win::Winrt::TWinRTGenericImportSI__2<_di_Json_IJsonArrayStatics,_di_Json_IJsonArray>
{
	typedef System::Win::Winrt::TWinRTGenericImportSI__2<_di_Json_IJsonArrayStatics,_di_Json_IJsonArray> inherited;
	
public:
	static _di_Json_IJsonArray __fastcall Parse(HSTRING input);
	static bool __fastcall TryParse(HSTRING input, /* out */ _di_Json_IJsonArray &a_result);
public:
	/* TObject.Create */ inline __fastcall TJson_JsonArray() : System::Win::Winrt::TWinRTGenericImportSI__2<_di_Json_IJsonArrayStatics,_di_Json_IJsonArray>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJson_JsonArray() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJson_JsonObject : public System::Win::Winrt::TWinRTGenericImportSI__2<_di_Json_IJsonObjectStatics,_di_Json_IJsonObject>
{
	typedef System::Win::Winrt::TWinRTGenericImportSI__2<_di_Json_IJsonObjectStatics,_di_Json_IJsonObject> inherited;
	
public:
	static _di_Json_IJsonObject __fastcall Parse(HSTRING input);
	static bool __fastcall TryParse(HSTRING input, /* out */ _di_Json_IJsonObject &a_result);
public:
	/* TObject.Create */ inline __fastcall TJson_JsonObject() : System::Win::Winrt::TWinRTGenericImportSI__2<_di_Json_IJsonObjectStatics,_di_Json_IJsonObject>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJson_JsonObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJson_JsonValue : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_Json_IJsonValueStatics,_di_Json_IJsonValueStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_Json_IJsonValueStatics,_di_Json_IJsonValueStatics2> inherited;
	
public:
	static _di_Json_IJsonValue __fastcall CreateNullValue();
	static _di_Json_IJsonValue __fastcall Parse(HSTRING input);
	static bool __fastcall TryParse(HSTRING input, /* out */ _di_Json_IJsonValue &a_result);
	static _di_Json_IJsonValue __fastcall CreateBooleanValue(bool input);
	static _di_Json_IJsonValue __fastcall CreateNumberValue(double input);
	static _di_Json_IJsonValue __fastcall CreateStringValue(HSTRING input);
public:
	/* TObject.Create */ inline __fastcall TJson_JsonValue() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_Json_IJsonValueStatics,_di_Json_IJsonValueStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJson_JsonValue() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJson_JsonError : public System::Win::Winrt::TWinRTGenericImportS__1<_di_Json_IJsonErrorStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_Json_IJsonErrorStatics2> inherited;
	
public:
	static Winapi::Commontypes::Json_JsonErrorStatus __fastcall GetJsonStatus(int hresult);
public:
	/* TObject.Create */ inline __fastcall TJson_JsonError() : System::Win::Winrt::TWinRTGenericImportS__1<_di_Json_IJsonErrorStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJson_JsonError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TXml_Dom_XmlDocument : public System::Win::Winrt::TWinRTGenericImportSI__2<_di_Xml_Dom_IXmlDocumentStatics,Winapi::Commontypes::_di_Xml_Dom_IXmlDocument>
{
	typedef System::Win::Winrt::TWinRTGenericImportSI__2<_di_Xml_Dom_IXmlDocumentStatics,Winapi::Commontypes::_di_Xml_Dom_IXmlDocument> inherited;
	
public:
	static _di_IAsyncOperation_1__Xml_Dom_IXmlDocument __fastcall LoadFromUriAsync(Winapi::Commontypes::_di_IUriRuntimeClass uri)/* overload */;
	static _di_IAsyncOperation_1__Xml_Dom_IXmlDocument __fastcall LoadFromUriAsync(Winapi::Commontypes::_di_IUriRuntimeClass uri, _di_Xml_Dom_IXmlLoadSettings loadSettings)/* overload */;
	static _di_IAsyncOperation_1__Xml_Dom_IXmlDocument __fastcall LoadFromFileAsync(Winapi::Commontypes::_di_IStorageFile file)/* overload */;
	static _di_IAsyncOperation_1__Xml_Dom_IXmlDocument __fastcall LoadFromFileAsync(Winapi::Commontypes::_di_IStorageFile file, _di_Xml_Dom_IXmlLoadSettings loadSettings)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TXml_Dom_XmlDocument() : System::Win::Winrt::TWinRTGenericImportSI__2<_di_Xml_Dom_IXmlDocumentStatics,Winapi::Commontypes::_di_Xml_Dom_IXmlDocument>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TXml_Dom_XmlDocument() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TText_UnicodeCharacters : public System::Win::Winrt::TWinRTGenericImportS__1<_di_Text_IUnicodeCharactersStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_Text_IUnicodeCharactersStatics> inherited;
	
public:
	static unsigned __fastcall GetCodepointFromSurrogatePair(unsigned highSurrogate, unsigned lowSurrogate);
	static void __fastcall GetSurrogatePairFromCodepoint(unsigned codepoint, /* out */ System::WideChar &highSurrogate, /* out */ System::WideChar &lowSurrogate);
	static bool __fastcall IsHighSurrogate(unsigned codepoint);
	static bool __fastcall IsLowSurrogate(unsigned codepoint);
	static bool __fastcall IsSupplementary(unsigned codepoint);
	static bool __fastcall IsNoncharacter(unsigned codepoint);
	static bool __fastcall IsWhitespace(unsigned codepoint);
	static bool __fastcall IsAlphabetic(unsigned codepoint);
	static bool __fastcall IsCased(unsigned codepoint);
	static bool __fastcall IsUppercase(unsigned codepoint);
	static bool __fastcall IsLowercase(unsigned codepoint);
	static bool __fastcall IsIdStart(unsigned codepoint);
	static bool __fastcall IsIdContinue(unsigned codepoint);
	static bool __fastcall IsGraphemeBase(unsigned codepoint);
	static bool __fastcall IsGraphemeExtend(unsigned codepoint);
	static Winapi::Commontypes::Text_UnicodeNumericType __fastcall GetNumericType(unsigned codepoint);
	static Winapi::Commontypes::Text_UnicodeGeneralCategory __fastcall GetGeneralCategory(unsigned codepoint);
public:
	/* TObject.Create */ inline __fastcall TText_UnicodeCharacters() : System::Win::Winrt::TWinRTGenericImportS__1<_di_Text_IUnicodeCharactersStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TText_UnicodeCharacters() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TText_WordsSegmenter : public System::Win::Winrt::TWinRTGenericImportF__1<_di_Text_IWordsSegmenterFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_Text_IWordsSegmenterFactory> inherited;
	
public:
	static _di_Text_IWordsSegmenter __fastcall CreateWithLanguage(HSTRING language);
public:
	/* TObject.Create */ inline __fastcall TText_WordsSegmenter() : System::Win::Winrt::TWinRTGenericImportF__1<_di_Text_IWordsSegmenterFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TText_WordsSegmenter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TText_SelectableWordsSegmenter : public System::Win::Winrt::TWinRTGenericImportF__1<_di_Text_ISelectableWordsSegmenterFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_Text_ISelectableWordsSegmenterFactory> inherited;
	
public:
	static _di_Text_ISelectableWordsSegmenter __fastcall CreateWithLanguage(HSTRING language);
public:
	/* TObject.Create */ inline __fastcall TText_SelectableWordsSegmenter() : System::Win::Winrt::TWinRTGenericImportF__1<_di_Text_ISelectableWordsSegmenterFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TText_SelectableWordsSegmenter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Datart */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_DatartHPP
