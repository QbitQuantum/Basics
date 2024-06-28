// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPConst.pas' rev: 34.00 (Android)

#ifndef Soap_SoapconstHPP
#define Soap_SoapconstHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.TypInfo.hpp>
#include <Xml.XMLSchema.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soapconst
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<System::UnicodeString, 2> Soap_Soapconst__1;

typedef System::StaticArray<System::UnicodeString, 2> Soap_Soapconst__2;

typedef System::StaticArray<System::UnicodeString, 2> Soap_Soapconst__3;

typedef System::StaticArray<System::UnicodeString, 2> Soap_Soapconst__4;

typedef System::StaticArray<System::UnicodeString, 2> Soap_Soapconst__5;

typedef System::StaticArray<System::UnicodeString, 18> Soap_Soapconst__6;

typedef System::StaticArray<System::UnicodeString, 2> Soap_Soapconst__8;

//-- var, const, procedure ---------------------------------------------------
#define SHTTPPrefix u"http://"
#define SContentId u"Content-ID"
#define SContentLocation u"Content-Location"
#define SContentLength u"Content-Length"
#define SContentType u"Content-Type"
#define SWSDLMIMENamespace u"http://schemas.xmlsoap.org/wsdl/mime/"
#define SBorlandMimeBoundary u"MIME_boundaryB0R9532143182121"
#define SSoapXMLHeader u"<?xml version=\"1.0\" encoding='UTF-8'?>"
#define SUTF8 u"UTF-8"
#define ContentTypeTemplate u"Content-Type: %s"
#define ContentTypeWithActionFmt u"Content-Type: %s;action=\"%s\""
#define ContentTypeWithActionNoLabelFmt u"%s;action=\"%s\""
#define ContentTypeApplicationBinary u"application/binary"
#define SBinaryEncoding u"binary"
#define S8BitEncoding u"8bit"
#define ContentTypeTextPlain u"text/plain"
#define SCharacterEncodingFormat u"Content-transfer-encoding: %s"
#define SCharacterEncoding u"Content-transfer-encoding"
#define SBoundary u"boundary="
#define SMultiPartRelated u"multipart/related"
#define SMultiPartRelatedNoSlash u"multipartRelated"
#define ContentHeaderMime u"multipart/related; boundary=%s"
#define SStart u"; start=\"<%s>\""
#define SBorlandSoapStart u"http://www.borland.com/rootpart.xml"
#define SAttachmentIdPrefix u"cid:"
#define MimeVersionName u"MIME-Version"
#define MimeVersionValue u"1.0"
#define MimeVersion u"MIME-Version: 1.0"
#define sTextHtml u"text/html"
#define sTextHtmlUTF8 u"text/html; charset=utf-8"
#define sTextXML u"text/xml"
#define ContentTypeUTF8 u"text/xml; charset=utf-8"
#define ContentTypeNoUTF8 u"text/xml"
#define ContentType12UTF8 u"application/soap+xml; charset=utf-8"
#define ContentType12NoUTF8 u"application/soap+xml"
#define SSoapNamespace u"http://schemas.xmlsoap.org/soap/envelope/"
#define SSoap12Namespace u"http://www.w3.org/2003/05/soap-envelope"
extern DELPHI_PACKAGE Soap_Soapconst__1 SOAPEnvelopeNamespaces;
#define SXMLNS u"xmlns"
#define SSoapEncodingAttr u"encodingStyle"
#define SSoap11EncodingS5 u"http://schemas.xmlsoap.org/soap/encoding/"
#define SSoap12EncodingNamespace u"http://www.w3.org/2003/05/soap-encoding"
extern DELPHI_PACKAGE Soap_Soapconst__2 SOAPEncodingNamespaces;
#define SSOAP12RPCNamespace u"http://www.w3.org/2003/05/soap-rpc"
#define SSoapEncodingArray u"Array"
#define SSoapEncodingArrayType u"arrayType"
#define SSoap12EncodingArrayType u"itemType"
extern DELPHI_PACKAGE Soap_Soapconst__3 SSoapEncodingArrayTypes;
#define SSoap12EncodingArraySize u"arraySize"
#define SSoapHTTPTransport u"http://schemas.xmlsoap.org/soap/http"
#define SSoapBodyUseEncoded u"encoded"
#define SSoapBodyUseLiteral u"literal"
#define SSoapEnvelope u"Envelope"
#define SSoapHeader u"Header"
#define SSoapBody u"Body"
#define SSoapResponseSuff u"Response"
#define SRequired u"required"
#define SSoapActor u"actor"
#define STrue u"true"
#define SSoapServerFaultCode u"Server"
#define SSoapServerFaultString u"Server Error"
#define SSoapFault u"Fault"
#define SSoapFaultCode u"faultcode"
#define SSoapFaultString u"faultstring"
#define SSoapFaultActor u"faultactor"
#define SSoapFaultDetails u"detail"
#define SFaultCodeMustUnderstand u"MustUnderstand"
#define SSOAP12FaultCode u"Code"
#define SSOAP12FaultSubCode u"Subcode"
#define SSOAP12FaultReason u"Reason"
#define SSOAP12FaultReasonLang u"lang"
#define SSOAP12FaultNode u"Node"
#define SSOAP12FaultRole u"Role"
#define SSOAP12FaultDetail u"Detail"
#define SSOAP12FaultText u"Text"
#define SHTTPSoapAction u"SOAPAction"
#define SHeaderMustUnderstand u"mustUnderstand"
#define SHeaderActor u"actor"
#define SActorNext u"http://schemas.xmlsoap.org/soap/actor/next"
#define SSoapType u"type"
#define SSoapResponse u"Response"
#define SDefaultReturnName u"return"
#define SDefaultResultName u"result"
#define SXMLID u"id"
#define SXMLHREF u"href"
#define SSOAP12XMLHREF u"ref"
extern DELPHI_PACKAGE Soap_Soapconst__4 SSOAPXMLHREFs;
#define SSoapNULL u"NULL"
#define SSoapNIL u"nil"
#define SSoapNillable u"nillable"
#define SOptional u"optional"
#define SElemForm u"form"
#define SUnqualified u"unqualified"
static constexpr System::WideChar SHREFPre = (System::WideChar)(0x23);
#define SSOAP12HREFPre u""
extern DELPHI_PACKAGE Soap_Soapconst__5 SSOAPHREFPres;
#define SArrayIDPre u"Array-"
static constexpr System::WideChar SDefVariantElemName = (System::WideChar)(0x56);
#define SDefaultBaseURI u"thismessage:/"
#define SDelphiTypeNamespace u"http://www.borland.com/namespaces/Delphi/Types"
#define SBorlandTypeNamespace u"http://www.borland.com/namespaces/Types"
#define SOperationNameSpecifier u"%operationName%"
#define SDefaultReturnParamNames u"Result;Return"
#define sReturnParamDelimiters u";,/:"
extern DELPHI_PACKAGE Soap_Soapconst__6 KindNameArray;
#define SSoapNameSpacePre u"SOAP-ENV"
#define SXMLSchemaNameSpacePre u"xsd"
#define SXMLSchemaInstNameSpace99Pre u"xsi"
#define SSoapEncodingPre u"SOAP-ENC"
#define SCharset u"charset"
#define sDefaultColor u"#333333"
#define sIntfColor u"#660000"
#define sTblHdrColor u"#CCCC99"
#define sTblColor1 u"#f5f5dc"
#define sTblColor0 u"#d9d4aa"
#define sBkgndColor u"#d9d4aa"
#define sTipColor u"#666666"
#define sWSDLColor u"#990000"
#define sOFFColor u"#A0A0A0"
#define sNavBarColor u"#660000"
#define sNavBkColor u"#f5f5dc"
#define HTMLStylBeg u"<style type=\"text/css\"><!--\n"
#define HTMLStylEnd u"--></style>\n"
#define BodyStyle1 u"body       {font-family: Verdana, Arial, Helvetica, sans-s"\
	u"erif; font-size: 9pt; }\n"
