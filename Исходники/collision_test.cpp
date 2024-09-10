bool CollisionTester::RayTriangleTest( const Ray3& ray, const CVector3& A, const CVector3& B, const CVector3& C, CVector3& isect, float& s, float& t )
{
	const CVector3& O = ray.mOrigin;
	const CVector3& D = ray.mDirection;

	///////////////////////////////////////////////////
	// first calc intersection to plane

	CVector3 vab = (B-A);
	CVector3 vac = (C-A);

	CVector3 Nabc = vab.Cross(vac);
	float dist_O_to_P = -(O-A).Dot(Nabc)/(D.Dot(Nabc));
	isect = O+(D*dist_O_to_P); // plane_isect
		
	if( dist_O_to_P<0.0f ) return false;


	///////////////////////////////////////////////////
	// calc s and t (pseudo-barycentric method)

	//CVector3 vop = (isect-O); // debugging?
	CVector3 voa = (A-O);
	CVector3 vob = (B-O);
	CVector3 voc = (C-O);

	CPlane PlaneOCA( voc.Cross(voa).Normal(), O );
	CPlane PlaneOBA( voa.Cross(vob).Normal(), O );
		
	t = PlaneOCA.GetPointDistance( isect )/PlaneOCA.GetPointDistance(B);
	s = PlaneOBA.GetPointDistance( isect )/PlaneOBA.GetPointDistance(C);

	return ((t>=0.0f)&&(t<=1.0f)&&(s>=0.0f)&&(s<=1.0f));

}