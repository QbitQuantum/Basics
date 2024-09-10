/*!
  Compute the image addition: \f$ Ires = I1 - I2 \f$.

  \param I1 : The first image.
  \param I2 : The second image.
  \param Ires : \f$ Ires = I1 - I2 \f$
  \param saturate : If true, saturate the result to [0 ; 255] using vpMath::saturate, otherwise overflow may occur.
*/
void
vpImageTools::imageSubtract(const vpImage<unsigned char> &I1,
                            const vpImage<unsigned char> &I2,
                            vpImage<unsigned char> &Ires,
                            const bool saturate)
{
  if ((I1.getHeight() != I2.getHeight()) || (I1.getWidth() != I2.getWidth())) {
    throw (vpException(vpException::dimensionError, "The two images do not have the same size"));
  }

  if ((I1.getHeight() != Ires.getHeight()) || (I1.getWidth() != Ires.getWidth())) {
    Ires.resize(I1.getHeight(), I1.getWidth());
  }

  unsigned char *ptr_I1   = I1.bitmap;
  unsigned char *ptr_I2   = I2.bitmap;
  unsigned char *ptr_Ires = Ires.bitmap;
  unsigned int cpt = 0;

#if VISP_HAVE_SSE2
  if (Ires.getSize() >= 16) {
    for (; cpt <= Ires.getSize() - 16 ; cpt += 16, ptr_I1 += 16, ptr_I2 += 16, ptr_Ires += 16) {
      const __m128i v1   = _mm_loadu_si128( (const __m128i*) ptr_I1);
      const __m128i v2   = _mm_loadu_si128( (const __m128i*) ptr_I2);
      const __m128i vres = saturate ? _mm_subs_epu8(v1, v2) : _mm_sub_epi8(v1, v2);

      _mm_storeu_si128( (__m128i*) ptr_Ires, vres );
    }
  }
#endif

  for (; cpt < Ires.getSize(); cpt++, ++ptr_I1, ++ptr_I2, ++ptr_Ires) {
    *ptr_Ires = saturate ? vpMath::saturate<unsigned char>( (short int) *ptr_I1 - (short int) *ptr_I2 ) : *ptr_I1 - *ptr_I2;
  }
}