// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Types.pas' rev: 34.00 (Windows)

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

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
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

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
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

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TRESTRequestParameterKind DefaultRESTRequestParameterKind;
extern DELPHI_PACKAGE TRESTContentType DefaultRESTContentType;
#define CONTENTTYPE_NONE L""
#define CONTENTTYPE_APPLICATION_ATOM_XML L"application/atom+xml"
#define CONTENTTYPE_APPLICATION_ECMASCRIPT L"application/ecmascript"
#define CONTENTTYPE_APPLICATION_EDI_X12 L"application/EDI-X12"
#define CONTENTTYPE_APPLICATION_EDIFACT L"application/EDIFACT"
#define CONTENTTYPE_APPLICATION_JSON L"application/json"
#define CONTENTTYPE_APPLICATION_JAVASCRIPT L"application/javascript"
#define CONTENTTYPE_APPLICATION_OCTET_STREAM L"application/octet-stream"
#define CONTENTTYPE_APPLICATION_OGG L"application/ogg"
#define CONTENTTYPE_APPLICATION_PDF L"application/pdf"
#define CONTENTTYPE_APPLICATION_POSTSCRIPT L"application/postscript"
#define CONTENTTYPE_APPLICATION_RDF_XML L"application/rdf+xml"
#define CONTENTTYPE_APPLICATION_RSS_XML L"application/rss+xml"
#define CONTENTTYPE_APPLICATION_SOAP_XML L"application/soap+xml"
#define CONTENTTYPE_APPLICATION_FONT_WOFF L"application/font-woff"
#define CONTENTTYPE_APPLICATION_XHTML_XML L"application/xhtml+xml"
#define CONTENTTYPE_APPLICATION_XML L"application/xml"
#define CONTENTTYPE_APPLICATION_XML_DTD L"application/xml-dtd"
#define CONTENTTYPE_APPLICATION_XOP_XML L"application/xop+xml"
#define CONTENTTYPE_APPLICATION_ZIP L"application/zip"
#define CONTENTTYPE_APPLICATION_GZIP L"application/gzip"
#define CONTENTTYPE_TEXT_CMD L"text/cmd"
#define CONTENTTYPE_TEXT_CSS L"text/css"
#define CONTENTTYPE_TEXT_CSV L"text/csv"
#define CONTENTTYPE_TEXT_HTML L"text/html"
#define CONTENTTYPE_TEXT_JAVASCRIPT L"text/javascript"
#define CONTENTTYPE_TEXT_PLAIN L"text/plain"
#define CONTENTTYPE_TEXT_VCARD L"text/vcard"
#define CONTENTTYPE_TEXT_XML L"text/xml"
#define CONTENTTYPE_AUDIO_BASIC L"audio/basic"
#define CONTENTTYPE_AUDIO_L24 L"audio/L24"
#define CONTENTTYPE_AUDIO_MP4 L"audio/mp4"
#define CONTENTTYPE_AUDIO_MPEG L"audio/mpeg"
#define CONTENTTYPE_AUDIO_OGG L"audio/ogg"
#define CONTENTTYPE_AUDIO_VORBIS L"audio/vorbis"
#define CONTENTTYPE_AUDIO_VND_RN_REALAUDIO L"audio/vnd.rn-realaudio"
#define CONTENTTYPE_AUDIO_VND_WAVE L"audio/vnd.wave"
#define CONTENTTYPE_AUDIO_WEBM L"audio/webm"
#define CONTENTTYPE_IMAGE_GIF L"image/gif"
#define CONTENTTYPE_IMAGE_JPEG L"image/jpeg"
#define CONTENTTYPE_IMAGE_PJPEG L"image/pjpeg"
#define CONTENTTYPE_IMAGE_PNG L"image/png"
#define CONTENTTYPE_IMAGE_SVG_XML L"image/svg+xml"
#define CONTENTTYPE_IMAGE_TIFF L"image/tiff"
#define CONTENTTYPE_MESSAGE_HTTP L"message/http"
#define CONTENTTYPE_MESSAGE_IMDN_XML L"message/imdn+xml"
#define CONTENTTYPE_MESSAGE_PARTIAL L"message/partial"
#define CONTENTTYPE_MESSAGE_RFC822 L"message/rfc822"
#define CONTENTTYPE_MODEL_EXAMPLE L"model/example"
#define CONTENTTYPE_MODEL_IGES L"model/iges"
#define CONTENTTYPE_MODEL_MESH L"model/mesh"
#define CONTENTTYPE_MODEL_VRML L"model/vrml"
#define CONTENTTYPE_MODEL_X3D_BINARY L"model/x3d+binary"
#define CONTENTTYPE_MODEL_X3D_VRML L"model/x3d+vrml"
#define CONTENTTYPE_MODEL_X3D_XML L"model/x3d+xml"
#define CONTENTTYPE_MULTIPART_MIXED L"multipart/mixed"
#define CONTENTTYPE_MULTIPART_ALTERNATIVE L"multipart/alternative"
#define CONTENTTYPE_MULTIPART_RELATED L"multipart/related"
#define CONTENTTYPE_MULTIPART_FORM_DATA L"multipart/form-data"
#define CONTENTTYPE_MULTIPART_SIGNED L"multipart/signed"
#define CONTENTTYPE_MULTIPART_ENCRYPTED L"multipart/encrypted"
#define CONTENTTYPE_VIDEO_MPEG L"video/mpeg"
#define CONTENTTYPE_VIDEO_MP4 L"video/mp4"
#define CONTENTTYPE_VIDEO_OGG L"video/ogg"
#define CONTENTTYPE_VIDEO_QUICKTIME L"video/quicktime"
#define CONTENTTYPE_VIDEO_WEBM L"video/webm"
#define CONTENTTYPE_VIDEO_X_MATROSKA L"video/x-matroska"
#define CONTENTTYPE_VIDEO_X_MS_WMV L"video/x-ms-wmv"
#define CONTENTTYPE_VIDEO_X_FLV L"video/x-flv"
#define CONTENTTYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_TEXT L"application/vnd.oasis.opendocument.text"
#define CONTENTTYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_SPREADSHEET L"application/vnd.oasis.opendocument.spreadsheet"
#define CONTENTTYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_PRESENTATION L"application/vnd.oasis.opendocument.presentation"
#define CONTENTTYPE_APPLICATION_VND_OASIS_OPENDOCUMENT_GRAPHICS L"application/vnd.oasis.opendocument.graphics"
#define CONTENTTYPE_APPLICATION_VND_MS_EXCEL L"application/vnd.ms-excel"
#define CONTENTTYPE_APPLICATION_VND_OPENXMLFORMATS_OFFICEDOCUMENT_SPREADSHEETML_SHEET L"application/vnd.openxmlformats-officedocument.spreadsheetm"\
	L"l.sheet"
