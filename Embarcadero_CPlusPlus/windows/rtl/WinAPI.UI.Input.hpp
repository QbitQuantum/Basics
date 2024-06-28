// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.UI.Input.pas' rev: 34.00 (Windows)

#ifndef Winapi_Ui_InputHPP
#define Winapi_Ui_InputHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Types.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.Devices.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Ui
{
namespace Input
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IIterator_1__IPointerPoint_Base;
typedef System::DelphiInterface<IIterator_1__IPointerPoint_Base> _di_IIterator_1__IPointerPoint_Base;
__interface DELPHIINTERFACE IIterator_1__IPointerPoint;
typedef System::DelphiInterface<IIterator_1__IPointerPoint> _di_IIterator_1__IPointerPoint;
__interface DELPHIINTERFACE IIterable_1__IPointerPoint_Base;
typedef System::DelphiInterface<IIterable_1__IPointerPoint_Base> _di_IIterable_1__IPointerPoint_Base;
__interface DELPHIINTERFACE IIterable_1__IPointerPoint;
typedef System::DelphiInterface<IIterable_1__IPointerPoint> _di_IIterable_1__IPointerPoint;
__interface DELPHIINTERFACE IIterator_1__IRadialControllerMenuItem_Base;
typedef System::DelphiInterface<IIterator_1__IRadialControllerMenuItem_Base> _di_IIterator_1__IRadialControllerMenuItem_Base;
__interface DELPHIINTERFACE IIterator_1__IRadialControllerMenuItem;
typedef System::DelphiInterface<IIterator_1__IRadialControllerMenuItem> _di_IIterator_1__IRadialControllerMenuItem;
__interface DELPHIINTERFACE IIterable_1__IRadialControllerMenuItem_Base;
typedef System::DelphiInterface<IIterable_1__IRadialControllerMenuItem_Base> _di_IIterable_1__IRadialControllerMenuItem_Base;
__interface DELPHIINTERFACE IIterable_1__IRadialControllerMenuItem;
typedef System::DelphiInterface<IIterable_1__IRadialControllerMenuItem> _di_IIterable_1__IRadialControllerMenuItem;
__interface DELPHIINTERFACE Core_IRadialControllerIndependentInputSource;
typedef System::DelphiInterface<Core_IRadialControllerIndependentInputSource> _di_Core_IRadialControllerIndependentInputSource;
__interface DELPHIINTERFACE Core_IRadialControllerIndependentInputSourceStatics;
typedef System::DelphiInterface<Core_IRadialControllerIndependentInputSourceStatics> _di_Core_IRadialControllerIndependentInputSourceStatics;
__interface DELPHIINTERFACE IPointerPointTransform;
typedef System::DelphiInterface<IPointerPointTransform> _di_IPointerPointTransform;
__interface DELPHIINTERFACE IRadialControllerRotationChangedEventArgs2;
typedef System::DelphiInterface<IRadialControllerRotationChangedEventArgs2> _di_IRadialControllerRotationChangedEventArgs2;
__interface DELPHIINTERFACE IRadialControllerButtonPressedEventArgs;
typedef System::DelphiInterface<IRadialControllerButtonPressedEventArgs> _di_IRadialControllerButtonPressedEventArgs;
__interface DELPHIINTERFACE IRadialControllerButtonHoldingEventArgs;
typedef System::DelphiInterface<IRadialControllerButtonHoldingEventArgs> _di_IRadialControllerButtonHoldingEventArgs;
__interface DELPHIINTERFACE IRadialControllerButtonReleasedEventArgs;
typedef System::DelphiInterface<IRadialControllerButtonReleasedEventArgs> _di_IRadialControllerButtonReleasedEventArgs;
__interface DELPHIINTERFACE IRadialControllerScreenContactStartedEventArgs2;
typedef System::DelphiInterface<IRadialControllerScreenContactStartedEventArgs2> _di_IRadialControllerScreenContactStartedEventArgs2;
__interface DELPHIINTERFACE IRadialControllerScreenContactContinuedEventArgs2;
typedef System::DelphiInterface<IRadialControllerScreenContactContinuedEventArgs2> _di_IRadialControllerScreenContactContinuedEventArgs2;
__interface DELPHIINTERFACE IRadialControllerScreenContactEndedEventArgs;
typedef System::DelphiInterface<IRadialControllerScreenContactEndedEventArgs> _di_IRadialControllerScreenContactEndedEventArgs;
__interface DELPHIINTERFACE IRadialControllerButtonClickedEventArgs2;
typedef System::DelphiInterface<IRadialControllerButtonClickedEventArgs2> _di_IRadialControllerButtonClickedEventArgs2;
__interface DELPHIINTERFACE IRadialControllerControlAcquiredEventArgs2;
typedef System::DelphiInterface<IRadialControllerControlAcquiredEventArgs2> _di_IRadialControllerControlAcquiredEventArgs2;
__interface DELPHIINTERFACE TypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs> _di_TypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs_Delegate_Base> _di_TypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs> _di_TypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs> _di_TypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs;
__interface DELPHIINTERFACE IRadialController2;
typedef System::DelphiInterface<IRadialController2> _di_IRadialController2;
__interface DELPHIINTERFACE IRadialControllerStatics;
typedef System::DelphiInterface<IRadialControllerStatics> _di_IRadialControllerStatics;
__interface DELPHIINTERFACE IRadialControllerMenuItemStatics;
typedef System::DelphiInterface<IRadialControllerMenuItemStatics> _di_IRadialControllerMenuItemStatics;
__interface DELPHIINTERFACE IRadialControllerMenuItemStatics2;
typedef System::DelphiInterface<IRadialControllerMenuItemStatics2> _di_IRadialControllerMenuItemStatics2;
__interface DELPHIINTERFACE IIterator_1__RadialControllerSystemMenuItemKind_Base;
typedef System::DelphiInterface<IIterator_1__RadialControllerSystemMenuItemKind_Base> _di_IIterator_1__RadialControllerSystemMenuItemKind_Base;
__interface DELPHIINTERFACE IIterator_1__RadialControllerSystemMenuItemKind;
typedef System::DelphiInterface<IIterator_1__RadialControllerSystemMenuItemKind> _di_IIterator_1__RadialControllerSystemMenuItemKind;
__interface DELPHIINTERFACE IIterable_1__RadialControllerSystemMenuItemKind_Base;
typedef System::DelphiInterface<IIterable_1__RadialControllerSystemMenuItemKind_Base> _di_IIterable_1__RadialControllerSystemMenuItemKind_Base;
__interface DELPHIINTERFACE IIterable_1__RadialControllerSystemMenuItemKind;
typedef System::DelphiInterface<IIterable_1__RadialControllerSystemMenuItemKind> _di_IIterable_1__RadialControllerSystemMenuItemKind;
__interface DELPHIINTERFACE IRadialControllerConfiguration;
typedef System::DelphiInterface<IRadialControllerConfiguration> _di_IRadialControllerConfiguration;
__interface DELPHIINTERFACE IRadialControllerConfigurationStatics;
typedef System::DelphiInterface<IRadialControllerConfigurationStatics> _di_IRadialControllerConfigurationStatics;
__interface DELPHIINTERFACE IRadialControllerConfiguration2;
typedef System::DelphiInterface<IRadialControllerConfiguration2> _di_IRadialControllerConfiguration2;
__interface DELPHIINTERFACE IRadialControllerConfigurationStatics2;
typedef System::DelphiInterface<IRadialControllerConfigurationStatics2> _di_IRadialControllerConfigurationStatics2;
class DELPHICLASS TCore_RadialControllerIndependentInputSource;
class DELPHICLASS TRadialController;
class DELPHICLASS TRadialControllerMenuItem;
class DELPHICLASS TRadialControllerConfiguration;
//-- type declarations -------------------------------------------------------
typedef _di_IIterator_1__IPointerPoint *PIIterator_1__IPointerPoint;

typedef _di_IIterable_1__IPointerPoint *PIIterable_1__IPointerPoint;

typedef _di_IIterator_1__IRadialControllerMenuItem *PIIterator_1__IRadialControllerMenuItem;

typedef _di_IIterable_1__IRadialControllerMenuItem *PIIterable_1__IRadialControllerMenuItem;

typedef _di_Core_IRadialControllerIndependentInputSource *PCore_IRadialControllerIndependentInputSource;

typedef _di_Core_IRadialControllerIndependentInputSourceStatics *PCore_IRadialControllerIndependentInputSourceStatics;

typedef _di_IPointerPointTransform *PIPointerPointTransform;

typedef _di_IRadialControllerRotationChangedEventArgs2 *PIRadialControllerRotationChangedEventArgs2;

typedef _di_IRadialControllerButtonPressedEventArgs *PIRadialControllerButtonPressedEventArgs;

typedef _di_IRadialControllerButtonHoldingEventArgs *PIRadialControllerButtonHoldingEventArgs;

typedef _di_IRadialControllerButtonReleasedEventArgs *PIRadialControllerButtonReleasedEventArgs;

typedef _di_IRadialControllerScreenContactStartedEventArgs2 *PIRadialControllerScreenContactStartedEventArgs2;

typedef _di_IRadialControllerScreenContactContinuedEventArgs2 *PIRadialControllerScreenContactContinuedEventArgs2;

typedef _di_IRadialControllerScreenContactEndedEventArgs *PIRadialControllerScreenContactEndedEventArgs;

typedef _di_IRadialControllerButtonClickedEventArgs2 *PIRadialControllerButtonClickedEventArgs2;

typedef _di_IRadialControllerControlAcquiredEventArgs2 *PIRadialControllerControlAcquiredEventArgs2;

typedef _di_TypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs *PTypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs;

typedef _di_TypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs *PTypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs;

typedef _di_TypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs *PTypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs;

typedef _di_IRadialController2 *PIRadialController2;

typedef _di_IRadialControllerStatics *PIRadialControllerStatics;

typedef _di_IRadialControllerMenuItemStatics *PIRadialControllerMenuItemStatics;

typedef _di_IRadialControllerMenuItemStatics2 *PIRadialControllerMenuItemStatics2;

typedef _di_IIterator_1__RadialControllerSystemMenuItemKind *PIIterator_1__RadialControllerSystemMenuItemKind;

typedef _di_IIterable_1__RadialControllerSystemMenuItemKind *PIIterable_1__RadialControllerSystemMenuItemKind;

typedef _di_IRadialControllerConfiguration *PIRadialControllerConfiguration;

typedef _di_IRadialControllerConfigurationStatics *PIRadialControllerConfigurationStatics;

typedef _di_IRadialControllerConfiguration2 *PIRadialControllerConfiguration2;

typedef _di_IRadialControllerConfigurationStatics2 *PIRadialControllerConfigurationStatics2;

__interface  INTERFACE_UUID("{721FE01C-5AD4-5262-B078-3AB345105DB8}") IIterator_1__IPointerPoint_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{2C506FAB-54BD-5007-8847-46FB9494DFB3}") IIterator_1__IPointerPoint  : public IIterator_1__IPointerPoint_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IPointerPoint &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIPointerPoint items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IPointerPoint _scw_get_Current() { Winapi::Commontypes::_di_IPointerPoint __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IPointerPoint Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{F6F2CBA6-7076-5B59-9631-F6AC32B57695}") IIterable_1__IPointerPoint_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{69A48EED-AF6C-5AE9-ACAD-A403EB13C0DA}") IIterable_1__IPointerPoint  : public IIterable_1__IPointerPoint_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IPointerPoint &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{5A773E24-D968-535E-969A-76CE3602A637}") IIterator_1__IRadialControllerMenuItem_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1A32FA4D-B3ED-5B91-AC5D-F5CC1845E696}") IIterator_1__IRadialControllerMenuItem  : public IIterator_1__IRadialControllerMenuItem_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IRadialControllerMenuItem &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIRadialControllerMenuItem items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRadialControllerMenuItem _scw_get_Current() { Winapi::Commontypes::_di_IRadialControllerMenuItem __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRadialControllerMenuItem Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{1AA752B3-DC11-5BCE-B2B9-CD1BF8F235BE}") IIterable_1__IRadialControllerMenuItem_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{7C62A666-8F21-5875-AA98-951AC77DAEB3}") IIterable_1__IRadialControllerMenuItem  : public IIterable_1__IRadialControllerMenuItem_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IRadialControllerMenuItem &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{3D577EF6-4CEE-11E6-B535-001BDC06AB3B}") Core_IRadialControllerIndependentInputSource  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Controller(Winapi::Commontypes::_di_IRadialController &__get_Controller_result) = 0 ;
	virtual HRESULT __safecall get_Dispatcher(Winapi::Commontypes::_di_ICoreDispatcher &__get_Dispatcher_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRadialController _scw_get_Controller() { Winapi::Commontypes::_di_IRadialController __r; HRESULT __hr = get_Controller(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRadialController Controller = {read=_scw_get_Controller};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_ICoreDispatcher _scw_get_Dispatcher() { Winapi::Commontypes::_di_ICoreDispatcher __r; HRESULT __hr = get_Dispatcher(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_ICoreDispatcher Dispatcher = {read=_scw_get_Dispatcher};
};

__interface  INTERFACE_UUID("{3D577EF5-4CEE-11E6-B535-001BDC06AB3B}") Core_IRadialControllerIndependentInputSourceStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateForView(Winapi::Commontypes::_di_ICoreApplicationView view, _di_Core_IRadialControllerIndependentInputSource &__CreateForView_result) = 0 ;
};

__interface  INTERFACE_UUID("{4D5FE14F-B87C-4028-BC9C-59E9947FB056}") IPointerPointTransform  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Inverse(_di_IPointerPointTransform &__get_Inverse_result) = 0 ;
	virtual HRESULT __safecall TryTransform(System::Types::TPointF inPoint, /* out */ System::Types::TPointF &outPoint, bool &__TryTransform_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall TransformBounds(System::Types::TRectF rect, System::Types::TRectF &__TransformBounds_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall TransformBounds(const System::Types::TRectF &rect, System::Types::TRectF &__TransformBounds_result) = 0 ;
#endif /* _WIN64 */
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IPointerPointTransform _scw_get_Inverse() { _di_IPointerPointTransform __r; HRESULT __hr = get_Inverse(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IPointerPointTransform Inverse = {read=_scw_get_Inverse};
};

__interface  INTERFACE_UUID("{3D577EEC-4CEE-11E6-B535-001BDC06AB3B}") IRadialControllerRotationChangedEventArgs2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsButtonPressed(bool &__get_IsButtonPressed_result) = 0 ;
	virtual HRESULT __safecall get_SimpleHapticsController(Winapi::Devices::_di_Haptics_ISimpleHapticsController &__get_SimpleHapticsController_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsButtonPressed() { bool __r; HRESULT __hr = get_IsButtonPressed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsButtonPressed = {read=_scw_get_IsButtonPressed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Devices::_di_Haptics_ISimpleHapticsController _scw_get_SimpleHapticsController() { Winapi::Devices::_di_Haptics_ISimpleHapticsController __r; HRESULT __hr = get_SimpleHapticsController(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Devices::_di_Haptics_ISimpleHapticsController SimpleHapticsController = {read=_scw_get_SimpleHapticsController};
};

__interface  INTERFACE_UUID("{3D577EED-4CEE-11E6-B535-001BDC06AB3B}") IRadialControllerButtonPressedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Contact(Winapi::Commontypes::_di_IRadialControllerScreenContact &__get_Contact_result) = 0 ;
	virtual HRESULT __safecall get_SimpleHapticsController(Winapi::Devices::_di_Haptics_ISimpleHapticsController &__get_SimpleHapticsController_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRadialControllerScreenContact _scw_get_Contact() { Winapi::Commontypes::_di_IRadialControllerScreenContact __r; HRESULT __hr = get_Contact(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRadialControllerScreenContact Contact = {read=_scw_get_Contact};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Devices::_di_Haptics_ISimpleHapticsController _scw_get_SimpleHapticsController() { Winapi::Devices::_di_Haptics_ISimpleHapticsController __r; HRESULT __hr = get_SimpleHapticsController(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Devices::_di_Haptics_ISimpleHapticsController SimpleHapticsController = {read=_scw_get_SimpleHapticsController};
};

__interface  INTERFACE_UUID("{3D577EEE-3CEE-11E6-B535-001BDC06AB3B}") IRadialControllerButtonHoldingEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Contact(Winapi::Commontypes::_di_IRadialControllerScreenContact &__get_Contact_result) = 0 ;
	virtual HRESULT __safecall get_SimpleHapticsController(Winapi::Devices::_di_Haptics_ISimpleHapticsController &__get_SimpleHapticsController_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRadialControllerScreenContact _scw_get_Contact() { Winapi::Commontypes::_di_IRadialControllerScreenContact __r; HRESULT __hr = get_Contact(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRadialControllerScreenContact Contact = {read=_scw_get_Contact};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Devices::_di_Haptics_ISimpleHapticsController _scw_get_SimpleHapticsController() { Winapi::Devices::_di_Haptics_ISimpleHapticsController __r; HRESULT __hr = get_SimpleHapticsController(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Devices::_di_Haptics_ISimpleHapticsController SimpleHapticsController = {read=_scw_get_SimpleHapticsController};
};

__interface  INTERFACE_UUID("{3D577EEF-3CEE-11E6-B535-001BDC06AB3B}") IRadialControllerButtonReleasedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Contact(Winapi::Commontypes::_di_IRadialControllerScreenContact &__get_Contact_result) = 0 ;
	virtual HRESULT __safecall get_SimpleHapticsController(Winapi::Devices::_di_Haptics_ISimpleHapticsController &__get_SimpleHapticsController_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRadialControllerScreenContact _scw_get_Contact() { Winapi::Commontypes::_di_IRadialControllerScreenContact __r; HRESULT __hr = get_Contact(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRadialControllerScreenContact Contact = {read=_scw_get_Contact};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Devices::_di_Haptics_ISimpleHapticsController _scw_get_SimpleHapticsController() { Winapi::Devices::_di_Haptics_ISimpleHapticsController __r; HRESULT __hr = get_SimpleHapticsController(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Devices::_di_Haptics_ISimpleHapticsController SimpleHapticsController = {read=_scw_get_SimpleHapticsController};
};

__interface  INTERFACE_UUID("{3D577EF0-3CEE-11E6-B535-001BDC06AB3B}") IRadialControllerScreenContactStartedEventArgs2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsButtonPressed(bool &__get_IsButtonPressed_result) = 0 ;
	virtual HRESULT __safecall get_SimpleHapticsController(Winapi::Devices::_di_Haptics_ISimpleHapticsController &__get_SimpleHapticsController_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsButtonPressed() { bool __r; HRESULT __hr = get_IsButtonPressed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsButtonPressed = {read=_scw_get_IsButtonPressed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Devices::_di_Haptics_ISimpleHapticsController _scw_get_SimpleHapticsController() { Winapi::Devices::_di_Haptics_ISimpleHapticsController __r; HRESULT __hr = get_SimpleHapticsController(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Devices::_di_Haptics_ISimpleHapticsController SimpleHapticsController = {read=_scw_get_SimpleHapticsController};
};

__interface  INTERFACE_UUID("{3D577EF1-3CEE-11E6-B535-001BDC06AB3B}") IRadialControllerScreenContactContinuedEventArgs2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsButtonPressed(bool &__get_IsButtonPressed_result) = 0 ;
	virtual HRESULT __safecall get_SimpleHapticsController(Winapi::Devices::_di_Haptics_ISimpleHapticsController &__get_SimpleHapticsController_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsButtonPressed() { bool __r; HRESULT __hr = get_IsButtonPressed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsButtonPressed = {read=_scw_get_IsButtonPressed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Devices::_di_Haptics_ISimpleHapticsController _scw_get_SimpleHapticsController() { Winapi::Devices::_di_Haptics_ISimpleHapticsController __r; HRESULT __hr = get_SimpleHapticsController(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Devices::_di_Haptics_ISimpleHapticsController SimpleHapticsController = {read=_scw_get_SimpleHapticsController};
};

__interface  INTERFACE_UUID("{3D577EF2-3CEE-11E6-B535-001BDC06AB3B}") IRadialControllerScreenContactEndedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsButtonPressed(bool &__get_IsButtonPressed_result) = 0 ;
	virtual HRESULT __safecall get_SimpleHapticsController(Winapi::Devices::_di_Haptics_ISimpleHapticsController &__get_SimpleHapticsController_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsButtonPressed() { bool __r; HRESULT __hr = get_IsButtonPressed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsButtonPressed = {read=_scw_get_IsButtonPressed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Devices::_di_Haptics_ISimpleHapticsController _scw_get_SimpleHapticsController() { Winapi::Devices::_di_Haptics_ISimpleHapticsController __r; HRESULT __hr = get_SimpleHapticsController(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Devices::_di_Haptics_ISimpleHapticsController SimpleHapticsController = {read=_scw_get_SimpleHapticsController};
};

__interface  INTERFACE_UUID("{3D577EF3-3CEE-11E6-B535-001BDC06AB3B}") IRadialControllerButtonClickedEventArgs2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_SimpleHapticsController(Winapi::Devices::_di_Haptics_ISimpleHapticsController &__get_SimpleHapticsController_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Devices::_di_Haptics_ISimpleHapticsController _scw_get_SimpleHapticsController() { Winapi::Devices::_di_Haptics_ISimpleHapticsController __r; HRESULT __hr = get_SimpleHapticsController(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Devices::_di_Haptics_ISimpleHapticsController SimpleHapticsController = {read=_scw_get_SimpleHapticsController};
};

__interface  INTERFACE_UUID("{3D577EF4-3CEE-11E6-B535-001BDC06AB3B}") IRadialControllerControlAcquiredEventArgs2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsButtonPressed(bool &__get_IsButtonPressed_result) = 0 ;
	virtual HRESULT __safecall get_SimpleHapticsController(Winapi::Devices::_di_Haptics_ISimpleHapticsController &__get_SimpleHapticsController_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsButtonPressed() { bool __r; HRESULT __hr = get_IsButtonPressed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsButtonPressed = {read=_scw_get_IsButtonPressed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Devices::_di_Haptics_ISimpleHapticsController _scw_get_SimpleHapticsController() { Winapi::Devices::_di_Haptics_ISimpleHapticsController __r; HRESULT __hr = get_SimpleHapticsController(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Devices::_di_Haptics_ISimpleHapticsController SimpleHapticsController = {read=_scw_get_SimpleHapticsController};
};

__interface  INTERFACE_UUID("{660BEE4A-4FED-5A62-AA5D-8113B477BC69}") TypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{A84E58BE-27BD-5B94-BD1C-AC5319506931}") TypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs  : public TypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Commontypes::_di_IRadialController sender, _di_IRadialControllerButtonPressedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{4C44F2FF-3A4A-51BA-A01F-9F2002471F59}") TypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{1DD1E759-DDBD-5FCC-AE7B-9DCFE3B28F7B}") TypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs  : public TypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Commontypes::_di_IRadialController sender, _di_IRadialControllerButtonHoldingEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{C22FF62C-C642-5D50-9340-FE163122720C}") TypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{16547458-2C91-5F76-AB77-69CBECB5085F}") TypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs  : public TypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Commontypes::_di_IRadialController sender, _di_IRadialControllerButtonReleasedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{3D577EFF-4CEE-11E6-B535-001BDC06AB3B}") IRadialController2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_ButtonPressed(_di_TypedEventHandler_2__IRadialController__IRadialControllerButtonPressedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_ButtonPressed_result) = 0 ;
	virtual HRESULT __safecall remove_ButtonPressed(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_ButtonHolding(_di_TypedEventHandler_2__IRadialController__IRadialControllerButtonHoldingEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_ButtonHolding_result) = 0 ;
	virtual HRESULT __safecall remove_ButtonHolding(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_ButtonReleased(_di_TypedEventHandler_2__IRadialController__IRadialControllerButtonReleasedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_ButtonReleased_result) = 0 ;
	virtual HRESULT __safecall remove_ButtonReleased(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
};

__interface  INTERFACE_UUID("{FADED0B7-B84C-4894-87AA-8F25AA5F288B}") IRadialControllerStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall IsSupported(bool &__IsSupported_result) = 0 ;
	virtual HRESULT __safecall CreateForCurrentView(Winapi::Commontypes::_di_IRadialController &__CreateForCurrentView_result) = 0 ;
};

__interface  INTERFACE_UUID("{249E0887-D842-4524-9DF8-E0D647EDC887}") IRadialControllerMenuItemStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateFromIcon(HSTRING displayText, Winapi::Commontypes::_di_IRandomAccessStreamReference icon, Winapi::Commontypes::_di_IRadialControllerMenuItem &__CreateFromIcon_result) = 0 ;
	virtual HRESULT __safecall CreateFromKnownIcon(HSTRING displayText, Winapi::Commontypes::RadialControllerMenuKnownIcon value, Winapi::Commontypes::_di_IRadialControllerMenuItem &__CreateFromKnownIcon_result) = 0 ;
};

__interface  INTERFACE_UUID("{0CBB70BE-7E3E-48BD-BE04-2C7FCAA9C1FF}") IRadialControllerMenuItemStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateFromFontGlyph(HSTRING displayText, HSTRING glyph, HSTRING fontFamily, Winapi::Commontypes::_di_IRadialControllerMenuItem &__CreateFromFontGlyph_result) = 0 /* overload */;
	virtual HRESULT __safecall CreateFromFontGlyph(HSTRING displayText, HSTRING glyph, HSTRING fontFamily, Winapi::Commontypes::_di_IUriRuntimeClass fontUri, Winapi::Commontypes::_di_IRadialControllerMenuItem &__CreateFromFontGlyph_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{3FBC1858-A43E-54DC-B0E2-8B098BDDACF6}") IIterator_1__RadialControllerSystemMenuItemKind_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__RadialControllerSystemMenuItemKind  : public IIterator_1__RadialControllerSystemMenuItemKind_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::RadialControllerSystemMenuItemKind &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PRadialControllerSystemMenuItemKind items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::RadialControllerSystemMenuItemKind _scw_get_Current() { Winapi::Commontypes::RadialControllerSystemMenuItemKind __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::RadialControllerSystemMenuItemKind Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{4516010F-FD98-5E1D-BF3F-AEAF79F1F3DA}") IIterable_1__RadialControllerSystemMenuItemKind_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__RadialControllerSystemMenuItemKind  : public IIterable_1__RadialControllerSystemMenuItemKind_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__RadialControllerSystemMenuItemKind &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{A6B79ECB-6A52-4430-910C-56370A9D6B42}") IRadialControllerConfiguration  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetDefaultMenuItems(_di_IIterable_1__RadialControllerSystemMenuItemKind buttons) = 0 ;
	virtual HRESULT __safecall ResetToDefaultMenuItems() = 0 ;
	virtual HRESULT __safecall TrySelectDefaultMenuItem(Winapi::Commontypes::RadialControllerSystemMenuItemKind type, bool &__TrySelectDefaultMenuItem_result) = 0 ;
};

__interface  INTERFACE_UUID("{79B6B0E5-069A-4486-A99D-8DB772B9642F}") IRadialControllerConfigurationStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetForCurrentView(_di_IRadialControllerConfiguration &__GetForCurrentView_result) = 0 ;
};

__interface  INTERFACE_UUID("{3D577EF7-3CEE-11E6-B535-001BDC06AB3B}") IRadialControllerConfiguration2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_ActiveControllerWhenMenuIsSuppressed(Winapi::Commontypes::_di_IRadialController value) = 0 ;
	virtual HRESULT __safecall get_ActiveControllerWhenMenuIsSuppressed(Winapi::Commontypes::_di_IRadialController &__get_ActiveControllerWhenMenuIsSuppressed_result) = 0 ;
	virtual HRESULT __safecall put_IsMenuSuppressed(bool value) = 0 ;
	virtual HRESULT __safecall get_IsMenuSuppressed(bool &__get_IsMenuSuppressed_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRadialController _scw_get_ActiveControllerWhenMenuIsSuppressed() { Winapi::Commontypes::_di_IRadialController __r; HRESULT __hr = get_ActiveControllerWhenMenuIsSuppressed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRadialController ActiveControllerWhenMenuIsSuppressed = {read=_scw_get_ActiveControllerWhenMenuIsSuppressed, write=put_ActiveControllerWhenMenuIsSuppressed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsMenuSuppressed() { bool __r; HRESULT __hr = get_IsMenuSuppressed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsMenuSuppressed = {read=_scw_get_IsMenuSuppressed, write=put_IsMenuSuppressed};
};

__interface  INTERFACE_UUID("{53E08B17-E205-48D3-9CAF-80FF47C4D7C7}") IRadialControllerConfigurationStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_AppController(Winapi::Commontypes::_di_IRadialController value) = 0 ;
	virtual HRESULT __safecall get_AppController(Winapi::Commontypes::_di_IRadialController &__get_AppController_result) = 0 ;
	virtual HRESULT __safecall put_IsAppControllerEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_IsAppControllerEnabled(bool &__get_IsAppControllerEnabled_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRadialController _scw_get_AppController() { Winapi::Commontypes::_di_IRadialController __r; HRESULT __hr = get_AppController(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRadialController AppController = {read=_scw_get_AppController, write=put_AppController};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsAppControllerEnabled() { bool __r; HRESULT __hr = get_IsAppControllerEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsAppControllerEnabled = {read=_scw_get_IsAppControllerEnabled, write=put_IsAppControllerEnabled};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCore_RadialControllerIndependentInputSource : public System::Win::Winrt::TWinRTGenericImportS__1<_di_Core_IRadialControllerIndependentInputSourceStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_Core_IRadialControllerIndependentInputSourceStatics> inherited;
	
public:
	static _di_Core_IRadialControllerIndependentInputSource __fastcall CreateForView(Winapi::Commontypes::_di_ICoreApplicationView view);
public:
	/* TObject.Create */ inline __fastcall TCore_RadialControllerIndependentInputSource() : System::Win::Winrt::TWinRTGenericImportS__1<_di_Core_IRadialControllerIndependentInputSourceStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCore_RadialControllerIndependentInputSource() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TRadialController : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IRadialControllerStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IRadialControllerStatics> inherited;
	
public:
	static bool __fastcall IsSupported();
	static Winapi::Commontypes::_di_IRadialController __fastcall CreateForCurrentView();
public:
	/* TObject.Create */ inline __fastcall TRadialController() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IRadialControllerStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRadialController() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TRadialControllerMenuItem : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_IRadialControllerMenuItemStatics,_di_IRadialControllerMenuItemStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_IRadialControllerMenuItemStatics,_di_IRadialControllerMenuItemStatics2> inherited;
	
public:
	static Winapi::Commontypes::_di_IRadialControllerMenuItem __fastcall CreateFromFontGlyph(HSTRING displayText, HSTRING glyph, HSTRING fontFamily)/* overload */;
	static Winapi::Commontypes::_di_IRadialControllerMenuItem __fastcall CreateFromFontGlyph(HSTRING displayText, HSTRING glyph, HSTRING fontFamily, Winapi::Commontypes::_di_IUriRuntimeClass fontUri)/* overload */;
	static Winapi::Commontypes::_di_IRadialControllerMenuItem __fastcall CreateFromIcon(HSTRING displayText, Winapi::Commontypes::_di_IRandomAccessStreamReference icon);
	static Winapi::Commontypes::_di_IRadialControllerMenuItem __fastcall CreateFromKnownIcon(HSTRING displayText, Winapi::Commontypes::RadialControllerMenuKnownIcon value);
public:
	/* TObject.Create */ inline __fastcall TRadialControllerMenuItem() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_IRadialControllerMenuItemStatics,_di_IRadialControllerMenuItemStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRadialControllerMenuItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TRadialControllerConfiguration : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_IRadialControllerConfigurationStatics,_di_IRadialControllerConfigurationStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_IRadialControllerConfigurationStatics,_di_IRadialControllerConfigurationStatics2> inherited;
	
public:
	static void __fastcall put_AppController(Winapi::Commontypes::_di_IRadialController value);
	static Winapi::Commontypes::_di_IRadialController __fastcall get_AppController();
	static void __fastcall put_IsAppControllerEnabled(bool value);
	static bool __fastcall get_IsAppControllerEnabled();
	/* static */ __property Winapi::Commontypes::_di_IRadialController AppController = {read=get_AppController, write=put_AppController};
	/* static */ __property bool IsAppControllerEnabled = {read=get_IsAppControllerEnabled, write=put_IsAppControllerEnabled, nodefault};
	static _di_IRadialControllerConfiguration __fastcall GetForCurrentView();
public:
	/* TObject.Create */ inline __fastcall TRadialControllerConfiguration() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_IRadialControllerConfigurationStatics,_di_IRadialControllerConfigurationStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRadialControllerConfiguration() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Input */
}	/* namespace Ui */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Ui_InputHPP
