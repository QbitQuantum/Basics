// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Bluetooth.pas' rev: 34.00 (Windows)

#ifndef Winapi_BluetoothHPP
#define Winapi_BluetoothHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <bthsdpdef.h>
#include <bthdef.h>
#include <bluetoothapis.h>
#include <ws2bth.h>

namespace Winapi
{
namespace Bluetooth
{
//-- forward type declarations -----------------------------------------------
struct SdpQueryUuidUnion;
struct _BLUETOOTH_LOCAL_SERVICE_INFO;
struct TSpdElementDataString;
struct TSpdElementDataUrl;
struct TSpdElementDataSequence;
struct TSpdElementDataAlternative;
//-- type declarations -------------------------------------------------------
typedef SDP_LARGE_INTEGER_16 TSdpLargeInteger;

typedef SDP_LARGE_INTEGER_16 *PSdpLargeInteger;

typedef SDP_ULARGE_INTEGER_16 TSdpULargeInteger16;

typedef SDP_ULARGE_INTEGER_16 *PSdpULargeInteger16;

enum DECLSPEC_DENUM NodeContainerType : unsigned int { NodeContainerTypeSequence, NodeContainerTypeAlternative };

typedef NodeContainerType TNodeContainerType;

typedef System::Word TSdpError;

typedef System::Word *PSdpError;

typedef SDP_TYPE TSdpType;

typedef SDP_SPECIFICTYPE TSdpSpecificType;

typedef _SdpAttributeRange TSdpAttributeRange;

struct DECLSPEC_DRECORD SdpQueryUuidUnion
{
	
public:
	union
	{
		struct 
		{
			System::Word uuid16;
		};
		struct 
		{
			unsigned uuid32;
		};
		struct 
		{
			GUID uuid128;
		};
		
	};
};


typedef SdpQueryUuidUnion TSdpQueryUuidUnion;

typedef _SdpQueryUuid TSdpQueryUuid;

typedef _BTH_DEVICE_INFO TBthDeviceInfo;

typedef _BTH_DEVICE_INFO *PBthDeviceInfo;

typedef _BTH_RADIO_IN_RANGE TBthRadioInRange;

typedef PBTH_RADIO_IN_RANGE PBthRadioInRange;

typedef _BTH_L2CAP_EVENT_INFO TBthL2CapEventInfo;

typedef _BTH_L2CAP_EVENT_INFO *PBthL2CapEventInfo;

typedef _BTH_HCI_EVENT_INFO TBthHciEventInfo;

typedef _BTH_HCI_EVENT_INFO *PBthHciEventInfo;

typedef _AUTHENTICATION_REQUIREMENTS TAuthenticationRequirements;

typedef _SOCKADDR_BTH TSockAddrBth;

typedef _SOCKADDR_BTH *PSockAddrBth;

typedef _BTH_SET_SERVICE TBthSetService;

typedef _BTH_SET_SERVICE *PBthSetService;

typedef _BTH_QUERY_DEVICE TBthQueryDevice;

typedef _BTH_QUERY_DEVICE *PBthQueryDevice;

typedef _BTH_QUERY_SERVICE TBthQueryService;

typedef _BTH_QUERY_SERVICE *PBthQueryService;

typedef _RFCOMM_MSC_DATA TRfCommMscData;

typedef _RFCOMM_MSC_DATA *PRfCommMscData;

typedef _RFCOMM_RLS_DATA TRfCommRlsData;

typedef _RFCOMM_RLS_DATA *PRfCommRlsData;

typedef _RFCOMM_RPN_DATA TRfCommRpnData;

typedef _RFCOMM_RPN_DATA *PRfCommRpnData;

typedef _RFCOMM_COMMAND TRfCommCommand;

typedef _RFCOMM_COMMAND *PRfCommCommand;

typedef _BTH_PING_REQ TBthPingReq;

typedef _BTH_PING_REQ *PBthPingReq;

typedef _BTH_PING_RSP TBthPingRsp;

typedef _BTH_PING_RSP *PBthPingRsp;

typedef _BTH_INFO_REQ TBthInfoReq;

typedef _BTH_INFO_REQ *PBthInfoReq;

typedef _BTH_INFO_RSP TBthInfoRsp;

typedef _BTH_INFO_RSP *PBthInfoRsp;

typedef _BTH_SET_SERVICE *PBTHNS_SETBLOB;

typedef _BTH_SET_SERVICE TBthnsSetblob;

typedef _BTH_SET_SERVICE *PBthnsSetblob;

typedef _BTH_QUERY_DEVICE TBthnsInquiryblob;

typedef _BTH_QUERY_DEVICE *PBthnsInquiryblob;

typedef _BTH_QUERY_SERVICE TBthnsRestrictionblob;

typedef _BTH_QUERY_SERVICE *PBthnsRestrictionblob;

typedef _BLUETOOTH_ADDRESS TBluetoothAddress;

typedef _BLUETOOTH_ADDRESS *PBluetoothAddress;

struct DECLSPEC_DRECORD _BLUETOOTH_LOCAL_SERVICE_INFO
{
public:
	System::LongBool Enabled;
	_BLUETOOTH_ADDRESS btAddr;
	System::StaticArray<System::WideChar, 248> szName;
	System::StaticArray<System::WideChar, 248> szDeviceString;
};


typedef _BLUETOOTH_LOCAL_SERVICE_INFO TBluetoothLocalServiceInfo;

typedef _BLUETOOTH_LOCAL_SERVICE_INFO *PBluetoothLocalServiceInfo;

typedef _BLUETOOTH_FIND_RADIO_PARAMS TBluetoothFindRadioParams;

typedef _BLUETOOTH_FIND_RADIO_PARAMS *PBluetoothFindRadioParams;

typedef NativeUInt TBluetoothRadioFind;

typedef _BLUETOOTH_RADIO_INFO TBluetoothRadioInfo;

typedef _BLUETOOTH_RADIO_INFO *PTBluetoothRadioInfo;

typedef _BLUETOOTH_DEVICE_INFO TBluetoothDeviceInfo;

typedef _BLUETOOTH_DEVICE_INFO *PBluetoothDeviceInfo;

typedef _BLUETOOTH_AUTHENTICATION_METHOD *PBLUETOOTH_AUTHENTICATION_METHOD;

typedef _BLUETOOTH_AUTHENTICATION_METHOD TBluetoothAuthenticationMethod;

typedef _BLUETOOTH_AUTHENTICATION_METHOD *PBluetoothAuthenticationMethod;

typedef _BLUETOOTH_IO_CAPABILITY BLUETOOTH_IO_CAPABILITY;

typedef _BLUETOOTH_IO_CAPABILITY TBluetoothIOCapability;

typedef _BLUETOOTH_IO_CAPABILITY *PBluetoothIOCapability;

typedef _BLUETOOTH_AUTHENTICATION_REQUIREMENTS TBluetoothAuthenticationRequirements;

typedef _BLUETOOTH_AUTHENTICATION_REQUIREMENTS *PBluetoothAuthenticationRequirements;

typedef _BLUETOOTH_AUTHENTICATION_CALLBACK_PARAMS TBluetoothAuthenticationCallbackParams;

typedef _BLUETOOTH_DEVICE_SEARCH_PARAMS *PBLUETOOTH_DEVICE_SEARCH_PARAMS;

typedef _BLUETOOTH_DEVICE_SEARCH_PARAMS TBluetoothDeviceSearchParams;

typedef _BLUETOOTH_DEVICE_SEARCH_PARAMS *PBluetoothDeviceSearchParams;

typedef NativeUInt TBluetoothDeviceFind;

typedef _BLUETOOTH_COD_PAIRS TBluetoothCodPairs;

typedef _BLUETOOTH_COD_PAIRS *PBluetoothCodPairs;

typedef PFN_DEVICE_CALLBACK TDeviceCallback;

typedef _BLUETOOTH_SELECT_DEVICE_PARAMS TBluetoothSelectDeviceParams;

typedef _BLUETOOTH_SELECT_DEVICE_PARAMS *PBluetoothSelectDeviceParams;

typedef _BLUETOOTH_PIN_INFO TBluetoothPinInfo;

typedef _BLUETOOTH_PIN_INFO *PBluetoothPinInfo;

typedef _BLUETOOTH_OOB_DATA_INFO *PBLUETOOTH_OOB_DATA_INFO;

typedef _BLUETOOTH_PIN_INFO TBluetoothOOBDataInfo;

typedef _BLUETOOTH_PIN_INFO *PBluetoothOOBDataInfo;

typedef _BLUETOOTH_NUMERIC_COMPARISON_INFO TBluetoothNumericComparisonInfo;

typedef _BLUETOOTH_NUMERIC_COMPARISON_INFO *PBluetoothNumericComparisonInfo;

typedef _BLUETOOTH_PASSKEY_INFO TBluetoothPassKeyInfo;

typedef _BLUETOOTH_PASSKEY_INFO *PBluetoothPassKeyInfo;

struct DECLSPEC_DRECORD TSpdElementDataString
{
public:
	System::Byte *value;
	unsigned length;
};


struct DECLSPEC_DRECORD TSpdElementDataUrl
{
public:
	System::Byte *value;
	unsigned length;
};


struct DECLSPEC_DRECORD TSpdElementDataSequence
{
public:
	System::Byte *value;
	unsigned length;
};


struct DECLSPEC_DRECORD TSpdElementDataAlternative
{
public:
	System::Byte *value;
	unsigned length;
};


typedef _SDP_ELEMENT_DATA TSdpElementData;

typedef _SDP_ELEMENT_DATA *PSdpElementData;

typedef _SDP_STRING_TYPE_DATA TSdpStringTypeData;

typedef _SDP_STRING_TYPE_DATA *PSdpStringTypeData;

typedef PFN_BLUETOOTH_ENUM_ATTRIBUTES_CALLBACK TBluetoothEnumAttributesCallback;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE GUID GUID_BLUETOOTH_HCI_VENDOR_EVENT;
extern DELPHI_PACKAGE GUID AVRemoteControlControllerServiceClass_UUID;
static const int _IOC_OUT = int(0x40000000);
static const unsigned _IOC_IN = unsigned(0x80000000);
static const unsigned _IOC_INOUT = unsigned(0xc0000000);
static const int _IOC_VENDOR = int(0x18000000);
}	/* namespace Bluetooth */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_BLUETOOTH)
using namespace Winapi::Bluetooth;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_BluetoothHPP