#define CONTENTTYPE_APPLICATION_VND_MS_POWERPOINT L"application/vnd.ms-powerpoint"
#define CONTENTTYPE_APPLICATION_VND_OPENXMLFORMATS_OFFICEDOCUMENT_PRESENTATIONML_PRESENTATION L"application/vnd.openxmlformats-officedocument.presentation"\
	L"ml.presentation"
#define CONTENTTYPE_APPLICATION_VND_OPENXMLFORMATS_OFFICEDOCUMENT_WORDPROCESSINGML_DOCUMENT L"application/vnd.openxmlformats-officedocument.wordprocessi"\
	L"ngml.document"
#define CONTENTTYPE_APPLICATION_VND_MOZILLA_XUL_XML L"application/vnd.mozilla.xul+xml"
#define CONTENTTYPE_APPLICATION_VND_GOOGLE_EARTH_KML_XML L"application/vnd.google-earth.kml+xml"
#define CONTENTTYPE_APPLICATION_VND_GOOGLE_EARTH_KMZ L"application/vnd.google-earth.kmz"
#define CONTENTTYPE_APPLICATION_VND_DART L"application/vnd.dart"
#define CONTENTTYPE_APPLICATION_VND_ANDROID_PACKAGE_ARCHIVE L"application/vnd.android.package-archive"
#define CONTENTTYPE_APPLICATION_X_DEB L"application/x-deb"
#define CONTENTTYPE_APPLICATION_X_DVI L"application/x-dvi"
#define CONTENTTYPE_APPLICATION_X_FONT_TTF L"application/x-font-ttf"
#define CONTENTTYPE_APPLICATION_X_JAVASCRIPT L"application/x-javascript"
#define CONTENTTYPE_APPLICATION_X_LATEX L"application/x-latex"
#define CONTENTTYPE_APPLICATION_X_MPEGURL L"application/x-mpegURL"
#define CONTENTTYPE_APPLICATION_X_RAR_COMPRESSED L"application/x-rar-compressed"
#define CONTENTTYPE_APPLICATION_X_SHOCKWAVE_FLASH L"application/x-shockwave-flash"
#define CONTENTTYPE_APPLICATION_X_STUFFIT L"application/x-stuffit"
#define CONTENTTYPE_APPLICATION_X_TAR L"application/x-tar"
#define CONTENTTYPE_APPLICATION_X_WWW_FORM_URLENCODED L"application/x-www-form-urlencoded"
#define CONTENTTYPE_APPLICATION_X_XPINSTALL L"application/x-xpinstall"
#define CONTENTTYPE_AUDIO_X_AAC L"audio/x-aac"
#define CONTENTTYPE_AUDIO_X_CAF L"audio/x-caf"
#define CONTENTTYPE_IMAGE_X_XCF L"image/x-xcf"
#define CONTENTTYPE_TEXT_X_GWT_RPC L"text/x-gwt-rpc"
#define CONTENTTYPE_TEXT_X_JQUERY_TMPL L"text/x-jquery-tmpl"
#define CONTENTTYPE_TEXT_X_MARKDOWN L"text/x-markdown"
#define CONTENTTYPE_APPLICATION_X_PKCS12 L"application/x-pkcs12"
#define CONTENTTYPE_APPLICATION_X_PKCS7_CERTIFICATES L"application/x-pkcs7-certificates"
#define CONTENTTYPE_APPLICATION_X_PKCS7_CERTREQRESP L"application/x-pkcs7-certreqresp"
#define CONTENTTYPE_APPLICATION_X_PKCS7_MIME L"application/x-pkcs7-mime"
#define CONTENTTYPE_APPLICATION_X_PKCS7_SIGNATURE L"application/x-pkcs7-signature"
#define CONTENTTYPE_APPLICATION_VND_EMBARCADERO_FIREDAC_JSON L"application/vnd.embarcadero.firedac+json"
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
