// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Authenticator.OAuth.WebForm.Win.pas' rev: 34.00 (Windows)

#ifndef Rest_Authenticator_Oauth_Webform_WinHPP
#define Rest_Authenticator_Oauth_Webform_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Variants.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.OleCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <SHDocVw.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Authenticator
{
namespace Oauth
{
namespace Webform
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS Tfrm_OAuthWebForm;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TOAuth2WebFormRedirectEvent)(const System::UnicodeString AURL, bool &DoCloseWebView);

typedef void __fastcall (__closure *TOAuth2WebFormTitleChangedEvent)(const System::UnicodeString ATitle, bool &DoCloseWebView);

class PASCALIMPLEMENTATION Tfrm_OAuthWebForm : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TBevel* Bevel1;
	Vcl::Stdctrls::TButton* btn_Close;
	Shdocvw::TWebBrowser* Browser;
	Vcl::Stdctrls::TLabel* Label1;
	void __fastcall FormKeyPress(System::TObject* Sender, System::WideChar &Key);
	void __fastcall BrowserTitleChange(System::TObject* ASender, const System::WideString Text);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall BrowserNavigateComplete2(System::TObject* ASender, const _di_IDispatch pDisp, const System::OleVariant &URL);
	void __fastcall BrowserBeforeNavigate2(System::TObject* ASender, const _di_IDispatch pDisp, const System::OleVariant &URL, const System::OleVariant &Flags, const System::OleVariant &TargetFrameName, const System::OleVariant &PostData, const System::OleVariant &Headers, System::WordBool &Cancel);
	
private:
	TOAuth2WebFormRedirectEvent FOnBeforeRedirect;
	TOAuth2WebFormRedirectEvent FOnAfterRedirect;
	TOAuth2WebFormTitleChangedEvent FOnBrowserTitleChanged;
	System::UnicodeString FLastTitle;
	System::UnicodeString FLastURL;
	
public:
	void __fastcall ShowWithURL(const System::UnicodeString AURL);
	void __fastcall ShowModalWithURL(const System::UnicodeString AURL);
	__property System::UnicodeString LastTitle = {read=FLastTitle};
	__property System::UnicodeString LastURL = {read=FLastURL};
	__property TOAuth2WebFormRedirectEvent OnAfterRedirect = {read=FOnAfterRedirect, write=FOnAfterRedirect};
	__property TOAuth2WebFormRedirectEvent OnBeforeRedirect = {read=FOnBeforeRedirect, write=FOnBeforeRedirect};
	__property TOAuth2WebFormTitleChangedEvent OnTitleChanged = {read=FOnBrowserTitleChanged, write=FOnBrowserTitleChanged};
public:
	/* TCustomForm.Create */ inline __fastcall virtual Tfrm_OAuthWebForm(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual Tfrm_OAuthWebForm(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~Tfrm_OAuthWebForm() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall Tfrm_OAuthWebForm(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Tfrm_OAuthWebForm* frm_OAuthWebForm;
}	/* namespace Win */
}	/* namespace Webform */
}	/* namespace Oauth */
}	/* namespace Authenticator */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_AUTHENTICATOR_OAUTH_WEBFORM_WIN)
using namespace Rest::Authenticator::Oauth::Webform::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_AUTHENTICATOR_OAUTH_WEBFORM)
using namespace Rest::Authenticator::Oauth::Webform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_AUTHENTICATOR_OAUTH)
using namespace Rest::Authenticator::Oauth;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_AUTHENTICATOR)
using namespace Rest::Authenticator;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_Authenticator_Oauth_Webform_WinHPP
