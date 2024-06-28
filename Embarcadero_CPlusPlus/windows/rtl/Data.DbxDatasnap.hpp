// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DbxDatasnap.pas' rev: 34.00 (Windows)

#ifndef Data_DbxdatasnapHPP
#define Data_DbxdatasnapHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXClient.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXJSON.hpp>
#include <Data.DBXTransport.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.DbxDatasnap"

namespace Data
{
namespace Dbxdatasnap
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXDatasnapProperties;
class DELPHICLASS TDBXDatasnapDriver;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXDatasnapProperties : public Data::Dbxcommon::TDBXProperties
{
	typedef Data::Dbxcommon::TDBXProperties inherited;
	
private:
	Data::Dbxtransport::TTransportFilterCollection* FFilters;
	System::UnicodeString __fastcall GetHostName();
	System::UnicodeString __fastcall GetPassword();
	System::UnicodeString __fastcall GetUserName();
	int __fastcall GetPort();
	int __fastcall GetBufferKBSize();
	System::UnicodeString __fastcall GetServerConnection();
	System::UnicodeString __fastcall GetCommunicationProtocol();
	System::UnicodeString __fastcall GetCommunicationIPVersion();
	System::UnicodeString __fastcall GetURLPath();
	System::UnicodeString __fastcall GetDSAuthenticationUser();
	System::UnicodeString __fastcall GetDSAuthenticationPassword();
	System::UnicodeString __fastcall GetConnectTimeout();
	System::UnicodeString __fastcall GetCommunicationTimeout();
	Data::Dbxtransport::TTransportFilterCollection* __fastcall GetFilters();
	System::UnicodeString __fastcall GetDatasnapContext();
	System::UnicodeString __fastcall GetDSAuthenticationScheme();
	System::UnicodeString __fastcall GetDSProxyHost();
	int __fastcall GetDSProxyPort();
	System::UnicodeString __fastcall GetDSProxyUsername();
	System::UnicodeString __fastcall GetDSProxyPassword();
	void __fastcall SetPort(const int Value);
	void __fastcall SetHostName(const System::UnicodeString Value);
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	void __fastcall SetBufferKBSize(const int Value);
	void __fastcall SetServerConnection(const System::UnicodeString Value);
	void __fastcall SetCommunicationProtocol(const System::UnicodeString Value);
	void __fastcall SetCommunicationIPVersion(const System::UnicodeString Value);
	void __fastcall SetURLPath(const System::UnicodeString Value);
	void __fastcall SetDSAuthenticationUser(const System::UnicodeString Value);
	void __fastcall SetDSAuthenticationPassword(const System::UnicodeString Value);
	void __fastcall SetConnectTimeout(const System::UnicodeString Value);
	void __fastcall SetCommunicationTimeout(const System::UnicodeString Value);
	void __fastcall SetFilters(Data::Dbxtransport::TTransportFilterCollection* const Value);
	void __fastcall SetDatasnapContext(const System::UnicodeString Value);
	void __fastcall SetDSAuthenticationScheme(const System::UnicodeString Value);
	void __fastcall SetDSProxyHost(const System::UnicodeString Value);
	void __fastcall SetDSProxyPort(const int Value);
	void __fastcall SetDSProxyUsername(const System::UnicodeString Value);
	void __fastcall SetDSProxyPassword(const System::UnicodeString Value);
	void __fastcall OnFiltersChange(System::TObject* source);
	Data::Dbxcommon::TValidateCertificate __fastcall GetValidateCertificate();
	void __fastcall SetValidateCertificate(Data::Dbxcommon::TValidateCertificate Cert);
	
protected:
	virtual void __fastcall Init();
	
public:
	__fastcall virtual TDBXDatasnapProperties(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */;
	__fastcall virtual TDBXDatasnapProperties()/* overload */;
	__fastcall virtual ~TDBXDatasnapProperties();
	__property Data::Dbxcommon::TValidateCertificate OnValidatePeerCertificate = {read=GetValidateCertificate, write=SetValidateCertificate};
	
__published:
	__property System::UnicodeString HostName = {read=GetHostName, write=SetHostName};
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property int Port = {read=GetPort, write=SetPort, default=211};
	__property int BufferKBSize = {read=GetBufferKBSize, write=SetBufferKBSize, default=32};
	__property System::UnicodeString ServerConnection = {read=GetServerConnection, write=SetServerConnection};
	__property System::UnicodeString CommunicationProtocol = {read=GetCommunicationProtocol, write=SetCommunicationProtocol};
	__property System::UnicodeString CommunicationIPVersion = {read=GetCommunicationIPVersion, write=SetCommunicationIPVersion};
	__property System::UnicodeString URLPath = {read=GetURLPath, write=SetURLPath};
	__property System::UnicodeString DSAuthUser = {read=GetDSAuthenticationUser, write=SetDSAuthenticationUser};
	__property System::UnicodeString DSAuthPassword = {read=GetDSAuthenticationPassword, write=SetDSAuthenticationPassword};
	__property System::UnicodeString DSAuthScheme = {read=GetDSAuthenticationScheme, write=SetDSAuthenticationScheme};
	__property System::UnicodeString ConnectTimeout = {read=GetConnectTimeout, write=SetConnectTimeout};
	__property System::UnicodeString CommunicationTimeout = {read=GetCommunicationTimeout, write=SetCommunicationTimeout};
	__property Data::Dbxtransport::TTransportFilterCollection* Filters = {read=GetFilters, write=SetFilters};
	__property System::UnicodeString DatasnapContext = {read=GetDatasnapContext, write=SetDatasnapContext};
	__property System::UnicodeString DSProxyHost = {read=GetDSProxyHost, write=SetDSProxyHost};
	__property int DSProxyPort = {read=GetDSProxyPort, write=SetDSProxyPort, nodefault};
	__property System::UnicodeString DSProxyUsername = {read=GetDSProxyUsername, write=SetDSProxyUsername};
	__property System::UnicodeString DSProxyPassword = {read=GetDSProxyPassword, write=SetDSProxyPassword};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDatasnapDriver : public Data::Dbxclient::TDBXClientDriver
{
	typedef Data::Dbxclient::TDBXClientDriver inherited;
	
public:
	__fastcall virtual TDBXDatasnapDriver(const Data::Dbxcommon::TDBXDriverDef &DriverDef)/* overload */;
public:
	/* TDBXClientDriver.Create */ inline __fastcall TDBXDatasnapDriver(const Data::Dbxcommon::TDBXDriverDef &DriverDef, Data::Dbxcommon::TDBXProperties* DriverProps)/* overload */ : Data::Dbxclient::TDBXClientDriver(DriverDef, DriverProps) { }
	
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXDatasnapDriver()/* overload */ : Data::Dbxclient::TDBXClientDriver() { }
	/* TDBXDriver.Destroy */ inline __fastcall virtual ~TDBXDatasnapDriver() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define DS_CONTEXT L"datasnap/"
}	/* namespace Dbxdatasnap */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXDATASNAP)
using namespace Data::Dbxdatasnap;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxdatasnapHPP
