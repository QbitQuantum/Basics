static uint32_t utoa32_sse2(uint32_t value, char* buffer)
{
   char* start = buffer;

   if (value < 10000)
      {
      const uint32_t d1 = (value / 100) << 1;
      const uint32_t d2 = (value % 100) << 1;

      if (value >= 1000) *buffer++ = u_ctn2s[d1];
      if (value >=  100) *buffer++ = u_ctn2s[d1+1];
      if (value >=   10) *buffer++ = u_ctn2s[d2];
                         *buffer++ = u_ctn2s[d2+1];

      return (buffer - start);
      }

   if (value < 100000000)
      {
      // Experiment shows that in this case SSE2 is slower
#  if 0
      const __m128i a = Convert8DigitsSSE2(value);

      // Convert to bytes, add '0'
      const __m128i va = _mm_add_epi8(_mm_packus_epi16(a, _mm_setzero_si128()), reinterpret_cast<const __m128i*>(kAsciiZero)[0]);

      // Count number of digit
      const unsigned mask = _mm_movemask_epi8(_mm_cmpeq_epi8(va, reinterpret_cast<const __m128i*>(kAsciiZero)[0]));
      unsigned long digit;
#  ifdef _MSC_VER
      _BitScanForward(&digit, ~mask | 0x8000);
#  else
      digit = __builtin_ctz(~mask | 0x8000);
#  endif

      // Shift digits to the beginning
      __m128i result = ShiftDigits_SSE2(va, digit);
      //__m128i result = _mm_srl_epi64(va, _mm_cvtsi32_si128(digit * 8));
      _mm_storel_epi64(reinterpret_cast<__m128i*>(buffer), result);

      return (buffer + 8 - digit - start);
#  else
      // value = bbbbcccc
      const uint32_t b = value / 10000;
      const uint32_t c = value % 10000;

      const uint32_t d1 = (b / 100) << 1;
      const uint32_t d2 = (b % 100) << 1;

      const uint32_t d3 = (c / 100);
      const uint32_t d4 = (c % 100);

      if (value >= 10000000) *buffer++ = u_ctn2s[d1];
      if (value >=  1000000) *buffer++ = u_ctn2s[d1+1];
      if (value >=   100000) *buffer++ = u_ctn2s[d2];
                             *buffer++ = u_ctn2s[d2+1];

      U_NUM2STR16(buffer,   d3);
      U_NUM2STR16(buffer+2, d4);

      return (buffer + 4 - start);
#  endif
      }

   // value = aabbbbbbbb in decimal

   const uint32_t a = value  / 100000000; // 1 to 42
                      value %= 100000000;

   if (a < 10) *buffer++ = '0' + (char)a;
   else
      {
      U_NUM2STR16(buffer, a);

      buffer += 2;
      }

   const __m128i b = Convert8DigitsSSE2(value);
   const __m128i ba = _mm_add_epi8(_mm_packus_epi16(_mm_setzero_si128(), b), reinterpret_cast<const __m128i*>(kAsciiZero)[0]);
   const __m128i result = _mm_srli_si128(ba, 8);

   _mm_storel_epi64(reinterpret_cast<__m128i*>(buffer), result);

   return (buffer + 8 - start);
}