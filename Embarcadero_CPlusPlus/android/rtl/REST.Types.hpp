// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Types.pas' rev: 34.00 (Android)

#ifndef Rest_TypesHPP
#define Rest_TypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Math.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Types
{
//-- forward type declarations -----------------------------------------------
struct TExecutionPerformance;
class DELPHICLASS ERESTException;
class DELPHICLASS ERequestError;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TMethod)(void);

/* [Template Alias] */
#if defined(__clang__)
template<typename T> using TMethod__1 = void __fastcall (__closure *)(T Arg1);
#endif

typedef System::Sysutils::_di_TProc TCompletionHandler;

typedef System::DelphiInterface<System::Sysutils::TProc__1<System::TObject*> > TCompletionHandlerWithError;

enum DECLSPEC_DENUM TRESTObjectOwnership : unsigned char { ooCopy, ooREST, ooApp };

enum DECLSPEC_DENUM TRESTRequestParameterOption : unsigned char { poDoNotEncode, poTransient, poAutoCreated, poFlatArray, poPHPArray, poListArray };

typedef System::Set<TRESTRequestParameterOption, TRESTRequestParameterOption::poDoNotEncode, TRESTRequestParameterOption::poListArray> TRESTRequestParameterOptions;

enum DECLSPEC_DENUM TRESTRequestParameterKind : unsigned char { pkCOOKIE, pkGETorPOST, pkURLSEGMENT, pkHTTPHEADER, pkREQUESTBODY, pkFILE, pkQUERY };

