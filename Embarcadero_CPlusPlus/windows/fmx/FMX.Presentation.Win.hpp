// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Presentation.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Presentation_WinHPP
#define Fmx_Presentation_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Messaging.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <FMX.Types.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Win.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.ZOrder.Win.hpp>
#include <FMX.Helpers.Win.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Presentation
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWinView;
class DELPHICLASS TWinPresentation;
template<typename TPresentation> class DELPHICLASS TWinPresentationProxy__1;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TWinView : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	static TWinView* FCreationControl;
	static HWND FContainerHandle;
	static HWND __fastcall GetContainerHandle();
	__classmethod void __fastcall CreateContainerHandle();
	__classmethod void __fastcall DestroyContainerHandle();
	
private:
	// __classmethod void __fastcall DestroyClass@();
	
private:
	void *FDefWndProc;
	HWND FHandle;
	void *FObjectInstance;
	void __fastcall SetParentWindow(const HWND Value);
	HWND __fastcall GetParentWindow();
	void __fastcall WndProc(Winapi::Messages::TMessage &Message);
	MESSAGE void __fastcall WMWindowPosChanged(Winapi::Messages::TWMWindowPosMsg &Message);
	System::Types::TSize __fastcall GetSize();
	HWND __fastcall GetHandle();
	float __fastcall GetScale();
	
protected:
#ifndef _WIN64
	/* static */ __property HWND ContainerHandle = {read=GetContainerHandle, nodefault};
#else /* _WIN64 */
	/* static */ __property HWND ContainerHandle = {read=GetContainerHandle};
#endif /* _WIN64 */
	static const System::Int8 NullHWnd = System::Int8(0x0);
	
	virtual void __fastcall CreateHandle();
	virtual void __fastcall CreateParams(Fmx::Controls::Win::TCreateParams &Params);
	void __fastcall CreateSubClass(Fmx::Controls::Win::TCreateParams &Params, System::WideChar * ControlClassName);
	virtual void __fastcall DestroyHandle();
	__property void * DefWndProc = {read=FDefWndProc};
	virtual void __fastcall Resized();
	
public:
	__fastcall virtual TWinView(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TWinView();
	virtual void __fastcall DefaultHandler(void *Message);
	void __fastcall RecreateWnd();
	bool __fastcall HandleAllocated();
#ifndef _WIN64
	__property HWND Handle = {read=GetHandle, nodefault};
#else /* _WIN64 */
	__property HWND Handle = {read=GetHandle};
#endif /* _WIN64 */
	__property System::Types::TSize Size = {read=GetSize};
	__property float Scale = {read=GetScale};
#ifndef _WIN64
	__property HWND ParentWindow = {read=GetParentWindow, write=SetParentWindow, nodefault};
#else /* _WIN64 */
	__property HWND ParentWindow = {read=GetParentWindow, write=SetParentWindow};
#endif /* _WIN64 */
	
private:
	// __classmethod void __fastcall Create@();
};


class PASCALIMPLEMENTATION TWinPresentation : public TWinView
{
	typedef TWinView inherited;
	
	
private:
	class DELPHICLASS TInterfacedHandle;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TInterfacedHandle : public System::TInterfacedObject
	{
		typedef System::TInterfacedObject inherited;
		
	private:
		TWinPresentation* FView;
		
