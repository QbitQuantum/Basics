float robotDepth()
{
	// Two interesting points
	float alpha1 = (x + (sx-height)/2)/(float)height*2*tan(VFOV/2.);
	float alpha2 = (x - (sx+height)/2)/(float)height*2*tan(VFOV/2.);
	float beta = (y - width/2)/(float)width*2*tan(HFOV/2.);

	// Vectors
	Eigen::Vector3f v1(1,-beta,-alpha1);
	Eigen::Vector3f v2(1,-beta,-alpha2);

	// Normalization
	v1 = v1/v1.norm();
	v2 = v2/v2.norm();

	// Center
	Eigen::Vector3f c = (v1+v2)/2.;
	float c_norm = c.norm();

	// Projection
	Eigen::MatrixXf proj_mat = c.transpose()*v1;
	float proj = proj_mat(0,0);

	// Orthogonal part in v1
	Eigen::Vector3f orth = v1 - proj/c_norm*c;

	// Norm
	float orth_norm = orth.norm();

	// Approximate depth
	float d = H/2.*proj/orth_norm;
	return d;
}