int
AFfWrMulaw (AFILE *AFp, const float Dbuff[], int Nval)

{
  int is, N, Nw, i;
  UT_uint1_t Buf[NBBUF/LW];
  double Dv;

/* Write data to the audio file */
  is = 0;
  while (is < Nval) {
    N = MINV (NBBUF / LW, Nval - is);
    for (i = 0; i < N; ++i) {
      Dv = AFp->ScaleF * Dbuff[i+is];
      if (Dv > AMAX || Dv < -AMAX)
	++AFp->Novld;
      Buf[i] = Yq[SPdQuantL (Dv, Xq, NLEV)];
    }
    Nw = FWRITE (Buf, LW, N, AFp->fp);
    is += Nw;
    if (Nw < N)
      break;
  }

  return is;
}