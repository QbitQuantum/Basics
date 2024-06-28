// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdNetworkCalculator.pas' rev: 34.00 (Android)

#ifndef IdnetworkcalculatorHPP
#define IdnetworkcalculatorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdBaseComponent.hpp>
#include <IdStruct.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idnetworkcalculator
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIpProperty;
class DELPHICLASS TIdNetworkCalculator;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TNetworkClass : unsigned char { ID_NET_CLASS_A, ID_NET_CLASS_B, ID_NET_CLASS_C, ID_NET_CLASS_D, ID_NET_CLASS_E };

enum DECLSPEC_DENUM TIdIPAddressType : unsigned char { IPLocalHost, IPLocalNetwork, IPReserved, IPInternetHost, IPPrivateNetwork, IPLoopback, IPMulticast, IPFutureUse, IPGlobalBroadcast };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIpProperty : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	bool FReadOnly;
	System::StaticArray<bool, 32> FBitArray;
	System::StaticArray<System::Byte, 4> FValue;
	System::Classes::TNotifyEvent FOnChange;
	TIdIPAddressType __fastcall GetAddressType();
	System::UnicodeString __fastcall GetAsBinaryString();
	unsigned __fastcall GetAsDoubleWord();
	System::UnicodeString __fastcall GetAsString();
	bool __fastcall GetBit(System::Byte Index);
	System::Byte __fastcall GetByte(int Index);
	void __fastcall SetAsBinaryString(const System::UnicodeString Value);
	void __fastcall SetAsDoubleWord(const unsigned Value);
	void __fastcall SetAsString(const System::UnicodeString Value);
	void __fastcall SetBit(System::Byte Index, const bool Value);
	void __fastcall SetByte(int Index, const System::Byte Value);
	__property bool IsReadOnly = {read=FReadOnly, write=FReadOnly, default=0};
	
public:
	__fastcall virtual TIpProperty();
	__fastcall virtual ~TIpProperty();
	virtual void __fastcall SetAll(System::Byte One, System::Byte Two, System::Byte Three, System::Byte Four);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property bool Bits[System::Byte Index] = {read=GetBit, write=SetBit};
	__property TIdIPAddressType AddressType = {read=GetAddressType, nodefault};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
__published:
	__property System::Byte Byte1 = {read=GetByte, write=SetByte, stored=false, index=0, nodefault};
	__property System::Byte Byte2 = {read=GetByte, write=SetByte, stored=false, index=1, nodefault};
	__property System::Byte Byte3 = {read=GetByte, write=SetByte, stored=false, index=2, nodefault};
	__property System::Byte Byte4 = {read=GetByte, write=SetByte, stored=false, index=3, nodefault};
	__property unsigned AsDoubleWord = {read=GetAsDoubleWord, write=SetAsDoubleWord, stored=false, nodefault};
	__property System::UnicodeString AsBinaryString = {read=GetAsBinaryString, write=SetAsBinaryString, stored=false};
	__property System::UnicodeString AsString = {read=GetAsString, write=SetAsString};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdNetworkCalculator : public Idbasecomponent::TIdBaseComponent
{
	typedef Idbasecomponent::TIdBaseComponent inherited;
	
protected:
	System::Classes::TStrings* FListIP;
	unsigned FNetworkMaskLength;
	TIpProperty* FNetworkMask;
	TIpProperty* FNetworkAddress;
	TNetworkClass FNetworkClass;
	System::Classes::TNotifyEvent FOnChange;
	System::Classes::TNotifyEvent FOnGenIPList;
	void __fastcall FillIPList();
	System::UnicodeString __fastcall GetNetworkClassAsString();
	bool __fastcall GetIsAddressRoutable();
	System::Classes::TStrings* __fastcall GetListIP();
	void __fastcall SetNetworkAddress(TIpProperty* const Value);
	void __fastcall SetNetworkMask(TIpProperty* const Value);
	void __fastcall SetNetworkMaskLength(const unsigned Value);
	void __fastcall NetMaskChanged(System::TObject* Sender);
	void __fastcall NetAddressChanged(System::TObject* Sender);
	virtual void __fastcall InitComponent();
	
public:
	__fastcall virtual ~TIdNetworkCalculator();
	bool __fastcall IsAddressInNetwork(const System::UnicodeString Address);
	unsigned __fastcall NumIP();
	System::UnicodeString __fastcall StartIP();
	System::UnicodeString __fastcall EndIP();
	__property System::Classes::TStrings* ListIP = {read=GetListIP};
	__property TNetworkClass NetworkClass = {read=FNetworkClass, nodefault};
	__property System::UnicodeString NetworkClassAsString = {read=GetNetworkClassAsString};
	__property bool IsAddressRoutable = {read=GetIsAddressRoutable, nodefault};
	
__published:
	__property TIpProperty* NetworkAddress = {read=FNetworkAddress, write=SetNetworkAddress};
	__property TIpProperty* NetworkMask = {read=FNetworkMask, write=SetNetworkMask};
	__property unsigned NetworkMaskLength = {read=FNetworkMaskLength, write=SetNetworkMaskLength, default=32};
	__property System::Classes::TNotifyEvent OnGenIPList = {read=FOnGenIPList, write=FOnGenIPList};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdNetworkCalculator(System::Classes::TComponent* AOwner)/* overload */ : Idbasecomponent::TIdBaseComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdNetworkCalculator()/* overload */ : Idbasecomponent::TIdBaseComponent() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 ID_NC_MASK_LENGTH = System::Int8(0x20);
static const TNetworkClass ID_NETWORKCLASS = (TNetworkClass)(0);
}	/* namespace Idnetworkcalculator */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDNETWORKCALCULATOR)
using namespace Idnetworkcalculator;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdnetworkcalculatorHPP
