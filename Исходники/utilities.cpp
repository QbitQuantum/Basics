CQuaternion  DeCasteljau(CQuaternion const& q1, CQuaternion const& q2,CQuaternion const& q3, CQuaternion const& q4,float t)
{
// simplified version
//	CQuaternion pp = Slerp(Slerp(q1,q4,t),Slerp(q2,q3,t),2*t*(1-t));

	CQuaternion p1,p2,p3,p12,p23,p;
	
	p1 = Slerp(q1,q2,t);
	p2 = Slerp(q2,q3,t);
	p3 = Slerp(q3,q4,t);

	p12 = Slerp(p1,p2,t);
	p23 = Slerp(p2,p3,t);

	p= Slerp(p12,p23,t);

	return p;
}