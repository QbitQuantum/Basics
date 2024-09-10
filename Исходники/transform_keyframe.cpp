void ATOM_RotateKeyFrame::visit (ATOM_Node &node)
{
	ATOM_Vector3f s, t;
	ATOM_Matrix4x4f r;
	ATOM_Matrix4x4f m = node.getO2T();
	m.decompose (t, r, s);

	ATOM_Quaternion q;
	q.fromEulerXYZ (getValue());
	q.toMatrix (r);

	m.m00 = r.m00 * s.x;
	m.m01 = r.m01 * s.x;
	m.m02 = r.m02 * s.x;
	m.m10 = r.m10 * s.y;
	m.m11 = r.m11 * s.y;
	m.m12 = r.m12 * s.y;
	m.m20 = r.m20 * s.z;
	m.m21 = r.m21 * s.z;
	m.m22 = r.m22 * s.z;

	node.setO2T (m);
}