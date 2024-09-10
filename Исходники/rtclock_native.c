static uint64_t
rtc_lapic_set_tsc_deadline_timer(uint64_t deadline, uint64_t now)
{
	uint64_t delta;
	uint64_t delta_tsc;
	uint64_t tsc = rdtsc64();
	uint64_t set = 0;

	if (deadline > 0) {
		/*
		 * Convert to TSC
		 */
		delta = deadline_to_decrementer(deadline, now);
		set = now + delta;
		delta_tsc = tmrCvt(delta, tscFCvtn2t);
		lapic_set_tsc_deadline_timer(tsc + delta_tsc);
	} else {
		lapic_set_tsc_deadline_timer(0);
	}
	
	KERNEL_DEBUG_CONSTANT(
		DECR_SET_TSC_DEADLINE | DBG_FUNC_NONE,
		now, deadline,
		tsc, lapic_get_tsc_deadline_timer(),
		0);

	return set;
} 