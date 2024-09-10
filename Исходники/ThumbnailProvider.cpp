void ThumbnailProvider::shrinkGrayscale4x4SSE(const Image& srcImage, Thumbnail::ThumbnailImageGrayscale& destImage)
{
  union
  {
    __m128i a;
    long long b[2];
  } splitter;

  const int scaleFactor = 4;
  const int width = srcImage.width;
  const int height = srcImage.height;

  ASSERT(width % scaleFactor == 0);
  ASSERT(height % scaleFactor == 0);

  destImage.setResolution(width / scaleFactor, height / scaleFactor);

  const unsigned char offset = offsetof(Image::Pixel, y);
  unsigned char mask[16] =
  {
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
  };
  mask[0] = offset;
  mask[1] = offset + 4;
  mask[2] = offset + 8;
  mask[3] = offset + 12;
  const __m128i mMask = _mm_loadu_si128(reinterpret_cast<__m128i*>(mask));

  const __m128i zero = _mm_setzero_si128();
  const int summsSize = destImage.width * 16;
  __m128i* summs = reinterpret_cast<__m128i*>(SystemCall::alignedMalloc(summsSize, 16));
  memset(summs, 0, summsSize);

  const Image::Pixel* pSrc;
  Thumbnail::ThumbnailImageGrayscale::PixelType* pDest;
  __m128i* pSumms;

  __m128i p0;
  __m128i p1;
  __m128i p2;
  __m128i p3;

  for(int y = 0; y < height; ++y)
  {
    if(y % scaleFactor == 0)
    {
      pDest = destImage[y / scaleFactor];
    }
    pSrc = srcImage[y];
    pSumms = summs;
    for(int x = 0; x < width; x += 8, pSrc += 8, ++pSumms)
    {
      p0 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pSrc));
      p1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(pSrc + 4));

      p0 = SHUFFLE(p0, mMask); // y0 y1 y2 y3 0 0 0 0 0 0 0 0 0 0 0 0
      p1 = SHUFFLE(p1, mMask); // y4 y5 y6 y7 0 0 0 0 0 0 0 0 0 0 0 0

      p0 = _mm_unpacklo_epi32(p0, p1); // y0 y1 y2 y3 y4 y5 y6 y7 0 0 0 0 0 0 0 0
      p0 = _mm_unpacklo_epi8(p0, zero); // y0 y1 y2 y3 y4 y5 y6 y7
      *pSumms = _mm_add_epi16(*pSumms, p0);
    }

    if(y % scaleFactor == scaleFactor - 1)
    {
      pSumms = summs;
      for (int i = 0; i < destImage.width; i += 8, pSumms += 4, pDest += 8)
      {
        p0 = *pSumms;
        p1 = *(pSumms + 1);
        p2 = *(pSumms + 2);
        p3 = *(pSumms + 3);

        p0 = _mm_hadd_epi16(p0, p1);
        p1 = _mm_hadd_epi16(p2, p3);
        p0 = _mm_hadd_epi16(p0, p1);
        p0 = _mm_srli_epi16(p0, 4);
        p0 = _mm_packus_epi16(p0, zero);
        splitter.a = p0;
        *reinterpret_cast<long long*>(pDest) = splitter.b[0];
      }
      memset(summs, 0, summsSize);
    }
  }
  SystemCall::alignedFree(summs);
}