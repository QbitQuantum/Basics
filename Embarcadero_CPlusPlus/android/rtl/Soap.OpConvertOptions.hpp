// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.OpConvertOptions.pas' rev: 34.00 (Android)

#ifndef Soap_OpconvertoptionsHPP
#define Soap_OpconvertoptionsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Opconvertoptions
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TSOAPConvertOption : unsigned char { soSendUntyped, soSendMultiRefObj, soSendMultiRefArray, soTryAllSchema, soRootRefNodesToBody, soDocument, soReturnSuccessForFault, soUTF8InHeader, soDontSendEmptyNodes, soCacheMimeResponse, soDontClearOutBoundHeaders, soCustomFaultAtDetailsNode, soLiteralParams, soUTF8EncodeXML, soXXXXHdr, soFormElementUnqualifed, soSOAP12, soDontSendVarArrayType };

typedef System::Set<TSOAPConvertOption, TSOAPConvertOption::soSendUntyped, TSOAPConvertOption::soDontSendVarArrayType> TSOAPConvertOptions;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Opconvertoptions */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_OPCONVERTOPTIONS)
using namespace Soap::Opconvertoptions;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_OpconvertoptionsHPP
