// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.ASE.Importer.pas' rev: 34.00 (iOS)

#ifndef Fmx_Ase_ImporterHPP
#define Fmx_Ase_ImporterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FMX.Import.hpp>
#include <FMX.Objects3D.hpp>

//-- user supplied -----------------------------------------------------------
namespace Fmx
{
namespace Ase
{
namespace Importer
{
  _INIT_UNIT(Fmx_Ase_Importer);
}	/* namespace Importer */
}	/* namespace Ase */
}	/* namespace Fmx */

namespace Fmx
{
namespace Ase
{
namespace Importer
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TASEModelImporter;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TASEModelImporter : public Fmx::Import::TModelImporter
{
	typedef Fmx::Import::TModelImporter inherited;
	
public:
	virtual System::UnicodeString __fastcall GetDescription();
	virtual System::UnicodeString __fastcall GetExt();
	virtual bool __fastcall LoadFromFile(const System::UnicodeString AFileName, /* out */ Fmx::Objects3d::TMeshDynArray &AMesh, System::Classes::TComponent* const AOwner);
public:
	/* TObject.Create */ inline __fastcall TASEModelImporter() : Fmx::Import::TModelImporter() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TASEModelImporter() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Importer */
}	/* namespace Ase */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ASE_IMPORTER)
using namespace Fmx::Ase::Importer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ASE)
using namespace Fmx::Ase;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Ase_ImporterHPP
