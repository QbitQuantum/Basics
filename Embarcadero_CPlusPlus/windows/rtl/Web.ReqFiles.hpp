// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.ReqFiles.pas' rev: 34.00 (Windows)

#ifndef Web_ReqfilesHPP
#define Web_ReqfilesHPP

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
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Reqfiles
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWebRequestFile;
class DELPHICLASS TWebRequestFiles;
class DELPHICLASS TWebRequestFileStream;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWebRequestFile : public Web::Httpapp::TAbstractWebRequestFile
{
	typedef Web::Httpapp::TAbstractWebRequestFile inherited;
	
private:
	System::UnicodeString FFieldName;
	System::UnicodeString FFileName;
	System::Classes::TStream* FStream;
	System::UnicodeString FContentType;
	
protected:
	virtual System::UnicodeString __fastcall GetFieldName();
	virtual System::UnicodeString __fastcall GetFileName();
	virtual System::Classes::TStream* __fastcall GetStream();
	virtual System::UnicodeString __fastcall GetContentType();
	
public:
	__fastcall TWebRequestFile(const System::UnicodeString AFieldName, const System::UnicodeString AFileName, const System::UnicodeString AContentType, void * AContent, int AContentLength);
	__fastcall virtual ~TWebRequestFile();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWebRequestFiles : public Web::Httpapp::TAbstractWebRequestFiles
{
	typedef Web::Httpapp::TAbstractWebRequestFiles inherited;
	
private:
	System::Generics::Collections::TObjectList__1<TWebRequestFile*>* FList;
	
protected:
	virtual int __fastcall GetCount();
	virtual Web::Httpapp::TAbstractWebRequestFile* __fastcall GetItem(int I);
	
public:
	__fastcall TWebRequestFiles();
	__fastcall virtual ~TWebRequestFiles();
	void __fastcall Add(const System::UnicodeString AName, const System::UnicodeString AFileName, const System::UnicodeString AContentType, void * AContent, int AContentLength)/* overload */;
	void __fastcall Add(TWebRequestFile* AFile)/* overload */;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWebRequestFileStream : public System::Classes::TCustomMemoryStream
{
	typedef System::Classes::TCustomMemoryStream inherited;
	
public:
	__fastcall TWebRequestFileStream(void * ABuffer, int Size);
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWebRequestFileStream() { }
	
	/* Hoisted overloads: */
	
public:
#ifndef _WIN64
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#else /* _WIN64 */
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#endif /* _WIN64 */
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Reqfiles */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_REQFILES)
using namespace Web::Reqfiles;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_ReqfilesHPP
