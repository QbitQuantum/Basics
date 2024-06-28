// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.DAE.Importer.pas' rev: 34.00 (Windows)

#ifndef Fmx_Dae_ImporterHPP
#define Fmx_Dae_ImporterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FMX.Import.hpp>
#include <FMX.DAE.Schema.hpp>
#include <FMX.Objects3D.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FMX.DAE.Importer"

namespace Fmx
{
namespace Dae
{
namespace Importer
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDAEModelImporter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDAEModelImporter : public Fmx::Import::TModelImporter
{
	typedef Fmx::Import::TModelImporter inherited;
	
public:
	virtual System::UnicodeString __fastcall GetDescription();
	virtual System::UnicodeString __fastcall GetExt();
	virtual bool __fastcall LoadFromFile(const System::UnicodeString AFileName, /* out */ Fmx::Objects3d::TMeshDynArray &AMesh, System::Classes::TComponent* const AOwner);
public:
	/* TObject.Create */ inline __fastcall TDAEModelImporter() : Fmx::Import::TModelImporter() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDAEModelImporter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Importer */
}	/* namespace Dae */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DAE_IMPORTER)
using namespace Fmx::Dae::Importer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DAE)
using namespace Fmx::Dae;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Dae_ImporterHPP
