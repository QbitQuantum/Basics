double compareT(Eigen::Isometry3d a, Eigen::Isometry3d b,
		Eigen::VectorXd weight)
{
	Eigen::Quaterniond qa(a.rotation());
	Eigen::Quaterniond qb(b.rotation());
	Eigen::Vector3d pa = a.translation();
	Eigen::Vector3d pb = b.translation();
	Eigen::VectorXd va(7), vb(7), verr(7), vScaled(7);
	va << pa, qa.x(), qa.y(), qa.z(), qa.w();
	vb << pb, qb.x(), qb.y(), qb.z(), qb.w();
	verr = vb - va;
	vScaled = weight.cwiseProduct(verr);
	return vScaled.squaredNorm();
}