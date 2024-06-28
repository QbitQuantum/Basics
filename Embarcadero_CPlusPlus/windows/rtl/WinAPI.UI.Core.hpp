// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.UI.Core.pas' rev: 34.00 (Windows)

#ifndef Winapi_Ui_CoreHPP
#define Winapi_Ui_CoreHPP

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
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Ui
{
namespace Core
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__IInputEnabledEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__IInputEnabledEventArgs_Delegate_Base> _di_TypedEventHandler_2__IInspectable__IInputEnabledEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__IInputEnabledEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__IInputEnabledEventArgs> _di_TypedEventHandler_2__IInspectable__IInputEnabledEventArgs;
__interface DELPHIINTERFACE IInitializeWithCoreWindow;
typedef System::DelphiInterface<IInitializeWithCoreWindow> _di_IInitializeWithCoreWindow;
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__IPointerEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__IPointerEventArgs_Delegate_Base> _di_TypedEventHandler_2__IInspectable__IPointerEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__IPointerEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__IPointerEventArgs> _di_TypedEventHandler_2__IInspectable__IPointerEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__ICharacterReceivedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__ICharacterReceivedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IInspectable__ICharacterReceivedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__ICharacterReceivedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__ICharacterReceivedEventArgs> _di_TypedEventHandler_2__IInspectable__ICharacterReceivedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__IKeyEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__IKeyEventArgs_Delegate_Base> _di_TypedEventHandler_2__IInspectable__IKeyEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__IKeyEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__IKeyEventArgs> _di_TypedEventHandler_2__IInspectable__IKeyEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__ICoreWindowEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__ICoreWindowEventArgs_Delegate_Base> _di_TypedEventHandler_2__IInspectable__ICoreWindowEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__ICoreWindowEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__ICoreWindowEventArgs> _di_TypedEventHandler_2__IInspectable__ICoreWindowEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__ITouchHitTestingEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__ITouchHitTestingEventArgs_Delegate_Base> _di_TypedEventHandler_2__IInspectable__ITouchHitTestingEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IInspectable__ITouchHitTestingEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IInspectable__ITouchHitTestingEventArgs> _di_TypedEventHandler_2__IInspectable__ITouchHitTestingEventArgs;
__interface DELPHIINTERFACE AnimationMetrics_IPropertyAnimation;
typedef System::DelphiInterface<AnimationMetrics_IPropertyAnimation> _di_AnimationMetrics_IPropertyAnimation;
__interface DELPHIINTERFACE AnimationMetrics_IScaleAnimation;
typedef System::DelphiInterface<AnimationMetrics_IScaleAnimation> _di_AnimationMetrics_IScaleAnimation;
__interface DELPHIINTERFACE AnimationMetrics_IOpacityAnimation;
typedef System::DelphiInterface<AnimationMetrics_IOpacityAnimation> _di_AnimationMetrics_IOpacityAnimation;
__interface DELPHIINTERFACE IIterator_1__AnimationMetrics_IPropertyAnimation_Base;
typedef System::DelphiInterface<IIterator_1__AnimationMetrics_IPropertyAnimation_Base> _di_IIterator_1__AnimationMetrics_IPropertyAnimation_Base;
__interface DELPHIINTERFACE IIterator_1__AnimationMetrics_IPropertyAnimation;
typedef System::DelphiInterface<IIterator_1__AnimationMetrics_IPropertyAnimation> _di_IIterator_1__AnimationMetrics_IPropertyAnimation;
__interface DELPHIINTERFACE IIterable_1__AnimationMetrics_IPropertyAnimation_Base;
typedef System::DelphiInterface<IIterable_1__AnimationMetrics_IPropertyAnimation_Base> _di_IIterable_1__AnimationMetrics_IPropertyAnimation_Base;
__interface DELPHIINTERFACE IIterable_1__AnimationMetrics_IPropertyAnimation;
typedef System::DelphiInterface<IIterable_1__AnimationMetrics_IPropertyAnimation> _di_IIterable_1__AnimationMetrics_IPropertyAnimation;
__interface DELPHIINTERFACE IVectorView_1__AnimationMetrics_IPropertyAnimation;
typedef System::DelphiInterface<IVectorView_1__AnimationMetrics_IPropertyAnimation> _di_IVectorView_1__AnimationMetrics_IPropertyAnimation;
__interface DELPHIINTERFACE AnimationMetrics_IAnimationDescription;
typedef System::DelphiInterface<AnimationMetrics_IAnimationDescription> _di_AnimationMetrics_IAnimationDescription;
__interface DELPHIINTERFACE AnimationMetrics_IAnimationDescriptionFactory;
typedef System::DelphiInterface<AnimationMetrics_IAnimationDescriptionFactory> _di_AnimationMetrics_IAnimationDescriptionFactory;
class DELPHICLASS TAnimationMetrics_AnimationDescription;
//-- type declarations -------------------------------------------------------
typedef _di_TypedEventHandler_2__IInspectable__IInputEnabledEventArgs *PTypedEventHandler_2__IInspectable__IInputEnabledEventArgs;

typedef _di_IInitializeWithCoreWindow *PIInitializeWithCoreWindow;

typedef _di_TypedEventHandler_2__IInspectable__IPointerEventArgs *PTypedEventHandler_2__IInspectable__IPointerEventArgs;

typedef _di_TypedEventHandler_2__IInspectable__ICharacterReceivedEventArgs *PTypedEventHandler_2__IInspectable__ICharacterReceivedEventArgs;

typedef _di_TypedEventHandler_2__IInspectable__IKeyEventArgs *PTypedEventHandler_2__IInspectable__IKeyEventArgs;

typedef _di_TypedEventHandler_2__IInspectable__ICoreWindowEventArgs *PTypedEventHandler_2__IInspectable__ICoreWindowEventArgs;

typedef _di_TypedEventHandler_2__IInspectable__ITouchHitTestingEventArgs *PTypedEventHandler_2__IInspectable__ITouchHitTestingEventArgs;

typedef _di_AnimationMetrics_IPropertyAnimation *PAnimationMetrics_IPropertyAnimation;

typedef _di_AnimationMetrics_IScaleAnimation *PAnimationMetrics_IScaleAnimation;

typedef _di_AnimationMetrics_IOpacityAnimation *PAnimationMetrics_IOpacityAnimation;

typedef _di_IIterator_1__AnimationMetrics_IPropertyAnimation *PIIterator_1__AnimationMetrics_IPropertyAnimation;

typedef _di_IIterable_1__AnimationMetrics_IPropertyAnimation *PIIterable_1__AnimationMetrics_IPropertyAnimation;

typedef _di_IVectorView_1__AnimationMetrics_IPropertyAnimation *PIVectorView_1__AnimationMetrics_IPropertyAnimation;

typedef _di_AnimationMetrics_IAnimationDescription *PAnimationMetrics_IAnimationDescription;

typedef _di_AnimationMetrics_IAnimationDescriptionFactory *PAnimationMetrics_IAnimationDescriptionFactory;

__interface  INTERFACE_UUID("{C9965F1C-3641-51B6-B823-048EC3628FB0}") TypedEventHandler_2__IInspectable__IInputEnabledEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{CAEE5D54-F45C-56BC-8F24-FFB2A20A00B5}") TypedEventHandler_2__IInspectable__IInputEnabledEventArgs  : public TypedEventHandler_2__IInspectable__IInputEnabledEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Winrt::_di_IInspectable sender, Winapi::Commontypes::_di_IInputEnabledEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{188F20D6-9873-464A-ACE5-57E010F465E6}") IInitializeWithCoreWindow  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Initialize(Winapi::Commontypes::_di_ICoreWindow window) = 0 ;
};

