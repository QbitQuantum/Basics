// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.PhoneDialer.pas' rev: 34.00 (Android)

#ifndef Fmx_PhonedialerHPP
#define Fmx_PhonedialerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------
namespace Fmx
{
namespace Phonedialer
{
  _INIT_UNIT(Fmx_Phonedialer);
}	/* namespace Phonedialer */
}	/* namespace Fmx */

namespace Fmx
{
namespace Phonedialer
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCarrier;
struct TCallStateHelper /* Helper for enum 'TCallState' */;
class DELPHICLASS TCall;
__interface DELPHIINTERFACE IFMXPhoneDialerService;
typedef System::DelphiInterface<IFMXPhoneDialerService> _di_IFMXPhoneDialerService;
class DELPHICLASS TPhoneDialerService;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TOnCarrierChanged)(TCarrier* ACarrier);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCarrier : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TOnCarrierChanged FOnCarrierChanged;
	
protected:
	virtual void __fastcall DoCarrierChanged(TCarrier* const ACarrier);
	
public:
	virtual System::UnicodeString __fastcall GetIsoCountryCode() = 0 ;
	virtual System::UnicodeString __fastcall GetMobileCountryCode() = 0 ;
	virtual System::UnicodeString __fastcall GetMobileNetwork() = 0 ;
	virtual System::UnicodeString __fastcall GetCarrierName() = 0 ;
	__property TOnCarrierChanged OnCarrierChanged = {read=FOnCarrierChanged, write=FOnCarrierChanged};
public:
	/* TObject.Create */ inline __fastcall TCarrier() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCarrier() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum class DECLSPEC_DENUM TCallState : unsigned char { None, Connected, Incoming, Dialing, Disconnected, csNone _DEPRECATED_ATTRIBUTE3("Use TCallState.None")  = 0, csConnected _DEPRECATED_ATTRIBUTE3("Use TCallState.Connected")  = 1, csIncoming _DEPRECATED_ATTRIBUTE3("Use TCallState.Incoming")  = 2, csDialing _DEPRECATED_ATTRIBUTE3("Use TCallState.Dialing")  = 3, csDisconnected _DEPRECATED_ATTRIBUTE3("Use TCallState.Disconnected")  = 4 };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCall : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual TCallState __fastcall GetCallState() = 0 ;
	virtual System::UnicodeString __fastcall GetCallID() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TCall() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCall() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<TCall*> TCalls;

typedef void __fastcall (__closure *TOnCallStateChanged)(const System::UnicodeString ACallID, const TCallState AState);

__interface  INTERFACE_UUID("{61EE0E7A-7643-4966-873E-384CF798E694}") IFMXPhoneDialerService  : public System::IInterface 
{
	virtual bool __fastcall Call(const System::UnicodeString APhoneNumber) = 0 ;
	virtual TCarrier* __fastcall GetCarrier() = 0 ;
	virtual TCalls __fastcall GetCurrentCalls() = 0 ;
	virtual TOnCallStateChanged __fastcall GetOnCallStateChanged() = 0 ;
	virtual void __fastcall SetOnCallStateChanged(const TOnCallStateChanged AEvent) = 0 ;
	__property TOnCallStateChanged OnCallStateChanged = {read=GetOnCallStateChanged, write=SetOnCallStateChanged};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPhoneDialerService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	TOnCallStateChanged FOnCallStateChanged;
	TOnCallStateChanged __fastcall GetOnCallStateChanged();
	void __fastcall SetOnCallStateChanged(const TOnCallStateChanged AEvent);
	
protected:
	virtual void __fastcall DoCallStateChanged(const System::UnicodeString ACallID, const TCallState AState);
	
public:
	virtual bool __fastcall Call(const System::UnicodeString APhoneNumber) = 0 ;
	virtual TCarrier* __fastcall GetCarrier() = 0 ;
	virtual TCalls __fastcall GetCurrentCalls() = 0 ;
	__property TOnCallStateChanged OnCallStateChanged = {read=GetOnCallStateChanged, write=SetOnCallStateChanged};
public:
	/* TObject.Create */ inline __fastcall TPhoneDialerService() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPhoneDialerService() { }
	
private:
	void *__IFMXPhoneDialerService;	// IFMXPhoneDialerService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {61EE0E7A-7643-4966-873E-384CF798E694}
	operator _di_IFMXPhoneDialerService()
	{
		_di_IFMXPhoneDialerService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFMXPhoneDialerService*(void) { return (IFMXPhoneDialerService*)&__IFMXPhoneDialerService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Phonedialer */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PHONEDIALER)
using namespace Fmx::Phonedialer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_PhonedialerHPP
