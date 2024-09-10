/*-------------------------------------------------------------------------*/
/**
  @file		FieldDataCPU.cpp
*/
/*--------------------------------------------------------------------------*/
#include "FieldDataCPU.h"
#include "ShapeFunctions.h"
#include "vec_funcs.h"
#include "PlasmaData.h"
#include "ParallelInfo.h"
#include "mpi.h"
#include <immintrin.h>
#include <omp.h>

#if !(defined NO_HAND_VEC)
const __m256 float_1 = _mm256_set1_ps(1.0);

const __m256 float_15 = _mm256_set1_ps(1.5);

const __m256 float_075 = _mm256_set1_ps(0.75);

const __m256 float_05 = _mm256_set1_ps(0.5);

const __m256 sign_mask = (__m256)_mm256_set1_epi32(0x7fffffff);
#endif


__inline__
int zorder(int ix,int iy,int iz)
{
	// Spread the bits of each index