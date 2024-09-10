int bpf_prog2(struct pt_regs *ctx)
{
	u64 *ts, cur_ts, delta;
	int key, cpu;
	long *val;

	cpu = bpf_get_smp_processor_id();
	ts = bpf_map_lookup_elem(&my_map, &cpu);
	if (!ts)
		return 0;

	cur_ts = bpf_ktime_get_ns();
	delta = log2l(cur_ts - *ts);

	if (delta > MAX_ENTRIES - 1)
		delta = MAX_ENTRIES - 1;

	key = cpu * MAX_ENTRIES + delta;
	val = bpf_map_lookup_elem(&my_lat, &key);
	if (val)
		__sync_fetch_and_add((long *)val, 1);

	return 0;

}