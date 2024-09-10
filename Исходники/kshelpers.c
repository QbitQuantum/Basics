GList *
ks_enumerate_devices (const GUID * category)
{
  GList *result = NULL;
  HDEVINFO devinfo;
  gint i;

  devinfo = SetupDiGetClassDevsW (category, NULL, NULL,
      DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
  if (!ks_is_valid_handle (devinfo))
    return NULL;                /* no devices */

  for (i = 0;; i++) {
    BOOL success;
    SP_DEVICE_INTERFACE_DATA if_data = { 0, };
    SP_DEVICE_INTERFACE_DETAIL_DATA_W *if_detail_data;
    DWORD if_detail_data_size;
    SP_DEVINFO_DATA devinfo_data = { 0, };
    DWORD req_size;

    if_data.cbSize = sizeof (SP_DEVICE_INTERFACE_DATA);

    success = SetupDiEnumDeviceInterfaces (devinfo, NULL, category, i,
        &if_data);
    if (!success)               /* all devices enumerated? */
      break;

    if_detail_data_size = (MAX_PATH - 1) * sizeof (gunichar2);
    if_detail_data = g_malloc0 (if_detail_data_size);
    if_detail_data->cbSize = sizeof (SP_DEVICE_INTERFACE_DETAIL_DATA_W);

    devinfo_data.cbSize = sizeof (SP_DEVINFO_DATA);

    success = SetupDiGetDeviceInterfaceDetailW (devinfo, &if_data,
        if_detail_data, if_detail_data_size, &req_size, &devinfo_data);
    if (success) {
      KsDeviceEntry *entry;
      WCHAR buf[512];

      entry = g_new0 (KsDeviceEntry, 1);
      entry->index = i;
      entry->path =
          g_utf16_to_utf8 (if_detail_data->DevicePath, -1, NULL, NULL, NULL);

      if (SetupDiGetDeviceRegistryPropertyW (devinfo, &devinfo_data,
              SPDRP_FRIENDLYNAME, NULL, (BYTE *) buf, sizeof (buf), NULL)) {
        entry->name = g_utf16_to_utf8 (buf, -1, NULL, NULL, NULL);
      }

      if (entry->name == NULL) {
        if (SetupDiGetDeviceRegistryPropertyW (devinfo, &devinfo_data,
                SPDRP_DEVICEDESC, NULL, (BYTE *) buf, sizeof (buf), NULL)) {
          entry->name = g_utf16_to_utf8 (buf, -1, NULL, NULL, NULL);
        }
      }

      if (entry->name != NULL)
        result = g_list_prepend (result, entry);
      else
        ks_device_entry_free (entry);
    }

    g_free (if_detail_data);
  }

  SetupDiDestroyDeviceInfoList (devinfo);

  return g_list_reverse (result);
}