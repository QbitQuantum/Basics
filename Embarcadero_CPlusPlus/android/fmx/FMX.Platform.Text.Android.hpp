// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.Text.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Platform_Text_AndroidHPP
#define Fmx_Platform_Text_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.Embarcadero.hpp>
#include <FMX.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Text
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidTextInputContextMenu;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidTextInputContextMenu : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
	
private:
	enum class DECLSPEC_DENUM TContextMenuItem : unsigned char { Cut, Copy, Paste, Share, SelectAll };
	
	
public:
	static constexpr System::Int8 UndefinedScreenScale = System::Int8(0x0);
	
	
private:
	Fmx::Types::_di_IControl FControl;
	Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode FActionMode;
	float FScreenScale;
	void __fastcall ResetSelection();
	void __fastcall SelectAll();
	void __fastcall ShareText();
	void __fastcall CopyToClipboard();
	void __fastcall PasteFromClipboard();
	void __fastcall CutToClipboard();
	bool __fastcall IsTextReadOnly();
	bool __fastcall IsPassword();
	bool __fastcall HasClipboardValue();
	bool __fastcall HasSelectedText();
	bool __fastcall HasText();
	float __fastcall GetScreenScale();
	
public:
	__fastcall TAndroidTextInputContextMenu();
	void __fastcall Show(const Fmx::Types::_di_IControl AControl);
	void __fastcall Hide();
	bool __fastcall CanCut();
	bool __fastcall CanPaste();
	bool __fastcall CanCopy();
	bool __fastcall CanShare();
	bool __fastcall CanSelectAll();
	bool __cdecl onActionItemClicked(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item);
	bool __cdecl onCreateActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu);
	void __cdecl onDestroyActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode);
	bool __cdecl onPrepareActionMode(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JMenu menu);
	void __cdecl onGetContentRect(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JRect outRect);
	__property float ScreenScale = {read=GetScreenScale};
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidTextInputContextMenu() { }
	
private:
	void *__JOnTextContextMenuListener;	// Androidapi::Jni::Embarcadero::JOnTextContextMenuListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {614FBEA7-BD83-4F1E-9978-423DA86E95E3}
	operator Androidapi::Jni::Embarcadero::_di_JOnTextContextMenuListener()
	{
		Androidapi::Jni::Embarcadero::_di_JOnTextContextMenuListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Embarcadero::JOnTextContextMenuListener*(void) { return (Androidapi::Jni::Embarcadero::JOnTextContextMenuListener*)&__JOnTextContextMenuListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Text */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_TEXT_ANDROID)
using namespace Fmx::Platform::Text::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_TEXT)
using namespace Fmx::Platform::Text;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM)
using namespace Fmx::Platform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Platform_Text_AndroidHPP
