// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.OBJ.Model.pas' rev: 34.00 (Windows)

#ifndef Fmx_Obj_ModelHPP
#define Fmx_Obj_ModelHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects3D.hpp>
#include <System.Math.hpp>
#include <FMX.Import.hpp>
#include <System.UITypes.hpp>
#include <System.Math.Vectors.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Obj
{
namespace Model
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TOBJMesh;
class DELPHICLASS TOBJModel;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOBJMesh : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FName;
	Fmx::Import::TGEMeshDynArray FSubMeshes;
	Fmx::Import::TGEMesh* __fastcall ReadUseMaterial(const System::UnicodeString ALine, Fmx::Import::TGEVertexSource* const AVertexSource);
	
public:
	__fastcall TOBJMesh();
	__fastcall virtual ~TOBJMesh();
	__property Fmx::Import::TGEMeshDynArray SubMeshes = {read=FSubMeshes};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<TOBJMesh*> TOBJMeshDynArray;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOBJModel : public Fmx::Import::TCustomModel
{
	typedef Fmx::Import::TCustomModel inherited;
	
private:
	Fmx::Import::TGEMaterials* FMaterials;
	TOBJMeshDynArray FMeshes;
	Fmx::Import::TGEVertexSource* FVertexSource;
	int FSmoothGroup;
	System::UnicodeString __fastcall ReadMaterials(const System::UnicodeString ALine);
	void __fastcall ReadSources(const System::UnicodeString ALine);
	TOBJMesh* __fastcall ReadGeometry(const System::UnicodeString ALine);
	void __fastcall ReadSmoothGroup(const System::UnicodeString ALine);
	void __fastcall ReadFaces(Fmx::Import::TGEMesh* const AMesh, const System::UnicodeString ALine);
	
public:
	__property Fmx::Import::TGEMaterials* Materials = {read=FMaterials};
	__property TOBJMeshDynArray Meshes = {read=FMeshes};
	virtual void __fastcall LoadFromFile(const System::UnicodeString AFileName);
	__fastcall TOBJModel();
	__fastcall virtual ~TOBJModel();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Model */
}	/* namespace Obj */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_OBJ_MODEL)
using namespace Fmx::Obj::Model;
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
#endif	// Fmx_Obj_ModelHPP
