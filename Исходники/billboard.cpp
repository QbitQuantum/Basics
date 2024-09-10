void Billboard::LookAt(Vec3f ObjectPosition, Vec3f TargetPosition, Matrix4& matrix)	// not quiet correct yet
{
	Vec3f worldUp( 0.f, 0.f, 1.f);
	Vec3f i;
	Vec3f j;
	Vec3f k;
	
	k = TargetPosition - ObjectPosition;
	k.normalize();

	i = worldUp.crossProductWith(k);
	i.normalize();
	
	j = k.crossProductWith(i);
	
	// make matrix
	matrix.m_matrix[0] = i.x;		matrix.m_matrix[1] = i.y;		matrix.m_matrix[2] = i.z;		matrix.m_matrix[3] = 0;
	matrix.m_matrix[4] = j.x;		matrix.m_matrix[5] = j.y;		matrix.m_matrix[6] = j.z;		matrix.m_matrix[7] = 0;
	matrix.m_matrix[8] = k.x;		matrix.m_matrix[9] = k.y;		matrix.m_matrix[10] = k.z;		matrix.m_matrix[11] = 0;
	matrix.m_matrix[12] = 0.0f;		matrix.m_matrix[13] = 0.0f;		matrix.m_matrix[14] = 0.0f;		matrix.m_matrix[15] = 1;
}