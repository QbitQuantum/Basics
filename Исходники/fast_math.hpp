/** @brief Rounds floating-point number to the nearest integer not smaller than the original.

 The function computes an integer i such that:
 \f[i \le \texttt{value} < i+1\f]
 @param value floating-point number. If the value is outside of INT_MIN ... INT_MAX range, the
 result is not defined.
 */
CV_INLINE int cvCeil( double value )
{
#if (defined _MSC_VER && defined _M_X64 || (defined __GNUC__ && defined __SSE2__&& !defined __APPLE__)) && !defined(__CUDACC__)
    __m128d t = _mm_set_sd( value );
    int i = _mm_cvtsd_si32(t);
    return i + _mm_movemask_pd(_mm_cmplt_sd(_mm_cvtsi32_sd(t,i), t));
#elif defined __GNUC__
    int i = (int)value;
    return i + (i < value);
#else
    int i = cvRound(value);
    float diff = (float)(i - value);
    return i + (diff < 0);
#endif
}