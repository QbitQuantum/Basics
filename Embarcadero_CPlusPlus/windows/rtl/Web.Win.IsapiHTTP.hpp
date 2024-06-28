// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.Win.IsapiHTTP.pas' rev: 34.00 (Windows)

#ifndef Web_Win_IsapihttpHPP
#define Web_Win_IsapihttpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <Winapi.Isapi2.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Win
{
namespace Isapihttp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TISAPIRequest;
class DELPHICLASS TISAPIResponse;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TISAPIRequest : public Web::Httpapp::TWebRequest
{
	typedef Web::Httpapp::TWebRequest inherited;
	
private:
#ifndef _WIN64
	System::DynamicArray<System::Byte> FBytesContent;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FBytesContent;
#endif /* _WIN64 */
	Winapi::Isapi2::TEXTENSION_CONTROL_BLOCK *FECB;
	System::UTF8String __fastcall GetHost();
	System::UTF8String __fastcall GetFieldByNameA(const System::UnicodeString Name);
	
protected:
	virtual System::UnicodeString __fastcall GetStringVariable(int Index);
	virtual System::TDateTime __fastcall GetDateVariable(int Index);
	virtual int __fastcall GetIntegerVariable(int Index);
	virtual System::UnicodeString __fastcall GetRawPathInfo();
	virtual void __fastcall DoReadTotalContent();
#ifndef _WIN64
	virtual System::DynamicArray<System::Byte> __fastcall GetRawContent();
#else /* _WIN64 */
	virtual System::TArray__1<System::Byte> __fastcall GetRawContent();
#endif /* _WIN64 */
	
public:
	__fastcall TISAPIRequest(Winapi::Isapi2::PEXTENSION_CONTROL_BLOCK AECB);
	virtual System::UnicodeString __fastcall GetFieldByName(const System::UnicodeString Name);
	virtual int __fastcall ReadClient(void *Buffer, int Count);
	virtual System::UnicodeString __fastcall ReadString(int Count);
	virtual System::UnicodeString __fastcall TranslateURI(const System::UnicodeString URI);
	virtual int __fastcall WriteClient(void *Buffer, int Count);
	virtual bool __fastcall WriteString(const System::UnicodeString AString);
	virtual bool __fastcall WriteHeaders(int StatusCode, const System::UnicodeString StatusString, const System::UnicodeString Headers);
	__property Winapi::Isapi2::PEXTENSION_CONTROL_BLOCK ECB = {read=FECB};
public:
	/* TWebRequest.Destroy */ inline __fastcall virtual ~TISAPIRequest() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TISAPIResponse : public Web::Httpapp::TWebResponse
{
	typedef Web::Httpapp::TWebResponse inherited;
	
	
private:
	typedef System::StaticArray<System::UTF8String, 12> _TISAPIResponse__1;
	
	
private:
	int FStatusCode;
	_TISAPIResponse__1 FStringVariables;
	System::StaticArray<int, 1> FIntegerVariables;
	System::StaticArray<System::TDateTime, 3> FDateVariables;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FBytesContent;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FBytesContent;
#endif /* _WIN64 */
	bool FSent;
	
protected:
	virtual System::UnicodeString __fastcall GetContent();
	virtual System::TDateTime __fastcall GetDateVariable(int Index);
	virtual int __fastcall GetIntegerVariable(int Index);
	virtual System::UnicodeString __fastcall GetLogMessage();
	virtual int __fastcall GetStatusCode();
	virtual System::UnicodeString __fastcall GetStringVariable(int Index);
	virtual void __fastcall SetContent(const System::UnicodeString Value);
	virtual void __fastcall SetDateVariable(int Index, const System::TDateTime Value);
	virtual void __fastcall SetIntegerVariable(int Index, int Value);
	virtual void __fastcall SetLogMessage(const System::UnicodeString Value);
	virtual void __fastcall SetStatusCode(int Value);
	virtual void __fastcall SetStringVariable(int Index, const System::UnicodeString Value);
	virtual void __fastcall InitResponse();
	
public:
	__fastcall TISAPIResponse(Web::Httpapp::TWebRequest* HTTPRequest);
	virtual void __fastcall SendResponse();
	virtual void __fastcall SendRedirect(const System::UnicodeString URI);
	virtual void __fastcall SendStream(System::Classes::TStream* AStream);
	virtual bool __fastcall Sent();
public:
	/* TWebResponse.Destroy */ inline __fastcall virtual ~TISAPIResponse() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Isapihttp */
}	/* namespace Win */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_WIN_ISAPIHTTP)
using namespace Web::Win::Isapihttp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_WIN)
using namespace Web::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_Win_IsapihttpHPP
