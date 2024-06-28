// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.xmlutil.pas' rev: 34.00 (Windows)

#ifndef Xml_XmlutilHPP
#define Xml_XmlutilHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Xml.xmldom.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Xmlutil
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS DomException;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DomException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall DomException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall DomException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall DomException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall DomException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall DomException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall DomException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall DomException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall DomException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall DomException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall DomException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall DomException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall DomException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~DomException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define mx_Root L"XmlTransformation"
#define mx_Transform L"Transform"
#define mx_Skeleton L"Skeleton"
#define mx_TranslateEach L"SelectEach"
#define mx_Translate L"Select"
#define mx_XmlSchema L"XmlSchema"
#define mx_CdsSkeleton L"CdsSkeleton"
#define mx_XmlSkeleton L"XmlSkeleton"
#define mx_XSLTransform L"XslTransform"
#define mx_Version L"Version"
#define mx_CurrVersion L"1.0"
#define mx_RootName L"RootName"
#define mx_DataEncoding L"DataEncoding"
#define mx_Direction L"Direction"
#define mx_ToXml L"ToXml"
#define mx_ToCds L"ToCds"
#define mx_ID L"id"
#define mx_DEFAULT L"Default"
#define mx_VALUE L"value"
#define mx_OPTIONS L"Options"
#define mx_MAPVALUES L"Map_Values"
#define mx_BOOLFORMAT L"Format_Bool"
#define mx_OPTIONAL L"Optional"
#define mx_DEST L"dest"
#define mx_FROM L"from"
#define mx_DATETIMEFORMAT L"Format_DateTime"
#define mx_DATEFORMAT L"Format_Date"
#define mx_TIMEFORMAT L"Format_Time"
#define mx_Datapacket L"DATAPACKET"
#define mx_ROWDATA L"ROWDATA"
#define mx_ROW L"ROW"
#define mx_RowState L"RowState"
#define val_DateTimeDefault L"Default Format"
extern DELPHI_PACKAGE Xml::Xmldom::_di_IDOMDocument __fastcall LoadDocFromFile(const System::UnicodeString XMLFile);
extern DELPHI_PACKAGE Xml::Xmldom::_di_IDOMDocument __fastcall LoadDocFromString(const System::UnicodeString XMLStr);
extern DELPHI_PACKAGE System::UnicodeString __fastcall getIndex_Attrs(System::UnicodeString tag, int &idx, System::UnicodeString &Attrs);
extern DELPHI_PACKAGE Xml::Xmldom::_di_IDOMNode __fastcall FindNode(Xml::Xmldom::_di_IDOMNode CurrEl, int currtag, System::Classes::TStrings* tags);
extern DELPHI_PACKAGE Xml::Xmldom::_di_IDOMNode __fastcall NextCreateElement(Xml::Xmldom::_di_IDOMNode El, System::UnicodeString tag, System::UnicodeString &attr);
extern DELPHI_PACKAGE Xml::Xmldom::_di_IDOMNode __fastcall SelectCreateNode(Xml::Xmldom::_di_IDOMNode Node, System::UnicodeString Path, System::UnicodeString &attrs);
extern DELPHI_PACKAGE Xml::Xmldom::_di_IDOMNode __fastcall SelectNode(Xml::Xmldom::_di_IDOMNode Node, System::UnicodeString Path);
extern DELPHI_PACKAGE Xml::Xmldom::_di_IDOMNode __fastcall SelectCreateSibling(Xml::Xmldom::_di_IDOMNode Node, Xml::Xmldom::_di_IDOMNode CloneNode);
extern DELPHI_PACKAGE void __fastcall PutValue(Xml::Xmldom::_di_IDOMNode Node, System::UnicodeString Path, System::UnicodeString value);
extern DELPHI_PACKAGE Xml::Xmldom::_di_IDOMDocument __fastcall CloneDoc(Xml::Xmldom::_di_IDOMDocument Doc);
extern DELPHI_PACKAGE System::Classes::TStringList* __fastcall Split0(System::UnicodeString Str, const System::UnicodeString substr);
extern DELPHI_PACKAGE System::UnicodeString __fastcall Head(System::UnicodeString s, const System::UnicodeString subs, System::UnicodeString &tail);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetAttribute(Xml::Xmldom::_di_IDOMNode Node, const System::UnicodeString name);
extern DELPHI_PACKAGE System::UnicodeString __fastcall StrToXmlDate(const System::UnicodeString DateStr, const System::UnicodeString Format);
extern DELPHI_PACKAGE System::UnicodeString __fastcall StrToXmlDateTime(const System::UnicodeString DateStr, const System::UnicodeString Format);
extern DELPHI_PACKAGE System::UnicodeString __fastcall StrToXmlTime(const System::UnicodeString TimeStr, const System::UnicodeString Format);
extern DELPHI_PACKAGE System::UnicodeString __fastcall XmlDateTimeToStr(const System::UnicodeString XmlDateTime, const System::UnicodeString Format);
extern DELPHI_PACKAGE System::UnicodeString __fastcall XmlTimeToStr(const System::UnicodeString XmlTime, const System::UnicodeString Format);
extern DELPHI_PACKAGE System::UnicodeString __fastcall MapDateTime(const System::UnicodeString DateFormatType, System::UnicodeString DateFormat, System::UnicodeString Value, bool ToCds);
extern DELPHI_PACKAGE System::UnicodeString __fastcall MakeValueMap(System::UnicodeString Enumeration, bool ToCds);
extern DELPHI_PACKAGE System::UnicodeString __fastcall MapValues(System::UnicodeString Mapping, System::UnicodeString Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetEncoding(Xml::Xmldom::_di_IDOMDocument Doc);
extern DELPHI_PACKAGE void __fastcall SetEncoding(Xml::Xmldom::_di_IDOMDocument Doc, System::UnicodeString Encoding, bool OverWrite);
extern DELPHI_PACKAGE void __fastcall SetStandalone(Xml::Xmldom::_di_IDOMDocument Doc, System::UnicodeString value);
extern DELPHI_PACKAGE Xml::Xmldom::_di_IDOMNode __fastcall CloneNodeToDoc(const Xml::Xmldom::_di_IDOMNode SourceNode, const Xml::Xmldom::_di_IDOMDocument TargetDoc, bool Deep = true);
extern DELPHI_PACKAGE System::UnicodeString __fastcall XmlFloatToStr(const System::Extended Value);
extern DELPHI_PACKAGE System::Extended __fastcall XmlStrToFloat(const System::UnicodeString Value);
extern DELPHI_PACKAGE System::Extended __fastcall XmlStrToFloatExt(const System::UnicodeString Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall XmlFloatToStrExt(const System::Extended Value);
}	/* namespace Xmlutil */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_XMLUTIL)
using namespace Xml::Xmlutil;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_XmlutilHPP
