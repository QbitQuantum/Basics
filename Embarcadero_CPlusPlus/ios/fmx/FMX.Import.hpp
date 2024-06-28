// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Import.pas' rev: 34.00 (iOS)

#ifndef Fmx_ImportHPP
#define Fmx_ImportHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Math.Vectors.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Objects3D.hpp>
#include <FMX.MaterialSources.hpp>
#include <FMX.Graphics.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Import
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IModelImporter;
typedef System::DelphiInterface<IModelImporter> _di_IModelImporter;
class DELPHICLASS TModelImportServices;
class DELPHICLASS TModelImporter;
class DELPHICLASS TCustomModel;
class DELPHICLASS TGEImage;
class DELPHICLASS TGEBitmap;
class DELPHICLASS TGEMaterial;
class DELPHICLASS TGEMaterials;
struct TGEVertex;
struct TGEVertexID;
class DELPHICLASS TGEVertexSource;
class DELPHICLASS TGEMesh;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{DBEB065D-3BE7-4289-8F24-9CD128902366}") IModelImporter  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetDescription() = 0 ;
	virtual System::UnicodeString __fastcall GetExt() = 0 ;
	virtual bool __fastcall LoadFromFile(const System::UnicodeString AFileName, /* out */ Fmx::Objects3d::TMeshDynArray &AMesh, System::Classes::TComponent* const AOwner) = 0 ;
};

class PASCALIMPLEMENTATION TModelImportServices : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
__published:
	__classmethod int __fastcall GetSupportedFileTypesCount();
	__classmethod System::UnicodeString __fastcall GetFileExt(const int index);
	__classmethod System::UnicodeString __fastcall GetFileDescription(const int index);
	__classmethod virtual int __fastcall RegisterImporter(const _di_IModelImporter AMeshImporter);
	__classmethod virtual void __fastcall UnregisterImporter(int AMeshImporterIndex);
	__classmethod bool __fastcall LoadFromFile(const System::UnicodeString AFileName, /* out */ Fmx::Objects3d::TMeshDynArray &AMesh, System::Classes::TComponent* const AOwner);
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TModelImportServices() { }
	
public:
	/* TObject.Create */ inline __fastcall TModelImportServices() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TModelImporter : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	virtual System::UnicodeString __fastcall GetDescription() = 0 ;
	virtual System::UnicodeString __fastcall GetExt() = 0 ;
	virtual bool __fastcall LoadFromFile(const System::UnicodeString AFileName, /* out */ Fmx::Objects3d::TMeshDynArray &AMesh, System::Classes::TComponent* const AOwner) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TModelImporter() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TModelImporter() { }
	
private:
	void *__IModelImporter;	// IModelImporter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DBEB065D-3BE7-4289-8F24-9CD128902366}
	operator _di_IModelImporter()
	{
		_di_IModelImporter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IModelImporter*(void) { return (IModelImporter*)&__IModelImporter; }
	#endif
	
};


class PASCALIMPLEMENTATION TCustomModel : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall LoadFromFile(const System::UnicodeString AFileName) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TCustomModel() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomModel() { }
	
};


class PASCALIMPLEMENTATION TGEImage : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::UnicodeString FId;
	System::UnicodeString FName;
	System::UnicodeString FFileName;
public:
	/* TObject.Create */ inline __fastcall TGEImage() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGEImage() { }
	
};


class PASCALIMPLEMENTATION TGEBitmap : public Fmx::Graphics::TBitmap
{
	typedef Fmx::Graphics::TBitmap inherited;
	
private:
	System::UnicodeString FFileName;
	
public:
	__fastcall virtual TGEBitmap(const System::UnicodeString AFileName);
	__property System::UnicodeString FileName = {read=FFileName};
public:
	/* TBitmap.Create */ inline __fastcall virtual TGEBitmap()/* overload */ : Fmx::Graphics::TBitmap() { }
	/* TBitmap.Create */ inline __fastcall virtual TGEBitmap(const int AWidth, const int AHeight)/* overload */ : Fmx::Graphics::TBitmap(AWidth, AHeight) { }
	/* TBitmap.CreateFromStream */ inline __fastcall virtual TGEBitmap(System::Classes::TStream* const AStream) : Fmx::Graphics::TBitmap(AStream) { }
	/* TBitmap.CreateFromBitmapAndMask */ inline __fastcall TGEBitmap(Fmx::Graphics::TBitmap* const Bitmap, Fmx::Graphics::TBitmap* const Mask) : Fmx::Graphics::TBitmap(Bitmap, Mask) { }
	/* TBitmap.Destroy */ inline __fastcall virtual ~TGEBitmap() { }
	
};


class PASCALIMPLEMENTATION TGEMaterial : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::UnicodeString FName;
	System::Uitypes::TAlphaColorF FDiffuse;
	System::Uitypes::TAlphaColorF FAmbient;
	System::Uitypes::TAlphaColorF FSpecular;
	System::UnicodeString FDiffuseMap;
	TGEBitmap* FDiffuseBitmap;
public:
	/* TObject.Create */ inline __fastcall TGEMaterial() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGEMaterial() { }
	
};


typedef System::DynamicArray<TGEMaterial*> TGEMaterialDynArray;

