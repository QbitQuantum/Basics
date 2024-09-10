// Store the pixel's values into a given pixel list's position
inline void StorePixel(float * rgbaBuffer, const __m128 pix, const float outAlpha)
{
    _mm_storeu_ps(rgbaBuffer, pix);
    rgbaBuffer[3] = outAlpha;
}