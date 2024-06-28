// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.ASE.Model.pas' rev: 34.00 (iOS)

#ifndef Fmx_Ase_ModelHPP
#define Fmx_Ase_ModelHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <FMX.ASE.Lexer.hpp>
#include <FMX.Import.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Ase
{
namespace Model
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAseMaterial;
struct TAseMesh;
class DELPHICLASS TAseModel;
class DELPHICLASS EAseParserError;
//-- type declarations -------------------------------------------------------
typedef System::DynamicArray<TAseMaterial*> TAseMaterialDynArray;

class PASCALIMPLEMENTATION TAseMaterial : public Fmx::Import::TGEMaterial
{
	typedef Fmx::Import::TGEMaterial inherited;
	
private:
	Fmx::Import::TGEMaterials* FSubMaterials;
	
public:
	__property Fmx::Import::TGEMaterials* SubMaterials = {read=FSubMaterials};
	__fastcall TAseMaterial();
	__fastcall virtual ~TAseMaterial();
};


struct DECLSPEC_DRECORD TAseMesh
{
	
private:
	typedef System::DynamicArray<Fmx::Import::TGEMesh*> _TAseMesh__1;
	
	
public:
	Fmx::Import::TGEVertexSource* FVertexSource;
	Fmx::Import::TGETriangleMeshID FTriangleMesh;
	System::TArray__1<int> FFaceMaterials;
	_TAseMesh__1 FSubMeshes;
};


typedef System::DynamicArray<TAseMesh> TAseMeshDynArray;

class PASCALIMPLEMENTATION TAseModel : public Fmx::Import::TCustomModel
{
	typedef Fmx::Import::TCustomModel inherited;
	
private:
	Fmx::Import::TGEMaterials* FMaterials;
	TAseMeshDynArray FMeshes;
	void __fastcall ParseVertexList(Fmx::Ase::Lexer::TAseLexer* const ALexer, const int ANumVertex, Fmx::Import::TGEVertexSource* const AVertexSource);
	void __fastcall ParseNormalList(Fmx::Ase::Lexer::TAseLexer* const ALexer, const int ANumFaceNormal, const int ANumVertexNormal, TAseMesh &AMesh);
	void __fastcall ParseTexCoordList(Fmx::Ase::Lexer::TAseLexer* const ALexer, const int ANumTexCoord, Fmx::Import::TGEVertexSource* const AVertexSource);
	void __fastcall ParseFaceList(Fmx::Ase::Lexer::TAseLexer* const ALexer, const int ANumFaces, TAseMesh &AMesh);
	void __fastcall ParseTFaceList(Fmx::Ase::Lexer::TAseLexer* const ALexer, const int ANumFaces, TAseMesh &AMesh);
	void __fastcall ParseMesh(Fmx::Ase::Lexer::TAseLexer* const ALexer, TAseMesh &AMesh);
	void __fastcall ParseMap(Fmx::Ase::Lexer::TAseLexer* const ALexer, System::UnicodeString &AFileName);
	void __fastcall ParseMaterialList(Fmx::Ase::Lexer::TAseLexer* const ALexer);
	void __fastcall ParseMaterial(Fmx::Ase::Lexer::TAseLexer* const ALexer, TAseMaterial* AMaterial);
	void __fastcall ParseGeometry(Fmx::Ase::Lexer::TAseLexer* const ALexer);
	void __fastcall ParseModel(Fmx::Ase::Lexer::TAseLexer* const ALexer);
	Fmx::Import::TGEMesh* __fastcall AddSubMesh(Fmx::Import::TGEVertexSource* const AVertexSource);
	
public:
	__property TAseMeshDynArray Meshes = {read=FMeshes};
	__property Fmx::Import::TGEMaterials* Materials = {read=FMaterials};
	virtual void __fastcall LoadFromFile(const System::UnicodeString AFileName);
	__fastcall TAseModel();
	__fastcall virtual ~TAseModel();
};


class PASCALIMPLEMENTATION EAseParserError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EAseParserError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EAseParserError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EAseParserError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EAseParserError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EAseParserError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EAseParserError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EAseParserError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EAseParserError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAseParserError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAseParserError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAseParserError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAseParserError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EAseParserError() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Model */
}	/* namespace Ase */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ASE_MODEL)
using namespace Fmx::Ase::Model;
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
#endif	// Fmx_Ase_ModelHPP
