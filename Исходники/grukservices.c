/*
 * Lock & load the kernel context for the specified blade.
 */
static struct gru_blade_state *gru_lock_kernel_context(int blade_id)
{
	struct gru_blade_state *bs;
	int bid;

	STAT(lock_kernel_context);
again:
	bid = blade_id < 0 ? uv_numa_blade_id() : blade_id;
	bs = gru_base[bid];

	/* Handle the case where migration occurred while waiting for the sema */
	down_read(&bs->bs_kgts_sema);
	if (blade_id < 0 && bid != uv_numa_blade_id()) {
		up_read(&bs->bs_kgts_sema);
		goto again;
	}
	if (!bs->bs_kgts || !bs->bs_kgts->ts_gru)
		gru_load_kernel_context(bs, bid);
	return bs;

}