#define BodyStyle2 u"body       {font-family: Verdana, Arial, Helvetica, sans-s"\
	u"erif; font-size: 9pt; margin-left: 0px; margin-top: 0px; m"\
	u"argin-right: 0px; }\n"
#define OtherStyles u"h1         {color: #333333; font-size: 18pt; font-style: n"\
	u"ormal; font-weight: bold; }\nh2         {color: #333333; f"\
	u"ont-size: 14pt; font-style: normal; font-weight: bold; }\n"\
	u"h3         {color: #333333; font-size: 12pt; font-style: n"\
	u"ormal; font-weight: bold; }\n.h1Style   {color: #333333; f"\
	u"ont-size: 18pt; font-style: normal; font-weight: bold; }\n"\
	u".TblRow    {color: #333333; font-family: Verdana, Arial, H"\
	u"elvetica, sans-serif; font-size: 10pt; font-weight: normal"\
	u"; }\n.TblRow1   {color: #333333; background-color: #f5f5dc"\
	u"; font-family: Verdana, Arial, Helvetica, sans-serif; font"\
	u"-size: 9pt; font-weight: normal; }\n.TblRow0   {color: #33"\
	u"3333; background-color: #d9d4aa; font-family: Verdana, Ari"\
	u"al, Helvetica, sans-serif; font-size: 9pt; font-weight: no"\
	u"rmal; }\n.TblHdr    {color: #CCCC99; background-color: #33"\
	u"3333; font-family: Verdana, Arial, Helvetica, sans-serif; "\
	u"font-size: 10pt; font-weight: bold; text-align: center;}\n"\
	u".IntfName  {color: #660000; font-family: Verdana, Arial, H"\
	u"elvetica, sans-serif; font-size: 10pt; font-weight: bold; "\
	u"}\n.MethName  {color: #333333; font-family: Verdana, Arial"\
	u", Helvetica, sans-serif; font-size: 8pt; font-weight: bold"\
	u"; text-decoration: none; }\n.ParmName  {color: #333333; fo"\
	u"nt-family: Verdana, Arial, Helvetica, sans-serif; font-siz"\
	u"e: 8pt; text-decoration: none; }\n.Namespace {color: #3333"\
	u"33; font-family: Verdana, Arial, Helvetica, sans-serif; fo"\
	u"nt-size: 9pt; font-style: italic; }\n.WSDL      {color: #9"\
	u"90000; font-family: Verdana, Arial, Helvetica, sans-serif;"\
	u" font-size: 8pt; font-weight: bold; }\n.MainBkgnd {backgro"\
	u"und-color : #d9d4aa; }\n.Info      {font-family: Verdana, "\
	u"Arial, Helvetica, sans-serif; font-size: 12pt; font-weight"\
	u": bold; }\n.NavBar    {color: #660000; background-color: #"\
	u"f5f5dc; font-family: Verdana, Arial, Helvetica, sans-serif"\
	u"; font-size: 8pt; font-weight: bold;text-decoration: none;"\
	u" }\n.Off       {color: #A0A0A0; }\n.Tip \t    {color: #666"\
	u"666; font-family : Verdana, Arial, Helvetica, sans-serif; "\
	u"font-weight : normal; font-size : 9pt; }\n"
#define HTMLStyles u"<style type=\"text/css\"><!--\nbody       {font-family: Ve"\
	u"rdana, Arial, Helvetica, sans-serif; font-size: 9pt; }\nh1"\
	u"         {color: #333333; font-size: 18pt; font-style: nor"\
	u"mal; font-weight: bold; }\nh2         {color: #333333; fon"\
	u"t-size: 14pt; font-style: normal; font-weight: bold; }\nh3"\
	u"         {color: #333333; font-size: 12pt; font-style: nor"\
	u"mal; font-weight: bold; }\n.h1Style   {color: #333333; fon"\
	u"t-size: 18pt; font-style: normal; font-weight: bold; }\n.T"\
	u"blRow    {color: #333333; font-family: Verdana, Arial, Hel"\
	u"vetica, sans-serif; font-size: 10pt; font-weight: normal; "\
	u"}\n.TblRow1   {color: #333333; background-color: #f5f5dc; "\
	u"font-family: Verdana, Arial, Helvetica, sans-serif; font-s"\
	u"ize: 9pt; font-weight: normal; }\n.TblRow0   {color: #3333"\
	u"33; background-color: #d9d4aa; font-family: Verdana, Arial"\
	u", Helvetica, sans-serif; font-size: 9pt; font-weight: norm"\
	u"al; }\n.TblHdr    {color: #CCCC99; background-color: #3333"\
	u"33; font-family: Verdana, Arial, Helvetica, sans-serif; fo"\
	u"nt-size: 10pt; font-weight: bold; text-align: center;}\n.I"\
	u"ntfName  {color: #660000; font-family: Verdana, Arial, Hel"\
	u"vetica, sans-serif; font-size: 10pt; font-weight: bold; }\n"\
	u".MethName  {color: #333333; font-family: Verdana, Arial, H"\
	u"elvetica, sans-serif; font-size: 8pt; font-weight: bold; t"\
	u"ext-decoration: none; }\n.ParmName  {color: #333333; font-"\
	u"family: Verdana, Arial, Helvetica, sans-serif; font-size: "\
	u"8pt; text-decoration: none; }\n.Namespace {color: #333333;"\
	u" font-family: Verdana, Arial, Helvetica, sans-serif; font-"\
	u"size: 9pt; font-style: italic; }\n.WSDL      {color: #9900"\
	u"00; font-family: Verdana, Arial, Helvetica, sans-serif; fo"\
	u"nt-size: 8pt; font-weight: bold; }\n.MainBkgnd {background"\
	u"-color : #d9d4aa; }\n.Info      {font-family: Verdana, Ari"\
	u"al, Helvetica, sans-serif; font-size: 12pt; font-weight: b"\
	u"old; }\n.NavBar    {color: #660000; background-color: #f5f"\
	u"5dc; font-family: Verdana, Arial, Helvetica, sans-serif; f"\
	u"ont-size: 8pt; font-weight: bold;text-decoration: none; }\n"\
	u".Off       {color: #A0A0A0; }\n.Tip \t    {color: #666666;"\
	u" font-family : Verdana, Arial, Helvetica, sans-serif; font"\
	u"-weight : normal; font-size : 9pt; }\n--></style>\n"
#define HTMLNoMargin u"<style type=\"text/css\"><!--\nbody       {font-family: Ve"\
	u"rdana, Arial, Helvetica, sans-serif; font-size: 9pt; margi"\
	u"n-left: 0px; margin-top: 0px; margin-right: 0px; }\nh1    "\
	u"     {color: #333333; font-size: 18pt; font-style: normal;"\
	u" font-weight: bold; }\nh2         {color: #333333; font-si"\
	u"ze: 14pt; font-style: normal; font-weight: bold; }\nh3    "\
	u"     {color: #333333; font-size: 12pt; font-style: normal;"\
	u" font-weight: bold; }\n.h1Style   {color: #333333; font-si"\
	u"ze: 18pt; font-style: normal; font-weight: bold; }\n.TblRo"\
	u"w    {color: #333333; font-family: Verdana, Arial, Helveti"\
	u"ca, sans-serif; font-size: 10pt; font-weight: normal; }\n."\
	u"TblRow1   {color: #333333; background-color: #f5f5dc; font"\
	u"-family: Verdana, Arial, Helvetica, sans-serif; font-size:"\
	u" 9pt; font-weight: normal; }\n.TblRow0   {color: #333333; "\
	u"background-color: #d9d4aa; font-family: Verdana, Arial, He"\
	u"lvetica, sans-serif; font-size: 9pt; font-weight: normal; "\
	u"}\n.TblHdr    {color: #CCCC99; background-color: #333333; "\
	u"font-family: Verdana, Arial, Helvetica, sans-serif; font-s"\
	u"ize: 10pt; font-weight: bold; text-align: center;}\n.IntfN"\
	u"ame  {color: #660000; font-family: Verdana, Arial, Helveti"\
	u"ca, sans-serif; font-size: 10pt; font-weight: bold; }\n.Me"\
	u"thName  {color: #333333; font-family: Verdana, Arial, Helv"\
	u"etica, sans-serif; font-size: 8pt; font-weight: bold; text"\
	u"-decoration: none; }\n.ParmName  {color: #333333; font-fam"\
	u"ily: Verdana, Arial, Helvetica, sans-serif; font-size: 8pt"\
	u"; text-decoration: none; }\n.Namespace {color: #333333; fo"\
	u"nt-family: Verdana, Arial, Helvetica, sans-serif; font-siz"\
	u"e: 9pt; font-style: italic; }\n.WSDL      {color: #990000;"\
	u" font-family: Verdana, Arial, Helvetica, sans-serif; font-"\
	u"size: 8pt; font-weight: bold; }\n.MainBkgnd {background-co"\
	u"lor : #d9d4aa; }\n.Info      {font-family: Verdana, Arial,"\
	u" Helvetica, sans-serif; font-size: 12pt; font-weight: bold"\
	u"; }\n.NavBar    {color: #660000; background-color: #f5f5dc"\
	u"; font-family: Verdana, Arial, Helvetica, sans-serif; font"\
	u"-size: 8pt; font-weight: bold;text-decoration: none; }\n.O"\
	u"ff       {color: #A0A0A0; }\n.Tip \t    {color: #666666; f"\
	u"ont-family : Verdana, Arial, Helvetica, sans-serif; font-w"\
	u"eight : normal; font-size : 9pt; }\n--></style>\n"
