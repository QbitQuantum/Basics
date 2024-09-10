static void
sse5_test (void)
{
  int i;
  
  /* Check haddbw */
  init_sbyte ();
  
  for (i = 0; i < NUM; i++)
    dst.x[i] = _mm_haddw_epi8 (src1.x[i]);
  
  if (check_sbyte2word())
  abort ();
  
  /* Check haddbd */
  for (i = 0; i < (NUM ); i++)
    dst.x[i] = _mm_haddd_epi8 (src1.x[i]);
  
  if (check_sbyte2dword())
    abort (); 
  
  /* Check haddbq */
  for (i = 0; i < NUM; i++)
    dst.x[i] = _mm_haddq_epi8 (src1.x[i]);
  
  if (check_sbyte2qword())
    abort ();

  /* Check haddwd */
  init_sword ();

  for (i = 0; i < (NUM ); i++)
    dst.x[i] = _mm_haddd_epi16 (src1.x[i]);
  
  if (check_sword2dword())
    abort (); 
   
  /* Check haddbwq */
 
  for (i = 0; i < NUM; i++)
    dst.x[i] = _mm_haddq_epi16 (src1.x[i]);
  
  if (check_sword2qword())
    abort ();
 
  /* Check haddq */
  init_sdword ();

    for (i = 0; i < NUM; i++)
    dst.x[i] = _mm_haddq_epi32 (src1.x[i]);
  
  if (check_dword2qword())
    abort ();
}