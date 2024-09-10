void
mono_debugger_initialize ()
{
	InitializeCriticalSection (&debugger_lock_mutex);
	initialized = 1;
}