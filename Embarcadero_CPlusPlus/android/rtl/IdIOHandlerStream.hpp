// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdIOHandlerStream.pas' rev: 34.00 (Android)

#ifndef IdiohandlerstreamHPP
#define IdiohandlerstreamHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdBaseComponent.hpp>
#include <IdGlobal.hpp>
#include <IdIOHandler.hpp>
#include <IdStream.hpp>
#include <IdComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idiohandlerstream
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdIOHandlerStream;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdIOHandlerStreamType : unsigned char { stRead, stWrite, stReadWrite };

typedef void __fastcall (__closure *TIdOnGetStreams)(TIdIOHandlerStream* ASender, System::Classes::TStream* &VReceiveStream, System::Classes::TStream* &VSendStream);

class PASCALIMPLEMENTATION TIdIOHandlerStream : public Idiohandler::TIdIOHandler
{
	typedef Idiohandler::TIdIOHandler inherited;
	
protected:
	bool FFreeStreams;
	TIdOnGetStreams FOnGetStreams;
	System::Classes::TStream* FReceiveStream;
	System::Classes::TStream* FSendStream;
	TIdIOHandlerStreamType FStreamType;
	virtual void __fastcall InitComponent();
	virtual int __fastcall ReadDataFromSource(Idglobal::TIdBytes &VBuffer);
	virtual int __fastcall WriteDataToTarget(const Idglobal::TIdBytes ABuffer, const int AOffset, const int ALength);
	virtual bool __fastcall SourceIsAvailable();
	virtual int __fastcall CheckForError(int ALastResult);
	virtual void __fastcall RaiseError(int AError);
	
public:
	bool __fastcall StreamingAvailable();
	virtual void __fastcall CheckForDisconnect(bool ARaiseExceptionIfDisconnected = true, bool AIgnoreBuffer = false);
	__fastcall virtual TIdIOHandlerStream(System::Classes::TComponent* AOwner, System::Classes::TStream* AReceiveStream, System::Classes::TStream* ASendStream)/* overload */;
	__fastcall TIdIOHandlerStream(System::Classes::TComponent* AOwner)/* overload */;
	virtual bool __fastcall Connected();
	virtual void __fastcall Close();
	virtual void __fastcall Open();
	virtual bool __fastcall Readable(int AMSec = 0xffffffff);
	__property System::Classes::TStream* ReceiveStream = {read=FReceiveStream};
	__property System::Classes::TStream* SendStream = {read=FSendStream};
	__property TIdIOHandlerStreamType StreamType = {read=FStreamType, nodefault};
	
__published:
	__property bool FreeStreams = {read=FFreeStreams, write=FFreeStreams, default=1};
	__property TIdOnGetStreams OnGetStreams = {read=FOnGetStreams, write=FOnGetStreams};
public:
	/* TIdIOHandler.Destroy */ inline __fastcall virtual ~TIdIOHandlerStream() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdIOHandlerStream()/* overload */ : Idiohandler::TIdIOHandler() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idiohandlerstream */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDIOHANDLERSTREAM)
using namespace Idiohandlerstream;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdiohandlerstreamHPP
