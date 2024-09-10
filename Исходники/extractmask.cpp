void
Extractor::Go()
{
  double val;

  for (int i=0; i<newcube.dimx; i++) {
    for (int j=0; j<newcube.dimy; j++) {
      for (int k=0; k<newcube.dimz; k++) {
	val=regioncode(i,j,k);
	if (xvflag==0 || val==xval)
	  newcube.SetValue(i,j,k,val);
      }
    }
  }
  newcube.WriteFile();

  return;
}