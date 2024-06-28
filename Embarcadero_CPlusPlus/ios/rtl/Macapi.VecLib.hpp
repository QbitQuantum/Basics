// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.vecLib.pas' rev: 34.00 (iOS)

#ifndef Macapi_VeclibHPP
#define Macapi_VeclibHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Macapi
{
namespace Veclib
{
//-- forward type declarations -----------------------------------------------
struct _DSPComplex;
struct _DSPSplitComplex;
struct _DSPDoubleComplex;
struct _DSPDoubleSplitComplex;
struct DECLSPEC_DRECORD _OpaqueFFTSetup
{
};


struct DECLSPEC_DRECORD _OpaqueFFTSetupD
{
};


//-- type declarations -------------------------------------------------------
typedef unsigned vDSP_Length;

typedef int vDSP_Stride;

struct DECLSPEC_DRECORD _DSPComplex
{
public:
	float real;
	float imag;
};


typedef _DSPComplex TDSPComplex;

typedef _DSPComplex *PDSPComplex;

struct DECLSPEC_DRECORD _DSPSplitComplex
{
public:
	float *realp;
	float *imagp;
};


typedef _DSPSplitComplex TDSPSplitComplex;

typedef _DSPSplitComplex *PDSPSplitComplex;

struct DECLSPEC_DRECORD _DSPDoubleComplex
{
public:
	double real;
	double imag;
};


typedef _DSPDoubleComplex TDSPDoubleComplex;

typedef _DSPDoubleComplex *PDSPDoubleComplex;

struct DECLSPEC_DRECORD _DSPDoubleSplitComplex
{
public:
	double *realp;
	double *imagp;
};


typedef _DSPDoubleSplitComplex TDSPDoubleSplitComplex;

typedef _DSPDoubleSplitComplex *PDSPDoubleSplitComplex;

typedef _OpaqueFFTSetup TFFTSetup;

typedef _OpaqueFFTSetup *PFFTSetup;

typedef _OpaqueFFTSetupD TFFTSetupD;

typedef _OpaqueFFTSetupD *PFFTSetupD;

enum DECLSPEC_DENUM FFTDirection: char { kFFTDirection_Inverse = -1, kFFTDirection_Forward = 1 };

enum DECLSPEC_DENUM FFTRadix : unsigned char { kFFTRadix2, kFFTRadix3, kFFTRadix5 };

enum DECLSPEC_DENUM vDSP_NEED_NAME_ENUM : unsigned char { vDSP_HANN_DENORM, vDSP_HALF_WINDOW, vDSP_HANN_NORM };

//-- var, const, procedure ---------------------------------------------------
#define libVeclib u"/System/Library/Frameworks/Accelerate.framework/Accelerate"
static constexpr System::Word vDSP_Version0 = System::Word(0x145);
static constexpr System::Int8 vDSP_Version1 = System::Int8(0x4);
extern "C" PFFTSetup __cdecl vDSP_create_fftsetup(unsigned __vDSP_log2n, FFTRadix __vDSP_radix);
extern "C" void __cdecl vDSP_destroy_fftsetup(PFFTSetup __vDSP_setup);
extern "C" PFFTSetupD __cdecl vDSP_create_fftsetupD(unsigned __vDSP_log2n, FFTRadix __vDSP_radix);
extern "C" void __cdecl vDSP_destroy_fftsetupD(PFFTSetupD __vDSP_setup);
extern "C" void __cdecl vDSP_ctoz(const PDSPComplex __vDSP_C, int __vDSP_strideC, PDSPSplitComplex __vDSP_Z, int __vDSP_strideZ, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_ztoc(const PDSPSplitComplex __vDSP_Z, int __vDSP_strideZ, PDSPComplex __vDSP_C, int __vDSP_strideC, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_ctozD(const PDSPDoubleComplex __vDSP_C, int __vDSP_strideC, PDSPDoubleSplitComplex __vDSP_Z, int __vDSP_strideZ, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_ztocD(const PDSPDoubleSplitComplex __vDSP_Z, int __vDSP_strideZ, PDSPDoubleComplex __vDSP_C, int __vDSP_strideC, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_mtrans(System::PSingle __vDSP_a, int __vDSP_aStride, System::PSingle __vDSP_c, int __vDSP_cStride, unsigned __vDSP_M, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_mtransD(System::PDouble __vDSP_a, int __vDSP_aStride, System::PDouble __vDSP_c, int __vDSP_cStride, unsigned __vDSP_M, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_mmul(System::PSingle __vDSP_a, int __vDSP_aStride, System::PSingle __vDSP_b, int __vDSP_bStride, System::PSingle __vDSP_c, int __vDSP_cStride, unsigned __vDSP_M, unsigned __vDSP_N, unsigned __vDSP_P);
extern "C" void __cdecl vDSP_mmulD(System::PDouble __vDSP_a, int __vDSP_aStride, System::PDouble __vDSP_b, int __vDSP_bStride, System::PDouble __vDSP_c, int __vDSP_cStride, unsigned __vDSP_M, unsigned __vDSP_N, unsigned __vDSP_P);
extern "C" void __cdecl vDSP_zmma(PDSPSplitComplex __vDSP_a, int __vDSP_i, PDSPSplitComplex __vDSP_b, int __vDSP_j, PDSPSplitComplex __vDSP_c, int __vDSP_k, PDSPSplitComplex __vDSP_d, int __vDSP_l, unsigned __vDSP_M, unsigned __vDSP_N, unsigned __vDSP_P);
extern "C" void __cdecl vDSP_zmmaD(PDSPDoubleSplitComplex __vDSP_a, int __vDSP_i, PDSPDoubleSplitComplex __vDSP_b, int __vDSP_j, PDSPDoubleSplitComplex __vDSP_c, int __vDSP_k, PDSPDoubleSplitComplex __vDSP_d, int __vDSP_l, unsigned __vDSP_M, unsigned __vDSP_N, unsigned __vDSP_P);
extern "C" void __cdecl vDSP_zmms(PDSPSplitComplex __vDSP_a, int __vDSP_i, PDSPSplitComplex __vDSP_b, int __vDSP_j, PDSPSplitComplex __vDSP_c, int __vDSP_k, PDSPSplitComplex __vDSP_d, int __vDSP_l, unsigned __vDSP_M, unsigned __vDSP_N, unsigned __vDSP_P);
extern "C" void __cdecl vDSP_zmmsD(PDSPDoubleSplitComplex __vDSP_a, int __vDSP_i, PDSPDoubleSplitComplex __vDSP_b, int __vDSP_j, PDSPDoubleSplitComplex __vDSP_c, int __vDSP_k, PDSPDoubleSplitComplex __vDSP_d, int __vDSP_l, unsigned __vDSP_M, unsigned __vDSP_N, unsigned __vDSP_P);
extern "C" void __cdecl vDSP_zmsm(PDSPSplitComplex __vDSP_a, int __vDSP_i, PDSPSplitComplex __vDSP_b, int __vDSP_j, PDSPSplitComplex __vDSP_c, int __vDSP_k, PDSPSplitComplex __vDSP_d, int __vDSP_l, unsigned __vDSP_M, unsigned __vDSP_N, unsigned __vDSP_P);
extern "C" void __cdecl vDSP_zmsmD(PDSPDoubleSplitComplex __vDSP_a, int __vDSP_i, PDSPDoubleSplitComplex __vDSP_b, int __vDSP_j, PDSPDoubleSplitComplex __vDSP_c, int __vDSP_k, PDSPDoubleSplitComplex __vDSP_d, int __vDSP_l, unsigned __vDSP_M, unsigned __vDSP_N, unsigned __vDSP_P);
extern "C" void __cdecl vDSP_zmmul(PDSPSplitComplex __vDSP_a, int __vDSP_i, PDSPSplitComplex __vDSP_b, int __vDSP_j, PDSPSplitComplex __vDSP_c, int __vDSP_k, unsigned __vDSP_M, unsigned __vDSP_N, unsigned __vDSP_P);
extern "C" void __cdecl vDSP_zmmulD(PDSPDoubleSplitComplex __vDSP_a, int __vDSP_i, PDSPDoubleSplitComplex __vDSP_b, int __vDSP_j, PDSPDoubleSplitComplex __vDSP_c, int __vDSP_k, unsigned __vDSP_M, unsigned __vDSP_N, unsigned __vDSP_P);
extern "C" void __cdecl vDSP_vadd(System::PSingle __vDSP_input1, int __vDSP_stride1, System::PSingle __vDSP_input2, int __vDSP_stride2, System::PSingle __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vaddD(System::PDouble __vDSP_input1, int __vDSP_stride1, System::PDouble __vDSP_input2, int __vDSP_stride2, System::PDouble __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vsub(System::PSingle __vDSP_input1, int __vDSP_stride1, System::PSingle __vDSP_input2, int __vDSP_stride2, System::PSingle __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vsubD(System::PDouble __vDSP_input1, int __vDSP_stride1, System::PDouble __vDSP_input2, int __vDSP_stride2, System::PDouble __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vmul(System::PSingle __vDSP_input1, int __vDSP_stride1, System::PSingle __vDSP_input2, int __vDSP_stride2, System::PSingle __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vmulD(System::PDouble __vDSP_input1, int __vDSP_stride1, System::PDouble __vDSP_input2, int __vDSP_stride2, System::PDouble __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vsmul(System::PSingle __vDSP_input1, int __vDSP_stride1, System::PSingle __vDSP_input2, System::PSingle __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vsmulD(System::PDouble __vDSP_input1, int __vDSP_stride1, System::PDouble __vDSP_input2, System::PDouble __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vsq(System::PSingle __vDSP_input, int __vDSP_strideInput, System::PSingle __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vsqD(System::PDouble __vDSP_input, int __vDSP_strideInput, System::PDouble __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vssq(System::PSingle __vDSP_input, int __vDSP_strideInput, System::PSingle __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vssqD(System::PDouble __vDSP_input, int __vDSP_strideInput, System::PDouble __vDSP_result, int __vDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_dotpr(System::PSingle __vDSP_input1, int __vDSP_stride1, System::PSingle __vDSP_input2, int __vDSP_stride2, System::PSingle __vDSP_result, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_dotprD(System::PDouble __vDSP_input1, int __vDSP_stride1, System::PDouble __vDSP_input2, int __vDSP_stride2, System::PDouble __vDSP_result, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vam(System::PSingle __vDSP_input1, int __vDSP_stride1, System::PSingle __vDSP_input2, int __vDSP_stride2, System::PSingle __vDSP_input3, int __vDSP_stride3, System::PSingle __vDSP_result, int __VDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vamD(System::PDouble __vDSP_input1, int __vDSP_stride1, System::PDouble __vDSP_input2, int __vDSP_stride2, System::PDouble __vDSP_input3, int __vDSP_stride3, System::PDouble __vDSP_result, int __VDSP_strideResult, unsigned __vDSP_size);
extern "C" void __cdecl vDSP_vdpsp(System::PDouble __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vspdp(System::PSingle __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vabsi(System::PInteger __vDSP_A, int __vDSP_I, System::PInteger __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_veqvi(System::PInteger __vDSP_A, int __vDSP_I, System::PInteger __vDSP_B, int __vDSP_J, System::PInteger __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vdivi(System::PInteger __vDSP_A, int __vDSP_I, System::PInteger __vDSP_B, int __vDSP_J, System::PInteger __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vfilli(System::PInteger __vDSP_A, System::PInteger __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vsaddi(System::PInteger __vDSP_A, int __vDSP_I, System::PInteger __vDSP_B, System::PInteger __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vsdivi(System::PInteger __vDSP_A, int __vDSP_I, System::PInteger __vDSP_B, System::PInteger __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_zaspec(PDSPSplitComplex __vDSP_A, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_zaspecD(PDSPDoubleSplitComplex __vDSP_A, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_blkman_window(System::PSingle __vDSP_C, unsigned __vDSP_N, int __vDSP_FLAG);
extern "C" void __cdecl vDSP_blkman_windowD(System::PDouble __vDSP_C, unsigned __vDSP_N, int __vDSP_FLAG);
extern "C" void __cdecl vDSP_zcoher(System::PSingle __vDSP_A, System::PSingle __vDSP_B, PDSPSplitComplex __vDSP_C, System::PSingle __vDSP_DC, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_zcoherD(System::PDouble __vDSP_A, System::PDouble __vDSP_B, PDSPDoubleSplitComplex __vDSP_C, System::PDouble __vDSP_DC, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_deq22(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_B, System::PSingle __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_deq22D(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_B, System::PDouble __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_desamp(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_B, System::PSingle __vDSP_C, unsigned __vDSP_N, unsigned __vDSP_M);
extern "C" void __cdecl vDSP_desampD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_B, System::PDouble __vDSP_C, unsigned __vDSP_N, unsigned __vDSP_M);
extern "C" void __cdecl vDSP_hamm_window(System::PSingle __vDSP_A, unsigned __vDSP_N, int __vDSP_FLAG);
extern "C" void __cdecl vDSP_hamm_windowD(System::PDouble __vDSP_A, unsigned __vDSP_N, int __vDSP_FLAG);
extern "C" void __cdecl vDSP_hann_window(System::PSingle __vDSP_A, unsigned __vDSP_N, int __vDSP_FLAG);
extern "C" void __cdecl vDSP_hann_windowD(System::PDouble __vDSP_A, unsigned __vDSP_N, int __vDSP_FLAG);
extern "C" void __cdecl vDSP_maxmgv(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_maxmgvD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_maxmgvi(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned &__vDSP_IC, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_maxmgviD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned &__vDSP_IC, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_maxv(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_maxvD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_maxvi(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned &__vDSP_IC, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_maxviD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned &__vDSP_IC, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_meamgv(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_meamgvD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_meanv(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_meanvD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_measqv(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_measqvD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_minmgv(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_minmgvD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_minmgvi(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned &__vDSP_IC, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_minmgviD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned &__vDSP_IC, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_minv(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_minvD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_minvi(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned &__vDSP_IC, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_minviD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned &__vDSP_IC, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_mmov(System::PSingle __vDSP_A, System::PSingle __vDSP_C, unsigned __vDSP_NC, unsigned __vDSP_NR, unsigned __vDSP_TCA, unsigned __vDSP_TCC);
extern "C" void __cdecl vDSP_mmovD(System::PDouble __vDSP_A, System::PDouble __vDSP_C, unsigned __vDSP_NC, unsigned __vDSP_NR, unsigned __vDSP_TCA, unsigned __vDSP_TCC);
extern "C" void __cdecl vDSP_mvessq(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_mvessqD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_nzcros(System::PSingle __vDSP_A, int __vDSP_I, unsigned __vDSP_B, unsigned &__vDSP_C, unsigned &__vDSP_D, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_nzcrosD(System::PDouble __vDSP_A, int __vDSP_I, unsigned __vDSP_B, unsigned &__vDSP_C, unsigned &__vDSP_D, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_polar(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_polarD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_rect(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_rectD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_rmsqv(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_rmsqvD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_svdiv(System::PSingle __vDSP_A, System::PSingle __vDSP_B, int __vDSP_J, System::PSingle __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_svdivD(System::PDouble __vDSP_A, System::PDouble __vDSP_B, int __vDSP_J, System::PDouble __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_sve(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_sveD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_svemg(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_svemgD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_svesq(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_svesqD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_svs(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_svsD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vaam(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_B, int __vDSP_J, System::PSingle __vDSP_C, int __vDSP_K, System::PSingle __vDSP_D, int __vDSP_L, System::PSingle __vDSP_E, int __vDSP_M, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vaamD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_B, int __vDSP_J, System::PDouble __vDSP_C, int __vDSP_K, System::PDouble __vDSP_D, int __vDSP_L, System::PDouble __vDSP_E, int __vDSP_M, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vabs(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vabsD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vasbm(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_B, int __vDSP_J, System::PSingle __vDSP_C, int __vDSP_K, System::PSingle __vDSP_D, int __vDSP_L, System::PSingle __vDSP_E, int __vDSP_M, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vasbmD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_B, int __vDSP_J, System::PDouble __vDSP_C, int __vDSP_K, System::PDouble __vDSP_D, int __vDSP_L, System::PDouble __vDSP_E, int __vDSP_M, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vasm(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_B, int __vDSP_J, System::PSingle __vDSP_C, System::PSingle __vDSP_D, int __vDSP_L, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vasmD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_B, int __vDSP_J, System::PDouble __vDSP_C, System::PDouble __vDSP_D, int __vDSP_L, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vavlin(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_B, System::PSingle __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vavlinD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_B, System::PDouble __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vclip(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_B, System::PSingle __vDSP_C, System::PSingle __vDSP_D, int __vDSP_L, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vclipD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_B, System::PDouble __vDSP_C, System::PDouble __vDSP_D, int __vDSP_L, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vclipc(System::PSingle __vDSP_A, int __vDSP_I, System::PSingle __vDSP_B, System::PSingle __vDSP_C, System::PSingle __vDSP_D, int __vDSP_L, unsigned __vDSP_N, unsigned &__vDSP_NLOW, unsigned &__vDSP_NHI);
extern "C" void __cdecl vDSP_vclipcD(System::PDouble __vDSP_A, int __vDSP_I, System::PDouble __vDSP_B, System::PDouble __vDSP_C, System::PDouble __vDSP_D, int __vDSP_L, unsigned __vDSP_N, unsigned &__vDSP_NLOW, unsigned &__vDSP_NHI);
extern "C" void __cdecl vDSP_vclr(System::PSingle __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
extern "C" void __cdecl vDSP_vclrD(System::PDouble __vDSP_C, int __vDSP_K, unsigned __vDSP_N);
}	/* namespace Veclib */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_VECLIB)
using namespace Macapi::Veclib;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_VeclibHPP
