// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPAttach.pas' rev: 34.00 (Android)

#ifndef Soap_SoapattachHPP
#define Soap_SoapattachHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Web.HTTPApp.hpp>
#include <Soap.SOAPAttachIntf.hpp>
#include <Soap.WSDLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soapattach
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSOAPAttachmentData;
class DELPHICLASS TWebRequestStream;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSOAPAttachmentData : public Soap::Invokeregistry::TSOAPAttachment
{
	typedef Soap::Invokeregistry::TSOAPAttachment inherited;
	
private:
	System::UnicodeString FID;
	
public:
	__property System::UnicodeString ID = {read=FID, write=FID};
	virtual void __fastcall SetSourceStream(System::Classes::TStream* const Value, const System::Classes::TStreamOwnership Ownership = (System::Classes::TStreamOwnership)(0x1));
	void __fastcall SetCacheFile(const System::UnicodeString Value);
public:
	/* TSOAPAttachment.Create */ inline __fastcall virtual TSOAPAttachmentData() : Soap::Invokeregistry::TSOAPAttachment() { }
	/* TSOAPAttachment.Destroy */ inline __fastcall virtual ~TSOAPAttachmentData() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TWebRequestStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	Web::Httpapp::TWebRequest* FWebRequest;
	__int64 FPosition;
	__int64 FSize;
	int FContentSize;
	System::TArray__1<System::Byte> FSavedChars;
	System::UnicodeString FContentType;
	int FMaxLine;
	
public:
	__fastcall TWebRequestStream(Web::Httpapp::TWebRequest* ARequest);
	__fastcall virtual ~TWebRequestStream();
#ifndef __aarch64__
	virtual int __fastcall Read(void *Buffer, int Count)/* overload */;
	virtual int __fastcall Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count)/* overload */;
#else /* __aarch64__ */
	virtual long __fastcall Read(void *Buffer, long Count)/* overload */;
	virtual long __fastcall Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
#endif /* __aarch64__ */
	System::UnicodeString __fastcall ReadLn();
#ifndef __aarch64__
	virtual int __fastcall Seek(int Offset, System::Word Origin)/* overload */;
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count)/* overload */;
#else /* __aarch64__ */
	virtual long __fastcall Seek(long Offset, System::Word Origin)/* overload */;
	virtual long __fastcall Write(const void *Buffer, long Count)/* overload */;
	virtual long __fastcall Write(const System::TArray__1<System::Byte> Buffer, long Offset, long Count)/* overload */;
#endif /* __aarch64__ */
	__property int MaxLine = {read=FMaxLine, write=FMaxLine, nodefault};
	/* Hoisted overloads: */
	
public:
#ifndef __aarch64__
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
#else /* __aarch64__ */
	inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
#endif /* __aarch64__ */
	inline __int64 __fastcall  Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
#ifndef __aarch64__
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#else /* __aarch64__ */
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Count){ return System::Classes::TStream::Write(Buffer, Count); }
#endif /* __aarch64__ */
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::TArray__1<System::Byte> EOLBytes;
#define EOL u"\r\n"
static constexpr System::Word BlockReadSize = System::Word(0x2800);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetTempDir(void);
extern DELPHI_PACKAGE NativeUInt __fastcall GetTempHandle(System::UnicodeString &ATempFileName);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetBorlandMimeContentType(void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetMimeBoundaryFromType(const System::UnicodeString ContentType);
extern DELPHI_PACKAGE Soap::Soapattachintf::_di_IMimeAttachmentHandler __fastcall GetMimeAttachmentHandler(const System::UnicodeString ContentType)/* overload */;
extern DELPHI_PACKAGE Soap::Soapattachintf::_di_IMimeAttachmentHandler __fastcall GetMimeAttachmentHandler(const Soap::Wsdlintf::TWebServiceBindingType BindingType)/* overload */;
}	/* namespace Soapattach */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPATTACH)
using namespace Soap::Soapattach;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoapattachHPP
