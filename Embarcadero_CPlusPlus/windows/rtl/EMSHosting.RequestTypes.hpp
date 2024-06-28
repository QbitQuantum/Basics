// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.RequestTypes.pas' rev: 34.00 (Windows)

#ifndef Emshosting_RequesttypesHPP
#define Emshosting_RequesttypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>

//-- user supplied -----------------------------------------------------------

namespace Emshosting
{
namespace Requesttypes
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IEMSHostRequest;
typedef System::DelphiInterface<IEMSHostRequest> _di_IEMSHostRequest;
__interface DELPHIINTERFACE IEMSHostRequestLocation;
typedef System::DelphiInterface<IEMSHostRequestLocation> _di_IEMSHostRequestLocation;
class DELPHICLASS TEMSHostRequest;
__interface DELPHIINTERFACE IEMSHostResponse;
typedef System::DelphiInterface<IEMSHostResponse> _di_IEMSHostResponse;
__interface DELPHIINTERFACE IEMSHostResponseLocation;
typedef System::DelphiInterface<IEMSHostResponseLocation> _di_IEMSHostResponseLocation;
__interface DELPHIINTERFACE IEMSHostResponseHeaders;
typedef System::DelphiInterface<IEMSHostResponseHeaders> _di_IEMSHostResponseHeaders;
class DELPHICLASS TEMSHostResponse;
__interface DELPHIINTERFACE IEMSHostContext;
typedef System::DelphiInterface<IEMSHostContext> _di_IEMSHostContext;
__interface DELPHIINTERFACE IEMSEdgeHostContext;
typedef System::DelphiInterface<IEMSEdgeHostContext> _di_IEMSEdgeHostContext;
class DELPHICLASS TEMSEdgeHostContext;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TEMSHostMethodType : unsigned char { Get, Put, Post, Head, Delete, Patch };

typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> TStringKeyValue;

#ifndef _WIN64
typedef System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TStringKeyValues;
#else /* _WIN64 */
typedef System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TStringKeyValues;
#endif /* _WIN64 */

__interface IEMSHostRequest  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetContentType() = 0 ;
	virtual TEMSHostMethodType __fastcall GetMethodType() = 0 ;
	virtual System::UnicodeString __fastcall GetPathInfo() = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetQueryFields() = 0 ;
	virtual System::DynamicArray<System::Byte> __fastcall GetRawContent() = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetQueryFields() = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall GetRawContent() = 0 ;
#endif /* _WIN64 */
	virtual System::UnicodeString __fastcall GetMethod() = 0 ;
	virtual int __fastcall GetContentLength() = 0 ;
	virtual System::UnicodeString __fastcall GetHeader(const System::UnicodeString AName) = 0 ;
	virtual System::UnicodeString __fastcall GetBasePath() = 0 ;
	virtual System::UnicodeString __fastcall GetServerHost() = 0 ;
	__property int ContentLength = {read=GetContentLength};
	__property System::UnicodeString ContentType = {read=GetContentType};
	__property TEMSHostMethodType MethodType = {read=GetMethodType};
	__property System::UnicodeString PathInfo = {read=GetPathInfo};
#ifndef _WIN64
	__property System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > QueryFields = {read=GetQueryFields};
	__property System::DynamicArray<System::Byte> RawContent = {read=GetRawContent};
#else /* _WIN64 */
	__property System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > QueryFields = {read=GetQueryFields};
	__property System::TArray__1<System::Byte> RawContent = {read=GetRawContent};
#endif /* _WIN64 */
	__property System::UnicodeString Method = {read=GetMethod};
	__property System::UnicodeString Headers[const System::UnicodeString I] = {read=GetHeader};
};

__interface  INTERFACE_UUID("{819E8684-3455-4B8A-AE31-AE708132362E}") IEMSHostRequestLocation  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall MakeAbsoluteLocation(const System::UnicodeString ALocation) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSHostRequest : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
public:
	typedef TEMSHostMethodType TMethodType;
	
	
protected:
	virtual System::UnicodeString __fastcall GetContentType() = 0 ;
	virtual TEMSHostMethodType __fastcall GetMethodType() = 0 ;
	virtual System::UnicodeString __fastcall GetPathInfo() = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetQueryFields() = 0 ;
	virtual System::DynamicArray<System::Byte> __fastcall GetRawContent() = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetQueryFields() = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall GetRawContent() = 0 ;
#endif /* _WIN64 */
	virtual System::UnicodeString __fastcall GetMethod();
	virtual int __fastcall GetContentLength() = 0 ;
	virtual System::UnicodeString __fastcall GetHeader(const System::UnicodeString AName) = 0 ;
	virtual System::UnicodeString __fastcall GetBasePath() = 0 ;
	virtual System::UnicodeString __fastcall GetServerHost() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TEMSHostRequest() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSHostRequest() { }
	
private:
	void *__IEMSHostRequest;	// IEMSHostRequest 
	
public:
	operator IEMSHostRequest*(void) { return (IEMSHostRequest*)&__IEMSHostRequest; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface IEMSHostResponse  : public System::IInterface 
{
	virtual System::Classes::TStream* __fastcall GetContentStream() = 0 ;
	virtual System::UnicodeString __fastcall GetContentType() = 0 ;
	virtual int __fastcall GetStatusCode() = 0 ;
	virtual System::UnicodeString __fastcall GetReasonString() = 0 ;
	virtual void __fastcall SetContentStream(System::Classes::TStream* const Value) = 0 ;
	virtual void __fastcall SetStatusCode(const int Value) = 0 ;
	virtual _di_IEMSHostRequest __fastcall GetRequest() = 0 ;
	virtual void __fastcall SetContentType(const System::UnicodeString Value) = 0 ;
	__property System::UnicodeString ContentType = {read=GetContentType, write=SetContentType};
	__property int StatusCode = {read=GetStatusCode, write=SetStatusCode};
	__property System::Classes::TStream* ContentStream = {read=GetContentStream, write=SetContentStream};
	__property _di_IEMSHostRequest Request = {read=GetRequest};
	__property System::UnicodeString ReasonString = {read=GetReasonString};
};

__interface  INTERFACE_UUID("{4DDEEE38-32B8-44A0-9F0E-FF16E2C4A4CA}") IEMSHostResponseLocation  : public System::IInterface 
{
	virtual void __fastcall SetLocation(const System::UnicodeString Value) = 0 ;
	__property System::UnicodeString Location = {write=SetLocation};
};

__interface  INTERFACE_UUID("{7364E7ED-7C27-4319-9855-11F24ACB3A77}") IEMSHostResponseHeaders  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetHeader(const System::UnicodeString AName) = 0 ;
	virtual void __fastcall SetHeader(const System::UnicodeString AName, const System::UnicodeString AValue) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSHostResponse : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	virtual System::Classes::TStream* __fastcall GetContentStream() = 0 ;
	virtual System::UnicodeString __fastcall GetContentType() = 0 ;
	virtual int __fastcall GetStatusCode() = 0 ;
	virtual void __fastcall SetContentStream(System::Classes::TStream* const Value) = 0 ;
	virtual void __fastcall SetStatusCode(const int Value) = 0 ;
	virtual _di_IEMSHostRequest __fastcall GetRequest() = 0 ;
	virtual void __fastcall SetContentType(const System::UnicodeString Value) = 0 ;
	virtual System::UnicodeString __fastcall GetReasonString();
public:
	/* TObject.Create */ inline __fastcall TEMSHostResponse() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSHostResponse() { }
	
private:
	void *__IEMSHostResponse;	// IEMSHostResponse 
	
public:
	operator IEMSHostResponse*(void) { return (IEMSHostResponse*)&__IEMSHostResponse; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface IEMSHostContext  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{4BF0A003-61EE-4196-8D6E-DBC9ACA579B3}") IEMSEdgeHostContext  : public IEMSHostContext 
{
	virtual System::UnicodeString __fastcall GetModuleName() = 0 ;
	virtual System::UnicodeString __fastcall GetModuleVersion() = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<System::UnicodeString> __fastcall GetGroupsByUser(const System::UnicodeString AUserID, const System::UnicodeString ATenantId) = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<System::UnicodeString> __fastcall GetGroupsByUser(const System::UnicodeString AUserID, const System::UnicodeString ATenantId) = 0 ;
#endif /* _WIN64 */
	virtual bool __fastcall UserIDOfSession(const System::UnicodeString ASessionToken, /* out */ System::UnicodeString &AUserID) = 0 ;
	virtual bool __fastcall UserNameOfID(const System::UnicodeString AUserID, /* out */ System::UnicodeString &AUserName) = 0 ;
	virtual System::UnicodeString __fastcall GetTenantNameByTenantId(const System::UnicodeString ATenantId) = 0 ;
	__property System::UnicodeString ModuleName = {read=GetModuleName};
	__property System::UnicodeString ModuleVersion = {read=GetModuleVersion};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEdgeHostContext : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetModuleName() = 0 ;
	virtual System::UnicodeString __fastcall GetModuleVersion() = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<System::UnicodeString> __fastcall GetGroupsByUser(const System::UnicodeString AUserID, const System::UnicodeString ATenantId) = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<System::UnicodeString> __fastcall GetGroupsByUser(const System::UnicodeString AUserID, const System::UnicodeString ATenantId) = 0 ;
#endif /* _WIN64 */
	virtual bool __fastcall UserIDOfSession(const System::UnicodeString ASessionID, /* out */ System::UnicodeString &AUserID) = 0 ;
	virtual bool __fastcall UserNameOfID(const System::UnicodeString AUserID, /* out */ System::UnicodeString &AUserName) = 0 ;
	virtual System::UnicodeString __fastcall GetTenantNameByTenantId(const System::UnicodeString ATenantId) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TEMSEdgeHostContext() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSEdgeHostContext() { }
	
private:
	void *__IEMSEdgeHostContext;	// IEMSEdgeHostContext 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4BF0A003-61EE-4196-8D6E-DBC9ACA579B3}
	operator _di_IEMSEdgeHostContext()
	{
		_di_IEMSEdgeHostContext intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IEMSEdgeHostContext*(void) { return (IEMSEdgeHostContext*)&__IEMSEdgeHostContext; }
	#endif
	operator IEMSHostContext*(void) { return (IEMSHostContext*)&__IEMSEdgeHostContext; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Requesttypes */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_REQUESTTYPES)
using namespace Emshosting::Requesttypes;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_RequesttypesHPP
