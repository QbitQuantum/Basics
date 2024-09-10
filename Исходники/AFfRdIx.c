int
AFfRdI3 (AFILE *AFp, float Dbuff[], int Nreq)

{
  int is, N, i, Nr, Hbo;
  UT_int4_t Iv;
  unsigned char Buf[NBBUF];
  unsigned char *cp;
  unsigned char t;
  double g;

  Hbo = UTbyteOrder ();
  cp = (unsigned char *) &Iv;
  for (is = 0; is < Nreq; ) {

    /* Read data from the audio file */
    N = MINV (NBBUF/LW3, Nreq - is);
    Nr = FREAD (Buf, LW3, N, AFp->fp);

    /* Byte swap and convert to float */
    g = AFp->ScaleF;
    for (i = 0; i < LW3*Nr; i += LW3) {
      if (AFp->Swapb == DS_SWAP) {
	t = Buf[i+2]; Buf[i+2] = Buf[i]; Buf[i] = t;
      }
      if (Hbo == DS_EL) {
	cp[0] = 0;
	cp[1] = Buf[i];
	cp[2] = Buf[i+1];
	cp[3] = Buf[i+2];	/* Most significant byte */
      }
      else {
	cp[0] = Buf[i];		/* Most significant byte */
	cp[1] = Buf[i+1];
	cp[2] = Buf[i+2];
	cp[3] = 0;
      }
      Dbuff[is] = (float) (g * (Iv / 256));
      ++is;
    }

    if (Nr < N)
      break;
  }

  return is;
}