// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.UriUtils.pas' rev: 34.00 (iOS)

#ifndef Xml_Internal_UriutilsHPP
#define Xml_Internal_UriutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Uriutils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TUriStrAnalyzer;
class DELPHICLASS TUriWideStrAnalyzer;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM Xml_Internal_Uriutils__1 : unsigned char { fuSetLocalhost, fuPlainColon };

typedef System::Set<Xml_Internal_Uriutils__1, Xml_Internal_Uriutils__1::fuSetLocalhost, Xml_Internal_Uriutils__1::fuPlainColon> TUtilsFilenameToUriOptions;

class PASCALIMPLEMENTATION TUriStrAnalyzer : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	System::UnicodeString FUriAuthority;
	System::UnicodeString FUriFragment;
	System::UnicodeString FUriQuery;
	System::UnicodeString FUriPath;
	System::UnicodeString FUriScheme;
	bool FHasUriAuthority;
	bool FHasUriFragment;
	bool FHasUriQuery;
	bool FHasUriScheme;
	virtual System::UnicodeString __fastcall GetUriReference();
	
public:
	__fastcall TUriStrAnalyzer();
	virtual bool __fastcall SetUriAuthority(const System::UnicodeString Value, const bool IsDefined);
	virtual bool __fastcall SetUriFragment(const System::UnicodeString Value, const bool IsDefined);
	virtual bool __fastcall SetUriPath(const System::UnicodeString Value);
	virtual bool __fastcall SetUriQuery(const System::UnicodeString Value, const bool IsDefined);
	virtual bool __fastcall SetUriReference(const System::UnicodeString Value);
	virtual bool __fastcall SetUriScheme(const System::UnicodeString Value, const bool IsDefined);
	__property bool HasUriAuthority = {read=FHasUriAuthority, nodefault};
	__property bool HasUriFragment = {read=FHasUriFragment, nodefault};
	__property bool HasUriQuery = {read=FHasUriQuery, nodefault};
	__property bool HasUriScheme = {read=FHasUriScheme, nodefault};
	__property System::UnicodeString UriAuthority = {read=FUriAuthority};
	__property System::UnicodeString UriFragment = {read=FUriFragment};
	__property System::UnicodeString UriPath = {read=FUriPath};
	__property System::UnicodeString UriQuery = {read=FUriQuery};
	__property System::UnicodeString UriReference = {read=GetUriReference};
	__property System::UnicodeString UriScheme = {read=FUriScheme};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUriStrAnalyzer() { }
	
};


class PASCALIMPLEMENTATION TUriWideStrAnalyzer : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	System::WideString FUriAuthority;
	System::WideString FUriFragment;
	System::WideString FUriQuery;
	System::WideString FUriPath;
	System::WideString FUriScheme;
	bool FHasUriAuthority;
	bool FHasUriFragment;
	bool FHasUriQuery;
	bool FHasUriScheme;
	virtual System::WideString __fastcall GetUriReference();
	
public:
	__fastcall TUriWideStrAnalyzer();
	virtual bool __fastcall SetUriAuthority(const System::WideString Value, const bool IsDefined);
	virtual bool __fastcall SetUriFragment(const System::WideString Value, const bool IsDefined);
	virtual bool __fastcall SetUriPath(const System::WideString Value);
	virtual bool __fastcall SetUriQuery(const System::WideString Value, const bool IsDefined);
	virtual bool __fastcall SetUriReference(const System::WideString Value);
	virtual bool __fastcall SetUriScheme(const System::WideString Value, const bool IsDefined);
	__property bool HasUriAuthority = {read=FHasUriAuthority, nodefault};
	__property bool HasUriFragment = {read=FHasUriFragment, nodefault};
	__property bool HasUriQuery = {read=FHasUriQuery, nodefault};
	__property bool HasUriScheme = {read=FHasUriScheme, nodefault};
	__property System::WideString UriAuthority = {read=FUriAuthority};
	__property System::WideString UriFragment = {read=FUriFragment};
	__property System::WideString UriPath = {read=FUriPath};
	__property System::WideString UriQuery = {read=FUriQuery};
	__property System::WideString UriReference = {read=GetUriReference};
	__property System::WideString UriScheme = {read=FUriScheme};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUriWideStrAnalyzer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall IsUriURI_referenceWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriAbsoluteURIWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriRelativeURIWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriHier_partWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriOpaque_partWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriNet_pathWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriAbs_pathWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriRel_pathWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriRel_segmentWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriSchemeWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriAuthorityWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriReg_nameWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriServerWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriUserinfoWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriHostPortWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriHostWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriHostnameWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriDomainlabelWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriToplabelWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriIPv4addressWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriPortWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriPathWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriPath_segmentsWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriSegmentWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriParamWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriQueryWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriFragmentWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriUricWideStr(System::WideString S);
extern DELPHI_PACKAGE bool __fastcall IsUriReservedWideChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriUnreservedWideChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriMarkWideChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriHexWideChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriAlphanumWideChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriAlphaWideChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriDigitWideChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriURI_referenceStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriAbsoluteURIStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriRelativeURIStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriHier_partStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriOpaque_partStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriNet_pathStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriAbs_pathStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriRel_pathStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriRel_segmentStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriSchemeStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriAuthorityStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriReg_nameStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriServerStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriUserinfoStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriHostPortStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriHostStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriHostnameStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriDomainlabelStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriToplabelStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriIPv4addressStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriPortStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriPathStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriPath_segmentsStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriSegmentStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriParamStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriQueryStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriFragmentStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriUricStr(System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsUriReservedChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriUnreservedChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriMarkChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriHexChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriAlphanumChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriAlphaChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall IsUriDigitChar(System::WideChar C);
extern DELPHI_PACKAGE bool __fastcall ResolveRelativeUriStr(const System::UnicodeString BaseUri, const System::UnicodeString RelUri, System::UnicodeString &ResultUri);
extern DELPHI_PACKAGE bool __fastcall ResolveRelativeUriWideStr(const System::WideString BaseUri, const System::WideString RelUri, System::WideString &ResultUri);
extern DELPHI_PACKAGE System::UnicodeString __fastcall FilenameToUriStr(const System::Sysutils::TFileName Path, const TUtilsFilenameToUriOptions Opt);
extern DELPHI_PACKAGE System::WideString __fastcall FilenameToUriWideStr(const System::Sysutils::TFileName Path, const TUtilsFilenameToUriOptions Opt);
extern DELPHI_PACKAGE bool __fastcall UriStrToFilename(const System::UnicodeString Uri, System::Sysutils::TFileName &Path, System::UnicodeString &Authority, System::UnicodeString &Query, System::UnicodeString &Fragment);
extern DELPHI_PACKAGE bool __fastcall UriWideStrToFilename(const System::WideString Uri, System::Sysutils::TFileName &Path, System::WideString &Authority, System::WideString &Query, System::WideString &Fragment);
}	/* namespace Uriutils */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_URIUTILS)
using namespace Xml::Internal::Uriutils;
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
#endif	// Xml_Internal_UriutilsHPP
