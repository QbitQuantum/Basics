double ConvexHull::CSimplex4::volume()
{
	CMatrix m;

	for( int i = 1; i < 5; i ++ )
	{
		CVertex * pV = m_v[i];
		CPoint4 q = pV->point() - m_v[0]->point();
		for( int j = 0; j < 4; j ++ )
		{
			m(i-1,j) = q[j];
		}
	};

	double vol = m.determinant();

	//std::cout << "Volume is " << vol << std::endl;
	return vol;
};