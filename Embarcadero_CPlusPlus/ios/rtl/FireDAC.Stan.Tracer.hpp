// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Stan.Tracer.pas' rev: 34.00 (iOS)

#ifndef Firedac_Stan_TracerHPP
#define Firedac_Stan_TracerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Stan
{
namespace Tracer
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDTracer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDTracer : public Firedac::Stan::Util::TFDThread
{
	typedef Firedac::Stan::Util::TFDThread inherited;
	
private:
	System::UnicodeString FTraceFileName;
	Firedac::Stan::Util::TFDTextFile* FTraceFileHandler;
	bool FTraceFileAppend;
	__int64 FCounter;
	Firedac::Stan::Intf::TFDTraceFileColumns FTraceFileColumns;
	Firedac::Stan::Intf::TFDEncoding FTraceFileEncoding;
	void __fastcall CheckInactive();
	void __fastcall SetTraceFileName(const System::UnicodeString AValue);
	void __fastcall SetTraceFileAppend(bool AValue);
	void __fastcall OpenTraceFiles();
	void __fastcall CloseTraceFiles();
	void __fastcall SetTraceFileEncoding(const Firedac::Stan::Intf::TFDEncoding Value);
	
protected:
	__classmethod virtual Firedac::Stan::Util::TFDThreadMsgClass __fastcall GetStartMsgClass();
	__classmethod virtual Firedac::Stan::Util::TFDThreadMsgClass __fastcall GetStopMsgClass();
	__classmethod virtual Firedac::Stan::Util::TFDThreadMsgClass __fastcall GetTerminateMsgClass();
	virtual bool __fastcall DoAllowTerminate();
	virtual void __fastcall DoActiveChanged();
	virtual void __fastcall DoIdle();
	
public:
	__fastcall TFDTracer();
	void __fastcall TraceMsg(const System::UnicodeString AObjClassName, const System::UnicodeString AObjName, const System::UnicodeString AMsg);
	__property System::UnicodeString TraceFileName = {read=FTraceFileName, write=SetTraceFileName};
	__property bool TraceFileAppend = {read=FTraceFileAppend, write=SetTraceFileAppend, nodefault};
	__property Firedac::Stan::Intf::TFDTraceFileColumns TraceFileColumns = {read=FTraceFileColumns, write=FTraceFileColumns, nodefault};
	__property Firedac::Stan::Intf::TFDEncoding TraceFileEncoding = {read=FTraceFileEncoding, write=SetTraceFileEncoding, nodefault};
public:
	/* TFDThread.Destroy */ inline __fastcall virtual ~TFDTracer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool FADShowTraces;
}	/* namespace Tracer */
}	/* namespace Stan */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_STAN_TRACER)
using namespace Firedac::Stan::Tracer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_STAN)
using namespace Firedac::Stan;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Stan_TracerHPP
