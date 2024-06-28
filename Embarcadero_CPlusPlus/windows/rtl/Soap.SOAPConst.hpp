// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPConst.pas' rev: 34.00 (Windows)

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

typedef System::StaticArray<System::UnicodeString, 2> Soap_Soapconst__7;

//-- var, const, procedure ---------------------------------------------------
#define SHTTPPrefix L"http://"
#define SContentId L"Content-ID"
#define SContentLocation L"Content-Location"
#define SContentLength L"Content-Length"
#define SContentType L"Content-Type"
#define SWSDLMIMENamespace L"http://schemas.xmlsoap.org/wsdl/mime/"
#define SBorlandMimeBoundary L"MIME_boundaryB0R9532143182121"
#define SSoapXMLHeader L"<?xml version=\"1.0\" encoding='UTF-8'?>"
#define SUTF8 L"UTF-8"
#define ContentTypeTemplate L"Content-Type: %s"
#define ContentTypeWithActionFmt L"Content-Type: %s;action=\"%s\""
#define ContentTypeWithActionNoLabelFmt L"%s;action=\"%s\""
#define ContentTypeApplicationBinary L"application/binary"
#define SBinaryEncoding L"binary"
#define S8BitEncoding L"8bit"
#define ContentTypeTextPlain L"text/plain"
#define SCharacterEncodingFormat L"Content-transfer-encoding: %s"
#define SCharacterEncoding L"Content-transfer-encoding"
#define SBoundary L"boundary="
#define SMultiPartRelated L"multipart/related"
#define SMultiPartRelatedNoSlash L"multipartRelated"
#define ContentHeaderMime L"multipart/related; boundary=%s"
#define SStart L"; start=\"<%s>\""
#define SBorlandSoapStart L"http://www.borland.com/rootpart.xml"
#define SAttachmentIdPrefix L"cid:"
#define MimeVersionName L"MIME-Version"
#define MimeVersionValue L"1.0"
#define MimeVersion L"MIME-Version: 1.0"
#define sTextHtml L"text/html"
#define sTextHtmlUTF8 L"text/html; charset=utf-8"
#define sTextXML L"text/xml"
#define ContentTypeUTF8 L"text/xml; charset=utf-8"
#define ContentTypeNoUTF8 L"text/xml"
#define ContentType12UTF8 L"application/soap+xml; charset=utf-8"
#define ContentType12NoUTF8 L"application/soap+xml"
#define SSoapNamespace L"http://schemas.xmlsoap.org/soap/envelope/"
#define SSoap12Namespace L"http://www.w3.org/2003/05/soap-envelope"
extern DELPHI_PACKAGE Soap_Soapconst__1 SOAPEnvelopeNamespaces;
#define SXMLNS L"xmlns"
#define SSoapEncodingAttr L"encodingStyle"
#define SSoap11EncodingS5 L"http://schemas.xmlsoap.org/soap/encoding/"
#define SSoap12EncodingNamespace L"http://www.w3.org/2003/05/soap-encoding"
extern DELPHI_PACKAGE Soap_Soapconst__2 SOAPEncodingNamespaces;
#define SSOAP12RPCNamespace L"http://www.w3.org/2003/05/soap-rpc"
#define SSoapEncodingArray L"Array"
#define SSoapEncodingArrayType L"arrayType"
#define SSoap12EncodingArrayType L"itemType"
extern DELPHI_PACKAGE Soap_Soapconst__3 SSoapEncodingArrayTypes;
#define SSoap12EncodingArraySize L"arraySize"
#define SSoapHTTPTransport L"http://schemas.xmlsoap.org/soap/http"
#define SSoapBodyUseEncoded L"encoded"
#define SSoapBodyUseLiteral L"literal"
#define SSoapEnvelope L"Envelope"
#define SSoapHeader L"Header"
#define SSoapBody L"Body"
#define SSoapResponseSuff L"Response"
#define SRequired L"required"
#define SSoapActor L"actor"
#define STrue L"true"
#define SSoapServerFaultCode L"Server"
#define SSoapServerFaultString L"Server Error"
#define SSoapFault L"Fault"
#define SSoapFaultCode L"faultcode"
#define SSoapFaultString L"faultstring"
#define SSoapFaultActor L"faultactor"
#define SSoapFaultDetails L"detail"
#define SFaultCodeMustUnderstand L"MustUnderstand"
#define SSOAP12FaultCode L"Code"
#define SSOAP12FaultSubCode L"Subcode"
#define SSOAP12FaultReason L"Reason"
#define SSOAP12FaultReasonLang L"lang"
#define SSOAP12FaultNode L"Node"
#define SSOAP12FaultRole L"Role"
#define SSOAP12FaultDetail L"Detail"
#define SSOAP12FaultText L"Text"
#define SHTTPSoapAction L"SOAPAction"
#define SHeaderMustUnderstand L"mustUnderstand"
#define SHeaderActor L"actor"
#define SActorNext L"http://schemas.xmlsoap.org/soap/actor/next"
#define SSoapType L"type"
#define SSoapResponse L"Response"
#define SDefaultReturnName L"return"
#define SDefaultResultName L"result"
#define SXMLID L"id"
#define SXMLHREF L"href"
#define SSOAP12XMLHREF L"ref"
extern DELPHI_PACKAGE Soap_Soapconst__4 SSOAPXMLHREFs;
#define SSoapNULL L"NULL"
#define SSoapNIL L"nil"
#define SSoapNillable L"nillable"
#define SOptional L"optional"
#define SElemForm L"form"
#define SUnqualified L"unqualified"
static const System::WideChar SHREFPre = (System::WideChar)(0x23);
#define SSOAP12HREFPre L""
extern DELPHI_PACKAGE Soap_Soapconst__5 SSOAPHREFPres;
#define SArrayIDPre L"Array-"
static const System::WideChar SDefVariantElemName = (System::WideChar)(0x56);
#define SDefaultBaseURI L"thismessage:/"
#define SDelphiTypeNamespace L"http://www.borland.com/namespaces/Delphi/Types"
#define SBorlandTypeNamespace L"http://www.borland.com/namespaces/Types"
#define SOperationNameSpecifier L"%operationName%"
#define SDefaultReturnParamNames L"Result;Return"
#define sReturnParamDelimiters L";,/:"
extern DELPHI_PACKAGE Soap_Soapconst__6 KindNameArray;
#define SSoapNameSpacePre L"SOAP-ENV"
#define SXMLSchemaNameSpacePre L"xsd"
#define SXMLSchemaInstNameSpace99Pre L"xsi"
#define SSoapEncodingPre L"SOAP-ENC"
#define SCharset L"charset"
#define sDefaultColor L"#333333"
#define sIntfColor L"#660000"
#define sTblHdrColor L"#CCCC99"
#define sTblColor1 L"#f5f5dc"
#define sTblColor0 L"#d9d4aa"
#define sBkgndColor L"#d9d4aa"
#define sTipColor L"#666666"
#define sWSDLColor L"#990000"
#define sOFFColor L"#A0A0A0"
#define sNavBarColor L"#660000"
#define sNavBkColor L"#f5f5dc"
#define HTMLStylBeg L"<style type=\"text/css\"><!--\r\n"
#define HTMLStylEnd L"--></style>\r\n"
#define BodyStyle1 L"body       {font-family: Verdana, Arial, Helvetica, sans-s"\
	L"erif; font-size: 9pt; }\r\n"
#define BodyStyle2 L"body       {font-family: Verdana, Arial, Helvetica, sans-s"\
	L"erif; font-size: 9pt; margin-left: 0px; margin-top: 0px; m"\
	L"argin-right: 0px; }\r\n"
#define OtherStyles L"h1         {color: #333333; font-size: 18pt; font-style: n"\
	L"ormal; font-weight: bold; }\r\nh2         {color: #333333;"\
	L" font-size: 14pt; font-style: normal; font-weight: bold; }"\
	L"\r\nh3         {color: #333333; font-size: 12pt; font-styl"\
	L"e: normal; font-weight: bold; }\r\n.h1Style   {color: #333"\
	L"333; font-size: 18pt; font-style: normal; font-weight: bol"\
	L"d; }\r\n.TblRow    {color: #333333; font-family: Verdana, "\
	L"Arial, Helvetica, sans-serif; font-size: 10pt; font-weight"\
	L": normal; }\r\n.TblRow1   {color: #333333; background-colo"\
	L"r: #f5f5dc; font-family: Verdana, Arial, Helvetica, sans-s"\
	L"erif; font-size: 9pt; font-weight: normal; }\r\n.TblRow0  "\
	L" {color: #333333; background-color: #d9d4aa; font-family: "\
	L"Verdana, Arial, Helvetica, sans-serif; font-size: 9pt; fon"\
	L"t-weight: normal; }\r\n.TblHdr    {color: #CCCC99; backgro"\
	L"und-color: #333333; font-family: Verdana, Arial, Helvetica"\
	L", sans-serif; font-size: 10pt; font-weight: bold; text-ali"\
	L"gn: center;}\r\n.IntfName  {color: #660000; font-family: V"\
	L"erdana, Arial, Helvetica, sans-serif; font-size: 10pt; fon"\
	L"t-weight: bold; }\r\n.MethName  {color: #333333; font-fami"\
	L"ly: Verdana, Arial, Helvetica, sans-serif; font-size: 8pt;"\
	L" font-weight: bold; text-decoration: none; }\r\n.ParmName "\
	L" {color: #333333; font-family: Verdana, Arial, Helvetica, "\
	L"sans-serif; font-size: 8pt; text-decoration: none; }\r\n.N"\
	L"amespace {color: #333333; font-family: Verdana, Arial, Hel"\
	L"vetica, sans-serif; font-size: 9pt; font-style: italic; }\r"\
	L"\n.WSDL      {color: #990000; font-family: Verdana, Arial,"\
	L" Helvetica, sans-serif; font-size: 8pt; font-weight: bold;"\
	L" }\r\n.MainBkgnd {background-color : #d9d4aa; }\r\n.Info  "\
	L"    {font-family: Verdana, Arial, Helvetica, sans-serif; f"\
	L"ont-size: 12pt; font-weight: bold; }\r\n.NavBar    {color:"\
	L" #660000; background-color: #f5f5dc; font-family: Verdana,"\
	L" Arial, Helvetica, sans-serif; font-size: 8pt; font-weight"\
	L": bold;text-decoration: none; }\r\n.Off       {color: #A0A"\
	L"0A0; }\r\n.Tip \t    {color: #666666; font-family : Verdan"\
	L"a, Arial, Helvetica, sans-serif; font-weight : normal; fon"\
	L"t-size : 9pt; }\r\n"
