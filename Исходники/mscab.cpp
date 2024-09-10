bool MsCab::extractFiles(LPWSTR pstrPath, LPWSTR pstrFile, FDICOPYFILECALLBACK copyCallback, void *data)
{
    bool r = false;
    void *p;

    if((p = FDICreate(copyCallback, data)) != NULL)
    {
        r = FDICopy(p, pstrPath, pstrFile);
        FDIClose(p);
    }

    return r;
}