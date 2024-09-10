float rsqrt(const float f)
{
    float buf[4];
    buf[0]=f;
    __m128 v=_mm_loadu_ps(buf);
    v=_mm_rsqrt_ss(v);
    _mm_storeu_ps(buf,v);
    return buf[0];
}