// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.SyncObjs.pas' rev: 34.00 (iOS)

#ifndef System_SyncobjsHPP
#define System_SyncobjsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.SysTime.hpp>
#include <Posix.Time.hpp>
#include <Posix.Semaphore.hpp>
#include <Posix.Pthread.hpp>
#include <Posix.Errno.hpp>
#include <Macapi.CoreServices.hpp>
#include <Macapi.Mach.hpp>
#include <System.Types.hpp>
#include <System.RTLConsts.hpp>
#include <System.TimeSpan.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
static const System::Types::TWaitResult wrIOCompletion = System::Types::TWaitResult::wrIOCompletion;

namespace System
{
namespace Syncobjs
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ESyncObjectException;
class DELPHICLASS TSynchroObject;
class DELPHICLASS THandleObject;
class DELPHICLASS TEvent;
class DELPHICLASS TSimpleEvent;
class DELPHICLASS TMutex;
class DELPHICLASS TSemaphore;
class DELPHICLASS TCriticalSection;
class DELPHICLASS TConditionVariableMutex;
class DELPHICLASS TConditionVariableCS;
struct TSpinWait;
class DELPHICLASS ELockRecursionException;
class DELPHICLASS ELockException;
struct TSpinLock;
class DELPHICLASS TLightweightEvent;
class DELPHICLASS TLightweightSemaphore;
class DELPHICLASS TCountdownEvent;
struct TLightweightMREW;
class DELPHICLASS TInterlocked;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION ESyncObjectException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESyncObjectException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESyncObjectException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESyncObjectException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESyncObjectException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESyncObjectException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESyncObjectException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESyncObjectException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESyncObjectException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESyncObjectException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESyncObjectException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESyncObjectException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESyncObjectException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESyncObjectException() { }
	
};


typedef void * PSecurityAttributes;

using System::Types::TWaitResult;

class PASCALIMPLEMENTATION TSynchroObject : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static unsigned CalendarClock;
	
protected:
	void __fastcall GetPosixEndTime(timespec &EndTime, unsigned TimeOut);
	void __fastcall CheckNamed(const System::UnicodeString Name);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	virtual void __fastcall Acquire();
	virtual void __fastcall Release();
	virtual System::Types::TWaitResult __fastcall WaitFor(unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	System::Types::TWaitResult __fastcall WaitFor(const System::Timespan::TTimeSpan &Timeout)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TSynchroObject() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TSynchroObject() { }
	
};


typedef System::DynamicArray<THandleObject*> THandleObjectArray;

class PASCALIMPLEMENTATION THandleObject : public TSynchroObject
{
	typedef TSynchroObject inherited;
	
public:
	/* TObject.Create */ inline __fastcall THandleObject() : TSynchroObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~THandleObject() { }
	
};


class PASCALIMPLEMENTATION TEvent : public THandleObject
{
	typedef THandleObject inherited;
	
private:
	bool FManualReset;
	Macapi::Coreservices::dispatch_object *FEvent;
	System::Types::TWaitResult __fastcall WaitNoReset(unsigned Timeout);
	
public:
	__fastcall TEvent(void * EventAttributes, bool ManualReset, bool InitialState, const System::UnicodeString Name, bool UseCOMWait)/* overload */;
	__fastcall TEvent(bool UseCOMWait)/* overload */;
	__fastcall virtual ~TEvent();
	virtual System::Types::TWaitResult __fastcall WaitFor(unsigned Timeout)/* overload */;
	void __fastcall SetEvent();
	void __fastcall ResetEvent();
	/* Hoisted overloads: */
	
public:
	inline System::Types::TWaitResult __fastcall  WaitFor(const System::Timespan::TTimeSpan &Timeout){ return TSynchroObject::WaitFor(Timeout); }
	
};


class PASCALIMPLEMENTATION TSimpleEvent : public TEvent
{
	typedef TEvent inherited;
	
public:
	/* TEvent.Create */ inline __fastcall TSimpleEvent(void * EventAttributes, bool ManualReset, bool InitialState, const System::UnicodeString Name, bool UseCOMWait)/* overload */ : TEvent(EventAttributes, ManualReset, InitialState, Name, UseCOMWait) { }
	/* TEvent.Create */ inline __fastcall TSimpleEvent(bool UseCOMWait)/* overload */ : TEvent(UseCOMWait) { }
	/* TEvent.Destroy */ inline __fastcall virtual ~TSimpleEvent() { }
	
};


