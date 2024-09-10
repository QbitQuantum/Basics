acpi_status
ec_terminate(void)
{
	acpi_status             status = AE_OK;
	BM_DEVICE_ID		criteria;
	BM_DRIVER		driver;

	FUNCTION_TRACE("ec_terminate");

	MEMSET(&criteria, 0, sizeof(BM_DEVICE_ID));
	MEMSET(&driver, 0, sizeof(BM_DRIVER));

	/*
	 * Unregister driver for AC Adapter devices.
	 */
	MEMCPY(criteria.hid, EC_HID_EC, sizeof(EC_HID_EC));

	driver.notify = &ec_notify;
	driver.request = &ec_request;

	status = bm_unregister_driver(&criteria, &driver);

	return_ACPI_STATUS(status);
}