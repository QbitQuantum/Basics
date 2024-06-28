// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Types.pas' rev: 34.00 (Android)

#ifndef System_TypesHPP
#define System_TypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------
#include <SystemTypes.h>
extern const System::Single cPI /*= 3.141592654*/;
extern const System::Single cPIdiv180 /*= 0.017453292*/;
extern const System::Single c180divPI /*= 57.29577951*/;
extern const System::Single c2PI /*= 6.283185307*/;
extern const System::Single cPIdiv2 /*= 1.570796326*/;
extern const System::Single cPIdiv4 /*= 0.785398163*/;
extern const System::Single c3PIdiv4 /*= 2.35619449*/;
extern const System::Single cInv2PI /*= 1 / 6.283185307*/;
extern const System::Single cInv360 /*= 1 / 360*/;
extern const System::Single c180 /*= 180*/;
extern const System::Single c360 /*= 360*/;
extern const System::Single cOneHalf /*= 0.5*/;
extern const System::Extended CurveKappa /*= 0.5522847498*/;
extern const System::Extended CurveKappaInv /*= 1 - CurveKappa*/;
extern const System::Single Epsilon /*= 1E-40*/;
extern const System::Single Epsilon2 /*= 1E-40*/;

namespace System
{
namespace Types
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBitConverter;
struct DECLSPEC_DRECORD TXrmOptionDescRec
{
};


struct _FILETIME;
struct tagSTATSTG;
__interface DELPHIINTERFACE IClassFactory;
typedef System::DelphiInterface<IClassFactory> _di_IClassFactory;
__interface DELPHIINTERFACE ISequentialStream;
typedef System::DelphiInterface<ISequentialStream> _di_ISequentialStream;
__interface DELPHIINTERFACE IStream;
typedef System::DelphiInterface<IStream> _di_IStream;
class DELPHICLASS TMultiWaitEvent;
__interface DELPHIINTERFACE IAsyncResult;
typedef System::DelphiInterface<IAsyncResult> _di_IAsyncResult;
//-- type declarations -------------------------------------------------------
typedef System::WideString OleStr;

enum DECLSPEC_DENUM TEndian : unsigned char { Big, Little };

enum DECLSPEC_DENUM TDuplicates : unsigned char { dupIgnore, dupAccept, dupError };

enum DECLSPEC_DENUM TDirection : unsigned char { FromBeginning, FromEnd };

typedef TPoint *PPoint;

enum DECLSPEC_DENUM TSplitRectType : unsigned char { srLeft, srRight, srTop, srBottom };

enum class DECLSPEC_DENUM THorzRectAlign : unsigned char { Center, Left, Right };

enum class DECLSPEC_DENUM TVertRectAlign : unsigned char { Center, Top, Bottom };

typedef TRect *PRect;

typedef System::StaticArray<float, 2> TPointFType;

typedef TPointF *PPointF;

typedef TSizeF *PSizeF;

typedef TRectF *PRectF;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBitConverter : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	static void __fastcall RangeCheckError();
	
public:
	template<typename T> static void __fastcall UnsafeFrom(const T Value, System::TArray__1<System::Byte> &B, int Offset = 0x0);
	template<typename T> static void __fastcall From(const T Value, System::TArray__1<System::Byte> &B, int Offset = 0x0);
	template<typename T> static T __fastcall UnsafeInTo(const System::TArray__1<System::Byte> B, int Offset = 0x0);
	template<typename T> static T __fastcall InTo(const System::TArray__1<System::Byte> B, int Offset = 0x0);
public:
	/* TObject.Create */ inline __fastcall TBitConverter() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBitConverter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void * PDisplay;

typedef void * PEvent;

typedef TXrmOptionDescRec XrmOptionDescRec;

typedef TXrmOptionDescRec *PXrmOptionDescRec;

typedef void * Widget;

typedef void * WidgetClass;

typedef void * ArgList;

typedef void * Region;

typedef System::WideChar TOleChar;

typedef System::WideChar * POleStr;

typedef System::WideChar * *PPOleStr;

typedef System::PGUID PCLSID;

typedef GUID TCLSID;

typedef _FILETIME *PFileTime;

struct DECLSPEC_DRECORD _FILETIME
{
public:
	unsigned dwLowDateTime;
	unsigned dwHighDateTime;
};


typedef _FILETIME TFileTime;

typedef _FILETIME FILETIME;

typedef tagSTATSTG *PStatStg;

struct DECLSPEC_DRECORD tagSTATSTG
{
public:
	System::WideChar *pwcsName;
	int dwType;
	__int64 cbSize;
	_FILETIME mtime;
	_FILETIME ctime;
	_FILETIME atime;
	int grfMode;
	int grfLocksSupported;
	GUID clsid;
	int grfStateBits;
	int reserved;
};


typedef tagSTATSTG TStatStg;

typedef tagSTATSTG STATSTG;

__interface  INTERFACE_UUID("{00000001-0000-0000-C000-000000000046}") IClassFactory  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateInstance(const System::_di_IInterface unkOuter, const GUID iid, /* out */ void *obj) = 0 ;
	virtual HRESULT __stdcall LockServer(System::LongBool fLock) = 0 ;
};

