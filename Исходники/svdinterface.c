void doit(void) {
  int n,i,hashcomp;
  openfile( WORDVEC_FILE, &leftfile );
  openfile( RIGHT_SINGVEC_FILE, &rghtfile );
  openfile( SINGVAL_FILE, &singfile );
  preparelandr( "", hashrow, hashstep, hashsing, left, right, sing, &hashcomp );
  if (hashcomp<hashsing)
    printf("\n  FEWER THAN EXPECTED SINGULAR VALUES\n");
  for (i=0; i<hashsing; i++)
    fprintf(singfile,"%f\n",sing[i]);
  fclose(singfile);
  for (n=0; n<hashrow; n++)
    for (i=0; i<hashsing; i++)
      fprintf(leftfile,"%f\n",left[n][i]);
  fclose(leftfile);
  for (n=0; n<hashcol; n++)
    for (i=0; i<hashsing; i++)
      fprintf(rghtfile,"%f\n",right[n][i]);
  fclose(rghtfile);
}