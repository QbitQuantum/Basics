// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.DAE.Model.pas' rev: 34.00 (Windows)

#ifndef Fmx_Dae_ModelHPP
#define Fmx_Dae_ModelHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Math.hpp>
#include <System.Math.Vectors.hpp>
#include <FMX.DAE.Schema.hpp>
#include <FMX.Import.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Dae
{
namespace Model
{
//-- forward type declarations -----------------------------------------------
struct TDAEVertexSource;
struct TDAESurface;
struct TDAEExporterHelper /* Helper for enum 'TDAEExporter' */;
struct TGEPhongMapModeHelper /* Helper for enum 'TGEPhongMapMode' */;
struct TGEMap;
class DELPHICLASS TGEEffect;
struct TSourceModeHelper /* Helper for enum 'TSourceMode' */;
struct TSourceSemantic;
struct TDAEVertices;
class DELPHICLASS TDAEMesh;
class DELPHICLASS TDAEController;
class DELPHICLASS TDAEVisualNode;
class DELPHICLASS TDAEVisualScene;
class DELPHICLASS TDAEModel;
class DELPHICLASS EDAEError;
//-- type declarations -------------------------------------------------------
typedef TDAEVertexSource *PDAEVertexSource;

struct DECLSPEC_DRECORD TDAEVertexSource
{
public:
	System::UnicodeString Id;
#ifndef _WIN64
	System::DynamicArray<float> Data;
#else /* _WIN64 */
	System::TArray__1<float> Data;
#endif /* _WIN64 */
	int Stride;
};


struct DECLSPEC_DRECORD TDAESurface
{
public:
	System::UnicodeString FID;
	System::UnicodeString FSource;
};


typedef System::DynamicArray<TDAESurface> TDAESurfaceArray;

enum class DECLSPEC_DENUM TDAEExporter : unsigned char { ThreeDStudioMax, Maya, Unknown, de3DStudioMax _DEPRECATED_ATTRIBUTE3("Use TDAEExporter.ThreeDStudioMax")  = 0x0, deMaya _DEPRECATED_ATTRIBUTE3("Use TDAEExporter.Maya")  = 0x1, deUnknown _DEPRECATED_ATTRIBUTE3("Use TDAEExporter.Unknown")  = 0x2 };

typedef System::DynamicArray<TDAEVertexSource> TDAEVertexSourceDynArray;

enum class DECLSPEC_DENUM TGEPhongMapMode : unsigned char { Emission, Ambient, Diffuse, Specular, Shininess, Reflective, Reflectivity, Transparent, Transparency, pmEmission _DEPRECATED_ATTRIBUTE3("Use TGEPhongMapMode.Emission")  = 0, pmAmbient _DEPRECATED_ATTRIBUTE3("Use TGEPhongMapMode.Ambient")  = 1, pmDiffuse _DEPRECATED_ATTRIBUTE3("Use TGEPhongMapMode.Diffuse")  = 2, pmSpecular _DEPRECATED_ATTRIBUTE3("Use TGEPhongMapMode.Specular")  = 3, pmShininess _DEPRECATED_ATTRIBUTE3("Use TGEPhongMapMode.Shininess")  = 4, pmReflective _DEPRECATED_ATTRIBUTE3("Use TGEPhongMapMode.Reflective")  = 5, pmReflectivity _DEPRECATED_ATTRIBUTE3("Use TGEPhongMapMode.Reflectivity")  = 6, pmTransparent _DEPRECATED_ATTRIBUTE3("Use TGEPhongMapMode.Transparent")  = 7, mpTransparency _DEPRECATED_ATTRIBUTE3("Use TGEPhongMapMode.Transparency")  = 8 };

struct DECLSPEC_DRECORD TGEMap
{
public:
	Fmx::Import::TGEImage* Image;
	System::Uitypes::TAlphaColorF Color;
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGEEffect : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::UnicodeString FId;
	System::StaticArray<TGEMap, 9> FMaps;
public:
	/* TObject.Create */ inline __fastcall TGEEffect() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGEEffect() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum class DECLSPEC_DENUM TSourceMode : unsigned char { Vertex, Normal, TexCoord, smVertex _DEPRECATED_ATTRIBUTE3("Use TSourceMode.Vertex")  = 0x0, smNormal _DEPRECATED_ATTRIBUTE3("Use TSourceMode.Normal")  = 0x1, smTexCoord _DEPRECATED_ATTRIBUTE3("Use TSourceMode.TexCoord")  = 0x2 };

struct DECLSPEC_DRECORD TSourceSemantic
{
public:
	TDAEVertexSource *FSource;
	int FOffset;
};


typedef System::StaticArray<TSourceSemantic, 3> TSourceSemantics;

struct DECLSPEC_DRECORD TDAEVertices
{
public:
	System::UnicodeString Id;
	TSourceSemantics Sources;
};


typedef System::DynamicArray<TSourceSemantic> TSourceSemanticDynArray;

typedef System::StaticArray<TSourceSemantic, 3> TSourceSemanticList;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDAEMesh : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FId;
	Fmx::Import::TGEMeshDynArray FSubMeshes;
	
public:
	__property System::UnicodeString Id = {read=FId};
	__fastcall virtual ~TDAEMesh();
	__property Fmx::Import::TGEMeshDynArray SubMeshes = {read=FSubMeshes};
public:
	/* TObject.Create */ inline __fastcall TDAEMesh() : System::TObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDAEController : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FId;
	TDAEMesh* FMesh;
	
public:
	__property System::UnicodeString Id = {read=FId};
	__property TDAEMesh* Mesh = {read=FMesh};
public:
	/* TObject.Create */ inline __fastcall TDAEController() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDAEController() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<TDAEMesh*> TDAEMeshDynArray;

typedef System::DynamicArray<TDAEController*> TDAEControllerDynArray;

typedef System::DynamicArray<TDAEVisualNode*> TDAEVisualNodeDynArray;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDAEVisualNode : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<System::UnicodeString> _TDAEVisualNode__1;
	
	
private:
	System::Math::Vectors::TMatrix3D FTransformation;
	TDAEMeshDynArray FMesh;
	TDAEControllerDynArray FControllers;
	TDAEVisualNodeDynArray FChildren;
	System::UnicodeString FId;
	_TDAEVisualNode__1 FNodeUrls;
	System::TObject* FOwner;
	
public:
	__property System::Math::Vectors::TMatrix3D Transformation = {read=FTransformation};
	__property TDAEMeshDynArray Mesh = {read=FMesh};
	__property TDAEControllerDynArray Controllers = {read=FControllers};
	__property System::TObject* Owner = {read=FOwner};
	__property TDAEVisualNodeDynArray Children = {read=FChildren};
	__property System::UnicodeString Id = {read=FId};
	__fastcall virtual ~TDAEVisualNode();
public:
	/* TObject.Create */ inline __fastcall TDAEVisualNode() : System::TObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDAEVisualScene : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDAEVisualNodeDynArray FNodes;
	
public:
	__property TDAEVisualNodeDynArray Nodes = {read=FNodes};
public:
	/* TObject.Create */ inline __fastcall TDAEVisualScene() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDAEVisualScene() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DynamicArray<TDAEVisualScene*> TDAEVisualSceneDynArray;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDAEModel : public Fmx::Import::TCustomModel
{
	typedef Fmx::Import::TCustomModel inherited;
	
	
private:
	typedef System::DynamicArray<Fmx::Import::TGEImage*> _TDAEModel__1;
	
	typedef System::DynamicArray<TGEEffect*> _TDAEModel__2;
	
	typedef System::DynamicArray<TDAEModel*> _TDAEModel__3;
	
	
private:
	TDAEExporter FExporter;
	System::UnicodeString FFileName;
	_TDAEModel__1 FImageList;
	TDAEMeshDynArray FMeshes;
	TDAEControllerDynArray FControllers;
	Fmx::Import::TGEMaterials* FMaterials;
	_TDAEModel__2 FEffects;
	_TDAEModel__3 FModels;
	TDAEVisualNodeDynArray FAllNodes;
	TDAEVisualSceneDynArray FSceneList;
	Fmx::Import::TGEVertexSource* __fastcall GetVertexSource(const TSourceSemantics &AVertex, const TSourceSemantics &ASemantics);
	Fmx::Import::TGEMesh* __fastcall LoadPolygons(const Fmx::Dae::Schema::_di_IXMLPolygons_type ASubMesh, const TSourceSemantics &AVertex, const TDAEVertexSourceDynArray ASources);
	Fmx::Import::TGEMesh* __fastcall LoadTriangles(const Fmx::Dae::Schema::_di_IXMLTriangles_type ASubMesh, const TSourceSemantics &AVertex, const TDAEVertexSourceDynArray ASources);
	Fmx::Import::TGEMesh* __fastcall LoadPolylist(const Fmx::Dae::Schema::_di_IXMLPolylist_type ASubMesh, const TSourceSemantics &AVertex, const TDAEVertexSourceDynArray ASources);
	TGEEffect* __fastcall FindEffectById(const System::UnicodeString AName);
	Fmx::Import::TGEImage* __fastcall FindImageById(const System::UnicodeString AName);
	TDAEMesh* __fastcall FindMeshById(const System::UnicodeString AName);
	TDAEVisualNode* __fastcall FindNodeById(const System::UnicodeString AName);
	TDAEController* __fastcall FindControllerById(const System::UnicodeString AName);
	TDAEMesh* __fastcall GetMesh(const Fmx::Dae::Schema::_di_IXMLGeometry_type AGeometry)/* overload */;
	Fmx::Import::TGEImage* __fastcall GetImage(const Fmx::Dae::Schema::_di_IXMLImage_type AImage);
	Fmx::Import::TGEMaterial* __fastcall GetMaterial(const Fmx::Dae::Schema::_di_IXMLMaterial_type AMaterial);
	TGEEffect* __fastcall GetEffect(const Fmx::Dae::Schema::_di_IXMLEffect_type AEffect);
	TDAEVisualScene* __fastcall GetScene(const Fmx::Dae::Schema::_di_IXMLVisual_scene_type AScene);
	TDAEVisualNode* __fastcall GetNode(const Fmx::Dae::Schema::_di_IXMLNode_type ANode);
	TDAEController* __fastcall GetController(const Fmx::Dae::Schema::_di_IXMLController_type AController);
	void __fastcall AddNode(TDAEVisualNode* const ANode);
	void __fastcall FindNodeUrls();
	void __fastcall ImportFromGeometryLib(const Fmx::Dae::Schema::_di_IXMLLibrary_geometries_type AGeometryLib);
	void __fastcall ImportFromImageLib(const Fmx::Dae::Schema::_di_IXMLLibrary_images_type AImageLib);
	void __fastcall ImportFromMaterialLib(const Fmx::Dae::Schema::_di_IXMLLibrary_materials_type AMaterialLib);
	void __fastcall ImportFromEffectLib(const Fmx::Dae::Schema::_di_IXMLLibrary_effects_type AEffectLib);
	void __fastcall ImportFromSceneLib(const Fmx::Dae::Schema::_di_IXMLLibrary_visual_scenes_type ASceneLib);
	void __fastcall ImportFromNodeLib(const Fmx::Dae::Schema::_di_IXMLLibrary_nodes_type ANodesLib);
	void __fastcall ImportExporter(const Fmx::Dae::Schema::_di_IXMLAsset_type AAssetLib);
	void __fastcall ImportFromControllersLib(const Fmx::Dae::Schema::_di_IXMLLibrary_controllers_type AControlerLib);
	void __fastcall ImportFromCot(TGEMap &AMap, const Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type AMapCot, const TDAESurfaceArray ASurfaces);
	
public:
	__property TDAEVisualSceneDynArray SceneList = {read=FSceneList};
	__property Fmx::Import::TGEMaterials* Materials = {read=FMaterials};
	__property TDAEMeshDynArray Meshes = {read=FMeshes};
	virtual void __fastcall LoadFromFile(const System::UnicodeString AFileName);
	__fastcall TDAEModel();
	__fastcall virtual ~TDAEModel();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EDAEError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EDAEError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EDAEError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDAEError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDAEError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDAEError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDAEError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDAEError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDAEError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDAEError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDAEError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDAEError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDAEError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDAEError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Model */
}	/* namespace Dae */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DAE_MODEL)
using namespace Fmx::Dae::Model;
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
#endif	// Fmx_Dae_ModelHPP
