std::string
WinPortFactory::begin()
{
    DWORD size = 0;

    if (_devInfo != INVALID_HANDLE_VALUE)
        cleanup();

    SetupDiClassGuidsFromNameA("Ports", 0, 0, &size);
    if (size < 1)
        return error();

    GUID guids[size];

    if (!SetupDiClassGuidsFromNameA("Ports", guids, size * sizeof(GUID), &size))
    {
        return error();
    }

    _devInfo = SetupDiGetClassDevs(guids, NULL, NULL, DIGCF_PRESENT);
    if(_devInfo == INVALID_HANDLE_VALUE)
        return error();

    _cfgMgr = LoadLibrary("cfgmgr32");
    if (!_cfgMgr)
        return error();

    _devNode = (CM_Open_DevNode_Key) GetProcAddress(_cfgMgr, "CM_Open_DevNode_Key");
    if (!_devNode)
        return error();

    return next();
}