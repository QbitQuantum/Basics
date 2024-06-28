// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.XmlTransform.pas' rev: 34.00 (Windows)

#ifndef Xml_XmltransformHPP
#define Xml_XmltransformHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Xml.xmldom.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Xmltransform
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TranslateException;
class DELPHICLASS TXMLTransform;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TranslateException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall TranslateException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall TranslateException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall TranslateException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall TranslateException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall TranslateException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall TranslateException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall TranslateException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall TranslateException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TranslateException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TranslateException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TranslateException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TranslateException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~TranslateException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TTranslateEvent)(System::TObject* Sender, System::UnicodeString Id, Xml::Xmldom::_di_IDOMNode SrcNode, System::UnicodeString &Value, Xml::Xmldom::_di_IDOMNode DestNode);

typedef void __fastcall (__closure *TRowEvent)(System::TObject* Sender, System::UnicodeString Id, Xml::Xmldom::_di_IDOMNode SrcNode, Xml::Xmldom::_di_IDOMNode DestNode);

class PASCALIMPLEMENTATION TXMLTransform : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FEncoding;
	System::UnicodeString FEncodingTrans;
	bool FDirectionToCds;
	System::UnicodeString FVersion;
	System::UnicodeString FSourceXmlFile;
	Xml::Xmldom::_di_IDOMDocument FSourceXmlDocument;
	System::UnicodeString FSourceXml;
	System::UnicodeString FTransformationFile;
	Xml::Xmldom::_di_IDOMDocument FTransformationDocument;
	Xml::Xmldom::_di_IDOMDocument FEmptyDestinationDocument;
	Xml::Xmldom::_di_IDOMDocument FResultDocument;
	System::UnicodeString FResultString;
	TTranslateEvent FOnTranslate;
	TRowEvent FBeforeEachRow;
	TRowEvent FAfterEachRow;
	TRowEvent FBeforeEachRowSet;
	TRowEvent FAfterEachRowSet;
	
protected:
	DYNAMIC void __fastcall Translate(const System::UnicodeString Id, const Xml::Xmldom::_di_IDOMNode SrcNode, System::UnicodeString &SrcValue, const Xml::Xmldom::_di_IDOMNode DestNode);
	System::UnicodeString __fastcall DoTransform(const Xml::Xmldom::_di_IDOMDocument XMLSrc, const Xml::Xmldom::_di_IDOMDocument XMLExtract, const Xml::Xmldom::_di_IDOMDocument XMLOut);
	void __fastcall Transform(Xml::Xmldom::_di_IDOMNode TransNode, Xml::Xmldom::_di_IDOMNode SrcNode, Xml::Xmldom::_di_IDOMNode DestNode, int Count, System::Classes::TStringList* InFromList, System::Classes::TStringList* InDestList, System::Classes::TStringList* InIdStrList, System::Classes::TStringList* InValueList, System::Classes::TStringList* InOptionalList, System::Classes::TStringList* InDateFormatList, System::Classes::TStringList* InDateFormatTypeList, System::Classes::TStringList* InMapValuesList);
	System::UnicodeString __fastcall GetData();
	System::UnicodeString __fastcall GetResultString();
	
public:
	System::UnicodeString __fastcall TransformXML(const System::UnicodeString SourceXml, const System::UnicodeString ATransformationFile = System::UnicodeString());
	__property System::UnicodeString Data = {read=GetData};
	__property System::UnicodeString Encoding = {read=FEncoding};
	__property System::UnicodeString EncodingTrans = {read=FEncodingTrans};
	__property Xml::Xmldom::_di_IDOMDocument SourceXmlDocument = {read=FSourceXmlDocument, write=FSourceXmlDocument};
	__property System::UnicodeString SourceXmlFile = {read=FSourceXmlFile, write=FSourceXmlFile};
	__property System::UnicodeString SourceXml = {read=FSourceXml, write=FSourceXml};
	__property Xml::Xmldom::_di_IDOMDocument TransformationDocument = {read=FTransformationDocument, write=FTransformationDocument};
	__property Xml::Xmldom::_di_IDOMDocument EmptyDestinationDocument = {read=FEmptyDestinationDocument, write=FEmptyDestinationDocument};
	__property Xml::Xmldom::_di_IDOMDocument ResultDocument = {read=FResultDocument};
	__property System::UnicodeString ResultString = {read=GetResultString};
	
__published:
	__property System::UnicodeString TransformationFile = {read=FTransformationFile, write=FTransformationFile};
	__property TTranslateEvent OnTranslate = {read=FOnTranslate, write=FOnTranslate};
	__property TRowEvent BeforeEachRow = {read=FBeforeEachRow, write=FBeforeEachRow};
	__property TRowEvent AfterEachRow = {read=FAfterEachRow, write=FAfterEachRow};
	__property TRowEvent BeforeEachRowSet = {read=FBeforeEachRowSet, write=FBeforeEachRowSet};
	__property TRowEvent AfterEachRowSet = {read=FAfterEachRowSet, write=FAfterEachRowSet};
public:
	/* TComponent.Create */ inline __fastcall virtual TXMLTransform(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TXMLTransform() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Xmltransform */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_XMLTRANSFORM)
using namespace Xml::Xmltransform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_XmltransformHPP