__interface  INTERFACE_UUID("{26AABF41-A0FD-5E66-B188-6C74182D00CD}") TypedEventHandler_2__IInspectable__IPointerEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{698383FB-4816-51E2-B784-F1EFD30A0A7F}") TypedEventHandler_2__IInspectable__IPointerEventArgs  : public TypedEventHandler_2__IInspectable__IPointerEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Winrt::_di_IInspectable sender, Winapi::Commontypes::_di_IPointerEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{5AA4A848-86B2-506B-89AB-5EB5786420C6}") TypedEventHandler_2__IInspectable__ICharacterReceivedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{B1626D26-8C50-5526-947F-76E5652A527F}") TypedEventHandler_2__IInspectable__ICharacterReceivedEventArgs  : public TypedEventHandler_2__IInspectable__ICharacterReceivedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Winrt::_di_IInspectable sender, Winapi::Commontypes::_di_ICharacterReceivedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{EADFFDF7-D70E-5688-906C-C2B1229EA16D}") TypedEventHandler_2__IInspectable__IKeyEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{DEC68719-2C61-5E75-8DCB-AEA742273701}") TypedEventHandler_2__IInspectable__IKeyEventArgs  : public TypedEventHandler_2__IInspectable__IKeyEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Winrt::_di_IInspectable sender, Winapi::Commontypes::_di_IKeyEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{1A8AC270-A777-50F7-88A1-E34E56C09449}") TypedEventHandler_2__IInspectable__ICoreWindowEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{F520E86D-9D9B-5024-8BAE-1DCBDDEFC67E}") TypedEventHandler_2__IInspectable__ICoreWindowEventArgs  : public TypedEventHandler_2__IInspectable__ICoreWindowEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Winrt::_di_IInspectable sender, Winapi::Commontypes::_di_ICoreWindowEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{C76E9D25-6A96-58FD-874F-AE52BD603AF8}") TypedEventHandler_2__IInspectable__ITouchHitTestingEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{202CDEA7-C8ED-5F65-9E1A-9FD2606E6851}") TypedEventHandler_2__IInspectable__ITouchHitTestingEventArgs  : public TypedEventHandler_2__IInspectable__ITouchHitTestingEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Winrt::_di_IInspectable sender, Winapi::Commontypes::_di_ITouchHitTestingEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{3A01B4DA-4D8C-411E-B615-1ADE683A9903}") AnimationMetrics_IPropertyAnimation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Type(Winapi::Commontypes::AnimationMetrics_PropertyAnimationType &__get_Type_result) = 0 ;
	virtual HRESULT __safecall get_Delay(Winapi::Commontypes::TimeSpan &__get_Delay_result) = 0 ;
	virtual HRESULT __safecall get_Duration(Winapi::Commontypes::TimeSpan &__get_Duration_result) = 0 ;
	virtual HRESULT __safecall get_Control1(System::Types::TPointF &__get_Control1_result) = 0 ;
	virtual HRESULT __safecall get_Control2(System::Types::TPointF &__get_Control2_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TPointF _scw_get_Control1() { System::Types::TPointF __r; HRESULT __hr = get_Control1(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TPointF Control1 = {read=_scw_get_Control1};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TPointF _scw_get_Control2() { System::Types::TPointF __r; HRESULT __hr = get_Control2(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TPointF Control2 = {read=_scw_get_Control2};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Delay() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Delay(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Delay = {read=_scw_get_Delay};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Duration() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Duration(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Duration = {read=_scw_get_Duration};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AnimationMetrics_PropertyAnimationType _scw_get_Type() { Winapi::Commontypes::AnimationMetrics_PropertyAnimationType __r; HRESULT __hr = get_Type(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AnimationMetrics_PropertyAnimationType Type = {read=_scw_get_Type};
};

__interface  INTERFACE_UUID("{023552C7-71AB-428C-9C9F-D31780964995}") AnimationMetrics_IScaleAnimation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_InitialScaleX(Winapi::Commontypes::_di_IReference_1__Single &__get_InitialScaleX_result) = 0 ;
	virtual HRESULT __safecall get_InitialScaleY(Winapi::Commontypes::_di_IReference_1__Single &__get_InitialScaleY_result) = 0 ;
	virtual HRESULT __safecall get_FinalScaleX(float &__get_FinalScaleX_result) = 0 ;
	virtual HRESULT __safecall get_FinalScaleY(float &__get_FinalScaleY_result) = 0 ;
	virtual HRESULT __safecall get_NormalizedOrigin(System::Types::TPointF &__get_NormalizedOrigin_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_FinalScaleX() { float __r; HRESULT __hr = get_FinalScaleX(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float FinalScaleX = {read=_scw_get_FinalScaleX};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_FinalScaleY() { float __r; HRESULT __hr = get_FinalScaleY(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float FinalScaleY = {read=_scw_get_FinalScaleY};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Single _scw_get_InitialScaleX() { Winapi::Commontypes::_di_IReference_1__Single __r; HRESULT __hr = get_InitialScaleX(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Single InitialScaleX = {read=_scw_get_InitialScaleX};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Single _scw_get_InitialScaleY() { Winapi::Commontypes::_di_IReference_1__Single __r; HRESULT __hr = get_InitialScaleY(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Single InitialScaleY = {read=_scw_get_InitialScaleY};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TPointF _scw_get_NormalizedOrigin() { System::Types::TPointF __r; HRESULT __hr = get_NormalizedOrigin(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TPointF NormalizedOrigin = {read=_scw_get_NormalizedOrigin};
};

__interface  INTERFACE_UUID("{803AABE5-EE7E-455F-84E9-2506AFB8D2B4}") AnimationMetrics_IOpacityAnimation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_InitialOpacity(Winapi::Commontypes::_di_IReference_1__Single &__get_InitialOpacity_result) = 0 ;
	virtual HRESULT __safecall get_FinalOpacity(float &__get_FinalOpacity_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_FinalOpacity() { float __r; HRESULT __hr = get_FinalOpacity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float FinalOpacity = {read=_scw_get_FinalOpacity};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__Single _scw_get_InitialOpacity() { Winapi::Commontypes::_di_IReference_1__Single __r; HRESULT __hr = get_InitialOpacity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__Single InitialOpacity = {read=_scw_get_InitialOpacity};
};

__interface  INTERFACE_UUID("{BB6799D3-9F1A-5A4E-A940-945F1AB8C4FE}") IIterator_1__AnimationMetrics_IPropertyAnimation_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{BB6799D3-9F1A-5A4E-A940-945F1AB8C4FE}") IIterator_1__AnimationMetrics_IPropertyAnimation  : public IIterator_1__AnimationMetrics_IPropertyAnimation_Base 
{
	virtual HRESULT __safecall get_Current(_di_AnimationMetrics_IPropertyAnimation &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PAnimationMetrics_IPropertyAnimation items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AnimationMetrics_IPropertyAnimation _scw_get_Current() { _di_AnimationMetrics_IPropertyAnimation __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AnimationMetrics_IPropertyAnimation Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{C75F1BD1-A3C1-5881-9DA0-1ECDB8E51BC3}") IIterable_1__AnimationMetrics_IPropertyAnimation_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{C75F1BD1-A3C1-5881-9DA0-1ECDB8E51BC3}") IIterable_1__AnimationMetrics_IPropertyAnimation  : public IIterable_1__AnimationMetrics_IPropertyAnimation_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__AnimationMetrics_IPropertyAnimation &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{3A6ED95D-6A50-5EAD-A4C6-09F8BABC632C}") IVectorView_1__AnimationMetrics_IPropertyAnimation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_AnimationMetrics_IPropertyAnimation &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_AnimationMetrics_IPropertyAnimation value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PAnimationMetrics_IPropertyAnimation items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{7D11A549-BE3D-41DE-B081-05C149962F9B}") AnimationMetrics_IAnimationDescription  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Animations(_di_IVectorView_1__AnimationMetrics_IPropertyAnimation &__get_Animations_result) = 0 ;
	virtual HRESULT __safecall get_StaggerDelay(Winapi::Commontypes::TimeSpan &__get_StaggerDelay_result) = 0 ;
	virtual HRESULT __safecall get_StaggerDelayFactor(float &__get_StaggerDelayFactor_result) = 0 ;
	virtual HRESULT __safecall get_DelayLimit(Winapi::Commontypes::TimeSpan &__get_DelayLimit_result) = 0 ;
	virtual HRESULT __safecall get_ZOrder(int &__get_ZOrder_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__AnimationMetrics_IPropertyAnimation _scw_get_Animations() { _di_IVectorView_1__AnimationMetrics_IPropertyAnimation __r; HRESULT __hr = get_Animations(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__AnimationMetrics_IPropertyAnimation Animations = {read=_scw_get_Animations};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_DelayLimit() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_DelayLimit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan DelayLimit = {read=_scw_get_DelayLimit};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_StaggerDelay() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_StaggerDelay(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan StaggerDelay = {read=_scw_get_StaggerDelay};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_StaggerDelayFactor() { float __r; HRESULT __hr = get_StaggerDelayFactor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float StaggerDelayFactor = {read=_scw_get_StaggerDelayFactor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_ZOrder() { int __r; HRESULT __hr = get_ZOrder(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int ZOrder = {read=_scw_get_ZOrder};
};

__interface  INTERFACE_UUID("{C6E27ABE-C1FB-48B5-9271-ECC70AC86EF0}") AnimationMetrics_IAnimationDescriptionFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateInstance(Winapi::Commontypes::AnimationMetrics_AnimationEffect effect, Winapi::Commontypes::AnimationMetrics_AnimationEffectTarget target, _di_AnimationMetrics_IAnimationDescription &__CreateInstance_result) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAnimationMetrics_AnimationDescription : public System::Win::Winrt::TWinRTGenericImportF__1<_di_AnimationMetrics_IAnimationDescriptionFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_AnimationMetrics_IAnimationDescriptionFactory> inherited;
	
public:
	static _di_AnimationMetrics_IAnimationDescription __fastcall CreateInstance(Winapi::Commontypes::AnimationMetrics_AnimationEffect effect, Winapi::Commontypes::AnimationMetrics_AnimationEffectTarget target);
public:
	/* TObject.Create */ inline __fastcall TAnimationMetrics_AnimationDescription() : System::Win::Winrt::TWinRTGenericImportF__1<_di_AnimationMetrics_IAnimationDescriptionFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAnimationMetrics_AnimationDescription() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Core */
}	/* namespace Ui */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Ui_CoreHPP
