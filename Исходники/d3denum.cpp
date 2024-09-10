static BOOL WINAPI enum_dd_devices_cb(
    GUID FAR* lpGUID, LPSTR lpDriverDescription, LPSTR lpDriverName, LPVOID lpContext)
{
    ddlist_t dd;

    dd.ddraw = NULL;

    if (FAILED(DirectDrawCreate(lpGUID, &dd.ddraw, NULL)))
    {
        return D3DENUMRET_OK;
    }

    strncpy(dd.descStr, lpDriverDescription, 127);
    strncpy(dd.nameStr, lpDriverName, 127);

    ddList.push_back(dd);

    return D3DENUMRET_OK;
}