#define HTMLStyles L"<style type=\"text/css\"><!--\r\nbody       {font-family: "\
	L"Verdana, Arial, Helvetica, sans-serif; font-size: 9pt; }\r"\
	L"\nh1         {color: #333333; font-size: 18pt; font-style:"\
	L" normal; font-weight: bold; }\r\nh2         {color: #33333"\
	L"3; font-size: 14pt; font-style: normal; font-weight: bold;"\
	L" }\r\nh3         {color: #333333; font-size: 12pt; font-st"\
	L"yle: normal; font-weight: bold; }\r\n.h1Style   {color: #3"\
	L"33333; font-size: 18pt; font-style: normal; font-weight: b"\
	L"old; }\r\n.TblRow    {color: #333333; font-family: Verdana"\
	L", Arial, Helvetica, sans-serif; font-size: 10pt; font-weig"\
	L"ht: normal; }\r\n.TblRow1   {color: #333333; background-co"\
	L"lor: #f5f5dc; font-family: Verdana, Arial, Helvetica, sans"\
	L"-serif; font-size: 9pt; font-weight: normal; }\r\n.TblRow0"\
	L"   {color: #333333; background-color: #d9d4aa; font-family"\
	L": Verdana, Arial, Helvetica, sans-serif; font-size: 9pt; f"\
	L"ont-weight: normal; }\r\n.TblHdr    {color: #CCCC99; backg"\
	L"round-color: #333333; font-family: Verdana, Arial, Helveti"\
	L"ca, sans-serif; font-size: 10pt; font-weight: bold; text-a"\
	L"lign: center;}\r\n.IntfName  {color: #660000; font-family:"\
	L" Verdana, Arial, Helvetica, sans-serif; font-size: 10pt; f"\
	L"ont-weight: bold; }\r\n.MethName  {color: #333333; font-fa"\
	L"mily: Verdana, Arial, Helvetica, sans-serif; font-size: 8p"\
	L"t; font-weight: bold; text-decoration: none; }\r\n.ParmNam"\
	L"e  {color: #333333; font-family: Verdana, Arial, Helvetica"\
	L", sans-serif; font-size: 8pt; text-decoration: none; }\r\n"\
	L".Namespace {color: #333333; font-family: Verdana, Arial, H"\
	L"elvetica, sans-serif; font-size: 9pt; font-style: italic; "\
	L"}\r\n.WSDL      {color: #990000; font-family: Verdana, Ari"\
	L"al, Helvetica, sans-serif; font-size: 8pt; font-weight: bo"\
	L"ld; }\r\n.MainBkgnd {background-color : #d9d4aa; }\r\n.Inf"\
	L"o      {font-family: Verdana, Arial, Helvetica, sans-serif"\
	L"; font-size: 12pt; font-weight: bold; }\r\n.NavBar    {col"\
	L"or: #660000; background-color: #f5f5dc; font-family: Verda"\
	L"na, Arial, Helvetica, sans-serif; font-size: 8pt; font-wei"\
	L"ght: bold;text-decoration: none; }\r\n.Off       {color: #"\
	L"A0A0A0; }\r\n.Tip \t    {color: #666666; font-family : Ver"\
	L"dana, Arial, Helvetica, sans-serif; font-weight : normal; "\
	L"font-size : 9pt; }\r\n--></style>\r\n"
#define HTMLNoMargin L"<style type=\"text/css\"><!--\r\nbody       {font-family: "\
	L"Verdana, Arial, Helvetica, sans-serif; font-size: 9pt; mar"\
	L"gin-left: 0px; margin-top: 0px; margin-right: 0px; }\r\nh1"\
	L"         {color: #333333; font-size: 18pt; font-style: nor"\
	L"mal; font-weight: bold; }\r\nh2         {color: #333333; f"\
	L"ont-size: 14pt; font-style: normal; font-weight: bold; }\r"\
	L"\nh3         {color: #333333; font-size: 12pt; font-style:"\
	L" normal; font-weight: bold; }\r\n.h1Style   {color: #33333"\
	L"3; font-size: 18pt; font-style: normal; font-weight: bold;"\
	L" }\r\n.TblRow    {color: #333333; font-family: Verdana, Ar"\
	L"ial, Helvetica, sans-serif; font-size: 10pt; font-weight: "\
	L"normal; }\r\n.TblRow1   {color: #333333; background-color:"\
	L" #f5f5dc; font-family: Verdana, Arial, Helvetica, sans-ser"\
	L"if; font-size: 9pt; font-weight: normal; }\r\n.TblRow0   {"\
	L"color: #333333; background-color: #d9d4aa; font-family: Ve"\
	L"rdana, Arial, Helvetica, sans-serif; font-size: 9pt; font-"\
	L"weight: normal; }\r\n.TblHdr    {color: #CCCC99; backgroun"\
	L"d-color: #333333; font-family: Verdana, Arial, Helvetica, "\
	L"sans-serif; font-size: 10pt; font-weight: bold; text-align"\
	L": center;}\r\n.IntfName  {color: #660000; font-family: Ver"\
	L"dana, Arial, Helvetica, sans-serif; font-size: 10pt; font-"\
	L"weight: bold; }\r\n.MethName  {color: #333333; font-family"\
	L": Verdana, Arial, Helvetica, sans-serif; font-size: 8pt; f"\
	L"ont-weight: bold; text-decoration: none; }\r\n.ParmName  {"\
	L"color: #333333; font-family: Verdana, Arial, Helvetica, sa"\
	L"ns-serif; font-size: 8pt; text-decoration: none; }\r\n.Nam"\
	L"espace {color: #333333; font-family: Verdana, Arial, Helve"\
	L"tica, sans-serif; font-size: 9pt; font-style: italic; }\r\n"\
	L".WSDL      {color: #990000; font-family: Verdana, Arial, H"\
	L"elvetica, sans-serif; font-size: 8pt; font-weight: bold; }"\
	L"\r\n.MainBkgnd {background-color : #d9d4aa; }\r\n.Info    "\
	L"  {font-family: Verdana, Arial, Helvetica, sans-serif; fon"\
	L"t-size: 12pt; font-weight: bold; }\r\n.NavBar    {color: #"\
	L"660000; background-color: #f5f5dc; font-family: Verdana, A"\
	L"rial, Helvetica, sans-serif; font-size: 8pt; font-weight: "\
	L"bold;text-decoration: none; }\r\n.Off       {color: #A0A0A"\
	L"0; }\r\n.Tip \t    {color: #666666; font-family : Verdana,"\
	L" Arial, Helvetica, sans-serif; font-weight : normal; font-"\
	L"size : 9pt; }\r\n--></style>\r\n"
#define TableStyle L"border=1 cellspacing=1 cellpadding=2 "
extern DELPHI_PACKAGE System::ResourceString _HTMLContentLanguage;
#define Soap_Soapconst_HTMLContentLanguage System::LoadResourceString(&Soap::Soapconst::_HTMLContentLanguage)
#define HTMLHead L"<html><head>"
#define HTMLServiceInspection L"<META name=\"serviceInspection\" content=\"inspection.wsil"\
	L"\">"
