HBufC* MicroEditionPlatformL()
{
    // First try to get the actual device name
    // If the device name is not found the default value is used: Series60/
    HBufC *productName= NULL;

    TBuf<KBufferSize> hardwareType(0);
    int retCode = getHardwareVersionL(hardwareType);

    if (retCode == KErrNone && hardwareType.Length() > 0)
    {
        TInt slashAfterManufacturer = hardwareType.Locate('/');
        TInt spaceAfterManufacturer = hardwareType.Locate(' ');
        TPtrC productNameShort = hardwareType;

        if ((slashAfterManufacturer != KErrNotFound) ||
                (spaceAfterManufacturer != KErrNotFound))
        {
            if (slashAfterManufacturer == KErrNotFound)
            {
                productNameShort.Set(hardwareType.Left(
                                         spaceAfterManufacturer));
            }
            else if (spaceAfterManufacturer == KErrNotFound)
            {
                productNameShort.Set(hardwareType.Left(
                                         slashAfterManufacturer));
            }
            else
            {
                productNameShort.Set(hardwareType.Left(
                                         slashAfterManufacturer < spaceAfterManufacturer ?
                                         slashAfterManufacturer :
                                         spaceAfterManufacturer));
            }
        }

        productName = HBufC::NewL(productNameShort.Length());
        productName->Des().Copy(productNameShort);
    }

    if (!productName)
    {
        productName = KMicroeditionPlatformValueDefaultPrefix().AllocLC();
    }
    else
    {
        CleanupStack::PushL(productName);
    }

    HBufC* platformName = NULL;

    TBuf<KSysUtilVersionTextLength> swVersion;
    if (SysUtil::GetSWVersion(swVersion) == KErrNone && swVersion.Length()>0)
    {
        // Assume syntax xx.xx\ndd-mm-yy\nNHL-vvv\n(c)Vendor
        TInt NLloc = swVersion.Locate('\n');
        if (KErrNotFound == NLloc)
        {
            NLloc = swVersion.Length();  // no '\n' -> use whole string
        }
        TPtrC verPtr = swVersion.Left(NLloc);

        // Get platform minor and major version numbers
        HBufC* platformVersionValue = GetPlatformVersionL();
        CleanupStack::PushL(platformVersionValue);

        // Get platform properties and values
        HBufC* platformNameProperty = KMicroeditionPlatformName().AllocLC();
        HBufC* platformNameValue = KMicroeditionPlatform().AllocLC();
        HBufC* platformVersionProperty = KMicroeditionPlatformVersion().AllocLC();
        HBufC* platformJavaVersionProperty = KMicroeditionPlatformJavaVersion().AllocLC();

        // Get Java version number
        TVersion versionInfo = Java::JavaEnvInfo::Version();
        TVersionName versionName;
        versionName.AppendNum(versionInfo.iMajor);
        versionName.Append('.');
        versionName.AppendNum(versionInfo.iMinor);
        versionName.Append('.');
        versionName.AppendNum(versionInfo.iBuild);
        HBufC* platformJavaVersionValue = versionName.AllocL();
        CleanupStack::PushL(platformJavaVersionValue);

        // Calculate length of property string
        TUint propertyLength = productName->Length() + 1 + verPtr.Length() + 1;
        propertyLength += platformNameProperty->Length();
        propertyLength += platformNameValue->Length() + 1;
        propertyLength += platformVersionProperty->Length();
        propertyLength += platformVersionValue->Length() + 1;
        propertyLength += platformJavaVersionProperty->Length();
        propertyLength += platformJavaVersionValue->Length();

        // Concatenate properties
        platformName = HBufC::NewL(propertyLength);
        platformName->Des().Append(*productName);
        platformName->Des().Append('/');
        platformName->Des().Append(verPtr);
        platformName->Des().Append('/');
        platformName->Des().Append(*platformNameProperty);
        platformName->Des().Append(*platformNameValue);
        platformName->Des().Append(';');
        platformName->Des().Append(*platformVersionProperty);
        platformName->Des().Append(*platformVersionValue);
        platformName->Des().Append(';');
        platformName->Des().Append(*platformJavaVersionProperty);
        platformName->Des().Append(*platformJavaVersionValue);

        CleanupStack::PopAndDestroy(platformJavaVersionValue);
        CleanupStack::PopAndDestroy(platformJavaVersionProperty);
        CleanupStack::PopAndDestroy(platformVersionProperty);
        CleanupStack::PopAndDestroy(platformNameValue);
        CleanupStack::PopAndDestroy(platformNameProperty);
        CleanupStack::PopAndDestroy(platformVersionValue);
    }

    CleanupStack::PopAndDestroy(productName);
    return platformName;
}