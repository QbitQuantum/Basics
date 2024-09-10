/* =============================================================== */
int32_t l3dskelsurf(struct xvimage * k, int32_t nsteps)
/* =============================================================== */
/* 
   squelette surfacique 3d dans la grille de Khalimsky 
*/
#undef F_NAME
#define F_NAME "l3dskelsurf"
{
  struct xvimage * kp;
  int32_t stablealpha, stablebeta, i;
  index_t x, y, z;
  index_t rs, cs, ps, d, N;
  uint8_t * K;
  uint8_t * KP;

  rs = rowsize(k);
  cs = colsize(k);
  d = depth(k);
  ps = rs * cs;
  N = ps * d;
  K = UCHARDATA(k);

#ifdef VERBOSE
  fprintf(stderr, "%s: Debut traitement\n", F_NAME);
#endif

  InitPileGrilles3d();

  kp = copyimage(k);
  if (kp == NULL)
  {   fprintf(stderr,"%s : copyimage failed\n", F_NAME);
      return 0;
  }  
  KP = UCHARDATA(kp);

  if (nsteps == -1) nsteps = 1000000000;

  for (i = 1; i <= nsteps; i++)
  {
#ifdef VERBOSE
    fprintf(stderr, "step %d\n", i);
#endif
    if (i % 2)
    {
      stablealpha = 1;
      for (z = 0; z < d; z++)
      for (y = 0; y < cs; y++)
      for (x = 0; x < rs; x++)
        if (K[z * ps + y * rs + x] && Alpha3Simple3d(k, x, y, z) && !Surfend3d(k, x, y, z))
          { KP[z * ps + y * rs + x] = 0; stablealpha = 0; }
      memcpy(K, KP, N);
    }
    else
    {
      stablebeta = 1;
      for (z = 0; z < d; z++)
      for (y = 0; y < cs; y++)
      for (x = 0; x < rs; x++)
        if (K[z * ps + y * rs + x] && Beta3Simple3d(k, x, y, z) && !Surfend3d(k, x, y, z))
          { KP[z * ps + y * rs + x] = 0; stablebeta = 0; }
      memcpy(K, KP, N);
    }
    if (stablealpha && stablebeta) break;
  }

  TerminePileGrilles3d();
  freeimage(kp);

  return 1;

} /* l3dskelsurf() */