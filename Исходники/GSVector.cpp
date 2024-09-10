const GSVector4 GSVector4::m_ps0123(0.0f, 1.0f, 2.0f, 3.0f);
const GSVector4 GSVector4::m_ps4567(4.0f, 5.0f, 6.0f, 7.0f);
const GSVector4 GSVector4::m_half(0.5f);
const GSVector4 GSVector4::m_one(1.0f);
const GSVector4 GSVector4::m_two(2.0f);
const GSVector4 GSVector4::m_four(4.0f);
const GSVector4 GSVector4::m_x4b000000(_mm_castsi128_ps(_mm_set1_epi32(0x4b000000)));
const GSVector4 GSVector4::m_x4f800000(_mm_castsi128_ps(_mm_set1_epi32(0x4f800000)));
const GSVector4 GSVector4::m_max(FLT_MAX);
const GSVector4 GSVector4::m_min(FLT_MIN);

#if _M_SSE >= 0x500

const GSVector8 GSVector8::m_half(0.5f);
const GSVector8 GSVector8::m_one(1.0f);
const GSVector8 GSVector8::m_x7fffffff(_mm256_castsi256_ps(_mm256_set1_epi32(0x7fffffff)));
const GSVector8 GSVector8::m_x80000000(_mm256_castsi256_ps(_mm256_set1_epi32(0x80000000)));
const GSVector8 GSVector8::m_x4b000000(_mm256_castsi256_ps(_mm256_set1_epi32(0x4b000000)));
const GSVector8 GSVector8::m_x4f800000(_mm256_castsi256_ps(_mm256_set1_epi32(0x4f800000)));
const GSVector8 GSVector8::m_max(FLT_MAX);
const GSVector8 GSVector8::m_min(FLT_MIN);

#endif

#if _M_SSE >= 0x501

const GSVector8i GSVector8i::m_xff[33] = 
{
	GSVector8i(0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000), 
	GSVector8i(0x000000ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000), 
	GSVector8i(0x0000ffff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000), 