class PASCALIMPLEMENTATION TGEMaterials : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<TGEBitmap*> _TGEMaterials__1;
	
	
public:
	TGEMaterial* operator[](int Index) { return this->Items[Index]; }
	
private:
	bool FMaterialsOwner;
	TGEMaterialDynArray FMaterials;
	_TGEMaterials__1 FBitmaps;
	TGEBitmap* __fastcall CreateBitmap(const System::UnicodeString AFileName);
	void __fastcall SetLocalTexturePath(const System::UnicodeString APath);
	int __fastcall GetCount();
	void __fastcall SetCount(const int ACount);
	TGEMaterial* __fastcall GetItems(int AIndex);
	void __fastcall SetItems(int AIndex, TGEMaterial* AItem);
	
public:
	__fastcall TGEMaterials(bool AMaterialsOwner);
	__fastcall virtual ~TGEMaterials();
	void __fastcall LoadImages(const System::UnicodeString APath);
	TGEMaterial* __fastcall Add(TGEMaterial* const AMaterial);
	__property int Count = {read=GetCount, write=SetCount, nodefault};
	__property TGEMaterial* Items[int Index] = {read=GetItems, write=SetItems/*, default*/};
	__property TGEMaterialDynArray Materials = {read=FMaterials};
};


typedef TGEVertex *PGEVertex;

struct DECLSPEC_DRECORD TGEVertex
{
public:
	System::Math::Vectors::TPoint3D Pos;
	System::Math::Vectors::TPoint3D Nor;
	System::Types::TPointF Tex;
	int Sth;
	bool GenerateNormal;
};


struct DECLSPEC_DRECORD TGEVertexID
{
public:
	int Position;
	int Normal;
	int Texture0;
	int SmoothGroup;
};


typedef System::DynamicArray<TGEVertexID> TGEPoligonID;

typedef System::StaticArray<TGEVertexID, 3> TGETriangleID;

typedef System::DynamicArray<TGETriangleID> TGETriangleMeshID;

typedef System::DynamicArray<TGEVertex> TGEVertexArray;

class PASCALIMPLEMENTATION TGEVertexSource : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Fmx::Types3d::TPoint3DDynArray FPositionSource;
	Fmx::Types3d::TPoint3DDynArray FNormalSource;
	Fmx::Types3d::TPointFDynArray FTexture0Source;
	void __fastcall SetTextue0SourceArray(const Fmx::Types3d::TPointFDynArray ASource);
	
public:
	void __fastcall SetPositionSource(const System::TArray__1<float> ASource);
	void __fastcall SetNormalSource(const System::TArray__1<float> ASource);
	void __fastcall SetTextue0Source(const System::TArray__1<float> ASource, int AStride = 0x2);
	int __fastcall AddPositionSource(const System::TArray__1<float> ASource);
	int __fastcall AddNormalSource(const System::TArray__1<float> ASource);
	int __fastcall AddTextue0Source(const System::TArray__1<float> ASource);
	__property Fmx::Types3d::TPoint3DDynArray PositionSource = {write=FPositionSource};
	__property Fmx::Types3d::TPoint3DDynArray NormalSource = {write=FNormalSource};
	__property Fmx::Types3d::TPointFDynArray Texture0Source = {write=SetTextue0SourceArray};
public:
	/* TObject.Create */ inline __fastcall TGEVertexSource() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGEVertexSource() { }
	
};


class PASCALIMPLEMENTATION TGEMesh : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FTriangleCount;
	TGEVertexArray FTriangles;
	TGEVertexSource* FSource;
	System::UnicodeString FMaterialName;
	void __fastcall CalculateTriNormal(TGEVertex &Av1, TGEVertex &Av2, TGEVertex &Av3);
	
public:
	__fastcall TGEMesh(TGEVertexSource* const ASource);
	__property System::UnicodeString MaterialName = {read=FMaterialName, write=FMaterialName};
	void __fastcall AddVertex(const TGEVertexID &AVertex);
	void __fastcall AddTriangle(const TGETriangleID &ATriangle);
	void __fastcall AddPoligon(const TGEPoligonID APoligon);
	void __fastcall AddTriangleMesh(const TGETriangleMeshID ATriangleMesh);
	Fmx::Objects3d::TMesh* __fastcall CreateMesh(System::Classes::TComponent* AOwner, const System::Math::Vectors::TMatrix3D &ATransform, const TGEMaterialDynArray AMaterials);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TGEMesh() { }
	
};


typedef System::DynamicArray<TGEMesh*> TGEMeshDynArray;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TGEVertexID NullVertexID;
extern DELPHI_PACKAGE bool __fastcall SetLocalPath(const System::UnicodeString APath, System::UnicodeString &AFileName);
extern DELPHI_PACKAGE System::TArray__1<float> __fastcall FloatStringsToSingleDynArray(const System::UnicodeString AStr);
extern DELPHI_PACKAGE System::TArray__1<int> __fastcall IntStringsToIntegerDynArray(const System::UnicodeString AStr)/* overload */;
extern DELPHI_PACKAGE System::TArray__1<System::UnicodeString> __fastcall StringsToStringDynArray(const System::UnicodeString AStr)/* overload */;
}	/* namespace Import */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_IMPORT)
using namespace Fmx::Import;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_ImportHPP
