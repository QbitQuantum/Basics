void EbrLockInit(EbrLock* pLock) {
    CRITICAL_SECTION* pCrit = (CRITICAL_SECTION*)IwMalloc(sizeof(CRITICAL_SECTION));

    InitializeCriticalSectionEx(pCrit, 0, 0);

    *pLock = (EbrLock)pCrit;
}