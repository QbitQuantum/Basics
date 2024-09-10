static int dump_freq(void)
{
	char t[128] = { 0 };
	int i;

	sprintf(t, "[ ");

	for (i = 0; i < freqs_cnt; ++i) {
		sprintf(t + strlen(t), "%d/%d ", freqs[i].cpu, freqs[i].bus);
	}

	STRCAT_S(t, "]");

	dbg_printf(d, "%s: Dump freqs table: %s", __func__, t);

	return 0;
}