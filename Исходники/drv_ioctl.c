int dc_get_boot_device(wchar_t *device)
{
	dc_ioctl dctl;
	u32      bytes;
	int      succs;

	wcscpy(dctl.device, L"\\ArcName\\multi(0)disk(0)rdisk(0)partition(1)");

	succs = DeviceIoControl(
		TlsGetValue(h_tls_idx), DC_CTL_RESOLVE, 
		&dctl, sizeof(dctl), &dctl, sizeof(dctl), &bytes, NULL);

	if (succs != 0) 
	{
		if (dctl.status == ST_OK) {
			wcscpy(device, dctl.device);			
		}
		return dctl.status;
	} else {		
		return ST_ERROR;
	}
}