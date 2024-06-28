// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProxyDelphi.pas' rev: 34.00 (Android)

#ifndef Datasnap_DsproxydelphiHPP
#define Datasnap_DsproxydelphiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Datasnap.DSProxyWriter.hpp>

//-- user supplied -----------------------------------------------------------
namespace Datasnap
{
namespace Dsproxydelphi
{
  _INIT_UNIT(Datasnap_Dsproxydelphi);
}	/* namespace Dsproxydelphi */
}	/* namespace Datasnap */

namespace Datasnap
{
namespace Dsproxydelphi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSCustomExtendedProxyWriter;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSCustomExtendedProxyWriter : public Datasnap::Dsproxywriter::TDSCustomProxyWriter
{
	typedef Datasnap::Dsproxywriter::TDSCustomProxyWriter inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetClassNameSuffix();
	
public:
	virtual System::TArray__1<System::UnicodeString> __fastcall GetProxyClassNames();
public:
	/* TDSCustomProxyWriter.Create */ inline __fastcall TDSCustomExtendedProxyWriter() : Datasnap::Dsproxywriter::TDSCustomProxyWriter() { }
	/* TDSCustomProxyWriter.Destroy */ inline __fastcall virtual ~TDSCustomExtendedProxyWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsproxydelphi */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROXYDELPHI)
using namespace Datasnap::Dsproxydelphi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproxydelphiHPP
