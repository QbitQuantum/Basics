// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.OBJ.Importer.pas' rev: 34.00 (Windows)

#ifndef Fmx_Obj_ImporterHPP
#define Fmx_Obj_ImporterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Import.hpp>
#include <FMX.Objects3D.hpp>
#include <System.Math.Vectors.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FMX.OBJ.Importer"

namespace Fmx
{
namespace Obj
{
namespace Importer
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TOBJModelImporter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOBJModelImporter : public Fmx::Import::TModelImporter
{
	typedef Fmx::Import::TModelImporter inherited;
	
public:
	virtual System::UnicodeString __fastcall GetDescription();
	virtual System::UnicodeString __fastcall GetExt();
	virtual bool __fastcall LoadFromFile(const System::UnicodeString AFileName, /* out */ Fmx::Objects3d::TMeshDynArray &AMesh, System::Classes::TComponent* const AOwner);
public:
	/* TObject.Create */ inline __fastcall TOBJModelImporter() : Fmx::Import::TModelImporter() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TOBJModelImporter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Importer */
}	/* namespace Obj */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_OBJ_IMPORTER)
using namespace Fmx::Obj::Importer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_OBJ)
using namespace Fmx::Obj;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Obj_ImporterHPP
