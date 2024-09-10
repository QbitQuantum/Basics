/**
 * Reset mock data (for use before each test)
 */
static void ResetMocks(int i)
{
	Memset(&lkparams, 0, sizeof(lkparams));
	Memset(&mock_disks, 0, sizeof(mock_disks));
	load_kernel_calls = 0;

	got_recovery_request_val = VBNV_RECOVERY_NOT_REQUESTED;
	got_find_disk = 0;
	got_load_disk = 0;
	got_return_val = 0xdeadbeef;

	t = test + i;
}