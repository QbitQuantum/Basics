void Wml::StretchMetric1( const Vector3<Real> & q1, 
						 const Vector3<Real> & q2,
						 const Vector3<Real> & q3,
						 const Vector2<Real> & p1,
						 const Vector2<Real> & p2,
						 const Vector2<Real> & p3,
						 Real & MaxSV, Real & MinSV, Real & L2Norm, Real & LInfNorm )
{
	Real s1 = p1.X();
	Real t1 = p1.Y();
	Real s2 = p2.X();
	Real t2 = p2.Y();
	Real s3 = p3.X();
	Real t3 = p3.Y();

	Real A = (Real)0.5 * ( (s2 - s1) * (t3 - t1) - (s3 - s1) * (t2 - t1));
	if ( A > 0 ) {

		Wml::Vector3<Real> Ss = 
			(q1 * (t2-t3) + q2 * (t3-t1) + q3 * (t1-t2)) / (2*A);
		Wml::Vector3<Real> St = 
			(q1 * (s3-s2) + q2 * (s1-s3) + q3 * (s2-s1)) / (2*A);

		Real a = Ss.Dot(Ss);
		Real b = Ss.Dot(St);
		Real c = St.Dot(St);

		Real discrim = (Real)sqrt( (a-c)*(a-c) + 4*b*b );

		MaxSV = (Real)sqrt( (Real)0.5 * ( (a+c) + discrim ) );
		MinSV = (Real)sqrt( (Real)0.5 * ( (a+c) - discrim ) );

		L2Norm = (Real)sqrt( (Real)0.5 * (a+c)  );
		LInfNorm = MaxSV;
	} else {
		MaxSV = MinSV = L2Norm = LInfNorm = std::numeric_limits<Real>::max();
	}

}