	public:
		__fastcall TInterfacedHandle(TWinPresentation* const AView);
		__property TWinPresentation* View = {read=FView};
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TInterfacedHandle() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	Fmx::Controls::TControl* FControl;
	Fmx::Controls::Model::TDataModel* FModel;
	Fmx::Forms::TCommonCustomForm* FForm;
	TInterfacedHandle* FInterfacedHandle;
	bool FIsParentNativeForm;
	System::Types::TSizeF FControlSize;
	Fmx::Zorder::Win::TWinZOrderManager* __fastcall GetZOrderManager();
	void __fastcall BeforeDestroyMessageListener(System::TObject* const Sender, System::Messaging::TMessageBase* const AMessage);
	void __fastcall AfterCreateMessageListener(System::TObject* const Sender, System::Messaging::TMessageBase* const AMessage);
	
protected:
	virtual void __fastcall CreateParams(Fmx::Controls::Win::TCreateParams &Params);
	virtual System::Types::TPoint __fastcall ExtractPoint(Winapi::Messages::TWMMouse &Message);
	virtual NativeInt __fastcall SetControlTextColor(const HDC DC, const bool Disabled);
	__property System::Types::TSizeF ControlSize = {read=FControlSize};
	MESSAGE void __fastcall PMGetNativeObject(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::_di_IInterface> &AMessage);
	MESSAGE void __fastcall PMRootChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::_di_IRoot> &AMessage);
	MESSAGE void __fastcall PMAncestorPresentationLoaded(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMAncestorPresentationUnloading(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::TControl*> &AMessage);
	MESSAGE void __fastcall PMUnload(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMRefreshParent(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMChangeOrder(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMAbsoluteChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMSetSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMGetSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMSetVisible(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMGetVisible(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMAncesstorVisibleChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMSetAbsoluteEnabled(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMGetAbsoluteEnabled(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMDoExit(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMDoEnter(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMResetFocus(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall WMSetFocus(Winapi::Messages::TWMSetFocus &Message);
	MESSAGE void __fastcall WMKillFocus(Winapi::Messages::TWMKillFocus &Message);
	MESSAGE void __fastcall WMKeyDown(Winapi::Messages::TWMKey &Message);
	MESSAGE void __fastcall WMKeyUp(Winapi::Messages::TWMKey &Message);
	MESSAGE void __fastcall WMLButtonDown(Winapi::Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMRButtonDown(Winapi::Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMMouseMove(Winapi::Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMLButtonUp(Winapi::Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMRButtonUp(Winapi::Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMLButtonDblClick(Winapi::Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMRButtonDblClick(Winapi::Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMMButtonDblClick(Winapi::Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMTextColor(Winapi::Messages::TMessage &Message);
	MESSAGE void __fastcall WMDisabledTextColor(Winapi::Messages::TMessage &Message);
	virtual bool __fastcall FindAncestorPresentedControl _DEPRECATED_ATTRIBUTE1("Use ZOrderManager.FindParentNativeControl instead.") (/* out */ Fmx::Controls::TControl* &APlatformControl);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual void __fastcall CreateHandle();
	virtual void __fastcall DestroyHandle();
	
public:
	__fastcall virtual TWinPresentation(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual TWinPresentation(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */;
	__fastcall virtual ~TWinPresentation();
	bool __fastcall HasZOrderManager();
	__property Fmx::Zorder::Win::TWinZOrderManager* ZOrderManager = {read=GetZOrderManager};
	bool __fastcall HasControl _DEPRECATED_ATTRIBUTE1("Native presentation guarantees the availability of the Control during the presentation's lifetime.") ();
	virtual void __fastcall SetFocus();
	virtual void __fastcall ResetFocus();
	bool __fastcall IsFocused();
	void __fastcall UpdateOrderAndBounds();
	__property Fmx::Controls::TControl* Control = {read=FControl};
	__property Fmx::Controls::Model::TDataModel* Model = {read=FModel};
	__property bool IsParentNativeForm = {read=FIsParentNativeForm, nodefault};
	__property Fmx::Forms::TCommonCustomForm* Form = {read=FForm};
};


#ifndef _WIN64
typedef System::TMetaClass* TWinPresentationClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TWinPresentationClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename TPresentation> class PASCALIMPLEMENTATION TWinPresentationProxy__1 : public Fmx::Controls::Presentation::TPresentationProxy
{
	typedef Fmx::Controls::Presentation::TPresentationProxy inherited;
	
protected:
	virtual System::TObject* __fastcall CreateReceiver();
public:
	/* TPresentationProxy.Create */ inline __fastcall virtual TWinPresentationProxy__1()/* overload */ : Fmx::Controls::Presentation::TPresentationProxy() { }
	/* TPresentationProxy.Create */ inline __fastcall virtual TWinPresentationProxy__1(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Controls::Presentation::TPresentationProxy(AModel, AControl) { }
	/* TPresentationProxy.Destroy */ inline __fastcall virtual ~TWinPresentationProxy__1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Presentation */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_WIN)
using namespace Fmx::Presentation::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION)
using namespace Fmx::Presentation;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Presentation_WinHPP
