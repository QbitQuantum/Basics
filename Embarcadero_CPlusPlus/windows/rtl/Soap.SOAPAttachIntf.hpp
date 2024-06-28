// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPAttachIntf.pas' rev: 34.00 (Windows)

#ifndef Soap_SoapattachintfHPP
#define Soap_SoapattachintfHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soapattachintf
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSoapDataList;
__interface DELPHIINTERFACE IMimeAttachmentHandler;
typedef System::DelphiInterface<IMimeAttachmentHandler> _di_IMimeAttachmentHandler;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSoapDataList : public System::Generics::Collections::TList__1<Soap::Invokeregistry::TSOAPAttachment*>
{
	typedef System::Generics::Collections::TList__1<Soap::Invokeregistry::TSOAPAttachment*> inherited;
	
public:
	HIDESBASE int __fastcall Add(Soap::Invokeregistry::TSOAPAttachment* Item);
	void __fastcall Assign(System::Generics::Collections::TList__1<Soap::Invokeregistry::TSOAPAttachment*>* ListA, System::Classes::TListAssignOp AOperator = (System::Classes::TListAssignOp)(0x0), System::Generics::Collections::TList__1<Soap::Invokeregistry::TSOAPAttachment*>* ListB = (System::Generics::Collections::TList__1<Soap::Invokeregistry::TSOAPAttachment*>*)(0x0));
	HIDESBASE void __fastcall Insert(int Index, System::TClass aClass);
	HIDESBASE int __fastcall Remove(System::TClass aClass);
public:
	/* {System_Generics_Collections}TList<Soap_InvokeRegistry_TSOAPAttachment>.Create */ inline __fastcall TSoapDataList()/* overload */ : System::Generics::Collections::TList__1<Soap::Invokeregistry::TSOAPAttachment*>() { }
	/* {System_Generics_Collections}TList<Soap_InvokeRegistry_TSOAPAttachment>.Create */ inline __fastcall TSoapDataList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<Soap::Invokeregistry::TSOAPAttachment*> > AComparer)/* overload */ : System::Generics::Collections::TList__1<Soap::Invokeregistry::TSOAPAttachment*>(AComparer) { }
	/* {System_Generics_Collections}TList<Soap_InvokeRegistry_TSOAPAttachment>.Create */ inline __fastcall TSoapDataList(System::Generics::Collections::TEnumerable__1<Soap::Invokeregistry::TSOAPAttachment*>* const Collection)/* overload */ : System::Generics::Collections::TList__1<Soap::Invokeregistry::TSOAPAttachment*>(Collection) { }
	/* {System_Generics_Collections}TList<Soap_InvokeRegistry_TSOAPAttachment>.Destroy */ inline __fastcall virtual ~TSoapDataList() { }
	
};


typedef void __fastcall (__closure *TOnSendAttachmentEvent)(System::Classes::TStream* AttachmentStream, Soap::Invokeregistry::TSOAPAttachment* Attachment);

typedef void __fastcall (__closure *TOnGetAttachmentEvent)(System::Classes::TStream* AttachmentStream, Soap::Invokeregistry::TSOAPAttachment* Attachment);

__interface  INTERFACE_UUID("{6B742425-FE6A-4EC2-ACF9-4751AF4E0EF8}") IMimeAttachmentHandler  : public System::IInterface 
{
	virtual void __fastcall ProcessMultiPartForm(System::Classes::TStream* const ASourceStream, System::Classes::TStream* const ADestStream, const System::UnicodeString AMimeBoundary, System::Classes::TStrings* SoapHeaders, TSoapDataList* Attachments, const System::UnicodeString TempDir) = 0 ;
	virtual void __fastcall AddSoapHeader(System::UnicodeString Value) = 0 ;
	virtual void __fastcall CreateMimeStream(System::Classes::TStream* Envelope, TSoapDataList* Attachments) = 0 ;
	virtual void __fastcall FinalizeStream() = 0 ;
	virtual System::Classes::TStream* __fastcall GetMIMEStream(bool Release = false) = 0 ;
	virtual System::UnicodeString __fastcall GetMIMEBoundary() = 0 ;
	virtual void __fastcall SetMIMEBoundary(const System::UnicodeString MimeBndry) = 0 ;
	virtual TOnSendAttachmentEvent __fastcall GetOnSendAttachmentEvent() = 0 ;
	virtual void __fastcall SetOnSendAttachmentEvent(TOnSendAttachmentEvent OnSendAttachment) = 0 ;
	virtual TOnGetAttachmentEvent __fastcall GetOnGetAttachmentEvent() = 0 ;
	virtual void __fastcall SetOnGetAttachmentEvent(TOnGetAttachmentEvent OnGetAttachment) = 0 ;
	__property System::UnicodeString MIMEBoundary = {read=GetMIMEBoundary, write=SetMIMEBoundary};
	__property TOnSendAttachmentEvent OnSendAttachment = {read=GetOnSendAttachmentEvent, write=SetOnSendAttachmentEvent};
	__property TOnGetAttachmentEvent OnGetAttachment = {read=GetOnGetAttachmentEvent, write=SetOnGetAttachmentEvent};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Soapattachintf */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPATTACHINTF)
using namespace Soap::Soapattachintf;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoapattachintfHPP
