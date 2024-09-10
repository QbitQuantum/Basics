static void
xop_test (void)
{
  int i;
  
  /* Check hsubbw */
  init_sbyte ();
  
  for (i = 0; i < NUM; i++)
    dst.x[i] = _mm_hsubw_epi8 (src1.x[i]);
  
  if (check_sbyte2word())
  abort ();
  

  /* Check hsubwd */
  init_sword ();

  for (i = 0; i < (NUM ); i++)
    dst.x[i] = _mm_hsubd_epi16 (src1.x[i]);
  
  if (check_sword2dword())
    abort (); 
   
   /* Check hsubdq */
  init_sdword ();
    for (i = 0; i < NUM; i++)
    dst.x[i] = _mm_hsubq_epi32 (src1.x[i]);
  
  if (check_dword2qword())
    abort ();
}