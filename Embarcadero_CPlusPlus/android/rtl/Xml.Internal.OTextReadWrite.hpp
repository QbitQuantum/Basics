// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.OTextReadWrite.pas' rev: 34.00 (Android)

#ifndef Xml_Internal_OtextreadwriteHPP
#define Xml_Internal_OtextreadwriteHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Xml.Internal.OBufferedStreams.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Otextreadwrite
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TOTextReader;
class DELPHICLASS TOTextWriter;
class DELPHICLASS EOTextReader;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TOTextReader : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString fTempString;
	int fTempStringPosition;
	int fTempStringLength;
	int fTempStringRemain;
	int fBufferSize;
	System::Classes::TStream* fStream;
	NativeInt fStreamSize;
	NativeInt fStreamPosition;
	NativeInt fStreamStartPosition;
	bool fOwnsStream;
	int fFilePosition;
	int fLinePosition;
	int fLine;
	System::Sysutils::TEncoding* fEncoding;
	bool fOwnsEncoding;
	bool fBOMFound;
	bool fEOFi;
	System::WideChar fPreviousChar;
	bool fReadFromUndo;
	void __fastcall SetEncoding(System::Sysutils::TEncoding* const Value);
	NativeInt __fastcall GetApproxStreamPosition();
	void __fastcall LoadStringFromStream();
	
protected:
	virtual void __fastcall DoCreate(const int aBufferSize);
	virtual void __fastcall DoInit(System::Classes::TStream* const aNewStream, const bool aNewOwnsStream, System::Sysutils::TEncoding* const aDefaultEncoding);
	
public:
	__fastcall TOTextReader(const int aBufferSize)/* overload */;
	__fastcall TOTextReader(System::Classes::TStream* const aStream, System::Sysutils::TEncoding* const aDefaultEncoding, const int aBufferSize)/* overload */;
	__fastcall virtual ~TOTextReader();
	void __fastcall InitFile(const System::UnicodeString aFileName, System::Sysutils::TEncoding* const aDefaultEncoding = (System::Sysutils::TEncoding*)(0x0));
	void __fastcall InitStream(System::Classes::TStream* const aStream, System::Sysutils::TEncoding* const aDefaultEncoding = (System::Sysutils::TEncoding*)(0x0));
	void __fastcall InitString(const System::UnicodeString aString);
	void __fastcall InitBuffer(const System::TArray__1<System::Byte> aBuffer, System::Sysutils::TEncoding* const aDefaultEncoding = (System::Sysutils::TEncoding*)(0x0));
	void __fastcall ReleaseDocument();
	bool __fastcall ReadNextChar(System::WideChar &outChar);
	System::UnicodeString __fastcall ReadString(const int aMaxChars, const bool aBreakAtNewLine = false);
	System::UnicodeString __fastcall ReadPreviousString(const int aMaxChars, const bool aBreakAtNewLine = false);
	void __fastcall UndoRead();
	void __fastcall BlockFlushTempBuffer();
	void __fastcall UnblockFlushTempBuffer();
	__property System::Sysutils::TEncoding* Encoding = {read=fEncoding, write=SetEncoding};
	__property bool OwnsEncoding = {read=fOwnsEncoding, write=fOwnsEncoding, nodefault};
	__property bool BOMFound = {read=fBOMFound, nodefault};
	__property bool EOFi = {read=fEOFi, nodefault};
#ifndef __aarch64__
	__property NativeInt ApproxStreamPosition = {read=GetApproxStreamPosition, nodefault};
#else /* __aarch64__ */
	__property NativeInt ApproxStreamPosition = {read=GetApproxStreamPosition};
#endif /* __aarch64__ */
	__property int FilePosition = {read=fFilePosition, nodefault};
	__property int LinePosition = {read=fLinePosition, nodefault};
	__property int Line = {read=fLine, nodefault};
#ifndef __aarch64__
	__property NativeInt StreamSize = {read=fStreamSize, nodefault};
#else /* __aarch64__ */
	__property NativeInt StreamSize = {read=fStreamSize};
#endif /* __aarch64__ */
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TOTextWriter : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString fTempString;
	int fTempStringPosition;
	int fTempStringLength;
	System::Classes::TStream* fStream;
	bool fOwnsStream;
	System::Sysutils::TEncoding* fEncoding;
	bool fOwnsEncoding;
	bool fWriteBOM;
	bool fBOMWritten;
	void __fastcall WriteStringToStream(const System::UnicodeString aString, const int aMaxLength);
	void __fastcall SetEncoding(System::Sysutils::TEncoding* const Value);
	
protected:
	void __fastcall DoCreate(const int aBufferSize);
	void __fastcall DoInit(System::Classes::TStream* const aNewStream, const bool aNewOwnsStream, System::Sysutils::TEncoding* const aEncoding, const bool aWriteBOM);
	
public:
	__fastcall TOTextWriter(const int aCharBufferSize)/* overload */;
	__fastcall TOTextWriter(System::Classes::TStream* const aStream, System::Sysutils::TEncoding* const aEncoding, const bool aWriteBOM, const int aCharBufferSize)/* overload */;
	__fastcall virtual ~TOTextWriter();
	void __fastcall InitFile(const System::UnicodeString aFileName, System::Sysutils::TEncoding* const aEncoding = (System::Sysutils::TEncoding*)(0x0), const bool aWriteBOM = true);
	void __fastcall InitStream(System::Classes::TStream* const aStream, System::Sysutils::TEncoding* const aEncoding = (System::Sysutils::TEncoding*)(0x0), const bool aWriteBOM = true);
	void __fastcall ReleaseDocument();
	void __fastcall WriteString(const System::UnicodeString aString);
	void __fastcall WriteChar(const System::WideChar aChar);
	void __fastcall EnsureTempStringWritten();
	__property System::Sysutils::TEncoding* Encoding = {read=fEncoding, write=SetEncoding};
	__property bool OwnsEncoding = {read=fOwnsEncoding, write=fOwnsEncoding, nodefault};
	__property bool WriteBOM = {read=fWriteBOM, write=fWriteBOM, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EOTextReader : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EOTextReader(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EOTextReader(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EOTextReader(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EOTextReader(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EOTextReader(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EOTextReader(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EOTextReader(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EOTextReader(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EOTextReader(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EOTextReader(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EOTextReader(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EOTextReader(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EOTextReader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 TEncodingBuffer_FirstElement = System::Int8(0x0);
extern DELPHI_PACKAGE System::Sysutils::TEncoding* __fastcall GetEncodingFromStream(System::Classes::TStream* const aStream, NativeInt &ioTempStringPosition, const NativeInt aLastPosition, System::Sysutils::TEncoding* const aDefaultEncoding);
}	/* namespace Otextreadwrite */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_OTEXTREADWRITE)
using namespace Xml::Internal::Otextreadwrite;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL)
using namespace Xml::Internal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Internal_OtextreadwriteHPP
