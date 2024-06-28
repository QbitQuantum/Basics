// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.AutoDisp.pas' rev: 34.00 (Android)

#ifndef Web_AutodispHPP
#define Web_AutodispHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <System.Masks.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Autodisp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWebDispatch;
class DELPHICLASS TWebPathInfo;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWebDispatch : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TWebPathInfo* FPathInfo;
	Web::Httpapp::TMethodType FMethodType;
	bool FEnabled;
	System::Masks::TMask* __fastcall GetMask();
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual void __fastcall SetPathInfo(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetPathInfo();
	
public:
	__fastcall TWebDispatch(System::Classes::TComponent* AComponent);
	__fastcall virtual ~TWebDispatch();
	__property System::Masks::TMask* Mask = {read=GetMask};
	
__published:
	__property bool Enabled = {read=FEnabled, write=FEnabled, default=1};
	__property Web::Httpapp::TMethodType MethodType = {read=FMethodType, write=FMethodType, default=3};
	__property System::UnicodeString PathInfo = {read=GetPathInfo, write=SetPathInfo};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWebPathInfo : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Masks::TMask* FMask;
	System::UnicodeString FMaskPathInfo;
	System::UnicodeString FPathInfo;
	System::Classes::TComponent* FOwner;
	System::Masks::TMask* __fastcall GetMask();
	System::UnicodeString __fastcall GetPathInfo();
	void __fastcall SetPathInfo(const System::UnicodeString Value);
	
public:
	__fastcall TWebPathInfo(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWebPathInfo();
	__property System::Masks::TMask* Mask = {read=GetMask};
	__property System::UnicodeString PathInfo = {read=GetPathInfo, write=SetPathInfo};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Autodisp */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_AUTODISP)
using namespace Web::Autodisp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_AutodispHPP
