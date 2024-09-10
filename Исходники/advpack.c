/***********************************************************************
 *             SetPerUserSecValuesA   (ADVPACK.@)
 *
 * See SetPerUserSecValuesW.
 */
HRESULT WINAPI SetPerUserSecValuesA(PERUSERSECTIONA* pPerUser)
{
    PERUSERSECTIONW perUserW;

    TRACE("(%p)\n", pPerUser);

    if (!pPerUser)
        return E_INVALIDARG;

    MultiByteToWideChar(CP_ACP, 0, pPerUser->szGUID, -1, perUserW.szGUID,
                        sizeof(perUserW.szGUID) / sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, pPerUser->szDispName, -1, perUserW.szDispName,
                        sizeof(perUserW.szDispName) / sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, pPerUser->szLocale, -1, perUserW.szLocale,
                        sizeof(perUserW.szLocale) / sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, pPerUser->szStub, -1, perUserW.szStub,
                        sizeof(perUserW.szStub) / sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, pPerUser->szVersion, -1, perUserW.szVersion,
                        sizeof(perUserW.szVersion) / sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, pPerUser->szCompID, -1, perUserW.szCompID,
                        sizeof(perUserW.szCompID) / sizeof(WCHAR));
    perUserW.dwIsInstalled = pPerUser->dwIsInstalled;
    perUserW.bRollback = pPerUser->bRollback;

    return SetPerUserSecValuesW(&perUserW);
}