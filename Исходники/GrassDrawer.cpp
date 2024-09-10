void CGrassDrawer::DrawFarBillboards(const std::vector<GrassStruct*>& inviewFarGrass)
{
	// update far grass blocks
	if (updateBillboards) {
		updateBillboards = false;

		for_mt(0, inviewFarGrass.size(), [&](const int i){
			GrassStruct& g = *inviewFarGrass[i];
			if (!g.va) {
				//TODO vertex arrays need to be send each frame to the gpu, that's slow. switch to VBOs.
				CVertexArray* va = new CVertexArray;
				g.va = va;
				g.lastDist = -1; // force a recreate
			}

			const float distSq = GetCamDistOfGrassBlock((g.posX + 0.5f) * grassBlockSize, (g.posZ + 0.5f) * grassBlockSize, true);
			if (distSq == g.lastDist)
				return;

			bool inAlphaRange1 = (    distSq < Square(maxDetailedDist + 128.f * 1.5f)) || (    distSq > Square(maxGrassDist - 128.f));
			bool inAlphaRange2 = (g.lastDist < Square(maxDetailedDist + 128.f * 1.5f)) || (g.lastDist > Square(maxGrassDist - 128.f));
			if (!inAlphaRange1 && (inAlphaRange1 == inAlphaRange2)) {
				return;
			}

			g.lastDist = distSq;
			CVertexArray* va = g.va;
			va->Initialize();

			for (int y2 = g.posZ * grassBlockSize; y2 < (g.posZ + 1) * grassBlockSize; ++y2) {
				for (int x2 = g.posX * grassBlockSize; x2 < (g.posX  + 1) * grassBlockSize; ++x2) {
					if (!grassMap[y2 * mapDims.mapx / grassSquareSize + x2]) {
						continue;
					}

					const float dist = GetCamDistOfGrassBlock(x2, y2);
					auto* va_tn = va->GetTypedVertexArray<VA_TYPE_TN>(numTurfs * 4);
					DrawBillboard(x2, y2, dist, va_tn);
				}
			}
		});
	}

	// render far grass blocks
	for (const GrassStruct* g: inviewFarGrass) {
		g->va->DrawArrayTN(GL_QUADS);
	}
}