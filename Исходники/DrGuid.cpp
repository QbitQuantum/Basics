// Generate a new guid
void DrGuid::Generate()
{
    HRESULT success = CoCreateGuid((GUID *)this);
    if (FAILED(success))
    {
        LogAssert("Fatal error, failed to create guid");
    }
}