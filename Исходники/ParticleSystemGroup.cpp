//function that handles the custom rendering
void CParticleSystemGroup::RenderParticleSystem(ILTCustomRenderCallback* pInterface, const LTRigidTransform& tCamera)
{
	//track our performance
	CTimedSystemBlock TimingBlock(g_tsClientFXParticles);

	//setup our vertex declaration
	if(pInterface->SetVertexDeclaration(g_ClientFXVertexDecl.GetTexTangentSpaceDecl()) != LT_OK)
		return;

	//bind a quad index stream
	if(pInterface->BindQuadIndexStream() != LT_OK)
		return;

	//set the fact that we were visible
	*m_pVisibleFlag = true;

	//now determine the largest number of particles that we can render at any time
	uint32 nMaxParticlesPerBatch = QUAD_RENDER_INDEX_STREAM_SIZE / 6;
	nMaxParticlesPerBatch = LTMIN(nMaxParticlesPerBatch, DYNAMIC_RENDER_VERTEX_STREAM_SIZE / (sizeof(STexTangentSpaceVert) * 4));

	//determine the screen orientation
	LTRotation rCamera = tCamera.m_rRot;

	if (m_pProps->m_bObjectSpace)
	{
		LTRotation rObjectRotation;
		g_pLTClient->GetObjectRotation(m_hCustomRender, &rObjectRotation);
		rCamera = rObjectRotation.Conjugate() * rCamera;
	}

	LTVector vUp = rCamera.Up();
	LTVector vRight = rCamera.Right();

	//create some vectors to offset to each corner (avoids adding for displacement in the inner loop)
	//Each one can just be scaled by the size of the particle to get the final offset
	static const float kfHalfRoot2 = 0.5f * MATH_SQRT2;

	//premultiplied versions of up and right scaled by half the square root of two
	LTVector vUpHalfRoot2 = vUp * kfHalfRoot2;
	LTVector vRightHalfRoot2 = vRight * kfHalfRoot2;

	//precalculate the diagonals for non-rotating particles since these are constant
	LTVector vDiagonals[4];
	vDiagonals[0] =  vUpHalfRoot2 - vRightHalfRoot2; 
	vDiagonals[1] =  vUpHalfRoot2 + vRightHalfRoot2; 
	vDiagonals[2] = -vUpHalfRoot2 + vRightHalfRoot2; 
	vDiagonals[3] = -vUpHalfRoot2 - vRightHalfRoot2; 

	uint32 nNumParticlesLeft = m_Particles.GetNumParticles();

	//precalculate some data for the basis space of the particles
	LTVector	vNormal		= -rCamera.Forward();
	LTVector	vTangent	= vRight;
	LTVector	vBinormal	= -vUp;

	//the U scale for particle images
	float		fUImageWidth = 1.0f / (float)m_pProps->m_nNumImages;

	//variables used within the inner loop
	float		fSize;
	uint32		nColor;

	//now run through all the particles and render
	CParticleIterator itParticles = m_Particles.GetIterator();
	while(nNumParticlesLeft > 0)
	{
		//determine our batch size
		uint32 nBatchSize = LTMIN(nNumParticlesLeft, nMaxParticlesPerBatch);

		//lock down our buffer for rendering
		SDynamicVertexBufferLockRequest LockRequest;
		if(pInterface->LockDynamicVertexBuffer(nBatchSize * 4, LockRequest) != LT_OK)
			return;

		//fill in a batch of particles
		STexTangentSpaceVert* pCurrOut = (STexTangentSpaceVert*)LockRequest.m_pData;

		if(m_pProps->m_bRotate)
		{
			//we need to render the particles rotated
			for(uint32 nBatchParticle = 0; nBatchParticle < nBatchSize; nBatchParticle++)
			{
				//sanity check
				LTASSERT(!itParticles.IsDone(), "Error: Particle count and iterator mismatch");

				//get the particle from the iterator
				SParticle* pParticle = (SParticle*)itParticles.GetParticle();

				GetParticleSizeAndColor(pParticle, nColor, fSize);

				//determine the sin and cosine of this particle angle
				float fAngle = pParticle->m_fAngle;
				float fSinAngle = LTSin(fAngle);
				float fCosAngle = LTCos(fAngle);

				LTVector vRotRight = (vRightHalfRoot2 * fCosAngle + vUpHalfRoot2 * fSinAngle) * fSize;
				LTVector vRotUp    = vNormal.Cross(vRotRight);

				LTVector vRotTangent  = vTangent * fCosAngle + vBinormal * fSinAngle;
				LTVector vRotBinormal = vTangent * fSinAngle + vBinormal * fCosAngle;

				SetupParticle(	pCurrOut, 
					pParticle->m_Pos + vRotUp - vRotRight,
					pParticle->m_Pos + vRotUp + vRotRight,
					pParticle->m_Pos - vRotUp + vRotRight,
					pParticle->m_Pos - vRotUp - vRotRight,
					nColor, vNormal, vRotTangent, vRotBinormal, 
					pParticle->m_nUserData & PARTICLE_IMAGE_MASK, fUImageWidth);

				//move onto the next set of particles
				pCurrOut += 4;

				//move onto the next particle for processing
				itParticles.Next();
			}
		}
		else if (m_pProps->m_bStreak)
		{
			//the particles are non-rotated but streaked along their velocity
			for(uint32 nBatchParticle = 0; nBatchParticle < nBatchSize; nBatchParticle++)
			{
				//sanity check
				LTASSERT(!itParticles.IsDone(), "Error: Particle count and iterator mismatch");

				//get the particle from the iterator
				SParticle* pParticle = (SParticle*)itParticles.GetParticle();

				GetParticleSizeAndColor(pParticle, nColor, fSize);

				//in order to render the streak, we determine a line that passes through
				//the particle and runs in the direction of the velocity of the particle

				//we need to project the velocity onto the screen
				LTVector2 vScreen;
				vScreen.x = -(pParticle->m_Velocity.Dot(vRight));
				vScreen.y = -(pParticle->m_Velocity.Dot(vUp));

				//we know that the up and right vectors are normalized, so we can save some work by
				//just doing a 2d normalization
				float fMag = vScreen.Mag();
				if(fMag == 0.0f)
					vScreen.Init(fSize, 0.0f);
				else
					vScreen *= fSize / fMag;

				//determine our actual screen space velocity
				LTVector vScreenRight = vUp * vScreen.y + vRight * vScreen.x;
				LTVector vScreenUp = vUp * -vScreen.x + vRight * vScreen.y;

				//and now compute the endpoint of the streak
				LTVector vEndPos = pParticle->m_Pos - pParticle->m_Velocity * m_pProps->m_fStreakScale;

				SetupParticle(	pCurrOut, 
					pParticle->m_Pos	- vScreenRight - vScreenUp,
					vEndPos				+ vScreenRight - vScreenUp,
					vEndPos				+ vScreenRight + vScreenUp,
					pParticle->m_Pos	- vScreenRight + vScreenUp,
					nColor, vNormal, vScreenRight, vScreenUp, 
					pParticle->m_nUserData & PARTICLE_IMAGE_MASK, fUImageWidth);

				//move onto the next set of particles
				pCurrOut += 4;

				//move onto the next particle for processing
				itParticles.Next();
			}
		}
		else
		{
			//the particles are non-rotated
			for(uint32 nBatchParticle = 0; nBatchParticle < nBatchSize; nBatchParticle++)
			{
				//sanity check
				LTASSERT(!itParticles.IsDone(), "Error: Particle count and iterator mismatch");

				//get the particle from the iterator
				SParticle* pParticle = (SParticle*)itParticles.GetParticle();

				GetParticleSizeAndColor(pParticle, nColor, fSize);

				SetupParticle(	pCurrOut, 
					pParticle->m_Pos + vDiagonals[0] * fSize,
					pParticle->m_Pos + vDiagonals[1] * fSize,
					pParticle->m_Pos + vDiagonals[2] * fSize,
					pParticle->m_Pos + vDiagonals[3] * fSize,
					nColor, vNormal, vTangent, vBinormal, 
					pParticle->m_nUserData & PARTICLE_IMAGE_MASK, fUImageWidth);

				//move onto the next set of particles
				pCurrOut += 4;

				//move onto the next particle for processing
				itParticles.Next();
			}
		}

		//unlock and render the batch
		pInterface->UnlockAndBindDynamicVertexBuffer(LockRequest);
		pInterface->RenderIndexed(	eCustomRenderPrimType_TriangleList, 
			0, nBatchSize * 6, LockRequest.m_nStartIndex, 
			0, nBatchSize * 4);

		nNumParticlesLeft -= nBatchSize;
	}
}