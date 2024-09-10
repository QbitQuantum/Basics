void MumbleManager::init()
{
#if defined BSD4_4
    return;
#endif
    if (mLinkedMem || !config.getBoolValue("enableMumble"))
        return;

    logger->log1("MumbleManager::init");
#ifdef WIN32
    HANDLE hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS,
                                         FALSE, L"MumbleLink");
    if (!hMapObject)
    {
        logger->log1("MumbleManager::init can't open MumbleLink");
        return;
    }

    mLinkedMem = reinterpret_cast<LinkedMem *>(MapViewOfFile(hMapObject,
        FILE_MAP_ALL_ACCESS, 0, 0, sizeof(LinkedMem)));

    if (!mLinkedMem)
    {
        CloseHandle(hMapObject);
        hMapObject = nullptr;
        logger->log1("MumbleManager::init can't map MumbleLink");
        return;
    }
#elif defined BSD4_4
#else
    char memName[256];
    snprintf(memName, sizeof(memName), "/MumbleLink.%u", getuid());

    const int shmfd = shm_open(memName, O_RDWR, S_IRUSR | S_IWUSR);

    if (shmfd < 0)
    {
        logger->log1("MumbleManager::init can't"
            " open shared memory MumbleLink");
        return;
    }

    mLinkedMem = static_cast<LinkedMem *>(mmap(nullptr,
        sizeof(struct LinkedMem), PROT_READ | PROT_WRITE,
        MAP_SHARED, shmfd, 0));

    if (mLinkedMem == reinterpret_cast<void *>(-1))
    {
        mLinkedMem = nullptr;
        logger->log1("MumbleManager::init can't map MumbleLink");
        return;
    }

#endif
    wcsncpy(mLinkedMemCache.name, L"ManaPlus", 256);
    wcsncpy(mLinkedMemCache.description, L"ManaPlus Plugin", 2048);
    mLinkedMemCache.uiVersion = 2;

    // Left handed coordinate system.
    // X positive towards "left".
    // Y positive towards "up".
    // Z positive towards "into screen".
    //
    // 1 unit = 1 meter

    // Unit vector pointing out of the avatars eyes
    // (here Front looks into scene).
    /* no way to look "up", 2d */
    mLinkedMemCache.fAvatarFront[1] = 0.0F;

    // Unit vector pointing out of the top of the avatars head
    // (here Top looks straight up).
    /* no way to change this in tmw */
    mLinkedMemCache.fAvatarTop[0] = 0.0F;
    mLinkedMemCache.fAvatarTop[1] = 1.0F;
    mLinkedMemCache.fAvatarTop[2] = 0.0F;

    mLinkedMemCache.fCameraFront[0] = 0.0F;
    mLinkedMemCache.fCameraFront[1] = 0.0F;
    mLinkedMemCache.fCameraFront[2] = 1.0F;

    mLinkedMemCache.fCameraTop[0] = 0.0F;
    mLinkedMemCache.fCameraTop[1] = 1.0F;
    mLinkedMemCache.fCameraTop[2] = 0.0F;

    mLinkedMemCache.uiTick++;
}