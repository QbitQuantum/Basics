/* Reset mock data (for use before each test) */
static void ResetMocks(void)
{
	int gbb_used;

	Memset(gbb_data, 0, sizeof(gbb_data));
	gbb->major_version = GBB_MAJOR_VER;
	gbb->minor_version = GBB_MINOR_VER;
	gbb->flags = 0;
	gbb_used = sizeof(GoogleBinaryBlockHeader);

	gbb->hwid_offset = gbb_used;
	strcpy(gbb_data + gbb->hwid_offset, "Test HWID");
	gbb->hwid_size = strlen(gbb_data + gbb->hwid_offset) + 1;
	gbb_used = (gbb_used + gbb->hwid_size + 7) & ~7;

	gbb->bmpfv_offset = gbb_used;
	bhdr = (BmpBlockHeader *)(gbb_data + gbb->bmpfv_offset);
	gbb->bmpfv_size = sizeof(BmpBlockHeader);
	gbb_used = (gbb_used + gbb->bmpfv_size + 7) & ~7;
	memcpy(bhdr->signature, BMPBLOCK_SIGNATURE, BMPBLOCK_SIGNATURE_SIZE);
	bhdr->major_version = BMPBLOCK_MAJOR_VERSION;
	bhdr->minor_version = BMPBLOCK_MINOR_VERSION;
	bhdr->number_of_localizations = 3;

	Memset(&cparams, 0, sizeof(cparams));
	cparams.shared_data_size = sizeof(shared_data);
	cparams.shared_data_blob = shared_data;
	cparams.gbb_data = gbb;
	cparams.gbb_size = sizeof(gbb_data);

	/*
	 * Note, VbApiKernelFree() expects this to be allocated by
	 * VbExMalloc(), so we cannot just assign it staticly.
	 */
	cparams.gbb = VbExMalloc(sizeof(*gbb));
	gbb->header_size = sizeof(*gbb);
	gbb->rootkey_offset = gbb_used;
	gbb->rootkey_size = 64;
	gbb_used += 64;
	gbb->recovery_key_offset = gbb_used;
	gbb->recovery_key_size = 64;
	gbb_used += 64;
	memcpy(cparams.gbb, gbb, sizeof(*gbb));

	Memset(&vnc, 0, sizeof(vnc));
	VbNvSetup(&vnc);
	VbNvTeardown(&vnc);                   /* So CRC gets generated */

	Memset(&shared_data, 0, sizeof(shared_data));
	VbSharedDataInit(shared, sizeof(shared_data));

	*debug_info = 0;
}