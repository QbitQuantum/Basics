///////////////////////////////////////////////////////////////////
// Scissor rectangle of water patches
CBoundingBoxAligned TerrainRenderer::ScissorWater(const CMatrix3D &viewproj)
{
	CBoundingBoxAligned scissor;
	for (size_t i = 0; i < m->visiblePatches.size(); ++i)
	{
		CPatchRData* data = m->visiblePatches[i];
		const CBoundingBoxAligned& waterBounds = data->GetWaterBounds();
		if (waterBounds.IsEmpty())
			continue;

		CVector4D v1 = viewproj.Transform(CVector4D(waterBounds[0].X, waterBounds[1].Y, waterBounds[0].Z, 1.0f));
		CVector4D v2 = viewproj.Transform(CVector4D(waterBounds[1].X, waterBounds[1].Y, waterBounds[0].Z, 1.0f));
		CVector4D v3 = viewproj.Transform(CVector4D(waterBounds[0].X, waterBounds[1].Y, waterBounds[1].Z, 1.0f));
		CVector4D v4 = viewproj.Transform(CVector4D(waterBounds[1].X, waterBounds[1].Y, waterBounds[1].Z, 1.0f));
		CBoundingBoxAligned screenBounds;
		#define ADDBOUND(v1, v2, v3, v4) \
			if (v1[2] >= -v1[3]) \
				screenBounds += CVector3D(v1[0], v1[1], v1[2]) * (1.0f / v1[3]); \
			else \
			{ \
				float t = v1[2] + v1[3]; \
				if (v2[2] > -v2[3]) \
				{ \
					CVector4D c2 = v1 + (v2 - v1) * (t / (t - (v2[2] + v2[3]))); \
					screenBounds += CVector3D(c2[0], c2[1], c2[2]) * (1.0f / c2[3]); \
				} \
				if (v3[2] > -v3[3]) \
				{ \
					CVector4D c3 = v1 + (v3 - v1) * (t / (t - (v3[2] + v3[3]))); \
					screenBounds += CVector3D(c3[0], c3[1], c3[2]) * (1.0f / c3[3]); \
				} \
				if (v4[2] > -v4[3]) \
				{ \
					CVector4D c4 = v1 + (v4 - v1) * (t / (t - (v4[2] + v4[3]))); \
					screenBounds += CVector3D(c4[0], c4[1], c4[2]) * (1.0f / c4[3]); \
				} \
			}
		ADDBOUND(v1, v2, v3, v4);
		ADDBOUND(v2, v1, v3, v4);
		ADDBOUND(v3, v1, v2, v4);
		ADDBOUND(v4, v1, v2, v3);
		#undef ADDBOUND
		if (screenBounds[0].X >= 1.0f || screenBounds[1].X <= -1.0f || screenBounds[0].Y >= 1.0f || screenBounds[1].Y <= -1.0f)
			continue;
		scissor += screenBounds;
	}
	return CBoundingBoxAligned(CVector3D(clamp(scissor[0].X, -1.0f, 1.0f), clamp(scissor[0].Y, -1.0f, 1.0f), -1.0f),
				  CVector3D(clamp(scissor[1].X, -1.0f, 1.0f), clamp(scissor[1].Y, -1.0f, 1.0f), 1.0f));
}