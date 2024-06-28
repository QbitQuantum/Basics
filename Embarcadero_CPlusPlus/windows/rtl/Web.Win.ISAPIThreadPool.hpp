// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.Win.ISAPIThreadPool.pas' rev: 34.00 (Windows)

#ifndef Web_Win_IsapithreadpoolHPP
#define Web_Win_IsapithreadpoolHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Isapi2.hpp>
#include <Winapi.Windows.hpp>
#include <System.SyncObjs.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Win
{
namespace Isapithreadpool
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TISAPIThreadPool;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
typedef System::TMetaClass* TISAPIThreadPoolClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TISAPIThreadPoolClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TISAPIThreadPool : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<NativeUInt> _TISAPIThreadPool__1;
	
	
private:
	System::Syncobjs::TCriticalSection* FCriticalSection;
	NativeUInt FRequestQueue;
	bool FInitCOM;
	int FMin _DEPRECATED_ATTRIBUTE0 ;
	int FMax _DEPRECATED_ATTRIBUTE0 ;
	int __fastcall GetThreadCount();
	void __fastcall SetMax _DEPRECATED_ATTRIBUTE0 (const int Value);
	void __fastcall SetMin _DEPRECATED_ATTRIBUTE0 (const int Value);
	void __fastcall SetInitCOM(const bool Value);
	
protected:
	_TISAPIThreadPool__1 FThreads;
	virtual void __fastcall Initialize();
	bool __fastcall PushBack(Winapi::Isapi2::PEXTENSION_CONTROL_BLOCK ECB);
	virtual void __fastcall ShutDown();
#ifndef _WIN64
	__property NativeUInt RequestQueue = {read=FRequestQueue, nodefault};
	__property NativeUInt Handle = {read=FRequestQueue, nodefault};
#else /* _WIN64 */
	__property NativeUInt RequestQueue = {read=FRequestQueue};
	__property NativeUInt Handle = {read=FRequestQueue};
#endif /* _WIN64 */
	
public:
	__fastcall virtual TISAPIThreadPool(bool InitCOM);
	__fastcall virtual ~TISAPIThreadPool();
	__property bool InitCOM = {read=FInitCOM, write=SetInitCOM, nodefault};
	__property int Min = {read=FMin, write=SetMin, default=1};
	__property int Max = {read=FMax, write=SetMax, default=32};
	__property int ThreadCount = {read=GetThreadCount, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::Byte NumberOfThreads;
extern DELPHI_PACKAGE TISAPIThreadPoolClass ThreadPoolClass;
extern DELPHI_PACKAGE TISAPIThreadPool* ThreadPool;
extern DELPHI_PACKAGE System::LongBool __stdcall GetExtensionVersion(Winapi::Isapi2::HSE_VERSION_INFO &Ver);
extern DELPHI_PACKAGE unsigned __stdcall HttpExtensionProc(Winapi::Isapi2::TEXTENSION_CONTROL_BLOCK &ECB);
extern DELPHI_PACKAGE System::LongBool __stdcall TerminateExtension(unsigned dwFlags);
}	/* namespace Isapithreadpool */
}	/* namespace Win */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_WIN_ISAPITHREADPOOL)
using namespace Web::Win::Isapithreadpool;
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
#endif	// Web_Win_IsapithreadpoolHPP
