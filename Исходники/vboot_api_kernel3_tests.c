/* Reset mock data (for use before each test) */
static void ResetMocks(void)
{
	Memset(&cparams, 0, sizeof(cparams));
	cparams.shared_data_size = sizeof(shared_data);
	cparams.shared_data_blob = shared_data;
	cparams.gbb_data = &gbb;

	Memset(&gbb, 0, sizeof(gbb));
	gbb.major_version = GBB_MAJOR_VER;
	gbb.minor_version = GBB_MINOR_VER;
	gbb.flags = 0;

	/*
	 * Only the outermost vboot_api_kernel call sets vboot_api_kernel's
	 * vnc.  So clear it here too.
	 */
	Memset(VbApiKernelGetVnc(), 0, sizeof(VbNvContext));
	VbNvSetup(VbApiKernelGetVnc());
	VbNvTeardown(VbApiKernelGetVnc()); /* So CRC gets generated */

	Memset(&shared_data, 0, sizeof(shared_data));
	VbSharedDataInit(shared, sizeof(shared_data));

	trust_ec = 0;
	mock_in_rw = 0;
	ec_ro_protected = 0;
	ec_rw_protected = 0;
	ec_run_image = 0;   /* 0 = RO, 1 = RW */
	ec_ro_updated = 0;
	ec_rw_updated = 0;
	in_rw_retval = VBERROR_SUCCESS;
	protect_retval = VBERROR_SUCCESS;
	update_retval = VBERROR_SUCCESS;
	run_retval = VBERROR_SUCCESS;
	get_expected_retval = VBERROR_SUCCESS;
	shutdown_request_calls_left = -1;

	Memset(mock_ec_ro_hash, 0, sizeof(mock_ec_ro_hash));
	mock_ec_ro_hash[0] = 42;
	mock_ec_ro_hash_size = sizeof(mock_ec_ro_hash);

	Memset(mock_ec_rw_hash, 0, sizeof(mock_ec_rw_hash));
	mock_ec_rw_hash[0] = 42;
	mock_ec_rw_hash_size = sizeof(mock_ec_rw_hash);

	Memset(want_ec_hash, 0, sizeof(want_ec_hash));
	want_ec_hash[0] = 42;
	want_ec_hash_size = sizeof(want_ec_hash);

	update_hash = 42;

	Memset(mock_sha, 0, sizeof(want_ec_hash));
	mock_sha[0] = 42;

	// TODO: ensure these are actually needed

	Memset(screens_displayed, 0, sizeof(screens_displayed));
	screens_count = 0;
}