__interface  INTERFACE_UUID("{0C733A30-2A1C-11CE-ADE5-00AA0044773D}") ISequentialStream  : public System::IInterface 
{
	virtual HRESULT __stdcall Read(void * pv, unsigned cb, System::PFixedUInt pcbRead) = 0 ;
	virtual HRESULT __stdcall Write(void * pv, unsigned cb, System::PFixedUInt pcbWritten) = 0 ;
};

__interface  INTERFACE_UUID("{0000000C-0000-0000-C000-000000000046}") IStream  : public ISequentialStream 
{
	virtual HRESULT __stdcall Seek(__int64 dlibMove, unsigned dwOrigin, /* out */ unsigned __int64 &libNewPosition) = 0 ;
	virtual HRESULT __stdcall SetSize(unsigned __int64 libNewSize) = 0 ;
	virtual HRESULT __stdcall CopyTo(_di_IStream stm, unsigned __int64 cb, /* out */ unsigned __int64 &cbRead, /* out */ unsigned __int64 &cbWritten) = 0 ;
	virtual HRESULT __stdcall Commit(unsigned grfCommitFlags) = 0 ;
	virtual HRESULT __stdcall Revert() = 0 ;
	virtual HRESULT __stdcall LockRegion(unsigned __int64 libOffset, unsigned __int64 cb, unsigned dwLockType) = 0 ;
	virtual HRESULT __stdcall UnlockRegion(unsigned __int64 libOffset, unsigned __int64 cb, unsigned dwLockType) = 0 ;
	virtual HRESULT __stdcall Stat(/* out */ tagSTATSTG &statstg, unsigned grfStatFlag) = 0 ;
	virtual HRESULT __stdcall Clone(/* out */ _di_IStream &stm) = 0 ;
};

_DECLARE_ARITH_TYPE_ALIAS(System::Int8, TValueRelationship);

enum DECLSPEC_DENUM TWaitResult : unsigned char { wrSignaled, wrTimeout, wrAbandoned, wrError, wrIOCompletion };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMultiWaitEvent : public System::TObject
{
	typedef System::TObject inherited;
	
	
protected:
	enum DECLSPEC_DENUM TWaiterFlag : unsigned char { Waiting, WaitAll };
	
	typedef System::Set<TWaiterFlag, TWaiterFlag::Waiting, TWaiterFlag::WaitAll> TWaiterFlags;
	
	class DELPHICLASS TMultiWaiter;
	class PASCALIMPLEMENTATION TMultiWaiter : public System::TObject
	{
		typedef System::TObject inherited;
		
		
	private:
#ifndef __aarch64__
		#pragma pack(push,8)
#endif /* not __aarch64__ */
		struct DECLSPEC_DRECORD _TMultiWaitEvent_TMultiWaiter__1
		{
			