enum DECLSPEC_DENUM TRESTContentType : unsigned char { ctNone, ctAPPLICATION_ATOM_XML, ctAPPLICATION_ECMASCRIPT, ctAPPLICATION_EDI_X12, ctAPPLICATION_EDIFACT, ctAPPLICATION_JSON, ctAPPLICATION_JAVASCRIPT, ctAPPLICATION_OCTET_STREAM, ctAPPLICATION_OGG, ctAPPLICATION_PDF, ctAPPLICATION_POSTSCRIPT, ctAPPLICATION_RDF_XML, ctAPPLICATION_RSS_XML, ctAPPLICATION_SOAP_XML, ctAPPLICATION_FONT_WOFF, ctAPPLICATION_XHTML_XML, ctAPPLICATION_XML, ctAPPLICATION_XML_DTD, ctAPPLICATION_XOP_XML, ctAPPLICATION_ZIP, ctAPPLICATION_GZIP, ctTEXT_CMD, ctTEXT_CSS, ctTEXT_CSV, ctTEXT_HTML, ctTEXT_JAVASCRIPT, ctTEXT_PLAIN, ctTEXT_VCARD, ctTEXT_XML, ctAUDIO_BASIC, ctAUDIO_L24, ctAUDIO_MP4, ctAUDIO_MPEG, ctAUDIO_OGG, ctAUDIO_VORBIS, ctAUDIO_VND_RN_REALAUDIO, ctAUDIO_VND_WAVE, 
	ctAUDIO_WEBM, ctIMAGE_GIF, ctIMAGE_JPEG, ctIMAGE_PJPEG, ctIMAGE_PNG, ctIMAGE_SVG_XML, ctIMAGE_TIFF, ctMESSAGE_HTTP, ctMESSAGE_IMDN_XML, ctMESSAGE_PARTIAL, ctMESSAGE_RFC822, ctMODEL_EXAMPLE, ctMODEL_IGES, ctMODEL_MESH, ctMODEL_VRML, ctMODEL_X3D_BINARY, ctMODEL_X3D_VRML, ctMODEL_X3D_XML, ctMULTIPART_MIXED, ctMULTIPART_ALTERNATIVE, ctMULTIPART_RELATED, ctMULTIPART_FORM_DATA, ctMULTIPART_SIGNED, ctMULTIPART_ENCRYPTED, ctVIDEO_MPEG, ctVIDEO_MP4, ctVIDEO_OGG, ctVIDEO_QUICKTIME, ctVIDEO_WEBM, ctVIDEO_X_MATROSKA, ctVIDEO_X_MS_WMV, ctVIDEO_X_FLV, ctAPPLICATION_VND_OASIS_OPENDOCUMENT_TEXT, ctAPPLICATION_VND_OASIS_OPENDOCUMENT_SPREADSHEET, ctAPPLICATION_VND_OASIS_OPENDOCUMENT_PRESENTATION, ctAPPLICATION_VND_OASIS_OPENDOCUMENT_GRAPHICS, ctAPPLICATION_VND_MS_EXCEL, 
	ctAPPLICATION_VND_OPENXMLFORMATS_OFFICEDOCUMENT_SPREADSHEETML_SHEET, ctAPPLICATION_VND_MS_POWERPOINT, ctAPPLICATION_VND_OPENXMLFORMATS_OFFICEDOCUMENT_PRESENTATIONML_PRESENTATION, ctAPPLICATION_VND_OPENXMLFORMATS_OFFICEDOCUMENT_WORDPROCESSINGML_DOCUMENT, ctAPPLICATION_VND_MOZILLA_XUL_XML, ctAPPLICATION_VND_GOOGLE_EARTH_KML_XML, ctAPPLICATION_VND_GOOGLE_EARTH_KMZ, ctAPPLICATION_VND_DART, ctAPPLICATION_VND_ANDROID_PACKAGE_ARCHIVE, ctAPPLICATION_X_DEB, ctAPPLICATION_X_DVI, ctAPPLICATION_X_FONT_TTF, ctAPPLICATION_X_JAVASCRIPT, ctAPPLICATION_X_LATEX, ctAPPLICATION_X_MPEGURL, ctAPPLICATION_X_RAR_COMPRESSED, ctAPPLICATION_X_SHOCKWAVE_FLASH, ctAPPLICATION_X_STUFFIT, ctAPPLICATION_X_TAR, ctAPPLICATION_X_WWW_FORM_URLENCODED, ctAPPLICATION_X_XPINSTALL, ctAUDIO_X_AAC, 
	ctAUDIO_X_CAF, ctIMAGE_X_XCF, ctTEXT_X_GWT_RPC, ctTEXT_X_JQUERY_TMPL, ctTEXT_X_MARKDOWN, ctAPPLICATION_X_PKCS12, ctAPPLICATION_X_PKCS7_CERTIFICATES, ctAPPLICATION_X_PKCS7_CERTREQRESP, ctAPPLICATION_X_PKCS7_MIME, ctAPPLICATION_X_PKCS7_SIGNATURE, ctAPPLICATION_VND_EMBARCADERO_FIREDAC_JSON };

struct DECLSPEC_DRECORD TExecutionPerformance
{
public:
	unsigned FStartTime;
	void __fastcall Start();
	void __fastcall Clear();
	void __fastcall PreProcessingDone();
	void __fastcall ExecutionDone();
	void __fastcall PostProcessingDone();
	int PreProcessingTime;
	int ExecutionTime;
	int PostProcessingTime;
	int __fastcall TotalExecutionTime();
};


