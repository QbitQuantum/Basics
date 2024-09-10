////////////////////////////////////////////////////////////////////////////////////////
// CreateStrips()
//
// Generates actual strips from the list-in-strip-order.
//
void NvStripifier::CreateStrips(const NvStripInfoVec& allStrips, IntVec& stripIndices, 
								const bool bStitchStrips, unsigned int& numSeparateStrips)
{
	assert(numSeparateStrips == 0);

	NvFaceInfo tLastFace(0, 0, 0);
	int nStripCount = allStrips.size();
	assert(nStripCount > 0);

	//we infer the cw/ccw ordering depending on the number of indices
	//this is screwed up by the fact that we insert -1s to denote changing strips
	//this is to account for that
	int accountForNegatives = 0;

	for (int i = 0; i < nStripCount; i++)
	{
		NvStripInfo *strip = allStrips[i];
		int nStripFaceCount = strip->m_faces.size();
		assert(nStripFaceCount > 0);

		// Handle the first face in the strip
		{
			NvFaceInfo tFirstFace(strip->m_faces[0]->m_v0, strip->m_faces[0]->m_v1, strip->m_faces[0]->m_v2);

			// If there is a second face, reorder vertices such that the
			// unique vertex is first
			if (nStripFaceCount > 1)
			{
				int nUnique = NvStripifier::GetUniqueVertexInB(strip->m_faces[1], &tFirstFace);
				if (nUnique == tFirstFace.m_v1)
				{
					SWAP(tFirstFace.m_v0, tFirstFace.m_v1);
				}
				else if (nUnique == tFirstFace.m_v2)
				{
					SWAP(tFirstFace.m_v0, tFirstFace.m_v2);
				}

				// If there is a third face, reorder vertices such that the
				// shared vertex is last
				if (nStripFaceCount > 2)
				{
					int nShared = GetSharedVertex(strip->m_faces[2], &tFirstFace);
					if (nShared == tFirstFace.m_v1)
					{
						SWAP(tFirstFace.m_v1, tFirstFace.m_v2);
					}
				}
			}

			if( (i == 0) || !bStitchStrips)
			{
				if(!IsCW(strip->m_faces[0], tFirstFace.m_v0, tFirstFace.m_v1))
					stripIndices.push_back(tFirstFace.m_v0);
			}
			else
			{
				// Double tap the first in the _new strip
				stripIndices.push_back(tFirstFace.m_v0);
	
				// Check CW/CCW ordering
				if (NextIsCW(stripIndices.size() - accountForNegatives) != IsCW(strip->m_faces[0], tFirstFace.m_v0, tFirstFace.m_v1))
				{
					stripIndices.push_back(tFirstFace.m_v0);
				}
			}

			stripIndices.push_back(tFirstFace.m_v0);
			stripIndices.push_back(tFirstFace.m_v1);
			stripIndices.push_back(tFirstFace.m_v2);

			// Update last face info
			tLastFace = tFirstFace;
		}

		for (int j = 1; j < nStripFaceCount; j++)
		{
			int nUnique = GetUniqueVertexInB(&tLastFace, strip->m_faces[j]);
			if (nUnique != -1)
			{
				stripIndices.push_back(nUnique);

				// Update last face info
				tLastFace.m_v0 = tLastFace.m_v1;
				tLastFace.m_v1 = tLastFace.m_v2;
				tLastFace.m_v2 = nUnique;
			}
		}

		// Double tap between strips.
		if(bStitchStrips)
		{
			if(i != nStripCount - 1)
				stripIndices.push_back(tLastFace.m_v2);
		}
		else
		{
			//-1 index indicates next strip
			stripIndices.push_back(-1);
			accountForNegatives++;
			numSeparateStrips++;
		}

		// Update last face info
		tLastFace.m_v0 = tLastFace.m_v1;
		tLastFace.m_v1 = tLastFace.m_v2;
		tLastFace.m_v2 = tLastFace.m_v2;
	}
	
	if(bStitchStrips)
		numSeparateStrips = 1;
}