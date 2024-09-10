int
AFfWrI1 (AFILE *AFp, const float Dbuff[], int Nval)

{
  int is, N, Nw, i;
  UT_int1_t Buf[NBBUF/LW1];
  double g, Dv;

/* Write data to the audio file */
  is = 0;
  g = AFp->ScaleF;
  while (is < Nval) {
    N = MINV (NBBUF / LW1, Nval - is);
    for (i = 0; i < N; ++i) {
      Dv = g * Dbuff[i+is];
      if (Dv >= 0.0) {
	Dv += 0.5;
	if (Dv >= UT_INT1_MAX + 1) {
	  ++AFp->Novld;
	  Dv = UT_INT1_MAX;
	}
      }
      else {
	Dv += -0.5;
	if (Dv <= UT_INT1_MIN - 1) {
	  ++AFp->Novld;
	  Dv = UT_INT1_MIN;
	}
      }
      Buf[i] = (UT_int1_t) Dv;
    }
    Nw = FWRITE (Buf, LW1, N, AFp->fp);
    is += Nw;
    if (Nw < N)
      break;
  }

  return is;
}