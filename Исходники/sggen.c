int ExpSgRMx(T_SgOps *SgOps, const int NewRMx[9])
{
  T_RTMx  SMx[1];

  MemCpy(SMx->s.R, NewRMx, 9);
  IntSetZero(SMx->s.T, 3);
  return ExpSgSMx(SgOps, SMx);
}