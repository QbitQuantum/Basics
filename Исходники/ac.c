acpi_status
ac_initialize (void)
{
    acpi_status		status = AE_OK;
    BM_DEVICE_ID		criteria;
    BM_DRIVER		driver;

    FUNCTION_TRACE("ac_initialize");

    MEMSET(&criteria, 0, sizeof(BM_DEVICE_ID));
    MEMSET(&driver, 0, sizeof(BM_DRIVER));

    driver.notify = &ac_notify;
    driver.request = &ac_request;

    /*
     * Register driver for AC Adapter devices.
     */
    MEMCPY(criteria.hid, AC_HID_AC_ADAPTER, sizeof(AC_HID_AC_ADAPTER));

    status = bm_register_driver(&criteria, &driver);

    return_ACPI_STATUS(status);
}