		public:
			union
			{
				struct 
				{
					int EventCount;
				};
				struct 
				{
					int FiredEvent;
				};
				
			};
		};
#ifndef __aarch64__
		#pragma pack(pop)
#endif /* not __aarch64__ */
		
		
		
	public:
		System::TObject* FCond;
		int FRefCount;
		TMultiWaitEvent::TWaiterFlags FFlags;
		_TMultiWaitEvent_TMultiWaiter__1 FStatus;
		__fastcall TMultiWaiter();
		__fastcall virtual ~TMultiWaiter();
	};
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TWaitInfo
	{
	public:
		TMultiWaitEvent::TMultiWaiter* FWaiter;
		int FIndex;
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	typedef TWaitInfo *PWaitInfo;
	
	typedef TMultiWaitEvent* *PMultiWaitEvent;
	
	_DECLARE_METACLASS(System::TMetaClass, TMultiWaitEventClass);
	
	
private:
	static void __fastcall FreeAndNil(void *Obj);
	static TWaitResult __fastcall DoWait(TMultiWaitEvent* const *Events, const int Events_High, bool WaitAll, System::PInteger Index, PMultiWaitEvent Event, unsigned Timeout);
	bool __fastcall WaiterExpired(TWaitInfo &Info);
	void __fastcall RemoveExpiredWaiters();
	
protected:
	static TMultiWaitEventClass FMultiEventType;
	virtual __classmethod TMultiWaitEvent* __fastcall CreateInstance() = 0 ;
	virtual __classmethod void __fastcall ArgumentException() = 0 ;
	virtual __classmethod unsigned __fastcall GetTickCount() = 0 ;
	virtual void __fastcall Lock() = 0 ;
	virtual void __fastcall Unlock() = 0 ;
	virtual void __fastcall AtomicSetEventState(bool State) = 0 ;
	virtual void __fastcall NotifyWaiters() = 0 ;
	virtual void __fastcall ClearWaiters() = 0 ;
	virtual void __fastcall PushWaiter(const TWaitInfo &Waiter) = 0 ;
	virtual void __fastcall RemoveWaiter(int Index) = 0 ;
	virtual int __fastcall GetWaiterCount() = 0 ;
	virtual PWaitInfo __fastcall GetWaiter(int Index) = 0 ;
	__property int WaiterCount = {read=GetWaiterCount, nodefault};
	__property PWaitInfo Waiters[int Index] = {read=GetWaiter};
	
public:
	static TMultiWaitEvent* __fastcall Create();
	__fastcall virtual ~TMultiWaitEvent();
	virtual TWaitResult __fastcall WaitFor(unsigned Timeout = (unsigned)(0xffffffff)) = 0 ;
	void __fastcall SetEvent();
	void __fastcall ResetEvent();
	static TWaitResult __fastcall WaitForAll(TMultiWaitEvent* const *Events, const int Events_High, unsigned Timeout = (unsigned)(0xffffffff));
	static TWaitResult __fastcall WaitForAny(TMultiWaitEvent* const *Events, const int Events_High, unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	static TWaitResult __fastcall WaitForAny(TMultiWaitEvent* const *Events, const int Events_High, /* out */ int &Index, unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	static TWaitResult __fastcall WaitForAny(TMultiWaitEvent* const *Events, const int Events_High, /* out */ TMultiWaitEvent* &Event, unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
public:
	/* TObject.Create */ inline __fastcall TMultiWaitEvent() : System::TObject() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface IAsyncResult  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetAsyncContext() = 0 ;
	virtual TMultiWaitEvent* __fastcall GetAsyncWaitEvent() = 0 ;
	virtual bool __fastcall GetCompletedSynchronously() = 0 ;
	virtual bool __fastcall GetIsCompleted() = 0 ;
	virtual bool __fastcall GetIsCancelled() = 0 ;
	virtual bool __fastcall Cancel() = 0 ;
	__property System::TObject* AsyncContext = {read=GetAsyncContext};
	__property TMultiWaitEvent* AsyncWaitEvent = {read=GetAsyncWaitEvent};
	__property bool CompletedSynchronously = {read=GetCompletedSynchronously};
	__property bool IsCompleted = {read=GetIsCompleted};
	__property bool IsCancelled = {read=GetIsCancelled};
};

//-- var, const, procedure ---------------------------------------------------
static const TEndian PlatformEndian = (TEndian)(1);
#ifndef __aarch64__
#define RT_RCDATA (System::WideChar *)(0xa)
#else /* __aarch64__ */
#define RT_RCDATA (System::WideChar *)(0x000000000000000aULL)
#endif /* __aarch64__ */
static constexpr System::WideChar NullChar = (System::WideChar)(0x0);
static constexpr System::WideChar Tabulator = (System::WideChar)(0x9);
static constexpr System::WideChar Space = (System::WideChar)(0x20);
static constexpr System::WideChar CarriageReturn = (System::WideChar)(0xd);
static constexpr System::WideChar LineFeed = (System::WideChar)(0xa);
static constexpr System::WideChar VerticalTab = (System::WideChar)(0xb);
static constexpr System::WideChar FormFeed = (System::WideChar)(0xc);
static constexpr System::WideChar LineSeparator = (System::WideChar)(0x2028);
static constexpr System::WideChar ParagraphSeparator = (System::WideChar)(0x2029);
static constexpr System::WideChar BOM_LSB_FIRST = (System::WideChar)(0xfeff);
static constexpr System::WideChar BOM_MSB_FIRST = (System::WideChar)(0xfffe);
extern DELPHI_PACKAGE GUID GUID_NULL;
static constexpr System::Int8 STGTY_STORAGE = System::Int8(0x1);
static constexpr System::Int8 STGTY_STREAM = System::Int8(0x2);
static constexpr System::Int8 STGTY_LOCKBYTES = System::Int8(0x3);
static constexpr System::Int8 STGTY_PROPERTY = System::Int8(0x4);
static constexpr System::Int8 STREAM_SEEK_SET = System::Int8(0x0);
static constexpr System::Int8 STREAM_SEEK_CUR = System::Int8(0x1);
static constexpr System::Int8 STREAM_SEEK_END = System::Int8(0x2);
static constexpr HRESULT E_FAIL = HRESULT(-2147467259);
static constexpr HRESULT STG_E_INVALIDFUNCTION = HRESULT(-2147287039);
static constexpr HRESULT STG_E_FILENOTFOUND = HRESULT(-2147287038);
static constexpr HRESULT STG_E_PATHNOTFOUND = HRESULT(-2147287037);
static constexpr HRESULT STG_E_TOOMANYOPENFILES = HRESULT(-2147287036);
static constexpr HRESULT STG_E_ACCESSDENIED = HRESULT(-2147287035);
static constexpr HRESULT STG_E_INVALIDHANDLE = HRESULT(-2147287034);
static constexpr HRESULT STG_E_INSUFFICIENTMEMORY = HRESULT(-2147287032);
static constexpr HRESULT STG_E_INVALIDPOINTER = HRESULT(-2147287031);
static constexpr HRESULT STG_E_NOMOREFILES = HRESULT(-2147287022);
static constexpr HRESULT STG_E_DISKISWRITEPROTECTED = HRESULT(-2147287021);
static constexpr HRESULT STG_E_SEEKERROR = HRESULT(-2147287015);
static constexpr HRESULT STG_E_WRITEFAULT = HRESULT(-2147287011);
static constexpr HRESULT STG_E_READFAULT = HRESULT(-2147287010);
static constexpr HRESULT STG_E_SHAREVIOLATION = HRESULT(-2147287008);
static constexpr HRESULT STG_E_LOCKVIOLATION = HRESULT(-2147287007);
static constexpr HRESULT STG_E_FILEALREADYEXISTS = HRESULT(-2147286960);
static constexpr HRESULT STG_E_INVALIDPARAMETER = HRESULT(-2147286953);
static constexpr HRESULT STG_E_MEDIUMFULL = HRESULT(-2147286928);
static constexpr HRESULT STG_E_PROPSETMISMATCHED = HRESULT(-2147286800);
static constexpr HRESULT STG_E_ABNORMALAPIEXIT = HRESULT(-2147286790);
static constexpr HRESULT STG_E_INVALIDHEADER = HRESULT(-2147286789);
static constexpr HRESULT STG_E_INVALIDNAME = HRESULT(-2147286788);
static constexpr HRESULT STG_E_UNKNOWN = HRESULT(-2147286787);
static constexpr HRESULT STG_E_UNIMPLEMENTEDFUNCTION = HRESULT(-2147286786);
static constexpr HRESULT STG_E_INVALIDFLAG = HRESULT(-2147286785);
static constexpr HRESULT STG_E_INUSE = HRESULT(-2147286784);
static constexpr HRESULT STG_E_NOTCURRENT = HRESULT(-2147286783);
static constexpr HRESULT STG_E_REVERTED = HRESULT(-2147286782);
static constexpr HRESULT STG_E_CANTSAVE = HRESULT(-2147286781);
static constexpr HRESULT STG_E_OLDFORMAT = HRESULT(-2147286780);
static constexpr HRESULT STG_E_OLDDLL = HRESULT(-2147286779);
static constexpr HRESULT STG_E_SHAREREQUIRED = HRESULT(-2147286778);
static constexpr HRESULT STG_E_NOTFILEBASEDSTORAGE = HRESULT(-2147286777);
static constexpr HRESULT STG_E_EXTANTMARSHALLINGS = HRESULT(-2147286776);
static constexpr HRESULT STG_E_DOCFILECORRUPT = HRESULT(-2147286775);
static constexpr HRESULT STG_E_BADBASEADDRESS = HRESULT(-2147286768);
static constexpr HRESULT STG_E_INCOMPLETE = HRESULT(-2147286527);
static constexpr HRESULT STG_E_TERMINATED = HRESULT(-2147286526);
static constexpr HRESULT STG_S_CONVERTED = HRESULT(197120);
static constexpr HRESULT STG_S_BLOCK = HRESULT(197121);
static constexpr HRESULT STG_S_RETRYNOW = HRESULT(197122);
static constexpr HRESULT STG_S_MONITORING = HRESULT(197123);
static constexpr System::Int8 LessThanValue = System::Int8(-1);
static constexpr System::Int8 EqualsValue = System::Int8(0x0);
static constexpr System::Int8 GreaterThanValue = System::Int8(1);
extern DELPHI_PACKAGE bool __fastcall PtInRect(const TRect &Rect, const TPoint &P)/* overload */;
extern DELPHI_PACKAGE int __fastcall RectWidth(const TRect &Rect)/* overload */;
extern DELPHI_PACKAGE int __fastcall RectHeight(const TRect &Rect)/* overload */;
extern DELPHI_PACKAGE float __fastcall RectWidth(const TRectF &Rect)/* overload */;
extern DELPHI_PACKAGE float __fastcall RectHeight(const TRectF &Rect)/* overload */;
extern DELPHI_PACKAGE TRect __fastcall SplitRect(const TRect &Rect, TSplitRectType SplitType, int Size)/* overload */;
extern DELPHI_PACKAGE TRect __fastcall SplitRect(const TRect &Rect, TSplitRectType SplitType, double Percent)/* overload */;
extern DELPHI_PACKAGE TRect __fastcall CenteredRect(const TRect &SourceRect, const TRect &CenteredRect);
extern DELPHI_PACKAGE TPointF __fastcall MinPoint(const TPointF &P1, const TPointF &P2)/* overload */;
extern DELPHI_PACKAGE TPoint __fastcall MinPoint(const TPoint &P1, const TPoint &P2)/* overload */;
extern DELPHI_PACKAGE void __fastcall MultiplyRect(TRectF &R, const float DX, const float DY);
extern DELPHI_PACKAGE TRectF __fastcall NormalizeRectF(const TPointF *Pts, const int Pts_High)/* overload */;
extern DELPHI_PACKAGE TRectF __fastcall NormalizeRect(const TRectF &ARect)/* overload */;
extern DELPHI_PACKAGE TPointF __fastcall ScalePoint(const TPointF &P, float dX, float dY)/* overload */;
extern DELPHI_PACKAGE TPoint __fastcall ScalePoint(const TPoint &P, float dX, float dY)/* overload */;
extern DELPHI_PACKAGE bool __fastcall EqualRect(const TRect &R1, const TRect &R2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall EqualRect(const TRectF &R1, const TRectF &R2)/* overload */;
extern DELPHI_PACKAGE TRectF __fastcall RectF(float Left, float Top, float Right, float Bottom)/* overload */;
extern DELPHI_PACKAGE TRect __fastcall RectCenter(TRect &R, const TRect &Bounds)/* overload */;
extern DELPHI_PACKAGE TRectF __fastcall RectCenter(TRectF &R, const TRectF &Bounds)/* overload */;
extern DELPHI_PACKAGE TPointF __fastcall PointF(float X, float Y)/* overload */;
extern DELPHI_PACKAGE TSmallPoint __fastcall SmallPoint(int X, int Y)/* overload */;
#ifndef __aarch64__
extern DELPHI_PACKAGE TSmallPoint __fastcall SmallPoint(unsigned XY)/* overload */;
#else /* __aarch64__ */
extern DELPHI_PACKAGE TSmallPoint __fastcall SmallPoint(unsigned long XY)/* overload */;
#endif /* __aarch64__ */
extern DELPHI_PACKAGE bool __fastcall PtInCircle _DEPRECATED_ATTRIBUTE1("use TPoint.PointInCircle instead") (const TPoint &Point, const TPoint &Center, int Radius)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IntersectRect(const TRect &Rect1, const TRect &Rect2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IntersectRect(/* out */ TRect &Rect, const TRect &R1, const TRect &R2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IntersectRect(const TRectF &Rect1, const TRectF &Rect2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IntersectRect(/* out */ TRectF &Rect, const TRectF &R1, const TRectF &R2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall UnionRect(/* out */ TRect &Rect, const TRect &R1, const TRect &R2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall UnionRect(/* out */ TRectF &Rect, const TRectF &R1, const TRectF &R2)/* overload */;
extern DELPHI_PACKAGE TRect __fastcall UnionRect(const TRect &ARect1, const TRect &ARect2)/* overload */;
extern DELPHI_PACKAGE TRectF __fastcall UnionRect(const TRectF &ARect1, const TRectF &ARect2)/* overload */;
extern DELPHI_PACKAGE void __fastcall InflateRect(TRectF &R, const float DX, const float DY)/* overload */;
extern DELPHI_PACKAGE void __fastcall InflateRect(TRect &R, const int DX, const int DY)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsRectEmpty(const TRect &Rect)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsRectEmpty(const TRectF &Rect)/* overload */;
extern DELPHI_PACKAGE bool __fastcall OffsetRect(TRect &R, int DX, int DY)/* overload */;
extern DELPHI_PACKAGE bool __fastcall OffsetRect(TRectF &R, float DX, float DY)/* overload */;
extern DELPHI_PACKAGE TPoint __fastcall CenterPoint(const TRect &Rect);
extern DELPHI_PACKAGE bool __fastcall IntersectRectF(/* out */ TRectF &Rect, const TRectF &R1, const TRectF &R2);
extern DELPHI_PACKAGE bool __fastcall UnionRectF(/* out */ TRectF &Rect, const TRectF &R1, const TRectF &R2);
extern DELPHI_PACKAGE bool __fastcall PtInRect(const TRectF &Rect, const TPointF &P)/* overload */;
}	/* namespace Types */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_TYPES)
using namespace System::Types;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif

//-- user supplied -----------------------------------------------------------
#define  SYSTEM_TYPES_AT_END /* Round #2 */
#include <SystemTypes.h>

#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_TypesHPP
