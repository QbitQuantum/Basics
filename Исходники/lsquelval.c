/* ==================================== */
int32_t lsquelval(struct xvimage *image, // entree/sortie: image originale / squelette
              struct xvimage *dx,    // entree/sortie: distance / distance topologique
              int32_t connex, 
              int32_t val_inhibit)
/* ==================================== */
#undef F_NAME
#define F_NAME "lsquelval"
{ 
  int32_t k;
  int32_t x;                       /* index muet de pixel */
  int32_t y;                       /* index muet (generalement un voisin de x) */
  int32_t rs = rowsize(image);     /* taille ligne */
  int32_t cs = colsize(image);     /* taille colonne */
  int32_t N = rs * cs;             /* taille image */
  struct xvimage *dt;          /* pour le calcul de la "distance topologique" */
  uint8_t *IM = UCHARDATA(image);      /* l'image de depart */
  uint32_t *DX;           /* fonction distance au complementaire de IM */
  uint32_t *DT;                    /* fonction "distance topologique" */
  uint32_t d;
  Rbt * RBT;
  int32_t taillemaxrbt;

  IndicsInit(N);
  if ((rowsize(dx) != rs) || (colsize(dx) != cs) || (depth(dx) != 1))
  {
    fprintf(stderr, "%s() : bad size for dx\n", F_NAME);
    return(0);
  }
  if (datatype(dx) != VFF_TYP_4_BYTE)
  {
    fprintf(stderr, "%s() : datatype(dx) must be uint32_t\n", F_NAME);
    return(0);
  }
  DX = ULONGDATA(dx); 
  dt = copyimage(dx);
  DT = ULONGDATA(dt); 
  taillemaxrbt = 2 * rs + 2 * cs ;
  /* cette taille est indicative, le RBT est realloue en cas de depassement */
  RBT = mcrbt_CreeRbtVide(taillemaxrbt);
  if (RBT == NULL)
  {
    fprintf(stderr, "%s() : mcrbt_CreeRbtVide failed\n", F_NAME);
    return(0);
  }

  /* ================================================ */
  /*               PREMIERE PHASE                     */
  /* ================================================ */

#ifdef VERBOSE
    printf("1ere etape\n");
#endif

  // INITIALISATION DT
  for (x = 0; x < N; x++) if (IM[x]) DT[x] = INFINI; else DT[x] = 0;

  // INITIALISATION DU RBT
  for (x = 0; x < N; x++)
    if (IM[x] && (DX[x] != val_inhibit) && bordext8(IM, x, rs, N))
    {
      mcrbt_RbtInsert(&RBT, DX[x], x);
      Set(x, EN_RBT);
    } // if, for

  d = 1;
  if (connex == 4)
  {
    while (!mcrbt_RbtVide(RBT))
    {
      x = RbtPopMin(RBT);
      UnSet(x, EN_RBT);
#ifdef DEBUG
      printf("pop x = %d,%d, im = %d, dx = %ld\n", x%rs, x/rs, IM[x], DX[x]);
#endif
      if (simple4(IM, x, rs, N))
      {
        DT[x] = d;
        IM[x] = 0;
        d++;
        for (k = 0; k < 8; k += 1)         /* parcourt les voisins en 8-connexite  */
        {                                              /* pour empiler les voisins */
          y = voisin(x, k, rs, N);                             /* non deja empiles */
          if ((y != -1) && (IM[y]) && (DX[y] != val_inhibit) && (! IsSet(y, EN_RBT)))
          {
            mcrbt_RbtInsert(&RBT, DX[y], y);
            Set(y, EN_RBT);
          } /* if y */
        } /* for k */      
      } // if (simple4(IM, x, rs, N))
    } /* while (!mcrbt_RbtVide(RBT)) */
  } /* if (connex == 4) */
  else
  if (connex == 8)
  {
    while (!mcrbt_RbtVide(RBT))
    {
      x = RbtPopMin(RBT);
      UnSet(x, EN_RBT);
#ifdef DEBUG
      printf("pop x = %d,%d, im = %d, dx = %ld\n", x%rs, x/rs, IM[x], DX[x]);
#endif
      if (simple8(IM, x, rs, N))
      {
        DT[x] = d;
        IM[x] = 0;
        d++;
        for (k = 0; k < 8; k += 1)         /* parcourt les voisins en 8-connexite  */
        {                                              /* pour empiler les voisins */
          y = voisin(x, k, rs, N);                             /* non deja empiles */
          if ((y != -1) && (IM[y]) && (DX[y] != val_inhibit) && (! IsSet(y, EN_RBT)))
          {
            mcrbt_RbtInsert(&RBT, DX[y], y);
            Set(y, EN_RBT);
          } /* if y */
        } /* for k */      
      } // if (simple8(IM, x, rs, N))
    } /* while (!mcrbt_RbtVide(RBT)) */
  } /* if (connex == 8) */

#ifdef DEBUG
  writeimage(dt, "_dt");
#endif

  /* ================================================ */
  /*               SECONDE PHASE                      */
  /* ================================================ */

#ifdef SECONDE_PHASE

  stabilite = 0;
  while (!stabilite)
  {
#ifdef VERBOSE
    printf("2eme etape\n");
#endif
    stabilite = 1;

    // INITIALISATION DU RBT
    for (j = 1; j < cs-1; j++) 
      for (i = 1; i < rs-1; i++) 
      {
        x = j * rs + i;
        if (DT[x] && (DT[x] != INFINI)) mcrbt_RbtInsert(&RBT, DT[x], x);
      }

    if (connex == 4)
    {
      while (!mcrbt_RbtVide(RBT))
      {
        x = RbtPopMin(RBT);
#ifdef DEBUG
        printf("pop x = %d,%d, dt = %ld\n", x%rs, x/rs, DT[x]);
#endif
        if (abaisse4(x, DT, rs, N)) 
        {
          stabilite = 0;
#ifdef DEBUG
          printf("abaisse a %ld\n", DT[x]);
#endif
	} // if (abaisse4(x, DT, rs, N)) 
      } // while (!mcrbt_RbtVide(RBT))
    } // if (connex == 4)
    else
    if (connex == 8)
    {
      int32_t abaisse;
      while (!mcrbt_RbtVide(RBT))
      {
        x = RbtPopMin(RBT);
#ifdef DEBUG
        printf("pop x = %d,%d, dt = %d\n", x%rs, x/rs, DT[x]);
#endif
        if (abaisse8(x, DT, rs, N)) 
        {
          stabilite = 0;
#ifdef DEBUG
          printf("abaisse a %ld\n", DT[x]);
#endif
	} // if (abaisse8(x, DT, rs, N)) 
      } // while (!mcrbt_RbtVide(RBT))
    } // if (connex == 8)
  } // while (!stabilite)

#endif

  // RECUPERATION DU RESULTAT
  d = 0; // valeur pour l'infini: plus grande valeur finie + 1
  for (x = 0; x < N; x++) if ((DT[x] > d) && (DT[x] < INFINI)) d = DT[x];
  d += 1;
  for (x = 0; x < N; x++) if (DT[x] == INFINI) DX[x] = d; else DX[x] = DT[x];
  
  /* ================================================ */
  /* UN PEU DE MENAGE                                 */
  /* ================================================ */

  IndicsTermine();
  mcrbt_RbtTermine(RBT);
  freeimage(dt);
  return(1);
} /* lsquelval() */