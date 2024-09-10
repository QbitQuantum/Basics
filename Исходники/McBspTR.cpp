///////////////////////////////////////////////////////////////////////////////
//		_Direct_lighting
// Calculate the radiance directly come from light sources
///////////////////////////////////////////////////////////////////////////////
CCol4 CMcBspTR::_Direct_lighting (const CVec3 &vPos, const CVec3 &vNml,
								  const CVec3 &vView, const CVec3 &vTex,
								  int PID)
{
	int l;
	TBspRay ray;
	TBspCross crs;
	CBspMaterial *pm;
	CCol4 cRsl = COLOR_BLACK;

	pm = &m_pMaterials[m_pTriangles[PID].GetMaterialID()];

	if (m_bDirectionalLight)
	{
		ray.vOrg = vPos;
		ray.vDir = m_vLightDir;
		ray.vEnd = ray.vOrg + ray.vDir * m_fSceneSize;

		if (ray.vDir.Dot(vNml) < 0.f)	return cRsl;

		int PID2 = PID;
		if (_RayTreeIntersect (ray, crs, PID2))
		{
			if (!_Is_light_patch(PID2)) return cRsl;
			cRsl =  G_theSahder.PhongShading (m_cLightColor, ray.vDir,
				vView*(-1), vPos, vNml, vTex.at(0), vTex.at(1), pm);
		}
		return cRsl;
	}

	for (l = 0; l < m_nLigPatches; l ++)
	{
		//---------------------------------------------------------------------
		// construct a ray point to a random point on the selected light patch
		//---------------------------------------------------------------------
		CBspTriangle *tri = &m_pTriangles[m_tpLigPatches[l].nTID];
		ray.vEnd = tri->Random_point_on_the_triangle();
		ray.vOrg = vPos;
		ray.vDir = ray.vEnd - vPos;
		ray.vDir.Normalize();
		ray.vEnd += ray.vDir; // extend the ray a little bit

		//---------------------------------------------------------------------
		// If the patch does not facing the light patch or the light patch dose
		// not facing the patch, return black;
		//---------------------------------------------------------------------
		if (ray.vDir.Dot(vNml) < 0.f) continue;
		float fDirectionalScale = m_tpLigPatches[l].vNml.Dot(ray.vDir);
		if (fDirectionalScale > 0.f) continue;
		else fDirectionalScale = -fDirectionalScale;

		//---------------------------------------------------------------------
		// Check if the light is occluded by another patch
		// Calculate the shading by phong model if is lit
		//---------------------------------------------------------------------
		int PID2 = PID;
		if (_RayTreeIntersect (ray, crs, PID2))
		{
			if (PID2 == m_tpLigPatches[l].nTID)
			{
				// Calculate the lighting intensity according to the the
				// distance and the intensity of the light patch.
				CVec3 vTemp = crs.vPos - vPos;
				//float fTemp = vTemp.Dot(vTemp) * 4 * PI;
				float fTemp = vTemp.Dot(vTemp) * PI;
				CCol4 cIntensity =
					m_tpLigPatches[l].cEnergy * fDirectionalScale / fTemp;

				// Shading computation by Phong model.
				cRsl += G_theSahder.PhongShading (cIntensity, ray.vDir,
					vView*(-1), vPos, vNml, vTex[0], vTex[1], pm);
			}
		}
	}

	return cRsl;
}