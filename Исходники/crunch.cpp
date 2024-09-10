void CTexelDiffuseMethod::GenerateTexel(size_t iTexel, CConversionMeshInstance* pMeshInstance, CConversionFace* pFace, CConversionVertex* pV1, CConversionVertex* pV2, CConversionVertex* pV3, raytrace::CTraceResult* tr, const Vector& vecUVPosition, raytrace::CRaytracer* pTracer)
{
	CConversionFace* pHitFace = tr->m_pMeshInstance->GetMesh()->GetFace(tr->m_iFace);
	CTexture& oTexture = m_aTextures[tr->m_pMeshInstance->GetMappedMaterial(pHitFace->m)->m_iMaterial];

	if (!oTexture.m_pclrData)
		return;

	CConversionMesh* pHitMesh = tr->m_pMeshInstance->GetMesh();

	// TODO: Use the nearest triangle in this face.
	CConversionVertex* pHitV1 = pHitFace->GetVertex(0);
	CConversionVertex* pHitV2 = pHitFace->GetVertex(1);
	CConversionVertex* pHitV3 = pHitFace->GetVertex(2);

	Vector2D vu1 = pHitMesh->GetUV(pHitV1->vu);
	Vector2D vu2 = pHitMesh->GetUV(pHitV2->vu);
	Vector2D vu3 = pHitMesh->GetUV(pHitV3->vu);

	Vector v1 = tr->m_pMeshInstance->GetVertex(pHitV1->v);
	Vector v2 = tr->m_pMeshInstance->GetVertex(pHitV2->v);
	Vector v3 = tr->m_pMeshInstance->GetVertex(pHitV3->v);

	// Find where the world point is in UV space.

	// First convert to barycentric coordinates.
	Vector u = v2 - v1;
	Vector v = v3 - v1;
	float uu = u.Dot(u);
	float uv = u.Dot(v);
	float vv = v.Dot(v);
	Vector w = tr->m_vecHit - v1;
	float wu = w.Dot(u);
	float wv = w.Dot(v);

	float D = uv * uv - uu * vv;

	float b1, b2, b3;

	b1 = (uv * wu - uu * wv) / D;
	b2 = (uv * wv - vv * wu) / D;
	b3 = 1 - b1 - b2;

	// The position of the traceline's hit in (u, v) texture space
	Vector2D vecWorldPosition = vu1 * b1 + vu2 * b2 + vu3 * b3;

	// Mutex may be dead, try to bail before.
	if (m_pGenerator->IsStopped())
		return;

	size_t iU = (size_t)((vecWorldPosition.x * oTexture.m_iWidth) - 0.5f);
	size_t iV = (size_t)((vecWorldPosition.y * oTexture.m_iHeight) - 0.5f);

	iU %= oTexture.m_iWidth;
	iV %= oTexture.m_iHeight;

	size_t iColorTexel;
	m_pGenerator->Texel(iU, iV, iColorTexel, oTexture.m_iWidth, oTexture.m_iHeight);

	Color clrData = oTexture.m_pclrData[iColorTexel];

	m_pGenerator->GetParallelizer()->LockData();

	m_avecDiffuseValues[iTexel] += Vector(clrData);
	m_aiDiffuseReads[iTexel]++;
	m_pGenerator->MarkTexelUsed(iTexel);

	m_pGenerator->GetParallelizer()->UnlockData();
}