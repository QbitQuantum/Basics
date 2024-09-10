nsresult
GfxInfo::GetFeatureStatusImpl(int32_t aFeature,
                              int32_t *aStatus, 
                              nsAString & aSuggestedDriverVersion, 
                              const nsTArray<GfxDriverInfo>& aDriverInfo,
                              OperatingSystem* aOS /* = nullptr */)
{
  NS_ENSURE_ARG_POINTER(aStatus);
  aSuggestedDriverVersion.SetIsVoid(true);
  OperatingSystem os = WindowsVersionToOperatingSystem(mWindowsVersion);
  *aStatus = nsIGfxInfo::FEATURE_STATUS_UNKNOWN;
  if (aOS)
    *aOS = os;

  // Don't evaluate special cases if we're checking the downloaded blocklist.
  if (!aDriverInfo.Length()) {
    nsAutoString adapterVendorID;
    nsAutoString adapterDeviceID;
    nsAutoString adapterDriverVersionString;
    if (NS_FAILED(GetAdapterVendorID(adapterVendorID)) ||
        NS_FAILED(GetAdapterDeviceID(adapterDeviceID)) ||
        NS_FAILED(GetAdapterDriverVersion(adapterDriverVersionString)))
    {
      return NS_ERROR_FAILURE;
    }

    if (!adapterVendorID.Equals(GfxDriverInfo::GetDeviceVendor(VendorIntel), nsCaseInsensitiveStringComparator()) &&
        !adapterVendorID.Equals(GfxDriverInfo::GetDeviceVendor(VendorNVIDIA), nsCaseInsensitiveStringComparator()) &&
        !adapterVendorID.Equals(GfxDriverInfo::GetDeviceVendor(VendorAMD), nsCaseInsensitiveStringComparator()) &&
        !adapterVendorID.Equals(GfxDriverInfo::GetDeviceVendor(VendorATI), nsCaseInsensitiveStringComparator()) &&
        !adapterVendorID.Equals(GfxDriverInfo::GetDeviceVendor(VendorMicrosoft), nsCaseInsensitiveStringComparator()) &&
        // FIXME - these special hex values are currently used in xpcshell tests introduced by
        // bug 625160 patch 8/8. Maybe these tests need to be adjusted now that we're only whitelisting
        // intel/ati/nvidia.
        !adapterVendorID.LowerCaseEqualsLiteral("0xabcd") &&
        !adapterVendorID.LowerCaseEqualsLiteral("0xdcba") &&
        !adapterVendorID.LowerCaseEqualsLiteral("0xabab") &&
        !adapterVendorID.LowerCaseEqualsLiteral("0xdcdc"))
    {
      *aStatus = FEATURE_BLOCKED_DEVICE;
      return NS_OK;
    }

    uint64_t driverVersion;
    if (!ParseDriverVersion(adapterDriverVersionString, &driverVersion)) {
      return NS_ERROR_FAILURE;
    }

    // special-case the WinXP test slaves: they have out-of-date drivers, but we still want to
    // whitelist them, actually we do know that this combination of device and driver version
    // works well.
    if (mWindowsVersion == kWindowsXP &&
        adapterVendorID.Equals(GfxDriverInfo::GetDeviceVendor(VendorNVIDIA), nsCaseInsensitiveStringComparator()) &&
        adapterDeviceID.LowerCaseEqualsLiteral("0x0861") && // GeForce 9400
        driverVersion == V(6,14,11,7756))
    {
      *aStatus = FEATURE_STATUS_OK;
      return NS_OK;
    }

    // Windows Server 2003 should be just like Windows XP for present purpose, but still has a different version number.
    // OTOH Windows Server 2008 R1 and R2 already have the same version numbers as Vista and Seven respectively
    if (os == DRIVER_OS_WINDOWS_SERVER_2003)
      os = DRIVER_OS_WINDOWS_XP;

    if (mHasDriverVersionMismatch) {
      if (aFeature == nsIGfxInfo::FEATURE_DIRECT3D_10_LAYERS ||
          aFeature == nsIGfxInfo::FEATURE_DIRECT3D_10_1_LAYERS ||
          aFeature == nsIGfxInfo::FEATURE_DIRECT2D ||
          aFeature == nsIGfxInfo::FEATURE_DIRECT3D_11_LAYERS)
      {
        *aStatus = nsIGfxInfo::FEATURE_BLOCKED_DRIVER_VERSION;
        return NS_OK;
      }
    }
  }

  return GfxInfoBase::GetFeatureStatusImpl(aFeature, aStatus, aSuggestedDriverVersion, aDriverInfo, &os);
}