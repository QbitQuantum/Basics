// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSNMP.pas' rev: 34.00 (Android)

#ifndef IdsnmpHPP
#define IdsnmpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdASN1Util.hpp>
#include <IdException.hpp>
#include <IdGlobal.hpp>
#include <IdUDPBase.hpp>
#include <IdUDPClient.hpp>
#include <IdSocketHandle.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsnmp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSNMPInfo;
class DELPHICLASS TIdSNMP;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSNMPInfo : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TIdSNMP* fOwner;
	System::UnicodeString fCommunity;
	System::UnicodeString __fastcall GetValue(int idx);
	int __fastcall GetValueCount();
	int __fastcall GetValueType(int idx);
	System::UnicodeString __fastcall GetValueOID(int idx);
	void __fastcall SetCommunity(const System::UnicodeString Value);
	
protected:
	System::UnicodeString Buffer;
	void __fastcall SyncMIB();
	
public:
	System::UnicodeString Host;
	System::Word Port;
	System::UnicodeString Enterprise;
	int GenTrap;
	int SpecTrap;
	int Version;
	int PDUType;
	int TimeTicks;
	int ID;
	int ErrorStatus;
	int ErrorIndex;
	System::Classes::TStrings* MIBOID;
	System::Classes::TStrings* MIBValue;
	__fastcall TSNMPInfo(TIdSNMP* AOwner);
	__fastcall virtual ~TSNMPInfo();
	bool __fastcall EncodeTrap();
	bool __fastcall DecodeTrap();
	void __fastcall DecodeBuf(System::UnicodeString Buffer);
	System::UnicodeString __fastcall EncodeBuf();
	void __fastcall Clear();
	void __fastcall MIBAdd(System::UnicodeString MIB, System::UnicodeString Value, int ValueType = 0x4);
	void __fastcall MIBDelete(int Index);
	System::UnicodeString __fastcall MIBGet(System::UnicodeString MIB);
	__property TIdSNMP* Owner = {read=fOwner};
	__property System::UnicodeString Community = {read=fCommunity, write=SetCommunity};
	__property int ValueCount = {read=GetValueCount, nodefault};
	__property System::UnicodeString Value[int idx] = {read=GetValue};
	__property System::UnicodeString ValueOID[int idx] = {read=GetValueOID};
	__property int ValueType[int idx] = {read=GetValueType};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TIdSNMP : public Idudpclient::TIdUDPClient
{
	typedef Idudpclient::TIdUDPClient inherited;
	
protected:
	System::UnicodeString fCommunity;
	System::Word fTrapPort;
	Idsockethandle::TIdSocketHandle* fTrapRecvBinding;
	void __fastcall SetCommunity(const System::UnicodeString Value);
	void __fastcall SetTrapPort(const System::Word AValue);
	virtual void __fastcall InitComponent();
	virtual Idsockethandle::TIdSocketHandle* __fastcall GetBinding();
	virtual void __fastcall CloseBinding();
	
public:
	TSNMPInfo* Query;
	TSNMPInfo* Reply;
	TSNMPInfo* Trap;
	__fastcall TIdSNMP(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TIdSNMP();
	bool __fastcall SendQuery();
	bool __fastcall QuickSend(const System::UnicodeString Mib, const System::UnicodeString DestCommunity, const System::UnicodeString DestHost, System::UnicodeString &Value);
	bool __fastcall QuickSendTrap(const System::UnicodeString DestHost, const System::UnicodeString Enterprise, const System::UnicodeString DestCommunity, System::Word DestPort, int Generic, int Specific, System::Classes::TStrings* MIBName, System::Classes::TStrings* MIBValue);
	bool __fastcall QuickReceiveTrap(System::UnicodeString &SrcHost, System::UnicodeString &Enterprise, System::UnicodeString &SrcCommunity, System::Word &SrcPort, int &Generic, int &Specific, int &Seconds, System::Classes::TStrings* MIBName, System::Classes::TStrings* MIBValue);
	bool __fastcall SendTrap();
	bool __fastcall ReceiveTrap();
	
__published:
	__property Port = {default=161};
	__property System::Word TrapPort = {read=fTrapPort, write=SetTrapPort, default=162};
	__property System::UnicodeString Community = {read=fCommunity, write=SetCommunity};
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSNMP()/* overload */ : Idudpclient::TIdUDPClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Byte PDUGetRequest = System::Byte(0xa0);
static constexpr System::Byte PDUGetNextRequest = System::Byte(0xa1);
static constexpr System::Byte PDUGetResponse = System::Byte(0xa2);
static constexpr System::Byte PDUSetRequest = System::Byte(0xa3);
static constexpr System::Byte PDUTrap = System::Byte(0xa4);
static constexpr System::Int8 ENoError = System::Int8(0x0);
static constexpr System::Int8 ETooBig = System::Int8(0x1);
static constexpr System::Int8 ENoSuchName = System::Int8(0x2);
static constexpr System::Int8 EBadValue = System::Int8(0x3);
static constexpr System::Int8 EReadOnly = System::Int8(0x4);
static constexpr System::Int8 EGenErr = System::Int8(0x5);
}	/* namespace Idsnmp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSNMP)
using namespace Idsnmp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsnmpHPP
