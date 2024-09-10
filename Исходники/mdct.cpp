INT imdct_copy_ov_and_nr(
        H_MDCT hMdct,
        FIXP_DBL * pTimeData,
        INT nrSamples
        )
{
  FIXP_DBL *pOvl;
  int nt, nf, i;

  nt = fMin(hMdct->ov_offset, nrSamples);
  nrSamples -= nt;
  nf = fMin(hMdct->prev_nr, nrSamples);
  nrSamples -= nf;
  FDKmemcpy(pTimeData, hMdct->overlap.time, nt*sizeof(FIXP_DBL));
  pTimeData += nt;

  pOvl = hMdct->overlap.freq + hMdct->ov_size - 1;
  for (i=0; i<nf; i++) {
    FIXP_DBL x = - (*pOvl--);
    *pTimeData = IMDCT_SCALE_DBL(x);
    pTimeData ++;
  }

  return (nt+nf);
}