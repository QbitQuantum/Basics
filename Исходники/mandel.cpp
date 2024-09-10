Iu32vec4 mandel_4(F32vec4 &c_re4, F32vec4 &c_im4, int max_iterations) {
  F32vec4  z_re4 = c_re4;
  F32vec4  z_im4 = c_im4;
  F32vec4  four4(4.0f);
  F32vec4  two4(2.0f);
  Iu32vec4 count4(0,0,0,0);
  Iu32vec4 one4(1,1,1,1);

  int i;

  for (i = 0; i < max_iterations; ++i) {
    F32vec4  z_re24 = z_re4 * z_re4;
    F32vec4  z_im24 = z_im4 * z_im4;
    F32vec4  mf4 = cmplt(z_re24 + z_im24, four4);
    Iu32vec4 mi4 (_mm_castps_si128((__m128)mf4));
    if (is_zero (mi4)) {
      break;
    }
    F32vec4 new_re4 = z_re24 - z_im24;
    F32vec4 new_im4 = two4 * z_re4 * z_im4;
    z_re4 = c_re4 + new_re4;
    z_im4 = c_im4 + new_im4;
    count4 = count4 + (mi4 & one4);
  }
  return count4;
}