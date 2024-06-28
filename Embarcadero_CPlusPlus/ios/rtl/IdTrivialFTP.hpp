// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdTrivialFTP.pas' rev: 34.00 (iOS)

#ifndef IdtrivialftpHPP
#define IdtrivialftpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdGlobal.hpp>
#include <IdTrivialFTPBase.hpp>
#include <IdUDPClient.hpp>
#include <IdComponent.hpp>
#include <IdUDPBase.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idtrivialftp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdTrivialFTP;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdTrivialFTP : public Idudpclient::TIdUDPClient
{
	typedef Idudpclient::TIdUDPClient inherited;
	
protected:
	Idtrivialftpbase::TIdTFTPMode FMode;
	int FRequestedBlockSize;
	System::Word FPeerPort;
	System::UnicodeString FPeerIP;
	System::UnicodeString __fastcall ModeToStr();
	void __fastcall CheckOptionAck(const Idglobal::TIdBytes OptionPacket, bool Reading);
	void __fastcall SendAck(const System::Word BlockNumber);
	void __fastcall RaiseError(const Idglobal::TIdBytes ErrorPacket);
	virtual void __fastcall InitComponent();
	
public:
	void __fastcall Get(const System::UnicodeString ServerFile, System::Classes::TStream* DestinationStream)/* overload */;
	void __fastcall Get(const System::UnicodeString ServerFile, const System::UnicodeString LocalFile)/* overload */;
	void __fastcall Put(System::Classes::TStream* SourceStream, const System::UnicodeString ServerFile)/* overload */;
	void __fastcall Put(const System::UnicodeString LocalFile, const System::UnicodeString ServerFile)/* overload */;
	
__published:
	__property Idtrivialftpbase::TIdTFTPMode TransferMode = {read=FMode, write=FMode, default=1};
	__property int RequestedBlockSize = {read=FRequestedBlockSize, write=FRequestedBlockSize, default=1500};
	__property OnWork;
	__property OnWorkBegin;
	__property OnWorkEnd;
public:
	/* TIdUDPClient.Destroy */ inline __fastcall virtual ~TIdTrivialFTP() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdTrivialFTP(System::Classes::TComponent* AOwner)/* overload */ : Idudpclient::TIdUDPClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdTrivialFTP()/* overload */ : Idudpclient::TIdUDPClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const Idtrivialftpbase::TIdTFTPMode GTransferMode = (Idtrivialftpbase::TIdTFTPMode)(1);
static constexpr System::Word GFRequestedBlockSize = System::Word(0x5dc);
static constexpr System::Word GReceiveTimeout = System::Word(0xfa0);
}	/* namespace Idtrivialftp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDTRIVIALFTP)
using namespace Idtrivialftp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdtrivialftpHPP
