bool ServiceUtil::remove(const tstring& name)
{
    bool bReturn = false;

    do 
    {
        scoped_svc_handle hService(name, GENERIC_ALL, SERVICE_ALL_ACCESS);
        if (!hService.valid())
        {
            break;
        }

        if (!DeleteService(hService.get()))
        {
            ErrorLogLastErr(TSTR("DeleteService[%s] fail"), name.c_str());
            break;
        }

        bReturn = true;

    } while (false);

    return bReturn;
}