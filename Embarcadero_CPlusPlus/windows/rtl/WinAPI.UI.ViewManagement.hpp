// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.UI.ViewManagement.pas' rev: 34.00 (Windows)

#ifndef Winapi_Ui_ViewmanagementHPP
#define Winapi_Ui_ViewmanagementHPP

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
namespace Viewmanagement
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IReference_1__UIElementType;
typedef System::DelphiInterface<IReference_1__UIElementType> _di_IReference_1__UIElementType;
__interface DELPHIINTERFACE IInputPaneVisibilityEventArgs;
typedef System::DelphiInterface<IInputPaneVisibilityEventArgs> _di_IInputPaneVisibilityEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs_Delegate_Base> _di_TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs> _di_TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs;
__interface DELPHIINTERFACE IInputPane;
typedef System::DelphiInterface<IInputPane> _di_IInputPane;
__interface DELPHIINTERFACE IInputPane2;
typedef System::DelphiInterface<IInputPane2> _di_IInputPane2;
__interface DELPHIINTERFACE IInputPaneControl;
typedef System::DelphiInterface<IInputPaneControl> _di_IInputPaneControl;
__interface DELPHIINTERFACE IInputPaneStatics;
typedef System::DelphiInterface<IInputPaneStatics> _di_IInputPaneStatics;
__interface DELPHIINTERFACE IUIViewSettings;
typedef System::DelphiInterface<IUIViewSettings> _di_IUIViewSettings;
__interface DELPHIINTERFACE IUIViewSettingsStatics;
typedef System::DelphiInterface<IUIViewSettingsStatics> _di_IUIViewSettingsStatics;
class DELPHICLASS TInputPane;
class DELPHICLASS TUIViewSettings;
//-- type declarations -------------------------------------------------------
typedef _di_IReference_1__UIElementType *PIReference_1__UIElementType;

typedef _di_IInputPaneVisibilityEventArgs *PIInputPaneVisibilityEventArgs;

typedef _di_TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs *PTypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs;

typedef _di_IInputPane *PIInputPane;

typedef _di_IInputPane2 *PIInputPane2;

typedef _di_IInputPaneControl *PIInputPaneControl;

typedef _di_IInputPaneStatics *PIInputPaneStatics;

typedef _di_IUIViewSettings *PIUIViewSettings;

typedef _di_IUIViewSettingsStatics *PIUIViewSettingsStatics;

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__UIElementType  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::UIElementType &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::UIElementType _scw_get_Value() { Winapi::Commontypes::UIElementType __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::UIElementType Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{D243E016-D907-4FCC-BB8D-F77BAA5028F1}") IInputPaneVisibilityEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_OccludedRect(System::Types::TRectF &__get_OccludedRect_result) = 0 ;
	virtual HRESULT __safecall put_EnsuredFocusedElementInView(bool value) = 0 ;
	virtual HRESULT __safecall get_EnsuredFocusedElementInView(bool &__get_EnsuredFocusedElementInView_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_EnsuredFocusedElementInView() { bool __r; HRESULT __hr = get_EnsuredFocusedElementInView(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool EnsuredFocusedElementInView = {read=_scw_get_EnsuredFocusedElementInView, write=put_EnsuredFocusedElementInView};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TRectF _scw_get_OccludedRect() { System::Types::TRectF __r; HRESULT __hr = get_OccludedRect(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TRectF OccludedRect = {read=_scw_get_OccludedRect};
};

__interface  INTERFACE_UUID("{B813D684-D953-5A8A-9B30-78B79FB9147B}") TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{DBA5B41B-EA45-5B69-B0D4-80493AE17F1C}") TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs  : public TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IInputPane sender, _di_IInputPaneVisibilityEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{640ADA70-06F3-4C87-A678-9829C9127C28}") IInputPane  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_Showing(_di_TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_Showing_result) = 0 ;
	virtual HRESULT __safecall remove_Showing(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_Hiding(_di_TypedEventHandler_2__IInputPane__IInputPaneVisibilityEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_Hiding_result) = 0 ;
	virtual HRESULT __safecall remove_Hiding(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall get_OccludedRect(System::Types::TRectF &__get_OccludedRect_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TRectF _scw_get_OccludedRect() { System::Types::TRectF __r; HRESULT __hr = get_OccludedRect(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TRectF OccludedRect = {read=_scw_get_OccludedRect};
};

__interface  INTERFACE_UUID("{8A6B3F26-7090-4793-944C-C3F2CDE26276}") IInputPane2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall TryShow(bool &__TryShow_result) = 0 ;
	virtual HRESULT __safecall TryHide(bool &__TryHide_result) = 0 ;
};

__interface  INTERFACE_UUID("{088BB24F-962F-489D-AA6E-C6BE1A0A6E52}") IInputPaneControl  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Visible(bool &__get_Visible_result) = 0 ;
	virtual HRESULT __safecall put_Visible(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Visible() { bool __r; HRESULT __hr = get_Visible(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Visible = {read=_scw_get_Visible, write=put_Visible};
};

__interface  INTERFACE_UUID("{95F4AF3A-EF47-424A-9741-FD2815EBA2BD}") IInputPaneStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetForCurrentView(_di_IInputPane &__GetForCurrentView_result) = 0 ;
};

__interface  INTERFACE_UUID("{C63657F6-8850-470D-88F8-455E16EA2C26}") IUIViewSettings  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_UserInteractionMode(Winapi::Commontypes::UserInteractionMode &__get_UserInteractionMode_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::UserInteractionMode _scw_get_UserInteractionMode() { Winapi::Commontypes::UserInteractionMode __r; HRESULT __hr = get_UserInteractionMode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::UserInteractionMode UserInteractionMode = {read=_scw_get_UserInteractionMode};
};

__interface  INTERFACE_UUID("{595C97A5-F8F6-41CF-B0FB-AACDB81FD5F6}") IUIViewSettingsStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetForCurrentView(_di_IUIViewSettings &__GetForCurrentView_result) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TInputPane : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IInputPaneStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IInputPaneStatics> inherited;
	
public:
	static _di_IInputPane __fastcall GetForCurrentView();
public:
	/* TObject.Create */ inline __fastcall TInputPane() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IInputPaneStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInputPane() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TUIViewSettings : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IUIViewSettingsStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IUIViewSettingsStatics> inherited;
	
public:
	static _di_IUIViewSettings __fastcall GetForCurrentView();
public:
	/* TObject.Create */ inline __fastcall TUIViewSettings() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IUIViewSettingsStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TUIViewSettings() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Viewmanagement */
}	/* namespace Ui */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Ui_ViewmanagementHPP