#define TableStyle u"border=1 cellspacing=1 cellpadding=2 "
extern DELPHI_PACKAGE System::ResourceString _HTMLContentLanguage;
#define Soap_Soapconst_HTMLContentLanguage System::LoadResourceString(&Soap::Soapconst::_HTMLContentLanguage)
#define HTMLHead u"<html><head>"
#define HTMLServiceInspection u"<META name=\"serviceInspection\" content=\"inspection.wsil"\
	u"\">"
#define HTMLTopPlain u"<html><head></head><body>"
#define HTMLTop u"<html><head><style type=\"text/css\"><!--\nbody       {fon"\
	u"t-family: Verdana, Arial, Helvetica, sans-serif; font-size"\
	u": 9pt; }\nh1         {color: #333333; font-size: 18pt; fon"\
	u"t-style: normal; font-weight: bold; }\nh2         {color: "\
	u"#333333; font-size: 14pt; font-style: normal; font-weight:"\
	u" bold; }\nh3         {color: #333333; font-size: 12pt; fon"\
	u"t-style: normal; font-weight: bold; }\n.h1Style   {color: "\
	u"#333333; font-size: 18pt; font-style: normal; font-weight:"\
	u" bold; }\n.TblRow    {color: #333333; font-family: Verdana"\
	u", Arial, Helvetica, sans-serif; font-size: 10pt; font-weig"\
	u"ht: normal; }\n.TblRow1   {color: #333333; background-colo"\
	u"r: #f5f5dc; font-family: Verdana, Arial, Helvetica, sans-s"\
	u"erif; font-size: 9pt; font-weight: normal; }\n.TblRow0   {"\
	u"color: #333333; background-color: #d9d4aa; font-family: Ve"\
	u"rdana, Arial, Helvetica, sans-serif; font-size: 9pt; font-"\
	u"weight: normal; }\n.TblHdr    {color: #CCCC99; background-"\
	u"color: #333333; font-family: Verdana, Arial, Helvetica, sa"\
	u"ns-serif; font-size: 10pt; font-weight: bold; text-align: "\
	u"center;}\n.IntfName  {color: #660000; font-family: Verdana"\
	u", Arial, Helvetica, sans-serif; font-size: 10pt; font-weig"\
	u"ht: bold; }\n.MethName  {color: #333333; font-family: Verd"\
	u"ana, Arial, Helvetica, sans-serif; font-size: 8pt; font-we"\
	u"ight: bold; text-decoration: none; }\n.ParmName  {color: #"\
	u"333333; font-family: Verdana, Arial, Helvetica, sans-serif"\
	u"; font-size: 8pt; text-decoration: none; }\n.Namespace {co"\
	u"lor: #333333; font-family: Verdana, Arial, Helvetica, sans"\
	u"-serif; font-size: 9pt; font-style: italic; }\n.WSDL      "\
	u"{color: #990000; font-family: Verdana, Arial, Helvetica, s"\
	u"ans-serif; font-size: 8pt; font-weight: bold; }\n.MainBkgn"\
	u"d {background-color : #d9d4aa; }\n.Info      {font-family:"\
	u" Verdana, Arial, Helvetica, sans-serif; font-size: 12pt; f"\
	u"ont-weight: bold; }\n.NavBar    {color: #660000; backgroun"\
	u"d-color: #f5f5dc; font-family: Verdana, Arial, Helvetica, "\
	u"sans-serif; font-size: 8pt; font-weight: bold;text-decorat"\
	u"ion: none; }\n.Off       {color: #A0A0A0; }\n.Tip \t    {c"\
	u"olor: #666666; font-family : Verdana, Arial, Helvetica, sa"\
	u"ns-serif; font-weight : normal; font-size : 9pt; }\n--></s"\
	u"tyle>\n</head><body>"
#define HTMLTopNoMargin u"<html><head><style type=\"text/css\"><!--\nbody       {fon"\
	u"t-family: Verdana, Arial, Helvetica, sans-serif; font-size"\
	u": 9pt; margin-left: 0px; margin-top: 0px; margin-right: 0p"\
	u"x; }\nh1         {color: #333333; font-size: 18pt; font-st"\
	u"yle: normal; font-weight: bold; }\nh2         {color: #333"\
	u"333; font-size: 14pt; font-style: normal; font-weight: bol"\
	u"d; }\nh3         {color: #333333; font-size: 12pt; font-st"\
	u"yle: normal; font-weight: bold; }\n.h1Style   {color: #333"\
	u"333; font-size: 18pt; font-style: normal; font-weight: bol"\
	u"d; }\n.TblRow    {color: #333333; font-family: Verdana, Ar"\
	u"ial, Helvetica, sans-serif; font-size: 10pt; font-weight: "\
	u"normal; }\n.TblRow1   {color: #333333; background-color: #"\
	u"f5f5dc; font-family: Verdana, Arial, Helvetica, sans-serif"\
	u"; font-size: 9pt; font-weight: normal; }\n.TblRow0   {colo"\
	u"r: #333333; background-color: #d9d4aa; font-family: Verdan"\
	u"a, Arial, Helvetica, sans-serif; font-size: 9pt; font-weig"\
	u"ht: normal; }\n.TblHdr    {color: #CCCC99; background-colo"\
	u"r: #333333; font-family: Verdana, Arial, Helvetica, sans-s"\
	u"erif; font-size: 10pt; font-weight: bold; text-align: cent"\
	u"er;}\n.IntfName  {color: #660000; font-family: Verdana, Ar"\
	u"ial, Helvetica, sans-serif; font-size: 10pt; font-weight: "\
	u"bold; }\n.MethName  {color: #333333; font-family: Verdana,"\
	u" Arial, Helvetica, sans-serif; font-size: 8pt; font-weight"\
	u": bold; text-decoration: none; }\n.ParmName  {color: #3333"\
	u"33; font-family: Verdana, Arial, Helvetica, sans-serif; fo"\
	u"nt-size: 8pt; text-decoration: none; }\n.Namespace {color:"\
	u" #333333; font-family: Verdana, Arial, Helvetica, sans-ser"\
	u"if; font-size: 9pt; font-style: italic; }\n.WSDL      {col"\
	u"or: #990000; font-family: Verdana, Arial, Helvetica, sans-"\
	u"serif; font-size: 8pt; font-weight: bold; }\n.MainBkgnd {b"\
	u"ackground-color : #d9d4aa; }\n.Info      {font-family: Ver"\
	u"dana, Arial, Helvetica, sans-serif; font-size: 12pt; font-"\
	u"weight: bold; }\n.NavBar    {color: #660000; background-co"\
	u"lor: #f5f5dc; font-family: Verdana, Arial, Helvetica, sans"\
	u"-serif; font-size: 8pt; font-weight: bold;text-decoration:"\
	u" none; }\n.Off       {color: #A0A0A0; }\n.Tip \t    {color"\
	u": #666666; font-family : Verdana, Arial, Helvetica, sans-s"\
	u"erif; font-weight : normal; font-size : 9pt; }\n--></style"\
	u">\n</head><body>"
