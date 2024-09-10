// GetMaxRamInMbExpected
//
// Helper function that determines the max RAM in MB supported on the current installed SKU.
// Returns 0 : if SKU not supported on current processor architecture or is SKU cannot be determined
int GetMaxRamInMbExpected()
{
    int nMaxRamInMbExpected = 0;

    // get processor architecture upfront.
    BOOL fIs64BitProcessor = FALSE;
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
        systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
    {
        fIs64BitProcessor = TRUE;
    }

    DWORD dwProductInfoType = 0;
    if (GetProductInfo(6, 0, 0, 0, &dwProductInfoType))
    {
        switch (dwProductInfoType)
        {
            case PRODUCT_STARTER:
            {
                if (!fIs64BitProcessor)
                {
                    nMaxRamInMbExpected = RAM_512MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for Starter on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                else
                {
                    LogTestInfoW(__FUNCTIONW__, L"Starter not supported on 64-bit processors!!");
                }
                break;
            }
            case PRODUCT_HOME_BASIC:
            case PRODUCT_HOME_BASIC_N:
            {
                if (!fIs64BitProcessor)
                {
                    nMaxRamInMbExpected = RAM_4GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for Home Basic on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                else
                {
                    nMaxRamInMbExpected = RAM_8GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for Home Basic on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                break;
            }
            case PRODUCT_HOME_PREMIUM:
            case PRODUCT_HOME_PREMIUM_N:
            {
                if (!fIs64BitProcessor)
                {
                    nMaxRamInMbExpected = RAM_4GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for Home Premium on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                else
                {
                    nMaxRamInMbExpected = RAM_16GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for Home Premium on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                break;
            }
            case PRODUCT_BUSINESS:
            case PRODUCT_BUSINESS_N:
            case PRODUCT_ENTERPRISE:
            case PRODUCT_ENTERPRISE_N:
            case PRODUCT_ULTIMATE:
            case PRODUCT_ULTIMATE_N:
            {
                if (!fIs64BitProcessor)
                {
                    nMaxRamInMbExpected = RAM_4GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for this SKU on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                else
                {
                    nMaxRamInMbExpected = RAM_128GB_IN_MB;
                    LogTestInfoW(__FUNCTIONW__, L"Max RAM for this SKU on a 32-bit processor is %dMB!", nMaxRamInMbExpected);
                }
                break;
            }
            default:
                LogTestInfoW(__FUNCTIONW__, L"Could not determine the SKU");
                break;
        }
    }

    return nMaxRamInMbExpected;
}