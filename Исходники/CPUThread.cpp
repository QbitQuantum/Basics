void cpu_thread::set_ideal_processor_core(int core)
{
#ifdef _WIN32
	HANDLE _this_thread = GetCurrentThread();
	SetThreadIdealProcessor(_this_thread, core);
#endif
}