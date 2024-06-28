// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.BluetoothWinRT.pas' rev: 34.00 (Windows)

#ifndef System_Win_BluetoothwinrtHPP
#define System_Win_BluetoothwinrtHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Bluetooth.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Win
{
namespace Bluetoothwinrt
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformWinRTBluetoothLEManager;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPlatformWinRTBluetoothLEManager : public System::Bluetooth::TBluetoothLEManager
{
	typedef System::Bluetooth::TBluetoothLEManager inherited;
	
public:
	__classmethod virtual System::Bluetooth::TBluetoothLEManager* __fastcall GetBluetoothManager();
public:
	/* TBluetoothLEManager.Create */ inline __fastcall TPlatformWinRTBluetoothLEManager() : System::Bluetooth::TBluetoothLEManager() { }
	/* TBluetoothLEManager.Destroy */ inline __fastcall virtual ~TPlatformWinRTBluetoothLEManager() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Bluetoothwinrt */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_BLUETOOTHWINRT)
using namespace System::Win::Bluetoothwinrt;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN)
using namespace System::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Win_BluetoothwinrtHPP