#define HTMLTopTitleNoMargin u"<html><head><title>%s</title><style type=\"text/css\"><!--"\
	u"\nbody       {font-family: Verdana, Arial, Helvetica, sans"\
	u"-serif; font-size: 9pt; margin-left: 0px; margin-top: 0px;"\
	u" margin-right: 0px; }\nh1         {color: #333333; font-si"\
	u"ze: 18pt; font-style: normal; font-weight: bold; }\nh2    "\
	u"     {color: #333333; font-size: 14pt; font-style: normal;"\
	u" font-weight: bold; }\nh3         {color: #333333; font-si"\
	u"ze: 12pt; font-style: normal; font-weight: bold; }\n.h1Sty"\
	u"le   {color: #333333; font-size: 18pt; font-style: normal;"\
	u" font-weight: bold; }\n.TblRow    {color: #333333; font-fa"\
	u"mily: Verdana, Arial, Helvetica, sans-serif; font-size: 10"\
	u"pt; font-weight: normal; }\n.TblRow1   {color: #333333; ba"\
	u"ckground-color: #f5f5dc; font-family: Verdana, Arial, Helv"\
	u"etica, sans-serif; font-size: 9pt; font-weight: normal; }\n"\
	u".TblRow0   {color: #333333; background-color: #d9d4aa; fon"\
	u"t-family: Verdana, Arial, Helvetica, sans-serif; font-size"\
	u": 9pt; font-weight: normal; }\n.TblHdr    {color: #CCCC99;"\
	u" background-color: #333333; font-family: Verdana, Arial, H"\
	u"elvetica, sans-serif; font-size: 10pt; font-weight: bold; "\
	u"text-align: center;}\n.IntfName  {color: #660000; font-fam"\
	u"ily: Verdana, Arial, Helvetica, sans-serif; font-size: 10p"\
	u"t; font-weight: bold; }\n.MethName  {color: #333333; font-"\
	u"family: Verdana, Arial, Helvetica, sans-serif; font-size: "\
	u"8pt; font-weight: bold; text-decoration: none; }\n.ParmNam"\
	u"e  {color: #333333; font-family: Verdana, Arial, Helvetica"\
	u", sans-serif; font-size: 8pt; text-decoration: none; }\n.N"\
	u"amespace {color: #333333; font-family: Verdana, Arial, Hel"\
	u"vetica, sans-serif; font-size: 9pt; font-style: italic; }\n"\
	u".WSDL      {color: #990000; font-family: Verdana, Arial, H"\
	u"elvetica, sans-serif; font-size: 8pt; font-weight: bold; }"\
	u"\n.MainBkgnd {background-color : #d9d4aa; }\n.Info      {f"\
	u"ont-family: Verdana, Arial, Helvetica, sans-serif; font-si"\
	u"ze: 12pt; font-weight: bold; }\n.NavBar    {color: #660000"\
	u"; background-color: #f5f5dc; font-family: Verdana, Arial, "\
	u"Helvetica, sans-serif; font-size: 8pt; font-weight: bold;t"\
	u"ext-decoration: none; }\n.Off       {color: #A0A0A0; }\n.T"\
	u"ip \t    {color: #666666; font-family : Verdana, Arial, He"\
	u"lvetica, sans-serif; font-weight : normal; font-size : 9pt"\
	u"; }\n--></style>\n</head><body>"
#define HTMLTopNoStyles u"<html><head></head><body>"
#define HTMLTopTitle u"<html><head><title>%s</title><style type=\"text/css\"><!--"\
	u"\nbody       {font-family: Verdana, Arial, Helvetica, sans"\
	u"-serif; font-size: 9pt; }\nh1         {color: #333333; fon"\
	u"t-size: 18pt; font-style: normal; font-weight: bold; }\nh2"\
	u"         {color: #333333; font-size: 14pt; font-style: nor"\
	u"mal; font-weight: bold; }\nh3         {color: #333333; fon"\
	u"t-size: 12pt; font-style: normal; font-weight: bold; }\n.h"\
	u"1Style   {color: #333333; font-size: 18pt; font-style: nor"\
	u"mal; font-weight: bold; }\n.TblRow    {color: #333333; fon"\
	u"t-family: Verdana, Arial, Helvetica, sans-serif; font-size"\
	u": 10pt; font-weight: normal; }\n.TblRow1   {color: #333333"\
	u"; background-color: #f5f5dc; font-family: Verdana, Arial, "\
	u"Helvetica, sans-serif; font-size: 9pt; font-weight: normal"\
	u"; }\n.TblRow0   {color: #333333; background-color: #d9d4aa"\
	u"; font-family: Verdana, Arial, Helvetica, sans-serif; font"\
	u"-size: 9pt; font-weight: normal; }\n.TblHdr    {color: #CC"\
	u"CC99; background-color: #333333; font-family: Verdana, Ari"\
	u"al, Helvetica, sans-serif; font-size: 10pt; font-weight: b"\
	u"old; text-align: center;}\n.IntfName  {color: #660000; fon"\
	u"t-family: Verdana, Arial, Helvetica, sans-serif; font-size"\
	u": 10pt; font-weight: bold; }\n.MethName  {color: #333333; "\
	u"font-family: Verdana, Arial, Helvetica, sans-serif; font-s"\
	u"ize: 8pt; font-weight: bold; text-decoration: none; }\n.Pa"\
	u"rmName  {color: #333333; font-family: Verdana, Arial, Helv"\
	u"etica, sans-serif; font-size: 8pt; text-decoration: none; "\
	u"}\n.Namespace {color: #333333; font-family: Verdana, Arial"\
	u", Helvetica, sans-serif; font-size: 9pt; font-style: itali"\
	u"c; }\n.WSDL      {color: #990000; font-family: Verdana, Ar"\
	u"ial, Helvetica, sans-serif; font-size: 8pt; font-weight: b"\
	u"old; }\n.MainBkgnd {background-color : #d9d4aa; }\n.Info  "\
	u"    {font-family: Verdana, Arial, Helvetica, sans-serif; f"\
	u"ont-size: 12pt; font-weight: bold; }\n.NavBar    {color: #"\
	u"660000; background-color: #f5f5dc; font-family: Verdana, A"\
	u"rial, Helvetica, sans-serif; font-size: 8pt; font-weight: "\
	u"bold;text-decoration: none; }\n.Off       {color: #A0A0A0;"\
	u" }\n.Tip \t    {color: #666666; font-family : Verdana, Ari"\
	u"al, Helvetica, sans-serif; font-weight : normal; font-size"\
	u" : 9pt; }\n--></style>\n</head><body>"
