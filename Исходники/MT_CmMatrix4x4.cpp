MT_CmMatrix4x4::MT_CmMatrix4x4(const MT_Point3& orig,
							 const MT_Vector3& dir,
							 const MT_Vector3 up)
{
	MT_Vector3 z = -(dir.normalized());
	MT_Vector3 x = (up.cross(z)).normalized();
	MT_Vector3 y = (z.cross(x));
	
	m_V[0][0] = x.x();
	m_V[0][1] = y.x();
	m_V[0][2] = z.x();
	m_V[0][3] = 0.0f;
	
	m_V[1][0] = x.y();
	m_V[1][1] = y.y();
	m_V[1][2] = z.y();
	m_V[1][3] = 0.0f;
	
	m_V[2][0] = x.z();
	m_V[2][1] = y.z();
	m_V[2][2] = z.z();
	m_V[2][3] = 0.0f;
	
	m_V[3][0] = orig.x();//0.0f;
	m_V[3][1] = orig.y();//0.0f;
	m_V[3][2] = orig.z();//0.0f;
	m_V[3][3] = 1.0f;
	
	//Translate(-orig);
}