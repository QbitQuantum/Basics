/** transform vector by rigid transform */
inline Matrix<float, 4, 1> operator * (const RigidTransform<float>& mat, const Matrix<float, 4, 1>& vec)
{
#ifdef SIMPLE_GL_USE_SSE4
    __m128 res;
    __m128 dotProd;

    res      = _mm_dp_ps(mat[0].m128, vec.m128, 0xEE);\
    dotProd  = _mm_dp_ps(mat[1].m128, vec.m128, 0xEE);\
    res      = _mm_blend_ps( res, dotProd, _MM_SHUFFLE(0, 1, 1, 1) );\
    dotProd  = _mm_dp_ps(mat[2].m128, vec.m128, 0xEE);\
    res      = _mm_blend_ps( res, dotProd, _MM_SHUFFLE(0, 0, 1, 1) );\
    dotProd  = _mm_dp_ps(mat[3].m128, vec.m128, 0xEE);\
    res      = _mm_blend_ps( res, dotProd, _MM_SHUFFLE(0, 0, 0, 1) );

    return Matrix<float, 4, 1>(res);
#elif defined(SIMPLE_GL_USE_SSE3)
    __m128 res;

    __m128 dotProd0 = _mm_mul_ps(mat[0].m128, vec.m128);
    dotProd0        = _mm_hadd_ps(dotProd0, dotProd0);
    dotProd0        = _mm_hadd_ps(dotProd0, dotProd0);

    __m128 dotProd1 = _mm_mul_ps(mat[1].m128, vec.m128);
    dotProd1        = _mm_hadd_ps(dotProd1, dotProd1);
    dotProd1        = _mm_hadd_ps(dotProd1, dotProd1);

    __m128 dotProd2 = _mm_mul_ps(mat[2].m128, vec.m128);
    dotProd2        = _mm_hadd_ps(dotProd2, dotProd2);
    dotProd2        = _mm_hadd_ps(dotProd2, dotProd2);

    __m128 dotProd3 = _mm_mul_ps(mat[3].m128, vec.m128);
    dotProd3        = _mm_hadd_ps(dotProd3, dotProd3);
    dotProd3        = _mm_hadd_ps(dotProd3, dotProd3);

    __m128 vec01    = _mm_unpacklo_ps(dotProd0, dotProd1);
    __m128 vec23    = _mm_unpackhi_ps(dotProd2, dotProd3);
    res             = _mm_movelh_ps(vec01, vec23);

    return Matrix<float, 4, 1>(res);
#else // SSE2
    // TODO: Think about good sse optimization
    Matrix<float, 4, 1> res;
    res[0] = mat[0][0] * res[0] + mat[0][1] * res[1] + mat[0][2] * res[2] + mat[0][3] * res[3];
    res[1] = mat[1][0] * res[0] + mat[1][1] * res[1] + mat[1][2] * res[2] + mat[1][3] * res[3];
    res[2] = mat[2][0] * res[0] + mat[2][1] * res[1] + mat[2][2] * res[2] + mat[2][3] * res[3];
    res[3] = mat[3][0] * res[0] + mat[3][1] * res[1] + mat[3][2] * res[2] + mat[3][3] * res[3];
    return res;
#endif
}