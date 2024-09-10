int SetupPrivacy(wchar_t *pszFname, wchar_t *pszState, BOOL bSetPrivacy)
{
    CComPtr<ICameraDs> spCameraDs = nullptr;
    HRESULT hr = S_OK;
    int retcode = DEFAULT_ERROR;

    hr = CreateCameraDsInstance(&spCameraDs);

    if (SUCCEEDED(hr) && spCameraDs)
    {
        hr = spCameraDs->Initialize(pszFname);

        if (SUCCEEDED(hr))
        {
            if (bSetPrivacy)
            {
                hr = spCameraDs->SetPrivacy(_wtol(pszState));

                if (SUCCEEDED(hr))
                {
                    _tprintf(L"Output: Operation successful.\n");
                    retcode = NOERROR;
                }
                else
                {
                    ErrorCom(hr, L"SetPrivacy");
                    retcode = DEFAULT_ERROR;
                }
            }
            else
            {
                LONG lValue = 0, lFlags = 0;

                hr = spCameraDs->GetPrivacy(&lValue, &lFlags);

                if (SUCCEEDED(hr))
                {
                    _tprintf(L"Output: Operation successful.\n");
                    _tprintf(L"Output: Current privacy settings: %d\n", lValue);
                    _tprintf(L"Output: Current privacy flags: %x\n", lFlags);
                    retcode = (int)lValue;
                }
                else
                {
                    ErrorCom(hr, L"GetPrivacy");
                    retcode = DEFAULT_ERROR;
                }
            }

            spCameraDs->CloseInterfaces();
        }
        else
        {
            ErrorCom(hr, L"Initialize");
            retcode = DEFAULT_ERROR;
        }
    }

    return retcode;
}