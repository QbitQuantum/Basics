int main(int argc, char* argv[])
{
    _setmaxstdio(2048);
    uint32 threads = 4, extractFlags = 0;
    std::set<uint32> mapIds;

    if (!HandleArgs(argc, argv, threads, mapIds, Constants::Debug, extractFlags))
    {
        PrintUsage();
        return -1;
    }

    if (extractFlags == 0)
    {
        printf("You must provide valid extract flags.\n");
        PrintUsage();
        return -1;
    }

    Cache = new CacheClass();
    MPQHandler = new MPQManager();
    MPQHandler->Initialize();

    if (extractFlags & Constants::EXTRACT_FLAG_DBC)
        ExtractDBCs();

    if (extractFlags & Constants::EXTRACT_FLAG_MMAPS)
        ExtractMMaps(mapIds, threads);

    if (extractFlags & Constants::EXTRACT_FLAG_GOB_MODELS)
        ExtractGameobjectModels();

    if (extractFlags & Constants::EXTRACT_FLAG_TEST)
    {
        float start[] = { 16226.200195f, 16257.000000f, 13.202200f };
        float end[] = { 16245.725586f, 16382.465820f, 47.384956f };

        //
        float m_spos[3];
        m_spos[0] = -start[1];
        m_spos[1] = start[2];
        m_spos[2] = -start[0];

        //
        float m_epos[3];
        m_epos[0] = -end[1];
        m_epos[1] = end[2];
        m_epos[2] = -end[0];

        //
        dtQueryFilter m_filter;
        m_filter.setIncludeFlags(Constants::POLY_AREA_ROAD | Constants::POLY_AREA_TERRAIN);
        m_filter.setExcludeFlags(Constants::POLY_AREA_WATER);

        //
        float m_polyPickExt[3];
        m_polyPickExt[0] = 2.5f;
        m_polyPickExt[1] = 2.5f;
        m_polyPickExt[2] = 2.5f;

        //
        dtPolyRef m_startRef;
        dtPolyRef m_endRef;

        FILE* mmap = fopen("mmaps/001.mmap", "rb");
        dtNavMeshParams params;
        int count = fread(&params, sizeof(dtNavMeshParams), 1, mmap);
        fclose(mmap);
        if (count != 1)
        {
            printf("main: Error reading from .mmap\n");
            return 0;
        }

        dtNavMesh* navMesh = new dtNavMesh();
        dtNavMeshQuery* navMeshQuery = new dtNavMeshQuery();

        navMesh->init(&params);
        for (int i = 0; i <= 32; ++i)
        {
            for (int j = 0; j <= 32; ++j)
            {
                char buff[100];
                sprintf(buff, "mmaps/001%02i%02i.mmtile", i, j);
                LoadTile(navMesh, buff);
            }
        }
        
        navMeshQuery->init(navMesh, 2048);

        float nearestPt[3];

        navMeshQuery->findNearestPoly(m_spos, m_polyPickExt, &m_filter, &m_startRef, nearestPt);
        navMeshQuery->findNearestPoly(m_epos, m_polyPickExt, &m_filter, &m_endRef, nearestPt);

        if ( !m_startRef || !m_endRef )
        {
            std::cerr << "Could not find any nearby poly's (" << m_startRef << "," << m_endRef << ")" << std::endl;
            return 0;
        }

        int hops;
        dtPolyRef* hopBuffer = new dtPolyRef[8192];
        dtStatus status = navMeshQuery->findPath(m_startRef, m_endRef, m_spos, m_epos, &m_filter, hopBuffer, &hops, 8192);
        
        int resultHopCount;
        float* straightPath = new float[2048*3];
        unsigned char* pathFlags = new unsigned char[2048];
        dtPolyRef* pathRefs = new dtPolyRef[2048];

        status = navMeshQuery->findStraightPath(m_spos, m_epos, hopBuffer, hops, straightPath, pathFlags, pathRefs, &resultHopCount, 2048);
        std::vector<Vector3> FinalPath;
        FinalPath.reserve(resultHopCount);
        for (uint32 i = 0; i < resultHopCount; ++i)
        {
            Vector3 finalV = Utils::ToWoWCoords(Vector3(straightPath[i * 3 + 0], straightPath[i * 3 + 1], straightPath[i * 3 + 2]));
            FinalPath.push_back(finalV);
            printf("Point %f %f %f\n", finalV.x, finalV.y, finalV.z);
        }
    }

    return 0;
}