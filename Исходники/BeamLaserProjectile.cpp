void CBeamLaserProjectile::Draw()
{
	inArray = true;

	const float3 cameraDir = (pos - camera->pos).SafeANormalize();
	// beam's coor-system; degenerate if targetPos == startPos
	const float3 zdir = (targetPos - startpos).SafeANormalize();
	const float3 xdir = (cameraDir.cross(zdir)).SafeANormalize();
	const float3 ydir = (cameraDir.cross(xdir));

	const float beamEdgeSize = thickness;
	const float beamCoreSize = beamEdgeSize * corethickness;
	const float flareEdgeSize = thickness * flaresize;
	const float flareCoreSize = flareEdgeSize * corethickness;

	const float3& pos1 = startpos;
	const float3& pos2 = targetPos;

	va->EnlargeArrays(32, 0, VA_SIZE_TC);

	#define WT1 weaponDef->visuals.texture1
	#define WT2 weaponDef->visuals.texture2
	#define WT3 weaponDef->visuals.texture3

	if ((pos - camera->pos).SqLength() < (1000.0f * 1000.0f)) {
		va->AddVertexQTC(pos1 - xdir * beamEdgeSize,                       midtexx,   WT2->ystart, edgeColStart);
		va->AddVertexQTC(pos1 + xdir * beamEdgeSize,                       midtexx,   WT2->yend,   edgeColStart);
		va->AddVertexQTC(pos1 + xdir * beamEdgeSize - ydir * beamEdgeSize, WT2->xend, WT2->yend,   edgeColStart);
		va->AddVertexQTC(pos1 - xdir * beamEdgeSize - ydir * beamEdgeSize, WT2->xend, WT2->ystart, edgeColStart);
		va->AddVertexQTC(pos1 - xdir * beamCoreSize,                       midtexx,   WT2->ystart, coreColStart);
		va->AddVertexQTC(pos1 + xdir * beamCoreSize,                       midtexx,   WT2->yend,   coreColStart);
		va->AddVertexQTC(pos1 + xdir * beamCoreSize - ydir * beamCoreSize, WT2->xend, WT2->yend,   coreColStart);
		va->AddVertexQTC(pos1 - xdir * beamCoreSize - ydir * beamCoreSize, WT2->xend, WT2->ystart, coreColStart);

		va->AddVertexQTC(pos1 - xdir * beamEdgeSize,                       WT1->xstart, WT1->ystart, edgeColStart);
		va->AddVertexQTC(pos1 + xdir * beamEdgeSize,                       WT1->xstart, WT1->yend,   edgeColStart);
		va->AddVertexQTC(pos2 + xdir * beamEdgeSize,                       WT1->xend,   WT1->yend,   edgeColEnd);
		va->AddVertexQTC(pos2 - xdir * beamEdgeSize,                       WT1->xend,   WT1->ystart, edgeColEnd);
		va->AddVertexQTC(pos1 - xdir * beamCoreSize,                       WT1->xstart, WT1->ystart, coreColStart);
		va->AddVertexQTC(pos1 + xdir * beamCoreSize,                       WT1->xstart, WT1->yend,   coreColStart);
		va->AddVertexQTC(pos2 + xdir * beamCoreSize,                       WT1->xend,   WT1->yend,   coreColEnd);
		va->AddVertexQTC(pos2 - xdir * beamCoreSize,                       WT1->xend,   WT1->ystart, coreColEnd);

		va->AddVertexQTC(pos2 - xdir * beamEdgeSize,                       midtexx,   WT2->ystart, edgeColStart);
		va->AddVertexQTC(pos2 + xdir * beamEdgeSize,                       midtexx,   WT2->yend,   edgeColStart);
		va->AddVertexQTC(pos2 + xdir * beamEdgeSize + ydir * beamEdgeSize, WT2->xend, WT2->yend,   edgeColStart);
		va->AddVertexQTC(pos2 - xdir * beamEdgeSize + ydir * beamEdgeSize, WT2->xend, WT2->ystart, edgeColStart);
		va->AddVertexQTC(pos2 - xdir * beamCoreSize,                       midtexx,   WT2->ystart, coreColStart);
		va->AddVertexQTC(pos2 + xdir * beamCoreSize,                       midtexx,   WT2->yend,   coreColStart);
		va->AddVertexQTC(pos2 + xdir * beamCoreSize + ydir * beamCoreSize, WT2->xend, WT2->yend,   coreColStart);
		va->AddVertexQTC(pos2 - xdir * beamCoreSize + ydir * beamCoreSize, WT2->xend, WT2->ystart, coreColStart);
	} else {
		va->AddVertexQTC(pos1 - xdir * beamEdgeSize,                       WT1->xstart, WT1->ystart, edgeColStart);
		va->AddVertexQTC(pos1 + xdir * beamEdgeSize,                       WT1->xstart, WT1->yend,   edgeColStart);
		va->AddVertexQTC(pos2 + xdir * beamEdgeSize,                       WT1->xend,   WT1->yend,   edgeColEnd);
		va->AddVertexQTC(pos2 - xdir * beamEdgeSize,                       WT1->xend,   WT1->ystart, edgeColEnd);
		va->AddVertexQTC(pos1 - xdir * beamCoreSize,                       WT1->xstart, WT1->ystart, coreColStart);
		va->AddVertexQTC(pos1 + xdir * beamCoreSize,                       WT1->xstart, WT1->yend,   coreColStart);
		va->AddVertexQTC(pos2 + xdir * beamCoreSize,                       WT1->xend,   WT1->yend,   coreColEnd);
		va->AddVertexQTC(pos2 - xdir * beamCoreSize,                       WT1->xend,   WT1->ystart, coreColEnd);
	}

	// draw flare
	va->AddVertexQTC(pos1 - camera->right * flareEdgeSize - camera->up * flareEdgeSize, WT3->xstart, WT3->ystart, edgeColStart);
	va->AddVertexQTC(pos1 + camera->right * flareEdgeSize - camera->up * flareEdgeSize, WT3->xend,   WT3->ystart, edgeColStart);
	va->AddVertexQTC(pos1 + camera->right * flareEdgeSize + camera->up * flareEdgeSize, WT3->xend,   WT3->yend,   edgeColStart);
	va->AddVertexQTC(pos1 - camera->right * flareEdgeSize + camera->up * flareEdgeSize, WT3->xstart, WT3->yend,   edgeColStart);

	va->AddVertexQTC(pos1 - camera->right * flareCoreSize - camera->up * flareCoreSize, WT3->xstart, WT3->ystart, coreColStart);
	va->AddVertexQTC(pos1 + camera->right * flareCoreSize - camera->up * flareCoreSize, WT3->xend,   WT3->ystart, coreColStart);
	va->AddVertexQTC(pos1 + camera->right * flareCoreSize + camera->up * flareCoreSize, WT3->xend,   WT3->yend,   coreColStart);
	va->AddVertexQTC(pos1 - camera->right * flareCoreSize + camera->up * flareCoreSize, WT3->xstart, WT3->yend,   coreColStart);

	#undef WT3
	#undef WT2
	#undef WT1
}