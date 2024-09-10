static int VerifyRotMxOrder(const int *ProperR, int AbsOrder, int *CumMx)
{
  int  MxA[9], MxB[9];
  int  *RR, *RRR, *Swp, iO, i;

  const int IdentityMx[] = { 1, 0, 0,
                             0, 1, 0,
                             0, 0, 1 };


  if (CumMx) for (i = 0; i < 9; i++) CumMx[i] = ProperR[i];

  RR = (int *) ProperR;
  RRR = MxA;

  for (iO = 1; iO < AbsOrder; iO++)
  {
    for (i = 0; i < 9; i++)
      if (-1 > RR[i] || RR[i] > 1)
        return -1;

    if (MemCmp(IdentityMx, RR, 9) == 0)
      return -1;

    RotMxMultiply(RRR, ProperR, RR);
    if (RR == ProperR) RR = MxB;
    Swp = RR; RR = RRR; RRR = Swp;

    if (CumMx) for (i = 0; i < 9; i++) CumMx[i] += RR[i];
  }

  if (MemCmp(IdentityMx, RR, 9) != 0)
    return -1;

  return 0;
}