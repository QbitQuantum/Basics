void  STAClientCall()
{
    if (SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
    {
        COSERVERINFO si;
        COAUTHINFO ai;
        si.pAuthInfo = &ai;
        COAUTHIDENTITY authident;
        ai.pAuthIdentityData = &authident;
        IntializeServerInfo (si);

        MULTI_QI mqi;
        mqi.pIID = &IID_ICalculator;
        mqi.pItf = 0;
        mqi.hr = 0;

        wprintf(L"\nCalling CoCreateInstanceEx ... ");
        if (SUCCEEDED(CoCreateInstanceEx(
            CLSID_Calculator,
            NULL,
            CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER,
            &si,
            1,
            &mqi
        )))
        {
            wprintf(L"done\n");
            ICalculator * pCalculator = NULL;
            pCalculator = (ICalculator*)mqi.pItf;
            __int32 result = 0;
            wprintf(L"Calling SumSlow ...");
            pCalculator->SumSlow(1,2, &result);
            pCalculator->Release();
            wprintf(L"done\n");
        }
        else
        {
	        wprintf(L"failed\n");
        }
        CoUninitialize();
    }
}