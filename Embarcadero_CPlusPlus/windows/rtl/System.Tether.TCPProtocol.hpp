// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Tether.TCPProtocol.pas' rev: 34.00 (Windows)

#ifndef System_Tether_TcpprotocolHPP
#define System_Tether_TcpprotocolHPP

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
#include <System.Tether.Manager.hpp>
#include <System.Tether.Comm.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Tether
{
namespace Tcpprotocol
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTetheringTCPProtocol;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringTCPProtocol : public System::Tether::Manager::TTetheringProtocol
{
	typedef System::Tether::Manager::TTetheringProtocol inherited;
	
	
private:
	typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::Tether::Comm::TTetheringCustomComm*> TConnectionPair;
	
	
public:
	#define TTetheringTCPProtocol_ProtocolID L"TCP"
	
	
private:
	static const System::Byte ReadTimeout = System::Byte(0xc8);
	
	System::Tether::Comm::TTetheringCustomComm* FTCPClient;
	System::Tether::Comm::TTetheringCustomComm* FTCPResponseClient;
	System::Tether::Comm::TTetheringCustomServerComm* FTCPServer;
	System::UnicodeString FImplementationID;
	System::UnicodeString FActiveTarget;
	bool FAsClient;
	void __fastcall DoOnExecute(System::Tether::Comm::TTetheringCustomComm* const AConnection);
	void __fastcall DoOnConnect(System::Tether::Comm::TTetheringCustomComm* const AConnection);
	void __fastcall DoOnDisconnect(System::Tether::Comm::TTetheringCustomComm* const AConnection);
	void __fastcall StartServerSide();
	
protected:
	virtual System::UnicodeString __fastcall GetProtocolType();
	virtual bool __fastcall GetIsConnected();
#ifndef _WIN64
	virtual void __fastcall DoSendData(const System::DynamicArray<System::Byte> AData);
	virtual System::DynamicArray<System::Byte> __fastcall DoReceiveData();
#else /* _WIN64 */
	virtual void __fastcall DoSendData(const System::TArray__1<System::Byte> AData);
	virtual System::TArray__1<System::Byte> __fastcall DoReceiveData();
#endif /* _WIN64 */
	virtual bool __fastcall DoReceiveStream(System::Classes::TStream* const AStream);
	virtual bool __fastcall DoSendStream(System::Classes::TStream* const AStream);
	
public:
	__fastcall virtual TTetheringTCPProtocol(System::Tether::Manager::TTetheringAdapter* const AnAdapter, bool AsClient);
	__fastcall virtual ~TTetheringTCPProtocol();
	virtual void __fastcall StopCommunication();
	virtual void __fastcall StartCommunication();
	virtual bool __fastcall Connect(System::Tether::Manager::TTetheringConnection* const AProfile)/* overload */;
	virtual bool __fastcall Connect(System::Tether::Manager::TTetheringConnection* const AProfile, int ATimeout)/* overload */;
	virtual void __fastcall Disconnect();
	virtual System::UnicodeString __fastcall GetConnectionString(const System::UnicodeString ManagerConnectionString);
	__classmethod virtual System::Tether::Manager::TTetheringProtocol* __fastcall CreateInstance(System::Tether::Manager::TTetheringAdapter* const AnAdapter, bool AsClient);
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Tcpprotocol */
}	/* namespace Tether */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_TETHER_TCPPROTOCOL)
using namespace System::Tether::Tcpprotocol;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_TETHER)
using namespace System::Tether;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Tether_TcpprotocolHPP
