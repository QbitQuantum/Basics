void ParametricSurface<Real>::ComputePrincipalCurvatureInfo (Real u, Real v,
        Real& curv0, Real& curv1, Vector3<Real>& dir0,
        Vector3<Real>& dir1)
{
	// Tangents:  T0 = (x_u,y_u,z_u), T1 = (x_v,y_v,z_v)
	// Normal:    N = Cross(T0,T1)/Length(Cross(T0,T1))
	// Metric Tensor:    G = +-                      -+
	//                       | Dot(T0,T0)  Dot(T0,T1) |
	//                       | Dot(T1,T0)  Dot(T1,T1) |
	//                       +-                      -+
	//
	// Curvature Tensor:  B = +-                          -+
	//                        | -Dot(N,T0_u)  -Dot(N,T0_v) |
	//                        | -Dot(N,T1_u)  -Dot(N,T1_v) |
	//                        +-                          -+
	//
	// Principal curvatures k are the generalized eigenvalues of
	//
	//     Bw = kGw
	//
	// If k is a curvature and w=(a,b) is the corresponding solution to
	// Bw = kGw, then the principal direction as a 3D vector is d = a*U+b*V.
	//
	// Let k1 and k2 be the principal curvatures.  The mean curvature
	// is (k1+k2)/2 and the Gaussian curvature is k1*k2.

	// Compute derivatives.
	Vector3<Real> derU = PU(u,v);
	Vector3<Real> derV = PV(u,v);
	Vector3<Real> derUU = PUU(u,v);
	Vector3<Real> derUV = PUV(u,v);
	Vector3<Real> derVV = PVV(u,v);

	// Compute the metric tensor.
	Matrix2<Real> metricTensor;
	metricTensor[0][0] = derU.Dot(derU);
	metricTensor[0][1] = derU.Dot(derV);
	metricTensor[1][0] = metricTensor[0][1];
	metricTensor[1][1] = derV.Dot(derV);

	// Compute the curvature tensor.
	Vector3<Real> normal = derU.UnitCross(derV);
	Matrix2<Real> curvatureTensor;
	curvatureTensor[0][0] = -normal.Dot(derUU);
	curvatureTensor[0][1] = -normal.Dot(derUV);
	curvatureTensor[1][0] = curvatureTensor[0][1];
	curvatureTensor[1][1] = -normal.Dot(derVV);

	// Characteristic polynomial is 0 = det(B-kG) = c2*k^2+c1*k+c0.
	Real c0 = curvatureTensor.Determinant();
	Real c1 = ((Real)2)*curvatureTensor[0][1]* metricTensor[0][1] -
	          curvatureTensor[0][0]*metricTensor[1][1] -
	          curvatureTensor[1][1]*metricTensor[0][0];
	Real c2 = metricTensor.Determinant();

	// Principal curvatures are roots of characteristic polynomial.
	Real temp = Math<Real>::Sqrt(Math<Real>::FAbs(c1*c1 - ((Real)4)*c0*c2));
	Real mult = ((Real)0.5)/c2;
	curv0 = -mult*(c1+temp);
	curv1 = mult*(-c1+temp);

	// Principal directions are solutions to (B-kG)w = 0,
	// w1 = (b12-k1*g12,-(b11-k1*g11)) OR (b22-k1*g22,-(b12-k1*g12)).
	Real a0 = curvatureTensor[0][1] - curv0*metricTensor[0][1];
	Real a1 = curv0*metricTensor[0][0] - curvatureTensor[0][0];
	Real length = Math<Real>::Sqrt(a0*a0 + a1*a1);
	if (length >= Math<Real>::ZERO_TOLERANCE)
	{
		dir0 = a0*derU + a1*derV;
	}
	else
	{
		a0 = curvatureTensor[1][1] - curv0*metricTensor[1][1];
		a1 = curv0*metricTensor[0][1] - curvatureTensor[0][1];
		length = Math<Real>::Sqrt(a0*a0 + a1*a1);
		if (length >= Math<Real>::ZERO_TOLERANCE)
		{
			dir0 = a0*derU + a1*derV;
		}
		else
		{
			// Umbilic (surface is locally sphere, any direction principal).
			dir0 = derU;
		}
	}
	dir0.Normalize();

	// Second tangent is cross product of first tangent and normal.
	dir1 = dir0.Cross(normal);
}