#define HTMLTopPlain L"<html><head></head><body>"
#define HTMLTop L"<html><head><style type=\"text/css\"><!--\r\nbody       {f"\
	L"ont-family: Verdana, Arial, Helvetica, sans-serif; font-si"\
	L"ze: 9pt; }\r\nh1         {color: #333333; font-size: 18pt;"\
	L" font-style: normal; font-weight: bold; }\r\nh2         {c"\
	L"olor: #333333; font-size: 14pt; font-style: normal; font-w"\
	L"eight: bold; }\r\nh3         {color: #333333; font-size: 1"\
	L"2pt; font-style: normal; font-weight: bold; }\r\n.h1Style "\
	L"  {color: #333333; font-size: 18pt; font-style: normal; fo"\
	L"nt-weight: bold; }\r\n.TblRow    {color: #333333; font-fam"\
	L"ily: Verdana, Arial, Helvetica, sans-serif; font-size: 10p"\
	L"t; font-weight: normal; }\r\n.TblRow1   {color: #333333; b"\
	L"ackground-color: #f5f5dc; font-family: Verdana, Arial, Hel"\
	L"vetica, sans-serif; font-size: 9pt; font-weight: normal; }"\
	L"\r\n.TblRow0   {color: #333333; background-color: #d9d4aa;"\
	L" font-family: Verdana, Arial, Helvetica, sans-serif; font-"\
	L"size: 9pt; font-weight: normal; }\r\n.TblHdr    {color: #C"\
	L"CCC99; background-color: #333333; font-family: Verdana, Ar"\
	L"ial, Helvetica, sans-serif; font-size: 10pt; font-weight: "\
	L"bold; text-align: center;}\r\n.IntfName  {color: #660000; "\
	L"font-family: Verdana, Arial, Helvetica, sans-serif; font-s"\
	L"ize: 10pt; font-weight: bold; }\r\n.MethName  {color: #333"\
	L"333; font-family: Verdana, Arial, Helvetica, sans-serif; f"\
	L"ont-size: 8pt; font-weight: bold; text-decoration: none; }"\
	L"\r\n.ParmName  {color: #333333; font-family: Verdana, Aria"\
	L"l, Helvetica, sans-serif; font-size: 8pt; text-decoration:"\
	L" none; }\r\n.Namespace {color: #333333; font-family: Verda"\
	L"na, Arial, Helvetica, sans-serif; font-size: 9pt; font-sty"\
	L"le: italic; }\r\n.WSDL      {color: #990000; font-family: "\
	L"Verdana, Arial, Helvetica, sans-serif; font-size: 8pt; fon"\
	L"t-weight: bold; }\r\n.MainBkgnd {background-color : #d9d4a"\
	L"a; }\r\n.Info      {font-family: Verdana, Arial, Helvetica"\
	L", sans-serif; font-size: 12pt; font-weight: bold; }\r\n.Na"\
	L"vBar    {color: #660000; background-color: #f5f5dc; font-f"\
	L"amily: Verdana, Arial, Helvetica, sans-serif; font-size: 8"\
	L"pt; font-weight: bold;text-decoration: none; }\r\n.Off    "\
	L"   {color: #A0A0A0; }\r\n.Tip \t    {color: #666666; font-"\
	L"family : Verdana, Arial, Helvetica, sans-serif; font-weigh"\
	L"t : normal; font-size : 9pt; }\r\n--></style>\r\n</head><b"\
	L"ody>"
