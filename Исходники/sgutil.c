T_RTMx *SetLISMx(const T_SgOps *SgOps, int iLTr, int iInv, int iSMx,
                 T_RTMx *LISMx)
{
  int  i;

  MemCpy(LISMx, &SgOps->SMx[iSMx], 1);
  if (iInv) SMx_t_InvT(LISMx, SgOps->InvT, LISMx);
  rangei(3) LISMx->s.T[i] += SgOps->LTr[iLTr].v[i];

  return LISMx;
}