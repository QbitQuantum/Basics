// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSchedulerOfThreadPool.pas' rev: 34.00 (iOS)

#ifndef IdschedulerofthreadpoolHPP
#define IdschedulerofthreadpoolHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdContext.hpp>
#include <IdScheduler.hpp>
#include <IdSchedulerOfThread.hpp>
#include <IdThread.hpp>
#include <IdYarn.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idschedulerofthreadpool
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSchedulerOfThreadPool;
//-- type declarations -------------------------------------------------------
typedef System::Classes::TThreadList TIdPoolThreadList;

typedef System::Classes::TList TIdPoolList;

class PASCALIMPLEMENTATION TIdSchedulerOfThreadPool : public Idschedulerofthread::TIdSchedulerOfThread
{
	typedef Idschedulerofthread::TIdSchedulerOfThread inherited;
	
protected:
	int FPoolSize;
	System::Classes::TThreadList* FThreadPool;
	virtual void __fastcall InitComponent();
	
public:
	__fastcall virtual ~TIdSchedulerOfThreadPool();
	virtual Idyarn::TIdYarn* __fastcall AcquireYarn();
	virtual void __fastcall Init();
	virtual Idthread::TIdThreadWithTask* __fastcall NewThread();
	virtual void __fastcall ReleaseYarn(Idyarn::TIdYarn* AYarn);
	virtual void __fastcall TerminateAllYarns();
	
__published:
	__property int PoolSize = {read=FPoolSize, write=FPoolSize, default=0};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSchedulerOfThreadPool(System::Classes::TComponent* AOwner)/* overload */ : Idschedulerofthread::TIdSchedulerOfThread(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSchedulerOfThreadPool()/* overload */ : Idschedulerofthread::TIdSchedulerOfThread() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idschedulerofthreadpool */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSCHEDULEROFTHREADPOOL)
using namespace Idschedulerofthreadpool;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdschedulerofthreadpoolHPP
