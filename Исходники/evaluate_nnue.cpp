 ScoreKeyValue(const ScoreKeyValue& other) {
   static_assert(sizeof(ScoreKeyValue) == sizeof(__m128i),
                 "sizeof(ScoreKeyValue) should be equal to sizeof(__m128i)");
   _mm_store_si128(&as_m128i, other.as_m128i);
 }