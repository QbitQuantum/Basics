//NOTE: this must be done after all parameters are computed
Vector4d CProxyCamera::getOpticalCenter(void) const 
{
	// orthographic case
	Vector4d ans;
	if (m_KR(2,0) == 0.0 && m_KR(2,1) == 0.0 &&
		m_KR(2,2) == 0.0) 
	{
		Vector3d vtmp[2];
		for (int i = 0; i < 2; ++i)
			for (int y = 0; y < 3; ++y)
			{
				vtmp[i][y] = m_KR(i,y);
			}

			Vector3d vtmp2 = vtmp[0].cross(vtmp[1]);
			vtmp2.normalize();
			for (int y = 0; y < 3; ++y)
			{
				ans[y] = vtmp2[y];
			}
			ans[3] = 0.0;
	}
	else 
	{
		Matrix3d A;
		Vector3d b;
		for (int y = 0; y < 3; ++y) 
		{
			for (int x = 0; x < 3; ++x)
			{
				A(y,x) = m_KR(y,x);
			}
			b[y] = - m_KT[y];
		}
		Matrix3d iA = A.inverse();
		b = iA * b;
		for (int y = 0; y < 3; ++y)
		{
			ans[y] = b[y];
		}
		ans[3] = 1.0;
	}
	return ans;
}