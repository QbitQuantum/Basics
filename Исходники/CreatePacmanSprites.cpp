static void CreatePacmanSprites(CBitmap & _bmOut)
{
	const int iSpriteCount = g_iBitmapSize / g_iSpriteSize;
	const float fMaxMouthAngle = 0.25f * D3DX_PI;
	const float fMouthCenterX = -0.2f;

	for(int iSpriteIndex = 0; iSpriteIndex < iSpriteCount; iSpriteIndex++)
	{
		float fMouthAngle = ((float)iSpriteIndex) * fMaxMouthAngle / (float)(iSpriteCount - 1);

		for(int iRowIndex = 0; iRowIndex < g_iSpriteSize; iRowIndex++)
		{
			for(int iColumnIndex = 0; iColumnIndex < g_iSpriteSize; iColumnIndex++)
			{
				int iInBmpColumnIndex = iColumnIndex + iSpriteIndex * g_iSpriteSize;

				float fNormColumnIndex = ((float)iColumnIndex) / ((float)g_iSpriteSize);
				float fNormRowIndex = ((float)iRowIndex) / ((float)g_iSpriteSize);
				float fX = fNormColumnIndex - 0.5f;
				float fY = fNormRowIndex - 0.5f;
				float fDistance = sqrtf(fX * fX + fY * fY);

				bool bColored = fDistance <= 0.5f;

				if(bColored && (fX >= fMouthCenterX))
				{
					float fAngle = fabsf(atanf(fY / (fX - fMouthCenterX)));

					bColored = fAngle >= fMouthAngle;
				}

				if (bColored)
				{
					_bmOut.SetPixel(iRowIndex, iInBmpColumnIndex, g_dwSpriteColor);
				}
			}
		}
	}
}