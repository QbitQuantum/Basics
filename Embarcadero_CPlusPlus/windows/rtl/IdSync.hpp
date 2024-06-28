// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSync.pas' rev: 34.00 (Windows)

#ifndef IdsyncHPP
#define IdsyncHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsync
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSync;
class DELPHICLASS TIdNotify;
class DELPHICLASS TIdNotifyMethod;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdSync _DEPRECATED_ATTRIBUTE1("Use static TThread.Synchronize()")  : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual void __fastcall DoSynchronize _DEPRECATED_ATTRIBUTE0 () = 0 ;
	
public:
	__fastcall virtual TIdSync _DEPRECATED_ATTRIBUTE0 ();
	void __fastcall Synchronize _DEPRECATED_ATTRIBUTE0 ();
	__classmethod void __fastcall SynchronizeMethod _DEPRECATED_ATTRIBUTE0 (System::Classes::TThreadMethod AMethod);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdSync() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdNotify _DEPRECATED_ATTRIBUTE1("Use static TThread.Queue() or TThread.ForceQueue()")  : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	bool FMainThreadUsesNotify _DEPRECATED_ATTRIBUTE0 ;
	virtual void __fastcall DoNotify _DEPRECATED_ATTRIBUTE0 () = 0 ;
	void __fastcall InternalDoNotify _DEPRECATED_ATTRIBUTE0 ();
	
public:
	__fastcall virtual TIdNotify _DEPRECATED_ATTRIBUTE0 ();
	void __fastcall Notify _DEPRECATED_ATTRIBUTE0 ();
	__classmethod void __fastcall NotifyMethod _DEPRECATED_ATTRIBUTE0 (System::Classes::TThreadMethod AMethod, bool AForceQueue = false);
	__property bool MainThreadUsesNotify = {read=FMainThreadUsesNotify, write=FMainThreadUsesNotify, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdNotify() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIdNotifyMethod _DEPRECATED_ATTRIBUTE1("Use static TThread.Queue() or TThread.ForceQueue()")  : public TIdNotify
{
	typedef TIdNotify inherited;
	
protected:
	System::Classes::TThreadMethod FMethod _DEPRECATED_ATTRIBUTE0 ;
	virtual void __fastcall DoNotify _DEPRECATED_ATTRIBUTE0 ();
	
public:
	__fastcall virtual TIdNotifyMethod _DEPRECATED_ATTRIBUTE0 (System::Classes::TThreadMethod AMethod);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIdNotifyMethod() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsync */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSYNC)
using namespace Idsync;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsyncHPP
