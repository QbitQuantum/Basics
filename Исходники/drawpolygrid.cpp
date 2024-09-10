static void GeneratePolyGridFresnelAlphaAndCamera(const LTVector& vViewPos, CPolyGridBumpVertex* pVerts, LTPolyGrid* pGrid, uint32 nNumVerts)
{
	//we need to transform the camera position into our view space
	LTMatrix mInvWorldTrans;

	mInvWorldTrans.Identity();
	mInvWorldTrans.SetTranslation(-pGrid->GetPos());

	LTMatrix mOrientation;
	pGrid->m_Rotation.ConvertToMatrix(mOrientation);

	mInvWorldTrans = mOrientation * mInvWorldTrans;

	LTVector vCameraPos = mInvWorldTrans * vViewPos;

	//now generate the internals of the polygrid
	CPolyGridBumpVertex* pCurrVert	= pVerts;
	CPolyGridBumpVertex* pEnd		= pCurrVert + nNumVerts;

	//determine the fresnel table that we are going to be using
	const CFresnelTable* pTable = g_FresnelCache.GetTable(LTMAX(1.0003f, pGrid->m_fFresnelVolumeIOR), pGrid->m_fBaseReflection);

	//use a vector from the camera to the center of the grid to base our approximations off of. The further
	//we get to the edges the more likely this error will be, but it is better than another sqrt per vert
	LTVector vToPGPt;

	while(pCurrVert < pEnd)
	{
		//the correct but slow way, so only do it every once in a while
		//if((pCurrVert - g_TriVertList) % 4 == 0)
		{
			vToPGPt = vCameraPos - pCurrVert->m_Vec;
			vToPGPt.Normalize();
		}

		pCurrVert->m_fEyeX = vToPGPt.x;
		pCurrVert->m_fEyeY = vToPGPt.y;
		pCurrVert->m_fEyeZ = vToPGPt.z;

		pCurrVert->m_nColor |= pTable->GetValue(vToPGPt.Dot(pCurrVert->m_vBasisUp));
		++pCurrVert;
	}
}