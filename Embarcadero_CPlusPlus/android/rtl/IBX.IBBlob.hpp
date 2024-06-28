// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBBlob.pas' rev: 34.00 (Android)

#ifndef Ibx_IbblobHPP
#define Ibx_IbblobHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IBExternals.hpp>
#include <Data.DB.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibblob
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBBlobStream;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIBBlobStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	Ibx::Ibdatabase::TIBBase* FBase;
	Ibx::Ibheader::TGDS_QUAD FBlobID;
	int FBlobMaxSegmentSize;
	int FBlobNumSegments;
	int FBlobSize;
	short FBlobType;
	System::Byte *FBuffer;
	bool FBlobInitialized;
	void * *FHandle;
	Data::Db::TBlobStreamMode FMode;
	bool FModified;
	int FPosition;
	System::UnicodeString FColumnName;
	System::UnicodeString FRelationName;
	
protected:
	void __fastcall CloseBlob();
	void __fastcall CreateBlob();
	void __fastcall EnsureBlobInitialized();
	void __fastcall GetBlobInfo();
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetDatabase();
	Ibx::Ibheader::PISC_DB_HANDLE __fastcall GetDBHandle();
	Ibx::Ibdatabase::TIBTransaction* __fastcall GetTransaction();
	Ibx::Ibheader::PISC_TR_HANDLE __fastcall GetTRHandle();
	void __fastcall OpenBlob();
	void __fastcall SetBlobID(const Ibx::Ibheader::TGDS_QUAD &Value);
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* Value);
	void __fastcall SetMode(Data::Db::TBlobStreamMode Value);
	void __fastcall SetTransaction(Ibx::Ibdatabase::TIBTransaction* Value);
	
public:
	__fastcall TIBBlobStream();
	__fastcall virtual ~TIBBlobStream();
	NativeInt __fastcall Call(NativeInt ErrCode, bool RaiseError);
	void __fastcall Cancel();
	void __fastcall CheckReadable();
	void __fastcall CheckWritable();
	void __fastcall Finalize();
	void __fastcall LoadFromFile(System::UnicodeString Filename);
	void __fastcall LoadFromStream(System::Classes::TStream* Stream);
#ifndef __aarch64__
	virtual int __fastcall Read(void *Buffer, int Count)/* overload */;
#else /* __aarch64__ */
	virtual long __fastcall Read(void *Buffer, long Count)/* overload */;
#endif /* __aarch64__ */
	void __fastcall SaveToFile(System::UnicodeString Filename);
	void __fastcall SaveToStream(System::Classes::TStream* Stream);
#ifndef __aarch64__
	virtual int __fastcall Seek(int Offset, System::Word Origin)/* overload */;
	virtual void __fastcall SetSize(int NewSize)/* overload */;
#else /* __aarch64__ */
	virtual long __fastcall Seek(long Offset, System::Word Origin)/* overload */;
	virtual void __fastcall SetSize(long NewSize)/* overload */;
#endif /* __aarch64__ */
	void __fastcall Truncate();
#ifndef __aarch64__
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
#else /* __aarch64__ */
	virtual long __fastcall Write(const void *Buffer, long Count)/* overload */;
#endif /* __aarch64__ */
	__property Ibx::Ibexternals::PVoid Handle = {read=FHandle};
	__property Ibx::Ibheader::TGDS_QUAD BlobID = {read=FBlobID, write=SetBlobID};
	__property int BlobMaxSegmentSize = {read=FBlobMaxSegmentSize, nodefault};
	__property int BlobNumSegments = {read=FBlobNumSegments, nodefault};
	__property int BlobSize = {read=FBlobSize, nodefault};
	__property short BlobType = {read=FBlobType, nodefault};
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=GetDatabase, write=SetDatabase};
	__property Ibx::Ibheader::PISC_DB_HANDLE DBHandle = {read=GetDBHandle};
	__property Data::Db::TBlobStreamMode Mode = {read=FMode, write=SetMode, nodefault};
	__property bool Modified = {read=FModified, nodefault};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=GetTransaction, write=SetTransaction};
	__property Ibx::Ibheader::PISC_TR_HANDLE TRHandle = {read=GetTRHandle};
	__property System::UnicodeString RelationName = {read=FRelationName, write=FRelationName};
	__property System::UnicodeString ColumnName = {read=FColumnName, write=FColumnName};
	/* Hoisted overloads: */
	
public:
#ifndef __aarch64__
	inline int __fastcall  Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
#else /* __aarch64__ */
	inline long __fastcall  Read(System::TArray__1<System::Byte> Buffer, long Offset, long Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline long __fastcall  Read(System::TArray__1<System::Byte> &Buffer, long Count){ return System::Classes::TStream::Read(Buffer, Count); }
#endif /* __aarch64__ */
	inline __int64 __fastcall  Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
	
protected:
	inline void __fastcall  SetSize(const __int64 NewSize){ System::Classes::TStream::SetSize(NewSize); }
	
public:
#ifndef __aarch64__
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#else /* __aarch64__ */
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Offset, long Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline long __fastcall  Write(const System::TArray__1<System::Byte> Buffer, long Count){ return System::Classes::TStream::Write(Buffer, Count); }
#endif /* __aarch64__ */
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word DefaultBlobSegmentSize = System::Word(0x4000);
extern DELPHI_PACKAGE void __fastcall GetBlobInfo(Ibx::Ibheader::PISC_BLOB_HANDLE hBlobHandle, int &NumSegments, int &MaxSegmentSize, int &TotalSize, short &BlobType, Ibx::Ibintf::_di_IGDSLibrary GDSLibrary);
extern DELPHI_PACKAGE void __fastcall ReadBlob(Ibx::Ibheader::PISC_BLOB_HANDLE hBlobHandle, System::PByte Buffer, int BlobSize, Ibx::Ibintf::_di_IGDSLibrary GDSLibrary);
extern DELPHI_PACKAGE void __fastcall WriteBlob(Ibx::Ibheader::PISC_BLOB_HANDLE hBlobHandle, System::PByte Buffer, int BlobSize, Ibx::Ibintf::_di_IGDSLibrary GDSLibrary);
}	/* namespace Ibblob */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBBLOB)
using namespace Ibx::Ibblob;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbblobHPP
