// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.Bluetooth.pas' rev: 34.00 (Windows)

#ifndef System_Win_BluetoothHPP
#define System_Win_BluetoothHPP

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
namespace Bluetooth
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformBluetoothClassicManager;
class DELPHICLASS TPlatformBluetoothLEManager;
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


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Bluetooth */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_BLUETOOTH)
using namespace System::Win::Bluetooth;
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
#endif	// System_Win_BluetoothHPP
