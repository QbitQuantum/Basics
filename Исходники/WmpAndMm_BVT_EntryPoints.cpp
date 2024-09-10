//    
//    VerifyWmp_StartMenuEntryPoint 
//  
STDAPI VerifyWmp_StartMenuEntryPoint(LPVOID pvReserved)
{
    BOOL    fPassed = FALSE;
    LPWSTR pwszResultInfo = NULL;
    HRESULT hr = E_FAIL;
    
    LogTestBeginW(__FUNCTIONW__, L"Verify Windows Media Player available in the Start Menu");    
 
    hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        
        hr = LOG_FAILED_HR(FromPartialQueryId(STARTMENU_ALLPROGRAMS));
        if (SUCCEEDED(hr))  
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            BOOL fFoundWMP = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(WINDOWS_MEDIA_PLAYER)));
            BOOL fExpected = FALSE;
            DWORD dwProductInfoType = 0;

            if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
            {
                switch (dwProductInfoType)
                {
                    case PRODUCT_BUSINESS_N:
                    case PRODUCT_HOME_BASIC_N:
                        LogTestInfoW(__FUNCTIONW__, L"Windows Media Player is not expected here!");
                        break;
                    case PRODUCT_STARTER:
                    case PRODUCT_HOME_BASIC:
                    case PRODUCT_HOME_PREMIUM:
                    case PRODUCT_HOME_PREMIUM_N:
                    case PRODUCT_BUSINESS:
                    case PRODUCT_ENTERPRISE:
                    case PRODUCT_ENTERPRISE_N:
                    case PRODUCT_ULTIMATE:
                    case PRODUCT_ULTIMATE_N:
                        fExpected = TRUE;
                        pwszResultInfo = L"Windows Media Player expected here.";
                        break;
                    default:
                        LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                        pwszResultInfo = L"Could not verify behavior";
                        break;
                }

                if (fFoundWMP != fExpected)
                {
                    LogTestInfoW(__FUNCTIONW__,
                        L"WMP SKU differentiation failed.[Current: %s | Expected: %s ]",
                        fFoundWMP ? L"Found": L"Not Found",
                        fExpected ? L"Found" : L"Not Found");
                }
                else
                {
                    fPassed = TRUE;
                    pwszResultInfo = L"WMP entry point is differentiated correctly";
                    if (fExpected)
                    {
                        RightButtonClick(CLICKABLE_POINT);
                    }
                }
            }
            else
            {
                LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
                pwszResultInfo = L"GetProductInfo failed.";
            }
        }
    }

    LogTestInfoW(__FUNCTIONW__, L"Cleaning up...");
    
    hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));
    if (SUCCEEDED(hr))
    {
       LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }

 
    LogTestResultW(fPassed, __FUNCTIONW__, pwszResultInfo);
    return NOERROR;
}