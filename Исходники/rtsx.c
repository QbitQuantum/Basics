static int proc_info(struct Scsi_Host *host, char *buffer,
		char **start, off_t offset, int length, int inout)
{
	char *pos = buffer;

	/* if someone is sending us data, just throw it away */
	if (inout)
		return length;

	/* print the controller name */
	SPRINTF("   Host scsi%d: %s\n", host->host_no, CR_DRIVER_NAME);

	/* print product, vendor, and driver version strings */
	SPRINTF("       Vendor: Realtek Corp.\n");
	SPRINTF("      Product: PCIE Card Reader\n");
	SPRINTF("      Version: %s\n", DRIVER_VERSION);

	/*
	 * Calculate start of next buffer, and return value.
	 */
	*start = buffer + offset;

	if ((pos - buffer) < offset)
		return 0;
	else if ((pos - buffer - offset) < length)
		return pos - buffer - offset;
	else
		return length;
}