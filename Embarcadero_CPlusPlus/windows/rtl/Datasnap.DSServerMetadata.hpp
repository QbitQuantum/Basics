// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSServerMetadata.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsservermetadataHPP
#define Datasnap_DsservermetadataHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DBXCommon.hpp>
#include <Datasnap.DSCommonServer.hpp>
#include <Datasnap.DSServer.hpp>
#include <Datasnap.DSCommonProxy.hpp>
#include <Datasnap.DSMetadata.hpp>
#include <Datasnap.DSServerResStrs.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsservermetadata
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSServerMetaDataProvider;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDSServerMetaDataProvider : public Datasnap::Dsmetadata::TDSCustomMetaDataProvider
{
	typedef Datasnap::Dsmetadata::TDSCustomMetaDataProvider inherited;
	
private:
	Datasnap::Dsserver::TDSServer* FServer;
	void __fastcall SetServer(Datasnap::Dsserver::TDSServer* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	virtual bool __fastcall HasProvider();
	virtual Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader __fastcall GetProvider();
	
__published:
	__property Datasnap::Dsserver::TDSServer* Server = {read=FServer, write=SetServer};
public:
	/* TComponent.Create */ inline __fastcall virtual TDSServerMetaDataProvider(System::Classes::TComponent* AOwner) : Datasnap::Dsmetadata::TDSCustomMetaDataProvider(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSServerMetaDataProvider() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsservermetadata */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSSERVERMETADATA)
using namespace Datasnap::Dsservermetadata;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsservermetadataHPP
