static void
fma4_test (void)
{
  int i;

  init_nmaccps ();
  
  for (i = 0; i < NUM; i++)
    dst.x[i] = _mm256_nmacc_ps (src1.x[i], src2.x[i], src3.x[i]);
  
  if (check_nmaccps ()) 
    abort ();
  
  init_nmaccpd ();
  
  for (i = 0; i < NUM; i++)
    dst.y[i] = _mm256_nmacc_pd (src1.y[i], src2.y[i], src3.y[i]);
  
  if (check_nmaccpd ()) 
    abort ();

}