#define HTMLTopNoMargin L"<html><head><style type=\"text/css\"><!--\r\nbody       {f"\
	L"ont-family: Verdana, Arial, Helvetica, sans-serif; font-si"\
	L"ze: 9pt; margin-left: 0px; margin-top: 0px; margin-right: "\
	L"0px; }\r\nh1         {color: #333333; font-size: 18pt; fon"\
	L"t-style: normal; font-weight: bold; }\r\nh2         {color"\
	L": #333333; font-size: 14pt; font-style: normal; font-weigh"\
	L"t: bold; }\r\nh3         {color: #333333; font-size: 12pt;"\
	L" font-style: normal; font-weight: bold; }\r\n.h1Style   {c"\
	L"olor: #333333; font-size: 18pt; font-style: normal; font-w"\
	L"eight: bold; }\r\n.TblRow    {color: #333333; font-family:"\
	L" Verdana, Arial, Helvetica, sans-serif; font-size: 10pt; f"\
	L"ont-weight: normal; }\r\n.TblRow1   {color: #333333; backg"\
	L"round-color: #f5f5dc; font-family: Verdana, Arial, Helveti"\
	L"ca, sans-serif; font-size: 9pt; font-weight: normal; }\r\n"\
	L".TblRow0   {color: #333333; background-color: #d9d4aa; fon"\
	L"t-family: Verdana, Arial, Helvetica, sans-serif; font-size"\
	L": 9pt; font-weight: normal; }\r\n.TblHdr    {color: #CCCC9"\
	L"9; background-color: #333333; font-family: Verdana, Arial,"\
	L" Helvetica, sans-serif; font-size: 10pt; font-weight: bold"\
	L"; text-align: center;}\r\n.IntfName  {color: #660000; font"\
	L"-family: Verdana, Arial, Helvetica, sans-serif; font-size:"\
	L" 10pt; font-weight: bold; }\r\n.MethName  {color: #333333;"\
	L" font-family: Verdana, Arial, Helvetica, sans-serif; font-"\
	L"size: 8pt; font-weight: bold; text-decoration: none; }\r\n"\
	L".ParmName  {color: #333333; font-family: Verdana, Arial, H"\
	L"elvetica, sans-serif; font-size: 8pt; text-decoration: non"\
	L"e; }\r\n.Namespace {color: #333333; font-family: Verdana, "\
	L"Arial, Helvetica, sans-serif; font-size: 9pt; font-style: "\
	L"italic; }\r\n.WSDL      {color: #990000; font-family: Verd"\
	L"ana, Arial, Helvetica, sans-serif; font-size: 8pt; font-we"\
	L"ight: bold; }\r\n.MainBkgnd {background-color : #d9d4aa; }"\
	L"\r\n.Info      {font-family: Verdana, Arial, Helvetica, sa"\
	L"ns-serif; font-size: 12pt; font-weight: bold; }\r\n.NavBar"\
	L"    {color: #660000; background-color: #f5f5dc; font-famil"\
	L"y: Verdana, Arial, Helvetica, sans-serif; font-size: 8pt; "\
	L"font-weight: bold;text-decoration: none; }\r\n.Off       {"\
	L"color: #A0A0A0; }\r\n.Tip \t    {color: #666666; font-fami"\
	L"ly : Verdana, Arial, Helvetica, sans-serif; font-weight : "\
	L"normal; font-size : 9pt; }\r\n--></style>\r\n</head><body>"
#define HTMLTopTitleNoMargin L"<html><head><title>%s</title><style type=\"text/css\"><!--"\
	L"\r\nbody       {font-family: Verdana, Arial, Helvetica, sa"\
	L"ns-serif; font-size: 9pt; margin-left: 0px; margin-top: 0p"\
	L"x; margin-right: 0px; }\r\nh1         {color: #333333; fon"\
	L"t-size: 18pt; font-style: normal; font-weight: bold; }\r\n"\
	L"h2         {color: #333333; font-size: 14pt; font-style: n"\
	L"ormal; font-weight: bold; }\r\nh3         {color: #333333;"\
	L" font-size: 12pt; font-style: normal; font-weight: bold; }"\
	L"\r\n.h1Style   {color: #333333; font-size: 18pt; font-styl"\
	L"e: normal; font-weight: bold; }\r\n.TblRow    {color: #333"\
	L"333; font-family: Verdana, Arial, Helvetica, sans-serif; f"\
	L"ont-size: 10pt; font-weight: normal; }\r\n.TblRow1   {colo"\
	L"r: #333333; background-color: #f5f5dc; font-family: Verdan"\
	L"a, Arial, Helvetica, sans-serif; font-size: 9pt; font-weig"\
	L"ht: normal; }\r\n.TblRow0   {color: #333333; background-co"\
	L"lor: #d9d4aa; font-family: Verdana, Arial, Helvetica, sans"\
	L"-serif; font-size: 9pt; font-weight: normal; }\r\n.TblHdr "\
	L"   {color: #CCCC99; background-color: #333333; font-family"\
	L": Verdana, Arial, Helvetica, sans-serif; font-size: 10pt; "\
	L"font-weight: bold; text-align: center;}\r\n.IntfName  {col"\
	L"or: #660000; font-family: Verdana, Arial, Helvetica, sans-"\
	L"serif; font-size: 10pt; font-weight: bold; }\r\n.MethName "\
	L" {color: #333333; font-family: Verdana, Arial, Helvetica, "\
	L"sans-serif; font-size: 8pt; font-weight: bold; text-decora"\
	L"tion: none; }\r\n.ParmName  {color: #333333; font-family: "\
	L"Verdana, Arial, Helvetica, sans-serif; font-size: 8pt; tex"\
	L"t-decoration: none; }\r\n.Namespace {color: #333333; font-"\
	L"family: Verdana, Arial, Helvetica, sans-serif; font-size: "\
	L"9pt; font-style: italic; }\r\n.WSDL      {color: #990000; "\
	L"font-family: Verdana, Arial, Helvetica, sans-serif; font-s"\
	L"ize: 8pt; font-weight: bold; }\r\n.MainBkgnd {background-c"\
	L"olor : #d9d4aa; }\r\n.Info      {font-family: Verdana, Ari"\
	L"al, Helvetica, sans-serif; font-size: 12pt; font-weight: b"\
	L"old; }\r\n.NavBar    {color: #660000; background-color: #f"\
	L"5f5dc; font-family: Verdana, Arial, Helvetica, sans-serif;"\
	L" font-size: 8pt; font-weight: bold;text-decoration: none; "\
	L"}\r\n.Off       {color: #A0A0A0; }\r\n.Tip \t    {color: #"\
	L"666666; font-family : Verdana, Arial, Helvetica, sans-seri"\
	L"f; font-weight : normal; font-size : 9pt; }\r\n--></style>"\
	L"\r\n</head><body>"
