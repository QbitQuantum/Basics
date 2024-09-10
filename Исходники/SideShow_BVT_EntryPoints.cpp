//Verify Windows SideShow (Aux display) item in CPL
STDAPI SideShow_BVT_EntryPoints(LPVOID pvReserved)
{
    BOOL fResult = FALSE;
    BOOL fLaunched = FALSE;

    LogTestBeginW(__FUNCTIONW__, L"Beginning Windows SideShow BVT test case...");

    HRESULT hr = LOG_FAILED_HR(FromPartialQueryId(START_BUTTON));

    if (SUCCEEDED(hr))
    {
        LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

        hr = LOG_FAILED_HR(FromPartialQueryId(START_MENU_CONTROL_PANEL));
        if (SUCCEEDED(hr))
        {
            LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));

            //checks to make the switch to Classic View or not
            int originalTimeout = SetSearchTimeOut(TEN_SECONDS);
            hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLASSIC_VIEW_LNK));
            if (FAILED(hr))
            {
                LogTestInfoW(__FUNCTIONW__, L"Attempt to switch to Classic View failed. Control Panel is already in Classic View mode...");
            }
            else
            {
                LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
            }
            // restore timeout
            SetSearchTimeOut(originalTimeout);

            BOOL fExpected = FALSE;
            DWORD dwProductInfoType = 0;

            if (GetProductInfo(WINDOWS_VISTA_VERSION, 0, 0, 0, &dwProductInfoType))
            {
                switch (dwProductInfoType)
                {
                    case PRODUCT_STARTER:
                    case PRODUCT_HOME_BASIC:
                    case PRODUCT_HOME_BASIC_N:
                        LogTestInfoW(__FUNCTIONW__, L"Windows SideShow is NOT expected in this SKU.");
                        break;
                    case PRODUCT_HOME_PREMIUM:
                    case PRODUCT_HOME_PREMIUM_N:
                    case PRODUCT_BUSINESS:
                    case PRODUCT_BUSINESS_N:
                    case PRODUCT_ENTERPRISE:
                    case PRODUCT_ENTERPRISE_N:
                    case PRODUCT_ULTIMATE:
                    case PRODUCT_ULTIMATE_N:
                        fExpected = TRUE;
                        LogTestInfoW(__FUNCTIONW__, L"Windows SideShow is expected in this SKU.");
                        break;
                    default:
                        LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU.");
                        break;
                }

                BOOL fFoundUI = SUCCEEDED(LOG_FAILED_HR(FromPartialQueryId(CPL_SIDESHOW_LNK_ENU)));

                if (fFoundUI)
                {
                    fFoundUI &= SUCCEEDED(LOG_FAILED_HR(DoubleClick(CLICKABLE_POINT)));
                    LogTestInfoW(__FUNCTIONW__, L"%s Found Item", fFoundUI ? L"Found": L"Did not find");
                    fLaunched = TRUE;
                }

                if (fFoundUI != fExpected)
                {
                    LogTestInfoW(__FUNCTIONW__,
                        L"Windows SideShow SKU differentiated feature failed.[Current: %s | Expected: %s ]",
                        fFoundUI ? L"Found": L"Not Found",
                        fExpected ? L"Found" : L"Not Found");
                }
                else
                {
                    fResult = TRUE;
                    LogTestInfoW(__FUNCTIONW__, L"Windows SideShow is differentiated correctly.");
                }
            }
            else
            {
                LogTestInfoW(__FUNCTIONW__, L"GetProductInfo failed.");
            }
        }
    }

  LogTestInfoW(__FUNCTIONW__, L"Cleaning up...\n");

  if (!fLaunched)
  {
    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_CLOSE_BTN));
    if (SUCCEEDED(hr))
    {
        hr = LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }
  }
  else
  {
    hr = LOG_FAILED_HR(FromPartialQueryId(CPL_SIDESHOW_CLOSE));
    if (SUCCEEDED(hr))
    {
        hr = LOG_FAILED_HR(LeftButtonClick(CLICKABLE_POINT));
    }
  }

  LogTestResultW(fResult, __FUNCTIONW__, L"Completed Windows SideShow BVT test case.");
  return NOERROR;
}