acpi_status
bm_compare (
	BM_DEVICE               *device,
	BM_DEVICE_ID            *criteria)
{
	if (!device || !criteria) {
		return AE_BAD_PARAMETER;
	}

	/*
	 * Present?
	 * --------
	 * We're only going to match on devices that are present.
	 * TBD: Optimize in bm_search (don't have to call here).
	 */
	if (!BM_DEVICE_PRESENT(device)) {
		return AE_NOT_FOUND;
	}

	/*
	 * Type?
	 */
	if (criteria->type && (criteria->type != device->id.type)) {
		return AE_NOT_FOUND;
	}

	/*
	 * HID?
	 */
	if ((criteria->hid[0]) && (0 != STRNCMP(criteria->hid,
		device->id.hid, sizeof(BM_DEVICE_HID)))) {
		return AE_NOT_FOUND;
	}

	/*
	 * ADR?
	 */
	if ((criteria->adr) && (criteria->adr != device->id.adr)) {
		return AE_NOT_FOUND;
	}

	return AE_OK;
}