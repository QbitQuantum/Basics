void DecomposeEssentialUsingHorn90(double _E[9], double _R1[9], double _R2[9], double _t1[3], double _t2[3]) {
	//from : http://people.csail.mit.edu/bkph/articles/Essential.pdf
#ifdef USE_EIGEN
	using namespace Eigen;

	Matrix3d E = Map<Matrix<double,3,3,RowMajor> >(_E);
	Matrix3d EEt = E * E.transpose();
	Vector3d e0e1 = E.col(0).cross(E.col(1)),e1e2 = E.col(1).cross(E.col(2)),e2e0 = E.col(2).cross(E.col(0));
	Vector3d b1,b2;

#if 1
	//Method 1
	Matrix3d bbt = 0.5 * EEt.trace() * Matrix3d::Identity() - EEt; //Horn90 (12)
	Vector3d bbt_diag = bbt.diagonal();
	if (bbt_diag(0) > bbt_diag(1) && bbt_diag(0) > bbt_diag(2)) {
		b1 = bbt.row(0) / sqrt(bbt_diag(0));
		b2 = -b1;
	} else if (bbt_diag(1) > bbt_diag(0) && bbt_diag(1) > bbt_diag(2)) {
		b1 = bbt.row(1) / sqrt(bbt_diag(1));
		b2 = -b1;
	} else {
		b1 = bbt.row(2) / sqrt(bbt_diag(2));
		b2 = -b1;
	}
#else
	//Method 2
	if (e0e1.norm() > e1e2.norm() && e0e1.norm() > e2e0.norm()) {
		b1 = e0e1.normalized() * sqrt(0.5 * EEt.trace()); //Horn90 (18)
		b2 = -b1;
	} else if (e1e2.norm() > e0e1.norm() && e1e2.norm() > e2e0.norm()) {
		b1 = e1e2.normalized() * sqrt(0.5 * EEt.trace()); //Horn90 (18)
		b2 = -b1;
	} else {
		b1 = e2e0.normalized() * sqrt(0.5 * EEt.trace()); //Horn90 (18)
		b2 = -b1;
	}
#endif
	
	//Horn90 (19)
	Matrix3d cofactors; cofactors.col(0) = e1e2; cofactors.col(1) = e2e0; cofactors.col(2) = e0e1;
	cofactors.transposeInPlace();
	
	//B = [b]_x , see Horn90 (6) and http://en.wikipedia.org/wiki/Cross_product#Conversion_to_matrix_multiplication
	Matrix3d B1; B1 <<	0,-b1(2),b1(1),
						b1(2),0,-b1(0),
						-b1(1),b1(0),0;
	Matrix3d B2; B2 <<	0,-b2(2),b2(1),
						b2(2),0,-b2(0),
						-b2(1),b2(0),0;

	Map<Matrix<double,3,3,RowMajor> > R1(_R1),R2(_R2);

	//Horn90 (24)
	R1 = (cofactors.transpose() - B1*E) / b1.dot(b1);
	R2 = (cofactors.transpose() - B2*E) / b2.dot(b2);
	Map<Vector3d> t1(_t1),t2(_t2); 
	t1 = b1; t2 = b2;
	
	cout << "Horn90 provided " << endl << R1 << endl << "and" << endl << R2 << endl;
#endif
}