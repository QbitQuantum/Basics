// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.ParserUtilsWin32.pas' rev: 34.00 (iOS)

#ifndef Xml_Internal_Parserutilswin32HPP
#define Xml_Internal_Parserutilswin32HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Xml.Internal.CodecUtilsWin32.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Parserutilswin32
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EParserUtilsException;
class DELPHICLASS TUtilsCustomInputStream;
class DELPHICLASS TUtilsCustomOutputStream;
class DELPHICLASS TUtilsCustomAutodetectInputStream;
class DELPHICLASS TUtilsAutodetectInputStream;
struct TUtilsUCS4CharData;
class DELPHICLASS TUtilsUCS4Reader;
class DELPHICLASS TUtilsCustomTranscoder;
class DELPHICLASS TUtilsStandardTranscoder;
class DELPHICLASS TUtilsStreamTranscoder;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EParserUtilsException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EParserUtilsException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EParserUtilsException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EParserUtilsException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EParserUtilsException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EParserUtilsException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EParserUtilsException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EParserUtilsException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EParserUtilsException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EParserUtilsException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EParserUtilsException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EParserUtilsException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EParserUtilsException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EParserUtilsException() { }
	
};


class PASCALIMPLEMENTATION TUtilsCustomInputStream : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStream* FStream;
	char *FBuffer;
	__int64 FInitialStreamPosition;
	__int64 FPosition;
	__int64 FRemaining;
	int FBufSize;
	
protected:
	virtual __int64 __fastcall GetPosition();
	virtual bool __fastcall Read(void *Buf, const long Count);
	virtual void __fastcall SetPosition(__int64 Value);
	__property int BufSize = {read=FBufSize, nodefault};
	__property __int64 InitialStreamPosition = {read=FInitialStreamPosition};
	__property __int64 Position = {read=GetPosition, write=SetPosition};
	
public:
	__fastcall TUtilsCustomInputStream(System::Classes::TStream* const Stream, const int BufSize);
	__fastcall virtual ~TUtilsCustomInputStream();
	virtual void __fastcall FlushBuffer();
};


class PASCALIMPLEMENTATION TUtilsCustomOutputStream : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStream* FStream;
	char *FBuffer;
	__int64 FInitialStreamPosition;
	__int64 FPosition;
	int FBufSize;
	
protected:
	virtual __int64 __fastcall GetPosition();
	virtual void __fastcall SetPosition(__int64 Value);
	virtual void __fastcall Write(const void *Buf, const long Count);
	__property int BufSize = {read=FBufSize, nodefault};
	__property __int64 InitialStreamPosition = {read=FInitialStreamPosition};
	__property __int64 Position = {read=GetPosition, write=SetPosition};
	
public:
	__fastcall TUtilsCustomOutputStream(System::Classes::TStream* const Stream, const int BufSize);
	__fastcall virtual ~TUtilsCustomOutputStream();
	virtual void __fastcall FlushBuffer();
};


class PASCALIMPLEMENTATION TUtilsCustomAutodetectInputStream : public TUtilsCustomInputStream
{
	typedef TUtilsCustomInputStream inherited;
	
private:
	unsigned FByteOrderMarkSize;
	Xml::Internal::Codecutilswin32::TUnicodeCodec* FCodec;
	void __fastcall Reset();
	
protected:
	virtual __int64 __fastcall GetPosition();
	virtual void __fastcall SetPosition(__int64 Value);
	__property unsigned ByteOrderMarkSize = {read=FByteOrderMarkSize, nodefault};
	
public:
	__fastcall TUtilsCustomAutodetectInputStream(System::Classes::TStream* const Stream, const int BufSize, const System::UnicodeString ExpectedEncoding, const System::UnicodeString DefaultEncoding);
	__fastcall virtual ~TUtilsCustomAutodetectInputStream();
	__property BufSize;
	__property Xml::Internal::Codecutilswin32::TUnicodeCodec* Codec = {read=FCodec};
};


class PASCALIMPLEMENTATION TUtilsAutodetectInputStream : public TUtilsCustomAutodetectInputStream
{
	typedef TUtilsCustomAutodetectInputStream inherited;
	
protected:
	void __fastcall ChangeEncoding(const System::UnicodeString AEncoding);
	virtual bool __fastcall GetHasByteOrderMark();
	
public:
	__property Position;
	__property bool HasByteOrderMark = {read=GetHasByteOrderMark, nodefault};
public:
	/* TUtilsCustomAutodetectInputStream.Create */ inline __fastcall TUtilsAutodetectInputStream(System::Classes::TStream* const Stream, const int BufSize, const System::UnicodeString ExpectedEncoding, const System::UnicodeString DefaultEncoding) : TUtilsCustomAutodetectInputStream(Stream, BufSize, ExpectedEncoding, DefaultEncoding) { }
	/* TUtilsCustomAutodetectInputStream.Destroy */ inline __fastcall virtual ~TUtilsAutodetectInputStream() { }
	
};


