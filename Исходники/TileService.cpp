///////////////////////////////////////////////////////////////////////////////
// Create tilename from mapDefinition, scaleIndex, row, and column.
// Remove lockfile, look for the tile in the cache, if not in cache create
// lockfile and look for map in mapcache.
MgByteReader* MgdTileService::GetTile(MgResourceIdentifier* mapDefinition,
                                      CREFSTRING baseMapLayerGroupName,
                                      INT32 tileColumn,
                                      INT32 tileRow,
                                      INT32 scaleIndex)
{
    Ptr<MgByteReader> ret;
    FILE* lockFile = NULL;
    STRING tilePathname, lockPathname;

    MG_LOG_OPERATION_MESSAGE(L"GetTile");

    MG_TRY()

    MG_LOG_OPERATION_MESSAGE_INIT(MG_API_VERSION(1, 0, 0), 5);
    MG_LOG_OPERATION_MESSAGE_PARAMETERS_START();
    MG_LOG_OPERATION_MESSAGE_ADD_STRING((NULL == mapDefinition) ? L"MgResourceIdentifier" : mapDefinition->ToString().c_str());
    MG_LOG_OPERATION_MESSAGE_ADD_SEPARATOR();
    MG_LOG_OPERATION_MESSAGE_ADD_STRING(baseMapLayerGroupName.c_str());
    MG_LOG_OPERATION_MESSAGE_ADD_SEPARATOR();
    MG_LOG_OPERATION_MESSAGE_ADD_INT32(tileColumn);
    MG_LOG_OPERATION_MESSAGE_ADD_SEPARATOR();
    MG_LOG_OPERATION_MESSAGE_ADD_INT32(tileRow);
    MG_LOG_OPERATION_MESSAGE_ADD_SEPARATOR();
    MG_LOG_OPERATION_MESSAGE_ADD_INT32(scaleIndex);
    MG_LOG_OPERATION_MESSAGE_PARAMETERS_END();

    if (NULL == mapDefinition || baseMapLayerGroupName.empty())
    {
        throw new MgNullArgumentException(L"MgdTileService.GetTile",
                                          __LINE__, __WFILE__, NULL, L"", NULL);
    }

    if (scaleIndex < 0)
    {
        STRING buffer;
        MgUtil::Int32ToString(scaleIndex, buffer);

        MgStringCollection arguments;
        arguments.Add(L"5");
        arguments.Add(buffer);

        throw new MgInvalidArgumentException(L"MgdTileService.GetTile",
                                             __LINE__, __WFILE__, &arguments, L"MgInvalidScaleIndex", NULL);
    }

    // get the service from our helper method
    Ptr<MgResourceService> resourceService = GetResourceServiceForMapDef(mapDefinition,
            L"MgdTileService.GetTile");
    // Generate tile and lock pathnames.
    m_tileCache->GeneratePathnames(mapDefinition, scaleIndex, baseMapLayerGroupName,
                                   tileColumn, tileRow, tilePathname, lockPathname, false);

    // If there is a dangling lock file, then attempt to remove it.
    if (DetectTileLockFile(lockPathname))
    {
        // TODO: Handle the exception by displaying a tile with an error message?
        MgFileUtil::DeleteFile(lockPathname, true);
    }

    // try getting the tile from the cache
    ret = m_tileCache->Get(tilePathname);

    // if the reader is NULL then the tile wasn't in the cache and we
    // need to generate it
    while (NULL == ret)
    {
        // Attempt use a cached & serialized MgMap object
        Ptr<MgMemoryStreamHelper> cachedMap;
        STRING mapString = mapDefinition->ToString();
        Ptr<MgdMap> map;

        // Protect the serialized MgMap cache with a MgdMutex.  Stream reading is not
        // thread safe so we need to deserialize the map within the MgdMutex to ensure
        // that a Rewind() is not called in the middle of a Deserialize().
        // Lockfile test and creation is in same protected scope.
        {
            // Attempt to lock the tile file.
            ACE_MT(ACE_GUARD_RETURN(ACE_Recursive_Thread_Mutex, ace_mon, sm_MgdMutex, NULL));

            // Bail out if the tile file has been locked for so long.
            if (DetectTileLockFile(lockPathname))
            {
                MgStringCollection arguments;
                arguments.Add(lockPathname);

                throw new MgFileIoException(L"MgdTileService.GetTile",
                                            __LINE__, __WFILE__, &arguments, L"MgUnableToLockTileFile", NULL);
            }

            // try getting the tile from the cache
            ret = m_tileCache->Get(tilePathname);

            if (NULL != ret)
            {
                break;  // tile was in tileCache .. done.
            }

            // Create the lock file and close it right away.
            m_tileCache->CreateFullPath(mapDefinition, scaleIndex, baseMapLayerGroupName, tileColumn, tileRow);
            lockFile = ACE_OS::fopen(MG_WCHAR_TO_TCHAR(lockPathname), ACE_TEXT("wb"));

            if (NULL == lockFile)
            {
                MgStringCollection arguments;
                arguments.Add(lockPathname);

                throw new MgFileIoException(L"MgdTileService.GetTile",
                                            __LINE__, __WFILE__, &arguments, L"MgUnableToOpenLockFile", NULL);
            }
            else
            {
                ACE_OS::fclose(lockFile);
            }

            MapCache::const_iterator iter = sm_mapCache.find(mapString);
            if (sm_mapCache.end() != iter)
            {
                cachedMap = SAFE_ADDREF((*iter).second);
                cachedMap->Rewind();
                Ptr<MgStream> stream = new MgStream(cachedMap);
                map = new MgdMap();
                map->Deserialize(stream);
            }
            else
            {
                /*Ptr<MgSiteConnection> siteConn = new MgSiteConnection();
                Ptr<MgUserInformation> userInfo = MgUserInformation::GetCurrentUserInfo();
                siteConn->Open(userInfo);
                map = new MgMap(siteConn);
                map->Create(resourceService, mapDefinition, mapString);*/
                map = new MgdMap(mapDefinition, mapString);
                cachedMap = new MgMemoryStreamHelper();
                Ptr<MgStream> stream = new MgStream(cachedMap);
                map->Serialize(stream);
                if ((INT32)sm_mapCache.size() >= sm_mapCacheSize)
                {
                    ClearMapCache(L"");
                }
                sm_mapCache[mapString] = SAFE_ADDREF((MgMemoryStreamHelper*)cachedMap);
            }
        }   // end of MgdMutex scope

        double scale = map->GetFiniteDisplayScaleAt(scaleIndex);
        map->SetViewScale(scale);

        // Render the tile and cache it.
        ret = GetTile(tilePathname, map, scaleIndex, baseMapLayerGroupName, tileColumn, tileRow);
        break;
    }

    // Successful operation
    MG_LOG_OPERATION_MESSAGE_ADD_STRING(MgResources::Success.c_str());

    MG_CATCH(L"MgdTileService::GetTile")

    if (mgException != NULL)
    {
        // Failed operation
        MG_LOG_OPERATION_MESSAGE_ADD_STRING(MgResources::Failure.c_str());
        MG_DESKTOP_LOG_EXCEPTION();
    }

    if (NULL != lockFile)
    {
        MgFileUtil::DeleteFile(lockPathname, false);
    }

    // Add access log entry for operation
    MG_LOG_OPERATION_MESSAGE_ACCESS_ENTRY();

    MG_THROW()

    return ret.Detach();
}