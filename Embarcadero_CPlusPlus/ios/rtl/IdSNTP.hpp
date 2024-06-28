// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSNTP.pas' rev: 34.00 (iOS)

#ifndef IdsntpHPP
#define IdsntpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdUDPClient.hpp>
#include <IdUDPBase.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsntp
{
//-- forward type declarations -----------------------------------------------
struct TNTPGram;
class DELPHICLASS TIdSNTP;
//-- type declarations -------------------------------------------------------
#pragma pack(push,1)
struct DECLSPEC_DRECORD TNTPGram
{
public:
	System::Byte Head1;
	System::Byte Head2;
	System::Byte Head3;
	System::Byte Head4;
	unsigned RootDelay;
	unsigned RootDispersion;
	unsigned RefID;
	unsigned Ref1;
	unsigned Ref2;
	unsigned Org1;
	unsigned Org2;
	unsigned Rcv1;
	unsigned Rcv2;
	unsigned Xmit1;
	unsigned Xmit2;
};
#pragma pack(pop)


class PASCALIMPLEMENTATION TIdSNTP : public Idudpclient::TIdUDPClient
{
	typedef Idudpclient::TIdUDPClient inherited;
	
protected:
	System::TDateTime FDestinationTimestamp;
	System::TDateTime FLocalClockOffset;
	System::TDateTime FOriginateTimestamp;
	System::TDateTime FReceiveTimestamp;
	System::TDateTime FRoundTripDelay;
	System::TDateTime FTransmitTimestamp;
	bool FCheckStratum;
	void __fastcall DateTimeToNTP(System::TDateTime ADateTime, unsigned &Second, unsigned &Fraction);
	System::TDateTime __fastcall NTPToDateTime(unsigned Second, unsigned Fraction);
	bool __fastcall Disregard(const TNTPGram &ANTPMessage);
	System::TDateTime __fastcall GetAdjustmentTime();
	System::TDateTime __fastcall GetDateTime();
	virtual void __fastcall InitComponent();
	
public:
	bool __fastcall SyncTime();
	__property System::TDateTime AdjustmentTime = {read=GetAdjustmentTime};
	__property System::TDateTime DateTime = {read=GetDateTime};
	__property System::TDateTime RoundTripDelay = {read=FRoundTripDelay};
	__property bool CheckStratum = {read=FCheckStratum, write=FCheckStratum, default=1};
public:
	/* TIdUDPClient.Destroy */ inline __fastcall virtual ~TIdSNTP() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSNTP(System::Classes::TComponent* AOwner)/* overload */ : Idudpclient::TIdUDPClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSNTP()/* overload */ : Idudpclient::TIdUDPClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define NTPMaxInt  (4.294967E+09)
}	/* namespace Idsntp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSNTP)
using namespace Idsntp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsntpHPP
