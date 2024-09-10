inline void Flow2D::BackTrace(Int2 Plaquette[2], float Weights[4], const int index)
{
	int iX = index % m_Nx;
	int iY = index / m_Nx;
	int indexFull = GetIndexFull(iX, iY);
	
	float fBackPtX = float(iX) - m_TmpVel.x.aligned[indexFull] * m_dtime;
	float fBackPtY = float(iY) - m_TmpVel.y.aligned[indexFull] * m_dtime;

	if (fBackPtX < 0.0f) {
		fBackPtX = m_Nx-1 + fmodf(fBackPtX, (float)m_Nx);
	} else if (fBackPtX >= m_Nx) {
		fBackPtX = fmodf(fBackPtX, (float)m_Nx);
	}

	if (fBackPtY < 0.0f) {
		fBackPtY = m_Ny-1 + fmodf(fBackPtY, (float)m_Ny);
	} else if (fBackPtY >= m_Ny) {
		fBackPtY = fmodf(fBackPtY, (float)m_Ny); 
	}

	float fdx,fdy; 
	float fidx, fidy;

	fdx	= modff(fBackPtX ,&(fidx));
	fdy	= modff(fBackPtY, &(fidy));

	// Set Sites Co On A Plaquette
	Plaquette[0].x =  (int)fidx;
	Plaquette[0].y =  (int)fidy;

	//right
	if (Plaquette[0].x == m_Nx - 1) {
		Plaquette[1].x = 0;
	} else { 
		Plaquette[1].x = Plaquette[0].x+ 1;
	}
	//top
	if (Plaquette[0].y == m_Ny - 1) {
		Plaquette[1].y = 0;
	} else {
		Plaquette[1].y = Plaquette[0].y + 1;
	}
	
	Weights[3] = fdx * fdy;
	Weights[2] = fdy - Weights[3];
	Weights[1] = fdx - Weights[3];
	Weights[0] = 1.0f - Weights[1] - fdy;
}