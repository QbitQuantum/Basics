HRESULT IndexConstructor::CreateIndex()
{    
    HRESULT hr = E_FAIL;
    try
    {
        if (0 == indexDesc_.cbKey)
        {
            throw HrError("no one col is specified. cbKey==0", E_UNEXPECTED, __FUNCTION__);
        }
        if (0 == wcslen(indexName_))
        {
            throw HrError("index name is not specified.", E_UNEXPECTED, __FUNCTION__);
        }
        const JET_ERR jetErr = JetCreateIndex2W(sesId_, tableId_, &indexDesc_, 1);
        if (jetErr != JET_errSuccess)
        {
            throw Error("JetCreateIndex2W", jetErr, __FUNCTION__);            
        }
        hr = S_OK;
    }
    catch (const HrError & e)
    {
        SetLastErrorDesc(e);
        hr = e.GetErrCode();
    }
    catch (const std::exception & e)
    {
        SetLastErrorDesc(e);
    }
    return hr;
}