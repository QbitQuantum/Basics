// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSMetadata.pas' rev: 34.00 (Android)

#ifndef Datasnap_DsmetadataHPP
#define Datasnap_DsmetadataHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Datasnap.DSCommonProxy.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsmetadata
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSCustomMetaDataProvider;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSCustomMetaDataProvider : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	virtual bool __fastcall HasProvider();
	virtual Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader __fastcall GetProvider();
public:
	/* TComponent.Create */ inline __fastcall virtual TDSCustomMetaDataProvider(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSCustomMetaDataProvider() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsmetadata */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSMETADATA)
using namespace Datasnap::Dsmetadata;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsmetadataHPP
