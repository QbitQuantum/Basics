void  Build_SymbolMatrix(csptr P, PASTIX_INT cblknbr, PASTIX_INT *rangtab, SymbolMatrix *symbmtx)
{
  PASTIX_INT i, j, k, l;
  PASTIX_INT cblknum;
  PASTIX_INT ind;
  PASTIX_INT    *tmpj      = NULL;
  double *tmpa      = NULL;
  PASTIX_INT    *node2cblk = NULL;
  PASTIX_INT    *ja        = NULL;
  PASTIX_INT n;

  n = rangtab[cblknbr];

  /**** First we transform the P matrix to find the block ****/
  MALLOC_INTERN(tmpj, n, PASTIX_INT);
  MALLOC_INTERN(tmpa, n, double);
  MALLOC_INTERN(node2cblk, n, PASTIX_INT);


  for(k=0;k<cblknbr;k++)
    for(i=rangtab[k];i<rangtab[k+1];i++)
      node2cblk[i] = k;

  for(k=0;k<cblknbr;k++)
    {
      /*i = rangtab[k];*/ /*OLD VERSION QUAND P pas recompacte */
      i = k;
#ifdef DEBUG_KASS
      ASSERT(P->nnzrow[i] >= (rangtab[k+1]-rangtab[k]), MOD_KASS);

      for(l=0;l<rangtab[k+1]-rangtab[k];l++)
        {
          ASSERT(P->ja[i][l] == rangtab[k]+l, MOD_KASS);
          ASSERT(node2cblk[P->ja[i][l]] == i, MOD_KASS);
        }
#endif
      ja = P->ja[i];
      j = 0;
      ind = 0;
      while(j<P->nnzrow[i])
        {
          cblknum = node2cblk[ja[j]];
          l=j+1;
          while(l < P->nnzrow[i] && ja[l] == ja[l-1]+1 && node2cblk[ja[l]] == cblknum)
            l++;

          tmpj[ind] = ja[j];
          tmpa[ind] = (double)(l-j);
          j = l;
          ind++;
        }

      memFree(P->ja[i]);
      P->nnzrow[i] = ind;
      MALLOC_INTERN(P->ja[i], ind, PASTIX_INT);
      MALLOC_INTERN(P->ma[i], ind, double);
      memCpy(P->ja[i], tmpj, sizeof(PASTIX_INT)*ind);
      memCpy(P->ma[i], tmpa, sizeof(double)*ind);

    }


  memFree(tmpj);
  memFree(tmpa);

#ifdef DEBUG_KASS
  for(k=0;k<cblknbr;k++)
    {
      /*i = rangtab[k];*/
      i = k;
      assert(P->nnzrow[i] > 0);

      if(P->ma[i][0] != (double)(rangtab[k+1]-rangtab[k]))
        print_one("Cblk %ld ma %ld rg %ld \n", k, (PASTIX_INT)P->ma[i][0],rangtab[k+1]-rangtab[k]);

      assert(P->ma[i][0] == (double)(rangtab[k+1]-rangtab[k]));
    }
#endif

  /**********************************/
  /*** Compute the symbol matrix ****/
  /**********************************/
  symbmtx->baseval = 0;
  symbmtx->cblknbr = cblknbr;

  ind = 0;
  symbmtx->bloknbr = CSnnz(P);
  symbmtx->nodenbr = rangtab[cblknbr];

  MALLOC_INTERN(symbmtx->cblktab, cblknbr+1,        SymbolCblk);
  MALLOC_INTERN(symbmtx->bloktab, symbmtx->bloknbr, SymbolBlok);

  ind = 0;
  for(k=0;k<cblknbr;k++)
    {
      symbmtx->cblktab[k].fcolnum = rangtab[k];
      symbmtx->cblktab[k].lcolnum = rangtab[k+1]-1;
      symbmtx->cblktab[k].bloknum = ind;
      /*l = rangtab[k];*/ /** OLD VERSION **/
      l = k;
      for(i=0;i<P->nnzrow[l];i++)
        {
          j = P->ja[l][i];
          symbmtx->bloktab[ind].frownum = j;
          symbmtx->bloktab[ind].lrownum = j+(PASTIX_INT)(P->ma[l][i])-1;
          symbmtx->bloktab[ind].cblknum = node2cblk[j];
          symbmtx->bloktab[ind].levfval = 0;
          ind++;
        }
#ifdef DEBUG_KASS
      assert(symbmtx->bloktab[symbmtx->cblktab[k].bloknum].frownum == symbmtx->cblktab[k].fcolnum);
      assert(symbmtx->bloktab[symbmtx->cblktab[k].bloknum].lrownum == symbmtx->cblktab[k].lcolnum);
      assert(symbmtx->bloktab[symbmtx->cblktab[k].bloknum].cblknum == k);
#endif


    }
  /*  virtual cblk to avoid side effect in the loops on cblk bloks */
  symbmtx->cblktab[cblknbr].fcolnum = symbmtx->cblktab[cblknbr-1].lcolnum+1;
  symbmtx->cblktab[cblknbr].lcolnum = symbmtx->cblktab[cblknbr-1].lcolnum+1;
  symbmtx->cblktab[cblknbr].bloknum = ind;

#ifdef DEBUG_KASS
  if(ind != symbmtx->bloknbr)
    fprintf(stderr, "ind %ld bloknbr %ld \n", ind, symbmtx->bloknbr);
  assert(ind == symbmtx->bloknbr);
#endif


  memFree(node2cblk);
}