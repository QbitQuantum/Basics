// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSTransport.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DstransportHPP
#define Datasnap_DstransportHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXMessageHandlerCommon.hpp>
#include <Data.DBXTransport.hpp>
#include <Datasnap.DSCommonServer.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dstransport
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSJSONProtocolHandlerFactory;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSJSONProtocolHandlerFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDSJSONProtocolHandlerFactory(Datasnap::Dscommonserver::TDSServerTransport* const ATransport);
	__fastcall virtual ~TDSJSONProtocolHandlerFactory();
	Data::Dbxmessagehandlercommon::TDBXProtocolHandler* __fastcall CreateProtocolHandler(Data::Dbxtransport::TDbxChannel* const Channel);
	
private:
	Datasnap::Dscommonserver::TDSServerTransport* FTransport;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dstransport */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSTRANSPORT)
using namespace Datasnap::Dstransport;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DstransportHPP
