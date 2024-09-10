static void
fma4_test (void)
{
  int i;

  init_maccps ();
  
  for (i = 0; i < NUM; i++)
    dst.x[i] = _mm256_macc_ps (src1.x[i], src2.x[i], src3.x[i]);
  
  if (check_maccps ()) 
    abort ();

  init_maccpd ();
  
  for (i = 0; i < NUM; i++)
    dst.y[i] = _mm256_macc_pd (src1.y[i], src2.y[i], src3.y[i]);
  
  if (check_maccpd ()) 
    abort ();  
}