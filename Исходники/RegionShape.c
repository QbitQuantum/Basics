void GenerateBasisLUT()
{
	double	angle, temp, radius;
	int		p, r, x, y;
	int		maxradius;

	maxradius = ART_LUT_RADIUS;

	for(y=0 ; y<ART_LUT_SIZE ; y++)
	for(x=0 ; x<ART_LUT_SIZE ; x++)
	{
		radius = HYPOT(x-maxradius, y-maxradius);
		if(radius < maxradius)
		{
			angle = atan2(y-maxradius, x-maxradius);

			for(p=0 ; p<ART_ANGULAR ; p++)
			for(r=0 ; r<ART_RADIAL ; r++)
			{
				temp = cos(radius*PI*r/maxradius);
				m_pBasisR[p][r][x][y] = temp*cos(angle*p);
				m_pBasisI[p][r][x][y] = temp*sin(angle*p);
			}
		}
		else
		{
			for(p=0 ; p<ART_ANGULAR ; p++)
			for(r=0 ; r<ART_RADIAL ; r++)
			{
				m_pBasisR[p][r][x][y] = 0;
				m_pBasisI[p][r][x][y] = 0;
			}
		}
	}
}