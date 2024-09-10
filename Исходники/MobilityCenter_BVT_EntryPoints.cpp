// Verify Mobility Center cpl in SKUs
STDAPI MobilityCenterEntryPoints(LPVOID pvReserved)
{

    BOOL fResult = FALSE;

    LogTestBeginW(__FUNCTIONW__, L"Beginning Mobility Center BVT test case...");

    LogTestInfoW(__FUNCTIONW__, L"Launch Start Button...\n");
    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));

    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        LogTestInfoW(__FUNCTIONW__, L"Launch Control Panel...\n");
        hr = LOG_FAILED_HR(FromPartialQueryId(START_MENU_CONTROL_PANEL));

        if (SUCCEEDED(hr))
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
            LogTestInfoW(__FUNCTIONW__, L"Maximize Control Panel...\n");
            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_MAXIMIZE));

            if (SUCCEEDED(hr))
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

                //Get Product Type
                LogTestInfoW(__FUNCTIONW__, L"Getting product type...\n");
                DWORD dwProductInfoType = 0;
                if (!GetProductInfo(6, 0, 0, 0, &dwProductInfoType))
                {
                    LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.\n");
                }

                LogTestInfoW(__FUNCTIONW__, L"Click Mobile PC link...\n");
                hr = FromPartialQueryId(CPL_MOBILE_PC_LNK);
                LeftButtonClick(CLICKABLE_POINT);

                // Unable to find Mobile PC item
                if (FAILED(hr))
                {
                    if (PRODUCT_STARTER == dwProductInfoType)
                    {
                        // pass test case if Mobile PC not found in Starter
                        fResult = TRUE;
                    }

                    else
                    {
                        // fail test case if Mobile PC not found in other SKUs
                        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                        fResult = FALSE;
                    }
                }

                // Able to find Mobile PC item
                else
                {
                    // fail test case for Starter
                    if (PRODUCT_STARTER == dwProductInfoType)
                    {
                        fResult = FALSE;
                    }
                    else
                    {
                        LogTestInfoW(__FUNCTIONW__, L"Click Mobility Center link...\n");
                        hr = LOG_FAILED_HR(FromPartialQueryId(CPL_MBLCTR_LNK));

                        if (SUCCEEDED(hr))
                        {
                            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                            LogTestInfoW(__FUNCTIONW__, L"Close Mobility Center...\n");
                            hr = LOG_FAILED_HR(FromPartialQueryId(MBLCTR_CLOSE_BTN));

                            if (SUCCEEDED(hr))
                            {
                                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
                                fResult = TRUE;
                            }
                        }
                    }
                }
            }
        }
    }

    // clean up: close windows
    if (SUCCEEDED(hr))
    {

        LogTestInfoW(__FUNCTIONW__, L"Close Control Panel...\n");
        hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLOSE_BTN));

        if (SUCCEEDED(hr))
        {
            hr = LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
        }
    }

    LogTestResultW(fResult, __FUNCTIONW__, L"Completed Mobility Center BVT test case.");
    return NOERROR;
}