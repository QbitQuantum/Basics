void MeshOptimize2dSurfaces :: 
GetNormalVector(INDEX surfind, const Point<3> & p, Vec<3> & n) const
{
  Vec<3> hn = n;
  geometry.GetSurface(surfind)->CalcGradient (p, hn);
  hn.Normalize();
  n = hn;

  /*
  if (geometry.GetSurface(surfind)->Inverse())
    n *= -1;
  */
}