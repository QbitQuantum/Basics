double JacobianEva::evaluate(HexVertex *hv, HexVertex* nhv[3]) {
	Matrix3d J = Matrix3d::Zero();
	for (int i = 0; i < 3; ++i) {
		Point pt = nhv[i]->point() - hv->point();
		pt /= pt.norm();
		for (int j = 0; j < 3; ++j) {
			J(j, i) = pt[j];
		}
	}
	
	return J.determinant();
}