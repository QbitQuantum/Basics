int
VBmap::readdata()
{
  int err;
  err=coords.ReadFile(coordfile);
  // 
  err=ts.ReadFile(lesionfile);
  // 
  err=dv.ReadFile(dvfile);
  // 
  // params matrix is one row for each pair of coordinates, columns
  // for: intercept, vox1, vox2, interaction, error, stat for int,
  // stat for v1, stat for v2, stat for v1*v2

  if (permfile.size())
    err=permmat.ReadFile(permfile);
  return 0;
}