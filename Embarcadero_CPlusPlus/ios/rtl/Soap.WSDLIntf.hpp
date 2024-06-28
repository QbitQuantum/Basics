// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.WSDLIntf.pas' rev: 34.00 (iOS)

#ifndef Soap_WsdlintfHPP
#define Soap_WsdlintfHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Classes.hpp>
#include <Xml.xmldom.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Wsdlintf
{
//-- forward type declarations -----------------------------------------------
struct TWString;
class DELPHICLASS TDOMStrings;
__interface DELPHIINTERFACE IStringTokenizer;
typedef System::DelphiInterface<IStringTokenizer> _di_IStringTokenizer;
__interface DELPHIINTERFACE IStreamLoader;
typedef System::DelphiInterface<IStreamLoader> _di_IStreamLoader;
__interface DELPHIINTERFACE IStreamLoaderCustomizer;
typedef System::DelphiInterface<IStreamLoaderCustomizer> _di_IStreamLoaderCustomizer;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TSOAPVersion : unsigned char { svUnspecified, svSOAP11, svSOAP12 };

enum DECLSPEC_DENUM TWebServiceBindingType : unsigned char { btUnknown, btSoap, btHttp, btMime, btDIME };

enum DECLSPEC_DENUM TWSDLElement : unsigned char { weServiceIntf, weServiceImpl, weMessage, wePortType, weBinding, weService, weTypes, WeImport, weOperation, wePart };

typedef System::Set<TWSDLElement, TWSDLElement::weServiceIntf, TWSDLElement::wePart> TWSDLElements;

struct DECLSPEC_DRECORD TWString
{
public:
	System::UnicodeString WString;
};


class PASCALIMPLEMENTATION TDOMStrings : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::UnicodeString operator[](int Index) { return this->Strings[Index]; }
	
private:
	System::Generics::Collections::TList__1<System::UnicodeString>* FDOMStringList;
	System::UnicodeString __fastcall Get(int Index);
	void __fastcall Put(int Index, const System::UnicodeString S);
	
public:
	__fastcall TDOMStrings();
	__fastcall virtual ~TDOMStrings();
	int __fastcall Count();
	void __fastcall Clear();
	int __fastcall Add(const System::UnicodeString S);
	int __fastcall IndexOf(const System::UnicodeString S);
	int __fastcall IndexOfIgnoreCase(const System::UnicodeString S);
	void __fastcall Insert(int Index, const System::UnicodeString S);
	__property System::UnicodeString Strings[int Index] = {read=Get, write=Put/*, default*/};
};


__interface  INTERFACE_UUID("{8C216E9D-984E-4E38-893F-0A222AC547DA}") IStringTokenizer  : public System::IInterface 
{
	virtual int __fastcall getTokenCounts() = 0 ;
	virtual bool __fastcall hasMoreTokens() = 0 ;
	virtual System::UnicodeString __fastcall nextToken() = 0 ;
	__property int countTokens = {read=getTokenCounts};
};

__interface  INTERFACE_UUID("{395CDFB2-1D10-4A37-AC16-393D569676F0}") IStreamLoader  : public System::IInterface 
{
	virtual void __fastcall Load(const System::UnicodeString WSDLFileName, System::Classes::TMemoryStream* Stream) = 0 ;
	virtual System::UnicodeString __fastcall GetProxy() = 0 ;
	virtual void __fastcall SetProxy(const System::UnicodeString Proxy) = 0 ;
	virtual System::UnicodeString __fastcall GetUserName() = 0 ;
	virtual void __fastcall SetUserName(const System::UnicodeString UserName) = 0 ;
	virtual System::UnicodeString __fastcall GetPassword() = 0 ;
	virtual void __fastcall SetPassword(const System::UnicodeString Password) = 0 ;
	virtual int __fastcall GetTimeout() = 0 ;
	virtual void __fastcall SetTimeout(int ATimeOut) = 0 ;
	virtual System::_di_IInterface __fastcall GetTransport() = 0 ;
	__property System::_di_IInterface Transport = {read=GetTransport};
	__property System::UnicodeString Proxy = {read=GetProxy, write=SetProxy};
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property int Timeout = {read=GetTimeout, write=SetTimeout};
};