#define HTMLTopTitleNoMarginWSIL u"<html><head><META name=\"serviceInspection\" content=\"ins"\
	u"pection.wsil\"><title>%s</title><style type=\"text/css\"><"\
	u"!--\nbody       {font-family: Verdana, Arial, Helvetica, s"\
	u"ans-serif; font-size: 9pt; margin-left: 0px; margin-top: 0"\
	u"px; margin-right: 0px; }\nh1         {color: #333333; font"\
	u"-size: 18pt; font-style: normal; font-weight: bold; }\nh2 "\
	u"        {color: #333333; font-size: 14pt; font-style: norm"\
	u"al; font-weight: bold; }\nh3         {color: #333333; font"\
	u"-size: 12pt; font-style: normal; font-weight: bold; }\n.h1"\
	u"Style   {color: #333333; font-size: 18pt; font-style: norm"\
	u"al; font-weight: bold; }\n.TblRow    {color: #333333; font"\
	u"-family: Verdana, Arial, Helvetica, sans-serif; font-size:"\
	u" 10pt; font-weight: normal; }\n.TblRow1   {color: #333333;"\
	u" background-color: #f5f5dc; font-family: Verdana, Arial, H"\
	u"elvetica, sans-serif; font-size: 9pt; font-weight: normal;"\
	u" }\n.TblRow0   {color: #333333; background-color: #d9d4aa;"\
	u" font-family: Verdana, Arial, Helvetica, sans-serif; font-"\
	u"size: 9pt; font-weight: normal; }\n.TblHdr    {color: #CCC"\
	u"C99; background-color: #333333; font-family: Verdana, Aria"\
	u"l, Helvetica, sans-serif; font-size: 10pt; font-weight: bo"\
	u"ld; text-align: center;}\n.IntfName  {color: #660000; font"\
	u"-family: Verdana, Arial, Helvetica, sans-serif; font-size:"\
	u" 10pt; font-weight: bold; }\n.MethName  {color: #333333; f"\
	u"ont-family: Verdana, Arial, Helvetica, sans-serif; font-si"\
	u"ze: 8pt; font-weight: bold; text-decoration: none; }\n.Par"\
	u"mName  {color: #333333; font-family: Verdana, Arial, Helve"\
	u"tica, sans-serif; font-size: 8pt; text-decoration: none; }"\
	u"\n.Namespace {color: #333333; font-family: Verdana, Arial,"\
	u" Helvetica, sans-serif; font-size: 9pt; font-style: italic"\
	u"; }\n.WSDL      {color: #990000; font-family: Verdana, Ari"\
	u"al, Helvetica, sans-serif; font-size: 8pt; font-weight: bo"\
	u"ld; }\n.MainBkgnd {background-color : #d9d4aa; }\n.Info   "\
	u"   {font-family: Verdana, Arial, Helvetica, sans-serif; fo"\
	u"nt-size: 12pt; font-weight: bold; }\n.NavBar    {color: #6"\
	u"60000; background-color: #f5f5dc; font-family: Verdana, Ar"\
	u"ial, Helvetica, sans-serif; font-size: 8pt; font-weight: b"\
	u"old;text-decoration: none; }\n.Off       {color: #A0A0A0; "\
	u"}\n.Tip \t    {color: #666666; font-family : Verdana, Aria"\
	u"l, Helvetica, sans-serif; font-weight : normal; font-size "\
	u": 9pt; }\n--></style>\n</head><body>"
#define HTMLEnd u"</body></html>"
#define InfoTitle1 u"<table class=\"MainBkgnd\" border=0 cellpadding=0 cellspac"\
	u"ing=0 width=\"100%\"><tr><td>&nbsp;</td></tr>"
#define InfoTitle2 u"<tr><td class=\"h1Style\" align=\"center\">%s - %s</td></t"\
	u"r></table>"
