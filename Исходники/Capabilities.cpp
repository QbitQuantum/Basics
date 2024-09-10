    GPUVendor DiGfxCaps::vendorFromString(const DiString& vendorString)
    {
        initVendorStrings();
        GPUVendor ret = GPU_UNKNOWN;
        DiString cmpString = vendorString;
        cmpString.ToLower();
        for (int i = 0; i < GPU_VENDOR_COUNT; ++i)
        {
            // case insensitive (lower case)
            if (msGPUVendorStrings[i] == cmpString)
            {
                ret = static_cast<GPUVendor>(i);
                break;
            }
        }

        return ret;
        
    }