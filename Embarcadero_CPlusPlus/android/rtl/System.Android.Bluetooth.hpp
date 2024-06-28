// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Android.Bluetooth.pas' rev: 34.00 (Android)

#ifndef System_Android_BluetoothHPP
#define System_Android_BluetoothHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Bluetooth.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Android
{
namespace Bluetooth
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformBluetoothClassicManager;
class DELPHICLASS TPlatformBluetoothLEManager;
__interface DELPHIINTERFACE IScanSettingsOptions;
typedef System::DelphiInterface<IScanSettingsOptions> _di_IScanSettingsOptions;
__interface DELPHIINTERFACE IExtraBLEAndroidProperties;
typedef System::DelphiInterface<IExtraBLEAndroidProperties> _di_IExtraBLEAndroidProperties;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPlatformBluetoothClassicManager : public System::Bluetooth::TBluetoothManager
{
	typedef System::Bluetooth::TBluetoothManager inherited;
	
protected:
	__classmethod virtual System::Bluetooth::TBluetoothManager* __fastcall GetBluetoothManager();
public:
	/* TBluetoothManager.Create */ inline __fastcall TPlatformBluetoothClassicManager() : System::Bluetooth::TBluetoothManager() { }
	/* TBluetoothManager.Destroy */ inline __fastcall virtual ~TPlatformBluetoothClassicManager() { }
	
};


class PASCALIMPLEMENTATION TPlatformBluetoothLEManager : public System::Bluetooth::TBluetoothLEManager
{
	typedef System::Bluetooth::TBluetoothLEManager inherited;
	
protected:
	__classmethod virtual System::Bluetooth::TBluetoothLEManager* __fastcall GetBluetoothManager();
public:
	/* TBluetoothLEManager.Create */ inline __fastcall TPlatformBluetoothLEManager() : System::Bluetooth::TBluetoothLEManager() { }
	/* TBluetoothLEManager.Destroy */ inline __fastcall virtual ~TPlatformBluetoothLEManager() { }
	
};


__interface  INTERFACE_UUID("{353170C7-B913-4FF9-A0E6-C5825A9BAC71}") IScanSettingsOptions  : public System::IInterface 
{
	virtual int __fastcall GetCALLBACK_TYPE_ALL_MATCHES() = 0 ;
	virtual int __fastcall GetCALLBACK_TYPE_FIRST_MATCH() = 0 ;
	virtual int __fastcall GetCALLBACK_TYPE_MATCH_LOST() = 0 ;
	virtual int __fastcall GetMATCH_MODE_AGGRESSIVE() = 0 ;
	virtual int __fastcall GetMATCH_MODE_STICKY() = 0 ;
	virtual int __fastcall GetMATCH_NUM_FEW_ADVERTISEMENT() = 0 ;
	virtual int __fastcall GetMATCH_NUM_MAX_ADVERTISEMENT() = 0 ;
	virtual int __fastcall GetMATCH_NUM_ONE_ADVERTISEMENT() = 0 ;
	virtual int __fastcall GetSCAN_MODE_BALANCED() = 0 ;
	virtual int __fastcall GetSCAN_MODE_LOW_LATENCY() = 0 ;
	virtual int __fastcall GetSCAN_MODE_LOW_POWER() = 0 ;
	virtual int __fastcall GetSCAN_MODE_OPPORTUNISTIC() = 0 ;
	__property int CALLBACK_TYPE_ALL_MATCHES = {read=GetCALLBACK_TYPE_ALL_MATCHES};
	__property int CALLBACK_TYPE_FIRST_MATCH = {read=GetCALLBACK_TYPE_FIRST_MATCH};
	__property int CALLBACK_TYPE_MATCH_LOST = {read=GetCALLBACK_TYPE_MATCH_LOST};
	__property int MATCH_MODE_AGGRESSIVE = {read=GetMATCH_MODE_AGGRESSIVE};
	__property int MATCH_MODE_STICKY = {read=GetMATCH_MODE_STICKY};
	__property int MATCH_NUM_FEW_ADVERTISEMENT = {read=GetMATCH_NUM_FEW_ADVERTISEMENT};
	__property int MATCH_NUM_MAX_ADVERTISEMENT = {read=GetMATCH_NUM_MAX_ADVERTISEMENT};
	__property int MATCH_NUM_ONE_ADVERTISEMENT = {read=GetMATCH_NUM_ONE_ADVERTISEMENT};
	__property int SCAN_MODE_BALANCED = {read=GetSCAN_MODE_BALANCED};
	__property int SCAN_MODE_LOW_LATENCY = {read=GetSCAN_MODE_LOW_LATENCY};
	__property int SCAN_MODE_LOW_POWER = {read=GetSCAN_MODE_LOW_POWER};
	__property int SCAN_MODE_OPPORTUNISTIC = {read=GetSCAN_MODE_OPPORTUNISTIC};
};

__interface  INTERFACE_UUID("{C14C69E8-C51B-4CF8-839B-FDE9CB96F15D}") IExtraBLEAndroidProperties  : public System::IInterface 
{
	virtual _di_IScanSettingsOptions __fastcall GetScanSettingsOptions() = 0 ;
	virtual int __fastcall GetScanSettings() = 0 ;
	virtual void __fastcall SetScanSettings(int Value) = 0 ;
	__property _di_IScanSettingsOptions ScanSettingsOptions = {read=GetScanSettingsOptions};
	__property int ScanSettings = {read=GetScanSettings, write=SetScanSettings};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Bluetooth */
}	/* namespace Android */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANDROID_BLUETOOTH)
using namespace System::Android::Bluetooth;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANDROID)
using namespace System::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Android_BluetoothHPP