struct DECLSPEC_DRECORD TUtilsUCS4CharData
{
public:
	__int64 ByteCount;
	__int64 CharCount;
	__int64 CharsInLine;
	unsigned CodePoint;
	__int64 Line;
	unsigned Size;
	__int64 TabsInLine;
};


class PASCALIMPLEMENTATION TUtilsUCS4Reader : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Xml::Internal::Codecutilswin32::TUnicodeCodec* FCodec;
	TUtilsUCS4CharData FCurrentUCS4Char;
	TUtilsAutodetectInputStream* FInternalInputStream;
	TUtilsUCS4CharData FInitialUCS4CharData;
	TUtilsUCS4CharData FNextUCS4Char;
	TUtilsUCS4CharData FPreviousUCS4Char;
	__int64 FResetPosition;
	bool __fastcall GetBof();
	int __fastcall GetBufSize();
	bool __fastcall GetEof();
	bool __fastcall GetHasByteOrderMark();
	__int64 __fastcall GetPosition();
	Xml::Internal::Codecutilswin32::TCodecReadLFOption __fastcall GetReadLFOption();
	void __fastcall SetReadLFOption(const Xml::Internal::Codecutilswin32::TCodecReadLFOption Value);
	void __fastcall UpdateLocator(TUtilsUCS4CharData &UCS4CharData);
	
protected:
	virtual Xml::Internal::Codecutilswin32::TUnicodeCodec* __fastcall GetCodec();
	virtual System::UnicodeString __fastcall GetDefaultEncoding();
	virtual void __fastcall ReadEventHandler(System::TObject* const Sender, void *Buf, long Count, bool &Ok);
	void __fastcall SetEncoding(const System::UnicodeString Value);
	virtual void __fastcall SetResetPosition(const __int64 Value);
	__property Xml::Internal::Codecutilswin32::TUnicodeCodec* Codec = {read=GetCodec};
	__property System::UnicodeString DefaultEncoding = {read=GetDefaultEncoding};
	__property TUtilsAutodetectInputStream* InternalInputStream = {read=FInternalInputStream};
	__property TUtilsUCS4CharData InitialUCS4CharData = {read=FInitialUCS4CharData, write=FInitialUCS4CharData};
	__property __int64 Position = {read=GetPosition};
	__property Xml::Internal::Codecutilswin32::TCodecReadLFOption ReadLFOption = {read=GetReadLFOption, write=SetReadLFOption, default=1};
	__property __int64 ResetPosition = {read=FResetPosition, write=SetResetPosition};
	
public:
	__fastcall TUtilsUCS4Reader(System::Classes::TStream* const Stream, const int ABufSize, const System::UnicodeString AEncoding, const __int64 InitialByteCount, const __int64 InitialCharCount, const __int64 InitialCharsInLine, const __int64 InitialTabsInLine, const __int64 InitialLine);
	__fastcall virtual ~TUtilsUCS4Reader();
	virtual bool __fastcall Match(System::WideString Ucs2Str);
	virtual void __fastcall Next();
	virtual void __fastcall Reset();
	virtual int __fastcall SkipNext(System::WideString Ucs2Str);
	__property bool Bof = {read=GetBof, nodefault};
	__property int BufSize = {read=GetBufSize, nodefault};
	__property TUtilsUCS4CharData CurrentCharInfo = {read=FCurrentUCS4Char};
	__property bool Eof = {read=GetEof, nodefault};
	__property bool HasByteOrderMark = {read=GetHasByteOrderMark, nodefault};
	__property TUtilsUCS4CharData NextCharInfo = {read=FNextUCS4Char};
	__property TUtilsUCS4CharData PreviousCharInfo = {read=FPreviousUCS4Char};
};


enum DECLSPEC_DENUM TUtilsLineBreakOpt : unsigned char { lbCRLF, lbCR, lbLF, lbNone };

