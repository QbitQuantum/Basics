void SplineInterpolate(const vector<Vector>& pts,
		       GeneralizedCubicBezierSpline& path,
		       CSpace* space,GeodesicManifold* manifold,
		       Real coxDeBoorParameter)
{
  if(coxDeBoorParameter == 0) {
    //uniform
    SplineInterpolate(pts,path.segments,space,manifold);
    path.durations.resize(path.segments.size());
    fill(path.durations.begin(),path.durations.end(),1);
  }
  else {
    vector<Real> times(pts.size());
    times[0] = 0;
    path.durations.resize(pts.size()-1);
    for(size_t i=0;i+1<pts.size();i++) {
      path.durations[i] = Pow(pts[i].distance(pts[i+1]),coxDeBoorParameter);
      times[i+1] = times[i] + path.durations[i];
    }
    SplineInterpolate(pts,times,path.segments,space,manifold);
  }
}