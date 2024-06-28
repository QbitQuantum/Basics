// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Zip.pas' rev: 34.00 (Windows)

#ifndef System_ZipHPP
#define System_ZipHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.IOUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Zip
{
//-- forward type declarations -----------------------------------------------
struct TZipEndOfCentralHeader;
struct TZipHeader;
class DELPHICLASS EZipException;
__interface DELPHIINTERFACE TStreamConstructor;
typedef System::DelphiInterface<TStreamConstructor> _di_TStreamConstructor;
__interface DELPHIINTERFACE TCreateCustomStreamCallBack;
typedef System::DelphiInterface<TCreateCustomStreamCallBack> _di_TCreateCustomStreamCallBack;
class DELPHICLASS TZipFile;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TZipCompression : unsigned char { zcStored, zcShrunk, zcReduce1, zcReduce2, zcReduce3, zcReduce4, zcImplode, zcTokenize, zcDeflate, zcDeflate64, zcPKImplode, zcBZIP2 = 12, zcLZMA = 14, zcTERSE = 18, zcLZ77, zcWavePack = 97, zcPPMdI1 };

#pragma pack(push,1)
struct DECLSPEC_DRECORD TZipEndOfCentralHeader
{
public:
	System::Word DiskNumber;
	System::Word CentralDirStartDisk;
	System::Word NumEntriesThisDisk;
	System::Word CentralDirEntries;
	unsigned CentralDirSize;
	unsigned CentralDirOffset;
	System::Word CommentLength;
};
#pragma pack(pop)


#pragma pack(push,1)
struct DECLSPEC_DRECORD TZipHeader
{
public:
	System::Word MadeByVersion;
	System::Word RequiredVersion;
	System::Word Flag;
	System::Word CompressionMethod;
	unsigned ModifiedDateTime;
	unsigned CRC32;
	unsigned CompressedSize;
	unsigned UncompressedSize;
	System::Word FileNameLength;
	System::Word ExtraFieldLength;
	System::Word FileCommentLength;
	System::Word DiskNumberStart;
	System::Word InternalAttributes;
	unsigned ExternalAttributes;
	unsigned LocalHeaderOffset;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FileName;
	System::DynamicArray<System::Byte> ExtraField;
	System::DynamicArray<System::Byte> FileComment;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FileName;
	System::TArray__1<System::Byte> ExtraField;
	System::TArray__1<System::Byte> FileComment;
#endif /* _WIN64 */
	bool __fastcall GetUTF8Support();
	void __fastcall SetUTF8Support(bool value);
	__property bool UTF8Support = {read=GetUTF8Support, write=SetUTF8Support};
};
#pragma pack(pop)


typedef TZipHeader *PZipHeader;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EZipException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EZipException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EZipException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EZipException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EZipException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EZipException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EZipException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EZipException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EZipException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EZipException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EZipException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EZipException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EZipException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EZipException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TZipMode : unsigned char { zmClosed, zmRead, zmReadWrite, zmWrite };

typedef void __fastcall (__closure *TZipProgressEvent)(System::TObject* Sender, System::UnicodeString FileName, const TZipHeader &Header, __int64 Position);

__interface TStreamConstructor  : public System::IInterface 
{
	virtual System::Classes::TStream* __fastcall Invoke(System::Classes::TStream* InStream, TZipFile* const ZipFile, const TZipHeader &Item) = 0 ;
};

__interface TCreateCustomStreamCallBack  : public System::IInterface 
{
	virtual System::Classes::TStream* __fastcall Invoke(System::Classes::TStream* const InStream, TZipFile* const ZipFile, const TZipHeader &Item, bool IsEncrypted) = 0 ;
};

typedef System::Classes::TStream* __fastcall (__closure *TOnCreateCustomStream)(System::Classes::TStream* const InStream, TZipFile* const ZipFile, const TZipHeader &Item, bool IsEncrypted);

class PASCALIMPLEMENTATION TZipFile : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::Generics::Collections::TDictionary__2<TZipCompression,System::Generics::Collections::TPair__2<_di_TStreamConstructor,_di_TStreamConstructor> >* TCompressionDict;
	
	
private:
	static System::Generics::Collections::TDictionary__2<TZipCompression,System::Generics::Collections::TPair__2<_di_TStreamConstructor,_di_TStreamConstructor> >* FCompressionHandler;
	static TOnCreateCustomStream FOnCreateDecompressStream;
	static _di_TCreateCustomStreamCallBack FCreateDecompressStreamCallBack;
	
protected:
	static System::Sysutils::TEncoding* FCP437Encoding;
	
private:
	TZipMode FMode;
	System::Classes::TStream* FStream;
	System::Classes::TFileStream* FFileStream;
	__int64 FStartFileData;
	__int64 FEndFileData;
	System::Generics::Collections::TList__1<TZipHeader>* FFiles;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FComment;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FComment;
#endif /* _WIN64 */
	System::Sysutils::TEncoding* FEncoding;
	bool FUTF8Support;
	TZipProgressEvent FOnProgress;
	System::UnicodeString FCurrentFile;
	TZipHeader FCurrentHeader;
	virtual System::Sysutils::TEncoding* __fastcall GetEncoding();
	int __fastcall GetFileCount();
	TZipHeader __fastcall GetFileInfo(int Index);
#ifndef _WIN64
	System::DynamicArray<TZipHeader> __fastcall GetFileInfos();
#else /* _WIN64 */
	System::TArray__1<TZipHeader> __fastcall GetFileInfos();
#endif /* _WIN64 */
	System::UnicodeString __fastcall GetFileName(int Index);
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall GetFileNames();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall GetFileNames();
#endif /* _WIN64 */
	void __fastcall ReadCentralHeader();
	void __fastcall SetUTF8Support(const bool Value);
	bool __fastcall LocateEndOfCentralHeader(TZipEndOfCentralHeader &Header);
	void __fastcall DoZLibProgress(System::TObject* Sender);
	
protected:
	virtual System::UnicodeString __fastcall InternalGetFileName(int Index);
	virtual void __fastcall CheckFileName(const System::UnicodeString ArchiveFileName);
	virtual System::UnicodeString __fastcall GetComment();
	virtual System::UnicodeString __fastcall GetFileComment(int Index);
	virtual System::Sysutils::TEncoding* __fastcall GetTextEncode(const TZipHeader &Header);
	virtual void __fastcall SetComment(System::UnicodeString Value);
	virtual void __fastcall SetFileComment(int Index, System::UnicodeString Value);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	__classmethod void __fastcall RegisterCompressionHandler(TZipCompression Compression, _di_TStreamConstructor CompressStream, _di_TStreamConstructor DecompressStream);
	static bool __fastcall IsValid(const System::UnicodeString ZipFileName);
	static void __fastcall ExtractZipFile(const System::UnicodeString ZipFileName, const System::UnicodeString Path, TZipProgressEvent ZipProgress = 0x0)/* overload */;
	static void __fastcall ExtractZipFile(const System::UnicodeString ZipFileName, const System::UnicodeString Path, System::Sysutils::TEncoding* const Encoding, TZipProgressEvent ZipProgress = 0x0)/* overload */;
	static void __fastcall ZipDirectoryContents(const System::UnicodeString ZipFileName, const System::UnicodeString Path, TZipCompression Compression = (TZipCompression)(0x8), TZipProgressEvent ZipProgress = 0x0)/* overload */;
	static void __fastcall ZipDirectoryContents(const System::UnicodeString ZipFileName, const System::UnicodeString Path, System::Sysutils::TEncoding* const Encoding, TZipCompression Compression = (TZipCompression)(0x8), TZipProgressEvent ZipProgress = 0x0)/* overload */;
	__classmethod bool __fastcall GetUTF8PathFromExtraField(const TZipHeader &AHeader, /* out */ System::UnicodeString &AFileName);
	__fastcall TZipFile();
	__fastcall virtual ~TZipFile();
	void __fastcall Open(const System::UnicodeString ZipFileName, TZipMode OpenMode)/* overload */;
	void __fastcall Open(System::Classes::TStream* ZipFileStream, TZipMode OpenMode)/* overload */;
	void __fastcall Close();
	void __fastcall Extract(const System::UnicodeString FileName, const System::UnicodeString Path = System::UnicodeString(), bool CreateSubdirs = true)/* overload */;
	void __fastcall Extract(int Index, const System::UnicodeString Path = System::UnicodeString(), bool CreateSubdirs = true)/* overload */;
	void __fastcall ExtractAll(const System::UnicodeString Path = System::UnicodeString());
#ifndef _WIN64
	void __fastcall Read(const System::UnicodeString FileName, /* out */ System::DynamicArray<System::Byte> &Bytes)/* overload */;
	void __fastcall Read(int Index, /* out */ System::DynamicArray<System::Byte> &Bytes)/* overload */;
#else /* _WIN64 */
	void __fastcall Read(const System::UnicodeString FileName, /* out */ System::TArray__1<System::Byte> &Bytes)/* overload */;
	void __fastcall Read(int Index, /* out */ System::TArray__1<System::Byte> &Bytes)/* overload */;
#endif /* _WIN64 */
	void __fastcall Read(const System::UnicodeString FileName, /* out */ System::Classes::TStream* &Stream, /* out */ TZipHeader &LocalHeader)/* overload */;
	void __fastcall Read(int Index, /* out */ System::Classes::TStream* &Stream, /* out */ TZipHeader &LocalHeader)/* overload */;
	void __fastcall Add(const System::UnicodeString FileName, const System::UnicodeString ArchiveFileName = System::UnicodeString(), TZipCompression Compression = (TZipCompression)(0x8))/* overload */;
#ifndef _WIN64
	void __fastcall Add(System::DynamicArray<System::Byte> Data, const System::UnicodeString ArchiveFileName, TZipCompression Compression = (TZipCompression)(0x8))/* overload */;
#else /* _WIN64 */
	void __fastcall Add(System::TArray__1<System::Byte> Data, const System::UnicodeString ArchiveFileName, TZipCompression Compression = (TZipCompression)(0x8))/* overload */;
#endif /* _WIN64 */
	void __fastcall Add(System::Classes::TStream* Data, const System::UnicodeString ArchiveFileName, TZipCompression Compression = (TZipCompression)(0x8), System::Ioutils::TFileAttributes AExternalAttributes = System::Ioutils::TFileAttributes() )/* overload */;
	void __fastcall Add(System::Classes::TStream* Data, const TZipHeader &LocalHeader, PZipHeader CentralHeader = (PZipHeader)(0x0))/* overload */;
	/* static */ __property TOnCreateCustomStream OnCreateDecompressStream = {read=FOnCreateDecompressStream, write=FOnCreateDecompressStream};
	/* static */ __property _di_TCreateCustomStreamCallBack CreateDecompressStreamCallBack = {read=FCreateDecompressStreamCallBack, write=FCreateDecompressStreamCallBack};
	int __fastcall IndexOf(const System::UnicodeString FileName);
	__property TZipMode Mode = {read=FMode, nodefault};
	__property int FileCount = {read=GetFileCount, nodefault};
#ifndef _WIN64
	__property System::DynamicArray<System::UnicodeString> FileNames = {read=GetFileNames};
	__property System::DynamicArray<TZipHeader> FileInfos = {read=GetFileInfos};
#else /* _WIN64 */
	__property System::TArray__1<System::UnicodeString> FileNames = {read=GetFileNames};
	__property System::TArray__1<TZipHeader> FileInfos = {read=GetFileInfos};
#endif /* _WIN64 */
	__property System::UnicodeString FileName[int Index] = {read=GetFileName};
	__property TZipHeader FileInfo[int Index] = {read=GetFileInfo};
	__property System::UnicodeString FileComment[int Index] = {read=GetFileComment, write=SetFileComment};
	__property System::UnicodeString Comment = {read=GetComment, write=SetComment};
	__property bool UTF8Support = {read=FUTF8Support, write=SetUTF8Support, default=1};
	__property System::Sysutils::TEncoding* Encoding = {read=GetEncoding, write=FEncoding};
	__property TZipProgressEvent OnProgress = {read=FOnProgress, write=FOnProgress};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE unsigned SIGNATURE_ZIPENDOFHEADER;
extern DELPHI_PACKAGE unsigned SIGNATURE_CENTRALHEADER;
extern DELPHI_PACKAGE unsigned SIGNATURE_LOCALHEADER;
static const System::Int8 LOCALHEADERSIZE = System::Int8(0x1a);
static const System::Int8 CENTRALHEADERSIZE = System::Int8(0x2a);
static const System::Int8 MADEBY_MSDOS = System::Int8(0x0);
static const System::Int8 MADEBY_UNIX = System::Int8(0x3);
extern DELPHI_PACKAGE System::UnicodeString __fastcall TZipCompressionToString(TZipCompression Compression);
}	/* namespace Zip */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ZIP)
using namespace System::Zip;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_ZipHPP
