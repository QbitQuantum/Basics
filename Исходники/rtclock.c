/*
 * rtc_clock_napped:
 *
 * Invoked from power management when we exit from a low C-State (>= C4)
 * and the TSC has stopped counting.  The nanotime data is updated according
 * to the provided value which represents the new value for nanotime.
 */
void
rtc_clock_napped(uint64_t base, uint64_t tsc_base)
{
	pal_rtc_nanotime_t	*rntp = &pal_rtc_nanotime_info;
	uint64_t	oldnsecs;
	uint64_t	newnsecs;
	uint64_t	tsc;

	assert(!ml_get_interrupts_enabled());
	tsc = rdtsc64();
	oldnsecs = rntp->ns_base + _rtc_tsc_to_nanoseconds(tsc - rntp->tsc_base, rntp);
	newnsecs = base + _rtc_tsc_to_nanoseconds(tsc - tsc_base, rntp);
	
	/*
	 * Only update the base values if time using the new base values
	 * is later than the time using the old base values.
	 */
	if (oldnsecs < newnsecs) {
	    _pal_rtc_nanotime_store(tsc_base, base, rntp->scale, rntp->shift, rntp);
	    rtc_nanotime_set_commpage(rntp);
	}
}