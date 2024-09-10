void GetCovariance(const vector<Vector3>& pts,Matrix3& C)
{
  C.setZero();
  Vector3 mean=GetMean(pts);
  for(size_t i=0;i<pts.size();i++) {
    Vector3 p = pts[i]-mean;
    Rank1Update(C,p,p);
  }
}