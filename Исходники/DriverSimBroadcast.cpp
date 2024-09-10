CDriverSimBroadcast::~CDriverSimBroadcast()
{
    Uninitialize();

    SAFE_FREELIBRARY(_hXdeModule);

    _pfnXdeInitialize = nullptr;
    _pfnXdeGetInternalMacAddress = nullptr;
}