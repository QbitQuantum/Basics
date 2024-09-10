int32_t
GfxInfoBase::FindBlocklistedDeviceInList(const nsTArray<GfxDriverInfo>& info,
                                         nsAString& aSuggestedVersion,
                                         int32_t aFeature,
                                         nsACString& aFailureId,
                                         OperatingSystem os)
{
  int32_t status = nsIGfxInfo::FEATURE_STATUS_UNKNOWN;

  uint32_t i = 0;
  for (; i < info.Length(); i++) {
    // Do the operating system check first, no point in getting the driver
    // info if we won't need to use it.  If the OS of the system we are running
    // on is unknown, we still let DRIVER_OS_ALL catch and disable it; 
    // if the OS of the downloadable entry is unknown, we skip the entry
    // as invalid.
    if (info[i].mOperatingSystem == DRIVER_OS_UNKNOWN ||
        (info[i].mOperatingSystem != DRIVER_OS_ALL &&
         info[i].mOperatingSystem != os))
    {
      continue;
    }

    if (info[i].mOperatingSystemVersion && info[i].mOperatingSystemVersion != OperatingSystemVersion()) {
        continue;
    }

    // XXX: it would be better not to do this everytime round the loop
    nsAutoString adapterVendorID;
    nsAutoString adapterDeviceID;
    nsAutoString adapterDriverVersionString;
    if (info[i].mGpu2) {
      if (NS_FAILED(GetAdapterVendorID2(adapterVendorID)) ||
          NS_FAILED(GetAdapterDeviceID2(adapterDeviceID)) ||
          NS_FAILED(GetAdapterDriverVersion2(adapterDriverVersionString)))
      {
        return 0;
      }
    } else {
      if (NS_FAILED(GetAdapterVendorID(adapterVendorID)) ||
          NS_FAILED(GetAdapterDeviceID(adapterDeviceID)) ||
          NS_FAILED(GetAdapterDriverVersion(adapterDriverVersionString)))
      {
        return 0;
      }
    }

#if defined(XP_WIN) || defined(ANDROID)
    uint64_t driverVersion;
    ParseDriverVersion(adapterDriverVersionString, &driverVersion);
#endif

    if (!info[i].mAdapterVendor.Equals(GfxDriverInfo::GetDeviceVendor(VendorAll), nsCaseInsensitiveStringComparator()) &&
        !info[i].mAdapterVendor.Equals(adapterVendorID, nsCaseInsensitiveStringComparator())) {
      continue;
    }

    if (info[i].mDevices != GfxDriverInfo::allDevices && info[i].mDevices->Length()) {
        bool deviceMatches = false;
        for (uint32_t j = 0; j < info[i].mDevices->Length(); j++) {
            if ((*info[i].mDevices)[j].Equals(adapterDeviceID, nsCaseInsensitiveStringComparator())) {
                deviceMatches = true;
                break;
            }
        }

        if (!deviceMatches) {
            continue;
        }
    }

    bool match = false;

    if (!info[i].mHardware.IsEmpty() && !info[i].mHardware.Equals(Hardware())) {
        continue;
    }
    if (!info[i].mModel.IsEmpty() && !info[i].mModel.Equals(Model())) {
        continue;
    }
    if (!info[i].mProduct.IsEmpty() && !info[i].mProduct.Equals(Product())) {
        continue;
    }
    if (!info[i].mManufacturer.IsEmpty() && !info[i].mManufacturer.Equals(Manufacturer())) {
        continue;
    }

#if defined(XP_WIN) || defined(ANDROID)
    switch (info[i].mComparisonOp) {
    case DRIVER_LESS_THAN:
      match = driverVersion < info[i].mDriverVersion;
      break;
    case DRIVER_LESS_THAN_OR_EQUAL:
      match = driverVersion <= info[i].mDriverVersion;
      break;
    case DRIVER_GREATER_THAN:
      match = driverVersion > info[i].mDriverVersion;
      break;
    case DRIVER_GREATER_THAN_OR_EQUAL:
      match = driverVersion >= info[i].mDriverVersion;
      break;
    case DRIVER_EQUAL:
      match = driverVersion == info[i].mDriverVersion;
      break;
    case DRIVER_NOT_EQUAL:
      match = driverVersion != info[i].mDriverVersion;
      break;
    case DRIVER_BETWEEN_EXCLUSIVE:
      match = driverVersion > info[i].mDriverVersion && driverVersion < info[i].mDriverVersionMax;
      break;
    case DRIVER_BETWEEN_INCLUSIVE:
      match = driverVersion >= info[i].mDriverVersion && driverVersion <= info[i].mDriverVersionMax;
      break;
    case DRIVER_BETWEEN_INCLUSIVE_START:
      match = driverVersion >= info[i].mDriverVersion && driverVersion < info[i].mDriverVersionMax;
      break;
    case DRIVER_COMPARISON_IGNORED:
      // We don't have a comparison op, so we match everything.
      match = true;
      break;
    default:
      NS_WARNING("Bogus op in GfxDriverInfo");
      break;
    }
#else
    // We don't care what driver version it was. We only check OS version and if
    // the device matches.
    match = true;
#endif

    if (match || info[i].mDriverVersion == GfxDriverInfo::allDriverVersions) {
      if (info[i].mFeature == GfxDriverInfo::allFeatures ||
          info[i].mFeature == aFeature)
      {
        status = info[i].mFeatureStatus;
        if (!info[i].mRuleId.IsEmpty()) {
          aFailureId = info[i].mRuleId.get();
        } else {
          aFailureId = "FEATURE_FAILURE_DL_BLACKLIST_NO_ID";
        }
        break;
      }
    }
  }

#if defined(XP_WIN)
  // As a very special case, we block D2D on machines with an NVidia 310M GPU
  // as either the primary or secondary adapter.  D2D is also blocked when the
  // NV 310M is the primary adapter (using the standard blocklisting mechanism).
  // If the primary GPU already matched something in the blocklist then we
  // ignore this special rule.  See bug 1008759.
  if (status == nsIGfxInfo::FEATURE_STATUS_UNKNOWN &&
    (aFeature == nsIGfxInfo::FEATURE_DIRECT2D)) {
    nsAutoString adapterVendorID2;
    nsAutoString adapterDeviceID2;
    if ((!NS_FAILED(GetAdapterVendorID2(adapterVendorID2))) &&
      (!NS_FAILED(GetAdapterDeviceID2(adapterDeviceID2))))
    {
      nsAString &nvVendorID = (nsAString &)GfxDriverInfo::GetDeviceVendor(VendorNVIDIA);
      const nsString nv310mDeviceId = NS_LITERAL_STRING("0x0A70");
      if (nvVendorID.Equals(adapterVendorID2, nsCaseInsensitiveStringComparator()) &&
        nv310mDeviceId.Equals(adapterDeviceID2, nsCaseInsensitiveStringComparator())) {
        status = nsIGfxInfo::FEATURE_BLOCKED_DEVICE;
        aFailureId = "FEATURE_FAILURE_D2D_NV310M_BLOCK";
      }
    }
  }

  // Depends on Windows driver versioning. We don't pass a GfxDriverInfo object
  // back to the Windows handler, so we must handle this here.
  if (status == FEATURE_BLOCKED_DRIVER_VERSION) {
    if (info[i].mSuggestedVersion) {
        aSuggestedVersion.AppendPrintf("%s", info[i].mSuggestedVersion);
    } else if (info[i].mComparisonOp == DRIVER_LESS_THAN &&
               info[i].mDriverVersion != GfxDriverInfo::allDriverVersions)
    {
        aSuggestedVersion.AppendPrintf("%lld.%lld.%lld.%lld",
                                      (info[i].mDriverVersion & 0xffff000000000000) >> 48,
                                      (info[i].mDriverVersion & 0x0000ffff00000000) >> 32,
                                      (info[i].mDriverVersion & 0x00000000ffff0000) >> 16,
                                      (info[i].mDriverVersion & 0x000000000000ffff));
    }
  }