extern DELPHI_PACKAGE Soap_Soapconst__8 TblCls;
#define sTblRow u"TblRow"
#define sTblHdrCls u"TblHdr"
#define sQueryStringIntf u"intf"
#define sQueryStringTypes u"types"
#define sNBSP u"&nbsp;"
extern DELPHI_PACKAGE System::UnicodeString XMLSchemaNameSpace;
extern DELPHI_PACKAGE System::UnicodeString XMLSchemaInstNameSpace;
extern DELPHI_PACKAGE System::ResourceString _SUnsupportedEncodingSyle;
#define Soap_Soapconst_SUnsupportedEncodingSyle System::LoadResourceString(&Soap::Soapconst::_SUnsupportedEncodingSyle)
extern DELPHI_PACKAGE System::ResourceString _SInvalidSoapRequest;
#define Soap_Soapconst_SInvalidSoapRequest System::LoadResourceString(&Soap::Soapconst::_SInvalidSoapRequest)
extern DELPHI_PACKAGE System::ResourceString _SInvalidSoapResponse;
#define Soap_Soapconst_SInvalidSoapResponse System::LoadResourceString(&Soap::Soapconst::_SInvalidSoapResponse)
extern DELPHI_PACKAGE System::ResourceString _SMultiBodyNotSupported;
#define Soap_Soapconst_SMultiBodyNotSupported System::LoadResourceString(&Soap::Soapconst::_SMultiBodyNotSupported)
extern DELPHI_PACKAGE System::ResourceString _SUnsupportedCC;
#define Soap_Soapconst_SUnsupportedCC System::LoadResourceString(&Soap::Soapconst::_SUnsupportedCC)
extern DELPHI_PACKAGE System::ResourceString _SUnsupportedCCIntfMeth;
#define Soap_Soapconst_SUnsupportedCCIntfMeth System::LoadResourceString(&Soap::Soapconst::_SUnsupportedCCIntfMeth)
extern DELPHI_PACKAGE System::ResourceString _SInvClassNotRegistered;
#define Soap_Soapconst_SInvClassNotRegistered System::LoadResourceString(&Soap::Soapconst::_SInvClassNotRegistered)
extern DELPHI_PACKAGE System::ResourceString _SInvInterfaceNotReg;
#define Soap_Soapconst_SInvInterfaceNotReg System::LoadResourceString(&Soap::Soapconst::_SInvInterfaceNotReg)
extern DELPHI_PACKAGE System::ResourceString _SInvInterfaceNotRegURL;
#define Soap_Soapconst_SInvInterfaceNotRegURL System::LoadResourceString(&Soap::Soapconst::_SInvInterfaceNotRegURL)
extern DELPHI_PACKAGE System::ResourceString _SRemTypeNotRegistered;
#define Soap_Soapconst_SRemTypeNotRegistered System::LoadResourceString(&Soap::Soapconst::_SRemTypeNotRegistered)
extern DELPHI_PACKAGE System::ResourceString _STypeMismatchInParam;
#define Soap_Soapconst_STypeMismatchInParam System::LoadResourceString(&Soap::Soapconst::_STypeMismatchInParam)
extern DELPHI_PACKAGE System::ResourceString _SNoSuchMethod;
#define Soap_Soapconst_SNoSuchMethod System::LoadResourceString(&Soap::Soapconst::_SNoSuchMethod)
extern DELPHI_PACKAGE System::ResourceString _SInterfaceNotReg;
#define Soap_Soapconst_SInterfaceNotReg System::LoadResourceString(&Soap::Soapconst::_SInterfaceNotReg)
extern DELPHI_PACKAGE System::ResourceString _SInterfaceNoRTTI;
#define Soap_Soapconst_SInterfaceNoRTTI System::LoadResourceString(&Soap::Soapconst::_SInterfaceNoRTTI)
extern DELPHI_PACKAGE System::ResourceString _SNoWSDL;
#define Soap_Soapconst_SNoWSDL System::LoadResourceString(&Soap::Soapconst::_SNoWSDL)
extern DELPHI_PACKAGE System::ResourceString _SWSDLError;
#define Soap_Soapconst_SWSDLError System::LoadResourceString(&Soap::Soapconst::_SWSDLError)
extern DELPHI_PACKAGE System::ResourceString _SEmptyWSDL;
#define Soap_Soapconst_SEmptyWSDL System::LoadResourceString(&Soap::Soapconst::_SEmptyWSDL)
extern DELPHI_PACKAGE System::ResourceString _sNoWSDLURL;
#define Soap_Soapconst_sNoWSDLURL System::LoadResourceString(&Soap::Soapconst::_sNoWSDLURL)
extern DELPHI_PACKAGE System::ResourceString _sCantGetURL;
#define Soap_Soapconst_sCantGetURL System::LoadResourceString(&Soap::Soapconst::_sCantGetURL)
extern DELPHI_PACKAGE System::ResourceString _SDataTypeNotSupported;
#define Soap_Soapconst_SDataTypeNotSupported System::LoadResourceString(&Soap::Soapconst::_SDataTypeNotSupported)
extern DELPHI_PACKAGE System::ResourceString _SUnknownSOAPAction;
#define Soap_Soapconst_SUnknownSOAPAction System::LoadResourceString(&Soap::Soapconst::_SUnknownSOAPAction)
extern DELPHI_PACKAGE System::ResourceString _SScalarFromTRemotableS;
#define Soap_Soapconst_SScalarFromTRemotableS System::LoadResourceString(&Soap::Soapconst::_SScalarFromTRemotableS)
extern DELPHI_PACKAGE System::ResourceString _SNoSerializeGraphs;
#define Soap_Soapconst_SNoSerializeGraphs System::LoadResourceString(&Soap::Soapconst::_SNoSerializeGraphs)
extern DELPHI_PACKAGE System::ResourceString _SUnsuportedClassType;
#define Soap_Soapconst_SUnsuportedClassType System::LoadResourceString(&Soap::Soapconst::_SUnsuportedClassType)
extern DELPHI_PACKAGE System::ResourceString _SUnexpectedDataType;
#define Soap_Soapconst_SUnexpectedDataType System::LoadResourceString(&Soap::Soapconst::_SUnexpectedDataType)
extern DELPHI_PACKAGE System::ResourceString _SInvalidContentType;
#define Soap_Soapconst_SInvalidContentType System::LoadResourceString(&Soap::Soapconst::_SInvalidContentType)
extern DELPHI_PACKAGE System::ResourceString _SArrayTooManyElem;
#define Soap_Soapconst_SArrayTooManyElem System::LoadResourceString(&Soap::Soapconst::_SArrayTooManyElem)
extern DELPHI_PACKAGE System::ResourceString _SWrongDocElem;
#define Soap_Soapconst_SWrongDocElem System::LoadResourceString(&Soap::Soapconst::_SWrongDocElem)
extern DELPHI_PACKAGE System::ResourceString _STooManyParameters;
#define Soap_Soapconst_STooManyParameters System::LoadResourceString(&Soap::Soapconst::_STooManyParameters)
extern DELPHI_PACKAGE System::ResourceString _SArrayExpected;
#define Soap_Soapconst_SArrayExpected System::LoadResourceString(&Soap::Soapconst::_SArrayExpected)
extern DELPHI_PACKAGE System::ResourceString _SNoInterfaceGUID;
#define Soap_Soapconst_SNoInterfaceGUID System::LoadResourceString(&Soap::Soapconst::_SNoInterfaceGUID)
extern DELPHI_PACKAGE System::ResourceString _SNoArrayElemRTTI;
#define Soap_Soapconst_SNoArrayElemRTTI System::LoadResourceString(&Soap::Soapconst::_SNoArrayElemRTTI)
extern DELPHI_PACKAGE System::ResourceString _SInvalidResponse;
#define Soap_Soapconst_SInvalidResponse System::LoadResourceString(&Soap::Soapconst::_SInvalidResponse)
extern DELPHI_PACKAGE System::ResourceString _SInvalidArraySpec;
#define Soap_Soapconst_SInvalidArraySpec System::LoadResourceString(&Soap::Soapconst::_SInvalidArraySpec)
extern DELPHI_PACKAGE System::ResourceString _SCannotFindNodeID;
#define Soap_Soapconst_SCannotFindNodeID System::LoadResourceString(&Soap::Soapconst::_SCannotFindNodeID)
extern DELPHI_PACKAGE System::ResourceString _SNoNativeNULL;
#define Soap_Soapconst_SNoNativeNULL System::LoadResourceString(&Soap::Soapconst::_SNoNativeNULL)
extern DELPHI_PACKAGE System::ResourceString _SFaultCodeOnlyAllowed;
#define Soap_Soapconst_SFaultCodeOnlyAllowed System::LoadResourceString(&Soap::Soapconst::_SFaultCodeOnlyAllowed)
extern DELPHI_PACKAGE System::ResourceString _SFaultStringOnlyAllowed;
#define Soap_Soapconst_SFaultStringOnlyAllowed System::LoadResourceString(&Soap::Soapconst::_SFaultStringOnlyAllowed)
extern DELPHI_PACKAGE System::ResourceString _SMissingFaultValue;
#define Soap_Soapconst_SMissingFaultValue System::LoadResourceString(&Soap::Soapconst::_SMissingFaultValue)
extern DELPHI_PACKAGE System::ResourceString _SNoInterfacesInClass;
#define Soap_Soapconst_SNoInterfacesInClass System::LoadResourceString(&Soap::Soapconst::_SNoInterfacesInClass)
extern DELPHI_PACKAGE System::ResourceString _SCantReturnInterface;
#define Soap_Soapconst_SCantReturnInterface System::LoadResourceString(&Soap::Soapconst::_SCantReturnInterface)
extern DELPHI_PACKAGE System::ResourceString _SVariantCastNotSupported;
#define Soap_Soapconst_SVariantCastNotSupported System::LoadResourceString(&Soap::Soapconst::_SVariantCastNotSupported)
extern DELPHI_PACKAGE System::ResourceString _SVarDateNotSupported;
#define Soap_Soapconst_SVarDateNotSupported System::LoadResourceString(&Soap::Soapconst::_SVarDateNotSupported)
extern DELPHI_PACKAGE System::ResourceString _SVarDispatchNotSupported;
#define Soap_Soapconst_SVarDispatchNotSupported System::LoadResourceString(&Soap::Soapconst::_SVarDispatchNotSupported)
extern DELPHI_PACKAGE System::ResourceString _SVarErrorNotSupported;
#define Soap_Soapconst_SVarErrorNotSupported System::LoadResourceString(&Soap::Soapconst::_SVarErrorNotSupported)
extern DELPHI_PACKAGE System::ResourceString _SVarVariantNotSupported;
#define Soap_Soapconst_SVarVariantNotSupported System::LoadResourceString(&Soap::Soapconst::_SVarVariantNotSupported)
extern DELPHI_PACKAGE System::ResourceString _SHeaderError;
#define Soap_Soapconst_SHeaderError System::LoadResourceString(&Soap::Soapconst::_SHeaderError)
extern DELPHI_PACKAGE System::ResourceString _SMissingSoapReturn;
#define Soap_Soapconst_SMissingSoapReturn System::LoadResourceString(&Soap::Soapconst::_SMissingSoapReturn)
extern DELPHI_PACKAGE System::ResourceString _SInvalidPointer;
#define Soap_Soapconst_SInvalidPointer System::LoadResourceString(&Soap::Soapconst::_SInvalidPointer)
extern DELPHI_PACKAGE System::ResourceString _SNoMessageConverter;
#define Soap_Soapconst_SNoMessageConverter System::LoadResourceString(&Soap::Soapconst::_SNoMessageConverter)
extern DELPHI_PACKAGE System::ResourceString _SNoMsgProcessingNode;
#define Soap_Soapconst_SNoMsgProcessingNode System::LoadResourceString(&Soap::Soapconst::_SNoMsgProcessingNode)
extern DELPHI_PACKAGE System::ResourceString _SHeaderAttributeError;
#define Soap_Soapconst_SHeaderAttributeError System::LoadResourceString(&Soap::Soapconst::_SHeaderAttributeError)
extern DELPHI_PACKAGE System::ResourceString _SNoRTTI;
#define Soap_Soapconst_SNoRTTI System::LoadResourceString(&Soap::Soapconst::_SNoRTTI)
extern DELPHI_PACKAGE System::ResourceString _SNoRTTIParam;
#define Soap_Soapconst_SNoRTTIParam System::LoadResourceString(&Soap::Soapconst::_SNoRTTIParam)
extern DELPHI_PACKAGE System::ResourceString _SInvalidDateString;
#define Soap_Soapconst_SInvalidDateString System::LoadResourceString(&Soap::Soapconst::_SInvalidDateString)
extern DELPHI_PACKAGE System::ResourceString _SInvalidTimeString;
#define Soap_Soapconst_SInvalidTimeString System::LoadResourceString(&Soap::Soapconst::_SInvalidTimeString)
extern DELPHI_PACKAGE System::ResourceString _SInvalidHour;
#define Soap_Soapconst_SInvalidHour System::LoadResourceString(&Soap::Soapconst::_SInvalidHour)
extern DELPHI_PACKAGE System::ResourceString _SInvalidMinute;
#define Soap_Soapconst_SInvalidMinute System::LoadResourceString(&Soap::Soapconst::_SInvalidMinute)
extern DELPHI_PACKAGE System::ResourceString _SInvalidSecond;
#define Soap_Soapconst_SInvalidSecond System::LoadResourceString(&Soap::Soapconst::_SInvalidSecond)
extern DELPHI_PACKAGE System::ResourceString _SInvalidFractionSecond;
#define Soap_Soapconst_SInvalidFractionSecond System::LoadResourceString(&Soap::Soapconst::_SInvalidFractionSecond)
extern DELPHI_PACKAGE System::ResourceString _SInvalidMillisecond;
#define Soap_Soapconst_SInvalidMillisecond System::LoadResourceString(&Soap::Soapconst::_SInvalidMillisecond)
extern DELPHI_PACKAGE System::ResourceString _SInvalidFractionalSecond;
#define Soap_Soapconst_SInvalidFractionalSecond System::LoadResourceString(&Soap::Soapconst::_SInvalidFractionalSecond)
extern DELPHI_PACKAGE System::ResourceString _SInvalidHourOffset;
#define Soap_Soapconst_SInvalidHourOffset System::LoadResourceString(&Soap::Soapconst::_SInvalidHourOffset)
extern DELPHI_PACKAGE System::ResourceString _SInvalidDay;
#define Soap_Soapconst_SInvalidDay System::LoadResourceString(&Soap::Soapconst::_SInvalidDay)
extern DELPHI_PACKAGE System::ResourceString _SInvalidMonth;
#define Soap_Soapconst_SInvalidMonth System::LoadResourceString(&Soap::Soapconst::_SInvalidMonth)
extern DELPHI_PACKAGE System::ResourceString _SInvalidDuration;
#define Soap_Soapconst_SInvalidDuration System::LoadResourceString(&Soap::Soapconst::_SInvalidDuration)
extern DELPHI_PACKAGE System::ResourceString _SMilSecRangeViolation;
#define Soap_Soapconst_SMilSecRangeViolation System::LoadResourceString(&Soap::Soapconst::_SMilSecRangeViolation)
extern DELPHI_PACKAGE System::ResourceString _SInvalidYearConversion;
#define Soap_Soapconst_SInvalidYearConversion System::LoadResourceString(&Soap::Soapconst::_SInvalidYearConversion)
extern DELPHI_PACKAGE System::ResourceString _SInvalidTimeOffset;
#define Soap_Soapconst_SInvalidTimeOffset System::LoadResourceString(&Soap::Soapconst::_SInvalidTimeOffset)
extern DELPHI_PACKAGE System::ResourceString _SInvalidDecimalString;
#define Soap_Soapconst_SInvalidDecimalString System::LoadResourceString(&Soap::Soapconst::_SInvalidDecimalString)
extern DELPHI_PACKAGE System::ResourceString _SEmptyDecimalString;
#define Soap_Soapconst_SEmptyDecimalString System::LoadResourceString(&Soap::Soapconst::_SEmptyDecimalString)
extern DELPHI_PACKAGE System::ResourceString _SNoSciNotation;
#define Soap_Soapconst_SNoSciNotation System::LoadResourceString(&Soap::Soapconst::_SNoSciNotation)
extern DELPHI_PACKAGE System::ResourceString _SNoNAN;
#define Soap_Soapconst_SNoNAN System::LoadResourceString(&Soap::Soapconst::_SNoNAN)
extern DELPHI_PACKAGE System::ResourceString _SInvalidBcd;
#define Soap_Soapconst_SInvalidBcd System::LoadResourceString(&Soap::Soapconst::_SInvalidBcd)
extern DELPHI_PACKAGE System::ResourceString _SBcdStringTooBig;
#define Soap_Soapconst_SBcdStringTooBig System::LoadResourceString(&Soap::Soapconst::_SBcdStringTooBig)
extern DELPHI_PACKAGE System::ResourceString _SInvalidHexValue;
#define Soap_Soapconst_SInvalidHexValue System::LoadResourceString(&Soap::Soapconst::_SInvalidHexValue)
extern DELPHI_PACKAGE System::ResourceString _SInvalidHTTPRequest;
#define Soap_Soapconst_SInvalidHTTPRequest System::LoadResourceString(&Soap::Soapconst::_SInvalidHTTPRequest)
extern DELPHI_PACKAGE System::ResourceString _SInvalidHTTPResponse;
#define Soap_Soapconst_SInvalidHTTPResponse System::LoadResourceString(&Soap::Soapconst::_SInvalidHTTPResponse)
extern DELPHI_PACKAGE System::ResourceString _SInvalidBooleanParameter;
#define Soap_Soapconst_SInvalidBooleanParameter System::LoadResourceString(&Soap::Soapconst::_SInvalidBooleanParameter)
extern DELPHI_PACKAGE System::ResourceString _SWideStringOutOfBounds;
#define Soap_Soapconst_SWideStringOutOfBounds System::LoadResourceString(&Soap::Soapconst::_SWideStringOutOfBounds)
extern DELPHI_PACKAGE System::ResourceString _IWSDLPublishDoc;
#define Soap_Soapconst_IWSDLPublishDoc System::LoadResourceString(&Soap::Soapconst::_IWSDLPublishDoc)
extern DELPHI_PACKAGE System::ResourceString _sPortNameHeader;
#define Soap_Soapconst_sPortNameHeader System::LoadResourceString(&Soap::Soapconst::_sPortNameHeader)
extern DELPHI_PACKAGE System::ResourceString _sAddressHeader;
#define Soap_Soapconst_sAddressHeader System::LoadResourceString(&Soap::Soapconst::_sAddressHeader)
extern DELPHI_PACKAGE System::ResourceString _sAdminButtonCation;
#define Soap_Soapconst_sAdminButtonCation System::LoadResourceString(&Soap::Soapconst::_sAdminButtonCation)
extern DELPHI_PACKAGE System::ResourceString _sAddButtonCaption;
#define Soap_Soapconst_sAddButtonCaption System::LoadResourceString(&Soap::Soapconst::_sAddButtonCaption)
extern DELPHI_PACKAGE System::ResourceString _sDeleteButtonCaption;
#define Soap_Soapconst_sDeleteButtonCaption System::LoadResourceString(&Soap::Soapconst::_sDeleteButtonCaption)
extern DELPHI_PACKAGE System::ResourceString _SNoServiceForURL;
#define Soap_Soapconst_SNoServiceForURL System::LoadResourceString(&Soap::Soapconst::_SNoServiceForURL)
extern DELPHI_PACKAGE System::ResourceString _SNoInterfaceForURL;
#define Soap_Soapconst_SNoInterfaceForURL System::LoadResourceString(&Soap::Soapconst::_SNoInterfaceForURL)
extern DELPHI_PACKAGE System::ResourceString _SNoClassRegisteredForURL;
#define Soap_Soapconst_SNoClassRegisteredForURL System::LoadResourceString(&Soap::Soapconst::_SNoClassRegisteredForURL)
extern DELPHI_PACKAGE System::ResourceString _SEmptyURL;
#define Soap_Soapconst_SEmptyURL System::LoadResourceString(&Soap::Soapconst::_SEmptyURL)
extern DELPHI_PACKAGE System::ResourceString _SInvalidURL;
#define Soap_Soapconst_SInvalidURL System::LoadResourceString(&Soap::Soapconst::_SInvalidURL)
extern DELPHI_PACKAGE System::ResourceString _SNoClassRegistered;
#define Soap_Soapconst_SNoClassRegistered System::LoadResourceString(&Soap::Soapconst::_SNoClassRegistered)
extern DELPHI_PACKAGE System::ResourceString _SNoDispatcher;
#define Soap_Soapconst_SNoDispatcher System::LoadResourceString(&Soap::Soapconst::_SNoDispatcher)
extern DELPHI_PACKAGE System::ResourceString _SMethNoRTTI;
#define Soap_Soapconst_SMethNoRTTI System::LoadResourceString(&Soap::Soapconst::_SMethNoRTTI)
extern DELPHI_PACKAGE System::ResourceString _SUnsupportedVariant;
#define Soap_Soapconst_SUnsupportedVariant System::LoadResourceString(&Soap::Soapconst::_SUnsupportedVariant)
extern DELPHI_PACKAGE System::ResourceString _SNoVarDispatch;
#define Soap_Soapconst_SNoVarDispatch System::LoadResourceString(&Soap::Soapconst::_SNoVarDispatch)
extern DELPHI_PACKAGE System::ResourceString _SNoErrorDispatch;
#define Soap_Soapconst_SNoErrorDispatch System::LoadResourceString(&Soap::Soapconst::_SNoErrorDispatch)
extern DELPHI_PACKAGE System::ResourceString _SUnknownInterface;
#define Soap_Soapconst_SUnknownInterface System::LoadResourceString(&Soap::Soapconst::_SUnknownInterface)
extern DELPHI_PACKAGE System::ResourceString _SInvalidTimeZone;
#define Soap_Soapconst_SInvalidTimeZone System::LoadResourceString(&Soap::Soapconst::_SInvalidTimeZone)
extern DELPHI_PACKAGE System::ResourceString _sUnknownError;
#define Soap_Soapconst_sUnknownError System::LoadResourceString(&Soap::Soapconst::_sUnknownError)
extern DELPHI_PACKAGE System::ResourceString _sErrorColon;
#define Soap_Soapconst_sErrorColon System::LoadResourceString(&Soap::Soapconst::_sErrorColon)
extern DELPHI_PACKAGE System::ResourceString _sServiceInfo;
#define Soap_Soapconst_sServiceInfo System::LoadResourceString(&Soap::Soapconst::_sServiceInfo)
extern DELPHI_PACKAGE System::ResourceString _sInterfaceInfo;
#define Soap_Soapconst_sInterfaceInfo System::LoadResourceString(&Soap::Soapconst::_sInterfaceInfo)
extern DELPHI_PACKAGE System::ResourceString _sWSILInfo;
#define Soap_Soapconst_sWSILInfo System::LoadResourceString(&Soap::Soapconst::_sWSILInfo)
extern DELPHI_PACKAGE System::ResourceString _sWSILLink;
#define Soap_Soapconst_sWSILLink System::LoadResourceString(&Soap::Soapconst::_sWSILLink)
extern DELPHI_PACKAGE System::ResourceString _sRegTypes;
#define Soap_Soapconst_sRegTypes System::LoadResourceString(&Soap::Soapconst::_sRegTypes)
extern DELPHI_PACKAGE System::ResourceString _sWebServiceListing;
#define Soap_Soapconst_sWebServiceListing System::LoadResourceString(&Soap::Soapconst::_sWebServiceListing)
extern DELPHI_PACKAGE System::ResourceString _sWebServiceListingAdmin;
#define Soap_Soapconst_sWebServiceListingAdmin System::LoadResourceString(&Soap::Soapconst::_sWebServiceListingAdmin)
extern DELPHI_PACKAGE System::ResourceString _sPortType;
#define Soap_Soapconst_sPortType System::LoadResourceString(&Soap::Soapconst::_sPortType)
extern DELPHI_PACKAGE System::ResourceString _sNameSpaceURI;
#define Soap_Soapconst_sNameSpaceURI System::LoadResourceString(&Soap::Soapconst::_sNameSpaceURI)
extern DELPHI_PACKAGE System::ResourceString _sDocumentation;
#define Soap_Soapconst_sDocumentation System::LoadResourceString(&Soap::Soapconst::_sDocumentation)
extern DELPHI_PACKAGE System::ResourceString _sWSDL;
#define Soap_Soapconst_sWSDL System::LoadResourceString(&Soap::Soapconst::_sWSDL)
extern DELPHI_PACKAGE System::ResourceString _sPortName;
#define Soap_Soapconst_sPortName System::LoadResourceString(&Soap::Soapconst::_sPortName)
extern DELPHI_PACKAGE System::ResourceString _sInterfaceNotFound;
#define Soap_Soapconst_sInterfaceNotFound System::LoadResourceString(&Soap::Soapconst::_sInterfaceNotFound)
extern DELPHI_PACKAGE System::ResourceString _sForbiddenAccess;
#define Soap_Soapconst_sForbiddenAccess System::LoadResourceString(&Soap::Soapconst::_sForbiddenAccess)
extern DELPHI_PACKAGE System::ResourceString _sWSDLPortsforPortType;
#define Soap_Soapconst_sWSDLPortsforPortType System::LoadResourceString(&Soap::Soapconst::_sWSDLPortsforPortType)
extern DELPHI_PACKAGE System::ResourceString _sWSDLFor;
#define Soap_Soapconst_sWSDLFor System::LoadResourceString(&Soap::Soapconst::_sWSDLFor)
extern DELPHI_PACKAGE System::ResourceString _sServiceInfoPage;
#define Soap_Soapconst_sServiceInfoPage System::LoadResourceString(&Soap::Soapconst::_sServiceInfoPage)
extern DELPHI_PACKAGE System::ResourceString _SEmptyStream;
#define Soap_Soapconst_SEmptyStream System::LoadResourceString(&Soap::Soapconst::_SEmptyStream)
extern DELPHI_PACKAGE System::ResourceString _SMethodNotSupported;
#define Soap_Soapconst_SMethodNotSupported System::LoadResourceString(&Soap::Soapconst::_SMethodNotSupported)
extern DELPHI_PACKAGE System::ResourceString _SInvalidMethod;
#define Soap_Soapconst_SInvalidMethod System::LoadResourceString(&Soap::Soapconst::_SInvalidMethod)
extern DELPHI_PACKAGE System::ResourceString _SNoContentLength;
#define Soap_Soapconst_SNoContentLength System::LoadResourceString(&Soap::Soapconst::_SNoContentLength)
extern DELPHI_PACKAGE System::ResourceString _SInvalidContentLength;
#define Soap_Soapconst_SInvalidContentLength System::LoadResourceString(&Soap::Soapconst::_SInvalidContentLength)
extern DELPHI_PACKAGE System::ResourceString _SMimeReadError;
#define Soap_Soapconst_SMimeReadError System::LoadResourceString(&Soap::Soapconst::_SMimeReadError)
extern DELPHI_PACKAGE System::ResourceString _STempFileAccessError;
#define Soap_Soapconst_STempFileAccessError System::LoadResourceString(&Soap::Soapconst::_STempFileAccessError)
extern DELPHI_PACKAGE System::ResourceString _SSOAPServerIIDFmt;
#define Soap_Soapconst_SSOAPServerIIDFmt System::LoadResourceString(&Soap::Soapconst::_SSOAPServerIIDFmt)
extern DELPHI_PACKAGE System::ResourceString _SNoURL;
#define Soap_Soapconst_SNoURL System::LoadResourceString(&Soap::Soapconst::_SNoURL)
extern DELPHI_PACKAGE System::ResourceString _SSOAPInterfaceNotRegistered;
#define Soap_Soapconst_SSOAPInterfaceNotRegistered System::LoadResourceString(&Soap::Soapconst::_SSOAPInterfaceNotRegistered)
extern DELPHI_PACKAGE System::ResourceString _SSOAPInterfaceNotRemotable;
#define Soap_Soapconst_SSOAPInterfaceNotRemotable System::LoadResourceString(&Soap::Soapconst::_SSOAPInterfaceNotRemotable)
extern DELPHI_PACKAGE System::ResourceString _SCantLoadLocation;
#define Soap_Soapconst_SCantLoadLocation System::LoadResourceString(&Soap::Soapconst::_SCantLoadLocation)
}	/* namespace Soapconst */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPCONST)
using namespace Soap::Soapconst;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoapconstHPP
