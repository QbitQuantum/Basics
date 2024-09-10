/** Start scheduler */
MPF_DECLARE(apt_bool_t) mpf_scheduler_start(mpf_scheduler_t *scheduler)
{
	mpf_scheduler_resolution_set(scheduler);
	scheduler->timer_id = timeSetEvent(
					scheduler->resolution, 0, mm_timer_proc, (DWORD_PTR) scheduler, 
					TIME_PERIODIC | TIME_CALLBACK_FUNCTION | TIME_KILL_SYNCHRONOUS);
	return scheduler->timer_id ? TRUE : FALSE;
}