#define HTMLTopNoStyles L"<html><head></head><body>"
#define HTMLTopTitle L"<html><head><title>%s</title><style type=\"text/css\"><!--"\
	L"\r\nbody       {font-family: Verdana, Arial, Helvetica, sa"\
	L"ns-serif; font-size: 9pt; }\r\nh1         {color: #333333;"\
	L" font-size: 18pt; font-style: normal; font-weight: bold; }"\
	L"\r\nh2         {color: #333333; font-size: 14pt; font-styl"\
	L"e: normal; font-weight: bold; }\r\nh3         {color: #333"\
	L"333; font-size: 12pt; font-style: normal; font-weight: bol"\
	L"d; }\r\n.h1Style   {color: #333333; font-size: 18pt; font-"\
	L"style: normal; font-weight: bold; }\r\n.TblRow    {color: "\
	L"#333333; font-family: Verdana, Arial, Helvetica, sans-seri"\
	L"f; font-size: 10pt; font-weight: normal; }\r\n.TblRow1   {"\
	L"color: #333333; background-color: #f5f5dc; font-family: Ve"\
	L"rdana, Arial, Helvetica, sans-serif; font-size: 9pt; font-"\
	L"weight: normal; }\r\n.TblRow0   {color: #333333; backgroun"\
	L"d-color: #d9d4aa; font-family: Verdana, Arial, Helvetica, "\
	L"sans-serif; font-size: 9pt; font-weight: normal; }\r\n.Tbl"\
	L"Hdr    {color: #CCCC99; background-color: #333333; font-fa"\
	L"mily: Verdana, Arial, Helvetica, sans-serif; font-size: 10"\
	L"pt; font-weight: bold; text-align: center;}\r\n.IntfName  "\
	L"{color: #660000; font-family: Verdana, Arial, Helvetica, s"\
	L"ans-serif; font-size: 10pt; font-weight: bold; }\r\n.MethN"\
	L"ame  {color: #333333; font-family: Verdana, Arial, Helveti"\
	L"ca, sans-serif; font-size: 8pt; font-weight: bold; text-de"\
	L"coration: none; }\r\n.ParmName  {color: #333333; font-fami"\
	L"ly: Verdana, Arial, Helvetica, sans-serif; font-size: 8pt;"\
	L" text-decoration: none; }\r\n.Namespace {color: #333333; f"\
	L"ont-family: Verdana, Arial, Helvetica, sans-serif; font-si"\
	L"ze: 9pt; font-style: italic; }\r\n.WSDL      {color: #9900"\
	L"00; font-family: Verdana, Arial, Helvetica, sans-serif; fo"\
	L"nt-size: 8pt; font-weight: bold; }\r\n.MainBkgnd {backgrou"\
	L"nd-color : #d9d4aa; }\r\n.Info      {font-family: Verdana,"\
	L" Arial, Helvetica, sans-serif; font-size: 12pt; font-weigh"\
	L"t: bold; }\r\n.NavBar    {color: #660000; background-color"\
	L": #f5f5dc; font-family: Verdana, Arial, Helvetica, sans-se"\
	L"rif; font-size: 8pt; font-weight: bold;text-decoration: no"\
	L"ne; }\r\n.Off       {color: #A0A0A0; }\r\n.Tip \t    {colo"\
	L"r: #666666; font-family : Verdana, Arial, Helvetica, sans-"\
	L"serif; font-weight : normal; font-size : 9pt; }\r\n--></st"\
	L"yle>\r\n</head><body>"
