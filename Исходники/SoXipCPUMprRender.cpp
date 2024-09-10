void	computeMPRCacheLUT(SoXipCPUMprRender *mprRender, T *volBuf, SoState *state)
{
	// Clear the contents of the mpr buffer
	memset(mprRender->mMPRBuf, 0, (int)mprRender->mMPRSize[0] * (int)mprRender->mMPRSize[1] * sizeof(float) * 4);

	// Get some constant sizes ready
	const int volWidth = mprRender->mVolDim[0];
	const int volHeight = mprRender->mVolDim[1];
	const int volDepth = mprRender->mVolDim[2];
	const int volSliceSize = volWidth * volHeight;
	const float boundX = volWidth - 1.0f;
	const float boundY = volHeight - 1.0f;
	const float boundZ = volDepth - 1.0f;

	// Get bounding box span and start from model matrix
	SbMatrix modelMat = SoModelMatrixElement::get(state);
	SbVec3f wSpan, wStart;
	SbRotation dummy;
	modelMat.getTransform(wStart, dummy, wSpan, dummy);

	SbMatrix inv = modelMat.inverse();

	// Convert the corner points from worldspace to model space
	SbVec3f	corners[4];
	short i;
	for (i = 0; i < 4; ++i)
	{
		inv.multVecMatrix( mprRender->mCorners[i], corners[i] );
		corners[i][0] *= boundX;
		corners[i][1] *= boundY;
		corners[i][2] *= boundZ;

	}

	SbVec3f vGrad1((corners[0] - corners[3]) / (mprRender->mMPRSize[1] - 1.0f));
	SbVec3f vGrad2((corners[1] - corners[2]) / (mprRender->mMPRSize[1] - 1.0f));
	SbVec3f vIntrp1 = corners[3];
	SbVec3f vIntrp2 = corners[2];
	
	SbVec3f hGrad;
	SbVec3f pos;

	// Prepare data cache stuff
	float neighboursVol[8];
	int	lastBaseOffsetVol = -1;	
	
	int bitRatio = (int)(powf(2, sizeof(T) * 8) / powf(2, mprRender->mVolBitsUsed));
	//
	mprCacheElem *cacheElem = mprRender->mMPRCache;
	float *mprVal = (float*) mprRender->mMPRBuf;

	for (i = 0; i < mprRender->mMPRSize[1]; ++i)
	{
		hGrad = (vIntrp2 - vIntrp1) / (mprRender->mMPRSize[0] - 1.0f);
		pos = vIntrp1;
		for (short j = 0; j < mprRender->mMPRSize[0]; ++j)
		{
			// Check if coord is out of bounds
			if (pos[0] >= 0 && pos[0] < boundX &&
				pos[1] >= 0 && pos[1] < boundY &&
				pos[2] >= 0 && pos[2] < boundZ)
			{

				cacheElem->volCoord[0] = pos[0];
				cacheElem->volCoord[1] = pos[1];
				cacheElem->volCoord[2] = pos[2];

				T val = (T)(sample3Di(volBuf, cacheElem->volCoord, volWidth, volSliceSize, neighboursVol, lastBaseOffsetVol) * bitRatio);

				sampleLut(mprVal, val, mprRender->mLutBuf, mprRender->mLutSize);
				
				cacheElem->mprOffset = mprVal - (float*) mprRender->mMPRBuf;
				cacheElem++;
			}
			mprVal += 4;
			pos += hGrad;
		}
		vIntrp1 += vGrad1;
		vIntrp2 += vGrad2;
	}
	mprRender->mNumCacheElems = cacheElem - mprRender->mMPRCache;
}