 float ssemax_reference(const float a, const float b)
 {
     float ret;
     _mm_store_ss(&ret, _mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
     return ret;
 }