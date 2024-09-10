/* global init function */
void cowInit(void) {
    int j;
    redisLog(REDIS_NOTICE, "cowInit");
    server.isBackgroundSaving = 0;
    server.cowDictCopied = NULL;
    server.cowDictConverted = NULL;
    server.cowSaveDbExt = (bkgdDbExt *)zmalloc(sizeof(bkgdDbExt)*server.dbnum);
    server.cowSaveDb = (redisDb *)zmalloc(sizeof(redisDb)*server.dbnum);

    deferSdsDelete = listCreate();
    deferObjDelete = listCreate();

    for (j = 0; j < server.dbnum; j++) {
        server.cowSaveDb[j].dict = NULL;
        server.cowSaveDb[j].expires = NULL;
        server.cowSaveDb[j].blocking_keys = NULL;
        server.cowSaveDb[j].watched_keys = NULL;
        server.cowSaveDb[j].id = j;
        server.cowSaveDbExt[j].savedType = NULL;
        server.cowSaveDbExt[j].cowType = &dbDeferDictType;
        server.cowSaveDbExt[j].readonlyType = &dbDeferDictType;
        server.cowSaveDbExt[j].dictArray = NULL;
        server.cowSaveDbExt[j].id = j;
    }

    server.cowCurIters.curDbDictIter = NULL;
    server.cowCurIters.curObjDictIter = NULL;
    server.cowCurIters.curObjListIter = NULL;
    server.cowCurIters.curObjZDictIter = NULL;
    InitializeCriticalSectionAndSpinCount(&server.cowCurIters.csMigrate, 500);

}