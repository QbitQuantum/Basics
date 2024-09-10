	bool NavMesh::BuildMesh()
	{
		dtStatus status;
		if (!m_geom || !m_geom->getMesh()) return false;
		m_tmproc->init(m_geom);
		// Init cache
		const float* bmin = m_geom->getMeshBoundsMin();
		const float* bmax = m_geom->getMeshBoundsMax();
		int gw = 0, gh = 0;
		rcCalcGridSize(bmin, bmax, m_cellSize, &gw, &gh);
		const int ts = (int)m_tileSize;
		const int tw = (gw + ts-1) / ts;
		const int th = (gh + ts-1) / ts;
		// Generation params.
		rcConfig cfg;
		memset(&cfg, 0, sizeof(cfg));
		cfg.cs = m_cellSize;
		cfg.ch = m_cellHeight;
		cfg.walkableSlopeAngle = m_agentMaxSlope;
		cfg.walkableHeight = (int)ceilf(m_agentHeight / cfg.ch);
		cfg.walkableClimb = (int)floorf(m_agentMaxClimb / cfg.ch);
		cfg.walkableRadius = (int)ceilf(m_agentRadius / cfg.cs);
		cfg.maxEdgeLen = (int)(m_edgeMaxLen / m_cellSize);
		cfg.maxSimplificationError = m_edgeMaxError;
		cfg.minRegionArea = (int)rcSqr(m_regionMinSize);		// Note: area = size*size
		cfg.mergeRegionArea = (int)rcSqr(m_regionMergeSize);	// Note: area = size*size
		cfg.maxVertsPerPoly = (int)m_vertsPerPoly;
		cfg.tileSize = (int)m_tileSize;
		cfg.borderSize = cfg.walkableRadius + 3; // Reserve enough padding.
		cfg.width = cfg.tileSize + cfg.borderSize*2;
		cfg.height = cfg.tileSize + cfg.borderSize*2;
		cfg.detailSampleDist = m_detailSampleDist < 0.9f ? 0 : m_cellSize * m_detailSampleDist;
		cfg.detailSampleMaxError = m_cellHeight * m_detailSampleMaxError;
		rcVcopy(cfg.bmin, bmin);
		rcVcopy(cfg.bmax, bmax);
		// Tile cache params.
		dtTileCacheParams tcparams;
		memset(&tcparams, 0, sizeof(tcparams));
		rcVcopy(tcparams.orig, bmin);
		tcparams.cs = m_cellSize;
		tcparams.ch = m_cellHeight;
		tcparams.width = (int)m_tileSize;
		tcparams.height = (int)m_tileSize;
		tcparams.walkableHeight = m_agentHeight;
		tcparams.walkableRadius = m_agentRadius;
		tcparams.walkableClimb = m_agentMaxClimb;
		tcparams.maxSimplificationError = m_edgeMaxError;
		tcparams.maxTiles = tw*th*EXPECTED_LAYERS_PER_TILE;
		tcparams.maxObstacles = 128;

		dtFreeTileCache(m_tileCache);

		m_tileCache = dtAllocTileCache();
		if (!m_tileCache) return false;
		status = m_tileCache->init(&tcparams, m_talloc, m_tcomp, m_tmproc);
		if (dtStatusFailed(status)) return false;

		dtFreeNavMesh(m_navMesh);

		m_navMesh = dtAllocNavMesh();
		if (!m_navMesh) return false;

		dtNavMeshParams params;
		memset(&params, 0, sizeof(params));
		rcVcopy(params.orig, m_geom->getMeshBoundsMin());
		params.tileWidth = m_tileSize*m_cellSize;
		params.tileHeight = m_tileSize*m_cellSize;
		params.maxTiles = m_maxTiles;
		params.maxPolys = m_maxPolysPerTile;

		status = m_navMesh->init(&params);
		if (dtStatusFailed(status)) return false;

		status = m_navQuery->init(m_navMesh, 2048);
		if (dtStatusFailed(status)) return false;

		for (int y = 0; y < th; ++y)
		{
			for (int x = 0; x < tw; ++x)
			{
				TileCacheData tiles[MAX_LAYERS];
				memset(tiles, 0, sizeof(tiles));
				int n = rasterizeTileLayers(m_geom, x, y, cfg, tiles, MAX_LAYERS);
				for (int i = 0; i < n; ++i)
				{
					TileCacheData* tile = &tiles[i];
					status = m_tileCache->addTile(tile->data, tile->dataSize, DT_COMPRESSEDTILE_FREE_DATA, 0);
					if (dtStatusFailed(status))
					{
						dtFree(tile->data);
						tile->data = 0;
						continue;
					}
				}
			}
		}
		for (int y = 0; y < th; ++y)
			for (int x = 0; x < tw; ++x)
				m_tileCache->buildNavMeshTilesAt(x,y, m_navMesh);
	}