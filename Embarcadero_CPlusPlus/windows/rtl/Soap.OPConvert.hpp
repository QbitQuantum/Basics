// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.OPConvert.pas' rev: 34.00 (Windows)

#ifndef Soap_OpconvertHPP
#define Soap_OpconvertHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Soap.IntfInfo.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Soap.OpConvertOptions.hpp>
#include <Soap.SOAPAttachIntf.hpp>
#include <Xml.xmldom.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Opconvert
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IOPConvert;
typedef System::DelphiInterface<IOPConvert> _di_IOPConvert;
//-- type declarations -------------------------------------------------------
using Soap::Opconvertoptions::TSOAPConvertOption;

using Soap::Opconvertoptions::TSOAPConvertOptions;

__interface  INTERFACE_UUID("{1F955FE3-890B-474C-A3A4-5E072D30CC4F}") IOPConvert  : public System::IInterface 
{
	virtual Soap::Opconvertoptions::TSOAPConvertOptions __fastcall GetOptions() = 0 ;
	virtual void __fastcall SetOptions(const Soap::Opconvertoptions::TSOAPConvertOptions Value) = 0 ;
	virtual Soap::Soapattachintf::TSoapDataList* __fastcall GetAttachments() = 0 ;
	virtual void __fastcall SetAttachments(Soap::Soapattachintf::TSoapDataList* Value) = 0 ;
	virtual System::UnicodeString __fastcall GetTempDir() = 0 ;
	virtual void __fastcall SetTempDir(const System::UnicodeString Value) = 0 ;
	virtual System::UnicodeString __fastcall GetEncoding() = 0 ;
	virtual void __fastcall SetEncoding(const System::UnicodeString Encoding) = 0 ;
	virtual System::Classes::TStream* __fastcall InvContextToMsg(const Soap::Intfinfo::TIntfMetaData &IntfMD, int MethNum, Soap::Invokeregistry::TInvContext* Con, Soap::Invokeregistry::THeaderList* Headers) = 0 ;
	virtual void __fastcall ProcessResponse(System::Classes::TStream* const Resp, const Soap::Intfinfo::TIntfMetaData &IntfMD, const Soap::Intfinfo::TIntfMethEntry &MD, Soap::Invokeregistry::TInvContext* Context, Soap::Invokeregistry::THeaderList* Headers) = 0 /* overload */;
	virtual void __fastcall ProcessResponse _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString Resp, const Soap::Intfinfo::TIntfMetaData &IntfMD, const Soap::Intfinfo::TIntfMethEntry &MD, Soap::Invokeregistry::TInvContext* Context) = 0 /* overload */;
	virtual void __fastcall MsgToInvContext(const System::UnicodeString Request, const Soap::Intfinfo::TIntfMetaData &IntfMD, int &MethNum, Soap::Invokeregistry::TInvContext* Context) = 0 /* overload */;
	virtual void __fastcall MsgToInvContext(System::Classes::TStream* const Request, const Soap::Intfinfo::TIntfMetaData &IntfMD, int &MethNum, Soap::Invokeregistry::TInvContext* Context, Soap::Invokeregistry::THeaderList* Headers) = 0 /* overload */;
	virtual void __fastcall MakeResponse(const Soap::Intfinfo::TIntfMetaData &IntfMD, const int MethNum, Soap::Invokeregistry::TInvContext* Context, System::Classes::TStream* Response, Soap::Invokeregistry::THeaderList* Headers) = 0 ;
	virtual void __fastcall MakeFault(System::Sysutils::Exception* const Ex, System::Classes::TStream* EStream) = 0 ;
	__property Soap::Soapattachintf::TSoapDataList* Attachments = {read=GetAttachments, write=SetAttachments};
	__property Soap::Opconvertoptions::TSOAPConvertOptions Options = {read=GetOptions, write=SetOptions};
	__property System::UnicodeString TempDir = {read=GetTempDir, write=SetTempDir};
	__property System::UnicodeString Encoding = {read=GetEncoding, write=SetEncoding};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Opconvert */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_OPCONVERT)
using namespace Soap::Opconvert;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_OpconvertHPP
