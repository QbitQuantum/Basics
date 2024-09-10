 static batch_type select(const batch_bool_type& cond, const batch_type& a, const batch_type& b)
 {
     return _mm512_mask_blend_ps(cond, b, a);
 }