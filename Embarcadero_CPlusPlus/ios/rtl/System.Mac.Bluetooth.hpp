// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Mac.Bluetooth.pas' rev: 34.00 (iOS)

#ifndef System_Mac_BluetoothHPP
#define System_Mac_BluetoothHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Bluetooth.hpp>
#include <Macapi.Bluetooth.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Mac
{
namespace Bluetooth
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformBluetoothLEManager;
class DELPHICLASS TBluetoothLEManagerHelper;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPlatformBluetoothLEManager : public System::Bluetooth::TBluetoothLEManager
{
	typedef System::Bluetooth::TBluetoothLEManager inherited;
	
protected:
	__classmethod virtual System::Bluetooth::TBluetoothLEManager* __fastcall GetBluetoothManager();
public:
	/* TBluetoothLEManager.Create */ inline __fastcall TPlatformBluetoothLEManager() : System::Bluetooth::TBluetoothLEManager() { }
	/* TBluetoothLEManager.Destroy */ inline __fastcall virtual ~TPlatformBluetoothLEManager() { }
	
};


typedef void __fastcall (__closure *TBluetoothLEManagerStateChangedEvent)(Macapi::Bluetooth::CBCentralManagerState AManagerState);

class PASCALIMPLEMENTATION TBluetoothLEManagerHelper : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TBluetoothLEManagerStateChangedEvent FOnManagerStateChanged;
	static TBluetoothLEManagerHelper* FCurrent;
	
private:
	void __fastcall NotifyManagerStateChange(Macapi::Bluetooth::CBCentralManagerState AManagerState);
	
public:
	__classmethod void __fastcall CreateCurrent();
	__classmethod void __fastcall DestroyCurrent();
	__property TBluetoothLEManagerStateChangedEvent OnManagerStateChanged = {read=FOnManagerStateChanged, write=FOnManagerStateChanged};
	/* static */ __property TBluetoothLEManagerHelper* Current = {read=FCurrent};
public:
	/* TObject.Create */ inline __fastcall TBluetoothLEManagerHelper() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBluetoothLEManagerHelper() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Bluetooth */
}	/* namespace Mac */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_MAC_BLUETOOTH)
using namespace System::Mac::Bluetooth;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_MAC)
using namespace System::Mac;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Mac_BluetoothHPP
