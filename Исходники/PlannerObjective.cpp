void CartesianTrackingObjective::GetDifferentialCostFunction(Real t,Matrix3& A,Vector3& b) const
{
  if(t < times.front() || t >= times.back()) {
    A.setZero();
    b.setZero();
    return;
  }
  int index=FindSegment(t);
  Real u=(t-times[index])/(times[index+1]-times[index]);
  Vector3 pu = positions[index]+u*(positions[index+1]-positions[index]);
  b = pu;
  if(matWeights.empty()) {
    A.setIdentity();
    if (!weights.empty())  A *= weights[index];
  }
  else A = matWeights[index];
}