double PairRelationDetector::RefPairModifier::operator() (Structure::Node *n1, Eigen::MatrixXd& m1, Structure::Node *n2, Eigen::MatrixXd& m2)
{
	double deviation(-1.0), min_dist, mean_dist, max_dist;
	if ( n1->id == n2->id)
		return deviation;
	
	
	Eigen::Vector3d refCenter = (n1->center() + n2->center())*0.5;
	Eigen::Vector3d refNormal = n1->center() - n2->center();
	refNormal.normalize();

    Eigen::MatrixXd newverts2;
    reflect_points3d(m2, refCenter, refNormal, newverts2);

	distanceBetween(m1, newverts2, min_dist, mean_dist, max_dist);
	deviation = 2 * mean_dist / (n1->bbox().diagonal().norm() + n2->bbox().diagonal().norm());

	
	if ( deviation > maxAllowDeviation_)
	{
		maxAllowDeviation_ = deviation;
	}

	return deviation;
}