class PASCALIMPLEMENTATION TUtilsCustomTranscoder : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Xml::Internal::Codecutilswin32::TUnicodeCodec* FInputCodec;
	System::UnicodeString FInputEncoding;
	TUtilsLineBreakOpt FLineBreakOpt;
	Xml::Internal::Codecutilswin32::TUnicodeCodec* FOutputCodec;
	System::UnicodeString FOutputEncoding;
	System::Classes::TNotifyEvent FOnProgress;
	void __fastcall SetInputEncoding(const System::UnicodeString Value);
	void __fastcall SetLineBreakOpt(const TUtilsLineBreakOpt Value);
	void __fastcall SetOutputEncoding(const System::UnicodeString Value);
	void __fastcall UpdateLineBreakOpt();
	
protected:
	bool FBusy;
	virtual void __fastcall CodecReadEventHandler(System::TObject* const Sender, void *Buf, long Count, bool &Ok);
	virtual void __fastcall CodecWriteEventHandler(System::TObject* const Sender, const void *Buf, long Count);
	virtual void __fastcall DoProgress();
	__property bool Busy = {read=FBusy, nodefault};
	__property Xml::Internal::Codecutilswin32::TUnicodeCodec* InputCodec = {read=FInputCodec};
	__property System::UnicodeString InputEncoding = {read=FInputEncoding, write=SetInputEncoding};
	__property TUtilsLineBreakOpt LineBreakOpt = {read=FLineBreakOpt, write=SetLineBreakOpt, default=3};
	__property Xml::Internal::Codecutilswin32::TUnicodeCodec* OutputCodec = {read=FOutputCodec};
	__property System::UnicodeString OutputEncoding = {read=FOutputEncoding, write=SetOutputEncoding};
	__property System::Classes::TNotifyEvent OnProgress = {read=FOnProgress, write=FOnProgress};
	
public:
	__fastcall TUtilsCustomTranscoder();
	__fastcall virtual ~TUtilsCustomTranscoder();
	virtual void __fastcall Transcode();
};


class PASCALIMPLEMENTATION TUtilsStandardTranscoder : public TUtilsCustomTranscoder
{
	typedef TUtilsCustomTranscoder inherited;
	
private:
	Xml::Internal::Codecutilswin32::TCodecReadEvent FOnRead;
	Xml::Internal::Codecutilswin32::TCodecWriteEvent FOnWrite;
	
protected:
	virtual void __fastcall CodecReadEventHandler(System::TObject* const Sender, void *Buf, long Count, bool &Ok);
	virtual void __fastcall CodecWriteEventHandler(System::TObject* const Sender, const void *Buf, long Count);
	
public:
	__property Busy;
	__property InputEncoding = {default=0};
	__property LineBreakOpt = {default=3};
	__property OutputEncoding = {default=0};
	__property OnProgress;
	__property Xml::Internal::Codecutilswin32::TCodecReadEvent OnRead = {read=FOnRead, write=FOnRead};
	__property Xml::Internal::Codecutilswin32::TCodecWriteEvent OnWrite = {read=FOnWrite, write=FOnWrite};
public:
	/* TUtilsCustomTranscoder.Create */ inline __fastcall TUtilsStandardTranscoder() : TUtilsCustomTranscoder() { }
	/* TUtilsCustomTranscoder.Destroy */ inline __fastcall virtual ~TUtilsStandardTranscoder() { }
	
};


class PASCALIMPLEMENTATION TUtilsStreamTranscoder : public TUtilsCustomTranscoder
{
	typedef TUtilsCustomTranscoder inherited;
	
private:
	TUtilsCustomInputStream* FReader;
	TUtilsCustomOutputStream* FWriter;
	
protected:
	virtual void __fastcall CodecReadEventHandler(System::TObject* const Sender, void *Buf, long Count, bool &Ok);
	virtual void __fastcall CodecWriteEventHandler(System::TObject* const Sender, const void *Buf, long Count);
	
public:
	__fastcall TUtilsStreamTranscoder(System::Classes::TStream* const InputStream, System::Classes::TStream* const OutputStream, const int BufSize);
	__fastcall virtual ~TUtilsStreamTranscoder();
	__property Busy;
	__property InputEncoding = {default=0};
	__property LineBreakOpt = {default=3};
	__property OutputEncoding = {default=0};
	__property OnProgress;
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::WideString __fastcall ConvertToUTF16(const System::UnicodeString SourceEncoding, const System::AnsiString S);
extern DELPHI_PACKAGE System::AnsiString __fastcall ConvertFromUTF16(const System::UnicodeString TargetEncoding, const System::WideString S);
}	/* namespace Parserutilswin32 */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_PARSERUTILSWIN32)
using namespace Xml::Internal::Parserutilswin32;
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
#endif	// Xml_Internal_Parserutilswin32HPP