class PASCALIMPLEMENTATION TMutex : public THandleObject
{
	typedef THandleObject inherited;
	
private:
	pthread_mutex_t FMutex;
	
public:
	__fastcall TMutex(bool UseCOMWait)/* overload */;
	__fastcall TMutex(void * MutexAttributes, bool InitialOwner, const System::UnicodeString Name, bool UseCOMWait)/* overload */;
	__fastcall TMutex(unsigned DesiredAccess, bool InheritHandle, const System::UnicodeString Name, bool UseCOMWait)/* overload */;
	__fastcall virtual ~TMutex();
	virtual System::Types::TWaitResult __fastcall WaitFor(unsigned Timeout)/* overload */;
	virtual void __fastcall Acquire();
	virtual void __fastcall Release();
	/* Hoisted overloads: */
	
public:
	inline System::Types::TWaitResult __fastcall  WaitFor(const System::Timespan::TTimeSpan &Timeout){ return TSynchroObject::WaitFor(Timeout); }
	
};


class PASCALIMPLEMENTATION TSemaphore : public THandleObject
{
	typedef THandleObject inherited;
	
private:
	Macapi::Coreservices::dispatch_object *FSem;
	
public:
	__fastcall TSemaphore(bool UseCOMWait)/* overload */;
	__fastcall TSemaphore(void * SemaphoreAttributes, int AInitialCount, int AMaximumCount, const System::UnicodeString Name, bool UseCOMWait)/* overload */;
	__fastcall TSemaphore(unsigned DesiredAccess, bool InheritHandle, const System::UnicodeString Name, bool UseCOMWait)/* overload */;
	__fastcall virtual ~TSemaphore();
	virtual System::Types::TWaitResult __fastcall WaitFor(unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	virtual void __fastcall Acquire();
	virtual void __fastcall Release()/* overload */;
	HIDESBASE int __fastcall Release(int AReleaseCount)/* overload */;
	/* Hoisted overloads: */
	
public:
	inline System::Types::TWaitResult __fastcall  WaitFor(const System::Timespan::TTimeSpan &Timeout){ return TSynchroObject::WaitFor(Timeout); }
	
};


class PASCALIMPLEMENTATION TCriticalSection : public TSynchroObject
{
	typedef TSynchroObject inherited;
	
	
private:
	struct DECLSPEC_DRECORD TCritSec
	{
	public:
		System::TObject* FSync;
		void __fastcall Initialize();
		void __fastcall Free();
		void __fastcall Enter();
		void __fastcall Leave();
		bool __fastcall TryEnter();
	};
	
	
	
protected:
	TCritSec FSection;
	
public:
	__fastcall TCriticalSection();
	__fastcall virtual ~TCriticalSection();
	virtual void __fastcall Acquire();
	virtual void __fastcall Release();
	bool __fastcall TryEnter();
	void __fastcall Enter();
	void __fastcall Leave();
};


class PASCALIMPLEMENTATION TConditionVariableMutex : public TSynchroObject
{
	typedef TSynchroObject inherited;
	
private:
	pthread_cond_t FCondVar;
	
public:
	__fastcall TConditionVariableMutex();
	__fastcall virtual ~TConditionVariableMutex();
	virtual void __fastcall Acquire();
	virtual void __fastcall Release();
	void __fastcall ReleaseAll();
	HIDESBASE System::Types::TWaitResult __fastcall WaitFor(TMutex* AExternalMutex, unsigned TimeOut = (unsigned)(0xffffffff));
};


class PASCALIMPLEMENTATION TConditionVariableCS : public TSynchroObject
{
	typedef TSynchroObject inherited;
	
protected:
	System::TObject* FCondVar;
	
public:
	__fastcall TConditionVariableCS();
	__fastcall virtual ~TConditionVariableCS();
	virtual void __fastcall Acquire();
	virtual void __fastcall Release();
	void __fastcall ReleaseAll();
	HIDESBASE System::Types::TWaitResult __fastcall WaitFor(TCriticalSection* CriticalSection, unsigned TimeOut = (unsigned)(0xffffffff))/* overload */;
	/* Hoisted overloads: */
	
public:
	inline System::Types::TWaitResult __fastcall  WaitFor(unsigned Timeout = (unsigned)(0xffffffff)){ return TSynchroObject::WaitFor(Timeout); }
	inline System::Types::TWaitResult __fastcall  WaitFor(const System::Timespan::TTimeSpan &Timeout){ return TSynchroObject::WaitFor(Timeout); }
	
};


struct DECLSPEC_DRECORD TSpinWait
{
private:
	static constexpr System::Int8 YieldThreshold = System::Int8(0xa);
	
	static constexpr System::Int8 Sleep1Threshold = System::Int8(0x14);
	
	static constexpr System::Int8 Sleep0Threshold = System::Int8(0x5);
	
	int FCount;
	bool __fastcall GetNextSpinCycleWillYield();
	
public:
	void __fastcall Reset();
	void __fastcall SpinCycle();
	static void __fastcall SpinUntil(const System::DelphiInterface<System::Sysutils::TFunc__1<bool> > ACondition)/* overload */;
	static bool __fastcall SpinUntil(const System::DelphiInterface<System::Sysutils::TFunc__1<bool> > ACondition, unsigned Timeout)/* overload */;
	static bool __fastcall SpinUntil(const System::DelphiInterface<System::Sysutils::TFunc__1<bool> > ACondition, const System::Timespan::TTimeSpan &Timeout)/* overload */;
	__property int Count = {read=FCount};
	__property bool NextSpinCycleWillYield = {read=GetNextSpinCycleWillYield};
};


class PASCALIMPLEMENTATION ELockRecursionException : public ESyncObjectException
{
	typedef ESyncObjectException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ELockRecursionException(const System::UnicodeString Msg) : ESyncObjectException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ELockRecursionException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ESyncObjectException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ELockRecursionException(NativeUInt Ident)/* overload */ : ESyncObjectException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ELockRecursionException(System::PResStringRec ResStringRec)/* overload */ : ESyncObjectException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ELockRecursionException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ESyncObjectException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ELockRecursionException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ESyncObjectException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ELockRecursionException(const System::UnicodeString Msg, int AHelpContext) : ESyncObjectException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ELockRecursionException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ESyncObjectException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELockRecursionException(NativeUInt Ident, int AHelpContext)/* overload */ : ESyncObjectException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELockRecursionException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ESyncObjectException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELockRecursionException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESyncObjectException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELockRecursionException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESyncObjectException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ELockRecursionException() { }
	
};


class PASCALIMPLEMENTATION ELockException : public ESyncObjectException
{
	typedef ESyncObjectException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ELockException(const System::UnicodeString Msg) : ESyncObjectException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ELockException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ESyncObjectException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ELockException(NativeUInt Ident)/* overload */ : ESyncObjectException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ELockException(System::PResStringRec ResStringRec)/* overload */ : ESyncObjectException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ELockException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ESyncObjectException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ELockException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ESyncObjectException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ELockException(const System::UnicodeString Msg, int AHelpContext) : ESyncObjectException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ELockException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ESyncObjectException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELockException(NativeUInt Ident, int AHelpContext)/* overload */ : ESyncObjectException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ELockException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ESyncObjectException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELockException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESyncObjectException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ELockException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ESyncObjectException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ELockException() { }
	
};


struct DECLSPEC_DRECORD TSpinLock
{
private:
	static constexpr unsigned ThreadTrackingDisabled = unsigned(0x80000000);
	
	static constexpr int MaxWaitingThreads = int(0x7ffffffe);
	
	static constexpr int WaitingThreadMask = int(0x7ffffffe);
	
	static constexpr System::Int8 AnonymouslyOwned = System::Int8(0x1);
	
	static constexpr System::Int8 LockAvailable = System::Int8(0x0);
	