#define HTMLTopTitleNoMarginWSIL L"<html><head><META name=\"serviceInspection\" content=\"ins"\
	L"pection.wsil\"><title>%s</title><style type=\"text/css\"><"\
	L"!--\r\nbody       {font-family: Verdana, Arial, Helvetica,"\
	L" sans-serif; font-size: 9pt; margin-left: 0px; margin-top:"\
	L" 0px; margin-right: 0px; }\r\nh1         {color: #333333; "\
	L"font-size: 18pt; font-style: normal; font-weight: bold; }\r"\
	L"\nh2         {color: #333333; font-size: 14pt; font-style:"\
	L" normal; font-weight: bold; }\r\nh3         {color: #33333"\
	L"3; font-size: 12pt; font-style: normal; font-weight: bold;"\
	L" }\r\n.h1Style   {color: #333333; font-size: 18pt; font-st"\
	L"yle: normal; font-weight: bold; }\r\n.TblRow    {color: #3"\
	L"33333; font-family: Verdana, Arial, Helvetica, sans-serif;"\
	L" font-size: 10pt; font-weight: normal; }\r\n.TblRow1   {co"\
	L"lor: #333333; background-color: #f5f5dc; font-family: Verd"\
	L"ana, Arial, Helvetica, sans-serif; font-size: 9pt; font-we"\
	L"ight: normal; }\r\n.TblRow0   {color: #333333; background-"\
	L"color: #d9d4aa; font-family: Verdana, Arial, Helvetica, sa"\
	L"ns-serif; font-size: 9pt; font-weight: normal; }\r\n.TblHd"\
	L"r    {color: #CCCC99; background-color: #333333; font-fami"\
	L"ly: Verdana, Arial, Helvetica, sans-serif; font-size: 10pt"\
	L"; font-weight: bold; text-align: center;}\r\n.IntfName  {c"\
	L"olor: #660000; font-family: Verdana, Arial, Helvetica, san"\
	L"s-serif; font-size: 10pt; font-weight: bold; }\r\n.MethNam"\
	L"e  {color: #333333; font-family: Verdana, Arial, Helvetica"\
	L", sans-serif; font-size: 8pt; font-weight: bold; text-deco"\
	L"ration: none; }\r\n.ParmName  {color: #333333; font-family"\
	L": Verdana, Arial, Helvetica, sans-serif; font-size: 8pt; t"\
	L"ext-decoration: none; }\r\n.Namespace {color: #333333; fon"\
	L"t-family: Verdana, Arial, Helvetica, sans-serif; font-size"\
	L": 9pt; font-style: italic; }\r\n.WSDL      {color: #990000"\
	L"; font-family: Verdana, Arial, Helvetica, sans-serif; font"\
	L"-size: 8pt; font-weight: bold; }\r\n.MainBkgnd {background"\
	L"-color : #d9d4aa; }\r\n.Info      {font-family: Verdana, A"\
	L"rial, Helvetica, sans-serif; font-size: 12pt; font-weight:"\
	L" bold; }\r\n.NavBar    {color: #660000; background-color: "\
	L"#f5f5dc; font-family: Verdana, Arial, Helvetica, sans-seri"\
	L"f; font-size: 8pt; font-weight: bold;text-decoration: none"\
	L"; }\r\n.Off       {color: #A0A0A0; }\r\n.Tip \t    {color:"\
	L" #666666; font-family : Verdana, Arial, Helvetica, sans-se"\
	L"rif; font-weight : normal; font-size : 9pt; }\r\n--></styl"\
	L"e>\r\n</head><body>"
#define HTMLEnd L"</body></html>"
#define InfoTitle1 L"<table class=\"MainBkgnd\" border=0 cellpadding=0 cellspac"\
	L"ing=0 width=\"100%\"><tr><td>&nbsp;</td></tr>"
#define InfoTitle2 L"<tr><td class=\"h1Style\" align=\"center\">%s - %s</td></t"\
	L"r></table>"
extern DELPHI_PACKAGE Soap_Soapconst__7 TblCls;
#define sTblRow L"TblRow"
#define sTblHdrCls L"TblHdr"
#define sQueryStringIntf L"intf"
#define sQueryStringTypes L"types"
#define sNBSP L"&nbsp;"
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
