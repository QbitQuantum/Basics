// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSchedulerOfThreadDefault.pas' rev: 34.00 (Android)

#ifndef IdschedulerofthreaddefaultHPP
#define IdschedulerofthreaddefaultHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdThread.hpp>
#include <IdSchedulerOfThread.hpp>
#include <IdScheduler.hpp>
#include <IdYarn.hpp>
#include <IdContext.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idschedulerofthreaddefault
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSchedulerOfThreadDefault;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdSchedulerOfThreadDefault : public Idschedulerofthread::TIdSchedulerOfThread
{
	typedef Idschedulerofthread::TIdSchedulerOfThread inherited;
	
public:
	virtual Idyarn::TIdYarn* __fastcall AcquireYarn();
	virtual void __fastcall ReleaseYarn(Idyarn::TIdYarn* AYarn);
	virtual Idthread::TIdThreadWithTask* __fastcall NewThread();
public:
	/* TIdSchedulerOfThread.Destroy */ inline __fastcall virtual ~TIdSchedulerOfThreadDefault() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSchedulerOfThreadDefault(System::Classes::TComponent* AOwner)/* overload */ : Idschedulerofthread::TIdSchedulerOfThread(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSchedulerOfThreadDefault()/* overload */ : Idschedulerofthread::TIdSchedulerOfThread() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idschedulerofthreaddefault */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSCHEDULEROFTHREADDEFAULT)
using namespace Idschedulerofthreaddefault;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdschedulerofthreaddefaultHPP
