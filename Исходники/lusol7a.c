/* ==================================================================
   lu7for  (forward sweep) updates the LU factorization  A = L*U
   when row  iw = ip(klast)  of  U  is eliminated by a forward
   sweep of stabilized row operations, leaving  ip * U * iq  upper
   triangular.
   The row permutation  ip  is updated to preserve stability and/or
   sparsity.  The column permutation  iq  is not altered.
   kfirst  is such that row  ip(kfirst)  is the first row involved
   in eliminating row  iw.  (Hence,  kfirst  marks the first nonzero
   in row  iw  in pivotal order.)  If  kfirst  is unknown it may be
   input as  1.
   klast   is such that row  ip(klast)  is the row being eliminated.
   klast   is not altered.
   lu7for  should be called only if  kfirst .le. klast.
   If  kfirst = klast,  there are no nonzeros to eliminate, but the
   diagonal element of row  ip(klast)  may need to be moved to the
   front of the row.
   ------------------------------------------------------------------
   On entry,  locc(*)  must be zero.

   On exit:
   inform = 0  if row iw has a nonzero diagonal (could be small).
   inform = 1  if row iw has no diagonal.
   inform = 7  if there is not enough storage to finish the update.

   On a successful exit (inform le 1),  locc(*)  will again be zero.
   ------------------------------------------------------------------
      Jan 1985: Final f66 version.
   09 May 1988: First f77 version.
   ================================================================== */
void LU7FOR(LUSOLrec *LUSOL, int KFIRST, int KLAST, int *LENL, int *LENU,
                     int *LROW, int *INFORM, REAL *DIAG)
{
  MYBOOL SWAPPD;
  int    KBEGIN, IW, LENW, LW1, LW2, JFIRST, MINFRE, NFREE, L, J, KSTART, KSTOP, K,
         LFIRST, IV, LENV, LV1, JLAST, LV2, LV3, LV, JV, LW, LDIAG, LIMIT;
  REAL   AMULT, LTOL, USPACE, SMALL, VJ, WJ;

  LTOL   = LUSOL->parmlu[LUSOL_RP_UPDATEMAX_Lij];
  SMALL  = LUSOL->parmlu[LUSOL_RP_ZEROTOLERANCE];
  USPACE = LUSOL->parmlu[LUSOL_RP_COMPSPACE_U];
  KBEGIN = KFIRST;
  SWAPPD = FALSE;

/*      We come back here from below if a row interchange is performed. */
x100:
  IW = LUSOL->ip[KLAST];
  LENW = LUSOL->lenr[IW];
  if(LENW==0)
    goto x910;
  LW1 = LUSOL->locr[IW];
  LW2 = (LW1+LENW)-1;
  JFIRST = LUSOL->iq[KBEGIN];
  if(KBEGIN>=KLAST)
    goto x700;
/*      Make sure there is room at the end of the row file
        in case row  iw  is moved there and fills in completely. */
  MINFRE = LUSOL->n+1;
  NFREE = LUSOL->lena-(*LENL)-(*LROW);
  if(NFREE<MINFRE) {
    LU1REC(LUSOL, LUSOL->m,TRUE,LROW,LUSOL->indr,LUSOL->lenr,LUSOL->locr);
    LW1 = LUSOL->locr[IW];
    LW2 = (LW1+LENW)-1;
    NFREE = LUSOL->lena-(*LENL)-(*LROW);
    if(NFREE<MINFRE)
      goto x970;

  }
/*      Set markers on row  iw. */
  for(L = LW1; L <= LW2; L++) {
    J = LUSOL->indr[L];
    LUSOL->locc[J] = L;
  }
/*      ==================================================================
        Main elimination loop.
        ================================================================== */
  KSTART = KBEGIN;
  KSTOP = MIN(KLAST,LUSOL->n);
  for(K = KSTART; K <= KSTOP; K++) {
    JFIRST = LUSOL->iq[K];
    LFIRST = LUSOL->locc[JFIRST];
    if(LFIRST==0)
      goto x490;
/*         Row  iw  has its first element in column  jfirst. */
    WJ = LUSOL->a[LFIRST];
    if(K==KLAST)
      goto x490;
/*         ---------------------------------------------------------------
           We are about to use the first element of row  iv
                  to eliminate the first element of row  iw.
           However, we may wish to interchange the rows instead,
           to preserve stability and/or sparsity.
           --------------------------------------------------------------- */
    IV = LUSOL->ip[K];
    LENV = LUSOL->lenr[IV];
    LV1 = LUSOL->locr[IV];
    VJ = ZERO;
    if(LENV==0)
      goto x150;
    if(LUSOL->indr[LV1]!=JFIRST)
      goto x150;
    VJ = LUSOL->a[LV1];
    if(SWAPPD)
      goto x200;
    if(LTOL*fabs(WJ)<fabs(VJ))
      goto x200;
    if(LTOL*fabs(VJ)<fabs(WJ))
      goto x150;
    if(LENV<=LENW)
      goto x200;
/*         ---------------------------------------------------------------
           Interchange rows  iv  and  iw.
           --------------------------------------------------------------- */
x150:
    LUSOL->ip[KLAST] = IV;
    LUSOL->ip[K] = IW;
    KBEGIN = K;
    SWAPPD = TRUE;
    goto x600;
/*         ---------------------------------------------------------------
           Delete the eliminated element from row  iw
           by overwriting it with the last element.
           --------------------------------------------------------------- */
x200:
    LUSOL->a[LFIRST] = LUSOL->a[LW2];
    JLAST = LUSOL->indr[LW2];
    LUSOL->indr[LFIRST] = JLAST;
    LUSOL->indr[LW2] = 0;
    LUSOL->locc[JLAST] = LFIRST;
    LUSOL->locc[JFIRST] = 0;
    LENW--;
    (*LENU)--;
    if(*LROW==LW2)
      (*LROW)--;
    LW2 = LW2-1;
/*         ---------------------------------------------------------------
           Form the multiplier and store it in the  L  file.
           --------------------------------------------------------------- */
    if(fabs(WJ)<=SMALL)
      goto x490;
    AMULT = -WJ/VJ;
    L = LUSOL->lena-(*LENL);
    LUSOL->a[L] = AMULT;
    LUSOL->indr[L] = IV;
    LUSOL->indc[L] = IW;
    (*LENL)++;
/*         ---------------------------------------------------------------
           Add the appropriate multiple of row  iv  to row  iw.
           We use two different inner loops.  The first one is for the
           case where row  iw  is not at the end of storage.
           --------------------------------------------------------------- */
    if(LENV==1)
      goto x490;
    LV2 = LV1+1;
    LV3 = (LV1+LENV)-1;
    if(LW2==*LROW)
      goto x400;
/*         ...............................................................
           This inner loop will be interrupted only if
           fill-in occurs enough to bump into the next row.
           ............................................................... */
    for(LV = LV2; LV <= LV3; LV++) {
      JV = LUSOL->indr[LV];
      LW = LUSOL->locc[JV];
      if(LW>0) {
/*               No fill-in. */
        LUSOL->a[LW] += AMULT*LUSOL->a[LV];
        if(fabs(LUSOL->a[LW])<=SMALL) {
/*                  Delete small computed element. */
          LUSOL->a[LW] = LUSOL->a[LW2];
          J = LUSOL->indr[LW2];
          LUSOL->indr[LW] = J;
          LUSOL->indr[LW2] = 0;
          LUSOL->locc[J] = LW;
          LUSOL->locc[JV] = 0;
          (*LENU)--;
          LENW--;
          LW2--;
        }
      }
      else {
/*               Row  iw  doesn't have an element in column  jv  yet
                 so there is a fill-in. */
        if(LUSOL->indr[LW2+1]!=0)
          goto x360;
        (*LENU)++;
        LENW++;
        LW2++;
        LUSOL->a[LW2] = AMULT*LUSOL->a[LV];
        LUSOL->indr[LW2] = JV;
        LUSOL->locc[JV] = LW2;
      }
    }
    goto x490;
/*         Fill-in interrupted the previous loop.
           Move row  iw  to the end of the row file. */
x360:
    LV2 = LV;
    LUSOL->locr[IW] = (*LROW)+1;

#ifdef LUSOLFastMove
    L = LW2-LW1+1;
    if(L > 0) {
      int loci, *locp;
      for(loci = LW1, locp = LUSOL->indr+LW1;
          loci <= LW2; loci++, locp++) {
        (*LROW)++;
        LUSOL->locc[*locp] = *LROW;
      }
      LW2 = (*LROW)-L+1;
      MEMMOVE(LUSOL->a+LW2,    LUSOL->a+LW1, L);
      MEMMOVE(LUSOL->indr+LW2, LUSOL->indr+LW1, L);
      MEMCLEAR(LUSOL->indr+LW1, L);
    }
#else
    for(L = LW1; L <= LW2; L++) {
      (*LROW)++;
      LUSOL->a[*LROW] = LUSOL->a[L];
      J = LUSOL->indr[L];
      LUSOL->indr[L] = 0;
      LUSOL->indr[*LROW] = J;
      LUSOL->locc[J] = *LROW;
    }
#endif
    LW1 = LUSOL->locr[IW];
    LW2 = *LROW;
/*         ...............................................................
           Inner loop with row  iw  at the end of storage.
           ............................................................... */
x400:
    for(LV = LV2; LV <= LV3; LV++) {
      JV = LUSOL->indr[LV];
      LW = LUSOL->locc[JV];
      if(LW>0) {
/*               No fill-in. */
        LUSOL->a[LW] += AMULT*LUSOL->a[LV];
        if(fabs(LUSOL->a[LW])<=SMALL) {
/*                  Delete small computed element. */
          LUSOL->a[LW] = LUSOL->a[LW2];
          J = LUSOL->indr[LW2];
          LUSOL->indr[LW] = J;
          LUSOL->indr[LW2] = 0;
          LUSOL->locc[J] = LW;
          LUSOL->locc[JV] = 0;
          (*LENU)--;
          LENW--;
          LW2--;
        }
      }
      else {
/*               Row  iw  doesn't have an element in column  jv  yet
                 so there is a fill-in. */
        (*LENU)++;
        LENW++;
        LW2++;
        LUSOL->a[LW2] = AMULT*LUSOL->a[LV];
        LUSOL->indr[LW2] = JV;
        LUSOL->locc[JV] = LW2;
      }
    }
    *LROW = LW2;
/*         The  k-th  element of row  iw  has been processed.
           Reset  swappd  before looking at the next element. */
x490:
    SWAPPD = FALSE;
  }
/*      ==================================================================
        End of main elimination loop.
        ==================================================================

        Cancel markers on row  iw. */
x600:
  LUSOL->lenr[IW] = LENW;
  if(LENW==0)
    goto x910;
  for(L = LW1; L <= LW2; L++) {
    J = LUSOL->indr[L];
    LUSOL->locc[J] = 0;
  }
/*      Move the diagonal element to the front of row  iw.
        At this stage,  lenw gt 0  and  klast le n. */
x700:
  for(L = LW1; L <= LW2; L++) {
    LDIAG = L;
    if(LUSOL->indr[L]==JFIRST)
      goto x730;
  }
  goto x910;

x730:
  *DIAG = LUSOL->a[LDIAG];
  LUSOL->a[LDIAG] = LUSOL->a[LW1];
  LUSOL->a[LW1] = *DIAG;
  LUSOL->indr[LDIAG] = LUSOL->indr[LW1];
  LUSOL->indr[LW1] = JFIRST;
/*      If an interchange is needed, repeat from the beginning with the
        new row  iw,  knowing that the opposite interchange cannot occur. */
  if(SWAPPD)
    goto x100;
  *INFORM = LUSOL_INFORM_LUSUCCESS;
  goto x950;
/*      Singular. */
x910:
  *DIAG = ZERO;
  *INFORM = LUSOL_INFORM_LUSINGULAR;
/*      Force a compression if the file for  U  is much longer than the
        no. of nonzeros in  U  (i.e. if  lrow  is much bigger than  lenU).
        This should prevent memory fragmentation when there is far more
        memory than necessary  (i.e. when  lena  is huge). */
x950:
  LIMIT = (int) (USPACE*(*LENU))+LUSOL->m+LUSOL->n+1000;
  if(*LROW>LIMIT)
    LU1REC(LUSOL, LUSOL->m,TRUE,LROW,LUSOL->indr,LUSOL->lenr,LUSOL->locr);
  goto x990;
/*      Not enough storage. */
x970:
  *INFORM = LUSOL_INFORM_ANEEDMEM;
/*      Exit. */
x990:
;
}