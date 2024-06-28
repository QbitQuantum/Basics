// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Authenticator.OAuth.WebForm.FMX.pas' rev: 34.00 (Windows)

#ifndef Rest_Authenticator_Oauth_Webform_FmxHPP
#define Rest_Authenticator_Oauth_Webform_FmxHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Classes.hpp>
#include <System.Variants.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.WebBrowser.hpp>
#include <FMX.StdCtrls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Authenticator
{
namespace Oauth
{
namespace Webform
{
namespace Fmx
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TOAuth2WebFormRedirectEvent)(const System::UnicodeString AURL, bool &DoCloseWebView);

typedef void __fastcall (__closure *TOAuth2WebFormTitleChangedEvent)(const System::UnicodeString ATitle, bool &DoCloseWebView);

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fmx */
}	/* namespace Webform */
}	/* namespace Oauth */
}	/* namespace Authenticator */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_AUTHENTICATOR_OAUTH_WEBFORM_FMX)
using namespace Rest::Authenticator::Oauth::Webform::Fmx;
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
#endif	// Rest_Authenticator_Oauth_Webform_FmxHPP