__interface  INTERFACE_UUID("{582D78AC-1FE4-49C2-9275-7DA54BD20C99}") IStreamLoaderCustomizer  : public System::IInterface 
{
	virtual void __fastcall Customize(const System::_di_IInterface ATransport) = 0 ;
};

typedef System::StaticArray<System::UnicodeString, 3> Soap_Wsdlintf__2;

typedef System::StaticArray<System::UnicodeString, 67> Soap_Wsdlintf__3;

typedef System::StaticArray<System::UnicodeString, 44> Soap_Wsdlintf__4;

typedef System::StaticArray<System::UnicodeString, 1> Soap_Wsdlintf__5;

typedef System::StaticArray<System::UnicodeString, 13> Soap_Wsdlintf__6;

typedef System::StaticArray<System::UnicodeString, 13> Soap_Wsdlintf__7;

typedef System::StaticArray<System::UnicodeString, 13> Soap_Wsdlintf__8;

//-- var, const, procedure ---------------------------------------------------
#define SDefinitions u"definitions"
#define SMessage u"message"
#define SPart u"part"
#define SType u"type"
#define STypes u"types"
#define SImport u"import"
#define SPort u"port"
#define SPortType u"portType"
#define SOperation u"operation"
#define SBinding u"binding"
#define SService u"service"
#define SSchema u"schema"
#define SName u"name"
#define STns u"targetNamespace"
#define SInput u"input"
#define SOutput u"output"
#define SInOut u"inout"
#define SRequest u"Request"
#define SResponse u"Response"
#define SReturn u"return"
#define SElement u"element"
#define SComplexType u"complexType"
#define xsdns u"http://www.w3.org/1999/XMLSchema"
#define tns u"http://tempuri.org/"
#define Wsdlns u"http://schemas.xmlsoap.org/wsdl/"
#define Soapns u"http://schemas.xmlsoap.org/wsdl/soap/"
#define Soap12ns u"http://schemas.xmlsoap.org/wsdl/soap12/"
#define Httpns u"http://schemas.xmlsoap.org/wsdl/http/"
extern DELPHI_PACKAGE Soap_Wsdlintf__2 SOAPWSDLNamespaces;
#define SAddress u"address"
#define SBody u"body"
#define SHeader u"header"
#define SFault u"fault"
#define SVerb u"verb"
#define SStyle u"style"
#define STransport u"transport"
#define SLocation u"location"
#define SSoapAction u"soapAction"
#define SParts u"parts"
#define SUse u"use"
#define SNameSpace u"namespace"
#define SEncodingStyle u"encodingStyle"
#define SArrayOf u"ArrayOf"
#define SArray u"Array"
#define SArrayType u"arrayType"
#define SUnknown u"Unknown"
#define SDynArray u"array of "
#define SAnySimpleType u"anySimpleType"
#define SAnyType u"anyType"
#define SNsPrefix u"ns"
extern DELPHI_PACKAGE Soap_Wsdlintf__3 ReservedWords;
extern DELPHI_PACKAGE Soap_Wsdlintf__4 Directives;
extern DELPHI_PACKAGE Soap_Wsdlintf__5 OtherReservedWords;
extern DELPHI_PACKAGE Soap_Wsdlintf__6 Operators;
extern DELPHI_PACKAGE Soap_Wsdlintf__7 ScalarArrayTypes;
extern DELPHI_PACKAGE Soap_Wsdlintf__8 DynArrayTypes;
}	/* namespace Wsdlintf */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_WSDLINTF)
using namespace Soap::Wsdlintf;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_WsdlintfHPP
