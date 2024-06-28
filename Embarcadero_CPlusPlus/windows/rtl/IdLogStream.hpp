// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdLogStream.pas' rev: 34.00 (Windows)

#ifndef IdlogstreamHPP
#define IdlogstreamHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdLogBase.hpp>
#include <IdGlobal.hpp>
#include <IdIntercept.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idlogstream
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdLogStream;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdLogStream : public Idlogbase::TIdLogBase
{
	typedef Idlogbase::TIdLogBase inherited;
	
protected:
	bool FFreeStreams;
	System::Classes::TStream* FReceiveStream;
	System::Classes::TStream* FSendStream;
	virtual void __fastcall InitComponent();
	virtual void __fastcall LogStatus(const System::UnicodeString AText);
	virtual void __fastcall LogReceivedData(const System::UnicodeString AText, const System::UnicodeString AData);
	virtual void __fastcall LogSentData(const System::UnicodeString AText, const System::UnicodeString AData);
	
public:
	virtual void __fastcall Disconnect();
	__property bool FreeStreams = {read=FFreeStreams, write=FFreeStreams, nodefault};
	__property System::Classes::TStream* ReceiveStream = {read=FReceiveStream, write=FReceiveStream};
	__property System::Classes::TStream* SendStream = {read=FSendStream, write=FSendStream};
public:
	/* TIdLogBase.Destroy */ inline __fastcall virtual ~TIdLogStream() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdLogStream(System::Classes::TComponent* AOwner)/* overload */ : Idlogbase::TIdLogBase(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdLogStream()/* overload */ : Idlogbase::TIdLogBase() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idlogstream */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDLOGSTREAM)
using namespace Idlogstream;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdlogstreamHPP
