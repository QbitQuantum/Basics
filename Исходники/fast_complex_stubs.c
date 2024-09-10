value complex_mul(value vab, value vcd)
{
    CAMLparam2(vab, vcd);
    CAMLlocal1(vz);
    vz = caml_alloc(Double_array_tag, 2);
    __m128d ab, cd, ac_bd, ba, bc_ad;
    ab = _mm_loadu_pd((double const*) vab);
    cd = _mm_loadu_pd((double const*) vcd);
    ac_bd = _mm_mul_pd(ab, cd);
    ba    = _mm_shuffle_pd(ab, ab, 1);
    bc_ad = _mm_mul_pd(ba, cd);
    _mm_storeu_pd((double*) vz, _mm_addsub_pd(ac_bd, bc_ad));
    CAMLreturn(vz);
}