void CLargeBeamLaserProjectile::Draw()
{
	inArray = true;

	const float3 cameraDir = (pos - camera->pos).SafeANormalize();
	// beam's coor-system; degenerate if targetPos == startPos
	const float3 zdir = (targetPos - startpos).SafeANormalize();
	const float3 xdir = (cameraDir.cross(zdir)).SafeANormalize();
	const float3 ydir = (cameraDir.cross(xdir));

	float3 pos1 = startpos;
	float3 pos2 = targetPos;

	const float startTex = 1.0f - ((gu->modGameTime * scrollspeed) - int(gu->modGameTime * scrollspeed));
	const float texSizeX = beamtex.xend - beamtex.xstart;

	const float beamEdgeSize = thickness;
	const float beamCoreSize = beamEdgeSize * corethickness;
	const float beamLength   = (targetPos - startpos).dot(zdir);
	const float flareEdgeSize = thickness * flaresize;
	const float flareCoreSize = flareEdgeSize * corethickness;

	const float beamTileMinDst = tilelength * (1.0f - startTex);
	const float beamTileMaxDst = beamLength - tilelength;
	// note: beamTileMaxDst can be negative, in which case we want numBeamTiles to equal zero
	const float numBeamTiles = std::floor(((std::max(beamTileMinDst, beamTileMaxDst) - beamTileMinDst) / tilelength) + 0.5f);

	AtlasedTexture tex = beamtex;

	va->EnlargeArrays(64 + (8 * (int((beamTileMaxDst - beamTileMinDst) / tilelength) + 2)), 0, VA_SIZE_TC);

	#define WT2 weaponDef->visuals.texture2
	#define WT4 weaponDef->visuals.texture4

	if (beamTileMinDst > beamLength) {
		// beam short enough to be drawn by one polygon
		// draw laser start
		tex.xstart = beamtex.xstart + startTex * texSizeX;

		va->AddVertexQTC(pos1 - (xdir * beamEdgeSize), tex.xstart, tex.ystart, edgeColStart);
		va->AddVertexQTC(pos1 + (xdir * beamEdgeSize), tex.xstart, tex.yend,   edgeColStart);
		va->AddVertexQTC(pos2 + (xdir * beamEdgeSize), tex.xend,   tex.yend,   edgeColStart);
		va->AddVertexQTC(pos2 - (xdir * beamEdgeSize), tex.xend,   tex.ystart, edgeColStart);
		va->AddVertexQTC(pos1 - (xdir * beamCoreSize), tex.xstart, tex.ystart, coreColStart);
		va->AddVertexQTC(pos1 + (xdir * beamCoreSize), tex.xstart, tex.yend,   coreColStart);
		va->AddVertexQTC(pos2 + (xdir * beamCoreSize), tex.xend,   tex.yend,   coreColStart);
		va->AddVertexQTC(pos2 - (xdir * beamCoreSize), tex.xend,   tex.ystart, coreColStart);
	} else {
		// beam longer than one polygon
		pos2 = pos1 + zdir * beamTileMinDst;

		// draw laser start
		tex.xstart = beamtex.xstart + startTex * texSizeX;

		va->AddVertexQTC(pos1 - (xdir * beamEdgeSize), tex.xstart, tex.ystart, edgeColStart);
		va->AddVertexQTC(pos1 + (xdir * beamEdgeSize), tex.xstart, tex.yend,   edgeColStart);
		va->AddVertexQTC(pos2 + (xdir * beamEdgeSize), tex.xend,   tex.yend,   edgeColStart);
		va->AddVertexQTC(pos2 - (xdir * beamEdgeSize), tex.xend,   tex.ystart, edgeColStart);
		va->AddVertexQTC(pos1 - (xdir * beamCoreSize), tex.xstart, tex.ystart, coreColStart);
		va->AddVertexQTC(pos1 + (xdir * beamCoreSize), tex.xstart, tex.yend,   coreColStart);
		va->AddVertexQTC(pos2 + (xdir * beamCoreSize), tex.xend,   tex.yend,   coreColStart);
		va->AddVertexQTC(pos2 - (xdir * beamCoreSize), tex.xend,   tex.ystart, coreColStart);

		// draw continous beam
		tex.xstart = beamtex.xstart;

		for (float i = beamTileMinDst; i < beamTileMaxDst; i += tilelength) {
			//! CAUTION: loop count must match EnlargeArrays above
			pos1 = startpos + zdir * i;
			pos2 = startpos + zdir * (i + tilelength);

			va->AddVertexQTC(pos1 - (xdir * beamEdgeSize), tex.xstart, tex.ystart, edgeColStart);
			va->AddVertexQTC(pos1 + (xdir * beamEdgeSize), tex.xstart, tex.yend,   edgeColStart);
			va->AddVertexQTC(pos2 + (xdir * beamEdgeSize), tex.xend,   tex.yend,   edgeColStart);
			va->AddVertexQTC(pos2 - (xdir * beamEdgeSize), tex.xend,   tex.ystart, edgeColStart);
			va->AddVertexQTC(pos1 - (xdir * beamCoreSize), tex.xstart, tex.ystart, coreColStart);
			va->AddVertexQTC(pos1 + (xdir * beamCoreSize), tex.xstart, tex.yend,   coreColStart);
			va->AddVertexQTC(pos2 + (xdir * beamCoreSize), tex.xend,   tex.yend,   coreColStart);
			va->AddVertexQTC(pos2 - (xdir * beamCoreSize), tex.xend,   tex.ystart, coreColStart);
		}

		// draw laser end
		pos1 = startpos + zdir * (beamTileMinDst + numBeamTiles * tilelength);
		pos2 = targetPos;
		tex.xend = tex.xstart + (pos1.distance(pos2) / tilelength) * texSizeX;

		va->AddVertexQTC(pos1 - (xdir * beamEdgeSize), tex.xstart, tex.ystart, edgeColStart);
		va->AddVertexQTC(pos1 + (xdir * beamEdgeSize), tex.xstart, tex.yend,   edgeColStart);
		va->AddVertexQTC(pos2 + (xdir * beamEdgeSize), tex.xend,   tex.yend,   edgeColStart);
		va->AddVertexQTC(pos2 - (xdir * beamEdgeSize), tex.xend,   tex.ystart, edgeColStart);
		va->AddVertexQTC(pos1 - (xdir * beamCoreSize), tex.xstart, tex.ystart, coreColStart);
		va->AddVertexQTC(pos1 + (xdir * beamCoreSize), tex.xstart, tex.yend,   coreColStart);
		va->AddVertexQTC(pos2 + (xdir * beamCoreSize), tex.xend,   tex.yend,   coreColStart);
		va->AddVertexQTC(pos2 - (xdir * beamCoreSize), tex.xend,   tex.ystart, coreColStart);
	}

	va->AddVertexQTC(pos2 - (xdir * beamEdgeSize),                         WT2->xstart, WT2->ystart, edgeColStart);
	va->AddVertexQTC(pos2 + (xdir * beamEdgeSize),                         WT2->xstart, WT2->yend,   edgeColStart);
	va->AddVertexQTC(pos2 + (xdir * beamEdgeSize) + (ydir * beamEdgeSize), WT2->xend,   WT2->yend,   edgeColStart);
	va->AddVertexQTC(pos2 - (xdir * beamEdgeSize) + (ydir * beamEdgeSize), WT2->xend,   WT2->ystart, edgeColStart);
	va->AddVertexQTC(pos2 - (xdir * beamCoreSize),                         WT2->xstart, WT2->ystart, coreColStart);
	va->AddVertexQTC(pos2 + (xdir * beamCoreSize),                         WT2->xstart, WT2->yend,   coreColStart);
	va->AddVertexQTC(pos2 + (xdir * beamCoreSize) + (ydir * beamCoreSize), WT2->xend,   WT2->yend,   coreColStart);
	va->AddVertexQTC(pos2 - (xdir * beamCoreSize) + (ydir * beamCoreSize), WT2->xend,   WT2->ystart, coreColStart);

	float pulseStartTime = (gu->modGameTime * pulseSpeed) - int(gu->modGameTime * pulseSpeed);
	float muzzleEdgeSize = thickness * flaresize * pulseStartTime;
	float muzzleCoreSize = muzzleEdgeSize * 0.6f;

	unsigned char coreColor[4] = {0, 0, 0, 1};
	unsigned char edgeColor[4] = {0, 0, 0, 1};

	for (int i = 0; i < 3; i++) {
		coreColor[i] = int(coreColStart[i] * (1.0f - pulseStartTime));
		edgeColor[i] = int(edgeColStart[i] * (1.0f - pulseStartTime));
	}

	{
		// draw muzzleflare
		pos1 = startpos - zdir * (thickness * flaresize) * 0.02f;

		va->AddVertexQTC(pos1 + (ydir * muzzleEdgeSize),                           sidetex.xstart, sidetex.ystart, edgeColor);
		va->AddVertexQTC(pos1 + (ydir * muzzleEdgeSize) + (zdir * muzzleEdgeSize), sidetex.xend,   sidetex.ystart, edgeColor);
		va->AddVertexQTC(pos1 - (ydir * muzzleEdgeSize) + (zdir * muzzleEdgeSize), sidetex.xend,   sidetex.yend,   edgeColor);
		va->AddVertexQTC(pos1 - (ydir * muzzleEdgeSize),                           sidetex.xstart, sidetex.yend,   edgeColor);

		va->AddVertexQTC(pos1 + (ydir * muzzleCoreSize),                           sidetex.xstart, sidetex.ystart, coreColor);
		va->AddVertexQTC(pos1 + (ydir * muzzleCoreSize) + (zdir * muzzleCoreSize), sidetex.xend,   sidetex.ystart, coreColor);
		va->AddVertexQTC(pos1 - (ydir * muzzleCoreSize) + (zdir * muzzleCoreSize), sidetex.xend,   sidetex.yend,   coreColor);
		va->AddVertexQTC(pos1 - (ydir * muzzleCoreSize),                           sidetex.xstart, sidetex.yend,   coreColor);

		pulseStartTime += 0.5f;
		pulseStartTime -= (1.0f * (pulseStartTime > 1.0f));

		for (int i = 0; i < 3; i++) {
			coreColor[i] = int(coreColStart[i] * (1.0f - pulseStartTime));
			edgeColor[i] = int(edgeColStart[i] * (1.0f - pulseStartTime));
		}

		muzzleEdgeSize = thickness * flaresize * pulseStartTime;

		va->AddVertexQTC(pos1 + (ydir * muzzleEdgeSize),                           sidetex.xstart, sidetex.ystart, edgeColor);
		va->AddVertexQTC(pos1 + (ydir * muzzleEdgeSize) + (zdir * muzzleEdgeSize), sidetex.xend,   sidetex.ystart, edgeColor);
		va->AddVertexQTC(pos1 - (ydir * muzzleEdgeSize) + (zdir * muzzleEdgeSize), sidetex.xend,   sidetex.yend,   edgeColor);
		va->AddVertexQTC(pos1 - (ydir * muzzleEdgeSize),                           sidetex.xstart, sidetex.yend,   edgeColor);

		muzzleCoreSize = muzzleEdgeSize * 0.6f;

		va->AddVertexQTC(pos1 + (ydir * muzzleCoreSize),                           sidetex.xstart, sidetex.ystart, coreColor);
		va->AddVertexQTC(pos1 + (ydir * muzzleCoreSize) + (zdir * muzzleCoreSize), sidetex.xend,   sidetex.ystart, coreColor);
		va->AddVertexQTC(pos1 - (ydir * muzzleCoreSize) + (zdir * muzzleCoreSize), sidetex.xend,   sidetex.yend,   coreColor);
		va->AddVertexQTC(pos1 - (ydir * muzzleCoreSize),                           sidetex.xstart, sidetex.yend,   coreColor);
	}

	{
		// draw flare (moved slightly along the camera direction)
		pos1 = startpos - (camera->forward * 3.0f);

		va->AddVertexQTC(pos1 - (camera->right * flareEdgeSize) - (camera->up * flareEdgeSize), WT4->xstart, WT4->ystart, edgeColStart);
		va->AddVertexQTC(pos1 + (camera->right * flareEdgeSize) - (camera->up * flareEdgeSize), WT4->xend,   WT4->ystart, edgeColStart);
		va->AddVertexQTC(pos1 + (camera->right * flareEdgeSize) + (camera->up * flareEdgeSize), WT4->xend,   WT4->yend,   edgeColStart);
		va->AddVertexQTC(pos1 - (camera->right * flareEdgeSize) + (camera->up * flareEdgeSize), WT4->xstart, WT4->yend,   edgeColStart);

		va->AddVertexQTC(pos1 - (camera->right * flareCoreSize) - (camera->up * flareCoreSize), WT4->xstart, WT4->ystart, coreColStart);
		va->AddVertexQTC(pos1 + (camera->right * flareCoreSize) - (camera->up * flareCoreSize), WT4->xend,   WT4->ystart, coreColStart);
		va->AddVertexQTC(pos1 + (camera->right * flareCoreSize) + (camera->up * flareCoreSize), WT4->xend,   WT4->yend,   coreColStart);
		va->AddVertexQTC(pos1 - (camera->right * flareCoreSize) + (camera->up * flareCoreSize), WT4->xstart, WT4->yend,   coreColStart);
	}

	#undef WT4
	#undef WT2
}