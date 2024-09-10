int
AFfRdMulaw (AFILE *AFp, float Dbuff[], int Nreq)

{
  int is, N, i, Nr;
  UT_uint1_t Buf[NBBUF/LW];
  double g;

  for (is = 0; is < Nreq; ) {

    /* Read data from the audio file */
    N = MINV (NBBUF / LW, Nreq - is);
    Nr = FREAD (Buf, LW, N, AFp->fp);

    /* Convert to float */
    g = AFp->ScaleF;
    for (i = 0; i < Nr; ++i) {
      Dbuff[is] = (float) (g * Mutab[Buf[i]]);
      ++is;
    }

    if (Nr < N)
      break;
  }

  return is;
}