enum DECLSPEC_DENUM TRESTRequestMethod : unsigned char { rmPOST, rmPUT, rmGET, rmDELETE, rmPATCH };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ERESTException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ERESTException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ERESTException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ERESTException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ERESTException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ERESTException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ERESTException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ERESTException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ERESTException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ERESTException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ERESTException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ERESTException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ERESTException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ERESTException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ERequestError : public ERESTException
{
	typedef ERESTException inherited;
	
private:
	System::UnicodeString FResponseContent;
	int FStatusCode;
	System::UnicodeString FStatusText;
	
public:
	__fastcall ERequestError(int AStatusCode, const System::UnicodeString AStatusText, const System::UnicodeString AResponseContent);
	__property System::UnicodeString ResponseContent = {read=FResponseContent, write=FResponseContent};
	__property int StatusCode = {read=FStatusCode, write=FStatusCode, nodefault};
	__property System::UnicodeString StatusText = {read=FStatusText, write=FStatusText};
public:
	/* Exception.CreateFmt */ inline __fastcall ERequestError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ERESTException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ERequestError(NativeUInt Ident)/* overload */ : ERESTException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ERequestError(System::PResStringRec ResStringRec)/* overload */ : ERESTException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ERequestError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ERESTException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ERequestError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ERESTException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ERequestError(const System::UnicodeString Msg, int AHelpContext) : ERESTException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ERequestError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ERESTException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ERequestError(NativeUInt Ident, int AHelpContext)/* overload */ : ERESTException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ERequestError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ERESTException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ERequestError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ERESTException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ERequestError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ERESTException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ERequestError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TRESTRequestParameterKind DefaultRESTRequestParameterKind;
extern DELPHI_PACKAGE TRESTContentType DefaultRESTContentType;
#define CONTENTTYPE_NONE u""
#define CONTENTTYPE_APPLICATION_ATOM_XML u"application/atom+xml"
#define CONTENTTYPE_APPLICATION_ECMASCRIPT u"application/ecmascript"
#define CONTENTTYPE_APPLICATION_EDI_X12 u"application/EDI-X12"
#define CONTENTTYPE_APPLICATION_EDIFACT u"application/EDIFACT"
#define CONTENTTYPE_APPLICATION_JSON u"application/json"
#define CONTENTTYPE_APPLICATION_JAVASCRIPT u"application/javascript"
#define CONTENTTYPE_APPLICATION_OCTET_STREAM u"application/octet-stream"
#define CONTENTTYPE_APPLICATION_OGG u"application/ogg"
#define CONTENTTYPE_APPLICATION_PDF u"application/pdf"
#define CONTENTTYPE_APPLICATION_POSTSCRIPT u"application/postscript"
#define CONTENTTYPE_APPLICATION_RDF_XML u"application/rdf+xml"
#define CONTENTTYPE_APPLICATION_RSS_XML u"application/rss+xml"
#define CONTENTTYPE_APPLICATION_SOAP_XML u"application/soap+xml"
#define CONTENTTYPE_APPLICATION_FONT_WOFF u"application/font-woff"
#define CONTENTTYPE_APPLICATION_XHTML_XML u"application/xhtml+xml"
#define CONTENTTYPE_APPLICATION_XML u"application/xml"
#define CONTENTTYPE_APPLICATION_XML_DTD u"application/xml-dtd"
#define CONTENTTYPE_APPLICATION_XOP_XML u"application/xop+xml"
#define CONTENTTYPE_APPLICATION_ZIP u"application/zip"
#define CONTENTTYPE_APPLICATION_GZIP u"application/gzip"
#define CONTENTTYPE_TEXT_CMD u"text/cmd"
#define CONTENTTYPE_TEXT_CSS u"text/css"
#define CONTENTTYPE_TEXT_CSV u"text/csv"
#define CONTENTTYPE_TEXT_HTML u"text/html"
#define CONTENTTYPE_TEXT_JAVASCRIPT u"text/javascript"
#define CONTENTTYPE_TEXT_PLAIN u"text/plain"
#define CONTENTTYPE_TEXT_VCARD u"text/vcard"
#define CONTENTTYPE_TEXT_XML u"text/xml"
#define CONTENTTYPE_AUDIO_BASIC u"audio/basic"
#define CONTENTTYPE_AUDIO_L24 u"audio/L24"
#define CONTENTTYPE_AUDIO_MP4 u"audio/mp4"
#define CONTENTTYPE_AUDIO_MPEG u"audio/mpeg"
#define CONTENTTYPE_AUDIO_OGG u"audio/ogg"
#define CONTENTTYPE_AUDIO_VORBIS u"audio/vorbis"
#define CONTENTTYPE_AUDIO_VND_RN_REALAUDIO u"audio/vnd.rn-realaudio"
#define CONTENTTYPE_AUDIO_VND_WAVE u"audio/vnd.wave"
#define CONTENTTYPE_AUDIO_WEBM u"audio/webm"
#define CONTENTTYPE_IMAGE_GIF u"image/gif"
#define CONTENTTYPE_IMAGE_JPEG u"image/jpeg"
#define CONTENTTYPE_IMAGE_PJPEG u"image/pjpeg"
#define CONTENTTYPE_IMAGE_PNG u"image/png"
#define CONTENTTYPE_IMAGE_SVG_XML u"image/svg+xml"
#define CONTENTTYPE_IMAGE_TIFF u"image/tiff"
#define CONTENTTYPE_MESSAGE_HTTP u"message/http"
#define CONTENTTYPE_MESSAGE_IMDN_XML u"message/imdn+xml"
#define CONTENTTYPE_MESSAGE_PARTIAL u"message/partial"
#define CONTENTTYPE_MESSAGE_RFC822 u"message/rfc822"
#define CONTENTTYPE_MODEL_EXAMPLE u"model/example"
#define CONTENTTYPE_MODEL_IGES u"model/iges"
#define CONTENTTYPE_MODEL_MESH u"model/mesh"
#define CONTENTTYPE_MODEL_VRML u"model/vrml"
#define CONTENTTYPE_MODEL_X3D_BINARY u"model/x3d+binary"
#define CONTENTTYPE_MODEL_X3D_VRML u"model/x3d+vrml"
#define CONTENTTYPE_MODEL_X3D_XML u"model/x3d+xml"
#define CONTENTTYPE_MULTIPART_MIXED u"multipart/mixed"
#define CONTENTTYPE_MULTIPART_ALTERNATIVE u"multipart/alternative"
#define CONTENTTYPE_MULTIPART_RELATED u"multipart/related"
#define CONTENTTYPE_MULTIPART_FORM_DATA u"multipart/form-data"
#define CONTENTTYPE_MULTIPART_SIGNED u"multipart/signed"
#define CONTENTTYPE_MULTIPART_ENCRYPTED u"multipart/encrypted"
#define CONTENTTYPE_VIDEO_MPEG u"video/mpeg"
#define CONTENTTYPE_VIDEO_MP4 u"video/mp4"
#define CONTENTTYPE_VIDEO_OGG u"video/ogg"
#define CONTENTTYPE_VIDEO_QUICKTIME u"video/quicktime"
#define CONTENTTYPE_VIDEO_WEBM u"video/webm"
#define CONTENTTYPE_VIDEO_X_MATROSKA u"video/x-matroska"
#define CONTENTTYPE_VIDEO_X_MS_WMV u"video/x-ms-wmv"
#define CONTENTTYPE_VIDEO_X_FLV u"video/x-flv"
#define CONTENTTYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_TEXT u"application/vnd.oasis.opendocument.text"
#define CONTENTTYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_SPREADSHEET u"application/vnd.oasis.opendocument.spreadsheet"
#define CONTENTTYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_PRESENTATION u"application/vnd.oasis.opendocument.presentation"
#define CONTENTTYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_GRAPHICS u"application/vnd.oasis.opendocument.graphics"
#define CONTENTTYPE_APPLICATION_VND_MS_EXCEL u"application/vnd.ms-excel"
#define CONTENTTYPE_APPLICATION_VND_OPENXMLFORMATS_OFFICEDOCUMENT_SPREADSHEETML_SHEET u"application/vnd.openxmlformats-officedocument.spreadsheetm"\
	u"l.sheet"
#define CONTENTTYPE_APPLICATION_VND_MS_POWERPOINT u"application/vnd.ms-powerpoint"
#define CONTENTTYPE_APPLICATION_VND_OPENXMLFORMATS_OFFICEDOCUMENT_PRESENTATIONML_PRESENTATION u"application/vnd.openxmlformats-officedocument.presentation"\
	u"ml.presentation"
#define CONTENTTYPE_APPLICATION_VND_OPENXMLFORMATS_OFFICEDOCUMENT_WORDPROCESSINGML_DOCUMENT u"application/vnd.openxmlformats-officedocument.wordprocessi"\
	u"ngml.document"
#define CONTENTTYPE_APPLICATION_VND_MOZILLA_XUL_XML u"application/vnd.mozilla.xul+xml"
#define CONTENTTYPE_APPLICATION_VND_GOOGLE_EARTH_KML_XML u"application/vnd.google-earth.kml+xml"
#define CONTENTTYPE_APPLICATION_VND_GOOGLE_EARTH_KMZ u"application/vnd.google-earth.kmz"
#define CONTENTTYPE_APPLICATION_VND_DART u"application/vnd.dart"
#define CONTENTTYPE_APPLICATION_VND_ANDROID_PACKAGE_ARCHIVE u"application/vnd.android.package-archive"
#define CONTENTTYPE_APPLICATION_X_DEB u"application/x-deb"
#define CONTENTTYPE_APPLICATION_X_DVI u"application/x-dvi"
#define CONTENTTYPE_APPLICATION_X_FONT_TTF u"application/x-font-ttf"
#define CONTENTTYPE_APPLICATION_X_JAVASCRIPT u"application/x-javascript"
#define CONTENTTYPE_APPLICATION_X_LATEX u"application/x-latex"
#define CONTENTTYPE_APPLICATION_X_MPEGURL u"application/x-mpegURL"
#define CONTENTTYPE_APPLICATION_X_RAR_COMPRESSED u"application/x-rar-compressed"
#define CONTENTTYPE_APPLICATION_X_SHOCKWAVE_FLASH u"application/x-shockwave-flash"
#define CONTENTTYPE_APPLICATION_X_STUFFIT u"application/x-stuffit"
#define CONTENTTYPE_APPLICATION_X_TAR u"application/x-tar"
#define CONTENTTYPE_APPLICATION_X_WWW_FORM_URLENCODED u"application/x-www-form-urlencoded"
#define CONTENTTYPE_APPLICATION_X_XPINSTALL u"application/x-xpinstall"
#define CONTENTTYPE_AUDIO_X_AAC u"audio/x-aac"
#define CONTENTTYPE_AUDIO_X_CAF u"audio/x-caf"
#define CONTENTTYPE_IMAGE_X_XCF u"image/x-xcf"
#define CONTENTTYPE_TEXT_X_GWT_RPC u"text/x-gwt-rpc"
#define CONTENTTYPE_TEXT_X_JQUERY_TMPL u"text/x-jquery-tmpl"
#define CONTENTTYPE_TEXT_X_MARKDOWN u"text/x-markdown"
#define CONTENTTYPE_APPLICATION_X_PKCS12 u"application/x-pkcs12"
#define CONTENTTYPE_APPLICATION_X_PKCS7_CERTIFICATES u"application/x-pkcs7-certificates"
#define CONTENTTYPE_APPLICATION_X_PKCS7_CERTREQRESP u"application/x-pkcs7-certreqresp"
#define CONTENTTYPE_APPLICATION_X_PKCS7_MIME u"application/x-pkcs7-mime"
#define CONTENTTYPE_APPLICATION_X_PKCS7_SIGNATURE u"application/x-pkcs7-signature"
#define CONTENTTYPE_APPLICATION_VND_EMBARCADERO_FIREDAC_JSON u"application/vnd.embarcadero.firedac+json"
extern DELPHI_PACKAGE TRESTRequestMethod DefaultRESTRequestMethod;
extern DELPHI_PACKAGE bool __fastcall IsTextualContentType(const System::UnicodeString AContentType)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsTextualContentType(TRESTContentType AContentType)/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall RESTRequestParameterKindToString(const TRESTRequestParameterKind AKind);
extern DELPHI_PACKAGE TRESTRequestParameterKind __fastcall RESTRequestParameterKindFromString(const System::UnicodeString AKindString);
extern DELPHI_PACKAGE System::UnicodeString __fastcall RESTRequestMethodToString(const TRESTRequestMethod AMethod);
extern DELPHI_PACKAGE TRESTContentType __fastcall ContentTypeFromString(const System::UnicodeString AContentType);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ContentTypeToString(TRESTContentType AContentType);
}	/* namespace Types */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_TYPES)
using namespace Rest::Types;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_TypesHPP
