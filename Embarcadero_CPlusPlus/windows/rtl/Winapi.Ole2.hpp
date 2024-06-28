// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Ole2.pas' rev: 34.00 (Windows)

#ifndef Winapi_Ole2HPP
#define Winapi_Ole2HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#include <ole2.h>

namespace Winapi
{
namespace Ole2
{
//-- forward type declarations -----------------------------------------------
struct TGUID;
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<HRESULT, 65536> TResultList;

typedef TResultList *PResultList;

typedef System::WideChar TOleChar;

typedef System::WideChar * POleStr;

typedef System::StaticArray<System::WideChar *, 65536> TOleStrList;

typedef TOleStrList *POleStrList;

typedef System::Comp Largeint;

typedef TGUID *PGUID;

struct DECLSPEC_DRECORD TGUID
{
public:
	unsigned D1;
	System::Word D2;
	System::Word D3;
	System::StaticArray<System::Byte, 8> D4;
};


typedef PGUID PIID;

typedef TGUID TIID;

typedef PGUID PCLSID;

typedef TGUID TCLSID;

typedef _OBJECTID *PObjectID;

typedef _OBJECTID TObjectID;

typedef unsigned TLCID;

typedef tagBIND_OPTS *PBindOpts;

typedef tagBIND_OPTS TBindOpts;

typedef tagSTATSTG *PStatStg;

typedef tagSTATSTG TStatStg;

typedef System::WideChar * *TSNB;

typedef tagDVTARGETDEVICE *PDVTargetDevice;

typedef tagDVTARGETDEVICE TDVTargetDevice;

typedef System::Word *PClipFormat;

typedef System::Word TClipFormat;

typedef tagFORMATETC *PFormatEtc;

typedef tagFORMATETC TFormatEtc;

typedef tagSTATDATA *PStatData;

typedef tagSTATDATA TStatData;

typedef tagRemSTGMEDIUM *PRemStgMedium;

typedef tagRemSTGMEDIUM TRemStgMedium;

typedef tagSTGMEDIUM *PStgMedium;

typedef tagSTGMEDIUM TStgMedium;

typedef tagINTERFACEINFO *PInterfaceInfo;

typedef tagINTERFACEINFO TInterfaceInfo;

typedef int TRpcOleDataRep;

typedef tagRPCOLEMESSAGE *PRpcOleMessage;

typedef tagRPCOLEMESSAGE TRpcOleMessage;

typedef System::WideChar * *PBStr;

typedef System::WideChar * TBStr;

typedef System::StaticArray<System::WideChar *, 65536> TBStrList;

typedef TBStrList *PBStrList;

typedef tagCLIPDATA *PClipData;

typedef tagCLIPDATA TClipData;

typedef tagSAFEARRAYBOUND *PSafeArrayBound;

typedef tagSAFEARRAYBOUND TSafeArrayBound;

typedef tagSAFEARRAY *PSafeArray;

typedef tagSAFEARRAY TSafeArray;

typedef double TOleDate;

typedef System::Comp TCurrency;

typedef System::WordBool TOleBool;

typedef System::Word TVarType;

typedef tagVARIANT *PVariantArg;

typedef tagVARIANT TVariantArg;

typedef System::StaticArray<tagVARIANT, 65536> TVariantArgList;

typedef TVariantArgList *PVariantArgList;

typedef int TDispID;

typedef System::StaticArray<int, 65536> TDispIDList;

typedef TDispIDList *PDispIDList;

typedef int TMemberID;

typedef System::StaticArray<int, 65536> TMemberIDList;

typedef TMemberIDList *PMemberIDList;

typedef int TPropID;

typedef int HRefType;

typedef int TTypeKind;

typedef tagARRAYDESC *PArrayDesc;

typedef tagTYPEDESC *PTypeDesc;

typedef tagTYPEDESC TTypeDesc;

typedef tagARRAYDESC TArrayDesc;

typedef tagIDLDESC *PIDLDesc;

typedef tagIDLDESC TIDLDesc;

typedef tagELEMDESC *PElemDesc;

typedef tagELEMDESC TElemDesc;

typedef System::StaticArray<tagELEMDESC, 65536> TElemDescList;

typedef TElemDescList *PElemDescList;

typedef tagTYPEATTR *PTypeAttr;

typedef tagTYPEATTR TTypeAttr;

typedef tagDISPPARAMS *PDispParams;

typedef tagDISPPARAMS TDispParams;

typedef tagEXCEPINFO *PExcepInfo;

typedef HRESULT __stdcall (*TFNDeferredFillIn)(PExcepInfo ExInfo);

typedef tagEXCEPINFO TExcepInfo;

typedef int TFuncKind;

typedef int TInvokeKind;

typedef int TCallConv;

typedef tagFUNCDESC *PFuncDesc;

typedef tagFUNCDESC TFuncDesc;

typedef int TVarKind;

typedef tagVARDESC *PVarDesc;

typedef tagVARDESC TVarDesc;

typedef int TDescKind;

typedef tagBINDPTR *PBindPtr;

typedef tagBINDPTR TBindPtr;

typedef int TSysKind;

typedef tagTLIBATTR *PTLibAttr;

typedef tagTLIBATTR TTLibAttr;

typedef System::StaticArray<ITypeInfo*, 65536> TTypeInfoList;

typedef TTypeInfoList *PTypeInfoList;

typedef tagPARAMDATA *PParamData;

typedef tagPARAMDATA TParamData;

typedef System::StaticArray<tagPARAMDATA, 65536> TParamDataList;

typedef TParamDataList *PParamDataList;

typedef tagMETHODDATA *PMethodData;

typedef tagMETHODDATA TMethodData;

typedef System::StaticArray<tagMETHODDATA, 65536> TMethodDataList;

typedef TMethodDataList *PMethodDataList;

typedef tagINTERFACEDATA *PInterfaceData;

typedef tagINTERFACEDATA TInterfaceData;

typedef tagOBJECTDESCRIPTOR *PObjectDescriptor;

typedef tagOBJECTDESCRIPTOR TObjectDescriptor;

typedef PObjectDescriptor PLinkSrcDescriptor;

typedef tagOBJECTDESCRIPTOR TLinkSrcDescriptor;

typedef tagOIFI *POleInPlaceFrameInfo;

typedef tagOIFI TOleInPlaceFrameInfo;

typedef tagOleMenuGroupWidths *POleMenuGroupWidths;

typedef tagOleMenuGroupWidths TOleMenuGroupWidths;

typedef System::LongBool __stdcall (*TContinueFunc)(int dwContinue);

typedef tagOLEVERB *POleVerb;

typedef tagOLEVERB TOleVerb;

typedef HRESULT __stdcall (*TDLLGetClassObject)(const TGUID &clsid, const TGUID &iid, void *pv);

typedef HRESULT __stdcall (*TDLLCanUnloadNow)();

//-- var, const, procedure ---------------------------------------------------
static const int CLSCTX_FROM_DEFAULT_CONTEXT = int(0x20000);
extern DELPHI_PACKAGE bool __fastcall Succeeded(HRESULT Res);
extern DELPHI_PACKAGE bool __fastcall Failed(HRESULT Res);
extern DELPHI_PACKAGE int __fastcall ResultCode(HRESULT Res);
extern DELPHI_PACKAGE int __fastcall ResultFacility(HRESULT Res);
extern DELPHI_PACKAGE int __fastcall ResultSeverity(HRESULT Res);
}	/* namespace Ole2 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_OLE2)
using namespace Winapi::Ole2;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Ole2HPP
