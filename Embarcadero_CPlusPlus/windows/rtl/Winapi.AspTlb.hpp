// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.AspTlb.pas' rev: 34.00 (Windows)

#ifndef Winapi_AsptlbHPP
#define Winapi_AsptlbHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.Win.ComObj.hpp>
#include <Winapi.Mtx.hpp>

//-- user supplied -----------------------------------------------------------
#include <asptlb.h>
DECLARE_DINTERFACE_TYPE(IStringList)
DECLARE_DINTERFACE_TYPE(IRequestDictionary)
DECLARE_DINTERFACE_TYPE(IRequest)
DECLARE_DINTERFACE_TYPE(IReadCookie)
DECLARE_DINTERFACE_TYPE(IWriteCookie)
DECLARE_DINTERFACE_TYPE(IResponse)
DECLARE_DINTERFACE_TYPE(IVariantDictionary)
DECLARE_DINTERFACE_TYPE(ISessionObject)
DECLARE_DINTERFACE_TYPE(IApplicationObject)
DECLARE_DINTERFACE_TYPE(IServer)
DECLARE_DINTERFACE_TYPE(IScriptingContext)
// comsvcs.h contains a macro for GetObjectContext that 
// conflicts with TASPMTSObject::GetObjectContext() 
// Use CoGetObjectContext directly:( 
#if defined(GetObjectContext)
  #undef GetObjectContext
#endif

namespace Winapi
{
namespace Asptlb
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IASPObject;
typedef System::DelphiInterface<IASPObject> _di_IASPObject;
class DELPHICLASS TASPObject;
class DELPHICLASS TASPMTSObject;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{7A8B9910-F33C-11D2-9EDD-00C04F6539EE}") IASPObject  : public System::IInterface 
{
	virtual HRESULT __safecall OnStartPage(const System::_di_IInterface AScriptingContext) = 0 ;
	virtual HRESULT __safecall OnEndPage() = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TASPObject : public System::Win::Comobj::TAutoObject
{
	typedef System::Win::Comobj::TAutoObject inherited;
	
private:
	_di_IScriptingContext FScriptingContext;
	_di_IApplicationObject __fastcall GetApplication();
	_di_IRequest __fastcall GetRequest();
	_di_IResponse __fastcall GetResponse();
	_di_IScriptingContext __fastcall GetScriptingContext();
	_di_IServer __fastcall GetServer();
	_di_ISessionObject __fastcall GetSession();
	
public:
	HRESULT __safecall OnStartPage(const System::_di_IInterface AScriptingContext);
	HRESULT __safecall OnEndPage();
	__property _di_IScriptingContext ScriptingContext = {read=GetScriptingContext};
	__property _di_IRequest Request = {read=GetRequest};
	__property _di_IResponse Response = {read=GetResponse};
	__property _di_ISessionObject Session = {read=GetSession};
	__property _di_IServer Server = {read=GetServer};
	__property _di_IApplicationObject Application = {read=GetApplication};
public:
	/* TAutoObject.Create */ inline __fastcall TASPObject() : System::Win::Comobj::TAutoObject() { }
	/* TAutoObject.CreateAggregated */ inline __fastcall TASPObject(const System::_di_IInterface Controller) : System::Win::Comobj::TAutoObject(Controller) { }
	/* TAutoObject.CreateFromFactory */ inline __fastcall TASPObject(System::Win::Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller) : System::Win::Comobj::TAutoObject(Factory, Controller) { }
	
public:
	/* TComObject.Destroy */ inline __fastcall virtual ~TASPObject() { }
	
private:
	void *__IASPObject;	// IASPObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7A8B9910-F33C-11D2-9EDD-00C04F6539EE}
	operator _di_IASPObject()
	{
		_di_IASPObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IASPObject*(void) { return (IASPObject*)&__IASPObject; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TASPMTSObject : public System::Win::Comobj::TAutoObject
{
	typedef System::Win::Comobj::TAutoObject inherited;
	
private:
	_di_IApplicationObject __fastcall GetApplication();
	_di_IRequest __fastcall GetRequest();
	_di_IResponse __fastcall GetResponse();
	_di_IServer __fastcall GetServer();
	_di_ISessionObject __fastcall GetSession();
	_di_IObjectContext __fastcall GetObjectContext();
	
public:
	__property _di_IApplicationObject Application = {read=GetApplication};
	__property _di_IObjectContext ObjectContext = {read=GetObjectContext};
	__property _di_IRequest Request = {read=GetRequest};
	__property _di_IResponse Response = {read=GetResponse};
	__property _di_ISessionObject Session = {read=GetSession};
	__property _di_IServer Server = {read=GetServer};
public:
	/* TAutoObject.Create */ inline __fastcall TASPMTSObject() : System::Win::Comobj::TAutoObject() { }
	/* TAutoObject.CreateAggregated */ inline __fastcall TASPMTSObject(const System::_di_IInterface Controller) : System::Win::Comobj::TAutoObject(Controller) { }
	/* TAutoObject.CreateFromFactory */ inline __fastcall TASPMTSObject(System::Win::Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller) : System::Win::Comobj::TAutoObject(Factory, Controller) { }
	
public:
	/* TComObject.Destroy */ inline __fastcall virtual ~TASPMTSObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Asptlb */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_ASPTLB)
using namespace Winapi::Asptlb;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_AsptlbHPP
