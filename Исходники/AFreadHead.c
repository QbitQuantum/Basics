int
AFreadHead (FILE *fp, void *Buf, int Size, int Nv, int Swapb)

{
  double Lbuf[NBUF];
  int Nvr, n, Nreq, status;

  if (Buf == NULL) {

    /* Skip data */
    n = 0;
    if (FLseekable (fp)) {
      status = fseek (fp, Size * Nv, SEEK_CUR);
      if (status) {
	UTwarn ("AFreadHead: %s", AFM_FilePosErr);
	longjmp (AFR_JMPENV, 1);
      }
      n = Nv;
    }
    else {
      while (n < Nv) {
	Nreq = MINV (Nv - n, BSIZE (Lbuf) / Size);
	Nvr = FREAD (Lbuf, Size, Nreq, fp);
	n += Nvr;
	if (Nvr < Nreq)
	  break;
      }
    }
  }

  else {
    
    /* Read the data in file byte order */
    n = FREAD (Buf, Size, Nv, fp);

    /* Swap the data if necessary */
    if (Size != 1 && UTswapCode (Swapb) == DS_SWAP)
      VRswapBytes (Buf, Buf, Size, n);
  }

  /* Error messages */
  if (n < Nv) {
    if (ferror (fp)) {
      UTsysMsg ("AFreadHead - %s", AFM_ReadErr);
      longjmp (AFR_JMPENV, 2);
    }
    else {
      UTwarn ("AFreadHead - %s", AFM_UEoF);
      longjmp (AFR_JMPENV, 1);
    }
  }

  return (Size * n);
}