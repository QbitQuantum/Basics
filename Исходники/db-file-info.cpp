HRESULT DbFileInfo::GetPageSize(uint32_t & pageSize)
{
    try
    {
        unsigned long ps;
        const JET_ERR jetErr = JetGetDatabaseFileInfoW(dbFilePath_.c_str(), &ps, sizeof(ps), JET_DbInfoPageSize);
        if (jetErr != JET_errSuccess)
        {
            throw Error("JetGetDatabaseFileInfoW()", jetErr, __FUNCTION__);
        }
        pageSize = ps;
        return S_OK;
    }
    catch (const std::exception & e)
    {
        SetLastErrorDesc(e);
    }
    return E_FAIL;
}