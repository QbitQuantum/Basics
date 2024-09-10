long DisplayCollector::CollectFallback(NVDataItem * TargetItem)
{
	DISPLAY_DEVICEW CurrDevInfo;
	long CurrDevIndex;

	for (CurrDevIndex = 0, CurrDevInfo.cb = sizeof (DISPLAY_DEVICE);
		EnumDisplayDevicesW(NULL, CurrDevIndex, &CurrDevInfo, 0);
		CurrDevIndex ++, CurrDevInfo.cb = sizeof (DISPLAY_DEVICE))
	{
		
		if ((CurrDevInfo.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) == DISPLAY_DEVICE_MIRRORING_DRIVER)
			continue;

		auto_ptr<NVDataItem> ReportItem (new NVDataItem(DISPCI_TAG));
		
		ReportItem->AddNVItem(DISP_DESC, CurrDevInfo.DeviceString);
		ReportItem->AddNVItem(DISP_FID, CurrDevInfo.DeviceName);
		TargetItem->AddSubItem(ReportItem.release());

	}

#ifdef INSTRUMENTED
	MessageBox(NULL, "Display Complete!", "Report", MB_OK);
#endif
	return ERROR_SUCCESS;
}