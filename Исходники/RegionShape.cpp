//Y表示照片的指针
void ExtractCoefficients(unsigned char *Y, double m_Coeff[ART_ANGULAR][ART_RADIAL], unsigned char *Edge, double CenX, double CenY)
{
	int				x, y, ix, iy;
	int				p, r;
	double			dx, dy, tx, ty, x1, x2;
	int				count;
	double			m_pCoeffR[ART_ANGULAR][ART_RADIAL];
	double			m_pCoeffI[ART_ANGULAR][ART_RADIAL];
//	double			norm;

	unsigned char *pImage;
//	unsigned char *pEdge;

	memset(m_pCoeffR, 0, ART_ANGULAR * ART_RADIAL * sizeof(double) );
	memset(m_pCoeffI, 0, ART_ANGULAR * ART_RADIAL * sizeof(double) );
//	for(p=0 ; p<ART_ANGULAR ; p++)
//	for(r=0 ; r<ART_RADIAL ; r++)
//	{
//		m_pCoeffR[p][r] = 0;
//		m_pCoeffI[p][r] = 0;
//	}

	count = 0;
	pImage = Y;
//	pEdge = Edge;
	for (y=0 ; y<HEIGHT ; y++)
	for (x=0 ; x<WIDTH; x++)
	{
//		if( *pImage < 127 )
		if( *pImage < 255 )
		{
			// 1.0 is for silhouette, another one is for depth, both weighting is 0.5
			// both depth and silhouette
//			norm = (1.0 + (255.0-*pImage) / 255.0) / 2;
			// depth only
//			norm = (255.0-*pImage) / 255.0;
			// silhouette only
//			norm = 1.0;
			// edge (from depth) only
//			norm = *pEdge / 255.0;
			// edge (from depth) + depth + silhouette
//			norm = (*pEdge/255.0 + (255.0-*pImage)/255.0 + 1.0) / 3;
			// edge (from silhouette) only
//			norm = 1.0;
			// edge (from silhouette) + silhouette
//			norm = (255.0-*pImage) / 255.0;

			// map image coordinate (x,y) to basis function coordinate (tx,ty)
//			dx = x - CENTER_X;
//			dy = y - CENTER_Y;
			dx = x - CenX;
			dy = y - CenY;
			tx = dx * r_radius + ART_LUT_RADIUS;//r_radius由上一个函数计算
			ty = dy * r_radius + ART_LUT_RADIUS;//为什么要加上50的ART_LUT_RADIUS，因为dx是负的
			ix = (int)tx;
			iy = (int)ty;
			dx = tx - ix;//dx表示小数部分，为啥要小数，用来干嘛？
			dy = ty - iy;

			//这里即通过分割地方法来近似积分
			// summation of basis function
//			if(tx >= 0 && tx < ART_LUT_SIZE && ty >= 0 && ty < ART_LUT_SIZE)
			for(p=0 ; p<ART_ANGULAR ; p++)
			for(r=0 ; r<ART_RADIAL ; r++)
			{
				// GetReal (if call function, the speed will be very slow)
				// m_pCoeffR[p][r] += GetReal(p, r, tx, ty);
				x1 = m_pBasisR[p][r][ix][iy] + (m_pBasisR[p][r][ix+1][iy]-m_pBasisR[p][r][ix][iy]) * dx;
				x2 = m_pBasisR[p][r][ix][iy+1] + (m_pBasisR[p][r][ix+1][iy+1]-m_pBasisR[p][r][ix][iy+1]) * dx;
//				m_pCoeffR[p][r] += norm * (x1 + (x2-x1) * dy);
				m_pCoeffR[p][r] += (x1 + (x2-x1) * dy);

				// GetImg (if call function, the speed will be very slow)
				// m_pCoeffI[p][r] -= GetImg(p, r, tx, ty);
				x1 = m_pBasisI[p][r][ix][iy] + (m_pBasisI[p][r][ix+1][iy]-m_pBasisI[p][r][ix][iy]) * dx;
				x2 = m_pBasisI[p][r][ix][iy+1] + (m_pBasisI[p][r][ix+1][iy+1]-m_pBasisI[p][r][ix][iy+1]) * dx;
//				m_pCoeffI[p][r] -= norm * (x1 + (x2-x1) * dy);
				m_pCoeffI[p][r] -= (x1 + (x2-x1) * dy);
			}

			count ++;		// how many pixels
		}
		pImage++;
//		pEdge++;
	}

	// if the 3D model is flat, some camera will render nothing, so count=0 in this case
	if( count > 0 )
	{
		for(p=0 ; p<ART_ANGULAR ; p++)
		for(r=0 ; r<ART_RADIAL ; r++)
			m_Coeff[p][r] = HYPOT( m_pCoeffR[p][r]/count, m_pCoeffI[p][r]/count );

		// normalization
		for(p=0 ; p<ART_ANGULAR ; p++)
		for(r=0 ; r<ART_RADIAL ; r++)
			m_Coeff[p][r] /= m_Coeff[0][0];
			
	}
	else
	{
		// if didn't add this, the result will also be saved as 0
		for(p=0 ; p<ART_ANGULAR ; p++)
		for(r=0 ; r<ART_RADIAL ; r++)
			m_Coeff[p][r] = 0.0;
		// use a line to test the number to approximate
/*		for(p=0 ; p<ART_ANGULAR ; p++)
		for(r=0 ; r<ART_RADIAL ; r++)
			m_Coeff[p][r] = 0.010256410;
		for(p=0 ; p<ART_ANGULAR ; p+=2)
			m_Coeff[p][0] = 0.980129780;*/
	}
}