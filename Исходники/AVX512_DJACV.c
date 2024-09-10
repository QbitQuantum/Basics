#include <stdlib.h>
#include <string.h>

#include "AVX512_DJACV.h"

#define VSIZE_B 64u
#define DBLE_SZ 8u
#define NDBLE_V (VSIZE_B / DBLE_SZ)
#define NPAIR_V NDBLE_V

static inline __m256d avx512_ddots(const unsigned m, const double *const restrict Gp, const double *const restrict Gq)
{
  register const double *const Gp_i = (const double*)__builtin_assume_aligned(Gp, VSIZE_B);
  register const double *const Gq_i = (const double*)__builtin_assume_aligned(Gq, VSIZE_B);

  register __m512d Gpp = _mm512_setzero_pd();
  register __m512d Gqq = _mm512_setzero_pd();
  register __m512d Gpq = _mm512_setzero_pd();

  for (register unsigned i = 0u; i < m; i += NDBLE_V) {
    register const __m512d Gpi = _mm512_load_pd(Gp_i + i);
    register const __m512d Gqi = _mm512_load_pd(Gq_i + i);

    Gpp = _mm512_fmadd_pd(Gpi, Gpi, Gpp);
    Gqq = _mm512_fmadd_pd(Gqi, Gqi, Gqq);
    Gpq = _mm512_fmadd_pd(Gpi, Gqi, Gpq);
  }

  register const double pq = _mm512_reduce_add_pd(Gpq);
  /* out[0] = Gpp; out[1] = Gqq; out[2] = Gpq; out[3] = |Gpq|; */
  return _mm256_set_pd(fabs(pq), pq, _mm512_reduce_add_pd(Gqq), _mm512_reduce_add_pd(Gpp));