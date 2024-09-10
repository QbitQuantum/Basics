void PixelPipeline::worker_main(int core)
{
#if defined(WIN32) && defined(PROFILE_PIPELINE)
	SetThreadIdealProcessor(GetCurrentThread(), core);
	SetThreadAffinityMask(GetCurrentThread(), 1 << core);
	unsigned __int64 ticks_waiting = 0;
	unsigned __int64 ticks_working = 0;
#endif
	PixelThreadContext context(core, active_cores);
	while (true)
	{
#if defined(WIN32) && defined(PROFILE_PIPELINE)
		unsigned __int64 wait_start_time = __rdtsc();
#endif
		int wakeup_reason = Event::wait(event_more_commands[core], event_stop);
		if (wakeup_reason != 0)
			break;
		event_more_commands[core].reset();
#if defined(WIN32) && defined(PROFILE_PIPELINE)
		unsigned __int64 wait_end_time = __rdtsc();
		ticks_waiting += wait_end_time-wait_start_time;
#endif
		process_commands(&context);
#if defined(WIN32) && defined(PROFILE_PIPELINE)
		unsigned __int64 commands_end_time = __rdtsc();
		ticks_working += commands_end_time-wait_end_time;
#endif
	}
#if defined(WIN32) && defined(PROFILE_PIPELINE)
	MessageBoxA(
		0,
		cl_format("Pipeline core %1 spent %2 percent of its time waiting for commands",
		core,
		(int)(ticks_waiting*100/(ticks_working+ticks_waiting))).c_str(),
		"DEBUG", MB_OK);
#endif
}