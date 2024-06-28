// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.DSDef.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_DsdefHPP
#define Firedac_Phys_DsdefHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Dsdef
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysDSConnectionDefParams;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDDSProtocol : unsigned int { prTcp_ip };

enum DECLSPEC_DENUM TFDDSCommunicationIPVersion : unsigned int { cipNone, cipIP_IPv4, cipIP_IPv6 };

enum DECLSPEC_DENUM TFDDSAuthenticationScheme : unsigned int { dsaNone, dsaBasic };

class PASCALIMPLEMENTATION TFDPhysDSConnectionDefParams : public Firedac::Stan::Intf::TFDConnectionDefParams
{
	typedef Firedac::Stan::Intf::TFDConnectionDefParams inherited;
	
private:
	HIDESBASE System::UnicodeString __fastcall GetDriverID();
	HIDESBASE void __fastcall SetDriverID(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetDBXAdvanced();
	void __fastcall SetDBXAdvanced(const System::UnicodeString AValue);
	TFDDSProtocol __fastcall GetProtocol();
	void __fastcall SetProtocol(const TFDDSProtocol AValue);
	System::UnicodeString __fastcall GetIPImplementationID();
	void __fastcall SetIPImplementationID(const System::UnicodeString AValue);
	TFDDSCommunicationIPVersion __fastcall GetCommunicationIPVersion();
	void __fastcall SetCommunicationIPVersion(const TFDDSCommunicationIPVersion AValue);
	System::UnicodeString __fastcall GetServer();
	void __fastcall SetServer(const System::UnicodeString AValue);
	int __fastcall GetPort();
	void __fastcall SetPort(const int AValue);
	int __fastcall GetBufferKBSize();
	void __fastcall SetBufferKBSize(const int AValue);
	System::UnicodeString __fastcall GetFilters();
	void __fastcall SetFilters(const System::UnicodeString AValue);
	int __fastcall GetLoginTimeout();
	void __fastcall SetLoginTimeout(const int AValue);
	int __fastcall GetCommunicationTimeout();
	void __fastcall SetCommunicationTimeout(const int AValue);
	System::UnicodeString __fastcall GetURLPath();
	void __fastcall SetURLPath(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetDatasnapContext();
	void __fastcall SetDatasnapContext(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetDSProxyHost();
	void __fastcall SetDSProxyHost(const System::UnicodeString AValue);
	int __fastcall GetDSProxyPort();
	void __fastcall SetDSProxyPort(const int AValue);
	System::UnicodeString __fastcall GetDSProxyUsername();
	void __fastcall SetDSProxyUsername(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetDSProxyPassword();
	void __fastcall SetDSProxyPassword(const System::UnicodeString AValue);
	TFDDSAuthenticationScheme __fastcall GetDSAuthenticationScheme();
	void __fastcall SetDSAuthenticationScheme(const TFDDSAuthenticationScheme AValue);
	
__published:
	__property System::UnicodeString DriverID = {read=GetDriverID, write=SetDriverID, stored=false};
	__property System::UnicodeString DBXAdvanced = {read=GetDBXAdvanced, write=SetDBXAdvanced, stored=false};
	__property TFDDSProtocol Protocol = {read=GetProtocol, write=SetProtocol, stored=false, default=0};
	__property System::UnicodeString IPImplementationID = {read=GetIPImplementationID, write=SetIPImplementationID, stored=false};
	__property TFDDSCommunicationIPVersion CommunicationIPVersion = {read=GetCommunicationIPVersion, write=SetCommunicationIPVersion, stored=false, nodefault};
	__property System::UnicodeString Server = {read=GetServer, write=SetServer, stored=false};
	__property int Port = {read=GetPort, write=SetPort, stored=false, default=8080};
	__property int BufferKBSize = {read=GetBufferKBSize, write=SetBufferKBSize, stored=false, default=32};
	__property System::UnicodeString Filters = {read=GetFilters, write=SetFilters, stored=false};
	__property int LoginTimeout = {read=GetLoginTimeout, write=SetLoginTimeout, stored=false, default=10000};
	__property int CommunicationTimeout = {read=GetCommunicationTimeout, write=SetCommunicationTimeout, stored=false, nodefault};
	__property System::UnicodeString URLPath = {read=GetURLPath, write=SetURLPath, stored=false};
	__property System::UnicodeString DatasnapContext = {read=GetDatasnapContext, write=SetDatasnapContext, stored=false};
	__property System::UnicodeString DSProxyHost = {read=GetDSProxyHost, write=SetDSProxyHost, stored=false};
	__property int DSProxyPort = {read=GetDSProxyPort, write=SetDSProxyPort, stored=false, default=8888};
	__property System::UnicodeString DSProxyUsername = {read=GetDSProxyUsername, write=SetDSProxyUsername, stored=false};
	__property System::UnicodeString DSProxyPassword = {read=GetDSProxyPassword, write=SetDSProxyPassword, stored=false};
	__property TFDDSAuthenticationScheme DSAuthenticationScheme = {read=GetDSAuthenticationScheme, write=SetDSAuthenticationScheme, stored=false, nodefault};
public:
	/* TFDConnectionDefParams.Create */ inline __fastcall TFDPhysDSConnectionDefParams(const Firedac::Stan::Intf::_di_IFDStanDefinition ADef) : Firedac::Stan::Intf::TFDConnectionDefParams(ADef) { }
	/* TFDConnectionDefParams.Destroy */ inline __fastcall virtual ~TFDPhysDSConnectionDefParams() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsdef */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_DSDEF)
using namespace Firedac::Phys::Dsdef;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS)
using namespace Firedac::Phys;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Phys_DsdefHPP
