void animate()
{
	float mx;
	float my;
	if(ManualControl)
	{
		POINT pos;
		GetCursorPos(&pos);
		RECT rc;
		GetClientRect(hMainWnd, &rc);
		ScreenToClient(hMainWnd, &pos);

		mx = pos.x;
		my = pos.y;
	}
	else
	{
		UpdatePosition(mx, my);
	}


	const auto size = partCount;

	VertexData *pVertexBuffer;
	pVertexObject->Lock(0, 0, (void**)&pVertexBuffer, D3DLOCK_DISCARD);

	_mm256_zeroall();

#pragma omp parallel \
	shared(pVertexBuffer, particlesCoord, particlesVel, mx, my, size)
	{
#pragma omp for nowait
		for(int i = 0; i < size; i += 4)
		{
			float mouseCoordVec[8] = { mx, my, mx, my, mx, my, mx, my };

			float *particleCoordsVec = (float*)particlesCoord + i;
			float *velocityVec = (float*)particlesVel + i;

			auto xyCoord = _mm256_loadu_ps(particleCoordsVec);
			auto hwTempData = _mm256_sub_ps(xyCoord, _mm256_loadu_ps(mouseCoordVec));

			auto squares = _mm256_mul_ps(hwTempData, hwTempData);
			auto distSquare = _mm256_hadd_ps(squares, squares);
			distSquare = _mm256_shuffle_ps(distSquare, distSquare, 0x50);

			auto theForce = _mm256_div_ps(_mm256_set1_ps(G), distSquare);

			if(distSquare.m256_f32[0] < 400)
			{
				theForce.m256_f32[0] = 0;
				theForce.m256_f32[1] = 0;
			}

			if(distSquare.m256_f32[2] < 400)
			{
				theForce.m256_f32[2] = 0;
				theForce.m256_f32[3] = 0;
			}
			if(distSquare.m256_f32[4] < 400)
			{
				theForce.m256_f32[4] = 0;
				theForce.m256_f32[5] = 0;
			}

			if(distSquare.m256_f32[6] < 400)
			{
				theForce.m256_f32[6] = 0;
				theForce.m256_f32[7] = 0;
			}

			auto xyForces = _mm256_mul_ps(_mm256_xor_ps(hwTempData, _mm256_set1_ps(-0.f)), theForce);

			auto xyVelocities = _mm256_loadu_ps(velocityVec);
			xyVelocities = _mm256_mul_ps(xyVelocities, _mm256_set1_ps(Resistance));
			xyVelocities = _mm256_add_ps(xyVelocities, xyForces);

			xyCoord = _mm256_add_ps(xyCoord, xyVelocities);

			_mm256_storeu_ps(velocityVec, xyVelocities);
			_mm256_storeu_ps(particleCoordsVec, xyCoord);


			processIfOutOfBounds(((ParticleCoord*)particleCoordsVec)[0], ((ParticleVel*)velocityVec)[0]);
			processIfOutOfBounds(((ParticleCoord*)particleCoordsVec)[1], ((ParticleVel*)velocityVec)[1]);
			processIfOutOfBounds(((ParticleCoord*)particleCoordsVec)[2], ((ParticleVel*)velocityVec)[2]);
			processIfOutOfBounds(((ParticleCoord*)particleCoordsVec)[3], ((ParticleVel*)velocityVec)[3]);

			pVertexBuffer[i].x = ((ParticleCoord*)particleCoordsVec)[0].x;
			pVertexBuffer[i].y = ((ParticleCoord*)particleCoordsVec)[0].y;
			pVertexBuffer[i + 1].x = ((ParticleCoord*)particleCoordsVec)[1].x;
			pVertexBuffer[i + 1].y = ((ParticleCoord*)particleCoordsVec)[1].y;
			pVertexBuffer[i + 2].x = ((ParticleCoord*)particleCoordsVec)[2].x;
			pVertexBuffer[i + 2].y = ((ParticleCoord*)particleCoordsVec)[2].y;
			pVertexBuffer[i + 3].x = ((ParticleCoord*)particleCoordsVec)[3].x;
			pVertexBuffer[i + 3].y = ((ParticleCoord*)particleCoordsVec)[3].y;
		}
	}
	pVertexObject->Unlock();

	_mm256_zeroall();
}