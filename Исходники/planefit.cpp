// Fit a plane to 3D data
void PlaneFit::fitPlane(const Points3D& P, Eigen::Vector4d& coeff, Eigen::Vector3d& mean)
{
	// Calculate a point on the plane and the normal vector to it
	Eigen::Vector3d normal;
	fitPlane(P, normal, mean);

	// Construct the coefficient vector (a,b,c,d) where the equation of the plane is ax + by + cz + d = 0
	coeff << normal, -normal.dot(mean);
}