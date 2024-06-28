// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.XmlRulesUtils.pas' rev: 34.00 (Windows)

#ifndef Xml_Internal_XmlrulesutilsHPP
#define Xml_Internal_XmlrulesutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Xmlrulesutils
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::WideString __fastcall GetXmlWhitespaceWideString(void);
extern DELPHI_PACKAGE bool __fastcall IsXmlCharCodePoint(const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlWhiteSpaceCodePoint(const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlWhiteSpaceOrNullCodePoint(const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlLetterCodePoint _DEPRECATED_ATTRIBUTE0 (const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlBaseCharCodePoint _DEPRECATED_ATTRIBUTE0 (const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlHexDigitCodePoint(const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlIdeographicCodePoint _DEPRECATED_ATTRIBUTE0 (const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlCombiningCharCodePoint _DEPRECATED_ATTRIBUTE0 (const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlDecDigitCodePoint(const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlDigitCodePoint _DEPRECATED_ATTRIBUTE0 (const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlExtenderCodePoint _DEPRECATED_ATTRIBUTE0 (const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlNameCharCodePoint(const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlNameStartCharCodePoint(const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlEncNameLeadingCharCodePoint(const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlEncNameFollowingCharCodePoint(const int UCS4);
extern DELPHI_PACKAGE bool __fastcall IsXmlChar(const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlWhiteSpace(const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlWhiteSpaceOrNull(const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlLetter _DEPRECATED_ATTRIBUTE0 (const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlBaseChar _DEPRECATED_ATTRIBUTE0 (const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlIdeographic _DEPRECATED_ATTRIBUTE0 (const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlCombiningChar _DEPRECATED_ATTRIBUTE0 (const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlDigit _DEPRECATED_ATTRIBUTE0 (const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlExtender _DEPRECATED_ATTRIBUTE0 (const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlNameChar(const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlNameStartChar(const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlPubidChar(const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlChars(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlS(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlName(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlNames(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlNmtoken(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlNmtokens(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlCharRef(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlEntityRef(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlPEReference(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlReference(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlEntityValue(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlEntityValueChars(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlAttValue(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlSystemLiteral(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlSystemChars(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlPubidLiteral(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlPredefinedEntityName(const System::WideString S);
extern DELPHI_PACKAGE System::WideString __fastcall XmlPredefinedEntityToStr(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlPubidChars(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlComment(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlCData(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlCharData(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlPITarget(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlVersionNum(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlEncName(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlStringType(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlTokenizedType(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlNCNameChar(const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlNCNameStartChar(const System::WideChar S);
extern DELPHI_PACKAGE bool __fastcall IsXmlNCName(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlDefaultAttName(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlPrefixedAttName(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlNSAttName(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlLocalPart(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlPrefix(const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsXmlQName(const System::WideString S);
}	/* namespace Xmlrulesutils */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_XMLRULESUTILS)
using namespace Xml::Internal::Xmlrulesutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL)
using namespace Xml::Internal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Internal_XmlrulesutilsHPP
