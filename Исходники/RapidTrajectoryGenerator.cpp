Vec3 RapidTrajectoryGenerator::GetOmega(double t, double timeStep) const
{
  //Calculates the body rates necessary at time t, to rotate the normal vector.
  //The result is coordinated in the world frame, i.e. would have to be rotated into a
  //body frame.
	const Vec3 n0 = GetNormalVector(t);
	const Vec3 n1 = GetNormalVector(t + timeStep);

	const Vec3 crossProd = n0.Cross(n1); //direction of omega, in inertial axes

	if (crossProd.GetNorm2()) return  (acos(n0.Dot(n1))/timeStep)*crossProd.GetUnitVector();
	else return Vec3(0, 0, 0);
}