// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Direct3D.pas' rev: 34.00 (Windows)

#ifndef Winapi_Direct3dHPP
#define Winapi_Direct3dHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.DXTypes.hpp>

//-- user supplied -----------------------------------------------------------
#define DIRECT3D_VERSION         0x0800
#include "d3d.h"
#include "d3dtypes.h"
#include "d3dcaps.h"
typedef LPD3DVALIDATECALLBACK TD3DValidateCallback;
typedef LPD3DENUMTEXTUREFORMATSCALLBACK TD3DEnumTextureFormatsCallback;
typedef LPD3DENUMPIXELFORMATSCALLBACK TD3DEnumPixelFormatsCallback;

namespace Winapi
{
namespace Direct3d
{
//-- forward type declarations -----------------------------------------------
struct TDXFileLoadResource;
struct TDXFileLoadMemory;
__interface DELPHIINTERFACE IDirectXFile;
typedef System::DelphiInterface<IDirectXFile> _di_IDirectXFile;
__interface DELPHIINTERFACE IDirectXFileEnumObject;
typedef System::DelphiInterface<IDirectXFileEnumObject> _di_IDirectXFileEnumObject;
__interface DELPHIINTERFACE IDirectXFileSaveObject;
typedef System::DelphiInterface<IDirectXFileSaveObject> _di_IDirectXFileSaveObject;
__interface DELPHIINTERFACE IDirectXFileObject;
typedef System::DelphiInterface<IDirectXFileObject> _di_IDirectXFileObject;
__interface DELPHIINTERFACE IDirectXFileData;
typedef System::DelphiInterface<IDirectXFileData> _di_IDirectXFileData;
__interface DELPHIINTERFACE IDirectXFileDataReference;
typedef System::DelphiInterface<IDirectXFileDataReference> _di_IDirectXFileDataReference;
__interface DELPHIINTERFACE IDirectXFileBinary;
typedef System::DelphiInterface<IDirectXFileBinary> _di_IDirectXFileBinary;
//-- type declarations -------------------------------------------------------
typedef GUID TRefClsID;

typedef float TD3DValue;

using Winapi::Dxtypes::PD3DValue;

typedef int TD3DFixed;

typedef D3DCOLOR TD3DColor;

typedef PD3DColor PD3DColor;

typedef unsigned *PD3DMaterialHandle;

typedef unsigned TD3DMaterialHandle;

typedef unsigned *PD3DTextureHandle;

typedef unsigned TD3DTextureHandle;

typedef unsigned *PD3DMatrixHandle;

typedef unsigned TD3DMatrixHandle;

typedef _D3DCOLORVALUE *PD3DColorValue;

typedef _D3DCOLORVALUE TD3DColorValue;

typedef _D3DRECT *PD3DRect;

typedef _D3DRECT TD3DRect;

typedef _D3DVECTOR *PD3DVector;

typedef _D3DVECTOR TD3DVector;

typedef _D3DHVERTEX *PD3DHVertex;

typedef _D3DHVERTEX TD3DHVertex;

typedef _D3DTLVERTEX *PD3DTLVertex;

typedef _D3DTLVERTEX TD3DTLVertex;

typedef _D3DLVERTEX *PD3DLVertex;

typedef _D3DLVERTEX TD3DLVertex;

typedef _D3DVERTEX *PD3DVertex;

typedef _D3DVERTEX TD3DVertex;

typedef _D3DMATRIX *PD3DMatrix;

typedef _D3DMATRIX TD3DMatrix;

typedef _D3DVIEWPORT *PD3DViewport;

typedef _D3DVIEWPORT TD3DViewport;

typedef _D3DVIEWPORT2 *PD3DViewport2;

typedef _D3DVIEWPORT2 TD3DViewport2;

typedef _D3DVIEWPORT7 *PD3DViewport7;

typedef _D3DVIEWPORT7 TD3DViewport7;

typedef _D3DTRANSFORMDATA *PD3DTransformData;

typedef _D3DTRANSFORMDATA TD3DTransformData;

typedef _D3DLIGHTINGELEMENT *PD3DLightingElement;

typedef _D3DLIGHTINGELEMENT TD3DLightingElement;

typedef _D3DMATERIAL *PD3DMaterial;

typedef _D3DMATERIAL TD3DMaterial;

typedef _D3DMATERIAL7 *PD3DMaterial7;

typedef _D3DMATERIAL7 TD3DMaterial7;

typedef _D3DLIGHT *PD3DLight;

typedef _D3DLIGHT TD3DLight;

typedef _D3DLIGHT7 *PD3DLight7;

typedef _D3DLIGHT7 TD3DLight7;

typedef _D3DLIGHT2 *PD3DLight2;

typedef _D3DLIGHT2 TD3DLight2;

typedef _D3DLIGHTDATA *PD3DLightData;

typedef _D3DLIGHTDATA TD3DLightData;

typedef unsigned TD3DColorModel;

typedef _D3DOPCODE *PD3DOpcode;

typedef _D3DOPCODE TD3DOpcode;

typedef _D3DINSTRUCTION *PD3DInstruction;

typedef _D3DINSTRUCTION TD3DInstruction;

typedef _D3DTEXTURELOAD *PD3DTextureLoad;

typedef _D3DTEXTURELOAD TD3DTextureLoad;

typedef _D3DPICKRECORD *PD3DPickRecord;

typedef _D3DPICKRECORD TD3DPickRecord;

typedef _D3DTEXTUREFILTER *PD3DTextureFilter;

typedef _D3DTEXTUREFILTER TD3DTextureFilter;

typedef _D3DTEXTUREBLEND *PD3DTextureBlend;

typedef _D3DTEXTUREBLEND TD3DTextureBlend;

typedef _D3DANTIALIASMODE *PD3DAntialiasMode;

typedef _D3DANTIALIASMODE TD3DAntialiasMode;

typedef _D3DVERTEXTYPE *PD3DVertexType;

typedef _D3DVERTEXTYPE TD3DVertexType;

typedef _D3DTRANSFORMSTATETYPE TD3DTRANSFORMSTATETYPE;

typedef _D3DTRANSFORMSTATETYPE *PD3DTransformStateType;

typedef _D3DLIGHTSTATETYPE *PD3DLightStateType;

typedef _D3DLIGHTSTATETYPE TD3DLightStateType;

typedef unsigned *PD3DRenderStateType;

typedef unsigned TD3DRenderStateType;

typedef _D3DSTATE *PD3DState;

typedef _D3DSTATE TD3DState;

typedef _D3DMATRIXLOAD *PD3DMatrixLoad;

typedef _D3DMATRIXLOAD TD3DMatrixLoad;

typedef _D3DMATRIXMULTIPLY *PD3DMatrixMultiply;

typedef _D3DMATRIXMULTIPLY TD3DMatrixMultiply;

typedef _D3DPROCESSVERTICES *PD3DProcessVertices;

typedef _D3DPROCESSVERTICES TD3DProcessVertices;

typedef _D3DTEXTUREMAGFILTER *PD3DTextureMagFilter;

typedef _D3DTEXTUREMAGFILTER TD3DTextureMagFilter;

typedef _D3DTEXTUREMINFILTER *PD3DTextureMinFilter;

typedef _D3DTEXTUREMINFILTER TD3DTextureMinFilter;

typedef _D3DTEXTUREMIPFILTER *PD3DTextureMipFilter;

typedef _D3DTEXTUREMIPFILTER TD3DTextureMipFilter;

typedef _D3DTRIANGLE *PD3DTriangle;

typedef _D3DTRIANGLE TD3DTriangle;

typedef _D3DLINE *PD3DLine;

typedef _D3DLINE TD3DLine;

typedef _D3DSPAN *PD3DSpan;

typedef _D3DSPAN TD3DSpan;

typedef _D3DPOINT *PD3DPoint;

typedef _D3DPOINT TD3DPoint;

typedef _D3DBRANCH *PD3DBranch;

typedef _D3DBRANCH TD3DBranch;

typedef _D3DSTATUS *PD3DStatus;

typedef _D3DSTATUS TD3DStatus;

typedef _D3DCLIPSTATUS *PD3DClipStatus;

typedef _D3DCLIPSTATUS TD3DClipStatus;

typedef _D3DSTATS *PD3DStats;

typedef _D3DSTATS TD3DStats;

typedef _D3DEXECUTEDATA *PD3DExecuteData;

typedef _D3DEXECUTEDATA TD3DExecuteData;

typedef _D3DVERTEXBUFFERDESC *PD3DVertexBufferDesc;

typedef _D3DVERTEXBUFFERDESC TD3DVertexBufferDesc;

typedef _D3DDP_PTRSTRIDE *PD3DDP_PtrStride;

typedef _D3DDP_PTRSTRIDE TD3DDP_PtrStride;

typedef _D3DDP_PTRSTRIDE TD3DDPPtrStride;

typedef _D3DDP_PTRSTRIDE *PD3DDPPtrStride;

typedef _D3DDRAWPRIMITIVESTRIDEDDATA *PD3DDrawPrimitiveStridedData;

typedef _D3DDRAWPRIMITIVESTRIDEDDATA TD3DDrawPrimitiveStridedData;

typedef _D3DTRANSFORMCAPS *PD3DTransformCaps;

typedef _D3DTRANSFORMCAPS TD3DTransformCaps;

typedef _D3DLIGHTINGCAPS *PD3DLightingCaps;

typedef _D3DLIGHTINGCAPS TD3DLightingCaps;

typedef _D3DPrimCaps *PD3DPrimCaps;

typedef _D3DPrimCaps TD3DPrimCaps;

typedef _D3DDeviceDesc *PD3DDeviceDesc;

typedef _D3DDeviceDesc TD3DDeviceDesc;

typedef _D3DDeviceDesc7 *PD3DDeviceDesc7;

typedef _D3DDeviceDesc7 TD3DDeviceDesc7;

typedef _D3DFINDDEVICESEARCH *PD3DFindDeviceSearch;

typedef _D3DFINDDEVICESEARCH TD3DFindDeviceSearch;

typedef _D3DFINDDEVICERESULT *PD3DFindDeviceResult;

typedef _D3DFINDDEVICERESULT TD3DFindDeviceResult;

typedef _D3DExecuteBufferDesc *PD3DExecuteBufferDesc;

typedef _D3DExecuteBufferDesc TD3DExecuteBufferDesc;

enum DECLSPEC_DENUM TDXFileFormat : unsigned int { DXFILEFORMAT_BINARY, DXFILEFORMAT_TEXT, DXFILEFORMAT_COMPRESSED };

enum DECLSPEC_DENUM TDXFileLoadOptions : unsigned int { DXFILELOAD_FROMFILE, DXFILELOAD_FROMRESOURCE, DXFILELOAD_FROMMEMORY, DXFILELOAD_INVALID_3, DXFILELOAD_FROMSTREAM, DXFILELOAD_INVALID_5, DXFILELOAD_INVALID_6, DXFILELOAD_INVALID_7, DXFILELOAD_FROMURL };

typedef TDXFileLoadResource *PDXFileLoadResource;

struct DECLSPEC_DRECORD TDXFileLoadResource
{
public:
	NativeUInt hModule;
	char *lpName;
	char *lpType;
};


typedef TDXFileLoadMemory *PDXFileLoadMemory;

struct DECLSPEC_DRECORD TDXFileLoadMemory
{
public:
	void *lpMemory;
	unsigned dSize;
};


__interface  INTERFACE_UUID("{3D82AB40-62DA-11CF-AB39-0020AF71E433}") IDirectXFile  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateEnumObject(void * pvSource, TDXFileLoadOptions dwLoadOptions, _di_IDirectXFileEnumObject &ppEnumObj) = 0 ;
	virtual HRESULT __stdcall CreateSaveObject(char * szFileName, TDXFileFormat dwFileFormat, _di_IDirectXFileSaveObject &ppSaveObj) = 0 ;
	virtual HRESULT __stdcall RegisterTemplates(void * pvData, unsigned cbSize) = 0 ;
};

__interface  INTERFACE_UUID("{3D82AB41-62DA-11CF-AB39-0020AF71E433}") IDirectXFileEnumObject  : public System::IInterface 
{
	virtual HRESULT __stdcall GetNextDataObject(_di_IDirectXFileData &ppDataObj) = 0 ;
	virtual HRESULT __stdcall GetDataObjectById(const GUID &rguid, _di_IDirectXFileData &ppDataObj) = 0 ;
	virtual HRESULT __stdcall GetDataObjectByName(char * szName, _di_IDirectXFileData &ppDataObj) = 0 ;
};

__interface  INTERFACE_UUID("{3D82AB42-62DA-11CF-AB39-0020AF71E433}") IDirectXFileSaveObject  : public System::IInterface 
{
	virtual HRESULT __stdcall SaveTemplates(unsigned cTemplates, System::PGUID &ppguidTemplates) = 0 ;
	virtual HRESULT __stdcall CreateDataObject(const GUID &rguidTemplate, char * szName, System::PGUID pguid, unsigned cbSize, void * pvData, _di_IDirectXFileData &ppDataObj) = 0 ;
	virtual HRESULT __stdcall SaveData(_di_IDirectXFileData pDataObj) = 0 ;
};

__interface  INTERFACE_UUID("{3D82AB43-62DA-11CF-AB39-0020AF71E433}") IDirectXFileObject  : public System::IInterface 
{
	virtual HRESULT __stdcall GetName(char * pstrNameBuf, unsigned &dwBufLen) = 0 ;
	virtual HRESULT __stdcall GetId(GUID &pGuidBuf) = 0 ;
};

__interface  INTERFACE_UUID("{3D82AB44-62DA-11CF-AB39-0020AF71E433}") IDirectXFileData  : public IDirectXFileObject 
{
	virtual HRESULT __stdcall GetData(char * szMember, unsigned &pcbSize, void * &ppvData) = 0 ;
	virtual HRESULT __stdcall GetType(System::PGUID &ppguid) = 0 ;
	virtual HRESULT __stdcall GetNextObject(_di_IDirectXFileObject &ppChildObj) = 0 ;
	virtual HRESULT __stdcall AddDataObject(_di_IDirectXFileData pDataObj) = 0 ;
	virtual HRESULT __stdcall AddDataReference(char * szRef, System::PGUID pguidRef) = 0 ;
	virtual HRESULT __stdcall AddBinaryObject(char * szName, System::PGUID pguid, char * szMimeType, void * pvData, unsigned cbSize) = 0 ;
};

__interface  INTERFACE_UUID("{3D82AB45-62DA-11CF-AB39-0020AF71E433}") IDirectXFileDataReference  : public IDirectXFileObject 
{
	virtual HRESULT __stdcall Resolve(_di_IDirectXFileData &ppDataObj) = 0 ;
};

__interface  INTERFACE_UUID("{3D82AB46-62DA-11CF-AB39-0020AF71E433}") IDirectXFileBinary  : public IDirectXFileObject 
{
	virtual HRESULT __stdcall GetSize(unsigned &pcbSize) = 0 ;
	virtual HRESULT __stdcall GetMimeType(char * &pszMimeType) = 0 ;
	virtual HRESULT __stdcall Read(void * pvData, unsigned cbSize, unsigned* pcbRead) = 0 ;
};

typedef _di_IDirectXFile IID_IDirectXFile;

typedef _di_IDirectXFileEnumObject IID_IDirectXFileEnumObject;

typedef _di_IDirectXFileSaveObject IID_IDirectXFileSaveObject;

typedef _di_IDirectXFileObject IID_IDirectXFileObject;

typedef _di_IDirectXFileData IID_IDirectXFileData;

typedef _di_IDirectXFileDataReference IID_IDirectXFileDataReference;

typedef _di_IDirectXFileBinary IID_IDirectXFileBinary;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE NativeUInt DXFileDLL;
extern DELPHI_PACKAGE GUID CLSID_CDirectXFile;
extern DELPHI_PACKAGE GUID TID_DXFILEHeader;
static const System::Int8 DXFILE_OK = System::Int8(0x0);
static const int DXFILEERR_BADOBJECT = int(-2005531822);
static const int DXFILEERR_BADVALUE = int(-2005531821);
static const int DXFILEERR_BADTYPE = int(-2005531820);
static const int DXFILEERR_BADSTREAMHANDLE = int(-2005531819);
static const int DXFILEERR_BADALLOC = int(-2005531818);
static const int DXFILEERR_NOTFOUND = int(-2005531817);
static const int DXFILEERR_NOTDONEYET = int(-2005531816);
static const int DXFILEERR_FILENOTFOUND = int(-2005531815);
static const int DXFILEERR_RESOURCENOTFOUND = int(-2005531814);
static const int DXFILEERR_URLNOTFOUND = int(-2005531813);
static const int DXFILEERR_BADRESOURCE = int(-2005531812);
static const int DXFILEERR_BADFILETYPE = int(-2005531811);
static const int DXFILEERR_BADFILEVERSION = int(-2005531810);
static const int DXFILEERR_BADFILEFLOATSIZE = int(-2005531809);
static const int DXFILEERR_BADFILECOMPRESSIONTYPE = int(-2005531808);
static const int DXFILEERR_BADFILE = int(-2005531807);
static const int DXFILEERR_PARSEERROR = int(-2005531806);
static const int DXFILEERR_NOTEMPLATE = int(-2005531805);
static const int DXFILEERR_BADARRAYSIZE = int(-2005531804);
static const int DXFILEERR_BADDATAREFERENCE = int(-2005531803);
static const int DXFILEERR_INTERNALERROR = int(-2005531802);
static const int DXFILEERR_NOMOREOBJECTS = int(-2005531801);
static const int DXFILEERR_BADINTRINSICS = int(-2005531800);
static const int DXFILEERR_NOMORESTREAMHANDLES = int(-2005531799);
static const int DXFILEERR_NOMOREDATA = int(-2005531798);
static const int DXFILEERR_BADCACHEFILE = int(-2005531797);
static const int DXFILEERR_NOINTERNET = int(-2005531796);
extern DELPHI_PACKAGE HRESULT __stdcall (*DirectXFileCreate)(/* out */ _di_IDirectXFile &lplpDirectXFile);
extern DELPHI_PACKAGE System::StaticArray<System::Byte, 3215> D3DRM_XTEMPLATES;
extern DELPHI_PACKAGE _D3DVECTOR __fastcall VectorAdd(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall VectorSub(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall VectorMulS(const _D3DVECTOR &v, float s);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall VectorDivS(const _D3DVECTOR &v, float s);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall VectorMul(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall VectorDiv(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE bool __fastcall VectorSmaller(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE bool __fastcall VectorSmallerEqual(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE bool __fastcall VectorEqual(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE float __fastcall VectorSquareMagnitude(const _D3DVECTOR &v);
extern DELPHI_PACKAGE float __fastcall VectorMagnitude(const _D3DVECTOR &v);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall VectorNormalize(const _D3DVECTOR &v);
extern DELPHI_PACKAGE float __fastcall VectorMin(const _D3DVECTOR &v);
extern DELPHI_PACKAGE float __fastcall VectorMax(const _D3DVECTOR &v);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall VectorMinimize(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall VectorMaximize(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE float __fastcall VectorDotProduct(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall VectorCrossProduct(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE void __fastcall DisableFPUExceptions(void);
extern DELPHI_PACKAGE void __fastcall EnableFPUExceptions(void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall DXFileErrorString(HRESULT Value);
}	/* namespace Direct3d */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DIRECT3D)
using namespace Winapi::Direct3d;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Direct3dHPP
