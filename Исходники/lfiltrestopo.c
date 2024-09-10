/* =============================================================== */
int32_t ltaflambda(struct xvimage * image, int32_t connexmin, int32_t rayon, int32_t lambdapics, int32_t lambdapuits)
/* =============================================================== */
#undef F_NAME
#define F_NAME "ltaflambda"
{
  struct xvimage * copy;
  struct xvimage * save;
  int32_t rs, cs, ds, ps, N;
  int32_t ndes;

  rs = rowsize(image);     /* taille ligne */
  cs = colsize(image);     /* taille colonne */
  ps = rs * cs;            /* taille plan */
  ds = depth(image);       /* nombre plans */
  N = ds * ps;             /* taille image */

  if (rayon == -1) rayon = 2000000000;   

  if (ds == 1) /* ======================= 2D ========================*/
  {
    copy = copyimage(image);
    save = copyimage(image);
    if ((copy == NULL) || (save == NULL))
    {
      fprintf(stderr, "%s: copyimage failed\n", F_NAME);
      return 0;
    }

    do
    {
      if (! lhthindelta(image, NULL, rayon, connexmin))
      {
        fprintf(stderr, "%s: lhthindelta failed\n", F_NAME);
        return 0;
      }
      ndes = p_deslambdapics(image, connexmin, lambdapics);
      if (! lhtkernu(image, copy, connexmin))
      {
        fprintf(stderr, "%s: lhtkernu failed\n", F_NAME);
        return 0;
      }
      subimage(copy, image);
      memcpy(UCHARDATA(image), UCHARDATA(save), N);

      if (! lhthickdelta(image, NULL, rayon, connexmin))
      {
        fprintf(stderr, "%s: lhthickdelta failed\n", F_NAME);
        return 0;
      }
      ndes += p_deslambdapuits(image, connexmin, lambdapuits);
      if (! lhtkern(image, save, connexmin))
      {
        fprintf(stderr, "%s: lhtkern failed\n", F_NAME);
        return 0;
      }
      subimage(image, copy);
      if (ndes) 
      {
        memcpy(UCHARDATA(copy), UCHARDATA(image), N);
        memcpy(UCHARDATA(save), UCHARDATA(image), N);
      }
    } while (ndes);
  }
  else /* ============================== 3D ================================*/
  {
    fprintf(stderr, "%s: 3D Not Yet Implemented\n", F_NAME);
    return 0;
  }

  freeimage(copy);
  freeimage(save);
  return 1;
} /* ltaflambda() */