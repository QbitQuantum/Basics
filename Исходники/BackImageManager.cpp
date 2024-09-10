float CBackImageManager::GetRatioCamera( float fFov, int nWidth, int nHeight )
{
	eRATIO eRatio = GetRatio(nWidth, nHeight);

	float fTan = fFov * 0.5f;	// eRATIO_16_10

	int nResolutionIdx = GetResolutionIndex();

	float fDis = DEF_CAMERA_DISTANCE;
		
	if (eRatio == eRATIO_4_3)
		fDis = DEF_CAMERA_DISTANCE_4_3;
	if (eRatio == eRATIO_5_4)
		fDis = DEF_CAMERA_DISTANCE_5_4;

	float fl = 8.f + (fDis / Tan(fTan));

	return fl;
}