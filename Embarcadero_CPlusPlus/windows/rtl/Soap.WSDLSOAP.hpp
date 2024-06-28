// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.WSDLSOAP.pas' rev: 34.00 (Windows)

#ifndef Soap_WsdlsoapHPP
#define Soap_WsdlsoapHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Wsdlsoap
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWSDLSOAPPort;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWSDLSOAPPort : public Soap::Invokeregistry::TRemotable
{
	typedef Soap::Invokeregistry::TRemotable inherited;
	
private:
	System::WideString FPortName;
#ifndef _WIN64
	System::DynamicArray<System::WideString> FAddresses;
#else /* _WIN64 */
	System::TArray__1<System::WideString> FAddresses;
#endif /* _WIN64 */
	
__published:
	__property System::WideString PortName = {read=FPortName, write=FPortName};
#ifndef _WIN64
	__property System::DynamicArray<System::WideString> Addresses = {read=FAddresses, write=FAddresses};
#else /* _WIN64 */
	__property System::TArray__1<System::WideString> Addresses = {read=FAddresses, write=FAddresses};
#endif /* _WIN64 */
public:
	/* TRemotable.Create */ inline __fastcall virtual TWSDLSOAPPort() : Soap::Invokeregistry::TRemotable() { }
	/* TRemotable.Destroy */ inline __fastcall virtual ~TWSDLSOAPPort() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<TWSDLSOAPPort*> TWSDLSOAPPortArray;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Wsdlsoap */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_WSDLSOAP)
using namespace Soap::Wsdlsoap;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_WsdlsoapHPP
