// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSConnectionMetaDataProvider.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsconnectionmetadataproviderHPP
#define Datasnap_DsconnectionmetadataproviderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Datasnap.DSCommonProxy.hpp>
#include <Datasnap.DSMetadata.hpp>
#include <Data.SqlExpr.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsconnectionmetadataprovider
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSConnectionMetaDataProvider;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDSConnectionMetaDataProvider : public Datasnap::Dsmetadata::TDSCustomMetaDataProvider
{
	typedef Datasnap::Dsmetadata::TDSCustomMetaDataProvider inherited;
	
private:
	Data::Sqlexpr::TSQLConnection* FConnection;
	void __fastcall SetConnection(Data::Sqlexpr::TSQLConnection* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	virtual bool __fastcall HasProvider();
	virtual Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader __fastcall GetProvider();
	
__published:
	__property Data::Sqlexpr::TSQLConnection* SQLConnection = {read=FConnection, write=SetConnection};
public:
	/* TComponent.Create */ inline __fastcall virtual TDSConnectionMetaDataProvider(System::Classes::TComponent* AOwner) : Datasnap::Dsmetadata::TDSCustomMetaDataProvider(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSConnectionMetaDataProvider() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsconnectionmetadataprovider */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSCONNECTIONMETADATAPROVIDER)
using namespace Datasnap::Dsconnectionmetadataprovider;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsconnectionmetadataproviderHPP
