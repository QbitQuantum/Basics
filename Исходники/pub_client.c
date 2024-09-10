static void set_repeat_time(void)
{
	uint64_t ticks = GetTickCount64();
	next_publish_tv = ticks + cfg.repeat_delay.tv_sec*1000 + cfg.repeat_delay.tv_usec/1000;
}