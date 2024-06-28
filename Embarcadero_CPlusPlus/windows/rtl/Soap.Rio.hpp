// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.Rio.pas' rev: 34.00 (Windows)

#ifndef Soap_RioHPP
#define Soap_RioHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include <Soap.IntfInfo.hpp>
#include <Soap.OPConvert.hpp>
#include <System.IOUtils.hpp>
#include <Soap.InvokeRegistry.hpp>
#include <Soap.WebNode.hpp>
#include <Soap.SOAPAttachIntf.hpp>
#include <Soap.WSDLIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Rio
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IRIOAccess;
typedef System::DelphiInterface<IRIOAccess> _di_IRIOAccess;
class DELPHICLASS TRIO;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{FEF7C9CC-A477-40B7-ACBE-487EDA3E5DFE}") IRIOAccess  : public System::IInterface 
{
	virtual TRIO* __fastcall GetRIO() = 0 ;
	__property TRIO* RIO = {read=GetRIO};
};

typedef void __fastcall (__closure *TBeforeExecuteEvent)(const System::UnicodeString MethodName, System::Classes::TStream* SOAPRequest);

typedef void __fastcall (__closure *TAfterExecuteEvent)(const System::UnicodeString MethodName, System::Classes::TStream* SOAPResponse);

class PASCALIMPLEMENTATION TRIO : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
private:
	class DELPHICLASS TRioVirtualInterface;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TRioVirtualInterface : public System::Rtti::TVirtualInterface
	{
		typedef System::Rtti::TVirtualInterface inherited;
		
	private:
		TRIO* FRio;
		
	protected:
		virtual int __stdcall _AddRef();
		virtual int __stdcall _Release();
		
	public:
		__fastcall TRioVirtualInterface(TRIO* ARio, void * AInterface);
		virtual HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	public:
		/* TVirtualInterface.Destroy */ inline __fastcall virtual ~TRioVirtualInterface() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	System::_di_IInterface FInterface;
	int FRefCount;
	Soap::Invokeregistry::TSOAPHeaders* FSOAPHeaders;
	Soap::Invokeregistry::THeaderList* FHeadersOutBound;
	Soap::Invokeregistry::THeaderList* FHeadersInbound;
	TAfterExecuteEvent FOnAfterExecute;
	TBeforeExecuteEvent FOnBeforeExecute;
	Soap::Soapattachintf::TOnSendAttachmentEvent FOnSendAttachment;
	Soap::Soapattachintf::TOnGetAttachmentEvent FOnGetAttachment;
#ifndef _WIN64
	void __fastcall Generic(System::Rtti::TRttiMethod* Method, const System::DynamicArray<System::Rtti::TValue> Args, /* out */ System::Rtti::TValue &Result);
#else /* _WIN64 */
	void __fastcall Generic(System::Rtti::TRttiMethod* Method, const System::TArray__1<System::Rtti::TValue> Args, /* out */ System::Rtti::TValue &Result);
#endif /* _WIN64 */
	HIDESBASE int __stdcall _AddRef();
	HIDESBASE int __stdcall _Release();
	TRIO* __fastcall GetRIO();
	
protected:
	GUID FIID;
	Soap::Intfinfo::TIntfMetaData IntfMD;
	Soap::Opconvert::_di_IOPConvert FConverter;
	Soap::Webnode::_di_IWebNode FWebNode;
	void __fastcall DoDispatch(Soap::Invokeregistry::TInvContext* const Context, int MethNum, const Soap::Intfinfo::TIntfMethEntry &MethMD);
	HRESULT __stdcall InternalQI(const GUID &IID, /* out */ void *Obj);
	virtual void __fastcall DoAfterExecute(const System::UnicodeString MethodName, System::Classes::TStream* Response);
	virtual void __fastcall DoBeforeExecute(const System::UnicodeString MethodName, System::Classes::TStream* Request);
	virtual System::Classes::TStream* __fastcall GetResponseStream(Soap::Wsdlintf::TWebServiceBindingType BindingType);
	
public:
	__fastcall virtual TRIO(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TRIO();
	virtual HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	virtual void __fastcall AfterConstruction();
	virtual void __fastcall BeforeDestruction();
	__classmethod virtual System::TObject* __fastcall NewInstance();
	__property int RefCount = {read=FRefCount, nodefault};
	__property Soap::Opconvert::_di_IOPConvert Converter = {read=FConverter, write=FConverter};
	__property Soap::Webnode::_di_IWebNode WebNode = {read=FWebNode, write=FWebNode};
	__property Soap::Invokeregistry::TSOAPHeaders* SOAPHeaders = {read=FSOAPHeaders};
	
__published:
	__property TAfterExecuteEvent OnAfterExecute = {read=FOnAfterExecute, write=FOnAfterExecute};
	__property TBeforeExecuteEvent OnBeforeExecute = {read=FOnBeforeExecute, write=FOnBeforeExecute};
	__property Soap::Soapattachintf::TOnSendAttachmentEvent OnSendAttachment = {read=FOnSendAttachment, write=FOnSendAttachment};
	__property Soap::Soapattachintf::TOnGetAttachmentEvent OnGetAttachment = {read=FOnGetAttachment, write=FOnGetAttachment};
private:
	void *__IRIOAccess;	// IRIOAccess 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FEF7C9CC-A477-40B7-ACBE-487EDA3E5DFE}
	operator _di_IRIOAccess()
	{
		_di_IRIOAccess intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IRIOAccess*(void) { return (IRIOAccess*)&__IRIOAccess; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IRIOAccess; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Rio */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_RIO)
using namespace Soap::Rio;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_RioHPP
