// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdTCPStream.pas' rev: 34.00 (Android)

#ifndef IdtcpstreamHPP
#define IdtcpstreamHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdTCPConnection.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idtcpstream
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdTCPStream;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdTCPStream : public Idglobal::TIdBaseStream
{
	typedef Idglobal::TIdBaseStream inherited;
	
protected:
	Idtcpconnection::TIdTCPConnection* FConnection;
	int FWriteThreshold;
	bool FWriteBuffering;
#ifndef __aarch64__
	virtual int __fastcall IdRead(Idglobal::TIdBytes &VBuffer, int AOffset, int ACount);
	virtual int __fastcall IdWrite(const Idglobal::TIdBytes ABuffer, int AOffset, int ACount);
#else /* __aarch64__ */
	virtual long __fastcall IdRead(Idglobal::TIdBytes &VBuffer, long AOffset, long ACount);
	virtual long __fastcall IdWrite(const Idglobal::TIdBytes ABuffer, long AOffset, long ACount);
#endif /* __aarch64__ */
	virtual __int64 __fastcall IdSeek(const __int64 AOffset, System::Classes::TSeekOrigin AOrigin);
	virtual void __fastcall IdSetSize(__int64 ASize);
	
public:
	__fastcall TIdTCPStream(Idtcpconnection::TIdTCPConnection* AConnection, const int AWriteThreshold);
	__fastcall virtual ~TIdTCPStream();
	__property Idtcpconnection::TIdTCPConnection* Connection = {read=FConnection};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idtcpstream */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDTCPSTREAM)
using namespace Idtcpstream;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdtcpstreamHPP
