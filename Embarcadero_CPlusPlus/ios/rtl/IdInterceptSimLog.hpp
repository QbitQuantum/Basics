// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdInterceptSimLog.pas' rev: 34.00 (iOS)

#ifndef IdinterceptsimlogHPP
#define IdinterceptsimlogHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdIntercept.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idinterceptsimlog
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdInterceptSimLog;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdInterceptSimLog : public Idintercept::TIdConnectionIntercept
{
	typedef Idintercept::TIdConnectionIntercept inherited;
	
protected:
	System::UnicodeString FFilename;
	System::Classes::TStream* FStream;
	void __fastcall SetFilename(const System::UnicodeString AValue);
	void __fastcall WriteRecord(const System::UnicodeString ATag, const Idglobal::TIdBytes ABuffer);
	
public:
	virtual void __fastcall Connect(System::Classes::TComponent* AConnection);
	virtual void __fastcall Disconnect();
	virtual void __fastcall Receive(Idglobal::TIdBytes &ABuffer);
	virtual void __fastcall Send(Idglobal::TIdBytes &ABuffer);
	
__published:
	__property System::UnicodeString Filename = {read=FFilename, write=SetFilename};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdInterceptSimLog(System::Classes::TComponent* AOwner)/* overload */ : Idintercept::TIdConnectionIntercept(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdInterceptSimLog()/* overload */ : Idintercept::TIdConnectionIntercept() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdInterceptSimLog() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idinterceptsimlog */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDINTERCEPTSIMLOG)
using namespace Idinterceptsimlog;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdinterceptsimlogHPP
