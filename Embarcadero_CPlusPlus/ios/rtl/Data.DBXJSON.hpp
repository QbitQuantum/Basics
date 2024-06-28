// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXJSON.pas' rev: 34.00 (iOS)

#ifndef Data_DbxjsonHPP
#define Data_DbxjsonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.SysUtils.hpp>
#include <System.JSON.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxjson
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXCallback;
class DELPHICLASS TDBXCallbackDelegate;
class DELPHICLASS TDBXNamedCallback;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXCallback : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::Json::TJSONValue* __fastcall Execute(System::Json::TJSONValue* const Arg) = 0 /* overload */;
	virtual System::TObject* __fastcall Execute(System::TObject* Arg) = 0 /* overload */;
	virtual int __fastcall AddRef();
	virtual int __fastcall Release();
	
protected:
	virtual void __fastcall SetConnectionHandler(System::TObject* const ConnectionHandler);
	virtual void __fastcall SetDsServer(System::TObject* const DsServer);
	virtual void __fastcall SetOrdinal(const int Ordinal);
	virtual bool __fastcall IsConnectionLost();
	
private:
	int FFRefCount;
	
public:
	__property System::TObject* ConnectionHandler = {write=SetConnectionHandler};
	__property System::TObject* DsServer = {write=SetDsServer};
	__property int Ordinal = {write=SetOrdinal, nodefault};
	__property bool ConnectionLost = {read=IsConnectionLost, nodefault};
	static constexpr System::Int8 ArgJson = System::Int8(0x1);
	
	static constexpr System::Int8 ArgObject = System::Int8(0x2);
	
public:
	/* TObject.Create */ inline __fastcall TDBXCallback() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXCallback() { }
	
};


class PASCALIMPLEMENTATION TDBXCallbackDelegate : public TDBXCallback
{
	typedef TDBXCallback inherited;
	
public:
	__fastcall virtual ~TDBXCallbackDelegate();
	virtual System::Json::TJSONValue* __fastcall Execute(System::Json::TJSONValue* const Arg)/* overload */;
	virtual System::TObject* __fastcall Execute(System::TObject* Arg)/* overload */;
	
protected:
	virtual void __fastcall SetDelegate(TDBXCallback* const Callback);
	virtual TDBXCallback* __fastcall GetDelegate();
	virtual void __fastcall SetConnectionHandler(System::TObject* const ConnectionHandler);
	virtual void __fastcall SetOrdinal(const int Ordinal);
	virtual void __fastcall SetDsServer(System::TObject* const DsServer);
	virtual bool __fastcall IsConnectionLost();
	
private:
	TDBXCallback* FDelegate;
	System::TObject* FConnectionHandler;
	System::TObject* FDsServer;
	int FOrdinal;
	
public:
	__property TDBXCallback* Delegate = {read=GetDelegate, write=SetDelegate};
public:
	/* TObject.Create */ inline __fastcall TDBXCallbackDelegate() : TDBXCallback() { }
	
};


class PASCALIMPLEMENTATION TDBXNamedCallback : public TDBXCallback
{
	typedef TDBXCallback inherited;
	
public:
	__fastcall TDBXNamedCallback(const System::UnicodeString Name);
	
protected:
	virtual System::UnicodeString __fastcall GetName();
	System::UnicodeString FName;
	
public:
	__property System::UnicodeString Name = {read=GetName};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXNamedCallback() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::Sysutils::TFormatSettings __fastcall GetUSFormat(void);
}	/* namespace Dbxjson */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXJSON)
using namespace Data::Dbxjson;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxjsonHPP
