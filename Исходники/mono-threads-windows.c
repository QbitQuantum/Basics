MonoNativeThreadId
mono_native_thread_id_get (void)
{
	return GetCurrentThreadId ();
}