﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.CGIHTTP.pas' rev: 34.00 (Windows)

#ifndef Web_CgihttpHPP
#define Web_CgihttpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <Web.WebBroker.hpp>
#include <System.IniFiles.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Cgihttp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCGIRequest;
class DELPHICLASS TCGIResponse;
class DELPHICLASS TWinCGIRequest;
class DELPHICLASS TWinCGIResponse;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCGIRequest : public Web::Httpapp::TWebRequest
{
	typedef Web::Httpapp::TWebRequest inherited;
	
private:
#ifndef _WIN64
	System::DynamicArray<System::Byte> FBytesContent;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FBytesContent;
#endif /* _WIN64 */
	
protected:
	virtual System::UnicodeString __fastcall GetStringVariable(int Index);
	virtual System::TDateTime __fastcall GetDateVariable(int Index);
	virtual int __fastcall GetIntegerVariable(int Index);
#ifndef _WIN64
	virtual System::DynamicArray<System::Byte> __fastcall GetRawContent();
#else /* _WIN64 */
	virtual System::TArray__1<System::Byte> __fastcall GetRawContent();
#endif /* _WIN64 */
	virtual void __fastcall DoReadTotalContent();
	
public:
	__fastcall TCGIRequest();
	virtual System::UnicodeString __fastcall GetFieldByName(const System::UnicodeString Name);
	virtual int __fastcall ReadClient(void *Buffer, int Count);
	virtual System::UnicodeString __fastcall ReadString(int Count);
	virtual System::UnicodeString __fastcall TranslateURI(const System::UnicodeString URI);
	virtual int __fastcall WriteClient(void *Buffer, int Count);
	virtual bool __fastcall WriteString(const System::UnicodeString AString);
	virtual bool __fastcall WriteHeaders(int StatusCode, const System::UnicodeString StatusString, const System::UnicodeString Headers);
public:
	/* TWebRequest.Destroy */ inline __fastcall virtual ~TCGIRequest() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TCGIRequestClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TCGIRequestClass);
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TCGIResponse : public Web::Httpapp::TWebResponse
{
	typedef Web::Httpapp::TWebResponse inherited;
	
	
private:
	typedef System::StaticArray<System::UnicodeString, 12> _TCGIResponse__1;
	
	
private:
	int FStatusCode;
	_TCGIResponse__1 FStringVariables;
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
	__fastcall TCGIResponse(Web::Httpapp::TWebRequest* HTTPRequest);
	virtual void __fastcall SendResponse();
	virtual void __fastcall SendRedirect(const System::UnicodeString URI);
	virtual void __fastcall SendStream(System::Classes::TStream* AStream);
	virtual bool __fastcall Sent();
public:
	/* TWebResponse.Destroy */ inline __fastcall virtual ~TCGIResponse() { }
	
};


#ifndef _WIN64
typedef System::TMetaClass* TCGIResponseClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TCGIResponseClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWinCGIRequest : public TCGIRequest
{
	typedef TCGIRequest inherited;
	
private:
	System::Inifiles::TIniFile* FIniFile;
	System::Classes::TFileStream* FClientData;
	System::Classes::TFileStream* FServerData;
	
protected:
	virtual System::UnicodeString __fastcall GetStringVariable(int Index);
	
public:
	__fastcall TWinCGIRequest(System::UnicodeString IniFileName, System::UnicodeString ContentFile, System::UnicodeString OutputFile);
	__fastcall virtual ~TWinCGIRequest();
	virtual System::UnicodeString __fastcall GetFieldByName(const System::UnicodeString Name);
	virtual int __fastcall ReadClient(void *Buffer, int Count);
	virtual System::UnicodeString __fastcall ReadString(int Count);
	virtual int __fastcall WriteClient(void *Buffer, int Count);
	virtual bool __fastcall WriteString(const System::UnicodeString AString);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TWinCGIRequestClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TWinCGIRequestClass);
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TWinCGIResponse : public TCGIResponse
{
	typedef TCGIResponse inherited;
	
public:
	/* TCGIResponse.Create */ inline __fastcall TWinCGIResponse(Web::Httpapp::TWebRequest* HTTPRequest) : TCGIResponse(HTTPRequest) { }
	
public:
	/* TWebResponse.Destroy */ inline __fastcall virtual ~TWinCGIResponse() { }
	
};


#ifndef _WIN64
typedef System::TMetaClass* TWinCGIResponseClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TWinCGIResponseClass);
#endif /* _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Cgihttp */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_CGIHTTP)
using namespace Web::Cgihttp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_CgihttpHPP