//--------------------------------------------------------------------------------------------------
// Name: ValidateExtractedOutline
// Desc: Performs a final validation pass on the extracted outline
//--------------------------------------------------------------------------------------------------
bool CBreakableGlassSystem::ValidateExtractedOutline(SBreakableGlassPhysData& data, SBreakableGlassInitParams& initParams)
{
	bool valid = true;

	// Check for overlapping points (leads to FPE during triangulation)
	if (initParams.pInitialFrag && initParams.numInitialFragPts > 0)
	{
		const Vec2* pPts = initParams.pInitialFrag;
		const uint numEdges = initParams.numInitialFragPts-1;
		const float minEdgeLen = 0.0001f;

		for (uint i = 0, j = 1; i < numEdges; ++i, ++j)
		{
			const Vec2 edge(pPts[i] - pPts[j]);

			if (edge.GetLength2() < minEdgeLen)
			{
				LOG_GLASS_ERROR("Extracted mesh has invalid edges.");

				valid = false;
				break;
			}
		}
	}

	// Check for overlapping UVs (leads to FPE during uv basis calculation)
	if (valid)
	{
		const Vec2 uvPtA(data.uvBasis[0].x, data.uvBasis[0].y);
		const Vec2 uvPtB(data.uvBasis[1].x, data.uvBasis[1].y);
		const Vec2 uvPtC(data.uvBasis[2].x, data.uvBasis[2].y);

		const Vec2 uvEdge0(uvPtC - uvPtA);
		const Vec2 uvEdge1(uvPtB - uvPtA);

		const float dot00 = uvEdge0.Dot(uvEdge0);
		const float dot01 = uvEdge0.Dot(uvEdge1);
		const float dot11 = uvEdge1.Dot(uvEdge1);
		const float epsilon = 0.001f;

		if (fabs_tpl(dot00 * dot11 - dot01 * dot01) < epsilon)
		{
			LOG_GLASS_ERROR("Extracted mesh has invalid uv layout.");
			valid = false;
		}
	}

	return valid;
}//-------------------------------------------------------------------------------------------------