	int FLock;
	bool __fastcall InternalTryEnter(unsigned Timeout);
	bool __fastcall GetIsLocked();
	bool __fastcall GetIsLockedByCurrentThread();
	bool __fastcall GetIsThreadTrackingEnabled();
	void __fastcall RemoveWaiter();
	
public:
	__fastcall TSpinLock(bool EnableThreadTracking);
	void __fastcall Enter();
	void __fastcall Exit(bool PublishNow = true);
	bool __fastcall TryEnter()/* overload */;
	bool __fastcall TryEnter(unsigned Timeout)/* overload */;
	bool __fastcall TryEnter(const System::Timespan::TTimeSpan &Timeout)/* overload */;
	__property bool IsLocked = {read=GetIsLocked};
	__property bool IsLockedByCurrentThread = {read=GetIsLockedByCurrentThread};
	__property bool IsThreadTrackingEnabled = {read=GetIsThreadTrackingEnabled};
	TSpinLock() {}
};


class PASCALIMPLEMENTATION TLightweightEvent : public TSynchroObject
{
	typedef TSynchroObject inherited;
	
private:
	static constexpr System::Int8 DefaultSpinMulticore = System::Int8(0xa);
	
	static constexpr System::Int8 DefaultSpinSinglecore = System::Int8(0x1);
	
	static constexpr System::Word SpinMask = System::Word(0xfff);
	
	static constexpr System::Word MaxSpin = System::Word(0xfff);
	
	static constexpr int EventSignaled = int(-2147483648);
	
	static constexpr System::Int8 EventUnsignaled = System::Int8(0x0);
	
	static constexpr int SignalMask = int(-2147483648);
	
	System::TObject* FLock;
	int FStateAndSpin;
	int FWaiters;
	int FBlockedCount;
	bool __fastcall GetIsSet();
	int __fastcall GetSpinCount();
	void __fastcall SetNewStateAtomically(int NewValue, int Mask);
	
public:
	__fastcall TLightweightEvent()/* overload */;
	__fastcall TLightweightEvent(bool InitialState)/* overload */;
	__fastcall TLightweightEvent(bool InitialState, int SpinCount)/* overload */;
	__fastcall virtual ~TLightweightEvent();
	void __fastcall ResetEvent();
	void __fastcall SetEvent();
	virtual System::Types::TWaitResult __fastcall WaitFor(unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	__property int BlockedCount = {read=FBlockedCount, nodefault};
	__property bool IsSet = {read=GetIsSet, nodefault};
	__property int SpinCount = {read=GetSpinCount, nodefault};
	/* Hoisted overloads: */
	
public:
	inline System::Types::TWaitResult __fastcall  WaitFor(const System::Timespan::TTimeSpan &Timeout){ return TSynchroObject::WaitFor(Timeout); }
	
};


class PASCALIMPLEMENTATION TLightweightSemaphore : public TSynchroObject
{
	typedef TSynchroObject inherited;
	
private:
	System::TObject* FCountLock;
	int FCurrentCount;
	int FInitialCount;
	int FMaxCount;
	int FWaitCount;
	int FBlockedCount;
	
public:
	__fastcall TLightweightSemaphore(int AInitialCount, int AMaxCount);
	__fastcall virtual ~TLightweightSemaphore();
	HIDESBASE int __fastcall Release(int AReleaseCount = 0x1);
	virtual System::Types::TWaitResult __fastcall WaitFor(unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	__property int BlockedCount = {read=FBlockedCount, nodefault};
	__property int CurrentCount = {read=FCurrentCount, nodefault};
	/* Hoisted overloads: */
	
public:
	inline System::Types::TWaitResult __fastcall  WaitFor(const System::Timespan::TTimeSpan &Timeout){ return TSynchroObject::WaitFor(Timeout); }
	
};


class PASCALIMPLEMENTATION TCountdownEvent : public TSynchroObject
{
	typedef TSynchroObject inherited;
	
private:
	TLightweightEvent* FEvent;
	int FInitialCount;
	int FCurrentCount;
	bool __fastcall GetIsSet();
	
public:
	__fastcall TCountdownEvent()/* overload */;
	__fastcall TCountdownEvent(int Count)/* overload */;
	__fastcall TCountdownEvent(int Count, int SpinCount)/* overload */;
	__fastcall virtual ~TCountdownEvent();
	bool __fastcall Signal(int Count = 0x1);
	void __fastcall AddCount(int Count = 0x1);
	void __fastcall Reset()/* overload */;
	void __fastcall Reset(int Count)/* overload */;
	bool __fastcall TryAddCount(int Count = 0x1);
	virtual System::Types::TWaitResult __fastcall WaitFor(unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	__property int CurrentCount = {read=FCurrentCount, nodefault};
	__property int InitialCount = {read=FInitialCount, nodefault};
	__property bool IsSet = {read=GetIsSet, nodefault};
	/* Hoisted overloads: */
	
public:
	inline System::Types::TWaitResult __fastcall  WaitFor(const System::Timespan::TTimeSpan &Timeout){ return TSynchroObject::WaitFor(Timeout); }
	
};


struct DECLSPEC_DRECORD TLightweightMREW
{
private:
	static unsigned CalendarClock;
	pthread_rwlock_t FNativeRW;
	void __fastcall GetPosixEndTime(timespec &EndTime, unsigned TimeOut);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	TLightweightMREW() { _op_Initialize(*this); }
	
		static void __fastcall _op_Initialize(/* out */ TLightweightMREW &Dest);
	void __fastcall BeginRead();
	bool __fastcall TryBeginRead();
	void __fastcall EndRead();
	void __fastcall BeginWrite();
	bool __fastcall TryBeginWrite();
	void __fastcall EndWrite();
};


_DECLARE_ARITH_TYPE_ALIAS(System::Int8, TBitOffset);

class PASCALIMPLEMENTATION TInterlocked : /*[[sealed]]*/ public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static int __fastcall Increment(int &Target)/* overload */;
	static __int64 __fastcall Increment(__int64 &Target)/* overload */;
	static int __fastcall Decrement(int &Target)/* overload */;
	static __int64 __fastcall Decrement(__int64 &Target)/* overload */;
	static int __fastcall Add(int &Target, int Increment)/* overload */;
	static __int64 __fastcall Add(__int64 &Target, __int64 Increment)/* overload */;
	static bool __fastcall BitTestAndSet(int &Target, TBitOffset BitOffset);
	static bool __fastcall BitTestAndClear(int &Target, TBitOffset BitOffset);
	static void * __fastcall Exchange(void * &Target, void * Value)/* overload */;
	static int __fastcall Exchange(int &Target, int Value)/* overload */;
	static __int64 __fastcall Exchange(__int64 &Target, __int64 Value)/* overload */;
	static System::TObject* __fastcall Exchange(System::TObject* &Target, System::TObject* Value)/* overload */;
	static double __fastcall Exchange(double &Target, double Value)/* overload */;
	static float __fastcall Exchange(float &Target, float Value)/* overload */;
	template<typename T> static T __fastcall Exchange(T &Target, T Value)/* overload */;
	static void * __fastcall CompareExchange(void * &Target, void * Value, void * Comparand)/* overload */;
	static int __fastcall CompareExchange(int &Target, int Value, int Comparand)/* overload */;
	static int __fastcall CompareExchange(int &Target, int Value, int Comparand, /* out */ bool &Succeeded)/* overload */;
	static __int64 __fastcall CompareExchange(__int64 &Target, __int64 Value, __int64 Comparand)/* overload */;
	static System::TObject* __fastcall CompareExchange(System::TObject* &Target, System::TObject* Value, System::TObject* Comparand)/* overload */;
	static double __fastcall CompareExchange(double &Target, double Value, double Comparand)/* overload */;
	static float __fastcall CompareExchange(float &Target, float Value, float Comparand)/* overload */;
	template<typename T> static T __fastcall CompareExchange(T &Target, T Value, T Comparand)/* overload */;
	static __int64 __fastcall Read(__int64 &Target);
public:
	/* TObject.Create */ inline __fastcall TInterlocked() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInterlocked() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Syncobjs */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_SYNCOBJS)
using namespace System::Syncobjs;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif

//-- user supplied -----------------------------------------------------------
namespace System
{
namespace Syncobjs
{
#if defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) || defined(NO_USING_NAMESPACE_SYSTEM_SYNCOBJS)
static const System::Types::TWaitResult wrSignaled = System::Types::TWaitResult::wrSignaled;
static const System::Types::TWaitResult wrTimeout = System::Types::TWaitResult::wrTimeout;
static const System::Types::TWaitResult wrAbandoned = System::Types::TWaitResult::wrAbandoned;
static const System::Types::TWaitResult wrError = System::Types::TWaitResult::wrError;
#endif
}	/* namespace Syncobjs */
}	/* namespace System */

#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_SyncobjsHPP
