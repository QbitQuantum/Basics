// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.Win.MConnect.pas' rev: 34.00 (Windows)

#ifndef Datasnap_Win_MconnectHPP
#define Datasnap_Win_MconnectHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Variants.hpp>
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Datasnap.Midas.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.Win.ComObj.hpp>
#include <Datasnap.Provider.hpp>
#include <Data.DBCommonTypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Win
{
namespace Mconnect
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomObjectBroker;
class DELPHICLASS TDispatchAppServer;
class DELPHICLASS TDispatchConnection;
class DELPHICLASS TCOMConnection;
class DELPHICLASS TDCOMConnection;
class DELPHICLASS TOLEnterpriseConnection;
class DELPHICLASS TSharedConnection;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomObjectBroker : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	virtual void __fastcall SetConnectStatus(System::UnicodeString ComputerName, bool Success) = 0 ;
	virtual System::UnicodeString __fastcall GetComputerForGUID(const GUID &GUID) = 0 ;
	virtual System::UnicodeString __fastcall GetComputerForProgID(const void *ProgID) = 0 ;
	virtual int __fastcall GetPortForComputer(const System::UnicodeString ComputerName) = 0 ;
public:
	/* TComponent.Create */ inline __fastcall virtual TCustomObjectBroker(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomObjectBroker() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDispatchAppServer : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Datasnap::Midas::_di_IAppServerDisp FAppServer;
	HRESULT __stdcall GetTypeInfoCount(/* out */ int &Count);
	HRESULT __stdcall GetTypeInfo(int Index, int LocaleID, /* out */ void *TypeInfo);
	HRESULT __stdcall GetIDsOfNames(const GUID &IID, void * Names, int NameCount, int LocaleID, void * DispIDs);
	HRESULT __stdcall Invoke(int DispID, const GUID &IID, int LocaleID, System::Word Flags, void *Params, void * VarResult, void * ExcepInfo, void * ArgErr);
	HRESULT __safecall AS_ApplyUpdates(const System::WideString ProviderName, System::OleVariant Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData, System::OleVariant &__AS_ApplyUpdates_result);
	HRESULT __safecall AS_GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData, System::OleVariant &__AS_GetRecords_result);
	HRESULT __safecall AS_DataRequest(const System::WideString ProviderName, System::OleVariant Data, System::OleVariant &__AS_DataRequest_result);
	HRESULT __safecall AS_GetProviderNames(System::OleVariant &__AS_GetProviderNames_result);
	HRESULT __safecall AS_GetParams(const System::WideString ProviderName, System::OleVariant &OwnerData, System::OleVariant &__AS_GetParams_result);
	HRESULT __safecall AS_RowRequest(const System::WideString ProviderName, System::OleVariant Row, int RequestType, System::OleVariant &OwnerData, System::OleVariant &__AS_RowRequest_result);
	HRESULT __safecall AS_Execute(const System::WideString ProviderName, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	HRESULT __stdcall InterfaceSupportsErrorInfo(const GUID &iid);
	
public:
	__fastcall TDispatchAppServer(const Datasnap::Midas::_di_IAppServerDisp AppServer);
	virtual HRESULT __fastcall SafeCallException(System::TObject* ExceptObject, void * ExceptAddr);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDispatchAppServer() { }
	
private:
	void *__ISupportErrorInfo;	// ISupportErrorInfo 
	void *__IAppServer;	// Datasnap::Midas::IAppServer 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DF0B3D60-548F-101B-8E65-08002B2BD119}
	operator _di_ISupportErrorInfo()
	{
		_di_ISupportErrorInfo intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ISupportErrorInfo*(void) { return (ISupportErrorInfo*)&__ISupportErrorInfo; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1AEFCC20-7A24-11D2-98B0-C69BEB4B5B6D}
	operator Datasnap::Midas::_di_IAppServer()
	{
		Datasnap::Midas::_di_IAppServer intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Datasnap::Midas::IAppServer*(void) { return (Datasnap::Midas::IAppServer*)&__IAppServer; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDispatchConnection : public Datasnap::Dbclient::TCustomRemoteServer
{
	typedef Datasnap::Dbclient::TCustomRemoteServer inherited;
	
private:
	GUID FServerGUID;
	System::UnicodeString FServerName;
	TCustomObjectBroker* FObjectBroker;
	System::UnicodeString __fastcall GetServerGUID();
	void __fastcall SetServerGUID(const System::UnicodeString Value);
	void __fastcall SetServerName(const System::UnicodeString Value);
	void __fastcall SetObjectBroker(TCustomObjectBroker* Value);
	
protected:
	virtual void __fastcall DoDisconnect();
	virtual bool __fastcall GetConnected();
	virtual void __fastcall SetConnected(bool Value);
	GUID __fastcall GetServerCLSID();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	__property TCustomObjectBroker* ObjectBroker = {read=FObjectBroker, write=SetObjectBroker};
	
public:
	__fastcall virtual TDispatchConnection(System::Classes::TComponent* AOwner);
	virtual Datasnap::Midas::_di_IAppServer __fastcall GetServer();
	virtual System::OleVariant __fastcall GetServerList();
	
__published:
	__property Connected = {default=0};
	__property LoginPrompt = {default=0};
	__property System::UnicodeString ServerGUID = {read=GetServerGUID, write=SetServerGUID};
	__property System::UnicodeString ServerName = {read=FServerName, write=SetServerName};
	__property AfterConnect;
	__property AfterDisconnect;
	__property BeforeConnect;
	__property BeforeDisconnect;
	__property OnGetUsername;
	__property OnLogin;
public:
	/* TCustomConnection.Destroy */ inline __fastcall virtual ~TDispatchConnection() { }
	
};


class PASCALIMPLEMENTATION TCOMConnection : public TDispatchConnection
{
	typedef TDispatchConnection inherited;
	
protected:
	virtual void __fastcall SetConnected(bool Value);
	virtual void __fastcall DoConnect();
public:
	/* TDispatchConnection.Create */ inline __fastcall virtual TCOMConnection(System::Classes::TComponent* AOwner) : TDispatchConnection(AOwner) { }
	
public:
	/* TCustomConnection.Destroy */ inline __fastcall virtual ~TCOMConnection() { }
	
};


class PASCALIMPLEMENTATION TDCOMConnection : public TCOMConnection
{
	typedef TCOMConnection inherited;
	
private:
	System::UnicodeString FComputerName;
	void __fastcall SetComputerName(const System::UnicodeString Value);
	bool __fastcall IsComputerNameStored();
	
protected:
	virtual void __fastcall DoConnect();
	
public:
	__fastcall virtual TDCOMConnection(System::Classes::TComponent* AOwner);
	
__published:
	__property System::UnicodeString ComputerName = {read=FComputerName, write=SetComputerName, stored=IsComputerNameStored};
	__property ObjectBroker;
public:
	/* TCustomConnection.Destroy */ inline __fastcall virtual ~TDCOMConnection() { }
	
};


class PASCALIMPLEMENTATION TOLEnterpriseConnection : public TCOMConnection
{
	typedef TCOMConnection inherited;
	
private:
	System::UnicodeString FComputerName;
	System::UnicodeString FBrokerName;
	void __fastcall SetComputerName(const System::UnicodeString Value);
	void __fastcall SetBrokerName(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall DoConnect();
	
__published:
	__property System::UnicodeString ComputerName = {read=FComputerName, write=SetComputerName};
	__property System::UnicodeString BrokerName = {read=FBrokerName, write=SetBrokerName};
public:
	/* TDispatchConnection.Create */ inline __fastcall virtual TOLEnterpriseConnection(System::Classes::TComponent* AOwner) : TCOMConnection(AOwner) { }
	
public:
	/* TCustomConnection.Destroy */ inline __fastcall virtual ~TOLEnterpriseConnection() { }
	
};


class PASCALIMPLEMENTATION TSharedConnection : public Datasnap::Dbclient::TCustomRemoteServer
{
	typedef Datasnap::Dbclient::TCustomRemoteServer inherited;
	
private:
	TDispatchConnection* FParentConnection;
	System::UnicodeString FChildName;
	void __fastcall SetParentConnection(TDispatchConnection* const Value);
	
protected:
	void __fastcall ConnectEvent(System::TObject* Sender, bool Connecting);
	virtual void __fastcall DoConnect();
	virtual void __fastcall DoDisconnect();
	virtual bool __fastcall GetConnected();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual ~TSharedConnection();
	virtual Datasnap::Midas::_di_IAppServer __fastcall GetServer();
	
__published:
	__fastcall virtual TSharedConnection(System::Classes::TComponent* AOwner);
	__property TDispatchConnection* ParentConnection = {read=FParentConnection, write=SetParentConnection};
	__property System::UnicodeString ChildName = {read=FChildName, write=FChildName};
	__property AfterConnect;
	__property AfterDisconnect;
	__property BeforeConnect;
	__property BeforeDisconnect;
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall GetMIDASAppServerList(System::Classes::TStringList* List, const System::UnicodeString RegCheck);
}	/* namespace Mconnect */
}	/* namespace Win */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_WIN_MCONNECT)
using namespace Datasnap::Win::Mconnect;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_WIN)
using namespace Datasnap::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_Win_MconnectHPP
