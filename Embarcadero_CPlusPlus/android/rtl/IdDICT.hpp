// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdDICT.pas' rev: 34.00 (Android)

#ifndef IddictHPP
#define IddictHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdComponent.hpp>
#include <IdDICTCommon.hpp>
#include <IdSASLCollection.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iddict
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdDICT;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdDICTAuthenticationType : unsigned char { datDefault, datSASL };

class PASCALIMPLEMENTATION TIdDICT : public Idtcpclient::TIdTCPClient
{
	typedef Idtcpclient::TIdTCPClient inherited;
	
protected:
	bool FTryMIME;
	TIdDICTAuthenticationType FAuthType;
	Idsaslcollection::TIdSASLEntries* FSASLMechanisms;
	System::UnicodeString FServer;
	System::UnicodeString FClient;
	System::Classes::TStrings* FCapabilities;
	virtual void __fastcall InitComponent();
	bool __fastcall IsCapaSupported(const System::UnicodeString ACapa);
	void __fastcall SetClient(const System::UnicodeString AValue);
	void __fastcall InternalGetList(const System::UnicodeString ACmd, System::Classes::TCollection* AENtries);
	void __fastcall InternalGetStrs(const System::UnicodeString ACmd, System::Classes::TStrings* AStrs);
	
public:
	__fastcall TIdDICT(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TIdDICT();
	virtual void __fastcall Connect()/* overload */;
	virtual void __fastcall DisconnectNotifyPeer();
	void __fastcall GetDictInfo(const System::UnicodeString ADict, System::Classes::TStrings* AResults);
	void __fastcall GetSvrInfo(System::Classes::TStrings* AResults);
	void __fastcall GetDBList(Iddictcommon::TIdDBList* ADB);
	void __fastcall GetStrategyList(Iddictcommon::TIdStrategyList* AStrats);
	void __fastcall Define(const System::UnicodeString AWord, const System::UnicodeString ADBName, Iddictcommon::TIdDefinitions* AResults)/* overload */;
	void __fastcall Define(const System::UnicodeString AWord, Iddictcommon::TIdDefinitions* AResults, const bool AGetAll = true)/* overload */;
	void __fastcall Match(const System::UnicodeString AWord, const System::UnicodeString ADBName, const System::UnicodeString AStrat, Iddictcommon::TIdMatchList* AResults)/* overload */;
	void __fastcall Match(const System::UnicodeString AWord, const System::UnicodeString AStrat, Iddictcommon::TIdMatchList* AResults, const bool AGetAll = true)/* overload */;
	void __fastcall Match(const System::UnicodeString AWord, Iddictcommon::TIdMatchList* AResults, const bool AGetAll = true)/* overload */;
	__property System::Classes::TStrings* Capabilities = {read=FCapabilities};
	__property System::UnicodeString Server = {read=FServer};
	
__published:
	__property bool TryMIME = {read=FTryMIME, write=FTryMIME, default=0};
	__property System::UnicodeString Client = {read=FClient, write=SetClient};
	__property TIdDICTAuthenticationType AuthType = {read=FAuthType, write=FAuthType, default=0};
	__property Idsaslcollection::TIdSASLEntries* SASLMechanisms = {read=FSASLMechanisms, write=FSASLMechanisms};
	__property Port = {default=2628};
	__property Username = {default=0};
	__property Password = {default=0};
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDICT()/* overload */ : Idtcpclient::TIdTCPClient() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Connect(const System::UnicodeString AHost){ Idtcpclient::TIdTCPClientCustom::Connect(AHost); }
	inline void __fastcall  Connect(const System::UnicodeString AHost, const System::Word APort){ Idtcpclient::TIdTCPClientCustom::Connect(AHost, APort); }
	
};


//-- var, const, procedure ---------------------------------------------------
static const TIdDICTAuthenticationType DICT_AUTHDEF = (TIdDICTAuthenticationType)(0);
static constexpr bool DEF_TRYMIME = false;
}	/* namespace Iddict */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDDICT)
using namespace Iddict;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IddictHPP
